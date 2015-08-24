/**
* @file structured.analytics.page.js
*/

var helpers = require('../helpers/helpers')
  , SamplePage = require('./sample.page')
  , path = require('path')
  , EC = protractor.ExpectedConditions;

var StructuredAnalyticsPage = function () {

  // Define text artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField         : element(by.css('#pece-structured-analytics-node-form #edit-title')),
    questionsField     : element(by.css('#pece-structured-analytics-node-form #edit-field-pece-analytics-und-0-target-id')),

    // Right side form elements.
    publishedOnDateField   : element(by.css('#pece-structured-analytics-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-structured-analytics-node-form .radix-layouts-sidebar #edit-log')),
    authorField            : element(by.css('#pece-structured-analytics-node-form .radix-layouts-sidebar #edit-name')),
    dateField              : element(by.css('#pece-structured-analytics-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))
  };

  this.publishButton     = element(by.css('#edit-submit'));

  // Define text pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-structured-analytics');
  };

  this.checkMandatoryFields = function () {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('URI field is required.');
    SamplePage.checkMessage('Author field is required.');
  };

  this.clearMandatoryFields = function () {
    browser.wait(EC.visibilityOf(this.mainElements.authorField), browser.params.timeoutLimit);
    this.mainElements.authorField.clear();
  };

  this.checkMainElementsPresence = function () {
    for (var key in this.mainElements) {
      expect(this.mainElements[key].isPresent()).toBe(true);
    }
  };

  this.add = function (title, question) {
    browser.wait(EC.visibilityOf(this.mainElements.questionsField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.questionsField.click();
    this.mainElements.questionsField.clear();
    this.mainElements.questionsField.sendKeys(question);
    browser.wait(EC.visibilityOf(element(by.css('.reference-autocomplete'))), browser.params.timeoutLimit);
    element(by.cssContainingText('.reference-autocomplete', question)).click();
    this.publishButton.click();
  };
};

module.exports = new StructuredAnalyticsPage();
