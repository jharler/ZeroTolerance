/***************************************************************************************************************************************************************************************************
	file: zt_hotswap.h v 0.00 (active initial development)
	
	This software is dual-licensed to the public domain and under the following
	license: you are granted a perpetual, irrevocable license to copy, modify,
	publish, and distribute this file as you see fit.
	
	No warranty is offered or implied.  Use this at your own risk.
	
 ***************************************************************************************************************************************************************************************************
   
    Zero Tolerance Hotswap Library

	In exactly one cpp source file for the exe build of your project, you must:

		#define ZT_HOTSWAP_IMPLEMENTATION
		#define ZT_HOTSWAP_LOADER
		#include "zt_hotswap.h"

	Also, in exactly one cpp source file for the dll build of your project, you must:

		#define ZT_HOTSWAP_IMPLEMENTATION
		#define ZT_HOTSWAP_DLL
		#include "zt_hotswap.h"
    
 ***************************************************************************************************************************************************************************************************

    Options:
		#define ZT_HOTSWAP_COMBINED_BUILD
			Tells the hotswap library that this build combines both the loader and dll together into one executable.
   

 ***************************************************************************************************************************************************************************************************

	Implimentation Options: (only used with ZT_HOTSWAP_IMPLEMENTATION #include)


 ***************************************************************************************************************************************************************************************************/

#ifndef __zt_hotswap_h_included__
#define __zt_hotswap_h_included__

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#if defined(ZT_HOTSWAP_LOADER)

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_GAME_NAME
#define ZT_GAME_NAME "ZeroTolerance Project"
#endif

#ifndef ZT_LOG_FILE
#define ZT_LOG_FILE "log.txt"
#endif

#define ZT_GAME_FUNC_SETTINGS       zt_loaderGameSettings
#define ZT_GAME_FUNC_INIT           zt_loaderGameInit
#define ZT_GAME_FUNC_SCREENCHANGE   zt_loaderGameScreenChange
#define ZT_GAME_FUNC_CLEANUP        zt_loaderGameCleanup
#define ZT_GAME_FUNC_LOOP           zt_loaderGameLoop

#include "zt_tools.h"
#include "zt_game.h"
#include "zt_game_gui.h"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#elif defined(ZT_HOTSWAP_DLL)

#include "zt_tools.h"
#include "zt_game.h"
#include "zt_game_gui.h"

ZT_DLLEXPORT bool dll_reload(void *memory);
ZT_DLLEXPORT bool dll_unload(void *memory);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#else
#error "ZT_HOTSWAP_LOADER or ZT_HOTSWAP_DLL must be defined before #including zt_hotswap.h"
#endif

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // include guard

#if defined(ZT_HOTSWAP_IMPLEMENTATION) || defined(ZT_HOTSWAP_INTERNAL_DECLARATIONS)

#ifndef __zt_hotswap_h_internal_included__
#define __zt_hotswap_h_internal_included__

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#if defined(ZT_HOTSWAP_LOADER)

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef LDR_DLL_NAME
#define LDR_DLL_NAME	"zt_editor.dll"
#endif

typedef bool (dll_settings_Func    ) (ztGameDetails *, ztGameSettings *);
typedef bool (dll_init_Func        ) (ztGameDetails *, ztGameSettings *, void **game_memory);
typedef bool (dll_reload_Func      ) (void *);
typedef bool (dll_unload_Func      ) (void *);
typedef void (dll_cleanup_Func     ) (void *);
typedef void (dll_screenChange_Func) (ztGameSettings *, void *);
typedef bool (dll_gameLoop_Func    ) (void *, r32);

#if defined(ZT_HOTSWAP_COMBINED_BUILD)
bool dll_settings     (ztGameDetails *, ztGameSettings *);
bool dll_init         (ztGameDetails *, ztGameSettings *, void **game_memory);
void dll_cleanup      (void *);
void dll_screenChange (ztGameSettings *, void *);
bool dll_gameLoop     (void *, r32);
#endif

// ================================================================================================================================================================================================

struct ztHotswapDll
{
	void *game_memory;

#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	HMODULE                game_dll;
	char                   game_dll_name[ztFileMaxPath];
	ztDirectoryMonitor     dir_mon;
#	endif

	dll_settings_Func     *dll_settings;
	dll_init_Func         *dll_init;
	dll_reload_Func       *dll_reload;
	dll_unload_Func       *dll_unload;
	dll_cleanup_Func      *dll_cleanup;
	dll_screenChange_Func *dll_screenChange;
	dll_gameLoop_Func     *dll_gameLoop;

	ztGameDetails *details;
};


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#elif defined(ZT_HOTSWAP_DLL)

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // ZT_HOTSWAP

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // internal include guard
#endif // internal declarations


#if defined(ZT_HOTSWAP_IMPLEMENTATION)
#ifndef __zt_hotswap_implementation__
#define __zt_hotswap_implementation__

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#if defined(ZT_HOTSWAP_LOADER)

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal ztHotswapDll g_dll;
ztInternal ztFile       g_log;

// ================================================================================================================================================================================================

ZT_FUNC_LOG_CALLBACK(zt_loaderLogCallback)
{
	zt_fileWrite(&g_log, message, zt_strSize(message) - 1);
	zt_fileWrite(&g_log, "\n", 1);
}

// ================================================================================================================================================================================================

ztInternal void zt_loaderBuildDllCleanup()
{
#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	char cleanup_file[ztFileMaxPath];
	zt_fileConcatFileToPath(cleanup_file, zt_elementsOf(cleanup_file), g_dll.details->app_path, "..\\..\\..\\build\\msvc\\cleanup.bat");

	if (zt_fileExists(cleanup_file)) {
		char cleanup_path[ztFileMaxPath];
		zt_fileGetFullPath(cleanup_file, cleanup_path, zt_elementsOf(cleanup_path));

		char current_path[ztFileMaxPath];
		zt_fileGetCurrentPath(current_path, zt_elementsOf(current_path));
		zt_fileSetCurrentPath(cleanup_path);

		zt_strMakePrintf(cleanup_cmd, ztFileMaxPath, "cmd.exe /c \"%s\"", cleanup_file);
		zt_processRun(cleanup_cmd);

		zt_fileSetCurrentPath(current_path);
	}
	else {
		zt_logCritical("cleanup file not found: %s", cleanup_file);
	}
#	endif
}

// ================================================================================================================================================================================================

bool zt_loaderLoadDll(const char *dll_name, bool initial_load)
{
#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	if (initial_load) {
		zt_loaderBuildDllCleanup();
	}

	zt_logInfo("Loading game DLL: %s", dll_name);

	if (g_dll.game_dll != NULL) {
		if (g_dll.dll_unload) {
			g_dll.dll_unload(g_dll.game_memory);
		}
		FreeLibrary(g_dll.game_dll);
	}

	if (!initial_load) {
		zt_sleep(.2f);
	}

	HMODULE dll = LoadLibraryA(dll_name);

	if (dll == NULL) {
		for (int i = 0; i < 100 && dll == NULL && GetLastError() == 32; ++i) {
			zt_sleep(.1f);
			dll = LoadLibraryA(dll_name);
		}
		if (dll == NULL) {
			zt_logCritical("Unable to load DLL: %s (%d)", dll_name, GetLastError());
			return false;
		}
	}

	g_dll.game_dll = dll;

	zt_dllSetGlobals_Func *zt_dllSetGlobals = (zt_dllSetGlobals_Func *)GetProcAddress(g_dll.game_dll, "zt_dllSetGlobals");
	if (!zt_dllSetGlobals) {
		zt_logCritical("Game DLL does not contain a SetGlobals function");
		return false;
	}
	zt_dllSendGlobals(zt_dllSetGlobals);

	zt_dllSetGameGlobals_Func *zt_dllSetGameGlobals = (zt_dllSetGameGlobals_Func *)GetProcAddress(g_dll.game_dll, "zt_dllSetGameGlobals");
	if (!zt_dllSetGameGlobals) {
		zt_logCritical("Game DLL does not contain a SetGameGlobals function");
		return false;
	}

#	if defined(ZT_OPENGL)
	zt_dllSetOpenGLGlobals_Func *zt_dllSetOpenGLGlobals = (zt_dllSetOpenGLGlobals_Func *)GetProcAddress(g_dll.game_dll, "zt_dllSetOpenGLGlobals");
	if (!zt_dllSetOpenGLGlobals) {
		zt_logCritical("Game DLL does not contain a SetOpenGLGlobals function");
		return false;
	}
	zt_dllSendGameGlobals(zt_dllSetGameGlobals, zt_dllSetOpenGLGlobals);

	if (!initial_load) {
		zt_dllSendOpenGLGlobals(zt_dllSetOpenGLGlobals);
	}
#	else
	zt_dllSendGameGlobals(zt_dllSetGameGlobals);
#	endif // ZT_OPENGL

	zt_dllSetGameGuiGlobals_Func *zt_dllSetGameGuiGlobals = (zt_dllSetGameGuiGlobals_Func *)GetProcAddress(g_dll.game_dll, "zt_dllSetGameGuiGlobals");
	if (zt_dllSetGameGuiGlobals) {
		zt_dllSendGameGuiGlobals(zt_dllSetGameGuiGlobals);
	}

	g_dll.dll_settings     = (dll_settings_Func     *)GetProcAddress(g_dll.game_dll, "dll_settings");
	g_dll.dll_init         = (dll_init_Func         *)GetProcAddress(g_dll.game_dll, "dll_init");
	g_dll.dll_reload       = (dll_reload_Func       *)GetProcAddress(g_dll.game_dll, "dll_reload");
	g_dll.dll_unload       = (dll_unload_Func       *)GetProcAddress(g_dll.game_dll, "dll_unload");
	g_dll.dll_cleanup      = (dll_cleanup_Func      *)GetProcAddress(g_dll.game_dll, "dll_cleanup");
	g_dll.dll_screenChange = (dll_screenChange_Func *)GetProcAddress(g_dll.game_dll, "dll_screenChange");
	g_dll.dll_gameLoop     = (dll_gameLoop_Func     *)GetProcAddress(g_dll.game_dll, "dll_gameLoop");

	if (!initial_load && g_dll.dll_reload) {
		g_dll.dll_reload(g_dll.game_memory);
	}

	zt_strCpy(g_dll.game_dll_name, zt_elementsOf(g_dll.game_dll_name), dll_name);

	zt_logInfo("Game DLL successfully loaded.");

	zt_loaderBuildDllCleanup();

#	else
	g_dll.dll_settings     = dll_settings;
	g_dll.dll_init         = dll_init;
	g_dll.dll_cleanup      = dll_cleanup;
	g_dll.dll_screenChange = dll_screenChange;
	g_dll.dll_gameLoop     = dll_gameLoop;
#	endif

	return true;
}

// ================================================================================================================================================================================================

#define ZT_LOADER_BUILD_BATCH_FILE_64BIT_DEBUG "..\\..\\..\\build\\msvc\\build_d64.bat"
#define ZT_LOADER_BUILD_BATCH_FILE_64BIT_RELEASE "..\\..\\..\\build\\msvc\\build_r64.bat"

#define ZT_LOADER_BUILD_BATCH_FILE_32BIT_DEBUG "..\\..\\..\\build\\msvc\\build_d.bat"
#define ZT_LOADER_BUILD_BATCH_FILE_32BIT_RELEASE "..\\..\\..\\build\\msvc\\build_r.bat"

#define ZT_LOADER_BUILD_BATCH_FILE_CLEANUP "..\\..\\..\\build\\msvc\\cleanup.bat"

#if defined(ZT_64BIT)
#	define ZT_LOADER_BUILD_BATCH_FILE zt_debugOnly(ZT_LOADER_BUILD_BATCH_FILE_64BIT_DEBUG) zt_releaseOnly(ZT_LOADER_BUILD_BATCH_FILE_64BIT_RELEASE)
#else
#	define ZT_LOADER_BUILD_BATCH_FILE zt_debugOnly(ZT_LOADER_BUILD_BATCH_FILE_32BIT_DEBUG) zt_releaseOnly(ZT_LOADER_BUILD_BATCH_FILE_32BIT_RELEASE)
#endif

// ================================================================================================================================================================================================

void zt_loaderCreateBuildBatchFiles()
{
	struct local
	{
		static bool fileOpen(ztFile *file, const char *file_name)
		{
			char build_file[ztFileMaxPath];
			zt_fileConcatFileToPath(build_file, zt_elementsOf(build_file), g_dll.details->app_path, file_name);

			return zt_fileOpen(file, build_file, ztFileOpenMethod_WriteOver);
		}
	};

	char build_file[ztFileMaxPath];
	zt_fileConcatFileToPath(build_file, zt_elementsOf(build_file), g_dll.details->app_path, ZT_LOADER_BUILD_BATCH_FILE);

	if (!zt_fileExists(build_file)) {

		const char *zt_include_dir = "E:\\Development\\Projects\\ZeroTolerance";
		const char *zt_dll_name = "zt_editor";

		ztFile file;
		if (local::fileOpen(&file, ZT_LOADER_BUILD_BATCH_FILE_32BIT_DEBUG)) {
			zt_fileWritef(&file,
				"@echo off\n"
				"set random_val=%%random%%\n\n"

				"set compile_flags=-MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W3 -wd4201 -wd4100 -wd4189 -DZT_DLL -FC -Z7 -LD -I\"%s\"\n"
				"set link_flags=-incremental:no -opt:ref -PDB:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.pdb -OUT:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.dll user32.lib gdi32.lib winmm.lib shell32.lib\n\n"

				"call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\"\n"
				"cl %%compile_flags%% ..\\..\\src\\unity_dll.cpp -Fm%s.map /link %%link_flags%%\n", zt_include_dir, zt_dll_name, zt_dll_name, zt_dll_name);
			zt_fileClose(&file);
		}

		if (local::fileOpen(&file, ZT_LOADER_BUILD_BATCH_FILE_32BIT_RELEASE)) {
			zt_fileWritef(&file,
				"@echo off\n"
				"set random_val=%%random%%\n\n"

				"set compile_flags=-MT -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W3 -wd4201 -wd4100 -wd4189 -DZT_DLL -FC -Z7 -LD -I\"%s\"\n"
				"set link_flags=-incremental:no -opt:ref -PDB:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.pdb -OUT:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.dll user32.lib gdi32.lib winmm.lib shell32.lib\n\n"

				"call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\"\n"
				"cl %%compile_flags%% ..\\..\\src\\unity_dll.cpp -Fm%s.map /link %%link_flags%%\n", zt_include_dir, zt_dll_name, zt_dll_name, zt_dll_name);
			zt_fileClose(&file);
		}

		if (local::fileOpen(&file, ZT_LOADER_BUILD_BATCH_FILE_64BIT_DEBUG)) {
			zt_fileWritef(&file,
				"@echo off\n"
				"set random_val=%%random%%\n\n"

				"set compile_flags=-MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W3 -wd4201 -wd4100 -wd4189 -DZT_DLL -FC -Z7 -LD -I\"%s\"\n"
				"set link_flags=-incremental:no -opt:ref -PDB:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.pdb -OUT:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.dll user32.lib gdi32.lib winmm.lib shell32.lib\n\n"

				"call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\" amd64\n"
				"cl %%compile_flags%% ..\\..\\src\\unity_dll.cpp -Fm%s.map /link %%link_flags%%\n", zt_include_dir, zt_dll_name, zt_dll_name, zt_dll_name);
			zt_fileClose(&file);
		}

		if (local::fileOpen(&file, ZT_LOADER_BUILD_BATCH_FILE_64BIT_RELEASE)) {
			zt_fileWritef(&file,
				"@echo off\n"
				"set random_val=%%random%%\n\n"

				"set compile_flags=-MT -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W3 -wd4201 -wd4100 -wd4189 -DZT_DLL -FC -Z7 -LD -I\"%s\"\n"
				"set link_flags=-incremental:no -opt:ref -PDB:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.pdb -OUT:..\\..\\bin\\%%1\\%%random_val%%.hotload.%s.dll user32.lib gdi32.lib winmm.lib shell32.lib\n\n"

				"call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\" amd64\n"
				"cl %%compile_flags%% ..\\..\\src\\unity_dll.cpp -Fm%s.map /link %%link_flags%%\n", zt_include_dir, zt_dll_name, zt_dll_name, zt_dll_name);
			zt_fileClose(&file);
		}

		if (local::fileOpen(&file, ZT_LOADER_BUILD_BATCH_FILE_CLEANUP)) {
			zt_fileWritef(&file,
				"@echo off\n"
				"del /Q ..\\..\\bin\\debug\\x86\\*.hotload.*\n"
				"del /Q ..\\..\\bin\\debug\\x64\\*.hotload.*\n"
				"del /Q ..\\..\\bin\\release\\x86\\*.hotload.*\n"
				"del /Q ..\\..\\bin\\release\\x64\\*.hotload.*\n");
			zt_fileClose(&file);
		}
	}
}

// ================================================================================================================================================================================================

void zt_loaderBuildDll()
{
#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	zt_logInfo("Building game DLL");

	zt_loaderCreateBuildBatchFiles();

	char *build_file_name = ZT_LOADER_BUILD_BATCH_FILE;

	char build_file[ztFileMaxPath];
	zt_fileConcatFileToPath(build_file, zt_elementsOf(build_file), g_dll.details->app_path, build_file_name);

	if (zt_fileExists(build_file)) {
		char build_path[ztFileMaxPath];
		zt_fileGetFullPath(build_file, build_path, zt_elementsOf(build_path));

		char current_path[ztFileMaxPath];
		zt_fileGetCurrentPath(current_path, zt_elementsOf(current_path));
		zt_fileSetCurrentPath(build_path);

		int size = zt_kilobytes(32);
		char *build_results = zt_mallocStructArrayArena(char, size, zt_memGetTempArena());

		zt_strMakePrintf(build_cmd, ztFileMaxPath, "cmd.exe /c \"\"%s\" \""ZT_BUILD_DESTINATION"\"\"", build_file);

		zt_processRun(build_cmd, build_results, size);

		ztToken lines[100];
		int lines_count = zt_strTokenize(build_results, "\r\n", lines, zt_elementsOf(lines));

		zt_fiz(zt_min(lines_count, zt_elementsOf(lines))) {
			char line[1024];
			zt_strCpy(line, zt_elementsOf(line), zt_strMoveForward(build_results, lines[i].beg), lines[i].len);

			if (zt_strFindPos(line, ") : error ", 0) != ztStrPosNotFound) {
				zt_logCritical(line);
			}
			else {
				zt_logInfo(line);
			}
		}

		if (lines_count >= zt_elementsOf(lines)) {
			zt_logInfo("%d more lines...", lines_count - zt_elementsOf(lines));
		}

		zt_freeArena(build_results, zt_memGetTempArena());

		zt_fileSetCurrentPath(current_path);
	}
	else {
		zt_logCritical("build file not found: %s", build_file);
	}
#	endif
}

// ================================================================================================================================================================================================

#if !defined(ZT_HOTSWAP_COMBINED_BUILD)
ZT_FUNC_CONSOLE_COMMAND(zt_loaderBuildDllConsoleCommand)
{
	zt_loaderBuildDll();
}
#endif

// ================================================================================================================================================================================================

bool zt_loaderGameSettings(ztGameDetails* details, ztGameSettings* settings)
{
	zt_fileOpen(&g_log, ZT_LOG_FILE, ztFileOpenMethod_WriteOver);
	zt_logAddCallback(zt_loaderLogCallback, ztLogMessageLevel_Verbose);

	g_dll.details = details;

	zt_strMakePrintf(dll_name, ztFileMaxPath, "%s\\" LDR_DLL_NAME, details->app_path);
	if (!zt_loaderLoadDll(dll_name, true)) {
		return false;
	}

	if (g_dll.dll_settings == nullptr || g_dll.dll_init == nullptr) {
		zt_logCritical("Game DLL does not contain a startup or init function");
		return false;
	}

	if (!g_dll.dll_settings(details, settings)) {
		zt_logCritical("Game DLL failed to startup");
		return false;
	}
	else {
		char bytes[128];
		zt_strBytesToString(bytes, zt_elementsOf(bytes), settings->memory);
		zt_logInfo("Game DLL requesting %s of memory", bytes);
	}

#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	zt_directoryMonitor(&g_dll.dir_mon, details->app_path, false, ztDirectoryMonitorFlags_All);
#	endif

	return true;
}

// ================================================================================================================================================================================================

bool zt_loaderGameInit(ztGameDetails* details, ztGameSettings* settings)
{
	zt_guiInitGlobalMemory(zt_memGetGlobalArena());

	if (!g_dll.dll_init(details, settings, &g_dll.game_memory)) {
		zt_logCritical("Game DLL failed to initialize");
		return false;
	}

#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	zt_consoleAddCommand("build", "Compiles the DLL", ZT_FUNCTION_POINTER_TO_VAR(zt_loaderBuildDllConsoleCommand), ZT_FUNCTION_POINTER_TO_VAR_NULL);
#	endif

	return true;
}

// ================================================================================================================================================================================================

void zt_loaderGameCleanup()
{
	if (g_dll.dll_cleanup) {
		g_dll.dll_cleanup(g_dll.game_memory);
	}
	if (g_dll.dll_unload) {
		g_dll.dll_unload(g_dll.game_memory);
	}

#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	FreeLibrary(g_dll.game_dll);
#	endif

	zt_loaderBuildDllCleanup();

	g_dll.dll_settings     = nullptr;
	g_dll.dll_init         = nullptr;
	g_dll.dll_reload       = nullptr;
	g_dll.dll_unload       = nullptr;
	g_dll.dll_cleanup      = nullptr;
	g_dll.dll_screenChange = nullptr;
	g_dll.dll_gameLoop     = nullptr;

	zt_logRemoveCallback(zt_loaderLogCallback);
	zt_fileClose(&g_log);
}

// ================================================================================================================================================================================================

void zt_loaderGameScreenChange(ztGameSettings *settings)
{
	if (g_dll.dll_screenChange) {
		g_dll.dll_screenChange(settings, g_dll.game_memory);
	}
}

// ================================================================================================================================================================================================

bool zt_loaderGameLoop(r32 dt)
{
	ztInputKeys *keys = zt_inputKeysAccessState();
	if (keys[ztInputKeys_Control].pressed() && keys[ztInputKeys_Menu].pressed() && keys[ztInputKeys_Shift].pressed()) {
		if (keys[ztInputKeys_B].justPressed()) {
			zt_loaderBuildDll();
		}
	}

#	if !defined(ZT_HOTSWAP_COMBINED_BUILD)
	if (zt_directoryMonitorHasChanged(&g_dll.dir_mon)) {
		while (zt_directoryMonitorHasChanged(&g_dll.dir_mon)) {
			;
		}

		char file_buffer[1024 * 16];
		zt_getDirectoryFiles(g_dll.details->app_path, file_buffer, zt_elementsOf(file_buffer), false);

		const char *files = file_buffer;
		while (files) {
			int end = zt_strFindPos(files, "\n", 0);
			if (end == ztStrPosNotFound) end = zt_strLen(files);
			if (end == 0) break;

			if (zt_striEndsWith(files, end, ".hotload." LDR_DLL_NAME, zt_strLen(".hotload." LDR_DLL_NAME))) {
				char file[ztFileMaxPath];
				zt_strCpy(file, ztFileMaxPath, files, end);

				if (!zt_strEquals(file, g_dll.game_dll_name)) {
					if (!zt_loaderLoadDll(file, false)) {
						zt_logCritical("Unable to reload game DLL");
						return false;
					}

					break;
				}
			}

			files = zt_strMoveForward(files, end + 1);
		}
	}
#	endif

	return g_dll.dll_gameLoop(g_dll.game_memory, dt);
}



// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#elif defined(ZT_HOTSWAP_DLL)

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifdef ZT_HOTSWAP_DLL_PROCESS_RELOAD_FUNC
ZT_DLLEXPORT void ZT_HOTSWAP_DLL_PROCESS_RELOAD_FUNC(void*);
#endif

#ifdef ZT_HOTSWAP_DLL_PROCESS_UNLOAD_FUNC
ZT_DLLEXPORT void ZT_HOTSWAP_DLL_PROCESS_UNLOAD_FUNC(void*);
#endif

ZT_DLLEXPORT bool dll_reload(void *memory)
{
#	if defined(ZT_DLL)
	zt_dllGuiLoad();

#	if defined(ZT_HOTSWAP_DLL_PROCESS_RELOAD_FUNC)
	ZT_HOTSWAP_DLL_PROCESS_RELOAD_FUNC(memory);
#	endif

#	endif
	return true;
}

// ================================================================================================================================================================================================

ZT_DLLEXPORT bool dll_unload(void *memory)
{
#	if defined(ZT_DLL)
	zt_dllGuiUnload();

#	if defined(ZT_HOTSWAP_DLL_PROCESS_UNLOAD_FUNC)
	ZT_HOTSWAP_DLL_PROCESS_UNLOAD_FUNC(memory);
#	endif

#	endif
	return true;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // ZT_HOTSWAP

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


#endif // ZT_HOTSWAP_IMPLEMENTATION

#endif // include guard