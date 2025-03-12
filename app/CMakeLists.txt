project (app)

add_executable(app app.cpp)

set_target_properties(app
    PROPERTIES
    ENABLE_EXPORTS TRUE)
