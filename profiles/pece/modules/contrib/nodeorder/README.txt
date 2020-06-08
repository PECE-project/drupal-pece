*******************************************************
    README.txt for nodeorder.module for Drupal
*******************************************************
The nodeorder module gives users an easy way to order nodes within their
taxonomy terms.

By default, the taxonomy module orders listings of nodes by stickiness and
then by node creation date -- most recently posted nodes come first.

The nodeorder module gives the user the ability to put nodes in any order they
wish within each category that the node lives.

There are two ways that a user can order nodes within a category.  The first
is to use the "move up" and "move down" links that can be configured to appear
on each node (especially useful when looking at lists of taxonomy terms).  The
second is to use drag and drop, which appears on the administrative listings
of nodes in a category.

To install the nodeorder module:

- Put the nodeorder directory in your modules directory.
- Navigate to administer --> modules, and enable the nodeorder module.
- Navigate to administer --> access control, and assign one or more roles
the right to "order nodes within categories."
- You may turn on "orderability" on a per-vocabulary basis by visiting your
vocabularies' administration pages (admin/taxonomy).  This module adds a
checkbox on the "edit vocabulary" page titled "Orderable" -- it defaults to
being unchecked.  After checking this box and saving your changes, you'll be
able to order nodes that are classified in this category.

- To use drag and drop node ordering, you will find a tab called "order
nodes" on any admin/taxonomy/VID pages where the vocabulary has been set to
orderable.

- Navigate to admin/settings/nodeorder, where you can set some options
that determine the way nodeorder works.

TECHNICAL NOTES:

Upon installation, this module adds a new column (weight) to the
term_node table.  Adding a column to a core table?  Are you crazy?  Yeah,
I guess so ... but it lets us keep the module's code very small since
most everything works through taxonomy.  Also it helps to avoid an extra
join for every node listing.

Please note that the node order is only respected when visiting links
that begin with "nodeorder" -- if you visit links that begin with
"taxonomy" they will appear in the generic taxonomy order.  Since the
module implements hook_term_path, the taxonomy links that get printed
per node will correctly point to the "nodeorder" space when they are in
orderable vocabularies.

The nodeorder module was developed by FunnyMonkey.
