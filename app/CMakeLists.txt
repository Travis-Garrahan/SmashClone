cmake_minimum_required(VERSION 3.30)

add_executable(SmashClone
        src/main.cpp
        src/animation.cpp
        include/animation.h
)

target_sources(SmashClone
    PRIVATE
        src/main.cpp
)

target_include_directories(SmashClone
    PRIVATE
        include
)

target_link_libraries(SmashClone
    PRIVATE
        raylib
)