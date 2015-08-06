/**
* @file fieldnote.page.js
*/

var FieldnotePage = function () {

  // Define fieldnote page object attributes.
  this.mainElements = {

    // Form main elements.
    uriField           : element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-uri-und-0-value')),
    textField          : element(by.css('#pece-artifact-fieldnote-node-form #edit-body-und-0-value_ifr')),
    fieldsiteField     : element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    contributorsFields : element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField          : element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-tags-und')),
    licenceField       : element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-license-und-0-licence')),

    // Right side form elements.
    publishedOnDateField   : element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-log')),
    authorField            : element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-name')),
    dateField              : element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))

  };

  this.editorSelectField = element(by.css('#edit-body-und-0-format--2'));
  this.plaintextOption   = element(by.css('#edit-body-und-0-format--2 option[value="plain_text"]'));
  this.publishButton     = element(by.css('#edit-submit'));

  //Define fieldnote pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-artifact-fieldnote');
  };

  this.checkMainElementsPresence = function () {
    for (var key in this.mainElements) {
      browser.driver.sleep(2000);
      expect(this.mainElements[key].isPresent()).toBe(true);
    }
  };

  this.add = function (fieldNoteText) {
    var EC = protractor.ExpectedConditions
      , uriFieldIsPresent = EC.visibilityOf(this.mainElements.uriField);

    browser.wait(uriFieldIsPresent, browser.params.timeoutLimit);
    this.mainElements.uriField.sendKeys('uri1');
    this.editorSelectField.click();
    this.plaintextOption.click();
    element(by.css('#edit-body-und-0-value')).sendKeys(fieldNoteText);
    this.publishButton.click();
  };

};

module.exports = new FieldnotePage();
