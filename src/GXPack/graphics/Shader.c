#import "Shader.h"

struct __GXShader {
	struct __CFObject obj;
    UInt32 mId; 
};

static struct __CFClass class = {
	.name = "GXShader",
	.size = sizeof(struct __GXShader),
	.ctor = GXShaderConstructor,
	.dtor = GXShaderFinalize,
	.class = CFClass,
    .tostr = GXShaderToString
};
CFClassRef GXShaderClass = &class;

Int32   GXGameId     (GXShaderRef this) { return this->mId; }

GXShaderRef 
GXShaderNew()
{
    return CFNew(GXShaderClass);
}

GXShaderRef 
GXShaderCreate()
{
    return CFCreate(GXShaderClass);
}

Boolean 
GXShaderConstructor(CFTypeRef self, va_list args)
{
    return true;
}

CFStringRef 
GXShaderToString(CFTypeRef this)
{
    return CFStringCreate("GXShader"); 
}

GXShaderRef
GXShaderUse(GXShaderRef this)
{
    GL.UseProgram(this->mId); 
    return this;
}

void
GXShaderCheckCompileErrors(GXShaderRef this, Int32 object, CFStringRef type);
{
    GLint success;
    GLchar infoLog[1024];
    if (!CFStringEqual(type, CFStringCreate("PROGRAM"))
    {
        GL.GetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GL.GetShaderInfoLog(object, 1024, NULL, infoLog);
            CFLog("| ERROR::Shader: Compile-time error: Type: %s\n%s\n -- --------------------------------------------------- -- ",
                CFStringC(type), infoLog);
        }
    }
    else
    {
        GL.GetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            GL.GetProgramInfoLog(object, 1024, NULL, infoLog);
            CFLog("| ERROR::Shader: Link-time error: Type: %s\n%s\n -- --------------------------------------------------- -- ",
            CFStringC(type), infoLog);
        }
    }
}

void
GXShaderCompile(GXShaderRef this, char* vertexSource, char* fragmentSource)
{
    GLuint sVertex, sFragment;
    // Vertex Shader
    sVertex = GL.CreateShader(GL_VERTEX_SHADER);
    GL.ShaderSource(sVertex, 1, &vertexSource, NULL);
    GL.CompileShader(sVertex);
    GXShaderCheckCompileErrors(this, sVertex, CFStringCreate("VERTEX");
    // Fragment Shader
    sFragment = GL.CreateShader(GL_FRAGMENT_SHADER);
    GL.ShaderSource(sFragment, 1, &fragmentSource, NULL);
    GL.CompileShader(sFragment);
    GXShaderCheckCompileErrors(this, sFragment, CFStringCreate("FRAGMENT");

    // Shader Program
    mId = GL.CreateProgram();
    GL.AttachShader(mId, sVertex);
    GL.AttachShader(mId, sFragment);
    GL.LinkProgram(mId);
    GXShaderCheckCompileErrors(this, this->mId, CFStringCreate("PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    GL.DeleteShader(sVertex);
    GL.DeleteShader(sFragment);

}

GXShaderRef
GXShaderSetInteger(GXShaderRef this, char* name, Int32 value, Boolean useShader)
{
    if (useShader)
        GXShaderUse(this);
    GL.Uniform1i(GL.GetUniformLocation(this->mId, name), value);
    return this;
}

GXShaderRef
GXShaderSetFloat(GXShaderRef this, char* name, Float32 value, Boolean useShader)
{
    if (useShader)
        GXShaderUse(this);
    GL.Uniform1f(GL.GetUniformLocation(this->mId, name), value);
    return this;
}

GXShaderRef
GXShaderSetVector2(GXShaderRef this, char* name, Vec2 value, Boolean useShader)
{
    if (useShader)
        GXShaderUse(this);
    GL.Uniform2fv(GL.GetUniformLocation(this->mId, name), value);
    return self;

}

GXShaderRef
GXShaderSetVector3(GXShaderRef this, char* name, Vec3 value, Boolean useShader)
{
    if (useShader)
        GXShaderUse(this);
    GL.Uniform3fv(GL.GetUniformLocation(this->mId, name), value);
    return self;

}

GXShaderRef
GXShaderSetMatrix(GXShaderRef this, char* name, Mat value, Boolean useShader)
{
    if (useShader)
        GXShaderUse(this);
    GL.UniformMatrix4fv(GL.GetUniformLocation(this->mId, name), 1, GL_FALSE, (GLfloat*)&value);

}

