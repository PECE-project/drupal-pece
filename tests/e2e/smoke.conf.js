/**
* @file conf.js
*/

var fs = require('fs');
var SeedsAPI = require('drupal-seeds');
var SpecReporter = require('jasmine-spec-reporter');
var HtmlScreenshotReporter = require('protractor-jasmine2-screenshot-reporter');

module.exports.config = {
  params: {
    admin: {
      user: 'admin',
      password: 'impossiblepassword'
    }
  },

  specs: ['smoke.spec.js'],
  baseUrl: 'http://pece.local/',

  capabilities: { 'browserName': 'chrome' },
  framework: 'jasmine2',
  directConnect: true,

  // Here you will set things that have to happen before start testing.
  onPrepare: function() {
    // Load all page objects to the global scope.
    require('./pages/global');

    // Used for non-angular apps
    browser.ignoreSynchronization = true;

    // Add jasmine spec reporter
    jasmine.getEnv().addReporter(new SpecReporter({
      displayFailuresSummary: true,
      displayFailedSpec: true,
      displaySuiteNumber: true,
      displaySpecDuration: true
    }));

    jasmine.getEnv().addReporter(
       new HtmlScreenshotReporter({
         dest: 'screenshots',
         filename: 'PECE-smoke-test-report.html'
       })
     );

    browser.driver.manage().window().maximize();

    // Used to define a default delay between actions.
    var origFn = browser.driver.controlFlow().execute;

    browser.driver.controlFlow().execute = function() {
      var args = arguments;

      // queue 200ms wait.
      origFn.call(browser.driver.controlFlow(), function() {
        return protractor.promise.delayed(100);
      });

      return origFn.apply(browser.driver.controlFlow(), args);
    };

    // Configure Seeds API.
    return SeedsAPI.initProtractor();
  },

  jasmineNodeOpts: {
    showColors: true,
    includeStackTrace: true,
    defaultTimeoutInterval: 999999
  }
};

// Allow for local config customization.
if (fs.existsSync(__dirname + '/config-alter.js')) {
  require(__dirname + '/config-alter.js')(module.exports.config);
}
