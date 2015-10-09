
var gulp = require('gulp');
var spawn = require('child_process').spawn;
var webdriverPath = process.cwd() + '/node_modules/.bin/webdriver-manager';

gulp.task('webdriver:update', function (done) {
  spawn(webdriverPath, ['update'], {
    stdio: 'inherit'
  }).once('close', done);
});
