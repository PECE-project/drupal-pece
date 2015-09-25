/**
* @file sample.page.js
*/

var EC = protractor.ExpectedConditions;

// This is a sample page file where you will find generic methods to use with drupal.
var SamplePage = function() {

  // Define sample attributes.
  this.body = element(by.css('body'));

  //Define sample methods.
  // The url argument is optional, if not set it just goes to the baseUrl defined in the conf.js file.
  this.get = function(url) {
    if (typeof(url) != 'undefined') {
      browser.get('/' + url);
    } else {
      browser.get('/');
    }
  };

  // Check that the correct drupal theme is used based on a string argument that represents the drupal theme.
  this.checkDrupalTheme = function(theme) {
    expect(browser.executeScript('return Drupal.settings.ajaxPageState.theme')).toEqual(theme);
  };

  this.checkMessage = function(message) {
    browser.wait(EC.visibilityOf(this.body), browser.params.timeoutLimit);
    expect(this.body.getText()).toContain(message);
  };

};

module.exports = new SamplePage();
