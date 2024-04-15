#include "lvgl.h"
#include <stdio.h>

#include "ssh_task.h"
#include "ui.h"

#include "esp_log.h"

static const char * TAG = "screen_2_cb";

void connect_button_clicked_cb(lv_event_t * e)
{
    char * cmd = "qm list";
    run_ssh_task_blocked(cmd);

    // Toggle the hidden state back
    // _ui_flag_modify(ui_connect_button, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_os_select_dropdown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_command_dropdown, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_status_spiner, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
    // _ui_flag_modify(ui_status_label, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_TOGGLE);
}