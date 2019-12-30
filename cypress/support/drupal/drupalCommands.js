//@TODO update this commands to use drush
//@TODO Integrate this commands with content_devel module to generate data

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

  cy.drupalDrushCommand([
    'user-create',
    'cy_' + name,
    '--mail="' + name + '@example.com"',
    '--password="'+ password+'"',
  ])

  if(role)
    cy.drupalDrushCommand(['urol', role, 'cy_' + name])
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

  cy.drupalDrushCommand(['ucan', '--delete-content', 'cy_'+ name, '-y'])
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

Cypress.Commands.add("drupalDrushCommand", (command) => {
  var cmd = Cypress.env('drupalDrushCmdLine');

  if (cmd == null) {
    cmd = 'drush %command'
  }

  if( typeof command === 'string' ) {
    command = [ command ];
  }

  const execCmd = cmd.replace('%command', command.join(' '));

  return cy.exec(execCmd);
});
