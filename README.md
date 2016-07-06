#Platform for Experimental and Collaborative Ethnography (PECE)  

PECE is a Free and Open Source (Drupal-based) digital platform that supports multi-sited, cross-scale ethnographic and historical research. PECE is built as a Drupal distribution, therefore it can be extended like any other Drupal project.

This repository holds the packaged distribution for PECE adopters. It contains the most updated version of PECE for public use. If you are an end-user who wants to run PECE for your research, this is the right place to get your copy. If you are a developer wishing to contribute to the development process, you must use the [development repository](https://github.com/PECE-project/drupal-pece) instead.

If you have general questions about the platform, please refer to our [official documentation](http://pece.readthedocs.io/en/docs).


## Dependencies

In addition to the [basic Drupal system requirements](https://www.drupal.org/requirements), you will need these extra libraries:

- php5-mcrypt
- php5-curl
- php-ssh2
- cURL

Even though these are not hard dependencies, we highly recommend running your PECE site with following set-up for better security and performance: 

- nginx
- php (>= 5.5)
- php5-fpm
- drush (>= 5.x)
- any *nix OS of your choice


## Installing PECE

After making sure you have all the dependencies configured in your system, PECE can be installed like any other Drupal 7 site. 

First, you need to obtain the installation package:

```$ wget https://github.com/PECE-project/pece-distro/archive/v1.0.tar.gz && tar zxvf v1.0.tar.gz```

Create an empty database and make sure to [configure the directory/file permissions before continuing](https://www.drupal.org/node/244924). Then, proceed with the regular install by accessing /install.php preceded by the URL of your new site (i.e. '''yoursite.org/install.php'''). Alternatively, you can use Drush for your own convenience instead of using the web interface:

```$ sudo drush si pece --account-name=admin --account-pass=YOUR_ADMIN_PASS --db-url=mysql://YOUR_DB_USER:YOUR_DB_USER_PASSWD@locahost/YOUR_DB --notify```

Go grab a cup of coffee or tea, since the installation process might take up to 30 minutes to complete dependending on your server backend. For detailed information on the installation process, please check our [official documentation](http://pece.readthedocs.io/en/docs/installation.html).

## Contributing

There are many ways of contributing to the PECE project. One of them is by reporting bugs or requesting features through Github in our [development repository](https://github.com/PECE-project/drupal-pece). Read our [contributors' guide](http://pece.readthedocs.io/en/docs/contributors.html) for more information about how to contribute code and bug fixes.

## PECE Team

Our official documentation contains the information on authorship for the design and implementation of the platform. Please check the document [PECE Team](http://pece.readthedocs.io/en/docs/team.html) for more information.

## Licensing

All the software code written for PECE is released under the GNU GPL version 3. Access our [legal documents for more information](http://pece.readthedocs.io/en/docs/legal.html). All the documentation for the project is released under CC-BY-SA 4.0 International, unless stated otherwise.

