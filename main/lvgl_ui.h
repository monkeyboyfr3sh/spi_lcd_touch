#pragma once
#include "lvgl.h"

typedef enum {
    bar_display,
    meter_display,
    clock_display,
    plot_display,
    slider_display,
    display_mode_max,
    display_mode_unknown
} display_mode_t;

void set_accelerometer_data(float new_x, float new_y, float new_z);
void get_accelerometer_data(float *get_x_buff, float *get_y_buff, float *get_z_buff);

void create_lvgl_ui(display_mode_t display_mode);
void cycle_display_code(void);
