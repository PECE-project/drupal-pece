/**
* @file registration.spec.js
*/

// Require authentication page object.
var AllPages= require('../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Registration' , function () {
  beforeAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.LegalPage.get();
    AllPages.LegalPage.create();
  });

  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
  });

  afterAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser('foobar@bar.baz');
  });

  it ('should be not accomplished because of not accepting the term', function () {
    AllPages.RegistrationPage.register('foo', 'foo@bar.baz', browser.params.admin.password, false);
    AllPages.SamplePage.checkMessage('Accept Terms & Conditions of Use field is required.');
  });

  it ('invalid email on user registration', function () {
    var invalidEmail = 'bar';
    AllPages.RegistrationPage.register('bar', invalidEmail, browser.params.admin.password, true);
    AllPages.SamplePage.checkMessage('The e-mail address ' + invalidEmail +  ' is not valid.');
  });

  it ('should be succesfuly done', function () {
    AllPages.RegistrationPage.register('foobar', 'foobar@bar.baz', browser.params.admin.password, true);
    AllPages.SamplePage.checkMessage('Your account is currently pending approval by the site administrator.');
  });
});
