/**
* @file license.spec.js
*/

var AllPages= require('../pages/all.page');

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('License' , function () {
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  it ('check the field_pece_license presence and its default value for Artifact content type', function () {
    AllPages.PeceArtifactPage.get();
    expect(AllPages.PeceArtifactPage.licenseField.isPresent()).toBe(true);
    expect(AllPages.PeceArtifactPage.licenseFieldDefaultValue.getText()).toEqual('Attribution, Share Alike CC BY-SA');
  });

  // @TODO: I think it could be in another file, since this is not directly related with Licence.
  it ('can inherit Artifact\'s fields', function () {
    AllPages.AddTypesPage.get();
    AllPages.AddTypesPage.inheritanceLink.click();
    AllPages.AddTypesPage.inheritanceCheckBox.click();
    // @TODO: Today we already have two more artifacts with the word Artifact, beyond the one that we need
    // to check, like Artifact - Image and Artifact - PDF Document, so, this is a not reliable test.
    expect(AllPages.AddTypesPage.bundleInheritParentSelect.getText()).toContain('Artifact');
  });
});
