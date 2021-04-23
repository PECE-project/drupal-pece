Matomo Noscript
===============

Some sites have a strict privacy policy which prohibits tracking of browser
metadata tracked by the Matomo JavaScript client (piwik.js).

In addition, some sites have a significant user base using noscript and other
browser extensions which limit ability to execute JavaScript.

This module uses an alternative syntax to setup Matomo tracking code via an
image tag rather than loading piwik.js.

This module adds a noscript tag containing the Matomo image tag to the bottom of
every page.

In addition, if Matomo module is not enabled, this module also adds an image tag
with some JavaScript to track the referrer URL.

To use this module you'll need to configure your Matomo settings by either
installing and configuring the Drupal Matomo module, or by adding these lines to
your settings.php file:

$conf['matomo_site_id'] = 1;
$conf['matomo_url_https'] = 'https://matomo.example.org/';
