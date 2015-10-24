/**
* @file group.spec.js
*/

describe ('Group', function () {
  beforeAll(function() {
    AuthenticationPage.logout();
  });

  it('Should display group thumbnail field', function() {
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    GroupPage.checkThumbnailField();
  });

  afterAll(function() {
    AuthenticationPage.logout();
  });
});
