#pragma once
#include <stdbool.h>

// Initializes the ESP32 Wi-Fi in station mode (STA) and connects to the configured network.
void wifi_init_sta(void);

// Returns true if the ESP32 is currently connected to the Wi-Fi network, false otherwise.
bool wifi_is_connected(void);