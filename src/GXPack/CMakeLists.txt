cmake_minimum_required ( VERSION 3.1 )
#
#   GXPack source
#
set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/tglm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.c
    ${CMAKE_CURRENT_SOURCE_DIR}/content/ResourceManager.c
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/Shader.c
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/SpriteRenderer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/Texture2D.c
    PARENT_SCOPE
  )


