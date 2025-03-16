cmake_minimum_required (VERSION 3.10)

project (far)

message(STATUS "==> CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")

set(APP_NAME "far")

include_directories(include)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(APP_DIR ${CMAKE_BINARY_DIR}/install)
    set(INSTALL_DIR ${APP_DIR}/${APP_NAME}.app/Contents/MacOS)
    set(EXECUTABLE_NAME ${APP_NAME})
else()
    set(INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
    set(EXECUTABLE_NAME far)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--gc-sections")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--gc-sections")
    endif()
endif()

add_subdirectory (far)
add_subdirectory (luafar)
add_subdirectory (myplug)
