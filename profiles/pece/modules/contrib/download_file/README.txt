
-- SUMMARY --

DownloadFile is a module to direct download files or images.

For a full description of the module, visit the project page:
  http://drupal.org/project/download_file

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/download_file

-- REQUIREMENTS --

 * File core module

-- INSTALLATION --
  
1) Copy the download_file folder to the modules folder in your installation.

2) Enable the module using Administration -> Modules (/admin/modules).

3) Configure user permissions in Administration -> People, click on the 
   Permissions tab (admin/people/permissions), go to DownloadFile module part 
   and "Access direct download file".
  
4) Manage teaser and full node display settings at Administration -> Structure 
   -> Content types -> "your type" -> manage display 
   (admin/structure/types/manage/"your type"/display).
  
5) Choose a formatter to apply to files or images in that field. Four new 
   formatters "Direct download file" appear in the select list.

6) Configure the format of the link accessible at Administration -> 
   Configuration -> Media -> Download file (/admin/config/media/download-file).


Using with Views module
-----------------------
Similarly, you can use a formatter when displaying files or images attached to
nodes using File or Image in a View (http://drupal.org/project/views)
through the Views UI.

1) Manage display at Administration -> Structure -> Views 
   (/admin/structure/views) and add a new view by clicking the "Add new view" 
   link (/admin/structure/views/add) or edit an existing view by clicking the 
   "Edit" link (/admin/structure/views/edit/"your view").

2) Click on a file field or image field.

3) Choose a formatter in select list "Format" to apply at this field. Four new 
   formatters "Direct download file" appear.

4) Click on "Save" button and see the display in the preview.

-- CONTACT --

Current maintainer:
* Matthieu Moratille (xMATTx) - http://drupal.org/user/394628

This project has been sponsored by:
* CORE-TECHS
  An innovative company based in Paris whose activities are structured around
  the software production, service delivery and use of open source technologies.
  Visit http://www.core-techs.fr for more information.
