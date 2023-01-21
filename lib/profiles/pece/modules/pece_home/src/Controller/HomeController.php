<?php

namespace Drupal\pece_home\Controller;

use \Drupal\Core\Controller\ControllerBase;
use Drupal\Core\Url;
use Drupal\node\NodeInterface;
use Drupal\Core\Access\AccessResult;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Render\RendererInterface;
use Drupal\Core\Entity\EntityTypeManager;
use Drupal\Core\Config\ConfigFactoryInterface;
use Symfony\Component\HttpFoundation\RedirectResponse;
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
      $container->get('entity_type.manager'),
      $container->get('config.factory')
    );
  }

  /**
   * Build default Home page.
   */
  public function buildPage() {
    $output = [];
    $nid = $this->getFrontPageNid();
    $node = $this->loadFrontNode($nid);

    if (empty($node)) {
      return $output;
    }

    return $this->entityTypeManager()
      ->getViewBuilder('node')
      ->view($node, 'default');
  }

  /**
   * Get site front page config setting.
   *
   * @return array|mixed|null
   */
  private function getFrontPageSetting() {
    return $this->config
      ->getEditable('system.site')
      ->get('page.front');
  }

  private function getFrontPageNid() {
    $frontPgPath = $this->getFrontPageSetting();
    // Skip if no front page.
    if (empty($frontPgPath)) {
      return FALSE;
    }
    // Extract node id from system.site.page.front setting.
    if (strpos($frontPgPath,'/node/') !== FALSE) {
      $nid = str_replace('/node/', '', $frontPgPath);
      return $nid;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Load node set as front page.
   *
   * @return \Drupal\Core\Entity\EntityInterface|false
   * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
   * @throws \Drupal\Component\Plugin\Exception\PluginNotFoundException
   */
  private function loadFrontNode() {
    $nid = $this->getFrontPageNid();
    // Skip if node isn't available.
    if (empty($nid)) {
      return FALSE;
    }

    return $this->entityTypeManager()
      ->getStorage('node')
      ->load($nid);
  }

  /**
   * Check if a custom home page is created.
   */

  public function isHomeCreated() {
    $nid = $this->getFrontPageNid();
    // No front page is set.
    if (empty($nid)) {
      return FALSE;
    }

    // Is front page node published?
    $nid = \Drupal::entityQuery('node')
      ->accessCheck(TRUE)
      ->condition('nid', $nid, '=')
      ->condition('status', NodeInterface::PUBLISHED)
      ->execute();
    // There is a valid node.
    if (!empty($nid)) {
      return TRUE;
    }

    // Node is unpublished.
    return FALSE;
  }
  /**
   * Return PECE default home or a custom home page if available.
   */
  public function defaultHome() {
    if  ($this->isHomeCreated()) {
      return $this->buildPage();
    }
    // Redirect to front page as a fallback.
    $url = Url::fromRoute('<front>');
    $response = new RedirectResponse($url->toString());
    $response->send();
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

