/**
* @file registration.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Registration', function() {
  beforeAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    LegalPage.get();
    LegalPage.create();
  });

  beforeEach(function() {
    AuthenticationPage.logout();
  });

  afterAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.deleteUser('foobar@bar.baz');
  });

  it('should be not accomplished because of not accepting the term', function() {
    RegistrationPage.register('foo', 'foo@bar.baz', browser.params.admin.password, false);
    SamplePage.checkMessage('Accept Terms & Conditions of Use field is required.');
  });

  it('invalid email on user registration', function() {
    var invalidEmail = 'bar';
    RegistrationPage.register('bar', invalidEmail, browser.params.admin.password, true);
    SamplePage.checkMessage('The e-mail address ' + invalidEmail +  ' is not valid.');
  });

  it('should be succesfuly done', function() {
    RegistrationPage.register('foobar', 'foobar@bar.baz', browser.params.admin.password, true);
    SamplePage.checkMessage('Your account is currently pending approval by the site administrator.');
  });
});
