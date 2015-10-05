/**
 * @file Test related Gulp tasks.
 */

var gulp = require('gulp')
  , request = require('request')
  , mocha = require('gulp-mocha')
  , spawn = require('child_process').spawn
  , webdriver
  , protractor

/**
 * Print buffer string.
 */
function logBuffer(data) {
  console.log(data.toString());
}

/**
 * Swallow any errors.
 */
function swallowError (error) {
  logBuffer(error);
  this.emit('end');
}

/**
 * Initiates webdriver.
 */
gulp.task('webdriver', function (done) {
  var started = false;

  /**
   * Check if webdriver is ready.
   */
  function ready(buffer) {
    if (!started && buffer.toString().indexOf('Started SocketListener') !== -1) {
      started = true;
      done();
    } else if (!started) {
      logBuffer(buffer);
    }
  }
  webdriver = spawn('webdriver-manager', ['start']);
  webdriver.stdout.on('data', ready);
  webdriver.stderr.on('data', ready);

  webdriver.on('exit', function (code) {
    // Make sure selenium stops.
    request('http://localhost:4444/selenium-server/driver/?cmd=shutDownSeleniumServer', function (err, res, body) {
      if (body == 'OKOK') {
        webdriver.emit('exitSelenium');
      }
    });
  });
});

/**
 * E2E test: uses Protractor to perform e2e tests.
 */
gulp.task('test:e2e', ['webdriver'], function (done) {
  protractor = spawn('protractor', ['tests/e2e/protractor.conf.js']);
  protractor.stdout.on('data', logBuffer);
  protractor.stderr.on('data', logBuffer);

  protractor.on('exit', function (code) {
    webdriver.kill('SIGHUP');
  });

  webdriver.on('exitSelenium', done);
});

/**
 * Unit test: uses Karma to test ElTracker front-end scripts.
 */
gulp.task('test:unit', function () {
  return gulp.src('tests/unit/**/*.js', { read: false })
    .pipe(mocha())
    .on('error', swallowError);
});

gulp.task('test:unit:watch', ['test:unit'], function () {
  return gulp.watch('tests/unit/**/*.js', ['test:unit']);
});

gulp.task('test', ['test:unit', 'test:e2e']);
