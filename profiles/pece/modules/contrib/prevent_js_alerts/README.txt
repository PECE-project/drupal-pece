Description
----------------------------
This module is an answer to the issue: #1232416: Drupal alerts "An AJAX HTTP request terminated abnormally" during normal site operation, confusing site visitors/editors, which describes a big problem for end users: JavaScript alert();'s for end users on AJAX Errors by Drupal core. Perhaps it will one day become obsolete, when this bug is fixed.
End users are often frightened of these errors and don't know, if they have "destroyed the internet" ;)

This module completely suppresses ALL JavaScript alerts and instead prints them to console via console.error!
Important: It does NOT ONLY suppress the core alerts, but also custom alerts.
=============================

Dependencies:
-----------------------------
    - none
=============================


Installation:
-----------------------------
    Download and enable this module
    Done! Happy Using! Alerts should be gone now!
    Visit our websites and hire us ;)
=============================

Development proudly sponsored by:
-----------------------------
webks: websolutions kept simple (http://www.webks.de)
and
DROWL: Drupalbasierte Lösungen aus Ostwestfalen-Lippe (http://www.DROWL.de)
