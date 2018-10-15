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
  $timeline_events = tlei_get_timeline_items($node);
  $TLEvents = json_encode($timeline_events);

  $timeline_sample = <<<TIMELINE
    <!-- 1 -->
    <link title="timeline-styles" rel="stylesheet" href="https://cdn.knightlab.com/libs/timeline3/latest/css/timeline.css">

    <!-- 2 -->
    <script src="https://cdn.knightlab.com/libs/timeline3/latest/js/timeline.js"></script>

    <div id='timeline-embed' style="width: 100%; height: 600px"></div>

    <!-- 3 -->
    <script type="text/javascript">
        var additionalOptions = {
           // start_at_end: true,
           // default_bg_color: {r:0, g:0, b:0},
           // timenav_height: 250
        }
        
        var timelineContent = {
            "events" : $TLEvents
        }
        
        var sampleJSON = {
          "title": {
            "media": {
              "url": "//www.flickr.com/photos/tm_10001/2310475988/",
              "caption": "Whitney Houston performing on her My Love is Your Love Tour in Hamburg.",
              "credit": "flickr/<a href='http://www.flickr.com/photos/tm_10001/'>tm_10001</a>"
            },
            "text": {
              "headline": "Whitney Houston<br/> 1963 - 2012",
              "text": "<p>Houston's voice caught the imagination of the world propelling her to superstardom at an early age becoming one of the most awarded performers of our time. This is a look into the amazing heights she achieved and her personal struggles with substance abuse and a tumultuous marriage.</p>"
            },
            "background": {
                "color": 'transparent'
            },
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

        timeline = new TL.Timeline('timeline-embed', timelineContent, additionalOptions);
    </script>

TIMELINE;

  $block->content = $timeline_sample;
//  $block->content = theme('timelinejs', array('timeline' => $timeline_sample));
  return $block;
}

/**
 * Build Timeline Items slide structure for TimelineJS plugin.
 *
 * @param $node
 * @return mixed
 */
function tlei_get_timeline_items($node) {
  $tlei_slides = array();
  foreach (pece_timeline_essay_pane_get_items($node) as $index => $item) {
    $tlei_slides[$index]['unique_id'] = $item->uuid->value();
    $tlei_slides[$index]['text'] = _tlei_format_text($item->field_description->value());
    $tlei_slides[$index]['media'] = _tlei_format_media(tlei_get_artifact_value($item->field_pece_timeline_artifact));
    $tlei_slides[$index]['start_date'] = _tlei_format_date($item->field_pece_start_end_date->value->value());
    $tlei_slides[$index]['end_date'] = _tlei_format_date($item->field_pece_start_end_date->value2->value());
    $tlei_slides[$index]['background'] = _tlei_format_bg_color($item->field_pece_timeline_color->rgb->value());
  }
  return $tlei_slides;
}

function tlei_get_artifact_value($artifactWpr) {
  switch ($artifactWpr->type->value()) {
    case 'pece_artifact_audio':
      return $artifactWpr->field_pece_media_audio->value();
    case 'pece_artifact_image':
      return $artifactWpr->field_pece_media_image->value();
    case 'pece_artifact_video':
      return $artifactWpr->field_pece_media_video->value();
    case 'pece_artifact_website':
      return $artifactWpr->field_pece_website_url->value();
    case 'pece_artifact_pdf':
      return $artifactWpr->field_pece_media_pdf->value();
    default:
      dsm($artifactWpr->value());
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

/**
 *
 * @return array
 */
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

/**
 * Format a given date to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_date($timestamp) {
  $default = array(
    'year' => date('Y', $timestamp),
    'month' => date('m', $timestamp),
    'day' => date('d', $timestamp),
  );
  return $default;
}

/**
 * Format a given text to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_text($raw_data) {
  $default = array(
    'text' => $raw_data
  );
  return $default;
}

/**
 * Format a given media to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_media($media_array) {
  $file_path = (!empty($media_array['uri'])) ? file_create_url($media_array['uri']) : '';
  $default = array(
    'url'=> $file_path,
    'caption' => $media_array['title'],
    'credit' => 'SAMPLE CREDIT',
  );
  return $default;
}

/**
 * Format a given background color to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_bg_color($bg_array) {
  $default = array(
    'color'=> $bg_array,
  );
  return (empty($bg_array)) ? $default['color'] = 'transparent' : $default;
}