#include "lvgl.h"
#include <stdio.h>

#include "ui.h"

#include "esp_log.h"

static const char * TAG = "screen_1_cb";

void accelerometer_en_sw_cb(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * en_sw = lv_event_get_target(e);
    bool en = lv_obj_has_state(en_sw, LV_STATE_CHECKED);
    ESP_LOGI(TAG, "en changed value: %d", en);
}
