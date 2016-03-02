var shell    = require('gulp-shell');
var sequence = require('gulp-sequence');
var gulp     = require('gulp');

gulp.task('build', ['styles'], function (done) {
  sequence('drush:kw-b', ['drush:kw-u', 'update'], done);
});

gulp.task('build:dev', ['styles'], function (done) {
  var cwd = pwd();
  cd(cwd + '/build');
  exec('drush make profiles/pece/pece.dev.make --no-core -y');
  cd(cwd);

  sequence('drush:kw-b', ['drush:kw-u', 'update'], done);
});
