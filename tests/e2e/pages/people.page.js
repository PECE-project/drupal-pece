/**
* @file people.page.js
*/

var PeoplePage = function () {

  // Define people attributes.
  this.emailField = element(by.css('#edit-mail'));
  this.applyButton = element(by.css('#edit-submit-admin-views-user'));

  this.get = function () {
    browser.get('admin/people');
  };

  this.filter = function (email) {
    browser.driver.sleep(1000);
    this.emailField.clear();
    browser.driver.sleep(100);
    this.emailField.sendKeys(email);
    browser.driver.sleep(100);
    this.applyButton.click();
    browser.driver.sleep(3000);
  };

  this.deleteUser = function (email) {
    this.get();
    this.filter(email);
    element(by.cssContainingText('a', 'Cancel account')).click();
    browser.driver.sleep(1000);
    element(by.css('input[value="user_cancel_delete"]')).click();
    browser.driver.sleep(1000);
    element(by.css('#edit-submit')).click();
    browser.driver.sleep(5000);
  };

};

module.exports = new PeoplePage();
