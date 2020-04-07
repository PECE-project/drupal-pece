module.exports = {
  '@tags': ['a11y'],
  'Accessible Forgot pass form' (client) {
    client
      .url(`${process.env.NUXT_APP_URL}/forgot-password`)
      .waitForElementVisible('#pece-app')
      .assert.titleContains('Forgot password')
      .axeInject()
      .axeRun('.pece-container')
      .end()
  }
}
