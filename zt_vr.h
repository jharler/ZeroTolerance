/**************************************************************************************************
 ** file: zt_vr.h v 0.00 (active initial development)
 **
 ** This software is dual-licensed to the public domain and under the following
 ** license: you are granted a perpetual, irrevocable license to copy, modify,
 ** publish, and distribute this file as you see fit.
 **
 ** No warranty is offered or implied.  Use this at your own risk.
 **
 **************************************************************************************************
   
	Zero Tolerance Virtual Reality Library
   
	In exactly one c/cpp source file of your project, you must:

		#define ZT_VR_IMPLEMENTATION
		#include "openvr/openvr.h"
		#include "zt_vr.h"
    
 **************************************************************************************************

    Options:


 **************************************************************************************************

	Implimentation Options: (only used with ZT_VR_IMPLEMENTATION #include)


 **************************************************************************************************/

#ifndef __zt_vr_h_included__
#define __zt_vr_h_included__

#include "zt_tools.h"
#include "zt_game.h"

// ------------------------------------------------------------------------------------------------

enum ztVrSystem_Enum
{
	ztVrSystem_Unknown,
	ztVrSystem_Vive,

	ztVrSystem_MAX,
};

// ------------------------------------------------------------------------------------------------

enum ztVrTrackedDeviceType_Enum
{
	ztVrTrackedDeviceType_Headset,
	ztVrTrackedDeviceType_Controller,
};

// ------------------------------------------------------------------------------------------------

struct ztVrTrackedDevice
{
	ztVrTrackedDeviceType_Enum type;
	int index;

	ztModel *model;
	bool actively_tracking;

	ztTransform transform;
};

// ------------------------------------------------------------------------------------------------

struct ztVrControllerStateVive
{
	// 0 - not pressed, 1 - fully pressed
	r32 trigger;

	r32 menu_button;
	r32 grip_button;

	r32 trackpad_x;
	r32 trackpad_y;

	r32 trackpad_press_x;
	r32 trackpad_press_y;
};

// ------------------------------------------------------------------------------------------------

struct ztVrControllerState
{
	union {
		ztVrControllerStateVive vive;
	};
};

// ------------------------------------------------------------------------------------------------

struct ztVrSystem
{
	ztVrSystem_Enum system;

	ztVrTrackedDevice headset;

	ztVrTrackedDevice *controllers;
	ztVrControllerState *controller_states;
	int controllers_count;

	ztCamera camera_left;
	ztCamera camera_right;

	ztTextureID tex_left;
	ztTextureID tex_right;

	void *internal_data;
};

// ------------------------------------------------------------------------------------------------

bool zt_vrIsHeadsetPresent();

ztVrSystem *zt_vrMake();
void zt_vrFree(ztVrSystem *vr_system);

bool zt_vrUpdate(ztVrSystem *vr_system);
bool zt_vrSubmit(ztVrSystem *vr_system);

void zt_vrControllerTriggerHapticFeedback(ztVrSystem *vr_system, int controller, r32 strength);


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

#if defined(ZT_VR_IMPLEMENTATION) || defined(ZT_VR_INTERNAL_DECLARATIONS)

struct ztVrInternal
{
	vr::IVRSystem *system;
	ztVrSystem *parent;

	ztMat4 cam_mat_left_proj, cam_mat_left_view;
	ztMat4 cam_mat_right_proj, cam_mat_right_view;

	ztMat4 headset_matrix;
	ztMat4 *controllers_matrix;
};

#endif // internal declarations

#if defined(ZT_VR_IMPLEMENTATION)

#define ZT_GAME_INTERNAL_DECLARATIONS
#include "zt_game.h"

#pragma comment(lib, "openvr_api.lib")


ztInternal void _zt_vrConvertMatrix(vr::HmdMatrix44_t& hmat, ztMat4& m)
{
	m[ztMat4_Col0Row0] = hmat.m[0][0]; m[ztMat4_Col1Row0] = hmat.m[0][1]; m[ztMat4_Col2Row0] = hmat.m[0][2]; m[ztMat4_Col3Row0] = hmat.m[0][3];
	m[ztMat4_Col0Row1] = hmat.m[1][0]; m[ztMat4_Col1Row1] = hmat.m[1][1]; m[ztMat4_Col2Row1] = hmat.m[1][2]; m[ztMat4_Col3Row1] = hmat.m[1][3];
	m[ztMat4_Col0Row2] = hmat.m[2][0]; m[ztMat4_Col1Row2] = hmat.m[2][1]; m[ztMat4_Col2Row2] = hmat.m[2][2]; m[ztMat4_Col3Row2] = hmat.m[2][3];
	m[ztMat4_Col0Row3] = hmat.m[3][0]; m[ztMat4_Col1Row3] = hmat.m[3][1]; m[ztMat4_Col2Row3] = hmat.m[3][2]; m[ztMat4_Col3Row3] = hmat.m[3][3];
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_vrConvertMatrix(vr::HmdMatrix34_t& hmat, ztMat4& m)
{
	// float m[3][4];

	m[ztMat4_Col0Row0] = hmat.m[0][0]; m[ztMat4_Col1Row0] = hmat.m[0][1]; m[ztMat4_Col2Row0] = hmat.m[0][2]; m[ztMat4_Col3Row0] = hmat.m[0][3];
	m[ztMat4_Col0Row1] = hmat.m[1][0]; m[ztMat4_Col1Row1] = hmat.m[1][1]; m[ztMat4_Col2Row1] = hmat.m[1][2]; m[ztMat4_Col3Row1] = hmat.m[1][3];
	m[ztMat4_Col0Row2] = hmat.m[2][0]; m[ztMat4_Col1Row2] = hmat.m[2][1]; m[ztMat4_Col2Row2] = hmat.m[2][2]; m[ztMat4_Col3Row2] = hmat.m[2][3];
	m[ztMat4_Col0Row3] =            0; m[ztMat4_Col1Row3] =            0; m[ztMat4_Col2Row3] =            0; m[ztMat4_Col3Row3] = 1;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztModel *_zt_vrLoadModel(ztVrInternal *vr, int tracking_device_index, ztShaderID shader_id)
{
	char buffer[1024] = { 0 };
	vr::TrackedPropertyError* error = nullptr;
	vr->system->GetStringTrackedDeviceProperty(tracking_device_index, vr::Prop_RenderModelName_String, buffer, zt_elementsOf(buffer), error);
	zt_logDebug("vr: device index %d name: %s", tracking_device_index, buffer);

	vr::RenderModel_t* render_model = nullptr;
	while (vr::VRRenderModels()->LoadRenderModel_Async(buffer, &render_model) == vr::VRRenderModelError_Loading) {
		zt_sleep(.10f);
	}

	if (vr::VRRenderModels()->LoadRenderModel_Async(buffer, &render_model) != vr::VRRenderModelError_None || render_model == nullptr) {
		zt_logCritical("vr: unable to load render model %s\n", buffer);
		return nullptr;
	}

	vr::RenderModel_TextureMap_t *texture = NULL;
	while (vr::VRRenderModels()->LoadTexture_Async(render_model->diffuseTextureId, &texture) == vr::VRRenderModelError_Loading) {
		zt_sleep(.10f);
	}

	if (vr::VRRenderModels()->LoadTexture_Async(render_model->diffuseTextureId, &texture) != vr::VRRenderModelError_None || texture == nullptr) {
		zt_logCritical("vr: unable to load render texture id: %d for render model %s\n", render_model->diffuseTextureId, buffer);
		vr::VRRenderModels()->FreeRenderModel(render_model);
		return nullptr;
	}

	ztTextureID tex_id = zt_textureMakeFromPixelData((void*)texture->rubTextureMapData, (i32)texture->unWidth, (i32)texture->unHeight, 0);
	if (tex_id == ztInvalidID) {
		vr::VRRenderModels()->FreeRenderModel(render_model);
		return nullptr;
	}

	ztMaterial material = zt_materialMake(tex_id, ztVec4::one, ztMaterialFlags_OwnsTexture);

	ztVec3* verts = zt_mallocStructArray(ztVec3, render_model->unVertexCount);
	ztVec2* uvs = zt_mallocStructArray(ztVec2, render_model->unVertexCount);
	ztVec3* normals = zt_mallocStructArray(ztVec3, render_model->unVertexCount);
	u32* indices = zt_mallocStructArray(u32, render_model->unTriangleCount * 3);

	zt_fiz(render_model->unVertexCount) {
		verts[i] = ztVec3(render_model->rVertexData[i].vPosition.v[0], render_model->rVertexData[i].vPosition.v[1], render_model->rVertexData[i].vPosition.v[2]);
		uvs[i] = ztVec2(render_model->rVertexData[i].rfTextureCoord[0], render_model->rVertexData[i].rfTextureCoord[1]);
		normals[i] = ztVec3(render_model->rVertexData[i].vNormal.v[0], render_model->rVertexData[i].vNormal.v[1], render_model->rVertexData[i].vNormal.v[2]);
	}
	zt_fiz(render_model->unTriangleCount * 3) {
		indices[i] = render_model->rIndexData[i];
	}

	ztMeshID mesh_id = zt_meshMake(verts, uvs, normals, (i32)render_model->unVertexCount, indices, render_model->unTriangleCount * 3);
	zt_free(verts);
	zt_free(uvs);
	zt_free(normals);
	zt_free(indices);

	if (mesh_id == ztInvalidID) {
		zt_textureFree(tex_id);
		vr::VRRenderModels()->FreeRenderModel(render_model);
		return nullptr;
	}

	ztModel *model = zt_modelMake(zt_memGetGlobalArena(), mesh_id, &material, shader_id, nullptr, ztModelFlags_CastsShadows);
	if (model == nullptr) {
		zt_textureFree(tex_id);
	}

	vr::VRRenderModels()->FreeRenderModel(render_model);

	return model;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_vrProcessEvent(ztVrInternal* vr, const vr::VREvent_t& vr_event)
{
	switch (vr_event.eventType)
	{
		case vr::VREvent_TrackedDeviceActivated: {
			switch (vr->system->GetTrackedDeviceClass(vr_event.trackedDeviceIndex))
			{
				case vr::TrackedDeviceClass_HMD: {
					zt_logDebug("vr: headset tracking activated");

					vr->parent->headset.actively_tracking = true;
					if (vr->parent->headset.model == nullptr) {
						vr->parent->headset.model = _zt_vrLoadModel(vr, vr_event.trackedDeviceIndex, zt_shaderGetDefault(ztShaderDefault_LitShadow)); // todo: make the shader configurable
					}
				} break;

				case vr::TrackedDeviceClass_Controller: {
					zt_fiz(vr->parent->controllers_count) {
						if (vr->parent->controllers[i].index == vr_event.trackedDeviceIndex || vr->parent->controllers[i].index == -1) {
							vr->parent->controllers[i].index = vr_event.trackedDeviceIndex;
							zt_logDebug("vr: controller %d tracking activated (device index %d)", i + 1, vr_event.trackedDeviceIndex);
							vr->parent->controllers[i].actively_tracking = true;
							if (vr->parent->controllers[i].model == nullptr) {
								vr->parent->controllers[i].model = _zt_vrLoadModel(vr, vr_event.trackedDeviceIndex, zt_shaderGetDefault(ztShaderDefault_LitShadow)); // todo: see above
							}
							break;
						}
					}
				} break;
			}
		} break;

		case vr::VREvent_TrackedDeviceDeactivated: {
			switch (vr->system->GetTrackedDeviceClass(vr_event.trackedDeviceIndex))
			{
				case vr::TrackedDeviceClass_HMD: {
					zt_logDebug("vr: headset tracking deactivated");
					vr->parent->headset.actively_tracking = false;
				} break;

				case vr::TrackedDeviceClass_Controller: {
					zt_fiz(vr->parent->controllers_count) {
						if (vr->parent->controllers[i].index == vr_event.trackedDeviceIndex) {
							zt_logDebug("vr: controller %d tracking deactivated (device index %d)", i + 1, vr_event.trackedDeviceIndex);
							vr->parent->controllers[i].actively_tracking = false;
							break;
						}
					}
				} break;
			}
		} break;

		case vr::VREvent_TrackedDeviceUpdated: {
		} break;
	}
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

bool zt_vrIsHeadsetPresent()
{
	return vr::VR_IsHmdPresent();
}

// ------------------------------------------------------------------------------------------------

ztVrSystem *zt_vrMake()
{
	if (!zt_vrIsHeadsetPresent()) {
		return nullptr;
	}

	vr::EVRInitError error = vr::VRInitError_None;
	vr::IVRSystem* vr_system = vr::VR_Init(&error, vr::VRApplication_Scene);
	if (error != vr::VRInitError_None) {
		zt_logCritical("vr: unable to initialize virtual reality");
		return nullptr;
	}

	if (!vr::VRCompositor()) {
		zt_logCritical("unable to initialize virtual reality compositor");
		return nullptr;
	}

	ztVrSystem *vr_parent = zt_mallocStruct(ztVrSystem);
	ztVrInternal *vr_internal = zt_mallocStruct(ztVrInternal);

	vr_parent->internal_data = vr_internal;
	vr_internal->parent = vr_parent;
	vr_internal->system = vr_system;

	char system_name[1024];
	vr_system->GetStringTrackedDeviceProperty(0, vr::Prop_ModelNumber_String, system_name, zt_elementsOf(system_name));
	if (zt_striStartsWith(system_name, "vive")) {
		vr_parent->system = ztVrSystem_Vive;
	}

	// prepare cameras
	u32 width = 0, height = 0;
	vr_system->GetRecommendedRenderTargetSize(&width, &height);

	vr_parent->tex_left = zt_textureMakeRenderTarget(width, height, 0);
	vr_parent->tex_right = zt_textureMakeRenderTarget(width, height, 0);

	zt_cameraMakePersp(&vr_parent->camera_left, width, height, 60, .1f, 30);
	zt_cameraMakePersp(&vr_parent->camera_right, width, height, 60, .1f, 30);

	// OpenVR sends us the camera view matrices based on relative position to the headset
	vr::HmdMatrix44_t hmat_left_proj = vr_system->GetProjectionMatrix(vr::Eye_Left, 0.1f, 100.0f, zt_currentRenderer() == ztRenderer_OpenGL ? vr::API_OpenGL : vr::API_DirectX);
	vr::HmdMatrix44_t hmat_right_proj = vr_system->GetProjectionMatrix(vr::Eye_Right, 0.1f, 100.0f, zt_currentRenderer() == ztRenderer_OpenGL ? vr::API_OpenGL : vr::API_DirectX);
	_zt_vrConvertMatrix(hmat_left_proj, vr_internal->cam_mat_left_proj);
	_zt_vrConvertMatrix(hmat_right_proj, vr_internal->cam_mat_right_proj);

	vr::HmdMatrix34_t hmat_left_view = vr_system->GetEyeToHeadTransform(vr::Eye_Left);
	vr::HmdMatrix34_t hmat_right_view = vr_system->GetEyeToHeadTransform(vr::Eye_Right);
	_zt_vrConvertMatrix(hmat_left_view, vr_internal->cam_mat_left_view);
	_zt_vrConvertMatrix(hmat_right_view, vr_internal->cam_mat_right_view);

	vr_parent->controllers_count = vr::k_unMaxTrackedDeviceCount - 1;
	vr_parent->controllers = zt_mallocStructArray(ztVrTrackedDevice, vr_parent->controllers_count);
	vr_parent->controller_states = zt_mallocStructArray(ztVrControllerState, vr_parent->controllers_count);
	vr_internal->controllers_matrix = zt_mallocStructArray(ztMat4, vr_parent->controllers_count);

	zt_fiz(vr_parent->controllers_count) {
		vr_parent->controllers[i].index = -1;
		vr_parent->controllers[i].type = ztVrTrackedDeviceType_Controller;
		vr_parent->controllers[i].actively_tracking = false;
	}
	vr_parent->headset.type = ztVrTrackedDeviceType_Headset;
	vr_parent->headset.actively_tracking = false;

	int controller_idx = 0;
	zt_fiz(vr::k_unMaxTrackedDeviceCount) {
		ztModel ** model = nullptr;

		switch (vr_system->GetTrackedDeviceClass(i))
		{
			case vr::TrackedDeviceClass_HMD: {
				model = &vr_parent->headset.model;
				vr_parent->headset.actively_tracking = true;

				int debug = 0;
			} break;

			case vr::TrackedDeviceClass_Controller: {
				model = &vr_parent->controllers[controller_idx].model;
				vr_parent->controllers[controller_idx].index = i;
				vr_parent->controllers[controller_idx].actively_tracking = true;

				zt_logDebug("vr: controller %d device index is %d", controller_idx, i);
			} break;
		}

		if (model == nullptr) continue;

		*model = _zt_vrLoadModel(vr_internal, i, zt_shaderGetDefault(ztShaderDefault_LitShadow));
	}

	return vr_parent;
}

// ------------------------------------------------------------------------------------------------

void zt_vrFree(ztVrSystem *vr_system)
{
	if (vr_system == nullptr) {
		return;
	}

	//vr::VR_Shutdown();

	if (vr_system->headset.model) {
		zt_materialFree(&vr_system->headset.model->material);
		zt_meshFree(vr_system->headset.model->mesh_id);
		zt_modelFree(vr_system->headset.model);
	}

	zt_fiz(vr_system->controllers_count) {
		if (vr_system->controllers[i].model) {
			zt_materialFree(&vr_system->controllers[i].model->material);
			zt_meshFree(vr_system->controllers[i].model->mesh_id);
			zt_modelFree(vr_system->controllers[i].model);
		}
	}

	zt_free(vr_system->controller_states);
	zt_free(vr_system->controllers);
	zt_free(vr_system->internal_data);
	zt_free(vr_system);
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_vrControllerAxisIndexForType(ztVrInternal *vr, int tracked_device, vr::EVRControllerAxisType axis_type)
{
	static int cached[vr::k_unControllerStateAxisCount];
	static bool first = true;
	if (first) {
		zt_fiz(zt_elementsOf(cached)) {
			cached[i] = -1;
		}
	}

	if (cached[axis_type] != -1) {
		return cached[axis_type];
	}

	zt_fkz(vr::k_unControllerStateAxisCount) {
		if (vr->system->GetInt32TrackedDeviceProperty(tracked_device, (vr::ETrackedDeviceProperty)(vr::Prop_Axis0Type_Int32 + k)) == axis_type) {
			return k;
		}
	}

	return 0;
}

// ------------------------------------------------------------------------------------------------

bool zt_vrUpdate(ztVrSystem *vr_system)
{
	ztVrInternal *vr = (ztVrInternal*)vr_system->internal_data;

	vr::VREvent_t vr_event;
	while (vr->system->PollNextEvent(&vr_event, sizeof(vr_event))) {
		_zt_vrProcessEvent(vr, vr_event);
	}

	vr::TrackedDevicePose_t devices_poses[vr::k_unMaxTrackedDeviceCount];
	vr::VRCompositor()->WaitGetPoses(devices_poses, zt_elementsOf(devices_poses), nullptr, 0);

	bool found_hmd = false;
	for (int i = 0; i < zt_elementsOf(devices_poses); ++i) {
		if (!devices_poses[i].bPoseIsValid) continue;

		switch (vr->system->GetTrackedDeviceClass(i))
		{
			case vr::TrackedDeviceClass_HMD: {
				_zt_vrConvertMatrix(devices_poses[i].mDeviceToAbsoluteTracking, vr->headset_matrix);
				vr->headset_matrix.extract(&vr_system->headset.transform.position, &vr_system->headset.transform.rotation, &vr_system->headset.transform.scale);
				if (vr_system->headset.model) {
					vr_system->headset.model->transform = vr_system->headset.transform;
				}

				found_hmd = true;
			} break;

			case vr::TrackedDeviceClass_Controller: {
				zt_fjz(vr_system->controllers_count) {
					if (vr_system->controllers[j].index == i) {
						_zt_vrConvertMatrix(devices_poses[i].mDeviceToAbsoluteTracking, vr->controllers_matrix[j]);
						vr->controllers_matrix[j].extract(&vr_system->controllers[j].transform.position, &vr_system->controllers[j].transform.rotation, &vr_system->controllers[j].transform.scale);
						if (vr_system->controllers[j].model) {
							vr_system->controllers[j].model->transform = vr_system->controllers[j].transform;
						}

						vr::VRControllerState_t controller_state;
						vr->system->GetControllerState(i, &controller_state);

						zt_memSet(&vr_system->controller_states[j], zt_sizeof(ztVrControllerState), 0);

						if (vr_system->system == ztVrSystem_Vive) {
							vr::EVRControllerAxisType axis_types[vr::k_unControllerStateAxisCount];
							zt_fkz(zt_elementsOf(axis_types)) {
								axis_types[k] = (vr::EVRControllerAxisType)vr->system->GetInt32TrackedDeviceProperty(i, (vr::ETrackedDeviceProperty)(vr::Prop_Axis0Type_Int32 + k));
							}

							if (controller_state.ulButtonPressed) {
								if (zt_bitIsSet(controller_state.ulButtonPressed, ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger))) {
									// only pressed when trigger is more than half way
									vr_system->controller_states[j].vive.trigger = controller_state.rAxis[_zt_vrControllerAxisIndexForType(vr, i, vr::k_eControllerAxis_Trigger)].x;
								}
								if (zt_bitIsSet(controller_state.ulButtonPressed, ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad))) {
									int axis = _zt_vrControllerAxisIndexForType(vr, i, vr::k_eControllerAxis_TrackPad);
									vr_system->controller_states[j].vive.trackpad_press_x = controller_state.rAxis[axis].x;
									vr_system->controller_states[j].vive.trackpad_press_y = controller_state.rAxis[axis].y;
								}
								if (zt_bitIsSet(controller_state.ulButtonPressed, ButtonMaskFromId(vr::k_EButton_ApplicationMenu))) {
									vr_system->controller_states[j].vive.menu_button = 1;
								}
								if (zt_bitIsSet(controller_state.ulButtonPressed, ButtonMaskFromId(vr::k_EButton_Grip))) {
									vr_system->controller_states[j].vive.grip_button = 1;
								}
							}
							if (controller_state.ulButtonTouched) {
								if (zt_bitIsSet(controller_state.ulButtonTouched, ButtonMaskFromId(vr::k_EButton_SteamVR_Trigger))) {
									// only touched when trigger is less than half way
									vr_system->controller_states[j].vive.trigger = controller_state.rAxis[_zt_vrControllerAxisIndexForType(vr, i, vr::k_eControllerAxis_Trigger)].x;
								}
								if (zt_bitIsSet(controller_state.ulButtonTouched, ButtonMaskFromId(vr::k_EButton_SteamVR_Touchpad))) {
									int axis = _zt_vrControllerAxisIndexForType(vr, i, vr::k_eControllerAxis_TrackPad);
									vr_system->controller_states[j].vive.trackpad_x = controller_state.rAxis[axis].x;
									vr_system->controller_states[j].vive.trackpad_y = controller_state.rAxis[axis].y;
								}
							}
						}

						break;
					}
				}
			} break;
		}
	}
	if (!found_hmd) {
		return false;
	}

	ztMat4 cam_left = vr->headset_matrix * vr->cam_mat_left_view;
	ztMat4 cam_right = vr->headset_matrix * vr->cam_mat_right_view;

	cam_left.inverse();
	cam_right.inverse();

	zt_cameraSetMatrices(&vr_system->camera_left, vr->cam_mat_left_proj, cam_left);
	zt_cameraSetMatrices(&vr_system->camera_right, vr->cam_mat_right_proj, cam_right);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_vrSubmit(ztVrSystem *vr_system)
{
	ztTexture *tex_left = &zt->textures[vr_system->tex_left];
	ztTexture *tex_right = &zt->textures[vr_system->tex_right];

	vr::Texture_t vr_tex_left, vr_tex_right;

	bool is_gl = false;

	switch (zt_currentRenderer())
	{
		case ztRenderer_OpenGL: {
#			if defined(ZT_OPENGL)
			vr_tex_left.handle = (void*)tex_left->gl_texid;
			vr_tex_right.handle = (void*)tex_right->gl_texid;

			vr_tex_left.eType = vr_tex_right.eType = vr::API_OpenGL;
			vr_tex_left.eColorSpace = vr_tex_right.eColorSpace = vr::ColorSpace_Gamma;

			is_gl = true;
#			endif
		} break;

		case ztRenderer_DirectX: {
#			if defined(ZT_DIRECTX)
			vr_tex_left.handle = (void*)tex_left->dx_tex;
			vr_tex_right.handle = (void*)tex_right->dx_tex;

			vr_tex_left.eType = vr_tex_right.eType = vr::API_DirectX;
			vr_tex_left.eColorSpace = vr_tex_right.eColorSpace = vr::ColorSpace_Auto;
#			endif
		} break;
	}

	vr::VRCompositor()->Submit(vr::Eye_Left, &vr_tex_left);
	vr::VRCompositor()->Submit(vr::Eye_Right, &vr_tex_right);

#	if defined(ZT_OPENGL)
	if (is_gl) {
		// see notes in openvr Hello VR sample code:
		glFinish();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	#endif

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_vrControllerTriggerHapticFeedback(ztVrSystem *vr_system, int controller, r32 strength)
{
	ztVrInternal *vr = (ztVrInternal*)vr_system->internal_data;

	vr->system->TriggerHapticPulse(vr_system->controllers[controller].index, vr::k_EButton_SteamVR_Touchpad - vr::k_EButton_Axis0, zt_convertToi32Floor(zt_linearRemap(strength, 0, 1, 0, 3999)));
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // implementation
