Cypress.Commands.add("type_tinyMCE", (element, content) => {
  cy.window()
    .then(win => {
      win.tinyMCE.get(element).setContent(content);
    });
});

Cypress.Commands.add('createUser', (name, role = null,password = '123456789') => {
  if(name == 'anonymous')
    return

  cy.login('admin')
  cy.visit('/admin/people/create')
  cy.get('#edit-name').type('cy_' + name)
  cy.get('#edit-mail').type(name + '@' + 'test.com')
  cy.get('#edit-pass-pass1').type(password)
  cy.get('#edit-pass-pass2').type(password)

  if(role)
    cy.get('.form-item-roles').contains(role).prev('input').click()
  cy.get("#edit-submit").click()
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
  cy.visit('/user/login')
  cy.get('input[name=name]').type(user)
  cy.get('input[name=pass]').type(password + `{enter}`)
  cy.contains("Log out")
})

/**
 *
 * @param path URL to form
 * @param fields []
 */
Cypress.Commands.add('createContent', (path, fields, beforeSave) => {
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
  cy.contains('PECE Essay ' + title + ' has been deleted.')
})

