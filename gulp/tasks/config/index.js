var gulp = require('gulp');

var configEnvironment = require('./environment').configEnvironment;
var configSettings = require('./settings').configSettings;

function config(done) {
  gulp.series(configEnvironment, configSettings, done)(done);
};

exports.config = config;
