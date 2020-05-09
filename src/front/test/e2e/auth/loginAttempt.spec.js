module.exports = {
  '@tags': ['feature'],
  'Login attempt with reCaptcha' (client) {
    client
      .url(`${process.env.NUXT_APP_URL}/login`)
      .waitForElementVisible('[data-nw="form-login"]')

    client
      .assert.visible('[data-nw="btn-submit"]')
      .expect.element('[data-nw="btn-submit"]').to.have.attribute('disabled')

    if (process.env.NUXT_RECAPTCHA_SITE_KEY_V2) {
      client.expect.element('.grecaptcha-badge').to.not.be.visible
      client.expect.element('[data-nw="recaptcha"]').to.not.be.visible
    }

    client
      .assert.visible('[data-nw="email"]')
      .setValue('[data-nw="email"]', client.globals.auth.email)
      .assert.valueContains('[data-nw="email"]', client.globals.auth.email)

    client
      .assert.visible('[data-nw="password"]')
      .setValue('[data-nw="password"]', 'blablabla')
      .assert.valueContains('[data-nw="password"]', 'blablabla')

    client
      .click('[data-nw="btn-submit"]')

    client
      .waitForElementVisible('[data-nw="alert"]')
      .assert.visible('[data-nw="alert"]')

    client
      .assert.attributeContains('[data-nw="alert"]', 'role', 'alert')
      .assert.attributeContains('[data-nw="alert"]', 'aria-atomic', 'true')

    client
      .expect.element('[data-nw="alert"]').text.to.contain('The user credentials were incorrect')

    for (let i = 0; i < 6; i++) {
      client
        .click('[data-nw="btn-submit"]')
        .pause(1000)
    }

    if (process.env.NUXT_RECAPTCHA_SITE_KEY_V2) {
      client
        .waitForElementVisible('[data-nw="recaptcha"]')
        .assert.visible('[data-nw="recaptcha"]')
    }

    client
      .expect.element('[data-nw="alert"]').text.to.contain('Login attempts limit reached, try again later.')

    client
      .end()
  }
}
