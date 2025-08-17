#include "internet_check.h"
#include "esp_log.h"
#include "lwip/netdb.h"
#include "esp_timer.h"

static const char *TAG = "NetCheck";

#define MAX_REC 100
#define WEEK_SEC (7 * 24 * 60 * 60)

typedef struct {
    int64_t start;
    int64_t dur;
} outage_t;

static outage_t rec[MAX_REC];
static int rec_count = 0;
static int64_t cur_start = 0;
static bool was_up = true;
//static int counter = 0;

bool check_internet_connection(void) {
    bool up = (gethostbyname("example.com") != NULL);
    int64_t now = esp_timer_get_time(); // µs

    // Simulating outages
    /*counter++;
    if(counter == 5){
        up = false;
        counter = 0;
    }*/

    if (up) {
        ESP_LOGI(TAG, "Internet is UP");

        if (!was_up && cur_start != 0) {
            if (rec_count < MAX_REC) {
                rec[rec_count++] = (outage_t){ .start = cur_start, .dur = now - cur_start };
            }
            cur_start = 0;
        }
    } else {
        ESP_LOGW(TAG, "Internet is DOWN");

        if (was_up) {
            cur_start = now;
        }
    }

    was_up = up;
    return up;
}

int get_outage_count_7d(void) {
    int64_t now = esp_timer_get_time();
    int cnt = 0;
    for (int i = 0; i < rec_count; i++) {
        if ((now - rec[i].start) < WEEK_SEC * 1000000LL) {
            cnt++;
        }
    }
    return cnt;
}

int get_outage_total_7d(void) {
    int64_t now = esp_timer_get_time(), sum = 0;
    for (int i = 0; i < rec_count; i++) {
        if ((now - rec[i].start) < WEEK_SEC * 1000000LL) {
            sum += rec[i].dur;
        }
    }
    return sum / 1000000; // to seconds
}

