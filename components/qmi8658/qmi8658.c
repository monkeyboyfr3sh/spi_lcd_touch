#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <esp_log.h>

#include "qmi8658.h"
#include "qmi8658_def.h"

static const char *TAG = "qmi8658-dr";

// Function to read a single byte from the QMI8658
esp_err_t qmi8658_write_byte(i2c_port_t i2c_num, uint8_t reg_addr, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (QMI8658_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, QMI8658_TIMEOUT);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t qmi8658_write_bytes(i2c_port_t i2c_num, uint8_t start_addr, uint8_t *data, size_t len)
{
    if (len == 0) return ESP_OK; // No need to write anything

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (QMI8658_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, start_addr, true); // Start from the specified register address
    i2c_master_write(cmd, data, len, true); // Write all bytes in data buffer
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, QMI8658_TIMEOUT);
    i2c_cmd_link_delete(cmd);
    return ret;
}

// Function to read a single byte from the QMI8658
esp_err_t qmi8658_read_byte(i2c_port_t i2c_num, uint8_t reg_addr, uint8_t *data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (QMI8658_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (QMI8658_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, data, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, QMI8658_TIMEOUT);
    i2c_cmd_link_delete(cmd);
    return ret;
}

// Function to read multiple bytes from the QMI8658
esp_err_t qmi8658_read_bytes(i2c_port_t i2c_num, uint8_t start_addr, uint8_t *data, size_t len)
{
    if (len == 0) return ESP_OK; // No need to read anything

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (QMI8658_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, start_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (QMI8658_ADDR << 1) | I2C_MASTER_READ, true);
    if (len > 1) {
        i2c_master_read(cmd, data, len - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, data + len - 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, QMI8658_TIMEOUT);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t qmi8658_configure(i2c_port_t i2c_num, qmi8658_cfg_t cfg)
{
    return ESP_OK;
}

esp_err_t qmi8658_read_accelerometer(i2c_port_t i2c_num, acc_axes_raw_t *acc)
{

    uint8_t acc_x_hi, acc_x_lo;
    uint8_t acc_y_hi, acc_y_lo;
    uint8_t acc_z_hi, acc_z_lo;

    qmi8658_read_byte(i2c_num, QMI8658_ACC_X_H, &acc_x_hi);
    qmi8658_read_byte(i2c_num, QMI8658_ACC_X_L, &acc_x_lo);
    
    qmi8658_read_byte(i2c_num, QMI8658_ACC_Y_H, &acc_y_hi);
    qmi8658_read_byte(i2c_num, QMI8658_ACC_Y_L, &acc_y_lo);

    qmi8658_read_byte(i2c_num, QMI8658_ACC_Z_H, &acc_z_hi);
    qmi8658_read_byte(i2c_num, QMI8658_ACC_Z_L, &acc_z_lo);

    acc->x = (((int16_t)(acc_x_hi << 8)) | ((int16_t)(acc_x_lo << 0)));
    acc->y = (((int16_t)(acc_y_hi << 8)) | ((int16_t)(acc_y_lo << 0)));
    acc->z = (((int16_t)(acc_z_hi << 8)) | ((int16_t)(acc_z_lo << 0)));


    return ESP_OK;
}

esp_err_t qmi8658_read_gyro(i2c_port_t i2c_num, gyro_axes_raw_t *gyro)
{

    uint8_t gyro_x_hi, gyro_x_lo;
    uint8_t gyro_y_hi, gyro_y_lo;
    uint8_t gyro_z_hi, gyro_z_lo;

    qmi8658_read_byte(i2c_num, QMI8658_ACC_X_H, &gyro_x_hi);
    qmi8658_read_byte(i2c_num, QMI8658_ACC_X_L, &gyro_x_lo);
    
    qmi8658_read_byte(i2c_num, QMI8658_ACC_Y_H, &gyro_y_hi);
    qmi8658_read_byte(i2c_num, QMI8658_ACC_Y_L, &gyro_y_lo);

    qmi8658_read_byte(i2c_num, QMI8658_ACC_Z_H, &gyro_z_hi);
    qmi8658_read_byte(i2c_num, QMI8658_ACC_Z_L, &gyro_z_lo);

    gyro->x = (((int16_t)(gyro_x_hi << 8)) | ((int16_t)(gyro_x_lo << 0)));
    gyro->y = (((int16_t)(gyro_y_hi << 8)) | ((int16_t)(gyro_y_lo << 0)));
    gyro->z = (((int16_t)(gyro_z_hi << 8)) | ((int16_t)(gyro_z_lo << 0)));

    return ESP_OK;
}

esp_err_t qmi8658_read_temperature(i2c_port_t i2c_num, int16_t *temp)
{
    // read temperature data
    uint8_t temp_hi, temp_lo;
    qmi8658_read_byte(i2c_num, QMI8658_TEMP_H, &temp_hi);
    qmi8658_read_byte(i2c_num, QMI8658_TEMP_L, &temp_lo);

    *temp = (((int16_t)(temp_hi << 8)) | ((int16_t)(temp_lo << 0)));

    return ESP_OK;    
}