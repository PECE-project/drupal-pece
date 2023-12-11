var fs = require('fs');
var gulp = require('gulp');
var shell = require('shelljs');
var util = require('../../lib/util');

var cwd = process.cwd(), command = '', env, environmentMakePath;
var profilePath = cwd + '/build/profiles/pece';

function drushKw_b(done) {
  shell.exec('drush kw-b');

  getEnvironmentMakePath(function (err, makeFile) {
    if (!err) {
      command += 'drush make';
      command += ' ' + makeFile;
      command += ' --no-core';
      command += ' --contrib-destination ' + profilePath;
      command += ' -y';

      console.log(command)

      shell.cd(cwd + '/build');
      shell.exec(command);
      shell.cd(cwd);
    }

    done();
  });
}

gulp.task('drush:kw-b', drushKw_b);

/**
 * Helper method to retrieve an environment make path.
 */
function getEnvironmentMakePath(callback) {
  util.environment(function (err, env) {
    environmentMakePath = profilePath + '/pece.' + (env || 'production') + '.make';

    fs.stat(environmentMakePath, function(err, stat) {
      callback.apply(null, err ? [err, null] : [null, environmentMakePath]);
    });
  });
}

exports.default = drushKw_b;
