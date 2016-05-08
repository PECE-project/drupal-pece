var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd(), command;
var password = process.env.PECE_DRUPAL_ADMIN_PASS || 'impossiblepassword';

gulp.task('drush:sample-content', function () {
  command = 'PASSWORD=' + password + ' ' + cwd + '/scripts/sample-content.sh';

  shell.cd(cwd + '/build');
  shell.exec(command);
  shell.cd(cwd);
});
