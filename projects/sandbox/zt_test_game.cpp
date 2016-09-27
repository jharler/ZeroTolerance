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
#define ZT_GAME_GUI_IMPLEMENTATION

//#define ZT_NO_DIRECTX
//#define ZT_MEM_ARENA_LOG_DETAILS
#define ZT_OPENGL_DIAGNOSE
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
#include "zt_game_gui.h"


// types/enums/defines ============================================================================

// structs/classes ================================================================================

struct ztGame
{
	ztGameDetails *details;
	ztGameSettings *settings;

	ztMemoryArena* asset_arena;
	ztAssetManager asset_mgr;

	ztCamera camera, gui_camera;

	ztShaderID shader_id, shader_id_lit;
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

	ztMeshID box, plane, rock, cube;

	ztTextureID render_tex, cube_map;

	ztScene *scene;
	ztModel *model_boxes[12];
	ztModel *model_plane;
	ztModel *model_light;
	ztLight directional_light;
};


// variables ======================================================================================

ztGame *g_game = nullptr;
ztFile g_log;

// private functions ==============================================================================

// ------------------------------------------------------------------------------------------------

void zt_logCallback(ztLogMessageLevel_Enum level, const char * message)
{
	zt_fileWrite(&g_log, message, zt_strSize(message) - 1);
	zt_fileWrite(&g_log, "\n", 1);
}

// functions ======================================================================================

bool game_settings(ztGameDetails* details, ztGameSettings* settings)
{
	zt_fileOpen(&g_log, "log.txt", ztFileOpenMethod_WriteOver);
	zt_logAddCallback(zt_logCallback, ztLogMessageLevel_Verbose);

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

	g_game->shader_id = zt_shaderMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "shaders/shader_simple.zts"));
	if (g_game->shader_id == ztInvalidID) {
		zt_logCritical("Unable to load game shader");
		return false;
	}

	g_game->shader_id_lit = zt_shaderMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "shaders/shader_lit.zts"));
	if (g_game->shader_id_lit == ztInvalidID) {
		zt_logCritical("Unable to load game shader");
		return false;
	}

	if (!zt_drawListMake(&g_game->draw_list, 1024 * 128)) {
		zt_logCritical("Unable to initialize draw list");
		return false;
	}

	g_game->tex_id_crate = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/floor_tile.png"));
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

	zt_guiInitDebug(g_game->gui_manager);

	g_game->gui_tex = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/gui.png"));
	if (g_game->gui_tex == ztInvalidID) {
		return false;
	}

	
	ztMaterialList materials = zt_materialListMake(g_game->tex_id_crate);
	g_game->box = zt_meshMakePrimativeBox(&materials, 1, 1, 1, ztMeshFlags_OwnsMaterials);
	g_game->plane = zt_meshMakePrimativePlane(&materials, 10, 10, 10, 10);
	//g_game->rock = zt_meshLoadOBJ(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/rock.obj"), nullptr);
	g_game->cube = zt_meshLoadOBJ(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/cube.obj"), nullptr);

	g_game->render_tex = zt_textureMakeRenderTarget(1024, 1024);

	g_game->cube_map = zt_textureMakeCubeMap(&g_game->asset_mgr, "textures/skybox_%s.png");

	if(false){
		ztGuiItemID window = zt_guiMakeScrollWindow("Test Window", ztGuiItemOrient_Vert);
		zt_guiItemSetSize(window, ztVec2(5, 7));
		zt_guiItemSetPosition(window, ztVec2(7.f, 0.f));

		ztGuiItemID sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiItemSetName(sizer, "SizeParentSizer");

		zt_fkz(4) {
			{
				ztGuiItemID header = zt_guiMakeCollapsingPanel(sizer, "Collapsing Panel");
				zt_guiSizerAddItem(sizer, header, 0, 3 / zt_pixelsPerUnit());

				{
					ztGuiItemID panel = zt_guiCollapsingPanelGetContentParent(header);
					ztGuiItemID sizer2 = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
					zt_guiSizerSizeToParent(sizer2);

					ztGuiItemID stattext = zt_guiMakeStaticText(sizer2, "Some text.");
					zt_guiSizerAddItem(sizer2, stattext, 0, 3 / zt_pixelsPerUnit());

					zt_guiSizerAddItem(sizer2, zt_guiMakeCheckbox(sizer2, "A Checkbox"), 0, 3 / zt_pixelsPerUnit());

					ztGuiItemID combo = zt_guiMakeComboBox(sizer2, 8);
					zt_guiSizerAddItem(sizer2, combo, 0, 3 / zt_pixelsPerUnit());

					const char *contents[] = {
						"Item 1",
						"Item 2",
						"Item 3",
						"Item 4",
					};
					zt_guiComboBoxSetContents(combo, contents, zt_elementsOf(contents), 1);
				}
			}
			{
				ztGuiItemID header = zt_guiMakeCollapsingPanel(sizer, "Collapsing Panel 2");
				zt_guiSizerAddItem(sizer, header, 0, 3 / zt_pixelsPerUnit());

				{
					ztGuiItemID panel = zt_guiCollapsingPanelGetContentParent(header);
					ztGuiItemID sizer2 = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
					zt_guiSizerSizeToParent(sizer2);

					ztGuiItemID stattext = zt_guiMakeStaticText(sizer2, "Some more text.");
					zt_guiSizerAddItem(sizer2, stattext, 0, 3 / zt_pixelsPerUnit());

					zt_guiSizerAddItem(sizer2, zt_guiMakeStaticText(sizer2, "A much longer line of text with\na new line in the middle of it."), 0, 3 / zt_pixelsPerUnit());

				}
			}
		}
		zt_guiSizerAddStretcher(sizer, 1);

		//zt_debugLogGuiHierarchy(window);
	}
	if (false){
		ztGuiItemID window = zt_guiMakeWindow("Tree Test");
		zt_guiItemSetSize(window, ztVec2(5, 7));
		zt_guiItemSetPosition(window, ztVec2(-7, 0));

		ztGuiItemID content = zt_guiWindowGetContentParent(window);
		ztGuiItemID sizer = zt_guiMakeSizer(content, ztGuiItemOrient_Vert);
		zt_guiSizerSizeToParent(sizer);

		ztGuiItemID tree = zt_guiMakeTree(sizer, 256);
		zt_guiSizerAddItem(sizer, tree, 1, 3 / zt_pixelsPerUnit());

		ztGuiTreeNodeID root = zt_guiTreeAppend(tree, "Root", nullptr);
		zt_guiTreeAppend(tree, "Subitem 1", nullptr, root);
		zt_guiTreeAppend(tree, "Subitem 2", nullptr, root);
		ztGuiTreeNodeID subitem = zt_guiTreeAppend(tree, "Subitem 3", nullptr, root);
		zt_guiTreeAppend(tree, "Sub-Subitem 1", nullptr, subitem);
		zt_guiTreeAppend(tree, "Sub-Subitem 2x", nullptr, subitem);
		zt_guiTreeAppend(tree, "Subitem 4", nullptr, root);

		ztGuiTreeNodeID subitem2 = zt_guiTreeAppend(tree, zt_guiMakeButton(tree, "Button"), nullptr, root);
		zt_guiTreeAppend(tree, "Button Subitem", nullptr, subitem2);
		zt_guiTreeAppend(tree, "Subitem 5", nullptr, root);
	}

	{
		zt_strMakePrintf(gui_tex, ztFileMaxPath, "%s\\run\\data\\textures\\gui.png", game_details->user_path);
		zt_strMakePrintf(gui_cpp, ztFileMaxPath, "%s\\run\\data\\textures\\gui.png.cpp", game_details->user_path);
		if (!zt_fileExists(gui_cpp) && zt_fileExists(gui_tex)) {
			i32 size = 0;
			byte *data = (byte*)zt_readEntireFile(gui_tex, &size);

			ztFile file;
			if (zt_fileOpen(&file, gui_cpp, ztFileOpenMethod_WriteOver)) {
				char *func_header =
					"byte *zt_loadGuiPng(i32 *size) {\n"
					"	byte data[] = {\n\t\t";
				char *func_footer =
					"};\n"
					"	*size = zt_sizeof(data);\n"
					"	byte *result = zt_mallocStructArray(byte, *size);\n"
					"	zt_memCpy(result, *size, data, *size);\n"
					"	return result;\n"
					"}";

				zt_fileWrite(&file, func_header, zt_strSize(func_header) - 1);

				char buff[32];
				zt_fiz(size) {
					if (i == 0) {
						zt_strPrintf(buff, zt_sizeof(buff), "0x%02x", data[i]);
					}
					else if (i % 1000 == 0){
						zt_strPrintf(buff, zt_sizeof(buff), ",\n\t\t0x%02x", data[i]);
					}
					else {
						zt_strPrintf(buff, zt_sizeof(buff), ",0x%02x", data[i]);
					}

					zt_fileWrite(&file, buff, zt_strSize(buff) - 1);
				}

				zt_fileWrite(&file, func_footer, zt_strSize(func_footer) - 1);
				zt_fileClose(&file);
			}

			zt_free(data);
		}
	}

	g_game->scene = zt_sceneMake(zt_memGetGlobalArena());

	zt_fiz(zt_elementsOf(g_game->model_boxes)) {
		g_game->model_boxes[i] = zt_modelMake(zt_memGetGlobalArena(), g_game->cube, zt_shaderGetDefault(ztShaderDefault_LitShadow), nullptr, ztModelFlags_CastsShadows);

		r32 angle = (ztMathPi2 / zt_elementsOf(g_game->model_boxes)) * i;
		g_game->model_boxes[i]->transform.position.x = zt_cos(angle) * 3.5f;
		g_game->model_boxes[i]->transform.position.z = zt_sin(angle) * 3.5f;
		g_game->model_boxes[i]->transform.position.y = .5f + ((r32)i * .75f);

		zt_sceneAddModel(g_game->scene, g_game->model_boxes[i]);
	}

	g_game->model_plane = zt_modelMake(zt_memGetGlobalArena(), g_game->plane, zt_shaderGetDefault(ztShaderDefault_LitShadow), nullptr, 0);
	zt_sceneAddModel(g_game->scene, g_game->model_plane);

	g_game->model_light = zt_modelMake(zt_memGetGlobalArena(), g_game->cube, zt_shaderGetDefault(ztShaderDefault_Unlit), nullptr, 0);
	zt_sceneAddModel(g_game->scene, g_game->model_light);

	g_game->model_light->transform.position = ztVec3(0, 0, 0);
	g_game->model_light->transform.scale = ztVec3(.5f, .5f, .5f);

	g_game->directional_light = zt_lightMakeDirectional(g_game->model_light->transform.position, ztVec3::zero);
	g_game->directional_light.position = ztVec3(-5, 10, -2.5f);
	zt_sceneAddLight(g_game->scene, &g_game->directional_light);

	return true;
}

// ------------------------------------------------------------------------------------------------

void game_screenChange(ztGameSettings *game_settings)
{
	//zt_logDebug("Game screen changed (%d x %d).  Updated cameras", game_settings->screen_w, game_settings->screen_h);


	if (g_game->details->current_frame == 1) {
		zt_cameraMakePersp(&g_game->camera, game_settings->screen_w, game_settings->screen_h, zt_degreesToRadians(60), 0.1f, 200.f, ztVec3(9, 10, 8), ztVec3(230, -30, 0));
		zt_cameraMakeOrtho(&g_game->gui_camera, game_settings->screen_w, game_settings->screen_h, game_settings->native_w, game_settings->native_h, 0.1f, 100.f, ztVec3(0, 0, 0));
	}
	else {
		zt_cameraMakePersp(&g_game->camera, game_settings->screen_w, game_settings->screen_h, zt_degreesToRadians(60), 0.1f, 200.f, g_game->camera.position, g_game->camera.rotation);
		zt_cameraMakeOrtho(&g_game->gui_camera, game_settings->screen_w, game_settings->screen_h, game_settings->native_w, game_settings->native_h, 0.1f, 100.f, g_game->gui_camera.position);
	}

	zt_cameraRecalcMatrices(&g_game->camera);
	zt_cameraRecalcMatrices(&g_game->gui_camera);
}

// ------------------------------------------------------------------------------------------------
void game_cleanup()
{
	zt_fiz(zt_elementsOf(g_game->model_boxes)) {
		zt_modelFree(g_game->model_boxes[i]);
	}

	zt_sceneFree(g_game->scene);

	zt_guiManagerFree(g_game->gui_manager);

	zt_textureFree(g_game->render_tex);

	zt_meshFree(g_game->cube);
	zt_meshFree(g_game->rock);
	zt_meshFree(g_game->box);
	zt_meshFree(g_game->plane);

	zt_fontFree(g_game->font_id_bmp);
	zt_fontFree(g_game->font_id_uni2);
	zt_fontFree(g_game->font_id_uni);
	zt_fontFree(g_game->font_id);
	zt_textureFree(g_game->tex_id_crate);
	zt_drawListFree(&g_game->draw_list);
	zt_shaderFree(g_game->shader_id);
	zt_shaderFree(g_game->shader_id_lit);

	zt_assetManagerFree(&g_game->asset_mgr);
	zt_memDumpArena(g_game->asset_arena, "asset memory");
	zt_memFreeArena(g_game->asset_arena);
	zt_free(g_game);

	zt_logRemoveCallback(zt_logCallback);
	zt_fileClose(&g_log);
}

// ------------------------------------------------------------------------------------------------

bool game_loop(r32 dt)
{
	ztInputKeys *input = zt_inputKeysAccessState();
	ztInputMouse *mouse = zt_inputMouseAccessState();

	ztInputKeys_Enum input_keystrokes[16];
	zt_inputGetKeyStrokes(input_keystrokes);

	zt_guiManagerUpdate(g_game->gui_manager, dt);

	bool gui_input = false;
	if (zt_inputMouseIsLook()) {
		zt_cameraControlUpdateWASD(&g_game->camera, mouse, input, dt);
	}
	else {
		if (zt_guiManagerHandleInput(g_game->gui_manager, input, input_keystrokes, mouse)) {
			gui_input = true;
		}
	}
	if (input[ztInputKeys_Space].justPressed() && !zt_guiManagerHasKeyboardFocus(g_game->gui_manager)) {
		zt_inputMouseLook(!zt_inputMouseIsLook()); // toggle mouse look and cursor
		if (zt_inputMouseIsLook()) {
			zt_inputMouseSetCursor(ztInputMouseCursor_None);
		}
		else {
			zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
		}
	}
	bool console_shown = false;
	if (input[ztInputKeys_Tilda].justPressed()) {
		zt_debugConsoleToggle(&console_shown);

		if (console_shown) {
			if (zt_inputMouseIsLook()) {
				zt_inputMouseLook(false);
				zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
			}
			zt_guiManagerSetKeyboardFocus(g_game->gui_manager);
		}
	}

	{
		static bool moving = true;
		if (input[ztInputKeys_P].justPressed()) {
			moving = !moving;
		}

		if (moving) {
			const r32 slice = (ztMathPi2 / 5);
			static r32 angle = 0;

			angle += slice * dt;

			g_game->model_light->transform.position.x = zt_cos(angle) * 5.5f;
			g_game->model_light->transform.position.z = zt_sin(angle) * 5.5f;
			g_game->model_light->transform.position.y = 10;
			g_game->directional_light.position = g_game->model_light->transform.position;

			zt_shaderSetVariableVec3(g_game->shader_id_lit, "light_pos", g_game->model_light->transform.position);
		}
	}

	zt_sceneCull(g_game->scene, &g_game->camera);
	//g_game->directional_light.position = g_game->camera.position;
	zt_sceneLighting(g_game->scene);
	zt_sceneRender(g_game->scene, &g_game->camera, ztColor(0,0,0,1));

	{
#if 0
		{
			static r32 osc = 0;
			osc += dt * 2.f;
			r32 off = 3 + zt_sin(osc);

			zt_drawListPushColor(&g_game->draw_list, ztVec4(0, 1, 1, 1));
			zt_drawListAddEmptyQuad(&g_game->draw_list, ztVec3(-1 * off, 1 * off, 0), ztVec3(-1 * off, -1 * off, 0), ztVec3(1 * off, -1 * off, 0), ztVec3(1 * off, 1 * off, 0));

			zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 1, 1, 1));
			zt_drawListPushShader(&g_game->draw_list, g_game->shader_id);
			zt_drawListAddText2D(&g_game->draw_list, g_game->font_id_bmp, "This is the\nZeroTolerance\nGame Library", ztVec2(0, 0), ztAlign_Center);
	
			zt_drawListPopShader(&g_game->draw_list);

			zt_renderDrawList(&g_game->gui_camera, &g_game->draw_list, ztColor(.2f, 0, 0, 1), ztRenderDrawListFlags_NoDepthTest, g_game->render_tex);
		}
		{
			zt_drawListPushColor(&g_game->draw_list, ztVec4(.5f, .5f, .5f, 1));
			zt_drawListAddSkybox(&g_game->draw_list, g_game->cube_map);
			zt_drawListAddFloorGrid(&g_game->draw_list, ztVec3(0, -0.0001f, 0), 30, 30);

			zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 0, 1, 1));
			zt_drawListPushShader(&g_game->draw_list, g_game->shader_id);
			zt_drawListPushTexture(&g_game->draw_list, g_game->tex_id_crate);
			{
				static ztVec3 pos[3] = { ztVec3(.0f, 1.5f, -.5f), ztVec3(-.5f, .5f, -.5f), ztVec3(.5f, .5f, -.5f) };
				static ztVec2 uvs[3] = { ztVec2(0, 0), ztVec2(1, 1), ztVec2(.5f, 0) };
				static ztVec3 nml[3] = { ztVec3::zero, ztVec3::zero, ztVec3::zero };

				zt_drawListAddFilledTriangle(&g_game->draw_list, pos, uvs, nml);
			}
			//zt_drawListPopTexture(&g_game->draw_list);

			zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 1, 1, 1));
			zt_drawListPushTexture(&g_game->draw_list, g_game->render_tex);
			{
				// top left, bottom left, bottom right, top right
				static ztVec3 pos[4] = { ztVec3(-11, 22, -22), ztVec3(-11, 0, -22), ztVec3(11, 0, -22), ztVec3(11, 22, -22) };
				static ztVec2 uvs[4] = { ztVec2(0, 0), ztVec2(0, 1), ztVec2(1, 1), ztVec2(1, 0) };
				static ztVec3 nml[4] = { ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero };

				zt_drawListAddFilledQuad(&g_game->draw_list, pos, uvs, nml);
			}
			zt_drawListAddBillboard(&g_game->draw_list, ztVec3(-2, 2, -2), ztVec2(.5f, .5f), ztVec2::zero, ztVec2::one);
			zt_drawListAddBillboard(&g_game->draw_list, ztVec3(2, 3, -3), ztVec2(.5f, .5f), ztVec2::zero, ztVec2::one);
			zt_drawListAddBillboard(&g_game->draw_list, ztVec3(-1, 5, -1), ztVec2(.5f, .5f), ztVec2::zero, ztVec2::one);
			zt_drawListPopTexture(&g_game->draw_list);

			zt_drawListPopTexture(&g_game->draw_list);

			zt_drawListAddMesh(&g_game->draw_list, g_game->box, ztVec3(2, .5f, 0), ztVec3(0, 0, 0), ztVec3(1, 1, 1));
			zt_drawListAddMesh(&g_game->draw_list, g_game->box, ztVec3(-3, .5f, 0), ztVec3(0, 45, 0), ztVec3(1, 1, 1));
			zt_drawListAddMesh(&g_game->draw_list, g_game->plane, ztVec3(0, -.01f, 0), ztVec3::zero, ztVec3::one);
			//zt_drawListAddMesh(&g_game->draw_list, g_game->rock, ztVec3(2, 0, -2), ztVec3::zero, ztVec3::one);
			zt_drawListAddMesh(&g_game->draw_list, g_game->cube, ztVec3(-2, .5f, -2), ztVec3::zero, ztVec3::one);

			zt_drawListPopShader(&g_game->draw_list);

			zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 0, 0, 1));
			zt_drawListAddLine(&g_game->draw_list, ztVec3(0, 0, 0), ztVec3(.5f, 0, 0));
			zt_drawListPushColor(&g_game->draw_list, ztVec4(0, 1, 0, 1));
			zt_drawListAddLine(&g_game->draw_list, ztVec3(0, 0, 0), ztVec3(0, .5f, 0));
			zt_drawListPushColor(&g_game->draw_list, ztVec4(0, 0, 1, 1));
			zt_drawListAddLine(&g_game->draw_list, ztVec3(0, 0, 0), ztVec3(0, 0, .5f));
			zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 1, 1, 1));
		}

		zt_renderDrawList(&g_game->camera, &g_game->draw_list, ztColor(0,0,0,1), 0);

#endif

#if 1
		zt_drawListPushShader(&g_game->draw_list, g_game->shader_id);
		zt_guiManagerRender(g_game->gui_manager, &g_game->draw_list);
		zt_drawListPopShader(&g_game->draw_list);

		if (zt_inputMouseIsLook()){
			zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 0, 0, 1));
			zt_drawListAddLine(&g_game->draw_list, ztVec3(-.5f, 0, 0), ztVec3(.5f, 0, 0));

			zt_drawListPushColor(&g_game->draw_list, ztVec4(0, 1, 0, 1));
			zt_drawListAddLine(&g_game->draw_list, ztVec3(0, -.5f, 0), ztVec3(0, .5f, 0));

			//zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 1, 1, 1));
			//zt_drawListAddPoint(&g_game->draw_list, ztVec3(2, 2, 2));
			//zt_drawListAddPoint(&g_game->draw_list, ztVec3(3, 3, 3));
			//zt_drawListPushColor(&g_game->draw_list, ztVec4(1, 0, 0, 1));
			//zt_drawListAddPoint(&g_game->draw_list, ztVec3(4, 4, 4));

			//zt_renderDrawList(&g_game->camera, &g_game->draw_list, ztColor(0, 0, 0, 1), 0);
		}
		
		zt_renderDrawList(&g_game->gui_camera, &g_game->draw_list, ztColor::zero, ztRenderDrawListFlags_NoClear | ztRenderDrawListFlags_NoDepthTest);
#endif
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

	if (input[ztInputKeys_M].justPressed()) {
		ztVec2 mpos = zt_cameraOrthoScreenToWorld(&g_game->gui_camera, mouse->screen_x, mouse->screen_y);
		zt_logDebug("mouse pos: %d, %d (%.4f, %.4f)", mouse->screen_x, mouse->screen_y, mpos.x, mpos.y);
	}

	//zt_memArenaValidate(zt_memGetGlobalArena());
	zt_assetManagerCheckForChanges(&g_game->asset_mgr);
	return !input[ztInputKeys_Escape].justPressed();
}

// ------------------------------------------------------------------------------------------------
