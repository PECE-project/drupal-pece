//@TODO update this commands to use drush:
// Ref: https://sevaa.com/blog/2018/10/end-to-end-testing-with-drupal-and-cypress/
// Ref: https://www.npmjs.com/package/cypress-drupal

Cypress.Commands.add("type_tinyMCE", (element, content) => {
  cy.window()
    .then(win => {
      win.tinyMCE.get(element).setContent(content);
    });
});

Cypress.Commands.add('addImage', (element, image = 'sf.jpg') => {
  cy.get(element).contains('Browse').click()
  cy.wait(3000)
  cy.get('iframe[id="mediaBrowser"]').then($iframe => {
    const body = $iframe.contents().find('body');
    cy.wrap(body.find('#ui-id-2')).click()
    cy.wrap(body.find('.view-id-media_default')).contains(image).click()
    cy.wrap(body.find('.fake-submit')).click()
  })
})

Cypress.Commands.add('createUser', (name, role = null,password = '123456789') => {
  if(name == 'anonymous')
    return

  cy.visit('/admin/people/create')
  cy.get('#edit-name').type('cy_' + name)
  cy.get('#edit-mail').type(name + '@' + 'test.com')
  cy.get('#edit-pass-pass1').type(password)
  cy.get('#edit-pass-pass2').type(password)

  if(role)
    cy.get('.form-item-roles').contains(role).prev('input').click()
  cy.get("#edit-submit").click()
})

Cypress.Commands.add('updateUser', (username, fields, beforeSave  = null) => {
  cy.visit('/users/cy' + username.replace('_','') + '/edit')

  /** @var String data **/
  fields.forEach((data) => {
    let [selectorField, func, dataValue] = data.split(':')
    cy.get(selectorField)[func](dataValue)
  })
  if (beforeSave) {
    beforeSave()
  }
  cy.get("#edit-submit").click()
  cy.contains('The changes have been saved.')
})

Cypress.Commands.add('deleteUser', (name) => {
  if(name == 'anonymous')
    return
  cy.login('admin')
  cy.visit('/admin/people')
  cy.get('.views-table a').contains('cy_' + name).parent().parent().contains('Cancel account').click()
  cy.contains('Delete the account and its content.').prev('input').click()
  cy.get('#edit-submit').click()
})

Cypress.Commands.add('login', (user, password = '123456789') => {
  if(name == 'anonymous')
    return
  user = user == 'admin' ? user : 'cy_' + user

  cy.request({
    method: 'POST',
    url: '/user/login', // baseUrl is prepended to url
    form: true, // indicates the body should be form urlencoded and sets Content-Type: application/x-www-form-urlencoded headers
    body: {
      name: user,
      pass: password,
      form_id: 'user_login'
    }
  })
})

/**
 *
 * @param path URL to form
 * @param fields []
 */
Cypress.Commands.add('createContent', (path, fields, beforeSave = null) => {
  cy.visit(path)
  /** @var String data **/
  fields.forEach((data) => {
    let [selectorField, func, dataValue] = data.split(':')
    cy.get(selectorField)[func](dataValue)
  })
  if (beforeSave) {
    beforeSave()
  }
  cy.get("#edit-submit").click()
  cy.contains(`has been created.`)
})

Cypress.Commands.add('deleteContent', (title) => {
  cy.visit('/admin/content')
  cy.contains(title).parent().parent().contains('delete').click()
  cy.get('[value="Delete"]').click()
  cy.contains( title + ' has been deleted.')
})

Cypress.Commands.add('updateContent', (title, fields, beforeSave  = null) => {
  cy.visit('/admin/content')
  cy.contains(title).parent().parent().contains('.views-field-edit-node','edit').contains('edit').click()

  /** @var String data **/
  fields.forEach((data) => {
    let [selectorField, func, dataValue] = data.split(':')
    cy.get(selectorField)[func](dataValue)
  })
  if (beforeSave) {
    beforeSave()
  }
  cy.get("#edit-submit").click()
  cy.contains(title + ' has been updated.')
})

