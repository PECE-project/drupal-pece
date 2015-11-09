
var Seeds = require('drupal-seeds').Seeds;
var sampleTitles = [
    'COLLABORATE IN A GROUP',
    'ANALYZE AN ARTIFACT',
    'EXPERIMENT WITH TERMS',
  ];

fdescribe('Homepage', function () {
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

  it('Should have the artifact section', function() {
    HomePage.get();
    expect(HomePage.mainElements.artifactSection.getText()).toBe(sampleTitles[1])
  });

});
