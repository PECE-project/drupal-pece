<?php

namespace Drupal\Tests\pece_groups\Kernel;

use Drupal\Core\Entity\EntityFormInterface;
use Drupal\Core\Form\FormState;
use Drupal\KernelTests\KernelTestBase;
use Drupal\taxonomy\Entity\Term;
use Drupal\user\Entity\User;

/**
 * Tests the pece_groups form hook that pre-fills the group manager field.
 *
 * The hook sets the current user as the default group manager when a new
 * taxonomy term in the groups vocabulary is being created.
 *
 * @group pece_groups
 */
class GroupManagerDefaultTest extends KernelTestBase {

  protected static $modules = ['system', 'user', 'field', 'taxonomy'];

  /**
   * The test user set as the current session account.
   *
   * @var \Drupal\user\Entity\User
   */
  protected $currentUser;

  protected function setUp(): void {
    parent::setUp();

    $this->installEntitySchema('user');
    $this->installEntitySchema('taxonomy_term');
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['system', 'user']);

    // Load the hook function without requiring the full module dep chain.
    require_once \Drupal::root() . '/profiles/pece/modules/pece_groups/pece_groups.module';

    $this->currentUser = User::create([
      'name' => 'manager_user',
      'mail' => 'manager@example.com',
      'status' => 1,
    ]);
    $this->currentUser->save();

    \Drupal::currentUser()->setAccount($this->currentUser);
  }

  /**
   * Tests that the current user is set as the first group manager widget value
   * when creating a new taxonomy term.
   */
  public function testNewTermGetsCurrentUserAsDefaultManager(): void {
    $term = Term::create(['vid' => 'groups', 'name' => 'New Group']);

    $form_object = $this->createMock(EntityFormInterface::class);
    $form_object->method('getEntity')->willReturn($term);

    $form_state = new FormState();
    $form_state->setFormObject($form_object);

    $form = [
      'field_group_managers' => [
        'widget' => [
          0 => [
            'target_id' => ['#default_value' => NULL],
          ],
        ],
      ],
    ];

    pece_groups_form_taxonomy_term_groups_form_alter($form, $form_state, 'taxonomy_term_groups_form');

    $default = $form['field_group_managers']['widget'][0]['target_id']['#default_value'];
    $this->assertInstanceOf(User::class, $default);
    $this->assertEquals($this->currentUser->id(), $default->id());
  }

  /**
   * Tests that widget[1] is created as a copy of widget[0] for new terms.
   */
  public function testNewTermAddsSecondWidgetSlot(): void {
    $term = Term::create(['vid' => 'groups', 'name' => 'Another Group']);

    $form_object = $this->createMock(EntityFormInterface::class);
    $form_object->method('getEntity')->willReturn($term);

    $form_state = new FormState();
    $form_state->setFormObject($form_object);

    $original_widget = ['target_id' => ['#default_value' => NULL, '#type' => 'entity_autocomplete']];
    $form = [
      'field_group_managers' => [
        'widget' => [0 => $original_widget],
      ],
    ];

    pece_groups_form_taxonomy_term_groups_form_alter($form, $form_state, 'taxonomy_term_groups_form');

    $this->assertArrayHasKey(1, $form['field_group_managers']['widget']);
  }

  /**
   * Tests that existing terms are not modified.
   */
  public function testExistingTermIsNotAltered(): void {
    $term = Term::create(['vid' => 'groups', 'name' => 'Existing Group']);
    $term->save();

    $form_object = $this->createMock(EntityFormInterface::class);
    $form_object->method('getEntity')->willReturn($term);

    $form_state = new FormState();
    $form_state->setFormObject($form_object);

    $form = [
      'field_group_managers' => [
        'widget' => [
          0 => ['target_id' => ['#default_value' => NULL]],
        ],
      ],
    ];

    pece_groups_form_taxonomy_term_groups_form_alter($form, $form_state, 'taxonomy_term_groups_form');

    // Saved term is not new — default value must remain untouched.
    $this->assertNull($form['field_group_managers']['widget'][0]['target_id']['#default_value']);
    $this->assertArrayNotHasKey(1, $form['field_group_managers']['widget']);
  }

}
