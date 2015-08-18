// Require authentication page object.
var SamplePage = require('./sample.page');
var RegistrationPage = require('./registration.page');
var AuthenticationPage = require('./authentication.page');
var FieldnotePage = require('./artifact.fieldnote.page');
var LegalPage = require('./legal.page');
var PeceArtifactPage = require('./pece.artifact.page');
var AddTypesPage = require('./add.types.page');
var ContentPage = require('./content.page');
var PeoplePage = require('./people.page');
var UserProfilePage = require('./user.profile.page');
var ArtifactImagePage = require('./artifact.image.page');
var ArtifactPdfPage = require('./artifact.pdf.page');
var ArtifactVideoPage = require('./artifact.video.page');
var ArtifactAudioPage = require('./artifact.audio.page');
var ArtifactWebsitePage = require('./artifact.website.page');
var ArtifactTextPage = require('./artifact.text.page');

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
  , 'UserProfilePage': UserProfilePage
  , 'ArtifactImagePage': ArtifactImagePage
  , 'ArtifactPdfPage': ArtifactPdfPage
  , 'ArtifactVideoPage': ArtifactVideoPage
  , 'ArtifactAudioPage': ArtifactAudioPage
  , 'ArtifactWebsitePage': ArtifactWebsitePage
  , 'ArtifactTextPage': ArtifactTextPage
}
