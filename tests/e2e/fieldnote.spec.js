/**
* @file fieldnote.spec.js
*/

// Require fieldnote page object.
var AllPages = require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Fieldnote' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  it ('verify main elements presence', function () {
		AllPages.FieldnotePage.get();
    AllPages.FieldnotePage.checkMainElementsPresence();
  });

	it ('add a fieldnote artifact', function () {
		AllPages.FieldnotePage.get();
		AllPages.FieldnotePage.add('Fieldnote text');
		expect(AllPages.SamplePage.body.getText()).toContain('has been created.');
	});

	it ('remove the just created fieldnote artifact', function () {
		AllPages.ContentPage.get();
		AllPages.ContentPage.remove('pece_artifact_fieldnote');
		expect(AllPages.SamplePage.body.getText()).toContain('has been deleted.');
	});
});
