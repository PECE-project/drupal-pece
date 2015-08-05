/**
* @file cleanup.spec.js
*/

// Require authentication page object.
var AllPages= require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Cleanup' , function () {
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  it ('remove the created fieldnote artifact', function () {
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('pece_artifact_fieldnote');
    expect(AllPages.SamplePage.body.getText()).toContain('has been deleted.');
  });

  it ('should delete the user from the registration test', function () {
    AllPages.PeoplePage.deleteUser('foobar@bar.baz');
    expect(AllPages.SamplePage.body.getText()).toContain('has been deleted.');
  });

  it ('remove the created image artifact', function () {
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Image Artifact');
    expect(AllPages.SamplePage.body.getText()).toContain('has been deleted.');
  });
});
