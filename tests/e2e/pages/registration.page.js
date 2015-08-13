/**
 * @file registration.page.js
 */

var EC = protractor.ExpectedConditions;

var RegistrationPage = function () {

  // Define registration attributes.
  // User fields.
  this.usernameField = element(by.css('input#edit-name'));
  this.emailField = element(by.css('input#edit-mail'));
  this.pass1Field = element(by.css('input#edit-pass-pass1'));
  this.pass2Field = element(by.css('input#edit-pass-pass2'));

  // Profile fields.
  this.fullnameField = element(by.css('input#edit-profile-pece-profile-main-field-pece-full-name-und-0-value'));
  this.institutionField = element(by.css('input#edit-profile-pece-profile-main-field-pece-institution-und-0-value'));
  this.positionField = element(by.css('input#edit-profile-pece-profile-main-field-pece-position-und-0-value'));
  this.bioField = element(by.css('textarea#edit-profile-pece-profile-main-field-pece-biography-und-0-value'));
  this.locStreetField = element(by.css('input#edit-profile-pece-profile-main-field-pece-location-und-0-street'));
  this.locAdditionalField = element(by.css('input#edit-profile-pece-profile-main-field-pece-location-und-0-additional'));
  this.locCountryField = element(by.css('select##edit-profile-pece-profile-main-field-pece-location-und-0-country'));
  this.tagsField = element(by.css('input#edit-profile-pece-profile-main-field-pece-tags-und'));
  this.tosField = element(by.css('input#edit-legal-accept'));
  this.submitButton = element(by.css('input#edit-submit'));

  this.get = function () {
    browser.get('user/register');
  };

  this.fillUserFields = function (user, email, pass) {
    browser.wait(EC.visibilityOf(this.usernameField), browser.params.timeoutLimit);
    this.usernameField.sendKeys(user);
    this.emailField.sendKeys(email);
    this.pass1Field.sendKeys(pass);
    this.pass2Field.sendKeys(pass);
  };

  this.fillProfileFields = function (name, institution, position, bio, location, tags) {
    this.fullnameField.sendKeys(name);
    this.institutionField.sendKeys(institution);
    this.positionField.sendKeys(position);
    this.bioField.sendKeys(bio);
    this.locStreetField.sendKeys(location.street);
    this.locAdditionalField.sendKeys(location.additional);
    element(by.cssContainingText('#edit-profile-pece-profile-main-field-pece-location-und-0-country option', location.country)).click();
    this.tagsField.sendKeys(tags);
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
    this.get();
    this.fillUserFields(user, email, pass);
    this.checkTosField(tos);
    this.submitRegisterForm();
  };

  this.registerProfile = function (user) {
    this.get();
    this.fillUserFields(user.username, user.email, user.pass);
    this.fillProfileFields(user.name, user.institution, user.position, user.bio, user.location, user.tags);
    this.checkTosField(user.tos);
    this.submitRegisterForm();
  };
}

module.exports = new RegistrationPage;
