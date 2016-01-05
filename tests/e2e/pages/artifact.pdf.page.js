/**
* @file artifact.pdf.page.js
*/

var helpers = require('../helpers/helpers');
var SamplePage = require('./sample.page');
var path = require('path');
var EC = protractor.ExpectedConditions;

var ArtifactPdfPage = function() {

  // Define PDF artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField         : $('#pece-artifact-pdf-node-form #edit-title'),
    uriField           : $('#pece-artifact-pdf-node-form #edit-field-pece-uri-und-0-value'),
    fieldsiteField     : $('#pece-artifact-pdf-node-form #edit-field-pece-fieldsite-und-0-target-id'),
    pdfField           : $('#pece-artifact-pdf-node-form #edit-field-pece-media-pdf-und-0-upload'),
    contributorsFields : $('#pece-artifact-pdf-node-form #edit-field-pece-contributors-und-0-target-id'),
    tagsField          : $('#pece-artifact-pdf-node-form #edit-field-pece-tags-und'),
    licenceField       : $('#pece-artifact-pdf-node-form #edit-field-pece-license-und-0-licence'),
    authorsField       : $('#pece-artifact-pdf-node-form #edit-field-pece-authors-und'),

    // Right side form elements.
    publishedOnDateField   : $('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0'),
    createNewRevisionField : $('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-log'),
    authorField            : $('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-name'),
    dateField              : $('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0')
  };

  this.pageElements = {
    // Panels layout
    layoutWrapper : $('.radix-phelan'),

    visible : {
       // Left side elements.
      titleField   : $('h1'),
      pdfField     : $('.radix-layouts-column1 .field-name-field-pece-media-pdf'),
      licenceField : $('.radix-layouts-column1 .field-name-field-pece-license'),

      // Right side form elements.
      createdField       : $('.radix-layouts-column2 .pane-node-created .pane-title'),
      contributorsFields : $('.radix-layouts-column2 .field-name-field-pece-contributors'),
    },

    hidden: {
      // Right side form elements.
      authorsField     : $('.radix-layouts-column2 .field-name-field-pece-authors'),
      tagsField        : $('.radix-layouts-column2 .field-name-field-pece-tags'),
      fieldsiteField   : $('.radix-layouts-column2 .field-name-field-pece-authors'),
      critCommentField : $('.radix-layouts-column2 .field-name-field-pece-crit-commentary'),
      locationField    : $('.radix-layouts-column2 .field-name-field-pece-location')
    }

  };

  this.browseButtonId = 'edit-field-pece-media-pdf-und-0-browse-button';
  this.publishButton = element(by.css('#pece-artifact-pdf-node-form #edit-submit'));

  // Define pdf page object methods.
  this.get = function() {
    browser.get('node/add/pece-artifact-pdf');
  };

  this.checkMandatoryFields = function() {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('PDF Document field is required.');
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

  this.checkFileFormat = function() {
    var fileFormats = element(by.css('#edit-upload-ajax-wrapper .description'));
    browser.wait(EC.visibilityOf(fileFormats), browser.params.timeoutLimit);
    expect(fileFormats.getText()).toContain('pdf');
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

  this.accessMediaBrowser = function() {
    var browseButton = element(by.css('.media-widget a.button.browse'));
    browser.wait(EC.visibilityOf(browseButton), browser.params.timeoutLimit);
    browseButton.click();
    browser.switchTo().frame('mediaBrowser');
  };

  this.add = function(title, fileName) {
    browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('uri1');
    this.addPdf(fileName);
    $('#edit-field-permissions-und-private').click();

    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript("jQuery('#edit-submit').click()");
  };

  this.addPdf = function(fileName) {
    var mediaElement = element.all(by.id('edit-upload-upload')).last();
    var nextButton = element(by.css('#edit-next'));
    var mediaInput = path.resolve(__dirname, '../assets/' + fileName);

    // Click on media browse button.
    element(by.css('.media-widget a.button.browse')).click();
    browser.switchTo().frame('mediaBrowser');

    // Upload media.
    mediaElement.sendKeys(mediaInput);
    nextButton.click();
    /* The below line is needed because when adding a media
    /* more than one next button is displayed.
    */
    nextButton.click();
    browser.switchTo().defaultContent();
  };
};

module.exports = new ArtifactPdfPage();
