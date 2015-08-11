/**
* @file registration.spec.js
*/

// Require authentication page object.
var AllPages= require('../pages/all.page');
var EC = protractor.ExpectedConditions;

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

  afterAll(function () {
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser('foobar@bar.baz');
    browser.wait(EC.visibilityOf(AllPages.SamplePage.body), browser.params.timeoutLimit);
    expect(AllPages.SamplePage.body.getText()).toContain('has been deleted.');
  });

  it ('should be not accomplished', function () {
    AllPages.RegistrationPage.register('foo', 'foo@bar.baz', browser.params.admin.password, false);
    browser.wait(EC.visibilityOf(AllPages.SamplePage.body), browser.params.timeoutLimit);
    expect(AllPages.SamplePage.body.getText()).toContain('Accept Terms & Conditions of Use field is required.');
  });

  it ('invalid email on user registration', function () {
    var invalidEmail = 'bar';
    AllPages.RegistrationPage.register('bar', invalidEmail, browser.params.admin.password, true);
    browser.wait(EC.visibilityOf(AllPages.SamplePage.body), browser.params.timeoutLimit);
    expect(AllPages.SamplePage.body.getText()).toContain('The e-mail address ' + invalidEmail +  ' is not valid.');
  });

  it ('should be succesfuly done', function () {
    AllPages.RegistrationPage.register('foobar', 'foobar@bar.baz', browser.params.admin.password, true);
    browser.wait(EC.visibilityOf(AllPages.SamplePage.body), browser.params.timeoutLimit);
    expect(AllPages.SamplePage.body.getText()).toContain('Your account is currently pending approval by the site administrator.');
  });
});
