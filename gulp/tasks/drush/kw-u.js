require('shelljs/global');

var gulp = require('gulp');
var yargs = require('yargs');
var minimatch = require('minimatch');
var git = require('../../helpers/git');

var updatePathsPatterns = [
  '**/*.install',
  '**/*.make',
  '**/*.info'
];

gulp.task('drush:kw-u', function () {
  // Parse task arguments, when executed alone.
  var args = yargs.argv._[0] == 'drush:kw-b' ? yargs.alias('f', 'force').argv : {};

  // @TODO: find a way to properly identify when we need to run a build.
  if (true || args.force || matchPattern(git.modified(), updatePathsPatterns)) {
    var cwd = pwd();
    cd(cwd + '/build');
    exec('drush kw-u');
    cd(cwd);
  }
});

/**
 * Helper method to find if a file matches any of an array of patterns.
 */
function matchPattern(files, patterns) {
  patterns = Array.isArray(patterns) ? patterns : [patterns];
  return patterns.some(function (pattern) {
    return files.some(minimatch.filter(pattern));
  });
}
