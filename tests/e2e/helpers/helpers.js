//
// Helper Funcions
//

var path = require('path')
  , EC = protractor.ExpectedConditions;

// Used for non-angular apps
browser.ignoreSynchronization = true;

function selectDropdownbyNum(element, optionNum) {
  if (optionNum) {
    var options = element.findElements(by.tagName('option'))
      .then(function(options){
        options[optionNum].click();
      });
  }
}

function selectAutocompleteReference(element, text) {
  signatureInput = element;
  signatureInput.click()
  signatureInput.clear()
  signatureInput.sendKeys(text);
  browser.wait(EC.visibilityOf(element(by.cssContainingText('.reference-autocomplete', text))), browser.params.timeoutLimit);
  element(by.cssContainingText('.reference-autocomplete', text)).click();
}

function clickElement(id) {
  return element(by.id(id)).click();
}

function addMedia(mediaButtonId, mediaFile) {
  // Click on media browse button.
  // clickElement(mediaButtonId);

  return browser.switchTo().frame('mediaBrowser').then(function() {
    var mediaElement = element.all(by.id('edit-upload-upload')).last()
      , nextButton = element(by.css('#edit-next'))
      , saveButton = element(by.css('#edit-submit'))
      , mediaInput = path.resolve(__dirname, '../assets/' + mediaFile);

    // Upload media.
    return mediaElement.sendKeys(mediaInput).then(function() {
      return nextButton.click().then(function() {
        return saveButton.click().then(function() {
          return browser.switchTo().defaultContent();
        });
      });
    });
  });
}

// Exposed helper methods.
module.exports = {
  clickElement: clickElement
  , addMedia: addMedia
}
