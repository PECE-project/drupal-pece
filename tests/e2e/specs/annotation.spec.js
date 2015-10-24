
describe('Annotation', function() {
  beforeAll(function() {
    AuthenticationPage.logout();
    RegistrationPage.registerProfile();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.get();
    PeoplePage.unblock(RegistrationPage.defaultUser.email);
    PeoplePage.addRole(RegistrationPage.defaultUser.email, 5);
    AuthenticationPage.logout();
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    ArtifactTextPage.add('Text Artifact Annotation', 'Lorem ipsum dolar sit.');
    AuthenticationPage.logout();
  });

  afterAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.deleteUser(RegistrationPage.defaultUser.email);
  });

  it('should not be visible for anonymous users.', function() {
    SamplePage.get('content/text-artifact-annotation');
    expect(AnnotationPage.annotateButton.isPresent()).toBe(false);
  });

  it('should have the Question set field required', function() {
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    SamplePage.get('content/text-artifact-annotation');
    AnnotationPage.clickAnnotate();
    AnnotationPage.checkNoQuestionSetEntered();
  });

  // @TODO: This test will be skipped because the add method from the annotation page is not ready yet.
  xit('should be available for Researcher user to create it.', function() {
    AuthenticationPage.login(RegistrationPage.defaultUser.username, RegistrationPage.defaultUser.pass);
    SamplePage.get('content/text-artifact-annotation');
    AnnotationPage.add();
  }).pend('This test will be skipped because the add method from the annotation page is not ready yet');
});
