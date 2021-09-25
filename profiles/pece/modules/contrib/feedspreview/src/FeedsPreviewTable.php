<?php

/**
 * @file
 * Contains FeedsPreviewTable class.
 */

/**
 * Class for constructing a table with parsed Feeds results.
 */
class FeedsPreviewTable {

  /**
   * The feeds source that is being used.
   *
   * @var FeedsSource
   */
  private $feedsSource;

  /**
   * Render array for the base table.
   *
   * @var array
   */
  private $baseTable;

  /**
   * The item that is shown as first.
   *
   * Defaults to 0.
   *
   * @var int
   * @todo make this configurable.
   */
  private $activeItem = 0;

  /**
   * The maximum number of items to show.
   *
   * Defaults to 50.
   *
   * @var int
   * @todo make this configurable.
   */
  private $max = 50;

  /**
   * If parsed data that is not mapped should be shown.
   *
   * Defaults to TRUE.
   *
   * @var bool
   * @todo make this configurable.
   */
  private $showNotMappedSource = TRUE;

  /**
   * Minimum length for texts to collapse.
   *
   * Defaults to 100. Use 0 to not collapse at all.
   *
   * @var int
   * @todo make this configurable.
   */
  private $collapseText = 100;

  /**
   * FeedsPreviewTable object constructor.
   *
   * @param FeedsSource $feeds_source
   *   The feeds source.
   */
  public function __construct(FeedsSource $feeds_source) {
    $this->feedsSource = $feeds_source;
  }

  /**
   * Returns the ID of this FeedsPreviewTable.
   *
   * @return string
   *   The unique identifier of the feeds source.
   */
  public function id() {
    return $this->feedsSource->id;
  }

  /**
   * Returns a build array of the table to render, without values.
   *
   * @param bool $reset
   *   If the base table should be regenerated.
   *   Defaults to FALSE.
   *
   * @return array
   *   A build array in the format expected by drupal_render().
   */
  public function getBaseTable($reset = FALSE) {
    if (!$reset && !empty($this->baseTable)) {
      return $this->baseTable;
    }

    $header = array(
      array(
        'data' => t('Source'),
        'class' => array(
          'feeds-preview-table-column',
          'feeds-preview-table-source-column',
        ),
      ),
      array(
        'data' => t('Targets'),
        'class' => array(
          'feeds-preview-table-column',
          'feeds-preview-table-target-column',
        ),
      ),
      array(
        'data' => t('Value'),
        'class' => array(
          'feeds-preview-table-column',
          'feeds-preview-table-value-column',
        ),
      ),
    );

    $sources = $this->feedsSource->importer->parser->getMappingSources();
    $targets = $this->feedsSource->importer->processor->getMappingTargets();
    $mappings = $this->feedsSource->importer->processor->getMappings();

    // In case of the CSV parser, the source keys are converted to lowercase.
    // Loop through to the source list from the parser to fix the mapping
    // information.
    foreach ($this->feedsSource->importer->parser->getMappingSourceList() as $index => $source_key) {
      $mappings[$index]['source'] = $source_key;
    }

    $rows = array();

    // Create the base table.
    foreach ($mappings as $mapping) {
      // Find source.
      $source_name = $mapping['source'];
      // Some parsers do not define source options.
      $source = isset($sources[$source_name]['name']) ? $sources[$source_name]['name'] : $mapping['source'];

      // Find target.
      if (isset($targets[$mapping['target']])) {
        if (isset($targets[$mapping['target']]['name'])) {
          $target = check_plain($targets[$mapping['target']]['name']);
        }
        else {
          $target = check_plain($mapping['target']);
        }
        $mapped_css_class = 'feeds-preview-table-row-mapped';
      }
      elseif (strpos($mapping['target'], 'Temporary target ') === 0) {
        // Feeds Tamper temporary target.
        $target = check_plain($mapping['target']);
        $mapped_css_class = 'feeds-preview-table-row-mapped';
      }
      else {
        $target = '<em>' . t('Missing') . '</em>';
        $mapped_css_class = 'feeds-preview-table-row-not-mapped';
      }

      if (!isset($rows[$source_name])) {
        $rows[$source_name] = array(
          'data' => array(
            'source' => array(
              'data' => check_plain($source),
              'class' => 'feeds-preview-table-source-column',
            ),
            'target' => array(
              'data' => $target,
              'class' => 'feeds-preview-table-target-column',
            ),
            'value' => array(
              'data' => '<em>' . t('None') . '</em>',
              'class' => array('feeds-preview-table-value-column'),
            ),
          ),
          'class' => array(
            'feeds-preview-table-row',
            $mapped_css_class,
          ),
        );
      }
      else {
        $rows[$source_name]['data']['target']['data'] .= '; ' . $target;
      }
    }

    $this->baseTable = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#attributes' => array(
        'class' => array(
          'feeds-preview-table',
          'feeds-preview-table-' . $this->id(),
        ),
      ),
    );

    return $this->baseTable;
  }

  /**
   * Builds the preview table.
   *
   * @param FeedsParserResult $result
   *   The parser result.
   *
   * @return array
   *   A build array in the format expected by drupal_render().
   */
  public function build(FeedsParserResult $result) {
    if (empty($result->items)) {
      return array();
    }

    $build = array();

    $build['#attached'] = array(
      'css' => array(drupal_get_path('module', 'feedspreview') . '/css/feedspreview.css'),
      'js' => array(drupal_get_path('module', 'feedspreview') . '/js/feedspreview.js'),
    );
    $build['buttons'] = $this->buildButtons();
    $build['summary'] = $this->buildResultSummary($result->items);
    $build['items'] = $this->buildItems($result->items);

    $js_settings = array(
      'feedsPreview' => array(
        $this->id() => array(
          'activeItem' => 0,
        ),
      ),
    );
    drupal_add_js($js_settings, 'setting');

    return $build;
  }

  /**
   * Returns a build array for buttons next and previous.
   *
   * @return array
   *   A build array in the format expected by drupal_render().
   */
  public function buildButtons() {
    return array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'feeds-preview-controls',
        ),
      ),
      'previous' => array(
        '#type' => 'container',
        'button' => array(
          '#markup' => '<a href="#">' . t('Previous') . '</a>',
        ),
        '#attributes' => array(
          'class' => array(
            'feeds-preview-controls-previous',
          ),
          'id' => array(
            'feeds-preview-controls-previous-' . $this->id(),
          ),
        ),
      ),
      'next' => array(
        '#type' => 'container',
        'button' => array(
          '#markup' => '<a href="#">' . t('Next') . '</a>',
        ),
        '#attributes' => array(
          'class' => array(
            'feeds-preview-controls-next',
          ),
          'id' => array(
            'feeds-preview-controls-next-' . $this->id(),
          ),
        ),
      ),
    );
  }

  /**
   * Returns a build array for the record total.
   *
   * @param array $items
   *   The items to display.
   *
   * @return array
   *   A build array in the format expected by drupal_render().
   */
  public function buildResultSummary(array $items) {
    $total = count($items);
    if ($total > $this->max) {
      $total = t('!max (!total total)', array(
        '!max' => $this->max,
        '!total' => $total,
      ));
    }
    $vars = array(
      '!current' => '<span id="feeds-preview-result-summary-current-' . $this->id() . '" class="feeds-preview-result-summary-current">' . ($this->activeItem + 1) . '</span>',
      '!total' => '<span id="feeds-preview-result-summary-total-' . $this->id() . '" class="feeds-preview-result-summary-total">' . $total . '</span>',
    );

    return array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'feeds-preview-result-summary',
        ),
      ),
      'summary' => array(
        '#markup' => t('Record !current of !total', $vars),
      ),
    );
  }

  /**
   * Returns a build array for a list of items.
   *
   * @param array $items
   *   The items to display.
   *
   * @return array
   *   A build array in the format expected by drupal_render().
   */
  public function buildItems(array $items) {
    $build = array();
    $index = 0;
    foreach ($items as $item) {
      $build[$index] = $this->buildItem($item, $index);
      $index++;
      if (!empty($this->max) && $this->max <= $index) {
        break;
      }
    }
    return $build;
  }

  /**
   * Returns a build array for a single item.
   *
   * @param array $item
   *   The item to display.
   * @param int $index
   *   The number of the item in the list.
   *
   * @return array
   *   A build array in the format expected by drupal_render().
   */
  public function buildItem(array $item, $index) {
    $table = $this->getBaseTable();

    foreach ($item as $key => $value) {
      if (!isset($table['#rows'][$key])) {
        if (!$this->showNotMappedSource) {
          continue;
        }

        $table['#rows'][$key] = array(
          'data' => array(
            'source' => array(
              'data' => check_plain($key),
              'class' => 'feeds-preview-table-source-column',
            ),
            'target' => array(
              'data' => '<em>' . t('Not mapped') . '</em>',
              'class' => 'feeds-preview-table-target-column',
            ),
            'value' => array(
              'data' => '<em>' . t('None') . '</em>',
              'class' => array('feeds-preview-table-value-column'),
            ),
          ),
          'class' => array(
            'feeds-preview-table-row',
            'feeds-preview-table-row-not-mapped',
          ),
        );
      }
      if (!empty($value) || $value === 0 || $value === '0') {
        $table['#rows'][$key]['data']['value']['data'] = $this->outputValue($value);
      }
    }
    $table['#attributes']['id'] = 'feeds-preview-table-item-' . $this->id() . '-' . $index;
    if ($index == $this->activeItem) {
      $table['#attributes']['class'][] = 'active';
    }

    return $table;
  }

  /**
   * Prepares a value for display.
   *
   * @param mixed $value
   *   The value to display.
   *
   * @return string
   *   An HTML-formatted string, containing the value to display.
   */
  public function outputValue($value) {
    $output = '';

    if (is_array($value)) {
      if (count($value) == 1) {
        $value = reset($value);
      }
      else {
        foreach ($value as $key => $subvalue) {
          $value[$key] = $this->outputValue($subvalue);
        }
        $list = array(
          '#theme' => 'item_list',
          '#items' => $value,
        );
        $output = drupal_render($list);
      }
    }

    if (is_scalar($value)) {
      $output = check_plain($value);
      $output = '<pre>' . check_plain($value) . '</pre>';
      // Collapse texts that are long.
      if ($this->collapseText && strlen($value) > $this->collapseText) {
        $output = '<div class="feeds-preview-long-content collapsed">' . $output . '</div>';
      }
    }

    return $output;
  }

}
