cmake_minimum_required ( VERSION 3.1 )
###################################################################################
#
#   Build catlock
#
###################################################################################
project ( catlock VERSION 0.1.0 )

#
set ( VERSION 0.1.0 )
set ( RELEASE_NAME catlock )

#
# enable features
#
include ( CMakeToolsHelpers OPTIONAL )

set(SOURCES
    src/helloworld.c
    # src/main.c
    # src/tests.c
)
add_subdirectory( src/CoreFX )
add_subdirectory( src/UIPack )


#
#   application includes
#
set ( INCLUDES "${INCLUDES};src" )

set ( INCLUDES "${INCLUDES};/usr/local/include" )
set ( INCLUDES "${INCLUDES};/usr/local/include/freetype2" )
set ( INCLUDES "${INCLUDES};/usr/local/include/X11" )
set ( INCLUDES "${INCLUDES};/usr/include" )
set ( INCLUDES "${INCLUDES};/usr/include/freetype2" )
set ( INCLUDES "${INCLUDES};/usr/include/X11" )

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNK_XLIB_USE_XFT" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__CoreFX_Advanced_Mode__" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Os -std=c18" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks" )

# links folders 
link_directories ( /usr/local/lib/ )

include_directories ( AFTER ${INCLUDES} )

#
#   compile ccode & link executable
#
add_executable ( ${PROJECT_NAME} ${SOURCES} ${RESOURCES} )
add_custom_command ( TARGET ${PROJECT_NAME} 
                   POST_BUILD COMMAND 
                   ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> .. )
                                      
target_link_libraries ( ${PROJECT_NAME}  c BlocksRuntime X11 Xft  )
# target_link_libraries ( ${PROJECT_NAME} c  )
install ( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . )

include ( CPack )

