/**
* @file analytics.spec.js
*/

var AllPages = require('../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Structured Analytics' , function () {
  // This its the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it ('Verify main elements presence', function () {
   AllPages.AnalyticPage.get();
   AllPages.AnalyticPage.checkMainElementsPresence();
  });

  it ('Verify mandatory fields', function () {
    AllPages.AnalyticPage.get();
    AllPages.AnalyticPage.checkMandatoryFields();
  });

  it ('Add a Structred Analytics as an authenticated user', function () {
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.get();
    AllPages.RegistrationPage.registerProfile(AllPages.RegistrationPage.simpleUser);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.get();
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.simpleUser.email);
    AllPages.PeoplePage.addRole(AllPages.RegistrationPage.simpleUser.email, 5);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.simpleUser.username, AllPages.RegistrationPage.simpleUser.pass);
    AllPages.AnalyticPage.get();
    AllPages.AnalyticPage.add('Sample Analytic');
    AllPages.StructuredAnalyticsPage.get();
    AllPages.StructuredAnalyticsPage.add('Structured Analytics', 'Sample Analytic');
    AllPages.SamplePage.checkMessage('Structured Analytics (Question Set) Structured Analytics has been created.');
  });
});
