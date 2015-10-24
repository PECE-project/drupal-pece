
describe ('Website Artifact', function () {
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
   ArtifactWebsitePage.get();
   ArtifactWebsitePage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    ArtifactWebsitePage.get();
    ArtifactWebsitePage.checkMandatoryFields();
  });

  it('Should check if it\'s a valid URL', function() {
    ArtifactWebsitePage.get();
    ArtifactWebsitePage.checkUrl();
  });

  it('Add a Website artifact as an authenticated user', function() {
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
    ArtifactWebsitePage.get();
    ArtifactWebsitePage.add('Website Artifact', 'http://google.com');
    ArtifactWebsitePage.checkPageLayout();
    ArtifactWebsitePage.checkPageElements();
  });
});
