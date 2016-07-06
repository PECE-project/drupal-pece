<?php

/**
 * @file
 * TimestampHelper class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Conversion;

use Drupal\node_expire\Module\CommonExpire\Exception\ExpireException;

/**
 * TimestampHelper class.
 */
class TimestampHelper {

  /**
   * Converts timestamp to string.
   */
  public static function timestampToString($format, $timestamp) {
    $dt = new \DateTime();
    $dt->setTimestamp($timestamp);
    $str = $dt->format($format);
    if (!$str) {
      throw new ExpireException(t('Wrong timestamp or format.'));
    }
    return $str;
  }

  /**
   * Converts string to timestamp.
   */
  public static function stringToTimestamp($format, $str) {
    $dt = \DateTime::createFromFormat('!' . $format, $str);
    if (!$dt) {
      throw new ExpireException(t('Wrong datetime string.'));
    }
    $timestamp = $dt->getTimestamp();
    return $timestamp;
  }

  /**
   * Converts string interval to timestamp.
   */
  public static function stringIntervalToTimestamp($str_interval) {
    $dt = new \DateTime();
    $dt->setTimestamp(REQUEST_TIME);
    $dt->modify($str_interval);
    $timestamp = $dt->getTimestamp();
    return $timestamp;
  }

  /**
   * Converts timestamp to DateTime.
   */
  public static function timestampToDateTime($timestamp) {
    $dt = new \DateTime();
    $dt->setTimestamp($timestamp);
    return $dt;
  }

  /**
   * Check is the string an interval.
   */
  public static function isInterval($str) {

    $str1 = trim($str);

    if (empty($str1)) {
      return FALSE;
    }

    $str2 = substr($str1, 0, 1);
    if (($str2 == '+') || ($str2 == '-')) {
      // Continue.
    }
    else {
      return FALSE;
    }

    // Try if string is an interval.
    $dt = new \DateTime();
    $dt->modify($str1);
    if (!$dt) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * Checks timestamp to be valid.
   */
  public static function isValidTimestamp($timestamp) {
    return ((string) (int) $timestamp === $timestamp)
    && ($timestamp <= PHP_INT_MAX)
    && ($timestamp >= ~PHP_INT_MAX);
  }

  /**
   * Adds string interval to timestamp.
   */
  public static function addInterval($interval, $timestamp) {
    $dt = new \DateTime('@' . $timestamp);
    $dt->modify($interval);
    $ts = $dt->getTimestamp();
    return $ts;
  }

  /**
   * Subtarcts string interval to timestamp.
   */
  public static function subtractInterval($interval, $timestamp) {
    $dt = new \DateTime('@' . $timestamp);
    $dt->sub(\DateInterval::createFromDateString($interval));
    $ts = $dt->getTimestamp();
    return $ts;
  }

  /**
   * Converts string interval to timestamp.
   */
  public static function stringIntervalToTimestampOld($str_interval) {
    $timestamp = strtotime($str_interval, REQUEST_TIME);;
    return $timestamp;
  }

  /**
   * Converts timestamp to string.
   */
  public static function timestampToStringOld($format, $timestamp) {
    $dt = new \DateTime('@' . $timestamp);
    $str = $dt->format($format);
    return $str;
  }

  /**
   * Converts string to timestamp.
   */
  public static function stringToTimestampOld($format, $str) {
    $dt = \DateTime::createFromFormat('!' . $format, $str);
    $timestamp = $dt->getTimestamp();
    return $timestamp;
  }

}
