/**
* @file group.spec.js
*/

var AllPages = require('../pages/all.page');

describe ('Group', function () {
  beforeAll(function() {
    AllPages.AuthenticationPage.logout();
  });

  it('Should display group thumbnail field', function() {
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    AllPages.GroupPage.checkThumbnailField();
  });

  afterAll(function() {
    AllPages.AuthenticationPage.logout();
  });
});
