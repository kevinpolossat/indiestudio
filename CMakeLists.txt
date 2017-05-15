cmake_minimum_required(VERSION 3.5.1)

project(indiestudio CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(
        BUILD_DEPENDENCIES ${CMAKE_SOURCE_DIR}/build/dependencies
)

file(MAKE_DIRECTORY ${BUILD_DEPENDENCIES})

set(BOOST_REQUESTED_VERSION 1.62.0)
set(ZLIB_ROOT ${BUILD_DEPENDENCIES}/zlib/build/)

find_package(Irrlicht)
find_package(X11)
find_package(OpenGL)
find_package(GLUT)
find_package(ZLIB)
find_package(Boost COMPONENTS serialization system)


set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${IRRLICHT_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIRS}
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
        ${IRRLICHT_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${X11_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${X11_Xxf86vm_LIB}
        ${BOOST_LIBRARIES}
)

if (NOT IRRLICHT_FOUND)
add_dependencies(indiestudio Irrlicht)
endif (NOT IRRLICHT_FOUND)

if (NOT BOOST_FOUND)
add_dependencies(indiestudio Boost)
endif (NOT BOOST_FOUND)

if (NOT ZLIB_FOUND)
include(External_ZLIB)
endif(NOT ZLIB_FOUND)
