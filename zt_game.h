/**************************************************************************************************
 ** file: zt_game.h v 0.00 (active initial development)
 **
 ** This software is dual-licensed to the public domain and under the following
 ** license: you are granted a perpetual, irrevocable license to copy, modify,
 ** publish, and distribute this file as you see fit.
 **
 ** No warranty is offered or implied.  Use this at your own risk.
 **
 **************************************************************************************************
   
	Zero Tolerance Game Library
   
	In exactly one c/cpp source file of your project, you must:

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

		ZT_GAME_FUNC_SCREENCHANGE
			Called whenever the screen resolution changes (usually by user resizing)

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

		ZT_OPENGL_DEBUGGING
			This will check the error value of every OpenGL call, even those in performance
			critical sections.  This should only be defined when a problem needs diagnosed.

		ZT_DIRECTX_DEBUGGING
			This will check the error value of every DirectX call, even those in performance
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

 **************************************************************************************************/

#ifndef __zt_game_h_included__
#define __zt_game_h_included__

#include "zt_tools.h"


// ------------------------------------------------------------------------------------------------
// renderer defines

#if !defined(ZT_NO_OPENGL)
#	include "zt_opengl.h"
#endif

#if !defined(ZT_NO_DIRECTX)
#	include "zt_directx.h"
#endif

#if !defined(ZT_NO_DSOUND)
#	include "zt_dsound.h"
#endif


#define ztInvalidID -1


// ------------------------------------------------------------------------------------------------
// common enumerations

enum ztAlign_Enum
{
	ztAlign_None       = 0,
	ztAlign_Default    = 0,
	ztAlign_Left       = (1<<0),
	ztAlign_Right      = (1<<1),
	ztAlign_Center     = (1<<2),
	ztAlign_Top        = (1<<3),
	ztAlign_Bottom     = (1<<4),
	ztAlign_VertCenter = (1<<5),
};

// ------------------------------------------------------------------------------------------------

enum ztAnchor_Enum
{
	ztAnchor_None       = ztAlign_None,
	ztAnchor_Default    = ztAlign_None,
	ztAnchor_Left       = ztAlign_Left,
	ztAnchor_Right      = ztAlign_Right,
	ztAnchor_Center     = ztAlign_Center,
	ztAnchor_Top        = ztAlign_Top,
	ztAnchor_Bottom     = ztAlign_Bottom,
	ztAnchor_VertCenter = ztAlign_VertCenter,
};

// ------------------------------------------------------------------------------------------------
// renderer enumerations

enum ztRenderer_Enum
{
	ztRenderer_Invalid,

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
	ztRendererScreenChangeBehavior_Resize,		// the viewport and native resolution scales to the window size
	ztRendererScreenChangeBehavior_ScaleAll,	// the viewport scales and distorts to keep the native resolution
	ztRendererScreenChangeBehavior_ScaleToHorz, // the viewport scales to the width of the screen (resizing up/down doesn't affect the size of things)
	ztRendererScreenChangeBehavior_ScaleToVert, // the viewport scales to the height of the screen (resizing left/right doesn't affect the size of things)
};


// ------------------------------------------------------------------------------------------------
// game settings
//
// these are set by the game in the ZT_GAME_FUNC_SETTINGS function, instructing the engine how to 
// configure everything

struct ztGameSettings
{
	i32                                 memory; // how much memory should the global arena have?

	i32                                 screen_w, native_w;
	i32                                 screen_h, native_h;
	ztRenderer_Enum                     renderer;
	i32                                 renderer_target_version_major;
	i32                                 renderer_target_version_minor;
	i32                                 renderer_flags;
	ztRendererScreenChangeBehavior_Enum renderer_screen_change_behavior;
	i32                                 renderer_memory;
	i32                                 pixels_per_unit;

	i32                                 threaded_frame_jobs;
	i32                                 threaded_background_jobs;
};

// ------------------------------------------------------------------------------------------------

ztRenderer_Enum zt_currentRenderer();

r32 zt_pixelsPerUnit();


// ------------------------------------------------------------------------------------------------
// game details
//
// these are set by the engine, providing useful information to the game
//

struct ztGameDetails
{
	const char* app_path;
	const char* user_path;

	int    argc;
	char** argv;

	i32 current_frame;

	struct {
		i32 shader_switches;
		i32 texture_switches;
		i32 triangles_drawn;
		i32 draw_calls;
	} curr_frame, prev_frame;
};


// ------------------------------------------------------------------------------------------------
// threading

typedef i32 ztThreadJobID;

ztThreadJobID zt_threadJobQueueForFrame(ztThread_Func thread_func, void *user_data, r32 anticipated_length = 1); // use for jobs that will complete in the time of a frame
ztThreadJobID zt_threadJobQueueForBackground(ztThread_Func thread_func, void *user_data, r32 anticipated_length = 1); // use for jobs that will take multiple frames to complete

bool          zt_threadJobIsComplete(ztThreadJobID job_id);
void          zt_threadJobCancel(ztThreadJobID job_id);

void          zt_threadJobQueueStartFrameJobs();
void          zt_threadJobQueueWaitForFrameJobs();      // waits until all frame jobs are completed (called after the game loop if jobs are pending)
void          zt_threadJobQueueWaitForBackgroundJobs(); // waits until all background jobs are completed
void          zt_threadJobQueueWaitForAllJobs();        // waits until all jobs are completed

void          zt_threadJobQueueDllLoad();
void          zt_threadJobQueueDllUnload();

int           zt_threadGetIndex();


// ------------------------------------------------------------------------------------------------
// profiling

// ------------------------------------------------------------------------------------------------

struct ztDrawList;
struct ztProfiledSection;

// ------------------------------------------------------------------------------------------------

struct ztProfilerRenderState
{
	int display_frame = -1;
	int display_thread = 0;
};

// ------------------------------------------------------------------------------------------------

#define ZT_SYSTEM_PLATFORM           "Platform"
#define ZT_SYSTEM_RENDERING	         "Rendering"
#define ZT_SYSTEM_AUDIO              "Audio"
#define ZT_SYSTEM_INPUT              "Input"
#define ZT_SYSTEM_ASSETS             "Assets"
#define ZT_SYSTEM_PHYSICS            "Physics"
#define ZT_SYSTEM_ANIMATION          "Animation"
#define ZT_SYSTEM_PARTICLES          "Particles"
#define ZT_SYSTEM_PATHFINDING        "Pathfinding"
#define ZT_SYSTEM_GAME               "Game"


// ------------------------------------------------------------------------------------------------

void               zt_profilerPause              ();
void               zt_profilerResume             ();
bool               zt_profilerIsPaused           ();
void               zt_profilerRender             (ztDrawList *draw_list, const ztVec2& pos, const ztVec2& size, const ztVec2& mouse_pos = ztVec2::min, bool mouse_clicked = false, ztProfilerRenderState *render_state = nullptr);
void               zt_profilerFrameBegin         ();
void               zt_profilerFrameEnd           ();

ztProfiledSection *zt_profiledSectionEnter       (const char *section, i32 section_hash, const char *system, i32 system_hash, int thread_idx = zt_threadGetIndex());
void               zt_profiledSectionExit        (ztProfiledSection *section);


// ------------------------------------------------------------------------------------------------

struct ztProfileBlock
{
	ztProfiledSection *profiled_section;

	// --------------------

	ztProfileBlock(const char *section, i32 section_hash, const char *system, i32 system_hash, int thread_idx = zt_threadGetIndex()) {
		profiled_section = zt_profiledSectionEnter(section, section_hash, system, system_hash, thread_idx);
	}

	// --------------------

	~ztProfileBlock() {
		zt_profiledSectionExit(profiled_section);
	}
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_NO_PROFILE
#define ZT_PROFILE(section, system)           static i32 __zt_profileBlockHashSection##__LINE__ = zt_strHash((section)); \
                                              static i32 __zt_profileBlockHashSystem##__LINE__ = zt_strHash((system));   \
                                              ztProfileBlock __zt_profileBlock_##__LINE((section), __zt_profileBlockHashSection##__LINE__, (system), __zt_profileBlockHashSystem##__LINE__);

#define ZT_PROFILE_PLATFORM(section)          ZT_PROFILE((section), ZT_SYSTEM_PLATFORM)
#define ZT_PROFILE_RENDERING(section)         ZT_PROFILE((section), ZT_SYSTEM_RENDERING)
#define ZT_PROFILE_AUDIO(section)             ZT_PROFILE((section), ZT_SYSTEM_AUDIO)
#define ZT_PROFILE_INPUT(section)             ZT_PROFILE((section), ZT_SYSTEM_INPUT)
#define ZT_PROFILE_ASSETS(section)            ZT_PROFILE((section), ZT_SYSTEM_ASSETS)
#define ZT_PROFILE_PHYSICS(section)           ZT_PROFILE((section), ZT_SYSTEM_PHYSICS)
#define ZT_PROFILE_ANIMATION(section)         ZT_PROFILE((section), ZT_SYSTEM_ANIMATION)
#define ZT_PROFILE_PARTICLES(section)         ZT_PROFILE((section), ZT_SYSTEM_PARTICLES)
#define ZT_PROFILE_PATHFINDING(section)       ZT_PROFILE((section), ZT_SYSTEM_PATHFINDING)
#define ZT_PROFILE_GAME(section)              ZT_PROFILE((section), ZT_SYSTEM_GAME)

#else
#define ZT_PROFILE(section)

#define ZT_PROFILE_PLATFORM(section)
#define ZT_PROFILE_RENDERING(section)
#define ZT_PROFILE_AUDIO(section)
#define ZT_PROFILE_INPUT(section)
#define ZT_PROFILE_ASSETS(section)
#define ZT_PROFILE_PHYSICS(section)
#define ZT_PROFILE_ANIMATION(section)
#define ZT_PROFILE_PARTICLES(section)
#define ZT_PROFILE_PATHFINDING(section)
#define ZT_PROFILE_GAME(section)
#endif


// ------------------------------------------------------------------------------------------------
// keyboard input

#define _zt_inputKey(inputkey)	__zt_inputKey(inputkey)

#define _zt_input_keysDef \
	_zt_inputKey(ztInputKeys_Invalid),       _zt_inputKey(ztInputKeys_LeftButton),       _zt_inputKey(ztInputKeys_RightButton),    _zt_inputKey(ztInputKeys_Cancel), \
	_zt_inputKey(ztInputKeys_MiddleButton),  _zt_inputKey(ztInputKeys_XButton1),         _zt_inputKey(ztInputKeys_XButton2),       _zt_inputKey(ztInputKeys_Back), \
	_zt_inputKey(ztInputKeys_Tab),           _zt_inputKey(ztInputKeys_Clear),            _zt_inputKey(ztInputKeys_Return),         _zt_inputKey(ztInputKeys_Shift), \
	_zt_inputKey(ztInputKeys_Control),       _zt_inputKey(ztInputKeys_Menu),             _zt_inputKey(ztInputKeys_Pause),          _zt_inputKey(ztInputKeys_Capital), \
	_zt_inputKey(ztInputKeys_Kana),          _zt_inputKey(ztInputKeys_Hangul),           _zt_inputKey(ztInputKeys_Junja),          _zt_inputKey(ztInputKeys_Final), \
	_zt_inputKey(ztInputKeys_Hanja),         _zt_inputKey(ztInputKeys_Kanji),            _zt_inputKey(ztInputKeys_Escape),         _zt_inputKey(ztInputKeys_Convert), \
	_zt_inputKey(ztInputKeys_Nonconvert),    _zt_inputKey(ztInputKeys_Accept),           _zt_inputKey(ztInputKeys_ModeChange),     _zt_inputKey(ztInputKeys_Space), \
	_zt_inputKey(ztInputKeys_Prior),         _zt_inputKey(ztInputKeys_Next),             _zt_inputKey(ztInputKeys_End),            _zt_inputKey(ztInputKeys_Home), \
	_zt_inputKey(ztInputKeys_Left),          _zt_inputKey(ztInputKeys_Up),               _zt_inputKey(ztInputKeys_Right),          _zt_inputKey(ztInputKeys_Down), \
	_zt_inputKey(ztInputKeys_Select),        _zt_inputKey(ztInputKeys_Print),            _zt_inputKey(ztInputKeys_Execute),        _zt_inputKey(ztInputKeys_Snapshot), \
	_zt_inputKey(ztInputKeys_Insert),        _zt_inputKey(ztInputKeys_Delete),           _zt_inputKey(ztInputKeys_Help), \
	\
	_zt_inputKey(ztInputKeys_0),             _zt_inputKey(ztInputKeys_1),                _zt_inputKey(ztInputKeys_2),              _zt_inputKey(ztInputKeys_3),                    _zt_inputKey(ztInputKeys_4), \
	_zt_inputKey(ztInputKeys_5),             _zt_inputKey(ztInputKeys_6),                _zt_inputKey(ztInputKeys_7),              _zt_inputKey(ztInputKeys_8),                    _zt_inputKey(ztInputKeys_9), \
	_zt_inputKey(ztInputKeys_A),             _zt_inputKey(ztInputKeys_B),                _zt_inputKey(ztInputKeys_C),              _zt_inputKey(ztInputKeys_D),                    _zt_inputKey(ztInputKeys_E), \
	_zt_inputKey(ztInputKeys_F),             _zt_inputKey(ztInputKeys_G),                _zt_inputKey(ztInputKeys_H),              _zt_inputKey(ztInputKeys_I),                    _zt_inputKey(ztInputKeys_J), \
	_zt_inputKey(ztInputKeys_K),             _zt_inputKey(ztInputKeys_L),                _zt_inputKey(ztInputKeys_M),              _zt_inputKey(ztInputKeys_N),                    _zt_inputKey(ztInputKeys_O), \
	_zt_inputKey(ztInputKeys_P),             _zt_inputKey(ztInputKeys_Q),                _zt_inputKey(ztInputKeys_R),              _zt_inputKey(ztInputKeys_S),                    _zt_inputKey(ztInputKeys_T), \
	_zt_inputKey(ztInputKeys_U),             _zt_inputKey(ztInputKeys_V),                _zt_inputKey(ztInputKeys_W),              _zt_inputKey(ztInputKeys_X),                    _zt_inputKey(ztInputKeys_Y), \
	_zt_inputKey(ztInputKeys_Z), \
	\
	_zt_inputKey(ztInputKeys_LeftWin),       _zt_inputKey(ztInputKeys_RightWin),         _zt_inputKey(ztInputKeys_Apps),           _zt_inputKey(ztInputKeys_Sleep), \
	_zt_inputKey(ztInputKeys_Numpad0),       _zt_inputKey(ztInputKeys_Numpad1),          _zt_inputKey(ztInputKeys_Numpad2),        _zt_inputKey(ztInputKeys_Numpad3), \
	_zt_inputKey(ztInputKeys_Numpad4),       _zt_inputKey(ztInputKeys_Numpad5),          _zt_inputKey(ztInputKeys_Numpad6),        _zt_inputKey(ztInputKeys_Numpad7), \
	_zt_inputKey(ztInputKeys_Numpad8),       _zt_inputKey(ztInputKeys_Numpad9),          _zt_inputKey(ztInputKeys_Multiply),       _zt_inputKey(ztInputKeys_Add), \
	_zt_inputKey(ztInputKeys_Separator),     _zt_inputKey(ztInputKeys_Substract),        _zt_inputKey(ztInputKeys_Decimal),        _zt_inputKey(ztInputKeys_Divide), \
	\
	_zt_inputKey(ztInputKeys_F1),            _zt_inputKey(ztInputKeys_F2),               _zt_inputKey(ztInputKeys_F3),             _zt_inputKey(ztInputKeys_F4), \
	_zt_inputKey(ztInputKeys_F5),            _zt_inputKey(ztInputKeys_F6),               _zt_inputKey(ztInputKeys_F7),             _zt_inputKey(ztInputKeys_F8), \
	_zt_inputKey(ztInputKeys_F9),            _zt_inputKey(ztInputKeys_F10),              _zt_inputKey(ztInputKeys_F11),            _zt_inputKey(ztInputKeys_F12), \
	_zt_inputKey(ztInputKeys_F13),           _zt_inputKey(ztInputKeys_F14),              _zt_inputKey(ztInputKeys_F15),            _zt_inputKey(ztInputKeys_F16), \
	_zt_inputKey(ztInputKeys_F17),           _zt_inputKey(ztInputKeys_F18),              _zt_inputKey(ztInputKeys_F19),            _zt_inputKey(ztInputKeys_F20), \
	_zt_inputKey(ztInputKeys_F21),           _zt_inputKey(ztInputKeys_F22),              _zt_inputKey(ztInputKeys_F23),            _zt_inputKey(ztInputKeys_F24), \
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

// ------------------------------------------------------------------------------------------------

enum ztInputKeys_Enum
{
	_zt_input_keysDef

	ztInputKeys_MAX,
};

// ------------------------------------------------------------------------------------------------

#undef _zt_inputKey

// ------------------------------------------------------------------------------------------------

enum ztInputKeyFlags_Enum
{
	ztInputKeyFlags_Pressed      = (1<<0),
	ztInputKeyFlags_JustPressed  = (1<<1),
	ztInputKeyFlags_JustReleased = (1<<2),
	ztInputKeyFlags_JustRepeated = (1<<3),
	ztInputKeyFlags_StateKey     = (1<<4),
};

// ------------------------------------------------------------------------------------------------

struct ztInputKeys
{
	ztInputKeys_Enum code;
	i32 flags;

	char *name;
	char display;
	char shift_display;

	i32 platform_mapping;

	r64 time_pressed;

	bool pressed()      { return zt_bitIsSet(flags, ztInputKeyFlags_Pressed); }
	bool justPressed()  { return zt_bitIsSet(flags, ztInputKeyFlags_JustPressed); }
	bool justReleased() { return zt_bitIsSet(flags, ztInputKeyFlags_JustReleased); }
	bool justRepeated() { return zt_bitIsSet(flags, ztInputKeyFlags_JustRepeated); }
	bool stateKey()     { return zt_bitIsSet(flags, ztInputKeyFlags_StateKey); }

	bool justPressedOrRepeated() {
		return justPressed() || justRepeated();
	}
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_INPUT_KEYSTROKES
#define ZT_MAX_INPUT_KEYSTROKES	16
#endif

// ------------------------------------------------------------------------------------------------

bool         zt_inputThisFrame();
ztInputKeys* zt_inputKeysAccessState(); // not thread safe
void         zt_inputKeysCopyState(ztInputKeys input_keys[ztInputKeys_MAX]); // should only be called in main thread
void         zt_inputGetKeyStrokes(ztInputKeys_Enum key_strokes[ZT_MAX_INPUT_KEYSTROKES]);

// ------------------------------------------------------------------------------------------------

enum ztInputMouseCursor_Enum
{
	ztInputMouseCursor_None,
	ztInputMouseCursor_Arrow,
	ztInputMouseCursor_ResizeNS,
	ztInputMouseCursor_ResizeEW,
	ztInputMouseCursor_ResizeNWSE,
	ztInputMouseCursor_ResizeSWNE,
};

// ------------------------------------------------------------------------------------------------

enum ztInputMouseFlags_Enum
{
	ztInputMouseFlags_Pressed      = (1<<0),
	ztInputMouseFlags_JustPressed  = (1<<1),
	ztInputMouseFlags_JustReleased = (1<<2),
};

// ------------------------------------------------------------------------------------------------

struct ztInputMouse
{
	i32 screen_x;
	i32 screen_y;

	i32 delta_x;
	i32 delta_y;

	union {
		i32 button_states[3];

		struct {
			i32 button_state_left;
			i32 button_state_right;
			i32 button_state_middle;
		};
	};

	i32 wheel_delta;

	bool over_window;
	ztInputMouseCursor_Enum cursor;

	bool pressed(int button)      { zt_assert(button >= 0 && button < zt_elementsOf(button_states)); return zt_bitIsSet(button_states[button], ztInputKeyFlags_Pressed); }
	bool justPressed(int button)  { zt_assert(button >= 0 && button < zt_elementsOf(button_states)); return zt_bitIsSet(button_states[button], ztInputKeyFlags_JustPressed); }
	bool justReleased(int button) { zt_assert(button >= 0 && button < zt_elementsOf(button_states)); return zt_bitIsSet(button_states[button], ztInputKeyFlags_JustReleased); }

	bool leftPressed()      { return pressed(0); }
	bool leftJustPressed()  { return justPressed(0); }
	bool leftJustReleased() { return justReleased(0); }

	bool rightPressed()      { return pressed(1); }
	bool rightJustPressed()  { return justPressed(1); }
	bool rightJustReleased() { return justReleased(1); }

	bool middlePressed()      { return pressed(2); }
	bool middleJustPressed()  { return justPressed(2); }
	bool middleJustReleased() { return justReleased(2); }
};

// ------------------------------------------------------------------------------------------------

ztInputMouse* zt_inputMouseAccessState(); // not thread safe
void          zt_inputMouseCopyState(ztInputMouse *input_mouse);

void          zt_inputMouseLook(bool mouse_look);
bool          zt_inputMouseIsLook();

void          zt_inputMouseSetCursor(ztInputMouseCursor_Enum cursor);

// ------------------------------------------------------------------------------------------------

enum ztInputControllerFlags_Enum
{
	ztInputControllerFlags_Pressed      = (1 << 0),
	ztInputControllerFlags_JustPressed  = (1 << 1),
	ztInputControllerFlags_JustReleased = (1 << 2),
};

// ------------------------------------------------------------------------------------------------

enum ztInputControllerButton_Enum
{
	ztInputControllerButton_DPadUp,
	ztInputControllerButton_DPadDown,
	ztInputControllerButton_DPadLeft,
	ztInputControllerButton_DPadRight,
	ztInputControllerButton_Start,
	ztInputControllerButton_Back,
	ztInputControllerButton_ThumbLeft,
	ztInputControllerButton_ThumbRight,
	ztInputControllerButton_ShoulderLeft,
	ztInputControllerButton_ShoulderRight,
	ztInputControllerButton_A,
	ztInputControllerButton_B,
	ztInputControllerButton_X,
	ztInputControllerButton_Y,
	ztInputControllerButton_TriggerLeft,
	ztInputControllerButton_TriggerRight,
	ztInputControllerButton_ThumbpadLeft,
	ztInputControllerButton_ThumbpadRight,

	ztInputControllerButton_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztInputController
{
	bool connected;

	union {
		i32 button_states[ztInputControllerButton_MAX];

		struct {
			i32 button_state_dpad_up;
			i32 button_state_dpad_down;
			i32 button_state_dpad_left;
			i32 button_state_dpad_right;
			i32 button_state_start;
			i32 button_state_back;
			i32 button_state_thumb_left;
			i32 button_state_thumb_right;
			i32 button_state_shoulder_left;
			i32 button_state_shoulder_right;
			i32 button_state_a;
			i32 button_state_b;
			i32 button_state_x;
			i32 button_state_y;

			i32 button_state_trigger_left;
			i32 button_state_trigger_right;
			i32 button_state_thumbpad_left;
			i32 button_state_thumbpad_right;
		};
	};

	union {
		r32 button_times[ztInputControllerButton_MAX];

		struct {
			r32 button_time_dpad_up;
			r32 button_time_dpad_down;
			r32 button_time_dpad_left;
			r32 button_time_dpad_right;
			r32 button_time_start;
			r32 button_time_back;
			r32 button_time_thumb_left;
			r32 button_time_thumb_right;
			r32 button_time_shoulder_left;
			r32 button_time_shoulder_right;
			r32 button_time_a;
			r32 button_time_b;
			r32 button_time_x;
			r32 button_time_y;

			r32 button_time_trigger_left;
			r32 button_time_trigger_right;
			r32 button_time_thumbpad_left;
			r32 button_time_thumbpad_right;
		};
	};

	union {
		r32 analog_values[6];

		struct {
			r32 analog_value_trigger_left;
			r32 analog_value_trigger_right;
			r32 analog_value_thumb_pad_left_x;
			r32 analog_value_thumb_pad_left_y;
			r32 analog_value_thumb_pad_right_x;
			r32 analog_value_thumb_pad_right_y;
		};
	};

	bool pressed(int button)      { zt_assert(button >= 0 && button < zt_elementsOf(button_states)); return zt_bitIsSet(button_states[button], ztInputControllerFlags_Pressed); }
	bool justPressed(int button)  { zt_assert(button >= 0 && button < zt_elementsOf(button_states)); return zt_bitIsSet(button_states[button], ztInputControllerFlags_JustPressed); }
	bool justReleased(int button) { zt_assert(button >= 0 && button < zt_elementsOf(button_states)); return zt_bitIsSet(button_states[button], ztInputControllerFlags_JustReleased); }

};

// ------------------------------------------------------------------------------------------------

#define ZT_MAX_INPUT_CONTROLLERS	4

// ------------------------------------------------------------------------------------------------

ztInputController* zt_inputControllerAccessState(int idx); // not thread safe
void               zt_inputControllerCopyState(ztInputController *input_controller, int idx);
void               zt_inputControllerTriggerHapticFeedback(int idx, r32 strength_low, r32 strength_high);


// ------------------------------------------------------------------------------------------------
// Asset Manager
//
// Using an asset manager is preferable over straight file access because it gives a lot of
// flexibility on how assets are managed.  Using this system allows for seamless use of straight
// files during development and a single packed file for releases.  The system can even be expanded
// to downloading resources from a network source.  It allows for resources to automatically
// reload themselves easily when needed or when the source changes (hot reloading of files).
//

enum ztAssetManagerSource_Enum
{
	ztAssetManagerSource_Unknown,

	ztAssetManagerSource_Directory,
	ztAssetManagerSource_PackedFile,

	ztAssetManagerSource_MAX,
};

// ------------------------------------------------------------------------------------------------

enum ztAssetManagerType_Enum
{
	ztAssetManagerType_Unknown,

	ztAssetManagerType_ImagePNG,
	ztAssetManagerType_ImageJPG,
	ztAssetManagerType_AudioWAV,

	ztAssetManagerType_Shader,
	ztAssetManagerType_Font,

	ztAssetManagerType_MeshOBJ,
	ztAssetManagerType_Material,

	ztAssetManagerType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztAssetManager;

typedef i32 ztAssetID; // this is an index into the asset arrays
typedef void(*zt_assetManagerAssetUpdated_Func)(ztAssetManager*, ztAssetID, void*);

#define ztAssetManagerMaxAssets	1024

// ------------------------------------------------------------------------------------------------

struct ztAssetManager
{
	ztAssetManagerSource_Enum source;

	const char *asset_name[ztAssetManagerMaxAssets];
	i32 asset_name_hash[ztAssetManagerMaxAssets];
	i32 asset_size[ztAssetManagerMaxAssets];
	ztAssetManagerType_Enum asset_type[ztAssetManagerMaxAssets];
	void *asset_data[ztAssetManagerMaxAssets];

	union {
		struct {
			i64 asset_modified[ztAssetManagerMaxAssets];
			zt_assetManagerAssetUpdated_Func asset_callbacks[ztAssetManagerMaxAssets];
			void *asset_callback_user_data[ztAssetManagerMaxAssets];
			ztAssetID asset_callback_ids[ztAssetManagerMaxAssets];
			i32 asset_callbacks_count;
			i32 asset_modified_check_last_idx; // used internally
		};

		const char *asset_file[ztAssetManagerMaxAssets];
	};

	i32 asset_count;

	union {
		ztSerial packed;

		struct {
			char *directory;
			int directory_len;
			ztDirectoryMonitor directory_mon;
		};
	};

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

// takes the given directory and places all files in all directories (recursively) into the given packed file
bool      zt_assetMakePackedFile(const char *directory, const char *packed_file, ztMemoryArena *arena = nullptr);

bool      zt_assetManagerLoadDirectory(ztAssetManager *asset_mgr, const char *directory, ztMemoryArena *arena = nullptr);
bool      zt_assetManagerLoadPackedFile(ztAssetManager *asset_mgr, const char *packed_file, ztMemoryArena *arena = nullptr);
void      zt_assetManagerFree(ztAssetManager *asset_mgr);

bool      zt_assetExists(ztAssetManager *asset_mgr, const char *asset);
bool      zt_assetExists(ztAssetManager *asset_mgr, i32 asset_hash);
bool      zt_assetFileExistsAsAsset(ztAssetManager *asset_mgr, const char *file_name, i32 *asset_hash);
ztAssetID zt_assetLoad(ztAssetManager *asset_mgr, const char *asset);
ztAssetID zt_assetLoad(ztAssetManager *asset_mgr, i32 asset_hash);
ztAssetID zt_assetLoad(ztAssetManager *asset_mgr, const char *asset, ztAssetID same_location_as);
i32       zt_assetSize(ztAssetManager *asset_mgr, ztAssetID asset_id);
bool      zt_assetLoadData(ztAssetManager *asset_mgr, ztAssetID asset_id, void *data, i32 data_size);

bool      zt_assetClearCache(ztAssetManager *asset_mgr, ztAssetID asset_id);

// if reading from a directory, the passed function will be called whenever the file changes
void      zt_assetAddReloadCallback(ztAssetManager *asset_mgr, ztAssetID asset_id, zt_assetManagerAssetUpdated_Func function, void *user_data);
void      zt_assetRemoveReloadCallback(ztAssetManager *asset_mgr, ztAssetID asset_id, void *user_data);

void      zt_assetManagerCheckForChanges(ztAssetManager *asset_mgr);


// ------------------------------------------------------------------------------------------------
// shaders

typedef i32 ztShaderID;

ztShaderID zt_shaderMake(ztAssetManager *asset_mgr, ztAssetID asset_id);
void       zt_shaderFree(ztShaderID shader_id);

// --------------------------------------------------------
// sets shader variables "model", "projection" and "view"
void       zt_shaderSetCameraMatrices(ztShaderID shader_id, const ztMat4& projection, const ztMat4& view);
void       zt_shaderSetModelMatrices(ztShaderID shader_id, const ztMat4& model);


// ------------------------------------------------------------------------------------------------

enum ztShaderVariable_Enum
{
	ztShaderVariable_Invalid,

	ztShaderVariable_Float,
	ztShaderVariable_Int,
	ztShaderVariable_Vec2,
	ztShaderVariable_Vec3,
	ztShaderVariable_Vec4,
	ztShaderVariable_Mat3,
	ztShaderVariable_Mat4,
	ztShaderVariable_Tex,
	ztShaderVariable_TexCube,

	ztShaderVariable_MAX,
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_SHADER_MAX_VARIABLES
#define ZT_SHADER_MAX_VARIABLES		128
#endif

// ------------------------------------------------------------------------------------------------

struct ztShaderVariableValues
{
	struct Variable
	{
		ztShaderVariable_Enum type;
		char name[64];
		u32 name_hash;
		bool changed;

		union {
			r32 val_float;
			i32 val_int;
			r32 val_vec2[2];
			r32 val_vec3[3];
			r32 val_vec4[4];
			r32 val_mat3[9];
			r32 val_mat4[16];
			i32 val_tex;
		};
	};

	Variable variables[ZT_SHADER_MAX_VARIABLES];
	int variables_count;
};

// ------------------------------------------------------------------------------------------------

void zt_shaderBegin(ztShaderID shader_id);
void zt_shaderEnd(ztShaderID shader_id);

// ------------------------------------------------------------------------------------------------

// populates the ztShaderVariableValues instance with the variables for the shader, along with default values
void zt_shaderPopulateVariables(ztShaderID shader_id, ztShaderVariableValues *shader_vars);

// applys the given variable values to the renderer's implementation of the shader
void zt_shaderApplyVariables(ztShaderID shader_id, ztShaderVariableValues *shader_vars);

// applys the changed variables to the shader
void zt_shaderApplyVariables(ztShaderID shader_id);

// ------------------------------------------------------------------------------------------------

// these functions change the default values of the shader
bool zt_shaderHasVariable(ztShaderID shader_id, const char *variable, ztShaderVariable_Enum *type);
void zt_shaderSetVariableFloat(ztShaderID shader_id, const char *variable, r32 value);
void zt_shaderSetVariableInt(ztShaderID shader_id, const char *variable, i32 value);
void zt_shaderSetVariableVec2(ztShaderID shader_id, const char *variable, const ztVec2& value);
void zt_shaderSetVariableVec3(ztShaderID shader_id, const char *variable, const ztVec3& value);
void zt_shaderSetVariableVec4(ztShaderID shader_id, const char *variable, const ztVec4& value);
void zt_shaderSetVariableMat4(ztShaderID shader_id, const char *variable, const ztMat4& value);
void zt_shaderSetVariableMat3(ztShaderID shader_id, const char *variable, r32 value[12]);
void zt_shaderSetVariableTex(ztShaderID shader_id, const char *variable, i32 texture_id);
void zt_shaderSetVariableTexCube(ztShaderID shader_id, const char *variable, i32 texture_id);

bool zt_shaderHasVariable(ztShaderID shader_id, u32 variable_hash, ztShaderVariable_Enum *type);
void zt_shaderSetVariableFloat(ztShaderID shader_id, u32 variable_hash, r32 value);
void zt_shaderSetVariableInt(ztShaderID shader_id, u32 variable_hash, i32 value);
void zt_shaderSetVariableVec2(ztShaderID shader_id, u32 variable_hash, const ztVec2& value);
void zt_shaderSetVariableVec3(ztShaderID shader_id, u32 variable_hash, const ztVec3& value);
void zt_shaderSetVariableVec4(ztShaderID shader_id, u32 variable_hash, const ztVec4& value);
void zt_shaderSetVariableMat4(ztShaderID shader_id, u32 variable_hash, const ztMat4& value);
void zt_shaderSetVariableMat3(ztShaderID shader_id, u32 variable_hash, r32 value[12]);
void zt_shaderSetVariableTex(ztShaderID shader_id, u32 variable_hash, i32 texture_id);
void zt_shaderSetVariableTexCube(ztShaderID shader_id, u32 variable_hash, i32 texture_id);

// ------------------------------------------------------------------------------------------------

// these functions allow for temporary changes of a shader's variables
bool zt_shaderHasVariable(ztShaderVariableValues *shader_vars, const char *variable, ztShaderVariable_Enum *type);
void zt_shaderSetVariableFloat(ztShaderVariableValues *shader_vars, const char *variable, r32 value);
void zt_shaderSetVariableInt(ztShaderVariableValues *shader_vars, const char *variable, i32 value);
void zt_shaderSetVariableVec2(ztShaderVariableValues *shader_vars, const char *variable, const ztVec2& value);
void zt_shaderSetVariableVec3(ztShaderVariableValues *shader_vars, const char *variable, const ztVec3& value);
void zt_shaderSetVariableVec4(ztShaderVariableValues *shader_vars, const char *variable, const ztVec4& value);
void zt_shaderSetVariableMat4(ztShaderVariableValues *shader_vars, const char *variable, const ztMat4& value);
void zt_shaderSetVariableMat3(ztShaderVariableValues *shader_vars, const char *variable, r32 value[12]);
void zt_shaderSetVariableTex(ztShaderVariableValues *shader_vars, const char *variable, i32 texture_id);
void zt_shaderSetVariableTexCube(ztShaderVariableValues *shader_vars, const char *variable, i32 texture_id);

bool zt_shaderHasVariable(ztShaderVariableValues *shader_vars, u32 variable_hash, ztShaderVariable_Enum *type);
void zt_shaderSetVariableFloat(ztShaderVariableValues *shader_vars, u32 variable_hash, r32 value);
void zt_shaderSetVariableInt(ztShaderVariableValues *shader_vars, u32 variable_hash, i32 value);
void zt_shaderSetVariableVec2(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztVec2& value);
void zt_shaderSetVariableVec3(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztVec3& value);
void zt_shaderSetVariableVec4(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztVec4& value);
void zt_shaderSetVariableMat4(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztMat4& value);
void zt_shaderSetVariableMat3(ztShaderVariableValues *shader_vars, u32 variable_hash, r32 value[12]);
void zt_shaderSetVariableTex(ztShaderVariableValues *shader_vars, u32 variable_hash, i32 texture_id);
void zt_shaderSetVariableTexCube(ztShaderVariableValues *shader_vars, u32 variable_hash, i32 texture_id);

// ------------------------------------------------------------------------------------------------

enum ztShaderDefault_Enum
{
	ztShaderDefault_Solid,		// no textures
	ztShaderDefault_Unlit,		// diffuse
	ztShaderDefault_Lit,		// diffuse
	ztShaderDefault_LitShadow,	// diffuse, shadow map, material values

	ztShaderDefault_Skybox,
	ztShaderDefault_ShadowDirectional,

	ztShaderDefault_MAX,
};

ztShaderID zt_shaderGetDefault(ztShaderDefault_Enum shader_default);


// ------------------------------------------------------------------------------------------------
// textures

typedef i32 ztTextureID;

enum ztTextureFlags_Enum
{
	ztTextureFlags_MipMaps      = (1<<0),
	ztTextureFlags_DepthMap     = (1<<1), // going to be used for depth information
	ztTextureFlags_PixelPerfect = (1<<2),
};

enum ztTextureCubeMapFiles_Enum
{
	ztTextureCubeMapFiles_Right,
	ztTextureCubeMapFiles_Left,
	ztTextureCubeMapFiles_Top,
	ztTextureCubeMapFiles_Bottom,
	ztTextureCubeMapFiles_Back,
	ztTextureCubeMapFiles_Front,

	ztTextureCubeMapFiles_MAX,
};

ztTextureID zt_textureMake(ztAssetManager *asset_mgr, ztAssetID asset_id, i32 flags = 0);
ztTextureID zt_textureMake(byte *pixels, i32 width, i32 height, i32 flags = 0);
ztTextureID zt_textureMakeFromFile(const char *file, i32 flags = 0);
ztTextureID zt_textureMakeFromFileData(void *data, i32 size, i32 flags = 0);
ztTextureID zt_textureMakeFromPixelData(void *data, i32 width, i32 height, i32 flags = 0);
ztTextureID zt_textureMakeRenderTarget(i32 width, i32 height, i32 flags = 0);
ztTextureID zt_textureMakeCubeMap(ztAssetManager *asset_mgr, const char *asset_format); // format is "data/textures/cubemap_%s.png", with lower case names matching the enum ("right", "left", etc.)
ztTextureID zt_textureMakeCubeMap(ztAssetManager *asset_mgr, ztAssetID files[ztTextureCubeMapFiles_MAX]);

void        zt_textureFree(ztTextureID texture_id);

void        zt_textureRenderTargetPrepare(ztTextureID texture_id);
void        zt_textureRenderTargetCommit(ztTextureID texture_id);

ztPoint2    zt_textureGetSize(ztTextureID texture_id);


// ------------------------------------------------------------------------------------------------
// materials

enum ztMaterialFlags_Enum
{
	ztMaterialFlags_OwnsTexture = (1 << 0),
};

// ------------------------------------------------------------------------------------------------

struct ztMaterial
{
	char name[64]; // used when loading from files

	ztTextureID diffuse_tex;
	ztVec4 diffuse_color;
	i32 diffuse_flags;

	u32 diffuse_tex_override; // shader variable name override
	u32 diffuse_color_override;

	ztTextureID specular_tex;
	ztVec4 specular_color;
	i32 specular_flags;

	u32 specular_tex_override;
	u32 specular_color_override;

	ztTextureID normal_tex;
	i32 normal_flags;

	u32 normal_tex_override;

	r32 shininess;

	u32 shininess_override;
};


ztMaterial zt_materialMake(ztTextureID diffuse_tex = ztInvalidID, const ztVec4& diffuse_color = ztVec4::one, i32 diffuse_flags = 0, 
						   ztTextureID specular_tex = ztInvalidID, const ztVec4& specular_color = ztVec4::one, i32 specular_flags = 0,
						   ztTextureID normal_tex = ztInvalidID, i32 normal_flags = 0, r32 shininess = 0.5f);

int zt_materialLoad(ztAssetManager *asset_mgr, ztAssetID asset_id, ztMaterial *materials_arr, int materials_arr_size);
int zt_materialLoadFromFile(char *file_name, ztMaterial *materials_arr, int materials_arr_size);

void zt_materialFree(ztMaterial *material);

bool zt_materialIsEmpty(ztMaterial *material);

void zt_materialPrepare(ztMaterial *material, ztShaderID shader, ztTextureID *additional_tex = nullptr, u32 *additional_tex_name_hashes = nullptr, int additional_tex_count = 0);


// ------------------------------------------------------------------------------------------------
// meshes

typedef i32 ztMeshID;

// ------------------------------------------------------------------------------------------------

// NOTE: UV coordinates are 0,0 = top left, 1,1 = bottom right

ztMeshID zt_meshMake(ztVec3 *verts, ztVec2 *uvs, ztVec3 *normals, i32 vert_count, u32 *indices, i32 indices_count);
void     zt_meshFree(ztMeshID mesh_id);

ztMeshID zt_meshMakePrimitiveBox(r32 width, r32 height, r32 depth);
ztMeshID zt_meshMakePrimitivePlane(r32 width, r32 depth, int grid_w = 1, int grid_d = 1);
ztMeshID zt_meshMakePrimitiveDiamond(r32 width, r32 top, r32 bottom, int sides);

ztVec3   zt_meshGetAABB(ztMeshID mesh_id);
void     zt_meshGetOBB(ztMeshID mesh_id, ztVec3 *center, ztVec3 *size);

enum ztMeshPrimativeSphere_Enum
{
	ztMeshPrimitiveSphere_TexDuplicatedPerFace, // the quadrilateralised spherical cube maps the same texture on each of the 6 faces
	ztMeshPrimitiveSphere_TexWrapped,           // the texture coordinates are in the shape of a T with the T at the top of the texture
};

ztMeshID zt_meshMakePrimitiveSphere(r32 radius, int rings, ztMeshPrimativeSphere_Enum texture);

int      zt_meshLoadOBJ(ztAssetManager *asset_mgr, ztAssetID asset_id, ztMeshID *mesh_ids, ztMaterial *materials, int mesh_mat_size, const ztVec3& scale = ztVec3::one, const ztVec3& offset = ztVec3::zero);

void     zt_meshRender(ztMeshID mesh_id);

// ------------------------------------------------------------------------------------------------
// transform

struct ztTransform
{
	ztVec3 position;
	ztQuat rotation;
	ztVec3 scale;
};


// ------------------------------------------------------------------------------------------------
// camera

enum ztCameraType_Enum
{
	ztCameraType_Invalid,
	ztCameraType_Orthographic,
	ztCameraType_Perspective,

	ztCameraType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztCamera
{
	ztCameraType_Enum type;

	ztVec3 position;

	i32 width, height;
	r32 near_z, far_z;

	ztMat4 mat_view, mat_proj;

	union {
		struct { // orthographic only
			i32 native_w, native_h;
			r32 zoom;
		};

		struct { // perspective only
			r32 fov;
			ztQuat rotation;
			ztVec3 direction;
		};
	};

};

// ------------------------------------------------------------------------------------------------

void zt_cameraMakeOrtho(ztCamera *camera, i32 width, i32 height, i32 native_w, i32 native_h, r32 near_z, r32 far_z, const ztVec3& position = ztVec3::zero);
void zt_cameraMakePersp(ztCamera *camera, i32 width, i32 height, r32 fov, r32 near_z, r32 far_z, const ztVec3& position = ztVec3::zero, const ztQuat& rotation = ztQuat::identity);

void zt_cameraRecalcMatrices(ztCamera *camera); // should be called anytime position or rotation changes
void zt_cameraCalcFinalMatrix(ztCamera *camera, ztMat4* final_mat);

// it is sometimes useful to set the camera matrices when the position/rotation is not known (such as with vr hmds)
void zt_cameraSetMatrices(ztCamera *camera, ztMat4& proj, ztMat4& view);

void     zt_cameraOrthoGetExtents(ztCamera *camera, ztVec2 *min_ext, ztVec2 *max_ext);
ztVec2   zt_cameraOrthoGetMaxExtent(ztCamera *camera);
ztVec2   zt_cameraOrthoGetMinExtent(ztCamera *camera);
ztVec2   zt_cameraOrthoGetViewportSize(ztCamera *camera);
ztVec2   zt_cameraOrthoScreenToWorld(ztCamera *camera, int sx, int sy);
ztPoint2 zt_cameraOrthoWorldToScreen(ztCamera *camera, ztVec2& pos);

void     zt_cameraPerspGetMouseRay(ztCamera *camera, int sx, int sy, ztVec3 *point, ztVec3 *direction);


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#ifndef CAMERA_SHAKE_MAX_SAMPLES
#define CAMERA_SHAKE_MAX_SAMPLES	1000
#endif

// ------------------------------------------------------------------------------------------------

struct ztCameraShake
{
	ztVec3   original_position;
	r32      duration;
	r32      current_time;

	r32      frequency;
	r32      amplitude;
	i32      sample_count;

	r32      samples_x[CAMERA_SHAKE_MAX_SAMPLES];
	r32      samples_y[CAMERA_SHAKE_MAX_SAMPLES];

	ztRandom randomizer;

	ztVec2   offset;
};

// ------------------------------------------------------------------------------------------------

// NOTE: Once prerender is applied, camera matrices need recalculated.  Also after postrender.

ztCameraShake zt_cameraShakeMake(r32 duration, r32 speed, r32 intensity, i32 seed);
void          zt_cameraShakeStart(ztCameraShake *camera_shake);
void          zt_cameraShakeUpdate(ztCameraShake *camera_shake, r32 dt);
bool          zt_cameraShakePreRender(ztCameraShake *camera_shake, ztCamera *camera);
bool          zt_cameraShakePostRender(ztCameraShake *camera_shake, ztCamera *camera);

struct ztDrawList;

void          zt_cameraShakePreRender(ztCameraShake *camera_shake, ztDrawList *draw_list);
void          zt_cameraShakePostRender(ztCameraShake *camera_shake, ztDrawList *draw_list);

// ------------------------------------------------------------------------------------------------

struct ztFrustum
{
	union {
		struct{
			ztVec3 points[8];
		};

		struct {
			ztVec3 near_rect[4];
			ztVec3 far_rect[4];
		};

		struct {
			ztVec3 near_nw;
			ztVec3 near_ne;
			ztVec3 near_se;
			ztVec3 near_sw;
			ztVec3 far_nw;
			ztVec3 far_ne;
			ztVec3 far_se;
			ztVec3 far_sw;
		};
	};
};

// ------------------------------------------------------------------------------------------------

ztFrustum zt_cameraCalcViewFrustum(ztCamera *camera);


// ------------------------------------------------------------------------------------------------

struct ztCameraControllerFPS
{
	// settings:
	ztCamera *camera;

	r32 mouse_sensitivity;
	r32 speed;
	r32 boosted_speed;
	r32 sneaking_speed;

	// per-frame input:
	r32 mouse_delta_x;
	r32 mouse_delta_y;

	bool is_boosted;
	bool is_sneaking;

	r32 move_back;
	r32 move_forward;
	r32 strafe_left;
	r32 strafe_right;

	// used internally:
	ztVec3 rotation;
	ztVec3 velocity;
};

// ------------------------------------------------------------------------------------------------

ztCameraControllerFPS zt_cameraControllerMakeFPS(ztCamera *camera, ztVec3 initial_rotation = ztVec3::zero);
void                  zt_cameraControlUpdateFPS(ztCameraControllerFPS *controller, r32 dt);
void                  zt_cameraControlUpdateWASD(ztCameraControllerFPS *controller, ztInputMouse *input_mouse, ztInputKeys *input_keys, r32 dt); // simple WASD + mouse look camera manipulation - good for testing



// ------------------------------------------------------------------------------------------------
// vertex arrays

enum ztVertexArrayDataType_Enum
{
	ztVertexArrayDataType_Float,

	ztVertexArrayDataType_MAX,
};

// ------------------------------------------------------------------------------------------------

enum ztVertexArrayDrawType_Enum
{
	ztVertexArrayDrawType_Triangles,
	ztVertexArrayDrawType_Lines,
	ztVertexArrayDrawType_Points,

	ztVertexArrayDrawType_MAX,
};

// ------------------------------------------------------------------------------------------------

typedef i32 ztVertexArrayID;

// ------------------------------------------------------------------------------------------------

struct ztVertexArrayEntry
{
	ztVertexArrayDataType_Enum type;
	i32                        size; // sizeof(type) * count of type variables
};

// ------------------------------------------------------------------------------------------------

ztVertexArrayID zt_vertexArrayMake(ztVertexArrayEntry *entries, int entries_count, void *vert_data, int vert_count);
void            zt_vertexArrayFree(ztVertexArrayID vertex_array_id);

bool            zt_vertexArrayUpdate(ztVertexArrayID vertex_array_id, void *vert_data, int vert_count);
void            zt_vertexArrayDraw(ztVertexArrayID vertex_array_id, ztVertexArrayDrawType_Enum draw_type = ztVertexArrayDrawType_Triangles);


// ------------------------------------------------------------------------------------------------
// rendering

enum ztDrawCommandType_Enum
{
	ztDrawCommandType_Invalid,

	ztDrawCommandType_Point,
	ztDrawCommandType_Line,
	ztDrawCommandType_Triangle,

	ztDrawCommandType_ChangeShader,
	ztDrawCommandType_ChangeColor,
	ztDrawCommandType_ChangeTexture,
	ztDrawCommandType_ChangeClipping,
	ztDrawCommandType_ChangeFlags,
	ztDrawCommandType_ChangeOffset,
	ztDrawCommandType_ChangeTransform,

	ztDrawCommandType_Skybox,
	ztDrawCommandType_Billboard,
	ztDrawCommandType_VertexArray,

	ztDrawCommandType_MAX,
};

// ------------------------------------------------------------------------------------------------

enum ztDrawCommandBillboardFlags_Enum
{
	ztDrawCommandBillboardFlags_AxisX = (1<<0),
	ztDrawCommandBillboardFlags_AxisY = (1<<1),
	ztDrawCommandBillboardFlags_AxisZ = (1<<2),

	ztDrawCommandBillboardFlags_AxisAll = ztDrawCommandBillboardFlags_AxisX | ztDrawCommandBillboardFlags_AxisY | ztDrawCommandBillboardFlags_AxisZ,
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_DRAW_COMMAND_MAX_TEXTURES
#define ZT_DRAW_COMMAND_MAX_TEXTURES	12
#endif

// ------------------------------------------------------------------------------------------------

struct ztDrawCommand
{
	ztDrawCommandType_Enum type;

	union {
		struct {
			ztVec3 point;
		};

		struct {
			ztVec3 line[2];
		};

		struct {
			ztVec3 tri_pos[3];
			ztVec2 tri_uv[3];
			ztVec3 tri_norm[3];
		};

		struct {
			ztShaderID shader;
			bool       shader_pop;
		};

		struct {
			ztColor color;
			bool    color_pop;
		};

		struct {
			ztTextureID texture[ZT_DRAW_COMMAND_MAX_TEXTURES];
			i32         texture_count;
			bool        texture_pop;
		};

		struct {
			ztVec2 clip_center;
			ztVec2 clip_size;
			int    clip_idx;
		};

		struct {
			i32 flags;
		};

		struct {
			ztVec3 offset;
			bool   offset_pop;
		};

		struct {
			ztMat4 transform;
			bool   transform_pop;
		};

		struct {
			ztVec3 billboard_center;
			ztVec2 billboard_size;
			ztVec4 billboard_uv;
			i32    billboard_flags;
		};

		struct {
			ztVertexArrayID            vertex_array;
			ztVertexArrayDrawType_Enum vertex_array_draw_type;
		};
	};
};

// ------------------------------------------------------------------------------------------------

enum ztDrawListFlags_Enum
{
	ztDrawListFlags_NoReset = (1 << 0),
};

// ------------------------------------------------------------------------------------------------

struct ztDrawList
{
	ztDrawCommand *commands;
	i32 commands_size;
	i32 commands_count;

	i32 flags;

	ztMemoryArena *arena;

	zt_debugOnly(int active_shaders);
	zt_debugOnly(int active_textures);
};

// ------------------------------------------------------------------------------------------------

// NOTE: UV coordinates for draw lists are 0,0 = top left, 1,1 = top right

bool zt_drawListMake(ztDrawList *draw_list, i32 max_commands, i32 flags = 0, ztMemoryArena *arena = zt_memGetGlobalArena());
void zt_drawListFree(ztDrawList *draw_list);

bool zt_drawListAddPoint(ztDrawList *draw_list, const ztVec3& p);
bool zt_drawListAddLine(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2);
bool zt_drawListAddLine(ztDrawList *draw_list, const ztVec3 p[2]);
bool zt_drawListAddEmptyTriangle(ztDrawList *draw_list, const ztVec3 p[3]);
bool zt_drawListAddEmptyTriangle(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3);
bool zt_drawListAddEmptyQuad(ztDrawList *draw_list, const ztVec3 p[4]); // clockwise or counter clockwise positions
bool zt_drawListAddEmptyQuad(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3, const ztVec3& p4);
bool zt_drawListAddEmptyRect(ztDrawList *draw_list, const ztVec2& pos, const ztVec2& size);
bool zt_drawListAddEmptyRect(ztDrawList *draw_list, const ztVec3& pos, const ztVec2& size);
bool zt_drawListAddEmptyCubeFromCenterSize(ztDrawList *draw_list, const ztVec3& pos, const ztVec3& size);
bool zt_drawListAddEmptyCubeFromMinMax(ztDrawList *draw_list, const ztVec3& min, const ztVec3& max);
bool zt_drawListAddFilledTriangle(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3); // points need to be ccw
bool zt_drawListAddFilledTriangle(ztDrawList *draw_list, const ztVec3 p[3], const ztVec2 uvs[3], const ztVec3 normals[3]);
bool zt_drawListAddFilledQuad(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3, const ztVec3& p4, const ztVec2& uv1, const ztVec2& uv2, const ztVec2& uv3, const ztVec2& uv4, const ztVec3& n1, const ztVec3& n2, const ztVec3& n3, const ztVec3& n4); // points need to be ccw
bool zt_drawListAddFilledQuad(ztDrawList *draw_list, const ztVec3 p[4], const ztVec2 uvs[4], const ztVec3 normals[4]);
bool zt_drawListAddFilledRect2D(ztDrawList *draw_list, const ztVec2& pos_ctr, const ztVec2& size, const ztVec2& uv_nw, const ztVec2& uv_se);
bool zt_drawListAddFilledRect2D(ztDrawList *draw_list, const ztVec3& pos_ctr, const ztVec2& size, const ztVec2& uv_nw, const ztVec2& uv_se);
bool zt_drawListAddBillboard(ztDrawList *draw_list, const ztVec3& pos_ctr, const ztVec2& size, const ztVec2& uv_nw, const ztVec2& uv_se, i32 flags = ztDrawCommandBillboardFlags_AxisAll);
bool zt_drawListAddFilledPoly(ztDrawList *draw_list, const ztVec3 *p, int count, const ztVec2 uvs[4], const ztVec3 normals[4]);
bool zt_drawListAddDrawList(ztDrawList *draw_list, ztDrawList *draw_list_to_add, const ztVec3& offset = ztVec3::zero);

bool zt_drawListAddFrustum(ztDrawList *draw_list, ztFrustum *frustum);
bool zt_drawListAddFloorGrid(ztDrawList *draw_list, const ztVec3& center, r32 width, r32 depth, r32 grid_w = 1, r32 grid_d = 1);
bool zt_drawListAddVertexArray(ztDrawList *draw_list, ztVertexArrayID vertex_array_id, ztVertexArrayDrawType_Enum draw_type);
bool zt_drawListAddAxis(ztDrawList *draw_list, r32 size = 1, const ztVec3& center = ztVec3::zero, const ztVec4& color_x = ztVec4(1, 0, 0, 1), const ztVec4& color_y = ztVec4(0, 1, 0, 1), const ztVec4& color_z = ztVec4(0, 0, 1, 1));
bool zt_drawListAddAxis(ztDrawList *draw_list, const ztMat4& mat, r32 size = 1, const ztVec3& center = ztVec3::zero, const ztVec4& color_x = ztVec4(1, 0, 0, 1), const ztVec4& color_y = ztVec4(0, 1, 0, 1), const ztVec4& color_z = ztVec4(0, 0, 1, 1));
bool zt_drawListAddPointMarker(ztDrawList *draw_list, const ztVec3& pos, r32 size = 1, bool color_axis = false);

bool zt_drawListPushShader(ztDrawList *draw_list, ztShaderID shader);
bool zt_drawListPopShader(ztDrawList *draw_list);
bool zt_drawListPushColor(ztDrawList *draw_list, const ztColor& color);
bool zt_drawListPopColor(ztDrawList *draw_list);
bool zt_drawListPushTexture(ztDrawList *draw_list, ztTextureID tex_id);
bool zt_drawListPushTexture(ztDrawList *draw_list, ztTextureID *tex_ids, int tex_count);
bool zt_drawListPopTexture(ztDrawList *draw_list);
bool zt_drawListPushClipRegion(ztDrawList *draw_list, ztVec2 center, ztVec2 size); // window coords
bool zt_drawListPopClipRegion(ztDrawList *draw_list);
bool zt_drawListPushDrawFlags(ztDrawList *draw_list, i32 flags);
bool zt_drawListPopDrawFlags(ztDrawList *draw_list);
bool zt_drawListPushOffset(ztDrawList *draw_list, const ztVec3& offset);
bool zt_drawListPopOffset(ztDrawList *draw_list);
bool zt_drawListPushTransform(ztDrawList *draw_list, const ztMat4& transform);
bool zt_drawListPopTransform(ztDrawList *draw_list);

ztShaderID zt_drawListGetCurrentShader(ztDrawList *draw_list);


void zt_drawListReset(ztDrawList *draw_list);

enum ztRenderDrawListFlags_Enum
{
	ztRenderDrawListFlags_NoClear = (1<<0),
	ztRenderDrawListFlags_Wireframe = (1<<1),
	ztRenderDrawListFlags_NoDepthTest = (1<<2),

	zt_debugOnly(ztRenderDrawListFlags_DebugDump = (1<<31))
};

void zt_renderDrawList(ztCamera *camera, ztDrawList *draw_list, const ztColor& clear, i32 flags, ztTextureID render_target_id = ztInvalidID);
void zt_renderDrawLists(ztCamera *camera, ztDrawList **draw_lists, int draw_lists_count, const ztColor& clear, i32 flags, ztTextureID render_target_id = ztInvalidID);


// ------------------------------------------------------------------------------------------------
// lighting

enum ztLightType_Enum
{
	ztLightType_Directional,
	ztLightType_Spot,
	ztLightType_Area,
};

// ------------------------------------------------------------------------------------------------

struct ztLight
{
	ztLightType_Enum type;

	ztVec3 position;
	ztVec3 direction;
	bool casts_shadows;
	
	ztColor color;
	r32 intensity;
	r32 ambient;
};

// ------------------------------------------------------------------------------------------------

ztLight zt_lightMakeDirectional(const ztVec3& pos, const ztVec3& dir, r32 intensity = 1, r32 ambient = .25f, bool casts_shadows = true, const ztColor& color = ztVec4::one);
ztLight zt_lightMakeSpot(const ztVec3& pos, const ztVec3& dir, r32 intensity = 1, bool casts_shadows = true, const ztColor& color = ztVec4::one);
ztLight zt_lightMakeArea(const ztVec3& pos, r32 intensity = 1, bool casts_shadows = true, const ztColor& color = ztVec4::one);



// ------------------------------------------------------------------------------------------------
// models

enum ztModelFlags_Enum
{
	ztModelFlags_NoFaceCull    = (1<<1),
	ztModelFlags_Translucent   = (1<<2),
	ztModelFlags_CastsShadows  = (1<<3),
	ztModelFlags_Hidden        = (1<<4),
	ztModelFlags_OwnsMaterials = (1<<5),
	ztModelFlags_OwnsMesh      = (1<<6),

	// set automically when using internal shaders, but can be set manually
	ztModelFlags_ShaderSupportsDiffuse          = (1<<27),		// "diffuse_tex", "diffuse_color"
	ztModelFlags_ShaderSupportsSpecular         = (1<<28),		// "specular_tex", "specular_color"
	ztModelFlags_ShaderSupportsNormal           = (1<<29),		// "normal_tex"
	ztModelFlags_ShaderSupportsDirectionalLight = (1<<30),		// "light_matrix", "light_pos", "view_pos"

	// toggled and used internally:
	ztSceneModelFlags_Culled = (1 << 31),
};

// ------------------------------------------------------------------------------------------------

struct ztModel
{
	ztMeshID mesh_id;
	ztTransform transform;
	i32 flags;

	ztShaderID shader;
	ztShaderVariableValues *shader_vars;

	ztMaterial material;

	ztModel *first_child;
	ztModel *next;
	ztModel *parent;

	ztMemoryArena *arena;

	ztMat4 calculated_mat;
};

// ------------------------------------------------------------------------------------------------

ztModel *zt_modelMake(ztMemoryArena *arena, ztMeshID mesh_id, ztMaterial *materials, ztShaderID shader, ztShaderVariableValues *shader_vars, i32 flags, ztModel *parent = nullptr);
void zt_modelFree(ztModel *model);

ztModel *zt_modelMakeSkybox(ztMemoryArena *arena, ztTextureID texture_id);

void zt_modelCalcMatrix(ztModel *model);


// ------------------------------------------------------------------------------------------------
// scenes

enum ztSceneModelFlags_Enum
{
	ztSceneModelFlags_ShaderLit      = (1<<1),
	ztSceneModelFlags_HasTranslucent = (1<<2),
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_SCENE_MAX_LIGHTS
#define ZT_SCENE_MAX_LIGHTS	4
#endif

// ------------------------------------------------------------------------------------------------

struct ztScene
{
	struct ModelInfo
	{
		ztModel *model;
		i32 flags;
		r32 dist_from_cam;
	};

	ModelInfo *models;
	int models_count;
	int models_size;

	struct LightInfo
	{
		ztLight *light;
	};

	LightInfo directional_light;
	LightInfo lights[ZT_SCENE_MAX_LIGHTS];

	ModelInfo skybox;

	ztMemoryArena *arena;

	ztTextureID tex_directional_shadow_map;
};

// ------------------------------------------------------------------------------------------------

struct ztSceneLightingRules
{
	r32 shadow_max_distance = 50.f;
};

// ------------------------------------------------------------------------------------------------

ztScene *zt_sceneMake(ztMemoryArena *arena, int max_models = 1024, int shadow_map_res = 4096);
void zt_sceneFree(ztScene *scene);
void zt_sceneFreeAllModels(ztScene *scene);

void zt_sceneAddLight(ztScene *scene, ztLight *light);
void zt_sceneSetSkybox(ztScene *scene, ztModel *skybox);

void zt_sceneAddModel(ztScene *scene, ztModel *model);
void zt_sceneRemoveModel(ztScene *scene, ztModel *model);
bool zt_sceneHasModel(ztScene *scene, ztModel *model);

// --------------------------------------------------------
// Calculates matrices for scene models (should be called after physics)
void zt_scenePrepare(ztScene *scene, ztCamera *camera);

// --------------------------------------------------------
// Culls models and lights based on camera view (not absolutely necessary)
void zt_sceneOptimize(ztScene *scene, ztCamera *camera);

// --------------------------------------------------------
// Generate shadow maps for non-culled lights
void zt_sceneLighting(ztScene *scene, ztCamera *camera, ztSceneLightingRules *lighting_rules = nullptr);

void zt_sceneRender(ztScene *scene, ztCamera *camera, ztSceneLightingRules *lighting_rules = nullptr);


// ------------------------------------------------------------------------------------------------
// renderer functions

bool zt_rendererSupported(ztRenderer_Enum renderer);
int zt_rendererSupportedList(ztRenderer_Enum* renderers, int renderers_count);

bool zt_rendererVersionSupported(ztRenderer_Enum renderer, i32 v_major, i32 v_minor);
bool zt_rendererGetMaxVersionSupported(ztRenderer_Enum renderer, i32* v_major, i32* v_minor);

void zt_rendererClear(r32 r, r32 g, r32 b, r32 a);
void zt_rendererClear(ztVec4 clr);

enum ztRendererDepthTestFunction_Enum
{
	ztRendererDepthTestFunction_Never,
	ztRendererDepthTestFunction_Less,
	ztRendererDepthTestFunction_LessEqual,
	ztRendererDepthTestFunction_Equal,
	ztRendererDepthTestFunction_Greater,
	ztRendererDepthTestFunction_NotEqual,
	ztRendererDepthTestFunction_GreaterEqual,
	ztRendererDepthTestFunction_Always,
};

void zt_rendererSetDepthTest(bool depth_test, ztRendererDepthTestFunction_Enum function);

enum ztRendererFaceCulling_Enum
{
	ztRendererFaceCulling_CullBack,
	ztRendererFaceCulling_CullFront,
	ztRendererFaceCulling_CullNone,
};

void zt_rendererSetFaceCulling(ztRendererFaceCulling_Enum culling);

void zt_rendererRequestChange(ztRenderer_Enum renderer);
void zt_rendererRequestWindowed();
void zt_rendererRequestFullscreen();

void zt_alignToPixel(r32 *val, r32 ppu, r32 *offset = nullptr);
void zt_alignToPixel(ztVec2 *val, r32 ppu);
void zt_alignToPixel(ztVec3 *val, r32 ppu);


// ------------------------------------------------------------------------------------------------
// fonts

typedef i32 ztFontID;

const char *zt_fontGetCharsetStandard( i32 *size );

ztFontID zt_fontMakeFromTrueTypeAsset(ztAssetManager *asset_mgr, ztAssetID asset_id, i32 size_in_pixels, const char *charset = nullptr, i32 charset_size = 0);
ztFontID zt_fontMakeFromTrueTypeFile(const char *file_name, i32 size_in_pixels, const char *charset = nullptr, i32 charset_size = 0);
ztFontID zt_fontMakeFromBmpFontAsset(ztAssetManager *asset_mgr, ztAssetID asset_id, ztAssetID texture_override_asset_id = ztInvalidID, const ztVec2& override_offset = ztVec2::zero);
ztFontID zt_fontMakeFromBmpFontFile(const char *file_name, ztTextureID texture_override_id = ztInvalidID, const ztVec2& override_offset = ztVec2::zero);
ztFontID zt_fontMakeFromBmpFontData(const char *file_data, ztTextureID texture_override_id, const ztVec2& override_offset = ztVec2::zero);
void zt_fontFree(ztFontID font_id);

const char *zt_fontGetName(ztFontID font_id);
i32 zt_fontGetSizeInPixels(ztFontID font_id);

ztVec2 zt_fontGetExtents(ztFontID font_id, const char *text);
ztVec2 zt_fontGetExtents(ztFontID font_id, const char *text, int text_len);

void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);
void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);

void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, ztVec2 scale, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);
void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, ztVec2 scale, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);

// fancy fonts allows colors to be added in the middle of text using the format:
// "This text is <color=ff0000ff>red</color> text.
// be sure to avoid spaces in the color specifier

ztVec2 zt_fontGetExtentsFancy(ztFontID font_id, const char *text);
ztVec2 zt_fontGetExtentsFancy(ztFontID font_id, const char *text, int text_len);

void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);
void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);

void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, ztVec2 scale, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);
void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, ztVec2 scale, i32 align_flags = ztAlign_Default, i32 anchor_flags = ztAnchor_Default, ztVec2 *extents = nullptr);

// ------------------------------------------------------------------------------------------------
// sprites

struct ztSprite
{
	ztTextureID tex;
	ztVec4 tex_uv;
	ztVec2 half_size;
	ztVec2 anchor;
};

ztSprite zt_spriteMake(ztTextureID tex, int x, int y, int w, int h, int anchor_x = 0, int anchor_y = 0);
ztSprite zt_spriteMake(ztTextureID tex, ztPoint2 pos, ztPoint2 size, ztPoint2 anchor = ztPoint2(0, 0));
ztSprite zt_spriteMakeFromGrid(ztTextureID tex, int x, int y, int w, int h, int anchor_x = 0, int anchor_y = 0);
ztSprite zt_spriteMakeFromGrid(ztTextureID tex, ztPoint2 pos, ztPoint2 size, ztPoint2 anchor = ztPoint2(0, 0));

void zt_drawListAddSprite(ztDrawList *draw_list, ztSprite *sprite, const ztVec3& pos);
void zt_drawListAddSprite(ztDrawList *draw_list, ztSprite *sprite, const ztVec3& pos, const ztVec3& rot, const ztVec3& scale);

// ------------------------------------------------------------------------------------------------

struct ztSpriteNineSlice
{
	ztTextureID tex;
	ztVec4 sp_nw, sp_n, sp_ne, sp_w, sp_c, sp_e, sp_sw, sp_s, sp_se;
	r32 sz_n, sz_s, sz_e, sz_w, sz_cw, sz_ch;

	ztVec4 offset;
};

ztSpriteNineSlice zt_spriteNineSliceMake(ztTextureID tex, int tex_x, int tex_y, int tex_w, int tex_h, int nw_interior_x, int nw_interior_y, int se_interior_x, int se_interior_y, int offset_l = 0, int offset_t = 0, int offset_r = 0, int offset_b = 0);
ztSpriteNineSlice zt_spriteNineSliceMake(ztTextureID tex, ztPoint2 tex_pos, ztPoint2 tex_size, ztPoint2 nw_interior, ztPoint2 se_interior, int offset_l = 0, int offset_t = 0, int offset_r = 0, int offset_b = 0);

void zt_drawListAddSpriteNineSlice(ztDrawList *draw_list, ztSpriteNineSlice *sns, const ztVec2& pos, const ztVec2& size);


// ------------------------------------------------------------------------------------------------
// physics

enum ztCollisionGeometryType_Enum
{
	ztCollisionGeometryType_AxisAlignedBox,
	ztCollisionGeometryType_OrientedBox,
	ztCollisionGeometryType_Sphere,
	
	ztCollisionGeometryType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztCollisionGeometry
{
	ztCollisionGeometryType_Enum type;

	union
	{
		struct {
			ztVec3 aabb_extents;
		};

		struct {
			ztVec3 obb_center;
			ztVec3 obb_extents;
		};

		struct {
			ztVec3 sphere_center;
			r32    sphere_radius;
		};
	};
};


// ------------------------------------------------------------------------------------------------

ztCollisionGeometry zt_collisionGeometryMakeAABB(const ztVec3& extents);
ztCollisionGeometry zt_collisionGeometryMakeOBB(const ztVec3& center, const ztVec3& extents);
ztCollisionGeometry zt_collisionGeometryMakeSphere(const ztVec3& center, r32 radius);

bool zt_collisionGeometryIntersecting(ztCollisionGeometry *geo_one, ztTransform *curr_tran_one, ztTransform *prev_tran_one, ztCollisionGeometry *geo_two, ztTransform *curr_tran_two, ztTransform *prev_tran_two, r32 *penetration);

// ------------------------------------------------------------------------------------------------

enum ztRigidBodyFlags_Enum
{
	ztRigidBodyFlags_NeedsMatrixCalc = (1<<0),

};

#ifndef ZT_MAX_RIGID_BODY_COLLISION_GEOMETRIES
#define ZT_MAX_RIGID_BODY_COLLISION_GEOMETRIES 4
#endif

#pragma pack(push, 1)
struct ztRigidBody
{
	ztModel *model;

	ztVec3   velocity;
	ztVec3   angular_velocity;
	ztVec3   acceleration;
	ztVec3   force_accum;
	ztVec3   torque_accum;

	r32      damping;
	r32      angular_damping;
	r32      inverse_mass;

	ztVec3   force_gravity;

	ztVec3   prev_acceleration;

	i32      flags;

	i8       collision_layer;        // 1-31
	i32      collides_with_layers;   // bits to determine which layers this body, when moving, can collide with

	ztCollisionGeometry  cg_bounding;
	ztCollisionGeometry  cg_details[ZT_MAX_RIGID_BODY_COLLISION_GEOMETRIES];
	int                  cg_details_count;
};
#pragma pack(pop)

// ------------------------------------------------------------------------------------------------

#define ztRigidBodyDampingDefaults_Low      .99f
#define ztRigidBodyDampingDefaults_Medium   .50f
#define ztRigidBodyDampingDefaults_High     .01f

#define ztRigidBodyMass_Infinite      0

#ifndef ZT_RIGID_BODY_DEFAULT_GRAVITY
#define ZT_RIGID_BODY_DEFAULT_GRAVITY ztVec3(0, -9.8f, 0)
#endif

// ------------------------------------------------------------------------------------------------

ztRigidBody zt_rigidBodyMake(ztModel *model, r32 one_over_mass_in_kg, ztCollisionGeometry cg_bounding, ztCollisionGeometry *details, int details_count, r32 damping = ztRigidBodyDampingDefaults_Medium, ztVec3 force_gravity = ZT_RIGID_BODY_DEFAULT_GRAVITY);
ztRigidBody zt_rigidBodyMake(ztModel *model, r32 one_over_mass_in_kg, ztCollisionGeometry cg_bounding, ztCollisionGeometry detail, r32 damping = ztRigidBodyDampingDefaults_Medium, ztVec3 force_gravity = ZT_RIGID_BODY_DEFAULT_GRAVITY);

void zt_rigidBodiesUpdate(ztRigidBody *rbs, int rbs_count, r32 dt);

void zt_rigidBodyAddForce(ztRigidBody *rigid_body, const ztVec3& force);
void zt_rigidBodyAddForceAtWorldPoint(ztRigidBody *rigid_body, const ztVec3& force, const ztVec3& point);
void zt_rigidBodyAddForceAtBodyPoint(ztRigidBody *rigid_body, const ztVec3& force, const ztVec3& point);


// ------------------------------------------------------------------------------------------------

enum ztForceAnchorType_Enum
{
	ztForceAnchorType_RigidBody,
	ztForceAnchorType_Transform,
	ztForceAnchorType_Vec3Ptr,
	ztForceAnchorType_Vec3,

	ztForceAnchorType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztForceAnchor
{
	ztForceAnchorType_Enum type;

	union {
		struct {
			ztRigidBody *rigid_body;
			ztVec3       connection_point;
		};

		ztTransform *transform;
		struct { ztVec3 *vec3_ptr; };
		struct { ztVec3  vec3; };
	};
};

// ------------------------------------------------------------------------------------------------

ztForceAnchor zt_forceAnchor(ztRigidBody *rigid_body, const ztVec3& connection_point = ztVec3::zero);
ztForceAnchor zt_forceAnchor(ztTransform *transform);
ztForceAnchor zt_forceAnchor(ztVec3 *vec3_ptr);
ztForceAnchor zt_forceAnchor(ztVec3 vec3);


// ------------------------------------------------------------------------------------------------

enum ztForceType_Enum
{
	ztForceType_Spring,
	ztForceType_StiffSpring,
	ztForceType_Bungee,
	ztForceType_Buoyancy,

	ztForceType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztForce
{
	ztForceType_Enum type;

	ztRigidBody *rigid_body;
	ztVec3       connection_point;

	ztForceAnchor anchor;

	union {
		struct {
			r32 spring_constant;
			r32 rest_length;
		} spring;

		struct {
			r32 spring_constant;
			r32 damping;
		} stiff_spring;

		struct {
			r32 max_depth;
			r32 volume;
			r32 water_height;
			r32 liquid_density; // water density is 1000 kg/cubic meter
		} buoyancy;
	};
};

// ------------------------------------------------------------------------------------------------

ztForce zt_forceMakeSpring      (ztRigidBody *rigid_body, const ztVec3& connection_point, ztForceAnchor anchor, r32 spring_constant, r32 rest_length);
ztForce zt_forceMakeStiffSpring (ztRigidBody *rigid_body, const ztVec3& connection_point, ztForceAnchor anchor, r32 spring_constant, r32 damping);
ztForce zt_forceMakeBungee      (ztRigidBody *rigid_body, const ztVec3& connection_point, ztForceAnchor anchor, r32 spring_constant, r32 rest_length);
ztForce zt_forceMakeBuoyancy    (ztRigidBody *rigid_body, const ztVec3& connection_point, r32 max_depth, r32 volume, r32 water_height = 0, r32 liquid_density = 1000.f);

void zt_forcesUpdate(ztForce *forces, int forces_count, r32 dt);


// ------------------------------------------------------------------------------------------------
// collisions

struct ztRigidBodyCollision
{
	ztRigidBody *rigid_bodies[2];

	r32          restitution;
	ztVec3       contact_normal;
	r32          penetration;
};

void zt_rigidBodyCollisionsResolve(ztRigidBodyCollision *collisions, int collisions_count, r32 dt, int max_iterations);


// ------------------------------------------------------------------------------------------------
// connectors

enum ztConnectorType_Enum
{
	ztConnectorType_Cable,
	ztConnectorType_Rod,

	ztConnectorType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztConnector
{
	ztConnectorType_Enum type;

	ztRigidBody *rigid_bodies[2];

	union {
		struct {
			r32 max_length;
			r32 restitution;

		} cable;

		struct {
			r32 length;
		} rod;
	};
};

// ------------------------------------------------------------------------------------------------

ztConnector zt_connectorMakeCable(r32 max_length, r32 restitution);
ztConnector zt_connectorMakeRod(r32 length);

int zt_connectorCalculateCollisions(ztConnector *connectors, int connectors_count, ztRigidBodyCollision *collisions, int collisions_size);


// ------------------------------------------------------------------------------------------------

int zt_collisionBrute(ztRigidBody *rigid_bodies, int rigid_bodies_count, ztRigidBodyCollision *collisions, int collisions_size);


// ------------------------------------------------------------------------------------------------

// rects have a center and a size
// the LL functions use a rect with the x/y point being the lower left corner

bool zt_collisionPointInRect(const ztVec2& point, const ztVec2& rect_pos, const ztVec2& rect_size);
bool zt_collisionPointInRect(r32 p_x, r32 p_y, r32 rect_x, r32 rect_y, r32 rect_w, r32 rect_h);
bool zt_collisionPointInRectLL(const ztVec2& point, const ztVec2& rect_pos, const ztVec2& rect_size);
bool zt_collisionPointInRectLL(r32 p_x, r32 p_y, r32 rect_x, r32 rect_y, r32 rect_w, r32 rect_h);

bool zt_collisionLineInPlane(const ztVec3& line_beg, const ztVec3& line_end, const ztVec3& plane_coord, const ztVec3& plane_normal, ztVec3 *intersection_point = nullptr);

bool zt_collisionPointInAABB(const ztVec3& point, const ztVec3& aabb_center, const ztVec3& aabb_extents);
bool zt_collisionRayInAABB(const ztVec3& point, const ztVec3& direction, const ztVec3& aabb_center, const ztVec3& aabb_extents, ztVec3 *intersection_point = nullptr);
bool zt_collisionLineSegmentInAABB(const ztVec3& line_0, const ztVec3& line_1, const ztVec3& aabb_center, const ztVec3& aabb_extents, ztVec3 intersection_points[2] = nullptr);
bool zt_collisionAABBInAABB(const ztVec3& aabb_center_1, const ztVec3& aabb_extents_1, const ztVec3& aabb_center_2, const ztVec3& aabb_extents_2);
bool zt_collisionAABBInPlane(const ztVec3& aabb_center_1, const ztVec3& aabb_extents_1, const ztVec3& plane_coord, const ztVec3& plane_normal, ztVec3 *intersection_point = nullptr);

bool zt_collisionOBBInOBB(const ztVec3& obb_center_1, const ztVec3& obb_extents_1, const ztQuat& obb_rot_1, const ztVec3& obb_center_2, const ztVec3& obb_extents_2, const ztQuat& obb_rot_2);
bool zt_collisionOBBInOBB(const ztVec3& obb_center_1, const ztVec3& obb_extents_1, const ztVec3 obb_axis_1[3], const ztVec3& obb_center_2, const ztVec3& obb_extents_2, const ztVec3 obb_axis_2[3]);
int zt_collisionOBBInOBBGetContactPoints(const ztVec3& obb_center_1, const ztVec3& obb_extents_1, const ztQuat& obb_rot_1, const ztVec3& obb_center_2, const ztVec3& obb_extents_2, const ztQuat& obb_rot_2, ztVec3 *contacts, int contacts_size);
bool zt_collisionLineSegmentInOBB(const ztVec3& line_0, const ztVec3& line_1, const ztVec3& obb_center, const ztVec3& obb_extents, const ztQuat& obb_rot, ztVec3 intersections[2] = nullptr);



// ------------------------------------------------------------------------------------------------
// physics manager

struct ztPhysics
{
	ztRigidBody          *rigid_bodies;
	int                   rigid_bodies_size;
	int                   rigid_bodies_count;

	ztForce              *forces;
	int                   forces_size;
	int                   forces_count;

	ztConnector          *connectors;
	int                   connectors_size;
	int                   connectors_count;

	ztRigidBodyCollision *collisions;
	int                   collisions_size;

	ztVec3 extents_min;
	ztVec3 extents_max;
	r32    extents_restitution;


	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

ztPhysics *zt_physicsMake(ztMemoryArena *arena, int max_rigid_bodies, int max_forces, int max_connectors);
void zt_physicsFree(ztPhysics *physics);

// these return indexes into the respective arrays
int zt_physicsAddRigidBody (ztPhysics *physics, ztRigidBody *rigid_body);
int zt_physicsAddForce     (ztPhysics *physics, ztForce *force);
int zt_physicsAddConnector (ztPhysics *physics, ztConnector *connector);

void zt_physicsUpdate(ztPhysics *physics, r32 dt);


// ------------------------------------------------------------------------------------------------
// tweening

#define ZT_FUNC_TWEEN_EASE(name)	r32 name(r32 value, void *user_data)
typedef ZT_FUNC_TWEEN_EASE(ztTweenEase_Func);

ZT_FUNC_TWEEN_EASE(zt_tweenEaseLinear  );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseBack    );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseBounce  );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseCirc    );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseCubic   );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseElastic );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseExpo    );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseQuad    );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseQuart   );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseQuint   );
ZT_FUNC_TWEEN_EASE(zt_tweenEaseSine    );

r32 zt_tweenValue(r32 val_beg, r32 val_end, r32 percent, ztTweenEase_Func *ease_in, ztTweenEase_Func *ease_out);
r32 zt_tweenValue(r32 val_beg, r32 val_end, r32 percent, ztTweenEase_Func *ease_in, void *ease_in_user_data, ztTweenEase_Func *ease_out, void *ease_out_user_data);

ztVec2 zt_tweenValue(const ztVec2& val_beg, const ztVec2& val_end, r32 percent, ztTweenEase_Func *ease_in, ztTweenEase_Func *ease_out);
ztVec2 zt_tweenValue(const ztVec2& val_beg, const ztVec2& val_end, r32 percent, ztTweenEase_Func *ease_in, void *ease_in_user_data, ztTweenEase_Func *ease_out, void *ease_out_user_data);

ztVec3 zt_tweenValue(const ztVec3& val_beg, const ztVec3& val_end, r32 percent, ztTweenEase_Func *ease_in, ztTweenEase_Func *ease_out);
ztVec3 zt_tweenValue(const ztVec3& val_beg, const ztVec3& val_end, r32 percent, ztTweenEase_Func *ease_in, void *ease_in_user_data, ztTweenEase_Func *ease_out, void *ease_out_user_data);

// ------------------------------------------------------------------------------------------------
// animation


// ------------------------------------------------------------------------------------------------
// ztAnimKey
// 
// Represents a single key frame in an animation.  Can point to any ztVariant value.

struct ztAnimKey
{
	ztVariantPointer      target;

	ztVariant             value_beg;
	ztVariant             value_end;

	r32                   time;
};

// ------------------------------------------------------------------------------------------------

ztAnimKey zt_animKeyMake(ztVariantPointer target, ztVariant value_beg, ztVariant value_end, r32 time);


// ------------------------------------------------------------------------------------------------
// ztAnimLayer
//
// Represents a collection of key frames for a single variable

enum ztAnimLayerState_Enum
{
	ztAnimLayerState_Sleeping,
	ztAnimLayerState_Transitioning,
	ztAnimLayerState_Playing,
};


struct ztAnimLayer
{
	ztAnimKey            *keys;
	int                   keys_count;

	ztAnimLayerState_Enum state;
	int                   current_key;
	r32                   current_time;

	ztVariant             value_beg;
	ztVariant             value_end;
	r32                   target_time;
};

// ------------------------------------------------------------------------------------------------

ztAnimLayer zt_animLayerMake(ztAnimKey *keys, int keys_count);
void        zt_animLayerFree(ztAnimLayer *layer);


// ------------------------------------------------------------------------------------------------
// ztAnimSequence
//
// Represents a group of layers combined together, such as a walking animation that has
// arms, legs and bodies all keyframed together

enum ztAnimSequenceType_Enum
{
	ztAnimSequenceType_Synchronous,     // only one of these can be running at the same time (running, jumping, idle, etc)
	ztAnimSequenceType_Asynchronous,    // any number of these can be running at the same time (blinking, breathing, talking)

	ztAnimSequenceType_MAX,
};

// ------------------------------------------------------------------------------------------------

enum ztAnimTransition_Enum
{
	ztAnimTransition_Snap,      // the target value snaps to the beginning value at the start of the animation
	ztAnimTransition_Interp,    // the target value will move to the beginning value over the transition time
};

// ------------------------------------------------------------------------------------------------

struct ztAnimSequence
{
	ztAnimSequenceType_Enum type;

	ztAnimLayer            *layers;
	int                     layers_count;

	ztAnimTransition_Enum   transition_type;
	r32                     transition_time;

	bool                    loops;
};

// ------------------------------------------------------------------------------------------------

ztAnimSequence *zt_animSequenceMake(ztAnimSequenceType_Enum type, ztAnimLayer *layers, int layers_count, ztAnimTransition_Enum transition_type, r32 transition_time, bool loops);
void            zt_animSequenceFree(ztAnimSequence *sequence);

r32             zt_animSequencePercentComplete(ztAnimSequence *sequence);


// ------------------------------------------------------------------------------------------------
// ztAnimController
//
// Represents a collection of animation sequences for a single actor/game object

// ------------------------------------------------------------------------------------------------

struct ztAnimController
{
	i32              *sequences_name_hash;
	ztString         *sequences_name;
	ztAnimSequence  **sequences;
	int               sequences_size;
	int               sequences_count;

	ztAnimSequence   *anim_sync;
	ztAnimSequence  **anim_async;
	int               anim_async_count;

	i32               queued;
};

// ------------------------------------------------------------------------------------------------

ztAnimController *zt_animControllerMake(int max_sequences, int max_async = 4);
void              zt_animControllerFree(ztAnimController *controller);
i32               zt_animControllerAddSequence(ztAnimController *controller, const char *sequence_name, ztAnimSequence *sequence);
int               zt_animControllerStartSequence(ztAnimController *controller, i32 anim_sequence_hash);
void              zt_animControllerUpdate(ztAnimController **controllers, int controllers_count, r32 dt);


// ------------------------------------------------------------------------------------------------
// sprite animation

struct ztSpriteAnimController
{
	struct Sequence
	{
		ztSprite *sprites;
		int       sprites_size;
		int       current_sprite;
	};

	Sequence         *sequences;
	int               sequences_size;
	int               sequences_count;

	int               active_sequence;

	ztAnimController *controller;
};

// ------------------------------------------------------------------------------------------------

ztSpriteAnimController *zt_spriteAnimControllerMake(int max_sequences);
void zt_spriteAnimControllerFree(ztSpriteAnimController *controller);

void zt_spriteAnimControllerAddSequence(ztSpriteAnimController *controller, const char *sequence_name, ztSprite *sprites, r32 *times, int sprites_count, bool loops);
void zt_spriteAnimControllerStartSequence(ztSpriteAnimController *controller, i32 sequence_name_hash);
void zt_spriteAnimControllerUpdate(ztSpriteAnimController **controllers, int controllers_count, r32 dt);

ztSprite *zt_spriteAnimControllerActiveSprite(ztSpriteAnimController *controller);


// ------------------------------------------------------------------------------------------------
// Particles

struct ztParticleEmitterSettings
{
	ztVec3  origin;
	ztVec3  size;

	r32     emission_rate;               // particles per second

	r32     lifetime;                    // particle lifetime
	r32     lifetime_random;             // 0 = no randomness, 1 = complete randomness (lifetime is max, so .5 would be from half lifetime to lifetime)

	r32     velocity_speed;              // units per second
	r32     velocity_speed_random;       // 0 = no randomness, 1 = complete randomness (0 - velocity_speed)

	r32     velocity_angle;              // 0 up, 90, right, 180 down, 270 left
	r32     velocity_angle_random;       // 0 = no randomness, 1 = complete randomness (0-360, percentage is based off angle (.125 on a 90 angle would be 45-135)

	r32     rotation;                    // rotation amount for each particle per second
	r32     rotation_random;             // 0 = no randomness, 1 = complete randomness (0-360)

	r32     scale;                       // scale amount for each particle
	r32     scale_random;                // 0 = no randomness, 1 = complete randomness (0-scale)

	ztVec3  gravity_velocity;

	ztVec4  color_life_begin;
	ztVec4  color_life_end;

	bool    random_rotation;            // particles are randomly rotated
	bool    local_space;                // particles position relative to emitter origin
	bool    burst_emit;                 // emit all particles at once

	bool    enabled;

	r32     emitter_lifetime;           // 0 = persistent, otherwise life in seconds
};

// ------------------------------------------------------------------------------------------------

struct ztParticle
{
	ztTransform transform;
	r32         life;
	r32         speed;
	r32         angle;
	r32         rotation;
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_PARTICLES
#define ZT_MAX_PARTICLES	500
#endif

// ------------------------------------------------------------------------------------------------

struct ztParticleEmitter2D
{
	ztParticleEmitterSettings settings;

	ztSprite                  sprite;

	ztParticle                particles[ZT_MAX_PARTICLES];
	int                       particles_count;

	i32                       live_particles;

	r32                       time_between_particles;
	r32                       time_last_particle;

	ztRandom                  randomizer;
};

// ------------------------------------------------------------------------------------------------

ztParticleEmitter2D  zt_particleEmitter2DMake(ztParticleEmitterSettings *settings, ztSprite *sprite, i32 seed);
bool                 zt_particleEmitter2DUpdate(ztParticleEmitter2D *emitter, r32 dt); // returns false when emitter is exhausted
void                 zt_particleEmitter2DRender(ztParticleEmitter2D *emitter, ztDrawList *draw_list);

// ------------------------------------------------------------------------------------------------
// Pathfinding

#ifndef ZT_PATH_NODE_MAX_NEIGHBORS
#define ZT_PATH_NODE_MAX_NEIGHBORS 16
#endif

#define ztPathNodeValue_Reset       -1
#define ztPathNodeValue_Impassable  -100


// ------------------------------------------------------------------------------------------------

enum ztPathNodeFlags_Enum
{
	ztPathNodeFlags_Ignore      = (1<<0),
	ztPathNodeFlags_Waypoint    = (1<<1),
	ztPathNodeFlags_Obstructed  = (1<<2),
};

// ------------------------------------------------------------------------------------------------

struct ztPathNode
{
	ztVec3      position; // not necessarily world coords, but used to determine node distances
	void       *user_data; // passed to the path cost function
	u8          flags;

	ztPathNode *neighbors[ZT_PATH_NODE_MAX_NEIGHBORS];
	int         neighbors_count;

	r32        _my_move_cost;
};

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_PATH_NODE_COST(name)   r32 name(ztPathNode *origin, ztPathNode *destination, void *user_data)
typedef ZT_FUNC_PATH_NODE_COST(ztPathNodeCost_Func);


// ------------------------------------------------------------------------------------------------

struct ztPathGridSquare
{
	int rows;
	int cols;

	ztPathNode *nodes;
};

ztPathGridSquare *zt_pathGridSquareMake(int rows, int cols, bool allow_diagonals);
void              zt_pathGridSquareFree(ztPathGridSquare *grid);
ztPathNode       *zt_pathGridSquareAccessNode(ztPathGridSquare *grid, int row, int col);
bool              zt_pathGridSquareGetCoords(ztPathGridSquare *grid, ztPathNode *node, int *row, int *col);
bool              zt_pathGridSquareGetNodeIndex(ztPathGridSquare *grid, ztPathNode *node, int *index);
r32               zt_pathNodeGetDistance(ztPathNode *node_one, ztPathNode *node_two);
ztPathNode       *zt_pathGridSquareGetNode(ztPathGridSquare *grid, int col, int row);

struct ztPathProgress;
void zt_pathGridSquarePrepareForPathfinding(ztPathGridSquare *grid, ztPathProgress *progress);


// ------------------------------------------------------------------------------------------------

struct ztPathProgress
{
	ztPathNode    *origin;
	ztPathNode    *destination;

	ztPathNode   **frontier;
	int            frontier_len;

	ztPathNode   **visited;
	int            visited_len;

	ztPathNode   **path;
	int            path_size;
	int            path_count;

	int            frontier_idx;
	int            visited_idx;

	ztMemoryArena *arena;
};

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_PATH_EARLY_EXIT(name)	bool name(ztPathProgress *progress, void *user_data);
typedef ZT_FUNC_PATH_EARLY_EXIT(ztPathEarlyExit_Func);

// ------------------------------------------------------------------------------------------------

ztPathProgress *zt_pathProgressMake(ztPathGridSquare *grid, ztMemoryArena *arena);
void zt_pathProgressFree(ztPathProgress *progress);

// ------------------------------------------------------------------------------------------------

enum ztPathType_Enum
{
	ztPathType_Dijkstra,  // dijkstra's algorithm - prioritize by movement cost
	ztPathType_Heuristic, // heuristic search - prioritize by distance from goal
	ztPathType_Astar,     // a* uses both movement cost and distance from goal

	ztPathType_MAX,
};

// ------------------------------------------------------------------------------------------------

int zt_pathCalculatePath(ztPathProgress *progress, ztPathNodeCost_Func *path_node_cost_func, void *path_cost_user_data, ztPathEarlyExit_Func *early_exit_func, void *early_exit_user_data, ztPathType_Enum path_type);



// ------------------------------------------------------------------------------------------------
// audio

typedef i32 ztAudioClipID;

ztAudioClipID zt_audioClipMake(ztAssetManager *asset_mgr, ztAssetID asset_id);
ztAudioClipID zt_audioClipMakeFromFile(const char *file_name);

void zt_audioClipFree(ztAudioClipID audio_clip_id);

void zt_audioClipPlayOnce(ztAudioClipID audio_clip_id);
void zt_audioClipPlayLooped(ztAudioClipID audio_clip_id);

bool zt_audioClipIsPlaying(ztAudioClipID audio_clip_id);
bool zt_audioClipStop(ztAudioClipID audio_clip_id);

void zt_audioSetMute(bool mute);
bool zt_audioGetMute();



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_DLL_SET_GAME_GLOBALS(name) void name(void *memory, int version)
typedef ZT_FUNC_DLL_SET_GAME_GLOBALS(zt_dllSetGameGlobals_Func);

#if !defined(ZT_DLL)

#if defined(ZT_OPENGL)
void zt_dllSendGameGlobals(zt_dllSetGameGlobals_Func *set_globals, zt_dllSetOpenGLGlobals_Func *set_globals_opengl);
#else
void zt_dllSendGameGlobals(zt_dllSetGameGlobals_Func *set_globals);
#endif
#endif


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

#if defined(ZT_GAME_IMPLEMENTATION) || defined(ZT_GAME_INTERNAL_DECLARATIONS)

#ifndef __zt_game_h_internal_included__
#define __zt_game_h_internal_included__

// configure renderers
#if defined(ZT_OPENGL)
#	define zt_openGLSupport(code) code
#	define zt_noOpenGLSupport(code)
#else
#	define zt_openGLSupport(code)
#	define zt_noOpenGLSupport(code) code
#endif

#if defined(ZT_DIRECTX)
#	define zt_directxSupport(code) code
#	define zt_noDirectxSupport(code)
#else
#	define zt_directxSupport(code)
#	define zt_noDirectxSupport(code) code
#endif

#if defined(ZT_DSOUND)
#	define zt_dsoundSupport(code) code
#	define zt_noDsoundSupport(code)
#else
#	define zt_dsoundSupport(code)
#	define zt_noDsoundSupport(code) code
#endif


// ------------------------------------------------------------------------------------------------
// Windows implementation

#if defined(ZT_WINDOWS)

// headers (strive to avoid including anything if possible)
#include <windows.h>
#include <windowsx.h>
#include <xinput.h>

#endif // ZT_WINDOWS

#if !defined(ZT_NO_OPENGL)
#define ZT_OPENGL_IMPLEMENTATION
#include "zt_opengl.h"
#endif

#if !defined(ZT_NO_DIRECTX)
#define ZT_DIRECTX_IMPLEMENTATION
#include "zt_directx.h"
#endif

#if !defined(ZT_NO_DSOUND)
#define ZT_DSOUND_IMPLEMENTATION
#include "zt_dsound.h"
#endif


// ------------------------------------------------------------------------------------------------
#if defined(ZT_WINDOWS)

struct ztWindowDetails
{
	RECT client_rect;
	RECT window_rect;
	ztVec4 client_rect_buffer;
	HWND handle;

	int screen_w, screen_h;

	zt_openGLSupport(ztContextGL *gl_context);
	zt_directxSupport(ztContextDX *dx_context);
	zt_directxSupport(ztVertexArrayDX *dx_tri_verts_array);
};

#endif // ZT_WINDOWS
// ------------------------------------------------------------------------------------------------

struct ztProfiledThread;

// ------------------------------------------------------------------------------------------------

struct ztProfiledSection
{
	const char        *section;
	i32                section_hash;

	r64                time_begin;
	r64                time_accum;
	int                called;

	ztProfiledSection  *parent;
	ztProfiledSection  *children;
	ztProfiledSection  *next;

	ztProfiledThread  *thread;
};

// ------------------------------------------------------------------------------------------------

struct ztProfiledThread
{
	ztProfiledSection  *root;                           // the first section in this frame
	ztProfiledSection  *current;                        // the most recently active section

	ztProfiledSection **allocations;                    // an allocated chunk of profiled sections for a series of past frames
	ztProfiledSection **roots;                          // roots for each saved frame
	int                *sections;                       // total sections used for each saved frame

	int                 allocations_current_frame;      // current section in the current frame
	int                 allocations_current_section;    // current section in the current frame
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_THREADS
#define ZT_MAX_THREADS	5
#endif

#ifndef ZT_PROFILER_FRAMES_KEPT
#define ZT_PROFILER_FRAMES_KEPT		180
#endif

#ifndef ZT_PROFILER_MAX_SECTIONS_PER_FRAME
#define ZT_PROFILER_MAX_SECTIONS_PER_FRAME	128
#endif

// ------------------------------------------------------------------------------------------------

struct ztProfiler
{
	bool             paused;
	ztProfiledThread threads[ZT_MAX_THREADS];

	int              current_frame;      // current frame we're using
};


// ------------------------------------------------------------------------------------------------

#define ZT_THREAD_JOB_QUEUE_SIZE		256

// ------------------------------------------------------------------------------------------------

enum ztThreadJobType_Enum
{
	ztThreadJobType_Frame,
	ztThreadJobType_Background,

	ztThreadJobType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztThreadJob
{
	ztThreadJobID         id;
	ztThreadJobType_Enum  type;
	ztThread_Func        *thread_func;
	void                 *thread_func_user_data;
	r32                   anticipated_length;

	ztAtomicBool          completed;
	ztAtomicBool          cancelled;

	ztThreadJob          *next;
};

// ------------------------------------------------------------------------------------------------

struct ztThreadJobThreadData
{
	ztThread            *thread;
	ztThreadID           thread_id;
	ztThreadJobType_Enum type;

	ztThreadMonitor     *start;
	ztThreadMonitor     *finish;

	ztAtomicBool         should_exit;
	ztAtomicBool         processing;

	ztThreadJob         *next_job;
};

// ------------------------------------------------------------------------------------------------

struct ztThreadJobQueue
{
	ztThreadJobThreadData  *threads;
	int                     threads_count;

	int                     frame_threads;
	int                     background_threads;

	ztThreadJob             job_queue[ZT_THREAD_JOB_QUEUE_SIZE];

	i32                     total_job_count;
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

enum ztShaderLoadType_Enum
{
	ztShaderLoadType_Asset,
	ztShaderLoadType_Data,

	ztShaderLoadType_MAX,
};

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_SHADERS
#define ZT_MAX_SHADERS		64
#endif

struct ztShader
{
	zt_openGLSupport(ztShaderGL *gl_shader);
	zt_directxSupport(ztShaderDX *dx_shader);

	char name[64];
	ztRenderer_Enum renderer;
	ztShaderLoadType_Enum load_type;

	union {
		struct {
			ztAssetManager *asset_mgr;
			ztAssetID asset_id;
		};

		struct {
			const char *data;
			i32 data_len;
		};
	};

	ztShaderVariableValues variables;

	int textures_bound;
};

// ------------------------------------------------------------------------------------------------

enum ztTextureLoadType_Enum
{
	ztTextureLoadType_Asset,
	ztTextureLoadType_Data,
	ztTextureLoadType_RenderTarget,

	ztTextureLoadType_MAX,
};

// ------------------------------------------------------------------------------------------------

struct ztTexture
{
	zt_openGLSupport(ztTextureGL *gl_texture);
	zt_directxSupport(ztTextureDX *dx_texture);

	i32 width, height;
	i32 flags;

	ztRenderer_Enum renderer;
	ztTextureLoadType_Enum load_type;

	union {
		struct {
			ztAssetManager *asset_mgr;
			ztAssetID asset_id;
		};

		struct {
			byte *data;
			i32 data_len;
			ztMemoryArena *arena;
		};
	};
};

#ifndef ZT_MAX_TEXTURES
#define ZT_MAX_TEXTURES	256
#endif


// ------------------------------------------------------------------------------------------------

struct ztVertexArray
{
	zt_openGLSupport(ztVertexArrayGL *gl_va);
	zt_directxSupport(ztVertexArrayDX *dx_va);
};

#ifndef ZT_MAX_VERTEX_ARRAYS
#define ZT_MAX_VERTEX_ARRAYS	32
#endif


// ------------------------------------------------------------------------------------------------

struct ztFont
{
	char name[128];
	i32 size_pixels;
	ztTextureID texture;

	i32 *glyph_code_point;

	struct ztGlyph
	{
		ztVec2 offset;
		ztVec2 size;
		ztVec4 tex_uv;
		r32 x_adv;
	};

	ztGlyph *glyphs;
	i32 glyph_count;

	r32 line_height;
	r32 line_spacing;
	r32 space_width;

	ztMemoryArena *arena;
};

#ifndef ZT_MAX_FONTS
#define ZT_MAX_FONTS	64
#endif


// ------------------------------------------------------------------------------------------------

struct ztMesh
{
	i32 triangles;
	i32 indices;

	ztVec3 aabb;

	ztVec3 obb_center;
	ztVec3 obb_size;

	zt_openGLSupport(ztVertexArrayGL *gl_vertex_array);
	zt_directxSupport(ztVertexArrayDX *dx_vertex_array);
};

#ifndef ZT_MAX_MESHES
#define ZT_MAX_MESHES	256
#endif

// ------------------------------------------------------------------------------------------------

enum ztAudioClipFlags_Enum
{
	ztAudioClipFlags_Playing = (1<<0),
	ztAudioClipFlags_Looping = (1<<1),
};


struct ztAudioClip
{
	zt_dsoundSupport(ztDirectSoundBuffer *ds_buffer);

	i32 flags;

	r32 length;
	r32 play_time;
};

#ifndef ZT_MAX_AUDIO_CLIPS
#define ZT_MAX_AUDIO_CLIPS  128
#endif

// ------------------------------------------------------------------------------------------------

#ifndef ZT_MAX_WINDOWS
#define ZT_MAX_WINDOWS	8
#endif

#ifndef ZT_MAX_RENDERER_REQUESTS
#define ZT_MAX_RENDERER_REQUESTS	8
#endif

struct ztGameGlobals
{
#if defined(ZT_WINDOWS)
	HINSTANCE hinstance = NULL;
	HICON     exe_icon = NULL;
	HMODULE   hmod_xinput = NULL;

	typedef DWORD (__stdcall *xinput_getState_Func)(DWORD, XINPUT_STATE *);
	typedef DWORD (__stdcall *xinput_setState_Func)(DWORD, XINPUT_VIBRATION *);
	xinput_getState_Func xinput_getState = nullptr;
	xinput_setState_Func xinput_setState = nullptr;
	r32                  xinput_haptic[ZT_MAX_INPUT_CONTROLLERS];
#endif

	zt_openGLSupport(zt_dllSetOpenGLGlobals_Func *zt_dllSetOpenGLGlobals = nullptr);

	bool quit_requested = false;

	ztProfiler       *profiler         = nullptr;

	ztThreadID        main_thread_id   = ztInvalidID;
	ztThreadJobQueue *thread_job_queue = nullptr;

	// ----------------------

	ztWindowDetails   win_details[ZT_MAX_WINDOWS];
	ztGameSettings    win_game_settings[ZT_MAX_WINDOWS];
	i32               win_count = 0;
	ztRendererRequest renderer_requests[ZT_MAX_RENDERER_REQUESTS];
	i32               renderer_requests_count = 0;
	byte             *renderer_memory;
	i32               renderer_memory_size;

	ztGameDetails     game_details;
	i32               last_drawn_frame = 0;

	// ----------------------

	ztShader      shaders[ZT_MAX_SHADERS];
	i32           shaders_count = 0;

	ztShaderID    default_shader_solid = 0;

	// ----------------------

	ztTexture     textures[ZT_MAX_TEXTURES];
	i32           textures_count = 0;

	// ----------------------

	ztVertexArray vertex_arrays[ZT_MAX_VERTEX_ARRAYS];
	i32           vertex_arrays_count = 0;

	// ----------------------

	ztFont        fonts[ZT_MAX_FONTS];
	i32           fonts_count = 0;
	i32           fonts_count_system = 0;

	// ----------------------

	ztMesh        meshes[ZT_MAX_MESHES];
	i32           meshes_count = 0;

	// ----------------------

	zt_dsoundSupport(ztDirectSoundContext *ds_context = nullptr);

	ztAudioClip   audio_clips[ZT_MAX_AUDIO_CLIPS];
	i32           audio_clips_count = 0;
	bool          audio_muted = false;


	// ----------------------

	bool              input_this_frame = false;

	ztInputKeys_Enum  input_key_strokes[ZT_MAX_INPUT_KEYSTROKES];
	i32               input_key_strokes_count = 0;

	i32               input_keys_mapping[256];
	ztInputKeys       input_keys[ztInputKeys_MAX];

	ztInputMouse      input_mouse;
	bool              input_mouse_look = false;
	i32               input_mouse_captures = 0;

	ztInputController input_controllers[ZT_MAX_INPUT_CONTROLLERS];

	// ----------------------
};

#define ZT_GAME_GLOBALS_VERSION   1 // update this any time ztGameGlobals is changed

ztGameGlobals *zt_game = nullptr;


#endif // internal include guard
#endif // internal declarations

#if defined(ZT_GAME_IMPLEMENTATION)
#ifndef __zt_game_implementation__
#define __zt_game_implementation__

#if !defined(ZT_DLL)
	// check for valid setup
#	if !defined(ZT_GAME_FUNC_SETTINGS)
#		error You must define ZT_GAME_FUNC_SETTINGS
#	endif
#	if !defined(ZT_GAME_FUNC_INIT)
#		error You must define ZT_GAME_FUNC_INIT
#	endif
#	if !defined(ZT_GAME_FUNC_CLEANUP)
#		error You must define ZT_GAME_FUNC_CLEANUP
#	endif
#	if !defined(ZT_GAME_FUNC_LOOP)
#		error You must define ZT_GAME_FUNC_LOOP
#	endif
#endif

#if defined(ZT_DLL)
ZT_DLLEXPORT ZT_FUNC_DLL_SET_GAME_GLOBALS(zt_dllSetGameGlobals)
{
	if (version == ZT_GAME_GLOBALS_VERSION) {
		zt_game = (ztGameGlobals *)memory;

		// fix profiler strings
		zt_fize(zt_game->profiler->threads) {
			zt_fjz(ZT_PROFILER_FRAMES_KEPT) {
				zt_fkz(zt_game->profiler->threads[i].sections[j]) {
					zt_game->profiler->threads[i].allocations[j][k].section = "(dll reload string loss)";
				}
			}
		}
	}
}
#else
#	if defined(ZT_OPENGL)
	void zt_dllSendGameGlobals(zt_dllSetGameGlobals_Func *set_globals, zt_dllSetOpenGLGlobals_Func *set_globals_opengl)
	{
		if (set_globals) {
			set_globals(zt_game, ZT_GAME_GLOBALS_VERSION);
		}
		if (set_globals_opengl) {
			zt_game->zt_dllSetOpenGLGlobals = set_globals_opengl;
		}
	}
#	else
	void zt_dllSendGameGlobals(zt_dllSetGameGlobals_Func *set_globals)
	{
		if (set_globals) {
			set_globals(zt_game, ZT_GAME_GLOBALS_VERSION);
		}
	}
#	endif
#endif

// ------------------------------------------------------------------------------------------------

typedef unsigned char stbi_uc;

extern "C" {
	// stb image
	static stbi_uc *stbi_load_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp);
	static void     stbi_image_free(void *retval_from_stbi_load);
	static const char *stbi_failure_reason  (void);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal ZT_FUNC_THREAD_EXIT(_zt_threadJobJobExit)
{
	ztThreadJob *job = (ztThreadJob*)user_data;
	return zt_atomicBoolGet(&job->cancelled);
}

// ------------------------------------------------------------------------------------------------

ztInternal ZT_FUNC_THREAD(_zt_threadJobThread)
{
	ztThreadJobThreadData *thread_data = (ztThreadJobThreadData*)user_data;

	zt_atomicBoolSet(&thread_data->should_exit, false);
	zt_atomicBoolSet(&thread_data->processing, false);
	zt_threadMonitorTriggerSignal(thread_data->finish);

	while (!zt_atomicBoolGet(&thread_data->should_exit)) {
		zt_threadMonitorWaitForSignal(thread_data->start); // sleep until we have a job to do or are exiting
		zt_threadMonitorReset(thread_data->finish);
		zt_atomicBoolSet(&thread_data->processing, true);
		zt_threadMonitorReset(thread_data->start);

		if (zt_atomicBoolGet(&thread_data->should_exit)) {
			zt_atomicBoolSet(&thread_data->processing, false);
			return 0;
		}

		ZT_PROFILE_GAME("Thread Main");

		while (thread_data->next_job && !zt_atomicBoolGet(&thread_data->should_exit)) {
			thread_data->next_job->thread_func(thread_data->thread_id, thread_data->next_job->thread_func_user_data, _zt_threadJobJobExit, thread_data->next_job);
			zt_atomicBoolSet(&thread_data->next_job->completed, true);
			thread_data->next_job = thread_data->next_job->next;
		}

		zt_atomicBoolSet(&thread_data->processing, false);
		zt_threadMonitorTriggerSignal(thread_data->finish);
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_threadJobQueueInit(int max_frame_threads, int max_background_threads)
{
	zt_assert(max_frame_threads + max_background_threads <= ZT_MAX_THREADS);

	ztThreadJobQueue *queue   = zt_game->thread_job_queue = zt_mallocStruct(ztThreadJobQueue);
	queue->threads_count      = max_frame_threads + max_background_threads;
	queue->threads            = zt_mallocStructArray(ztThreadJobThreadData, queue->threads_count);
	queue->frame_threads      = max_frame_threads;
	queue->background_threads = max_background_threads;

	zt_fiz(queue->threads_count) {
		queue->threads[i].thread = zt_threadMake(_zt_threadJobThread, &queue->threads[i], nullptr, nullptr, &queue->threads[i].thread_id);
		queue->threads[i].type = i < max_frame_threads ? ztThreadJobType_Frame : ztThreadJobType_Background;
		queue->threads[i].start = zt_threadMonitorMake();
		queue->threads[i].finish = zt_threadMonitorMake();
		zt_atomicBoolSet(&queue->threads[i].should_exit, false);
		zt_atomicBoolSet(&queue->threads[i].processing, false);
		queue->threads[i].next_job = nullptr;
	}

	zt_fize(queue->job_queue) {
		queue->job_queue[i].id                    = ztInvalidID;
		queue->job_queue[i].type                  = ztThreadJobType_MAX;
		queue->job_queue[i].thread_func           = nullptr;
		queue->job_queue[i].thread_func_user_data = nullptr;
		queue->job_queue[i].next                  = nullptr;
		zt_atomicBoolSet(&queue->job_queue[i].completed, true);
		zt_atomicBoolSet(&queue->job_queue[i].cancelled, false);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_threadJobQueueFree()
{
	zt_threadJobQueueDllUnload();

	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	zt_fiz(queue->threads_count) {
		zt_threadMonitorFree(queue->threads[i].start);
		zt_threadMonitorFree(queue->threads[i].finish);
	}

	zt_free(queue->threads);
	zt_free(queue);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_threadJobQueueUpdate()
{
	ZT_PROFILE_PLATFORM("_zt_threadJobQueueUpdate");
	if(zt_game->thread_job_queue == nullptr || zt_game->thread_job_queue->threads_count <= 0) {
		return;
	}

	zt_threadJobQueueWaitForFrameJobs();
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobQueueDllLoad()
{
	ztThreadJobQueue *queue = zt_mallocStruct(ztThreadJobQueue);
	zt_fiz(queue->threads_count) {
		zt_atomicBoolSet(&queue->threads[i].should_exit, false);
		queue->threads[i].thread = zt_threadMake(_zt_threadJobThread, &queue->threads[i], nullptr, nullptr, &queue->threads[i].thread_id);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobQueueDllUnload()
{
	zt_threadJobQueueWaitForAllJobs();

	ztThreadJobQueue *queue = zt_game->thread_job_queue;
	zt_fiz(queue->threads_count) {
		zt_atomicBoolSet(&queue->threads[i].should_exit, true);
		zt_threadMonitorTriggerSignal(queue->threads[i].start);
		zt_threadJoin(queue->threads[i].thread);
		zt_threadFree(queue->threads[i].thread);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztThreadJobID _zt_threadJobQueueFor(ztThread_Func thread_func, void *user_data, r32 anticipated_length, ztThreadJobType_Enum type)
{
	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	if(queue->threads_count <= 0) {
		thread_func(0, user_data, nullptr, nullptr);
		return -2;
	}

	r32 lowest_val = ztReal32Max;
	int lowest_idx = -1;

	zt_fiz(queue->threads_count) {
		if (queue->threads[i].type == type && !zt_atomicBoolGet(&queue->threads[i].processing)) {
			r32 val = 0;
			zt_flink(job, queue->threads[i].next_job) {
				val += job->anticipated_length;
			}
			if (val < lowest_val) {
				lowest_val = val;
				lowest_idx = i;
			}
		}
	}

	if (lowest_idx == -1) {
		// there are no waiting frame threads, so we need to wait
		if(type == ztThreadJobType_Frame) {
			zt_threadJobQueueWaitForFrameJobs();
		}
		else {
			// TODO: should maintain a separate queue so we aren't stalling here
			zt_threadJobQueueWaitForBackgroundJobs();
		}
		return _zt_threadJobQueueFor(thread_func, user_data, anticipated_length, type);
	}

	ztThreadJobThreadData *thread_data = &queue->threads[lowest_idx];

	ztThreadJob *job = nullptr;
	zt_fiz(ZT_THREAD_JOB_QUEUE_SIZE) {
		if(zt_atomicBoolGet(&queue->job_queue[i].completed)) {
			job = &queue->job_queue[i];
			break;
		}
	}
	if(job == nullptr) {
		// there are no free job slots, so we need to wait
		if(type == ztThreadJobType_Frame) {
			zt_threadJobQueueWaitForFrameJobs();
		}
		else {
			zt_threadJobQueueWaitForBackgroundJobs();
		}
		zt_threadJobQueueWaitForFrameJobs();
		return _zt_threadJobQueueFor(thread_func, user_data, anticipated_length, type);
	}

	job->id                     = ++queue->total_job_count;
	job->type                   = type;
	job->thread_func            = thread_func;
	job->thread_func_user_data  = user_data;
	job->anticipated_length     = anticipated_length;
	job->next                   = nullptr;

	zt_atomicBoolSet(&job->completed, false);
	zt_atomicBoolSet(&job->cancelled, false);

	zt_singleLinkAddToEnd(thread_data->next_job, job);

	if (type == ztThreadJobType_Background) {
		zt_threadMonitorTriggerSignal(thread_data->start);
	}

	return job->id;
}

// ------------------------------------------------------------------------------------------------

ztThreadJobID zt_threadJobQueueForFrame(ztThread_Func thread_func, void *user_data, r32 anticipated_length)
{
	ZT_PROFILE_PLATFORM("zt_threadJobQueueForFrame");
	return _zt_threadJobQueueFor(thread_func, user_data, anticipated_length, ztThreadJobType_Frame);
}

// ------------------------------------------------------------------------------------------------

ztThreadJobID zt_threadJobQueueForBackground(ztThread_Func thread_func, void *user_data, r32 anticipated_length)
{
	ZT_PROFILE_PLATFORM("zt_threadJobQueueForBackground");
	if(zt_game->thread_job_queue->background_threads == 0) {
		thread_func(0, user_data, nullptr, nullptr);
		return -2;
	}
	else {
		return _zt_threadJobQueueFor(thread_func, user_data, anticipated_length, ztThreadJobType_Background);
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_threadJobIsComplete(ztThreadJobID job_id)
{
	ZT_PROFILE_PLATFORM("zt_threadJobIsComplete");
	if(job_id == -2) {
		return true;
	}

	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	zt_fiz(ZT_THREAD_JOB_QUEUE_SIZE) {
		if(queue->job_queue[i].id == job_id) {
			return zt_atomicBoolGet(&queue->job_queue[i].completed);
		}
	}

	return true; // if the job isn't found, it's been pushed out of the queue
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobCancel(ztThreadJobID job_id)
{
	ZT_PROFILE_PLATFORM("zt_threadJobCancel");
	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	zt_fiz(ZT_THREAD_JOB_QUEUE_SIZE) {
		if(queue->job_queue[i].id == job_id) {
			zt_atomicBoolSet(&queue->job_queue[i].cancelled, true);
			break;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobQueueStartFrameJobs()
{
	ZT_PROFILE_PLATFORM("zt_threadJobQueueStartFrameJobs");
	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	zt_fiz(queue->threads_count) {
		if (queue->threads[i].type == ztThreadJobType_Frame && !zt_atomicBoolGet(&queue->threads[i].processing)) {
			zt_threadMonitorTriggerSignal(queue->threads[i].start);
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobQueueWaitForFrameJobs()
{
	ZT_PROFILE_PLATFORM("zt_threadJobQueueWaitForFrameJobs");
	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	zt_fiz(queue->threads_count) {
		if (queue->threads[i].type == ztThreadJobType_Frame && zt_atomicBoolGet(&queue->threads[i].processing)) {
			zt_threadMonitorWaitForSignal(queue->threads[i].finish);
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobQueueWaitForBackgroundJobs()
{
	ZT_PROFILE_PLATFORM("zt_threadJobQueueWaitForBackgroundJobs");
	ztThreadJobQueue *queue = zt_game->thread_job_queue;

	zt_fiz(queue->threads_count) {
		if (queue->threads[i].type == ztThreadJobType_Background && zt_atomicBoolGet(&queue->threads[i].processing)) {
			zt_threadMonitorWaitForSignal(queue->threads[i].finish);
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_threadJobQueueWaitForAllJobs()
{
	ZT_PROFILE_PLATFORM("zt_threadJobQueueWaitForAllJobs");
	zt_threadJobQueueWaitForFrameJobs();
	zt_threadJobQueueWaitForBackgroundJobs();
}

// ------------------------------------------------------------------------------------------------

int zt_threadGetIndex()
{
	ztThreadID thread_id = zt_threadGetCurrentID();
	if(thread_id == zt_game->main_thread_id) {
		return 0;
	}

	zt_fiz(zt_game->thread_job_queue->threads_count) {
		if(zt_game->thread_job_queue->threads[i].thread_id == thread_id) {
			return i + 1;
		}
	}

	zt_assert(false);
	return -1;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal void _zt_profilerInit()
{
#	if !defined(ZT_NO_PROFILE)
	zt_game->profiler = zt_mallocStruct(ztProfiler);
	zt_game->profiler->paused = false;

	zt_fize(zt_game->profiler->threads) {
		zt_game->profiler->threads[i].allocations = (ztProfiledSection**)malloc(zt_sizeof(ztProfiledSection*) * ZT_PROFILER_FRAMES_KEPT);
		zt_game->profiler->threads[i].roots       = (ztProfiledSection**)malloc(zt_sizeof(ztProfiledSection*) * ZT_PROFILER_FRAMES_KEPT);
		zt_game->profiler->threads[i].sections    = (int*)malloc(zt_sizeof(int) * ZT_PROFILER_FRAMES_KEPT);

		zt_fjz(ZT_PROFILER_FRAMES_KEPT) {
			zt_game->profiler->threads[i].allocations[j] = (ztProfiledSection*)malloc(zt_sizeof(ztProfiledSection) * ZT_PROFILER_MAX_SECTIONS_PER_FRAME);
			zt_game->profiler->threads[i].roots      [j] = nullptr;
			zt_game->profiler->threads[i].sections   [j] = 0;
		}
		zt_game->profiler->threads[i].root                        = nullptr;
		zt_game->profiler->threads[i].current                     = nullptr;
		zt_game->profiler->threads[i].allocations_current_section = 0;
		zt_game->profiler->threads[i].allocations_current_frame   = -1;
	}
	
	zt_game->profiler->current_frame = -1;
#	endif
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_profilerFree()
{
#	if !defined(ZT_NO_PROFILE)

	zt_fize(zt_game->profiler->threads) {
		zt_fjz(ZT_PROFILER_FRAMES_KEPT) {
			free(zt_game->profiler->threads[i].allocations[j]);
		}
		free(zt_game->profiler->threads[i].allocations);
		free(zt_game->profiler->threads[i].roots);
		free(zt_game->profiler->threads[i].sections);
	}

	free(zt_game->profiler);
	zt_game->profiler = nullptr;
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_profilerPause()
{
#	if !defined(ZT_NO_PROFILE)
	zt_game->profiler->paused = true;
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_profilerResume()
{
#	if !defined(ZT_NO_PROFILE)
	zt_game->profiler->paused = false;
#	endif
}

// ------------------------------------------------------------------------------------------------

bool zt_profilerIsPaused()
{
#	if !defined(ZT_NO_PROFILE)
	return zt_game->profiler->paused;
#	else
	return false;
#	endif
}

// ------------------------------------------------------------------------------------------------
void zt_profilerFrameBegin()
{
#	if !defined(ZT_NO_PROFILE)
	if(zt_game->profiler->paused) {
		return;
	}

	zt_game->profiler->current_frame = (zt_game->profiler->current_frame + 1) % ZT_PROFILER_FRAMES_KEPT;
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_profilerFrameEnd()
{
#	if !defined(ZT_NO_PROFILE)
#	endif
}

// ------------------------------------------------------------------------------------------------

ztInternal byte _zt_default_font_data[] = {
	0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x10,0x08,0x06,0x00,0x00,0x00,0x88,0x84,0x0d,0x0b,0x00,0x00,0x00,0x19,0x74,0x45,0x58,0x74,0x53,0x6f,0x66,0x74,0x77,0x61,0x72,0x65,0x00,0x41,0x64,0x6f,0x62,0x65,0x20,0x49,0x6d,0x61,0x67,0x65,0x52,0x65,0x61,0x64,0x79,0x71,0xc9,0x65,0x3c,0x00,0x00,0x04,0xf3,0x49,0x44,0x41,0x54,0x78,0xda,0xec,0x9d,0xd9,0x8e,0xdd,0x30,0x08,0x40,0x4d,0xd5,0xff,0xff,0x65,0xaa,0x3e,0x54,0x1d,0x5d,0x25,0x31,0x18,0xf0,0x92,0x7b,0x8e,0x34,0x1a,0xcd,0x24,0xde,0xb1,0x0d,0x78,0x89,0xa8,0x6a,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x77,0xf3,0x8b,0x2a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x3f,0xbf,0x9d,0xef,0xff,0xdd,0x2e,0x20,0x9d,0x67,0x77,0xef,0xfc,0xfc,0x7f,0xef,0x9d,0xa7,0x74,0x7a,0xe1,0xff,0x21,0xce,0xfc,0x5f,0xc5,0x23,0x37,0x7f,0x9f,0x4e,0xaf,0xfe,0x64,0xb0,0xfd,0x7b,0x75,0xdf,0x0c,0xf5,0x78,0x97,0x87,0xab,0xad,0x2a,0xe2,0x48,0x23,0x1a,0xde,0x53,0x86,0x5d,0xdb,0xdc,0x5a,0x36,0xaf,0x0c,0x58,0xea,0xf6,0x29,0x0f,0xea,0x68,0x17,0x4b,0x78,0x4b,0x1c,0x62,0x28,0x93,0x24,0xd5,0x9f,0x3a,0xff,0xf6,0xf4,0x57,0x19,0xc8,0x7f,0x45,0xfd,0x8d,0x86,0x7f,0xda,0x82,0x26,0x83,0xf5,0x67,0xad,0x5f,0xeb,0x9c,0x65,0x79,0xde,0x02,0xe3,0x8b,0x65,0x5e,0xd2,0xc1,0xbe,0x99,0x35,0xbf,0x57,0x84,0xcb,0x8e,0x73,0x74,0x9e,0xf6,0xe8,0x05,0x32,0xf0,0x8e,0xa7,0x7d,0xdf,0xa2,0x63,0xb4,0x4d,0xe4,0x68,0xe7,0xb9,0xd8,0x2a,0x27,0xc8,0x06,0x00,0x2c,0x77,0x00,0xcc,0x36,0x54,0x3c,0x03,0xa0,0x57,0xa9,0xf6,0x4c,0x42,0x62,0x8c,0x33,0xfa,0x7c,0x97,0xc9,0xd7,0x6a,0xe4,0x55,0x2a,0xe4,0x16,0x85,0xda,0x93,0x87,0x5e,0x79,0xb2,0xca,0xb0,0x52,0xf9,0x95,0xa4,0xf6,0x19,0xc9,0x83,0x04,0xd3,0x14,0x63,0x1f,0x6c,0x09,0xb2,0x31,0x5a,0xbe,0xa7,0x30,0x62,0xec,0x2b,0x59,0x32,0xa1,0x81,0xf6,0xb7,0xf6,0x0f,0x99,0x10,0x7e,0x56,0x9f,0xf2,0xb6,0xad,0x27,0x2f,0x16,0x87,0x90,0x55,0x8e,0x2d,0xce,0x90,0x36,0xe0,0xac,0xf8,0x26,0xe3,0xb1,0xaa,0x0e,0x24,0xe9,0x9d,0x27,0x19,0x04,0x9c,0x1c,0x6d,0x40,0xff,0xfc,0xf6,0xfe,0x0f,0x00,0x4e,0x32,0x8f,0x00,0x48,0x70,0x02,0xfc,0xa9,0x10,0x5e,0x4d,0x86,0xde,0xc9,0x5d,0x06,0x26,0xe7,0x5e,0xdc,0xd2,0x71,0x50,0x54,0x1a,0x00,0x95,0x13,0xd0,0x95,0x32,0xaf,0x8e,0xba,0x63,0xc2,0x59,0xab,0x20,0x44,0x14,0xc8,0x4f,0xc5,0x59,0x1f,0xe2,0xd3,0xc1,0x74,0xbc,0x06,0xfd,0x0c,0x65,0x58,0x0e,0x6b,0xdf,0xb7,0x21,0x87,0xe5,0x35,0xea,0x70,0xa9,0x34,0xfe,0xf4,0x63,0xfe,0xd5,0xc4,0x72,0xb6,0x8f,0xb1,0x41,0x8d,0xef,0x78,0x9e,0x65,0x3c,0xef,0xc9,0x96,0x25,0xbc,0x25,0xfd,0x36,0x18,0x3e,0xa2,0x1f,0xe8,0xcd,0xef,0xab,0xe7,0xa3,0x6d,0xe3,0x29,0xff,0x48,0x1c,0x9e,0xf6,0xb3,0xd4,0x97,0x3a,0xf4,0xaf,0x19,0x7f,0x6b,0xb0,0x8c,0x19,0x73,0x0a,0x73,0x0b,0x00,0x98,0x99,0xb5,0x03,0x40,0x6f,0x06,0x6d,0xab,0x51,0x69,0x35,0xf8,0x57,0xaf,0x20,0xbd,0x41,0xc1,0xaf,0xc8,0xbf,0x2c,0x48,0x77,0xc5,0x4e,0x8c,0xaa,0x1d,0x22,0xd6,0xd5,0x44,0x69,0x63,0xab,0xe7,0x57,0x8e,0x00,0x14,0x89,0xbd,0xfa,0x96,0x5c,0x28,0x7a,0xba,0xc9,0xf8,0xf7,0x16,0x87,0x84,0x76,0xfa,0xd0,0xae,0x8a,0xf6,0x48,0x7f,0xf7,0x1a,0xcf,0x91,0x1d,0x3e,0x23,0xbb,0xab,0x3c,0x69,0x79,0xfb,0x5d,0xaf,0x3c,0x4f,0xed,0x1f,0x75,0xe4,0x44,0x77,0x26,0xde,0xc9,0x60,0xa4,0xbe,0x3d,0xe1,0x75,0xa0,0x6c,0xd6,0xf4,0x7f,0xfe,0x96,0x8d,0xfa,0xbe,0xa7,0xcf,0xac,0x18,0x1b,0x64,0x41,0x9d,0x01,0x00,0x0e,0x00,0xf7,0x00,0x9b,0x31,0x09,0xce,0x34,0xea,0x46,0xcb,0x78,0x67,0xc0,0x45,0xce,0x29,0x46,0x95,0xbc,0xd5,0x75,0x14,0x9d,0xdc,0x2b,0xcf,0xe0,0x4b,0x27,0x7e,0xab,0x02,0x58,0xe1,0x94,0xc8,0xdc,0xaa,0x9e,0xd1,0xf7,0xa4,0xf9,0xce,0x98,0x67,0xca,0x4e,0x6b,0x35,0xf7,0x33,0xe8,0x04,0xd9,0xff,0x56,0x05,0x4d,0x26,0xc8,0x47,0xf5,0x18,0x5e,0xdd,0xce,0x3b,0x3b,0x70,0xb2,0xb7,0xbe,0xcb,0x80,0xbc,0xec,0x50,0xc6,0x95,0x73,0x9f,0x14,0xe7,0x5f,0x02,0x7d,0x79,0x24,0x8e,0x93,0xe4,0x1f,0x00,0x00,0x07,0xc0,0x44,0x25,0x31,0xea,0xe1,0x9f,0xad,0x64,0x3e,0xed,0x00,0xc8,0x58,0x59,0x95,0x49,0x65,0x90,0xc2,0x38,0xac,0x2b,0x14,0x96,0xf2,0xf7,0xee,0x29,0x88,0x9e,0xa1,0xef,0xad,0xa4,0xeb,0x66,0xf5,0x6e,0x51,0xa6,0x2a,0x15,0x2c,0x99,0x50,0xa6,0x8c,0xfe,0x71,0x27,0x23,0x9e,0x3b,0x2f,0x56,0x19,0x97,0x95,0x69,0x44,0x0d,0xf4,0x5e,0xf8,0x99,0xb2,0x58,0xd5,0xd7,0xaa,0x9c,0x6b,0x27,0xa0,0x07,0xa4,0xbf,0xf3,0x65,0x69,0xdf,0xbc,0xbb,0x2a,0xa2,0xdb,0xcd,0xce,0xe3,0x0a,0xe7,0x1f,0x00,0xc0,0x6b,0x1d,0x00,0xd6,0x23,0x00,0x59,0x97,0xae,0xcd,0x9e,0x6c,0x7b,0xdb,0xf3,0x76,0x51,0xe0,0x64,0xe3,0x34,0x32,0x14,0x4c,0xcf,0x45,0x83,0x6f,0x53,0x3e,0xa2,0x65,0x94,0xf6,0x7c,0xae,0x72,0x07,0x23,0x20,0x5b,0x11,0x3f,0xad,0x9d,0x2b,0xc7,0x96,0xec,0x15,0xc4,0x13,0x95,0xe1,0xc8,0xf8,0xad,0x49,0x75,0x78,0xca,0xdc,0xb1,0xe3,0x0a,0xfd,0x09,0xf2,0xf6,0xad,0x2b,0xdd,0x3b,0x5c,0xf6,0xb9,0xc3,0x0e,0x48,0x41,0x76,0x00,0xe0,0x9b,0x1c,0x00,0x59,0x47,0x00,0x76,0x55,0x30,0x33,0xcf,0x60,0xee,0x54,0x8e,0xac,0xf6,0xf0,0xdc,0xf7,0xf0,0x16,0x43,0x33,0x73,0x72,0xf7,0x6c,0xb9,0xac,0xd8,0x65,0x72,0x92,0x33,0xe5,0xdb,0x0d,0x80,0x19,0xdb,0xa7,0xdf,0xd8,0x3f,0x7b,0x47,0x5c,0x00,0xe0,0xbd,0x44,0x17,0x6f,0xac,0xbb,0x18,0xa3,0x8b,0x24,0x8c,0x49,0x00,0x90,0xc2,0xaf,0x8d,0xf2,0xe2,0xfd,0xcc,0x5c,0x4f,0xe9,0xcd,0x58,0x05,0x8d,0x1a,0xb2,0x99,0x06,0x76,0x96,
	0x72,0x6b,0x29,0x77,0xf4,0x92,0xa5,0x37,0x1a,0x1d,0x33,0xd2,0xbf,0x93,0x3f,0xb9,0xf9,0xc9,0x90,0x4f,0xeb,0x97,0x2d,0xb2,0xcb,0xa5,0x8b,0xe5,0xe9,0x54,0xd9,0xdc,0xa1,0x5e,0x64,0xb3,0xfa,0xb1,0x5e,0xc2,0x3a,0xfa,0x15,0x8b,0x99,0xe3,0xdf,0x09,0x9f,0x83,0x8b,0x8e,0x17,0x5a,0xfc,0x1c,0xea,0xc6,0x30,0x2d,0x8c,0x7b,0x34,0xbe,0x37,0x5d,0xc2,0x0c,0x00,0x30,0x05,0xef,0x0e,0x80,0xac,0xdb,0x85,0x2d,0x86,0x48,0xd4,0x90,0x89,0xdc,0xe8,0xfa,0x79,0x96,0x70,0xd6,0xd9,0xc2,0x95,0x67,0xd0,0xa4,0x53,0xce,0xde,0x04,0xab,0x9d,0xf6,0x8e,0x9e,0x01,0xf4,0x5e,0xd2,0x27,0x0b,0xe2,0x8f,0x7e,0x05,0x20,0x22,0xb7,0x96,0x30,0xea,0x70,0x02,0x54,0x9c,0x01,0x7f,0xaa,0x3f,0xcf,0x25,0x7f,0xde,0xfc,0x65,0x96,0x4f,0x0b,0x64,0xaf,0xb5,0xdc,0x4b,0xf2,0xee,0xc6,0xc2,0xec,0xfa,0xf3,0x7c,0x92,0x35,0x33,0x7d,0xef,0x25,0x62,0x9f,0xcf,0x2c,0x3b,0xd2,0xbc,0xfd,0x50,0x93,0xe7,0xcb,0x19,0xc6,0x9d,0x24,0xcb,0x93,0x0e,0x8e,0xff,0xbd,0xf8,0xb3,0xc7,0xf6,0x48,0x1d,0x56,0x7e,0x41,0xa6,0x2a,0x7e,0x4f,0xff,0xe9,0xb5,0xcf,0x48,0x5d,0x5a,0xdb,0xef,0x2e,0x0f,0x1e,0xf9,0xeb,0xf5,0xff,0xde,0xdd,0x38,0x57,0xef,0x58,0x16,0x86,0x5a,0xdb,0xff,0x9e,0x03,0x00,0x80,0xff,0x83,0x94,0xaa,0x6b,0x2c,0xaf,0xf6,0xae,0x7e,0xfb,0xf7,0x4c,0xf1,0x5e,0xd3,0xb6,0x00,0xc0,0x18,0xc0,0x38,0x72,0xe6,0x58,0x7c,0xf2,0xdd,0x17,0xc8,0x60,0x7d,0xf9,0x23,0x47,0x25,0xe9,0xfb,0x00,0x90,0xc6,0xcc,0x1d,0x00,0x9e,0xf8,0x31,0xfe,0xe1,0x6d,0xd0,0xb6,0x00,0x90,0xf5,0x19,0x58,0x00,0x00,0x00,0x80,0x29,0x0e,0x00,0xc0,0x40,0x04,0x00,0x80,0xb9,0x63,0x3c,0xf3,0xc3,0x38,0xac,0xf8,0xc3,0x2e,0x6d,0xdc,0x3b,0x6a,0x79,0x97,0x3e,0x63,0x00,0x00,0xe0,0x00,0x00,0x00,0x00,0x00,0x70,0x1a,0x5d,0xd9,0x86,0xd4,0x09,0xdf,0xb8,0x87,0xbd,0xda,0x58,0x92,0xfe,0x0f,0x00,0x30,0xcc,0x1f,0x01,0x06,0x00,0x51,0xde,0x2e,0x82,0xa6,0x77,0x29,0x89,0x00,0x00,0x00,0x00,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82};

// ------------------------------------------------------------------------------------------------

void zt_profilerRender(ztDrawList *draw_list, const ztVec2& pos, const ztVec2& size, const ztVec2& mouse_pos, bool mouse_clicked, ztProfilerRenderState *render_state)
{
#	if !defined(ZT_NO_PROFILE)

	if(zt_game->fonts_count <= 0) {
		ztTextureID tex = zt_textureMakeFromFileData(_zt_default_font_data, zt_sizeof(_zt_default_font_data), ztTextureFlags_PixelPerfect);
		char *data = "info face=ZeroToleranceGui size=16 bold=0 italic=0 charset=unicode=stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=0,0 outline=0\ncommon lineHeight=16 base=13 scaleW=512 scaleH=64 pages=1 packed=0\npage id=0 file=\".\"\nchars count=94\nchar id=33 x=8 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=34 x=16 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=35 x=24 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=36 x=32 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=37 x=40 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=38 x=48 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=39 x=56 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=40 x=64 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=41 x=72 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=42 x=80 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=43 x=88 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=44 x=96 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=45 x=104 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=46 x=112 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=47 x=120 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=48 x=128 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=49 x=136 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=50 x=144 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=51 x=152 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=52 x=160 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=53 x=168 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=54 x=176 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=55 x=184 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=56 x=192 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=57 x=200 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=58 x=208 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=59 x=216 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=60 x=224 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=61 x=232 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=62 x=240 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=63 x=248 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=64 x=256 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=65 x=264 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=66 x=272 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=67 x=280 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=68 x=288 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=69 x=296 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=70 x=304 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=71 x=312 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=72 x=320 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=73 x=328 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=74 x=336 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=75 x=344 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=76 x=352 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=77 x=360 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=78 x=368 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=79 x=376 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=80 x=384 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=81 x=392 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=82 x=400 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=83 x=408 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=84 x=416 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=85 x=424 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=86 x=432 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=87 x=440 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=88 x=448 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=89 x=456 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=90 x=464 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=91 x=472 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=92 x=480 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=93 x=488 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=94 x=496 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=95 x=504 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=96 x=512 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=97 x=520 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=98 x=528 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=99 x=536 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=100 x=544 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=101 x=552 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=102 x=560 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=103 x=568 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=104 x=576 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=105 x=584 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=106 x=592 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=107 x=600 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=108 x=608 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=109 x=616 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=110 x=624 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=111 x=632 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=112 x=640 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=113 x=648 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=114 x=656 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=115 x=664 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=116 x=672 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=117 x=680 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=118 x=688 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=119 x=696 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=120 x=704 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=121 x=712 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=122 x=720 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=123 x=728 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=124 x=736 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=125 x=744 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=126 x=744 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\n";
		ztFontID font = zt_fontMakeFromBmpFontData(data, tex);
		zt_game->fonts_count_system += 1;
	}

	r32 ppu = zt_pixelsPerUnit();

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, 0);

	zt_drawListPushColor(draw_list, ztColor(0, 0, .1f, .95f));
	zt_drawListAddFilledRect2D(draw_list, pos, size, ztVec2::zero, ztVec2::one);
	zt_drawListPopColor(draw_list);

	ztVec2 timeline_size(size.x - 10 / ppu, 30 / ppu);
	ztVec2 timeline_pos(pos.x, pos.y + ((size.y - timeline_size.y) / 2) - (5 / ppu));

	r32 pixel_size = 2 / ppu;
	r32 width_per_frame = (timeline_size.x - ((ZT_PROFILER_FRAMES_KEPT + 1) * pixel_size)) / ZT_PROFILER_FRAMES_KEPT;

	int display_frame = zt_game->profiler->current_frame - 1;
	if (display_frame < 0) {
		display_frame = ZT_PROFILER_FRAMES_KEPT - 1;
	}

	int display_thread = render_state ? zt_clamp(render_state->display_thread, 0, zt_elementsOf(zt_game->profiler->threads)) : 0;

	if(render_state) {
		if(render_state->display_frame >= 0 && render_state->display_frame < ZT_PROFILER_FRAMES_KEPT && render_state->display_frame != zt_game->profiler->current_frame) {
			display_frame = render_state->display_frame;
		}
	}

	{

		zt_drawListPushColor(draw_list, ztColor_Black);
		zt_drawListAddFilledRect2D(draw_list, timeline_pos, timeline_size, ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);

		zt_drawListPushColor(draw_list, ztColor_Gray);

		ztVec2 frame_size(width_per_frame, timeline_size.y - (pixel_size * 2));
		r32 x = (timeline_pos.x - (timeline_size.x / 2)) + (width_per_frame / 2) + pixel_size;
		zt_fiz(ZT_PROFILER_FRAMES_KEPT) {
			ztVec2 fpos(x, timeline_pos.y);
			if (mouse_clicked && render_state && i != zt_game->profiler->current_frame && zt_collisionPointInRect(mouse_pos, fpos, frame_size)) {
				if(render_state->display_frame == i) {
					render_state->display_frame = -1;
				}
				else {
					render_state->display_frame = i;
				}
			}

			if (i == zt_game->profiler->current_frame) {
				zt_drawListPushColor(draw_list, ztColor_Green);
			}
			else if (i == display_frame) {
				zt_drawListPushColor(draw_list, ztColor_Orange);
			}

			zt_drawListAddFilledRect2D(draw_list, fpos, frame_size, ztVec2::zero, ztVec2::one);
			x += width_per_frame + pixel_size;

			if(i == zt_game->profiler->current_frame || i == display_frame) {
				zt_drawListPopColor(draw_list);
			}
		}

		zt_drawListPopColor(draw_list);
	}

	ztVec2 timegraph_size(size.x - 10 / ppu, 90 / ppu);
	ztVec2 timegraph_pos(pos.x, timeline_pos.y - (timeline_size.y / 2 + timegraph_size.y / 2 + 5 / ppu));
	{
		zt_drawListPushColor(draw_list, ztColor_Black);
		zt_drawListAddFilledRect2D(draw_list, timegraph_pos, timegraph_size, ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);

		r64 max = 0;
		zt_fiz(ZT_PROFILER_FRAMES_KEPT) {
			if (i == zt_game->profiler->current_frame || zt_game->profiler->threads[display_thread].roots[i] == nullptr) {
				continue;
			}

			max = zt_max(max, zt_game->profiler->threads[display_thread].roots[i]->time_accum);
		}

		max *= 1.1f;
		//max = 1000 / 60.f;

		if(max) {
			r32 x = (timegraph_pos.x - (timegraph_size.x / 2)) + (width_per_frame / 2) + pixel_size;
			zt_drawListPushColor(draw_list, ztColor_Green);
			ztVec2 frame_size(width_per_frame, timegraph_size.y - (pixel_size * 2));
			zt_fiz(ZT_PROFILER_FRAMES_KEPT) {
				if (i == zt_game->profiler->current_frame || zt_game->profiler->threads[display_thread].roots[i] == nullptr) {
					x += width_per_frame + pixel_size;
					continue;
				}

				r32 pct = (r32)(zt_game->profiler->threads[display_thread].roots[i]->time_accum / max);

				zt_drawListAddFilledRect2D(draw_list, ztVec2(x, timegraph_pos.y - ((frame_size.y * (1 - pct)) / 2)), ztVec2(frame_size.x, zt_max(pixel_size, frame_size.y * pct)), ztVec2::zero, ztVec2::one);
				x += width_per_frame + pixel_size;
			}
			zt_drawListPopColor(draw_list);
		}
	}

	{
		r32 button_w = pixel_size * 50;
		r32 button_x = timegraph_pos.x - ((timegraph_size.x - button_w) / 2) + (pixel_size * 2);
		zt_fiz(zt_elementsOf(zt_game->profiler->threads) + 1) {
			ztVec2 button_pos = ztVec2(button_x, timegraph_pos.y - (timegraph_size.y / 2) - pixel_size * 7);
			ztVec2 button_size = ztVec2(button_w, pixel_size * 12);

			button_x += button_w + pixel_size * 10;

			ztColor button_clr = ztColor_Gray;
			
			if (i == 0 && zt_game->profiler->paused) {
				button_clr = ztColor_DarkRed;
			}
			else if(i - 1 == display_thread) {
				button_clr = ztColor_DarkGreen;
			}

			if(zt_collisionPointInRect(mouse_pos, button_pos, button_size)) {
				button_clr *= 1.25f;

				if(mouse_clicked) {
					if(i == 0) {
						zt_game->profiler->paused = !zt_game->profiler->paused;
					}
					else if(render_state) {
						render_state->display_thread = i - 1;
					}
				}
			}

			zt_drawListPushColor(draw_list, button_clr);
			zt_drawListAddFilledRect2D(draw_list, button_pos, button_size, ztVec2::zero, ztVec2::one);
			zt_drawListPopColor(draw_list);
			button_pos.y += pixel_size;
			if (i == 0) {
				zt_drawListAddText2D(draw_list, 0, zt_game->profiler->paused ? "Resume" : "Pause", button_pos);
			}
			else if (i == 1) {
				zt_drawListAddText2D(draw_list, 0, "Main Thread", button_pos);
			}
			else {
				zt_strMakePrintf(thread_name, 128, "Thread %d", i - 1);
				zt_drawListAddText2D(draw_list, 0, thread_name, button_pos);
			}
		}
	}

	ztProfiledSection *ps_details = nullptr;
	{
		ztProfiledSection *ps = zt_game->profiler->threads[display_thread].roots[display_frame];
		r32 x = (timegraph_pos.x - (timegraph_size.x / 2)) + (width_per_frame / 2) + pixel_size;
		r32 y = (timegraph_pos.y - (timegraph_size.y / 2)) - 15 * pixel_size;

		if (ps) {
			int sections = zt_game->profiler->threads[display_thread].sections[display_frame];

			r64 self_times[ZT_PROFILER_MAX_SECTIONS_PER_FRAME];

			zt_fiz(sections) {
				self_times[i] = zt_game->profiler->threads[display_thread].allocations[display_frame][i].time_accum;

				zt_flink(child, zt_game->profiler->threads[display_thread].allocations[display_frame][i].children) {
					self_times[i] -= child->time_accum;
				}
			}

			zt_fiz(sections) {
				r64 current = 0;
				int current_idx = 0;
				zt_fjz(sections) {
					if (self_times[j] >= current) {
						current = self_times[j];
						current_idx = j;
					}
				}
				r64 self_time = self_times[current_idx];
				self_times[current_idx] = 0;

				if (self_time == 0) break;

				ztProfiledSection *ps = &zt_game->profiler->threads[display_thread].allocations[display_frame][current_idx];

				zt_strMakePrintf(display, 512, "%10.4f . %s", (r32)self_time * 1000000, ps->section);

				ztVec2 text_pos(x, y);
				ztVec2 text_size;

				zt_drawListAddText2D(draw_list, 0, display, ztVec2(x, y), ztAlign_Top | ztAlign_Left, ztAnchor_Top | ztAnchor_Left, &text_size);

				text_pos.x += text_size.x / 2.f;
				text_pos.y -= text_size.y / 2.f;
				if (zt_collisionPointInRect(mouse_pos, text_pos, text_size)) {
					ps_details = ps;
				}

				y -= pixel_size * 10;

				if (y - pixel_size * 10 < pos.y - (size.y / 2.f)) break;
			}
		}

		x = pos.x + pixel_size;
		y = (timegraph_pos.y - (timegraph_size.y / 2)) - 15 * pixel_size;

		struct local
		{
			static int compare(const void *a, const void *b)
			{
				ztProfiledSection *pa = *(ztProfiledSection**)a;
				ztProfiledSection *pb = *(ztProfiledSection**)b;

				if(pa->time_accum > pb->time_accum) {
					return -1;
				}
				else if(pa->time_accum < pb->time_accum) {
					return 1;
				}
				return 0;
			}

			static void displaySection(ztDrawList *draw_list, ztProfiledSection *section, r32 x, r32 *y, r32 pixel_size, r32 right, r32 y_max, int indent)
			{
				if (section == nullptr || *y < y_max) {
					return;
				}

				ztVec2 ext_label, ext_value;

				r64 tm_total = section->time_accum, tm_alone = section->time_accum;
				{
					zt_flink(child, section->children) {
						tm_alone -= child->time_accum;
					}
				}

				ztVec2 pos(x + (indent * pixel_size * 10), *y);

				zt_strMakePrintf(time, 512, " %10.4f %12.4f . ", tm_total * 1000000, tm_alone * 1000000);
				zt_drawListAddText2D(draw_list, 0, time, pos, ztAlign_Top|ztAlign_Left, ztAnchor_Top|ztAnchor_Left, &ext_label);

				zt_strMakePrintf(func, 512, "%s", section->section);
				zt_drawListAddText2D(draw_list, 0, func, ztVec2(pos.x + ext_label.x, *y), ztAlign_Top|ztAlign_Left, ztAnchor_Top|ztAnchor_Left, &ext_label);

				if(indent > 0) {
					zt_drawListAddLine(draw_list, ztVec3(x + ((indent - 1) * pixel_size * 10), *y - ext_label.y / 2, 0), ztVec3(x + (indent * pixel_size * 10), *y - ext_label.y / 2, 0));
					zt_drawListAddLine(draw_list, ztVec3(x + ((indent - 1) * pixel_size * 10), *y + ext_label.y / 2 + pixel_size * 2, 0), ztVec3(x + ((indent - 1) * pixel_size * 10), *y - (ext_label.y + pixel_size) / 2, 0));
				}

				*y -= pixel_size * 10;

				ztProfiledSection *children[ZT_PROFILER_MAX_SECTIONS_PER_FRAME];
				{
					int idx = 0;
					zt_flink(child, section->children) {
						children[idx++] = child;
					}

					qsort(children, idx, zt_sizeof(ztProfiledSection*), compare);

					zt_fiz(idx) {
						displaySection(draw_list, children[i], x, y , pixel_size, right, y_max, indent + 1);
					}
				}

//				int idx = 0;
//				zt_flink(child, section->children) {
//					idx += 1;
//					displaySection(draw_list, child, x, y, pixel_size, right, y_max, indent + 1);
//				}
			}
		};

		if(ps_details) {
			local::displaySection(draw_list, ps_details, pos.x - pixel_size * 100, &y, pixel_size, (pos.x + size.x / 2) - pixel_size * 10, (pos.y - (size.y / 2.f)) + pixel_size * 10, 0);//pos.x + (size.x / 2) - 10 / ppu);
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
#	endif
}

// ------------------------------------------------------------------------------------------------

ztProfiledSection *zt_profiledSectionEnter(const char *section, i32 section_hash, const char *system, i32 system_hash, int thread_idx)
{
#	if !defined(ZT_NO_PROFILE)
	if (zt_game->profiler->paused) {
		return nullptr;
	}

	//if (zt_game->game_details.current_frame <= 1) return nullptr;

	ztProfiledThread *pt = &zt_game->profiler->threads[thread_idx];
	ztProfiledSection *ps = nullptr;
	bool ps_existing = false;

	if (pt->root == nullptr || pt->allocations_current_frame != zt_game->profiler->current_frame) {

		if (pt->allocations_current_frame < zt_game->profiler->current_frame) {
			for (int i = pt->allocations_current_frame + 1; i < zt_game->profiler->current_frame; ++i) {
				pt->roots[i] = nullptr;
				pt->sections[i] = 0;
			}
		}
		else {
			for (int i = pt->allocations_current_frame + 1; i < ZT_PROFILER_FRAMES_KEPT; ++i) {
				pt->roots[i] = nullptr;
				pt->sections[i] = 0;
			}
			for (int i = 0; i < zt_game->profiler->current_frame; ++i) {
				pt->roots[i] = nullptr;
				pt->sections[i] = 0;
			}
		}

		pt->allocations_current_frame   = zt_game->profiler->current_frame;
		pt->allocations_current_section = 0;

		ps = pt->root = &pt->allocations[pt->allocations_current_frame][pt->allocations_current_section++];

		pt->roots   [pt->allocations_current_frame] = pt->root;
		pt->sections[pt->allocations_current_frame] = 0;
		pt->current = nullptr;
	}
	else {
		zt_flink(child, pt->current->children) {
			if(child->section_hash == section_hash) {
				ps = child;
				ps_existing = true;
				break;
			}
		}
		if(ps == nullptr) {
			if (pt->allocations_current_section >= ZT_PROFILER_MAX_SECTIONS_PER_FRAME) {
				return nullptr;
			}

			ps = &pt->allocations[pt->allocations_current_frame][pt->allocations_current_section++];
			pt->sections[pt->allocations_current_frame] = pt->allocations_current_section;

		}
	}

	if (ps) {
		ps->thread = pt;

		ps->parent = pt->current;
		ps->time_begin = zt_getTime();

		if (!ps_existing) {
			ps->time_accum   = 0;
			ps->called       = 0;
			ps->children     = nullptr;
			ps->next         = nullptr;
			ps->section      = section;
			ps->section_hash = section_hash;
		}

		if (pt->current && !ps_existing) {
			ztProfiledSection *last = pt->current->children;
			while(last && last->next) {
				last = last->next;
			}

			zt_singleLinkAddToEnd(pt->current->children, ps);
			zt_assert(pt->current->children != pt->current->parent);
		}

		pt->current = ps;

	}

	return ps;
#	else
	return nullptr;
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_profiledSectionExit(ztProfiledSection *section)
{
#	if !defined(ZT_NO_PROFILE)
	if (section == nullptr) {
		return;
	}

	//if (zt_game->game_details.current_frame <= 1) return;

	r64 time_end = zt_max(zt_getTime(), section->time_begin);

	section->time_accum += time_end - section->time_begin;
	section->called += 1;

	if(section->parent) {
		section->thread->current = section->parent;
	}
#	endif
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool zt_assetMakePackedFile(const char *directory, const char *packed_file, ztMemoryArena *arena)
{
	return false; // not yet implemented
}

// ------------------------------------------------------------------------------------------------

bool zt_assetManagerLoadDirectory(ztAssetManager *asset_mgr, const char *directory, ztMemoryArena *arena)
{
	ZT_PROFILE_ASSETS("zt_assetManagerLoadDirectory");

	zt_memSet(asset_mgr, sizeof(ztAssetManager), 0);

	int buffer_size = 1024 * 128;
	char *buffer = zt_mallocStructArrayArena(char, buffer_size, arena);

	i32 len = zt_getDirectoryFiles(directory, buffer, buffer_size, true);
	if (len == 0) {
		zt_logInfo("Asset Manager: No assets found in directory: %s", directory);
		zt_freeArena(buffer, arena);
		return true; // no reason to fail here, but there's nothing more to do
	}

	if (ztFilePathSeparator == '\\') {
		zt_fiz(len) {
			if (buffer[i] == '\\') {
				buffer[i] = '/';
			}
		}
	}

	int tokens_count = zt_strTokenize(buffer, "\n", nullptr, 0);
	if (tokens_count <= 0) {
		zt_logCritical("Asset Manager: Unable to parse directory list: %s", buffer);
		zt_freeArena(buffer, arena);
		return false;
	}

	ztToken* tokens = zt_mallocStructArrayArena(ztToken, tokens_count, arena);
	tokens_count = zt_strTokenize(buffer, "\n", tokens, tokens_count);

	int dir_len = zt_strLen(directory) + 1;

	asset_mgr->source = ztAssetManagerSource_Directory;
	asset_mgr->directory = buffer;
	asset_mgr->directory_len = dir_len;
	asset_mgr->arena = arena;
	asset_mgr->asset_callbacks_count = 0;
	asset_mgr->asset_modified_check_last_idx = 0;

	if (tokens_count > ztAssetManagerMaxAssets) {
		zt_assert(false && "Too many assets in directory");
		tokens_count = ztAssetManagerMaxAssets;
	}

	zt_fiz(tokens_count) {
		char* token = buffer + tokens[i].beg + dir_len;
		buffer[tokens[i].beg + tokens[i].len] = 0; // replace the \n with null

		asset_mgr->asset_name[i] = token;
		asset_mgr->asset_name_hash[i] = zt_strHash(token);
		asset_mgr->asset_size[i] = zt_fileSize(token - dir_len);
		asset_mgr->asset_modified[i] = 0;

		if (zt_striEndsWith(token, ".png")) asset_mgr->asset_type[i] = ztAssetManagerType_ImagePNG;
		else if (zt_striEndsWith(token, ".jpg")) asset_mgr->asset_type[i] = ztAssetManagerType_ImageJPG;
		else if (zt_striEndsWith(token, ".wav")) asset_mgr->asset_type[i] = ztAssetManagerType_AudioWAV;
		else if (zt_striEndsWith(token, ".zts")) asset_mgr->asset_type[i] = ztAssetManagerType_Shader;
		else if (zt_striEndsWith(token, ".ttf")) asset_mgr->asset_type[i] = ztAssetManagerType_Font;
		else if (zt_striEndsWith(token, ".fnt")) asset_mgr->asset_type[i] = ztAssetManagerType_Font;
		else if (zt_striEndsWith(token, ".obj")) asset_mgr->asset_type[i] = ztAssetManagerType_MeshOBJ;
		else if (zt_striEndsWith(token, ".mtl")) asset_mgr->asset_type[i] = ztAssetManagerType_Material;
		else asset_mgr->asset_type[i] = ztAssetManagerType_Unknown;

		asset_mgr->asset_data[i] = nullptr;
		asset_mgr->asset_callbacks[i] = nullptr;
	}
	asset_mgr->asset_count = tokens_count;

	zt_directoryMonitor(&asset_mgr->directory_mon, directory, true, ztDirectoryMonitorFlags_Modify);

	zt_freeArena(tokens, arena);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_assetManagerLoadPackedFile(ztAssetManager *asset_mgr, const char *packed_file, ztMemoryArena *arena)
{
	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_assetManagerFree(ztAssetManager *asset_mgr)
{
	if (asset_mgr == nullptr) {
		return;
	}
	zt_fiz(asset_mgr->asset_count) {
		if (asset_mgr->asset_data[i]) {
			zt_freeArena(asset_mgr->asset_data[i], asset_mgr->arena);
		}
	}
	zt_freeArena(asset_mgr->directory, asset_mgr->arena);
	zt_memSet(asset_mgr, sizeof(ztAssetManager), 0);
}

// ------------------------------------------------------------------------------------------------

bool zt_assetExists(ztAssetManager *asset_mgr, const char *asset)
{
	return zt_assetExists(asset_mgr, zt_strHash(asset));
}

// ------------------------------------------------------------------------------------------------

bool zt_assetExists(ztAssetManager *asset_mgr, i32 asset_hash)
{
	ZT_PROFILE_ASSETS("zt_assetExists");
	zt_returnValOnNull(asset_mgr, false);

	zt_fiz(asset_mgr->asset_count) {
		if (asset_mgr->asset_name_hash[i] == asset_hash) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_assetFileExistsAsAsset(ztAssetManager *asset_mgr, const char *file_name, i32 *asset_hash)
{
	ZT_PROFILE_ASSETS("zt_assetFileExistsAsAsset");
	zt_returnValOnNull(asset_mgr, false);
	zt_returnValOnNull(file_name, false);

	if (asset_mgr->source == ztAssetManagerSource_Directory) {
		const char *asset_name = nullptr;

		if (!zt_strStartsWith(file_name, asset_mgr->directory)) {
			asset_name = file_name;
		}
		else {
			asset_name = zt_strMoveForward(file_name, zt_strLen(asset_mgr->directory + 1));
		}

		if (!asset_name) {
			return false;
		}

		i32 hash = zt_strHash(asset_name);
		zt_fiz(asset_mgr->asset_count) {
			if (asset_mgr->asset_name_hash[i] == hash) {
				if (asset_hash) {
					*asset_hash = hash;
				}
				return true;
			}
		}

		return false;
	}
	else {
		return false;
	}
}

// ------------------------------------------------------------------------------------------------

ztAssetID zt_assetLoad(ztAssetManager *asset_mgr, const char *asset)
{
	ZT_PROFILE_ASSETS("zt_assetLoad(char*)");
	ztAssetID asset_id = zt_assetLoad(asset_mgr, zt_strHash(asset));
	
	if(asset_id == ztInvalidID) {
		zt_logDebug("Unable to load asset: %s", asset);
	}
	else {
		zt_logDebug("Loaded asset: %s (%d)", asset, asset_id);
	}

	return asset_id;
}

// ------------------------------------------------------------------------------------------------

ztAssetID zt_assetLoad(ztAssetManager *asset_mgr, i32 asset_hash)
{
	ZT_PROFILE_ASSETS("zt_assetLoad(i32)");
	zt_returnValOnNull(asset_mgr, ztInvalidID);

	zt_fiz(asset_mgr->asset_count) {
		if (asset_mgr->asset_name_hash[i] == asset_hash) {
			return i;
		}
	}

	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

ztAssetID zt_assetLoad(ztAssetManager *asset_mgr, const char *asset, ztAssetID same_location_as)
{
	ZT_PROFILE_ASSETS("zt_assetLoad(char*, ztAssetID)");
	zt_returnValOnNull(asset_mgr, ztInvalidID);

	if (same_location_as == ztInvalidID) {
		return zt_assetLoad(asset_mgr, asset);
	}
	int pos_path = zt_strFindLastPos(asset_mgr->asset_name[same_location_as], "/");
	if (pos_path == ztStrPosNotFound) {
		return zt_assetLoad(asset_mgr, asset);
	}

	char asset_path[1024];
	zt_strCpy(asset_path, zt_elementsOf(asset_path), asset_mgr->asset_name[same_location_as], pos_path);

	zt_strMakePrintf(asset_name, 2048, "%s/%s", asset_path, asset);
	return zt_assetLoad(asset_mgr, asset_name);
}

// ------------------------------------------------------------------------------------------------
i32 zt_assetSize(ztAssetManager *asset_mgr, ztAssetID asset_id)
{
	ZT_PROFILE_ASSETS("zt_assetSize");
	zt_returnValOnNull(asset_mgr, 0);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);
	return asset_mgr->asset_size[asset_id];
}

// ------------------------------------------------------------------------------------------------

bool zt_assetLoadData(ztAssetManager *asset_mgr, ztAssetID asset_id, void *data, i32 data_size)
{
	ZT_PROFILE_ASSETS("zt_assetLoadData");
	zt_returnValOnNull(asset_mgr, false);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	switch(asset_mgr->source)
	{
		case ztAssetManagerSource_Directory: {
			if (asset_mgr->asset_data[asset_id] == nullptr) {
				i32 size = 0;
				asset_mgr->asset_data[asset_id] = zt_readEntireFile(asset_mgr->asset_name[asset_id] - asset_mgr->directory_len, &size, false, asset_mgr->arena);

				if (size != asset_mgr->asset_size[asset_id]) {
					asset_mgr->asset_size[asset_id] = size;
				}
			}

			if (data_size < asset_mgr->asset_size[asset_id]) {
				return false;
			}

			zt_memCpy(data, data_size, asset_mgr->asset_data[asset_id], asset_mgr->asset_size[asset_id]);

			return true;
		} break;

		case ztAssetManagerSource_PackedFile: {
		} break;

		default: {
			return false;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_assetClearCache(ztAssetManager *asset_mgr, ztAssetID asset_id)
{
	ZT_PROFILE_ASSETS("zt_assetClearCache");
	zt_returnValOnNull(asset_mgr, false);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	zt_fiz(asset_mgr->asset_count) {
		if (asset_mgr->asset_data[i]) {
			zt_freeArena(asset_mgr->asset_data[i], asset_mgr->arena);
			asset_mgr->asset_data[i] = nullptr;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_assetAddReloadCallback(ztAssetManager *asset_mgr, ztAssetID asset_id, zt_assetManagerAssetUpdated_Func function, void *user_data)
{
	ZT_PROFILE_ASSETS("zt_assetAddReloadCallback");
	zt_returnOnNull(asset_mgr);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);
	
	if (asset_mgr->source != ztAssetManagerSource_Directory) {
		return;
	}

	if (asset_mgr->asset_callbacks_count >= zt_elementsOf(asset_mgr->asset_callbacks)) {
		zt_assert(false && "Asset callback overflow");
		return;
	}

	int idx = asset_mgr->asset_callbacks_count++;
	asset_mgr->asset_callbacks[idx] = function;
	asset_mgr->asset_callback_ids[idx] = asset_id;
	asset_mgr->asset_callback_user_data[idx] = user_data;
	
	zt_fileModified(asset_mgr->asset_name[asset_id] - asset_mgr->directory_len, &asset_mgr->asset_modified[asset_id]);
}

// ------------------------------------------------------------------------------------------------

void zt_assetRemoveReloadCallback(ztAssetManager *asset_mgr, ztAssetID asset_id, void *user_data)
{
	ZT_PROFILE_ASSETS("zt_assetRemoveReloadCallback");
	zt_returnOnNull(asset_mgr);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	if (asset_mgr->source != ztAssetManagerSource_Directory) {
		return;
	}

	zt_fiz(asset_mgr->asset_callbacks_count) {
		if (asset_mgr->asset_callback_ids[i] == asset_id && asset_mgr->asset_callback_user_data[i] == user_data) {
			for (int j = i; j < asset_mgr->asset_callbacks_count - 1; ++j) {
				asset_mgr->asset_callbacks[j] = asset_mgr->asset_callbacks[j+1];
				asset_mgr->asset_callback_user_data[j] = asset_mgr->asset_callback_user_data[j+1];
				asset_mgr->asset_callback_ids[j] = asset_mgr->asset_callback_ids[j+1];
			}
			asset_mgr->asset_callbacks_count -= 1;

			int count = 0;
			zt_fjz(asset_mgr->asset_callbacks_count) {
				if (asset_mgr->asset_callback_ids[j] == asset_id) {
					count += 1;
					break;
				}
			}
			if (count == 0) {
				asset_mgr->asset_modified[asset_id] = 0; // so it doesn't get checked anymore
			}
			return;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_assetManagerCheckForChanges(ztAssetManager *asset_mgr)
{
	ZT_PROFILE_ASSETS("zt_assetManagerCheckForChanges");
	zt_returnOnNull(asset_mgr);

	if (asset_mgr->source != ztAssetManagerSource_Directory || asset_mgr->asset_callbacks_count == 0 || asset_mgr->asset_count == 0) {
		return;
	}

	if (!zt_directoryMonitorHasChanged(&asset_mgr->directory_mon)) {
		return;
	}

	zt_fiz(asset_mgr->asset_count) {
		if (asset_mgr->asset_modified[i] != 0) {
			i64 modified = 0;
			i32 size = zt_fileSize(asset_mgr->asset_name[i] - asset_mgr->directory_len);

			if (size > 0 && zt_fileModified(asset_mgr->asset_name[i] - asset_mgr->directory_len, &modified)) {
				const i64 min_difference = 20000; // not sure why, but occassionally was seeing multiple rapid changes to a file when saving one time, so make sure we don't reload the same file twice in short order
				if (asset_mgr->asset_modified[i] != modified && modified - asset_mgr->asset_modified[i] > min_difference) {
					if (asset_mgr->asset_data[i]) {
						zt_freeArena(asset_mgr->asset_data[i], asset_mgr->arena);
						asset_mgr->asset_data[i] = nullptr;
					}
					asset_mgr->asset_size[i] = size;

					// copy the callback data in case something changes within a function call
					int asset_callbacks_count = asset_mgr->asset_callbacks_count;
					void *asset_callback_user_data[ztAssetManagerMaxAssets];
					ztAssetID asset_callback_ids[ztAssetManagerMaxAssets];
					zt_assetManagerAssetUpdated_Func asset_callbacks[ztAssetManagerMaxAssets];

					zt_memCpy(asset_callback_user_data, zt_sizeof(asset_callback_user_data), asset_mgr->asset_callback_user_data, zt_sizeof(asset_mgr->asset_callback_user_data));
					zt_memCpy(asset_callback_ids, zt_sizeof(asset_callback_ids), asset_mgr->asset_callback_ids, zt_sizeof(asset_mgr->asset_callback_ids));
					zt_memCpy(asset_callbacks, zt_sizeof(asset_callbacks), asset_mgr->asset_callbacks, zt_sizeof(asset_mgr->asset_callbacks));

					zt_fjz(asset_callbacks_count) {
						if (asset_callback_ids[j] == i) {
							if (asset_callbacks[j]) {
								asset_callbacks[j](asset_mgr, i, asset_callback_user_data[j]);
							}
						}
					}
				}
				asset_mgr->asset_modified[i] = modified;
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------
// verifies data type and loads data into allocated buffer.  free with zt_free()

ztInternal bool _zt_assetLoadData(ztAssetManager *asset_mgr, ztAssetID asset_id, ztAssetManagerType_Enum *type_verify, int type_verify_count, void **data, i32 *data_size)
{
	ZT_PROFILE_ASSETS("_zt_assetLoadData");
	zt_returnValOnNull(asset_mgr, false);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	*data = nullptr;
	*data_size = 0;

	bool verified = false;
	zt_fiz(type_verify_count) {
		if (asset_mgr->asset_type[asset_id] == type_verify[i]) {
			verified = true;
			break;
		}
	}
	if (!verified) {
		return false;
	}

	i32 size = zt_assetSize(asset_mgr, asset_id);
	if (size <= 0) {
		return false;
	}

	(*data) = zt_mallocStructArray(byte, size);
	if (!(*data)) {
		return false;
	}

	if (!zt_assetLoadData(asset_mgr, asset_id, *data, size)) {
		zt_free(*data);
		*data = nullptr;
		return false;
	}

	return true;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

ztInternal const char *_zt_default_shaders_names[] = {
	"shader-solid",
	"shader-unlit",
	"shader-lit",
	"shader-litshadow",
	"shader-skybox",
	"shader-shadowdirectional"
};

ztInternal const char *_zt_default_shaders[] = {
	"<<[glsl_vs]>>\n<<[\n	#version 330 core\n	layout (location = 0) in vec3 position;\n	layout (location = 3) in vec4 vert_color;\n\n	uniform mat4 model;\n	uniform mat4 projection;\n	uniform mat4 view;\n	\n	out vec4 color;\n\n	void main()\n	{\n		gl_Position = projection * view * model * vec4(position, 1.0);\n		color = vert_color;\n	}\n]>>\n\n<<[glsl_fs]>>\n<<[\n	#version 330 core\n	out vec4 frag_color;\n\n	in vec4 color;\n\n	void main()\n	{\n		frag_color = color;\n	}\n]>>\n\n<<[hlsl_vs, vertexShader]>>\n<<[\n	cbuffer MatrixBuffer : register(b0)\n	{\n		matrix model;\n		matrix view;\n		matrix projection;\n	};\n\n	struct VertexInputType\n	{\n		float3 position : POSITION;\n		float2 tex_coord : TEXCOORD0;\n		float3 normal : NORMAL;\n		float4 color : COLOR;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float4 color : COLOR0;\n	};\n\n\n	FragmentInputType vertexShader(VertexInputType input)\n	{\n		FragmentInputType output;\n		float4 position4 = float4(input.position, 1);\n		output.position = mul(position4, model);\n		output.position = mul(output.position, view);\n		output.position = mul(output.position, projection);\n		output.color = input.color;\n		\n		return output;\n	}\n]>>\n\n<<[hlsl_fs, fragmentShader]>>\n<<[\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float4 color : COLOR0;\n	};\n\n	float4 fragmentShader(FragmentInputType input) : SV_TARGET\n	{\n		float4 color = input.color;\n		return color;\n	}\n]>>\n",
	"<<[glsl_vs]>>\n<<[\n	#version 330 core\n	layout (location = 0) in vec3 position;\n	layout (location = 1) in vec2 tex_coord; \n	layout (location = 2) in vec3 normal;\n	layout (location = 3) in vec4 color;\n\n	out VS_OUT {\n		vec3 frag_pos;\n		vec3 normal;\n		vec2 tex_coord;\n		vec4 color;\n	} vs_out;\n\n	uniform mat4 model;\n	uniform mat4 projection;\n	uniform mat4 view;\n\n	void main()\n	{\n		gl_Position = projection * view * model * vec4(position, 1.0);\n		vs_out.tex_coord = tex_coord;\n		vs_out.color = color;\n	}\n]>>\n\n<<[glsl_fs]>>\n<<[\n	#version 330 core\n	out vec4 frag_color;\n\n	in VS_OUT {\n		vec3 frag_pos;\n		vec3 normal;\n		vec2 tex_coord;\n		vec4 color;\n	} fs_in;\n\n	uniform sampler2D tex_diffuse;\n\n	void main()\n	{\n		vec4 clr = texture(tex_diffuse, fs_in.tex_coord) * fs_in.color;\n		frag_color = clr;\n	};\n]>>\n\n<<[hlsl_vs, vertexShader]>>\n<<[\n	cbuffer MatrixBuffer : register(b0)\n	{\n		matrix model;\n		matrix view;\n		matrix projection;\n	};\n\n	struct VertexInputType\n	{\n		float3 position : POSITION;\n		float2 tex_coord : TEXCOORD0;\n		float3 normal : NORMAL;\n		float4 color : COLOR;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float2 tex_coord : TEXCOORD0;\n		float4 color : COLOR0;\n	};\n\n\n	FragmentInputType vertexShader(VertexInputType input)\n	{\n		FragmentInputType output;\n		float4 position4 = float4(input.position, 1);\n		output.position = mul(position4, model);\n		output.position = mul(output.position, view);\n		output.position = mul(output.position, projection);\n		\n		output.tex_coord = input.tex_coord;\n		output.color = input.color;\n		\n		return output;\n	}\n]>>\n\n<<[hlsl_fs, fragmentShader]>>\n<<[\n	Texture2D tex_diffuse;\n	SamplerState sample_type;\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float2 tex_coord : TEXCOORD0;\n		float4 color : COLOR0;\n	};\n\n\n	float4 fragmentShader(FragmentInputType input) : SV_TARGET\n	{\n		float4 color = tex_diffuse.Sample(sample_type, input.tex_coord) * input.color;\n		return color;\n	}\n]>>\n",
	"<<[glsl_vs]>>\n<<[\n	#version 330 core\n	layout (location = 0) in vec3 position;\n	layout (location = 1) in vec2 tex_coord; \n	layout (location = 2) in vec3 normal;\n	layout (location = 3) in vec4 color;\n	layout (location = 4) in vec4 tangent;\n	layout (location = 5) in vec4 bitangent;\n\n	out VS_OUT {\n		vec3 frag_pos;\n		vec3 normal;\n		vec2 tex_coord;\n		vec4 color;\n		vec4 frag_pos_light_space;\n		mat3 tbn;\n	} vs_out;\n\n	uniform mat4 model;\n	uniform mat4 projection;\n	uniform mat4 view;\n	uniform mat4 light_matrix;\n\n	void main()\n	{\n		gl_Position = projection * view * model * vec4(position, 1.0);\n		vs_out.frag_pos = vec3(model * vec4(position, 1.0));\n		vs_out.normal = normalize(transpose(inverse(mat3(model))) * normal);\n		vs_out.tex_coord = tex_coord;\n		vs_out.color = color;\n		vs_out.frag_pos_light_space = light_matrix * vec4(vs_out.frag_pos, 1.0);\n		\n		vec3 t = normalize(vec3(model * tangent));\n		vec3 b = normalize(vec3(model * bitangent));\n		vec3 n = normalize(vec3(model * vec4(normal, 0)));\n		vs_out.tbn = mat3(t, b, n);\n	}\n]>>\n\n<<[glsl_fs]>>\n<<[\n	#version 330 core\n	out vec4 frag_color;\n\n	in VS_OUT {\n		vec3 frag_pos;\n		vec3 normal;\n		vec2 tex_coord;\n		vec4 color;\n		vec4 frag_pos_light_space;\n		mat3 tbn;\n	} fs_in;\n\n	uniform sampler2D diffuse_tex;\n	uniform sampler2D specular_tex;\n	uniform sampler2D normal_tex;\n	uniform sampler2D shadowmap_directional_tex;\n	uniform vec4 diffuse_color;\n	uniform vec4 specular_color;\n	uniform float shininess;\n	\n	uniform vec3 view_pos;\n\n	uniform vec3 light_pos;\n	uniform float light_ambient;\n	uniform float light_intensity;\n	uniform vec4 light_color;\n	\n	struct PointLight\n	{\n		vec3 pos;\n		\n		float intensity;\n\n		vec3 ambient_color;\n		vec3 diffuse_color;\n		vec3 specular_color;\n	};\n	\n	#define MAX_POINT_LIGHTS 4\n\n	uniform PointLight point_lights[MAX_POINT_LIGHTS];\n	uniform int point_lights_count;\n	\n	vec3 normalCalculation()\n	{\n		vec3 normal = texture(normal_tex, fs_in.tex_coord).rgb;\n		if(normal.x == 1 && normal.y == 1 && normal.z == 1) {\n			return fs_in.normal;\n		}\n		normal = normalize(normal * 2.0 - 1.0);\n		normal = normalize(fs_in.tbn * normal);\n		return normal;\n	}\n	\n	float shadowCalculation(vec3 light_dir, vec3 normal)\n	{\n		return 0;\n	}\n	\n	float specularCalculation(vec3 light_dir, vec3 normal, vec3 view_dir)\n	{\n		vec3 halfway_dir = normalize(light_dir + view_dir);\n		float spec_value = texture(specular_tex, fs_in.tex_coord).r;\n		return pow(max(dot(normal, halfway_dir), 0.0), 256.0) * shininess * 5 * spec_value;\n	}\n	\n	vec4 directionalLightCalculation(vec4 clr, vec3 normal, vec3 view_dir)\n	{\n		vec4 light_clr = light_color * light_intensity;\n        \n		vec3 light_dir = normalize(light_pos - fs_in.frag_pos);\n		float diff = max(dot(light_dir, normal), 0.0);\n		vec4 diffuse = diff * light_clr;\n     \n		vec4 specular = specularCalculation(light_dir, normal, view_dir) * light_clr * specular_color;\n		float shadow = shadowCalculation(light_dir, normal);\n\n		vec4 ambient_clr = clr * light_ambient;\n		return (ambient_clr + (1.0 - shadow) * (diffuse + specular)) * clr;\n	}\n	\n	vec4 pointLightCalculation(vec4 clr, vec3 normal, vec3 view_dir, PointLight light)\n	{\n		vec4 light_clr = vec4(light.ambient_color, 1);\n        \n		vec3 light_dir = normalize(light.pos - fs_in.frag_pos);\n		float diff = max(dot(light_dir, normal), 0.0);\n		vec4 diffuse = diff * light_clr;\n     \n		vec4 specular = specularCalculation(light_dir, normal, view_dir) * light_clr;// * specular_color;\n		float shadow = 0;//shadowCalculation(light_dir, normal);\n\n		float distance    = length(light.pos - fs_in.frag_pos);\n		float constant = 1;\n		float linear = 0.7 - (.693 * light.intensity);\n		float quadratic = 1.8 - (1.7998 * light.intensity);\n		float attenuation = 1.0 * light.intensity;\n		\n		return ((1.0 - shadow) * (diffuse + specular)) * clr * attenuation;\n	}\n	\n	void main()\n	{\n		vec4 clr = texture(diffuse_tex, fs_in.tex_coord) * fs_in.color * diffuse_color;\n		vec3 normal = normalCalculation();\n		vec3 view_dir = normalize(view_pos - fs_in.frag_pos);\n		vec4 lighting = directionalLightCalculation(clr, normal, view_dir);\n		\n		for(int i = 0; i < point_lights_count; ++i) {\n			lighting += pointLightCalculation(clr, normal, view_dir, point_lights[i]);\n		}\n        \n		frag_color = vec4(lighting.xyz, 1);\n	};\n]>>\n\n<<[hlsl_vs, vertexShader]>>\n<<[\n	cbuffer MatrixBuffer : register(b0)\n	{\n		matrix model;\n		matrix view;\n		matrix projection;\n		matrix light_matrix;\n		float3 light_pos;\n		float3 view_pos;\n	};\n\n	struct VertexInputType\n	{\n		float3 position : POSITION;\n		float2 tex_coord : TEXCOORD0;\n		float3 normal : NORMAL;\n		float4 color : COLOR;\n		float4 tangent : TANGENT;\n		float4 bitangent : BINORMAL;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float3 normal : NORMAL0;\n		float2 tex_coord : TEXCOORD0;\n		float4 color : COLOR0;\n		float4 frag_pos : POSITION0;\n		float4 frag_pos_light_space : POSITION1;\n		float4 light_pos : POSITION2;\n		float4 view_pos : POSITION3;\n		float3 tbn_t : NORMAL1;\n		float3 tbn_b : NORMAL2;\n		float3 tbn_n : NORMAL3;\n	};\n\n\n	FragmentInputType vertexShader(VertexInputType input)\n	{\n		FragmentInputType output;\n		float4 position4 = float4(input.position, 1);\n		output.position = mul(position4, model);\n		output.position = mul(output.position, view);\n		output.position = mul(output.position, projection);\n		\n		output.tex_coord = input.tex_coord;\n		output.color = input.color;\n		output.frag_pos = float4(mul(position4, model).xyz, 1);\n		output.frag_pos_light_space = mul(output.frag_pos, light_matrix);\n\n		output.normal = normalize(mul(input.normal, transpose((float3x3)model)));\n\n		output.light_pos = float4(light_pos, 1);\n		output.view_pos = float4(view_pos, 1);\n		\n		output.tbn_t = normalize(mul(model, input.tangent)).xyz;\n		output.tbn_b = normalize(mul(model, input.bitangent)).xyz;\n		output.tbn_n = normalize(mul(model, float4(input.normal, 0))).xyz;\n		\n		return output;\n	}\n]>>\n\n<<[hlsl_fs, fragmentShader]>>\n<<[\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float3 normal : NORMAL0;\n		float2 tex_coord : TEXCOORD0;\n		float4 color : COLOR0;\n		float4 frag_pos : POSITION0;\n		float4 frag_pos_light_space : POSITION1;\n		float4 light_pos : POSITION2;\n		float4 view_pos : POSITION3;\n		float3 tbn_t : NORMAL1;\n		float3 tbn_b : NORMAL2;\n		float3 tbn_n : NORMAL3;\n	};\n\n	struct PointLight\n	{\n		float3 pos;\n		\n		float intensity;\n\n		float3 ambient_color;\n		float3 diffuse_color;\n		float3 specular_color;\n	};\n	\n	#define MAX_POINT_LIGHTS 4\n\n	Texture2D diffuse_tex;\n	Texture2D specular_tex;\n	Texture2D normal_tex;\n	Texture2D shadowmap_directional_tex;\n	SamplerState sample_type;\n\n	cbuffer VariableBuffer : register(b0)\n	{\n		float4 diffuse_color;\n		float4 specular_color;\n		float  shininess;\n		float  light_ambient;\n		float  light_intensity;\n		float4 light_color;\n		int point_lights_count;\n		PointLight point_lights[MAX_POINT_LIGHTS];\n	};\n\n\n	float3 normalCalculation(FragmentInputType input)\n	{\n		float3 normal = normal_tex.Sample(sample_type, input.tex_coord).rgb;\n		if(normal.x == 1 && normal.y == 1 && normal.z == 1) {\n			return input.normal;\n		}\n\n		float3x3 tbn = transpose(float3x3(input.tbn_t, input.tbn_b, input.tbn_n));\n		normal = normalize(mul(normal, 2.0) - float3(1.0, 1.0, 1.0));\n		normal = normalize(mul(tbn, normal));\n		return normal;\n	}\n\n	float shadowCalculation(FragmentInputType input, float3 light_dir, float3 normal)\n	{\n		return 0;\n	}\n	\n	float specularCalculation(FragmentInputType input, float3 light_dir, float3 normal, float3 view_dir)\n	{\n		float3 halfway_dir = normalize(light_dir + view_dir);\n		float spec_value = specular_tex.Sample(sample_type, input.tex_coord).r;\n		float spec = pow(max(dot(normal, halfway_dir), 0.0), 256.0) * shininess * 5 * spec_value;\n		return spec;\n	}\n	\n	float4 directionalLightCalculation(FragmentInputType input, float4 clr, float3 normal, float3 view_dir)\n	{\n		float4 light_clr = light_color * light_intensity;\n		\n		float3 light_dir = normalize(input.light_pos - input.frag_pos).xyz;\n		float diff = max(dot(light_dir, normal), 0);\n		float4 diffuse = diff * light_clr;\n		\n		float4 specular = specularCalculation(input, light_dir, normal, view_dir) * light_clr * specular_color;\n		float shadow = shadowCalculation(input, light_dir, normal);\n		\n		float4 ambient_clr = clr * light_ambient;\n		return (ambient_clr + (1.0 - shadow) * (diffuse + specular)) * clr;\n	}\n\n	float4 pointLightCalculation(FragmentInputType input, float4 clr, float3 normal, float3 view_dir, PointLight light)\n	{\n		float4 light_clr = float4(light.ambient_color, 1);\n        \n		float3 light_dir = normalize(light.pos - input.frag_pos.xyz);\n		float diff = max(dot(light_dir, normal), 0.0);\n		float4 diffuse = diff * light_clr;\n		\n		float4 specular = specularCalculation(input, light_dir, normal, view_dir) * light_clr;// * specular_color;\n		float shadow = 0;//shadowCalculation(light_dir, normal);\n\n		float attenuation = 1.0 * light.intensity;\n		\n		return ((1.0 - shadow) * (diffuse + specular)) * clr * attenuation;\n	}\n\n	float4 fragmentShader(FragmentInputType input) : SV_TARGET\n	{\n		float4 clr = diffuse_tex.Sample(sample_type, input.tex_coord) * input.color * diffuse_color;\n		float3 normal = normalCalculation(input);\n		float3 view_dir = normalize(input.view_pos - input.frag_pos).xyz;\n		float4 lighting = directionalLightCalculation(input, clr, normal, view_dir);\n		\n		for(int i = 0; i < point_lights_count; ++i) {\n			lighting += pointLightCalculation(input, clr, normal, view_dir, point_lights[i]);\n		}\n\n		return float4(lighting.xyz, 1);\n	}\n]>>",
	"<<[glsl_vs]>>\n<<[\n	#version 330 core\n	layout (location = 0) in vec3 position;\n	layout (location = 1) in vec2 tex_coord; \n	layout (location = 2) in vec3 normal;\n	layout (location = 3) in vec4 color;\n	layout (location = 4) in vec4 tangent;\n	layout (location = 5) in vec4 bitangent;\n\n	out VS_OUT {\n		vec3 frag_pos;\n		vec3 normal;\n		vec2 tex_coord;\n		vec4 color;\n		vec4 frag_pos_light_space;\n		mat3 tbn;\n	} vs_out;\n\n	uniform mat4 model;\n	uniform mat4 projection;\n	uniform mat4 view;\n	uniform mat4 light_matrix;\n\n	void main()\n	{\n		gl_Position = projection * view * model * vec4(position, 1.0);\n		vs_out.frag_pos = vec3(model * vec4(position, 1.0));\n		vs_out.normal = normalize(transpose(inverse(mat3(model))) * normal);\n		vs_out.tex_coord = tex_coord;\n		vs_out.color = color;\n		vs_out.frag_pos_light_space = light_matrix * vec4(vs_out.frag_pos, 1.0);\n		\n		vec3 t = normalize(vec3(model * tangent));\n		vec3 b = normalize(vec3(model * bitangent));\n		vec3 n = normalize(vec3(model * vec4(normal, 0)));\n		vs_out.tbn = mat3(t, b, n);\n	}\n]>>\n\n<<[glsl_fs]>>\n<<[\n	#version 330 core\n	out vec4 frag_color;\n\n	in VS_OUT {\n		vec3 frag_pos;\n		vec3 normal;\n		vec2 tex_coord;\n		vec4 color;\n		vec4 frag_pos_light_space;\n		mat3 tbn;\n	} fs_in;\n\n	uniform sampler2D diffuse_tex;\n	uniform sampler2D specular_tex;\n	uniform sampler2D normal_tex;\n	uniform sampler2D shadowmap_directional_tex;\n	uniform vec4 diffuse_color;\n	uniform vec4 specular_color;\n	uniform float shininess;\n	\n	uniform vec3 view_pos;\n\n	uniform vec3 light_pos;\n	uniform float light_ambient;\n	uniform float light_intensity;\n	uniform vec4 light_color;\n	\n	struct PointLight\n	{\n		vec3 pos;\n		\n		float intensity;\n\n		vec3 ambient_color;\n		vec3 diffuse_color;\n		vec3 specular_color;\n	};\n	\n	#define MAX_POINT_LIGHTS 4\n\n	uniform PointLight point_lights[MAX_POINT_LIGHTS];\n	uniform int point_lights_count;\n	\n	vec3 normalCalculation()\n	{\n		vec3 normal = texture(normal_tex, fs_in.tex_coord).rgb;\n		if(normal.x == 1 && normal.y == 1 && normal.z == 1) {\n			return fs_in.normal;\n		}\n		normal = normalize(normal * 2.0 - 1.0);\n		normal = normalize(fs_in.tbn * normal);\n		return normal;\n	}\n	\n	float shadowCalculation(vec3 light_dir, vec3 normal)\n	{\n		vec3 proj_coords = fs_in.frag_pos_light_space.xyz / fs_in.frag_pos_light_space.w;\n		proj_coords = proj_coords * 0.5 + 0.5;\n		if(proj_coords.x < 0 || proj_coords.x > 1 || proj_coords.y < 0 || proj_coords.y > 1) {\n			return 0;\n		}\n		\n		float current_depth = proj_coords.z;\n		\n		float bias = 0;//max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);\n		\n		float shadow = 0.0;\n		vec2 texel_size = 1.0 / textureSize(shadowmap_directional_tex, 0);\n		\n		const int samples = 3;\n		for(int x = -samples; x <= samples; ++x) {\n			for(int y = -samples; y <= samples; ++y) {\n				float pcf_depth = texture(shadowmap_directional_tex, proj_coords.xy + vec2(x, y) * texel_size).r;\n				shadow += current_depth - bias > pcf_depth ? 1.0 : 0.0f;\n			}\n		}\n		shadow /= (samples * 2 + 1) * (samples * 2 + 1);\n		return shadow;\n	}\n	\n	float specularCalculation(vec3 light_dir, vec3 normal, vec3 view_dir)\n	{\n		vec3 halfway_dir = normalize(light_dir + view_dir);\n		float spec_value = texture(specular_tex, fs_in.tex_coord).r;\n		return pow(max(dot(normal, halfway_dir), 0.0), 256.0) * shininess * 5 * spec_value;\n	}\n	\n	vec4 directionalLightCalculation(vec4 clr, vec3 normal, vec3 view_dir)\n	{\n		vec4 light_clr = light_color * light_intensity;\n        \n		vec3 light_dir = normalize(light_pos - fs_in.frag_pos);\n		float diff = max(dot(light_dir, normal), 0.0);\n		vec4 diffuse = diff * light_clr;\n     \n		vec4 specular = specularCalculation(light_dir, normal, view_dir) * light_clr * specular_color;\n		float shadow = shadowCalculation(light_dir, normal);\n\n		vec4 ambient_clr = clr * light_ambient;\n		return (ambient_clr + (1.0 - shadow) * (diffuse + specular)) * clr;\n	}\n	\n	vec4 pointLightCalculation(vec4 clr, vec3 normal, vec3 view_dir, PointLight light)\n	{\n		vec4 light_clr = vec4(light.ambient_color, 1);\n        \n		vec3 light_dir = normalize(light.pos - fs_in.frag_pos);\n		float diff = max(dot(light_dir, normal), 0.0);\n		vec4 diffuse = diff * light_clr;\n     \n		vec4 specular = specularCalculation(light_dir, normal, view_dir) * light_clr;// * specular_color;\n		float shadow = 0;//shadowCalculation(light_dir, normal);\n\n		float distance    = length(light.pos - fs_in.frag_pos);\n		float constant = 1;\n		float linear = 0.7 - (.693 * light.intensity);\n		float quadratic = 1.8 - (1.7998 * light.intensity);\n		float attenuation = 1.0 * light.intensity;\n		\n		return ((1.0 - shadow) * (diffuse + specular)) * clr * attenuation;\n	}\n	\n	void main()\n	{\n		vec4 clr = texture(diffuse_tex, fs_in.tex_coord) * fs_in.color * diffuse_color;\n		vec3 normal = normalCalculation();\n		vec3 view_dir = normalize(view_pos - fs_in.frag_pos);\n		vec4 lighting = directionalLightCalculation(clr, normal, view_dir);\n		\n		for(int i = 0; i < point_lights_count; ++i) {\n			lighting += pointLightCalculation(clr, normal, view_dir, point_lights[i]);\n		}\n        \n		frag_color = vec4(lighting.xyz, 1);\n	};\n]>>\n\n<<[hlsl_vs, vertexShader]>>\n<<[\n	cbuffer MatrixBuffer : register(b0)\n	{\n		matrix model;\n		matrix view;\n		matrix projection;\n		matrix light_matrix;\n		float3 light_pos;\n		float3 view_pos;\n	};\n\n	struct VertexInputType\n	{\n		float3 position : POSITION;\n		float2 tex_coord : TEXCOORD0;\n		float3 normal : NORMAL;\n		float4 color : COLOR;\n		float4 tangent : TANGENT;\n		float4 bitangent : BINORMAL;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float3 normal : NORMAL0;\n		float2 tex_coord : TEXCOORD0;\n		float4 color : COLOR0;\n		float4 frag_pos : POSITION0;\n		float4 frag_pos_light_space : POSITION1;\n		float4 light_pos : POSITION2;\n		float4 view_pos : POSITION3;\n		float3 tbn_t : NORMAL1;\n		float3 tbn_b : NORMAL2;\n		float3 tbn_n : NORMAL3;\n	};\n\n\n	FragmentInputType vertexShader(VertexInputType input)\n	{\n		FragmentInputType output;\n		float4 position4 = float4(input.position, 1);\n		output.position = mul(position4, model);\n		output.position = mul(output.position, view);\n		output.position = mul(output.position, projection);\n		\n		output.tex_coord = input.tex_coord;\n		output.color = input.color;\n		output.frag_pos = float4(mul(position4, model).xyz, 1);\n		output.frag_pos_light_space = mul(output.frag_pos, light_matrix);\n\n		output.normal = normalize(mul(input.normal, transpose((float3x3)model)));\n\n		output.light_pos = float4(light_pos, 1);\n		output.view_pos = float4(view_pos, 1);\n		\n		output.tbn_t = normalize(mul(model, input.tangent)).xyz;\n		output.tbn_b = normalize(mul(model, input.bitangent)).xyz;\n		output.tbn_n = normalize(mul(model, float4(input.normal, 0))).xyz;\n		\n		return output;\n	}\n]>>\n\n<<[hlsl_fs, fragmentShader]>>\n<<[\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float3 normal : NORMAL0;\n		float2 tex_coord : TEXCOORD0;\n		float4 color : COLOR0;\n		float4 frag_pos : POSITION0;\n		float4 frag_pos_light_space : POSITION1;\n		float4 light_pos : POSITION2;\n		float4 view_pos : POSITION3;\n		float3 tbn_t : NORMAL1;\n		float3 tbn_b : NORMAL2;\n		float3 tbn_n : NORMAL3;\n	};\n\n	struct PointLight\n	{\n		float3 pos;\n		\n		float intensity;\n\n		float3 ambient_color;\n		float3 diffuse_color;\n		float3 specular_color;\n	};\n	\n	#define MAX_POINT_LIGHTS 4\n\n	Texture2D diffuse_tex;\n	Texture2D specular_tex;\n	Texture2D normal_tex;\n	Texture2D shadowmap_directional_tex;\n	SamplerState sample_type;\n\n	cbuffer VariableBuffer : register(b0)\n	{\n		float4 diffuse_color;\n		float4 specular_color;\n		float  shininess;\n		float  light_ambient;\n		float  light_intensity;\n		float4 light_color;\n		int point_lights_count;\n		PointLight point_lights[MAX_POINT_LIGHTS];\n	};\n\n\n	float3 normalCalculation(FragmentInputType input)\n	{\n		float3 normal = normal_tex.Sample(sample_type, input.tex_coord).rgb;\n		if(normal.x == 1 && normal.y == 1 && normal.z == 1) {\n			return input.normal;\n		}\n\n		float3x3 tbn = transpose(float3x3(input.tbn_t, input.tbn_b, input.tbn_n));\n		normal = normalize(mul(normal, 2.0) - float3(1.0, 1.0, 1.0));\n		normal = normalize(mul(tbn, normal));\n		return normal;\n	}\n\n	float shadowCalculation(FragmentInputType input, float3 light_dir, float3 normal)\n	{\n		float3 proj_coords = input.frag_pos_light_space.xyz / input.frag_pos_light_space.w;\n		proj_coords = proj_coords * 0.5 + 0.5;\n		proj_coords.y = 1 - proj_coords.y;		\n		//if(proj_coords.x < 0 || proj_coords.x > 1 || proj_coords.y < 0 || proj_coords.y > 1) {\n		//	return 0;\n		//}\n		\n		float current_depth = input.frag_pos_light_space.z;\n		float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);\n		\n		float shadow = 0.0;\n		uint tex_w = 0, tex_h = 0;\n		shadowmap_directional_tex.GetDimensions(tex_w, tex_h);\n		float2 texel_size = 1.0 / float2(tex_w, tex_h);\n		\n		const int samples = 3;\n		for(int x = -samples; x <= samples; ++x) {\n			for(int y = -samples; y <= samples; ++y) {\n				float pcf_depth = shadowmap_directional_tex.Sample(sample_type, proj_coords.xy + float2(x, y) * texel_size).r;\n				shadow += current_depth - bias > pcf_depth ? 1: 0.0f;\n			}\n		}\n		shadow /= (samples * 2 + 1) * (samples * 2 + 1);\n		return shadow;\n	}\n	\n	float specularCalculation(FragmentInputType input, float3 light_dir, float3 normal, float3 view_dir)\n	{\n		float3 halfway_dir = normalize(light_dir + view_dir);\n		float spec_value = specular_tex.Sample(sample_type, input.tex_coord).r;\n		float spec = pow(max(dot(normal, halfway_dir), 0.0), 256.0) * shininess * 5 * spec_value;\n		return spec;\n	}\n	\n	float4 directionalLightCalculation(FragmentInputType input, float4 clr, float3 normal, float3 view_dir)\n	{\n		float4 light_clr = light_color * light_intensity;\n		\n		float3 light_dir = normalize(input.light_pos - input.frag_pos).xyz;\n		float diff = max(dot(light_dir, normal), 0);\n		float4 diffuse = diff * light_clr;\n		\n		float4 specular = specularCalculation(input, light_dir, normal, view_dir) * light_clr * specular_color;\n		float shadow = shadowCalculation(input, light_dir, normal);\n		\n		float4 ambient_clr = clr * light_ambient;\n		return (ambient_clr + (1.0 - shadow) * (diffuse + specular)) * clr;\n	}\n\n	float4 pointLightCalculation(FragmentInputType input, float4 clr, float3 normal, float3 view_dir, PointLight light)\n	{\n		float4 light_clr = float4(light.ambient_color, 1);\n        \n		float3 light_dir = normalize(light.pos - input.frag_pos.xyz);\n		float diff = max(dot(light_dir, normal), 0.0);\n		float4 diffuse = diff * light_clr;\n		\n		float4 specular = specularCalculation(input, light_dir, normal, view_dir) * light_clr;// * specular_color;\n		float shadow = 0;//shadowCalculation(light_dir, normal);\n\n		float attenuation = 1.0 * light.intensity;\n		\n		return ((1.0 - shadow) * (diffuse + specular)) * clr * attenuation;\n	}\n\n	float4 fragmentShader(FragmentInputType input) : SV_TARGET\n	{\n		float4 clr = diffuse_tex.Sample(sample_type, input.tex_coord) * input.color * diffuse_color;\n		float3 normal = normalCalculation(input);\n		float3 view_dir = normalize(input.view_pos - input.frag_pos).xyz;\n		float4 lighting = directionalLightCalculation(input, clr, normal, view_dir);\n		\n		for(int i = 0; i < point_lights_count; ++i) {\n			lighting += pointLightCalculation(input, clr, normal, view_dir, point_lights[i]);\n		}\n\n		return float4(lighting.xyz, 1);\n	}\n]>>",
	"<<[glsl_vs]>>\n<<[\n	#version 330 core\n	layout (location = 0) in vec3 position;\n	out vec3 the_tex_coord;\n\n	uniform mat4 projection;\n	uniform mat4 view;\n\n	void main()\n	{\n		vec4 pos = projection * view * vec4(position, 1.0);\n		gl_Position = pos.xyww;\n		the_tex_coord = position;\n	};\n\n]>>\n\n<<[glsl_fs]>>\n<<[\n	\n	#version 330 core\n	in vec3 the_tex_coord;\n	out vec4 color;\n\n	uniform samplerCube skybox_tex;\n\n	void main()\n	{\n		color = vec4(texture(skybox_tex, the_tex_coord).rgb, 1);\n		if (color.rgb == vec3(0,0,0)) color = vec4(0,0,1,1);\n	};\n]>>\n\n<<[hlsl_vs, vertexShader]>>\n<<[\n	cbuffer MatrixBuffer : register(b0)\n	{\n		matrix view;\n		matrix projection;\n	};\n\n	struct VertexInputType\n	{\n		float3 position : POSITION;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float3 positionL : POSITION;\n	};\n\n\n	FragmentInputType vertexShader(VertexInputType input)\n	{\n		FragmentInputType output;\n		output.position = float4(input.position, 1);\n		output.position = mul(output.position, view);\n		output.position = mul(output.position, projection) * 1000;\n\n		output.positionL = input.position * 1000;\n		\n		return output;\n	}\n]>>\n\n<<[hlsl_fs, fragmentShader]>>\n<<[\n	TextureCube skybox_tex;\n	\n	SamplerState sample_type\n	{\n		Filter = MIN_MAG_MIP_LINEAR;\n		AddressU = Wrap;\n		AddressV = Wrap;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n		float3 positionL : POSITION;\n	};\n\n\n	float4 fragmentShader(FragmentInputType input) : SV_TARGET\n	{\n		return skybox_tex.Sample(sample_type, input.positionL);\n	}\n]>>\n",
	"<<[glsl_vs]>>\n<<[\n	#version 330 core\n	layout (location = 0) in vec3 position;\n\n	uniform mat4 model;\n	uniform mat4 light_matrix;\n\n	void main()\n	{\n		gl_Position = light_matrix * model * vec4(position, 1.0);\n	}\n]>>\n\n<<[glsl_fs]>>\n<<[\n	#version 330 core\n\n	void main()\n	{\n		//gl_FragDepth = gl_FragCoord.z;\n	}\n]>>\n\n<<[hlsl_vs, vertexShader]>>\n<<[\n	cbuffer MatrixBuffer : register(b0)\n	{\n		matrix model;\n		matrix light_matrix;\n	};\n\n	struct VertexInputType\n	{\n		float3 position : POSITION;\n	};\n\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n	};\n\n\n	FragmentInputType vertexShader(VertexInputType input)\n	{\n		FragmentInputType output;\n		float4 position4 = float4(input.position, 1);\n		output.position = mul(position4, model);\n		output.position = mul(output.position, light_matrix);\n		\n		return output;\n	}\n]>>\n\n<<[hlsl_fs, fragmentShader]>>\n<<[\n	struct FragmentInputType\n	{\n		float4 position : SV_POSITION;\n	};\n\n\n	float4 fragmentShader(FragmentInputType input) : SV_TARGET\n	{\n		return float4(input.position.z,input.position.z,input.position.z,1);\n	}]>>\n",
};

// ------------------------------------------------------------------------------------------------

ztRenderer_Enum zt_currentRenderer()
{
	return zt_game->win_game_settings[0].renderer;
}

// ------------------------------------------------------------------------------------------------

r32 zt_pixelsPerUnit()
{
	return (r32)zt_game->win_game_settings[0].pixels_per_unit;
}

// ------------------------------------------------------------------------------------------------

ztInternal void (*_zt_rendererSwapBuffers)(ztWindowDetails*);
ztInternal bool (*_zt_rendererSetViewport)(ztWindowDetails*, ztGameSettings*, bool);
ztInternal bool (*_zt_rendererMakeContext)(ztWindowDetails*, ztGameSettings*, i32);
ztInternal bool (*_zt_rendererFreeContext)(ztWindowDetails*);
ztInternal bool (*_zt_rendererToggleFullscreen)(ztWindowDetails*, ztGameSettings*, bool);

ztInternal bool _zt_rendererSetRendererFuncs(ztRenderer_Enum renderer);

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztdx_rendererSetViewport(ztWindowDetails *win_details, ztGameSettings *game_settings, bool force);
ztInternal bool _ztdx_rendererMakeContext(ztWindowDetails *win_details, ztGameSettings *game_settings, i32 renderer_flags);
ztInternal bool _ztdx_rendererFreeContext(ztWindowDetails *win_details);
ztInternal void _ztdx_rendererSwapBuffers(ztWindowDetails *win_details);
ztInternal bool _ztdx_rendererToggleFullscreen(ztWindowDetails *win_details, ztGameSettings *game_settings, bool);

bool _zt_winCreateWindow(ztGameSettings *game_settings, ztWindowDetails *window_details);
bool _zt_winCleanupWindow(ztWindowDetails *win_details, ztGameSettings *settings);
void _zt_winUpdateTitle(ztGameSettings *game_settings, ztWindowDetails *window_details);

// ------------------------------------------------------------------------------------------------

#define _zt_setKeyData(code, name, display, shift_display, mapping) zt_game->input_keys[idx++] = {code, (display == 0 ? ztInputKeyFlags_StateKey : 0), name, display, shift_display, mapping, 0}

ztInternal void _zt_inputSetupKeys()
{
	int idx = 0;
	_zt_setKeyData(ztInputKeys_Invalid,            "Invalid",              0,    0, 0);
	_zt_setKeyData(ztInputKeys_LeftButton,         "LeftButton",           0,    0, VK_LBUTTON);
	_zt_setKeyData(ztInputKeys_RightButton,        "RightButton",          0,    0, VK_RBUTTON);
	_zt_setKeyData(ztInputKeys_Cancel,             "Cancel",               0,    0, VK_CANCEL);
	_zt_setKeyData(ztInputKeys_MiddleButton,       "MiddleButton",         0,    0, VK_MBUTTON);
	_zt_setKeyData(ztInputKeys_XButton1,           "XButton1",             0,    0, VK_XBUTTON1);
	_zt_setKeyData(ztInputKeys_XButton2,           "XButton2",             0,    0, VK_XBUTTON2);
	_zt_setKeyData(ztInputKeys_Back,               "Back",                 0,    0, VK_BACK);
	_zt_setKeyData(ztInputKeys_Tab,                "Tab",               '\t',    0, VK_TAB);
	_zt_setKeyData(ztInputKeys_Clear,              "Clear",                0,    0, VK_CLEAR);
	_zt_setKeyData(ztInputKeys_Return,             "Return",            '\n',    0, VK_RETURN);
	_zt_setKeyData(ztInputKeys_Shift,              "Shift",                0,    0, VK_SHIFT);
	_zt_setKeyData(ztInputKeys_Control,            "Control",              0,    0, VK_CONTROL);
	_zt_setKeyData(ztInputKeys_Menu,               "Menu",                 0,    0, VK_MENU);
	_zt_setKeyData(ztInputKeys_Pause,              "Pause",                0,    0, VK_PAUSE);
	_zt_setKeyData(ztInputKeys_Capital,            "Capital",              0,    0, VK_CAPITAL);
	_zt_setKeyData(ztInputKeys_Kana,               "Kana",                 0,    0, VK_KANA);
	_zt_setKeyData(ztInputKeys_Hangul,             "Hangul",               0,    0, VK_HANGUL);
	_zt_setKeyData(ztInputKeys_Junja,              "Junja",                0,    0, VK_JUNJA);
	_zt_setKeyData(ztInputKeys_Final,              "Final",                0,    0, VK_FINAL);
	_zt_setKeyData(ztInputKeys_Hanja,              "Hanja",                0,    0, VK_HANJA);
	_zt_setKeyData(ztInputKeys_Kanji,              "Kanji",                0,    0, VK_KANJI);
	_zt_setKeyData(ztInputKeys_Escape,             "Escape",               0,    0, VK_ESCAPE);
	_zt_setKeyData(ztInputKeys_Convert,            "Convert",              0,    0, VK_CONVERT);
	_zt_setKeyData(ztInputKeys_Nonconvert,         "Nonconvert",           0,    0, VK_NONCONVERT);
	_zt_setKeyData(ztInputKeys_Accept,             "Accept",               0,    0, VK_ACCEPT);
	_zt_setKeyData(ztInputKeys_ModeChange,         "ModeChange",           0,    0, VK_MODECHANGE);
	_zt_setKeyData(ztInputKeys_Space,              "Space",             ' ',   ' ', VK_SPACE);
	_zt_setKeyData(ztInputKeys_Prior,              "Prior",                0,    0, VK_PRIOR);
	_zt_setKeyData(ztInputKeys_Next,               "Next",                 0,    0, VK_NEXT);
	_zt_setKeyData(ztInputKeys_End,                "End",                  0,    0, VK_END);
	_zt_setKeyData(ztInputKeys_Home,               "Home",                 0,    0, VK_HOME);
	_zt_setKeyData(ztInputKeys_Left,               "Left",                 0,    0, VK_LEFT);
	_zt_setKeyData(ztInputKeys_Up,                 "Up",                   0,    0, VK_UP);
	_zt_setKeyData(ztInputKeys_Right,              "Right",                0,    0, VK_RIGHT);
	_zt_setKeyData(ztInputKeys_Down,               "Down",                 0,    0, VK_DOWN);
	_zt_setKeyData(ztInputKeys_Select,             "Select",               0,    0, VK_SELECT);
	_zt_setKeyData(ztInputKeys_Print,              "Print",                0,    0, VK_PRINT);
	_zt_setKeyData(ztInputKeys_Execute,            "Execute",              0,    0, VK_EXECUTE);
	_zt_setKeyData(ztInputKeys_Snapshot,           "Snapshot",             0,    0, VK_SNAPSHOT);
	_zt_setKeyData(ztInputKeys_Insert,             "Insert",               0,    0, VK_INSERT);
	_zt_setKeyData(ztInputKeys_Delete,             "Delete",               0,    0, VK_DELETE);
	_zt_setKeyData(ztInputKeys_Help,               "Help",                 0,    0, VK_HELP);
	_zt_setKeyData(ztInputKeys_0,                  "0",                  '0',  ')', '0');
	_zt_setKeyData(ztInputKeys_1,                  "1",                  '1',  '!', '1');
	_zt_setKeyData(ztInputKeys_2,                  "2",                  '2',  '@', '2');
	_zt_setKeyData(ztInputKeys_3,                  "3",                  '3',  '#', '3');
	_zt_setKeyData(ztInputKeys_4,                  "4",                  '4',  '$', '4');
	_zt_setKeyData(ztInputKeys_5,                  "5",                  '5',  '%', '5');
	_zt_setKeyData(ztInputKeys_6,                  "6",                  '6',  '^', '6');
	_zt_setKeyData(ztInputKeys_7,                  "7",                  '7',  '&', '7');
	_zt_setKeyData(ztInputKeys_8,                  "8",                  '8',  '*', '8');
	_zt_setKeyData(ztInputKeys_9,                  "9",                  '9',  '(', '9');
	_zt_setKeyData(ztInputKeys_A,                  "A",                  'a',  'A', 'A');
	_zt_setKeyData(ztInputKeys_B,                  "B",                  'b',  'B', 'B');
	_zt_setKeyData(ztInputKeys_C,                  "C",                  'c',  'C', 'C');
	_zt_setKeyData(ztInputKeys_D,                  "D",                  'd',  'D', 'D');
	_zt_setKeyData(ztInputKeys_E,                  "E",                  'e',  'E', 'E');
	_zt_setKeyData(ztInputKeys_F,                  "F",                  'f',  'F', 'F');
	_zt_setKeyData(ztInputKeys_G,                  "G",                  'g',  'G', 'G');
	_zt_setKeyData(ztInputKeys_H,                  "H",                  'h',  'H', 'H');
	_zt_setKeyData(ztInputKeys_I,                  "I",                  'i',  'I', 'I');
	_zt_setKeyData(ztInputKeys_J,                  "J",                  'j',  'J', 'J');
	_zt_setKeyData(ztInputKeys_K,                  "K",                  'k',  'K', 'K');
	_zt_setKeyData(ztInputKeys_L,                  "L",                  'l',  'L', 'L');
	_zt_setKeyData(ztInputKeys_M,                  "M",                  'm',  'M', 'M');
	_zt_setKeyData(ztInputKeys_N,                  "N",                  'n',  'N', 'N');
	_zt_setKeyData(ztInputKeys_O,                  "O",                  'o',  'O', 'O');
	_zt_setKeyData(ztInputKeys_P,                  "P",                  'p',  'P', 'P');
	_zt_setKeyData(ztInputKeys_Q,                  "Q",                  'q',  'Q', 'Q');
	_zt_setKeyData(ztInputKeys_R,                  "R",                  'r',  'R', 'R');
	_zt_setKeyData(ztInputKeys_S,                  "S",                  's',  'S', 'S');
	_zt_setKeyData(ztInputKeys_T,                  "T",                  't',  'T', 'T');
	_zt_setKeyData(ztInputKeys_U,                  "U",                  'u',  'U', 'U');
	_zt_setKeyData(ztInputKeys_V,                  "V",                  'v',  'V', 'V');
	_zt_setKeyData(ztInputKeys_W,                  "W",                  'w',  'W', 'W');
	_zt_setKeyData(ztInputKeys_X,                  "X",                  'x',  'X', 'X');
	_zt_setKeyData(ztInputKeys_Y,                  "Y",                  'y',  'Y', 'Y');
	_zt_setKeyData(ztInputKeys_Z,                  "Z",                  'z',  'Z', 'Z');
	_zt_setKeyData(ztInputKeys_LeftWin,            "LeftWin",              0,    0, VK_LWIN);
	_zt_setKeyData(ztInputKeys_RightWin,           "RightWin",             0,    0, VK_RWIN);
	_zt_setKeyData(ztInputKeys_Apps,               "Apps",                 0,    0, VK_APPS);
	_zt_setKeyData(ztInputKeys_Sleep,              "Sleep",                0,    0, VK_SLEEP);
	_zt_setKeyData(ztInputKeys_Numpad0,            "Numpad0",            '0',    0, VK_NUMPAD0);
	_zt_setKeyData(ztInputKeys_Numpad1,            "Numpad1",            '1',    0, VK_NUMPAD1);
	_zt_setKeyData(ztInputKeys_Numpad2,            "Numpad2",            '2',    0, VK_NUMPAD2);
	_zt_setKeyData(ztInputKeys_Numpad3,            "Numpad3",            '3',    0, VK_NUMPAD3);
	_zt_setKeyData(ztInputKeys_Numpad4,            "Numpad4",            '4',    0, VK_NUMPAD4);
	_zt_setKeyData(ztInputKeys_Numpad5,            "Numpad5",            '5',    0, VK_NUMPAD5);
	_zt_setKeyData(ztInputKeys_Numpad6,            "Numpad6",            '6',    0, VK_NUMPAD6);
	_zt_setKeyData(ztInputKeys_Numpad7,            "Numpad7",            '7',    0, VK_NUMPAD7);
	_zt_setKeyData(ztInputKeys_Numpad8,            "Numpad8",            '8',    0, VK_NUMPAD8);
	_zt_setKeyData(ztInputKeys_Numpad9,            "Numpad9",            '9',    0, VK_NUMPAD9);
	_zt_setKeyData(ztInputKeys_Multiply,           "Multiply",           '*',    0, VK_MULTIPLY);
	_zt_setKeyData(ztInputKeys_Add,                "Add",                '+',    0, VK_ADD);
	_zt_setKeyData(ztInputKeys_Separator,          "Separator",            0,    0, VK_SEPARATOR);
	_zt_setKeyData(ztInputKeys_Substract,          "Substract",          '-',    0, VK_SUBTRACT);
	_zt_setKeyData(ztInputKeys_Decimal,            "Decimal",            '.',    0, VK_DECIMAL);
	_zt_setKeyData(ztInputKeys_Divide,             "Divide",             '/',    0, VK_DIVIDE);
	_zt_setKeyData(ztInputKeys_F1,                 "F1",                   0,    0, VK_F1);
	_zt_setKeyData(ztInputKeys_F2,                 "F2",                   0,    0, VK_F2);
	_zt_setKeyData(ztInputKeys_F3,                 "F3",                   0,    0, VK_F3);
	_zt_setKeyData(ztInputKeys_F4,                 "F4",                   0,    0, VK_F4);
	_zt_setKeyData(ztInputKeys_F5,                 "F5",                   0,    0, VK_F5);
	_zt_setKeyData(ztInputKeys_F6,                 "F6",                   0,    0, VK_F6);
	_zt_setKeyData(ztInputKeys_F7,                 "F7",                   0,    0, VK_F7);
	_zt_setKeyData(ztInputKeys_F8,                 "F8",                   0,    0, VK_F8);
	_zt_setKeyData(ztInputKeys_F9,                 "F9",                   0,    0, VK_F9);
	_zt_setKeyData(ztInputKeys_F10,                "F10",                  0,    0, VK_F10);
	_zt_setKeyData(ztInputKeys_F11,                "F11",                  0,    0, VK_F11);
	_zt_setKeyData(ztInputKeys_F12,                "F12",                  0,    0, VK_F12);
	_zt_setKeyData(ztInputKeys_F13,                "F13",                  0,    0, VK_F13);
	_zt_setKeyData(ztInputKeys_F14,                "F14",                  0,    0, VK_F14);
	_zt_setKeyData(ztInputKeys_F15,                "F15",                  0,    0, VK_F15);
	_zt_setKeyData(ztInputKeys_F16,                "F16",                  0,    0, VK_F16);
	_zt_setKeyData(ztInputKeys_F17,                "F17",                  0,    0, VK_F17);
	_zt_setKeyData(ztInputKeys_F18,                "F18",                  0,    0, VK_F18);
	_zt_setKeyData(ztInputKeys_F19,                "F19",                  0,    0, VK_F19);
	_zt_setKeyData(ztInputKeys_F20,                "F20",                  0,    0, VK_F20);
	_zt_setKeyData(ztInputKeys_F21,                "F21",                  0,    0, VK_F21);
	_zt_setKeyData(ztInputKeys_F22,                "F22",                  0,    0, VK_F22);
	_zt_setKeyData(ztInputKeys_F23,                "F23",                  0,    0, VK_F23);
	_zt_setKeyData(ztInputKeys_F24,                "F24",                  0,    0, VK_F24);
	_zt_setKeyData(ztInputKeys_NumLock,            "NumLock",              0,    0, VK_NUMLOCK);
	_zt_setKeyData(ztInputKeys_Scroll,             "Scroll",               0,    0, VK_SCROLL);
	_zt_setKeyData(ztInputKeys_LeftShift,          "LeftShift",            0,    0, VK_LSHIFT);
	_zt_setKeyData(ztInputKeys_RightShift,         "RightShift",           0,    0, VK_RSHIFT);
	_zt_setKeyData(ztInputKeys_LeftControl,        "LeftControl",          0,    0, VK_LCONTROL);
	_zt_setKeyData(ztInputKeys_RightControl,       "RightControl",         0,    0, VK_RCONTROL);
	_zt_setKeyData(ztInputKeys_LeftMenu,           "LeftMenu",             0,    0, VK_LMENU);
	_zt_setKeyData(ztInputKeys_RightMenu,          "RightMenu",            0,    0, VK_RMENU);
	_zt_setKeyData(ztInputKeys_BrowserBack,        "BrowserBack",          0,    0, VK_BROWSER_BACK);
	_zt_setKeyData(ztInputKeys_BrowserForward,     "BrowserForward",       0,    0, VK_BROWSER_FORWARD);
	_zt_setKeyData(ztInputKeys_BrowserRefresh,     "BrowserRefresh",       0,    0, VK_BROWSER_REFRESH);
	_zt_setKeyData(ztInputKeys_BrowserStop,        "BrowserStop",          0,    0, VK_BROWSER_STOP);
	_zt_setKeyData(ztInputKeys_BrowserSearch,      "BrowserSearch",        0,    0, VK_BROWSER_SEARCH);
	_zt_setKeyData(ztInputKeys_BrowserFavorites,   "BrowserFavorites",     0,    0, VK_BROWSER_FAVORITES);
	_zt_setKeyData(ztInputKeys_BrowserHome,        "BrowserHome",          0,    0, VK_BROWSER_HOME);
	_zt_setKeyData(ztInputKeys_VolumeMute,         "VolumeMute",           0,    0, VK_VOLUME_MUTE);
	_zt_setKeyData(ztInputKeys_VolumeDown,         "VolumeDown",           0,    0, VK_VOLUME_DOWN);
	_zt_setKeyData(ztInputKeys_VolumeUp,           "VolumeUp",             0,    0, VK_VOLUME_UP);
	_zt_setKeyData(ztInputKeys_MediaNextTrack,     "MediaNextTrack",       0,    0, VK_MEDIA_NEXT_TRACK);
	_zt_setKeyData(ztInputKeys_MediaPrevTrack,     "MediaPrevTrack",       0,    0, VK_MEDIA_PREV_TRACK);
	_zt_setKeyData(ztInputKeys_MediaStop,          "MediaStop",            0,    0, VK_MEDIA_STOP);
	_zt_setKeyData(ztInputKeys_MediaPlayPause,     "MediaPlayPause",       0,    0, VK_MEDIA_PLAY_PAUSE);
	_zt_setKeyData(ztInputKeys_LaunchMail,         "LaunchMail",           0,    0, VK_LAUNCH_MAIL);
	_zt_setKeyData(ztInputKeys_LaunchMediaSelect,  "LaunchMediaSelect",    0,    0, VK_LAUNCH_MEDIA_SELECT);
	_zt_setKeyData(ztInputKeys_LaunchApp1,         "LaunchApp1",           0,    0, VK_LAUNCH_APP1);
	_zt_setKeyData(ztInputKeys_LaunchApp2,         "LaunchApp2",           0,    0, VK_LAUNCH_APP2);
	_zt_setKeyData(ztInputKeys_Semicolon,          "Semicolon",          ';',  ':', VK_OEM_1);
	_zt_setKeyData(ztInputKeys_Plus,               "Plus",               '=',  '+', VK_OEM_PLUS);
	_zt_setKeyData(ztInputKeys_Comma,              "Comma",              ',',  '<', VK_OEM_COMMA);
	_zt_setKeyData(ztInputKeys_Minus,              "Minus",              '-',  '_', VK_OEM_MINUS);
	_zt_setKeyData(ztInputKeys_Period,             "Period",             '.',  '>', VK_OEM_PERIOD);
	_zt_setKeyData(ztInputKeys_ForwardSlash,       "ForwardSlash",       '/',  '?', VK_OEM_2);
	_zt_setKeyData(ztInputKeys_Tilda,              "Tilda",              '`',  '~', VK_OEM_3);
	_zt_setKeyData(ztInputKeys_OpenBrace,          "OpenBrace",          '[',  '{', VK_OEM_4);
	_zt_setKeyData(ztInputKeys_BackSlash,          "BackSlash",         '\\',  '|', VK_OEM_5);
	_zt_setKeyData(ztInputKeys_CloseBrace,         "CloseBrace",         ']',  '}', VK_OEM_6);
	_zt_setKeyData(ztInputKeys_Apos,               "Apos",              '\'', '\"', VK_OEM_7);
	_zt_setKeyData(ztInputKeys_Oem_8,              "Oem_8",                0,    0, VK_OEM_8);
	_zt_setKeyData(ztInputKeys_Oem_102,            "Oem_102",              0,    0, VK_OEM_102);
	_zt_setKeyData(ztInputKeys_ProcessKey,         "ProcessKey",           0,    0, VK_PROCESSKEY);
	_zt_setKeyData(ztInputKeys_Packet,             "Packet",               0,    0, VK_PACKET);
	_zt_setKeyData(ztInputKeys_Attn,               "Attn",                 0,    0, VK_ATTN);
	_zt_setKeyData(ztInputKeys_Crsel,              "Crsel",                0,    0, VK_CRSEL);
	_zt_setKeyData(ztInputKeys_Exsel,              "Exsel",                0,    0, VK_EXSEL);
	_zt_setKeyData(ztInputKeys_Ereof,              "Ereof",                0,    0, VK_EREOF);
	_zt_setKeyData(ztInputKeys_Play,               "Play",                 0,    0, VK_PLAY);
	_zt_setKeyData(ztInputKeys_Zoom,               "Zoom",                 0,    0, VK_ZOOM);
	_zt_setKeyData(ztInputKeys_Pa1,                "Pa1",                  0,    0, VK_PA1);
	_zt_setKeyData(ztInputKeys_OemClear,           "OemClear",             0,    0, VK_OEM_CLEAR);
};

// ------------------------------------------------------------------------------------------------

bool zt_inputThisFrame()
{
	return zt_game->input_this_frame;
}

// ------------------------------------------------------------------------------------------------

ztInputKeys* zt_inputKeysAccessState()
{
	return zt_game->input_keys;
}

// ------------------------------------------------------------------------------------------------

void zt_inputKeysCopyState(ztInputKeys input_keys[ztInputKeys_MAX])
{
	ZT_PROFILE_INPUT("zt_inputKeysCopyState");
	int size = sizeof(ztInputKeys) * ztInputKeys_MAX;
	zt_memCpy(input_keys, size, zt_game->input_keys, size);
}

// ------------------------------------------------------------------------------------------------

void zt_inputGetKeyStrokes(ztInputKeys_Enum key_strokes[ZT_MAX_INPUT_KEYSTROKES])
{
	ZT_PROFILE_INPUT("zt_inputGetKeyStrokes");
	int size = sizeof(ztInputKeys_Enum) * ZT_MAX_INPUT_KEYSTROKES;
	zt_memCpy(key_strokes, size, zt_game->input_key_strokes, size);
}

// ------------------------------------------------------------------------------------------------

ztInputMouse* zt_inputMouseAccessState()
{
	return &zt_game->input_mouse;
}

// ------------------------------------------------------------------------------------------------

void zt_inputMouseCopyState(ztInputMouse *input_mouse)
{
	ZT_PROFILE_INPUT("zt_inputMouseCopyState");
	zt_memCpy(input_mouse, zt_sizeof(ztInputMouse), &zt_game->input_mouse, zt_sizeof(ztInputMouse));
}

// ------------------------------------------------------------------------------------------------

void zt_inputMouseLook(bool mouse_look)
{
	zt_game->input_mouse_look = mouse_look;
}

// ------------------------------------------------------------------------------------------------

bool zt_inputMouseIsLook()
{
	return zt_game->input_mouse_look;
}

// ------------------------------------------------------------------------------------------------

void zt_inputMouseSetCursor(ztInputMouseCursor_Enum cursor)
{
	ZT_PROFILE_INPUT("zt_inputMouseSetCursor");
	switch (cursor)
	{
	case ztInputMouseCursor_None:		SetCursor(NULL); break;
	case ztInputMouseCursor_Arrow:		SetCursor(LoadCursor(NULL, IDC_ARROW)); break;
	case ztInputMouseCursor_ResizeNS:	SetCursor(LoadCursor(NULL, IDC_SIZENS)); break;
	case ztInputMouseCursor_ResizeEW:	SetCursor(LoadCursor(NULL, IDC_SIZEWE)); break;
	case ztInputMouseCursor_ResizeNWSE:	SetCursor(LoadCursor(NULL, IDC_SIZENWSE)); break;
	case ztInputMouseCursor_ResizeSWNE:	SetCursor(LoadCursor(NULL, IDC_SIZENESW)); break;
	}

	zt_game->input_mouse.cursor = cursor;
}

// ------------------------------------------------------------------------------------------------

ztInputController* zt_inputControllerAccessState(int idx)
{
	zt_assertReturnValOnFail(idx >= 0 && idx < ZT_MAX_INPUT_CONTROLLERS, nullptr);
	return &zt_game->input_controllers[idx];
}

// ------------------------------------------------------------------------------------------------

void zt_inputControllerCopyState(ztInputController *input_controller, int idx)
{
	ZT_PROFILE_INPUT("zt_inputControllerCopyState");
	zt_assertReturnOnFail(idx >= 0 && idx < ZT_MAX_INPUT_CONTROLLERS);
	zt_memCpy(input_controller, zt_sizeof(ztInputController), &zt_game->input_controllers[idx], zt_sizeof(ztInputController));
}

// ------------------------------------------------------------------------------------------------

zt_winOnly(void _zt_winControllerInputHapticFeedback(int idx, r32 strength_low, r32 strength_high));

void zt_inputControllerTriggerHapticFeedback(int idx, r32 strength_low, r32 strength_high)
{
	ZT_PROFILE_INPUT("zt_inputControllerTriggerHapticFeedback");
	zt_winOnly(_zt_winControllerInputHapticFeedback(idx, strength_low, strength_high));
}

// ------------------------------------------------------------------------------------------------

void _zt_inputClearState( bool lost_focus )
{
	ZT_PROFILE_INPUT("_zt_inputClearState");
	zt_fiz(ztInputKeys_MAX) {
		zt_bitRemove(zt_game->input_keys[i].flags, ztInputKeyFlags_JustPressed);
		zt_bitRemove(zt_game->input_keys[i].flags, ztInputKeyFlags_JustReleased);
		zt_bitRemove(zt_game->input_keys[i].flags, ztInputKeyFlags_JustRepeated);
	}

	zt_fiz(zt_elementsOf(zt_game->input_key_strokes)) {
		zt_game->input_key_strokes[i] = ztInputKeys_Invalid;
	}
	zt_game->input_key_strokes_count = 0;

	zt_fiz(zt_elementsOf(zt_game->input_mouse.button_states)) {
		zt_bitRemove(zt_game->input_mouse.button_states[i], ztInputMouseFlags_JustPressed);
		zt_bitRemove(zt_game->input_mouse.button_states[i], ztInputMouseFlags_JustReleased);
	}

	zt_game->input_mouse.delta_x = zt_game->input_mouse.delta_y = 0;

	zt_fiz(ZT_MAX_INPUT_CONTROLLERS) {
		zt_fjz(zt_elementsOf(zt_game->input_controllers[i].button_states)) {
			zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_JustPressed);
			zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_JustReleased);
		}
	}

	if (lost_focus) {
		zt_fiz(ztInputKeys_MAX) {
			if (zt_bitIsSet(zt_game->input_keys[i].flags, ztInputKeyFlags_Pressed)) {
				zt_game->input_keys[i].flags = ztInputKeyFlags_JustReleased;
			}
		}

		zt_fiz(zt_elementsOf(zt_game->input_mouse.button_states)) {
			if (zt_bitIsSet(zt_game->input_mouse.button_states[i], ztInputMouseFlags_Pressed)) {
				zt_game->input_mouse.button_states[i] = ztInputMouseFlags_JustReleased;
			}
		}

		zt_fiz(ZT_MAX_INPUT_CONTROLLERS) {
			zt_fjz(zt_elementsOf(zt_game->input_controllers[i].button_states)) {
				if (zt_bitIsSet(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_Pressed)) {
					zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_JustReleased);
					zt_game->input_controllers[i].button_times[j] = 0;
				}
			}
			zt_fjz(zt_elementsOf(zt_game->input_controllers[i].analog_values)) {
				zt_game->input_controllers[i].analog_values[j] = 0;
			}
		}
	}

	zt_game->input_this_frame = false;
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
	else if (renderer == ztRenderer_DirectX) {
		zt_noDirectxSupport(return false);

		if (v_major == 11) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListMake(ztDrawList *draw_list, i32 max_commands, i32 flags, ztMemoryArena *arena)
{
	ZT_PROFILE_RENDERING("zt_drawListMake");
	zt_returnValOnNull(draw_list, false);

	draw_list->commands = zt_mallocStructArrayArena(ztDrawCommand, max_commands, arena);
	if (!draw_list->commands) {
		return false;
	}

	draw_list->commands_size = max_commands;
	draw_list->commands_count = 0;
	draw_list->flags = flags;
	draw_list->arena = arena;

	zt_debugOnly(draw_list->active_shaders = draw_list->active_textures = 0);

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_drawListFree(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListFree");
	if (draw_list == nullptr) {
		return;
	}

	if (draw_list->commands) {
		zt_freeArena(draw_list->commands, draw_list->arena);
	}

	zt_memSet(draw_list, sizeof(ztDrawList), 0);
}

// ------------------------------------------------------------------------------------------------

#define _zt_drawListCheck(draw_list) zt_returnValOnNull(draw_list, false); if (draw_list->commands_count >= draw_list->commands_size) { zt_assert(false && "ztDrawList command overflow"); return false; };

#define _zt_drawListVerifyShader(draw_list) zt_debugOnly(zt_assert(draw_list->active_shaders > 0))
#define _zt_drawListVerifyTexture(draw_list) zt_debugOnly(zt_assert(draw_list->active_textures > 0))

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddPoint(ztDrawList *draw_list, const ztVec3& p)
{
	ZT_PROFILE_RENDERING("zt_drawListAddPoint");
	_zt_drawListCheck(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_Point;
	command->point = p;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddLine(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2)
{
	ZT_PROFILE_RENDERING("zt_drawListAddLine");
	_zt_drawListCheck(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_Line;
	command->line[0] = p1;
	command->line[1] = p2;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddLine(ztDrawList *draw_list, const ztVec3 p[2])
{
	ZT_PROFILE_RENDERING("zt_drawListAddLine");
	_zt_drawListCheck(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_Line;
	command->line[0] = p[0];
	command->line[1] = p[1];

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyTriangle(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3)
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyTriangle");
	if (!zt_drawListAddLine(draw_list, p1, p2)) return false;
	if (!zt_drawListAddLine(draw_list, p2, p3)) return false;
	if (!zt_drawListAddLine(draw_list, p3, p1)) return false;
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyTriangle(ztDrawList *draw_list, const ztVec3 p[3])
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyTriangle");
	zt_fiz(3) {
		if (!zt_drawListAddLine(draw_list, p[i], p[(i + 1) % 3])) {
			return false;
		}
	}
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyQuad(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3, const ztVec3& p4)
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyQuad");
	if (!zt_drawListAddLine(draw_list, p1, p2)) return false;
	if (!zt_drawListAddLine(draw_list, p2, p3)) return false;
	if (!zt_drawListAddLine(draw_list, p3, p4)) return false;
	if (!zt_drawListAddLine(draw_list, p4, p1)) return false;
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyRect(ztDrawList *draw_list, const ztVec2& pos, const ztVec2& size)
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyRect");
	return zt_drawListAddEmptyRect(draw_list, ztVec3(pos, 0), size);
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyRect(ztDrawList *draw_list, const ztVec3& pos, const ztVec2& size)
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyRect");
	r32 ppu = zt_pixelsPerUnit();
	r32 pix = 1 / ppu;

	ztVec3 p[4] = {
		ztVec3(pos.x - size.x / 2.f + pix, pos.y + size.y / 2.f - pix, pos.z),
		ztVec3(pos.x - size.x / 2.f + pix, pos.y - size.y / 2.f, pos.z),
		ztVec3(pos.x + size.x / 2.f,       pos.y - size.y / 2.f, pos.z),
		ztVec3(pos.x + size.x / 2.f,       pos.y + size.y / 2.f - pix, pos.z)
	};

	zt_fiz(4) {
		zt_fjz(2) zt_alignToPixel(&p[i].values[j], ppu); // ignore the z value
	}

	return zt_drawListAddEmptyQuad(draw_list, p);
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyQuad(ztDrawList *draw_list, const ztVec3 p[4])
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyQuad");
	zt_fiz(4) {
		if (!zt_drawListAddLine(draw_list, p[i], p[(i + 1) % 4])) {
			return false;
		}
	}
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyCubeFromCenterSize(ztDrawList *draw_list, const ztVec3& pos, const ztVec3& size)
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyCubeFromCenterSize");
	r32 half_x = size.x / 2.f;
	r32 half_y = size.y / 2.f;
	r32 half_z = size.z / 2.f;

	zt_drawListAddEmptyQuad(draw_list, ztVec3(pos.x - half_x, pos.y + half_y, pos.z + half_z),
									   ztVec3(pos.x - half_x, pos.y + half_y, pos.z - half_z),
									   ztVec3(pos.x + half_x, pos.y + half_y, pos.z - half_z),
									   ztVec3(pos.x + half_x, pos.y + half_y, pos.z + half_z)); // top face

	zt_drawListAddEmptyQuad(draw_list, ztVec3(pos.x - half_x, pos.y - half_y, pos.z + half_z),
									   ztVec3(pos.x - half_x, pos.y - half_y, pos.z - half_z),
									   ztVec3(pos.x + half_x, pos.y - half_y, pos.z - half_z),
									   ztVec3(pos.x + half_x, pos.y - half_y, pos.z + half_z)); // bottom face

	zt_drawListAddLine(draw_list, ztVec3(pos.x - half_x, pos.y + half_y, pos.z + half_z), ztVec3(pos.x - half_x, pos.y - half_y, pos.z + half_z));
	zt_drawListAddLine(draw_list, ztVec3(pos.x - half_x, pos.y + half_y, pos.z - half_z), ztVec3(pos.x - half_x, pos.y - half_y, pos.z - half_z));
	zt_drawListAddLine(draw_list, ztVec3(pos.x + half_x, pos.y + half_y, pos.z - half_z), ztVec3(pos.x + half_x, pos.y - half_y, pos.z - half_z));
	zt_drawListAddLine(draw_list, ztVec3(pos.x + half_x, pos.y + half_y, pos.z + half_z), ztVec3(pos.x + half_x, pos.y - half_y, pos.z + half_z));

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddEmptyCubeFromMinMax(ztDrawList *draw_list, const ztVec3& min, const ztVec3& max)
{
	ZT_PROFILE_RENDERING("zt_drawListAddEmptyCubeFromMinMax");
	ztVec3 size = ztVec3((max.x - min.x), (max.y - min.y), (max.z - min.z));
	ztVec3 pos  = min + (size * .5f);
	return zt_drawListAddEmptyCubeFromCenterSize(draw_list, pos, size);
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFilledTriangle(ztDrawList *draw_list, const ztVec3 p[3], const ztVec2 uvs[3], const ztVec3 normals[3])
{
	ZT_PROFILE_RENDERING("zt_drawListAddFilledTriangle");
	_zt_drawListCheck(draw_list);
	_zt_drawListVerifyTexture(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_Triangle;
	
	zt_fiz(3) command->tri_pos[i] = p[i];
	zt_fiz(3) command->tri_uv[i] = uvs[i];
	zt_fiz(3) command->tri_norm[i] = normals[i];

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFilledQuad(ztDrawList *draw_list, const ztVec3& p1, const ztVec3& p2, const ztVec3& p3, const ztVec3& p4, const ztVec2& uv1, const ztVec2& uv2, const ztVec2& uv3, const ztVec2& uv4, const ztVec3& n1, const ztVec3& n2, const ztVec3& n3, const ztVec3& n4)
{
	ZT_PROFILE_RENDERING("zt_drawListAddFilledQuad");
	_zt_drawListVerifyTexture(draw_list);

	{
		_zt_drawListCheck(draw_list);
		auto *command = &draw_list->commands[draw_list->commands_count++];

		command->type = ztDrawCommandType_Triangle;

		command->tri_pos[0] = p1;
		command->tri_pos[1] = p2;
		command->tri_pos[2] = p3;

		command->tri_uv[0] = uv1;
		command->tri_uv[1] = uv2;
		command->tri_uv[2] = uv3;

		command->tri_norm[0] = n1;
		command->tri_norm[1] = n2;
		command->tri_norm[2] = n3;
	}
	{
		_zt_drawListCheck(draw_list);
		auto *command = &draw_list->commands[draw_list->commands_count++];

		command->type = ztDrawCommandType_Triangle;

		command->tri_pos[0] = p1;
		command->tri_pos[1] = p3;
		command->tri_pos[2] = p4;

		command->tri_uv[0] = uv1;
		command->tri_uv[1] = uv3;
		command->tri_uv[2] = uv4;

		command->tri_norm[0] = n1;
		command->tri_norm[1] = n3;
		command->tri_norm[2] = n4;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFilledQuad(ztDrawList *draw_list, const ztVec3 p[4], const ztVec2 uvs[4], const ztVec3 normals[4])
{
	ZT_PROFILE_RENDERING("zt_drawListAddFilledQuad");
	_zt_drawListVerifyTexture(draw_list);

	zt_fjz(2) {
		_zt_drawListCheck(draw_list);
		auto *command = & draw_list->commands[draw_list->commands_count++];

		command->type = ztDrawCommandType_Triangle;

		command->tri_pos[0] = p[0];
		command->tri_pos[1] = p[1 + j];
		command->tri_pos[2] = p[2 + j];

		command->tri_uv[0] = uvs[0];
		command->tri_uv[1] = uvs[1 + j];
		command->tri_uv[2] = uvs[2 + j];

		command->tri_norm[0] = normals[0];
		command->tri_norm[1] = normals[1 + j];
		command->tri_norm[2] = normals[2 + j];
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFilledRect2D(ztDrawList *draw_list, const ztVec2& p, const ztVec2& size, const ztVec2& uv_nw, const ztVec2& uv_se)
{
	return zt_drawListAddFilledRect2D(draw_list, ztVec3(p.x, p.y, 0), size, uv_nw, uv_se);
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFilledRect2D(ztDrawList *draw_list, const ztVec3& p, const ztVec2& size, const ztVec2& uv_nw, const ztVec2& uv_se)
{
	ZT_PROFILE_RENDERING("zt_drawListAddFilledRect2D");
	r32 half_w = size.x / 2.f;
	r32 half_h = size.y / 2.f;

	return zt_drawListAddFilledQuad(draw_list, 
		ztVec3(p.x - half_w, p.y + half_h, p.z),
		ztVec3(p.x - half_w, p.y - half_h, p.z),
		ztVec3(p.x + half_w, p.y - half_h, p.z),
		ztVec3(p.x + half_w, p.y + half_h, p.z),
										
		ztVec2(uv_nw.x, uv_nw.y),
		ztVec2(uv_nw.x, uv_se.y),
		ztVec2(uv_se.x, uv_se.y),
		ztVec2(uv_se.x, uv_nw.y),
		
		ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddBillboard(ztDrawList *draw_list, const ztVec3& pos_ctr, const ztVec2& size, const ztVec2& uv_nw, const ztVec2& uv_se, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_drawListAddBillboard");
	_zt_drawListCheck(draw_list);
	_zt_drawListVerifyTexture(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_Billboard;

	command->billboard_center = pos_ctr;
	command->billboard_size = size;
	command->billboard_uv = ztVec4(uv_nw, uv_se);
	command->billboard_flags = flags;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFilledPoly(ztDrawList *draw_list, const ztVec3 *p, int count, const ztVec2 uvs[4], const ztVec3 normals[4])
{
	ZT_PROFILE_RENDERING("zt_drawListAddFilledPoly");
	_zt_drawListVerifyTexture(draw_list);

	zt_fjz(count - 2) {
		_zt_drawListCheck(draw_list);
		auto *command = & draw_list->commands[draw_list->commands_count++];

		command->type = ztDrawCommandType_Triangle;

		command->tri_pos[0] = p[0];
		command->tri_pos[1] = p[1 + j];
		command->tri_pos[2] = p[2 + j];

		command->tri_uv[0] = uvs[0];
		command->tri_uv[1] = uvs[1 + j];
		command->tri_uv[2] = uvs[2 + j];

		command->tri_norm[0] = normals[0];
		command->tri_norm[1] = normals[1 + j];
		command->tri_norm[2] = normals[2 + j];
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

//#include <stdlib.h>

bool zt_drawListAddDrawList(ztDrawList *draw_list, ztDrawList *draw_list_to_add, const ztVec3& offset)
{
	ZT_PROFILE_RENDERING("zt_drawListAddDrawList");
	if (draw_list->commands_size - draw_list->commands_count >= draw_list_to_add->commands_count) {
		i32 size = zt_sizeof(ztDrawCommand) * draw_list_to_add->commands_count;
		zt_memCpy(&draw_list->commands[draw_list->commands_count], size, draw_list_to_add->commands, size);
		//memcpy(&draw_list->commands[draw_list->commands_count], draw_list_to_add->commands, size);
		draw_list->commands_count += draw_list_to_add->commands_count;

		if (offset != ztVec3::zero) {
			int start = draw_list->commands_count - draw_list_to_add->commands_count;
			for (int i = start; i < start + draw_list_to_add->commands_count; ++i) {
				ztDrawCommand *command = &draw_list->commands[i];
				switch (command->type)
				{
					case ztDrawCommandType_Point: {
						command->point.x += offset.x;
						command->point.y += offset.y;
						command->point.z += offset.z;
					} break;

					case ztDrawCommandType_Line: {
						zt_fiz(2) zt_fjz(3) command->line[i].values[j] += offset.values[j];
					} break;

					case ztDrawCommandType_Triangle: {
						zt_fiz(3) zt_fjz(3) command->tri_pos[i].values[j] += offset.values[j];
					} break;

					case ztDrawCommandType_ChangeClipping: {
						zt_fjz(2) command->clip_center.values[j] += offset.values[j];
					} break;

					case ztDrawCommandType_Billboard: {
						zt_fjz(3) command->billboard_center.values[j] += offset.values[j];
					} break;
				}
			}
		}
		return true;
	}
	else {
		zt_assert(false);
		return false;
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFrustum(ztDrawList *draw_list, ztFrustum *frustum)
{
	ZT_PROFILE_RENDERING("zt_drawListAddFrustum");
	if(!zt_drawListAddLine(draw_list, frustum->near_nw, frustum->near_ne)) return false;
	if(!zt_drawListAddLine(draw_list, frustum->near_ne, frustum->near_se)) return false;
	if(!zt_drawListAddLine(draw_list, frustum->near_se, frustum->near_sw)) return false;
	if(!zt_drawListAddLine(draw_list, frustum->near_sw, frustum->near_nw)) return false;

	if (!zt_drawListAddLine(draw_list, frustum->far_nw, frustum->far_ne)) return false;
	if (!zt_drawListAddLine(draw_list, frustum->far_ne, frustum->far_se)) return false;
	if (!zt_drawListAddLine(draw_list, frustum->far_se, frustum->far_sw)) return false;
	if (!zt_drawListAddLine(draw_list, frustum->far_sw, frustum->far_nw)) return false;

	if (!zt_drawListAddLine(draw_list, frustum->near_nw, frustum->far_nw)) return false;
	if (!zt_drawListAddLine(draw_list, frustum->near_ne, frustum->far_ne)) return false;
	if (!zt_drawListAddLine(draw_list, frustum->near_se, frustum->far_se)) return false;
	if (!zt_drawListAddLine(draw_list, frustum->near_sw, frustum->far_sw)) return false;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddFloorGrid(ztDrawList *draw_list, const ztVec3& center, r32 width, r32 depth, r32 grid_w, r32 grid_d)
{
	ZT_PROFILE_RENDERING("zt_drawListAddFloorGrid");
	r32 max_x = center.x + width / 2.f;
	r32 max_z = center.z + depth / 2.f;

	r32 x = center.x - width / 2.f;
	r32 z = center.z - depth / 2.f;

	while (z <= max_z) {
		if (!zt_drawListAddLine(draw_list, ztVec3(x, center.y, z), ztVec3(x + width, center.y, z))) {
			return false;
		}
		z += grid_d;
	}

	x = center.x - width / 2.f;
	z = center.z - depth / 2.f;

	while (x <= max_x) {
		if (!zt_drawListAddLine(draw_list, ztVec3(x, center.y, z), ztVec3(x, center.y, z + depth))) {
			return false;
		}
		x += grid_w;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddVertexArray(ztDrawList *draw_list, ztVertexArrayID vertex_array_id, ztVertexArrayDrawType_Enum draw_type)
{
	ZT_PROFILE_RENDERING("zt_drawListAddVertexArray");
	_zt_drawListCheck(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_VertexArray;
	command->vertex_array = vertex_array_id;
	command->vertex_array_draw_type = draw_type;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddAxis(ztDrawList *draw_list, r32 size, const ztVec3& center, const ztVec4& color_x, const ztVec4& color_y, const ztVec4& color_z)
{
	ZT_PROFILE_RENDERING("zt_drawListAddAxis");
	zt_drawListPushColor(draw_list, color_x);
	zt_drawListAddLine(draw_list, center, center + ztVec3(size, 0, 0));
	zt_drawListPopColor(draw_list);

	zt_drawListPushColor(draw_list, color_y);
	zt_drawListAddLine(draw_list, center, center + ztVec3(0, size, 0));
	zt_drawListPopColor(draw_list);

	zt_drawListPushColor(draw_list, color_z);
	zt_drawListAddLine(draw_list, center, center + ztVec3(0, 0, size));
	zt_drawListPopColor(draw_list);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddAxis(ztDrawList *draw_list, const ztMat4& mat, r32 size, const ztVec3& center, const ztVec4& color_x, const ztVec4& color_y, const ztVec4& color_z)
{
	ZT_PROFILE_RENDERING("zt_drawListAddAxis");
	ztVec3 t_center = mat * center;

	zt_drawListPushColor(draw_list, color_x);
	zt_drawListAddLine(draw_list, t_center, mat * (center + ztVec3(size, 0, 0)));
	zt_drawListPopColor(draw_list);

	zt_drawListPushColor(draw_list, color_y);
	zt_drawListAddLine(draw_list, t_center, mat * (center + ztVec3(0, size, 0)));
	zt_drawListPopColor(draw_list);

	zt_drawListPushColor(draw_list, color_z);
	zt_drawListAddLine(draw_list, t_center, mat * (center + ztVec3(0, 0, size)));
	zt_drawListPopColor(draw_list);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListAddPointMarker(ztDrawList *draw_list, const ztVec3& pos, r32 size, bool color_axis)
{
	ZT_PROFILE_RENDERING("zt_drawListAddPointMarker");
	if(color_axis) {
		zt_drawListPushColor(draw_list, ztColor_Red  ); zt_drawListAddLine(draw_list, pos - ztVec3(size / 2.f, 0, 0), pos + ztVec3(size / 2.f, 0, 0)); zt_drawListPopColor(draw_list);
		zt_drawListPushColor(draw_list, ztColor_Green); zt_drawListAddLine(draw_list, pos - ztVec3(0, size / 2.f, 0), pos + ztVec3(0, size / 2.f, 0)); zt_drawListPopColor(draw_list);
		zt_drawListPushColor(draw_list, ztColor_Blue ); zt_drawListAddLine(draw_list, pos - ztVec3(0, 0, size / 2.f), pos + ztVec3(0, 0, size / 2.f)); zt_drawListPopColor(draw_list);
	}
	else {
		zt_drawListAddLine(draw_list, pos - ztVec3(size / 2.f, 0, 0), pos + ztVec3(size / 2.f, 0, 0));
		zt_drawListAddLine(draw_list, pos - ztVec3(0, size / 2.f, 0), pos + ztVec3(0, size / 2.f, 0));
		zt_drawListAddLine(draw_list, pos - ztVec3(0, 0, size / 2.f), pos + ztVec3(0, 0, size / 2.f));
	}
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushShader(ztDrawList *draw_list, ztShaderID shader)
{
	ZT_PROFILE_RENDERING("zt_drawListPushShader");
	_zt_drawListCheck(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_ChangeShader;
	command->shader = shader;

	zt_debugOnly(draw_list->active_shaders++);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPopShader(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListPopShader");
	int pops = 1;
	zt_fizr(draw_list->commands_count - 1) {
		if (draw_list->commands[i].type == ztDrawCommandType_ChangeShader) {
			if (draw_list->commands[i].shader_pop) {
				pops += 1;
			}
			else if (pops-- == 0) {
				auto *command = &draw_list->commands[draw_list->commands_count++];
				command->type = ztDrawCommandType_ChangeShader;
				command->shader = draw_list->commands[i].shader;
				command->shader_pop = true;
				return true;
			}
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztShaderID zt_drawListGetCurrentShader(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListGetCurrentShader");
	_zt_drawListVerifyShader(draw_list);

	zt_fizr(draw_list->commands_count - 1) {
		if (draw_list->commands[i].type == ztDrawCommandType_ChangeShader) {
			return draw_list->commands[i].shader;
		}
	}

	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushColor(ztDrawList *draw_list, const ztColor& color)
{
	ZT_PROFILE_RENDERING("zt_drawListPushColor");
	_zt_drawListCheck(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_ChangeColor;
	command->color = color;
	command->color_pop = false;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPopColor(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListPopColor");
	_zt_drawListCheck(draw_list);

	int pops = 1;
	zt_fizr(draw_list->commands_count - 1) {
		if (draw_list->commands[i].type == ztDrawCommandType_ChangeColor) {
			if (draw_list->commands[i].color_pop) {
				pops += 1;
			}
			else if (pops-- == 0) {
				auto *command = &draw_list->commands[draw_list->commands_count++];
				command->type = ztDrawCommandType_ChangeColor;
				command->color = draw_list->commands[i].color;
				command->color_pop = true;
				return true;
			}
		}
	}

	auto *command = &draw_list->commands[draw_list->commands_count++];
	command->type = ztDrawCommandType_ChangeColor;
	command->color = ztColor(1,1,1,1);
	command->color_pop = true;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushTexture(ztDrawList *draw_list, ztTextureID tex_id)
{
	ZT_PROFILE_RENDERING("zt_drawListPushTexture");
	_zt_drawListCheck(draw_list);
	//_zt_drawListVerifyShader(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_ChangeTexture;
	command->texture[0] = tex_id;
	command->texture_count = 1;
	command->texture_pop = false;

	zt_assert(zt_game->textures[tex_id].renderer != ztRenderer_Invalid);

	zt_debugOnly(draw_list->active_textures++);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushTexture(ztDrawList *draw_list, ztTextureID *tex_ids, int tex_count)
{
	ZT_PROFILE_RENDERING("zt_drawListPushTexture");
	_zt_drawListCheck(draw_list);
	//_zt_drawListVerifyShader(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_ChangeTexture;

	if (tex_count > zt_elementsOf(command->texture)) {
		zt_assert(false && "Too many textures for a single draw list command");
		tex_count = zt_elementsOf(command->texture);
	}
	zt_fiz(tex_count) {
		command->texture[i] = tex_ids[i];
	}
	command->texture_count = tex_count;
	command->texture_pop = false;

	zt_debugOnly(draw_list->active_textures++);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPopTexture(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListPopTexture");
	int pops = 1;
	zt_fizr(draw_list->commands_count - 1) {
		if (draw_list->commands[i].type == ztDrawCommandType_ChangeTexture) {
			if (draw_list->commands[i].texture_pop) {
				pops += 1;
			}
			else if (pops-- == 0) {
				auto *command = &draw_list->commands[draw_list->commands_count++];
				command->type = ztDrawCommandType_ChangeTexture;
				zt_fjz(draw_list->commands[i].texture_count) command->texture[j] = draw_list->commands[i].texture[j];
				command->texture_count = draw_list->commands[i].texture_count;
				command->texture_pop = true;

				zt_debugOnly(draw_list->active_textures--);
				return true;
			}
		}
	}

	// if we're here, we need to set an empty texture command
	_zt_drawListCheck(draw_list);

	auto *command = & draw_list->commands[draw_list->commands_count++];

	command->type          = ztDrawCommandType_ChangeTexture;
	command->texture[0]    = 0;
	command->texture_count = 1;
	command->texture_pop   = false;

	zt_debugOnly(draw_list->active_textures--);
	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushClipRegion(ztDrawList *draw_list, ztVec2 center, ztVec2 size)
{
	ZT_PROFILE_RENDERING("zt_drawListPushClipRegion");
	_zt_drawListCheck(draw_list);
	zt_assert(size != ztVec2::zero);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_ChangeClipping;
	command->clip_center = center;
	command->clip_size = size;
	command->clip_idx = 0;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPopClipRegion(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListPopClipRegion");
	_zt_drawListCheck(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type = ztDrawCommandType_ChangeClipping;
	command->clip_center = ztVec2::zero;
	command->clip_size = ztVec2::zero;
	command->clip_idx = 0;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushOffset(ztDrawList *draw_list, const ztVec3& offset)
{
	ZT_PROFILE_RENDERING("zt_drawListPushOffset");
	_zt_drawListCheck(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type       = ztDrawCommandType_ChangeOffset;
	command->offset     = offset;
	command->offset_pop = false;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPopOffset(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListPopOffset");
	int pops = 1;
	zt_fizr(draw_list->commands_count - 1) {
		if (draw_list->commands[i].type == ztDrawCommandType_ChangeOffset) {
			if (draw_list->commands[i].offset_pop) {
				pops += 1;
			}
			else if (pops-- == 0) {
				auto *command = &draw_list->commands[draw_list->commands_count++];
				command->type       = ztDrawCommandType_ChangeOffset;
				command->offset     = draw_list->commands[i].offset;
				command->offset_pop = true;
				return true;
			}
		}
	}

	// if we're here, we need to set an empty offset command
	_zt_drawListCheck(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type       = ztDrawCommandType_ChangeOffset;
	command->offset     = ztVec3::zero;
	command->offset_pop = true;

	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPushTransform(ztDrawList *draw_list, const ztMat4& transform)
{
	ZT_PROFILE_RENDERING("zt_drawListPushTransform");
	_zt_drawListCheck(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type          = ztDrawCommandType_ChangeTransform;
	command->transform     = transform;
	command->transform_pop = false;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_drawListPopTransform(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListPopTransform");
	int pops = 1;
	zt_fizr(draw_list->commands_count - 1) {
		if (draw_list->commands[i].type == ztDrawCommandType_ChangeTransform) {
			if (draw_list->commands[i].transform_pop) {
				pops += 1;
			}
			else if (pops-- == 0) {
				auto *command = &draw_list->commands[draw_list->commands_count++];
				command->type          = ztDrawCommandType_ChangeTransform;
				command->transform     = draw_list->commands[i].transform;
				command->transform_pop = true;
				return true;
			}
		}
	}

	// if we're here, we need to set an empty offset command
	_zt_drawListCheck(draw_list);

	auto *command = &draw_list->commands[draw_list->commands_count++];

	command->type          = ztDrawCommandType_ChangeTransform;
	command->transform     = ztMat4::identity;
	command->transform_pop = true;

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_drawListReset(ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_drawListReset");
	draw_list->commands_count = 0;
	zt_debugOnly(draw_list->active_shaders = draw_list->active_textures = 0);
}

// ------------------------------------------------------------------------------------------------

#undef 	_zt_drawListCheck

// ------------------------------------------------------------------------------------------------

void zt_renderDrawList(ztCamera *camera, ztDrawList *draw_list, const ztColor& clear, i32 flags, ztTextureID render_target_id)
{
	zt_returnOnNull(draw_list);

	ztDrawList *draw_lists_arr[1] = {draw_list};
	zt_renderDrawLists(camera, draw_lists_arr, 1, clear, flags, render_target_id);
}

// ------------------------------------------------------------------------------------------------

#define ztRenderDrawListVertexArraySize	3 * 1024 * 8
#define ztRenderDrawListVertexByteSize (ztRenderDrawListVertexArraySize * 48)

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_rendererCheckToResetStats()
{	
	if (zt_game->last_drawn_frame != zt_game->game_details.current_frame) {
		zt_game->game_details.prev_frame = zt_game->game_details.curr_frame;
		zt_game->game_details.curr_frame.shader_switches = zt_game->game_details.curr_frame.texture_switches = zt_game->game_details.curr_frame.triangles_drawn = zt_game->game_details.curr_frame.draw_calls = 0;
		zt_game->last_drawn_frame = zt_game->game_details.current_frame;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_renderDrawLists(ztCamera *camera, ztDrawList **draw_lists, int draw_lists_count, const ztColor& clear, i32 flags, ztTextureID render_target_id)
{
	ZT_PROFILE_RENDERING("zt_renderDrawLists");
	_zt_rendererCheckToResetStats();

	zt_returnOnNull(camera);
	zt_returnOnNull(draw_lists);

	if (draw_lists_count == 0) {
		return;
	}

	if (!zt_bitIsSet(flags, ztRenderDrawListFlags_NoClear) && render_target_id == ztInvalidID) {
		zt_rendererClear(clear);
	}

#if 0
	zt_fiz(draw_lists_count) {
		ztDrawList *draw_list = draw_lists[i];


	}
#else

	byte *mem = zt_game->renderer_memory;
	i32 mem_left = zt_game->renderer_memory_size;

	struct ztCompileClipRegion
	{
		ztDrawCommand *command;
	};

	struct ztCompileItem
	{
		ztDrawCommand *command;
		ztCompileItem *next;

		ztCompileClipRegion *clip_region;
	};

	struct ztCompileTexture
	{
		ztCompileItem *item;
		ztCompileItem *last_item;
		int cnt_display_items;

		ztDrawCommand *command;
		ztCompileTexture *next;
	};

	struct ztCompileShader
	{
		ztShaderID shader;
		ztCompileTexture *texture;
	};

	ztCompileShader *shaders[1024];
	i32 shaders_count = 0;

	int clip_regions_count = 0;
	zt_fiz(draw_lists_count) {
		ztDrawList *draw_list = draw_lists[i];
		zt_assert(draw_list);
		zt_fjz(draw_list->commands_count) {
			if (draw_list->commands[j].type == ztDrawCommandType_ChangeClipping && draw_list->commands[j].clip_size != ztVec2::zero) {
				clip_regions_count += 1;
			}
		}
	}

	ztCompileClipRegion* clip_regions = clip_regions_count == 0 ? nullptr : (ztCompileClipRegion*)mem;

	mem += zt_sizeof(ztCompileClipRegion) * clip_regions_count;
	mem_left -= zt_sizeof(ztCompileClipRegion) * clip_regions_count;
	zt_assert(mem_left >= 0);

	{
		int clip_stack[512];
		int clip_stack_idx = -1;

		clip_regions_count = 0;
		zt_fiz(draw_lists_count) {
			ztDrawList *draw_list = draw_lists[i];
			zt_assert(draw_list);
			zt_fjz(draw_list->commands_count) {
				if (draw_list->commands[j].type == ztDrawCommandType_ChangeClipping) {
					if (draw_list->commands[j].clip_size != ztVec2::zero) {
						clip_stack[++clip_stack_idx] = clip_regions_count;
						clip_regions[clip_regions_count].command = &draw_list->commands[j];
						clip_regions_count += 1;
					}
					else {
						clip_stack_idx--;
					}
					draw_list->commands[j].clip_idx = clip_stack_idx >= 0 ? clip_stack[clip_stack_idx] : -1;
				}
			}
		}

		zt_assert(clip_stack_idx == -1); // if you're here, you have mismatching push/pop clip regions
	}

#	define _zt_castMem(type) (type*)mem; mem += zt_sizeof(type); mem_left -= zt_sizeof(type); zt_assert(mem_left >= 0); // if you assert here, you need more ztGameSettings::renderer_memory

	struct local
	{
		static bool texturesMatch(ztDrawCommand *cmd1, ztDrawCommand *cmd2)
		{
			ZT_PROFILE_RENDERING("zt_renderDrawLists::local::texturesMatch");

			if (cmd1 == nullptr ) {
				return cmd2->texture_count == 0;
			}
			if (cmd1->texture_count != cmd2->texture_count) {
				return false;
			}
			zt_fiz(cmd1->texture_count) {
				if (cmd1->texture[i] != cmd2->texture[i]) {
					return false;
				}
			}
			return true;
		}

		static byte *processForShader(ztCamera *camera, ztDrawList **draw_lists, int draw_lists_count, i32 flags, ztShaderID shader_id, byte *mem, i32 &mem_left, ztCompileShader **shader, ztCompileClipRegion *clip_regions)
		{
			ZT_PROFILE_RENDERING("zt_renderDrawLists::local::processForShader");

			ztCompileShader *cmp_shader = _zt_castMem(ztCompileShader);
			cmp_shader->shader = shader_id;
			cmp_shader->texture = nullptr;

			ztCompileTexture *cmp_texture = nullptr;
			ztCompileClipRegion *cmp_clip_region = nullptr;

			if (shader_id == ztInvalidID) {
				cmp_texture = _zt_castMem(ztCompileTexture);
				cmp_texture->command = nullptr;
				cmp_texture->next = nullptr;
				cmp_texture->item = nullptr;
				cmp_texture->last_item = nullptr;
				cmp_texture->cnt_display_items = 0;
				cmp_shader->texture = cmp_texture;

				// all lines and points go here
				zt_fiz(draw_lists_count) {
					ztDrawList *draw_list = draw_lists[i];
					zt_assert(draw_list != nullptr);

					ztCompileItem *cmp_item_last = nullptr;

					// extract points next
					zt_fjz(draw_list->commands_count) {
						ztDrawCommand *command = &draw_list->commands[j];
						if (command->type == ztDrawCommandType_ChangeColor || command->type == ztDrawCommandType_ChangeTransform || command->type == ztDrawCommandType_Point) {
							ztCompileItem *cmp_item = _zt_castMem(ztCompileItem);
							cmp_item->command = command;
							cmp_item->clip_region = nullptr;
							zt_singleLinkAddToEnd(cmp_texture->item, cmp_item);
							cmp_texture->cnt_display_items += 1;
						}
					}

					// extract lines next
					zt_fjz(draw_list->commands_count) {
						ztDrawCommand *command = &draw_list->commands[j];
						if (command->type == ztDrawCommandType_ChangeColor || command->type == ztDrawCommandType_ChangeTransform || command->type == ztDrawCommandType_Line) {
							ztCompileItem *cmp_item = _zt_castMem(ztCompileItem);
							cmp_item->command = command;
							cmp_item->clip_region = nullptr;
//							zt_singleLinkAddToEnd(cmp_texture->item, cmp_item);
//							cmp_texture->cnt_display_items += 1;
							if (cmp_item_last == nullptr) {
								cmp_texture->last_item = cmp_item_last = cmp_item;
								zt_singleLinkAddToEnd(cmp_texture->item, cmp_item);
							}
							else {
								cmp_item_last->next = cmp_item;
								cmp_item_last = cmp_item;
								cmp_item_last->next = nullptr;
								cmp_texture->last_item = cmp_item_last;
							}
						}
					}
				}
			}
			else {
				cmp_texture = _zt_castMem(ztCompileTexture);
				cmp_texture->command = nullptr;
				cmp_texture->item = nullptr;
				cmp_texture->last_item = nullptr;
				cmp_texture->cnt_display_items = 0;
				cmp_texture->next = nullptr;
				cmp_shader->texture = cmp_texture;

				zt_fiz(draw_lists_count) {
					ztDrawList *draw_list = draw_lists[i];
					zt_assert(draw_list != nullptr);

					bool ignore_shader = true;

					// extract all textures
					zt_fjz(draw_list->commands_count) {
						ztDrawCommand *command = &draw_list->commands[j];
						if (command->type == ztDrawCommandType_ChangeShader) {
							ignore_shader = command->shader != shader_id;
						}
						if (!ignore_shader) {
							if (command->type == ztDrawCommandType_ChangeTexture) {
								zt_linkFind(cmp_shader->texture, cmp_texture, texturesMatch(cmp_texture->command, command));
								if (cmp_texture == nullptr) {
									cmp_texture = _zt_castMem(ztCompileTexture);
									cmp_texture->command = command;
									cmp_texture->item = nullptr;
									cmp_texture->last_item = nullptr;
									cmp_texture->cnt_display_items = 0;
									cmp_texture->next = nullptr;
									zt_singleLinkAddToEnd(cmp_shader->texture, cmp_texture);
								}
							}
						}
					}

					// extract display elements.  we sort them out so that things can be batched efficiently
					ztDrawCommandType_Enum extract[] = { ztDrawCommandType_Triangle, ztDrawCommandType_Billboard, ztDrawCommandType_VertexArray };

					zt_fkz(zt_elementsOf(extract)) {
						cmp_texture = cmp_shader->texture;

						cmp_clip_region = nullptr;
						ztCompileItem *cmp_item_last = nullptr;

						ignore_shader = true;
						zt_fjz(draw_list->commands_count) {
							ztDrawCommand *command = &draw_list->commands[j];

							if (command->type == ztDrawCommandType_ChangeShader) {
								ignore_shader = command->shader != shader_id;
							}
							if (command->type == ztDrawCommandType_ChangeClipping) {
								cmp_clip_region = command->clip_idx < 0 ? nullptr : &clip_regions[command->clip_idx];
							}
							if (!ignore_shader) {
								if (command->type == ztDrawCommandType_ChangeTexture) {
									zt_linkFind(cmp_shader->texture, cmp_texture, texturesMatch(cmp_texture->command, command));
									zt_assert(cmp_texture != nullptr);
									cmp_item_last = cmp_texture->last_item;
								}
								if (command->type == extract[k] || command->type == ztDrawCommandType_ChangeColor) {
									ztCompileItem *cmp_item = _zt_castMem(ztCompileItem);
									cmp_item->command = command;
									cmp_item->clip_region = cmp_clip_region;
									if (cmp_item_last == nullptr) {
										cmp_texture->last_item = cmp_item_last = cmp_item;
										zt_singleLinkAddToEnd(cmp_texture->item, cmp_item);
									}
									else {
										cmp_item_last->next = cmp_item;
										cmp_item_last = cmp_item;
										cmp_item_last->next = nullptr;
										cmp_texture->last_item = cmp_item_last;
									}
									cmp_texture->cnt_display_items += command->type == ztDrawCommandType_ChangeColor ? 0 : 1;
								}
							}
						}
					}
				}
			}

			*shader = cmp_shader;


			return mem;
		}

		static bool processedShader(ztShaderID shader_id, ztCompileShader **shaders, i32 shaders_count)
		{
			ZT_PROFILE_RENDERING("zt_renderDrawLists::local::processShader");

			zt_fiz(shaders_count) {
				if (shaders[i]->shader == shader_id) {
					return true;
				}
			}
			return false;
		}
	};

	if (!zt_bitIsSet(flags, ztRenderDrawListFlags_NoDepthTest)) {
		zt_fiz(draw_lists_count) {
			ztDrawList *draw_list = draw_lists[i];
			zt_assert(draw_list != nullptr);

			zt_fjz(draw_list->commands_count) {
				ztDrawCommand *command = &draw_list->commands[j];

				switch (command->type)
				{
					case ztDrawCommandType_ChangeShader: {
						if (!local::processedShader(command->shader, shaders, shaders_count)) {
							zt_assert(shaders_count < zt_elementsOf(shaders));
							mem = local::processForShader(camera, draw_lists, draw_lists_count, flags, command->shader, mem, mem_left, &shaders[shaders_count++], clip_regions);
						}
					} break;
				}
			}
		}

		// process non-shader commands last
		local::processForShader(camera, draw_lists, draw_lists_count, flags, ztInvalidID, mem, mem_left, &shaders[shaders_count++], clip_regions);
	}
	else {
		// there's no depth testing, so we just display everything as it came in
		ZT_PROFILE_RENDERING("zt_renderDrawLists::no depth");

		ztCompileShader *cmp_shader = shaders[shaders_count++] = _zt_castMem(ztCompileShader);
		ztShaderID current_shader = cmp_shader->shader = ztInvalidID;

		ztCompileTexture *cmp_texture = cmp_shader->texture = _zt_castMem(ztCompileTexture);
		cmp_texture->command = nullptr;
		cmp_texture->item = nullptr;
		cmp_texture->last_item = nullptr;
		cmp_texture->cnt_display_items = 0;
		cmp_texture->next = nullptr;
		int current_textures_count = 0;
		ztTextureID current_textures[ZT_DRAW_COMMAND_MAX_TEXTURES];
		zt_fiz(zt_elementsOf(current_textures)) {
			current_textures[i] = ztInvalidID;
		}

		ztCompileClipRegion *cmp_clip_region = nullptr;
		ztCompileItem *cmp_item_last = nullptr;

		zt_fiz(draw_lists_count) {
			ztDrawList *draw_list = draw_lists[i];
			zt_assert(draw_list != nullptr);

			zt_fjz(draw_list->commands_count) {
				ztDrawCommand *command = &draw_list->commands[j];

				switch (command->type)
				{
					case ztDrawCommandType_ChangeShader: {
						if (command->shader != current_shader) {
							zt_assertReturnOnFail(shaders_count < zt_elementsOf(shaders));
							cmp_shader = shaders[shaders_count++] = _zt_castMem(ztCompileShader);
							cmp_shader->shader = command->shader;
							cmp_texture = cmp_shader->texture = _zt_castMem(ztCompileTexture);
							cmp_texture->command = nullptr;
							cmp_texture->item = nullptr;
							cmp_texture->last_item = nullptr;
							cmp_texture->cnt_display_items = 0;
							cmp_texture->next = nullptr;
							current_shader = command->shader;

							zt_fiz(zt_elementsOf(current_textures)) {
								current_textures[i] = ztInvalidID;
							}
						}
					} break;

					case ztDrawCommandType_ChangeTexture: {
						{
							// make sure the last texture used actually has items, otherwise, remove it from the list
							ztCompileTexture *cmp_tex = cmp_shader->texture;
							ztCompileTexture *cmp_prev = nullptr;

							while (cmp_tex) {
								if (cmp_tex->next) {
									cmp_prev = cmp_tex;
									cmp_tex = cmp_tex->next;
								}
								else break;
							}

							if (cmp_tex) {
								if (cmp_tex->cnt_display_items == 0) {
									if (cmp_prev) {
										cmp_prev->next = nullptr;
										current_textures_count = cmp_prev->command ? cmp_prev->command->texture_count : 0;
										zt_fiz(current_textures_count) {
											current_textures[i] = cmp_prev->command->texture[i];
										}
										cmp_item_last = cmp_prev->last_item;
										cmp_texture = cmp_prev;
									}
								}
							}
						}

						bool is_same = command->texture_count == current_textures_count;
						if (is_same) {
							zt_fiz(command->texture_count) {
								if (current_textures[i] != command->texture[i]) {
									is_same = false;
									break;
								}
							}
						}
						if (!is_same) {
							cmp_texture = _zt_castMem(ztCompileTexture);
							cmp_texture->command = command;
							cmp_texture->item = nullptr;
							cmp_texture->last_item = nullptr;
							cmp_texture->cnt_display_items = 0;
							cmp_texture->next = nullptr;
							cmp_item_last = nullptr;
							zt_singleLinkAddToEnd(cmp_shader->texture, cmp_texture);

							current_textures_count = command->texture_count;
							zt_fiz(current_textures_count) {
								current_textures[i] = command->texture[i];
							}
						}
					} break;

					case ztDrawCommandType_ChangeClipping: {
						cmp_clip_region = command->clip_idx < 0 ? nullptr : &clip_regions[command->clip_idx];
					} break;

					default: {
						ztCompileItem *cmp_item = _zt_castMem(ztCompileItem);
						cmp_item->command = command;
						cmp_item->clip_region = cmp_clip_region;
						if (cmp_item_last == nullptr) {
							cmp_texture->last_item = cmp_item_last = cmp_item;
							zt_singleLinkAddToEnd(cmp_texture->item, cmp_item);
						}
						else {
							cmp_item_last->next = cmp_item;
							cmp_item_last = cmp_item;
							cmp_item_last->next = nullptr;
							cmp_texture->last_item = cmp_item_last;
						}
						cmp_texture->cnt_display_items += 1;// command->type == ztDrawCommandType_ChangeColor ? 0 : 1;
					} break;
				}
			}
		}
	}

#	undef _zt_castMem

	zt_fiz(draw_lists_count) {
		ztDrawList *draw_list = draw_lists[i];
		if (!zt_bitIsSet(draw_list->flags, ztDrawListFlags_NoReset)) {
			zt_drawListReset(draw_list);
		}
	}

#	pragma pack(push, 1)
	struct ztVertex
	{
		ztVec3 pos;
		ztVec2 uv;
		ztVec3 norm;
		ztVec4 color;
	};
#	pragma pack(pop)

	struct ztBuffer
	{
		ztVertex vertices[ztRenderDrawListVertexArraySize];
		i32 vertices_count;
	};

	zt_assert(sizeof(ztVertex) == 48);
	zt_assert(sizeof(ztBuffer) == ztRenderDrawListVertexByteSize + 4);

	static ztBuffer buffer;
	buffer.vertices_count = 0;

	ztVec3 offset = ztVec3::zero;
	bool has_offset = false;

	ztCamera rt_cam;
	if (render_target_id != ztInvalidID) {
		if (camera->type == ztCameraType_Orthographic) {
			zt_cameraMakeOrtho(&rt_cam, zt_game->textures[render_target_id].width, zt_game->textures[render_target_id].height, zt_game->textures[render_target_id].width, zt_game->textures[render_target_id].height, camera->near_z, camera->far_z);
			rt_cam.zoom = camera->zoom;
			rt_cam.position = camera->position;
		}
		else {
			zt_cameraMakePersp(&rt_cam, zt_game->textures[render_target_id].width, zt_game->textures[render_target_id].height, camera->fov, camera->near_z, camera->far_z);
			rt_cam.position = camera->position;
			rt_cam.rotation = camera->rotation;
			rt_cam.direction = camera->direction;
		}

		zt_cameraRecalcMatrices(&rt_cam);
		camera = &rt_cam;
	}

#if defined(ZT_DEBUG)
	if (zt_bitIsSet(flags, ztRenderDrawListFlags_DebugDump)) {
		zt_logVerbose("DrawList debug dump for frame %d:", zt_game->game_details.current_frame);
		zt_logVerbose("  Total shaders accessed: %d", shaders_count);

		zt_fiz(shaders_count) {
			zt_logVerbose("  Shader %d.  ID: %d", i + 1, shaders[i]->shader);

			{
				int tex_count = 0;
				ztCompileTexture *cmp_tex = shaders[i]->texture;
				while (cmp_tex) {
					tex_count += 1;
					cmp_tex = cmp_tex->next;
				}
				zt_logVerbose("    Total textures for this shader: %d", tex_count);
			}
			{
				int tex_count = 0;
				ztCompileTexture *cmp_tex = shaders[i]->texture;
				while (cmp_tex) {
					zt_logVerbose("    Texture %d. Count: %d", ++tex_count, cmp_tex->command ? cmp_tex->command->texture_count : 0);
					if (cmp_tex->command) {
						zt_fjz(cmp_tex->command->texture_count) {
							zt_logVerbose("      ID: %d (%d x %d)", cmp_tex->command->texture[j], zt_game->textures[cmp_tex->command->texture[j]].width, zt_game->textures[cmp_tex->command->texture[j]].height);
						}
					}

					{
						int item_count = 0;
						ztCompileItem *item = cmp_tex->item;
						while (item) {
							item_count += 1;
							item = item->next;
						}
						zt_logVerbose("      Texture has %d items", item_count);
					}

					{
						int item_count = 0;
						int tab_count = 0;

						ztCompileItem *item = cmp_tex->item;
						while (item) {
							char info[1024];
							switch (item->command->type)
							{
								case ztDrawCommandType_Point:          zt_strPrintf(info, zt_elementsOf(info), "Point: %.2f, %.2f, %.2f", item->command->point.x, item->command->point.y, item->command->point.z); break;
								case ztDrawCommandType_Line:           zt_strPrintf(info, zt_elementsOf(info), "Line: start: %.2f, %.2f, %.2f; end: %.2f, %.2f, %.2f", item->command->line[0].x, item->command->line[0].y, item->command->line[0].z, item->command->line[1].x, item->command->line[1].y, item->command->line[1].z); break;
								case ztDrawCommandType_Triangle:       zt_strPrintf(info, zt_elementsOf(info), "Triangle: [p1] %.2f, %.2f, %.2f; [p2] %.2f, %.2f, %.2f; [p3] %.2f, %.2f, %.2f; [u1] %.2f, %.2f; [u2] %.2f, %.2f; [u3] %.2f, %.2f; [n1] %.2f, %.2f, %.2f; [n2] %.2f, %.2f, %.2f; [n3] %.2f, %.2f, %.2f; ", item->command->tri_pos[0].x, item->command->tri_pos[0].y, item->command->tri_pos[0].z, item->command->tri_pos[1].x, item->command->tri_pos[1].y, item->command->tri_pos[1].z, item->command->tri_pos[2].x, item->command->tri_pos[2].y, item->command->tri_pos[2].z, item->command->tri_uv[0].x, item->command->tri_uv[0].y, item->command->tri_uv[1].x, item->command->tri_uv[1].y, item->command->tri_uv[2].x, item->command->tri_uv[2].y, item->command->tri_norm[0].x, item->command->tri_norm[0].y, item->command->tri_norm[0].z, item->command->tri_norm[1].x, item->command->tri_norm[1].y, item->command->tri_norm[1].z, item->command->tri_norm[2].x, item->command->tri_norm[2].y, item->command->tri_norm[2].z); break;
								case ztDrawCommandType_ChangeColor:    zt_strPrintf(info, zt_elementsOf(info), "Color Change: %.2f, %.2f, %.2f, %.2f", item->command->color.r, item->command->color.g, item->command->color.b, item->command->color.a); if (item->command->color_pop) tab_count -= 1; break;
								case ztDrawCommandType_ChangeClipping: zt_strPrintf(info, zt_elementsOf(info), "Clip: center: %.2f, %.2f; size: %.2f, %.2f", item->command->clip_center.x, item->command->clip_center.y, item->command->clip_size.x, item->command->clip_size.y); break;
								case ztDrawCommandType_ChangeFlags:    zt_strPrintf(info, zt_elementsOf(info), "Flags: %d", item->command->flags); break;
								case ztDrawCommandType_ChangeOffset:   zt_strPrintf(info, zt_elementsOf(info), "Offset: %.2f, %.2f, %.2f", item->command->offset.x, item->command->offset.y, item->command->offset.z); if (item->command->offset_pop) tab_count -= 1; break;
								case ztDrawCommandType_ChangeTransform:zt_strPrintf(info, zt_elementsOf(info), "Transform: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f", item->command->transform.values[0], item->command->transform.values[1], item->command->transform.values[2], item->command->transform.values[3], item->command->transform.values[4], item->command->transform.values[5], item->command->transform.values[6], item->command->transform.values[7], item->command->transform.values[8], item->command->transform.values[9], item->command->transform.values[10], item->command->transform.values[11], item->command->transform.values[12], item->command->transform.values[13], item->command->transform.values[14], item->command->transform.values[15] ); if (item->command->transform_pop) tab_count -= 1; break;
								case ztDrawCommandType_Skybox:         zt_strPrintf(info, zt_elementsOf(info), "Skybox"); break;
								case ztDrawCommandType_Billboard:      zt_strPrintf(info, zt_elementsOf(info), "Billboard: center: %.2f, %.2f, %.2f; size: %.2f, %.2f; uv: %.2f, %.2f, %.2f, %.2f; flags: %d", item->command->billboard_center.x, item->command->billboard_center.y, item->command->billboard_center.z, item->command->billboard_size.x, item->command->billboard_size.x, item->command->billboard_uv.x, item->command->billboard_uv.y, item->command->billboard_uv.z, item->command->billboard_uv.w, item->command->billboard_flags); break;
								case ztDrawCommandType_VertexArray:    zt_strPrintf(info, zt_elementsOf(info), "Vertex Array: ID: %d; draw type: %d", item->command->vertex_array, item->command->vertex_array_draw_type); break;
							}

							char tabs[128] = { 0 };
							zt_fiz(zt_min(zt_elementsOf(tabs) - 1, tab_count)) {
								tabs[i] = '\t';
								tabs[i + 1] = 0;
							}

							switch (item->command->type)
							{
								case ztDrawCommandType_ChangeColor:    if (!item->command->color_pop) tab_count += 1; break;
								case ztDrawCommandType_ChangeOffset:   if (!item->command->offset_pop) tab_count += 1; break;
							}

							zt_logVerbose("        Item %d: %s %s", ++item_count, tabs, info);
							item = item->next;
						}
					}
					cmp_tex = cmp_tex->next;
				}
			}
		}
	}
#endif // defined(ZT_DEBUG)


	if (zt_game->win_game_settings[0].renderer == ztRenderer_OpenGL) {
#if defined(ZT_OPENGL)
		if (render_target_id != ztInvalidID) {
			zt_textureRenderTargetPrepare(render_target_id);
			zt_rendererClear(clear);
		}

		if (!zt_bitIsSet(flags, ztRenderDrawListFlags_NoDepthTest)) {
			ztgl_callAndReportOnErrorFast(glEnable(GL_DEPTH_TEST));
			ztgl_callAndReportOnErrorFast(glDepthFunc(GL_LESS));
		}
		else {
			ztgl_callAndReportOnErrorFast(glDisable(GL_DEPTH_TEST));
		}

		ztgl_callAndReportOnErrorFast(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA));

		ztMat4 mat2d;

		if (clip_regions_count > 0) {
			ztgl_callAndReportOnErrorFast(glEnable(GL_SCISSOR_TEST));
			ztgl_callAndReportOnErrorFast(glScissor(0, 0, zt_game->win_game_settings[0].screen_w, zt_game->win_game_settings[0].screen_h));
		}

		ztCompileClipRegion *curr_clip_region = nullptr;

		ztVec4 active_color = ztVec4::one;
		ztMat4 *transform = nullptr;

		zt_fiz(shaders_count) {
			ZT_PROFILE_RENDERING("zt_renderDrawLists::shader loop");

			ztShaderID shader_id = shaders[i]->shader;

			GLuint model_loc = -1;

			if (shaders[i]->shader != ztInvalidID) {
				zt_game->game_details.curr_frame.shader_switches += 1;
				zt_shaderBegin(shader_id);
				zt_shaderSetVariableMat4(shader_id, zt_strHash("model"), ztMat4::identity);
				zt_shaderSetCameraMatrices(shader_id, camera->mat_proj, camera->mat_view);
			}
			else {
				glColor4fv(ztVec4::one.values);

				mat2d = camera->mat_proj * camera->mat_view;
			}

			ztCompileTexture *cmp_tex = shaders[i]->texture;
			while (cmp_tex) {

				if (cmp_tex->cnt_display_items == 0) {
					cmp_tex = cmp_tex->next;
					continue;
				}

				if (curr_clip_region) {
					curr_clip_region = nullptr;
					//glDisable(GL_SCISSOR_TEST);
					ztgl_callAndReportOnErrorFast(glScissor(0, 0, zt_game->win_game_settings[0].screen_w, zt_game->win_game_settings[0].screen_h));
				}

				if (cmp_tex->command && shader_id != ztInvalidID) {
					ZT_PROFILE_RENDERING("zt_renderDrawLists::texture binding");

					ztgl_textureBindReset(zt_game->shaders[shader_id].gl_shader);
					zt_game->game_details.curr_frame.texture_switches += 1;
					zt_fiz(cmp_tex->command->texture_count) {
						ztgl_shaderVariableTex(zt_game->shaders[shader_id].gl_shader, zt_strHash("tex_diffuse"), zt_game->textures[cmp_tex->command->texture[i]].gl_texture);
					}
				}

				if (shader_id == ztInvalidID || zt_bitIsSet(flags, ztRenderDrawListFlags_NoDepthTest)) {
					glColor4fv(active_color.values);
				}

				if (curr_clip_region) {
					curr_clip_region = nullptr;
					//glDisable(GL_SCISSOR_TEST);
					ztgl_callAndReportOnErrorFast(glScissor(0, 0, zt_game->win_game_settings[0].screen_w, zt_game->win_game_settings[0].screen_h));
				}

				ztCompileItem *cmp_item = cmp_tex->item;

				ztDrawCommandType_Enum last_command = ztDrawCommandType_Invalid;

				struct OpenGL
				{
					static void processLastCommand(ztCamera *cam, ztMat4 *mat, ztVec4& active_color, ztDrawCommandType_Enum this_command, ztDrawCommandType_Enum last_command, ztBuffer *buffer)
					{
						ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand");
						switch (last_command)
						{
							case ztDrawCommandType_Billboard:
							case ztDrawCommandType_Triangle: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::v");
								ztVertexEntryGL entries[] = {
									{ GL_FLOAT, 3 * sizeof(GLfloat) },
									{ GL_FLOAT, 2 * sizeof(GLfloat) },
									{ GL_FLOAT, 3 * sizeof(GLfloat) },
									{ GL_FLOAT, 4 * sizeof(GLfloat) },
								};

								ztgl_drawVertices(GL_TRIANGLES, entries, zt_elementsOf(entries), buffer->vertices, buffer->vertices_count);
								zt_game->game_details.curr_frame.draw_calls += 1;

							} break;

							case ztDrawCommandType_Line:
							case ztDrawCommandType_Point: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::l/p");
								zt_game->game_details.curr_frame.draw_calls += 1;
								glEnd();
								ztgl_callAndReportOnErrorFast(glPopMatrix());
							} break;
						}

						switch (this_command)
						{
							case ztDrawCommandType_Billboard:
							case ztDrawCommandType_Triangle: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::t");
								buffer->vertices_count = 0;
							} break;

							case ztDrawCommandType_Line: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::l");
								if (cam->type == ztCameraType_Perspective) {
									ztgl_callAndReportOnErrorFast(glMatrixMode(GL_PROJECTION));
									ztgl_callAndReportOnErrorFast(glPushMatrix());
									glLoadMatrixf(mat->values);
								}
								else {
									ztgl_callAndReportOnErrorFast(glMatrixMode(GL_MODELVIEW));
									ztgl_callAndReportOnErrorFast(glPushMatrix());
									ztgl_callAndReportOnErrorFast(glLoadIdentity());
								}
								ztgl_callAndReportOnErrorFast(glLineWidth(1));
								glColor4fv(active_color.values);
								glBegin(GL_LINES);
							} break;

							case ztDrawCommandType_Point: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::p");
								if (cam->type == ztCameraType_Perspective) {
									ztgl_callAndReportOnErrorFast(glMatrixMode(GL_PROJECTION));
									ztgl_callAndReportOnErrorFast(glPushMatrix());
									glLoadMatrixf(mat->values);
								}
								else {
									ztgl_callAndReportOnErrorFast(glMatrixMode(GL_MODELVIEW));
									ztgl_callAndReportOnErrorFast(glPushMatrix());
									ztgl_callAndReportOnErrorFast(glLoadIdentity());
								}
								glColor4fv(active_color.values);
								glBegin(GL_POINTS);
							} break;
						}
					}
				};

				while (cmp_item) {

					if (cmp_item->clip_region != curr_clip_region && camera->type == ztCameraType_Orthographic) {
						ZT_PROFILE_RENDERING("zt_renderDrawLists::clip regions");
						OpenGL::processLastCommand(nullptr, nullptr, active_color, ztDrawCommandType_Invalid, last_command, &buffer);
						last_command = ztDrawCommandType_Invalid;

						curr_clip_region = cmp_item->clip_region;

						if (curr_clip_region) {
							r32 ppu = zt_pixelsPerUnit();
							ztPoint2 pos = zt_cameraOrthoWorldToScreen(camera, curr_clip_region->command->clip_center - curr_clip_region->command->clip_size * ztVec2(.5f, .5f));
							int w = zt_convertToi32Ceil(curr_clip_region->command->clip_size.x * ppu);
							int h = zt_convertToi32Ceil(curr_clip_region->command->clip_size.y * ppu);

							ztgl_callAndReportOnErrorFast(glScissor(pos.x, pos.y, w, h));
						}
						else {
							ztgl_callAndReportOnErrorFast(glScissor(0, 0, zt_game->win_game_settings[0].screen_w, zt_game->win_game_settings[0].screen_h));
							//ztgl_callAndReportOnErrorFast(glDisable(GL_SCISSOR_TEST));
						}
					}

					if (cmp_item->command->type != last_command) {
						bool skipProcess = false;
						switch (cmp_item->command->type)
						{
							case ztDrawCommandType_ChangeColor:
							case ztDrawCommandType_ChangeOffset:
							case ztDrawCommandType_ChangeTransform:
								skipProcess = true;
								break;
						}

						if (!skipProcess) {
							OpenGL::processLastCommand(camera, &mat2d, active_color, cmp_item->command->type, last_command, &buffer);
							last_command = cmp_item->command->type;
						}
					}

					switch (cmp_item->command->type)
					{
						case ztDrawCommandType_Triangle: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::triangle");
							++zt_game->game_details.curr_frame.triangles_drawn;

							zt_fkz(3) {
								int idx = buffer.vertices_count++;
								if(has_offset) {
									buffer.vertices[idx].pos = cmp_item->command->tri_pos[k] + offset;
								}
								else {
									buffer.vertices[idx].pos = cmp_item->command->tri_pos[k];
								}
								buffer.vertices[idx].uv = cmp_item->command->tri_uv[k];
								buffer.vertices[idx].norm = cmp_item->command->tri_norm[k];
								buffer.vertices[idx].color = active_color;
								buffer.vertices[idx].uv.y = 1 - buffer.vertices[idx].uv.y;


								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}
							}

						} break;

						case ztDrawCommandType_Billboard: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::billboard");
							zt_game->game_details.curr_frame.triangles_drawn += 2;

							ztVec3 p[4] = {
								ztVec3(-cmp_item->command->billboard_size.x / 2.f + offset.x, +cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
								ztVec3(-cmp_item->command->billboard_size.x / 2.f + offset.x, -cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
								ztVec3(+cmp_item->command->billboard_size.x / 2.f + offset.x, -cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
								ztVec3(+cmp_item->command->billboard_size.x / 2.f + offset.x, +cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
							};

							ztVec2 uv[4] = {
								ztVec2(cmp_item->command->billboard_uv.x, 1 - cmp_item->command->billboard_uv.y),
								ztVec2(cmp_item->command->billboard_uv.x, 1 - cmp_item->command->billboard_uv.w),
								ztVec2(cmp_item->command->billboard_uv.z, 1 - cmp_item->command->billboard_uv.w),
								ztVec2(cmp_item->command->billboard_uv.z, 1 - cmp_item->command->billboard_uv.y),
							};

							ztVec3 pos_lookat = camera->position;

							if (!zt_bitIsSet(cmp_item->command->billboard_flags, ztDrawCommandBillboardFlags_AxisX)) pos_lookat.x = cmp_item->command->billboard_center.x;
							if (!zt_bitIsSet(cmp_item->command->billboard_flags, ztDrawCommandBillboardFlags_AxisY)) pos_lookat.y = cmp_item->command->billboard_center.y;
							if (!zt_bitIsSet(cmp_item->command->billboard_flags, ztDrawCommandBillboardFlags_AxisZ)) pos_lookat.z = cmp_item->command->billboard_center.z;

							ztMat4 mat = ztMat4::identity.getLookAt(pos_lookat, cmp_item->command->billboard_center).getInverse();
							mat.values[ztMat4_Col3Row0] = mat.values[ztMat4_Col3Row1] = mat.values[ztMat4_Col3Row2] = 0; // remove translation

							zt_fiz(4) {
								p[i] = cmp_item->command->billboard_center + (mat * p[i]);
							}

							zt_fiz(2) {
								int idx = buffer.vertices_count++;
								buffer.vertices[idx].pos = p[0];
								buffer.vertices[idx].uv = uv[0];
								buffer.vertices[idx].norm = ztVec3::zero;
								buffer.vertices[idx].color = active_color;
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}

								idx = buffer.vertices_count++;
								buffer.vertices[idx].pos = p[1 + i];
								buffer.vertices[idx].uv = uv[1 + i];
								buffer.vertices[idx].norm = ztVec3::zero;
								buffer.vertices[idx].color = active_color;
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}

								idx = buffer.vertices_count++;
								buffer.vertices[idx].pos = p[2 + i];
								buffer.vertices[idx].uv = uv[2 + i];
								buffer.vertices[idx].norm = ztVec3::zero;
								buffer.vertices[idx].color = active_color;
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}
							}
						} break;

						case ztDrawCommandType_Line: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::line");
							if(transform) {
								ztVec3 line0 = (*transform) * cmp_item->command->line[0];
								ztVec3 line1 = (*transform) * cmp_item->command->line[1];
								glVertex3f(line0.x + offset.x, line0.y + offset.y, line0.z + offset.z);
								glVertex3f(line1.x + offset.x, line1.y + offset.y, line1.z + offset.z);
							}
							else {
								glVertex3f(cmp_item->command->line[0].x + offset.x, cmp_item->command->line[0].y + offset.y, cmp_item->command->line[0].z + offset.z);
								glVertex3f(cmp_item->command->line[1].x + offset.x, cmp_item->command->line[1].y + offset.y, cmp_item->command->line[1].z + offset.z);
							}
						} break;

						case ztDrawCommandType_Point: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::point");
							if(transform) {
								ztVec3 p = (*transform) * cmp_item->command->point;
								glVertex3f(cmp_item->command->point.x+ offset.x, p.y + offset.y, p.z + offset.z);
							}
							else {
								glVertex3f(cmp_item->command->point.x+ offset.x, cmp_item->command->point.y + offset.y, cmp_item->command->point.z + offset.z);
							}
						} break;

						case ztDrawCommandType_ChangeColor: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::change color");
							active_color = cmp_item->command->color;

							if (shader_id == ztInvalidID || zt_bitIsSet(flags, ztRenderDrawListFlags_NoDepthTest)) {
								glColor4fv(active_color.values);
							}
						} break;

						case ztDrawCommandType_ChangeOffset: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::change offset");
							offset = cmp_item->command->offset;
							has_offset = offset == ztVec3::zero;
						} break;

						case ztDrawCommandType_ChangeTransform: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::change transform");
							if(cmp_item->command->transform == ztMat4::identity) {
								transform = nullptr;
							}
							else {
								transform = &cmp_item->command->transform;
							}
						} break;

						case ztDrawCommandType_VertexArray: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::vertex array");
							zt_vertexArrayDraw(cmp_item->command->vertex_array, cmp_item->command->vertex_array_draw_type);
						} break;
					};

					cmp_item = cmp_item->next;
				}
				OpenGL::processLastCommand(nullptr, nullptr, active_color, ztDrawCommandType_Invalid, last_command, &buffer);

				if (curr_clip_region) {
					curr_clip_region = nullptr;
					//glDisable(GL_SCISSOR_TEST);
					ztgl_callAndReportOnErrorFast(glScissor(0, 0, zt_game->win_game_settings[0].screen_w, zt_game->win_game_settings[0].screen_h));
				}

				if (cmp_tex->command && shader_id != ztInvalidID) {
					ZT_PROFILE_RENDERING("zt_renderDrawLists::resetting texture");
					ztgl_textureBindReset(zt_game->shaders[shader_id].gl_shader);
				}

				cmp_tex = cmp_tex->next;
			}

			if (curr_clip_region) {
				curr_clip_region = nullptr;
				//glDisable(GL_SCISSOR_TEST);
				ztgl_callAndReportOnErrorFast(glScissor(0, 0, zt_game->win_game_settings[0].screen_w, zt_game->win_game_settings[0].screen_h));
			}

			glUseProgram(0);
		}

		if (clip_regions_count > 0) {
			glDisable(GL_SCISSOR_TEST);
		}

		if (render_target_id != ztInvalidID) {
			zt_textureRenderTargetCommit(render_target_id);
		}

#endif // ZT_OPENGL
	}
	else if (zt_game->win_game_settings[0].renderer == ztRenderer_DirectX) {
#if defined(ZT_DIRECTX)

		if (render_target_id != ztInvalidID) {
			zt_textureRenderTargetPrepare(render_target_id);
		}

		if (!zt_bitIsSet(flags, ztRenderDrawListFlags_NoDepthTest)) {
			ztdx_depthTestLess(zt_game->win_details[0].dx_context);
		}
		else {
			ztdx_depthTestOff(zt_game->win_details[0].dx_context);
		}

		ztCompileClipRegion *curr_clip_region = nullptr;

		static u32 model_hash = zt_strHash("model");
		static u32 view_hash = zt_strHash("view");
		static u32 projection_hash = zt_strHash("projection");

		zt_fiz(shaders_count) {
			ZT_PROFILE_RENDERING("zt_renderDrawLists::shader loop");

			ztShaderID shader_id = shaders[i]->shader;
			if (shaders[i]->shader != ztInvalidID) {
				zt_game->game_details.curr_frame.shader_switches += 1;
				ztdx_shaderBegin(zt_game->win_details[0].dx_context, zt_game->shaders[shader_id].dx_shader);

				ztMat4 dxMod = ztMat4::identity;
				ztMat4 dxView = camera->mat_view;
				ztMat4 dxProj = camera->mat_proj;

				zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, model_hash, dxMod);
				zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, view_hash, dxView);
				zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, projection_hash, dxProj);
				zt_shaderApplyVariables(shader_id);
			}
			else {
				shader_id = zt_shaderGetDefault(ztShaderDefault_Solid);

				zt_game->game_details.curr_frame.shader_switches += 1;
				ztdx_shaderBegin(zt_game->win_details[0].dx_context, zt_game->shaders[shader_id].dx_shader);

				ztMat4 dxMod = ztMat4::identity;
				ztMat4 dxView = camera->mat_view;
				ztMat4 dxProj = camera->mat_proj;

				zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, model_hash, dxMod);
				zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, view_hash, dxView);
				zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, projection_hash, dxProj);
				zt_shaderApplyVariables(shader_id);
				// set color
			}

			ztVec4 active_color = ztVec4::one;
			ztMat4 *transform = nullptr;

			ztCompileTexture *cmp_tex = shaders[i]->texture;
			while (cmp_tex) {
				if (cmp_tex->cnt_display_items == 0) {
					cmp_tex = cmp_tex->next;
					continue;
				}

				if (cmp_tex->command && shader_id != ztInvalidID) {
					ZT_PROFILE_RENDERING("zt_renderDrawLists::texture binding");
					zt_game->game_details.curr_frame.texture_switches += 1;
					static u32 tex_diffuse_hash = zt_strHash("tex_diffuse");
					zt_shaderSetVariableTex(shader_id, tex_diffuse_hash, cmp_tex->command->texture[0]);
					zt_shaderApplyVariables(shader_id);
				}

				ztCompileItem *cmp_item = cmp_tex->item;

				ztDrawCommandType_Enum last_command = ztDrawCommandType_Invalid;

				struct DirectX
				{
					static void processLastCommand(ztShaderID active_shader, ztDrawCommandType_Enum this_command, ztDrawCommandType_Enum last_command, ztBuffer *buffer)
					{
						ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand");
						switch (last_command)
						{
							case ztDrawCommandType_Billboard:
							case ztDrawCommandType_Triangle: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::v");
								//zt_shaderApplyVariables(active_shader);

								ztdx_vertexArrayUpdate(zt_game->win_details[0].dx_context, zt_game->win_details[0].dx_tri_verts_array, buffer->vertices, buffer->vertices_count);
								ztdx_vertexArrayDraw(zt_game->win_details[0].dx_context, zt_game->win_details[0].dx_tri_verts_array);
								buffer->vertices_count = 0;

								zt_game->game_details.curr_frame.draw_calls += 1;
							} break;

							case ztDrawCommandType_Line:
							case ztDrawCommandType_Point: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::l/p");
								//zt_shaderApplyVariables(active_shader);

								ztdx_vertexArrayUpdate(zt_game->win_details[0].dx_context, zt_game->win_details[0].dx_tri_verts_array, buffer->vertices, buffer->vertices_count);
								ztdx_vertexArrayDraw(zt_game->win_details[0].dx_context, zt_game->win_details[0].dx_tri_verts_array, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
								buffer->vertices_count = 0;

								zt_game->game_details.curr_frame.draw_calls += 1;
							} break;
						}

						switch (this_command)
						{
							case ztDrawCommandType_Billboard:
							case ztDrawCommandType_Triangle: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::t");
								buffer->vertices_count = 0;
								ztdx_cullBack(zt_game->win_details[0].dx_context);
							} break;

							case ztDrawCommandType_Line:
							case ztDrawCommandType_Point: {
								ZT_PROFILE_RENDERING("zt_renderDrawLists::lastCommand::lp");
								buffer->vertices_count = 0;
								ztdx_cullNone(zt_game->win_details[0].dx_context);
							} break;
						}
					}
				};

				while (cmp_item) {

					if (cmp_item->clip_region != curr_clip_region && camera->type == ztCameraType_Orthographic) {
						ZT_PROFILE_RENDERING("zt_renderDrawLists::clip regions");
						DirectX::processLastCommand(shader_id, ztDrawCommandType_Invalid, last_command, &buffer);
						last_command = ztDrawCommandType_Invalid;

						curr_clip_region = cmp_item->clip_region;

						if (curr_clip_region) {
							r32 ppu = zt_pixelsPerUnit();
							ztPoint2 pos = zt_cameraOrthoWorldToScreen(camera, (curr_clip_region->command->clip_center * ztVec2(1, -1)) - curr_clip_region->command->clip_size * ztVec2(.5f, .5f));

							int w = zt_convertToi32Floor(curr_clip_region->command->clip_size.x * ppu);
							int h = zt_convertToi32Floor(curr_clip_region->command->clip_size.y * ppu);

							ztdx_clipRegionSet(zt_game->win_details[0].dx_context, pos.x, pos.y, pos.x + w, pos.y + h);
						}
						else {
							ztdx_clipRegionRemove(zt_game->win_details[0].dx_context);
						}
					}

					if (cmp_item->command->type != last_command) {
						bool skipProcess = false;
						switch (cmp_item->command->type)
						{
							case ztDrawCommandType_ChangeColor:
							case ztDrawCommandType_ChangeOffset:
								skipProcess = true;
								break;
						}

						if (!skipProcess) {
							DirectX::processLastCommand(shader_id, cmp_item->command->type, last_command, &buffer);
							last_command = cmp_item->command->type;
						}
					}

					switch (cmp_item->command->type)
					{
						case ztDrawCommandType_Triangle: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::triangle");
							++zt_game->game_details.curr_frame.triangles_drawn;

							if (buffer.vertices_count >= zt_elementsOf(buffer.vertices)) {
								DirectX::processLastCommand(shader_id, ztDrawCommandType_Invalid, ztDrawCommandType_Triangle, &buffer);
							}

							zt_fkz(3) {
								int idx = buffer.vertices_count++;
								zt_fjz(3) buffer.vertices[idx].pos.values[j] = cmp_item->command->tri_pos[k].values[j] + offset.values[j];
								zt_fjz(2) buffer.vertices[idx].uv.values[j] = cmp_item->command->tri_uv[k].values[j];
								zt_fjz(3) buffer.vertices[idx].norm.values[j] = cmp_item->command->tri_norm[k].values[j];
								zt_fjz(4) buffer.vertices[idx].color.values[j] = active_color.values[j];
								buffer.vertices[idx].uv.y = 1 - buffer.vertices[idx].uv.y;

								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}
							}

						} break;

						case ztDrawCommandType_Billboard: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::billboard");
							zt_game->game_details.curr_frame.triangles_drawn += 2;

							ztVec3 p[4] = {
								ztVec3(-cmp_item->command->billboard_size.x / 2.f + offset.x, +cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
								ztVec3(-cmp_item->command->billboard_size.x / 2.f + offset.x, -cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
								ztVec3(+cmp_item->command->billboard_size.x / 2.f + offset.x, -cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
								ztVec3(+cmp_item->command->billboard_size.x / 2.f + offset.x, +cmp_item->command->billboard_size.y / 2.f + offset.y, offset.z),
							};

							ztVec2 uv[4] = {
								ztVec2(cmp_item->command->billboard_uv.x, cmp_item->command->billboard_uv.y),
								ztVec2(cmp_item->command->billboard_uv.x, cmp_item->command->billboard_uv.w),
								ztVec2(cmp_item->command->billboard_uv.z, cmp_item->command->billboard_uv.w),
								ztVec2(cmp_item->command->billboard_uv.z, cmp_item->command->billboard_uv.y),
							};

							ztVec3 pos_lookat = camera->position;

							if (!zt_bitIsSet(cmp_item->command->billboard_flags, ztDrawCommandBillboardFlags_AxisX)) pos_lookat.x = cmp_item->command->billboard_center.x;
							if (!zt_bitIsSet(cmp_item->command->billboard_flags, ztDrawCommandBillboardFlags_AxisY)) pos_lookat.y = cmp_item->command->billboard_center.y;
							if (!zt_bitIsSet(cmp_item->command->billboard_flags, ztDrawCommandBillboardFlags_AxisZ)) pos_lookat.z = cmp_item->command->billboard_center.z;

							ztMat4 mat = ztMat4::identity.getLookAt(pos_lookat, cmp_item->command->billboard_center).getInverse();
							mat.values[ztMat4_Col3Row0] = mat.values[ztMat4_Col3Row1] = mat.values[ztMat4_Col3Row2] = 0; // remove translation

							zt_fiz(4) {
								p[i] = cmp_item->command->billboard_center + (mat * p[i]);
							}

							zt_fiz(2) {
								int idx = buffer.vertices_count++;
								buffer.vertices[idx].pos = p[0];
								buffer.vertices[idx].uv = uv[0];
								buffer.vertices[idx].norm = ztVec3::zero;
								buffer.vertices[idx].color = active_color;
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}

								idx = buffer.vertices_count++;
								buffer.vertices[idx].pos = p[1 + i];
								buffer.vertices[idx].uv = uv[1 + i];
								buffer.vertices[idx].norm = ztVec3::zero;
								buffer.vertices[idx].color = active_color;
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}

								idx = buffer.vertices_count++;
								buffer.vertices[idx].pos = p[2 + i];
								buffer.vertices[idx].uv = uv[2 + i];
								buffer.vertices[idx].norm = ztVec3::zero;
								buffer.vertices[idx].color = active_color;
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}
							}
						} break;

						case ztDrawCommandType_Line: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::line");
							if (buffer.vertices_count >= zt_elementsOf(buffer.vertices)) {
								DirectX::processLastCommand(shader_id, ztDrawCommandType_Invalid, ztDrawCommandType_Line, &buffer);
							}

							zt_fkz(2) {
								int idx = buffer.vertices_count++;
								zt_fjz(3) buffer.vertices[idx].pos.values[j] = cmp_item->command->line[k].values[j] + offset.values[j];
								zt_fjz(2) buffer.vertices[idx].uv.values[j] = (r32)k;
								zt_fjz(3) buffer.vertices[idx].norm.values[j] = 1.f;
								zt_fjz(4) buffer.vertices[idx].color.values[j] = active_color.values[j];
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}
							}
						} break;

						case ztDrawCommandType_Point: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::point");
							zt_fkz(2) {
								int idx = buffer.vertices_count++;
								zt_fjz(3) buffer.vertices[idx].pos.values[j] = cmp_item->command->line[k].values[j] + (k * 0.001f) + offset.values[j];
								zt_fjz(2) buffer.vertices[idx].uv.values[j] = (r32)k;
								zt_fjz(3) buffer.vertices[idx].norm.values[j] = 1.f;
								zt_fjz(4) buffer.vertices[idx].color.values[j] = active_color.values[j];
								if(transform) {
									buffer.vertices[idx].pos = (*transform) * buffer.vertices[idx].pos;
								}
							}
						} break;

						case ztDrawCommandType_ChangeColor: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::change color");
							active_color = cmp_item->command->color;
						} break;

						case ztDrawCommandType_ChangeOffset: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::change offset");
							offset = cmp_item->command->offset;
						} break;

						case ztDrawCommandType_ChangeTransform: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::change transform");
							if(cmp_item->command->transform == ztMat4::identity) {
								transform = nullptr;
							}
							else {
								transform = &cmp_item->command->transform;
							}
						} break;

						case ztDrawCommandType_VertexArray: {
							ZT_PROFILE_RENDERING("zt_renderDrawLists::vertex array");
							zt_vertexArrayDraw(cmp_item->command->vertex_array, cmp_item->command->vertex_array_draw_type);
						} break;
					};

					cmp_item = cmp_item->next;
				}
				DirectX::processLastCommand(shader_id, ztDrawCommandType_Invalid, last_command, &buffer);

				if (curr_clip_region) {
					curr_clip_region = nullptr;
					ztdx_clipRegionRemove(zt_game->win_details[0].dx_context);
				}

				cmp_tex = cmp_tex->next;
			}

			if (curr_clip_region) {
				curr_clip_region = nullptr;
				ztdx_clipRegionRemove(zt_game->win_details[0].dx_context);
			}
			// unbind shader?
		}

		if (render_target_id != ztInvalidID) {
			zt_textureRenderTargetCommit(render_target_id);
		}
#endif // ZT_DIRECTX
	}
#endif
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztVertexArrayID zt_vertexArrayMake(ztVertexArrayEntry *entries, int entries_count, void *vert_data, int vert_count)
{
	ZT_PROFILE_RENDERING("zt_vertexArrayMake");
	zt_returnValOnNull(entries, ztInvalidID);
	zt_assertReturnValOnFail(zt_game->vertex_arrays_count < zt_elementsOf(zt_game->vertex_arrays), ztInvalidID);

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			ztVertexEntryGL *gl_entries = zt_mallocStructArray(ztVertexEntryGL, entries_count);
			zt_fiz(entries_count) {
				gl_entries[i].size = entries[i].size;

				switch (entries[i].type)
				{
					case ztVertexArrayDataType_Float: {
						gl_entries[i].type = GL_FLOAT;
					} break;

					default: zt_assert(false);
				}
			}
			ztVertexArrayGL *gl_va = ztgl_vertexArrayMake(gl_entries, entries_count, vert_data, vert_count);
			zt_free(gl_entries);

			if (gl_va == nullptr) {
				return ztInvalidID;
			}

			ztVertexArrayID va_id = zt_game->vertex_arrays_count++;
			zt_game->vertex_arrays[va_id].gl_va = gl_va;

			return va_id;
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			ztVertexEntryDX *dx_entries = zt_mallocStructArray(ztVertexEntryDX, entries_count);
			zt_fiz(entries_count) {
				dx_entries[i].size = entries[i].size;
				// DirectX doesn't care about data types here
			}
			ztVertexArrayDX *dx_va = ztdx_vertexArrayMake(zt_game->win_details[0].dx_context, dx_entries, entries_count, vert_data, vert_count);
			zt_free(dx_entries);

			if (dx_va == nullptr) {
				return ztInvalidID;
			}

			ztVertexArrayID va_id = zt_game->vertex_arrays_count++;
			zt_game->vertex_arrays[va_id].dx_va = dx_va;

			return va_id;
#			endif
		} break;
	}

	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

void zt_vertexArrayFree(ztVertexArrayID vertex_array_id)
{
	ZT_PROFILE_RENDERING("zt_vertexArrayFree");
	zt_assertReturnOnFail(vertex_array_id >= 0 && vertex_array_id < zt_game->vertex_arrays_count);

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			ztgl_vertexArrayFree(zt_game->vertex_arrays[vertex_array_id].gl_va);
			zt_game->vertex_arrays[vertex_array_id].gl_va = nullptr;
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			ztdx_vertexArrayFree(zt_game->vertex_arrays[vertex_array_id].dx_va);
			zt_game->vertex_arrays[vertex_array_id].dx_va = nullptr;
#			endif
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_vertexArrayUpdate(ztVertexArrayID vertex_array_id, void *vert_data, int vert_count)
{
	ZT_PROFILE_RENDERING("zt_vertexArrayUpdate");
	zt_assertReturnValOnFail(vertex_array_id >= 0 && vertex_array_id < zt_game->vertex_arrays_count, false);

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			return ztgl_vertexArrayUpdate(zt_game->vertex_arrays[vertex_array_id].gl_va, vert_data, vert_count);
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			return ztdx_vertexArrayUpdate(zt_game->win_details[0].dx_context, zt_game->vertex_arrays[vertex_array_id].dx_va, vert_data, vert_count);
#			endif
		} break;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_vertexArrayDraw(ztVertexArrayID vertex_array_id, ztVertexArrayDrawType_Enum draw_type)
{
	ZT_PROFILE_RENDERING("zt_vertexArrayDraw");
	zt_assertReturnOnFail(vertex_array_id >= 0 && vertex_array_id < zt_game->vertex_arrays_count);

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			GLenum gl_draw_type = GL_TRIANGLES;
			switch (draw_type)
			{
				case ztVertexArrayDrawType_Triangles: {
					gl_draw_type = GL_TRIANGLES;
				} break;

				case ztVertexArrayDrawType_Lines: {
					gl_draw_type = GL_LINES;
				} break;

				case ztVertexArrayDrawType_Points: {
					gl_draw_type = GL_POINTS;
				} break;
			}
			return ztgl_vertexArrayDraw(zt_game->vertex_arrays[vertex_array_id].gl_va, gl_draw_type);
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			D3D11_PRIMITIVE_TOPOLOGY dx_draw_type = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			switch (draw_type)
			{
				case ztVertexArrayDrawType_Triangles: {
					dx_draw_type = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
				} break;

				case ztVertexArrayDrawType_Lines: {
					dx_draw_type = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
				} break;

				case ztVertexArrayDrawType_Points: {
					dx_draw_type = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
				} break;
			}
			return ztdx_vertexArrayDraw(zt_game->win_details[0].dx_context, zt_game->vertex_arrays[vertex_array_id].dx_va, dx_draw_type);
#			endif
		} break;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztLight zt_lightMakeDirectional(const ztVec3& pos, const ztVec3& dir, r32 intensity, r32 ambient, bool casts_shadows, const ztColor& color)
{
	ZT_PROFILE_RENDERING("zt_lightMakeDirectional");
	ztLight result;
	result.type = ztLightType_Directional;
	result.position = pos;
	result.direction = dir;
	result.intensity = intensity;
	result.ambient = ambient;
	result.casts_shadows = casts_shadows;
	result.color = color;
	return result;
}

// ------------------------------------------------------------------------------------------------

ztLight zt_lightMakeSpot(const ztVec3& pos, const ztVec3& dir, r32 intensity, bool casts_shadows, const ztColor& color)
{
	ZT_PROFILE_RENDERING("zt_lightMakeSpot");
	ztLight result;
	result.type = ztLightType_Spot;
	result.position = pos;
	result.direction = dir;
	result.intensity = intensity;
	result.ambient = 0;
	result.casts_shadows = casts_shadows;
	result.color = color;
	return result;
}

// ------------------------------------------------------------------------------------------------

ztLight zt_lightMakeArea(const ztVec3& pos, r32 intensity, bool casts_shadows, const ztColor& color)
{
	ZT_PROFILE_RENDERING("zt_lightMakeArea");
	ztLight result;
	result.type = ztLightType_Area;
	result.position = pos;
	result.direction = ztVec3::zero;
	result.intensity = intensity;
	result.ambient = 0;
	result.casts_shadows = casts_shadows;
	result.color = color;
	return result;
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztModel *zt_modelMake(ztMemoryArena *arena, ztMeshID mesh_id, ztMaterial *material, ztShaderID shader, ztShaderVariableValues *shader_vars, i32 flags, ztModel *parent)
{
	ZT_PROFILE_RENDERING("zt_modelMake");
	zt_assertReturnValOnFail(shader >= 0 && shader < zt_game->shaders_count, nullptr);

	static u32 diffuse_tex_hash  = zt_strHash("diffuse_tex");
	static u32 specular_tex_hash = zt_strHash("specular_tex");
	static u32 normal_tex_hash   = zt_strHash("normal_tex");

	if (material && !zt_bitIsSet(flags, ztModelFlags_ShaderSupportsDiffuse ) && zt_shaderHasVariable(shader, material->diffuse_tex_override  ? material->diffuse_tex_override  : diffuse_tex_hash , nullptr)) flags |= ztModelFlags_ShaderSupportsDiffuse;
	if (material && !zt_bitIsSet(flags, ztModelFlags_ShaderSupportsSpecular) && zt_shaderHasVariable(shader, material->specular_tex_override ? material->specular_tex_override : specular_tex_hash, nullptr)) flags |= ztModelFlags_ShaderSupportsSpecular;
	if (material && !zt_bitIsSet(flags, ztModelFlags_ShaderSupportsNormal  ) && zt_shaderHasVariable(shader, material->normal_tex_override   ? material->normal_tex_override   : normal_tex_hash  , nullptr)) flags |= ztModelFlags_ShaderSupportsNormal;

	if (!zt_bitIsSet(flags, ztModelFlags_ShaderSupportsDirectionalLight) && shader < ztShaderDefault_MAX && zt_shaderHasVariable(shader, "light_pos", nullptr)) flags |= ztModelFlags_ShaderSupportsDirectionalLight;

	ztModel *model = zt_mallocStructArena(ztModel, arena);
	model->arena = arena;
	model->mesh_id = mesh_id;
	model->flags = flags;
	model->shader = shader;
	model->shader_vars = shader_vars;
	model->material = material ? *material : zt_materialMake();
	model->transform.position = ztVec3::zero;
	model->transform.rotation = ztQuat::identity;
	model->transform.scale = ztVec3::one;
	model->next = nullptr;
	model->first_child = nullptr;
	model->parent = parent;
	model->calculated_mat = ztMat4::identity;

	if (parent != nullptr) {
		zt_singleLinkAddToEnd(parent->first_child, model);
	}

	return model;
}

// ------------------------------------------------------------------------------------------------

void zt_modelFree(ztModel *model)
{
	ZT_PROFILE_RENDERING("zt_modelFree");
	if (model == nullptr) {
		return;
	}

	ztModel *child = model->first_child;
	while (child) {
		zt_modelFree(child);
		child = child->next;
	}

	if (zt_bitIsSet(model->flags, ztModelFlags_OwnsMaterials)) {
		zt_materialFree(&model->material);
	}
	if (zt_bitIsSet(model->flags, ztModelFlags_OwnsMesh)) {
		zt_meshFree(model->mesh_id);
	}

	zt_freeArena(model, model->arena);
}

// ------------------------------------------------------------------------------------------------

ztModel *zt_modelMakeSkybox(ztMemoryArena *arena, ztTextureID texture_id)
{
	ZT_PROFILE_RENDERING("zt_modelMakeSkybox");
	ztVec3 skybox_verts[] = {
		ztVec3(-1.0f,  1.0f, -1.0f), ztVec3(-1.0f, -1.0f, -1.0f), ztVec3( 1.0f, -1.0f, -1.0f), ztVec3( 1.0f, -1.0f, -1.0f), ztVec3( 1.0f,  1.0f, -1.0f), ztVec3(-1.0f,  1.0f, -1.0f),
		ztVec3(-1.0f, -1.0f,  1.0f), ztVec3(-1.0f, -1.0f, -1.0f), ztVec3(-1.0f,  1.0f, -1.0f), ztVec3(-1.0f,  1.0f, -1.0f), ztVec3(-1.0f,  1.0f,  1.0f), ztVec3(-1.0f, -1.0f,  1.0f),
		ztVec3( 1.0f, -1.0f, -1.0f), ztVec3( 1.0f, -1.0f,  1.0f), ztVec3( 1.0f,  1.0f,  1.0f), ztVec3( 1.0f,  1.0f,  1.0f), ztVec3( 1.0f,  1.0f, -1.0f), ztVec3( 1.0f, -1.0f, -1.0f),
		ztVec3(-1.0f, -1.0f,  1.0f), ztVec3(-1.0f,  1.0f,  1.0f), ztVec3( 1.0f,  1.0f,  1.0f), ztVec3( 1.0f,  1.0f,  1.0f), ztVec3( 1.0f, -1.0f,  1.0f), ztVec3(-1.0f, -1.0f,  1.0f),
		ztVec3(-1.0f,  1.0f, -1.0f), ztVec3( 1.0f,  1.0f, -1.0f), ztVec3( 1.0f,  1.0f,  1.0f), ztVec3( 1.0f,  1.0f,  1.0f), ztVec3(-1.0f,  1.0f,  1.0f), ztVec3(-1.0f,  1.0f, -1.0f),
		ztVec3(-1.0f, -1.0f, -1.0f), ztVec3(-1.0f, -1.0f,  1.0f), ztVec3( 1.0f, -1.0f, -1.0f), ztVec3( 1.0f, -1.0f, -1.0f), ztVec3(-1.0f, -1.0f,  1.0f), ztVec3( 1.0f, -1.0f,  1.0f)
	};

	ztMeshID mesh = zt_meshMake(skybox_verts, nullptr, nullptr, zt_elementsOf(skybox_verts), nullptr, 0);
	if (mesh == ztInvalidID) {
		return nullptr;
	}

	ztMaterial material = zt_materialMake(texture_id);

	return zt_modelMake(zt_memGetGlobalArena(), mesh, &material, zt_shaderGetDefault(ztShaderDefault_Skybox), nullptr, ztModelFlags_OwnsMesh | ztModelFlags_OwnsMaterials);
}

// ------------------------------------------------------------------------------------------------

void zt_modelCalcMatrix(ztModel *model)
{
	ZT_PROFILE_RENDERING("zt_modelCalcMatrix");
	struct local
	{
		static void calculateModel(ztModel *model, const ztMat4 *parent_mat)
		{
			model->calculated_mat = ztMat4::identity.getTranslate(model->transform.position);

			if (model->transform.rotation != ztQuat::identity) {
				//model->calculated_mat.rotateEuler(model->transform.rotation);
				ztMat4 rmat = model->transform.rotation.convertToMat4();
				model->calculated_mat *= rmat;
			}

			if (model->transform.scale != ztVec3::one) {
				ztMat4 scale = ztMat4::identity;
				scale.scale(model->transform.scale);
				model->calculated_mat = model->calculated_mat * scale;
			}

			model->calculated_mat = model->calculated_mat * (*parent_mat);

			for (ztModel *child = model->first_child; child != nullptr; child = child->next) {
				calculateModel(child, &model->calculated_mat);
			}
		}
	};

	while(model->parent) {
		model = model->parent;
	}

	local::calculateModel(model, &ztMat4::identity);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztScene *zt_sceneMake(ztMemoryArena *arena, int max_models, int shadow_map_res)
{
	ZT_PROFILE_RENDERING("zt_sceneMake");
	ztScene *scene = zt_mallocStructArena(ztScene, arena);
	scene->models = zt_mallocStructArray(ztScene::ModelInfo, max_models);
	scene->models_count = 0;
	scene->models_size = max_models;
	scene->arena = arena;

	scene->directional_light.light = nullptr;
	scene->tex_directional_shadow_map = zt_textureMakeRenderTarget(shadow_map_res, shadow_map_res, ztTextureFlags_DepthMap);

	zt_fiz(ZT_SCENE_MAX_LIGHTS) {
		scene->lights[i].light = nullptr;
	}

	scene->skybox.model = nullptr;

	return scene;
}

// ------------------------------------------------------------------------------------------------

void zt_sceneFree(ztScene *scene)
{
	ZT_PROFILE_RENDERING("zt_sceneFree");
	if (scene == nullptr) {
		return;
	}

	zt_textureFree(scene->tex_directional_shadow_map);

	zt_freeArena(scene->models, scene->arena);
	zt_freeArena(scene, scene->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_sceneFreeAllModels(ztScene *scene)
{
	ZT_PROFILE_RENDERING("zt_sceneFreeAllModels");
	zt_returnOnNull(scene);

	zt_fiz(scene->models_count) {
		zt_modelFree(scene->models[i].model);
		scene->models[i].model = nullptr;
	}

	if (scene->skybox.model) {
		zt_modelFree(scene->skybox.model);
		scene->skybox.model = nullptr;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_sceneAddLight(ztScene *scene, ztLight *light)
{
	ZT_PROFILE_RENDERING("zt_sceneAddLight");
	zt_returnOnNull(scene);
	zt_returnOnNull(light);

	if (light->type == ztLightType_Directional) {
		scene->directional_light.light = light;
	}
	else {
		zt_fiz(ZT_SCENE_MAX_LIGHTS) {
			if (scene->lights[i].light == nullptr) {
				scene->lights[i].light = light;
				break;
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_sceneSetSkybox(ztScene *scene, ztModel *skybox)
{
	ZT_PROFILE_RENDERING("zt_sceneSetSkybox");
	zt_returnOnNull(scene);
	zt_returnOnNull(skybox);

	scene->skybox.model = skybox;
}

// ------------------------------------------------------------------------------------------------

void zt_sceneAddModel(ztScene *scene, ztModel *model)
{
	ZT_PROFILE_RENDERING("zt_sceneAddModel");
	zt_returnOnNull(scene);
	zt_returnOnNull(model);

	if (scene->models_count == scene->models_size) {
		zt_assert(false);
		return;
	}

#	if defined(ZT_DEBUG)
	zt_fiz(scene->models_count) {
		if (scene->models[i].model == model) {
			zt_assert(false); // the same model instance can't be added twice
		}
	}
#	endif

	// TODO: sort according to shader
	int idx = scene->models_count++;
	scene->models[idx].model = model;
	scene->models[idx].dist_from_cam = 0;
	
	if (zt_shaderHasVariable(model->shader, "light_pos", nullptr)) {
		scene->models[idx].flags |= ztSceneModelFlags_ShaderLit;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_sceneRemoveModel(ztScene *scene, ztModel *model)
{
	ZT_PROFILE_RENDERING("zt_sceneRemoveModel");
	zt_returnOnNull(scene);
	zt_returnOnNull(model);

	zt_fiz(scene->models_count) {
		if (scene->models[i].model == model) {
			for (int j = i; j < scene->models_count - 1; ++j) {
				scene->models[j] = scene->models[j + 1];
			}
			scene->models_count -= 1;
			return;
		}
	}

	zt_assert(false); // should not be removing a model that doesn't exist in the scene
}

// ------------------------------------------------------------------------------------------------

bool zt_sceneHasModel(ztScene *scene, ztModel *model)
{
	ZT_PROFILE_RENDERING("zt_sceneHasModel");
	zt_returnValOnNull(scene, false);
	zt_returnValOnNull(model, false);

	zt_fiz(scene->models_count) {
		if (scene->models[i].model == model) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_scenePrepare(ztScene *scene, ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_scenePrepare");
	zt_fiz(scene->models_count) {
		zt_modelCalcMatrix(scene->models[i].model);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_sceneOptimize(ztScene *scene, ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_sceneOptimize");
}

// ------------------------------------------------------------------------------------------------

ztInternal ztMat4 _zt_sceneLightingMakeLightMat(ztLight *light, ztCamera *camera, ztSceneLightingRules *lighting_rules)
{
	ZT_PROFILE_RENDERING("_zt_sceneLightingMakeLightMat");
	ztCamera camera_copy = *camera; // copy camera so that we can adjust near/far planes

	r32 shadow_near = .1f;
	r32 shadow_far  = lighting_rules ? lighting_rules->shadow_max_distance * 2 : 60.f;

	if(camera_copy.type == ztCameraType_Perspective) {
		//camera_copy.near_z = shadow_near;
		//camera_copy.far_z = lighting_rules ? lighting_rules->shadow_max_distance : 30.f;
		//camera = &camera_copy;
	}

	ztMat4 mat_view = ztMat4::identity.getLookAt(light->position.getNormal(), ztVec3::zero);
	ztMat4 mat_proj = ztMat4::makeOrthoProjection(-camera->far_z / 2.f, camera->far_z / 2.f, camera->far_z / 2.f, -camera->far_z / 2.f, shadow_near, shadow_far);

	ztVec3 center = camera->position + camera->direction * (camera->far_z / 2.f); //half_z;

	mat_view *= ztMat4::identity.getTranslate(center * ztVec3(-1, 1, -1));
	return mat_proj * mat_view;
}

// ------------------------------------------------------------------------------------------------

void zt_sceneLighting(ztScene *scene, ztCamera *camera, ztSceneLightingRules *lighting_rules)
{
	ZT_PROFILE_RENDERING("zt_sceneLighting");
	struct local
	{
		static void renderModelAndChildren(ztScene *scene, ztShaderID shader, ztModel *model, i32 match_flags)
		{
			if ((match_flags == 0 || zt_bitIsSet(model->flags, match_flags)) && !zt_bitIsSet(model->flags, ztModelFlags_Hidden)) {
				zt_shaderSetModelMatrices(shader, model->calculated_mat);

				bool changed_cull = zt_bitIsSet(model->flags, ztModelFlags_NoFaceCull);
				if (changed_cull) {
					zt_rendererSetFaceCulling(ztRendererFaceCulling_CullNone);
				}

				zt_meshRender(model->mesh_id);

				if (changed_cull) {
					zt_rendererSetFaceCulling(ztRendererFaceCulling_CullBack);
				}
			}

			ztModel *child = model->first_child;
			while (child) {
				renderModelAndChildren(scene, shader, child, match_flags);
				child = child->next;
			}
		}
	};

	if (scene->directional_light.light) {
		ztMat4 light_mat = _zt_sceneLightingMakeLightMat(scene->directional_light.light, camera, lighting_rules);

		_zt_rendererCheckToResetStats();

		zt_textureRenderTargetPrepare(scene->tex_directional_shadow_map);
		zt_rendererClear(ztVec4(1, 1, 1, 1));
		zt_rendererSetDepthTest(true, ztRendererDepthTestFunction_Less);

		ztShaderID shader = zt_shaderGetDefault(ztShaderDefault_ShadowDirectional);
		zt_shaderBegin(shader);

		static u32 light_matrix_hash = zt_strHash("light_matrix");
		zt_shaderSetVariableMat4(shader, light_matrix_hash, light_mat);
		zt_shaderApplyVariables(shader);
		ztShaderVariableValues *shader_vars = nullptr;

		zt_fiz(scene->models_count) {
			local::renderModelAndChildren(scene, shader, scene->models[i].model, ztModelFlags_CastsShadows);
		}

		zt_shaderEnd(shader);

		zt_textureRenderTargetCommit(scene->tex_directional_shadow_map);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_sceneRender(ztScene *scene, ztCamera *camera, ztSceneLightingRules *lighting_rules)
{
	ZT_PROFILE_RENDERING("zt_sceneRender");
	struct local
	{
		static void renderModelAndChildren(ztScene *scene, ztScene::ModelInfo *scene_model_info, ztModel *model, ztCamera *camera, ztMat4 *light_mat, ztShaderID *active_shader)
		{
			if (zt_bitIsSet(model->flags, ztModelFlags_Hidden)) {
				return;
			}

			bool shader_supports_lights = zt_bitIsSet(scene_model_info->flags, ztSceneModelFlags_ShaderLit);

			if(model->shader != *active_shader) {
				if(*active_shader != ztInvalidID) {
					zt_shaderEnd(*active_shader);
				}
				*active_shader = model->shader;
				zt_shaderBegin(*active_shader);

				if (shader_supports_lights) {
					if (scene->directional_light.light) {
						static u32 light_matrix_hash    = zt_strHash("light_matrix");
						static u32 light_pos_hash       = zt_strHash("light_pos");
						static u32 light_ambient_hash   = zt_strHash("light_ambient");
						static u32 light_intensity_hash = zt_strHash("light_intensity");
						static u32 light_color_hash     = zt_strHash("light_color");
						static u32 view_pos_hash        = zt_strHash("view_pos");
						zt_shaderSetVariableMat4(*active_shader, light_matrix_hash, *light_mat);
						zt_shaderSetVariableVec3(*active_shader, light_pos_hash, scene->directional_light.light->position);
						zt_shaderSetVariableFloat(*active_shader, light_ambient_hash, scene->directional_light.light->ambient);
						zt_shaderSetVariableFloat(*active_shader, light_intensity_hash, scene->directional_light.light->intensity);
						zt_shaderSetVariableVec4(*active_shader, light_color_hash, scene->directional_light.light->color);
						zt_shaderSetVariableVec3(*active_shader, view_pos_hash, camera->position);
					}
					
					int lights = 0;
					static u32 point_lights_ambient_color_hash[ZT_SCENE_MAX_LIGHTS] = { 0 };
					static u32 point_lights_intensity_hash[ZT_SCENE_MAX_LIGHTS];
					static u32 point_lights_pos_hash[ZT_SCENE_MAX_LIGHTS];

					zt_fiz(ZT_SCENE_MAX_LIGHTS) {
						if (scene->lights[i].light != 0) {

							if (point_lights_ambient_color_hash[i] == 0) {
								char varname[128];

								zt_strPrintf(varname, zt_elementsOf(varname), "point_lights[%d].ambient_color", i);
								point_lights_ambient_color_hash[i] = zt_strHash(varname);

								zt_strPrintf(varname, zt_elementsOf(varname), "point_lights[%d].intensity", i);
								point_lights_intensity_hash[i] = zt_strHash(varname);

								zt_strPrintf(varname, zt_elementsOf(varname), "point_lights[%d].pos", i);
								point_lights_pos_hash[i] = zt_strHash(varname);
							}

							zt_shaderSetVariableVec3(*active_shader, point_lights_ambient_color_hash[i], scene->lights[i].light->color.rgb);
							zt_shaderSetVariableFloat(*active_shader, point_lights_intensity_hash[i], scene->lights[i].light->intensity);
							zt_shaderSetVariableVec3(*active_shader, point_lights_pos_hash[i], scene->lights[i].light->position);

							lights += 1;
						}
					}

					static u32 point_lights_count_hash = zt_strHash("point_lights_count");
					zt_shaderSetVariableInt(*active_shader, point_lights_count_hash, lights);
				}

				zt_shaderSetCameraMatrices(*active_shader, camera->mat_proj, camera->mat_view);
				if (model->shader_vars) {
					zt_shaderApplyVariables(*active_shader, model->shader_vars);
				}
			}
			else if (model->shader_vars) {
				zt_shaderApplyVariables(*active_shader, model->shader_vars);
			}

			if (shader_supports_lights) {
				static u32 shadowmap_directional_tex_hash = zt_strHash("shadowmap_directional_tex");
				zt_materialPrepare(&model->material, *active_shader, &scene->tex_directional_shadow_map, &shadowmap_directional_tex_hash, 1);
			}
			else {
				zt_materialPrepare(&model->material, *active_shader);
			}

			zt_shaderSetModelMatrices(*active_shader, model->calculated_mat);

			bool changed_cull = zt_bitIsSet(model->flags, ztModelFlags_NoFaceCull);
			if (changed_cull) {
				zt_rendererSetFaceCulling(ztRendererFaceCulling_CullNone);
			}

			zt_meshRender(model->mesh_id);

			if (changed_cull) {
				zt_rendererSetFaceCulling(ztRendererFaceCulling_CullBack);
			}

			ztModel *child = model->first_child;
			while (child) {
				local::renderModelAndChildren(scene, scene_model_info, child, camera, light_mat, active_shader);
				child = child->next;
			}

		}
	};

	_zt_rendererCheckToResetStats();

	zt_rendererSetDepthTest(true, ztRendererDepthTestFunction_LessEqual);

	ztShaderID shader = ztInvalidID;
	ztShaderVariableValues *shader_vars = nullptr;

	ztMat4 light_mat;
	if (scene->directional_light.light) {
		light_mat = _zt_sceneLightingMakeLightMat(scene->directional_light.light, camera, lighting_rules);
	}
	else {
		light_mat = ztMat4::identity;
	}

	if (scene->skybox.model) {
		static u32 skybox_hash = zt_strHash("skybox_tex");

		ztMat4 mat_view = camera->mat_view;
		mat_view.values[ztMat4_Col3Row0] = mat_view.values[ztMat4_Col3Row1] = mat_view.values[ztMat4_Col3Row2] = 0;
		mat_view.values[ztMat4_Col3Row3] = 1;

		zt_shaderBegin(scene->skybox.model->shader);
		zt_shaderSetCameraMatrices(scene->skybox.model->shader, camera->mat_proj, mat_view);
		zt_shaderSetVariableTexCube(scene->skybox.model->shader, skybox_hash, scene->skybox.model->material.diffuse_tex);
		zt_shaderApplyVariables(scene->skybox.model->shader);
		zt_meshRender(scene->skybox.model->mesh_id);
		zt_shaderEnd(scene->skybox.model->shader);
	}

	zt_fiz(scene->models_count) {
		local::renderModelAndChildren(scene, &scene->models[i], scene->models[i].model, camera, &light_mat, &shader);
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
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
	ZT_PROFILE_RENDERING("zt_rendererClear");
	switch(zt_game->win_game_settings[0].renderer)
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			glClearColor(r, g, b, a);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
#			endif
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_clear(zt_game->win_details[0].dx_context, r, g, b, a));
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_rendererClear(ztVec4 clr)
{
	return zt_rendererClear(clr.r, clr.g, clr.b, clr.a);
}

// ------------------------------------------------------------------------------------------------

void zt_rendererSetDepthTest(bool depth_test, ztRendererDepthTestFunction_Enum function)
{
	ZT_PROFILE_RENDERING("zt_rendererSetDepthTest");
	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			if (!depth_test) {
				glDisable(GL_DEPTH_TEST);
			}
			else {
				glEnable(GL_DEPTH_TEST);

				switch (function)
				{
					case ztRendererDepthTestFunction_Never       : ztgl_depthTestNever();        break;
					case ztRendererDepthTestFunction_Less        : ztgl_depthTestLess();         break;
					case ztRendererDepthTestFunction_LessEqual   : ztgl_depthTestLessEqual();    break;
					case ztRendererDepthTestFunction_Equal       : ztgl_depthTestEqual();        break;
					case ztRendererDepthTestFunction_Greater     : ztgl_depthTestGreater();      break;
					case ztRendererDepthTestFunction_NotEqual    : ztgl_depthTestNotEqual();     break;
					case ztRendererDepthTestFunction_GreaterEqual: ztgl_depthTestGreaterEqual(); break;
					case ztRendererDepthTestFunction_Always      : ztgl_depthTestAlways();       break;
				}
				
			}
#			endif
		} break;
		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			switch (function)
			{
				case ztRendererDepthTestFunction_Never       : ztdx_depthTestNever(zt_game->win_details[0].dx_context);        break;
				case ztRendererDepthTestFunction_Less        : ztdx_depthTestLess(zt_game->win_details[0].dx_context);         break;
				case ztRendererDepthTestFunction_LessEqual   : ztdx_depthTestLessEqual(zt_game->win_details[0].dx_context);    break;
				case ztRendererDepthTestFunction_Equal       : ztdx_depthTestEqual(zt_game->win_details[0].dx_context);        break;
				case ztRendererDepthTestFunction_Greater     : ztdx_depthTestGreater(zt_game->win_details[0].dx_context);      break;
				case ztRendererDepthTestFunction_NotEqual    : ztdx_depthTestNotEqual(zt_game->win_details[0].dx_context);     break;
				case ztRendererDepthTestFunction_GreaterEqual: ztdx_depthTestGreaterEqual(zt_game->win_details[0].dx_context); break;
				case ztRendererDepthTestFunction_Always      : ztdx_depthTestAlways(zt_game->win_details[0].dx_context);       break;
			}
#			endif
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_rendererSetFaceCulling(ztRendererFaceCulling_Enum culling)
{
	ZT_PROFILE_RENDERING("zt_rendererSetFaceCulling");
	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			switch (culling)
			{
				case ztRendererFaceCulling_CullBack : ztgl_cullBack(); break;
				case ztRendererFaceCulling_CullFront: ztgl_cullFront(); break;
				case ztRendererFaceCulling_CullNone : ztgl_cullNone(); break;
			}
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			switch (culling)
			{
				case ztRendererFaceCulling_CullBack : ztdx_cullBack(zt_game->win_details[0].dx_context); break;
				case ztRendererFaceCulling_CullFront: ztdx_cullFront(zt_game->win_details[0].dx_context); break;
				case ztRendererFaceCulling_CullNone : ztdx_cullNone(zt_game->win_details[0].dx_context); break;
			}
#			endif
		} break;
	}

}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestChange(ztRenderer_Enum renderer)
{
	ZT_PROFILE_RENDERING("zt_rendererRequestChange");
	if (zt_game->renderer_requests_count >= zt_elementsOf(zt_game->renderer_requests))
		return;

	auto* request = &zt_game->renderer_requests[zt_game->renderer_requests_count++];
	request->type = ztRendererRequest_Change;
	request->change_to = renderer;
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestWindowed()
{
	ZT_PROFILE_RENDERING("zt_rendererRequestWindowed");
	if (!zt_bitIsSet(zt_game->win_game_settings[0].renderer_flags, ztRendererFlags_Fullscreen))
		return;

	if (zt_game->renderer_requests_count >= zt_elementsOf(zt_game->renderer_requests))
		return;

	auto* request = &zt_game->renderer_requests[zt_game->renderer_requests_count++];
	request->type = ztRendererRequest_Windowed;
}

// ------------------------------------------------------------------------------------------------

void zt_rendererRequestFullscreen()
{
	ZT_PROFILE_RENDERING("zt_rendererRequestFullscreen");
	if (zt_bitIsSet(zt_game->win_game_settings[0].renderer_flags, ztRendererFlags_Fullscreen))
		return;

	if (zt_game->win_count > 1)
		return; // cannot go into fullscreen if there are multiple windows opened

	if (zt_game->renderer_requests_count >= zt_elementsOf(zt_game->renderer_requests))
		return;

	auto* request = &zt_game->renderer_requests[zt_game->renderer_requests_count++];
	request->type = ztRendererRequest_Fullscreen;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztShaderID _zt_shaderMakeBase(const char *name, const char *data_in, i32 data_len, ztShaderID replace);

// ---------

ztInternal void _zt_rendererShaderReload(ztAssetManager *asset_mgr, ztAssetID asset_id, void *user_data)
{
	ZT_PROFILE_RENDERING("_zt_rendererShaderReload");
	zt_logInfo("shader reload: asset_id: %d (%s)", asset_id, asset_mgr->asset_name[asset_id]);
	ztShaderID shader_id = (ztShaderID)user_data;
	zt_assert(shader_id >= 0 && shader_id < zt_game->shaders_count);

	i32 size = zt_assetSize(asset_mgr, asset_id);
	if (size <= 0) {
		zt_logCritical("shader reload: unable to determine asset size");
		return;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		zt_logCritical("shader reload: unable to allocate memory for asset data");
		return;
	}

	const char *error = nullptr;

	if (!zt_assetLoadData(asset_mgr, asset_id, data, size)) {
		error = "Unable to load asset contents";
		goto on_error;
	}

	ztShaderID result_shader_id = _zt_shaderMakeBase(asset_mgr->asset_name[asset_id], data, size, shader_id);
	if (result_shader_id == ztInvalidID) {
		goto on_error;
	}

	zt_game->shaders[shader_id].load_type = ztShaderLoadType_Asset;
	zt_game->shaders[shader_id].asset_mgr = asset_mgr;
	zt_game->shaders[shader_id].asset_id = asset_id;

	zt_assetAddReloadCallback(asset_mgr, asset_id, _zt_rendererShaderReload, (void*)shader_id);

	zt_free(data);
	return;

on_error:
	zt_logCritical("Unable to reload shader (%s). %s.", asset_mgr->asset_name[asset_id], error);
	zt_free(data);
}

// ------------------------------------------------------------------------------------------------

ztShaderID _zt_shaderMakeBase(const char *name, const char *data_in, i32 data_len, ztShaderID replace = ztInvalidID)
{
	ZT_PROFILE_RENDERING("_zt_shaderMakeBase");
	ztShaderID shader_id = ztInvalidID;

	ztShaderVariableValues var_values;
	if (replace != ztInvalidID) {
		zt_shaderPopulateVariables(replace, &var_values);
	}
	
	char data[1024 * 64];
	zt_assert(data_len < sizeof(data));
	zt_strCpy(data, sizeof(data), data_in, data_len);

	const int max_idx = 16;
	i32 gl_vert_beg[max_idx]; i32 gl_vert_len[max_idx]; i32 gl_vert_cnt = 0;
	i32 gl_geom_beg[max_idx]; i32 gl_geom_len[max_idx]; i32 gl_geom_cnt = 0;
	i32 gl_frag_beg[max_idx]; i32 gl_frag_len[max_idx]; i32 gl_frag_cnt = 0;
	i32 dx_vert_beg[max_idx]; i32 dx_vert_len[max_idx]; i32 dx_vert_cnt = 0;
	i32 dx_frag_beg[max_idx]; i32 dx_frag_len[max_idx]; i32 dx_frag_cnt = 0;

	const char* glsl_vs = "glsl_vs";
	const int glsl_vs_len = zt_strLen(glsl_vs);
	const char* glsl_gs = "glsl_gs";
	const int glsl_gs_len = zt_strLen(glsl_gs);
	const char* glsl_fs = "glsl_fs";
	const int glsl_fs_len = zt_strLen(glsl_fs);
	const char* hlsl_vs = "hlsl_vs";
	const int hlsl_vs_len = zt_strLen(hlsl_vs);
	const char* hlsl_fs = "hlsl_fs";
	const int hlsl_fs_len = zt_strLen(hlsl_fs);

	const char *error = nullptr;

	i32 pos_beg = zt_strFindPos(data, "<<[", 0);
	while (pos_beg != ztStrPosNotFound) {
		int pos_end = zt_strFindPos(data, "]>>", pos_beg);
		if (pos_end == ztStrPosNotFound) {
			error = "Invalid format.";
			goto on_error;
		}
		pos_beg += 3;

		i32 *arr_beg = nullptr, *arr_len = nullptr, *arr_cnt = nullptr;

			 if (zt_striStartsWith(data + pos_beg, pos_end - pos_beg, glsl_vs, glsl_vs_len)) { arr_beg = gl_vert_beg; arr_len = gl_vert_len; arr_cnt = &gl_vert_cnt; }
		else if (zt_striStartsWith(data + pos_beg, pos_end - pos_beg, glsl_gs, glsl_gs_len)) { arr_beg = gl_geom_beg; arr_len = gl_geom_len; arr_cnt = &gl_geom_cnt; }
		else if (zt_striStartsWith(data + pos_beg, pos_end - pos_beg, glsl_fs, glsl_fs_len)) { arr_beg = gl_frag_beg; arr_len = gl_frag_len; arr_cnt = &gl_frag_cnt; }
		else if (zt_striStartsWith(data + pos_beg, pos_end - pos_beg, hlsl_vs, hlsl_vs_len)) { arr_beg = dx_vert_beg; arr_len = dx_vert_len; arr_cnt = &dx_vert_cnt; }
		else if (zt_striStartsWith(data + pos_beg, pos_end - pos_beg, hlsl_fs, hlsl_fs_len)) { arr_beg = dx_frag_beg; arr_len = dx_frag_len; arr_cnt = &dx_frag_cnt; }

		if (arr_beg && arr_len && arr_cnt) {
			int sh_beg = zt_strFindPos(data, "<<[", pos_end + 3);
			int sh_end = zt_strFindPos(data, "]>>", sh_beg);
			if (sh_beg == ztStrPosNotFound || sh_end == ztStrPosNotFound) {
				error = "Error in format.";
				goto on_error;
			}
			sh_beg += 3;
			int idx = (*arr_cnt)++;
			arr_beg[idx] = sh_beg;
			arr_len[idx] = sh_end - sh_beg;
			pos_end += arr_len[idx];
		}
		else {
			char temp[1024] = {0};
			zt_strCpy(temp, sizeof(temp), data + pos_beg, pos_end - pos_beg);
			zt_logVerbose("Unknown shader group encountered: %s", temp);
		}

		pos_beg = zt_strFindPos(data, "<<[", pos_end);
	}

	ztGameSettings *game_settings = &zt_game->win_game_settings[0];
	if (game_settings->renderer == ztRenderer_OpenGL) {
#if defined(ZT_OPENGL)
		if (gl_vert_cnt == 0) { error = "No vertex shader found"; goto on_error; }
		if (gl_frag_cnt == 0) { error = "No fragment shader found"; goto on_error; }

		char *vert_src = data + gl_vert_beg[0];
		vert_src[gl_vert_len[0]] = 0;

		char *frag_src = data + gl_frag_beg[0];
		frag_src[gl_frag_len[0]] = 0;

		char *geom_src = gl_geom_cnt ? data + gl_geom_beg[0] : nullptr;
		if (gl_geom_cnt) geom_src[gl_geom_len[0]] = 0;

		if (replace != ztInvalidID) {
			zt_shaderFree(replace);
			shader_id = replace;
		}
		else {
			zt_assert(zt_game->shaders_count < zt_elementsOf(zt_game->shaders));
			shader_id = zt_game->shaders_count++;
		}

		ztShaderGL *gl_shader = zt_game->shaders[shader_id].gl_shader = ztgl_shaderMake(vert_src, frag_src, geom_src);
		if(gl_shader == nullptr) {
			return ztInvalidID;
		}

		ztShader* shader = &zt_game->shaders[shader_id];
		shader->renderer = ztRenderer_OpenGL;

		shader->variables.variables_count = gl_shader->uniforms_count;
		zt_fiz(shader->variables.variables_count) {
			ztShaderVariable_Enum var_type = ztShaderVariable_Invalid;
			switch (gl_shader->uniforms[i].type)
			{
				case GL_FLOAT       : var_type = ztShaderVariable_Float; break;
				case GL_FLOAT_VEC2  : var_type = ztShaderVariable_Vec2; break;
				case GL_FLOAT_VEC3  : var_type = ztShaderVariable_Vec3; break;
				case GL_FLOAT_VEC4  : var_type = ztShaderVariable_Vec4; break;
				case GL_INT         : var_type = ztShaderVariable_Int; break;
				case GL_FLOAT_MAT3  : var_type = ztShaderVariable_Mat3; break;
				case GL_FLOAT_MAT4  : var_type = ztShaderVariable_Mat4; break;
				case GL_SAMPLER_2D  : var_type = ztShaderVariable_Tex; break;
				case GL_SAMPLER_CUBE: var_type = ztShaderVariable_TexCube; break;
			}

			if (var_type == ztShaderVariable_Invalid) {
				zt_logDebug("Unsupported shader variable type in variable %s", gl_shader->uniforms[i].name);
			}
			else {
				shader->variables.variables[i].type = var_type;
				zt_strCpy(shader->variables.variables[i].name, zt_elementsOf(shader->variables.variables[i].name), gl_shader->uniforms[i].name);
				shader->variables.variables[i].name_hash = zt_strHash(shader->variables.variables[i].name);
			}
		}


#else
		error = "OpenGL has been disabled in the library.";
		goto on_error;
#endif // ZT_OPENGL
	}
	else if (game_settings->renderer == ztRenderer_DirectX) {
#if defined(ZT_DIRECTX)
		if (dx_vert_cnt == 0) { error = "No DirectX vertex shader found"; goto on_error; }
		if (dx_frag_cnt == 0) { error = "No DirectX fragment shader found"; goto on_error; }

		char *vert_src = data + dx_vert_beg[0];
		vert_src[dx_vert_len[0]] = 0;
		char vert_entry[128] = { 0 };

		char *frag_src = data + dx_frag_beg[0];
		frag_src[dx_frag_len[0]] = 0;
		char frag_entry[128] = { 0 };

		struct DirectX
		{
			static void getEntryFunction(char *start, int start_len, const char *src, char entry_func[128])
			{
				int label_pos = zt_strFindLastPos(start, start_len, "<<[", (int)(src - start) - 4);
				char *header = start + label_pos;
				int label_end = zt_strFindPos(header, "]>>", 0);

				ztToken header_tokens[4];
				int header_tokens_count = zt_strTokenize(header, label_end, " ,", header_tokens, zt_elementsOf(header_tokens), ztStrTokenizeFlags_TrimWhitespace);
				if (header_tokens_count == 2) { // 0 - hlsl_xx, 1 - entry function
					zt_strCpy(entry_func, 128, header + header_tokens[1].beg, header_tokens[1].len);
				}
			}
		};

		DirectX::getEntryFunction((char*)data_in, data_len, data_in + dx_vert_beg[0], vert_entry);
		DirectX::getEntryFunction((char*)data_in, data_len, data_in + dx_frag_beg[0], frag_entry);

		if (replace != ztInvalidID) {
			zt_shaderFree(replace);
			shader_id = replace;
		}
		else {
			zt_assert(zt_game->shaders_count < zt_elementsOf(zt_game->shaders));
			shader_id = zt_game->shaders_count++;
		}

		ztShader* shader = &zt_game->shaders[shader_id];
		shader->renderer = ztRenderer_DirectX;
		ztShaderDX *dx_shader = shader->dx_shader = ztdx_shaderMake(zt_game->win_details[0].dx_context, vert_src, vert_entry, frag_src, frag_entry);
		if (shader->dx_shader == nullptr) {
			return ztInvalidID;
		}

		shader->variables.variables_count = dx_shader->variables_count;
		zt_fiz(shader->variables.variables_count) {
			ztShaderVariable_Enum var_type = ztShaderVariable_Invalid;
			switch (dx_shader->variables[i].type)
			{
				case ztShaderDXVariableType_Float  : var_type = ztShaderVariable_Float; break;
				case ztShaderDXVariableType_Vec2   : var_type = ztShaderVariable_Vec2; break;
				case ztShaderDXVariableType_Vec3   : var_type = ztShaderVariable_Vec3; break;
				case ztShaderDXVariableType_Vec4   : var_type = ztShaderVariable_Vec4; break;
				case ztShaderDXVariableType_Int    : var_type = ztShaderVariable_Int; break;
				case ztShaderDXVariableType_Mat3   : var_type = ztShaderVariable_Mat3; break;
				case ztShaderDXVariableType_Mat4   : var_type = ztShaderVariable_Mat4; break;
				case ztShaderDXVariableType_Tex    : var_type = ztShaderVariable_Tex; break;
				case ztShaderDXVariableType_TexCube: var_type = ztShaderVariable_TexCube; break;
			}

			if (var_type == ztShaderVariable_Invalid) {
				zt_logDebug("Unsupported shader variable type in variable %s", dx_shader->variables[i].name);
			}
			else {
				shader->variables.variables[i].type = var_type;
				zt_strCpy(shader->variables.variables[i].name, zt_elementsOf(shader->variables.variables[i].name), dx_shader->variables[i].name);
				shader->variables.variables[i].name_hash = zt_strHash(shader->variables.variables[i].name);
			}
		}

#else
		error = "DirectX has been disabled in the library.";
		goto on_error;
#endif // ZT_DIRECTX
	}

	if (replace != ztInvalidID && shader_id != ztInvalidID) {
		ztShader *shader = &zt_game->shaders[shader_id];
		zt_fjz(shader->variables.variables_count) {
			zt_fiz(var_values.variables_count) {
				if (zt_strEquals(var_values.variables[i].name, shader->variables.variables[j].name)) {
					zt_memCpy(&shader->variables.variables[j], zt_sizeof(ztShaderVariableValues::Variable), &var_values.variables[i], zt_sizeof(ztShaderVariableValues::Variable));
					break;
				}
			}
		}
	}
	return shader_id;

on_error:
	zt_logCritical("Unable to load shader (%s). %s.", name, error);
	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

ztShaderID zt_shaderMake(const char *name, const char *data, i32 data_len)
{
	ZT_PROFILE_RENDERING("zt_shaderMake(char*)");
	ztShaderID shader_id = _zt_shaderMakeBase(name, data, data_len);
	if (shader_id == ztInvalidID) {
		return shader_id;
	}

	zt_game->shaders[shader_id].load_type = ztShaderLoadType_Data;
	zt_game->shaders[shader_id].data = data;
	zt_game->shaders[shader_id].data_len = data_len;

	return shader_id;
}

// ------------------------------------------------------------------------------------------------

ztShaderID zt_shaderMake(ztAssetManager *asset_mgr, ztAssetID asset_id)
{
	ZT_PROFILE_RENDERING("zt_shaderMake(ztAssetID)");
	zt_returnValOnNull(asset_mgr, ztInvalidID);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	if (asset_mgr->asset_type[asset_id] != ztAssetManagerType_Shader && asset_mgr->asset_type[asset_id] != ztAssetManagerType_Unknown) {
		return ztInvalidID;
	}

	i32 size = zt_assetSize(asset_mgr, asset_id);
	if (size <= 0) {
		return ztInvalidID;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		return ztInvalidID;
	}

	const char *error = nullptr;

	if (!zt_assetLoadData(asset_mgr, asset_id, data, size)) {
		error = "Unable to load asset contents";
		goto on_error;
	}

	ztShaderID shader_id = _zt_shaderMakeBase(asset_mgr->asset_name[asset_id], data, size);
	if (shader_id == ztInvalidID) {
		goto on_error;
	}

	zt_game->shaders[shader_id].load_type = ztShaderLoadType_Asset;
	zt_game->shaders[shader_id].asset_mgr = asset_mgr;
	zt_game->shaders[shader_id].asset_id = asset_id;

	zt_assetAddReloadCallback(asset_mgr, asset_id, _zt_rendererShaderReload, (void*)shader_id);

	zt_free(data);
	return shader_id;

on_error:
	zt_logCritical("Unable to load shader (%s). %s.", asset_mgr->asset_name[asset_id], error);
	zt_free(data);
	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

void zt_shaderFree(ztShaderID shader_id)
{
	ZT_PROFILE_RENDERING("zt_shaderFree");
	zt_assert(shader_id >= 0 && shader_id < zt_game->shaders_count);

	ztShader* shader = &zt_game->shaders[shader_id];

	if (shader->renderer == ztRenderer_Invalid) {
		return;
	}

	if (shader->load_type == ztShaderLoadType_Asset && shader->asset_mgr) {
		zt_assetRemoveReloadCallback(shader->asset_mgr, shader->asset_id, (void*)shader_id);
	}

	if (shader->renderer == ztRenderer_OpenGL) {
		zt_openGLSupport(ztgl_shaderFree(shader->gl_shader));
	}
	else if (shader->renderer == ztRenderer_DirectX) {
		zt_directxSupport(ztdx_shaderFree(zt_game->win_details[0].dx_context, shader->dx_shader));
	}

	zt_memSet(shader, sizeof(ztShader), 0);
}

// ------------------------------------------------------------------------------------------------

void zt_shaderBegin(ztShaderID shader_id)
{
	ZT_PROFILE_RENDERING("zt_shaderBegin");
	zt_game->game_details.curr_frame.shader_switches += 1;

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
			zt_openGLSupport(ztgl_shaderBegin(zt_game->shaders[shader_id].gl_shader));
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_shaderBegin(zt_game->win_details[0].dx_context, zt_game->shaders[shader_id].dx_shader));
		} break;

		default: {
			zt_assert(false);
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_shaderEnd(ztShaderID shader_id)
{
	ZT_PROFILE_RENDERING("zt_shaderEnd");
	zt_assertReturnOnFail(shader_id >= 0 && shader_id < zt_game->shaders_count);

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
			zt_openGLSupport(ztgl_shaderEnd(zt_game->shaders[shader_id].gl_shader));
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_shaderEnd(zt_game->win_details[0].dx_context, zt_game->shaders[shader_id].dx_shader));
		} break;

		default: {
			zt_assert(false);
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetCameraMatrices(ztShaderID shader_id, const ztMat4& projection, const ztMat4& view)
{
	ZT_PROFILE_RENDERING("zt_shaderSetCameraMatrices");
	static u32 view_hash = zt_strHash("view");
	static u32 projection_hash = zt_strHash("projection");
	zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, view_hash, view);
	zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, projection_hash, projection);
	zt_shaderApplyVariables(shader_id);
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetModelMatrices(ztShaderID shader_id, const ztMat4& model)
{
	ZT_PROFILE_RENDERING("zt_shaderSetModelMatrices");
	static u32 model_hash = zt_strHash("model");
	zt_shaderSetVariableMat4(&zt_game->shaders[shader_id].variables, model_hash, model);
	zt_shaderApplyVariables(shader_id);
}

// ------------------------------------------------------------------------------------------------

void zt_shaderPopulateVariables(ztShaderID shader_id, ztShaderVariableValues *shader_vars)
{
	ZT_PROFILE_RENDERING("zt_shaderPopulateVariables");
	zt_returnOnNull(shader_vars);
	zt_assertReturnOnFail(shader_id >= 0 && shader_id <= zt_game->shaders_count);

	zt_memCpy(shader_vars, zt_sizeof(ztShaderVariableValues), &zt_game->shaders[shader_id].variables, zt_sizeof(ztShaderVariableValues));

	zt_fiz(shader_vars->variables_count) {
		shader_vars->variables[i].changed = false;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_shaderApplyVariables(ztShaderID shader_id, ztShaderVariableValues *shader_vars)
{
	ZT_PROFILE_RENDERING("zt_shaderApplyVariables");
	zt_returnOnNull(shader_vars);
	zt_assertReturnOnFail(shader_id >= 0 && shader_id <= zt_game->shaders_count);

	ztShaderVariableValues *shader = &zt_game->shaders[shader_id].variables;

#if defined(ZT_DEBUG)
	// validate that the shader variables match up
	zt_assertReturnOnFail(shader->variables_count == shader_vars->variables_count);
	zt_fiz(shader->variables_count) {
		zt_assertReturnOnFail(shader->variables[i].type == shader_vars->variables[i].type);
		zt_assertReturnOnFail(zt_strEquals(shader->variables[i].name, shader_vars->variables[i].name));
	}
#endif

	zt_memCpy(&shader->variables, zt_sizeof(ztShaderVariableValues), shader_vars, zt_sizeof(ztShaderVariableValues));
	zt_shaderApplyVariables(shader_id);
}

// ------------------------------------------------------------------------------------------------

void zt_shaderApplyVariables(ztShaderID shader_id)
{
	ZT_PROFILE_RENDERING("zt_shaderApplyVariables");
	ztShader *shader = &zt_game->shaders[shader_id];
	ztShaderVariableValues *shader_vars = &shader->variables;

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			if (shader_vars->variables_count) {
				{
					ZT_PROFILE_RENDERING("ztgl_textureBindReset");
					ztgl_textureBindReset(shader->gl_shader);
				}
				{
					ZT_PROFILE_RENDERING("ztgl_shaderVariable...");

					zt_fiz(shader_vars->variables_count) {
						ztShaderVariableValues::Variable *val = &shader_vars->variables[i];

						switch (val->type)
						{
							case ztShaderVariable_Float  : ztgl_shaderVariableFloat(shader->gl_shader, val->name_hash, val->val_float); break;
							case ztShaderVariable_Int    : ztgl_shaderVariableInt  (shader->gl_shader, val->name_hash, val->val_int  ); break;
							case ztShaderVariable_Vec2   : ztgl_shaderVariableVec2 (shader->gl_shader, val->name_hash, val->val_vec2 ); break;
							case ztShaderVariable_Vec3   : ztgl_shaderVariableVec3 (shader->gl_shader, val->name_hash, val->val_vec3 ); break;
							case ztShaderVariable_Vec4   : ztgl_shaderVariableVec4 (shader->gl_shader, val->name_hash, val->val_vec4 ); break;
							case ztShaderVariable_Mat3   : ztgl_shaderVariableMat3 (shader->gl_shader, val->name_hash, val->val_mat3 ); break;
							case ztShaderVariable_Mat4   : ztgl_shaderVariableMat4 (shader->gl_shader, val->name_hash, val->val_mat4 ); break;
							case ztShaderVariable_Tex    : ztgl_shaderVariableTex  (shader->gl_shader, val->name_hash, zt_game->textures[val->val_tex].gl_texture); break;
							case ztShaderVariable_TexCube: ztgl_shaderVariableTex  (shader->gl_shader, val->name_hash, zt_game->textures[val->val_tex].gl_texture); break;
						}
					}
				}
			}
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			// populate cbuffer data
			if (shader_vars->variables_count) {
				zt_fiz(shader_vars->variables_count) {
					ztShaderVariableValues::Variable *val = &shader_vars->variables[i];

					switch (val->type)
					{
						case ztShaderVariable_Float  : ztdx_shaderVariableFloat(shader->dx_shader, val->name_hash, val->val_float); break;
						case ztShaderVariable_Int    : ztdx_shaderVariableInt  (shader->dx_shader, val->name_hash, val->val_int  ); break;
						case ztShaderVariable_Vec2   : ztdx_shaderVariableVec2 (shader->dx_shader, val->name_hash, val->val_vec2 ); break;
						case ztShaderVariable_Vec3   : ztdx_shaderVariableVec3 (shader->dx_shader, val->name_hash, val->val_vec3 ); break;
						case ztShaderVariable_Vec4   : ztdx_shaderVariableVec4 (shader->dx_shader, val->name_hash, val->val_vec4 ); break;
						case ztShaderVariable_Mat3   : ztdx_shaderVariableMat3 (shader->dx_shader, val->name_hash, val->val_mat3 ); break;
						case ztShaderVariable_Mat4   : ztdx_shaderVariableMat4 (shader->dx_shader, val->name_hash, val->val_mat4 ); break;
						case ztShaderVariable_Tex    : ztdx_shaderVariableTex  (shader->dx_shader, val->name_hash, zt_game->textures[val->val_tex].dx_texture); break;
						case ztShaderVariable_TexCube: ztdx_shaderVariableTex  (shader->dx_shader, val->name_hash, zt_game->textures[val->val_tex].dx_texture); break;
					}
				}

				ztdx_shaderPopulateConstantBuffers(zt_game->win_details[0].dx_context, shader->dx_shader);
			}
#			endif
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_shaderHasVariable(ztShaderVariableValues *shader_vars, const char *variable, ztShaderVariable_Enum *type)
{
	return zt_shaderHasVariable(shader_vars, zt_strHash(variable), type);
}

// ------------------------------------------------------------------------------------------------

bool zt_shaderHasVariable(ztShaderVariableValues *shader_vars, u32 variable_hash, ztShaderVariable_Enum *type)
{
	ZT_PROFILE_RENDERING("zt_shaderHasVariable");
	zt_returnValOnNull(shader_vars, false);

	zt_fiz(shader_vars->variables_count) {
		if (shader_vars->variables[i].name_hash == variable_hash) {
			if (type) *type = shader_vars->variables[i].type;
			return true;
		}
	}
	if (type) *type = ztShaderVariable_Invalid;
	return false;
}

// ------------------------------------------------------------------------------------------------

#define _zt_shaderCheckHash(shader_vars) \
	int idx = -1; \
	zt_fiz(shader_vars->variables_count) { \
		if (shader_vars->variables[i].name_hash == variable_hash) {\
			idx = i; break; \
						} \
	} \
	if (idx == -1) { return; } \

#define _zt_shaderCheckType(shared_vars, shader_type) \
	if (shader_vars->variables[idx].type != shader_type) { \
		zt_assert(false); \
		return; \
			}

#define _zt_shaderCheckHashAndType(shared_vars, shader_type) \
	_zt_shaderCheckHash(shader_vars); \
	_zt_shaderCheckType(shader_vars, shader_type);


// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableFloat  (ztShaderVariableValues *shader_vars, const char *variable, r32 value          ) { zt_shaderSetVariableFloat  (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableInt    (ztShaderVariableValues *shader_vars, const char *variable, i32 value          ) { zt_shaderSetVariableInt    (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableVec2   (ztShaderVariableValues *shader_vars, const char *variable, const ztVec2& value) { zt_shaderSetVariableVec2   (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableVec3   (ztShaderVariableValues *shader_vars, const char *variable, const ztVec3& value) { zt_shaderSetVariableVec3   (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableVec4   (ztShaderVariableValues *shader_vars, const char *variable, const ztVec4& value) { zt_shaderSetVariableVec4   (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableMat4   (ztShaderVariableValues *shader_vars, const char *variable, const ztMat4& value) { zt_shaderSetVariableMat4   (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableMat3   (ztShaderVariableValues *shader_vars, const char *variable, r32 value[12]      ) { zt_shaderSetVariableMat3   (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableTex    (ztShaderVariableValues *shader_vars, const char *variable, ztTextureID value  ) { zt_shaderSetVariableTex    (shader_vars, zt_strHash(variable), value); }
void zt_shaderSetVariableTexCube(ztShaderVariableValues *shader_vars, const char *variable, ztTextureID value  ) { zt_shaderSetVariableTexCube(shader_vars, zt_strHash(variable), value); }

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableFloat(ztShaderVariableValues *shader_vars, u32 variable_hash, r32 value)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableFloat");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Float);
	shader_vars->variables[idx].val_float = value;
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableInt(ztShaderVariableValues *shader_vars, u32 variable_hash, i32 value)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableInt");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Int);
	shader_vars->variables[idx].val_int = value;
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableVec2(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztVec2& value)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableVec2");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Vec2);
	shader_vars->variables[idx].val_vec2[0] = value.values[0];
	shader_vars->variables[idx].val_vec2[1] = value.values[1];
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableVec3(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztVec3& value)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableVec3");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Vec3);
	shader_vars->variables[idx].val_vec3[0] = value.values[0];
	shader_vars->variables[idx].val_vec3[1] = value.values[1];
	shader_vars->variables[idx].val_vec3[2] = value.values[2];
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableVec4(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztVec4& value)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableVec4");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Vec4);
	shader_vars->variables[idx].val_vec4[0] = value.values[0];
	shader_vars->variables[idx].val_vec4[1] = value.values[1];
	shader_vars->variables[idx].val_vec4[2] = value.values[2];
	shader_vars->variables[idx].val_vec4[3] = value.values[3];
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableMat4(ztShaderVariableValues *shader_vars, u32 variable_hash, const ztMat4& value)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableMat4");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Mat4);
	zt_fiz(zt_elementsOf(value.values)) {
		shader_vars->variables[idx].val_mat4[i] = value.values[i];
	}
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableMat3(ztShaderVariableValues *shader_vars, u32 variable_hash, r32 value[12])
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableMat3");
	_zt_shaderCheckHashAndType(shader_vars, ztShaderVariable_Mat3);
	zt_fiz(12) {
		shader_vars->variables[idx].val_mat3[i] = value[i];
	}
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableTex(ztShaderVariableValues *shader_vars, u32 variable_hash, ztTextureID texture)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableTex");
	_zt_shaderCheckHash(shader_vars);
	if (shader_vars->variables[idx].type == ztShaderVariable_Tex || shader_vars->variables[idx].type == ztShaderVariable_TexCube) {
		shader_vars->variables[idx].val_tex = texture;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableTexCube(ztShaderVariableValues *shader_vars, u32 variable_hash, ztTextureID texture)
{
	ZT_PROFILE_RENDERING("zt_shaderSetVariableTexCube");
	_zt_shaderCheckHash(shader_vars);
	if (shader_vars->variables[idx].type == ztShaderVariable_Tex || shader_vars->variables[idx].type == ztShaderVariable_TexCube) {
		shader_vars->variables[idx].val_tex = texture;
	}
}

// ------------------------------------------------------------------------------------------------

#undef _zt_shaderCheckHash
#undef _zt_shaderCheckType
#undef _zt_shaderCheckHashAndType


#define _zt_shaderCheck(shader_id) \
	zt_assertReturnOnFail(shader_id >= 0 && shader_id < zt_game->shaders_count); \
	ztShaderVariableValues *shader_vars = &zt_game->shaders[shader_id].variables;

// ------------------------------------------------------------------------------------------------

bool zt_shaderHasVariable(ztShaderID shader_id, const char *variable, ztShaderVariable_Enum *type)
{
	ZT_PROFILE_RENDERING("zt_shaderHasVariable");
	zt_assertReturnValOnFail(shader_id >= 0 && shader_id < zt_game->shaders_count, false);
	return zt_shaderHasVariable(&zt_game->shaders[shader_id].variables, variable, type);
}

// ------------------------------------------------------------------------------------------------

bool zt_shaderHasVariable(ztShaderID shader_id, u32 variable_hash, ztShaderVariable_Enum *type)
{
	ZT_PROFILE_RENDERING("zt_shaderHasVariable");
	zt_assertReturnValOnFail(shader_id >= 0 && shader_id < zt_game->shaders_count, false);
	return zt_shaderHasVariable(&zt_game->shaders[shader_id].variables, variable_hash, type);
}

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableFloat  (ztShaderID shader_id, const char *variable, r32 value          ) { zt_shaderSetVariableFloat  (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableInt    (ztShaderID shader_id, const char *variable, i32 value          ) { zt_shaderSetVariableInt    (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableVec2   (ztShaderID shader_id, const char *variable, const ztVec2& value) { zt_shaderSetVariableVec2   (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableVec3   (ztShaderID shader_id, const char *variable, const ztVec3& value) { zt_shaderSetVariableVec3   (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableVec4   (ztShaderID shader_id, const char *variable, const ztVec4& value) { zt_shaderSetVariableVec4   (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableMat4   (ztShaderID shader_id, const char *variable, const ztMat4& value) { zt_shaderSetVariableMat4   (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableMat3   (ztShaderID shader_id, const char *variable, r32 value[12]      ) { zt_shaderSetVariableMat3   (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableTex    (ztShaderID shader_id, const char *variable, i32 value          ) { zt_shaderSetVariableTex    (shader_id, zt_strHash(variable), value); }
void zt_shaderSetVariableTexCube(ztShaderID shader_id, const char *variable, i32 value          ) { zt_shaderSetVariableTexCube(shader_id, zt_strHash(variable), value); }

// ------------------------------------------------------------------------------------------------

void zt_shaderSetVariableFloat  (ztShaderID shader_id, u32 variable_hash, r32 value          ) { _zt_shaderCheck(shader_id); zt_shaderSetVariableFloat  (shader_vars, variable_hash, value); }
void zt_shaderSetVariableInt    (ztShaderID shader_id, u32 variable_hash, i32 value          ) { _zt_shaderCheck(shader_id); zt_shaderSetVariableInt    (shader_vars, variable_hash, value); }
void zt_shaderSetVariableVec2   (ztShaderID shader_id, u32 variable_hash, const ztVec2& value) { _zt_shaderCheck(shader_id); zt_shaderSetVariableVec2   (shader_vars, variable_hash, value); }
void zt_shaderSetVariableVec3   (ztShaderID shader_id, u32 variable_hash, const ztVec3& value) { _zt_shaderCheck(shader_id); zt_shaderSetVariableVec3   (shader_vars, variable_hash, value); }
void zt_shaderSetVariableVec4   (ztShaderID shader_id, u32 variable_hash, const ztVec4& value) { _zt_shaderCheck(shader_id); zt_shaderSetVariableVec4   (shader_vars, variable_hash, value); }
void zt_shaderSetVariableMat4   (ztShaderID shader_id, u32 variable_hash, const ztMat4& value) { _zt_shaderCheck(shader_id); zt_shaderSetVariableMat4   (shader_vars, variable_hash, value); }
void zt_shaderSetVariableMat3   (ztShaderID shader_id, u32 variable_hash, r32 value[12]      ) { _zt_shaderCheck(shader_id); zt_shaderSetVariableMat3   (shader_vars, variable_hash, value); }
void zt_shaderSetVariableTex    (ztShaderID shader_id, u32 variable_hash, i32 value          ) { _zt_shaderCheck(shader_id); zt_shaderSetVariableTex    (shader_vars, variable_hash, value); }
void zt_shaderSetVariableTexCube(ztShaderID shader_id, u32 variable_hash, i32 value          ) { _zt_shaderCheck(shader_id); zt_shaderSetVariableTexCube(shader_vars, variable_hash, value); }

// ------------------------------------------------------------------------------------------------

ztShaderID zt_shaderGetDefault(ztShaderDefault_Enum shader_default)
{
	if (shader_default >= ztShaderDefault_Solid && shader_default < ztShaderDefault_MAX) {
		return shader_default;
	}

	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal void _zt_rendererTextureReload(ztAssetManager *asset_mgr, ztAssetID asset_id, void *user_id)
{
}

// ------------------------------------------------------------------------------------------------

ztInternal ztTextureID _zt_textureMakeBase(byte *pixel_data, i32 width, i32 height, i32 depth, i32 flags, const char **error)
{
	ZT_PROFILE_RENDERING("_zt_textureMakeBase");
	ztTextureID texture_id = zt_game->textures_count++;
	ztTexture *texture = &zt_game->textures[texture_id];

	texture->renderer = zt_currentRenderer();
	texture->width = width;
	texture->height = height;
	texture->flags = flags;

	switch (texture->renderer)
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			if (pixel_data) {
				texture->gl_texture = ztgl_textureMakeFromPixelData(pixel_data, width, height, depth, flags);
			}
			else {
				texture->gl_texture = ztgl_textureMakeRenderTarget(width, height, flags);
			}
			if (texture->gl_texture == nullptr) {
				zt_game->textures_count -= 1;
				return ztInvalidID;
			}
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			if (pixel_data) {
				texture->dx_texture = ztdx_textureMakeFromPixelData(zt_game->win_details[0].dx_context, pixel_data, width, height, depth, flags);
			}
			else {
				texture->dx_texture = ztdx_textureMakeRenderTarget(zt_game->win_details[0].dx_context, width, height, flags);
			}
			if (texture->dx_texture == nullptr) {
				zt_game->textures_count -= 1;
				return ztInvalidID;
			}
#			endif
		} break;
	}

	return texture_id;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMake(ztAssetManager *asset_mgr, ztAssetID asset_id, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_textureMake");
	ztBlockProfiler bp_tex("zt_textureMake (from asset)");

	zt_returnValOnNull(asset_mgr, ztInvalidID);
	zt_assertReturnValOnFail(asset_id >= 0 && asset_id < asset_mgr->asset_count, ztInvalidID);

	zt_logDebug("loading texture asset: %s", asset_mgr->asset_name[asset_id]);

	if (asset_mgr->asset_type[asset_id] != ztAssetManagerType_ImagePNG && asset_mgr->asset_type[asset_id] != ztAssetManagerType_ImageJPG) {
		return ztInvalidID;
	}

	i32 size = zt_assetSize(asset_mgr, asset_id);
	if (size <= 0) {
		return ztInvalidID;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		return ztInvalidID;
	}

	const char *error = nullptr;
	byte *pixel_data = nullptr;

	if (!zt_assetLoadData(asset_mgr, asset_id, data, size)) {
		error = "Unable to load asset contents";
		goto on_error;
	}

	int width, height, depth;
	{
		ztBlockProfiler bp_tex("stbi_load_from_memory");
		pixel_data = stbi_load_from_memory((const stbi_uc*)data, size, &width, &height, &depth, 4);
	}

	if (pixel_data == nullptr) {
		error = stbi_failure_reason();
		goto on_error;
	}

	ztTextureID texture_id = _zt_textureMakeBase(pixel_data, width, height, depth, flags, &error);

	if (texture_id != ztInvalidID) {
		ztTexture *texture = &zt_game->textures[texture_id];
		texture->load_type = ztTextureLoadType_Asset;
		texture->asset_mgr = asset_mgr;
		texture->asset_id = asset_id;

		zt_assetAddReloadCallback(asset_mgr, asset_id, _zt_rendererTextureReload, (void*)texture_id);
	}

	zt_free(data);
	stbi_image_free(pixel_data);
	return texture_id;

on_error:
	zt_logCritical("Unable to load texture (%s). %s.", asset_mgr->asset_name[asset_id], error);
	zt_free(data);
	if (pixel_data) {
		stbi_image_free(pixel_data);
	}
	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMake(byte *pixel_data, i32 width, i32 height, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_textureMake");
	ztBlockProfiler bp_tex("zt_textureMake (from dimensions)");

	zt_returnValOnNull(pixel_data, ztInvalidID);

	int depth = 4;
	const char *error = nullptr;
	ztTextureID texture_id = _zt_textureMakeBase(pixel_data, width, height, depth, flags, &error);
	if (texture_id != ztInvalidID) {
		ztTexture *texture = &zt_game->textures[texture_id];
		texture->load_type = ztTextureLoadType_Data;
		
		// we copy this so we can reload if necessary
		texture->arena = zt_memGetGlobalArena();
		texture->data_len = width * height * depth;
		texture->data = zt_mallocStructArray(byte, zt_game->textures[texture_id].data_len);
		zt_memCpy(texture->data, texture->data_len, pixel_data, texture->data_len);
	}
	else {
		zt_logCritical("Unable to load texture (%d x %d). %s.", width, height, error);
	}

	return texture_id;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMakeFromFile(const char *file, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_textureMakeFromFile");
	ztBlockProfiler bp_tex("zt_textureMake (from file)");

	i32 size = 0;
	void *data = zt_readEntireFile(file, &size);
	if (data == nullptr || size == 0) {
		return ztInvalidID;
	}

	ztTextureID tex_id = zt_textureMakeFromFileData(data, size, flags);

	zt_free(data);

	if (tex_id == ztInvalidID) {
		zt_logCritical("Unable to load texture (%s)", file);
	}

	return tex_id;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMakeFromFileData(void *data, i32 size, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_textureMakeFromFileData");
	ztBlockProfiler bp_tex("zt_textureMake (from file data)");

	const char *error = nullptr;

	int width, height, depth;
	byte *pixel_data = stbi_load_from_memory((const stbi_uc*)data, size, &width, &height, &depth, 4);

	if (pixel_data == nullptr) {
		error = stbi_failure_reason();
		goto on_error;
	}

	ztTextureID texture_id = _zt_textureMakeBase(pixel_data, width, height, depth, flags, &error);
	if (texture_id != ztInvalidID) {
		ztTexture *texture = &zt_game->textures[texture_id];
		texture->load_type = ztTextureLoadType_Data;

		// we copy this so we can reload if necessary
		texture->arena = zt_memGetGlobalArena();
		texture->data_len = width * height * depth;
		texture->data = zt_mallocStructArray(byte, texture->data_len);
		zt_memCpy(texture->data, texture->data_len, pixel_data, texture->data_len);
	}

	stbi_image_free(pixel_data);
	return texture_id;

on_error:
	zt_logCritical("Unable to load texture. %s.", error);
	if (pixel_data) {
		stbi_image_free(pixel_data);
	}
	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMakeFromPixelData(void *data, i32 width, i32 height, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_textureMakeFromPixelData");
	const char *error = nullptr;
	ztTextureID texture_id = _zt_textureMakeBase((byte*)data, width, height, 4, flags, &error);
	if (texture_id != ztInvalidID) {
		ztTexture *texture = &zt_game->textures[texture_id];
		texture->load_type = ztTextureLoadType_Data;

		// we copy this so we can reload if necessary
		texture->arena = zt_memGetGlobalArena();
		texture->data_len = width * height * 4;
		texture->data = zt_mallocStructArray(byte, zt_game->textures[texture_id].data_len);
		zt_memCpy(texture->data, texture->data_len, data, texture->data_len);
	}

	return texture_id;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMakeRenderTarget(i32 width, i32 height, i32 flags)
{
	ZT_PROFILE_RENDERING("zt_textureMakeRenderTarget");
	ztBlockProfiler bp_tex("zt_textureMakeRenderTarget");

	const char *error = nullptr;
	ztTextureID texture_id = _zt_textureMakeBase(nullptr, width, height, 4, flags, &error);
	if (texture_id != ztInvalidID) {
		zt_game->textures[texture_id].load_type = ztTextureLoadType_RenderTarget;
	}

	return texture_id;
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMakeCubeMap(ztAssetManager *asset_mgr, const char *asset_format)
{
	ZT_PROFILE_RENDERING("zt_textureMakeCubeMap");
	ztAssetID asset_ids[ztTextureCubeMapFiles_MAX];

	char asset_name[1024];

	const char *names[ztTextureCubeMapFiles_MAX] = { "right", "left", "top", "bottom", "back", "front" };

	zt_fiz(ztTextureCubeMapFiles_MAX) {
		zt_strPrintf(asset_name, zt_elementsOf(asset_name), asset_format, names[i]);
		asset_ids[i] = zt_assetLoad(asset_mgr, asset_name);
	}

	return zt_textureMakeCubeMap(asset_mgr, asset_ids);
}

// ------------------------------------------------------------------------------------------------

ztTextureID zt_textureMakeCubeMap(ztAssetManager *asset_mgr, ztAssetID files[ztTextureCubeMapFiles_MAX])
{
	ZT_PROFILE_RENDERING("zt_textureMakeCubeMap");
	ztBlockProfiler bp_tex("zt_textureMakeCubeMap");

	zt_returnValOnNull(asset_mgr, ztInvalidID);

	byte *tex_data[ztTextureCubeMapFiles_MAX];
	int tex_size[ztTextureCubeMapFiles_MAX];

	zt_fiz(ztTextureCubeMapFiles_MAX) {
		ztAssetID asset_id = files[i];
		zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);
		if (asset_mgr->asset_type[asset_id] != ztAssetManagerType_ImagePNG && asset_mgr->asset_type[asset_id] != ztAssetManagerType_ImageJPG) {
			return ztInvalidID;
		}

		tex_size[i] = zt_assetSize(asset_mgr, asset_id);
		if (tex_size[i] <= 0) {
			return ztInvalidID;
		}

		tex_data[i] = zt_mallocStructArray(byte, tex_size[i]);
		if (!tex_data[i]) {
			return ztInvalidID;
		}

		if (!zt_assetLoadData(asset_mgr, asset_id, tex_data[i], tex_size[i])) {
			zt_logCritical("Unable to load image asset: %s", asset_mgr->asset_name[asset_id]);
			zt_fjzr(i) zt_free(tex_data[j]);
			return ztInvalidID;
		}
	}

	int width, height, depth;
	byte *pixel_data[ztTextureGLCubeMapFiles_MAX];
	zt_fiz(ztTextureGLCubeMapFiles_MAX) {
		pixel_data[i] = stbi_load_from_memory((const stbi_uc*)tex_data[i], tex_size[i], &width, &height, &depth, 4);
	}

	ztTextureID texture_id = zt_game->textures_count++;
	ztTexture *texture = &zt_game->textures[texture_id];

	texture->renderer = zt_currentRenderer();
	switch (texture->renderer)
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			texture->gl_texture = ztgl_textureMakeCubeMapFromPixelData(pixel_data, width, height, depth);
			if (texture->gl_texture == nullptr) {
				zt_game->textures_count--;
				return ztInvalidID;
			}
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			texture->dx_texture = ztdx_textureMakeCubeMapFromPixelData(zt_game->win_details[0].dx_context, pixel_data, width, height, depth);
			if (texture->dx_texture == nullptr) {
				zt_game->textures_count--;
				return ztInvalidID;
			}
#			endif
		} break;
	}

	texture->width  = width;
	texture->height = height;
	texture->flags  = 0;

	zt_fiz(ztTextureCubeMapFiles_MAX) {
		stbi_image_free(pixel_data[i]);
		zt_free(tex_data[i]);
	}

	return texture_id;
}

// ------------------------------------------------------------------------------------------------

void zt_textureFree(ztTextureID texture_id)
{
	ZT_PROFILE_RENDERING("zt_textureFree");
	if (zt_game->textures[texture_id].renderer == ztRenderer_Invalid) {
		return;
	}

	if (zt_game->textures[texture_id].renderer == ztRenderer_OpenGL) {
#		if defined(ZT_OPENGL)
		ztgl_textureFree(zt_game->textures[texture_id].gl_texture);
		zt_game->textures[texture_id].gl_texture = nullptr;
#		endif // ZT_OPENGL
	}
	else if (zt_game->textures[texture_id].renderer == ztRenderer_DirectX) {
#		if defined(ZT_DIRECTX)
		ztdx_textureFree(zt_game->textures[texture_id].dx_texture);
		zt_game->textures[texture_id].dx_texture = nullptr;
#		endif // ZT_DIRECTX
	}

	if (zt_game->textures[texture_id].load_type == ztTextureLoadType_Data) {
		zt_freeArena(zt_game->textures[texture_id].data, zt_game->textures[texture_id].arena);
	}
	zt_memSet(&zt_game->textures[texture_id], sizeof(ztTexture), 0);
}

// ------------------------------------------------------------------------------------------------

void zt_textureRenderTargetPrepare(ztTextureID texture_id)
{
	ZT_PROFILE_RENDERING("zt_textureRenderTargetPrepare");
	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
			zt_openGLSupport(ztgl_textureRenderTargetPrepare(zt_game->textures[texture_id].gl_texture));
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_textureRenderTargetPrepare(zt_game->win_details[0].dx_context, zt_game->textures[texture_id].dx_texture));
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_textureRenderTargetCommit(ztTextureID texture_id)
{
	ZT_PROFILE_RENDERING("zt_textureRenderTargetCommit");
	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
			zt_openGLSupport(ztgl_textureRenderTargetCommit(zt_game->textures[texture_id].gl_texture, zt_game->win_details[0].gl_context));
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_textureRenderTargetCommit(zt_game->win_details[0].dx_context, zt_game->textures[texture_id].dx_texture));
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

ztPoint2 zt_textureGetSize(ztTextureID texture_id)
{
	ZT_PROFILE_RENDERING("zt_textureGetSize");
	zt_assertReturnValOnFail(texture_id >= 0 && texture_id < zt_game->textures_count, ztPoint2(0,0));
	return ztPoint2(zt_game->textures[texture_id].width, zt_game->textures[texture_id].height);
}

// ------------------------------------------------------------------------------------------------

void zt_alignToPixel(r32 *val, r32 ppu, r32 *offset)
{
	ZT_PROFILE_RENDERING("zt_alignToPixel");
#if 1
	r32 abval = zt_abs(*val *ppu);
	r32 rem = abval - zt_convertToi32Floor(abval);
//	r32 rem = zt_abs(*val *ppu) - zt_convertToi32Floor(zt_abs(*val *ppu));
	//if (rem >= .375f && rem <= .625f) {
	if (rem >= .25f && rem < .75f) {
		if (*val >= 0) {
			*val = zt_convertToi32Floor((*val * ppu)) / ppu;
			if (offset) *offset += rem / ppu;
		}
		else {
			*val = zt_convertToi32Ceil((*val * ppu)) / ppu;
			if (offset) *offset += (1.f - rem) / ppu;
		}
	}
#else
	r32 abval = zt_abs(*val * ppu);
	r32 rem = abval - zt_convertToi32Floor(abval);

	r32 nval = zt_convertToi32Floor(((*val) * ppu)) / ppu;
	if(offset) *offset = rem / ppu;
	*val = nval;
#endif
}

// ------------------------------------------------------------------------------------------------

void zt_alignToPixel(ztVec2 *val, r32 ppu)
{
	zt_alignToPixel(&val->x, ppu);
	zt_alignToPixel(&val->y, ppu);
}

// ------------------------------------------------------------------------------------------------

void zt_alignToPixel(ztVec3 *val, r32 ppu)
{
	zt_alignToPixel(&val->x, ppu);
	zt_alignToPixel(&val->y, ppu);
	zt_alignToPixel(&val->z, ppu);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void zt_cameraMakeOrtho(ztCamera *camera, i32 width, i32 height, i32 native_w, i32 native_h, r32 near_z, r32 far_z, const ztVec3& position)
{
	ZT_PROFILE_RENDERING("zt_cameraMakeOrtho");
	zt_returnOnNull(camera);

	camera->type = ztCameraType_Orthographic;
	camera->width = width;
	camera->height = height;
	camera->native_w = native_w;
	camera->native_h = native_h;
	camera->zoom = 1;
	camera->near_z = near_z;
	camera->far_z = far_z;
	camera->position = position;

	r32 aspect_w = native_w > native_h ? native_w / (r32)native_h : 1.f;
	r32 aspect_h = native_w > native_h ? 1.f : native_h / (r32)native_w;

	r32 scale = (zt_min(width, height) / (r32)zt_game->win_game_settings[0].pixels_per_unit) / 2;
	aspect_w *= scale;
	aspect_h *= scale;

	camera->mat_proj = ztMat4::makeOrthoProjection(-aspect_w, aspect_w, aspect_h, -aspect_h, near_z, far_z);
	camera->mat_view = ztMat4::identity;
}

// ------------------------------------------------------------------------------------------------

void zt_cameraMakePersp(ztCamera *camera, i32 width, i32 height, r32 fov, r32 near_z, r32 far_z, const ztVec3& position, const ztQuat& rotation)
{
	ZT_PROFILE_RENDERING("zt_cameraMakePersp");
	zt_returnOnNull(camera);

	camera->width = width;
	camera->height = height;
	camera->type = ztCameraType_Perspective;
	camera->fov = fov;
	camera->near_z = near_z;
	camera->far_z = far_z;
	camera->position = position;
	camera->rotation = rotation;
	camera->direction = ztVec3::zero;

	camera->mat_proj = ztMat4::makePerspectiveProjection(fov, (r32)width, (r32)height, near_z, far_z);
}

// ------------------------------------------------------------------------------------------------

void zt_cameraRecalcMatrices(ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraRecalcMatrices");
	zt_returnOnNull(camera);

	if (camera->type == ztCameraType_Orthographic) {
		camera->mat_view = ztMat4::identity.getTranslate(camera->position);
	}
	else if (camera->type == ztCameraType_Perspective) {
		camera->mat_view = camera->rotation.convertToMat4();
		camera->mat_view *= ztMat4::identity.getTranslate(camera->position).getInverse();
		
		ztMat4 mat_final = camera->mat_proj * camera->mat_view;
		camera->direction = ztVec3(mat_final.values[2], mat_final.values[6], mat_final.values[10]).getNormal();
	}
	else {
		zt_assert(false && "Invalid camera type");
	}
}

// ------------------------------------------------------------------------------------------------

void zt_cameraCalcFinalMatrix(ztCamera *camera, ztMat4* final_mat)
{
	ZT_PROFILE_RENDERING("zt_cameraCalcFinalMatrix");
	zt_returnOnNull(camera);
	zt_returnOnNull(final_mat);

	if (camera->type == ztCameraType_Orthographic) {
		ztMat4 temp = camera->mat_proj * camera->mat_view;
		ztMat4 zoom = ztMat4(camera->zoom, 0, 0, 0, 0, camera->zoom, 0, 0, 0, 0, camera->zoom, 0, 0, 0, 0, camera->zoom);

		*final_mat = temp * zoom;
	}
	else if (camera->type == ztCameraType_Perspective) {
		*final_mat = camera->mat_proj * camera->mat_view;
	}
	else {
		zt_assert(false && "Invalid camera type");
	}
}

// ------------------------------------------------------------------------------------------------

void zt_cameraSetMatrices(ztCamera *camera, ztMat4& proj, ztMat4& view)
{
	ZT_PROFILE_RENDERING("zt_cameraSetMatrices");
	zt_returnOnNull(camera);

	camera->mat_proj = proj;
	camera->mat_view = view;

	ztMat4 mat_final = camera->mat_proj * camera->mat_view;
	camera->direction = ztVec3(mat_final.values[2], mat_final.values[6], mat_final.values[10]).getNormal();

	//mat_final.inverse();

	ztVec3 rot;
	view.extract(&camera->position, &rot, nullptr);

	camera->rotation = ztQuat::makeFromEuler(rot);
}

// ------------------------------------------------------------------------------------------------

void zt_cameraOrthoGetExtents(ztCamera *camera, ztVec2 *min_ext, ztVec2 *max_ext)
{
	ZT_PROFILE_RENDERING("zt_cameraOrthoGetExtents");
	zt_returnOnNull(min_ext);
	zt_returnOnNull(max_ext);

	ztVec2 size = zt_cameraOrthoGetViewportSize(camera);
	min_ext->x = size.x / -2;
	min_ext->y = size.y / -2;
	max_ext->x = size.x / 2;
	max_ext->y = size.y / 2;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_cameraOrthoGetMaxExtent(ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraOrthoGetMaxExtent");
	ztVec2 ext = zt_cameraOrthoGetViewportSize(camera);
	ext.x /= 2;
	ext.y /= 2;
	return ext;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_cameraOrthoGetMinExtent(ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraOrthoGetMinExtent");
	ztVec2 ext = zt_cameraOrthoGetViewportSize(camera);
	ext.x /= -2;
	ext.y /= -2;
	return ext;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_cameraOrthoGetViewportSize(ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraOrthoGetViewportSize");
	zt_returnValOnNull(camera, ztVec2::zero);
	
	if (camera->type != ztCameraType_Orthographic) {
		return ztVec2::zero;
	}

	return ztVec2(camera->width / (r32)zt_game->win_game_settings[0].pixels_per_unit, camera->height / (r32)zt_game->win_game_settings[0].pixels_per_unit);
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_cameraOrthoScreenToWorld(ztCamera *camera, int sx, int sy)
{
	ZT_PROFILE_RENDERING("zt_cameraOrthoScreenToWorld");
	zt_returnValOnNull(camera, ztVec2::zero);

	if (camera->type != ztCameraType_Orthographic) {
		return ztVec2::zero;
	}

	r32 spct_x = camera->width / (r32)camera->native_w;
	r32 spct_y = camera->height / (r32)camera->native_h;
	r32 x = (sx - (camera->width / 2.0f)) / zt_game->win_game_settings[0].pixels_per_unit / (camera->zoom * spct_x);
	r32 y = (sy - (camera->height / 2.0f)) / zt_game->win_game_settings[0].pixels_per_unit * -1 / (camera->zoom * spct_y);

	return ztVec2(x + camera->position.x, y + camera->position.y);
}

// ------------------------------------------------------------------------------------------------

ztPoint2 zt_cameraOrthoWorldToScreen(ztCamera *camera, ztVec2& pos)
{
	ZT_PROFILE_RENDERING("zt_cameraOrthoWorldToScreen");
	zt_returnValOnNull(camera, ztPoint2(0,0));

	if (camera->type != ztCameraType_Orthographic) {
		return ztPoint2(0,0);
	}

	r32 ppu = (r32)zt_game->win_game_settings[0].pixels_per_unit;
	ztVec2 diff = pos - camera->position.xy;

	r32 x = (diff.x + ((camera->width / ppu) / 2.f)) * ppu;
	r32 y = (((camera->height / ppu) / 2) + diff.y) * ppu;

	return ztPoint2(x < 0 ? zt_convertToi32Floor(x) : zt_convertToi32Ceil(x),
					y < 0 ? zt_convertToi32Floor(y) : zt_convertToi32Ceil(y));
}

// ------------------------------------------------------------------------------------------------

void zt_cameraPerspGetMouseRay(ztCamera *camera, int sx, int sy, ztVec3 *point, ztVec3 *direction)
{
	ZT_PROFILE_RENDERING("zt_cameraPerspGetMouseRay");
	r32 x = zt_linearRemap((r32)sx, 0.f, (r32)camera->width , -1, 1);
	r32 y = zt_linearRemap((r32)sy, 0.f, (r32)camera->height, 1, -1);

	r32 near_height = zt_tan(camera->fov / 2.f) * camera->near_z;
	r32 far_height = zt_tan(camera->fov / 2.f) * camera->far_z;

	r32 aspect = (r32)camera->width / (r32)camera->height;
	r32 near_width = near_height * aspect;
	r32 far_width = far_height * aspect;

	ztVec3 pos_near(near_width * x, near_height * y, -camera->near_z);
	ztVec3 pos_far(far_width * x, far_height * y, -camera->far_z);

	ztMat4 inv_view = camera->mat_view.getInverse();
	pos_near = inv_view * pos_near;
	pos_far  = inv_view * pos_far;

	*point = pos_near;
	*direction = pos_far - pos_near;
	direction->normalize();
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztCameraShake zt_cameraShakeMake(r32 duration, r32 speed, r32 intensity, i32 seed)
{
	ZT_PROFILE_RENDERING("zt_cameraShakeMake");
	ztCameraShake camera_shake;
	zt_memSet(&camera_shake, zt_sizeof(ztCameraShake), 0);

	zt_randomInit(&camera_shake.randomizer, seed);

	camera_shake.duration = duration;
	camera_shake.frequency = 60 * speed; // hertz
	camera_shake.amplitude = 16 * intensity / zt_pixelsPerUnit(); // units
	camera_shake.sample_count = zt_min(CAMERA_SHAKE_MAX_SAMPLES - 1, (int)camera_shake.frequency);

	zt_fiz(camera_shake.sample_count) {
		camera_shake.samples_x[i] = zt_randomVal(&camera_shake.randomizer) * 2.0f - 1.0f;
		camera_shake.samples_y[i] = zt_randomVal(&camera_shake.randomizer) * 2.0f - 1.0f;
	}
	camera_shake.samples_x[camera_shake.sample_count] = 0;
	camera_shake.samples_y[camera_shake.sample_count] = 0;

	return camera_shake;
}

// ------------------------------------------------------------------------------------------------

void zt_cameraShakeStart(ztCameraShake *camera_shake)
{
	ZT_PROFILE_RENDERING("zt_cameraShakeStart");
	zt_returnOnNull(camera_shake);
	camera_shake->current_time = camera_shake->duration;
}

// ------------------------------------------------------------------------------------------------

void zt_cameraShakeUpdate(ztCameraShake *camera_shake, r32 dt)
{
	ZT_PROFILE_RENDERING("zt_cameraShakeUpdate");
	zt_returnOnNull(camera_shake);

	if (camera_shake->current_time > 0) {
		camera_shake->current_time -= dt;
		if (camera_shake->current_time > 0) {
			r32 percent = 1 - camera_shake->current_time / camera_shake->duration;
			r32 frequency = percent * camera_shake->frequency;

			r32 sample_x       = frequency;
			i32 sample_x_idx_0 = zt_convertToi32Floor(sample_x);
			i32 sample_x_idx_1 = sample_x_idx_0 + 1;
			r32 amplitude_x    = (camera_shake->samples_x[sample_x_idx_0] + (sample_x - sample_x_idx_0) * (camera_shake->samples_x[sample_x_idx_1] - camera_shake->samples_x[sample_x_idx_0])) * (1 - percent);

			r32 sample_y       = frequency;
			i32 sample_y_idx_0 = zt_convertToi32Floor(sample_y);
			i32 sample_y_idx_1 = sample_y_idx_0 + 1;
			r32 amplitude_y    = (camera_shake->samples_y[sample_y_idx_0] + (sample_y - sample_y_idx_0) * (camera_shake->samples_y[sample_y_idx_1] - camera_shake->samples_y[sample_y_idx_0])) * (1 - percent);

			camera_shake->offset.x = amplitude_x * camera_shake->amplitude;
			camera_shake->offset.y = amplitude_y * camera_shake->amplitude;
		}
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_cameraShakePreRender(ztCameraShake *camera_shake, ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraShakePreRender");
	zt_returnValOnNull(camera_shake, false);
	zt_returnValOnNull(camera, false);

	if (camera_shake->current_time <= 0) {
		return false;
	}

	camera_shake->original_position = camera->position;
	camera->position.x += camera_shake->offset.x;
	camera->position.y += camera_shake->offset.y;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_cameraShakePostRender(ztCameraShake *camera_shake, ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraShakePostRender");
	zt_returnValOnNull(camera_shake, false);
	zt_returnValOnNull(camera, false);

	if (camera_shake->current_time <= 0) {
		return false;
	}

	camera->position = camera_shake->original_position;

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_cameraShakePreRender(ztCameraShake *camera_shake, ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_cameraShakePreRender");
	zt_returnOnNull(camera_shake);
	zt_returnOnNull(draw_list);

	zt_drawListPushOffset(draw_list, ztVec3(camera_shake->offset, 0));
}

// ------------------------------------------------------------------------------------------------

void zt_cameraShakePostRender(ztCameraShake *camera_shake, ztDrawList *draw_list)
{
	ZT_PROFILE_RENDERING("zt_cameraShakePostRender");
	zt_returnOnNull(camera_shake);
	zt_returnOnNull(draw_list);

	zt_drawListPopOffset(draw_list);
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztCameraControllerFPS zt_cameraControllerMakeFPS(ztCamera *camera, ztVec3 initial_rotation)
{
	ZT_PROFILE_RENDERING("zt_cameraControllerMakeFPS");
	ztCameraControllerFPS controller;
	zt_memSet(&controller, zt_sizeof(ztCameraControllerFPS), 0);

	controller.camera = camera;
	controller.mouse_sensitivity = 0.05f;
	controller.speed = 10.f;
	controller.boosted_speed = 30.f;
	controller.sneaking_speed = 2.f;

	controller.rotation = initial_rotation;
	controller.camera->rotation = ztQuat::makeFromEuler(controller.rotation.x, 0, 0);
	controller.camera->rotation *= ztQuat::makeFromEuler(0, controller.rotation.y, 0);
	zt_cameraRecalcMatrices(controller.camera);

	return controller;
}

// ------------------------------------------------------------------------------------------------

void zt_cameraControlUpdateFPS(ztCameraControllerFPS *controller, r32 dt)
{
	ZT_PROFILE_RENDERING("zt_cameraControlUpdateFPS");
	zt_returnOnNull(controller);

	bool cam_moved = false;

	if (controller->mouse_delta_x != 0 || controller->mouse_delta_y != 0) {
		cam_moved = true;

		r32 delta_x = controller->mouse_delta_x * controller->mouse_sensitivity;
		r32 delta_y = controller->mouse_delta_y * controller->mouse_sensitivity;

		controller->rotation.y += delta_x;
		if (controller->rotation.x <   0) controller->rotation.y += 360;
		if (controller->rotation.x > 360) controller->rotation.y -= 360;

		controller->rotation.x = zt_clamp(controller->rotation.x + delta_y, -89, 89);

		controller->camera->rotation = ztQuat::makeFromEuler(controller->rotation.x, 0, 0);
		controller->camera->rotation *= ztQuat::makeFromEuler(0, controller->rotation.y, 0);
	}

	r32 movement_speed = controller->is_boosted ? controller->boosted_speed : (controller->is_sneaking ? controller->sneaking_speed : controller->speed);

	ztVec3 movement_velocity = controller->velocity;

	bool moved_x = false, moved_z = false;
	if (controller->move_forward) { movement_velocity.z = zt_approach(movement_velocity.z, -1, 2 * dt); moved_z = true; }
	if (controller->move_back   ) { movement_velocity.z = zt_approach(movement_velocity.z, +1, 2 * dt); moved_z = true; }
	if (controller->strafe_left ) { movement_velocity.x = zt_approach(movement_velocity.x, -1, 2 * dt); moved_x = true; }
	if (controller->strafe_right) { movement_velocity.x = zt_approach(movement_velocity.x, +1, 2 * dt); moved_x = true; }

	if (!moved_z && movement_velocity.z != 0) { movement_velocity.z = zt_approach(movement_velocity.z, 0, 4.75f * dt); }
	if (!moved_x && movement_velocity.x != 0) { movement_velocity.x = zt_approach(movement_velocity.x, 0, 4.75f * dt); }

	controller->velocity = movement_velocity;

	if (movement_velocity != ztVec3::zero) {
		cam_moved = true;
		if (movement_velocity.z != 0) {
			r32 z_move = -1 * movement_velocity.z * movement_speed * dt;
			controller->camera->position.x += controller->camera->direction.x * z_move;
			controller->camera->position.y += controller->camera->direction.y * z_move;
			controller->camera->position.z += controller->camera->direction.z * z_move;
		}
		if (movement_velocity.x != 0) {
			ztVec3 side = ztVec3(0, 1, 0).cross(controller->camera->direction);
			side.normalize();

			r32 x_move = -1 * movement_velocity.x * movement_speed * dt;

			controller->camera->position.x += side.x * x_move;
			controller->camera->position.y += side.y * x_move;
			controller->camera->position.z += side.z * x_move;
		}
	}

	if (cam_moved) {
		zt_cameraRecalcMatrices(controller->camera);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_cameraControlUpdateWASD(ztCameraControllerFPS *camera, ztInputMouse *input_mouse, ztInputKeys *input_keys, r32 dt)
{
	ZT_PROFILE_RENDERING("zt_cameraControlUpdateWASD");
	zt_returnOnNull(camera);

	camera->mouse_delta_x = (r32)input_mouse->delta_x;
	camera->mouse_delta_y = (r32)input_mouse->delta_y;

	camera->move_forward = input_keys[ztInputKeys_W].pressed() ? 1.f : 0.f;
	camera->move_back    = input_keys[ztInputKeys_S].pressed() ? 1.f : 0.f;
	camera->strafe_left  = input_keys[ztInputKeys_A].pressed() ? 1.f : 0.f;
	camera->strafe_right = input_keys[ztInputKeys_D].pressed() ? 1.f : 0.f;

	camera->is_boosted  = input_keys[ztInputKeys_Control].pressed();
	camera->is_sneaking = input_keys[ztInputKeys_Shift].pressed();

	zt_cameraControlUpdateFPS(camera, dt);
}

// ------------------------------------------------------------------------------------------------

ztFrustum zt_cameraCalcViewFrustum(ztCamera *camera)
{
	ZT_PROFILE_RENDERING("zt_cameraCalcViewFrustum");
	ztVec3 near_center(0, 0, -camera->near_z);
	ztVec3 far_center(0, 0, -camera->far_z);

	r32 near_half_height = zt_tan(camera->fov / 2.f) * camera->near_z;
	r32 far_half_height = zt_tan(camera->fov / 2.f) * camera->far_z;

	r32 aspect = (r32)camera->width / (r32)camera->height;

	r32 near_half_width = near_half_height * aspect;
	r32 far_half_width = far_half_height * aspect;
	
	ztFrustum results;
	results.near_nw = ztVec3(near_center.x - near_half_width, near_center.y + near_half_height, near_center.z);
	results.near_ne = ztVec3(near_center.x + near_half_width, near_center.y + near_half_height, near_center.z);
	results.near_se = ztVec3(near_center.x + near_half_width, near_center.y - near_half_height, near_center.z);
	results.near_sw = ztVec3(near_center.x - near_half_width, near_center.y - near_half_height, near_center.z);

	results.far_nw = ztVec3(far_center.x - far_half_width, far_center.y + far_half_height, far_center.z);
	results.far_ne = ztVec3(far_center.x + far_half_width, far_center.y + far_half_height, far_center.z);
	results.far_se = ztVec3(far_center.x + far_half_width, far_center.y - far_half_height, far_center.z);
	results.far_sw = ztVec3(far_center.x - far_half_width, far_center.y - far_half_height, far_center.z);

	ztMat4 cam_view_inv = camera->mat_view.getInverse();
	zt_fiz(8) {
		results.points[i] = cam_view_inv * results.points[i];
	}

	return results;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

const char *zt_fontGetCharsetStandard(i32 *size)
{
	zt_returnValOnNull(size, nullptr);

	char *charset = " !\"#$%&'()*+'-.,/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	*size = zt_strLen(charset);
	return charset;
}

// ------------------------------------------------------------------------------------------------

ztFontID _zt_fontMakeFromSTB(const char *name, void *data, i32 data_size, i32 size_in_pixels, const char *charset, i32 charset_size); // defined after stb_truetype.h below

// ------------------------------------------------------------------------------------------------

ztFontID zt_fontMakeFromTrueTypeAsset(ztAssetManager *asset_mgr, ztAssetID asset_id, i32 size_in_pixels, const char *charset, i32 charset_size)
{
	ZT_PROFILE_RENDERING("zt_fontMakeFromTrueTypeAsset");
	if (charset == nullptr || charset_size == 0) {
		charset = zt_fontGetCharsetStandard(&charset_size);
	}

	void *data = nullptr;
	i32 size = 0;

	ztAssetManagerType_Enum verify[] = { ztAssetManagerType_Font };
	if (!_zt_assetLoadData(asset_mgr, asset_id, verify, zt_elementsOf(verify), &data, &size)) {
		return ztInvalidID;
	}

	ztFontID font_id = _zt_fontMakeFromSTB(asset_mgr->asset_name[asset_id], data, size, size_in_pixels, charset, charset_size);
	zt_free(data);
	return font_id;
}

// ------------------------------------------------------------------------------------------------

ztFontID zt_fontMakeFromTrueTypeFile(const char *file_name, i32 size_in_pixels, const char *charset, i32 charset_size)
{
	ZT_PROFILE_RENDERING("zt_fontMakeFromTrueTypeFile");
	if (charset == nullptr || charset_size == 0) {
		if (charset) {
			charset_size = zt_strLen(charset);
		}
		else {
			charset = zt_fontGetCharsetStandard(&charset_size);
		}
	}

	i32 size = 0;
	void *data = zt_readEntireFile(file_name, &size);

	if (data == nullptr || size == 0) {
		return ztInvalidID;
	}

	const char *last = zt_strFindLast(file_name, ztFilePathSeparatorStr);
	if (last == nullptr) {
		last = file_name;
	}
	else {
		last += 1;
	}

	ztFontID font_id = _zt_fontMakeFromSTB(last, data, size, size_in_pixels, charset, charset_size);
	zt_free(data);
	return font_id;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztFontID _zt_fontMakeFromBmpFontBase(ztAssetManager *asset_mgr, ztAssetID asset_id, ztAssetID texture_override_asset_id, const char *font_data, ztTextureID texture_override_tex_id, const ztVec2& override_offset)
{
	ZT_PROFILE_RENDERING("_zt_fontMakeFromBmpFontBase");
	void *data = nullptr;
	i32 size = 0;
	ztVec2 offset = override_offset;
	
	if (asset_mgr) {
		ztAssetManagerType_Enum verify[] = { ztAssetManagerType_Font };
		if (!_zt_assetLoadData(asset_mgr, asset_id, verify, zt_elementsOf(verify), &data, &size)) {
			return ztInvalidID;
		}
	}
	else {
		data = (void*)font_data;
		size = zt_strSize(font_data);
	}

	ztFontID font_id = ztInvalidID;
	const char *error = nullptr;

	ztToken lines_tok[2048];
	int lines = zt_strTokenize((char*)data, "\r\n", lines_tok, zt_elementsOf(lines_tok), 0);
	if (lines < 4) {
		error = "bitmap font file has an invalid header";
		goto on_error;
	}
	if (lines > zt_elementsOf(lines_tok)) {
		error = "font glyph count exceeds maximum supported";
		goto on_error;
	}

	font_id = zt_game->fonts_count++;
	ztFont *font = &zt_game->fonts[font_id];

	zt_memSet(font, zt_sizeof(ztFont), 0);

	if (asset_mgr) {
		font->arena = asset_mgr->arena;
		font->texture = texture_override_asset_id;
	}
	else {
		font->arena = zt_memGetGlobalArena();
		font->texture = texture_override_tex_id;
	}

	struct local
	{
		static int32 getIntAfterEquals(char* str, int len)
		{
			int idx = 0;
			while (str[idx]) {
				if (str[idx] != '=') {
					idx++;
				}
				else {
					idx++;
					int str_len = len - idx;
					char buffer[128] = { 0 };
					zt_strCpy(buffer, zt_elementsOf(buffer), &str[idx], str_len);

					i32 result = zt_strToInt(buffer, 0);
					return result;
				}
			}
			return 0;
		}
	};

	char line_buff[1024];

	int chars = 0;
	int chars_line = 0;
	int base = 0;

	zt_fiz(lines) {
		if (lines_tok[i].len >= zt_elementsOf(line_buff)) {
			continue;
		}

		zt_strCpy(line_buff, zt_elementsOf(line_buff), (char*)data + lines_tok[i].beg, lines_tok[i].len);
		line_buff[lines_tok[i].len] = 0;

		if (zt_strStartsWith(line_buff, "info face")) {
		}

		if (zt_strStartsWith(line_buff, "char id")) {
			if (chars_line == 0) {
				chars_line = i;
				break;
			}
		}
		else {
			ztToken toks[32];
			int toks_cnt = zt_strTokenize(line_buff, " ", toks, zt_elementsOf(toks), ztStrTokenizeFlags_ProcessQuotes | ztStrTokenizeFlags_KeepQuotes);
			if (toks_cnt > zt_elementsOf(toks)) {
				continue;
			}

			zt_fjz(toks_cnt) {
				char* start = line_buff + toks[j].beg;
				if (zt_strStartsWith(start, "face=")) {
					int find_beg = 5;
					int find_end = -1;
					if (start[find_beg] == '\"') {
						find_beg += 1;
						find_end = zt_strFindPos(start, "\"", find_beg);
					}
					else {
						find_end = zt_strFindPos(start, " ", find_beg);
					}

					if (find_end != ztStrPosNotFound) {
						zt_strCpy(font->name, zt_elementsOf(font->name), start + find_beg, find_end - find_beg);
					}
				}
				else if (zt_strStartsWith(start, "size=")) {
					font->size_pixels = local::getIntAfterEquals(start, toks[j].len);
				}
				else if (zt_strStartsWith(start, "lineHeight=")) {
					font->line_height = local::getIntAfterEquals(start, toks[j].len) / (r32)zt_game->win_game_settings[0].pixels_per_unit;
				}
				else if (zt_strStartsWith(start, "base=")) {
					base = local::getIntAfterEquals(start, toks[j].len);
				}
				else if (zt_strStartsWith(start, "count=") && zt_strStartsWith(line_buff, "chars count")) {
					chars = local::getIntAfterEquals(start, toks[j].len);
				}
				else if (zt_strStartsWith(start, "pages=")) {
					int pages = local::getIntAfterEquals(start, toks[j].len);
					if (pages != 1) {
						error = "bitmap fonts with more than one page are not supported";
						goto on_error;
					}
				}
				else if (zt_strStartsWith(start, "file=")) {
					if (font->texture == ztInvalidID) {
						char tex_file[ztFileMaxPath];
						if (zt_strStartsWith(start, "file=\"")) {
							zt_strCpy(tex_file, zt_elementsOf(tex_file), start + 6, toks[j].len - 7);
						}
						else {
							zt_strCpy(tex_file, zt_elementsOf(tex_file), start + 5, toks[j].len - 5);
						}

						char bmp_dir[ztFileMaxPath] = "";
						int pos_sep = zt_strFindLastPos(asset_mgr->asset_name[asset_id], "/");
						if (pos_sep != ztStrPosNotFound) {
							zt_strCpy(bmp_dir, zt_elementsOf(bmp_dir), asset_mgr->asset_name[asset_id], pos_sep);
						}
						
						char tex_file_full[ztFileMaxPath];
						zt_strPrintf(tex_file_full, zt_elementsOf(tex_file_full), "%s/%s", bmp_dir, tex_file);
						i32 tex_asset_hash = 0;
						if (zt_assetFileExistsAsAsset(asset_mgr, tex_file_full, &tex_asset_hash)) {
							font->texture = zt_textureMake(asset_mgr, zt_assetLoad(asset_mgr, tex_asset_hash), 0);
						}
						else if (zt_fileExists(tex_file_full)) {
							// TODO(josh): should this support loading non-asset files?
							zt_assert(false);
						}
						else {
							zt_assert(false);
						}

						if (font->texture == ztInvalidID) {
							error = "unable to load bitmap font texture";
							goto on_error;
						}
					}
				}
			}
		}
	}

	font->glyph_count = chars;
	font->glyph_code_point = zt_mallocStructArrayArena(i32, chars, font->arena);
	font->glyphs = zt_mallocStructArrayArena(ztFont::ztGlyph, chars, font->arena);

	r32 tex_w = (r32)zt_game->textures[font->texture].width;
	r32 tex_h = (r32)zt_game->textures[font->texture].height;

	int glyph_idx = 0;
	i32 x_adv_ttl = 0;
	r32 base_offset = base == 0 ? 0 : base / (r32)zt_game->win_game_settings[0].pixels_per_unit;

	font->space_width = 0;

	for (int i = chars_line; i < lines; ++i) {
		zt_strCpy(line_buff, zt_elementsOf(line_buff), (char*)data + lines_tok[i].beg, lines_tok[i].len);
		line_buff[lines_tok[i].len] = 0;

		if (!zt_strStartsWith(line_buff, "char id")) {
			continue;
		}

		ztToken toks[32];
		int toks_cnt = zt_strTokenize(line_buff, " ", toks, zt_elementsOf(toks), ztStrTokenizeFlags_ProcessQuotes);
		if (toks_cnt > zt_elementsOf(toks)) {
			continue;
		}

		if (glyph_idx >= chars)
			break;

		int* codepoint = &font->glyph_code_point[glyph_idx];
		ztFont::ztGlyph *glyph = &font->glyphs[glyph_idx];
		glyph_idx += 1;
		*codepoint = -1;

		zt_fjz(toks_cnt) {
			char* start = line_buff + toks[j].beg;
			int val = local::getIntAfterEquals(start, toks[j].len);

			if (zt_strStartsWith(start, "id=")) {
				*codepoint = val;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "x=")) {
				glyph->tex_uv.x = (offset.x + (r32)val) / tex_w;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "y=")) {
				glyph->tex_uv.y = (offset.y + (r32)val) / tex_h;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "width=")) {
				glyph->tex_uv.z = (r32)val / tex_w;
				glyph->size.x = val / (r32)zt_game->win_game_settings[0].pixels_per_unit;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "height=")) {
				glyph->tex_uv.w = (r32)val / tex_h;
				glyph->size.y = val / (r32)zt_game->win_game_settings[0].pixels_per_unit;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "xoffset=")) {
				glyph->offset.x = (val / 1.f) / zt_game->win_game_settings[0].pixels_per_unit;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "yoffset=")) {
				glyph->offset.y = ((val / 1.f) / zt_game->win_game_settings[0].pixels_per_unit) - base_offset;
			}
			else if (*codepoint != -1 && zt_strStartsWith(start, "xadvance=")) {
				glyph->x_adv = val / (r32)zt_game->win_game_settings[0].pixels_per_unit;
				x_adv_ttl += val;
			}
		}
		if (*codepoint != -1) {
			glyph->tex_uv.z += glyph->tex_uv.x;
			glyph->tex_uv.w += glyph->tex_uv.y;

			if (*codepoint == ' ') {
				font->space_width = glyph->x_adv;
			}
		}
	}

	font->line_spacing = ((r32)font->size_pixels * .1f) / zt_game->win_game_settings[0].pixels_per_unit;
	if (font->space_width == 0) {
		font->space_width = (x_adv_ttl / (r32)(glyph_idx - 1)) / zt_game->win_game_settings[0].pixels_per_unit;
	}

	if (asset_mgr) {
		zt_free(data);
	}
	return font_id;

on_error:
	if (error) {
		if (asset_mgr) {
			zt_logCritical("Unable to load bitmap font from asset '%s' (error: %s)", asset_mgr->asset_name[asset_id], error);
		}
		else {
			zt_logCritical("Unable to load bitmap font (error: %s)", error);
		}
	}
	if (font_id != ztInvalidID) {
		zt_fontFree(font_id);
	}

	if (asset_mgr) {
		zt_free(data);
	}
	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

ztFontID zt_fontMakeFromBmpFontAsset(ztAssetManager *asset_mgr, ztAssetID asset_id, ztAssetID texture_override_asset_id, const ztVec2& override_offset)
{
	ZT_PROFILE_RENDERING("zt_fontMakeFromBmpFontAsset");
	return _zt_fontMakeFromBmpFontBase(asset_mgr, asset_id, texture_override_asset_id, nullptr, ztInvalidID, override_offset);
}

// ------------------------------------------------------------------------------------------------

ztFontID zt_fontMakeFromBmpFontFile(const char *file_name, ztTextureID texture_override_id, const ztVec2& override_offset)
{
	ZT_PROFILE_RENDERING("zt_fontMakeFromBmpFontFile");
	i32 size;
	void *data = zt_readEntireFile(file_name, &size);
	if (data == nullptr) {
		zt_logCritical("Unable to load bitmap font file: %s", file_name);
		return ztInvalidID;
	}

	ztFontID font_id = _zt_fontMakeFromBmpFontBase(nullptr, ztInvalidID, ztInvalidID, (char*)data, texture_override_id, override_offset);
	zt_free(data);
	return font_id;
}

// ------------------------------------------------------------------------------------------------

ztFontID zt_fontMakeFromBmpFontData(const char *file_data, ztTextureID texture_override_id, const ztVec2& override_offset)
{
	ZT_PROFILE_RENDERING("zt_fontMakeFromBmpFontData");
	return _zt_fontMakeFromBmpFontBase(nullptr, ztInvalidID, ztInvalidID, file_data, texture_override_id, override_offset);
}

// ------------------------------------------------------------------------------------------------

void zt_fontFree(ztFontID font_id)
{
	ZT_PROFILE_RENDERING("zt_fontFree");
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);

	ztFont *font = &zt_game->fonts[font_id];

	if (font->texture != ztInvalidID) {
		zt_textureFree(font->texture);
	}

	if (font->glyph_code_point) {
		zt_freeArena(font->glyph_code_point, font->arena);
	}
	if (font->glyphs) {
		zt_freeArena(font->glyphs, font->arena);
	}

	zt_memSet(font, zt_sizeof(ztFont), 0);
}

// ------------------------------------------------------------------------------------------------

const char *zt_fontGetName(ztFontID font_id)
{
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);
	return zt_game->fonts[font_id].name;
}

// ------------------------------------------------------------------------------------------------

i32 zt_fontGetSizeInPixels(ztFontID font_id)
{
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);
	return zt_game->fonts[font_id].size_pixels;
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_fontGetRowCount(const char *text, int text_len)
{
	ZT_PROFILE_RENDERING("_zt_fontGetRowCount");
	int rows = 1;
	zt_fiz(text_len) {
		i32 codepoint;
		text = zt_strCodepoint(text, &codepoint);
		if (codepoint == '\n') {
			rows += 1;
		}
	}

	return rows;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_fontGetRowInfo(const char *text, int text_len, int row, int *start_char, int *length)
{
	ZT_PROFILE_RENDERING("_zt_fontGetRowInfo");
	int current_row = 0;
	*start_char = 0;
	*length = 0;
	zt_fiz(text_len) {
		i32 codepoint = 0;
		text = zt_strCodepoint(text, &codepoint);
		if (codepoint == '\n') {
			current_row += 1;
			if (current_row > row) {
				return;
			}
			else if (current_row == row) {
				*start_char = i + 1;
				*length = 0;
			}
		}
		else if (current_row == row) {
			*length += 1;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_fontGetGlyphsFromText(ztFontID font_id, const char *text, int text_len, i32 *glyphs_idx, int glyphs_size)
{
	ZT_PROFILE_RENDERING("_zt_fontGetGlyphsFromText");
	ztFont *font = &zt_game->fonts[font_id];

	if (text_len > glyphs_size) {
		text_len = glyphs_size;
	}

	zt_fiz(text_len) {
		i32 codepoint = 0;
		text = zt_strCodepoint(text, &codepoint);
		glyphs_idx[i] = -1;
		zt_fjz(font->glyph_count) {
			if (font->glyph_code_point[j] == codepoint) {
				glyphs_idx[i] = j;
				break;
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_fontGetExtents(ztFontID font_id, const char *text, int text_len, int row, i32 *glyphs_idx, int glyphs_size, r32 *width, r32 *height)
{
	ZT_PROFILE_RENDERING("_zt_fontGetExtents");
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);

	if (text_len == 0) {
		// we should return a valid height for empty lines
		_zt_fontGetExtents(font_id, "A", 1, row, glyphs_idx, glyphs_size, width, height);
		*width = 0;
		return;
	}

	ztFont *font = &zt_game->fonts[font_id];

	r32 total_width = 0;
	r32 total_height = 0;
	r32 row_width = 0;
	r32 row_height = 0;

	int current_row = 0;

	zt_fiz(text_len) {
		int glyph_idx = glyphs_idx[i];
		if (glyph_idx < 0) {
			if (row_height == 0) {
				row_height = font->line_height;
			}

			i32 codepoint = zt_strCodepoint(text, i);
			if (codepoint == '\n') {
				if (current_row == row) {
					*width = row_width;
					*height = row_height;
					return;
				}
				total_height += row_height + (font->line_spacing);
				total_width = zt_max(total_width, row_width);
				row_height = row_width = 0;
				current_row += 1;
			}
			else if (codepoint == ' ') {
				row_width += font->space_width;
			}
			else if (codepoint == '\t') {
				row_width += font->space_width * 4; // TODO(josh): fix this
			}
			continue;
		}

		r32 x = font->glyphs[glyph_idx].x_adv;
		r32 y = font->glyphs[glyph_idx].size.y;

		row_width += x;
		row_height = zt_max(row_height, y);
	}
	total_height += row_height;
	total_width = zt_max(total_width, row_width);

	if (row == current_row) {
		*width = row_width;
		*height = row_height;
	}
	else {
		*width = total_width;
		*height = total_height;
	}
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_fontGetExtents(ztFontID font_id, const char *text)
{
	return zt_fontGetExtents(font_id, text, zt_strLen(text));
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_fontGetExtents(ztFontID font_id, const char *text, int text_len)
{
	ZT_PROFILE_RENDERING("zt_fontGetExtents");
	if (text == nullptr || text_len <= 0) {
		return ztVec2::zero;
	}

	i32 glyphs_idx[1024 * 64];
	_zt_fontGetGlyphsFromText(font_id, text, text_len, glyphs_idx, zt_elementsOf(glyphs_idx));

	ztVec2 result;
	_zt_fontGetExtents(font_id, text, text_len, -1, glyphs_idx, zt_elementsOf(glyphs_idx), &result.x, &result.y);
	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	zt_drawListAddText2D(draw_list, font_id, text, zt_strLen(text), pos, ztVec2::one, align_flags, anchor_flags, extents);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	zt_drawListAddText2D(draw_list, font_id, text, text_len, pos, ztVec2::one, align_flags, anchor_flags, extents);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, ztVec2 scale, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	zt_drawListAddText2D(draw_list, font_id, text, zt_strLen(text), pos, scale, align_flags, anchor_flags, extents);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, ztVec2 scale, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	ZT_PROFILE_RENDERING("zt_drawListAddText2D");
	zt_returnOnNull(draw_list);
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);
	if (text_len <= 0) return;

	ztFont *font = &zt_game->fonts[font_id];

	i32 glyphs_idx[1024 * 64];
	_zt_fontGetGlyphsFromText(font_id, text, text_len, glyphs_idx, zt_elementsOf(glyphs_idx));

	r32 total_width = 0;
	r32 total_height = 0;

	int rows = _zt_fontGetRowCount(text, text_len);
	_zt_fontGetExtents(font_id, text, text_len, -1, glyphs_idx, zt_elementsOf(glyphs_idx), &total_width, &total_height);

	total_width *= scale.x;
	total_height *= scale.y;

	if(extents) {
		extents->x = total_width;
		extents->y = total_height;
	}

	r32 true_total_width = total_width;
	r32 true_total_height = total_height;

	ztVec2 size = ztVec2::zero; // TODO(josh): add support for setting area for font to fit to
	if (size.x > total_width) total_width = size.x;
	if (size.y > total_height) total_height = size.y;

	ztVec2 position = pos;
	if (zt_bitIsSet(anchor_flags, ztAnchor_Left)) { position.x += total_width / 2.f; }
	else if (zt_bitIsSet(anchor_flags, ztAnchor_Right)) { position.x -= total_width / 2.f; }
	if (zt_bitIsSet(anchor_flags, ztAnchor_Top)) { position.y -= total_height / 2.f; }
	else if (zt_bitIsSet(anchor_flags, ztAnchor_Bottom)) { position.y += total_height / 1.f; }

	r32 start_pos_y = (position.y + (true_total_height / 2)); // initially start out at the top left corner.  each row needs to subtract its height to get the proper start pos

	if (zt_bitIsSet(align_flags, ztAlign_Top)) { start_pos_y += (total_height - true_total_height) / 2.f; }
	else if (zt_bitIsSet(align_flags, ztAlign_Bottom)) { start_pos_y -= (total_height - true_total_height) / 2.f; }

	zt_drawListPushTexture(draw_list, font->texture);

	r32 ppu = zt_pixelsPerUnit();

	for (int r = 0; r < rows; ++r) {
		r32 row_width = 0;
		r32 row_height = 0;
		if (size.x == 0 && size.y == 0 && rows == 1) {
			row_width = total_width;
			row_height = total_height;
		}
		else {
			_zt_fontGetExtents(font_id, text, text_len, r, glyphs_idx, zt_elementsOf(glyphs_idx), &row_width, &row_height);
			row_width *= scale.x;
			row_height *= scale.y;
		}

		int start_char = 0, length = 0;
		_zt_fontGetRowInfo(text, text_len, r, &start_char, &length);

		start_pos_y -= row_height;

		r32 start_pos_x = position.x - (total_width / 2.f);

		if (zt_bitIsSet(align_flags, ztAlign_Center)) {
			start_pos_x = position.x - (row_width / 2.f);
		}
		else if (zt_bitIsSet(align_flags, ztAlign_Right)) {
			start_pos_x = position.x + (total_width / 2.f - row_width);
		}

		real32 spacing = 0;

		ztVec2 position;
		ztVec2 units_size;
		ztVec3 rotation = ztVec3::zero;

		r32 scale_x = scale.x;
		r32 scale_y = scale.y;

		ztVec3 dl_pos[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };
		ztVec2 dl_uvs[4];
		ztVec3 dl_nml[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };

		for (int i = start_char; i < start_char + length; ++i) {
			int glyph_idx = glyphs_idx[i];
			if (glyph_idx < 0) {
				if (text[i] == ' ') {
					start_pos_x += font->space_width * scale_x;
				}
				else if (text[i] == '\t') {
					start_pos_x += font->space_width * 4 * scale_x; // TODO(josh): fix
				}
				continue;
			}

			ztFont::ztGlyph* glyph = &font->glyphs[glyph_idx];

			units_size.x = glyph->size.x * scale_x;
			units_size.y = glyph->size.y * scale_y;
			row_height = zt_max(row_height, units_size.y);

			position.x = glyph->offset.x + start_pos_x;
			position.y = start_pos_y - glyph->offset.y * scale_y;
			zt_alignToPixel(&position.x, ppu);
			zt_alignToPixel(&position.y, ppu);

			// points in ccw order
			dl_pos[0].x = position.x; dl_pos[1].x = position.x;                dl_pos[2].x = position.x + units_size.x; dl_pos[3].x = position.x + units_size.x;
			dl_pos[0].y = position.y; dl_pos[1].y = position.y - units_size.y; dl_pos[2].y = position.y - units_size.y; dl_pos[3].y = position.y;

			dl_uvs[0].x = glyph->tex_uv.x; dl_uvs[1].x = glyph->tex_uv.x; dl_uvs[2].x = glyph->tex_uv.z; dl_uvs[3].x = glyph->tex_uv.z;
			dl_uvs[0].y = glyph->tex_uv.y; dl_uvs[1].y = glyph->tex_uv.w; dl_uvs[2].y = glyph->tex_uv.w; dl_uvs[3].y = glyph->tex_uv.y;

			zt_drawListAddFilledQuad(draw_list, dl_pos, dl_uvs, dl_nml);

			start_pos_x += glyph->x_adv * scale_x;
		}

		start_pos_y -= font->line_spacing * scale_y;
	}

	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_fontGetExtentsFancy(ztFontID font_id, const char *text, int text_len, int row, i32 *glyphs_idx, int glyphs_size, r32 *width, r32 *height)
{
	ZT_PROFILE_RENDERING("_zt_fontGetExtentsFancy");
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);

	if (text_len == 0) {
		// we should return a valid height for empty lines
		_zt_fontGetExtentsFancy(font_id, "A", 1, row, glyphs_idx, glyphs_size, width, height);
		*width = 0;
		return;
	}

	ztFont *font = &zt_game->fonts[font_id];

	r32 total_width = 0;
	r32 total_height = 0;
	r32 row_width = 0;
	r32 row_height = 0;

	int current_row = 0;

	bool in_format = false;
	char format[128];
	char *format_ptr = format;

	zt_fiz(text_len) {
		int glyph_idx = glyphs_idx[i];
		char ch;
		if (glyph_idx < 0) {
			ch = (char)zt_strCodepoint(text, i);
		}
		else {
			ch = (char)font->glyph_code_point[glyph_idx];
		}

		if (in_format) {
			if (ch == '>') {
				in_format = false;
				*format_ptr = 0;
				format_ptr = format;
				continue;
			}
			else if (ch == '<') {
				in_format = false;
			}
			else {
				*format_ptr++ = ch;
				zt_assert(format_ptr - format < zt_elementsOf(format));
				continue;
			}
		}
		else if (ch == '<') {
			in_format = true;
			continue;
		}

		if (glyph_idx < 0) {
			if (row_height == 0) {
				row_height = font->line_height;
			}

			if (ch == '\n') {
				if (current_row == row) {
					*width = row_width;
					*height = row_height;
					return;
				}
				total_height += row_height + (font->line_spacing);
				total_width = zt_max(total_width, row_width);
				row_height = row_width = 0;
				current_row += 1;
			}
			else if (ch == ' ') {
				row_width += font->space_width;
			}
			else if (ch == '\t') {
				row_width += font->space_width * 4; // TODO(josh): fix this
			}
			continue;
		}

		r32 x = font->glyphs[glyph_idx].x_adv;
		r32 y = font->glyphs[glyph_idx].size.y;

		row_width += x;
		row_height = zt_max(row_height, y);
	}
	total_height += row_height;
	total_width = zt_max(total_width, row_width);

	if (row == current_row) {
		*width = row_width;
		*height = row_height;
	}
	else {
		*width = total_width;
		*height = total_height;
	}
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_fontGetExtentsFancy(ztFontID font_id, const char *text)
{
	return zt_fontGetExtentsFancy(font_id, text, zt_strLen(text));
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_fontGetExtentsFancy(ztFontID font_id, const char *text, int text_len)
{
	ZT_PROFILE_RENDERING("zt_fontGetExtentsFancy");
	if (text == nullptr || text_len <= 0) {
		return ztVec2::zero;
	}

	i32 glyphs_idx[1024 * 64];
	_zt_fontGetGlyphsFromText(font_id, text, text_len, glyphs_idx, zt_elementsOf(glyphs_idx));

	ztVec2 result;
	_zt_fontGetExtentsFancy(font_id, text, text_len, -1, glyphs_idx, zt_elementsOf(glyphs_idx), &result.x, &result.y);
	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	zt_drawListAddFancyText2D(draw_list, font_id, text, zt_strLen(text), pos, ztVec2::one, align_flags, anchor_flags, extents);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	zt_drawListAddFancyText2D(draw_list, font_id, text, text_len, pos, ztVec2::one, align_flags, anchor_flags, extents);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, ztVec2 pos, ztVec2 scale, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	zt_drawListAddFancyText2D(draw_list, font_id, text, zt_strLen(text), pos, scale, align_flags, anchor_flags, extents);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddFancyText2D(ztDrawList *draw_list, ztFontID font_id, const char *text, int text_len, ztVec2 pos, ztVec2 scale, i32 align_flags, i32 anchor_flags, ztVec2 *extents)
{
	ZT_PROFILE_RENDERING("zt_drawListAddFancyText2D");
	zt_returnOnNull(draw_list);
	zt_assert(font_id >= 0 && font_id < zt_game->fonts_count);
	if (text_len <= 0) return;

	ztFont *font = &zt_game->fonts[font_id];

	i32 glyphs_idx[1024 * 64];
	_zt_fontGetGlyphsFromText(font_id, text, text_len, glyphs_idx, zt_elementsOf(glyphs_idx));

	r32 total_width = 0;
	r32 total_height = 0;

	int rows = _zt_fontGetRowCount(text, text_len);
	_zt_fontGetExtentsFancy(font_id, text, text_len, -1, glyphs_idx, zt_elementsOf(glyphs_idx), &total_width, &total_height);

	total_width *= scale.x;
	total_height *= scale.y;

	if(extents) {
		extents->x = total_width;
		extents->y = total_height;
	}

	r32 true_total_width = total_width;
	r32 true_total_height = total_height;

	ztVec2 size = ztVec2::zero; // TODO(josh): add support for setting area for font to fit to
	if (size.x > total_width) total_width = size.x;
	if (size.y > total_height) total_height = size.y;

	ztVec2 position = pos;
	if (zt_bitIsSet(anchor_flags, ztAnchor_Left)) { position.x += total_width / 2.f; }
	else if (zt_bitIsSet(anchor_flags, ztAnchor_Right)) { position.x -= total_width / 2.f; }
	if (zt_bitIsSet(anchor_flags, ztAnchor_Top)) { position.y -= total_height / 2.f; }
	else if (zt_bitIsSet(anchor_flags, ztAnchor_Bottom)) { position.y += total_height / 1.f; }

	r32 start_pos_y = (position.y + (true_total_height / 2)); // initially start out at the top left corner.  each row needs to subtract its height to get the proper start pos

	if (zt_bitIsSet(align_flags, ztAlign_Top)) { start_pos_y += (total_height - true_total_height) / 2.f; }
	else if (zt_bitIsSet(align_flags, ztAlign_Bottom)) { start_pos_y -= (total_height - true_total_height) / 2.f; }

	zt_drawListPushTexture(draw_list, font->texture);

	r32 ppu = zt_pixelsPerUnit();

	bool in_format = false;
	char format[128];
	char *format_ptr = format;

	zt_drawListPushColor(draw_list, ztColor(1, 1, 1, 1));
	int colors_pushed = 0;

	for (int r = 0; r < rows; ++r) {
		real32 row_width = 0;
		real32 row_height = 0;
		if (size.x == 0 && size.y == 0 && rows == 1) {
			row_width = total_width;
			row_height = total_height;
		}
		else {
			_zt_fontGetExtentsFancy(font_id, text, text_len, r, glyphs_idx, zt_elementsOf(glyphs_idx), &row_width, &row_height);
			row_width *= scale.x;
			row_height *= scale.y;
		}

		int start_char = 0, length = 0;
		_zt_fontGetRowInfo(text, text_len, r, &start_char, &length);

		start_pos_y -= row_height;

		r32 start_pos_x = position.x - (total_width / 2.f);

		if (zt_bitIsSet(align_flags, ztAlign_Center)) {
			start_pos_x = position.x - (row_width / 2.f);
		}
		else if (zt_bitIsSet(align_flags, ztAlign_Right)) {
			start_pos_x = position.x + (total_width / 2.f - row_width);
		}

		real32 spacing = 0;

		ztVec2 position;
		ztVec2 units_size;
		ztVec3 rotation = ztVec3::zero;

		r32 scale_x = scale.x;
		r32 scale_y = scale.y;

		ztVec3 dl_pos[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };
		ztVec2 dl_uvs[4];
		ztVec3 dl_nml[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };

		for (int i = start_char; i < start_char + length; ++i) {
			int glyph_idx = glyphs_idx[i];
			char ch;

			if (glyph_idx < 0) {
				ch = (char)zt_strCodepoint(text, i);
			}
			else {
				ch = (char)font->glyph_code_point[glyph_idx];
			}

			if (in_format) {
				if (ch == '>') {
					in_format = false;
					*format_ptr = 0;
					format_ptr = format;

					int str_len = zt_strLen(format);
					if (zt_strStartsWith(format, "color=") && (str_len == 12 || str_len == 14) ) {
						r32 r = zt_strToIntHex(format + 6, 2, 1) / 255.f;
						r32 g = zt_strToIntHex(format + 8, 2, 1) / 255.f;
						r32 b = zt_strToIntHex(format + 10, 2, 1) / 255.f;
						r32 a = str_len == 12 ? 1 : (zt_strToIntHex(format + 12, 2, 1) / 255.f);
						zt_drawListPushColor(draw_list, ztColor(r, g, b, a));
						colors_pushed += 1;
					}
					else if (zt_strStartsWith(format, "/color")) {
						zt_drawListPopColor(draw_list);
						colors_pushed -= 1;
					}

					continue;
				}
				else if (ch == '<') {
					in_format = false;
				}
				else {
					*format_ptr++ = ch;
					zt_assert(format_ptr - format < zt_elementsOf(format));
					continue;
				}
			}
			else if (ch == '<') {
				in_format = true;
				continue;
			}

			if (glyph_idx < 0) {
				if (ch == ' ') {
					start_pos_x += font->space_width * scale_x;
				}
				else if (ch == '\t') {
					start_pos_x += font->space_width * 4 * scale_x; // TODO(josh): fix
				}
				continue;
			}

			ztFont::ztGlyph* glyph = &font->glyphs[glyph_idx];

			units_size.x = glyph->size.x * scale_x;
			units_size.y = glyph->size.y * scale_y;
			row_height = zt_max(row_height, units_size.y);

			position.x = glyph->offset.x + start_pos_x;
			position.y = start_pos_y - glyph->offset.y * scale_y;
			zt_alignToPixel(&position.x, ppu);
			zt_alignToPixel(&position.y, ppu);

			// points in ccw order
			dl_pos[0].x = position.x; dl_pos[1].x = position.x;                dl_pos[2].x = position.x + units_size.x; dl_pos[3].x = position.x + units_size.x;
			dl_pos[0].y = position.y; dl_pos[1].y = position.y - units_size.y; dl_pos[2].y = position.y - units_size.y; dl_pos[3].y = position.y;

			dl_uvs[0].x = glyph->tex_uv.x; dl_uvs[1].x = glyph->tex_uv.x; dl_uvs[2].x = glyph->tex_uv.z; dl_uvs[3].x = glyph->tex_uv.z;
			dl_uvs[0].y = glyph->tex_uv.y; dl_uvs[1].y = glyph->tex_uv.w; dl_uvs[2].y = glyph->tex_uv.w; dl_uvs[3].y = glyph->tex_uv.y;

			zt_drawListAddFilledQuad(draw_list, dl_pos, dl_uvs, dl_nml);

			start_pos_x += glyph->x_adv * scale_x;
		}

		start_pos_y -= font->line_spacing * scale_y;
	}
	zt_fiz(colors_pushed) {
		zt_drawListPopColor(draw_list);
	}
	zt_drawListPopColor(draw_list);

	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztSprite zt_spriteMake(ztTextureID tex, int x, int y, int w, int h, int anchor_x, int anchor_y)
{
	ZT_PROFILE_RENDERING("zt_spriteMake");
	zt_assert(tex != ztInvalidID);
	zt_assert(x >= 0 && y >= 0 && w != 0 && h != 0);

	r32 tex_w = (r32)zt_game->textures[tex].width;
	r32 tex_h = (r32)zt_game->textures[tex].height;

	ztSprite result;
	result.tex = tex;
	result.tex_uv.x = x / tex_w;
	result.tex_uv.y = y / tex_h;
	result.tex_uv.z = result.tex_uv.x + w / tex_w;
	result.tex_uv.w = result.tex_uv.y + h / tex_h;

	r32 ppu = zt_pixelsPerUnit();
	result.half_size.x = w / ppu / 2.f;
	result.half_size.y = h / ppu / 2.f;
	result.anchor.x = anchor_x / ppu;
	result.anchor.y = anchor_y / ppu;

	return result;
}

// ------------------------------------------------------------------------------------------------

ztSprite zt_spriteMake(ztTextureID tex, ztPoint2 pos, ztPoint2 size, ztPoint2 anchor)
{
	return zt_spriteMake(tex, pos.x, pos.y, size.x, size.y, anchor.x, anchor.y);
}

// ------------------------------------------------------------------------------------------------

ztSprite zt_spriteMakeFromGrid(ztTextureID tex, int x, int y, int w, int h, int anchor_x, int anchor_y)
{
	return zt_spriteMake(tex, x * w, y * h, w, h, anchor_x, anchor_y);
}

// ------------------------------------------------------------------------------------------------

ztSprite zt_spriteMakeFromGrid(ztTextureID tex, ztPoint2 pos, ztPoint2 size, ztPoint2 anchor)
{
	return zt_spriteMake(tex, pos.x * size.x, pos.y * size.y, size.x, size.y, anchor.x, anchor.y);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddSprite(ztDrawList *draw_list, ztSprite *sprite, const ztVec3& position)
{
	ZT_PROFILE_RENDERING("zt_drawListAddSprite");
	ztVec3 pos[4] = {
		ztVec3(-sprite->anchor.x + -sprite->half_size.x, -sprite->anchor.y + sprite->half_size.y, 0), // top left
		ztVec3(-sprite->anchor.x + -sprite->half_size.x, -sprite->anchor.y + -sprite->half_size.y, 0), // bottom left
		ztVec3(-sprite->anchor.x + sprite->half_size.x, -sprite->anchor.y + -sprite->half_size.y, 0), // bottom right
		ztVec3(-sprite->anchor.x + sprite->half_size.x, -sprite->anchor.y + sprite->half_size.y, 0), // top right
	};

	ztVec2 uvs[4] = {
		ztVec2(sprite->tex_uv.x, sprite->tex_uv.y),
		ztVec2(sprite->tex_uv.x, sprite->tex_uv.w),
		ztVec2(sprite->tex_uv.z, sprite->tex_uv.w),
		ztVec2(sprite->tex_uv.z, sprite->tex_uv.y),
	};

	static ztVec3 nml[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };

	r32 ppu = zt_pixelsPerUnit();

	zt_fiz(4) {
		pos[i].x += position.x;
		pos[i].y += position.y;

		zt_alignToPixel(&pos[i].x, ppu);
		zt_alignToPixel(&pos[i].y, ppu);
	}

	zt_drawListPushTexture(draw_list, sprite->tex);
	zt_drawListAddFilledQuad(draw_list, pos, uvs, nml);
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddSprite(ztDrawList *draw_list, ztSprite *sprite, const ztVec3& position, const ztVec3& rot, const ztVec3& scale)
{
	ZT_PROFILE_RENDERING("zt_drawListAddSprite");
	ztVec3 pos[4] = {
		ztVec3(-sprite->anchor.x + -sprite->half_size.x, -sprite->anchor.y + sprite->half_size.y, 0), // top left
		ztVec3(-sprite->anchor.x + -sprite->half_size.x, -sprite->anchor.y + -sprite->half_size.y, 0), // bottom left
		ztVec3(-sprite->anchor.x + sprite->half_size.x,  -sprite->anchor.y + -sprite->half_size.y, 0), // bottom right
		ztVec3(-sprite->anchor.x + sprite->half_size.x,  -sprite->anchor.y + sprite->half_size.y, 0), // top right
	};

	ztVec2 uvs[4] = {
		ztVec2(sprite->tex_uv.x, sprite->tex_uv.y),
		ztVec2(sprite->tex_uv.x, sprite->tex_uv.w),
		ztVec2(sprite->tex_uv.z, sprite->tex_uv.w),
		ztVec2(sprite->tex_uv.z, sprite->tex_uv.y),
	};

	static ztVec3 nml[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };

	if (rot.x != 0 || rot.y != 0 || rot.z != 0) {
		ztMat4 rotation_mat = ztMat4::identity.getRotateEuler(rot);

		zt_fiz(4) {
			pos[i] = rotation_mat * pos[i];
		}
	}

	if (scale.x != 1 || scale.y != 1) {
		zt_fiz(4) {
			pos[i].x *= scale.x;
			pos[i].y *= scale.y;
		}
	}

	r32 pos_x = position.x, pos_y = position.y, ppu = zt_pixelsPerUnit();
	zt_alignToPixel(&pos_x, ppu);
	zt_alignToPixel(&pos_y, ppu);

	zt_fiz(4) {
		pos[i].x += pos_x;
		pos[i].y += pos_y;
	}

	zt_drawListPushTexture(draw_list, sprite->tex);
	zt_drawListAddFilledQuad(draw_list, pos, uvs, nml);
	zt_drawListPopTexture(draw_list);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztSpriteNineSlice zt_spriteNineSliceMake(ztTextureID tex, int tex_x, int tex_y, int tex_w, int tex_h, int nw_interior_x, int nw_interior_y, int se_interior_x, int se_interior_y, int offset_l, int offset_t, int offset_r, int offset_b)
{
	ZT_PROFILE_RENDERING("zt_spriteNineSliceMake");
	zt_assert(tex != ztInvalidID);
	zt_assert(tex_x >= 0 && tex_y >= 0 && tex_w != 0 && tex_h != 0 && nw_interior_x > tex_x && nw_interior_y > tex_y && se_interior_x < tex_x + tex_w && se_interior_y < tex_y + tex_h);

	r32 tex_atl_w = (r32)zt_game->textures[tex].width;
	r32 tex_atl_h = (r32)zt_game->textures[tex].height;

	//  0, 1,  2, 3, 4, 5,  6, 7,  8
	// nw, n, ne, w, c, e, sw, s, se

	ztSpriteNineSlice result;

	r32 x = tex_x / tex_atl_w;
	r32 y = tex_y / tex_atl_h;
	r32 w = ((r32)tex_w) / tex_atl_w;
	r32 h = ((r32)tex_h) / tex_atl_h;
	r32 nwx = ((r32)nw_interior_x) / tex_atl_w;
	r32 nwy = ((r32)nw_interior_y) / tex_atl_h;
	r32 sex = ((r32)se_interior_x) / tex_atl_w;
	r32 sey = ((r32)se_interior_y) / tex_atl_h;

	result.tex = tex;
	result.sp_nw = ztVec4( x  , y  , nwx  , nwy); // nw
	result.sp_n  = ztVec4( nwx, y  , sex  , nwy); // n
	result.sp_ne = ztVec4( sex, y  , x + w, nwy); // ne
	result.sp_w  = ztVec4( x  , nwy, nwx  , sey); // w
	result.sp_c  = ztVec4( nwx, nwy, sex  , sey); // c
	result.sp_e  = ztVec4( sex, nwy, x + w, sey); // e
	result.sp_sw = ztVec4( x  , sey, nwx  , y + h); // sw
	result.sp_s  = ztVec4( nwx, sey, sex  , y + h); // s
	result.sp_se = ztVec4( sex, sey, x + w, y + h); // se

	r32 ppu = zt_pixelsPerUnit();
	result.sz_n = (nw_interior_y - tex_y) / ppu;
	result.sz_s = ((tex_y + tex_h) - se_interior_y) / ppu;
	result.sz_w = (nw_interior_x - tex_x) / ppu;
	result.sz_e = ((tex_x + tex_w) - se_interior_x) / ppu;
	result.sz_cw = (se_interior_x - nw_interior_x) / ppu;
	result.sz_ch = (se_interior_y - nw_interior_y) / ppu;

	result.offset.x = offset_l / tex_atl_w;
	result.offset.y = offset_t / tex_atl_h;
	result.offset.z = offset_r / tex_atl_w;
	result.offset.w = offset_b / tex_atl_h;

	return result;
}

// ------------------------------------------------------------------------------------------------

ztSpriteNineSlice zt_spriteNineSliceMake(ztTextureID tex, ztPoint2 tex_pos, ztPoint2 tex_size, ztPoint2 nw_interior, ztPoint2 se_interior, int offset_l, int offset_t, int offset_r, int offset_b)
{
	return zt_spriteNineSliceMake(tex, tex_pos.x, tex_pos.y, tex_size.x, tex_size.y, nw_interior.x, nw_interior.y, se_interior.x, se_interior.y, offset_l, offset_t, offset_r, offset_b);
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddSpriteNineSlice(ztDrawList *draw_list, ztSpriteNineSlice *sns, const ztVec2& cpos, const ztVec2& csize)
{
	ZT_PROFILE_RENDERING("zt_drawListAddSpriteNineSlice");
	r32 ppu = zt_pixelsPerUnit();

	ztVec2 pos = cpos;
//	zt_alignToPixel(&pos, ppu);
	ztVec2 size = csize;
//	zt_alignToPixel(&size, ppu);

	ztVec2 upper_left (pos.x - size.x / 2.f, pos.y + size.y / 2.f);
	ztVec2 upper_right(pos.x + size.x / 2.f, pos.y + size.y / 2.f);
	ztVec2 lower_left (pos.x - size.x / 2.f, pos.y - size.y / 2.f);
	ztVec2 lower_right(pos.x + size.x / 2.f, pos.y - size.y / 2.f);
	ztVec2 center     (pos.x + (sns->sz_w - sns->sz_e) / 2.f, pos.y - (sns->sz_n - sns->sz_s) / 2.f);

	ztVec3 scale_corners = ztVec3::one;
	if (size.x < sns->sz_e + sns->sz_w) { scale_corners.x = size.x / (sns->sz_e + sns->sz_w); }
	if (size.y < sns->sz_n + sns->sz_s) { scale_corners.y = size.y / (sns->sz_n + sns->sz_s); }

#if 0
	struct local
	{
		static void fix(r32 *val, r32 *offset, r32 ppu)
		{
			r32 rem = zt_abs(*val * ppu) - zt_convertToi32Floor(zt_abs(*val * ppu));
			if (rem > .25f && rem < .75f) {
				*val = zt_convertToi32Floor((*val * ppu)) / ppu;
				*offset += rem / ppu;
			}
		}
	};

	r32 ul_center_add_x = 0, ul_center_add_y = 0;
	//zt_alignToPixel(&upper_left.x, ppu, &ul_center_add_x);
	//zt_alignToPixel(&upper_left.y, ppu, &ul_center_add_y);

	r32 ur_center_add_x = 0, ur_center_add_y = 0;
	//zt_alignToPixel(&upper_right.x, ppu, &ur_center_add_x);
	//zt_alignToPixel(&upper_right.y, ppu, &ur_center_add_y);

	r32 ll_center_add_x = 0, ll_center_add_y = 0;
	//zt_alignToPixel(&lower_left.x, ppu, &ll_center_add_x);
	//zt_alignToPixel(&lower_left.y, ppu, &ll_center_add_y);

	r32 lr_center_add_x = 0, lr_center_add_y = 0;
	//zt_alignToPixel(&lower_right.x, ppu, &lr_center_add_x);
	//zt_alignToPixel(&lower_right.y, ppu, &lr_center_add_y);

	//ul_center_add_x = ul_center_add_y = ur_center_add_x = ur_center_add_y = ll_center_add_x = ll_center_add_y = lr_center_add_x = lr_center_add_y = 0;

	zt_drawListPushTexture(draw_list, sns->tex);

	/* center */ zt_drawListAddFilledRect2D(draw_list, ztVec3(center.x,                                            center.y,                                           0), ztVec2(size.x - ((sns->sz_e + sns->sz_w)),                         size.y - ((sns->sz_n + sns->sz_s))),                   sns->sp_c.xy, sns->sp_c.zw);
	/* west   */ zt_drawListAddFilledRect2D(draw_list, ztVec3(upper_left.x + (sns->sz_w * scale_corners.x) / 2.f,  center.y,                                           0), ztVec2(sns->sz_w * scale_corners.x + ul_center_add_x,              size.y - ((sns->sz_n + sns->sz_s) + ul_center_add_y)), sns->sp_w.xy, sns->sp_w.zw);
	/* east   */ zt_drawListAddFilledRect2D(draw_list, ztVec3(upper_right.x - (sns->sz_e * scale_corners.x) / 2.f, center.y,                                           0), ztVec2(sns->sz_e * scale_corners.x + ur_center_add_x,              size.y - ((sns->sz_n + sns->sz_s) + ur_center_add_y)), sns->sp_e.xy, sns->sp_e.zw);
	/* north  */ zt_drawListAddFilledRect2D(draw_list, ztVec3(center.x,                                            upper_left.y - (sns->sz_n * scale_corners.y) / 2.f, 0), ztVec2(size.x - ((sns->sz_e + sns->sz_w) + (ul_center_add_x * 2)), sns->sz_n * scale_corners.y + ul_center_add_y),        sns->sp_n.xy, sns->sp_n.zw);
	/* south  */ zt_drawListAddFilledRect2D(draw_list, ztVec3(center.x,                                            lower_left.y + (sns->sz_s * scale_corners.y) / 2.f, 0), ztVec2(size.x - ((sns->sz_e + sns->sz_w) + (ll_center_add_x * 2)), sns->sz_s * scale_corners.y + ll_center_add_y),        sns->sp_s.xy, sns->sp_s.zw);

	/* north west */ zt_drawListAddFilledRect2D(draw_list, ztVec3(upper_left.x + (sns->sz_w * scale_corners.x) / 2.f, upper_left.y - (sns->sz_n * scale_corners.y) / 2.f, 0), ztVec2(sns->sz_w * scale_corners.x + ul_center_add_x, sns->sz_n * scale_corners.y + ul_center_add_y), sns->sp_nw.xy, sns->sp_nw.zw);
	/* north east */ zt_drawListAddFilledRect2D(draw_list, ztVec3(upper_right.x - (sns->sz_e * scale_corners.x) / 2.f, upper_right.y - (sns->sz_n * scale_corners.y) / 2.f, 0), ztVec2(sns->sz_e * scale_corners.x + ur_center_add_x, sns->sz_n * scale_corners.y + ur_center_add_y), sns->sp_ne.xy, sns->sp_ne.zw);
	/* south west */ zt_drawListAddFilledRect2D(draw_list, ztVec3(lower_left.x + (sns->sz_w * scale_corners.x) / 2.f, lower_left.y + (sns->sz_s * scale_corners.y) / 2.f, 0), ztVec2(sns->sz_w * scale_corners.x + ll_center_add_x, sns->sz_s * scale_corners.y + ll_center_add_y), sns->sp_sw.xy, sns->sp_sw.zw);
	/* south east */ zt_drawListAddFilledRect2D(draw_list, ztVec3(lower_right.x - (sns->sz_e * scale_corners.x) / 2.f, lower_right.y + (sns->sz_s * scale_corners.y) / 2.f, 0), ztVec2(sns->sz_e * scale_corners.x + lr_center_add_x, sns->sz_s * scale_corners.y + lr_center_add_y), sns->sp_se.xy, sns->sp_se.zw);

	zt_drawListPopTexture(draw_list);
#else

	ztVec3 pos_nw[] = {
		ztVec3(upper_left.x,                               upper_left.y, 0),
		ztVec3(upper_left.x,                               upper_left.y - sns->sz_n * scale_corners.y, 0),
		ztVec3(upper_left.x + sns->sz_w * scale_corners.x, upper_left.y - sns->sz_n * scale_corners.y, 0),
		ztVec3(upper_left.x + sns->sz_w * scale_corners.x, upper_left.y, 0)
	};
	ztVec3 pos_ne[] = {
		ztVec3(upper_right.x - sns->sz_e * scale_corners.x, upper_right.y, 0),
		ztVec3(upper_right.x - sns->sz_e * scale_corners.x, upper_right.y - sns->sz_n * scale_corners.y, 0),
		ztVec3(upper_right.x,                               upper_right.y - sns->sz_n * scale_corners.y, 0),
		ztVec3(upper_right.x,                               upper_right.y, 0)
	};
	ztVec3 pos_sw[] = {
		ztVec3(lower_left.x,                               lower_left.y + sns->sz_s * scale_corners.y, 0),
		ztVec3(lower_left.x,                               lower_left.y, 0),
		ztVec3(lower_left.x + sns->sz_w * scale_corners.x, lower_left.y, 0),
		ztVec3(lower_left.x + sns->sz_w * scale_corners.x, lower_left.y + sns->sz_s * scale_corners.y, 0)
	};
	ztVec3 pos_se[] = {
		ztVec3(lower_right.x - sns->sz_e * scale_corners.x, lower_right.y + sns->sz_s * scale_corners.y, 0),
		ztVec3(lower_right.x - sns->sz_e * scale_corners.x, lower_right.y, 0),
		ztVec3(lower_right.x,                               lower_right.y, 0),
		ztVec3(lower_right.x,                               lower_right.y + sns->sz_s * scale_corners.y, 0)
	};

	zt_fiz(4) {
		zt_alignToPixel(&pos_nw[i], ppu);
		zt_alignToPixel(&pos_ne[i], ppu);
		zt_alignToPixel(&pos_sw[i], ppu);
		zt_alignToPixel(&pos_se[i], ppu);
	}

	zt_drawListPushTexture(draw_list, sns->tex);
	/* center     */ zt_drawListAddFilledQuad(draw_list, pos_nw[2], pos_sw[3], pos_se[0], pos_ne[1], sns->sp_c.xy, ztVec2(sns->sp_c.x, sns->sp_c.w), sns->sp_c.zw, ztVec2(sns->sp_c.z, sns->sp_c.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* west       */ zt_drawListAddFilledQuad(draw_list, pos_nw[1], pos_sw[0], pos_sw[3], pos_nw[2], sns->sp_w.xy, ztVec2(sns->sp_w.x, sns->sp_w.w), sns->sp_w.zw, ztVec2(sns->sp_w.z, sns->sp_w.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* east       */ zt_drawListAddFilledQuad(draw_list, pos_ne[1], pos_se[0], pos_se[3], pos_ne[2], sns->sp_e.xy, ztVec2(sns->sp_e.x, sns->sp_e.w), sns->sp_e.zw, ztVec2(sns->sp_e.z, sns->sp_e.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* north      */ zt_drawListAddFilledQuad(draw_list, pos_nw[3], pos_nw[2], pos_ne[1], pos_ne[0], sns->sp_n.xy, ztVec2(sns->sp_n.x, sns->sp_n.w), sns->sp_n.zw, ztVec2(sns->sp_n.z, sns->sp_n.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* south      */ zt_drawListAddFilledQuad(draw_list, pos_sw[3], pos_sw[2], pos_se[1], pos_se[0], sns->sp_s.xy, ztVec2(sns->sp_s.x, sns->sp_s.w), sns->sp_s.zw, ztVec2(sns->sp_s.z, sns->sp_s.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);

	/* north west */ zt_drawListAddFilledQuad(draw_list, pos_nw[0], pos_nw[1], pos_nw[2], pos_nw[3], sns->sp_nw.xy, ztVec2(sns->sp_nw.x, sns->sp_nw.w), sns->sp_nw.zw, ztVec2(sns->sp_nw.z, sns->sp_nw.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* north east */ zt_drawListAddFilledQuad(draw_list, pos_ne[0], pos_ne[1], pos_ne[2], pos_ne[3], sns->sp_ne.xy, ztVec2(sns->sp_ne.x, sns->sp_ne.w), sns->sp_ne.zw, ztVec2(sns->sp_ne.z, sns->sp_ne.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* south west */ zt_drawListAddFilledQuad(draw_list, pos_sw[0], pos_sw[1], pos_sw[2], pos_sw[3], sns->sp_sw.xy, ztVec2(sns->sp_sw.x, sns->sp_sw.w), sns->sp_sw.zw, ztVec2(sns->sp_sw.z, sns->sp_sw.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	/* south east */ zt_drawListAddFilledQuad(draw_list, pos_se[0], pos_se[1], pos_se[2], pos_se[3], sns->sp_se.xy, ztVec2(sns->sp_se.x, sns->sp_se.w), sns->sp_se.zw, ztVec2(sns->sp_se.z, sns->sp_se.y), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero);
	zt_drawListPopTexture(draw_list);
#endif
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztMaterial zt_materialMake(ztTextureID diffuse_tex, const ztVec4& diffuse_color, i32 diffuse_flags,
						   ztTextureID specular_tex, const ztVec4& specular_color, i32 specular_flags,
						   ztTextureID normal_tex, i32 normal_flags, r32 shininess)
{
	ZT_PROFILE_RENDERING("zt_materialMake");
	ztMaterial result;

	result.name[0] = 0;

	result.diffuse_tex = diffuse_tex;
	result.diffuse_color = diffuse_color;
	result.diffuse_flags = diffuse_flags;

	result.diffuse_tex_override = 0;
	result.diffuse_color_override = 0;

	result.specular_tex = specular_tex;
	result.specular_color = specular_color;
	result.specular_flags = specular_flags;

	result.specular_tex_override = 0;
	result.specular_color_override = 0;

	result.normal_tex = normal_tex;
	result.normal_flags = normal_flags;

	result.normal_tex_override = 0;

	result.shininess = shininess;
	result.shininess_override = 0;

	return result;
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_materialLoadFromFileDataBase(char *data, int data_size, ztMaterial *materials_arr, int materials_arr_size, ztAssetManager *asset_mgr, ztAssetID asset_id, char *file_name)
{
	ZT_PROFILE_RENDERING("_zt_materialLoadFromFileDataBase");
	zt_returnValOnNull(data, 0);

	int lines = zt_strTokenize(data, data_size, "\r\n", nullptr, 0, ztStrTokenizeFlags_TrimWhitespace);

	ztToken *tokens = zt_mallocStructArray(ztToken, lines);
	zt_strTokenize(data, "\r\n", tokens, lines, ztStrTokenizeFlags_TrimWhitespace);

	int curr_mtl_idx = -1;
	ztMaterial *curr_mtl = nullptr;

	zt_fiz(lines) {
		char line[1024];
		zt_strCpy(line, zt_elementsOf(line), data + tokens[i].beg, tokens[i].len);

		if (line[0] == '#') continue;

		if (zt_strStartsWith(line, "newmtl")) {
			curr_mtl_idx += 1;

			curr_mtl = curr_mtl_idx < materials_arr_size ? &materials_arr[curr_mtl_idx] : nullptr;
			if (curr_mtl) {
				*curr_mtl = zt_materialMake();

				int space = zt_strFindPos(line, " ", 0);
				if (space != ztStrPosNotFound) {
					zt_strCpy(curr_mtl->name, zt_elementsOf(curr_mtl->name), line + space + 1);
				}
			}
		}
		else if (curr_mtl != nullptr) {
			struct local
			{
				static ztVec4 parseReflectivity(char *line)
				{
					ztVec4 result = ztVec4::one;
					ztToken tokens[3];
					if (zt_strTokenize(line, " ", tokens, zt_elementsOf(tokens)) == 3) {
						result.r = zt_strToReal32(line + tokens[0].beg, tokens[0].len, 1);
						result.g = zt_strToReal32(line + tokens[1].beg, tokens[1].len, 1);
						result.b = zt_strToReal32(line + tokens[2].beg, tokens[2].len, 1);
					}
					// should support spectral curve and CIEXYZ color space
					return result;
				}

				static r32 parseValue(char *line)
				{
					return zt_strToReal32(line, 0);
				}

				static ztTextureID parseTexture(char *line, ztAssetManager *asset_mgr, ztAssetID asset_id, char *file_name)
				{
					char *file = line + zt_strFindLastPos(line, " ") + 1;

					if (asset_mgr) {
						ztAssetID tex_asset_id = zt_assetLoad(asset_mgr, file, asset_id);
						if (tex_asset_id != ztInvalidID) {
							return zt_textureMake(asset_mgr, tex_asset_id);
						}
					}
					else {
						char tex_file_name[ztFileMaxPath];
						zt_fileGetFileInOtherFileDirectory(tex_file_name, ztFileMaxPath, file, file_name);
						return zt_textureMakeFromFile(tex_file_name);
					}
					return ztInvalidID;
				}
			};
			if (zt_strStartsWith(line, "Ka ")) {	// ambient reflectivity
			}
			else if (zt_strStartsWith(line, "Kd ")) {	// diffuse reflectivity
				curr_mtl->diffuse_color = local::parseReflectivity(line + 3);
			}
			else if (zt_strStartsWith(line, "Ks ")) {	// specular reflectivity
				curr_mtl->specular_color = local::parseReflectivity(line + 3);
			}
			else if (zt_strStartsWith(line, "Ni ")) {	// optical density
			}
			else if (zt_strStartsWith(line, "Ns ")) {	// specular exponent
				curr_mtl->shininess = local::parseValue(line) / 1000.f;
			}
			else if (zt_strStartsWith(line, "d ")) {	// dissolve
			}
			else if (zt_strStartsWith(line, "illum ")) { // illumination model
			}
			else if (zt_strStartsWith(line, "sharpness ")) {	// sharpness of reflections
			}
			else if (zt_strStartsWith(line, "map_Ka ")) {
			}
			else if (zt_strStartsWith(line, "map_Kd ")) {
				if (curr_mtl->diffuse_tex != ztInvalidID) {
					zt_assert(false);
				}
				curr_mtl->diffuse_tex = local::parseTexture(line, asset_mgr, asset_id, file_name);
				curr_mtl->diffuse_flags |= ztMaterialFlags_OwnsTexture;
			}
			else if (zt_strStartsWith(line, "map_Ks ")) {
				if (curr_mtl->specular_tex != ztInvalidID) {
					zt_assert(false);
				}
				curr_mtl->specular_tex = local::parseTexture(line, asset_mgr, asset_id, file_name);
				curr_mtl->specular_flags |= ztMaterialFlags_OwnsTexture;
			}
			else if (zt_strStartsWith(line, "map_Ns ")) {
				if (curr_mtl->normal_tex != ztInvalidID) {
					zt_assert(false);
				}
				curr_mtl->normal_tex = local::parseTexture(line, asset_mgr, asset_id, file_name);
				curr_mtl->normal_flags |= ztMaterialFlags_OwnsTexture;
			}
			else if (zt_strStartsWith(line, "map_d ")) {
			}
			else if (zt_strStartsWith(line, "disp ")) {
			}
			else if (zt_strStartsWith(line, "decal ")) {
			}
			else if (zt_strStartsWith(line, "bump ")) {
			}
			else if (zt_strStartsWith(line, "refl ")) {
			}
		}
	}

	zt_free(tokens);

	return curr_mtl_idx + 1;
}

// ------------------------------------------------------------------------------------------------

int zt_materialLoad(ztAssetManager *asset_mgr, ztAssetID asset_id, ztMaterial *materials_arr, int materials_arr_size)
{
	ZT_PROFILE_RENDERING("zt_materialLoad");
	zt_returnValOnNull(asset_mgr, 0);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	if (asset_mgr->asset_type[asset_id] != ztAssetManagerType_Material) {
		zt_logCritical("Asset is not a material: %s", asset_mgr->asset_name[asset_id]);
		return 0;
	}

	i32 size = zt_assetSize(asset_mgr, asset_id);
	if (size <= 0) {
		zt_logCritical("Unable to determine asset size: %s", asset_mgr->asset_name[asset_id]);
		return 0;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		zt_logCritical("Unable to allocate memory: %s (%d bytes)", asset_mgr->asset_name[asset_id], size);
		return 0;
	}

	if (!zt_assetLoadData(asset_mgr, asset_id, data, size)) {
		zt_logCritical("Unable to load asset contents: %s", asset_mgr->asset_name[asset_id]);
		zt_free(data);
		return 0;
	}
	int result = _zt_materialLoadFromFileDataBase(data, size, materials_arr, materials_arr_size, asset_mgr, asset_id, nullptr);
	zt_free(data);
	return result;
}

// ------------------------------------------------------------------------------------------------

int zt_materialLoadFromFile(char *file_name, ztMaterial *materials_arr, int materials_arr_size)
{
	ZT_PROFILE_RENDERING("zt_materialLoadFromFile");
	int size = zt_fileSize(file_name);
	if (size <= 0) {
		zt_logCritical("Unable to determine size of file: %s", file_name);
		return 0;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		zt_logCritical("Unable to allocate memory: %s (%d bytes)", file_name, size);
		return 0;
	}

	zt_readEntireFile(file_name, data, size);

	int result = _zt_materialLoadFromFileDataBase(data, size, materials_arr, materials_arr_size, nullptr, ztInvalidID, file_name);
	zt_free(data);
	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_materialFree(ztMaterial *material)
{
	ZT_PROFILE_RENDERING("zt_materialFree");
	zt_returnOnNull(material);

	if (zt_bitIsSet(material->diffuse_flags, ztMaterialFlags_OwnsTexture)) {
		zt_textureFree(material->diffuse_tex);
	}
	material->diffuse_tex = ztInvalidID;
	material->diffuse_flags = 0;
	material->diffuse_color = ztVec4::one;
	material->diffuse_tex_override = 0;
	material->diffuse_color_override = 0;

	if (zt_bitIsSet(material->specular_flags, ztMaterialFlags_OwnsTexture)) {
		zt_textureFree(material->specular_tex);
	}
	material->specular_tex = ztInvalidID;
	material->specular_flags = 0;
	material->specular_color = ztVec4::one;
	material->specular_tex_override = 0;
	material->specular_color_override = 0;

	if (zt_bitIsSet(material->normal_flags, ztMaterialFlags_OwnsTexture)) {
		zt_textureFree(material->normal_tex);
	}
	material->normal_tex = ztInvalidID;
	material->normal_flags = 0;
	material->normal_tex_override = 0;

	material->shininess_override = 0;
}

// ------------------------------------------------------------------------------------------------

bool zt_materialIsEmpty(ztMaterial *material)
{
	if (material->diffuse_tex != ztInvalidID || material->diffuse_color != ztVec4::one ||
		material->specular_tex != ztInvalidID || material->specular_color != ztVec4::one ||
		material->normal_tex != ztInvalidID) {
		return false;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_materialPrepare(ztMaterial *material, ztShaderID shader, ztTextureID *additional_tex, u32 *additional_tex_name_hashes, int additional_tex_count)
{
	ZT_PROFILE_RENDERING("zt_materialPrepare");
	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			ztgl_textureBindReset(zt_game->shaders[shader].gl_shader);

			int tex_count = 0;
			ztTextureID diffuse_tex = zt_max(material->diffuse_tex, 0);
			zt_game->game_details.curr_frame.texture_switches += 1;
			static u32 diffuse_tex_hash = zt_strHash("diffuse_tex");
			zt_shaderSetVariableTex(shader, material->diffuse_tex_override ? material->diffuse_tex_override : diffuse_tex_hash, diffuse_tex);

			ztTextureID specular_tex = zt_max(material->specular_tex, 0);
			zt_game->game_details.curr_frame.texture_switches += 1;
			static u32 specular_tex_hash = zt_strHash("specular_tex");
			ztgl_textureBind(zt_game->textures[specular_tex].gl_texture, tex_count);
			zt_shaderSetVariableTex(shader, material->specular_tex_override ? material->specular_tex_override : specular_tex_hash, specular_tex);

			ztTextureID normal_tex = zt_max(material->normal_tex, 0);
			zt_game->game_details.curr_frame.texture_switches += 1;
			static u32 normal_tex_hash = zt_strHash("normal_tex");
			zt_shaderSetVariableTex(shader, material->normal_tex_override ? material->normal_tex_override : normal_tex_hash, normal_tex);

			zt_fiz(additional_tex_count) {
				if (additional_tex[i] != ztInvalidID) {
					zt_game->game_details.curr_frame.texture_switches += 1;
					zt_shaderSetVariableTex(shader, additional_tex_name_hashes[i], additional_tex[i]);
					tex_count += 1;
				}
			}

			zt_game->shaders[shader].textures_bound = tex_count;

#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)

			ztTextureID diffuse_tex = zt_max(material->diffuse_tex, 0);
			zt_game->game_details.curr_frame.texture_switches += 1;
			static u32 diffuse_tex_hash = zt_strHash("diffuse_tex");
			zt_shaderSetVariableTex(shader, material->diffuse_tex_override ? material->diffuse_tex_override : diffuse_tex_hash, diffuse_tex);

			ztTextureID specular_tex = zt_max(material->specular_tex, 0);
			zt_game->game_details.curr_frame.texture_switches += 1;
			static u32 specular_tex_hash = zt_strHash("specular_tex");
			zt_shaderSetVariableTex(shader, material->specular_tex_override ? material->specular_tex_override : specular_tex_hash, specular_tex);

			ztTextureID normal_tex = zt_max(material->normal_tex, 0);
			zt_game->game_details.curr_frame.texture_switches += 1;
			static u32 normal_tex_hash = zt_strHash("normal_tex");
			zt_shaderSetVariableTex(shader, material->normal_tex_override ? material->normal_tex_override : normal_tex_hash, normal_tex);

			zt_fiz(additional_tex_count) {
				if (additional_tex[i] != ztInvalidID) {
					zt_game->game_details.curr_frame.texture_switches += 1;
					zt_shaderSetVariableTex(shader, additional_tex_name_hashes[i], additional_tex[i]);
				}
			}
#			endif
		} break;

		default: {
			zt_assert(false);
		}
	}

	static u32 diffuse_color_hash = zt_strHash("diffuse_color");
	static u32 specular_color_hash = zt_strHash("specular_color_hash");
	static u32 shininess_hash = zt_strHash("shininess_hash");

	zt_shaderSetVariableVec4(shader, material->diffuse_color_override ? material->diffuse_color_override : diffuse_color_hash, material->diffuse_color);
	zt_shaderSetVariableVec4(shader, material->specular_color_override ? material->specular_color_override : specular_color_hash, material->specular_color);
	zt_shaderSetVariableFloat(shader, material->shininess_override ? material->shininess_override : shininess_hash, material->shininess);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztMeshID zt_meshMake(ztVec3 *verts, ztVec2 *uvs, ztVec3 *normals, i32 vert_count, u32 *indices, i32 indices_count)
{
	ZT_PROFILE_RENDERING("zt_meshMake");
#	pragma pack(push, 1)
	struct ztVertex
	{
		ztVec3 pos;
		ztVec2 uv;
		ztVec3 normals;
		ztVec4 colors;
		ztVec4 tangent;
		ztVec4 bitangent;
	};
#	pragma pack(pop)


	u32* t_indices = nullptr;
	if (indices_count == 0) {
		t_indices = zt_mallocStructArray(u32, vert_count);
		indices_count = vert_count;
		indices = t_indices;

		zt_fiz(indices_count) indices[i] = i;
	}

	ztVertex *vertices = zt_mallocStructArray(ztVertex, indices_count);

	ztVec3 *t_normals = nullptr;
	if (normals == nullptr) {
		// calculate the vertex normals
		t_normals = zt_mallocStructArray(ztVec3, vert_count);
		zt_fiz(vert_count) t_normals[i] = ztVec3::zero;

		// for each vertex, we need to find the faces that surround it and add them to
		for (int i = 0; i < indices_count; i += 3) {
			ztVec3 u = verts[indices[i + 1]] - verts[indices[i + 0]];
			ztVec3 v = verts[indices[i + 2]] - verts[indices[i + 0]];

			for (int j = 0; j < 3; ++j) {
				t_normals[indices[i + j]].x += u.y * v.z - u.z * v.y;
				t_normals[indices[i + j]].y += u.z * v.x - u.x * v.z;
				t_normals[indices[i + j]].z += u.x * v.y - u.y * v.x;
			}
		}

		zt_fiz(vert_count) {
			t_normals[i].normalize();
		}

		normals = t_normals;
	}

	zt_fiz(indices_count) {
		vertices[i].pos = verts[indices[i]];
		vertices[i].uv = uvs == nullptr ? ztVec2::zero : uvs[indices[i]];
		vertices[i].normals = normals[indices[i]];
		vertices[i].colors = ztVec4::one;
		indices[i] = i;

		vertices[i].uv.y = 1 - vertices[i].uv.y;
	}

	int triangles = indices_count / 3;
	int idx = 0;
	zt_fiz(triangles) {
		ztVertex& v1 = vertices[idx++];
		ztVertex& v2 = vertices[idx++];
		ztVertex& v3 = vertices[idx++];

		ztVec3 edge1 = v2.pos - v1.pos;
		ztVec3 edge2 = v3.pos - v1.pos;
		ztVec2 duv1 = v2.uv - v1.uv;
		ztVec2 duv2 = v3.uv - v1.uv;

		r32 f = 1.f / (duv2.x * duv1.y - duv1.x * duv2.y);

		ztVec3 tangent  (f * ( duv2.y * edge1.x - duv1.y * edge2.x), f * ( duv2.y * edge1.y - duv1.y * edge2.y), f * ( duv2.y * edge1.z - duv1.y * edge2.z));
		ztVec3 bitangent(f * (-duv2.x * edge1.x + duv1.x * edge2.x), f * (-duv2.x * edge1.y + duv1.x * edge2.y), f * (-duv2.x * edge1.z + duv1.x * edge2.z));

		tangent.normalize();
		bitangent.normalize();

		v1.tangent = v2.tangent = v3.tangent = ztVec4(tangent, 0);
		v1.bitangent = v2.bitangent = v3.bitangent = ztVec4(bitangent, 0);
	}

	zt_assert(zt_game->meshes_count < zt_elementsOf(zt_game->meshes));
	ztMeshID mesh_id = zt_game->meshes_count++;
	ztMesh *mesh = &zt_game->meshes[mesh_id];
	zt_memSet(mesh, zt_sizeof(ztMesh), 0);

	mesh->triangles = indices_count / 3;
	mesh->indices = indices_count;

	{
		// calculate aabb / obb
		ztVec3 ext_min = ztVec3::max, ext_max = ztVec3::min;
		zt_fiz(vert_count) {
			ext_min.x = zt_min(ext_min.x, verts[i].x);
			ext_min.y = zt_min(ext_min.y, verts[i].y);
			ext_min.z = zt_min(ext_min.z, verts[i].z);

			ext_max.x = zt_max(ext_max.x, verts[i].x);
			ext_max.y = zt_max(ext_max.y, verts[i].y);
			ext_max.z = zt_max(ext_max.z, verts[i].z);
		}

		r32 aabb_dist = zt_max(zt_max(zt_max(ext_max.x, ext_max.y), ext_max.z), zt_abs(zt_min(zt_min(ext_min.x, ext_min.y), ext_min.z)));
		ztVec2 dist_min(-aabb_dist, -aabb_dist), dist_max(aabb_dist, aabb_dist);
		aabb_dist = dist_max.distance(dist_min);

		mesh->aabb = ztVec3(aabb_dist, aabb_dist, aabb_dist);

		mesh->obb_size = ext_max - ext_min;
		mesh->obb_center = ztVec3(ext_min.x + mesh->obb_size.x / 2, ext_min.y + mesh->obb_size.y / 2, ext_min.z + mesh->obb_size.z / 2);
	}

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#if defined(ZT_OPENGL)
			
			ztVertexEntryGL entries[] = {
				{ GL_FLOAT, 3 * sizeof(GLfloat) },
				{ GL_FLOAT, 2 * sizeof(GLfloat) },
				{ GL_FLOAT, 3 * sizeof(GLfloat) },
				{ GL_FLOAT, 4 * sizeof(GLfloat) },
				{ GL_FLOAT, 4 * sizeof(GLfloat) },
				{ GL_FLOAT, 4 * sizeof(GLfloat) },
			};

			mesh->gl_vertex_array = ztgl_vertexArrayMake(entries, zt_elementsOf(entries), vertices, indices_count);
			if (mesh->gl_vertex_array == nullptr) {
				return ztInvalidID;
			}

#endif // ZT_OPENGL
		} break;

		case ztRenderer_DirectX: {
#if defined(ZT_DIRECTX)
			ztWindowDetails *win_details = &zt_game->win_details[0];

			ztVertexEntryDX entries[] = {
				{ 3 * sizeof(r32) },
				{ 2 * sizeof(r32) },
				{ 3 * sizeof(r32) },
				{ 4 * sizeof(r32) },
				{ 4 * sizeof(r32) },
				{ 4 * sizeof(r32) },
			};

			mesh->dx_vertex_array = ztdx_vertexArrayMake(win_details->dx_context, entries, zt_elementsOf(entries), vertices, indices_count);
			if (mesh->dx_vertex_array == nullptr) {
				return ztInvalidID;
			}
#endif // ZT_DIRECTX
		} break;
	}

	if (t_indices != nullptr) {
		zt_free(t_indices);
	}
	if (t_normals != nullptr) {
		zt_free(t_normals);
	}

	zt_free(vertices);

	return mesh_id;
}

// ------------------------------------------------------------------------------------------------

void zt_meshFree(ztMeshID mesh_id)
{
	ZT_PROFILE_RENDERING("zt_meshFree");
	zt_assert(mesh_id >= 0 && mesh_id < zt_game->meshes_count);

	ztMesh *mesh = &zt_game->meshes[mesh_id];

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
			zt_openGLSupport(ztgl_vertexArrayFree(mesh->gl_vertex_array));
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_vertexArrayFree(mesh->dx_vertex_array));
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

ztMeshID zt_meshMakePrimitiveBox(r32 width, r32 height, r32 depth)
{
	ZT_PROFILE_RENDERING("zt_meshMakePrimitiveBox");
	ztVec3 vertices[] = {
		/* front face  */ ztVec3(-.5f * width,  .5f * height,  .5f * depth), ztVec3(-.5f * width, -.5f * height,  .5f * depth), ztVec3( .5f * width, -.5f * height,  .5f * depth), ztVec3( .5f * width,  .5f * height,  .5f * depth),
		/* back face   */ ztVec3( .5f * width,  .5f * height, -.5f * depth), ztVec3( .5f * width, -.5f * height, -.5f * depth), ztVec3(-.5f * width, -.5f * height, -.5f * depth), ztVec3(-.5f * width,  .5f * height, -.5f * depth),
		/* top face    */ ztVec3(-.5f * width,  .5f * height, -.5f * depth), ztVec3(-.5f * width,  .5f * height,  .5f * depth), ztVec3( .5f * width,  .5f * height,  .5f * depth), ztVec3( .5f * width,  .5f * height, -.5f * depth),
		/* bottom face */ ztVec3(-.5f * width, -.5f * height,  .5f * depth), ztVec3(-.5f * width, -.5f * height, -.5f * depth), ztVec3( .5f * width, -.5f * height, -.5f * depth), ztVec3( .5f * width, -.5f * height,  .5f * depth),
		/* right face  */ ztVec3( .5f * width,  .5f * height,  .5f * depth), ztVec3( .5f * width, -.5f * height,  .5f * depth), ztVec3( .5f * width, -.5f * height, -.5f * depth), ztVec3( .5f * width,  .5f * height, -.5f * depth),
		/* left face   */ ztVec3(-.5f * width,  .5f * height, -.5f * depth), ztVec3(-.5f * width, -.5f * height, -.5f * depth), ztVec3(-.5f * width, -.5f * height,  .5f * depth), ztVec3(-.5f * width,  .5f * height,  .5f * depth)
	};

	ztVec2 uvs[] = {
		ztVec2(0.0f, 0.0f), ztVec2(0.0f, 1.0f), ztVec2(1.0f, 1.0f), ztVec2(1.0f, 0.0f),
		ztVec2(0.0f, 0.0f),	ztVec2(0.0f, 1.0f), ztVec2(1.0f, 1.0f), ztVec2(1.0f, 0.0f),
		ztVec2(0.0f, 0.0f), ztVec2(0.0f, 1.0f), ztVec2(1.0f, 1.0f), ztVec2(1.0f, 0.0f),
		ztVec2(0.0f, 0.0f), ztVec2(0.0f, 1.0f), ztVec2(1.0f, 1.0f), ztVec2(1.0f, 0.0f),
		ztVec2(0.0f, 0.0f),	ztVec2(0.0f, 1.0f), ztVec2(1.0f, 1.0f), ztVec2(1.0f, 0.0f),
		ztVec2(0.0f, 0.0f),	ztVec2(0.0f, 1.0f), ztVec2(1.0f, 1.0f), ztVec2(1.0f, 0.0f),
	};

	ztVec3 normals[] = {
		ztVec3(0, 0, 1), ztVec3(0, 0, 1), ztVec3(0, 0, 1), ztVec3(0, 0, 1),
		ztVec3(0, 0, -1), ztVec3(0, 0, -1), ztVec3(0, 0, -1), ztVec3(0, 0, -1),
		ztVec3(0, 1, 0), ztVec3(0, 1, 0), ztVec3(0, 1, 0), ztVec3(0, 1, 0),
		ztVec3(0, -1, 0), ztVec3(0, -1, 0), ztVec3(0, -1, 0), ztVec3(0, -1, 0),
		ztVec3(1, 0, 0), ztVec3(1, 0, 0), ztVec3(1, 0, 0), ztVec3(1, 0, 0),
		ztVec3(-1, 0, 0), ztVec3(-1, 0, 0), ztVec3(-1, 0, 0), ztVec3(-1, 0, 0),
	};

	u32 indices[] = {
		/* front face  */ 0, 1, 2, 0, 2, 3,
		/* back face   */ 4, 5, 6, 4, 6, 7,
		/* top face    */ 8, 9, 10, 8, 10, 11,
		/* bottom face */ 12, 13, 14, 12, 14, 15,
		/* right face  */ 16, 17, 18, 16, 18, 19,
		/* left face   */ 20, 21, 22, 20, 22, 23,
	};

	zt_assert(zt_elementsOf(vertices) == zt_elementsOf(normals) && zt_elementsOf(vertices) == zt_elementsOf(uvs));

	return zt_meshMake(vertices, uvs, normals, zt_elementsOf(vertices), indices, zt_elementsOf(indices));
}

// ------------------------------------------------------------------------------------------------

ztMeshID zt_meshMakePrimitivePlane(r32 width, r32 depth, int grid_w, int grid_d)
{
	ZT_PROFILE_RENDERING("zt_meshMakePrimitivePlane");
	int verts_count = (grid_w * grid_d) * 4;
	ztVec3 *vertices = zt_mallocStructArray(ztVec3, verts_count);
	ztVec2 *uvs = zt_mallocStructArray(ztVec2, verts_count);
	ztVec3 *normals = zt_mallocStructArray(ztVec3, verts_count);
	int indices_count = (grid_w * grid_d) * 6;
	u32* indices = zt_mallocStructArray(u32, indices_count);

	real32 x_offset = (width / -2.0f);
	real32 z_offset = (depth / -2.0f);

	int vrt_idx = 0;
	int ind_idx = 0;

	r32 sec_w = (width / grid_w) * .5f;
	r32 sec_d = (depth / grid_d) * .5f;

	for (int z = 0; z < grid_d; ++z) {
		for (int x = 0; x < grid_w; ++x) {
			r32 x_pos = sec_w + x_offset + (x * (width / grid_w));
			r32 z_pos = sec_d + z_offset + (z * (depth / grid_d));

			vertices[vrt_idx] = ztVec3(-sec_w + x_pos, 0, -sec_d + z_pos);
			uvs[vrt_idx] = ztVec2(0.0f, 0.0f);
			normals[vrt_idx++] = ztVec3(0, 1, 0);

			vertices[vrt_idx] = ztVec3(-sec_w + x_pos, 0, sec_d + z_pos);
			uvs[vrt_idx] = ztVec2(0.0f, 1.0f);
			normals[vrt_idx++] = ztVec3(0, 1, 0);

			vertices[vrt_idx] = ztVec3(sec_w + x_pos, 0, sec_d + z_pos);
			uvs[vrt_idx] = ztVec2(1.0f, 1.0f);
			normals[vrt_idx++] = ztVec3(0, 1, 0);

			vertices[vrt_idx] = ztVec3(sec_w + x_pos, 0, -sec_d + z_pos);
			uvs[vrt_idx] = ztVec2(1.0f, 0.0f);
			normals[vrt_idx++] = ztVec3(0, 1, 0);

			indices[ind_idx++] = vrt_idx - 4;
			indices[ind_idx++] = vrt_idx - 3;
			indices[ind_idx++] = vrt_idx - 2;
			indices[ind_idx++] = vrt_idx - 4;
			indices[ind_idx++] = vrt_idx - 2;
			indices[ind_idx++] = vrt_idx - 1;
		}
	}

	ztMeshID result = zt_meshMake(vertices, uvs, normals, verts_count, indices, indices_count);

	zt_free(indices);
	zt_free(normals);
	zt_free(uvs);
	zt_free(vertices);

	return result;
}

// ------------------------------------------------------------------------------------------------

ztMeshID zt_meshMakePrimitiveDiamond(r32 width, r32 top, r32 bottom, int sides)
{
	ZT_PROFILE_RENDERING("zt_meshMakePrimitiveDiamond");
	int verts_count = 6 * sides;

	ztVec3 *vertices = zt_mallocStructArray(ztVec3, verts_count);

	r32 angle = zt_degreesToRadians(360.f / sides);

	ztVec3 vtop(0, top, 0);
	ztVec3 vbtm(0, -bottom, 0);

	int vert_idx = 0;
	zt_fiz(sides) {
		ztVec3 side_a = ztVec3(width * zt_cos(angle * i), 0, width * zt_sin(angle * i));
		ztVec3 side_b = ztVec3(width * zt_cos(angle * ((i + 1) % sides)), 0, width * zt_sin(angle * ((i + 1) % sides)));

		vertices[vert_idx++] = vtop;
		vertices[vert_idx++] = side_b;
		vertices[vert_idx++] = side_a;

		vertices[vert_idx++] = vbtm;
		vertices[vert_idx++] = side_a;
		vertices[vert_idx++] = side_b;
	}

	ztMeshID result = zt_meshMake(vertices, nullptr, nullptr, verts_count, nullptr, 0);

	zt_free(vertices);

	return result;
}

// ------------------------------------------------------------------------------------------------

ztMeshID zt_meshMakePrimitiveSphere(r32 radius, int rings, ztMeshPrimativeSphere_Enum texture)
{
	ZT_PROFILE_RENDERING("zt_meshMakePrimitiveSphere");
	int verts_count = rings * rings * 6 * 6;
	ztVec3 *vertices  = zt_mallocStructArray(ztVec3, verts_count);
	ztVec2 *uvs       = zt_mallocStructArray(ztVec2, verts_count);
	
	r32 grid_size = radius * 2 / rings;

	int vert_idx = 0;

	//                           front,        bottom,          back,            top,          left,         right

	r32 y_add_vert_2[6] = { -grid_size,             0,     grid_size,              0,    -grid_size,    -grid_size };
	r32 z_add_vert_2[6] = {          0,    -grid_size,             0,      grid_size,             0,             0 };

	r32 x_add_vert_3[6] = {  grid_size,     grid_size,     grid_size,      grid_size,             0,             0 };
	r32 y_add_vert_3[6] = { -grid_size,             0,     grid_size,              0,    -grid_size,    -grid_size };
	r32 z_add_vert_3[6] = {          0,    -grid_size,             0,      grid_size,     grid_size,    -grid_size };

	r32 x_add_vert_5[6] = {  grid_size,     grid_size,     grid_size,      grid_size,             0,             0 };
	r32 y_add_vert_5[6] = { -grid_size,             0,     grid_size,              0,    -grid_size,    -grid_size };
	r32 z_add_vert_5[6] = {          0,    -grid_size,             0,      grid_size,     grid_size,    -grid_size };

	r32 x_add_vert_6[6] = {  grid_size,     grid_size,     grid_size,      grid_size,             0,             0 };
	r32 z_add_vert_6[6] = {          0,             0,             0,              0,     grid_size,    -grid_size };

	r32 x_start[6]      = {    -radius,       -radius,       -radius,        -radius,       -radius,        radius };
	r32 y_start[6]      = {     radius,       -radius,       -radius,         radius,        radius,        radius };
	r32 z_start[6]      = {     radius,        radius,       -radius,        -radius,       -radius,        radius };

	r32 y_add_1[6]      = { -grid_size,             0,     grid_size,              0,    -grid_size,    -grid_size };
	r32 z_add_1[6]      = {          0,    -grid_size,             0,      grid_size,             0,             0 };

	r32 x_add_2[6]      = { grid_size ,     grid_size,     grid_size,      grid_size,             0,             0 };
	r32 y_add_2[6]      = { radius * 2,             0,   -radius * 2,              0,    radius * 2,    radius * 2 };
	r32 z_add_2[6]      = {          0,    radius * 2,             0,    -radius * 2,     grid_size,    -grid_size };

	r32 uv_x_beg[6]     = {       .25f,          .25f,          .25f,           .25f,         .000f,           .5f };
	r32 uv_y_beg[6]     = {      .000f,          .25f,           .5f,           .75f,         .000f,         .000f };

	zt_fkz(6) {
		r32 x_pos = x_start[k];
		r32 y_pos = y_start[k];
		r32 z_pos = z_start[k];

		zt_fiz(rings) {
			zt_fjz(rings) {
				vertices[vert_idx + 0] = ztVec3(x_pos                  , y_pos                  , z_pos);
				vertices[vert_idx + 1] = ztVec3(x_pos                  , y_pos + y_add_vert_2[k], z_pos + z_add_vert_2[k]);
				vertices[vert_idx + 2] = ztVec3(x_pos + x_add_vert_3[k], y_pos + y_add_vert_3[k], z_pos + z_add_vert_3[k]);

				vertices[vert_idx + 3] = ztVec3(x_pos                  , y_pos                  , z_pos);
				vertices[vert_idx + 4] = ztVec3(x_pos + x_add_vert_5[k], y_pos + y_add_vert_5[k], z_pos + z_add_vert_5[k]);
				vertices[vert_idx + 5] = ztVec3(x_pos + x_add_vert_6[k], y_pos                  , z_pos + z_add_vert_6[k]);

				if (texture == ztMeshPrimitiveSphere_TexDuplicatedPerFace) {
					uvs[vert_idx + 0] = ztVec2((i + 0) / (r32)rings, (j + 0) / (r32)rings);
					uvs[vert_idx + 1] = ztVec2((i + 0) / (r32)rings, (j + 1) / (r32)rings);
					uvs[vert_idx + 2] = ztVec2((i + 1) / (r32)rings, (j + 1) / (r32)rings);

					uvs[vert_idx + 3] = ztVec2((i + 0) / (r32)rings, (j + 0) / (r32)rings);
					uvs[vert_idx + 4] = ztVec2((i + 1) / (r32)rings, (j + 1) / (r32)rings);
					uvs[vert_idx + 5] = ztVec2((i + 1) / (r32)rings, (j + 0) / (r32)rings);
				}
				else {
					uvs[vert_idx + 0] = ztVec2(uv_x_beg[k] + ((i + 0) / (r32)rings * .25f), uv_y_beg[k] + ((j + 0) / (r32)rings * .25f));
					uvs[vert_idx + 1] = ztVec2(uv_x_beg[k] + ((i + 0) / (r32)rings * .25f), uv_y_beg[k] + ((j + 1) / (r32)rings * .25f));
					uvs[vert_idx + 2] = ztVec2(uv_x_beg[k] + ((i + 1) / (r32)rings * .25f), uv_y_beg[k] + ((j + 1) / (r32)rings * .25f));

					uvs[vert_idx + 3] = ztVec2(uv_x_beg[k] + ((i + 0) / (r32)rings * .25f), uv_y_beg[k] + ((j + 0) / (r32)rings * .25f));
					uvs[vert_idx + 4] = ztVec2(uv_x_beg[k] + ((i + 1) / (r32)rings * .25f), uv_y_beg[k] + ((j + 1) / (r32)rings * .25f));
					uvs[vert_idx + 5] = ztVec2(uv_x_beg[k] + ((i + 1) / (r32)rings * .25f), uv_y_beg[k] + ((j + 0) / (r32)rings * .25f));
				}

				vert_idx += 6;

				y_pos += y_add_1[k];
				z_pos += z_add_1[k];
			}
			x_pos += x_add_2[k];
			y_pos += y_add_2[k];
			z_pos += z_add_2[k];
		}
	}

	zt_fiz(vert_idx) {
		vertices[i].normalize();
		vertices[i] *= radius;
	}

	verts_count = vert_idx;

	ztMeshID result = zt_meshMake(vertices, uvs, nullptr, verts_count, nullptr, 0);

	zt_free(vertices);
	zt_free(uvs);

	return result;
}

// ------------------------------------------------------------------------------------------------

int zt_meshLoadOBJ(ztAssetManager *asset_mgr, ztAssetID asset_id, ztMeshID *mesh_ids, ztMaterial *materials, int mesh_mat_size, const ztVec3& scale, const ztVec3& offset)
{
	ZT_PROFILE_RENDERING("zt_meshLoadOBJ");
	zt_returnValOnNull(asset_mgr, ztInvalidID);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	if (asset_mgr->asset_type[asset_id] != ztAssetManagerType_MeshOBJ) {
		return ztInvalidID;
	}

	i32 size = zt_assetSize(asset_mgr, asset_id);

	zt_logInfo("loading obj file: %s (%d bytes)", asset_mgr->asset_name[asset_id], size);
	if (size <= 0) {
		return ztInvalidID;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		return ztInvalidID;
	}

	const char *error = nullptr;

	if (!zt_assetLoadData(asset_mgr, asset_id, data, size)) {
		zt_logCritical("Unable to load asset contents");
		zt_free(data);
		return ztInvalidID;
	}

	{
		bool has_cr = zt_strFindPos(data, zt_min(1024, size), "\r", 1) != ztStrPosNotFound;
		char *end_search = has_cr ? "\\\r" : "\\n";
		int replace_chars = has_cr ? 3 : 2;

		zt_fiz(size - replace_chars) {
			if (data[i] == end_search[0] && data[i+1] == end_search[1]) {
				data[i] = ' ';
				data[i+1] = ' ';
				if(has_cr) data[i+2] = ' ';
			}
		}
	}

	int lines = 0;
	zt_fiz(size) {
		if (data[i] == '\n') {
			lines += 1;
		}
	}

	ztToken *tokens = zt_mallocStructArray(ztToken, lines + 1);
	int tokens_count = zt_strTokenize(data, "\r\n", tokens, lines + 1, 0);

	if (tokens_count > lines + 1) {
		tokens_count = zt_min(tokens_count, lines + 1);
	}

	ztMaterial *mats = nullptr;
	int mats_count = 0;

	int verts_count = 0;
	int normals_count = 0;
	int tex_coords_count = 0;
	int indices_count = 0;
	bool has_uv_indices = false;
	bool has_norm_indices = false;

	ztToken l_tokens[128], i_tokens[128];

	bool first_face_entry = true;
	zt_fiz(tokens_count) {
		if (tokens[i].len <= 2) continue;

		char* line = data + tokens[i].beg;

		if (line[0] == 'v' && line[1] == ' ') verts_count += 1;
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') normals_count += 1;
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') tex_coords_count += 1;
		else if (line[0] == 'f' && line[1] == ' ') {
			int f_tokens = zt_strTokenize(line, tokens[i].len, " ", l_tokens, zt_elementsOf(l_tokens), 0);
			if (f_tokens < 4) {
				zt_assert(false);
			}
			int triangles = f_tokens - 3;
			indices_count += 3 * triangles;

			if (first_face_entry && f_tokens > 3) {
				first_face_entry = false;
				if (zt_strFindPos(line + l_tokens[1].beg, l_tokens[1].len, "//", 0) != ztStrPosNotFound) {
					has_norm_indices = true;
				}
				int count = zt_strCount(line + l_tokens[1].beg, l_tokens[1].len, "/");
				if (count >= 1) {
					has_uv_indices = true;
				}
			}
		}
		else if (line[0] == 'g' && line[1] == ' ') {
			//break;
		}
		else if (zt_strStartsWith(line, tokens[i].len, "mtllib ", 7)) {
			char mtl_name[128];
			zt_strCpy(mtl_name, zt_elementsOf(mtl_name), line + 7, tokens[i].len - 7);

			ztAssetID mtl_asset_id = zt_assetLoad(asset_mgr, mtl_name, asset_id);
			if (mtl_asset_id != ztInvalidID) {
				mats_count = zt_materialLoad(asset_mgr, mtl_asset_id, nullptr, 0);
				if(mats_count) {
					mats = zt_mallocStructArray(ztMaterial, mats_count);
					zt_fiz(mats_count) {
						mats[i] = zt_materialMake();
					}

					zt_materialLoad(asset_mgr, mtl_asset_id, mats, mats_count);
				}
			}
			else {
				zt_logCritical("Unable to locate material file '%s' while loading OBJ '%s'", mtl_name, asset_mgr->asset_name[asset_id]);
			}
		}
	}

	struct local
	{
		static r32 parseReal(const char* src, ztToken& token)
		{
			static char buffer[128];
			zt_strCpy(buffer, zt_elementsOf(buffer), src + token.beg, token.len);

			return zt_strToReal32(src + token.beg, token.len, 0.f);
		}

		static int parseInt(const char* src, ztToken& token)
		{
			static char buffer[128];
			strncpy_s(buffer, zt_elementsOf(buffer), src + token.beg, token.len);

			return zt_strToInt(src + token.beg, token.len, 0);
		}

		static ztMeshID applyToMesh(bool has_norm_indices, bool has_uv_indices, int indices_idx, int verts_idx, ztVec3 *verts, ztVec2 *uvs, ztVec3 *normals, u32 *uv_indices, u32 *normal_indices, u32 *indices, int indices_count)
		{
			if (has_norm_indices || has_uv_indices) {
				// we need to redo the vert/normal/uv arrays
				ztVec3* new_verts = zt_mallocStructArray(ztVec3, indices_idx);
				ztVec2* new_uvs = has_uv_indices ? zt_mallocStructArray(ztVec2, indices_idx) : nullptr;
				ztVec3* new_normals = has_norm_indices ? zt_mallocStructArray(ztVec3, indices_idx) : nullptr;

				for (int i = 0; i < indices_idx; ++i) {
					new_verts[i] = verts[indices[i]];
					if (new_uvs) {
						new_uvs[i] = uvs ? uvs[uv_indices[i]] : ztVec2::zero;
					}
					if (new_normals) {
						new_normals[i] = normals[normal_indices[i]];
					}
				}

				zt_logDebug("obj contains %d triangles", indices_idx / 3);

				ztMeshID mesh = zt_meshMake(new_verts, new_uvs, new_normals, indices_idx, nullptr, 0);

				zt_free(new_normals);
				zt_free(new_uvs);
				zt_free(new_verts);

				return mesh;
			}
			else {
				zt_logDebug("obj contains %d triangles", indices_idx / 3);
				return zt_meshMake(verts, uvs, normals, verts_idx, indices, indices_count);
			}
		}
	};

	if (verts_count == 0 || indices_count <= 0) {
		zt_logCritical("Invalid vertices or indices count");
		zt_free(data);
		return ztInvalidID;
	}

	ztVec3* verts = zt_mallocStructArray(ztVec3, verts_count);
	ztVec3* normals = normals_count > 0 ? zt_mallocStructArray(ztVec3, normals_count) : nullptr;
	ztVec2* uvs = tex_coords_count > 0 ? zt_mallocStructArray(ztVec2, tex_coords_count) : nullptr;
	u32* indices = zt_mallocStructArray(u32, indices_count);
	u32* normal_indices = has_norm_indices ? zt_mallocStructArray(u32, indices_count) : nullptr;
	u32* uv_indices = has_uv_indices ? zt_mallocStructArray(u32, indices_count) : nullptr;

	int verts_idx = 0;
	int normals_idx = 0;
	int uvs_idx = 0;
	int indices_idx = 0;

	int group_idx = 0;

	ztMeshID *curr_mesh_id = group_idx < mesh_mat_size ? &mesh_ids[group_idx] : nullptr;
	ztMaterial *curr_mat = group_idx < mesh_mat_size ? &materials[group_idx] : nullptr;

	if (curr_mat) {
		*curr_mat = zt_materialMake();
	}

	// first time around, get the verts/normals/uvs
	bool failed = false;
	for (int i = 0; i < tokens_count && !failed; ++i) {
		if (tokens[i].len <= 2) continue;
		char* line = data + tokens[i].beg;

		if (line[0] == '#') continue;

		int l_tokens_count = zt_strTokenize(line, tokens[i].len, " ", l_tokens, zt_elementsOf(l_tokens), 0);

		if (line[0] == 'v' && line[1] == ' ') {
			if (l_tokens_count < 4) {
				failed = true;
			}
			else {
				verts[verts_idx].x = offset.x + (scale.x * local::parseReal(line, l_tokens[1]));
				verts[verts_idx].y = offset.y + (scale.y * local::parseReal(line, l_tokens[2]));
				verts[verts_idx++].z = offset.z + (scale.z * local::parseReal(line, l_tokens[3]));
			}
		}
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			if (l_tokens_count < 4) {
				failed = true;
			}
			else {
				normals[normals_idx].x = local::parseReal(line, l_tokens[1]);
				normals[normals_idx].y = local::parseReal(line, l_tokens[2]);
				normals[normals_idx++].z = local::parseReal(line, l_tokens[3]);
			}
		}
		else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
			if (l_tokens_count < 3) {
				failed = true;
			}
			else {
				uvs[uvs_idx].x = local::parseReal(line, l_tokens[1]);
				uvs[uvs_idx++].y = 1 - local::parseReal(line, l_tokens[2]);
			}
		}
	}

	// second time around, populate the groups
	failed = false;
	int group_mtls = 0;
	for (int i = 0; i < tokens_count && !failed; ++i) {
		if (tokens[i].len <= 2) continue;
		char* line = data + tokens[i].beg;

		if (line[0] == '#') continue;

		int l_tokens_count = zt_strTokenize(line, tokens[i].len, " ", l_tokens, zt_elementsOf(l_tokens), 0);

		if (line[0] == 'f' && line[1] == ' ') {
			if (l_tokens_count < 4) {
				failed = true;
			}
			else if (l_tokens_count <= 64) {
				int triangles = l_tokens_count - 3;
				int vert_indexes[64] = { 0 };
				int norm_indexes[64] = { 0 };
				int uv_indexes[64] = { 0 };

				int indexes_idx = 0;

				for (int j = 1; j < l_tokens_count; ++j) {
					char* i_token_str = line + l_tokens[j].beg;
					int i_tokens_count = zt_strTokenize(i_token_str, l_tokens[j].len, "/", i_tokens, zt_elementsOf(i_tokens), 0);
					switch (i_tokens_count)
					{
						case 3: {	// vertex / uv / normal
							norm_indexes[indexes_idx] = local::parseInt(i_token_str, i_tokens[2]) - 1;
							uv_indexes[indexes_idx] = local::parseInt(i_token_str, i_tokens[1]) - 1;
							vert_indexes[indexes_idx++] = local::parseInt(i_token_str, i_tokens[0]) - 1;
						} break;

						case 2: {	// either vertex / uv or vertex // normal
							if (has_uv_indices) {
								uv_indexes[indexes_idx] = local::parseInt(i_token_str, i_tokens[1]) - 1;
							}
							else {
								norm_indexes[indexes_idx] = local::parseInt(i_token_str, i_tokens[1]) - 1;
							}
							vert_indexes[indexes_idx++] = local::parseInt(i_token_str, i_tokens[0]) - 1;
						} break;

						case 1: {	// vertex
							vert_indexes[indexes_idx++] = local::parseInt(i_token_str, i_tokens[0]) - 1;
						} break;
					}
				}

#				define _zt_assignIndexesToIndices(INDEX_IDX) \
					if (has_norm_indices) { normal_indices[indices_idx] = norm_indexes[INDEX_IDX]; } \
					if (has_uv_indices) { uv_indices[indices_idx] = uv_indexes[INDEX_IDX]; } \
					indices[indices_idx++] = vert_indexes[INDEX_IDX];

				for (int i = 0; i < triangles; ++i) {
					_zt_assignIndexesToIndices(0);
					_zt_assignIndexesToIndices(1 + i);
					_zt_assignIndexesToIndices(2 + i);
				}

#				undef _zt_assignIndexesToIndices
			}
		}
		else if (line[0] == 'g' && line[1] == ' ') {
			if (indices_idx != 0) {
				if (curr_mesh_id) {
					*curr_mesh_id = local::applyToMesh(has_norm_indices, has_uv_indices, indices_idx, verts_idx, verts, uvs, normals, uv_indices, normal_indices, indices, indices_count);
					indices_idx = 0;
				}
				group_idx += 1;
				group_mtls = 0;
				curr_mesh_id = group_idx < mesh_mat_size ? &mesh_ids[group_idx] : nullptr;
				curr_mat = group_idx < mesh_mat_size ? &materials[group_idx] : nullptr;

				if (curr_mat) {
					*curr_mat = zt_materialMake();
				}
			}
		}
		else if (tokens[i].len > 8) {
			if (zt_strStartsWith(line, tokens[i].len, "usemtl ", 7) && l_tokens_count > 1) {
				if (++group_mtls > 1 && indices_idx != 0) {
					if (curr_mesh_id) {
						*curr_mesh_id = local::applyToMesh(has_norm_indices, has_uv_indices, indices_idx, verts_idx, verts, uvs, normals, uv_indices, normal_indices, indices, indices_count);
						indices_idx = 0;
					}
					group_idx += 1;
					group_mtls = 0;
					curr_mesh_id = group_idx < mesh_mat_size ? &mesh_ids[group_idx] : nullptr;
					curr_mat = group_idx < mesh_mat_size ? &materials[group_idx] : nullptr;

					if (curr_mat) {
						*curr_mat = zt_materialMake();
					}
				}

				char mtl_name[128];
				zt_strCpy(mtl_name, zt_elementsOf(mtl_name), line + l_tokens[1].beg, l_tokens[1].len);

				zt_fkz(mats_count) {
					if (zt_strEquals(mats[k].name, mtl_name)) {
						if (curr_mat) {
							*curr_mat = mats[k];
						}
						break;
					}
				}
			}
		}
	}
	if(curr_mesh_id) {
		*curr_mesh_id = local::applyToMesh(has_norm_indices, has_uv_indices, indices_idx, verts_idx, verts, uvs, normals, uv_indices, normal_indices, indices, indices_count);
		group_idx += 1;
	}

	zt_free(indices);
	if (uvs != nullptr) zt_free(uvs);
	if (uv_indices != nullptr) zt_free(uv_indices);
	if (normals != nullptr) zt_free(normals);
	if (normal_indices != nullptr) zt_free(normal_indices);
	if (mats != nullptr) zt_free(mats);
	zt_free(verts);

	zt_free(tokens);
	zt_free(data);

	return group_idx;
}

// ------------------------------------------------------------------------------------------------

ztVec3 zt_meshGetAABB(ztMeshID mesh_id)
{
	zt_assertReturnValOnFail(mesh_id >= 0 && mesh_id < zt_game->meshes_count, ztVec3::zero);

	ztMesh *mesh = &zt_game->meshes[mesh_id];
	return mesh->aabb;
}

// ------------------------------------------------------------------------------------------------

void zt_meshGetOBB(ztMeshID mesh_id, ztVec3 *center, ztVec3 *size)
{
	zt_assertReturnOnFail(mesh_id >= 0 && mesh_id < zt_game->meshes_count);
	zt_returnOnNull(center);
	zt_returnOnNull(size);

	ztMesh *mesh = &zt_game->meshes[mesh_id];
	*center = mesh->obb_center;
	*size   = mesh->obb_size;
}

// ------------------------------------------------------------------------------------------------

void zt_meshRender(ztMeshID mesh_id)
{
	ZT_PROFILE_RENDERING("zt_meshRender");
	zt_assertReturnOnFail(mesh_id >= 0 && mesh_id < zt_game->meshes_count);

	ztMesh *mesh = &zt_game->meshes[mesh_id];
	zt_game->game_details.curr_frame.triangles_drawn += mesh->triangles;
	zt_game->game_details.curr_frame.draw_calls += 1;

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
			zt_openGLSupport(ztgl_vertexArrayDraw(mesh->gl_vertex_array));
		} break;

		case ztRenderer_DirectX: {
			zt_directxSupport(ztdx_vertexArrayDraw(zt_game->win_details[0].dx_context, mesh->dx_vertex_array));
		} break;

		default: {
			zt_assert(false);
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_rendererRequestProcess()
{
	ZT_PROFILE_RENDERING("_zt_rendererRequestProcess");
	int count = zt_game->renderer_requests_count;
	zt_game->renderer_requests_count = 0;

	zt_fiz(count) {
		auto* request = &zt_game->renderer_requests[i];
		switch(request->type)
		{
			case ztRendererRequest_Change: {
				zt_fiz(zt_game->win_count) {
					_zt_rendererFreeContext(&zt_game->win_details[i]);
				}

				if (request->change_to == ztRenderer_OpenGL) {
					zt_logInfo("Switching to OpenGL renderer");
				}
				else if (request->change_to == ztRenderer_DirectX) {
					zt_logInfo("Switching to DirectX renderer");
				}
				else {
					zt_assert(false && "Unknown renderer");
				}

				if (!_zt_rendererSetRendererFuncs(request->change_to)) {
					return false;
				}

				zt_fiz(zt_game->win_count) {
					zt_game->win_game_settings[i].renderer = request->change_to;
					if (!_zt_rendererMakeContext(&zt_game->win_details[i], &zt_game->win_game_settings[i], zt_game->win_game_settings[i].renderer_flags)) {
						zt_logCritical("Failed to switch renderer");
						return false;
					}
				}

			} break;

			case ztRendererRequest_Windowed: {
				zt_fiz(zt_game->win_count) {
					zt_bitRemove(zt_game->win_game_settings[i].renderer_flags, ztRendererFlags_Fullscreen);
					zt_game->win_game_settings[i].renderer_flags |= ztRendererFlags_Windowed;

					if (!_zt_rendererToggleFullscreen(&zt_game->win_details[i], &zt_game->win_game_settings[i], false))
						return false;
				}
			} break;

			case ztRendererRequest_Fullscreen: {
				zt_fiz(zt_game->win_count) {
					zt_bitRemove(zt_game->win_game_settings[i].renderer_flags, ztRendererFlags_Windowed);
					zt_game->win_game_settings[i].renderer_flags |= ztRendererFlags_Fullscreen;

					if (!_zt_rendererToggleFullscreen(&zt_game->win_details[i], &zt_game->win_game_settings[i], true))
						return false;
				}
			} break;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztdx_rendererSetViewport(ztWindowDetails* win_details, ztGameSettings *game_settings, bool force)
{
	ZT_PROFILE_RENDERING("_ztdx_rendererSetViewport");
#if defined(ZT_DIRECTX)
	return ztdx_setViewport(win_details->dx_context);
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztdx_rendererMakeContext(ztWindowDetails *win_details, ztGameSettings *game_settings, i32 renderer_flags)
{
	ZT_PROFILE_RENDERING("_ztdx_rendererMakeContext");
#	if defined(ZT_DIRECTX)
	win_details->dx_context = ztdx_contextMake(win_details->handle, game_settings->native_w, game_settings->native_h, game_settings->pixels_per_unit, renderer_flags);
	if (win_details->dx_context == nullptr) {
		return false;
	}
	
	ztVertexEntryDX entries[] = {
		3 * zt_sizeof(r32), // pos
		2 * zt_sizeof(r32), // uv
		3 * zt_sizeof(r32), // normals
		4 * zt_sizeof(r32), // color
	};

	win_details->dx_tri_verts_array = ztdx_vertexArrayMake(win_details->dx_context, entries, zt_elementsOf(entries), nullptr, ztRenderDrawListVertexArraySize);
	if (win_details->dx_tri_verts_array == nullptr) {
		return false;
	}
	
	return true;
#	endif
	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztdx_rendererFreeContext(ztWindowDetails *win_details)
{
	ZT_PROFILE_RENDERING("_ztdx_rendererFreeContext");
#	if defined(ZT_DIRECTX)
	ztdx_contextFree(win_details->dx_context);
	win_details->dx_context = nullptr;

	ztdx_vertexArrayFree(win_details->dx_tri_verts_array);
	win_details->dx_tri_verts_array = nullptr;

	return true;
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _ztdx_rendererSwapBuffers(ztWindowDetails* win_details)
{
	ZT_PROFILE_RENDERING("_ztdx_rendererSwapBuffers");
	zt_directxSupport(ztdx_contextDisplay(win_details->dx_context));
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztdx_rendererToggleFullscreen(ztWindowDetails* win_details, ztGameSettings *game_settings, bool fullscreen)
{
	ZT_PROFILE_RENDERING("_ztdx_rendererToggleFullscreen");
#if defined(ZT_DIRECTX)
	return _ztdx_rendererSetViewport(win_details, game_settings, true);
#else
	return false;
#endif
}

// ------------------------------------------------------------------------------------------------

ztInternal void _ztgl_rendererSwapBuffers(ztWindowDetails* wd)
{
	ZT_PROFILE_RENDERING("_ztgl_rendererSwapBuffers");
	ztgl_contextDisplay(wd->gl_context);
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztgl_rendererSetViewport(ztWindowDetails* wd, ztGameSettings*, bool)
{
	ZT_PROFILE_RENDERING("_ztgl_rendererSetViewport");
	return ztgl_setViewport(wd->gl_context);
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztgl_rendererMakeContext(ztWindowDetails* wd, ztGameSettings* gs, i32 flags)
{
	ZT_PROFILE_RENDERING("_ztgl_rendererMakeContext");
	wd->gl_context = ztgl_contextMake(zt_memGetGlobalArena(), wd->handle, gs->native_w, gs->native_h, gs->pixels_per_unit, flags);
#if !defined(ZT_DLL)
	if (wd->gl_context && zt_game->zt_dllSetOpenGLGlobals) {
		zt_dllSendOpenGLGlobals(zt_game->zt_dllSetOpenGLGlobals);
	}
#endif
	return wd->gl_context != nullptr;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztgl_rendererFreeContext(ztWindowDetails* wd)
{
	ZT_PROFILE_RENDERING("_ztgl_rendererFreeContext");
	ztgl_contextFree(wd->gl_context);
	wd->gl_context = nullptr;
	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _ztgl_rendererToggleFullscreen(ztWindowDetails* wd, ztGameSettings* gs, bool fullscreen)
{
	ZT_PROFILE_RENDERING("_ztgl_rendererToggleFullscreen");
	return ztgl_contextToggleFullscreen(wd->gl_context, fullscreen);
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_rendererSetRendererFuncs(ztRenderer_Enum renderer)
{
	if (renderer == ztRenderer_OpenGL) {
#if defined(ZT_OPENGL)
		_zt_rendererSwapBuffers      = _ztgl_rendererSwapBuffers;
		_zt_rendererSetViewport      = _ztgl_rendererSetViewport;
		_zt_rendererMakeContext      = _ztgl_rendererMakeContext;
		_zt_rendererFreeContext      = _ztgl_rendererFreeContext;
		_zt_rendererToggleFullscreen = _ztgl_rendererToggleFullscreen;
#else
		zt_logFatal("OpenGL is not supported in this configuration");
		return false;
#endif
	}
	else if (renderer == ztRenderer_DirectX) {
#if defined(ZT_DIRECTX)
		_zt_rendererSwapBuffers      = _ztdx_rendererSwapBuffers;
		_zt_rendererSetViewport      = _ztdx_rendererSetViewport;
		_zt_rendererMakeContext      = _ztdx_rendererMakeContext;
		_zt_rendererFreeContext      = _ztdx_rendererFreeContext;
		_zt_rendererToggleFullscreen = _ztdx_rendererToggleFullscreen;
#else
		zt_logFatal("DirectX is not supported in this configuration");
		return false;
#endif
	}
	else {
		return false;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztCollisionGeometry zt_collisionGeometryMakeAABB(const ztVec3& extents)
{
	ztCollisionGeometry cg;
	cg.type = ztCollisionGeometryType_AxisAlignedBox;
	cg.aabb_extents = extents;
	return cg;
}

// ------------------------------------------------------------------------------------------------

ztCollisionGeometry zt_collisionGeometryMakeOBB(const ztVec3& center, const ztVec3& extents)
{
	ztCollisionGeometry cg;
	cg.type = ztCollisionGeometryType_OrientedBox;
	cg.obb_center = center;
	cg.obb_extents = extents;
	return cg;
}

// ------------------------------------------------------------------------------------------------

ztCollisionGeometry zt_collisionGeometryMakeSphere(const ztVec3& center, r32 radius)
{
	ztCollisionGeometry cg;
	cg.type = ztCollisionGeometryType_Sphere;
	cg.sphere_center = center;
	cg.sphere_radius = radius;
	return cg;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionGeometryIntersecting(ztCollisionGeometry *geo_one, ztTransform *curr_tran_one, ztTransform *prev_tran_one, ztCollisionGeometry *geo_two, ztTransform *curr_tran_two, ztTransform *prev_tran_two, r32 *penetration)
{
	ZT_PROFILE_PHYSICS("zt_collisionGeometryIntersecting");
	zt_returnValOnNull(geo_one, false);
	zt_returnValOnNull(curr_tran_one, false);
	//zt_returnValOnNull(prev_tran_one, false);
	zt_returnValOnNull(geo_two, false);
	zt_returnValOnNull(curr_tran_two, false);
	//zt_returnValOnNull(prev_tran_two, false);

	switch(geo_one->type)
	{
		case ztCollisionGeometryType_AxisAlignedBox: {
			switch(geo_two->type)
			{
				case ztCollisionGeometryType_AxisAlignedBox: {
					return zt_collisionAABBInAABB(curr_tran_one->position, geo_one->aabb_extents, curr_tran_two->position, geo_two->aabb_extents);
				} break;

				default: {
					zt_assert(false);
				}
			}
		} break;

		case ztCollisionGeometryType_OrientedBox: {
			switch(geo_two->type)
			{
				case ztCollisionGeometryType_OrientedBox: {
					if(zt_collisionOBBInOBB(curr_tran_one->position + geo_one->obb_center, geo_one->obb_extents, curr_tran_one->rotation, curr_tran_two->position + geo_two->obb_center, geo_two->obb_extents, curr_tran_two->rotation)) {
						ztVec3 contacts[16];
						int contacts_count = zt_collisionOBBInOBBGetContactPoints(curr_tran_one->position + geo_one->obb_center, geo_one->obb_extents, curr_tran_one->rotation, curr_tran_two->position + geo_two->obb_center, geo_two->obb_extents, curr_tran_two->rotation, contacts, zt_elementsOf(contacts));
						ztVec3 average(0,0,0);
						zt_fiz(contacts_count) {
							average += contacts[i] - curr_tran_one->position;
						}
						if(contacts_count) {
							average *= 1.f / contacts_count;
						}

						*penetration = zt_abs(average.distance(ztVec3::zero)) * .2f;
						return true;
					}
				} break;

				default: {
					zt_assert(false);
				}
			}
		} break;

		default: {
			zt_assert(false);
		}
	}

	return false;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztRigidBody zt_rigidBodyMake(ztModel *model, r32 one_over_mass_in_kg, ztCollisionGeometry cg_bounding, ztCollisionGeometry details, r32 damping, ztVec3 force_gravity)
{
	return zt_rigidBodyMake(model, one_over_mass_in_kg, cg_bounding, &details, 1, damping, force_gravity);
}

// ------------------------------------------------------------------------------------------------

ztRigidBody zt_rigidBodyMake(ztModel *model, r32 one_over_mass_in_kg, ztCollisionGeometry cg_bounding, ztCollisionGeometry *details, int details_count, r32 damping, ztVec3 force_gravity)
{
	ZT_PROFILE_PHYSICS("zt_rigidBodyMake");
	ztRigidBody result;
	result.model                  = model;
	result.velocity               = ztVec3::zero;
	result.angular_velocity       = ztVec3::zero;
	result.acceleration           = ztVec3::zero;
	result.force_accum            = ztVec3::zero;
	result.torque_accum           = ztVec3::zero;
	result.damping                = damping;
	result.angular_damping        = damping;
	result.inverse_mass           = one_over_mass_in_kg;
	result.force_gravity          = force_gravity;
	result.prev_acceleration      = ztVec3::zero;
	result.flags                   = 0;

	result.cg_bounding = cg_bounding;
	result.cg_details_count = details_count;

	zt_fiz(details_count) {
		result.cg_details[i] = details[i];
	}

	if(model->calculated_mat == ztMat4::identity) {
		result.flags |= ztRigidBodyFlags_NeedsMatrixCalc;
	}

	zt_staticAssert(zt_sizeof(ztRigidBody) == (ztPointerSize * 1) + (zt_sizeof(ztCollisionGeometry) * (1 + ZT_MAX_RIGID_BODY_COLLISION_GEOMETRIES)) + 109); // if this fails, more fields were added to ztRigidBody so update this function!

	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_rigidBodiesUpdate(ztRigidBody *rbs, int rbs_count, r32 dt)
{
	ZT_PROFILE_PHYSICS("zt_rigidBodiesUpdate");
	if(dt <= 0) return;

	zt_fiz(rbs_count) {
		ztRigidBody *rigid_body = &rbs[i];

		if (rigid_body->inverse_mass != 0) {
			// apply gravity
			if(rigid_body->force_gravity != ztVec3::zero) rigid_body->force_accum += rigid_body->force_gravity * (1.f / rigid_body->inverse_mass);

			rigid_body->prev_acceleration = rigid_body->acceleration;
			rigid_body->acceleration = (rigid_body->force_accum * rigid_body->inverse_mass);

			if(zt_bitIsSet(rigid_body->flags, ztRigidBodyFlags_NeedsMatrixCalc)) {
				zt_modelCalcMatrix(rigid_body->model);
				zt_bitRemove(rigid_body->flags, ztRigidBodyFlags_NeedsMatrixCalc);
			}

			ztMat4 *pmat = &rigid_body->model->calculated_mat;
			ztMat4 mat(/* col 0 */pmat->values[0], pmat->values[1], pmat->values[2], 0,
					   /* col 1 */pmat->values[4], pmat->values[5], pmat->values[6], 0,
					   /* col 2 */pmat->values[8], pmat->values[9], pmat->values[10], 0,
					   /* col 3 */0, 0, 0, 0);

			ztVec3 angular_acceleration = mat * rigid_body->torque_accum;

			rigid_body->velocity += rigid_body->acceleration * dt;
			rigid_body->angular_velocity += angular_acceleration * dt;

			//rigid_body->acceleration = rigid_body->force_accum * rigid_body->inverse_mass;

			// apply drag
			rigid_body->velocity *= zt_pow(rigid_body->damping, dt);
			rigid_body->angular_velocity *= zt_pow(rigid_body->angular_damping, dt);

			// apply velocities
			rigid_body->model->transform.position += rigid_body->velocity * dt;
			rigid_body->model->transform.rotation = ztQuat::makeFromEuler(rigid_body->angular_velocity * dt) * rigid_body->model->transform.rotation;

			// may want to recalc model matrices here

			// clear force accumulators
			rigid_body->force_accum = ztVec3::zero;
			rigid_body->torque_accum = ztVec3::zero;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_rigidBodyAddForce(ztRigidBody *rigid_body, const ztVec3& force)
{
	ZT_PROFILE_PHYSICS("zt_rigidBodyAddForce");
	zt_returnOnNull(rigid_body);
	rigid_body->force_accum += force;
}

// ------------------------------------------------------------------------------------------------

void zt_rigidBodyAddForceAtWorldPoint(ztRigidBody *rigid_body, const ztVec3& force, const ztVec3& point)
{
	ZT_PROFILE_PHYSICS("zt_rigidBodyAddForceAtWorldPoint");
	zt_returnOnNull(rigid_body);

	ztVec3 point_world = rigid_body->model->calculated_mat * point;
	zt_rigidBodyAddForceAtBodyPoint(rigid_body, force, point_world);
}

// ------------------------------------------------------------------------------------------------

void zt_rigidBodyAddForceAtBodyPoint(ztRigidBody *rigid_body, const ztVec3& force, const ztVec3& point)
{
	ZT_PROFILE_PHYSICS("zt_rigidBodyAddForceAtBodyPoint");
	zt_returnOnNull(rigid_body);

	rigid_body->force_accum += force;
	rigid_body->torque_accum += point.cross(force);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztForceAnchor zt_forceAnchor(ztRigidBody *rigid_body, const ztVec3& connection_point)
{
	ZT_PROFILE_PHYSICS("zt_forceAnchor");
	zt_assert(rigid_body != nullptr);
	ztForceAnchor anchor;
	anchor.type = ztForceAnchorType_RigidBody;
	anchor.rigid_body = rigid_body;
	anchor.connection_point = connection_point;
	return anchor;
}

// ------------------------------------------------------------------------------------------------

ztForceAnchor zt_forceAnchor(ztTransform *transform)
{
	ZT_PROFILE_PHYSICS("zt_forceAnchor");
	zt_assert(transform != nullptr);
	ztForceAnchor anchor;
	anchor.type = ztForceAnchorType_Transform;
	anchor.transform = transform;
	return anchor;
}

// ------------------------------------------------------------------------------------------------

ztForceAnchor zt_forceAnchor(ztVec3 *vec3_ptr)
{
	ZT_PROFILE_PHYSICS("zt_forceAnchor");
	zt_assert(vec3_ptr != nullptr);
	ztForceAnchor anchor;
	anchor.type = ztForceAnchorType_Vec3Ptr;
	anchor.vec3_ptr = vec3_ptr;
	return anchor;
}

// ------------------------------------------------------------------------------------------------

ztForceAnchor zt_forceAnchor(ztVec3 vec3)
{
	ZT_PROFILE_PHYSICS("zt_forceAnchor");
	ztForceAnchor anchor;
	anchor.type = ztForceAnchorType_Vec3;
	anchor.vec3 = vec3;
	return anchor;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztForce zt_forceMakeSpring(ztRigidBody *rigid_body, const ztVec3& connection_point, ztForceAnchor anchor, r32 spring_constant, r32 rest_length)
{
	ZT_PROFILE_PHYSICS("zt_forceMakeSpring");
	zt_assert(rigid_body != nullptr);

	ztForce force;
	force.type                   = ztForceType_Spring;
	force.rigid_body             = rigid_body;
	force.connection_point       = connection_point;
	force.anchor                 = anchor;
	force.spring.spring_constant = spring_constant;
	force.spring.rest_length     = rest_length;

	return force;
}

// ------------------------------------------------------------------------------------------------

ztForce zt_forceMakeStiffSpring(ztRigidBody *rigid_body, const ztVec3& connection_point, ztForceAnchor anchor, r32 spring_constant, r32 damping)
{
	ZT_PROFILE_PHYSICS("zt_forceMakeStiffSpring");
	zt_assert(rigid_body != nullptr);

	ztForce force;
	force.type                         = ztForceType_StiffSpring;
	force.rigid_body                   = rigid_body;
	force.connection_point       = connection_point;
	force.anchor                       = anchor;
	force.stiff_spring.spring_constant = spring_constant;
	force.stiff_spring.damping         = damping;

	return force;
}

// ------------------------------------------------------------------------------------------------

ztForce zt_forceMakeBungee(ztRigidBody *rigid_body, const ztVec3& connection_point, ztForceAnchor anchor, r32 spring_constant, r32 rest_length)
{
	ZT_PROFILE_PHYSICS("zt_forceMakeBungee");
	zt_assert(rigid_body != nullptr);

	ztForce force;
	force.type                   = ztForceType_Bungee;
	force.rigid_body             = rigid_body;
	force.connection_point       = connection_point;
	force.anchor                 = anchor;
	force.spring.spring_constant = spring_constant;
	force.spring.rest_length     = rest_length;

	return force;
}

// ------------------------------------------------------------------------------------------------

ztForce zt_forceMakeBuoyancy(ztRigidBody *rigid_body, const ztVec3& connection_point, r32 max_depth, r32 volume, r32 water_height, r32 liquid_density)
{
	ZT_PROFILE_PHYSICS("zt_forceMakeBuoyancy");
	zt_assert(rigid_body != nullptr);

	ztForce force;
	force.type                    = ztForceType_Buoyancy;
	force.rigid_body              = rigid_body;
	force.connection_point       = connection_point;
	force.buoyancy.max_depth      = max_depth;
	force.buoyancy.volume         = volume;
	force.buoyancy.water_height   = water_height;
	force.buoyancy.liquid_density = liquid_density;

	return force;
}

// ------------------------------------------------------------------------------------------------

void zt_forcesUpdate(ztForce *forces, int forces_count, r32 dt)
{
	ZT_PROFILE_PHYSICS("zt_forcesUpdate");
	ztVec3 force_to_apply;

	zt_fiz(forces_count) {
		ztForce *force = &forces[i];

		ztVec3 point_body = force->rigid_body->model->calculated_mat * force->connection_point;

#		define getAnchor(force) (force->anchor.type == ztForceAnchorType_RigidBody ? force->anchor.rigid_body->model->calculated_mat * force->anchor.connection_point : \
								(force->anchor.type == ztForceAnchorType_Transform ? force->anchor.transform->position : \
								(force->anchor.type == ztForceAnchorType_Vec3Ptr ? *force->anchor.vec3_ptr : force->anchor.vec3)))

		switch (force->type)
		{
			case ztForceType_Spring: {
				force_to_apply = point_body - getAnchor(force);

				r32 magnitude = force_to_apply.length();
				magnitude = (magnitude - force->spring.rest_length) * force->spring.spring_constant;

				force_to_apply.normalize();
				force_to_apply *= -magnitude;
			} break;

			// ------------------------------------------------------------------------------------

			case ztForceType_StiffSpring: {
				ztVec3 position = point_body;
				ztVec3 anchor = getAnchor(force);
				position -= anchor;

				r32 gamma = .5f * zt_sqrt(4 * force->stiff_spring.spring_constant - force->stiff_spring.damping * force->stiff_spring.damping);
				if (gamma != 0.f) {
					ztVec3 c = position * (force->stiff_spring.damping / (2.f * gamma)) + force->rigid_body->velocity * (1.f / gamma);
					ztVec3 target = position * zt_cos(gamma * dt) + c * zt_sin(gamma * dt);
					target *= zt_exp(-.5f * dt * force->stiff_spring.damping);

					ztVec3 accel = (target - position) * (1.f / dt * dt) - force->rigid_body->velocity * dt;
					force_to_apply = accel * (1.f / force->rigid_body->inverse_mass * (1.f / dt));
				}
			} break;

			// ------------------------------------------------------------------------------------

			case ztForceType_Bungee: {
				force_to_apply = point_body - getAnchor(force);

				r32 magnitude = force_to_apply.length();
				if (magnitude > force->spring.rest_length) {
					magnitude = (magnitude - force->spring.rest_length) * force->spring.spring_constant;

					force_to_apply.normalize();
					force_to_apply *= -magnitude;
				}
			} break;

			// ------------------------------------------------------------------------------------

			case ztForceType_Buoyancy: {
				r32 depth = point_body.y;
				if (depth < force->buoyancy.water_height + force->buoyancy.max_depth) {
					if (depth < force->buoyancy.water_height - force->buoyancy.max_depth) {
						force_to_apply.y = force->buoyancy.liquid_density * force->buoyancy.volume;
					}
					else {
						force_to_apply.y = force->buoyancy.liquid_density * force->buoyancy.volume * (depth - force->buoyancy.max_depth - force->buoyancy.water_height) / 2.f * force->buoyancy.max_depth;
					}
				}
			} break;

			// ------------------------------------------------------------------------------------

			default: {
				zt_assert(false);
			}
		}

		force->rigid_body->force_accum += force_to_apply;
		force->rigid_body->torque_accum += point_body.cross(force_to_apply);

#		undef getAnchor
	}
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


void zt_rigidBodyCollisionsResolve(ztRigidBodyCollision *collisions, int collisions_count, r32 dt, int max_iterations)
{
	ZT_PROFILE_PHYSICS("zt_rigidBodyCollisionsResolve");
	int iterations = 0;
	while(iterations++ < max_iterations) {
		int max_idx = -1;
		r32 max_separating_velocity = 0;

		zt_fiz(collisions_count) {
			ztRigidBodyCollision *collision = &collisions[i];

			ztVec3 relative_velocity = collision->rigid_bodies[0]->velocity;
			if (collision->rigid_bodies[1]) relative_velocity += collision->rigid_bodies[1]->velocity;

			r32 separating_velocity = relative_velocity.dot(collision->contact_normal);

			if(separating_velocity < max_separating_velocity) {
				max_separating_velocity = separating_velocity;
				max_idx = i;
			}
		}

		if(max_idx < 0) {
			break;
		}

		ztRigidBodyCollision *collision = &collisions[max_idx];
		r32 separating_velocity = max_separating_velocity;

		if(separating_velocity <= 0) {
			r32 new_separating_velocity = -separating_velocity * collision->restitution;

			ztVec3 accel_caused_velocity = collision->rigid_bodies[0]->acceleration;
			if(collision->rigid_bodies[1]) accel_caused_velocity -= collision->rigid_bodies[1]->acceleration;
			r32 accel_caused_sep_velocity = accel_caused_velocity.dot(collision->contact_normal) * dt;

			if(accel_caused_sep_velocity < 0) {
				new_separating_velocity += collision->restitution * accel_caused_sep_velocity;
				if (new_separating_velocity < 0) {
					new_separating_velocity = 0;
				}
			}

			r32 delta_velocity = new_separating_velocity - separating_velocity;
			r32 total_inverse_mass = collision->rigid_bodies[0]->inverse_mass;
			if(collision->rigid_bodies[1]) total_inverse_mass += collision->rigid_bodies[1]->inverse_mass;

			if(total_inverse_mass > 0) {
				r32 impulse = delta_velocity / total_inverse_mass;
				ztVec3 impulse_per_invmass = collision->contact_normal * impulse;

				collision->rigid_bodies[0]->velocity += impulse_per_invmass * collision->rigid_bodies[0]->inverse_mass;
				if(collision->rigid_bodies[1]) collision->rigid_bodies[1]->velocity += impulse_per_invmass * -collision->rigid_bodies[1]->inverse_mass;

				if(collision->penetration != 0) {
					//ztVec3 move_per_invmass = collision->contact_normal * (-collision->penetration / total_inverse_mass);
					//collision->rigid_bodies[0]->model->transform.position += move_per_invmass * collision->rigid_bodies[0]->inverse_mass;
					//if(collision->rigid_bodies[1]) collision->rigid_bodies[1]->model->transform.position -= (move_per_invmass * -1) * collision->rigid_bodies[1]->inverse_mass;
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztConnector zt_connectorMakeCable(r32 max_length, r32 restitution)
{
	ZT_PROFILE_PHYSICS("zt_connectorMakeCable");
	ztConnector connector;
	connector.type = ztConnectorType_Cable;
	connector.cable.max_length = max_length;
	connector.cable.restitution = restitution;
	return connector;
}

// ------------------------------------------------------------------------------------------------

ztConnector zt_connectorMakeRod(r32 length)
{
	ZT_PROFILE_PHYSICS("zt_connectorMakeRod");
	ztConnector connector;
	connector.type = ztConnectorType_Rod;
	connector.rod.length = length;
	return connector;
}

// ------------------------------------------------------------------------------------------------

int zt_connectorCalculateCollisions(ztConnector *connectors, int connectors_count, ztRigidBodyCollision *collisions, int collisions_size)
{
	ZT_PROFILE_PHYSICS("zt_connectorCalculateCollisions");
	zt_assert(collisions != nullptr && collisions_size > 0);

	int collisions_idx = 0;

	zt_fiz(connectors_count) {
		ztConnector *connector = &connectors[i];

		ztVec3 relative_pos = connector->rigid_bodies[0]->model->transform.position - connector->rigid_bodies[1]->model->transform.position;
		r32 length = relative_pos.length();

		switch(connector->type)
		{
			case ztConnectorType_Cable: {
				if(length > connector->cable.max_length) {
					ztRigidBodyCollision *collision = &collisions[collisions_idx++];
					collision->rigid_bodies[0] = connector->rigid_bodies[0];
					collision->rigid_bodies[1] = connector->rigid_bodies[1];

					collision->contact_normal = connector->rigid_bodies[1]->model->transform.position - connector->rigid_bodies[1]->model->transform.position;
					collision->contact_normal.normalize();
					collision->penetration = length - connector->cable.max_length;
					collision->restitution = connector->cable.restitution;

					if(collisions_idx >= collisions_size) return collisions_idx;
				}
			} break;

			case ztConnectorType_Rod: {
				if(!zt_real32Eq(length, connector->rod.length)) {
					ztRigidBodyCollision *collision = &collisions[collisions_idx++];
					collision->rigid_bodies[0] = connector->rigid_bodies[0];
					collision->rigid_bodies[1] = connector->rigid_bodies[1];

					collision->contact_normal = connector->rigid_bodies[1]->model->transform.position - connector->rigid_bodies[1]->model->transform.position;
					collision->contact_normal.normalize();

					if(length < connector->rod.length) {
						collision->contact_normal *= -1;
						collision->penetration = connector->rod.length - length;
					}
					else {
						collision->penetration = length - connector->rod.length;
					}

					collision->restitution = 0;

					if(collisions_idx >= collisions_size) return collisions_idx;
				}
			} break;
		}
	}

	return collisions_idx;
}

// ------------------------------------------------------------------------------------------------

int zt_collisionBrute(ztRigidBody *rigid_bodies, int rigid_bodies_count, ztRigidBodyCollision *collisions, int collisions_size)
{
	ZT_PROFILE_PHYSICS("zt_collisionBrute");
	int col_idx = 0;
	zt_fiz(rigid_bodies_count - 1) {
		for(int j = i + 1; j < rigid_bodies_count; ++j) {
			if(zt_collisionGeometryIntersecting(&rigid_bodies[i].cg_bounding, &rigid_bodies[i].model->transform, nullptr, &rigid_bodies[j].cg_bounding, &rigid_bodies[j].model->transform, nullptr, nullptr)) {
				// bounding volumes are colliding, now check actual collision geometry

				zt_fxz(rigid_bodies[i].cg_details_count) {
					zt_fyz(rigid_bodies[j].cg_details_count) {
						r32 penetration = 0;
						if(zt_collisionGeometryIntersecting(&rigid_bodies[i].cg_details[x], &rigid_bodies[i].model->transform, nullptr, &rigid_bodies[j].cg_details[y], &rigid_bodies[j].model->transform, nullptr, &penetration)) {
							if(col_idx < collisions_size) {
								collisions[col_idx].rigid_bodies[0] = &rigid_bodies[i];
								collisions[col_idx].rigid_bodies[1] = &rigid_bodies[j];
								collisions[col_idx].restitution     = .5f;
								collisions[col_idx].penetration     = penetration;
								collisions[col_idx].contact_normal  = rigid_bodies[i].model->transform.position - rigid_bodies[j].model->transform.position;
								collisions[col_idx].contact_normal.normalize();
								col_idx += 1;
							}
							else return col_idx;
							goto exit_detail_loop;
						}
					}
				}

			exit_detail_loop:
				;
			}
		}
	}

	return col_idx;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztPhysics *zt_physicsMake(ztMemoryArena *arena, int max_rigid_bodies, int max_forces, int max_connectors)
{
	ZT_PROFILE_PHYSICS("zt_physicsMake");
	ztPhysics *physics = zt_mallocStructArena(ztPhysics, arena);

	physics->arena = arena;

	physics->rigid_bodies_count = 0;
	physics->rigid_bodies_size  = max_rigid_bodies;
	physics->rigid_bodies       = zt_mallocStructArrayArena(ztRigidBody, physics->rigid_bodies_size, arena);

	physics->forces_count       = 0;
	physics->forces_size        = max_forces;
	physics->forces             = zt_mallocStructArrayArena(ztForce, physics->forces_size, arena);

	physics->connectors_count   = 0;
	physics->connectors_size    = max_connectors;
	physics->connectors         = zt_mallocStructArrayArena(ztConnector, physics->connectors_size, arena);

	physics->collisions_size    = 2048;
	physics->collisions         = zt_mallocStructArrayArena(ztRigidBodyCollision, physics->collisions_size, arena);

	if(physics->rigid_bodies == nullptr || physics->forces == nullptr || physics->connectors == nullptr || physics->collisions == nullptr) {
		zt_physicsFree(physics);
		return nullptr;
	}

	physics->extents_min = ztVec3::min;
	physics->extents_max = ztVec3::max;
	physics->extents_restitution = .5f;

	return physics;
}

// ------------------------------------------------------------------------------------------------

void zt_physicsFree(ztPhysics *physics)
{
	ZT_PROFILE_PHYSICS("zt_physicsFree");
	if (physics == nullptr) {
		return;
	}

	if (physics->rigid_bodies) zt_freeArena(physics->rigid_bodies, physics->arena);
	if (physics->forces      ) zt_freeArena(physics->forces, physics->arena);
	if (physics->connectors  ) zt_freeArena(physics->connectors, physics->arena);
	if (physics->collisions  ) zt_freeArena(physics->collisions, physics->arena);

	zt_freeArena(physics, physics->arena);
}

// ------------------------------------------------------------------------------------------------

int zt_physicsAddRigidBody(ztPhysics *physics, ztRigidBody *rigid_body)
{
	ZT_PROFILE_PHYSICS("zt_physicsAddRigidBody");
	zt_returnValOnNull(physics, -1);
	zt_returnValOnNull(rigid_body, -1);

	zt_assertReturnValOnFail(physics->rigid_bodies_count < physics->rigid_bodies_size, -1);

	physics->rigid_bodies[physics->rigid_bodies_count] = *rigid_body;
	return physics->rigid_bodies_count++;
}

// ------------------------------------------------------------------------------------------------

int zt_physicsAddForce(ztPhysics *physics, ztForce *force)
{
	ZT_PROFILE_PHYSICS("zt_physicsAddForce");
	zt_returnValOnNull(physics, -1);
	zt_returnValOnNull(force, -1);

	zt_assertReturnValOnFail(physics->forces_count < physics->forces_size, -1);
	physics->forces[physics->forces_count] = *force;
	return physics->forces_count++;
}

// ------------------------------------------------------------------------------------------------

int zt_physicsAddConnector(ztPhysics *physics, ztConnector *connector)
{
	ZT_PROFILE_PHYSICS("zt_physicsAddConnector");
	zt_returnValOnNull(physics, -1);
	zt_returnValOnNull(connector, -1);

	zt_assertReturnValOnFail(physics->connectors_count < physics->connectors_size, -1);
	physics->connectors[physics->connectors_count] = *connector;
	return physics->connectors_count++;
}

// ------------------------------------------------------------------------------------------------

void zt_physicsUpdate(ztPhysics *physics, r32 dt)
{
	ZT_PROFILE_PHYSICS("zt_physicsUpdate");
	zt_rigidBodiesUpdate(physics->rigid_bodies, physics->rigid_bodies_count, dt);

	int collisions_count = 0;

#	define zt_checkCollisionsCount \
		{ \
			if(collisions_count >= physics->collisions_size) { \
				zt_arrayResizeArenaNoCopy(physics->collisions, ztRigidBodyCollision, physics->collisions_size * 2, physics->arena); \
				if(physics->collisions == nullptr) { \
					zt_logCritical("unable to resize physics collision cache"); \
					physics->collisions = zt_mallocStructArrayArena(ztRigidBodyCollision, physics->collisions_size, physics->arena); \
					break; \
				} \
				else { \
					zt_logDebug("physics resized collision cache from %d to %d", physics->collisions_size, physics->collisions_size * 2); \
					physics->collisions_size *= 2; \
				} \
			} \
		}

	if(physics->extents_min != ztVec3::min) {
		zt_fjz(3) {
			if(physics->extents_min.values[j] == ztReal32Min) {
				continue;
			}

			zt_fiz(physics->rigid_bodies_count) {
				if (physics->rigid_bodies[i].model->transform.position.values[j] < physics->extents_min.values[j]) {
					zt_checkCollisionsCount;
					ztRigidBodyCollision * collision = &physics->collisions[collisions_count++];

					collision->rigid_bodies[0] = &physics->rigid_bodies[i];
					collision->rigid_bodies[1] = nullptr;
					collision->contact_normal = ztVec3(j == 0 ? 1.f : 0.f, j == 1 ? 1.f : 0.f, j == 2 ? 1.f : 0.f);
					collision->penetration = physics->rigid_bodies[i].model->transform.position.values[j] - physics->extents_min.values[j];
					collision->restitution = physics->extents_restitution;
				}
			}
		}
	}

	if(physics->extents_max != ztVec3::max) {
		zt_fjz(3) {
			if(physics->extents_max.values[j] == ztReal32Max) {
				continue;
			}

			zt_fiz(physics->rigid_bodies_count) {
				if (physics->rigid_bodies[i].model->transform.position.values[j] > physics->extents_max.values[j]) {
					zt_checkCollisionsCount;
					ztRigidBodyCollision * collision = &physics->collisions[collisions_count++];

					collision->rigid_bodies[0] = &physics->rigid_bodies[i];
					collision->rigid_bodies[1] = nullptr;
					collision->contact_normal = ztVec3(j == 0 ? -1.f : 0.f, j == 1 ? -1.f : 0.f, j == 2 ? -1.f : 0.f);
					collision->penetration = physics->extents_max.values[j] - physics->rigid_bodies[i].model->transform.position.values[j];
					collision->restitution = physics->extents_restitution;
				}
			}
		}
	}

	collisions_count += zt_collisionBrute(physics->rigid_bodies, physics->rigid_bodies_count, physics->collisions + collisions_count, physics->collisions_size - collisions_count);

#	undef zt_checkCollisionsCount

	if (collisions_count > 0) {
		zt_rigidBodyCollisionsResolve(physics->collisions, collisions_count, dt, zt_convertToi32Floor(collisions_count * 1.25f));
	}
}

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool zt_collisionPointInRect(const ztVec2& point, const ztVec2& rect_pos, const ztVec2& rect_size)
{
	return zt_collisionPointInRect(point.x, point.y, rect_pos.x, rect_pos.y, rect_size.x, rect_size.y);
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionPointInRect(r32 p_x, r32 p_y, r32 rect_x, r32 rect_y, r32 rect_w, r32 rect_h)
{
	return zt_collisionPointInRectLL(p_x, p_y, rect_x - rect_w / 2.f, rect_y - rect_h / 2.f, rect_w, rect_h);
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionPointInRectLL(const ztVec2& point, const ztVec2& rect_pos, const ztVec2& rect_size)
{
	return zt_collisionPointInRectLL(point.x, point.y, rect_pos.x, rect_pos.y, rect_size.x, rect_size.y);
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionPointInRectLL(r32 p_x, r32 p_y, r32 rect_x, r32 rect_y, r32 rect_w, r32 rect_h)
{
	ZT_PROFILE_PHYSICS("zt_collisionPointInRectLL");
	return !(p_x < rect_x || p_y < rect_y || p_x > rect_x + rect_w || p_y > rect_y + rect_h);
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionLineInPlane(const ztVec3& line_beg, const ztVec3& line_end, const ztVec3& plane_coord, const ztVec3& plane_normal, ztVec3 *intersection_point)
{
	ZT_PROFILE_PHYSICS("zt_collisionLineInPlane");
	ztVec3 line_dir = (line_end - line_beg);

	r32 dot = plane_normal.dot(plane_coord);
	if(plane_normal.dot(line_dir) == 0) {
		// line is parallel
		return false;
	}

	r32 x = (dot - plane_normal.dot(line_beg)) / plane_normal.dot(line_dir);
	if(x < 0 - ztReal32Epsilon || x > 1 + ztReal32Epsilon) {
		return false;
	}

	if(intersection_point) {
		*intersection_point = line_beg + (line_dir * ztVec3(x, x, x));
	}
	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionPointInAABB(const ztVec3& point, const ztVec3& aabb_center, const ztVec3& aabb_extents)
{
	ZT_PROFILE_PHYSICS("zt_collisionPointInAABB");
	return point.x >= aabb_center.x - aabb_extents.x / 2.f && point.x <= aabb_center.x + aabb_extents.x / 2.f &&
		point.y >= aabb_center.y - aabb_extents.y / 2.f && point.y <= aabb_center.y + aabb_extents.y / 2.f &&
		point.z >= aabb_center.z - aabb_extents.z / 2.f && point.z <= aabb_center.z + aabb_extents.z / 2.f;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionRayInAABB(const ztVec3& point, const ztVec3& direction, const ztVec3& aabb_center, const ztVec3& aabb_extents, ztVec3 *intersection_point)
{
	ZT_PROFILE_PHYSICS("zt_collisionRayInAABB");
	r32 tmin = 0;
	r32 tmax = ztReal32Max;

	ztVec3 aabb_min(aabb_center.x - (aabb_extents.x / 2.f), aabb_center.y - (aabb_extents.y / 2.f), aabb_center.z - (aabb_extents.z / 2.f));
	ztVec3 aabb_max(aabb_center.x + (aabb_extents.x / 2.f), aabb_center.y + (aabb_extents.y / 2.f), aabb_center.z + (aabb_extents.z / 2.f));

	zt_fiz(3) {
		if(zt_real32Eq(direction.values[i], 0)) {
			// parallel in this axis
			if(point.values[i] < aabb_min.values[i] || point.values[i] > aabb_max.values[i]) {
				return false;
			}
		}
		else {
			r32 t1, t2;
			if(direction.values[i] >= 0) {
				t1 = (aabb_min.values[i] - point.values[i]) / direction.values[i];
				t2 = (aabb_max.values[i] - point.values[i]) / direction.values[i];
			}
			else {
				t1 = (aabb_max.values[i] - point.values[i]) / direction.values[i];
				t2 = (aabb_min.values[i] - point.values[i]) / direction.values[i];
			}

			if(tmin > t2 || t1 > tmax) { return false; }

			if (t1 > tmin) tmin = t1;
			if (t2 < tmax) tmax = t2;

			if(tmin > tmax) {
				return false;
			}
		}
	}

	if(intersection_point) {
		*intersection_point = point + direction * tmin;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionLineSegmentInAABB(const ztVec3& line_0, const ztVec3& line_1, const ztVec3& aabb_center, const ztVec3& aabb_extents, ztVec3 intersection_points[2])
{
	ZT_PROFILE_PHYSICS("zt_collisionLineSegmentInAABB");
	r32 tmin = 0;
	r32 tmax = ztReal32Max;

	ztVec3 direction  = line_1 - line_0;
	//direction.normalize();

	ztVec3 aabb_min(aabb_center.x - (aabb_extents.x / 2.f), aabb_center.y - (aabb_extents.y / 2.f), aabb_center.z - (aabb_extents.z / 2.f));
	ztVec3 aabb_max(aabb_center.x + (aabb_extents.x / 2.f), aabb_center.y + (aabb_extents.y / 2.f), aabb_center.z + (aabb_extents.z / 2.f));

	zt_fiz(3) {
		if(zt_real32Eq(direction.values[i], 0)) {
			// parallel in this axis
			if(line_0.values[i] < aabb_min.values[i] || line_0.values[i] > aabb_max.values[i]) {
				return false;
			}
		}
		else {
			r32 t1, t2;
			if(direction.values[i] >= 0) {
				t1 = (aabb_min.values[i] - line_0.values[i]) / direction.values[i];
				t2 = (aabb_max.values[i] - line_0.values[i]) / direction.values[i];
			}
			else {
				t1 = (aabb_max.values[i] - line_0.values[i]) / direction.values[i];
				t2 = (aabb_min.values[i] - line_0.values[i]) / direction.values[i];
			}

			if(tmin > t2 || t1 > tmax) { return false; }

			if (t1 > tmin) tmin = t1;
			if (t2 < tmax) tmax = t2;

			if(tmin > tmax) {
				return false;
			}
		}
	}

	if(tmin < 0 || tmin > 1) {
		return false;
	}

	if(intersection_points) {
		intersection_points[0] = line_0 + direction * tmin;
		intersection_points[1] = line_0 + direction * zt_min(1, tmax);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionAABBInAABB(const ztVec3& aabb_center_1, const ztVec3& aabb_extents_1, const ztVec3& aabb_center_2, const ztVec3& aabb_extents_2)
{
	ZT_PROFILE_PHYSICS("zt_collisionAABBInAABB");
	ztVec3 aabb_min_1(aabb_center_1.x - (aabb_extents_1.x / 2.f), aabb_center_1.y - (aabb_extents_1.y / 2.f), aabb_center_1.z - (aabb_extents_1.z / 2.f));
	ztVec3 aabb_max_1(aabb_center_1.x + (aabb_extents_1.x / 2.f), aabb_center_1.y + (aabb_extents_1.y / 2.f), aabb_center_1.z + (aabb_extents_1.z / 2.f));

	ztVec3 aabb_min_2(aabb_center_2.x - (aabb_extents_2.x / 2.f), aabb_center_2.y - (aabb_extents_2.y / 2.f), aabb_center_2.z - (aabb_extents_2.z / 2.f));
	ztVec3 aabb_max_2(aabb_center_2.x + (aabb_extents_2.x / 2.f), aabb_center_2.y + (aabb_extents_2.y / 2.f), aabb_center_2.z + (aabb_extents_2.z / 2.f));

	zt_fiz(3) {
		if(aabb_max_1.values[i] < aabb_min_2.values[i] || aabb_min_1.values[i] > aabb_max_2.values[i]) {
			return false;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionAABBInPlane(const ztVec3& aabb_center_1, const ztVec3& aabb_extents_1, const ztVec3& plane_coord, const ztVec3& plane_normal, ztVec3 *intersection_point)
{
	ZT_PROFILE_PHYSICS("zt_collisionAABBInPlane");
	zt_assert(false); // not yet implemented
	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionOBBInOBB(const ztVec3& obb_center_1, const ztVec3& obb_extents_1, const ztQuat& obb_rot_1, const ztVec3& obb_center_2, const ztVec3& obb_extents_2, const ztQuat& obb_rot_2)
{
	ZT_PROFILE_PHYSICS("zt_collisionOBBInOBB");
	ztVec3 obb_axis_1[3] = {
		obb_rot_1.rotatePosition(1, 0, 0),
		obb_rot_1.rotatePosition(0, 1, 0),
		obb_rot_1.rotatePosition(0, 0, 1),
	};

	ztVec3 obb_axis_2[3] = {
		obb_rot_2.rotatePosition(1, 0, 0),
		obb_rot_2.rotatePosition(0, 1, 0),
		obb_rot_2.rotatePosition(0, 0, 1),
	};

	return zt_collisionOBBInOBB(obb_center_1, obb_extents_1, obb_axis_1, obb_center_2, obb_extents_2, obb_axis_2);
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionOBBInOBB(const ztVec3& obb_center_1, const ztVec3& obb_extents_1, const ztVec3 obb_axis_1[3], const ztVec3& obb_center_2, const ztVec3& obb_extents_2, const ztVec3 obb_axis_2[3])
{
	ZT_PROFILE_PHYSICS("zt_collisionOBBInOBB");
	r32 mat_r[3][3], mat_abs_r[3][3], ra, rb, sp;

	zt_fiz(3) {
		zt_fjz(3) {
			mat_r[i][j] = obb_axis_1[i].dot(obb_axis_2[j]);
			mat_abs_r[i][j] = zt_abs(mat_r[i][j]) + ztReal32Epsilon;
		}
	}

	ztVec3 t = obb_center_2 - obb_center_1;
	t = ztVec3(t.dot(obb_axis_1[0]), t.dot(obb_axis_1[1]), t.dot(obb_axis_1[2]));

	ztVec3 a_ext = obb_extents_1 * .5f;
	ztVec3 b_ext = obb_extents_2 * .5f;

	r32 spans[15], diffs[15];
	//r32 axis_min0[15], axis_max0[15], axis_min1[15], axis_max1[15];
	int axis_idx = 0;

	// axis 0 - x, 1 - y, 2 - z

	// axis A0, A1, A2 (0-2)
	zt_fiz(3) {
		ra = a_ext.values[i];
		rb = b_ext.values[0] * mat_abs_r[i][0] + b_ext.values[1] * mat_abs_r[i][1] + b_ext.values[2] * mat_abs_r[i][2];
		sp = zt_abs(t.values[i]);
		if(sp > ra + rb) return false;
		diffs[axis_idx] = (ra + rb) - sp;
		spans[axis_idx++] = sp;
	}

	// axis B0, B1, B2 (3-5)
	zt_fiz(3) {
		ra = a_ext.values[0] * mat_abs_r[0][i] + a_ext.values[1] * mat_abs_r[1][i] + a_ext.values[2] * mat_abs_r[2][i];
		rb = b_ext.values[i];
		sp = zt_abs(t.values[0] * mat_r[0][i] + t.values[1] *  mat_r[1][i] + t.values[2] * mat_r[2][i]);
		if(sp > ra + rb) return false;
		diffs[axis_idx] = (ra + rb) - sp;
		spans[axis_idx++] = sp;
	}

	// axis A0 x B0 (6)
	ra = a_ext.values[1] * mat_abs_r[2][0] + a_ext.values[2] * mat_abs_r[1][0];
	rb = b_ext.values[1] * mat_abs_r[0][2] + b_ext.values[2] * mat_abs_r[0][1];
	sp = zt_abs(t.values[2] * mat_r[1][0] - t.values[1] * mat_r[2][0]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A0 x B1 (7)
	ra = a_ext.values[1] * mat_abs_r[2][1] + a_ext.values[2] * mat_abs_r[1][1];
	rb = b_ext.values[0] * mat_abs_r[0][2] + b_ext.values[2] * mat_abs_r[0][0];
	sp = zt_abs(t.values[2] * mat_r[1][1] - t.values[1] * mat_r[2][1]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A0 x B2 (8)
	ra = a_ext.values[1] * mat_abs_r[2][2] + a_ext.values[2] * mat_abs_r[1][2];
	rb = b_ext.values[0] * mat_abs_r[0][1] + b_ext.values[1] * mat_abs_r[0][0];
	sp = zt_abs(t.values[2] * mat_r[1][2] - t.values[1] * mat_r[2][2]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A1 x B0 (9)
	ra = a_ext.values[0] * mat_abs_r[2][0] + a_ext.values[2] * mat_abs_r[0][0];
	rb = b_ext.values[1] * mat_abs_r[1][2] + b_ext.values[2] * mat_abs_r[1][1];
	sp = zt_abs(t.values[0] * mat_r[2][0] - t.values[2] * mat_r[0][0]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A1 x B1 (10)
	ra = a_ext.values[0] * mat_abs_r[2][1] + a_ext.values[2] * mat_abs_r[0][1];
	rb = b_ext.values[0] * mat_abs_r[1][2] + b_ext.values[2] * mat_abs_r[1][0];
	sp = zt_abs(t.values[0] * mat_r[2][1] - t.values[2] * mat_r[0][1]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A1 x B2 (11)
	ra = a_ext.values[0] * mat_abs_r[2][2] + a_ext.values[2] * mat_abs_r[0][2];
	rb = b_ext.values[0] * mat_abs_r[1][1] + b_ext.values[1] * mat_abs_r[1][0];
	sp = zt_abs(t.values[0] * mat_r[2][2] - t.values[2] * mat_r[0][2]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A2 x B0 (12)
	ra = a_ext.values[0] * mat_abs_r[1][0] + a_ext.values[1] * mat_abs_r[0][0];
	rb = b_ext.values[1] * mat_abs_r[2][2] + b_ext.values[2] * mat_abs_r[2][1];
	sp = zt_abs(t.values[1] * mat_r[0][0] - t.values[0] * mat_r[1][0]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A2 x B1 (13)
	ra = a_ext.values[0] * mat_abs_r[1][1] + a_ext.values[1] * mat_abs_r[0][1];
	rb = b_ext.values[0] * mat_abs_r[2][2] + b_ext.values[2] * mat_abs_r[2][0];
	sp = zt_abs(t.values[1] * mat_r[0][1] - t.values[0] * mat_r[0][1]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	// axis A2 x B2 (14)
	ra = a_ext.values[0] * mat_abs_r[1][2] + a_ext.values[1] * mat_abs_r[0][2];
	rb = b_ext.values[0] * mat_abs_r[2][1] + b_ext.values[1] * mat_abs_r[2][0];
	sp = zt_abs(t.values[1] * mat_r[0][2] - t.values[0] * mat_r[1][2]);
	if(sp > ra + rb) return false;
	diffs[axis_idx] = (ra + rb) - sp;
	spans[axis_idx++] = sp;

	return true;
}

// ------------------------------------------------------------------------------------------------

int zt_collisionOBBInOBBGetContactPoints(const ztVec3& obb_center_1, const ztVec3& obb_extents_1, const ztQuat& obb_rot_1, const ztVec3& obb_center_2, const ztVec3& obb_extents_2, const ztQuat& obb_rot_2, ztVec3 *contacts, int contacts_size)
{
	ZT_PROFILE_PHYSICS("zt_collisionOBBInOBBGetContactPoints");
	ztVec3 diff = obb_center_2 - obb_center_1;

	ztVec3 corners[8] = {
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(-obb_extents_2.x / 2.f, +obb_extents_2.y / 2.f, +obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(-obb_extents_2.x / 2.f, +obb_extents_2.y / 2.f, -obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(+obb_extents_2.x / 2.f, +obb_extents_2.y / 2.f, -obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(+obb_extents_2.x / 2.f, +obb_extents_2.y / 2.f, +obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(-obb_extents_2.x / 2.f, -obb_extents_2.y / 2.f, +obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(-obb_extents_2.x / 2.f, -obb_extents_2.y / 2.f, -obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(+obb_extents_2.x / 2.f, -obb_extents_2.y / 2.f, -obb_extents_2.z / 2.f)),
		obb_center_2 + obb_rot_2.rotatePosition(ztVec3(+obb_extents_2.x / 2.f, -obb_extents_2.y / 2.f, +obb_extents_2.z / 2.f)),
	};

	ztPoint2 lines[12] = {
		ztPoint2(0, 1),
		ztPoint2(1, 2),
		ztPoint2(2, 3),
		ztPoint2(3, 0),

		ztPoint2(4, 5),
		ztPoint2(5, 6),
		ztPoint2(6, 7),
		ztPoint2(7, 4),

		ztPoint2(0, 4),
		ztPoint2(1, 5),
		ztPoint2(2, 6),
		ztPoint2(3, 7),
	};

	int ct_idx = 0;
	zt_fize(lines) {
		ztVec3 line_0 = corners[lines[i].x];
		ztVec3 line_1 = corners[lines[i].y];
		if(line_0.distance(obb_center_1) < line_1.distance(obb_center_1)) {
			zt_swap(line_0, line_1);
		}

		ztVec3 line_intersects[2];
		if(zt_collisionLineSegmentInOBB(line_0, line_1, obb_center_1, obb_extents_1, obb_rot_1, line_intersects)) {
			zt_fjz(2) {
				if(ct_idx < contacts_size && (j != 1 || !line_intersects[1].equalsClose(line_1))) {
					contacts[ct_idx++] = line_intersects[j];
				}
				else return ct_idx;
			}
		}
	}

	return ct_idx;
}

// ------------------------------------------------------------------------------------------------

bool zt_collisionLineSegmentInOBB(const ztVec3& line_0, const ztVec3& line_1, const ztVec3& obb_center, const ztVec3& obb_extents, const ztQuat& obb_rot, ztVec3 intersections[2])
{
	ZT_PROFILE_PHYSICS("zt_collisionLineSegmentInOBB");
	ztQuat to_local = obb_rot.getInverse();
	if(zt_collisionLineSegmentInAABB(to_local.rotatePosition(line_0 - obb_center), to_local.rotatePosition(line_1 - obb_center), ztVec3::zero, obb_extents, intersections)) {
		intersections[0] = obb_rot.rotatePosition(intersections[0]) + obb_center;
		intersections[1] = obb_rot.rotatePosition(intersections[1]) + obb_center;
		return true;
	}

	return false;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseLinear)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseLinear");
	return value;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseBack)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseBack");
	return (value * value) * (2.70158f * value - 1.70158f);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseBounce)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseBounce");
	if(1 - value < 1 / 2.75f) {
		value = 1 - 7.5625f * ((1 - value) * (1-value));
	}
	else if(1 - value < 2 / 2.75f) {
		value = 1 - (7.5625f * (1 - value - 1.5f / 2.75f) * (1 - value - 1.5f / 2.75f) + 0.75f);
	}
	else if(1 - value < 2.5 / 2.75) {
		value = 1 - (7.5625f * (1 - value - 2.25f / 2.75f) * (1 - value - 2.25f / 2.75f) + 0.9375f);
	}
	else {
		value = 1 - (7.5625f * (1 - value - 2.625f / 2.75f) * (1 - value - 2.625f / 2.75f) + 0.984375f);
	}

	return value;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseCirc)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseCirc");
	return 1 - zt_sqrt(1 - (value * value));
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseCubic)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseCubic");
	return value * value * value;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseElastic)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseElastic");
	if( value == 0 || value == 1 ) return value;
	return zt_sin(2.f * ztMathPi2 * value) * zt_pow(2, 2.f * (value - 1));
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseExpo)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseExpo");
	if( value == 0 ) return 0;
	return zt_pow(2, 10 * (value - 1));
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseQuad)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseQuad");
	return value * value;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseQuart)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseQuart");
	return value * value * value * value;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseQuint)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseQuint");
	return value * value * value * value * value;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_TWEEN_EASE(zt_tweenEaseSine)
{
	ZT_PROFILE_ANIMATION("zt_tweenEaseSine");
	return 1 - zt_cos(value * 3.14159f / 2);
}

// ------------------------------------------------------------------------------------------------

r32 zt_tweenValue(r32 val_beg, r32 val_end, r32 percent, ztTweenEase_Func *ease_in, ztTweenEase_Func *ease_out)
{
	return zt_tweenValue(val_beg, val_end, percent, ease_in, nullptr, ease_out, nullptr);
}

// ------------------------------------------------------------------------------------------------

r32 zt_tweenValue(r32 val_beg, r32 val_end, r32 percent, ztTweenEase_Func *ease_in, void *ease_in_user_data, ztTweenEase_Func *ease_out, void *ease_out_user_data)
{
	ZT_PROFILE_ANIMATION("zt_tweenValue");
	if (ease_in && ease_out == nullptr) {
		percent = ease_in(percent, ease_in_user_data);
	}
	else if (ease_in == nullptr && ease_out) {
		percent = 1 - ease_out(1 - percent, ease_out_user_data);
	}
	else if (ease_in && ease_out) {
		if (percent < .5f) {
			percent = ease_in(2 * percent, ease_in) / 2.0f;
		}
		else {
			percent = .5f + .5f * (1 - ease_out(1 - (percent - .5f) * 2, ease_out_user_data));
		}
	}

	return zt_lerp(val_beg, val_end, percent);
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_tweenValue(const ztVec2& val_beg, const ztVec2& val_end, r32 percent, ztTweenEase_Func *ease_in, ztTweenEase_Func *ease_out)
{
	return ztVec2(zt_tweenValue(val_beg.x, val_end.x, percent, ease_in, ease_out),
		zt_tweenValue(val_beg.y, val_end.y, percent, ease_in, ease_out));
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_tweenValue(const ztVec2& val_beg, const ztVec2& val_end, r32 percent, ztTweenEase_Func *ease_in, void *ease_in_user_data, ztTweenEase_Func *ease_out, void *ease_out_user_data)
{
	return ztVec2(zt_tweenValue(val_beg.x, val_end.x, percent, ease_in, ease_in_user_data, ease_out, ease_out_user_data),
		zt_tweenValue(val_beg.y, val_end.y, percent, ease_in, ease_in_user_data, ease_out, ease_out_user_data));
}

// ------------------------------------------------------------------------------------------------

ztVec3 zt_tweenValue(const ztVec3& val_beg, const ztVec3& val_end, r32 percent, ztTweenEase_Func *ease_in, ztTweenEase_Func *ease_out)
{
	return ztVec3(zt_tweenValue(val_beg.x, val_end.x, percent, ease_in, ease_out),
		zt_tweenValue(val_beg.y, val_end.y, percent, ease_in, ease_out),
		zt_tweenValue(val_beg.z, val_end.z, percent, ease_in, ease_out));
}

// ------------------------------------------------------------------------------------------------

ztVec3 zt_tweenValue(const ztVec3& val_beg, const ztVec3& val_end, r32 percent, ztTweenEase_Func *ease_in, void *ease_in_user_data, ztTweenEase_Func *ease_out, void *ease_out_user_data)
{
	return ztVec3(zt_tweenValue(val_beg.x, val_end.x, percent, ease_in, ease_in_user_data, ease_out, ease_out_user_data),
		zt_tweenValue(val_beg.y, val_end.y, percent, ease_in, ease_in_user_data, ease_out, ease_out_user_data),
		zt_tweenValue(val_beg.z, val_end.z, percent, ease_in, ease_in_user_data, ease_out, ease_out_user_data));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


ztAnimKey zt_animKeyMake(ztVariantPointer target, ztVariant value_beg, ztVariant value_end, r32 time)
{
	ZT_PROFILE_ANIMATION("zt_animKeyMake");
	ztAnimKey anim_key;
	anim_key.target    = target;
	anim_key.value_beg = value_beg;
	anim_key.value_end = value_end;
	anim_key.time      = time;

	return anim_key;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztAnimLayer zt_animLayerMake(ztAnimKey *keys, int keys_count)
{
	ZT_PROFILE_ANIMATION("zt_animLayerMake");
	ztAnimLayer layer;

	layer.keys = zt_mallocStructArray(ztAnimKey, keys_count);
	layer.keys_count = keys_count;
	zt_fiz(keys_count) {
		layer.keys[i] = keys[i];
	}

	layer.state        = ztAnimLayerState_Sleeping;
	layer.current_key  = 0;
	layer.current_time = 0;
	layer.target_time  = 0;

	return layer;
}

// ------------------------------------------------------------------------------------------------

void zt_animLayerFree(ztAnimLayer *layer)
{
	ZT_PROFILE_ANIMATION("zt_animLayerFree");
	if (layer == nullptr) {
		return;
	}

	zt_free(layer->keys);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _zt_animLayerTransitionInto(ztAnimLayer *layer, r32 transition_time)
{
	ZT_PROFILE_ANIMATION("_zt_animLayerTransitionInto");
	zt_variantAssignValue(&layer->value_beg, zt_variantMake(&layer->keys[0].target));
	zt_variantAssignValue(&layer->value_end, layer->keys[0].value_beg);
	layer->state        = ztAnimLayerState_Transitioning;
	layer->current_time = 0;
	layer->current_key  = 0;
	layer->target_time  = transition_time;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _zt_animLayerStart(ztAnimLayer *layer)
{
	ZT_PROFILE_ANIMATION("_zt_animLayerStart");
	zt_variantAssignValue(&layer->value_beg, layer->keys[0].value_beg);
	zt_variantAssignValue(&layer->value_end, layer->keys[0].value_end);
	zt_variantAssignValue(&layer->keys[0].target, layer->keys[0].value_beg);
	layer->state        = ztAnimLayerState_Playing;
	layer->current_time = 0;
	layer->current_key  = 0;
	layer->target_time  = layer->keys[0].time;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_animLayerUpdate(ztAnimLayer *layer, r32 dt)
{
	ZT_PROFILE_ANIMATION("_zt_animLayerUpdate");
	if (layer->state == ztAnimLayerState_Sleeping) {
		return false;
	}

	layer->current_time += dt;

	ztAnimKey *key = &layer->keys[layer->current_key];

	zt_variantAssignValue(&key->target, zt_variantLerp(&layer->value_beg, &layer->value_end, zt_min(1, layer->current_time / layer->target_time)));

	if (layer->current_time > layer->target_time) {
		layer->current_time -= layer->target_time;

		if (layer->state == ztAnimLayerState_Transitioning) {
			_zt_animLayerStart(layer);
		}
		else {
			layer->current_key += 1;
			if (layer->current_key >= layer->keys_count) {
				layer->state = ztAnimLayerState_Sleeping;
				return false;
			}
			else {
				layer->target_time = layer->keys[layer->current_key].time;
			}

			zt_variantAssignValue(&layer->value_beg, layer->keys[layer->current_key].value_beg);
			zt_variantAssignValue(&layer->value_end, layer->keys[layer->current_key].value_end);
			zt_variantAssignValue(&layer->keys[layer->current_key].target, layer->keys[layer->current_key].value_beg);
		}
	}

	return true;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztAnimSequence *zt_animSequenceMake(ztAnimSequenceType_Enum type, ztAnimLayer *layers, int layers_count, ztAnimTransition_Enum transition_type, r32 transition_time, bool loops)
{
	ZT_PROFILE_ANIMATION("zt_animSequenceMake");
	ztAnimSequence *sequence = zt_mallocStruct(ztAnimSequence);

	sequence->type = type;

	sequence->layers = zt_mallocStructArray(ztAnimLayer, layers_count);
	sequence->layers_count = layers_count;
	zt_fiz(layers_count) {
		sequence->layers[i] = layers[i];
	}

	sequence->transition_type = transition_type;
	sequence->transition_time = transition_time;
	sequence->loops = loops;

	return sequence;
}

// ------------------------------------------------------------------------------------------------

void zt_animSequenceFree(ztAnimSequence *sequence)
{
	ZT_PROFILE_ANIMATION("zt_animSequenceFree");
	if (sequence == nullptr) {
		return;
	}
	zt_fiz(sequence->layers_count) {
		zt_animLayerFree(&sequence->layers[i]);
	}
	zt_free(sequence->layers);
	zt_free(sequence);
}

// ------------------------------------------------------------------------------------------------

r32 zt_animSequencePercentComplete(ztAnimSequence *sequence)
{
	ZT_PROFILE_ANIMATION("zt_animSequencePercentComplete");
	r32 longest_layer_time = 0;
	r32 longest_layer_curr = 0;

	zt_fiz(sequence->layers_count) {
		if (sequence->layers[i].state != ztAnimLayerState_Sleeping) {
			longest_layer_time = zt_max(longest_layer_time, sequence->layers[i].target_time);
			longest_layer_curr = zt_max(longest_layer_curr, sequence->layers[i].current_time);
		}
	}

	if (longest_layer_time == 0) {
		return 1;
	}

	return longest_layer_curr / longest_layer_time;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_animSequenceStart(ztAnimSequence *sequence)
{
	ZT_PROFILE_ANIMATION("_zt_animSequenceStart");
	if(sequence->transition_type == ztAnimTransition_Interp) {
		zt_fiz(sequence->layers_count) {
			_zt_animLayerTransitionInto(&sequence->layers[i], sequence->transition_time);
		}
	}
	else {
		zt_fiz(sequence->layers_count) {
			_zt_animLayerStart(&sequence->layers[i]);
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_animSequenceUpdate(ztAnimSequence *sequence, r32 dt)
{
	ZT_PROFILE_ANIMATION("_zt_animSequenceUpdate");
	int layers_processed = 0;
	zt_fiz(sequence->layers_count) {
		if(sequence->layers[i].state == ztAnimLayerState_Sleeping) {
			continue;
		}

		if(_zt_animLayerUpdate(&sequence->layers[i], dt)) {
			layers_processed += 1;
		}
	}

	if(layers_processed == 0 && sequence->loops) {
		_zt_animSequenceStart(sequence);
		return true;
	}

	return layers_processed != 0;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztAnimController *zt_animControllerMake(int max_sequences, int max_async)
{
	ZT_PROFILE_ANIMATION("zt_animControllerMake");
	ztAnimController *controller = zt_mallocStruct(ztAnimController);

	controller->sequences_name_hash = zt_mallocStructArray(i32, max_sequences);
	controller->sequences_name      = zt_mallocStructArray(ztString, max_sequences);
	controller->sequences           = zt_mallocStructArray(ztAnimSequence*, max_sequences);
	controller->sequences_size      = max_sequences;
	controller->sequences_count     = 0;

	controller->anim_sync           = nullptr;

	controller->anim_async_count = max_async;
	controller->anim_async = max_async > 0 ? zt_mallocStructArray(ztAnimSequence*, max_async) : nullptr;

	zt_fiz(max_async) {
		controller->anim_async[i] = nullptr;
	}

	controller->queued = 0;

	return controller;
}

// ------------------------------------------------------------------------------------------------

void zt_animControllerFree(ztAnimController *controller)
{
	ZT_PROFILE_ANIMATION("zt_animControllerFree");
	if (controller == nullptr) {
		return;
	}

	zt_fiz(controller->sequences_count) {
		zt_stringFree(controller->sequences_name[i]);
		zt_animSequenceFree(controller->sequences[i]);
	}

	if (controller->anim_async) {
		zt_free(controller->anim_async);
	}

	zt_free(controller->sequences);
	zt_free(controller->sequences_name);
	zt_free(controller->sequences_name_hash);
	zt_free(controller);
}

// ------------------------------------------------------------------------------------------------

i32 zt_animControllerAddSequence(ztAnimController *controller, const char *sequence_name, ztAnimSequence *sequence)
{
	ZT_PROFILE_ANIMATION("zt_animControllerAddSequence");
	zt_returnValOnNull(controller, -1);
	zt_returnValOnNull(sequence_name, -1);
	zt_returnValOnNull(sequence, -1);
	zt_assertReturnValOnFail(sequence->layers_count > 0, -1);

	if (controller->sequences_count >= controller->sequences_size) {
		return -1;
	}

	int idx = controller->sequences_count++;
	controller->sequences          [idx] = sequence;
	controller->sequences_name     [idx] = zt_stringMakeFrom(sequence_name);
	controller->sequences_name_hash[idx] = zt_strHash(sequence_name);

	return controller->sequences_name_hash[idx];
}

// ------------------------------------------------------------------------------------------------

int zt_animControllerStartSequence(ztAnimController *controller, i32 sequence_name_hash)
{
	ZT_PROFILE_ANIMATION("zt_animControllerStartSequence");
	ztAnimSequence *sequence = nullptr;

	int result = -1;
	zt_fiz(controller->sequences_count) {
		if (controller->sequences_name_hash[i] == sequence_name_hash) {
			sequence = controller->sequences[i];
			result = i;
			break;
		}
	}

	if (!sequence) return -1;

	if (sequence->type == ztAnimSequenceType_Synchronous) {
		controller->anim_sync = sequence;
	}
	else if (sequence->type == ztAnimSequenceType_Asynchronous) {
		int idx = -1;
		zt_fxz(3) {
			r32 most_complete = 0;
			zt_fiz(controller->anim_async_count) {
				r32 pct = controller->anim_async[i] == nullptr ? 1 : zt_animSequencePercentComplete(controller->anim_async[i]);

				if (x == 0 && pct == 1) {
					idx = i;
					break;
				}
				else if (x == 1 && controller->anim_async[i]->layers[0].state == ztAnimLayerState_Transitioning) {
					if (1 - pct > most_complete) {
						most_complete = 1 - pct;
						idx = i;
					}
				}
				else if (x == 2) {
					if (pct > most_complete) {
						most_complete = pct;
						idx = i;
					}
				}
			}
			if (idx != -1) {
				controller->anim_async[idx] = sequence;
				break;
			}
		}
		if(idx == -1) {
			return -1;
		}
	}

	_zt_animSequenceStart(sequence);

	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_animControllerUpdate(ztAnimController **controllers, int controllers_count, r32 dt)
{
	ZT_PROFILE_ANIMATION("zt_animControllerUpdate");
	zt_fiz(controllers_count) {
		ztAnimController *controller = controllers[i];

		if(controller->anim_sync) {
			if(!_zt_animSequenceUpdate(controller->anim_sync, dt)) {
				if (controller->queued != 0) {
					i32 queued = controller->queued;
					controller->queued = 0;
					zt_animControllerStartSequence(controller, queued);
				}
				else {
					controller->anim_sync = nullptr;
				}
			}
		}

		zt_fiz(controller->anim_async_count) {
			if(controller->anim_async[i] == nullptr) {
				continue;
			}
			if(!_zt_animSequenceUpdate(controller->anim_async[i], dt)) {
				controller->anim_async[i] = nullptr;
			}
		}
	}
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztSpriteAnimController *zt_spriteAnimControllerMake(int max_sequences)
{
	ZT_PROFILE_ANIMATION("zt_spriteAnimControllerMake");
	ztSpriteAnimController *controller = zt_mallocStruct(ztSpriteAnimController);
	controller->sequences = zt_mallocStructArray(ztSpriteAnimController::Sequence, max_sequences);
	controller->sequences_size = max_sequences;
	controller->sequences_count = 0;

	controller->controller = zt_animControllerMake(max_sequences, 0);

	return controller;
}

// ------------------------------------------------------------------------------------------------

void zt_spriteAnimControllerFree(ztSpriteAnimController *controller)
{
	ZT_PROFILE_ANIMATION("zt_spriteAnimControllerFree");
	if(controller == nullptr) {
		return;
	}

	zt_animControllerFree(controller->controller);

	zt_fiz(controller->sequences_count) {
		zt_free(controller->sequences[i].sprites);
	}

	zt_free(controller->sequences);
	zt_free(controller);
}

// ------------------------------------------------------------------------------------------------

void zt_spriteAnimControllerAddSequence(ztSpriteAnimController *controller, const char *sequence_name, ztSprite *sprites, r32 *times, int sprites_count, bool loops)
{
	ZT_PROFILE_ANIMATION("zt_spriteAnimControllerAddSequence");
	zt_returnOnNull(controller);
	zt_returnOnNull(sequence_name);
	zt_returnOnNull(sprites);
	zt_returnOnNull(times);
	zt_assertReturnOnFail(sprites_count > 0);
	zt_assertReturnOnFail(controller->sequences_count < controller->sequences_size);

	ztSpriteAnimController::Sequence *sequence = &controller->sequences[controller->sequences_count++];

	ztAnimKey *keys = zt_mallocStructArray(ztAnimKey, sprites_count);
	zt_fiz(sprites_count) {
		keys[i] = zt_animKeyMake(zt_variantPointerMake_i32(&sequence->current_sprite), zt_variantMake_i32(i), zt_variantMake_i32(i+1), times[i]);
	}

	ztAnimLayer layer = zt_animLayerMake(keys, sprites_count);

	zt_free(keys);

	ztAnimSequence *a_sequence = zt_animSequenceMake(ztAnimSequenceType_Synchronous, &layer, 1, ztAnimTransition_Snap, 0, loops);
	zt_animControllerAddSequence(controller->controller, sequence_name, a_sequence);

	sequence->sprites = zt_mallocStructArray(ztSprite, sprites_count);
	sequence->sprites_size = sprites_count;
	sequence->current_sprite = -1;

	zt_fiz(sprites_count) {
		sequence->sprites[i] = sprites[i];
	}
}

// ------------------------------------------------------------------------------------------------

void zt_spriteAnimControllerStartSequence(ztSpriteAnimController *controller, i32 sequence_name_hash)
{
	ZT_PROFILE_ANIMATION("zt_spriteAnimControllerStartSequence");
	zt_returnOnNull(controller);

	int active = zt_animControllerStartSequence(controller->controller, sequence_name_hash);
	if(active == -1 ) {
		return;
	}

	controller->active_sequence = active;
	controller->sequences[active].current_sprite = 0;
	return;
}

// ------------------------------------------------------------------------------------------------

void zt_spriteAnimControllerUpdate(ztSpriteAnimController **controllers, int controllers_count, r32 dt)
{
	ZT_PROFILE_ANIMATION("zt_spriteAnimControllerUpdate");
	zt_fiz(controllers_count) {
		zt_animControllerUpdate(&controllers[i]->controller, 1, dt);

		if(controllers[i]->active_sequence >= 0 && controllers[i]->active_sequence < controllers[i]->sequences_count) {

			ztSpriteAnimController::Sequence *sequence = &controllers[i]->sequences[controllers[i]->active_sequence];

			if(sequence->current_sprite >= 0 && sequence->current_sprite < sequence->sprites_size) {
				zt_animControllerUpdate(&controllers[i]->controller, 1, dt);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztSprite *zt_spriteAnimControllerActiveSprite(ztSpriteAnimController *controller)
{
	ZT_PROFILE_ANIMATION("zt_spriteAnimControllerActiveSprite");
	if(controller->active_sequence < 0 || controller->active_sequence >= controller->sequences_count) {
		return nullptr;
	}

	ztSpriteAnimController::Sequence *sequence = &controller->sequences[controller->active_sequence];

	if (sequence->current_sprite < 0 || sequence->current_sprite >= sequence->sprites_size) {
		return nullptr;
	}

	return &sequence->sprites[sequence->current_sprite];
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztParticleEmitter2D zt_particleEmitter2DMake(ztParticleEmitterSettings *settings, ztSprite *sprite, i32 seed)
{
	ZT_PROFILE_PARTICLES("zt_particleEmitter2DMake");
	ztParticleEmitter2D emitter = {};
	emitter.settings = *settings;
	emitter.sprite   = *sprite;

	emitter.particles_count = zt_min(ZT_MAX_PARTICLES, zt_convertToi32Ceil(settings->emission_rate * (settings->burst_emit ? 1 : settings->lifetime)));
	zt_fiz(emitter.particles_count) {
		emitter.particles[i].life = 0;
	}

	emitter.live_particles         = 0;
	emitter.time_between_particles = settings->burst_emit ? 0 : 1.0f / (zt_min(settings->emission_rate, ZT_MAX_PARTICLES) / settings->lifetime);
	emitter.time_last_particle     = 0;

	zt_randomInit(&emitter.randomizer, seed);

	return emitter;
}

// ------------------------------------------------------------------------------------------------

bool zt_particleEmitter2DUpdate(ztParticleEmitter2D *emitter, r32 dt)
{
	ZT_PROFILE_PARTICLES("zt_particleEmitter2DUpdate");
	// update existing particles before creating new ones
	zt_fiz(emitter->particles_count) {
		if (emitter->particles[i].life) {
			emitter->particles[i].life -= dt;
			if (emitter->particles[i].life > 0) {
				// should add friction affect to speed here
				// <- here

				// move particle
				emitter->particles[i].transform.position.x += (emitter->settings.gravity_velocity.x * dt) + zt_cos(zt_degreesToRadians(emitter->particles[i].angle)) * emitter->particles[i].speed * dt;
				emitter->particles[i].transform.position.y += (emitter->settings.gravity_velocity.y * dt) + zt_sin(zt_degreesToRadians(emitter->particles[i].angle)) * emitter->particles[i].speed * dt;

				if(emitter->settings.rotation != 0) {
					emitter->particles[i].transform.rotation *= ztQuat::makeFromEuler(0, 0, emitter->particles[i].rotation * dt);
				}
			}
			else {
				emitter->particles[i].life = 0;
				emitter->live_particles -= 1;
			}
		}
	}

	// emit new particles if needed
	if (emitter->settings.emitter_lifetime != 0 && emitter->settings.emitter_lifetime < 0) {
		if (emitter->live_particles <= 0) {
			return false;
		}
	}
	else {
		bool first = emitter->time_last_particle == 0;
		emitter->time_last_particle += dt;
		while (emitter->time_last_particle > emitter->time_between_particles) {
			emitter->time_last_particle -= emitter->time_between_particles;
			if ((!first && emitter->live_particles >= emitter->particles_count) || (!first && emitter->settings.burst_emit)) {
				break;
			}

			zt_fiz(emitter->particles_count) {
				if (emitter->particles[i].life <= 0) {

					r32 diff = 360 * emitter->settings.velocity_angle_random * zt_randomVal(&emitter->randomizer);
					r32 angle = emitter->settings.velocity_angle - (360 * emitter->settings.velocity_angle_random * .5f) + diff;
					if (angle < 0) angle += 360;


					emitter->particles[i].life                = emitter->settings.lifetime - (emitter->settings.lifetime * (emitter->settings.lifetime_random * zt_randomVal(&emitter->randomizer)));
					emitter->particles[i].angle               = angle;
					emitter->particles[i].transform.position  = ztVec3((zt_randomVal(&emitter->randomizer) * emitter->settings.size.x) - emitter->settings.size.x / 2,
					                                                   (zt_randomVal(&emitter->randomizer) * emitter->settings.size.y) - emitter->settings.size.y / 2,
					                                                   (zt_randomVal(&emitter->randomizer) * emitter->settings.size.z) - emitter->settings.size.z / 2);
					emitter->particles[i].speed               = emitter->settings.velocity_speed - (emitter->settings.velocity_speed * (emitter->settings.velocity_speed_random * zt_randomVal(&emitter->randomizer)));
					emitter->particles[i].rotation            = (emitter->settings.rotation * 360) * (1 - (zt_randomVal(&emitter->randomizer) * emitter->settings.rotation_random));

					if (emitter->settings.random_rotation) {
						emitter->particles[i].transform.rotation = ztQuat::makeFromEuler(0, 0, zt_randomVal(&emitter->randomizer) * 360);
					}

					ztVec3 scale(emitter->settings.scale, emitter->settings.scale, emitter->settings.scale);
					if (emitter->settings.scale_random != 0) {
						scale = scale * (1 - zt_randomVal(&emitter->randomizer) * emitter->settings.scale_random);
					}
					emitter->particles[i].transform.scale = scale;
					emitter->particles[i].transform.rotation = ztQuat::identity;

					emitter->live_particles += 1;
					if (!emitter->settings.burst_emit) {
						break;
					}
					else if(emitter->live_particles == emitter->particles_count) {
						first = false;
						break;
					}
				}
			}
		}
	}

	if (emitter->settings.emitter_lifetime > 0) {
		emitter->settings.emitter_lifetime -= dt;
		if (emitter->settings.emitter_lifetime <= 0) {
			emitter->settings.emitter_lifetime = -1;
			return true;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_particleEmitter2DRender(ztParticleEmitter2D *emitter, ztDrawList *draw_list)
{
	ZT_PROFILE_PARTICLES("zt_particleEmitter2DRender");
	zt_drawListPushTexture(draw_list, emitter->sprite.tex);
	
	bool change_color = emitter->settings.color_life_begin != emitter->settings.color_life_end;

	ztVec2 uv[4] = {
		ztVec2(emitter->sprite.tex_uv.x, emitter->sprite.tex_uv.y),
		ztVec2(emitter->sprite.tex_uv.x, emitter->sprite.tex_uv.w),
		ztVec2(emitter->sprite.tex_uv.z, emitter->sprite.tex_uv.w),
		ztVec2(emitter->sprite.tex_uv.z, emitter->sprite.tex_uv.y)
	};

	ztVec3 normals[4] = { ztVec3::one, ztVec3::one, ztVec3::one, ztVec3::one };

	zt_fiz(emitter->live_particles) {

		if (change_color) {
			ztVec4 color = ztVec4::lerp(emitter->settings.color_life_begin, emitter->settings.color_life_end, 1 - zt_min(1, (emitter->particles[i].life / emitter->settings.lifetime)));
			zt_drawListPushColor(draw_list, color);
		}

		ztVec3 pos = emitter->particles[i].transform.position;
		if (emitter->settings.local_space) {
			pos += emitter->settings.origin;
		}

		if (emitter->particles[i].rotation) {
			ztVec3 p[4] = {
				emitter->particles[i].transform.scale * ztVec3(-emitter->sprite.half_size.x, emitter->sprite.half_size.y, 0),
				emitter->particles[i].transform.scale * ztVec3(-emitter->sprite.half_size.x, -emitter->sprite.half_size.y, 0),
				emitter->particles[i].transform.scale * ztVec3( emitter->sprite.half_size.x, -emitter->sprite.half_size.y, 0),
				emitter->particles[i].transform.scale * ztVec3( emitter->sprite.half_size.x, emitter->sprite.half_size.y, 0),
			};

			zt_fjze(p) {
				emitter->particles[i].transform.rotation.rotatePosition(&p[j]);
				p[j] += pos;
			}

			zt_drawListAddFilledQuad(draw_list, p, uv, normals	);

		}
		else {
			//zt_drawListAddBillboard(draw_list, emitt6er->settings.origin + emitter->particles[i].transform.position, emitter->sprite.half_size * 2, emitter->sprite.tex_uv.xy, emitter->sprite.tex_uv.zw);
			zt_drawListAddFilledRect2D(draw_list, pos, emitter->particles[i].transform.scale.xy * (emitter->sprite.half_size * 2), emitter->sprite.tex_uv.xy, emitter->sprite.tex_uv.zw);
		}
		if (change_color) {
			zt_drawListPopColor(draw_list);
		}
	}
	zt_drawListPopTexture(draw_list);
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztPathGridSquare *zt_pathGridSquareMake(int rows, int cols, bool allow_diagonals)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquareMake");
	ztPathGridSquare *grid = zt_mallocStruct(ztPathGridSquare);
	grid->rows = rows;
	grid->cols = cols;

	grid->nodes = zt_mallocStructArray(ztPathNode, rows * cols);

#	define get_idx(R,C) (((R) < 0 || (R) > rows - 1 || (C) < 0 || (C) > cols - 1) ? -1 : ((R) * cols) + (C))

	int nodes = rows * cols;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int idx = (r * cols) + c;
			grid->nodes[idx].position.x = (r32)c;
			grid->nodes[idx].position.y = (r32)r;
			grid->nodes[idx].position.z = 0.0f;
			grid->nodes[idx].flags = 0;

			int neighbors = (r == 0 ? 0 : 1) + (r == rows - 1 ? 0 : 1) + (c == 0 ? 0 : 1) + (c == cols - 1 ? 0 : 1);

			if (allow_diagonals) {
				neighbors +=
					(r > 0 && c < cols - 1 ? 1 : 0) + // ne
					(r < rows - 1 && c < cols - 1 ? 1 : 0) + // se
					(r < rows - 1 && c > 0 ? 1 : 0) + // sw
					(r > 0 && c > 0 ? 1 : 0);// nw
			}

			zt_assert(neighbors <= ZT_PATH_NODE_MAX_NEIGHBORS);

			grid->nodes[idx].neighbors_count = neighbors;

			int idx_n = get_idx(r - 1, c);
			int idx_s = get_idx(r + 1, c);
			int idx_e = get_idx(r, c + 1);
			int idx_w = get_idx(r, c - 1);

			int idx_ne = allow_diagonals ? get_idx(r - 1, c + 1) : -1;
			int idx_se = allow_diagonals ? get_idx(r + 1, c + 1) : -1;
			int idx_sw = allow_diagonals ? get_idx(r + 1, c - 1) : -1;
			int idx_nw = allow_diagonals ? get_idx(r - 1, c - 1) : -1;

			int n_idx = 0;
			if (idx_n != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_n];
			if (idx_ne != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_ne];
			if (idx_s != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_s];
			if (idx_se != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_se];
			if (idx_e != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_e];
			if (idx_sw != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_sw];
			if (idx_w != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_w];
			if (idx_nw != -1) grid->nodes[idx].neighbors[n_idx++] = &grid->nodes[idx_nw];

			zt_assert(n_idx == grid->nodes[idx].neighbors_count);
		}
	}

#	undef get_idx

	return grid;
}

// ------------------------------------------------------------------------------------------------

void zt_pathGridSquareFree(ztPathGridSquare *grid)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquareFree");
	if (grid == nullptr) {
		return;
	}

	if (grid->nodes) {
		zt_free(grid->nodes);
	}
	zt_free(grid);
}

// ------------------------------------------------------------------------------------------------

ztPathNode *zt_pathGridSquareAccessNode(ztPathGridSquare *grid, int row, int col)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquareAccessNode");
	zt_returnValOnNull(grid, nullptr);
	if (row < 0 || row >= grid->rows || col < 0 || col >= grid->cols) {
		return nullptr;
	}

	int idx = (row * grid->cols) + col;
	return &grid->nodes[idx];
}

// ------------------------------------------------------------------------------------------------

bool zt_pathGridSquareGetCoords(ztPathGridSquare *grid, ztPathNode *node, int *row, int *col)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquareGetCoords");
	zt_returnValOnNull(grid, false);
	zt_returnValOnNull(node, false);
	zt_returnValOnNull(row, false);
	zt_returnValOnNull(col, false);

	int max = grid->rows * grid->cols;
	for (int i = 0; i < max; ++i) {
		if (node == &grid->nodes[i]) {
			*row = i / grid->cols;
			*col = i - ((*row) * grid->cols);
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

bool zt_pathGridSquareGetNodeIndex(ztPathGridSquare *grid, ztPathNode *node, int *index)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquareGetNodeIndex");
	zt_returnValOnNull(grid, false);
	zt_returnValOnNull(node, false);
	zt_returnValOnNull(index, false);

	int max = grid->rows * grid->cols;
	for (int i = 0; i < max; ++i) {
		if (node == &grid->nodes[i]) {
			*index = i;
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

r32 zt_pathNodeGetDistance(ztPathNode *node_one, ztPathNode *node_two)
{
	ZT_PROFILE_PATHFINDING("zt_pathNodeGetDistance");
	zt_returnValOnNull(node_one, 0);
	zt_returnValOnNull(node_two, 0);

	return node_one->position.distance(node_two->position);
}

// ------------------------------------------------------------------------------------------------

ztPathNode *zt_pathGridSquareGetNode(ztPathGridSquare *grid, int col, int row)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquareGetNode");
	zt_returnValOnNull(grid, nullptr);
	return &grid->nodes[col + row * grid->cols];
}

// ------------------------------------------------------------------------------------------------

void zt_pathGridSquarePrepareForPathfinding(ztPathGridSquare *grid, ztPathProgress *progress)
{
	ZT_PROFILE_PATHFINDING("zt_pathGridSquarePrepareForPathfinding");
	int max = grid->rows * grid->cols;
	zt_fiz(max) {
		zt_bitRemove(grid->nodes[i].flags, ztPathNodeFlags_Ignore);
		grid->nodes[i]._my_move_cost = ztPathNodeValue_Reset;
	}

	progress->frontier_idx = 0;
	progress->visited_idx = 0;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_pathNodeArrayContains(ztPathNode **arr, int len, ztPathNode *node)
{
	ZT_PROFILE_PATHFINDING("_zt_pathNodeArrayContains");
	zt_fiz(len) {
		if (arr[i] == node) {
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_pathArrayInsertBefore(ztPathNode **arr, int len, int *index, int before_index, ztPathNode *node)
{
	ZT_PROFILE_PATHFINDING("_zt_pathArrayInsertBefore");
	if (*index == len) {
		return false;
	}
	for (int i = *index; i > before_index; --i) {
		arr[i] = arr[i - 1];
	}
	arr[before_index] = node;
	*index += 1;
	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_pathArrayAddToBegin(ztPathNode **arr, int len, int *index, ztPathNode *node)
{
	ZT_PROFILE_PATHFINDING("_zt_pathArrayAddToBegin");
	return _zt_pathArrayInsertBefore(arr, len, index, 0, node);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline bool _zt_pathArrayAddToEnd(ztPathNode **arr, int len, int* index, ztPathNode *node)
{
	ZT_PROFILE_PATHFINDING("_zt_pathArrayAddToEnd");
	if (*index == len) {
		return false;
	}
	arr[(*index)++] = node;
	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztInline void _zt_pathArrayRemoveFromBegin(ztPathNode **arr, int len, int* index)
{
	ZT_PROFILE_PATHFINDING("_zt_pathArrayRemoveFromBegin");
	for (int i = 1; i < *index; ++i) {
		arr[i - 1] = arr[i];
	}
	*index -= 1;
}

// ------------------------------------------------------------------------------------------------

ztPathProgress *zt_pathProgressMake(ztPathGridSquare *grid, ztMemoryArena *arena)
{
	ZT_PROFILE_PATHFINDING("zt_pathProgressMake");
	zt_returnValOnNull(grid, nullptr);

	if (arena == nullptr) {
		arena = zt_memGetGlobalArena();
	}

	ztPathProgress *progress = zt_mallocStructArena(ztPathProgress, arena);

	progress->arena = arena;

	progress->origin = nullptr;
	progress->destination = nullptr;

	int nodes = grid->rows * grid->cols;

	progress->frontier_len = nodes;
	progress->frontier = zt_mallocStructArrayArena(ztPathNode *, progress->frontier_len, arena);

	progress->visited_len = nodes;
	progress->visited = zt_mallocStructArrayArena(ztPathNode *, progress->visited_len, arena);

	progress->path_size = nodes;
	progress->path = zt_mallocStructArrayArena(ztPathNode *, progress->path_size, arena);

	return progress;
}

// ------------------------------------------------------------------------------------------------

void zt_pathProgressFree(ztPathProgress *progress)
{
	ZT_PROFILE_PATHFINDING("zt_pathProgressFree");
	if (progress == nullptr) {
		return;
	}

	zt_freeArena(progress->path, progress->arena);
	zt_freeArena(progress->visited, progress->arena);
	zt_freeArena(progress->frontier, progress->arena);
	zt_freeArena(progress, progress->arena);
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_pathGridGetSteps(ztPathNode *origin, ztPathNode *destination, ztPathNode **path, int path_max)
{
	ZT_PROFILE_PATHFINDING("_zt_pathGridGetSteps");
	int steps = 0;
	bool no_mem = false;

	if (steps >= path_max) {
		steps += 1;
		no_mem = true;
	}
	else {
		path[steps++] = destination;
	}

	ztPathNode *current = destination;
	while (current != origin) {
		r32 lowest_movement_cost = ztReal32Max;
		int lowest_movement_idx = -1;
		zt_fiz(current->neighbors_count) {
			if (current->neighbors[i]->_my_move_cost >= 0 && (current->neighbors[i]->_my_move_cost < lowest_movement_cost || lowest_movement_cost == ztPathNodeValue_Impassable)) {
				lowest_movement_cost = current->neighbors[i]->_my_move_cost;
				lowest_movement_idx = i;
			}
		}

		if (lowest_movement_idx == -1) {
			return 0;
		}

		zt_fiz(current->neighbors_count) {
			if (i != lowest_movement_idx) {
				//current->neighbors[i]->_my_move_cost = ztPathNodeValue_Impassable; // prevent revisiting old nodes
			}
		}

		if (steps >= path_max) {
			no_mem = true;
		}
		else {
			path[steps] = current->neighbors[lowest_movement_idx];
		}
		steps += 1;
		//current->neighbors[lowest_movement_idx]->_my_move_cost = ztPathNodeValue_Impassable;
		current = current->neighbors[lowest_movement_idx];

		zt_assert(steps < 100000); // if you're here, you probably forgot to call zt_pathGridSquarePrepareForPathfinding - the movement costs need cleared after the last pathfinding
	}

	// now we have to reverse the array
	if (!no_mem) {
		zt_fiz(steps / 2) {
			int idx1 = i;
			int idx2 = steps - (i + 1);

			auto* temp = path[idx1];
			path[idx1] = path[idx2];
			path[idx2] = temp;
		}
	}

	return steps * (no_mem ? -1 : 1);
}

// ------------------------------------------------------------------------------------------------

int zt_pathCalculatePath(ztPathProgress *progress, ztPathNodeCost_Func *path_node_cost_func, void *path_cost_user_data, ztPathEarlyExit_Func *early_exit_func, void *early_exit_user_data, ztPathType_Enum path_type)
{
	ZT_PROFILE_PATHFINDING("zt_pathCalculatePath");
	zt_returnValOnNull(progress, 0);

	if (progress->visited_idx == 0) {
		progress->origin->_my_move_cost = 0;
		progress->frontier[progress->frontier_idx++] = progress->origin;
	}

	while (progress->frontier_idx > 0) {
		// find and remove a location in the frontier
		ztPathNode *location = progress->frontier[0];
		_zt_pathArrayRemoveFromBegin(progress->frontier, progress->frontier_len, &progress->frontier_idx);

		if (location == progress->destination) {
			break;
		}

		// mark as visited so we don't process it again
		if (!_zt_pathNodeArrayContains(progress->visited, progress->visited_idx, location)) {
			//if (!array_add_to_begin(visited, visited_len, visited_idx, location)) {
			if (!_zt_pathArrayAddToBegin(progress->visited, progress->visited_len, &progress->visited_idx, location)) {
				return 0;
			}
		}

		for (int n = 0; n < location->neighbors_count; ++n) {
			ztPathNode *neighbor = location->neighbors[n];
			if (zt_bitIsSet(neighbor->flags, ztPathNodeFlags_Ignore) || zt_bitIsSet(neighbor->flags, ztPathNodeFlags_Obstructed)) {
				continue;
			}

			if (!_zt_pathNodeArrayContains(progress->frontier, progress->frontier_idx, neighbor)) {
				r32 path_cost = (neighbor == progress->destination) ? 0.01f : (path_node_cost_func == nullptr ? zt_abs(location->position.distance(neighbor->position)) : path_node_cost_func(location, neighbor, path_cost_user_data));
				if (path_cost == ztPathNodeValue_Impassable) {
					continue;
				}
				r32 new_cost = location->_my_move_cost + path_cost;
				bool add_to_frontier = true;
				if (_zt_pathNodeArrayContains(progress->visited, progress->visited_idx, neighbor)) {
					add_to_frontier = neighbor->_my_move_cost > new_cost;
				}
				if (add_to_frontier) {
					neighbor->_my_move_cost = new_cost;

					r32 dist = progress->destination->position.distance(neighbor->position);
					int idx;
					for (idx = 0; idx < progress->frontier_idx; ++idx) {
						if (path_type == ztPathType_Dijkstra) {
							if (progress->frontier[idx]->_my_move_cost > new_cost) {
								break;
							}
						}
						else if (path_type == ztPathType_Heuristic) {
							if (progress->destination->position.distance(progress->frontier[idx]->position) > dist) {
								break;
							}
						}
						else if (path_type == ztPathType_Astar) {
							if (progress->destination->position.distance(progress->frontier[idx]->position) > dist || progress->frontier[idx]->_my_move_cost > new_cost) {
								break;
							}
						}
					}
					if (idx != progress->frontier_idx) {
						if (!_zt_pathArrayInsertBefore(progress->frontier, progress->frontier_len, &progress->frontier_idx, idx, neighbor)) {
							return 0;
						}
					}
					else {
						if (!_zt_pathArrayAddToEnd(progress->frontier, progress->frontier_len, &progress->frontier_idx, neighbor)) {
							return 0;
						}
					}
				}
			}
		}

		if (early_exit_func && early_exit_func(progress, early_exit_user_data)) {
			return -1;
		}
	}

	progress->path_count = _zt_pathGridGetSteps(progress->origin, progress->destination, progress->path, progress->path_size);
	return progress->path_count;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_audioCheckContext()
{
	ZT_PROFILE_AUDIO("_zt_audioCheckContext");
#	if defined(ZT_DSOUND)
	if (zt_game->ds_context == nullptr) {
		zt_game->ds_context = ztds_contextMake(zt_game->win_details[0].handle);
	}

	return zt_game->ds_context != nullptr;
#	endif
}

// ------------------------------------------------------------------------------------------------

ztInternal ztAudioClipID _zt_audioClipMakeFromData(void *data, i32 data_size)
{
	ZT_PROFILE_AUDIO("_zt_audioCheckContext");
	if (!_zt_audioCheckContext()) {
		return ztInvalidID;
	}

#	if defined(ZT_DSOUND)
	ztDirectSoundBuffer *buffer = ztds_bufferMake(zt_game->ds_context, (byte*)data, data_size);
	if (buffer == nullptr) {
		return ztInvalidID;
	}

	zt_assert(zt_game->audio_clips_count < zt_elementsOf(zt_game->audio_clips));

	i32 channels = 0, bits_per_sample = 0, samples_per_second = 0;
	r32 length = 0;
	ztds_bufferGetDetails(buffer, &channels, &bits_per_sample, &samples_per_second, &length);

	ztAudioClipID audio_clip_id = zt_game->audio_clips_count++;
	ztAudioClip *audio_clip = &zt_game->audio_clips[audio_clip_id];
	audio_clip->ds_buffer = buffer;
	audio_clip->length    = length;
	audio_clip->play_time = 0;
	audio_clip->flags     = 0;

	return audio_clip_id;
#	endif
}

// ------------------------------------------------------------------------------------------------

ztAudioClipID zt_audioClipMake(ztAssetManager *asset_mgr, ztAssetID asset_id)
{
	ZT_PROFILE_AUDIO("zt_audioClipMake");
	ztBlockProfiler bp_tex("zt_audioClipMake (from asset)");

	zt_returnValOnNull(asset_mgr, ztInvalidID);
	zt_assert(asset_id >= 0 && asset_id < asset_mgr->asset_count);

	zt_logDebug("loading audio asset: %s", asset_mgr->asset_name[asset_id]);

	if (asset_mgr->asset_type[asset_id] != ztAssetManagerType_AudioWAV) {
		return ztInvalidID;
	}

	i32 size = zt_assetSize(asset_mgr, asset_id);
	if (size <= 0) {
		return ztInvalidID;
	}

	char *data = zt_mallocStructArray(char, size);
	if (!data) {
		return ztInvalidID;
	}

	const char *error = nullptr;
	if (!zt_assetLoadData(asset_mgr, asset_id, data, size)) {
		error = "Unable to load asset contents";
		goto on_error;
	}

	ztAudioClipID audio_clip_id = _zt_audioClipMakeFromData(data, size);
	if (audio_clip_id == ztInvalidID) {
		error = "Unable to process audio data";
		goto on_error;
	}

	// TODO: Add reload callback

	zt_free(data);
	return audio_clip_id;

on_error:
	zt_logCritical("Unable to load audio clip (%s). %s.", asset_mgr->asset_name[asset_id], error);
	zt_free(data);
	return ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

ztAudioClipID zt_audioClipMakeFromFile(const char *file_name)
{
	ZT_PROFILE_AUDIO("zt_audioClipMakeFromFile");
	ztBlockProfiler bp_tex("zt_audioClipMakeFromFile");

	i32 size = 0;
	void *data = zt_readEntireFile(file_name, &size);
	if (data == nullptr || size == 0) {
		return ztInvalidID;
	}

	ztAudioClipID audio_clip_id = _zt_audioClipMakeFromData(data, size);

	zt_free(data);

	if (audio_clip_id == ztInvalidID) {
		zt_logCritical("Unable to load audio clip from file: %s", file_name);
	}

	return audio_clip_id;
}

// ------------------------------------------------------------------------------------------------

void zt_audioClipFree(ztAudioClipID audio_clip_id)
{
	ZT_PROFILE_AUDIO("zt_audioClipFree");
	if (audio_clip_id == ztInvalidID) {
		return;
	}

	zt_assertReturnOnFail(audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count);

	ztAudioClip *audio_clip = &zt_game->audio_clips[audio_clip_id];

#	if defined(ZT_DSOUND)
	if (audio_clip->ds_buffer) {
		ztds_bufferFree(audio_clip->ds_buffer);
		audio_clip->ds_buffer = nullptr;
	}
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_audioClipPlayOnce(ztAudioClipID audio_clip_id)
{
	ZT_PROFILE_AUDIO("zt_audioClipPlayOnce");
	if(zt_game->audio_muted) {
		return;
	}

	zt_assertReturnOnFail(audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count);
	ztAudioClip *audio_clip = &zt_game->audio_clips[audio_clip_id];
#	if defined(ZT_DSOUND)
	ztds_bufferPlay(audio_clip->ds_buffer);
	audio_clip->flags |= ztAudioClipFlags_Playing;
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_audioClipPlayLooped(ztAudioClipID audio_clip_id)
{
	ZT_PROFILE_AUDIO("zt_audioClipPlayLooped");
	if(zt_game->audio_muted) {
		return;
	}

	zt_assertReturnOnFail(audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count);
	ztAudioClip *audio_clip = &zt_game->audio_clips[audio_clip_id];
#	if defined(ZT_DSOUND)
	ztds_bufferPlayLooping(audio_clip->ds_buffer);
	audio_clip->flags |= ztAudioClipFlags_Playing | ztAudioClipFlags_Looping;
#	endif
}

// ------------------------------------------------------------------------------------------------

bool zt_audioClipIsPlaying(ztAudioClipID audio_clip_id)
{
	ZT_PROFILE_AUDIO("zt_audioClipIsPlaying");
	zt_assertReturnValOnFail(audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count, false);
	ztAudioClip *audio_clip = &zt_game->audio_clips[audio_clip_id];
	return zt_bitIsSet(audio_clip->flags, ztAudioClipFlags_Playing);
}

// ------------------------------------------------------------------------------------------------

bool zt_audioClipStop(ztAudioClipID audio_clip_id)
{
	ZT_PROFILE_AUDIO("zt_audioClipStop");
	zt_assertReturnValOnFail(audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count, false);
	ztAudioClip *audio_clip = &zt_game->audio_clips[audio_clip_id];

#	if defined(ZT_DSOUND)
	zt_assertReturnValOnFail(audio_clip->ds_buffer != nullptr, false);
	ztds_bufferStop(audio_clip->ds_buffer);
#	endif

	zt_bitRemove(audio_clip->flags, ztAudioClipFlags_Playing);
	zt_bitRemove(audio_clip->flags, ztAudioClipFlags_Looping);

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_audioSetMute(bool mute)
{
	ZT_PROFILE_AUDIO("zt_audioSetMute");
	if(mute) {
		zt_fiz(zt_game->audio_clips_count) {
			if(zt_bitIsSet(zt_game->audio_clips[i].flags, ztAudioClipFlags_Playing)) {
				zt_audioClipStop(i);
			}
		}
	}

	zt_game->audio_muted = mute;
}

// ------------------------------------------------------------------------------------------------

bool zt_audioGetMute()
{
	return 	zt_game->audio_muted;
}

// ------------------------------------------------------------------------------------------------


ztInternal void _zt_audioUpdateFrame(r32 dt)
{
	ZT_PROFILE_AUDIO("_zt_audioUpdateFrame");
#	if defined(ZT_DSOUND)
	if (!zt_game->ds_context) {
		return;
	}

	zt_fiz(zt_game->audio_clips_count) {
		if (zt_bitIsSet(zt_game->audio_clips[i].flags, ztAudioClipFlags_Playing)) {
			zt_game->audio_clips[i].play_time += dt;
			if (zt_game->audio_clips[i].play_time > zt_game->audio_clips[i].length) {
				if (zt_bitIsSet(zt_game->audio_clips[i].flags, ztAudioClipFlags_Looping)) {
					zt_game->audio_clips[i].play_time -= zt_game->audio_clips[i].length;
				}
				else {
					zt_bitRemove(zt_game->audio_clips[i].flags, ztAudioClipFlags_Playing);
				}
			}
		}
	}
#	endif
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// the _zt_callFunc<function> calls are used because it's possible for the ZT_GAME_FUNC_<function> defines
// to have naming conflicts with variables in the main function

#if !defined(ZT_DLL)
	bool ZT_GAME_FUNC_SETTINGS(ztGameDetails*, ztGameSettings*);
	ztInternal ztInline bool _zt_callFuncSettings(ztGameDetails *details, ztGameSettings *settings)
	{ return ZT_GAME_FUNC_SETTINGS(details, settings); }

	bool ZT_GAME_FUNC_INIT(ztGameDetails*, ztGameSettings*);
	ztInternal ztInline bool _zt_callFuncInit(ztGameDetails *details, ztGameSettings *settings)
	{ return ZT_GAME_FUNC_INIT(details, settings); }

	void ZT_GAME_FUNC_SCREENCHANGE(ztGameSettings *settings);
	ztInternal ztInline void _zt_callFuncScreenChange(ztGameSettings *settings)
	{ ZT_GAME_FUNC_SCREENCHANGE(settings); }

	void ZT_GAME_FUNC_CLEANUP();
	ztInternal ztInline void _zt_callFuncCleanup()
	{ ZT_GAME_FUNC_CLEANUP(); }

	bool ZT_GAME_FUNC_LOOP(r32);
	ztInternal ztInline bool _zt_callFuncLoop(r32 dt)
	{ return ZT_GAME_FUNC_LOOP(dt); }
#endif

#if defined(ZT_WINDOWS)

LRESULT CALLBACK _zt_winCallback(HWND handle, UINT msg, WPARAM w_param, LPARAM l_param);

// ------------------------------------------------------------------------------------------------

#if !defined(ZT_DLL)

bool _zt_winCreateWindow(ztGameSettings* game_settings, ztWindowDetails* window_details)
{
	ZT_PROFILE_PLATFORM("_zt_winCreateWindow");
	WNDCLASS wndcls = {};
	wndcls.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndcls.lpfnWndProc = _zt_winCallback;
	wndcls.hInstance = zt_game->hinstance;
	wndcls.hIcon = zt_game->exe_icon;
#if defined(ZT_UNICODE)
	u16 wc_game_name[1024] = { 0 };
	zt_strConvertToUTF16(ZT_GAME_NAME, zt_strLen(ZT_GAME_NAME), wc_game_name, zt_elementsOf(wc_game_name));
	wndcls.lpszClassName = (LPCWSTR)wc_game_name;
#else
	wndcls.lpszClassName = ZT_GAME_NAME;
#endif

	static bool first_call = true;
	if (first_call) {
		if (!RegisterClass(&wndcls)) {
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

	_zt_winUpdateTitle(game_settings, window_details);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool _zt_winCleanupWindow(ztWindowDetails* win_details, ztGameSettings* settings)
{
	ZT_PROFILE_PLATFORM("_zt_winCleanupWindow");
	bool context_result = _zt_rendererFreeContext(win_details);

	DestroyWindow(win_details->handle);
	
	return context_result;
}

// ------------------------------------------------------------------------------------------------

void _zt_winUpdateTitle(ztGameSettings *game_settings, ztWindowDetails *window_details)
{
	ZT_PROFILE_PLATFORM("_zt_winUpdateTitle");
	const char* renderer;
	switch(game_settings->renderer)
	{
	case ztRenderer_OpenGL: renderer = "OpenGL"; break;
	case ztRenderer_DirectX: renderer = "DirectX"; break;
	default: renderer = "Unknown Renderer"; break;
	}

	zt_debugOnly(zt_strMakePrintf(title, 1024, "%s [Renderer: %s] [Resolution: %d x %d]", ZT_GAME_NAME, renderer, game_settings->screen_w, game_settings->screen_h));
	zt_releaseOnly(zt_strMakePrintf(title, 1024, "%s", ZT_GAME_NAME));
	SetWindowTextA(window_details->handle, title);
}

#endif

// ------------------------------------------------------------------------------------------------

void _zt_winControllerInputUpdate(r32 dt);

// ------------------------------------------------------------------------------------------------

void _zt_winControllerInputInit()
{
	ZT_PROFILE_INPUT("_zt_winControllerInputInit");
	const char *libs[] = { "xinput1_4.dll", "xinput9_1_0.dll", "xinput1_3.dll" };
	zt_fiz(zt_elementsOf(libs)) {
		zt_game->hmod_xinput = LoadLibraryA(libs[i]);
		if (zt_game->hmod_xinput != NULL) {
			break;
		}
	}

	if (zt_game->hmod_xinput == NULL) {
		return;
	}

	zt_game->xinput_getState = (ztGameGlobals::xinput_getState_Func)GetProcAddress(zt_game->hmod_xinput, "XInputGetState");
	zt_game->xinput_setState = (ztGameGlobals::xinput_setState_Func)GetProcAddress(zt_game->hmod_xinput, "XInputSetState");

	zt_fiz(zt_elementsOf(zt_game->input_controllers)) {
		zt_game->input_controllers[i].connected = true;
		zt_game->xinput_haptic[i] = false;
	}

	_zt_winControllerInputUpdate(0);

	zt_fiz(zt_elementsOf(zt_game->input_controllers)) {
		zt_fjz(zt_elementsOf(zt_game->input_controllers[i].button_states)) {
			zt_game->input_controllers[i].button_states[j] = 0;
			zt_game->input_controllers[i].button_times [j] = 0;
		}
		zt_fjz(zt_elementsOf(zt_game->input_controllers[i].analog_values)) {
			zt_game->input_controllers[i].analog_values[j] = 0;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void _zt_winControllerInputCleanup()
{
	zt_game->xinput_getState = nullptr;
	zt_game->xinput_setState = nullptr;
}

// ------------------------------------------------------------------------------------------------

void _zt_winControllerInputUpdate(r32 dt)
{
	ZT_PROFILE_INPUT("_zt_winControllerInputUpdate");
	if (!zt_game->xinput_getState) {
		return;
	}

	int flags[] = { XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_RIGHT, XINPUT_GAMEPAD_START, XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB, XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER, XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y };
	zt_staticAssert(zt_elementsOf(flags) == ztInputControllerButton_Y+1);

	bool pressed[ztInputControllerButton_MAX];

	zt_fiz(zt_min(ZT_MAX_INPUT_CONTROLLERS, zt_elementsOf(zt_game->input_controllers))) {
		if (zt_game->input_controllers[i].connected) {
			XINPUT_STATE controller_state;
			if (zt_game->xinput_getState(i, &controller_state) == ERROR_SUCCESS) {

				// if analog controls are within the deadzone, we just zero them out
				if (controller_state.Gamepad.bLeftTrigger  < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) controller_state.Gamepad.bLeftTrigger = 0;
				if (controller_state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD) controller_state.Gamepad.bRightTrigger = 0;

				if (controller_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  && controller_state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) controller_state.Gamepad.sThumbLX = 0;
				if (controller_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  && controller_state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) controller_state.Gamepad.sThumbLY = 0;
				if (controller_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && controller_state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) controller_state.Gamepad.sThumbRX = 0;
				if (controller_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && controller_state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) controller_state.Gamepad.sThumbRY = 0;

				zt_fjz(zt_elementsOf(flags)) {
					pressed[j] = zt_bitIsSet(controller_state.Gamepad.wButtons, flags[j]);
				}
				pressed[ztInputControllerButton_TriggerLeft  ] = controller_state.Gamepad.bLeftTrigger != 0;
				pressed[ztInputControllerButton_TriggerRight ] = controller_state.Gamepad.bRightTrigger != 0;
				pressed[ztInputControllerButton_ThumbpadLeft ] = controller_state.Gamepad.sThumbLX != 0 || controller_state.Gamepad.sThumbLY != 0;
				pressed[ztInputControllerButton_ThumbpadRight] = controller_state.Gamepad.sThumbRX != 0 || controller_state.Gamepad.sThumbRY != 0;

				zt_fjz(zt_elementsOf(pressed)) {
					if (pressed[j]) {
						if (zt_bitIsSet(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_Pressed)) {
							zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_JustPressed);
							zt_game->input_controllers[i].button_times[j] += dt;
						}
						else {
							zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_JustReleased);
							zt_game->input_controllers[i].button_states[j] |= ztInputControllerFlags_Pressed | ztInputControllerFlags_JustPressed;
							zt_game->input_controllers[i].button_times[j] = dt;
						}
						zt_game->input_this_frame = true;
					}
					else if (zt_game->input_controllers[i].button_times[j] != 0) {
						zt_game->input_controllers[i].button_states[j] |= ztInputControllerFlags_JustReleased;
						zt_game->input_controllers[i].button_times[j] = 0;
						zt_game->input_this_frame = true;
					}
					else {
						zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_Pressed);
						zt_bitRemove(zt_game->input_controllers[i].button_states[j], ztInputControllerFlags_JustReleased);
					}
				}
				zt_game->input_controllers[i].analog_value_trigger_left      = zt_linearRemap((r32)controller_state.Gamepad.bLeftTrigger,  0.f, 255.f, 0.f, 1.f);
				zt_game->input_controllers[i].analog_value_trigger_right     = zt_linearRemap((r32)controller_state.Gamepad.bRightTrigger, 0.f, 255.f, 0.f, 1.f);
				zt_game->input_controllers[i].analog_value_thumb_pad_left_x  = zt_linearRemap((r32)controller_state.Gamepad.sThumbLX, -32768.f, 32768.f, -1.f, 1.f);
				zt_game->input_controllers[i].analog_value_thumb_pad_left_y  = zt_linearRemap((r32)controller_state.Gamepad.sThumbLY, -32768.f, 32768.f, -1.f, 1.f);
				zt_game->input_controllers[i].analog_value_thumb_pad_right_x = zt_linearRemap((r32)controller_state.Gamepad.sThumbRX, -32768.f, 32768.f, -1.f, 1.f);
				zt_game->input_controllers[i].analog_value_thumb_pad_right_y = zt_linearRemap((r32)controller_state.Gamepad.sThumbRY, -32768.f, 32768.f, -1.f, 1.f);

				for (int j = 2; j < zt_elementsOf(zt_game->input_controllers[i].analog_values); ++j) {
					if (zt_abs(zt_game->input_controllers[i].analog_values[j]) < 0.05f) {
						zt_game->input_controllers[i].analog_values[j] = 0;
					}
				}

				if (zt_game->xinput_haptic[i] != 0.f) {
					zt_game->xinput_haptic[i] += dt;
					if (zt_game->xinput_haptic[i] > 1 / 60.f) {
						zt_game->xinput_haptic[i] = 0;
						XINPUT_VIBRATION vibration = { 0, 0 };
						zt_game->xinput_setState(i, &vibration);
					}
				}
			}
			else {
				zt_game->input_controllers[i].connected = false;

				if (dt != 0) {
					zt_logInfo("Controller %d disconnected", i + 1);
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

void _zt_winControllerInputHapticFeedback(int idx, r32 strength_low, r32 strength_high)
{
	ZT_PROFILE_INPUT("_zt_winControllerInputHapticFeedback");
	zt_assertReturnOnFail(idx >= 0 && idx < ZT_MAX_INPUT_CONTROLLERS);

	if (zt_game->xinput_setState) {
		XINPUT_VIBRATION vibration = { zt_convertToi32Floor(strength_low * 65535.f), zt_convertToi32Floor(strength_high * 65535.f) };
		zt_game->xinput_setState(idx, &vibration);
		zt_game->xinput_haptic[idx] = 0.01f;
	}
}

// ------------------------------------------------------------------------------------------------

void _zt_win_processMessages()
{
	ZT_PROFILE_PLATFORM("_zt_win_processMessages");
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT) {
		zt_game->quit_requested = false;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal HINSTANCE _zt_hinstance;

#endif // ZT_WINDOWS

// ------------------------------------------------------------------------------------------------

#if !defined(ZT_DLL)

int main(int argc, char **argv)
{
	char app_path[ztFileMaxPath] = {0};
	zt_fileGetAppPath(app_path, sizeof(app_path));

	char user_path[ztFileMaxPath] = {0};

#	if defined(ZT_GAME_LOCAL_ONLY)
	zt_fileGetCurrentPath(user_path, sizeof(user_path));
#	else
	zt_fileGetUserPath(user_path, sizeof(user_path), ZT_GAME_NAME);
#	endif

	zt_game = (ztGameGlobals *)malloc(sizeof(ztGameGlobals));
	zt_memSet(zt_game, zt_sizeof(ztGameGlobals), 0);
	{
		char size[128];
		zt_strBytesToString(size, zt_sizeof(size), zt_sizeof(ztGameGlobals));
		zt_logDebug("main: initial memory: %s", size);

		zt_game->hinstance = _zt_hinstance;

		char exe_name[ztFileMaxPath];
		GetModuleFileNameA(NULL, exe_name, zt_elementsOf(exe_name));
		zt_game->exe_icon = ExtractIconA(_zt_hinstance, exe_name, 0);
	}

	zt_game->main_thread_id = zt_threadGetCurrentID();

	ztWindowDetails *win_details;

	_zt_profilerInit();
	zt_profilerFrameBegin();
	{
		ZT_PROFILE_PLATFORM("main(init)");

		{ // init input
			_zt_inputSetupKeys();

			for (int i = 0; i < ztInputKeys_MAX; ++i) {
				zt_game->input_keys_mapping[zt_game->input_keys[i].platform_mapping] = zt_game->input_keys[i].code;
			}
			zt_memSet(&zt_game->input_mouse, zt_sizeof(ztInputMouse), 0);
			zt_game->input_mouse.cursor = ztInputMouseCursor_Arrow;
		}

		zt_game->game_details = {};
		zt_game->game_details.argc = argc;
		zt_game->game_details.argv = argv;

		zt_game->game_details.app_path = app_path;
		zt_game->game_details.user_path = user_path;

		zt_game->game_details.current_frame = 1;

		ztGameSettings *game_settings = &zt_game->win_game_settings[0];
		zt_game->win_count += 1;

		game_settings->memory = zt_megabytes(64);
		game_settings->native_w = game_settings->screen_w = 1280;
		game_settings->native_h = game_settings->screen_h = 720;
		game_settings->pixels_per_unit = 64;

		game_settings->renderer = ztRenderer_OpenGL;
		game_settings->renderer_flags = ztRendererFlags_Windowed | ztRendererFlags_LockAspect;
		game_settings->renderer_screen_change_behavior = ztRendererScreenChangeBehavior_Resize;
		game_settings->renderer_memory = zt_megabytes(16);

		game_settings->threaded_frame_jobs      = zt_max(0, ZT_MAX_THREADS - 2);
		game_settings->threaded_background_jobs = 1;

		if(game_settings->threaded_frame_jobs > 3) {
			game_settings->threaded_frame_jobs -= 1;
			game_settings->threaded_background_jobs += 1;
		}

		if (!_zt_callFuncSettings(&zt_game->game_details, game_settings))
			return 1;

		zt_logDebug("main: app path: %s", zt_game->game_details.app_path);
		zt_logDebug("main: user path: %s", zt_game->game_details.user_path);

		char app_memory_str[128];
		zt_strBytesToString(app_memory_str, sizeof(app_memory_str), game_settings->memory);
		zt_logDebug("main: initializing %s of memory", app_memory_str);

		zt_memPushGlobalArena(zt_memMakeArena(game_settings->memory));

		win_details = &zt_game->win_details[0];
		if (!_zt_winCreateWindow(game_settings, win_details))
			return 1;

		{ // more input init
			POINT cursor_pos;
			GetCursorPos(&cursor_pos);

			zt_game->input_mouse.screen_x = cursor_pos.x - win_details->window_rect.left;
			zt_game->input_mouse.screen_y = cursor_pos.y - win_details->window_rect.top;

			_zt_winControllerInputInit();
		}

		zt_game->renderer_memory_size = game_settings->renderer_memory;
		zt_game->renderer_memory = (byte*)zt_memAlloc(zt_memGetGlobalArena(), zt_game->renderer_memory_size);

		if (!_zt_rendererSetRendererFuncs(game_settings->renderer)) {
			zt_logCritical("main: Unknown renderer (%d)", game_settings->renderer);
			return 1;
		}

		if (!_zt_rendererMakeContext(win_details, game_settings, game_settings->renderer_flags)) {
			zt_logCritical("main: Failed to create renderer context on main window");
			return 1;
		}

		zt_fiz(zt_elementsOf(_zt_default_shaders)) {
			if (zt_shaderMake(_zt_default_shaders_names[i], _zt_default_shaders[i], zt_strLen(_zt_default_shaders[i])) == ztInvalidID) {
				zt_logCritical("main: Failed to load default shader: %s", _zt_default_shaders_names[i]);
				return 1;
			}
		}

		// make a simple white texture to use as a default
		{
			ztTextureID white_tex = zt_textureMakeRenderTarget(8, 8);
			zt_textureRenderTargetPrepare(white_tex);
			zt_rendererClear(ztVec4::one);
			zt_textureRenderTargetCommit(white_tex);
		}

		if (!_zt_callFuncInit(&zt_game->game_details, game_settings))
			return 1;

		_zt_threadJobQueueInit(game_settings->threaded_frame_jobs, game_settings->threaded_background_jobs);

		_zt_callFuncScreenChange(game_settings);
	}
	zt_profilerFrameEnd();

	r32 dt = 0;
	r64 time_last = zt_getTime();

	bool mouse_look = zt_game->input_mouse_look;
	POINT mouse_prev_frame = { 0, 0 };
	if (mouse_look) {
		SetCursorPos(0, 0);
	}

	do {
		zt_profilerFrameBegin();
		ZT_PROFILE_INPUT("Game Loop");

		{
			ZT_PROFILE_INPUT("Mouse Handling");

			if (mouse_look != zt_game->input_mouse_look) {
				mouse_look = zt_game->input_mouse_look;
				if (mouse_look) {
					GetCursorPos(&mouse_prev_frame);
				}
			}
			if (zt_game->input_mouse_look) {
				POINT mouse_this_frame;
				GetCursorPos(&mouse_this_frame);

				if (GetFocus() == win_details->handle) {
					zt_game->input_mouse.screen_x = 0;
					zt_game->input_mouse.screen_y = 0;

					zt_game->input_mouse.delta_x = mouse_this_frame.x - mouse_prev_frame.x;
					zt_game->input_mouse.delta_y = mouse_this_frame.y - mouse_prev_frame.y;

					mouse_prev_frame.x = win_details->window_rect.left + ((win_details->window_rect.right - win_details->window_rect.left) / 2);
					mouse_prev_frame.y = win_details->window_rect.top + ((win_details->window_rect.bottom - win_details->window_rect.top) / 2);

					SetCursorPos(mouse_prev_frame.x, mouse_prev_frame.y);
				}
				else {
					zt_game->input_mouse.screen_x = 0;
					zt_game->input_mouse.screen_y = 0;
					zt_game->input_mouse.delta_x  = 0;
					zt_game->input_mouse.delta_y  = 0;
				}
			}
		}
		r64 time_this = zt_getTime();
		dt = (r32)(time_this - time_last);
		time_last = time_this;

		zt_debugOnly(if (dt > 1.f / 30.f) dt = 1.f / 30.f); // keep the delta time meaningful during debugging

		_zt_audioUpdateFrame(dt);

		if (!_zt_callFuncLoop(dt))
			break;

		zt_fiz(zt_game->win_count) {
			_zt_rendererSwapBuffers(&zt_game->win_details[i]);
		}

		if (zt_game->renderer_requests_count) {
			if (!_zt_rendererRequestProcess())
				break;
		}

		_zt_inputClearState(false);
		_zt_win_processMessages();
		_zt_winControllerInputUpdate(dt);

		_zt_threadJobQueueUpdate();

		++zt_game->game_details.current_frame;

		zt_profilerFrameEnd();
	} while (!zt_game->quit_requested);

	zt_profilerFrameBegin();
	{
		ZT_PROFILE_PLATFORM("main(cleanup)");
		zt_textureFree(0); // free the white tex

		_zt_threadJobQueueFree();

		zt_fiz(zt_game->fonts_count_system) {
			zt_fontFree(i);
		}

		_zt_callFuncCleanup();

#	if defined(ZT_DSOUND)
		if(zt_game->ds_context != nullptr) {
			ztds_contextFree(zt_game->ds_context);
		}
#	endif

		zt_fiz(zt_game->shaders_count) {
			zt_game->shaders[i].asset_mgr = nullptr;
			zt_shaderFree((ztShaderID)i);
		}
		zt_fiz(zt_game->textures_count) {
			//zt_textureFree((ztTextureID)i);
		}

		zt_memFree(zt_memGetGlobalArena(), zt_game->renderer_memory);

		_zt_winControllerInputCleanup();
		_zt_winCleanupWindow(&zt_game->win_details[0], &zt_game->win_game_settings[0]);

		zt_memDumpArena(zt_memGetGlobalArena(), "main memory");
		zt_memFreeArena(zt_memGetGlobalArena());
		zt_memPopGlobalArena();
	}
	zt_profilerFrameEnd();
	_zt_profilerFree();

	free(zt_game);

	return 0;
}

#endif

// ------------------------------------------------------------------------------------------------

#if defined(ZT_WINDOWS) && !defined(ZT_DLL)

#if !defined(ZT_PLATFORM_WIN32_CONSOLE) && !defined(ZT_PLATFORM_WIN64_CONSOLE)

int CALLBACK WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR cmd_line, int cmd_show)
{
	_zt_hinstance = h_instance;

	char* argv[128];
	int argc = 0;

	if (cmd_line != nullptr) {
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
	bool repeated = (msg.lParam & 0xffff) != 0;

	if (was_down != is_down || repeated) {
		zt_game->input_this_frame = true;

		auto* input_key = &zt_game->input_keys[zt_game->input_keys_mapping[key_code]];
		
		input_key->flags = input_key->display == 0 ? ztInputKeyFlags_StateKey : 0;

		if (is_down && !was_down) {
			input_key->flags |= ztInputKeyFlags_JustPressed;
			input_key->time_pressed = zt_getTime();
		}

		if (!is_down && was_down) input_key->flags |= ztInputKeyFlags_JustReleased;
		if (is_down) input_key->flags |= ztInputKeyFlags_Pressed;

		if (is_down && repeated) input_key->flags |= ztInputKeyFlags_JustRepeated;

		if ( is_down && (!was_down || repeated) && zt_game->input_key_strokes_count < zt_elementsOf(zt_game->input_key_strokes) ) {
			zt_game->input_key_strokes[zt_game->input_key_strokes_count++] = input_key->code;
		}

		switch(key_code)
		{
			case VK_F4: {
#if !defined(ZT_GAME_NO_ALTF4)
				if ( GetAsyncKeyState(VK_MENU) ) {
					zt_game->quit_requested = true;	// ALT+F4 needs to close our game
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

	zt_fiz(zt_game->win_count) {
		if (zt_game->win_details[i].handle == handle) {
			game_settings = &zt_game->win_game_settings[i];
			window_details = &zt_game->win_details[i];
			break;
		}
	}

	LRESULT result = 0;

	switch (msg)
	{
		case WM_QUIT: {
			zt_game->quit_requested = false;
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
			struct local
			{
				ztInternal void button_pressed(ztWindowDetails *win_details, i32& input_state, bool is_down, bool was_down)
				{
					input_state = 0;
					if (is_down) input_state |= ztInputMouseFlags_Pressed;
					if (is_down && !was_down) input_state |= ztInputMouseFlags_JustPressed;
					if (!is_down && was_down) input_state |= ztInputMouseFlags_JustReleased;

					if (is_down) {
						if (zt_game->input_mouse_captures == 0) {
							SetCapture(win_details->handle); // required so that events continue to be sent during dragging
						}
						zt_game->input_mouse_captures += 1;
					}
					else {
						if (--zt_game->input_mouse_captures == 0) {
							ReleaseCapture();
						}
					}
				}
			};

			zt_game->input_this_frame = true;

			switch (msg)
			{
				case WM_MOUSEMOVE: {
					int x = GET_X_LPARAM(l_param);// - window_details->window_rect.left;
					int y = GET_Y_LPARAM(l_param);// - window_details->window_rect.top;

					zt_game->input_mouse.delta_x = x - zt_game->input_mouse.screen_x;
					zt_game->input_mouse.delta_y = y - zt_game->input_mouse.screen_y;

					zt_game->input_mouse.screen_x = x;
					zt_game->input_mouse.screen_y = y;
				} break;

				case WM_LBUTTONDOWN: local::button_pressed(window_details, zt_game->input_mouse.button_state_left, true, false); break;
				case WM_LBUTTONUP: local::button_pressed(window_details, zt_game->input_mouse.button_state_left, false, true); break;

				case WM_RBUTTONDOWN: local::button_pressed(window_details, zt_game->input_mouse.button_state_right, true, false); break;
				case WM_RBUTTONUP: local::button_pressed(window_details, zt_game->input_mouse.button_state_right, false, true); break;

				case WM_MBUTTONDOWN: local::button_pressed(window_details, zt_game->input_mouse.button_state_middle, true, false); break;
				case WM_MBUTTONUP: local::button_pressed(window_details, zt_game->input_mouse.button_state_middle, false, true); break;

				case WM_MOUSEWHEEL: {
					zt_game->input_mouse.wheel_delta = GET_WHEEL_DELTA_WPARAM(w_param) / 120;
				} break;
			}
		} break;

		case WM_DESTROY:
		case WM_CLEAR: {
			if (window_details && window_details == &zt_game->win_details[0]) {
				zt_game->quit_requested = true;
			}
			else {
				_zt_winCleanupWindow(window_details, game_settings);
			}
		} break;

		case WM_MOVE:
		case WM_SIZE: {
			if (window_details) {
				GetClientRect(window_details->handle, &window_details->client_rect);
				GetWindowRect(window_details->handle, &window_details->window_rect);

				int screen_w = window_details->client_rect.right - window_details->client_rect.left;
				int screen_h = window_details->client_rect.bottom - window_details->client_rect.top;
				int native_w = game_settings->native_w;
				int native_h = game_settings->native_h;
				int native_w_reset = 0;
				int native_h_reset = 0;

				// the viewport scales to the width of the screen (resizing up/down doesn't affect the size of things)
				if (game_settings->renderer_screen_change_behavior == ztRendererScreenChangeBehavior_ScaleToHorz) {
					native_w_reset = native_w;
					native_h_reset = native_h;

					r32 screen_aspect_w = screen_w / (r32)native_w;
					r32 screen_aspect_h = screen_h / (r32)native_h;

					if ( zt_real32Eq(screen_aspect_w, 1.f) && zt_real32Eq(screen_aspect_h, 1.f)) {
						// no aspect change, do nothing
					}
					else {
						if (screen_aspect_w < 1.f) {
							screen_aspect_h /= screen_aspect_w;
							screen_aspect_w = 1;
						}
						native_w = zt_convertToi32Ceil(native_w * screen_aspect_w);
						native_h = zt_convertToi32Ceil(native_h * screen_aspect_h);
					}
				}
				// the viewport scales to the height of the screen (resizing left/right doesn't affect the size of things)
				else if (game_settings->renderer_screen_change_behavior == ztRendererScreenChangeBehavior_ScaleToVert) {
					native_w_reset = native_w;
					native_h_reset = native_h;

					r32 screen_aspect_w = screen_w / (r32)native_w;
					r32 screen_aspect_h = screen_h / (r32)native_h;

					if (zt_real32Eq(screen_aspect_w, 1.f) && zt_real32Eq(screen_aspect_h, 1.f)) {
						// no aspect change, do nothing
					}
					else {
						if (screen_aspect_h < 1.f) {
							screen_aspect_w /= screen_aspect_h;
							screen_aspect_h = 1;
						}
						native_w = zt_convertToi32Ceil(native_w * screen_aspect_w);
						native_h = zt_convertToi32Ceil(native_h * screen_aspect_h);
					}
				}
				else if (game_settings->renderer_screen_change_behavior == ztRendererScreenChangeBehavior_Resize) {
					native_h = screen_h;
					native_w = screen_w;
				}
				else {
					screen_w = native_w;
					screen_h = native_h;
				}

				game_settings->native_h = native_h;
				game_settings->native_w = native_w;
				game_settings->screen_w = screen_w;
				game_settings->screen_h = screen_h;

				zt_openGLSupport(if (window_details->gl_context) ztgl_contextSetSize(window_details->gl_context, screen_w, screen_h));
				zt_directxSupport(if (window_details->dx_context) ztdx_contextSetSize(window_details->dx_context, screen_w, screen_h));

				_zt_rendererSetViewport(window_details, game_settings, true);
				_zt_callFuncScreenChange(game_settings);
				_zt_winUpdateTitle(game_settings, window_details);

				if (native_w_reset != 0 && native_h_reset != 0) {
					game_settings->native_w = native_w_reset;
					game_settings->native_h = native_h_reset;
				}
			}
		} break;

		case WM_SIZING: {
			if (game_settings && zt_bitIsSet(game_settings->renderer_flags, ztRendererFlags_LockAspect)) {
				r32 aspect_ratio = game_settings->native_h / (r32)game_settings->native_w;

				RECT size;
				memcpy(&size, (const void*)l_param, sizeof(RECT));

				int width = size.right - size.left;
				int height = size.bottom - size.top;

				RECT client_size;
				GetClientRect(window_details->handle, &client_size);

				int c_width = (client_size.right - client_size.left);
				int c_height = (client_size.bottom - client_size.top);

				int w_diff = width - c_width;
				int h_diff = height - c_height;

				//zt_logDebug("window w/h: %d/%d; client w/h: %d/%d; diff w/h: %d/%d", width, height, c_width, c_height, w_diff, h_diff);

				switch (w_param)
				{
					case WMSZ_LEFT:
					case WMSZ_RIGHT: {
						size.bottom = zt_convertToi32Floor(c_width * aspect_ratio + h_diff) + size.top;
					} break;

					case WMSZ_TOP:
					case WMSZ_BOTTOM: {
						size.right = zt_convertToi32Floor(c_height * (1 / aspect_ratio) + w_diff) + size.left;
					} break;

					case WMSZ_TOPRIGHT:
					case WMSZ_TOPLEFT:
					case WMSZ_BOTTOMRIGHT:
					case WMSZ_BOTTOMLEFT: {
						r32 w_pct = c_width / (r32)game_settings->native_w;
						r32 h_pct = c_height / (r32)game_settings->native_h;

						if (w_pct > h_pct) {
							height = (int)(game_settings->native_h * w_pct);
						}
						else {
							width = (int)(game_settings->native_w * h_pct);
						}

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
				if (zt_game->input_mouse_look || LOWORD(l_param) == HTCLIENT) {
					SetCursor(NULL);
					zt_game->input_mouse.over_window = true;
				}
				else {
					zt_game->input_mouse.over_window = false;
					SetCursor(LoadCursor(NULL, IDC_ARROW));
				}
			}
			else {
				zt_game->input_mouse.over_window = false;
				zt_inputMouseSetCursor(zt_game->input_mouse.cursor);
			}
		} break;

		case WM_KILLFOCUS: {
			//_zt_inputClearState(true);
		} break;

		default: {
			result = DefWindowProc(handle, msg, w_param, l_param);
		} break;
	}

	return result;
}

#endif // ZT_WINDOWS

// Embedded stb_image.h:
#define STB_IMAGE_IMPLEMENTATION

// ------------------------------------------------------------------------------------------------

/* stb_image - v2.12 - public domain image loader - http://nothings.org/stb_image.h
no warranty implied; use at your own risk

Do this:
#define STB_IMAGE_IMPLEMENTATION
before you include this file in *one* C or C++ file to create the implementation.

// i.e. it should look like this:
#include ...
#include ...
#include ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

You can #define STBI_ASSERT(x) before the #include to avoid using assert.h.
And #define STBI_MALLOC, STBI_REALLOC, and STBI_FREE to avoid using malloc,realloc,free


QUICK NOTES:
Primarily of interest to game developers and other people who can
avoid problematic images and only need the trivial interface

JPEG baseline & progressive (12 bpc/arithmetic not supported, same as stock IJG lib)
PNG 1/2/4/8-bit-per-channel (16 bpc not supported)

TGA (not sure what subset, if a subset)
BMP non-1bpp, non-RLE
PSD (composited view only, no extra channels, 8/16 bit-per-channel)

GIF (*comp always reports as 4-channel)
HDR (radiance rgbE format)
PIC (Softimage PIC)
PNM (PPM and PGM binary only)

Animated GIF still needs a proper API, but here's one way to do it:
http://gist.github.com/urraka/685d9a6340b26b830d49

- decode from memory or through FILE (define STBI_NO_STDIO to remove code)
- decode from arbitrary I/O callbacks
- SIMD acceleration on x86/x64 (SSE2) and ARM (NEON)

Full documentation under "DOCUMENTATION" below.


Revision 2.00 release notes:

- Progressive JPEG is now supported.

- PPM and PGM binary formats are now supported, thanks to Ken Miller.

- x86 platforms now make use of SSE2 SIMD instructions for
JPEG decoding, and ARM platforms can use NEON SIMD if requested.
This work was done by Fabian "ryg" Giesen. SSE2 is used by
default, but NEON must be enabled explicitly; see docs.

With other JPEG optimizations included in this version, we see
2x speedup on a JPEG on an x86 machine, and a 1.5x speedup
on a JPEG on an ARM machine, relative to previous versions of this
library. The same results will not obtain for all JPGs and for all
x86/ARM machines. (Note that progressive JPEGs are significantly
slower to decode than regular JPEGs.) This doesn't mean that this
is the fastest JPEG decoder in the land; rather, it brings it
closer to parity with standard libraries. If you want the fastest
decode, look elsewhere. (See "Philosophy" section of docs below.)

See final bullet items below for more info on SIMD.

- Added STBI_MALLOC, STBI_REALLOC, and STBI_FREE macros for replacing
the memory allocator. Unlike other STBI libraries, these macros don't
support a context parameter, so if you need to pass a context in to
the allocator, you'll have to store it in a global or a thread-local
variable.

- Split existing STBI_NO_HDR flag into two flags, STBI_NO_HDR and
STBI_NO_LINEAR.
STBI_NO_HDR:     suppress implementation of .hdr reader format
STBI_NO_LINEAR:  suppress high-dynamic-range light-linear float API

- You can suppress implementation of any of the decoders to reduce
your code footprint by #defining one or more of the following
symbols before creating the implementation.

STBI_NO_JPEG
STBI_NO_PNG
STBI_NO_BMP
STBI_NO_PSD
STBI_NO_TGA
STBI_NO_GIF
STBI_NO_HDR
STBI_NO_PIC
STBI_NO_PNM   (.ppm and .pgm)

- You can request *only* certain decoders and suppress all other ones
(this will be more forward-compatible, as addition of new decoders
doesn't require you to disable them explicitly):

STBI_ONLY_JPEG
STBI_ONLY_PNG
STBI_ONLY_BMP
STBI_ONLY_PSD
STBI_ONLY_TGA
STBI_ONLY_GIF
STBI_ONLY_HDR
STBI_ONLY_PIC
STBI_ONLY_PNM   (.ppm and .pgm)

Note that you can define multiples of these, and you will get all
of them ("only x" and "only y" is interpreted to mean "only x&y").

- If you use STBI_NO_PNG (or _ONLY_ without PNG), and you still
want the zlib decoder to be available, #define STBI_SUPPORT_ZLIB

- Compilation of all SIMD code can be suppressed with
#define STBI_NO_SIMD
It should not be necessary to disable SIMD unless you have issues
compiling (e.g. using an x86 compiler which doesn't support SSE
intrinsics or that doesn't support the method used to detect
SSE2 support at run-time), and even those can be reported as
bugs so I can refine the built-in compile-time checking to be
smarter.

- The old STBI_SIMD system which allowed installing a user-defined
IDCT etc. has been removed. If you need this, don't upgrade. My
assumption is that almost nobody was doing this, and those who
were will find the built-in SIMD more satisfactory anyway.

- RGB values computed for JPEG images are slightly different from
previous versions of stb_image. (This is due to using less
integer precision in SIMD.) The C code has been adjusted so
that the same RGB values will be computed regardless of whether
SIMD support is available, so your app should always produce
consistent results. But these results are slightly different from
previous versions. (Specifically, about 3% of available YCbCr values
will compute different RGB results from pre-1.49 versions by +-1;
most of the deviating values are one smaller in the G channel.)

- If you must produce consistent results with previous versions of
stb_image, #define STBI_JPEG_OLD and you will get the same results
you used to; however, you will not get the SIMD speedups for
the YCbCr-to-RGB conversion step (although you should still see
significant JPEG speedup from the other changes).

Please note that STBI_JPEG_OLD is a temporary feature; it will be
removed in future versions of the library. It is only intended for
near-term back-compatibility use.


Latest revision history:
2.12  (2016-04-02) fix typo in 2.11 PSD fix that caused crashes
2.11  (2016-04-02) 16-bit PNGS; enable SSE2 in non-gcc x64
RGB-format JPEG; remove white matting in PSD;
allocate large structures on the stack;
correct channel count for PNG & BMP
2.10  (2016-01-22) avoid warning introduced in 2.09
2.09  (2016-01-16) 16-bit TGA; comments in PNM files; STBI_REALLOC_SIZED
2.08  (2015-09-13) fix to 2.07 cleanup, reading RGB PSD as RGBA
2.07  (2015-09-13) partial animated GIF support
limited 16-bit PSD support
minor bugs, code cleanup, and compiler warnings
2.06  (2015-04-19) fix bug where PSD returns wrong '*comp' value
2.05  (2015-04-19) fix bug in progressive JPEG handling, fix warning
2.04  (2015-04-15) try to re-enable SIMD on MinGW 64-bit
2.03  (2015-04-12) additional corruption checking
stbi_set_flip_vertically_on_load
fix NEON support; fix mingw support
2.02  (2015-01-19) fix incorrect assert, fix warning
2.01  (2015-01-17) fix various warnings
2.00b (2014-12-25) fix STBI_MALLOC in progressive JPEG
2.00  (2014-12-25) optimize JPEG, including x86 SSE2 & ARM NEON SIMD
progressive JPEG
PGM/PPM support
STBI_MALLOC,STBI_REALLOC,STBI_FREE
STBI_NO_*, STBI_ONLY_*
GIF bugfix

See end of file for full revision history.


============================    Contributors    =========================

Image formats                          Extensions, features
Sean Barrett (jpeg, png, bmp)          Jetro Lauha (stbi_info)
Nicolas Schulz (hdr, psd)              Martin "SpartanJ" Golini (stbi_info)
Jonathan Dummer (tga)                  James "moose2000" Brown (iPhone PNG)
Jean-Marc Lienher (gif)                Ben "Disch" Wenger (io callbacks)
Tom Seddon (pic)                       Omar Cornut (1/2/4-bit PNG)
Thatcher Ulrich (psd)                  Nicolas Guillemot (vertical flip)
Ken Miller (pgm, ppm)                  Richard Mitton (16-bit PSD)
urraka@github (animated gif)           Junggon Kim (PNM comments)
Daniel Gibson (16-bit TGA)

Optimizations & bugfixes
Fabian "ryg" Giesen
Arseny Kapoulkine

Bug & warning fixes
Marc LeBlanc            David Woo          Guillaume George   Martins Mozeiko
Christpher Lloyd        Martin Golini      Jerry Jansson      Joseph Thomson
Dave Moore              Roy Eltham         Hayaki Saito       Phil Jordan
Won Chun                Luke Graham        Johan Duparc       Nathan Reed
the Horde3D community   Thomas Ruf         Ronny Chevalier    Nick Verigakis
Janez Zemva             John Bartholomew   Michal Cichon      svdijk@github
Jonathan Blow           Ken Hamada         Tero Hanninen      Baldur Karlsson
Laurent Gomila          Cort Stratton      Sergio Gonzalez    romigrou@github
Aruelien Pocheville     Thibault Reuille   Cass Everitt       Matthew Gregan
Ryamond Barbiero        Paul Du Bois       Engin Manap        snagar@github
Michaelangel007@github  Oriol Ferrer Mesia socks-the-fox
Blazej Dariusz Roszkowski


LICENSE

This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.

*/

#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STBI_INCLUDE_STB_IMAGE_H

// DOCUMENTATION
//
// Limitations:
//    - no 16-bit-per-channel PNG
//    - no 12-bit-per-channel JPEG
//    - no JPEGs with arithmetic coding
//    - no 1-bit BMP
//    - GIF always returns *comp=4
//
// Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)
//
// Standard parameters:
//    int *x       -- outputs image width in pixels
//    int *y       -- outputs image height in pixels
//    int *comp    -- outputs # of image components in image file
//    int req_comp -- if non-zero, # of image components requested in result
//
// The return value from an image loader is an 'unsigned char *' which points
// to the pixel data, or NULL on an allocation failure or if the image is
// corrupt or invalid. The pixel data consists of *y scanlines of *x pixels,
// with each pixel consisting of N interleaved 8-bit components; the first
// pixel pointed to is top-left-most in the image. There is no padding between
// image scanlines or between pixels, regardless of format. The number of
// components N is 'req_comp' if req_comp is non-zero, or *comp otherwise.
// If req_comp is non-zero, *comp has the number of components that _would_
// have been output otherwise. E.g. if you set req_comp to 4, you will always
// get RGBA output, but you can check *comp to see if it's trivially opaque
// because e.g. there were only 3 channels in the source image.
//
// An output image with N components has the following components interleaved
// in this order in each pixel:
//
//     N=#comp     components
//       1           grey
//       2           grey, alpha
//       3           red, green, blue
//       4           red, green, blue, alpha
//
// If image loading fails for any reason, the return value will be NULL,
// and *x, *y, *comp will be unchanged. The function stbi_failure_reason()
// can be queried for an extremely brief, end-user unfriendly explanation
// of why the load failed. Define STBI_NO_FAILURE_STRINGS to avoid
// compiling these strings at all, and STBI_FAILURE_USERMSG to get slightly
// more user-friendly ones.
//
// Paletted PNG, BMP, GIF, and PIC images are automatically depalettized.
//
// ===========================================================================
//
// Philosophy
//
// stb libraries are designed with the following priorities:
//
//    1. easy to use
//    2. easy to maintain
//    3. good performance
//
// Sometimes I let "good performance" creep up in priority over "easy to maintain",
// and for best performance I may provide less-easy-to-use APIs that give higher
// performance, in addition to the easy to use ones. Nevertheless, it's important
// to keep in mind that from the standpoint of you, a client of this library,
// all you care about is #1 and #3, and stb libraries do not emphasize #3 above all.
//
// Some secondary priorities arise directly from the first two, some of which
// make more explicit reasons why performance can't be emphasized.
//
//    - Portable ("ease of use")
//    - Small footprint ("easy to maintain")
//    - No dependencies ("ease of use")
//
// ===========================================================================
//
// I/O callbacks
//
// I/O callbacks allow you to read from arbitrary sources, like packaged
// files or some other source. Data read from callbacks are processed
// through a small internal buffer (currently 128 bytes) to try to reduce
// overhead.
//
// The three functions you must define are "read" (reads some bytes of data),
// "skip" (skips some bytes of data), "eof" (reports if the stream is at the end).
//
// ===========================================================================
//
// SIMD support
//
// The JPEG decoder will try to automatically use SIMD kernels on x86 when
// supported by the compiler. For ARM Neon support, you must explicitly
// request it.
//
// (The old do-it-yourself SIMD API is no longer supported in the current
// code.)
//
// On x86, SSE2 will automatically be used when available based on a run-time
// test; if not, the generic C versions are used as a fall-back. On ARM targets,
// the typical path is to have separate builds for NEON and non-NEON devices
// (at least this is true for iOS and Android). Therefore, the NEON support is
// toggled by a build flag: define STBI_NEON to get NEON loops.
//
// The output of the JPEG decoder is slightly different from versions where
// SIMD support was introduced (that is, for versions before 1.49). The
// difference is only +-1 in the 8-bit RGB channels, and only on a small
// fraction of pixels. You can force the pre-1.49 behavior by defining
// STBI_JPEG_OLD, but this will disable some of the SIMD decoding path
// and hence cost some performance.
//
// If for some reason you do not want to use any of SIMD code, or if
// you have issues compiling it, you can disable it entirely by
// defining STBI_NO_SIMD.
//
// ===========================================================================
//
// HDR image support   (disable by defining STBI_NO_HDR)
//
// stb_image now supports loading HDR images in general, and currently
// the Radiance .HDR file format, although the support is provided
// generically. You can still load any file through the existing interface;
// if you attempt to load an HDR file, it will be automatically remapped to
// LDR, assuming gamma 2.2 and an arbitrary scale factor defaulting to 1;
// both of these constants can be reconfigured through this interface:
//
//     stbi_hdr_to_ldr_gamma(2.2f);
//     stbi_hdr_to_ldr_scale(1.0f);
//
// (note, do not use _inverse_ constants; stbi_image will invert them
// appropriately).
//
// Additionally, there is a new, parallel interface for loading files as
// (linear) floats to preserve the full dynamic range:
//
//    float *data = stbi_loadf(filename, &x, &y, &n, 0);
//
// If you load LDR images through this interface, those images will
// be promoted to floating point values, run through the inverse of
// constants corresponding to the above:
//
//     stbi_ldr_to_hdr_scale(1.0f);
//     stbi_ldr_to_hdr_gamma(2.2f);
//
// Finally, given a filename (or an open file or memory block--see header
// file for details) containing image data, you can query for the "most
// appropriate" interface to use (that is, whether the image is HDR or
// not), using:
//
//     stbi_is_hdr(char *filename);
//
// ===========================================================================
//
// iPhone PNG support:
//
// By default we convert iphone-formatted PNGs back to RGB, even though
// they are internally encoded differently. You can disable this conversion
// by by calling stbi_convert_iphone_png_to_rgb(0), in which case
// you will always just get the native iphone "format" through (which
// is BGR stored in RGB).
//
// Call stbi_set_unpremultiply_on_load(1) as well to force a divide per
// pixel to remove any premultiplied alpha *only* if the image file explicitly
// says there's premultiplied data (currently only happens in iPhone images,
// and only if iPhone convert-to-rgb processing is on).
//


#ifndef STBI_NO_STDIO
#include <stdio.h>
#endif // STBI_NO_STDIO

#define STBI_VERSION 1

enum
{
	STBI_default = 0, // only used for req_comp

	STBI_grey = 1,
	STBI_grey_alpha = 2,
	STBI_rgb = 3,
	STBI_rgb_alpha = 4
};

typedef unsigned char stbi_uc;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_IMAGE_STATIC
#define STBIDEF static
#else
#define STBIDEF extern
#endif

	//////////////////////////////////////////////////////////////////////////////
	//
	// PRIMARY API - works on images of any type
	//

	//
	// load image by filename, open file, or memory buffer
	//

	typedef struct
	{
		int(*read)  (void *user, char *data, int size);   // fill 'data' with 'size' bytes.  return number of bytes actually read
		void(*skip)  (void *user, int n);                 // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
		int(*eof)   (void *user);                       // returns nonzero if we are at end of file/data
	} stbi_io_callbacks;

	STBIDEF stbi_uc *stbi_load(char              const *filename, int *x, int *y, int *comp, int req_comp);
	STBIDEF stbi_uc *stbi_load_from_memory(stbi_uc           const *buffer, int len, int *x, int *y, int *comp, int req_comp);
	STBIDEF stbi_uc *stbi_load_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp);

#ifndef STBI_NO_STDIO
	STBIDEF stbi_uc *stbi_load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp);
	// for stbi_load_from_file, file pointer is left pointing immediately after image
#endif

#ifndef STBI_NO_LINEAR
	STBIDEF float *stbi_loadf(char const *filename, int *x, int *y, int *comp, int req_comp);
	STBIDEF float *stbi_loadf_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp);
	STBIDEF float *stbi_loadf_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp);

#ifndef STBI_NO_STDIO
	STBIDEF float *stbi_loadf_from_file(FILE *f, int *x, int *y, int *comp, int req_comp);
#endif
#endif

#ifndef STBI_NO_HDR
	STBIDEF void   stbi_hdr_to_ldr_gamma(float gamma);
	STBIDEF void   stbi_hdr_to_ldr_scale(float scale);
#endif // STBI_NO_HDR

#ifndef STBI_NO_LINEAR
	STBIDEF void   stbi_ldr_to_hdr_gamma(float gamma);
	STBIDEF void   stbi_ldr_to_hdr_scale(float scale);
#endif // STBI_NO_LINEAR

	// stbi_is_hdr is always defined, but always returns false if STBI_NO_HDR
	STBIDEF int    stbi_is_hdr_from_callbacks(stbi_io_callbacks const *clbk, void *user);
	STBIDEF int    stbi_is_hdr_from_memory(stbi_uc const *buffer, int len);
#ifndef STBI_NO_STDIO
	STBIDEF int      stbi_is_hdr(char const *filename);
	STBIDEF int      stbi_is_hdr_from_file(FILE *f);
#endif // STBI_NO_STDIO


	// get a VERY brief reason for failure
	// NOT THREADSAFE
	STBIDEF const char *stbi_failure_reason(void);

	// free the loaded image -- this is just free()
	STBIDEF void     stbi_image_free(void *retval_from_stbi_load);

	// get image dimensions & components without fully decoding
	STBIDEF int      stbi_info_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp);
	STBIDEF int      stbi_info_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp);

#ifndef STBI_NO_STDIO
	STBIDEF int      stbi_info(char const *filename, int *x, int *y, int *comp);
	STBIDEF int      stbi_info_from_file(FILE *f, int *x, int *y, int *comp);

#endif



	// for image formats that explicitly notate that they have premultiplied alpha,
	// we just return the colors as stored in the file. set this flag to force
	// unpremultiplication. results are undefined if the unpremultiply overflow.
	STBIDEF void stbi_set_unpremultiply_on_load(int flag_true_if_should_unpremultiply);

	// indicate whether we should process iphone images back to canonical format,
	// or just pass them through "as-is"
	STBIDEF void stbi_convert_iphone_png_to_rgb(int flag_true_if_should_convert);

	// flip the image vertically, so the first pixel in the output array is the bottom left
	STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);

	// ZLIB client - used by PNG, available for other purposes

	STBIDEF char *stbi_zlib_decode_malloc_guesssize(const char *buffer, int len, int initial_size, int *outlen);
	STBIDEF char *stbi_zlib_decode_malloc_guesssize_headerflag(const char *buffer, int len, int initial_size, int *outlen, int parse_header);
	STBIDEF char *stbi_zlib_decode_malloc(const char *buffer, int len, int *outlen);
	STBIDEF int   stbi_zlib_decode_buffer(char *obuffer, int olen, const char *ibuffer, int ilen);

	STBIDEF char *stbi_zlib_decode_noheader_malloc(const char *buffer, int len, int *outlen);
	STBIDEF int   stbi_zlib_decode_noheader_buffer(char *obuffer, int olen, const char *ibuffer, int ilen);


#ifdef __cplusplus
}
#endif

//
//
////   end header file   /////////////////////////////////////////////////////
#endif // STBI_INCLUDE_STB_IMAGE_H

#ifdef STB_IMAGE_IMPLEMENTATION

#if defined(STBI_ONLY_JPEG) || defined(STBI_ONLY_PNG) || defined(STBI_ONLY_BMP) \
  || defined(STBI_ONLY_TGA) || defined(STBI_ONLY_GIF) || defined(STBI_ONLY_PSD) \
  || defined(STBI_ONLY_HDR) || defined(STBI_ONLY_PIC) || defined(STBI_ONLY_PNM) \
  || defined(STBI_ONLY_ZLIB)
#ifndef STBI_ONLY_JPEG
#define STBI_NO_JPEG
#endif
#ifndef STBI_ONLY_PNG
#define STBI_NO_PNG
#endif
#ifndef STBI_ONLY_BMP
#define STBI_NO_BMP
#endif
#ifndef STBI_ONLY_PSD
#define STBI_NO_PSD
#endif
#ifndef STBI_ONLY_TGA
#define STBI_NO_TGA
#endif
#ifndef STBI_ONLY_GIF
#define STBI_NO_GIF
#endif
#ifndef STBI_ONLY_HDR
#define STBI_NO_HDR
#endif
#ifndef STBI_ONLY_PIC
#define STBI_NO_PIC
#endif
#ifndef STBI_ONLY_PNM
#define STBI_NO_PNM
#endif
#endif

#if defined(STBI_NO_PNG) && !defined(STBI_SUPPORT_ZLIB) && !defined(STBI_NO_ZLIB)
#define STBI_NO_ZLIB
#endif


#include <stdarg.h>
#include <stddef.h> // ptrdiff_t on osx
#include <stdlib.h>
#include <string.h>

#if !defined(STBI_NO_LINEAR) || !defined(STBI_NO_HDR)
#include <math.h>  // ldexp
#endif

#ifndef STBI_NO_STDIO
#include <stdio.h>
#endif

#ifndef STBI_ASSERT
#include <assert.h>
#define STBI_ASSERT(x) assert(x)
#endif


#ifndef _MSC_VER
#ifdef __cplusplus
#define stbi_inline inline
#else
#define stbi_inline
#endif
#else
#define stbi_inline __forceinline
#endif


#ifdef _MSC_VER
typedef unsigned short stbi__uint16;
typedef   signed short stbi__int16;
typedef unsigned int   stbi__uint32;
typedef   signed int   stbi__int32;
#else
#include <stdint.h>
typedef uint16_t stbi__uint16;
typedef int16_t  stbi__int16;
typedef uint32_t stbi__uint32;
typedef int32_t  stbi__int32;
#endif

// should produce compiler error if size is wrong
typedef unsigned char validate_uint32[sizeof(stbi__uint32) == 4 ? 1 : -1];

#ifdef _MSC_VER
#define STBI_NOTUSED(v)  (void)(v)
#else
#define STBI_NOTUSED(v)  (void)sizeof(v)
#endif

#ifdef _MSC_VER
#define STBI_HAS_LROTL
#endif

#ifdef STBI_HAS_LROTL
#define stbi_lrot(x,y)  _lrotl(x,y)
#else
#define stbi_lrot(x,y)  (((x) << (y)) | ((x) >> (32 - (y))))
#endif

#if defined(STBI_MALLOC) && defined(STBI_FREE) && (defined(STBI_REALLOC) || defined(STBI_REALLOC_SIZED))
// ok
#elif !defined(STBI_MALLOC) && !defined(STBI_FREE) && !defined(STBI_REALLOC) && !defined(STBI_REALLOC_SIZED)
// ok
#else
#error "Must define all or none of STBI_MALLOC, STBI_FREE, and STBI_REALLOC (or STBI_REALLOC_SIZED)."
#endif

#ifndef STBI_MALLOC
#define STBI_MALLOC(sz)           malloc(sz)
#define STBI_REALLOC(p,newsz)     realloc(p,newsz)
#define STBI_FREE(p)              free(p)
#endif

#ifndef STBI_REALLOC_SIZED
#define STBI_REALLOC_SIZED(p,oldsz,newsz) STBI_REALLOC(p,newsz)
#endif

// x86/x64 detection
#if defined(__x86_64__) || defined(_M_X64)
#define STBI__X64_TARGET
#elif defined(__i386) || defined(_M_IX86)
#define STBI__X86_TARGET
#endif

#if defined(__GNUC__) && (defined(STBI__X86_TARGET) || defined(STBI__X64_TARGET)) && !defined(__SSE2__) && !defined(STBI_NO_SIMD)
// NOTE: not clear do we actually need this for the 64-bit path?
// gcc doesn't support sse2 intrinsics unless you compile with -msse2,
// (but compiling with -msse2 allows the compiler to use SSE2 everywhere;
// this is just broken and gcc are jerks for not fixing it properly
// http://www.virtualdub.org/blog/pivot/entry.php?id=363 )
#define STBI_NO_SIMD
#endif

#if defined(__MINGW32__) && defined(STBI__X86_TARGET) && !defined(STBI_MINGW_ENABLE_SSE2) && !defined(STBI_NO_SIMD)
// Note that __MINGW32__ doesn't actually mean 32-bit, so we have to avoid STBI__X64_TARGET
//
// 32-bit MinGW wants ESP to be 16-byte aligned, but this is not in the
// Windows ABI and VC++ as well as Windows DLLs don't maintain that invariant.
// As a result, enabling SSE2 on 32-bit MinGW is dangerous when not
// simultaneously enabling "-mstackrealign".
//
// See https://github.com/nothings/stb/issues/81 for more information.
//
// So default to no SSE2 on 32-bit MinGW. If you've read this far and added
// -mstackrealign to your build settings, feel free to #define STBI_MINGW_ENABLE_SSE2.
#define STBI_NO_SIMD
#endif

#if !defined(STBI_NO_SIMD) && (defined(STBI__X86_TARGET) || defined(STBI__X64_TARGET))
#define STBI_SSE2
#include <emmintrin.h>

#ifdef _MSC_VER

#if _MSC_VER >= 1400  // not VC6
#include <intrin.h> // __cpuid
static int stbi__cpuid3(void)
{
	int info[4];
	__cpuid(info, 1);
	return info[3];
}
#else
static int stbi__cpuid3(void)
{
	int res;
	__asm {
		mov  eax, 1
			cpuid
			mov  res, edx
	}
	return res;
}
#endif

#define STBI_SIMD_ALIGN(type, name) __declspec(align(16)) type name

static int stbi__sse2_available()
{
	int info3 = stbi__cpuid3();
	return ((info3 >> 26) & 1) != 0;
}
#else // assume GCC-style if not VC++
#define STBI_SIMD_ALIGN(type, name) type name __attribute__((aligned(16)))

static int stbi__sse2_available()
{
#if defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 408 // GCC 4.8 or later
	// GCC 4.8+ has a nice way to do this
	return __builtin_cpu_supports("sse2");
#else
	// portable way to do this, preferably without using GCC inline ASM?
	// just bail for now.
	return 0;
#endif
}
#endif
#endif

// ARM NEON
#if defined(STBI_NO_SIMD) && defined(STBI_NEON)
#undef STBI_NEON
#endif

#ifdef STBI_NEON
#include <arm_neon.h>
// assume GCC or Clang on ARM targets
#define STBI_SIMD_ALIGN(type, name) type name __attribute__((aligned(16)))
#endif

#ifndef STBI_SIMD_ALIGN
#define STBI_SIMD_ALIGN(type, name) type name
#endif

///////////////////////////////////////////////
//
//  stbi__context struct and start_xxx functions

// stbi__context structure is our basic context used by all images, so it
// contains all the IO context, plus some basic image information
typedef struct
{
	stbi__uint32 img_x, img_y;
	int img_n, img_out_n;

	stbi_io_callbacks io;
	void *io_user_data;

	int read_from_callbacks;
	int buflen;
	stbi_uc buffer_start[128];

	stbi_uc *img_buffer, *img_buffer_end;
	stbi_uc *img_buffer_original, *img_buffer_original_end;
} stbi__context;


static void stbi__refill_buffer(stbi__context *s);

// initialize a memory-decode context
static void stbi__start_mem(stbi__context *s, stbi_uc const *buffer, int len)
{
	s->io.read = NULL;
	s->read_from_callbacks = 0;
	s->img_buffer = s->img_buffer_original = (stbi_uc *)buffer;
	s->img_buffer_end = s->img_buffer_original_end = (stbi_uc *)buffer + len;
}

// initialize a callback-based context
static void stbi__start_callbacks(stbi__context *s, stbi_io_callbacks *c, void *user)
{
	s->io = *c;
	s->io_user_data = user;
	s->buflen = sizeof(s->buffer_start);
	s->read_from_callbacks = 1;
	s->img_buffer_original = s->buffer_start;
	stbi__refill_buffer(s);
	s->img_buffer_original_end = s->img_buffer_end;
}

#ifndef STBI_NO_STDIO

static int stbi__stdio_read(void *user, char *data, int size)
{
	return (int)fread(data, 1, size, (FILE*)user);
}

static void stbi__stdio_skip(void *user, int n)
{
	fseek((FILE*)user, n, SEEK_CUR);
}

static int stbi__stdio_eof(void *user)
{
	return feof((FILE*)user);
}

static stbi_io_callbacks stbi__stdio_callbacks =
{
	stbi__stdio_read,
	stbi__stdio_skip,
	stbi__stdio_eof,
};

static void stbi__start_file(stbi__context *s, FILE *f)
{
	stbi__start_callbacks(s, &stbi__stdio_callbacks, (void *)f);
}

//static void stop_file(stbi__context *s) { }

#endif // !STBI_NO_STDIO

static void stbi__rewind(stbi__context *s)
{
	// conceptually rewind SHOULD rewind to the beginning of the stream,
	// but we just rewind to the beginning of the initial buffer, because
	// we only use it after doing 'test', which only ever looks at at most 92 bytes
	s->img_buffer = s->img_buffer_original;
	s->img_buffer_end = s->img_buffer_original_end;
}

#ifndef STBI_NO_JPEG
static int      stbi__jpeg_test(stbi__context *s);
static stbi_uc *stbi__jpeg_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__jpeg_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_PNG
static int      stbi__png_test(stbi__context *s);
static stbi_uc *stbi__png_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__png_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_BMP
static int      stbi__bmp_test(stbi__context *s);
static stbi_uc *stbi__bmp_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__bmp_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_TGA
static int      stbi__tga_test(stbi__context *s);
static stbi_uc *stbi__tga_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__tga_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_PSD
static int      stbi__psd_test(stbi__context *s);
static stbi_uc *stbi__psd_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__psd_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_HDR
static int      stbi__hdr_test(stbi__context *s);
static float   *stbi__hdr_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__hdr_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_PIC
static int      stbi__pic_test(stbi__context *s);
static stbi_uc *stbi__pic_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__pic_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_GIF
static int      stbi__gif_test(stbi__context *s);
static stbi_uc *stbi__gif_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__gif_info(stbi__context *s, int *x, int *y, int *comp);
#endif

#ifndef STBI_NO_PNM
static int      stbi__pnm_test(stbi__context *s);
static stbi_uc *stbi__pnm_load(stbi__context *s, int *x, int *y, int *comp, int req_comp);
static int      stbi__pnm_info(stbi__context *s, int *x, int *y, int *comp);
#endif

// this is not threadsafe
static const char *stbi__g_failure_reason;

STBIDEF const char *stbi_failure_reason(void)
{
	return stbi__g_failure_reason;
}

static int stbi__err(const char *str)
{
	stbi__g_failure_reason = str;
	return 0;
}

static void *stbi__malloc(size_t size)
{
	return STBI_MALLOC(size);
}

// stbi__err - error
// stbi__errpf - error returning pointer to float
// stbi__errpuc - error returning pointer to unsigned char

#ifdef STBI_NO_FAILURE_STRINGS
#define stbi__err(x,y)  0
#elif defined(STBI_FAILURE_USERMSG)
#define stbi__err(x,y)  stbi__err(y)
#else
#define stbi__err(x,y)  stbi__err(x)
#endif

#define stbi__errpf(x,y)   ((float *)(size_t) (stbi__err(x,y)?NULL:NULL))
#define stbi__errpuc(x,y)  ((unsigned char *)(size_t) (stbi__err(x,y)?NULL:NULL))

STBIDEF void stbi_image_free(void *retval_from_stbi_load)
{
	STBI_FREE(retval_from_stbi_load);
}

#ifndef STBI_NO_LINEAR
static float   *stbi__ldr_to_hdr(stbi_uc *data, int x, int y, int comp);
#endif

#ifndef STBI_NO_HDR
static stbi_uc *stbi__hdr_to_ldr(float   *data, int x, int y, int comp);
#endif

static int stbi__vertically_flip_on_load = 0;

STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip)
{
	stbi__vertically_flip_on_load = flag_true_if_should_flip;
}

static unsigned char *stbi__load_main(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
#ifndef STBI_NO_JPEG
	if (stbi__jpeg_test(s)) return stbi__jpeg_load(s, x, y, comp, req_comp);
#endif
#ifndef STBI_NO_PNG
	if (stbi__png_test(s))  return stbi__png_load(s, x, y, comp, req_comp);
#endif
#ifndef STBI_NO_BMP
	if (stbi__bmp_test(s))  return stbi__bmp_load(s, x, y, comp, req_comp);
#endif
#ifndef STBI_NO_GIF
	if (stbi__gif_test(s))  return stbi__gif_load(s, x, y, comp, req_comp);
#endif
#ifndef STBI_NO_PSD
	if (stbi__psd_test(s))  return stbi__psd_load(s, x, y, comp, req_comp);
#endif
#ifndef STBI_NO_PIC
	if (stbi__pic_test(s))  return stbi__pic_load(s, x, y, comp, req_comp);
#endif
#ifndef STBI_NO_PNM
	if (stbi__pnm_test(s))  return stbi__pnm_load(s, x, y, comp, req_comp);
#endif

#ifndef STBI_NO_HDR
	if (stbi__hdr_test(s)) {
		float *hdr = stbi__hdr_load(s, x, y, comp, req_comp);
		return stbi__hdr_to_ldr(hdr, *x, *y, req_comp ? req_comp : *comp);
	}
#endif

#ifndef STBI_NO_TGA
	// test tga last because it's a crappy test!
	if (stbi__tga_test(s))
		return stbi__tga_load(s, x, y, comp, req_comp);
#endif

	return stbi__errpuc("unknown image type", "Image not of any known type, or corrupt");
}

static unsigned char *stbi__load_flip(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	unsigned char *result = stbi__load_main(s, x, y, comp, req_comp);

	if (stbi__vertically_flip_on_load && result != NULL) {
		int w = *x, h = *y;
		int depth = req_comp ? req_comp : *comp;
		int row, col, z;
		stbi_uc temp;

		// @OPTIMIZE: use a bigger temp buffer and memcpy multiple pixels at once
		for (row = 0; row < (h >> 1); row++) {
			for (col = 0; col < w; col++) {
				for (z = 0; z < depth; z++) {
					temp = result[(row * w + col) * depth + z];
					result[(row * w + col) * depth + z] = result[((h - row - 1) * w + col) * depth + z];
					result[((h - row - 1) * w + col) * depth + z] = temp;
				}
			}
		}
	}

	return result;
}

#ifndef STBI_NO_HDR
static void stbi__float_postprocess(float *result, int *x, int *y, int *comp, int req_comp)
{
	if (stbi__vertically_flip_on_load && result != NULL) {
		int w = *x, h = *y;
		int depth = req_comp ? req_comp : *comp;
		int row, col, z;
		float temp;

		// @OPTIMIZE: use a bigger temp buffer and memcpy multiple pixels at once
		for (row = 0; row < (h >> 1); row++) {
			for (col = 0; col < w; col++) {
				for (z = 0; z < depth; z++) {
					temp = result[(row * w + col) * depth + z];
					result[(row * w + col) * depth + z] = result[((h - row - 1) * w + col) * depth + z];
					result[((h - row - 1) * w + col) * depth + z] = temp;
				}
			}
		}
	}
}
#endif

#ifndef STBI_NO_STDIO

static FILE *stbi__fopen(char const *filename, char const *mode)
{
	FILE *f;
#if defined(_MSC_VER) && _MSC_VER >= 1400
	if (0 != fopen_s(&f, filename, mode))
		f = 0;
#else
	f = fopen(filename, mode);
#endif
	return f;
}


STBIDEF stbi_uc *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp)
{
	FILE *f = stbi__fopen(filename, "rb");
	unsigned char *result;
	if (!f) return stbi__errpuc("can't fopen", "Unable to open file");
	result = stbi_load_from_file(f, x, y, comp, req_comp);
	fclose(f);
	return result;
}

STBIDEF stbi_uc *stbi_load_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
	unsigned char *result;
	stbi__context s;
	stbi__start_file(&s, f);
	result = stbi__load_flip(&s, x, y, comp, req_comp);
	if (result) {
		// need to 'unget' all the characters in the IO buffer
		fseek(f, -(int)(s.img_buffer_end - s.img_buffer), SEEK_CUR);
	}
	return result;
}
#endif //!STBI_NO_STDIO

STBIDEF stbi_uc *stbi_load_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp)
{
	stbi__context s;
	stbi__start_mem(&s, buffer, len);
	return stbi__load_flip(&s, x, y, comp, req_comp);
}

STBIDEF stbi_uc *stbi_load_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp)
{
	stbi__context s;
	stbi__start_callbacks(&s, (stbi_io_callbacks *)clbk, user);
	return stbi__load_flip(&s, x, y, comp, req_comp);
}

#ifndef STBI_NO_LINEAR
static float *stbi__loadf_main(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	unsigned char *data;
#ifndef STBI_NO_HDR
	if (stbi__hdr_test(s)) {
		float *hdr_data = stbi__hdr_load(s, x, y, comp, req_comp);
		if (hdr_data)
			stbi__float_postprocess(hdr_data, x, y, comp, req_comp);
		return hdr_data;
	}
#endif
	data = stbi__load_flip(s, x, y, comp, req_comp);
	if (data)
		return stbi__ldr_to_hdr(data, *x, *y, req_comp ? req_comp : *comp);
	return stbi__errpf("unknown image type", "Image not of any known type, or corrupt");
}

STBIDEF float *stbi_loadf_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp)
{
	stbi__context s;
	stbi__start_mem(&s, buffer, len);
	return stbi__loadf_main(&s, x, y, comp, req_comp);
}

STBIDEF float *stbi_loadf_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp, int req_comp)
{
	stbi__context s;
	stbi__start_callbacks(&s, (stbi_io_callbacks *)clbk, user);
	return stbi__loadf_main(&s, x, y, comp, req_comp);
}

#ifndef STBI_NO_STDIO
STBIDEF float *stbi_loadf(char const *filename, int *x, int *y, int *comp, int req_comp)
{
	float *result;
	FILE *f = stbi__fopen(filename, "rb");
	if (!f) return stbi__errpf("can't fopen", "Unable to open file");
	result = stbi_loadf_from_file(f, x, y, comp, req_comp);
	fclose(f);
	return result;
}

STBIDEF float *stbi_loadf_from_file(FILE *f, int *x, int *y, int *comp, int req_comp)
{
	stbi__context s;
	stbi__start_file(&s, f);
	return stbi__loadf_main(&s, x, y, comp, req_comp);
}
#endif // !STBI_NO_STDIO

#endif // !STBI_NO_LINEAR

// these is-hdr-or-not is defined independent of whether STBI_NO_LINEAR is
// defined, for API simplicity; if STBI_NO_LINEAR is defined, it always
// reports false!

STBIDEF int stbi_is_hdr_from_memory(stbi_uc const *buffer, int len)
{
#ifndef STBI_NO_HDR
	stbi__context s;
	stbi__start_mem(&s, buffer, len);
	return stbi__hdr_test(&s);
#else
	STBI_NOTUSED(buffer);
	STBI_NOTUSED(len);
	return 0;
#endif
}

#ifndef STBI_NO_STDIO
STBIDEF int      stbi_is_hdr(char const *filename)
{
	FILE *f = stbi__fopen(filename, "rb");
	int result = 0;
	if (f) {
		result = stbi_is_hdr_from_file(f);
		fclose(f);
	}
	return result;
}

STBIDEF int      stbi_is_hdr_from_file(FILE *f)
{
#ifndef STBI_NO_HDR
	stbi__context s;
	stbi__start_file(&s, f);
	return stbi__hdr_test(&s);
#else
	STBI_NOTUSED(f);
	return 0;
#endif
}
#endif // !STBI_NO_STDIO

STBIDEF int      stbi_is_hdr_from_callbacks(stbi_io_callbacks const *clbk, void *user)
{
#ifndef STBI_NO_HDR
	stbi__context s;
	stbi__start_callbacks(&s, (stbi_io_callbacks *)clbk, user);
	return stbi__hdr_test(&s);
#else
	STBI_NOTUSED(clbk);
	STBI_NOTUSED(user);
	return 0;
#endif
}

#ifndef STBI_NO_LINEAR
static float stbi__l2h_gamma = 2.2f, stbi__l2h_scale = 1.0f;

STBIDEF void   stbi_ldr_to_hdr_gamma(float gamma) { stbi__l2h_gamma = gamma; }
STBIDEF void   stbi_ldr_to_hdr_scale(float scale) { stbi__l2h_scale = scale; }
#endif

static float stbi__h2l_gamma_i = 1.0f / 2.2f, stbi__h2l_scale_i = 1.0f;

STBIDEF void   stbi_hdr_to_ldr_gamma(float gamma) { stbi__h2l_gamma_i = 1 / gamma; }
STBIDEF void   stbi_hdr_to_ldr_scale(float scale) { stbi__h2l_scale_i = 1 / scale; }


//////////////////////////////////////////////////////////////////////////////
//
// Common code used by all image loaders
//

enum
{
	STBI__SCAN_load = 0,
	STBI__SCAN_type,
	STBI__SCAN_header
};

static void stbi__refill_buffer(stbi__context *s)
{
	int n = (s->io.read)(s->io_user_data, (char*)s->buffer_start, s->buflen);
	if (n == 0) {
		// at end of file, treat same as if from memory, but need to handle case
		// where s->img_buffer isn't pointing to safe memory, e.g. 0-byte file
		s->read_from_callbacks = 0;
		s->img_buffer = s->buffer_start;
		s->img_buffer_end = s->buffer_start + 1;
		*s->img_buffer = 0;
	}
	else {
		s->img_buffer = s->buffer_start;
		s->img_buffer_end = s->buffer_start + n;
	}
}

stbi_inline static stbi_uc stbi__get8(stbi__context *s)
{
	if (s->img_buffer < s->img_buffer_end)
		return *s->img_buffer++;
	if (s->read_from_callbacks) {
		stbi__refill_buffer(s);
		return *s->img_buffer++;
	}
	return 0;
}

stbi_inline static int stbi__at_eof(stbi__context *s)
{
	if (s->io.read) {
		if (!(s->io.eof)(s->io_user_data)) return 0;
		// if feof() is true, check if buffer = end
		// special case: we've only got the special 0 character at the end
		if (s->read_from_callbacks == 0) return 1;
	}

	return s->img_buffer >= s->img_buffer_end;
}

static void stbi__skip(stbi__context *s, int n)
{
	if (n < 0) {
		s->img_buffer = s->img_buffer_end;
		return;
	}
	if (s->io.read) {
		int blen = (int)(s->img_buffer_end - s->img_buffer);
		if (blen < n) {
			s->img_buffer = s->img_buffer_end;
			(s->io.skip)(s->io_user_data, n - blen);
			return;
		}
	}
	s->img_buffer += n;
}

static int stbi__getn(stbi__context *s, stbi_uc *buffer, int n)
{
	if (s->io.read) {
		int blen = (int)(s->img_buffer_end - s->img_buffer);
		if (blen < n) {
			int res, count;

			memcpy(buffer, s->img_buffer, blen);

			count = (s->io.read)(s->io_user_data, (char*)buffer + blen, n - blen);
			res = (count == (n - blen));
			s->img_buffer = s->img_buffer_end;
			return res;
		}
	}

	if (s->img_buffer + n <= s->img_buffer_end) {
		memcpy(buffer, s->img_buffer, n);
		s->img_buffer += n;
		return 1;
	}
	else
		return 0;
}

static int stbi__get16be(stbi__context *s)
{
	int z = stbi__get8(s);
	return (z << 8) + stbi__get8(s);
}

static stbi__uint32 stbi__get32be(stbi__context *s)
{
	stbi__uint32 z = stbi__get16be(s);
	return (z << 16) + stbi__get16be(s);
}

#if defined(STBI_NO_BMP) && defined(STBI_NO_TGA) && defined(STBI_NO_GIF)
// nothing
#else
static int stbi__get16le(stbi__context *s)
{
	int z = stbi__get8(s);
	return z + (stbi__get8(s) << 8);
}
#endif

#ifndef STBI_NO_BMP
static stbi__uint32 stbi__get32le(stbi__context *s)
{
	stbi__uint32 z = stbi__get16le(s);
	return z + (stbi__get16le(s) << 16);
}
#endif

#define STBI__BYTECAST(x)  ((stbi_uc) ((x) & 255))  // truncate int to byte without warnings


//////////////////////////////////////////////////////////////////////////////
//
//  generic converter from built-in img_n to req_comp
//    individual types do this automatically as much as possible (e.g. jpeg
//    does all cases internally since it needs to colorspace convert anyway,
//    and it never has alpha, so very few cases ). png can automatically
//    interleave an alpha=255 channel, but falls back to this for other cases
//
//  assume data buffer is malloced, so malloc a new one and free that one
//  only failure mode is malloc failing

static stbi_uc stbi__compute_y(int r, int g, int b)
{
	return (stbi_uc)(((r * 77) + (g * 150) + (29 * b)) >> 8);
}

static unsigned char *stbi__convert_format(unsigned char *data, int img_n, int req_comp, unsigned int x, unsigned int y)
{
	int i, j;
	unsigned char *good;

	if (req_comp == img_n) return data;
	STBI_ASSERT(req_comp >= 1 && req_comp <= 4);

	good = (unsigned char *)stbi__malloc(req_comp * x * y);
	if (good == NULL) {
		STBI_FREE(data);
		return stbi__errpuc("outofmem", "Out of memory");
	}

	for (j = 0; j < (int)y; ++j) {
		unsigned char *src = data + j * x * img_n;
		unsigned char *dest = good + j * x * req_comp;

#define COMBO(a,b)  ((a)*8+(b))
#define CASE(a,b)   case COMBO(a,b): for (i=x-1; i >= 0; --i, src += a, dest += b)
		// convert source image with img_n components to one with req_comp components;
		// avoid switch per pixel, so use switch per scanline and massive macros
		switch (COMBO(img_n, req_comp)) {
			CASE(1, 2) dest[0] = src[0], dest[1] = 255; break;
			CASE(1, 3) dest[0] = dest[1] = dest[2] = src[0]; break;
			CASE(1, 4) dest[0] = dest[1] = dest[2] = src[0], dest[3] = 255; break;
			CASE(2, 1) dest[0] = src[0]; break;
			CASE(2, 3) dest[0] = dest[1] = dest[2] = src[0]; break;
			CASE(2, 4) dest[0] = dest[1] = dest[2] = src[0], dest[3] = src[1]; break;
			CASE(3, 4) dest[0] = src[0], dest[1] = src[1], dest[2] = src[2], dest[3] = 255; break;
			CASE(3, 1) dest[0] = stbi__compute_y(src[0], src[1], src[2]); break;
			CASE(3, 2) dest[0] = stbi__compute_y(src[0], src[1], src[2]), dest[1] = 255; break;
			CASE(4, 1) dest[0] = stbi__compute_y(src[0], src[1], src[2]); break;
			CASE(4, 2) dest[0] = stbi__compute_y(src[0], src[1], src[2]), dest[1] = src[3]; break;
			CASE(4, 3) dest[0] = src[0], dest[1] = src[1], dest[2] = src[2]; break;
		default: STBI_ASSERT(0);
		}
#undef CASE
	}

	STBI_FREE(data);
	return good;
}

#ifndef STBI_NO_LINEAR
static float   *stbi__ldr_to_hdr(stbi_uc *data, int x, int y, int comp)
{
	int i, k, n;
	float *output = (float *)stbi__malloc(x * y * comp * sizeof(float));
	if (output == NULL) { STBI_FREE(data); return stbi__errpf("outofmem", "Out of memory"); }
	// compute number of non-alpha components
	if (comp & 1) n = comp; else n = comp - 1;
	for (i = 0; i < x*y; ++i) {
		for (k = 0; k < n; ++k) {
			output[i*comp + k] = (float)(pow(data[i*comp + k] / 255.0f, stbi__l2h_gamma) * stbi__l2h_scale);
		}
		if (k < comp) output[i*comp + k] = data[i*comp + k] / 255.0f;
	}
	STBI_FREE(data);
	return output;
}
#endif

#ifndef STBI_NO_HDR
#define stbi__float2int(x)   ((int) (x))
static stbi_uc *stbi__hdr_to_ldr(float   *data, int x, int y, int comp)
{
	int i, k, n;
	stbi_uc *output = (stbi_uc *)stbi__malloc(x * y * comp);
	if (output == NULL) { STBI_FREE(data); return stbi__errpuc("outofmem", "Out of memory"); }
	// compute number of non-alpha components
	if (comp & 1) n = comp; else n = comp - 1;
	for (i = 0; i < x*y; ++i) {
		for (k = 0; k < n; ++k) {
			float z = (float)pow(data[i*comp + k] * stbi__h2l_scale_i, stbi__h2l_gamma_i) * 255 + 0.5f;
			if (z < 0) z = 0;
			if (z > 255) z = 255;
			output[i*comp + k] = (stbi_uc)stbi__float2int(z);
		}
		if (k < comp) {
			float z = data[i*comp + k] * 255 + 0.5f;
			if (z < 0) z = 0;
			if (z > 255) z = 255;
			output[i*comp + k] = (stbi_uc)stbi__float2int(z);
		}
	}
	STBI_FREE(data);
	return output;
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  "baseline" JPEG/JFIF decoder
//
//    simple implementation
//      - doesn't support delayed output of y-dimension
//      - simple interface (only one output format: 8-bit interleaved RGB)
//      - doesn't try to recover corrupt jpegs
//      - doesn't allow partial loading, loading multiple at once
//      - still fast on x86 (copying globals into locals doesn't help x86)
//      - allocates lots of intermediate memory (full size of all components)
//        - non-interleaved case requires this anyway
//        - allows good upsampling (see next)
//    high-quality
//      - upsampled channels are bilinearly interpolated, even across blocks
//      - quality integer IDCT derived from IJG's 'slow'
//    performance
//      - fast huffman; reasonable integer IDCT
//      - some SIMD kernels for common paths on targets with SSE2/NEON
//      - uses a lot of intermediate memory, could cache poorly

#ifndef STBI_NO_JPEG

// huffman decoding acceleration
#define FAST_BITS   9  // larger handles more cases; smaller stomps less cache

typedef struct
{
	stbi_uc  fast[1 << FAST_BITS];
	// weirdly, repacking this into AoS is a 10% speed loss, instead of a win
	stbi__uint16 code[256];
	stbi_uc  values[256];
	stbi_uc  size[257];
	unsigned int maxcode[18];
	int    delta[17];   // old 'firstsymbol' - old 'firstcode'
} stbi__huffman;

typedef struct
{
	stbi__context *s;
	stbi__huffman huff_dc[4];
	stbi__huffman huff_ac[4];
	stbi_uc dequant[4][64];
	stbi__int16 fast_ac[4][1 << FAST_BITS];

	// sizes for components, interleaved MCUs
	int img_h_max, img_v_max;
	int img_mcu_x, img_mcu_y;
	int img_mcu_w, img_mcu_h;

	// definition of jpeg image component
	struct
	{
		int id;
		int h, v;
		int tq;
		int hd, ha;
		int dc_pred;

		int x, y, w2, h2;
		stbi_uc *data;
		void *raw_data, *raw_coeff;
		stbi_uc *linebuf;
		short   *coeff;   // progressive only
		int      coeff_w, coeff_h; // number of 8x8 coefficient blocks
	} img_comp[4];

	stbi__uint32   code_buffer; // jpeg entropy-coded buffer
	int            code_bits;   // number of valid bits
	unsigned char  marker;      // marker seen while filling entropy buffer
	int            nomore;      // flag if we saw a marker so must stop

	int            progressive;
	int            spec_start;
	int            spec_end;
	int            succ_high;
	int            succ_low;
	int            eob_run;
	int            rgb;

	int scan_n, order[4];
	int restart_interval, todo;

	// kernels
	void(*idct_block_kernel)(stbi_uc *out, int out_stride, short data[64]);
	void(*YCbCr_to_RGB_kernel)(stbi_uc *out, const stbi_uc *y, const stbi_uc *pcb, const stbi_uc *pcr, int count, int step);
	stbi_uc *(*resample_row_hv_2_kernel)(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs);
} stbi__jpeg;

static int stbi__build_huffman(stbi__huffman *h, int *count)
{
	int i, j, k = 0, code;
	// build size list for each symbol (from JPEG spec)
	for (i = 0; i < 16; ++i)
		for (j = 0; j < count[i]; ++j)
			h->size[k++] = (stbi_uc)(i + 1);
	h->size[k] = 0;

	// compute actual symbols (from jpeg spec)
	code = 0;
	k = 0;
	for (j = 1; j <= 16; ++j) {
		// compute delta to add to code to compute symbol id
		h->delta[j] = k - code;
		if (h->size[k] == j) {
			while (h->size[k] == j)
				h->code[k++] = (stbi__uint16)(code++);
			if (code - 1 >= (1 << j)) return stbi__err("bad code lengths", "Corrupt JPEG");
		}
		// compute largest code + 1 for this size, preshifted as needed later
		h->maxcode[j] = code << (16 - j);
		code <<= 1;
	}
	h->maxcode[j] = 0xffffffff;

	// build non-spec acceleration table; 255 is flag for not-accelerated
	memset(h->fast, 255, 1 << FAST_BITS);
	for (i = 0; i < k; ++i) {
		int s = h->size[i];
		if (s <= FAST_BITS) {
			int c = h->code[i] << (FAST_BITS - s);
			int m = 1 << (FAST_BITS - s);
			for (j = 0; j < m; ++j) {
				h->fast[c + j] = (stbi_uc)i;
			}
		}
	}
	return 1;
}

// build a table that decodes both magnitude and value of small ACs in
// one go.
static void stbi__build_fast_ac(stbi__int16 *fast_ac, stbi__huffman *h)
{
	int i;
	for (i = 0; i < (1 << FAST_BITS); ++i) {
		stbi_uc fast = h->fast[i];
		fast_ac[i] = 0;
		if (fast < 255) {
			int rs = h->values[fast];
			int run = (rs >> 4) & 15;
			int magbits = rs & 15;
			int len = h->size[fast];

			if (magbits && len + magbits <= FAST_BITS) {
				// magnitude code followed by receive_extend code
				int k = ((i << len) & ((1 << FAST_BITS) - 1)) >> (FAST_BITS - magbits);
				int m = 1 << (magbits - 1);
				if (k < m) k += (-1 << magbits) + 1;
				// if the result is small enough, we can fit it in fast_ac table
				if (k >= -128 && k <= 127)
					fast_ac[i] = (stbi__int16)((k << 8) + (run << 4) + (len + magbits));
			}
		}
	}
}

static void stbi__grow_buffer_unsafe(stbi__jpeg *j)
{
	do {
		int b = j->nomore ? 0 : stbi__get8(j->s);
		if (b == 0xff) {
			int c = stbi__get8(j->s);
			if (c != 0) {
				j->marker = (unsigned char)c;
				j->nomore = 1;
				return;
			}
		}
		j->code_buffer |= b << (24 - j->code_bits);
		j->code_bits += 8;
	} while (j->code_bits <= 24);
}

// (1 << n) - 1
static stbi__uint32 stbi__bmask[17] = { 0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535 };

// decode a jpeg huffman value from the bitstream
stbi_inline static int stbi__jpeg_huff_decode(stbi__jpeg *j, stbi__huffman *h)
{
	unsigned int temp;
	int c, k;

	if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);

	// look at the top FAST_BITS and determine what symbol ID it is,
	// if the code is <= FAST_BITS
	c = (j->code_buffer >> (32 - FAST_BITS)) & ((1 << FAST_BITS) - 1);
	k = h->fast[c];
	if (k < 255) {
		int s = h->size[k];
		if (s > j->code_bits)
			return -1;
		j->code_buffer <<= s;
		j->code_bits -= s;
		return h->values[k];
	}

	// naive test is to shift the code_buffer down so k bits are
	// valid, then test against maxcode. To speed this up, we've
	// preshifted maxcode left so that it has (16-k) 0s at the
	// end; in other words, regardless of the number of bits, it
	// wants to be compared against something shifted to have 16;
	// that way we don't need to shift inside the loop.
	temp = j->code_buffer >> 16;
	for (k = FAST_BITS + 1;; ++k)
		if (temp < h->maxcode[k])
			break;
	if (k == 17) {
		// error! code not found
		j->code_bits -= 16;
		return -1;
	}

	if (k > j->code_bits)
		return -1;

	// convert the huffman code to the symbol id
	c = ((j->code_buffer >> (32 - k)) & stbi__bmask[k]) + h->delta[k];
	STBI_ASSERT((((j->code_buffer) >> (32 - h->size[c])) & stbi__bmask[h->size[c]]) == h->code[c]);

	// convert the id to a symbol
	j->code_bits -= k;
	j->code_buffer <<= k;
	return h->values[c];
}

// bias[n] = (-1<<n) + 1
static int const stbi__jbias[16] = { 0, -1, -3, -7, -15, -31, -63, -127, -255, -511, -1023, -2047, -4095, -8191, -16383, -32767 };

// combined JPEG 'receive' and JPEG 'extend', since baseline
// always extends everything it receives.
stbi_inline static int stbi__extend_receive(stbi__jpeg *j, int n)
{
	unsigned int k;
	int sgn;
	if (j->code_bits < n) stbi__grow_buffer_unsafe(j);

	sgn = (stbi__int32)j->code_buffer >> 31; // sign bit is always in MSB
	k = stbi_lrot(j->code_buffer, n);
	STBI_ASSERT(n >= 0 && n < (int)(sizeof(stbi__bmask) / sizeof(*stbi__bmask)));
	j->code_buffer = k & ~stbi__bmask[n];
	k &= stbi__bmask[n];
	j->code_bits -= n;
	return k + (stbi__jbias[n] & ~sgn);
}

// get some unsigned bits
stbi_inline static int stbi__jpeg_get_bits(stbi__jpeg *j, int n)
{
	unsigned int k;
	if (j->code_bits < n) stbi__grow_buffer_unsafe(j);
	k = stbi_lrot(j->code_buffer, n);
	j->code_buffer = k & ~stbi__bmask[n];
	k &= stbi__bmask[n];
	j->code_bits -= n;
	return k;
}

stbi_inline static int stbi__jpeg_get_bit(stbi__jpeg *j)
{
	unsigned int k;
	if (j->code_bits < 1) stbi__grow_buffer_unsafe(j);
	k = j->code_buffer;
	j->code_buffer <<= 1;
	--j->code_bits;
	return k & 0x80000000;
}

// given a value that's at position X in the zigzag stream,
// where does it appear in the 8x8 matrix coded as row-major?
static stbi_uc stbi__jpeg_dezigzag[64 + 15] =
{
	0, 1, 8, 16, 9, 2, 3, 10,
	17, 24, 32, 25, 18, 11, 4, 5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13, 6, 7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63,
	// let corrupt input sample past end
	63, 63, 63, 63, 63, 63, 63, 63,
	63, 63, 63, 63, 63, 63, 63
};

// decode one 64-entry block--
static int stbi__jpeg_decode_block(stbi__jpeg *j, short data[64], stbi__huffman *hdc, stbi__huffman *hac, stbi__int16 *fac, int b, stbi_uc *dequant)
{
	int diff, dc, k;
	int t;

	if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);
	t = stbi__jpeg_huff_decode(j, hdc);
	if (t < 0) return stbi__err("bad huffman code", "Corrupt JPEG");

	// 0 all the ac values now so we can do it 32-bits at a time
	memset(data, 0, 64 * sizeof(data[0]));

	diff = t ? stbi__extend_receive(j, t) : 0;
	dc = j->img_comp[b].dc_pred + diff;
	j->img_comp[b].dc_pred = dc;
	data[0] = (short)(dc * dequant[0]);

	// decode AC components, see JPEG spec
	k = 1;
	do {
		unsigned int zig;
		int c, r, s;
		if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);
		c = (j->code_buffer >> (32 - FAST_BITS)) & ((1 << FAST_BITS) - 1);
		r = fac[c];
		if (r) { // fast-AC path
			k += (r >> 4) & 15; // run
			s = r & 15; // combined length
			j->code_buffer <<= s;
			j->code_bits -= s;
			// decode into unzigzag'd location
			zig = stbi__jpeg_dezigzag[k++];
			data[zig] = (short)((r >> 8) * dequant[zig]);
		}
		else {
			int rs = stbi__jpeg_huff_decode(j, hac);
			if (rs < 0) return stbi__err("bad huffman code", "Corrupt JPEG");
			s = rs & 15;
			r = rs >> 4;
			if (s == 0) {
				if (rs != 0xf0) break; // end block
				k += 16;
			}
			else {
				k += r;
				// decode into unzigzag'd location
				zig = stbi__jpeg_dezigzag[k++];
				data[zig] = (short)(stbi__extend_receive(j, s) * dequant[zig]);
			}
		}
	} while (k < 64);
	return 1;
}

static int stbi__jpeg_decode_block_prog_dc(stbi__jpeg *j, short data[64], stbi__huffman *hdc, int b)
{
	int diff, dc;
	int t;
	if (j->spec_end != 0) return stbi__err("can't merge dc and ac", "Corrupt JPEG");

	if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);

	if (j->succ_high == 0) {
		// first scan for DC coefficient, must be first
		memset(data, 0, 64 * sizeof(data[0])); // 0 all the ac values now
		t = stbi__jpeg_huff_decode(j, hdc);
		diff = t ? stbi__extend_receive(j, t) : 0;

		dc = j->img_comp[b].dc_pred + diff;
		j->img_comp[b].dc_pred = dc;
		data[0] = (short)(dc << j->succ_low);
	}
	else {
		// refinement scan for DC coefficient
		if (stbi__jpeg_get_bit(j))
			data[0] += (short)(1 << j->succ_low);
	}
	return 1;
}

// @OPTIMIZE: store non-zigzagged during the decode passes,
// and only de-zigzag when dequantizing
static int stbi__jpeg_decode_block_prog_ac(stbi__jpeg *j, short data[64], stbi__huffman *hac, stbi__int16 *fac)
{
	int k;
	if (j->spec_start == 0) return stbi__err("can't merge dc and ac", "Corrupt JPEG");

	if (j->succ_high == 0) {
		int shift = j->succ_low;

		if (j->eob_run) {
			--j->eob_run;
			return 1;
		}

		k = j->spec_start;
		do {
			unsigned int zig;
			int c, r, s;
			if (j->code_bits < 16) stbi__grow_buffer_unsafe(j);
			c = (j->code_buffer >> (32 - FAST_BITS)) & ((1 << FAST_BITS) - 1);
			r = fac[c];
			if (r) { // fast-AC path
				k += (r >> 4) & 15; // run
				s = r & 15; // combined length
				j->code_buffer <<= s;
				j->code_bits -= s;
				zig = stbi__jpeg_dezigzag[k++];
				data[zig] = (short)((r >> 8) << shift);
			}
			else {
				int rs = stbi__jpeg_huff_decode(j, hac);
				if (rs < 0) return stbi__err("bad huffman code", "Corrupt JPEG");
				s = rs & 15;
				r = rs >> 4;
				if (s == 0) {
					if (r < 15) {
						j->eob_run = (1 << r);
						if (r)
							j->eob_run += stbi__jpeg_get_bits(j, r);
						--j->eob_run;
						break;
					}
					k += 16;
				}
				else {
					k += r;
					zig = stbi__jpeg_dezigzag[k++];
					data[zig] = (short)(stbi__extend_receive(j, s) << shift);
				}
			}
		} while (k <= j->spec_end);
	}
	else {
		// refinement scan for these AC coefficients

		short bit = (short)(1 << j->succ_low);

		if (j->eob_run) {
			--j->eob_run;
			for (k = j->spec_start; k <= j->spec_end; ++k) {
				short *p = &data[stbi__jpeg_dezigzag[k]];
				if (*p != 0)
					if (stbi__jpeg_get_bit(j))
						if ((*p & bit) == 0) {
							if (*p > 0)
								*p += bit;
							else
								*p -= bit;
						}
			}
		}
		else {
			k = j->spec_start;
			do {
				int r, s;
				int rs = stbi__jpeg_huff_decode(j, hac); // @OPTIMIZE see if we can use the fast path here, advance-by-r is so slow, eh
				if (rs < 0) return stbi__err("bad huffman code", "Corrupt JPEG");
				s = rs & 15;
				r = rs >> 4;
				if (s == 0) {
					if (r < 15) {
						j->eob_run = (1 << r) - 1;
						if (r)
							j->eob_run += stbi__jpeg_get_bits(j, r);
						r = 64; // force end of block
					}
					else {
						// r=15 s=0 should write 16 0s, so we just do
						// a run of 15 0s and then write s (which is 0),
						// so we don't have to do anything special here
					}
				}
				else {
					if (s != 1) return stbi__err("bad huffman code", "Corrupt JPEG");
					// sign bit
					if (stbi__jpeg_get_bit(j))
						s = bit;
					else
						s = -bit;
				}

				// advance by r
				while (k <= j->spec_end) {
					short *p = &data[stbi__jpeg_dezigzag[k++]];
					if (*p != 0) {
						if (stbi__jpeg_get_bit(j))
							if ((*p & bit) == 0) {
								if (*p > 0)
									*p += bit;
								else
									*p -= bit;
							}
					}
					else {
						if (r == 0) {
							*p = (short)s;
							break;
						}
						--r;
					}
				}
			} while (k <= j->spec_end);
		}
	}
	return 1;
}

// take a -128..127 value and stbi__clamp it and convert to 0..255
stbi_inline static stbi_uc stbi__clamp(int x)
{
	// trick to use a single test to catch both cases
	if ((unsigned int)x > 255) {
		if (x < 0) return 0;
		if (x > 255) return 255;
	}
	return (stbi_uc)x;
}

#define stbi__f2f(x)  ((int) (((x) * 4096 + 0.5)))
#define stbi__fsh(x)  ((x) << 12)

// derived from jidctint -- DCT_ISLOW
#define STBI__IDCT_1D(s0,s1,s2,s3,s4,s5,s6,s7) \
   int t0,t1,t2,t3,p1,p2,p3,p4,p5,x0,x1,x2,x3; \
   p2 = s2;                                    \
   p3 = s6;                                    \
   p1 = (p2+p3) * stbi__f2f(0.5411961f);       \
   t2 = p1 + p3*stbi__f2f(-1.847759065f);      \
   t3 = p1 + p2*stbi__f2f( 0.765366865f);      \
   p2 = s0;                                    \
   p3 = s4;                                    \
   t0 = stbi__fsh(p2+p3);                      \
   t1 = stbi__fsh(p2-p3);                      \
   x0 = t0+t3;                                 \
   x3 = t0-t3;                                 \
   x1 = t1+t2;                                 \
   x2 = t1-t2;                                 \
   t0 = s7;                                    \
   t1 = s5;                                    \
   t2 = s3;                                    \
   t3 = s1;                                    \
   p3 = t0+t2;                                 \
   p4 = t1+t3;                                 \
   p1 = t0+t3;                                 \
   p2 = t1+t2;                                 \
   p5 = (p3+p4)*stbi__f2f( 1.175875602f);      \
   t0 = t0*stbi__f2f( 0.298631336f);           \
   t1 = t1*stbi__f2f( 2.053119869f);           \
   t2 = t2*stbi__f2f( 3.072711026f);           \
   t3 = t3*stbi__f2f( 1.501321110f);           \
   p1 = p5 + p1*stbi__f2f(-0.899976223f);      \
   p2 = p5 + p2*stbi__f2f(-2.562915447f);      \
   p3 = p3*stbi__f2f(-1.961570560f);           \
   p4 = p4*stbi__f2f(-0.390180644f);           \
   t3 += p1+p4;                                \
   t2 += p2+p3;                                \
   t1 += p2+p4;                                \
   t0 += p1+p3;

static void stbi__idct_block(stbi_uc *out, int out_stride, short data[64])
{
	int i, val[64], *v = val;
	stbi_uc *o;
	short *d = data;

	// columns
	for (i = 0; i < 8; ++i, ++d, ++v) {
		// if all zeroes, shortcut -- this avoids dequantizing 0s and IDCTing
		if (d[8] == 0 && d[16] == 0 && d[24] == 0 && d[32] == 0
			&& d[40] == 0 && d[48] == 0 && d[56] == 0) {
			//    no shortcut                 0     seconds
			//    (1|2|3|4|5|6|7)==0          0     seconds
			//    all separate               -0.047 seconds
			//    1 && 2|3 && 4|5 && 6|7:    -0.047 seconds
			int dcterm = d[0] << 2;
			v[0] = v[8] = v[16] = v[24] = v[32] = v[40] = v[48] = v[56] = dcterm;
		}
		else {
			STBI__IDCT_1D(d[0], d[8], d[16], d[24], d[32], d[40], d[48], d[56])
				// constants scaled things up by 1<<12; let's bring them back
				// down, but keep 2 extra bits of precision
				x0 += 512; x1 += 512; x2 += 512; x3 += 512;
			v[0] = (x0 + t3) >> 10;
			v[56] = (x0 - t3) >> 10;
			v[8] = (x1 + t2) >> 10;
			v[48] = (x1 - t2) >> 10;
			v[16] = (x2 + t1) >> 10;
			v[40] = (x2 - t1) >> 10;
			v[24] = (x3 + t0) >> 10;
			v[32] = (x3 - t0) >> 10;
		}
	}

	for (i = 0, v = val, o = out; i < 8; ++i, v += 8, o += out_stride) {
		// no fast case since the first 1D IDCT spread components out
		STBI__IDCT_1D(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7])
			// constants scaled things up by 1<<12, plus we had 1<<2 from first
			// loop, plus horizontal and vertical each scale by sqrt(8) so together
			// we've got an extra 1<<3, so 1<<17 total we need to remove.
			// so we want to round that, which means adding 0.5 * 1<<17,
			// aka 65536. Also, we'll end up with -128 to 127 that we want
			// to encode as 0..255 by adding 128, so we'll add that before the shift
			x0 += 65536 + (128 << 17);
		x1 += 65536 + (128 << 17);
		x2 += 65536 + (128 << 17);
		x3 += 65536 + (128 << 17);
		// tried computing the shifts into temps, or'ing the temps to see
		// if any were out of range, but that was slower
		o[0] = stbi__clamp((x0 + t3) >> 17);
		o[7] = stbi__clamp((x0 - t3) >> 17);
		o[1] = stbi__clamp((x1 + t2) >> 17);
		o[6] = stbi__clamp((x1 - t2) >> 17);
		o[2] = stbi__clamp((x2 + t1) >> 17);
		o[5] = stbi__clamp((x2 - t1) >> 17);
		o[3] = stbi__clamp((x3 + t0) >> 17);
		o[4] = stbi__clamp((x3 - t0) >> 17);
	}
}

#ifdef STBI_SSE2
// sse2 integer IDCT. not the fastest possible implementation but it
// produces bit-identical results to the generic C version so it's
// fully "transparent".
static void stbi__idct_simd(stbi_uc *out, int out_stride, short data[64])
{
	// This is constructed to match our regular (generic) integer IDCT exactly.
	__m128i row0, row1, row2, row3, row4, row5, row6, row7;
	__m128i tmp;

	// dot product constant: even elems=x, odd elems=y
#define dct_const(x,y)  _mm_setr_epi16((x),(y),(x),(y),(x),(y),(x),(y))

	// out(0) = c0[even]*x + c0[odd]*y   (c0, x, y 16-bit, out 32-bit)
	// out(1) = c1[even]*x + c1[odd]*y
#define dct_rot(out0,out1, x,y,c0,c1) \
      __m128i c0##lo = _mm_unpacklo_epi16((x),(y)); \
      __m128i c0##hi = _mm_unpackhi_epi16((x),(y)); \
      __m128i out0##_l = _mm_madd_epi16(c0##lo, c0); \
      __m128i out0##_h = _mm_madd_epi16(c0##hi, c0); \
      __m128i out1##_l = _mm_madd_epi16(c0##lo, c1); \
      __m128i out1##_h = _mm_madd_epi16(c0##hi, c1)

	// out = in << 12  (in 16-bit, out 32-bit)
#define dct_widen(out, in) \
      __m128i out##_l = _mm_srai_epi32(_mm_unpacklo_epi16(_mm_setzero_si128(), (in)), 4); \
      __m128i out##_h = _mm_srai_epi32(_mm_unpackhi_epi16(_mm_setzero_si128(), (in)), 4)

	// wide add
#define dct_wadd(out, a, b) \
      __m128i out##_l = _mm_add_epi32(a##_l, b##_l); \
      __m128i out##_h = _mm_add_epi32(a##_h, b##_h)

	// wide sub
#define dct_wsub(out, a, b) \
      __m128i out##_l = _mm_sub_epi32(a##_l, b##_l); \
      __m128i out##_h = _mm_sub_epi32(a##_h, b##_h)

	// butterfly a/b, add bias, then shift by "s" and pack
#define dct_bfly32o(out0, out1, a,b,bias,s) \
	      { \
         __m128i abiased_l = _mm_add_epi32(a##_l, bias); \
         __m128i abiased_h = _mm_add_epi32(a##_h, bias); \
         dct_wadd(sum, abiased, b); \
         dct_wsub(dif, abiased, b); \
         out0 = _mm_packs_epi32(_mm_srai_epi32(sum_l, s), _mm_srai_epi32(sum_h, s)); \
         out1 = _mm_packs_epi32(_mm_srai_epi32(dif_l, s), _mm_srai_epi32(dif_h, s)); \
	      }

	// 8-bit interleave step (for transposes)
#define dct_interleave8(a, b) \
      tmp = a; \
      a = _mm_unpacklo_epi8(a, b); \
      b = _mm_unpackhi_epi8(tmp, b)

	// 16-bit interleave step (for transposes)
#define dct_interleave16(a, b) \
      tmp = a; \
      a = _mm_unpacklo_epi16(a, b); \
      b = _mm_unpackhi_epi16(tmp, b)

#define dct_pass(bias,shift) \
	      { \
         /* even part */ \
         dct_rot(t2e,t3e, row2,row6, rot0_0,rot0_1); \
         __m128i sum04 = _mm_add_epi16(row0, row4); \
         __m128i dif04 = _mm_sub_epi16(row0, row4); \
         dct_widen(t0e, sum04); \
         dct_widen(t1e, dif04); \
         dct_wadd(x0, t0e, t3e); \
         dct_wsub(x3, t0e, t3e); \
         dct_wadd(x1, t1e, t2e); \
         dct_wsub(x2, t1e, t2e); \
         /* odd part */ \
         dct_rot(y0o,y2o, row7,row3, rot2_0,rot2_1); \
         dct_rot(y1o,y3o, row5,row1, rot3_0,rot3_1); \
         __m128i sum17 = _mm_add_epi16(row1, row7); \
         __m128i sum35 = _mm_add_epi16(row3, row5); \
         dct_rot(y4o,y5o, sum17,sum35, rot1_0,rot1_1); \
         dct_wadd(x4, y0o, y4o); \
         dct_wadd(x5, y1o, y5o); \
         dct_wadd(x6, y2o, y5o); \
         dct_wadd(x7, y3o, y4o); \
         dct_bfly32o(row0,row7, x0,x7,bias,shift); \
         dct_bfly32o(row1,row6, x1,x6,bias,shift); \
         dct_bfly32o(row2,row5, x2,x5,bias,shift); \
         dct_bfly32o(row3,row4, x3,x4,bias,shift); \
	      }

	__m128i rot0_0 = dct_const(stbi__f2f(0.5411961f), stbi__f2f(0.5411961f) + stbi__f2f(-1.847759065f));
	__m128i rot0_1 = dct_const(stbi__f2f(0.5411961f) + stbi__f2f(0.765366865f), stbi__f2f(0.5411961f));
	__m128i rot1_0 = dct_const(stbi__f2f(1.175875602f) + stbi__f2f(-0.899976223f), stbi__f2f(1.175875602f));
	__m128i rot1_1 = dct_const(stbi__f2f(1.175875602f), stbi__f2f(1.175875602f) + stbi__f2f(-2.562915447f));
	__m128i rot2_0 = dct_const(stbi__f2f(-1.961570560f) + stbi__f2f(0.298631336f), stbi__f2f(-1.961570560f));
	__m128i rot2_1 = dct_const(stbi__f2f(-1.961570560f), stbi__f2f(-1.961570560f) + stbi__f2f(3.072711026f));
	__m128i rot3_0 = dct_const(stbi__f2f(-0.390180644f) + stbi__f2f(2.053119869f), stbi__f2f(-0.390180644f));
	__m128i rot3_1 = dct_const(stbi__f2f(-0.390180644f), stbi__f2f(-0.390180644f) + stbi__f2f(1.501321110f));

	// rounding biases in column/row passes, see stbi__idct_block for explanation.
	__m128i bias_0 = _mm_set1_epi32(512);
	__m128i bias_1 = _mm_set1_epi32(65536 + (128 << 17));

	// load
	row0 = _mm_load_si128((const __m128i *) (data + 0 * 8));
	row1 = _mm_load_si128((const __m128i *) (data + 1 * 8));
	row2 = _mm_load_si128((const __m128i *) (data + 2 * 8));
	row3 = _mm_load_si128((const __m128i *) (data + 3 * 8));
	row4 = _mm_load_si128((const __m128i *) (data + 4 * 8));
	row5 = _mm_load_si128((const __m128i *) (data + 5 * 8));
	row6 = _mm_load_si128((const __m128i *) (data + 6 * 8));
	row7 = _mm_load_si128((const __m128i *) (data + 7 * 8));

	// column pass
	dct_pass(bias_0, 10);

	{
		// 16bit 8x8 transpose pass 1
		dct_interleave16(row0, row4);
		dct_interleave16(row1, row5);
		dct_interleave16(row2, row6);
		dct_interleave16(row3, row7);

		// transpose pass 2
		dct_interleave16(row0, row2);
		dct_interleave16(row1, row3);
		dct_interleave16(row4, row6);
		dct_interleave16(row5, row7);

		// transpose pass 3
		dct_interleave16(row0, row1);
		dct_interleave16(row2, row3);
		dct_interleave16(row4, row5);
		dct_interleave16(row6, row7);
	}

	// row pass
	dct_pass(bias_1, 17);

	{
		// pack
		__m128i p0 = _mm_packus_epi16(row0, row1); // a0a1a2a3...a7b0b1b2b3...b7
		__m128i p1 = _mm_packus_epi16(row2, row3);
		__m128i p2 = _mm_packus_epi16(row4, row5);
		__m128i p3 = _mm_packus_epi16(row6, row7);

		// 8bit 8x8 transpose pass 1
		dct_interleave8(p0, p2); // a0e0a1e1...
		dct_interleave8(p1, p3); // c0g0c1g1...

		// transpose pass 2
		dct_interleave8(p0, p1); // a0c0e0g0...
		dct_interleave8(p2, p3); // b0d0f0h0...

		// transpose pass 3
		dct_interleave8(p0, p2); // a0b0c0d0...
		dct_interleave8(p1, p3); // a4b4c4d4...

		// store
		_mm_storel_epi64((__m128i *) out, p0); out += out_stride;
		_mm_storel_epi64((__m128i *) out, _mm_shuffle_epi32(p0, 0x4e)); out += out_stride;
		_mm_storel_epi64((__m128i *) out, p2); out += out_stride;
		_mm_storel_epi64((__m128i *) out, _mm_shuffle_epi32(p2, 0x4e)); out += out_stride;
		_mm_storel_epi64((__m128i *) out, p1); out += out_stride;
		_mm_storel_epi64((__m128i *) out, _mm_shuffle_epi32(p1, 0x4e)); out += out_stride;
		_mm_storel_epi64((__m128i *) out, p3); out += out_stride;
		_mm_storel_epi64((__m128i *) out, _mm_shuffle_epi32(p3, 0x4e));
	}

#undef dct_const
#undef dct_rot
#undef dct_widen
#undef dct_wadd
#undef dct_wsub
#undef dct_bfly32o
#undef dct_interleave8
#undef dct_interleave16
#undef dct_pass
}

#endif // STBI_SSE2

#ifdef STBI_NEON

// NEON integer IDCT. should produce bit-identical
// results to the generic C version.
static void stbi__idct_simd(stbi_uc *out, int out_stride, short data[64])
{
	int16x8_t row0, row1, row2, row3, row4, row5, row6, row7;

	int16x4_t rot0_0 = vdup_n_s16(stbi__f2f(0.5411961f));
	int16x4_t rot0_1 = vdup_n_s16(stbi__f2f(-1.847759065f));
	int16x4_t rot0_2 = vdup_n_s16(stbi__f2f(0.765366865f));
	int16x4_t rot1_0 = vdup_n_s16(stbi__f2f(1.175875602f));
	int16x4_t rot1_1 = vdup_n_s16(stbi__f2f(-0.899976223f));
	int16x4_t rot1_2 = vdup_n_s16(stbi__f2f(-2.562915447f));
	int16x4_t rot2_0 = vdup_n_s16(stbi__f2f(-1.961570560f));
	int16x4_t rot2_1 = vdup_n_s16(stbi__f2f(-0.390180644f));
	int16x4_t rot3_0 = vdup_n_s16(stbi__f2f(0.298631336f));
	int16x4_t rot3_1 = vdup_n_s16(stbi__f2f(2.053119869f));
	int16x4_t rot3_2 = vdup_n_s16(stbi__f2f(3.072711026f));
	int16x4_t rot3_3 = vdup_n_s16(stbi__f2f(1.501321110f));

#define dct_long_mul(out, inq, coeff) \
   int32x4_t out##_l = vmull_s16(vget_low_s16(inq), coeff); \
   int32x4_t out##_h = vmull_s16(vget_high_s16(inq), coeff)

#define dct_long_mac(out, acc, inq, coeff) \
   int32x4_t out##_l = vmlal_s16(acc##_l, vget_low_s16(inq), coeff); \
   int32x4_t out##_h = vmlal_s16(acc##_h, vget_high_s16(inq), coeff)

#define dct_widen(out, inq) \
   int32x4_t out##_l = vshll_n_s16(vget_low_s16(inq), 12); \
   int32x4_t out##_h = vshll_n_s16(vget_high_s16(inq), 12)

	// wide add
#define dct_wadd(out, a, b) \
   int32x4_t out##_l = vaddq_s32(a##_l, b##_l); \
   int32x4_t out##_h = vaddq_s32(a##_h, b##_h)

	// wide sub
#define dct_wsub(out, a, b) \
   int32x4_t out##_l = vsubq_s32(a##_l, b##_l); \
   int32x4_t out##_h = vsubq_s32(a##_h, b##_h)

	// butterfly a/b, then shift using "shiftop" by "s" and pack
#define dct_bfly32o(out0,out1, a,b,shiftop,s) \
	   { \
      dct_wadd(sum, a, b); \
      dct_wsub(dif, a, b); \
      out0 = vcombine_s16(shiftop(sum_l, s), shiftop(sum_h, s)); \
      out1 = vcombine_s16(shiftop(dif_l, s), shiftop(dif_h, s)); \
	   }

#define dct_pass(shiftop, shift) \
	   { \
      /* even part */ \
      int16x8_t sum26 = vaddq_s16(row2, row6); \
      dct_long_mul(p1e, sum26, rot0_0); \
      dct_long_mac(t2e, p1e, row6, rot0_1); \
      dct_long_mac(t3e, p1e, row2, rot0_2); \
      int16x8_t sum04 = vaddq_s16(row0, row4); \
      int16x8_t dif04 = vsubq_s16(row0, row4); \
      dct_widen(t0e, sum04); \
      dct_widen(t1e, dif04); \
      dct_wadd(x0, t0e, t3e); \
      dct_wsub(x3, t0e, t3e); \
      dct_wadd(x1, t1e, t2e); \
      dct_wsub(x2, t1e, t2e); \
      /* odd part */ \
      int16x8_t sum15 = vaddq_s16(row1, row5); \
      int16x8_t sum17 = vaddq_s16(row1, row7); \
      int16x8_t sum35 = vaddq_s16(row3, row5); \
      int16x8_t sum37 = vaddq_s16(row3, row7); \
      int16x8_t sumodd = vaddq_s16(sum17, sum35); \
      dct_long_mul(p5o, sumodd, rot1_0); \
      dct_long_mac(p1o, p5o, sum17, rot1_1); \
      dct_long_mac(p2o, p5o, sum35, rot1_2); \
      dct_long_mul(p3o, sum37, rot2_0); \
      dct_long_mul(p4o, sum15, rot2_1); \
      dct_wadd(sump13o, p1o, p3o); \
      dct_wadd(sump24o, p2o, p4o); \
      dct_wadd(sump23o, p2o, p3o); \
      dct_wadd(sump14o, p1o, p4o); \
      dct_long_mac(x4, sump13o, row7, rot3_0); \
      dct_long_mac(x5, sump24o, row5, rot3_1); \
      dct_long_mac(x6, sump23o, row3, rot3_2); \
      dct_long_mac(x7, sump14o, row1, rot3_3); \
      dct_bfly32o(row0,row7, x0,x7,shiftop,shift); \
      dct_bfly32o(row1,row6, x1,x6,shiftop,shift); \
      dct_bfly32o(row2,row5, x2,x5,shiftop,shift); \
      dct_bfly32o(row3,row4, x3,x4,shiftop,shift); \
	   }

	// load
	row0 = vld1q_s16(data + 0 * 8);
	row1 = vld1q_s16(data + 1 * 8);
	row2 = vld1q_s16(data + 2 * 8);
	row3 = vld1q_s16(data + 3 * 8);
	row4 = vld1q_s16(data + 4 * 8);
	row5 = vld1q_s16(data + 5 * 8);
	row6 = vld1q_s16(data + 6 * 8);
	row7 = vld1q_s16(data + 7 * 8);

	// add DC bias
	row0 = vaddq_s16(row0, vsetq_lane_s16(1024, vdupq_n_s16(0), 0));

	// column pass
	dct_pass(vrshrn_n_s32, 10);

	// 16bit 8x8 transpose
	{
		// these three map to a single VTRN.16, VTRN.32, and VSWP, respectively.
		// whether compilers actually get this is another story, sadly.
#define dct_trn16(x, y) { int16x8x2_t t = vtrnq_s16(x, y); x = t.val[0]; y = t.val[1]; }
#define dct_trn32(x, y) { int32x4x2_t t = vtrnq_s32(vreinterpretq_s32_s16(x), vreinterpretq_s32_s16(y)); x = vreinterpretq_s16_s32(t.val[0]); y = vreinterpretq_s16_s32(t.val[1]); }
#define dct_trn64(x, y) { int16x8_t x0 = x; int16x8_t y0 = y; x = vcombine_s16(vget_low_s16(x0), vget_low_s16(y0)); y = vcombine_s16(vget_high_s16(x0), vget_high_s16(y0)); }

		// pass 1
		dct_trn16(row0, row1); // a0b0a2b2a4b4a6b6
		dct_trn16(row2, row3);
		dct_trn16(row4, row5);
		dct_trn16(row6, row7);

		// pass 2
		dct_trn32(row0, row2); // a0b0c0d0a4b4c4d4
		dct_trn32(row1, row3);
		dct_trn32(row4, row6);
		dct_trn32(row5, row7);

		// pass 3
		dct_trn64(row0, row4); // a0b0c0d0e0f0g0h0
		dct_trn64(row1, row5);
		dct_trn64(row2, row6);
		dct_trn64(row3, row7);

#undef dct_trn16
#undef dct_trn32
#undef dct_trn64
	}

	// row pass
	// vrshrn_n_s32 only supports shifts up to 16, we need
	// 17. so do a non-rounding shift of 16 first then follow
	// up with a rounding shift by 1.
	dct_pass(vshrn_n_s32, 16);

	{
		// pack and round
		uint8x8_t p0 = vqrshrun_n_s16(row0, 1);
		uint8x8_t p1 = vqrshrun_n_s16(row1, 1);
		uint8x8_t p2 = vqrshrun_n_s16(row2, 1);
		uint8x8_t p3 = vqrshrun_n_s16(row3, 1);
		uint8x8_t p4 = vqrshrun_n_s16(row4, 1);
		uint8x8_t p5 = vqrshrun_n_s16(row5, 1);
		uint8x8_t p6 = vqrshrun_n_s16(row6, 1);
		uint8x8_t p7 = vqrshrun_n_s16(row7, 1);

		// again, these can translate into one instruction, but often don't.
#define dct_trn8_8(x, y) { uint8x8x2_t t = vtrn_u8(x, y); x = t.val[0]; y = t.val[1]; }
#define dct_trn8_16(x, y) { uint16x4x2_t t = vtrn_u16(vreinterpret_u16_u8(x), vreinterpret_u16_u8(y)); x = vreinterpret_u8_u16(t.val[0]); y = vreinterpret_u8_u16(t.val[1]); }
#define dct_trn8_32(x, y) { uint32x2x2_t t = vtrn_u32(vreinterpret_u32_u8(x), vreinterpret_u32_u8(y)); x = vreinterpret_u8_u32(t.val[0]); y = vreinterpret_u8_u32(t.val[1]); }

		// sadly can't use interleaved stores here since we only write
		// 8 bytes to each scan line!

		// 8x8 8-bit transpose pass 1
		dct_trn8_8(p0, p1);
		dct_trn8_8(p2, p3);
		dct_trn8_8(p4, p5);
		dct_trn8_8(p6, p7);

		// pass 2
		dct_trn8_16(p0, p2);
		dct_trn8_16(p1, p3);
		dct_trn8_16(p4, p6);
		dct_trn8_16(p5, p7);

		// pass 3
		dct_trn8_32(p0, p4);
		dct_trn8_32(p1, p5);
		dct_trn8_32(p2, p6);
		dct_trn8_32(p3, p7);

		// store
		vst1_u8(out, p0); out += out_stride;
		vst1_u8(out, p1); out += out_stride;
		vst1_u8(out, p2); out += out_stride;
		vst1_u8(out, p3); out += out_stride;
		vst1_u8(out, p4); out += out_stride;
		vst1_u8(out, p5); out += out_stride;
		vst1_u8(out, p6); out += out_stride;
		vst1_u8(out, p7);

#undef dct_trn8_8
#undef dct_trn8_16
#undef dct_trn8_32
	}

#undef dct_long_mul
#undef dct_long_mac
#undef dct_widen
#undef dct_wadd
#undef dct_wsub
#undef dct_bfly32o
#undef dct_pass
}

#endif // STBI_NEON

#define STBI__MARKER_none  0xff
// if there's a pending marker from the entropy stream, return that
// otherwise, fetch from the stream and get a marker. if there's no
// marker, return 0xff, which is never a valid marker value
static stbi_uc stbi__get_marker(stbi__jpeg *j)
{
	stbi_uc x;
	if (j->marker != STBI__MARKER_none) { x = j->marker; j->marker = STBI__MARKER_none; return x; }
	x = stbi__get8(j->s);
	if (x != 0xff) return STBI__MARKER_none;
	while (x == 0xff)
		x = stbi__get8(j->s);
	return x;
}

// in each scan, we'll have scan_n components, and the order
// of the components is specified by order[]
#define STBI__RESTART(x)     ((x) >= 0xd0 && (x) <= 0xd7)

// after a restart interval, stbi__jpeg_reset the entropy decoder and
// the dc prediction
static void stbi__jpeg_reset(stbi__jpeg *j)
{
	j->code_bits = 0;
	j->code_buffer = 0;
	j->nomore = 0;
	j->img_comp[0].dc_pred = j->img_comp[1].dc_pred = j->img_comp[2].dc_pred = 0;
	j->marker = STBI__MARKER_none;
	j->todo = j->restart_interval ? j->restart_interval : 0x7fffffff;
	j->eob_run = 0;
	// no more than 1<<31 MCUs if no restart_interal? that's plenty safe,
	// since we don't even allow 1<<30 pixels
}

static int stbi__parse_entropy_coded_data(stbi__jpeg *z)
{
	stbi__jpeg_reset(z);
	if (!z->progressive) {
		if (z->scan_n == 1) {
			int i, j;
			STBI_SIMD_ALIGN(short, data[64]);
			int n = z->order[0];
			// non-interleaved data, we just need to process one block at a time,
			// in trivial scanline order
			// number of blocks to do just depends on how many actual "pixels" this
			// component has, independent of interleaved MCU blocking and such
			int w = (z->img_comp[n].x + 7) >> 3;
			int h = (z->img_comp[n].y + 7) >> 3;
			for (j = 0; j < h; ++j) {
				for (i = 0; i < w; ++i) {
					int ha = z->img_comp[n].ha;
					if (!stbi__jpeg_decode_block(z, data, z->huff_dc + z->img_comp[n].hd, z->huff_ac + ha, z->fast_ac[ha], n, z->dequant[z->img_comp[n].tq])) return 0;
					z->idct_block_kernel(z->img_comp[n].data + z->img_comp[n].w2*j * 8 + i * 8, z->img_comp[n].w2, data);
					// every data block is an MCU, so countdown the restart interval
					if (--z->todo <= 0) {
						if (z->code_bits < 24) stbi__grow_buffer_unsafe(z);
						// if it's NOT a restart, then just bail, so we get corrupt data
						// rather than no data
						if (!STBI__RESTART(z->marker)) return 1;
						stbi__jpeg_reset(z);
					}
				}
			}
			return 1;
		}
		else { // interleaved
			int i, j, k, x, y;
			STBI_SIMD_ALIGN(short, data[64]);
			for (j = 0; j < z->img_mcu_y; ++j) {
				for (i = 0; i < z->img_mcu_x; ++i) {
					// scan an interleaved mcu... process scan_n components in order
					for (k = 0; k < z->scan_n; ++k) {
						int n = z->order[k];
						// scan out an mcu's worth of this component; that's just determined
						// by the basic H and V specified for the component
						for (y = 0; y < z->img_comp[n].v; ++y) {
							for (x = 0; x < z->img_comp[n].h; ++x) {
								int x2 = (i*z->img_comp[n].h + x) * 8;
								int y2 = (j*z->img_comp[n].v + y) * 8;
								int ha = z->img_comp[n].ha;
								if (!stbi__jpeg_decode_block(z, data, z->huff_dc + z->img_comp[n].hd, z->huff_ac + ha, z->fast_ac[ha], n, z->dequant[z->img_comp[n].tq])) return 0;
								z->idct_block_kernel(z->img_comp[n].data + z->img_comp[n].w2*y2 + x2, z->img_comp[n].w2, data);
							}
						}
					}
					// after all interleaved components, that's an interleaved MCU,
					// so now count down the restart interval
					if (--z->todo <= 0) {
						if (z->code_bits < 24) stbi__grow_buffer_unsafe(z);
						if (!STBI__RESTART(z->marker)) return 1;
						stbi__jpeg_reset(z);
					}
				}
			}
			return 1;
		}
	}
	else {
		if (z->scan_n == 1) {
			int i, j;
			int n = z->order[0];
			// non-interleaved data, we just need to process one block at a time,
			// in trivial scanline order
			// number of blocks to do just depends on how many actual "pixels" this
			// component has, independent of interleaved MCU blocking and such
			int w = (z->img_comp[n].x + 7) >> 3;
			int h = (z->img_comp[n].y + 7) >> 3;
			for (j = 0; j < h; ++j) {
				for (i = 0; i < w; ++i) {
					short *data = z->img_comp[n].coeff + 64 * (i + j * z->img_comp[n].coeff_w);
					if (z->spec_start == 0) {
						if (!stbi__jpeg_decode_block_prog_dc(z, data, &z->huff_dc[z->img_comp[n].hd], n))
							return 0;
					}
					else {
						int ha = z->img_comp[n].ha;
						if (!stbi__jpeg_decode_block_prog_ac(z, data, &z->huff_ac[ha], z->fast_ac[ha]))
							return 0;
					}
					// every data block is an MCU, so countdown the restart interval
					if (--z->todo <= 0) {
						if (z->code_bits < 24) stbi__grow_buffer_unsafe(z);
						if (!STBI__RESTART(z->marker)) return 1;
						stbi__jpeg_reset(z);
					}
				}
			}
			return 1;
		}
		else { // interleaved
			int i, j, k, x, y;
			for (j = 0; j < z->img_mcu_y; ++j) {
				for (i = 0; i < z->img_mcu_x; ++i) {
					// scan an interleaved mcu... process scan_n components in order
					for (k = 0; k < z->scan_n; ++k) {
						int n = z->order[k];
						// scan out an mcu's worth of this component; that's just determined
						// by the basic H and V specified for the component
						for (y = 0; y < z->img_comp[n].v; ++y) {
							for (x = 0; x < z->img_comp[n].h; ++x) {
								int x2 = (i*z->img_comp[n].h + x);
								int y2 = (j*z->img_comp[n].v + y);
								short *data = z->img_comp[n].coeff + 64 * (x2 + y2 * z->img_comp[n].coeff_w);
								if (!stbi__jpeg_decode_block_prog_dc(z, data, &z->huff_dc[z->img_comp[n].hd], n))
									return 0;
							}
						}
					}
					// after all interleaved components, that's an interleaved MCU,
					// so now count down the restart interval
					if (--z->todo <= 0) {
						if (z->code_bits < 24) stbi__grow_buffer_unsafe(z);
						if (!STBI__RESTART(z->marker)) return 1;
						stbi__jpeg_reset(z);
					}
				}
			}
			return 1;
		}
	}
}

static void stbi__jpeg_dequantize(short *data, stbi_uc *dequant)
{
	int i;
	for (i = 0; i < 64; ++i)
		data[i] *= dequant[i];
}

static void stbi__jpeg_finish(stbi__jpeg *z)
{
	if (z->progressive) {
		// dequantize and idct the data
		int i, j, n;
		for (n = 0; n < z->s->img_n; ++n) {
			int w = (z->img_comp[n].x + 7) >> 3;
			int h = (z->img_comp[n].y + 7) >> 3;
			for (j = 0; j < h; ++j) {
				for (i = 0; i < w; ++i) {
					short *data = z->img_comp[n].coeff + 64 * (i + j * z->img_comp[n].coeff_w);
					stbi__jpeg_dequantize(data, z->dequant[z->img_comp[n].tq]);
					z->idct_block_kernel(z->img_comp[n].data + z->img_comp[n].w2*j * 8 + i * 8, z->img_comp[n].w2, data);
				}
			}
		}
	}
}

static int stbi__process_marker(stbi__jpeg *z, int m)
{
	int L;
	switch (m) {
	case STBI__MARKER_none: // no marker found
		return stbi__err("expected marker", "Corrupt JPEG");

	case 0xDD: // DRI - specify restart interval
		if (stbi__get16be(z->s) != 4) return stbi__err("bad DRI len", "Corrupt JPEG");
		z->restart_interval = stbi__get16be(z->s);
		return 1;

	case 0xDB: // DQT - define quantization table
		L = stbi__get16be(z->s) - 2;
		while (L > 0) {
			int q = stbi__get8(z->s);
			int p = q >> 4;
			int t = q & 15, i;
			if (p != 0) return stbi__err("bad DQT type", "Corrupt JPEG");
			if (t > 3) return stbi__err("bad DQT table", "Corrupt JPEG");
			for (i = 0; i < 64; ++i)
				z->dequant[t][stbi__jpeg_dezigzag[i]] = stbi__get8(z->s);
			L -= 65;
		}
		return L == 0;

	case 0xC4: // DHT - define huffman table
		L = stbi__get16be(z->s) - 2;
		while (L > 0) {
			stbi_uc *v;
			int sizes[16], i, n = 0;
			int q = stbi__get8(z->s);
			int tc = q >> 4;
			int th = q & 15;
			if (tc > 1 || th > 3) return stbi__err("bad DHT header", "Corrupt JPEG");
			for (i = 0; i < 16; ++i) {
				sizes[i] = stbi__get8(z->s);
				n += sizes[i];
			}
			L -= 17;
			if (tc == 0) {
				if (!stbi__build_huffman(z->huff_dc + th, sizes)) return 0;
				v = z->huff_dc[th].values;
			}
			else {
				if (!stbi__build_huffman(z->huff_ac + th, sizes)) return 0;
				v = z->huff_ac[th].values;
			}
			for (i = 0; i < n; ++i)
				v[i] = stbi__get8(z->s);
			if (tc != 0)
				stbi__build_fast_ac(z->fast_ac[th], z->huff_ac + th);
			L -= n;
		}
		return L == 0;
	}
	// check for comment block or APP blocks
	if ((m >= 0xE0 && m <= 0xEF) || m == 0xFE) {
		stbi__skip(z->s, stbi__get16be(z->s) - 2);
		return 1;
	}
	return 0;
}

// after we see SOS
static int stbi__process_scan_header(stbi__jpeg *z)
{
	int i;
	int Ls = stbi__get16be(z->s);
	z->scan_n = stbi__get8(z->s);
	if (z->scan_n < 1 || z->scan_n > 4 || z->scan_n > (int)z->s->img_n) return stbi__err("bad SOS component count", "Corrupt JPEG");
	if (Ls != 6 + 2 * z->scan_n) return stbi__err("bad SOS len", "Corrupt JPEG");
	for (i = 0; i < z->scan_n; ++i) {
		int id = stbi__get8(z->s), which;
		int q = stbi__get8(z->s);
		for (which = 0; which < z->s->img_n; ++which)
			if (z->img_comp[which].id == id)
				break;
		if (which == z->s->img_n) return 0; // no match
		z->img_comp[which].hd = q >> 4;   if (z->img_comp[which].hd > 3) return stbi__err("bad DC huff", "Corrupt JPEG");
		z->img_comp[which].ha = q & 15;   if (z->img_comp[which].ha > 3) return stbi__err("bad AC huff", "Corrupt JPEG");
		z->order[i] = which;
	}

   {
	   int aa;
	   z->spec_start = stbi__get8(z->s);
	   z->spec_end = stbi__get8(z->s); // should be 63, but might be 0
	   aa = stbi__get8(z->s);
	   z->succ_high = (aa >> 4);
	   z->succ_low = (aa & 15);
	   if (z->progressive) {
		   if (z->spec_start > 63 || z->spec_end > 63 || z->spec_start > z->spec_end || z->succ_high > 13 || z->succ_low > 13)
			   return stbi__err("bad SOS", "Corrupt JPEG");
	   }
	   else {
		   if (z->spec_start != 0) return stbi__err("bad SOS", "Corrupt JPEG");
		   if (z->succ_high != 0 || z->succ_low != 0) return stbi__err("bad SOS", "Corrupt JPEG");
		   z->spec_end = 63;
	   }
   }

   return 1;
}

static int stbi__process_frame_header(stbi__jpeg *z, int scan)
{
	stbi__context *s = z->s;
	int Lf, p, i, q, h_max = 1, v_max = 1, c;
	Lf = stbi__get16be(s);         if (Lf < 11) return stbi__err("bad SOF len", "Corrupt JPEG"); // JPEG
	p = stbi__get8(s);            if (p != 8) return stbi__err("only 8-bit", "JPEG format not supported: 8-bit only"); // JPEG baseline
	s->img_y = stbi__get16be(s);   if (s->img_y == 0) return stbi__err("no header height", "JPEG format not supported: delayed height"); // Legal, but we don't handle it--but neither does IJG
	s->img_x = stbi__get16be(s);   if (s->img_x == 0) return stbi__err("0 width", "Corrupt JPEG"); // JPEG requires
	c = stbi__get8(s);
	if (c != 3 && c != 1) return stbi__err("bad component count", "Corrupt JPEG");    // JFIF requires
	s->img_n = c;
	for (i = 0; i < c; ++i) {
		z->img_comp[i].data = NULL;
		z->img_comp[i].linebuf = NULL;
	}

	if (Lf != 8 + 3 * s->img_n) return stbi__err("bad SOF len", "Corrupt JPEG");

	z->rgb = 0;
	for (i = 0; i < s->img_n; ++i) {
		static unsigned char rgb[3] = { 'R', 'G', 'B' };
		z->img_comp[i].id = stbi__get8(s);
		if (z->img_comp[i].id != i + 1)   // JFIF requires
			if (z->img_comp[i].id != i) {  // some version of jpegtran outputs non-JFIF-compliant files!
				// somethings output this (see http://fileformats.archiveteam.org/wiki/JPEG#Color_format)
				if (z->img_comp[i].id != rgb[i])
					return stbi__err("bad component ID", "Corrupt JPEG");
				++z->rgb;
			}
		q = stbi__get8(s);
		z->img_comp[i].h = (q >> 4);  if (!z->img_comp[i].h || z->img_comp[i].h > 4) return stbi__err("bad H", "Corrupt JPEG");
		z->img_comp[i].v = q & 15;    if (!z->img_comp[i].v || z->img_comp[i].v > 4) return stbi__err("bad V", "Corrupt JPEG");
		z->img_comp[i].tq = stbi__get8(s);  if (z->img_comp[i].tq > 3) return stbi__err("bad TQ", "Corrupt JPEG");
	}

	if (scan != STBI__SCAN_load) return 1;

	if ((1 << 30) / s->img_x / s->img_n < s->img_y) return stbi__err("too large", "Image too large to decode");

	for (i = 0; i < s->img_n; ++i) {
		if (z->img_comp[i].h > h_max) h_max = z->img_comp[i].h;
		if (z->img_comp[i].v > v_max) v_max = z->img_comp[i].v;
	}

	// compute interleaved mcu info
	z->img_h_max = h_max;
	z->img_v_max = v_max;
	z->img_mcu_w = h_max * 8;
	z->img_mcu_h = v_max * 8;
	z->img_mcu_x = (s->img_x + z->img_mcu_w - 1) / z->img_mcu_w;
	z->img_mcu_y = (s->img_y + z->img_mcu_h - 1) / z->img_mcu_h;

	for (i = 0; i < s->img_n; ++i) {
		// number of effective pixels (e.g. for non-interleaved MCU)
		z->img_comp[i].x = (s->img_x * z->img_comp[i].h + h_max - 1) / h_max;
		z->img_comp[i].y = (s->img_y * z->img_comp[i].v + v_max - 1) / v_max;
		// to simplify generation, we'll allocate enough memory to decode
		// the bogus oversized data from using interleaved MCUs and their
		// big blocks (e.g. a 16x16 iMCU on an image of width 33); we won't
		// discard the extra data until colorspace conversion
		z->img_comp[i].w2 = z->img_mcu_x * z->img_comp[i].h * 8;
		z->img_comp[i].h2 = z->img_mcu_y * z->img_comp[i].v * 8;
		z->img_comp[i].raw_data = stbi__malloc(z->img_comp[i].w2 * z->img_comp[i].h2 + 15);

		if (z->img_comp[i].raw_data == NULL) {
			for (--i; i >= 0; --i) {
				STBI_FREE(z->img_comp[i].raw_data);
				z->img_comp[i].raw_data = NULL;
			}
			return stbi__err("outofmem", "Out of memory");
		}
		// align blocks for idct using mmx/sse
		z->img_comp[i].data = (stbi_uc*)(((size_t)z->img_comp[i].raw_data + 15) & ~15);
		z->img_comp[i].linebuf = NULL;
		if (z->progressive) {
			z->img_comp[i].coeff_w = (z->img_comp[i].w2 + 7) >> 3;
			z->img_comp[i].coeff_h = (z->img_comp[i].h2 + 7) >> 3;
			z->img_comp[i].raw_coeff = STBI_MALLOC(z->img_comp[i].coeff_w * z->img_comp[i].coeff_h * 64 * sizeof(short) + 15);
			z->img_comp[i].coeff = (short*)(((size_t)z->img_comp[i].raw_coeff + 15) & ~15);
		}
		else {
			z->img_comp[i].coeff = 0;
			z->img_comp[i].raw_coeff = 0;
		}
	}

	return 1;
}

// use comparisons since in some cases we handle more than one case (e.g. SOF)
#define stbi__DNL(x)         ((x) == 0xdc)
#define stbi__SOI(x)         ((x) == 0xd8)
#define stbi__EOI(x)         ((x) == 0xd9)
#define stbi__SOF(x)         ((x) == 0xc0 || (x) == 0xc1 || (x) == 0xc2)
#define stbi__SOS(x)         ((x) == 0xda)

#define stbi__SOF_progressive(x)   ((x) == 0xc2)

static int stbi__decode_jpeg_header(stbi__jpeg *z, int scan)
{
	int m;
	z->marker = STBI__MARKER_none; // initialize cached marker to empty
	m = stbi__get_marker(z);
	if (!stbi__SOI(m)) return stbi__err("no SOI", "Corrupt JPEG");
	if (scan == STBI__SCAN_type) return 1;
	m = stbi__get_marker(z);
	while (!stbi__SOF(m)) {
		if (!stbi__process_marker(z, m)) return 0;
		m = stbi__get_marker(z);
		while (m == STBI__MARKER_none) {
			// some files have extra padding after their blocks, so ok, we'll scan
			if (stbi__at_eof(z->s)) return stbi__err("no SOF", "Corrupt JPEG");
			m = stbi__get_marker(z);
		}
	}
	z->progressive = stbi__SOF_progressive(m);
	if (!stbi__process_frame_header(z, scan)) return 0;
	return 1;
}

// decode image to YCbCr format
static int stbi__decode_jpeg_image(stbi__jpeg *j)
{
	int m;
	for (m = 0; m < 4; m++) {
		j->img_comp[m].raw_data = NULL;
		j->img_comp[m].raw_coeff = NULL;
	}
	j->restart_interval = 0;
	if (!stbi__decode_jpeg_header(j, STBI__SCAN_load)) return 0;
	m = stbi__get_marker(j);
	while (!stbi__EOI(m)) {
		if (stbi__SOS(m)) {
			if (!stbi__process_scan_header(j)) return 0;
			if (!stbi__parse_entropy_coded_data(j)) return 0;
			if (j->marker == STBI__MARKER_none) {
				// handle 0s at the end of image data from IP Kamera 9060
				while (!stbi__at_eof(j->s)) {
					int x = stbi__get8(j->s);
					if (x == 255) {
						j->marker = stbi__get8(j->s);
						break;
					}
					else if (x != 0) {
						return stbi__err("junk before marker", "Corrupt JPEG");
					}
				}
				// if we reach eof without hitting a marker, stbi__get_marker() below will fail and we'll eventually return 0
			}
		}
		else {
			if (!stbi__process_marker(j, m)) return 0;
		}
		m = stbi__get_marker(j);
	}
	if (j->progressive)
		stbi__jpeg_finish(j);
	return 1;
}

// static jfif-centered resampling (across block boundaries)

typedef stbi_uc *(*resample_row_func)(stbi_uc *out, stbi_uc *in0, stbi_uc *in1,
	int w, int hs);

#define stbi__div4(x) ((stbi_uc) ((x) >> 2))

static stbi_uc *resample_row_1(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs)
{
	STBI_NOTUSED(out);
	STBI_NOTUSED(in_far);
	STBI_NOTUSED(w);
	STBI_NOTUSED(hs);
	return in_near;
}

static stbi_uc* stbi__resample_row_v_2(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs)
{
	// need to generate two samples vertically for every one in input
	int i;
	STBI_NOTUSED(hs);
	for (i = 0; i < w; ++i)
		out[i] = stbi__div4(3 * in_near[i] + in_far[i] + 2);
	return out;
}

static stbi_uc*  stbi__resample_row_h_2(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs)
{
	// need to generate two samples horizontally for every one in input
	int i;
	stbi_uc *input = in_near;

	if (w == 1) {
		// if only one sample, can't do any interpolation
		out[0] = out[1] = input[0];
		return out;
	}

	out[0] = input[0];
	out[1] = stbi__div4(input[0] * 3 + input[1] + 2);
	for (i = 1; i < w - 1; ++i) {
		int n = 3 * input[i] + 2;
		out[i * 2 + 0] = stbi__div4(n + input[i - 1]);
		out[i * 2 + 1] = stbi__div4(n + input[i + 1]);
	}
	out[i * 2 + 0] = stbi__div4(input[w - 2] * 3 + input[w - 1] + 2);
	out[i * 2 + 1] = input[w - 1];

	STBI_NOTUSED(in_far);
	STBI_NOTUSED(hs);

	return out;
}

#define stbi__div16(x) ((stbi_uc) ((x) >> 4))

static stbi_uc *stbi__resample_row_hv_2(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs)
{
	// need to generate 2x2 samples for every one in input
	int i, t0, t1;
	if (w == 1) {
		out[0] = out[1] = stbi__div4(3 * in_near[0] + in_far[0] + 2);
		return out;
	}

	t1 = 3 * in_near[0] + in_far[0];
	out[0] = stbi__div4(t1 + 2);
	for (i = 1; i < w; ++i) {
		t0 = t1;
		t1 = 3 * in_near[i] + in_far[i];
		out[i * 2 - 1] = stbi__div16(3 * t0 + t1 + 8);
		out[i * 2] = stbi__div16(3 * t1 + t0 + 8);
	}
	out[w * 2 - 1] = stbi__div4(t1 + 2);

	STBI_NOTUSED(hs);

	return out;
}

#if defined(STBI_SSE2) || defined(STBI_NEON)
static stbi_uc *stbi__resample_row_hv_2_simd(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs)
{
	// need to generate 2x2 samples for every one in input
	int i = 0, t0, t1;

	if (w == 1) {
		out[0] = out[1] = stbi__div4(3 * in_near[0] + in_far[0] + 2);
		return out;
	}

	t1 = 3 * in_near[0] + in_far[0];
	// process groups of 8 pixels for as long as we can.
	// note we can't handle the last pixel in a row in this loop
	// because we need to handle the filter boundary conditions.
	for (; i < ((w - 1) & ~7); i += 8) {
#if defined(STBI_SSE2)
		// load and perform the vertical filtering pass
		// this uses 3*x + y = 4*x + (y - x)
		__m128i zero = _mm_setzero_si128();
		__m128i farb = _mm_loadl_epi64((__m128i *) (in_far + i));
		__m128i nearb = _mm_loadl_epi64((__m128i *) (in_near + i));
		__m128i farw = _mm_unpacklo_epi8(farb, zero);
		__m128i nearw = _mm_unpacklo_epi8(nearb, zero);
		__m128i diff = _mm_sub_epi16(farw, nearw);
		__m128i nears = _mm_slli_epi16(nearw, 2);
		__m128i curr = _mm_add_epi16(nears, diff); // current row

		// horizontal filter works the same based on shifted vers of current
		// row. "prev" is current row shifted right by 1 pixel; we need to
		// insert the previous pixel value (from t1).
		// "next" is current row shifted left by 1 pixel, with first pixel
		// of next block of 8 pixels added in.
		__m128i prv0 = _mm_slli_si128(curr, 2);
		__m128i nxt0 = _mm_srli_si128(curr, 2);
		__m128i prev = _mm_insert_epi16(prv0, t1, 0);
		__m128i next = _mm_insert_epi16(nxt0, 3 * in_near[i + 8] + in_far[i + 8], 7);

		// horizontal filter, polyphase implementation since it's convenient:
		// even pixels = 3*cur + prev = cur*4 + (prev - cur)
		// odd  pixels = 3*cur + next = cur*4 + (next - cur)
		// note the shared term.
		__m128i bias = _mm_set1_epi16(8);
		__m128i curs = _mm_slli_epi16(curr, 2);
		__m128i prvd = _mm_sub_epi16(prev, curr);
		__m128i nxtd = _mm_sub_epi16(next, curr);
		__m128i curb = _mm_add_epi16(curs, bias);
		__m128i even = _mm_add_epi16(prvd, curb);
		__m128i odd = _mm_add_epi16(nxtd, curb);

		// interleave even and odd pixels, then undo scaling.
		__m128i int0 = _mm_unpacklo_epi16(even, odd);
		__m128i int1 = _mm_unpackhi_epi16(even, odd);
		__m128i de0 = _mm_srli_epi16(int0, 4);
		__m128i de1 = _mm_srli_epi16(int1, 4);

		// pack and write output
		__m128i outv = _mm_packus_epi16(de0, de1);
		_mm_storeu_si128((__m128i *) (out + i * 2), outv);
#elif defined(STBI_NEON)
		// load and perform the vertical filtering pass
		// this uses 3*x + y = 4*x + (y - x)
		uint8x8_t farb = vld1_u8(in_far + i);
		uint8x8_t nearb = vld1_u8(in_near + i);
		int16x8_t diff = vreinterpretq_s16_u16(vsubl_u8(farb, nearb));
		int16x8_t nears = vreinterpretq_s16_u16(vshll_n_u8(nearb, 2));
		int16x8_t curr = vaddq_s16(nears, diff); // current row

		// horizontal filter works the same based on shifted vers of current
		// row. "prev" is current row shifted right by 1 pixel; we need to
		// insert the previous pixel value (from t1).
		// "next" is current row shifted left by 1 pixel, with first pixel
		// of next block of 8 pixels added in.
		int16x8_t prv0 = vextq_s16(curr, curr, 7);
		int16x8_t nxt0 = vextq_s16(curr, curr, 1);
		int16x8_t prev = vsetq_lane_s16(t1, prv0, 0);
		int16x8_t next = vsetq_lane_s16(3 * in_near[i + 8] + in_far[i + 8], nxt0, 7);

		// horizontal filter, polyphase implementation since it's convenient:
		// even pixels = 3*cur + prev = cur*4 + (prev - cur)
		// odd  pixels = 3*cur + next = cur*4 + (next - cur)
		// note the shared term.
		int16x8_t curs = vshlq_n_s16(curr, 2);
		int16x8_t prvd = vsubq_s16(prev, curr);
		int16x8_t nxtd = vsubq_s16(next, curr);
		int16x8_t even = vaddq_s16(curs, prvd);
		int16x8_t odd = vaddq_s16(curs, nxtd);

		// undo scaling and round, then store with even/odd phases interleaved
		uint8x8x2_t o;
		o.val[0] = vqrshrun_n_s16(even, 4);
		o.val[1] = vqrshrun_n_s16(odd, 4);
		vst2_u8(out + i * 2, o);
#endif

		// "previous" value for next iter
		t1 = 3 * in_near[i + 7] + in_far[i + 7];
	}

	t0 = t1;
	t1 = 3 * in_near[i] + in_far[i];
	out[i * 2] = stbi__div16(3 * t1 + t0 + 8);

	for (++i; i < w; ++i) {
		t0 = t1;
		t1 = 3 * in_near[i] + in_far[i];
		out[i * 2 - 1] = stbi__div16(3 * t0 + t1 + 8);
		out[i * 2] = stbi__div16(3 * t1 + t0 + 8);
	}
	out[w * 2 - 1] = stbi__div4(t1 + 2);

	STBI_NOTUSED(hs);

	return out;
}
#endif

static stbi_uc *stbi__resample_row_generic(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs)
{
	// resample with nearest-neighbor
	int i, j;
	STBI_NOTUSED(in_far);
	for (i = 0; i < w; ++i)
		for (j = 0; j < hs; ++j)
			out[i*hs + j] = in_near[i];
	return out;
}

#ifdef STBI_JPEG_OLD
// this is the same YCbCr-to-RGB calculation that stb_image has used
// historically before the algorithm changes in 1.49
#define float2fixed(x)  ((int) ((x) * 65536 + 0.5))
static void stbi__YCbCr_to_RGB_row(stbi_uc *out, const stbi_uc *y, const stbi_uc *pcb, const stbi_uc *pcr, int count, int step)
{
	int i;
	for (i = 0; i < count; ++i) {
		int y_fixed = (y[i] << 16) + 32768; // rounding
		int r, g, b;
		int cr = pcr[i] - 128;
		int cb = pcb[i] - 128;
		r = y_fixed + cr*float2fixed(1.40200f);
		g = y_fixed - cr*float2fixed(0.71414f) - cb*float2fixed(0.34414f);
		b = y_fixed + cb*float2fixed(1.77200f);
		r >>= 16;
		g >>= 16;
		b >>= 16;
		if ((unsigned)r > 255) { if (r < 0) r = 0; else r = 255; }
		if ((unsigned)g > 255) { if (g < 0) g = 0; else g = 255; }
		if ((unsigned)b > 255) { if (b < 0) b = 0; else b = 255; }
		out[0] = (stbi_uc)r;
		out[1] = (stbi_uc)g;
		out[2] = (stbi_uc)b;
		out[3] = 255;
		out += step;
	}
}
#else
// this is a reduced-precision calculation of YCbCr-to-RGB introduced
// to make sure the code produces the same results in both SIMD and scalar
#define float2fixed(x)  (((int) ((x) * 4096.0f + 0.5f)) << 8)
static void stbi__YCbCr_to_RGB_row(stbi_uc *out, const stbi_uc *y, const stbi_uc *pcb, const stbi_uc *pcr, int count, int step)
{
	int i;
	for (i = 0; i < count; ++i) {
		int y_fixed = (y[i] << 20) + (1 << 19); // rounding
		int r, g, b;
		int cr = pcr[i] - 128;
		int cb = pcb[i] - 128;
		r = y_fixed + cr* float2fixed(1.40200f);
		g = y_fixed + (cr*-float2fixed(0.71414f)) + ((cb*-float2fixed(0.34414f)) & 0xffff0000);
		b = y_fixed + cb* float2fixed(1.77200f);
		r >>= 20;
		g >>= 20;
		b >>= 20;
		if ((unsigned)r > 255) { if (r < 0) r = 0; else r = 255; }
		if ((unsigned)g > 255) { if (g < 0) g = 0; else g = 255; }
		if ((unsigned)b > 255) { if (b < 0) b = 0; else b = 255; }
		out[0] = (stbi_uc)r;
		out[1] = (stbi_uc)g;
		out[2] = (stbi_uc)b;
		out[3] = 255;
		out += step;
	}
}
#endif

#if defined(STBI_SSE2) || defined(STBI_NEON)
static void stbi__YCbCr_to_RGB_simd(stbi_uc *out, stbi_uc const *y, stbi_uc const *pcb, stbi_uc const *pcr, int count, int step)
{
	int i = 0;

#ifdef STBI_SSE2
	// step == 3 is pretty ugly on the final interleave, and i'm not convinced
	// it's useful in practice (you wouldn't use it for textures, for example).
	// so just accelerate step == 4 case.
	if (step == 4) {
		// this is a fairly straightforward implementation and not super-optimized.
		__m128i signflip = _mm_set1_epi8(-0x80);
		__m128i cr_const0 = _mm_set1_epi16((short)(1.40200f*4096.0f + 0.5f));
		__m128i cr_const1 = _mm_set1_epi16(-(short)(0.71414f*4096.0f + 0.5f));
		__m128i cb_const0 = _mm_set1_epi16(-(short)(0.34414f*4096.0f + 0.5f));
		__m128i cb_const1 = _mm_set1_epi16((short)(1.77200f*4096.0f + 0.5f));
		__m128i y_bias = _mm_set1_epi8((char)(unsigned char)128);
		__m128i xw = _mm_set1_epi16(255); // alpha channel

		for (; i + 7 < count; i += 8) {
			// load
			__m128i y_bytes = _mm_loadl_epi64((__m128i *) (y + i));
			__m128i cr_bytes = _mm_loadl_epi64((__m128i *) (pcr + i));
			__m128i cb_bytes = _mm_loadl_epi64((__m128i *) (pcb + i));
			__m128i cr_biased = _mm_xor_si128(cr_bytes, signflip); // -128
			__m128i cb_biased = _mm_xor_si128(cb_bytes, signflip); // -128

			// unpack to short (and left-shift cr, cb by 8)
			__m128i yw = _mm_unpacklo_epi8(y_bias, y_bytes);
			__m128i crw = _mm_unpacklo_epi8(_mm_setzero_si128(), cr_biased);
			__m128i cbw = _mm_unpacklo_epi8(_mm_setzero_si128(), cb_biased);

			// color transform
			__m128i yws = _mm_srli_epi16(yw, 4);
			__m128i cr0 = _mm_mulhi_epi16(cr_const0, crw);
			__m128i cb0 = _mm_mulhi_epi16(cb_const0, cbw);
			__m128i cb1 = _mm_mulhi_epi16(cbw, cb_const1);
			__m128i cr1 = _mm_mulhi_epi16(crw, cr_const1);
			__m128i rws = _mm_add_epi16(cr0, yws);
			__m128i gwt = _mm_add_epi16(cb0, yws);
			__m128i bws = _mm_add_epi16(yws, cb1);
			__m128i gws = _mm_add_epi16(gwt, cr1);

			// descale
			__m128i rw = _mm_srai_epi16(rws, 4);
			__m128i bw = _mm_srai_epi16(bws, 4);
			__m128i gw = _mm_srai_epi16(gws, 4);

			// back to byte, set up for transpose
			__m128i brb = _mm_packus_epi16(rw, bw);
			__m128i gxb = _mm_packus_epi16(gw, xw);

			// transpose to interleave channels
			__m128i t0 = _mm_unpacklo_epi8(brb, gxb);
			__m128i t1 = _mm_unpackhi_epi8(brb, gxb);
			__m128i o0 = _mm_unpacklo_epi16(t0, t1);
			__m128i o1 = _mm_unpackhi_epi16(t0, t1);

			// store
			_mm_storeu_si128((__m128i *) (out + 0), o0);
			_mm_storeu_si128((__m128i *) (out + 16), o1);
			out += 32;
		}
	}
#endif

#ifdef STBI_NEON
	// in this version, step=3 support would be easy to add. but is there demand?
	if (step == 4) {
		// this is a fairly straightforward implementation and not super-optimized.
		uint8x8_t signflip = vdup_n_u8(0x80);
		int16x8_t cr_const0 = vdupq_n_s16((short)(1.40200f*4096.0f + 0.5f));
		int16x8_t cr_const1 = vdupq_n_s16(-(short)(0.71414f*4096.0f + 0.5f));
		int16x8_t cb_const0 = vdupq_n_s16(-(short)(0.34414f*4096.0f + 0.5f));
		int16x8_t cb_const1 = vdupq_n_s16((short)(1.77200f*4096.0f + 0.5f));

		for (; i + 7 < count; i += 8) {
			// load
			uint8x8_t y_bytes = vld1_u8(y + i);
			uint8x8_t cr_bytes = vld1_u8(pcr + i);
			uint8x8_t cb_bytes = vld1_u8(pcb + i);
			int8x8_t cr_biased = vreinterpret_s8_u8(vsub_u8(cr_bytes, signflip));
			int8x8_t cb_biased = vreinterpret_s8_u8(vsub_u8(cb_bytes, signflip));

			// expand to s16
			int16x8_t yws = vreinterpretq_s16_u16(vshll_n_u8(y_bytes, 4));
			int16x8_t crw = vshll_n_s8(cr_biased, 7);
			int16x8_t cbw = vshll_n_s8(cb_biased, 7);

			// color transform
			int16x8_t cr0 = vqdmulhq_s16(crw, cr_const0);
			int16x8_t cb0 = vqdmulhq_s16(cbw, cb_const0);
			int16x8_t cr1 = vqdmulhq_s16(crw, cr_const1);
			int16x8_t cb1 = vqdmulhq_s16(cbw, cb_const1);
			int16x8_t rws = vaddq_s16(yws, cr0);
			int16x8_t gws = vaddq_s16(vaddq_s16(yws, cb0), cr1);
			int16x8_t bws = vaddq_s16(yws, cb1);

			// undo scaling, round, convert to byte
			uint8x8x4_t o;
			o.val[0] = vqrshrun_n_s16(rws, 4);
			o.val[1] = vqrshrun_n_s16(gws, 4);
			o.val[2] = vqrshrun_n_s16(bws, 4);
			o.val[3] = vdup_n_u8(255);

			// store, interleaving r/g/b/a
			vst4_u8(out, o);
			out += 8 * 4;
		}
	}
#endif

	for (; i < count; ++i) {
		int y_fixed = (y[i] << 20) + (1 << 19); // rounding
		int r, g, b;
		int cr = pcr[i] - 128;
		int cb = pcb[i] - 128;
		r = y_fixed + cr* float2fixed(1.40200f);
		g = y_fixed + cr*-float2fixed(0.71414f) + ((cb*-float2fixed(0.34414f)) & 0xffff0000);
		b = y_fixed + cb* float2fixed(1.77200f);
		r >>= 20;
		g >>= 20;
		b >>= 20;
		if ((unsigned)r > 255) { if (r < 0) r = 0; else r = 255; }
		if ((unsigned)g > 255) { if (g < 0) g = 0; else g = 255; }
		if ((unsigned)b > 255) { if (b < 0) b = 0; else b = 255; }
		out[0] = (stbi_uc)r;
		out[1] = (stbi_uc)g;
		out[2] = (stbi_uc)b;
		out[3] = 255;
		out += step;
	}
}
#endif

// set up the kernels
static void stbi__setup_jpeg(stbi__jpeg *j)
{
	j->idct_block_kernel = stbi__idct_block;
	j->YCbCr_to_RGB_kernel = stbi__YCbCr_to_RGB_row;
	j->resample_row_hv_2_kernel = stbi__resample_row_hv_2;

#ifdef STBI_SSE2
	if (stbi__sse2_available()) {
		j->idct_block_kernel = stbi__idct_simd;
#ifndef STBI_JPEG_OLD
		j->YCbCr_to_RGB_kernel = stbi__YCbCr_to_RGB_simd;
#endif
		j->resample_row_hv_2_kernel = stbi__resample_row_hv_2_simd;
	}
#endif

#ifdef STBI_NEON
	j->idct_block_kernel = stbi__idct_simd;
#ifndef STBI_JPEG_OLD
	j->YCbCr_to_RGB_kernel = stbi__YCbCr_to_RGB_simd;
#endif
	j->resample_row_hv_2_kernel = stbi__resample_row_hv_2_simd;
#endif
}

// clean up the temporary component buffers
static void stbi__cleanup_jpeg(stbi__jpeg *j)
{
	int i;
	for (i = 0; i < j->s->img_n; ++i) {
		if (j->img_comp[i].raw_data) {
			STBI_FREE(j->img_comp[i].raw_data);
			j->img_comp[i].raw_data = NULL;
			j->img_comp[i].data = NULL;
		}
		if (j->img_comp[i].raw_coeff) {
			STBI_FREE(j->img_comp[i].raw_coeff);
			j->img_comp[i].raw_coeff = 0;
			j->img_comp[i].coeff = 0;
		}
		if (j->img_comp[i].linebuf) {
			STBI_FREE(j->img_comp[i].linebuf);
			j->img_comp[i].linebuf = NULL;
		}
	}
}

typedef struct
{
	resample_row_func resample;
	stbi_uc *line0, *line1;
	int hs, vs;   // expansion factor in each axis
	int w_lores; // horizontal pixels pre-expansion
	int ystep;   // how far through vertical expansion we are
	int ypos;    // which pre-expansion row we're on
} stbi__resample;

static stbi_uc *load_jpeg_image(stbi__jpeg *z, int *out_x, int *out_y, int *comp, int req_comp)
{
	int n, decode_n;
	z->s->img_n = 0; // make stbi__cleanup_jpeg safe

	// validate req_comp
	if (req_comp < 0 || req_comp > 4) return stbi__errpuc("bad req_comp", "Internal error");

	// load a jpeg image from whichever source, but leave in YCbCr format
	if (!stbi__decode_jpeg_image(z)) { stbi__cleanup_jpeg(z); return NULL; }

	// determine actual number of components to generate
	n = req_comp ? req_comp : z->s->img_n;

	if (z->s->img_n == 3 && n < 3)
		decode_n = 1;
	else
		decode_n = z->s->img_n;

	// resample and color-convert
	{
		int k;
		unsigned int i, j;
		stbi_uc *output;
		stbi_uc *coutput[4];

		stbi__resample res_comp[4];

		for (k = 0; k < decode_n; ++k) {
			stbi__resample *r = &res_comp[k];

			// allocate line buffer big enough for upsampling off the edges
			// with upsample factor of 4
			z->img_comp[k].linebuf = (stbi_uc *)stbi__malloc(z->s->img_x + 3);
			if (!z->img_comp[k].linebuf) { stbi__cleanup_jpeg(z); return stbi__errpuc("outofmem", "Out of memory"); }

			r->hs = z->img_h_max / z->img_comp[k].h;
			r->vs = z->img_v_max / z->img_comp[k].v;
			r->ystep = r->vs >> 1;
			r->w_lores = (z->s->img_x + r->hs - 1) / r->hs;
			r->ypos = 0;
			r->line0 = r->line1 = z->img_comp[k].data;

			if (r->hs == 1 && r->vs == 1) r->resample = resample_row_1;
			else if (r->hs == 1 && r->vs == 2) r->resample = stbi__resample_row_v_2;
			else if (r->hs == 2 && r->vs == 1) r->resample = stbi__resample_row_h_2;
			else if (r->hs == 2 && r->vs == 2) r->resample = z->resample_row_hv_2_kernel;
			else                               r->resample = stbi__resample_row_generic;
		}

		// can't error after this so, this is safe
		output = (stbi_uc *)stbi__malloc(n * z->s->img_x * z->s->img_y + 1);
		if (!output) { stbi__cleanup_jpeg(z); return stbi__errpuc("outofmem", "Out of memory"); }

		// now go ahead and resample
		for (j = 0; j < z->s->img_y; ++j) {
			stbi_uc *out = output + n * z->s->img_x * j;
			for (k = 0; k < decode_n; ++k) {
				stbi__resample *r = &res_comp[k];
				int y_bot = r->ystep >= (r->vs >> 1);
				coutput[k] = r->resample(z->img_comp[k].linebuf,
					y_bot ? r->line1 : r->line0,
					y_bot ? r->line0 : r->line1,
					r->w_lores, r->hs);
				if (++r->ystep >= r->vs) {
					r->ystep = 0;
					r->line0 = r->line1;
					if (++r->ypos < z->img_comp[k].y)
						r->line1 += z->img_comp[k].w2;
				}
			}
			if (n >= 3) {
				stbi_uc *y = coutput[0];
				if (z->s->img_n == 3) {
					if (z->rgb == 3) {
						for (i = 0; i < z->s->img_x; ++i) {
							out[0] = y[i];
							out[1] = coutput[1][i];
							out[2] = coutput[2][i];
							out[3] = 255;
							out += n;
						}
					}
					else {
						z->YCbCr_to_RGB_kernel(out, y, coutput[1], coutput[2], z->s->img_x, n);
					}
				}
				else
					for (i = 0; i < z->s->img_x; ++i) {
						out[0] = out[1] = out[2] = y[i];
						out[3] = 255; // not used if n==3
						out += n;
					}
			}
			else {
				stbi_uc *y = coutput[0];
				if (n == 1)
					for (i = 0; i < z->s->img_x; ++i) out[i] = y[i];
				else
					for (i = 0; i < z->s->img_x; ++i) *out++ = y[i], *out++ = 255;
			}
		}
		stbi__cleanup_jpeg(z);
		*out_x = z->s->img_x;
		*out_y = z->s->img_y;
		if (comp) *comp = z->s->img_n; // report original components, not output
		return output;
	}
}

static unsigned char *stbi__jpeg_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	unsigned char* result;
	stbi__jpeg* j = (stbi__jpeg*)stbi__malloc(sizeof(stbi__jpeg));
	j->s = s;
	stbi__setup_jpeg(j);
	result = load_jpeg_image(j, x, y, comp, req_comp);
	STBI_FREE(j);
	return result;
}

static int stbi__jpeg_test(stbi__context *s)
{
	int r;
	stbi__jpeg j;
	j.s = s;
	stbi__setup_jpeg(&j);
	r = stbi__decode_jpeg_header(&j, STBI__SCAN_type);
	stbi__rewind(s);
	return r;
}

static int stbi__jpeg_info_raw(stbi__jpeg *j, int *x, int *y, int *comp)
{
	if (!stbi__decode_jpeg_header(j, STBI__SCAN_header)) {
		stbi__rewind(j->s);
		return 0;
	}
	if (x) *x = j->s->img_x;
	if (y) *y = j->s->img_y;
	if (comp) *comp = j->s->img_n;
	return 1;
}

static int stbi__jpeg_info(stbi__context *s, int *x, int *y, int *comp)
{
	int result;
	stbi__jpeg* j = (stbi__jpeg*)(stbi__malloc(sizeof(stbi__jpeg)));
	j->s = s;
	result = stbi__jpeg_info_raw(j, x, y, comp);
	STBI_FREE(j);
	return result;
}
#endif

// public domain zlib decode    v0.2  Sean Barrett 2006-11-18
//    simple implementation
//      - all input must be provided in an upfront buffer
//      - all output is written to a single output buffer (can malloc/realloc)
//    performance
//      - fast huffman

#ifndef STBI_NO_ZLIB

// fast-way is faster to check than jpeg huffman, but slow way is slower
#define STBI__ZFAST_BITS  9 // accelerate all cases in default tables
#define STBI__ZFAST_MASK  ((1 << STBI__ZFAST_BITS) - 1)

// zlib-style huffman encoding
// (jpegs packs from left, zlib from right, so can't share code)
typedef struct
{
	stbi__uint16 fast[1 << STBI__ZFAST_BITS];
	stbi__uint16 firstcode[16];
	int maxcode[17];
	stbi__uint16 firstsymbol[16];
	stbi_uc  size[288];
	stbi__uint16 value[288];
} stbi__zhuffman;

stbi_inline static int stbi__bitreverse16(int n)
{
	n = ((n & 0xAAAA) >> 1) | ((n & 0x5555) << 1);
	n = ((n & 0xCCCC) >> 2) | ((n & 0x3333) << 2);
	n = ((n & 0xF0F0) >> 4) | ((n & 0x0F0F) << 4);
	n = ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
	return n;
}

stbi_inline static int stbi__bit_reverse(int v, int bits)
{
	STBI_ASSERT(bits <= 16);
	// to bit reverse n bits, reverse 16 and shift
	// e.g. 11 bits, bit reverse and shift away 5
	return stbi__bitreverse16(v) >> (16 - bits);
}

static int stbi__zbuild_huffman(stbi__zhuffman *z, stbi_uc *sizelist, int num)
{
	int i, k = 0;
	int code, next_code[16], sizes[17];

	// DEFLATE spec for generating codes
	memset(sizes, 0, sizeof(sizes));
	memset(z->fast, 0, sizeof(z->fast));
	for (i = 0; i < num; ++i)
		++sizes[sizelist[i]];
	sizes[0] = 0;
	for (i = 1; i < 16; ++i)
		if (sizes[i] >(1 << i))
			return stbi__err("bad sizes", "Corrupt PNG");
	code = 0;
	for (i = 1; i < 16; ++i) {
		next_code[i] = code;
		z->firstcode[i] = (stbi__uint16)code;
		z->firstsymbol[i] = (stbi__uint16)k;
		code = (code + sizes[i]);
		if (sizes[i])
			if (code - 1 >= (1 << i)) return stbi__err("bad codelengths", "Corrupt PNG");
		z->maxcode[i] = code << (16 - i); // preshift for inner loop
		code <<= 1;
		k += sizes[i];
	}
	z->maxcode[16] = 0x10000; // sentinel
	for (i = 0; i < num; ++i) {
		int s = sizelist[i];
		if (s) {
			int c = next_code[s] - z->firstcode[s] + z->firstsymbol[s];
			stbi__uint16 fastv = (stbi__uint16)((s << 9) | i);
			z->size[c] = (stbi_uc)s;
			z->value[c] = (stbi__uint16)i;
			if (s <= STBI__ZFAST_BITS) {
				int j = stbi__bit_reverse(next_code[s], s);
				while (j < (1 << STBI__ZFAST_BITS)) {
					z->fast[j] = fastv;
					j += (1 << s);
				}
			}
			++next_code[s];
		}
	}
	return 1;
}

// zlib-from-memory implementation for PNG reading
//    because PNG allows splitting the zlib stream arbitrarily,
//    and it's annoying structurally to have PNG call ZLIB call PNG,
//    we require PNG read all the IDATs and combine them into a single
//    memory buffer

typedef struct
{
	stbi_uc *zbuffer, *zbuffer_end;
	int num_bits;
	stbi__uint32 code_buffer;

	char *zout;
	char *zout_start;
	char *zout_end;
	int   z_expandable;

	stbi__zhuffman z_length, z_distance;
} stbi__zbuf;

stbi_inline static stbi_uc stbi__zget8(stbi__zbuf *z)
{
	if (z->zbuffer >= z->zbuffer_end) return 0;
	return *z->zbuffer++;
}

static void stbi__fill_bits(stbi__zbuf *z)
{
	do {
		STBI_ASSERT(z->code_buffer < (1U << z->num_bits));
		z->code_buffer |= (unsigned int)stbi__zget8(z) << z->num_bits;
		z->num_bits += 8;
	} while (z->num_bits <= 24);
}

stbi_inline static unsigned int stbi__zreceive(stbi__zbuf *z, int n)
{
	unsigned int k;
	if (z->num_bits < n) stbi__fill_bits(z);
	k = z->code_buffer & ((1 << n) - 1);
	z->code_buffer >>= n;
	z->num_bits -= n;
	return k;
}

static int stbi__zhuffman_decode_slowpath(stbi__zbuf *a, stbi__zhuffman *z)
{
	int b, s, k;
	// not resolved by fast table, so compute it the slow way
	// use jpeg approach, which requires MSbits at top
	k = stbi__bit_reverse(a->code_buffer, 16);
	for (s = STBI__ZFAST_BITS + 1;; ++s)
		if (k < z->maxcode[s])
			break;
	if (s == 16) return -1; // invalid code!
	// code size is s, so:
	b = (k >> (16 - s)) - z->firstcode[s] + z->firstsymbol[s];
	STBI_ASSERT(z->size[b] == s);
	a->code_buffer >>= s;
	a->num_bits -= s;
	return z->value[b];
}

stbi_inline static int stbi__zhuffman_decode(stbi__zbuf *a, stbi__zhuffman *z)
{
	int b, s;
	if (a->num_bits < 16) stbi__fill_bits(a);
	b = z->fast[a->code_buffer & STBI__ZFAST_MASK];
	if (b) {
		s = b >> 9;
		a->code_buffer >>= s;
		a->num_bits -= s;
		return b & 511;
	}
	return stbi__zhuffman_decode_slowpath(a, z);
}

static int stbi__zexpand(stbi__zbuf *z, char *zout, int n)  // need to make room for n bytes
{
	char *q;
	int cur, limit, old_limit;
	z->zout = zout;
	if (!z->z_expandable) return stbi__err("output buffer limit", "Corrupt PNG");
	cur = (int)(z->zout - z->zout_start);
	limit = old_limit = (int)(z->zout_end - z->zout_start);
	while (cur + n > limit)
		limit *= 2;
	q = (char *)STBI_REALLOC_SIZED(z->zout_start, old_limit, limit);
	STBI_NOTUSED(old_limit);
	if (q == NULL) return stbi__err("outofmem", "Out of memory");
	z->zout_start = q;
	z->zout = q + cur;
	z->zout_end = q + limit;
	return 1;
}

static int stbi__zlength_base[31] = {
	3, 4, 5, 6, 7, 8, 9, 10, 11, 13,
	15, 17, 19, 23, 27, 31, 35, 43, 51, 59,
	67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0 };

static int stbi__zlength_extra[31] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0 };

static int stbi__zdist_base[32] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0 };

static int stbi__zdist_extra[32] =
{ 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };

static int stbi__parse_huffman_block(stbi__zbuf *a)
{
	char *zout = a->zout;
	for (;;) {
		int z = stbi__zhuffman_decode(a, &a->z_length);
		if (z < 256) {
			if (z < 0) return stbi__err("bad huffman code", "Corrupt PNG"); // error in huffman codes
			if (zout >= a->zout_end) {
				if (!stbi__zexpand(a, zout, 1)) return 0;
				zout = a->zout;
			}
			*zout++ = (char)z;
		}
		else {
			stbi_uc *p;
			int len, dist;
			if (z == 256) {
				a->zout = zout;
				return 1;
			}
			z -= 257;
			len = stbi__zlength_base[z];
			if (stbi__zlength_extra[z]) len += stbi__zreceive(a, stbi__zlength_extra[z]);
			z = stbi__zhuffman_decode(a, &a->z_distance);
			if (z < 0) return stbi__err("bad huffman code", "Corrupt PNG");
			dist = stbi__zdist_base[z];
			if (stbi__zdist_extra[z]) dist += stbi__zreceive(a, stbi__zdist_extra[z]);
			if (zout - a->zout_start < dist) return stbi__err("bad dist", "Corrupt PNG");
			if (zout + len > a->zout_end) {
				if (!stbi__zexpand(a, zout, len)) return 0;
				zout = a->zout;
			}
			p = (stbi_uc *)(zout - dist);
			if (dist == 1) { // run of one byte; common in images.
				stbi_uc v = *p;
				if (len) { do *zout++ = v; while (--len); }
			}
			else {
				if (len) { do *zout++ = *p++; while (--len); }
			}
		}
	}
}

static int stbi__compute_huffman_codes(stbi__zbuf *a)
{
	static stbi_uc length_dezigzag[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	stbi__zhuffman z_codelength;
	stbi_uc lencodes[286 + 32 + 137];//padding for maximum single op
	stbi_uc codelength_sizes[19];
	int i, n;

	int hlit = stbi__zreceive(a, 5) + 257;
	int hdist = stbi__zreceive(a, 5) + 1;
	int hclen = stbi__zreceive(a, 4) + 4;

	memset(codelength_sizes, 0, sizeof(codelength_sizes));
	for (i = 0; i < hclen; ++i) {
		int s = stbi__zreceive(a, 3);
		codelength_sizes[length_dezigzag[i]] = (stbi_uc)s;
	}
	if (!stbi__zbuild_huffman(&z_codelength, codelength_sizes, 19)) return 0;

	n = 0;
	while (n < hlit + hdist) {
		int c = stbi__zhuffman_decode(a, &z_codelength);
		if (c < 0 || c >= 19) return stbi__err("bad codelengths", "Corrupt PNG");
		if (c < 16)
			lencodes[n++] = (stbi_uc)c;
		else if (c == 16) {
			c = stbi__zreceive(a, 2) + 3;
			memset(lencodes + n, lencodes[n - 1], c);
			n += c;
		}
		else if (c == 17) {
			c = stbi__zreceive(a, 3) + 3;
			memset(lencodes + n, 0, c);
			n += c;
		}
		else {
			STBI_ASSERT(c == 18);
			c = stbi__zreceive(a, 7) + 11;
			memset(lencodes + n, 0, c);
			n += c;
		}
	}
	if (n != hlit + hdist) return stbi__err("bad codelengths", "Corrupt PNG");
	if (!stbi__zbuild_huffman(&a->z_length, lencodes, hlit)) return 0;
	if (!stbi__zbuild_huffman(&a->z_distance, lencodes + hlit, hdist)) return 0;
	return 1;
}

static int stbi__parse_uncompressed_block(stbi__zbuf *a)
{
	stbi_uc header[4];
	int len, nlen, k;
	if (a->num_bits & 7)
		stbi__zreceive(a, a->num_bits & 7); // discard
	// drain the bit-packed data into header
	k = 0;
	while (a->num_bits > 0) {
		header[k++] = (stbi_uc)(a->code_buffer & 255); // suppress MSVC run-time check
		a->code_buffer >>= 8;
		a->num_bits -= 8;
	}
	STBI_ASSERT(a->num_bits == 0);
	// now fill header the normal way
	while (k < 4)
		header[k++] = stbi__zget8(a);
	len = header[1] * 256 + header[0];
	nlen = header[3] * 256 + header[2];
	if (nlen != (len ^ 0xffff)) return stbi__err("zlib corrupt", "Corrupt PNG");
	if (a->zbuffer + len > a->zbuffer_end) return stbi__err("read past buffer", "Corrupt PNG");
	if (a->zout + len > a->zout_end)
		if (!stbi__zexpand(a, a->zout, len)) return 0;
	memcpy(a->zout, a->zbuffer, len);
	a->zbuffer += len;
	a->zout += len;
	return 1;
}

static int stbi__parse_zlib_header(stbi__zbuf *a)
{
	int cmf = stbi__zget8(a);
	int cm = cmf & 15;
	/* int cinfo = cmf >> 4; */
	int flg = stbi__zget8(a);
	if ((cmf * 256 + flg) % 31 != 0) return stbi__err("bad zlib header", "Corrupt PNG"); // zlib spec
	if (flg & 32) return stbi__err("no preset dict", "Corrupt PNG"); // preset dictionary not allowed in png
	if (cm != 8) return stbi__err("bad compression", "Corrupt PNG"); // DEFLATE required for png
	// window = 1 << (8 + cinfo)... but who cares, we fully buffer output
	return 1;
}

// @TODO: should statically initialize these for optimal thread safety
static stbi_uc stbi__zdefault_length[288], stbi__zdefault_distance[32];
static void stbi__init_zdefaults(void)
{
	int i;   // use <= to match clearly with spec
	for (i = 0; i <= 143; ++i)     stbi__zdefault_length[i] = 8;
	for (; i <= 255; ++i)     stbi__zdefault_length[i] = 9;
	for (; i <= 279; ++i)     stbi__zdefault_length[i] = 7;
	for (; i <= 287; ++i)     stbi__zdefault_length[i] = 8;

	for (i = 0; i <= 31; ++i)     stbi__zdefault_distance[i] = 5;
}

static int stbi__parse_zlib(stbi__zbuf *a, int parse_header)
{
	int final, type;
	if (parse_header)
		if (!stbi__parse_zlib_header(a)) return 0;
	a->num_bits = 0;
	a->code_buffer = 0;
	do {
		final = stbi__zreceive(a, 1);
		type = stbi__zreceive(a, 2);
		if (type == 0) {
			if (!stbi__parse_uncompressed_block(a)) return 0;
		}
		else if (type == 3) {
			return 0;
		}
		else {
			if (type == 1) {
				// use fixed code lengths
				if (!stbi__zdefault_distance[31]) stbi__init_zdefaults();
				if (!stbi__zbuild_huffman(&a->z_length, stbi__zdefault_length, 288)) return 0;
				if (!stbi__zbuild_huffman(&a->z_distance, stbi__zdefault_distance, 32)) return 0;
			}
			else {
				if (!stbi__compute_huffman_codes(a)) return 0;
			}
			if (!stbi__parse_huffman_block(a)) return 0;
		}
	} while (!final);
	return 1;
}

static int stbi__do_zlib(stbi__zbuf *a, char *obuf, int olen, int exp, int parse_header)
{
	a->zout_start = obuf;
	a->zout = obuf;
	a->zout_end = obuf + olen;
	a->z_expandable = exp;

	return stbi__parse_zlib(a, parse_header);
}

STBIDEF char *stbi_zlib_decode_malloc_guesssize(const char *buffer, int len, int initial_size, int *outlen)
{
	stbi__zbuf a;
	char *p = (char *)stbi__malloc(initial_size);
	if (p == NULL) return NULL;
	a.zbuffer = (stbi_uc *)buffer;
	a.zbuffer_end = (stbi_uc *)buffer + len;
	if (stbi__do_zlib(&a, p, initial_size, 1, 1)) {
		if (outlen) *outlen = (int)(a.zout - a.zout_start);
		return a.zout_start;
	}
	else {
		STBI_FREE(a.zout_start);
		return NULL;
	}
}

STBIDEF char *stbi_zlib_decode_malloc(char const *buffer, int len, int *outlen)
{
	return stbi_zlib_decode_malloc_guesssize(buffer, len, 16384, outlen);
}

STBIDEF char *stbi_zlib_decode_malloc_guesssize_headerflag(const char *buffer, int len, int initial_size, int *outlen, int parse_header)
{
	stbi__zbuf a;
	char *p = (char *)stbi__malloc(initial_size);
	if (p == NULL) return NULL;
	a.zbuffer = (stbi_uc *)buffer;
	a.zbuffer_end = (stbi_uc *)buffer + len;
	if (stbi__do_zlib(&a, p, initial_size, 1, parse_header)) {
		if (outlen) *outlen = (int)(a.zout - a.zout_start);
		return a.zout_start;
	}
	else {
		STBI_FREE(a.zout_start);
		return NULL;
	}
}

STBIDEF int stbi_zlib_decode_buffer(char *obuffer, int olen, char const *ibuffer, int ilen)
{
	stbi__zbuf a;
	a.zbuffer = (stbi_uc *)ibuffer;
	a.zbuffer_end = (stbi_uc *)ibuffer + ilen;
	if (stbi__do_zlib(&a, obuffer, olen, 0, 1))
		return (int)(a.zout - a.zout_start);
	else
		return -1;
}

STBIDEF char *stbi_zlib_decode_noheader_malloc(char const *buffer, int len, int *outlen)
{
	stbi__zbuf a;
	char *p = (char *)stbi__malloc(16384);
	if (p == NULL) return NULL;
	a.zbuffer = (stbi_uc *)buffer;
	a.zbuffer_end = (stbi_uc *)buffer + len;
	if (stbi__do_zlib(&a, p, 16384, 1, 0)) {
		if (outlen) *outlen = (int)(a.zout - a.zout_start);
		return a.zout_start;
	}
	else {
		STBI_FREE(a.zout_start);
		return NULL;
	}
}

STBIDEF int stbi_zlib_decode_noheader_buffer(char *obuffer, int olen, const char *ibuffer, int ilen)
{
	stbi__zbuf a;
	a.zbuffer = (stbi_uc *)ibuffer;
	a.zbuffer_end = (stbi_uc *)ibuffer + ilen;
	if (stbi__do_zlib(&a, obuffer, olen, 0, 0))
		return (int)(a.zout - a.zout_start);
	else
		return -1;
}
#endif

// public domain "baseline" PNG decoder   v0.10  Sean Barrett 2006-11-18
//    simple implementation
//      - only 8-bit samples
//      - no CRC checking
//      - allocates lots of intermediate memory
//        - avoids problem of streaming data between subsystems
//        - avoids explicit window management
//    performance
//      - uses stb_zlib, a PD zlib implementation with fast huffman decoding

#ifndef STBI_NO_PNG
typedef struct
{
	stbi__uint32 length;
	stbi__uint32 type;
} stbi__pngchunk;

static stbi__pngchunk stbi__get_chunk_header(stbi__context *s)
{
	stbi__pngchunk c;
	c.length = stbi__get32be(s);
	c.type = stbi__get32be(s);
	return c;
}

static int stbi__check_png_header(stbi__context *s)
{
	static stbi_uc png_sig[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
	int i;
	for (i = 0; i < 8; ++i)
		if (stbi__get8(s) != png_sig[i]) return stbi__err("bad png sig", "Not a PNG");
	return 1;
}

typedef struct
{
	stbi__context *s;
	stbi_uc *idata, *expanded, *out;
	int depth;
} stbi__png;


enum {
	STBI__F_none = 0,
	STBI__F_sub = 1,
	STBI__F_up = 2,
	STBI__F_avg = 3,
	STBI__F_paeth = 4,
	// synthetic filters used for first scanline to avoid needing a dummy row of 0s
	STBI__F_avg_first,
	STBI__F_paeth_first
};

static stbi_uc first_row_filter[5] =
{
	STBI__F_none,
	STBI__F_sub,
	STBI__F_none,
	STBI__F_avg_first,
	STBI__F_paeth_first
};

static int stbi__paeth(int a, int b, int c)
{
	int p = a + b - c;
	int pa = abs(p - a);
	int pb = abs(p - b);
	int pc = abs(p - c);
	if (pa <= pb && pa <= pc) return a;
	if (pb <= pc) return b;
	return c;
}

static stbi_uc stbi__depth_scale_table[9] = { 0, 0xff, 0x55, 0, 0x11, 0, 0, 0, 0x01 };

// create the png data from post-deflated data
static int stbi__create_png_image_raw(stbi__png *a, stbi_uc *raw, stbi__uint32 raw_len, int out_n, stbi__uint32 x, stbi__uint32 y, int depth, int color)
{
	int bytes = (depth == 16 ? 2 : 1);
	stbi__context *s = a->s;
	stbi__uint32 i, j, stride = x*out_n*bytes;
	stbi__uint32 img_len, img_width_bytes;
	int k;
	int img_n = s->img_n; // copy it into a local for later

	int output_bytes = out_n*bytes;
	int filter_bytes = img_n*bytes;
	int width = x;

	STBI_ASSERT(out_n == s->img_n || out_n == s->img_n + 1);
	a->out = (stbi_uc *)stbi__malloc(x * y * output_bytes); // extra bytes to write off the end into
	if (!a->out) return stbi__err("outofmem", "Out of memory");

	img_width_bytes = (((img_n * x * depth) + 7) >> 3);
	img_len = (img_width_bytes + 1) * y;
	if (s->img_x == x && s->img_y == y) {
		if (raw_len != img_len) return stbi__err("not enough pixels", "Corrupt PNG");
	}
	else { // interlaced:
		if (raw_len < img_len) return stbi__err("not enough pixels", "Corrupt PNG");
	}

	for (j = 0; j < y; ++j) {
		stbi_uc *cur = a->out + stride*j;
		stbi_uc *prior = cur - stride;
		int filter = *raw++;

		if (filter > 4)
			return stbi__err("invalid filter", "Corrupt PNG");

		if (depth < 8) {
			STBI_ASSERT(img_width_bytes <= x);
			cur += x*out_n - img_width_bytes; // store output to the rightmost img_len bytes, so we can decode in place
			filter_bytes = 1;
			width = img_width_bytes;
		}

		// if first row, use special filter that doesn't sample previous row
		if (j == 0) filter = first_row_filter[filter];

		// handle first byte explicitly
		for (k = 0; k < filter_bytes; ++k) {
			switch (filter) {
			case STBI__F_none: cur[k] = raw[k]; break;
			case STBI__F_sub: cur[k] = raw[k]; break;
			case STBI__F_up: cur[k] = STBI__BYTECAST(raw[k] + prior[k]); break;
			case STBI__F_avg: cur[k] = STBI__BYTECAST(raw[k] + (prior[k] >> 1)); break;
			case STBI__F_paeth: cur[k] = STBI__BYTECAST(raw[k] + stbi__paeth(0, prior[k], 0)); break;
			case STBI__F_avg_first: cur[k] = raw[k]; break;
			case STBI__F_paeth_first: cur[k] = raw[k]; break;
			}
		}

		if (depth == 8) {
			if (img_n != out_n)
				cur[img_n] = 255; // first pixel
			raw += img_n;
			cur += out_n;
			prior += out_n;
		}
		else if (depth == 16) {
			if (img_n != out_n) {
				cur[filter_bytes] = 255; // first pixel top byte
				cur[filter_bytes + 1] = 255; // first pixel bottom byte
			}
			raw += filter_bytes;
			cur += output_bytes;
			prior += output_bytes;
		}
		else {
			raw += 1;
			cur += 1;
			prior += 1;
		}

		// this is a little gross, so that we don't switch per-pixel or per-component
		if (depth < 8 || img_n == out_n) {
			int nk = (width - 1)*filter_bytes;
#define CASE(f) \
             case f:     \
                for (k=0; k < nk; ++k)
			switch (filter) {
				// "none" filter turns into a memcpy here; make that explicit.
			case STBI__F_none:         memcpy(cur, raw, nk); break;
				CASE(STBI__F_sub)          cur[k] = STBI__BYTECAST(raw[k] + cur[k - filter_bytes]); break;
				CASE(STBI__F_up)           cur[k] = STBI__BYTECAST(raw[k] + prior[k]); break;
				CASE(STBI__F_avg)          cur[k] = STBI__BYTECAST(raw[k] + ((prior[k] + cur[k - filter_bytes]) >> 1)); break;
				CASE(STBI__F_paeth)        cur[k] = STBI__BYTECAST(raw[k] + stbi__paeth(cur[k - filter_bytes], prior[k], prior[k - filter_bytes])); break;
				CASE(STBI__F_avg_first)    cur[k] = STBI__BYTECAST(raw[k] + (cur[k - filter_bytes] >> 1)); break;
				CASE(STBI__F_paeth_first)  cur[k] = STBI__BYTECAST(raw[k] + stbi__paeth(cur[k - filter_bytes], 0, 0)); break;
			}
#undef CASE
			raw += nk;
		}
		else {
			STBI_ASSERT(img_n + 1 == out_n);
#define CASE(f) \
             case f:     \
                for (i=x-1; i >= 1; --i, cur[filter_bytes]=255,raw+=filter_bytes,cur+=output_bytes,prior+=output_bytes) \
                   for (k=0; k < filter_bytes; ++k)
			switch (filter) {
				CASE(STBI__F_none)         cur[k] = raw[k]; break;
				CASE(STBI__F_sub)          cur[k] = STBI__BYTECAST(raw[k] + cur[k - output_bytes]); break;
				CASE(STBI__F_up)           cur[k] = STBI__BYTECAST(raw[k] + prior[k]); break;
				CASE(STBI__F_avg)          cur[k] = STBI__BYTECAST(raw[k] + ((prior[k] + cur[k - output_bytes]) >> 1)); break;
				CASE(STBI__F_paeth)        cur[k] = STBI__BYTECAST(raw[k] + stbi__paeth(cur[k - output_bytes], prior[k], prior[k - output_bytes])); break;
				CASE(STBI__F_avg_first)    cur[k] = STBI__BYTECAST(raw[k] + (cur[k - output_bytes] >> 1)); break;
				CASE(STBI__F_paeth_first)  cur[k] = STBI__BYTECAST(raw[k] + stbi__paeth(cur[k - output_bytes], 0, 0)); break;
			}
#undef CASE

			// the loop above sets the high byte of the pixels' alpha, but for
			// 16 bit png files we also need the low byte set. we'll do that here.
			if (depth == 16) {
				cur = a->out + stride*j; // start at the beginning of the row again
				for (i = 0; i < x; ++i, cur += output_bytes) {
					cur[filter_bytes + 1] = 255;
				}
			}
		}
	}

	// we make a separate pass to expand bits to pixels; for performance,
	// this could run two scanlines behind the above code, so it won't
	// intefere with filtering but will still be in the cache.
	if (depth < 8) {
		for (j = 0; j < y; ++j) {
			stbi_uc *cur = a->out + stride*j;
			stbi_uc *in = a->out + stride*j + x*out_n - img_width_bytes;
			// unpack 1/2/4-bit into a 8-bit buffer. allows us to keep the common 8-bit path optimal at minimal cost for 1/2/4-bit
			// png guarante byte alignment, if width is not multiple of 8/4/2 we'll decode dummy trailing data that will be skipped in the later loop
			stbi_uc scale = (color == 0) ? stbi__depth_scale_table[depth] : 1; // scale grayscale values to 0..255 range

			// note that the final byte might overshoot and write more data than desired.
			// we can allocate enough data that this never writes out of memory, but it
			// could also overwrite the next scanline. can it overwrite non-empty data
			// on the next scanline? yes, consider 1-pixel-wide scanlines with 1-bit-per-pixel.
			// so we need to explicitly clamp the final ones

			if (depth == 4) {
				for (k = x*img_n; k >= 2; k -= 2, ++in) {
					*cur++ = scale * ((*in >> 4));
					*cur++ = scale * ((*in) & 0x0f);
				}
				if (k > 0) *cur++ = scale * ((*in >> 4));
			}
			else if (depth == 2) {
				for (k = x*img_n; k >= 4; k -= 4, ++in) {
					*cur++ = scale * ((*in >> 6));
					*cur++ = scale * ((*in >> 4) & 0x03);
					*cur++ = scale * ((*in >> 2) & 0x03);
					*cur++ = scale * ((*in) & 0x03);
				}
				if (k > 0) *cur++ = scale * ((*in >> 6));
				if (k > 1) *cur++ = scale * ((*in >> 4) & 0x03);
				if (k > 2) *cur++ = scale * ((*in >> 2) & 0x03);
			}
			else if (depth == 1) {
				for (k = x*img_n; k >= 8; k -= 8, ++in) {
					*cur++ = scale * ((*in >> 7));
					*cur++ = scale * ((*in >> 6) & 0x01);
					*cur++ = scale * ((*in >> 5) & 0x01);
					*cur++ = scale * ((*in >> 4) & 0x01);
					*cur++ = scale * ((*in >> 3) & 0x01);
					*cur++ = scale * ((*in >> 2) & 0x01);
					*cur++ = scale * ((*in >> 1) & 0x01);
					*cur++ = scale * ((*in) & 0x01);
				}
				if (k > 0) *cur++ = scale * ((*in >> 7));
				if (k > 1) *cur++ = scale * ((*in >> 6) & 0x01);
				if (k > 2) *cur++ = scale * ((*in >> 5) & 0x01);
				if (k > 3) *cur++ = scale * ((*in >> 4) & 0x01);
				if (k > 4) *cur++ = scale * ((*in >> 3) & 0x01);
				if (k > 5) *cur++ = scale * ((*in >> 2) & 0x01);
				if (k > 6) *cur++ = scale * ((*in >> 1) & 0x01);
			}
			if (img_n != out_n) {
				int q;
				// insert alpha = 255
				cur = a->out + stride*j;
				if (img_n == 1) {
					for (q = x - 1; q >= 0; --q) {
						cur[q * 2 + 1] = 255;
						cur[q * 2 + 0] = cur[q];
					}
				}
				else {
					STBI_ASSERT(img_n == 3);
					for (q = x - 1; q >= 0; --q) {
						cur[q * 4 + 3] = 255;
						cur[q * 4 + 2] = cur[q * 3 + 2];
						cur[q * 4 + 1] = cur[q * 3 + 1];
						cur[q * 4 + 0] = cur[q * 3 + 0];
					}
				}
			}
		}
	}
	else if (depth == 16) {
		// force the image data from big-endian to platform-native.
		// this is done in a separate pass due to the decoding relying
		// on the data being untouched, but could probably be done
		// per-line during decode if care is taken.
		stbi_uc *cur = a->out;
		stbi__uint16 *cur16 = (stbi__uint16*)cur;

		for (i = 0; i < x*y*out_n; ++i, cur16++, cur += 2) {
			*cur16 = (cur[0] << 8) | cur[1];
		}
	}

	return 1;
}

static int stbi__create_png_image(stbi__png *a, stbi_uc *image_data, stbi__uint32 image_data_len, int out_n, int depth, int color, int interlaced)
{
	stbi_uc *final;
	int p;
	if (!interlaced)
		return stbi__create_png_image_raw(a, image_data, image_data_len, out_n, a->s->img_x, a->s->img_y, depth, color);

	// de-interlacing
	final = (stbi_uc *)stbi__malloc(a->s->img_x * a->s->img_y * out_n);
	for (p = 0; p < 7; ++p) {
		int xorig[] = { 0, 4, 0, 2, 0, 1, 0 };
		int yorig[] = { 0, 0, 4, 0, 2, 0, 1 };
		int xspc[] = { 8, 8, 4, 4, 2, 2, 1 };
		int yspc[] = { 8, 8, 8, 4, 4, 2, 2 };
		int i, j, x, y;
		// pass1_x[4] = 0, pass1_x[5] = 1, pass1_x[12] = 1
		x = (a->s->img_x - xorig[p] + xspc[p] - 1) / xspc[p];
		y = (a->s->img_y - yorig[p] + yspc[p] - 1) / yspc[p];
		if (x && y) {
			stbi__uint32 img_len = ((((a->s->img_n * x * depth) + 7) >> 3) + 1) * y;
			if (!stbi__create_png_image_raw(a, image_data, image_data_len, out_n, x, y, depth, color)) {
				STBI_FREE(final);
				return 0;
			}
			for (j = 0; j < y; ++j) {
				for (i = 0; i < x; ++i) {
					int out_y = j*yspc[p] + yorig[p];
					int out_x = i*xspc[p] + xorig[p];
					memcpy(final + out_y*a->s->img_x*out_n + out_x*out_n,
						a->out + (j*x + i)*out_n, out_n);
				}
			}
			STBI_FREE(a->out);
			image_data += img_len;
			image_data_len -= img_len;
		}
	}
	a->out = final;

	return 1;
}

static int stbi__compute_transparency(stbi__png *z, stbi_uc tc[3], int out_n)
{
	stbi__context *s = z->s;
	stbi__uint32 i, pixel_count = s->img_x * s->img_y;
	stbi_uc *p = z->out;

	// compute color-based transparency, assuming we've
	// already got 255 as the alpha value in the output
	STBI_ASSERT(out_n == 2 || out_n == 4);

	if (out_n == 2) {
		for (i = 0; i < pixel_count; ++i) {
			p[1] = (p[0] == tc[0] ? 0 : 255);
			p += 2;
		}
	}
	else {
		for (i = 0; i < pixel_count; ++i) {
			if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2])
				p[3] = 0;
			p += 4;
		}
	}
	return 1;
}

static int stbi__compute_transparency16(stbi__png *z, stbi__uint16 tc[3], int out_n)
{
	stbi__context *s = z->s;
	stbi__uint32 i, pixel_count = s->img_x * s->img_y;
	stbi__uint16 *p = (stbi__uint16*)z->out;

	// compute color-based transparency, assuming we've
	// already got 65535 as the alpha value in the output
	STBI_ASSERT(out_n == 2 || out_n == 4);

	if (out_n == 2) {
		for (i = 0; i < pixel_count; ++i) {
			p[1] = (p[0] == tc[0] ? 0 : 65535);
			p += 2;
		}
	}
	else {
		for (i = 0; i < pixel_count; ++i) {
			if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2])
				p[3] = 0;
			p += 4;
		}
	}
	return 1;
}

static int stbi__expand_png_palette(stbi__png *a, stbi_uc *palette, int len, int pal_img_n)
{
	stbi__uint32 i, pixel_count = a->s->img_x * a->s->img_y;
	stbi_uc *p, *temp_out, *orig = a->out;

	p = (stbi_uc *)stbi__malloc(pixel_count * pal_img_n);
	if (p == NULL) return stbi__err("outofmem", "Out of memory");

	// between here and free(out) below, exitting would leak
	temp_out = p;

	if (pal_img_n == 3) {
		for (i = 0; i < pixel_count; ++i) {
			int n = orig[i] * 4;
			p[0] = palette[n];
			p[1] = palette[n + 1];
			p[2] = palette[n + 2];
			p += 3;
		}
	}
	else {
		for (i = 0; i < pixel_count; ++i) {
			int n = orig[i] * 4;
			p[0] = palette[n];
			p[1] = palette[n + 1];
			p[2] = palette[n + 2];
			p[3] = palette[n + 3];
			p += 4;
		}
	}
	STBI_FREE(a->out);
	a->out = temp_out;

	STBI_NOTUSED(len);

	return 1;
}

static int stbi__reduce_png(stbi__png *p)
{
	int i;
	int img_len = p->s->img_x * p->s->img_y * p->s->img_out_n;
	stbi_uc *reduced;
	stbi__uint16 *orig = (stbi__uint16*)p->out;

	if (p->depth != 16) return 1; // don't need to do anything if not 16-bit data

	reduced = (stbi_uc *)stbi__malloc(img_len);
	if (p == NULL) return stbi__err("outofmem", "Out of memory");

	for (i = 0; i < img_len; ++i) reduced[i] = (stbi_uc)((orig[i] >> 8) & 0xFF); // top half of each byte is a decent approx of 16->8 bit scaling

	p->out = reduced;
	STBI_FREE(orig);

	return 1;
}

static int stbi__unpremultiply_on_load = 0;
static int stbi__de_iphone_flag = 0;

STBIDEF void stbi_set_unpremultiply_on_load(int flag_true_if_should_unpremultiply)
{
	stbi__unpremultiply_on_load = flag_true_if_should_unpremultiply;
}

STBIDEF void stbi_convert_iphone_png_to_rgb(int flag_true_if_should_convert)
{
	stbi__de_iphone_flag = flag_true_if_should_convert;
}

static void stbi__de_iphone(stbi__png *z)
{
	stbi__context *s = z->s;
	stbi__uint32 i, pixel_count = s->img_x * s->img_y;
	stbi_uc *p = z->out;

	if (s->img_out_n == 3) {  // convert bgr to rgb
		for (i = 0; i < pixel_count; ++i) {
			stbi_uc t = p[0];
			p[0] = p[2];
			p[2] = t;
			p += 3;
		}
	}
	else {
		STBI_ASSERT(s->img_out_n == 4);
		if (stbi__unpremultiply_on_load) {
			// convert bgr to rgb and unpremultiply
			for (i = 0; i < pixel_count; ++i) {
				stbi_uc a = p[3];
				stbi_uc t = p[0];
				if (a) {
					p[0] = p[2] * 255 / a;
					p[1] = p[1] * 255 / a;
					p[2] = t * 255 / a;
				}
				else {
					p[0] = p[2];
					p[2] = t;
				}
				p += 4;
			}
		}
		else {
			// convert bgr to rgb
			for (i = 0; i < pixel_count; ++i) {
				stbi_uc t = p[0];
				p[0] = p[2];
				p[2] = t;
				p += 4;
			}
		}
	}
}

#define STBI__PNG_TYPE(a,b,c,d)  (((a) << 24) + ((b) << 16) + ((c) << 8) + (d))

static int stbi__parse_png_file(stbi__png *z, int scan, int req_comp)
{
	stbi_uc palette[1024], pal_img_n = 0;
	stbi_uc has_trans = 0, tc[3];
	stbi__uint16 tc16[3];
	stbi__uint32 ioff = 0, idata_limit = 0, i, pal_len = 0;
	int first = 1, k, interlace = 0, color = 0, is_iphone = 0;
	stbi__context *s = z->s;

	z->expanded = NULL;
	z->idata = NULL;
	z->out = NULL;

	if (!stbi__check_png_header(s)) return 0;

	if (scan == STBI__SCAN_type) return 1;

	for (;;) {
		stbi__pngchunk c = stbi__get_chunk_header(s);
		switch (c.type) {
		case STBI__PNG_TYPE('C', 'g', 'B', 'I'):
			is_iphone = 1;
			stbi__skip(s, c.length);
			break;
		case STBI__PNG_TYPE('I', 'H', 'D', 'R'): {
			int comp, filter;
			if (!first) return stbi__err("multiple IHDR", "Corrupt PNG");
			first = 0;
			if (c.length != 13) return stbi__err("bad IHDR len", "Corrupt PNG");
			s->img_x = stbi__get32be(s); if (s->img_x > (1 << 24)) return stbi__err("too large", "Very large image (corrupt?)");
			s->img_y = stbi__get32be(s); if (s->img_y > (1 << 24)) return stbi__err("too large", "Very large image (corrupt?)");
			z->depth = stbi__get8(s);  if (z->depth != 1 && z->depth != 2 && z->depth != 4 && z->depth != 8 && z->depth != 16)  return stbi__err("1/2/4/8/16-bit only", "PNG not supported: 1/2/4/8/16-bit only");
			color = stbi__get8(s);  if (color > 6)         return stbi__err("bad ctype", "Corrupt PNG");
			if (color == 3 && z->depth == 16)                  return stbi__err("bad ctype", "Corrupt PNG");
			if (color == 3) pal_img_n = 3; else if (color & 1) return stbi__err("bad ctype", "Corrupt PNG");
			comp = stbi__get8(s);  if (comp) return stbi__err("bad comp method", "Corrupt PNG");
			filter = stbi__get8(s);  if (filter) return stbi__err("bad filter method", "Corrupt PNG");
			interlace = stbi__get8(s); if (interlace>1) return stbi__err("bad interlace method", "Corrupt PNG");
			if (!s->img_x || !s->img_y) return stbi__err("0-pixel image", "Corrupt PNG");
			if (!pal_img_n) {
				s->img_n = (color & 2 ? 3 : 1) + (color & 4 ? 1 : 0);
				if ((1 << 30) / s->img_x / s->img_n < s->img_y) return stbi__err("too large", "Image too large to decode");
				if (scan == STBI__SCAN_header) return 1;
			}
			else {
				// if paletted, then pal_n is our final components, and
				// img_n is # components to decompress/filter.
				s->img_n = 1;
				if ((1 << 30) / s->img_x / 4 < s->img_y) return stbi__err("too large", "Corrupt PNG");
				// if SCAN_header, have to scan to see if we have a tRNS
			}
			break;
		}

		case STBI__PNG_TYPE('P', 'L', 'T', 'E'):  {
			if (first) return stbi__err("first not IHDR", "Corrupt PNG");
			if (c.length > 256 * 3) return stbi__err("invalid PLTE", "Corrupt PNG");
			pal_len = c.length / 3;
			if (pal_len * 3 != c.length) return stbi__err("invalid PLTE", "Corrupt PNG");
			for (i = 0; i < pal_len; ++i) {
				palette[i * 4 + 0] = stbi__get8(s);
				palette[i * 4 + 1] = stbi__get8(s);
				palette[i * 4 + 2] = stbi__get8(s);
				palette[i * 4 + 3] = 255;
			}
			break;
		}

		case STBI__PNG_TYPE('t', 'R', 'N', 'S'): {
			if (first) return stbi__err("first not IHDR", "Corrupt PNG");
			if (z->idata) return stbi__err("tRNS after IDAT", "Corrupt PNG");
			if (pal_img_n) {
				if (scan == STBI__SCAN_header) { s->img_n = 4; return 1; }
				if (pal_len == 0) return stbi__err("tRNS before PLTE", "Corrupt PNG");
				if (c.length > pal_len) return stbi__err("bad tRNS len", "Corrupt PNG");
				pal_img_n = 4;
				for (i = 0; i < c.length; ++i)
					palette[i * 4 + 3] = stbi__get8(s);
			}
			else {
				if (!(s->img_n & 1)) return stbi__err("tRNS with alpha", "Corrupt PNG");
				if (c.length != (stbi__uint32)s->img_n * 2) return stbi__err("bad tRNS len", "Corrupt PNG");
				has_trans = 1;
				if (z->depth == 16) {
					for (k = 0; k < s->img_n; ++k) tc16[k] = stbi__get16be(s); // copy the values as-is
				}
				else {
					for (k = 0; k < s->img_n; ++k) tc[k] = (stbi_uc)(stbi__get16be(s) & 255) * stbi__depth_scale_table[z->depth]; // non 8-bit images will be larger
				}
			}
			break;
		}

		case STBI__PNG_TYPE('I', 'D', 'A', 'T'): {
			if (first) return stbi__err("first not IHDR", "Corrupt PNG");
			if (pal_img_n && !pal_len) return stbi__err("no PLTE", "Corrupt PNG");
			if (scan == STBI__SCAN_header) { s->img_n = pal_img_n; return 1; }
			if ((int)(ioff + c.length) < (int)ioff) return 0;
			if (ioff + c.length > idata_limit) {
				stbi__uint32 idata_limit_old = idata_limit;
				stbi_uc *p;
				if (idata_limit == 0) idata_limit = c.length > 4096 ? c.length : 4096;
				while (ioff + c.length > idata_limit)
					idata_limit *= 2;
				STBI_NOTUSED(idata_limit_old);
				p = (stbi_uc *)STBI_REALLOC_SIZED(z->idata, idata_limit_old, idata_limit); if (p == NULL) return stbi__err("outofmem", "Out of memory");
				z->idata = p;
			}
			if (!stbi__getn(s, z->idata + ioff, c.length)) return stbi__err("outofdata", "Corrupt PNG");
			ioff += c.length;
			break;
		}

		case STBI__PNG_TYPE('I', 'E', 'N', 'D'): {
			stbi__uint32 raw_len, bpl;
			if (first) return stbi__err("first not IHDR", "Corrupt PNG");
			if (scan != STBI__SCAN_load) return 1;
			if (z->idata == NULL) return stbi__err("no IDAT", "Corrupt PNG");
			// initial guess for decoded data size to avoid unnecessary reallocs
			bpl = (s->img_x * z->depth + 7) / 8; // bytes per line, per component
			raw_len = bpl * s->img_y * s->img_n /* pixels */ + s->img_y /* filter mode per row */;
			z->expanded = (stbi_uc *)stbi_zlib_decode_malloc_guesssize_headerflag((char *)z->idata, ioff, raw_len, (int *)&raw_len, !is_iphone);
			if (z->expanded == NULL) return 0; // zlib should set error
			STBI_FREE(z->idata); z->idata = NULL;
			if ((req_comp == s->img_n + 1 && req_comp != 3 && !pal_img_n) || has_trans)
				s->img_out_n = s->img_n + 1;
			else
				s->img_out_n = s->img_n;
			if (!stbi__create_png_image(z, z->expanded, raw_len, s->img_out_n, z->depth, color, interlace)) return 0;
			if (has_trans) {
				if (z->depth == 16) {
					if (!stbi__compute_transparency16(z, tc16, s->img_out_n)) return 0;
				}
				else {
					if (!stbi__compute_transparency(z, tc, s->img_out_n)) return 0;
				}
			}
			if (is_iphone && stbi__de_iphone_flag && s->img_out_n > 2)
				stbi__de_iphone(z);
			if (pal_img_n) {
				// pal_img_n == 3 or 4
				s->img_n = pal_img_n; // record the actual colors we had
				s->img_out_n = pal_img_n;
				if (req_comp >= 3) s->img_out_n = req_comp;
				if (!stbi__expand_png_palette(z, palette, pal_len, s->img_out_n))
					return 0;
			}
			STBI_FREE(z->expanded); z->expanded = NULL;
			return 1;
		}

		default:
			// if critical, fail
			if (first) return stbi__err("first not IHDR", "Corrupt PNG");
			if ((c.type & (1 << 29)) == 0) {
#ifndef STBI_NO_FAILURE_STRINGS
				// not threadsafe
				static char invalid_chunk[] = "XXXX PNG chunk not known";
				invalid_chunk[0] = STBI__BYTECAST(c.type >> 24);
				invalid_chunk[1] = STBI__BYTECAST(c.type >> 16);
				invalid_chunk[2] = STBI__BYTECAST(c.type >> 8);
				invalid_chunk[3] = STBI__BYTECAST(c.type >> 0);
#endif
				return stbi__err(invalid_chunk, "PNG not supported: unknown PNG chunk type");
			}
			stbi__skip(s, c.length);
			break;
		}
		// end of PNG chunk, read and skip CRC
		stbi__get32be(s);
	}
}

static unsigned char *stbi__do_png(stbi__png *p, int *x, int *y, int *n, int req_comp)
{
	unsigned char *result = NULL;
	if (req_comp < 0 || req_comp > 4) return stbi__errpuc("bad req_comp", "Internal error");
	if (stbi__parse_png_file(p, STBI__SCAN_load, req_comp)) {
		if (p->depth == 16) {
			if (!stbi__reduce_png(p)) {
				return result;
			}
		}
		result = p->out;
		p->out = NULL;
		if (req_comp && req_comp != p->s->img_out_n) {
			result = stbi__convert_format(result, p->s->img_out_n, req_comp, p->s->img_x, p->s->img_y);
			p->s->img_out_n = req_comp;
			if (result == NULL) return result;
		}
		*x = p->s->img_x;
		*y = p->s->img_y;
		if (n) *n = p->s->img_n;
	}
	STBI_FREE(p->out);      p->out = NULL;
	STBI_FREE(p->expanded); p->expanded = NULL;
	STBI_FREE(p->idata);    p->idata = NULL;

	return result;
}

static unsigned char *stbi__png_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	stbi__png p;
	p.s = s;
	return stbi__do_png(&p, x, y, comp, req_comp);
}

static int stbi__png_test(stbi__context *s)
{
	int r;
	r = stbi__check_png_header(s);
	stbi__rewind(s);
	return r;
}

static int stbi__png_info_raw(stbi__png *p, int *x, int *y, int *comp)
{
	if (!stbi__parse_png_file(p, STBI__SCAN_header, 0)) {
		stbi__rewind(p->s);
		return 0;
	}
	if (x) *x = p->s->img_x;
	if (y) *y = p->s->img_y;
	if (comp) *comp = p->s->img_n;
	return 1;
}

static int stbi__png_info(stbi__context *s, int *x, int *y, int *comp)
{
	stbi__png p;
	p.s = s;
	return stbi__png_info_raw(&p, x, y, comp);
}
#endif

// Microsoft/Windows BMP image

#ifndef STBI_NO_BMP
static int stbi__bmp_test_raw(stbi__context *s)
{
	int r;
	int sz;
	if (stbi__get8(s) != 'B') return 0;
	if (stbi__get8(s) != 'M') return 0;
	stbi__get32le(s); // discard filesize
	stbi__get16le(s); // discard reserved
	stbi__get16le(s); // discard reserved
	stbi__get32le(s); // discard data offset
	sz = stbi__get32le(s);
	r = (sz == 12 || sz == 40 || sz == 56 || sz == 108 || sz == 124);
	return r;
}

static int stbi__bmp_test(stbi__context *s)
{
	int r = stbi__bmp_test_raw(s);
	stbi__rewind(s);
	return r;
}


// returns 0..31 for the highest set bit
static int stbi__high_bit(unsigned int z)
{
	int n = 0;
	if (z == 0) return -1;
	if (z >= 0x10000) n += 16, z >>= 16;
	if (z >= 0x00100) n += 8, z >>= 8;
	if (z >= 0x00010) n += 4, z >>= 4;
	if (z >= 0x00004) n += 2, z >>= 2;
	if (z >= 0x00002) n += 1, z >>= 1;
	return n;
}

static int stbi__bitcount(unsigned int a)
{
	a = (a & 0x55555555) + ((a >> 1) & 0x55555555); // max 2
	a = (a & 0x33333333) + ((a >> 2) & 0x33333333); // max 4
	a = (a + (a >> 4)) & 0x0f0f0f0f; // max 8 per 4, now 8 bits
	a = (a + (a >> 8)); // max 16 per 8 bits
	a = (a + (a >> 16)); // max 32 per 8 bits
	return a & 0xff;
}

static int stbi__shiftsigned(int v, int shift, int bits)
{
	int result;
	int z = 0;

	if (shift < 0) v <<= -shift;
	else v >>= shift;
	result = v;

	z = bits;
	while (z < 8) {
		result += v >> z;
		z += bits;
	}
	return result;
}

typedef struct
{
	int bpp, offset, hsz;
	unsigned int mr, mg, mb, ma, all_a;
} stbi__bmp_data;

static void *stbi__bmp_parse_header(stbi__context *s, stbi__bmp_data *info)
{
	int hsz;
	if (stbi__get8(s) != 'B' || stbi__get8(s) != 'M') return stbi__errpuc("not BMP", "Corrupt BMP");
	stbi__get32le(s); // discard filesize
	stbi__get16le(s); // discard reserved
	stbi__get16le(s); // discard reserved
	info->offset = stbi__get32le(s);
	info->hsz = hsz = stbi__get32le(s);
	info->mr = info->mg = info->mb = info->ma = 0;

	if (hsz != 12 && hsz != 40 && hsz != 56 && hsz != 108 && hsz != 124) return stbi__errpuc("unknown BMP", "BMP type not supported: unknown");
	if (hsz == 12) {
		s->img_x = stbi__get16le(s);
		s->img_y = stbi__get16le(s);
	}
	else {
		s->img_x = stbi__get32le(s);
		s->img_y = stbi__get32le(s);
	}
	if (stbi__get16le(s) != 1) return stbi__errpuc("bad BMP", "bad BMP");
	info->bpp = stbi__get16le(s);
	if (info->bpp == 1) return stbi__errpuc("monochrome", "BMP type not supported: 1-bit");
	if (hsz != 12) {
		int compress = stbi__get32le(s);
		if (compress == 1 || compress == 2) return stbi__errpuc("BMP RLE", "BMP type not supported: RLE");
		stbi__get32le(s); // discard sizeof
		stbi__get32le(s); // discard hres
		stbi__get32le(s); // discard vres
		stbi__get32le(s); // discard colorsused
		stbi__get32le(s); // discard max important
		if (hsz == 40 || hsz == 56) {
			if (hsz == 56) {
				stbi__get32le(s);
				stbi__get32le(s);
				stbi__get32le(s);
				stbi__get32le(s);
			}
			if (info->bpp == 16 || info->bpp == 32) {
				if (compress == 0) {
					if (info->bpp == 32) {
						info->mr = 0xffu << 16;
						info->mg = 0xffu << 8;
						info->mb = 0xffu << 0;
						info->ma = 0xffu << 24;
						info->all_a = 0; // if all_a is 0 at end, then we loaded alpha channel but it was all 0
					}
					else {
						info->mr = 31u << 10;
						info->mg = 31u << 5;
						info->mb = 31u << 0;
					}
				}
				else if (compress == 3) {
					info->mr = stbi__get32le(s);
					info->mg = stbi__get32le(s);
					info->mb = stbi__get32le(s);
					// not documented, but generated by photoshop and handled by mspaint
					if (info->mr == info->mg && info->mg == info->mb) {
						// ?!?!?
						return stbi__errpuc("bad BMP", "bad BMP");
					}
				}
				else
					return stbi__errpuc("bad BMP", "bad BMP");
			}
		}
		else {
			int i;
			if (hsz != 108 && hsz != 124)
				return stbi__errpuc("bad BMP", "bad BMP");
			info->mr = stbi__get32le(s);
			info->mg = stbi__get32le(s);
			info->mb = stbi__get32le(s);
			info->ma = stbi__get32le(s);
			stbi__get32le(s); // discard color space
			for (i = 0; i < 12; ++i)
				stbi__get32le(s); // discard color space parameters
			if (hsz == 124) {
				stbi__get32le(s); // discard rendering intent
				stbi__get32le(s); // discard offset of profile data
				stbi__get32le(s); // discard size of profile data
				stbi__get32le(s); // discard reserved
			}
		}
	}
	return (void *)1;
}


static stbi_uc *stbi__bmp_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	stbi_uc *out;
	unsigned int mr = 0, mg = 0, mb = 0, ma = 0, all_a;
	stbi_uc pal[256][4];
	int psize = 0, i, j, width;
	int flip_vertically, pad, target;
	stbi__bmp_data info;

	info.all_a = 255;
	if (stbi__bmp_parse_header(s, &info) == NULL)
		return NULL; // error code already set

	flip_vertically = ((int)s->img_y) > 0;
	s->img_y = abs((int)s->img_y);

	mr = info.mr;
	mg = info.mg;
	mb = info.mb;
	ma = info.ma;
	all_a = info.all_a;

	if (info.hsz == 12) {
		if (info.bpp < 24)
			psize = (info.offset - 14 - 24) / 3;
	}
	else {
		if (info.bpp < 16)
			psize = (info.offset - 14 - info.hsz) >> 2;
	}

	s->img_n = ma ? 4 : 3;
	if (req_comp && req_comp >= 3) // we can directly decode 3 or 4
		target = req_comp;
	else
		target = s->img_n; // if they want monochrome, we'll post-convert

	out = (stbi_uc *)stbi__malloc(target * s->img_x * s->img_y);
	if (!out) return stbi__errpuc("outofmem", "Out of memory");
	if (info.bpp < 16) {
		int z = 0;
		if (psize == 0 || psize > 256) { STBI_FREE(out); return stbi__errpuc("invalid", "Corrupt BMP"); }
		for (i = 0; i < psize; ++i) {
			pal[i][2] = stbi__get8(s);
			pal[i][1] = stbi__get8(s);
			pal[i][0] = stbi__get8(s);
			if (info.hsz != 12) stbi__get8(s);
			pal[i][3] = 255;
		}
		stbi__skip(s, info.offset - 14 - info.hsz - psize * (info.hsz == 12 ? 3 : 4));
		if (info.bpp == 4) width = (s->img_x + 1) >> 1;
		else if (info.bpp == 8) width = s->img_x;
		else { STBI_FREE(out); return stbi__errpuc("bad bpp", "Corrupt BMP"); }
		pad = (-width) & 3;
		for (j = 0; j < (int)s->img_y; ++j) {
			for (i = 0; i < (int)s->img_x; i += 2) {
				int v = stbi__get8(s), v2 = 0;
				if (info.bpp == 4) {
					v2 = v & 15;
					v >>= 4;
				}
				out[z++] = pal[v][0];
				out[z++] = pal[v][1];
				out[z++] = pal[v][2];
				if (target == 4) out[z++] = 255;
				if (i + 1 == (int)s->img_x) break;
				v = (info.bpp == 8) ? stbi__get8(s) : v2;
				out[z++] = pal[v][0];
				out[z++] = pal[v][1];
				out[z++] = pal[v][2];
				if (target == 4) out[z++] = 255;
			}
			stbi__skip(s, pad);
		}
	}
	else {
		int rshift = 0, gshift = 0, bshift = 0, ashift = 0, rcount = 0, gcount = 0, bcount = 0, acount = 0;
		int z = 0;
		int easy = 0;
		stbi__skip(s, info.offset - 14 - info.hsz);
		if (info.bpp == 24) width = 3 * s->img_x;
		else if (info.bpp == 16) width = 2 * s->img_x;
		else /* bpp = 32 and pad = 0 */ width = 0;
		pad = (-width) & 3;
		if (info.bpp == 24) {
			easy = 1;
		}
		else if (info.bpp == 32) {
			if (mb == 0xff && mg == 0xff00 && mr == 0x00ff0000 && ma == 0xff000000)
				easy = 2;
		}
		if (!easy) {
			if (!mr || !mg || !mb) { STBI_FREE(out); return stbi__errpuc("bad masks", "Corrupt BMP"); }
			// right shift amt to put high bit in position #7
			rshift = stbi__high_bit(mr) - 7; rcount = stbi__bitcount(mr);
			gshift = stbi__high_bit(mg) - 7; gcount = stbi__bitcount(mg);
			bshift = stbi__high_bit(mb) - 7; bcount = stbi__bitcount(mb);
			ashift = stbi__high_bit(ma) - 7; acount = stbi__bitcount(ma);
		}
		for (j = 0; j < (int)s->img_y; ++j) {
			if (easy) {
				for (i = 0; i < (int)s->img_x; ++i) {
					unsigned char a;
					out[z + 2] = stbi__get8(s);
					out[z + 1] = stbi__get8(s);
					out[z + 0] = stbi__get8(s);
					z += 3;
					a = (easy == 2 ? stbi__get8(s) : 255);
					all_a |= a;
					if (target == 4) out[z++] = a;
				}
			}
			else {
				int bpp = info.bpp;
				for (i = 0; i < (int)s->img_x; ++i) {
					stbi__uint32 v = (bpp == 16 ? (stbi__uint32)stbi__get16le(s) : stbi__get32le(s));
					int a;
					out[z++] = STBI__BYTECAST(stbi__shiftsigned(v & mr, rshift, rcount));
					out[z++] = STBI__BYTECAST(stbi__shiftsigned(v & mg, gshift, gcount));
					out[z++] = STBI__BYTECAST(stbi__shiftsigned(v & mb, bshift, bcount));
					a = (ma ? stbi__shiftsigned(v & ma, ashift, acount) : 255);
					all_a |= a;
					if (target == 4) out[z++] = STBI__BYTECAST(a);
				}
			}
			stbi__skip(s, pad);
		}
	}

	// if alpha channel is all 0s, replace with all 255s
	if (target == 4 && all_a == 0)
		for (i = 4 * s->img_x*s->img_y - 1; i >= 0; i -= 4)
			out[i] = 255;

	if (flip_vertically) {
		stbi_uc t;
		for (j = 0; j < (int)s->img_y >> 1; ++j) {
			stbi_uc *p1 = out + j     *s->img_x*target;
			stbi_uc *p2 = out + (s->img_y - 1 - j)*s->img_x*target;
			for (i = 0; i < (int)s->img_x*target; ++i) {
				t = p1[i], p1[i] = p2[i], p2[i] = t;
			}
		}
	}

	if (req_comp && req_comp != target) {
		out = stbi__convert_format(out, target, req_comp, s->img_x, s->img_y);
		if (out == NULL) return out; // stbi__convert_format frees input on failure
	}

	*x = s->img_x;
	*y = s->img_y;
	if (comp) *comp = s->img_n;
	return out;
}
#endif

// Targa Truevision - TGA
// by Jonathan Dummer
#ifndef STBI_NO_TGA
// returns STBI_rgb or whatever, 0 on error
static int stbi__tga_get_comp(int bits_per_pixel, int is_grey, int* is_rgb16)
{
	// only RGB or RGBA (incl. 16bit) or grey allowed
	if (is_rgb16) *is_rgb16 = 0;
	switch (bits_per_pixel) {
	case 8:  return STBI_grey;
	case 16: if (is_grey) return STBI_grey_alpha;
		// else: fall-through
	case 15: if (is_rgb16) *is_rgb16 = 1;
		return STBI_rgb;
	case 24: // fall-through
	case 32: return bits_per_pixel / 8;
	default: return 0;
	}
}

static int stbi__tga_info(stbi__context *s, int *x, int *y, int *comp)
{
	int tga_w, tga_h, tga_comp, tga_image_type, tga_bits_per_pixel, tga_colormap_bpp;
	int sz, tga_colormap_type;
	stbi__get8(s);                   // discard Offset
	tga_colormap_type = stbi__get8(s); // colormap type
	if (tga_colormap_type > 1) {
		stbi__rewind(s);
		return 0;      // only RGB or indexed allowed
	}
	tga_image_type = stbi__get8(s); // image type
	if (tga_colormap_type == 1) { // colormapped (paletted) image
		if (tga_image_type != 1 && tga_image_type != 9) {
			stbi__rewind(s);
			return 0;
		}
		stbi__skip(s, 4);       // skip index of first colormap entry and number of entries
		sz = stbi__get8(s);    //   check bits per palette color entry
		if ((sz != 8) && (sz != 15) && (sz != 16) && (sz != 24) && (sz != 32)) {
			stbi__rewind(s);
			return 0;
		}
		stbi__skip(s, 4);       // skip image x and y origin
		tga_colormap_bpp = sz;
	}
	else { // "normal" image w/o colormap - only RGB or grey allowed, +/- RLE
		if ((tga_image_type != 2) && (tga_image_type != 3) && (tga_image_type != 10) && (tga_image_type != 11)) {
			stbi__rewind(s);
			return 0; // only RGB or grey allowed, +/- RLE
		}
		stbi__skip(s, 9); // skip colormap specification and image x/y origin
		tga_colormap_bpp = 0;
	}
	tga_w = stbi__get16le(s);
	if (tga_w < 1) {
		stbi__rewind(s);
		return 0;   // test width
	}
	tga_h = stbi__get16le(s);
	if (tga_h < 1) {
		stbi__rewind(s);
		return 0;   // test height
	}
	tga_bits_per_pixel = stbi__get8(s); // bits per pixel
	stbi__get8(s); // ignore alpha bits
	if (tga_colormap_bpp != 0) {
		if ((tga_bits_per_pixel != 8) && (tga_bits_per_pixel != 16)) {
			// when using a colormap, tga_bits_per_pixel is the size of the indexes
			// I don't think anything but 8 or 16bit indexes makes sense
			stbi__rewind(s);
			return 0;
		}
		tga_comp = stbi__tga_get_comp(tga_colormap_bpp, 0, NULL);
	}
	else {
		tga_comp = stbi__tga_get_comp(tga_bits_per_pixel, (tga_image_type == 3) || (tga_image_type == 11), NULL);
	}
	if (!tga_comp) {
		stbi__rewind(s);
		return 0;
	}
	if (x) *x = tga_w;
	if (y) *y = tga_h;
	if (comp) *comp = tga_comp;
	return 1;                   // seems to have passed everything
}

static int stbi__tga_test(stbi__context *s)
{
	int res = 0;
	int sz, tga_color_type;
	stbi__get8(s);      //   discard Offset
	tga_color_type = stbi__get8(s);   //   color type
	if (tga_color_type > 1) goto errorEnd;   //   only RGB or indexed allowed
	sz = stbi__get8(s);   //   image type
	if (tga_color_type == 1) { // colormapped (paletted) image
		if (sz != 1 && sz != 9) goto errorEnd; // colortype 1 demands image type 1 or 9
		stbi__skip(s, 4);       // skip index of first colormap entry and number of entries
		sz = stbi__get8(s);    //   check bits per palette color entry
		if ((sz != 8) && (sz != 15) && (sz != 16) && (sz != 24) && (sz != 32)) goto errorEnd;
		stbi__skip(s, 4);       // skip image x and y origin
	}
	else { // "normal" image w/o colormap
		if ((sz != 2) && (sz != 3) && (sz != 10) && (sz != 11)) goto errorEnd; // only RGB or grey allowed, +/- RLE
		stbi__skip(s, 9); // skip colormap specification and image x/y origin
	}
	if (stbi__get16le(s) < 1) goto errorEnd;      //   test width
	if (stbi__get16le(s) < 1) goto errorEnd;      //   test height
	sz = stbi__get8(s);   //   bits per pixel
	if ((tga_color_type == 1) && (sz != 8) && (sz != 16)) goto errorEnd; // for colormapped images, bpp is size of an index
	if ((sz != 8) && (sz != 15) && (sz != 16) && (sz != 24) && (sz != 32)) goto errorEnd;

	res = 1; // if we got this far, everything's good and we can return 1 instead of 0

errorEnd:
	stbi__rewind(s);
	return res;
}

// read 16bit value and convert to 24bit RGB
void stbi__tga_read_rgb16(stbi__context *s, stbi_uc* out)
{
	stbi__uint16 px = stbi__get16le(s);
	stbi__uint16 fiveBitMask = 31;
	// we have 3 channels with 5bits each
	int r = (px >> 10) & fiveBitMask;
	int g = (px >> 5) & fiveBitMask;
	int b = px & fiveBitMask;
	// Note that this saves the data in RGB(A) order, so it doesn't need to be swapped later
	out[0] = (r * 255) / 31;
	out[1] = (g * 255) / 31;
	out[2] = (b * 255) / 31;

	// some people claim that the most significant bit might be used for alpha
	// (possibly if an alpha-bit is set in the "image descriptor byte")
	// but that only made 16bit test images completely translucent..
	// so let's treat all 15 and 16bit TGAs as RGB with no alpha.
}

static stbi_uc *stbi__tga_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	//   read in the TGA header stuff
	int tga_offset = stbi__get8(s);
	int tga_indexed = stbi__get8(s);
	int tga_image_type = stbi__get8(s);
	int tga_is_RLE = 0;
	int tga_palette_start = stbi__get16le(s);
	int tga_palette_len = stbi__get16le(s);
	int tga_palette_bits = stbi__get8(s);
	int tga_x_origin = stbi__get16le(s);
	int tga_y_origin = stbi__get16le(s);
	int tga_width = stbi__get16le(s);
	int tga_height = stbi__get16le(s);
	int tga_bits_per_pixel = stbi__get8(s);
	int tga_comp, tga_rgb16 = 0;
	int tga_inverted = stbi__get8(s);
	// int tga_alpha_bits = tga_inverted & 15; // the 4 lowest bits - unused (useless?)
	//   image data
	unsigned char *tga_data;
	unsigned char *tga_palette = NULL;
	int i, j;
	unsigned char raw_data[4];
	int RLE_count = 0;
	int RLE_repeating = 0;
	int read_next_pixel = 1;

	//   do a tiny bit of precessing
	if (tga_image_type >= 8)
	{
		tga_image_type -= 8;
		tga_is_RLE = 1;
	}
	tga_inverted = 1 - ((tga_inverted >> 5) & 1);

	//   If I'm paletted, then I'll use the number of bits from the palette
	if (tga_indexed) tga_comp = stbi__tga_get_comp(tga_palette_bits, 0, &tga_rgb16);
	else tga_comp = stbi__tga_get_comp(tga_bits_per_pixel, (tga_image_type == 3), &tga_rgb16);

	if (!tga_comp) // shouldn't really happen, stbi__tga_test() should have ensured basic consistency
		return stbi__errpuc("bad format", "Can't find out TGA pixelformat");

	//   tga info
	*x = tga_width;
	*y = tga_height;
	if (comp) *comp = tga_comp;

	tga_data = (unsigned char*)stbi__malloc((size_t)tga_width * tga_height * tga_comp);
	if (!tga_data) return stbi__errpuc("outofmem", "Out of memory");

	// skip to the data's starting position (offset usually = 0)
	stbi__skip(s, tga_offset);

	if (!tga_indexed && !tga_is_RLE && !tga_rgb16) {
		for (i = 0; i < tga_height; ++i) {
			int row = tga_inverted ? tga_height - i - 1 : i;
			stbi_uc *tga_row = tga_data + row*tga_width*tga_comp;
			stbi__getn(s, tga_row, tga_width * tga_comp);
		}
	}
	else  {
		//   do I need to load a palette?
		if (tga_indexed)
		{
			//   any data to skip? (offset usually = 0)
			stbi__skip(s, tga_palette_start);
			//   load the palette
			tga_palette = (unsigned char*)stbi__malloc(tga_palette_len * tga_comp);
			if (!tga_palette) {
				STBI_FREE(tga_data);
				return stbi__errpuc("outofmem", "Out of memory");
			}
			if (tga_rgb16) {
				stbi_uc *pal_entry = tga_palette;
				STBI_ASSERT(tga_comp == STBI_rgb);
				for (i = 0; i < tga_palette_len; ++i) {
					stbi__tga_read_rgb16(s, pal_entry);
					pal_entry += tga_comp;
				}
			}
			else if (!stbi__getn(s, tga_palette, tga_palette_len * tga_comp)) {
				STBI_FREE(tga_data);
				STBI_FREE(tga_palette);
				return stbi__errpuc("bad palette", "Corrupt TGA");
			}
		}
		//   load the data
		for (i = 0; i < tga_width * tga_height; ++i)
		{
			//   if I'm in RLE mode, do I need to get a RLE stbi__pngchunk?
			if (tga_is_RLE)
			{
				if (RLE_count == 0)
				{
					//   yep, get the next byte as a RLE command
					int RLE_cmd = stbi__get8(s);
					RLE_count = 1 + (RLE_cmd & 127);
					RLE_repeating = RLE_cmd >> 7;
					read_next_pixel = 1;
				}
				else if (!RLE_repeating)
				{
					read_next_pixel = 1;
				}
			}
			else
			{
				read_next_pixel = 1;
			}
			//   OK, if I need to read a pixel, do it now
			if (read_next_pixel)
			{
				//   load however much data we did have
				if (tga_indexed)
				{
					// read in index, then perform the lookup
					int pal_idx = (tga_bits_per_pixel == 8) ? stbi__get8(s) : stbi__get16le(s);
					if (pal_idx >= tga_palette_len) {
						// invalid index
						pal_idx = 0;
					}
					pal_idx *= tga_comp;
					for (j = 0; j < tga_comp; ++j) {
						raw_data[j] = tga_palette[pal_idx + j];
					}
				}
				else if (tga_rgb16) {
					STBI_ASSERT(tga_comp == STBI_rgb);
					stbi__tga_read_rgb16(s, raw_data);
				}
				else {
					//   read in the data raw
					for (j = 0; j < tga_comp; ++j) {
						raw_data[j] = stbi__get8(s);
					}
				}
				//   clear the reading flag for the next pixel
				read_next_pixel = 0;
			} // end of reading a pixel

			// copy data
			for (j = 0; j < tga_comp; ++j)
				tga_data[i*tga_comp + j] = raw_data[j];

			//   in case we're in RLE mode, keep counting down
			--RLE_count;
		}
		//   do I need to invert the image?
		if (tga_inverted)
		{
			for (j = 0; j * 2 < tga_height; ++j)
			{
				int index1 = j * tga_width * tga_comp;
				int index2 = (tga_height - 1 - j) * tga_width * tga_comp;
				for (i = tga_width * tga_comp; i > 0; --i)
				{
					unsigned char temp = tga_data[index1];
					tga_data[index1] = tga_data[index2];
					tga_data[index2] = temp;
					++index1;
					++index2;
				}
			}
		}
		//   clear my palette, if I had one
		if (tga_palette != NULL)
		{
			STBI_FREE(tga_palette);
		}
	}

	// swap RGB - if the source data was RGB16, it already is in the right order
	if (tga_comp >= 3 && !tga_rgb16)
	{
		unsigned char* tga_pixel = tga_data;
		for (i = 0; i < tga_width * tga_height; ++i)
		{
			unsigned char temp = tga_pixel[0];
			tga_pixel[0] = tga_pixel[2];
			tga_pixel[2] = temp;
			tga_pixel += tga_comp;
		}
	}

	// convert to target component count
	if (req_comp && req_comp != tga_comp)
		tga_data = stbi__convert_format(tga_data, tga_comp, req_comp, tga_width, tga_height);

	//   the things I do to get rid of an error message, and yet keep
	//   Microsoft's C compilers happy... [8^(
	tga_palette_start = tga_palette_len = tga_palette_bits =
		tga_x_origin = tga_y_origin = 0;
	//   OK, done
	return tga_data;
}
#endif

// *************************************************************************************************
// Photoshop PSD loader -- PD by Thatcher Ulrich, integration by Nicolas Schulz, tweaked by STB

#ifndef STBI_NO_PSD
static int stbi__psd_test(stbi__context *s)
{
	int r = (stbi__get32be(s) == 0x38425053);
	stbi__rewind(s);
	return r;
}

static stbi_uc *stbi__psd_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	int   pixelCount;
	int channelCount, compression;
	int channel, i, count, len;
	int bitdepth;
	int w, h;
	stbi_uc *out;

	// Check identifier
	if (stbi__get32be(s) != 0x38425053)   // "8BPS"
		return stbi__errpuc("not PSD", "Corrupt PSD image");

	// Check file type version.
	if (stbi__get16be(s) != 1)
		return stbi__errpuc("wrong version", "Unsupported version of PSD image");

	// Skip 6 reserved bytes.
	stbi__skip(s, 6);

	// Read the number of channels (R, G, B, A, etc).
	channelCount = stbi__get16be(s);
	if (channelCount < 0 || channelCount > 16)
		return stbi__errpuc("wrong channel count", "Unsupported number of channels in PSD image");

	// Read the rows and columns of the image.
	h = stbi__get32be(s);
	w = stbi__get32be(s);

	// Make sure the depth is 8 bits.
	bitdepth = stbi__get16be(s);
	if (bitdepth != 8 && bitdepth != 16)
		return stbi__errpuc("unsupported bit depth", "PSD bit depth is not 8 or 16 bit");

	// Make sure the color mode is RGB.
	// Valid options are:
	//   0: Bitmap
	//   1: Grayscale
	//   2: Indexed color
	//   3: RGB color
	//   4: CMYK color
	//   7: Multichannel
	//   8: Duotone
	//   9: Lab color
	if (stbi__get16be(s) != 3)
		return stbi__errpuc("wrong color format", "PSD is not in RGB color format");

	// Skip the Mode Data.  (It's the palette for indexed color; other info for other modes.)
	stbi__skip(s, stbi__get32be(s));

	// Skip the image resources.  (resolution, pen tool paths, etc)
	stbi__skip(s, stbi__get32be(s));

	// Skip the reserved data.
	stbi__skip(s, stbi__get32be(s));

	// Find out if the data is compressed.
	// Known values:
	//   0: no compression
	//   1: RLE compressed
	compression = stbi__get16be(s);
	if (compression > 1)
		return stbi__errpuc("bad compression", "PSD has an unknown compression format");

	// Create the destination image.
	out = (stbi_uc *)stbi__malloc(4 * w*h);
	if (!out) return stbi__errpuc("outofmem", "Out of memory");
	pixelCount = w*h;

	// Initialize the data to zero.
	//memset( out, 0, pixelCount * 4 );

	// Finally, the image data.
	if (compression) {
		// RLE as used by .PSD and .TIFF
		// Loop until you get the number of unpacked bytes you are expecting:
		//     Read the next source byte into n.
		//     If n is between 0 and 127 inclusive, copy the next n+1 bytes literally.
		//     Else if n is between -127 and -1 inclusive, copy the next byte -n+1 times.
		//     Else if n is 128, noop.
		// Endloop

		// The RLE-compressed data is preceeded by a 2-byte data count for each row in the data,
		// which we're going to just skip.
		stbi__skip(s, h * channelCount * 2);

		// Read the RLE data by channel.
		for (channel = 0; channel < 4; channel++) {
			stbi_uc *p;

			p = out + channel;
			if (channel >= channelCount) {
				// Fill this channel with default data.
				for (i = 0; i < pixelCount; i++, p += 4)
					*p = (channel == 3 ? 255 : 0);
			}
			else {
				// Read the RLE data.
				count = 0;
				while (count < pixelCount) {
					len = stbi__get8(s);
					if (len == 128) {
						// No-op.
					}
					else if (len < 128) {
						// Copy next len+1 bytes literally.
						len++;
						count += len;
						while (len) {
							*p = stbi__get8(s);
							p += 4;
							len--;
						}
					}
					else if (len > 128) {
						stbi_uc   val;
						// Next -len+1 bytes in the dest are replicated from next source byte.
						// (Interpret len as a negative 8-bit int.)
						len ^= 0x0FF;
						len += 2;
						val = stbi__get8(s);
						count += len;
						while (len) {
							*p = val;
							p += 4;
							len--;
						}
					}
				}
			}
		}

	}
	else {
		// We're at the raw image data.  It's each channel in order (Red, Green, Blue, Alpha, ...)
		// where each channel consists of an 8-bit value for each pixel in the image.

		// Read the data by channel.
		for (channel = 0; channel < 4; channel++) {
			stbi_uc *p;

			p = out + channel;
			if (channel >= channelCount) {
				// Fill this channel with default data.
				stbi_uc val = channel == 3 ? 255 : 0;
				for (i = 0; i < pixelCount; i++, p += 4)
					*p = val;
			}
			else {
				// Read the data.
				if (bitdepth == 16) {
					for (i = 0; i < pixelCount; i++, p += 4)
						*p = (stbi_uc)(stbi__get16be(s) >> 8);
				}
				else {
					for (i = 0; i < pixelCount; i++, p += 4)
						*p = stbi__get8(s);
				}
			}
		}
	}

	if (channelCount >= 4) {
		for (i = 0; i < w*h; ++i) {
			unsigned char *pixel = out + 4 * i;
			if (pixel[3] != 0 && pixel[3] != 255) {
				// remove weird white matte from PSD
				float a = pixel[3] / 255.0f;
				float ra = 1.0f / a;
				float inv_a = 255.0f * (1 - ra);
				pixel[0] = (unsigned char)(pixel[0] * ra + inv_a);
				pixel[1] = (unsigned char)(pixel[1] * ra + inv_a);
				pixel[2] = (unsigned char)(pixel[2] * ra + inv_a);
			}
		}
	}

	if (req_comp && req_comp != 4) {
		out = stbi__convert_format(out, 4, req_comp, w, h);
		if (out == NULL) return out; // stbi__convert_format frees input on failure
	}

	if (comp) *comp = 4;
	*y = h;
	*x = w;

	return out;
}
#endif

// *************************************************************************************************
// Softimage PIC loader
// by Tom Seddon
//
// See http://softimage.wiki.softimage.com/index.php/INFO:_PIC_file_format
// See http://ozviz.wasp.uwa.edu.au/~pbourke/dataformats/softimagepic/

#ifndef STBI_NO_PIC
static int stbi__pic_is4(stbi__context *s, const char *str)
{
	int i;
	for (i = 0; i<4; ++i)
		if (stbi__get8(s) != (stbi_uc)str[i])
			return 0;

	return 1;
}

static int stbi__pic_test_core(stbi__context *s)
{
	int i;

	if (!stbi__pic_is4(s, "\x53\x80\xF6\x34"))
		return 0;

	for (i = 0; i<84; ++i)
		stbi__get8(s);

	if (!stbi__pic_is4(s, "PICT"))
		return 0;

	return 1;
}

typedef struct
{
	stbi_uc size, type, channel;
} stbi__pic_packet;

static stbi_uc *stbi__readval(stbi__context *s, int channel, stbi_uc *dest)
{
	int mask = 0x80, i;

	for (i = 0; i<4; ++i, mask >>= 1) {
		if (channel & mask) {
			if (stbi__at_eof(s)) return stbi__errpuc("bad file", "PIC file too short");
			dest[i] = stbi__get8(s);
		}
	}

	return dest;
}

static void stbi__copyval(int channel, stbi_uc *dest, const stbi_uc *src)
{
	int mask = 0x80, i;

	for (i = 0; i<4; ++i, mask >>= 1)
		if (channel&mask)
			dest[i] = src[i];
}

static stbi_uc *stbi__pic_load_core(stbi__context *s, int width, int height, int *comp, stbi_uc *result)
{
	int act_comp = 0, num_packets = 0, y, chained;
	stbi__pic_packet packets[10];

	// this will (should...) cater for even some bizarre stuff like having data
	// for the same channel in multiple packets.
	do {
		stbi__pic_packet *packet;

		if (num_packets == sizeof(packets) / sizeof(packets[0]))
			return stbi__errpuc("bad format", "too many packets");

		packet = &packets[num_packets++];

		chained = stbi__get8(s);
		packet->size = stbi__get8(s);
		packet->type = stbi__get8(s);
		packet->channel = stbi__get8(s);

		act_comp |= packet->channel;

		if (stbi__at_eof(s))          return stbi__errpuc("bad file", "file too short (reading packets)");
		if (packet->size != 8)  return stbi__errpuc("bad format", "packet isn't 8bpp");
	} while (chained);

	*comp = (act_comp & 0x10 ? 4 : 3); // has alpha channel?

	for (y = 0; y<height; ++y) {
		int packet_idx;

		for (packet_idx = 0; packet_idx < num_packets; ++packet_idx) {
			stbi__pic_packet *packet = &packets[packet_idx];
			stbi_uc *dest = result + y*width * 4;

			switch (packet->type) {
			default:
				return stbi__errpuc("bad format", "packet has bad compression type");

			case 0: {//uncompressed
				int x;

				for (x = 0; x<width; ++x, dest += 4)
					if (!stbi__readval(s, packet->channel, dest))
						return 0;
				break;
			}

			case 1://Pure RLE
			{
				int left = width, i;

				while (left>0) {
					stbi_uc count, value[4];

					count = stbi__get8(s);
					if (stbi__at_eof(s))   return stbi__errpuc("bad file", "file too short (pure read count)");

					if (count > left)
						count = (stbi_uc)left;

					if (!stbi__readval(s, packet->channel, value))  return 0;

					for (i = 0; i<count; ++i, dest += 4)
						stbi__copyval(packet->channel, dest, value);
					left -= count;
				}
			}
			break;

			case 2: {//Mixed RLE
				int left = width;
				while (left>0) {
					int count = stbi__get8(s), i;
					if (stbi__at_eof(s))  return stbi__errpuc("bad file", "file too short (mixed read count)");

					if (count >= 128) { // Repeated
						stbi_uc value[4];

						if (count == 128)
							count = stbi__get16be(s);
						else
							count -= 127;
						if (count > left)
							return stbi__errpuc("bad file", "scanline overrun");

						if (!stbi__readval(s, packet->channel, value))
							return 0;

						for (i = 0; i<count; ++i, dest += 4)
							stbi__copyval(packet->channel, dest, value);
					}
					else { // Raw
						++count;
						if (count>left) return stbi__errpuc("bad file", "scanline overrun");

						for (i = 0; i<count; ++i, dest += 4)
							if (!stbi__readval(s, packet->channel, dest))
								return 0;
					}
					left -= count;
				}
				break;
			}
			}
		}
	}

	return result;
}

static stbi_uc *stbi__pic_load(stbi__context *s, int *px, int *py, int *comp, int req_comp)
{
	stbi_uc *result;
	int i, x, y;

	for (i = 0; i<92; ++i)
		stbi__get8(s);

	x = stbi__get16be(s);
	y = stbi__get16be(s);
	if (stbi__at_eof(s))  return stbi__errpuc("bad file", "file too short (pic header)");
	if ((1 << 28) / x < y) return stbi__errpuc("too large", "Image too large to decode");

	stbi__get32be(s); //skip `ratio'
	stbi__get16be(s); //skip `fields'
	stbi__get16be(s); //skip `pad'

	// intermediate buffer is RGBA
	result = (stbi_uc *)stbi__malloc(x*y * 4);
	memset(result, 0xff, x*y * 4);

	if (!stbi__pic_load_core(s, x, y, comp, result)) {
		STBI_FREE(result);
		result = 0;
	}
	*px = x;
	*py = y;
	if (req_comp == 0) req_comp = *comp;
	result = stbi__convert_format(result, 4, req_comp, x, y);

	return result;
}

static int stbi__pic_test(stbi__context *s)
{
	int r = stbi__pic_test_core(s);
	stbi__rewind(s);
	return r;
}
#endif

// *************************************************************************************************
// GIF loader -- public domain by Jean-Marc Lienher -- simplified/shrunk by stb

#ifndef STBI_NO_GIF
typedef struct
{
	stbi__int16 prefix;
	stbi_uc first;
	stbi_uc suffix;
} stbi__gif_lzw;

typedef struct
{
	int w, h;
	stbi_uc *out, *old_out;             // output buffer (always 4 components)
	int flags, bgindex, ratio, transparent, eflags, delay;
	stbi_uc  pal[256][4];
	stbi_uc lpal[256][4];
	stbi__gif_lzw codes[4096];
	stbi_uc *color_table;
	int parse, step;
	int lflags;
	int start_x, start_y;
	int max_x, max_y;
	int cur_x, cur_y;
	int line_size;
} stbi__gif;

static int stbi__gif_test_raw(stbi__context *s)
{
	int sz;
	if (stbi__get8(s) != 'G' || stbi__get8(s) != 'I' || stbi__get8(s) != 'F' || stbi__get8(s) != '8') return 0;
	sz = stbi__get8(s);
	if (sz != '9' && sz != '7') return 0;
	if (stbi__get8(s) != 'a') return 0;
	return 1;
}

static int stbi__gif_test(stbi__context *s)
{
	int r = stbi__gif_test_raw(s);
	stbi__rewind(s);
	return r;
}

static void stbi__gif_parse_colortable(stbi__context *s, stbi_uc pal[256][4], int num_entries, int transp)
{
	int i;
	for (i = 0; i < num_entries; ++i) {
		pal[i][2] = stbi__get8(s);
		pal[i][1] = stbi__get8(s);
		pal[i][0] = stbi__get8(s);
		pal[i][3] = transp == i ? 0 : 255;
	}
}

static int stbi__gif_header(stbi__context *s, stbi__gif *g, int *comp, int is_info)
{
	stbi_uc version;
	if (stbi__get8(s) != 'G' || stbi__get8(s) != 'I' || stbi__get8(s) != 'F' || stbi__get8(s) != '8')
		return stbi__err("not GIF", "Corrupt GIF");

	version = stbi__get8(s);
	if (version != '7' && version != '9')    return stbi__err("not GIF", "Corrupt GIF");
	if (stbi__get8(s) != 'a')                return stbi__err("not GIF", "Corrupt GIF");

	stbi__g_failure_reason = "";
	g->w = stbi__get16le(s);
	g->h = stbi__get16le(s);
	g->flags = stbi__get8(s);
	g->bgindex = stbi__get8(s);
	g->ratio = stbi__get8(s);
	g->transparent = -1;

	if (comp != 0) *comp = 4;  // can't actually tell whether it's 3 or 4 until we parse the comments

	if (is_info) return 1;

	if (g->flags & 0x80)
		stbi__gif_parse_colortable(s, g->pal, 2 << (g->flags & 7), -1);

	return 1;
}

static int stbi__gif_info_raw(stbi__context *s, int *x, int *y, int *comp)
{
	stbi__gif* g = (stbi__gif*)stbi__malloc(sizeof(stbi__gif));
	if (!stbi__gif_header(s, g, comp, 1)) {
		STBI_FREE(g);
		stbi__rewind(s);
		return 0;
	}
	if (x) *x = g->w;
	if (y) *y = g->h;
	STBI_FREE(g);
	return 1;
}

static void stbi__out_gif_code(stbi__gif *g, stbi__uint16 code)
{
	stbi_uc *p, *c;

	// recurse to decode the prefixes, since the linked-list is backwards,
	// and working backwards through an interleaved image would be nasty
	if (g->codes[code].prefix >= 0)
		stbi__out_gif_code(g, g->codes[code].prefix);

	if (g->cur_y >= g->max_y) return;

	p = &g->out[g->cur_x + g->cur_y];
	c = &g->color_table[g->codes[code].suffix * 4];

	if (c[3] >= 128) {
		p[0] = c[2];
		p[1] = c[1];
		p[2] = c[0];
		p[3] = c[3];
	}
	g->cur_x += 4;

	if (g->cur_x >= g->max_x) {
		g->cur_x = g->start_x;
		g->cur_y += g->step;

		while (g->cur_y >= g->max_y && g->parse > 0) {
			g->step = (1 << g->parse) * g->line_size;
			g->cur_y = g->start_y + (g->step >> 1);
			--g->parse;
		}
	}
}

static stbi_uc *stbi__process_gif_raster(stbi__context *s, stbi__gif *g)
{
	stbi_uc lzw_cs;
	stbi__int32 len, init_code;
	stbi__uint32 first;
	stbi__int32 codesize, codemask, avail, oldcode, bits, valid_bits, clear;
	stbi__gif_lzw *p;

	lzw_cs = stbi__get8(s);
	if (lzw_cs > 12) return NULL;
	clear = 1 << lzw_cs;
	first = 1;
	codesize = lzw_cs + 1;
	codemask = (1 << codesize) - 1;
	bits = 0;
	valid_bits = 0;
	for (init_code = 0; init_code < clear; init_code++) {
		g->codes[init_code].prefix = -1;
		g->codes[init_code].first = (stbi_uc)init_code;
		g->codes[init_code].suffix = (stbi_uc)init_code;
	}

	// support no starting clear code
	avail = clear + 2;
	oldcode = -1;

	len = 0;
	for (;;) {
		if (valid_bits < codesize) {
			if (len == 0) {
				len = stbi__get8(s); // start new block
				if (len == 0)
					return g->out;
			}
			--len;
			bits |= (stbi__int32)stbi__get8(s) << valid_bits;
			valid_bits += 8;
		}
		else {
			stbi__int32 code = bits & codemask;
			bits >>= codesize;
			valid_bits -= codesize;
			// @OPTIMIZE: is there some way we can accelerate the non-clear path?
			if (code == clear) {  // clear code
				codesize = lzw_cs + 1;
				codemask = (1 << codesize) - 1;
				avail = clear + 2;
				oldcode = -1;
				first = 0;
			}
			else if (code == clear + 1) { // end of stream code
				stbi__skip(s, len);
				while ((len = stbi__get8(s)) > 0)
					stbi__skip(s, len);
				return g->out;
			}
			else if (code <= avail) {
				if (first) return stbi__errpuc("no clear code", "Corrupt GIF");

				if (oldcode >= 0) {
					p = &g->codes[avail++];
					if (avail > 4096)        return stbi__errpuc("too many codes", "Corrupt GIF");
					p->prefix = (stbi__int16)oldcode;
					p->first = g->codes[oldcode].first;
					p->suffix = (code == avail) ? p->first : g->codes[code].first;
				}
				else if (code == avail)
					return stbi__errpuc("illegal code in raster", "Corrupt GIF");

				stbi__out_gif_code(g, (stbi__uint16)code);

				if ((avail & codemask) == 0 && avail <= 0x0FFF) {
					codesize++;
					codemask = (1 << codesize) - 1;
				}

				oldcode = code;
			}
			else {
				return stbi__errpuc("illegal code in raster", "Corrupt GIF");
			}
		}
	}
}

static void stbi__fill_gif_background(stbi__gif *g, int x0, int y0, int x1, int y1)
{
	int x, y;
	stbi_uc *c = g->pal[g->bgindex];
	for (y = y0; y < y1; y += 4 * g->w) {
		for (x = x0; x < x1; x += 4) {
			stbi_uc *p = &g->out[y + x];
			p[0] = c[2];
			p[1] = c[1];
			p[2] = c[0];
			p[3] = 0;
		}
	}
}

// this function is designed to support animated gifs, although stb_image doesn't support it
static stbi_uc *stbi__gif_load_next(stbi__context *s, stbi__gif *g, int *comp, int req_comp)
{
	int i;
	stbi_uc *prev_out = 0;

	if (g->out == 0 && !stbi__gif_header(s, g, comp, 0))
		return 0; // stbi__g_failure_reason set by stbi__gif_header

	prev_out = g->out;
	g->out = (stbi_uc *)stbi__malloc(4 * g->w * g->h);
	if (g->out == 0) return stbi__errpuc("outofmem", "Out of memory");

	switch ((g->eflags & 0x1C) >> 2) {
	case 0: // unspecified (also always used on 1st frame)
		stbi__fill_gif_background(g, 0, 0, 4 * g->w, 4 * g->w * g->h);
		break;
	case 1: // do not dispose
		if (prev_out) memcpy(g->out, prev_out, 4 * g->w * g->h);
		g->old_out = prev_out;
		break;
	case 2: // dispose to background
		if (prev_out) memcpy(g->out, prev_out, 4 * g->w * g->h);
		stbi__fill_gif_background(g, g->start_x, g->start_y, g->max_x, g->max_y);
		break;
	case 3: // dispose to previous
		if (g->old_out) {
			for (i = g->start_y; i < g->max_y; i += 4 * g->w)
				memcpy(&g->out[i + g->start_x], &g->old_out[i + g->start_x], g->max_x - g->start_x);
		}
		break;
	}

	for (;;) {
		switch (stbi__get8(s)) {
		case 0x2C: /* Image Descriptor */
		{
			int prev_trans = -1;
			stbi__int32 x, y, w, h;
			stbi_uc *o;

			x = stbi__get16le(s);
			y = stbi__get16le(s);
			w = stbi__get16le(s);
			h = stbi__get16le(s);
			if (((x + w) > (g->w)) || ((y + h) > (g->h)))
				return stbi__errpuc("bad Image Descriptor", "Corrupt GIF");

			g->line_size = g->w * 4;
			g->start_x = x * 4;
			g->start_y = y * g->line_size;
			g->max_x = g->start_x + w * 4;
			g->max_y = g->start_y + h * g->line_size;
			g->cur_x = g->start_x;
			g->cur_y = g->start_y;

			g->lflags = stbi__get8(s);

			if (g->lflags & 0x40) {
				g->step = 8 * g->line_size; // first interlaced spacing
				g->parse = 3;
			}
			else {
				g->step = g->line_size;
				g->parse = 0;
			}

			if (g->lflags & 0x80) {
				stbi__gif_parse_colortable(s, g->lpal, 2 << (g->lflags & 7), g->eflags & 0x01 ? g->transparent : -1);
				g->color_table = (stbi_uc *)g->lpal;
			}
			else if (g->flags & 0x80) {
				if (g->transparent >= 0 && (g->eflags & 0x01)) {
					prev_trans = g->pal[g->transparent][3];
					g->pal[g->transparent][3] = 0;
				}
				g->color_table = (stbi_uc *)g->pal;
			}
			else
				return stbi__errpuc("missing color table", "Corrupt GIF");

			o = stbi__process_gif_raster(s, g);
			if (o == NULL) return NULL;

			if (prev_trans != -1)
				g->pal[g->transparent][3] = (stbi_uc)prev_trans;

			return o;
		}

		case 0x21: // Comment Extension.
		{
			int len;
			if (stbi__get8(s) == 0xF9) { // Graphic Control Extension.
				len = stbi__get8(s);
				if (len == 4) {
					g->eflags = stbi__get8(s);
					g->delay = stbi__get16le(s);
					g->transparent = stbi__get8(s);
				}
				else {
					stbi__skip(s, len);
					break;
				}
			}
			while ((len = stbi__get8(s)) != 0)
				stbi__skip(s, len);
			break;
		}

		case 0x3B: // gif stream termination code
			return (stbi_uc *)s; // using '1' causes warning on some compilers

		default:
			return stbi__errpuc("unknown code", "Corrupt GIF");
		}
	}

	STBI_NOTUSED(req_comp);
}

static stbi_uc *stbi__gif_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	stbi_uc *u = 0;
	stbi__gif* g = (stbi__gif*)stbi__malloc(sizeof(stbi__gif));
	memset(g, 0, sizeof(*g));

	u = stbi__gif_load_next(s, g, comp, req_comp);
	if (u == (stbi_uc *)s) u = 0;  // end of animated gif marker
	if (u) {
		*x = g->w;
		*y = g->h;
		if (req_comp && req_comp != 4)
			u = stbi__convert_format(u, 4, req_comp, g->w, g->h);
	}
	else if (g->out)
		STBI_FREE(g->out);
	STBI_FREE(g);
	return u;
}

static int stbi__gif_info(stbi__context *s, int *x, int *y, int *comp)
{
	return stbi__gif_info_raw(s, x, y, comp);
}
#endif

// *************************************************************************************************
// Radiance RGBE HDR loader
// originally by Nicolas Schulz
#ifndef STBI_NO_HDR
static int stbi__hdr_test_core(stbi__context *s)
{
	const char *signature = "#?RADIANCE\n";
	int i;
	for (i = 0; signature[i]; ++i)
		if (stbi__get8(s) != signature[i])
			return 0;
	return 1;
}

static int stbi__hdr_test(stbi__context* s)
{
	int r = stbi__hdr_test_core(s);
	stbi__rewind(s);
	return r;
}

#define STBI__HDR_BUFLEN  1024
static char *stbi__hdr_gettoken(stbi__context *z, char *buffer)
{
	int len = 0;
	char c = '\0';

	c = (char)stbi__get8(z);

	while (!stbi__at_eof(z) && c != '\n') {
		buffer[len++] = c;
		if (len == STBI__HDR_BUFLEN - 1) {
			// flush to end of line
			while (!stbi__at_eof(z) && stbi__get8(z) != '\n')
				;
			break;
		}
		c = (char)stbi__get8(z);
	}

	buffer[len] = 0;
	return buffer;
}

static void stbi__hdr_convert(float *output, stbi_uc *input, int req_comp)
{
	if (input[3] != 0) {
		float f1;
		// Exponent
		f1 = (float)ldexp(1.0f, input[3] - (int)(128 + 8));
		if (req_comp <= 2)
			output[0] = (input[0] + input[1] + input[2]) * f1 / 3;
		else {
			output[0] = input[0] * f1;
			output[1] = input[1] * f1;
			output[2] = input[2] * f1;
		}
		if (req_comp == 2) output[1] = 1;
		if (req_comp == 4) output[3] = 1;
	}
	else {
		switch (req_comp) {
		case 4: output[3] = 1; /* fallthrough */
		case 3: output[0] = output[1] = output[2] = 0;
			break;
		case 2: output[1] = 1; /* fallthrough */
		case 1: output[0] = 0;
			break;
		}
	}
}

static float *stbi__hdr_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	char buffer[STBI__HDR_BUFLEN];
	char *token;
	int valid = 0;
	int width, height;
	stbi_uc *scanline;
	float *hdr_data;
	int len;
	unsigned char count, value;
	int i, j, k, c1, c2, z;


	// Check identifier
	if (strcmp(stbi__hdr_gettoken(s, buffer), "#?RADIANCE") != 0)
		return stbi__errpf("not HDR", "Corrupt HDR image");

	// Parse header
	for (;;) {
		token = stbi__hdr_gettoken(s, buffer);
		if (token[0] == 0) break;
		if (strcmp(token, "FORMAT=32-bit_rle_rgbe") == 0) valid = 1;
	}

	if (!valid)    return stbi__errpf("unsupported format", "Unsupported HDR format");

	// Parse width and height
	// can't use sscanf() if we're not using stdio!
	token = stbi__hdr_gettoken(s, buffer);
	if (strncmp(token, "-Y ", 3))  return stbi__errpf("unsupported data layout", "Unsupported HDR format");
	token += 3;
	height = (int)strtol(token, &token, 10);
	while (*token == ' ') ++token;
	if (strncmp(token, "+X ", 3))  return stbi__errpf("unsupported data layout", "Unsupported HDR format");
	token += 3;
	width = (int)strtol(token, NULL, 10);

	*x = width;
	*y = height;

	if (comp) *comp = 3;
	if (req_comp == 0) req_comp = 3;

	// Read data
	hdr_data = (float *)stbi__malloc(height * width * req_comp * sizeof(float));

	// Load image data
	// image data is stored as some number of sca
	if (width < 8 || width >= 32768) {
		// Read flat data
		for (j = 0; j < height; ++j) {
			for (i = 0; i < width; ++i) {
				stbi_uc rgbe[4];
			main_decode_loop:
				stbi__getn(s, rgbe, 4);
				stbi__hdr_convert(hdr_data + j * width * req_comp + i * req_comp, rgbe, req_comp);
			}
		}
	}
	else {
		// Read RLE-encoded data
		scanline = NULL;

		for (j = 0; j < height; ++j) {
			c1 = stbi__get8(s);
			c2 = stbi__get8(s);
			len = stbi__get8(s);
			if (c1 != 2 || c2 != 2 || (len & 0x80)) {
				// not run-length encoded, so we have to actually use THIS data as a decoded
				// pixel (note this can't be a valid pixel--one of RGB must be >= 128)
				stbi_uc rgbe[4];
				rgbe[0] = (stbi_uc)c1;
				rgbe[1] = (stbi_uc)c2;
				rgbe[2] = (stbi_uc)len;
				rgbe[3] = (stbi_uc)stbi__get8(s);
				stbi__hdr_convert(hdr_data, rgbe, req_comp);
				i = 1;
				j = 0;
				STBI_FREE(scanline);
				goto main_decode_loop; // yes, this makes no sense
			}
			len <<= 8;
			len |= stbi__get8(s);
			if (len != width) { STBI_FREE(hdr_data); STBI_FREE(scanline); return stbi__errpf("invalid decoded scanline length", "corrupt HDR"); }
			if (scanline == NULL) scanline = (stbi_uc *)stbi__malloc(width * 4);

			for (k = 0; k < 4; ++k) {
				i = 0;
				while (i < width) {
					count = stbi__get8(s);
					if (count > 128) {
						// Run
						value = stbi__get8(s);
						count -= 128;
						for (z = 0; z < count; ++z)
							scanline[i++ * 4 + k] = value;
					}
					else {
						// Dump
						for (z = 0; z < count; ++z)
							scanline[i++ * 4 + k] = stbi__get8(s);
					}
				}
			}
			for (i = 0; i < width; ++i)
				stbi__hdr_convert(hdr_data + (j*width + i)*req_comp, scanline + i * 4, req_comp);
		}
		STBI_FREE(scanline);
	}

	return hdr_data;
}

static int stbi__hdr_info(stbi__context *s, int *x, int *y, int *comp)
{
	char buffer[STBI__HDR_BUFLEN];
	char *token;
	int valid = 0;

	if (stbi__hdr_test(s) == 0) {
		stbi__rewind(s);
		return 0;
	}

	for (;;) {
		token = stbi__hdr_gettoken(s, buffer);
		if (token[0] == 0) break;
		if (strcmp(token, "FORMAT=32-bit_rle_rgbe") == 0) valid = 1;
	}

	if (!valid) {
		stbi__rewind(s);
		return 0;
	}
	token = stbi__hdr_gettoken(s, buffer);
	if (strncmp(token, "-Y ", 3)) {
		stbi__rewind(s);
		return 0;
	}
	token += 3;
	*y = (int)strtol(token, &token, 10);
	while (*token == ' ') ++token;
	if (strncmp(token, "+X ", 3)) {
		stbi__rewind(s);
		return 0;
	}
	token += 3;
	*x = (int)strtol(token, NULL, 10);
	*comp = 3;
	return 1;
}
#endif // STBI_NO_HDR

#ifndef STBI_NO_BMP
static int stbi__bmp_info(stbi__context *s, int *x, int *y, int *comp)
{
	void *p;
	stbi__bmp_data info;

	info.all_a = 255;
	p = stbi__bmp_parse_header(s, &info);
	stbi__rewind(s);
	if (p == NULL)
		return 0;
	*x = s->img_x;
	*y = s->img_y;
	*comp = info.ma ? 4 : 3;
	return 1;
}
#endif

#ifndef STBI_NO_PSD
static int stbi__psd_info(stbi__context *s, int *x, int *y, int *comp)
{
	int channelCount;
	if (stbi__get32be(s) != 0x38425053) {
		stbi__rewind(s);
		return 0;
	}
	if (stbi__get16be(s) != 1) {
		stbi__rewind(s);
		return 0;
	}
	stbi__skip(s, 6);
	channelCount = stbi__get16be(s);
	if (channelCount < 0 || channelCount > 16) {
		stbi__rewind(s);
		return 0;
	}
	*y = stbi__get32be(s);
	*x = stbi__get32be(s);
	if (stbi__get16be(s) != 8) {
		stbi__rewind(s);
		return 0;
	}
	if (stbi__get16be(s) != 3) {
		stbi__rewind(s);
		return 0;
	}
	*comp = 4;
	return 1;
}
#endif

#ifndef STBI_NO_PIC
static int stbi__pic_info(stbi__context *s, int *x, int *y, int *comp)
{
	int act_comp = 0, num_packets = 0, chained;
	stbi__pic_packet packets[10];

	if (!stbi__pic_is4(s, "\x53\x80\xF6\x34")) {
		stbi__rewind(s);
		return 0;
	}

	stbi__skip(s, 88);

	*x = stbi__get16be(s);
	*y = stbi__get16be(s);
	if (stbi__at_eof(s)) {
		stbi__rewind(s);
		return 0;
	}
	if ((*x) != 0 && (1 << 28) / (*x) < (*y)) {
		stbi__rewind(s);
		return 0;
	}

	stbi__skip(s, 8);

	do {
		stbi__pic_packet *packet;

		if (num_packets == sizeof(packets) / sizeof(packets[0]))
			return 0;

		packet = &packets[num_packets++];
		chained = stbi__get8(s);
		packet->size = stbi__get8(s);
		packet->type = stbi__get8(s);
		packet->channel = stbi__get8(s);
		act_comp |= packet->channel;

		if (stbi__at_eof(s)) {
			stbi__rewind(s);
			return 0;
		}
		if (packet->size != 8) {
			stbi__rewind(s);
			return 0;
		}
	} while (chained);

	*comp = (act_comp & 0x10 ? 4 : 3);

	return 1;
}
#endif

// *************************************************************************************************
// Portable Gray Map and Portable Pixel Map loader
// by Ken Miller
//
// PGM: http://netpbm.sourceforge.net/doc/pgm.html
// PPM: http://netpbm.sourceforge.net/doc/ppm.html
//
// Known limitations:
//    Does not support comments in the header section
//    Does not support ASCII image data (formats P2 and P3)
//    Does not support 16-bit-per-channel

#ifndef STBI_NO_PNM

static int      stbi__pnm_test(stbi__context *s)
{
	char p, t;
	p = (char)stbi__get8(s);
	t = (char)stbi__get8(s);
	if (p != 'P' || (t != '5' && t != '6')) {
		stbi__rewind(s);
		return 0;
	}
	return 1;
}

static stbi_uc *stbi__pnm_load(stbi__context *s, int *x, int *y, int *comp, int req_comp)
{
	stbi_uc *out;
	if (!stbi__pnm_info(s, (int *)&s->img_x, (int *)&s->img_y, (int *)&s->img_n))
		return 0;
	*x = s->img_x;
	*y = s->img_y;
	*comp = s->img_n;

	out = (stbi_uc *)stbi__malloc(s->img_n * s->img_x * s->img_y);
	if (!out) return stbi__errpuc("outofmem", "Out of memory");
	stbi__getn(s, out, s->img_n * s->img_x * s->img_y);

	if (req_comp && req_comp != s->img_n) {
		out = stbi__convert_format(out, s->img_n, req_comp, s->img_x, s->img_y);
		if (out == NULL) return out; // stbi__convert_format frees input on failure
	}
	return out;
}

static int      stbi__pnm_isspace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

static void     stbi__pnm_skip_whitespace(stbi__context *s, char *c)
{
	for (;;) {
		while (!stbi__at_eof(s) && stbi__pnm_isspace(*c))
			*c = (char)stbi__get8(s);

		if (stbi__at_eof(s) || *c != '#')
			break;

		while (!stbi__at_eof(s) && *c != '\n' && *c != '\r')
			*c = (char)stbi__get8(s);
	}
}

static int      stbi__pnm_isdigit(char c)
{
	return c >= '0' && c <= '9';
}

static int      stbi__pnm_getinteger(stbi__context *s, char *c)
{
	int value = 0;

	while (!stbi__at_eof(s) && stbi__pnm_isdigit(*c)) {
		value = value * 10 + (*c - '0');
		*c = (char)stbi__get8(s);
	}

	return value;
}

static int      stbi__pnm_info(stbi__context *s, int *x, int *y, int *comp)
{
	int maxv;
	char c, p, t;

	stbi__rewind(s);

	// Get identifier
	p = (char)stbi__get8(s);
	t = (char)stbi__get8(s);
	if (p != 'P' || (t != '5' && t != '6')) {
		stbi__rewind(s);
		return 0;
	}

	*comp = (t == '6') ? 3 : 1;  // '5' is 1-component .pgm; '6' is 3-component .ppm

	c = (char)stbi__get8(s);
	stbi__pnm_skip_whitespace(s, &c);

	*x = stbi__pnm_getinteger(s, &c); // read width
	stbi__pnm_skip_whitespace(s, &c);

	*y = stbi__pnm_getinteger(s, &c); // read height
	stbi__pnm_skip_whitespace(s, &c);

	maxv = stbi__pnm_getinteger(s, &c);  // read max value

	if (maxv > 255)
		return stbi__err("max value > 255", "PPM image not 8-bit");
	else
		return 1;
}
#endif

static int stbi__info_main(stbi__context *s, int *x, int *y, int *comp)
{
#ifndef STBI_NO_JPEG
	if (stbi__jpeg_info(s, x, y, comp)) return 1;
#endif

#ifndef STBI_NO_PNG
	if (stbi__png_info(s, x, y, comp))  return 1;
#endif

#ifndef STBI_NO_GIF
	if (stbi__gif_info(s, x, y, comp))  return 1;
#endif

#ifndef STBI_NO_BMP
	if (stbi__bmp_info(s, x, y, comp))  return 1;
#endif

#ifndef STBI_NO_PSD
	if (stbi__psd_info(s, x, y, comp))  return 1;
#endif

#ifndef STBI_NO_PIC
	if (stbi__pic_info(s, x, y, comp))  return 1;
#endif

#ifndef STBI_NO_PNM
	if (stbi__pnm_info(s, x, y, comp))  return 1;
#endif

#ifndef STBI_NO_HDR
	if (stbi__hdr_info(s, x, y, comp))  return 1;
#endif

	// test tga last because it's a crappy test!
#ifndef STBI_NO_TGA
	if (stbi__tga_info(s, x, y, comp))
		return 1;
#endif
	return stbi__err("unknown image type", "Image not of any known type, or corrupt");
}

#ifndef STBI_NO_STDIO
STBIDEF int stbi_info(char const *filename, int *x, int *y, int *comp)
{
	FILE *f = stbi__fopen(filename, "rb");
	int result;
	if (!f) return stbi__err("can't fopen", "Unable to open file");
	result = stbi_info_from_file(f, x, y, comp);
	fclose(f);
	return result;
}

STBIDEF int stbi_info_from_file(FILE *f, int *x, int *y, int *comp)
{
	int r;
	stbi__context s;
	long pos = ftell(f);
	stbi__start_file(&s, f);
	r = stbi__info_main(&s, x, y, comp);
	fseek(f, pos, SEEK_SET);
	return r;
}
#endif // !STBI_NO_STDIO

STBIDEF int stbi_info_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp)
{
	stbi__context s;
	stbi__start_mem(&s, buffer, len);
	return stbi__info_main(&s, x, y, comp);
}

STBIDEF int stbi_info_from_callbacks(stbi_io_callbacks const *c, void *user, int *x, int *y, int *comp)
{
	stbi__context s;
	stbi__start_callbacks(&s, (stbi_io_callbacks *)c, user);
	return stbi__info_main(&s, x, y, comp);
}

#endif // STB_IMAGE_IMPLEMENTATION

/*
revision history:
2.12  (2016-04-02) fix typo in 2.11 PSD fix that caused crashes
2.11  (2016-04-02) allocate large structures on the stack
remove white matting for transparent PSD
fix reported channel count for PNG & BMP
re-enable SSE2 in non-gcc 64-bit
support RGB-formatted JPEG
read 16-bit PNGs (only as 8-bit)
2.10  (2016-01-22) avoid warning introduced in 2.09 by STBI_REALLOC_SIZED
2.09  (2016-01-16) allow comments in PNM files
16-bit-per-pixel TGA (not bit-per-component)
info() for TGA could break due to .hdr handling
info() for BMP to shares code instead of sloppy parse
can use STBI_REALLOC_SIZED if allocator doesn't support realloc
code cleanup
2.08  (2015-09-13) fix to 2.07 cleanup, reading RGB PSD as RGBA
2.07  (2015-09-13) fix compiler warnings
partial animated GIF support
limited 16-bpc PSD support
#ifdef unused functions
bug with < 92 byte PIC,PNM,HDR,TGA
2.06  (2015-04-19) fix bug where PSD returns wrong '*comp' value
2.05  (2015-04-19) fix bug in progressive JPEG handling, fix warning
2.04  (2015-04-15) try to re-enable SIMD on MinGW 64-bit
2.03  (2015-04-12) extra corruption checking (mmozeiko)
stbi_set_flip_vertically_on_load (nguillemot)
fix NEON support; fix mingw support
2.02  (2015-01-19) fix incorrect assert, fix warning
2.01  (2015-01-17) fix various warnings; suppress SIMD on gcc 32-bit without -msse2
2.00b (2014-12-25) fix STBI_MALLOC in progressive JPEG
2.00  (2014-12-25) optimize JPG, including x86 SSE2 & NEON SIMD (ryg)
progressive JPEG (stb)
PGM/PPM support (Ken Miller)
STBI_MALLOC,STBI_REALLOC,STBI_FREE
GIF bugfix -- seemingly never worked
STBI_NO_*, STBI_ONLY_*
1.48  (2014-12-14) fix incorrectly-named assert()
1.47  (2014-12-14) 1/2/4-bit PNG support, both direct and paletted (Omar Cornut & stb)
optimize PNG (ryg)
fix bug in interlaced PNG with user-specified channel count (stb)
1.46  (2014-08-26)
fix broken tRNS chunk (colorkey-style transparency) in non-paletted PNG
1.45  (2014-08-16)
fix MSVC-ARM internal compiler error by wrapping malloc
1.44  (2014-08-07)
various warning fixes from Ronny Chevalier
1.43  (2014-07-15)
fix MSVC-only compiler problem in code changed in 1.42
1.42  (2014-07-09)
don't define _CRT_SECURE_NO_WARNINGS (affects user code)
fixes to stbi__cleanup_jpeg path
added STBI_ASSERT to avoid requiring assert.h
1.41  (2014-06-25)
fix search&replace from 1.36 that messed up comments/error messages
1.40  (2014-06-22)
fix gcc struct-initialization warning
1.39  (2014-06-15)
fix to TGA optimization when req_comp != number of components in TGA;
fix to GIF loading because BMP wasn't rewinding (whoops, no GIFs in my test suite)
add support for BMP version 5 (more ignored fields)
1.38  (2014-06-06)
suppress MSVC warnings on integer casts truncating values
fix accidental rename of 'skip' field of I/O
1.37  (2014-06-04)
remove duplicate typedef
1.36  (2014-06-03)
convert to header file single-file library
if de-iphone isn't set, load iphone images color-swapped instead of returning NULL
1.35  (2014-05-27)
various warnings
fix broken STBI_SIMD path
fix bug where stbi_load_from_file no longer left file pointer in correct place
fix broken non-easy path for 32-bit BMP (possibly never used)
TGA optimization by Arseny Kapoulkine
1.34  (unknown)
use STBI_NOTUSED in stbi__resample_row_generic(), fix one more leak in tga failure case
1.33  (2011-07-14)
make stbi_is_hdr work in STBI_NO_HDR (as specified), minor compiler-friendly improvements
1.32  (2011-07-13)
support for "info" function for all supported filetypes (SpartanJ)
1.31  (2011-06-20)
a few more leak fixes, bug in PNG handling (SpartanJ)
1.30  (2011-06-11)
added ability to load files via callbacks to accomidate custom input streams (Ben Wenger)
removed deprecated format-specific test/load functions
removed support for installable file formats (stbi_loader) -- would have been broken for IO callbacks anyway
error cases in bmp and tga give messages and don't leak (Raymond Barbiero, grisha)
fix inefficiency in decoding 32-bit BMP (David Woo)
1.29  (2010-08-16)
various warning fixes from Aurelien Pocheville
1.28  (2010-08-01)
fix bug in GIF palette transparency (SpartanJ)
1.27  (2010-08-01)
cast-to-stbi_uc to fix warnings
1.26  (2010-07-24)
fix bug in file buffering for PNG reported by SpartanJ
1.25  (2010-07-17)
refix trans_data warning (Won Chun)
1.24  (2010-07-12)
perf improvements reading from files on platforms with lock-heavy fgetc()
minor perf improvements for jpeg
deprecated type-specific functions so we'll get feedback if they're needed
attempt to fix trans_data warning (Won Chun)
1.23    fixed bug in iPhone support
1.22  (2010-07-10)
removed image *writing* support
stbi_info support from Jetro Lauha
GIF support from Jean-Marc Lienher
iPhone PNG-extensions from James Brown
warning-fixes from Nicolas Schulz and Janez Zemva (i.stbi__err. Janez (U+017D)emva)
1.21    fix use of 'stbi_uc' in header (reported by jon blow)
1.20    added support for Softimage PIC, by Tom Seddon
1.19    bug in interlaced PNG corruption check (found by ryg)
1.18  (2008-08-02)
fix a threading bug (local mutable static)
1.17    support interlaced PNG
1.16    major bugfix - stbi__convert_format converted one too many pixels
1.15    initialize some fields for thread safety
1.14    fix threadsafe conversion bug
header-file-only version (#define STBI_HEADER_FILE_ONLY before including)
1.13    threadsafe
1.12    const qualifiers in the API
1.11    Support installable IDCT, colorspace conversion routines
1.10    Fixes for 64-bit (don't use "unsigned long")
optimized upsampling by Fabian "ryg" Giesen
1.09    Fix format-conversion for PSD code (bad global variables!)
1.08    Thatcher Ulrich's PSD code integrated by Nicolas Schulz
1.07    attempt to fix C++ warning/errors again
1.06    attempt to fix C++ warning/errors again
1.05    fix TGA loading to return correct *comp and use good luminance calc
1.04    default float alpha is 1, not 255; use 'void *' for stbi_image_free
1.03    bugfixes to STBI_NO_STDIO, STBI_NO_HDR
1.02    support for (subset of) HDR files, float interface for preferred access to them
1.01    fix bug: possible bug in handling right-side up bmps... not sure
fix bug: the stbi__bmp_load() and stbi__tga_load() functions didn't work at all
1.00    interface to zlib that skips zlib header
0.99    correct handling of alpha in palette
0.98    TGA loader by lonesock; dynamically add loaders (untested)
0.97    jpeg errors on too large a file; also catch another malloc failure
0.96    fix detection of invalid v value - particleman@mollyrocket forum
0.95    during header scan, seek to markers in case of padding
0.94    STBI_NO_STDIO to disable stdio usage; rename all #defines the same
0.93    handle jpegtran output; verbose errors
0.92    read 4,8,16,24,32-bit BMP files of several formats
0.91    output 24-bit Windows 3.0 BMP files
0.90    fix a few more warnings; bump version number to approach 1.0
0.61    bugfixes due to Marc LeBlanc, Christopher Lloyd
0.60    fix compiling as c++
0.59    fix warnings: merge Dave Moore's -Wall fixes
0.58    fix bug: zlib uncompressed mode len/nlen was wrong endian
0.57    fix bug: jpg last huffman symbol before marker was >9 bits but less than 16 available
0.56    fix bug: zlib uncompressed mode len vs. nlen
0.55    fix bug: restart_interval not initialized to 0
0.54    allow NULL for 'int *comp'
0.53    fix bug in png 3->4; speedup png decoding
0.52    png handles req_comp=3,4 directly; minor cleanup; jpeg comments
0.51    obey req_comp requests, 1-component jpegs return as 1-component,
on 'test' only check type, not whether we support this variant
0.50  (2006-11-19)
first released version
*/

// Embedded stb_truetype.h
#define STB_TRUETYPE_IMPLEMENTATION

// stb_truetype.h - v1.11 - public domain
// authored from 2009-2015 by Sean Barrett / RAD Game Tools
//
//   This library processes TrueType files:
//        parse files
//        extract glyph metrics
//        extract glyph shapes
//        render glyphs to one-channel bitmaps with antialiasing (box filter)
//
//   Todo:
//        non-MS cmaps
//        crashproof on bad data
//        hinting? (no longer patented)
//        cleartype-style AA?
//        optimize: use simple memory allocator for intermediates
//        optimize: build edge-list directly from curves
//        optimize: rasterize directly from curves?
//
// ADDITIONAL CONTRIBUTORS
//
//   Mikko Mononen: compound shape support, more cmap formats
//   Tor Andersson: kerning, subpixel rendering
//
//   Misc other:
//       Ryan Gordon
//       Simon Glass
//
//   Bug/warning reports/fixes:
//       "Zer" on mollyrocket (with fix)
//       Cass Everitt
//       stoiko (Haemimont Games)
//       Brian Hook 
//       Walter van Niftrik
//       David Gow
//       David Given
//       Ivan-Assen Ivanov
//       Anthony Pesch
//       Johan Duparc
//       Hou Qiming
//       Fabian "ryg" Giesen
//       Martins Mozeiko
//       Cap Petschulat
//       Omar Cornut
//       github:aloucks
//       Peter LaValle
//       Sergey Popov
//       Giumo X. Clanjor
//       Higor Euripedes
//       Thomas Fields
//       Derek Vinyard
//
// VERSION HISTORY
//
//   1.11 (2016-04-02) fix unused-variable warning
//   1.10 (2016-04-02) user-defined fabs(); rare memory leak; remove duplicate typedef
//   1.09 (2016-01-16) warning fix; avoid crash on outofmem; use allocation userdata properly
//   1.08 (2015-09-13) document stbtt_Rasterize(); fixes for vertical & horizontal edges
//   1.07 (2015-08-01) allow PackFontRanges to accept arrays of sparse codepoints;
//                     variant PackFontRanges to pack and render in separate phases;
//                     fix stbtt_GetFontOFfsetForIndex (never worked for non-0 input?);
//                     fixed an assert() bug in the new rasterizer
//                     replace assert() with STBTT_assert() in new rasterizer
//   1.06 (2015-07-14) performance improvements (~35% faster on x86 and x64 on test machine)
//                     also more precise AA rasterizer, except if shapes overlap
//                     remove need for STBTT_sort
//   1.05 (2015-04-15) fix misplaced definitions for STBTT_STATIC
//   1.04 (2015-04-15) typo in example
//   1.03 (2015-04-12) STBTT_STATIC, fix memory leak in new packing, various fixes
//
//   Full history can be found at the end of this file.
//
// LICENSE
//
//   This software is dual-licensed to the public domain and under the following
//   license: you are granted a perpetual, irrevocable license to copy, modify,
//   publish, and distribute this file as you see fit.
//
// USAGE
//
//   Include this file in whatever places neeed to refer to it. In ONE C/C++
//   file, write:
//      #define STB_TRUETYPE_IMPLEMENTATION
//   before the #include of this file. This expands out the actual
//   implementation into that C/C++ file.
//
//   To make the implementation private to the file that generates the implementation,
//      #define STBTT_STATIC
//
//   Simple 3D API (don't ship this, but it's fine for tools and quick start)
//           stbtt_BakeFontBitmap()               -- bake a font to a bitmap for use as texture
//           stbtt_GetBakedQuad()                 -- compute quad to draw for a given char
//
//   Improved 3D API (more shippable):
//           #include "stb_rect_pack.h"           -- optional, but you really want it
//           stbtt_PackBegin()
//           stbtt_PackSetOversample()            -- for improved quality on small fonts
//           stbtt_PackFontRanges()               -- pack and renders
//           stbtt_PackEnd()
//           stbtt_GetPackedQuad()
//
//   "Load" a font file from a memory buffer (you have to keep the buffer loaded)
//           stbtt_InitFont()
//           stbtt_GetFontOffsetForIndex()        -- use for TTC font collections
//
//   Render a unicode codepoint to a bitmap
//           stbtt_GetCodepointBitmap()           -- allocates and returns a bitmap
//           stbtt_MakeCodepointBitmap()          -- renders into bitmap you provide
//           stbtt_GetCodepointBitmapBox()        -- how big the bitmap must be
//
//   Character advance/positioning
//           stbtt_GetCodepointHMetrics()
//           stbtt_GetFontVMetrics()
//           stbtt_GetCodepointKernAdvance()
//
//   Starting with version 1.06, the rasterizer was replaced with a new,
//   faster and generally-more-precise rasterizer. The new rasterizer more
//   accurately measures pixel coverage for anti-aliasing, except in the case
//   where multiple shapes overlap, in which case it overestimates the AA pixel
//   coverage. Thus, anti-aliasing of intersecting shapes may look wrong. If
//   this turns out to be a problem, you can re-enable the old rasterizer with
//        #define STBTT_RASTERIZER_VERSION 1
//   which will incur about a 15% speed hit.
//
// ADDITIONAL DOCUMENTATION
//
//   Immediately after this block comment are a series of sample programs.
//
//   After the sample programs is the "header file" section. This section
//   includes documentation for each API function.
//
//   Some important concepts to understand to use this library:
//
//      Codepoint
//         Characters are defined by unicode codepoints, e.g. 65 is
//         uppercase A, 231 is lowercase c with a cedilla, 0x7e30 is
//         the hiragana for "ma".
//
//      Glyph
//         A visual character shape (every codepoint is rendered as
//         some glyph)
//
//      Glyph index
//         A font-specific integer ID representing a glyph
//
//      Baseline
//         Glyph shapes are defined relative to a baseline, which is the
//         bottom of uppercase characters. Characters extend both above
//         and below the baseline.
//
//      Current Point
//         As you draw text to the screen, you keep track of a "current point"
//         which is the origin of each character. The current point's vertical
//         position is the baseline. Even "baked fonts" use this model.
//
//      Vertical Font Metrics
//         The vertical qualities of the font, used to vertically position
//         and space the characters. See docs for stbtt_GetFontVMetrics.
//
//      Font Size in Pixels or Points
//         The preferred interface for specifying font sizes in stb_truetype
//         is to specify how tall the font's vertical extent should be in pixels.
//         If that sounds good enough, skip the next paragraph.
//
//         Most font APIs instead use "points", which are a common typographic
//         measurement for describing font size, defined as 72 points per inch.
//         stb_truetype provides a point API for compatibility. However, true
//         "per inch" conventions don't make much sense on computer displays
//         since they different monitors have different number of pixels per
//         inch. For example, Windows traditionally uses a convention that
//         there are 96 pixels per inch, thus making 'inch' measurements have
//         nothing to do with inches, and thus effectively defining a point to
//         be 1.333 pixels. Additionally, the TrueType font data provides
//         an explicit scale factor to scale a given font's glyphs to points,
//         but the author has observed that this scale factor is often wrong
//         for non-commercial fonts, thus making fonts scaled in points
//         according to the TrueType spec incoherently sized in practice.
//
// ADVANCED USAGE
//
//   Quality:
//
//    - Use the functions with Subpixel at the end to allow your characters
//      to have subpixel positioning. Since the font is anti-aliased, not
//      hinted, this is very import for quality. (This is not possible with
//      baked fonts.)
//
//    - Kerning is now supported, and if you're supporting subpixel rendering
//      then kerning is worth using to give your text a polished look.
//
//   Performance:
//
//    - Convert Unicode codepoints to glyph indexes and operate on the glyphs;
//      if you don't do this, stb_truetype is forced to do the conversion on
//      every call.
//
//    - There are a lot of memory allocations. We should modify it to take
//      a temp buffer and allocate from the temp buffer (without freeing),
//      should help performance a lot.
//
// NOTES
//
//   The system uses the raw data found in the .ttf file without changing it
//   and without building auxiliary data structures. This is a bit inefficient
//   on little-endian systems (the data is big-endian), but assuming you're
//   caching the bitmaps or glyph shapes this shouldn't be a big deal.
//
//   It appears to be very hard to programmatically determine what font a
//   given file is in a general way. I provide an API for this, but I don't
//   recommend it.
//
//
// SOURCE STATISTICS (based on v0.6c, 2050 LOC)
//
//   Documentation & header file        520 LOC  \___ 660 LOC documentation
//   Sample code                        140 LOC  /
//   Truetype parsing                   620 LOC  ---- 620 LOC TrueType
//   Software rasterization             240 LOC  \                           .
//   Curve tesselation                  120 LOC   \__ 550 LOC Bitmap creation
//   Bitmap management                  100 LOC   /
//   Baked bitmap interface              70 LOC  /
//   Font name matching & access        150 LOC  ---- 150 
//   C runtime library abstraction       60 LOC  ----  60
//
//
// PERFORMANCE MEASUREMENTS FOR 1.06:
//
//                      32-bit     64-bit
//   Previous release:  8.83 s     7.68 s
//   Pool allocations:  7.72 s     6.34 s
//   Inline sort     :  6.54 s     5.65 s
//   New rasterizer  :  5.63 s     5.00 s

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////
////  SAMPLE PROGRAMS
////
//
//  Incomplete text-in-3d-api example, which draws quads properly aligned to be lossless
//
#if 0
#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "stb_truetype.h"

unsigned char ttf_buffer[1 << 20];
unsigned char temp_bitmap[512 * 512];

stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
GLuint ftex;

void my_stbtt_initfont(void)
{
	fread(ttf_buffer, 1, 1 << 20, fopen("c:/windows/fonts/times.ttf", "rb"));
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
	// can free ttf_buffer at this point
	glGenTextures(1, &ftex);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	// can free temp_bitmap at this point
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void my_stbtt_print(float x, float y, char *text)
{
	// assume orthographic projection with units = screen pixels, origin at top left
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glBegin(GL_QUADS);
	while (*text) {
		if (*text >= 32 && *text < 128) {
			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(cdata, 512, 512, *text - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
			glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y0);
			glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y0);
			glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y1);
			glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y1);
		}
		++text;
	}
	glEnd();
}
#endif
//
//
//////////////////////////////////////////////////////////////////////////////
//
// Complete program (this compiles): get a single bitmap, print as ASCII art
//
#if 0
#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "stb_truetype.h"

char ttf_buffer[1 << 25];

int main(int argc, char **argv)
{
	stbtt_fontinfo font;
	unsigned char *bitmap;
	int w, h, i, j, c = (argc > 1 ? atoi(argv[1]) : 'a'), s = (argc > 2 ? atoi(argv[2]) : 20);

	fread(ttf_buffer, 1, 1 << 25, fopen(argc > 3 ? argv[3] : "c:/windows/fonts/arialbd.ttf", "rb"));

	stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
	bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0, 0);

	for (j = 0; j < h; ++j) {
		for (i = 0; i < w; ++i)
			putchar(" .:ioVM@"[bitmap[j*w + i] >> 5]);
		putchar('\n');
	}
	return 0;
}
#endif 
//
// Output:
//
//     .ii.
//    @@@@@@.
//   V@Mio@@o
//   :i.  V@V
//     :oM@@M
//   :@@@MM@M
//   @@o  o@M
//  :@@.  M@M
//   @@@o@@@@
//   :M@@V:@@.
//  
//////////////////////////////////////////////////////////////////////////////
// 
// Complete program: print "Hello World!" banner, with bugs
//
#if 0
char buffer[24 << 20];
unsigned char screen[20][79];

int main(int arg, char **argv)
{
	stbtt_fontinfo font;
	int i, j, ascent, baseline, ch = 0;
	float scale, xpos = 2; // leave a little padding in case the character extends left
	char *text = "Heljo World!"; // intentionally misspelled to show 'lj' brokenness

	fread(buffer, 1, 1000000, fopen("c:/windows/fonts/arialbd.ttf", "rb"));
	stbtt_InitFont(&font, buffer, 0);

	scale = stbtt_ScaleForPixelHeight(&font, 15);
	stbtt_GetFontVMetrics(&font, &ascent, 0, 0);
	baseline = (int)(ascent*scale);

	while (text[ch]) {
		int advance, lsb, x0, y0, x1, y1;
		float x_shift = xpos - (float)floor(xpos);
		stbtt_GetCodepointHMetrics(&font, text[ch], &advance, &lsb);
		stbtt_GetCodepointBitmapBoxSubpixel(&font, text[ch], scale, scale, x_shift, 0, &x0, &y0, &x1, &y1);
		stbtt_MakeCodepointBitmapSubpixel(&font, &screen[baseline + y0][(int)xpos + x0], x1 - x0, y1 - y0, 79, scale, scale, x_shift, 0, text[ch]);
		// note that this stomps the old data, so where character boxes overlap (e.g. 'lj') it's wrong
		// because this API is really for baking character bitmaps into textures. if you want to render
		// a sequence of characters, you really need to render each bitmap to a temp buffer, then
		// "alpha blend" that into the working buffer
		xpos += (advance * scale);
		if (text[ch + 1])
			xpos += scale*stbtt_GetCodepointKernAdvance(&font, text[ch], text[ch + 1]);
		++ch;
	}

	for (j = 0; j < 20; ++j) {
		for (i = 0; i < 78; ++i)
			putchar(" .:ioVM@"[screen[j][i] >> 5]);
		putchar('\n');
	}

	return 0;
}
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////
////   INTEGRATION WITH YOUR CODEBASE
////
////   The following sections allow you to supply alternate definitions
////   of C library functions used by stb_truetype.

#ifdef STB_TRUETYPE_IMPLEMENTATION
// #define your own (u)stbtt_int8/16/32 before including to override this
#ifndef stbtt_uint8
typedef unsigned char   stbtt_uint8;
typedef signed   char   stbtt_int8;
typedef unsigned short  stbtt_uint16;
typedef signed   short  stbtt_int16;
typedef unsigned int    stbtt_uint32;
typedef signed   int    stbtt_int32;
#endif

typedef char stbtt__check_size32[sizeof(stbtt_int32) == 4 ? 1 : -1];
typedef char stbtt__check_size16[sizeof(stbtt_int16) == 2 ? 1 : -1];

// #define your own STBTT_ifloor/STBTT_iceil() to avoid math.h
#ifndef STBTT_ifloor
#include <math.h>
#define STBTT_ifloor(x)   ((int) floor(x))
#define STBTT_iceil(x)    ((int) ceil(x))
#endif

#ifndef STBTT_sqrt
#include <math.h>
#define STBTT_sqrt(x)      sqrt(x)
#endif

#ifndef STBTT_fabs
#include <math.h>
#define STBTT_fabs(x)      fabs(x)
#endif

// #define your own functions "STBTT_malloc" / "STBTT_free" to avoid malloc.h
#ifndef STBTT_malloc
#include <stdlib.h>
#define STBTT_malloc(x,u)  ((void)(u),malloc(x))
#define STBTT_free(x,u)    ((void)(u),free(x))
#endif

#ifndef STBTT_assert
#include <assert.h>
#define STBTT_assert(x)    assert(x)
#endif

#ifndef STBTT_strlen
#include <string.h>
#define STBTT_strlen(x)    strlen(x)
#endif

#ifndef STBTT_memcpy
#include <memory.h>
#define STBTT_memcpy       memcpy
#define STBTT_memset       memset
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////
////   INTERFACE
////
////

#ifndef __STB_INCLUDE_STB_TRUETYPE_H__
#define __STB_INCLUDE_STB_TRUETYPE_H__

#ifdef STBTT_STATIC
#define STBTT_DEF static
#else
#define STBTT_DEF extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//////////////////////////////////////////////////////////////////////////////
	//
	// TEXTURE BAKING API
	//
	// If you use this API, you only have to call two functions ever.
	//

	typedef struct
	{
		unsigned short x0, y0, x1, y1; // coordinates of bbox in bitmap
		float xoff, yoff, xadvance;
	} stbtt_bakedchar;

	STBTT_DEF int stbtt_BakeFontBitmap(const unsigned char *data, int offset,  // font location (use offset=0 for plain .ttf)
		float pixel_height,                     // height of font in pixels
		unsigned char *pixels, int pw, int ph,  // bitmap to be filled in
		int first_char, int num_chars,          // characters to bake
		stbtt_bakedchar *chardata);             // you allocate this, it's num_chars long
	// if return is positive, the first unused row of the bitmap
	// if return is negative, returns the negative of the number of characters that fit
	// if return is 0, no characters fit and no rows were used
	// This uses a very crappy packing.

	typedef struct
	{
		float x0, y0, s0, t0; // top-left
		float x1, y1, s1, t1; // bottom-right
	} stbtt_aligned_quad;

	STBTT_DEF void stbtt_GetBakedQuad(stbtt_bakedchar *chardata, int pw, int ph,  // same data as above
		int char_index,             // character to display
		float *xpos, float *ypos,   // pointers to current position in screen pixel space
		stbtt_aligned_quad *q,      // output: quad to draw
		int opengl_fillrule);       // true if opengl fill rule; false if DX9 or earlier
	// Call GetBakedQuad with char_index = 'character - first_char', and it
	// creates the quad you need to draw and advances the current position.
	//
	// The coordinate system used assumes y increases downwards.
	//
	// Characters will extend both above and below the current position;
	// see discussion of "BASELINE" above.
	//
	// It's inefficient; you might want to c&p it and optimize it.



	//////////////////////////////////////////////////////////////////////////////
	//
	// NEW TEXTURE BAKING API
	//
	// This provides options for packing multiple fonts into one atlas, not
	// perfectly but better than nothing.

	typedef struct
	{
		unsigned short x0, y0, x1, y1; // coordinates of bbox in bitmap
		float xoff, yoff, xadvance;
		float xoff2, yoff2;
	} stbtt_packedchar;

	typedef struct stbtt_pack_context stbtt_pack_context;
	typedef struct stbtt_fontinfo stbtt_fontinfo;
#ifndef STB_RECT_PACK_VERSION
	typedef struct stbrp_rect stbrp_rect;
#endif

	STBTT_DEF int  stbtt_PackBegin(stbtt_pack_context *spc, unsigned char *pixels, int width, int height, int stride_in_bytes, int padding, void *alloc_context);
	// Initializes a packing context stored in the passed-in stbtt_pack_context.
	// Future calls using this context will pack characters into the bitmap passed
	// in here: a 1-channel bitmap that is weight x height. stride_in_bytes is
	// the distance from one row to the next (or 0 to mean they are packed tightly
	// together). "padding" is the amount of padding to leave between each
	// character (normally you want '1' for bitmaps you'll use as textures with
	// bilinear filtering).
	//
	// Returns 0 on failure, 1 on success.

	STBTT_DEF void stbtt_PackEnd(stbtt_pack_context *spc);
	// Cleans up the packing context and frees all memory.

#define STBTT_POINT_SIZE(x)   (-(x))

	STBTT_DEF int  stbtt_PackFontRange(stbtt_pack_context *spc, unsigned char *fontdata, int font_index, float font_size,
		int first_unicode_char_in_range, int num_chars_in_range, stbtt_packedchar *chardata_for_range);
	// Creates character bitmaps from the font_index'th font found in fontdata (use
	// font_index=0 if you don't know what that is). It creates num_chars_in_range
	// bitmaps for characters with unicode values starting at first_unicode_char_in_range
	// and increasing. Data for how to render them is stored in chardata_for_range;
	// pass these to stbtt_GetPackedQuad to get back renderable quads.
	//
	// font_size is the full height of the character from ascender to descender,
	// as computed by stbtt_ScaleForPixelHeight. To use a point size as computed
	// by stbtt_ScaleForMappingEmToPixels, wrap the point size in STBTT_POINT_SIZE()
	// and pass that result as 'font_size':
	//       ...,                  20 , ... // font max minus min y is 20 pixels tall
	//       ..., STBTT_POINT_SIZE(20), ... // 'M' is 20 pixels tall

	typedef struct
	{
		float font_size;
		int first_unicode_codepoint_in_range;  // if non-zero, then the chars are continuous, and this is the first codepoint
		int *array_of_unicode_codepoints;       // if non-zero, then this is an array of unicode codepoints
		int num_chars;
		stbtt_packedchar *chardata_for_range; // output
		unsigned char h_oversample, v_oversample; // don't set these, they're used internally
	} stbtt_pack_range;

	STBTT_DEF int  stbtt_PackFontRanges(stbtt_pack_context *spc, unsigned char *fontdata, int font_index, stbtt_pack_range *ranges, int num_ranges);
	// Creates character bitmaps from multiple ranges of characters stored in
	// ranges. This will usually create a better-packed bitmap than multiple
	// calls to stbtt_PackFontRange. Note that you can call this multiple
	// times within a single PackBegin/PackEnd.

	STBTT_DEF void stbtt_PackSetOversampling(stbtt_pack_context *spc, unsigned int h_oversample, unsigned int v_oversample);
	// Oversampling a font increases the quality by allowing higher-quality subpixel
	// positioning, and is especially valuable at smaller text sizes.
	//
	// This function sets the amount of oversampling for all following calls to
	// stbtt_PackFontRange(s) or stbtt_PackFontRangesGatherRects for a given
	// pack context. The default (no oversampling) is achieved by h_oversample=1
	// and v_oversample=1. The total number of pixels required is
	// h_oversample*v_oversample larger than the default; for example, 2x2
	// oversampling requires 4x the storage of 1x1. For best results, render
	// oversampled textures with bilinear filtering. Look at the readme in
	// stb/tests/oversample for information about oversampled fonts
	//
	// To use with PackFontRangesGather etc., you must set it before calls
	// call to PackFontRangesGatherRects.

	STBTT_DEF void stbtt_GetPackedQuad(stbtt_packedchar *chardata, int pw, int ph,  // same data as above
		int char_index,             // character to display
		float *xpos, float *ypos,   // pointers to current position in screen pixel space
		stbtt_aligned_quad *q,      // output: quad to draw
		int align_to_integer);

	STBTT_DEF int  stbtt_PackFontRangesGatherRects(stbtt_pack_context *spc, stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects);
	STBTT_DEF void stbtt_PackFontRangesPackRects(stbtt_pack_context *spc, stbrp_rect *rects, int num_rects);
	STBTT_DEF int  stbtt_PackFontRangesRenderIntoRects(stbtt_pack_context *spc, stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects);
	// Calling these functions in sequence is roughly equivalent to calling
	// stbtt_PackFontRanges(). If you more control over the packing of multiple
	// fonts, or if you want to pack custom data into a font texture, take a look
	// at the source to of stbtt_PackFontRanges() and create a custom version 
	// using these functions, e.g. call GatherRects multiple times,
	// building up a single array of rects, then call PackRects once,
	// then call RenderIntoRects repeatedly. This may result in a
	// better packing than calling PackFontRanges multiple times
	// (or it may not).

	// this is an opaque structure that you shouldn't mess with which holds
	// all the context needed from PackBegin to PackEnd.
	struct stbtt_pack_context {
		void *user_allocator_context;
		void *pack_info;
		int   width;
		int   height;
		int   stride_in_bytes;
		int   padding;
		unsigned int   h_oversample, v_oversample;
		unsigned char *pixels;
		void  *nodes;
	};

	//////////////////////////////////////////////////////////////////////////////
	//
	// FONT LOADING
	//
	//

	STBTT_DEF int stbtt_GetFontOffsetForIndex(const unsigned char *data, int index);
	// Each .ttf/.ttc file may have more than one font. Each font has a sequential
	// index number starting from 0. Call this function to get the font offset for
	// a given index; it returns -1 if the index is out of range. A regular .ttf
	// file will only define one font and it always be at offset 0, so it will
	// return '0' for index 0, and -1 for all other indices. You can just skip
	// this step if you know it's that kind of font.


	// The following structure is defined publically so you can declare one on
	// the stack or as a global or etc, but you should treat it as opaque.
	struct stbtt_fontinfo
	{
		void           * userdata;
		unsigned char  * data;              // pointer to .ttf file
		int              fontstart;         // offset of start of font

		int numGlyphs;                     // number of glyphs, needed for range checking

		int loca, head, glyf, hhea, hmtx, kern; // table locations as offset from start of .ttf
		int index_map;                     // a cmap mapping for our chosen character encoding
		int indexToLocFormat;              // format needed to map from glyph index to glyph
	};

	STBTT_DEF int stbtt_InitFont(stbtt_fontinfo *info, const unsigned char *data, int offset);
	// Given an offset into the file that defines a font, this function builds
	// the necessary cached info for the rest of the system. You must allocate
	// the stbtt_fontinfo yourself, and stbtt_InitFont will fill it out. You don't
	// need to do anything special to free it, because the contents are pure
	// value data with no additional data structures. Returns 0 on failure.


	//////////////////////////////////////////////////////////////////////////////
	//
	// CHARACTER TO GLYPH-INDEX CONVERSIOn

	STBTT_DEF int stbtt_FindGlyphIndex(const stbtt_fontinfo *info, int unicode_codepoint);
	// If you're going to perform multiple operations on the same character
	// and you want a speed-up, call this function with the character you're
	// going to process, then use glyph-based functions instead of the
	// codepoint-based functions.


	//////////////////////////////////////////////////////////////////////////////
	//
	// CHARACTER PROPERTIES
	//

	STBTT_DEF float stbtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float pixels);
	// computes a scale factor to produce a font whose "height" is 'pixels' tall.
	// Height is measured as the distance from the highest ascender to the lowest
	// descender; in other words, it's equivalent to calling stbtt_GetFontVMetrics
	// and computing:
	//       scale = pixels / (ascent - descent)
	// so if you prefer to measure height by the ascent only, use a similar calculation.

	STBTT_DEF float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo *info, float pixels);
	// computes a scale factor to produce a font whose EM size is mapped to
	// 'pixels' tall. This is probably what traditional APIs compute, but
	// I'm not positive.

	STBTT_DEF void stbtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap);
	// ascent is the coordinate above the baseline the font extends; descent
	// is the coordinate below the baseline the font extends (i.e. it is typically negative)
	// lineGap is the spacing between one row's descent and the next row's ascent...
	// so you should advance the vertical position by "*ascent - *descent + *lineGap"
	//   these are expressed in unscaled coordinates, so you must multiply by
	//   the scale factor for a given size

	STBTT_DEF void stbtt_GetFontBoundingBox(const stbtt_fontinfo *info, int *x0, int *y0, int *x1, int *y1);
	// the bounding box around all possible characters

	STBTT_DEF void stbtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing);
	// leftSideBearing is the offset from the current horizontal position to the left edge of the character
	// advanceWidth is the offset from the current horizontal position to the next horizontal position
	//   these are expressed in unscaled coordinates

	STBTT_DEF int  stbtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2);
	// an additional amount to add to the 'advance' value between ch1 and ch2

	STBTT_DEF int stbtt_GetCodepointBox(const stbtt_fontinfo *info, int codepoint, int *x0, int *y0, int *x1, int *y1);
	// Gets the bounding box of the visible part of the glyph, in unscaled coordinates

	STBTT_DEF void stbtt_GetGlyphHMetrics(const stbtt_fontinfo *info, int glyph_index, int *advanceWidth, int *leftSideBearing);
	STBTT_DEF int  stbtt_GetGlyphKernAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2);
	STBTT_DEF int  stbtt_GetGlyphBox(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1);
	// as above, but takes one or more glyph indices for greater efficiency


	//////////////////////////////////////////////////////////////////////////////
	//
	// GLYPH SHAPES (you probably don't need these, but they have to go before
	// the bitmaps for C declaration-order reasons)
	//

#ifndef STBTT_vmove // you can predefine these to use different values (but why?)
	enum {
		STBTT_vmove = 1,
		STBTT_vline,
		STBTT_vcurve
	};
#endif

#ifndef stbtt_vertex // you can predefine this to use different values
	// (we share this with other code at RAD)
#define stbtt_vertex_type short // can't use stbtt_int16 because that's not visible in the header file
	typedef struct
	{
		stbtt_vertex_type x, y, cx, cy;
		unsigned char type, padding;
	} stbtt_vertex;
#endif

	STBTT_DEF int stbtt_IsGlyphEmpty(const stbtt_fontinfo *info, int glyph_index);
	// returns non-zero if nothing is drawn for this glyph

	STBTT_DEF int stbtt_GetCodepointShape(const stbtt_fontinfo *info, int unicode_codepoint, stbtt_vertex **vertices);
	STBTT_DEF int stbtt_GetGlyphShape(const stbtt_fontinfo *info, int glyph_index, stbtt_vertex **vertices);
	// returns # of vertices and fills *vertices with the pointer to them
	//   these are expressed in "unscaled" coordinates
	//
	// The shape is a series of countours. Each one starts with
	// a STBTT_moveto, then consists of a series of mixed
	// STBTT_lineto and STBTT_curveto segments. A lineto
	// draws a line from previous endpoint to its x,y; a curveto
	// draws a quadratic bezier from previous endpoint to
	// its x,y, using cx,cy as the bezier control point.

	STBTT_DEF void stbtt_FreeShape(const stbtt_fontinfo *info, stbtt_vertex *vertices);
	// frees the data allocated above

	//////////////////////////////////////////////////////////////////////////////
	//
	// BITMAP RENDERING
	//

	STBTT_DEF void stbtt_FreeBitmap(unsigned char *bitmap, void *userdata);
	// frees the bitmap allocated below

	STBTT_DEF unsigned char *stbtt_GetCodepointBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int codepoint, int *width, int *height, int *xoff, int *yoff);
	// allocates a large-enough single-channel 8bpp bitmap and renders the
	// specified character/glyph at the specified scale into it, with
	// antialiasing. 0 is no coverage (transparent), 255 is fully covered (opaque).
	// *width & *height are filled out with the width & height of the bitmap,
	// which is stored left-to-right, top-to-bottom.
	//
	// xoff/yoff are the offset it pixel space from the glyph origin to the top-left of the bitmap

	STBTT_DEF unsigned char *stbtt_GetCodepointBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint, int *width, int *height, int *xoff, int *yoff);
	// the same as stbtt_GetCodepoitnBitmap, but you can specify a subpixel
	// shift for the character

	STBTT_DEF void stbtt_MakeCodepointBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint);
	// the same as stbtt_GetCodepointBitmap, but you pass in storage for the bitmap
	// in the form of 'output', with row spacing of 'out_stride' bytes. the bitmap
	// is clipped to out_w/out_h bytes. Call stbtt_GetCodepointBitmapBox to get the
	// width and height and positioning info for it first.

	STBTT_DEF void stbtt_MakeCodepointBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint);
	// same as stbtt_MakeCodepointBitmap, but you can specify a subpixel
	// shift for the character

	STBTT_DEF void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);
	// get the bbox of the bitmap centered around the glyph origin; so the
	// bitmap width is ix1-ix0, height is iy1-iy0, and location to place
	// the bitmap top left is (leftSideBearing*scale,iy0).
	// (Note that the bitmap uses y-increases-down, but the shape uses
	// y-increases-up, so CodepointBitmapBox and CodepointBox are inverted.)

	STBTT_DEF void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1);
	// same as stbtt_GetCodepointBitmapBox, but you can specify a subpixel
	// shift for the character

	// the following functions are equivalent to the above functions, but operate
	// on glyph indices instead of Unicode codepoints (for efficiency)
	STBTT_DEF unsigned char *stbtt_GetGlyphBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int glyph, int *width, int *height, int *xoff, int *yoff);
	STBTT_DEF unsigned char *stbtt_GetGlyphBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int glyph, int *width, int *height, int *xoff, int *yoff);
	STBTT_DEF void stbtt_MakeGlyphBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int glyph);
	STBTT_DEF void stbtt_MakeGlyphBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int glyph);
	STBTT_DEF void stbtt_GetGlyphBitmapBox(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1);
	STBTT_DEF void stbtt_GetGlyphBitmapBoxSubpixel(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1);


	// @TODO: don't expose this structure
	typedef struct
	{
		int w, h, stride;
		unsigned char *pixels;
	} stbtt__bitmap;

	// rasterize a shape with quadratic beziers into a bitmap
	STBTT_DEF void stbtt_Rasterize(stbtt__bitmap *result,        // 1-channel bitmap to draw into
		float flatness_in_pixels,     // allowable error of curve in pixels
		stbtt_vertex *vertices,       // array of vertices defining shape
		int num_verts,                // number of vertices in above array
		float scale_x, float scale_y, // scale applied to input vertices
		float shift_x, float shift_y, // translation applied to input vertices
		int x_off, int y_off,         // another translation applied to input
		int invert,                   // if non-zero, vertically flip shape
		void *userdata);              // context for to STBTT_MALLOC

	//////////////////////////////////////////////////////////////////////////////
	//
	// Finding the right font...
	//
	// You should really just solve this offline, keep your own tables
	// of what font is what, and don't try to get it out of the .ttf file.
	// That's because getting it out of the .ttf file is really hard, because
	// the names in the file can appear in many possible encodings, in many
	// possible languages, and e.g. if you need a case-insensitive comparison,
	// the details of that depend on the encoding & language in a complex way
	// (actually underspecified in truetype, but also gigantic).
	//
	// But you can use the provided functions in two possible ways:
	//     stbtt_FindMatchingFont() will use *case-sensitive* comparisons on
	//             unicode-encoded names to try to find the font you want;
	//             you can run this before calling stbtt_InitFont()
	//
	//     stbtt_GetFontNameString() lets you get any of the various strings
	//             from the file yourself and do your own comparisons on them.
	//             You have to have called stbtt_InitFont() first.


	STBTT_DEF int stbtt_FindMatchingFont(const unsigned char *fontdata, const char *name, int flags);
	// returns the offset (not index) of the font that matches, or -1 if none
	//   if you use STBTT_MACSTYLE_DONTCARE, use a font name like "Arial Bold".
	//   if you use any other flag, use a font name like "Arial"; this checks
	//     the 'macStyle' header field; i don't know if fonts set this consistently
#define STBTT_MACSTYLE_DONTCARE     0
#define STBTT_MACSTYLE_BOLD         1
#define STBTT_MACSTYLE_ITALIC       2
#define STBTT_MACSTYLE_UNDERSCORE   4
#define STBTT_MACSTYLE_NONE         8   // <= not same as 0, this makes us check the bitfield is 0

	STBTT_DEF int stbtt_CompareUTF8toUTF16_bigendian(const char *s1, int len1, const char *s2, int len2);
	// returns 1/0 whether the first string interpreted as utf8 is identical to
	// the second string interpreted as big-endian utf16... useful for strings from next func

	STBTT_DEF const char *stbtt_GetFontNameString(const stbtt_fontinfo *font, int *length, int platformID, int encodingID, int languageID, int nameID);
	// returns the string (which may be big-endian double byte, e.g. for unicode)
	// and puts the length in bytes in *length.
	//
	// some of the values for the IDs are below; for more see the truetype spec:
	//     http://developer.apple.com/textfonts/TTRefMan/RM06/Chap6name.html
	//     http://www.microsoft.com/typography/otspec/name.htm

	enum { // platformID
		STBTT_PLATFORM_ID_UNICODE = 0,
		STBTT_PLATFORM_ID_MAC = 1,
		STBTT_PLATFORM_ID_ISO = 2,
		STBTT_PLATFORM_ID_MICROSOFT = 3
	};

	enum { // encodingID for STBTT_PLATFORM_ID_UNICODE
		STBTT_UNICODE_EID_UNICODE_1_0 = 0,
		STBTT_UNICODE_EID_UNICODE_1_1 = 1,
		STBTT_UNICODE_EID_ISO_10646 = 2,
		STBTT_UNICODE_EID_UNICODE_2_0_BMP = 3,
		STBTT_UNICODE_EID_UNICODE_2_0_FULL = 4
	};

	enum { // encodingID for STBTT_PLATFORM_ID_MICROSOFT
		STBTT_MS_EID_SYMBOL = 0,
		STBTT_MS_EID_UNICODE_BMP = 1,
		STBTT_MS_EID_SHIFTJIS = 2,
		STBTT_MS_EID_UNICODE_FULL = 10
	};

	enum { // encodingID for STBTT_PLATFORM_ID_MAC; same as Script Manager codes
		STBTT_MAC_EID_ROMAN = 0, STBTT_MAC_EID_ARABIC = 4,
		STBTT_MAC_EID_JAPANESE = 1, STBTT_MAC_EID_HEBREW = 5,
		STBTT_MAC_EID_CHINESE_TRAD = 2, STBTT_MAC_EID_GREEK = 6,
		STBTT_MAC_EID_KOREAN = 3, STBTT_MAC_EID_RUSSIAN = 7
	};

	enum { // languageID for STBTT_PLATFORM_ID_MICROSOFT; same as LCID...
		// problematic because there are e.g. 16 english LCIDs and 16 arabic LCIDs
		STBTT_MS_LANG_ENGLISH = 0x0409, STBTT_MS_LANG_ITALIAN = 0x0410,
		STBTT_MS_LANG_CHINESE = 0x0804, STBTT_MS_LANG_JAPANESE = 0x0411,
		STBTT_MS_LANG_DUTCH = 0x0413, STBTT_MS_LANG_KOREAN = 0x0412,
		STBTT_MS_LANG_FRENCH = 0x040c, STBTT_MS_LANG_RUSSIAN = 0x0419,
		STBTT_MS_LANG_GERMAN = 0x0407, STBTT_MS_LANG_SPANISH = 0x0409,
		STBTT_MS_LANG_HEBREW = 0x040d, STBTT_MS_LANG_SWEDISH = 0x041D
	};

	enum { // languageID for STBTT_PLATFORM_ID_MAC
		STBTT_MAC_LANG_ENGLISH = 0, STBTT_MAC_LANG_JAPANESE = 11,
		STBTT_MAC_LANG_ARABIC = 12, STBTT_MAC_LANG_KOREAN = 23,
		STBTT_MAC_LANG_DUTCH = 4, STBTT_MAC_LANG_RUSSIAN = 32,
		STBTT_MAC_LANG_FRENCH = 1, STBTT_MAC_LANG_SPANISH = 6,
		STBTT_MAC_LANG_GERMAN = 2, STBTT_MAC_LANG_SWEDISH = 5,
		STBTT_MAC_LANG_HEBREW = 10, STBTT_MAC_LANG_CHINESE_SIMPLIFIED = 33,
		STBTT_MAC_LANG_ITALIAN = 3, STBTT_MAC_LANG_CHINESE_TRAD = 19
	};

#ifdef __cplusplus
}
#endif

#endif // __STB_INCLUDE_STB_TRUETYPE_H__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////
////   IMPLEMENTATION
////
////

#ifdef STB_TRUETYPE_IMPLEMENTATION

#ifndef STBTT_MAX_OVERSAMPLE
#define STBTT_MAX_OVERSAMPLE   8
#endif

#if STBTT_MAX_OVERSAMPLE > 255
#error "STBTT_MAX_OVERSAMPLE cannot be > 255"
#endif

typedef int stbtt__test_oversample_pow2[(STBTT_MAX_OVERSAMPLE & (STBTT_MAX_OVERSAMPLE - 1)) == 0 ? 1 : -1];

#ifndef STBTT_RASTERIZER_VERSION
#define STBTT_RASTERIZER_VERSION 2
#endif

#ifdef _MSC_VER
#define STBTT__NOTUSED(v)  (void)(v)
#else
#define STBTT__NOTUSED(v)  (void)sizeof(v)
#endif

//////////////////////////////////////////////////////////////////////////
//
// accessors to parse data from file
//

// on platforms that don't allow misaligned reads, if we want to allow
// truetype fonts that aren't padded to alignment, define ALLOW_UNALIGNED_TRUETYPE

#define ttBYTE(p)     (* (stbtt_uint8 *) (p))
#define ttCHAR(p)     (* (stbtt_int8 *) (p))
#define ttFixed(p)    ttLONG(p)

#if defined(STB_TRUETYPE_BIGENDIAN) && !defined(ALLOW_UNALIGNED_TRUETYPE)

#define ttUSHORT(p)   (* (stbtt_uint16 *) (p))
#define ttSHORT(p)    (* (stbtt_int16 *) (p))
#define ttULONG(p)    (* (stbtt_uint32 *) (p))
#define ttLONG(p)     (* (stbtt_int32 *) (p))

#else

static stbtt_uint16 ttUSHORT(const stbtt_uint8 *p) { return p[0] * 256 + p[1]; }
static stbtt_int16 ttSHORT(const stbtt_uint8 *p)   { return p[0] * 256 + p[1]; }
static stbtt_uint32 ttULONG(const stbtt_uint8 *p)  { return (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3]; }
static stbtt_int32 ttLONG(const stbtt_uint8 *p)    { return (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3]; }

#endif

#define stbtt_tag4(p,c0,c1,c2,c3) ((p)[0] == (c0) && (p)[1] == (c1) && (p)[2] == (c2) && (p)[3] == (c3))
#define stbtt_tag(p,str)           stbtt_tag4(p,str[0],str[1],str[2],str[3])

static int stbtt__isfont(const stbtt_uint8 *font)
{
	// check the version number
	if (stbtt_tag4(font, '1', 0, 0, 0))  return 1; // TrueType 1
	if (stbtt_tag(font, "typ1"))   return 1; // TrueType with type 1 font -- we don't support this!
	if (stbtt_tag(font, "OTTO"))   return 1; // OpenType with CFF
	if (stbtt_tag4(font, 0, 1, 0, 0)) return 1; // OpenType 1.0
	return 0;
}

// @OPTIMIZE: binary search
static stbtt_uint32 stbtt__find_table(stbtt_uint8 *data, stbtt_uint32 fontstart, const char *tag)
{
	stbtt_int32 num_tables = ttUSHORT(data + fontstart + 4);
	stbtt_uint32 tabledir = fontstart + 12;
	stbtt_int32 i;
	for (i = 0; i < num_tables; ++i) {
		stbtt_uint32 loc = tabledir + 16 * i;
		if (stbtt_tag(data + loc + 0, tag))
			return ttULONG(data + loc + 8);
	}
	return 0;
}

STBTT_DEF int stbtt_GetFontOffsetForIndex(const unsigned char *font_collection, int index)
{
	// if it's just a font, there's only one valid index
	if (stbtt__isfont(font_collection))
		return index == 0 ? 0 : -1;

	// check if it's a TTC
	if (stbtt_tag(font_collection, "ttcf")) {
		// version 1?
		if (ttULONG(font_collection + 4) == 0x00010000 || ttULONG(font_collection + 4) == 0x00020000) {
			stbtt_int32 n = ttLONG(font_collection + 8);
			if (index >= n)
				return -1;
			return ttULONG(font_collection + 12 + index * 4);
		}
	}
	return -1;
}

STBTT_DEF int stbtt_InitFont(stbtt_fontinfo *info, const unsigned char *data2, int fontstart)
{
	stbtt_uint8 *data = (stbtt_uint8 *)data2;
	stbtt_uint32 cmap, t;
	stbtt_int32 i, numTables;

	info->data = data;
	info->fontstart = fontstart;

	cmap = stbtt__find_table(data, fontstart, "cmap");       // required
	info->loca = stbtt__find_table(data, fontstart, "loca"); // required
	info->head = stbtt__find_table(data, fontstart, "head"); // required
	info->glyf = stbtt__find_table(data, fontstart, "glyf"); // required
	info->hhea = stbtt__find_table(data, fontstart, "hhea"); // required
	info->hmtx = stbtt__find_table(data, fontstart, "hmtx"); // required
	info->kern = stbtt__find_table(data, fontstart, "kern"); // not required
	if (!cmap || !info->loca || !info->head || !info->glyf || !info->hhea || !info->hmtx)
		return 0;

	t = stbtt__find_table(data, fontstart, "maxp");
	if (t)
		info->numGlyphs = ttUSHORT(data + t + 4);
	else
		info->numGlyphs = 0xffff;

	// find a cmap encoding table we understand *now* to avoid searching
	// later. (todo: could make this installable)
	// the same regardless of glyph.
	numTables = ttUSHORT(data + cmap + 2);
	info->index_map = 0;
	for (i = 0; i < numTables; ++i) {
		stbtt_uint32 encoding_record = cmap + 4 + 8 * i;
		// find an encoding we understand:
		switch (ttUSHORT(data + encoding_record)) {
		case STBTT_PLATFORM_ID_MICROSOFT:
			switch (ttUSHORT(data + encoding_record + 2)) {
			case STBTT_MS_EID_UNICODE_BMP:
			case STBTT_MS_EID_UNICODE_FULL:
				// MS/Unicode
				info->index_map = cmap + ttULONG(data + encoding_record + 4);
				break;
			}
			break;
		case STBTT_PLATFORM_ID_UNICODE:
			// Mac/iOS has these
			// all the encodingIDs are unicode, so we don't bother to check it
			info->index_map = cmap + ttULONG(data + encoding_record + 4);
			break;
		}
	}
	if (info->index_map == 0)
		return 0;

	info->indexToLocFormat = ttUSHORT(data + info->head + 50);
	return 1;
}

STBTT_DEF int stbtt_FindGlyphIndex(const stbtt_fontinfo *info, int unicode_codepoint)
{
	stbtt_uint8 *data = info->data;
	stbtt_uint32 index_map = info->index_map;

	stbtt_uint16 format = ttUSHORT(data + index_map + 0);
	if (format == 0) { // apple byte encoding
		stbtt_int32 bytes = ttUSHORT(data + index_map + 2);
		if (unicode_codepoint < bytes - 6)
			return ttBYTE(data + index_map + 6 + unicode_codepoint);
		return 0;
	}
	else if (format == 6) {
		stbtt_uint32 first = ttUSHORT(data + index_map + 6);
		stbtt_uint32 count = ttUSHORT(data + index_map + 8);
		if ((stbtt_uint32)unicode_codepoint >= first && (stbtt_uint32)unicode_codepoint < first + count)
			return ttUSHORT(data + index_map + 10 + (unicode_codepoint - first) * 2);
		return 0;
	}
	else if (format == 2) {
		STBTT_assert(0); // @TODO: high-byte mapping for japanese/chinese/korean
		return 0;
	}
	else if (format == 4) { // standard mapping for windows fonts: binary search collection of ranges
		stbtt_uint16 segcount = ttUSHORT(data + index_map + 6) >> 1;
		stbtt_uint16 searchRange = ttUSHORT(data + index_map + 8) >> 1;
		stbtt_uint16 entrySelector = ttUSHORT(data + index_map + 10);
		stbtt_uint16 rangeShift = ttUSHORT(data + index_map + 12) >> 1;

		// do a binary search of the segments
		stbtt_uint32 endCount = index_map + 14;
		stbtt_uint32 search = endCount;

		if (unicode_codepoint > 0xffff)
			return 0;

		// they lie from endCount .. endCount + segCount
		// but searchRange is the nearest power of two, so...
		if (unicode_codepoint >= ttUSHORT(data + search + rangeShift * 2))
			search += rangeShift * 2;

		// now decrement to bias correctly to find smallest
		search -= 2;
		while (entrySelector) {
			stbtt_uint16 end;
			searchRange >>= 1;
			end = ttUSHORT(data + search + searchRange * 2);
			if (unicode_codepoint > end)
				search += searchRange * 2;
			--entrySelector;
		}
		search += 2;

		{
			stbtt_uint16 offset, start;
			stbtt_uint16 item = (stbtt_uint16)((search - endCount) >> 1);

			STBTT_assert(unicode_codepoint <= ttUSHORT(data + endCount + 2 * item));
			start = ttUSHORT(data + index_map + 14 + segcount * 2 + 2 + 2 * item);
			if (unicode_codepoint < start)
				return 0;

			offset = ttUSHORT(data + index_map + 14 + segcount * 6 + 2 + 2 * item);
			if (offset == 0)
				return (stbtt_uint16)(unicode_codepoint + ttSHORT(data + index_map + 14 + segcount * 4 + 2 + 2 * item));

			return ttUSHORT(data + offset + (unicode_codepoint - start) * 2 + index_map + 14 + segcount * 6 + 2 + 2 * item);
		}
	}
	else if (format == 12 || format == 13) {
		stbtt_uint32 ngroups = ttULONG(data + index_map + 12);
		stbtt_int32 low, high;
		low = 0; high = (stbtt_int32)ngroups;
		// Binary search the right group.
		while (low < high) {
			stbtt_int32 mid = low + ((high - low) >> 1); // rounds down, so low <= mid < high
			stbtt_uint32 start_char = ttULONG(data + index_map + 16 + mid * 12);
			stbtt_uint32 end_char = ttULONG(data + index_map + 16 + mid * 12 + 4);
			if ((stbtt_uint32)unicode_codepoint < start_char)
				high = mid;
			else if ((stbtt_uint32)unicode_codepoint > end_char)
				low = mid + 1;
			else {
				stbtt_uint32 start_glyph = ttULONG(data + index_map + 16 + mid * 12 + 8);
				if (format == 12)
					return start_glyph + unicode_codepoint - start_char;
				else // format == 13
					return start_glyph;
			}
		}
		return 0; // not found
	}
	// @TODO
	STBTT_assert(0);
	return 0;
}

STBTT_DEF int stbtt_GetCodepointShape(const stbtt_fontinfo *info, int unicode_codepoint, stbtt_vertex **vertices)
{
	return stbtt_GetGlyphShape(info, stbtt_FindGlyphIndex(info, unicode_codepoint), vertices);
}

static void stbtt_setvertex(stbtt_vertex *v, stbtt_uint8 type, stbtt_int32 x, stbtt_int32 y, stbtt_int32 cx, stbtt_int32 cy)
{
	v->type = type;
	v->x = (stbtt_int16)x;
	v->y = (stbtt_int16)y;
	v->cx = (stbtt_int16)cx;
	v->cy = (stbtt_int16)cy;
}

static int stbtt__GetGlyfOffset(const stbtt_fontinfo *info, int glyph_index)
{
	int g1, g2;

	if (glyph_index >= info->numGlyphs) return -1; // glyph index out of range
	if (info->indexToLocFormat >= 2)    return -1; // unknown index->glyph map format

	if (info->indexToLocFormat == 0) {
		g1 = info->glyf + ttUSHORT(info->data + info->loca + glyph_index * 2) * 2;
		g2 = info->glyf + ttUSHORT(info->data + info->loca + glyph_index * 2 + 2) * 2;
	}
	else {
		g1 = info->glyf + ttULONG(info->data + info->loca + glyph_index * 4);
		g2 = info->glyf + ttULONG(info->data + info->loca + glyph_index * 4 + 4);
	}

	return g1 == g2 ? -1 : g1; // if length is 0, return -1
}

STBTT_DEF int stbtt_GetGlyphBox(const stbtt_fontinfo *info, int glyph_index, int *x0, int *y0, int *x1, int *y1)
{
	int g = stbtt__GetGlyfOffset(info, glyph_index);
	if (g < 0) return 0;

	if (x0) *x0 = ttSHORT(info->data + g + 2);
	if (y0) *y0 = ttSHORT(info->data + g + 4);
	if (x1) *x1 = ttSHORT(info->data + g + 6);
	if (y1) *y1 = ttSHORT(info->data + g + 8);
	return 1;
}

STBTT_DEF int stbtt_GetCodepointBox(const stbtt_fontinfo *info, int codepoint, int *x0, int *y0, int *x1, int *y1)
{
	return stbtt_GetGlyphBox(info, stbtt_FindGlyphIndex(info, codepoint), x0, y0, x1, y1);
}

STBTT_DEF int stbtt_IsGlyphEmpty(const stbtt_fontinfo *info, int glyph_index)
{
	stbtt_int16 numberOfContours;
	int g = stbtt__GetGlyfOffset(info, glyph_index);
	if (g < 0) return 1;
	numberOfContours = ttSHORT(info->data + g);
	return numberOfContours == 0;
}

static int stbtt__close_shape(stbtt_vertex *vertices, int num_vertices, int was_off, int start_off,
	stbtt_int32 sx, stbtt_int32 sy, stbtt_int32 scx, stbtt_int32 scy, stbtt_int32 cx, stbtt_int32 cy)
{
	if (start_off) {
		if (was_off)
			stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, (cx + scx) >> 1, (cy + scy) >> 1, cx, cy);
		stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, sx, sy, scx, scy);
	}
	else {
		if (was_off)
			stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, sx, sy, cx, cy);
		else
			stbtt_setvertex(&vertices[num_vertices++], STBTT_vline, sx, sy, 0, 0);
	}
	return num_vertices;
}

STBTT_DEF int stbtt_GetGlyphShape(const stbtt_fontinfo *info, int glyph_index, stbtt_vertex **pvertices)
{
	stbtt_int16 numberOfContours;
	stbtt_uint8 *endPtsOfContours;
	stbtt_uint8 *data = info->data;
	stbtt_vertex *vertices = 0;
	int num_vertices = 0;
	int g = stbtt__GetGlyfOffset(info, glyph_index);

	*pvertices = NULL;

	if (g < 0) return 0;

	numberOfContours = ttSHORT(data + g);

	if (numberOfContours > 0) {
		stbtt_uint8 flags = 0, flagcount;
		stbtt_int32 ins, i, j = 0, m, n, next_move, was_off = 0, off, start_off = 0;
		stbtt_int32 x, y, cx, cy, sx, sy, scx, scy;
		stbtt_uint8 *points;
		endPtsOfContours = (data + g + 10);
		ins = ttUSHORT(data + g + 10 + numberOfContours * 2);
		points = data + g + 10 + numberOfContours * 2 + 2 + ins;

		n = 1 + ttUSHORT(endPtsOfContours + numberOfContours * 2 - 2);

		m = n + 2 * numberOfContours;  // a loose bound on how many vertices we might need
		vertices = (stbtt_vertex *)STBTT_malloc(m * sizeof(vertices[0]), info->userdata);
		if (vertices == 0)
			return 0;

		next_move = 0;
		flagcount = 0;

		// in first pass, we load uninterpreted data into the allocated array
		// above, shifted to the end of the array so we won't overwrite it when
		// we create our final data starting from the front

		off = m - n; // starting offset for uninterpreted data, regardless of how m ends up being calculated

		// first load flags

		for (i = 0; i < n; ++i) {
			if (flagcount == 0) {
				flags = *points++;
				if (flags & 8)
					flagcount = *points++;
			}
			else
				--flagcount;
			vertices[off + i].type = flags;
		}

		// now load x coordinates
		x = 0;
		for (i = 0; i < n; ++i) {
			flags = vertices[off + i].type;
			if (flags & 2) {
				stbtt_int16 dx = *points++;
				x += (flags & 16) ? dx : -dx; // ???
			}
			else {
				if (!(flags & 16)) {
					x = x + (stbtt_int16)(points[0] * 256 + points[1]);
					points += 2;
				}
			}
			vertices[off + i].x = (stbtt_int16)x;
		}

		// now load y coordinates
		y = 0;
		for (i = 0; i < n; ++i) {
			flags = vertices[off + i].type;
			if (flags & 4) {
				stbtt_int16 dy = *points++;
				y += (flags & 32) ? dy : -dy; // ???
			}
			else {
				if (!(flags & 32)) {
					y = y + (stbtt_int16)(points[0] * 256 + points[1]);
					points += 2;
				}
			}
			vertices[off + i].y = (stbtt_int16)y;
		}

		// now convert them to our format
		num_vertices = 0;
		sx = sy = cx = cy = scx = scy = 0;
		for (i = 0; i < n; ++i) {
			flags = vertices[off + i].type;
			x = (stbtt_int16)vertices[off + i].x;
			y = (stbtt_int16)vertices[off + i].y;

			if (next_move == i) {
				if (i != 0)
					num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx, sy, scx, scy, cx, cy);

				// now start the new one               
				start_off = !(flags & 1);
				if (start_off) {
					// if we start off with an off-curve point, then when we need to find a point on the curve
					// where we can start, and we need to save some state for when we wraparound.
					scx = x;
					scy = y;
					if (!(vertices[off + i + 1].type & 1)) {
						// next point is also a curve point, so interpolate an on-point curve
						sx = (x + (stbtt_int32)vertices[off + i + 1].x) >> 1;
						sy = (y + (stbtt_int32)vertices[off + i + 1].y) >> 1;
					}
					else {
						// otherwise just use the next point as our start point
						sx = (stbtt_int32)vertices[off + i + 1].x;
						sy = (stbtt_int32)vertices[off + i + 1].y;
						++i; // we're using point i+1 as the starting point, so skip it
					}
				}
				else {
					sx = x;
					sy = y;
				}
				stbtt_setvertex(&vertices[num_vertices++], STBTT_vmove, sx, sy, 0, 0);
				was_off = 0;
				next_move = 1 + ttUSHORT(endPtsOfContours + j * 2);
				++j;
			}
			else {
				if (!(flags & 1)) { // if it's a curve
					if (was_off) // two off-curve control points in a row means interpolate an on-curve midpoint
						stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, (cx + x) >> 1, (cy + y) >> 1, cx, cy);
					cx = x;
					cy = y;
					was_off = 1;
				}
				else {
					if (was_off)
						stbtt_setvertex(&vertices[num_vertices++], STBTT_vcurve, x, y, cx, cy);
					else
						stbtt_setvertex(&vertices[num_vertices++], STBTT_vline, x, y, 0, 0);
					was_off = 0;
				}
			}
		}
		num_vertices = stbtt__close_shape(vertices, num_vertices, was_off, start_off, sx, sy, scx, scy, cx, cy);
	}
	else if (numberOfContours == -1) {
		// Compound shapes.
		int more = 1;
		stbtt_uint8 *comp = data + g + 10;
		num_vertices = 0;
		vertices = 0;
		while (more) {
			stbtt_uint16 flags, gidx;
			int comp_num_verts = 0, i;
			stbtt_vertex *comp_verts = 0, *tmp = 0;
			float mtx[6] = { 1, 0, 0, 1, 0, 0 }, m, n;

			flags = ttSHORT(comp); comp += 2;
			gidx = ttSHORT(comp); comp += 2;

			if (flags & 2) { // XY values
				if (flags & 1) { // shorts
					mtx[4] = ttSHORT(comp); comp += 2;
					mtx[5] = ttSHORT(comp); comp += 2;
				}
				else {
					mtx[4] = ttCHAR(comp); comp += 1;
					mtx[5] = ttCHAR(comp); comp += 1;
				}
			}
			else {
				// @TODO handle matching point
				STBTT_assert(0);
			}
			if (flags & (1 << 3)) { // WE_HAVE_A_SCALE
				mtx[0] = mtx[3] = ttSHORT(comp) / 16384.0f; comp += 2;
				mtx[1] = mtx[2] = 0;
			}
			else if (flags & (1 << 6)) { // WE_HAVE_AN_X_AND_YSCALE
				mtx[0] = ttSHORT(comp) / 16384.0f; comp += 2;
				mtx[1] = mtx[2] = 0;
				mtx[3] = ttSHORT(comp) / 16384.0f; comp += 2;
			}
			else if (flags & (1 << 7)) { // WE_HAVE_A_TWO_BY_TWO
				mtx[0] = ttSHORT(comp) / 16384.0f; comp += 2;
				mtx[1] = ttSHORT(comp) / 16384.0f; comp += 2;
				mtx[2] = ttSHORT(comp) / 16384.0f; comp += 2;
				mtx[3] = ttSHORT(comp) / 16384.0f; comp += 2;
			}

			// Find transformation scales.
			m = (float)STBTT_sqrt(mtx[0] * mtx[0] + mtx[1] * mtx[1]);
			n = (float)STBTT_sqrt(mtx[2] * mtx[2] + mtx[3] * mtx[3]);

			// Get indexed glyph.
			comp_num_verts = stbtt_GetGlyphShape(info, gidx, &comp_verts);
			if (comp_num_verts > 0) {
				// Transform vertices.
				for (i = 0; i < comp_num_verts; ++i) {
					stbtt_vertex* v = &comp_verts[i];
					stbtt_vertex_type x, y;
					x = v->x; y = v->y;
					v->x = (stbtt_vertex_type)(m * (mtx[0] * x + mtx[2] * y + mtx[4]));
					v->y = (stbtt_vertex_type)(n * (mtx[1] * x + mtx[3] * y + mtx[5]));
					x = v->cx; y = v->cy;
					v->cx = (stbtt_vertex_type)(m * (mtx[0] * x + mtx[2] * y + mtx[4]));
					v->cy = (stbtt_vertex_type)(n * (mtx[1] * x + mtx[3] * y + mtx[5]));
				}
				// Append vertices.
				tmp = (stbtt_vertex*)STBTT_malloc((num_vertices + comp_num_verts)*sizeof(stbtt_vertex), info->userdata);
				if (!tmp) {
					if (vertices) STBTT_free(vertices, info->userdata);
					if (comp_verts) STBTT_free(comp_verts, info->userdata);
					return 0;
				}
				if (num_vertices > 0) STBTT_memcpy(tmp, vertices, num_vertices*sizeof(stbtt_vertex));
				STBTT_memcpy(tmp + num_vertices, comp_verts, comp_num_verts*sizeof(stbtt_vertex));
				if (vertices) STBTT_free(vertices, info->userdata);
				vertices = tmp;
				STBTT_free(comp_verts, info->userdata);
				num_vertices += comp_num_verts;
			}
			// More components ?
			more = flags & (1 << 5);
		}
	}
	else if (numberOfContours < 0) {
		// @TODO other compound variations?
		STBTT_assert(0);
	}
	else {
		// numberOfCounters == 0, do nothing
	}

	*pvertices = vertices;
	return num_vertices;
}

STBTT_DEF void stbtt_GetGlyphHMetrics(const stbtt_fontinfo *info, int glyph_index, int *advanceWidth, int *leftSideBearing)
{
	stbtt_uint16 numOfLongHorMetrics = ttUSHORT(info->data + info->hhea + 34);
	if (glyph_index < numOfLongHorMetrics) {
		if (advanceWidth)     *advanceWidth = ttSHORT(info->data + info->hmtx + 4 * glyph_index);
		if (leftSideBearing)  *leftSideBearing = ttSHORT(info->data + info->hmtx + 4 * glyph_index + 2);
	}
	else {
		if (advanceWidth)     *advanceWidth = ttSHORT(info->data + info->hmtx + 4 * (numOfLongHorMetrics - 1));
		if (leftSideBearing)  *leftSideBearing = ttSHORT(info->data + info->hmtx + 4 * numOfLongHorMetrics + 2 * (glyph_index - numOfLongHorMetrics));
	}
}

STBTT_DEF int  stbtt_GetGlyphKernAdvance(const stbtt_fontinfo *info, int glyph1, int glyph2)
{
	stbtt_uint8 *data = info->data + info->kern;
	stbtt_uint32 needle, straw;
	int l, r, m;

	// we only look at the first table. it must be 'horizontal' and format 0.
	if (!info->kern)
		return 0;
	if (ttUSHORT(data + 2) < 1) // number of tables, need at least 1
		return 0;
	if (ttUSHORT(data + 8) != 1) // horizontal flag must be set in format
		return 0;

	l = 0;
	r = ttUSHORT(data + 10) - 1;
	needle = glyph1 << 16 | glyph2;
	while (l <= r) {
		m = (l + r) >> 1;
		straw = ttULONG(data + 18 + (m * 6)); // note: unaligned read
		if (needle < straw)
			r = m - 1;
		else if (needle > straw)
			l = m + 1;
		else
			return ttSHORT(data + 22 + (m * 6));
	}
	return 0;
}

STBTT_DEF int  stbtt_GetCodepointKernAdvance(const stbtt_fontinfo *info, int ch1, int ch2)
{
	if (!info->kern) // if no kerning table, don't waste time looking up both codepoint->glyphs
		return 0;
	return stbtt_GetGlyphKernAdvance(info, stbtt_FindGlyphIndex(info, ch1), stbtt_FindGlyphIndex(info, ch2));
}

STBTT_DEF void stbtt_GetCodepointHMetrics(const stbtt_fontinfo *info, int codepoint, int *advanceWidth, int *leftSideBearing)
{
	stbtt_GetGlyphHMetrics(info, stbtt_FindGlyphIndex(info, codepoint), advanceWidth, leftSideBearing);
}

STBTT_DEF void stbtt_GetFontVMetrics(const stbtt_fontinfo *info, int *ascent, int *descent, int *lineGap)
{
	if (ascent) *ascent = ttSHORT(info->data + info->hhea + 4);
	if (descent) *descent = ttSHORT(info->data + info->hhea + 6);
	if (lineGap) *lineGap = ttSHORT(info->data + info->hhea + 8);
}

STBTT_DEF void stbtt_GetFontBoundingBox(const stbtt_fontinfo *info, int *x0, int *y0, int *x1, int *y1)
{
	*x0 = ttSHORT(info->data + info->head + 36);
	*y0 = ttSHORT(info->data + info->head + 38);
	*x1 = ttSHORT(info->data + info->head + 40);
	*y1 = ttSHORT(info->data + info->head + 42);
}

STBTT_DEF float stbtt_ScaleForPixelHeight(const stbtt_fontinfo *info, float height)
{
	int fheight = ttSHORT(info->data + info->hhea + 4) - ttSHORT(info->data + info->hhea + 6);
	return (float)height / fheight;
}

STBTT_DEF float stbtt_ScaleForMappingEmToPixels(const stbtt_fontinfo *info, float pixels)
{
	int unitsPerEm = ttUSHORT(info->data + info->head + 18);
	return pixels / unitsPerEm;
}

STBTT_DEF void stbtt_FreeShape(const stbtt_fontinfo *info, stbtt_vertex *v)
{
	STBTT_free(v, info->userdata);
}

//////////////////////////////////////////////////////////////////////////////
//
// antialiasing software rasterizer
//

STBTT_DEF void stbtt_GetGlyphBitmapBoxSubpixel(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
	int x0 = 0, y0 = 0, x1, y1; // =0 suppresses compiler warning
	if (!stbtt_GetGlyphBox(font, glyph, &x0, &y0, &x1, &y1)) {
		// e.g. space character
		if (ix0) *ix0 = 0;
		if (iy0) *iy0 = 0;
		if (ix1) *ix1 = 0;
		if (iy1) *iy1 = 0;
	}
	else {
		// move to integral bboxes (treating pixels as little squares, what pixels get touched)?
		if (ix0) *ix0 = STBTT_ifloor(x0 * scale_x + shift_x);
		if (iy0) *iy0 = STBTT_ifloor(-y1 * scale_y + shift_y);
		if (ix1) *ix1 = STBTT_iceil(x1 * scale_x + shift_x);
		if (iy1) *iy1 = STBTT_iceil(-y0 * scale_y + shift_y);
	}
}

STBTT_DEF void stbtt_GetGlyphBitmapBox(const stbtt_fontinfo *font, int glyph, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
	stbtt_GetGlyphBitmapBoxSubpixel(font, glyph, scale_x, scale_y, 0.0f, 0.0f, ix0, iy0, ix1, iy1);
}

STBTT_DEF void stbtt_GetCodepointBitmapBoxSubpixel(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, float shift_x, float shift_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
	stbtt_GetGlyphBitmapBoxSubpixel(font, stbtt_FindGlyphIndex(font, codepoint), scale_x, scale_y, shift_x, shift_y, ix0, iy0, ix1, iy1);
}

STBTT_DEF void stbtt_GetCodepointBitmapBox(const stbtt_fontinfo *font, int codepoint, float scale_x, float scale_y, int *ix0, int *iy0, int *ix1, int *iy1)
{
	stbtt_GetCodepointBitmapBoxSubpixel(font, codepoint, scale_x, scale_y, 0.0f, 0.0f, ix0, iy0, ix1, iy1);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Rasterizer

typedef struct stbtt__hheap_chunk
{
	struct stbtt__hheap_chunk *next;
} stbtt__hheap_chunk;

typedef struct stbtt__hheap
{
	struct stbtt__hheap_chunk *head;
	void   *first_free;
	int    num_remaining_in_head_chunk;
} stbtt__hheap;

static void *stbtt__hheap_alloc(stbtt__hheap *hh, size_t size, void *userdata)
{
	if (hh->first_free) {
		void *p = hh->first_free;
		hh->first_free = *(void **)p;
		return p;
	}
	else {
		if (hh->num_remaining_in_head_chunk == 0) {
			int count = (size < 32 ? 2000 : size < 128 ? 800 : 100);
			stbtt__hheap_chunk *c = (stbtt__hheap_chunk *)STBTT_malloc(sizeof(stbtt__hheap_chunk) + size * count, userdata);
			if (c == NULL)
				return NULL;
			c->next = hh->head;
			hh->head = c;
			hh->num_remaining_in_head_chunk = count;
		}
		--hh->num_remaining_in_head_chunk;
		return (char *)(hh->head) + size * hh->num_remaining_in_head_chunk;
	}
}

static void stbtt__hheap_free(stbtt__hheap *hh, void *p)
{
	*(void **)p = hh->first_free;
	hh->first_free = p;
}

static void stbtt__hheap_cleanup(stbtt__hheap *hh, void *userdata)
{
	stbtt__hheap_chunk *c = hh->head;
	while (c) {
		stbtt__hheap_chunk *n = c->next;
		STBTT_free(c, userdata);
		c = n;
	}
}

typedef struct stbtt__edge {
	float x0, y0, x1, y1;
	int invert;
} stbtt__edge;


typedef struct stbtt__active_edge
{
	struct stbtt__active_edge *next;
#if STBTT_RASTERIZER_VERSION==1
	int x, dx;
	float ey;
	int direction;
#elif STBTT_RASTERIZER_VERSION==2
	float fx, fdx, fdy;
	float direction;
	float sy;
	float ey;
#else
#error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif
} stbtt__active_edge;

#if STBTT_RASTERIZER_VERSION == 1
#define STBTT_FIXSHIFT   10
#define STBTT_FIX        (1 << STBTT_FIXSHIFT)
#define STBTT_FIXMASK    (STBTT_FIX-1)

static stbtt__active_edge *stbtt__new_active(stbtt__hheap *hh, stbtt__edge *e, int off_x, float start_point, void *userdata)
{
	stbtt__active_edge *z = (stbtt__active_edge *)stbtt__hheap_alloc(hh, sizeof(*z), userdata);
	float dxdy = (e->x1 - e->x0) / (e->y1 - e->y0);
	STBTT_assert(z != NULL);
	if (!z) return z;

	// round dx down to avoid overshooting
	if (dxdy < 0)
		z->dx = -STBTT_ifloor(STBTT_FIX * -dxdy);
	else
		z->dx = STBTT_ifloor(STBTT_FIX * dxdy);

	z->x = STBTT_ifloor(STBTT_FIX * e->x0 + z->dx * (start_point - e->y0)); // use z->dx so when we offset later it's by the same amount
	z->x -= off_x * STBTT_FIX;

	z->ey = e->y1;
	z->next = 0;
	z->direction = e->invert ? 1 : -1;
	return z;
}
#elif STBTT_RASTERIZER_VERSION == 2
static stbtt__active_edge *stbtt__new_active(stbtt__hheap *hh, stbtt__edge *e, int off_x, float start_point, void *userdata)
{
	stbtt__active_edge *z = (stbtt__active_edge *)stbtt__hheap_alloc(hh, sizeof(*z), userdata);
	float dxdy = (e->x1 - e->x0) / (e->y1 - e->y0);
	STBTT_assert(z != NULL);
	//STBTT_assert(e->y0 <= start_point);
	if (!z) return z;
	z->fdx = dxdy;
	z->fdy = dxdy != 0.0f ? (1.0f / dxdy) : 0.0f;
	z->fx = e->x0 + dxdy * (start_point - e->y0);
	z->fx -= off_x;
	z->direction = e->invert ? 1.0f : -1.0f;
	z->sy = e->y0;
	z->ey = e->y1;
	z->next = 0;
	return z;
}
#else
#error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif

#if STBTT_RASTERIZER_VERSION == 1
// note: this routine clips fills that extend off the edges... ideally this
// wouldn't happen, but it could happen if the truetype glyph bounding boxes
// are wrong, or if the user supplies a too-small bitmap
static void stbtt__fill_active_edges(unsigned char *scanline, int len, stbtt__active_edge *e, int max_weight)
{
	// non-zero winding fill
	int x0 = 0, w = 0;

	while (e) {
		if (w == 0) {
			// if we're currently at zero, we need to record the edge start point
			x0 = e->x; w += e->direction;
		}
		else {
			int x1 = e->x; w += e->direction;
			// if we went to zero, we need to draw
			if (w == 0) {
				int i = x0 >> STBTT_FIXSHIFT;
				int j = x1 >> STBTT_FIXSHIFT;

				if (i < len && j >= 0) {
					if (i == j) {
						// x0,x1 are the same pixel, so compute combined coverage
						scanline[i] = scanline[i] + (stbtt_uint8)((x1 - x0) * max_weight >> STBTT_FIXSHIFT);
					}
					else {
						if (i >= 0) // add antialiasing for x0
							scanline[i] = scanline[i] + (stbtt_uint8)(((STBTT_FIX - (x0 & STBTT_FIXMASK)) * max_weight) >> STBTT_FIXSHIFT);
						else
							i = -1; // clip

						if (j < len) // add antialiasing for x1
							scanline[j] = scanline[j] + (stbtt_uint8)(((x1 & STBTT_FIXMASK) * max_weight) >> STBTT_FIXSHIFT);
						else
							j = len; // clip

						for (++i; i < j; ++i) // fill pixels between x0 and x1
							scanline[i] = scanline[i] + (stbtt_uint8)max_weight;
					}
				}
			}
		}

		e = e->next;
	}
}

static void stbtt__rasterize_sorted_edges(stbtt__bitmap *result, stbtt__edge *e, int n, int vsubsample, int off_x, int off_y, void *userdata)
{
	stbtt__hheap hh = { 0, 0, 0 };
	stbtt__active_edge *active = NULL;
	int y, j = 0;
	int max_weight = (255 / vsubsample);  // weight per vertical scanline
	int s; // vertical subsample index
	unsigned char scanline_data[512], *scanline;

	if (result->w > 512)
		scanline = (unsigned char *)STBTT_malloc(result->w, userdata);
	else
		scanline = scanline_data;

	y = off_y * vsubsample;
	e[n].y0 = (off_y + result->h) * (float)vsubsample + 1;

	while (j < result->h) {
		STBTT_memset(scanline, 0, result->w);
		for (s = 0; s < vsubsample; ++s) {
			// find center of pixel for this scanline
			float scan_y = y + 0.5f;
			stbtt__active_edge **step = &active;

			// update all active edges;
			// remove all active edges that terminate before the center of this scanline
			while (*step) {
				stbtt__active_edge * z = *step;
				if (z->ey <= scan_y) {
					*step = z->next; // delete from list
					STBTT_assert(z->direction);
					z->direction = 0;
					stbtt__hheap_free(&hh, z);
				}
				else {
					z->x += z->dx; // advance to position for current scanline
					step = &((*step)->next); // advance through list
				}
			}

			// resort the list if needed
			for (;;) {
				int changed = 0;
				step = &active;
				while (*step && (*step)->next) {
					if ((*step)->x > (*step)->next->x) {
						stbtt__active_edge *t = *step;
						stbtt__active_edge *q = t->next;

						t->next = q->next;
						q->next = t;
						*step = q;
						changed = 1;
					}
					step = &(*step)->next;
				}
				if (!changed) break;
			}

			// insert all edges that start before the center of this scanline -- omit ones that also end on this scanline
			while (e->y0 <= scan_y) {
				if (e->y1 > scan_y) {
					stbtt__active_edge *z = stbtt__new_active(&hh, e, off_x, scan_y, userdata);
					if (z != NULL) {
						// find insertion point
						if (active == NULL)
							active = z;
						else if (z->x < active->x) {
							// insert at front
							z->next = active;
							active = z;
						}
						else {
							// find thing to insert AFTER
							stbtt__active_edge *p = active;
							while (p->next && p->next->x < z->x)
								p = p->next;
							// at this point, p->next->x is NOT < z->x
							z->next = p->next;
							p->next = z;
						}
					}
				}
				++e;
			}

			// now process all active edges in XOR fashion
			if (active)
				stbtt__fill_active_edges(scanline, result->w, active, max_weight);

			++y;
		}
		STBTT_memcpy(result->pixels + j * result->stride, scanline, result->w);
		++j;
	}

	stbtt__hheap_cleanup(&hh, userdata);

	if (scanline != scanline_data)
		STBTT_free(scanline, userdata);
}

#elif STBTT_RASTERIZER_VERSION == 2

// the edge passed in here does not cross the vertical line at x or the vertical line at x+1
// (i.e. it has already been clipped to those)
static void stbtt__handle_clipped_edge(float *scanline, int x, stbtt__active_edge *e, float x0, float y0, float x1, float y1)
{
	if (y0 == y1) return;
	STBTT_assert(y0 < y1);
	STBTT_assert(e->sy <= e->ey);
	if (y0 > e->ey) return;
	if (y1 < e->sy) return;
	if (y0 < e->sy) {
		x0 += (x1 - x0) * (e->sy - y0) / (y1 - y0);
		y0 = e->sy;
	}
	if (y1 > e->ey) {
		x1 += (x1 - x0) * (e->ey - y1) / (y1 - y0);
		y1 = e->ey;
	}

	if (x0 == x)
		STBTT_assert(x1 <= x + 1);
	else if (x0 == x + 1)
		STBTT_assert(x1 >= x);
	else if (x0 <= x)
		STBTT_assert(x1 <= x);
	else if (x0 >= x + 1)
		STBTT_assert(x1 >= x + 1);
	else
		STBTT_assert(x1 >= x && x1 <= x + 1);

	if (x0 <= x && x1 <= x)
		scanline[x] += e->direction * (y1 - y0);
	else if (x0 >= x + 1 && x1 >= x + 1)
		;
	else {
		STBTT_assert(x0 >= x && x0 <= x + 1 && x1 >= x && x1 <= x + 1);
		scanline[x] += e->direction * (y1 - y0) * (1 - ((x0 - x) + (x1 - x)) / 2); // coverage = 1 - average x position
	}
}

static void stbtt__fill_active_edges_new(float *scanline, float *scanline_fill, int len, stbtt__active_edge *e, float y_top)
{
	float y_bottom = y_top + 1;

	while (e) {
		// brute force every pixel

		// compute intersection points with top & bottom
		STBTT_assert(e->ey >= y_top);

		if (e->fdx == 0) {
			float x0 = e->fx;
			if (x0 < len) {
				if (x0 >= 0) {
					stbtt__handle_clipped_edge(scanline, (int)x0, e, x0, y_top, x0, y_bottom);
					stbtt__handle_clipped_edge(scanline_fill - 1, (int)x0 + 1, e, x0, y_top, x0, y_bottom);
				}
				else {
					stbtt__handle_clipped_edge(scanline_fill - 1, 0, e, x0, y_top, x0, y_bottom);
				}
			}
		}
		else {
			float x0 = e->fx;
			float dx = e->fdx;
			float xb = x0 + dx;
			float x_top, x_bottom;
			float sy0, sy1;
			float dy = e->fdy;
			STBTT_assert(e->sy <= y_bottom && e->ey >= y_top);

			// compute endpoints of line segment clipped to this scanline (if the
			// line segment starts on this scanline. x0 is the intersection of the
			// line with y_top, but that may be off the line segment.
			if (e->sy > y_top) {
				x_top = x0 + dx * (e->sy - y_top);
				sy0 = e->sy;
			}
			else {
				x_top = x0;
				sy0 = y_top;
			}
			if (e->ey < y_bottom) {
				x_bottom = x0 + dx * (e->ey - y_top);
				sy1 = e->ey;
			}
			else {
				x_bottom = xb;
				sy1 = y_bottom;
			}

			if (x_top >= 0 && x_bottom >= 0 && x_top < len && x_bottom < len) {
				// from here on, we don't have to range check x values

				if ((int)x_top == (int)x_bottom) {
					float height;
					// simple case, only spans one pixel
					int x = (int)x_top;
					height = sy1 - sy0;
					STBTT_assert(x >= 0 && x < len);
					scanline[x] += e->direction * (1 - ((x_top - x) + (x_bottom - x)) / 2)  * height;
					scanline_fill[x] += e->direction * height; // everything right of this pixel is filled
				}
				else {
					int x, x1, x2;
					float y_crossing, step, sign, area;
					// covers 2+ pixels
					if (x_top > x_bottom) {
						// flip scanline vertically; signed area is the same
						float t;
						sy0 = y_bottom - (sy0 - y_top);
						sy1 = y_bottom - (sy1 - y_top);
						t = sy0, sy0 = sy1, sy1 = t;
						t = x_bottom, x_bottom = x_top, x_top = t;
						dx = -dx;
						dy = -dy;
						t = x0, x0 = xb, xb = t;
					}

					x1 = (int)x_top;
					x2 = (int)x_bottom;
					// compute intersection with y axis at x1+1
					y_crossing = (x1 + 1 - x0) * dy + y_top;

					sign = e->direction;
					// area of the rectangle covered from y0..y_crossing
					area = sign * (y_crossing - sy0);
					// area of the triangle (x_top,y0), (x+1,y0), (x+1,y_crossing)
					scanline[x1] += area * (1 - ((x_top - x1) + (x1 + 1 - x1)) / 2);

					step = sign * dy;
					for (x = x1 + 1; x < x2; ++x) {
						scanline[x] += area + step / 2;
						area += step;
					}
					y_crossing += dy * (x2 - (x1 + 1));

					STBTT_assert(STBTT_fabs(area) <= 1.01f);

					scanline[x2] += area + sign * (1 - ((x2 - x2) + (x_bottom - x2)) / 2) * (sy1 - y_crossing);

					scanline_fill[x2] += sign * (sy1 - sy0);
				}
			}
			else {
				// if edge goes outside of box we're drawing, we require
				// clipping logic. since this does not match the intended use
				// of this library, we use a different, very slow brute
				// force implementation
				int x;
				for (x = 0; x < len; ++x) {
					// cases:
					//
					// there can be up to two intersections with the pixel. any intersection
					// with left or right edges can be handled by splitting into two (or three)
					// regions. intersections with top & bottom do not necessitate case-wise logic.
					//
					// the old way of doing this found the intersections with the left & right edges,
					// then used some simple logic to produce up to three segments in sorted order
					// from top-to-bottom. however, this had a problem: if an x edge was epsilon
					// across the x border, then the corresponding y position might not be distinct
					// from the other y segment, and it might ignored as an empty segment. to avoid
					// that, we need to explicitly produce segments based on x positions.

					// rename variables to clear pairs
					float y0 = y_top;
					float x1 = (float)(x);
					float x2 = (float)(x + 1);
					float x3 = xb;
					float y3 = y_bottom;
					float y1, y2;

					// x = e->x + e->dx * (y-y_top)
					// (y-y_top) = (x - e->x) / e->dx
					// y = (x - e->x) / e->dx + y_top
					y1 = (x - x0) / dx + y_top;
					y2 = (x + 1 - x0) / dx + y_top;

					if (x0 < x1 && x3 > x2) {         // three segments descending down-right
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x1, y1);
						stbtt__handle_clipped_edge(scanline, x, e, x1, y1, x2, y2);
						stbtt__handle_clipped_edge(scanline, x, e, x2, y2, x3, y3);
					}
					else if (x3 < x1 && x0 > x2) {  // three segments descending down-left
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x2, y2);
						stbtt__handle_clipped_edge(scanline, x, e, x2, y2, x1, y1);
						stbtt__handle_clipped_edge(scanline, x, e, x1, y1, x3, y3);
					}
					else if (x0 < x1 && x3 > x1) {  // two segments across x, down-right
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x1, y1);
						stbtt__handle_clipped_edge(scanline, x, e, x1, y1, x3, y3);
					}
					else if (x3 < x1 && x0 > x1) {  // two segments across x, down-left
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x1, y1);
						stbtt__handle_clipped_edge(scanline, x, e, x1, y1, x3, y3);
					}
					else if (x0 < x2 && x3 > x2) {  // two segments across x+1, down-right
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x2, y2);
						stbtt__handle_clipped_edge(scanline, x, e, x2, y2, x3, y3);
					}
					else if (x3 < x2 && x0 > x2) {  // two segments across x+1, down-left
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x2, y2);
						stbtt__handle_clipped_edge(scanline, x, e, x2, y2, x3, y3);
					}
					else {  // one segment
						stbtt__handle_clipped_edge(scanline, x, e, x0, y0, x3, y3);
					}
				}
			}
		}
		e = e->next;
	}
}

// directly AA rasterize edges w/o supersampling
static void stbtt__rasterize_sorted_edges(stbtt__bitmap *result, stbtt__edge *e, int n, int vsubsample, int off_x, int off_y, void *userdata)
{
	stbtt__hheap hh = { 0, 0, 0 };
	stbtt__active_edge *active = NULL;
	int y, j = 0, i;
	float scanline_data[129], *scanline, *scanline2;

	STBTT__NOTUSED(vsubsample);

	if (result->w > 64)
		scanline = (float *)STBTT_malloc((result->w * 2 + 1) * sizeof(float), userdata);
	else
		scanline = scanline_data;

	scanline2 = scanline + result->w;

	y = off_y;
	e[n].y0 = (float)(off_y + result->h) + 1;

	while (j < result->h) {
		// find center of pixel for this scanline
		float scan_y_top = y + 0.0f;
		float scan_y_bottom = y + 1.0f;
		stbtt__active_edge **step = &active;

		STBTT_memset(scanline, 0, result->w*sizeof(scanline[0]));
		STBTT_memset(scanline2, 0, (result->w + 1)*sizeof(scanline[0]));

		// update all active edges;
		// remove all active edges that terminate before the top of this scanline
		while (*step) {
			stbtt__active_edge * z = *step;
			if (z->ey <= scan_y_top) {
				*step = z->next; // delete from list
				STBTT_assert(z->direction);
				z->direction = 0;
				stbtt__hheap_free(&hh, z);
			}
			else {
				step = &((*step)->next); // advance through list
			}
		}

		// insert all edges that start before the bottom of this scanline
		while (e->y0 <= scan_y_bottom) {
			if (e->y0 != e->y1) {
				stbtt__active_edge *z = stbtt__new_active(&hh, e, off_x, scan_y_top, userdata);
				if (z != NULL) {
					STBTT_assert(z->ey >= scan_y_top);
					// insert at front
					z->next = active;
					active = z;
				}
			}
			++e;
		}

		// now process all active edges
		if (active)
			stbtt__fill_active_edges_new(scanline, scanline2 + 1, result->w, active, scan_y_top);

		{
			float sum = 0;
			for (i = 0; i < result->w; ++i) {
				float k;
				int m;
				sum += scanline2[i];
				k = scanline[i] + sum;
				k = (float)STBTT_fabs(k) * 255 + 0.5f;
				m = (int)k;
				if (m > 255) m = 255;
				result->pixels[j*result->stride + i] = (unsigned char)m;
			}
		}
		// advance all the edges
		step = &active;
		while (*step) {
			stbtt__active_edge *z = *step;
			z->fx += z->fdx; // advance to position for current scanline
			step = &((*step)->next); // advance through list
		}

		++y;
		++j;
	}

	stbtt__hheap_cleanup(&hh, userdata);

	if (scanline != scanline_data)
		STBTT_free(scanline, userdata);
}
#else
#error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif

#define STBTT__COMPARE(a,b)  ((a)->y0 < (b)->y0)

static void stbtt__sort_edges_ins_sort(stbtt__edge *p, int n)
{
	int i, j;
	for (i = 1; i < n; ++i) {
		stbtt__edge t = p[i], *a = &t;
		j = i;
		while (j > 0) {
			stbtt__edge *b = &p[j - 1];
			int c = STBTT__COMPARE(a, b);
			if (!c) break;
			p[j] = p[j - 1];
			--j;
		}
		if (i != j)
			p[j] = t;
	}
}

static void stbtt__sort_edges_quicksort(stbtt__edge *p, int n)
{
	/* threshhold for transitioning to insertion sort */
	while (n > 12) {
		stbtt__edge t;
		int c01, c12, c, m, i, j;

		/* compute median of three */
		m = n >> 1;
		c01 = STBTT__COMPARE(&p[0], &p[m]);
		c12 = STBTT__COMPARE(&p[m], &p[n - 1]);
		/* if 0 >= mid >= end, or 0 < mid < end, then use mid */
		if (c01 != c12) {
			/* otherwise, we'll need to swap something else to middle */
			int z;
			c = STBTT__COMPARE(&p[0], &p[n - 1]);
			/* 0>mid && mid<n:  0>n => n; 0<n => 0 */
			/* 0<mid && mid>n:  0>n => 0; 0<n => n */
			z = (c == c12) ? 0 : n - 1;
			t = p[z];
			p[z] = p[m];
			p[m] = t;
		}
		/* now p[m] is the median-of-three */
		/* swap it to the beginning so it won't move around */
		t = p[0];
		p[0] = p[m];
		p[m] = t;

		/* partition loop */
		i = 1;
		j = n - 1;
		for (;;) {
			/* handling of equality is crucial here */
			/* for sentinels & efficiency with duplicates */
			for (;; ++i) {
				if (!STBTT__COMPARE(&p[i], &p[0])) break;
			}
			for (;; --j) {
				if (!STBTT__COMPARE(&p[0], &p[j])) break;
			}
			/* make sure we haven't crossed */
			if (i >= j) break;
			t = p[i];
			p[i] = p[j];
			p[j] = t;

			++i;
			--j;
		}
		/* recurse on smaller side, iterate on larger */
		if (j < (n - i)) {
			stbtt__sort_edges_quicksort(p, j);
			p = p + i;
			n = n - i;
		}
		else {
			stbtt__sort_edges_quicksort(p + i, n - i);
			n = j;
		}
	}
}

static void stbtt__sort_edges(stbtt__edge *p, int n)
{
	stbtt__sort_edges_quicksort(p, n);
	stbtt__sort_edges_ins_sort(p, n);
}

typedef struct
{
	float x, y;
} stbtt__point;

static void stbtt__rasterize(stbtt__bitmap *result, stbtt__point *pts, int *wcount, int windings, float scale_x, float scale_y, float shift_x, float shift_y, int off_x, int off_y, int invert, void *userdata)
{
	float y_scale_inv = invert ? -scale_y : scale_y;
	stbtt__edge *e;
	int n, i, j, k, m;
#if STBTT_RASTERIZER_VERSION == 1
	int vsubsample = result->h < 8 ? 15 : 5;
#elif STBTT_RASTERIZER_VERSION == 2
	int vsubsample = 1;
#else
#error "Unrecognized value of STBTT_RASTERIZER_VERSION"
#endif
	// vsubsample should divide 255 evenly; otherwise we won't reach full opacity

	// now we have to blow out the windings into explicit edge lists
	n = 0;
	for (i = 0; i < windings; ++i)
		n += wcount[i];

	e = (stbtt__edge *)STBTT_malloc(sizeof(*e) * (n + 1), userdata); // add an extra one as a sentinel
	if (e == 0) return;
	n = 0;

	m = 0;
	for (i = 0; i < windings; ++i) {
		stbtt__point *p = pts + m;
		m += wcount[i];
		j = wcount[i] - 1;
		for (k = 0; k < wcount[i]; j = k++) {
			int a = k, b = j;
			// skip the edge if horizontal
			if (p[j].y == p[k].y)
				continue;
			// add edge from j to k to the list
			e[n].invert = 0;
			if (invert ? p[j].y > p[k].y : p[j].y < p[k].y) {
				e[n].invert = 1;
				a = j, b = k;
			}
			e[n].x0 = p[a].x * scale_x + shift_x;
			e[n].y0 = (p[a].y * y_scale_inv + shift_y) * vsubsample;
			e[n].x1 = p[b].x * scale_x + shift_x;
			e[n].y1 = (p[b].y * y_scale_inv + shift_y) * vsubsample;
			++n;
		}
	}

	// now sort the edges by their highest point (should snap to integer, and then by x)
	//STBTT_sort(e, n, sizeof(e[0]), stbtt__edge_compare);
	stbtt__sort_edges(e, n);

	// now, traverse the scanlines and find the intersections on each scanline, use xor winding rule
	stbtt__rasterize_sorted_edges(result, e, n, vsubsample, off_x, off_y, userdata);

	STBTT_free(e, userdata);
}

static void stbtt__add_point(stbtt__point *points, int n, float x, float y)
{
	if (!points) return; // during first pass, it's unallocated
	points[n].x = x;
	points[n].y = y;
}

// tesselate until threshhold p is happy... @TODO warped to compensate for non-linear stretching
static int stbtt__tesselate_curve(stbtt__point *points, int *num_points, float x0, float y0, float x1, float y1, float x2, float y2, float objspace_flatness_squared, int n)
{
	// midpoint
	float mx = (x0 + 2 * x1 + x2) / 4;
	float my = (y0 + 2 * y1 + y2) / 4;
	// versus directly drawn line
	float dx = (x0 + x2) / 2 - mx;
	float dy = (y0 + y2) / 2 - my;
	if (n > 16) // 65536 segments on one curve better be enough!
		return 1;
	if (dx*dx + dy*dy > objspace_flatness_squared) { // half-pixel error allowed... need to be smaller if AA
		stbtt__tesselate_curve(points, num_points, x0, y0, (x0 + x1) / 2.f, (y0 + y1) / 2.f, mx, my, objspace_flatness_squared, n + 1);
		stbtt__tesselate_curve(points, num_points, mx, my, (x1 + x2) / 2.f, (y1 + y2) / 2.f, x2, y2, objspace_flatness_squared, n + 1);
	}
	else {
		stbtt__add_point(points, *num_points, x2, y2);
		*num_points = *num_points + 1;
	}
	return 1;
}

// returns number of contours
static stbtt__point *stbtt_FlattenCurves(stbtt_vertex *vertices, int num_verts, float objspace_flatness, int **contour_lengths, int *num_contours, void *userdata)
{
	stbtt__point *points = 0;
	int num_points = 0;

	float objspace_flatness_squared = objspace_flatness * objspace_flatness;
	int i, n = 0, start = 0, pass;

	// count how many "moves" there are to get the contour count
	for (i = 0; i < num_verts; ++i)
		if (vertices[i].type == STBTT_vmove)
			++n;

	*num_contours = n;
	if (n == 0) return 0;

	*contour_lengths = (int *)STBTT_malloc(sizeof(**contour_lengths) * n, userdata);

	if (*contour_lengths == 0) {
		*num_contours = 0;
		return 0;
	}

	// make two passes through the points so we don't need to realloc
	for (pass = 0; pass < 2; ++pass) {
		float x = 0, y = 0;
		if (pass == 1) {
			points = (stbtt__point *)STBTT_malloc(num_points * sizeof(points[0]), userdata);
			if (points == NULL) goto error;
		}
		num_points = 0;
		n = -1;
		for (i = 0; i < num_verts; ++i) {
			switch (vertices[i].type) {
			case STBTT_vmove:
				// start the next contour
				if (n >= 0)
					(*contour_lengths)[n] = num_points - start;
				++n;
				start = num_points;

				x = vertices[i].x, y = vertices[i].y;
				stbtt__add_point(points, num_points++, x, y);
				break;
			case STBTT_vline:
				x = vertices[i].x, y = vertices[i].y;
				stbtt__add_point(points, num_points++, x, y);
				break;
			case STBTT_vcurve:
				stbtt__tesselate_curve(points, &num_points, x, y,
					vertices[i].cx, vertices[i].cy,
					vertices[i].x, vertices[i].y,
					objspace_flatness_squared, 0);
				x = vertices[i].x, y = vertices[i].y;
				break;
			}
		}
		(*contour_lengths)[n] = num_points - start;
	}

	return points;
error:
	STBTT_free(points, userdata);
	STBTT_free(*contour_lengths, userdata);
	*contour_lengths = 0;
	*num_contours = 0;
	return NULL;
}

STBTT_DEF void stbtt_Rasterize(stbtt__bitmap *result, float flatness_in_pixels, stbtt_vertex *vertices, int num_verts, float scale_x, float scale_y, float shift_x, float shift_y, int x_off, int y_off, int invert, void *userdata)
{
	float scale = scale_x > scale_y ? scale_y : scale_x;
	int winding_count, *winding_lengths;
	stbtt__point *windings = stbtt_FlattenCurves(vertices, num_verts, flatness_in_pixels / scale, &winding_lengths, &winding_count, userdata);
	if (windings) {
		stbtt__rasterize(result, windings, winding_lengths, winding_count, scale_x, scale_y, shift_x, shift_y, x_off, y_off, invert, userdata);
		STBTT_free(winding_lengths, userdata);
		STBTT_free(windings, userdata);
	}
}

STBTT_DEF void stbtt_FreeBitmap(unsigned char *bitmap, void *userdata)
{
	STBTT_free(bitmap, userdata);
}

STBTT_DEF unsigned char *stbtt_GetGlyphBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int glyph, int *width, int *height, int *xoff, int *yoff)
{
	int ix0, iy0, ix1, iy1;
	stbtt__bitmap gbm;
	stbtt_vertex *vertices;
	int num_verts = stbtt_GetGlyphShape(info, glyph, &vertices);

	if (scale_x == 0) scale_x = scale_y;
	if (scale_y == 0) {
		if (scale_x == 0) {
			STBTT_free(vertices, info->userdata);
			return NULL;
		}
		scale_y = scale_x;
	}

	stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x, shift_y, &ix0, &iy0, &ix1, &iy1);

	// now we get the size
	gbm.w = (ix1 - ix0);
	gbm.h = (iy1 - iy0);
	gbm.pixels = NULL; // in case we error

	if (width) *width = gbm.w;
	if (height) *height = gbm.h;
	if (xoff) *xoff = ix0;
	if (yoff) *yoff = iy0;

	if (gbm.w && gbm.h) {
		gbm.pixels = (unsigned char *)STBTT_malloc(gbm.w * gbm.h, info->userdata);
		if (gbm.pixels) {
			gbm.stride = gbm.w;

			stbtt_Rasterize(&gbm, 0.35f, vertices, num_verts, scale_x, scale_y, shift_x, shift_y, ix0, iy0, 1, info->userdata);
		}
	}
	STBTT_free(vertices, info->userdata);
	return gbm.pixels;
}

STBTT_DEF unsigned char *stbtt_GetGlyphBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int glyph, int *width, int *height, int *xoff, int *yoff)
{
	return stbtt_GetGlyphBitmapSubpixel(info, scale_x, scale_y, 0.0f, 0.0f, glyph, width, height, xoff, yoff);
}

STBTT_DEF void stbtt_MakeGlyphBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int glyph)
{
	int ix0, iy0;
	stbtt_vertex *vertices;
	int num_verts = stbtt_GetGlyphShape(info, glyph, &vertices);
	stbtt__bitmap gbm;

	stbtt_GetGlyphBitmapBoxSubpixel(info, glyph, scale_x, scale_y, shift_x, shift_y, &ix0, &iy0, 0, 0);
	gbm.pixels = output;
	gbm.w = out_w;
	gbm.h = out_h;
	gbm.stride = out_stride;

	if (gbm.w && gbm.h)
		stbtt_Rasterize(&gbm, 0.35f, vertices, num_verts, scale_x, scale_y, shift_x, shift_y, ix0, iy0, 1, info->userdata);

	STBTT_free(vertices, info->userdata);
}

STBTT_DEF void stbtt_MakeGlyphBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int glyph)
{
	stbtt_MakeGlyphBitmapSubpixel(info, output, out_w, out_h, out_stride, scale_x, scale_y, 0.0f, 0.0f, glyph);
}

STBTT_DEF unsigned char *stbtt_GetCodepointBitmapSubpixel(const stbtt_fontinfo *info, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint, int *width, int *height, int *xoff, int *yoff)
{
	return stbtt_GetGlyphBitmapSubpixel(info, scale_x, scale_y, shift_x, shift_y, stbtt_FindGlyphIndex(info, codepoint), width, height, xoff, yoff);
}

STBTT_DEF void stbtt_MakeCodepointBitmapSubpixel(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, float shift_x, float shift_y, int codepoint)
{
	stbtt_MakeGlyphBitmapSubpixel(info, output, out_w, out_h, out_stride, scale_x, scale_y, shift_x, shift_y, stbtt_FindGlyphIndex(info, codepoint));
}

STBTT_DEF unsigned char *stbtt_GetCodepointBitmap(const stbtt_fontinfo *info, float scale_x, float scale_y, int codepoint, int *width, int *height, int *xoff, int *yoff)
{
	return stbtt_GetCodepointBitmapSubpixel(info, scale_x, scale_y, 0.0f, 0.0f, codepoint, width, height, xoff, yoff);
}

STBTT_DEF void stbtt_MakeCodepointBitmap(const stbtt_fontinfo *info, unsigned char *output, int out_w, int out_h, int out_stride, float scale_x, float scale_y, int codepoint)
{
	stbtt_MakeCodepointBitmapSubpixel(info, output, out_w, out_h, out_stride, scale_x, scale_y, 0.0f, 0.0f, codepoint);
}

//////////////////////////////////////////////////////////////////////////////
//
// bitmap baking
//
// This is SUPER-CRAPPY packing to keep source code small

STBTT_DEF int stbtt_BakeFontBitmap(const unsigned char *data, int offset,  // font location (use offset=0 for plain .ttf)
	float pixel_height,                     // height of font in pixels
	unsigned char *pixels, int pw, int ph,  // bitmap to be filled in
	int first_char, int num_chars,          // characters to bake
	stbtt_bakedchar *chardata)
{
	float scale;
	int x, y, bottom_y, i;
	stbtt_fontinfo f;
	f.userdata = NULL;
	if (!stbtt_InitFont(&f, data, offset))
		return -1;
	STBTT_memset(pixels, 0, pw*ph); // background of 0 around pixels
	x = y = 1;
	bottom_y = 1;

	scale = stbtt_ScaleForPixelHeight(&f, pixel_height);

	for (i = 0; i < num_chars; ++i) {
		int advance, lsb, x0, y0, x1, y1, gw, gh;
		int g = stbtt_FindGlyphIndex(&f, first_char + i);
		stbtt_GetGlyphHMetrics(&f, g, &advance, &lsb);
		stbtt_GetGlyphBitmapBox(&f, g, scale, scale, &x0, &y0, &x1, &y1);
		gw = x1 - x0;
		gh = y1 - y0;
		if (x + gw + 1 >= pw)
			y = bottom_y, x = 1; // advance to next row
		if (y + gh + 1 >= ph) // check if it fits vertically AFTER potentially moving to next row
			return -i;
		STBTT_assert(x + gw < pw);
		STBTT_assert(y + gh < ph);
		stbtt_MakeGlyphBitmap(&f, pixels + x + y*pw, gw, gh, pw, scale, scale, g);
		chardata[i].x0 = (stbtt_int16)x;
		chardata[i].y0 = (stbtt_int16)y;
		chardata[i].x1 = (stbtt_int16)(x + gw);
		chardata[i].y1 = (stbtt_int16)(y + gh);
		chardata[i].xadvance = scale * advance;
		chardata[i].xoff = (float)x0;
		chardata[i].yoff = (float)y0;
		x = x + gw + 1;
		if (y + gh + 1 > bottom_y)
			bottom_y = y + gh + 1;
	}
	return bottom_y;
}

STBTT_DEF void stbtt_GetBakedQuad(stbtt_bakedchar *chardata, int pw, int ph, int char_index, float *xpos, float *ypos, stbtt_aligned_quad *q, int opengl_fillrule)
{
	float d3d_bias = opengl_fillrule ? 0 : -0.5f;
	float ipw = 1.0f / pw, iph = 1.0f / ph;
	stbtt_bakedchar *b = chardata + char_index;
	int round_x = STBTT_ifloor((*xpos + b->xoff) + 0.5f);
	int round_y = STBTT_ifloor((*ypos + b->yoff) + 0.5f);

	q->x0 = round_x + d3d_bias;
	q->y0 = round_y + d3d_bias;
	q->x1 = round_x + b->x1 - b->x0 + d3d_bias;
	q->y1 = round_y + b->y1 - b->y0 + d3d_bias;

	q->s0 = b->x0 * ipw;
	q->t0 = b->y0 * iph;
	q->s1 = b->x1 * ipw;
	q->t1 = b->y1 * iph;

	*xpos += b->xadvance;
}

//////////////////////////////////////////////////////////////////////////////
//
// rectangle packing replacement routines if you don't have stb_rect_pack.h
//

#ifndef STB_RECT_PACK_VERSION

typedef int stbrp_coord;

////////////////////////////////////////////////////////////////////////////////////
//                                                                                //
//                                                                                //
// COMPILER WARNING ?!?!?                                                         //
//                                                                                //
//                                                                                //
// if you get a compile warning due to these symbols being defined more than      //
// once, move #include "stb_rect_pack.h" before #include "stb_truetype.h"         //
//                                                                                //
////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	int width, height;
	int x, y, bottom_y;
} stbrp_context;

typedef struct
{
	unsigned char x;
} stbrp_node;

struct stbrp_rect
{
	stbrp_coord x, y;
	int id, w, h, was_packed;
};

static void stbrp_init_target(stbrp_context *con, int pw, int ph, stbrp_node *nodes, int num_nodes)
{
	con->width = pw;
	con->height = ph;
	con->x = 0;
	con->y = 0;
	con->bottom_y = 0;
	STBTT__NOTUSED(nodes);
	STBTT__NOTUSED(num_nodes);
}

static void stbrp_pack_rects(stbrp_context *con, stbrp_rect *rects, int num_rects)
{
	int i;
	for (i = 0; i < num_rects; ++i) {
		if (con->x + rects[i].w > con->width) {
			con->x = 0;
			con->y = con->bottom_y;
		}
		if (con->y + rects[i].h > con->height)
			break;
		rects[i].x = con->x;
		rects[i].y = con->y;
		rects[i].was_packed = 1;
		con->x += rects[i].w;
		if (con->y + rects[i].h > con->bottom_y)
			con->bottom_y = con->y + rects[i].h;
	}
	for (; i < num_rects; ++i)
		rects[i].was_packed = 0;
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// bitmap baking
//
// This is SUPER-AWESOME (tm Ryan Gordon) packing using stb_rect_pack.h. If
// stb_rect_pack.h isn't available, it uses the BakeFontBitmap strategy.

STBTT_DEF int stbtt_PackBegin(stbtt_pack_context *spc, unsigned char *pixels, int pw, int ph, int stride_in_bytes, int padding, void *alloc_context)
{
	stbrp_context *context = (stbrp_context *)STBTT_malloc(sizeof(*context), alloc_context);
	int            num_nodes = pw - padding;
	stbrp_node    *nodes = (stbrp_node    *)STBTT_malloc(sizeof(*nodes) * num_nodes, alloc_context);

	if (context == NULL || nodes == NULL) {
		if (context != NULL) STBTT_free(context, alloc_context);
		if (nodes != NULL) STBTT_free(nodes, alloc_context);
		return 0;
	}

	spc->user_allocator_context = alloc_context;
	spc->width = pw;
	spc->height = ph;
	spc->pixels = pixels;
	spc->pack_info = context;
	spc->nodes = nodes;
	spc->padding = padding;
	spc->stride_in_bytes = stride_in_bytes != 0 ? stride_in_bytes : pw;
	spc->h_oversample = 1;
	spc->v_oversample = 1;

	stbrp_init_target(context, pw - padding, ph - padding, nodes, num_nodes);

	if (pixels)
		STBTT_memset(pixels, 0, pw*ph); // background of 0 around pixels

	return 1;
}

STBTT_DEF void stbtt_PackEnd(stbtt_pack_context *spc)
{
	STBTT_free(spc->nodes, spc->user_allocator_context);
	STBTT_free(spc->pack_info, spc->user_allocator_context);
}

STBTT_DEF void stbtt_PackSetOversampling(stbtt_pack_context *spc, unsigned int h_oversample, unsigned int v_oversample)
{
	STBTT_assert(h_oversample <= STBTT_MAX_OVERSAMPLE);
	STBTT_assert(v_oversample <= STBTT_MAX_OVERSAMPLE);
	if (h_oversample <= STBTT_MAX_OVERSAMPLE)
		spc->h_oversample = h_oversample;
	if (v_oversample <= STBTT_MAX_OVERSAMPLE)
		spc->v_oversample = v_oversample;
}

#define STBTT__OVER_MASK  (STBTT_MAX_OVERSAMPLE-1)

static void stbtt__h_prefilter(unsigned char *pixels, int w, int h, int stride_in_bytes, unsigned int kernel_width)
{
	unsigned char buffer[STBTT_MAX_OVERSAMPLE];
	int safe_w = w - kernel_width;
	int j;
	STBTT_memset(buffer, 0, STBTT_MAX_OVERSAMPLE); // suppress bogus warning from VS2013 -analyze
	for (j = 0; j < h; ++j) {
		int i;
		unsigned int total;
		STBTT_memset(buffer, 0, kernel_width);

		total = 0;

		// make kernel_width a constant in common cases so compiler can optimize out the divide
		switch (kernel_width) {
		case 2:
			for (i = 0; i <= safe_w; ++i) {
				total += pixels[i] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i];
				pixels[i] = (unsigned char)(total / 2);
			}
			break;
		case 3:
			for (i = 0; i <= safe_w; ++i) {
				total += pixels[i] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i];
				pixels[i] = (unsigned char)(total / 3);
			}
			break;
		case 4:
			for (i = 0; i <= safe_w; ++i) {
				total += pixels[i] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i];
				pixels[i] = (unsigned char)(total / 4);
			}
			break;
		case 5:
			for (i = 0; i <= safe_w; ++i) {
				total += pixels[i] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i];
				pixels[i] = (unsigned char)(total / 5);
			}
			break;
		default:
			for (i = 0; i <= safe_w; ++i) {
				total += pixels[i] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i];
				pixels[i] = (unsigned char)(total / kernel_width);
			}
			break;
		}

		for (; i < w; ++i) {
			STBTT_assert(pixels[i] == 0);
			total -= buffer[i & STBTT__OVER_MASK];
			pixels[i] = (unsigned char)(total / kernel_width);
		}

		pixels += stride_in_bytes;
	}
}

static void stbtt__v_prefilter(unsigned char *pixels, int w, int h, int stride_in_bytes, unsigned int kernel_width)
{
	unsigned char buffer[STBTT_MAX_OVERSAMPLE];
	int safe_h = h - kernel_width;
	int j;
	STBTT_memset(buffer, 0, STBTT_MAX_OVERSAMPLE); // suppress bogus warning from VS2013 -analyze
	for (j = 0; j < w; ++j) {
		int i;
		unsigned int total;
		STBTT_memset(buffer, 0, kernel_width);

		total = 0;

		// make kernel_width a constant in common cases so compiler can optimize out the divide
		switch (kernel_width) {
		case 2:
			for (i = 0; i <= safe_h; ++i) {
				total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
				pixels[i*stride_in_bytes] = (unsigned char)(total / 2);
			}
			break;
		case 3:
			for (i = 0; i <= safe_h; ++i) {
				total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
				pixels[i*stride_in_bytes] = (unsigned char)(total / 3);
			}
			break;
		case 4:
			for (i = 0; i <= safe_h; ++i) {
				total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
				pixels[i*stride_in_bytes] = (unsigned char)(total / 4);
			}
			break;
		case 5:
			for (i = 0; i <= safe_h; ++i) {
				total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
				pixels[i*stride_in_bytes] = (unsigned char)(total / 5);
			}
			break;
		default:
			for (i = 0; i <= safe_h; ++i) {
				total += pixels[i*stride_in_bytes] - buffer[i & STBTT__OVER_MASK];
				buffer[(i + kernel_width) & STBTT__OVER_MASK] = pixels[i*stride_in_bytes];
				pixels[i*stride_in_bytes] = (unsigned char)(total / kernel_width);
			}
			break;
		}

		for (; i < h; ++i) {
			STBTT_assert(pixels[i*stride_in_bytes] == 0);
			total -= buffer[i & STBTT__OVER_MASK];
			pixels[i*stride_in_bytes] = (unsigned char)(total / kernel_width);
		}

		pixels += 1;
	}
}

static float stbtt__oversample_shift(int oversample)
{
	if (!oversample)
		return 0.0f;

	// The prefilter is a box filter of width "oversample",
	// which shifts phase by (oversample - 1)/2 pixels in
	// oversampled space. We want to shift in the opposite
	// direction to counter this.
	return (float)-(oversample - 1) / (2.f * (float)oversample);
}

// rects array must be big enough to accommodate all characters in the given ranges
STBTT_DEF int stbtt_PackFontRangesGatherRects(stbtt_pack_context *spc, stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects)
{
	int i, j, k;

	k = 0;
	for (i = 0; i < num_ranges; ++i) {
		float fh = ranges[i].font_size;
		float scale = fh > 0 ? stbtt_ScaleForPixelHeight(info, fh) : stbtt_ScaleForMappingEmToPixels(info, -fh);
		ranges[i].h_oversample = (unsigned char)spc->h_oversample;
		ranges[i].v_oversample = (unsigned char)spc->v_oversample;
		for (j = 0; j < ranges[i].num_chars; ++j) {
			int x0, y0, x1, y1;
			int codepoint = ranges[i].array_of_unicode_codepoints == NULL ? ranges[i].first_unicode_codepoint_in_range + j : ranges[i].array_of_unicode_codepoints[j];
			int glyph = stbtt_FindGlyphIndex(info, codepoint);
			stbtt_GetGlyphBitmapBoxSubpixel(info, glyph,
				scale * spc->h_oversample,
				scale * spc->v_oversample,
				0, 0,
				&x0, &y0, &x1, &y1);
			rects[k].w = (stbrp_coord)(x1 - x0 + spc->padding + spc->h_oversample - 1);
			rects[k].h = (stbrp_coord)(y1 - y0 + spc->padding + spc->v_oversample - 1);
			++k;
		}
	}

	return k;
}

// rects array must be big enough to accommodate all characters in the given ranges
STBTT_DEF int stbtt_PackFontRangesRenderIntoRects(stbtt_pack_context *spc, stbtt_fontinfo *info, stbtt_pack_range *ranges, int num_ranges, stbrp_rect *rects)
{
	int i, j, k, return_value = 1;

	// save current values
	int old_h_over = spc->h_oversample;
	int old_v_over = spc->v_oversample;

	k = 0;
	for (i = 0; i < num_ranges; ++i) {
		float fh = ranges[i].font_size;
		float scale = fh > 0 ? stbtt_ScaleForPixelHeight(info, fh) : stbtt_ScaleForMappingEmToPixels(info, -fh);
		float recip_h, recip_v, sub_x, sub_y;
		spc->h_oversample = ranges[i].h_oversample;
		spc->v_oversample = ranges[i].v_oversample;
		recip_h = 1.0f / spc->h_oversample;
		recip_v = 1.0f / spc->v_oversample;
		sub_x = stbtt__oversample_shift(spc->h_oversample);
		sub_y = stbtt__oversample_shift(spc->v_oversample);
		for (j = 0; j < ranges[i].num_chars; ++j) {
			stbrp_rect *r = &rects[k];
			if (r->was_packed) {
				stbtt_packedchar *bc = &ranges[i].chardata_for_range[j];
				int advance, lsb, x0, y0, x1, y1;
				int codepoint = ranges[i].array_of_unicode_codepoints == NULL ? ranges[i].first_unicode_codepoint_in_range + j : ranges[i].array_of_unicode_codepoints[j];
				int glyph = stbtt_FindGlyphIndex(info, codepoint);
				stbrp_coord pad = (stbrp_coord)spc->padding;

				// pad on left and top
				r->x += pad;
				r->y += pad;
				r->w -= pad;
				r->h -= pad;
				stbtt_GetGlyphHMetrics(info, glyph, &advance, &lsb);
				stbtt_GetGlyphBitmapBox(info, glyph,
					scale * spc->h_oversample,
					scale * spc->v_oversample,
					&x0, &y0, &x1, &y1);
				stbtt_MakeGlyphBitmapSubpixel(info,
					spc->pixels + r->x + r->y*spc->stride_in_bytes,
					r->w - spc->h_oversample + 1,
					r->h - spc->v_oversample + 1,
					spc->stride_in_bytes,
					scale * spc->h_oversample,
					scale * spc->v_oversample,
					0, 0,
					glyph);

				if (spc->h_oversample > 1)
					stbtt__h_prefilter(spc->pixels + r->x + r->y*spc->stride_in_bytes,
					r->w, r->h, spc->stride_in_bytes,
					spc->h_oversample);

				if (spc->v_oversample > 1)
					stbtt__v_prefilter(spc->pixels + r->x + r->y*spc->stride_in_bytes,
					r->w, r->h, spc->stride_in_bytes,
					spc->v_oversample);

				bc->x0 = (stbtt_int16)r->x;
				bc->y0 = (stbtt_int16)r->y;
				bc->x1 = (stbtt_int16)(r->x + r->w);
				bc->y1 = (stbtt_int16)(r->y + r->h);
				bc->xadvance = scale * advance;
				bc->xoff = (float)x0 * recip_h + sub_x;
				bc->yoff = (float)y0 * recip_v + sub_y;
				bc->xoff2 = (x0 + r->w) * recip_h + sub_x;
				bc->yoff2 = (y0 + r->h) * recip_v + sub_y;
			}
			else {
				return_value = 0; // if any fail, report failure
			}

			++k;
		}
	}

	// restore original values
	spc->h_oversample = old_h_over;
	spc->v_oversample = old_v_over;

	return return_value;
}

STBTT_DEF void stbtt_PackFontRangesPackRects(stbtt_pack_context *spc, stbrp_rect *rects, int num_rects)
{
	stbrp_pack_rects((stbrp_context *)spc->pack_info, rects, num_rects);
}

STBTT_DEF int stbtt_PackFontRanges(stbtt_pack_context *spc, unsigned char *fontdata, int font_index, stbtt_pack_range *ranges, int num_ranges)
{
	stbtt_fontinfo info;
	int i, j, n, return_value = 1;
	//stbrp_context *context = (stbrp_context *) spc->pack_info;
	stbrp_rect    *rects;

	// flag all characters as NOT packed
	for (i = 0; i < num_ranges; ++i)
		for (j = 0; j < ranges[i].num_chars; ++j)
			ranges[i].chardata_for_range[j].x0 =
			ranges[i].chardata_for_range[j].y0 =
			ranges[i].chardata_for_range[j].x1 =
			ranges[i].chardata_for_range[j].y1 = 0;

	n = 0;
	for (i = 0; i < num_ranges; ++i)
		n += ranges[i].num_chars;

	rects = (stbrp_rect *)STBTT_malloc(sizeof(*rects) * n, spc->user_allocator_context);
	if (rects == NULL)
		return 0;

	info.userdata = spc->user_allocator_context;
	stbtt_InitFont(&info, fontdata, stbtt_GetFontOffsetForIndex(fontdata, font_index));

	n = stbtt_PackFontRangesGatherRects(spc, &info, ranges, num_ranges, rects);

	stbtt_PackFontRangesPackRects(spc, rects, n);

	return_value = stbtt_PackFontRangesRenderIntoRects(spc, &info, ranges, num_ranges, rects);

	STBTT_free(rects, spc->user_allocator_context);
	return return_value;
}

STBTT_DEF int stbtt_PackFontRange(stbtt_pack_context *spc, unsigned char *fontdata, int font_index, float font_size,
	int first_unicode_codepoint_in_range, int num_chars_in_range, stbtt_packedchar *chardata_for_range)
{
	stbtt_pack_range range;
	range.first_unicode_codepoint_in_range = first_unicode_codepoint_in_range;
	range.array_of_unicode_codepoints = NULL;
	range.num_chars = num_chars_in_range;
	range.chardata_for_range = chardata_for_range;
	range.font_size = font_size;
	return stbtt_PackFontRanges(spc, fontdata, font_index, &range, 1);
}

STBTT_DEF void stbtt_GetPackedQuad(stbtt_packedchar *chardata, int pw, int ph, int char_index, float *xpos, float *ypos, stbtt_aligned_quad *q, int align_to_integer)
{
	float ipw = 1.0f / pw, iph = 1.0f / ph;
	stbtt_packedchar *b = chardata + char_index;

	if (align_to_integer) {
		float x = (float)STBTT_ifloor((*xpos + b->xoff) + 0.5f);
		float y = (float)STBTT_ifloor((*ypos + b->yoff) + 0.5f);
		q->x0 = x;
		q->y0 = y;
		q->x1 = x + b->xoff2 - b->xoff;
		q->y1 = y + b->yoff2 - b->yoff;
	}
	else {
		q->x0 = *xpos + b->xoff;
		q->y0 = *ypos + b->yoff;
		q->x1 = *xpos + b->xoff2;
		q->y1 = *ypos + b->yoff2;
	}

	q->s0 = b->x0 * ipw;
	q->t0 = b->y0 * iph;
	q->s1 = b->x1 * ipw;
	q->t1 = b->y1 * iph;

	*xpos += b->xadvance;
}


//////////////////////////////////////////////////////////////////////////////
//
// font name matching -- recommended not to use this
//

// check if a utf8 string contains a prefix which is the utf16 string; if so return length of matching utf8 string
static stbtt_int32 stbtt__CompareUTF8toUTF16_bigendian_prefix(const stbtt_uint8 *s1, stbtt_int32 len1, const stbtt_uint8 *s2, stbtt_int32 len2)
{
	stbtt_int32 i = 0;

	// convert utf16 to utf8 and compare the results while converting
	while (len2) {
		stbtt_uint16 ch = s2[0] * 256 + s2[1];
		if (ch < 0x80) {
			if (i >= len1) return -1;
			if (s1[i++] != ch) return -1;
		}
		else if (ch < 0x800) {
			if (i + 1 >= len1) return -1;
			if (s1[i++] != 0xc0 + (ch >> 6)) return -1;
			if (s1[i++] != 0x80 + (ch & 0x3f)) return -1;
		}
		else if (ch >= 0xd800 && ch < 0xdc00) {
			stbtt_uint32 c;
			stbtt_uint16 ch2 = s2[2] * 256 + s2[3];
			if (i + 3 >= len1) return -1;
			c = ((ch - 0xd800) << 10) + (ch2 - 0xdc00) + 0x10000;
			if (s1[i++] != 0xf0 + (c >> 18)) return -1;
			if (s1[i++] != 0x80 + ((c >> 12) & 0x3f)) return -1;
			if (s1[i++] != 0x80 + ((c >> 6) & 0x3f)) return -1;
			if (s1[i++] != 0x80 + ((c)& 0x3f)) return -1;
			s2 += 2; // plus another 2 below
			len2 -= 2;
		}
		else if (ch >= 0xdc00 && ch < 0xe000) {
			return -1;
		}
		else {
			if (i + 2 >= len1) return -1;
			if (s1[i++] != 0xe0 + (ch >> 12)) return -1;
			if (s1[i++] != 0x80 + ((ch >> 6) & 0x3f)) return -1;
			if (s1[i++] != 0x80 + ((ch)& 0x3f)) return -1;
		}
		s2 += 2;
		len2 -= 2;
	}
	return i;
}

STBTT_DEF int stbtt_CompareUTF8toUTF16_bigendian(const char *s1, int len1, const char *s2, int len2)
{
	return len1 == stbtt__CompareUTF8toUTF16_bigendian_prefix((const stbtt_uint8*)s1, len1, (const stbtt_uint8*)s2, len2);
}

// returns results in whatever encoding you request... but note that 2-byte encodings
// will be BIG-ENDIAN... use stbtt_CompareUTF8toUTF16_bigendian() to compare
STBTT_DEF const char *stbtt_GetFontNameString(const stbtt_fontinfo *font, int *length, int platformID, int encodingID, int languageID, int nameID)
{
	stbtt_int32 i, count, stringOffset;
	stbtt_uint8 *fc = font->data;
	stbtt_uint32 offset = font->fontstart;
	stbtt_uint32 nm = stbtt__find_table(fc, offset, "name");
	if (!nm) return NULL;

	count = ttUSHORT(fc + nm + 2);
	stringOffset = nm + ttUSHORT(fc + nm + 4);
	for (i = 0; i < count; ++i) {
		stbtt_uint32 loc = nm + 6 + 12 * i;
		if (platformID == ttUSHORT(fc + loc + 0) && encodingID == ttUSHORT(fc + loc + 2)
			&& languageID == ttUSHORT(fc + loc + 4) && nameID == ttUSHORT(fc + loc + 6)) {
			*length = ttUSHORT(fc + loc + 8);
			return (const char *)(fc + stringOffset + ttUSHORT(fc + loc + 10));
		}
	}
	return NULL;
}

static int stbtt__matchpair(stbtt_uint8 *fc, stbtt_uint32 nm, stbtt_uint8 *name, stbtt_int32 nlen, stbtt_int32 target_id, stbtt_int32 next_id)
{
	stbtt_int32 i;
	stbtt_int32 count = ttUSHORT(fc + nm + 2);
	stbtt_int32 stringOffset = nm + ttUSHORT(fc + nm + 4);

	for (i = 0; i < count; ++i) {
		stbtt_uint32 loc = nm + 6 + 12 * i;
		stbtt_int32 id = ttUSHORT(fc + loc + 6);
		if (id == target_id) {
			// find the encoding
			stbtt_int32 platform = ttUSHORT(fc + loc + 0), encoding = ttUSHORT(fc + loc + 2), language = ttUSHORT(fc + loc + 4);

			// is this a Unicode encoding?
			if (platform == 0 || (platform == 3 && encoding == 1) || (platform == 3 && encoding == 10)) {
				stbtt_int32 slen = ttUSHORT(fc + loc + 8);
				stbtt_int32 off = ttUSHORT(fc + loc + 10);

				// check if there's a prefix match
				stbtt_int32 matchlen = stbtt__CompareUTF8toUTF16_bigendian_prefix(name, nlen, fc + stringOffset + off, slen);
				if (matchlen >= 0) {
					// check for target_id+1 immediately following, with same encoding & language
					if (i + 1 < count && ttUSHORT(fc + loc + 12 + 6) == next_id && ttUSHORT(fc + loc + 12) == platform && ttUSHORT(fc + loc + 12 + 2) == encoding && ttUSHORT(fc + loc + 12 + 4) == language) {
						slen = ttUSHORT(fc + loc + 12 + 8);
						off = ttUSHORT(fc + loc + 12 + 10);
						if (slen == 0) {
							if (matchlen == nlen)
								return 1;
						}
						else if (matchlen < nlen && name[matchlen] == ' ') {
							++matchlen;
							if (stbtt_CompareUTF8toUTF16_bigendian((char*)(name + matchlen), nlen - matchlen, (char*)(fc + stringOffset + off), slen))
								return 1;
						}
					}
					else {
						// if nothing immediately following
						if (matchlen == nlen)
							return 1;
					}
				}
			}

			// @TODO handle other encodings
		}
	}
	return 0;
}

static int stbtt__matches(stbtt_uint8 *fc, stbtt_uint32 offset, stbtt_uint8 *name, stbtt_int32 flags)
{
	stbtt_int32 nlen = (stbtt_int32)STBTT_strlen((char *)name);
	stbtt_uint32 nm, hd;
	if (!stbtt__isfont(fc + offset)) return 0;

	// check italics/bold/underline flags in macStyle...
	if (flags) {
		hd = stbtt__find_table(fc, offset, "head");
		if ((ttUSHORT(fc + hd + 44) & 7) != (flags & 7)) return 0;
	}

	nm = stbtt__find_table(fc, offset, "name");
	if (!nm) return 0;

	if (flags) {
		// if we checked the macStyle flags, then just check the family and ignore the subfamily
		if (stbtt__matchpair(fc, nm, name, nlen, 16, -1))  return 1;
		if (stbtt__matchpair(fc, nm, name, nlen, 1, -1))  return 1;
		if (stbtt__matchpair(fc, nm, name, nlen, 3, -1))  return 1;
	}
	else {
		if (stbtt__matchpair(fc, nm, name, nlen, 16, 17))  return 1;
		if (stbtt__matchpair(fc, nm, name, nlen, 1, 2))  return 1;
		if (stbtt__matchpair(fc, nm, name, nlen, 3, -1))  return 1;
	}

	return 0;
}

STBTT_DEF int stbtt_FindMatchingFont(const unsigned char *font_collection, const char *name_utf8, stbtt_int32 flags)
{
	stbtt_int32 i;
	for (i = 0;; ++i) {
		stbtt_int32 off = stbtt_GetFontOffsetForIndex(font_collection, i);
		if (off < 0) return off;
		if (stbtt__matches((stbtt_uint8 *)font_collection, off, (stbtt_uint8*)name_utf8, flags))
			return off;
	}
}

#endif // STB_TRUETYPE_IMPLEMENTATION


// FULL VERSION HISTORY
//
//   1.11 (2016-04-02) fix unused-variable warning
//   1.10 (2016-04-02) allow user-defined fabs() replacement
//                     fix memory leak if fontsize=0.0
//                     fix warning from duplicate typedef
//   1.09 (2016-01-16) warning fix; avoid crash on outofmem; use alloc userdata for PackFontRanges
//   1.08 (2015-09-13) document stbtt_Rasterize(); fixes for vertical & horizontal edges
//   1.07 (2015-08-01) allow PackFontRanges to accept arrays of sparse codepoints;
//                     allow PackFontRanges to pack and render in separate phases;
//                     fix stbtt_GetFontOFfsetForIndex (never worked for non-0 input?);
//                     fixed an assert() bug in the new rasterizer
//                     replace assert() with STBTT_assert() in new rasterizer
//   1.06 (2015-07-14) performance improvements (~35% faster on x86 and x64 on test machine)
//                     also more precise AA rasterizer, except if shapes overlap
//                     remove need for STBTT_sort
//   1.05 (2015-04-15) fix misplaced definitions for STBTT_STATIC
//   1.04 (2015-04-15) typo in example
//   1.03 (2015-04-12) STBTT_STATIC, fix memory leak in new packing, various fixes
//   1.02 (2014-12-10) fix various warnings & compile issues w/ stb_rect_pack, C++
//   1.01 (2014-12-08) fix subpixel position when oversampling to exactly match
//                        non-oversampled; STBTT_POINT_SIZE for packed case only
//   1.00 (2014-12-06) add new PackBegin etc. API, w/ support for oversampling
//   0.99 (2014-09-18) fix multiple bugs with subpixel rendering (ryg)
//   0.9  (2014-08-07) support certain mac/iOS fonts without an MS platformID
//   0.8b (2014-07-07) fix a warning
//   0.8  (2014-05-25) fix a few more warnings
//   0.7  (2013-09-25) bugfix: subpixel glyph bug fixed in 0.5 had come back
//   0.6c (2012-07-24) improve documentation
//   0.6b (2012-07-20) fix a few more warnings
//   0.6  (2012-07-17) fix warnings; added stbtt_ScaleForMappingEmToPixels,
//                        stbtt_GetFontBoundingBox, stbtt_IsGlyphEmpty
//   0.5  (2011-12-09) bugfixes:
//                        subpixel glyph renderer computed wrong bounding box
//                        first vertex of shape can be off-curve (FreeSans)
//   0.4b (2011-12-03) fixed an error in the font baking example
//   0.4  (2011-12-01) kerning, subpixel rendering (tor)
//                    bugfixes for:
//                        codepoint-to-glyph conversion using table fmt=12
//                        codepoint-to-glyph conversion using table fmt=4
//                        stbtt_GetBakedQuad with non-square texture (Zer)
//                    updated Hello World! sample to use kerning and subpixel
//                    fixed some warnings
//   0.3  (2009-06-24) cmap fmt=12, compound shapes (MM)
//                    userdata, malloc-from-userdata, non-zero fill (stb)
//   0.2  (2009-03-11) Fix unsigned/signed char warnings
//   0.1  (2009-03-09) First public release
//

// end stb_truetype.h

// ------------------------------------------------------------------------------------------------

ztFontID _zt_fontMakeFromSTB(const char *name, void *data, i32 data_size, i32 size_in_pixels, const char *charset, i32 charset_size)
{
	i32 tex_size = 1024; // TODO(josh): make this dynamic based off charset

	stbtt_fontinfo f;
	if (!stbtt_InitFont(&f, (const byte *)data, 0))
		return ztInvalidID;

	byte *pixel_data = zt_mallocStructArray(byte, tex_size * tex_size);
	zt_memSet(pixel_data, 0, tex_size * tex_size); // background of 0 around pixels

	int padding = 0;
	int spacing = 2;
	int x, y, bottom_y;
	x = y = bottom_y = spacing;

	r32 scale = stbtt_ScaleForPixelHeight(&f, (r32)size_in_pixels);

	zt_assert(zt_game->fonts_count < zt_elementsOf(zt_game->fonts));
	ztFontID font_id = zt_game->fonts_count++;
	ztFont *font = &zt_game->fonts[font_id];
	zt_memSet(font, zt_sizeof(ztFont), 0);

	font->arena = zt_memGetGlobalArena();

	zt_strCpy(font->name, zt_elementsOf(font->name), name, zt_strLen(name));
	font->size_pixels = size_in_pixels;
	font->glyph_count = charset_size;
	
	font->glyph_code_point = zt_mallocStructArray(i32, charset_size);
	font->glyphs = zt_mallocStructArray(ztFont::ztGlyph, charset_size);

	r32 min_size_x = 9999, max_size_x = 0;

	i32 space_idx = -1;
	zt_fiz(charset_size) {
		int advance, lsb, x0, y0, x1, y1, gw, gh;
		i32 code_point = zt_strCodepoint(charset, i);
		int g = stbtt_FindGlyphIndex(&f, code_point);
		stbtt_GetGlyphHMetrics(&f, g, &advance, &lsb);
		stbtt_GetGlyphBitmapBox(&f, g, scale, scale, &x0, &y0, &x1, &y1);
		gw = x1 - x0;
		gh = y1 - y0;
		if (x + gw + spacing >= tex_size)
			y = bottom_y, x = spacing; // advance to next row
		if (y + gh + spacing >= tex_size) // check if it fits vertically AFTER potentially moving to next row
			return ztInvalidID;

		zt_assert(x + gw < tex_size);
		zt_assert(y + gh < tex_size);
		stbtt_MakeGlyphBitmap(&f, pixel_data + x + y*tex_size, gw, gh, tex_size, scale, scale, g);

		font->glyph_code_point[i] = code_point;
		font->glyphs[i].tex_uv.x = (x - padding) / (r32)tex_size;
		font->glyphs[i].tex_uv.y = (y - padding) / (r32)tex_size;
		font->glyphs[i].tex_uv.z = (x + gw + padding * 2) / (r32)tex_size;
		font->glyphs[i].tex_uv.w = (y + gh + padding * 2) / (r32)tex_size;

		font->glyphs[i].size.x = gw / (r32)zt_game->win_game_settings[0].pixels_per_unit;
		font->glyphs[i].size.y = gh / (r32)zt_game->win_game_settings[0].pixels_per_unit;
		font->line_height = zt_max(font->line_height, font->glyphs[i].size.y);

		font->glyphs[i].offset.x = (r32)x0 / zt_game->win_game_settings[0].pixels_per_unit;
		font->glyphs[i].offset.y = (r32)y0 / zt_game->win_game_settings[0].pixels_per_unit;

		font->glyphs[i].x_adv = (scale * advance) / (r32)zt_game->win_game_settings[0].pixels_per_unit;

		x = x + gw + spacing;
		if (y + gh + spacing > bottom_y)
			bottom_y = y + gh + spacing;

		if (code_point == ' ')
			space_idx = i;
	}

	font->line_spacing = ((r32)size_in_pixels * .1f) / zt_game->win_game_settings[0].pixels_per_unit;

	int advance, lsb;
	stbtt_GetGlyphHMetrics(&f, stbtt_FindGlyphIndex(&f, ' '), &advance, &lsb);
	font->space_width = (scale * advance) / zt_game->win_game_settings[0].pixels_per_unit;

	if (space_idx != -1) {
		font->glyphs[space_idx].size.x = font->space_width;
	}

	byte *pixel_data_full = zt_mallocStructArray(byte, tex_size * tex_size * 4);
	int pixel_data_idx = 0;
	zt_fiz(tex_size * tex_size) {
		pixel_data_full[pixel_data_idx++] = pixel_data[i] == 0 ? 0 : 255;
		pixel_data_full[pixel_data_idx++] = pixel_data[i] == 0 ? 0 : 255;
		pixel_data_full[pixel_data_idx++] = pixel_data[i] == 0 ? 0 : 255;
		pixel_data_full[pixel_data_idx++] = pixel_data[i];
	}
	zt_free(pixel_data);

	font->texture = zt_textureMake(pixel_data_full, tex_size, tex_size, 0);
	zt_free(pixel_data_full);

	if (font->texture == ztInvalidID) {
		zt_fontFree(font_id);		
		return ztInvalidID;
	}

	return font_id;
}

// ------------------------------------------------------------------------------------------------

#endif // implementation guard
#endif // implementation