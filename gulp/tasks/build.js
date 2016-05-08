var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('build', function (done) {
  sequence('bower:install', 'styles', 'drush:kw-b', done);
});
