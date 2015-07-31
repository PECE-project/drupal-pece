/**
* @file user_profile.spec.js
*/

// Require all page objects.
var AllPages= require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

describe ('User profile' , function () {
  beforeAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
  });

  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
  });

  it ('should create a new user profile', function () {
    AllPages.RegistrationPage.registerProfile('foob', 'foob@bar.baz', browser.params.admin.password, 'Foo B.', 'Institution', 'Trainee', 'Lorem ipsum', 'Brazil', 'tagFoo', true);
    expect(AllPages.SamplePage.body.getText()).toContain('Your account is currently pending approval by the site administrator.');
  });

  it('check profile email after registration', function () {
    var email = 'boof@bar.baz'
    AllPages.RegistrationPage.registerProfile('boof', email, browser.params.admin.password, 'Boo F.', 'Institution', 'Trainee', 'Lorem ipsum', 'Brazil', 'tagFoo', true);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.edit(email);
    AllPages.UserProfilePage.accessProfileForm();
    expect(AllPages.UserProfilePage.emailField.getText()).toEqual(email);
  });
});
