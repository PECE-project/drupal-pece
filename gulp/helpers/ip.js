
var dns = require('dns');
var os = require('os');

/**
 * Retrive IP address.
 */
module.exports = function ip(callback) {
  dns.lookup(os.hostname(), callback);
};
