// ***********************************************
// This example commands.js shows you how to
// create various custom commands and overwrite
// existing commands.
//
// For more comprehensive examples of custom
// commands please read more here:
// https://on.cypress.io/custom-commands
// ***********************************************
//
//
// -- This is a parent command --
// Cypress.Commands.add("login", (email, password) => { ... })
//
//
// -- This is a child command --
// Cypress.Commands.add("drag", { prevSubject: 'element'}, (subject, options) => { ... })
//
//
// -- This is a dual command --
// Cypress.Commands.add("dismiss", { prevSubject: 'optional'}, (subject, options) => { ... })
//
//
// -- This will overwrite an existing command --
// Cypress.Commands.overwrite("visit", (originalFn, url, options) => { ... })

Cypress.Commands.add("testNoAccess", (url) => {
  cy.request({
    url: url,
    failOnStatusCode: false // turn off following redirects
  })
    .then((resp) => {
      expect(resp.status).to.eq(403)
    })
});

Cypress.Commands.add("testAccess", (url) => {
  cy.request({
    url: url
  })
    .then((resp) => {
      expect(resp.status).to.eq(200)
    })
});

// ============== Only to you see tests more slow ===========
// const COMMAND_DELAY = 500;
//
// for (const command of ['visit', 'click', 'trigger', 'type', 'clear', 'reload', 'contains']) {
//   Cypress.Commands.overwrite(command, (originalFn, ...args) => {
//     const origVal = originalFn(...args);
//
//     return new Promise((resolve) => {
//       setTimeout(() => {
//         resolve(origVal);
//       }, COMMAND_DELAY);
//     });
//   });
// }

// ============== End: Only to you see tests more slow ===========
