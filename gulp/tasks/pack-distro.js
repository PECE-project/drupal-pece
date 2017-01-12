var gulp = require('gulp');
var shell = require('shelljs');
var sequence = require('gulp-sequence');
var fs = require('fs');

var cwd = process.cwd();
var repo = 'https://github.com/PECE-project/pece-distro.git';
// var repo = 'https://github.com/revagomes/pece-distro.git';
var commitMessage = 'Added new release based on master of development repository.'

gulp.task('pack-distro', function (done) {
  // Clone distro repository.
  fs.stat('distro', function (err) {
    if (err == null) {
      shell.exec('rm -rf distro');
    }
    packDistroCallback(done);
  });

});

var packDistroCallback = function (done) {
  shell.exec('drush kw-setup-env production');
  sequence('build', function (cb) {
    shell.exec('drush kw-setup-env development');
    shell.exec('git clone ' + repo + ' distro');

    // Update distro repository with a new build.
    shell.exec('rsync -rkptgozhD --delete --progress --exclude=profiles/pece/docs  build/* distro/');
    shell.cd('distro');

  // shell.exec('rm profiles/pece/.gitignore');

  //   var gitIgnoreDistro = `# ignore modules in kraftwagen, but keep the README.md
  //   modules/dev/*
  //   !modules/dev/README.md
  //
  //   # OS specific files
  //   .DS_Store
  //   Thumbs.db
  // `;
    // shell.exec('echo ' + gitIgnoreDistro + ' >> .gitignore');

    shell.exec('git add -A');


    // shell.exec('git add profiles/pece -f');
    // shell.exec('git reset profiles/pece/docs');
    // shell.exec('git reset profiles/pece/modules/dev');

    shell.exec(`git commit -m "${ commitMessage }"`);
    // shell.exec(`git push ${repo} master`);
    cb();
  }, done);
}
