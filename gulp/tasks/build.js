require('shelljs/global');

var shell    = require('gulp-shell');
var sequence = require('gulp-sequence');
var gulp     = require('gulp');
var profile  = 'profiles/pece';

gulp.task('build', function (done) {
  sequence('bower:install', 'styles', 'drush:kw-b', done);
});

gulp.task('build:dev', ['build'], function (done) {
  var cwd = pwd();
  cd(cwd + '/build');
  exec('drush make ' + profile + '/pece.dev.make --no-core --contrib-destination ' + profile + ' -y');
  cd(cwd);
  done();
});
