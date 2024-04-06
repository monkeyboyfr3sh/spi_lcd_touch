#pragma once

#include "freertos/FreeRTOS.h"

#define QMI8658_TIMEOUT              pdMS_TO_TICKS(1000)

// QMI8658 I2C Address
#define QMI8658_ADDR                0x6B      // I2C address of QMI8658 IMU

/* General purpose registers */
#define QMI8658_WHO_AM_I    0x00  // WHO_AM_I register address.
#define QMI8658_REVISION    0x01  // REVISION register address.

/* Setup and control registers */
#define QMI8658_CTRL1       0x02  // Control register 1 address.
#define QMI8658_CTRL2       0x03  // Control register 2 address.
#define QMI8658_CTRL3       0x04  // Control register 3 address.
#define QMI8658_CTRL4       0x05  // Control register 4 address.
#define QMI8658_CTRL5       0x06  // Control register 5 address.
#define QMI8658_CTRL6       0x07  // Control register 6 address.
#define QMI8658_CTRL7       0x08  // Control register 7 address.
#define QMI8658_CTRL9       0x0A  // Control register 9 address.

/* Data output registers */

// Accelerometer
#define QMI8658_ACC_X_L     0x35  // Accelerometer X-axis low byte.
#define QMI8658_ACC_X_H     0x36  // Accelerometer X-axis high byte.
#define QMI8658_ACC_Y_L     0x37  // Accelerometer Y-axis low byte.
#define QMI8658_ACC_Y_H     0x38  // Accelerometer Y-axis high byte.
#define QMI8658_ACC_Z_L     0x39  // Accelerometer Z-axis low byte.
#define QMI8658_ACC_Z_H     0x3A  // Accelerometer Z-axis high byte.

// Gyroscope
#define QMI8658_GYR_X_L     0x3B  // Gyroscope X-axis low byte.
#define QMI8658_GYR_X_H     0x3C  // Gyroscope X-axis high byte.
#define QMI8658_GYR_Y_L     0x3D  // Gyroscope Y-axis low byte.
#define QMI8658_GYR_Y_H     0x3E  // Gyroscope Y-axis high byte.
#define QMI8658_GYR_Z_L     0x3F  // Gyroscope Z-axis low byte.
#define QMI8658_GYR_Z_H     0x40  // Gyroscope Z-axis high byte.

// Temperature sensor
#define QMI8658_TEMP_L      0x33  // Temperature sensor low byte.
#define QMI8658_TEMP_H      0x34  // Temperature sensor high byte.

/* Soft reset register */
#define QMI8658_RESET       0x60  // Soft reset register address.

/* define scale sensitivity */
/* Accelerometer scale sensitivity values for different gravity ranges */
#define ACC_SCALE_SENSITIVITY_2G        (1 << 14)  // Sensitivity for ±2g range.
#define ACC_SCALE_SENSITIVITY_4G        (1 << 13)  // Sensitivity for ±4g range.
#define ACC_SCALE_SENSITIVITY_8G        (1 << 12)  // Sensitivity for ±8g range.
#define ACC_SCALE_SENSITIVITY_16G       (1 << 11)  // Sensitivity for ±16g range.

/* Gyroscope scale sensitivity values for different degrees per second ranges */
#define GYRO_SCALE_SENSITIVITY_16DPS    (1 << 11)  // Sensitivity for ±16 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_32DPS    (1 << 10)  // Sensitivity for ±32 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_64DPS    (1 << 9 )  // Sensitivity for ±64 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_128DPS   (1 << 8 )  // Sensitivity for ±128 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_256DPS   (1 << 7 )  // Sensitivity for ±256 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_512DPS   (1 << 6 )  // Sensitivity for ±512 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_1024DPS  (1 << 5 )  // Sensitivity for ±1024 degrees per second range.
#define GYRO_SCALE_SENSITIVITY_2048DPS  (1 << 4 )  // Sensitivity for ±2048 degrees per second range.

/* Temperature sensor resolution */
#define TEMPERATURE_SENSOR_RESOLUTION   (1 << 8 )  // Telperature sensor resolution (ADC)