var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('site-install', function (done) {
  sequence('drush:si', 'drush:kw-apply-module-dependencies', done)
});
