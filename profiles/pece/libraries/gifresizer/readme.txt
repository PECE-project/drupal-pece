PHP GIF Animation Resizer
(written by Taha PAKSU <tpaksu (at) gmail (dot) com>)

.:: INTRODUCTION ::.

This class resizes GIF Animations by parsing the GIF animation into seperate
GIF Images and combining them after desired resize operation. It's written because
there is not so many sources about this operation and PHP's GD library didn't 
support it, ImageMagick succeeds it with some executable file etc.


.:: DEPENDENCIES ::.

- PHP 5 or higher
- GD Image Library


.:: FEATURES ::.

- Light and easy to use
- Needs a temp directory for frames
- Delay Timings and Disposal Methods stay the same
- Minimum diffusion
- Tested with several GIF animations

.:: EXAMPLES ::.

See the attached examples files for more information.

Just download the whole package and extract it into a web directory.
After that, just call test.php script within you browser and have fun.

.:: DOCUMENTATION ::.

Code is partly explained in the class file. But there are some points to look first:

1. You need to create a folder and make it writeable (CHMOD 777) and set the 
$class->temp_dir variable to point that folder. Because it needs a folder to extract
the frames.

2. The paths should be relative and existing. You should define the new file path with an
existing and writeable folder.

3. This class has only one function and it is $class->resize(). It's used like this : 

	include_once "gifresizer.php";
	$gr = new gifresizer;
	$gr->temp_dir = "frames"; //note that it doesn't end with a "/"
	$gr->resize("gif/1.gif","resized/1.gif",200,300);

	// $gr->resize({file to be resized}, {new file to be created}, {new width}, {new height});

and that's all. 

.:: SUPPORT ::.

If you made efforts to add features, bugfixes, complain about the
uselessness of this class, or you simply want to leave a personal comment, 
you are welcome to write me, and explain what you have done and why.