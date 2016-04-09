###############
Installing PECE
###############

PECE is a Free Software-based Drupal distribution, therefore the standard
installation procedure for Drupal 7 applies to PECE with extra dependencies. 

The following instructions have been tested on a Debian 8 (jessie) server. Use this
version of GNU/Linux as a guide for the version of the software dependencies we mention below.


Downloading the Distro
-----------------------

Our distribution is currently being developed on Github. You can have to the most 
updated version following the link "Releases" on the project's git repository:

::
  
    https://github.com/PECE-project/pece-distro.git

Alternatively, you can obtain the source code and build the distro yourself if
you intend to help our team by fixing bugs and extending the platform for your
research purposes:

::

    git clone https://github.com/PECE-project/drupal-pece.git

To use the development source files, you will need to follow special instructions
to install and use `Kraftwagen <https://github.com/kraftwagen/kraftwagen>`_ as a build and 
deployment tool. See the sub-section on `Development`_ below.


Dependencies
------------

PECE has extra dependencies in addition to the ones you will need for Drupal 7 core:

* cURL (for the D7 Amber contributed module)
* Kraftwagen (for building, updating, and deploying PECE)
* php-mcrypt (for AES encryption support in backups and user passwords)
* php-ssh2 (for backup SFTP support, installed via PHP ``pear``)

All the other distro-specific dependencies are generated in the build process, 
so you do not need to worry about them when downloading the tarball or cloning 
the development repo for generating a customized build. All the backend 
dependencies, however, must be configured. It is out of the scope of this document
how to configure the backend. Follow the Drupal.org documentation, if you need
help `getting started <https://www.drupal.org/documentation/install/>`_.
In the section "Troubleshooting" below we describe common issues that might
happen when trying to install PECE without the proper backend configuration.


Quick Install
-------------

If you have the backend already set-up (including ''Drush''), you can quickly install PECE following these steps:

1. Clone the ''pece-distro'' repostory:

:: 

    git clone https://github.com/PECE-project/pece-distro.git
    


2. Create an empty database:

::
    
    mysql -u $YOUR_USER -p -e "CREATE DATABASE $YOUR_DB_NAME CHARACTER SET utf8 COLLATE utf8_general_ci;"


3. Edit the file ''sites/default/settings.php'' with your DB credentials: ``($YOUR_USER, $YOUR_DB_NAME, and $YOUR_DB_PASSWD)``


4. Copy the database schema (.sql) to your database:

::

    drush sql-cli < pece-drupal/database.sql
    


Please observe that this step will only work if ``Drush`` and your ``settings.php`` is properly configured.
The default passwd for the admin user is ''peceadmin''. **Make sure to change it** after the first log-in.
Also, make sure to set the **permissions** on the filesystem properly. We cannot emphasize this enough. 
The `official Drupal documentation explains <https://www.drupal.org/node/244924>`_ how to do so, 
if you have questions on how to proceed.


Development
-----------

PECE development is currently happening on Github, but we are planning to move to Drupal.org
soon. To get started, you need to clone the development repository:

::

    https://github.com/PECE-project/drupal-pece.git

This repository contains the source files in the ``src`` directory, which is basically
everything you will need from us to extend, build, deploy an existent version of
the distro. This  process depends on Kraftwagen and its workflow, so `follow their 
guide <http://kraftwagen.org/get-started.html>`_ if you need help on how to set it up 
for an existent PECE installation.

In order to build the distro from the development repository, you will need to
install the following dependencies:

* Drush (5.x or 6.x)
* Kraftwagen (1.0rc1)
* Node.js (0.12.0)

Make sure you use the ``master`` branch of the dev repository. Specific instructions
on how to contribute to the project after you are done setting it up, please follow
the Contributors guide.

The development branch contains the following bash scripts which execute the build 
and the update processes.

* ``build.sh``
* ``update.sh``

Please, read their content if you do not know the order of commands for Krafwagen. 

There are special dependencies if you are planning to use Nginx as the webserver,
which we highly recommend. These dependencies include:

* nginx-extras
* php5-dev
* uploadprogress (installed via PHP ``pear``)

These are necessary for having the upload progress bar working on Nginx, but this
step is not mandatory. Configuring Nginx is out of the scope of this document, but
there is plenty of information on it. If you want to use the configuration we use,
copy and customize `Perusio\'s instructions <https://github.com/perusio/drupal-with-nginx>`_ 
according to your server set-up for getting Drupal to perform better (than Apache2), 
especially when serving large, binary files.


Post-Install Instructions
-------------------------

OK, so now you have your PECE instance up and running, but you are not yet done! There 
are specific configurations which you need to do using the Admin interface. Further
configuration is needed because these are specific settings for each PECE installation
and use case.

0. **Basic site info**: first things first, you need to provide the basic information
about your site before you go live. Go to "Administration » Configuration » System » Site information" 
and fill out the information about your site name, the basic admin password contact, 
timezone and other relevant info. You can also customize the 403-redirect-upon-access-denied
messages to the users.

1. **Customizing the PECE theme**: we will make this easier for you in the near future, 
but for now you have to change the logo.png on ``profiles/pece/themes/pece_scholarly_lite/logo.png`` 
and tweak the main CSS file to change the basic colors of the PECE theme.

2. **Uploading your "Terms of Service":** go to "Administration » Configuration » People » Legal" 
and click "Add T&C", then fill-out the boxes with your custom text to be displayed to 
every user who requests an account on the system. You may ask: why is there not a default 
"Terms of Service"? Because... the text really depends on the way you are using PECE, so our 
legal documents do not suit your case, you need to craft your own text according to the 
usage you are making of PECE. We are not (cannot and should not be) responsible for any 
use people make of the platform.

3. **Setting up AES**: it is very important that you generate, secure, and use your 
own encryption keys. To config AES, go to: "Administration » Configuration » System » AES settings". 
Make sure to point to a secure directory **outside the webroot where PECE is installed** 
to store your key and make it read-only (to the owner of the httpd service), instead 
of having it stored in the database (which tends to be a less secure option).

4. **Perma.cc:** PECE comes pre-shipped with Amber, so if you have an account on 
perma.cc you can set PECE up to use it an store your snapshots there. This is the
way to go when it comes to long-term preservation of content for scholarly
purposes. Go to "Administration » Configuration » Content authoring » Amber" 
and select "perma.cc" as alternate backend and provide your API key in the
text field below. Done! You are storing "PECE Website" link artifacts, hopefully,
for many future anthropological lives and times now.

5. **Backup:** as explained in our data management documents, PECE is configured 
to automatically generate backups. You should, however, revise the settings 
and set-up a SFTP connection to transfer your backup to another server and 
ensure that you have extra security when storing your backups. First, 
revise the settings we provided, changing whatever you think is needed 
(say, the most convenient time, when the site is not being used, to generate 
the backup). Go to "Configuration » System » Backup and Migrate" to perform 
this first step. Then, click on "Destinations" and "Add Destination" to
set-up the (S)FTP connection with the credentials of your backup server. Please
note that you have to use the port 22 (not 21) and password authentication,
since ssh-key authentication is unfortunately not supported.

6. **System Notification**: PECE uses Drupal notification for key events on the system.
It has to be configured using a regular email address, provided you have all the mail
server information. You just need your SMTP server info and credentials to get this done.
Go to "Administration » Configuration » System » SMTP Authentication Support" and provide 
your STMP server information, including username and password. Voilà! System notifications 
are now working for everyone as described in your data management section on "Notifications".

7. **User Roles:** we provide a basic permission system based on 2 user roles: Researcher
and Colaborator. If you need other user roles, you might need to extend the module
``pece_access`` which is shipped with the distro to reflect the changes. By default,
there is only one administrator. This is a security config: to have a more secure
system, you do not want to give admin powers to regular users, so that when one
regular user account is compromised, the whole system and users' data gets 
compromised in the process. Not good...


Troubleshooting
---------------
Common issues post-installation include:

* **Links do not work:** your webserver is not properly configured to support what is called "Clean URLs" on Drupal. Make sure you have your httpd "rewrite" rules properly set-up. This configuration can be done in the vhost file of your nginx configuration, following the `Perusio guide <https://github.com/perusio/drupal-with-nginx>`_ or using the `default .htaccess file that is provided by default by Drupal <https://github.com/PECE-project/drupal/blob/7.x/.htaccess>`_ if you are running Apache.

* **Permission denied when uploading content:** your filesystem permissions must be  set accordingly for the ``public`` and ``private`` directories, since PECE uses both extensively. `Follow this official Drupal tutorial <https://www.drupal.org/node/244924>`_ to configure the permissions properly for both directories where you installed PECE.

* **Permission denied when uploading content after configuring filesystem permissions:** make sure your ``/tmp`` is also writable and, if you are on a shared host and cannot have access to it, configure Drupal to point to a temporary directory in your ``system/files`` path. There is a `discussion about this issue on Drupal.org that is helpful <https://www.drupal.org/node/2140629>`_.

* **Cannot create users, server internal error:** in our experience, ``php5-mcrypt`` is probably not installed in your system. Make sure it is properly installed and loaded, by running ``php -m`` in a shell and checking if it is listed.

* **Autocomplete fields do not work, displaying a 404 error:** This is **known issue** for both nginx and apache2 after the upgrade to Drupal 7.39 (and has persisted until Drupal 7.42, which is the version we are using for PECE 1.0-rc2). To solve this problem, you have to make sure /non-clean/ URLs also work. This can be done by configuring your webserver to deal with non-clean URLs for the exception of the autocomplete function. This issue is debated and temporarily solved for `nginx <https://github.com/perusio/drupal-with-nginx/issues/241>`_ here and for `apache2 here <https://www.drupal.org/node/2599326>`_.


Further Information
-------------------

For further information on the specifics of the Drupal installation process, please
`read the official Drupal documentation
<https://www.drupal.org/documentation/install>`_.

PECE version 1.0 does not yet have a pre-configured virtual machine image
distribution. It is in our plans to prepare one to make the lives of our
colleagues in the humanities and social sciences easier. Visit the **Contributors
Guide** page to learn how you can contribute to the project!
