
Taxonomy access fix
====

This module

* adds one permission per vocabulary: "add terms in VOCABULARY"
* changes the way vocabulary specific permissions are handled
* changes the Taxonomy admin pages' access checks
* alters the vocabularies overview table to show only what you have access to
  edit or delete

The module does what native Taxonomy lacks: more specific Taxonomy permissions
(and checking them correctly).

*Note*: In order to access the admin/structure/taxonomy page, you must first set
permissions for the desired vocabularies.

*Note*: A module can't add permissions to another module, so the
extra "add terms in X" permissions are located under "Taxonomy access fix" and
not under "Taxonomy".

*Note*: If you are upgrading from version 1.x, you can update your feature as
follows:

// Exported permission: 'add terms in 1'.
$permissions['add terms in 1'] = array(
  'name' => 'add terms in 1',
  'roles' => array(
    'admin' => 'admin',
  ),
  'module' => 'taxonomy_access_fix',
);

becomes:

// Exported permission: 'add terms in 3'.
$permissions['add terms in tags'] = array(
  'name' => 'add terms in tags',
  'roles' => array(
    'editor' => 'editor',
  ),
  'module' => 'taxonomy_access_fix',
);
