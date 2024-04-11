// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_accelerometer_en_sw = lv_switch_create(ui_Screen1);
    lv_obj_set_width(ui_accelerometer_en_sw, 50);
    lv_obj_set_height(ui_accelerometer_en_sw, 25);
    lv_obj_set_x(ui_accelerometer_en_sw, 0);
    lv_obj_set_y(ui_accelerometer_en_sw, 52);
    lv_obj_set_align(ui_accelerometer_en_sw, LV_ALIGN_CENTER);


    ui_x_display_bar = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_x_display_bar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_x_display_bar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_x_display_bar, 150);
    lv_obj_set_height(ui_x_display_bar, 10);
    lv_obj_set_x(ui_x_display_bar, 20);
    lv_obj_set_y(ui_x_display_bar, -40);
    lv_obj_set_align(ui_x_display_bar, LV_ALIGN_CENTER);

    ui_y_display_bar = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_y_display_bar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_y_display_bar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_y_display_bar, 150);
    lv_obj_set_height(ui_y_display_bar, 10);
    lv_obj_set_x(ui_y_display_bar, 20);
    lv_obj_set_y(ui_y_display_bar, -10);
    lv_obj_set_align(ui_y_display_bar, LV_ALIGN_CENTER);

    ui_z_display_bar = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_z_display_bar, 25, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_z_display_bar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_z_display_bar, 150);
    lv_obj_set_height(ui_z_display_bar, 10);
    lv_obj_set_x(ui_z_display_bar, 20);
    lv_obj_set_y(ui_z_display_bar, 20);
    lv_obj_set_align(ui_z_display_bar, LV_ALIGN_CENTER);

    ui_x_label = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_x_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_x_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_x_label, -83);
    lv_obj_set_y(ui_x_label, -43);
    lv_obj_set_align(ui_x_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_x_label, "X");

    ui_y_label = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_y_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_y_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_y_label, -84);
    lv_obj_set_y(ui_y_label, -13);
    lv_obj_set_align(ui_y_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_y_label, "Y");

    ui_z_label = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_z_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_z_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_z_label, -85);
    lv_obj_set_y(ui_z_label, 16);
    lv_obj_set_align(ui_z_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_z_label, "Z");

    ui_on_label = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_on_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_on_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_on_label, 50);
    lv_obj_set_y(ui_on_label, 52);
    lv_obj_set_align(ui_on_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_on_label, "ON");

    ui_off_label = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_off_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_off_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_off_label, -50);
    lv_obj_set_y(ui_off_label, 52);
    lv_obj_set_align(ui_off_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_off_label, "OFF");

}
