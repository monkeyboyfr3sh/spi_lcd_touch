#pragma once

#include <esp_err.h>
#include "driver/i2c.h"

/* Enum representing the output data rate (ODR) settings for the accelerometer */
typedef enum {
    acc_odr_8000,      // Accelerometer ODR set to 8000 Hz.
    acc_odr_4000,      // Accelerometer ODR set to 4000 Hz.
    acc_odr_2000,      // Accelerometer ODR set to 2000 Hz.
    acc_odr_1000,      // Accelerometer ODR set to 1000 Hz.
    acc_odr_500,       // Accelerometer ODR set to 500 Hz.
    acc_odr_250,       // Accelerometer ODR set to 250 Hz.
    acc_odr_125,       // Accelerometer ODR set to 125 Hz.
    acc_odr_62_5,      // Accelerometer ODR set to 62.5 Hz.
    acc_odr_31_25,     // Accelerometer ODR set to 31.25 Hz.
    acc_odr_128 = 12,  // Accelerometer ODR set to 128 Hz.
    acc_odr_21,        // Accelerometer ODR set to 21 Hz.
    acc_odr_11,        // Accelerometer ODR set to 11 Hz.
    acc_odr_3,         // Accelerometer ODR set to 3 Hz.
} acc_odr_t;

/* Enum representing the output data rate (ODR) settings for the gyroscope */
typedef enum {
    gyro_odr_8000,     // Gyroscope ODR set to 8000 Hz.
    gyro_odr_4000,     // Gyroscope ODR set to 4000 Hz.
    gyro_odr_2000,     // Gyroscope ODR set to 2000 Hz.
    gyro_odr_1000,     // Gyroscope ODR set to 1000 Hz.
    gyro_odr_500,      // Gyroscope ODR set to 500 Hz.
    gyro_odr_250,      // Gyroscope ODR set to 250 Hz.
    gyro_odr_125,      // Gyroscope ODR set to 125 Hz.
    gyro_odr_62_5,     // Gyroscope ODR set to 62.5 Hz.
    gyro_odr_31_25,    // Gyroscope ODR set to 31.25 Hz.
} gyro_odr_t;

/* Enum representing the scale settings for the accelerometer */
typedef enum {
    acc_scale_2g = 0,    // Accelerometer scale set to ±2g.
    acc_scale_4g,        // Accelerometer scale set to ±4g.
    acc_scale_8g,        // Accelerometer scale set to ±8g.
    acc_scale_16g,       // Accelerometer scale set to ±16g.
} acc_scale_t;

/* Enum representing the scale settings for the gyroscope */
typedef enum {
    gyro_scale_16dps = 0,       // Gyroscope scale set to ±16 degrees per second.
    gyro_scale_32dps,            // Gyroscope scale set to ±32 degrees per second.
    gyro_scale_64dps,            // Gyroscope scale set to ±64 degrees per second.
    gyro_scale_128dps,           // Gyroscope scale set to ±128 degrees per second.
    gyro_scale_256dps,           // Gyroscope scale set to ±256 degrees per second.
    gyro_scale_512dps,           // Gyroscope scale set to ±512 degrees per second.
    gyro_scale_1024dps,          // Gyroscope scale set to ±1024 degrees per second.
    gyro_scale_2048dps,          // Gyroscope scale set to ±2048 degrees per second.
} gyro_scale_t;

/* Struct representing the axes data for accelerometer */
typedef struct {
    int16_t x;    // Accelerometer data along the x-axis.
    int16_t y;    // Accelerometer data along the y-axis.
    int16_t z;    // Accelerometer data along the z-axis.
} acc_axes_raw_t;

/* Struct representing the axes data for gyroscope */
typedef struct {
    int16_t x;    // Gyroscope data along the x-axis.
    int16_t y;    // Gyroscope data along the y-axis.
    int16_t z;    // Gyroscope data along the z-axis.
} gyro_axes_raw_t;

/* Struct representing the data read from Qmi8658c */
typedef struct {
    acc_axes_raw_t  acc_xyz;       // Accelerometer data in three axes (x, y, z).
    gyro_axes_raw_t gyro_xyz;      // Gyroscope data in three axes (x, y, z).
    float temperature;         // Temperature reading from Qmi8658c.
} qmi_data_raw_t;

/* Enum representing the mode of operation for Qmi8658c */
typedef enum {
    qmi8658_mode_acc_only = 1,   // Mode for accelerometer-only operation.
    qmi8658_mode_gyro_only,      // Mode for gyroscope-only operation.
    qmi8658_mode_dual,           // Mode for dual accelerometer and gyroscope operation.
} qmi8658_mode_t;

/* Qmi8658 config */

/* Struct representing the configuration settings for Qmi8658c */
typedef struct {
    qmi8658_mode_t qmi8658_mode;    // Mode of operation for Qmi8658c.
    acc_scale_t acc_scale;          // Scale setting for the accelerometer.
    acc_odr_t acc_odr;              // Output data rate (ODR) setting for the accelerometer.
    gyro_scale_t gyro_scale;        // Scale setting for the gyroscope.
    gyro_odr_t gyro_odr;            // Output data rate (ODR) setting for the gyroscope.
} qmi8658_cfg_t;

/* Enum representing the result of an operation with Qmi8658c */
typedef enum {
    qmi8658_result_open_success,   // Operation to open communication with Qmi8658c was successful.
    qmi8658_result_open_error,     // Error occurred while trying to open communication with Qmi8658c.
    qmi8658_result_close_success,  // Operation to close communication with Qmi8658c was successful.
    qmi8658_result_close_error,    // Error occurred while trying to close communication with Qmi8658c.
} qmi8658_result_t;

esp_err_t qmi8658_write_byte(i2c_port_t i2c_num, uint8_t reg_addr, uint8_t data);
esp_err_t qmi8658_write_bytes(i2c_port_t i2c_num, uint8_t start_addr, uint8_t *data, size_t len);
esp_err_t qmi8658_read_byte(i2c_port_t i2c_num, uint8_t reg_addr, uint8_t *data);
esp_err_t qmi8658_read_bytes(i2c_port_t i2c_num, uint8_t start_addr, uint8_t *data, size_t len);

esp_err_t qmi8658_read_sensor(i2c_port_t i2c_num, acc_axes_raw_t *acc);
