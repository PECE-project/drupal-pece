module.exports = {
  '@tags': ['a11y'],
  'Accessible login form' (client) {
    client
      .url('http://172.17.191.205:5000/login')
      .waitForElementVisible('body')
      .assert.titleContains('Login')
      .axeInject()
      .axeRun('.pece-container')
      .end()
  }
}
