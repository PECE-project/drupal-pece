module.exports = {
  '@tags': ['a11y'],
  'Accessible login form' (client) {
    client
      .url(`${process.env.NUXT_APP_URL}/login`)
      .waitForElementVisible('body')
      .assert.titleContains('Login')
      .axeInject()
      .axeRun('.pece-container')
      .end()
  }
}
