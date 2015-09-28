/**
* @file authentication.page.js
*/

var EC = protractor.ExpectedConditions;

var AuthenticationPage = function() {

  // Define authentication attributes.
  this.usernameField = $('input#edit-name');
  this.passwordField = $('input#edit-pass');
  this.loginButton   = $('input#edit-submit');
  this.loggedIn      = $('body.logged-in');

  this.login = function (user, password) {
    this.get();
    browser.wait(EC.visibilityOf(this.usernameField), browser.params.timeoutLimit);
    this.usernameField.sendKeys(user);

    this.passwordField.sendKeys(password);
    this.loginButton.click();
  };

  this.logout = function() {
    browser.get('user/logout');
  }

  this.get = function() {
    browser.get('user');
  };

};

module.exports = new AuthenticationPage();
