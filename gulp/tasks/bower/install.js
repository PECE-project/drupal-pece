
var gulp = require('gulp');
var bower = require('gulp-bower');

gulp.task('bower:install', function () {
  return bower();
});
