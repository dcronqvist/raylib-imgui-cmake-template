cmake_minimum_required(VERSION 3.15)
project(raylib-imgui-cmake-template VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    link_directories(libs/raylib-cpp/win)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    link_directories(libs/raylib-cpp/osx)
endif()

include_directories(libs)
include_directories(include)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(raylib-imgui-cmake-template ${SOURCES})

target_link_libraries(raylib-imgui-cmake-template raylib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(raylib-imgui-cmake-template winmm)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(raylib-imgui-cmake-template
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )
endif()