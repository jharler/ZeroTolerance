/**************************************************************************************************
 ** file: zt_testgame.cpp
 **
 ** This library is in the public domain.  Do with it what you will.
 **
 **************************************************************************************************
 **
 ** implementation notes:
 ** 
 **************************************************************************************************/

// headers ========================================================================================

#define ZT_TOOLS_IMPLEMENTATION
#define ZT_GAME_IMPLEMENTATION

#define ZT_GAME_NAME			"ZeroTolerance Test Game"
#define ZT_GAME_LOCAL_ONLY
#define ZT_GAME_FUNC_SETTINGS	game_settings
#define ZT_GAME_FUNC_INIT		game_init
#define ZT_GAME_FUNC_CLEANUP	game_cleanup
#define ZT_GAME_FUNC_LOOP		game_loop

#include "zt_tools.h"
#include "zt_game.h"


// types/enums/defines ============================================================================

// structs/classes ================================================================================

struct ztGame
{
	ztGameDetails *details;
	ztGameSettings *settings;
};


// variables ======================================================================================

ztGame *g_game = nullptr;


// private functions ==============================================================================

// ------------------------------------------------------------------------------------------------

// functions ======================================================================================

bool game_settings(ztGameDetails* details, ztGameSettings* settings)
{
	zt_strMakePrintf(ini_file, ztFileMaxPath, "%s%csettings.cfg", details->user_path, ztFilePathSeparator);
	settings->memory = zt_iniFileGetValue(ini_file, "general", "app_memory", (i32)zt_megabytes(64));

	settings->native_w = settings->screen_w = 1920;
	settings->native_h = settings->screen_h = 1080;
	//settings->renderer = ztRenderer_OpenGL;
	settings->renderer = ztRenderer_DirectX;
	//settings->renderer_flags |= ztRendererFlags_Vsync;

	return true;
}

// ------------------------------------------------------------------------------------------------

bool game_init(ztGameDetails* game_details, ztGameSettings* game_settings)
{
	g_game = zt_malloc_struct(ztGame);
	*g_game = {};
	g_game->details = game_details;
	g_game->settings = game_settings;

	return true;
}

// ------------------------------------------------------------------------------------------------

void game_cleanup()
{
	zt_free(g_game);
}

// ------------------------------------------------------------------------------------------------

bool game_loop(r32 dt)
{
	// color cycle the background
	{
		const ztVec4 colors[] = {
			ztVec4(1, 0, 0, 1),
			ztVec4(0, 1, 0, 1),
			ztVec4(0, 0, 1, 1),
			ztVec4(1, 1, 0, 1),
			ztVec4(1, 0, 1, 1),
			ztVec4(0, 1, 1, 1),
		};

		static i32 color_idx = 0;
		static r32 color_time = 0;

		color_time += dt;
		if (color_time > 1) {
			color_time -= 1;
			color_idx += 1;
		}

		ztVec4 color = ztVec4::lerp(colors[color_idx % zt_elementsOf(colors)], colors[(color_idx + 1) % zt_elementsOf(colors)], color_time);
		zt_rendererClear(color);
	}

	// test changing renderers
	{
		static r32 swap_time = 0;
		swap_time += dt;

		if (swap_time > 10) {
			swap_time -= 10;
			zt_rendererRequestChange(g_game->settings->renderer == ztRenderer_OpenGL ? ztRenderer_DirectX : ztRenderer_OpenGL);
		}
	}

	// calculate frame time
	{
		static r32 dt_accum = 0;
		static int frame = 0;

		dt_accum += dt;
		frame += 1;
		if (dt_accum > 1) {
			// show frame time in microseconds.  to hit 60 fps, each frame must take less than 16,666 microseconds (or 16.666 ms)
			zt_logDebug("average frame rate: %.6f us/f (%.2f fps)", (dt_accum / frame) * 1000.f, 1.f / (dt_accum / frame));
			dt_accum = 0;
			frame = 0;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------
