project (mylib CXX C)

add_library(mylib SHARED mylib.cpp)

target_link_libraries(mylib far)

set_target_properties(mylib
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/mylib"
    PREFIX ""
    SUFFIX ".so")
