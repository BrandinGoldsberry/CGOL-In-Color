cmake_minimum_required(VERSION 3.10)

# set the project name
project(GOL VERSION 1.0)

configure_file(Headers/GOLConfig.h.in Headers/GOLConfig.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

set(SOURCE_FILES 
    Source/main.cpp
    Source/Life.cpp
    Headers/Life.hpp
    Headers/GOLConfig.h
)

include_directories(Source)
include_directories(Headers)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS REQUIRED audio network graphics window system)
if(NOT SFML_FOUND)
  message(FATAL_ERROR "SFML couldn't be located!")
endif()
add_executable(GOL ${SOURCE_FILES})
target_link_libraries(GOL sfml-audio sfml-network sfml-graphics sfml-window sfml-system)