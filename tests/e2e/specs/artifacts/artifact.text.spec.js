/**
* @file artifact.text.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Text Artifact', function () {
  // This its the pre-condition step of each test.
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
   ArtifactTextPage.get();
   ArtifactTextPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactTextPage.get();
    ArtifactTextPage.checkMandatoryFields();
  });

  it('Add a Text artifact as an authenticated user', function() {
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
    AuthenticationPage.logout();
    RegistrationPage.get();
    RegistrationPage.registerProfile();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.get();
    PeoplePage.unblock(RegistrationPage.defaultUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    ArtifactTextPage.get();
    ArtifactTextPage.add('Text Artifact', 'Lorem ipsum dolar sit.');
    ArtifactTextPage.checkPageLayout();
    ArtifactTextPage.checkPageElements();
  });
});
