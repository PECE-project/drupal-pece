###############
PECE Data Model
###############

PECE Data Model

0. User Roles

* Researcher: 
  Access to restricted data

* Contributor:
  Access to group contributed data

* Anonymous
  Public access data

1. Data Types

List of data types, their fields, and their relations.
References to other data types within a particular type are marked with italics.

**Projects**
* URI
* Title (required)
* Description
* Institution (Field link com title, multiple, and required)
* Researchers
* Contributors
* Fieldsites
* Design and Substantive Logics
* Funding Agency
* Interview Request Form
* File Attachment (public)
* Consent Form 
* Start and End Date field (Only the start date is required)

**Groups**
* URI
* Title
* Description
* Banner Image
* File Attachment
* Email
* Members
* Researchers
* Contributors
* Citations
* Memos
* Field Diaries

**Forums** 

**Fieldsites**
URI
Title
Description
Location

**Design and Substantive Logics**
URI
Title
Researchers
Description
Image
Authors
Researchers
Contributors
Type (Design/Substantive)
Citation
Tags

**Artifacts**

**Fieldnote**
URI
Title
Date of creation
Date of publication
Date(s) of modification
Revision number
Author
Author
Contributor (if different from authors)
Text
Fieldsite
Annotations
License
Permissions
Tags

**Text**
URI
Title
Date of creation
Date of publication
Date(s) of modification
Revision number
Author
Authors
Contributors (if different from authors)
Fieldsite
Annotations
Critical Commentary
License
Permissions
Tags
Citation
Group Audience
Groups
Personal workspace

**PDF Document**
URI
Title
Date of creation
Date of publication
Authors
Collaborators (if different from authors)
Fieldsite
Annotations
Critical Commentary
License
Permissions
Tags
Citation
File attachment
Group Audience
Groups
Personal workspace

**Image**
URI
Title
Date of creation
Date of publication
Date(s) of modification
Revision number
Author
Author
Collaborator (if different from author)
Format
Fieldsite
Annotations
Critical Commentary
License
Permissions
Tags
File attachment
Location (if different from fieldsite)
Group Audience
Groups
Personal workspace

**Audio**
URI
Title
Date of creation
Date of publication
Author
Collaborator (if different from author)
Format
Duration
Transcript
Fieldsite
Annotations
Critical Commentary
License
Permissions
Tags
Citation
File attachment
Location (if different from fieldsite)
Group Audience
Groups
Personal workspace

**Video**
URI
Title
Date of creation
Date of publication
Author
Collaborator (if different from author)
Format
Duration
Transcript
Fieldsite
Annotations
Critical Commentary
License
Permissions
Tags
Citation
File attachment
Location (if different from fieldsite)
Group Audience
Groups
Personal workspace

**Website**
URI
Title
Date of creation
Date of publication
Author
Collaborator (if different from author)
Fieldsite
Annotations
Critical Commentary
License
Permissions
Tags
Citation
File attachment
Group Audience
Groups
Personal workspace

**Bundle**
URI
Title
Date of creation
Date of publication
Author
Collaborator (if different from author)
Fieldsite
Annotations
License
Permissions
Tags
Citation
Reference to other artifacts (unlimited)
Group Audience
Groups
Personal workspace
License
URI
Name
Type
Description
Logo
File attachment

**Memo**
Title
Text
Author
Tags
Comments
Group Audience
Groups
Personal workspace

**Bibliography**
(pulls all the biblio metadata from Zotero API)
Biblio entry
All the biblio fields, including keywords
Tags
Group Audience
Groups
Personal workspace

----------------------
PECE Annotation Scheme
----------------------

Structured Analytics (Question set)
Description: Collection of Questions/Annotations
Type: Entity
Title
Reference to Questions

Analytics (questions)
Type: entity
URI
Title (Question)
Author
Date
Tags
Reference to Question Set

Annotation (“Response to a question”)
Type: entity
URI
Text body (long text)
Author
Date
Reference to annotation question
Reference to content where was created.
Permissions
License
Tags
