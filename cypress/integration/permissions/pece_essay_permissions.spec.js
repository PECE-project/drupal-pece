describe('Test private, restricted and open PECE Essay', function() {
  function adminLogin () {
    cy.visit('/user/login')
    cy.get('input[name=name]').type('admin')
    cy.get('input[name=pass]').type(`123456789{enter}`)
  }

  it('create contents to test', function() {
    adminLogin()
    cy.visit('/node/add/pece-photo-essay')
    cy.get('input[name=title]').type('Private Contribuitor No Group')
    cy.get('#edit-field-pece-contributors-und-0-target-id').type('admin')
    cy.window()
      .then(win => {
        win.tinyMCE.get('edit-field-pece-photo-essay-items-und-form-field-description-und-0-value').setContent("<p>Test private content with no group</p>");
      });
    cy.get('#edit-field-permissions-und-private').check('private')
  })
})
