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

(Some later commands will reference DDEV; substitute the development environment

0. [Install Docker](https://ddev.readthedocs.io/en/stable/users/install/docker-installation/) if you have not yet.
1. [Install DDEV](https://ddev.readthedocs.io/en/stable/users/install/ddev-installation/)

## Installation quickstart

```bash
git clone git@github.com:PECE-project/drupal-pece.git --branch 2.x
cd drupal-pece
ddev pece-install
ddev content-import-all
```

Note that the "[warning] … was not found" messages are addressed by the necessarily later `content-import-all` step.

## Usage

Those last two steps of installation can be re-run to do a **re-**install of PECE.
This will wipe out any content and configuration you have.

Broken down into the component steps, get up to speed (destructively) with other developers:

```bash
git pull
ddev composer install
ddev drush -y si pece --existing-config
ddev content-import-all
```

## Updating Drupal core and contrib

To update Drupal core and contributed modules, make sure your configuration is clean (exported and committed, or imported from an up-to-date and clean git repository) and then run:

```
ddev composer update
ddev drush -y updb
ddev drush -y cex
```

And commit any updates Drupal made to configuration as part of the updates (there may be no update hooks that are run, and even if there are some, they may not change configuration.)

### Scaffolding files

This project will attempt to keep all of your Drupal Core files up-to-date; the
project [drupal-composer/drupal-scaffold](https://github.com/drupal-composer/drupal-scaffold)
is used to ensure that your scaffold files are updated every time drupal/core is
updated. If you customize any of the "scaffolding" files (commonly .htaccess),
you may need to merge conflicts if any of your modified files are updated in a
new release of Drupal core.

## FAQ

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

From `web/themes/custom/peceful`, run `npm run build-bulma` or use this DDEV command:

```
ddev css
```

See more about Bulma's Sass in `web/themes/custom/peceful/README.md`

## Deployment

Deploy to https://demo-pece.agaric.coop/ using Drutopia hosting.
