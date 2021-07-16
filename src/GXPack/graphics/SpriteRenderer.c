#import "SpriteRenderer.h"

struct __GXSpriteRenderer
{
	struct __CFObject obj;
    GXShaderRef mShader; 
    UInt32 mQuadVAO;
};

static struct __CFClass class = {
	.name = "SpriteRenderer",
	.size = sizeof(struct __GXSpriteRenderer),
	.ctor = GXSpriteRendererConstructor,
	.dtor = GXSpriteRendererFinalize,
	.class = CFClass,
    .tostr = GXSpriteRendererToString
};

Boolean
GXSpriteRendererConstructor(CFType self, va_list args)
{
	GXSpriteRendererRef this = self;
    this->mShader = va_arg(args, GXShaderRef);
    GXSpriteRendererInitRenderData(this);
    return true;
}

extern GXSpriteRendererRef
GXSpriteRendererNew(GXShaderRef shader);
{
    return CFNewObject(GXSpriteRendererClass, shader);
}

extern GXSpriteRendererRef
GXSpriteRendererCreate(GXShaderRef shader)
{
    return CFCreateObject(GXSpriteRendererClass, shader);
}

void
GXSpriteRendererFinalize(CFType self)
{
	GXSpriteRendererRef this = self;
    GL.DeleteVertexArrays(1, &this->mQuadVAO);
}

CFString
GXSpriteRendererToString { return CFCreateString("Shader"); }

void
GXSpriteRendererDrawSprite(GXSpriteRendererRef this, 
    Texture2DRef texture,
    SDL_Rect* bounds,
    Float32 rotate,
    Vec3 color)
{
    // Prepare transformations
    GXShaderUse(this->mShader);

    Mat model= {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    //First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    static Vec3 zero = { 0, 0, 0 };
    static Vec3 tr = { 0, 0, 0 };
    static Vec3 sc = { 0, 0, 1 };
    tr.x = bounds->x;
    tr.y = bounds->y;
    model = glm_translate(model, tr);  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    tr.x = 0.5f * bounds->w;
    tr.y = 0.5f * bounds->h;
    model = glm_translate(model, tr); // Move origin of rotation to center of quad
    model = glm_rotate(model, rotate, zero); // Then rotate
    tr.x = -0.5f * bounds->w;
    tr.y = -0.5f * bounds->h;
    model = glm_translate(model, tr); // Move origin back
    sc.x = bounds->w;
    sc.y = bounds->h;
    model = glm_scale(model, sc); // Last scale


    // CFLog("model");
    // CFLog("%f %f %f %f", model[0], model[1], model[2], model[3]);
    // CFLog("%f %f %f %f", model[4], model[5], model[6], model[7]);
    // CFLog("%f %f %f %f", model[8], model[9], model[10], model[11]);
    // CFLog("%f %f %f %f", model[12], model[13], model[14], model[15]);

    GXShaderSetMatrix(this->mShader,  "model", model);
    GXShaderSetVector3(this-<mShader, "spriteColor", color);

    GL.ActiveTexture(GL_TEXTURE0);
    GXTexture2DBind(texture);

    GL.BindVertexArray(this->mQuadVAO);
    GL.DrawArrays(GL_TRIANGLES, 0, 6);
    GL.BindVertexArray(0);

}

void
InitRenderData(GXSpriteRendererRef this)
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = { 
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    GL.GenVertexArrays(1, &this->mQuadVAO);
    GL.GenBuffers(1, &this->VBO);

    GL.BindBuffer(GL_ARRAY_BUFFER, VBO);
    GL.BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GL.BindVertexArray(this->mQuadVAO);
    GL.EnableVertexAttribArray(0);
    GL.VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    GL.BindBuffer(GL_ARRAY_BUFFER, 0);
    GL.BindVertexArray(0);

}
