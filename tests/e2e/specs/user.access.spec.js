/**
* @file user.access.spec.js
*/

// Require authentication page object.
var AllPages = require('../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('User Access' , function () {

  var artifactName = 'myartifact',

      creatorData = {
        name:  'creator',
        email: 'creator@foo.bar',
        role:  5
      },

      contributorData = {
        name:  'contr',
        email: 'contr@foo.bar',
        role:  5
      },

      researcherData = {
        name:  'rsrchr',
        email: 'rsrchr@foo.bar',
        role:  6
      };

  beforeAll(function() {
    AllPages.AuthenticationPage.logout();

    AllPages.RegistrationPage.register(creatorData.name, creatorData.email, browser.params.admin.password, true);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(creatorData.email);
    AllPages.PeoplePage.addRole(creatorData.email, creatorData.role);
    AllPages.AuthenticationPage.logout();

    AllPages.AuthenticationPage.login(creatorData.name, browser.params.admin.password);
    AllPages.ArtifactTextPage.get();
    AllPages.ArtifactTextPage.add(artifactName, 'user-access-file');
    AllPages.UserAccessPage.editArtifactPermission(artifactName, 'restricted');
  });

  it ('restricted artifact should be allowed to creator and researchers', function() {
    AllPages.UserAccessPage.expectAllowedContent(artifactName);
    AllPages.AuthenticationPage.logout();

    AllPages.RegistrationPage.register(researcherData.name, researcherData.email, browser.params.admin.password, true);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(researcherData.email);
    AllPages.PeoplePage.addRole(researcherData.email, researcherData.role);
    AllPages.AuthenticationPage.logout();

    AllPages.AuthenticationPage.login(researcherData.name, browser.params.admin.password);
    AllPages.UserAccessPage.getArtifact(artifactName);
    AllPages.UserAccessPage.expectAllowedContent(artifactName);
    AllPages.AuthenticationPage.logout();
  });

  it ('restricted artifact should be denied to contributor', function() {
    AllPages.RegistrationPage.register(contributorData.name, contributorData.email, browser.params.admin.password, true);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.unblock(contributorData.email);
    AllPages.PeoplePage.addRole(contributorData.email, contributorData.role);
    AllPages.AuthenticationPage.logout();

    AllPages.AuthenticationPage.login(contributorData.name, browser.params.admin.password);
    AllPages.UserAccessPage.getArtifact(artifactName);
    AllPages.UserAccessPage.expectDenyMessage();
    AllPages.AuthenticationPage.logout();
  });

  it('private artifact should only be allowed to creator', function() {
    AllPages.AuthenticationPage.login(creatorData.name, browser.params.admin.password);
    AllPages.UserAccessPage.editArtifactPermission(artifactName, 'private');
    AllPages.AuthenticationPage.logout();

    AllPages.AuthenticationPage.login(creatorData.name, browser.params.admin.password);
    AllPages.UserAccessPage.getArtifact(artifactName);
    AllPages.UserAccessPage.expectAllowedContent(artifactName);
    AllPages.AuthenticationPage.logout();

    AllPages.AuthenticationPage.login(contributorData.name, browser.params.admin.password);
    AllPages.UserAccessPage.getArtifact(artifactName);
    AllPages.UserAccessPage.expectDenyMessage();
    AllPages.AuthenticationPage.logout();

    AllPages.AuthenticationPage.login(researcherData.name, browser.params.admin.password);
    AllPages.UserAccessPage.getArtifact(artifactName);
    AllPages.UserAccessPage.expectDenyMessage();
    AllPages.AuthenticationPage.logout();
  });

  afterAll(function() {
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser(creatorData.email);
    AllPages.PeoplePage.deleteUser(researcherData.email);
    AllPages.PeoplePage.deleteUser(contributorData.email);
    AllPages.AuthenticationPage.logout();
  });
});
