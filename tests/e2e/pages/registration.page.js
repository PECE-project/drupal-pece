/**
 * @file registration.page.js
 */

var EC = protractor.ExpectedConditions;

var RegistrationPage = function () {

  this.defaultUser = {
    username: 'defaultuser',
    email: 'default@user.com',
    pass: browser.params.admin.password,
    name: 'Default User',
    institution: 'PUCRS',
    position: 'Developer',
    bio: 'Lorem ipsum',
    location: {
      label: 'Sweet Home',
      street: 'street',
      additional: 'additional',
      province: 'Santa Catarina',
      country: 'Brazil'
    },
    tags: 'tagFoo',
    tos: true
  };

  this.simpleUser = {
    username: this.defaultUser.username,
    email: this.defaultUser.email,
    pass: browser.params.admin.password,
    name: this.defaultUser.name,
    tos: true
  }

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
  this.locProvinceField = element(by.css('input#edit-profile-pece-profile-main-field-pece-location-und-0-province'));
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

  this.fillProfileFields = function (user) {
    browser.wait(EC.visibilityOf(this.fullnameField), browser.params.timeoutLimit);
    if (typeof user.name != 'undefined') {
      this.fullnameField.sendKeys(user.name);
    };
    if (typeof user.institution != 'undefined') {
      this.institutionField.sendKeys(user.institution);
    }
    if (typeof user.position != 'undefined') {
      this.positionField.sendKeys(user.position);
    }
    if (typeof user.bio != 'undefined') {
      this.bioField.sendKeys(user.bio);
    }
    if (user.location) {
      if (typeof user.location.street != 'undefined') {
        this.locStreetField.sendKeys(user.location.street);
      }
      if (typeof user.location.additional != 'undefined') {
        this.locAdditionalField.sendKeys(user.location.additional);
      }
      if (typeof user.location.country != 'undefined') {
        element(by.cssContainingText('#edit-profile-pece-profile-main-field-pece-location-und-0-country option', user.location.country)).click();
      }
      if (typeof user.location.province != 'undefined') {
        this.locProvinceField.sendKeys(user.location.province);
      }
    }
    if (typeof user.tags != 'undefined') {
      this.tagsField.sendKeys(user.tags);
    }
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
    if (typeof(user) == 'undefined') {
      this.fillUserFields(this.defaultUser.username, this.defaultUser.email, this.defaultUser.pass);
      this.fillProfileFields(this.defaultUser);
      this.checkTosField(this.defaultUser.tos);
    } else {
      this.fillUserFields(user.username, user.email, user.pass);
      this.fillProfileFields(user);
      this.checkTosField(user.tos);
    }
    this.submitRegisterForm();
  };
}

module.exports = new RegistrationPage;
