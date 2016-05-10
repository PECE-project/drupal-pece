var gulp = require('gulp');
var shell = require('shelljs');

gulp.task('files:disallow-write', function () {
  shell.exec('chmod 755 cnf/files');
});
