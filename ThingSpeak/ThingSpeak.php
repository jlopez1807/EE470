<!DOCTYPE html>
<html lang="en">
    
<!-- Using HTML to add content to webpage -->
<head>
<meta charset="utf-8">
<h1>ThingSpeak Lab</h1>
<!-- Using CSS to style HTML page -->
<style>
body{
background-color:green;
color:Purple
}
</style>
</head>

<!-- Embedding a video on webpage -->
<p>
    <h2>CPU Temperature</h2>
<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2749096/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
</p>
<p>
    <h2>CPU Usage</h2>
<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2749096/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=CPU+Usage&type=line"></iframe>
</p>
<p>
    <h2>Average CPU Temperature</h2>
<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2749096/widgets/972854"></iframe>
</p>
<p>
    <h2>Power versus Time</h2>
<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/apps/matlab_visualizations/591309"></iframe>
</p>
</body>
</html>
