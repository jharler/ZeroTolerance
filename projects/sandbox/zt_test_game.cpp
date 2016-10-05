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
//#define ZT_SHADER_LOG_INVALID_ACCESS

//#define ZT_NO_DIRECTX
//#define ZT_MEM_ARENA_LOG_DETAILS
//#define ZT_OPENGL_DEBUGGING
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

	ztCamera camera, gui_camera, camera_test;

	ztTextureID tex_test;

	ztShaderID shader_id, shader_id_lit;
	ztTextureID tex_id_floor, tex_id_floor_spec, tex_id_floor_norm, tex_id_crate, tex_id_crate_spec, tex_id_crate_norm, tex_skybox;

	ztDrawList draw_list;

	ztGuiManagerID gui_manager;

	ztMeshID plane, cube;

	ztScene *scene;
	ztModel *model_boxes[12];
	ztModel *model_plane;
	ztModel *model_light;
	ztLight directional_light;

	ztModel *model_point_lights[4];
	ztLight point_lights[4];

	ztMaterial material_boxes;
	ztMaterial material_plane;
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

// ------------------------------------------------------------------------------------------------

void makePngCpp(ztGameDetails* game_details)
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

// functions ======================================================================================

bool game_settings(ztGameDetails* details, ztGameSettings* settings)
{
	zt_fileOpen(&g_log, "log.txt", ztFileOpenMethod_WriteOver);
	zt_logAddCallback(zt_logCallback, ztLogMessageLevel_Verbose);

	zt_strMakePrintf(ini_file, ztFileMaxPath, "%s%csettings.cfg", details->user_path, ztFilePathSeparator);
	settings->memory = zt_iniFileGetValue(ini_file, "general", "app_memory", (i32)zt_megabytes(128));

	settings->native_w = settings->screen_w = zt_iniFileGetValue(ini_file, "general", "resolution_w", (i32)1920);
	settings->native_h = settings->screen_h = zt_iniFileGetValue(ini_file, "general", "resolution_h", (i32)1080);
	settings->renderer = ztRenderer_OpenGL;
	settings->renderer = ztRenderer_DirectX;

	char cfg_renderer[128] = { 0 };
	zt_iniFileGetValue(ini_file, "general", "renderer", nullptr, cfg_renderer, sizeof(cfg_renderer));
	if(zt_striCmp(cfg_renderer, "opengl") == 0) settings->renderer = ztRenderer_OpenGL;
	if(zt_striCmp(cfg_renderer, "directx") == 0) settings->renderer = ztRenderer_DirectX;

	settings->renderer_flags = 0;
	//settings->renderer_flags |= ztRendererFlags_Vsync;
	settings->renderer_flags |= ztRendererFlags_Windowed;

	settings->renderer_screen_change_behavior = ztRendererScreenChangeBehavior_ScaleToVert;

	zt_inputMouseLook(true);
	zt_inputMouseSetCursor(ztInputMouseCursor_None);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool game_init(ztGameDetails* game_details, ztGameSettings* game_settings)
{
	ztBlockProfiler bp_tex("game_init");

	g_game = zt_mallocStruct(ztGame);
	*g_game = {};
	g_game->details = game_details;
	g_game->settings = game_settings;

	g_game->asset_arena = zt_memMakeArena(zt_megabytes(64), zt_memGetGlobalArena());
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

	g_game->tex_id_crate = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/cube.png"), ztTextureFlags_Flip);
	if (g_game->tex_id_crate == ztInvalidID) return false;
	g_game->tex_id_crate_spec = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/cube_s.png"), ztTextureFlags_Flip);
	if (g_game->tex_id_crate_spec == ztInvalidID) return false;
	g_game->tex_id_crate_norm = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/cube_n.png"), ztTextureFlags_Flip);
	if (g_game->tex_id_crate_norm == ztInvalidID) return false;
	g_game->tex_id_floor = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/floor_tile.png"), ztTextureFlags_Flip);
	if (g_game->tex_id_floor == ztInvalidID) return false;
	g_game->tex_id_floor_spec = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/floor_tile_s.png"), ztTextureFlags_Flip|ztTextureFlags_MipMaps);
	if (g_game->tex_id_floor_spec == ztInvalidID) return false;
	g_game->tex_id_floor_norm = zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "textures/floor_tile_n.png"), ztTextureFlags_Flip | ztTextureFlags_MipMaps);
	if (g_game->tex_id_floor_norm == ztInvalidID) return false;
	g_game->tex_skybox = zt_textureMakeCubeMap(&g_game->asset_mgr, "textures/skybox_%s.png");
	if (g_game->tex_skybox == ztInvalidID) return false;

	g_game->gui_manager = zt_guiManagerMake(&g_game->gui_camera, nullptr, zt_memGetGlobalArena());
	zt_guiInitDebug(g_game->gui_manager);

	g_game->tex_test = zt_textureMakeRenderTarget(512, 512);


	ztMeshID mesh_chair = ztInvalidID;
	ztMaterial mat_chair = zt_materialMake();
	zt_meshLoadOBJ(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/chair/SA_LD_Medieval_X_Chair.obj"), &mesh_chair, &mat_chair, 1, ztVec3::one, ztVec3(2, 3, 0));

	ztMeshID mesh_droid[2];
	ztMaterial mat_droid[2];
	zt_meshLoadOBJ(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/droid/attack_droid.obj"), mesh_droid, mat_droid, 2, ztVec3(.2f, .2f, .2f), ztVec3(0, 0, 0));
	
	g_game->material_plane = zt_materialMake(g_game->tex_id_floor, ztVec4::one, 0, g_game->tex_id_floor_spec, ztVec4::one, 0, g_game->tex_id_floor_norm);
	g_game->material_plane.shininess = 0.25f;

	g_game->material_boxes = zt_materialMake(g_game->tex_id_crate, ztVec4::one, 0, g_game->tex_id_crate_spec, ztVec4::one, 0, g_game->tex_id_crate_norm);
	g_game->material_boxes.shininess = 1.f;

	g_game->plane = zt_meshMakePrimativePlane(200, 200, 50, 50);
//	g_game->cube = zt_meshLoadOBJ(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/cube.obj"), nullptr);
	g_game->cube = zt_meshMakePrimativeBox(1, 1, 1);

	g_game->scene = zt_sceneMake(zt_memGetGlobalArena());

	zt_sceneAddModel(g_game->scene, zt_modelMake(zt_memGetGlobalArena(), mesh_chair, &mat_chair, zt_shaderGetDefault(ztShaderDefault_LitShadow), nullptr, ztModelFlags_CastsShadows));

	ztShaderID droid_shader = zt_shaderGetDefault(ztShaderDefault_Lit);// g_game->shader_id_lit; // zt_shaderGetDefault(ztShaderDefault_Lit);// zt_shaderGetDefault(ztShaderDefault_Lit);
	ztModel* model_droid = zt_modelMake(zt_memGetGlobalArena(), mesh_droid[0], &mat_droid[0], droid_shader, nullptr, ztModelFlags_CastsShadows);
	zt_fiz(1) {
		zt_modelMake(zt_memGetGlobalArena(), mesh_droid[i + 1], &mat_droid[i + 1], droid_shader, nullptr, ztModelFlags_CastsShadows, model_droid);
	}
	zt_sceneAddModel(g_game->scene, model_droid);
	model_droid->transform.position.x = -4;
	model_droid->transform.position.z = -6;
	model_droid->transform.rotation.y = 45;


	zt_fiz(zt_elementsOf(g_game->model_boxes)) {
		if (i == 0) {
			g_game->model_boxes[i] = zt_modelMake(zt_memGetGlobalArena(), zt_meshMakePrimativeBox(1, 1, 1), &g_game->material_boxes, zt_shaderGetDefault(ztShaderDefault_LitShadow), nullptr, ztModelFlags_CastsShadows);
		}
		else {
			g_game->model_boxes[i] = zt_modelMake(zt_memGetGlobalArena(), g_game->cube, &g_game->material_boxes, zt_shaderGetDefault(ztShaderDefault_LitShadow), nullptr, ztModelFlags_CastsShadows);
		}

		r32 angle = (ztMathPi2 / zt_elementsOf(g_game->model_boxes)) * i;
		g_game->model_boxes[i]->transform.position.x = zt_cos(angle) * 3.5f;
		g_game->model_boxes[i]->transform.position.z = zt_sin(angle) * 3.5f;
		g_game->model_boxes[i]->transform.position.y = .5f + ((r32)i * .75f);

		zt_sceneAddModel(g_game->scene, g_game->model_boxes[i]);
	}

	ztModel *model_center = zt_modelMake(zt_memGetGlobalArena(), g_game->cube, nullptr, zt_shaderGetDefault(ztShaderDefault_Solid), nullptr, 0);
	model_center->transform.scale = ztVec3(.15f, .15f, .15f);
	zt_sceneAddModel(g_game->scene, model_center);

	/*
	ztMaterial mat = zt_materialMake(zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/spot_texture.png"), ztTextureFlags_Flip), ztVec4::one, ztMaterialFlags_OwnsTexture,
									 zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/spot_texture_s.png"), ztTextureFlags_Flip), ztVec4::one, ztMaterialFlags_OwnsTexture,
									 zt_textureMake(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/spot_texture_n.png"), ztTextureFlags_Flip), ztMaterialFlags_OwnsTexture);
	ztMeshID mesh = zt_meshLoadOBJ(&g_game->asset_mgr, zt_assetLoad(&g_game->asset_mgr, "models/spot_control_mesh.obj"), nullptr);
	ztModel *model = zt_modelMake(zt_memGetGlobalArena(), mesh, &mat, g_game->shader_id_lit, nullptr, ztModelFlags_CastsShadows);
	model->transform.position.y = 1;
	zt_sceneAddModel(g_game->scene, model);
	*/
	g_game->model_plane = zt_modelMake(zt_memGetGlobalArena(), g_game->plane, &g_game->material_plane, zt_shaderGetDefault(ztShaderDefault_LitShadow), nullptr, 0);
	//g_game->model_plane = zt_modelMake(zt_memGetGlobalArena(), g_game->plane, &g_game->material_plane, g_game->shader_id_lit, nullptr, 0);
	zt_sceneAddModel(g_game->scene, g_game->model_plane);

	g_game->model_light = zt_modelMake(zt_memGetGlobalArena(), g_game->cube, nullptr, zt_shaderGetDefault(ztShaderDefault_Solid), nullptr, 0);
	zt_sceneAddModel(g_game->scene, g_game->model_light);
	g_game->model_light->transform.position = ztVec3(0, 0, 0);
	g_game->model_light->transform.scale = ztVec3(.5f, .5f, .5f);

	ztMaterial point_light_mat = zt_materialMake(ztInvalidID, ztVec4(1, 1, 1, 1));
	ztVec3 positions[4] = { ztVec3(-6, 3, 0), ztVec3(0, 3, -6), ztVec3(6, 3, 0), ztVec3(0, 3, 6) };
	ztVec4 colors[4] = { ztVec4(1, 0, 0, 1), ztVec4(0, 1, 0, 1), ztVec4(0, 0, 1, 1), ztVec4(0, 1, 1, 1) };

	zt_fiz(4) {
		g_game->model_point_lights[i] = zt_modelMake(zt_memGetGlobalArena(), g_game->cube, &point_light_mat, zt_shaderGetDefault(ztShaderDefault_Solid), nullptr, 0);
		zt_sceneAddModel(g_game->scene, g_game->model_point_lights[i]);
		g_game->model_point_lights[i]->transform.position = positions[i];
		g_game->model_point_lights[i]->transform.scale = ztVec3(.25f, .25f, .25f);
		g_game->point_lights[i] = zt_lightMakeArea(g_game->model_point_lights[i]->transform.position, 1, true, colors[i]);
		zt_sceneAddLight(g_game->scene, &g_game->point_lights[i]);
	}

	g_game->directional_light = zt_lightMakeDirectional(g_game->model_light->transform.position, ztVec3::zero, 1, .05f);
	g_game->directional_light.position = ztVec3(-5, 10, -2.5f);
	zt_sceneAddLight(g_game->scene, &g_game->directional_light);

	{
		ztGuiItemID slider = zt_guiMakeSlider(ztInvalidID, ztGuiItemOrient_Horz, &g_game->directional_light.ambient);
		zt_guiItemSetSize(slider, ztVec2(3, .3f));
		zt_guiItemSetPosition(slider, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);

		slider = zt_guiMakeSlider(ztInvalidID, ztGuiItemOrient_Horz, &g_game->directional_light.intensity);
		zt_guiItemSetSize(slider, ztVec2(3, .3f));
		zt_guiItemSetPosition(slider, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(0, -.4f));

		slider = zt_guiMakeSlider(ztInvalidID, ztGuiItemOrient_Horz, &g_game->directional_light.color.r);
		zt_guiItemSetSize(slider, ztVec2(1, .3f));
		zt_guiItemSetPosition(slider, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(0, -.8f));

		slider = zt_guiMakeSlider(ztInvalidID, ztGuiItemOrient_Horz, &g_game->directional_light.color.g);
		zt_guiItemSetSize(slider, ztVec2(1, .3f));
		zt_guiItemSetPosition(slider, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(1, -.8f));

		slider = zt_guiMakeSlider(ztInvalidID, ztGuiItemOrient_Horz, &g_game->directional_light.color.b);
		zt_guiItemSetSize(slider, ztVec2(1, .3f));
		zt_guiItemSetPosition(slider, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(2, -.8f));

		zt_fiz(4) {
			slider = zt_guiMakeSlider(ztInvalidID, ztGuiItemOrient_Horz, &g_game->point_lights[i].intensity);
			zt_guiItemSetSize(slider, ztVec2(3, .3f));
			zt_guiItemSetPosition(slider, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(0, -1.2f - (i * .4f)));
		}
	}

	makePngCpp(game_details);
	return true;
}

// ------------------------------------------------------------------------------------------------

void game_screenChange(ztGameSettings *game_settings)
{
	//zt_logDebug("Game screen changed (%d x %d).  Updated cameras", game_settings->screen_w, game_settings->screen_h);

	if (g_game->details->current_frame == 1) {
		zt_cameraMakePersp(&g_game->camera, game_settings->screen_w, game_settings->screen_h, zt_degreesToRadians(60), 0.1f, 100.f, ztVec3(9, 10, 8), ztVec3(230, -30, 0));
		zt_cameraMakeOrtho(&g_game->gui_camera, game_settings->screen_w, game_settings->screen_h, game_settings->native_w, game_settings->native_h, 0.1f, 100.f, ztVec3(0, 0, 0));
	}
	else {
		zt_cameraMakePersp(&g_game->camera, game_settings->screen_w, game_settings->screen_h, zt_degreesToRadians(60), 0.1f, 100.f, g_game->camera.position, g_game->camera.rotation);
		zt_cameraMakeOrtho(&g_game->gui_camera, game_settings->screen_w, game_settings->screen_h, game_settings->native_w, game_settings->native_h, 0.1f, 100.f, g_game->gui_camera.position);
	}

	zt_cameraMakePersp(&g_game->camera_test, game_settings->screen_w, game_settings->screen_h, zt_degreesToRadians(30), 0.1f, 10.f, ztVec3(1, 1, 1), ztVec3(230, 0, 0));
	zt_cameraRecalcMatrices(&g_game->camera_test);

	zt_cameraRecalcMatrices(&g_game->camera);
	zt_cameraRecalcMatrices(&g_game->gui_camera);
}

// ------------------------------------------------------------------------------------------------
void game_cleanup()
{
	zt_sceneFreeAllModels(g_game->scene);
	zt_sceneFree(g_game->scene);

	zt_guiManagerFree(g_game->gui_manager);

	zt_meshFree(g_game->cube);
	zt_meshFree(g_game->plane);

	zt_textureFree(g_game->tex_id_crate);
	zt_textureFree(g_game->tex_id_floor);
	zt_textureFree(g_game->tex_skybox);

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

			g_game->model_light->transform.rotation.y += 360 * dt;
			if (g_game->model_light->transform.rotation.y > 360) {
				g_game->model_light->transform.rotation.y -= 360;
			}

			g_game->directional_light.position = g_game->model_light->transform.position;

			zt_shaderSetVariableVec3(g_game->shader_id_lit, "light_pos", g_game->model_light->transform.position);
		}

		if (moving) {
			const r32 slice = (ztMathPi2 / 5);
			static r32 angle = 0;

			angle += slice * dt;

			zt_fiz(2) {
				g_game->model_boxes[i]->transform.rotation.y += 90 * dt;
				if (g_game->model_boxes[i]->transform.rotation.y > 360) {
					g_game->model_boxes[i]->transform.rotation.y -= 360;
				}
			}
		}

//		if (input[ztInputKeys_Up].pressed()) {
//			if (input[ztInputKeys_Shift].pressed()) {
//				g_game->point_light.position.y += 1 * dt;
//			}
//			else {
//				g_game->point_light.position.z += 1 * dt;
//			}
//		}
//		if (input[ztInputKeys_Down].pressed()) {
//			if (input[ztInputKeys_Shift].pressed()) {
//				g_game->point_light.position.y -= 1 * dt;
//			}
//			else {
//				g_game->point_light.position.z -= 1 * dt;
//			}
//		}
//		if (input[ztInputKeys_Left].pressed()) {
//			g_game->point_light.position.x -= 1 * dt;
//		}
//		if (input[ztInputKeys_Right].pressed()) {
//			g_game->point_light.position.x += 1 * dt;
//		}
//		g_game->model_point_light->transform.position = g_game->point_light.position;
	}

	zt_rendererClear(ztVec4(0, 0, 0, 0));
	zt_sceneCull(g_game->scene, &g_game->camera);
	zt_sceneLighting(g_game->scene, &g_game->camera);
	zt_sceneRender(g_game->scene, &g_game->camera);

	{
		//zt_sceneCull(g_game->scene, &g_game->camera_test);
		//zt_sceneLighting(g_game->scene, &g_game->camera_test);

//		zt_textureRenderTargetPrepare(g_game->tex_test);
//
//		zt_rendererClear(ztVec4(0, 0, 0, 1));
//		zt_sceneRender(g_game->scene, &g_game->camera_test);
//
//		zt_textureRenderTargetCommit(g_game->tex_test);

		zt_drawListPushShader(&g_game->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		//zt_drawListPushTexture(&g_game->draw_list, g_game->tex_test);
		zt_drawListPushTexture(&g_game->draw_list, g_game->scene->tex_directional_shadow_map);
		zt_drawListAddFilledRect2D(&g_game->draw_list, ztVec3(11, -5.9375f, 0), ztVec2(14.22f / 2.f, 8 / 2.f), ztVec2(0,0), ztVec2(1,1));
		zt_drawListPopTexture(&g_game->draw_list);
		zt_drawListPopShader(&g_game->draw_list);
		zt_renderDrawList(&g_game->gui_camera, &g_game->draw_list, ztColor::zero, ztRenderDrawListFlags_NoClear);
	}

//	ztFrustum frustum = zt_cameraCalcViewFrustum(&g_game->camera_test);
//	zt_drawListAddFrustum(&g_game->draw_list, &frustum);
//	zt_renderDrawList(&g_game->camera, &g_game->draw_list, ztColor::zero, ztRenderDrawListFlags_NoClear);


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
