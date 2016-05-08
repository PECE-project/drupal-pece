# PECE's Gulp tasks

This is a list of separately available tasks.

## Installing Gulp task runner

To run a task you must use Gulp task runner. When you install the project's Node.js dependencies, Gulp will be installed locally, but no globally available command line interface will be provided. You can either:

#### 1. Install Gulp globally

Simply run in you terminal:

```sh
npm install -g gulp
```

#### 2. Execute Gulp's local executable

Gulp is a direct dependency for the PECE project's. Therefore, after running `npm install` in the project's root a Gulp executable will be available at `node_modules/.bin` directory. You can use it ass follows:

```sh
./node_modules/.bin/gulp [TASK-NAME]
```

#### 3. Execute Gulp's localally with *npm*

Although *npm* does not yet provide an easy way to run locally installed executables (such as [bundler does](http://bundler.io/man/bundle-exec.1.html)), *npm* provides the *bin* command which returns the absolute path to the binaries installed. You can use it to run Gulp tasks as follows:

```sh
$(npm bin)/gulp [TASK-NAME]
```

## Tasks

| Name                 | Description                                                                                                                    | Dependencies                        |
|----------------------|--------------------------------------------------------------------------------------------------------------------------------|-------------------------------------|
| bower:install        | Installs dependencies registered with bower. Usually, refers to JavaScript libraries installed on the default theme directory. |                                     |
| build                | Downloads Drupal modules (using Kraftwagen's build system) and install front-end dependencies.                                 | bower:install, styles, drush:kw-b   |
| drush:kw-b           | Executes `drush kw-b` and install environment based dependencies.                                                                                               |                                     |
| drush:kw-u           | Helper task to run `drush kw-u`.                                                                                               |                                     |
| drush:sample-content | Adds sample content to a fresh install.                                                                                        |                                     |
| drush:si             | Helper task to run `drush si` with PECE's configuration.                                                                       |                                     |
| init                 | One-for-all install method.                                                                                                    | build, drush:kw-i, drush:kw-u       |
| styles               | Compiles Sass stylesheets into CSS.                                                                                            |                                     |
| test:e2e             | Execute end to end tests using Protractor.                                                                                     | webdriver:start                     |
| update               | Helper task to update assets and database.                                                                                     | [drush:kw-u, bower:install], styles |
| watch:styles         | Watch Sass changes and re-compiles into CSS.                                                                                   | styles                              |
| watch                | Helper task to run watcher tasks.                                                                                              | watch:styles                        |
| webdriver:start      | Starts a webdriver instance for usage on e2e tests.                                                                            |                                     |
| webdriver:update     | Updates the selenium standalone provided by Protractor.                                                                        |                                     |
