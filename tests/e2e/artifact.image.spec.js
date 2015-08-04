/**
* @file artifact.image.spec.js
*/

// Require all page objects.
var AllPages = require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Image Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  //it ('verify main elements presence', function () {
  //  AllPages.ArtifactImagePage.get();
  //  AllPages.ArtifactImagePage.checkMainElementsPresence();
  //});
  it ('add a image artifact', function () {
    AllPages.ArtifactImagePage.get();
    AllPages.ArtifactImagePage.add();
    expect(AllPages.SamplePage.body.getText()).toContain('has been created.');
  });
});
