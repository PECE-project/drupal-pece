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

  let title = "Private text artifact cy"
  let path = "/content/private-text-artifact-cy"

  describe ('Create contents to tests', () => {

    it('create users: researcher, owner, contributor and user',  () => {
      users.forEach((user) => {
        cy.createUser(user.username, user.role)
      })
    })

    it('create a private text artifact content ', () => {
      cy.login('owner')
      cy.createContent('/node/add/pece-artifact-text', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-private:check:private'
      ], () => {
        cy.type_tinyMCE('edit-field-pece-crit-commentary-und-0-value', "<p>This text is very important</p>")
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test private text artifact content</p>")
      })
    })
  })

  describe('Test private text artifact', () => {

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
  })

  describe ('Delete contents after tests', () => {
    it('delete a private text artifact content', () => {
      cy.login('admin')
      cy.deleteContent(title)
    })
    users.forEach((user) => {
      it('delete user: ' + user.username,  () => {
        cy.deleteUser(user.username)
      })
    })
  })
})
