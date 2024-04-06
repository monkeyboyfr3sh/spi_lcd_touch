get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# List all the source files
set(COMMON_SRC_FILES
    "filter_helpers.c" 
    "batch_absolute.c"
    "datatype_convert_helpers.c"
    "filter10c_float.c"
    "circular_integrator.c"
)

if(SIMULATION_BUILD)
    message(STATUS "[${LIBRARY_NAME}]: SIMULATION_BUILD is ENABLED")

    # In demo_component's CMakeLists.txt
    add_library(${LIBRARY_NAME} ${COMMON_SRC_FILES})

    # Specify that depedent libraries
    target_link_libraries(${LIBRARY_NAME} PRIVATE
        
    )

    # Include the include directory within dependent libraries
    target_include_directories( ${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

else()
    message(STATUS "[${LIBRARY_NAME}]: SIMULATION_BUILD is DISABLED")

    idf_component_register(
        
        # Add component sources    
        SRCS
            ${COMMON_SRC_FILES}

        # Add component include locations
        INCLUDE_DIRS 
            "include"

        # Add component public dependencies
        REQUIRES

        # Add component private dependencies
        PRIV_REQUIRES
    )

endif()
