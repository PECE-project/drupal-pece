/**
 * This file will export all pages existing in the project. For each
 * file in the 'pages' directory, it will grab the name and set a
 * camel-cased property in the final exported object. For instance,
 * if there is a page object file named 'sample.page.js', the exported
 * object from this current file will contain a property called
 * 'SamplePage' which will therefore point to the exported value of
 * that page object file.
 *
 * @WARNING: many of the page objects might use variables that are only
 * made available globally after Protractor initiates.
 */

var pages = require('require-dir')('./');

Object.keys(pages).forEach(function (filename) {
  module.exports[filename.split('.').map(function (filenamePart) {
    return filenamePart[0].toUpperCase() + filenamePart.substr(1);
  }).join('')] = pages[filename];
});
