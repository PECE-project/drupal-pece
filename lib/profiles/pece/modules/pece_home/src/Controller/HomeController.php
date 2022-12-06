<?php

namespace Drupal\pece_home\Controller;

use \Drupal\Core\Controller\ControllerBase;
use Drupal\Core\Render\RendererInterface;
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
   * Creates a new HomeController instance.
   *
   * @param \Drupal\Core\Renderer\RendererInterface $date_formatter
   *   The date formatter.
   */
  public function __construct(RendererInterface $renderer) {
    $this->renderer = $renderer;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static($container->get('renderer'));
  }

  /**
   * Build default Home page.
   */
  public function buildPage() {
    return [
      '#markup' => 'Home page',
    ];
  }

  /**
   * Check if a custom home page is created.
   */
  public function isHomeCreated() {
    return FALSE;
  }

  /**
   * Return PECE default home or a custom home page if available.
   */
  public function defaultHome() {
    $output = $this->buildPage();

    if  ($this->isHomeCreated()) {
     $output = '';
    }

    return $output;
  }
}