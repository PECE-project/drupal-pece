/**
 * This file should be copied to a 'config-alter.js' file so that
 * Protractor can correctly load this file.
 */

/**
 * Configuration alter method.
 * @param {object} Current Protractor configuration, as defined in
 *                 protractor.confg.js file.
 */
module.exports = function (config) {
  config.baseUrl = 'http://pece.local/';
  config.params.admin.password = 'root';
};
