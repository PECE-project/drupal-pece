// See https://github.com/angular/protractor/blob/master/docs/referenceConf.js for reference
exports.config = {
  // Attach to Selenium server running within the container
  seleniumAddress: 'http://localhost:4444/wd/hub',

  // Use Jasmine 2.x
  framework : 'jasmine2',
  specs: [
    'spec.js'
  ],

  baseUrl: 'http://pece.revax.com.br',

  // Chrome is not allowed to create a SUID sandbox when running inside Docker
  capabilities: {
    'browserName': 'chrome',
    'chromeOptions': {
      'args': ['no-sandbox']
    }
  }
};
