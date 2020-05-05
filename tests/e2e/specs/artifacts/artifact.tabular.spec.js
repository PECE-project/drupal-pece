
describe('Tabular Artifact', function() {
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

  it('Should not accept other than Tabular files', function() {
    ArtifactVideoPage.get();
    ArtifactVideoPage.accessMediaBrowser();
    ArtifactVideoPage.checkFileFormat();
  });

  it ('Add a Tabular artifact as an authenticated user', function () {
    AuthenticationPage.logout();
    RegistrationPage.registerProfile(RegistrationPage.simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.simpleUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    ArtifactVideoPage.add('Tabular Artifact', 'tabularFile.ods');
    ArtifactVideoPage.checkPageLayout();
    ArtifactVideoPage.checkPageElements();
  });

  // @TODO: This test is still not ready. An annotation needs to be created for the artifact.
  xit('Verify presence of the annotation list in a tabular artifact.', function () {
    AuthenticationPage.logout();
    RegistrationPage.registerProfile(RegistrationPage.simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.simpleUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    ArtifactVideoPage.add('Tabular Artifact', 'tabularFile.ods');
    ArtifactVideoPage.checkAnnotationList();
  }).pend('This test is still not ready. An annotation needs to be created for the artifact');
});
