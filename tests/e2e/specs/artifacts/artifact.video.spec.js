/**
* @file artifact.video.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Video Artifact', function() {
  // This is the pre-condition step of each test.
  beforeEach(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.deleteUser(RegistrationPage.defaultUser.email);
  });

  it('Verify main elements presence', function() {
   ArtifactVideoPage.get();
   ArtifactVideoPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactVideoPage.get();
    ArtifactVideoPage.checkMandatoryFields();
  });

  it('Should not accept other than Video files', function() {
    ArtifactVideoPage.get();
    ArtifactVideoPage.accessMediaBrowser();
    ArtifactVideoPage.checkFileFormat();
  });

  it ('Add a Video artifact as an authenticated user', function () {
    AuthenticationPage.logout();
    RegistrationPage.registerProfile(RegistrationPage.simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.simpleUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    ArtifactVideoPage.add('Video Artifact', 'videoFile.mp4');
    ArtifactVideoPage.checkPageLayout();
    ArtifactVideoPage.checkPageElements();
  });

  // @TODO: This test is still not ready. An annotation needs to be created for the artifact.
  xit('Verify presence of the annotation list in a video artifact.', function () {
    AuthenticationPage.logout();
    RegistrationPage.registerProfile(RegistrationPage.simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.simpleUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    ArtifactVideoPage.add('Video Artifact', 'videoFile.mp4');
    ArtifactVideoPage.checkAnnotationList();
  }).pend('This test is still not ready. An annotation needs to be created for the artifact');
});
