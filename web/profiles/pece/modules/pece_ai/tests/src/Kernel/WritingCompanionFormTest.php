<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\Core\Form\FormState;
use Drupal\KernelTests\KernelTestBase;

/**
 * Tests that pece_ai_form_alter() wires the Writing Companion into target forms.
 *
 * @group pece_ai
 */
class WritingCompanionFormTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter',
    'block', 'pece_ai',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installSchema('node', ['node_access']);
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);
  }

  /**
   * Calls pece_ai_form_alter() with a minimal form stub and returns the result.
   */
  private function applyFormAlter(string $formId): array {
    $form = ['body' => ['#type' => 'text_format', '#weight' => 5]];
    $formState = new FormState();
    pece_ai_form_alter($form, $formState, $formId);
    return $form;
  }

  /**
   * Tests that the button and placeholder are added to annotation step 2.
   */
  public function testFormAlterAddsButtonToAnnotationStep2(): void {
    $form = $this->applyFormAlter(
      'node_pece_annotation_annotation_step_2_form'
    );
    $this->assertArrayHasKey('pece_ai_suggest', $form);
    $this->assertArrayHasKey('pece_ai_suggestions_placeholder', $form);
    $this->assertEquals('button', $form['pece_ai_suggest']['#type']);
  }

  /**
   * Tests that the button is added to the essay add form.
   */
  public function testFormAlterAddsButtonToEssayForm(): void {
    $form = $this->applyFormAlter('node_pece_essay_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
    $this->assertArrayHasKey('pece_ai_suggestions_placeholder', $form);
  }

  /**
   * Tests that the button is added to the essay edit form.
   */
  public function testFormAlterAddsButtonToEssayEditForm(): void {
    $form = $this->applyFormAlter('node_pece_essay_edit_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the photo essay add form.
   */
  public function testFormAlterAddsButtonToPhotoEssayForm(): void {
    $form = $this->applyFormAlter('node_pece_photo_essay_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the photo essay edit form.
   */
  public function testFormAlterAddsButtonToPhotoEssayEditForm(): void {
    $form = $this->applyFormAlter('node_pece_photo_essay_edit_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the timeline essay add form.
   */
  public function testFormAlterAddsButtonToTimelineEssayForm(): void {
    $form = $this->applyFormAlter('node_pece_timeline_essay_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the timeline essay edit form.
   */
  public function testFormAlterAddsButtonToTimelineEssayEditForm(): void {
    $form = $this->applyFormAlter('node_pece_timeline_essay_edit_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that unrelated forms are not modified.
   */
  public function testFormAlterIgnoresUnrelatedForms(): void {
    $form = $this->applyFormAlter('user_login_form');
    $this->assertArrayNotHasKey('pece_ai_suggest', $form);
    $this->assertArrayNotHasKey('pece_ai_suggestions_placeholder', $form);
  }

}
