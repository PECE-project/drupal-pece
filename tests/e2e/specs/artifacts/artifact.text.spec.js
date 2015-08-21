/**
* @file artifact.text.spec.js
*/

var AllPages = require('../../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('Text Artifact' , function () {
  // This its the pre-condition step of each test.
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  afterAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.ContentPage.get();
    AllPages.ContentPage.remove('Text Artifact');
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it ('Verify main elements presence', function () {
   AllPages.ArtifactTextPage.get();
   AllPages.ArtifactTextPage.checkMainElementsPresence();
  });

  it ('Verify mandatory fields', function () {
    AllPages.ArtifactTextPage.get();
    AllPages.ArtifactTextPage.checkMandatoryFields();
  });

  it ('Add a Text artifact as an authenticated user', function () {
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
    AllPages.AuthenticationPage.logout();
    AllPages.RegistrationPage.get();
    AllPages.RegistrationPage.registerProfile();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.get();
    AllPages.PeoplePage.unblock(AllPages.RegistrationPage.defaultUser.email);
    AllPages.PeoplePage.addRole(AllPages.RegistrationPage.defaultUser.email, 5);
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(AllPages.RegistrationPage.defaultUser.username, AllPages.RegistrationPage.defaultUser.pass);
    AllPages.ArtifactTextPage.get();
    AllPages.ArtifactTextPage.add('Text Artifact', 'Lorem ipsum dolar sit.');
    AllPages.ArtifactTextPage.checkPageLayout();
    AllPages.ArtifactTextPage.checkPageElements();
  });
});
