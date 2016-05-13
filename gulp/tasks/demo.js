var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd();

gulp.task('demo', function () {
  shell.cd(cwd + '/build');
  shell.exec('drush pece-demo');
  shell.cd(cwd);
});
