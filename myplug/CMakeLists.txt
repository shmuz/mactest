project (myplug)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/luafar/luaplug.c
)

add_library(${PROJECT_NAME} MODULE ${SOURCES})

include_directories(${LIBLUA_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} luafar)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar/myplug/plug"
    PREFIX ""
    SUFFIX ".far-plug-wide"
)
