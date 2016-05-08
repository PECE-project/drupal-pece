var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd();

gulp.task('drush:kw-u', function () {
  shell.cd(cwd + '/build');
  shell.exec('drush kw-u');
  shell.cd(cwd);
});
