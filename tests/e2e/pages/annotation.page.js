/**
* @file artifact.image.page.js
*/

var EC         = protractor.ExpectedConditions;

var path       = require('path'),
    helpers    = require('../helpers/helpers'),
    SamplePage = require('./sample.page');

var AnnotationPage = function() {

  // Define image artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    questionSetField: $('#pece-annotations-annotate-form-start input[name="struct_analytics"]'),
    questionField: $('#pece-annotations-annotate-form-second input[name="analytic"]'),
    annotationTextField: $('#pece-annotations-annotate-form-third #edit-body'),
    tagsField: $('#pece-annotations-annotate-form-third #edit-field-pece-tags-und'),
    licenceField: $('#pece-annotations-annotate-form-third #edit-field-pece-license-und-0-licence'),
  };

  this.annotateButton = $('.annotate-link');
  this.finishButton  = $('#pece-annotations-annotate-form-third #edit-submit');
  this.continueButton = element(by.id('edit-next'));

  this.clickAnnotate = function() {
    browser.wait(EC.visibilityOf(this.annotateButton), browser.params.timeoutLimit);
    this.annotateButton.click();
  }

  this.checkNoQuestionSetEntered = function() {
    this.continueButton.click();
    SamplePage.checkMessage('You have to choose at least one of the structured analytics options below or create a new question set by filling the Question set title field.');
  };

  this.checkNoQuestionEntered = function() {
    this.continueButton.click();
    SamplePage.checkMessage('You have to choose at least one of the analytics options below or create a new question by filling the Question title field.');
  };

  this.add = function(title, fileName) {
    this.clickAnnotate();
    browser.wait(EC.visibilityOf(this.mainElements.questionSetField), browser.params.timeoutLimit);
    browser.sleep(3000);
    // this.continueButton.click();
    // this.finishButton.click();
  };
};

module.exports = new AnnotationPage();
