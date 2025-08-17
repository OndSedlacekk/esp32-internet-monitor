#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "wifi_manager.h"
#include "internet_check.h"
#include "web_server.h"

static const char *TAG = "main";

void app_main(void) {
    // Initialize NVS — required for Wi-Fi
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Optional: enable log visibility
    esp_log_level_set("*", ESP_LOG_INFO);

    wifi_init_sta();  // Start Wi-Fi

    start_web_server(); // Start Http web server

    while (1) {
        if (wifi_is_connected()) {
            if (check_internet_connection()) {
                ESP_LOGI(TAG, "Internet is available.");
            } else {
                ESP_LOGW(TAG, "Wi-Fi connected but no internet.");
            }
        } else {
            ESP_LOGW(TAG, "Wi-Fi not connected.");
        }

        vTaskDelay(pdMS_TO_TICKS(10000));  // Wait 10 seconds
    }
}

