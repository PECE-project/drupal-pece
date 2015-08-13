/**
* @file artifact.video.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Video Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  //afterAll(function () {
  //  AllPages.ContentPage.get();
  //  AllPages.ContentPage.remove('Video Artifact');
  //});

  it ('verify main elements presence', function () {
   AllPages.ArtifactVideoPage.get();
   AllPages.ArtifactVideoPage.checkMainElementsPresence();
  });

  it ('verify mandatory fields', function () {
    AllPages.ArtifactVideoPage.get();
    AllPages.ArtifactVideoPage.checkMandatoryFields();
  });

  it ('add a Video artifact', function () {
    AllPages.ArtifactVideoPage.get();
    AllPages.ArtifactVideoPage.add('Video Artifact', 'videoFile.mp4');
    AllPages.SamplePage.checkMessage('has been created.');
  });

  it ('Should not accept other than Video files', function () {
    AllPages.ArtifactVideoPage.get();
    AllPages.ArtifactVideoPage.accessMediaBrowser();
    AllPages.ArtifactVideoPage.checkFileFormat();
  });
});
