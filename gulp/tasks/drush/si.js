var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd(), command;
var password = process.env.PECE_DRUPAL_ADMIN_PASS || 'impossiblepassword';
var siteName = process.env.PECE_DRUPAL_SITE_NAME || 'PECE Drupal Distro';

gulp.task('drush:si', function () {
  command = '';
  command += 'drush si pece';
  command += ' --site-name="' + siteName + '"';
  command += ' --account-pass="' + password + '"';
  command += ' --notify';
  command += ' --verbose';
  command += ' -y';

  shell.cd(cwd + '/build');
  shell.exec(command);
  shell.cd(cwd);
});
