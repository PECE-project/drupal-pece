/**
* @file user.profile.page.js
*/
var EC = protractor.ExpectedConditions;

var UserProfilePage = function () {

  // Define user profile attributes.
  this.body = element(by.css('body'));
  this.nameField = element(by.css('#user-profile-form input#edit-profile-pece-profile-main-field-pece-full-name-und-0-value'));
  this.emailField = element(by.css('#user-profile-form input#edit-profile-pece-profile-main-field-pece-email-und-0-email'));
  this.institutionField = element(by.css('#user-profile-form input#edit-profile-pece-profile-main-field-pece-institution-und-0-value'));
  this.positionField = element(by.css('#user-profile-form input#edit-profile-pece-profile-main-field-pece-position-und-0-value'));
  this.bioField = element(by.css('#user-profile-form textarea#edit-profile-pece-profile-main-field-pece-biography-und-0-value'));
  this.tagsField = element(by.css('#user-profile-form input#edit-profile-pece-profile-main-field-pece-tags-und'));
  this.coordSrcDiv = element(by.css('#edit-profile-pece-profile-main-field-pece-location-und-0-locpick-current'));
  this.submitButton = element(by.css('#edit-submit'));

  // Define profile methods.
  this.accessProfileForm = function () {
    var profileTab = element(by.cssContainingText('ul.secondary a', 'Profile'));
    var profileTabIsVisible = EC.visibilityOf(profileTab);

    browser.wait(profileTabIsVisible, browser.params.timeuotLimit);
    profileTab.click();
  };

  this.checkGeocoding = function () {
    var coordSrc =  'Geocoded (Exact)';

    expect(this.coordSrcDiv.getInnerHtml()).toContain(coordSrc);
  };
  
};

module.exports = new UserProfilePage();
