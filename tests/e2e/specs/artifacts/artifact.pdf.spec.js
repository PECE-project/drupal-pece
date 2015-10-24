/**
* @file artifact.pdf.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('PDF Docuemnt Artifact', function() {
  // This is the pre-condition step of each test.
  beforeEach(function () {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.deleteUser(RegistrationPage.defaultUser.email);
  });

  it('Verify main elements presence', function() {
   ArtifactPdfPage.get();
   ArtifactPdfPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactPdfPage.get();
    ArtifactPdfPage.checkMandatoryFields();
  });

  it('Should not accept other than PDF files', function() {
    ArtifactPdfPage.get();
    ArtifactPdfPage.accessMediaBrowser();
    ArtifactPdfPage.checkFileFormat();
  });

  it('Add PDF Document artifact as an authenticated user', function() {
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
    ArtifactPdfPage.get();
    ArtifactPdfPage.add('PDF Document Artifact', 'pdfFile.pdf');
    ArtifactPdfPage.checkPageLayout();
    ArtifactPdfPage.checkPageElements();
  });

  // @TODO
  // it ('add PDF Document artifact with author different from contributor', function () {});
});
