get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
if(SIMULATION_BUILD)
    message(STATUS "[${LIBRARY_NAME}]: SIMULATION_BUILD is ENABLED")

    # List all the source files in the 'components' directory
    set(SRC_FILES
        "dsp.c" 
        "batch_absolute.c"
        "convert_helpers.c"
        "filter_float_470s_100c.c" 
        "filter_8x8x16_470s_100c.c" 
        "filter_16x16x40_470s_100c.c" 
        "filter_16x16x64_470s_100c.c" 
        "filter_32x32x64_470s_100c.c"
        "filter4_float_470s_100c.c"
        "filter4_32x32x64_470s_100c.c"
        "filter10c_float.c"
        "circular_integrator.c"
        "mag_hpf.c"
    )

    # In demo_component's CMakeLists.txt
    add_library(${LIBRARY_NAME} ${SRC_FILES})

    # Specify that demo_component depends on ComponentA
    target_link_libraries(${LIBRARY_NAME} PRIVATE DART_DATATYPE)

    # Include the custom include directory within 'DART_DATATYPE'
    target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

else()
    message(STATUS "[${LIBRARY_NAME}]: SIMULATION_BUILD is DISABLED")

    idf_component_register(
        
        # Add component sources    
        SRCS
            "dsp.c" 
            "batch_absolute.c"
            "convert_helpers.c"
            "filter_float_470s_100c.c" 
            "filter_8x8x16_470s_100c.c" 
            "filter_16x16x40_470s_100c.c" 
            "filter_16x16x64_470s_100c.c" 
            "filter_32x32x64_470s_100c.c"
            "filter4_float_470s_100c.c"
            "filter4_32x32x64_470s_100c.c"
            "filter10c_float.c"
            "circular_integrator.c"
            "mag_hpf.c"

        # Add component include locations
        INCLUDE_DIRS
            "include"

        # Add component public dependencies
        REQUIRES

        # Add component private dependencies
        PRIV_REQUIRES
    )

endif()
