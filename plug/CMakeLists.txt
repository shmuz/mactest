project (plug)

add_library(plug MODULE plug.cpp)

target_link_libraries(plug lib)

set_target_properties(plug
  PROPERTIES
    PREFIX ""
    SUFFIX ".far-plug-wide")
