/**
* @file artifact.text.page.js
*/

var helpers = require('../helpers/helpers');
var SamplePage = require('./sample.page');
var path = require('path');
var EC = protractor.ExpectedConditions;

var ArtifactTextPage = function() {

  // Define text artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField: element(by.css('#pece-artifact-text-node-form #edit-title')),
    uriField: element(by.css('#pece-artifact-text-node-form #edit-field-pece-uri-und-0-value')),
    textField: element(by.css('#pece-artifact-text-node-form #edit-body-und-0-value')),
    fieldsiteField: element(by.css('#pece-artifact-text-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    contributorsFields: element(by.css('#pece-artifact-text-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField: element(by.css('#pece-artifact-text-node-form #edit-field-pece-tags-und')),
    licenceField: element(by.css('#pece-artifact-text-node-form #edit-field-pece-license-und-0-licence')),
    authorsField: element(by.css('#pece-artifact-text-node-form #edit-field-pece-authors-und')),

    // Right side form elements.
    publishedOnDateField: element(by.css('#pece-artifact-text-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField: element(by.css('#pece-artifact-text-node-form .radix-layouts-sidebar #edit-log')),
    authorField: element(by.css('#pece-artifact-text-node-form .radix-layouts-sidebar #edit-name')),
    dateField: element(by.css('#pece-artifact-text-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))

  };

  this.pageElements = {
    // Panels layout.
    layoutWrapper: element(by.css('.radix-phelan')),

    visible: {
       // Left side elements.
      titleField: element(by.css('h1')),
      textField: element(by.css('.radix-layouts-column1 .field-name-body')),
      licenceField: element(by.css('.radix-layouts-column1 .field-name-field-pece-license')),

      // Right side form elements.
      createdField: element(by.css('.radix-layouts-column2 .pane-node-created .pane-title')),
      contributorsFields: element(by.css('.radix-layouts-column2 .field-name-field-pece-contributors')),
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

  // Define text pageobject methods.
  this.get = function() {
    browser.get('node/add/pece-artifact-text');
  };

  this.view = function() {
    browser.get('content/text-artifact');
  };

  this.checkMandatoryFields = function() {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('Text field is required.');
    SamplePage.checkMessage('URI field is required.');
  };

  this.clearMandatoryFields = function() {
    browser.wait(EC.visibilityOf(this.mainElements.authorField), browser.params.timeoutLimit);
    this.mainElements.authorField.clear();
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

  this.add = function(title, text) {
    browser.wait(EC.visibilityOf(this.mainElements.uriField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('texturi1');
    this.mainElements.textField.sendKeys(text);
    $('#edit-field-permissions-und-private').click();
    // @TODO: Discovery why the below two lines are comented.
    // this.mainElements.tagsField.sendKeys('foo');
    // this.mainElements.authorsField.sandKeys('John Do');
    
    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript("jQuery('#edit-submit').click()");
  };
};

module.exports = new ArtifactTextPage();
