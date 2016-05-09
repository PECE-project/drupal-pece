# Platform for Experimental and Collaborative Ethnography (PECE)

PECE is a Free and Open Source (Drupal-based) digital platform that supports
multi-sited, cross-scale ethnographic and historical research. PECE is built
as a [Drupal distribution](https://www.drupal.org/documentation/build/distributions),
therefore it can be extended like any other Drupal project.

This repository holds the **development code** for PECE. It contains work in progress which
is intended to be used by developers to suggest bug fixes or improvements,
as well as a starting point for customizations of the platform. If you are a
developer wishing to contribute to the development process, this is the
repository you must use.

If you are an end-user looking for stable PECE releases, please access the repository
[PECE-distro](https://github.com/PECE-project/pece-distro), which contains our
installation packages with the latest stable versions. If you have general questions about
the platform, please refer to our [complete documentation](http://pece.readthedocs.io/en/docs/).


## Prerequisites

PECE development is made easy by using the following software projects:

- [Node.js](https://nodejs.org/en/) JavaScript runtime;
- [Gulp](http://gulpjs.com/) task runner;
- [Drush](http://docs.drush.org/) command line interface;
- [Kraftwagen](http://kraftwagen.org/) Drush extension;
- [Drupal requirements](https://www.drupal.org/requirements).

Keep in mind that these are prerequisites for the *development environment* of
the PECE project, not for the production-hosted software. In order words, you
will not need to follow these instructions if you are interested in installing
and running PECE. Please, refer to our [official
documentation](http://pece.readthedocs.io/en/docs/installation.html) if you are
looking for instructions for regular PECE installation and usage.

### Installing Node.js

We strongly suggest you use [nvm](https://github.com/creationix/nvm) to install Node.js on your development machine. You must have Node.js version 4.x.x and *npm* version 3.x.x, at least.

**1. To install *nvm*** run the following on you terminal:

```sh
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.31.0/install.sh | bash
```

After doing so, you will probably have to open a new terminal to have *nvm* available as a command. Visit nvm's [official installation guide](https://github.com/creationix/nvm#install-script) if you have any questions.

**2. To install Node.js version 4.x.x** run the following on you terminal:

```sh
nvm install 4.x.x
nvm use 4.x.x
```

Alternatively, you can first clone this repository, change to it's directory, and run `nvm install`. The file ``.nvmrc` will inform *nvm* which version of Node.js it should install and automatically set it as currently version to use.

**3. To install the required version of *npm*** you must run the following on your terminal:

```sh
npm install -g npm@3.x.x
```

To check if everything went smoothly, run the following on your terminal:

```sh
node --version # should echo a number starting with 4
npm --version # should echo a number starting with 3
```

### Installing Gulp

Even though Gulp is not a hard requirement for installing PECE's development
version, it is currently the main tool for running common tasks which are
inconvenient if not automated. We strongly suggest you install it to ease
installation process and avoid mistakes. Keep in mind that the following
[Getting started](#getting-started) guide will use Gulp. Consider having a look at the full [list of the available tasks](gulp/tasks/README.md).

Gulp is a Node.js package that provides an executable, and can be easily installed with the following command:

```sh
npm install -g gulp
```

After doing that, `gulp` command should be available in your terminal. If you find any trouble, please refer to Gulp's [official installation guide](https://github.com/gulpjs/gulp/blob/master/docs/getting-started.md).

### Installing Drush

To properly install Drush please follow the [official installing guide](http://docs.drush.org/en/master/install/).

### Installing Kraftwagen

Kraftwagen also provides an [official installation guide](http://kraftwagen.org/get-started.html#installation). Unfortunutelly, we currently use a forked version of the project. You can still follow the instructions on the official installation guide, but the `git clone` should come from [Taller's fork](https://github.com/TallerWebSolutions/kraftwagen/tree/local_workflow_improvements), on the *local_workflow_improvements* branch.

Terminal steps to install:

1. Move to Drush install directory.

```sh
cd ~/.drush
```

2. Clone the Taller fork version of Kraftwagen.

```sh
git clone -b local_workflow_improvements --single-branch git://github.com/TallerWebSolutions/kraftwagen.git
```

3. Make Drush know you've installed a new module.

```sh
drush cc drush
```

Using Kraftwagen is an important part of the build process. Please make sure you understand its concepts before proceding to the next steps.

## Getting Started

If you follow these instructions will get you a copy of the project up and running on your local machine for development and testing purposes. Proceed to the **Deployment** to learn how to deploy the project on a live system.

### Download

To download the project, simply clone it to your directory of choice as follows:

```sh
git clone git://github.com/PECE-project/drupal-pece.git
cd drupal-pece
```

### Install dependencies

PECE dependends on a bunch of Node.js packages, which will mostly help building PECE, and Bower packages, which are front-end libraries used. To install all these dependencies you can run the following:

```sh
npm install
```

After installing Node.js dependencies, *npm* will automatically perform Bower install.

### Build

Kraftwagen - the tool behind PECE's building system - relies on the concept of different *environments* upon building. The two environments in use are:

- **production**
- **development**

> Onwards in the Drupal installing process, the environment will be responsible for enabling/disabling specific modules. Furthermore, using the *development* environment will also cause for the directory structure to use the *src* directory linked as the *pece* Drupal profile, inside Drupal's root directory - this means you can actively engage development using this directory without having to build every time you change something. This technique was introduced as a [pull-request](https://github.com/kraftwagen/kraftwagen/pull/46) to the Kraftwagen project.

Kraftwagen provides many commands through the drush interface. We encapsulate some of them inside gulp tasks with the intend to ease the building and configuration steps.

To setup the Kraftwagen workspace you can run the following:

```sh
gulp setup
```

You'll then be prompt to define the environment (defaults to production) and the posterior database configuration.

## Running the tests

TODO

## Deployment

Deployments are coordinated among the core developers and designers of PECE and distributed through installation packages in the [production repository of PECE](https://github.com/PECE-project/pece-distro.git).

TODO: explain how to deploy a PECE instance?

## Contributing

Contribution should be done [using pull requests](https://help.github.com/articles/using-pull-requests) to this repository. We keep the `master` branch current with tested, stable code. The branch `dev` is used for the on-going development tasks, new features, and bug fixes.

Our [Contributors' guide](http://pece.readthedocs.io/en/docs/contributors.html) contains all the information you will need to know about the project before submitting your contribution. Please read it before sending us pull requests.

## Authors

Our official documentation contains the information on authorship for the design and implementation tasks of the platform. Please check the document [PECE Team](http://pece.readthedocs.io/en/docs/team.html) for more information.

## License

All the code produced for PECE is released under the GNU GPL version 3. Please, read our [legal documents for more information](http://pece.readthedocs.io/en/docs/legal.html).
