PECE System Administration
==================

How do I install PECE?
----------------------

PECE is a Free Software-based Drupal distribution, therefore the
[*standard installation procedure for Drupal 7*](https://www.drupal.org/requirements) applies to PECE with a few
extra dependencies.

The following instructions have been tested on a Debian 8 (jessie)
server, but they are not OS-dependent. PECE should run on any system
supported by Drupal 7. PECE has been tested in virtual machines with
256M allocated for PHP, being 128M the recommended minimum for Drupal 7
distributions. Your configuration, of course, may vary considerably
depending on the usage you are making of the platform. Refer to our data
management guidelines under the “sustainability” section to learn about
the recommended minimum specs for your servers.

### Downloading the Distro

Our distribution is currently being developed on Github. You can obtain
the most updated version following the link “Releases” on the project’s
git repository:

> https://github.com/PECE-project/pece-distro

Alternatively, you can obtain the source code and build the distro
yourself if you intend to help our team by fixing bugs and extending the
platform for your research purposes:

> git clone
> https://github.com/PECE-project/drupal-pece.git

If you are a developer who wants to contribute to PECE, you will need to
follow special instructions to install and configure the tools for
building the distro. Consult the sub-section [*Setting up the Development Environment*](http://pece.readthedocs.io/en/latest/installation.html#setting-up-the-development-environment)
below for more information.

### Dependencies

PECE has extra dependencies in addition to the ones you will need for
Drupal 7 core:

-   cURL

-   php-mcrypt (for AES encryption support in backups and user passwords)

-   php-ssh2 (for backup SFTP support, installed via PHP pear)

-   pecl-yaml (for YAML parsing)

### Quick Install

If you have the server backend already set-up, you can quickly install
PECE following these steps:

Clone the ‘’pece-distro’’ repository:

> git clone
> [*https://github.com/PECE-project/pece-distro.git*](https://github.com/PECE-project/pece-distro.git)

Create an empty database:

> mysql -u $YOUR\_USER -p -e "CREATE DATABASE $YOUR\_DB\_NAME
> CHARACTER SET utf8 COLLATE utf8\_general\_ci;"

Proceed to the URL in which your Drupal will reside, i.e.
https://worldpece.org. From there, you can install PECE like any other
Drupal site. Follow the Drupal.org [*official documentation if you need further help*](https://www.drupal.org/documentation/install/). In the
section [*Troubleshooting*](http://pece.readthedocs.io/en/latest/installation.html#troubleshooting) below we describe common issues users have when trying to install PECE without the proper backend dependencies, configurations, and permissions.

One important note: please, make sure to set the permissions on the
filesystem properly. We cannot emphasize this enough. The [*official Drupal documentation explains*](https://www.drupal.org/node/244924) how
to do so, if you have questions. (In our experience, we have needed to
set the file permissions at sites/default/files/artifacts to 770 and
sites/default/files/private to 770.)

I want to use HTTPS with PECE. How can I do that?
------------------------------------------------------------------------
A very simple tutorial for setting up HTTPS with Certbot on Ubuntu can be found [here](https://www.digitalocean.com/community/tutorials/how-to-secure-apache-with-let-s-encrypt-on-ubuntu-18-04).

I’ve installed PECE, but none of my links are working. What is going on?
------------------------------------------------------------------------

Your webserver is not properly configured to support what is called
“Clean URLs” on Drupal. Make sure you have your httpd “rewrite” rules
properly set-up. This configuration can be done in the vhost file of
your nginx configuration, following the [*Perusio guide*](https://github.com/perusio/drupal-with-nginx) or using the [*default.htaccess file that is provided by default by Drupal*](https://github.com/PECE-project/drupal/blob/7.x/.htaccess) if you are running Apache.

I get an error about a YAML parser being missing. How can I fix that?
------------------------------------------------------------------------

Newer versions of PHP require you to install pecl-yaml for YAML parsing. You can find it [here](https://pecl.php.net/package/yaml).
We recommend using the latest version, which is 2.0.4 at the time of writing. Follow the pecl-yaml instructions to build and install it.
Then edit your php.ini file. For example, if you are using PHP 7.2, the file will be found at:
/etc/php/7.2/apache2/php.ini

Add the following line to php.ini:
extension=yaml.so

When should the admin login credentials be used?
------------------------------------------------

Distribute admin login credentials to as few users as possible. Admin
login credentials should only be used to configure settings and to
approve new users. The admin credentials should not be used to add
content or comment on content.

How do I update the site information?
-------------------------------------

Go to “Administration » Configuration » System » Site information” and
fill out the information about your site name, the basic admin password,
contact, timezone and other relevant info.

How do I upload the terms of service?
-------------------------------------

Go to “Administration » Configuration » People » Legal” and click “Add
T&C”, then fill-out the boxes with your custom text to be displayed to
every user who requests an account on the system. 

How do I set up back-ups?
-------------------------

As explained in our data management guidelines, PECE is configured to
automatically generate backups. You should, however, revise the settings
and set-up a SFTP connection to transfer your backup to another server
and ensure that you have extra security when storing your encrypted
backups. First, revise the settings we provided, changing whatever you
think is needed (say, the most convenient time, when the site is not
being used, to generate the backup). Go to “Configuration » System »
Backup and Migrate” to perform this first step. Then, click on
“Destinations” and “Add Destination” to set-up the SFTP connection with
the credentials of your backup server. Please note that you have to use
the port 22 (not 21) and password authentication, since ssh-key
authentication is unfortunately not supported yet.

How do I configure SMTP so that emails can be sent from the platform?
---------------------------------------------------------------------

PECE uses Drupal notification for key events on the system. It has to be
configured using a regular email address, provided you have all the mail
server information. You just need your SMTP server info and credentials
to get this done. Go to “Administration » Configuration » System » SMTP
Authentication Support” and provide your SMTP server information,
including username and password.

How do I increase the file upload limit?
----------------------------------------

While logged-in as an administrator, navigate to Administration &gt;&gt;
Configuration &gt;&gt; Media &gt;&gt; File Settings. Under the Maximum
Upload Size field, enter a new value (we use 2GB). Click Save
Configuration. You may also need to increase the upload limit on the
server.

How do I update my instance when a new version of the PECE distro is released?
------------------------------------------------------------------------------

Always back-up your files and database before updating the platform.

Put the site in maintenance mode. Under sites/default/, there is a file
called settings.php. Search for $update\_free\_access = FALSE; and
change FALSE to TRUE.

Then, go to YourSite/update.php and follow the steps. In theory major
updates are not handled differently, but sometimes issues have occurred.

Be sure to turn off maintenance mode when you are done.

Other Post-Installation Troubleshooting
---------------------------------------

-   “Time Out” during installation: this issue is related to the usage of Drupal distributions in “shared hosting” environments which are very limited in terms of the resources allocated per client / user account. If the installation process is interrupted before it is finished, you will have to check your PHP configuration and increase the memory allocation and timeout configuration for the php scripts with the following directives: memory\_limit and max\_execution\_time which can be found in your php.ini file. After doing so, you should not experience more “timeouts” during installation.

-   Links do not work: your webserver is not properly configured to support what is called “Clean URLs” on Drupal. Make sure you have your httpd “rewrite” rules properly set-up. This configuration can be done in the vhost file of your nginx configuration, following the [*Perusio guide*](https://github.com/perusio/drupal-with-nginx) or using the [*default.htaccess file that is provided by default by Drupal*](https://github.com/PECE-project/drupal/blob/7.x/.htaccess) if you are running Apache.

-   Permission denied when uploading content: your filesystem permissions must be set accordingly for the public and private directories, since PECE uses both extensively. [*Follow this official Drupal tutorial*](https://www.drupal.org/node/244924) to configure the permissions properly for both directories where you installed PECE.

-   Permission denied when uploading content after configuring filesystem permissions: make sure your /tmp is also writable and, if you are on a shared host and cannot have access to it, configure Drupal to point to a temporary directory in your system/files path. There is a [*discussion about this issue on Drupal.org that is helpful*](https://www.drupal.org/node/2140629).

-   Cannot create users, server internal error: in our experience, php5-mcrypt is probably not installed in your system. Make sure it is properly installed and loaded, by running php -m in a shell and checking if it is listed.
