var gulp = require('gulp');
var sequence = require('gulp-sequence');

gulp.task('site-install', ['drush:si']);
