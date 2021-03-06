cmake_minimum_required(VERSION 3.5.1)

project(indiestudio CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(BUILD_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies)

if (WIN32)
    set(BUILD_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies/windows)
endif (WIN32)

if (UNIX)
    set(BUILD_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies/linux)
endif (UNIX)

set(INCLUDE_DEPENDENCIES ${CMAKE_SOURCE_DIR}/dependencies/include)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

file(MAKE_DIRECTORY ${BUILD_DEPENDENCIES})

set(BOOST_REQUESTED_VERSION 1.62.0)

find_library(
        IRRLICHT_LIBRARY
        Irrlicht
        HINTS ${BUILD_DEPENDENCIES}/irrlicht/lib
)

find_path(
        LUABRIDGE_INCLUDE_DIR
        LuaBridge.h
        HINTS ${INCLUDE_DEPENDENCIES}/LuaBridge
)

find_path(
        IRRLICHT_INCLUDE_DIR
        irrlicht.h
        HINTS ${INCLUDE_DEPENDENCIES}/irrlicht
)

find_path(
        ASSIMP_INCLUDE_DIR
        assimp/scene.h
        HINTS ${INCLUDE_DEPENDENCIES}
)

find_library(
        SFML_AUDIO_LIB
        sfml-audio
        HINTS ${BUILD_DEPENDENCIES}/sfml/lib
)

find_library(
        SFML_SYSTEM_LIB
        sfml-system
        HINTS ${BUILD_DEPENDENCIES}/sfml/lib
)

find_library(
        ASSIMP_LIBRARY
        assimp
        HINTS ${BUILD_DEPENDENCIES}/assimp
)

find_path(
        LUA_INCLUDE_DIR
        lua.h
        HINTS ${INCLUDE_DEPENDENCIES}/lua
)

find_library(
        LUA_LIBRARY
        lua
        HINTS ${BUILD_DEPENDENCIES}/lua
)

find_package(Boost COMPONENTS serialization system filesystem thread REQUIRED)
find_package(Threads)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-DSOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(SOURCE_FOLDER ${CMAKE_SOURCE_DIR}/src)

include_directories(
        SYSTEM
        ${IRRLICHT_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIR}
        ${LUA_INCLUDE_DIR}
        ${LUABRIDGE_INCLUDE_DIR}
)

include_directories(
        ${SOURCE_FOLDER}/Scenes
        ${SOURCE_FOLDER}/BomberMan
        ${SOURCE_FOLDER}/Core
        ${SOURCE_FOLDER}/Animations
        ${SOURCE_FOLDER}/IrrAssimp
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

if (UNIX)
    find_package(X11)
    find_package(OpenGL)
    find_package(GLUT)
    find_package(ZLIB)

    target_link_libraries(
            indiestudio
            ${IRRLICHT_LIBRARY}
            ${OPENGL_LIBRARIES}
            ${GLUT_LIBRARIES}
            ${X11_LIBRARIES}
            ${ZLIB_LIBRARIES}
            ${X11_Xxf86vm_LIB}
            ${Boost_LIBRARIES}
            ${SFML_AUDIO_LIB}
            ${SFML_SYSTEM_LIB}
            ${CMAKE_THREAD_LIBS_INIT}
            ${ASSIMP_LIBRARY}
            ${LUA_LIBRARY}
            dl
    )
endif (UNIX)