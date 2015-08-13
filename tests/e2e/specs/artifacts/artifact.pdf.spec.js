/**
* @file artifact.pdf.spec.js
*/

var AllPages = require('../../pages/all.page');
var EC = protractor.ExpectedConditions;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('PDF Docuemnt Artifact' , function () {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('PDF Document Artifact');
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
    browser.wait(EC.visibilityOf(AllPages.SamplePage.body), browser.params.timeoutLimit);
    expect(AllPages.SamplePage.body.getText()).toContain('has been created.');
  });

  it ('Should not accept other than PDF files', function () {
    AllPages.ArtifactPdfPage.get();
    AllPages.ArtifactPdfPage.accessMediaBrowser();
    AllPages.ArtifactPdfPage.checkFileFormat();
  });
});
