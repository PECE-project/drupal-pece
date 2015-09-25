/**
* @file structured.analytics.page.js
*/

var helpers = require('../helpers/helpers');
var AllPages = require('./all.page');
var path = require('path');
var EC = protractor.ExpectedConditions;

var StructuredAnalyticsPage = function() {

  // Define text artifact page object attributes.
  this.mainElements = {
    // Form main elements.
    titleField: $('#taxonomy-form-term #edit-name'),
    descriptionField: $('#taxonomy-form-term  #edit-description-value'),
    addQuestionSet: $('.entityconnect-add input'),
  };

  this.publishButton = $('#edit-submit');

  this.checkMandatoryFields = function () {
    this.publishButton.click();
    AllPages.SamplePage.checkMessage('Title field is required.');
  };

  this.checkMainElementsPresence = function () {
    for (var key in this.mainElements) {
      expect(this.mainElements[key].isPresent()).toBe(true);
    }
  };

  this.add = function(title) {
    AllPages.AnalyticPage.get();
    this.mainElements.addQuestionSet.click();
    browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.descriptionField.sendKeys('Question set description');
    this.publishButton.click();
    browser.wait(EC.visibilityOf(AllPages.AnalyticPage.mainElements.questionSetField), browser.params.timeoutLimit);
  };

};

module.exports = new StructuredAnalyticsPage();
