/**
* @file fieldnote.spec.js
*/

// Require fieldnote page object.
var FieldnotePage = require('./pages/fieldnote.page');
var AuthenticationPage = require('./pages/authentication.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Fieldnote' , function () {
  // This is the pre-condition step of each test.
	beforeEach(function () {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    FieldnotePage.get();
  });

	it ('verify main elements presence', function () {
    FieldnotePage.checkMainElementsPresence();
	});
});
