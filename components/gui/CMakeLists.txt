idf_component_register(
    SRCS
        generated_component/screens/ui_Screen1.c
        generated_component/screens/ui_Screen2.c
        generated_component/ui.c
        generated_component/components/ui_comp_hook.c
        generated_component/ui_helpers.c
        # generated_component/ui_events.c

    INCLUDE_DIRS 
        "include"
        "generated_component"

    REQUIRES
        driver
        lvgl
        
    PRIV_REQUIRES
    
)
