# List all the source files
set(MAIN_SRC_FILES
    "main.c"
    "lvgl_ui.c"
    "lvgl_drive_task.c"
)

idf_component_register(

    SRCS 
        ${MAIN_SRC_FILES}
    
    INCLUDE_DIRS
        "."
)
