cmake_minimum_required(VERSION 3.30)

add_executable(SmashClone
        src/main.cpp
        src/animation.cpp
        include/animation.h
        src/input.cpp
        include/input.h
        src/player.cpp
        include/player.h
        include/states.h
        src/states.cpp
        src/game.cpp
        include/game.h
        include/collisions.h
  )


# include app's own headers
target_include_directories(SmashClone
        PRIVATE
        include
)

# external includes
target_include_directories(SmashClone
        PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/imgui
        ${CMAKE_SOURCE_DIR}/libs/imgui/backends
        ${CMAKE_SOURCE_DIR}/libs/raylib
        ${CMAKE_SOURCE_DIR}/app/thirdparty/rlImGui
)



# main app source
target_sources(SmashClone
    PRIVATE
        src/main.cpp
)

# Add source files from imgui
target_sources(SmashClone
    PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp
)

target_sources(SmashClone
    PRIVATE
        ${CMAKE_SOURCE_DIR}/app/thirdparty/rlImGui/rlImGui.cpp
)

target_link_libraries(SmashClone
    PRIVATE
        raylib
        nlohmann_json::nlohmann_json
)

