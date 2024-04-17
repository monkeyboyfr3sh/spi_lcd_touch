#include "lvgl.h"
#include <stdio.h>

#include "ssh_task.h"
#include "ui.h"

#include "esp_log.h"

static const char * TAG = "screen_2_cb";

void win11_dev_start_clicked_cb(lv_event_t * e)
{
    const size_t ssh_string_len = 64;
    
    // Form ssh string
    char ssh_cmd_string[ssh_string_len];
    snprintf(ssh_cmd_string, ssh_string_len, 
        "qm start 100;");
    // Run the ssh task
    run_ssh_task_blocked(ssh_cmd_string);

    // Form check ssh string
    char ssh_read_cmd_string[ssh_string_len];
    snprintf(ssh_read_cmd_string, ssh_string_len, 
        "qm list | awk '$2 == \"ZorinDev\" {print $3}';");
    // Run the ssh task
    run_ssh_task_blocked(ssh_read_cmd_string);
}

void win11_dev_stop_clicked_cb(lv_event_t * e)
{
    // Form ssh string
    const size_t ssh_string_len = 64;
    char ssh_cmd_string[ssh_string_len];
    snprintf(ssh_cmd_string, ssh_string_len, 
        "qm stop 100;");
    
    // Run the ssh task
    run_ssh_task_blocked(ssh_cmd_string);
}