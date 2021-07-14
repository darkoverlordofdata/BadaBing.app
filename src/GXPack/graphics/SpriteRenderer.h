#import <CoreFX/CoreFX.h>
#import <SDL2/SDL.h>
#import "../tglm.h"
#import "../OpenGL.h"
#import "Texture2D.h"
#import "Shader.h"

typedef struct __GXSpriteRenderer *GXSpriteRendererRef;

extern CFClassRef GXSpriteRendererClass;

extern Boolean 
GXSpriteRendererConstructor(CFTypeRef, va_list);

extern GXSpriteRendererRef
GXSpriteRendererNew(GXShaderRef);

extern GXSpriteRendererRef
GXSpriteRendererCreate(GXShaderRef);

extern void
GXSpriteRendererInitRenderData(GXSpriteRendererRef);

extern CFStringRef
GXSpriteRendererToString(GXSpriteRendererRef);

extern void
GXSpriteRendererDrawSprite(GXSpriteRendererRef, 
    Texture2DRef, SDL_Rect*, Float32, Vec3);

