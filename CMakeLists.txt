cmake_minimum_required(VERSION 3.20)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(ESP32 ON)

project(birdfight LANGUAGES CXX)

FetchContent_Declare(raylib URL "https://github.com/raysan5/raylib/archive/refs/heads/master.tar.gz")
FetchContent_MakeAvailable(raylib)

add_executable(birdfight)

set_property(TARGET birdfight PROPERTY CXX_STANDARD 23)

file(GLOB_RECURSE birdfight_src "src/*.cpp")
target_sources(birdfight PRIVATE "${birdfight_src}")

target_include_directories(birdfight PRIVATE "include")

target_link_libraries(birdfight PRIVATE raylib)

if(ESP32)
  target_compile_definitions(birdfight PRIVATE ESP32)
  target_compile_definitions(raylib PRIVATE
    GRAPHICS_API_OPENGL_11_SOFTWARE
    SUPPORT_CUSTOM_FRAME_CONTROL
    SW_GL_FRAMEBUFFER_COPY_BGRA=0
    #SW_COLOR_BUFFER_BITS=16
    #SW_DEPTH_BUFFER_BITS=16
  )
  get_target_property(raylib_cdefs raylib COMPILE_DEFINITIONS)
  list(FILTER raylib_cdefs EXCLUDE REGEX [[^PLATFORM_DESKTOP$]])
  set_property(TARGET raylib PROPERTY COMPILE_DEFINITIONS ${raylib_cdefs})
endif()