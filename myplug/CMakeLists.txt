project (myplug)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/luafar/luaplug.c
)

add_library(${PROJECT_NAME} MODULE ${SOURCES})

include_directories(${LIBLUA_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} luafar)

set(INSTALL_DIR "${INSTALL_DIR}/Plugins/luafar/${PROJECT_NAME}")

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/plug"
    PREFIX ""
    SUFFIX ".far-plug-wide"
)

set(MY_LIST
  myplug.lua
)

foreach(elem ${MY_LIST})
  configure_file("src/${elem}" "${INSTALL_DIR}/plug/${elem}" COPYONLY)
endforeach()
