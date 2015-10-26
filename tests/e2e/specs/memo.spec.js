
var Seeds = require('drupal-seeds').Seeds;

describe('Memo', function () {
  var seeds = new Seeds([
    {
      type: 'user',
      data: { name: 'contributor', mail: 'contributor@email.com', roles: ['Contributor'], pass: '123123' },
      config: { accept_legal_terms: true }
    },
    {
      type: 'user',
      data: { name: 'contributor 2', mail: 'contributor2@email.com', roles: ['Contributor'], pass: '123123' },
      config: { accept_legal_terms: true }
    }
  ]);

  seeds.attach();

  it('Verify main elements presence', function() {
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    MemoPage.get();
    MemoPage.checkMainElementsPresence();
  });

  it('Verify mandatory fields', function() {
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    MemoPage.get();
    MemoPage.checkMandatoryFields();
  });

  it('Add a Memo as an authenticated user', function() {
    // @TODO: create a specific seed for this.
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();

    AuthenticationPage.login('contributor', '123123');
    MemoPage.add('Memo', 'Lorem ipsum dolar sit.');

    MemoPage.checkPageLayout();
    MemoPage.checkPageElements();
  });

  it('should have comments opened but moderated for an authenticated users.', function() {
    // @TODO: create a specific seed for this.
    AuthenticationPage.login(browser.params.admin.user, browser.params.admin.password);
    SamplePage.get('admin/config/people/legal');
    LegalPage.create();

    // @TODO: replace with a node seed, created with user/author using 'seeds.values[0].uid'.
    AuthenticationPage.login('contributor', 123123);
    MemoPage.add('Memo 2', 'Lorem ipsum dolar sit.');

    AuthenticationPage.login('Contributor 2', 123123);
    MemoPage.comment('content/memo-2', 'Comment content');

    SamplePage.checkMessage('Your comment has been queued for review by site administrators and will be published after approval.');
  });
});
