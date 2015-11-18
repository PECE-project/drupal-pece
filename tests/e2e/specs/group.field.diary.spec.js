
var Seeds = require('drupal-seeds').Seeds;

describe('Group field diary', function () {
  var seeds = new Seeds([
    {
      // type: 'user',
      // data: { name: 'contributor', mail: 'contributor@email.com', roles: ['Contributor'], pass: '123123' },
      // config: { accept_legal_terms: true }
    },
    {
      // type: 'user',
      // data: { name: 'contributor 2', mail: 'contributor2@email.com', roles: ['Contributor'], pass: '123123' },
      // config: { accept_legal_terms: true }
    }
  ]);

  seeds.attach();

  beforeAll(function() {
    AuthenticationPage.logout();
  });

  xit('verify main elements presence', function() {

  }).pend('Test not created yet. TODO!');

  xit('only show fieldnotes from the current group', function() {

  }).pend('Test not created yet. TODO!');

  xit('restricted fieldnotes are only displayed for researcher users', function() {

  }).pend('Test not created yet. TODO!');

  xit('private fieldnotes are only displayed for the fieldnote\'s author', function() {

  }).pend('Test not created yet. TODO!');

  xit('no results', function() {

  }).pend('Test not created yet. TODO!');
});
