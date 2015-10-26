
describe('Text Artifact', function () {
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
