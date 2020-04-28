module.exports = {
  '@tags': ['feature'],
  'Login attempt with reCaptcha' (client) {
    client
      .url(`${process.env.NUXT_APP_URL}/login`)
      .waitForElementVisible('[data-nw="form-login"]')

    client
      .assert.visible('[data-nw="btn-submit"]')
      .expect.element('[data-nw="btn-submit"]').to.have.attribute('disabled')

    client.expect.element('.grecaptcha-badge').to.not.be.visible
    client.expect.element('[data-nw="recaptcha"]').to.not.be.visible

    client
      .assert.visible('[data-nw="username"]')
      .setValue('[data-nw="username"]', client.globals.auth.username)
      .assert.valueContains('[data-nw="username"]', client.globals.auth.username)

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
        .wait(1000)
    }

    client
      .waitForElementVisible('[data-nw="recaptcha"]')
      .assert.visible('[data-nw="recaptcha"]')

    client
      .expect.element('[data-nw="alert"]').text.to.contain('Login attempts limit reached, try again later.')

    client
      .end()
  }
}
