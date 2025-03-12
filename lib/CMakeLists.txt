project (lib)

add_library(lib SHARED lib.cpp)

target_link_libraries(lib app)

set_target_properties(lib
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar"
    PREFIX ""
    SUFFIX ".so")
