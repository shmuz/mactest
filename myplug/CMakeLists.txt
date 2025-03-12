project (myplug)

add_library(myplug MODULE myplug.cpp)

target_link_libraries(myplug mylib)

set_target_properties(myplug
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/mylib/myplug/plug"
    PREFIX ""
    SUFFIX ".far-plug-wide")
