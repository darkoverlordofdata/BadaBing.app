#import <CoreFX/CoreFX.h>
#import <SDL2/SDL.h>
#import "../tglm.h"
#import "../OpenGL.h"

typedef struct __GXShader *GXShaderRef;

extern CFClassRef GXShaderClass;

extern Int32
GXShaderId(GXShaderRef);

extern Boolean 
GXShaderConstructor(CFTypeRef, va_list);

extern CFStringRef 
GXShaderToString(CFTypeRef);

extern GXShaderRef
GXShaderUse(GXShaderRef);

extern void
GXShaderCheckCompileErrors(GXShaderRef, Int32, CFStringRef);

extern void
GXShaderCompile(GXShaderRef, char*, char*);

extern GXShaderRef
GXShaderSetInteger(GXShaderRef, char*, Int32, Boolean);

extern GXShaderRef
GXShaderSetFloat(GXShaderRef, char*, Float32, Boolean);

extern GXShaderRef
GXShaderSetVector2(GXShaderRef, char*, Vec2, Boolean);

extern GXShaderRef
GXShaderSetVector3(GXShaderRef, char*, Vec3, Boolean);

extern GXShaderRef
GXShaderSetMatrix(GXShaderRef, char*, Mat, Boolean);

