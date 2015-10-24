/**
* @file artifact.text.spec.js
*/

var simpleUser = {
    username: 'simpleUser',
    email: 'simpleUser@example.com',
    pass: browser.params.admin.password,
    name: 'SimpleUser',
    tos: true
}

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Memo', function () {
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
   MemoPage.get();
   MemoPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    MemoPage.get();
    MemoPage.checkMandatoryFields();
  });

  it('Add a Memo as an authenticated user', function() {
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
    AuthenticationPage.logout();
    RegistrationPage.registerProfile();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.defaultUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    MemoPage.add('Memo', 'Lorem ipsum dolar sit.');
    MemoPage.checkPageLayout();
    MemoPage.checkPageElements();
  });

  it('should have comments opened but moderated for an authenticated users.', function() {
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
    AuthenticationPage.logout();
    RegistrationPage.registerProfile();
    RegistrationPage.registerProfile(simpleUser);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(RegistrationPage.defaultUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    PeoplePage.unblock(simpleUser.email);
    PeoplePage.addRole(simpleUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    MemoPage.add('Memo 2', 'Lorem ipsum dolar sit.');
    AuthenticationPage.logout();
    AuthenticationPage.login(simpleUser.username, simpleUser.pass);
    MemoPage.comment('content/memo-2', 'Comment content');
    SamplePage.checkMessage('Your comment has been queued for review by site administrators and will be published after approval.');
  });
});
