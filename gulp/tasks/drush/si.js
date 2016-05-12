var gulp = require('gulp');
var shell = require('shelljs');

var cwd = process.cwd(), command, failed, message;
var password = process.env.PECE_DRUPAL_ADMIN_PASS || 'impossiblepassword';
var siteName = process.env.PECE_DRUPAL_SITE_NAME || 'PECE Drupal Distro';
var acceptableErrors = [
  'Couldn\'t write .htaccess file',
  'notify-send command failed'
];

gulp.task('drush:si', function (done) {
  shell.cd(cwd + '/build');

  command = '';
  command += 'drush si pece';
  command += ' --site-name="' + siteName + '"';
  command += ' --account-pass="' + password + '"';
  command += ' --notify';
  command += ' --verbose';
  command += ' -y';

  failed = false;
  shell.exec(command, end).stderr.on('data', onError);

  function end(code) {
    shell.cd(cwd);
    done(failed ? code : 0);
  }

  function onError(data) {
    if (!failed) {
      var message = data.toString();
      failed = !acceptableErrors.some(function (pattern) {
        return message.indexOf(pattern) > -1;
      });
    }
  }
});
