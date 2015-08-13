/**
* @file sample.page.js
*/

var EC = protractor.ExpectedConditions;

// This is a sample page file where you will find generic methods to use with drupal.
var SamplePage = function () {

  // Define sample attributes.
  this.errorMessage = element(by.css('.messages.error'));
  this.successMessage = element(by.css('#messages .alert-success'));

  //Define sample methods.
  // The url argument is optional, if not set it just goes to the baseUrl defined in the conf.js file.
  this.get = function (url) {
    if (typeof(url) != 'undefined') {
      browser.get('/' + url);
    } else {
      browser.get('/');
    }
  };

  // Check that the correct drupal theme is used based on a string argument that represents the drupal theme.
  this.checkDrupalTheme = function (theme) {
    expect(browser.executeScript('return Drupal.settings.ajaxPageState.theme')).toEqual(theme);
  };

  this.checkSuccessMessage = function (message) {
    browser.wait(EC.visibilityOf(this.successMessage ), browser.params.timeoutLimit);
    expect(this.successMessage.getText()).toContain(message);
  };

  this.checkErrorMessage = function (message) {
    browser.wait(EC.visibilityOf(this.errorMessage ), browser.params.timeoutLimit);
    expect(this.errorMessage.getText()).toContain(message);
  };

};

module.exports = new SamplePage();
