var Seeds = require('drupal-seeds').Seeds;

describe('Audio Artifact', function() {
  var seeds = new Seeds([
    {
      type: 'user',
      data: {
        name: RegistrationPage.simpleUser.username,
        mail: RegistrationPage.simpleUser.email,
        pass: RegistrationPage.simpleUser.pass,
        roles: ['contributor'],
      }
    }
  ]);

  seeds.attach();

  beforeEach(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function() {
    AuthenticationPage.logout();
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
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    LegalPage.acceptTerm();
    ArtifactAudioPage.get();
    ArtifactAudioPage.add('Audio Artifact', 'audioFile.mp3');
    ArtifactAudioPage.checkPageLayout();
    ArtifactAudioPage.checkPageElements();
  });
});
