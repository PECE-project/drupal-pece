var gulp = require('gulp');
var util = require('../../lib/util');
var spawn = require('child_process').spawn;
var webdriverPath = process.cwd() + '/node_modules/.bin/webdriver-manager';
var webdriver;

gulp.task('webdriver:start', function (done) {
  var tryAgain = null;
  var fuser;

  // Check if port 4444 is already in use. In this case, probably the
  // developer has already started a webdriver-manager instance.
  util.isPortTaken(4444, function (err, used) {
    err || used ? done(err) : webdriverStart();
  });

  /**
   * Webdriver starter. Encapsulated so we can try again.
   */
  function webdriverStart() {
    webdriver = spawn(webdriverPath, ['start']);
    webdriver.stdout.on('data', onMessage);
    webdriver.stderr.on('data', onMessage);
    webdriver.once('close', onClose);
  }

  /**
   * Close event from webdriver child process.
   */
  function onClose() {
    if (tryAgain) {
      tryAgain = false;
      fuser = spawn('fuser', ['-k', '4444/tcp']);
      return fuser.on('close', webdriverStart);
    }

    done('Could not initiate webdriver. Make sure this machine has an available display (either real or xfvb).');
  }

  /**
   * Message received from webdriver child process.
   */
  function onMessage(data) {
    var notOk = false;

    var expectedMessages = {
      'Selenium Standalone is not present'      : 'error',
      'Selenium Server is up and running'       : 'success',
      'Selenium is already running on port 4444': 'success'
    };

    Object.keys(expectedMessages).some(function (message) {
      if (data.indexOf(message) > -1) {
        done(expectedMessages[message] == 'error' ? message : null);
        return true;
      }
    });
  }
});
