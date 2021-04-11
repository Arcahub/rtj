cmake_minimum_required(VERSION 3.8)

project(rtj)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(rtj_SOURCES
    "include/rtj/json.hpp"
    "src/deserializer/deserializeri.cpp"
    "src/deserializer/deserializers.cpp"
    "src/json.cpp"
    "src/serializer.cpp"
)

add_library(rtj MODULE ${rtj_SOURCES})
target_include_directories(rtj PUBLIC include)
