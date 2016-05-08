var gulp = require('gulp');
var sass = require('gulp-sass');
var autoprefixer = require('gulp-autoprefixer');

gulp.task('styles', function () {
  return gulp.src('src/themes/pece_scholarly_lite/assets/sass/sources/**/*')
    .pipe(sass({
      includePaths: [
        'src/themes/pece_scholarly_lite/assets/sass/library',
        'src/themes/pece_scholarly_lite/assets/sass/partials'
      ]
    }).on('error', sass.logError))
    .pipe(autoprefixer({
      browsers: ['last 2 versions'],
      cascade: false
    }))
    .pipe(gulp.dest('src/themes/pece_scholarly_lite/assets/css'));
});
