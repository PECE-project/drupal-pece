/**
 * @file pece.artifact.page.js
 */

var ArtifactPage = function() {

  // Define pece artifacts attributes.
  this.licenseField = element(by.css('#edit-field-pece-license-und-0-licence'));
  this.licenseFieldDefaultValue = element(by.css('#edit-field-pece-license-und-0-licence option:checked'));

  // Define pece artifact methods.
  this.get = function() {
    browser.get('node/add/pece-artifact');
  };

  this.getArtifact = function(node) {
    browser.get('content/' + node);
  };

}

module.exports = new ArtifactPage;
