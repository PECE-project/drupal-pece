var gulp = require('gulp');
var shell = require('shelljs');

gulp.task('files:allow-write', function () {
  shell.exec('chmod 777 cnf/files');
});
