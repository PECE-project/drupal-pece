
var Seeds = require('drupal-seeds').Seeds;

describe('Group field diary', function () {
  var seeds = new Seeds([{
    type: 'node',
    data: {
      type: 'pece_group',
      title: 'Test',
    },
    // {
    //   type: 'user',
    //   data: { name: 'contributor', mail: 'contributor@email.com', roles: ['contributor'], pass: '123123' },
    //   config: { accept_legal_terms: true }
    // },
    // {
    //   type: 'user',
    //   data: { name: 'researcher', mail: 'researcher@email.com', roles: ['researcher'], pass: '123123' },
    //   config: { accept_legal_terms: true }
    // },
  }]);

  seeds.attach();

  beforeAll(function() {
    AuthenticationPage.logout();
  });

  it('no results', function() {
    FieldDiaryPage.get('pece-group-field-diary/' + seeds.values[0].nid);
    expect(FieldDiaryPage.emptyResult.getText()).toEqual('There are no field notes for the current group.');
  });

  xit('verify main elements presence', function() {

  }).pend('Test not created yet. TODO!');

  xit('only show fieldnotes from the current group', function() {

  }).pend('Test not created yet. TODO!');

  xit('restricted fieldnotes are only displayed for researcher users', function() {

  }).pend('Test not created yet. TODO!');

  xit('private fieldnotes are only displayed for the fieldnote\'s author', function() {

  }).pend('Test not created yet. TODO!');
});
