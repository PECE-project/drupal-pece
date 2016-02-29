#!/bin/bash

# Please note that this file is here only to help with debugging.
# In a working environment there is no need to create two new files per every
# email recieved. If done with debugging please use
# og_mailinglist_postfix_transport.php directly.

# Write message to file
cat >/tmp/message.$$

# Read message from file, pass it to PHP and write output to log file.
(cat /tmp/message.$$ | \
  /etc/postfix/postfix_og_mailinglist/og_mailinglist_postfix_transport.php $1 > \
  /tmp/message.$$.log 2>&1 )

# Show log file for easier debugging.
cat /tmp/message.$$.log

