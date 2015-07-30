/**
 * @file registration.page.js
 */

// This is a sample page file where you will find generic methods to use with drupal.
var RegistrationPage = function () {

  // Define registration attributes.
  // User fields.
  this.usernameField = element(by.css('input#edit-name'));
  this.emailField = element(by.css('input#edit-mail'));

  // Profile fields.
  this.fullnameFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-full-name-und-0-value'));
  this.email2FIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-email-und-0-email'));
  this.institutionFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-institution-und-0-value'));
  this.positionFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-position-und-0-value'));
  this.bioFIeld = element(by.css('textarea#edit-profile-pece-profile-main-field-pece-biography-und-0-value'));
  this.tagsFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-tags-und'));
  this.tosField = element(by.css('input#edit-legal-accept'));

  this.tosField = element(by.css('input#edit-legal-accept'));
  this.submitButton = element(by.css('input#edit-submit'));

  // Define authentication methods.
  this.get = function () {
    browser.get('user/register');
  };

  this.fillUserFields = function (user, email) {
    this.usernameField.sendKeys(user);
    this.emailField.sendKeys(email);
  };

  this.fillProfileFields = function (name, email2, institution, position, bio, tags) {
    this.fullnameFIeld.sendKeys(name);
    this.email2FIeld.sendKeys(email2);
    this.institutionFIeld.sendKeys(institution);
    this.positionFIeld.sendKeys(position);
    this.bioFIeld.sendKeys(bio);
    this.tagsFIeld.sendKeys(tags);
  };

  this.checkTosField = function (tos) {
    if (tos == true) {
      this.tosField.click();
    }
  };

  this.submitRegisterForm = function () {
    this.submitButton.click();
  };

  this.register = function (user, email, tos) {
    this.get();
    browser.driver.sleep(3000);
    this.fillUserFields(user, email);
    browser.driver.sleep(1000);
    this.checkTosField(tos);
    browser.driver.sleep(1000);
    this.submitRegisterForm();
    browser.driver.sleep(3000);
  };

  this.registerProfile = function (user, email, name, email2, institution, position, bio, location, tags, tos) {
    this.get();
    browser.driver.sleep(3000);
    this.fillUserFields(user, email);
    browser.driver.sleep(1000);
    this.fillProfileFields(name, email2, institution, position, bio, tags);
    browser.driver.sleep(1000);
    this.checkTosField(tos);
    browser.driver.sleep(1000);
    this.submitRegisterForm();
    browser.driver.sleep(3000);
  };
}

module.exports = new RegistrationPage;
