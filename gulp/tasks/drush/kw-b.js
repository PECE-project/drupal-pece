require('shelljs/global');

var gulp = require('gulp');

gulp.task('drush:kw-b', function () {
  exec('drush kw-b');
});
