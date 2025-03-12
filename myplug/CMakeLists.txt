project (myplug)

add_library(myplug MODULE myplug.cpp)

target_link_libraries(myplug lib)

set_target_properties(myplug
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${INSTALL_DIR}/Plugins/luafar/myplug/plug"
    PREFIX ""
    SUFFIX ".far-plug-wide")
