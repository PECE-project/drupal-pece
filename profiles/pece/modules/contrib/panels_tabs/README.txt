@todo: Port this readme to d7 and get out old stuff
Description
-----------
Configurable 'tabs' panel style. Provides 3 kinds of tabs:
- Normal tabs (horizontal filling disabled).
- Horizontally filling, equal width tabs: sets the width property, forcing
  each tab to be equally wide. If the text doesn't fit in the tab, the
  overflow will be hidden.
- Horizontally filling, smart width tabs: calculates the length of the text in
  each tab and compares this to the total length of the text on all tabs. It
  then sets the width property of each tab according to the percentage of text
  the tab contains.
  
Pager links inside panels (e.g. views with pagers) will automatically be
updated to ensure that the same tab is opened when the page is loaded.


Dependencies
------------
* Panels 2,3 (Drupal 6) or 2(Drupal 5) (http://drupal.org/project/panels)
  (a 5.x-2.x-dev tarball of July 6 or later, or alternatively: beta 5 with
  this patch applied: http://drupal.org/node/278861)
* Tabs
  * Drupal6 http://drupal.org/project/tabs
  * Drupal 5 (part of Javascript Tools, http://drupal.org/project/jstools)


Installation
------------
1) Place this module directory in your modules folder (this will usually be
"sites/all/modules/").

2) Enable the module.

3) Go to the "Layout settings" tab of the Panels page, Mini panel, ... on
which you want to apply this style.


Troubleshooting
---------------
This module does not have any CSS of itself. CSS is provided by the Tabs
module. The Tabs module itself only *overrides* the tabs style defined by the
theme. This means that you need a theme that already supports tabs, or you
won't see any tabs at all! E.g. Garland has tabs.
See http://drupal.org/node/258177.


Sponsors
--------
* Initial development:
   Paul Ektov of http://autobin.ru.
* Port to drupal7:
    Amitai Burstein of http://gizra.com/


Author
------
Wim Leers

* mail: work@wimleers.com
* website: http://wimleers.com/work

The author can be contacted for paid customizations of this module as well as
Drupal consulting, development and installation.
