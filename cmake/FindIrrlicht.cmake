find_path(IRRLICHT_INCLUDE_DIR irrlicht/irrlicht.h
        PATHS $ENV{IRRDIR}/include
        PATH_SUFFIXES irrlicht
        )

message(STATUS "IRRLICHT_INCLUDE_DIR = ${IRRLICHT_INCLUDE_DIR}")

find_library(IRRLICHT_LIBRARY NAMES Irrlicht
        PATHS $ENV{IRRDIR}/lib
        )

message(STATUS "IRRLICHT_LIBRARY = ${IRRLICHT_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set IRRLICHT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IRRLICHT DEFAULT_MSG IRRLICHT_LIBRARY IRRLICHT_INCLUDE_DIR)

IF(IRRLICHT_FOUND)
    set(IRRLICHT_LIBRARIES ${IRRLICHT_LIBRARY})
ELSE(IRRLICHT_FOUND)
    include(ExternalProject)
    ExternalProject_Add(
            Irrlicht
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/toto
                URL https://vorboss.dl.sourceforge.net/project/irrlicht/Irrlicht%20SDK/1.8/1.8.4/irrlicht-1.8.4.zip
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                UPDATE_COMMAND ""
                INSTALL_COMMAND ""
                LOG_DOWNLOAD 1
                LOG_UPDATE 1
                LOG_CONFIGURE 1
                LOG_BUILD 1
                LOG_TEST 1
                LOG_INSTALL 1
        )
    set(IRRLICHT_LIBRARIES)
ENDIF(IRRLICHT_FOUND)

mark_as_advanced(IRRLICHT_LIBRARY IRRLICHT_INCLUDE_DIR)