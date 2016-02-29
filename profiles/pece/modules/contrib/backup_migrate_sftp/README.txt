Backup and Migrate SFTP Module
------------------------------

This module adds SFTP support to Backup and Migrate's "Destinations" list. It
works in much the same way as the built-in FTP support.

To use it, you must first install the PHP "ssh2" PECL module:
http://www.php.net/manual/en/ssh2.installation.php

As noted in the instructions, Ubuntu has a package for this that may be
installed with a single command:

  apt-get install libssh2-php
  
For other platforms, try the following:

  pecl install ssh2 channel://pecl.php.net/ssh2-version
  
or refer to the installation guide referenced above.

Configuration and Usage
-----------------------

Create an SFTP destination exactly the same way you would create an FTP
destination, by visiting admin/config/system/backup_migrate/destination and
clicking "Add Destination". Most of the parameters are the same, but please
note the following:

  * SFTP uses SSH, and thus defaults to port 22, not 21.
  
  * SFTP requires a full path to a destination directory.
  
