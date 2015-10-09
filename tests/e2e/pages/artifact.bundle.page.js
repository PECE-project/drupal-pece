/**
* @file artifact.website.page.js
*/

var helpers = require('../helpers/helpers');
var SamplePage = require('./sample.page');
var path = require('path');

var ArtifactBundlePage = function() {

  // Define website artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField: element(by.css('#pece-artifact-bundle-node-form #edit-title')),
    uriField: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-uri-und-0-value')),
    artifactsField: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-website-url-und-0-url')),
    fieldsiteField: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    contributorsFields: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-tags-und')),
    licenceField: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-license-und-0-licence')),
    authorsField: element(by.css('#pece-artifact-bundle-node-form #edit-field-pece-authors-und')),

    // Right side form elements.
    publishedOnDateField: element(by.css('#pece-artifact-bundle-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField: element(by.css('#pece-artifact-bundle-node-form .radix-layouts-sidebar #edit-log')),
    authorField: element(by.css('#pece-artifact-bundle-node-form .radix-layouts-sidebar #edit-name')),
    dateField: element(by.css('#pece-artifact-bundle-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))

  };

  this.pageElements = {
    // Panels layout.
    layoutWrapper: element(by.css('.radix-phelan')),

    visible: {
       // Left side elements.
      titleField: element(by.css('h1')),
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

  this.publishButton = element(by.css('#edit-submit'));

  // Define website pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-artifact-bundle');
  };

  this.checkMandatoryFields = function() {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('URI field is required.');
    SamplePage.checkMessage('Artifacts field is required.');
  };

  this.clearMandatoryFields = function() {
    browser.wait(this.mainElements.authorField.isDisplayed());
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

  this.add = function(title) {
    this.get();
    browser.wait(this.mainElements.uriField.isDisplayed());
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('artifactBundleUri');
    $('#edit-field-permissions-und-open').click();

    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript("jQuery('#edit-submit').click()");

    browser.wait(this.pageElements.visible.titleField.isDisplayed());
  };
};

module.exports = new ArtifactBundlePage();
