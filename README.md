# PECE

Platform for Experimental and Collaborative Ethnography

## Built upon Drupal

PECE is built as a [Drupal distribution](https://www.drupal.org/documentation/build/distributions) and therefore can be extended as any Drupal project can. This repository holds the development code for this project. Also, it is intended to be used by other developers to suggest bug fixes or improvements, as well as the starting point for the customization of the platform.

If you are looking for the installable you should refer to the [PECE project](https://www.drupal.org/project/pece) on Drupal.org.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisities

> Keep in mind that these are prerequisites for the *development environemnt* of the PECE project, not for the production hosted software.

PECE development is made easy by using the following softwares:

- [Node.js](https://nodejs.org/en/) JavaScript runtime;
- [Drush](http://docs.drush.org/) command line interface;
- [Kraftwagen](http://kraftwagen.org/) drush extension;

#### Installing Node.js

We strongly suggest you use [nvm](https://github.com/creationix/nvm) to install Node.js on your development machine. We recommend Node.js version 4.x.x and *npm* version 3.x.x.

> After installing node via *nvm* you can update global *npm* package by running `npm install -g npm@3.x.x`.

##### Installing Node.js dependencies

Run `npm install` inside the project's root directory to download all Node.js dependencies.

#### Installing Drush

To properly install Drush please follow the [official installing guide](http://docs.drush.org/en/master/install/).

#### Installing Kraftwagen

Kraftwagen also provides a [official installation guide](http://kraftwagen.org/get-started.html#installation). Unfortunutelly, we currently use a forked version of the project. You can still follow the instructions on the official installation, but the git clone should come from [TallerWebSolutions/kraftwagen's local_workflow_improvements branch](https://github.com/TallerWebSolutions/kraftwagen/tree/local_workflow_improvements).

> Kraftwagen system is an import part of our building process. Please make sure you understang it's concepts before proceding to the next steps.

### Building

PECE's building process consists of many tasks that automatically install dependencies, compile source assets (such as CSS), and build Drupal dependencies. These tasks as developed using [Gulp](http://gulpjs.com/).

> A full list of the available tasks can be found on the [gulp/TASKS.md](gulp/TASKS.md) file and can be run on their own when desired to perform a single part of the process. To do that, you can install Gulp globally and execute it's tasks directly. The following commands, though, suggest the usage of *npm bin* command to retrieve the locally installed binaries' directory and execute the local Gulp available there after *npm install* was executed.

To build the project, execute the following command on the root directory:

```sh
$(npm bin)/gulp build
```

## Running the tests

TODO

## Deployment

TODO

## Contributing

Contribution should be done [using pull requests](https://help.github.com/articles/using-pull-requests).

## Authors

TODO

## License

TODO

## Acknowledgments

TODO
