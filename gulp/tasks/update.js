var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('update', function (done) {
  sequence(['drush:kw-u', 'bower:install'], 'styles', done);
});
