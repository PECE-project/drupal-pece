# Mapping (Migrate from D7 to D10)
Created this document using STSInfrastructure as D7 source reference

## Example Old Content Type `example_old_content_type`
- Example New Entity Bundle `example_new_entity_bundle`
(Don't want to assume all migrations with node sources target a node entity)
### Example old field `example_old_field`
- Example new field `example_new_field`
- any notes on data transformation or anything else relevant


## About Page `pece_about_page`
- Basic Page `page`
- Just assuming this is where we want to migrate to
### Title `title`
- Title `title` on `node_field_data` (though I imagine this is pretty standard)
### Location `locations`
- TBD
### URL path settings `path`
- TBD
### Body `body`
- Body `body`


## Analytic (Question) `pece_analytic`
- Analytic (Question) `pece_analytic`
### Title `title`
- Title `title` on `node_field_data`
### URI	`field_pece_uri`
- Url alias
### URL path settings `path`
- TBD
### Location	`locations`
- Location 	`field_pece_geolocation`
### Tags	`field_pece_tags`
- Tags 	`field_analytic_tags` ‡
- this should probably just be field_tags, so that it can be re-used, rather than having the same field name all over the place
### Question Set	`field_pece_struct_analytics`
- Question Set 	`field_analytic_question_set`
### Fields missing from D7 source
- ARK Enabled 	`field_ark_enabled`


## Annotation `pece_annotation`
- Annotation `pece_annotation`
### Title	`title`
- Title `title` on `node_field_data`
### URI	`field_pece_uri`
- Url alias
### Body	`body`
- Body `body`
### Artifact	`field_pece_artifact`
### Analytic (Question)	`field_pece_analytic`
### License	`field_pece_license`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### Permissions	`field_permissions`



## Artifact - Audio `pece_artifact_audio`
- Artifact - Audio `pece_artifact_audio`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Audio	`field_pece_media_audio`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Format	`field_pece_file_format`
### Duration	`field_pece_media_duration`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's `location	field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	locations
### ARK Enabled	`field_ark_enabled`



## Artifact - Bundle `pece_artifact_bundle`
- Artifact - Bundle `pece_artifact_bundle`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Artifacts	`field_pece_artifacts`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`



## Artifact - Fieldnote `pece_artifact_fieldnote`
- Artifact - Field note `pece_artifact_fieldnote`
Is the space in the new label intentional?
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Text	`body`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Group audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`



## Artifact - Image `pece_artifact_image`
- Artifact - Image `pece_artifact_image`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Image	`field_pece_media_image`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Format	`field_pece_file_format`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`



## Artifact - PDF Document `pece_artifact_pdf`
- Artifact - PDF Document `pece_artifact_pdf`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### PDF Document	`field_pece_media_pdf`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Bibliography	`field_pece_bibliography`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`


## Artifact - Tabular data `pece_artifact_tabular`
- Artifact - Tabular data `artifact_tabular_data`
Was this change in machine name intentional?
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Tabular data Document	`field_pece_media_tabular`
### Attachments	`field_pece_media_tablr_attach`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`


## Artifact - Text `pece_artifact_text`
- Artifact - Text `pece_artifact_text`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Text	`body`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`


## Artifact - Video `pece_artifact_video`
- Artifact - Video `artifact_video`
Was this change in machine name intentional?
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Video	`field_pece_media_video`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Format	`field_pece_file_format`
### Duration	`field_pece_media_duration`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`


## Artifact - Website `pece_artifact_website`
- Artifact - Website `pece_artifact_website`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### URI	`field_pece_uri`
### Contributors	`field_pece_contributors`
### Critical Commentary	`field_pece_crit_commentary`
### Website URL	`field_pece_website_url`
### Source	`field_pece_source`
### Creator(s)	`field_pece_authors`
### Created Date	`field_pece_created`
### Language	`field_pece_language`
### Fieldsite	`field_pece_fieldsite`
### Use fieldsite's location	`field_pece_use_fieldsite_local`
### Bibliography	`field_pece_bibliography`
### Location	`field_pece_location`
### License	`field_pece_license`
### Permissions	`field_permissions`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### Tags	`field_pece_tags`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`



## Biblio `biblio`
- TBD
### Title	`title`
### Year of Publication	`biblio_year`
### Publication Type	`biblio_type`
### Other Biblio Fields (Fieldset)	`other_fields`
### Zotero attachments as links	`field_zotero_attachment_links`
### Authors (Fieldset)	`biblio_authors_field`
### Secondary Authors (Fieldset)	`biblio_secondary_authors_field`
### Tertiary Authors (Fieldset)	`biblio_tertiary_authors_field`
### Subsidiary Authors (Fieldset)	`biblio_subsidiary_authors_field`
### Corporate Authors (Fieldset)	`biblio_corp_authors_field`
### Body	`body`
### Secondary Title	`biblio_secondary_title`
### Tertiary Title	`biblio_tertiary_title`
### Volume	`biblio_volume`
### Issue	`biblio_issue`
### Section	`biblio_section`
### Edition	`biblio_edition`
### Number of Volumes	`biblio_number_of_volumes`
### Number	`biblio_number`
### Pagination	`biblio_pages`
### Date Published	`biblio_date`
### Publisher	`biblio_publisher`
### Place Published	`biblio_place_published`
### Type of Work	`biblio_type_of_work`
### Publication Language	`biblio_lang`
### Other Author Affiliations	`biblio_other_author_affiliations`
### ISSN Number	`biblio_issn`
### ISBN Number	`biblio_isbn`
### Accession Number	`biblio_accession_number`
### Call Number	`biblio_call_number`
### Other Numbers	`biblio_other_number`
### Keywords	`biblio_keywords`
### Abstract	`biblio_abst_e`
### French Abstract	`biblio_abst_f`
### Notes	`biblio_notes`
### URL	`biblio_url`
### DOI	`biblio_doi`
### Reseach Notes	`biblio_research_notes`
### Custom 1	`biblio_custom1`
### Custom 2	`biblio_custom2`
### Custom 3	`biblio_custom3`
### Custom 4	`biblio_custom4`
### Custom 5	`biblio_custom5`
### Custom 6	`biblio_custom6`
### Custom 7	`biblio_custom7`
### Short Title	`biblio_short_title`
### Translated Title	`biblio_translated_title`
### Alternate Title	`biblio_alternate_title`
### Original Publication	`biblio_original_publication`
### Reprint Edition	`biblio_reprint_edition`
### Citation Key	`biblio_citekey`
### COinS Data	`biblio_coins`
### Remote Database Name	`biblio_remote_db_name`
### Remote Database Provider	`biblio_remote_db_provider`
### Label	`biblio_label`
### Author Address	`biblio_auth_address`
### Access Date	`biblio_access_date`
### Refereed Designation	`biblio_refereed`
### Zotero canonical URL	`field_zotero_canonical_url`
### Zotero fetched-from URL	`field_zotero_fetch_url`
### Location	`locations`
### URL path settings	`path`
### Tags	`field_pece_tags`
### Collection	`field_pece_biblio_collection`


## Content Page `panopoly_page`
- TBD
### Title	`title`
### Primary Image	`field_featured_image`
### Categories	`field_featured_categories`
### Feature content	`field_featured_status`
### Body	`body`
### URL path settings	`path`
### Location	`locations`



## Fieldsite `pece_fieldsite`
- Fieldsite `pece_fieldsite`
### Title	`title`
### Description	`body`
### Researchers	`field_pece_researchers`
### Location	`field_pece_location`
### Location	`locations`
### URL path settings	`path`
### Project	`field_pece_project_ref`



## Group `pece_group`

This *content type* is going to migrate to a *vocabulary*, `groups`, so all fields here are moving from Content (`node__`) to to Taxonomy Term (`taxonomy_term__`).

### URL path settings	`path`
### Title	`title`
### Description	`body`
### Group	`group_group`
### Visibility	`group_access`
### Audience	`og_group_ref`
### Roles and permissions	`og_roles_permissions`
### Group content visibility	`group_content_access`
### Thumbnail image	`field_pece_media_image`
### Location	`locations`
### Project	`field_pece_project_ref`
### Substantive Logic	`field_pece_substantive_logic`


## Landing Page `panopoly_landing_page`
- TBD
### Title	`title`
### Location	`locations`
### URL path settings	`path`


## Memo `pece_memo`
- Memo `pece_memo`
### Title	`title`
### URI	`field_pece_uri`
### Body	`body`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### License	`field_pece_license`
### Tags	`field_pece_tags`
### Contributors	`field_pece_contributors`
### Permissions	`field_permissions`
### Location	`locations`
### URL path settings	`path`


## PECE Essay `pece_essay`
- PECE Essay (pece_essay)
### URI	`field_pece_uri`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### Contributors	`field_pece_contributors`
### Description	`body`
### Thumbnail	`field_thumbnail`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### License	`field_pece_license`
### Tags	`field_pece_tags`
### Permissions	`field_permissions`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`



## Photo Essay `pece_photo_essay`
- Photo Essay `pece_photo_essay`
### URI	`field_pece_uri`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### Contributors	`field_pece_contributors`
### Description	`body`
### Thumbnail	`field_thumbnail`
### items	`field_pece_photo_essay_items`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### License	`field_pece_license`
### Tags	`field_pece_tags`
### Permissions	`field_permissions`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`


## Project `pece_project`
- Project `pece_project`
### Title	`title`
### Contributors	`field_pece_contributors`
### Description	`body`
### URL path settings	`path`
### Location	`locations`
### URI	`field_pece_uri`
### Image/Banner	`field_pece_proj_img`
### Thumbnail	`field_basic_image_image`
### Institution	`field_pece_multiple_link`
### Funding Agency	`field_pece_funding_agency`
### Project Lead	`field_pece_proj_lead`
### Design Group	`field_pece_design_group`
### Interview Request	`field_basic_file_file`
### Consent Form	`field_pece_consent_form`
### Start and End Date	`field_pece_start_end_date`
### Groups	`field_pece_groups`
### Featured Essays	`field_pece_featured_essays`
### Structured Analytics	`field_pece_proj_struct_analytics`
### Substantive Logic	`field_pece_substantive_logic`
### Open Notes	`field_pece_proj_notes`
### Tags	`field_pece_tags`


## Slideshow Image `frontpage_image_slideshow`
- Slideshow Image `pece_slideshow_image`
### Slideshow	`title`
### Image	`field_pece_slideshow_image`
### Image link	`field_pece_slideshow_img_link`
### Location	`locations`
### URL path settings	`path`


## Substantive Logic `pece_sub_logic`
- Substantive Logic `pece_substantive_logic`
### Title	`title`
### Description	`body`
### URL path settings	`path`
### Location	`locations`
### URI	`field_pece_uri`
### Thumbnail	`field_basic_image_image`
### Contributors	`field_pece_contributors`
### Image Citation	`field_pece_sub_logic_cit_link`
### Tags	`field_pece_tags`


## Timeline Essay `pece_timeline_essay`
- Timeline Essay `pece_timeline_essay`
### URI	`field_pece_uri`
### Title	`title`
### Cite as part of...	`field_pece_project_ref`
### Contributors	`field_pece_contributors`
### Description	`body`
### Thumbnail	`field_thumbnail`
### Timeline Entries	`field_pece_timeline_essay_items`
### Groups audience	`og_group_ref`
### Group content visibility	`group_content_access`
### License	`field_pece_license`
### Tags	`field_pece_tags`
### Permissions	`field_permissions`
### URL path settings	`path`
### Location	`locations`
### ARK Enabled	`field_ark_enabled`


## Migration questions
- Assuming I am using CER, and I migrate "Group members" into the field on a Group term, will CER ensure that the Group being migrated is referenced from the "Groups joined" field on the user when the migration is run?
- When a node of a type that is allowed to use an access policy is migrated, does an access policy datapoint need to be created manually during the migration (see db table node__access_policy)? I don't expect they will be created automatically, since the original author is not the one saving them during the migration, which is required to apply the access policy.
- Lots of machine names have the "pece" prefix. We should standardize, and either remove it in many places, or add it in many places. Which will it be? Let's just let it be inconsistent.

## Process (draft)
- Install the upgraded version of the site
- bump the sql auto-incrementers `ddev mysql < alter.sql`
- import default content `ddev import-content-all`
- import the source database `ddev import-db --database=sts7 --file=backups/yourbackup.sql.gz`
- run the sql helpers: `ddev mysql sts7 < scripts/panel_mapper.sql` and `ddev mysql sts7 < scripts/token_parser.sql`
- rsync the files directory to wherever the migration will run (prevent timeout of video files moving during migration, and required for private files anyway) `rsync -av user@example.com:/var/www/html/sites/default/files/ web/sites/default/files`
- scrape/collect the essay pages (see scripts/commands.md)
- rebuild the cache `ddev drush cr`
- run the migration `ddev drush mim --tag='PECE v1'`
- bulk update url aliases (assuming that they were migrated in as pathauto-generated aliases)
