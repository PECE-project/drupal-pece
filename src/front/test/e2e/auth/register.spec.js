const utils = require('../utils/faker')

const dataRegister = utils.generateDataRegister()

module.exports = {
  '@tags': ['page'],
  'register page' (client) {
    client
      .register(dataRegister)

    client
      .waitForElementVisible('.swal-modal')
      .assert.visible('.swal-modal')
      .assert.containsText('.swal-title', 'Registration successfully Complete!')

    client
      .pause(2000)
      .waitForElementVisible('[data-nw="header-admin"]')
      .assert.visible('[data-nw="header-admin"]')

    client
      .end()
  },

  'Testing the registration page with the existing user' (client) {
    client
      .register(dataRegister)

    client
      .waitForElementVisible('[data-nw="error-alert"]')
      .assert.visible('[data-nw="error-alert"]')
      .assert.visible('[data-nw="error-alert-list"] > li')
      .assert.containsText('[data-nw="error-alert-list"] > li:first-child', 'User already registered')

    client
      .end()
  }
}
