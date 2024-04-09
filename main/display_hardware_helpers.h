#pragma once

void initialize_display_drivers(void);
void config_pwm(void);

void set_backlight_brightness(float brightness);
float get_backlight_brightness(void);
