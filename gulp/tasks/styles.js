var gulp = require('gulp');
// var sass = require('gulp-sass');
const sass = require('gulp-sass')(require('sass'));


// change to dynamic import
var autoprefixer;

async function styles() {
  if (!autoprefixer) {
    autoprefixer = (await import('gulp-autoprefixer')).default;
  }

  return gulp.src('src/themes/pece_scholarly_lite/assets/sass/sources/**/*')
    .pipe(sass({
      includePaths: [
        'src/themes/pece_scholarly_lite/assets/sass/library',
        'src/themes/pece_scholarly_lite/assets/sass/partials'
      ]
    }).on('error', sass.logError))
    .pipe(autoprefixer({
      cascade: false
    }))
    .pipe(gulp.dest('src/themes/pece_scholarly_lite/assets/css'));
}

gulp.task('styles', styles);

exports.default = styles;
