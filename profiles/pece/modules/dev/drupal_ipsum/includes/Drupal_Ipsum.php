<?php
/**
 * @file
 * Drupal Ipsum text generation class.
 */

/**
 * General-purpose lorem ipsum filler text generation class.
 */
class Drupal_Ipsum {

  /**
   * The Active text generation vocabulary.
   *
   * @var array
   */
  protected $_vocabulary = 'drupal';

  /**
   * Pre-packaged text-generation vocabularies.
   *
   * @var array
   */
  protected $_vocabularies = array(
    'drupal' => array(
      'title' => 'Drupal Ipsum',
      'words' => array(
        'drupal',
        'hook',
        'module',
        'theme',
        'alter',
        'node',
        'entity',
        'comment',
        'user',
        'taxonomy',
        'term',
        'vocabulary',
        'content',
        'permission',
        'hack',
        'core',
        'contrib',
        'template',
        'menu',
        'profile',
        'behaviors',
        'ahah',
        'ajax',
        'javascript',
        'css',
        'html',
        'markup',
        'form',
        'api',
        'FAPI',
        'install',
        'uninstall',
        'enable',
        'disable',
        'block',
        'help',
        'documentation',
        'RTFM',
        'article',
        'webform',
        'captcha',
        'views',
        'panels',
        'context',
        'ctools',
        'zen',
        'cck',
        'features',
        'cron',
        'locale',
        'i18n',
        'community',
        'server',
        'git',
        'commit',
        'push',
        'pull',
        'diff',
        'issue',
        'project',
        'role',
        'field',
        'cache',
        'session',
        'semaphore',
        'bug',
        'major',
        'minor',
        'critical',
        'meta',
        'profile',
        'color',
        'filter',
        'backup',
        'migrate',
        'actions',
        'rules',
        'plugin',
        'book',
        'contact',
        'dashboard',
        'workbench',
        'trigger',
        'simpletest',
        'devel',
        'generate',
        'flag',
        'bundle',
        'token',
        'variable',
        'wysiwyg',
        'jquery',
        'html5',
        'css3',
        'scheduler',
        'date',
        'calendar',
        'overlay',
        'revision',
        'access',
        'registry',
        'router',
        'link',
        'alias',
        'database',
        'query',
        'responsive',
        'mobile',
        'xhtml',
      ),
    ),
    'classic' => array(
      'title' => 'Classic Lorem Ipsum',
      'words' => array(
        'lorem',
        'ipsum',
        'dolor',
        'sit',
        'amet',
        'consectetur',
        'adipiscing',
        'elit',
        'maecenas',
        'libero',
        'vehicula',
        'eu',
        'sagittis',
        'vitae',
        'convallis',
        'at',
        'purus',
        'suspendisse',
        'quam',
        'nisl',
        'malesuada',
        'ligula',
        'donec',
        'pharetra',
        'urna',
        'sed',
        'pellentesque',
        'varius',
        'mollis',
        'facilisis',
        'consequat',
        'egestas',
        'venenatis',
        'tempus',
        'lacus',
        'eros',
        'vestibulum',
        'cursus',
        'auctor',
        'tempor',
        'dapibus',
        'ut',
        'in',
        'sapien',
        'volutpat',
        'ultricies',
        'eget',
        'duis',
        'et',
        'faucibus',
        'risus',
        'mauris',
        'a',
        'est',
        'metus',
        'feugiat',
        'luctus',
        'id',
        'felis',
        'ante',
        'primis',
        'orci',
        'ultrices',
        'posuere',
        'cubilia',
        'curae',
        'curabitur',
        'augue',
        'nunc',
        'eleifend',
        'iaculis',
        'class',
        'aptent',
        'taciti',
        'sociosqu',
        'ad',
        'litora',
        'torquent',
        'per',
        'conubia',
        'nostra',
        'inceptos',
        'himenaeos',
        'hac',
        'habitasse',
        'platea',
        'dictumst',
        'praesent',
        'bibendum',
        'pulvinar',
        'diam',
        'non',
        'sem',
        'semper',
        'lectus',
        'fringilla',
        'nisi',
        'arcu',
        'nec',
        'fermentum',
        'velit',
        'massa',
        'etiam',
        'tincidunt',
        'leo',
        'blandit',
        'nulla',
        'laoreet',
        'vel',
        'mi',
        'integer',
        'hendrerit',
        'lacinia',
        'proin',
        'porta',
        'phasellus',
        'pretium',
        'aliquam',
        'justo',
        'interdum',
        'quis',
        'dictum',
        'tortor',
        'turpis',
        'neque',
        'commodo',
        'ac',
        'rutrum',
        'rhoncus',
        'magna',
        'ullamcorper',
        'lobortis',
        'tristique',
        'erat',
        'imperdiet',
        'nam',
        'nullam',
        'nibh',
        'accumsan',
        'morbi',
        'condimentum',
        'placerat',
        'odio',
        'enim',
        'euismod',
        'sodales',
        'dui',
        'ornare',
        'porttitor',
        'vulputate',
        'scelerisque',
        'viverra',
        'mattis',
        'quisque',
        'dignissim',
        'tellus',
        'cum',
        'sociis',
        'natoque',
        'penatibus',
        'magnis',
        'dis',
        'parturient',
        'montes',
        'nascetur',
        'ridiculus',
        'mus',
        'aenean',
        'vivamus',
        'facilisi',
        'congue',
        'elementum',
        'fusce',
        'suscipit',
        'gravida',
        'sollicitudin',
        'aliquet',
        'potenti',
        'molestie',
        'cras',
        'orem',
        'habitant',
        'senectus',
        'netus',
        'fames',
      ),
    ),
  );

  /**
   * Sentence length (words).
   *
   * @var array
   */
  protected $_sentenceLength = array(6, 20);

  /**
   * Paragraph length (sentences).
   *
   * @var array
   */
  protected $_paragraphLength = array(6, 10);

  /**
   * Singleton implementation.
   *
   * @var Drupal_Ipsum
   */
  protected static $_instance;

  /**
   * Singleton implementation.
   *
   * @see self::getInstance()
   */
  protected function __construct() {
    foreach (module_implements('drupal_ipsum_vocabularies') as $module) {
      foreach (module_invoke($module, 'drupal_ipsum_vocabularies') as $machine_name => $definition) {
        $this->_vocabularies[$machine_name] = $definition;
      }
    }
  }

  /**
   * Returns an initialized Drupal Ipsum class.
   */
  public static function getInstance() {
    if (!self::$_instance instanceof self) {
      self::$_instance = new self();
    }

    return self::$_instance;
  }

  ### Getters & Setters ###

  /**
   * Return available vocabularies.
   *
   * @return array
   *   An array who's keys are the vocabulary machine names and who's values
   *   are the vocabulary titles.
   */
  public function getVocabularies() {
    static $vocabularies;

    if (!isset($vocabularies)) {
      foreach ($this->_vocabularies as $machine_name => $definition) {
        $vocabularies[$machine_name] = $definition['title'];
      }
    }

    return $vocabularies;
  }

  /**
   * Return the active vocabulary.
   *
   * @return string
   *   The name of the active vocabulary.
   */
  public function getVocabulary() {
    return $this->_vocabulary;
  }

  /**
   * Set active vocabulary.
   *
   * @param string
   *   The vocabulary machine name.
   * @throws Drupal_Ipsum_Vocabulary_Exception
   *   If the vocabulary doesn't exist.
   */
  public function setVocabulary($vocabulary) {
    if (in_array($vocabulary, array_keys($this->_vocabularies))) {
      $this->_vocabulary = $vocabulary;
    }
    else {
      throw new Drupal_Ipsum_Vocabulary_Exception('Trying to set inexistent vocabulary: ' . $vocabulary);
    }
  }

  /**
   * Set sentence length.
   *
   * @param int
   *   The minimum sentence length, in words.
   * @param int
   *   The maximum sentence length, in words.
   */
  public function setSentenceLength($min, $max) {
    $this->_sentenceLength = array($min, $max);
  }

  /**
   * Get sentence length.
   *
   * @return array
   *   An array who's first value is the minimum length and second value is
   *   the maximum word length of generated sentences.
   */
  public function getSentenceLength() {
    return $this->_sentenceLength;
  }

  /**
   * Set paragraph length.
   *
   * @param int
   *   The minimum paragraph length, in sentences.
   * @param int
   *   The maximum paragraph length, in sentences.
   */
  public function setParagraphLength($min, $max) {
    $this->_paragraphLength = array($min, $max);
  }

  /**
   * Get paragraph length.
   *
   * @return array
   *   An array who's first value is the minimum length and second value is
   *   the maximum sentence length of generated paragraphs.
   */
  public function getParagraphLength() {
    return $this->_paragraphLength;
  }

  ### Main functionality ###

  /**
   * Return a given number of words.
   *
   * @param int
   *   The $number of words.
   * @param string
   *   Optionally, specify a word to start with.
   *
   * @return string
   *   The given number of words.
   */
  public function words($number, $startsWith = NULL) {
    $return = array();
    $lim = count($this->_vocabularies[$this->_vocabulary]['words']) - 1;

    if (isset($startsWith)) {
      $explode = explode(' ', $startsWith);
      $starts_length = count($explode);

      // Make sure we don't exceed the given number of words, even if
      // our "starts with" text is longer.
      if ($starts_length > $number) {
        while (count($explode) > $number) {
          array_pop($explode);
        }

        $starts_length = count($explode);
      }

      $number -= $starts_length;
      $return = $explode;

      if ($number <= 0) {
        return implode(' ', $return);
      }
    }

    for ($i = 0; $i < $number; ++$i) {
      $new_word = $this->_vocabularies[$this->_vocabulary]['words'][mt_rand(0, $lim)];
      // Prevent duplicate consecutive words.
      $previous_word = $i > 0 ? $return[$i - 1] : NULL;

      if ($new_word !== $previous_word) {
        $return[] = $new_word;
      }
      else {
        // Force an extra iteration.
        --$i;
      }
    }

    if (isset($return[0])) {
      $return[0] = ucwords($return[0]);
    }

    return implode(' ', $return);
  }

  /**
   * Return a given number of sentences.
   *
   * @param int
   *   The $number of sentences.
   * @param string
   *   Optionally, specify a word to start with.
   *
   * @return string
   *   The given number of sentences.
   */
  public function sentences($number, $startsWith = NULL) {
    $return = '';
    $start = 0;

    if (isset($startsWith)) {
      $return .= "{$startsWith} ";
      $start = 1;
      $wordsPerSentence = mt_rand($this->_sentenceLength[0], $this->_sentenceLength[1]);
      $explode = explode(' ', $startsWith);
      $starts_length = count($explode);
      $wordsPerSentence -= $starts_length;
      $return .= strtolower($this->words($wordsPerSentence) . '. ');
    }

    for ($i = $start; $i < $number; ++$i) {
      $wordsPerSentence = mt_rand($this->_sentenceLength[0], $this->_sentenceLength[1]);
      $return .= $this->words($wordsPerSentence) . '. ';
    }

    return trim($return);
  }

  /**
   * Return a given number paragraphs.
   *
   * @param int
   *   The $number of paragraphs.
   * @param string
   *   Optionally, specify a word to start with.
   * @param boolean
   *   Whether to wrap the paragraphs in <p> tags.
   *
   * @return string
   *   The given number of paragraphs.
   */
  public function paragraphs($number, $startsWith = NULL, $html = TRUE) {
    $return = '';
    $start = 0;

    if (isset($startsWith)) {
      if ($html) {
        $return .= '<p>';
      }

      $return .= "{$startsWith} ";
      $start = 1;
      $wordsPerSentence = mt_rand($this->_sentenceLength[0], $this->_sentenceLength[1]);
      $explode = explode(' ', $startsWith);
      $starts_length = count($explode);
      $wordsPerSentence -= $starts_length;
      $return .= strtolower($this->words($wordsPerSentence) . '. ');
      $sentencesPerParagraph = mt_rand($this->_paragraphLength[0], $this->_paragraphLength[1]);
      // We already have our first sentence.
      --$sentencesPerParagraph;
      $return .= $this->sentences($sentencesPerParagraph);

      if ($html) {
        $return .= '</p>';
      }
    }

    for ($i = $start; $i < $number; ++$i) {
      $sentencesPerParagraph = mt_rand($this->_paragraphLength[0], $this->_paragraphLength[1]);

      if ($html) {
        $return .= '<p>';
      }

      $return .= $this->sentences($sentencesPerParagraph);

      if ($html) {
        $return .= '</p>';
      }
    }

    return $return;
  }

}

/**
 * Drupal Ipsum "vocabulary not found" exception.
 */
class Drupal_Ipsum_Vocabulary_Exception extends Exception {

}