<?php

$plugin = array(
  'single' => TRUE,
  'top level' => TRUE,
  'title' => t('Timeline Essay Pane'),
  'description' => t('Timeline Essay'),
  'category' => t('PECE'),
  'render callback' => 'pece_timeline_essay_timeline_pane_render',
  'required context' => new ctools_context_required(t('Node'), 'node', array(
    'type' => 'pece_timeline_essay',
  )),
  'edit form' => 'pece_timeline_essay_timeline_pane_edit_form',
  'defaults' => array(
    'destination' => null,
  ),
);

/**
 * Configure Essay link pane.
 */
function pece_timeline_essay_timeline_pane_edit_form($form, &$form_state) {
  $conf = drupal_array_merge_deep(
    $form_state['plugin']['defaults'],
    $form_state['conf'],
    $form_state['values']
  );

  // Remove common unnecessary fields.
  unset($form['override_title']);
  unset($form['override_title_text']);
  unset($form['override_title_heading']);
  unset($form['override_title_markup']);

  return $form;
}

/**
 * Submit callback for Essay link pane edit form.
 */
function pece_timeline_essay_timeline_pane_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['destination'] = $form_state['values']['destination'];
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function pece_timeline_essay_timeline_pane_render($subtype, $conf, $args, $context) {

  // Prepare response block.
  $block = new stdClass();
  $node = $context->data;
  $TLEI_values = array();

  foreach (pece_timeline_essay_pane_get_items($node) as $index => $item) {
    $TLEI_values[$index]['uuid'] = $item->uuid->value();
    $TLEI_values[$index]['desc'] = $item->field_description->value();
    $TLEI_values[$index]['artifact'] = tlei_get_artifact_value($item->field_pece_timeline_artifact);
    $TLEI_values[$index]['start_date'] = $item->field_pece_start_end_date->value->value();
    $TLEI_values[$index]['end_date'] = $item->field_pece_start_end_date->value2->value();
    $TLEI_values[$index]['bg_color'] = $item->field_pece_timeline_color->rgb->value();
  }
//  dsm($TLEI_values);
  $timeline_settings = array(
    'description' => 'Teste',
  );
//  $block->content = theme('timeline_pane', $timeline_settings);

  $timeline_sample = <<<TIMELINE
    <!-- 1 -->
    <link title="timeline-styles" rel="stylesheet" href="https://cdn.knightlab.com/libs/timeline3/latest/css/timeline.css">

    <!-- 2 -->
    <script src="https://cdn.knightlab.com/libs/timeline3/latest/js/timeline.js"></script>

    <div id='timeline-embed' style="width: 100%; height: 600px"></div>

    <!-- 3 -->
    <script type="text/javascript">
        // The TL.Timeline constructor takes at least two arguments:
        // the id of the Timeline container (no '#'), and
        // the URL to your JSON data file or Google spreadsheet.
        // the id must refer to an element "above" this code,
        // and the element must have CSS styling to give it width and height
        // optionally, a third argument with configuration options can be passed.
        // See below for more about options.
        var additionalOptions = {
           // start_at_end: true,
           // default_bg_color: {r:0, g:0, b:0},
           // timenav_height: 250
        }
        
        var json = {
          "title": {
            "media": {
              "url": "//www.flickr.com/photos/tm_10001/2310475988/",
              "caption": "Whitney Houston performing on her My Love is Your Love Tour in Hamburg.",
              "credit": "flickr/<a href='http://www.flickr.com/photos/tm_10001/'>tm_10001</a>"
            },
            "text": {
              "headline": "Whitney Houston<br/> 1963 - 2012",
              "text": "<p>Houston's voice caught the imagination of the world propelling her to superstardom at an early age becoming one of the most awarded performers of our time. This is a look into the amazing heights she achieved and her personal struggles with substance abuse and a tumultuous marriage.</p>"
            }
          },
          "events": [
            {
              "media": {
                "url": "{{ static_url }}/img/examples/houston/family.jpg",
                "caption": "Houston's mother and Gospel singer, Cissy Houston (left) and cousin Dionne Warwick.",
                "credit": "Cissy Houston photo:<a href='http://www.flickr.com/photos/11447043@N00/418180903/'>Tom Marcello</a><br/><a href='http://commons.wikimedia.org/wiki/File%3ADionne_Warwick_television_special_1969.JPG'>Dionne Warwick: CBS Television via Wikimedia Commons</a>"
              },
              "start_date": {
                "month": "8",
                "day": "9",
                "year": "1963"
              },
              "text": {
                "headline": "A Musical Heritage",
                "text": "<p>Born in New Jersey on August 9th, 1963, Houston grew up surrounded by the music business. Her mother is gospel singer Cissy Houston and her cousins are Dee Dee and Dionne Warwick.</p>"
              }
            },
            {
              "media": {
                "url": "https://youtu.be/fSrO91XO1Ck",
                "caption": "",
                "credit": "<a href=\"http://unidiscmusic.com\">Unidisc Music</a>"
              },
              "start_date": {
                "year": "1978"
              },
              "text": {
                "headline": "First Recording",
                "text": "At the age of 15 Houston was featured on Michael Zager's song, Life's a Party."
              }
            },
          ]
        };


        timeline = new TL.Timeline('timeline-embed',
            json,
            additionalOptions);
    </script>

TIMELINE;
  $block->content = $timeline_sample;

  return $block;
}

function tlei_get_artifact_value($artifactWpr) {
  switch ($artifactWpr->type->value()) {
    case 'pece_artifact_image':
      return $artifactWpr->field_pece_media_image->value();
    case 'pece_artifact_website':
      return $artifactWpr->field_pece_website_url->value();
    default:
      return Null;
  }
}

function pece_timeline_essay_pane_get_items($node) {
  $nodeWpr = entity_metadata_wrapper('node', $node);
  return $nodeWpr->field_pece_timeline_essay_items->getIterator();
}

function pece_timeline_essay_pane_get_item_value($tlitems) {
  $tl_items_val = array();
  foreach ($tlitems as $delta => $item) {
    $tl_items_val[$delta] = array();
    foreach (_tl_essay_item_field() as $key => $field) {
      $tl_items_val[$delta][$key] = $item->$field;
//      switch ($key) {
//        case 'title':
//          $tl_items_val[$delta][$key] = $item->$field->value;
//        default:
//          $tl_items_val[$delta][$key] = $item->$field;
//      }
    }
  }
  dsm($tl_items_val);
}

function timeline_essay_item_field_map() {
  return array(
    'title' => 'title',
    'body' => 'field_description',
    'artifact' => 'field_pece_timeline_artifact',
    'background' => 'field_pece_timeline_color',
  );
}

/**
 * Field mapping helper to get a given field on Timeline Essay Item.
 */
function _tl_essay_item_field($key) {
  $field_map =  timeline_essay_item_field_map();
  return !(empty($key)) ? $field_map[$key] : $field_map;
}
/**
 * Field get the proper value of a given field on Timeline Essay Item.
 */
function _tl_essay_item_field_value($key) {
  $field_map = timeline_essay_item_field_map();
  if (empty($key))
    return '';
  switch ($key) {
    case 'title':
      return $field_map[$key];
    default:
      return $field_map[$key]->value();
  }
}
