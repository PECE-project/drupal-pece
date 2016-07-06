<?php

ini_set('max_execution_time', -1);

/**
 * @file
 * FeedsZoteroFetcher
 */

/**
 * Result of FeedsZoteroHTTPFetcher::fetch().
 * Overriding FeedsHTTPFetcher so we can import results of multiple HTTP requests
 * as required by Zotero's API limitations
 *
 */
class FeedsZoteroHTTPFetcherResult extends FeedsHTTPFetcherResult {

  protected $file_path;
  protected $timeout;
  protected $itemsPages = array('no_collection_items' => array());
  protected $collectionPages = array();
  protected $notes = array();
  protected $files = array();
  protected $childPages = array();

  /**
   * Constructor.
   */
  public function __construct($url = NULL) {
    parent::__construct($url);
  }

  /**
   *  Add one of the items pages retrieved from Zotero
   *  $pages - An array containing collection key and another array of pages (XML documents)
   *  in the following form
   *
   *  array('collection_key' => $key, 'page' => $pages)
   *
   *    $key can be set to NULL if pages are not associated with a collection
   *    $pages - An array of XML pages retrieved from Zotero
   */
  public function addItemPages($pages, $collection_key = NULL) {
    if ($collection_key) {
      $this->itemsPages[$collection_key] = isset($this->itemsPages[$collection_key]) ? array_merge($this->itemsPages[$collection_key], $pages) : $pages;
    } else {
      $this->itemsPages['no_collection_items'] = array_merge($this->itemsPages['no_collection_items'], $pages);
    }
  }

  public function getItemPages() {
    return $this->itemsPages;
  }

  /**
   * Return a simple array of all entry keys on Zotero XML page
   * Can be either a collection page, page of items, or children
   *
   * @pages - an array of XML Pages retrieved from Zotero
   *
   */
  public function getEntryKeys($pages, $exclude_types = array()) {
    $keys = array();
    foreach ($pages as $collectionsPage) {
      $simple_xml = simplexml_load_string($collectionsPage);
      if (is_object($simple_xml)) {
        $namespaces = $simple_xml->getNameSpaces(true);
        foreach ($simple_xml->entry as $entry) {
          $zapi = $entry->children($namespaces['zapi']);
          if (!in_array($zapi->itemType, $exclude_types)) {
            $key = (string) $zapi->key;
            $keys[$key] = $key;
          }
        }
      }
    }
    return $keys;
  }

  /**
   * Return a structured array with sub-collections nested underneath their parents
   */
  public function getCollectionHierarchy() {
    $collections = array();
    foreach ($this->collectionPages as $collectionsPage) {
      $simple_xml = simplexml_load_string($collectionsPage);
      if (is_object($simple_xml)) {
        $namespaces = $simple_xml->getNameSpaces(true);
        foreach ($simple_xml->entry as $entry) {
          $zapi = $entry->children($namespaces['zapi']);
          $key = (string) $zapi->key;
          $parent = $this->getCollectionParent($entry);
          $collections[$key] = array('key' => $key, 'title' => (string) $entry->title, 'parent' => $parent, 'children' => array());
        }
        //Sort collections into a hierarchical array matching their Zotero structure
        foreach ($collections as $collection) {
          $parent = $collection['parent'];
          if ($parent && isset($collections[$parent])) {
            //Put collection under its parent's entry
            //The - $collections[$collection['key']] - Syntax is important here because '$collection' is not updated by PHP
            $collections[$parent]['children'][$collection['key']] = $collections[$collection['key']];
            //Remove collection now that we've copied it under its parent
            unset($collections[$collection['key']]);
          }
        }
      }
    }
    return $collections;
  }

  /**
   *  Given a Simple XML Element of the collection entry, return the key of collection's parent
   */
  public function getCollectionParent(SimpleXMLElement $entry) {
    //Search for collection key in XML result
    $link = $entry->xpath("*[@rel='up']");
    if ($link) {
      $link = (string) $link[0]['href'];
      $matches = array();
      preg_match('#collections/(.*)#', $link, $matches);
      $collection_key = isset($matches[1]) ? $matches[1] : FALSE;
      return $collection_key;
    }
  }

  /**
   * Add XML for the collections pages retrieved from Zotero
   */
  public function addCollectionPages($page) {
    if (is_array($page)) {
      $this->collectionPages = array_merge($this->collectionPages, $page);
    } else {
      $this->collectionPages[] = $page;
    }
  }

  public function getCollectionPages() {
    return $this->collectionPages;
  }

  public function addChildPages($item_key, $pages) {
    $this->childPages[$item_key] = $pages;
  }

  public function getChildPages($item_key = FALSE) {
    if ($item_key !== FALSE) {
      return isset($this->childPages[$item_key]) ? $this->childPages[$item_key] : array();
    } else {
      return $this->childPages;
    }
  }

}

/**
 * Fetches data via HTTP.
 */
class FeedsZoteroFetcher extends FeedsHTTPFetcher {

  /**
   * Expose source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['zotero_type'] = array(
      '#type' => 'radios',
      '#title' => t('What type of Zotero library is this?'),
      '#options' => array('group' => 'Group', 'user' => 'User'),
      '#default_value' => isset($source_config['zotero_type']) ? $source_config['zotero_type'] : '',
      '#maxlength' => NULL,
      '#required' => TRUE,
    );
    $form['zotero_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Zotero ID'),
      '#description' => t('Enter the numeric id of your zotero user or group. To find your
            group id, navigate to your groups\'s settings page and the numeric part of the URL
            is you group id. Your userID is in
            <a href="https://www.zotero.org/settings/keys">Feeds/API section</a> of your zotero settings.'),
      '#default_value' => isset($source_config['zotero_id']) ? $source_config['zotero_id'] : '',
      '#maxlength' => NULL,
      '#required' => TRUE,
    );
    $form['fetch_collections'] = array(
      '#type' => 'checkbox',
      '#title' => t("Fetch collections"),
      '#description' => t("If selected a user or group's collections will be fetched instead of their library items"),
      '#default_value' => isset($source_config['fetch_collections']) ? $source_config['fetch_collections'] : 0,
    );
    $form['use_pubsubhubbub'] = array(
      '#type' => 'hidden',
      '#title' => t("Use Pubsubhubhub"),
      //  '#description' => t("If selected a user or group's collections will be fetched instead of their library items"),
      '#default_value' => isset($source_config['use_pubsubhubbub']) ? $source_config['use_pubsubhubbub'] : 0,
    );

    $form['collection_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Collection ID'),
      '#description' => t('Only applicable if Fetch Collections above is selected. If none is entered, all top level collections for the user or group will be retrieved. If you enter a collection id, only items from that collection will be fetched from Zotero. Collections are the "folders" in your Zotero library. To find the id of a collection, go to your library, click on a collection to see its content, and look at the page URL. The collection id is the last item in the path, after "collectionKey/".')
    );
    $form['api_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Zotero API key'),
      '#description' => t('If your group or user account is private, you will need to enter
            your api key to be allowed to access the library.  Your api key is in
            <a href="https://www.zotero.org/settings/keys">Feeds/API section</a> of your zotero settings.'),
      '#default_value' => isset($source_config['api_key']) ? $source_config['api_key'] : '',
      '#maxlength' => NULL,
    );
    $form['next_index'] = array(
      '#type' => 'hidden',
      '#title' => t('Next Index'),
      '#disabled' => TRUE,
      '#description' => t('The next index to be used as the start parameter for the next import.'),
      '#default_value' => isset($source_config['next_index']) ? $source_config['next_index'] : 0,
      '#maxlength' => NULL,
    );
    return $form;
  }

  /**
   * Override parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {
    // We need to construct a url that looks like this:
    // https://api.zotero.org/groups/98765/items
    // or this:
    // https://api.zotero.org/users/12345/items

    if (!is_numeric($values['zotero_id'])) {
      $form_key = 'feeds][' . get_class($this) . '][zotero_id';
      form_set_error($form_key, t('The zotero id must be numeric.'));
    }

    // TODO add option to fetch from zotero without json for use in non-biblio fields, i.e. the standard processor
    // TODO test the accessibility of the API call.
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    $defaults = parent::configDefaults();
    return $defaults;
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    return $form;
  }

  /**
   * Implements FeedsFetcher::fetch().
   * Overrides FeedsHTTPFetcher->fetch
   */
  public function fetch(FeedsSource $source) {
    $this->config = $source->getConfigFor($this);
    $config = $source->getConfigFor($this);
    $result = new FeedsZoteroHTTPFetcherResult($source);
    //Retrieve minimal information for edit node page
    if (arg(2) == 'edit') {
      $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 'start' => $config['next_index'], 'top' => TRUE));
      $result->addItemPages($pages);
      return $result;
    }
    if ($config['fetch_collections']) {
      $pages = $this->getCollections($source, $config['collection_key']);
      $result->addCollectionPages($pages);
      $collection_keys = $result->getEntryKeys($result->getCollectionPages());
      foreach ($collection_keys as $key) {
        $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'],
          'start' => $config['next_index'], 'source' => 'collection', 'source_key' => $key));
        $result->addItemPages($pages, $key);
      }
      //Get top-level items not in any collection
      $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 'start' => $config['next_index'], 'top' => TRUE));
    } else {
      $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 'start' => $config['next_index']));

    }

    $result->addCollectionPages($pages);
    $result->addItemPages($pages);
    //    file_put_contents('itemsPages', print_r($result->getItemPages(), TRUE));
    //Retrieve children for each item - Notes, Links, Files
    $child_pages = array();
    $pages = $result->getItemPages();
    foreach ($result->getItemPages() as $page) {
      $item_keys = $result->getEntryKeys($page, array('attachment', 'note'));
      foreach ($item_keys as $item_key) {
        $result->addChildPages($item_key, $this->getItemChildren($item_key));
      }
    }
    return $result;
  }

  /**
   *  Retrieve XML Pages from Zotero's API
   *
   *  @params - an associative array or parameters
   *    $account_type - either group or user
   *    $account_id - the id of the zotero account to retrieve from
   *    $source - Only set if you want to retrive from specific source such as retrieving all sub-collections or items from a collection
   *    $source_key - the key of the above target
   *    $target - the type of object to fetch, defaults to items
   *    $start - the index at which to start retrieving items
   *    $top - fetch only top level items
   *    $limit - the number of items to fetch
   *
   *    Returns a numbered array of pages from Zotero
   */
  public function fetchPages($params) {
    extract($params);
    $items_fetched = 0;
    if (!isset($limit)) {
      $limit = 0;
    }
    $no_limit = (!isset($limit) || $limit == 0);
    $items_pages = array();
    $index = isset($start) ? $start : 0;
    while ($items_fetched < $limit || $no_limit) {
      $last_index = $index;
      $url = $this->formatUrl($params);
      $page = $this->fetchURL($url);
      $pages[] = $page;
      $next_index = $this->getNextIndex($page);
      $params['start'] = $next_index;
      $items_fetched = $index - $last_index;
      if (!$next_index) {
        //No items left to fetch, exit loop
        break;
      }
    }
    return $pages;
  }

  public function getCollections(FeedsSource $source, $collection_key = NULL) {
    $config = $source->getConfigFor($this);
    $account_type = $config['zotero_type'] == 'group' ? 'groups' : 'users';
    $xml = '';
    $page = array();
    $top = $collection_key ? FALSE : TRUE;
    //TODO: Allow import from specific collection
    $pages = $this->fetchPages(array('account_type' => $account_type, 'account_id' => $config['zotero_id'],
      'target' => 'collections', 'start' => 0, 'source_key' => $collection_key));

    return $pages;
  }

  /**
   * Retrieve all children from a Zotero item
   */
  public function getItemChildren($item_key) {
    $config = $this->config;
    $account_type = $config['zotero_type'] == 'group' ? 'groups' : 'users';
    $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'source' => 'items', 'source_key' => $item_key, 'account_id' => $config['zotero_id'], 'target' => 'children'));
    return $pages;
  }

  /**
   *  Format a url for fetching items from zotero
   *
   *  @params - an associative array of parameters
   *    $account_type - either group or user
   *    $account_id - the id of the zotero account to retrieve from
   *    $source - if specified, will retrieve from a specific location - items, collections, etc
   *    $source_key - the key of source (item, collection, or search)
   *    $target - the type of object to fetch, defaults to items
   *    $start - the index at which to start retrieving items
   *    $top - fetch only top level items
   */
  public function formatUrl($params) {
    $this->validateUrlParams($params);
    extract($params);
    if (!isset($target)) {
      $target = 'items';
    }
    if (!isset($start) || !$start) {
      $start = 0;
    }
    if (isset($account_type) && $account_type == 'user') {
      $account_type = 'users';
    }
    if (isset($account_type) && $account_type == 'group') {
      $account_type = 'groups';
    }
    if (isset($source) && $source == 'collection') {
      $source = 'collections';
    }

    $url = "https://api.zotero.org/$account_type/$account_id";

    if (isset($source) && $source) {
      $url .= "/$source";
    }
    if (isset($source_key) && $source_key) {
      $url .= "/$source_key";
    }

    $url .= "/$target";

    if (isset($top) && $top) {
      $url .= "/top";
    }
    if (isset($children) && $children) {
      $url .= "/children";
    }
    $url .= '?start=' . $start;
    $url .= '&content=json';

    return $url;
  }

  public function validateUrlParams($params) {
    if ((isset($params['children']) && $params['children']) && (isset($params['top']) && $params['top'])) {
      throw new Exception("You cannot set both 'top' and 'children' in a Zotero API url");
    }
  }

  public function fetchURL($url) {
    feeds_include_library('http_request.inc', 'http_request');
    $result = http_request_get($url, NULL, NULL, NULL, $this->timeout);
    if (!in_array($result->code, array(200, 201, 202, 203, 204, 205, 206))) {
      throw new Exception(t('Download of @url failed with code !code. Error details: !details', array('@url' => $url, '!code' => $result->code, '!details' => $result->data)));
    }

    return $result->data;
  }

  /**
   *  Parses XML response from Zotero to return the numeric index for the next request
   */
  private function getNextIndex($xml) {
    $feed_simple_xml = simplexml_load_string($xml);

    if (is_object($feed_simple_xml)) {
      $next = $feed_simple_xml->xpath("*[@rel='next']");
      $first = $feed_simple_xml->xpath("*[@rel='first']");
      if (!empty($next)) {
        $next_href = (string) $next[0]['href'];
        $pattern = "/start=\d+/";
        preg_match($pattern, $next_href, $matches);
        $first_match_parts = explode("=", $matches[0]);
        $next_index = array_pop($first_match_parts);
        return $next_index;
      } else {
        return FALSE;
      }
    }
  }

}
