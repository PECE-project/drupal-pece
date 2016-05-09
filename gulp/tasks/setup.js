var gulp = require('gulp');
var sequence = require('gulp-sequence');
var shell = require('shelljs');
var prompt = require('gulp-prompt');

gulp.task('setup', function (done) {
  sequence('drush:kw-s', 'config', done);
});
