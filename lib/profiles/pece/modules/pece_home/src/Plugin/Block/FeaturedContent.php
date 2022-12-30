<?php

namespace Drupal\pece_home\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\views\Views;

/**
 * Provides the Featured Content block.
 *
 * @Block(
 *   id = "pece_home_featured",
 *   admin_label = @Translation("Featured"),
 *   category = @Translation("PECE")
 * )
 */
class FeaturedContent extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    // $viewFeatured = views_get_view_result('', 'block_1');
    $name = 'pece_featured_content';
    $display = 'block_1';

    $view = Views::getView($name);
    $view->setDisplay($display);
    $view->initDisplay();
    $view->preExecute();
    $view->execute();
    $output = $view->result;

    return [
      '#type' => 'container',
      '#items' => [
          'top' => [
            '#type' => 'container',
            '#markup' => 'Here goes the view of Featured content'
          ],
          'center' => [
            $output,
          ],
        ],
      ];
  }

  /**
   * {@inheritdoc}
   */
  public function blockForm($form, FormStateInterface $formState) {
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function blockSubmit($form, FormStateInterface $formState) {
    parent::blockSubmit($form, $formState);
  }
}
