/**************************************************************************************************
 ** file: zt_testgame.cpp
 **
 ** This library is in the public domain.  Do with it what you will.
 **
 **************************************************************************************************
 **
 ** implementation notes:
 ** 
 ** Unit tests for the ZeroTolerance single header file libraries.
 **
 ** These tests aren't comprehensive and are probably terrible.  Essentially, I'll use the library
 ** and add tests for edge cases that I run into so at least I won't re-introduce the same bugs once
 ** they've been fixed.
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
	zt_sleep(.01f);

	return true;
}

// ------------------------------------------------------------------------------------------------
