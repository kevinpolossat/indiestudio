cmake_minimum_required(VERSION 3.7)

project(indiestudio CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Irrlicht)

set(CMAKE_CXX_STANDARD 14)

set(
        CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
                        -O3"
)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
)

file(
        GLOB_RECURSE
        SOURCE_FILES
        ./src/*.cpp
)

file(
        GLOB_RECURSE
        HEADERS
        ./src/*.hh
)

add_executable(indiestudio ${SOURCE_FILES} ${HEADERS})