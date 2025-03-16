project (far CXX C)

# Set target names for the executables
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    add_executable(far MACOSX_BUNDLE far.cpp)
    set_target_properties(far PROPERTIES
        OUTPUT_NAME ${APP_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${APP_DIR})
else()
    add_executable(far far.cpp)
    set_target_properties(far PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")
endif()

set_target_properties(far
    PROPERTIES
    ENABLE_EXPORTS TRUE)

add_custom_command(TARGET far
    POST_BUILD
    COMMAND "nm -D far"
)
