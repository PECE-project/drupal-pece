var gulp = require('gulp');
var styles = require('./styles');

function watchStyles(done) {
  gulp.series(styles, function (done) {
    gulp.watch('src/themes/pece_scholarly_lite/assets/sass/**/*', gulp.series('styles'));
  })(done);
}

gulp.task('watch:styles', watchStyles);

gulp.task('watch', gulp.series('watch:styles'));
