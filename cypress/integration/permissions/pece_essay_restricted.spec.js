/// <reference types="Cypress" />
/// <reference types="../support" />

Cypress.on('uncaught:exception', (err, runnable) => {
  //@TODO: Remove event error from panels popup, but i could not get error name to create if.
  return false
})

context('Permissions', () => {
  let users = [
    { username:'researcher', role: 'Researcher'},
    { username:'owner', role: 'Researcher'},
    { username:'contributor', role: 'Contributor'},
    { username:'user', role: null},
    { username:'anonymous', role: null}
  ]

  const title = "Restricted PECE Essay cy"
  const path = "/content/restricted-pece-essay-cy"

  describe ('Create contents to tests', () => {
    it('create users: researcher, owner, contributor and user',  () => {
      cy.login('admin')
      users.forEach((user) => {
        cy.createUser(user.username, user.role)
      })
    })

    it('create a restricted PECE Essay content ', () => {
      cy.login('owner')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-restricted:check:restricted'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test restricted PECE Essay content</p>")
      })
    })
  })

  describe('Test restricted PECE Essay', () => {

    it("anonymous user can't access this content", () => {
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('authenticated user can\'t access this content', () => {
      cy.login('user')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('researcher user can access this content', () => {
      cy.login('researcher')
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
    })

    it('contributor user can access this content', () => {
      cy.login('contributor')
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
    })

    it('contributor user can access in panels editor', () => {
      cy.login('contributor')
      cy.visit(path + "/essay")
      cy.contains('Customize this page').click()
      cy.contains('Save as custom')
      cy.contains('Cancel')
    })

    it('owner can view and edit this content', () => {
      cy.login('owner')
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
    })
  })

  describe ('Delete contents after tests', () => {

    users.forEach((user) => {
      it('delete user: ' + user.username,  () => {
        cy.deleteUser(user.username)
      })
    })
  })
})
