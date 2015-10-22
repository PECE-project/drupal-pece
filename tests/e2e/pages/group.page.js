/**
 * @file group.page.js
 */

var GroupPage = function() {
  // Define add types methods.
  this.get = function () {
    browser.get('node/add/pece-group');
  };

  this.checkThumbnailField = function () {
    this.get();
    var message = 'Group thumbnail field is not being displayed in add group form.';
    expect($('#edit-field-pece-media-image').isPresent()).toBe(false, message);
  };
}

module.exports = new GroupPage;
