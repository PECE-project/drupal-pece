var fs = require('fs');
var gulp = require('gulp');
var inquirer = require('inquirer');

var cwd = process.cwd();

var isProduction = process.env.IS_PRODUCTION;

var questions = [{
  'type': 'list',
  'name': 'environment',
  'message': 'Which Kraftwagen environment should we use?',
  'default': 'production',
  'choices': ['production', 'development']
}];

gulp.task('config:environment', function (done) {
  if (isProduction) {
    return fs.writeFile(cwd + '/cnf/environment', 'production', done);
  }
  inquirer.prompt(questions).then(function (answers) {
    // Set Kraftwagen environment.
    if (answers.environment) {
      return fs.writeFile(cwd + '/cnf/environment', answers.environment, done);
    }

    done();
  });
});
