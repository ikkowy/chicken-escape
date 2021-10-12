# Copyright (C) 2021 Chicken Escape authors

cmake_minimum_required(VERSION 3.10)

project(chicken-escape)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(chicken-escape
    src/main.cpp
    src/game.cpp)

target_link_libraries(chicken-escape allegro allegro_image)

add_custom_command(TARGET chicken-escape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/img/ $<TARGET_FILE_DIR:chicken-escape>)
