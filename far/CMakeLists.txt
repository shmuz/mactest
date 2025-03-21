project (far)

set(SOURCES
  far.cpp
  find_files.cpp
)

# Set target names for the executables
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    add_executable(far MACOSX_BUNDLE ${SOURCES})
    set_target_properties(far PROPERTIES
        OUTPUT_NAME ${APP_NAME}
        RUNTIME_OUTPUT_DIRECTORY ${APP_DIR})
else()
    add_executable(far ${SOURCES})
    set_target_properties(far PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")
endif()

add_dependencies(far winport)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET (WINPORT -force_load winport)
else()
    SET (WINPORT -Wl,--whole-archive winport -Wl,--no-whole-archive)
endif()

set_target_properties(far
    PROPERTIES
    ENABLE_EXPORTS TRUE)

if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    target_link_libraries(far
        PRIVATE ${WINPORT}
        PRIVATE c)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Haiku")
    target_link_libraries(far
        PRIVATE ${WINPORT}
        PRIVATE gnu)
else()
    target_link_libraries(far
        PRIVATE ${WINPORT}
        PRIVATE dl)
endif()
