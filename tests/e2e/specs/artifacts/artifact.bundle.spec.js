/**
* @file artifact.website.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe ('Artifact Bundle', function () {
  // This is the pre-condition step of each test.
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
   ArtifactBundlePage.get();
   ArtifactBundlePage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactBundlePage.get();
    ArtifactBundlePage.checkMandatoryFields();
  });

  xit('Add a Artifact Bundle as an authenticated user', function() {
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
    AuthenticationPage.logout();
    RegistrationPage.registerProfile(RegistrationPage.simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.simpleUser.email);
    PeoplePage.addRole(RegistrationPage.simpleUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.simpleUser.username, RegistrationPage.simpleUser.pass);
    ArtifactBundlePage.add('Artifact Bundle');
    ArtifactBundlePage.checkPageLayout();
    ArtifactBundlePage.checkPageElements();
  }).pend('This test will be skipped because the add method from the Bundle Artifact page is not ready yet');
});
