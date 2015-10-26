
describe('Audio Artifact', function() {
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
   ArtifactAudioPage.get();
   ArtifactAudioPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactAudioPage.get();
    ArtifactAudioPage.checkMandatoryFields();
  });

  it('Should not accept other than Audio files', function() {
    ArtifactAudioPage.get();
    ArtifactAudioPage.accessMediaBrowser();
    ArtifactAudioPage.checkFileFormat();
  });

  it('Add a Audio artifact as an authenticated user', function() {
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
    AuthenticationPage.logout();
    RegistrationPage.get();
    RegistrationPage.registerProfile(RegistrationPage.simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.get();
    PeoplePage.unblock(RegistrationPage.simpleUser.email);
    PeoplePage.addRole(RegistrationPage.simpleUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    ArtifactAudioPage.get();
    ArtifactAudioPage.add('Audio Artifact', 'audioFile.mp3');
    ArtifactAudioPage.checkPageLayout();
    ArtifactAudioPage.checkPageElements();
  });
});
