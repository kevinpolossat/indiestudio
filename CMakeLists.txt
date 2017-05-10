cmake_minimum_required(VERSION 3.7)

project(indiestudio CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(
        BUILD_DEPENDENCIES ${CMAKE_SOURCE_DIR}/build/dependencies
)

file(MAKE_DIRECTORY ${BUILD_DEPENDENCIES})

#set(Boost_DEBUG ON)

find_package(Irrlicht)
find_package(X11)
find_package(OpenGL)
find_package(GLUT)
find_package(ZLIB)
find_package(Boost 1.62)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${IRRLICHT_INCLUDE_DIR}
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

message(STATUS "boost found === ${Boost_FOUND}")
message(STATUS "boost lib === ${Boost_LIBRARIES}")
message(STATUS "boost lib dir === ${Boost_LIBRARY_DIRS}")
message(STATUS "boost include dir === ${Boost_INCLUDE_DIRS}")
message(STATUS ${PATHS})

add_executable(indiestudio ${SOURCE_FILES} ${HEADERS})

target_link_libraries(
        indiestudio
        ${IRRLICHT_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${X11_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${X11_Xxf86vm_LIB}
        ${Boost_LIBRARIES}
)

if (NOT IRRLICHT_FOUND)
add_dependencies(indiestudio Irrlicht)
endif (NOT IRRLICHT_FOUND)