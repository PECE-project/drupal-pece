############### 
Installing PECE 
###############

PECE is a Free Software-based Drupal distribution, therefore the `standard
installation procedure for Drupal 7 <https://www.drupal.org/requirements>`_
applies to PECE with a few extra dependencies. 

The following instructions have been tested on a Debian 8 (jessie) server, but
they are not OS-dependent.  PECE should run on any system supported by Drupal 7.
PECE has been tested in virtual machines with 256M allocated for PHP, being 128M
the recommendated minimum for Drupal 7 distributions. Your configuration, of 
course, may vary considerably depending on the usage you are making of the 
platform. Refer to our data management guidelines under the "sustainability" 
section to learn about the recommendated minimum specs for your servers. 


Downloading the Distro 
----------------------

Our distribution is currently being developed on Github. You can obtain the most
updated version following the link "Releases" on the project's git repository:

::
  
    https://github.com/PECE-project/pece-distro

Alternatively, you can obtain the source code and build the distro yourself if
you intend to help our team by fixing bugs and extending the platform for your
research purposes:

::

    git clone https://github.com/PECE-project/drupal-pece.git

If you are a developer who wants to contribute to PECE, you will need to follow
special instructions to install and configure the tools for building the distro.
Consult the sub-section `Setting up the Development Environment`_ below for more 
information.


Dependencies 
------------

PECE has extra dependencies in addition to the ones you will need for Drupal 7
core:

* cURL 
* php-mcrypt (for AES encryption support in backups and user passwords) 
* php-ssh2 (for backup SFTP support, installed via PHP ``pear``)


Quick Install 
-------------

If you have the server backend already set-up, you can quickly install PECE following
these steps:

1. Clone the ''pece-distro'' repostory:

:: 

    git clone https://github.com/PECE-project/pece-distro.git
    

2. Create an empty database:

::
    
    mysql -u $YOUR_USER -p -e "CREATE DATABASE $YOUR_DB_NAME CHARACTER SET utf8 COLLATE utf8_general_ci;"


Proceed to the URL in which your Drupal will reside, i.e.
``https://worldpece.org``. From there, you can install PECE like any other
Drupal site. Follow the Drupal.org `official documentation if you need
further help <https://www.drupal.org/documentation/install/>`_. In the section
`Troubleshooting`_ below we describe common issues users have when trying to
install PECE without the proper backend dependencies, configurations, and
permissions.

**One important note:** please, make sure to set the **permissions** on the
filesystem properly. We cannot emphasize this enough.  The `official Drupal
documentation explains <https://www.drupal.org/node/244924>`_ how to do so, if
you have questions.


Setting up the Development Environment 
--------------------------------------

PECE development is currently being conducted on Github, but we are planning to
move to Drupal.org soon. To get started, you need to clone the **development**
repository:

::

    git clone https://github.com/PECE-project/drupal-pece.git

This repository contains the source files for PECE in the ``src`` directory,
which has basically everything you need from us to extend, build, deploy the 
current version of the distro.  But, after cloning the repo, you are not done
quite yet... you need to install and configure the development environment
dependencies, following the steps we describe below.

PECE development is made easy by using the following software projects:

- `Node.js <https://nodejs.org/en/>`_ JavaScript runtime;
- `Gulp <http://gulpjs.com/>`_ task runner;
- `Drush <http://docs.drush.org/>`_ command line interface;
- `Kraftwagen <http://kraftwagen.org/>`_ Drush extension;

Keep in mind that these are prerequisites for the **development environment** of
the PECE project, not for the production software. In other words, you
will not need to follow these instructions if you are only interested in installing
and running PECE, even though Drush and Kraftwagen are useful tools for 
managing and updating any Drupal site. 


Installing Node.js 
^^^^^^^^^^^^^^^^^^

We strongly suggest the usage of `nvm <https://github.com/creationix/nvm>`_ to
install Node.js on your development machine. You must have Node.js version 4.x.x
and *npm* version 3.x.x, at least.
 
1. To install ``nvm`` run the following on you terminal:

::

    curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.0/install.sh | bash


After doing so, you will probably have to open a new terminal to have ``nvm``
available as a command. Visit `nvm's official installation guide
<https://github.com/creationix/nvm#install-script>`_ if you have further questions.

2. To install Node.js version 4.x.x run the following on you terminal:

:: 

    nvm install 4.x.x 
    nvm use 4.x.x


Alternatively, you can first clone this repository, change to it's directory,
and run ``nvm install``. The file ``.nvmrc`` will inform ``nvm`` which version
of Node.js it should install and automatically set it as currently version to
use.

3. To install the required version of ``npm`` you must run the following on your
terminal:

:: 

    npm install -g npm@3.x.x


To check if everything went smoothly, run the following on your terminal:

::

    node --version # should echo a number starting with 4 
    npm --version # should echo a number starting with 3


Installing Gulp 
^^^^^^^^^^^^^^^

Even though Gulp is not a hard requirement for installing PECE's development
version, it is currently the main tool for running common tasks which are
inconvenient if not automated. We strongly suggest for you to install it to 
help the installation process and avoid mistakes. Keep in mind that the following
guide will use Gulp. Consider taking a look at the full list of the available tasks
under ``gulp/tasks/README.md``.

Gulp is a Node.js package that provides an executable, and can be easily
installed with the following command:

::

    npm install -g gulp


After running the command, ``gulp`` should be available in your terminal. If you
find any trouble, please refer to Gulp's `official installation guide
<https://github.com/gulpjs/gulp/blob/master/docs/getting-started.md>`_.


Installing Drush 
^^^^^^^^^^^^^^^^

Drush is an amazing tool. Even if you are not interested in helping to develop
PECE, we highly recommend the installation of it for regular maintanence tasks
of your Drupal instance. 

To properly install, Drush please follow the `official installation guide
<http://docs.drush.org/en/master/install/>`_.


Installing Kraftwagen 
^^^^^^^^^^^^^^^^^^^^^

Kraftwagen provides an `official installation guide
<http://kraftwagen.org/get-started.html#installation>`_. Currently, we
use a forked version of the project. You can still follow the instructions on 
the official installation guide, but the ``git clone`` should
come from `Taller's fork
<https://github.com/TallerWebSolutions/kraftwagen/tree/local_workflow_improvements>`_,
using the **local_workflow_improvements** branch.

These are the steps to install kw using the terminal:

1. Move to Drush install directory.

::

    cd ~/.drush


2. Clone Taller's forked version of Kraftwagen.

::

    git clone -b local_workflow_improvements --single-branch git://github.com/TallerWebSolutions/kraftwagen.git


3. Let Drush know you've installed a new module.

::

    drush cc drush


Using Kraftwagen is an important part of the build process. Please make sure you
understand its concepts before proceding to the next steps.


Installing Development Dependencies 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

PECE dependends on various Node.js packages, which help to build PECE, plus
Bower packages, which are used for front-end libraries. To install all these
dependencies you can run the following:

::

    npm install


After installing Node.js dependencies, ``npm`` will automatically perform Bower
install.


Buidling PECE 
^^^^^^^^^^^^^

Kraftwagen, the tool behind PECE's building system, relies on the concept of
different **environments** upon building. The two available environments are:

- **Production**
- **Development**

During the installation process, the environment set-up will be responsible for
enabling/disabling specific modules. Furthermore, using the **development**
environment will also cause for the directory structure to use the **src**
directory linked to **pece** Drupal profile, inside Drupal's root directory. In
practical terms, this means that you can actively engage development using this
directory without having to build everytime you change something. This technique
was introduced as a `pull-request
<https://github.com/kraftwagen/kraftwagen/pull/46>`_ to the Kraftwagen project.

Kraftwagen provides many commands through the drush interface. We encapsulate
some of them inside ``gulp tasks`` with the intent to make building and
configuring easier.

1. Setup the Kraftwagen workspace:

::

    gulp setup


You'll then be prompted to define the environment (defaults to **production**) and the
posterior database configuration.

The database configuration provided here is only used to connect to the
database, not to create it. Before proceeding with the install you should
make sure you create the database and make it properly available via the
settings provided on this step.

2. Download Drupal and its contributed modules:

::

    gulp build 


3. Configure the Web Server

Now you should have the directory **build** already created as Drupal's root
directory. You should then just go ahead and configure Apache, Nginx, or whichever 
HTTP server you find best. Remember to point the site's root directory to the
**build** directory, not to the cloned repository's root.

PECE is media-intensive, which means it will demand serving large binary files
from your server. For this reason, we recommend using Nginx and php5-fpm with
specific customizations to serve files much faster to your users.
Configuring Nginx is out of the scope of this document, but there is plenty of
information on it. If you want to use the configuration we recommend, copy and
customize the config files from `Perusio's instructions
<https://github.com/perusio/drupal-with-nginx>`_ according to your specific
back-end set-up.

4. Installing Drupal

There are currently two methods for installing PECE: via command-line or using 
the browser.

4.1 Using the Browser

In your browser, access the URL ``/install.php`` preceded by the domain serving
the site. The install process is self-explanatory. Keep in mind it takes a while
to finish (up to 30 minutes on low-end server configurations).

4.2 Using the Command Line

There is a one-command install available through Gulp. Keep in mind that this
will erase any currently available data on the database configured in the step

To proceed, run the following:

::

    gulp site-install


If the user running the Gulp task differs from the user running the server, you
will need to redo step 3 to make sure proper permissions to manage files are
set-up.

5. Adding Demo Content 

This is useful for testing purposes, therefore this is an optional step. 
PECE comes with a script to add some testing content. To execute it, run:

::

   gulp demo

Alternatively, you can execute it in your browser by accessing ``Configuration >
Development > PECE Demo`` (or ``/admin/config/development/pece/demo``). This
path will only be available if you configure the environment to **development**
or if you enable the ``pece_demo`` module.


Post-Install Instructions 
-------------------------

OK, so now you have your PECE instance up and running, but you are not yet done!
There are specific configurations you need to do using the admin interface.
Further configuration is needed because these are specific settings for each
PECE installation and use-case.

0. **Basic site info**: first things first, you need to provide the basic
information about your site before you go live. Go to "Administration »
Configuration » System » Site information" and fill out the information about
your site name, the basic admin password, contact, timezone and other relevant
info. 

1. **Customizing the PECE theme**: we will make this easier for you in the near
future, but for now you have to change the the file ``logo.png`` under 
``profiles/pece/themes/pece_scholarly_lite/logo.png`` and tweak the main CSS
file to change the basic colors of the PECE theme.

2. **Uploading your "Terms of Service":** go to "Administration » Configuration
» People » Legal" and click "Add T&C", then fill-out the boxes with your custom
text to be displayed to every user who requests an account on the system. You
may ask: why is there not a default "Terms of Service"? Because... the text
really depends on the way you are using PECE, so our legal documents won't not
suit your case, you need to craft your own text according to the usage you are
making of PECE. **We are not (cannot and should not be) responsible for any use
authorized researchers or any other person make of the platform.** Please, refer
to our section on "Legal Documents" for more information about the software
licenses we use for the PECE project (and for the Free Software technology we use
from the Drupal project).

3. **Setting up AES**: it is very important that you generate, secure, and use
your own encryption keys. To config AES, go to: "Administration » Configuration
» System » AES settings".  Make sure to point to a secure directory **outside
the webroot where PECE is installed** to store your key and make it read-only
(to the owner of the httpd service), instead of having it stored in the database
(which tends to be a much less secure option).

4. **Perma.cc:** PECE comes pre-shipped with Amber, so if you have an account on
Perma.cc you can set PECE up to use it an store your snapshots there. This is
the way to go when it comes to long-term preservation of content for scholarly
purposes. Go to "Administration » Configuration » Content authoring » Amber" and
select "perma.cc" as alternate backend and provide your API key in the text
field below. Done! You are storing "PECE Website" link artifacts, hopefully, for
many future anthropological lives and times now.

5. **Backup:** as explained in our data management guidelines, PECE is configured
to automatically generate backups. You should, however, revise the settings and
set-up a SFTP connection to transfer your backup to another server and ensure
that you have extra security when storing your encrypted backups. First, revise 
the settings we provided, changing whatever you think is needed (say, the most
convenient time, when the site is not being used, to generate the backup). Go to
"Configuration » System » Backup and Migrate" to perform this first step. Then,
click on "Destinations" and "Add Destination" to set-up the SFTP connection
with the credentials of your backup server. Please note that you have to use the
port 22 (not 21) and password authentication, since ssh-key authentication is
unfortunately not supported yet.

6. **System Notification**: PECE uses Drupal notification for key events on the
system.  It has to be configured using a regular email address, provided you
have all the mail server information. You just need your SMTP server info and
credentials to get this done.  Go to "Administration » Configuration » System »
SMTP Authentication Support" and provide your STMP server information, including
username and password. Voilà! System notifications are now working for everyone
as described in your data management section on "Notifications".

7. **User Roles:** we provide a basic permission system based on 2 user roles:
Researcher and Colaborator. If you need other user roles, you might need to
extend the module ``pece_access`` which is shipped with the distro to reflect
the changes. By default, there is only one administrator. This is a security
configuration: to have a more secure system, you do not want to give admin 
powers to regular users, so that when one regular user account is compromised, 
the whole system and users' data gets compromised in the process. Not good...


Troubleshooting
---------------

Common issues post-installation include:

* **"Time Out" during installation:** this issue is related to the usage of Drupal distributions in "shared hosting" environments which are very limited in terms of the resources allocated per client / user account. If the installation process is interrupted before it is finished, you will have to check your PHP configuration and increase the memory allocation and timeout configuration for the php scripts with the following directives: ``memory_limit`` and ``max_execution_time`` which can be found in your ``php.ini`` file. After doing so, you should not experience more "timeouts" during installation.


* **Links do not work:** your webserver is not properly configured to support what is called "Clean URLs" on Drupal. Make sure you have your httpd "rewrite" rules properly set-up. This configuration can be done in the vhost file of your nginx configuration, following the `Perusio guide <https://github.com/perusio/drupal-with-nginx>`_ or using the `default.htaccess file that is provided by default by Drupal <https://github.com/PECE-project/drupal/blob/7.x/.htaccess>`_ if you are running Apache.

* **Permission denied when uploading content:** your filesystem permissions must be set accordingly for the ``public`` and ``private`` directories, since PECE uses both extensively. `Follow this official Drupal tutorial <https://www.drupal.org/node/244924>`_ to configure the permissions properly for both directories where you installed PECE.

* **Permission denied when uploading content after configuring filesystem permissions:** make sure your ``/tmp`` is also writable and, if you are on a shared host and cannot have access to it, configure Drupal to point to a temporary directory in your ``system/files`` path. There is a `discussion about this issue on Drupal.org that is helpful <https://www.drupal.org/node/2140629>`_.

* **Cannot create users, server internal error:** in our experience, ``php5-mcrypt`` is probably not installed in your system. Make sure it is properly installed andloaded, by running ``php -m`` in a shell and checking if it is listed.


Further Information 
-------------------

For further information on the Drupal installation process, please `read the official 
Drupal documentation <https://www.drupal.org/documentation/install>`_.

PECE version 1.0 does not yet have a pre-configured virtual machine image
distribution. It is in our plans to prepare one to make the lives of our
colleagues in the humanities and social sciences easier. Visit the
**Contributors Guide** page to learn how you can contribute to the project!

