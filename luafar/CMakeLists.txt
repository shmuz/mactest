project (luafar)

add_library(${PROJECT_NAME} SHARED lf_luafar.cpp)

add_dependencies(${PROJECT_NAME} far)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBLUA_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} far winport)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar"
    PREFIX ""
    SUFFIX ".so")
