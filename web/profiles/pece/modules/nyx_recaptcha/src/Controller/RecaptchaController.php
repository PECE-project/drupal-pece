<?php

namespace Drupal\nyx_recaptcha\Controller;

use Exception;
use Drupal\Core\Controller\ControllerBase;
use Symfony\Component\HttpFoundation\Response;

/**
 * Controller for Google Recaptcha.
 *
 * @codeCoverageIgnore
 */
class RecaptchaController extends ControllerBase {
  /**
   * Receive and verify response recaptcha token
   * @param $token
   */
  public function verify($token) {
    $response = new Response();
    $errorName = 'error-codes';
    if (isset($token)) {
        try {
            $recaptcha_url = 'https://www.google.com/recaptcha/api/siteverify';
            $recaptcha_secret = getenv('NYX_RECAPTCHA');
            $recaptcha_response = $token;
    
            $recaptcha = file_get_contents($recaptcha_url . '?secret=' . $recaptcha_secret . '&response=' . $recaptcha_response);
            $recaptcha = json_decode($recaptcha);
            
            if (isset($recaptcha->$errorName)) {
                throw new Exception($recaptcha->$errorName[0]);
            }

            if ($recaptcha->score >= 0.5) {
                $response->setContent(json_encode(['message' => 'success']));
                $response->setStatusCode(200);
            } else {
                throw new Exception('Low score');
            }
            
        } catch (Exception $e) {
            $response->setContent(json_encode(['message' => $e->getMessage()]));
            $response->setStatusCode(403);
        }
        return $response;
    }
    $response->setContent(json_encode(['message' => 'Token not informed']));
    $response->setStatusCode(400);
    return $response;
  }
}
