/**
* @file artifact.image.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Image Artifact', function() {
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
    ArtifactImagePage.get();
    ArtifactImagePage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactImagePage.get();
    ArtifactImagePage.checkMandatoryFields();
  });

  it('Should not accept other than image files', function() {
    ArtifactImagePage.get();
    ArtifactImagePage.accessMediaBrowser();
    ArtifactImagePage.checkFileFormat();
  });

  it('Add a image artifact as researcher user', function() {
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
    AuthenticationPage.logout();
    RegistrationPage.get();
    RegistrationPage.registerProfile();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.get();
    PeoplePage.unblock(RegistrationPage.defaultUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    ArtifactImagePage.get();
    ArtifactImagePage.add('Image Artifact', 'imageFile.jpg');
    ArtifactImagePage.checkPageLayout();
    ArtifactImagePage.checkPageElements();
  });
});
