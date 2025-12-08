cmake_minimum_required(VERSION 3.25)
project(FPM LANGUAGES CXX)

add_library(fpm STATIC
    ../src/FPM.cpp
)

target_include_directories(fpm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(fpm PUBLIC cxx_std_20) 
