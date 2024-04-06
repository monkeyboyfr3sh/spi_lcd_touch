# List all the source files
set(MAIN_SRC_FILES
    "spi_lcd_touch_example_main.c"
    "lvgl_demo_ui.c"
    "lvgl_drive_task.c"
)

idf_component_register(

    SRCS 
        ${MAIN_SRC_FILES}

    
    INCLUDE_DIRS
        "."
)
