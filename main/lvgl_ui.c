#include "lvgl.h"
#include "lvgl_ui.h"
#include <stdio.h>
#include <math.h>

// Define a threshold for the difference
#define THRESHOLD 0.0

// Create labels for x, y, and z
static lv_obj_t *label_x;
static lv_obj_t *label_y;
static lv_obj_t *label_z;

static lv_obj_t *bar_x;
static lv_obj_t *bar_y;
static lv_obj_t *bar_z;

lv_meter_indicator_t *indic;
static lv_obj_t *meter;
const float graph_sensitivity = 100.0;

// Flag to indicate which display code is currently active
static int current_display_code = 1;

// Function to update display based on the chosen display code
static void update_display_code(float new_x, float new_y, float new_z) {
    if (current_display_code == 2) {
        // Display code 1
        lv_meter_set_indicator_end_value(meter, indic, new_y * 100.0);
    } else {
        // Display code 2
        lv_bar_set_value(bar_x, new_x * graph_sensitivity, LV_ANIM_OFF);
        lv_bar_set_value(bar_y, new_y * graph_sensitivity, LV_ANIM_OFF);
        lv_bar_set_value(bar_z, new_z * graph_sensitivity, LV_ANIM_OFF);
    }
}

// Function to switch between display codes
void switch_display_code()
{
    current_display_code = (current_display_code == 1) ? 2 : 1;
    // Reinitialize UI based on the new display code
    create_lvgl_ui();
}

void update_bars(float new_x, float new_y, float new_z) {
    // Call the function to update the display based on the chosen display code
    update_display_code(new_x, new_y, new_z);
}

void create_lvgl_ui(void) {
    lv_disp_t *disp = NULL; // This will fetch default
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    lv_disp_set_rotation(disp, LV_DISP_ROT_90);

    const float acceleration = 9.81; // m/s^2
    const int g_scale = 2; // # of g to show
    const int bar_range = (acceleration * g_scale) * graph_sensitivity; // Applying graph sensitivity scale
    const int bar_height = 45;
    const int bar_offset = 60;

    // Clear the screen before re-creating the UI
    lv_obj_clean(scr);

    if (current_display_code == 1) {
        // Create bars for x, y, and z
        bar_x = lv_bar_create(scr);
        bar_y = lv_bar_create(scr);
        bar_z = lv_bar_create(scr);

        // Set range and initial values for each bar
        lv_bar_set_range(bar_x, -bar_range, bar_range); // Define the range for x
        lv_obj_align(bar_x, LV_ALIGN_CENTER, 0, -bar_offset);
        lv_obj_set_width(bar_x, 200); // Set the width of the bar
        lv_obj_set_height(bar_x, bar_height); // Set the width of the bar

        lv_bar_set_range(bar_y, -bar_range, bar_range); // Define the range for x
        lv_obj_align(bar_y, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_width(bar_y, 200); // Set the width of the bar
        lv_obj_set_height(bar_y, bar_height); // Set the width of the bar

        lv_bar_set_range(bar_z, -bar_range, bar_range); // Define the range for x
        lv_obj_align(bar_z, LV_ALIGN_CENTER, 0, bar_offset);
        lv_obj_set_width(bar_z, 200); // Set the width of the bar
        lv_obj_set_height(bar_z, bar_height); // Set the width of the bar

        // Create text labels
        label_x = lv_label_create(scr);
        label_y = lv_label_create(scr);
        label_z = lv_label_create(scr);

        // Align labels to the center of the screen
        lv_obj_align(label_x, LV_ALIGN_CENTER, 0, -60);
        lv_obj_align(label_y, LV_ALIGN_CENTER, 0, 0);
        lv_obj_align(label_z, LV_ALIGN_CENTER, 0, 60);

        lv_label_set_text(label_x,"X");
        lv_label_set_text(label_y,"Y");
        lv_label_set_text(label_z,"Z");
    } else {
        // Create a meter
        meter = lv_meter_create(scr);
        lv_obj_center(meter);
        lv_obj_set_size(meter, 240, 240);

        /*Add a scale first*/
        lv_meter_scale_t *scale = lv_meter_add_scale(meter);

        lv_meter_set_scale_range(meter,scale,-bar_range, bar_range, 300, 300);
        lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
        lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);

        /*Add a blue arc to the start*/
        indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
        lv_meter_set_indicator_start_value(meter, indic, (bar_range*0.6));
        lv_meter_set_indicator_end_value(meter, indic, bar_range);

        /*Make the tick lines blue at the start of the scale*/
        indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
        lv_meter_set_indicator_start_value(meter, indic, (bar_range*0.6));
        lv_meter_set_indicator_end_value(meter, indic, bar_range);

        /*Add a red arc to the end*/
        indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
        lv_meter_set_indicator_start_value(meter, indic, -bar_range);
        lv_meter_set_indicator_end_value(meter, indic, -(bar_range*0.6));

        /*Make the tick lines red at the end of the scale*/
        indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
        lv_meter_set_indicator_start_value(meter, indic, -bar_range);
        lv_meter_set_indicator_end_value(meter, indic, -(bar_range*0.6));

        /*Add a needle line indicator*/
        indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);
    }
}
