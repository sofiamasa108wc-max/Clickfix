cmake_minimum_required(VERSION 3.21)
project(ClickFix VERSION 0.1.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK environment variable is not set. Install the Geode SDK first.")
endif()

include($ENV{GEODE_SDK}/cmake/Geode.cmake)
setup_geode_mod(${PROJECT_NAME})
