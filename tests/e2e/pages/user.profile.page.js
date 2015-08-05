/**
* @file user.profile.page.js
*/

var UserProfilePage = function () {

  // Define user profile attributes.
  this.emailField = element(by.css('#user-profile-form input#edit-profile-pece-profile-main-field-pece-email-und-0-email'));

  this.accessProfileForm = function () {
    var EC = protractor.ExpectedConditions
      , profileTab = element(by.cssContainingText('ul.secondary a', 'Profile'))
      , profileTabIsVisible = EC.visibilityOf(profileTab);

    browser.wait(profileTabIsVisible, browser.params.timeuotLimit);
    profileTab.click();
  };
};

module.exports = new UserProfilePage();
