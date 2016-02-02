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
      type: 'user',
      data: {
        name: 'smoke-test-user-2',
        mail: 'smoke@test-user-2.com',
        pass: '123123',
        roles: [
          'contributor',
          'researcher'
        ]
      }
    },
    {
      type: 'user',
      data: {
        name: 'smoke-test-user-3',
        mail: 'smoke@test-user-3.com',
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
        field_pece_tags: [Seeds.parser(3, 'tid')]
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

  var groupPane = $('.pane-pece-recent-groups-panel-pane-1');
  var artifactPane = $('.pane-pece-recent-artifacts-panel-pane-1');
  var tagsPane = $('.pane-tagclouds-3');

  var group = groupPane.$('.node-pece-group');
  var artifact = artifactPane.$('.node-pece-artifact-text');
  var tag = tagsPane.$('.tagclouds');

  var groupLink = group.$('h5 a');
  var artifactLink = artifact.$('h5 a');
  var tagLink = tag.$('h5 a');

  beforeEach(function() {
    SamplePage.get();
  });

  it('check home page main elements', function() {
    expect(group.getText()).toEqual('SMOKE TEST GROUP');
    expect(artifact.getText()).toEqual('SMOKE TEST ARTIFACT TEXT');
    expect(tag.getText()).toEqual('smoke-test-tag');
  });

  it('check that user is directed to the clicked group page', function() {
    groupLink.click();

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /content\/smoke-test-group/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

  it('check that user can request being part of a group when in a group page', function() {
    groupLink.click();

    var requestGroupMembershiptButton = $('.pane-node-group-group');

    expect(requestGroupMembershiptButton.isDisplayed()).toBe(true);
  });

  it('check that user is directed to the clicked artifact page', function() {
    artifactLink.click();

    browser.getCurrentUrl().then(function(url) {
      var artifactUrl = /content\/smoke-test-artifact-text/.test(url);
      expect(artifactUrl).toBe(true);
    });
  });

  it('check that user is directed to the clicked artifact page from tag page', function() {
    var artifactIntoTagsPage = $('h5 a');

    tag.click();
    artifactIntoTagsPage.click();

    browser.getCurrentUrl().then(function(url) {
      var artifactUrl = /content\/smoke-test-artifact-text/.test(url);
      expect(artifactUrl).toBe(true);
    });
  });

  it('check that user is directed to the clicked tag page', function() {
    tag.click();

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /tags\/smoke-test-tag/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

  it('researcher/contributor user is directed to profile page on login', function() {
    AuthenticationPage.login('smoke-test-user', '123123');
    LegalPage.acceptTerm();

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /users\/smoke-test-user/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

  it('researcher/contributor user can annotate an artifact', function() {
    AuthenticationPage.logout();
    AuthenticationPage.login('smoke-test-user-2', '123123');
    LegalPage.acceptTerm();
    SamplePage.get();

    artifactLink.click();

    var annotateButton = $('.pane-annotation div a.annotate-link');

    expect(annotateButton.isDisplayed()).toBe(true);
  });

  it('researcher/contributor user can navigate to a tag through an artifact', function() {
    AuthenticationPage.logout();
    AuthenticationPage.login('smoke-test-user-3', '123123');
    LegalPage.acceptTerm();
    SamplePage.get();

    artifactLink.click();

    var tagLink = $('.field-name-field-pece-tags a');

    tagLink.click();

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /tags\/smoke-test-tag/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

});
