var gulp = require('gulp');
var shell = require('shelljs');
var fs = require('fs');

var cwd = process.cwd();
var kwEnvConfigFile = cwd + '/cnf/environment';
var repo = 'https://github.com/revagomes/pece-distro.git';
var commitMessage = 'Added new release based on master of development repository.'

gulp.task('pack-distro', function () {
  // Clone distro repository.
  fs.stat('distro', function (err) {
    if (err == null) {
      shell.exec('rm -rf distro');
    }
    packDistroCallback();
  });

});

var packDistroCallback = function () {
  if (!process.env.IS_PRODUCTION) {
    // Backup kw previous config and set kraftwagen env config to production
    // in order to prevent symlinks in the profile filder.
    shell.exec('mv ' + kwEnvConfigFile + ' ' + kwEnvConfigFile + '.bkp');

    shell.exec('drush kw-setup-env production');
    shell.exec('drush kw-b');

    // Remove the updated config file and restore previous kraftwagen env config.
    shell.exec('rm ' + kwEnvConfigFile);
    shell.exec('mv ' + kwEnvConfigFile + '.bkp ' + kwEnvConfigFile);

    return;
  }

  shell.exec('git clone ' + repo + ' distro');

  // Update distro repository with a new build.
  shell.exec('rsync -rptgohD --delete --progress --exclude=profiles/pece/docs  build/* distro/');
  shell.cd('distro');
  shell.exec('git add -A');

  shell.exec('git commit -m "' + commitMessage + '"');
  shell.exec('git push ' + repo + ' master');
}
