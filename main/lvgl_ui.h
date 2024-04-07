#pragma once
#include "lvgl.h"

typedef enum {
    bar_display,
    meter_display,
    clock_display,
    display_mode_max,
    display_mode_unknown
} display_mode_t;

void update_bars(float new_x, float new_y, float new_z);
void create_lvgl_ui(display_mode_t display_mode);
void cycle_display_code(void);
