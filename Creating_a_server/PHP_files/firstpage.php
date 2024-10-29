<!DOCTYPE html>
<html lang="en">
    
<!-- Using HTML to add content to webpage -->
<head>
<title>Hot Cocoa </title>
<meta charset="utf-8">

<!-- Using CSS to style HTML page -->
<style>
body{
background-color:green;
color:yellow
}
</style>
</head>

<!-- Using HTML to add header and list content to webpage -->
<h1>Hot Cocoa Varieties</h1>
<ul>
<li>Mayan Cocoa</li>
<li>Coconut Chai Cocoa</li>
</ul>

<!-- Using PHP to add content to webpage -->
<p>
<?php
echo "Hello World!";
$txt = "Learn PHP";
$txt2 = "Engineering @ SSU";
$x = 5;
$y = 4; 
echo "<h2>" . $txt . "</h2>";
echo "Study PHP at $txt2<br>";
echo "The sum of X and Y is: " . ($x + $y);
?>
</p>

<!-- Embedding an image on webpage -->
<p>
<img src="https://seeklogo.com/images/S/sonoma-state-university-ssu-logo-22E39E4817-seeklogo.com.png">
</p>

<!-- Embedding a video on webpage -->
<p>
<iframe width="560" height="315"
src="https://www.youtube.com/embed/lwLLFbC1H0c" frameborder=
"0" allow="accelerometer; autoplay; encrypted-media; gyroscope;
picture-inpicture"
allowfullscreen></iframe>
</p>

</body>
</html>
