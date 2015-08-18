/**
* @file artifact.website.page.js
*/

var helpers = require('../helpers/helpers')
  , SamplePage = require('./sample.page')
  , path = require('path')
  , EC = protractor.ExpectedConditions;

var ArtifactWebsitePage = function () {

  // Define website artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField         : element(by.css('#pece-artifact-website-node-form #edit-title')),
    uriField           : element(by.css('#pece-artifact-website-node-form #edit-field-pece-uri-und-0-value')),
    urlField           : element(by.css('#pece-artifact-website-node-form #edit-field-pece-website-url-und-0-url')),
    fieldsiteField     : element(by.css('#pece-artifact-website-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    contributorsFields : element(by.css('#pece-artifact-website-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField          : element(by.css('#pece-artifact-website-node-form #edit-field-pece-tags-und')),
    licenceField       : element(by.css('#pece-artifact-website-node-form #edit-field-pece-license-und-0-licence')),
    authorsField       : element(by.css('#pece-artifact-website-node-form #edit-field-pece-authors-und')),

    // Right side form elements.
    publishedOnDateField   : element(by.css('#pece-artifact-website-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-artifact-website-node-form .radix-layouts-sidebar #edit-log')),
    authorField            : element(by.css('#pece-artifact-website-node-form .radix-layouts-sidebar #edit-name')),
    dateField              : element(by.css('#pece-artifact-website-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))

  };

  this.publishButton     = element(by.css('#edit-submit'));

  // Define website pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-artifact-website');
  };

  this.checkMandatoryFields = function () {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('URI field is required.');
    SamplePage.checkMessage('URL field is required.');
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

  this.checkUrl = function () {
    this.mainElements.urlField.sendKeys('An invalid url');
    this.publishButton.click();
    SamplePage.checkMessage('Not a valid URL.');
  };

  this.add = function (title, website) {
    browser.wait(EC.visibilityOf(this.mainElements.uriField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('websiteuri1');
    this.mainElements.urlField.sendKeys(website);
    this.publishButton.click();
  };

};

module.exports = new ArtifactWebsitePage();
