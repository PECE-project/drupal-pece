function createUser(name, role = null,password = '123456789') {
  login('admin')
  cy.visit('/admin/people/create')
  cy.get('#edit-name').type(name)
  cy.get('#edit-mail').type(name + '@' + 'test.com')
  cy.get('#edit-pass-pass1').type(password)
  cy.get('#edit-pass-pass2').type(password)

  if(role)
    cy.get('.form-item-roles').contains(role).prev('input').click()
  cy.get("#edit-submit").click()
}

function deleteUser(name) {
  login('admin')
  cy.visit('/admin/people')
  cy.contains(name).parent().parent().contains('Cancel account').click()
  cy.contains('Delete the account and its content.').prev('input').click()
  cy.get('#edit-submit').click()
}

function login(user, password = '123456789') {
  cy.visit('/user/login')
  cy.get('input[name=name]').type(user)
  cy.get('input[name=pass]').type(password + `{enter}`)
}

function deleteContent(title) {
  cy.visit('/admin/content')
  cy.contains(title).parent().parent().contains('delete').click()
  cy.get('[value="Delete"]').click()
  cy.contains('PECE Essay ' + title + ' has been deleted.')
}

function testNoAccess(url) {
  cy.visit(url).contains('Access denied')
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
    { username:'owner', role: null},
    { username:'user', role: null}
  ]

  // describe ('Create users to tests', () => {
  //   users.forEach((user) => {
  //     it('create user: ' + user.username,  () => {
  //       createUser(user.username, user.role)
  //     })
  //   })
  // })

  describe('Test private PECE Essay', () => {

    let title = "Private Contributor No Group"
    let path = "/content/private-contributor-no-group-cy"

    it('create a private PECE Essay content ', () => {
      login('admin')
      cy.visit('/node/add/pece-essay')
      cy.get('input[name=title]').type(title)

      cy.get('#edit-path-alias').type(path.substr(1))
      cy.get('#edit-name').clear().type('owner')
      cy.get('#edit-field-pece-contributors-und-0-target-id').type('contributor')
      cy.window()
        .then(win => {
          win.tinyMCE.get('edit-body-und-0-value').setContent("<p>Test private content with no group</p>");
        });
      cy.get('#edit-field-permissions-und-private').check('private')
      cy.get("#edit-submit").click()
      cy.contains(`has been created.`)
    })

    it ("anonymous user can't access this content", () => {
      testNoAccess(path)
      testNoAccess( path + '/essay')
    })

    it ('authenticated user can\'t access this content', () => {
      login('user')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it ('research user can\'t access this content', () => {
      login('research')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it ('contributor user can\'t access this content', () => {
      login('contributor')
      testNoAccess(path)
      testNoAccess(path + '/essay')
    })

    it ('owner can view and edit this content', () => {
      login('owner')
      testAccess(path)
      testAccess(path + '/essay')
    })

    it('delete a private PECE Essay content',  () => {
      login('admin')
      deleteContent(title)
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

  // describe ('Delete users after tests', () => {
  //   users.forEach((user) => {
  //     it('delete user: ' + user.username,  () => {
  //       deleteUser(user.username)
  //     })
  //   })
  // })
})

