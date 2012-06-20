CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)



################################################################################
# Qt4
################################################################################
FIND_PACKAGE(Qt4 REQUIRED)

# overide some value for mingw32
IF(TARGET_WINDOWS)
  SET(QT_LIBS QtCore4)
ELSE()
  SET(QT_LIBS ${QT_LIBRARIES})
ENDIF()

################################################################################



################################################################################
# libvcard
################################################################################
FILE(GLOB vcard_cpp libvcard/*.cpp)
FILE(GLOB vcard_h include/vcard/*.h)
QT4_WRAP_CPP(vcard_moc ${libvcard_h})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(AFTER SYSTEM include/vcard ${QT_INCLUDES} ${CMAKE_BINARY_DIR})
ADD_LIBRARY(vcard ${vcard_cpp} ${libvcard_h} ${vcard_moc})

TARGET_LINK_LIBRARIES(vcard ${QT_LIBS})
################################################################################
