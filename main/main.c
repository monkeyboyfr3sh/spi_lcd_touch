#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#include "display_hardware_helpers.h"
#include "lvgl_drive_task.h"

static const char *TAG = "main";

void app_main(void)
{
    // Initialize display drivers
    initialize_display_drivers();
    
    // Create the driver task
    ESP_LOGI(TAG, "Creating LVGL task");
    xTaskCreate(lvgl_drive_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);
}
