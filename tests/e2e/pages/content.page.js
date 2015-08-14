/**
* @file content.page.js
*/

var EC = protractor.ExpectedConditions;

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
		browser.wait(EC.visibilityOf(this.titleField), browser.params.timeoutLimit);
		this.titleField.clear();
    this.titleField.sendKeys(contentTitle);
    this.applyButton.click();
  };

  this.remove = function (title) {
    this.filter(title);
    browser.wait(EC.visibilityOf(element(by.cssContainingText('a', title))), browser.params.timeoutLimit);
    element(by.cssContainingText('a', title)).click();
		browser.wait(EC.visibilityOf(element(by.cssContainingText('.tabs a', 'Edit'))), browser.params.timeoutLimit);
    element(by.cssContainingText('.tabs a', 'Edit')).click();
		browser.wait(EC.visibilityOf(element(by.css('#edit-delete'))), browser.params.timeoutLimit);
    element(by.css('#edit-delete')).click();
		browser.wait(EC.visibilityOf(element(by.css('#edit-submit'))), browser.params.timeoutLimit);
    element(by.css('#edit-submit')).click();
  };

};

module.exports = new ContentPage();
