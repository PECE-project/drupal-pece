<?php
/**
 * @file
 * Iframe for displaying cached content
 */
?><!DOCTYPE html>
<html style="height: 100%">
<head>
<title>Amber</title>
</head>
<body style="margin:0; padding: 0; height: 100%">
<iframe
sandbox="allow-scripts allow-forms allow-popups allow-pointer-lock"
security="restricted"
style="border:0 none transparent; background-color:transparent; width:100%; height:100%;"
src="<?php print $url; ?>"></iframe>
</body>
</html>
