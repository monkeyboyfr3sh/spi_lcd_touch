#include "lvgl_drive_task.h"

#include <esp_log.h>

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <driver/i2c.h>
#include <esp_timer.h>
#include <lvgl.h>
#include "esp_task_wdt.h"

#include "display_config.h"
#include "qmi8658.h"
#include "lvgl_ui.h"
#include "circular_integrator.h"

static const char * TAG = "lvgl-drive";

static SemaphoreHandle_t lvgl_mux = NULL;
static acc_axes_raw_t acc;
static CircularBuffer buff_x, buff_y, buff_z;

#define I2C_MASTER_NUM              I2C_NUM_0 // I2C port number for master dev

static void increase_lvgl_tick_cb(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

static void lvgl_update_cb(void *arg)
{
    int avg_x = getAccumulatedSum(&buff_x)/buff_x.size;
    int avg_y = getAccumulatedSum(&buff_y)/buff_y.size;
    int avg_z = getAccumulatedSum(&buff_z)/buff_z.size;
    // const float accelerometer_sensitivity = 8192.0;
    const float accelerometer_sensitivity = 16384.0;

    // Calculate g
    float x = ((float)avg_x/accelerometer_sensitivity) * 9.81;
    float y = ((float)avg_y/accelerometer_sensitivity) * 9.81;
    float z = ((float)avg_z/accelerometer_sensitivity) * 9.81;

    // Update UI
    set_accelerometer_data(x, y, z);
}

static void sample_qmi8658_cb(void *arg)
{
    // Read accelerometer
    qmi8658_read_accelerometer(I2C_MASTER_NUM, &acc);

    // Add samples to buffer
    addSample(&buff_x, acc.x);
    addSample(&buff_y, acc.y);
    addSample(&buff_z, acc.z);
}

bool lvgl_lock(int timeout_ms)
{
    // Convert timeout in milliseconds to FreeRTOS ticks
    // If `timeout_ms` is set to -1, the program will block until the condition is met
    const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE;
}

void lvgl_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
}

void lvgl_drive_task(void *arg)
{
    ESP_LOGI(TAG, "Starting LVGL drive task");
    ESP_LOGI(TAG, "LittlevGL version: %s", lv_version_info());

    ESP_LOGI(TAG, "Creating lvgl mutex");
    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    assert(lvgl_mux);

    // Configure gpio 0 as input
    gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT);

    ESP_LOGI(TAG, "Initializing filters");
    static size_t buff_len = 100;
    initializeCircularBuffer(&buff_x, buff_len);
    initializeCircularBuffer(&buff_y, buff_len);
    initializeCircularBuffer(&buff_z, buff_len);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick_cb,
        .name = "lvgl_tick"
    };

    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Install LVGL update timer");
    // Tick interface for LVGL (using esp_timer to generate periodic event)
    const esp_timer_create_args_t lvgl_update_timer_args = {
        .callback = &lvgl_update_cb,
        .name = "lvgl_update"
    };

    esp_timer_handle_t lvgl_update_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_update_timer_args, &lvgl_update_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_update_timer, LVGL_UPDATE_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Creating UI");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    if (lvgl_lock(-1)) {
        create_lvgl_ui(plot_display);
        // Release the mutex
        lvgl_unlock();
    }

    ESP_LOGI(TAG, "Initializing QMI8658");
    qmi8658_reset(I2C_MASTER_NUM);
    // qmi8658_write_byte(I2C_MASTER_NUM, 0x03, 0x13); // Set accelerometer (sensitivity=+-4g) and (data rate=1000Hz)
    qmi8658_write_byte(I2C_MASTER_NUM, 0x03, 0x03); // Set accelerometer (sensitivity=+-4g) and (data rate=1000Hz)
    qmi8658_write_byte(I2C_MASTER_NUM, 0x06, 0x01); // Enable accelerometer LPF
    qmi8658_write_byte(I2C_MASTER_NUM, 0x08, 0x01); // Enable accelerometer

    // Run whoami checl
    if(qmi8658_whoami_check(I2C_MASTER_NUM)!=ESP_OK){
        vTaskDelete(NULL);
    }

    ESP_LOGI(TAG, "Install LVGL sample timer");
    // Tick interface for LVGL (using esp_timer to generate periodic event)
    const esp_timer_create_args_t lvgl_sample_timer_args = {
        .callback = &sample_qmi8658_cb,
        .name = "lvgl_sample"
    };

    esp_timer_handle_t lvgl_sample_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_sample_timer_args, &lvgl_sample_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_sample_timer, LVGL_SAMPLE_PERIOD_US));

    // Turn on LCD backlight
    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

    TickType_t last_switch_time = xTaskGetTickCount();

    ESP_LOGI(TAG, "Running QMI8658 sample loop");
    uint32_t task_delay_ms = EXAMPLE_LVGL_TASK_MAX_DELAY_MS;
    bool prev_btn_lvl = true;
    bool curr_btn_lvl = true;
    while (1) {
        
        // Lock the mutex due to the LVGL APIs are not thread-safe
        if (lvgl_lock(-1)) {
            lv_timer_handler();

            prev_btn_lvl = curr_btn_lvl;
            curr_btn_lvl = gpio_get_level(GPIO_NUM_0);
            if (
                (xTaskGetTickCount() - last_switch_time >= pdMS_TO_TICKS(100)) &&
                ((prev_btn_lvl==1)&&(curr_btn_lvl==0))
            ) {
                last_switch_time = xTaskGetTickCount();

                // Update display code
                cycle_display_code();
            }

            // Release the mutex
            lvgl_unlock();
        }
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }

    vTaskDelete(NULL);
}
