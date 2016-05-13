var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd();

gulp.task('drush:cc', function () {
  shell.cd(cwd + '/build');
  shell.exec('drush cc all');
  shell.cd(cwd);
});
