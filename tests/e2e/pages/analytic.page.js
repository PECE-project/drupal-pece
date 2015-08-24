/**
* @file analytic.page.js
*/

var helpers = require('../helpers/helpers')
  , SamplePage = require('./sample.page')
  , path = require('path')
  , EC = protractor.ExpectedConditions;

var AnalyticPage = function () {

  // Define text artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField         : element(by.css('#pece-analytic-node-form #edit-title')),
    uriField           : element(by.css('#pece-analytic-node-form #edit-field-pece-uri-und-0-value')),
    tagsField          : element(by.css('#pece-analytic-node-form #edit-field-pece-tags-und')),

    // Right side form elements.
    publishedOnDateField   : element(by.css('#pece-analytic-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-analytic-node-form .radix-layouts-sidebar #edit-log')),
    authorField            : element(by.css('#pece-analytic-node-form .radix-layouts-sidebar #edit-name')),
    dateField              : element(by.css('#pece-analytic-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))
  };

  this.publishButton = element(by.css('#edit-submit'));

  // Define text pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-analytic');
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

  this.add = function (title) {
    browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('analyticuri1');
    this.publishButton.click();
  };
};

module.exports = new AnalyticPage();
