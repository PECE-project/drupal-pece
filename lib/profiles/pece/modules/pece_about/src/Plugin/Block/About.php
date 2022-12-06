<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the About block.
 *
 * @Block(
 *   id = "pece_about_about",
 *   admin_label = @Translation("About")
 * )
 */
class About extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    \Drupal::moduleHandler()->loadInclude('kw_itemnames', 'inc');
    $about_page = kw_itemnames_load('node', 'about');

    if (empty($about_page)) {
      \Drupal::moduleHandler()->loadInclude('install', 'pece_about');
      _pece_about_install_default_page();
      $about_page = kw_itemnames_load('node', 'about');
    }

    $node_wrapper = entity_metadata_wrapper('node', $about_page);
    $body_wrapper = $node_wrapper->body->value();
    $allowed_tags = '<p> <a> <em> <strong> <cite> <blockquote> <ul> <ol> <li> <dl> <dt> <dd>';
    $summary = text_summary(strip_tags($body_wrapper['value'], $allowed_tags), $body_wrapper['format'], 400);

    // Add ellipsis and read more link.
    return pece_about_trim_summary($summary, TRUE);
  }

}
