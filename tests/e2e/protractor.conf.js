/**
* @file conf.js
*/

var authentication = require('./authentication.js');

exports.config = {
  // The selenium address where the selenium server will be running.
  seleniumAddress: 'http://localhost:4444/wd/hub',

  // Parameters that can be used in the tests.
  params: {
    // Here is where you set the user credentials for tests usage.
    admin: {
      'user': authentication.getInfo('user'),
      'password': authentication.getInfo('password')
    }
  },

  // The test files are stored into the specs array, separated by comma.
  specs: [
    'spec.js'
    , 'authentication.spec.js'
    // , 'task.scheduler.spec.js'
    // , 'performance.spec.js'
    // 'content.spec.js'
  ],

  // Browser configuration.
  capabilities: {
    'browserName': 'chrome'
  },

  // The url that will be used for the tests. With this you can call just the relative urls into the tests.
  // This is also good for running tests in different environments. To do this you just have to change the url here.
  baseUrl: 'http://dev-pece.rpi.dropit.in/',

  // Here you will set things that have to happen before start testing.
  onPrepare: function () {
    var SpecReporter = require('jasmine-spec-reporter');
    // add jasmine spec reporter
    jasmine.getEnv().addReporter(new SpecReporter({
      displayFailuresSummary: true,
      displayFailedSpec: true,
      displaySuiteNumber: true,
      displaySpecDuration: true
    }));
  }
};
