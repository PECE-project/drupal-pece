/**
* @file artifact.audio.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Audio Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Audio Artifact');
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it ('Verify main elements presence', function () {
   AllPages.ArtifactAudioPage.get();
   AllPages.ArtifactAudioPage.checkMainElementsPresence();
  });

  it ('Verify mandatory fields', function () {
    AllPages.ArtifactAudioPage.get();
    AllPages.ArtifactAudioPage.checkMandatoryFields();
  });

  it ('Add a Audio artifact as an authenticated user', function () {
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.get();
    AllPages.RegistrationPage.registerProfile();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.get();
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.defaultUser.email);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.defaultUser.username, AllPages.RegistrationPage.defaultUser.pass);
    AllPages.ArtifactAudioPage.get();
    AllPages.ArtifactAudioPage.add('Audio Artifact', 'audioFile.mp3');
    AllPages.SamplePage.checkMessage('has been created.');
  });

  it ('Should not accept other than Audio files', function () {
    AllPages.ArtifactAudioPage.get();
    AllPages.ArtifactAudioPage.accessMediaBrowser();
    AllPages.ArtifactAudioPage.checkFileFormat();
  });
});
