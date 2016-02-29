# Respond.js Drupal module

Respond.js is a polyfill for CSS3 media queries. It allows browsers
without native MQ support to have a rudimentary ability to process
CSS wrapped in max- and min-width MQs.

This module adds respond.js to pages in an optimal manner:

- Respond.js will never be preprocessed or aggregated.
- Respond.js will come after CSS
- Respond.js should come before most other scripts, with exceptions for
  Modernizr or other scripts that might provide presentational benefits
  deemed more important than the legacy IE userbase.
- As of 7.x-1.1 you can choose whether you'd like the library to appear
  in the <head> or bottom of the page. Defaults to <head>

## Installing the module and JavaScript library:

Note: Drush can automatically install the latest copy
of the JS library when you enable the module.

- Download the library from https://github.com/scottjehl/Respond
- Add a folder with the name 'respondjs' in your libraries folder
  e.g. sites/all/libraries/respondjs
- Check the Status Report page if the library is succesfully installed
- Select the position of the <script> tag by visiting
  /admin/config/media/respondjs

## Known issues

- Sasson theme's development mode can cause malfunctions
  http://drupal.org/node/1706502

## Credits

Module maintained by:
- Chris Ruppel, Four Kitchens (https://drupal.org/user/411999)
- Carwin Young, Lullabot (https://drupal.org/user/487058)

Full list of contributors
http://drupal.org/node/1238970/committers

Respond.js (c) 2011 Scott Jehl, scottjehl.com
https://github.com/scottjehl/Respond
