<?php

/**
 * @file
 * Defines Key-specific exceptions.
 */

/**
 * Defines a generic exception for Key.
 */
class KeyException extends Exception {}

/**
 * Defines an exception for when a key value fails to be set.
 */
class KeyValueNotSetException extends KeyException {}

/**
 * Defines an exception for when a key value fails to be retrieved.
 */
class KeyValueNotRetrievedException extends KeyException {}

/**
 * Defines an exception for when a key value fails to be deleted.
 */
class KeyValueNotDeletedException extends KeyException {}
