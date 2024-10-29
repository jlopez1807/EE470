<?php
// Connecting to my database
$servername = "localhost";
$username = "u326197708_db_jessielopez";
$password = "";
$dbname = "u326197708_jessielopez";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// If node_name was not provided in the GET request, check the POST request
if (empty($node_name) && isset($_POST['node_name'])) {
    $node_name = $_POST['node_name'];
}

// If still not set, default to 'node-1'
if (empty($node_name)) {
    $node_name = 'node-1';
}

// Query to obtain data from sensor_register table in database
$register_query = "SELECT * FROM sensor_register";
$register_result = $conn->query($register_query);

// Query to obtain data from sensor_data table in database
$data_query = "SELECT * FROM sensor_data";
$data_result = $conn->query($data_query);

// Query to find average temp and humidity for node-1
$average_query = "SELECT AVG(temperature) AS avg_temp, AVG(humidity) AS avg_humidity FROM sensor_data WHERE node_name = 'node-1'";
$average_result = $conn->query($average_query);
$avg_temp = 0;
$avg_humidity = 0;

// If the query returns a result, fetch the average values
if ($average_result->num_rows > 0) {
    $row = $average_result->fetch_assoc();
    $avg_temp = $row['avg_temp'];
    $avg_humidity = $row['avg_humidity'];
}
// Query to get data for the specified node for charting
$chart_query = "SELECT * FROM sensor_data WHERE node_name = '$node_name'";
$chart_result = $conn->query($chart_query);
$time_data = [];
$temperature_data = [];

// If the chart query returns results, fetch the time and temperature data
if ($chart_result->num_rows > 0) {
    while ($row = $chart_result->fetch_assoc()) {
        $time_data[] = $row['time_received'];
        $temperature_data[] = $row['temperature'];
    }
}

// Uses URL to send values to my database/webpage
if (isset($_GET['nodeId']) && isset($_GET['nodeTemp']) && isset($_GET['nodeHum'])) {
    $nodeId = $_GET['nodeId'];
    $nodeTemp = $_GET['nodeTemp'];
    $nodeHum = $_GET['nodeHum'];

    // Check if the time_received is provided in the URL
    if (isset($_GET['time_received'])) {
        $time_received = $_GET['time_received'];
    } else {
        // If not provided, use the current time
        $time_received = date('Y-m-d H:i:s');
    }

    // Check if the nodeId is registered
    $check_node_query = "SELECT * FROM sensor_register WHERE node_name = '$nodeId'";
    $check_node_result = $conn->query($check_node_query);

    // If node is registered, proceed to insert the data into the sensor_data table
    if ($check_node_result->num_rows > 0) {
        // Insert data into the sensor_data table
        $insert_query = "INSERT INTO sensor_data (node_name, time_received, temperature, humidity) VALUES ('$nodeId', '$time_received', '$nodeTemp', '$nodeHum')";
        if ($conn->query($insert_query) === TRUE) {
            echo "Data inserted successfully for node $nodeId with temperature $nodeTemp.";
        } else {
            echo "Error: " . $conn->error;
        }
    } else {
        // If the node is not registered, show an error message
        echo "Error: Node $nodeId is not registered, no data received.";
    }
 }
?>

<html>
<head>
   /* Styling for the tables and headings */
    <style>
        table { width: 50%; border-collapse: collapse; margin: 20px 0; }
        table, th, td { border: 1px solid black; padding: 8px; text-align: center; }
        th { background-color: purple; color: white; }
        h2 { color: purple; }
        #chart-container { width: 50%; height: 500px; margin: 40px; }
        form { margin: 20px; }
        label, input, button { font-size: 24px; margin: 5px; }
    </style>
</head>
<body>
<h1>Welcome to SSU IoT Lab</h1>
<h2>Registered Sensor Nodes</h2>

<!-- Display the average temperature and humidity for node-1 -->
<table>
    <caption style="font-size: 24px; font-weight: bold;">node-1</caption>
    <tr>
        <th>Average Temperature</th>
        <th>Average Humidity</th>
    </tr>
<h2>Average Data for node-1</h2>
<td>Average Temperature: <?php echo $avg_temp; ?></td>
<td>Average Humidity: <?php echo $avg_humidity; ?></td>
</table>

<!-- Table to display registered sensor nodes -->
<table>
    <tr>
        <th>Node Name</th>
        <th>Manufacturer</th>
        <th>Longitude</th>
        <th>Latitude</th>
    </tr>
    <?php
    if ($register_result->num_rows > 0) {
        while ($row = $register_result->fetch_assoc()) {
            echo "<tr>";
            echo "<td>" . $row['node_name'] . "</td>";
            echo "<td>" . $row['manufacturer'] . "</td>";
            echo "<td>" . $row['longitude'] . "</td>";
            echo "<td>" . $row['latitude'] . "</td>";
            echo "</tr>";
        }
    }
    ?>
</table>

<!-- Table to display data received -->
<h2>Data Received</h2>
<table>
    <tr>
        <th>Node Name</th>
        <th>Time Received</th>
        <th>Temperature</th>
        <th>Humidity</th>
    </tr>
    <?php
    if ($data_result->num_rows > 0) {
        while ($row = $data_result->fetch_assoc()) {
            echo "<tr>";
            echo "<td>" . $row['node_name'] . "</td>";
            echo "<td>" . $row['time_received'] . "</td>";
            echo "<td>" . $row['temperature'] . "</td>";
            echo "<td>" . $row['humidity'] . "</td>";
            echo "</tr>";
        }
    }
    ?>
</table>

<!-- Form to input node name -->
<form method="POST" action="">
    <label for="node_name">Enter Node Name:</label>
    <input type="text" name="node_name" id="node_name" value="<?php echo htmlspecialchars($node_name); ?>" required>
    <button type="submit">Display Data</button>
</form>

<!-- Used to create chart on web page -->
<div id="chart-container">
    <canvas id="temperatureChart"></canvas>
</div>

<!-- JavaScript Libraries -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.7.1/chart.min.js"></script>

<!-- JavaScript for Chart.js -->
<script>
    $(document).ready(function() {
        // Data arrays from PHP
        const timeData = <?php echo json_encode($time_data); ?>;
        const temperatureData = <?php echo json_encode($temperature_data); ?>;

        // Create the chart
        const ctx = document.getElementById('temperatureChart').getContext('2d');
        new Chart(ctx, {
            type: 'bar',
            data: {
                labels: timeData,
                datasets: [{
                    label: 'Temperature (°F)',
                    data: temperatureData,
                    backgroundColor: 'rgba(11, 243, 38, 0.8)',
                    borderColor: 'rgba(6, 17, 3, 0.96)',
                    borderWidth: 5
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,  // Disable aspect ratio to customize dimensions
                scales: {
                    x: {
                        title: {
                            display: true,
                            text: 'Time',
                            font: {
                                size: 18 // Set the font size for X axis title
                            }
                        },
                        ticks: {
                            font: {
                                size: 14 // Set the font size for X axis labels
                            }
                        }
                    },
                    y: {
                        beginAtZero: true,
                        title: {
                            display: true,
                            text: 'Temperature (°F)',
                            font: {
                                size: 18 // Set the font size for Y axis title
                            }
                        },
                        ticks: {
                            font: {
                                size: 14 // Set the font size for Y axis labels
                            }
                        }
                    }
                },
                plugins: {
                    title: {
                        display: true,
                        text: 'Sensor ' + '<?php echo htmlspecialchars($node_name); ?>',
                        font: {
                            size: 24 // Set the font size for chart title
                        }
                    },
                    legend: {
                        labels: {
                            font: {
                                size: 16 // Set the font size for legend
                            }
                        }
                    }
                }
            }
        });
    });
</script>
</body>
</html>
