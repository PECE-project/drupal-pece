var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('init', function (done) {
  sequence('build', 'drush:kw-i', 'drush:kw-u', done);
});
