var Seeds = require('drupal-seeds').Seeds;

describe('PECE Smoke test', function() {

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
    },
    {
      type: 'node',
      data: {
        type: 'pece_sub_logic',
        title: 'Substantive logic test',
        field_pece_tags: [Seeds.parser(3, 'tid')],
        field_pece_sub_logic_citation_link: '',
        body: 'Substantive logic body',
        field_pece_uri: 'logic body uri'
      }
    }
  ]);

  seeds.attach();

  var groupPane = $('.pane-pece-recent-groups-panel-pane-1');
  var artifactPane = $('.pane-pece-recent-artifacts-panel-pane-1');
  var tagsPane = $('.pane-tagclouds-3');

  var firstGroup = groupPane.all(by.css('.node-pece-group')).first();
  var firstArtifact = artifactPane.all(by.css('.node-pece-artifact-text')).first();
  var firstTag = tagsPane.all(by.css('.tagclouds')).first();

  var firstGroupLink = firstGroup.all(by.css('h5 a')).first();
  var firstArtifactLink = firstArtifact.all(by.css('h5 a')).first();

  beforeEach(function() {
    SamplePage.get();
  });

  it('check home page main elements', function() {
    expect(groupPane.isDisplayed()).toBe(true);
    expect(firstGroup.isDisplayed()).toBe(true);
    expect(firstGroupLink.isDisplayed()).toBe(true);

    expect(artifactPane.isDisplayed()).toBe(true);
    expect(firstArtifact.isDisplayed()).toBe(true);
    expect(firstArtifactLink.isDisplayed()).toBe(true);

    expect(tagsPane.isDisplayed()).toBe(true);
    expect(firstTag.isDisplayed()).toBe(true);
  });

  it('check that user is directed to the clicked group page', function() {
    firstGroupLink.click();

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /content\/smoke-test-group/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

  it('check that user can request being part of a group when in a group page', function() {
    firstGroupLink.click();

    var requestGroupMembershiptButton = $('.pane-node-group-group');

    expect(requestGroupMembershiptButton.isDisplayed()).toBe(true);
  });

  it('check that user is directed to the clicked artifact page', function() {
    firstArtifactLink.click();

    browser.getCurrentUrl().then(function(url) {
      var artifactUrl = /content\/smoke-test-artifact-text/.test(url);
      expect(artifactUrl).toBe(true);
    });
  });

  xit('check that user is directed to the clicked artifact page from tag page', function() {
    // The below element is not clickable when running the test against dev environment.
    // It says that other element would receive the click: <div class="panel-pane pane-block pane-tagclouds-3">...</div>
    // I think this is happening because of some broken images in this environment,
    // even the message not saying exactly this. It needs more investigation.
    firstTag.click();

    var firstArtifactIntoTagsPage = element.all(by.css('h5 a')).first();

    // The below logic is used to make the test independent of environment,
    // because depending on the environment the first artifact will change,
    // since depending on the environment the first tag will change also.
    firstArtifactIntoTagsPage.getText().then(function(text) {
      var artifactText = text;
      var artifactTextToLower = artifactText.toLowerCase();
      var artifactTextToUrl = artifactTextToLower.replace(/ /g, '-');

      firstArtifactIntoTagsPage.click();

      browser.getCurrentUrl().then(function(url) {
        var artifactUrl = '/content/' + artifactTextToUrl;

        expect(url).toContain(artifactUrl);
      })

    });
  }).pend('This test if failing when running against dev environment. It needs review.');

  it('check that user is directed to the clicked tag page', function() {
    // The below logic is used to make the test independent of environment,
    // because depending on the environment the first tag will change.
    firstTag.getText().then(function(text) {
      var tagText = text;

      firstTag.click();

      browser.getCurrentUrl().then(function(url) {
        var tagUrl = '/tags/' + tagText;

        expect(url).toContain(tagUrl);
      });
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

    firstArtifactLink.click();

    var annotateButton = $('.pane-annotation div a.annotate-link');

    expect(annotateButton.isDisplayed()).toBe(true);
  });

  it('researcher/contributor user can navigate to a tag through an artifact', function() {
    AuthenticationPage.logout();
    AuthenticationPage.login('smoke-test-user-3', '123123');
    LegalPage.acceptTerm();
    SamplePage.get();

    firstArtifactLink.click();

    var tagLink = $('.field-name-field-pece-tags a');

    tagLink.click();

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /tags\/smoke-test-tag/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

  it('any user can navigate to a substantive logic content', function() {
    AuthenticationPage.logout();
    SamplePage.get('content/substantive-logic-test');

    browser.getCurrentUrl().then(function(url) {
      var currentUrl = /content\/substantive-logic-test/.test(url);
      expect(currentUrl).toBe(true);
    });
  });

});
