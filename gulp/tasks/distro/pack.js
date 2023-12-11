var gulp = require('gulp');
var shell = require('shelljs');
var fs = require('fs');

var cwd = process.cwd();
var kwEnvConfigFile = cwd + '/cnf/environment';
var repo = 'https://github.com/PECE-project/pece-distro.git';
var commitMessage = 'New release based on master of development repository.';

function distroPack() {
  gulp.series(distroPrepare, function () {
    shell.cd('distro');
    shell.exec('git add -A');
    // shell.exec('git commit -m "' + commitMessage + '"');
    //shell.exec('git push ' + repo + ' master');
  });
}

gulp.task('distro:pack', distroPack);

exports.distroPack = distroPack;
