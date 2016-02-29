
WHAT THIS MODULE IS GOOD FOR
----------------------
This module can basically be useful in 2 ways:
1. For making your users passwords readable by admins.
2. As a very simple general purpose AES encryption API to use in other modules.

REQUIREMENTS
----------------------
This module requires an implementation of AES encryption to work. Since 1.4 there are two supported implementations:
1. PHP's Mcrypt extension, based on old abandoned library libmcrypt but still in the saddle.
2. PHP Secure Communications Library (phpseclib).

You need to have at least one of these installed (both is fine as well).
Mcrypt is a lot faster than phpseclib (about 15..60 times according to simple tests in different conditions), so you might want to use old but fast Mcrypt.
The phpseclib is a great alternative, and the speed difference probably won't matter in most cases.

If you don't have any of them, then read the next section below.

Also note that although this module SHOULD work on Windows and with a MySQL database, it has only been tested on Linux with a PostgreSQL
database.

HOW TO GET AN AES IMPLEMENTATION
----------------------
If you don't have an AES implementation (you'll notice this when you install this module) then the easiest implementation for you to get is probably the PHP Secure Communications Library (phpseclib).

Just download the latest version from http://phpseclib.sourceforge.net/ and install it as a regular Drupal library.
You should have actual AES implementation located in he file like sites/all/libraries/phpseclib/Crypt/AES.php and the Library module have to be enabled.

That's it! Try installing/enabling the module again.

This module was developed using phpseclib version 1.5, but hopefully future versions should work as well (and might contain security bug fixes, so always get the latest). If you've got a version of phpseclib that's newer than 1.5 and you're running into trouble, then please create an issue at drupal.org/project/aes

If you want to use the Mcrypt implementation instead then you can find information on how to install it here: http://php.net/mcrypt
Note that you most likely need to be running your own webserver in order to install Mcrypt. If you're on a shared host you'll probably have to ask your hosting provider to install Mcrypt for you (or use phpseclib instead).

ABOUT KEY STORAGE METHODS
----------------------
Something you should pay attention to (if you want any sort of security) is how you store your encryption key. You have the option of storing it in the database as a normal Drupal variable, this is also the default, but it's the default only because there is no good standard location to store it. Switching to a file-based storage is strongly encouraged since storing the key in the same database as your encrypted strings will sort of nullify the point of them being encrypted in the first place. Also make sure to set the permission on the keyfile to be as restrictive as possible, assuming you're on a unix-like system running apache, I recommend setting the ownership of the file to apache with the owner being the only one allowed to read and write to it (0600). Above all make sure that the file is not readable from the web! The easiest way to do that is probably to place it somewhere outside the webroot.

UPGRADING FROM 1.3 OR EARLIER
----------------------
If you're upgrading from an earlier version than 1.4, and don't want to change anything, then just stick with the Mcrypt implementation since that is the (only) implementation this module used in earlier versions. It should be selected as default when you install/upgrade (remember to run update.php).

TODO
____
Ideas for 7.x-2.x
- PHPSecLib currently supported IV so usage setIV() should be added;
  the adding itself is easy, backward compatibility is an issue;
- Ability to manually update IV. Check for correct number of bytes;
- Here is an example of having same result by different implementation:
  http://stackoverflow.com/questions/9305781/cant-get-the-same-result-for-encryption-with-mcrypt-and-phpseclib
  cannot reproduce the same for 256 bits;
- Optionally(?) store IV together with encoded data, like <hex-iv>~<base64-encrypted>;
- the MCrypt extension is kind of abandoned and obsolete; switch to any new player like libsodium if they strong enough
  to be represented as a core PHP extension;
