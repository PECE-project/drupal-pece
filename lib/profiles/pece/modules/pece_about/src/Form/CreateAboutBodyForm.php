<?php

namespace Drupal\pece_about\Form;

use Drupal\Core\Form\ConfirmFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Url;
use Exception;

/**
 * Builds the form to create About.
 *
 * @codeCoverageIgnore
 */
class CreateAboutBodyForm extends ConfirmFormBase
{

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'pece_about_create_about_body_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $form['body'] = [
      '#type' => 'text_format',
      '#attributes' => [
        'class' => ['body']
      ]
    ];
    
    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function getQuestion()
  {
    return $this->t('Enter the content for your about page:');
  }

  /**
   * {@inheritdoc}
   */
  public function getCancelUrl()
  {
    return new Url('pece_about.admin_config_pece_about');
  }

  /**
   * {@inheritdoc}
   */
  public function getConfirmText()
  {
    return $this->t('Create');
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state)
  {
    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state)
  {
    $body = $form_state->getValue("body");
    $config = \Drupal::service('config.factory')->getEditable('about.settings');
    $config->set('body', $body['value'])->save();
    $this->messenger()->addMessage($this->t('The about text has been saved.', []));
  }

}


