<?php

namespace Drupal\pece_about\Form;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Url;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Builds the form to create About page content.
 *
 * @codeCoverageIgnore
 */
class CreateAboutBodyForm extends ConfigFormBase {

  /**
   * Constructs a CreateAboutBodyForm object.
   *
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   The factory for configuration objects.
   */
  public function __construct(ConfigFactoryInterface $config_factory) {
    parent::__construct($config_factory);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static(
      $container->get('config.factory')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'pece_about_create_about_body';
  }

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return ['pece_about.settings'];
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config('pece_about.settings');
    $form['content'] = array(
      '#type' => 'details',
      '#title' => $this->t('Content'),
      '#open' => TRUE,
    );
    $form['content']['about'] = [
      '#type' => 'text_format',
      '#title' => $this->t('About page'),
      '#attributes' => [
        'class' => ['body']
      ],
      '#default_value' => $config->get('body'),
      '#maxlength' => NULL,
    ];
    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $body = $form_state->getValue("about");
    $config = $this->configFactory->getEditable('pece_about.settings');
    $config->set('body', $body['value'])->save();

    parent::submitForm($form, $form_state);
  }

}


