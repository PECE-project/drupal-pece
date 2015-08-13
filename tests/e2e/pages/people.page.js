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
    browser.wait(EC.visibilityOf(this.emailField), browser.params.timeoutLimit);
    this.emailField.clear();
    this.emailField.sendKeys(email);
    this.applyButton.click();
  };

  this.deleteUser = function (email) {
    var cancelOption = element(by.css('input[value="user_cancel_delete"]'))
      , cancelButton = element(by.css('#edit-submit'));

    this.get();
    this.filter(email);
    browser.wait(EC.visibilityOf(element(by.cssContainingText('a', 'Cancel account'))), browser.params.timeoutLimit);
    element(by.cssContainingText('a', 'Cancel account')).click();
    browser.wait(EC.visibilityOf(cancelOption), browser.params.timeoutLimit);
    cancelOption.click();
    cancelButton.click();
    // The below line of code is necessary for a later test verification.
    browser.wait(EC.visibilityOf(element(by.css('.messages.status'))), browser.params.timeoutLimit);
  };

  this.edit = function (email) {
    this.get();
    this.filter(email);
    browser.wait(EC.visibilityOf(element(by.cssContainingText('a', 'edit'))), browser.params.timeoutLimit);
    element(by.cssContainingText('a', 'edit')).click();
  };

  // this.unblock = function (email) {
  //   this.edit(email);
  //   this.statusField.click();
  //   this.confirmButton.click();
  // };

  this.addRole = function (email, roleName) {
    var roleWrapper = element(by.cssContainingText('#edit-roles .form-type-checkbox', roleName))
      , role = roleWrapper.findElement(by.css('input#edit-roles-6'));

    this.edit(email);
    browser.wait(EC.visibilityOf(role), browser.params.timeoutLimit);
    role.click();
    browser.wait(EC.visibilityOf(this.confirmButton), browser.params.timeoutLimit);
    this.confirmButton.click();
  };
};

module.exports = new PeoplePage();
