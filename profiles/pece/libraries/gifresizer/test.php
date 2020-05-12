<?php 
require_once "gifresizer.php";	//Including our class
$gr = new gifresizer;	//New Instance Of GIFResizer
$gr->temp_dir = "frames"; //Used for extracting GIF Animation Frames
$gr->resize("gifs/1.gif","resized/1_resized.gif",200,150); //Resizing the animation into a new file.
?>