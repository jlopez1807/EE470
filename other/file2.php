<?php
// Setting header to JSON
header('Content-Type: application/json');

// Database credentials
define('DB_HOST', 'localhost');
define('DB_USERNAME', 'u326197708_db_jessielopez');
define('DB_PASSWORD', 'Meelie1807!');
define('DB_NAME', 'u326197708_jessielopez');

// Establishing a database connection
$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

// Check the connection
if ($mysqli->connect_error) {
    die(json_encode(['error' => 'Connection failed: ' . $mysqli->connect_error]));
}

// Query to get data from the table
$query = "SELECT node_name, temperature, time_received FROM sensor_data";

// Execute the query
$result = $mysqli->query($query);

// Check if the query was successful
if (!$result) {
    die(json_encode(['error' => 'Query failed: ' . $mysqli->error]));
}

// Loop through the returned data
$data = [];
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

// Close the database connection
$mysqli->close();

// Output the data as JSON
echo json_encode($data);
?>
