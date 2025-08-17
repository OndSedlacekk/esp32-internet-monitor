#pragma once

// Starts the HTTP web server on the ESP32.
// Registers all defined URI handlers (e.g., /status) and begins listening for requests.
void start_web_server(void);
