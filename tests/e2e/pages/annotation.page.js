/**
* @file artifact.image.page.js
*/

var helpers = require('../helpers/helpers');
var SamplePage = require('./sample.page');
var path = require('path');
var EC = protractor.ExpectedConditions;

var AnnotationPage = function() {

  // Define image artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    questionSetField: element(by.css('#pece-annotations-annotate-form-start input[name="struct_analytics"]')),
    questionField: element(by.css('#pece-annotations-annotate-form-second input[name="analytic"]')),
    annotationTextField: element(by.css('#pece-annotations-annotate-form-third #edit-body')),
    tagsField: element(by.css('#pece-annotations-annotate-form-third #edit-field-pece-tags-und')),
    licenceField: element(by.css('#pece-annotations-annotate-form-third #edit-field-pece-license-und-0-licence')),
  };

  this.annotateButton = element(by.css('.annotate-link'));
  this.finishButton  = element(by.css('#pece-annotations-annotate-form-third #edit-submit'));
  this.continueButton = element(by.id('edit-next'));

  this.clickAnnotate = function() {
    browser.wait(EC.visibilityOf(annotateButton), browser.params.timeoutLimit);
    annotateButton.click();
  }

  this.checkNoQuestionSetEntered = function() {
    this.continueButton.click();
    SamplePage.checkMessage('You have to choose at least one of the structured analytics options below or create a new question set by filling the Question set title field.');
  };

  this.checkNoQuestionEntered = function() {
    this.continueButton.click();
    SamplePage.checkMessage('You have to choose at least one of the analytics options below or create a new question by filling the Question title field.');
  };

  // this.add = function(title, fileName) {
    // browser.wait(EC.visibilityOf(this.mainElements.questionSetField), browser.params.timeoutLimit);
    //
    // this.finishButton.click();
  // };

};

module.exports = new AnnotationPage();
