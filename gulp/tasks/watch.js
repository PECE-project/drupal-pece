var gulp = require('gulp');

gulp.task('watch:styles', ['styles'], function () {
  gulp.watch('src/themes/pece_scholarly_lite/assets/sass/**/*', ['styles']);
});

gulp.task('watch', ['watch:styles']);
