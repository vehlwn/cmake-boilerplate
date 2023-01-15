cmake_minimum_required(VERSION 3.16)

project(Boilerplate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

option(USE_CONAN "Use Conan to install dependencies" OFF)
if(USE_CONAN)
    message(STATUS "Using Conan")
    set(CONAN_SYSTEM_INCLUDES ON)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

include(CMakePrintHelpers)
include(cmake/HardenCxxFlags.cmake)
add_subdirectory(src)
