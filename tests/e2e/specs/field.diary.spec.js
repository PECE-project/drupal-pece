
var Seeds = require('drupal-seeds').Seeds;

describe('Field diary', function () {
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

  xit('only show fieldnotes created by the logged in user', function() {

  }).pend('Test not created yet. TODO!');

  xit('no results', function() {

  }).pend('Test not created yet. TODO!');
});
