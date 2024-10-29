<!-- HTML/PHP code for RGB_LED project -->
<!DOCTYPE html>
<html>
    <head></head>
    <body>
        <!-- Adding headers to the web page -->
        <h1 style="color:green;">IoT Course</h1>
        <h3>Adjust the sliders and submit the values</h3>
        <!-- Posts to the same page -->
        <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']);?>"> 
            
        <!-- Slider 1: Control from 0 to 255 -->
        <label for="slider1">Red Slider (0-255): </label>
        <input type="range" id="slider1" name="slider1" min="0" max="255" value="0"
        oninput="this.nextElementSibling.value = this.value">
        <output>0</output>
        <p></p>
        
        <!-- Slider 2: Control from 0 to 255 -->
        <label for="slider2">Green Slider (0-255): </label>
        <input type="range" id="slider2" name="slider2" min="0" max="255" value="0"
        oninput="this.nextElementSibling.value = this.value">
        <output>0</output>
        <p></p>
        
        <!-- Slider 3: Control from 0 to 255 -->
        <label for="slider3">Blue Slider (0-255): </label>
        <input type="range" id="slider3" name="slider3" min="0" max="255" value="0"
        oninput="this.nextElementSibling.value = this.value">
        <output>0</output>
        <p></p>
        
        <!-- Submit button -->
        <input type="submit" value="Submit Values">
        </form>
    <?php
        // Obtaining values from sliders if form has been submitted
        if ($_SERVER["REQUEST_METHOD"] == "POST"){
            $red = isset($_POST["slider1"]) ? $_POST["slider1"] : 0;
            $green = isset($_POST["slider2"]) ? $_POST["slider2"] : 0;
            $blue = isset($_POST["slider3"]) ? $_POST["slider3"] : 0;
        
        // Outputting values on same web page
            echo "Red value: " . $red . "<br>";
            echo "Green value: " . $green . "<br>";
            echo "Blue value: " . $blue . "<br>";
        
        // Writing values to a file
            $myfile = fopen("tp2.txt", "w") or die("Unable to open file!");
            fwrite($myfile, "Red: $red\n");
            fwrite($myfile, "Green: $green\n");
            fwrite($myfile, "Blue: $blue\n");
            fclose($myfile);
        }
    ?>
    </body>
</html>
