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

gulp.task('distro:clone', function (done) {
  // Clone distro repository.
  fs.stat('distro', function (err) {
    if (err == null) {
      shell.exec('rm -rf distro');
    }
    cloneDistroRepo(done);
  });

});

gulp.task('distro:sync', function (done) {
  // Sync latest local build with PECE Distro repo.
  syncLocalFiles(done);
});

gulp.task('distro:build', function (done) {
  // Build distro to production environment.
  rebuildToProd();
  done();
});


gulp.task('distro:build:sync', function (done) {
  // Build to production and Sync the result with PECE Distro repo.
  rebuildToProd();
  syncLocalFiles();
  done();
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
  cloneDistroRepo();
  syncLocalFiles();
  done();
}

var cloneDistroRepo = function (done) {
  // Clone PECE Distro repository.
  shell.exec('git clone ' + repo + ' distro');
  done();
}

var syncLocalFiles = function (done) {
  // Update distro repository with a new production build.
  shell.exec('rsync -rptgohD --delete --progress --exclude=profiles/pece/docs  build/* distro/');
  done();
}
