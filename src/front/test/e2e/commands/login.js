module.exports.command = function () {
  const client = this
  client
    .url(`${process.env.NUXT_APP_URL}/login`)
    .waitForElementVisible('#pece-app')
    .assert.titleContains('Login')

  client
    .expect.element('[data-nw="header-admin"]').to.not.be.present

  client
    .assert.visible('[data-nw="btn-submit"]')
    .expect.element('[data-nw="btn-submit"]').to.have.attribute('disabled')

  client
    .assert.visible('[data-nw="username"]')
    .setValue('[data-nw="username"]', client.globals.auth.username)
    .assert.valueContains('[data-nw="username"]', client.globals.auth.username)

  client
    .assert.visible('[data-nw="password"]')
    .setValue('[data-nw="password"]', client.globals.auth.password)
    .assert.valueContains('[data-nw="password"]', client.globals.auth.password)

  client
    .expect.element('[data-nw="btn-submit"]').to.not.have.attribute('disabled')

  client
    .click('[data-nw="btn-submit"]')

  client
    .waitForElementVisible('[data-nw="header-admin"]')
    .assert.visible('[data-nw="header-admin"]')
}
