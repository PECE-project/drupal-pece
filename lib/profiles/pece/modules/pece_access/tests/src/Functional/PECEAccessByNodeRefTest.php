<?php

namespace Drupal\Tests\pece_access\Functional;

use Drupal\Tests\pbf\Functional\PbfAccessByNodeRefTest;

/**
 * Test access permissions with Pbf field which reference node.
 *
 * @group pece_access
 */
class PECEAccessByNodeRefTest extends PbfAccessByNodeRefTest {

  /**
   * Modules to install.
   *
   * @var array
   */
  public static $modules = array(
    'address',
    'admin_toolbar',
    'admin_toolbar_tools',
    'bibcite',
    'bibcite_entity',
    'block',
    'block_content',
    'breakpoint',
    'ckeditor',
    'color',
    'color_field',
    'comment',
    'components',
    'config',
    'config_filter',
    'config_partial_export',
    'config_translation',
    'consumers',
    'contact',
    'content_moderation',
    'content_translation',
    'contextual',
    'ctools',
    'datetime',
    'datetime_range',
    'dblog',
    'eck',
    'entity',
    'entity_browser',
    'entity_browser_entity_form',
    'entity_reference_revisions',
    'field',
    'field_ui',
    'field_group',
    'file',
    'filter',
    'geolocation',
    'graphql',
    'graphql_people',
    'hal',
    'help',
    'history',
    'image',
    'inline_entity_form',
    'language',
    'locale',
    'layout_builder',
    'layout_discovery',
    'link',
    'locale',
    'languagefield',
    'location_migration',
    'media',
    'media_library',
    'metatag',
    'metatag_dc',
    'metatag_dc_advanced',
    'metatag_open_graph',
    'metatag_verification',
    'metatag_views',
    'migrate',
    'migrate_devel',
    'migrate_drupal',
    'migrate_plus',
    'migrate_tools',
    'node',
    'nyx_graphql',
    'options',
    'pbf',
    'paragraphs_type_permissions',
    'paragraphs',
    'pathauto',
    'workflow',
    'path',
    'pece_analytics',
    'path_alias',
    'pece_access',
    'pece_artifacts_audio',
    'pece_artifacts_bundle',
    'pece_artifacts_fieldsite',
    'pece_artifacts_image',
    'pece_artifacts_text',
    'pece_artifacts_video',
    'pece_core',
    'pece_annotations',
    'pece_artifacts',
    'pece_essay',
    'pece_frontpage_slideshow',
    'pece_groups',
    'pece_memo',
    'pece_migrate',
    'pece_n8n',
    'pece_oauth',
    'pece_photo_essay',
    'pece_project',
    'pece_rules_webhook',
    'pece_timeline_essay',
    'pece_subst_logic',
    'profile',
    'quickedit',
    'rdf',
    'rest',
    'restui',
    'rules',
    'search',
    'serialization',
    'shortcut',
    'system',
    'search_api',
    'simple_oauth',
    'taxonomy',
    'text',
    'toolbar',
    'token',
    'typed_data',
    'update',
    'user',
    'views',
    'views_ui',
    'workflow'
  );
  protected $profile = 'pece';
  /*
   * Field name to add.
   *
   * @var string
   */
  protected $fieldname;

  /**
   * Setup and create content with Pbf field.
   */
  public function setUp() {
    parent::setUp();

    $this->fieldname = 'field_pbf_group';
    $this->attachPbfNodeFields($this->fieldname);

    $this->article1 = $this->createSimpleArticle('Article 1', $this->fieldname, $this->group1->id(), 1, 0, 0, 0);
    $this->article2 = $this->createSimpleArticle('Article 2', $this->fieldname, $this->group1->id(), 0, 1, 0, 0);
  }

  /**
   * Test the "pbf" node access with a Pbf field which reference node.
   */
  public function testPbfAccessByNodeRef() {

    $this->drupalLogin($this->adminUser);

    $this->drupalGet("node/{$this->article1->id()}");
    $this->assertResponse(200, 'adminUser is allowed to view the content.');
    $this->drupalGet("node/{$this->article1->id()}/edit");
    // Make sure we don't get a 401 unauthorized response:
    $this->assertResponse(200, 'adminUser is allowed to edit the content.');

    $bundle_path = 'admin/structure/types/manage/article';
    // Check that the field appears in the overview form.
    $this->drupalGet($bundle_path . '/fields');
    $this->assertFieldByXPath('//table[@id="field-overview"]//tr[@id="field-pbf-group"]/td[1]', 'Content of group', 'Field was created and appears in the overview page.');

    // Check that the field appears in the overview manage display form.
    $this->drupalGet($bundle_path . '/form-display');
    $this->assertFieldByXPath('//table[@id="field-display-overview"]//tr[@id="field-pbf-group"]/td[1]', 'Content of group', 'Field appears in the Manage form display page.');
    $this->assertFieldByName('fields[field_pbf_group][type]', 'pbf_widget', 'The expected widget is selected.');

    // Check that the field appears in the overview manage display page.
    $this->drupalGet($bundle_path . '/display');
    $this->assertFieldByXPath('//table[@id="field-display-overview"]//tr[@id="field-pbf-group"]/td[1]', 'Content of group', 'Field appears in the Manage form display page.');
    $this->assertFieldByName('fields[field_pbf_group][type]', 'pbf_formatter_default', 'The expected formatter is selected.');

    $user_path_config = 'admin/config/people/accounts';
    $this->drupalGet($user_path_config . '/fields');
    $this->assertFieldByXPath('//table[@id="field-overview"]//tr[@id="field-pbf-group"]/td[1]', 'Member of group', 'User Obf field was created and appears in the overview page.');
    $this->drupalGet($user_path_config . '/form-display');
    $this->assertFieldByName('fields[field_pbf_group][type]', 'pbf_widget', 'The expected widget is selected.');
    $this->drupalGet($user_path_config . '/display');
    $this->assertFieldByName('fields[field_pbf_group][type]', 'pbf_formatter_default', 'The expected formatter is selected.');

    // Test view access with normal user.
    $this->drupalLogin($this->normalUser);
    $this->drupalGet("node/{$this->article2->id()}");
    $this->assertText(t('You are not authorized to access this page'));
    $this->assertResponse(403);
    $this->drupalGet("node/{$this->article1->id()}");
    $this->assertResponse(200);

    $this->drupalGet("node/{$this->article1->id()}/edit");
    $this->assertResponse(403);
    $this->drupalGet("node/{$this->article2->id()}/edit");
    $this->assertResponse(403);

    //TODO: create test to check result in the search page. See PbfAccessByNodeRefTest.

    // Set article2 as public without custom permission.
    $value = [
      'target_id' => $this->group1->id(),
      'grant_public' => 1,
      'grant_view' => 0,
      'grant_update' => 0,
      'grant_delete' => 0,
    ];
    $this->article2->set($this->fieldname, $value)->save();
    $this->drupalGet("node/{$this->article2->id()}");
    $this->assertResponse(200);
    //TODO: create test to check result in the search page with 2 results. See PbfAccessByNodeRefTest.

    $this->drupalGet("node/{$this->article2->id()}/edit");
    $this->assertResponse(403);

    $this->drupalGet("node/{$this->article2->id()}/delete");
    $this->assertResponse(403);

    // Set article2 with view permission.
    $value = [
      'target_id' => $this->group1->id(),
      'grant_public' => 0,
      'grant_view' => 1,
      'grant_update' => 0,
      'grant_delete' => 0,
    ];
    $this->article2->set($this->fieldname, $value)->save();
    $this->drupalGet("node/{$this->article2->id()}");
    $this->assertResponse(403);
    //TODO: create test to check result in the search page with 1 result. See PbfAccessByNodeRefTest.

    // Associate normalUser with group1.
    $this->setUserField($this->normalUser->id(), $this->fieldname, ['target_id' => $this->group1->id()]);

    // Check if user is well associated with group1.
    $this->drupalGet("user/{$this->normalUser->id()}/edit");
    $this->assertResponse(200);
    $this->assertFieldByName('field_pbf_group[0][target_id]', $this->group1->getTitle() . ' (' . $this->group1->id() . ')', 'The expected value is found in the Pbf input field');
    $this->drupalGet("user/{$this->normalUser->id()}");
    $this->assertLink($this->group1->getTitle());
    $this->assertResponse(200);

    // Check search.
    $this->container->get('cron')->run();
    //TODO: create test to check result in the search page with 2 result. See PbfAccessByNodeRefTest.
    // Check view.
    $this->drupalGet("node/{$this->article2->id()}");
    $this->assertResponse(200);
    // Check edit.
    $this->drupalGet("node/{$this->article2->id()}/edit");
    $this->assertResponse(403);
    // Check delete.
    $this->drupalGet("node/{$this->article2->id()}/delete");
    $this->assertResponse(403);

    // Set article2 with view, update, delete permissions.
    $value = [
      'target_id' => $this->group1->id(),
      'grant_public' => 0,
      'grant_view' => 1,
      'grant_update' => 1,
      'grant_delete' => 1,
    ];
    $this->article2->set($this->fieldname, $value)->save();
    // Check view.
    $this->drupalGet("node/{$this->article2->id()}");
    $this->assertResponse(200);
    // Check edit.
    $this->drupalGet("node/{$this->article2->id()}/edit");
    $this->assertResponse(200);
    // Check delete.
    $this->drupalGet("node/{$this->article2->id()}/delete");
    $this->assertResponse(200);

    // Test with anonymous user.
    $this->drupalLogout();
    $this->drupalGet("node/{$this->article1->id()}");
    $this->assertResponse(200);
    $this->drupalGet("node/{$this->article2->id()}");
    $this->assertResponse(403);

  }

}
