/**************************************************************************************************
 ** file: zt_game.h v 0.00 (active initial development)
 **
 ** This library is in the public domain.  Do with it what you will.  No waranty implied.
 **
 ** There is no guarantee that this code works as intended.  Use it at your own risk.
 **
 **************************************************************************************************
   
    Zero Tolerance Game Library
   
    Single header library collection of powerful and easy to use utilities.  The goal is to be able
    to use this header file to easily create programs with access to a wide variety of useful tools.

	The game library is geared towards containing game-specific utilities.  zt_tools.h is required,
	so this technically isn't a single header library, but all the game stuff is in the single file,
	so I say it counts.  I may embed zt_tools.h at some point once both libraries have matured a bit.
   
    Be sure that #define ZT_GAME_IMPLEMENTATION is used in one cpp file before including this
    header file:

		#define ZT_GAME_IMPLEMENTATION
		#include "zt_game.h"
    
	You must also defined the following

		ZT_GAME_FUNC_SETTINGS
			Called to getting settings required to setup the game.  Only as much work as is
			needed to populate the ztGameSettings structure should be done in this function.
			bool game_settings(ztGameDetails* game_details, ztGameSettings* game_settings)

		ZT_GAME_FUNC_INIT
			Called to initialize the game.
			bool game_init(ztGameDetails* game_details, ztGameSettings* game_settings)

		ZT_GAME_FUNC_CLEANUP
			Called to cleanup resources during shutdown.
			void game_cleanup()

		ZT_GAME_FUNC_LOOP
			Called once per frame.  This takes the time delta since the last frame completed.
			Return false to exit the game.
			bool game_loop(r32 dt)


 **************************************************************************************************

    Options:
		ZT_NO_OPENGL
			Define this in order to disable OpenGL on platforms where it's supported

		ZT_NO_DIRECTX
			Define this in order to disable DirectX on platforms where it's supported

		ZT_OPENGL_DIAGNOSE;
			This will check the error value of every OpenGL call, even those in performance
			critical sections.  This should only be defined when a problem needs diagnosed.


 **************************************************************************************************

	Implimentation Options: (only used with ZT_GAME_IMPLEMENTATION #include)

	ZT_GAME_NAME
		This is used when the game name is needed, such as for naming user data directories.

	ZT_GAME_LOCAL_ONLY
		The user path passed in will be the same directory that the executable lives in instead of
		the typical user data directory (C:\Users\<user>\AppData\Roaming on Windows)

 **************************************************************************************************

	What's with the name "Zero Tolerance?"
		I chose the name because my goal is to have a zero tolerance policy for slow, bloated
		software, slow compile times, and long development time.  I want this library to be
		fast in execution, fast in compile times and fast and easy to use.

	Special Thanks
		This library is inspired by the single file libraries by Sean Barrett.  Inspiration has
		also been drawn from Casey Muratori's Handmade Hero video series as well as Shawn
		McGrath's programming streams.

 **************************************************************************************************/

#ifndef __zt_game_h_included__
#define __zt_game_h_included__

// headers ========================================================================================

#include "zt_tools.h"


// forward declarations ===========================================================================

// types/enums/defines ============================================================================

#if !defined(ZT_NO_OPENGL)
#	if defined(ZT_WINDOWS)
#		define ZT_OPENGL
#		include <gl/GLU.h>
#	endif
#endif

#if !defined(ZT_NO_DIRECTX)
#	if defined(ZT_WINDOWS)
#		define ZT_DIRECTX
#	endif
#endif

// structures/classes =============================================================================

enum ztRenderer_Enum
{
	ztRenderer_OpenGL,
	ztRenderer_DirectX,

	ztRenderer_MAX,
};

// ------------------------------------------------------------------------------------------------

enum ztRendererFlags_Enum
{
	ztRendererFlags_Windowed        = (1<<0),
	ztRendererFlags_FullScreen      = (1<<1),
	ztRendererFlags_Vsync           = (1<<2),
	ztRendererFlags_RotationAllowed = (1<<3), // mobile
	ztRendererFlags_VertOrientation = (1<<4), // mobile
	ztRendererFlags_LockAspect      = (1<<5),
	ztRendererFlags_HideCursor      = (1<<6),
};

// ------------------------------------------------------------------------------------------------

enum ztRendererScreenChangeBehavior_Enum
{
	ztRendererScreenChangeBehavior_Resize,
	ztRendererScreenChangeBehavior_ScaleAll,
	ztRendererScreenChangeBehavior_ScaleToAspect,
};

// ------------------------------------------------------------------------------------------------

struct ztGameSettings
{
	i32 memory; // how much memory should the global arena have?

	i32 screen_w, native_w;
	i32 screen_h, native_h;
	ztRenderer_Enum renderer;
	i32 renderer_target_version_major;
	i32 renderer_target_version_minor;
	i32 renderer_flags;
	ztRendererScreenChangeBehavior_Enum renderer_screen_change_behavior;
};

// ------------------------------------------------------------------------------------------------

struct ztGameDetails
{
	const char* app_path;
	const char* user_path;

	int argc;
	char** argv;
};

// ------------------------------------------------------------------------------------------------


// inlined functions ==============================================================================

// they are inlined below
// ------------------------------------------------------------------------------------------------

// functions ======================================================================================

bool zt_rendererSupported(ztRenderer_Enum renderer);
int zt_rendererSupportedList(ztRenderer_Enum* renderers, int renderers_count);

bool zt_rendererVersionSupported(ztRenderer_Enum renderer, i32 v_major, i32 v_minor);
bool zt_rendererGetMaxVersionSupported(ztRenderer_Enum renderer, i32* v_major, i32* v_minor);

void zt_rendererClear(r32 r, r32 g, r32 b, r32 a);
void zt_rendererClear(ztVec4 clr);

void zt_rendererRequestChange(ztRenderer_Enum renderer);
void zt_rendererRequestWindowed();
void zt_rendererRequestFullscreen();


#if defined(ZT_OPENGL)

// constants we need
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C



// function prototypes we need
#define ZTGL_WINAPI	__stdcall
#define ZTGL_BOOL int

typedef ZTGL_BOOL (ZTGL_WINAPI *ztgl_wglSwapIntervalEXT_Func) (int interval);

bool zt_glCheckAndReportError(const char *function);
i32 zt_glClearErrors();

#define zt_glCallAndReturnOnError(function) function; if(zt_glCheckAndReportError(#function)) return;
#define zt_glCallAndReturnValOnError(function, retval) function; if(zt_glCheckAndReportError(#function)) return retval;
#define zt_glCallAndReportOnError(function) function; zt_glCheckAndReportError(#function);

#if defined(ZT_OPENGL_DIAGNOSE)
#define zt_glCallAndReportOnErrorFast(function) function; zt_glCheckAndReportError(#function);
#else
#define zt_glCallAndReportOnErrorFast(function) function;
#endif


struct ztOpenGL
{
	bool initialized = false;
	ztgl_wglSwapIntervalEXT_Func wglSwapIntervalEXT;
};

extern ztOpenGL zt_gl;

#define wglSwapIntervalEXT zt_gl.wglSwapIntervalEXT


#endif // ZT_OPENGL

#if defined(ZT_DIRECTX)

bool zt_dxCheckAndReportError(const char *function, i32 hr);
i32 zt_dxClearErrors();

#define zt_dxCallAndReturnOnError(function) if(zt_dxCheckAndReportError(#function, (function))) return;
#define zt_dxCallAndReturnValOnError(function, retval) if(zt_dxCheckAndReportError(#function, (function))) return retval;
#define zt_dxCallAndReportOnError(function) zt_dxCheckAndReportError(#function, (function));

#if defined(ZT_OPENGL_DIAGNOSE)
#define zt_dxCallAndReportOnErrorFast(function) zt_dxCheckAndReportError(#function, (function));
#else
#define zt_dxCallAndReportOnErrorFast(function) function;
#endif

#endif


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#if defined(ZT_GAME_IMPLEMENTATION)

#if !defined(ZT_GAME_FUNC_SETTINGS)
#	error "You must define ZT_GAME_FUNC_SETTINGS"
#endif
#if !defined(ZT_GAME_FUNC_INIT)
#	error "You must define ZT_GAME_FUNC_INIT"
#endif
#if !defined(ZT_GAME_FUNC_CLEANUP)
#	error "You must define ZT_GAME_FUNC_CLEANUP"
#endif
#if !defined(ZT_GAME_FUNC_LOOP)
#	error "You must define ZT_GAME_FUNC_LOOP"
#endif

#if defined(ZT_OPENGL)
#define zt_openGLSupport(code) code
#define zt_noOpenGLSupport(code)
#else
#define zt_openGLSupport(code)
#define zt_noOpenGLSupport(code) code
#endif

#if defined(ZT_DIRECTX)
#define zt_directxSupport(code) code
#define zt_noDirectxSupport(code)
#else
#define zt_directxSupport(code)
#define zt_noDirectxSupport(code) code
#endif


#if defined(ZT_WINDOWS)

// headers (strive to avoid including anything if possible)
#include <windows.h>

#if defined(ZT_OPENGL)
#pragma comment(lib, "opengl32.lib")
#include <Wingdi.h>

ztOpenGL zt_gl = {};

#endif

#if defined(ZT_DIRECTX)
#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>

#endif

// ------------------------------------------------------------------------------------------------

struct ztWindowDetails
{
	RECT client_rect;
	RECT window_rect;
	ztVec4 client_rect_buffer;
	HWND handle;

	int screen_w, screen_h;

	zt_openGLSupport(HDC gl_hdc);
	zt_openGLSupport(HGLRC gl_context);

	zt_directxSupport(IDXGISwapChain *dx_swapchain);
	zt_directxSupport(ID3D11Device *dx_device);
	zt_directxSupport(ID3D11DeviceContext *dx_context);
	zt_directxSupport(ID3D11RenderTargetView *dx_backbuffer);
};

// ------------------------------------------------------------------------------------------------

enum ztRendererRequest_Enum
{
	ztRendererRequest_Change,
	ztRendererRequest_Windowed,
	ztRendererRequest_Fullscreen,

	ztRendererRequest_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztRendererRequest
{
	ztRendererRequest_Enum type;

	union {
		struct {
			ztRenderer_Enum change_to;
		};
	};
};

// ------------------------------------------------------------------------------------------------

ztInternal HINSTANCE _zt_hinstance = NULL;
ztInternal bool _zt_quit_requested = false;

#define ztMaxWindows	32
ztGameSettings _zt_windowsSettings[ztMaxWindows];
ztWindowDetails _zt_windowsDetails[ztMaxWindows];
i32 _zt_windowsSettingsCount = 0;

#define ztMaxRendererRequests	8
ztRendererRequest _zt_rendererRequests[ztMaxRendererRequests];
i32 _zt_rendererRequestsCount = 0;

// ------------------------------------------------------------------------------------------------

void (*_zt_rendererSwapBuffers)(ztWindowDetails*);
bool (*_zt_rendererSetViewport)(ztWindowDetails*, bool);
bool (*_zt_rendererMakeContext)(ztWindowDetails*, i32);
bool (*_zt_rendererFreeContext)(ztWindowDetails*);

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glSetViewport(ztWindowDetails* win_details, bool force);
ztInternal bool _zt_glMakeContext(ztWindowDetails* win_details, i32 renderer_flags);
ztInternal bool _zt_glFreeContext(ztWindowDetails* win_details);
ztInternal ztInline void _zt_glSwapBuffers(ztWindowDetails* win_details);

ztInternal bool _zt_dxSetViewport(ztWindowDetails* win_details, bool force);
ztInternal bool _zt_dxMakeContext(ztWindowDetails* win_details, i32 renderer_flags);
ztInternal bool _zt_dxFreeContext(ztWindowDetails* win_details);
ztInternal ztInline void _zt_dxSwapBuffers(ztWindowDetails* win_details);

// ------------------------------------------------------------------------------------------------

bool zt_rendererSupported(ztRenderer_Enum renderer)
{
	switch (renderer)
	{
	case ztRenderer_OpenGL: return zt_openGLSupport(true) zt_noOpenGLSupport(false);
	case ztRenderer_DirectX: return zt_directxSupport(true) zt_noDirectxSupport(false);
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

int zt_rendererSupportedList(ztRenderer_Enum* renderers, int renderers_count)
{
	int idx = 0;
	zt_openGLSupport(if (idx < renderers_count) renderers[idx++] = ztRenderer_OpenGL);
	zt_directxSupport(if (idx < renderers_count) renderers[idx++] = ztRenderer_DirectX);
	return idx;
}

// ------------------------------------------------------------------------------------------------

bool zt_rendererVersionSupported(ztRenderer_Enum renderer, int v_major, int v_minor)
{
	if (renderer == ztRenderer_OpenGL) {
		zt_noOpenGLSupport(return false);

		// TODO(josh): this needs updated to check dlls
		switch (v_major)
		{
			case 4: return v_minor >= 0 && v_minor <= 5;
			case 3: return v_minor >= 0 && v_minor <= 3;
			case 2: return v_minor >= 0 && v_minor <= 1;
			case 1: return v_minor >= 0 && v_minor <= 5;
		}
	}
	else if(renderer == ztRenderer_DirectX) {
		zt_noDirectxSupport(return false);

		if(v_major == 11) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_rendererGetMaxVersionSupported(ztRenderer_Enum renderer, i32* v_major, i32* v_minor)
{
	if (renderer == ztRenderer_OpenGL) {
		zt_noOpenGLSupport(return false);

		// TODO(josh): this needs updated to check dlls
		*v_major = 4;
		*v_minor = 5;
		return true;
	}
	else if (renderer == ztRenderer_DirectX) {
		zt_noDirectxSupport(return false);

		*v_major = 11;
		*v_minor = 0;
	}

	*v_major = *v_minor = 0;

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_rendererClear(r32 r, r32 g, r32 b, r32 a)
{
	switch(_zt_windowsSettings[0].renderer)
	{
		case ztRenderer_OpenGL: {
#if defined(ZT_OPENGL)
			glClearColor(r, g, b, a);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
#endif
		} break;
		case ztRenderer_DirectX: {
#if defined(ZT_DIRECTX)
			auto* win_details = &_zt_windowsDetails[0];
			r32 color[4] = {r, g, b, a};
			win_details->dx_context->ClearRenderTargetView(win_details->dx_backbuffer, color);
#endif
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_rendererClear(ztVec4 clr)
{
	return zt_rendererClear(clr.r, clr.g, clr.b, clr.a);
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestChange(ztRenderer_Enum renderer)
{
	auto* request = &_zt_rendererRequests[_zt_rendererRequestsCount++];
	request->type = ztRendererRequest_Change;
	request->change_to = renderer;
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestWindowed()
{
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestFullscreen()
{
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_rendererRequestProcess()
{
	int count = _zt_rendererRequestsCount;
	_zt_rendererRequestsCount = 0;

	zt_fiz(count) {
		auto* request = &_zt_rendererRequests[i];
		switch(request->type)
		{
			case ztRendererRequest_Change: {
				zt_fiz(_zt_windowsSettingsCount) {
					_zt_rendererFreeContext(&_zt_windowsDetails[i]);
				}

				if(request->change_to == ztRenderer_OpenGL) {
					zt_logInfo("Switching to OpenGL renderer");
					_zt_rendererSwapBuffers = _zt_glSwapBuffers;
					_zt_rendererSetViewport = _zt_glSetViewport;
					_zt_rendererMakeContext = _zt_glMakeContext;
					_zt_rendererFreeContext = _zt_glFreeContext;
				}
				else if(request->change_to == ztRenderer_DirectX) {
					zt_logInfo("Switching to DirectX renderer");
					_zt_rendererSwapBuffers = _zt_dxSwapBuffers;
					_zt_rendererSetViewport = _zt_dxSetViewport;
					_zt_rendererMakeContext = _zt_dxMakeContext;
					_zt_rendererFreeContext = _zt_dxFreeContext;
				}
				else {
					zt_assert(false && "Unknown renderer");
				}

				zt_fiz(_zt_windowsSettingsCount) {
					_zt_windowsSettings[i].renderer = request->change_to;
					if(!_zt_rendererMakeContext(&_zt_windowsDetails[i], _zt_windowsSettings[i].renderer_flags)) {
						zt_logCritical("Failed to switch renderer");
						return false;
					}
				}

			} break;

			case ztRendererRequest_Windowed: {
			} break;

			case ztRendererRequest_Fullscreen: {
			} break;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_glCheckAndReportError(const char* function)
{
#if defined(ZT_OPENGL)
	int errors = 0;
	for( GLint error = glGetError(); error != 0 && errors < 10; error = glGetError() ) {
		zt_logCritical("OpenGL: error from function %s: 0x%08x (%d)", function, error, error);
		errors += 1;
	}
	return errors > 0;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_glClearErrors()
{
#if defined(ZT_OPENGL)
	int errors = 0;
	for( GLint error = glGetError(); error != 0 && errors < 10; error = glGetError() )
		++errors;

	return errors;
#else
	return 0;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glSetup()
{
#if defined(ZT_OPENGL)
	if(zt_gl.initialized)
		return true;

	zt_memSet(&zt_gl, sizeof(zt_gl), 0);

#define zt_loadFunc(func)	\
	zt_logDebug("OpenGL: loading function " #func); zt_gl.##func = (ztgl_##func##_Func)wglGetProcAddress((LPCSTR)((const GLubyte*)#func));

#	pragma push_macro("wglSwapIntervalEXT")
#	undef wglSwapIntervalEXT
	zt_loadFunc(wglSwapIntervalEXT);
#	pragma pop_macro("wglSwapIntervalEXT")


#undef zt_loadFunc

	zt_logInfo("OpenGL: version: %s", glGetString(GL_VERSION));
	zt_logInfo("OpenGL: vendor: %s", glGetString(GL_VENDOR));
	zt_logInfo("OpenGL: renderer %s", glGetString(GL_RENDERER));
	zt_logInfo("OpenGL: shader version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	zt_logInfo("OpenGL: extensions %s", glGetString(GL_EXTENSIONS));

	zt_gl.initialized = true;

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glSetViewport(ztWindowDetails* win_details, bool force)
{
#if defined(ZT_OPENGL)
	if (win_details->gl_hdc == NULL) {
		return false; // we have not initialized opengl yet
	}

	int w = win_details->client_rect.right - win_details->client_rect.left;
	int h = win_details->client_rect.bottom - win_details->client_rect.top;

	if (!force && w == win_details->screen_w && h == win_details->screen_h) {
		return true;
	}

	r32 realw = w / (r32)h;
	r32 realh = h / (r32)h;
	
	struct local
	{
		static bool opengl_calls(int w, int h, r32 realw, r32 realh)
		{
			zt_glCallAndReturnValOnError(glViewport(0, 0, w, h), false); // Sets up clipping
			zt_glCallAndReturnValOnError(glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ), false);
			zt_glCallAndReturnValOnError(glMatrixMode(GL_PROJECTION), false);
			zt_glCallAndReturnValOnError(glLoadIdentity(), false);
			zt_glCallAndReturnValOnError(glOrtho(-realw, realw, -realh, realh, 0.0, 1.0), false);
			zt_glCallAndReturnValOnError(glEnable(GL_TEXTURE_2D), false);
			zt_glCallAndReturnValOnError(glEnable(GL_BLEND), false);
			zt_glCallAndReturnValOnError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);
			return true;
		}
	};

	zt_glClearErrors(); // make sure previously failed calls don't make the app exit
	if( !local::opengl_calls(w, h, realw, realh) ) {
		return false;
	}

	win_details->screen_w = w;
	win_details->screen_h = h;

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glMakeContext(ztWindowDetails* win_details, i32 renderer_flags)
{
#if defined(ZT_OPENGL)
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
	win_details->gl_hdc = GetDC(win_details->handle);
	zt_logDebug("OpenGL: setting pixel format");
	if(FALSE == SetPixelFormat(win_details->gl_hdc, ChoosePixelFormat(win_details->gl_hdc, &pfd), &pfd)) {
		zt_logCritical("OpenGL: SetPixelFormat failed");
		return false;
	}

	zt_logDebug("OpenGL: creating OpenGL context");
	win_details->gl_context = wglCreateContext(win_details->gl_hdc);
	if(win_details->gl_context == NULL) {
		zt_logCritical("OpenGL: wglCreateContext failed");
		return false;
	}

	zt_logDebug("OpenGL: setting context to current");
	wglMakeCurrent(win_details->gl_hdc, win_details->gl_context);
	if(zt_glCheckAndReportError("wglMakeCurrent"))
		return false;

	if(!_zt_glSetup())
		return false;

	glEnable(GL_CULL_FACE); // NOTE(josh): should this be here?

	// this turns off wait for vsync:
	if( !zt_bitIsSet(renderer_flags, ztRendererFlags_Vsync) ) {
		zt_glCallAndReturnValOnError(wglSwapIntervalEXT(0), false);
	}

	zt_logDebug("OpenGL: setting viewport");
	if(!_zt_glSetViewport(win_details, true)) {
		return false;
	}

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glFreeContext(ztWindowDetails* win_details)
{
#if defined(ZT_OPENGL)
	if(win_details->gl_context != NULL) {
		wglMakeCurrent(GetDC(win_details->handle), NULL);
		wglDeleteContext(win_details->gl_context);
		ReleaseDC(win_details->handle, win_details->gl_hdc);

		win_details->gl_context = NULL;
		win_details->gl_hdc = NULL;
	}
	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _zt_glSwapBuffers(ztWindowDetails* win_details)
{
	SwapBuffers(win_details->gl_hdc);
}

// ------------------------------------------------------------------------------------------------

bool zt_dxCheckAndReportError(const char *function, i32 hr)
{
#if defined(ZT_DIRECTX)
	switch(hr)
	{
	case S_OK: return false;
	case D3D11_ERROR_FILE_NOT_FOUND                              : zt_logCritical("DirectX: Error: D3D11_ERROR_FILE_NOT_FOUND"); return true;
	case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS               : zt_logCritical("DirectX: Error: D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS"); return true;
	case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS                : zt_logCritical("DirectX: Error: D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS"); return true;
	case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD: zt_logCritical("DirectX: Error: D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD"); return true;
	case DXGI_ERROR_INVALID_CALL                                 : zt_logCritical("DirectX: Error: DXGI_ERROR_INVALID_CALL"); return true;
	case DXGI_ERROR_WAS_STILL_DRAWING                            : zt_logCritical("DirectX: Error: DXGI_ERROR_WAS_STILL_DRAWING"); return true;
	case E_FAIL                                                  : zt_logCritical("DirectX: Error: E_FAIL"); return true;
	case E_INVALIDARG                                            : zt_logCritical("DirectX: Error: E_INVALIDARG"); return true;
	case E_OUTOFMEMORY                                           : zt_logCritical("DirectX: Error: E_OUTOFMEMORY"); return true;
	case E_NOTIMPL                                               : zt_logCritical("DirectX: Error: E_NOTIMPL"); return true;
	case S_FALSE                                                 : zt_logCritical("DirectX: Error: S_FALSE"); return true;
	default: zt_logCritical("DirectX: Unknown error code: 0x%x (%d)", hr, hr); return true;
	}
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

i32 zt_dxClearErrors()
{
	return 0;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_dxSetup()
{
#if defined(ZT_DIRECTX)
	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_dxSetViewport(ztWindowDetails* win_details, bool force)
{
#if defined(ZT_DIRECTX)
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0.f;
	viewport.TopLeftY = 0.f;
	viewport.Width = (r32)win_details->screen_w;
	viewport.Height = (r32)win_details->screen_h;

	win_details->dx_context->RSSetViewports(1, &viewport);

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_dxMakeContext(ztWindowDetails *win_details, i32 renderer_flags)
{
#if defined(ZT_DIRECTX)
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = win_details->handle;                 // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples

	scd.Windowed = zt_bitIsSet(renderer_flags, ztRendererFlags_Windowed) ? TRUE : FALSE;

	D3D_FEATURE_LEVEL feature_level;

	zt_logInfo("DirectX: Creating swap chain");
		// create a device, device context and swap chain using the information in the scd struct
	zt_dxCallAndReturnValOnError(D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&win_details->dx_swapchain,
		&win_details->dx_device,
		&feature_level,
		&win_details->dx_context), false);

	// get the address of the back buffer
	zt_logInfo("DirectX: Finding back buffer address");
	ID3D11Texture2D *backbuffer;
	zt_dxCallAndReturnValOnError(win_details->dx_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer), false);

	// use the back buffer address to create the render target
	zt_logInfo("DirectX: Creating back buffer render target");
	zt_dxCallAndReturnValOnError(win_details->dx_device->CreateRenderTargetView(backbuffer, NULL, &win_details->dx_backbuffer), false);
	backbuffer->Release();

	// set the render target as the back buffer
	zt_logInfo("DirectX: Setting context back buffer");
	win_details->dx_context->OMSetRenderTargets(1, &win_details->dx_backbuffer, NULL);

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_dxFreeContext(ztWindowDetails *win_details)
{
#if defined(ZT_DIRECTX)
	win_details->dx_swapchain->Release();
	win_details->dx_backbuffer->Release();
	win_details->dx_device->Release();
	win_details->dx_context->Release();

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _zt_dxSwapBuffers(ztWindowDetails* win_details)
{
#if defined(ZT_DIRECTX)
	win_details->dx_swapchain->Present(0, 0);
#endif
}

// ------------------------------------------------------------------------------------------------

// the _zt_callFunc<function> calls are used because it's possible for the ZT_GAME_FUNC_<function> defines
// to have naming conflicts with variables in the main function

bool ZT_GAME_FUNC_SETTINGS(ztGameDetails*, ztGameSettings*);
ztInternal ztInline bool _zt_callFuncSettings(ztGameDetails *details, ztGameSettings *settings)
{ return ZT_GAME_FUNC_SETTINGS(details, settings); }

bool ZT_GAME_FUNC_INIT(ztGameDetails*, ztGameSettings*);
ztInternal ztInline bool _zt_callFuncInit(ztGameDetails *details, ztGameSettings *settings)
{ return ZT_GAME_FUNC_INIT(details, settings); }

void ZT_GAME_FUNC_CLEANUP();
ztInternal ztInline void _zt_callFuncCleanup()
{ return ZT_GAME_FUNC_CLEANUP(); }

bool ZT_GAME_FUNC_LOOP(r32);
ztInternal ztInline bool _zt_callFuncLoop(r32 dt)
{ return ZT_GAME_FUNC_LOOP(dt); }


LRESULT CALLBACK _zt_winCallback(HWND handle, UINT msg, WPARAM w_param, LPARAM l_param);

// ------------------------------------------------------------------------------------------------

bool _zt_winCreateWindow(ztGameSettings* game_settings, ztWindowDetails* window_details)
{
	WNDCLASS wndcls = {};
	wndcls.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndcls.lpfnWndProc = _zt_winCallback;
	wndcls.hInstance = _zt_hinstance;
	wndcls.lpszClassName = ZT_GAME_NAME;

	if (!RegisterClass(&wndcls)) {
		zt_logCritical("win: failed to create window class");
		return false;
	}

	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT client_rect = { 0, 0, game_settings->native_w, game_settings->native_h };
	if (AdjustWindowRect(&client_rect, style, FALSE) == FALSE) {
		zt_logCritical("win: failed to adjust window rect");
	}

	window_details->client_rect_buffer = ztVec4((r32)client_rect.left, (r32)client_rect.top, (r32)client_rect.right - game_settings->native_w, (r32)client_rect.bottom - game_settings->native_h);

	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
	int pos_x = (screen_x - (client_rect.right - client_rect.left)) / 2;
	int pos_y = (screen_y - (client_rect.bottom - client_rect.top)) / 2;

	window_details->handle = CreateWindow(wndcls.lpszClassName, ZT_GAME_NAME, style, pos_x, pos_y, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, NULL, NULL, wndcls.hInstance, 0);

	if (window_details->handle == NULL) {
		zt_logCritical("win: failed to create window");
		return false;
	}

	GetClientRect(window_details->handle, &window_details->client_rect);
	GetWindowRect(window_details->handle, &window_details->window_rect);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool _zt_winCleanupWindow(ztWindowDetails* win_details, ztGameSettings* settings)
{
	if(settings->renderer == ztRenderer_OpenGL) {
		return _zt_glFreeContext(win_details);
	}
	else {
		return false;
	}
}

// ------------------------------------------------------------------------------------------------

void _zt_win_processMessages()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT) {
		_zt_quit_requested = false;
	}
}

// ------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	char app_path[ztFileMaxPath] = {0};
	zt_fileGetAppPath(app_path, sizeof(app_path));

	char user_path[ztFileMaxPath] = {0};

#if defined(ZT_GAME_LOCAL_ONLY)
	zt_fileGetCurrentPath(user_path, sizeof(user_path));
#else
	zt_fileGetUserPath(user_path, sizeof(user_path), ZT_GAME_NAME);
#endif

	ztGameDetails game_details = {};
	game_details.argc = argc;
	game_details.argv = argv;

	game_details.app_path = app_path;
	game_details.user_path = user_path;

	ztGameSettings *game_settings = &_zt_windowsSettings[0];
	_zt_windowsSettingsCount += 1;

	game_settings->memory = zt_megabytes(64);
	game_settings->native_w = game_settings->screen_w = 1280;
	game_settings->native_h = game_settings->screen_h = 720;

	game_settings->renderer = ztRenderer_OpenGL;
	game_settings->renderer_flags = ztRendererFlags_Windowed | ztRendererFlags_LockAspect;
	game_settings->renderer_screen_change_behavior = ztRendererScreenChangeBehavior_Resize;

	if (!_zt_callFuncSettings(&game_details, game_settings))
		return 1;

	zt_logDebug("main: app path: %s", game_details.app_path);
	zt_logDebug("main: user path: %s", game_details.user_path);

	ztWindowDetails *win_details = &_zt_windowsDetails[0];
	if (!_zt_winCreateWindow(game_settings, win_details))
		return 1;

	if(game_settings->renderer == ztRenderer_OpenGL) {
		_zt_rendererSwapBuffers = _zt_glSwapBuffers;
		_zt_rendererSetViewport = _zt_glSetViewport;
		_zt_rendererMakeContext = _zt_glMakeContext;
		_zt_rendererFreeContext = _zt_glFreeContext;
	}
	else if(game_settings->renderer == ztRenderer_DirectX) {
		_zt_rendererSwapBuffers = _zt_dxSwapBuffers;
		_zt_rendererSetViewport = _zt_dxSetViewport;
		_zt_rendererMakeContext = _zt_dxMakeContext;
		_zt_rendererFreeContext = _zt_dxFreeContext;
	}
	else {
		zt_logCritical("main: Unknown renderer (%d)", game_settings->renderer);
		return 1;
	}

	if(!_zt_rendererMakeContext(win_details, game_settings->renderer_flags)) {
		zt_logCritical("main: Failed to create OpenGL context on main window");
		return 1;
	}

	char app_memory_str[128];
	zt_strBytesToString(app_memory_str, sizeof(app_memory_str), game_settings->memory);
	zt_logDebug("main: initializing %s of memory", app_memory_str);

	zt_memPushGlobalArena(zt_memMakeArena(game_settings->memory));

	if (!_zt_callFuncInit(&game_details, game_settings))
		return 1;

	r32 dt = 0;
	r32 time_last = zt_getTime();

	do {
		_zt_win_processMessages();

		r32 time_this = zt_getTime();
		dt = time_this - time_last;
		time_last = time_this;

		zt_debugOnly(if(dt > 1.f / 30.f) dt = 1.f / 30.f); // keep the delta time meaningful during debugging

		if(!_zt_callFuncLoop(dt))
			break;

		zt_fiz(_zt_windowsSettingsCount)
			_zt_rendererSwapBuffers(&_zt_windowsDetails[i]);

		if(_zt_rendererRequestsCount) {
			if(!_zt_rendererRequestProcess())
				break;
		}

	} while (!_zt_quit_requested);

	_zt_callFuncCleanup();

	zt_memDumpArena(zt_memGetGlobalArena(), "main memory");
	zt_memFreeArena(zt_memGetGlobalArena());
	zt_memPopGlobalArena();

	return 0;
}

// ------------------------------------------------------------------------------------------------

#if !defined(ZT_PLATFORM_WIN32_CONSOLE) && !defined(ZT_PLATFORM_WIN64_CONSOLE)

int CALLBACK WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR cmd_line, int cmd_show)
{
	_zt_hinstance = h_instance;

	char* argv[128];
	int argc = 0;

	if(cmd_line != nullptr) {
		static char cmd_line_buffer[1024] = {0};
		zt_strCpy(cmd_line_buffer, sizeof(cmd_line_buffer), cmd_line);

		ztToken tokens[128];
		int tokens_count = zt_strTokenize(cmd_line, " ", tokens, zt_elementsOf(tokens));
		zt_assert(tokens_count <= zt_elementsOf(tokens));

		argv[0] = nullptr;
		zt_fiz(tokens_count) {
			argv[i+1] = cmd_line_buffer + tokens[i].beg;
			cmd_line_buffer[tokens[i].beg + tokens[i].len] = 0;
		}
		argc = tokens_count ? tokens_count + 1 : 0;
	}

	return main(argc, argv);
}

#endif // WinMain

// ------------------------------------------------------------------------------------------------

LRESULT CALLBACK _zt_winCallback(HWND handle, UINT msg, WPARAM w_param, LPARAM l_param)
{
	ztGameSettings *game_settings = nullptr;
	ztWindowDetails *window_details = nullptr;

	zt_fiz(_zt_windowsSettingsCount) {
		if (_zt_windowsDetails[i].handle == handle) {
			game_settings = &_zt_windowsSettings[i];
			window_details = &_zt_windowsDetails[i];
			break;
		}
	}

	LRESULT result = 0;

	switch (msg)
	{
		case WM_QUIT: {
			_zt_quit_requested = false;
		} break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP: {
			MSG smsg;
			smsg.message = msg;
			smsg.hwnd = handle;
			smsg.lParam = l_param;
			smsg.wParam = w_param;
			//win32_process_input_keystroke(smsg);
		} break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_MOUSEMOVE: {
			MSG smsg;
			smsg.message = msg;
			smsg.hwnd = handle;
			smsg.lParam = l_param;
			smsg.wParam = w_param;
			//win32_process_input_mouse(smsg);
		} break;

		case WM_DESTROY:
		case WM_CLEAR: {
			_zt_quit_requested = true;
			if(window_details) {
				_zt_winCleanupWindow(window_details, game_settings);
			}
		} break;

		case WM_MOVE:
		case WM_SIZE: {
			if (window_details) {
				_zt_rendererSetViewport(window_details, false);
				GetClientRect(window_details->handle, &window_details->client_rect);
			}
		} break;

		case WM_SIZING: {
			if (game_settings && zt_bitIsSet(game_settings->renderer_flags, ztRendererFlags_LockAspect)) {
				r32 aspect_ratio = game_settings->native_h / (r32)game_settings->native_w;

				RECT size;
				memcpy(&size, (const void*)l_param, sizeof(RECT));

				int width = size.right - size.left;
				int height = size.bottom - size.top;

				switch (w_param)
				{
					case WMSZ_LEFT:
					case WMSZ_RIGHT: {
						size.bottom = zt_convertToi32Floor(width * aspect_ratio) + size.top;
					} break;

					case WMSZ_TOP:
					case WMSZ_BOTTOM: {
						size.right = zt_convertToi32Floor(height * (1 / aspect_ratio)) + size.left;
					} break;

					case WMSZ_TOPRIGHT:
					case WMSZ_TOPLEFT:
					case WMSZ_BOTTOMRIGHT:
					case WMSZ_BOTTOMLEFT: {
						if (height / (real32)width > aspect_ratio)
							width = zt_convertToi32Floor(height / aspect_ratio);
						else
							height = zt_convertToi32Floor(width * aspect_ratio);

						if (w_param == WMSZ_TOPLEFT || w_param == WMSZ_TOPRIGHT)
							size.top = size.bottom - height;
						else
							size.bottom = size.top + height;

						if (w_param == WMSZ_TOPLEFT || w_param == WMSZ_BOTTOMLEFT)
							size.left = size.right - width;
						else
							size.right = size.left + width;
					} break;
				}

				memcpy((void*)l_param, &size, sizeof(RECT));
			}
		} break;

		case WM_PAINT: {
			PAINTSTRUCT ps;
			BeginPaint(handle, &ps);
			EndPaint(handle, &ps);
		} break;

		case WM_SETCURSOR: {
			if (game_settings && zt_bitIsSet(game_settings->renderer_flags, ztRendererFlags_HideCursor) && GetFocus() == handle) {
				//if (g_globals->sys_mouse_relative || LOWORD(l_param) == HTCLIENT) {
				if (LOWORD(l_param) == HTCLIENT) {
					SetCursor(NULL);
					//g_globals->input->mouse.over_window = true;
				}
				else {
					//g_globals->input->mouse.over_window = false;
					SetCursor(LoadCursor(NULL, IDC_ARROW));
				}
			}
			else {
				//g_globals->input->mouse.over_window = false;
				//win32_set_cursor();
				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
		} break;

		case WM_KILLFOCUS: {
			// we need to clear input
			//input_clear_state(g_globals->input, true);
		} break;

		default: {
			result = DefWindowProc(handle, msg, w_param, l_param);
		} break;
	}

	return result;
}

#endif // ZT_WINDOWS

// ------------------------------------------------------------------------------------------------

#endif // ZT_TOOLS_IMPLEMENTATION

#endif // include guard