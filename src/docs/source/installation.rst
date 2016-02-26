###############
Installing PECE
###############

PECE is a Free Software-based Drupal distribution, therefore the standard
installation procedure for Drupal applies to PECE with a few
extra dependencies. The distribution is generated through a ``Makefile`` which
pulls all the dependencies and customizations for PECE.


Obtaining the Distro
--------------------

Our distribution is being distributed as a tarball on Github. You can have
access to the first release, v.1.0, through the link "Releases" on the project's
Github page.

Alternatively, you can obtain the source code and build the distro yourself if
you intend to help our team by fixing bugs and extending the platform for your
research purposes:

::

    git clone https://github.com/PECE-project/drupal-pece.git

Dependencies
------------

PECE has a few extra dependencies in addition to the basic dependencies of
Drupal, which include:

* curl (for the Amber module)
* php-mcrypt library (for AES encryption support)

All the platform-specific dependencies are generated in the build process of
the distro, so you do not need to worry about them when downloading the tarball
or cloning the repository with the source code. All the extra backend
dependencies, however, must be configured by the person who is installing the
platform.


For Developers
--------------

PECE development is happening on Github, but it will soon be transfered
to Drupal.org. You can get started by cloning the following repository:

::

    https://github.com/PECE-project/drupal-pece.git

In order to build the PECE distro from the devevelopment branch, you need to
install the following dependencies:

* Drush
* Kraftwagen
* Node.js

The development branch, ``dev`` contains the following bash scripts which
execute the ''build' and the 'update' processes.

* build.sh
* update.sh

Further Information
-------------------
For further information on the specifics of the installation process, please
`read the official Drupal documentation
<https://www.drupal.org/documentation/install/>`_.

PECE version 1.0 does not yet have a pre-configured virtual machine image
distribution. It is in our plans to prepare one. Visit the **Contributors
Guide** page to learn how you can contribute to the project! 

