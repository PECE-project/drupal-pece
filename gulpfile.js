/**
 * @file Main gulp file.
 */

var gulp = require('gulp')
  , requireDir = require('require-dir');

// Load all tasks.
requireDir('./gulp', {
  recurse: true
});

// Register default.
// gulp.task('default', ['build']);
