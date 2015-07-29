/**
* @file user_profile.spec.js
*/

// Require all page objects.
var AllPages= require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

describe ('User profile' , function () {
  beforeAll(function () {
      AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
      AllPages.SamplePage.get('admin/config/people/legal');
      AllPages.LegalPage.create();
    }
  );

  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
  });

  it ('should create a new user profile', function () {
    AllPages.RegistrationPage.get();
    AllPages.RegistrationPage.registerProfile('foob', 'foob@bar.baz', 'Foo Bar Baz', 'foob@bar.baz', 'Institution', 'Trainee', 'Lorem ipsum', 'Brazil', 'tagFoo', true);
    // Check that the error message is present.
    expect(AllPages.SamplePage.body.getText()).toContain('Your account is currently pending approval by the site administrator.');
  });
});
