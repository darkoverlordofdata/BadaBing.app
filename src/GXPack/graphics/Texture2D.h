#import <CoreFX/CoreFX.h>
#import <SDL2/SDL.h>
#import "../OpenGL.h"

typedef struct __GXTexture2D *GXTexture2DRef;

extern CFClassRef GXTexture2DClass;

extern Boolean 
GXTexture2DConstructor(CFTypeRef, va_list);

extern Int32
GXTexture2DId(GXTexture2DRef);

extern Int32
GXTexture2DWidth(GXTexture2DRef);

extern Int32
GXTexture2DHeight(GXTexture2DRef);

extern Int32
GXTexture2DInternalFormat(GXTexture2DRef);

extern Int32
GXTexture2DImageFormat(GXTexture2DRef);

extern GXTexture2DRef
GXTexture2DNew(CFStringRef, Boolean);

extern GXTexture2DRef
GXTexture2DCreate(CFStringRef, Boolean);

extern CFStringRef 
GXTexture2DToString(CFTypeRef);

extern void
GXTexture2DGenerate(GXTexture2DRef, unsigned char*, UInt32, UInt32); 

extern void
GXTexture2DBind(GXTexture2DRef);

