
var gulp = require('gulp');

gulp.task('watch', ['build'], function () {
  gulp.watch('./src/themes/**/assets/sass/**/*', ['sass']);
});
