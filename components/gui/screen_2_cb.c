#include "lvgl.h"
#include <stdio.h>

#include "ssh_task.h"
#include "ui.h"

#include "esp_log.h"

static const char * TAG = "screen_2_cb";

void connect_button_clicked_cb(lv_event_t * e)
{
    const size_t select_buff_len = 32;
    char os_select_string[select_buff_len];
    char cmd_select_string[select_buff_len];

    // Get select options
    lv_dropdown_get_selected_str(ui_os_select_dropdown, &os_select_string[0], select_buff_len);
    lv_dropdown_get_selected_str(ui_command_dropdown, &cmd_select_string[0], select_buff_len);

    // Log the command
    ESP_LOGI(TAG,"os:'%s', command:'%s'", os_select_string, cmd_select_string);

    const size_t out_buff_len = 32;
    char os_out_string[out_buff_len];
    char cmd_out_string[out_buff_len];

    // Interpret OS
    if(strncmp("Win11 Dev", os_select_string, out_buff_len)==0){
        strncpy(os_out_string, "104", out_buff_len);
    } else if(strncmp("Win10 Game", os_select_string, out_buff_len)==0) {
        strncpy(os_out_string, "101", out_buff_len);
    } else if(strncmp("Zorin OS", os_select_string, out_buff_len)==0) {
        strncpy(os_out_string, "100", out_buff_len);
    }

    // Interpret cmd
    if(strncmp("Start", cmd_select_string, out_buff_len)==0){
        strncpy(cmd_out_string, "start", out_buff_len);
    } else if(strncmp("Stop", cmd_select_string, out_buff_len)==0) {
        strncpy(cmd_out_string, "stop", out_buff_len);
    }

    // Form final string
    const size_t ssh_string_len = 2*out_buff_len + 32;
    char ssh_cmd_string[ssh_string_len];
    snprintf(ssh_cmd_string, ssh_string_len, 
        "qm %s %s", cmd_out_string, os_out_string);
    ESP_LOGI(TAG,"Generated command: '%s'", ssh_cmd_string);

    run_ssh_task_blocked(ssh_cmd_string);

    // Toggle the hidden state back
    // _ui_flag_modify(ui_connect_button, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_os_select_dropdown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_command_dropdown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_status_spiner, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_status_label, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
}