# Copyright (C) 2021 Chicken Escape authors

cmake_minimum_required(VERSION 3.10)

project(chicken-escape)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chicken-escape
    src/main.cpp)

target_link_libraries(chicken-escape ${SDL2_LIBRARIES})
