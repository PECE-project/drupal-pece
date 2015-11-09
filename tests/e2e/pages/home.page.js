/**
* @file home.page.js
*/

var EC = protractor.ExpectedConditions;

// This is a sample page file where you will find generic methods to use with drupal.
var HomePage = function() {

  this.mainElements = {

    // Form main elements.
    groupsSection: $('.pane-pece-recent-groups-panel-pane-1 .pane-title'),
    artifactsSection: $('.pane-pece-recent-artifacts-panel-pane-1 .pane-title'),
    tagsSection: $('.pane-tagclouds-3 .pane-title'),
  };

  //Define sample methods.
  // The url argument is optional, if not set it just goes to the baseUrl defined in the conf.js file.
  this.get = function(url) {
    if (typeof(url) != 'undefined') {
      browser.get('/' + url);
    } else {
      browser.get('/');
    }
  };

};

module.exports = new HomePage();
