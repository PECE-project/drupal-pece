-- SUMMARY --

MimeDetect provides a mime detection API.

Detection service is primarely based on fileinfo PHP extension and on UNIX file
command as secondary method. It also improves default Drupal mimetype detection
based on filename extension.

MimeDetect includes a simple submodule for file upload protection against
inconsistent filename extension and its real content.


-- REQUIREMENTS --

None.


-- INSTALLATION --

Install as usual, see:

  https://www.drupal.org/node/895232

for further information.


-- CONFIGURATION --

Module configuration is available at Admin -> Configuration -> Media
(/admin/config/media/mimedetect).

By default, only the PHP fileinfo detection engine is enabled.


-- USAGE --

MimeDetect acts as an API, other modules can make usage of it by calling
'mimedetect_mime' function.

A simple file upload validator is included in a separate module for illustration
purposes, basic functionality and backward compatibility with Drupal 6. It
rejects any file upload which detected MIME type doesn't match the filename
extension.


-- CUSTOMIZATION --

None.


-- DRUPAL 6 UPGRADE --

Drupal 6 filefield module ( https://www.drupal.org/project/filefield ) had
integration with MimeDetect. This module is now part of the Drupal 7 core, so
the integration with non-core (third-party) modules like MimeDetect was lost.

This functionality is now provided by the "MimeDetect file upload validator"
module, included as a submodule.


-- TROUBLESHOOTING --

Previous versions of MimeDetect (7.x-1.0 and older) were distributed with a
Magic database file to make FileInfo based MIME detection more consistent across
servers. Due to that different PHP version expect different 'magic' file format,
there were frequently errors on installation and after PHP version updates, so
this database has been removed in favor of the default magic information
available in system server or bundled with PHP fileinfo extension.

This change affects only the default behaviour; if your website is configured to
use a custom magic, MimeDetect will be still running with it.

For the default behaviour, might be slight differences in MIME type detection
since the magic information is now taken from system or PHP, not from the old
provided magic file. In any case, default behaviour should be now more
accurate.


-- CONTACT --

Current maintainers:
* Manuel Adan (manuel.adan) - https://www.drupal.org/user/516420


-- CREDITS --

Ported to D6 & D7 by:
* andrew morton (drewish) - https://www.drupal.org/user/34869

Created by:
* Darrel O'Pry (dopry) - https://www.drupal.org/user/22202
