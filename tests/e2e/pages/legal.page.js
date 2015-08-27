/**
* @file legal.page.js
*/

var EC = protractor.ExpectedConditions;

var LegalPage = function () {

  this.tosTextarea = element(by.css('#edit-conditions'));
  this.submitButton = element(by.css('input#edit-save'));

  this.get = function () {
    browser.get('admin/config/people/legal');
  };

  this.create = function () {
    EC.visibilityOf(this.tosTextarea, browser.params.timeOutLimit);
    this.tosTextarea.click();
    this.tosTextarea.sendKeys('Lorem Ipsum');
    this.submitButton.click();
  };
};

module.exports = new LegalPage();
