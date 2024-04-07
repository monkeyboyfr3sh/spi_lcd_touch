#include "lvgl.h"
#include "lvgl_ui.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

// Define a threshold for the difference
#define THRESHOLD 0.0

// Create labels for x, y, and z
static lv_obj_t *label_x;
static lv_obj_t *label_y;
static lv_obj_t *label_z;

static lv_obj_t *bar_x;
static lv_obj_t *bar_y;
static lv_obj_t *bar_z;

// Define text labels for FPS and CPU utilization
static lv_obj_t *label_fps;
uint32_t frame_count = 0;

static lv_obj_t *label_cpu;

static lv_meter_indicator_t *indic;
static lv_obj_t *meter;
const float graph_sensitivity = 100.0;

// Flag to indicate which display code is currently active
static display_mode_t current_display_code = bar_display;

double xy_to_degrees(double x, double y) {
    // Calculate the angle in radians
    double radians = atan2(y, x);
    
    // Convert radians to degrees
    double degrees = radians * (180.0 / M_PI);
    
    // Ensure the angle is within [0, 360] range
    while (degrees < 0) {
        degrees += 360.0;
    }
    
    return degrees;
}

// Function to update display based on the chosen display code
static void update_display_code(float new_x, float new_y, float new_z) {
    switch (current_display_code)
    {
    case meter_display:
        lv_meter_set_indicator_end_value(meter, indic, xy_to_degrees(new_x, new_y));
        // lv_meter_set_indicator_end_value(meter, indic, new_y * 100.0);
        break;

    case bar_display:
        // Display code 2
        lv_bar_set_value(bar_x, new_x * graph_sensitivity, LV_ANIM_OFF);
        lv_bar_set_value(bar_y, new_y * graph_sensitivity, LV_ANIM_OFF);
        lv_bar_set_value(bar_z, new_z * graph_sensitivity, LV_ANIM_OFF);
        break;
    
    default:
        break;
    }
}

// Function to switch between display codes
void cycle_display_code(void)
{
    display_mode_t new_display_code = (current_display_code+1) % display_mode_max;
    // Reinitialize UI based on the new display code
    create_lvgl_ui(new_display_code);
}

void update_bars(float new_x, float new_y, float new_z) {
    // Call the function to update the display based on the chosen display code
    update_display_code(-new_x, -new_y, new_z);
}

static lv_obj_t * clock_meter;
lv_meter_indicator_t * indic_min;
lv_meter_indicator_t * indic_hour; 
lv_timer_t * clock_timer;

static void set_clock(void)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    int32_t system_hours = timeinfo->tm_hour;
    int32_t system_minutes = timeinfo->tm_min;
    int32_t system_seconds = timeinfo->tm_sec;

    lv_meter_set_indicator_end_value(clock_meter, indic_min, system_seconds);
    lv_meter_set_indicator_end_value(clock_meter, indic_hour, system_minutes);
}

void create_lvgl_ui(display_mode_t display_mode)
{
    lv_disp_t *disp = NULL; // This will fetch default
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    lv_disp_set_rotation(disp, LV_DISP_ROT_270);

    const float acceleration = 9.81; // m/s^2
    const int g_scale = 2; // # of g to show
    const int bar_range = (acceleration * g_scale) * graph_sensitivity; // Applying graph sensitivity scale
    const int bar_height = 45;
    const int bar_offset = 60;

    // Stop animations when switching away from clock display
    if (current_display_code == clock_display) {
        lv_timer_del(clock_timer); 
    }

    // Clear the screen before re-creating the UI
    lv_obj_clean(scr);

    switch (display_mode)
    {
    case meter_display:
        // Create a meter
        meter = lv_meter_create(scr);
        lv_obj_center(meter);
        lv_obj_set_size(meter, 240, 240);

        /*Add a scale first*/
        lv_meter_scale_t *scale = lv_meter_add_scale(meter);

        // xy_to_degrees
        // lv_meter_set_scale_range(meter,scale,-bar_range, bar_range, 300, 300);
        lv_meter_set_scale_range(meter,scale, 0, 360, 360, 270);
        lv_meter_set_scale_ticks(meter, scale, 17 , 2, 10, lv_palette_main(LV_PALETTE_GREY));
        lv_meter_set_scale_major_ticks(meter, scale, 2, 4, 15, lv_color_black(), 10);

        /*Add a needle line indicator*/
        indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);
        break;

    case bar_display:
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
        break;

    case clock_display:
        // Create a meter
        clock_meter = lv_meter_create(scr);
        lv_obj_center(clock_meter);
        lv_obj_set_size(clock_meter, 240, 240);

        /*Create a scale for the minutes*/
        /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
        lv_meter_scale_t * scale_min = lv_meter_add_scale(clock_meter);
        lv_meter_set_scale_ticks(clock_meter, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_GREY));
        lv_meter_set_scale_range(clock_meter, scale_min, 0, 60, 360, 270);

        /*Create another scale for the hours. It's only visual and contains only major ticks*/
        lv_meter_scale_t * scale_hour = lv_meter_add_scale(clock_meter);
        lv_meter_set_scale_ticks(clock_meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
        lv_meter_set_scale_major_ticks(clock_meter, scale_hour, 1, 2, 20, lv_color_black(), 10);    /*Every tick is major*/
        lv_meter_set_scale_range(clock_meter, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/

        LV_IMG_DECLARE(img_hand)

        /*Add a the hands from images*/
        indic_min = lv_meter_add_needle_img(clock_meter, scale_min, &img_hand, 5, 5);
        indic_hour = lv_meter_add_needle_img(clock_meter, scale_min, &img_hand, 5, 5);

        clock_timer = lv_timer_create(set_clock, 100, NULL);
        break;
    
    default:
        display_mode = display_mode_unknown;
        break;
    }

    // Update display mode var
    current_display_code = display_mode;
}
