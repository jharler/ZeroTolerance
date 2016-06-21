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

	ZT_GAME_NO_ALTF4
		This will disable ALT+F4 closing the window and exiting the game

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
	ztRendererFlags_Fullscreen      = (1<<1),
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

#define _zt_inputKey(inputkey)	__zt_inputKey(inputkey)

#define _zt_input_keysDef \
	_zt_inputKey(ztInputKeys_Invalid),      _zt_inputKey(ztInputKeys_LeftButton),  _zt_inputKey(ztInputKeys_RightButton), _zt_inputKey(ztInputKeys_Cancel), \
	_zt_inputKey(ztInputKeys_MiddleButton), _zt_inputKey(ztInputKeys_XButton1),    _zt_inputKey(ztInputKeys_XButton2),    _zt_inputKey(ztInputKeys_Back), \
	_zt_inputKey(ztInputKeys_Tab),          _zt_inputKey(ztInputKeys_Clear),       _zt_inputKey(ztInputKeys_Return),      _zt_inputKey(ztInputKeys_Shift), \
	_zt_inputKey(ztInputKeys_Control),      _zt_inputKey(ztInputKeys_Menu),        _zt_inputKey(ztInputKeys_Pause),       _zt_inputKey(ztInputKeys_Capital), \
	_zt_inputKey(ztInputKeys_Kana),         _zt_inputKey(ztInputKeys_Hangul),      _zt_inputKey(ztInputKeys_Junja),       _zt_inputKey(ztInputKeys_Final), \
	_zt_inputKey(ztInputKeys_Hanja),        _zt_inputKey(ztInputKeys_Kanji),       _zt_inputKey(ztInputKeys_Escape),      _zt_inputKey(ztInputKeys_Convert), \
	_zt_inputKey(ztInputKeys_Nonconvert),   _zt_inputKey(ztInputKeys_Accept),      _zt_inputKey(ztInputKeys_ModeChange),  _zt_inputKey(ztInputKeys_Space), \
	_zt_inputKey(ztInputKeys_Prior),        _zt_inputKey(ztInputKeys_Next),        _zt_inputKey(ztInputKeys_End),         _zt_inputKey(ztInputKeys_Home), \
	_zt_inputKey(ztInputKeys_Left),         _zt_inputKey(ztInputKeys_Up),          _zt_inputKey(ztInputKeys_Right),       _zt_inputKey(ztInputKeys_Down), \
	_zt_inputKey(ztInputKeys_Select),       _zt_inputKey(ztInputKeys_Print),       _zt_inputKey(ztInputKeys_Execute),     _zt_inputKey(ztInputKeys_Snapshot), \
	_zt_inputKey(ztInputKeys_Insert),       _zt_inputKey(ztInputKeys_Delete),      _zt_inputKey(ztInputKeys_Help), \
	\
	_zt_inputKey(ztInputKeys_0), _zt_inputKey(ztInputKeys_1), _zt_inputKey(ztInputKeys_2), _zt_inputKey(ztInputKeys_3), _zt_inputKey(ztInputKeys_4), \
	_zt_inputKey(ztInputKeys_5), _zt_inputKey(ztInputKeys_6), _zt_inputKey(ztInputKeys_7), _zt_inputKey(ztInputKeys_8), _zt_inputKey(ztInputKeys_9), \
	_zt_inputKey(ztInputKeys_A), _zt_inputKey(ztInputKeys_B), _zt_inputKey(ztInputKeys_C), _zt_inputKey(ztInputKeys_D), _zt_inputKey(ztInputKeys_E), \
	_zt_inputKey(ztInputKeys_F), _zt_inputKey(ztInputKeys_G), _zt_inputKey(ztInputKeys_H), _zt_inputKey(ztInputKeys_I), _zt_inputKey(ztInputKeys_J), \
	_zt_inputKey(ztInputKeys_K), _zt_inputKey(ztInputKeys_L), _zt_inputKey(ztInputKeys_M), _zt_inputKey(ztInputKeys_N), _zt_inputKey(ztInputKeys_O), \
	_zt_inputKey(ztInputKeys_P), _zt_inputKey(ztInputKeys_Q), _zt_inputKey(ztInputKeys_R), _zt_inputKey(ztInputKeys_S), _zt_inputKey(ztInputKeys_T), \
	_zt_inputKey(ztInputKeys_U), _zt_inputKey(ztInputKeys_V), _zt_inputKey(ztInputKeys_W), _zt_inputKey(ztInputKeys_X), _zt_inputKey(ztInputKeys_Y), \
	_zt_inputKey(ztInputKeys_Z), \
	\
	_zt_inputKey(ztInputKeys_LeftWin),   _zt_inputKey(ztInputKeys_RightWin),  _zt_inputKey(ztInputKeys_Apps),     _zt_inputKey(ztInputKeys_Sleep), \
	_zt_inputKey(ztInputKeys_Numpad0),   _zt_inputKey(ztInputKeys_Numpad1),   _zt_inputKey(ztInputKeys_Numpad2),  _zt_inputKey(ztInputKeys_Numpad3), \
	_zt_inputKey(ztInputKeys_Numpad4),   _zt_inputKey(ztInputKeys_Numpad5),   _zt_inputKey(ztInputKeys_Numpad6),  _zt_inputKey(ztInputKeys_Numpad7), \
	_zt_inputKey(ztInputKeys_Numpad8),   _zt_inputKey(ztInputKeys_Numpad9),   _zt_inputKey(ztInputKeys_Multiply), _zt_inputKey(ztInputKeys_Add), \
	_zt_inputKey(ztInputKeys_Separator), _zt_inputKey(ztInputKeys_Substract), _zt_inputKey(ztInputKeys_Decimal),  _zt_inputKey(ztInputKeys_Divide), \
	\
	_zt_inputKey(ztInputKeys_F1),  _zt_inputKey(ztInputKeys_F2),  _zt_inputKey(ztInputKeys_F3),  _zt_inputKey(ztInputKeys_F4), \
	_zt_inputKey(ztInputKeys_F5),  _zt_inputKey(ztInputKeys_F6),  _zt_inputKey(ztInputKeys_F7),  _zt_inputKey(ztInputKeys_F8), \
	_zt_inputKey(ztInputKeys_F9),  _zt_inputKey(ztInputKeys_F10), _zt_inputKey(ztInputKeys_F11), _zt_inputKey(ztInputKeys_F12), \
	_zt_inputKey(ztInputKeys_F13), _zt_inputKey(ztInputKeys_F14), _zt_inputKey(ztInputKeys_F15), _zt_inputKey(ztInputKeys_F16), \
	_zt_inputKey(ztInputKeys_F17), _zt_inputKey(ztInputKeys_F18), _zt_inputKey(ztInputKeys_F19), _zt_inputKey(ztInputKeys_F20), \
	_zt_inputKey(ztInputKeys_F21), _zt_inputKey(ztInputKeys_F22), _zt_inputKey(ztInputKeys_F23), _zt_inputKey(ztInputKeys_F24), \
	\
	_zt_inputKey(ztInputKeys_NumLock),       _zt_inputKey(ztInputKeys_Scroll),           _zt_inputKey(ztInputKeys_LeftShift),      _zt_inputKey(ztInputKeys_RightShift), \
	_zt_inputKey(ztInputKeys_LeftControl),   _zt_inputKey(ztInputKeys_RightControl),     _zt_inputKey(ztInputKeys_LeftMenu),       _zt_inputKey(ztInputKeys_RightMenu), \
	_zt_inputKey(ztInputKeys_BrowserBack),   _zt_inputKey(ztInputKeys_BrowserForward),   _zt_inputKey(ztInputKeys_BrowserRefresh), _zt_inputKey(ztInputKeys_BrowserStop), \
	_zt_inputKey(ztInputKeys_BrowserSearch), _zt_inputKey(ztInputKeys_BrowserFavorites), _zt_inputKey(ztInputKeys_BrowserHome),    _zt_inputKey(ztInputKeys_VolumeMute), \
	_zt_inputKey(ztInputKeys_VolumeDown),    _zt_inputKey(ztInputKeys_VolumeUp),         _zt_inputKey(ztInputKeys_MediaNextTrack), _zt_inputKey(ztInputKeys_MediaPrevTrack), \
	_zt_inputKey(ztInputKeys_MediaStop),     _zt_inputKey(ztInputKeys_MediaPlayPause),   _zt_inputKey(ztInputKeys_LaunchMail),     _zt_inputKey(ztInputKeys_LaunchMediaSelect), \
	_zt_inputKey(ztInputKeys_LaunchApp1),    _zt_inputKey(ztInputKeys_LaunchApp2),       _zt_inputKey(ztInputKeys_Semicolon),      _zt_inputKey(ztInputKeys_Plus), \
	_zt_inputKey(ztInputKeys_Comma),         _zt_inputKey(ztInputKeys_Minus),            _zt_inputKey(ztInputKeys_Period),         _zt_inputKey(ztInputKeys_ForwardSlash), \
	_zt_inputKey(ztInputKeys_Tilda),         _zt_inputKey(ztInputKeys_OpenBrace),        _zt_inputKey(ztInputKeys_BackSlash),      _zt_inputKey(ztInputKeys_CloseBrace), \
	_zt_inputKey(ztInputKeys_Apos),          _zt_inputKey(ztInputKeys_Oem_8),            _zt_inputKey(ztInputKeys_Oem_102),        _zt_inputKey(ztInputKeys_ProcessKey), \
	_zt_inputKey(ztInputKeys_Packet),        _zt_inputKey(ztInputKeys_Attn),             _zt_inputKey(ztInputKeys_Crsel),          _zt_inputKey(ztInputKeys_Exsel), \
	_zt_inputKey(ztInputKeys_Ereof),         _zt_inputKey(ztInputKeys_Play),             _zt_inputKey(ztInputKeys_Zoom),           _zt_inputKey(ztInputKeys_Pa1), \
	_zt_inputKey(ztInputKeys_OemClear),

#define __zt_inputKey(key)	key

enum ztInputKeys_Enum
{
	_zt_input_keysDef

	ztInputKeys_MAX,
};

#undef _zt_inputKey

enum ztInputKeyFlags_Enum
{
	ztInputKeyFlags_Pressed      = (1<<0),
	ztInputKeyFlags_JustPressed  = (1<<1),
	ztInputKeyFlags_JustReleased = (1<<2),
	ztInputKeyFlags_StateKey     = (1<<3),
};

struct ztInputKeys
{
	ztInputKeys_Enum code;
	i32 flags;

	char *name;
	char display;
	char shift_display;

	i32 platform_mapping;

	bool pressed()      { return zt_bitIsSet(flags, ztInputKeyFlags_Pressed); }
	bool justPressed()  { return zt_bitIsSet(flags, ztInputKeyFlags_JustPressed); }
	bool justReleased() { return zt_bitIsSet(flags, ztInputKeyFlags_JustReleased); }
	bool stateKey()     { return zt_bitIsSet(flags, ztInputKeyFlags_StateKey); }
};

#define ztInputKeyMaxStrokes	16

bool zt_inputThisFrame();
ztInputKeys* zt_inputKeysAccessState(); // not thread safe
void zt_inputKeysCopyState(ztInputKeys input_keys[ztInputKeys_MAX]); // should only be called in main thread
void zt_inputGetKeyStrokes(ztInputKeys_Enum key_strokes[ztInputKeyMaxStrokes]);

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


#define ztInvalidID -1

typedef i32 ztShaderID;

ztShaderID zt_rendererMakeShader(const char *ztshader_file);

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
	zt_openGLSupport(RECT gl_win_screen_area);

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
ztGameSettings _zt_windows_settings[ztMaxWindows];
ztWindowDetails _zt_windows_details[ztMaxWindows];
i32 _zt_windows_settings_count = 0;

#define ztMaxRendererRequests	8
ztRendererRequest _zt_renderer_requests[ztMaxRendererRequests];
i32 _zt_renderer_requests_count = 0;

// ------------------------------------------------------------------------------------------------

ztInternal void (*_zt_rendererSwapBuffers)(ztWindowDetails*);
ztInternal bool (*_zt_rendererSetViewport)(ztWindowDetails*, bool);
ztInternal bool (*_zt_rendererMakeContext)(ztWindowDetails*, i32);
ztInternal bool (*_zt_rendererFreeContext)(ztWindowDetails*);
ztInternal bool (*_zt_rendererToggleFullscreen)(ztWindowDetails*, bool);

ztInternal bool _zt_rendererSetRendererFuncs(ztRenderer_Enum renderer);

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glSetViewport(ztWindowDetails* win_details, bool force);
ztInternal bool _zt_glMakeContext(ztWindowDetails* win_details, i32 renderer_flags);
ztInternal bool _zt_glFreeContext(ztWindowDetails* win_details);
ztInternal void _zt_glSwapBuffers(ztWindowDetails* win_details);
ztInternal bool _zt_glToggleFullscreen(ztWindowDetails* win_details, bool);

ztInternal bool _zt_dxSetViewport(ztWindowDetails* win_details, bool force);
ztInternal bool _zt_dxMakeContext(ztWindowDetails* win_details, i32 renderer_flags);
ztInternal bool _zt_dxFreeContext(ztWindowDetails* win_details);
ztInternal void _zt_dxSwapBuffers(ztWindowDetails* win_details);
ztInternal bool _zt_dxToggleFullscreen(ztWindowDetails* win_details, bool);

bool _zt_winCreateWindow(ztGameSettings* game_settings, ztWindowDetails* window_details);
bool _zt_winCleanupWindow(ztWindowDetails* win_details, ztGameSettings* settings);

// ------------------------------------------------------------------------------------------------

#define _zt_setKeyData(code, name, display, shift_display, mapping) {code, (display == 0 ? ztInputKeyFlags_StateKey : 0), name, display, shift_display, mapping}

ztInternal bool _zt_input_this_frame = false;
ztInternal ztInputKeys_Enum _zt_input_key_strokes[ztInputKeyMaxStrokes];
ztInternal i32 _zt_input_key_strokes_count = 0;

ztInternal i32 _zt_input_keys_mapping[256];
ztInternal ztInputKeys _zt_input_keys[ztInputKeys_MAX] = {
	_zt_setKeyData(ztInputKeys_Invalid,            "Invalid",              0,    0, 0),
	_zt_setKeyData(ztInputKeys_LeftButton,         "LeftButton",           0,    0, VK_LBUTTON),
	_zt_setKeyData(ztInputKeys_RightButton,        "RightButton",          0,    0, VK_RBUTTON),
	_zt_setKeyData(ztInputKeys_Cancel,             "Cancel",               0,    0, VK_CANCEL),
	_zt_setKeyData(ztInputKeys_MiddleButton,       "MiddleButton",         0,    0, VK_MBUTTON),
	_zt_setKeyData(ztInputKeys_XButton1,           "XButton1",             0,    0, VK_XBUTTON1),
	_zt_setKeyData(ztInputKeys_XButton2,           "XButton2",             0,    0, VK_XBUTTON2),
	_zt_setKeyData(ztInputKeys_Back,               "Back",                 0,    0, VK_BACK),
	_zt_setKeyData(ztInputKeys_Tab,                "Tab",               '\t',    0, VK_TAB),
	_zt_setKeyData(ztInputKeys_Clear,              "Clear",                0,    0, VK_CLEAR),
	_zt_setKeyData(ztInputKeys_Return,             "Return",            '\n',    0, VK_RETURN),
	_zt_setKeyData(ztInputKeys_Shift,              "Shift",                0,    0, VK_SHIFT),
	_zt_setKeyData(ztInputKeys_Control,            "Control",              0,    0, VK_CONTROL),
	_zt_setKeyData(ztInputKeys_Menu,               "Menu",                 0,    0, VK_MENU),
	_zt_setKeyData(ztInputKeys_Pause,              "Pause",                0,    0, VK_PAUSE),
	_zt_setKeyData(ztInputKeys_Capital,            "Capital",              0,    0, VK_CAPITAL),
	_zt_setKeyData(ztInputKeys_Kana,               "Kana",                 0,    0, VK_KANA),
	_zt_setKeyData(ztInputKeys_Hangul,             "Hangul",               0,    0, VK_HANGUL),
	_zt_setKeyData(ztInputKeys_Junja,              "Junja",                0,    0, VK_JUNJA),
	_zt_setKeyData(ztInputKeys_Final,              "Final",                0,    0, VK_FINAL),
	_zt_setKeyData(ztInputKeys_Hanja,              "Hanja",                0,    0, VK_HANJA),
	_zt_setKeyData(ztInputKeys_Kanji,              "Kanji",                0,    0, VK_KANJI),
	_zt_setKeyData(ztInputKeys_Escape,             "Escape",               0,    0, VK_ESCAPE),
	_zt_setKeyData(ztInputKeys_Convert,            "Convert",              0,    0, VK_CONVERT),
	_zt_setKeyData(ztInputKeys_Nonconvert,         "Nonconvert",           0,    0, VK_NONCONVERT),
	_zt_setKeyData(ztInputKeys_Accept,             "Accept",               0,    0, VK_ACCEPT),
	_zt_setKeyData(ztInputKeys_ModeChange,         "ModeChange",           0,    0, VK_MODECHANGE),
	_zt_setKeyData(ztInputKeys_Space,              "Space",             ' ',   ' ', VK_SPACE),
	_zt_setKeyData(ztInputKeys_Prior,              "Prior",                0,    0, VK_PRIOR),
	_zt_setKeyData(ztInputKeys_Next,               "Next",                 0,    0, VK_NEXT),
	_zt_setKeyData(ztInputKeys_End,                "End",                  0,    0, VK_END),
	_zt_setKeyData(ztInputKeys_Home,               "Home",                 0,    0, VK_HOME),
	_zt_setKeyData(ztInputKeys_Left,               "Left",                 0,    0, VK_LEFT),
	_zt_setKeyData(ztInputKeys_Up,                 "Up",                   0,    0, VK_UP),
	_zt_setKeyData(ztInputKeys_Right,              "Right",                0,    0, VK_RIGHT),
	_zt_setKeyData(ztInputKeys_Down,               "Down",                 0,    0, VK_RIGHT),
	_zt_setKeyData(ztInputKeys_Select,             "Select",               0,    0, VK_SELECT),
	_zt_setKeyData(ztInputKeys_Print,              "Print",                0,    0, VK_PRINT),
	_zt_setKeyData(ztInputKeys_Execute,            "Execute",              0,    0, VK_EXECUTE),
	_zt_setKeyData(ztInputKeys_Snapshot,           "Snapshot",             0,    0, VK_SNAPSHOT),
	_zt_setKeyData(ztInputKeys_Insert,             "Insert",               0,    0, VK_INSERT),
	_zt_setKeyData(ztInputKeys_Delete,             "Delete",               0,    0, VK_DELETE),
	_zt_setKeyData(ztInputKeys_Help,               "Help",                 0,    0, VK_HELP),
	_zt_setKeyData(ztInputKeys_0,                  "0",                  '0',  ')', '0'),
	_zt_setKeyData(ztInputKeys_1,                  "1",                  '1',  '!', '1'),
	_zt_setKeyData(ztInputKeys_2,                  "2",                  '2',  '@', '2'),
	_zt_setKeyData(ztInputKeys_3,                  "3",                  '3',  '#', '3'),
	_zt_setKeyData(ztInputKeys_4,                  "4",                  '4',  '$', '4'),
	_zt_setKeyData(ztInputKeys_5,                  "5",                  '5',  '%', '5'),
	_zt_setKeyData(ztInputKeys_6,                  "6",                  '6',  '^', '6'),
	_zt_setKeyData(ztInputKeys_7,                  "7",                  '7',  '&', '7'),
	_zt_setKeyData(ztInputKeys_8,                  "8",                  '8',  '*', '8'),
	_zt_setKeyData(ztInputKeys_9,                  "9",                  '9',  '(', '9'),
	_zt_setKeyData(ztInputKeys_A,                  "A",                  'a',  'A', 'A'),
	_zt_setKeyData(ztInputKeys_B,                  "B",                  'b',  'B', 'B'),
	_zt_setKeyData(ztInputKeys_C,                  "C",                  'c',  'C', 'C'),
	_zt_setKeyData(ztInputKeys_D,                  "D",                  'd',  'D', 'D'),
	_zt_setKeyData(ztInputKeys_E,                  "E",                  'e',  'E', 'E'),
	_zt_setKeyData(ztInputKeys_F,                  "F",                  'f',  'F', 'F'),
	_zt_setKeyData(ztInputKeys_G,                  "G",                  'g',  'G', 'G'),
	_zt_setKeyData(ztInputKeys_H,                  "H",                  'h',  'H', 'H'),
	_zt_setKeyData(ztInputKeys_I,                  "I",                  'i',  'I', 'I'),
	_zt_setKeyData(ztInputKeys_J,                  "J",                  'j',  'J', 'J'),
	_zt_setKeyData(ztInputKeys_K,                  "K",                  'k',  'K', 'K'),
	_zt_setKeyData(ztInputKeys_L,                  "L",                  'l',  'L', 'L'),
	_zt_setKeyData(ztInputKeys_M,                  "M",                  'm',  'M', 'M'),
	_zt_setKeyData(ztInputKeys_N,                  "N",                  'n',  'N', 'N'),
	_zt_setKeyData(ztInputKeys_O,                  "O",                  'o',  'O', 'O'),
	_zt_setKeyData(ztInputKeys_P,                  "P",                  'p',  'P', 'P'),
	_zt_setKeyData(ztInputKeys_Q,                  "Q",                  'q',  'Q', 'Q'),
	_zt_setKeyData(ztInputKeys_R,                  "R",                  'r',  'R', 'R'),
	_zt_setKeyData(ztInputKeys_S,                  "S",                  's',  'S', 'S'),
	_zt_setKeyData(ztInputKeys_T,                  "T",                  't',  'T', 'T'),
	_zt_setKeyData(ztInputKeys_U,                  "U",                  'u',  'U', 'U'),
	_zt_setKeyData(ztInputKeys_V,                  "V",                  'v',  'V', 'V'),
	_zt_setKeyData(ztInputKeys_W,                  "W",                  'w',  'W', 'W'),
	_zt_setKeyData(ztInputKeys_X,                  "X",                  'x',  'X', 'X'),
	_zt_setKeyData(ztInputKeys_Y,                  "Y",                  'y',  'Y', 'Y'),
	_zt_setKeyData(ztInputKeys_Z,                  "Z",                  'z',  'Z', 'Z'),
	_zt_setKeyData(ztInputKeys_LeftWin,            "LeftWin",              0,    0, VK_LWIN),
	_zt_setKeyData(ztInputKeys_RightWin,           "RightWin",             0,    0, VK_RWIN),
	_zt_setKeyData(ztInputKeys_Apps,               "Apps",                 0,    0, VK_APPS),
	_zt_setKeyData(ztInputKeys_Sleep,              "Sleep",                0,    0, VK_SLEEP),
	_zt_setKeyData(ztInputKeys_Numpad0,            "Numpad0",            '0',    0, VK_NUMPAD0),
	_zt_setKeyData(ztInputKeys_Numpad1,            "Numpad1",            '1',    0, VK_NUMPAD1),
	_zt_setKeyData(ztInputKeys_Numpad2,            "Numpad2",            '2',    0, VK_NUMPAD2),
	_zt_setKeyData(ztInputKeys_Numpad3,            "Numpad3",            '3',    0, VK_NUMPAD3),
	_zt_setKeyData(ztInputKeys_Numpad4,            "Numpad4",            '4',    0, VK_NUMPAD4),
	_zt_setKeyData(ztInputKeys_Numpad5,            "Numpad5",            '5',    0, VK_NUMPAD5),
	_zt_setKeyData(ztInputKeys_Numpad6,            "Numpad6",            '6',    0, VK_NUMPAD6),
	_zt_setKeyData(ztInputKeys_Numpad7,            "Numpad7",            '7',    0, VK_NUMPAD7),
	_zt_setKeyData(ztInputKeys_Numpad8,            "Numpad8",            '8',    0, VK_NUMPAD8),
	_zt_setKeyData(ztInputKeys_Numpad9,            "Numpad9",            '9',    0, VK_NUMPAD9),
	_zt_setKeyData(ztInputKeys_Multiply,           "Multiply",           '*',    0, VK_MULTIPLY),
	_zt_setKeyData(ztInputKeys_Add,                "Add",                '+',    0, VK_ADD),
	_zt_setKeyData(ztInputKeys_Separator,          "Separator",            0,    0, VK_SEPARATOR),
	_zt_setKeyData(ztInputKeys_Substract,          "Substract",          '-',    0, VK_SUBTRACT),
	_zt_setKeyData(ztInputKeys_Decimal,            "Decimal",            '.',    0, VK_DECIMAL),
	_zt_setKeyData(ztInputKeys_Divide,             "Divide",             '/',    0, VK_DIVIDE),
	_zt_setKeyData(ztInputKeys_F1,                 "F1",                   0,    0, VK_F1),
	_zt_setKeyData(ztInputKeys_F2,                 "F2",                   0,    0, VK_F2),
	_zt_setKeyData(ztInputKeys_F3,                 "F3",                   0,    0, VK_F3),
	_zt_setKeyData(ztInputKeys_F4,                 "F4",                   0,    0, VK_F4),
	_zt_setKeyData(ztInputKeys_F5,                 "F5",                   0,    0, VK_F5),
	_zt_setKeyData(ztInputKeys_F6,                 "F6",                   0,    0, VK_F6),
	_zt_setKeyData(ztInputKeys_F7,                 "F7",                   0,    0, VK_F7),
	_zt_setKeyData(ztInputKeys_F8,                 "F8",                   0,    0, VK_F8),
	_zt_setKeyData(ztInputKeys_F9,                 "F9",                   0,    0, VK_F9),
	_zt_setKeyData(ztInputKeys_F10,                "F10",                  0,    0, VK_F10),
	_zt_setKeyData(ztInputKeys_F11,                "F11",                  0,    0, VK_F11),
	_zt_setKeyData(ztInputKeys_F12,                "F12",                  0,    0, VK_F12),
	_zt_setKeyData(ztInputKeys_F13,                "F13",                  0,    0, VK_F13),
	_zt_setKeyData(ztInputKeys_F14,                "F14",                  0,    0, VK_F14),
	_zt_setKeyData(ztInputKeys_F15,                "F15",                  0,    0, VK_F15),
	_zt_setKeyData(ztInputKeys_F16,                "F16",                  0,    0, VK_F16),
	_zt_setKeyData(ztInputKeys_F17,                "F17",                  0,    0, VK_F17),
	_zt_setKeyData(ztInputKeys_F18,                "F18",                  0,    0, VK_F18),
	_zt_setKeyData(ztInputKeys_F19,                "F19",                  0,    0, VK_F19),
	_zt_setKeyData(ztInputKeys_F20,                "F20",                  0,    0, VK_F20),
	_zt_setKeyData(ztInputKeys_F21,                "F21",                  0,    0, VK_F21),
	_zt_setKeyData(ztInputKeys_F22,                "F22",                  0,    0, VK_F22),
	_zt_setKeyData(ztInputKeys_F23,                "F23",                  0,    0, VK_F23),
	_zt_setKeyData(ztInputKeys_F24,                "F24",                  0,    0, VK_F24),
	_zt_setKeyData(ztInputKeys_NumLock,            "NumLock",              0,    0, VK_NUMLOCK),
	_zt_setKeyData(ztInputKeys_Scroll,             "Scroll",               0,    0, VK_SCROLL),
	_zt_setKeyData(ztInputKeys_LeftShift,          "LeftShift",            0,    0, VK_LSHIFT),
	_zt_setKeyData(ztInputKeys_RightShift,         "RightShift",           0,    0, VK_RSHIFT),
	_zt_setKeyData(ztInputKeys_LeftControl,        "LeftControl",          0,    0, VK_LCONTROL),
	_zt_setKeyData(ztInputKeys_RightControl,       "RightControl",         0,    0, VK_RCONTROL),
	_zt_setKeyData(ztInputKeys_LeftMenu,           "LeftMenu",             0,    0, VK_LMENU),
	_zt_setKeyData(ztInputKeys_RightMenu,          "RightMenu",            0,    0, VK_RMENU),
	_zt_setKeyData(ztInputKeys_BrowserBack,        "BrowserBack",          0,    0, VK_BROWSER_BACK),
	_zt_setKeyData(ztInputKeys_BrowserForward,     "BrowserForward",       0,    0, VK_BROWSER_FORWARD),
	_zt_setKeyData(ztInputKeys_BrowserRefresh,     "BrowserRefresh",       0,    0, VK_BROWSER_REFRESH),
	_zt_setKeyData(ztInputKeys_BrowserStop,        "BrowserStop",          0,    0, VK_BROWSER_STOP),
	_zt_setKeyData(ztInputKeys_BrowserSearch,      "BrowserSearch",        0,    0, VK_BROWSER_SEARCH),
	_zt_setKeyData(ztInputKeys_BrowserFavorites,   "BrowserFavorites",     0,    0, VK_BROWSER_FAVORITES),
	_zt_setKeyData(ztInputKeys_BrowserHome,        "BrowserHome",          0,    0, VK_BROWSER_HOME),
	_zt_setKeyData(ztInputKeys_VolumeMute,         "VolumeMute",           0,    0, VK_VOLUME_MUTE),
	_zt_setKeyData(ztInputKeys_VolumeDown,         "VolumeDown",           0,    0, VK_VOLUME_DOWN),
	_zt_setKeyData(ztInputKeys_VolumeUp,           "VolumeUp",             0,    0, VK_VOLUME_UP),
	_zt_setKeyData(ztInputKeys_MediaNextTrack,     "MediaNextTrack",       0,    0, VK_MEDIA_NEXT_TRACK),
	_zt_setKeyData(ztInputKeys_MediaPrevTrack,     "MediaPrevTrack",       0,    0, VK_MEDIA_PREV_TRACK),
	_zt_setKeyData(ztInputKeys_MediaStop,          "MediaStop",            0,    0, VK_MEDIA_STOP),
	_zt_setKeyData(ztInputKeys_MediaPlayPause,     "MediaPlayPause",       0,    0, VK_MEDIA_PLAY_PAUSE),
	_zt_setKeyData(ztInputKeys_LaunchMail,         "LaunchMail",           0,    0, VK_LAUNCH_MAIL),
	_zt_setKeyData(ztInputKeys_LaunchMediaSelect,  "LaunchMediaSelect",    0,    0, VK_LAUNCH_MEDIA_SELECT),
	_zt_setKeyData(ztInputKeys_LaunchApp1,         "LaunchApp1",           0,    0, VK_LAUNCH_APP1),
	_zt_setKeyData(ztInputKeys_LaunchApp2,         "LaunchApp2",           0,    0, VK_LAUNCH_APP2),
	_zt_setKeyData(ztInputKeys_Semicolon,          "Semicolon",          ';',  ':', VK_OEM_1),
	_zt_setKeyData(ztInputKeys_Plus,               "Plus",               '=',  '+', VK_OEM_PLUS),
	_zt_setKeyData(ztInputKeys_Comma,              "Comma",              ',',  '<', VK_OEM_COMMA),
	_zt_setKeyData(ztInputKeys_Minus,              "Minus",              '-',  '_', VK_OEM_MINUS),
	_zt_setKeyData(ztInputKeys_Period,             "Period",             '.',  '>', VK_OEM_PERIOD),
	_zt_setKeyData(ztInputKeys_ForwardSlash,       "ForwardSlash",       '/',  '?', VK_OEM_2),
	_zt_setKeyData(ztInputKeys_Tilda,              "Tilda",              '`',  '~', VK_OEM_3),
	_zt_setKeyData(ztInputKeys_OpenBrace,          "OpenBrace",          '[',  '(', VK_OEM_4),
	_zt_setKeyData(ztInputKeys_BackSlash,          "BackSlash",         '\\',  '|', VK_OEM_5),
	_zt_setKeyData(ztInputKeys_CloseBrace,         "CloseBrace",         ']',  '}', VK_OEM_6),
	_zt_setKeyData(ztInputKeys_Apos,               "Apos",              '\'', '\"', VK_OEM_7),
	_zt_setKeyData(ztInputKeys_Oem_8,              "Oem_8",                0,    0, VK_OEM_8),
	_zt_setKeyData(ztInputKeys_Oem_102,            "Oem_102",              0,    0, VK_OEM_102),
	_zt_setKeyData(ztInputKeys_ProcessKey,         "ProcessKey",           0,    0, VK_PROCESSKEY),
	_zt_setKeyData(ztInputKeys_Packet,             "Packet",               0,    0, VK_PACKET),
	_zt_setKeyData(ztInputKeys_Attn,               "Attn",                 0,    0, VK_ATTN),
	_zt_setKeyData(ztInputKeys_Crsel,              "Crsel",                0,    0, VK_CRSEL),
	_zt_setKeyData(ztInputKeys_Exsel,              "Exsel",                0,    0, VK_EXSEL),
	_zt_setKeyData(ztInputKeys_Ereof,              "Ereof",                0,    0, VK_EREOF),
	_zt_setKeyData(ztInputKeys_Play,               "Play",                 0,    0, VK_PLAY),
	_zt_setKeyData(ztInputKeys_Zoom,               "Zoom",                 0,    0, VK_ZOOM),
	_zt_setKeyData(ztInputKeys_Pa1,                "Pa1",                  0,    0, VK_PA1),
	_zt_setKeyData(ztInputKeys_OemClear,           "OemClear",             0,    0, VK_OEM_CLEAR),
};

// ------------------------------------------------------------------------------------------------

bool zt_inputThisFrame()
{
	return _zt_input_this_frame;
}

// ------------------------------------------------------------------------------------------------

ztInputKeys* zt_inputKeysAccessState()
{
	return _zt_input_keys;
}

// ------------------------------------------------------------------------------------------------

void zt_inputKeysCopyState(ztInputKeys input_keys[ztInputKeys_MAX])
{
	int size = sizeof(ztInputKeys) * ztInputKeys_MAX;
	zt_memCpy(input_keys, size, _zt_input_keys, size);
}

// ------------------------------------------------------------------------------------------------

void zt_inputGetKeyStrokes(ztInputKeys_Enum key_strokes[ztInputKeyMaxStrokes])
{
	int size = sizeof(ztInputKeys_Enum) * ztInputKeyMaxStrokes;
	zt_memCpy(key_strokes, size, _zt_input_key_strokes, size);
}

// ------------------------------------------------------------------------------------------------

void _zt_inputClearState()
{
	zt_fiz(ztInputKeys_MAX) {
		zt_bitRemove(_zt_input_keys[i].flags, ztInputKeyFlags_JustPressed);
	}
}

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
	switch(_zt_windows_settings[0].renderer)
	{
		case ztRenderer_OpenGL: {
#if defined(ZT_OPENGL)
			glClearColor(r, g, b, a);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
#endif
		} break;
		case ztRenderer_DirectX: {
#if defined(ZT_DIRECTX)
			auto* win_details = &_zt_windows_details[0];
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
	if(_zt_renderer_requests_count >= zt_elementsOf(_zt_renderer_requests))
		return;

	auto* request = &_zt_renderer_requests[_zt_renderer_requests_count++];
	request->type = ztRendererRequest_Change;
	request->change_to = renderer;
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestWindowed()
{
	if(!zt_bitIsSet(_zt_windows_settings[0].renderer_flags, ztRendererFlags_Fullscreen))
		return;

	if(_zt_renderer_requests_count >= zt_elementsOf(_zt_renderer_requests))
		return;

	auto* request = &_zt_renderer_requests[_zt_renderer_requests_count++];
	request->type = ztRendererRequest_Windowed;
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestFullscreen()
{
	if (zt_bitIsSet(_zt_windows_settings[0].renderer_flags, ztRendererFlags_Fullscreen))
		return;

	if(_zt_windows_settings_count > 1)
		return; // cannot go into fullscreen if there are multiple windows opened

	if(_zt_renderer_requests_count >= zt_elementsOf(_zt_renderer_requests))
		return;

	auto* request = &_zt_renderer_requests[_zt_renderer_requests_count++];
	request->type = ztRendererRequest_Fullscreen;
}

// ------------------------------------------------------------------------------------------------

ztShaderID zt_rendererMakeShader(const char *ztshader_file)
{
	return -1;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_rendererRequestProcess()
{
	int count = _zt_renderer_requests_count;
	_zt_renderer_requests_count = 0;

	zt_fiz(count) {
		auto* request = &_zt_renderer_requests[i];
		switch(request->type)
		{
			case ztRendererRequest_Change: {
				zt_fiz(_zt_windows_settings_count) {
					_zt_rendererFreeContext(&_zt_windows_details[i]);
				}

				if(request->change_to == ztRenderer_OpenGL) {
					zt_logInfo("Switching to OpenGL renderer");
				}
				else if(request->change_to == ztRenderer_DirectX) {
					zt_logInfo("Switching to DirectX renderer");
				}
				else {
					zt_assert(false && "Unknown renderer");
				}

				if(!_zt_rendererSetRendererFuncs(request->change_to)) {
					return false;
				}

				zt_fiz(_zt_windows_settings_count) {
					_zt_windows_settings[i].renderer = request->change_to;
					if(!_zt_rendererMakeContext(&_zt_windows_details[i], _zt_windows_settings[i].renderer_flags)) {
						zt_logCritical("Failed to switch renderer");
						return false;
					}
				}

			} break;

			case ztRendererRequest_Windowed: {
				zt_fiz(_zt_windows_settings_count) {
					zt_bitRemove(_zt_windows_settings[i].renderer_flags, ztRendererFlags_Fullscreen);
					_zt_windows_settings[i].renderer_flags |= ztRendererFlags_Windowed;

					if(!_zt_rendererToggleFullscreen(&_zt_windows_details[i], false))
						return false;
				}
			} break;

			case ztRendererRequest_Fullscreen: {
				zt_fiz(_zt_windows_settings_count) {
					zt_bitRemove(_zt_windows_settings[i].renderer_flags, ztRendererFlags_Windowed);
					_zt_windows_settings[i].renderer_flags |= ztRendererFlags_Fullscreen;

					if(!_zt_rendererToggleFullscreen(&_zt_windows_details[i], true))
						return false;
				}
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
	if (!zt_bitIsSet(renderer_flags, ztRendererFlags_Vsync)) {
		zt_glCallAndReturnValOnError(wglSwapIntervalEXT(0), false);
	}

	if(zt_bitIsSet(renderer_flags, ztRendererFlags_Fullscreen)) {
		//GetWindowRect(win_details->handle, &win_details->windowed_screen_area);

		LONG dwExStyle = GetWindowLong(win_details->handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(win_details->handle, GWL_STYLE);

		dwExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		dwStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

		SetWindowLong(win_details->handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(win_details->handle, GWL_STYLE, dwStyle);

		int screen_x = GetSystemMetrics(SM_CXSCREEN);
		int screen_y = GetSystemMetrics(SM_CYSCREEN);

		SetWindowPos(win_details->handle, 0, 0, 0, screen_x, screen_y, SWP_NOZORDER | SWP_FRAMECHANGED);
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
#if defined(ZT_OPENGL)
	SwapBuffers(win_details->gl_hdc);
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_glToggleFullscreen(ztWindowDetails* win_details, bool fullscreen)
{
#if defined(ZT_OPENGL)
	if(fullscreen) {
		GetWindowRect(win_details->handle, &win_details->gl_win_screen_area);

		LONG dwExStyle = GetWindowLong(win_details->handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(win_details->handle, GWL_STYLE);

		dwExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		dwStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);

		SetWindowLong(win_details->handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(win_details->handle, GWL_STYLE, dwStyle);

		int screen_x = GetSystemMetrics(SM_CXSCREEN);
		int screen_y = GetSystemMetrics(SM_CYSCREEN);

		SetWindowPos(win_details->handle, 0, 0, 0, screen_x, screen_y, SWP_NOZORDER | SWP_FRAMECHANGED);
	}
	else {
		LONG dwExStyle = GetWindowLong(win_details->handle, GWL_EXSTYLE);
		LONG dwStyle = GetWindowLong(win_details->handle, GWL_STYLE);

		dwExStyle |= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle |= WS_OVERLAPPEDWINDOW;

		SetWindowLong(win_details->handle, GWL_EXSTYLE, dwExStyle);
		SetWindowLong(win_details->handle, GWL_STYLE, dwStyle);

		SetWindowPos(win_details->handle, HWND_TOP, 
			win_details->gl_win_screen_area.left, win_details->gl_win_screen_area.top, 
			win_details->gl_win_screen_area.right - win_details->gl_win_screen_area.left, 
			win_details->gl_win_screen_area.bottom - win_details->gl_win_screen_area.top, SWP_FRAMECHANGED);	
	}

	_zt_glSetViewport(win_details, true);
	return true;
#else
	return false;
#endif
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

ztInternal bool _zt_dxToggleFullscreen(ztWindowDetails* win_details, bool fullscreen)
{
#if defined(ZT_DIRECTX)
	win_details->dx_swapchain->SetFullscreenState(fullscreen ? TRUE : FALSE, NULL);
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_rendererSetRendererFuncs(ztRenderer_Enum renderer)
{
	if(renderer == ztRenderer_OpenGL) {
		_zt_rendererSwapBuffers      = _zt_glSwapBuffers;
		_zt_rendererSetViewport      = _zt_glSetViewport;
		_zt_rendererMakeContext      = _zt_glMakeContext;
		_zt_rendererFreeContext      = _zt_glFreeContext;
		_zt_rendererToggleFullscreen = _zt_glToggleFullscreen;
	}
	else if(renderer == ztRenderer_DirectX) {
		_zt_rendererSwapBuffers      = _zt_dxSwapBuffers;
		_zt_rendererSetViewport      = _zt_dxSetViewport;
		_zt_rendererMakeContext      = _zt_dxMakeContext;
		_zt_rendererFreeContext      = _zt_dxFreeContext;
		_zt_rendererToggleFullscreen = _zt_glToggleFullscreen;
	}
	else {
		return false;
	}

	return true;
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
#if defined(ZT_UNICODE)
	u16 wc_game_name[1024] = { 0 };
	zt_strConvertToUTF16(ZT_GAME_NAME, zt_strLen(ZT_GAME_NAME), wc_game_name, zt_elementsOf(wc_game_name));
	wndcls.lpszClassName = (LPCWSTR)wc_game_name;
#else
	wndcls.lpszClassName = ZT_GAME_NAME;
#endif

	static bool first_call = true;
	if(first_call) {
		if(!RegisterClass(&wndcls)) {
			zt_logCritical("win: failed to create window class");
			return false;
		}
		first_call = false;
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

#if defined(ZT_UNICODE)
	window_details->handle = CreateWindow(wndcls.lpszClassName, (LPCWSTR)wc_game_name, style, pos_x, pos_y, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, NULL, NULL, wndcls.hInstance, 0);
#else
	window_details->handle = CreateWindow(wndcls.lpszClassName, ZT_GAME_NAME, style, pos_x, pos_y, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, NULL, NULL, wndcls.hInstance, 0);
#endif
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
	bool context_result = true;
	if(settings->renderer == ztRenderer_OpenGL) {
		context_result = _zt_glFreeContext(win_details);
	}
	else if(settings->renderer == ztRenderer_DirectX) {
		context_result = _zt_dxFreeContext(win_details);
	}
	else {
		context_result = false;
	}

	DestroyWindow(win_details->handle);
	
	return context_result;
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

	for(int i = 0; i < ztInputKeys_MAX; ++i) {
		_zt_input_keys_mapping[_zt_input_keys[i].platform_mapping] = _zt_input_keys[i].code;
	}

	ztGameDetails game_details = {};
	game_details.argc = argc;
	game_details.argv = argv;

	game_details.app_path = app_path;
	game_details.user_path = user_path;

	ztGameSettings *game_settings = &_zt_windows_settings[0];
	_zt_windows_settings_count += 1;

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

	ztWindowDetails *win_details = &_zt_windows_details[0];
	if (!_zt_winCreateWindow(game_settings, win_details))
		return 1;

	if(!_zt_rendererSetRendererFuncs(game_settings->renderer)) {
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

		zt_fiz(_zt_windows_settings_count)
			_zt_rendererSwapBuffers(&_zt_windows_details[i]);

		if(_zt_renderer_requests_count) {
			if(!_zt_rendererRequestProcess())
				break;
		}

		_zt_inputClearState();

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

ztInternal void _zt_winCallbackKeyboard(MSG& msg)
{
	u32 key_code = (uint32)msg.wParam;
	bool is_down = !zt_bitIsSet(msg.lParam, (1<<31));
	bool was_down = zt_bitIsSet(msg.lParam, (1<<30));

	if (was_down != is_down) {
		_zt_input_this_frame = true;

		auto* input_key = &_zt_input_keys[_zt_input_keys_mapping[key_code]];
		
		input_key->flags = input_key->display == 0 ? ztInputKeyFlags_StateKey : 0;

		if(is_down && !was_down) input_key->flags |= ztInputKeyFlags_JustPressed;
		if(!is_down && was_down) input_key->flags |= ztInputKeyFlags_JustReleased;
		if(is_down) input_key->flags |= ztInputKeyFlags_Pressed;

		if( _zt_input_key_strokes_count < zt_elementsOf(_zt_input_key_strokes) ) {
			_zt_input_key_strokes[_zt_input_key_strokes_count++] = input_key->code;
		}

		switch(key_code)
		{
			case VK_F4: {
#if !defined(ZT_GAME_NO_ALTF4)
				if( GetAsyncKeyState(VK_MENU) ) {
					_zt_quit_requested = true;	// ALT+F4 needs to close our game
				}
#endif
			} break;
		}

	}
}

// ------------------------------------------------------------------------------------------------

LRESULT CALLBACK _zt_winCallback(HWND handle, UINT msg, WPARAM w_param, LPARAM l_param)
{
	ztGameSettings *game_settings = nullptr;
	ztWindowDetails *window_details = nullptr;

	zt_fiz(_zt_windows_settings_count) {
		if (_zt_windows_details[i].handle == handle) {
			game_settings = &_zt_windows_settings[i];
			window_details = &_zt_windows_details[i];
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
			_zt_winCallbackKeyboard(smsg);
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
			if(window_details && window_details == &_zt_windows_details[0]) {
				_zt_quit_requested = true;
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