/// <reference types="Cypress" />
/// <reference types="../support" />

Cypress.on('uncaught:exception', (err, runnable) => {
  //@TODO: Remove event error from panels popup, but i could not get error name to create if.
  return false
})


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

    let title = "Private PECE Essay cy"
    let path = "/content/private-pece-essay-cy"

    it('create a private PECE Essay content ', () => {
      cy.login('editor')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-private:check:private'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test private PECE Essay content</p>")
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

    let title = "Open PECE Essay cy"
    let path = "/content/open-pece-essay-cy"

    it('create an open PECE Essay content ', () => {
      cy.login('editor')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-open:check:open'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test open PECE Essay content</p>")
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
      cy.contains('Save as custom')
      cy.contains('Cancel')
    })

    context('Group permissions', () => {
      let groupName = 'Group Test cy'
      let groupPath = '/content/group-test-cy'
      it('create group', () => {
        cy.login('admin')
        cy.createContent('/node/add/pece-group', [
          'input[name=title]:type:' + groupName
        ], () => {
          cy.addImage('#edit-field-pece-media-image-und-0-upload--widget')
          cy.type_tinyMCE('edit-body-und-0-value', "<p>Test group</p>")
        })
        cy.updateContent(title, [
          '#edit-og-group-ref-und-0-default:select:' + groupName
        ])
      })

      describe('Public group', () => {
        it("anonymous user can access this content with default visibility", () => {
          testAccess(path)
          testAccess(path + '/essay')
        })

        it ("CHANGE GROUP VISIBILITY TO PUBLIC", () => {
          cy.login('admin')
          cy.updateContent(groupName, [
            '#edit-group-content-access-und:select:Public - accessible to all site users'
          ])
        })
        it("anonymous user can access this content with public visibility", () => {
          testAccess(path)
          testAccess(path + '/essay')
        })

        it ("CHANGE GROUP VISIBILITY TO PRIVATE", () => {
          cy.login('admin')
          cy.updateContent(groupName, [
            '#edit-group-content-access-und:select:Private - accessible only to group members'
          ])
        })
        it("anonymous user can't access this content with private visibility", () => {
          testNoAccess(path)
          testNoAccess(path + '/essay')
        })
      })
/*
      describe('Private group', () => {
        it('Visibility default', () => {
          testAccess(path)
        })
        it('Visibility public', () => {
          testAccess(path)
        })
        it('Visibility private', () => {
          testAccess(path)
        })
      })

       */

      describe('Delete contents', () => {
        it('delete an open PECE Essay content', () => {
          cy.login('admin')
          cy.deleteContent(title)
        })
        it('Delete group', () => {
          cy.deleteContent(groupName)
        })
      })
    })

    it('delete an open PECE Essay content', () => {
      cy.login('admin')
      cy.deleteContent(title)
    })
  })

  describe('Test restricted PECE Essay', () => {

    let title = "Restricted PECE Essay cy"
    let path = "/content/restricted-pece-essay-cy"

    it('create a restricted PECE Essay content ', () => {
      cy.login('editor')
      cy.createContent('/node/add/pece-essay', [
        'input[name=title]:type:' + title,
        '#edit-field-pece-contributors-und-0-target-id:type:cy_contributor',
        '#edit-field-permissions-und-restricted:check:restricted'
      ], () => {
        cy.type_tinyMCE('edit-body-und-0-value', "<p>Test restricted PECE Essay content</p>")
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

    it('research user can access this content', () => {
      cy.login('researcher')
      testAccess(path)
      testAccess(path + '/essay')
    })

    it('contributor user can access this content', () => {
      cy.login('contributor')
      testAccess(path)
      testAccess(path + '/essay')
    })

    it('contributor user can access in panels editor', () => {
      cy.login('contributor')
      cy.visit(path + "/essay")
      cy.contains('Customize this page').click()
      cy.contains('Save as custom')
      cy.contains('Cancel')
    })

    it('owner can view and edit this content', () => {
      cy.login('editor')
      testAccess(path)
      testAccess(path + '/essay')
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
