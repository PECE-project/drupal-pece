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

  const title = "Open PECE Essay cy"
  const path = "/content/open-pece-essay-cy"
  const publicGroup = 'Public Group Test cy'
  const privateGroup = 'Private Group Test cy'

  describe ('Create contents to tests', () => {

    it('create users: researcher, owner, contributor and user',  () => {
      users.forEach((user) => {
        cy.createUser(user.username, user.role)
      })
    })

    it('create an open PECE Essay content', () => {
      cy.login('owner')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-open:check:open'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test open PECE Essay content</p>")
      })
    })

    it('create public group', () => {
      cy.login('admin')
      cy.createContent('/node/add/pece-group', [
        'input[name=title]:type:' + publicGroup
      ], () => {
        cy.addImage('#edit-field-pece-media-image-und-0-upload--widget')
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test group</p>")
      })
    })

    it('create private group', () => {
      cy.login('admin')
      cy.createContent('/node/add/pece-group', [
        'input[name=title]:type:' + privateGroup,
        '#edit-group-access-und-1:check:1'
      ], () => {
        cy.addImage('#edit-field-pece-media-image-und-0-upload--widget')
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test group</p>")
      })
    })
  })

  describe('Test open PECE Essay', () => {

    it("anonymous user can access this content", () => {
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

  })

  describe('Default Visibility', () => {
    it ('group with default visibility', () => {
      cy.login('admin')
      cy.updateContent(title, [
        '#edit-og-group-ref-und-0-default:select:' + privateGroup
      ])
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

    it("researcher user can't access this content", () => {
      cy.login('researcher')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it ('add user in the content group', () => {
      cy.login('admin')
      cy.updateUser('user', [
        '#edit-og-user-node-und-0-default:select:' + privateGroup
      ])
    })

    it("user in group content can access this content", () => {
      cy.login('user')
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
    })

  })
  describe('Public Visibility', () => {
    it("change group visibility TO PUBLIC", () => {
      cy.login('admin')
      cy.updateContent(privateGroup, [
        '#edit-group-content-access-und:select:Public - accessible to all site users'
      ])
    })
    it("anonymous user can access this content", () => {
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
    })
  })

  describe('Private Visibility', () => {
    it ("change group visibility TO PRIVATE", () => {
      cy.login('admin')
      cy.updateContent(privateGroup, [
        '#edit-group-content-access-und:select:Private - accessible only to group members'
      ])
    })
    it("anonymous user can't access this content", () => {
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it('researcher user can\'t access this content', () => {
      cy.login('researcher')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
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

    it("researcher user can't access this content", () => {
      cy.login('researcher')
      cy.testNoAccess(path)
      cy.testNoAccess(path + '/essay')
    })

    it ('add researcher in the content group', () => {
      cy.login('admin')
      cy.updateUser('researcher', [
        '#edit-og-user-node-und-0-default:select:' + privateGroup
      ])
    })

    it("researcher user in group user can access this content", () => {
      cy.login('researcher')
      cy.testAccess(path)
      cy.testAccess(path + '/essay')
    })

    //@TODO: Need test to add two groups, one public and visibility public other private and permission need keep public
  })

  describe ('Delete contents', () => {
    it('delete content and group', () => {
      cy.login('admin')
      cy.deleteContent(title)
      cy.deleteContent(publicGroup)
      cy.deleteContent(privateGroup)
    })
    users.forEach((user) => {
      it('delete user: ' + user.username,  () => {
        cy.deleteUser(user.username)
      })
    })
  })

})
