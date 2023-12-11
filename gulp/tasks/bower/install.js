var gulp = require('gulp');
var bower = require('gulp-bower');

function bowerInstall(done) {
  return bower();
}

gulp.task('bower:install', bowerInstall);

exports.default = bowerInstall;
