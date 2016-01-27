var Seeds = require('drupal-seeds').Seeds;

describe('Smoke test', function() {

  var seeds = new Seeds([
    {
      type: 'user',
      data: {
        name: 'smoke-test-user',
        mail: 'smoke@test-user.com',
        pass: '123123',
        roles: [
          'contributor',
          'researcher'
        ]
      }
    },
    {
      type: 'term',
      data: {
        type: 'pece_tags',
        name: 'smoke-test-tag'
      }
    },
    {
      type: 'node',
      data: {
        type: 'pece_artifact_text',
        title: 'Smoke test artifact text',
        field_pece_tags: [Seeds.parser(1, 'tid')]
      }
    },
    {
      type: 'node',
      data: {
        type: 'pece_memo',
        title: 'Smoke test memo'
      }
    },
    {
      type: 'node',
      data: {
        type: 'pece_group',
        title: 'Smoke test group'
      }
    }
  ]);

  seeds.attach();

  it('navigate through the site as a anonymous user', function() {
    SamplePage.get();
    browser.pause();
  });

});

// require('./specs/some-test.spec.js');
