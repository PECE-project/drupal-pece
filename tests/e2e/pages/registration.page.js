/**
 * @file registration.page.js
 */

var EC = protractor.ExpectedConditions;

// This is a sample page file where you will find generic methods to use with drupal.
var RegistrationPage = function () {

  // Define registration attributes.
  // User fields.
  this.usernameField = element(by.css('input#edit-name'));
  this.emailField = element(by.css('input#edit-mail'));
  this.pass1Field = element(by.css('input#edit-pass-pass1'));
  this.pass2Field = element(by.css('input#edit-pass-pass2'));

  // Profile fields.
  this.fullnameFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-full-name-und-0-value'));
  this.institutionFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-institution-und-0-value'));
  this.positionFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-position-und-0-value'));
  this.bioFIeld = element(by.css('textarea#edit-profile-pece-profile-main-field-pece-biography-und-0-value'));
  this.locStreetField = element(by.css('input#edit-profile-pece-profile-main-field-pece-location-und-0-street'));
  this.locAdditionalField = element(by.css('input#edit-profile-pece-profile-main-field-pece-location-und-0-additional'));
  this.locCountryField = element(by.css('select##edit-profile-pece-profile-main-field-pece-location-und-0-country'));
  this.tagsFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-tags-und'));
  this.tosField = element(by.css('input#edit-legal-accept'));
  this.submitButton = element(by.css('input#edit-submit'));

  // Define authentication methods.
  this.get = function () {
    browser.get('user/register');
  };

  this.fillUserFields = function (user, email, pass) {
    this.usernameField.sendKeys(user);
    this.emailField.sendKeys(email);
    this.pass1Field.sendKeys(pass);
    this.pass2Field.sendKeys(pass);
  };

  this.fillProfileFields = function (name, institution, position, bio, location, tags) {
    this.fullnameFIeld.sendKeys(name);
    this.institutionFIeld.sendKeys(institution);
    this.positionFIeld.sendKeys(position);
    this.bioFIeld.sendKeys(bio);
    this.locStreetField.sendKeys(location.street);
    this.locAdditionalField.sendKeys(location.additional);
    // this.locCountryField.findElements(by.css('option[text=' + location.country + ']')).click();
    element(by.cssContainingText('#edit-profile-pece-profile-main-field-pece-location-und-0-country option', location.country)).click();
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

  this.register = function (user, email, pass, tos) {
    var formIsPresent = EC.visibilityOf(this.usernameField);

    this.get();
    browser.wait(formIsPresent, browser.params.timeoutLimit);
    this.fillUserFields(user, email, pass);
    this.checkTosField(tos);
    this.submitRegisterForm();
  };

  this.registerProfile = function (user) {
    var formIsPresent = EC.visibilityOf(this.fullnameFIeld);

    this.get();
    browser.wait(formIsPresent, browser.params.timeoutLimit);
    this.fillUserFields(user.username, user.email, user.pass);
    this.fillProfileFields(user.name, user.institution, user.position, user.bio, user.location, user.tags);
    this.checkTosField(user.tos);
    this.submitRegisterForm();
  };
}

module.exports = new RegistrationPage;
