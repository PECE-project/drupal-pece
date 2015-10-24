/**
 * When required, this file will make available all page object
 * helpers as defined in the 'pages/index.js' file.
 */

var pages = require('./index');

Object.keys(pages).forEach(function (pageName) {
  if (typeof GLOBAL[pageName] !== 'undefined') {
    throw '"' + pageName + '" was already defined in the Global scope.';
  }

  GLOBAL[pageName] = pages[pageName];
});
