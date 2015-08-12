/**
* @file legal.page.js
*/

var LegalPage = function () {

  this.tosTextarea = element(by.css('textarea#edit-conditions'));
  this.submitButton = element(by.css('input#edit-save'));

  this.get = function () {
    browser.get('admin/config/people/legal');
  };

  this.create = function () {
    this.tosTextarea.sendKeys('Lorem Ipsum');
    this.submitButton.click();
  };
};

module.exports = new LegalPage();
