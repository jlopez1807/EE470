<?php

$servername = "localhost";
$username = "u326197708_db_jessielopez";
$password = "Meelie1807!";
$dbname = "u326197708_jessielopez";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Get node name from user input or default to 'node_1'
$node_name = isset($_GET['node_name']) ? $_GET['node_name'] : 'node-1';

$chart_query = "SELECT * FROM sensor_data WHERE node_name = '$node_name'";
$chart_result = $conn->query($chart_query);

$data = [];
if ($chart_result->num_rows > 0) {
    while ($row = $chart_result->fetch_assoc()) {
        $data[] = $row; // Collecting all data for the node
    }
}

// Set content type to JSON and output data
header('Content-Type: application/json');
echo json_encode($data); // Output raw JSON data without pretty print
?>
