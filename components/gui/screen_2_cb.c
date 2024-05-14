#include "lvgl.h"
#include <stdio.h>

#include "ssh_task.h"
#include "ui.h"

#include "esp_log.h"

static const char * TAG = "screen_2_cb";
    
void win11_dev_start_clicked_cb(lv_event_t * e)
{
    const size_t ssh_string_len = 64;
	char tx_buff[ssh_string_len];
	char rx_buff[ssh_string_len];

    // Form ssh string
    snprintf(tx_buff, ssh_string_len, 
        "qm start 100;");
    // Run the ssh task
    run_ssh_task_blocked(tx_buff, ssh_string_len, rx_buff, ssh_string_len);

    // Form check ssh string
    snprintf(tx_buff, ssh_string_len, 
        "qm list | awk '$2 == \"ZorinDev\" {print $3}';");
    // Run the ssh task
    run_ssh_task_blocked(tx_buff, ssh_string_len, rx_buff, ssh_string_len);
}

void win11_dev_stop_clicked_cb(lv_event_t * e)
{
    const size_t ssh_string_len = 64;
	char tx_buff[ssh_string_len];
	char rx_buff[ssh_string_len];

    snprintf(tx_buff, ssh_string_len, 
        "qm stop 100;");
    
    // Run the ssh task
    run_ssh_task_blocked(tx_buff, ssh_string_len, rx_buff, ssh_string_len);
}