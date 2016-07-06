ABOUT
Biblio Zotero is a custom Feeds implementation to subscribe to 
multiple zotero user and group libraries and sync them with a biblio library. 
It has been tested with Biblio version 7.x-1.0-rc7

DEPENDENCIES
Requires: feeds and biblio. feeds_ui is also needed if you want to change 
any of the default settings as described below.

GETTING STARTED
Install and enable the module at admin/structure/modules
      
CREATE YOUR FIRST ZOTERO-FEED NODE:
1. Go to: <yoursite>/node/add/zotero-feed
2. Name your feed, preferably, use the same name as your zotero library.
3. Specify if it is to pull from a zotero group or from a personal library (user).
4. If your zotero group or library is private, then you need to create an 
api key for yourself: https://www.zotero.org/settings/keys and then paste 
the value of the key into the api key field of your feed settings.
5. Enter a value for the 'limit' field to specify how many items from zotero 
to fetch at a time (default is 50; maximum is 99). If you have a large library it will take some
time to import the entire library. Feeds are fetched once for each cron run. You can also fetch
them manually from the "import" tab of your feed node.

OG INTEGRATION
The way that the OG integration works is that imported biblio items are added to the same group 
that the zotero-feed belongs to. So first, you have edit the zotero-feed content type and set it to 
be group content (not a group itself, but content that can be posted to a group). Assuming you haven't 
changed the content type that acts as the zotero feed, you would do that here: admin/structure/types/manage/zotero_feed.
Then when you create your feed (node/add/zotero-feed) where you specify the zotero library id, 
you also specify the group audience and any content you import also gets that same group audience. 
It works with both one or multiple groups set as group audience.

ADVANCED CONFIGURATION OF THE ZOTERO FEED IMPORTER
To modify the zotero_feed importer settings, first enable the module, 
Feeds Admin UI (feeds_ui). Once Feeds Admin UI is enabled and your user has
"adminster feeds" permission, you can change the mappings, the field 
used for tags, whether or not and how to map zotero users to drupal users.
Any changes made here will effect all zotero-feed nodes that have been created
using this importer (zotero_feed).

Go to: <yoursite>/admin/structure/feeds/zotero_feed

Settings for Feeds Zotero Processor
<yoursite>/admin/structure/feeds/zotero_feed/settings/FeedsZoteroProcessor
Here you can set the following options:
- Update existing nodes:  This should be set to "Update existing nodes" if your zotero items are likely to change at all.
- Text format:  not applicable for the out-of-the-box biblio-zotero importer setup. It is also untested in biblio_zotero
- Content type: this should always be set to Biblio unless you want to map zotero items to something other content type
- Author:  this is the default author for imported nodes. (It can be overriden based on the options below)
- Expire nodes: your choice. this is untested in biblio_zotero.
- Sync zotero tags?
- Select a term reference field in the biblio content type to use for zotero tags.
   -- First, a taxonomy vocabulary for tags should be created if it doesn't exist.
   -- Then a term reference field for tags should be set up.
   -- Finally that new field can be selected in this select box
- Use the feed owner's user account the author of imported nodes?
   -- This will set the import items to be 
- Zotero Username Profile Field
   -- If you have added a field in   User Account Settings -> Manage Fields (admin/config/people/accounts/fields) they will appear here
      and when zotero items are imported, the feeds processor will look for drupal users who have a zotero username listed in their user account
      If found, it will make that user the owner of the biblio item.
      
Mappings for Feeds Zotero Processor

<yoursite>/admin/structure/feeds/zotero_feed/mapping
For each item type in zotero you can customize which biblio field it should be mapped to. To see which biblio fields 
are available for which publication type, see <yoursite>/admin/config/content/biblio/fields. To see which zotero item
types are mapped to which biblio publication type, see the "getZoteroTypeToBiblioType" function in the biblio_zotero.inc file:

IMPORTANT
- Biblio_zotero can only map a subset of zotero item types and fields to biblio publication types and fields. You can, of course, 
extend biblio to include the Zotero fields that don't map to any biblio fields.
- During installation, biblio_zotero sets it module weight in the system table to 10 (one higher than the default weight of biblio).
If you've changed the weight of biblio, you'll want to manually set the weight of biblio sotero to be higher than that of biblio.
- After each feeds run, biblio_zotero writes a tab-delimited report of which zotero fields were and were not mapped. 
The file is stored in drupal's temporary directory.

NICE-TO-HAVES / TODO
- Allow admins to map zotero item types to different biblio publication types (might want to create the missing zotero item types as zotero pub types);
- Allow admins to change the mappings for zotero creators to biblio contributors.
- document how to override sources, targets and mappings in a custom module
- Provide config settings to turn the mapping log off if desired
- Provide an optional module that configures a stock biblio installation to have the necessary publication types, fields and contributor types to allow 
  for a complete mapping 
- Provide support for profile and profile2 modules for zotero username field.
- Biblio2 support




