/**
* Helper funcions.
*/

var path = require('path');
var EC = protractor.ExpectedConditions;

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
  browser.wait(element(by.cssContainingText('#autocomplete', text)).isDisplayed());
  element(by.cssContainingText('#autocomplete', text)).click();
}

function clickElement(id) {
  return element(by.id(id)).click();
}

function addMedia(mediaButtonId, mediaFile) {
  var mediaElement = element.all(by.id('edit-upload-upload')).last();
  var nextButton = element(by.css('#edit-next'));
  var saveButton = element(by.css('#edit-submit'));
  var mediaInput = path.resolve(__dirname, '../assets/' + mediaFile);

  // Click on media browse button.
  clickElement(mediaButtonId);
  browser.switchTo().frame('mediaBrowser');

  // Upload media.
  mediaElement.sendKeys(mediaInput);
  nextButton.click();
  saveButton.click();
  browser.switchTo().defaultContent();
}

// Exposed helper methods.
module.exports = {
  clickElement: clickElement,
  selectDropdownbyNum: selectDropdownbyNum,
  selectAutocompleteReference: selectAutocompleteReference,
  addMedia: addMedia
}
