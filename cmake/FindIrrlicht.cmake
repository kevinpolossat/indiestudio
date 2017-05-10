set(IRRLICHT_DIR ${BUILD_DEPENDENCIES}/irrlicht)

find_path(IRRLICHT_INCLUDE_DIR
        NAMES irrlicht/irrlicht.h irrlicht.h
        PATHS $ENV{IRRDIR}/include ${IRRLICHT_DIR}/Source/Irrlicht/include
        PATH_SUFFIXES irrlicht
        )

message(STATUS "IRRLICHT_INCLUDE_DIR = ${IRRLICHT_INCLUDE_DIR}")

find_library(IRRLICHT_LIBRARY NAMES Irrlicht
        PATHS $ENV{IRRDIR}/lib ${IRRLICHT_DIR}/Source/Irrlicht/lib/Linux
        )

# handle the QUIETLY and REQUIRED arguments and set IRRLICHT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IRRLICHT DEFAULT_MSG IRRLICHT_LIBRARY IRRLICHT_INCLUDE_DIR)

IF(IRRLICHT_FOUND)
    set(IRRLICHT_LIBRARIES ${IRRLICHT_LIBRARY})
ELSE(IRRLICHT_FOUND)
    include(ExternalProject)


    set(EP_BASE_DIRECTORY ${IRRLICHT_DIR})
    set_directory_properties(
            PROPERTIES
            EP_BASE ${EP_BASE_DIRECTORY}
    )
    set(IRRLICHT_DL_SOURCE ${EP_BASE_DIRECTORY}/Source)
    set(IRRLICHT_DL ${IRRLICHT_DL_SOURCE}/Irrlicht)
    set(IRRLICHT_BUILD_LOCATION ${IRRLICHT_DL}/source/Irrlicht)
    ExternalProject_Add(
                Irrlicht
                URL https://vorboss.dl.sourceforge.net/project/irrlicht/Irrlicht%20SDK/1.8/1.8.4/irrlicht-1.8.4.zip
                INSTALL_DIR ${IRRLICHT_DL}
                BINARY_DIR ${IRRLICHT_BUILD_LOCATION}
                CONFIGURE_COMMAND ""
                BUILD_COMMAND    "make"
                INSTALL_COMMAND     ""
                LOG_CONFIGURE 1
                LOG_INSTALL 1
                LOG_BUILD 1
        )
    ExternalProject_Get_Property(Irrlicht INSTALL_DIR)

    #    ExternalProject_Get_Property(IRRLICHT_INCLUDE_DIR ${IRRLICHT_DIR}/Source/Irrlicht/include)
    set(IRRLICHT_LIBRARY ${INSTALL_DIR}/lib/Linux/libIrrlicht.a)
    set(IRRLICHT_INCLUDE_DIR ${INSTALL_DIR}/include)
ENDIF(IRRLICHT_FOUND)

mark_as_advanced(IRRLICHT_LIBRARY IRRLICHT_INCLUDE_DIR)
