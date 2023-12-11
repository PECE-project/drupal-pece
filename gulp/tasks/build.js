var gulp = require('gulp');

function build(done) {
  gulp.series('bower:install', 'styles', 'drush:kw-b', done)(done);
}

gulp.task('build', build);

exports.default = build;
