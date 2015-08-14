/**
* @file artifact.website.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Website Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Website Artifact');
  });

  it ('verify main elements presence', function () {
   AllPages.ArtifactWebsitePage.get();
   AllPages.ArtifactWebsitePage.checkMainElementsPresence();
  });

  it ('verify mandatory fields', function () {
    AllPages.ArtifactWebsitePage.get();
    AllPages.ArtifactWebsitePage.checkMandatoryFields();
  });

  // it ('Should check if it\'s a valid URL', function () {
  //   AllPages.ArtifactWebsitePage.get();
  //   AllPages.ArtifactWebsitePage.checkUrl();
  // });

  it ('add a Website artifact', function () {
    AllPages.ArtifactWebsitePage.get();
    AllPages.ArtifactWebsitePage.add('Website Artifact', 'http://google.com');
    AllPages.SamplePage.checkMessage('has been created.');
  });
});
