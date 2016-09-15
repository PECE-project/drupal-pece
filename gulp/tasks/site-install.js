var gulp = require('gulp');
var sequence = require('gulp-sequence');
var shell = require('shelljs');

gulp.task('site-install', function (done) {
  // Avoid site-install if we are just running a build for the distro.
  if (process.env.IS_PRODUCTION) {
    return done();
  }
  sequence('drush:si', 'drush:kw-apply-module-dependencies', 'drush:cc', done)
});
