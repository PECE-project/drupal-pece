
describe('Structured Analytics', function() {
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
   AnalyticPage.get();
   AnalyticPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    AnalyticPage.get();
    AnalyticPage.checkMandatoryFields();
  });

  it('Add a Structred Analytics as an authenticated user', function() {
    var questionSetTitle = 'Sample Structured Analytics (Question set)';

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
    StructuredAnalyticsPage.add(questionSetTitle);
    expect(AnalyticPage.mainElements.questionSetField.element(by.cssContainingText('label', questionSetTitle)));
  });
});
