/**
 * This task simply sets up some contextual information, like current
 * running environment's ip address, so that some tasks might not be run
 * on specific conditions, such as inside VM.
 */

var gulp = require('gulp');

gulp.task('context:setup', function (done) {
  // This task must never run on VMs!
  Helpers.ip(function (err, address) {
    if (err) return done(err);
    process.ip = address;
    process.isVM = process.ip !== '127.0.1.1' && process.ip !== '127.0.0.1';
    done();
  });
});
