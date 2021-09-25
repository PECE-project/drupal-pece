
--------------------------------------------------------------------------------
                           Pack and Upload Module
--------------------------------------------------------------------------------

There are certain situations where a user would require a bulk of files to be 
uploaded at server. You can take an example of feed import activity where a user
uploads node using feed importer. There could be an image or file field which 
requires files to be uploaded however there is no simple way to move all files 
via FTP first and then refer the path of uploaded files in your CSV or excel 
files for a specific node to be created.

By using Pack & Upload this process can be very easy just by following the 
steps:

1. Create a tar.gz or zip of files you want to upload.
2. Change pack & upload settings and specify a directory where you want to 
move all uploaded files.
3. Now go to uploader form, provide path to your pack (zip or tar.gz) and 
upload.
4. Once uploading is completed it will extract all files in the specified 
directory.

Note: Make sure you have the right permissions to the directory where you want 
to upload.


Installation
-------------

 * Copy the pack_upload directory to your modules directory and
   activate the module.


Usage
-----
   
 * Install pack_upload module from admin panel.
 
 * Goto url admin/config/pack-upload.
 
 * Provide the pack_upload directory for extraction.
    
 * Click on save settings.
 
 * Create a zip or tar of files you want to upload.

 * Use importer on pack & upload settings page.

 * Provide the path of packed file and upload.

 * After completion of upload your pack will be extracted to specified 
directory.


--------------------------------------------------------------------------------
                               General notes
--------------------------------------------------------------------------------
Currently path can be provide as stream wrapper as default path is
public://bulk_media.


Maintainers: 
 * Divesh Kumar, diveshkumar1983@gmail.com
