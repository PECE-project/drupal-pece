/**
 * @file
 * Exposes utility methods for the Gulp tasks.
 */

var net = require('net');

/**
 * Helper method to find if a given port is in use.
 * @param {Number} port The port to check for availability.
 * @param {Function} callback The callback to call with result.
 */
module.exports.isPortTaken = function (port, callback) {
  var finish = callback.bind(null, null, false);
  var tester = net.createServer();

  tester
    .once('error', onError)
    .once('listening', onSuccess)
    .listen(port);

  /**
   * Handles server creation error.
   */
  function onError(err) {
    callback.apply(null, err.code === 'EADDRINUSE' ? [null, true] : [err, null]);
  }

  /**
   * Handles listening success.
   */
  function onSuccess() {
    tester.once('close', finish).close();
  }
};
