/**
* @file user.profile.spec.js
*/

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc.
// It depends on the team's work agreement.
describe('User profile', function() {
  beforeAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();
  });

  beforeEach(function() {
    AuthenticationPage.logout();
  });

  afterAll(function() {
    AuthenticationPage.logout();
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.deleteUser('boof@bar.baz');
  });

  it('should create a new user profile', function() {
    RegistrationPage.registerProfile();
    SamplePage.checkMessage('Your account is currently pending approval by the site administrator.');
  });

  it('check user profile after registration', function() {
    var email = 'boof@bar.baz'
      , user = {
      username: 'boof',
      email: email,
      pass: browser.params.admin.password,
      name: 'Boo F.',
      institution: 'Institution',
      position: 'Trainee',
      bio: 'Lorem ipsum',
      location: {
        label: 'Taller Web Solutions',
        street: 'Servidão Recanto das Pedras, 3',
        additional: 'Rio Tavares - Florianópolis',
        province: 'Santa Catarina',
        country: 'Brazil'
      },
      tags: 'tagFoo',
      tos: true
    };
    RegistrationPage.registerProfile(user);
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    PeoplePage.edit(email);
    UserProfilePage.accessProfileForm();
    UserProfilePage.checkGeocoding();
    expect(UserProfilePage.nameField.getAttribute('value')).toEqual(user.name);
    expect(UserProfilePage.emailField.getAttribute('value')).toEqual(email);
    expect(UserProfilePage.institutionField.getAttribute('value')).toEqual(user.institution);
    expect(UserProfilePage.positionField.getAttribute('value')).toEqual(user.position);
    expect(UserProfilePage.bioField.getText()).toEqual(user.bio);
    expect(UserProfilePage.tagsField.getAttribute('value')).toEqual(user.tags);
  });
});
