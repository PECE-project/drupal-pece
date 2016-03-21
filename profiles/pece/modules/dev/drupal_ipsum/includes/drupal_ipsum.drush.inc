<?php

/**
 * @file
 * Drupal Ipsum Drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function drupal_ipsum_drush_command() {
  return array(
    'drupal-ipsum-generate' => array(
      'description' => 'Generate Drupal Ipsum filler text.',
      'aliases' => array('dipsum'),
      'arguments' => array(
        'vocabulary' => 'Machine name of the vocabulary to use.',
        'length' => 'Length of the generated text.',
        'type' => 'Type of the generated text (word, sentence, paragraph)',
        'start' => 'What should the text start with (drupal, lorem, any)',
      ),
      'options' => array(
        'with-markup' => 'Include HTML markup in the generated text',
      ),
      'examples' => array(
        'example[1]' => 'drush dipsum drupal 4 word',
        'example[2]' => 'drush dipsum classic 1 paragraph drupal',
        'example[3]' => 'drush dipsum drupal 2 sentence any',
      ),
    ),
    'drupal-ipsum-vocabularies' => array(
      'description' => 'List available vocabularies',
      'aliases' => array('dispum-vocabs'),
    ),
  );
}

/**
 * Drush command.
 * Lists available vocabularies.
 *
 * @see drupal_ipsum_drush_command()
 */
function drush_drupal_ipsum_vocabularies() {
  $drupal_ipsum = Drupal_Ipsum::getInstance();
  $vocabularies = $drupal_ipsum->getVocabularies();
  print_r($vocabularies);
}

/**
 * Drush command.
 * Generate drupal ipsum filler text.
 *
 * @param string
 *   The $vocabulary machine_name.
 * @param int
 *   The amount of $type to generate.
 * @param string
 *   What we want to generate (words, sentences, paragraphs)
 * @param string
 *   Whether we want to $start with specific text
 *
 * @see drupal_ipsum_drush_command()
 */
function drush_drupal_ipsum_generate($vocabulary = NULL, $length = NULL, $type = NULL, $start = NULL) {
  // Convert $type argument to constant.
  if (isset($type)) {
    switch (drupal_strtolower($type)) {
      case 'word':
        $type = 0;
        break;
      case 'sentence':
        $type = 1;
        break;
      case 'paragraph':
        $type = 2;
        break;
      default:
        drush_die(dt('Please enter a valid "type" argument.'));
    }
  }

  // Convert $start argument to constant.
  if (isset($start)) {
    switch (drupal_strtolower($start)) {
      case 'any':
        $start = 0;
        break;
      case 'lorem':
        $start = 1;
        break;
      case 'drupal':
        $start = 2;
        break;
      default:
        drush_die(dt('Please enter a valid "start" argument.'));
    }
  }

  $text = drupal_ipsum_generate($vocabulary, $length, $type, $start, FALSE);
  drush_print(dt("\n{$text}\n"));
}

/**
 * Implements hook_drush_help().
 */
function drupal_ipsum_drush_help($section) {
  switch ($section) {
    case 'drush:drupal-ipsum-generate':
      return dt("Generate Drupal Ipsum filler text.");
    case 'drush:drupal-ipsum-vocabularies':
      return dt("List available vocabularies.");
  }
}