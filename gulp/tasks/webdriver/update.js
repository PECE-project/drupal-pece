
var gulp = require('gulp');
var spawn = require('child_process').spawn;
var webdriverPath = process.cwd() + '/node_modules/.bin/webdriver-manager';

gulp.task('webdriver:update', ['context:setup'], function (done) {
  // This task's content must never run inside a VM environment.
  if (process.isVM) return done();

  spawn(webdriverPath, ['update'], {
    stdio: 'inherit'
  }).once('close', done);
});
