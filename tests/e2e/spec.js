
describe('PECE home page', function() {
  beforeEach(function() {
    SamplePage.get();
  });

  it('uses \'PECE Scholarly Lite\' theme', function() {
    SamplePage.checkDrupalTheme('pece_scholarly_lite');
  });
});

require('./specs/registration.spec.js');
require('./specs/artifacts/artifact.fieldnote.spec.js');
require('./specs/license.spec.js');
require('./specs/user.profile.spec.js');
require('./specs/user.access.spec.js');
require('./specs/artifacts/artifact.image.spec.js');
require('./specs/artifacts/artifact.pdf.spec.js');
require('./specs/artifacts/artifact.video.spec.js');
require('./specs/artifacts/artifact.audio.spec.js');
require('./specs/artifacts/artifact.website.spec.js');
require('./specs/artifacts/artifact.bundle.spec.js');
require('./specs/annotation.spec.js');
require('./specs/memo.spec.js');
require('./specs/group.spec.js');
require('./specs/homepage.spec.js');
require('./specs/field.diary.spec.js');
require('./specs/group.field.diary.spec.js');
