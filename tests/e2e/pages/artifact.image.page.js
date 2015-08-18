/**
* @file artifact.image.page.js
*/

var helpers = require('../helpers/helpers')
  , SamplePage = require('./sample.page')
  , path = require('path')
  , EC = protractor.ExpectedConditions;

var ArtifactImagePage = function () {

  // Define image artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField         : element(by.css('#pece-artifact-image-node-form #edit-title')),
    uriField           : element(by.css('#pece-artifact-image-node-form #edit-field-pece-uri-und-0-value')),
    fieldsiteField     : element(by.css('#pece-artifact-image-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    imageField         : element(by.css('#pece-artifact-image-node-form #edit-field-pece-media-image-und-0-upload')),
    formatField        : element(by.css('#pece-artifact-image-node-form #edit-field-pece-file-format-und-0-value')),
    contributorsFields : element(by.css('#pece-artifact-image-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField          : element(by.css('#pece-artifact-image-node-form #edit-field-pece-tags-und')),
    licenceField       : element(by.css('#pece-artifact-image-node-form #edit-field-pece-license-und-0-licence')),
    authorsField       : element(by.css('#pece-artifact-image-node-form #edit-field-pece-authors-und')),

    // Right side form elements.
    publishedOnDateField   : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-log')),
    authorField            : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-name')),
    dateField              : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))
  };

  this.browseButtonId = 'edit-field-pece-media-image-und-0-browse-button';
  this.publishButton  = element(by.css('#pece-artifact-image-node-form #edit-submit'));

  //Define image pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-artifact-image');
  };

  this.clearMandatoryFields = function () {
    browser.wait(EC.visibilityOf(this.mainElements.authorField), browser.params.timeoutLimit);
    this.mainElements.authorField.clear();
  };

  this.accessMediaBrowser = function () {
    var browseButton      = element(by.css('.media-widget a.button.browse'));
    browser.wait(EC.visibilityOf(browseButton), browser.params.timeoutLimit);
    browseButton.click();

    browser.switchTo().frame('mediaBrowser');
  }

  this.checkMandatoryFields = function () {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('Image field is required.');
    SamplePage.checkMessage('URI field is required.');
  };

  this.checkMainElementsPresence = function () {
    for (var key in this.mainElements) {
      expect(this.mainElements[key].isPresent()).toBe(true);
    }
  };

  this.checkFileFormat = function () {
    var fileFormats = element(by.css('#edit-upload-ajax-wrapper .description'));
    browser.wait(EC.visibilityOf(fileFormats), browser.params.timeoutLimit);
    expect(fileFormats.getText()).toContain('png gif jpg jpeg svg');
  };

  this.addImage = function (fileName) {
    var mediaElement = element.all(by.id('edit-upload-upload')).last()
      , nextButton   = element(by.css('#edit-next'))
      , saveButton   = element(by.css('[value="Save"]'))
      , mediaInput   = path.resolve(__dirname, '../assets/' + fileName);

    // Click on media browse button.
    element(by.css('.media-widget a.button.browse')).click();
    browser.switchTo().frame('mediaBrowser');

    // Upload media.
    mediaElement.sendKeys(mediaInput);
    nextButton.click();
    browser.wait(EC.visibilityOf(saveButton), browser.params.timeoutLimit);
    saveButton.click();
    browser.switchTo().defaultContent();
  };

  this.add = function (title, fileName) {
    browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('uri1');
    this.addImage(fileName);
    // this.mainElements.formatField.sendKeys('jpg');
    // this.mainElements.authorsField.sendKeys('Other author, Another Author');
    this.publishButton.click();
  };
};

module.exports = new ArtifactImagePage();
