<?php

namespace Drupal\pece_home\Form;

use Drupal\Core\Form\ConfirmFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Url;

/**
 * Builds the form to create PECE front page.
 *
 * @codeCoverageIgnore
 */
class CreateHomepageForm extends ConfirmFormBase
{

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'pece_home_create_home_confirm';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function getQuestion()
  {
    return $this->t('Are you sure you want to recreate %name?', ['%name' => 'PECE front page']);
  }

  /**
   * {@inheritdoc}
   */
  public function getCancelUrl()
  {
    return new Url('pece_home.admin_config_pece_home');
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
    $aliasManager = \Drupal::service('path_alias.manager');
    $file_path =  \Drupal::service('extension.path.resolver')
        ->getPath('module', 'pece_home') . '/defaults/node-page-9d1a578c-5718-4056-8fdb-cec197f3a61c.yml';

    if (!file_exists($file_path)) {
      $this->messenger()->addError(
        $this->t('Unable to create PECE front page. Base file not found.', [])
      );
      $form_state->setRedirectUrl($this->getCancelUrl());
      return;
    }
    $home_page = \Drupal::service('single_content_sync.importer')->importFromFile($file_path);
    $link = $aliasManager->getPathByAlias('/home');
    \Drupal::service('config.factory')->getEditable('system.site')
      ->set('page.front', $link)
      ->save();
    $this->messenger()->addStatus(
      $this->t('PECE front page was successfully created! <a href="@link">View home page</a>', [
        '@link' => $link,
      ])
    );
    $form_state->setRedirectUrl($this->getCancelUrl());
  }

}

