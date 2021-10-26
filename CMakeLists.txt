# Copyright (C) 2021 Chicken Escape authors

cmake_minimum_required(VERSION 3.10)

project(chicken-escape)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chicken-escape
    src/main.cpp
    src/game.cpp
    src/map.cpp
    src/sound.cpp)

target_link_libraries(chicken-escape allegro allegro_image)
target_link_libraries(chicken-escape allegro allegro_audio)
target_link_libraries(chicken-escape allegro allegro_acodec)

add_custom_command(TARGET chicken-escape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/img/ $<TARGET_FILE_DIR:chicken-escape>
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sfx/ $<TARGET_FILE_DIR:chicken-escape>)
