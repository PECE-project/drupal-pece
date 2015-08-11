/**
* @file people.page.js
*/

var EC = protractor.ExpectedConditions;

var PeoplePage = function () {

  // Define people attributes.
  this.emailField = element(by.css('#edit-mail'));
  this.applyButton = element(by.css('#edit-submit-admin-views-user'));
  this.statusField = element(by.css('#edit-status-1'));
  this.confirmButton = element(by.css('#edit-submit'));

  this.get = function () {
    browser.get('admin/people');
  };

  this.filter = function (email) {
    var isEmailPresent = EC.visibilityOf(this.emailField);

    browser.wait(isEmailPresent, browser.params.timeoutLimit);
    this.emailField.clear();
    this.emailField.sendKeys(email);
    this.applyButton.click();
    browser.driver.sleep(3000);
  };

  this.deleteUser = function (email) {
    var cancelButton = element(by.css('input[value="user_cancel_delete"]'))
      , confirmButton = element(by.css('#edit-submit'))
      , isConfirmPresent = EC.visibilityOf(confirmButton)
      , isCancelPresent = EC.visibilityOf(cancelButton);

    this.get();
    this.filter(email);
    element(by.cssContainingText('a', 'Cancel account')).click();
    browser.wait(isCancelPresent, browser.params.timeoutLimit);
    cancelButton.click();
    browser.wait(isConfirmPresent, browser.params.timeoutLimit);
    confirmButton.click();
    browser.driver.sleep(1000);
  };

  this.edit = function (email) {
    this.get();
    this.filter(email);
    element(by.cssContainingText('a', 'edit')).click();
    browser.driver.sleep(1000);
  };

  this.unblock = function (email) {
    this.edit(email);
    this.statusField.click();
    this.confirmButton.click();
    browser.driver.sleep(1000);
  };

  this.addRole = function (email, roleName) {
    var roleWrapper = element(by.cssContainingText('#edit-roles .form-type-checkbox', roleName))
      , role = roleWrapper.findElement(by.css('input#edit-roles-6'));

    this.edit(email);
    browser.driver.sleep(1000);
    role.click();
    browser.driver.sleep(4000);
    this.confirmButton.click();
  };
};

module.exports = new PeoplePage();
