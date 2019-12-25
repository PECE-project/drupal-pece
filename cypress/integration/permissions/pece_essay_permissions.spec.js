/// <reference types="Cypress" />
/// <reference types="../support" />

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
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
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

  describe('Test open PECE Essay', () => {

    let title = "Open Contributor No Group cy"
    let path = "/content/open-contributor-no-group-cy"

    it('create an open PECE Essay content ', () => {
      cy.login('editor')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-open:check:open'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test open content with no group</p>")
      })
    })

    it("anonymous user can access this content", () => {
      testAccess(path)
      testAccess(path + '/essay')
    })

    it('contributor user can access in panels editor', () => {
      cy.login('contributor')
      cy.visit(path + "/essay")
      cy.contains('Customize this page').click()
      cy.contains('Save')
      cy.contains('Cancel')
      cy.contains('Revert to PECE Essay default')
    })

    it('delete an open PECE Essay content', () => {
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
