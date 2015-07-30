/**
* @file registration.spec.js
*/

// Require authentication page object.
var AllPages= require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Registration' , function () {
  beforeAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
  });

  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
  });

  it ('should be not accomplished', function () {
    AllPages.RegistrationPage.register('foo', 'foo@bar.baz', false);
    expect(AllPages.SamplePage.body.getText()).toContain('Accept Terms & Conditions of Use field is required.');
  });

  it ('invalid email on user registration', function () {
    var invalidEmail = 'bar';
    AllPages.RegistrationPage.register('bar', invalidEmail, true);
    expect(AllPages.SamplePage.body.getText()).toContain('The e-mail address ' + invalidEmail +  ' is not valid.');
  });

  it ('should be succesfuly done', function () {
    AllPages.RegistrationPage.register('foobar', 'foobar@bar.baz', true);
    expect(AllPages.SamplePage.body.getText()).toContain('Your account is currently pending approval by the site administrator.');
  });
});
