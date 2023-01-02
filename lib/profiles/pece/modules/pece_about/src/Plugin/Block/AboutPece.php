<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Session\AccountProxy;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides the AboutPece block.
 *
 * @Block(
 *   id = "pece_about_about_pece",
 *   admin_label = @Translation("About PECE")
 * )
 */
class AboutPece extends BlockBase implements ContainerFactoryPluginInterface {

   /**
   * @param \Symfony\Component\DependencyInjection\ContainerInterface $container
   * @param array $configuration
   * @param string $plugin_id
   * @param mixed $plugin_definition
   *
   * @return static
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('current_user'),
      $container->get('extension.path.resolver')
    );
  }

  /**
   * @param array $configuration
   * @param string $plugin_id
   * @param mixed $plugin_definition
   * @param  $account
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, AccountProxy $account) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->currentUser = $account;
  }

  /**
   * {@inheritdoc}
   */
  public function build() {
    $twigFilePath = \Drupal::service('extension.path.resolver')
      ->getPath('module', 'pece_about') . '/templates/pece-about-block.html.twig';
    $twigService = \Drupal::service('twig');
    $template = $twigService->loadTemplate($twigFilePath);
    // return $template->render([
    //   'default' => '',
    // ]);

    return [];
  }

}
