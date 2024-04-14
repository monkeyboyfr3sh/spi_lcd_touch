#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#include "display_hardware_helpers.h"
#include "lvgl_drive_task.h"

#include "protocol_examples_common.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "ssh_task.h"

static const char *TAG = "main";

#define COMMAND_MAX_LEN 64
#define NUM_BUTTONS     6
char button_command_lut[NUM_BUTTONS][COMMAND_MAX_LEN] = {
    "qm list",
    "echo 123",
};

void app_main(void)
{
    // Initialize display drivers
    initialize_display_drivers();

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    // ESP_ERROR_CHECK(wifi_connect());
    ESP_ERROR_CHECK(example_connect());

    // Create the driver task
    ESP_LOGI(TAG, "Creating LVGL task");
    xTaskCreate(lvgl_drive_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);

    char * cmd = &button_command_lut[0][0];
    run_ssh_task_blocked(cmd);
}
