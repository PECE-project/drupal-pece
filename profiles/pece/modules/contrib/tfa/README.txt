## Two-factor Authentication (TFA) module for Drupal

TFA is a base module for providing two-factor authentication for your Drupal
site. As a base module, TFA handles all of the Drupal integration work,
providing flexible and well tested interfaces to enable seamless, and
configurable, choice of various two-factor authentication solutions like
Time-based One Time Passwords, SMS-delivered codes, fallback codes, or
integrations with third-party suppliers like Authy, Duo and others.

Read more about the features and use of TFA at its Drupal.org project page at
https://drupal.org/project/tfa

### Installation and use

TFA module can be installed like other Drupal modules by placing this directory
in the Drupal file system (for example, under sites/all/modules) and enabling on
the Drupal modules page.

TFA module does not come with any plugins of its own so refer to the project
page for contributed plugins or read the section on Plugin development.

### Configuration

TFA can be configured on your Drupal site at Administration - Configuration -
People - Two-factor Authentication. Available plugins will be listed along with
their type and configured use, if set.

Additionally, a permission is exposed to Drupal roles allowing them to skip the
TFA process -- regardless of plugins and the "require TFA" setting.

#### Default validation plugin

The plugin that will be used by default during user authentication. The plugin
must be ready for use by the authenticating account. If "Require TFA" is marked
then an account that has not setup TFA with the validation plugin will be unable
to log in.

#### Fallback plugins

With multiple validation plugins installed, TFA can be setup to handle fallback
options for a user going through the TFA process. For example, let's say a user
has setup SMS code delivery and TOTP via Google Authenticator app on their
phone. In the situation that the user has deleted the Authenticator app they
could fallback to SMS code delivery and still authenticate to the site.

### Plugin development

TFA plugins provide the form and validation handling for 2nd factor
authentication of a user. The TFA module will interrupt a successful username
and password authentication and begin the TFA process (see Configuration for
exceptions to this statement), passing off the form control and validation to
the active plugin.

#### Getting started

 * Implement hook_tfa_api() in a .module file

 * Create a class extending TfaBasePlugin and implementing one of the TFA
interfaces

 * Optionally create a second class for plugin setup implementing
TfaSetupPluginInterface

For starter or example code see the test classes at ./tests/includes/

#### Plugin interfaces, or types of plugins

TFA plugins should implement one of the following interfaces.

 * Validation (TfaValidationPluginInterface) - Validation plugins are the main
TFA plugin and are used during the authentication process to accept the 2nd
authenticating element.

 * Login (TfaLoginPluginInterface) - Login plugins are used to limit what
accounts must carry out TFA before final authentication.

 * Send (TfaSendPluginInterface) - Send plugins are used for carrying out an
action at the beginning of the TFA process. For example, a plugin that sends a
code to a user over SMS could implement this interface to generate and text the
code.

 * Setup (TfaSetupPluginInterface) - A setup plugin is used by the TfaSetup
 class for configuring a TFA plugin for an account.

#### Plugin context

A plugin is instantiated with an array of data about the occurring TFA process.
This context array must contain the following elements that should not be
modified.

 * uid - Drupal UID of user carrying out the TFA process.
 * plugins - Array of active plugins in the process, must include element
'validate' and may also include 'login' and 'fallback'.

The context array may also include any plugin-specifc elements so long as there
is no conflict with the above keys. Context can be used for temporal storage of
plugin data like codes or state but do be aware that this context may be written
to the Drupal session or form cache database tables.

#### Base methods

Plugins can implement the ready() method to determine if its ready for use with
the authenticating account. For example, if authenticating user has not setup of
a phone number for SMS delivery a SMS TFA plugin would not want to begin the TFA
process for that account and should return FALSE.

The finalize() method can be used to carry-out actions after confirming the TFA
process. For example, a SMS plugin might mark a code as having been used to
prevent a repeated attempt.

#### Cryptography

The base TFA plugin class provides encryption and decryption methods using PHP
Mcrypt. While you can use these methods for simple encryption it is recommended
that you utilize more advanced cryptography libraries with your own plugins.

Use one of the following libraries and override the TfaBasePlugin encrypt and
decrypt methods.

* Zend Framework's Zend\Crypt
* phpseclib http://phpseclib.sourceforge.net/

#### Example implementation descriptions

**How to generate and send a code to a user via SMS**

Create a plugin that implements the TfaSendPluginInterface interface and
implement the begin() method to generate a code (or use parent generate()) and
send it to the user. Use the SMS Framework or Twilio modules (for example) to
actually deliver the code over SMS.

Implement the TfaSetupPluginInterface to allow the user to
set the phone number for delivery. Separately implement hook_schema() to create
a database table for storing TFA phone numbers or use a account profile field.

**How to allow web services to authenticate while requiring TFA for regular
users**

A services authentication scheme will be affected by TFA's implementation during
hook_user_login() so create a login plugin that checks the services user and
returns TRUE for loginAllowed(). See TfaTestLogin in ./tests/includes for an
example.
