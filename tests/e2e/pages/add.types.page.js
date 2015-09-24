/**
 * @file add.types.page.js
 */

var AddTypesPage = function () {

  // Define add types attributes.
  this.inheritanceLink = element(by.cssContainingText('.vertical-tabs-list a', 'Inheritance'));
  this.inheritanceCheckBox = element(by.css('#edit-bundle-inherit-inherit'));
  this.bundleInheritParentSelect = element(by.css('#edit-bundle-inherit-parent-type'))

  // Define add types methods.
  this.get = function () {
    browser.get('admin/structure/types/add');
  };
}

module.exports = new AddTypesPage;
