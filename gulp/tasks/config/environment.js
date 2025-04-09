var fs = require('fs');
var gulp = require('gulp');

//
var inquirer;

var cwd = process.cwd();

var isProduction = process.env.IS_PRODUCTION;

var questions = [{
  'type': 'list',
  'name': 'environment',
  'message': 'Which Kraftwagen environment should we use?',
  'default': 'production',
  'choices': ['production', 'development']
}];

async function configEnvironment(done) {
  if (!inquirer) {
    inquirer = (await import('inquirer').default);
  }
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
}

exports.configEnvironment = configEnvironment;
