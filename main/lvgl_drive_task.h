#pragma once

#define LVGL_SAMPLE_PERIOD_US          1000
#define EXAMPLE_LVGL_TICK_PERIOD_MS    5

#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 10
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (4 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     tskIDLE_PRIORITY+20

void lvgl_drive_task(void *arg);
