INTRODUCTION
------------

Whether links fail because of DDoS attacks, censorship, or just plain old link rot, reliably accessing linked content is a problem for Internet users everywhere. The more routes we provide to information, the more all people can freely share that information, even in the face of filtering or blockages. Amber adds to these routes.

Amber automatically preserves a snapshot of every page linked to on a website, giving visitors a fallback option if links become inaccessible. If one of the pages linked to on this website were to ever go down, Amber can provide visitors with access to an alternate version. This safeguards the promise of the URL: that information placed online can remain there, even amidst network or endpoint disruptions.

Lots of copies keeps stuff safe. By default, Amber stores snapshots directly on the host website. But users can choose to store snapshots using a combination of the following third party storage and archiving systems: the Internet Archive, Perma.cc, and Amazon Simple Storage Service (Amazon S3).

Amber is an open source project led by the Berkman Center for Internet & Society (https://cyber.law.harvard.edu). It builds on a proposal from Tim Berners-Lee and Jonathan Zittrain for a "mutual aid treaty for the Internet" that would enable operators of websites to enter easily into mutually beneficial agreements and bolster the robustness of the entire web. The project also aims to mitigate risks associated with increasing centralization of online content.

* For a full description of the module, visit the project page:
  http://amberlink.org/

* To submit bug reports and feature suggestions, or to track changes:
  https://drupal.org/project/issues/amber

REQUIREMENTS
------------

* Drupal 7.x
* PHP 5.3 or higher
* cURL (To see if cURL is installed, go to Administration > Reports > Status Report)

RECOMMENDED MODULES
-------------------

The Libraries module (https://drupal.org/project/libraries) and the AWS PHP library (https://github.com/aws/aws-sdk-php) are required if using AWS to store snapshots.

INSTALLATION
------------

* Install as you would normally install a contributed Drupal module.
* If using AWS to store snapshots, download version 3 of the AWS library from https://github.com/aws/aws-sdk-php and save it in sites/all/libraries/aws

Full installation instructions, as well as a guide for configurations and settings, can be found on the Amber wiki guide (https://github.com/berkmancenter/amber_drupal/wiki).

CONFIGURATION
-------------

* Amber uses a Text Format filter to allow the end user to access snapshots. After enabling the module, go to Administration » Configuration » Content Authoring » Text Formats, and configure each of the text formats that might display links. (Typically this will be "Filtered HTML" and "Full HTML"). Ensure that the "Amber Filter" is enabled, and that it is after the "Convert URLs into links" filter.
* Additional configuration settings are available at Administration » Content Authoring » Amber
* View the snapshots preserved by Amber at Administration » Reports » Amber Dashboard

HOW IT WORKS
------------
When a node is saved, Amber scans all text and Link fields for external links. If an external link is detected, Amber adds the external URL to a list of links for which to create a snapshot.

When cron runs (or on demand), Amber checks whether there are any pending links to create snapshots for. These could be new links, or links for which it's time to update the snapshot. If there are any links to update, Amber uses the cURL library to take a snapshot of the linked content along with any related assets required to display it (such as CSS, images and Javascript). Amber also checks periodically to see if each link for which it has a snapshot is still available.

There are several options for where this snapshot is saved. By default, it will be saved on the local filesystem, under sites/default/files/amber. (There are configuration settings with in Amber to limit the amount of disk space used overall, and for a single snapshot). Alternately, the snapshot can be saved to Perma.cc or the Internet Archive. In these cases Amber doesn't save the file locally, but instead makes an API call to the relevant service requesting that it make a snapshot of the linked content. Finally, the snapshot can be saved to a "bucket" in the cloud using Amazon's Simple Storage Service (AWS S3). This option requires entering valid AWS credentials as part of the Amber configuration. *Amazon charges for this service.*

When a user views a page on the Drupal site, Amber uses a Text Format Filter to detect any external links in the content being displayed. If there are any links for which it has a snapshot, Amber inserts CSS and Javascript to support display of a hover window or popup, depending on the preferences set at Administration » Content Authoring » Amber.


MAINTAINERS
-----------

Current maintainers:
 * Berkman Center for Internet & Society (berkmancenter)
 * Jeffrey Licht (jlicht)

This project has been sponsored by the Berkman Center for Internet & Society (http://cyber.law.harvard.edu).
