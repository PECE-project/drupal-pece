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
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Image Artifact');
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it ('Verify main elements presence', function () {
   AllPages.ArtifactImagePage.get();
   AllPages.ArtifactImagePage.checkMainElementsPresence();
  });

  it ('Verify mandatory fields', function () {
    AllPages.ArtifactImagePage.get();
    AllPages.ArtifactImagePage.checkMandatoryFields();
  });

  it ('Add a image artifact as researcher user', function () {
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.get();
    AllPages.RegistrationPage.registerProfile();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.get();
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.defaultUser.email);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.defaultUser.username, AllPages.RegistrationPage.defaultUser.pass);
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
