/**
 * Git related helpers.
 */


var shell = require('shelljs');
var opt = { silent: true };

/**
 * Returns an array containing the currently modified files from last commit.
 */
module.exports.modified = function () {
  var local = this.getBranch();
  var remote = this.getRemoteBranch();
  var command = 'git diff ' + local + ' ' + remote + ' --name-only';
  var stagged = 'git diff --name-only --cached';

  return [
    exec(command),
    exec(stagged)
  ].join('\n').split('\n');
};

/**
 * Returns the name of the current local branch.
 */
module.exports.getBranch = function () {
  return exec('git rev-parse --abbrev-ref HEAD');
};

/**
 * Returns the name of the tracked remote branch from local.
 */
module.exports.getRemoteBranch = function () {
  return exec('git for-each-ref --format="%(upstream:short)" $(git symbolic-ref -q HEAD)');
};

/**
 * Helper method execute commands and parse line breaks on outputs.
 */
function exec(command) {
  return removeEmptyLines((shell.exec(command, opt).output || '')).trim('\n');
}

/**
 * Helper method to remove empty lines from text.
 */
function removeEmptyLines(text) {
  return text.split('\n').filter(Boolean).join('\n');
}

module.exports.modified();
