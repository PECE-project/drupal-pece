/**
* @file artifact.pdf.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('PDF Docuemnt Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('PDF Document Artifact');
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it ('verify main elements presence', function () {
   AllPages.ArtifactPdfPage.get();
   AllPages.ArtifactPdfPage.checkMainElementsPresence();
  });

  it ('verify mandatory fields', function () {
    AllPages.ArtifactPdfPage.get();
    AllPages.ArtifactPdfPage.checkMandatoryFields();
  });

  it ('add a PDF Document artifact', function () {
    AllPages.ArtifactPdfPage.get();
    AllPages.ArtifactPdfPage.add('PDF Document Artifact', 'pdfFile.pdf');
    AllPages.SamplePage.checkMessage('has been created.');
  });

  it ('should not accept other than PDF files', function () {
    AllPages.ArtifactPdfPage.get();
    AllPages.ArtifactPdfPage.accessMediaBrowser();
    AllPages.ArtifactPdfPage.checkFileFormat();
  });

  it ('add PDF Document artifact as researcher user', function () {
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.get();
    AllPages.RegistrationPage.registerProfile();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.get();
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.defaultUser.email);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.defaultUser.username, AllPages.RegistrationPage.defaultUser.pass);
    AllPages.ArtifactPdfPage.get();
    AllPages.ArtifactPdfPage.add('Sample PDF Document', 'pdfFile.pdf');
    AllPages.SamplePage.checkMessage('has been created.');
  });

  // it ('add PDF Document artifact with author different from contributor', function () {});
});
