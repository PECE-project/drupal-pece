function testNoAccess(url) {
  cy.request({
    url: url,
    failOnStatusCode: false // turn off following redirects
  })
    .then((resp) => {
      // redirect status code is 302
      expect(resp.status).to.eq(403)
    })
}

function testAccess(url) {
  cy.request({
    url: url
  })
    .then((resp) => {
      // redirect status code is 302
      expect(resp.status).to.eq(200)
    })
}

context('Permissions', () => {
  let users = [
    { username:'researcher', role: 'Researcher'},
    { username:'contributor', role: 'Contributor'},
    { username:'editor', role: 'editor'},
    { username:'user', role: null},
    { username:'anonymous', role: null}
  ]

  describe ('Create users to tests', () => {
    users.forEach((user) => {
      it('create user: ' + user.username,  () => {
        cy.createUser(user.username, user.role)
      })
    })
  })

  describe('Test private PECE Essay', () => {

    let title = "Private Contributor No Group cy"
    let path = "/content/private-contributor-no-group-cy"

    it('create a private PECE Essay content ', () => {
      cy.login('editor')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:contributor',
        '#edit-field-permissions-und-private:check:private'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test private content with no group</p>")
      })
    })

    it("anonymous user can't access this content", () => {
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it('authenticated user can\'t access this content', () => {
      cy.login('user')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it('research user can\'t access this content', () => {
      cy.login('researcher')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it('contributor user can\'t access this content', () => {
      cy.login('contributor')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it('owner can view and edit this content', () => {
      cy.login('editor')
      testAccess(path)
      testAccess(path + '/essay')
    })

    it('delete a private PECE Essay content', () => {
      cy.login('admin')
      cy.deleteContent(title)
    })
  })

  describe ('Delete users after tests', () => {
    users.forEach((user) => {
      it('delete user: ' + user.username,  () => {
        cy.deleteUser(user.username)
      })
    })
  })
})
