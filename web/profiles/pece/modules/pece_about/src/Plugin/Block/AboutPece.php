<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the AboutPece block.
 *
 * @Block(
 *   id = "pece_about_about_pece",
 *   admin_label = @Translation("About PECE")
 * )
 */
class AboutPece extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    $twigFilePath = \Drupal::service('extension.path.resolver')
      ->getPath('module', 'pece_about') . '/templates/pece-about-block.html.twig';
    $twigService = \Drupal::service('twig');
    $template = $twigService->loadTemplate($twigFilePath);
    return $template->render();
  }

}
