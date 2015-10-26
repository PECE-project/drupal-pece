
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
    AuthenticationPage.logout();

    RegistrationPage.register(creatorData.name, creatorData.email, browser.params.admin.password, true);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(creatorData.email);
    PeoplePage.addRole(creatorData.email, creatorData.role);
    AuthenticationPage.logout();

    AuthenticationPage.login(creatorData.name, browser.params.admin.password);
    ArtifactTextPage.get();
    ArtifactTextPage.add(artifactName, 'user-access-file');
    UserAccessPage.editArtifactPermission(artifactName, 'restricted');
  });

  it ('restricted artifact should be allowed to creator and researchers', function() {
    UserAccessPage.expectAllowedContent(artifactName);
    AuthenticationPage.logout();

    RegistrationPage.register(researcherData.name, researcherData.email, browser.params.admin.password, true);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(researcherData.email);
    PeoplePage.addRole(researcherData.email, researcherData.role);
    AuthenticationPage.logout();

    AuthenticationPage.login(researcherData.name, browser.params.admin.password);
    PeceArtifactPage.getArtifact(artifactName);
    UserAccessPage.expectAllowedContent(artifactName);
    AuthenticationPage.logout();
  });

  it ('restricted artifact should be denied to contributor', function() {
    RegistrationPage.register(contributorData.name, contributorData.email, browser.params.admin.password, true);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.unblock(contributorData.email);
    PeoplePage.addRole(contributorData.email, contributorData.role);
    AuthenticationPage.logout();

    AuthenticationPage.login(contributorData.name, browser.params.admin.password);
    PeceArtifactPage.getArtifact(artifactName);
    UserAccessPage.expectDenyMessage();
    AuthenticationPage.logout();
  });

  it('private artifact should only be allowed to creator', function() {
    AuthenticationPage.login(creatorData.name, browser.params.admin.password);
    UserAccessPage.editArtifactPermission(artifactName, 'private');
    AuthenticationPage.logout();

    AuthenticationPage.login(creatorData.name, browser.params.admin.password);
    PeceArtifactPage.getArtifact(artifactName);
    UserAccessPage.expectAllowedContent(artifactName);
    AuthenticationPage.logout();

    AuthenticationPage.login(contributorData.name, browser.params.admin.password);
    PeceArtifactPage.getArtifact(artifactName);
    UserAccessPage.expectDenyMessage();
    AuthenticationPage.logout();

    AuthenticationPage.login(researcherData.name, browser.params.admin.password);
    PeceArtifactPage.getArtifact(artifactName);
    UserAccessPage.expectDenyMessage();
    AuthenticationPage.logout();
  });

  afterAll(function() {
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.deleteUser(creatorData.email);
    PeoplePage.deleteUser(researcherData.email);
    PeoplePage.deleteUser(contributorData.email);
    AuthenticationPage.logout();
  });
});
