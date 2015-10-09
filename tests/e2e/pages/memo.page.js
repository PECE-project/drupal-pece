/**
* @file artifact.text.page.js
*/

var EC         = protractor.ExpectedConditions;

var path       = require('path'),
    helpers    = require('../helpers/helpers'),
    SamplePage = require('./sample.page');

var MemoPage = function() {

  var formId = '#pece-memo-node-form ';
  // Define text artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField        : $(formId + '#edit-title'),
    uriField          : $(formId + '#edit-field-pece-uri-und-0-value'),
    textField         : $(formId + '#edit-body-und-0-value'),
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

    layoutWrapper: $('.node-main-content'),

    visible: {
      titleField         : $('h1'),
      textField          : $('.field-name-body'),
      licenceField       : $('.field-name-field-pece-license'),
      commentBox         : $('#comments'),
    },

    hidden: {}
  };

  this.editorSelectField = $('#edit-body-und-0-format--2');
  this.plaintextOption   = $('#edit-body-und-0-format--2 option[value="plain_text"]');
  this.publishButton     = $('#edit-submit');

  // Define text pageobject methods.
  this.get = function() {
    browser.get('node/add/pece-memo');
  };

  this.view = function() {
    browser.get('content/memo');
  };

  this.checkMandatoryFields = function() {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('Author field is required.');
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
    browser.wait(this.pageElements.visible.commentBox.isDisplayed);
    for (var key in this.pageElements.visible) {
      expect(this.pageElements.visible[key].isDisplayed()).toBe(true);
    }
    for (var key in this.pageElements.hidden) {
      expect(this.pageElements.hidden[key].isPresent()).toBe(false);
    }
  };

  this.add = function(title, text) {
    this.get();
    browser.wait(this.mainElements.titleField.isDisplayed);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('memouri1');
    this.mainElements.textField.sendKeys(text);
    element(by.css('input[value="open"]')).click();
    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript('document.querySelector(\'#edit-submit\').click();');
  };
};

module.exports = new MemoPage();
