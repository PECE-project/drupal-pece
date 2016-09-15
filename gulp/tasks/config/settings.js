var fs = require('fs');
var gulp = require('gulp');
var slug = require('slug');
var inquirer = require('inquirer');
var rename = require('gulp-rename');
var replace = require('gulp-replace');

var cwd = process.cwd();
var isProduction = process.env.IS_PRODUCTION;

var info = [
  { 'name' : 'name',     'placeholder': '%SETTINGS_DATABASE_NAME%',     'default': process.env.DB_NAME     || 'pece'      },
  { 'name' : 'username', 'placeholder': '%SETTINGS_DATABASE_USERNAME%', 'default': process.env.DB_USERNAME || 'pece'      },
  { 'name' : 'password', 'placeholder': '%SETTINGS_DATABASE_PASSWORD%', 'default': process.env.DB_PASSWORD || ''          },
  { 'name' : 'host',     'placeholder': '%SETTINGS_DATABASE_HOST%',     'default': process.env.DB_HOST     || 'localhost' },
  { 'name' : 'port',     'placeholder': '%SETTINGS_DATABASE_PORT%',     'default': process.env.DB_PORT     || ''          },
  { 'name' : 'driver',   'placeholder': '%SETTINGS_DATABASE_DRIVER%',   'default': process.env.DB_DRIVER   || 'mysql'     },
  { 'name' : 'prefix',   'placeholder': '%SETTINGS_DATABASE_PREFIX%',   'default': '' }
];

var questions = info.map(function (info) {
  info.type = 'input';
  info.message = 'Database ' + info.name + ':';
  info.filter = filter;
  info.validate = validation;
  return info;
});

gulp.task('config:settings', function () {
  if (isProduction) {
    return gulp.src('src/cnf/settings.local.base.php')
      .pipe(replace('%SETTINGS_DATABASE_NAME%', process.env.DB_NAME))
      .pipe(replace('%SETTINGS_DATABASE_USERNAME%', process.env.DB_USERNAME))
      .pipe(replace('%SETTINGS_DATABASE_PASSWORD%', process.env.DB_PASSWORD))
      .pipe(replace('%SETTINGS_DATABASE_HOST%', process.env.DB_HOST))
      .pipe(replace('%SETTINGS_DATABASE_PORT%', process.env.DB_PORT))
      .pipe(replace('%SETTINGS_DATABASE_DRIVER%', process.env.DB_DRIVER))
      .pipe(replace('%SETTINGS_DATABASE_PREFIX%', ''))
      .pipe(rename('settings.local.php'))
      .pipe(gulp.dest('cnf'));
  }
  return inquirer.prompt(questions).then(function (answers) {
    return gulp.src('src/cnf/settings.local.base.php')
      .pipe(replace('%SETTINGS_DATABASE_NAME%', answers.name))
      .pipe(replace('%SETTINGS_DATABASE_USERNAME%', answers.username))
      .pipe(replace('%SETTINGS_DATABASE_PASSWORD%', answers.password))
      .pipe(replace('%SETTINGS_DATABASE_HOST%', answers.host))
      .pipe(replace('%SETTINGS_DATABASE_PORT%', answers.port))
      .pipe(replace('%SETTINGS_DATABASE_DRIVER%', answers.driver))
      .pipe(replace('%SETTINGS_DATABASE_PREFIX%', answers.prefix))
      .pipe(rename('settings.local.php'))
      .pipe(gulp.dest('cnf'));
  });
});

var validateMap = {
  'empty': ['name', 'username', 'host', 'driver'],
  'slug': ['name', 'username', 'port', 'driver', 'prefix']
};

/**
 * Simple trimming filter.
 */
function filter(value) {
  return (value || '').trim();
}

/**
 * Simple validation for the database config.
 */
function validation(value) {
  // Required values.
  if (validateMap['empty'].indexOf(info.name) > -1 && !value) {
    return info.name + ' is required';
  }

  // Only valid chars.
  if (validateMap['slug'].indexOf(info.name) > -1 && value !== slug(value)) {
    return info.name + ' cannot have invalid characters';
  }

  return true
}
