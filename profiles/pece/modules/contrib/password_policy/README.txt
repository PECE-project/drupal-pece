INTRODUCTION
------------

This module provides a way to enforce restrictions on user passwords by
defining password policies.

A password policy can be defined with a set of constraints which must be met
before a user password change will be accepted. Each constraint has a parameter
allowing for the minimum number of valid conditions which must be met before
the constraint is satisfied.

Example: An uppercase constraint (with a parameter of 2) and a digit constraint
(with a parameter of 4) means that a user password must have at least 2
uppercase letters and at least 4 digits for it to be accepted.

Current constraints include:

 * Digit
 * Letter
 * Letter/Digit (Alphanumeric)
 * Length
 * Uppercase
 * Lowercase
 * Punctuation
 * Character types (Allows the administrator to set the minimum number of
   character types required, but without dictating which ones must be used.)
 * History (Ensures password does not match a specified number of the user's
   previous passwords.)
 * Username

The module also implements configurable password expiration features:

 * When a password is not changed for a certain amount of time the user will
   be forced to change their password on next login.
 * Optionally, the user will also be blocked upon password expiration.
 * Expiration of passwords can begin after expiration time from enabling
   the policy or immediately all users with passwords older than expiration
   time will be blocked (retroactive behavior).
 * Expiration notifications (warnings) are mailed to the users several times
   (configurable) before the password expires.
 * Warning e-mail message's subject and body are configurable.


REQUIREMENTS
------------

No special requirements.


INSTALLATION
------------

Install as you would normally install a contributed Drupal module. See
https://drupal.org/documentation/install/modules-themes/modules-7
for further information.


CONFIGURATION
-------------

* Configure password policies and general settings at Administration »
  Configuration » People » Password policies:

   - Settings

     Configure behaviors of the module that will apply to all password
     policies.

   - List

     Manage existing password policies.

   - Add

     Add a new password policy.

   - Force Password Change

     Force groups of users to change their passwords.


LIMITATIONS
-----------

 * Password policies only apply to passwords set via user forms in the web
   interface. Passwords changed by other means (Drush, web services, etc.) will
   not be subject to password policy constraints. Please see the following issue
   if you would like to contribute to removing this limitation:
     https://www.drupal.org/node/2451159

 * Password policies alone cannot ensure secure password practices. A
   password policy can help prevent a user from choosing a weak password that
   is susceptible to password guessing. However, an overly restrictive password
   policy could promote insecure password practices such as writing a password
   down in an insecure location, or devising an obvious password only to meet
   the constraints (e.g., Abc123!).

   Consider encouraging (or requiring as an organizational policy) users to use
   a password manager to generate and store strong, per-site passwords:
     https://en.wikipedia.org/wiki/List_of_password_managers


CREDITS
-------
Drupal 4.7 version was written by David Ayre <drupal at ayre dot ca>
Refactored and maintained by Miglius Alaburda <miglius at gmail dot com>
Sponsored by Bryght, SPAWAR, McDean, Classic Graphics, Acquia
