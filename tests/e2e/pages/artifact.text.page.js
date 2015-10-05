/**
* @file artifact.text.page.js
*/

var EC         = protractor.ExpectedConditions;

var path       = require('path'),
    helpers    = require('../helpers/helpers'),
    SamplePage = require('./sample.page');

var ArtifactTextPage = function() {

  var formId = '#pece-artifact-text-node-form ';
  // Define text artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField        : $(formId + '#edit-title'),
    uriField          : $(formId + '#edit-field-pece-uri-und-0-value'),
    textField         : $(formId + '#edit-body-und-0-value'),
    fieldsiteField    : $(formId + '#edit-field-pece-fieldsite-und-0-target-id'),
    contributorsFields: $(formId + '#edit-field-pece-contributors-und-0-target-id'),
    tagsField         : $(formId + '#edit-field-pece-tags-und'),
    licenceField      : $(formId + '#edit-field-pece-license-und-0-licence'),
    authorsField      : $(formId + '#edit-field-pece-authors-und'),
    permissionsField  : $(formId + 'input[name="field_permissions[und]"]'),

    // Right side form elements.
    publishedOnDateField  : $(formId + '.radix-layouts-sidebar #edit-pubdate-datepicker-popup-0'),
    createNewRevisionField: $(formId + '.radix-layouts-sidebar #edit-log'),
    authorField           : $(formId + '.radix-layouts-sidebar #edit-name'),
    dateField             : $(formId + '.radix-layouts-sidebar #edit-date-datepicker-popup-0')

  };

  this.pageElements = {
    // Panels layout.
    layoutWrapper: $('.radix-phelan'),

    visible: {
       // Left side elements.
      titleField  : $('h1'),
      textField   : $('.radix-layouts-column1 .field-name-body'),
      licenceField: $('.radix-layouts-column1 .field-name-field-pece-license'),

      // Right side form elements.
      createdField      : $('.radix-layouts-column2 .pane-node-created .pane-title'),
      contributorsFields: $('.radix-layouts-column2 .field-name-field-pece-contributors'),
    },

    hidden: {
      // Right side form elements.
      authorsField    : $('.radix-layouts-column2 .field-name-field-pece-authors'),
      tagsField       : $('.radix-layouts-column2 .field-name-field-pece-tags'),
      fieldsiteField  : $('.radix-layouts-column2 .field-name-field-pece-authors'),
      critCommentField: $('.radix-layouts-column2 .field-name-field-pece-crit-commentary'),
      locationField   : $('.radix-layouts-column2 .field-name-field-pece-location')
    }
  };

  this.editorSelectField = $('#edit-body-und-0-format--2');
  this.plaintextOption = $('#edit-body-und-0-format--2 option[value="plain_text"]');
  this.publishButton = $('#edit-submit');

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
    this.get();
    // browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    browser.sleep(1000);
    browser.sleep(1000);
    browser.sleep(1000);
    this.mainElements.titleField.click();
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('texturi1');
    this.mainElements.textField.sendKeys(text);
    this.mainElements.permissionsField.element(by.css('input[value="open"]')).click();
    // $('#edit-field-permissions-und-open').click();
    // @TODO: Discovery why the below two lines are comented.
    this.mainElements.tagsField.sendKeys('foo');
    this.mainElements.authorsField.sandKeys('John Do');

    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript("jQuery('#edit-submit').click()");
  };
};

module.exports = new ArtifactTextPage();
