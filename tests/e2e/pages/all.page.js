// Require authentication page object.
var SamplePage = require('./sample.page');
var RegistrationPage = require('./registration.page');
var AuthenticationPage = require('./authentication.page');
var FieldnotePage = require('./fieldnote.page');
var LegalPage = require('./legal.page');
var PeceArtifactPage = require('./pece.artifact.page');
var AddTypesPage = require('./add.types.page');
var ContentPage = require('./content.page');
var PeoplePage = require('./people.page');

module.exports = {
  'SamplePage': SamplePage
  , 'RegistrationPage': RegistrationPage
  , 'AuthenticationPage': AuthenticationPage
  , 'FieldnotePage': FieldnotePage
  , 'LegalPage': LegalPage
  , 'PeceArtifactPage': PeceArtifactPage
  , 'AddTypesPage': AddTypesPage
  , 'ContentPage': ContentPage
  , 'PeoplePage': PeoplePage
}
