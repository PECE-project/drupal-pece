/**
* @file authentication.page.js
*/

// This is a sample page file where you will find generic methods to use with drupal.
var AuthenticationPage = function () {

  // Define authentication attributes.
  this.usernameField = element(by.css('input#edit-name'));
  this.passwordField = element(by.css('input#edit-pass'));
  this.loginButton = element(by.css('input#edit-submit'));
  this.loggedIn = element(by.css('body.logged-in'));

  // Define authentication methods.
	this.get = function () {
    browser.get('user');
  };

  this.login = function (user, password) {
    this.get();
    browser.driver.sleep(100);
    this.usernameField.sendKeys(user);
    browser.driver.sleep(100);
    this.passwordField.sendKeys(password);
    browser.driver.sleep(100);
    this.loginButton.click();
  }

  this.logout = function () {
    browser.get('user/logout');
    browser.driver.sleep(1000);
  }

};

module.exports = new AuthenticationPage();
