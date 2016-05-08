
var gulp = require('gulp');
var protractor = require('gulp-protractor').protractor;

gulp.task('test:e2e', ['webdriver:start'], function () {
  return gulp.src('tests/e2e/smoke.spec.js')
    .pipe(protractor({
      configFile: 'tests/e2e/smoke.conf.js',
      debug: false
    }));
});
