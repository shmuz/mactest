project (luafar)

add_library(luafar SHARED luafar.cpp)

target_link_libraries(luafar far)

set_target_properties(luafar
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar"
    PREFIX ""
    SUFFIX ".so")
