<?php

namespace Drupal\pece_home\Controller;

use \Drupal\Core\Controller\ControllerBase;
use Drupal\Core\Access\AccessResult;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Render\RendererInterface;
use Drupal\Core\Entity\EntityTypeManager;
use Drupal\Core\Config\ConfigFactoryInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Builds the standard PECE front page.
 */
class HomeController extends ControllerBase {

  /**
   * The renderer.
   *
   * @var \Drupal\Core\Render\RendererInterface
   */
  protected $renderer;

  /**
   * The entity manager.
   *
   * @var \Drupal\Core\Entity\EntityTypeManager
   */
  protected $entityTypeManager;

  /**
   * The config factory.
   *
   * @var \Drupal\Core\Config\ConfigFactoryInterface
   */
  protected $config;

  /**
   * Creates a new HomeController instance.
   *
   * @param \Drupal\Core\Renderer\RendererInterface $date_formatter
   *   The renderer instance.
   * @param \Drupal\Core\Entity\EntityTypeManager $entity_manager
   *   The entity manager.
   * @param \Drupal\Core\Config\ConfigFactoryInterface $date_formatter
   *   The config factory.
   */
  public function __construct(RendererInterface $renderer,
                              EntityTypeManager $entity_manager,
                              ConfigFactoryInterface $config_factory) {
    $this->renderer = $renderer;
    $this->entityTypeManager = $entity_manager;
    $this->config = $config_factory;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('renderer'),
      $container->get('entity_manager'),
      $container->get('config.factory')
    );
  }

  /**
   * Build default Home page.
   */
  public function buildPage() {
    $output = [];
    $frontPgPath = $this->config
      ->getEditable('system.site')
      ->get('page.front');

    // Skip if no front page.
    if (empty($frontPgPath)) {
      return $output;
    }

    // Load and render the node.
    if (strpos($frontPgPath,'/node/') !== FALSE) {
      $nid = str_replace('/node/', '', $frontPgPath);
      $node = $this->entityTypeManager()
        ->getStorage('node')
        ->load($nid);
      return $this->entityTypeManager()
        ->getViewBuilder('node')
        ->view($node, 'default');
    }
  }

  /**
   * Check if a custom home page is created.
   */
  public function isHomeCreated() {
    return !empty($frontPgPath = $this->config
      ->getEditable('system.site')
      ->get('page.front'));
  }

  /**
   * Return PECE default home or a custom home page if available.
   */
  public function defaultHome() {
    $output = $this->buildPage();
    dsm($this->isHomeCreated(), 'Is Home created?');
    dsm($output, 'Output');
    if  ($this->isHomeCreated()) {
     $output = '';
    }

    return $output;
  }

  /**
   * Checks access for a specific request.
   *
   * @param \Drupal\Core\Session\AccountInterface $account
   *   Run access checks for this account.
   *
   * @return \Drupal\Core\Access\AccessResultInterface
   *   The access result.
   */
  public function accessCheck($account) {
    // Check permissions. Pass forward parameters from the route and/or request
    // as needed.
    return AccessResult::allowedIf($account->hasPermission('access content'));
  }

}

