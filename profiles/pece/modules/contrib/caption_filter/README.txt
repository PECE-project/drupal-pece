Caption Filter is a module that converts WordPress-style [caption] tags into
HTML markup. It also allows floating images left or right in a way that avoids
allowing users access to "style" attributes, moving both the image and the
caption at the same time.

Installation
------------

1. Enable the module on the modules page.

2. Go to the admin/config/content/formats page and enable the "Caption filter"
   to the text format(s) that should be allowed to use this filter.

3. IMPORTANT: After enabling the fitler, check the "Filter processing order"
   section within the input format configuration. Make sure that the "Caption
   filter" is run AFTER the "HTML filter" (if enabled). Generally having the
   Caption filter as the last filter run will be appropriate.

Usage
-----

While entering content, choose an input format that utilizes the caption filter.
In a plain textarea, the entered code should look like this:

A simple caption:
[caption caption="This is an image caption"]<img src="" alt="" />[/caption]

Aligned Caption (can be left, center or right):
[caption caption="This is a right aligned caption" align="right"]<img src="" alt="" />[/caption]
