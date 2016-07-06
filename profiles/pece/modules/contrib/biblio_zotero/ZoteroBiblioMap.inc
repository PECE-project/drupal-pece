<?php

/**
 * Zotero API Client
 */

/**
 * Zotero object with mappings to Biblio nodes.
 */
class ZoteroBiblioMap {

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

  public static function getBiblioToZoteroFields() {
    return ZoteroBiblioMap::map();
  }

  public static function getZoteroToBiblioFields() {
    return ZoteroBiblioMap::map($flip = TRUE);
  }

  /**
   * Returns a map biblio keys => zotero keys
   *
   * @param boolean $flip
   * 	set true to get zotero => biblio
   * @return array
   */
  private static function map($flip = false) {
    // @see notMapped() for properties I haven't mapped so far

    $biblioToZoteroFields = array_filter(array(
      'biblio_abst_e' => 'description',
      'biblio_abst_f' => '',
      'biblio_accession_number' => null,
      'biblio_access_date' => 'accessDate',
      'biblio_alternate_title' => null,
      'biblio_auth_address' => null,
      'biblio_call_number' => 'callNumber',
      'biblio_citekey' => null,
      'biblio_coins' => null,
      'biblio_contributors' => null, // biblio sends a $node->biblio_contributors which includes authors, editors, @see contributor types
      'biblio_corp_authors' => null,
      'biblio_custom1' => null,
      'biblio_custom2' => null,
      'biblio_custom3' => null,
      'biblio_custom4' => null,
      'biblio_custom5' => null,
      'biblio_custom6' => null,
      'biblio_custom7' => null,
      'biblio_date' => null,
      'biblio_doi' => 'DOI',
      'biblio_edition' => 'edition',
      'biblio_isbn' => 'ISBN',
      'biblio_issn' => 'ISSN',
      'biblio_issue' => 'issue',
      'biblio_keywords' => null, // was set in medeley
      'biblio_label' => 'label',
      'biblio_lang' => 'language',
      /* 'biblio_zotero_doc_id' => 'documentNumber', */
      'biblio_notes' => null, // was set in mendeley
      'biblio_number' => null,
      'biblio_number_of_volumes' => null,
      'biblio_original_publication' => null, // 'originalPublication',
      'biblio_other_author_affiliations' => null,
      'biblio_other_number' => null,
      'biblio_pages' => 'pages',
      'biblio_place_published' => 'place',
      'biblio_publisher' => 'publisher',
      'biblio_pubmed_id' => null, //'pmid',
      'biblio_refereed' => null,
      'biblio_remote_db_name' => null,
      'biblio_remote_db_provider' => null,
      'biblio_reprint_edition' => null,
      'biblio_research_notes' => null,
      'biblio_secondary_authors' => null,
      'biblio_secondary_title' => null,
      'biblio_section' => null,
      'biblio_short_title' => null,
      'biblio_subsidiary_authors' => null,
      'biblio_tertiary_authors' => null,
      'biblio_tertiary_title' => null,
      'biblio_translated_title' => null,
      'biblio_type' => 'type', // needs callback $this->typeToBiblio()
      'biblio_type_of_work' => null,
      'biblio_url' => 'url',
      'biblio_volume' => 'volume',
      'biblio_year' => 'date',
      'title' => 'title',
        //'taxonomy' => 'tags', // proprietary addition to add taxonomy terms to a node
    ));

    if ($flip) {
      $biblioToZoteroFields = array_flip($biblioToZoteroFields);
    }

    return $biblioToZoteroFields;
  }

  /**
   * Convenience method for @see ZoteroBiblioMap::biblioToZoteroType
   */
  public static function zoteroToBiblioType($zoteroType) {
    return self::biblioToZoteroType($zoteroType, true);
  }

  /**
   * Maps biblio publication types to zotero publication types.
   *
   * Not all types of biblio are supported by the zotero api
   *
   * @param mixed
   * 	biblio type id if flip is false, else Zotero type string
   * @return int
   * 	biblio/zotero type id/string
   */
  public static function biblioToZoteroType($type, $flip = false) {
    $biblioToZotero = array(
      // biblio types in the zotero api
      self::BIBLIO_BILL => 'bill',
      self::BIBLIO_BOOK => 'book',
      self::BIBLIO_BOOK_CHAPTER => 'bookSection',
      self::BIBLIO_BROADCAST => 'tvBroadcast',
      self::BIBLIO_CASE => 'case',
      self::BIBLIO_CONFERENCE_PROCEEDINGS => 'Conference Proceedings',
      self::BIBLIO_FILM => 'film',
      self::BIBLIO_HEARING => 'hearing',
      self::BIBLIO_JOURNAL_ARTICLE => 'journalArticle',
      self::BIBLIO_MAGAZINE_ARTICLE => 'magazineArticle',
      self::BIBLIO_NEWSPAPER_ARTICLE => 'newspaperArticle',
      self::BIBLIO_PATENT => 'patent',
      self::BIBLIO_SOFTWARE => 'computerProgram',
      self::BIBLIO_STATUTE => 'statute',
      self::BIBLIO_THESIS => 'thesis',
      self::BIBLIO_WEB_ARTICLE => 'webpage',
      self::BIBLIO_ARTWORK => 'artwork',
      self::BIBLIO_CONFERENCE_PAPER => 'conferencePaper',
      self::BIBLIO_MANUSCRIPT => 'manuscript',
      self::BIBLIO_MAP => 'map',
      self::BIBLIO_REPORT => 'report',
      // biblio types not yet in the zotero api:
      self::BIBLIO_AUDIOVISUAL => 'Generic',
      self::BIBLIO_CHART => 'Generic',
      self::BIBLIO_CLASSICAL => 'Generic',
      self::BIBLIO_DATABASE => 'Generic',
      self::BIBLIO_GOVERNMENT_REPORT => 'Generic',
      self::BIBLIO_LEGAL_RULING => 'Generic',
      self::BIBLIO_MISCELLANEOUS => 'Generic',
      self::BIBLIO_MISCELLANEOUS_SECTION => 'Generic',
      self::BIBLIO_PERSONAL => 'Generic',
      self::BIBLIO_UNPUBLISHED => 'Generic',
        // zotero types not supported by biblio:
        // self::??? => audioRecording		Audio Recording
        // self::??? => blogPost
        // self::??? => dictionaryEntry		Dictionary Entry
        // self::??? => document		Document
        // self::??? => email		E-mail
        // self::??? => encyclopediaArticle		Encyclopedia Article
        // self::??? => forumPost		Forum Post
        // self::??? => hearing		Hearing
        // self::??? => instantMessage		Instant Message
        // self::??? => interview		Interview
        // self::??? => journalArticle		Journal Article
        // self::??? => letter		Letter
        // self::??? => magazineArticle		Magazine Article
        // self::??? => note		Note
        // self::??? => podcast		Podcast
        // self::??? => presentation		Presentation
        // self::??? => radioBroadcast		Radio Broadcast
        // self::??? => videoRecording		Video Recording
    );

    if ($flip) {
      $biblioToZotero = array_flip($biblioToZotero);
    }

    if (isset($biblioToZotero[$type])) {
      return $biblioToZotero[$type];
    } else {
      return ($flip ? self::BIBLIO_MISCELLANEOUS : $biblioToZotero[self::BIBLIO_MISCELLANEOUS]);
    }
  }

  /**
   * list all biblio field names
   * 	FROM MySql Db:  DESCRIBE biblio_fields;
   * */
  public static function getAllBiblioFieldNames() {
    return array(
      'biblio_authors',
      'biblio_secondary_authors',
      'biblio_tertiary_authors',
      'biblio_subsidiary_authors',
      'biblio_corp_authors',
      'biblio_secondary_title',
      'biblio_tertiary_title',
      'biblio_accession_number',
      'biblio_isbn',
      'biblio_call_number',
      'biblio_other_number',
      'biblio_other_author_affiliations',
      'biblio_publisher',
      'biblio_place_published',
      'biblio_year',
      'biblio_edition',
      'biblio_volume',
      'biblio_number',
      'biblio_pages',
      'biblio_date',
      'biblio_lang',
      'biblio_abst_e',
      'biblio_abst_f',
      'biblio_keywords',
      'biblio_type_of_work',
      'biblio_url',
      'biblio_notes',
      'biblio_issue',
      'biblio_research_notes',
      'biblio_custom1',
      'biblio_custom2',
      'biblio_custom3',
      'biblio_custom4',
      'biblio_custom5',
      'biblio_custom6',
      'biblio_custom7',
      'biblio_number_of_volumes',
      'biblio_short_title',
      'biblio_alternate_title',
      'biblio_translated_title',
      'biblio_original_publication',
      'biblio_reprint_edition',
      'biblio_section',
      'biblio_citekey',
      'biblio_coins',
      'biblio_issn',
      'biblio_doi',
      'biblio_auth_address',
      'biblio_remote_db_name',
      'biblio_remote_db_provider',
      'biblio_label',
      'biblio_access_date',
      'biblio_refereed',
    );
  }

}
