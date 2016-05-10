var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('site-install', function (done) {
  sequence('files:allow-write', 'drush:si', 'files:disallow-write', done);
});
