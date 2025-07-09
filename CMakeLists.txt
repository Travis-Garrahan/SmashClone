cmake_minimum_required(VERSION 3.30)
project(SmashClone)

set(CMAKE_CXX_STANDARD 20)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

# Download SDL2
CPMAddPackage(
        NAME SDL2
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG release-2.30.3
        SOURCE_DIR ${LIB_DIR}/sdl2
)

# Download raylib, build with SDL for input + audio
CPMAddPackage(
        NAME RAYLIB
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
        SOURCE_DIR ${LIB_DIR}/raylib
        OPTIONS
            "PLATFORM Desktop"
            "USE_INPUT SDL"
            "USE_AUDIO SDL"
            "USE_GRAPHICS GLFW"
)

CPMAddPackage(
        NAME IMGUI
        GITHUB_REPOSITORY ocornut/imgui
        VERSION 1.92.0
        SOURCE_DIR ${LIB_DIR}/imgui
)


add_subdirectory(app)
