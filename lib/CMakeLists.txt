project (lib)

add_library(lib SHARED lib.cpp)

target_link_libraries(lib app)
