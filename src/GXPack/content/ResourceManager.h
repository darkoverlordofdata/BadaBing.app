#import <CoreFX/CoreFX.h>
#import <SDL2/SDL.h>
#import <SDL2/SDL_image.h>
#import "../OpenGL.h"
#import "../graphics/Texture2D.h"
#import "../graphics/Shader.h"

typedef struct __GXResourceManager *GXResourceManagerRef;

extern CFClass GXResourceManagerClass;

extern CFMap
GXResourceManagerShaders(GXResourceManagerRef);

extern CFMap
GXResourceManagerTexturess(GXResourceManagerRef);

extern GXShader
GXResourceManagerLoadShader(GXResourceManagerRef,
    CFString, CFString, CFString)
    

+ (Shader*)GetShader:(NSString*)name;
+ (Texture2D*)LoadTexture:(NSString*)name Path:(NSString*)path Alpha:(GLboolean)alpha;
+ (Texture2D*)GetTexture:(NSString*)name;
+ (void)Clear;

+ (Shader*)LoadShaderFromFile:(NSString*) vertex Fragment:(NSString*) fragment;
+ (Texture2D*)LoadTextureFromFile:(NSString*)path Alpha:(GLboolean)alpha;
+ (NSString*)ResourcePath:(NSString*)filename;
