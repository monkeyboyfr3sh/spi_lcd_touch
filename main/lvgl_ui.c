#include "lvgl.h"
#include "lvgl_ui.h"
#include <stdio.h>
#include <math.h>

// Define a threshold for the difference
#define THRESHOLD 0.0

// Define the clock object globally
lv_obj_t *hour_hand, *minute_hand, *second_hand, *clock;

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

// static lv_obj_t * clock_scale;
// static lv_obj_t * minute_hand;
// static lv_obj_t * hour_hand;
// static lv_point_precise_t minute_hand_points[2];
// static int32_t hour;
// static int32_t minute;

static void timer_cb(lv_timer_t * timer)
{
    // LV_UNUSED(timer);

    // minute++;
    // if(minute > 59) {
    //     minute = 0;
    //     hour++;
    //     if(hour > 11) {
    //         hour = 0;
    //     }
    // }

    // /**
    //  * the scale will store the needle line points in the existing
    //  * point array if one was set with `lv_line_set_points_mutable`.
    //  * Otherwise, it will allocate the needle line points.
    //  */

    // /* the scale will store the minute hand line points in `minute_hand_points` */
    // lv_scale_set_line_needle_value(clock_scale, minute_hand, 60, minute);
    // /* log the points that were stored in the array */
    // LV_LOG_USER(
    //     "minute hand points - "
    //     "0: (%" my_PRIprecise ", %" my_PRIprecise "), "
    //     "1: (%" my_PRIprecise ", %" my_PRIprecise ")",
    //     minute_hand_points[0].x, minute_hand_points[0].y,
    //     minute_hand_points[1].x, minute_hand_points[1].y
    // );

    // /* the scale will allocate the hour hand line points */
    // lv_scale_set_line_needle_value(clock_scale, hour_hand, 40, hour * 5 + (minute / 12));
}

/**
 * A round scale with multiple needles, resembing a clock
 */
void lv_example_scale_6(void)
{

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
    current_display_code = (current_display_code+1) % display_mode_max;
    // Reinitialize UI based on the new display code
    create_lvgl_ui(current_display_code);
}

void update_bars(float new_x, float new_y, float new_z) {
    // Call the function to update the display based on the chosen display code
    update_display_code(-new_x, -new_y, new_z);
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
        // clock_scale = lv_scale_create(lv_screen_active());

        // lv_obj_set_size(clock_scale, 150, 150);
        // lv_scale_set_mode(clock_scale, LV_SCALE_MODE_ROUND_INNER);
        // lv_obj_set_style_bg_opa(clock_scale, LV_OPA_60, 0);
        // lv_obj_set_style_bg_color(clock_scale, lv_color_black(), 0);
        // lv_obj_set_style_radius(clock_scale, LV_RADIUS_CIRCLE, 0);
        // lv_obj_set_style_clip_corner(clock_scale, true, 0);
        // lv_obj_center(clock_scale);

        // lv_scale_set_label_show(clock_scale, true);

        // lv_scale_set_total_tick_count(clock_scale, 61);
        // lv_scale_set_major_tick_every(clock_scale, 5);

        // static const char * hour_ticks[] = {"12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", NULL};
        // lv_scale_set_text_src(clock_scale, hour_ticks);

        // static lv_style_t indicator_style;
        // lv_style_init(&indicator_style);

        // /* Label style properties */
        // lv_style_set_text_font(&indicator_style, LV_FONT_DEFAULT);
        // lv_style_set_text_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));

        // /* Major tick properties */
        // lv_style_set_line_color(&indicator_style, lv_palette_main(LV_PALETTE_YELLOW));
        // lv_style_set_length(&indicator_style, 8); /* tick length */
        // lv_style_set_line_width(&indicator_style, 2); /* tick width */
        // lv_obj_add_style(clock_scale, &indicator_style, LV_PART_INDICATOR);

        // /* Minor tick properties */
        // static lv_style_t minor_ticks_style;
        // lv_style_init(&minor_ticks_style);
        // lv_style_set_line_color(&minor_ticks_style, lv_palette_main(LV_PALETTE_YELLOW));
        // lv_style_set_length(&minor_ticks_style, 6); /* tick length */
        // lv_style_set_line_width(&minor_ticks_style, 2); /* tick width */
        // lv_obj_add_style(clock_scale, &minor_ticks_style, LV_PART_ITEMS);

        // /* Main line properties */
        // static lv_style_t main_line_style;
        // lv_style_init(&main_line_style);
        // lv_style_set_arc_color(&main_line_style, lv_color_black());
        // lv_style_set_arc_width(&main_line_style, 5);
        // lv_obj_add_style(clock_scale, &main_line_style, LV_PART_MAIN);

        // lv_scale_set_range(clock_scale, 0, 60);

        // lv_scale_set_angle_range(clock_scale, 360);
        // lv_scale_set_rotation(clock_scale, 270);

        // minute_hand = lv_line_create(clock_scale);
        // lv_line_set_points_mutable(minute_hand, minute_hand_points, 2);

        // lv_obj_set_style_line_width(minute_hand, 3, 0);
        // lv_obj_set_style_line_rounded(minute_hand, true, 0);
        // lv_obj_set_style_line_color(minute_hand, lv_color_white(), 0);

        // hour_hand = lv_line_create(clock_scale);

        // lv_obj_set_style_line_width(hour_hand, 5, 0);
        // lv_obj_set_style_line_rounded(hour_hand, true, 0);
        // lv_obj_set_style_line_color(hour_hand, lv_palette_main(LV_PALETTE_RED), 0);

        // hour = 11;
        // minute = 5;
        // lv_timer_t * timer = lv_timer_create(timer_cb, 250, NULL);
        // lv_timer_ready(timer);
        break;
    
    default:
        display_mode = display_mode_unknown;
        break;
    }

    // Update display mode var
    current_display_code = display_mode;
}
