###############
PECE Data Model
###############

**User Roles**

* Researcher:
  Access to restricted data

* Contributor:
  Access to group contributed data

* Anonymous:
  Public access data

**Observation:** Standard Drupal node fields (date, revision number, node id, etc.) are not described below.

Data Types
----------

List of data types, their fields (with machine names), and their relations.
References to other data types within a particular type are marked with italics.

**Projects**

* URI (field_pece_uri)

* Title (title)

* Description (body)

* Institution (field_basic_image_image)

* *Researchers* (field_pece_researchers)

* *Contributors* (field_pece_contributors)

* *Fieldsites* (pece_fieldsites)

* *Substantive Logics* (field_pece_substantive_logic)

* Funding Agency (field_pece_funding_agency)

* Interview Request Form (field_basic_file_file)

* Consent Form (field_pece_consent_form)

* Start and End Date (field_pece_start_end_date)

* Tags (field_pece_tags)


**Groups**

* URI (field_pece_uri)

* Title (title)

* Description (body)

* Group Settings (group_group)

    * Group Visibility (group_access)

    * Group Audience (og_group_ref)

    * Group Content visibility (group_content_accessList)

    * Roles and Permissions (og_roles_permissions)

    * Thumbnail Image (field_pece_media_image)

* Location (locations)

* Group Email

* Members

    * *Researchers* (field_pece_researchers)

    * *Contributors* (field_pece_contributors)

* *Citations*

* *Memos*

* *Field Diaries*


**Fieldsite**

* URI (field_pece_uri)

* Title (title)

* Description (body)

* *Researchers* (field_pece_researchers)

* Location (locations)

* *Project* (field_pece_project_ref)


**Design and Substantive Logics** (pece_design_logics and pece_substantive_logics)

* URI (field_pece_uri)

* Title (title)

* *Researchers* (field_pece_researchers)

* Description (body)

* Image (field_basic_image_image)

* Image Citation (field_pece_sub_logic_cit_link)

* *Authors* (field_pece_authors)

* *Researchers* (field_pece_researchers)

* *Contributors* (field_pece_contributors)

* Type (Design or Substantive)

* Tags (field_pece_tags)


Artifacts
---------

**Fieldnote**

* URI (field_pece_uri)

* Authors (field_pece_authors)

* Contributor (if different from authors) (field_pece_contributors)

* Text (body)

* Tags (field_pece_tags)

* Permissions (field_permissions)


**Annotations**

* URI (field_pece_uri)

* Text (body)

* *Artifact* (field_pece_artifact)

* *Analytic* (field_pece_analytic)

* License (field_pece_license)

* Tags (field_pece_tags)

* Permissions (field_permissions)


**Text**

* URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Citation

* Group Audience (og_group_ref)


**PDF Document**

* URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Citation

* PDF Document (field_pece_media_pdf)

* Group Audience (og_group_ref)


**Image**

* URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Citation

* Format (field_pece_file_format)

* Image File (field_pece_media_image)

* Location (if different from fieldsite) (locations)

* Group Audience (og_group_ref)


**Audio**

* URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Format (field_pece_file_format)

* Audio File (field_pece_media_audio)

* Location (if different from fieldsite) (locations)

* Group Audience (og_group_ref)

* Format (field_pece_file_format) 

* Duration (field_pece_media_duration)

* Transcript (field_pece_transcript)


**Video**

* URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Format (field_pece_file_format)

* Video File (field_pece_media_video)

* Location (if different from fieldsite) (locations)

* Group Audience (og_group_ref)

* Format (field_pece_file_format) 

* Duration (field_pece_media_duration)

* Transcript (field_pece_transcript)


**Website**

 URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Website URL (field_pece_website_url)

* Location (if different from fieldsite) (locations)

* Group Audience (og_group_ref)


**Bundle**

* URI (field_pece_uri)

* Title (title)

* Authors (field_pece_authors)

* Contributors (if different from authors) (field_pece_contributors)

* *Artifacts* (field_pece_artifacts)

* *Fieldsite* (field_pece_fieldsite)

* Critical Commentary (field_pece_crit_commentary)

* License (field_pece_license)

* Permissions (field_permissions)

* Tags (field_pece_tags)

* Format (field_pece_file_format)

* Location (if different from fieldsite) (locations)

* Group Audience (og_group_ref)


**Memo**

* URI (field_pece_uri)

* Title (title)

* Text (body)

* Authors (field_pece_authors)

* Tags (field_pece_tags)

* Comments

* Group Audience (og_group_ref)

* License (field_pece_license)


**Bibliography**

(biblio metadata from Zotero API)

* Biblio entry
    * All the biblio fields, including keywords

* Tags (field_pece_tags)

* Group Audience (og_group_ref)


PECE Annotation Scheme
----------------------

**Structured Analytics (Question Set)**

* Description: Collection of Questions / Annotations (type: Entity)

* Title (title)

* Reference to Analytics / Questions

**Analytics (Questions)**

* Description: Individual Questions

* URI (field_pece_uri)

* Title (Question)

* Author

* Tags (field_pece_tags)

* Reference to Question Set

**Annotation (“Response to a question”)**

* Description: Response to a Question

* URI (field_pece_uri)

* Text body (long text)

* Author

* Reference to annotation question

* Reference to content where was created.

* Permissions

* License (field_pece_license)

* Tags (field_pece_tags)

