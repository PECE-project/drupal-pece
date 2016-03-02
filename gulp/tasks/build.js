require('shelljs/global');

var shell    = require('gulp-shell');
var sequence = require('gulp-sequence');
var gulp     = require('gulp');
var profile  = 'profiles/pece';

gulp.task('build', ['styles'], function (done) {
  sequence('drush:kw-b', ['drush:kw-u', 'update'], done);
});

gulp.task('build:dev', ['drush:kw-b'], function (done) {
  var cwd = pwd();
  cd(cwd + '/build');
  exec('drush make ' + profile + '/pece.dev.make --no-core --contrib-destination ' + profile + ' -y');
  cd(cwd);

  sequence(['drush:kw-u', 'update'], done);
});
