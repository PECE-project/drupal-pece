/**
* @file content.page.js
*/

// This is an object used for mananing drupal contents.
var ContentPage = function () {

	// Define content attributes.
	this.titleField = element(by.css('#views-exposed-form-admin-views-node-system-1 #edit-title'));
  this.applyButton = element(by.css('#views-exposed-form-admin-views-node-system-1 #edit-submit-admin-views-node'));

	//Define content methods.
	this.get = function () {
    browser.get('/admin/content');
  };

  this.filter = function (contentTitle) {
    this.titleField.sendKeys(contentTitle);
    browser.driver.sleep(100);
    this.applyButton.click();
    browser.driver.sleep(1000);
  };

  this.remove = function (title) {
    browser.driver.sleep(3000);
    this.filter(title);
    browser.driver.sleep(3000);
    element(by.cssContainingText('a', title)).click().then(function () {
			browser.driver.sleep(3000);
      element(by.cssContainingText('.tabs a', 'Edit')).click().then(function () {
				browser.driver.sleep(3000);
        element(by.css('#edit-delete')).click().then(function () {
					browser.driver.sleep(2000);
          element(by.css('#edit-submit')).click();
					browser.driver.sleep(3000);
        });
      });
    });
  };

};

module.exports = new ContentPage();
