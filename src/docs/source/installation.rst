###############
Installing PECE
###############

PECE is a Free Software-based Drupal distribution, therefore the standard
installation procedure for Drupal 7 applies to PECE with a few extra dependencies. 
For development purposes, the procedure is very specific. 

The following instructions have been tested on a Debian 8 (jessie) server. Use this
version as a guide for the version of the packaged dependencies we mention below.

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
* php-mcrypt (for AES encryption support in backups)

All the other distro-specific dependencies are generated in the build process, 
so you do not need to worry about them when downloading the tarball or cloning 
the development repo for generating a customized build. All the backend 
dependencies, however, must be configured. It is out of the scope of this document
how to configure the backend. Follow the Drupal.org documentation, if you need
help `getting started <https://www.drupal.org/documentation/install/>`_.

Quick Install
-------------

If you have the backend already set-up (including ''Drush''), you can quickly install PECE following these steps:

1. Clone the ''pece-distro'' repostory:

:: 

    git clone https://github.com/PECE-project/pece-distro.git
    
    
2. Create a database:

::
    
    mysql -u $YOUR_USER -p -e "CREATE DATABASE $YOUR_DB_NAME CHARACTER SET utf8 COLLATE utf8_general_ci;"

    
3. Copy the database schema (.sql) file to your database:

::

    drush sql-cli < pece-drupal/database.sql
    
    
4. Edit the file ''sites/default/settings.php'' with your DB credentials accordingly

The default passwd for the admin user is ''peceadmin'', **make sure to change it** after the first log-in.
Also, make sure to set the **permissions** properly. We cannot emphasize this enough. 
The `official Drupal documentation explains <https://www.drupal.org/documentation/install>`_ how to do so, 
if you have questions on how to proceed.


Development 
-----------

PECE development is currently happening on Github but we are planning to move to Drupal.org
soon. To get started, you need to clone the development repository:

::

    https://github.com/PECE-project/drupal-pece.git

This repository contains the source files in the ``src`` directory, which is basically
everything you will need from us to build, update, and extend an existent version of
distro. This  process depends on Kraftwagen and its workflow, so `follow their 
guide <http://kraftwagen.org/get-started.html>`_ if you need help on how to set it up for an existent Drupal installation.

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

There are special dependencies if you are planning to use Nginx as the webserver.
These dependencies include:

* nginx-extras
* php5-dev
* uploadprogress (installed via PHP ``pear``)

These are necessary for having the upload progress bar working on Nginx, but this
step is not mandatory. Configuring Nginx is out of the scope of this document. Follow 
`Perusio\'s instructions <https://github.com/perusio/drupal-with-nginx>`_ for more information 
on getting Drupal 7 to perform better (than Apache2) with Nginx.


Further Information
-------------------
For further information on the specifics of the Drupal installation process, please
`read the official Drupal documentation
<https://www.drupal.org/documentation/install>`_.

PECE version 1.0 does not yet have a pre-configured virtual machine image
distribution. It is in our plans to prepare one to make the lives of our
colleagues in the humanities and social sciences easier. Visit the **Contributors
Guide** page to learn how you can contribute to the project!
