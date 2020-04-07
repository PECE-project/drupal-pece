module.exports = {
  '@tags': ['page'],
  'Forgot password page' (client) {
    client
      .url(`${process.env.NUXT_APP_URL}/login`)
      .click('[data-nw="link-forgot-pass"]')
      .waitForElementVisible('[data-nw="form-forgot-pass"]')

    client
      .assert.visible('[data-nw="btn-submit"]')
      .expect.element('[data-nw="btn-submit"]').to.have.attribute('disabled')

    client
      .assert.visible('[data-nw="email"]')
      .setValue('[data-nw="email"]', client.globals.auth.username)
      .assert.valueContains('[data-nw="email"]', client.globals.auth.username)

    client
      .expect.element('[data-nw="btn-submit"]').to.not.have.attribute('disabled')

    client
      .click('[data-nw="btn-submit"]')

    client
      .waitForElementVisible('[data-nw="alert"]')
      .assert.visible('[data-nw="alert"]')

    client
      .assert.attributeContains('[data-nw="alert"]', 'role', 'alert')
      .assert.attributeContains('[data-nw="alert"]', 'aria-atomic', 'true')

    client
      .expect.element('[data-nw="alert"]').text.to.contain('If the email you specified exists')

    client
      .end()
  }
}
