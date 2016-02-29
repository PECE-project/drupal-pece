OG_mailinglist - Turns Drupal into a multi-group email list.


OG_Mailinglist allows users to start new posts by email and post comments on
existing posts by simply replying to emails.  You get the best of both worlds: a
browser-based discussion site and an email-based list.

See the INSTALL.TXT file for system requirements and prerequisites.


EXAMPLE:

Suppose you have implemented Organic Groups and have three topical groups: "Web
Programming", "Technical Help", and "Politics".  Users normally go to the group
page and click "Create Story" to start a discussion.  With this module, a user
simply emails "web-programming@example.com" to start a new discussion.  The
subject becomes the story title, and the body becomes the story body.

Using the regular Drupal notifications framework, all users in the group get an
email telling them of the new post.  These users would normally click the link
to make comments.  With this module, a user wanting to post a comment simply
hits Reply and sends his or her comment.  The reply mail also goes to the
"web-programming@example.com" address.

In many ways, your Drupal site becomes a mailing list manager.  Users never have
to visit the site to start or participate in discussions.  The module
automatically detects new or deleted groups and is always up to date.


SECURITY:

This module essentially allows group members to post to your site directly from
their email box -- it bypasses their login name and password and simply matches
the email address.  This can be spoofed by anyone smart enough to do it.  The
module has some security in place, but by its very nature, it is a potential
security risk.  Use this module only on sites where this is acceptable.


CREDITS:

Thanks to the mail_comment module for the inspiration for some of the code in
this module.
