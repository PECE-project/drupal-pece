/**
* @file user.profile.page.js
*/

var UserProfilePage = function () {

  // Define user profile attributes.
  this.emailField = element(by.css('#user-profile-form input#edit-mail'));

  this.accessProfileForm = function () {
    element(by.cssContainingText('a', 'Profile')).click();
    browser.driver.sleep(1000);
  };

};

module.exports = new UserProfilePage();
