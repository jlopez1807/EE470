<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <h1>ThingSpeak Lab</h1>

    <!-- Using CSS to style HTML page -->
    <style>
        body {
            background-color: green;
            color: purple;
            font-family: Arial, sans-serif;
            text-align: center;
        }

        .container {
            display: flex;
            flex-wrap: wrap;
            justify-content: space-around;
            gap: 20px;
            padding: 20px;
        }

        iframe {
            border: 1px solid #cccccc;
            width: 500px;
            height: 300px;
        }

        h2 {
            margin-bottom: 10px;
        }

        /* Style for the button */
        .control-btn {
            background-color: #4CAF50; /* Green */
            border: none;
            color: white;
            padding: 15px 32px;
            text-align: center;
            font-size: 16px;
            cursor: pointer;
            margin-top: 20px;
            border-radius: 8px;
        }

        .control-btn:hover {
            background-color: #45a049; /* Darker green on hover */
        }
    </style>
</head>

<body>

    <!-- Button to send "ON" command -->
    <h2>Control LED1</h2>
    <form action="https://api.thingspeak.com/talkbacks/53601/commands.json" method="post" target="invisible">
        <input type="hidden" name="api_key" value="1HKXUO4N68F0HLXC"> 
        <input type="hidden" name="command_string" value="ON">
        <button class="control-btn" type="submit">Turn LED1 ON</button>
    </form>

    <!-- Button to send "OFF" command -->
    <form action="https://api.thingspeak.com/talkbacks/53601/commands.json" method="post" target="invisible">
        <input type="hidden" name="api_key" value="1HKXUO4N68F0HLXC"> 
        <input type="hidden" name="command_string" value="OFF">
        <button class="control-btn" type="submit">Turn LED1 OFF</button>
    </form>

    <!-- Adding graphs from ThingSpeak -->
    <div class="container">
        <div>
            <h2>CPU Temperature</h2>
            <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2749096/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=CPU+Temperature&type=line&xaxis=Time+and+Date&yaxis=CPU+Temp+%28deg+Celcius%29"></iframe>
        </div>

        <div>
            <h2>CPU Usage</h2>
            <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2749096/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=CPU+Usage&type=line&xaxis=Time+and+Date&yaxis=Usage+%28%25%29"></iframe>
        </div>

        <div>
            <h2>Average CPU Temperature</h2>
            <iframe src="https://thingspeak.com/channels/2749096/widgets/972854"></iframe>
        </div>

        <div>
            <h2>Power versus Time</h2>
            <iframe src="https://thingspeak.com/apps/matlab_visualizations/591309"></iframe>
        </div>
    </div>
</body>

</html>
