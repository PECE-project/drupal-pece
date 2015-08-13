/**
* @file artifact.image.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Image Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Image Artifact');
  });

  it ('verify main elements presence', function () {
   AllPages.ArtifactImagePage.get();
   AllPages.ArtifactImagePage.checkMainElementsPresence();
  });

  it ('verify mandatory fields', function () {
    AllPages.ArtifactImagePage.get();
    AllPages.ArtifactImagePage.checkMandatoryFields();
  });

  it ('add a image artifact', function () {
    AllPages.ArtifactImagePage.get();
    AllPages.ArtifactImagePage.add('Image Artifact', 'imageFile.jpg');
    AllPages.SamplePage.checkMessage('has been created.');
  });

  it ('Should not accept other than image files', function () {
    AllPages.ArtifactImagePage.get();
    AllPages.ArtifactImagePage.accessMediaBrowser();
    AllPages.ArtifactImagePage.checkFileFormat();
  });
});
