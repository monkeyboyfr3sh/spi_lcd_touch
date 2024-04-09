#pragma once

#include "sdkconfig.h"
#include "driver/spi_master.h"

// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST
#define TOUCH_HOST  I2C_NUM_0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// LCD Config //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (80 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           10
#define EXAMPLE_PIN_NUM_MOSI           11
#define EXAMPLE_PIN_NUM_MISO           12
#define EXAMPLE_PIN_NUM_LCD_DC         8
#define EXAMPLE_PIN_NUM_LCD_RST        14
#define EXAMPLE_PIN_NUM_LCD_CS         9
#define EXAMPLE_PIN_NUM_BK_LIGHT       2
#define EXAMPLE_PIN_NUM_TOUCH_CS       -1
#define LCD_TOUCH_RST       GPIO_NUM_13
#define LCD_TOUCH_INT       GPIO_NUM_5


// The pixel number in horizontal and vertical
#if CONFIG_EXAMPLE_LCD_CONTROLLER_ILI9341
#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              320
#elif CONFIG_EXAMPLE_LCD_CONTROLLER_GC9A01
#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              240
#endif

// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8

// I2C Configuration
#define I2C_MASTER_SCL_IO           7        // GPIO number for I2C master clock
#define I2C_MASTER_SDA_IO           6        // GPIO number for I2C master data
#define I2C_MASTER_NUM              I2C_NUM_0 // I2C port number for master dev
#define I2C_MASTER_TX_BUF_DISABLE   0         // I2C master no buffer needed
#define I2C_MASTER_RX_BUF_DISABLE   0         // I2C master no buffer needed
#define I2C_MASTER_FREQ_HZ          400000    // I2C master clock frequency
