# Install script for directory: /home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/kevin/DevSpace/indiestudio/dependencies/assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3.3.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/code/libassimp.so.3.3.1"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/code/libassimp.so.3"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Build/assimp/code/libassimp.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3.3.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so.3"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/anim.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/ai_assert.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/camera.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/color4.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/color4.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/config.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/defs.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/cfileio.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/light.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/material.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/material.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/matrix3x3.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/matrix3x3.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/matrix4x4.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/matrix4x4.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/mesh.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/postprocess.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/quaternion.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/quaternion.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/scene.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/metadata.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/texture.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/types.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/vector2.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/vector2.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/vector3.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/vector3.inl"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/version.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/cimport.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/importerdesc.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/Importer.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/IOStream.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/IOSystem.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/Logger.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/LogStream.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/NullLogger.hpp"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/cexport.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/Exporter.hpp"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/home/kevin/DevSpace/indiestudio/dependencies/assimp_dl/Source/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

