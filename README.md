# Platform for Experimental and Collaborative Ethnography (PECE)

PECE is a Free and Open Source (Drupal-based) digital platform that supports
multi-sited, cross-scale ethnographic and historical research. PECE is built
as a Drupal distribution to be improved and extended like any other Drupal project.

This repository contains the **development code** for PECE. It has work in progress which
is intended to be used by developers to suggest bug fixes and improvements,
as well as a starting point for customizations of the platform. If you are a
developer wishing to contribute to the development process, this is the
repository to use.

If you are an end-user looking for stable PECE releases, please access the repository
[PECE-distro](https://github.com/PECE-project/pece-distro), which contains our
installation package with the latest stable version. If you have general questions about
the platform, please refer to our [complete documentation](https://pece-project.github.io/drupal-pece/).

## Recommended setup

(Some later commands will reference DDEV; substitute the development environment of your choice at your own risk.)

0. [Install Docker](https://ddev.readthedocs.io/en/stable/users/install/docker-installation/) if you have not yet.
1. [Install DDEV](https://ddev.readthedocs.io/en/stable/users/install/ddev-installation/)

You will also need to put your public key on your profile on https://git.drupalcode.org

## Installation quickstart

```bash
git clone git@github.com:PECE-project/drupal-pece.git --branch 2.x
cd drupal-pece
ddev pece-install
```

Note that the "[warning] … was not found" messages are addressed by the necessarily later `content-import-all` step (which is run for you in `pece-install`).

## Usage

The `ddev pece-install` line can be re-run to do a **re-**installation of PECE.
This will wipe out any content and configuration you have.

Broken down into the component steps, get up to speed (destructively) with other developers:

```bash
git pull
ddev composer install
ddev drush -y si pece --existing-config
ddev import-demo-content
ddev import-essential-content
```

## Running tests

### To run behat tests

```shell
ddev exec ./vendor/bin/behat /var/www/html/features
```

To run the tests of only a specific feature:
```shell
ddev exec ./vendor/bin/behat /var/www/html/features/homepage.feature

## Updating Drupal core and contrib

To update Drupal core and contributed modules, make sure your configuration is clean (exported and committed, or imported from an up-to-date and clean git repository) and then run:

```shell
ddev composer update
ddev drush -y updb
ddev drush -y cex
```

And commit any updates Drupal made to configuration as part of the updates (there may be no update hooks that are run, and even if there are some, they may not change configuration.)

## Exporting configuration

```shell
ddev drush -y cex
```

## Exporting and importing content

You can make selected content (including taxonomy terms, blocks, and menu links) part of the default distribution with the [Single Content Sync](https://www.drupal.org/project/single_content_sync) module (that can in fact sync a lot more than one at a time).

For example:

```shell
ddev drush content:export shortcut ../content/essential/
ddev drush content:export menu_link_content ../content/essential/
```

You should be careful though. There are 3 directories under content:
- essential (export content here that is essential and safe to re-import)
- demo (export content here that is only intended to demonstrate curation of featured page elements)
- pre-migrate (export content here that must be imported in order for the migration from Drupal 7 to run properly)

Also note that exporting content locally may not work as expected, especially when it comes to content with images. Therefore, it is recommended that content is exported via the UI from a live site, and ideally one that we expect will be around for a while (worldpece.org may be a good candidate).

Content in the demo and pre-migrate folder should only ever be imported once, usually at the start of the project. It is possible that new demo content is created, and importing new demo content may be useful for existing sites that are not utilizing that content yet. The reason is that content in these folders are expected to be updated, and so re-importing will wipe away those edits.

Content in the essential folder should be safe to re-import. The reason you might want to re-import would be if there are changes made to that content.

## Importing Drupal 7 database to work on migration

```shell
ddev import-db --database=sts7 --file=backups/CFE_20240825b.sql.gz
```

(Change that filename to match the backup you are using, the key info here is targeting the database.)

### Scaffolding files

This project will attempt to keep all of your Drupal Core files up-to-date; the
project [drupal-composer/drupal-scaffold](https://github.com/drupal-composer/drupal-scaffold)
is used to ensure that your scaffold files are updated every time drupal/core is
updated. If you customize any of the "scaffolding" files (commonly .htaccess),
you may need to merge conflicts if any of your modified files are updated in a
new release of Drupal core.

## FAQ

### How can I customize the look and feel?

PECE is based on [Bulma](https://bulma.io/) using [CSS variables](https://bulma.io/documentation/features/css-variables/) plus CSS overrides for lightweight changes, especially to color, (at `/admin/config/development/asset-injector/css`).

### How can I apply patches to downloaded modules?

We use the [composer-patches](https://github.com/cweagans/composer-patches) plugin.

To add a patch to drupal module foobar insert the patches section in the extra
section of composer.json:
```json
"extra": {
    "patches": {
        "drupal/foobar": {
            "Patch description": "URL or local path to patch"
        }
    }
}
```

If the patch URL does not contain the Drupal.org node ID (AKA issue ID

### How do I compile SCSS to CSS?

From `web/themes/custom/peceful`, run `npm run build-bulma` or use this DDEV command to generate the .css file from the .sass file:

```
ddev css
```

Please commit the changes to both, in separate commits.

See more about Bulma's Sass in `web/themes/custom/peceful/README.md`

## Deployment

Deployed to https://demo-pece.agaric.coop/ using Drutopia hosting.

See [DEPLOYMENT.md](DEPLOYMENT.md) for more about deploying.

## License

PECE is licensed to the public under the [General Public License, version 3](https://www.gnu.org/licenses/gpl-3.0.txt) ("GPLv3"). Your use of the software constitutes acceptance of those terms.

Drupal and all drupal.org files are licensed under the [General Public License, version 2](https://www.drupal.org/about/licensing).
