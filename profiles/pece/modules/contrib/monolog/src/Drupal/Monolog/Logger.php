<?php

/**
 * Monolog extension for use with Drupal.
 */

namespace Drupal\Monolog;

use Monolog\Logger as BaseLogger;

/**
 * Logger class for the Drupal Monolog module.
 *
 * Allows the channel to be modified after the class is instantiated. This is
 * normally not a good idea, but it is necessary to reconcile the differences in
 * the Monolog library and how the watchdog type relates to the logging
 * facility.
 */
class Logger extends BaseLogger
{
    /**
     * Sets the channel name.
     *
     * @param string $name
     *   The logging channel.
     */
    public function setName($name)
    {
        $this->name = $name;
    }
}
