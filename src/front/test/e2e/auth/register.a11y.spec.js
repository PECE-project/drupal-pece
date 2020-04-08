module.exports = {
  '@tags': ['a11y'],
  'Accessible register form' (client) {
    client
      .url(`${process.env.NUXT_APP_URL}/register`)
      .waitForElementVisible('[data-nw="form-register"]')
      .assert.titleContains('Create an account')
      .axeInject()
      .axeRun('.pece-container')
      .end()
  }
}
