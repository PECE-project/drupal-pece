/**
* @file user_profile.spec.js
*/

// Require all page objects.
var AllPages = require('../pages/all.page');

describe ('User profile' , function () {
  beforeAll(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.SamplePage.get('admin/config/people/legal');
    AllPages.LegalPage.create();
  });

  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
  });

  afterAll(function () {
    AllPages.PeoplePage.deleteUser('foob@bar.baz');
    AllPages.PeoplePage.deleteUser('boof@bar.baz');
  });

  it ('should create a new user profile', function () {
    var user = {
      username: 'foob',
      email: 'foob@bar.baz',
      pass: browser.params.admin.password,
      name: 'Foo B.',
      institutions: 'Institution',
      position: 'Trainee',
      bio: 'Lorem ipsum',
      location: {
        label: 'Sweet Home',
        street: 'street',
        additional: 'additional',
        country: 'Brazil'
      },
      tags: 'tagFoo',
      tos: true
    };
    AllPages.RegistrationPage.registerProfile(user);
    expect(AllPages.SamplePage.body.getText()).toContain('Your account is currently pending approval by the site administrator.');
  });

  it('check user profile after registration', function () {
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
        country: 'Brazil'
      },
      tags: 'tagFoo',
      tos: true
    };
    AllPages.RegistrationPage.registerProfile(user);
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.PeoplePage.edit(email);
    AllPages.UserProfilePage.accessProfileForm();
    AllPages.UserProfilePage.checkGeocoding();
    expect(AllPages.UserProfilePage.nameField.getAttribute('value')).toEqual(user.name);
    expect(AllPages.UserProfilePage.emailField.getAttribute('value')).toEqual(email);
    expect(AllPages.UserProfilePage.institutionField.getAttribute('value')).toEqual(user.institution);
    expect(AllPages.UserProfilePage.positionField.getAttribute('value')).toEqual(user.position);
    expect(AllPages.UserProfilePage.bioField.getText()).toEqual(user.bio);
    expect(AllPages.UserProfilePage.tagsField.getAttribute('value')).toEqual(user.tags);
  });
});
