#include "web_server.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "internet_check.h"
#include "wifi_manager.h"
#include <stdio.h>  // for snprintf

static const char *TAG = "web_server";

static esp_err_t status_get_handler(httpd_req_t *req)
{
    char resp[256];  // Buffer for HTTP response
    if (wifi_is_connected()) {
        bool internet = check_internet_connection();
        int count = get_outage_count_7d();
        int total = get_outage_total_7d();
        snprintf(resp, sizeof(resp),
                 "Internet: %s\nOutages (7d): %d\nTotal Downtime (7d): %d s\n",
                 internet ? "Connected" : "Disconnected",
                 count,
                 total);
    } else {
        snprintf(resp, sizeof(resp), "Wi-Fi: Not connected\n");
    }

    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t status_uri = {
    .uri       = "/status",
    .method    = HTTP_GET,
    .handler   = status_get_handler,
    .user_ctx  = NULL
};

void start_web_server(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    esp_err_t ret = httpd_start(&server, &config);
    if (ret == ESP_OK) {
        httpd_register_uri_handler(server, &status_uri);
        ESP_LOGI(TAG, "Web server started, visit http://<ESP_IP>/status");
    } else {
        ESP_LOGE(TAG, "Failed to start web server: %s", esp_err_to_name(ret));
    }
}
