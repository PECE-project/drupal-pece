
README
--------------------------------------------------------------------------
The Publication Date module adds a "Published on" date to each node,
containing the date when it was first published.

Without this, the only dates available for nodes are their created date and
changed date, but these are often insufficient to meet the needs of publishing
workflows. Sorting nodes by their created date doesn't account for content
which is held in draft form for a time while being readied for publication.
Sorting nodes by their changed date fails to account for content needing minor
corrections after being published.

The "Published on" date can be used in any templates, or views. Publication date
also incudes integration with the Display Suite module and has entity wrapper
support, so it can integrate with modules like Rules that use the Entity API
module.

By default, the "Published on" date is set automatically when a node is first
published, but it can also be edited through the node edit form, allowing a
custom published date to be set. This is useful when backdating migrated content
from an older site. The module provides permisions for restricting this field,
per content type. If a custom date is set prior to publication, it will be
respected when the node is published. The publication date is also retained when
a node is unpublished and then republished.


INSTALLATION
--------------------------------------------------------------------------
1. Copy the publication_date folder to your modules directory
2. Go to /admin/modules and enable this module.
3. If you want to give users access to edit the "Published on" date, then go
   to /admin/people/permissions and set permissions as desired.

This will add a new $node->published_at field to nodes, containing the
published date, or 'false' if no published date has been set. You can then use
this field in any templates. Moreover, this field is available in the views
parameters.

IMPORTANT: For nodes that were published BEFORE the installation of this
module, we can not know the exact date of publication, so $node->published_at
will initially contain the creation date.


UPGRADING FROM 1.0 TO 2.x
--------------------------------------------------------------------------
Please pay special attention to the README and CHANGELOG, as there are some
changes to the way the Published On date is handled. Notably in 2.x, once the
date has been set for a node it will persist until manually changed, even if
the node is unpublished and republished. In version 1.0 the date was lost when
the node was unpublished.


API
--------------------------------------------------------------------------
Other modules can use hook_publication_date_alter() to change the publication
date when it is set. See publication_date.api.php for more documentation.


CREDITS
--------------------------------------------------------------------------
The Publication Date module was originally written by Emmanuelle Gouleau and
Tristan Marly from Clever Age (http://www.clever-age.org).

D7 version initially ported by joostvdl (https://drupal.org/user/115719) and
maintained by dgtlmoon (https://drupal.org/user/25027).

Publication Date is currently maintained by jstoller
(https://drupal.org/user/99012).
