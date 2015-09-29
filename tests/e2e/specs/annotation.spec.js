/**
* @file artifact.image.spec.js
*/

var AllPages = require('../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('Annotation', function() {
  // This is the pre-condition step of each test.
  beforeEach(function() {
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
    AllPages.ArtifactTextPage.add('Text Artifact Annotation', 'Lorem ipsum dolar sit.');
    AllPages.AuthenticationPage.logout();
    AllPages.SamplePage.get('content/text-artifact-annotation');
  });

  afterAll(function() {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.deleteUser(AllPages.RegistrationPage.defaultUser.email);
  });

  it('Verify if anonymous users cannot see annotation button', function() {
    expect(AllPages.AnnotationPage.annotateButton.isPresent()).toBe(false);
  });

  // @TODO: Finish annotate wizard form tests.
  // it('Verify Question set field requirement', function() {
  //   AllPages.AnnotationPage.clickAnnotate();
  //   AllPages.AnnotationPage.checkNoQuestionSetEntered();
  // });
});
