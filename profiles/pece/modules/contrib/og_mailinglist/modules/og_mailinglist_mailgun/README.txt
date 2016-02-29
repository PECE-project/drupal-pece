This modules provides integration with the commercial email API service,
Mailgun. Using Mailgun is by far the easiest way to get up and running
with OG Mailinglist and perfect for those who'd like to use OG
Mailinglist but don't have a server that it supports or don't have the
technical wherewithal to perform the complicated steps needed to setup a
server for OG Mailinglist.

To use, enable this module. Then signup for an account at
http://mailgun.net and create a domain for your site. You can either use
a free mailgun.net domain or setup the MX DNS record for your site to
point at mailgun.net. See
http://documentation.mailgun.net/user_manual.html#configuring-a-domain
for more on that.

Next you'll need to setup a route on mailgun.net. Mailgun provides a
wide variety of options for setting up custom routing of incoming emails
depending on your needs. If you need additional flexibility, read Mailgun's
documentation at
http://documentation.mailgun.net/user_manual.html#routes

But generally, you will want to setup a catchall router which forwards
all emails sent to your domain to your Drupal site. To do so, click
"Create route", then set the "Filter Expression" to "catch_all()". Then
set "Actions" to
"forward('http://BASE_URL_OF_YOUR_DRUPAL_SITE/og_mailinglist/mailgun_callback_mime')"

Once you have a domain setup, goto
example.com/admin/config/group/mailinglist/mailgun and copy/paste your
domain's Login/Password information as well as your API Key.

The last step is to go to admin/config/group/mailinglist and set the Domain
Name there to match the domain you setup at mailgun.net.
