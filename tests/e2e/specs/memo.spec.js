/**
* @file artifact.text.spec.js
*/

var AllPages = require('../pages/all.page');

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
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function() {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it('Verify main elements presence', function() {
   AllPages.MemoPage.get();
   AllPages.MemoPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    AllPages.MemoPage.get();
    AllPages.MemoPage.checkMandatoryFields();
  });

  it('Add a Memo as an authenticated user', function() {
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.registerProfile();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.defaultUser.email);
    AllPages.PeoplePage.addRole(AllPages.RegistrationPage.defaultUser.email, 5);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.defaultUser.username, AllPages.RegistrationPage.defaultUser.pass);
    AllPages.MemoPage.add('Memo', 'Lorem ipsum dolar sit.');
    AllPages.MemoPage.checkPageLayout();
    AllPages.MemoPage.checkPageElements();
  });

  it('should have comments opened but moderated for an authenticated users.', function() {
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.registerProfile();
    AllPages.RegistrationPage.registerProfile(simpleUser);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.defaultUser.email);
    AllPages.PeoplePage.addRole(AllPages.RegistrationPage.defaultUser.email, 5);
    AllPages.PeoplePage.unblock(simpleUser.email);
    AllPages.PeoplePage.addRole(simpleUser.email, 5);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.defaultUser.username, AllPages.RegistrationPage.defaultUser.pass);
    AllPages.MemoPage.add('Memo 2', 'Lorem ipsum dolar sit.');
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(simpleUser.username, simpleUser.pass);
    AllPages.MemoPage.comment('content/memo-2', 'Comment content');
    AllPages.SamplePage.checkMessage('Your comment has been queued for review by site administrators and will be published after approval.');
  });
});
