describe('@pages/Home', () => {
  before(() => {
    cy.visit(`/`)
  })

  it('Title be visible and contain text', () => {
    cy.get('h1')
      .should('be.visible')
      .contains('V2 PECE')
  })

  it('Render the logo', () => {
    cy.get('[data-pece="logo"]')
      .should('be.visible')
  })
})
