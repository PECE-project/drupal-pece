/**
* @file artifact.image.page.js
*/

var ArtifactImagePage = function () {

  // Define image artifact page object attributes.
  this.mainElements = {

    // Form main elements.
    uriField : element(by.css('#pece-artifact-image-node-form #edit-field-pece-uri-und-0-value')),
    fieldsiteField : element(by.css('#pece-artifact-image-node-form #edit-field-pece-fieldsite-und-0-target-id')),
    imageField : element(by.css('#edit-field-pece-media-image-und-0-upload')),
    contributorsFields : element(by.css('#pece-artifact-image-node-form #edit-field-pece-contributors-und-0-target-id')),
    tagsField : element(by.css('#pece-artifact-image-node-form #edit-field-pece-tags-und')),
    licenceField : element(by.css('#pece-artifact-image-node-form #edit-field-pece-license-und-0-licence')),

    // Right side form elements.
    publishedOnDateField : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-pubdate-datepicker-popup-0')),
    createNewRevisionField : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-log')),
    authorField : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-name')),
    dateField : element(by.css('#pece-artifact-image-node-form .radix-layouts-sidebar #edit-date-datepicker-popup-0'))
  };

  this.image = __dirname + '/../assets/replay_1x.png';
  this.publishButton = element(by.css('#edit-submit'));

  //Define image pageobject methods.
	this.get = function () {
    browser.get('node/add/pece-artifact-image');
  };

  this.checkMainElementsPresence = function () {
    for (var key in this.mainElements) {
      browser.driver.sleep(2000);
      expect(this.mainElements[key].isPresent()).toBe(true);
    }
  };

  this.addImage = function (file) {
    var EC = protractor.ExpectedConditions
      , browseButton = element(by.css('a#edit-field-pece-media-image-und-0-browse-button'))
      , browserBtnIsPresent = EC.visibilityOf(browseButton)
      , library = element(by.css('a#ui-id-2'))
      , libraryIsPresent = EC.visibilityOf(library)
      , uploadFile = element(by.css('input.form-file'))
      , uploadIsPresent = EC.visibilityOf(uploadFile)
      , sendFileIsPresent = EC.presenceOf(element(by.cssContainingText('a', 'replay_1x.png')));

    browser.wait(browserBtnIsPresent, 2000);
    browseButton.click();
    // browser.wait(uploadIsPresent, 5000);

    // var uploadField = element(by.css('input.form-file'));
    // uploadField.sendKeys(file);

    browser.wait(libraryIsPresent, 3000);
    library.click();

    browser.driver.sleep(5000);
    element(by.css('input[name=upload_upload_button]')).click();
    browser.wait(sendFileIsPresent, 5000);
    element(by.css('input#edit-next')).click();
    browser.driver.sleep(1000);
    element(by.css('input#edit-submit')).click();
  }

  this.add = function () {
    browser.driver.sleep(100);
    this.mainElements.uriField.sendKeys('uri1');
    browser.driver.sleep(100);
    this.addImage(this.mainElements.imageField, this.image);
    browser.driver.sleep(100);
    this.publishButton.click();
    browser.driver.sleep(1000);
  };

};

module.exports = new ArtifactImagePage();
