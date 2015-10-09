
var gulp = require('gulp');
var protractor = require("gulp-protractor").protractor;

gulp.task('test:e2e', ['webdriver:start'], function () {
  return gulp.src('tests/e2e/specs/spec.js')
    .pipe(protractor({
      configFile: 'tests/e2e/protractor.conf.js',
      debug: false
    }));
});
