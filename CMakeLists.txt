cmake_minimum_required(VERSION 3.5.1)

project(indiestudio CXX)

find_package(X11)
find_package(OpenGL)
find_package(ZLIB)

set(CMAKE_CXX_STANDARD 14)

set(
        CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
                        -O3"
)

set(
    DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/dependencies
)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${DEPENDENCIES_DIR}/include
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

target_link_libraries(
        indiestudio
        ${X11_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${ZLIB_LIBRARIES}
        "${DEPENDENCIES_DIR}/lib/libIrrlicht.a"
        -lGL -lXxf86vm -lXext -lX11 -lpthread -ldl
)
