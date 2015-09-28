/**
* @file user.access.page.js
*/

var EC = protractor.ExpectedConditions;

var UserAccessPage = function() {

  this.getArtifact = function(node) {
    browser.get('content/' + node);
  };

  this.getArtifactForm = function(node) {
    this.getArtifact(node);
    element(by.cssContainingText('a', 'Edit')).click();
  };

  this.editArtifactPermission = function (node, permission) {
    this.getArtifactForm(node);

    if (permission === 'restricted') {
      browser.executeScript('jQuery("#edit-field-permissions-und-restricted").click();');
    }

    if (permission === 'private') {
      browser.executeScript('jQuery("#edit-field-permissions-und-private").click();');
    }

    $('#edit-submit').click();
  };

  this.expectDenyMessage = function() {
    expect(element(by.cssContainingText('h1', 'Access denied')).isPresent()).toBe(true);
  };

  this.expectAllowedContent = function(title) {
    expect(element(by.cssContainingText('h1', title)).isPresent()).toBe(true);
  };

};

module.exports = new UserAccessPage();
