; Panopoly Search Makefile

api = 2
core = 7.x

; Search API and Facet API Modules

projects[facetapi][version] = 1.5
projects[facetapi][subdir] = contrib

projects[search_api][version] = 1.15
projects[search_api][subdir] = contrib

projects[search_api_solr][version] = 1.8
projects[search_api_solr][subdir] = contrib

projects[search_api_db][version] = 1.4
projects[search_api_db][subdir] = contrib
projects[search_api_db][patch][2428693] = https://www.drupal.org/files/issues/entity-type-indhold-doest-specify-a-type-for-the-nid-property-2428693-2.patch
projects[search_api_db][patch][2436341] = https://www.drupal.org/files/issues/2436341-search_api_db-updb-1.patch
projects[search_api_db][patch][2343371] = https://www.drupal.org/files/issues/2343371-search_api_db-update-table-8.patch

; Solr PHP Client Library

libraries[SolrPhpClient][download][type] = get
libraries[SolrPhpClient][download][url] = http://solr-php-client.googlecode.com/files/SolrPhpClient.r60.2011-05-04.zip
