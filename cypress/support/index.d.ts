/// <reference types="Cypress" />

declare namespace Cypress {
  interface Chainable {
    type_tinyMCE(element: string, content: string):Cypress.Chainable<JQuery>;
    createUser(name:string, role?:string, password = '123456789'): Cypress.Chainable<JQuery>;
    deleteUser(name: string): Cypress.Chainable<JQuery>;
    login(user:string, password = '123456789'): Cypress.Chainable<JQuery>;
    createContent(path:string, fields:[], beforeSave = () => {}): Cypress.Chainable<JQuery>;
    deleteContent(title: string): Cypress.Chainable<JQuery>;
  }
}
