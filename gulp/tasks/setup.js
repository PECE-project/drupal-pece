var gulp = require('gulp');
var shell = require('shelljs');
var prompt = require('gulp-prompt');

// Import external tasks.
var drushKw_s = require('./drush/kw-s.js').drushKw_s;
var config = require('./config/index.js').config;

function setup(done) {
  gulp.series(drushKw_s, config)(done);
}

exports.setup = setup;
