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

//#define ZT_MEM_ARENA_LOG_DETAILS
//#define ZT_OPENGL_DIAGNOSE
#define ZT_DIRECTX_DEBUGGING

#define ZT_GAME_NAME			"ZeroTolerance Test Game"
#define ZT_GAME_LOCAL_ONLY
#define ZT_GAME_FUNC_SETTINGS		game_settings
#define ZT_GAME_FUNC_INIT			game_init
#define ZT_GAME_FUNC_SCREENCHANGE	game_screenChange
#define ZT_GAME_FUNC_CLEANUP		game_cleanup
#define ZT_GAME_FUNC_LOOP			game_loop

#include "zt_tools.h"
#include "zt_game.h"


// types/enums/defines ============================================================================

// structs/classes ================================================================================

struct ztGame
{
	ztGameDetails *details;
	ztGameSettings *settings;


	ztMemoryArena* asset_arena;
	ztAssetManager asset_mgr;

	ztCamera camera, gui_camera;

	ztShaderID shader_id;
	ztTextureID tex_id_crate;
	ztFontID font_id;
	ztFontID font_id_uni;
	ztFontID font_id_uni2;
	ztFontID font_id_bmp;

	ztDrawList draw_list;

	ztGuiManagerID gui_manager;
	ztTextureID gui_tex;
	bool button_live_value;
	r32 slider_live_value;
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

	settings->native_w = settings->screen_w = zt_iniFileGetValue(ini_file, "general", "resolution_w", (i32)1920);
	settings->native_h = settings->screen_h = zt_iniFileGetValue(ini_file, "general", "resolution_h", (i32)1080);
	settings->renderer = ztRenderer_OpenGL;
	//settings->renderer = ztRenderer_DirectX;

	char cfg_renderer[128] = { 0 };
	zt_iniFileGetValue(ini_file, "general", "renderer", nullptr, cfg_renderer, sizeof(cfg_renderer));
	if(zt_striCmp(cfg_renderer, "opengl") == 0) settings->renderer = ztRenderer_OpenGL;
	if(zt_striCmp(cfg_renderer, "directx") == 0) settings->renderer = ztRenderer_DirectX;

	//settings->renderer_flags |= ztRendererFlags_Vsync;
	settings->renderer_flags = ztRendererFlags_Windowed;

	settings->renderer_screen_change_behavior = ztRendererScreenChangeBehavior_ScaleToVert;

	zt_inputMouseLook(true);
	zt_inputMouseSetCursor(ztInputMouseCursor_None);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool game_init(ztGameDetails* game_details, ztGameSettings* game_settings)
{
	g_game = zt_mallocStruct(ztGame);
	*g_game = {};
	g_game->details = game_details;
	g_game->settings = game_settings;

	g_game->asset_arena = zt_memMakeArena(zt_megabytes(32), zt_memGetGlobalArena());
	zt_strMakePrintf(data_path, ztFileMaxPath, "%s%crun%cdata", game_details->user_path, ztFilePathSeparator, ztFilePathSeparator);

	if (!zt_assetManagerLoadDirectory(&g_game->asset_mgr, data_path, g_game->asset_arena)) {
		zt_logCritical("Unable to load game assets");
		return false;
	}

	g_game->shader_id = zt_rendererMakeShader(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "shaders/shader_simple.zts"));
	if (g_game->shader_id == ztInvalidID) {
		zt_logCritical("Unable to load game shader");
		return false;
	}

	if (!zt_drawListMake(&g_game->draw_list, 1024)) {
		zt_logCritical("Unable to initialize draw list");
		return false;
	}

	g_game->tex_id_crate = zt_rendererMakeTexture(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/floor_tile.png"));
	if (g_game->tex_id_crate == ztInvalidID) {
		return false;
	}

	//g_game->font_id = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\arial.ttf", 20);
	g_game->font_id = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\courbd.ttf", 20);
	if (g_game->font_id == ztInvalidID) {
		return false;
	}

	g_game->font_id_uni = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\DengXian.ttf", 60, "ゼロ容認 零容忍");
	g_game->font_id_uni2 = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\arialbd.ttf", 60, "عدم التسامح");
	g_game->font_id_bmp = zt_fontMakeFromBmpFontAsset(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "fonts/bmp_font.fnt"));

	g_game->gui_manager = zt_guiManagerMake(&g_game->gui_camera, nullptr, zt_memGetGlobalArena());


	g_game->gui_tex = zt_rendererMakeTexture(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/gui.png"));
	if (g_game->gui_tex == ztInvalidID) {
		return false;
	}

	zt_fiz(2){
		ztGuiItemID window = zt_guiMakeWindow("Test Window");
		zt_guiItemSetSize(window, ztVec2(10, 7));
		zt_guiItemSetPosition(window, ztVec2(5.f + i, 0.f + i));

		zt_strMakePrintf(text, 128, "This is window %d", i + 1);
		ztGuiItemID text_id = zt_guiMakeText(window, text);
		zt_guiItemSetPosition(text_id, ztVec2(-2, 2));

		ztGuiItemID button_id = zt_guiMakeButton(window, "Button", 0, &g_game->button_live_value);
		zt_guiItemSetPosition(button_id, ztVec2(-2, -2));

		ztGuiItemID tbutton_id = zt_guiMakeToggleButton(window, "Toggle Button", 0);
		zt_guiItemSetPosition(tbutton_id, ztVec2(1, -2));

		zt_guiItemSetPosition(zt_guiMakeCheckbox(window, "Checkbox", 0), ztVec2(0, 0));
		zt_guiItemSetPosition(zt_guiMakeCheckbox(window, "Checkbox", ztGuiCheckboxFlags_RightText), ztVec2(0, .55f));
		zt_guiItemSetPosition(zt_guiMakeRadioButton(window, "Radio", 0), ztVec2(2, 0));
		zt_guiItemSetPosition(zt_guiMakeRadioButton(window, "Radio", ztGuiRadioButtonFlags_RightText), ztVec2(2, .55f));

		g_game->slider_live_value = 0;
		ztGuiItemID slider_id = zt_guiMakeSlider(window, ztGuiItemOrient_Horz, &g_game->slider_live_value);
		zt_guiItemSetPosition(slider_id, ztVec2(0, -.55f));
		zt_guiItemSetSize(slider_id, ztVec2(10, -1));

		struct local
		{
			static void on_pressed(ztGuiItemID item_id)
			{
				zt_logDebug("button pressed: %d", item_id);
			}
		};
		zt_guiButtonSetCallback(button_id, local::on_pressed);
		zt_guiButtonSetCallback(tbutton_id, local::on_pressed);

	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void game_screenChange(ztGameSettings *game_settings)
{
	//zt_logDebug("Game screen changed (%d x %d).  Updated cameras", game_settings->screen_w, game_settings->screen_h);
	
	zt_cameraMakePersp(&g_game->camera, game_settings->screen_w, game_settings->screen_h, zt_degreesToRadians(60), 0.1f, 200.f);
	zt_cameraMakeOrtho(&g_game->gui_camera, game_settings->screen_w, game_settings->screen_h, game_settings->native_w, game_settings->native_h, 0.1f, 100.f);

	g_game->camera.position = ztVec3(0, 0, 1);
	g_game->camera.rotation = ztVec3(270, 0, 0);
	zt_cameraRecalcMatrices(&g_game->camera);

	g_game->gui_camera.position = ztVec3(0, 0, 0);
	zt_cameraRecalcMatrices(&g_game->gui_camera);
}

// ------------------------------------------------------------------------------------------------
void game_cleanup()
{
	zt_guiManagerFree(g_game->gui_manager);

	zt_fontFree(g_game->font_id_bmp);
	zt_fontFree(g_game->font_id_uni2);
	zt_fontFree(g_game->font_id_uni);
	zt_fontFree(g_game->font_id);
	zt_rendererFreeTexture(g_game->tex_id_crate);
	zt_drawListFree(&g_game->draw_list);
	zt_rendererFreeShader(g_game->shader_id);

	zt_assetManagerFree(&g_game->asset_mgr);
	zt_memDumpArena(g_game->asset_arena, "asset memory");
	zt_memFreeArena(g_game->asset_arena);
	zt_free(g_game);
}

// ------------------------------------------------------------------------------------------------

bool game_loop(r32 dt)
{
	ztInputKeys *input = zt_inputKeysAccessState();
	ztInputMouse *mouse = zt_inputMouseAccessState();

	ztInputKeys_Enum input_keystrokes[16];
	zt_inputGetKeyStrokes(input_keystrokes);

	if (input[ztInputKeys_Space].justPressed()) {
		zt_inputMouseLook(!zt_inputMouseIsLook()); // toggle mouse look and cursor
		if (zt_inputMouseIsLook()) {
			zt_inputMouseSetCursor(ztInputMouseCursor_None);
		}
		else {
			zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
		}
	}
	else if (zt_inputMouseIsLook()) {
		zt_cameraControlUpdateWASD(&g_game->camera, mouse, input, dt);
	}
	else {
		if (!zt_guiManagerHandleInput(g_game->gui_manager, dt, input, input_keystrokes, mouse)) {
		}
	}

	static bool button_value = false;
	if (button_value != g_game->button_live_value) {
		button_value = g_game->button_live_value;
		zt_logDebug("button_live_value changed");
	}

	{
		{
			zt_drawListPushShader(&g_game->draw_list, g_game->shader_id);
			zt_drawListPushTexture(&g_game->draw_list, g_game->tex_id_crate);
			{
				static ztVec3 pos[3] = { ztVec3(.0f, .5f, 0), ztVec3(-.5f, -.5f, 0), ztVec3(.5f, -.5f, 0) };
				static ztVec2 uvs[3] = { ztVec2(0, 0), ztVec2(1, 1), ztVec2(.5f, 0) };
				static ztVec3 nml[3] = { ztVec3::zero, ztVec3::zero, ztVec3::zero };

				zt_drawListAddFilledTriangle(&g_game->draw_list, pos, uvs, nml);
			}

			{
				static ztVec3 pos[4] = { ztVec3(-2, 1, -2), ztVec3(-2, -1, -2), ztVec3(0, -1, -1), ztVec3(0, 1, -1) };
				static ztVec2 uvs[4] = { ztVec2(0, 0), ztVec2(0, 1), ztVec2(1, 1), ztVec2(1, 0) };
				static ztVec3 nml[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };

				zt_drawListAddFilledQuad(&g_game->draw_list, pos, uvs, nml);
			}
			zt_drawListPopTexture(&g_game->draw_list);
			zt_drawListPopShader(&g_game->draw_list);
		}

		zt_renderDrawList(&g_game->camera, &g_game->draw_list, ztColor(0, .15f, .15f, .5f), 0);


		// display frame time
		{
			zt_drawListPushShader(&g_game->draw_list, g_game->shader_id);
			zt_strMakePrintf(fps, 128, "%.4f us/f \n(%.0f fps) \ncamera: %.2f, %.2f, %.2f \n%.2f, %.2f, %.2f \n%.2f, %.2f, %.2f \nmouse: %d, %d ", dt * 1000.f, 1.f / dt, 
				g_game->camera.position.x, g_game->camera.position.y, g_game->camera.position.z,
				g_game->camera.rotation.x, g_game->camera.rotation.y, g_game->camera.rotation.z,
				g_game->camera.direction.x, g_game->camera.direction.y, g_game->camera.direction.z,
				mouse->screen_x, mouse->screen_y);

			ztVec2 pos = zt_cameraOrthoGetMaxExtent(&g_game->gui_camera);
			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id, fps, pos, ztAlign_Right, ztAnchor_Right|ztAnchor_Top);

			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id, "This is a test string.", ztVec2(-pos.x, pos.y), ztAlign_Left, ztAnchor_Left | ztAnchor_Top);
			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id_uni, "ゼロ容認 零容忍", ztVec2(-pos.x, -pos.y), ztAlign_Left, ztAnchor_Left | ztAnchor_Bottom);
			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id_uni2, "عدم التسامح", ztVec2(pos.x, -pos.y), ztAlign_Right, ztAnchor_Right | ztAnchor_Bottom);
			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id_bmp, "Bitmap Fonts Work Too! :-)", ztVec2(0, pos.y), ztAlign_Center, ztAnchor_Top);
			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id_bmp, "Bitmap Fonts Work Too! :-)", ztVec2(0, -pos.y), ztAlign_Center, ztAnchor_Bottom);


			zt_drawListPopShader(&g_game->draw_list);
		}

		zt_renderDrawList(&g_game->gui_camera, &g_game->draw_list, ztColor::zero, ztRenderDrawListFlags_NoClear | ztRenderDrawListFlags_NoDepthTest);

		zt_drawListPushShader(&g_game->draw_list, g_game->shader_id);
		zt_guiManagerRender(g_game->gui_manager, &g_game->draw_list);
		zt_drawListPopShader(&g_game->draw_list);

		zt_renderDrawList(&g_game->gui_camera, &g_game->draw_list, ztColor::zero, ztRenderDrawListFlags_NoClear | ztRenderDrawListFlags_NoDepthTest);
	}

	// test changing renderers
	{
		if (input[ztInputKeys_R].justPressed() && input[ztInputKeys_Control].pressed()) {
			zt_rendererRequestChange(g_game->settings->renderer == ztRenderer_OpenGL ? ztRenderer_DirectX : ztRenderer_OpenGL);
		}
	}

	// test changing windows mode
	{
		static bool fullscreen = false;

		if (input[ztInputKeys_F].justPressed() && input[ztInputKeys_Control].pressed()) {
			if(!fullscreen) {
				zt_rendererRequestFullscreen();
			}
			else {
				zt_rendererRequestWindowed();
			}
			fullscreen = !fullscreen;
		}
	}


	zt_assetManagerCheckForChanges(&g_game->asset_mgr);
	return !input[ztInputKeys_Escape].justPressed();
}

// ------------------------------------------------------------------------------------------------
