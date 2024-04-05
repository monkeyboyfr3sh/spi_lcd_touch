#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <esp_log.h>

#include "qmi8658.h"
#include "qmi8658_def.h"

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

esp_err_t qmi8658_read_sensor(i2c_port_t i2c_num, acc_axes_raw_t *acc)
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

    // // read accelerometer data
    // int16_t acc_x = (((int16_t)qmi8658_read(QMI8658_ACC_X_H) << 8) | this->qmi8658_read(QMI8658_ACC_X_L));
    // int16_t acc_y = (((int16_t)this->qmi8658_read(QMI8658_ACC_Y_H) << 8) | this->qmi8658_read(QMI8658_ACC_Y_L));
    // int16_t acc_z = (((int16_t)this->qmi8658_read(QMI8658_ACC_Z_H) << 8) | this->qmi8658_read(QMI8658_ACC_Z_L));
    // data->acc_xyz.x = (float)acc_x/qmi_ctx.acc_sensitivity;
    // data->acc_xyz.y = (float)acc_y/qmi_ctx.acc_sensitivity;
    // data->acc_xyz.z = (float)acc_z/qmi_ctx.acc_sensitivity;

    // // read gyroscope data
    // int16_t rot_x = (((int16_t)this->qmi8658_read(QMI8658_GYR_X_H) << 8) | this->qmi8658_read(QMI8658_GYR_X_L));
    // int16_t rot_y = (((int16_t)this->qmi8658_read(QMI8658_GYR_Y_H) << 8) | this->qmi8658_read(QMI8658_GYR_Y_L));
    // int16_t rot_z = (((int16_t)this->qmi8658_read(QMI8658_GYR_Z_H) << 8) | this->qmi8658_read(QMI8658_GYR_Z_L));
    // data->gyro_xyz.x = (float)rot_x/qmi_ctx.gyro_sensitivity;
    // data->gyro_xyz.y = (float)rot_y/qmi_ctx.gyro_sensitivity;
    // data->gyro_xyz.z = (float)rot_z/qmi_ctx.gyro_sensitivity;

    // // read temperature data
    // int16_t temp = (((int16_t)this->qmi8658_read(QMI8658_TEMP_H) << 8) | this->qmi8658_read(QMI8658_TEMP_L));
    // data->temperature = (float)temp/TEMPERATURE_SENSOR_RESOLUTION;
    return ESP_OK;
}