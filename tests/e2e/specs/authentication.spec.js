/**
* @file authentication.spec.js
*/

// Require authentication page object.
var AllPages = require('../pages/all.page');


// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Authentication' , function () {
  it ('login', function () {
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    // Check that user is logged in.
    expect(AllPages.AuthenticationPage.loggedIn.isPresent()).toBe(true);
	});

  it ('logout', function () {
    AllPages.AuthenticationPage.logout();
    // Check that user is logged out.
    expect(AllPages.AuthenticationPage.loggedIn.isPresent()).toBe(false);
  });
});
