/**
* @file artifact.video.page.js
*/

var EC         = protractor.ExpectedConditions;

var path       = require('path'),
    helpers    = require('../helpers/helpers'),
    SamplePage = require('./sample.page');

var ArtifactVideoPage = function() {

  var formId = '#pece-artifact-video-node-form ';
  // Define video artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    titleField        : $(formId + '#edit-title'),
    uriField          : $(formId + '#edit-field-pece-uri-und-0-value'),
    videoField        : $(formId + '#edit-field-pece-media-video-und-0-upload'),
    fieldsiteField    : $(formId + '#edit-field-pece-fieldsite-und-0-target-id'),
    contributorsFields: $(formId + '#edit-field-pece-contributors-und-0-target-id'),
    tagsField         : $(formId + '#edit-field-pece-tags-und'),
    licenceField      : $(formId + '#edit-field-pece-license-und-0-licence'),
    authorsField      : $(formId + '#edit-field-pece-authors-und'),

    // Right side form elements.
    publishedOnDateField  : $(formId + '.radix-layouts-sidebar #edit-pubdate-datepicker-popup-0'),
    createNewRevisionField: $(formId + '.radix-layouts-sidebar #edit-log'),
    authorField           : $(formId + '.radix-layouts-sidebar #edit-name'),
    dateField             : $(formId + '.radix-layouts-sidebar #edit-date-datepicker-popup-0')

  };

  this.pageElements = {
    // Panels layout.
    layoutWrapper: $('.radix-phelan'),

    visible: {
       // Left side elements.
      titleField  : $('h1'),
      videoField  : $('.radix-layouts-column1 .field-name-field-pece-media-video video'),
      licenceField: $('.radix-layouts-column1 .field-name-field-pece-license'),

      // Right side form elements.
      createdField      : $('.radix-layouts-column2 .pane-node-created .pane-title'),
      contributorsFields: $('.radix-layouts-column2 .field-name-field-pece-contributors'),
      // @TODO: Create a separete test for validating the annotation list.
      // annotationList    : $('.views-view-annotations-by-user')
    },

    hidden: {
      // Right side form elements.
      authorsField: $('.radix-layouts-column2 .field-name-field-pece-authors'),
      tagsField: $('.radix-layouts-column2 .field-name-field-pece-tags'),
      fieldsiteField: $('.radix-layouts-column2 .field-name-field-pece-authors'),
      critCommentField: $('.radix-layouts-column2 .field-name-field-pece-crit-commentary'),
      locationField: $('.radix-layouts-column2 .field-name-field-pece-location')
    }
  };

  this.browseButtonId = 'edit-field-pece-media-video-und-0-browse-button';
  this.publishButton = $('#pece-artifact-video-node-form #edit-submit');

  // Define video pageobject methods.
  this.get = function() {
    browser.get('node/add/pece-artifact-video');
  };

  this.checkMandatoryFields = function() {
    this.clearMandatoryFields();
    this.publishButton.click();
    SamplePage.checkMessage('Title field is required.');
    SamplePage.checkMessage('Video field is required.');
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
    var fileFormats = $('#edit-upload-ajax-wrapper .description');
    browser.wait(EC.visibilityOf(fileFormats), browser.params.timeoutLimit);
    expect(fileFormats.getText()).toContain('ogv ogg mp4 m4v webm');
  };

  this.accessMediaBrowser = function() {
    var browseButton = $('.media-widget a.button.browse');
    browser.wait(EC.visibilityOf(browseButton), browser.params.timeoutLimit);
    browseButton.click();
    browser.switchTo().frame('mediaBrowser');
  };

  this.add = function(title, fileName) {
    this.get();
    browser.wait(EC.visibilityOf(this.mainElements.titleField), browser.params.timeoutLimit);
    this.mainElements.titleField.sendKeys(title);
    this.mainElements.uriField.sendKeys('uri1');
    this.addVideo(fileName);
    $('#edit-field-permissions-und-private').click();

    // Protractor already scrolled down to click in permission bullet,
    // and can not manage to scroll back up to click in publish
    // button, that's why the script.
    browser.executeScript("jQuery('#edit-submit').click()");
  };

  this.addVideo = function(fileName) {
    var mediaElement = element.all(by.id('edit-upload-upload')).last();
    var nextButton = $('#edit-next');
    var mediaInput = path.resolve(__dirname, '../assets/' + fileName);

    // Click on media browse button.
    $('.media-widget a.button.browse').click();
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

  this.checkAnnotationList = function () {mainElements
    SamplePage.get('/video-artifact');
    expect(this.pageElements.visible.annotationList.isPresent()).toBe(true);
  }
};

module.exports = new ArtifactVideoPage();
