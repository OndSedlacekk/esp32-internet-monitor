#pragma once
#include <stdbool.h>

// Checks if the ESP currently has an active internet connection.
// Returns true if the internet is reachable, false otherwise.
bool check_internet_connection(void);

// Returns the number of internet outages that occurred in the last 7 days.
// Outages are counted only if they lasted at least a brief moment.
int get_outage_count_7d(void);

// Returns the total duration (in seconds) of all internet outages in the last 7 days.
int get_outage_total_7d(void);
