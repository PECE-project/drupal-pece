require('shelljs/global');

var gulp = require('gulp');
var shell = require('gulp-shell');
var yargs = require('yargs');
var minimatch = require('minimatch');
var git = require('../../helpers/git');

gulp.task('drush:kw-b', function () {
  // Parse task arguments, when executed alone.
  var args = yargs.argv._[0] == 'drush:kw-b' ? yargs.alias('f', 'force').argv : {};

  // @TODO: find a way to properly identify when we need to run a build.
  if (true || args.force || git.modified().some(minimatch.filter('**/*.make'))) {
    exec('drush kw-b');
  }
});
