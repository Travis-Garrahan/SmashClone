cmake_minimum_required(VERSION 3.30)
project(SmashClone)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

CPMAddPackage(
        NAME RAYLIB
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
        SOURCE_DIR ${LIB_DIR}/raylib
        OPTIONS
            "PLATFORM Desktop"
            "USE_GRAPHICS GLFW"
)

CPMAddPackage(
        NAME IMGUI
        GITHUB_REPOSITORY ocornut/imgui
        VERSION 1.92.0
        SOURCE_DIR ${LIB_DIR}/imgui
)

CPMAddPackage("gh:nlohmann/json@3.12.0")

add_subdirectory(app)
