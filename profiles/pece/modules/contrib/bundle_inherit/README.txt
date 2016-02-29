Description:
  The main target of the Bundle Inherit module is to allow users to inherit
  bundles of different entity types from any other bundles of the same entity
  type. Inheritance could be performed while creating new bundle of some entity
  type (for example new content type). There are two types (modes) of inherit
  available:
  - Soft: All field instances from existing (parent) bundle will be cloned and
     attached to the newly created bundle. As for the soft mode it is all.
  - Strict: All field instances from existing (parent) bundle will be cloned and
     attached to the newly created bundle. After that you will not be able to
     directly edit inherited field instances in the children bundles and they
     will be always kept synchronized.

Structure:
  Consist of two modules.
  First module only Provide API for other modules to implement inheritance logic
  on their (or other modules) entity types.
  Second one extends node module and allow end users to inherit new content
  types from already created.

  Support for other entity types (like commerce products, etc) could be easily
  added by writing appropriate module. You can look at Bundle Inherit Node
  module (included in Bundle Inherit module basic package, presented on this
  page) for example of bundle inheritance logic implementation.

Demo
  Demo site: http://demo.etreyd.com/
  Demo login: demo
  Demo password: demo

Module project page:
  http://drupal.org/project/bundle_inherit

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/bundle_inherit

-- MAINTAINERS --

lemark - http://drupal.org/user/317870