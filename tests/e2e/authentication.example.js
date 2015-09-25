/**
 * @file authentication.js
 */

/**
 * Define user credentials
 */
var userInfo = {
    user: 'admin',
    password: 'impossiblepassword'
};

function getInfo(info) {
    return userInfo[info];
}

module.exports = {
    // Expose functions
    getInfo: getInfo,

    // Expose static attribues.
    userInfo: userInfo
};
