var gulp = require('gulp');
var shell = require('shelljs');
var fs = require('fs');

var cwd = process.cwd();
var kwEnvConfigFile = cwd + '/cnf/environment';
var repo = 'https://github.com/PECE-project/pece-distro.git';

gulp.task('distro:prepare', function (done) {
  // Clone distro repository.
  fs.stat('distro', function (err) {
    if (err == null) {
      shell.exec('rm -rf distro');
    }
    prepareDistro(done);
  });

});

var rebuildToProd = function () {
  // Backup kw previous config and set kraftwagen env config to production
  // in order to prevent symlinks in the profile folder.
  shell.exec('mv ' + kwEnvConfigFile + ' ' + kwEnvConfigFile + '.bkp');

  shell.exec('drush kw-setup-env production');
  shell.exec('drush kw-b');

  // Remove the updated config file and restore previous kraftwagen env config.
  shell.exec('rm ' + kwEnvConfigFile);
  shell.exec('mv ' + kwEnvConfigFile + '.bkp ' + kwEnvConfigFile);
}

var prepareDistro = function (done) {
  rebuildToProd();

  shell.exec('git clone ' + repo + ' distro');

  // Update distro repository with a new build.
  shell.exec('rsync -rptgohD --delete --progress --exclude=profiles/pece/docs  build/* distro/');

  done();
}
