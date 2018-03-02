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

// ================================================================================================================================================================================================

#define ZT_OPENGL


// ================================================================================================================================================================================================

#include "zt_tools.h"

#if defined(ZT_WINDOWS)
#include <windows.h>
#include <gl/GL.h>

#define ZT_OPENGL_HAS_VAOS

#elif defined(ZT_EMSCRIPTEN)
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <gl/GLU.h>

#define ZT_GLES2
#define ZT_GLES

#elif defined(ZT_ANDROID)
#include <GLES/gl.h>
#include <EGL/egl.h>

#define ZT_GLES2
#define ZT_GLES

#endif



// ================================================================================================================================================================================================

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

#if !defined(ZT_ANDROID)
typedef ptrdiff_t GLsizeiptr;
#endif

// ================================================================================================================================================================================================

#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_LINK_STATUS 0x8B82
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_DYNAMIC_DRAW 0x88E8
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
#define GL_ACTIVE_ATTRIBUTES 0x8B89
#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_BOOL 0x8B56
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLER_CUBE 0x8B60
#define GL_MIRRORED_REPEAT 0x8370
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_DEPTH_COMPONENT32 0x81A7
#define GL_RGBA16F 0x881A
#define GL_RGB16F 0x881B
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F

#if defined(ZT_ANDROID)
#define GL_INT 0x1404
#define GL_DEPTH_COMPONENT 0x1902
#define GL_RGBA8 0x8058
#endif

// ================================================================================================================================================================================================

struct ztContextGL;

ztContextGL *ztgl_contextMake(void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags); // ztRendererFlags
ztContextGL *ztgl_contextMake(ztMemoryArena *arena, void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags); // ztRendererFlags
void         ztgl_contextFree(ztContextGL *context);

void         ztgl_contextDisplay(ztContextGL *context);

ztVec2i      ztgl_contextGetSize(ztContextGL *context);
bool         ztgl_contextSetSize(ztContextGL *context, i32 w, i32 h, i32 nw, i32 nh);
bool         ztgl_contextIsFullscreen(ztContextGL *context);
bool         ztgl_contextToggleFullscreen(ztContextGL *context, bool fullscreen);
bool         ztgl_contextChangeResolution(ztContextGL *context, i32 w, i32 h);

// ================================================================================================================================================================================================

void ztgl_clearColor(ztVec4 color);
void ztgl_clearColor(r32 r, r32 g, r32 b, r32 a);
void ztgl_clearDepth();
void ztgl_clear(ztVec4 color);
void ztgl_clear(r32 r, r32 g, r32 b, r32 a);

bool ztgl_setViewport(i32 width, i32 height);
bool ztgl_setViewport(ztContextGL *context);

bool ztgl_clipViewport(i32 x, i32 y, i32 w, i32 h);
bool ztgl_clipReset();

void ztgl_cullFront();
void ztgl_cullBack();
void ztgl_cullNone();

void ztgl_depthTestOff();
void ztgl_depthTestNever();
void ztgl_depthTestLess();
void ztgl_depthTestLessEqual();
void ztgl_depthTestEqual();
void ztgl_depthTestGreater();
void ztgl_depthTestNotEqual();
void ztgl_depthTestGreaterEqual();
void ztgl_depthTestAlways();

// ================================================================================================================================================================================================

enum ztGLBlendMode_Enum
{
	ztGLBlendMode_Zero,
	ztGLBlendMode_One,
	ztGLBlendMode_SourceColor,
	ztGLBlendMode_OneMinusSourceColor,
	ztGLBlendMode_DestColor,
	ztGLBlendMode_OneMinusDestColor,
	ztGLBlendMode_SourceAlpha,
	ztGLBlendMode_OneMinusSourceAlpha,
	ztGLBlendMode_DestAlpha,
	ztGLBlendMode_OneMinusDestAlpha,

	ztGLBlendMode_MAX,
};

void ztgl_blendMode(ztGLBlendMode_Enum source, ztGLBlendMode_Enum dest);

// ================================================================================================================================================================================================

bool    ztgl_checkAndReportError(const char *function, int line = 0);
int     ztgl_clearErrors();

#if defined(ZT_OPENGL_DEBUGGING_LOGALL)
#	define ztgl_callAndReturnOnError(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; if (ztgl_checkAndReportError(#function)) return;
#	define ztgl_callAndReturnValOnError(function, retval) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; if (ztgl_checkAndReportError(#function)) return retval;
#	define ztgl_callAndReportOnError(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; ztgl_checkAndReportError(#function);
#else
#	if defined(ZT_EMSCRIPTEN) && !defined(ZT_OPENGL_DEBUGGING) // checking errors is too expensive here
#		define ztgl_callAndReturnOnError(function) function;
#		define ztgl_callAndReturnValOnError(function, retval) function;
#		define ztgl_callAndReportOnError(function) function;
#	else
#		define ztgl_callAndReturnOnError(function) function; if (ztgl_checkAndReportError(#function, __LINE__)) return;
#		define ztgl_callAndReturnValOnError(function, retval) function; if (ztgl_checkAndReportError(#function, __LINE__)) return retval;
#		define ztgl_callAndReportOnError(function) function; ztgl_checkAndReportError(#function, __LINE__);
#	endif
#endif

#if defined(ZT_OPENGL_DEBUGGING)
#if defined(ZT_OPENGL_DEBUGGING_LOGALL)
#	define ztgl_callAndReportOnErrorFast(function) zt_logDebug("Calling " #function " (%s line %d)", __FILE__, __LINE__); function; ztgl_checkAndReportError(#function);
#else
#	define ztgl_callAndReportOnErrorFast(function) function; ztgl_checkAndReportError(#function, __LINE__);
#endif
#else
#	define ztgl_callAndReportOnErrorFast(function) function;
#endif


// ================================================================================================================================================================================================

struct ztShaderGL
{
	GLuint program_id;
	GLuint vert_id, frag_id, geom_id;

	struct Uniform
	{
		GLint    location;
		GLenum   type;
		ztString name;
		u32      name_hash;
	};

	Uniform        *uniforms;
	int             uniforms_count;

	struct Inputs
	{
		GLint    location;
		GLenum   type;
		ztString name;
		u32      name_hash;
	};

	Inputs         *inputs;
	int             inputs_count;

	struct Outputs
	{
		GLint    location;
		GLenum   type;
		ztString name;
		u32      name_hash;
	};

	Outputs        *outputs;
	int             outputs_count;

	int             textures_bound;

	bool            in_use;

	ztMemoryArena  *arena;
	ztContextGL *context;
};

// ================================================================================================================================================================================================

struct ztTextureGL;

// ================================================================================================================================================================================================

ztShaderGL *ztgl_shaderMake(ztContextGL *context, const char *vert_src, const char *frag_src, const char *geom_src = nullptr);
ztShaderGL *ztgl_shaderMake(ztContextGL *context, ztMemoryArena *arena, const char *vert_src, const char *frag_src, const char *geom_src = nullptr);
void        ztgl_shaderFree(ztShaderGL *shader);

void        ztgl_shaderBegin(ztShaderGL *shader);
void        ztgl_shaderEnd(ztShaderGL *shader);

bool        ztgl_shaderHasVariable(ztShaderGL *shader, u32 name_hash);

void        ztgl_shaderVariableFloat(ztShaderGL *shader, u32 name_hash, r32 value);
void        ztgl_shaderVariableInt(ztShaderGL *shader, u32 name_hash, i32 value);
void        ztgl_shaderVariableVec2(ztShaderGL *shader, u32 name_hash, r32 value[2]);
void        ztgl_shaderVariableVec3(ztShaderGL *shader, u32 name_hash, r32 value[3]);
void        ztgl_shaderVariableVec4(ztShaderGL *shader, u32 name_hash, r32 value[4]);
void        ztgl_shaderVariableMat4(ztShaderGL *shader, u32 name_hash, r32 value[16]);
void        ztgl_shaderVariableMat3(ztShaderGL *shader, u32 name_hash, r32 value[12]);
void        ztgl_shaderVariableTex(ztShaderGL *shader, u32 name_hash, ztTextureGL *tex);

int         ztgl_shaderGetOutputs(ztShaderGL *shader, ztVariant_Enum *types, int types_size);

ztShaderGL *ztgl_shaderMakePointLightShadows(ztContextGL *context);


// ================================================================================================================================================================================================

enum ztTextureGLFlags_Enum
{
	ztTextureGLFlags_MipMaps             = (1<<0),
	ztTextureGLFlags_DepthMap            = (1<<1),
	ztTextureGLFlags_PixelPerfect        = (1<<2),
	ztTextureGLFlags_CubeMap             = (1<<3),
	ztTextureGLFlags_RenderTargetScreen  = (1<<4),
	ztTextureGLFlags_HDR                 = (1<<5),
	ztTextureGLFlags_Repeat              = (1<<6),
	ztTextureGLFlags_Multisample         = (1<<7),
	ztTextureGLFlags_FlipOnLoad          = (1<<8),

	ztTextureGLFlags_RenderTargetWriting = (1<<30),
	ztTextureGLFlags_Attachment          = (1<<31),
};

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

enum ztTextureGLColorFormat_Enum
{
	ztTextureGLColorFormat_RGBA,
	ztTextureGLColorFormat_RGB,
	ztTextureGLColorFormat_RGBA16F,
	ztTextureGLColorFormat_RGB16F,

	ztTextureGLColorFormat_MAX,
};

// ================================================================================================================================================================================================

struct ztTextureGL
{
	GLuint texid;

	GLuint fbo;	// frame buffer
	GLuint dbo;	// depth buffer
	GLuint rt;	// render texture
	GLuint rb;	// resolve buffer

	int    attachments_count;
	GLuint attachments[8];
	bool   attachments_enabled[8];

	int w, h, d, wa, ha;

	i32 flags;

	ztMemoryArena *arena;
	ztContextGL *context;
};

// ================================================================================================================================================================================================

#define ZT_FUNC_GL_TEXTURE_RENDER(name)	void name(int side, int mip_level, int w, int h, ztMat4 *proj, ztMat4 *view, void *user_data)
typedef ZT_FUNC_GL_TEXTURE_RENDER(ztTextureGLRender_Func);

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeFromPixelData               (ztContextGL *context, byte *pixels, int w, int h, int d, i32 flags);
ztTextureGL *ztgl_textureMakeFromPixelData               (ztContextGL *context, ztMemoryArena *arena, byte *pixels, int w, int h, int d, i32 flags);
ztTextureGL *ztgl_textureMakeCubeMapFromPixelData        (ztContextGL *context, byte **pixels, int w, int h, int d);
ztTextureGL *ztgl_textureMakeCubeMapFromPixelData        (ztContextGL *context, ztMemoryArena *arena, byte **pixels, int w, int h, int d);
ztTextureGL *ztgl_textureMakeCubeMapFromRender           (ztContextGL *context, int w, int h, int mip_map_levels, ztTextureGLRender_Func *render_func, void *user_data); // calls render_func for each side (6 total)
ztTextureGL *ztgl_textureMakeCubeMapFromHDR              (ztContextGL *context, ztTextureGL *hdr_texture, int w, int h);
ztTextureGL *ztgl_textureMakeCubeMapForDepth             (ztContextGL *context, i32 dimension);
ztTextureGL *ztgl_textureMakeIrradianceCubeMapFromCubeMap(ztContextGL *context, ztTextureGL *cube_map_texture);
ztTextureGL *ztgl_textureMakePrefilterCubeMapFromCubeMap (ztContextGL *context, ztTextureGL *cube_map_texture);
ztTextureGL *ztgl_textureMakeRenderTarget                (ztContextGL *context, int w, int h, i32 flags);
ztTextureGL *ztgl_textureMakeRenderTarget                (ztContextGL *context, ztMemoryArena *arena, int w, int h, i32 flags);
ztTextureGL *ztgl_textureMakeDepthRenderTarget           (ztContextGL *context, int w, int h);
ztTextureGL *ztgl_textureMakeDepthRenderTarget           (ztContextGL *context, ztMemoryArena *arena, int w, int h);

void         ztgl_textureFree                            (ztTextureGL *texture);

void	     ztgl_textureBindReset                       (ztShaderGL *shader);
void	     ztgl_textureBind                            (ztTextureGL *texture, int as_idx);

void         ztgl_textureRenderTargetPrepare             (ztTextureGL *texture, bool clear);
void         ztgl_textureRenderTargetCommit              (ztTextureGL *texture, ztContextGL *context);
ztTextureGL *ztgl_textureRenderTargetAddAttachment       (ztTextureGL *texture, ztTextureGLColorFormat_Enum color_format);
void         ztgl_textureRenderTargetAttachmentEnable    (ztTextureGL *texture, int attachment_idx, bool enable);

bool         ztgl_textureIsRenderTarget                  (ztTextureGL *texture);

void         ztgl_textureGetPixels                       (ztTextureGL *texture, ztContextGL *context, byte *pixels); // pixels = w * h * 4


// ================================================================================================================================================================================================

struct ztVertexEntryGL
{
	GLenum type;
	int size;
};

// ================================================================================================================================================================================================

void ztgl_drawVertices(GLenum mode, ztVertexEntryGL *entries, int entries_count, void *vertices, int vert_count);


// ================================================================================================================================================================================================

struct ztVertexArrayGL
{
	GLuint vao;
	GLuint vbo;
	int    vert_count;
	int    vert_count_active;

#	if !defined(ZT_OPENGL_HAS_VAOS)
	ztVertexEntryGL entries[8];
	void           *vert_data;
#	endif
};

// ================================================================================================================================================================================================

bool ztgl_vertexArrayMake  (ztVertexArrayGL *vertex_array, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count);
void ztgl_vertexArrayFree  (ztVertexArrayGL *vertex_array);
bool ztgl_vertexArrayUpdate(ztVertexArrayGL *vertex_array, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count);
void ztgl_vertexArrayDraw  (ztVertexArrayGL *vertex_array, GLenum mode = GL_TRIANGLES);

// ================================================================================================================================================================================================

#if defined(ZT_WINDOWS)
#	define ZTGL_API	__stdcall

typedef void (APIENTRY *GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

typedef int       (ZTGL_API *ztgl_wglSwapIntervalEXT_Func) (int interval);
typedef HGLRC     (ZTGL_API *ztgl_wglCreateContextAttribsARB_Func) (HDC hDC, HGLRC hShareContext, const int* attribList);
typedef GLuint    (ZTGL_API *ztgl_glCreateShader_Func) (GLenum type);
typedef void      (ZTGL_API *ztgl_glShaderSource_Func) (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
typedef void      (ZTGL_API *ztgl_glCompileShader_Func) (GLuint shader);
typedef void      (ZTGL_API *ztgl_glGetShaderiv_Func) (GLuint shader, GLenum pname, GLint* param);
typedef void      (ZTGL_API *ztgl_glGetShaderInfoLog_Func) (GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void      (ZTGL_API *ztgl_glDeleteShader_Func) (GLuint shader);
typedef GLuint    (ZTGL_API *ztgl_glCreateProgram_Func) (void);
typedef void      (ZTGL_API *ztgl_glAttachShader_Func) (GLuint program, GLuint shader);
typedef void      (ZTGL_API *ztgl_glLinkProgram_Func) (GLuint program);
typedef void      (ZTGL_API *ztgl_glGetProgramiv_Func) (GLuint program, GLenum pname, GLint* param);
typedef void      (ZTGL_API *ztgl_glGetProgramInfoLog_Func) (GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void      (ZTGL_API *ztgl_glGetProgramResourceiv_Func) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei *length, GLint *params);
typedef void      (ZTGL_API *ztgl_glGetProgramResourceName_Func) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar *name);
typedef void      (ZTGL_API *ztgl_glDeleteProgram_Func) (GLuint program);
typedef void      (ZTGL_API *ztgl_glDetachShader_Func) (GLuint program, GLuint shader);
typedef void      (ZTGL_API *ztgl_glUseProgram_Func) (GLuint program);
typedef void      (ZTGL_API *ztgl_glBlendFuncSeparate_Func) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void      (ZTGL_API *ztgl_glVertexAttribPointer_Func) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void      (ZTGL_API *ztgl_glVertexAttribIPointer_Func) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
typedef void      (ZTGL_API *ztgl_glEnableVertexAttribArray_Func) (GLuint index);
typedef void      (ZTGL_API *ztgl_glDisableVertexAttribArray_Func) (GLuint index);
typedef GLint     (ZTGL_API *ztgl_glGetUniformLocation_Func) (GLuint program, const GLchar* name);
typedef GLint     (ZTGL_API *ztgl_glGetAttribLocation_Func) (GLuint program, const GLchar* name);
typedef void      (ZTGL_API *ztgl_glUniformMatrix4fv_Func) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniformMatrix3fv_Func) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform1fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform2fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform3fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform4fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glGenBuffers_Func) (GLsizei n, GLuint* buffers);
typedef void      (ZTGL_API *ztgl_glBindBuffer_Func) (GLenum target, GLuint buffer);
typedef void      (ZTGL_API *ztgl_glGenVertexArrays_Func) (GLsizei n, GLuint* arrays);
typedef void      (ZTGL_API *ztgl_glBindVertexArray_Func) (GLuint array);
typedef void      (ZTGL_API *ztgl_glDeleteVertexArrays_Func) (GLsizei n, const GLuint* arrays);
typedef void      (ZTGL_API *ztgl_glDeleteBuffers_Func) (GLsizei n, const GLuint* buffers);
typedef void      (ZTGL_API *ztgl_glBufferData_Func) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void      (ZTGL_API *ztgl_glActiveTexture_Func) (GLenum texture);
typedef void      (ZTGL_API *ztgl_glGenerateMipmap_Func) (GLenum target);
typedef void      (ZTGL_API *ztgl_glDeleteRenderbuffers_Func) (GLsizei n, const GLuint* renderbuffers);
typedef void      (ZTGL_API *ztgl_glDeleteFramebuffers_Func) (GLsizei n, const GLuint* framebuffers);
typedef void      (ZTGL_API *ztgl_glUniform1i_Func) (GLint location, GLint v0);
typedef void      (ZTGL_API *ztgl_glGenFramebuffers_Func) (GLsizei n, GLuint* framebuffers);
typedef void      (ZTGL_API *ztgl_glBindFramebuffer_Func) (GLenum target, GLuint framebuffer);
typedef void      (ZTGL_API *ztgl_glFramebufferTexture2D_Func) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void      (ZTGL_API *ztgl_glFramebufferTexture_Func) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void      (ZTGL_API *ztgl_glGenRenderbuffers_Func) (GLsizei n, GLuint* renderbuffers);
typedef void      (ZTGL_API *ztgl_glBindRenderbuffer_Func) (GLenum target, GLuint renderbuffer);
typedef GLenum    (ZTGL_API *ztgl_glCheckFramebufferStatus_Func) (GLenum target);
typedef void      (ZTGL_API *ztgl_glRenderbufferStorageMultisample_Func) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void      (ZTGL_API *ztgl_glRenderbufferStorage_Func) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void      (ZTGL_API *ztgl_glFramebufferRenderbuffer_Func) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void      (ZTGL_API *ztgl_glTexImage2DMultisample_Func) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void      (ZTGL_API *ztgl_glBlitFramebuffer_Func) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void      (ZTGL_API *ztgl_glGetActiveUniform_Func) (GLuint program, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void      (ZTGL_API *ztgl_glGetActiveAttrib_Func) (GLuint program, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void      (ZTGL_API *ztgl_glGetUniformfv_Func) (GLuint program, GLint location, GLfloat* params);
typedef void      (ZTGL_API *ztgl_glGetUniformiv_Func) (GLuint program, GLint location, GLint* params);
typedef void      (ZTGL_API *ztgl_glBindAttribLocation_Func) (GLuint program, GLuint index, const GLchar* name);
typedef void      (ZTGL_API *ztgl_glDrawBuffers_Func) (GLsizei n, const GLenum* bufs);
typedef void      (ZTGL_API *ztgl_glDebugMessageCallback_Func) (GLDEBUGPROC callback, const void *userParam);
typedef void      (ZTGL_API *ztgl_glDebugMessageControl_Func) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
// ================================================================================================================================================================================================

#define ZTGL_FUNCTIONS	\
	ZTGL_FUNC_OP(wglSwapIntervalEXT) \
	ZTGL_FUNC_OP(wglCreateContextAttribsARB) \
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
	ZTGL_FUNC_OP(glGetProgramResourceiv) \
	ZTGL_FUNC_OP(glGetProgramResourceName) \
	ZTGL_FUNC_OP(glDeleteProgram) \
	ZTGL_FUNC_OP(glDetachShader) \
	ZTGL_FUNC_OP(glUseProgram) \
	ZTGL_FUNC_OP(glBlendFuncSeparate) \
	ZTGL_FUNC_OP(glVertexAttribPointer) \
	ZTGL_FUNC_OP(glVertexAttribIPointer) \
	ZTGL_FUNC_OP(glEnableVertexAttribArray) \
	ZTGL_FUNC_OP(glDisableVertexAttribArray) \
	ZTGL_FUNC_OP(glGetUniformLocation) \
	ZTGL_FUNC_OP(glGetAttribLocation) \
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
	ZTGL_FUNC_OP(glFramebufferTexture) \
	ZTGL_FUNC_OP(glGenRenderbuffers) \
	ZTGL_FUNC_OP(glBindRenderbuffer) \
	ZTGL_FUNC_OP(glCheckFramebufferStatus) \
	ZTGL_FUNC_OP(glRenderbufferStorageMultisample) \
	ZTGL_FUNC_OP(glRenderbufferStorage) \
	ZTGL_FUNC_OP(glFramebufferRenderbuffer) \
	ZTGL_FUNC_OP(glTexImage2DMultisample) \
	ZTGL_FUNC_OP(glBlitFramebuffer) \
	ZTGL_FUNC_OP(glGetActiveUniform) \
	ZTGL_FUNC_OP(glGetActiveAttrib) \
	ZTGL_FUNC_OP(glGetUniformfv) \
	ZTGL_FUNC_OP(glGetUniformiv) \
	ZTGL_FUNC_OP(glBindAttribLocation) \
	ZTGL_FUNC_OP(glDrawBuffers) \
	ZTGL_FUNC_OP(glDebugMessageCallback) \
	ZTGL_FUNC_OP(glDebugMessageControl)


#define ZTGL_FUNC_OP(func)	extern ztgl_##func##_Func func;
ZTGL_FUNCTIONS
#undef ZTGL_FUNC_OP

#endif // ZT_WINDOWS

#if defined(ZT_ANDROID)
#	define ZTGL_API

typedef GLuint    (ZTGL_API *ztgl_glCreateShader_Func) (GLenum type);
typedef void      (ZTGL_API *ztgl_glShaderSource_Func) (GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
typedef void      (ZTGL_API *ztgl_glCompileShader_Func) (GLuint shader);
typedef void      (ZTGL_API *ztgl_glGetShaderiv_Func) (GLuint shader, GLenum pname, GLint* param);
typedef void      (ZTGL_API *ztgl_glGetShaderInfoLog_Func) (GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void      (ZTGL_API *ztgl_glDeleteShader_Func) (GLuint shader);
typedef GLuint    (ZTGL_API *ztgl_glCreateProgram_Func) (void);
typedef void      (ZTGL_API *ztgl_glAttachShader_Func) (GLuint program, GLuint shader);
typedef void      (ZTGL_API *ztgl_glLinkProgram_Func) (GLuint program);
typedef void      (ZTGL_API *ztgl_glGetProgramiv_Func) (GLuint program, GLenum pname, GLint* param);
typedef void      (ZTGL_API *ztgl_glGetProgramInfoLog_Func) (GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void      (ZTGL_API *ztgl_glGetProgramResourceiv_Func) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum* props, GLsizei bufSize, GLsizei *length, GLint *params);
typedef void      (ZTGL_API *ztgl_glGetProgramResourceName_Func) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar *name);
typedef void      (ZTGL_API *ztgl_glDeleteProgram_Func) (GLuint program);
typedef void      (ZTGL_API *ztgl_glDetachShader_Func) (GLuint program, GLuint shader);
typedef void      (ZTGL_API *ztgl_glUseProgram_Func) (GLuint program);
typedef void      (ZTGL_API *ztgl_glBlendFuncSeparate_Func) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void      (ZTGL_API *ztgl_glVertexAttribPointer_Func) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void      (ZTGL_API *ztgl_glVertexAttribIPointer_Func) (GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
typedef void      (ZTGL_API *ztgl_glEnableVertexAttribArray_Func) (GLuint index);
typedef void      (ZTGL_API *ztgl_glDisableVertexAttribArray_Func) (GLuint index);
typedef GLint     (ZTGL_API *ztgl_glGetUniformLocation_Func) (GLuint program, const GLchar* name);
typedef GLint     (ZTGL_API *ztgl_glGetAttribLocation_Func) (GLuint program, const GLchar* name);
typedef void      (ZTGL_API *ztgl_glUniformMatrix4fv_Func) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniformMatrix3fv_Func) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform1fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform2fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform3fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glUniform4fv_Func) (GLint location, GLsizei count, const GLfloat* value);
typedef void      (ZTGL_API *ztgl_glGenVertexArrays_Func) (GLsizei n, GLuint* arrays);
typedef void      (ZTGL_API *ztgl_glBindVertexArray_Func) (GLuint array);
typedef void      (ZTGL_API *ztgl_glDeleteVertexArrays_Func) (GLsizei n, const GLuint* arrays);
typedef void      (ZTGL_API *ztgl_glGenerateMipmap_Func) (GLenum target);
typedef void      (ZTGL_API *ztgl_glDeleteRenderbuffers_Func) (GLsizei n, const GLuint* renderbuffers);
typedef void      (ZTGL_API *ztgl_glDeleteFramebuffers_Func) (GLsizei n, const GLuint* framebuffers);
typedef void      (ZTGL_API *ztgl_glUniform1i_Func) (GLint location, GLint v0);
typedef void      (ZTGL_API *ztgl_glGenFramebuffers_Func) (GLsizei n, GLuint* framebuffers);
typedef void      (ZTGL_API *ztgl_glBindFramebuffer_Func) (GLenum target, GLuint framebuffer);
typedef void      (ZTGL_API *ztgl_glFramebufferTexture2D_Func) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void      (ZTGL_API *ztgl_glGenRenderbuffers_Func) (GLsizei n, GLuint* renderbuffers);
typedef void      (ZTGL_API *ztgl_glBindRenderbuffer_Func) (GLenum target, GLuint renderbuffer);
typedef GLenum    (ZTGL_API *ztgl_glCheckFramebufferStatus_Func) (GLenum target);
typedef void      (ZTGL_API *ztgl_glRenderbufferStorageMultisample_Func) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void      (ZTGL_API *ztgl_glRenderbufferStorage_Func) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void      (ZTGL_API *ztgl_glFramebufferRenderbuffer_Func) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void      (ZTGL_API *ztgl_glTexImage2DMultisample_Func) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void      (ZTGL_API *ztgl_glBlitFramebuffer_Func) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void      (ZTGL_API *ztgl_glGetActiveUniform_Func) (GLuint program, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void      (ZTGL_API *ztgl_glGetActiveAttrib_Func) (GLuint program, GLuint index, GLsizei maxLength, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
typedef void      (ZTGL_API *ztgl_glGetUniformfv_Func) (GLuint program, GLint location, GLfloat* params);
typedef void      (ZTGL_API *ztgl_glGetUniformiv_Func) (GLuint program, GLint location, GLint* params);
typedef void      (ZTGL_API *ztgl_glBindAttribLocation_Func) (GLuint program, GLuint index, const GLchar* name);
typedef void      (ZTGL_API *ztgl_glDrawBuffers_Func) (GLsizei n, const GLenum* bufs);

// ================================================================================================================================================================================================

#define ZTGL_FUNCTIONS	\
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
	ZTGL_FUNC_OP(glGetProgramResourceiv) \
	ZTGL_FUNC_OP(glGetProgramResourceName) \
	ZTGL_FUNC_OP(glDeleteProgram) \
	ZTGL_FUNC_OP(glDetachShader) \
	ZTGL_FUNC_OP(glUseProgram) \
	ZTGL_FUNC_OP(glBlendFuncSeparate) \
	ZTGL_FUNC_OP(glVertexAttribPointer) \
	ZTGL_FUNC_OP(glVertexAttribIPointer) \
	ZTGL_FUNC_OP(glEnableVertexAttribArray) \
	ZTGL_FUNC_OP(glDisableVertexAttribArray) \
	ZTGL_FUNC_OP(glGetUniformLocation) \
	ZTGL_FUNC_OP(glGetAttribLocation) \
	ZTGL_FUNC_OP(glUniformMatrix4fv) \
	ZTGL_FUNC_OP(glUniformMatrix3fv) \
	ZTGL_FUNC_OP(glUniform1fv) \
	ZTGL_FUNC_OP(glUniform2fv) \
	ZTGL_FUNC_OP(glUniform3fv) \
	ZTGL_FUNC_OP(glUniform4fv) \
	ZTGL_FUNC_OP(glGenVertexArrays) \
	ZTGL_FUNC_OP(glBindVertexArray) \
	ZTGL_FUNC_OP(glDeleteVertexArrays) \
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
	ZTGL_FUNC_OP(glRenderbufferStorage) \
	ZTGL_FUNC_OP(glFramebufferRenderbuffer) \
	ZTGL_FUNC_OP(glTexImage2DMultisample) \
	ZTGL_FUNC_OP(glBlitFramebuffer) \
	ZTGL_FUNC_OP(glGetActiveUniform) \
	ZTGL_FUNC_OP(glGetActiveAttrib) \
	ZTGL_FUNC_OP(glGetUniformfv) \
	ZTGL_FUNC_OP(glGetUniformiv) \
	ZTGL_FUNC_OP(glBindAttribLocation) \
	ZTGL_FUNC_OP(glDrawBuffers) \


#define ZTGL_FUNC_OP(func)	extern ztgl_##func##_Func func;
ZTGL_FUNCTIONS
#undef ZTGL_FUNC_OP

#endif // ZT_ANDROID
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_FUNC_DLL_SET_OPENGL_GLOBALS(name) void name(void *memory, int version)
typedef ZT_FUNC_DLL_SET_OPENGL_GLOBALS(zt_dllSetOpenGLGlobals_Func);

#if !defined(ZT_DLL)

void zt_dllSendOpenGLGlobals(zt_dllSetOpenGLGlobals_Func *set_globals);

#endif

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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

	ztVec2i size;
	ztVec2i native_size;

	i32 pixels_per_unit;
	i32 flags;

	RECT screen_area;

	ztMemoryArena *arena;

	ztTextureGL *active_render_target;
};

#elif defined(ZT_EMSCRIPTEN) // end ZT_WINDOWS

struct ztContextGL
{
	SDL_Surface *sdl_screen;

	ztVec2i size;
	ztVec2i native_size;

	i32 pixels_per_unit;
	i32 flags;

	ztVec4i screen_area;

	ztMemoryArena *arena;

	ztTextureGL *active_render_target;
};

#elif defined(ZT_ANDROID) // end ZT_EMSCRIPTEN

struct ztContextGL
{
	EGLDisplay egl_display;
	EGLSurface egl_render_surface;
	EGLContext egl_context;

	ztVec2i size;

	i32 pixels_per_unit;
	i32 flags;

	android_app *game_android_app;

	ztMemoryArena *arena;

	ztTextureGL *active_render_target;
};

#endif // ZT_ANDROID

#endif // include guard
#endif // internal declarations

#if defined(ZT_OPENGL_IMPLEMENTATION)

#if defined(ZT_PROFILE)
#define ZT_PROFILE_OPENGL(section) ZT_PROFILE(section, "OpenGL")
#else
#define ZT_PROFILE_OPENGL(section)
#endif

enum ztRendererFlagsGL_Enum
{
	ztRendererFlagsGL_Windowed           = (1<<0),
	ztRendererFlagsGL_WindowedBorderless = (1<<1),
	ztRendererFlagsGL_Fullscreen         = (1<<2),
	ztRendererFlagsGL_Vsync              = (1<<3),
	ztRendererFlagsGL_RotationAllowed    = (1<<4), // mobile
	ztRendererFlagsGL_VertOrientation    = (1<<5), // mobile
	ztRendererFlagsGL_LockAspect         = (1<<6),
	ztRendererFlagsGL_HideCursor         = (1<<7),
};


// ================================================================================================================================================================================================

#if defined(ZT_WINDOWS)

struct ztOpenGLFunctions
{
#	define ZTGL_FUNC_OP(func)	ztgl_##func##_Func func;
	ZTGL_FUNCTIONS
#	undef ZTGL_FUNC_OP
};

#define ZT_OPENGL_FUNCTIONS_VERSION   1 // update this any time ztOpenGLFunctions is changed

// ================================================================================================================================================================================================

void ztgl_loadFunctions(ztOpenGLFunctions *functions)
{
#	define ZTGL_FUNC_OP(func) functions->func = func;
	ZTGL_FUNCTIONS;
#	undef ZTGL_FUNC_OP
}

// ================================================================================================================================================================================================

void ztgl_saveFunctions(ztOpenGLFunctions *functions)
{
#	define ZTGL_FUNC_OP(func) func = functions->func;
	ZTGL_FUNCTIONS;
#	undef ZTGL_FUNC_OP
}

// ================================================================================================================================================================================================

#if defined(ZT_DLL)

ZT_DLLEXPORT ZT_FUNC_DLL_SET_GAME_GLOBALS(zt_dllSetOpenGLGlobals)
{
	if (version == ZT_OPENGL_FUNCTIONS_VERSION) {
		ztgl_saveFunctions((ztOpenGLFunctions*)memory);
	}
}

#else

void zt_dllSendOpenGLGlobals(zt_dllSetOpenGLGlobals_Func *set_globals)
{
	if (set_globals) {
		ztOpenGLFunctions functions;
		ztgl_loadFunctions(&functions);
		set_globals(&functions, ZT_OPENGL_FUNCTIONS_VERSION);
	}
}

#endif


// ================================================================================================================================================================================================

#pragma comment(lib, "opengl32.lib")

// ================================================================================================================================================================================================

ztInternal void _ztgl_win_loadFunctions()
{
#	define ZTGL_FUNC_OP(func) if(!func) func = (ztgl_##func##_Func)wglGetProcAddress((LPCSTR)((const GLubyte*)#func)); if(func == nullptr) zt_logCritical("Unable to load OpenGL function: %s (%d)", #func, GetLastError());
	ZTGL_FUNCTIONS;
#	undef ZTGL_FUNC_OP
}

// ================================================================================================================================================================================================

void ztgl_win_contextDisplay(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_win_contextDisplay");

	SwapBuffers(context->hdc);
	glFinish();
}

// ================================================================================================================================================================================================

ztInternal void _ztgl_getFullScreenCoords(HWND handle, int *pos_x, int *pos_y, int *screen_w, int *screen_h)
{
	*pos_x = 0;
	*pos_y = 0;
	*screen_w = GetSystemMetrics(SM_CXSCREEN);
	*screen_h = GetSystemMetrics(SM_CYSCREEN);

	RECT win_rect;
	if (GetWindowRect(handle, &win_rect) == TRUE) {
		// make sure we go fullscreen on the right monitor
		ztDisplay displays[16];
		int display_count = zt_displayGetDetails(displays, zt_elementsOf(displays));

		ztVec2 win_pos = zt_vec2(win_rect.left + ((win_rect.right - win_rect.left) / 2.f), win_rect.top + ((win_rect.bottom - win_rect.top) / 2.f));

		zt_fiz(display_count) {
			ztVec2 screen_pos = zt_vec2(displays[i].screen_area.xy) + zt_vec2(displays[i].screen_area.zw) * .5f;
			ztVec2 screen_size = zt_vec2(displays[i].screen_area.zw);

			if (zt_collisionPointInRect(win_pos, screen_pos, screen_size)) {
				*pos_x = displays[i].screen_area.x;
				*pos_y = displays[i].screen_area.y;
				*screen_w = displays[i].screen_area.z;
				*screen_h = displays[i].screen_area.w;
				break;
			}
		}
	}
}

// ================================================================================================================================================================================================

#define GL_DEBUG_SOURCE_API 0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY 0x8249
#define GL_DEBUG_SOURCE_APPLICATION 0x824A
#define GL_DEBUG_SOURCE_OTHER 0x824B

#define GL_DEBUG_TYPE_ERROR 0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824E
#define GL_DEBUG_TYPE_PORTABILITY 0x824F
#define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#define GL_DEBUG_TYPE_OTHER 0x8251

#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_DEBUG_SEVERITY_LOW 0x9148
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B

// ================================================================================================================================================================================================


void WINAPI _ztgl_debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	char *error_source = nullptr;
	switch (source)
	{
		case GL_DEBUG_SOURCE_API            : error_source = "API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM  : error_source = "WINDOW SYSTEM"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: error_source = "SHADER COMPILER"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY    : error_source = "THIRD PARTY"; break;
		case GL_DEBUG_SOURCE_APPLICATION    : error_source = "APPLICATION"; break;
		case GL_DEBUG_SOURCE_OTHER          : error_source = "OTHER"; break;
		default                             : error_source = "UNKNOWN SOURCE"; break;
	}

	char *error_type = nullptr;
	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR              : error_type = "ERROR"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: error_type = "DEPRECATED_BEHAVIOR"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR : error_type = "UNDEFINED_BEHAVIOR"; break;
		case GL_DEBUG_TYPE_PORTABILITY        : error_type = "PORTABILITY"; break;
		case GL_DEBUG_TYPE_PERFORMANCE        : error_type = "PERFORMANCE"; break;
		case GL_DEBUG_TYPE_OTHER              : error_type = "OTHER"; break;
		default                               : error_type = "UNKNOWN TYPE"; break;
	}

	char *error_severity = nullptr;

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_LOW         : error_severity = "LOW"; break;
		case GL_DEBUG_SEVERITY_MEDIUM      : error_severity = "MEDIUM"; break;
		case GL_DEBUG_SEVERITY_HIGH        : error_severity = "HIGH"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: error_severity = "NOTIFICATION"; break;
		default                            : error_severity = "UNKNOWN SEVERITY"; break;
	}

	switch(id)
	{
		case 131185: if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) return; // Buffer detailed info: Buffer object 2 (bound to GL_ARRAY_BUFFER_ARB, usage hint is GL_STATIC_DRAW) will use VIDEO memory as the source for buffer object operations.
	}

	zt_logCritical("opengl error: [%s/%s/%s] %s (%d)", error_source, error_severity, error_type, message, id);
}

// ================================================================================================================================================================================================

ztContextGL *ztgl_win_contextMake(ztMemoryArena *arena, HWND handle, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
	ZT_PROFILE_OPENGL("ztgl_win_contextMake");

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

#	if defined(ZT_OPENGL_DEBUGGING)
	if (wglCreateContextAttribsARB) {
#		define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#		define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#		define WGL_CONTEXT_FLAGS_ARB 0x2094
#		define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#		define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#		define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001
#		define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

		int attrib_list[] = { 
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 5,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0, 0 };

		zt_logInfo("OpenGL: Using 4.5 Core profile");

		HGLRC ncontext = wglCreateContextAttribsARB(hdc, 0, attrib_list);
		ztgl_checkAndReportError("wglCreateContextAttribsARB");

		if (wglMakeCurrent(NULL, NULL) == FALSE) {
			zt_logCritical("OpenGL: wglMakeCurrent(NULL, NULL) failed");
			return false;
		}

		if (wglDeleteContext(context) == FALSE) {
			zt_logCritical("OpenGL: wglDeleteContext failed");
			return false;
		}
		context = ncontext;

		if (wglMakeCurrent(hdc, context) == FALSE) {
			zt_logCritical("OpenGL: wglMakeCurrent failed");
			ztgl_checkAndReportError("wglMakeCurrent");
			return false;
		}
	}

	if (glDebugMessageCallback) {
#		define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
		ztgl_callAndReportOnError(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));

		ztgl_callAndReportOnError(glDebugMessageCallback(_ztgl_debugCallback, nullptr));

		GLuint unused_ids = 0;
		ztgl_callAndReportOnError(glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unused_ids, true));
	}
#	endif

	ztgl_callAndReturnValOnError(glEnable(GL_CULL_FACE), false); // NOTE(josh): should this be here?
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

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

		int pos_x = 0, pos_y = 0, screen_x = 0, screen_y = 0;
		_ztgl_getFullScreenCoords(handle, &pos_x, &pos_y, &screen_x, &screen_y);

		LONG dwExStyle = GetWindowLong(handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(handle, GWL_STYLE);

		dwExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		dwStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

		SetWindowLong(handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(handle, GWL_STYLE, dwStyle);

		SetWindowPos(handle, 0, pos_x, pos_y, screen_x, screen_y, SWP_NOZORDER | SWP_FRAMECHANGED);
	}

	ztContextGL *result = zt_mallocStructArena(ztContextGL, arena);
	result->hdc = hdc;
	result->context = context;
	result->handle = handle;
	result->size.x = client_w;
	result->size.y = client_h;
	result->native_size.x = client_w;
	result->native_size.y = client_h;
	result->pixels_per_unit = pixels_per_unit;
	result->flags = flags;
	result->arena = arena;

	zt_logDebug("OpenGL: setting viewport");
	ztgl_setViewport(result);

	zt_logDebug("OpenGL: version %s", glGetString(GL_VERSION));
	zt_logDebug("OpenGL: vendor %s", glGetString(GL_VENDOR));
	zt_logDebug("OpenGL: renderer %s", glGetString(GL_RENDERER));
	zt_logDebug("OpenGL: shader version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

#	if !defined(ZT_OPENGL_DEBUGGING)
	zt_logDebug("OpenGL: extensions %s", glGetString(GL_EXTENSIONS));
#	endif

	return result;
}

// ================================================================================================================================================================================================

void ztgl_win_contextFree(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_win_contextFree");

	wglMakeCurrent(GetDC(context->handle), NULL);
	wglDeleteContext(context->context);
	ReleaseDC(context->handle, context->hdc);
}

// ================================================================================================================================================================================================

bool ztgl_win_contextSetSize(ztContextGL *context, i32 w, i32 h, i32 nw, i32 nh)
{
	ZT_PROFILE_OPENGL("ztgl_win_contextSetSize");

	context->size.x = w;
	context->size.y = h;
	context->native_size.x = nw;
	context->native_size.y = nh;
	return ztgl_setViewport(context);
}

// ================================================================================================================================================================================================

bool ztgl_win_contextToggleFullscreen(ztContextGL *context, bool fullscreen)
{
	ZT_PROFILE_OPENGL("ztgl_win_contextToggleFullscreen");

	if (fullscreen) {
		GetWindowRect(context->handle, &context->screen_area);

		LONG dwExStyle = GetWindowLong(context->handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(context->handle, GWL_STYLE);

		dwExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		dwStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

		SetWindowLong(context->handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(context->handle, GWL_STYLE, dwStyle);

		int pos_x = 0, pos_y = 0, screen_x = 0, screen_y = 0;
		_ztgl_getFullScreenCoords(context->handle, &pos_x, &pos_y, &screen_x, &screen_y);

		SetWindowPos(context->handle, 0, pos_x, pos_y, screen_x, screen_y, SWP_NOZORDER | SWP_FRAMECHANGED);

		context->flags |= ztRendererFlagsGL_Fullscreen;
	}
	else {
		if(zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen)) {
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
	}

	return ztgl_setViewport(context);
}

// ================================================================================================================================================================================================

bool ztgl_win_contextChangeResolution(ztContextGL *context, i32 w, i32 h)
{
	ZT_PROFILE_OPENGL("ztgl_win_contextChangeResolution");

	RECT client_rect = { 0, 0, w, h };

	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
	int pos_x = (screen_x - (client_rect.right - client_rect.left)) / 2;
	int pos_y = (screen_y - (client_rect.bottom - client_rect.top)) / 2;

	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	if (AdjustWindowRect(&client_rect, style, FALSE) == FALSE) {
		zt_logCritical("opengl: failed to adjust window rect");
		return false;
	}

	context->screen_area.left = pos_x;
	context->screen_area.top = pos_y;
	context->screen_area.right = pos_x + (client_rect.right - client_rect.left);
	context->screen_area.bottom = pos_y + (client_rect.bottom - client_rect.top);

	if (!zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen)) {
		SetWindowPos(context->handle, HWND_TOP, pos_x, pos_y, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, SWP_SHOWWINDOW);
	}

	context->native_size.x = w;
	context->native_size.y = h;

	return ztgl_setViewport(context);
}

// ================================================================================================================================================================================================

bool ztgl_win_setViewport(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_win_setViewport");

	zt_returnValOnNull(context, false);

	struct local
	{
		static bool opengl_calls(int w, int h, r32 realw, r32 realh)
		{
			ztgl_callAndReturnValOnError(glViewport(0, 0, w, h), false); // Sets up clipping
			ztgl_callAndReturnValOnError(glClearColor(0.0f, 0.0f, 0.0f, 0.0f), false);
			ztgl_callAndReturnValOnError(glEnable(GL_BLEND), false);
			ztgl_callAndReturnValOnError(glEnable(GL_MULTISAMPLE), false);
			ztgl_callAndReturnValOnError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);
			return true;
		}
	};

	ztgl_clearErrors(); // make sure previously failed calls don't make the app exit

	r32 realw = (context->native_size.x / (r32)context->pixels_per_unit) / 2.f;
	r32 realh = (context->native_size.y / (r32)context->pixels_per_unit) / 2.f;

	if (zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen)) {
		int pos_x = 0, pos_y = 0, screen_x = 0, screen_y = 0;
		_ztgl_getFullScreenCoords(context->handle, &pos_x, &pos_y, &screen_x, &screen_y);

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

// ================================================================================================================================================================================================

#define ZTGL_FUNC_OP(func)	ztgl_##func##_Func func = nullptr;
ZTGL_FUNCTIONS
#undef ZTGL_FUNC_OP

// end ZT_WINDOWS
#elif defined(ZT_EMSCRIPTEN)

// ================================================================================================================================================================================================

void ztgl_ems_contextDisplay(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_ems_contextDisplay");

	if (SDL_MUSTLOCK(context->sdl_screen)) SDL_UnlockSurface(context->sdl_screen);
	SDL_Flip(context->sdl_screen);
	if (SDL_MUSTLOCK(context->sdl_screen)) SDL_LockSurface(context->sdl_screen);
}

// ================================================================================================================================================================================================

ztContextGL *ztgl_ems_contextMake(ztMemoryArena *arena, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
	ZT_PROFILE_OPENGL("ztgl_ems_contextMake");

	zt_logDebug("OpenGL: initializing SDL");

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	zt_logDebug("OpenGL: creating SDL screen");

	i32 sdl_flags = SDL_OPENGL;

	if (zt_bitIsSet(flags, ztRendererFlagsGL_Fullscreen)) {
		zt_logDebug("OpenGL: Going fullscreen");
		sdl_flags |= SDL_FULLSCREEN;
	}

	SDL_Surface *screen = SDL_SetVideoMode(client_w, client_h, 32, sdl_flags);

	ztgl_callAndReportOnErrorFast(glEnable(GL_CULL_FACE)); // NOTE(josh): should this be here?
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	// this turns off wait for vsync:
	//if (!zt_bitIsSet(flags, ztRendererFlagsGL_Vsync)) {
	//	zt_logDebug("OpenGL: Vsync: true");
	//	ztgl_callAndReturnValOnError(wglSwapIntervalEXT(0), false);
	//}
	//else {
	//	zt_logDebug("OpenGL: Vsync: false");
	//}

	SDL_GL_SetSwapInterval(1);

	ztContextGL *result = zt_mallocStructArena(ztContextGL, arena);
	result->sdl_screen = screen;
	result->size.x = client_w;
	result->size.y = client_h;
	result->native_size.x = client_w;
	result->native_size.y = client_h;
	result->pixels_per_unit = pixels_per_unit;
	result->flags = flags;
	result->arena = arena;

	zt_logDebug("OpenGL: setting viewport");
	ztgl_setViewport(result);

	zt_logDebug("OpenGL: version %s", glGetString(GL_VERSION));
	zt_logDebug("OpenGL: vendor %s", glGetString(GL_VENDOR));
	zt_logDebug("OpenGL: renderer %s", glGetString(GL_RENDERER));
	zt_logDebug("OpenGL: shader version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	zt_logDebug("OpenGL: extensions %s", glGetString(GL_EXTENSIONS));

	return result;
}

// ================================================================================================================================================================================================

void ztgl_ems_contextFree(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_ems_contextFree");

	SDL_Quit();
}

// ================================================================================================================================================================================================

bool ztgl_ems_contextSetSize(ztContextGL *context, i32 w, i32 h, i32 nw, i32 nh)
{
	ZT_PROFILE_OPENGL("ztgl_ems_contextSetSize");

	context->size.x = w;
	context->size.y = h;
	context->native_size.x = nw;
	context->native_size.y = nh;
	return ztgl_setViewport(context);
}

// ================================================================================================================================================================================================

bool ztgl_ems_contextToggleFullscreen(ztContextGL *context, bool fullscreen)
{
//	if (fullscreen) {
//		SDL_SetWindowFullscreen(SDL_WINDOW_FULLSCREEN);
//		context->flags |= ztRendererFlagsGL_Fullscreen;
//	}
//	else {
//		if(zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen)) {
//			SDL_SetWindowFullscreen(0);
//			zt_bitRemove(context->flags, ztRendererFlagsGL_Fullscreen);
//		}
//	}
//
//	return ztgl_setViewport(context);

	return true;
}

// ================================================================================================================================================================================================

bool ztgl_ems_contextChangeResolution(ztContextGL *context, i32 w, i32 h)
{
	return false;
}

// ================================================================================================================================================================================================

bool ztgl_ems_setViewport(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_ems_setViewport");

	zt_returnValOnNull(context, false);

	struct local
	{
		static bool opengl_calls(int w, int h, r32 realw, r32 realh)
		{
			ztgl_callAndReturnValOnError(glViewport(0, 0, w, h), false); // Sets up clipping
			ztgl_callAndReturnValOnError(glClearColor(0.0f, 0.0f, 0.0f, 0.0f), false);
			ztgl_callAndReturnValOnError(glEnable(GL_BLEND), false);
			ztgl_callAndReturnValOnError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);
			return true;
		}
	};

	r32 realw = (context->native_size.x / (r32)context->pixels_per_unit) / 2.f;
	r32 realh = (context->native_size.y / (r32)context->pixels_per_unit) / 2.f;

	if (zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen)) {
		int screen_x = context->native_size.x;
		int screen_y = context->native_size.y;

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

// end ZT_EMSCRIPTEN
#elif defined(ZT_ANDROID)

// ================================================================================================================================================================================================

ztInternal void _ztgl_android_loadFunctions()
{
#	define ZTGL_FUNC_OP(func) if(!func) func = (ztgl_##func##_Func)eglGetProcAddress(#func); if(func == nullptr) zt_logCritical("Unable to load OpenGL function: %s", #func);
	ZTGL_FUNCTIONS;
#	undef ZTGL_FUNC_OP
}

// ================================================================================================================================================================================================

void ztgl_android_contextDisplay(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_android_contextDisplay");
	glFlush();
	ztgl_callAndReturnOnError(eglSwapBuffers(context->egl_display, context->egl_render_surface));
}

// ================================================================================================================================================================================================

ztContextGL *ztgl_android_contextMake(ztMemoryArena *arena, android_app *game_android_app, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
	ZT_PROFILE_OPENGL("ztgl_android_contextMake");

	ztContextGL *result = zt_mallocStructArena(ztContextGL, arena);
	result->egl_display        = EGL_NO_DISPLAY;
	result->egl_render_surface = EGL_NO_SURFACE;
	result->egl_context        = EGL_NO_CONTEXT;
	result->game_android_app   = game_android_app;

	result->egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (!result->egl_display) {
		zt_logCritical("eglGetDisplay failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	if (!eglInitialize(result->egl_display, NULL, NULL)) {
		zt_logCritical("eglInitialize failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	const EGLint RGBX_8888_ATTRIBS[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_NONE
	};
	const EGLint RGB_565_ATTRIBS[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6,
		EGL_RED_SIZE, 5, EGL_DEPTH_SIZE, 8, EGL_NONE
	};

	const EGLint* attribList;

	int windowFormat = ANativeWindow_getFormat(game_android_app->window);
	if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888)) {
		attribList = RGBX_8888_ATTRIBS;
	}
	else {
		attribList = RGB_565_ATTRIBS;
	}

	EGLConfig config;
	EGLint numConfigs;
	if (!eglChooseConfig(result->egl_display, attribList, &config, 1, &numConfigs)) {
		zt_logCritical("eglChooseConfig failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	EGLint format;
	if (!eglGetConfigAttrib(result->egl_display, config, EGL_NATIVE_VISUAL_ID, &format)) {
		zt_logCritical("eglGetConfigAttrib failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	int32 setBufRes = ANativeWindow_setBuffersGeometry(game_android_app->window, 0, 0, format);
	if (setBufRes != 0) {
		zt_logCritical("ANativeWindow_setBuffersGeometry failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	result->egl_context = eglCreateContext(result->egl_display, config, EGL_NO_CONTEXT, contextAttribs);
	if (result->egl_context == EGL_NO_CONTEXT) {
		zt_logCritical("eglCreateContext failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	result->egl_render_surface = eglCreateWindowSurface(result->egl_display, config, game_android_app->window, NULL);
	if (result->egl_render_surface == EGL_NO_SURFACE) {
		zt_logCritical("eglCreateWindowSurface failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	if (!eglMakeCurrent(result->egl_display, result->egl_render_surface, result->egl_render_surface, result->egl_context)) {
		zt_logCritical("eglMakeCurrent failed");
		zt_freeArena(result, arena);
		return nullptr;
	}

	_ztgl_android_loadFunctions();

	zt_logInfo("Android screen: %d x %d", client_w, client_h);

	result->size.x = client_w;
	result->size.y = client_h;
	result->pixels_per_unit = pixels_per_unit;

	ztgl_checkAndReportError("OpenGL Initialization");

	zt_logDebug("OpenGL: version %s", glGetString(GL_VERSION));
	zt_logDebug("OpenGL: vendor %s", glGetString(GL_VENDOR));
	zt_logDebug("OpenGL: renderer %s", glGetString(GL_RENDERER));
	zt_logDebug("OpenGL: shader version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	zt_logDebug("OpenGL: extensions %s", glGetString(GL_EXTENSIONS));

	if (!zt_bitIsSet(flags, ztRendererFlagsGL_Vsync)) {
		zt_logDebug("OpenGL: vsync on");

		eglSwapInterval(result->egl_display, 0);
		ztgl_checkAndReportError("eglSwapInterval");
	}

	zt_logDebug("OpenGL: setting viewport");
	ztgl_setViewport(result);

	return result;
}

// ================================================================================================================================================================================================

void ztgl_android_contextUpdateAfterResume(ztContextGL *context)
{
	zt_logInfo("opengl: resuming application, recreating things as needed");

	const EGLint RGBX_8888_ATTRIBS[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_NONE
	};
	const EGLint RGB_565_ATTRIBS[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6,
		EGL_RED_SIZE, 5, EGL_DEPTH_SIZE, 8, EGL_NONE
	};

	const EGLint* attribList;

	zt_logInfo("opengl: getting format");
	int windowFormat = ANativeWindow_getFormat(context->game_android_app->window);
	if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888)) {
		attribList = RGBX_8888_ATTRIBS;
	}
	else {
		attribList = RGB_565_ATTRIBS;
	}

	EGLConfig config;
	EGLint numConfigs;
	zt_logInfo("opengl: choosing config");
	if (!eglChooseConfig(context->egl_display, attribList, &config, 1, &numConfigs)) {
		zt_logCritical("eglChooseConfig failed");
		return;
	}

	zt_logInfo("opengl: creating window surface");
	context->egl_render_surface = eglCreateWindowSurface(context->egl_display, config, context->game_android_app->window, NULL);
	if (context->egl_render_surface == EGL_NO_SURFACE) {
		zt_logCritical("eglCreateWindowSurface failed");
		return;
	}

	zt_logInfo("opengl: making display current");
	if (!eglMakeCurrent(context->egl_display, context->egl_render_surface, context->egl_render_surface, context->egl_context)) {
		zt_logCritical("eglMakeCurrent failed");
		return;
	}
}

// ================================================================================================================================================================================================

void ztgl_android_contextFree(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_ems_contextFree");

	if (context->egl_display != EGL_NO_DISPLAY) {
		eglMakeCurrent(context->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (context->egl_context != EGL_NO_CONTEXT) {
			eglDestroyContext(context->egl_display, context->egl_context);
		}
		if (context->egl_render_surface != EGL_NO_SURFACE) {
			eglDestroySurface(context->egl_display, context->egl_render_surface);
		}
		eglTerminate(context->egl_display);
	}

	zt_freeArena(context, context->arena);
}

// ================================================================================================================================================================================================

bool ztgl_android_contextSetSize(ztContextGL *context, i32 w, i32 h, i32 nw, i32 nh)
{
	ZT_PROFILE_OPENGL("ztgl_android_contextSetSize");

	context->size.x = w;
	context->size.y = h;
	return ztgl_setViewport(context);
}

// ================================================================================================================================================================================================

bool ztgl_android_contextToggleFullscreen(ztContextGL *context, bool fullscreen)
{
	return true;
}

// ================================================================================================================================================================================================

bool ztgl_android_contextChangeResolution(ztContextGL *context, i32 w, i32 h)
{
	return false;
}

// ================================================================================================================================================================================================

bool ztgl_android_setViewport(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_android_setViewport");

	zt_returnValOnNull(context, false);

	struct local
	{
		static bool opengl_calls(int w, int h, r32 realw, r32 realh)
		{
			ztgl_callAndReturnValOnError(glViewport(0, 0, w, h), false); // Sets up clipping
			ztgl_callAndReturnValOnError(glClearColor(0.0f, 0.0f, 0.0f, 0.0f), false);
			ztgl_callAndReturnValOnError(glEnable(GL_BLEND), false);
			ztgl_callAndReturnValOnError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);
			return true;
		}
	};

	r32 realw = (context->size.x / (r32)context->pixels_per_unit) / 2.f;
	r32 realh = (context->size.y / (r32)context->pixels_per_unit) / 2.f;

	if (!local::opengl_calls(context->size.x, context->size.y, realw, realh)) {
		zt_logCritical("opengl: Calls failed on values: %d, %d, %.2f, %.2f", context->size.x, context->size.y, realw, realh);
		return false;
	}

	return true;
}

// ================================================================================================================================================================================================

bool ztgl_android_contextQueryChangeResolution(ztContextGL *context)
{
	int width = 0;
	int height = 0;

	if (!eglQuerySurface(context->egl_display, context->egl_render_surface, EGL_WIDTH, &width)) {
		zt_logCritical("eglQuerySurface failed");
		return false;
	}

	if (!eglQuerySurface(context->egl_display, context->egl_render_surface, EGL_HEIGHT, &height)) {
		zt_logCritical("eglQuerySurface failed");
		return false;
	}

	if (width != context->size.x || height != context->size.y) {
		context->size.x = width;
		context->size.y = height;
		ztgl_android_setViewport(context);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

#define ZTGL_FUNC_OP(func)	ztgl_##func##_Func func = nullptr;
ZTGL_FUNCTIONS
#undef ZTGL_FUNC_OP

#endif

// ================================================================================================================================================================================================

ztInternal void _ztgl_loadFunctions()
{
	ZT_PROFILE_OPENGL("_ztgl_loadFunctions");

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

// ================================================================================================================================================================================================

ztContextGL *ztgl_contextMake(void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
#if defined(ZT_WINDOWS)
	return ztgl_contextMake(zt_memGetGlobalArena(), (HWND)window, client_w, client_h, pixels_per_unit, flags);

#elif defined(ZT_EMSCRIPTEN) || defined(ZT_ANDROID)
	return ztgl_contextMake(zt_memGetGlobalArena(), nullptr, client_w, client_h, pixels_per_unit, flags);

#else
#error "ztgl_contextMake needs a body for this platform"
#endif
}

// ================================================================================================================================================================================================

ztContextGL *ztgl_contextMake(ztMemoryArena *arena, void *window, i32 client_w, i32 client_h, i32 pixels_per_unit, i32 flags)
{
#if defined(ZT_WINDOWS)
	return ztgl_win_contextMake(arena, (HWND)window, client_w, client_h, pixels_per_unit, flags);

#elif defined(ZT_EMSCRIPTEN)
	return ztgl_ems_contextMake(arena, client_w, client_h, pixels_per_unit, flags);

#elif defined(ZT_ANDROID)
	return ztgl_android_contextMake(arena, (android_app*)window, client_w, client_h, pixels_per_unit, flags);

#else
#endif
}

// ================================================================================================================================================================================================

void ztgl_contextFree(ztContextGL *context)
{
	if(context == nullptr) {
		return;
	}

	zt_winOnly(if(context->context != NULL) ztgl_win_contextFree(context));
	zt_emscriptenOnly(ztgl_ems_contextFree(context));
	zt_androidOnly(ztgl_android_contextFree(context));

	zt_freeArena(context, context->arena);
}

// ================================================================================================================================================================================================

ztVec2i ztgl_contextGetSize(ztContextGL *context)
{
	zt_returnValOnNull(context, zt_vec2i(0,0));
	return context->size;
}

// ================================================================================================================================================================================================

bool ztgl_contextSetSize(ztContextGL *context, i32 w, i32 h, i32 nw, i32 nh)
{
	zt_winOnly(return ztgl_win_contextSetSize(context, w, h, nw, nh));
	zt_emscriptenOnly(return ztgl_ems_contextSetSize(context, w, h, nw, nh));
	zt_androidOnly(return ztgl_android_contextSetSize(context, w, h, nw, nh));
}

// ================================================================================================================================================================================================

void ztgl_contextDisplay(ztContextGL *context)
{
	zt_winOnly(ztgl_win_contextDisplay(context));
	zt_emscriptenOnly(ztgl_ems_contextDisplay(context));
	zt_androidOnly(ztgl_android_contextDisplay(context));
}

// ================================================================================================================================================================================================

bool ztgl_contextIsFullscreen(ztContextGL *context)
{
	zt_returnValOnNull(context, false);
	return zt_bitIsSet(context->flags, ztRendererFlagsGL_Fullscreen);
}

// ================================================================================================================================================================================================

bool ztgl_contextToggleFullscreen(ztContextGL *context, bool fullscreen)
{
	zt_returnValOnNull(context, false);
	zt_winOnly(return ztgl_win_contextToggleFullscreen(context, fullscreen));
	zt_emscriptenOnly(return ztgl_ems_contextToggleFullscreen(context, fullscreen));
	zt_androidOnly(return ztgl_android_contextToggleFullscreen(context, fullscreen));
}

// ================================================================================================================================================================================================

bool ztgl_contextChangeResolution(ztContextGL *context, i32 w, i32 h)
{
	zt_returnValOnNull(context, false);
	zt_winOnly(return ztgl_win_contextChangeResolution(context, w, h));
	zt_emscriptenOnly(return ztgl_ems_contextChangeResolution(context, w, h));
	zt_androidOnly(return ztgl_android_contextChangeResolution(context, w, h));
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void ztgl_clearColor(ztVec4 color)
{
	ZT_PROFILE_OPENGL("ztgl_clearColor");

	ztgl_callAndReportOnErrorFast(glClearColor(color.r, color.g, color.b, color.a));
	ztgl_callAndReportOnErrorFast(glClear(GL_COLOR_BUFFER_BIT));
}

// ================================================================================================================================================================================================

void ztgl_clearColor(r32 r, r32 g, r32 b, r32 a)
{
	ZT_PROFILE_OPENGL("ztgl_clearColor");

	ztgl_callAndReportOnErrorFast(glClearColor(r, g, b, a));
	ztgl_callAndReportOnErrorFast(glClear(GL_COLOR_BUFFER_BIT));
}

// ================================================================================================================================================================================================

void ztgl_clearDepth()
{
	ZT_PROFILE_OPENGL("ztgl_clearDepth");

#if !defined(ZT_GLES2)
	ztgl_callAndReportOnErrorFast(glClear(GL_DEPTH_BUFFER_BIT));
#endif
}

// ================================================================================================================================================================================================

void ztgl_clear(ztVec4 color)
{
	ZT_PROFILE_OPENGL("ztgl_clear");

	ztgl_callAndReportOnErrorFast(glClearColor(color.r, color.g, color.b, color.a));
	ztgl_callAndReportOnErrorFast(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}

// ================================================================================================================================================================================================

void ztgl_clear(r32 r, r32 g, r32 b, r32 a)
{
	ZT_PROFILE_OPENGL("ztgl_clear");

	ztgl_callAndReportOnErrorFast(glClearColor(r, g, b, a));
	ztgl_callAndReportOnErrorFast(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}

// ================================================================================================================================================================================================

bool ztgl_setViewport(i32 width, i32 height)
{
	ZT_PROFILE_OPENGL("ztgl_setViewport(w,h)");

	ztgl_callAndReturnValOnError(glViewport(0, 0, width, height), false);
	return true;
}

// ================================================================================================================================================================================================

bool ztgl_setViewport(ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_setViewport");

	zt_winOnly(return ztgl_win_setViewport(context));
	zt_emscriptenOnly(return ztgl_ems_setViewport(context));
	zt_androidOnly(return ztgl_android_setViewport(context));
}

// ================================================================================================================================================================================================

bool ztgl_clipViewport(i32 x, i32 y, i32 w, i32 h)
{
	ZT_PROFILE_OPENGL("ztgl_setViewport");

	ztgl_callAndReportOnErrorFast(glEnable(GL_SCISSOR_TEST));
	ztgl_callAndReportOnErrorFast(glScissor(x, y, w, h));

	return true;
}

// ================================================================================================================================================================================================

bool ztgl_clipReset()
{
	ZT_PROFILE_OPENGL("ztgl_clipReset");

	ztgl_callAndReportOnErrorFast(glDisable(GL_SCISSOR_TEST));

	return true;
}

// ================================================================================================================================================================================================

void ztgl_cullFront()
{
	ZT_PROFILE_OPENGL("ztgl_cullFront");

	ztgl_callAndReportOnErrorFast(glEnable(GL_CULL_FACE));
	ztgl_callAndReportOnErrorFast(glCullFace(GL_FRONT));
}

// ================================================================================================================================================================================================

void ztgl_cullBack()
{
	ZT_PROFILE_OPENGL("ztgl_cullBack");

	ztgl_callAndReportOnErrorFast(glEnable(GL_CULL_FACE));
	ztgl_callAndReportOnErrorFast(glCullFace(GL_BACK));
}

// ================================================================================================================================================================================================

void ztgl_cullNone()
{
	ZT_PROFILE_OPENGL("ztgl_cullNone");

	ztgl_callAndReportOnErrorFast(glDisable(GL_CULL_FACE));
}

// ================================================================================================================================================================================================

void ztgl_depthTestOff()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestOff");
#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glDisable(GL_DEPTH_TEST));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestNever()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestNever");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_NEVER));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestLess()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestLess");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_LESS));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestLessEqual()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestLessEqual");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_LEQUAL));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestEqual()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestEqual");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_EQUAL));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestGreater()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestGreater");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_GREATER));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestNotEqual()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestNotEqual");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_NOTEQUAL));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestGreaterEqual()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestGreaterEqual");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_GEQUAL));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_depthTestAlways()
{
	ZT_PROFILE_OPENGL("ztgl_depthTestAlways");

#	if !defined(ZT_GLES2) || defined(ZT_EMSCRIPTEN)
	ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
	ztgl_callAndReportOnErrorFast(glDepthFunc(GL_ALWAYS));
#	endif
}

// ================================================================================================================================================================================================

void ztgl_blendMode(ztGLBlendMode_Enum source, ztGLBlendMode_Enum dest)
{
	ZT_PROFILE_OPENGL("ztgl_blendMode");

	GLenum factors[2] = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
	ztGLBlendMode_Enum params[2] = { source, dest };

	zt_fize(params) {
		switch(params[i])
		{
			case ztGLBlendMode_Zero                : factors[i] = GL_ZERO; break;
			case ztGLBlendMode_One                 : factors[i] = GL_ONE; break;
			case ztGLBlendMode_SourceColor         : factors[i] = GL_SRC_COLOR; break;
			case ztGLBlendMode_OneMinusSourceColor : factors[i] = GL_ONE_MINUS_SRC_COLOR; break;
			case ztGLBlendMode_DestColor           : factors[i] = GL_DST_COLOR; break;
			case ztGLBlendMode_OneMinusDestColor   : factors[i] = GL_ONE_MINUS_DST_COLOR; break;
			case ztGLBlendMode_SourceAlpha         : factors[i] = GL_SRC_ALPHA; break;
			case ztGLBlendMode_OneMinusSourceAlpha : factors[i] = GL_ONE_MINUS_SRC_ALPHA; break;
			case ztGLBlendMode_DestAlpha           : factors[i] = GL_DST_ALPHA; break;
			case ztGLBlendMode_OneMinusDestAlpha   : factors[i] = GL_ONE_MINUS_DST_ALPHA; break;
		}
	}

	ztgl_callAndReportOnErrorFast(glEnable(GL_BLEND));
	ztgl_callAndReportOnErrorFast(glBlendFunc(factors[0], factors[1]));
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool ztgl_checkAndReportError(const char *function, int line)
{
	ZT_PROFILE_OPENGL("ztgl_checkAndReportError");

#	if defined(ZT_OPENGL_DEBUGGING_LOGALL)
	//zt_logDebug("Checking for errors after call to %s", function);
#	endif
	int errors = 0;

#	if defined(ZT_ANDROID)
	for(GLint error = eglGetError(); error != EGL_SUCCESS && errors < 10; error = eglGetError()) {
		zt_logCritical("OpenGLES: error from function %s: 0x%08x (%d, %d)", function, error, error, line);
		errors += 1;
	}
#	endif

	for (GLint error = glGetError(); error != 0 && errors < 10; error = glGetError()) {
		zt_logCritical("OpenGL: error from function %s: 0x%08x (%d, %d)", function, error, error, line);
		errors += 1;
	}

	return errors > 0;
}

// ================================================================================================================================================================================================

int ztgl_clearErrors()
{
	ZT_PROFILE_OPENGL("ztgl_clearErrors");

	int errors = 0;
	for (GLint error = glGetError(); error != 0 && errors < 10; error = glGetError())
		++errors;

	return errors;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztShaderGL *ztgl_shaderMake(ztContextGL *context, const char *vert_src, const char *frag_src, const char *geom_src)
{
	return ztgl_shaderMake(context, zt_memGetGlobalArena(), vert_src, frag_src, geom_src);
}

// ================================================================================================================================================================================================

ztShaderGL *ztgl_shaderMake(ztContextGL *context, ztMemoryArena *arena, const char *vert_src, const char *frag_src, const char *geom_src)
{
	ZT_PROFILE_OPENGL("ztgl_shaderMake");

	struct local
	{
		static GLuint load_shader(GLenum type, const char *src)
		{
			GLuint shader = glCreateShader(type);
			ztgl_checkAndReportError("glCreateShader");

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

		static GLuint load_program(GLuint vert, GLuint frag, GLuint geom, const char *vert_src, const char *frag_src, const char *geom_src)
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

				int attrib_pos = zt_strFindPos(vert_src, "attribute ", 0);
				int attrib_idx = 0;
				while (attrib_pos != ztStrPosNotFound) {
					// we need to parse out the attributes and tell opengl which locations to bind them to
					int attrib_end = zt_strFindPos(vert_src, ";", attrib_pos);
					int attrib_beg = zt_strFindLastPos(vert_src, " ", attrib_end);

					if (attrib_end != ztStrPosNotFound && attrib_beg != ztStrPosNotFound) {
						attrib_beg += 1; // remove space
						char attrib_name[128];
						zt_strCpy(attrib_name, zt_elementsOf(attrib_name), vert_src + attrib_beg, attrib_end - attrib_beg);

						ztgl_callAndReturnValOnError(glBindAttribLocation(program, attrib_idx++, attrib_name), 0);

						attrib_pos = zt_strFindPos(vert_src, "attribute ", attrib_end + 1);
					}
					else break;
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
	if (vert == 0) { zt_logCritical("OpenGL: Unable to compile vertex shader."); return nullptr; }

	GLuint frag = local::load_shader(GL_FRAGMENT_SHADER, frag_src);
	if (frag == 0) { zt_logCritical("OpenGL: Unable to compile fragment shader."); return nullptr; }

	GLuint geom = geom_src ? local::load_shader(GL_GEOMETRY_SHADER, geom_src) : 0;
	if (geom_src && geom == 0) { zt_logCritical("OpenGL: Unable to compile geometry shader."); return nullptr; }

	GLuint program = local::load_program(vert, frag, geom, vert_src, frag_src, geom_src);
	if (program == 0) { zt_logCritical("OpenGL: Unable to compile and link shader program."); return nullptr; }

	ztShaderGL *shader = zt_mallocStructArena(ztShaderGL, arena);
	shader->program_id = program;
	shader->vert_id = vert;
	shader->frag_id = frag;
	shader->geom_id = geom;
	shader->textures_bound = 0;
	shader->in_use = false;
	shader->arena = arena;
	shader->context = context;

	// extract shader variables
	int uniform_count = 0;
	ztgl_callAndReportOnErrorFast(glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniform_count));

	int actual_count = 0;
	zt_fiz(uniform_count) {
		int len = 0, size = 0;
		GLenum type = 0;
		char varname[256] = { 0 };
		ztgl_callAndReportOnErrorFast(glGetActiveUniform(program, i, zt_elementsOf(varname), &len, &size, &type, varname));

		actual_count += size;
	}

	shader->uniforms_count = actual_count;
	shader->uniforms = actual_count ? zt_mallocStructArrayArena(ztShaderGL::Uniform, actual_count, arena) : nullptr;

	int act_idx = 0;
	zt_fiz(uniform_count) {
		int len = 0, size = 0;
		GLenum type = 0;
		char varname[256] = { 0 };
		ztgl_callAndReportOnErrorFast(glGetActiveUniform(program, i, zt_elementsOf(varname), &len, &size, &type, varname));
		varname[len] = 0;

		if (size > 1) { // variable array is named like "variable[0]"
			int pos_open = zt_strFindPos(varname, "[", 0);
			char subname[256];
			zt_strCpy(subname, zt_elementsOf(subname), varname, pos_open == ztStrPosNotFound ? zt_strLen(varname) : pos_open);

			zt_fjz(size) {
				zt_strMakePrintf(name, 256, "%s[%d]", subname, j);

				shader->uniforms[act_idx].name = zt_stringMakeFrom(name, arena);
				shader->uniforms[act_idx].type = type;
				shader->uniforms[act_idx].location = glGetUniformLocation(program, name);
				shader->uniforms[act_idx].name_hash = zt_strHash(shader->uniforms[act_idx].name);

				act_idx += 1;
			}
		}
		else {
			shader->uniforms[act_idx].name = zt_stringMakeFrom(varname, arena);
			shader->uniforms[act_idx].type = type;
			shader->uniforms[act_idx].location = glGetUniformLocation(program, varname);
			shader->uniforms[act_idx].name_hash = zt_strHash(shader->uniforms[act_idx].name);

			act_idx += 1;
		}
	}

#	if 1
	int attrib_count = 0;
	ztgl_callAndReportOnErrorFast(glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &attrib_count));

	shader->inputs_count = attrib_count;
	shader->inputs = attrib_count ? zt_mallocStructArrayArena(ztShaderGL::Inputs, attrib_count, arena) : nullptr;

	zt_fiz(attrib_count) {
		int len = 0, size = 0;
		GLenum type = 0;
		char varname[256] = { 0 };
		ztgl_callAndReportOnErrorFast(glGetActiveAttrib(program, i, zt_elementsOf(varname), &len, &size, &type, varname));
		varname[len] = 0;

		shader->inputs[i].name      = zt_stringMakeFrom(varname, arena);
		shader->inputs[i].name_hash = zt_strHash(shader->inputs[i].name);
		shader->inputs[i].type      = type;
		shader->inputs[i].location  = glGetAttribLocation(program, varname);
	}
#	endif

#	if 1
#	define GL_LOCATION 0x930E
#	define GL_PROGRAM_OUTPUT 0x92E4
#	define GL_ARRAY_SIZE 0x92FB
#	define GL_REFERENCED_BY_FRAGMENT_SHADER 0x930A
#define GL_LOCATION_INDEX 0x930F
#define GL_LOCATION_COMPONENT 0x934A
#define GL_TYPE 0x92FA

	int locations_count = 0;

	zt_fiz(16) {
		GLenum inputs[] = { GL_LOCATION };
		GLint outputs[64];
		int outputs_count = 0;
		glGetProgramResourceiv(program, GL_PROGRAM_OUTPUT, i, zt_elementsOf(inputs), inputs, zt_elementsOf(outputs), &outputs_count, outputs);
		for (GLint error = glGetError(); error != 0; error = glGetError()) {}
		if (outputs_count <= 0) break;

		locations_count += 1;
	}

	shader->outputs_count = locations_count;
	shader->outputs = locations_count ? zt_mallocStructArrayArena(ztShaderGL::Outputs, locations_count, arena) : nullptr;

	zt_fiz(locations_count) {
		GLenum inputs[] = { GL_LOCATION };
		GLint outputs[64];
		int outputs_count = 0;

		glGetProgramResourceiv(program, GL_PROGRAM_OUTPUT, i, zt_elementsOf(inputs), inputs, zt_elementsOf(outputs), &outputs_count, outputs);
		shader->outputs[i].location = outputs[0];

		inputs[0] = GL_TYPE;
		glGetProgramResourceiv(program, GL_PROGRAM_OUTPUT, i, zt_elementsOf(inputs), inputs, zt_elementsOf(outputs), &outputs_count, outputs);
		shader->outputs[i].type = outputs[0];

		char varname[256] = { 0 };
		int len = 0;
		glGetProgramResourceName(program, GL_PROGRAM_OUTPUT, i, zt_elementsOf(varname), &len, varname);

		shader->outputs[i].name = zt_stringMakeFrom(varname, arena);
		shader->outputs[i].name_hash = zt_strHash(shader->outputs[i].name);
	}
#	endif

	return shader;
}

// ================================================================================================================================================================================================

void ztgl_shaderFree(ztShaderGL *shader)
{
	ZT_PROFILE_OPENGL("ztgl_shaderFree");

	if (shader == nullptr) {
		return;
	}

	zt_fiz(shader->uniforms_count) {
		zt_stringFree(shader->uniforms[i].name, shader->arena);
	}
	zt_freeArena(shader->uniforms, shader->arena);

	zt_fiz(shader->inputs_count) {
		zt_stringFree(shader->inputs[i].name, shader->arena);
	}
	zt_freeArena(shader->inputs, shader->arena);

	zt_fiz(shader->outputs_count) {
		zt_stringFree(shader->outputs[i].name, shader->arena);
	}
	zt_freeArena(shader->outputs, shader->arena);

	GLuint ids[3] = { shader->vert_id, shader->frag_id, shader->geom_id };

	zt_fiz(zt_elementsOf(ids)) {
		if (ids[i]) {
			ztgl_callAndReportOnError(glDetachShader(shader->program_id, ids[i]));
			ztgl_callAndReportOnError(glDeleteShader(ids[i]));
		}
	}

	ztgl_callAndReportOnError(glDeleteProgram(shader->program_id));

	zt_freeArena(shader, shader->arena);
}

// ================================================================================================================================================================================================

void ztgl_shaderBegin(ztShaderGL *shader)
{
	ZT_PROFILE_OPENGL("ztgl_shaderBegin");

	zt_returnOnNull(shader);
	ztgl_callAndReportOnErrorFast(glUseProgram(shader->program_id));
	ztgl_textureBindReset(shader);

	if (shader->context && shader->context->active_render_target) {
		zt_fize(shader->context->active_render_target->attachments) {
			ztgl_textureRenderTargetAttachmentEnable(shader->context->active_render_target, i, (shader->outputs_count - 1) > i);
		}
	}

	shader->in_use = true;
}

// ================================================================================================================================================================================================

void ztgl_shaderEnd(ztShaderGL *shader)
{
	ZT_PROFILE_OPENGL("ztgl_shaderEnd");

	zt_returnOnNull(shader);
	ztgl_textureBindReset(shader);
	ztgl_callAndReportOnErrorFast(glUseProgram(0));
	shader->textures_bound = 0;
	shader->in_use = false;
}

// ================================================================================================================================================================================================

bool ztgl_shaderHasVariable(ztShaderGL *shader, u32 name_hash)
{
	ZT_PROFILE_OPENGL("ztgl_shaderHasVariable");

	zt_returnValOnNull(shader, false);
	zt_fiz(shader->uniforms_count) {
		if (shader->uniforms[i].name_hash == name_hash) {
			return true;
		}
	}

	return false;
}

// ================================================================================================================================================================================================

ztInternal ztInline GLint _ztgl_shaderGetUniformLocation(ztShaderGL *shader, u32 name_hash)
{
	ZT_PROFILE_OPENGL("_ztgl_shaderGetUniformLocation");

	zt_returnValOnNull(shader, -1);
	zt_fiz(shader->uniforms_count) {
		if (shader->uniforms[i].name_hash == name_hash) {
			return shader->uniforms[i].location;
			break;
		}
	}
	return -1;
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableFloat(ztShaderGL *shader, u32 name_hash, r32 value)
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableFloat");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform1fv(location, 1, &value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableInt(ztShaderGL *shader, u32 name_hash, i32 value)
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableInt");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform1i(location, value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableVec2(ztShaderGL *shader, u32 name_hash, r32 value[2])
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableVec2");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform2fv(location, 1, value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableVec3(ztShaderGL *shader, u32 name_hash, r32 value[3])
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableVec3");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform3fv(location, 1, value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableVec4(ztShaderGL *shader, u32 name_hash, r32 value[4])
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableVec4");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform4fv(location, 1, value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableMat4(ztShaderGL *shader, u32 name_hash, r32 value[16])
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableMat4");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniformMatrix4fv(location, 1, GL_FALSE, value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableMat3(ztShaderGL *shader, u32 name_hash, r32 value[12])
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableMat3");
	zt_assertReturnOnFail(shader->in_use);

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniformMatrix3fv(location, 1, GL_FALSE, value));
}

// ================================================================================================================================================================================================

void ztgl_shaderVariableTex(ztShaderGL *shader, u32 name_hash, ztTextureGL *tex)
{
	ZT_PROFILE_OPENGL("ztgl_shaderVariableTex");
	zt_assertReturnOnFail(shader->in_use);

	if (tex == nullptr) {
		return;
	}

	GLint location = _ztgl_shaderGetUniformLocation(shader, name_hash);
	if (location != -1) ztgl_callAndReportOnErrorFast(glUniform1i(location, shader->textures_bound));
	ztgl_textureBind(tex, shader->textures_bound++);
}

// ================================================================================================================================================================================================

ztShaderGL *ztgl_shaderMakePointLightShadows(ztContextGL *context)
{
	char *vert =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"\n"
		"uniform mat4 model;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = model * vec4(position, 1.0);\n"
		"}\n";

	char *geom =
		"#version 330 core\n"
		"layout (triangles) in;\n"
		"layout (triangle_strip, max_vertices=18) out;\n"
		"\n"
		"out vec4 frag_pos;\n"
		"\n"
		"uniform mat4 shadow_matrices[6];\n"
		"\n"
		"void main()\n"
		"{\n"
		"	for (int face = 0; face < 6; ++face) {\n"
		"		gl_Layer = face;\n"
		"		for (int i = 0; i < 3; ++i) {\n"
		"			frag_pos = gl_in[i].gl_Position;\n"
		"			gl_Position = shadow_matrices[face] * frag_pos;\n"
		"			EmitVertex();\n"
		"		}    \n"
		"		EndPrimitive();\n"
		"	}\n"
		"} \n";

	char *frag =
		"#version 330 core\n"
		"in vec4 frag_pos;\n"
		"\n"
		"uniform vec3 light_pos;\n"
		"uniform float far_plane;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	float light_distance = length(frag_pos.xyz - light_pos);\n"
		"\n"
		"	// map to [0;1] range by dividing by far_plane\n"
		"	light_distance = light_distance / far_plane;\n"
		"\n"
		"	// write this as modified depth\n"
		"	gl_FragDepth = light_distance;\n"
		"}\n";

	return ztgl_shaderMake(context, vert, frag, geom);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


ztInternal ztTextureGL *_ztgl_textureMakeBase(ztContextGL *context, ztMemoryArena *arena, byte *pixel_data, i32 width, i32 height, i32 depth, i32 flags)
{
	ZT_PROFILE_OPENGL("_ztgl_textureMakeBase");

	if (pixel_data && zt_bitIsSet(flags, ztTextureGLFlags_FlipOnLoad)) {
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

	bool render_target = pixel_data == nullptr;

	struct OpenGL
	{
		static bool loadTexture(GLuint *tex_id, byte *pixel_data, i32 width, i32 height, i32 depth, i32 flags)
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
			if (zt_bitIsSet(flags, ztTextureGLFlags_Repeat)) {
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);
			}
			else {
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
			}

			if (!zt_bitIsSet(flags, ztTextureGLFlags_HDR)) {
				zt_assertReturnValOnFail(depth == 4 || depth == 3, false);
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, depth == 4 ? GL_RGBA : GL_RGB, width, height, 0, depth == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pixel_data), false);
			}
			else {
				zt_assertReturnValOnFail(depth == 3, false);
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, pixel_data), false);
			}

			if (zt_bitIsSet(flags, ztTextureGLFlags_MipMaps)) {
				if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST), false);
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
				}
				else {
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR), false);
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
				}
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 7), false);
				ztgl_callAndReturnValOnError(glGenerateMipmap(GL_TEXTURE_2D), false);
			}
			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), false);

			return true;
		}

		static bool makeRenderTarget(GLuint *tex_id, GLuint *frame_buffer_id, GLuint *depth_buffer_id, GLuint *resolve_buffer_id, GLuint *render_target_id, i32 width, i32 height, i32 depth, i32 flags, i32 *width_actual, i32 *height_actual)
		{
#			if defined(ZT_GLES)
			if (!zt_isPow2(width)) width = zt_nextPow2(width);
			if (!zt_isPow2(height)) height = zt_nextPow2(height);
			zt_logDebug("opengl: render target dimensions: %d x %d", width, height);
#			endif
			ztgl_callAndReturnValOnError(glGenFramebuffers(1, frame_buffer_id), false);

#			if defined(ZT_GLES2)
			zt_bitRemove(flags, ztTextureGLFlags_DepthMap);
#			endif

			if (zt_bitIsSet(flags, ztTextureGLFlags_DepthMap)) {
				ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
				//ztgl_callAndReturnValOnError(glActiveTexture(GL_TEXTURE0), false);
				ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);
#				if !defined(ZT_GLES2)
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL), false);
#				else
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL), false);
#				endif

				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);

				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
				ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);
#				if !defined(ZT_GLES)
//				GLfloat border_color[] = { 1.f, 1.f, 1.f, 1.f };
//				ztgl_callAndReturnValOnError(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color), false);
#				endif

				ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);
				ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *tex_id, 0), false);
#				if !defined(ZT_GLES)
				ztgl_callAndReturnValOnError(glDrawBuffer(GL_NONE), false);
				ztgl_callAndReturnValOnError(glReadBuffer(GL_NONE), false);
#				endif
			}
			else {
#				if defined(ZT_GLES)
				ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);

				*depth_buffer_id = 0;
				*render_target_id = 0;
				*resolve_buffer_id = 0;

				ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
				ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);
				if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
				}
				else {
					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
				}
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr), false);
				ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *tex_id, 0), false);
				ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), false);

#				else
				if(zt_bitIsSet(flags, ztTextureGLFlags_Multisample)) {
					ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);

					ztgl_callAndReturnValOnError(glGenRenderbuffers(1, depth_buffer_id), false);
					ztgl_callAndReturnValOnError(glBindRenderbuffer(GL_RENDERBUFFER, *depth_buffer_id), false);
					ztgl_callAndReturnValOnError(glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, width, height), false);
					ztgl_callAndReturnValOnError(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depth_buffer_id), false);

					ztgl_callAndReturnValOnError(glGenTextures(1, render_target_id), false);
					if (zt_bitIsSet(flags, ztTextureGLFlags_HDR)) {
						ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, *render_target_id), false);

						if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
						}
						else {
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
						}

						if (zt_bitIsSet(flags, ztTextureGLFlags_Repeat)) {
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);
						}
						else {
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
							ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
						}
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0), false);
						//ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr), false);
						ztgl_callAndReturnValOnError(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16F, width, height, GL_TRUE), false);
						ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0), false);
						ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, *render_target_id, 0), false);
					}
					else {
						ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, *render_target_id), false);
						ztgl_callAndReturnValOnError(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, width, height, GL_TRUE), false);

						ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0), false);
						ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, *render_target_id, 0), false);
					}

					if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
						zt_logCritical("OpenGL frame buffer status is not complete [1] (status: 0x%x)", glCheckFramebufferStatus(GL_FRAMEBUFFER));
						return false;
					}

					//

					ztgl_callAndReturnValOnError(glGenFramebuffers(1, resolve_buffer_id), false);
					ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *resolve_buffer_id), false);

					ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
					ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);
					if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
					}
					else {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
					}

					if (zt_bitIsSet(flags, ztTextureGLFlags_Repeat)) {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);
					}
					else {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
					}

					ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0), false);
					if (zt_bitIsSet(flags, ztTextureGLFlags_HDR)) {
						ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr), false);
					}
					else {
						ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr), false);
					}
					ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *tex_id, 0), false);
					ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), false);
				}
				else {
					ztgl_callAndReturnValOnError(glGenFramebuffers(1, frame_buffer_id), false);
					ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);

					ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
					//ztgl_callAndReturnValOnError(glActiveTexture(GL_TEXTURE0), false);
					ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, *tex_id), false);

					if (zt_bitIsSet(flags, ztTextureGLFlags_HDR)) {
						ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr), false);
					}
					else {
						ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr), false);
					}

					if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
					}
					else {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
					}
					
					if (zt_bitIsSet(flags, ztTextureGLFlags_Repeat)) {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);
					}
					else {
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
						ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
					}

					ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), false);
					ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *tex_id, 0), false);

					ztgl_callAndReturnValOnError(glGenRenderbuffers(1, depth_buffer_id), false);
					ztgl_callAndReturnValOnError(glBindRenderbuffer(GL_RENDERBUFFER, *depth_buffer_id), false);
					ztgl_callAndReturnValOnError(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height), false);
					ztgl_callAndReturnValOnError(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depth_buffer_id), false);
				}
#endif
			}

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				zt_logCritical("OpenGL frame buffer status is not complete [2] (status: 0x%x)", glCheckFramebufferStatus(GL_FRAMEBUFFER));
				return false;
			}

			ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, 0), false);
			ztgl_callAndReturnValOnError(glClear(GL_COLOR_BUFFER_BIT), false);

			*width_actual = width;
			*height_actual = height;

			return true;
		}
	};

	GLuint tex_id = 0, fb_id = 0, db_id = 0, rb_id = 0, rt_id = 0;

	i32 actual_width = width;
	i32 actual_height = height;

	if (!render_target) {
		if (!OpenGL::loadTexture(&tex_id, pixel_data, width, height, depth, flags)) {
			zt_logCritical("Unable to load image into texture");
			return nullptr;
		}
	}
	else {
		if (!OpenGL::makeRenderTarget(&tex_id, &fb_id, &db_id, &rb_id, &rt_id, width, height, depth, flags, &actual_width, &actual_height)) {
			zt_logCritical("Unable to create render target");
			return nullptr;
		}
	}

	ztTextureGL *texture = zt_mallocStructArena(ztTextureGL, arena);

	texture->texid             = tex_id;
	texture->fbo               = fb_id;
	texture->dbo               = db_id;
	texture->rt                = rt_id;
	texture->rb                = rb_id;
	texture->w                 = width;
	texture->h                 = height;
	texture->wa                = actual_width;
	texture->ha                = actual_height;
	texture->d                 = depth;
	texture->attachments_count = 0;
	texture->flags             = flags;
	texture->arena             = arena;
	texture->context           = context;

	zt_logDebug("opengl: made texture (id: %d; fbo: %d; dim: %d x %d)", tex_id, fb_id, width, height);

	return texture;
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeFromPixelData(ztContextGL *context, byte *pixels, int w, int h, int d, i32 flags)
{
	return ztgl_textureMakeFromPixelData(context, zt_memGetGlobalArena(), pixels, w, h, d, flags);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeFromPixelData(ztContextGL *context, ztMemoryArena *arena, byte *pixels, int w, int h, int d, i32 flags)
{
	ZT_PROFILE_OPENGL("ztgl_textureMakeFromPixelData");

	return _ztgl_textureMakeBase(context, arena, pixels, w, h, d, flags);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeCubeMapFromPixelData(ztContextGL *context, byte **pixels, int w, int h, int d)
{
	return ztgl_textureMakeCubeMapFromPixelData(context, zt_memGetGlobalArena(), pixels, w, h, d);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeCubeMapFromPixelData(ztContextGL *context, ztMemoryArena *arena, byte **pixels, int w, int h, int d)
{
	ZT_PROFILE_OPENGL("ztgl_textureMakeCubeMapFromPixelData");

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

	texture->texid             = texid;
	texture->fbo               = 0;
	texture->dbo               = 0;
	texture->rt                = 0;
	texture->rb                = 0;
	texture->w                 = w;
	texture->h                 = h;
	texture->wa                = w;
	texture->ha                = h;
	texture->d                 = 4;
	texture->attachments_count = 0;
	texture->flags             = ztTextureGLFlags_CubeMap;
	texture->arena             = arena;
	texture->context           = context;

	return texture;
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeCubeMapFromRender(ztContextGL *context, int w, int h, int mip_map_levels, ztTextureGLRender_Func *render_func, void *user_data)
{
	ZT_PROFILE_OPENGL("ztgl_textureMakeCubeMapFromRender");

	struct local
	{
		static bool load(GLuint *frame_buffer_id, GLuint *depth_buffer_id, GLuint *tex_id, int w, int h, int mip_map_levels, ztTextureGLRender_Func *render_func, void *user_data)
		{
			ztgl_callAndReturnValOnError(glGenFramebuffers(1, frame_buffer_id), false);
			ztgl_callAndReturnValOnError(glGenRenderbuffers(1, depth_buffer_id), false);

			ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);
			ztgl_callAndReturnValOnError(glBindRenderbuffer(GL_RENDERBUFFER, *depth_buffer_id), false);
			ztgl_callAndReturnValOnError(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depth_buffer_id), false);

			ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_CUBE_MAP, *tex_id), false);

			zt_fiz(6) {
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, nullptr), false);
			}

			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mip_map_levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);

			if (mip_map_levels > 1) {
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			}

			for (int mip = 0; mip < mip_map_levels; ++mip) {
				ztgl_callAndReturnValOnError(glBindRenderbuffer(GL_RENDERBUFFER, *depth_buffer_id), false);

				int mip_w = w, mip_h = h;
				if (mip_map_levels > 1) {
					mip_w = mip_h = zt_convertToi32Floor(128 * zt_pow(0.5, (r32)mip));
				}

				ztgl_callAndReturnValOnError(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mip_w, mip_h), false);

				ztMat4 capture_proj = ztMat4::makePerspectiveProjection(zt_degreesToRadians(90), 1.f, 1.f, .1f, 100.f);
				ztMat4 capture_views[] =
				{
					ztMat4::identity.getLookAt(ztVec3::zero, zt_vec3( 1.0f,  0.0f,  0.0f), zt_vec3(0, -1,  0)), //zt_vec3(0.0f, -1.0f,  0.0f)),
					ztMat4::identity.getLookAt(ztVec3::zero, zt_vec3(-1.0f,  0.0f,  0.0f), zt_vec3(0, -1,  0)), //zt_vec3(0.0f, -1.0f,  0.0f)),
					ztMat4::identity.getLookAt(ztVec3::zero, zt_vec3( 0.0f,  1.0f,  0.0f), zt_vec3(0,  0,  1)), //zt_vec3(0.0f,  0.0f,  1.0f)),
					ztMat4::identity.getLookAt(ztVec3::zero, zt_vec3( 0.0f, -1.0f,  0.0f), zt_vec3(0,  0, -1)), //zt_vec3(0.0f,  0.0f, -1.0f)),
					ztMat4::identity.getLookAt(ztVec3::zero, zt_vec3( 0.0f,  0.0f,  1.0f), zt_vec3(0, -1,  0)), //zt_vec3(0.0f, -1.0f,  0.0f)),
					ztMat4::identity.getLookAt(ztVec3::zero, zt_vec3( 0.0f,  0.0f, -1.0f), zt_vec3(0, -1,  0)), //zt_vec3(0.0f, -1.0f,  0.0f)),
				};

				ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);
				zt_fiz(6) {
					ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, *tex_id, mip), false);
					ztgl_callAndReturnValOnError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), false);

					render_func(i, mip, mip_w, mip_h, &capture_proj, &capture_views[i], user_data);
				}
			}
			ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, 0), false);
			return true;
		}
	};

	GLuint frame_buffer_id, depth_buffer_id, tex_id;
	if(!local::load(&frame_buffer_id, &depth_buffer_id, &tex_id, w, h, mip_map_levels, render_func, user_data)) {
		return nullptr;
	}

	ztMemoryArena *arena = zt_memGetGlobalArena();

	ztTextureGL *texture = zt_mallocStructArena(ztTextureGL, arena);

	texture->texid             = tex_id;
	texture->fbo               = frame_buffer_id;
	texture->dbo               = depth_buffer_id;
	texture->rt                = 0;
	texture->rb                = 0;
	texture->w                 = w;
	texture->h                 = h;
	texture->wa                = w;
	texture->ha                = h;
	texture->d                 = 3;
	texture->attachments_count = 0;
	texture->flags             = ztTextureGLFlags_CubeMap;
	texture->arena             = arena;
	texture->context           = context;

	return texture;
}

// ================================================================================================================================================================================================

ztInternal ztTextureGL *_ztgl_textureMakeCubeMapFromOther(ztContextGL *context, ztTextureGL *hdr_texture, ztTextureGL *cube_map_irradiance, ztTextureGL *cube_map_prefilter, int w, int h)
{
	float vertices[] = {
		-1.0f,  1.0f, -1.0f,       -1.0f, -1.0f, -1.0f,        1.0f, -1.0f, -1.0f,        1.0f, -1.0f, -1.0f,        1.0f,  1.0f, -1.0f,       -1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,       -1.0f, -1.0f, -1.0f,       -1.0f,  1.0f, -1.0f,       -1.0f,  1.0f, -1.0f,       -1.0f,  1.0f,  1.0f,       -1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,        1.0f, -1.0f,  1.0f,        1.0f,  1.0f,  1.0f,        1.0f,  1.0f,  1.0f,        1.0f,  1.0f, -1.0f,        1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,       -1.0f,  1.0f,  1.0f,        1.0f,  1.0f,  1.0f,        1.0f,  1.0f,  1.0f,        1.0f, -1.0f,  1.0f,       -1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,        1.0f,  1.0f, -1.0f,        1.0f,  1.0f,  1.0f,        1.0f,  1.0f,  1.0f,       -1.0f,  1.0f,  1.0f,       -1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,       -1.0f, -1.0f,  1.0f,        1.0f, -1.0f, -1.0f,        1.0f, -1.0f, -1.0f,       -1.0f, -1.0f,  1.0f,        1.0f, -1.0f,  1.0f
	};

	ztVertexEntryGL entries[] = {
		{ GL_FLOAT, 3 * sizeof(GLfloat) },
	};

	struct CubeRender
	{
		ztVertexArrayGL   va;
		ztShaderGL       *shader;
		ztTextureGL      *texture;
		int               mip_levels;

		static ZT_FUNC_GL_TEXTURE_RENDER(render)
		{
			CubeRender *cube_render = (CubeRender*)user_data;

			if (side == 0) {
				ztgl_shaderVariableTex(cube_render->shader, zt_strHash("equirectangular_map"), cube_render->texture);
				ztgl_shaderVariableMat4(cube_render->shader, zt_strHash("projection"), proj->values);

				ztgl_setViewport(w, h);

				if (cube_render->mip_levels > 1) {
					r32 roughness = (r32)mip_level / (r32)(cube_render->mip_levels - 1);
					ztgl_shaderVariableFloat(cube_render->shader, zt_strHash("roughness"), roughness);
				}
			}

			ztgl_shaderVariableMat4(cube_render->shader, zt_strHash("view"), view->values);

			ztgl_clear(ztColor_Green);
			ztgl_vertexArrayDraw(&cube_render->va);
		}
	};

	CubeRender cube_render;
	cube_render.mip_levels = 1;

	if (!ztgl_vertexArrayMake(&cube_render.va, entries, zt_elementsOf(entries), vertices, zt_elementsOf(vertices) / 3)) {
		return nullptr;
	}

	if (hdr_texture != nullptr) {
		const char *vert_shader = "#version 330 core\nlayout (location = 0) in vec3 position;\n\nout vec3 world_position;\n\nuniform mat4 projection;\nuniform mat4 view;\n\nvoid main()\n{\n    world_position = position;  \n    gl_Position =  projection * view * vec4(world_position, 1.0);\n}";
		const char *frag_shader = "#version 330 core\nout vec4 frag_color;\nin vec3 world_position;\n\nuniform sampler2D equirectangular_map;\n\nconst vec2 inv_atan = vec2(0.1591, 0.3183);\n\nvec2 sampleSphericalMap(vec3 v)\n{\n    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));\n    uv *= inv_atan;\n    uv += 0.5;\n    return uv;\n}\n\nvoid main()\n{		\n    vec2 uv = sampleSphericalMap(normalize(world_position));\n    vec3 clr = texture(equirectangular_map, uv).rgb;\n    \n    frag_color = vec4(clr, 1.0);\n}";
		cube_render.shader = ztgl_shaderMake(context, vert_shader, frag_shader);
		cube_render.texture = hdr_texture;
	}
	else if (cube_map_irradiance != nullptr) {
		const char *vert_shader = "#version 330 core\nlayout (location = 0) in vec3 position;\n\nout vec3 world_position;\n\nuniform mat4 projection;\nuniform mat4 view;\n\nvoid main()\n{\n    world_position = position;  \n    gl_Position =  projection * view * vec4(world_position, 1.0);\n}";
		const char *frag_shader = "#version 330 core\nout vec4 frag_color;\nin vec3 world_position;\n\nuniform samplerCube environment_map;\n\nconst float PI = 3.14159265359;\n\nvoid main()\n{		\n    vec3 npos = normalize(world_position);\n    vec3 irradiance = vec3(0.0);   \n    vec3 up    = vec3(0.0, 1.0, 0.0);\n    vec3 right = cross(up, npos);\n    up = cross(npos, right);\n       \n    float sample_delta = 0.025;\n    float cnt_samples = 0.0f;\n    for (float phi = 0.0; phi < 2.0 * PI; phi += sample_delta) {\n        for (float theta = 0.0; theta < 0.5 * PI; theta += sample_delta) {\n            vec3 tangent_simple = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));\n            vec3 sample_vec = tangent_simple.x * right + tangent_simple.y * up + tangent_simple.z * npos;\n\n            irradiance += texture(environment_map, sample_vec).rgb * cos(theta) * sin(theta);\n            cnt_samples++;\n        }\n    }\n    irradiance = PI * irradiance * (1.0 / float(cnt_samples));\n    \n    frag_color = vec4(irradiance, 1.0);\n}";
		cube_render.shader = ztgl_shaderMake(context, vert_shader, frag_shader);
		cube_render.texture = cube_map_irradiance;
	}
	else if(cube_map_prefilter != nullptr) {
		const char *vert_shader = "#version 330 core\nlayout (location = 0) in vec3 position;\n\nout vec3 world_position;\n\nuniform mat4 projection;\nuniform mat4 view;\n\nvoid main()\n{\n    world_position = position;  \n    gl_Position =  projection * view * vec4(world_position, 1.0);\n}";
		const char *frag_shader = "#version 330 core\nout vec4 frag_color;\nin vec3 world_position;\n\nuniform samplerCube environment_map;\nuniform float roughness;\n\nconst float PI = 3.14159265359;\n\n// ----------------------------------------------------------------------------\n\nfloat distributionGGX(vec3 N, vec3 H, float roughness)\n{\n    float a = roughness * roughness;\n    float a2 = a*a;\n    float n_dot_h = max(dot(N, H), 0.0);\n    float n_dot_h2 = n_dot_h * n_dot_h;\n\n    float nom   = a2;\n    float denom = (n_dot_h2 * (a2 - 1.0) + 1.0);\n    denom = PI * denom * denom;\n\n    return nom / denom;\n}\n\nfloat radicalInverseVdC(uint bits) \n{\n     bits = (bits << 16u) | (bits >> 16u);\n     bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);\n     bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);\n     bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);\n     bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);\n     return float(bits) * 2.3283064365386963e-10; // / 0x100000000\n}\n\n// ----------------------------------------------------------------------------\n\nvec2 hammersley(uint i, uint N)\n{\n	return vec2(float(i)/float(N), radicalInverseVdC(i));\n}\n\n// ----------------------------------------------------------------------------\n\nvec3 importanceSampleGGX(vec2 Xi, vec3 N, float roughness)\n{\n	float a = roughness * roughness;\n	\n	float phi = 2.0 * PI * Xi.x;\n	float cos_theta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));\n	float sin_theta = sqrt(1.0 - cos_theta*cos_theta);\n	\n	// from spherical coordinates to cartesian coordinates - halfway vector\n	vec3 H;\n	H.x = cos(phi) * sin_theta;\n	H.y = sin(phi) * sin_theta;\n	H.z = cos_theta;\n	\n	// from tangent-space H vector to world-space sample vector\n	vec3 up          = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);\n	vec3 tangent   = normalize(cross(up, N));\n	vec3 bitangent = cross(N, tangent);\n	\n	vec3 sample_vec = tangent * H.x + bitangent * H.y + N * H.z;\n	return normalize(sample_vec);\n}\n\n// ----------------------------------------------------------------------------\n\nvoid main()\n{		\n    vec3 N = normalize(world_position);\n    \n    // make the simplyfying assumption that V equals R equals the normal \n    vec3 R = N;\n    vec3 V = R;\n\n    const uint SAMPLE_COUNT = 1024u;\n    vec3 prefiltered_color = vec3(0.0);\n    float total_weight = 0.0;\n    \n    for (uint i = 0u; i < SAMPLE_COUNT; ++i) {\n        // generates a sample vector that's biased towards the preferred alignment direction (importance sampling).\n        vec2 Xi = hammersley(i, SAMPLE_COUNT);\n        vec3 H = importanceSampleGGX(Xi, N, roughness);\n        vec3 L  = normalize(2.0 * dot(V, H) * H - V);\n\n        float NdotL = max(dot(N, L), 0.0);\n        if(NdotL > 0.0)\n        {\n            // sample from the environment's mip level based on roughness/pdf\n            float D   = distributionGGX(N, H, roughness);\n            float n_dot_h = max(dot(N, H), 0.0);\n            float HdotV = max(dot(H, V), 0.0);\n            float pdf = D * n_dot_h / (4.0 * HdotV) + 0.0001; \n\n            float resolution = 512.0; // resolution of source cubemap (per face)\n            float sa_texel  = 4.0 * PI / (6.0 * resolution * resolution);\n            float sa_sample = 1.0 / (float(SAMPLE_COUNT) * pdf + 0.0001);\n\n            float mip_level = roughness == 0.0 ? 0.0 : 0.5 * log2(sa_sample / sa_texel); \n            \n            prefiltered_color += textureLod(environment_map, L, mip_level).rgb * NdotL;\n            total_weight      += NdotL;\n        }\n    }\n\n    prefiltered_color = prefiltered_color / total_weight;\n\n    frag_color = vec4(prefiltered_color, 1.0);\n}";
		cube_render.shader = ztgl_shaderMake(context, vert_shader, frag_shader);
		cube_render.texture = cube_map_prefilter;
		cube_render.mip_levels = 5;
	}

	if (cube_render.shader == nullptr) {
		ztgl_vertexArrayFree(&cube_render.va);
		return nullptr;
	}

	ztgl_shaderBegin(cube_render.shader);
	ztTextureGL *cube_map_result = ztgl_textureMakeCubeMapFromRender(context, w, h, cube_render.mip_levels, CubeRender::render, &cube_render);
	ztgl_shaderEnd(cube_render.shader);

	ztgl_vertexArrayFree(&cube_render.va);
	ztgl_shaderFree(cube_render.shader);

	return cube_map_result;
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeCubeMapFromHDR(ztContextGL *context, ztTextureGL *hdr_texture, int w, int h)
{
	return _ztgl_textureMakeCubeMapFromOther(context, hdr_texture, nullptr, nullptr, w, h);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeCubeMapForDepth(ztContextGL *context, i32 dimension)
{
	ZT_PROFILE_OPENGL("ztgl_textureMakeCubeMapFromRender");

	struct local
	{
		static bool load(GLuint *frame_buffer_id, GLuint *tex_id, i32 dimension)
		{
			ztgl_callAndReturnValOnError(glGenTextures(1, tex_id), false);
			ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_CUBE_MAP, *tex_id), false);

			zt_fiz(6) {
				ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, dimension, dimension, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr), false);
			}

			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);

			ztgl_callAndReturnValOnError(glGenFramebuffers(1, frame_buffer_id), false);
			ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, *frame_buffer_id), false);

			ztgl_callAndReturnValOnError(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *tex_id, 0), false);

			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);

			ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, 0), false);

			return true;
		}
	};

	GLuint frame_buffer_id, tex_id;
	if (!local::load(&frame_buffer_id, &tex_id, dimension)) {
		return nullptr;
	}

	ztMemoryArena *arena = zt_memGetGlobalArena();

	ztTextureGL *texture = zt_mallocStructArena(ztTextureGL, arena);

	texture->texid             = tex_id;
	texture->fbo               = frame_buffer_id;
	texture->dbo               = 0;
	texture->rt                = 0;
	texture->rb                = 0;
	texture->w                 = dimension;
	texture->h                 = dimension;
	texture->wa                = dimension;
	texture->ha                = dimension;
	texture->d                 = 1;
	texture->attachments_count = 0;
	texture->flags             = ztTextureGLFlags_CubeMap | ztTextureGLFlags_DepthMap;
	texture->arena             = arena;
	texture->context           = context;

	return texture;
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeIrradianceCubeMapFromCubeMap(ztContextGL *context, ztTextureGL *cube_map_texture)
{
	return _ztgl_textureMakeCubeMapFromOther(context, nullptr, cube_map_texture, nullptr, 32, 32);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakePrefilterCubeMapFromCubeMap(ztContextGL *context, ztTextureGL *cube_map_texture)
{
	return _ztgl_textureMakeCubeMapFromOther(context, nullptr, nullptr, cube_map_texture, 128, 128);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeRenderTarget(ztContextGL *context, int w, int h, i32 flags)
{
	return ztgl_textureMakeRenderTarget(context, zt_memGetGlobalArena(), w, h, flags);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeRenderTarget(ztContextGL *context, ztMemoryArena *arena, int w, int h, i32 flags)
{
	ZT_PROFILE_OPENGL("ztgl_textureMakeRenderTarget");

	return _ztgl_textureMakeBase(context, arena, nullptr, w, h, 4, flags);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeDepthRenderTarget(ztContextGL *context, int w, int h)
{
	return ztgl_textureMakeDepthRenderTarget(context, zt_memGetGlobalArena(), w, h);
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureMakeDepthRenderTarget(ztContextGL *context, ztMemoryArena *arena, int w, int h)
{
	ZT_PROFILE_OPENGL("ztgl_textureMakeDepthRenderTarget");

	return ztgl_textureMakeRenderTarget(context, arena, w, h, ztTextureGLFlags_DepthMap);
}

// ================================================================================================================================================================================================

void ztgl_textureFree(ztTextureGL *texture)
{
	ZT_PROFILE_OPENGL("ztgl_textureFree");

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

// ================================================================================================================================================================================================

void ztgl_textureBindReset(ztShaderGL *shader)
{
	ZT_PROFILE_OPENGL("ztgl_textureBindReset");

	if (shader->textures_bound == 0) {
		return;
	}

	ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_2D, 0));
	ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0));
	shader->textures_bound = 0;
}

// ================================================================================================================================================================================================

void ztgl_textureBind(ztTextureGL *texture, int as_idx)
{
	ZT_PROFILE_OPENGL("ztgl_textureBind");

	zt_returnOnNull(texture);
	ztgl_callAndReportOnErrorFast(glActiveTexture(GL_TEXTURE0 + as_idx));

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_CubeMap)) {
		ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_CUBE_MAP, texture->texid));
	}
	else {
		ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_2D, texture->texid));
	}
}

// ================================================================================================================================================================================================

ztInternal void _ztgl_textureRenderTargetSetDrawBuffers(ztTextureGL *texture, bool force_on)
{
	GLenum targets[zt_elementsOf(texture->attachments)];

	int target_idx = 0;
	targets[target_idx++] = GL_COLOR_ATTACHMENT0;

	zt_fize(texture->attachments) {
		if (texture->attachments_enabled[i] || (texture->attachments[i] != 0 && force_on)) {
			targets[target_idx++] = GL_COLOR_ATTACHMENT0 + 1 + i;
		}
	}

	ztgl_callAndReportOnError(glDrawBuffers(target_idx, targets));
}

// ================================================================================================================================================================================================

void ztgl_textureRenderTargetPrepare(ztTextureGL *texture, bool clear)
{
	ZT_PROFILE_OPENGL("ztgl_textureRenderTargetPrepare");

	zt_returnOnNull(texture);
	zt_assertReturnOnFail(texture->context != nullptr && texture->context->active_render_target == nullptr);

	ztgl_callAndReportOnErrorFast(glBindFramebuffer(texture->rb != 0 ? GL_DRAW_FRAMEBUFFER : GL_FRAMEBUFFER, texture->fbo));

#	if !defined(ZT_GLES)

	if (!zt_bitIsSet(texture->flags, ztTextureGLFlags_CubeMap) && !zt_bitIsSet(texture->flags, ztTextureGLFlags_DepthMap)) {
		if (clear) {
			_ztgl_textureRenderTargetSetDrawBuffers(texture, true);
			ztgl_callAndReportOnErrorFast(glClearColor(0, 0, 0, 0));
			ztgl_callAndReportOnErrorFast(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			_ztgl_textureRenderTargetSetDrawBuffers(texture, false);
		}
	}
	else {
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

#	else
	ztgl_callAndReportOnErrorFast(glBindTexture(GL_TEXTURE_2D, 0));
#	endif

	ztgl_callAndReportOnErrorFast(glViewport(0, 0, texture->wa, texture->ha));

#	if !defined(ZT_GLES)
	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_Multisample)) {
		ztgl_callAndReportOnErrorFast(glEnable(GL_MULTISAMPLE));
	}
	else {
		ztgl_callAndReportOnErrorFast(glDisable(GL_MULTISAMPLE));
	}
#	endif

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_DepthMap)) {
		ztgl_callAndReportOnErrorFast(glCullFace(GL_FRONT));
		ztgl_callAndReportOnErrorFast(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	if (clear) {
		ztgl_callAndReportOnErrorFast(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	texture->flags |= ztTextureGLFlags_RenderTargetWriting;

	texture->context->active_render_target = texture;
}

// ================================================================================================================================================================================================

void ztgl_textureRenderTargetCommit(ztTextureGL *texture, ztContextGL *context)
{
	ZT_PROFILE_OPENGL("ztgl_textureRenderTargetCommit");

	zt_assertReturnOnFail(texture->context != nullptr && texture->context->active_render_target == texture);

	ztgl_callAndReportOnErrorFast(glBindFramebuffer(texture->rb != 0 ? GL_DRAW_FRAMEBUFFER : GL_FRAMEBUFFER, 0));

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_DepthMap)) {
		ztgl_callAndReportOnErrorFast(glCullFace(GL_BACK));
	}

#	if !defined(ZT_GLES)
	ztgl_callAndReportOnErrorFast(glDisable(GL_MULTISAMPLE));
#	endif

#	if !defined(ZT_GLES2)
	if (texture->rb != 0) {
		ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_READ_FRAMEBUFFER, texture->fbo));
		ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, texture->rb));
		glReadBuffer(GL_COLOR_ATTACHMENT0);

		ztgl_callAndReportOnErrorFast(glBlitFramebuffer(0, 0, texture->wa, texture->ha, 0, 0, texture->wa, texture->ha, GL_COLOR_BUFFER_BIT, GL_LINEAR));

		zt_fiz(texture->attachments_count) {
			glReadBuffer(GL_COLOR_ATTACHMENT0 + 1 + i);
			ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
			ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, texture->attachments[i]));

			ztgl_callAndReportOnErrorFast(glBlitFramebuffer(0, 0, texture->wa, texture->ha, 0, 0, texture->wa, texture->ha, GL_COLOR_BUFFER_BIT, GL_LINEAR));
		}

		ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
		ztgl_callAndReportOnErrorFast(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));

		glDisable(GL_BLEND);
		glEnable(GL_BLEND);
		ztgl_callAndReportOnErrorFast(glFinish());
		ztgl_callAndReportOnErrorFast(glFlush());
	}
#	endif

	ztgl_setViewport(context);

	zt_bitRemove(texture->flags, ztTextureGLFlags_RenderTargetWriting);
	texture->context->active_render_target = nullptr;
}

// ================================================================================================================================================================================================

ztTextureGL *ztgl_textureRenderTargetAddAttachment(ztTextureGL *texture, ztTextureGLColorFormat_Enum color_format)
{
	ZT_PROFILE_OPENGL("ztgl_textureRenderTargetAddAttachment");

	zt_returnValOnNull(texture, nullptr);
	zt_assertReturnValOnFail(ztgl_textureIsRenderTarget(texture), nullptr);

	ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, texture->fbo), nullptr);
	ztgl_callAndReturnValOnError(glBindRenderbuffer(GL_RENDERBUFFER, texture->dbo), false);

	i32 flags = ztTextureGLFlags_Attachment;

	GLuint attachment = 0;
	int attachment_idx = texture->attachments_count++;
	ztgl_callAndReturnValOnError(glGenTextures(1, &attachment), nullptr);
	ztgl_callAndReturnValOnError(glActiveTexture(GL_TEXTURE0 + texture->attachments_count), nullptr);

	bool multisample = zt_bitIsSet(texture->flags, ztTextureGLFlags_Multisample);
	if (multisample) {
		flags |= ztTextureGLFlags_Multisample;
		ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, attachment), false);
	}
	else {
		ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, attachment), nullptr);
	}

	GLint color_lvl = GL_RGBA;
	GLint color_fmt = GL_RGBA;
	GLint color_type = GL_UNSIGNED_BYTE;
	int   color_depth = 4;

	switch(color_format)
	{
		case ztTextureGLColorFormat_RGBA   : color_depth = 4; color_lvl = GL_RGBA   ; color_fmt = GL_RGBA   ; break;
		case ztTextureGLColorFormat_RGB    : color_depth = 3; color_lvl = GL_RGB    ; color_fmt = GL_RGB    ; break;
		case ztTextureGLColorFormat_RGBA16F: color_depth = 4; color_lvl = GL_RGBA16F; color_fmt = GL_RGBA   ; color_type = GL_FLOAT; break;
		case ztTextureGLColorFormat_RGB16F : color_depth = 3; color_lvl = GL_RGB16F ; color_fmt = GL_RGB    ; color_type = GL_FLOAT; break;

		default: zt_assertReturnValOnFail(false, nullptr);
	}

	if(multisample) {
		ztgl_callAndReturnValOnError(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16F, texture->w, texture->h, GL_TRUE), false);
	}
	else {
		ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, color_lvl, texture->w, texture->h, 0, color_fmt, color_type, NULL), nullptr);
	}

	ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), nullptr);
	ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), nullptr);
	ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0), nullptr);
	ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
	ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);

	if(multisample) {
		ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0), false);
		ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + texture->attachments_count, GL_TEXTURE_2D_MULTISAMPLE, attachment, 0), nullptr);
	}
	else {
		ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), nullptr);
		ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + texture->attachments_count, GL_TEXTURE_2D, attachment, 0), nullptr);
	}

	_ztgl_textureRenderTargetSetDrawBuffers(texture, false);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		zt_assertReturnValOnFail(false, nullptr);
	}
	ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, 0), nullptr);

	GLuint render_target_id = 0;
	GLuint resolve_buffer_id = 0;

	if (multisample) {
		// because we can't use multisample textures directly, we need a new render buffer to blit to when the original writing is complete

		render_target_id = attachment;

		ztgl_callAndReturnValOnError(glGenFramebuffers(1, &resolve_buffer_id), false);
		ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, resolve_buffer_id), false);

		ztgl_callAndReturnValOnError(glGenTextures(1, &attachment), false);
		ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, attachment), false);
		if (zt_bitIsSet(flags, ztTextureGLFlags_PixelPerfect)) {
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), false);
		}
		else {
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), false);
		}

		if (zt_bitIsSet(flags, ztTextureGLFlags_Repeat)) {
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT), false);
		}
		else {
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), false);
			ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), false);
		}

		ztgl_callAndReturnValOnError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0), false);
		ztgl_callAndReturnValOnError(glTexImage2D(GL_TEXTURE_2D, 0, color_lvl, texture->w, texture->h, 0, color_fmt, color_type, NULL), nullptr);
		ztgl_callAndReturnValOnError(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, attachment, 0), false);
		ztgl_callAndReturnValOnError(glBindTexture(GL_TEXTURE_2D, 0), false);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			zt_assertReturnValOnFail(false, nullptr);
		}
		ztgl_callAndReturnValOnError(glBindFramebuffer(GL_FRAMEBUFFER, 0), nullptr);
	}

	ztMemoryArena *arena = zt_memGetGlobalArena();

	ztTextureGL *ntexture = zt_mallocStructArena(ztTextureGL, arena);

	ntexture->texid             = attachment;
	ntexture->fbo               = 0;
	ntexture->dbo               = 0;
	ntexture->rt                = render_target_id;
	ntexture->rb                = resolve_buffer_id;
	ntexture->w                 = texture->w;
	ntexture->h                 = texture->h;
	ntexture->d                 = color_depth;
	ntexture->attachments_count = 0;
	ntexture->flags             = flags;
	ntexture->arena             = arena;

	texture->attachments        [attachment_idx] = resolve_buffer_id;
	texture->attachments_enabled[attachment_idx] = true;

	return ntexture;
}

// ================================================================================================================================================================================================

void ztgl_textureRenderTargetAttachmentEnable(ztTextureGL *texture, int attachment_idx, bool enable)
{
	ZT_PROFILE_OPENGL("ztgl_textureRenderTargetAttachmentEnable");

	zt_returnOnNull(texture);
	zt_assertReturnOnFail(ztgl_textureIsRenderTarget(texture));
	zt_assertReturnOnFail(attachment_idx >= 0 && attachment_idx < zt_elementsOf(texture->attachments));
	
	if (texture->attachments[attachment_idx] == 0) {
		return;
	}

	if (texture->attachments_enabled[attachment_idx] == enable) {
		return;
	}

	texture->attachments_enabled[attachment_idx] = enable;

	if (zt_bitIsSet(texture->flags, ztTextureGLFlags_RenderTargetWriting)) {
		_ztgl_textureRenderTargetSetDrawBuffers(texture, false);
	}
}

// ================================================================================================================================================================================================

bool ztgl_textureIsRenderTarget(ztTextureGL *texture)
{
	ZT_PROFILE_OPENGL("ztgl_textureIsRenderTarget");

	zt_returnValOnNull(texture, false);
	return texture->fbo != 0;
}

// ================================================================================================================================================================================================

void ztgl_textureGetPixels(ztTextureGL *texture, ztContextGL *context, byte *pixels)
{
	ZT_PROFILE_OPENGL("ztgl_textureGetPixels");

#	if defined(ZT_GLES)
	zt_assert(false); // this is not supported in ES
#	else
	if (texture->fbo != 0) {
		ztgl_callAndReportOnError(glBindFramebuffer(GL_READ_FRAMEBUFFER, texture->rb));
		ztgl_callAndReportOnError(glReadBuffer(GL_COLOR_ATTACHMENT0));
		ztgl_callAndReportOnError(glReadPixels(0, 0, texture->w, texture->h, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
		ztgl_callAndReportOnError(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));

		int half_height = texture->h / 2;
		u32* pix_u32 = ((u32*)pixels);
		for (int y = 0; y < half_height; ++y) {
			for (int x = 0; x < texture->w; ++x) {
				int idx_1 = (y * texture->w) + x;
				int idx_2 = (((texture->h - y) - 1) * texture->w) + x;
				uint32 pixel = pix_u32[idx_2];
				pix_u32[idx_2] = pix_u32[idx_1];
				pix_u32[idx_1] = pixel;
			}
		}
	}
	else {
		ztgl_callAndReportOnError(glBindTexture(GL_TEXTURE_2D, texture->texid));
		ztgl_callAndReportOnError(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels));
		ztgl_callAndReportOnError(glBindTexture(GL_TEXTURE_2D, 0));
	}
#endif
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void ztgl_drawVertices(GLenum mode, ztVertexEntryGL *entries, int entries_count, void *vertices, int vert_count)
{
	ZT_PROFILE_OPENGL("ztgl_drawVertices");

#	if defined(ZT_GLES2)
	zt_assert(false); // this is not supported here, must use ztVertexArrayGL
#	endif

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

			case GL_INT: {
				attrib_size = 4;
			} break;

			default: {
				zt_assert(false);
			} break;
		}

		ztgl_callAndReportOnErrorFast(glVertexAttribPointer(i, entries[i].size / attrib_size, entries[i].type, GL_FALSE, vert_size, (GLvoid*)((byte*)vertices + size)));
		ztgl_callAndReportOnErrorFast(glEnableVertexAttribArray(i));

		size += entries[i].size;
	}

	ztgl_callAndReportOnErrorFast(glDrawArrays(mode, 0, vert_count));

	zt_fiz(entries_count) {
		glDisableVertexAttribArray(i);
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal bool _ztgl_vertexArrayMake(ztVertexArrayGL *vertex_array, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count, bool create)
{
	ZT_PROFILE_OPENGL("_ztgl_vertexArrayMake");

	zt_returnValOnNull(vertex_array, false);
	zt_returnValOnNull(entries, false);
	zt_assertReturnValOnFail(entries_count > 0, false);
	//zt_returnValOnNull(vert_data, false);
	//zt_assertReturnValOnFail(vert_count > 0, false);

	int vert_size = 0;
	zt_fiz(entries_count) {
		vert_size += entries[i].size;
	}

	if (!create) {
		if (vert_count > vertex_array->vert_count) {
			ztgl_vertexArrayFree(vertex_array);
			create = true;
			zt_logDebug("had to recreate vertex array (%d not as big as %d)", vertex_array->vert_count, vert_count);
		}
	}

	if (create) {
#		if defined(ZT_OPENGL_HAS_VAOS)
		ztgl_callAndReturnValOnError(glGenVertexArrays(1, &vertex_array->vao), false);
#		endif

		ztgl_callAndReturnValOnError(glGenBuffers(1, &vertex_array->vbo), false);
		vertex_array->vert_count = vert_count;

#		if !defined(ZT_OPENGL_HAS_VAOS)
		vertex_array->vert_data = zt_mallocStructArray(byte, vert_size * vert_count);
#		endif
	}

#	if defined(ZT_OPENGL_HAS_VAOS)
	ztgl_callAndReturnValOnError(glBindVertexArray(vertex_array->vao), false);
#	endif
	{
		ztgl_callAndReturnValOnError(glBindBuffer(GL_ARRAY_BUFFER, vertex_array->vbo), false);
		ztgl_callAndReturnValOnError(glBufferData(GL_ARRAY_BUFFER, vert_count * vert_size, vert_data, GL_DYNAMIC_DRAW), false);

		int size = 0;
		zt_fiz(entries_count) {
			int attrib_size = 0;
			switch (entries[i].type)
			{
				case GL_FLOAT: {
					attrib_size = 4;
					ztgl_callAndReturnValOnError(glEnableVertexAttribArray(i), false);
					ztgl_callAndReturnValOnError(glVertexAttribPointer(i, entries[i].size / attrib_size, entries[i].type, GL_FALSE, vert_size, (GLvoid*)size), false);
				} break;

				case GL_INT: {
#					if defined(ZT_GLES2)
					zt_assert(false); // not supported in ES2
#					else
					attrib_size = 4;
					ztgl_callAndReturnValOnError(glVertexAttribIPointer(i, entries[i].size / attrib_size, entries[i].type, vert_size, (GLvoid*)size), false);
					ztgl_callAndReturnValOnError(glEnableVertexAttribArray(i), false);
#					endif
				} break;

				default: {
					zt_assert(false);
				} break;
			}

			size += entries[i].size;
		}
		ztgl_callAndReturnValOnError(glBindBuffer(GL_ARRAY_BUFFER, 0), false);
	}
#	if defined(ZT_OPENGL_HAS_VAOS)
	ztgl_callAndReturnValOnError(glBindVertexArray(0), false);
#	else
	if (vert_data) {
		zt_memCpy(vertex_array->vert_data, vertex_array->vert_count, vert_data, vert_count);
	}
	zt_memCpy(vertex_array->entries, zt_elementsOf(vertex_array->entries) * zt_sizeof(ztVertexEntryGL), entries, entries_count * zt_sizeof(ztVertexEntryGL));
#	endif

	vertex_array->vert_count_active = vert_count;
	return true;
}

// ================================================================================================================================================================================================

bool ztgl_vertexArrayMake(ztVertexArrayGL *vertex_array, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count)
{
	ZT_PROFILE_OPENGL("ztgl_vertexArrayMake");

	return _ztgl_vertexArrayMake(vertex_array, entries, entries_count, vert_data, vert_count, true);
}

// ================================================================================================================================================================================================

void ztgl_vertexArrayFree(ztVertexArrayGL *vertex_array)
{
	ZT_PROFILE_OPENGL("ztgl_vertexArrayFree");

	if (vertex_array == nullptr || vertex_array->vbo == 0) {
		return;
	}

#	if defined(ZT_OPENGL_HAS_VAOS)
	ztgl_callAndReportOnError(glDeleteVertexArrays(1, &vertex_array->vao));
#	endif

	ztgl_callAndReportOnError(glDeleteBuffers(1, &vertex_array->vbo));

	vertex_array->vao = vertex_array->vbo = vertex_array->vert_count = 0;

#	if !defined(ZT_OPENGL_HAS_VAOS)
	if (vertex_array->vert_data) {
		zt_free(vertex_array->vert_data);
	}
#	endif
}

// ================================================================================================================================================================================================

bool ztgl_vertexArrayUpdate(ztVertexArrayGL *vertex_array, ztVertexEntryGL *entries, int entries_count, void *vert_data, int vert_count)
{
	ZT_PROFILE_OPENGL("ztgl_vertexArrayUpdate");

	return _ztgl_vertexArrayMake(vertex_array, entries, entries_count, vert_data, vert_count, false);
}

// ================================================================================================================================================================================================

void ztgl_vertexArrayDraw(ztVertexArrayGL *vertex_array, GLenum mode)
{
	ZT_PROFILE_OPENGL("ztgl_vertexArrayDraw");

#	if defined(ZT_OPENGL_HAS_VAOS)
	ztgl_callAndReportOnErrorFast(glBindVertexArray(vertex_array->vao));
	ztgl_callAndReportOnErrorFast(glDrawArrays(mode, 0, vertex_array->vert_count_active));
	ztgl_callAndReportOnErrorFast(glBindVertexArray(0));
#	else
	ztgl_callAndReportOnErrorFast(glBindBuffer(GL_ARRAY_BUFFER, vertex_array->vbo));
	ztgl_callAndReportOnErrorFast(glDrawArrays(mode, 0, vertex_array->vert_count_active));
	ztgl_callAndReportOnErrorFast(glBindBuffer(GL_ARRAY_BUFFER, 0));
#	endif
}


#endif // implementation

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


#ifdef __zt_game_h_internal_included__

bool _zt_shaderLangConvertToGLSL(ztShLangSyntaxNode *global_node, ztString *vs, ztString *gs, ztString *fs, ztString *error)
{
	ZT_PROFILE_OPENGL("_zt_shaderLangConvertToGLSL");

	*vs = *gs = *fs = *error = nullptr;

#	define vv_prefix "_ztvv_"

	struct local
	{
		enum Shader_Enum
		{
			Shader_Vert,
			Shader_Geom,
			Shader_Frag,
		};

		struct Vars
		{
			ztShLangSyntaxNode *v_output = nullptr;
			ztShLangSyntaxNode *v_position = nullptr;

			ztShLangSyntaxNode *f_input = nullptr;
			ztShLangSyntaxNode *f_color = nullptr;
			//ztShLangSyntaxNode *f_textures = nullptr;

			ztShLangSyntaxNode *struct_input = nullptr;
			ztShLangSyntaxNode *struct_output = nullptr;
			ztShLangSyntaxNode *struct_uniform = nullptr;
			ztShLangSyntaxNode *struct_textures = nullptr;

			ztShLangSyntaxNode *var_input = nullptr;

			Shader_Enum         which_shader;
		};

		// ----------------------------------------------

		static const char *dataType(const char *data_type, bool *is_texture = nullptr)
		{
			if (zt_strEquals(data_type, "texture2d")) {
				if(is_texture) *is_texture = true;
				return "sampler2D";
			}
			if(zt_strEquals(data_type, "textureCube")) {
				return "samplerCube";
			}

			return data_type;
		}

		// ----------------------------------------------

		static void writeVariableDecl(ztShLangSyntaxNode *var_node, ztString *s, int s_len, Vars *vars, bool needs_flat = false, const char *name_prefix = nullptr)
		{
			if (var_node->variable_decl.is_const) {
				zt_strCat(*s, s_len, "const ");
			}

			if (needs_flat) {
				switch (var_node->variable_decl.type)
				{
					case ztShLangTokenType_ivec2:
					case ztShLangTokenType_ivec3:
					case ztShLangTokenType_ivec4:
					case ztShLangTokenType_int:
						zt_strCat(*s, s_len, "flat ");
						break;
				}
			}

			if (var_node->first_child && var_node->first_child->type == ztShLangSyntaxNodeType_Operation && var_node->first_child->operation.right->type != ztShLangSyntaxNodeType_Scope) {
				zt_strMakePrintf(vardecl, 256, "%s %s", dataType(var_node->variable_decl.type_name), (name_prefix == nullptr ? "" : name_prefix));
				zt_strCat(*s, s_len, vardecl);

				zt_flink(child, var_node->first_child) {
					write(child, 0, s, s_len, vars);
				}
			}
			else {
				zt_strMakePrintf(vardecl, 256, "%s %s%s", dataType(var_node->variable_decl.type_name), (name_prefix == nullptr ? "" : name_prefix), var_node->variable_decl.name);
				zt_strCat(*s, s_len, vardecl);
			}

			if (var_node->variable_decl.array_size != -1) {
				zt_strMakePrintf(var_arr, 16, "[%d]", var_node->variable_decl.array_size);
				zt_strCat(*s, s_len, var_arr);

				if (var_node->first_child && var_node->first_child->type == ztShLangSyntaxNodeType_Operation && var_node->first_child->operation.right->type == ztShLangSyntaxNodeType_Scope) {
					zt_strCatf(*s, s_len, " = %s[]( ", dataType(var_node->variable_decl.type_name));
					zt_flink(child, var_node->first_child->operation.right->first_child) {
						write(child, 0, s, s_len, vars);

						if(child->next != nullptr) {
							zt_strCat(*s, s_len, ", ");
						}
					}
					zt_strCat(*s, s_len, " )");
				}
			}
		}

		// ----------------------------------------------

		static void writeStructs(ztShLangSyntaxNode *global_node, ztShLangSyntaxNode *func_node, ztShLangSyntaxNode **ignore_structs, int ignore_structs_size, ztString *s, int s_len, Vars *vars)
		{
			zt_flink(child, global_node->first_child) {
				if (child->type == ztShLangSyntaxNodeType_Structure) {
					if (child->token == nullptr) {
						continue;
					}
					bool ignore = false;
					zt_fiz(ignore_structs_size) {
						if ((ignore = (ignore_structs[i] == child))) {
							break;
						}
					}
					if (ignore) {
						continue;
					}

					if (!_zt_shaderLangIsStructureReferenced(func_node, child->structure.name)) {
						continue;
					}

					bool needs_flat = false;

#					if defined(ZT_GLES)

					if (child == vars->struct_output || (child == vars->struct_input && vars->which_shader == Shader_Frag)) {
						//zt_strMakePrintf(prefix, 256, "%s_", vars->v_output->variable_decl.name);
						const char *prefix = "_zt_varying_";

						zt_flink(chvar, child->first_child) {
							zt_strCat(*s, s_len, "varying ");
							writeVariableDecl(chvar, s, s_len, vars, needs_flat, prefix);
							zt_strCat(*s, s_len, ";\n");
						}
						zt_strCat(*s, s_len, "\n");
						continue;
					}

					zt_strCat(*s, s_len, "struct ");

#					else
					if (child == vars->struct_input) {
						zt_strCat(*s, s_len, "in ");

						if(vars->which_shader != Shader_Vert) {
							needs_flat = true;
						}
					}
					else if (child == vars->struct_output) {
						zt_strCat(*s, s_len, "out ");

						if (vars->which_shader == Shader_Vert) {
							needs_flat = true;
						}
					}
					else {
						zt_strCat(*s, s_len, "struct ");
					}
#endif

					zt_strMakePrintf(st_name, 256, "%s\n{\n", child->structure.name);
					zt_strCat(*s, s_len, st_name);
					zt_flink(chvar, child->first_child) {
						zt_strCat(*s, s_len, "\t");
						writeVariableDecl(chvar, s, s_len, vars, needs_flat);
						zt_strCat(*s, s_len, ";\n");
					}

#					if defined(ZT_GLES)
					zt_strCat(*s, s_len, "};\n\n");
#					else
					if (child == vars->struct_input) {
						zt_strCat(*s, s_len, "} ");
						zt_strCat(*s, s_len, vars->f_input->variable_decl.name);
						zt_strCat(*s, s_len, ";\n\n");
					}
					else if (child == vars->struct_output) {
						zt_strCat(*s, s_len, "} ");
						zt_strCat(*s, s_len, vars->v_output->variable_decl.name);
						zt_strCat(*s, s_len, ";\n\n");
					}
					else {
						zt_strCat(*s, s_len, "};\n\n");
					}
#					endif
				}
			}
		}

		// ----------------------------------------------

		static void writeFunctions(ztShLangSyntaxNode *global_node, ztShLangSyntaxNode *func_node, ztString *s, int s_len, Vars *vars)
		{
			zt_flink(child, global_node->first_child) {
				if (child->type == ztShLangSyntaxNodeType_FunctionDecl) {
					if (!_zt_shaderLangIsFunctionReferenced(func_node, child->function_decl.name)) {
						continue;
					}

					bool has_body = false;
					zt_flink(body_check, child->first_child) {
						if (body_check->type == ztShLangSyntaxNodeType_Scope) {
							has_body = true;
							break;
						}
					}
					if (!has_body) break; // built in functions don't have bodies

					zt_strMakePrintf(fn_decl, 512, "%s %s(", child->function_decl.returns_name, child->function_decl.name);
					zt_strCat(*s, s_len, fn_decl);

					ztShLangSyntaxNode *body = nullptr;
					int params = 0;
					zt_flink(param, child->first_child) {
						if (param->type == ztShLangSyntaxNodeType_VariableDecl) {
							if ((vars->struct_uniform && zt_strEquals(param->variable_decl.type_name, vars->struct_uniform->structure.name)) ||
								(vars->struct_textures && zt_strEquals(param->variable_decl.type_name, vars->struct_textures->structure.name)) ||
								(vars->struct_input && zt_strEquals(param->variable_decl.type_name, vars->struct_input->structure.name))) {
								continue;
							}

							if (params++ != 0) {
								zt_strCat(*s, s_len, ", ");
							}
							writeVariableDecl(param, s, s_len, vars);
						}
						else {
							body = param;
							break;
						}
					}
					zt_strCat(*s, s_len, ")\n{\n");

					zt_flink(body_child, body->first_child) {
						write(body_child, 1, s, s_len, vars);
					}
					zt_strCat(*s, s_len, "}\n\n");
				}
			}
		}

		// ----------------------------------------------

		static bool isParent(ztShLangSyntaxNode *child, ztShLangSyntaxNode *parent)
		{
			//if(child->token && zt_bitIsSet(child->token->flags, ztShLangTokenFlags_IdentifierWithAccess)) {
			//	int debug = 1;
			//}
			if (child->parent == parent) {
				return true;
			}
			if (child->parent) {
				return isParent(child->parent, parent);
			}

			return false;
		}

		// ----------------------------------------------

		static void write(ztShLangSyntaxNode *node, int indent, ztString *s, int s_len, Vars *vars)
		{
			zt_fiz(indent) zt_strCat(*s, s_len, "\t");

			switch (node->type)
			{
				case ztShLangSyntaxNodeType_VariableDecl: {
					writeVariableDecl(node, s, s_len, vars);

					//zt_strCat(*s, s_len, ";\n");
				} break;

				case ztShLangSyntaxNodeType_Variable: {
					zt_strMakePrintf(input_check, 256, "%s.", vars->var_input ? vars->var_input->variable_decl.name : "__invalid");
					zt_strMakePrintf(output_check, 256, "%s.", vars->v_output ? vars->v_output->variable_decl.name : "__invalid");
					//zt_strMakePrintf(texture_check, 256, "%s.", vars->f_textures ? vars->f_textures->variable_decl.name : "__invalid");

					if (node->variable_val.decl == vars->f_color) {
#						if defined(ZT_GLES)
						zt_strCat(*s, s_len, "gl_FragColor");
#						else
						zt_strCat(*s, s_len, "_ztfs_frag_color");
#						endif
					}
					else if ((node->variable_val.decl->parent == vars->struct_input || zt_strStartsWith(node->variable_val.name, input_check)) && vars->which_shader == Shader_Vert) {
						zt_strCat(*s, s_len, vv_prefix);

						int pos = zt_strFindPos(node->variable_val.name, ".", 0);
						if (pos != ztStrPosNotFound) {
							zt_strCat(*s, s_len, node->variable_val.name + pos + 1);
						}
						else {
							zt_strCat(*s, s_len, node->variable_val.decl->variable_decl.name);
						}
					}
					else if (node->variable_val.decl->parent == vars->struct_uniform) {
						zt_strCat(*s, s_len, node->variable_val.decl->variable_decl.name);
					}
					else if (node->variable_val.decl->parent == vars->struct_textures) {
						zt_strCat(*s, s_len, node->variable_val.decl->variable_decl.name);
					}
					else if (node->variable_val.decl->parent == vars->struct_output && vars->which_shader == Shader_Frag) {
						zt_strCatf(*s, s_len, "_ztfs_frag_%s", node->variable_val.decl->variable_decl.name);
					}
#					if defined(ZT_GLES)
					else if((vars->which_shader == Shader_Vert && zt_strStartsWith(node->variable_val.name, output_check)) || (vars->which_shader == Shader_Frag && zt_strStartsWith(node->variable_val.name, input_check))) {
					//else if ((node->variable_val.decl->parent == vars->struct_output && ) || (node->variable_val.decl->parent == vars->struct_input && vars->which_shader == Shader_Frag)) {
						char var_name[256];
						zt_strCpy(var_name, zt_elementsOf(var_name), node->variable_val.name);

						char var_name_new[256] = { 0 };
						zt_strCat(var_name_new, zt_elementsOf(var_name_new), "_zt_varying_");
						zt_fize(var_name) {
							if (var_name[i] == '.') {
								zt_strCat(var_name_new, zt_elementsOf(var_name_new), &var_name[i + 1]);
								break;
							}
						}

						zt_strCat(*s, s_len, var_name_new);
					}
#					endif
					else {
						zt_strCat(*s, s_len, node->variable_val.name);
					}

					zt_flink(node_child, node->first_child) {
						zt_strCat(*s, s_len, "[");
						write(node_child, 0, s, s_len, vars);
						zt_strCat(*s, s_len, "]");
					}
				} break;

				case ztShLangSyntaxNodeType_Operation: {
					bool left_is_empty = node->operation.left->type == ztShLangSyntaxNodeType_ValueEmpty;
					bool right_is_empty = node->operation.right == nullptr || node->operation.right->type == ztShLangSyntaxNodeType_ValueEmpty;
					if (!left_is_empty) {
						write(node->operation.left, 0, s, s_len, vars);
					}
					if (!left_is_empty && !right_is_empty) {
						zt_strCat(*s, s_len, " ");
					}
					zt_strCat(*s, s_len, _zt_shaderLangTokenTypeDesc(node->operation.op));
					if (!left_is_empty && !right_is_empty) {
						zt_strCat(*s, s_len, " ");
					}
					//					if (node->operation.right->first_child && !zt_bitIsSet(node->token->flags, ztShLangTokenFlags_ConditionOperator)) {
					//						zt_strCat(*s, s_len, "(");
					//					}
					if (node->operation.right != nullptr) {
						write(node->operation.right, 0, s, s_len, vars);
					}
					//					if (node->operation.right->first_child && !zt_bitIsSet(node->token->flags, ztShLangTokenFlags_ConditionOperator)) {
					//						zt_strCat(*s, s_len, ")");
					//					}
				} break;

				case ztShLangSyntaxNodeType_FunctionCall: {

					bool skip_call = false;
					const char *alternate_name = nullptr;

					if (node->function_call.decl->token == nullptr) {
						// built in function
						if (zt_strEquals(node->function_call.decl->function_decl.name, "textureSample")) {
#							if defined(ZT_GLES)
							ztShLangSyntaxNode *decl_param = node->function_call.decl->first_child;
							zt_flink(param, node->first_child) {
								if ((vars->struct_uniform && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_uniform->structure.name)) ||
									(vars->struct_textures && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_textures->structure.name)) ||
									(vars->struct_input && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_input->structure.name))) {
									decl_param = decl_param->next;
									continue;
								}
								decl_param = decl_param->next;

								if(param->type != ztShLangSyntaxNodeType_Variable) {
									zt_strCat(*s, s_len, "[textureSample parameter must be a variable name]");
								}
								else {
									if(zt_strEquals(dataType(param->variable_val.decl->variable_decl.type_name), "samplerCube")) {
										alternate_name = "textureCube";
									}
									else {
										alternate_name = "texture2D";
									}
								}
								break;
							}

#							else
							alternate_name = "texture";
#							endif
						}
						else if (zt_strEquals(node->function_call.decl->function_decl.name, "textureSampleLOD")) {
							alternate_name = "textureLod";
						}
						else if (zt_strEquals(node->function_call.decl->function_decl.name, "lerp")) {
							alternate_name = "mix";
						}
						else if (zt_strEquals(node->function_call.decl->function_decl.name, "discard")) {
							skip_call = true;
							zt_strCat(*s, s_len, "discard");
						}
#						if defined(ZT_GLES)
						else if (zt_strEquals(node->function_call.decl->function_decl.name, "transpose")) {
							alternate_name = " ";
						}
						else if(zt_strEquals(node->function_call.decl->function_decl.name, "textureSize")) {

							ztShLangSyntaxNode *decl_param = node->function_call.decl->first_child;
							zt_flink(param, node->first_child) {
								if ((vars->struct_uniform && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_uniform->structure.name)) ||
									(vars->struct_textures && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_textures->structure.name)) ||
									(vars->struct_input && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_input->structure.name))) {
									decl_param = decl_param->next;
									continue;
								}
								decl_param = decl_param->next;

								if(param->type != ztShLangSyntaxNodeType_Variable) {
									zt_strCat(*s, s_len, "[textureSize parameter must be a variable name]");
								}
								else {
									zt_strCat(*s, s_len, "_zt_size_of_");
									write(param, 0, s, s_len, vars);
								}
							}

							skip_call = true;
						}
#						endif
					}
					if (!skip_call) {
						if (alternate_name) {
							zt_strCat(*s, s_len, alternate_name);
						}
						else {
							zt_strCat(*s, s_len, node->function_call.name);
						}
						zt_strCat(*s, s_len, "(");

						int param_count = 0;
						ztShLangSyntaxNode *decl_param = node->function_call.decl->first_child;
						zt_flink(param, node->first_child) {
							if ((vars->struct_uniform && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_uniform->structure.name)) ||
								(vars->struct_textures && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_textures->structure.name)) ||
								(vars->struct_input && zt_strEquals(decl_param->variable_decl.type_name, vars->struct_input->structure.name))) {
								decl_param = decl_param->next;
								continue;
							}
							decl_param = decl_param->next;

							if (param_count++ > 0) {
								zt_strCat(*s, s_len, ", ");
							}
							write(param, 0, s, s_len, vars);
						}

						if (zt_strEquals(node->function_call.decl->function_decl.name, "textureSize")) {
							zt_strCat(*s, s_len, ", 0");
						}

						zt_strCat(*s, s_len, ")");
					}
				} break;

				case ztShLangSyntaxNodeType_ValueBool:
				case ztShLangSyntaxNodeType_ValueNumberFloat:
				case ztShLangSyntaxNodeType_ValueNumberInt: {
					zt_strCat(*s, s_len, node->value.value);
				} break;


				case ztShLangSyntaxNodeType_Scope: {
					zt_strCat(*s, s_len, "{\n");
					zt_flink(child, node->first_child) {
						write(child, indent + 1, s, s_len, vars);
					}
					zt_fiz(indent) zt_strCat(*s, s_len, "\t");
					zt_strCat(*s, s_len, "}\n");
					indent = 0;
				} break;

				case ztShLangSyntaxNodeType_ConditionTest: {
					if (!node->condition.is_inline) {
						zt_strCat(*s, s_len, _zt_shaderLangTokenTypeDesc(node->condition.op));
						zt_strCat(*s, s_len, " (");
						write(node->condition.expr, 0, s, s_len, vars);
						zt_strCat(*s, s_len, ")\n");
						write(node->condition.if_true, indent, s, s_len, vars);

						if (node->condition.if_false) {
							zt_strCat(*s, s_len, "else\n");
							write(node->condition.if_false, indent, s, s_len, vars);
						}
						indent = 0;
					}
					else {
						zt_strCat(*s, s_len, "((");
						write(node->condition.expr, 0, s, s_len, vars);
						zt_strCat(*s, s_len, ") ? (");
						write(node->condition.if_true, 0, s, s_len, vars);
						zt_strCat(*s, s_len, ") : (");
						write(node->condition.if_false, 0, s, s_len, vars);
						zt_strCat(*s, s_len, "))");
					}
				} break;

				case ztShLangSyntaxNodeType_Return: {
					if (node->first_child) {
						zt_strCat(*s, s_len, "return ");
						write(node->first_child, 0, s, s_len, vars);
					}
					else {
						zt_strCat(*s, s_len, "return;\n");
					}
				} break;

				case ztShLangSyntaxNodeType_Loop: {
					zt_strCat(*s, s_len, "for (");
					zt_flink(child, node->first_child) {
						if (child->type == ztShLangSyntaxNodeType_Scope) {
							zt_strCat(*s, s_len, ")\n");
							write(child, indent, s, s_len, vars);
						}
						else {
							write(child, 0, s, s_len, vars);

							if (child->next->type != ztShLangSyntaxNodeType_Scope) {
								zt_strCat(*s, s_len, "; ");
							}
						}
					}
					indent = 0;
				} break;

				case ztShLangSyntaxNodeType_ValueEmpty: {
					if (node->value.value && node->value.value[0] == '.') {
						zt_strCat(*s, s_len, node->value.value + 1);
					}
					return;
				}

				case ztShLangSyntaxNodeType_Group: {
					zt_strCat(*s, s_len, "(");
					write(node->first_child, 0, s, s_len, vars);
					zt_strCat(*s, s_len, ")");
				} break;

				case ztShLangSyntaxNodeType_Break: {
					zt_strCat(*s, s_len, "break");
				} break;

				default: {
					zt_assert(false);
				} break;
			}

			if (indent) zt_strCat(*s, s_len, ";\n");
		}

		// ----------------------------------------------
	};

	ztShLangSyntaxNode *program_node = nullptr;
	zt_flink(child, global_node->first_child) {
		if (child->type == ztShLangSyntaxNodeType_ProgramDecl) {
			program_node = child;
			break;
		}
	}
	zt_assert(program_node);

	local::Vars vars = {};

	{	// find variables
		zt_flink(child, global_node->first_child) {
			if (child->type == ztShLangSyntaxNodeType_Structure) {
				zt_flink(chvar, child->first_child) {
					if (zt_strEquals(chvar->variable_decl.qualifier, "position")) {
						vars.v_position = chvar;
					}
					else if (zt_strEquals(chvar->variable_decl.qualifier, "color")) {
						vars.f_color = chvar;
					}
				}
			}
		}

		zt_assertReturnValOnFail(vars.v_position != nullptr, false);
		//zt_assertReturnValOnFail(vars.f_color != nullptr, false);
	}
	{	// vertex shader

		vars.which_shader = local::Shader_Vert;

		ztShLangSyntaxNode *vertex_func_node = nullptr;
		zt_flink(child, program_node->first_child) {
			if (child->type == ztShLangSyntaxNodeType_FunctionDecl) {
				if (zt_strEquals(child->function_decl.returns_name, "vertex_shader")) {
					vertex_func_node = child;
					break;
				}
			}
		}
		zt_assert(vertex_func_node);

		int vs_len = 1024 * 256;
		*vs = zt_stringMake(vs_len, zt_memGetGlobalArena());

//#		if defined(ZT_GLES3)
//		zt_strCat(*vs, vs_len, "#version 300 es\n\n");
//#		elif defined(ZT_GLES2)
#		if defined(ZT_GLES)
		zt_strCat(*vs, vs_len, "#version 100\n\n");
#		else
		zt_strCat(*vs, vs_len, "#version 330 core\n\n");
#endif

		ztShLangSyntaxNode *param_input = nullptr, *param_uniforms = nullptr, *param_output = nullptr;
		zt_flink(child, vertex_func_node->first_child) {
			if (child->type == ztShLangSyntaxNodeType_VariableDecl) {
				if (zt_strEquals(child->variable_decl.qualifier, "input")) { param_input = child; }
				else if (zt_strEquals(child->variable_decl.qualifier, "uniforms")) { param_uniforms = child; }
				else if (zt_strEquals(child->variable_decl.qualifier, "output")) { param_output = child; }
			}
		}
		zt_assert(param_input && param_uniforms && param_output);

		ztShLangSyntaxNode *struct_input = _zt_shaderLangFindStructure(global_node, param_input->variable_decl.type_name);
		ztShLangSyntaxNode *struct_uniforms = _zt_shaderLangFindStructure(global_node, param_uniforms->variable_decl.type_name);
		ztShLangSyntaxNode *struct_output = _zt_shaderLangFindStructure(global_node, param_output->variable_decl.type_name);
		zt_assert(struct_input && struct_uniforms && struct_output);

		vars.struct_uniform = struct_uniforms;
		vars.struct_input = struct_input;
		vars.var_input = param_input;
		vars.struct_output = struct_output;
		vars.v_output = param_output;

		{	// write the location variables

#			if !defined(ZT_GLES)
			int child_count = 0;
#			endif
			zt_flink(child, struct_input->first_child) {
#				if !defined(ZT_GLES)
				i32 index = child->variable_decl.qualifier ? zt_strToInt(child->variable_decl.qualifier, -1) : child_count;
				zt_assert(index >= 0);

				zt_strMakePrintf(vvar, 256, "layout (location = %d) in %s %s%s;\n", index, local::dataType(child->variable_decl.type_name), vv_prefix, child->variable_decl.name);
#				else
				zt_strMakePrintf(vvar, 256, "attribute %s %s%s;\n", local::dataType(child->variable_decl.type_name), vv_prefix, child->variable_decl.name);
#				endif
				zt_strCat(*vs, vs_len, vvar);
			}
			zt_strCat(*vs, vs_len, "\n");
		}

		{	// write the structures

			ztShLangSyntaxNode *ignore[] = {
				struct_input, struct_uniforms,
			};

			local::writeStructs(global_node, vertex_func_node, ignore, zt_elementsOf(ignore), vs, vs_len, &vars);
		}

		{	// write the uniforms

			zt_flink(child, struct_uniforms->first_child) {
				if (_zt_shaderLangIsVariableReferenced(vertex_func_node, child)) {
					//					zt_strMakePrintf(st_uni, 256, "uniform %s %s;\n", local::dataType(child->variable_decl.type_name), child->variable_decl.name);
					//					zt_strCat(*vs, vs_len, st_uni);
					zt_strCat(*vs, vs_len, "uniform ");
					local::writeVariableDecl(child, vs, vs_len, &vars);
					zt_strCat(*vs, vs_len, ";\n");
				}
			}
			zt_strCat(*vs, vs_len, "\n");
		}

		{ // write the functions
			local::writeFunctions(global_node, vertex_func_node, vs, vs_len, &vars);
		}

		{	// write the vertex function

			zt_strCat(*vs, vs_len, "void main()\n{\n");

			zt_flink(child, vertex_func_node->first_child) {
				if (child->type == ztShLangSyntaxNodeType_Scope) {
					zt_flink(command, child->first_child) {
						local::write(command, 1, vs, vs_len, &vars);
					}
					break;
				}
			}

			zt_strCat(*vs, vs_len, "\tgl_Position = ");
#			if defined(ZT_GLES)
			zt_strCat(*vs, vs_len, "_zt_varying_");
#			else
			zt_strCat(*vs, vs_len, param_output->variable_decl.name);
			zt_strCat(*vs, vs_len, ".");
#			endif
			zt_strCat(*vs, vs_len, vars.v_position->variable_decl.name);
			zt_strCat(*vs, vs_len, ";\n");

			zt_strCat(*vs, vs_len, "}\n");
		}
	}

	{	// fragment shader

		vars.which_shader = local::Shader_Frag;

		ztShLangSyntaxNode *fragment_func_node = nullptr;
		zt_flink(child, program_node->first_child) {
			if (child->type == ztShLangSyntaxNodeType_FunctionDecl) {
				if (zt_strEquals(child->function_decl.returns_name, "pixel_shader")) {
					fragment_func_node = child;
					break;
				}
			}
		}
		zt_assert(fragment_func_node);

		int fs_len = 1024 * 256;
		*fs = zt_stringMake(fs_len, zt_memGetGlobalArena());

//#		if defined(ZT_GLES3)
//		zt_strCat(*fs, fs_len, "#version 300 es\n\nout vec4 _ztfs_frag_color;\n\n");
//#		elif defined(ZT_GLES2)
#		if defined(ZT_GLES)
		zt_strCat(*fs, fs_len, "#version 100\nprecision mediump float;\n\n");
#		else
		zt_strCat(*fs, fs_len, "#version 330 core\n\nlayout (location = 0) out vec4 _ztfs_frag_color;\n");
#endif

#		if !defined(ZT_GLES2)
#		else
#		endif

		ztShLangSyntaxNode *param_input = nullptr, *param_uniforms = nullptr, *param_output = nullptr, *param_textures = nullptr;
		zt_flink(child, fragment_func_node->first_child) {
			if (child->type == ztShLangSyntaxNodeType_VariableDecl) {
				if (zt_strEquals(child->variable_decl.qualifier, "input")) { param_input = child; }
				else if (zt_strEquals(child->variable_decl.qualifier, "uniforms")) { param_uniforms = child; }
				else if (zt_strEquals(child->variable_decl.qualifier, "output")) { param_output = child; }
				else if (zt_strEquals(child->variable_decl.qualifier, "textures")) { param_textures = child; }
			}
		}
		zt_assert(param_input && param_uniforms && param_output);

		ztShLangSyntaxNode *struct_input = _zt_shaderLangFindStructure(global_node, param_input->variable_decl.type_name);
		ztShLangSyntaxNode *struct_uniforms = _zt_shaderLangFindStructure(global_node, param_uniforms->variable_decl.type_name);
		ztShLangSyntaxNode *struct_output = _zt_shaderLangFindStructure(global_node, param_output->variable_decl.type_name);
		ztShLangSyntaxNode *struct_textures = param_textures ? _zt_shaderLangFindStructure(global_node, param_textures->variable_decl.type_name) : nullptr;
		zt_assert(struct_input && struct_uniforms && struct_output);

		vars.struct_uniform = struct_uniforms;
		vars.struct_input = struct_input;
		vars.var_input = param_input;
		vars.struct_textures = struct_textures;
		vars.struct_output = struct_output;
		vars.v_position = nullptr;
		vars.v_output = nullptr;
		vars.f_input = param_input;

		if (struct_output) {
			int layout_idx = 1;
			zt_flink(child, struct_output->first_child) {
				if (child->type == ztShLangSyntaxNodeType_VariableDecl && child != vars.f_color) {
					zt_strCatf(*fs, fs_len, "layout (location = %d) out %s _ztfs_frag_%s;\n", layout_idx++, child->variable_decl.type_name, child->variable_decl.name);
				}
			}
		}

		zt_strCat(*fs, fs_len, "\n");

		{	// write the structures

			ztShLangSyntaxNode *ignore[] = {
				struct_uniforms, struct_output, struct_textures,
			};

			local::writeStructs(global_node, fragment_func_node, ignore, zt_elementsOf(ignore), fs, fs_len, &vars);
		}

		{	// write the uniforms

			zt_flink(child, struct_uniforms->first_child) {
				if (_zt_shaderLangIsVariableReferenced(fragment_func_node, child)) {
					//					zt_strMakePrintf(st_uni, 256, "uniform %s %s;\n", local::dataType(child->variable_decl.type_name), child->variable_decl.name);
					//					zt_strCat(*fs, fs_len, st_uni);
					zt_strCat(*fs, fs_len, "uniform ");
					local::writeVariableDecl(child, fs, fs_len, &vars);
					zt_strCat(*fs, fs_len, ";\n");
				}
			}

			if(struct_textures) {
				zt_flink(child, struct_textures->first_child) {
					if (_zt_shaderLangIsVariableReferenced(fragment_func_node, child)) {
						zt_strMakePrintf(st_uni, 256, "uniform %s %s", local::dataType(child->variable_decl.type_name), child->variable_decl.name);
						zt_strCat(*fs, fs_len, st_uni);

						if (child->variable_decl.array_size != -1) {
							zt_strMakePrintf(var_arr, 16, "[%d]", child->variable_decl.array_size);
							zt_strCat(*fs, fs_len, var_arr);
						}
						zt_strCat(*fs, fs_len, ";\n");

#						if defined(ZT_GLES)
						zt_strCatf(*fs, fs_len, "uniform vec2 _zt_size_of_%s;\n", child->variable_decl.name);
#						endif

					}
				}
			}
			zt_strCat(*fs, fs_len, "\n");
		}

		{ // write the functions
			local::writeFunctions(global_node, fragment_func_node, fs, fs_len, &vars);
		}

		{	// write the vertex function

			zt_strCat(*fs, fs_len, "void main()\n{\n");

			zt_flink(child, fragment_func_node->first_child) {
				if (child->type == ztShLangSyntaxNodeType_Scope) {
					zt_flink(command, child->first_child) {
						local::write(command, 1, fs, fs_len, &vars);
					}
					break;
				}
			}

			zt_strCat(*fs, fs_len, "}\n");
		}
	}

#	undef vv_prefix

	return true;
}

#endif // __zt_game_h_internal_included__

