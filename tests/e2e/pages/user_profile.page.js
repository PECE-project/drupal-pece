/**
 * @file user_profile.page.js
 */

var UserProfilePage = function () {

  // Define user profile attributes.
  this.usernameField = element(by.css('input#edit-name'));
  this.emailField = element(by.css('input#edit-mail'));
  // Profile fields
  this.fullnameFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-full-name-und-0-value'));
  this.email2FIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-email-und-0-email'));
  this.institutionFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-institution-und-0-value'));
  this.positionFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-position-und-0-value'));
  this.bioFIeld = element(by.css('textarea#edit-profile-pece-profile-main-field-pece-biography-und-0-value'));
  this.tagsFIeld = element(by.css('input#edit-profile-pece-profile-main-field-pece-tags-und'));
  this.tosField = element(by.css('input#edit-legal-accept'));

  this.submitButton = element(by.css('input#edit-submit'));


  // Define user profile methods.
  this.getRegister = function () {
    browser.get('user/register');
  };

  this.register = function (user, email, name, email2, institution, position, bio, location, tags, tos) {

    this.usernameField.sendKeys(user);
    this.emailField.sendKeys(email);
    this.fullnameFIeld.sendKeys(name);
    this.email2FIeld.sendKeys(email2);
    this.institutionFIeld.sendKeys(institution);
    this.positionFIeld.sendKeys(position);
    this.bioFIeld.sendKeys(bio);
    this.tagsFIeld.sendKeys(tags);
    if (tos == true) {
      this.tosField.click();
    }

    this.submitButton.click();
  }
}

module.exports = new UserProfilePage;