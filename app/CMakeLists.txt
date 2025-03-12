project (app)

# Set target names for the executables
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    add_executable(app MACOSX_BUNDLE app.cpp)
    set_target_properties(app PROPERTIES
        OUTPUT_NAME ${APP_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${APP_DIR})
else()
    add_executable(app app.cpp)
    set_target_properties(app PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")
endif()

set_target_properties(app
    PROPERTIES
    ENABLE_EXPORTS TRUE)
