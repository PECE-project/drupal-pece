/**
* @file artifact.pdf.page.js
*/

var helpers = require('../helpers/helpers')
  , SamplePage = require('./sample.page')
  , path = require('path')
  , EC = protractor.ExpectedConditions;

var ArtifactPdfPage = function () {

  // Define PDF artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField         : element(by.css('#pece-artifact-pdf-node-form #edit-title')),
    uriField           : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-uri-und-0-value')),
    fieldsiteField     : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    pdfField           : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-media-pdf-und-0')),
    contributorsFields : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField          : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-tags-und')),
    licenceField       : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-license-und-0-licence')),
    authorsField       : element(by.css('#pece-artifact-pdf-node-form #edit-field-pece-authors-und')),

    // Right side form elements.
    publishedOnDateField   : element(by.css('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-log')),
    authorField            : element(by.css('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-name')),
    dateField              : element(by.css('#pece-artifact-pdf-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))
  };

  this.browseButtonId = 'edit-field-pece-media-pdf-und-0-browse-button';
  this.publishButton  = element(by.css('#pece-artifact-pdf-node-form #edit-submit'));

  //Define pdf pageobject methods.
  this.get = function () {
    browser.get('node/add/pece-artifact-pdf');
  };

  this.checkMandatoryFields = function () {
    this.clearMandatoryFields();
    browser.wait(EC.visibilityOf(this.publishButton), browser.params.timeoutLimit);
    this.publishButton.click();
    browser.wait(EC.visibilityOf(SamplePage.body), browser.params.timeoutLimit);
    expect(SamplePage.body.getText()).toContain('Title field is required.');
    expect(SamplePage.body.getText()).toContain('Author field is required.');
    expect(SamplePage.body.getText()).toContain('PDF Document field is required.');
    expect(SamplePage.body.getText()).toContain('URI field is required.');
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

  this.checkFileFormat = function () {
      var fileFormats = element(by.css('#edit-upload-ajax-wrapper .description'))
      , fileFormatsIsVisible = EC.visibilityOf(fileFormats);

    browser.wait(fileFormatsIsVisible, browser.params.timeoutLimit);
    expect(fileFormats.getText()).toContain('pdf');
  };

  this.accessMediaBrowser = function () {
      var browseButton      = element(by.css('.media-widget a.button.browse'))
      , browserBtnIsPresent = EC.visibilityOf(browseButton);

    browser.wait(browserBtnIsPresent, browser.params.timeoutLimit);
    browseButton.click();

    browser.switchTo().frame('mediaBrowser');
  }

  this.addPdf = function (fileName) {
    // Click on media browse button.
    element(by.css('.media-widget a.button.browse')).click();

    return browser.switchTo().frame('mediaBrowser').then(function() {
      var mediaElement = element.all(by.id('edit-upload-upload')).last()
        , nextButton   = element(by.css('#edit-next'))
        , saveButton   = element(by.css('#edit-submit'))
        , mediaInput   = path.resolve(__dirname, '../assets/' + fileName);

        // Upload media.
        return mediaElement.sendKeys(mediaInput).then(function() {
          return nextButton.click().then(function() {
            browser.sleep(3000);
            return saveButton.click().then(function() {
              browser.sleep(1000);
              return browser.switchTo().defaultContent();
            });
          });
        });
    });
  };

  this.getFromLibrary = function (fileName) {

    var library = element(by.css('a#ui-id-2'))
      , libraryIsPresent = EC.visibilityOf(library)
      , sendFileIsPresent = EC.presenceOf(element(by.cssContainingText('a', fileName)))
      , mediaItem = element(by.cssContainingText('.media-item', fileName))
      , submitButton = element(by.css('a.fake-submit'));

    this.accessMediaBrowser();

    browser.wait(libraryIsPresent, browser.params.timeoutLimit);
    library.click();
    mediaItem.click();
    return submitButton.click().then(function () {
      return browser.switchTo().defaultContent();
    });
  };

  this.add = function (title, fileName) {
    browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('uri1');
    this.addPdf(fileName);
  };
};

module.exports = new ArtifactPdfPage();
