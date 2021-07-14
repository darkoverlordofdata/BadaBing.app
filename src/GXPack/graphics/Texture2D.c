#import "Texture2D.h"

struct __GXTexture2D 
{
	struct __CFObject obj;
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    UInt32 mId;
    // Texture image dimensions
    UInt32 mWidth;
    UInt32 mHeight; // Width and height of loaded image in pixels
    // Texture Format
    UInt32 mInternalFormat; // Format of texture object
    UInt32 mImageFormat; // Format of loaded image

    UInt32 mWrapS; // Wrapping mode on S axis
    UInt32 mWrapT; // Wrapping mode on T axis
    UInt32 mFilterMin; // Filtering mode if texture pixels < screen pixels
    UInt32 mFilterMag; // Filtering mode if texture pixels > screen pixels
    CFStringRef mPath;

};

static struct __CFClass class = {
	.name = "GXTexture2D",
	.size = sizeof(struct __GXTexture2D),
	.ctor = GXTexture2DConstructor,
	.dtor = GXTexture2DFinalize,
	.class = CFClass,
    .tostr = GXTexture2DToString
};

extern Int32
GXTexture2DId(GXTexture2DRef this)
{
    return this->mId;
}

extern Int32
GXTexture2DWidth(GXTexture2DRef this)
{
    return this->mWidth;
}

extern Int32
GXTexture2DHeight(GXTexture2DRef this)
{
    return this->mHeight;
}

extern Int32
GXTexture2DInternalFormat(GXTexture2DRef this)
{
    return this->mInternalFormat;
}

extern Int32
GXTexture2DImageFormat(GXTexture2DRef this)
{
    return this->mImageFormat;
}

Boolean 
GXTexture2DConstructor(CFTypeRef self, va_list args)
{
	GXTexture2DRef this = self;
    this->mPath = va_arg(args, CFStringRef);
    Boolean alpha = va_arg(args, Boolean);
    this->mInternalFormat = alpha ? GL_RGBA : GL_RGB;
    this->mImageFormat = alpha ? GL_RGBA : GL_RGB;
    this->mWrapS = GL_REPEAT;
    this->mWrapT = GL_REPEAT;
    this->mFilterMin = GL_LINEAR;
    this->mFilterMag = GL_LINEAR;
    GL.GenTextures(1, &mId);
    return true;
}

CFStringRef 
GXTexture2DToString(CFTypeRef self)
{
    return CFStringCreate("GXTexture2D");
}

void
GXTexture2DBind(GXTexture2DRef this)
{
    GL.BindTexture(GL_TEXTURE_2D, this->mId);
}

void
GXTexture2DGenerate(GXTexture2DRef this, 
    unsigned char* pixels, 
    UInt32 width, UInt32 height)
{
    this->mWidth = width;
    this->mHeight = height;
    // Create Texture
    GL.BindTexture(GL_TEXTURE_2D, this->mId);
    GL.TexImage2D(GL_TEXTURE_2D, 0, this->mInternalFormat, this->width, this->height, 0, this->mImageFormat, GL_UNSIGNED_BYTE, pixels);
    // Set Texture wrap and filter modes
    GL.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->mWrapS);
    GL.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->mWrapT);
    GL.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->mFilterMin);
    GL.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->mFilterMag);
    // Unbind texture
    GL.BindTexture(GL_TEXTURE_2D, 0);
}
