project (luafar)

add_library(luafar SHARED luafar.cpp)

add_dependencies(luafar far)

target_link_libraries(luafar far winport)

set_target_properties(luafar
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar"
    PREFIX ""
    SUFFIX ".so")
