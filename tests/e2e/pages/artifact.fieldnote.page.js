/**
* @file fieldnote.page.js
*/

var EC = protractor.ExpectedConditions;

var ArtifactFieldnotePage = function() {

  // Define fieldnote page object attributes.
  this.mainElements = {

    // Form main elements.
    uriField: element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-uri-und-0-value')),
    textField: element(by.css('#pece-artifact-fieldnote-node-form #edit-body-und-0-value')),
    fieldsiteField: element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    contributorsFields: element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField: element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-tags-und')),
    licenceField: element(by.css('#pece-artifact-fieldnote-node-form #edit-field-pece-license-und-0-licence')),

    // Right side form elements.
    publishedOnDateField: element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField: element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-log')),
    authorField: element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-name')),
    dateField: element(by.css('#pece-artifact-fieldnote-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))

  };

  this.pageElements = {

    // Panels layout
    layoutWrapper: element(by.css('.radix-phelan')),

    visible: {
      // Left side elements.
      titleField: element(by.css('h1')),
      textField: element(by.css('.radix-layouts-column1 .field-name-body')),
      licenceField: element(by.css('.radix-layouts-column1 .field-name-field-pece-license')),

      // Right side form elements.
      createdField: element(by.css('.radix-layouts-column2 .pane-node-created .pane-title')),
      contributorsFields: element(by.css('.radix-layouts-column2 .field-name-field-pece-contributors'))

    },

    hidden: {

      // Right side form elements.
      authorsField: element(by.css('.radix-layouts-column2 .field-name-field-pece-authors')),
      tagsField: element(by.css('.radix-layouts-column2 .field-name-field-pece-tags')),
      fieldsiteField: element(by.css('.radix-layouts-column2 .field-name-field-pece-authors')),
      critCommentField: element(by.css('.radix-layouts-column2 .field-name-field-pece-crit-commentary')),
      locationField: element(by.css('.radix-layouts-column2 .field-name-field-pece-location'))

    }

  };

  this.editorSelectField = element(by.css('#edit-body-und-0-format--2'));
  this.plaintextOption = element(by.css('#edit-body-und-0-format--2 option[value="plain_text"]'));
  this.publishButton = element(by.css('#edit-submit'));

  // Define fieldnote page object methods.
  this.get = function() {
    browser.get('node/add/pece-artifact-fieldnote');
  };

  this.checkMainElementsPresence = function() {
    for (var key in this.mainElements) {
      expect(this.mainElements[key].isPresent()).toBe(true);
    }
  };

  this.checkPageLayout = function() {
    expect(this.pageElements.layoutWrapper.isPresent()).toBe(true);
  };

  this.checkPageElements = function() {
    for (var key in this.pageElements.visible) {
      expect(this.pageElements.visible[key].isDisplayed()).toBe(true);
    }
    for (var key in this.pageElements.hidden) {
      expect(this.pageElements.hidden[key].isPresent()).toBe(false);
    }
  };

  this.add = function(fieldNoteText) {
    var uriFieldIsPresent = EC.visibilityOf(this.mainElements.uriField);
    browser.wait(uriFieldIsPresent, browser.params.timeoutLimit);
    this.mainElements.uriField.sendKeys('uri1');
    this.mainElements.textField.sendKeys(fieldNoteText);
    $('#edit-field-permissions-und-private').click();

    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript("jQuery('#edit-submit').click()");

    browser.wait(element(by.css('.messages.status')).isDisplayed);
  };

};

module.exports = new ArtifactFieldnotePage();
