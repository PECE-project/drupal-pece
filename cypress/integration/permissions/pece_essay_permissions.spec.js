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
    { username:'user', role: null}
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

    it ("anonymous user can't access this content", () => {
      testNoAccess(path)
      testNoAccess( path + '/essay')
    })

    it ('authenticated user can\'t access this content', () => {
      cy.login('user')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it ('research user can\'t access this content', () => {
      cy.login('researcher')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it ('contributor user can\'t access this content', () => {
      cy.login('contributor')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it ('owner can view and edit this content', () => {
      cy.login('editor')
      testAccess(path)
      testAccess(path + '/essay')
    })

    it('delete a private PECE Essay content',  () => {
      cy.login('admin')
      cy.deleteContent(title)
    })


    //
    // it('create a restricted PECE Essay content ', () => {
    //   adminLogin()
    //   cy.visit('/node/add/pece-essay')
    //   cy.get('input[name=title]').type('Restricted Contributor No Group')
    //   cy.get('#edit-field-pece-contributors-und-0-target-id').type('admin')
    //   cy.window()
    //     .then(win => {
    //       win.tinyMCE.get('edit-body-und-0-value').setContent("<p>Test restricted content with no group</p>");
    //     });
    //   cy.get('#edit-field-permissions-und-private').check('restricted')
    //   cy.get("#edit-submit").click()
    // })
    // //
    // it('create an open PECE Essay content ', () => {
    //   adminLogin()
    //   cy.visit('/node/add/pece-essay')
    //   cy.get('input[name=title]').type('Open Contributor No Group')
    //   cy.get('#edit-field-pece-contributors-und-0-target-id').type('admin')
    //   cy.window()
    //     .then(win => {
    //       win.tinyMCE.get('edit-body-und-0-value').setContent("<p>Test open content with no group</p>");
    //     });
    //   cy.get('#edit-field-permissions-und-private').check('open')
    //   cy.get("#edit-submit").click()
    // })
  })

  // describe('Test open PECE Essay', () => {
  //
  //   let title = "Public Contributor No Group"
  //   let path = "/content/open-contributor-no-group-cy"
  //
  //   it('create a Open PECE Essay content ', () => {
  //     login('admin')
  //     cy.visit('/node/add/pece-essay')
  //     cy.get('input[name=title]').type(title)
  //
  //     cy.get('#edit-path-alias').type(path.substr(1))
  //     cy.get('#edit-name').clear().type('editor')
  //     cy.get('#edit-field-pece-contributors-und-0-target-id').type('contributor')
  //     cy.window()
  //       .then(win => {
  //         win.tinyMCE.get('edit-body-und-0-value').setContent("<p>Test open content with no group</p>");
  //       });
  //     cy.get('#edit-field-permissions-und-private').check('open')
  //     cy.get("#edit-submit").click()
  //     cy.contains(`has been created.`)
  //   })
  //
  //   it ("anonymous user can't access this content", () => {
  //     testNoAccess(path)
  //     testNoAccess( path + '/essay')
  //   })
  //
  //   it ('authenticated user can\'t access this content', () => {
  //     login('user')
  //     testNoAccess(path)
  //     testNoAccess(path + '/essay')
  //   })
  //
  //   it ('research user can\'t access this content', () => {
  //     login('researcher')
  //     testNoAccess(path)
  //     testNoAccess(path + '/essay')
  //   })
  //
  //   it ('contributor user can\'t access this content', () => {
  //     login('contributor')
  //     testNoAccess(path)
  //     testNoAccess(path + '/essay')
  //   })
  //
  //   it ('owner can view and edit this content', () => {
  //     login('editor')
  //     testAccess(path)
  //     testAccess(path + '/essay')
  //   })
  //
  //   it('delete a private PECE Essay content',  () => {
  //     login('admin')
  //     deleteContent(title)
  //   })
  //
  //
  //   //
  //   // it('create a restricted PECE Essay content ', () => {
  //   //   adminLogin()
  //   //   cy.visit('/node/add/pece-essay')
  //   //   cy.get('input[name=title]').type('Restricted Contributor No Group')
  //   //   cy.get('#edit-field-pece-contributors-und-0-target-id').type('admin')
  //   //   cy.window()
  //   //     .then(win => {
  //   //       win.tinyMCE.get('edit-body-und-0-value').setContent("<p>Test restricted content with no group</p>");
  //   //     });
  //   //   cy.get('#edit-field-permissions-und-private').check('restricted')
  //   //   cy.get("#edit-submit").click()
  //   // })
  //   // //
  //   // it('create an open PECE Essay content ', () => {
  //   //   adminLogin()
  //   //   cy.visit('/node/add/pece-essay')
  //   //   cy.get('input[name=title]').type('Open Contributor No Group')
  //   //   cy.get('#edit-field-pece-contributors-und-0-target-id').type('admin')
  //   //   cy.window()
  //   //     .then(win => {
  //   //       win.tinyMCE.get('edit-body-und-0-value').setContent("<p>Test open content with no group</p>");
  //   //     });
  //   //   cy.get('#edit-field-permissions-und-private').check('open')
  //   //   cy.get("#edit-submit").click()
  //   // })
  // })

  describe ('Delete users after tests', () => {
    users.forEach((user) => {
      it('delete user: ' + user.username,  () => {
        cy.deleteUser(user.username)
      })
    })
  })
})

