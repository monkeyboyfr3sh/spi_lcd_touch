#include "lvgl.h"
#include "lvgl_demo_ui.h"
#include <stdio.h>

// Create labels for x, y, and z
static lv_obj_t *label_x;
static lv_obj_t *label_y;
static lv_obj_t *label_z;

static lv_obj_t *bar_x;
static lv_obj_t *bar_y;
static lv_obj_t *bar_z;

lv_meter_indicator_t *indic;
static lv_obj_t *meter;

static void update_obect(lv_obj_t *object_x, lv_obj_t *object_y, lv_obj_t *object_z, float new_x, float new_y, float new_z)
{
    // // Convert integers to strings
    // char str_x[20];
    // char str_y[20];
    // char str_z[20];
    // sprintf(str_x, "x=%0.2f", new_x);
    // sprintf(str_y, "y=%0.2f", new_y);
    // sprintf(str_z, "z=%0.2f", new_z);

    // // Update bars
    // lv_bar_set_value(bar_x, (int32_t)new_x*100.0, LV_ANIM_OFF);
    // lv_bar_set_value(bar_y, (int32_t)new_y*100.0, LV_ANIM_OFF);
    // lv_bar_set_value(bar_z, (int32_t)new_z*100.0, LV_ANIM_OFF);

    // // Update text of the labels
    // lv_label_set_text(object_x, str_x);
    // lv_label_set_text(object_y, str_y);
    // lv_label_set_text(object_z, str_z);

    lv_meter_set_indicator_end_value(meter, indic, new_y*100.0);
}

void update_bars(float new_x, float new_y, float new_z)
{
    // float z_offset = 0.0;
    float y_offset = 1.1;
    // float z_offset = 0.0;
    update_obect(label_x, label_y, label_z, -new_x, -new_y+y_offset, new_z);
}
void example_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    lv_disp_set_rotation(disp, LV_DISP_ROT_90);

    // // Create bars for x, y, and z
    // bar_x = lv_bar_create(scr);
    // bar_y = lv_bar_create(scr);
    // bar_z = lv_bar_create(scr);

    int bar_range = 900;
    int bar_height = 45;
    int bar_offset = 60;

    // // Set range and initial values for each bar
    // lv_bar_set_range(bar_x, -bar_range, bar_range); // Define the range for x
    // lv_obj_align(bar_x, LV_ALIGN_CENTER, 0, -bar_offset);
    // lv_obj_set_width(bar_x, 200); // Set the width of the bar
    // lv_obj_set_height(bar_x, bar_height); // Set the width of the bar

    // lv_bar_set_range(bar_y, -bar_range, bar_range); // Define the range for x
    // lv_obj_align(bar_y, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_width(bar_y, 200); // Set the width of the bar
    // lv_obj_set_height(bar_y, bar_height); // Set the width of the bar

    // lv_bar_set_range(bar_z, -bar_range, bar_range); // Define the range for x
    // lv_obj_align(bar_z, LV_ALIGN_CENTER, 0, bar_offset);
    // lv_obj_set_width(bar_z, 200); // Set the width of the bar
    // lv_obj_set_height(bar_z, bar_height); // Set the width of the bar

    // // Create text labels
    // label_x = lv_label_create(scr);
    // label_y = lv_label_create(scr);
    // label_z = lv_label_create(scr);

    // // Align labels to the center of the screen
    // lv_obj_align(label_x, LV_ALIGN_CENTER, 0, -60);
    // lv_obj_align(label_y, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(label_z, LV_ALIGN_CENTER, 0, 60);

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

// /*
//  * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
//  *
//  * SPDX-License-Identifier: CC0-1.0
//  */

// // This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter

// #include "lvgl.h"

// static lv_obj_t *meter;
// static lv_obj_t * btn;
// static lv_disp_rot_t rotation = LV_DISP_ROT_NONE;

// static int display_number = 20;
// void set_display_number(int set_number)
// {
//     display_number = set_number;
// }

// int get_display_number(void)
// {
//     return display_number;
// }

// static void set_value(void *indic, int32_t v)
// {
//     lv_meter_set_indicator_end_value(meter, indic, get_display_number());
// }

// static void btn_cb(lv_event_t * e)
// {
//     lv_disp_t *disp = lv_event_get_user_data(e);
//     rotation++;
//     if (rotation > LV_DISP_ROT_270) {
//         rotation = LV_DISP_ROT_NONE;
//     }
//     lv_disp_set_rotation(disp, rotation);
// }

// void example_lvgl_demo_ui(lv_disp_t *disp)
// {
//     lv_obj_t *scr = lv_disp_get_scr_act(disp);
//     meter = lv_meter_create(scr);
//     lv_obj_center(meter);
//     lv_obj_set_size(meter, 200, 200);

//     /*Add a scale first*/
//     lv_meter_scale_t *scale = lv_meter_add_scale(meter);
//     lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
//     lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);

//     lv_meter_indicator_t *indic;

//     /*Add a blue arc to the start*/
//     indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
//     lv_meter_set_indicator_start_value(meter, indic, 0);
//     lv_meter_set_indicator_end_value(meter, indic, 20);

//     /*Make the tick lines blue at the start of the scale*/
//     indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE), false, 0);
//     lv_meter_set_indicator_start_value(meter, indic, 0);
//     lv_meter_set_indicator_end_value(meter, indic, 20);

//     /*Add a red arc to the end*/
//     indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
//     lv_meter_set_indicator_start_value(meter, indic, 80);
//     lv_meter_set_indicator_end_value(meter, indic, 100);

//     /*Make the tick lines red at the end of the scale*/
//     indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
//     lv_meter_set_indicator_start_value(meter, indic, 80);
//     lv_meter_set_indicator_end_value(meter, indic, 100);

//     /*Add a needle line indicator*/
//     indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

//     // btn = lv_btn_create(scr);
//     // lv_obj_t * lbl = lv_label_create(btn);
//     // lv_label_set_text_static(lbl, LV_SYMBOL_REFRESH" ROTATE");
//     // lv_obj_align(btn, LV_ALIGN_BOTTOM_LEFT, 30, -30);
//     // /*Button event*/
//     // lv_obj_add_event_cb(btn, btn_cb, LV_EVENT_CLICKED, disp);

//     /*Create an animation to set the value*/
//     lv_anim_t a;
//     lv_anim_init(&a);
//     lv_anim_set_exec_cb(&a, set_value);
//     lv_anim_set_var(&a, indic);
//     lv_anim_set_values(&a, 0, 100);
//     lv_anim_set_time(&a, 2000);
//     lv_anim_set_repeat_delay(&a, 100);
//     lv_anim_set_playback_time(&a, 500);
//     lv_anim_set_playback_delay(&a, 100);
//     lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
//     lv_anim_start(&a);
// }
