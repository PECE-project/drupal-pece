/**
 * @file registration.page.js
 */

// This is a sample page file where you will find generic methods to use with drupal.
var RegistrationPage = function () {

  // Define registration attributes.
  this.usernameField = element(by.css('input#edit-name'));
  this.emailField = element(by.css('input#edit-mail'));
  this.tosField = element(by.css('input#edit-legal-accept'));

  // Define authentication methods.
  this.get = function () {
    browser.get('user/register');
  };

  this.register = function (user, email, tos) {
    this.get();
    this.usernameField.sendKeys(user);
    this.emailField.sendKeys(email);
    if (tos != 'undefined') {
      this.tosField.click();
    }
  }
}

module.exports = new RegistrationPage;