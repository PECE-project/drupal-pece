var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('config', function(done) {
  sequence('config:environment', 'config:settings', done);
});
