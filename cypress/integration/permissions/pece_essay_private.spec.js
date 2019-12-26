/// <reference types="Cypress" />
/// <reference types="../support" />

context('Permissions', () => {
  let users = [
    { username:'researcher', role: 'Researcher'},
    { username:'owner', role: 'Researcher'},
    { username:'contributor', role: 'Contributor'},
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

    let title = "Private PECE Essay cy"
    let path = "/content/private-pece-essay-cy"

    it('create a private PECE Essay content ', () => {
      cy.login('owner')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-private:check:private'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test private PECE Essay content</p>")
      })
    })

    it("anonymous user can't access this content", () => {
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('authenticated user can\'t access this content', () => {
      cy.login('user')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('researcher user can\'t access this content', () => {
      cy.login('researcher')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('contributor user can\'t access this content', () => {
      cy.login('contributor')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('owner can view and edit this content', () => {
      cy.login('owner')
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
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
