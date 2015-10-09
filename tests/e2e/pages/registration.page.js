/**
 * @file registration.page.js
 */

var EC = protractor.ExpectedConditions;

var RegistrationPage = function() {

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
  this.usernameField = $('input#edit-name');
  this.emailField    = $('input#edit-mail');
  this.pass1Field    = $('input#edit-pass-pass1');
  this.pass2Field    = $('input#edit-pass-pass2');

  // Profile fields.
  this.fullnameField      = $('input#edit-profile-pece-profile-main-field-pece-full-name-und-0-value');
  this.institutionField   = $('input#edit-profile-pece-profile-main-field-pece-institution-und-0-value');
  this.positionField      = $('input#edit-profile-pece-profile-main-field-pece-position-und-0-value');
  this.bioField           = $('textarea#edit-profile-pece-profile-main-field-pece-biography-und-0-value');
  this.locStreetField     = $('input#edit-profile-pece-profile-main-field-pece-location-und-0-street');
  this.locAdditionalField = $('input#edit-profile-pece-profile-main-field-pece-location-und-0-additional');
  this.locProvinceField   = $('input#edit-profile-pece-profile-main-field-pece-location-und-0-province');
  this.locCountryField    = $('select##edit-profile-pece-profile-main-field-pece-location-und-0-country');
  this.tagsField          = $('input#edit-profile-pece-profile-main-field-pece-tags-und');
  this.tosField           = $('input#edit-legal-accept');
  this.submitButton       = $('input#edit-submit');

  // Define registration methods.
  this.register = function(user, email, pass, tos) {
    this.get();
    this.fillUserFields(user, email, pass);
    this.checkTosField(tos);
    this.submitRegisterForm();
    browser.wait(element(by.css('.messages')).isDisplayed);
  };

  this.registerProfile = function(user) {
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

  this.get = function() {
    browser.get('user/register');
  };

  this.fillUserFields = function(user, email, pass) {
    browser.wait(EC.visibilityOf(this.usernameField), browser.params.timeoutLimit);
    // @TODO: Find why protractor needs this time in order to be able to fill
    // the fields bellow.
    browser.sleep(1000);
    browser.sleep(1000);
    browser.sleep(1000);
    browser.sleep(1000);
    this.usernameField.click();
    this.usernameField.sendKeys(user);
    this.emailField.sendKeys(email);
    this.pass1Field.sendKeys(pass);
    this.pass2Field.sendKeys(pass);
  };

  this.fillProfileFields = function(user) {
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

  this.checkTosField = function(tos) {
    if (tos == true) {
      this.tosField.click();
    }
  };

  this.submitRegisterForm = function() {
    this.submitButton.click();
  };

}

module.exports = new RegistrationPage;
