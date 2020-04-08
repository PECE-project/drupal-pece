module.exports.command = function (dataRegister) {
  const client = this

  client
    .url(`${process.env.NUXT_APP_URL}/register`)
    .waitForElementVisible('[data-nw="form-register"]')
    .assert.titleContains('Create an account')

  client
    .assert.visible('[data-nw="btn-submit"]')
    .expect.element('[data-nw="btn-submit"]').to.have.attribute('disabled')

  client
    .assert.visible('[data-nw="username"]')
    .setValue('[data-nw="username"]', dataRegister.username)
    .assert.valueContains('[data-nw="username"]', dataRegister.username)

  client
    .assert.visible('[data-nw="email"]')
    .setValue('[data-nw="email"]', dataRegister.email)
    .assert.valueContains('[data-nw="email"]', dataRegister.email)

  client
    .assert.visible('[data-nw="password"]')
    .setValue('[data-nw="password"]', dataRegister.password)
    .assert.valueContains('[data-nw="password"]', dataRegister.password)

  client
    .assert.visible('[data-nw="password_confirm"]')
    .setValue('[data-nw="password_confirm"]', dataRegister.password)
    .assert.valueContains('[data-nw="password_confirm"]', dataRegister.password)

  client
    .assert.visible('[data-nw="zotero"]')
    .setValue('[data-nw="zotero"]', dataRegister.zotero)
    .assert.valueContains('[data-nw="zotero"]', dataRegister.zotero)

  client
    .expect.element('[data-nw="btn-submit"]').to.not.have.attribute('disabled')

  client
    .click('[data-nw="btn-submit"]')
}
