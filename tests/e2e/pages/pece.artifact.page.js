/**
 * @file pece.artifact.page.js
 */

var PeceArtifactPage = function() {

  // Define pece artifacts attributes.
  this.licenseField = element(by.css('#edit-field-pece-license-und-0-licence'));
  this.licenseFieldDefaultValue = element(by.css('#edit-field-pece-license-und-0-licence option:checked'));

  // Define pece artifact methods.
  this.get = function() {
    browser.get('node/add/pece-artifact');
  };
  
}

module.exports = new PeceArtifactPage;
