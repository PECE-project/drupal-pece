var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd();

gulp.task('site-uninstall', function () {
  if (shell.test('-d', 'build')) {
    shell.cd('build');
    shell.exec('drush sql-drop -y');
    shell.cd(cwd);
  }

  shell.rm('-rf', 'cnf/files');
});
