cmake_minimum_required(VERSION 3.30)
project(SmashClone)

set(CMAKE_CXX_STANDARD 20)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

CPMAddPackage(
        NAME RAYLIB
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
        SOURCE_DIR ${LIB_DIR}/raylib
)

add_subdirectory(app)
