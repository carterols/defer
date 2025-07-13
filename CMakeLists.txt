cmake_minimum_required(VERSION 3.17)

project(defer
  LANGUAGES CXX
  VERSION 0.1
)

add_library(defer STATIC)
target_sources(defer
  PRIVATE
    defer.cpp
    include/defer/defer.hpp
)
target_include_directories(defer
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(defer PUBLIC cxx_std_17)

