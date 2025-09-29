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
    rayplus
    GIT_REPOSITORY https://github.com/rkc137/rayplus.git
    GIT_TAG 5716eee9aca88d7ba8d590c47a5a62a22d0cf09d
)
FetchContent_MakeAvailable(rayplus)


add_executable(game_of_life src/main.cpp)

target_link_libraries(game_of_life PRIVATE rayplus)
target_link_options(game_of_life PRIVATE -static)