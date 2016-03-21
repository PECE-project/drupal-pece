## Contents of this file

* Introduction
* Installation
* Installing a YAML parser
* API
* Maintainers

## Introduction

This is a tiny bridge module that tries to provide access to an API
function (named `parse_yaml_stream`) to parse a YAML stream.

It is intended as a stopgap until the Drupal 8 [class Yaml][1] is
backported to Drupal 7.

The project also contains a sub-module (named **Parse YAML check**)
that can be used to check if a YAML parser is available.

This is an API module.  Only install it if another module requires it.

## Installation

Install this module as you would normally install a contributed Drupal
module. See: [Installing modules][2] for further information.

If you're not sure that you have a YAML-parser available, enable both
**Parse YAML** and **Parse YAML check**.  Navigate to *Administration
» Configuration » System » YAML check*. If a YAML parser available, it
will output the parsed demo array.  If a parser is not available, it
will tell you that you need to install one.

## Installing a YAML parser

The module relies on one of two external resources for the actual
parsing.  If a PHP function named [`yaml_parse`][3] is available (part
of [php-pecl-yaml][4]), it will use that.  If a function named
`spyc_load` is available (part of a php YAML library called
[Spyc][5]), it will use that.  If neither is available, the API
function will return `FALSE`.

To install [php-pecl-yaml][4], refer to [Installation of PECL
extensions][6] (php.net).  Please note that you probably will need to
install *libYAML* first. After succesfully installing the extension,
add "extension=yaml.so" to php.ini and restart the web server.

To install [Spyc][5], first download the file `spyc-master.zip` from
GitHub by pressing the “Download ZIP” button on the [Spyc project
page][5].  Then unpack this zip-archive in `sites/all/libraries`.
After you've done this, the following path should exist on your site:
`sites/all/libraries/spyc-master/Spyc.php`.

After installing one of these resources, use **Parse YAML check** to
verify that a YAML parser is available, and working.

You should disable **Parse YAML check** after you've verified that a
parser is available.

## API

If you want to make use of this module, first make it a dependency in
your module's `.info`-file.  You do that with the following line:

    dependencies[] = parse_yaml

The module provides this API function:

### parse_yaml_stream

Parses a YAML stream and returns the parsed elements in an array.

    parse_yaml_stream($input)

If no YAML parser is available, it will return FALSE and show the
following in the message area:  
“Parse YAML: Unable to find a YAML parser.”

#### Parameters

**$input**: The YAML stream.

#### Return value

An array with the parsed elements.

## Maintainers

* [gisle](https://www.drupal.org/u/gisle)

Any help with development (reviews, patches) are welcome.

[1]: https://api.drupal.org/api/drupal/core!vendor!symfony!yaml!Yaml.php/class/Yaml/8
[2]: https://drupal.org/documentation/install/modules-themes/modules-7
[3]: http://php.net/manual/en/function.yaml-parse.php
[4]: https://pecl.php.net/package/yaml
[5]: https://github.com/mustangostang/spyc
[6]: http://php.net/manual/en/install.pecl.php
