var shell    = require('gulp-shell');
var sequence = require('gulp-sequence');

require('gulp').task('build', ['styles'], function (done) {
  sequence('drush:kw-b', 'update', done);
});
