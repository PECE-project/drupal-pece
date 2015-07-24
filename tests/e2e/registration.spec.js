/**
* @file registration.spec.js
*/

// Require authentication page object.
var RegistrationPage = require('./pages/registration.page');
var AuthenticationPage = require('./pages/authentication.page');
var SamplePage = require('./pages/sample.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Registration' , function () {
  it ('should be not accomplished', function () {
    RegistrationPage.register('foo', 'foo@bar.baz');
    // Check that the error message is present.
    expect(SamplePage.body.getText()).toContain('Accept Terms & Conditions of Use field is required.');
  });

  it ('should be succesfuly done', function () {
    RegistrationPage.register('foo', 'foo@bar.baz', true);
    // Check that user is logged in.
    expect(AuthenticationPage.loggedIn.isPresent()).toBe(true);
  });
});
