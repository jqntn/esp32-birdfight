cmake_minimum_required(VERSION 3.20)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

project(birdfight LANGUAGES CXX)

FetchContent_Declare(sdl URL "https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.26.tar.gz")
FetchContent_MakeAvailable(sdl)

set(PLATFORM "SDL" CACHE STRING "" FORCE)
set(GRAPHICS "GRAPHICS_API_OPENGL_11_SOFTWARE" CACHE STRING "" FORCE)

FetchContent_Declare(raylib URL "https://github.com/raysan5/raylib/archive/refs/heads/master.tar.gz")
FetchContent_MakeAvailable(raylib)

add_executable(birdfight)

set_property(TARGET birdfight PROPERTY CXX_STANDARD 20)

file(GLOB_RECURSE birdfight_src "src/*.cpp")
target_sources(birdfight PRIVATE "${birdfight_src}")

target_include_directories(birdfight PRIVATE "include")

target_link_libraries(birdfight PRIVATE raylib SDL3::SDL3)