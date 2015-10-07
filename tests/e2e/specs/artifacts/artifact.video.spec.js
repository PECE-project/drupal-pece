/**
* @file artifact.video.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Video Artifact', function() {
  // This is the pre-condition step of each test.
  beforeEach(function() {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function() {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it('Verify main elements presence', function() {
   AllPages.ArtifactVideoPage.get();
   AllPages.ArtifactVideoPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    AllPages.ArtifactVideoPage.get();
    AllPages.ArtifactVideoPage.checkMandatoryFields();
  });

  it('Should not accept other than Video files', function() {
    AllPages.ArtifactVideoPage.get();
    AllPages.ArtifactVideoPage.accessMediaBrowser();
    AllPages.ArtifactVideoPage.checkFileFormat();
  });

  it ('Add a Video artifact as an authenticated user', function () {
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.registerProfile(AllPages.RegistrationPage.simpleUser);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.simpleUser.email);
    AllPages.PeoplePage.addRole(AllPages.RegistrationPage.defaultUser.email, 5);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.simpleUser.username, AllPages.RegistrationPage.simpleUser.pass);
    AllPages.ArtifactVideoPage.add('Video Artifact', 'videoFile.mp4');
    AllPages.ArtifactVideoPage.checkPageLayout();
    AllPages.ArtifactVideoPage.checkPageElements();
  });

  // @TODO: This test is still not ready. An annotation needs to be created for the artifact.
  xit('Verify presence of the annotation list in a video artifact.', function () {
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.registerProfile(AllPages.RegistrationPage.simpleUser);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.simpleUser.email);
    AllPages.PeoplePage.addRole(AllPages.RegistrationPage.defaultUser.email, 5);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.simpleUser.username, AllPages.RegistrationPage.simpleUser.pass);
    AllPages.ArtifactVideoPage.add('Video Artifact', 'videoFile.mp4');
    AllPages.ArtifactVideoPage.checkAnnotationList();
  });
});
