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
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Audio Artifact');
  });

  it ('verify main elements presence', function () {
   AllPages.ArtifactAudioPage.get();
   AllPages.ArtifactAudioPage.checkMainElementsPresence();
  });

  it ('verify mandatory fields', function () {
    AllPages.ArtifactAudioPage.get();
    AllPages.ArtifactAudioPage.checkMandatoryFields();
  });

  it ('add a Video artifact', function () {
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
