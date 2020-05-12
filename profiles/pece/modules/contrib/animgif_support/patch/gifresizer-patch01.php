diff --git a/gifresizer.php b/gifresizer.php
index 78e1619..79098b0 100644
--- a/gifresizer.php
+++ b/gifresizer.php
@@ -1,4 +1,5 @@
-<? 
+<?php
+
     /** 
     * Resizes Animated GIF Files
     *
@@ -65,7 +66,7 @@
                 $this->get_graphics_extension(2);
                 $this->get_image_block(2);
             }
-            $this->writeframes(time());		
+            $this->writeframes(md5($filename));
             $this->closefile();
             $this->decoding = false;
         }
@@ -514,4 +515,4 @@
     }
 
 
-?>
\ No newline at end of file
+
