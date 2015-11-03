
var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('update', function (done) {
  sequence(['bower:install'], 'styles', done);
});
