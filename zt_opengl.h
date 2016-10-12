/**************************************************************************************************
** file: zt_opengl.h v 0.00 (active initial development)
**
** This software is dual-licensed to the public domain and under the following
** license: you are granted a perpetual, irrevocable license to copy, modify,
** publish, and distribute this file as you see fit.
**
** No warranty is offered or implied.  Use this at your own risk.
**
**************************************************************************************************

Zero Tolerance OpenGL Library

In exactly one c/cpp source file of your project, you must:

#define ZT_OPENGL_IMPLEMENTATION
#include "zt_opengl.h"

**************************************************************************************************

Options:


**************************************************************************************************

Implimentation Options: (only used with ZT_OPENGL_IMPLEMENTATION #include)


**************************************************************************************************/

#ifndef __zt_opengl_h_included__
#define __zt_opengl_h_included__

// ------------------------------------------------------------------------------------------------

#define ZT_OPENGL


// ------------------------------------------------------------------------------------------------

#include "zt_tools.h"
#include <gl/GL.h>


// ------------------------------------------------------------------------------------------------

typedef unsigned int   GLenum;
typedef unsigned char  GLboolean;
typedef unsigned int   GLbitfield;
typedef signed char    GLbyte;
typedef short          GLshort;
typedef int            GLint;
typedef int            GLsizei;
typedef unsigned char  GLubyte;
typedef unsigned short GLushort;
typedef unsigned int   GLuint;
typedef float          GLfloat;
typedef float          GLclampf;
typedef double         GLdouble;
typedef double         GLclampd;
typedef void           GLvoid;
typedef char           GLchar;

#if defined(ZT_COMPILER_MSVC)
#	ifndef _PTRDIFF_T_DEFINED
#		ifdef _WIN64
			typedef __int64             ptrdiff_t;
#		else  /* _WIN64 */
			typedef _W64 int            ptrdiff_t;
#		endif  /* _WIN64 */
#		define _PTRDIFF_T_DEFINED
#	endif  /* _PTRDIFF_T_DEFINED */
#endif

typedef ptrdiff_t GLsizeiptr;

// ------------------------------------------------------------------------------------------------

#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_LINK_STATUS 0x8B82
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_TEXTURE0 0x84C0
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_MULTISAMPLE 0x809D
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_FRAMEBUFFER 0x8D40
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_RENDERBUFFER 0x8D41
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_TEXTURE_MAX_LEVEL 0x813D
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_ACTIVE_UNIFORMS 0x8B86
#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_BOOL 0x8B56
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLER_CUBE 0x8B60

// ------------------------------------------------------------------------------------------------

struct ztContextGL;

ztContextGL *ztgl_contextMake(void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags); // ztRendererFlags
ztContextGL *ztgl_contextMake(ztMemoryArena *arena, void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags); // ztRendererFlags
void         ztgl_contextFree(ztContextGL *context);

void         ztgl_contextDisplay(ztContextGL *context);

ztPoint2     ztgl_contextGetSize(ztContextGL *context);
bool         ztgl_contextSetSize(ztContextGL *context, i32 w, i32 h);
bool         ztgl_contextIsFullscreen(ztContextGL *context);
bool         ztgl_contextToggleFullscreen(ztContextGL *context, bool fullscreen);

// ------------------------------------------------------------------------------------------------

bool ztgl_setViewport(i32 width, i32 height);
bool ztgl_setViewport(ztContextGL *context);

void ztgl_cullFront();
void ztgl_cullBack();
void ztgl_cullNone();


// ------------------------------------------------------------------------------------------------

bool    ztgl_checkAndReportError(const char *function);
int     ztgl_clearErrors();

#define ztgl_callAndReturnOnError(function) function; if (ztgl_checkAndReportError(#function)) return;
#define ztgl_callAndReturnValOnError(function, retval) function; if (ztgl_checkAndReportError(#function)) return retval;
#define ztgl_callAndReportOnError(function) function; ztgl_checkAndReportError(#function);

#if defined(ZT_OPENGL_DEBUGGING)
#	define ztgl_callAndReportOnErrorFast(function) function; ztgl_checkAndReportError(#function);
#else
#	define ztgl_callAndReportOnErrorFast(function) function;
#endif


// ------------------------------------------------------------------------------------------------

struct ztShaderGL
{
	GLuint program_id;
	GLuint vert_id, frag_id, geom_id;

	struct Uniform
	{
		GLint location;
		GLenum type;
		ztString name;
		u32 name_hash;
	};

	Uniform *uniforms;
	int uniforms_count;

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

ztShaderGL *ztgl_shaderMake(const char *vert_src, const char *frag_src, const char *geom_src = nullptr);
ztShaderGL *ztgl_shaderMake(ztMemoryArena *arena, const char *vert_src, const char *frag_src, const char *geom_src = nullptr);
void        ztgl_shaderFree(ztShaderGL *shader);

void        ztgl_shaderBegin(ztShaderGL *shader);
void        ztgl_shaderEnd(ztShaderGL *shader);

bool        ztgl_shaderHasVariable(ztShaderGL *shader, u32 name_hash);

void        ztgl_shaderVariableFloat(ztShaderGL *shader, u32 name_hash, r32 value);
void        ztgl_shaderVariableInt(ztShaderGL *shader, u32 name_hash, i32 value);
void        ztgl_shaderVariableVec2(ztShaderGL *shader, u32 name_hash, const ztVec2& value);
void        ztgl_shaderVariableVec3(ztShaderGL *shader, u32 name_hash, const ztVec3& value);
void        ztgl_shaderVariableVec4(ztShaderGL *shader, u32 name_hash, const ztVec4& value);
void        ztgl_shaderVariableMat4(ztShaderGL *shader, u32 name_hash, const ztMat4& value);
void        ztgl_shaderVariableMat3(ztShaderGL *shader, u32 name_hash, r32 value[12]);
void        ztgl_shaderVariableTex(ztShaderGL *shader, u32 name_hash, i32 value);


// ------------------------------------------------------------------------------------------------

enum ztTextureGLFlags_Enum
{
	ztTextureGLFlags_MipMaps      = (1<<0),
	ztTextureGLFlags_DepthMap     = (1<<1),
	ztTextureGLFlags_PixelPerfect = (1<<2),
	ztTextureGLFlags_CubeMap      = (1<<3),
};

// ------------------------------------------------------------------------------------------------

enum ztTextureGLCubeMapFiles_Enum
{
	ztTextureGLCubeMapFiles_Right,
	ztTextureGLCubeMapFiles_Left,
	ztTextureGLCubeMapFiles_Top,
	ztTextureGLCubeMapFiles_Bottom,
	ztTextureGLCubeMapFiles_Back,
	ztTextureGLCubeMapFiles_Front,

	ztTextureGLCubeMapFiles_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztTextureGL
{
	GLuint texid;

	GLuint fbo;	// frame buffer
	GLuint dbo;	// depth buffer
	GLuint rt;	// render texture
	GLuint rb;	// resolve buffer

	int w, h, d;

	i32 flags;

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeFromPixelData(byte *pixels, int w, int h, int d, i32 flags);
ztTextureGL *ztgl_textureMakeFromPixelData(ztMemoryArena *arena, byte *pixels, int w, int h, int d, i32 flags);
ztTextureGL *ztgl_textureMakeCubeMapFromPixelData(byte **pixels, int w, int h, int d);
ztTextureGL *ztgl_textureMakeCubeMapFromPixelData(ztMemoryArena *arena, byte **pixels, int w, int h, int d);
ztTextureGL *ztgl_textureMakeRenderTarget(int w, int h, i32 flags);
ztTextureGL *ztgl_textureMakeRenderTarget(ztMemoryArena *arena, int w, int h, i32 flags);
ztTextureGL *ztgl_textureMakeDepthRenderTarget(int w, int h);
ztTextureGL *ztgl_textureMakeDepthRenderTarget(ztMemoryArena *arena, int w, int h);

void         ztgl_textureFree(ztTextureGL *texture);

void	     ztgl_textureBindReset();
void	     ztgl_textureBind(ztTextureGL *texture, int as_idx);

void         ztgl_textureRenderTargetPrepare(ztTextureGL *texture);
void         ztgl_textureRenderTargetCommit(ztTextureGL *texture, ztContextGL *context);

bool         ztgl_textureIsRenderTarget(ztTextureGL *texture);


// ------------------------------------------------------------------------------------------------

struct ztVertexEntryGL
{
	GLenum type;
	int size;
};

// ------------------------------------------------------------------------------------------------

void ztgl_drawVertices(GLenum mode, ztVertexEntryGL *entries, int entries_count, void *vertices, int vert_count);


// ------------------------------------------------------------------------------------------------

struct ztVertexArrayGL
{
	GLuint vao;
	GLuint vbo;

	ztVertexEntryGL *entries;
	int              entries_count;

	int vert_count;

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

ztVertexArrayGL *ztgl_vertexArrayMake(ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count);
ztVertexArrayGL *ztgl_vertexArrayMake(ztMemoryArena *arena, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count);
void             ztgl_vertexArrayFree(ztVertexArrayGL *vertex_array);
void             ztgl_vertexArrayDraw(ztVertexArrayGL *vertex_array, GLenum mode = GL_TRIANGLES);

// ------------------------------------------------------------------------------------------------

#define ZTGL_WINAPI	__stdcall

typedef int       (ZTGL_WINAPI *ztgl_wglSwapIntervalEXT_Func) (int interval);
typedef GLuint    (ZTGL_WINAPI *ztgl_glCreateShader_Func) (GLenum type);
typedef void      (ZTGL_WINAPI *ztgl_glShaderSource_Func) (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
typedef void      (ZTGL_WINAPI *ztgl_glCompileShader_Func) (GLuint shader);
typedef void      (ZTGL_WINAPI *ztgl_glGetShaderiv_Func) (GLuint shader, GLenum pname, GLint* param);
typedef void      (ZTGL_WINAPI *ztgl_glGetShaderInfoLog_Func) (GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void      (ZTGL_WINAPI *ztgl_glDeleteShader_Func) (GLuint shader);
typedef GLuint    (ZTGL_WINAPI *ztgl_glCreateProgram_Func) (void);
typedef void      (ZTGL_WINAPI *ztgl_glAttachShader_Func) (GLuint program, GLuint shader);
typedef void      (ZTGL_WINAPI *ztgl_glLinkProgram_Func) (GLuint program);
typedef void      (ZTGL_WINAPI *ztgl_glGetProgramiv_Func) (GLuint program, GLenum pname, GLint* param);
typedef void      (ZTGL_WINAPI *ztgl_glGetProgramInfoLog_Func) (GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void      (ZTGL_WINAPI *ztgl_glDeleteProgram_Func) (GLuint program);
typedef void      (ZTGL_WINAPI *ztgl_glDetachShader_Func) (GLuint program, GLuint shader);
typedef void      (ZTGL_WINAPI *ztgl_glUseProgram_Func) (GLuint program);
typedef void      (ZTGL_WINAPI *ztgl_glBlendFuncSeparate_Func) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void      (ZTGL_WINAPI *ztgl_glVertexAttribPointer_Func) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void      (ZTGL_WINAPI *ztgl_glEnableVertexAttribArray_Func) (GLuint index);
typedef GLint     (ZTGL_WINAPI *ztgl_glGetUniformLocation_Func) (GLuint program, const GLchar* name);
typedef void      (ZTGL_WINAPI *ztgl_glUniformMatrix4fv_Func) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void      (ZTGL_WINAPI *ztgl_glUniformMatrix3fv_Func) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void      (ZTGL_WINAPI *ztgl_glUniform1fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_WINAPI *ztgl_glUniform2fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_WINAPI *ztgl_glUniform3fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_WINAPI *ztgl_glUniform4fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_WINAPI *ztgl_glGenBuffers_Func) (GLsizei n, GLuint* buffers);
typedef void      (ZTGL_WINAPI *ztgl_glBindBuffer_Func) (GLenum target, GLuint buffer);
typedef void      (ZTGL_WINAPI *ztgl_glGenVertexArrays_Func) (GLsizei n, GLuint* arrays);
typedef void      (ZTGL_WINAPI *ztgl_glBindVertexArray_Func) (GLuint array);
typedef void      (ZTGL_WINAPI *ztgl_glDeleteVertexArrays_Func) (GLsizei n, const GLuint* arrays);
typedef void      (ZTGL_WINAPI *ztgl_glDeleteBuffers_Func) (GLsizei n, const GLuint* buffers);
typedef void      (ZTGL_WINAPI *ztgl_glBufferData_Func) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void      (ZTGL_WINAPI *ztgl_glActiveTexture_Func) (GLenum texture);
typedef void      (ZTGL_WINAPI *ztgl_glGenerateMipmap_Func) (GLenum target);
typedef void      (ZTGL_WINAPI *ztgl_glDeleteRenderbuffers_Func) (GLsizei n, const GLuint* renderbuffers);
typedef void      (ZTGL_WINAPI *ztgl_glDeleteFramebuffers_Func) (GLsizei n, const GLuint* framebuffers);
typedef void      (ZTGL_WINAPI *ztgl_glUniform1i_Func) (GLint location, GLint v0);
typedef void      (ZTGL_WINAPI *ztgl_glGenFramebuffers_Func) (GLsizei n, GLuint* framebuffers);
typedef void      (ZTGL_WINAPI *ztgl_glBindFramebuffer_Func) (GLenum target, GLuint framebuffer);
typedef void      (ZTGL_WINAPI *ztgl_glFramebufferTexture2D_Func) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void      (ZTGL_WINAPI *ztgl_glGenRenderbuffers_Func) (GLsizei n, GLuint* renderbuffers);
typedef void      (ZTGL_WINAPI *ztgl_glBindRenderbuffer_Func) (GLenum target, GLuint renderbuffer);
typedef GLenum    (ZTGL_WINAPI *ztgl_glCheckFramebufferStatus_Func) (GLenum target);
typedef void      (ZTGL_WINAPI *ztgl_glRenderbufferStorageMultisample_Func) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void      (ZTGL_WINAPI *ztgl_glFramebufferRenderbuffer_Func) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void      (ZTGL_WINAPI *ztgl_glTexImage2DMultisample_Func) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void      (ZTGL_WINAPI *ztgl_glBlitFramebuffer_Func) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void      (ZTGL_WINAPI *ztgl_glGetActiveUniform_Func) (GLuint program, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void      (ZTGL_WINAPI *ztgl_glGetUniformfv_Func) (GLuint program, GLint location, GLfloat* params);
typedef void      (ZTGL_WINAPI *ztgl_glGetUniformiv_Func) (GLuint program, GLint location, GLint* params);

// ------------------------------------------------------------------------------------------------

#define ZTGL_FUNCTIONS	\
	ZTGL_FUNC_OP(wglSwapIntervalEXT) \
	ZTGL_FUNC_OP(glCreateShader) \
	ZTGL_FUNC_OP(glShaderSource) \
	ZTGL_FUNC_OP(glCompileShader) \
	ZTGL_FUNC_OP(glGetShaderiv) \
	ZTGL_FUNC_OP(glGetShaderInfoLog) \
	ZTGL_FUNC_OP(glDeleteShader) \
	ZTGL_FUNC_OP(glCreateProgram) \
	ZTGL_FUNC_OP(glAttachShader) \
	ZTGL_FUNC_OP(glLinkProgram) \
	ZTGL_FUNC_OP(glGetProgramiv) \
	ZTGL_FUNC_OP(glGetProgramInfoLog) \
	ZTGL_FUNC_OP(glDeleteProgram) \
	ZTGL_FUNC_OP(glDetachShader) \
	ZTGL_FUNC_OP(glUseProgram) \
	ZTGL_FUNC_OP(glBlendFuncSeparate) \
	ZTGL_FUNC_OP(glVertexAttribPointer) \
	ZTGL_FUNC_OP(glEnableVertexAttribArray) \
	ZTGL_FUNC_OP(glGetUniformLocation) \
	ZTGL_FUNC_OP(glUniformMatrix4fv) \
	ZTGL_FUNC_OP(glUniformMatrix3fv) \
	ZTGL_FUNC_OP(glUniform1fv) \
	ZTGL_FUNC_OP(glUniform2fv) \
	ZTGL_FUNC_OP(glUniform3fv) \
	ZTGL_FUNC_OP(glUniform4fv) \
	ZTGL_FUNC_OP(glGenBuffers) \
	ZTGL_FUNC_OP(glBindBuffer) \
	ZTGL_FUNC_OP(glGenVertexArrays) \
	ZTGL_FUNC_OP(glBindVertexArray) \
	ZTGL_FUNC_OP(glDeleteVertexArrays) \
	ZTGL_FUNC_OP(glDeleteBuffers) \
	ZTGL_FUNC_OP(glBufferData) \
	ZTGL_FUNC_OP(glActiveTexture) \
	ZTGL_FUNC_OP(glGenerateMipmap) \
	ZTGL_FUNC_OP(glDeleteRenderbuffers) \
	ZTGL_FUNC_OP(glDeleteFramebuffers) \
	ZTGL_FUNC_OP(glUniform1i) \
	ZTGL_FUNC_OP(glGenFramebuffers) \
	ZTGL_FUNC_OP(glBindFramebuffer) \
	ZTGL_FUNC_OP(glFramebufferTexture2D) \
	ZTGL_FUNC_OP(glGenRenderbuffers) \
	ZTGL_FUNC_OP(glBindRenderbuffer) \
	ZTGL_FUNC_OP(glCheckFramebufferStatus) \
	ZTGL_FUNC_OP(glRenderbufferStorageMultisample) \
	ZTGL_FUNC_OP(glFramebufferRenderbuffer) \
	ZTGL_FUNC_OP(glTexImage2DMultisample) \
	ZTGL_FUNC_OP(glBlitFramebuffer) \
	ZTGL_FUNC_OP(glGetActiveUniform) \
	ZTGL_FUNC_OP(glGetUniformfv) \
	ZTGL_FUNC_OP(glGetUniformiv) \

#define ZTGL_FUNC_OP(func)	extern ztgl_##func##_Func func;
ZTGL_FUNCTIONS
#undef ZTGL_FUNC_OP

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // include guard

#if defined(ZT_OPENGL_IMPLEMENTATION) || defined(ZT_OPENGL_INTERNAL_DECLARATIONS)

#ifndef __zt_opengl_h_internal_included__
#define __zt_opengl_h_internal_included__

#if defined(ZT_WINDOWS)
#include <windows.h>
#include <windowsx.h>
#include <gl/GLU.h>
#include <Wingdi.h>

struct ztContextGL
{
	HDC hdc;
	HGLRC context;
	HWND handle;

	ztPoint2 size;
	i32 pixels_per_unit;
	i32 flags;

	RECT screen_area;

	ztMemoryArena *arena;
};

#endif // ZT_WINDOWS

#endif // include guard
#endif // internal declarations

#if defined(ZT_OPENGL_IMPLEMENTATION)


enum ztRendererFlagsGL_Enum
{
	ztRendererFlagsGL_Windowed        = (1<<0),
	ztRendererFlagsGL_Fullscreen      = (1<<1),
	ztRendererFlagsGL_Vsync           = (1<<2),
	ztRendererFlagsGL_RotationAllowed = (1<<3), // mobile
	ztRendererFlagsGL_VertOrientation = (1<<4), // mobile
	ztRendererFlagsGL_LockAspect      = (1<<5),
	ztRendererFlagsGL_HideCursor      = (1<<6),
};



#if defined(ZT_WINDOWS)
#pragma comment(lib, "opengl32.lib")

// ------------------------------------------------------------------------------------------------

ztInternal void _ztgl_win_loadFunctions()
{
#	define ZTGL_FUNC_OP(func) func = (ztgl_##func##_Func)wglGetProcAddress((LPCSTR)((const GLubyte*)#func)); if(func == nullptr) zt_logCritical("Unable to load OpenGL function: %s", #func);
	ZTGL_FUNCTIONS;
#	undef ZTGL_FUNC_OP
}

// ------------------------------------------------------------------------------------------------

void ztgl_win_contextDisplay(ztContextGL *context)
{
	SwapBuffers(context->hdc);
}

// ------------------------------------------------------------------------------------------------

ztContextGL *ztgl_win_contextMake(ztMemoryArena *arena, HWND handle, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	zt_logDebug("OpenGL: creating DC");
	HDC hdc = GetDC(handle);

	zt_logDebug("OpenGL: setting pixel format");
	if (FALSE == SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd)) {
		zt_logCritical("OpenGL: SetPixelFormat failed");
		return nullptr;
	}

	zt_logDebug("OpenGL: creating OpenGL context");
	HGLRC context = wglCreateContext(hdc);
	if (context == NULL) {
		zt_logCritical("OpenGL: wglCreateContext failed");
		return false;
	}

	zt_logDebug("OpenGL: setting context to current");
	wglMakeCurrent(hdc, context);
	if (ztgl_checkAndReportError("wglMakeCurrent"))
		return nullptr;

	_ztgl_win_loadFunctions();

	glEnable(GL_CULL_FACE); // NOTE(josh): should this be here?

	// this turns off wait for vsync:
	if (!zt_bitIsSet(flags, ztRendererFlagsGL_Vsync)) {
		zt_logDebug("OpenGL: Vsync: true");
		ztgl_callAndReturnValOnError(wglSwapIntervalEXT(0), false);
	}
	else {
		zt_logDebug("OpenGL: Vsync: false");
	}

	if (zt_bitIsSet(flags, ztRendererFlagsGL_Fullscreen)) {
		zt_logDebug("OpenGL: Going fullscreen");
		//GetWindowRect(win_details->handle, &win_details->windowed_screen_area);

		LONG dwExStyle = GetWindowLong(handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(handle, GWL_STYLE);

		dwExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		dwStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

		SetWindowLong(handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(handle, GWL_STYLE, dwStyle);

		int screen_x = GetSystemMetrics(SM_CXSCREEN);
		int screen_y = GetSystemMetrics(SM_CYSCREEN);

		SetWindowPos(handle, 0, 0, 0, screen_x, screen_y, SWP_NOZORDER | SWP_FRAMECHANGED);
	}

	ztContextGL *result = zt_mallocStructArena(ztContextGL, arena);
	result->hdc = hdc;
	result->context = context;
	result->handle = handle;
	result->size.x = client_w;
	result->size.y = client_h;
	result->pixels_per_unit = pixels_per_unit;
	result->flags = flags;
	result->arena = arena;

	zt_logDebug("OpenGL: setting viewport");
	ztgl_setViewport(result);

	return result;
}

// ------------------------------------------------------------------------------------------------

void ztgl_win_contextFree(ztContextGL *context)
{
	wglMakeCurrent(GetDC(context->handle), NULL);
	wglDeleteContext(context->context);
	ReleaseDC(context->handle, context->hdc);
}

// ------------------------------------------------------------------------------------------------

bool ztgl_win_contextSetSize(ztContextGL *context, i32 w, i32 h)
{
	context->size.x = w;
	context->size.y = h;
	return ztgl_setViewport(context);
}

// ------------------------------------------------------------------------------------------------

bool ztgl_win_contextToggleFullscreen(ztContextGL *context, bool fullscreen)
{
	if (fullscreen) {
		GetWindowRect(context->handle, &context->screen_area);

		LONG dwExStyle = GetWindowLong(context->handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(context->handle, GWL_STYLE);

		dwExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		dwStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

		SetWindowLong(context->handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(context->handle, GWL_STYLE, dwStyle);

		int screen_x = GetSystemMetrics(SM_CXSCREEN);
		int screen_y = GetSystemMetrics(SM_CYSCREEN);

		SetWindowPos(context->handle, 0, 0, 0, screen_x, screen_y, SWP_NOZORDER | SWP_FRAMECHANGED);

		context->flags |= ztRendererFlagsGL_Fullscreen;
	}
	else {
		LONG dwExStyle = GetWindowLong(context->handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(context->handle, GWL_STYLE);

		dwExStyle |= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle |= WS_OVERLAPPEDWINDOW;

		SetWindowLong(context->handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(context->handle, GWL_STYLE, dwStyle);

		SetWindowPos(context->handle, HWND_TOP, 
					 context->screen_area.left, context->screen_area.top, 
					 context->screen_area.right - context->screen_area.left, 
					 context->screen_area.bottom - context->screen_area.top, SWP_FRAMECHANGED);	

		zt_bitRemove(context->flags, ztRendererFlagsGL_Fullscreen);
	}

	return ztgl_setViewport(context);
}

// ------------------------------------------------------------------------------------------------

bool ztgl_win_setViewport(ztContextGL *context)
{
	zt_returnValOnNull(context, false);

	struct local
	{
		static bool opengl_calls(int w, int h, r32 realw, r32 realh)
		{
			ztgl_callAndReturnValOnError(glViewport(0, 0, w, h), false); // Sets up clipping
			ztgl_callAndReturnValOnError(glClearColor(0.0f, 0.0f, 0.0f, 0.0f), false);
			ztgl_callAndReturnValOnError(glMatrixMode(GL_PROJECTION), false);
			ztgl_callAndReturnValOnError(glLoadIdentity(), false);
			ztgl_callAndReturnValOnError(glOrtho(-realw, realw, -realh, realh, -100.0, 100.0), false);
			ztgl_callAndReturnValOnError(glEnable(GL_TEXTURE_2D), false);
			ztgl_callAndReturnValOnError(glEnable(GL_BLEND), false);
			ztgl_callAndReturnValOnError(glEnable(GL_MULTISAMPLE), false);
			ztgl_callAndReturnValOnError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);
			return true;
		}
	};

	ztgl_clearErrors(); // make sure previously failed calls don't make the app exit

	r32 realw = (context->size.x / (r32)context->pixels_per_unit) / 2.f;
	r32 realh = (context->size.y / (r32)context->pixels_per_unit) / 2.f;

	if (zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen)) {
		int screen_x = GetSystemMetrics(SM_CXSCREEN);
		int screen_y = GetSystemMetrics(SM_CYSCREEN);

		if (!local::opengl_calls(screen_x, screen_y, realw, realh)) {
			return false;
		}
	}
	else {
		if (!local::opengl_calls(context->size.x, context->size.y, realw, realh)) {
			return false;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

#endif // ZT_WINDOWS

#define ZTGL_FUNC_OP(func)	ztgl_##func##_Func func = nullptr;
ZTGL_FUNCTIONS
#undef ZTGL_FUNC_OP

// ------------------------------------------------------------------------------------------------

ztInternal void _ztgl_loadFunctions()
{
	static bool called = false;
	if(called) return;
	called = true;

	zt_winOnly(_ztgl_win_loadFunctions());

	zt_logInfo("OpenGL: version: %s", glGetString(GL_VERSION));
	zt_logInfo("OpenGL: vendor: %s", glGetString(GL_VENDOR));
	zt_logInfo("OpenGL: renderer %s", glGetString(GL_RENDERER));
	zt_logInfo("OpenGL: shader version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	zt_logInfo("OpenGL: extensions %s", glGetString(GL_EXTENSIONS));
}

// ------------------------------------------------------------------------------------------------

ztContextGL *ztgl_contextMake(void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
	return ztgl_contextMake(zt_memGetGlobalArena(), (HWND)window, client_w, client_h, pixels_per_unit, flags);
}

// ------------------------------------------------------------------------------------------------

ztContextGL *ztgl_contextMake(ztMemoryArena *arena, void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
	zt_winOnly(return ztgl_win_contextMake(arena, (HWND)window, client_w, client_h, pixels_per_unit, flags));
}

// ------------------------------------------------------------------------------------------------

void ztgl_contextFree(ztContextGL *context)
{
	if(context == nullptr) {
		return;
	}

	if(context->context != NULL) {
		zt_winOnly(ztgl_win_contextFree(context));
	}

	zt_freeArena(context, context->arena);
}

// ------------------------------------------------------------------------------------------------

ztPoint2 ztgl_contextGetSize(ztContextGL *context)
{
	zt_returnValOnNull(context, ztPoint2(0,0));
	return context->size;
}

// ------------------------------------------------------------------------------------------------

bool ztgl_contextSetSize(ztContextGL *context, i32 w, i32 h)
{
	zt_winOnly(return ztgl_win_contextSetSize(context, w, h));
}

// ------------------------------------------------------------------------------------------------

void ztgl_contextDisplay(ztContextGL *context)
{
	zt_winOnly(ztgl_win_contextDisplay(context));
}

// ------------------------------------------------------------------------------------------------

bool ztgl_contextIsFullscreen(ztContextGL *context)
{
	zt_returnValOnNull(context, false);
	return zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen);
}

// ------------------------------------------------------------------------------------------------

bool ztgl_contextToggleFullscreen(ztContextGL *context, bool fullscreen)
{
	zt_returnValOnNull(context, false);
	zt_winOnly(return ztgl_win_contextToggleFullscreen(context, fullscreen));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool ztgl_setViewport(i32 width, i32 height)
{
	ztgl_callAndReturnValOnError(glViewport(0, 0, width, height), false);
	return true;
}

// ------------------------------------------------------------------------------------------------

bool ztgl_setViewport(ztContextGL *context)
{
	zt_winOnly(return ztgl_win_setViewport(context));
}

// ------------------------------------------------------------------------------------------------

void ztgl_cullFront()
{
	ztgl_callAndReportOnErrorFast(glEnable(GL_CULL_FACE));
	ztgl_callAndReportOnErrorFast(glCullFace(GL_FRONT));
}

// ------------------------------------------------------------------------------------------------

void ztgl_cullBack()
{
	ztgl_callAndReportOnErrorFast(glEnable(GL_CULL_FACE));
	ztgl_callAndReportOnErrorFast(glCullFace(GL_BACK));
}

// ------------------------------------------------------------------------------------------------

void ztgl_cullNone()
{
	ztgl_callAndReportOnErrorFast(glDisable(GL_CULL_FACE));
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool ztgl_checkAndReportError(const char *function)
{
	int errors = 0;
	for (GLint error = glGetError(); error != 0 && errors < 10; error = glGetError()) {
		zt_logCritical("OpenGL: error from function %s: 0x%08x (%d)", function, error, error);
		errors += 1;
	}
	return errors > 0;
}

// ------------------------------------------------------------------------------------------------

int ztgl_clearErrors()
{
	int errors = 0;
	for (GLint error = glGetError(); error != 0 && errors < 10; error = glGetError())
		++errors;

	return errors;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztShaderGL *ztgl_shaderMake(const char *vert_src, const char *frag_src, const char *geom_src)
{
	return ztgl_shaderMake(zt_memGetGlobalArena(), vert_src, frag_src, geom_src);
}

// ------------------------------------------------------------------------------------------------

ztShaderGL *ztgl_shaderMake(ztMemoryArena *arena, const char *vert_src, const char *frag_src, const char *geom_src)
{
	struct local
	{
		static GLuint load_shader(GLenum type, const char *src)
		{
			GLuint shader = glCreateShader(type);
			ztgl_callAndReturnValOnError("glCreateShader", 0);

			if (shader) {
				ztgl_callAndReturnValOnError(glShaderSource(shader, 1, &src, NULL), 0);
				ztgl_callAndReturnValOnError(glCompileShader(shader), 0);

				GLint compiled = 0;
				ztgl_callAndReturnValOnError(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled), 0);
				if (!compiled) {
					GLint info_len = 0;
					ztgl_callAndReturnValOnError(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len), 0);
					if (info_len) {
						char *buff = zt_mallocStructArray(char, info_len);
						if (buff) {
							glGetShaderInfoLog(shader, info_len, NULL, buff);
							zt_logCritical("Could not compile shader: %d\nReason: %s", type, buff);
							zt_free(buff);
						}
						ztgl_callAndReturnValOnError(glDeleteShader(shader), 0);
						shader = 0;
					}
				}
			}

			return shader;
		}

		static GLuint load_program(GLuint vert, GLuint frag, GLuint geom)
		{
			GLuint program = glCreateProgram();
			if (ztgl_checkAndReportError("glCreateProgram")) {
				return 0;
			}

			if (program) {
				ztgl_callAndReturnValOnError(glAttachShader(program, vert), 0);
				ztgl_callAndReturnValOnError(glAttachShader(program, frag), 0);

				if (geom != 0) {
					ztgl_callAndReturnValOnError(glAttachShader(program, geom), 0);
				}
				ztgl_callAndReturnValOnError(glLinkProgram(program), 0);

				GLint link_status = GL_FALSE;
				glGetProgramiv(program, GL_LINK_STATUS, &link_status);
				if (link_status != GL_TRUE) {
					GLint buff_len = 0;
					glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buff_len);
					if (buff_len) {
						char *buff = zt_mallocStructArray(char, buff_len);
						if (buff) {
							glGetProgramInfoLog(program, buff_len, NULL, buff);
							zt_logCritical("glLinkProgram failed.  Reason: %s", buff);
							zt_free(buff);
						}
					}
					ztgl_callAndReturnValOnError(glDeleteProgram(program), 0);
					program = 0;
				}
			}

			return program;
		}
	};

	GLuint vert = local::load_shader(GL_VERTEX_SHADER, vert_src);
	if (vert == 0) { zt_logCritical("OpenGL: Unable to compile vertex shader."); return false; }

	GLuint frag = local::load_shader(GL_FRAGMENT_SHADER, frag_src);
	if (frag == 0) { zt_logCritical("OpenGL: Unable to compile fragment shader."); return false; }

	GLuint geom = geom_src ? local::load_shader(GL_GEOMETRY_SHADER, geom_src) : 0;
	if (geom_src && geom == 0) { zt_logCritical("OpenGL: Unable to compile geometry shader."); return false; }

	GLuint program = local::load_program(vert, frag, geom);
	if (program == 0) { zt_logCritical("OPenGL: Unable to compile and link shader program."); return false; }

	ztShaderGL *shader = zt_mallocStructArena(ztShaderGL, arena);
	shader->program_id = program;
	shader->vert_id = vert;
	shader->frag_id = frag;
	shader->geom_id = geom;
	shader->arena = arena;

	// extract shader variables
	int uniform_count = 0;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniform_count);

	shader->uniforms_count = uniform_count;
	shader->uniforms = zt_mallocStructArrayArena(ztShaderGL::Uniform, uniform_count, arena);

	zt_fiz(uniform_count) {
		int len = 0, size = 0;
		GLenum type = 0;
		char varname[256] = { 0 };
		glGetActiveUniform(program, i, zt_elementsOf(varname), &len, &size, &type, varname);
		varname[len] = 0;

		shader->uniforms[i].name = zt_stringMakeFrom(varname, arena);
		shader->uniforms[i].type = type;
		shader->uniforms[i].location = glGetUniformLocation(program, varname);
		shader->uniforms[i].name_hash = zt_strHash(shader->uniforms[i].name);
	}

	return shader;
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderFree(ztShaderGL *shader)
{
	if (shader == nullptr) {
		return;
	}

	zt_fiz(shader->uniforms_count) {
		zt_stringFree(shader->uniforms[i].name, shader->arena);
	}
	zt_freeArena(shader->uniforms, shader->arena);

	GLint ids[3] = { shader->vert_id, shader->frag_id, shader->geom_id };

	zt_fiz(zt_elementsOf(ids)) {
		if (ids[i]) {
			ztgl_callAndReportOnError(glDeleteShader(ids[i]));
			ztgl_callAndReportOnError(glDetachShader(shader->program_id, ids[i]));
		}
	}

	ztgl_callAndReportOnError(glDeleteProgram(shader->program_id));

	zt_freeArena(shader, shader->arena);
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderBegin(ztShaderGL *shader)
{
	zt_returnOnNull(shader);
	ztgl_callAndReportOnErrorFast(glUseProgram(shader->program_id));
	glBindTexture(GL_TEXTURE_2D, 0);
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderEnd(ztShaderGL *shader)
{
	zt_returnOnNull(shader);
	ztgl_callAndReportOnErrorFast(glUseProgram(0));
}

// ------------------------------------------------------------------------------------------------

bool ztgl_shaderHasVariable(ztShaderGL *shader, u32 name_hash)
{
	zt_returnValOnNull(shader, false);
	zt_fiz(shader->uniforms_count) {
		if (shader->uniforms[i].name_hash == name_hash) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline GLint _ztgl_shaderGetUniformLocation(ztShaderGL *shader, u32 name_hash)
{
	zt_returnValOnNull(shader, -1);
	zt_fiz(shader->uniforms_count) {
		if (shader->uniforms[i].name_hash == name_hash) {
			return shader->uniforms[i].location;
			break;
		}
	}
	return -1;
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableFloat(ztShaderGL *shader, u32 name_hash, r32 value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform1fv(location, 1, &value));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableInt(ztShaderGL *shader, u32 name_hash, i32 value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform1i(location, value));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableVec2(ztShaderGL *shader, u32 name_hash, const ztVec2& value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform2fv(location, 1, value.values));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableVec3(ztShaderGL *shader, u32 name_hash, const ztVec3& value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform3fv(location, 1, value.values));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableVec4(ztShaderGL *shader, u32 name_hash, const ztVec4& value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform4fv(location, 1, value.values));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableMat4(ztShaderGL *shader, u32 name_hash, const ztMat4& value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniformMatrix4fv(location, 1, GL_FALSE, value.values));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableMat3(ztShaderGL *shader, u32 name_hash, r32 value[12])
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniformMatrix3fv(location, 1, GL_FALSE, value));
}

// ------------------------------------------------------------------------------------------------

void ztgl_shaderVariableTex(ztShaderGL *shader, u32 name_hash, i32 value)
{
	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform1i(location, value));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


ztInternal ztTextureGL *_ztgl_textureMakeBase(ztMemoryArena *arena, byte *pixel_data, i32 width, i32 height, i32 depth, i32 flags)
{
#if 1
	if (pixel_data) {
		int half_height = height / 2;
		u32* pix_u32 = ((u32*)pixel_data);
		for (int y = 0; y < half_height; ++y) {
			for (int x = 0; x < width; ++x) {
				int idx_1 = (y * width) + x;
				int idx_2 = (((height - y) - 1) * width) + x;
				uint32 pixel = pix_u32[idx_2];
				pix_u32[idx_2] = pix_u32[idx_1];
				pix_u32[idx_1] = pixel;
			}
		}
	}
#endif
	bool render_target = pixel_data == nullptr;

	struct OpenGL
	{
		static bool loadTexture(GLuint *tex_id, byte *pixel_data, i32 width, i32 height, i32 flags)
		{
			ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
			ztgl_callAndReturnValOnError(glActiveTexture(GL_TEXTURE0), false);
			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);
			if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
			}
			else {
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
			}
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);

			ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data), false);
			if (zt_bitIsSet(flags, ztTextureGLFlags_MipMaps)) {
				ztgl_callAndReturnValOnError(glGenerateMipmap(GL_TEXTURE_2D), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST), false);
			}
			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), false);

			return true;
		}

		static bool makeRenderTarget(GLuint *tex_id, GLuint *frame_buffer_id, GLuint *depth_buffer_id, GLuint *resolve_buffer_id, GLuint *render_target_id, i32 width, i32 height, i32 flags)
		{
			ztgl_callAndReturnValOnError(glGenFramebuffers(1, frame_buffer_id), false);

			if (zt_bitIsSet(flags, ztTextureGLFlags_DepthMap)) {
				ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
				//ztgl_callAndReturnValOnError(glActiveTexture(GL_TEXTURE0), false);
				ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
				GLfloat border_color[] = { 1.f, 1.f, 1.f, 1.f };
				ztgl_callAndReturnValOnError(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color), false);

				ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);
				ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *tex_id, 0), false);
				ztgl_callAndReturnValOnError(glDrawBuffer(GL_NONE), false);
				ztgl_callAndReturnValOnError(glReadBuffer(GL_NONE), false);
			}
			else {
				ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);

				ztgl_callAndReturnValOnError(glGenRenderbuffers(1, depth_buffer_id), false);
				ztgl_callAndReturnValOnError(glBindRenderbuffer(GL_RENDERBUFFER, *depth_buffer_id), false);
				ztgl_callAndReturnValOnError(glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, width, height), false);
				ztgl_callAndReturnValOnError(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depth_buffer_id), false);

				ztgl_callAndReturnValOnError(glGenTextures(1, render_target_id), false);
				ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, *render_target_id), false);
				ztgl_callAndReturnValOnError(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, width, height, true), false);
				ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, *render_target_id, 0), false);

				ztgl_callAndReturnValOnError(glGenFramebuffers(1, resolve_buffer_id), false);
				ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *resolve_buffer_id), false);

				ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
				ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0), false);
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr), false);
				ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *tex_id, 0), false);
			}

			ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, 0), false);
			ztgl_callAndReturnValOnError(glClear(GL_COLOR_BUFFER_BIT), false);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				zt_logCritical("OpenGL frame buffer status is not complete");
				return false;
			}

			return true;
		}
	};

	GLuint tex_id = 0, fb_id = 0, db_id = 0, rb_id = 0, rt_id = 0;

	if (!render_target) {
		if (!OpenGL::loadTexture(&tex_id, pixel_data, width, height, flags)) {
			zt_logCritical("Unable to load image into texture");
			return nullptr;
		}
	}
	else {
		if (!OpenGL::makeRenderTarget(&tex_id, &fb_id, &db_id, &rb_id, &rt_id, width, height, flags)) {
			zt_logCritical("Unable to create render target");
			return nullptr;
		}
	}

	ztTextureGL *texture = zt_mallocStructArena(ztTextureGL, arena);

	texture->texid = tex_id;
	texture->fbo = fb_id;
	texture->dbo = db_id;
	texture->rt = rt_id;
	texture->rb = rb_id;
	texture->w = width;
	texture->h = height;
	texture->d = 4;
	texture->flags = flags;
	texture->arena = arena;

	return texture;
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeFromPixelData(byte *pixels, int w, int h, int d, i32 flags)
{
	return ztgl_textureMakeFromPixelData(zt_memGetGlobalArena(), pixels, w, h, d, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeFromPixelData(ztMemoryArena *arena, byte *pixels, int w, int h, int d, i32 flags)
{
	return _ztgl_textureMakeBase(arena, pixels, w, h, d, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeCubeMapFromPixelData(byte **pixels, int w, int h, int d)
{
	return ztgl_textureMakeCubeMapFromPixelData(zt_memGetGlobalArena(), pixels, w, h, d);
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeCubeMapFromPixelData(ztMemoryArena *arena, byte **pixels, int w, int h, int d)
{
	struct local
	{
		static bool loadTexture(GLuint *tex_id, byte *tex_data[ztTextureGLCubeMapFiles_MAX], int w, int h)
		{
			ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_CUBE_MAP, *tex_id), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE), false);

			for (int i = 0; i < 6; ++i) {
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data[i]), false);

				if (false) {
					ztgl_callAndReturnValOnError(glGenerateMipmap(GL_TEXTURE_CUBE_MAP), false);
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST), false);
				}
			}

			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_CUBE_MAP, 0), false);

			return true;
		}

	};

	GLuint texid = 0;
	if (!local::loadTexture(&texid, pixels, w, h)) {
		zt_logCritical("Unable to load images into cube map texture");
		return nullptr;
	}

	ztTextureGL *texture = zt_mallocStructArena(ztTextureGL, arena);

	texture->texid = texid;
	texture->fbo = 0;
	texture->dbo = 0;
	texture->rt = 0;
	texture->rb = 0;
	texture->w = w;
	texture->h = h;
	texture->d = 4;
	texture->flags = ztTextureGLFlags_CubeMap;
	texture->arena = arena;

	return texture;
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeRenderTarget(int w, int h, i32 flags)
{
	return ztgl_textureMakeRenderTarget(zt_memGetGlobalArena(), w, h, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeRenderTarget(ztMemoryArena *arena, int w, int h, i32 flags)
{
	return _ztgl_textureMakeBase(arena, nullptr, w, h, 4, flags);
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeDepthRenderTarget(int w, int h)
{
	return ztgl_textureMakeDepthRenderTarget(zt_memGetGlobalArena(), w, h);
}

// ------------------------------------------------------------------------------------------------

ztTextureGL *ztgl_textureMakeDepthRenderTarget(ztMemoryArena *arena, int w, int h)
{
	return ztgl_textureMakeRenderTarget(arena, w, h, ztTextureGLFlags_DepthMap);
}

// ------------------------------------------------------------------------------------------------

void ztgl_textureFree(ztTextureGL *texture)
{
	if(texture == nullptr) {
		return;
	}

	if (texture->dbo != 0) {
		ztgl_callAndReportOnError(glDeleteRenderbuffers(1, &texture->dbo));
		ztgl_callAndReportOnError(glDeleteTextures(1, &texture->rt));
		ztgl_callAndReportOnError(glDeleteFramebuffers(1, &texture->rb));
	}
	if ( texture->fbo != 0 ) {
		ztgl_callAndReportOnError(glDeleteFramebuffers(1, &texture->fbo));
	}
	if ( texture->texid != 0 ) {
		ztgl_callAndReportOnError(glDeleteTextures(1, &texture->texid));
	}

	zt_freeArena(texture, texture->arena);
}

// ------------------------------------------------------------------------------------------------

void ztgl_textureBindReset()
{
	ztgl_callAndReportOnError(glBindTexture(GL_TEXTURE_2D, 0));
	ztgl_callAndReportOnError(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

// ------------------------------------------------------------------------------------------------

void ztgl_textureBind(ztTextureGL *texture, int as_idx)
{
	ztgl_callAndReportOnErrorFast(glActiveTexture(GL_TEXTURE0 + as_idx));

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_CubeMap)) {
		ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_CUBE_MAP, texture->texid));
	}
	else {
		ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_2D, texture->texid));
	}
}

// ------------------------------------------------------------------------------------------------

void ztgl_textureRenderTargetPrepare(ztTextureGL *texture)
{
	zt_returnOnNull(texture);

	ztgl_callAndReportOnErrorFast(glViewport(0, 0, texture->w, texture->h));
	ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_FRAMEBUFFER, texture->fbo));

	ztgl_callAndReportOnErrorFast(glMatrixMode(GL_PROJECTION));
	ztgl_callAndReportOnErrorFast(glEnable(GL_TEXTURE_2D));
	ztgl_callAndReportOnErrorFast(glEnable(GL_BLEND));
	ztgl_callAndReportOnErrorFast(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glEnable(GL_MULTISAMPLE);

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_DepthMap)) {
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);
	}
}

// ------------------------------------------------------------------------------------------------

void ztgl_textureRenderTargetCommit(ztTextureGL *texture, ztContextGL *context)
{
	ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_DepthMap)) {
		glCullFace(GL_BACK);
	}

	glDisable(GL_MULTISAMPLE);

	if (texture->dbo != 0) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, texture->fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, texture->rb);

		glBlitFramebuffer(0, 0, texture->w, texture->h, 0, 0, texture->w, texture->h, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	ztgl_setViewport(context);
}

// ------------------------------------------------------------------------------------------------

bool ztgl_textureIsRenderTarget(ztTextureGL *texture)
{
	zt_returnValOnNull(texture, false);
	return texture->fbo != 0;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void ztgl_drawVertices(GLenum mode, ztVertexEntryGL *entries, int entries_count, void *vertices, int vert_count)
{
	int vert_size = 0;
	zt_fiz(entries_count) {
		vert_size += entries[i].size;
	}

	int size = 0;
	zt_fiz(entries_count) {
		int attrib_size = 0;
		switch (entries[i].type)
		{
			case GL_FLOAT: {
				attrib_size = 4;
			} break;

			default: {
				zt_assert(false);
			} break;
		}

		ztgl_callAndReportOnError(glVertexAttribPointer(i, entries[i].size / attrib_size, entries[i].type, GL_FALSE, vert_size, (GLvoid*)((byte*)vertices + size)));
		ztgl_callAndReportOnError(glEnableVertexAttribArray(i));

		size += entries[i].size;
	}

	glDrawArrays(mode, 0, vert_count);
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztVertexArrayGL *ztgl_vertexArrayMake(ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count)
{
	return ztgl_vertexArrayMake(zt_memGetGlobalArena(), entries, entries_count, vert_data, vert_count);
}

// ------------------------------------------------------------------------------------------------

ztVertexArrayGL *ztgl_vertexArrayMake(ztMemoryArena *arena, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count)
{
	zt_assertReturnValOnFail(entries_count > 0, nullptr);
	zt_assertReturnValOnFail(vert_count > 0, nullptr);
	zt_returnValOnNull(vert_data, nullptr);

	ztVertexArrayGL *vertex_array = zt_mallocStructArena(ztVertexArrayGL, arena);
	vertex_array->entries = zt_mallocStructArrayArena(ztVertexEntryGL, entries_count, arena);
	vertex_array->entries_count = entries_count;
	zt_memCpy(vertex_array->entries, entries_count * zt_sizeof(ztVertexEntryGL), entries, entries_count *  zt_sizeof(ztVertexEntryGL));

	int vert_size = 0;
	zt_fiz(entries_count) {
		vert_size += entries[i].size;
	}

	ztgl_callAndReturnValOnError(glGenVertexArrays(1, &vertex_array->vao), nullptr);
	ztgl_callAndReturnValOnError(glGenBuffers(1, &vertex_array->vbo), nullptr);

	ztgl_callAndReportOnError(glBindVertexArray(vertex_array->vao));
	{
		ztgl_callAndReportOnError(glBindBuffer(GL_ARRAY_BUFFER, vertex_array->vbo));
		ztgl_callAndReportOnError(glBufferData(GL_ARRAY_BUFFER, vert_count * vert_size, vert_data, GL_STATIC_DRAW));

		int size = 0;
		zt_fiz(entries_count) {
			int attrib_size = 0;
			switch (entries[i].type)
			{
				case GL_FLOAT: {
					attrib_size = 4;
				} break;

				default: {
					zt_assert(false);
				} break;
			}

			ztgl_callAndReportOnError(glVertexAttribPointer(i, entries[i].size / attrib_size, entries[i].type, GL_FALSE, vert_size, (GLvoid*)size));
			ztgl_callAndReportOnError(glEnableVertexAttribArray(i));

			size += entries[i].size;
		}
		ztgl_callAndReportOnError(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
	ztgl_callAndReportOnError(glBindVertexArray(0));

	vertex_array->vert_count = vert_count;
	vertex_array->arena = arena;
	return vertex_array;
}

// ------------------------------------------------------------------------------------------------

void ztgl_vertexArrayFree(ztVertexArrayGL *vertex_array)
{
	if (vertex_array == nullptr) {
		return;
	}

	ztgl_callAndReportOnError(glDeleteVertexArrays(1, &vertex_array->vao));
	ztgl_callAndReportOnError(glDeleteBuffers(1, &vertex_array->vbo));

	zt_freeArena(vertex_array->entries, vertex_array->arena);
	zt_freeArena(vertex_array, vertex_array->arena);
}

// ------------------------------------------------------------------------------------------------

void ztgl_vertexArrayDraw(ztVertexArrayGL *vertex_array, GLenum mode)
{
	ztgl_callAndReportOnErrorFast(glBindVertexArray(vertex_array->vao));
	ztgl_callAndReportOnErrorFast(glDrawArrays(mode, 0, vertex_array->vert_count));
	ztgl_callAndReportOnErrorFast(glBindVertexArray(0));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // implementation
