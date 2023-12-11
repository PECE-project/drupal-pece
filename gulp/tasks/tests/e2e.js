
var gulp = require('gulp');
var protractor = require('gulp-protractor').protractor;

var webdriverStart = require('../webdriver/start');

function e2e(done) {
  gulp.series(webdriverStart, function (done) {
    return gulp.src('tests/e2e/smoke.spec.js')
      .pipe(protractor({
        configFile: 'tests/e2e/smoke.conf.js',
        debug: false
      }));
  })
}

gulp.task('test:e2e', e2e);

exports.default = e2e;
