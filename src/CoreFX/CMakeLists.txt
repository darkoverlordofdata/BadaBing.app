cmake_minimum_required ( VERSION 3.1 )
#
#   CoreFX source
#
set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/CFArray.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFBitVector.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFBool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFBox.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFClass.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFDouble.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFFile.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFInt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFList.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFMap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFObject.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFRange.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFRefPool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFSocket.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFStream.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFString.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CFUUID.c
    PARENT_SCOPE
  )
