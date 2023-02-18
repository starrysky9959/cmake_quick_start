cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

# common settings
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# config third party
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(ThirdPartyConfig)

include_directories(src)

add_subdirectory(src) 

