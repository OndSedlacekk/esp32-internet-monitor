# ESP32 Internet Outage Logger

This project is a **solo demo project** built with **ESP-IDF** to monitor internet availability and log outages.  
The ESP32 connects to Wi-Fi, periodically checks for internet connectivity, and exposes a simple **web server** that shows:

- Current Wi-Fi and internet connection status  
- Number of outages in the last 7 days  
- Total downtime in the last 7 days  

It is designed as an example project for embedded systems and networking, and can be used as a lightweight tool to track ISP reliability.

---

## Features

- Connects to Wi-Fi in **station mode**  
- Periodically checks connectivity (DNS lookup test)  
- Tracks outages (start, duration) in a circular buffer  
- Provides a **REST-like web interface** via HTTP server  
- Persistent uptime/downtime statistics for the last 7 days  
- Modular project structure for scalability  

---

## Project Structure

```
esp32-internet-logger/
├── main/
│   ├── main.c              # Entry point
│   ├── wifi_manager.c      # Wi-Fi connection handling
│   ├── wifi_manager.h
│   ├── internet_check.c    # Connectivity checking + outage statistics
│   ├── internet_check.h
│   ├── web_server.c        # Minimal HTTP server exposing status
│   ├── web_server.h
│   ├── config_template.h   # Example configuration file (Wi-Fi SSID & password)
│   └── CMakeLists.txt
├── CMakeLists.txt
├── sdkconfig               # ESP-IDF build config
├── README.md               # This file
└── .gitignore              # Ignore secrets like config.h
```

---

## Example Web Output

When accessing `http://<ESP_IP>/status`:

```
Internet: Connected
Outages (7d): 2
Total Downtime (7d): 135 s
```

---

## Configuration

Wi-Fi credentials are stored in wifi_config.c. Edit this file to add your SSID and password before building and flashing the project.

```
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"
```

---

## Hardware Requirements

- ESP32 DevKit (tested on ESP32-WROOM-32)  
- 5V USB power supply (e.g., phone charger)  
- Wi-Fi network  

---

## License

MIT License — free to use, modify, and share.  

---

## Author

Developed as a small hobby project to test ESP32 functionality. Monitors internet outages and shows stats on a simple web page.
