var gulp = require('gulp');
var shell = require('shelljs');

gulp.task('drush:kw-s', function () {
  shell.exec('drush kw-s');
});
