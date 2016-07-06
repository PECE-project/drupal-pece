<?php

/**
 * @file
 * Class definition of FeedsZoteroProcessor.
 */
// Create or delete FEEDS_NODE_BATCH_SIZE at a time.
define('FEEDS_NODE_BATCH_SIZE', 50);

// Deprecated. Use FEEDS_SKIPE_EXISTING, FEEDS_REPLACE_EXISTNG,
// FEEDS_UPDATE_EXISTING instead.
define('FEEDS_NODE_SKIP_EXISTING', 0);
define('FEEDS_NODE_REPLACE_EXISTING', 1);
define('FEEDS_NODE_UPDATE_EXISTING', 2);

module_load_include('inc', 'feeds', 'plugins/FeedsNodeProcessor');

/**
 * Creates nodes from feed items.
 * This is a modified version of FeedsNodeProcessor
 */
class FeedsZoteroProcessor extends FeedsNodeProcessor {

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    $config = parent::configDefaults();
    $config['sync_tags'] = FALSE;
    $config['tags_field'] = NULL;
    $config['tags_vocab'] = NULL;
    $config['collections_field'] = NULL;
    $config['collections_vocab'] = NULL;
    $config['notes_field'] = 'biblio_notes';
    $config['use_feed_owner_as_author'] = FALSE;
    $config['zotero_username_field_name'] = NULL;
    $config['url_field'] = NULL;
    return $config;
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);
    $c = $this->getConfig();

    // Get vocabularies for this content type.
    $content_type = !empty($this->config['bundle']) ? $this->config['bundle'] : 'biblio';

    $taxonomy_fields = biblio_zotero_fields_by_type_by_bundle('node', $content_type, 'taxonomy_term_reference');
    $taxo_field_options = array(t(' - Select -'));
    $taxo_field_options += $taxonomy_fields;

    if (!empty($taxonomy_fields)) {
      $form['sync_tags'] = array(
        '#type' => 'radios',
        '#title' => t('Sync zotero tags to a term reference field in the biblio content type?'),
        '#options' => array(1 => t('yes'), 0 => t('no')),
        '#default_value' => $this->config['sync_tags'],
      );

      $warning = t('Important - to sync tags for this feed, you need at at least one taxonomy vocabulary configured and a term reference field in your content type: ') . l(t('taxonomy settings'), 'admin/content/taxonomy');
      $desc = empty($taxo_field_options) ? sprintf('<span class=\'warning\'>%s</span>', $warning) : '';
      $form['tags_field'] = array(
        '#type' => 'select',
        '#title' => t('Select a term reference field in the @type content type to use for zotero tags.', array('@type' => $content_type)),
        '#description' => $desc,
        '#options' => $taxo_field_options,
        '#default_value' => $this->config['tags_field'],
      );

      $form['tags_vocab'] = array(
        '#type' => 'textfield',
        '#title' => t('Vocab Machine Name [not editable]'),
        '#size' => 60,
        '#disabled' => TRUE,
        '#default_value' => $this->config['tags_vocab'] ? $this->config['tags_vocab'] : '',
        '#description' => $this->config['tags_vocab'] ? '' : t('<span class="warning">No taxonomy term reference field has been submitted yet</span>'),
      );
      #Collections taxonomy field
      $form['collections_field'] = array(
        '#type' => 'select',
        '#title' => t('Select a term reference field in the @type content type to use for collections.', array('@type' => $content_type)),
        '#description' => $desc,
        '#options' => $taxo_field_options,
        '#default_value' => isset($this->config['collections_field']) ? $this->config['collections_field'] : FALSE,
      );
      $form['collection_vocab'] = array(
        '#type' => 'textfield',
        '#title' => t('Collections Vocab Machine Name [not editable]'),
        '#size' => 60,
        '#disabled' => TRUE,
        '#default_value' => isset($this->config['collections_vocab']) ? $this->config['collections_vocab'] : '',
        '#description' => isset($this->config['collections_vocab']) ? '' : t('<span class="warning">No taxonomy term reference field has been submitted yet</span>'),
      );
    } else {
      $form['no_vocabs'] = array(
        '#markup' => t('<p class="warning">Please configure at least one !taxo_link to import zotero tags. </p>', array('!taxo_link' => l(t('taxonomy vocabulary'), 'admin/structure/taxonomy')))
      );
    }
    $text_fields = biblio_zotero_fields_by_type_by_bundle('node', $content_type, 'text_textfield');
    $text_field_options = array(t(' - Select -'));
    $text_field_options += $text_fields;

    if (!empty($text_fields)) {
      $form['url_field'] = array(
        '#type' => 'select',
        '#title' => t('Zotero item URL field'),
        '#description' => t('Select a text field in the @type content type to use for the Zotero item URL.', array('@type' => $content_type)),
        '#options' => $text_field_options,
        '#default_value' => $this->config['url_field'],
      );
    }
    else {
      $form['url_field'] = array(
        '#markup' => t('To save the Zotero item URL for each item on @type nodes, add a text field on that node type to hold it.', array('@type' => $content_type)),
      );
    }

    // AUTHOR settings for imported nodes
    // Use feed_owner as author?
    $form['use_feed_owner_as_author'] = array(
      '#type' => 'radios',
      '#title' => t('Use the feed owner\'s user account the author of imported nodes?'),
      '#description' => t('This will override the \'Author\' setting above'),
      '#options' => array(1 => t('yes'), 0 => t('no')),
      '#default_value' => $this->config['use_feed_owner_as_author'],
    );

    // Choose a field for zotero usernames stored in the user profile
    /** @TODO test this with profile and profile2 modules * */
    $fields = field_info_instances("user");
    $zotero_username_field_options = array();
    $zotero_username_field_options[''] = t(' - Select -'); // if this option is chosen it means don't map zotero users to drupal users
    foreach ($fields['user'] as $field_machine_name => $field) {
      if ($field['entity_type'] == 'user') {
        $zotero_username_field_options[$field_machine_name] = $field['label'];
      }
    }
    $form['zotero_username_field_name'] = array(
      '#title' => t('Zotero Username Profile Field'),
      '#description' => t('In !user_settings_link you can add a user profile field for a user\'s zotero username which will allow zotero content to be attributed to drupal user accounts. This will override the \'Author\' and \'Use the feed owner\'s user account\' settings above.', array('!user_settings_link' => l(t('User Account Settings -> Manage Fields'), 'admin/config/people/accounts/fields'))),
      '#type' => 'select',
      '#options' => $zotero_username_field_options,
      '#default_value' => $this->config['zotero_username_field_name'],
    );
    return $form;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    parent::configFormValidate($values);

    if (!empty($values['sync_tags']) && empty($values['tags_field'])) {
      $warning = t('To sync tags for this feed, you need at at least one taxonomy vocabulary configured and a term reference field in your content type:  !taxo_admin', array('!taxo_admin' => l(t('taxonomy settings'), 'admin/content/taxonomy')));
      form_set_error('tags_field', $warning);
    }

    if (!empty($values['tags_field'])) {
      // get the taxo machine name from the field info
      $taxo_field_name = $this->config['tags_field'];
      $taxo_field_info = field_info_field($values['tags_field']);
      if ($taxo_field_info['settings']['allowed_values'][0]['vocabulary']) {
        $vocab_machine_name = $taxo_field_info['settings']['allowed_values'][0]['vocabulary'];
        $values['tags_vocab'] = $vocab_machine_name;
      } else {
        $warning = t('');
        form_set_error('tags_field', $warning);
      }
    }
    if (!empty($values['collections_field'])) {
      // get the taxo machine name from the field info
      $taxo_field_name = $this->config['collections_field'];
      $taxo_field_info = field_info_field($values['collections_field']);
      if ($taxo_field_info['settings']['allowed_values'][0]['vocabulary']) {
        $vocab_machine_name = $taxo_field_info['settings']['allowed_values'][0]['vocabulary'];
        $values['collections_vocab'] = $vocab_machine_name;
      } else {
        $warning = t('');
        form_set_error('collections_field', $warning);
      }
    }
  }

  /**
   * Reschedule if expiry time changes.
   */
  public function configFormSubmit(&$values) {
    parent::configFormSubmit($values);
  }

  /**
   * Return available mapping targets.
   * target names are from MySql Db:  DESCRIBE biblio_fields
   */
  //  THESE ARE ACTUALL ALREADY PROVIDED IN biblio.feeds.inc _biblio_feeds_processor_targets_alter()
  public function getMappingTargets() {
    $targets = array(
      'biblio_number' => array(
        'name' => t('Biblio - Number'),
      ),
      'biblio_other_number' => array(
        'name' => t('Biblio - Other number'),
      ),
      'biblio_sort_title' => array(
        'name' => t('Biblio - Sort title'),
        'description' => 'A normalized version of the title, used for sorting on titles. (only first 64 characters saved)',
      ),
      'biblio_secondary_title' => array(
        'name' => t('Biblio - Secondary title'),
      ),
      'biblio_tertiary_title' => array(
        'name' => t('Biblio - Tertiary title'),
      ),
      'biblio_edition' => array(
        'name' => t('Biblio - Edition'),
      ),
      'biblio_publisher' => array(
        'name' => t('Biblio - Publisher'),
      ),
      'biblio_place_published' => array(
        'name' => t('Biblio - Place published'),
      ),
      'biblio_year' => array(
        'name' => 'Biblio - Year',
      ),
      'biblio_volume' => array(
        'name' => t('Biblio - Volume'),
      ),
      'biblio_pages' => array(
        'name' => t('Biblio - Pages'),
      ),
      'biblio_date' => array(
        'name' => t('Biblio - Date'),
      ),
      'biblio_isbn' => array(
        'name' => t('Biblio - ISBN'),
      ),
      'biblio_lang' => array(
        'name' => t('Biblio - Language'),
      ),
      'biblio_abst_e' => array(
        'name' => t('Biblio - Abstract E'),
      ),
      'biblio_abst_f' => array(
        'name' => t('Biblio - Abstract F'),
      ),
      'biblio_url' => array(
        'name' => t('Biblio - Url'),
      ),
      'biblio_issue' => array(
        'name' => t('Biblio - Issue'),
      ),
      'biblio_type_of_work' => array(
        'name' => t('Biblio - Type of work'),
      ),
      'biblio_accession_number' => array(
        'name' => t('Biblio - Accession number'),
      ),
      'biblio_call_number' => array(
        'name' => t('Biblio - Call number'),
      ),
      'biblio_notes' => array(
        'name' => t('Biblio - Notes'),
      ),
      'biblio_custom1' => array(
        'name' => t('Biblio - Custom 1'),
      ),
      'biblio_custom2' => array(
        'name' => t('Biblio - Custom 2'),
      ),
      'biblio_custom3' => array(
        'name' => t('Biblio - Custom 3'),
      ),
      'biblio_custom4' => array(
        'name' => t('Biblio - Custom 4'),
      ),
      'biblio_custom5' => array(
        'name' => t('Biblio - Custom 5'),
      ),
      'biblio_custom6' => array(
        'name' => t('Biblio - Custom 6'),
      ),
      'biblio_custom7' => array(
        'name' => t('Biblio - Custom 7'),
      ),
      'biblio_research_notes' => array(
        'name' => t('Biblio - Research notes'),
      ),
      'biblio_number_of_volumes' => array(
        'name' => t('Biblio - Number of volumes'),
      ),
      'biblio_short_title' => array(
        'name' => t('Biblio - Short title'),
      ),
      'biblio_alternate_title' => array(
        'name' => t('Biblio - Alternate title'),
      ),
      'biblio_original_publication' => array(
        'name' => t('Biblio - Original publication'),
      ),
      'biblio_reprint_edition' => array(
        'name' => t('Biblio - Reprint edition'),
      ),
      'biblio_translated_title' => array(
        'name' => t('Biblio - Translated title'),
      ),
      'biblio_section' => array(
        'name' => t('Biblio - Section'),
      ),
      'biblio_citekey' => array(
        'name' => t('Biblio - Citekey'),
      ),
      'biblio_coins' => array(
        'name' => t('Biblio - COinS'),
      ),
      'biblio_doi' => array(
        'name' => t('Biblio - DOI'),
      ),
      'biblio_issn' => array(
        'name' => t('Biblio - Issn'),
      ),
      'biblio_auth_address' => array(
        'name' => t('Biblio - Author address'),
      ),
      'biblio_remote_db_name' => array(
        'name' => t('Biblio - Remote db name'),
      ),
      'biblio_remote_db_provider' => array(
        'name' => t('Biblio - Remote db provider'),
      ),
      'biblio_label' => array(
        'name' => t('Biblio - Label'),
      ),
      'biblio_access_date' => array(
        'name' => t('Biblio - Access date'),
      ),
      'biblio_refereed' => array(
        'name' => t('Biblio - Refereed'),
      ),
      'biblio_formats' => array(
        'name' => t('Biblio - Formats'),
      ),
    ) + parent::getMappingTargets();

    // Allow other modules to modify targets.
    if (method_exists($this, 'getHookTargets')) {
      $this->getHookTargets($targets);
    }

    return $targets;
  }

  public function process(FeedsSource $source, FeedsParserResult $parser_result) {
    /*
      // debugging mappings; keep this;
      $conf = $this->getConfig();
      $msources = array();
      foreach($conf['mappings'] as $m) {
      $msources[] = $m['source'] . ' -> ' . $m['target'];
      }
      dpm($msources, "msources");
     */

    //Create taxonomy terms for our Zotero collections
    $enable_search_index = FALSE;
    //Make sure rebuild biblio search index is disabled on import, or it will re-index everytime we import a node, slowly things down dramatically
    if (variable_get('biblio_index', 0)) {
      $enable_search_index = TRUE;
      variable_set('biblio_index', 0);
    }

    // this needs to go here since map is called multiple times per import.
    $source->reportFilePath = file_directory_temp() . "/biblio-zotero-mapping-report-" . time() . ".tab.txt";
    file_put_contents($source->reportFilePath, "zotero itemtype\tzotero field name\tbiblio field mapping\n");
    $msg = t('Biblio Zotero wrote an import report of mapped and un-mapped fields to @filename', array('@filename' => $source->reportFilePath));
    watchdog('FeedsZoteroProcessor', $msg, NULL, WATCHDOG_NOTICE, $link = NULL);
    drupal_set_message(t('Biblio Zotero wrote an import report of mapped and un-mapped fields to drupal\'s temp directory. See the watchdog for details.'));

    parent::process($source, $parser_result);

    if (isset($this->config['tags_vocab']) and !empty($this->config['tags_vocab'])) {
      $this->cleanUpZoteroTags();
    }

    if ($enable_search_index) {
      variable_set('biblio_index', 1);
    }
    // Reindex search.
    search_update_totals();
    /** @TODO look at parent::process to see about UPDATING during import * */
  }

  protected function cleanUpZoteroTags() {
    $tags_vocab = taxonomy_vocabulary_machine_name_load($this->config['tags_vocab']);
    $tags_tree = taxonomy_get_tree($tags_vocab->vid);
    $delete_count = 0;
    foreach ($tags_tree as $term) {
      $nodes = taxonomy_select_nodes($term->tid);
      if (empty($nodes)) {
        $delete_count++;
        $delete = taxonomy_term_delete($term->tid);
      }
    }
    if ($delete_count) {
      drupal_set_message('Deleted ' . $delete_count . ' Zotero tag taxonomy terms', 'status');
    }
  }

  /**
   * Deletes terms with no nodes associated to it for this collection
   */
  protected function cleanUpCollectionTerms($collections, $recursive = FALSE) {
    $vocab = taxonomy_vocabulary_machine_name_load($this->config['collections_vocab']);
    if ($vocab) {
      foreach ($collections as $collection) {
        $term = biblio_zotero_get_collection_term($collection['key']);
        $nodes = taxonomy_select_nodes($term->tid);
        $collection['child_has_nodes'] = FALSE;
        if ($collection['children']) {
          $collection['child_has_nodes'] = $this->cleanUpCollectionTerms($collection['children'], TRUE);
        }

        if (empty($nodes) && !$collection['child_has_nodes']) {
          taxonomy_term_delete($term->tid);

          if ($recursive) {
            return FALSE;
          }
        }
      }
    }

    return TRUE;
  }

  protected function createCollectionTerm($name, $collection_key, $parent_collection_key = FALSE) {
    $vocab = taxonomy_vocabulary_machine_name_load($this->config['collections_vocab']);
    $term = new StdClass();
    $term->vid = $vocab->vid;
    $term->name = $name;
    $term->key = $collection_key;
    $term->parentterm = $parent_collection_key;
    if ($parent_collection_key) {
      $term->parent = biblio_zotero_get_collection_term($parent_collection_key)->tid;
    }
    taxonomy_term_save($term);
    db_query('INSERT INTO {biblio_zotero_collections} VALUES (:tid, :key)', array(':tid' => $term->tid, ':key' => $collection_key));
    return $term;
  }


  /**
   * Implementation of map function
   * The zotero items are all in  $result->current_item
   * */
  protected function map(FeedsSource $source, FeedsParserResult $result, $target_item = NULL) {
    // Disable biblio_index so search index doesn't get rebuilt on every node insertion.
    if ($biblio_index = variable_get('biblio_index', 0)) {
      variable_set('biblio_index', 0);
    }

    // Log the mapping succeses and failures to a tab-delimited file in the temp direcory.
    if (variable_get('biblio_zotero_enable_log', FALSE)) {
      drupal_set_message('Mapping sources', 'notice');
      $this->logMapping($source, $result);
    }

    // Do the mappings
    // parent::map($source, $result, $target_item); //parent::map IS OVERRIDDEN below in super_map
    $this->super_map($source, $result, $target_item);


    // map the remaining zotero fields which do not have mapping sources: tags, creators,
    $feed = node_load($target_item->feeds_item->feed_nid);
    $parser = feeds_importer($this->id)->parser; // $batch's fields are protected so we have to get them from the parser
    $itemType = $parser->getSourceElement($source, $result, 'itemType');
    $target_item->biblio_type = BiblioZotero::getZoteroTypeToBiblioType($itemType);

    // Skip saving for notes and attachments since they will be brought in as
    // children of their parent item: see FeedsProcessor::process().
    if ($itemType == 'note' || $itemType == 'attachment') {
      $target_item->feeds_item->skip = TRUE;
      return;
    }
    $collections_vocab = taxonomy_vocabulary_machine_name_load($this->config['collections_vocab']);
    $collection_keys = $parser->getSourceElement($source, $result, 'collection_keys');
    $collection_tids = array();
    // Reset collection terms so that every update we get the latest only.
    if (isset($this->config['collections_field']) && !empty($this->config['collections_field'])) {
      $target_item->{$this->config['collections_field']}[LANGUAGE_NONE] = array();

      foreach ($collection_keys as $collection_key) {
        $term = biblio_zotero_get_collection_term($collection_key);
        if (empty($term)) {
          $data = BiblioZotero::getCollection($collection_key, $source);
          $term = $this->createCollectionTerm($data->data->name, $collection_key, $data->data->parentCollection);
        }
        $target_item->{$this->config['collections_field']}[LANGUAGE_NONE][] = (array) $term;
        $collection_tids[] = $term->tid;
      }
    } else {
      drupal_set_message('No taxonomy set up for collections in Zotero Feed importer settings, collections won\'t be imported', 'warning', FALSE);
    }

    if ($collection_tids && isset($target_item->taxonomy['tags']) && !empty($target_item->taxonomy['tags'])) {
      $target_item->taxonomy['tags'][$collections_vocab->vid] = implode(",", $collection_tids);
    }

    // Check for custom fields that support longer field length
    if (field_info_field('field_biblio_long_title')) {
      $target_item->field_biblio_long_title[LANGUAGE_NONE][0]['value'] = $parser->getSourceElement($source, $result, 'long_title');
    }
    if (field_info_field('field_biblio_long_language') && isset($target_item->biblio_lang)) {
      $target_item->field_biblio_long_language[LANGUAGE_NONE][0]['value'] = $target_item->biblio_lang;
      $target_item->biblio_lang = '';
    }

    // map the tags
    /** @TODO use mappings w/ source and target callbacks for this * */
    if ($this->config['tags_field']) {
      $tags = $parser->getSourceElement($source, $result, 'tags');
      $tags = is_array($tags) ? $tags : array();
      $tagStrings = array();
      $terms = array();
      foreach ($tags as $t) {
        $term = taxonomy_get_term_by_name($t->tag, $this->config['tags_vocab']);
        if (!empty($term)) {
          $term = array_pop($term);
        } else {
          $vocab = taxonomy_vocabulary_machine_name_load($this->config['tags_vocab']);
          $term = new stdClass();
          $term->name = $t->tag;
          $term->vid = $vocab->vid;
          taxonomy_term_save($term);
        }
        $tagStrings[] = $term->name;
        $terms[] = (array) $term;
      }
      $target_item->{$this->config['tags_field']}[LANGUAGE_NONE] = $terms;
    }

    if ($tagStrings && isset($this->config['tags_vocab_id']) && !empty($this->config['tags_vocab_id'])) {
      $target_item->taxonomy['tags'][$this->config['tags_vocab_id']] = implode(",", $tagStrings);
    }

    // map the institution
    /** @TODO test using the biblio_contributors mapping target for this without overwriting the mapped values from the creators field. It should work * */
    $institution = $parser->getSourceElement($source, $result, 'institution');
    if (!empty($institution)) {
      $contributor = array(
        'name' => $institution,
        'auth_category' => 5, // 1= Primary, 2 = secondary, 3 = tertiary, 4 = Subsidiary, 5 = corporate
        'auth_type' => 5,);
      $target_item->biblio_contributors[] = $contributor;
    }

    // add the group
    if (module_exists('og')) {
      $target_item->group_audience = $feed->group_audience;
    }

    // try to set the author from the zotero username field
    $author_uid = null;
    $zot_user_name = $parser->getSourceElement($source, $result, 'entry_author_name');
    if (!empty($this->config['zotero_username_field_name'])) {
      $query = new EntityFieldQuery;
      $query
          ->entityCondition('entity_type', 'user')
          ->fieldCondition($this->config['zotero_username_field_name'], "value", $zot_user_name, '=', 0);
      $users = $query->execute();
      if ($users) {
        $author = array_shift($users['user']);
        $author_uid = $author->uid;
      }
    }

    // if there was no corresponding zotero user found among the drupal users, use the feed owner if config says to do so.
    if (empty($author_uid) && $this->config['use_feed_owner_as_author']) {
      $author_uid = $feed->uid;
    }

    if ($author_uid) {
      $target_item->uid = $author_uid;
    }
    // Restore setting of biblio_index variable
    if ($biblio_index) {
      variable_set('biblio_index', 1);
    }

    // Prevent a notice by Biblio if this property is not on the node.
    if (!isset($target_item->biblio_keywords)) {
      $target_item->biblio_keywords = NULL;
    }
  }

  /**
   * Execute mapping on an item.
   *
   * This method is lifted in its entirety from ancestor class FeedsProcessor::map() with one condition added which prevents calling
   * setTargetElement if the item type doesnt match the item type in the prefix of the the mapping source, e.g. 'book' from book:title
   * This is needed since it appears that if multiple sources are mapped to the same target then that target is overwritten even when
   * the source item does not contain data keyed to that source. For example, a zotero book type does not contain the key webpage:title so we
   * need to prevent the null value for webpage:title being applied to the target that we want written with data from book:title
   *
   * @TODO test if all this can be accomplished by simply overriding the setTargetElement function. Surely it can.
   */
  protected function super_map(FeedsSource $source, FeedsParserResult $result, $target_item = NULL) {

    // Static cache $targets as getMappingTargets() may be an expensive method.
    static $sources;
    if (!isset($sources[$this->id])) {
      $sources[$this->id] = feeds_importer($this->id)->parser->getMappingSources();
    }
    static $targets;
    if (!isset($targets[$this->id])) {
      $targets[$this->id] = $this->getMappingTargets();
    }
    $parser = feeds_importer($this->id)->parser;
    if (empty($target_item)) {
      $target_item = array();
    }

    // Many mappers add to existing fields rather than replacing them. Hence we
    // need to clear target elements of each item before mapping in case we are
    // mapping on a prepopulated item such as an existing node.
    foreach ($this->config['mappings'] as $mapping) {
      if (isset($targets[$this->id][$mapping['target']]['real_target'])) {
        unset($target_item->{$targets[$this->id][$mapping['target']]['real_target']});
      } elseif (isset($target_item->{$mapping['target']})) {
        unset($target_item->{$mapping['target']});
      }
    }

    /*
      This is where the actual mapping happens: For every mapping we envoke
      the parser's getSourceElement() method to retrieve the value of the source
      element and pass it to the processor's setTargetElement() to stick it
      on the right place of the target item.

      If the mapping specifies a callback method, use the callback instead of
      setTargetElement().
     */
    self::loadMappers();

    foreach ($this->config['mappings'] as $mapping) {
      // Retrieve source element's value from parser.
      if (isset($sources[$this->id][$mapping['source']]) &&
          is_array($sources[$this->id][$mapping['source']]) &&
          isset($sources[$this->id][$mapping['source']]['callback']) &&
          function_exists($sources[$this->id][$mapping['source']]['callback'])) {
        $callback = $sources[$this->id][$mapping['source']]['callback'];
        $value = $callback($source, $result, $mapping['source']);
      } else {
        $value = $parser->getSourceElement($source, $result, $mapping['source']);
      }

      // If we don't have a value, trying to assign it is pointless.
      if (!$value) {
        continue;
      }

      // Map the source element's value to the target.
      if (isset($targets[$this->id][$mapping['target']]) &&
          is_array($targets[$this->id][$mapping['target']]) &&
          isset($targets[$this->id][$mapping['target']]['callback']) &&
          function_exists($targets[$this->id][$mapping['target']]['callback'])) {
        $callback = $targets[$this->id][$mapping['target']]['callback'];
        $callback($source, $target_item, $mapping['target'], $value);
      }
      else {
        // START modifications to parent's FeedsProcessor::map
        $src_array = explode(":", $mapping['source']);
        $zotero_src_prefix = $src_array[0];
        $ok_to_set_target = sizeof($src_array) == 1 || $zotero_src_prefix == $result->current_item['itemType'];
        if ($ok_to_set_target) {
          $this->setTargetElement($source, $target_item, $mapping['target'], $value); // this is the original code for this block
        }
        else {
          watchdog('biblio_zotero', "Could not set target for source @source", array('@source' => $mapping['source']));
        }
        // END modifications
      }
    }
    return $target_item;
  }

  /**
   * Since Zotero has so many item-type/field combinations, write a tab-delimited report for each run of a zotero feed
   * that can be used to improve the mappings.
   * */
  function logMapping($source, $result) {
    $zot2bib = $this->getZot2BibMappings();
    // Log unmapped fields to watchdog
    $map_report = array();
    foreach ($result->current_item as $key => $val) {
      $dont_log = array('url', 'guid', 'published', 'updated', 'key', 'itemType', 'description', 'creatorSummary', 'year', 'tags', 'creators');
      if (in_array($key, $dont_log) || !in_array($key, array_keys(FeedsZoteroParser::getMappingSources()))) {
        continue;
      }
      $target = $zot2bib[$key];
      $val = empty($val) ? 'NO VALUE' : $val;
      $trunc_val = isset($val) && strlen($val) < 25 ? $val : substr($val, 0, 25) . "...";
      if (empty($target)) {
        $msg = t("Source '@key' with value '@val' was NOT MAPPED to any target", array('@key' => $key, '@val' => $trunc_val));
        $mapped = FALSE;
      } else {
        $msg = t("Source '@key' with value '@val' was mapped to target '@target'", array('@key' => $key, '@val' => $trunc_val, '@target' => $target));
        $mapped = TRUE;
      }

      if (isset($msg)) {
        /** @TODO write the map success/failures to a tab-delim file */
        $keybits = explode(":", $key);
        $it = $keybits[0];
        $fn = $keybits[1];
        $m = $mapped ? "mapped" : "unmapped";
        $map_report[$it][$fn] = !empty($target) ? $target : 'UNMAPPED';
        $tab_data = "$it	$fn	$trunc_val	$m";
        watchdog('FeedsZoteroProcessor', $msg, NULL, WATCHDOG_NOTICE, $link = NULL);
      }
      unset($msg);
    }
    foreach ($map_report as $it => $row) {
      foreach ($row as $fn => $m) {
        file_put_contents($source->reportFilePath, "$it\t$fn\t$m" . PHP_EOL, FILE_APPEND);
      }
    }
  }

  function getZot2BibMappings() {
    $z2b = &drupal_static(__FUNCTION__);
    if (!isset($z2b)) {
      $z2b = array();
      foreach ($this->config['mappings'] as $mapping) {
        $z2b[$mapping['source']] = $mapping['target'];
      }
    }
    return $z2b;
  }

}

/**
 * Helper function to return all fields of one type on one bundle.
 */
function biblio_zotero_fields_by_type_by_bundle($entity_type, $bundle, $type) {
  $taxonomy_fields = array();
  $fields = field_info_field_map();
  foreach ($fields as $field => $info) {
    if ($info['type'] == $type &&
        in_array($entity_type, array_keys($info['bundles'])) &&
        in_array($bundle, $info['bundles'][$entity_type])) {
      $taxonomy_fields[$field] = $field;
    }
  }
  return $taxonomy_fields;
}
