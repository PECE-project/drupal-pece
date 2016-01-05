
var Seeds = require('drupal-seeds').Seeds;
var sampleTitles = [
    'COLLABORATE IN A GROUP',
    'ANALYZE AN ARTIFACT',
    'EXPERIMENT WITH TERMS',
  ];

describe('Homepage', function () {
  var seeds = new Seeds([
    {
      type: 'node',
      data: {
        type: 'pece_artifact_text',
        title: 'Text artifact',
        body: 'Text artifact description'
        }
    }
  ]);

  seeds.attach();

  it('Should have the Group section', function() {
    HomePage.get();
    browser.wait(HomePage.mainElements.groupsSection.isDisplayed);
    expect(HomePage.mainElements.groupsSection.getText()).toBe(sampleTitles[0])
  });

  it('Should have the Artifact section', function() {
    HomePage.get();
    browser.wait(HomePage.mainElements.artifactsSection.isDisplayed);
    expect(HomePage.mainElements.artifactsSection.getText()).toBe(sampleTitles[1])
  });

  it('Should have the Tags section', function() {
    HomePage.get();
    browser.wait(HomePage.mainElements.tagsSection.isDisplayed);
    expect(HomePage.mainElements.tagsSection.getText()).toBe(sampleTitles[2])
  });

});
