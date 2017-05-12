include(ExternalProject)
ExternalProject_add(
        ZLIB
        PREFIX ${BUILD_DEPENDENCIES}/zlib
        URL http://prdownloads.sourceforge.net/libpng/zlib-1.2.11.tar.xz
        BUILD_IN_SOURCE 1
        SOURCE_DIR ${BUILD_DEPENDENCIES}/zlib/build
        INSTALL_COMMAND ""
)
ExternalProject_Get_Property(ZLIB install_dir)
if(WIN32)
    set(ZLIB_LIBRARIES "${BUILD_DEPENDENCIES}/zlib/build/zlib1.${link_library_suffix}")
else()
    set(ZLIB_LIBRARIES "${BUILD_DEPENDENCIES}/zlib/build/libz.${link_library_suffix}")
endif()
mark_as_advanced(ZLIB_LIBRARIES)