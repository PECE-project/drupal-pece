# Yaml parser

This module will add the spyc-library and provide a simple API to parse YAML from strings or files. It is an api-only module and has no UI. Other modules will depend on this one.

## Installation

1. Copy the modules in sites/all/modules/contrib as usual
2. Download the spyc-library from https://github.com/mustangostang/spyc and place it into `sites/all/modules/libraries`

## Usage

* To parse YAML from a string use the function `yaml_parser_parse_string($string)`
* To parse a YAML-file use the function `yaml_parser_parse_file($filename)`


