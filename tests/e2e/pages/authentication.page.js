/**
* @file authentication.page.js
*/

var EC = protractor.ExpectedConditions;

var AuthenticationPage = function() {

  var currentUser = null;

  // Define authentication attributes.
  this.usernameField = $('input#edit-name');
  this.passwordField = $('input#edit-pass');
  this.loginButton   = $('input#edit-submit');
  this.loggedIn      = $('body.logged-in');

  this.login = function (user, password) {
    if (currentUser == user) return;
    if (currentUser) this.logout();

    this.get();
    browser.wait(EC.visibilityOf(this.usernameField), browser.params.timeoutLimit);
    this.usernameField.sendKeys(user);

    this.passwordField.sendKeys(password);
    this.loginButton.click();

    currentUser = user;
  };

  this.logout = function() {
    if (!currentUser) return;
    browser.get('user/logout');
    currentUser = null;
  }

  this.get = function() {
    browser.get('user');
  };

};

module.exports = new AuthenticationPage();
