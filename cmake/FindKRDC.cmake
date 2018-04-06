# FindKRDC.cmake

# KRDC_FOUND - System has KRDC
# KRDC_INCLUDES - The KRDC include directories
# KRDC_LIBRARIES - The libraries needed to use KRDC
# KRDC_DEFINITIONS - Compiler switches required for using KRDC


IF (KRDC_INCLUDE_DIRS AND KRDC_LIBRARIES)
   # in cache already
   SET(KRDC_FIND_QUIETLY TRUE)
ELSE (KRDC_INCLUDE_DIRS AND KRDC_LIBRARIES)
   SET(KRDC_FIND_QUIETLY FALSE)
ENDIF (KRDC_INCLUDE_DIRS AND KRDC_LIBRARIES)

IF (NOT WIN32)
   # use pkg-config to get the directories and then use these values
   # in the FIND_PATH() and FIND_LIBRARY() calls
   FIND_PACKAGE(PkgConfig)
   PKG_CHECK_MODULES(PC_KRDC libkrdccore)
   #MESSAGE(STATUS "DEBUG: KRDC include directory = ${KRDC_INCLUDE_DIRS}")
   #MESSAGE(STATUS "DEBUG: KRDC link directory = ${KRDC_LIBRARY_DIRS}")
   #MESSAGE(STATUS "DEBUG: KRDC CFlags = ${KRDC_CFLAGS}")
   SET(KRDC_DEFINITIONS  ${PC_KRDC_CFLAGS} ${PC_KRDC_CFLAGS_OTHER})
ENDIF (NOT WIN32)

FIND_PATH(
    KRDC_INCLUDE_DIR remoteview.h
    HINTS ${PC_KRDC_INCLUDES} ${PC_KRDC_INCLUDE_DIRS}
    PATH_SUFFIXES krdc
)

FIND_LIBRARY(
    _KRDCLibs NAME krdccore
    HINTS ${PC_KRDC_LIBDIR} ${PC_KRDC_LIBRARY_DIRS}
    PATH_SUFFIXES ${LIBDIR}
)

list(APPEND KRDC_LIBRARIES ${_KRDCLibs} )
list(APPEND KRDC_INCLUDE_DIRS ${KRDC_INCLUDE_DIR} )

IF (KRDC_INCLUDE_DIRS AND KRDC_LIBRARIES)
   SET(KRDC_FOUND TRUE)
ELSE (KRDC_INCLUDE_DIRS AND KRDC_LIBRARIES)
   SET(KRDC_FOUND FALSE)
ENDIF (KRDC_INCLUDE_DIRS AND KRDC_LIBRARIES)

IF (KRDC_FOUND)
   IF (NOT KRDC_FIND_QUIETLY)
      MESSAGE(STATUS "Found KRDC libraries: ${KRDC_LIBRARIES}")
      MESSAGE(STATUS "Found KRDC includes : ${KRDC_INCLUDE_DIRS}")
   ENDIF (NOT KRDC_FIND_QUIETLY)
ELSE (KRDC_FOUND)
    IF (KRDC_FIND_REQUIRED)
      MESSAGE(STATUS "Could NOT find KRDC")
    ENDIF(KRDC_FIND_REQUIRED)
ENDIF (KRDC_FOUND)

MARK_AS_ADVANCED(KRDC_INCLUDE_DIRS KRDC_LIBRARIES)
