cmake_minimum_required(VERSION 3.10)
project(game_of_life LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(FetchContent)

if(DEFINED ENV{CMAKE_LIBS_DIR})
    set(FETCHCONTENT_BASE_DIR "$ENV{CMAKE_LIBS_DIR}")
endif()

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)


add_executable(game_of_life
                            src/main.cpp
                            src/raywrap/Drawler.cpp
                            src/raywrap/Window.cpp
                            src/raywrap/Keyboard.cpp)

target_link_libraries(game_of_life PRIVATE raylib)
target_link_options(game_of_life PRIVATE -static)