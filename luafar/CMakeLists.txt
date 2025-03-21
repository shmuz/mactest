project (luafar)

set(SOURCES
  src/lf_service.cpp
  src/lf_exported.cpp
  src/lf_bit64.c
  src/lf_utf8lib.c
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBLUA_INCLUDE_DIRS})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(${PROJECT_NAME} winport ${LIBLUA_LIBRARIES})
else()
  target_link_libraries(${PROJECT_NAME} far winport)
endif()

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar"
    PREFIX ""
    SUFFIX ".so")
