<?php

/**
 * @file
 * TimestampUtils class.
 */

namespace Drupal\node_expire\Module\Utils;

use Drupal\node_expire\Module\CommonExpire\Conversion\TimestampHelper;
use Drupal\node_expire\Module\CommonExpire\Exception\ExpireException;
use Drupal\node_expire\Module\Config\ConfigHandler;

/**
 * TimestampUtils class.
 */
class TimestampUtils {

  /**
   * Convert date string to timestamp int.
   *
   * @param string $date_in
   *   String date representation for UI:
   *   not set, non-date string, date string.
   * @param object $ntype
   *   Node expire configuration for particular node type.
   *
   * @return int
   *   Timestamp (int) date representation for DB:
   *   timestamp int, NODE_EXPIRE_NO_EXPIRE as a special value.
   */
  public static function dateStrToDb($date_in, $ntype) {
    if (!isset($date_in)) {
      $date_out = NODE_EXPIRE_NO_EXPIRE;
      return $date_out;
    }

    $date_inner = trim($date_in);
    $date_out = self::strToTimestamp($date_inner);

    return $date_out;
  }

  /**
   * Convert timestamp int to date string.
   *
   * @param int $date_in
   *   Timestamp (int) date representation for DB:
   *   not set, timestamp int.
   * @param object $ntype
   *   Node expire configuration for particular node type.
   *
   * @return string
   *   String date representation for UI:
   *   date string or ''.
   */
  public static function dateDbToStr($date_in, $ntype) {
    $date_inner = $date_in;
    if ((empty($date_inner)) ||
      (!(TimestampHelper::isValidTimestamp($date_inner)))) {
      if (isset($ntype) && !empty($ntype['default'])) {
        $default = $ntype['default'];
        $date_out = self::dateStrFromCfgDefault($default, FALSE);
      }
      else {
        $date_out = '';
      }
    }
    elseif ($date_inner >= NODE_EXPIRE_NO_EXPIRE) {
      $date_out = '';
    }
    else {
      // $date_out = date(ConfigHandler::getDateFormat(), $date_inner);
      $date_out = self::timestampToStr($date_inner);
    }
    return $date_out;
  }

  /**
   * Makes date string from default config value for node type.
   *
   * If used for Node Type, interval string is accepted as output and
   * $return_intervals = TRUE.
   *
   * If used for Node, interval string is converted to real DateTime string and
   * $return_intervals = FALSE.
   *
   * NODE_EXPIRE_NO_EXPIRE and '' are used as special values.
   * Intervals are accepted as well.
   */
  public static function dateStrFromCfgDefault($default, $return_intervals = TRUE) {
    if (!isset($default)) {
      $date_out = '';
      return $date_out;
    }

    $default1 = trim($default);
    if (empty($default1)) {
      $date_out = '';
    }
    elseif (TimestampHelper::isInterval($default)) {
      if ($return_intervals) {
        // Return as interval string - for Node Type.
        $date_out = $default;
      }
      else {
        // Convert to DateTime string - for Node.
        $timestamp = TimestampHelper::stringIntervalToTimestamp($default);
        $date_out = self::timestampToStr($timestamp);
      }
    }
    elseif (is_int($default)) {
      // It is timestamp, handle it.
      $date_out = self::timestampToStr($default);
    }
    else {
      // Maybe legacy string from old version.
      try {
        $format = 'Y-m-d';
        $timestamp = TimestampHelper::stringToTimestamp($format, $default);
        $date_out = self::timestampToStr($timestamp);
      }
      catch (\Exception $e) {
        $date_out = '';
      }
    }

    return $date_out;
  }

  /**
   * Converts date string to timestamp int.
   *
   * NODE_EXPIRE_NO_EXPIRE and '' are used as special values.
   * Intervals are accepted as well.
   */
  public static function dateStrToCfgDefault($date_in) {
    if (!isset($date_in)) {
      $date_out = '';
      return $date_out;
    }

    $date_inner = trim($date_in);
    if (empty($date_inner)) {
      $date_out = '';
      return $date_out;
    }
    elseif (TimestampHelper::isInterval($date_inner)) {
      return $date_inner;
    }

    // Try to handle as timestamp.
    try {
      $format = ConfigHandler::getDateFormat();
      $timestamp = TimestampHelper::stringToTimestamp($format, $date_inner);
      return $timestamp;
    }
    catch (\Exception $e) {
      $date_out = '';
      return $date_out;
    }

  }

  /**
   * Converts date string to timestamp int.
   *
   * NODE_EXPIRE_NO_EXPIRE and '' are used as special values.
   */
  public static function strToTimestamp($date_in) {
    // Can be placed into exception. Leaved here for faster execution.
    if (!isset($date_in)) {
      $timestamp = NODE_EXPIRE_NO_EXPIRE;
      return $timestamp;
    }

    $date_inner = trim($date_in);
    try {
      $format = ConfigHandler::getDateFormat();
      $timestamp = TimestampHelper::stringToTimestamp($format, $date_inner);
    }
    catch (\Exception $e) {
      $timestamp = NODE_EXPIRE_NO_EXPIRE;
    }

    return $timestamp;
  }

  /**
   * Converts string to timestamp with interval option checking.
   */
  private static function stringToTimestampAdvConfig($format, $str) {
    $dt = \DateTime::createFromFormat('!' . $format, $str);
    if (!$dt) {
      // Try if string is an interval.
      $dt = new \DateTime();
      $dt->modify($str);
      if (!$dt) {
        throw new ExpireException(t('Wrong datetime/interval string.'));
      }
      else {
        return $str;
      }
    }
    $timestamp = $dt->getTimestamp();
    return $timestamp;
  }

  /**
   * Converts string to timestamp with interval option checking.
   */
  public static function stringToTimestampAdv($format, $str) {
    $dt = \DateTime::createFromFormat('!' . $format, $str);
    if (!$dt) {
      // Try if string is an interval.
      $dt = new \DateTime();
      $dt->modify($str);
      if (!$dt) {
        throw new ExpireException(t('Wrong datetime/interval string.'));
      }
    }
    $timestamp = $dt->getTimestamp();
    return $timestamp;
  }

  /**
   * Converts timestamp int to date string.
   *
   * NODE_EXPIRE_NO_EXPIRE and '' are used as special values.
   */
  public static function timestampToStr($date_in) {
    $date_inner = $date_in;
    if (empty($date_inner)) {
      $str = '';
    }
    elseif ($date_inner >= NODE_EXPIRE_NO_EXPIRE) {
      $str = '';
    }
    else {
      try {
        $format = ConfigHandler::getDateFormat();
        $str = TimestampHelper::timestampToString($format, $date_inner);
      }
      catch (\Exception $e) {
        $str = '';
      }
    }
    return $str;
  }

}
