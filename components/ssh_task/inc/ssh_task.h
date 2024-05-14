#ifndef _SSH_TASK_H
#define _SSH_TASK_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_err.h"

#define SSH_TASK_FINISH_BIT BIT4
#define SSH_TASK_FAIL_BIT   BIT5
#define SSH_CMD_SUCCESS_BIT BIT6

typedef struct ssh_task_input_t {
    EventGroupHandle_t xEventGroup;
    // Command tx buffer
    size_t tx_buffer_size;
    char * tx_buffer;
    // rx buffer
    size_t rx_buffer_size;
    char * rx_buffer;
} ssh_task_input_t;

esp_err_t create_ssh_task_input(ssh_task_input_t * task_parameters, char * tx_buffer, size_t tx_buffer_len, char * rx_buffer, size_t rx_buffer_len);
esp_err_t delete_ssh_task_input(ssh_task_input_t * task_parameters);
void ssh_task(void *pvParameters);
void ssh_shell_session(void *pvParameters);

/**
 * This is a helper that automates the creation of ssh task process
 *
 * @param command The command to be executed (string format) 
 *
 * @return Execution result (PASS/FAIL)
 *
 */
esp_err_t run_ssh_task_blocked(char * tx_buffer, size_t tx_buffer_len, char * rx_buffer, size_t rx_buffer_len );

/**
 * This is a helper that automates the creation of ssh shell session
 *
 * @return Execution result (PASS/FAIL)
 *
 */
esp_err_t run_ssh_shell_session_blocked(void);

#endif
