This project provides animated GIF resize and scale support for image styles with GD.

It uses a library written by Taha Paksu (<a href="http://www.phpclasses.org/package/7353-PHP-Resize-animations-in-files-of-the-GIF-format.html">GIF Animation Resizer</a>).

Installation:

* download the library above and extract to the libraries/gifresizer folder.(libraries/gifresizer/gifresizer.php)

* apply the patch from the animgif_support/patch to the lirbaries/firresizer/gifresizer.php
(eg: patch -p1 < ../../modules/contrib/animgif_support/patch/gifresizer-patch01.php)

* It can be, you can not able to patch the gifresizer.php file, then change:
  - first line to <?php
  - in the line 69, replace the $this->writeframes(time()); with this->writeframes(md5($filename));
  - remove the closing ?> line

* enable this module

That's it.

This module supports only "resize" and "scale". However, "resize" is quite useless for animated GIFs. The actions "crop" and "scale and crop" will both do resize only since the used lib does not support crop.

Caveats: It can happen that the generated image does not appear for the first time. Just reload the page if this happens.

Development supported by <a href="http://mediabistro.com">mediabistro</a>.
