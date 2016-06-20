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

// structures/classes =============================================================================

enum ztRenderer_Enum
{
	ztRenderer_OpenGL,

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


// headers (strive to avoid including anything if possible)

#if defined(ZT_WINDOWS)

#include <windows.h>


struct ztWindowDetails
{
	RECT client_rect;
	RECT window_rect;
	ztVec4 client_rect_buffer;
	HWND handle;
};


ztInternal HINSTANCE _zt_hinstance = NULL;
ztInternal bool _zt_quit_requested = false;

#define ztMaxWindows	32
ztGameSettings _zt_windowsSettings[ztMaxWindows];
ztWindowDetails _zt_windowsDetails[ztMaxWindows];
i32 _zt_windowsSettingsCount = 0;


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

bool _zt_win_createWindow(ztGameSettings* game_settings, ztWindowDetails* window_details)
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

//	if (!win32_opengl_init()) {
//		return false;
//	}

//	if (!win32_dsound_init()) {
//		return false;	// todo: should eventually just disable audio instead of erroring out
//	}

	return true;
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

	char app_memory_str[128];
	zt_strBytesToString(app_memory_str, sizeof(app_memory_str), game_settings->memory);
	zt_logDebug("main: initializing %s of memory", app_memory_str);

	zt_memPushGlobalArena(zt_memMakeArena(game_settings->memory));

	ztWindowDetails *window_details = &_zt_windowsDetails[0];
	if (!_zt_win_createWindow(game_settings, window_details))
		return 1;

	if (!_zt_callFuncInit(&game_details, game_settings))
		return 1;

	r32 dt = 0;
	r32 time_last = zt_getTime();
	do {
		_zt_win_processMessages();

		r32 time_this = zt_getTime();
		dt = time_this - time_last;
		time_last = time_this;

	} while (_zt_callFuncLoop(dt) && !_zt_quit_requested);

	_zt_callFuncCleanup();

	zt_memDumpArena(zt_memGetGlobalArena(), "main memory");
	zt_memFreeArena(zt_memGetGlobalArena());
	zt_memPopGlobalArena();

	return 0;
}


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
	} break;

	case WM_MOVE:
	case WM_SIZE: {
		//win32_opengl_set_screen_viewport(false);
		//GetClientRect(g_win32_state->window_handle, &g_win32_state->client_rect);
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