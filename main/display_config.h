#pragma once

#include "sdkconfig.h"
#include "driver/spi_master.h"

// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// LCD Config //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (80 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           10
#define EXAMPLE_PIN_NUM_MOSI           11
#define EXAMPLE_PIN_NUM_MISO           -1
#define EXAMPLE_PIN_NUM_LCD_DC         8
#define EXAMPLE_PIN_NUM_LCD_RST        12
#define EXAMPLE_PIN_NUM_LCD_CS         9
#define EXAMPLE_PIN_NUM_BK_LIGHT       40
#define EXAMPLE_PIN_NUM_TOUCH_CS       -1

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