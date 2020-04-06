module.exports = {
  '@tags': ['action'],
  'Login Test' (client) {
    client
      .login()

    client
      .click('[data-nw="logout"]')
      .waitForElementVisible('#pece-app')

    client
      .expect.element('[data-nw="header-admin"]').to.not.be.present

    client
      .end()
  }
}
