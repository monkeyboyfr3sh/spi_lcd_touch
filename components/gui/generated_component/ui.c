// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
void ui_event_Screen1(lv_event_t * e);
lv_obj_t * ui_Screen1;
void ui_event_accelerometer_en_sw(lv_event_t * e);
lv_obj_t * ui_accelerometer_en_sw;
lv_obj_t * ui_x_display_bar;
lv_obj_t * ui_y_display_bar;
lv_obj_t * ui_z_display_bar;
lv_obj_t * ui_x_label;
lv_obj_t * ui_y_label;
lv_obj_t * ui_z_label;
lv_obj_t * ui_on_label;
lv_obj_t * ui_off_label;
lv_obj_t * ui_title;


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
void ui_event_Screen3(lv_event_t * e);
lv_obj_t * ui_Screen3;
lv_obj_t * ui_brightness_option;
lv_obj_t * ui_brightness_slider;


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
void ui_event_Screen2(lv_event_t * e);
lv_obj_t * ui_Screen2;
lv_obj_t * ui_win11_dev_label;
void ui_event_win11_start_button(lv_event_t * e);
lv_obj_t * ui_win11_start_button;
void ui_event_win11_stop_button(lv_event_t * e);
lv_obj_t * ui_win11_stop_button;
void ui_event____initial_actions0(lv_event_t * e);
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Screen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 150, 0, &ui_Screen2_screen_init);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Screen3, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 150, 0, &ui_Screen3_screen_init);
    }
}
void ui_event_accelerometer_en_sw(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        accelerometer_en_sw_cb(e);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_opacity_set(ui_x_display_bar, 40);
        _ui_opacity_set(ui_y_display_bar, 40);
        _ui_opacity_set(ui_z_display_bar, 40);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_opacity_set(ui_x_display_bar, 255);
        _ui_opacity_set(ui_y_display_bar, 255);
        _ui_opacity_set(ui_z_display_bar, 255);
    }
}
void ui_event_Screen3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen1_screen_init);
    }
}
void ui_event_Screen2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen1_screen_init);
    }
}
void ui_event_win11_start_button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        win11_dev_start_clicked_cb(e);
    }
}
void ui_event_win11_stop_button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        win11_dev_stop_clicked_cb(e);
    }
}
void ui_event____initial_actions0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        _ui_state_modify(ui_accelerometer_en_sw, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen3_screen_init();
    ui_Screen2_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui____initial_actions0, ui_event____initial_actions0, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui____initial_actions0);
    lv_disp_load_scr(ui_Screen1);
}
