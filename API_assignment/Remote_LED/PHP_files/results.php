<?php
// Allow PUT request
if ($_SERVER['REQUEST_METHOD'] === 'PUT') {
    parse_str(file_get_contents("php://input"), $data);
    
    // Check if the led parameter is set
    if (isset($data['led'])) {
        // Update the results.txt file with the new LED state
        file_put_contents('results.txt', $data['led']);
        http_response_code(200); // Success
    } else {
        http_response_code(400); // Bad Request
    }
} else {
    // Handle GET request
    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        // Read the LED state from the results.txt file
        echo file_get_contents('results.txt');
    } else {
        http_response_code(405); // Method Not Allowed
    }
}
?>
