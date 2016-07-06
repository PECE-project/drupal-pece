<?php

class BiblioZotero {

  /**
   * Contributor types
   */
  const BIBLIO_AUTHOR = 1;
  const BIBLIO_SECONDARY_AUTHOR = 2;
  const BIBLIO_TERTIARY_AUTHOR = 3;
  const BIBLIO_SUBSIDIARY_AUTHOR = 4;
  const BIBLIO_CORPORATE_AUTHOR = 5;
  const BIBLIO_SERIES_EDITOR = 10;
  const BIBLIO_PERFORMERS = 11;
  const BIBLIO_SPONSOR = 12;
  const BIBLIO_TRANSLATOR = 13;
  const BIBLIO_EDITOR = 14;
  const BIBLIO_COUNSEL = 15;
  const BIBLIO_SERIES_DIRECTOR = 16;
  const BIBLIO_PRODUCER = 17;
  const BIBLIO_DEPARTMENT = 18;
  const BIBLIO_ISSUING_ORGANIZATION = 19;
  const BIBLIO_INTERNATIONAL_AUTHOR = 20;
  const BIBLIO_RECIPIENT = 21;
  const BIBLIO_ADVISOR = 22;

  /**
   * Document types
   */
  const BIBLIO_BOOK = 100;
  const BIBLIO_BOOK_CHAPTER = 101;
  const BIBLIO_JOURNAL_ARTICLE = 102;
  const BIBLIO_CONFERENCE_PAPER = 103;
  const BIBLIO_CONFERENCE_PROCEEDINGS = 104;
  const BIBLIO_NEWSPAPER_ARTICLE = 105;
  const BIBLIO_MAGAZINE_ARTICLE = 106;
  const BIBLIO_WEB_ARTICLE = 107;
  const BIBLIO_THESIS = 108;
  const BIBLIO_REPORT = 109;
  const BIBLIO_FILM = 110;
  const BIBLIO_BROADCAST = 111;
  const BIBLIO_ARTWORK = 112;
  const BIBLIO_SOFTWARE = 113;
  const BIBLIO_AUDIOVISUAL = 114;
  const BIBLIO_HEARING = 115;
  const BIBLIO_CASE = 116;
  const BIBLIO_BILL = 117;
  const BIBLIO_STATUTE = 118;
  const BIBLIO_PATENT = 119;
  const BIBLIO_PERSONAL = 120;
  const BIBLIO_MANUSCRIPT = 121;
  const BIBLIO_MAP = 122;
  const BIBLIO_CHART = 123;
  const BIBLIO_UNPUBLISHED = 124;
  const BIBLIO_DATABASE = 125;
  const BIBLIO_GOVERNMENT_REPORT = 126;
  const BIBLIO_CLASSICAL = 127;
  const BIBLIO_LEGAL_RULING = 128;
  const BIBLIO_MISCELLANEOUS = 129;
  const BIBLIO_MISCELLANEOUS_SECTION = 130;
  const BIBLIO_JOURNAL = 131;
  const BIBLIO_WEBSITE = 132;
  const BIBLIO_WEB_SERVICE = 133;
  const BIBLIO_WEB_PROJECT_PAGE = 134;
  const BIBLIO_PRESENTATION = 135;

  public static function getZoteroTypeToBiblioType($type) {
    $zoteroToBiblioType = array(
      // 35 zotero item types
      'bill' => self::BIBLIO_BILL,
      'book' => self::BIBLIO_BOOK,
      'bookSection' => self::BIBLIO_BOOK_CHAPTER,
      'tvBroadcast' => self::BIBLIO_BROADCAST,
      'radioBroadcast' => self::BIBLIO_BROADCAST,
      'case' => self::BIBLIO_CASE,
      'film' => self::BIBLIO_FILM,
      'hearing' => self::BIBLIO_HEARING,
      'journalArticle' => self::BIBLIO_JOURNAL_ARTICLE,
      'magazineArticle' => self::BIBLIO_MAGAZINE_ARTICLE,
      'newspaperArticle' => self::BIBLIO_NEWSPAPER_ARTICLE,
      'patent' => self::BIBLIO_PATENT,
      'computerProgram' => self::BIBLIO_SOFTWARE,
      'statute' => self::BIBLIO_STATUTE,
      'thesis' => self::BIBLIO_THESIS,
      'webpage' => self::BIBLIO_WEB_ARTICLE,
      'artwork' => self::BIBLIO_ARTWORK,
      'conferencePaper' => self::BIBLIO_CONFERENCE_PAPER,
      'manuscript' => self::BIBLIO_MANUSCRIPT,
      'map' => self::BIBLIO_MAP,
      'report' => self::BIBLIO_REPORT,
      'presentation' => self::BIBLIO_PRESENTATION,
      'audioRecording' => self::BIBLIO_AUDIOVISUAL,
      'videoRecording' => self::BIBLIO_AUDIOVISUAL,
      // below: zotero types not specifically supported by biblio:
      'blogPost' => self::BIBLIO_MISCELLANEOUS,
      'dictionaryEntry' => self::BIBLIO_MISCELLANEOUS,
      'document' => self::BIBLIO_MISCELLANEOUS,
      'email' => self::BIBLIO_MISCELLANEOUS,
      'encyclopediaArticle' => self::BIBLIO_MISCELLANEOUS,
      'forumPost' => self::BIBLIO_MISCELLANEOUS,
      'instantMessage' => self::BIBLIO_MISCELLANEOUS,
      'interview' => self::BIBLIO_MISCELLANEOUS,
      'letter' => self::BIBLIO_MISCELLANEOUS,
      'note' => self::BIBLIO_MISCELLANEOUS,
      'attachment' => self::BIBLIO_MISCELLANEOUS,
      'podcast' => self::BIBLIO_MISCELLANEOUS,
        /* biblio types with no corresponding item types in zotero:
          'zoteroUnknown' => self::BIBLIO_CHART,
          'zoteroUnknown' => self::BIBLIO_CLASSICAL,
          'zoteroUnknown' => self::BIBLIO_CONFERENCE_PROCEEDINGS,
          'zoteroUnknown' => self::BIBLIO_DATABASE,
          'zoteroUnknown' => self::BIBLIO_GOVERNMENT_REPORT,
          'zoteroUnknown' => self::BIBLIO_LEGAL_RULING,
          'zoteroUnknown' => self::BIBLIO_PERSONAL,
          'zoteroUnknown' => self::BIBLIO_UNPUBLISHED, */
    );
    return $zoteroToBiblioType[$type];
  }

  /**
   * @TODO send locale to zotero api
   * */
  static function getItemTypeStructure($refresh = FALSE) {
    $type_structure = &drupal_static(__FUNCTION__);
    if (!isset($type_structure)) {
      $cache = cache_get('biblio_zotero__item_type_field_data');
      if ($cache && !$refresh) {
        $type_structure = $cache->data;
      } else {
        $type_structure = array();
        $types = self::_getAllItemTypes();
        foreach ($types as $item_type) {
          $item_type->fields = self::_getItemTypeFields($item_type);
          $item_type->creators = self::_getItemTypeCreators($item_type);
          $type_structure[$item_type->itemType] = $item_type;
        }
        cache_set('biblio_zotero__item_type_field_data', $type_structure, 'cache');
      }
    }
    return $type_structure;
  }

  /**
   * @TODO send locale to zotero api
   * @TODO write a function to compare file-based sources with api-based itemType creators
   * */
  /*    static function getAllItemTypeCreators($refresh = FALSE ) {
    $type_creators = &drupal_static(__FUNCTION__);
    if (! isset ($type_creators) ) {
    $cache = cache_get('biblio_zotero__item_type_creator_data');
    if ( $cache && ! $refresh ) {
    $type_creators = $cache->data;
    }
    else {
    $type_creators = array();
    $types = self::_getAllItemTypes();
    foreach ( $types  as $item_type) {
    $type_creators[$item_type->itemType] = $item_type;
    }
    cache_set('biblio_zotero__item_type_creator_data', $type_creators, 'cache');
    }
    }
    return $type_creators;
    }
   */
  private static function _getAllItemTypes() {
    $url = "https://api.zotero.org/itemTypes";
    $json = file_get_contents($url);
    $data = json_decode($json);
    return $data;
  }

  private static function _getItemTypeFields($item_type) {
    $url = "https://api.zotero.org/itemTypeFields?itemType=$item_type->itemType";
    $json = file_get_contents($url);
    $data = json_decode($json);
    foreach ($data as $idx => $field) {
      $data[$field->field] = $field;
      unset($data[$idx]);
    }
    return $data;
  }

  private static function _getItemTypeCreators($item_type) {
    $url = "https://api.zotero.org/itemTypeCreatorTypes?itemType=$item_type->itemType";
    $json = file_get_contents($url);
    $data = json_decode($json);
    foreach ($data as $idx => $field) {
      $data[$field->creatorType] = $field;
      unset($data[$idx]);
    }
    return $data;
  }

  static function getCollection($collection_key, $source) {
    $type = $source->config['FeedsZoteroFetcher']['zotero_type'];
    $type = ($type == 'group') ? 'groups' : $type;
    $id = $source->config['FeedsZoteroFetcher']['zotero_id'];
    $url = "https://api.zotero.org/$type/$id/collections/$collection_key";
    $json = file_get_contents($url);
    $data = json_decode($json);
    return $data;
  }

}
