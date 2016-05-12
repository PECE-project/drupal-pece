var gulp = require('gulp');
var shell = require('shelljs');
var util = require('../../lib/util');

var cwd = process.cwd();

gulp.task('drush:kw-apply-module-dependencies', function (done) {
  util.environment(function (err, env) {
    shell.cd('build');
    shell.exec('drush kw-apply-module-dependencies ' + (env || 'production'));
    shell.cd(cwd);
    done();
  });
});
