$(document).ready(function() {
  $.ajax({
    url: "https://ssu.jessielopez.net/PHP_Projects/file2.php", // Your JSON endpoint
    method: "GET",
    dataType: "json",
    success: function(data) {
      console.log("Data received:", data); // Log the data

      var x_axis = [];
      var y_axis = [];

      // Loop through the returned data
      for (var i in data) {
        x_axis.push(data[i].time_received); // Use time_received for x-axis
        y_axis.push(data[i].temperature); // Use temperature for y-axis
      }

      console.log("X Axis:", x_axis); // Log x_axis values
      console.log("Y Axis:", y_axis); // Log y_axis values

      // Check if data arrays are populated
      if (x_axis.length === 0 || y_axis.length === 0) {
        console.error("No data available to display.");
        return; // Exit if there's no data
      }

      var chartdata = {
        labels: x_axis,
        datasets: [{
          label: 'Temperature',
          backgroundColor: 'rgba(200, 200, 200, 0.75)',
          borderColor: 'rgba(200, 200, 200, 1)',
          hoverBackgroundColor: 'rgba(200, 200, 200, 1)',
          hoverBorderColor: 'rgba(200, 200, 200, 1)',
          data: y_axis
        }]
      };

      var ctx = $("#mycanvas");

      // Check if context is valid
      if (!ctx) {
        console.error("Failed to get canvas context.");
        return;
      }

      var barGraph = new Chart(ctx, {
        type: 'bar',
        data: chartdata,
      });
    },
    error: function(xhr, status, error) {
      console.error("AJAX Error: " + status + ": " + error);
    }
  });
});
