/**
* @file license.spec.js
*/

var AllPages= require('./pages/all.page');

// Used for non-angular apps
browser.ignoreSynchronization = true;

// For each spec file is recommended to have just one describe.
// A describe may the the description of a functionality/feature or even a web page, like home page, contact page, etc. It depends on the team work agreement
describe ('License' , function () {
  beforeEach(function () {
    AllPages.AuthenticationPage.logout();
    AllPages.AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
  });

  it ('should check the field_pece_license is present for Artifact content type', function () {
    AllPages.PeceArtifactPage.get();
    expect(AllPages.PeceArtifactPage.licenseField.isPresent()).toBe(true);
    expect(AllPages.PeceArtifactPage.licenseFieldDefaultValue.getText()).toEqual('Attribution, Share Alike CC BY-SA');
  });

  it ('should be able to inherit the artifact fields', function () {
    AllPages.AddTypesPage.get();
    AllPages.AddTypesPage.inheritanceLink.click();
    AllPages.AddTypesPage.inheritanceCheckBox.click();
    expect(AllPages.AddTypesPage.bundleInheritParentSelect.getText()).toContain('Artifact');
  });
});
