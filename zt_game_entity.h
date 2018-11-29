/***************************************************************************************************************************************************************************************************
file: zt_game_entity.h v 0.00 (active initial development)

This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.

No warranty is offered or implied.  Use this at your own risk.

***************************************************************************************************************************************************************************************************

Zero Tolerance Game Entity Component System

In exactly one c/cpp source file of your project, you must:

#define ZT_GAME_ENTITY_IMPLEMENTATION
#include "zt_game_entity.h"

***************************************************************************************************************************************************************************************************

Options:


***************************************************************************************************************************************************************************************************

Implementation Options: (only used with ZT_GAME_ENTITY_IMPLEMENTATION #include)


***************************************************************************************************************************************************************************************************/

#ifndef __zt_game_entity_h__
#define __zt_game_entity_h__

// ================================================================================================================================================================================================

#include "zt_game.h"
#include "zt_game_gui.h"

// ================================================================================================================================================================================================

typedef i64 ztEntityID;        // globally unique
typedef i32 ztComponentID;     // unique on a per-component system basis

// ================================================================================================================================================================================================

#define zt_entityIndex(entity_id)                  ((i32)((((entity_id) & 0xffffffff00000000)>> 32)))
#define zt_entityInternalID(entity_id)             ((i32)((entity_id) & 0x00000000ffffffff))
#define zt_entityMakeID(index, internal_id)        ((((i64)(index)) << 32) | (internal_id))

// ================================================================================================================================================================================================

struct ztEntity;
struct ztEntityPool;
struct ztEntityEditor;
struct ztComponent;
struct ztComponentEntry;

#define ZT_FUNC_COMPONENT_MAKE_DECL(name) void name(ztEntityPool *pool, ztEntityID entity_id, ztComponent *component)
typedef ZT_FUNC_COMPONENT_MAKE_DECL(ztComponentMake_Func);
#define ZT_FUNC_COMPONENT_MAKE(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_MAKE_DECL(name))

#define ZT_FUNC_COMPONENT_FREE_DECL(name) void name(ztEntityPool *pool, ztEntityID entity_id, ztComponent *component, ztComponentID component_id)
typedef ZT_FUNC_COMPONENT_FREE_DECL(ztComponentFree_Func);
#define ZT_FUNC_COMPONENT_FREE(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_FREE_DECL(name))

#define ZT_FUNC_COMPONENT_FIND_DECL(name) ztComponentID name(ztComponent *component, ztEntity *entity, ztEntityID entity_id, ztComponentID after_component_id)
typedef ZT_FUNC_COMPONENT_FIND_DECL(ztComponentFind_Func);
#define ZT_FUNC_COMPONENT_FIND(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_FIND_DECL(name))

#define ZT_FUNC_COMPONENT_GUI_DECL(name) ztGuiItem *name(ztComponent *component, ztComponentID component_id, ztGuiItem *parent)
typedef ZT_FUNC_COMPONENT_GUI_DECL(ztComponentGui_Func);
#define ZT_FUNC_COMPONENT_GUI(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_GUI_DECL(name))

#define ZT_FUNC_COMPONENT_SAVE_DECL(name) bool name(ztEntityPool *pool, ztComponent *component, ztSerial *serial)
typedef ZT_FUNC_COMPONENT_SAVE_DECL(ztComponentSave_Func);
#define ZT_FUNC_COMPONENT_SAVE(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_SAVE_DECL(name))

#define ZT_FUNC_COMPONENT_LOAD_DECL(name) bool name(ztEntityPool *pool, ztComponent *component, ztSerial *serial)
typedef ZT_FUNC_COMPONENT_LOAD_DECL(ztComponentLoad_Func);
#define ZT_FUNC_COMPONENT_LOAD(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_LOAD_DECL(name))

#define ZT_FUNC_COMPONENT_UPDATE_DECL(name) bool name(ztEntityPool *pool, ztComponent *component, r32 dt, ztCamera *camera, bool gui_input, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
typedef ZT_FUNC_COMPONENT_UPDATE_DECL(ztComponentUpdate_Func);
#define ZT_FUNC_COMPONENT_UPDATE(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_UPDATE_DECL(name))

// the following are optional functions that can be used to enhance component functionality
#define ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK_DECL(name) bool name(ztEntityPool *pool, ztCamera *camera, ztComponent *component, ztVec3 ray_pos, ztVec3 ray_dir, i32 *closest_id, r32 *closest_dist, ztInputMouse *input_mouse, ztInputKeys *input_keys)
typedef ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK_DECL(ztComponentEditQueryClick_Func);
#define ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK_DECL(name))

#define ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK_DECL(name) bool name(ztEntityPool *pool, ztCamera *camera, ztComponent *component, ztVec3 ray_pos, ztVec3 ray_dir, i32 closest_id, ztInputMouse *input_mouse, ztInputKeys *input_keys)
typedef ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK_DECL(ztComponentEditProcessClick_Func);
#define ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK_DECL(name))

#define ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_DECL(name) void name(ztComponent *component, ztCamera *camera, ztDrawList *draw_list, ztEntityID active_entity_id, ztComponentID active_component_id)
typedef ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_DECL(ztComponentEditDrawDebug_Func);
#define ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_DECL(name))

#define ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_ALL_DECL(name) void name(ztComponent *component, ztCamera *camera, ztDrawList *draw_list, ztEntityID active_entity_id, ztComponentID active_component_id)
typedef ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_ALL_DECL(ztComponentEditDrawDebugAll_Func);
#define ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_ALL(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_ALL_DECL(name))

#define ZT_FUNC_COMPONENT_NOTIFY_CHANGE_DECL(name) void name(ztEntityPool *pool, ztComponent *component, ztEntity *entity, ztEntityID entity_id, ztComponentID component_id)
typedef ZT_FUNC_COMPONENT_NOTIFY_CHANGE_DECL(ztComponentNotifyChange_Func);
#define ZT_FUNC_COMPONENT_NOTIFY_CHANGE(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_COMPONENT_NOTIFY_CHANGE_DECL(name))

// ================================================================================================================================================================================================

#define ZT_FUNC_ENTITY_SERIALIZE_EXTRA_SAVE_DECL(name) bool name(ztEntityPool *pool, ztSerial *serial, void *user_data)
typedef ZT_FUNC_ENTITY_SERIALIZE_EXTRA_SAVE_DECL(ztEntitySerialExtraSave_Func);
#define ZT_FUNC_ENTITY_SERIALIZE_EXTRA_SAVE(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_ENTITY_SERIALIZE_EXTRA_SAVE_DECL(name))

#define ZT_FUNC_ENTITY_SERIALIZE_EXTRA_LOAD_DECL(name) bool name(ztEntityPool *pool, ztSerial *serial, void *user_data)
typedef ZT_FUNC_ENTITY_SERIALIZE_EXTRA_LOAD_DECL(ztEntitySerialExtraLoad_Func);
#define ZT_FUNC_ENTITY_SERIALIZE_EXTRA_LOAD(name) ZT_FUNCTION_POINTER_REGISTER(name, ZT_FUNC_ENTITY_SERIALIZE_EXTRA_LOAD_DECL(name))



// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_COMPONENTS_MAX
#define ZT_COMPONENTS_MAX  64 // must be a multiple of 32
#endif

// ================================================================================================================================================================================================

struct ztEntity
{
	i32               internal_id;
	ztString          name;
	ztEntity         *parent;
	ztEntity         *child;
	ztEntity         *next;

	ztComponentEntry *components;
};

// ================================================================================================================================================================================================

struct ztComponent
{
	ztGuid  guid;
	char    name[64];
	void   *user_data;

	ZT_FUNCTION_POINTER_VAR(component_make,                ztComponentMake_Func);
	ZT_FUNCTION_POINTER_VAR(component_free,                ztComponentFree_Func);
	ZT_FUNCTION_POINTER_VAR(component_find,                ztComponentFind_Func);
	ZT_FUNCTION_POINTER_VAR(component_gui,                 ztComponentGui_Func);
	ZT_FUNCTION_POINTER_VAR(component_save,                ztComponentSave_Func);
	ZT_FUNCTION_POINTER_VAR(component_load,                ztComponentLoad_Func);
	ZT_FUNCTION_POINTER_VAR(component_update,              ztComponentUpdate_Func);
	ZT_FUNCTION_POINTER_VAR(component_edit_query_click,    ztComponentEditQueryClick_Func);
	ZT_FUNCTION_POINTER_VAR(component_edit_process_click,  ztComponentEditProcessClick_Func);
	ZT_FUNCTION_POINTER_VAR(component_edit_draw_debug,     ztComponentEditDrawDebug_Func);
	ZT_FUNCTION_POINTER_VAR(component_edit_draw_debug_all, ztComponentEditDrawDebugAll_Func);
	ZT_FUNCTION_POINTER_VAR(component_notify_change,       ztComponentNotifyChange_Func);
};

// ================================================================================================================================================================================================

struct ztComponentEntry
{
	ztComponent      *component;
	ztComponentID     component_id;
	ztComponentEntry *next;
};

// ================================================================================================================================================================================================

struct ztEntityPool
{
	ztEntity         *entities;
	i32               entities_size;
	i32               entities_count;

	ztComponent       components[ZT_COMPONENTS_MAX];
	i32               components_count;

	ztComponentEntry *component_entries;
	i32               component_entries_count;

	ztStringPool      string_pool;

	i32               last_id;

	ztEntityEditor   *editor;
};


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool          zt_entityPoolMake(ztEntityPool *pool, i32 entities);
void          zt_entityPoolFree(ztEntityPool *pool);

bool          zt_entityPoolSave(ztEntityPool *pool, const char *file_name, ztEntitySerialExtraSave_Func *extra_save, void *extra_save_user_data);
bool          zt_entityPoolLoad(ztEntityPool *pool, ztAssetManager *asset_manager, ztAssetID asset_id, ztEntitySerialExtraLoad_Func *extra_load, void *extra_load_user_data);
bool          zt_entityPoolLoad(ztEntityPool *pool, const char *file_name, ztEntitySerialExtraLoad_Func *extra_load, void *extra_load_user_data);

ztEntityID    zt_entityPoolMakeEntity(ztEntityPool *pool, const char *name, ztEntityID parent_id = ztInvalidID);
void          zt_entityPoolFreeEntity(ztEntityPool *pool, ztEntityID entity_id);

ztEntity     *zt_entityPoolGetEntity(ztEntityPool *pool, ztEntityID entity_id);

ztEntityID    zt_entityFindByName(ztEntityPool *pool, const char *name, ztEntityID parent_id, bool recursive);

i32           zt_entityPoolRegisterComponent(ztEntityPool *pool, ztGuid guid, const char *name, void *user_data, ZT_FUNCTION_POINTER_VAR(component_make, ztComponentMake_Func), ZT_FUNCTION_POINTER_VAR(component_free, ztComponentFree_Func), ZT_FUNCTION_POINTER_VAR(component_find, ztComponentFind_Func), ZT_FUNCTION_POINTER_VAR(component_gui, ztComponentGui_Func), ZT_FUNCTION_POINTER_VAR(component_save, ztComponentSave_Func), ZT_FUNCTION_POINTER_VAR(component_load, ztComponentLoad_Func), ZT_FUNCTION_POINTER_VAR(component_update, ztComponentUpdate_Func), ztComponent **component_out = nullptr);
i32           zt_entityPoolUnregisterComponent(ztEntityPool *pool, ztGuid guid);

void          zt_entityAddedComponent(ztEntityPool *pool, ztEntityID entity_id, ztGuid component_guid, ztComponentID component_id); // components call when added
void          zt_entityRemovedComponent(ztEntityPool *pool, ztEntityID entity_id, ztGuid component_guid, ztComponentID component_id); // components call when removed

void          zt_entityRemoveComponent(ztEntityPool *pool, ztEntityID entity_id, ztGuid component_guid, ztComponentID component_id);

void          zt_entityPoolUpdate(ztEntityPool *pool, r32 dt, ztCamera *camera, bool gui_input, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_COMPONENTS_MAX_PER_ENTITY
#define ZT_COMPONENTS_MAX_PER_ENTITY  64
#endif

// ================================================================================================================================================================================================

enum ztEntityEditorStateFlags_Enum
{
	ztEntityEditorStateFlags_HasUnsavedChanges = (1<<0),
};

// ================================================================================================================================================================================================

struct ztEntityEditor
{
	i32 state_flags;

	ztEntityPool *pool;

	ztGuiTreeNodeID *entity_nodes;
	ztGuiTreeNodeID  tree_node_scene;

	ztGuiItem       *editor_win;
	ztGuiItem       *editor_tree;
	ztGuiItem       *editor_components_sizer;

	ztGuiTreeNodeID  entity_active_node_id;
	ztGuiItem       *entity_components_gui[ZT_COMPONENTS_MAX_PER_ENTITY];
	ztComponent     *entity_components    [ZT_COMPONENTS_MAX_PER_ENTITY];
	ztComponentID    entity_components_id [ZT_COMPONENTS_MAX_PER_ENTITY];
	i32              entity_components_count;

	char             file_path[ztFileMaxPath];

	ZT_FUNCTION_POINTER_VAR(serial_extra_save, ztEntitySerialExtraSave_Func);
	ZT_FUNCTION_POINTER_VAR(serial_extra_load, ztEntitySerialExtraLoad_Func);
	void                   *serial_extra_user_data;
};

// ================================================================================================================================================================================================

bool       zt_entityEditorMake  (ztEntityEditor *editor, ztEntityPool *pool, i32 max_items = 4096);
void       zt_entityEditorFree  (ztEntityEditor *editor);

bool       zt_entityEditorLoad  (ztEntityEditor *editor, const char *file_name);

bool       zt_entityEditorHasUnsavedChanges(ztEntityEditor *editor);

void       zt_entityEditorNotifyNewEntity(ztEntityEditor *editor, ztEntityID entity);
void       zt_entityEditorNotifyNewComponent(ztEntityEditor *editor, ztEntityID entity, ztGuid component_guid, ztComponentID component_id);
void       zt_entityEditorNotifyDeleteComponent(ztEntityEditor *editor, ztEntityID entity, ztGuid component_guid, ztComponentID component_id);
void       zt_entityEditorNotifyChangedComponent(ztEntityEditor *editor, ztEntityID entity, ztGuid component_guid, ztComponentID component_id);

void       zt_entityEditorMakeEntityActive(ztEntityEditor *editor, ztEntityID entity_id);
ztEntityID zt_entityEditorGetActiveEntity(ztEntityEditor *editor);

void       zt_entityEditorUpdate(ztEntityEditor *editor, r32 dt, ztCamera *camera, bool gui_input, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse);
void       zt_entityEditorRender(ztEntityEditor *editor, ztCamera *camera, ztDrawList *draw_list);


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ===============================================================================
// ztModelComponent
//
// Allows the attachment of ztModels to an entity.
// ===============================================================================

struct ztModelComponentModel
{
	ztGuid            guid;
	char              name[64];
	ztModel          *model;
};

void zt_modelComponentModelMake(ztModelComponentModel *comp_model, ztGuid guid, const char *name, ztModel *model);

// ================================================================================================================================================================================================

struct ztModelComponentShader
{
	ztGuid     guid;
	char       name[64];
	ztShaderID shader;
};

void zt_modelComponentShaderMake(ztModelComponentShader *comp_shader, ztGuid guid, const char *name, ztShaderID shader_id);

// ================================================================================================================================================================================================

struct ztModelComponentMaterial
{
	ztGuid     guid;
	char       name[64];
	ztMaterial material;
};

void zt_modelComponentMaterialMake(ztModelComponentMaterial *comp_material, ztGuid guid, const char *name, ztMaterial *material);

// ================================================================================================================================================================================================

struct ztModelComponent
{
	ztModel                  *models_pool;
	i32                       models_pool_size;
	i32                       models_pool_count;

	ztBone                   *bones_pool;
	i32                       bones_pool_size;
	i32                       bones_pool_count;

	ztGuid                   *models_guids;
	ztModel                 **models;
	i32                      *models_layers;
	i32                       models_count;

	ztEntityID               *entity_ids;

	ztModelComponentModel    *options_models;
	i32                       options_models_size;

	ztModelComponentShader   *options_shaders;
	i32                       options_shaders_size;

	ztModelComponentMaterial *options_materials;
	i32                       options_materials_size;

	ztString                 *options_layers;
	i32                       options_layers_size;

	ztScene                  *scene;

	ztShaderID                default_shader;

	ztModelEditWidget         edit_widget;
	ztModel                  *edit_last_active_model;
	ztEntityID                edit_last_active_entity;
	bool                      edit_show_bounds_aabb;
	bool                      edit_show_wireframe;
	bool                      edit_show_simple;
	i32                       edit_show_layers_mask;
	bool                      edit_ignore_entity_change;
};

// ================================================================================================================================================================================================

bool          zt_modelComponentMakeAndRegister(ztModelComponent *model_component, i32 model_pool_size, i32 bone_pool_size, ztEntityPool *pool, ztModelComponentModel *options_models, i32 options_models_size, ztModelComponentShader *options_shaders, i32 options_shaders_size, ztModelComponentMaterial *options_materials, i32 options_materials_size, const char ** options_layers, i32 options_layers_size, ztScene *scene, bool using_editor, ztShaderID default_shader);
void          zt_modelComponentFreeAndUnregister(ztModelComponent *model_component, ztEntityPool *pool);

ztComponentID zt_modelComponentAdd(ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity, ztGuid model_guid);
void          zt_modelComponentRemove(ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

ztModel      *zt_modelComponentGet(ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity, int which_idx = 0, ztComponentID *component_id_out = nullptr);
ztModel      *zt_modelComponentGet(ztModelComponent *model_component, ztComponentID component_id);

// ===============================================================================
// This takes all the given options_models and creates entities based on the names
//
// parent_entity_name.parent_entity_name.entity_name
//
void          zt_modelComponentCreateAndAssignEntities(ztModelComponent *model_component, ztEntityPool *pool, bool overwrite_existing);

bool          zt_modelComponentFindModelAndIntersectPoint(ztModelComponent *model_component, const ztVec3 &ray_pos, const ztVec3 &ray_dir, ztEntityID *entity_id, ztModel **model, ztVec3 *intersect_point);


// ================================================================================================================================================================================================

struct ztModelComponentMaterialLoaderState
{
	i32 textures_total;
	i32 textures_current;
	i32 materials_total;
	i32 materials_current;
	i32 *asset_manager_file_indexes;
};

i32 zt_modelComponentMaterialLoaderQuery(ztModelComponentMaterialLoaderState *state, ztAssetManager *asset_manager, const char **directories, i32 directories_count, ztModelComponentMaterial **materials);
void zt_modelComponentMaterialLoaderFree(ztModelComponentMaterialLoaderState *state);
bool zt_modelComponentMaterialLoaderUpdate(ztModelComponentMaterialLoaderState *state, ztAssetManager *asset_manager, ztModelComponentMaterial *materials, bool *is_complete, char *error_buffer, i32 error_buffer_len);


// ================================================================================================================================================================================================

struct ztModelComponentShaderLoaderState
{
	i32 shaders_total;
	i32 shaders_current;
	i32 *asset_manager_file_indexes;
};

i32 zt_modelComponentShaderLoaderQuery(ztModelComponentShaderLoaderState *state, ztAssetManager *asset_manager, const char **directories, i32 directories_count, const char **ignore, i32 ignore_count, ztModelComponentShader **shaders);
void zt_modelComponentShaderLoaderFree(ztModelComponentShaderLoaderState *state);
bool zt_modelComponentShaderLoaderUpdate(ztModelComponentShaderLoaderState *state, ztAssetManager *asset_manager, ztModelComponentShader *shaders, bool *is_complete, char *error_buffer, i32 error_buffer_len);

// ================================================================================================================================================================================================


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ===============================================================================
// ztLightComponent
//
// Allows the attachment of ztLights to an entity.
// ===============================================================================

#ifndef ZT_LIGHT_COMPONENT_MAX_LIGHTS
#define ZT_LIGHT_COMPONENT_MAX_LIGHTS ZT_SCENE_MAX_LIGHTS
#endif

struct ztLightComponent
{
	ztLight                   lights       [ZT_SCENE_MAX_LIGHTS];
	ztEntityID                entity_ids   [ZT_SCENE_MAX_LIGHTS];

	i32                       lights_count;

	ztScene                  *scene;

	ztEntityPool             *pool;
	ztModelComponent         *model_component;

	ztModelEditWidget         edit_widget;
	ztTransform               edit_widget_transform;
	ztLight                  *edit_last_active_light;
	ztLight                   edit_copy_active_light;
	ztEntityID                edit_last_active_entity;
	bool                      edit_show_bounds;
	bool                      edit_ignore_entity_change;
};

// ================================================================================================================================================================================================

bool          zt_lightComponentMakeAndRegister(ztLightComponent *light_component, ztEntityPool *pool, ztScene *scene, ztModelComponent *model_component);
void          zt_lightComponentFreeAndUnregister(ztLightComponent *light_component, ztEntityPool *pool);

ztComponentID zt_lightComponentAdd(ztLightComponent *light_component, ztEntityPool *pool, ztEntityID entity, ztLight *light_to_copy);
void          zt_lightComponentRemove(ztLightComponent *light_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

ztLight      *zt_lightComponentGet(ztLightComponent *light_component, ztEntityPool *pool, ztEntityID entity, int which_idx = 0, ztComponentID *component_id_out = nullptr);
ztLight      *zt_lightComponentGet(ztLightComponent *light_component, ztComponentID component_id);


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


// ===============================================================================
// ztRigidBodyComponent
//
// Allows the attachment of ztRigidBodies to an entity.  Requires a ztModelComponent to attach to.
// ===============================================================================


struct ztRigidBodyComponent
{
	ztRigidBody      *rigid_bodies;
	i32               rigid_bodies_size;
	i32               rigid_bodies_count;

	ztString          collision_layers[32];
	i32               collision_layers_count;

	ztEntityID       *entity_ids;

	ztEntityPool     *pool;
	ztModelComponent *model_component;
};

// ================================================================================================================================================================================================

bool          zt_rigidBodyComponentMakeAndRegister(ztRigidBodyComponent *rigid_body_component, i32 pool_size, ztEntityPool *pool, ztModelComponent *model_component, const char **collision_layers, i32 collision_layers_size);
void          zt_rigidBodyComponentFreeAndUnregister(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool);

ztComponentID zt_rigidBodyComponentAdd(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool, ztEntityID entity);
void          zt_rigidBodyComponentRemove(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

ztRigidBody  *zt_rigidBodyComponentGet(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool, ztEntityID entity, int which_idx = 0, ztComponentID *component_id_out = nullptr);
ztRigidBody  *zt_rigidBodyComponentGet(ztRigidBodyComponent *rigid_body_component, ztComponentID component_id);

void          zt_rigidBodyComponentPhysicsPopulate(ztRigidBodyComponent *rigid_body_component, ztPhysics *physics);
void          zt_rigidBodyComponentPhysicsCleanup(ztRigidBodyComponent *rigid_body_component, ztPhysics *physics);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ===============================================================================
// ztStaticBodyComponent
//
// Allows the attachment of ztStaticBodies to an entity.  Requires a ztModelComponent to extract triangles from
// ===============================================================================


struct ztStaticBodyComponent
{
	i32               static_bodies_count;
	i32               static_bodies_size;

	ztEntityID       *entity_ids;

	ztEntityPool     *pool;
	ztModelComponent *model_component;

	ztStaticBody      editor_body;

	bool              changed;
	bool              show_octree;
	bool              show_triangles;

	i32               max_objects_per_node;
	i32               max_node_levels;
};

// ================================================================================================================================================================================================

bool          zt_staticBodyComponentMakeAndRegister(ztStaticBodyComponent *static_body_component, i32 pool_size, ztEntityPool *pool, ztModelComponent *model_component);
void          zt_staticBodyComponentFreeAndUnregister(ztStaticBodyComponent *static_body_component, ztEntityPool *pool);

ztComponentID zt_staticBodyComponentAdd(ztStaticBodyComponent *static_body_component, ztEntityPool *pool, ztEntityID entity);
void          zt_staticBodyComponentRemove(ztStaticBodyComponent *static_body_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

bool          zt_staticBodyComponentCreateStaticBody(ztStaticBodyComponent *static_body_component, ztStaticBody *body);

void          zt_staticBodyComponentPhysicsPopulate(ztStaticBodyComponent *static_body_component, ztPhysics *physics);
void          zt_staticBodyComponentPhysicsCleanup(ztStaticBodyComponent *static_body_component, ztPhysics *physics);


// ===============================================================================
// ztMovingBodyComponent
//
// Allows the attachment of ztMovingBodies to an entity.  Requires a ztModelComponent to attach to.
// ===============================================================================


struct ztMovingBodyComponent
{
	ztMovingBody     *moving_bodies;
	i32               moving_bodies_size;
	i32               moving_bodies_count;

	ztString          collision_layers[32];
	i32               collision_layers_count;

	ztEntityID       *entity_ids;

	ztEntityPool     *pool;
	ztModelComponent *model_component;
};

// ================================================================================================================================================================================================

bool          zt_movingBodyComponentMakeAndRegister(ztMovingBodyComponent *moving_body_component, i32 pool_size, ztEntityPool *pool, ztModelComponent *model_component, const char **collision_layers, i32 collision_layers_size);
void          zt_movingBodyComponentFreeAndUnregister(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool);

ztComponentID zt_movingBodyComponentAdd(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool, ztEntityID entity);
void          zt_movingBodyComponentRemove(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

ztMovingBody *zt_movingBodyComponentGet(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool, ztEntityID entity, int which_idx = 0, ztComponentID *component_id_out = nullptr);
ztMovingBody *zt_movingBodyComponentGet(ztMovingBodyComponent *moving_body_component, ztComponentID component_id);

void          zt_movingBodyComponentPhysicsPopulate(ztMovingBodyComponent *moving_body_component, ztPhysics *physics);
void          zt_movingBodyComponentPhysicsCleanup(ztMovingBodyComponent *moving_body_component, ztPhysics *physics);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ===============================================================================
// ztMarkerComponent
//
// Allows marking a particular point and orientation for use in the game.
// ===============================================================================

#ifndef ZT_MARKER_COMPONENT_MAX_MARKERS
#define ZT_MARKER_COMPONENT_MAX_MARKERS		256
#endif

struct ztMarkerType
{
	ztGuid guid;
	char   label[64];
};

ztMarkerType zt_markerTypeMake(ztGuid guid, const char *label);

struct ztMarkerComponent
{
	struct Marker
	{
		char        name[64];
		ztGuid      type;
		ztTransform transform;
		ztEntityID  entity_id;
	};

	Marker             markers[ZT_MARKER_COMPONENT_MAX_MARKERS];
	i32                markers_count;

	ztMarkerType      *types;
	i32                types_count;

	ztModelEditWidget  edit_widget;

	ztModelComponent  *model_component;
	ztEntityPool      *pool;
};

// ================================================================================================================================================================================================

bool                        zt_markerComponentMakeAndRegister(ztMarkerComponent *marker_component, ztEntityPool *pool, ztModelComponent *model_component, ztMarkerType *types, i32 types_count);
void                        zt_markerComponentFreeAndUnregister(ztMarkerComponent *marker_component, ztEntityPool *pool);

ztComponentID               zt_markerComponentAdd(ztMarkerComponent *marker_component, ztEntityPool *pool, ztEntityID entity);
void                        zt_markerComponentRemove(ztMarkerComponent *marker_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

ztMarkerComponent::Marker  *zt_markerComponentGet(ztMarkerComponent *marker_component, ztEntityPool *pool, ztEntityID entity, int which_idx = 0, ztComponentID *component_id_out = nullptr);
ztMarkerComponent::Marker  *zt_markerComponentGet(ztMarkerComponent *marker_component, ztComponentID component_id);



// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ===============================================================================
// ztTagComponent
//
// Allows tagging a particular entity
// ===============================================================================

#ifndef ZT_TAG_COMPONENT_MAX_TAGS
#define ZT_TAG_COMPONENT_MAX_TAGS		2048
#endif

struct ztTagComponent
{
	struct Tag
	{
		char        tag[64];
		ztEntityID  entity_id;
	};

	const char **defaults;
	i32          defaults_count;

	Tag          tags[ZT_TAG_COMPONENT_MAX_TAGS];
	i32          tags_count;
};

// ================================================================================================================================================================================================

bool          zt_tagComponentMakeAndRegister(ztTagComponent *tag_component, ztEntityPool *pool, const char **defaults, i32 defaults_count);
void          zt_tagComponentFreeAndUnregister(ztTagComponent *tag_component, ztEntityPool *pool);

ztComponentID zt_tagComponentAdd(ztTagComponent *tag_component, ztEntityPool *pool, ztEntityID entity);
void          zt_tagComponentRemove(ztTagComponent *tag_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

const char   *zt_tagComponentGet(ztTagComponent *tag_component, ztEntityPool *pool, ztEntityID entity, int which_idx = 0, ztComponentID *component_id_out = nullptr);
const char   *zt_tagComponentGet(ztTagComponent *tag_component, ztComponentID component_id);



// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ===============================================================================
// ztPathComponent
//
// Allows editing waypoints in a pathfinding array.
// ===============================================================================

#ifndef ZT_PATH_COMPONENT_MAX_PATHS
#define ZT_PATH_COMPONENT_MAX_PATHS		16
#endif

#ifndef ZT_PATH_COMPONENT_MAX_NODES_PER_PATH
#define ZT_PATH_COMPONENT_MAX_NODES_PER_PATH		2048
#endif

struct ztPath
{
	ztGuid  guid;
	char    label[64];
	ztColor color;
};

ztPath zt_pathMake(ztGuid guid, const char *label, ztColor color);

struct ztPathComponent
{
	struct Node
	{
		i32       index;
		ztVec3    position;
		i32       neighbors[ZT_PATH_NODE_MAX_NEIGHBORS];
	};

	struct Path
	{
		i32        path_idx;
		ztEntityID entity_id;
		Node       nodes[ZT_PATH_COMPONENT_MAX_NODES_PER_PATH];
		i32        nodes_count;

		i32        selected_node;
	};

	Path                   paths    [ZT_PATH_COMPONENT_MAX_PATHS];
	ztPath                 paths_ids[ZT_PATH_COMPONENT_MAX_PATHS];
	i32                    paths_count;

	ztModelEditWidget      edit_widget;

	ztModelComponent       *model_component;
	ztEntityPool           *pool;

	bool                    add_to_static_bodies_only;

	i32                     active_path;
	bool                    active_path_adding;
	ztTransform             active_path_transform;
	ztVec3                  active_path_add_point;

	enum Action_Enum
	{
		Action_Add,
		Action_Del,
		Action_Move,
		Action_LinkStep1,
		Action_LinkStep2,
		Action_UnlinkStep1,
		Action_UnlinkStep2,
	};

	Action_Enum            active_action;
};

// ================================================================================================================================================================================================

bool                        zt_pathComponentMakeAndRegister(ztPathComponent *path_component, ztEntityPool *pool, ztModelComponent *model_component, ztPath *paths, i32 paths_count);
void                        zt_pathComponentFreeAndUnregister(ztPathComponent *path_component, ztEntityPool *pool);

ztComponentID               zt_pathComponentAdd(ztPathComponent *path_component, ztEntityPool *pool, ztEntityID entity, ztGuid path_guid);
void                        zt_pathComponentRemove(ztPathComponent *path_component, ztEntityPool *pool, ztEntityID entity, ztComponentID component_id);

i32                         zt_pathComponentPathNodeCount(ztPathComponent *path_component, ztGuid path_guid);
i32                         zt_pathComponentGeneratePath(ztPathComponent *path_component, ztGuid path_guid, ztPathNode *nodes, i32 nodes_count);





// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // include guard

#if defined(ZT_GAME_ENTITY_IMPLEMENTATION) || defined(ZT_GAME_ENTITY_INTERNAL_DECLARATIONS)

#define ZT_GAME_ENTITY_INTERNAL_DECLARATIONS


#endif // defined(ZT_GAME_ENTITY_IMPLEMENTATION) || defined(ZT_GAME_ENTITY_INTERNAL_DECLARATIONS)

#if defined(ZT_GAME_ENTITY_IMPLEMENTATION)

#ifndef __zt_game_entity_implementation__
#define __zt_game_entity_implementation__

#define ZT_GAME_INTERNAL_DECLARATIONS
#include "zt_game.h"

#define ZT_GAME_GUI_INTERNAL_DECLARATIONS
#include "zt_game_gui.h"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


bool zt_entityPoolMake(ztEntityPool *pool, i32 entities)
{
	ZT_PROFILE_GAME("zt_entityPoolMake");

	zt_returnValOnNull(pool, false);
	zt_assertReturnValOnFail(entities > 0, false);

	pool->entities = zt_mallocStructArray(ztEntity, entities);
	pool->entities_size = entities;
	pool->entities_count = 0;

	pool->component_entries_count = entities * 4;
	pool->component_entries = zt_mallocStructArray(ztComponentEntry, pool->component_entries_count);

	pool->components_count = 0;

	int sizes[] = { 32, 64, 128, 256 };
	int props[] = { 50, 40, 5, 5 };

	pool->string_pool = zt_stringPoolMake(entities, sizes, props, zt_elementsOf(sizes));

	return true;
}

// ================================================================================================================================================================================================

void zt_entityPoolFree(ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_entityPoolFree");

	if (pool == nullptr) {
		return;
	}

	if (pool->entities) {
		zt_fiz(pool->entities_count) {
			zt_entityPoolFreeEntity(pool, zt_entityMakeID(i, pool->entities[i].internal_id));
		}

		zt_free(pool->entities);
	}

	if (pool->component_entries) {
		zt_free(pool->component_entries);
	}

	zt_stringPoolFree(&pool->string_pool);

	zt_memSet(pool, zt_sizeof(ztEntityPool), 0);
}

// ================================================================================================================================================================================================

#define ZT_ENTITY_FILE_IDENTIFIER	"2f74a19f392a4bd2b5398a1eea169d54"
#define ZT_ENTITY_FILE_VERSION      10010

// ================================================================================================================================================================================================

ztInternal ztEntity *_zt_entityFind(ztEntityPool *pool, i32 internal_id)
{
	ZT_PROFILE_GAME("_zt_entityFind");

	zt_fiz(pool->entities_count) {
		if (pool->entities[i].internal_id == internal_id) {
			return (&pool->entities[i]);
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

ztInternal i32 _zt_entityFindIndex(ztEntityPool *pool, ztEntity *entity)
{
	ZT_PROFILE_GAME("_zt_entityFindIndex");

	zt_fiz(pool->entities_count) {
		if (entity == &pool->entities[i]) {
			return i;
		}
	}

	return -1;
}

// ================================================================================================================================================================================================

#define _serialCheck(code) if(!(code)) { zt_logCritical("EntityPool serialization failed."); return false; }

// ================================================================================================================================================================================================

bool zt_entityPoolSave(ztEntityPool *pool, const char *file_name, ztEntitySerialExtraSave_Func *extra_save, void *extra_save_user_data)
{
	ZT_PROFILE_GAME("zt_entityPoolSave");

	zt_returnValOnNull(pool, false);
	zt_returnValOnNull(file_name, false);

	ztSerial serial;
	if (!zt_serialMakeWriter(&serial, file_name, ZT_ENTITY_FILE_IDENTIFIER, ZT_ENTITY_FILE_VERSION)) {
		return false;
	}

	_serialCheck(zt_serialGroupPush(&serial));
	{
		_serialCheck(zt_serialWrite(&serial, pool->entities_count));
		_serialCheck(zt_serialWrite(&serial, pool->last_id));

		zt_fiz(pool->entities_count) {
			_serialCheck(zt_serialWrite(&serial, pool->entities[i].internal_id));
		}

		zt_fiz(pool->entities_count) {
			_serialCheck(zt_serialWrite(&serial, pool->entities[i].parent ? pool->entities[i].parent->internal_id : -1));
			_serialCheck(zt_serialWrite(&serial, pool->entities[i].child ? pool->entities[i].child->internal_id : -1));
			_serialCheck(zt_serialWrite(&serial, pool->entities[i].next ? pool->entities[i].next->internal_id : -1));
			_serialCheck(zt_serialWrite(&serial, pool->entities[i].name, zt_strLen(pool->entities[i].name)));
		}
	}
	_serialCheck(zt_serialGroupPop(&serial));

	_serialCheck(zt_serialGroupPush(&serial));
	{
		_serialCheck(zt_serialWrite(&serial, pool->components_count));
		
		zt_fiz(pool->components_count) {
			_serialCheck(zt_serialGroupPush(&serial));
			{
				_serialCheck(zt_serialWrite(&serial, pool->components[i].guid));

				if (ZT_FUNCTION_POINTER_IS_VALID(pool->components[i].component_save)) {
					if (!ZT_FUNCTION_POINTER_ACCESS(pool->components[i].component_save, ztComponentSave_Func)(pool, &pool->components[i], &serial)) {
						return false;
					}
				}
			}
			_serialCheck(zt_serialGroupPop(&serial));
		}
	}
	_serialCheck(zt_serialGroupPop(&serial));

	_serialCheck(zt_serialGroupPush(&serial));
	{
		if (extra_save != nullptr) {
			_serialCheck(extra_save(pool, &serial, extra_save_user_data));
		}
	}
	_serialCheck(zt_serialGroupPop(&serial));



	zt_serialClose(&serial);

	return true;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_entityPoolLoad(ztEntityPool *pool, void *data, i32 data_size, ztEntitySerialExtraLoad_Func *extra_load, void *extra_load_user_data)
{
	ZT_PROFILE_GAME("_zt_entityPoolLoad");

	zt_returnValOnNull(pool, false);
	zt_returnValOnNull(data, false);
	zt_assertReturnValOnFail(data_size > 0, false);

	ztSerial serial;
	if (!zt_serialMakeReader(&serial, data, data_size, ZT_ENTITY_FILE_IDENTIFIER)) {
		return false;
	}

	if (serial.version > ZT_ENTITY_FILE_VERSION) {
		zt_logCritical("Entity pool file version newer than supported");
		return false;
	}

	zt_fiz(pool->entities_count) {
		zt_entityPoolFreeEntity(pool, zt_entityMakeID(i, pool->entities[i].internal_id));
	}

	pool->last_id = 0;

	_serialCheck(zt_serialGroupPush(&serial));
	{
		_serialCheck(zt_serialRead(&serial, &pool->entities_count));
		_serialCheck(zt_serialRead(&serial, &pool->last_id));

		zt_fiz(pool->entities_count) {
			_serialCheck(zt_serialRead(&serial, &pool->entities[i].internal_id));
			pool->last_id = zt_max(pool->last_id, pool->entities[i].internal_id);
		}

		zt_fiz(pool->entities_count) {
			i32 entity_id = 0;
			_serialCheck(zt_serialRead(&serial, &entity_id));
			pool->entities[i].parent = _zt_entityFind(pool, entity_id);

			_serialCheck(zt_serialRead(&serial, &entity_id));
			pool->entities[i].child = _zt_entityFind(pool, entity_id);

			_serialCheck(zt_serialRead(&serial, &entity_id));
			pool->entities[i].next = _zt_entityFind(pool, entity_id);

			char name[128];
			int name_len = 0;
			_serialCheck(zt_serialRead(&serial, name, zt_elementsOf(name), &name_len));

			pool->entities[i].name = nullptr;
			if(name_len >= 0) {
				pool->entities[i].name = zt_stringMakeFrom(&pool->string_pool, name);
			}
		}
	}
	_serialCheck(zt_serialGroupPop(&serial));

	_serialCheck(zt_serialGroupPush(&serial));
	{
		i32 components_count = 0;
		_serialCheck(zt_serialRead(&serial, &components_count));

		zt_fjz(components_count) {
			_serialCheck(zt_serialGroupPush(&serial));
			{
				ztGuid guid;
				_serialCheck(zt_serialRead(&serial, &guid));

				zt_fiz(pool->components_count) {
					if (pool->components[i].guid == guid) {
						if (ZT_FUNCTION_POINTER_IS_VALID(pool->components[i].component_load)) {
							if (!ZT_FUNCTION_POINTER_ACCESS(pool->components[i].component_load, ztComponentLoad_Func)(pool, &pool->components[i], &serial)) {
								return false;
							}
						}
						break;
					}
				}
			}
			_serialCheck(zt_serialGroupPop(&serial));
		}
	}
	_serialCheck(zt_serialGroupPop(&serial));

	_serialCheck(zt_serialGroupPush(&serial));
	{
		if (extra_load != nullptr) {
			_serialCheck(extra_load(pool, &serial, extra_load_user_data));
		}
	}
	_serialCheck(zt_serialGroupPop(&serial));

	zt_serialClose(&serial);

	return true;
}

#	undef _serialCheck

// ================================================================================================================================================================================================

bool zt_entityPoolLoad(ztEntityPool *pool, ztAssetManager *asset_manager, ztAssetID asset_id, ztEntitySerialExtraLoad_Func *extra_load, void *extra_load_user_data)
{
	ZT_PROFILE_GAME("zt_entityPoolLoad");

	zt_returnValOnNull(pool, false);
	zt_returnValOnNull(asset_manager, false);

	void *data = nullptr;
	i32 data_size = 0;
	if (!_zt_assetLoadData(asset_manager, asset_id, nullptr, 0, &data, &data_size)) {
		return false;
	}

	bool result = _zt_entityPoolLoad(pool, data, data_size, extra_load, extra_load_user_data);

	zt_free(data);

	return result;
}

// ================================================================================================================================================================================================

bool zt_entityPoolLoad(ztEntityPool *pool, const char *file_name, ztEntitySerialExtraLoad_Func *extra_load, void *extra_load_user_data)
{
	ZT_PROFILE_GAME("zt_entityPoolLoad");

	i32 data_size = 0;
	void *data = zt_readEntireFile(file_name, &data_size);
	if (data == nullptr) {
		return false;
	}

	bool result = _zt_entityPoolLoad(pool, data, data_size, extra_load, extra_load_user_data);

	zt_free(data);

	return result;
}

// ================================================================================================================================================================================================

ztEntityID zt_entityPoolMakeEntity(ztEntityPool *pool, const char *name, ztEntityID parent_id)
{
	ZT_PROFILE_GAME("zt_entityPoolMakeEntity");

	zt_returnValOnNull(pool, ztInvalidID);

	ztEntity *entity = nullptr;
	i32 entity_idx = 0;

	zt_fiz(pool->entities_size) {
		if (pool->entities[i].internal_id == 0) {
			pool->entities[i].internal_id = ++pool->last_id;
			pool->entities[i].parent = parent_id == ztInvalidID ? nullptr : _zt_entityFind(pool, zt_entityInternalID(parent_id));
			pool->entities[i].child = nullptr;
			pool->entities[i].next = nullptr;
			
			if (zt_strLen(name) != 0) {
				pool->entities[i].name = zt_stringMakeFrom(&pool->string_pool, name);
			}

			if (pool->entities[i].parent) {
				ztEntity *child = &pool->entities[i];
				zt_singleLinkAddToBegin(pool->entities[i].parent->child, child);
			}

			ztEntityID entity_id = zt_entityMakeID(i, pool->entities[i].internal_id);
			zt_assert(entity_id != -1);

			pool->entities_count = zt_max(pool->entities_count, i + 1);
			return entity_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_entityPoolFreeEntity(ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_entityPoolFreeEntity");

	i32 index = zt_entityIndex(entity_id);
	i32 internal_id = zt_entityInternalID(entity_id);

	zt_assertReturnOnFail(index >= 0 && index < pool->entities_count);

	while (pool->entities[index].components) {
		ztComponentEntry *entry = pool->entities[index].components;
		ZT_FUNCTION_POINTER_ACCESS(entry->component->component_free, ztComponentFree_Func)(pool, entity_id, entry->component, entry->component_id);

		if (pool->entities[index].components == entry) {
			zt_assert(false);
			pool->entities[index].components = pool->entities[index].components->next;
		}
	}

	if (pool->entities[index].parent) {
		ztEntity *prev = nullptr;
		zt_flink(child, pool->entities[index].parent->child) {
			if (child == &pool->entities[index]) {
				if (prev) {
					prev->next = child->next;
				}
				if (child == pool->entities[index].parent->child) {
					pool->entities[index].parent->child = child->next;
				}
				break;
			}
			prev = child;
		}
	}

	ztEntity *children = pool->entities[index].child;
	pool->entities[index].child = nullptr;

	zt_flink(child, children) {
		i32 index = _zt_entityFindIndex(pool, child);
		ztEntityID child_id = zt_entityMakeID(index, child->internal_id);
		zt_entityPoolFreeEntity(pool, child_id);
	}

	pool->entities[index].internal_id = 0;
}

// ================================================================================================================================================================================================

ztEntity *zt_entityPoolGetEntity(ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_entityPoolGetEntity");

	i32 index = zt_entityIndex(entity_id);
	i32 internal_id = zt_entityInternalID(entity_id);

	if (index >= 0 && index < pool->entities_count) {
		if (pool->entities[index].internal_id == internal_id) {
			return &pool->entities[index];
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

ztEntityID zt_entityFindByName(ztEntityPool *pool, const char *name, ztEntityID parent_id, bool recursive)
{
	ZT_PROFILE_GAME("zt_entityFindByName");

	i32 parent_idx = zt_entityIndex(parent_id);
	ztEntity *parent = parent_idx < 0 ? nullptr : &pool->entities[parent_idx];

	zt_fiz(pool->entities_count) {
		if (pool->entities[i].internal_id > 0 && (recursive || pool->entities[i].parent == parent)) {
			if (zt_strEquals(pool->entities[i].name, name)) {
				return zt_entityMakeID(i, pool->entities[i].internal_id);
			}
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

i32 zt_entityPoolRegisterComponent(ztEntityPool *pool, ztGuid guid, const char *name, void *user_data, ZT_FUNCTION_POINTER_VAR(component_make, ztComponentMake_Func), ZT_FUNCTION_POINTER_VAR(component_free, ztComponentFree_Func), ZT_FUNCTION_POINTER_VAR(component_find, ztComponentFind_Func), ZT_FUNCTION_POINTER_VAR(component_gui, ztComponentGui_Func), ZT_FUNCTION_POINTER_VAR(component_save, ztComponentSave_Func), ZT_FUNCTION_POINTER_VAR(component_load, ztComponentLoad_Func), ZT_FUNCTION_POINTER_VAR(component_update, ztComponentUpdate_Func), ztComponent **component_out)
{
	ZT_PROFILE_GAME("zt_entityPoolRegisterComponent");

	zt_returnValOnNull(pool, -1);
	zt_assertReturnValOnFail(pool->components_count < zt_elementsOf(pool->components), -1);

	int idx = pool->components_count++;

	pool->components[idx].guid = guid;
	zt_strCpy(pool->components[idx].name, zt_elementsOf(pool->components[idx].name), name);
	pool->components[idx].user_data = user_data;

	pool->components[idx].component_make                = component_make;
	pool->components[idx].component_free                = component_free;
	pool->components[idx].component_find                = component_find;
	pool->components[idx].component_gui                 = component_gui;
	pool->components[idx].component_save                = component_save;
	pool->components[idx].component_load                = component_load;
	pool->components[idx].component_update              = component_update;

	pool->components[idx].component_edit_query_click    = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	pool->components[idx].component_edit_process_click  = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	pool->components[idx].component_edit_draw_debug     = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	pool->components[idx].component_edit_draw_debug_all = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	pool->components[idx].component_notify_change       = ZT_FUNCTION_POINTER_TO_VAR_NULL;

	zt_assert(ZT_FUNCTION_POINTER_IS_VALID(component_make));
	zt_assert(ZT_FUNCTION_POINTER_IS_VALID(component_free));
	zt_assert(ZT_FUNCTION_POINTER_IS_VALID(component_find));
	zt_assert(ZT_FUNCTION_POINTER_IS_VALID(component_gui));
	zt_assert(ZT_FUNCTION_POINTER_IS_VALID(component_save));
	zt_assert(ZT_FUNCTION_POINTER_IS_VALID(component_load));

	if (component_out) {
		*component_out = &pool->components[idx];
	}

	return idx;
}

// ================================================================================================================================================================================================

i32 zt_entityPoolUnregisterComponent(ztEntityPool *pool, ztGuid guid)
{
	ZT_PROFILE_GAME("zt_entityPoolUnregisterComponent");

	zt_returnValOnNull(pool, -1);

	zt_fiz(pool->entities_count) {
		if (pool->entities[i].internal_id <= 0) {
			continue;
		}

		ztEntityID entity_id = zt_entityMakeID(i, pool->entities[i].internal_id);

		while (true) {
			bool removed_component = false;
			zt_flink(entry, pool->entities[i].components) {
				if (entry->component->guid == guid) {
					ZT_FUNCTION_POINTER_ACCESS(entry->component->component_free, ztComponentFree_Func)(pool, entity_id, entry->component, entry->component_id);
					removed_component = true;
					break;
				}
			}
			if (!removed_component) {
				break;
			}
		}
	}

	zt_fiz(pool->components_count) {
		if (pool->components[i].guid == guid) {
			zt_memSet(&pool->components[i], zt_sizeof(ztComponent), 0);
			return i;
		}
	}

	return -1;
}

// ================================================================================================================================================================================================

void zt_entityAddedComponent(ztEntityPool *pool, ztEntityID entity_id, ztGuid component_guid, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_entityAddedComponent");

	i32 index = zt_entityIndex(entity_id);
	i32 internal_id = zt_entityInternalID(entity_id);

	zt_assertReturnOnFail(index >= 0 && index < pool->entities_count);

	if (pool->entities[index].internal_id != internal_id) {
		zt_logCritical("Attempting to add component to expired entity");
		return;
	}

	zt_staticAssert(ZT_COMPONENTS_MAX % 32 == 0); // just make sure

	zt_fvz(comp_idx, pool->components_count) {
		if (pool->components[comp_idx].guid == component_guid) {

			bool found_entry = false;
			zt_fvz(entry_idx, pool->component_entries_count) {
				if (pool->component_entries[entry_idx].component == nullptr) {
					found_entry = true;
					ztComponentEntry *entry = &pool->component_entries[entry_idx];
					entry->component    = &pool->components[comp_idx];
					entry->component_id = component_id;
					entry->next         = nullptr;

					zt_singleLinkAddToEnd(pool->entities[index].components, entry);
					break;
				}
			}

			zt_assertReturnOnFail(found_entry);

			zt_flink(entry, pool->entities[index].components) {
				if (entry->component_id != component_id) {
					ZT_FUNCTION_POINTER_ACCESS_SAFE(entry->component->component_notify_change, ztComponentNotifyChange_Func)(pool, entry->component, &pool->entities[index], entity_id, entry->component_id);
				}
			}

			break;
		}
	}

	if (pool->editor) {
		zt_entityEditorNotifyNewComponent(pool->editor, entity_id, component_guid, component_id);
	}
}

// ================================================================================================================================================================================================

void zt_entityRemovedComponent(ztEntityPool *pool, ztEntityID entity_id, ztGuid component_guid, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_entityRemovedComponent");

	i32 index = zt_entityIndex(entity_id);
	i32 internal_id = zt_entityInternalID(entity_id);

	zt_assertReturnOnFail(index >= 0 && index < pool->entities_count);

	if (pool->entities[index].internal_id != internal_id) {
		zt_logCritical("Attempting to remove component from expired entity");
		return;
	}

	ztComponentEntry *prev = nullptr;
	zt_flink(entry, pool->entities[index].components) {
		if (entry->component->guid == component_guid && entry->component_id == component_id) {
			if (prev) {
				prev->next = entry->next;
			}
			else {
				pool->entities[index].components = entry->next;
			}

			entry->component    = nullptr;
			entry->component_id = ztInvalidID;
			entry->next         = nullptr;
			break;
		}
	}

	zt_flink(entry, pool->entities[index].components) {
		if (entry->component_id != component_id) {
			ZT_FUNCTION_POINTER_ACCESS_SAFE(entry->component->component_notify_change, ztComponentNotifyChange_Func)(pool, entry->component, &pool->entities[index], entity_id, component_id);
		}
	}
}

// ================================================================================================================================================================================================

void zt_entityRemoveComponent(ztEntityPool *pool, ztEntityID entity_id, ztGuid component_guid, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_entityRemoveComponent");

	zt_fiz(pool->components_count) {
		if (pool->components[i].guid == component_guid) {
			if (ZT_FUNCTION_POINTER_IS_VALID(pool->components[i].component_free)) {
				ZT_FUNCTION_POINTER_ACCESS(pool->components[i].component_free, ztComponentFree_Func)(pool, entity_id, &pool->components[i], component_id);

				if (pool->editor) {
					zt_entityEditorNotifyDeleteComponent(pool->editor, entity_id, component_guid, component_id);
				}
			}
			break;
		}
	}
}

// ================================================================================================================================================================================================

void zt_entityPoolUpdate(ztEntityPool *pool, r32 dt, ztCamera *camera, bool gui_input, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	ZT_PROFILE_GAME("zt_entityPoolUpdate");

	zt_fiz(pool->components_count) {
		ZT_FUNCTION_POINTER_ACCESS_SAFE(pool->components[i].component_update, ztComponentUpdate_Func)(pool, &pool->components[i], dt, camera, gui_input, input_this_frame, input_keys, input_controller, input_mouse);
	}
}

// ================================================================================================================================================================================================

//ztComponentID zt_entityPoolAddComponentToEntity(ztEntityPool *pool, ztGuid component_guid, ztEntityID entity_id)
//{
//	zt_returnValOnNull(pool, ztInvalidID);
//
//	zt_fiz(pool->components_count) {
//		if (pool->components[i].guid == component_guid) {
//			if (ZT_FUNCTION_POINTER_IS_VALID(pool->components[i].component_make)) {
//				ZT_FUNCTION_POINTER_ACCESS(pool->components[i].component_make, ztComponentMake_Func)(pool, entity_id, &pool->components[i]);
//			}
//		}
//	}
//
//	return ztInvalidID;
//}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztEntityEditorComponentInfo
{
	ztEntityEditor *editor;
	ztEntityID      entity_id;
	ztComponentID   component_id;
	ztGuid          component_guid;
};

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal void _zt_entityEditorUpdateEntityTree(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("_zt_entityEditorUpdateEntityTree");

	zt_fiz(editor->pool->entities_count) {
		if (editor->pool->entities[i].internal_id == 0) {
			if (editor->entity_nodes[i] != ztInvalidID) {
				zt_guiTreeRemoveNode(editor->editor_tree, editor->entity_nodes[i]);
			}
		}
		else {
			if (editor->entity_nodes[i] == ztInvalidID) {
				ztGuiTreeNodeID parent_id = editor->tree_node_scene;

				if (editor->pool->entities[i].parent != nullptr) {
					i32 index = _zt_entityFindIndex(editor->pool, editor->pool->entities[i].parent);
					if (index >= 0) {
						parent_id = editor->entity_nodes[index];
					}
				}

				ztEntityID entity_id = zt_entityMakeID(i, editor->pool->entities[i].internal_id);
				zt_strMakePrintf(entity_name, 512, "%s", editor->pool->entities[i].name);
				ztGuiTreeNodeID node_id = zt_guiTreeAppend(editor->editor_tree, entity_name, &editor->pool->entities[i], parent_id);
				editor->entity_nodes[i] = node_id;
			}
		}
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_entityEditorClearComponents(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("_zt_entityEditorClearComponents");

	if (editor == nullptr) {
		return;
	}

	zt_guiSizerRemoveAllItems(editor->editor_components_sizer);

	editor->entity_components_count = 0;
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_MENU_SELECTED(_zt_entityEditorButtonMenuComponent)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonMenuComponent");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	ztEntity* entity = (ztEntity*)zt_guiTreeGetNodeUserData(editor->editor_tree, editor->entity_active_node_id);
	ztEntityID entity_id = zt_entityMakeID(_zt_entityFindIndex(editor->pool, entity), entity->internal_id);

	ZT_FUNCTION_POINTER_ACCESS_SAFE(editor->pool->components[menu_item].component_make, ztComponentMake_Func)(editor->pool, entity_id, &editor->pool->components[menu_item]);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonNewComponent)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonNewComponent");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	ztGuiItem *popup = zt_guiMakeMenu(nullptr, ztGuiMenuBehaviorFlags_FreeOnClose);

	zt_fiz(editor->pool->components_count) {
		zt_guiMenuAppend(popup, editor->pool->components[i].name, i, editor);
	}

	zt_guiMenuSetCallback(popup, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonMenuComponent));

	zt_guiMenuPopupAtItem(popup, button, ztAlign_Top, zt_vec2(0, button->size.y));

}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonHideComponent)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonHideComponent");

	bool visible = !zt_guiItemIsVisible((ztGuiItem*)button->user_data);
	zt_guiItemShow((ztGuiItem*)button->user_data, visible);
	zt_guiItemSetLabel(button, visible ? "-" : "+");
	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_DIALOG_MESSAGE_CLOSED(_zt_entityEditorButtonRemoveComponentDialog)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonRemoveComponentDialog");

	if (option->id == 0) {
		ztEntityEditorComponentInfo *component_info = (ztEntityEditorComponentInfo *)user_data;

		zt_entityRemoveComponent(component_info->editor->pool, component_info->entity_id, component_info->component_guid, component_info->component_id);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonRemoveComponent)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonRemoveComponent");

	zt_guiDialogMessageBoxYesNo("Delete Component?", "Are you sure you want to delete this component?", ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonRemoveComponentDialog), user_data);
}

// ================================================================================================================================================================================================

ztInternal void _zt_entityEditorUpdateComponents(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("_zt_entityEditorUpdateComponents");

	r32 padding = zt_guiPadding();

	ztEntity* entity = (ztEntity*)zt_guiTreeGetNodeUserData(editor->editor_tree, editor->entity_active_node_id);
	if (entity == nullptr) {
		return;
	}

	ztEntityID entity_id = zt_entityMakeID(_zt_entityFindIndex(editor->pool, entity), entity->internal_id);

	// add entity info
	{
		ztGuiItem *panel = zt_guiMakePanel(editor->editor_components_sizer, ztGuiPanelBehaviorFlags_DrawBackground);
		zt_guiSizerAddItem(editor->editor_components_sizer, panel, 0, padding, ztAlign_Left);

		ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert, false);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		i32 index = zt_entityIndex(entity_id);
		zt_strMakePrintf(entity_info, 512, "Entity: %s\n\nID: %lld     Index: %d     internal_id: %d", entity->name, entity_id, index, entity->internal_id);

		ztGuiItem *info = zt_guiMakeStaticText(sizer, entity_info);
		zt_guiItemSetAlign(info, ztAlign_Left);
		zt_guiSizerAddItem(sizer, info, 0, padding * 2, ztAlign_Left, 0);

		panel->min_size = zt_guiSizerGetMinSize(sizer);
		panel->min_size.x = 0;
	}

	zt_fvz(comp_idx, editor->pool->components_count) {
		ztComponentID component_id = ZT_FUNCTION_POINTER_ACCESS(editor->pool->components[comp_idx].component_find, ztComponentFind_Func)(&editor->pool->components[comp_idx], entity, entity_id, ztInvalidID);
		while (component_id != ztInvalidID) {
			if (editor->entity_components_count >= ZT_COMPONENTS_MAX_PER_ENTITY) {
				zt_assert(editor->entity_components_count < ZT_COMPONENTS_MAX_PER_ENTITY);
			}
			else {
				int entity_idx = editor->entity_components_count++;
				editor->entity_components[entity_idx] = &editor->pool->components[comp_idx];
				editor->entity_components_id[entity_idx] = component_id;

				ztEntityEditorComponentInfo *component_info = zt_mallocStructArena(ztEntityEditorComponentInfo, editor->editor_components_sizer->gm->arena);
				component_info->editor         = editor;
				component_info->entity_id      = entity_id;
				component_info->component_guid = editor->pool->components[comp_idx].guid;
				component_info->component_id   = component_id;

				ztGuiItem *panel = zt_guiMakePanel(editor->editor_components_sizer, ztGuiPanelBehaviorFlags_DrawBackground, component_info, editor->editor_components_sizer->gm->arena);
				ztGuiItem *panel_sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert, false);
				zt_guiSizerSizeParent(panel_sizer, false, true);
				zt_guiSizerSizeToParent(panel_sizer, true);

				zt_guiItemSetName(panel, editor->pool->components[comp_idx].name);

				ztGuiItem *panel_title_sizer = zt_guiMakeSizer(panel_sizer, ztGuiItemOrient_Horz, true);
				zt_guiSizerAddItem(panel_sizer, panel_title_sizer, 0, padding);

				ztGuiItem *panel_button_hide = zt_guiMakeButton(panel_sizer, "-");
				panel_button_hide->size.y *= .75f;
				panel_button_hide->size.x = panel_button_hide->size.y;
				zt_guiButtonSetCallback(panel_button_hide, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonHideComponent), editor);
				zt_guiSizerAddItem(panel_title_sizer, panel_button_hide, 0, padding);


				ztGuiItem *panel_label = zt_guiMakeStaticText(panel_sizer, editor->pool->components[comp_idx].name);
				zt_guiItemSetAlign(panel_sizer, ztAlign_Left | ztAlign_VertCenter);
				zt_guiSizerAddItem(panel_title_sizer, panel_label, 1, padding, ztAlign_Left, 0);

				zt_strMakePrintf(comp_id_str, 64, "<color=777777>[%d]", component_id);
				ztGuiItem *panel_comp_id = zt_guiMakeStaticText(panel_sizer, comp_id_str, ztGuiStaticTextBehaviorFlags_Fancy);
				zt_guiItemSetAlign(panel_sizer, ztAlign_Right | ztAlign_VertCenter);
				zt_guiSizerAddItem(panel_title_sizer, panel_comp_id, 0, padding, ztAlign_Right, 0);

				ztGuiItem *panel_button_delete = zt_guiMakeToggleButton(panel_sizer, "del");
				panel_button_delete->size.y *= .75f;
				panel_button_delete->size.x = panel_button_delete->size.y * 2;
				zt_guiButtonSetCallback(panel_button_delete, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonRemoveComponent), component_info);
				zt_guiSizerAddItem(panel_title_sizer, panel_button_delete, 0, padding);

				editor->entity_components_gui[entity_idx] = ZT_FUNCTION_POINTER_ACCESS(editor->pool->components[comp_idx].component_gui, ztComponentGui_Func)(&editor->pool->components[comp_idx], component_id, panel_sizer);
				zt_guiItemSetName(editor->entity_components_gui[entity_idx], "Comp Gui Panel");

				zt_guiSizerAddItem(panel_sizer, editor->entity_components_gui[entity_idx], 1, padding);

				zt_guiSizerAddItem(editor->editor_components_sizer, panel, 0, padding);

				panel_button_hide->user_data = editor->entity_components_gui[entity_idx];
				panel_button_delete->custom_flags = component_id;
				panel_button_delete->user_data = editor;
			}

			component_id = ZT_FUNCTION_POINTER_ACCESS(editor->pool->components[comp_idx].component_find, ztComponentFind_Func)(&editor->pool->components[comp_idx], entity, entity_id, component_id);
		}
	}

	ztGuiItem *button_sizer = zt_guiMakeSizer(editor->editor_components_sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(editor->editor_components_sizer, button_sizer, 0, 0);

	ztGuiItem *button_new_component = zt_guiMakeButton(button_sizer, "New Component");
	zt_guiSizerAddItem(button_sizer, button_new_component, 0, 0);
	zt_guiButtonSetCallback(button_new_component, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonNewComponent), editor);

	zt_guiSizerRecalc(editor->editor_components_sizer);
}

// ================================================================================================================================================================================================

ztInternal void _zt_entityEditorNewScene(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("_zt_entityEditorNewScene");

	zt_fiz(editor->pool->entities_count) {
		zt_entityPoolFreeEntity(editor->pool, zt_entityMakeID(i, editor->pool->entities[i].internal_id));
	}

	editor->pool->entities_count = 0;
	editor->pool->last_id = 0;
	editor->file_path[0] = 0;

	_zt_entityEditorClearComponents(editor);

	zt_guiTreeClear(editor->editor_tree);
	editor->tree_node_scene = zt_guiTreeAppend(editor->editor_tree, "Scene", nullptr);
}

// ================================================================================================================================================================================================

ztInternal void _zt_entityEditorSaveScene(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("_zt_entityEditorSaveScene");

	zt_entityPoolSave(editor->pool, editor->file_path, ZT_FUNCTION_POINTER_ACCESS(editor->serial_extra_save, ztEntitySerialExtraSave_Func), editor->serial_extra_user_data);

	zt_bitRemove(editor->state_flags, ztEntityEditorStateFlags_HasUnsavedChanges);
}

// ================================================================================================================================================================================================

ztInternal bool _zt_entityEditorLoadScene(ztEntityEditor *editor, const char *file_name)
{
	ZT_PROFILE_GUI("_zt_entityEditorLoadScene");

	_zt_entityEditorNewScene(editor);

	zt_strCpy(editor->file_path, zt_elementsOf(editor->file_path), file_name);

	if (!zt_entityPoolLoad(editor->pool, editor->file_path, ZT_FUNCTION_POINTER_ACCESS(editor->serial_extra_load, ztEntitySerialExtraLoad_Func), editor->serial_extra_user_data)) {
		return false;
	}

	_zt_entityEditorUpdateEntityTree(editor);

	zt_bitRemove(editor->state_flags, ztEntityEditorStateFlags_HasUnsavedChanges);

	return true;
}

// ================================================================================================================================================================================================

bool zt_entityEditorHasUnsavedChanges(ztEntityEditor *editor)
{
	return editor && zt_bitIsSet(editor->state_flags, ztEntityEditorStateFlags_HasUnsavedChanges);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_DIALOG_MESSAGE_CLOSED(_zt_entityEditorButtonNewSceneUnsavedChangedDialog)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonNewSceneUnsavedChangedDialog");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	if (option->id == 0) {
		_zt_entityEditorNewScene(editor);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonNewScene)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonNewScene");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	if (zt_bitIsSet(editor->state_flags, ztEntityEditorStateFlags_HasUnsavedChanges)) {
		zt_guiDialogMessageBoxYesNo("Unsaved Changes", "There are unsaved changes to this scene.  Continue and lose changes?", ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonNewSceneUnsavedChangedDialog), editor);
	}
	else {
		_zt_entityEditorNewScene(editor);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_entityEditorLoadSceneFileSelected)
{
	ZT_PROFILE_GUI("_zt_entityEditorLoadSceneFileSelected");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	if (!_zt_entityEditorLoadScene(editor, path)) {
		zt_guiDialogMessageBoxOk("Error Loading Scene", "There was an error loading the scene.");
		_zt_entityEditorNewScene(editor);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonLoadScene)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonLoadScene");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;
	zt_guiDialogFileSelect("Choose File", ztGuiDialogFileSelectFlags_Open, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorLoadSceneFileSelected), editor);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_entityEditorSaveSceneFileSelected)
{
	ZT_PROFILE_GUI("_zt_entityEditorSaveSceneFileSelected");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;
	zt_strCpy(editor->file_path, zt_elementsOf(editor->file_path), path);
	_zt_entityEditorSaveScene(editor);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonSaveScene)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonSaveScene");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	if (editor->file_path[0] == 0) {
		zt_guiDialogFileSelect("Choose Save Location", ztGuiDialogFileSelectFlags_Save, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorSaveSceneFileSelected), editor);
	}
	else {
		_zt_entityEditorSaveScene(editor);
	}	
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_DIALOG_GET_USER_TEXT(_zt_entityEditorButtonNewEntityGetName)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonNewEntityGetName");

	if (cancelled) {
		return;
	}

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	ztEntityID parent_id = ztInvalidID;

	ztGuiTreeNodeID active_node_id = zt_guiTreeGetSelected(editor->editor_tree);
	if (active_node_id != ztInvalidID) {
		zt_fiz(editor->pool->entities_count) {
			if (editor->entity_nodes[i] == active_node_id) {
				parent_id = zt_entityMakeID(i, editor->pool->entities[i].internal_id);
				break;
			}
		}
	}

	ztEntityID entity = zt_entityPoolMakeEntity(editor->pool, value, parent_id);
	_zt_entityEditorUpdateEntityTree(editor);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonNewEntity)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonNewEntity");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;
	zt_guiDialogGetUserText("Create New Entity", "Entity Name:", "", true, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonNewEntityGetName), editor);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_entityEditorButtonDelEntity)
{
	ZT_PROFILE_GUI("_zt_entityEditorButtonDelEntity");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;

	if (editor->entity_active_node_id != ztInvalidID) {
		ztEntity *entity = (ztEntity*)zt_guiTreeGetNodeUserData(editor->editor_tree, editor->entity_active_node_id);

		i32 index = _zt_entityFindIndex(editor->pool, entity);
		ztEntityID entity_id = zt_entityMakeID(index, entity->internal_id);

		zt_entityPoolFreeEntity(editor->pool, entity_id);

		zt_guiTreeRemoveNode(editor->editor_tree, editor->entity_active_node_id);
		editor->entity_active_node_id = ztInvalidID;
		editor->entity_nodes[index] = ztInvalidID;

		_zt_entityEditorUpdateEntityTree(editor);
		_zt_entityEditorClearComponents(editor);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_TREE_ITEM_SELECTED(_zt_entityEditorTreeItemSelected)
{
	ZT_PROFILE_GUI("_zt_entityEditorTreeItemSelected");

	ztEntityEditor *editor = (ztEntityEditor*)user_data;
	if (node_id != editor->tree_node_scene) {
		if (editor->entity_active_node_id != ztInvalidID && editor->entity_active_node_id != node_id) {
			_zt_entityEditorClearComponents(editor);
		}

		if (editor->entity_active_node_id != node_id) {
			editor->entity_active_node_id = node_id;
			_zt_entityEditorUpdateComponents(editor);
		}
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_entityEditorMake(ztEntityEditor *editor, ztEntityPool *pool, i32 max_items)
{
	ZT_PROFILE_GUI("zt_entityEditorMake");

	zt_returnValOnNull(editor, false);
	zt_returnValOnNull(pool, false);

	editor->state_flags = 0;
	editor->pool = pool;
	editor->pool->editor = editor;
	editor->entity_active_node_id = ztInvalidID;
	editor->serial_extra_save = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	editor->serial_extra_load = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	editor->serial_extra_user_data = nullptr;

	editor->entity_nodes = zt_mallocStructArray(ztGuiTreeNodeID, editor->pool->entities_size);

	zt_fiz(editor->pool->entities_size) {
		editor->entity_nodes[i] = ztInvalidID;
	}

	ztGuiItem *editor_win = zt_guiMakeWindow("Entity Editor", ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_AllowCollapse | ztGuiWindowBehaviorFlags_ShowTitle);
	editor->editor_win = editor_win;

	ztVec2 cam_ext = zt_cameraOrthoGetViewportSize(editor_win->gm->gui_camera);
	r32 padding = zt_guiPadding();

	zt_guiItemSetSize(editor_win, zt_vec2(8, cam_ext.y - .75f));
	zt_guiItemSetPosition(editor_win, ztAlign_Left | ztAlign_Top, ztAnchor_Left|ztAnchor_Top, zt_vec2(.25f, -.5f), true);

	ztGuiItem *editor_sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(editor_win), ztGuiItemOrient_Vert);

	ztGuiItem *editor_splitter = zt_guiMakeSplitter(editor_sizer, ztGuiItemOrient_Vert, .25f);
	zt_guiSizerAddItem(editor_sizer, editor_splitter, 1, padding);


	{
		ztGuiItem *editor_tree_panel = zt_guiMakePanel(editor_sizer);

		ztGuiItem *editor_tree_sizer = zt_guiMakeSizer(editor_tree_panel, ztGuiItemOrient_Vert);

		{
			ztGuiItem *button_sizer = zt_guiMakeSizer(editor_tree_sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(editor_tree_sizer, button_sizer, 0, 0);

			ztGuiItem *button_new_scene = zt_guiMakeButton(button_sizer, "New Scene");
			ztGuiItem *button_lod_scene = zt_guiMakeButton(button_sizer, "Load Scene");
			ztGuiItem *button_sav_scene = zt_guiMakeButton(button_sizer, "Save Scene");
			zt_guiSizerAddItem(button_sizer, button_new_scene, 0, 0);
			zt_guiSizerAddItem(button_sizer, button_lod_scene, 0, 0);
			zt_guiSizerAddItem(button_sizer, button_sav_scene, 0, 0);
			zt_guiButtonSetCallback(button_new_scene, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonNewScene), editor);
			zt_guiButtonSetCallback(button_lod_scene, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonLoadScene), editor);
			zt_guiButtonSetCallback(button_sav_scene, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonSaveScene), editor);
		}

		ztGuiItem *editor_tree = zt_guiMakeTree(editor_sizer, max_items);
		editor->editor_tree = editor_tree;
		zt_guiTreeSetCallback(editor_tree, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorTreeItemSelected), editor);
		zt_guiSizerAddItem(editor_tree_sizer, editor_tree, 1, padding);

		{
			ztGuiItem *button_sizer = zt_guiMakeSizer(editor_tree_sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(editor_tree_sizer, button_sizer, 0, 0);

			ztGuiItem *button_new_entity = zt_guiMakeButton(button_sizer, "New Entity");
			ztGuiItem *button_del_entity = zt_guiMakeButton(button_sizer, "Del Entity");
			zt_guiSizerAddItem(button_sizer, button_new_entity, 0, 0);
			zt_guiSizerAddItem(button_sizer, button_del_entity, 0, 0);
			zt_guiButtonSetCallback(button_new_entity, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonNewEntity), editor);
			zt_guiButtonSetCallback(button_del_entity, ZT_FUNCTION_POINTER_TO_VAR(_zt_entityEditorButtonDelEntity), editor);
		}

		zt_guiSplitterSetFirstItem(editor_splitter, editor_tree_panel);
	}

	{
		ztGuiItem *scroll_panel = zt_guiMakePanel(editor_sizer);
		zt_guiSplitterSetSecondItem(editor_splitter, scroll_panel);

		ztGuiItem *scroll_sizer = zt_guiMakeSizer(scroll_panel, ztGuiItemOrient_Vert);

		ztGuiItem *editor_scroll = zt_guiMakeScrollContainer(scroll_sizer, ztGuiScrollContainerBehaviorFlags_StretchHorz);
		zt_guiSizerAddItem(scroll_sizer, editor_scroll, 1, padding);

		ztGuiItem *editor_scroll_panel = zt_guiMakePanel(editor_scroll);
		zt_guiScrollContainerSetItem(editor_scroll, editor_scroll_panel);

		ztGuiItem *editor_scroll_sizer = zt_guiMakeSizer(editor_scroll_panel, ztGuiItemOrient_Vert, false);
		zt_guiSizerSizeParent(editor_scroll_sizer, false, true);
		zt_guiSizerSizeToParent(editor_scroll_sizer);

		editor->editor_components_sizer = editor_scroll_sizer;
	}

	_zt_entityEditorNewScene(editor);
	_zt_entityEditorUpdateEntityTree(editor);

	return true;
}

// ================================================================================================================================================================================================

void zt_entityEditorFree(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("zt_entityEditorFree");

	if (editor == nullptr || editor->pool == nullptr) {
		return;
	}

	zt_guiItemFree(editor->editor_win);
	editor->pool->editor = nullptr;

	zt_free(editor->entity_nodes);

	zt_memSet(editor, zt_sizeof(ztEntityEditor), 0);
}

// ================================================================================================================================================================================================

bool zt_entityEditorLoad(ztEntityEditor *editor, const char *file_name)
{
	ZT_PROFILE_GUI("zt_entityEditorLoad");

	if (!_zt_entityEditorLoadScene(editor, file_name)) {
		zt_guiDialogMessageBoxOk("Error Loading Scene", "There was an error loading the default scene.");
		_zt_entityEditorNewScene(editor);
		return false;
	}

	return true;
}

// ================================================================================================================================================================================================

void zt_entityEditorUpdate(ztEntityEditor *editor, r32 dt, ztCamera *camera, bool gui_input, bool input_this_frame, ztInputKeys *input_keys, ztInputController *input_controller, ztInputMouse *input_mouse)
{
	ZT_PROFILE_GUI("zt_entityEditorUpdate");

	if (!gui_input) {
		if (input_mouse->leftJustPressed()) {
			i32 closest_id = -1;
			r32 closest_dist = ztReal32Max;
			i32 closest_comp_idx = -1;

			ztVec3 ray_pos, ray_dir;
			zt_cameraPerspGetMouseRay(camera, input_mouse->screen_x, input_mouse->screen_y, &ray_pos, &ray_dir);

			zt_fiz(editor->pool->components_count) {
				if (ZT_FUNCTION_POINTER_IS_VALID(editor->pool->components[i].component_edit_query_click)) {
					i32 this_closest_id = -1;
					r32 this_closest_dist = ztReal32Max;
					if (ZT_FUNCTION_POINTER_ACCESS(editor->pool->components[i].component_edit_query_click, ztComponentEditQueryClick_Func)(editor->pool, camera, &editor->pool->components[i], ray_pos, ray_dir, &this_closest_id, &this_closest_dist, input_mouse, input_keys)) {
						if (this_closest_dist < closest_dist) {
							closest_dist     = this_closest_dist;
							closest_id       = this_closest_id;
							closest_comp_idx = i;
						}
					}
				}
			}

			if (closest_comp_idx != -1) {
				ztComponent *component = &editor->pool->components[closest_comp_idx];
				ZT_FUNCTION_POINTER_ACCESS_SAFE(component->component_edit_process_click, ztComponentEditProcessClick_Func)(editor->pool, camera, component, ray_pos, ray_dir, closest_id, input_mouse, input_keys);
			}
		}
	}
}

// ================================================================================================================================================================================================

void zt_entityEditorRender(ztEntityEditor *editor, ztCamera *camera, ztDrawList *draw_list)
{
	ZT_PROFILE_GUI("zt_entityEditorRender");

	ztEntity *entity = nullptr;
	ztEntityID entity_id = ztInvalidID;

	if (editor->entity_active_node_id != ztInvalidID) {
		entity = (ztEntity*)zt_guiTreeGetNodeUserData(editor->editor_tree, editor->entity_active_node_id);
		if (entity == nullptr) {
			return;
		}

		i32 entity_idx = _zt_entityFindIndex(editor->pool, entity);
		entity_id = zt_entityMakeID(entity_idx, entity->internal_id);

		zt_flink(component, entity->components) {
			ZT_FUNCTION_POINTER_ACCESS_SAFE(component->component->component_edit_draw_debug, ztComponentEditDrawDebug_Func)(component->component, camera, draw_list, entity_id, component->component_id);
		}
	}

	zt_fiz(editor->pool->components_count) {
		ZT_FUNCTION_POINTER_ACCESS_SAFE(editor->pool->components[i].component_edit_draw_debug_all, ztComponentEditDrawDebugAll_Func)(&editor->pool->components[i], camera, draw_list, entity_id, ztInvalidID);
	}
}

// ================================================================================================================================================================================================

void zt_entityEditorMakeEntityActive(ztEntityEditor *editor, ztEntityID entity_id)
{
	ZT_PROFILE_GUI("zt_entityEditorMakeEntityActive");

	i32 internal_id = zt_entityInternalID(entity_id);

	ztEntity *entity = _zt_entityFind(editor->pool, internal_id);
	if (entity == nullptr) {
		zt_logCritical("Unable to locate entity_id: %lld", entity_id);
		return;
	}

	ztGuiTreeNodeID node_id = zt_guiTreeFindNodeWithUserDataOf(editor->editor_tree, entity);
	if (node_id == ztInvalidID) {
		zt_logCritical("Unable to locate node_id for entity_id: %lld", entity_id);
		return;
	}

	zt_guiTreeSetSelected(editor->editor_tree, node_id);

	if (editor->entity_active_node_id != ztInvalidID && editor->entity_active_node_id != node_id) {
		_zt_entityEditorClearComponents(editor);
	}

	if (editor->entity_active_node_id != node_id) {
		editor->entity_active_node_id = node_id;
		_zt_entityEditorUpdateComponents(editor);
	}
}

// ================================================================================================================================================================================================

ztEntityID zt_entityEditorGetActiveEntity(ztEntityEditor *editor)
{
	ZT_PROFILE_GUI("zt_entityEditorGetActiveEntity");

	ztEntity *entity = (ztEntity*)zt_guiTreeGetNodeUserData(editor->editor_tree, editor->entity_active_node_id);
	i32 index = _zt_entityFindIndex(editor->pool, entity);
	if (index < 0) {
		return ztInvalidID;
	}

	return zt_entityMakeID(index, entity->internal_id);
}

// ================================================================================================================================================================================================

void zt_entityEditorNotifyNewEntity(ztEntityEditor *editor, ztEntityID entity)
{
	ZT_PROFILE_GUI("zt_entityEditorNotifyNewEntity");

	_zt_entityEditorUpdateEntityTree(editor);
	_zt_entityEditorClearComponents(editor);
	_zt_entityEditorUpdateComponents(editor);
	editor->state_flags |= ztEntityEditorStateFlags_HasUnsavedChanges;
}

// ================================================================================================================================================================================================

void zt_entityEditorNotifyNewComponent(ztEntityEditor *editor, ztEntityID entity, ztGuid component_guid, ztComponentID component_id)
{
	ZT_PROFILE_GUI("zt_entityEditorNotifyNewComponent");

	_zt_entityEditorClearComponents(editor);
	_zt_entityEditorUpdateComponents(editor);

	editor->state_flags |= ztEntityEditorStateFlags_HasUnsavedChanges;
}

// ================================================================================================================================================================================================

void zt_entityEditorNotifyDeleteComponent(ztEntityEditor *editor, ztEntityID entity, ztGuid component_guid, ztComponentID component_id)
{
	ZT_PROFILE_GUI("zt_entityEditorNotifyDeleteComponent");

	_zt_entityEditorClearComponents(editor);
	_zt_entityEditorUpdateComponents(editor);

	editor->state_flags |= ztEntityEditorStateFlags_HasUnsavedChanges;
}

// ================================================================================================================================================================================================

void zt_entityEditorNotifyChangedComponent(ztEntityEditor *editor, ztEntityID entity, ztGuid component_guid, ztComponentID component_id)
{
	ZT_PROFILE_GUI("zt_entityEditorNotifyChangedComponent");

	editor->state_flags |= ztEntityEditorStateFlags_HasUnsavedChanges;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_componentGuiMakeItem(ztGuiItem *sizer, const char *name, ztGuiItem *editor)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeItem");

	r32 padding = 6 / zt_pixelsPerUnit();

	ztGuiItem *label = zt_guiMakeStaticText(sizer, name);
	zt_guiItemSetAlign(label, ztAlign_Right | ztAlign_VertCenter);
	zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);

	zt_guiSizerAddItem(sizer, editor, 0, padding, ztAlign_Left | ztAlign_VertCenter);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeStaticText(ztGuiItem *sizer, const char *name, const char *text)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeStaticText");

	ztGuiItem *label = zt_guiMakeStaticText(sizer, text);
	zt_guiItemSetAlign(label, ztAlign_Left | ztAlign_VertCenter);
	zt_componentGuiMakeItem(sizer, name, label);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeEditor(ztGuiItem *sizer, const char *name, ztTransform *transform, r32 pos_step = 1.f, r32 rot_step = 1.f, r32 sca_step = 1.f)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeEditor");

	ztGuiItem *transform_pos = zt_guiMakeEditor(sizer, nullptr, &transform->position, ztVec3::min, ztVec3::max, pos_step, false);
	zt_componentGuiMakeItem(sizer, "Position:", transform_pos);

	ztGuiItem *transform_rot = zt_guiMakeEditor(sizer, nullptr, &transform->rotation, ztVec3::min, ztVec3::max, rot_step, false);
	zt_componentGuiMakeItem(sizer, "Rotation:", transform_rot);

	ztGuiItem *transform_sca = zt_guiMakeEditor(sizer, nullptr, &transform->scale, ztVec3::min, ztVec3::max, sca_step, false);
	zt_componentGuiMakeItem(sizer, "Scale:", transform_sca);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeEditor(ztGuiItem *sizer, const char *name, ztVec3 *value, r32 step = .25f)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeEditor");

	ztGuiItem *value_ed = zt_guiMakeEditor(sizer, nullptr, value, ztVec3::min, ztVec3::max, step, false);
	zt_componentGuiMakeItem(sizer, name, value_ed);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeEditor(ztGuiItem *sizer, const char *name, r32 *value, r32 step = .25f)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeEditor");

	ztGuiItem *value_ed = zt_guiMakeEditor(sizer, nullptr, value, ztReal32Min, ztReal32Max, step);
	zt_componentGuiMakeItem(sizer, name, value_ed);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeEditor(ztGuiItem *sizer, const char *name, bool *value)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeEditor");

	ztGuiItem *value_ed = zt_guiMakeCheckbox(sizer, nullptr, ztGuiCheckboxBehaviorFlags_RightText, value);
	zt_componentGuiMakeItem(sizer, name, value_ed);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeEditor(ztGuiItem *sizer, const char *name, ztColor *value)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeEditor");

	ztGuiItem *value_ed = zt_guiMakeColorPicker(sizer, *value, ztGuiColorPickerBehaviorFlags_LiveEdit, value);
	zt_componentGuiMakeItem(sizer, name, value_ed);
}

// ================================================================================================================================================================================================

void zt_componentGuiMakeFlagsEditor(ztGuiItem *sizer, const char *name, const char **flags_names, i32 *flags, int flags_count, i32 *flags_var, int columns)
{
	ZT_PROFILE_GUI("zt_componentGuiMakeFlagsEditor");

	ztGuiItem *edit_flags = zt_guiMakeFlagEditor(sizer, flags_names, flags, flags_count, flags_var, columns);
	zt_componentGuiMakeItem(sizer, name, edit_flags);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_MODEL_COMPONENT_GUID       zt_guidMake(0xe74abd50, 0xc515439c, 0x932aaf3a, 0x8ae8eb12)
#define ZT_MODEL_COMPONENT_NAME       "Model"

enum ztModelComponentBoneFlags_Enum
{
	ztModelComponentBoneFlags_InUse = (1 << 31),
};


// ================================================================================================================================================================================================

struct ztModelComponentMakeParams
{
	ztEntityPool     *pool;
	ztEntityID        entity_id;
	ztComponent      *component;
	ztModelComponent *model_component;
	ztGuiItem        *listbox;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_modelComponentMakeAdd)
{
	ZT_PROFILE_GAME("_zt_modelComponentMakeAdd");

	ztModelComponentMakeParams *params = (ztModelComponentMakeParams*)user_data;

	int selected = zt_guiListBoxGetSelected(params->listbox);

	zt_assertReturnOnFail(selected >= 0 && selected < params->model_component->options_models_size);

	ztComponentID component_id = zt_modelComponentAdd(params->model_component, params->pool, params->entity_id, params->model_component->options_models[selected].guid);

	if (component_id != ztInvalidID) {
		ztModel *model = params->model_component->models[component_id];
		zt_logDebug("Added model: %s; component_id: %d; entity_id: %lld; model: 0x%08x", model->name, component_id, params->entity_id, model);
	}

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_modelComponentMakeCancel)
{
	ZT_PROFILE_GAME("_zt_modelComponentMakeCancel");

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_modelComponentMake)
{
	ZT_PROFILE_GAME("_zt_modelComponentMake");

	ztModelComponent *model_component = (ztModelComponent*)component->user_data;

	// this needs to open a dialog to allow the user to select one of the valid models

	ztGuiItem *window = zt_guiMakeWindow("Select Model", ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_Modal | ztGuiWindowBehaviorFlags_ShowTitle);
	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	r32 padding = zt_guiPadding();

	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Choose a model:"), 0, padding);

	ztGuiItem *listbox = zt_guiMakeListBox(sizer, 0, model_component->options_models_size);
	zt_fiz(model_component->options_models_size) {
		zt_guiListBoxAppend(listbox, model_component->options_models[i].name, &model_component->options_models[i].guid);
	}

	zt_guiSizerAddItem(sizer, listbox, 1, padding);

	ztGuiItem *button_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, button_sizer, 0, 0);

	ztGuiItem *button_ok = zt_guiMakeButton(button_sizer, "OK");
	ztGuiItem *button_no = zt_guiMakeButton(button_sizer, "Cancel");

	button_ok->size = button_no->size;

	zt_guiSizerAddStretcher(button_sizer, 1);
	zt_guiSizerAddItem(button_sizer, button_ok, 0, padding);
	zt_guiSizerAddItem(button_sizer, button_no, 0, padding);

	ztModelComponentMakeParams *params = zt_mallocStructArena(ztModelComponentMakeParams, window->gm->arena);
	ztGuiItem *params_cleanup = zt_guiMakePanel(window, 0, params, window->gm->arena);

	zt_guiButtonSetCallback(button_ok, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentMakeAdd), params);
	zt_guiButtonSetCallback(button_no, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentMakeCancel), nullptr);

	params->pool = pool;
	params->entity_id = entity_id;
	params->component = component;
	params->model_component = model_component;
	params->listbox = listbox;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_modelComponentFree)
{
	ZT_PROFILE_GAME("_zt_modelComponentFree");

	ztModelComponent *model_component = (ztModelComponent*)component->user_data;

	zt_modelComponentRemove(model_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_modelComponentFind)
{
	ZT_PROFILE_GAME("_zt_modelComponentFind");

	ztModelComponent *model_component = (ztModelComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(model_component->models_count) {
		if (model_component->entity_ids[i] == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztModelComponentGuiInfo
{
	ztModelComponent *model_component;
	ztComponentID     component_id;
	ztModel          *model;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_modelComponentGuiComboAnimation)
{
	ZT_PROFILE_GAME("_zt_modelComponentGuiComboMaterial");

	ztModelComponentGuiInfo *gui_info = (ztModelComponentGuiInfo *)user_data;

	if (gui_info->model->anim_controller) {
		char label[128] = { 0 };
		zt_guiComboBoxGetItemText(combobox, selected, label, zt_elementsOf(label));
		zt_animControllerStartSequence(gui_info->model->anim_controller, zt_strHash(label), .1f);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_modelComponentGuiComboMaterial)
{
	ZT_PROFILE_GAME("_zt_modelComponentGuiComboMaterial");

	ztModelComponentGuiInfo *gui_info = (ztModelComponentGuiInfo *)user_data;

	if (selected == 0) {
		gui_info->model->material = zt_materialMake();
	}
	else {
		gui_info->model->material = gui_info->model_component->options_materials[selected - 1].material;
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_modelComponentGuiComboShader)
{
	ZT_PROFILE_GAME("_zt_modelComponentGuiComboShader");

	ztModelComponentGuiInfo *gui_info = (ztModelComponentGuiInfo *)user_data;

	if (selected == 0) {
		gui_info->model->shader = gui_info->model_component->default_shader;
	}
	else {
		gui_info->model->shader = gui_info->model_component->options_shaders[selected - 1].shader;
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_MENU_SELECTED(_zt_modelComponentGuiLayersMenu)
{
	ZT_PROFILE_GUI("_zt_modelComponentGuiLayersMenu");

	ztModelComponent *model_component = (ztModelComponent*)user_data;

	if (menu_item == -1) {
		model_component->edit_show_layers_mask = 0;
		return;
	}

	if (zt_bitIsSet(model_component->edit_show_layers_mask, zt_bit(menu_item))) {
		zt_bitRemove(model_component->edit_show_layers_mask, zt_bit(menu_item));
	}
	else {
		model_component->edit_show_layers_mask |= zt_bit(menu_item);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_modelComponentGuiLayersButton)
{
	ZT_PROFILE_GUI("_zt_modelComponentGuiLayersButton");

	ztModelComponent *model_component = (ztModelComponent*)user_data;

	ztGuiItem *menu = zt_guiMakeMenu(button, ztGuiMenuBehaviorFlags_FreeOnClose);

	zt_guiMenuAppend(menu, "Show All Layers", -1, model_component);
	zt_guiMenuAppendSeparator(menu);

	zt_fiz(model_component->options_layers_size) {
		zt_strMakePrintf(layer_name, 256, "<color=%s>%s", zt_bitIsSet(model_component->edit_show_layers_mask, zt_bit(i)) ? "FFFFFF" : "999999", model_component->options_layers[i]);
		zt_guiMenuAppend(menu, layer_name, i, model_component);
	}

	zt_guiMenuSetCallback(menu, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentGuiLayersMenu));

	zt_guiMenuPopupAtItem(menu, button, ztAlign_Bottom);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_modelComponentGui)
{
	ZT_PROFILE_GUI("_zt_modelComponentGui");

	//ztComponent *component, ztComponentID component_id, ztGuiItem *parent
	ztModelComponent *model_component = (ztModelComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < model_component->models_count, nullptr);

	r32 padding = zt_guiPadding();

	ztModel *model = model_component->models[component_id];

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow, false);
	zt_guiSizerSizeParent(sizer, false, true);
	zt_guiSizerSizeToParent(sizer);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztModelComponentGuiInfo *gui_info = zt_mallocStructArena(ztModelComponentGuiInfo, sizer->gm->arena);
	gui_info->model_component = model_component;
	gui_info->component_id = component_id;
	gui_info->model = model;

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	zt_componentGuiMakeStaticText(sizer, "Model:", model->name);

	if (model->type >= ztModelType_Invalid && model->type < ztModelType_MAX) {
		const char *types[ztModelType_MAX] = { "Invalid", "Empty", "Mesh", "VertexArray", "Sprite", "SpriteAnimation", "ParticleSystem" };

		i32 vert_count = zt_modelGetVertices(model, nullptr, 0, ztModelGetVerticesTransform_NoTransform);

		if (vert_count > 0) {
			zt_strMakePrintf(model_info, 256, "Type: %s     (%d tris)", types[model->type], zt_convertToi32Floor(vert_count / 3.f));
			zt_componentGuiMakeStaticText(sizer, "Type:", model_info);
		}
		else {
			zt_componentGuiMakeStaticText(sizer, "Type:", types[model->type]);
		}
	}

	zt_componentGuiMakeEditor(sizer, "", &model->transform);

	{
		const char *flags_names[] = {
			"No Face Culling",
			"Translucent",
			"Casts Shadows",
			"Shadows Only",
			"Hidden",
		};

		i32 flags[] = {
			ztModelFlags_NoFaceCull,
			ztModelFlags_Translucent,
			ztModelFlags_CastsShadows,
			ztModelFlags_ShadowOnly,
			ztModelFlags_Hidden,
		};

		zt_componentGuiMakeFlagsEditor(sizer, "Flags:", flags_names, flags, zt_elementsOf(flags_names), &model->flags, 2);
	}

	if (model_component->options_layers_size > 0) {
		const char *flags_names[32];
		i32 flags[32];

		zt_fiz(model_component->options_layers_size) {
			flags_names[i] = model_component->options_layers[i];
			flags[i] = zt_bit(i);
		}

		zt_componentGuiMakeFlagsEditor(sizer, "Layers:", flags_names, flags, model_component->options_layers_size, &model_component->models_layers[component_id], 2);
	}

	if (model->anim_controller) {
		ztGuiItem *combo_anim = zt_guiMakeComboBox(sizer, model->anim_controller->sequences_count);

		zt_fiz(model->anim_controller->sequences_count) {
			zt_guiComboBoxAppend(combo_anim, model->anim_controller->sequences_name[i]);;

			if (model->anim_controller->anim_sync == model->anim_controller->sequences[i]) {
				zt_guiComboBoxSetSelected(combo_anim, i);
			}
		}
		zt_guiComboBoxSetCallback(combo_anim, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentGuiComboAnimation), gui_info);

		zt_componentGuiMakeItem(sizer, "Animation:", combo_anim);
	}

	{
		ztGuiItem *combo_materials = zt_guiMakeComboBox(sizer, model_component->options_materials_size + 1);
		zt_guiComboBoxAppend(combo_materials, "No Material");
		zt_fiz(model_component->options_materials_size) {
			zt_guiComboBoxAppend(combo_materials, model_component->options_materials[i].name);

			if (zt_materialIsEqual(&model->material, &model_component->options_materials[i].material)) {
				zt_guiComboBoxSetSelected(combo_materials, i + 1);
			}
		}
		zt_guiComboBoxSetCallback(combo_materials, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentGuiComboMaterial), gui_info);

		zt_componentGuiMakeItem(sizer, "Material:", combo_materials);
	}

	{
		ztGuiItem *combo_shaders = zt_guiMakeComboBox(sizer, model_component->options_shaders_size + 1);
		zt_guiComboBoxAppend(combo_shaders, "No Shader");
		zt_fiz(model_component->options_shaders_size) {
			zt_guiComboBoxAppend(combo_shaders, model_component->options_shaders[i].name);

			if (model->shader == model_component->options_shaders[i].shader) {
				zt_guiComboBoxSetSelected(combo_shaders, i + 1);
			}
		}
		zt_guiComboBoxSetCallback(combo_shaders, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentGuiComboShader), gui_info);

		zt_componentGuiMakeItem(sizer, "Shader:", combo_shaders);
	}

	{
		ztGuiItem *sizer_ops = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);

		ztGuiItem *toggle_aabb = zt_guiMakeToggleButton(sizer_ops, "aabb", 0, &model_component->edit_show_bounds_aabb);
		zt_guiSizerAddItem(sizer_ops, toggle_aabb, 0, padding);

		ztGuiItem *toggle_wire = zt_guiMakeToggleButton(sizer_ops, "wire", 0, &model_component->edit_show_wireframe);
		zt_guiSizerAddItem(sizer_ops, toggle_wire, 0, padding);

		ztGuiItem *toggle_simple = zt_guiMakeToggleButton(sizer_ops, "simple", 0, &model_component->edit_show_simple);
		zt_guiSizerAddItem(sizer_ops, toggle_simple, 0, padding);

		ztGuiItem *layers = zt_guiMakeButton(sizer_ops, "layers", 0, nullptr);
		zt_guiSizerAddItem(sizer_ops, layers, 0, padding);
		zt_guiButtonSetCallback(layers, ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentGuiLayersButton), model_component);
		layers->size.y = toggle_simple->size.y;


		zt_componentGuiMakeItem(sizer, "", sizer_ops);
	}

	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_MODEL_COMPONENT_FILE_VERSION_1     10001
#define ZT_MODEL_COMPONENT_FILE_VERSION_2     10002
#define ZT_MODEL_COMPONENT_FILE_VERSION_3     10003

#define ZT_MODEL_COMPONENT_FILE_VERSION       ZT_MODEL_COMPONENT_FILE_VERSION_3

#define _serialCheck(code) if(!(code)) { zt_logCritical("ModelComponent serialization failed."); return false; }

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_SAVE(_zt_modelComponentSave)
{
	ZT_PROFILE_GAME("_zt_modelComponentSave");

	ztModelComponent *model_component = (ztModelComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_MODEL_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_MODEL_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, model_component->models_count));
		_serialCheck(zt_serialWrite(serial, model_component->edit_show_wireframe));
		_serialCheck(zt_serialWrite(serial, model_component->edit_show_simple));
		_serialCheck(zt_serialWrite(serial, model_component->edit_show_bounds_aabb));
		_serialCheck(zt_serialWrite(serial, model_component->edit_show_layers_mask));

		zt_fiz(model_component->models_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, model_component->models_guids[i]));
				_serialCheck(zt_serialWrite(serial, model_component->entity_ids[i]));

				if (model_component->entity_ids[i] != ztInvalidID) {
					_serialCheck(zt_serialWrite(serial, model_component->models[i]->transform.position));
					_serialCheck(zt_serialWrite(serial, model_component->models[i]->transform.rotation));
					_serialCheck(zt_serialWrite(serial, model_component->models[i]->transform.scale));
					_serialCheck(zt_serialWrite(serial, model_component->models[i]->flags));
					_serialCheck(zt_serialWrite(serial, model_component->models_layers[i]));

					bool found_shader = false;
					zt_fjz(model_component->options_shaders_size) {
						if (model_component->models[i]->shader == model_component->options_shaders[j].shader) {
							_serialCheck(zt_serialWrite(serial, model_component->options_shaders[j].guid));
							found_shader = true;
							break;
						}
					}
					if (!found_shader) {
						_serialCheck(zt_serialWrite(serial, zt_guidMake(0, 0, 0, 0)));
					}

					bool found_material = false;
					zt_fjz(model_component->options_materials_size) {
						if (zt_materialIsEqual(&model_component->models[i]->material, &model_component->options_materials[j].material)) {
							_serialCheck(zt_serialWrite(serial, model_component->options_materials[j].guid));
							found_material = true;
							break;
						}
					}
					if (!found_material) {
						_serialCheck(zt_serialWrite(serial, zt_guidMake(0, 0, 0, 0)));
					}
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_modelComponentLoad)
{
	ZT_PROFILE_GAME("_zt_modelComponentLoad");

	ztModelComponent *model_component = (ztModelComponent*)component->user_data;

	// clear out existing models from scene
	zt_fiz(model_component->models_count) {
		if (model_component->models[i] == nullptr) {
			continue;
		}
		if (zt_sceneHasModel(model_component->scene, model_component->models[i])) {
			zt_sceneRemoveModel(model_component->scene, model_component->models[i]);
		}
		zt_modelFree(model_component->models[i]);
	}

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_MODEL_COMPONENT_GUID) {
			zt_logCritical("ModelComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_MODEL_COMPONENT_FILE_VERSION) {
			zt_logCritical("ModelComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		i32 models_count = 0;
		_serialCheck(zt_serialRead(serial, &models_count));

		if (version >= ZT_MODEL_COMPONENT_FILE_VERSION_3) {
			_serialCheck(zt_serialRead(serial, &model_component->edit_show_wireframe));
			_serialCheck(zt_serialRead(serial, &model_component->edit_show_simple));
			_serialCheck(zt_serialRead(serial, &model_component->edit_show_bounds_aabb));
			_serialCheck(zt_serialRead(serial, &model_component->edit_show_layers_mask));
		}

		zt_fiz(models_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				ztGuid model_guid;
				_serialCheck(zt_serialRead(serial, &model_guid));

				ztEntityID entity_id = ztInvalidID;
				_serialCheck(zt_serialRead(serial, &entity_id));

				if (entity_id != ztInvalidID) {
					ztComponentID comp_idx = zt_modelComponentAdd(model_component, pool, entity_id, model_guid);

					if (comp_idx != ztInvalidID) {
						_serialCheck(zt_serialRead(serial, &model_component->models[comp_idx]->transform.position));
						_serialCheck(zt_serialRead(serial, &model_component->models[comp_idx]->transform.rotation));
						_serialCheck(zt_serialRead(serial, &model_component->models[comp_idx]->transform.scale));
						_serialCheck(zt_serialRead(serial, &model_component->models[comp_idx]->flags));

						if (version >= ZT_MODEL_COMPONENT_FILE_VERSION_2) {
							_serialCheck(zt_serialRead(serial, &model_component->models_layers[comp_idx]));
						}

						model_component->models[comp_idx]->flags |= ztModelFlags_Initialized;

						ztGuid shader_guid, material_guid;

						_serialCheck(zt_serialRead(serial, &shader_guid));
						_serialCheck(zt_serialRead(serial, &material_guid));

						model_component->models[comp_idx]->shader = model_component->default_shader;
						zt_fjz(model_component->options_shaders_size) {
							if (shader_guid == model_component->options_shaders[j].guid) {
								model_component->models[comp_idx]->shader = model_component->options_shaders[j].shader;
								break;
							}
						}

						zt_fjz(model_component->options_materials_size) {
							if (material_guid == model_component->options_materials[j].guid) {
								model_component->models[comp_idx]->material = model_component->options_materials[j].material;
								break;
							}
						}

						zt_sceneRefreshModel(model_component->scene, model_component->models[comp_idx]);
					}
					else {
						zt_logCritical("Component GUID missing: {%08x-%08x-%08x-%08x}", model_guid.guid_32[0], model_guid.guid_32[1], model_guid.guid_32[2], model_guid.guid_32[3]);
					}
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_modelComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_modelComponentUpdate");

	ztModelComponent *model_component = (ztModelComponent *)component->user_data;

	if (pool->editor) {

		if (model_component->edit_last_active_model != nullptr) {
			ztEntityID active_entity = zt_entityEditorGetActiveEntity(pool->editor);
			if (active_entity != model_component->edit_last_active_entity) {
				if (!model_component->edit_ignore_entity_change) {
					model_component->edit_last_active_model = nullptr;
				}
				model_component->edit_ignore_entity_change = false;
				model_component->edit_last_active_entity = active_entity;
			}

			zt_modelEditWidgetUpdate(&model_component->edit_widget, input_keys, input_mouse, camera, dt);
		}
	}

	return true;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_modelComponentFindModelAndIntersectPoint(ztModelComponent *model_component, const ztVec3 &ray_pos, const ztVec3 &ray_dir, ztEntityID *entity_id, ztModel **model, ztVec3 *intersect_point, i32 *closest_id, r32 *closest_dist)
{
	r32 closest_time = ztReal32Max;
	i32 closest_idx = -1;
	ztVec3 closest_pos = ztVec3::zero;

	zt_fiz(model_component->models_count) {
		if (model_component->models[i] == nullptr || zt_bitIsSet(model_component->models[i]->flags, ztModelFlags_Hidden) || zt_bitIsSet(model_component->models[i]->flags, ztModelFlags_ShadowOnly)) {
			continue;
		}

		if (model_component->edit_show_layers_mask != 0) {
			if (!zt_bitIsSet(model_component->models_layers[i], model_component->edit_show_layers_mask)) {
				continue;
			}
		}

		ztVec3 center, ext;
		zt_modelGetAABB(model_component->models[i], &center, &ext);

		r32 intersect_time = ztReal32Max;
		ztVec3 intersect_pos = ztVec3::zero;
		if (zt_collisionRayInAABB(ray_pos, ray_dir, center, ext, &intersect_time, &intersect_pos)) {
			i32 vert_count = zt_modelGetVertices(model_component->models[i], nullptr, 0, ztModelGetVerticesTransform_WorldTransform);
			ztVec3 *verts = zt_mallocStructArrayArena(ztVec3, vert_count, zt_memGetTempArena());

			bool collided_tri = false;

			if (verts == nullptr) {
				zt_logCritical("Not enough temporary memory to extract triangles for model component_id %d", i);
				collided_tri = true;
			}
			else {
				zt_modelGetVertices(model_component->models[i], verts, vert_count, ztModelGetVerticesTransform_WorldTransform);

				r32 dist = ray_pos.distance(intersect_pos);
				ztVec3 line_beg = ray_pos;
				ztVec3 line_end = ray_pos + (ray_dir * 1000);

				for (int tri = 0; tri < vert_count; tri += 3) {
					if (zt_collisionLineInTriangle(line_beg, line_end, verts[tri], verts[tri + 1], verts[tri + 2], &intersect_pos, &intersect_time)) {
						collided_tri = true;
						break;
					}
				}

				zt_freeArena(verts, zt_memGetTempArena());
			}

			if (collided_tri && intersect_time < closest_time) {
				closest_time = intersect_time;
				closest_idx = i;
				closest_pos = intersect_pos;
			}
		}
	}

	if (closest_idx >= 0) {
		if (closest_id) *closest_id = closest_idx;
		if (closest_dist) *closest_dist = ray_pos.distance(closest_pos);

		if (entity_id) *entity_id = model_component->entity_ids[closest_idx];
		if (model) *model = model_component->models[closest_idx];
		if (intersect_point) *intersect_point = closest_pos;

		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

bool zt_modelComponentFindModelAndIntersectPoint(ztModelComponent *model_component, const ztVec3 &ray_pos, const ztVec3 &ray_dir, ztEntityID *entity_id, ztModel **model, ztVec3 *intersect_point)
{
	return _zt_modelComponentFindModelAndIntersectPoint(model_component, ray_pos, ray_dir, entity_id, model, intersect_point, nullptr, nullptr);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK(_zt_modelComponentEditQueryClick)
{
	ZT_PROFILE_GAME("_zt_modelComponentEditQueryClick");

	ztModelComponent *model_component = (ztModelComponent *)component->user_data;

	if (model_component->edit_last_active_model != nullptr) {
		if (zt_modelEditWidgetIsMouseWithinBounds(&model_component->edit_widget, camera, input_mouse->screen_x, input_mouse->screen_y)) {
			*closest_id = -100;
			*closest_dist = ztReal32Min; // this always needs processed with priority
			return true;
		}
	}

	model_component->edit_last_active_model = nullptr;
	model_component->edit_last_active_entity = ztInvalidID;

	r32 closest_time = ztReal32Max;
	i32 closest_idx = -1;
	ztVec3 closest_pos = ztVec3::zero;

	zt_fiz(model_component->models_count) {
		if (model_component->models[i] == nullptr || zt_bitIsSet(model_component->models[i]->flags, ztModelFlags_Hidden) || zt_bitIsSet(model_component->models[i]->flags, ztModelFlags_ShadowOnly)) {
			continue;
		}

		if (model_component->edit_show_layers_mask != 0) {
			if (!zt_bitIsSet(model_component->models_layers[i], model_component->edit_show_layers_mask)) {
				continue;
			}
		}


		ztVec3 center, ext;
		zt_modelGetAABB(model_component->models[i], &center, &ext);

		r32 intersect_time = ztReal32Max;
		ztVec3 intersect_pos = ztVec3::zero;
		if (zt_collisionRayInAABB(ray_pos, ray_dir, center, ext, &intersect_time, &intersect_pos)) {
			i32 vert_count = zt_modelGetVertices(model_component->models[i], nullptr, 0, ztModelGetVerticesTransform_WorldTransform);
			ztVec3 *verts = zt_mallocStructArrayArena(ztVec3, vert_count, zt_memGetTempArena());

			bool collided_tri = false;

			if (verts == nullptr) {
				zt_logCritical("Not enough temporary memory to extract triangles for model component_id %d", i);
				collided_tri = true;
			}
			else {
				zt_modelGetVertices(model_component->models[i], verts, vert_count, ztModelGetVerticesTransform_WorldTransform);

				r32 dist = ray_pos.distance(intersect_pos);
				ztVec3 line_beg = ray_pos;
				ztVec3 line_end = ray_pos + (ray_dir * 1000);

				for (int tri = 0; tri < vert_count; tri += 3) {
					if (zt_collisionLineInTriangle(line_beg, line_end, verts[tri], verts[tri + 1], verts[tri + 2], &intersect_pos, &intersect_time)) {
						collided_tri = true;
						break;
					}
				}

				zt_freeArena(verts, zt_memGetTempArena());
			}

			if (collided_tri && intersect_time < closest_time) {
				closest_time = intersect_time;
				closest_idx = i;
				closest_pos = intersect_pos;
			}
		}
	}

	if (closest_idx >= 0) {
		*closest_id = closest_idx;
		*closest_dist = ray_pos.distance(closest_pos);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK(_zt_modelComponentEditProcessClick)
{
	ZT_PROFILE_GAME("_zt_modelComponentEditProcessClick");

	ztModelComponent *model_component = (ztModelComponent *)component->user_data;

	if (closest_id != -100) {
		if (model_component->edit_last_active_model != model_component->models[closest_id]) {
			model_component->edit_last_active_model = model_component->models[closest_id];
			model_component->edit_last_active_entity = model_component->entity_ids[closest_id];
			zt_modelEditWidgetFree(&model_component->edit_widget);
			zt_modelEditWidgetMake(&model_component->edit_widget, model_component->edit_last_active_model);

			model_component->edit_ignore_entity_change = true;
			zt_entityEditorMakeEntityActive(pool->editor, model_component->edit_last_active_entity);
		}
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_modelComponentEditDrawDebug)
{
	ZT_PROFILE_GAME("_zt_modelComponentEditDrawDebug");

	ztModelComponent *model_component = (ztModelComponent *)component->user_data;

	ztVec3 aabb_center, aabb_size;
	ztModel *model = model_component->models[active_component_id];

	zt_assertReturnOnFail(model != nullptr);

	zt_modelGetAABB(model, &aabb_center, &aabb_size);

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefaultWhite);

	if (model_component->edit_show_bounds_aabb) {
		zt_drawListPushColor(draw_list, ztColor_Red);
		zt_drawListAddEmptyCubeFromCenterSize(draw_list, aabb_center, aabb_size);
		zt_drawListPopColor(draw_list);
	}

	if (model_component->edit_last_active_model != nullptr) {
		zt_modelEditWidgetRender(&model_component->edit_widget, camera, draw_list);

		if (model_component->edit_show_wireframe) {
			i32 verts_count = zt_modelGetVertices(model_component->edit_last_active_model, nullptr, 0, ztModelGetVerticesTransform_WorldTransform);
			ztVec3 *verts = zt_mallocStructArrayArena(ztVec3, verts_count, zt_memGetTempArena());

			zt_modelGetVertices(model_component->edit_last_active_model, verts, verts_count, ztModelGetVerticesTransform_WorldTransform);

			zt_drawListPushColor(draw_list, ztColor_White);
			for (int i = 0; i < verts_count; i += 3) {
				zt_drawListAddEmptyTriangle(draw_list, verts[i], verts[i + 1], verts[i + 2]);
			}
			zt_drawListPopColor(draw_list);

			zt_freeArena(verts, zt_memGetTempArena());
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);

}

// ================================================================================================================================================================================================
//#define ZT_FUNC_SCENE_RENDER_MODEL_OVERRIDE(name) void name(ztScene *scene, i32 scene_model_info_index, ztModel *model, ztShaderID *shader_to_use, i32 *model_info_flags_to_use, i32 *model_flags_to_use, ztSceneRenderStage_Enum render_stage, void *user_data)

ZT_FUNC_SCENE_RENDER_MODEL_OVERRIDE(_zt_modelComponentEditRenderOverride)
{
	ZT_PROFILE_GAME("_zt_modelComponentEditRenderOverride");

	ztModelComponent *model_component = (ztModelComponent *)user_data;

	if (model_component->edit_show_layers_mask != 0) {
		zt_fiz(model_component->models_count) {
			if (model_component->models[i] == model) {
				if (!zt_bitIsSet(model_component->models_layers[i], model_component->edit_show_layers_mask)) {

					*model_info_flags_to_use |= ztSceneModelFlags_Culled;
					return;
				}
				break;
			}
		}
	}

	if (!model_component->edit_show_simple) {
		return;
	}

	if (render_stage != ztSceneRenderStage_Render) {
		*model_info_flags_to_use |= ztSceneModelFlags_Culled;
		return;
	}

	*shader_to_use = model_component->default_shader;
}

// ================================================================================================================================================================================================

void zt_modelComponentModelMake(ztModelComponentModel *comp_model, ztGuid guid, const char *name, ztModel *model)
{
	ZT_PROFILE_GAME("zt_modelComponentModelMake");

	comp_model->guid = guid;
	zt_strCpy(comp_model->name, zt_elementsOf(comp_model->name), name);
	comp_model->model = model;
}

// ================================================================================================================================================================================================

void zt_modelComponentShaderMake(ztModelComponentShader *comp_shader, ztGuid guid, const char *name, ztShaderID shader_id)
{
	ZT_PROFILE_GAME("zt_modelComponentShaderMake");

	comp_shader->guid = guid;
	zt_strCpy(comp_shader->name, zt_elementsOf(comp_shader->name), name);
	comp_shader->shader = shader_id;
}

// ================================================================================================================================================================================================

void zt_modelComponentMaterialMake(ztModelComponentMaterial *comp_material, ztGuid guid, const char *name, ztMaterial *material)
{
	ZT_PROFILE_GAME("zt_modelComponentMaterialMake");

	comp_material->guid = guid;
	zt_strCpy(comp_material->name, zt_elementsOf(comp_material->name), name);
	comp_material->material = *material;
}

// ================================================================================================================================================================================================

bool zt_modelComponentMakeAndRegister(ztModelComponent *model_component, i32 model_pool_size, i32 bone_pool_size, ztEntityPool *pool, ztModelComponentModel *options_models, i32 options_models_size, ztModelComponentShader *options_shaders, i32 options_shaders_size, ztModelComponentMaterial *options_materials, i32 options_materials_size, const char **options_layers, i32 options_layers_size, ztScene *scene, bool using_editor, ztShaderID default_shader)
{
	ZT_PROFILE_GAME("zt_modelComponentMakeAndRegister");

	zt_returnValOnNull(model_component, false);
	zt_returnValOnNull(pool, false);
	zt_returnValOnNull(scene, false);

	model_component->models_pool = zt_mallocStructArray(ztModel, model_pool_size);
	model_component->models_pool_size = model_pool_size;
	model_component->models_pool_count = 0;

	model_component->bones_pool = zt_mallocStructArray(ztBone, bone_pool_size);
	model_component->bones_pool_size = bone_pool_size;
	model_component->bones_pool_count = 0;

	model_component->models_guids = zt_mallocStructArray(ztGuid, model_pool_size);
	model_component->models = zt_mallocStructArray(ztModel*, model_pool_size);
	model_component->models_layers = zt_mallocStructArray(i32, model_pool_size);
	model_component->models_count = 0;

	model_component->entity_ids = zt_mallocStructArray(ztEntityID, model_pool_size);

	model_component->default_shader = default_shader;

	model_component->edit_last_active_model = nullptr;
	model_component->edit_last_active_entity = ztInvalidID;
	model_component->edit_show_bounds_aabb = true;
	model_component->edit_show_wireframe = false;
	model_component->edit_show_layers_mask = 0;
	model_component->edit_ignore_entity_change = false;

	zt_fiz(model_pool_size) {
		model_component->models[i] = nullptr;
		model_component->entity_ids[i] = ztInvalidID;
	}

	struct sorter
	{
		static int compareModels(const void *vone, const void *vtwo)
		{
			ztModelComponentModel *one = (ztModelComponentModel*)vone;
			ztModelComponentModel *two = (ztModelComponentModel*)vtwo;
			return zt_striCmp(one->name, two->name);
		}
		static int compareShaders(const void *vone, const void *vtwo)
		{
			ztModelComponentShader *one = (ztModelComponentShader*)vone;
			ztModelComponentShader *two = (ztModelComponentShader*)vtwo;
			return zt_striCmp(one->name, two->name);
		}
		static int compareMaterials(const void *vone, const void *vtwo)
		{
			ztModelComponentMaterial *one = (ztModelComponentMaterial*)vone;
			ztModelComponentMaterial *two = (ztModelComponentMaterial*)vtwo;
			return zt_striCmp(one->name, two->name);
		}
	};

	model_component->options_models = zt_mallocStructArray(ztModelComponentModel, options_models_size);
	model_component->options_models_size = options_models_size;
	zt_memCpy(model_component->options_models, zt_sizeof(ztModelComponentModel) * options_models_size, options_models, zt_sizeof(ztModelComponentModel) * options_models_size);
	qsort(model_component->options_models, model_component->options_models_size, zt_sizeof(ztModelComponentModel), sorter::compareModels);

	model_component->options_shaders = zt_mallocStructArray(ztModelComponentShader, options_shaders_size);
	model_component->options_shaders_size = options_shaders_size;
	zt_memCpy(model_component->options_shaders, zt_sizeof(ztModelComponentShader) * options_shaders_size, options_shaders, zt_sizeof(ztModelComponentShader) * options_shaders_size);
	qsort(model_component->options_shaders, model_component->options_shaders_size, zt_sizeof(ztModelComponentShader), sorter::compareShaders);

	model_component->options_materials = zt_mallocStructArray(ztModelComponentMaterial, options_materials_size);
	model_component->options_materials_size = options_materials_size;
	zt_memCpy(model_component->options_materials, zt_sizeof(ztModelComponentMaterial) * options_materials_size, options_materials, zt_sizeof(ztModelComponentMaterial) * options_materials_size);
	qsort(model_component->options_materials, model_component->options_materials_size, zt_sizeof(ztModelComponentMaterial), sorter::compareMaterials);

	model_component->options_layers = zt_mallocStructArray(ztString, options_layers_size);
	model_component->options_layers_size = options_layers_size;

	zt_fiz(options_layers_size) {
		model_component->options_layers[i] = zt_stringMakeFrom(options_layers[i]);
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_MODEL_COMPONENT_GUID, ZT_MODEL_COMPONENT_NAME, model_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentUpdate), &component) < 0) {

		return false;
	}

	component->component_edit_query_click = ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentEditQueryClick);
	component->component_edit_process_click = ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentEditProcessClick);
	component->component_edit_draw_debug = ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentEditDrawDebug);

	model_component->scene = scene;

	if (using_editor) {
		model_component->scene->render_override = ZT_FUNCTION_POINTER_TO_VAR(_zt_modelComponentEditRenderOverride);
		model_component->scene->render_override_user_data = model_component;
	}

	return true;
}

// ================================================================================================================================================================================================

void zt_modelComponentFreeAndUnregister(ztModelComponent *model_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_modelComponentFreeAndUnregister");

	if (model_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_MODEL_COMPONENT_GUID);

	zt_fiz(model_component->models_count) {
		if (model_component->models[i] == nullptr) {
			continue;
		}

		if (zt_sceneHasModel(model_component->scene, model_component->models[i])) {
			zt_sceneRemoveModel(model_component->scene, model_component->models[i]);
		}

		zt_modelFree(model_component->models[i]);
	}

	if (model_component->models_pool) zt_free(model_component->models_pool);
	if (model_component->bones_pool) zt_free(model_component->bones_pool);
	if (model_component->models_guids) zt_free(model_component->models_guids);
	if (model_component->models_layers) zt_free(model_component->models_layers);
	if (model_component->models) zt_free(model_component->models);
	if (model_component->entity_ids) zt_free(model_component->entity_ids);
	if (model_component->options_models) zt_free(model_component->options_models);
	if (model_component->options_shaders) zt_free(model_component->options_shaders);
	if (model_component->options_materials) zt_free(model_component->options_materials);

	if (model_component->options_layers) {
		zt_fiz(model_component->options_layers_size) {
			zt_stringFree(model_component->options_layers[i]);
		}
		zt_free(model_component->options_layers);
	}

	zt_modelEditWidgetFree(&model_component->edit_widget);

	zt_memSet(model_component, zt_sizeof(ztModelComponent), 0);
}

// ================================================================================================================================================================================================

ztInternal i32 _zt_modelComponentCountModels(ztModel *model)
{
	ZT_PROFILE_GAME("_zt_modelComponentCountModels");

	i32 models = 1;

	zt_flink(child, model->first_child) {
		models += _zt_modelComponentCountModels(model);
	}

	return models;
}

// ================================================================================================================================================================================================

ztInternal i32 _zt_modelComponentCountBones(ztModel *model)
{
	ZT_PROFILE_GAME("_zt_modelComponentCountBones");

	i32 bones = model->bones_count;

	zt_flink(child, model->first_child) {
		bones += _zt_modelComponentCountBones(model);
	}

	return bones;
}

// ================================================================================================================================================================================================

ztComponentID zt_modelComponentAdd(ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity_id, ztGuid model_guid)
{
	ZT_PROFILE_GAME("zt_modelComponentAdd");

	zt_returnValOnNull(model_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);
	zt_assertReturnValOnFail(entity_id != ztInvalidID, ztInvalidID);

	ztModelComponentModel *mcm = nullptr;
	zt_fiz(model_component->options_models_size) {
		if (model_component->options_models[i].guid == model_guid) {
			mcm = &model_component->options_models[i];
			break;
		}
	}

	if (mcm == nullptr) {
		char guidstr[128] = { 0 };
		zt_guidToString(model_guid, guidstr, zt_elementsOf(guidstr));
		zt_logCritical("Unable to find model matching guid: %s", guidstr);
		return ztInvalidID;
	}

	int total_models = _zt_modelComponentCountModels(mcm->model);
	int total_bones = _zt_modelComponentCountBones(mcm->model);

	if (model_component->models_pool_size - model_component->models_pool_count < total_models) {
		char guidstr[128] = { 0 };
		zt_guidToString(model_guid, guidstr, zt_elementsOf(guidstr));
		zt_logCritical("Unable to allocate %d models for guid: %s", total_models, guidstr);
		return ztInvalidID;
	}

	if (model_component->bones_pool_size - model_component->bones_pool_count < total_bones) {
		char guidstr[128] = { 0 };
		zt_guidToString(model_guid, guidstr, zt_elementsOf(guidstr));
		zt_logCritical("Unable to allocate %d bones for guid: %s", total_bones, guidstr);
		return ztInvalidID;
	}

	int models_begin_idx = -1;
	int bones_begin_idx = -1;

	int models_in_this_run = 0;
	int bones_in_this_run = 0;

	zt_fiz(model_component->models_pool_size) {
		if (model_component->models_pool[i].type == ztModelType_Invalid) {
			if (++models_in_this_run == total_models) {
				models_begin_idx = i - (models_in_this_run - 1);
				break;
			}
		}
		else {
			models_in_this_run = 0;
		}
	}

	if (total_bones > 0) {
		zt_fiz(model_component->bones_pool_size) {
			if (!zt_bitIsSet(model_component->bones_pool[i].flags, ztModelComponentBoneFlags_InUse)) {
				if (++bones_in_this_run == total_bones) {
					bones_begin_idx = i - (bones_in_this_run - 1);
					break;
				}
			}
			else {
				bones_in_this_run = 0;
			}
		}
	}

	zt_assertReturnValOnFail(models_begin_idx != -1 && (total_bones <= 0 || bones_begin_idx != -1), ztInvalidID);

	ztModelLoaderInput input;
	zt_memSet(&input, zt_sizeof(ztModelLoaderInput), 0);

	input.models = &model_component->models_pool[models_begin_idx];
	input.models_size = total_models;
	input.bones = bones_begin_idx >= 0 ? &model_component->bones_pool[bones_begin_idx] : nullptr;
	input.bones_size = total_bones;

	if (!zt_modelClone(&input, mcm->model)) {
		char guidstr[128] = { 0 };
		zt_guidToString(model_guid, guidstr, zt_elementsOf(guidstr));
		zt_logCritical("Unable to clone model guid: %s", total_bones, guidstr);
		return ztInvalidID;
	}

	zt_assertReturnValOnFail(input.root_model != nullptr, ztInvalidID);

	zt_fiz(input.bones_used) {
		input.bones[i].flags |= ztModelComponentBoneFlags_InUse;
	}
	zt_fiz(input.models_used) {
		if (input.models[i].type == ztModelType_Mesh) {
			input.models[i].shader = model_component->default_shader;
		}
	}

	int model_idx = -1;
	zt_fiz(model_component->models_pool_size) {
		if (model_component->models[i] == nullptr) {
			model_idx = i;
			model_component->models_guids[i] = model_guid;
			model_component->models[i] = input.root_model;
			model_component->entity_ids[i] = entity_id;
			model_component->models_count = zt_max(model_component->models_count, i + 1);
			zt_sceneAddModel(model_component->scene, input.root_model);
			zt_entityAddedComponent(pool, entity_id, ZT_MODEL_COMPONENT_GUID, model_idx);
			break;
		}
	}

	return model_idx;
}

// ================================================================================================================================================================================================

void zt_modelComponentRemove(ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_modelComponentRemove");

	ztModel *model = model_component->models[component_id];

	//zt_logVerbose("Deleting model: %s; component_id: %d; entity_id: %lld; model: 0x%08x", model->name, component_id, entity_id, model);

	model_component->models[component_id] = nullptr;
	model_component->entity_ids[component_id] = ztInvalidID;

	if (model_component->models_count - 1 == component_id) {
		model_component->models_count -= 1;
	}

	if (zt_sceneHasModel(model_component->scene, model)) {
		zt_sceneRemoveModel(model_component->scene, model);
	}

	zt_fiz(model->bones_count) {
		zt_bitRemove(model->bones[i].flags, ztModelComponentBoneFlags_InUse);
	}

	zt_modelFree(model);

	zt_entityRemovedComponent(pool, entity_id, ZT_MODEL_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

ztModel *zt_modelComponentGet(ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity, int which_idx, ztComponentID *component_id_out)
{
	ZT_PROFILE_GAME("zt_modelComponentGet");

	if (component_id_out) {
		*component_id_out = ztInvalidID;
	}

	zt_returnValOnNull(model_component, nullptr);
	zt_returnValOnNull(pool, nullptr);

	zt_fiz(model_component->models_count) {
		if (model_component->entity_ids[i] == entity) {
			if (which_idx-- <= 0) {

				if (component_id_out) {
					*component_id_out = i;
				}
				return model_component->models[i];
			}
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

ztModel *zt_modelComponentGet(ztModelComponent *model_component, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_modelComponentGet");

	zt_returnValOnNull(model_component, nullptr);
	zt_assertReturnValOnFail(component_id >= 0 && component_id < model_component->models_count, nullptr);

	return model_component->models[component_id];
}

// ================================================================================================================================================================================================

void zt_modelComponentCreateAndAssignEntities(ztModelComponent *model_component, ztEntityPool *pool, bool overwrite_existing)
{
	ZT_PROFILE_GAME("zt_modelComponentCreateAndAssignEntities");

	ztComponent *component = nullptr;
	zt_fiz(pool->components_count) {
		if (pool->components[i].guid == ZT_MODEL_COMPONENT_GUID) {
			component = &pool->components[i];
			break;
		}
	}

	bool added_new_entry = false;
	zt_fiz(model_component->options_models_size) {
		ztToken tokens[16];
		int tokens_count = zt_strTokenize(model_component->options_models[i].name, ".", tokens, zt_elementsOf(tokens));

		ztEntityID parent_entity_id = ztInvalidID;

		zt_fvz(token_idx, tokens_count) {
			char entity_name[64];
			zt_strCpy(entity_name, zt_elementsOf(entity_name), model_component->options_models[i].name + tokens[token_idx].beg, tokens[token_idx].len);

			ztEntityID entity_id = zt_entityFindByName(pool, entity_name, parent_entity_id, false);
			if (entity_id == ztInvalidID) {
				entity_id = zt_entityPoolMakeEntity(pool, entity_name, parent_entity_id);
			}

			parent_entity_id = entity_id;

			if (token_idx == tokens_count - 1) {
				ztEntity *entity = zt_entityPoolGetEntity(pool, entity_id);

				bool create_new = true;

				ztComponentID component_id = _zt_modelComponentFind(component, entity, entity_id, ztInvalidID);
				while (component_id != ztInvalidID) {
					if (zt_strEquals(model_component->models[component_id]->name, model_component->options_models[i].model->name)) {
						if (overwrite_existing) {
							create_new = true;
							zt_modelComponentRemove(model_component, pool, entity_id, component_id);
						}
						else {
							create_new = false;
						}
						break;
					}
					component_id = _zt_modelComponentFind(component, entity, entity_id, component_id);
				}

				if (create_new) {
					zt_modelComponentAdd(model_component, pool, entity_id, model_component->options_models[i].guid);
					added_new_entry = true;
				}
			}
		}
	}

	if (pool->editor && added_new_entry) {
		zt_entityEditorNotifyNewEntity(pool->editor, ztInvalidID);
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal char *_zt_modelMaterial_types[] = {
	".albedo.png",
	".normal.png",
	".rough_metal_height.png",
	".emissive.png",
};

// ================================================================================================================================================================================================

i32 zt_modelComponentMaterialLoaderQuery(ztModelComponentMaterialLoaderState *state, ztAssetManager *asset_manager, const char **directories, i32 directories_count, ztModelComponentMaterial **materials)
{
	zt_returnValOnNull(state, 0);
	zt_returnValOnNull(asset_manager, 0);
	zt_returnValOnNull(materials, 0);

	zt_memSet(state, zt_sizeof(ztModelComponentMaterialLoaderState), 0);

	int textures_to_load = 0;

	zt_fiz(asset_manager->asset_count) {
		zt_fjz(directories_count) {
			if (zt_strStartsWith(asset_manager->asset_name[i], directories[j])) {
				zt_fxze(_zt_modelMaterial_types) {
					if (zt_striEndsWith(asset_manager->asset_name[i], _zt_modelMaterial_types[x])) {
						textures_to_load += 1;
						break;
					}
				}
			}
		}
	}

	state->textures_total = textures_to_load;
	state->textures_current = 0;

	state->asset_manager_file_indexes = zt_mallocStructArray(i32, textures_to_load);

	i32 *unique_materials = zt_mallocStructArrayArena(i32, textures_to_load, zt_memGetTempArena());
	i32 unique_materials_idx = 0;

	textures_to_load = 0;
	zt_fiz(asset_manager->asset_count) {
		zt_fjz(directories_count) {
			if (zt_strStartsWith(asset_manager->asset_name[i], directories[j])) {
				zt_fxze(_zt_modelMaterial_types) {
					if (zt_striEndsWith(asset_manager->asset_name[i], _zt_modelMaterial_types[x])) {
						const char *name_ptr = zt_strFindLast(asset_manager->asset_name[i], "/");
						int name_pos_type = zt_striFindPos(name_ptr, _zt_modelMaterial_types[x], 0);

						if (name_ptr != nullptr && name_pos_type != ztStrPosNotFound) {
							char name[256];
							zt_strCpy(name, zt_elementsOf(name), name_ptr + 1, name_pos_type - 1);

							i32 hash = zt_strHash(name);
							bool found_hash = false;
							zt_fyz(unique_materials_idx) {
								if (unique_materials[y] == hash) {
									found_hash = true;
									break;
								}
							}

							if (!found_hash) {
								unique_materials[unique_materials_idx++] = hash;
							}

							state->asset_manager_file_indexes[textures_to_load++] = i;
						}
						break;
					}
				}
			}
		}
	}

	state->materials_total = unique_materials_idx;
	state->materials_current = 0;

	*materials = zt_mallocStructArray(ztModelComponentMaterial, unique_materials_idx);

	zt_freeArena(unique_materials, zt_memGetTempArena());

	return unique_materials_idx;
}

// ================================================================================================================================================================================================

void zt_modelComponentMaterialLoaderFree(ztModelComponentMaterialLoaderState *state)
{
	if (state == nullptr) {
		return;
	}

	if (state->asset_manager_file_indexes) {
		zt_free(state->asset_manager_file_indexes);
		state->asset_manager_file_indexes = nullptr;
	}
}

// ================================================================================================================================================================================================

bool zt_modelComponentMaterialLoaderUpdate(ztModelComponentMaterialLoaderState *state, ztAssetManager *asset_manager, ztModelComponentMaterial *materials, bool *is_complete, char *error_buffer, i32 error_buffer_len)
{
	zt_returnValOnNull(state, false);
	zt_returnValOnNull(asset_manager, false);
	zt_returnValOnNull(materials, false);
	zt_returnValOnNull(is_complete, false);

	int tex_idx = state->asset_manager_file_indexes[state->textures_current++];
	const char *tex_name = asset_manager->asset_name[tex_idx];

	int type_idx = -1;
	zt_fize(_zt_modelMaterial_types) {
		if (zt_striEndsWith(tex_name, _zt_modelMaterial_types[i])) {
			type_idx = i;
			break;
		}
	}

	if (type_idx != -1) {
		const char *name_ptr = zt_strFindLast(tex_name, "/");
		int name_pos_type = zt_striFindPos(name_ptr, _zt_modelMaterial_types[type_idx], 0);

		if (name_ptr != nullptr && name_pos_type != ztStrPosNotFound) {
			char name[64];
			zt_strCpy(name, zt_elementsOf(name), name_ptr + 1, name_pos_type - 1);

			ztModelComponentMaterial *mcm = nullptr;

			zt_fiz(state->materials_current) {
				if (zt_striEquals(materials[i].name, name)) {
					mcm = &materials[i];
					break;
				}
			}

			if (mcm == nullptr) {
				zt_assert(state->materials_current < state->materials_total);

				mcm = &materials[state->materials_current++];
				zt_strCpy(mcm->name, zt_elementsOf(mcm->name), name);
				mcm->guid = zt_guidMake(0x681f6037, 0xc8b14034, 0xab755bcb, zt_strHash(mcm->name));
				mcm->material = zt_materialMake();
			}

			if (mcm != nullptr) {
				ztTextureID tex_id = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, tex_name), ztTextureFlags_MipMaps | ztTextureFlags_Repeat);
				if (tex_id != ztInvalidID) {
					switch (type_idx)
					{
						case 0: {
							mcm->material.diffuse_tex = tex_id;
							mcm->material.diffuse_flags = ztMaterialFlags_OwnsTexture;
						} break;

						case 1: {
							mcm->material.normal_tex = tex_id;
							mcm->material.normal_flags = ztMaterialFlags_OwnsTexture;
						} break;

						case 2: {
							mcm->material.specular_tex = tex_id;
							mcm->material.specular_flags = ztMaterialFlags_OwnsTexture;
						} break;

						case 3: {
							mcm->material.emissive_tex = tex_id;
							mcm->material.emissive_flags = ztMaterialFlags_OwnsTexture;
							mcm->material.emissive_strength = 1;
						}
					}
				}
				else {
					zt_logCritical("Unable to load texture: %s", tex_name);
					zt_strPrintf(error_buffer, error_buffer_len, "Unable to load texture: %s", tex_name);
					return false;
				}
			}
		}
		else {
			zt_assert(false); // this shouldn't happen
			zt_strPrintf(error_buffer, error_buffer_len, "Could not parse file name: %s", tex_name);
			return false;
		}
	}

	if (state->textures_current == state->textures_total) {
		*is_complete = true;
	}

	return true;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

i32 zt_modelComponentShaderLoaderQuery(ztModelComponentShaderLoaderState *state, ztAssetManager *asset_manager, const char **directories, i32 directories_count, const char **ignore, i32 ignore_count, ztModelComponentShader **shaders)
{
	zt_returnValOnNull(state, 0);
	zt_returnValOnNull(asset_manager, 0);
	zt_returnValOnNull(shaders, 0);

	zt_memSet(state, zt_sizeof(ztModelComponentMaterialLoaderState), 0);

	int shaders_to_load = 0;

	struct local
	{
		static bool shouldIgnore(const char *asset_name, const char **ignore, i32 ignore_count)
		{
			zt_fiz(ignore_count) {
				if (zt_strEquals(ignore[i], asset_name)) {
					return true;
				}
			}
			return false;
		}
	};

	zt_fiz(asset_manager->asset_count) {
		zt_fjze(directories) {
			if (zt_strStartsWith(asset_manager->asset_name[i], directories[j]) && !local::shouldIgnore(asset_manager->asset_name[i], ignore, ignore_count)) {
				shaders_to_load += 1;
			}
		}
	}

	state->shaders_total = shaders_to_load;
	state->shaders_current = 0;

	state->asset_manager_file_indexes = zt_mallocStructArray(i32, shaders_to_load);

	shaders_to_load = 0;

	zt_fiz(asset_manager->asset_count) {
		zt_fjze(directories) {
			if (zt_strStartsWith(asset_manager->asset_name[i], directories[j]) && !local::shouldIgnore(asset_manager->asset_name[i], ignore, ignore_count)) {
				state->asset_manager_file_indexes[shaders_to_load++] = i;
			}
		}
	}

	*shaders = zt_mallocStructArray(ztModelComponentShader, shaders_to_load);

	return shaders_to_load;
}

// ================================================================================================================================================================================================

void zt_modelComponentShaderLoaderFree(ztModelComponentShaderLoaderState *state)
{
	if (state == nullptr) {
		return;
	}

	if (state->asset_manager_file_indexes) {
		zt_free(state->asset_manager_file_indexes);
		state->asset_manager_file_indexes = nullptr;
	}
}

// ================================================================================================================================================================================================

bool zt_modelComponentShaderLoaderUpdate(ztModelComponentShaderLoaderState *state, ztAssetManager *asset_manager, ztModelComponentShader *shaders, bool *is_complete, char *error_buffer, i32 error_buffer_len)
{
	int shader_idx = state->shaders_current++;
	zt_assert(shader_idx < state->shaders_total);

	int shader_asset_idx = state->asset_manager_file_indexes[shader_idx];

	const char *shader_name = asset_manager->asset_name[shader_asset_idx];

	ztShaderID shader_id = zt_shaderMake(asset_manager, zt_assetLoad(asset_manager, shader_name));
	if (shader_id != ztInvalidID) {
		char name[64];
		zt_fileGetFileName(shader_name, name, zt_elementsOf(name));

		ztModelComponentShader *mcs = &shaders[shader_idx];
		zt_strCpy(mcs->name, zt_elementsOf(mcs->name), name);
		mcs->guid = zt_guidMake(0x36ace88f, 0x602e4893, 0xa5daaf8b, zt_strHash(shader_name));
		mcs->shader = shader_id;
	}
	else {
		return false;
	}

	if (state->shaders_current == state->shaders_total) {
		*is_complete = true;
	}

	return true;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_LIGHT_COMPONENT_GUID       zt_guidMake(0x3ba2f34c, 0x022044bd, 0xb8d0a97e, 0x0dd62224)
#define ZT_LIGHT_COMPONENT_NAME       "Light"

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_lightComponentMake)
{
	ZT_PROFILE_GAME("_zt_lightComponentMake");

	ztLightComponent *light_component = (ztLightComponent*)component->user_data;
	ztLight light = zt_lightMakeArea(ztVec3::zero);
	zt_lightComponentAdd(light_component, pool, entity_id, &light);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_lightComponentFree)
{
	ZT_PROFILE_GAME("_zt_lightComponentFree");

	ztLightComponent *light_component = (ztLightComponent*)component->user_data;
	zt_lightComponentRemove(light_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_lightComponentFind)
{
	ZT_PROFILE_GAME("_zt_lightComponentFind");

	ztLightComponent *light_component = (ztLightComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(light_component->lights_count) {
		if (light_component->entity_ids[i] == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztLightComponentGuiInfo
{
	ztLightComponent *light_component;
	ztComponentID     component_id;
	ztLight          *light;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_lightComponentGuiComboType)
{
	ZT_PROFILE_GAME("_zt_lightComponentGuiComboType");

	ztLightComponentGuiInfo *gui_info = (ztLightComponentGuiInfo *)user_data;

	// todo
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_lightComponentGui)
{
	ZT_PROFILE_GUI("_zt_lightComponentGui");

	//ztComponent *component, ztComponentID component_id, ztGuiItem *parent
	ztLightComponent *light_component = (ztLightComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < light_component->lights_count, nullptr);

	r32 padding = zt_guiPadding();

	ztLight *light = &light_component->lights[component_id];

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow, false);
	zt_guiSizerSizeParent(sizer, false, true);
	zt_guiSizerSizeToParent(sizer);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztLightComponentGuiInfo *gui_info = zt_mallocStructArena(ztLightComponentGuiInfo, sizer->gm->arena);
	gui_info->light_component = light_component;
	gui_info->component_id = component_id;
	gui_info->light = light;

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	const char *types[ztLightType_MAX] = { "Directional", "Spot", "Point" };
	ztGuiItem *combo_type = zt_guiMakeComboBox(sizer, zt_elementsOf(types));
	zt_fize(types) {
		zt_guiComboBoxAppend(combo_type, types[i]);

		if(light->type == (ztLightType_Enum)i) {
			zt_guiComboBoxSetSelected(combo_type, i);
		}
	}
	zt_guiComboBoxSetCallback(combo_type, ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentGuiComboType), gui_info);

	zt_componentGuiMakeItem(sizer, "Type:", combo_type);
	zt_componentGuiMakeEditor(sizer, "Position:", &light->position);
	zt_componentGuiMakeEditor(sizer, "Direction:", &light->direction);
	zt_componentGuiMakeEditor(sizer, "Casts Shadows:", &light->casts_shadows);

	//{
	//	const char *flags_names[] = {
	//		"Exclude From Culling",
	//	};
	//
	//	i32 flags[] = {
	//		ztSceneLightFlags_ExcludeFromCull,
	//	};
	//
	//	zt_componentGuiMakeFlagsEditor(sizer, "Flags:", flags_names, flags, zt_elementsOf(flags_names), &model->flags, 2);
	//}

	zt_componentGuiMakeEditor(sizer, "Color:", &light->color);
	zt_componentGuiMakeEditor(sizer, "Intensity:", &light->intensity);
	zt_componentGuiMakeEditor(sizer, "Ambient:", &light->ambient);
	zt_componentGuiMakeEditor(sizer, "Cutoff In:", &light->cutoff_in);
	zt_componentGuiMakeEditor(sizer, "Cutoff Out:", &light->cutoff_out);

	{
		ztGuiItem *sizer_ops = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);

		ztGuiItem *toggle_aabb = zt_guiMakeToggleButton(sizer_ops, "bounds", 0, &light_component->edit_show_bounds);
		zt_guiSizerAddItem(sizer_ops, toggle_aabb, 0, padding);
		zt_guiSizerAddStretcher(sizer_ops, 1, 0);

		zt_componentGuiMakeItem(sizer, "", sizer_ops);
	}

	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_LIGHT_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("LightComponent serialization failed."); return false; }

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_SAVE(_zt_lightComponentSave)
{
	ZT_PROFILE_GAME("_zt_lightComponentSave");

	ztLightComponent *light_component = (ztLightComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_LIGHT_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_LIGHT_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, light_component->lights_count));
		_serialCheck(zt_serialWrite(serial, light_component->edit_show_bounds));

		zt_fiz(light_component->lights_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, light_component->entity_ids[i]));

				if (light_component->entity_ids[i] != ztInvalidID) {
					ztLight *light = &light_component->lights[i];
					_serialCheck(zt_serialWrite(serial, light->type));
					_serialCheck(zt_serialWrite(serial, light->position));
					_serialCheck(zt_serialWrite(serial, light->direction));
					_serialCheck(zt_serialWrite(serial, light->casts_shadows));
					_serialCheck(zt_serialWrite(serial, light->color));
					_serialCheck(zt_serialWrite(serial, light->intensity));
					_serialCheck(zt_serialWrite(serial, light->ambient));
					_serialCheck(zt_serialWrite(serial, light->cutoff_in));
					_serialCheck(zt_serialWrite(serial, light->cutoff_out));
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_lightComponentLoad)
{
	ZT_PROFILE_GAME("_zt_lightComponentLoad");

	ztLightComponent *light_component = (ztLightComponent*)component->user_data;

	// clear out existing models from scene
	zt_fiz(light_component->lights_count) {
		if(light_component->entity_ids[i] == ztInvalidID) continue;

		if (zt_sceneHasLight(light_component->scene, &light_component->lights[i])) {
			zt_sceneRemoveLight(light_component->scene, &light_component->lights[i]);
		}
	}

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_LIGHT_COMPONENT_GUID) {
			zt_logCritical("LightComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_LIGHT_COMPONENT_FILE_VERSION) {
			zt_logCritical("LightComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		i32 lights_count = 0;
		_serialCheck(zt_serialRead(serial, &lights_count));
		_serialCheck(zt_serialRead(serial, &light_component->edit_show_bounds));

		zt_fiz(lights_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				ztEntityID entity_id = ztInvalidID;
				_serialCheck(zt_serialRead(serial, &entity_id));

				if (entity_id != ztInvalidID) {
					ztLight light = {};

					i32 light_type = 0;
					_serialCheck(zt_serialRead(serial, &light_type));
					light.type = (ztLightType_Enum)light_type;

					_serialCheck(zt_serialRead(serial, &light.position));
					_serialCheck(zt_serialRead(serial, &light.direction));
					_serialCheck(zt_serialRead(serial, &light.casts_shadows));
					_serialCheck(zt_serialRead(serial, &light.color));
					_serialCheck(zt_serialRead(serial, &light.intensity));
					_serialCheck(zt_serialRead(serial, &light.ambient));
					_serialCheck(zt_serialRead(serial, &light.cutoff_in));
					_serialCheck(zt_serialRead(serial, &light.cutoff_out));

					ztComponentID comp_idx = zt_lightComponentAdd(light_component, pool, entity_id, &light);
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_lightComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_lightComponentUpdate");

	ztLightComponent *light_component = (ztLightComponent *)component->user_data;

	if (pool->editor) {

		if (light_component->edit_last_active_light != nullptr) {
			ztEntityID active_entity = zt_entityEditorGetActiveEntity(pool->editor);
			if (active_entity != light_component->edit_last_active_entity) {
				if (!light_component->edit_ignore_entity_change) {
					light_component->edit_last_active_light = nullptr;
				}
				light_component->edit_ignore_entity_change = false;
				light_component->edit_last_active_entity = active_entity;
			}
			else {
				if (light_component->edit_copy_active_light.casts_shadows != light_component->edit_last_active_light->casts_shadows) {
					zt_sceneRemoveLight(light_component->scene, light_component->edit_last_active_light);
					zt_sceneAddLight(light_component->scene, light_component->edit_last_active_light, 1024, ztSceneLightFlags_ExcludeFromCull);
					zt_memCpy(&light_component->edit_copy_active_light, zt_sizeof(ztLight), light_component->edit_last_active_light, zt_sizeof(ztLight));
				}
			}

			zt_modelEditWidgetUpdate(&light_component->edit_widget, input_keys, input_mouse, camera, dt);
		}
	}

	return true;
}

// ================================================================================================================================================================================================

ztInternal r32 _zt_lightComponentLightSizeAtOrigin(ztLight *light)
{
	return zt_clamp(light->intensity * .1f, .25f, 1.5f);
}

// ================================================================================================================================================================================================

ztInternal bool _zt_lightComponentFindLightAndIntersectPoint(ztLightComponent *light_component, const ztVec3 &ray_pos, const ztVec3 &ray_dir, ztEntityID *entity_id, ztLight **light, ztVec3 *intersect_point, i32 *closest_id, r32 *closest_dist)
{
	r32 closest_time = ztReal32Max;
	i32 closest_idx = -1;
	ztVec3 closest_pos = ztVec3::zero;

	zt_fiz(light_component->lights_count) {
		if (light_component->entity_ids[i] == ztInvalidID) {
			continue;
		}

		ztLight *light = &light_component->lights[i];

		r32 intersect_time = ztReal32Max;
		ztVec3 intersect_pos = ztVec3::zero;
		if (zt_collisionRayInSphere(ray_pos, ray_dir, light->position, _zt_lightComponentLightSizeAtOrigin(light), &intersect_time, &intersect_pos)) {
			if (intersect_time < closest_time) {
				closest_time = intersect_time;
				closest_idx = i;
				closest_pos = intersect_pos;
			}
		}
	}

	if (closest_idx >= 0) {
		if (closest_id) *closest_id = closest_idx;
		if (closest_dist) *closest_dist = ray_pos.distance(closest_pos);

		if (entity_id) *entity_id = light_component->entity_ids[closest_idx];
		if (light) *light = &light_component->lights[closest_idx];
		if (intersect_point) *intersect_point = closest_pos;

		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK(_zt_lightComponentEditQueryClick)
{
	ZT_PROFILE_GAME("_zt_lightComponentEditQueryClick");

	ztLightComponent *light_component = (ztLightComponent *)component->user_data;

	if (light_component->edit_last_active_light != nullptr) {
		if (zt_modelEditWidgetIsMouseWithinBounds(&light_component->edit_widget, camera, input_mouse->screen_x, input_mouse->screen_y)) {
			*closest_id = -100;
			*closest_dist = ztReal32Min; // this always needs processed with priority
			return true;
		}
	}

	light_component->edit_last_active_light = nullptr;
	light_component->edit_last_active_entity = ztInvalidID;

	r32 close_dist = ztReal32Max;
	i32 close_idx = -1;
	ztVec3 close_pos = ztVec3::zero;

	_zt_lightComponentFindLightAndIntersectPoint(light_component, ray_pos, ray_dir, nullptr, nullptr, &close_pos, &close_idx, &close_dist);

	if (close_idx >= 0) {
		*closest_id = close_idx;
		*closest_dist = ray_pos.distance(close_pos);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK(_zt_lightComponentEditProcessClick)
{
	ZT_PROFILE_GAME("_zt_lightComponentEditProcessClick");

	ztLightComponent *light_component = (ztLightComponent *)component->user_data;

	if (closest_id != -100) {
		if (light_component->edit_last_active_light != &light_component->lights[closest_id]) {
			light_component->edit_last_active_light = &light_component->lights[closest_id];
			zt_memCpy(&light_component->edit_copy_active_light, zt_sizeof(ztLight), light_component->edit_last_active_light, zt_sizeof(ztLight));

			light_component->edit_ignore_entity_change = true;
			zt_entityEditorMakeEntityActive(pool->editor, light_component->edit_last_active_entity);
		}
	}
	else if(light_component->edit_last_active_light != nullptr) {
		light_component->edit_last_active_light->position = light_component->edit_widget_transform.position;
		light_component->edit_last_active_light->direction = light_component->edit_widget_transform.rotation.euler();
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_ALL(_zt_lightComponentEditDrawDebugAll)
{
	ZT_PROFILE_GAME("_zt_lightComponentEditDrawDebugAll");

	ztLightComponent *light_component = (ztLightComponent *)component->user_data;

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefaultWhite);

	bool active_found = false;

	zt_fiz(light_component->lights_count) {
		if (light_component->entity_ids[i] == ztInvalidID) continue;

		ztLight *light = &light_component->lights[i];

		zt_drawListPushColor(draw_list, light->color);
		zt_drawListAddEmptySimpleSphere(draw_list, light->position, _zt_lightComponentLightSizeAtOrigin(light), 8, 2);
		zt_drawListPopColor(draw_list);

		if (light_component->edit_show_bounds) {
			zt_drawListPushColor(draw_list, ztColor_White);
			zt_drawListAddEmptySimpleSphere(draw_list, light->position, light->intensity * .8f, 16, 4);
			zt_drawListPopColor(draw_list);
		}

		if (light_component->entity_ids[i] == active_entity_id) {
			active_found = true;

			if (light_component->edit_last_active_light == nullptr) {
				light_component->edit_last_active_entity = light_component->entity_ids[i];
				light_component->edit_last_active_light = &light_component->lights[i];
				zt_memCpy(&light_component->edit_copy_active_light, zt_sizeof(ztLight), light_component->edit_last_active_light, zt_sizeof(ztLight));

				light_component->edit_widget_transform.position = light_component->edit_last_active_light->position;
				light_component->edit_widget_transform.rotation = ztQuat::makeFromEuler(light_component->edit_last_active_light->direction);

				zt_modelEditWidgetFree(&light_component->edit_widget);
				zt_modelEditWidgetMake(&light_component->edit_widget, &light_component->edit_widget_transform);

				light_component->edit_widget_transform.position = light_component->edit_last_active_light->position;
				light_component->edit_widget_transform.rotation = ztQuat::makeFromEuler(light_component->edit_last_active_light->direction);
				light_component->edit_widget_transform.scale = ztVec3::one;
			}
			else {
				light_component->edit_last_active_light->position = light_component->edit_widget_transform.position;
				light_component->edit_last_active_light->direction = light_component->edit_widget_transform.rotation.euler();
			}
		}
	}
	if (light_component->edit_last_active_light != nullptr) {
		if (!active_found) {
			light_component->edit_last_active_light = nullptr;
		}
		else {
			zt_modelEditWidgetRender(&light_component->edit_widget, camera, draw_list);
		}
	}
	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);

}

// ================================================================================================================================================================================================

bool zt_lightComponentMakeAndRegister(ztLightComponent *light_component, ztEntityPool *pool, ztScene *scene, ztModelComponent *model_component)
{
	ZT_PROFILE_GAME("zt_lightComponentMakeAndRegister");

	zt_returnValOnNull(light_component, false);
	zt_returnValOnNull(pool, false);
	zt_returnValOnNull(scene, false);

	light_component->lights_count = 0;

	zt_fize(light_component->entity_ids) {
		light_component->entity_ids[i] = ztInvalidID;
	}

	light_component->edit_last_active_light = nullptr;
	light_component->edit_last_active_entity = ztInvalidID;
	light_component->edit_show_bounds = true;
	light_component->edit_ignore_entity_change = false;

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_LIGHT_COMPONENT_GUID, ZT_LIGHT_COMPONENT_NAME, light_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentUpdate), &component) < 0) {

		return false;
	}

	component->component_edit_query_click = ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentEditQueryClick);
	component->component_edit_process_click = ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentEditProcessClick);
	component->component_edit_draw_debug_all = ZT_FUNCTION_POINTER_TO_VAR(_zt_lightComponentEditDrawDebugAll);

	light_component->scene = scene;

	return true;
}

// ================================================================================================================================================================================================

void zt_lightComponentFreeAndUnregister(ztLightComponent *light_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_lightComponentFreeAndUnregister");

	if (light_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_LIGHT_COMPONENT_GUID);

	zt_fiz(light_component->lights_count) {
		if (light_component->entity_ids[i] == ztInvalidID) {
			continue;
		}

		if (zt_sceneHasLight(light_component->scene, &light_component->lights[i])) {
			zt_sceneRemoveLight(light_component->scene, &light_component->lights[i]);
		}

		light_component->entity_ids[i] = ztInvalidID;
	}

	zt_modelEditWidgetFree(&light_component->edit_widget);

	zt_memSet(light_component, zt_sizeof(ztLightComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_lightComponentAdd(ztLightComponent *light_component, ztEntityPool *pool, ztEntityID entity_id, ztLight *light)
{
	ZT_PROFILE_GAME("zt_lightComponentAdd");

	zt_returnValOnNull(light_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);
	zt_assertReturnValOnFail(entity_id != ztInvalidID, ztInvalidID);

	zt_fize(light_component->lights) {
		if (light_component->entity_ids[i] == ztInvalidID) {
			light_component->entity_ids[i] = entity_id;
			light_component->lights_count = zt_max(light_component->lights_count, i + 1);

			zt_memCpy(&light_component->lights[i], zt_sizeof(ztLight), light, zt_sizeof(ztLight));
			zt_sceneAddLight(light_component->scene, &light_component->lights[i], 1024, ztSceneLightFlags_ExcludeFromCull);
			zt_entityAddedComponent(pool, entity_id, ZT_LIGHT_COMPONENT_GUID, i);

			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_lightComponentRemove(ztLightComponent *light_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_lightComponentRemove");

	ztLight *light = &light_component->lights[component_id];

	light_component->entity_ids[component_id] = ztInvalidID;

	if (light_component->lights_count - 1 == component_id) {
		light_component->lights_count -= 1;
	}

	if (zt_sceneHasLight(light_component->scene, light)) {
		zt_sceneRemoveLight(light_component->scene, light);
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_LIGHT_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

ztLight *zt_lightComponentGet(ztLightComponent *light_component, ztEntityPool *pool, ztEntityID entity, int which_idx, ztComponentID *component_id_out)
{
	ZT_PROFILE_GAME("zt_lightComponentGet");

	if (component_id_out) {
		*component_id_out = ztInvalidID;
	}

	zt_returnValOnNull(light_component, nullptr);
	zt_returnValOnNull(pool, nullptr);

	zt_fiz(light_component->lights_count) {
		if (light_component->entity_ids[i] == entity) {
			if (which_idx-- <= 0) {

				if (component_id_out) {
					*component_id_out = i;
				}
				return &light_component->lights[i];
			}
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

ztLight *zt_lightComponentGet(ztLightComponent *light_component, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_lightComponentGet");

	zt_returnValOnNull(light_component, nullptr);
	zt_assertReturnValOnFail(component_id >= 0 && component_id < light_component->lights_count, nullptr);

	return &light_component->lights[component_id];
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================

struct ztGuiCollisionGeometryEditorInfo
{
	ztEntityID             entity_id;
	ztModelComponent      *model_component;
	ztModel               *model;
	ztEntityPool          *pool;
	ztCollisionGeometry   *geo;
	ztGuiItem             *combo;
	ztGuiItem             *editor_sizer;
	i32                    last_selected;
	bool                   auto_adjust;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiCollisionGeometryEditorCreateEditors(ztGuiCollisionGeometryEditorInfo *info)
{
	ZT_PROFILE_GUI("_zt_guiCollisionGeometryEditorCreateEditors");

	i32 selected = zt_guiComboBoxGetSelected(info->combo);
	if (selected == info->last_selected) {
		return;
	}

	zt_guiSizerRemoveAllItems(info->editor_sizer);

	r32 padding = zt_guiPadding();


	switch (selected)
	{
		case ztCollisionGeometryType_AxisAlignedBox: {
			if (info->auto_adjust && info->model) {
				zt_modelGetAABB(info->model, &info->geo->aabb_center, &info->geo->aabb_extents);
			}

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Center:"), 0, padding);
			ztGuiItem *edit_center = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->aabb_center, ztVec3::min, ztVec3::max, .25f, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_center, 0, padding);

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Extents:"), 0, padding);
			ztGuiItem *edit_extents = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->aabb_extents, ztVec3::zero, ztVec3::max, .25f, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_extents, 0, padding);
		} break;

		case ztCollisionGeometryType_OrientedBox: {
			if (info->auto_adjust && info->model) {
				zt_modelGetOBB(info->model, &info->geo->obb_center, &info->geo->obb_extents);
				info->geo->obb_rotation = ztQuat::identity;
			}

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Center:"), 0, padding);
			ztGuiItem *edit_center = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->obb_center, ztVec3::min, ztVec3::max, .25f, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_center, 0, padding);

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Extents:"), 0, padding);
			ztGuiItem *edit_extents = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->obb_extents, ztVec3::zero, ztVec3::max, .25f, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_extents, 0, padding);

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Rotation:"), 0, padding);
			ztGuiItem *edit_rotation = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->obb_rotation, ztVec3::min, ztVec3::max, 1, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_rotation, 0, padding);
		} break;

		case ztCollisionGeometryType_Sphere: {
			if (info->auto_adjust && info->model) {
				ztVec3 aabb_center, aabb_extents;
				zt_modelGetAABB(info->model, &aabb_center, &aabb_extents);

				info->geo->sphere_center = aabb_center;
				info->geo->sphere_radius = aabb_extents.length() * .5f;
			}

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Center:"), 0, padding);
			ztGuiItem *edit_center = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->sphere_center, ztVec3::min, ztVec3::max, .25f, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_center, 0, padding);

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Radius:"), 0, padding);
			ztGuiItem *edit_radius = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->sphere_radius, 0, ztReal32Max, .25f);
			zt_guiSizerAddItem(info->editor_sizer, edit_radius, 0, padding);
		} break;

		case ztCollisionGeometryType_Capsule: {
			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Center:"), 0, padding);
			ztGuiItem *edit_center = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->capsule_center, ztVec3::min, ztVec3::max, .25f, false);
			zt_guiSizerAddItem(info->editor_sizer, edit_center, 0, padding);

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Radius:"), 0, padding);
			ztGuiItem *edit_radius = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->capsule_radius, 0, ztReal32Max, .25f);
			zt_guiSizerAddItem(info->editor_sizer, edit_radius, 0, padding);

			zt_guiSizerAddItem(info->editor_sizer, zt_guiMakeStaticText(info->editor_sizer, "Height:"), 0, padding);
			ztGuiItem *edit_height = zt_guiMakeEditor(info->editor_sizer, nullptr, &info->geo->capsule_height, 0, ztReal32Max, .25f);
			zt_guiSizerAddItem(info->editor_sizer, edit_height, 0, padding);
		} break;

		case ztCollisionGeometryType_Triangles: {
			if (info->auto_adjust && info->model == nullptr) {
				info->model = zt_modelComponentGet(info->model_component, info->pool, info->entity_id);
			}

			if (info->model) {
				i32 vertices_count = zt_modelGetVertices(info->model, nullptr, 0, ztModelGetVerticesTransform_NoTransform);

				zt_strMakePrintf(tri_count, 128, "Triangles: %d", zt_convertToi32Floor(vertices_count / 3.f));
				ztGuiItem *tri_label = zt_guiMakeStaticText(info->editor_sizer, tri_count);
				zt_guiSizerAddItem(info->editor_sizer, tri_label, 0, padding);

				ztVec3 *vertices = zt_mallocStructArrayArena(ztVec3, vertices_count, zt_memGetTempArena()); // collision geo copies the vertices, so we only need temporary memory here
				zt_modelGetVertices(info->model, vertices, vertices_count, ztModelGetVerticesTransform_NoTransform);

				zt_collisionGeometryMakeTriangles(info->geo, vertices, vertices_count);

				zt_freeArena(vertices, zt_memGetTempArena());
			}
			else {
				ztGuiItem *tri_label = zt_guiMakeStaticText(info->editor_sizer, "No valid model on entity");
				zt_guiSizerAddItem(info->editor_sizer, tri_label, 0, padding);
			}
		} break;
	}

	info->geo->type = (ztCollisionGeometryType_Enum)selected;

	info->last_selected = selected;

	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(info->editor_sizer));
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiCollisionGeometryEditorCombo)
{
	ZT_PROFILE_GUI("_zt_guiCollisionGeometryEditorCombo");

	ztGuiCollisionGeometryEditorInfo *info = (ztGuiCollisionGeometryEditorInfo *)user_data;
	zt_collisionGeometryFree(info->geo);
	info->geo->type = (ztCollisionGeometryType_Enum)selected;
	_zt_guiCollisionGeometryEditorCreateEditors(info);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, ztCollisionGeometry *geo, ztModel *model, ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity_id, bool auto_adjust)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	r32 padding = zt_guiPadding();
	ztGuiItem *sizer = zt_guiMakeSizer(parent, ztGuiItemOrient_Vert);

	ztGuiCollisionGeometryEditorInfo *info = zt_mallocStructArena(ztGuiCollisionGeometryEditorInfo, parent->gm->arena);

	ztGuiItem *combo = zt_guiMakeComboBox(sizer, ztCollisionGeometryType_MAX);
	zt_guiComboBoxSetCallback(combo, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCollisionGeometryEditorCombo), info);

	zt_guiMakePanel(combo, 0, info, parent->gm->arena); // make sure info is deleted

	const char *names[ztCollisionGeometryType_MAX] = { "Axis Aligned Bounding Box", "Oriented Bounding Box", "Sphere", "Capsule", "Triangles" };

	zt_fize(names) {
		zt_guiComboBoxAppend(combo, names[i], info);

		if (geo->type == (ztCollisionGeometryType_Enum)i) {
			zt_guiComboBoxSetSelected(combo, i);
		}
	}

	zt_guiSizerAddItem(sizer, combo, 0, padding);

	ztGuiItem *sizer_edits = zt_guiMakeColumnSizer(sizer, 2, ztGuiColumnSizerType_FillRow);
	zt_guiSizerAddItem(sizer, sizer_edits, 1, padding);

	zt_guiColumnSizerSetProp(sizer_edits, 1, 1);

	info->geo = geo;
	info->combo = combo;
	info->editor_sizer = sizer_edits;
	info->model = model;
	info->model_component = model_component;
	info->pool = pool;
	info->entity_id = entity_id;

	info->last_selected = -1;

	_zt_guiCollisionGeometryEditorCreateEditors(info);

	return sizer;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztCollisionGeoGuiInfo
{
	ztModel             *model;
	ztModelComponent    *model_component;
	ztEntityPool        *pool;
	ztEntityID           entity_id;
	ztCollisionGeometry *geometries;
	int                 *geometries_count;
	int                  geometries_size;
	ztGuiItem           *listbox;
	ztGuiItem           *detailed_bounds_sizer;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_LISTBOX_ITEM_SELECTED(_zt_collisionGeoGuiListBox)
{
	ZT_PROFILE_GUI("_zt_collisionGeoGuiListBox");

	ztCollisionGeoGuiInfo *gui_info = (ztCollisionGeoGuiInfo*)user_data;

	zt_guiSizerRemoveAllItems(gui_info->detailed_bounds_sizer);

	ztGuiItem *editor = zt_guiMakeEditor(gui_info->detailed_bounds_sizer, &gui_info->geometries[selected], gui_info->model, gui_info->model_component, gui_info->pool, gui_info->entity_id, false);
	zt_guiSizerAddItem(gui_info->detailed_bounds_sizer, editor, 1, zt_guiPadding());
	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor));
}

// ================================================================================================================================================================================================

ztInternal void _zt_collisionGeoUpdateBoundsList(ztCollisionGeoGuiInfo *gui_info)
{
	ZT_PROFILE_GUI("_zt_collisionGeoUpdateBoundsList");

	int selected = zt_guiListBoxGetSelected(gui_info->listbox);

	zt_guiListBoxClear(gui_info->listbox);

	zt_fiz(*gui_info->geometries_count) {
		zt_strMakePrintf(label, 64, "Collider %d", i + 1);
		zt_guiListBoxAppend(gui_info->listbox, label, gui_info);
	}

	if (selected >= 0) {
		selected = zt_min(selected, *gui_info->geometries_count - 1);
		zt_guiListBoxSetSelected(gui_info->listbox, selected);
	}

	if (*gui_info->geometries_count == 0) {
		zt_guiSizerRemoveAllItems(gui_info->detailed_bounds_sizer);
		zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(gui_info->detailed_bounds_sizer));
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_collisionGeoGuiButtonAddBounds)
{
	ZT_PROFILE_GUI("_zt_collisionGeoGuiButtonAddBounds");

	ztCollisionGeoGuiInfo *gui_info = (ztCollisionGeoGuiInfo*)user_data;

	if (*gui_info->geometries_count >= gui_info->geometries_size) {
		return;
	}

	int idx = (*gui_info->geometries_count)++;
	gui_info->geometries[idx].type = ztCollisionGeometryType_OrientedBox;
	gui_info->geometries[idx].obb_center = ztVec3::zero;
	gui_info->geometries[idx].obb_extents = ztVec3::one;

	if (gui_info->model) {
		zt_modelGetOBB(gui_info->model, &gui_info->geometries[idx].obb_center, &gui_info->geometries[idx].obb_extents);
	}

	_zt_collisionGeoUpdateBoundsList(gui_info);
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_collisionGeoGuiButtonRemBounds)
{
	ZT_PROFILE_GUI("_zt_collisionGeoGuiButtonRemBounds");

	ztCollisionGeoGuiInfo *gui_info = (ztCollisionGeoGuiInfo*)user_data;

	int selected = zt_guiListBoxGetSelected(gui_info->listbox);

	if (*gui_info->geometries_count == selected + 1) {
		*gui_info->geometries_count -= 1;
	}
	else {
		for (int i = selected; i < *gui_info->geometries_count - 1; ++i) {
			zt_memCpy(&gui_info->geometries[i], zt_sizeof(ztCollisionGeometry), &gui_info->geometries[i + 1], zt_sizeof(ztCollisionGeometry));
		}
		*gui_info->geometries_count -= 1;
	}

	_zt_collisionGeoUpdateBoundsList(gui_info);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, ztModel *model, ztModelComponent *model_component, ztEntityPool *pool, ztEntityID entity_id, ztCollisionGeometry *geometries, int *geometries_count, int geometries_size)
{
	r32 padding = zt_guiPadding();

	ztGuiItem *main_sizer = zt_guiMakeSizer(parent, ztGuiItemOrient_Vert);

	ztGuiItem *listsizer = zt_guiMakeSizer(parent, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(main_sizer, listsizer, 1, padding);

	ztCollisionGeoGuiInfo *gui_info = zt_mallocStructArena(ztCollisionGeoGuiInfo, parent->gm->arena);
	ztGuiItem *gui_info_panel = zt_guiMakePanel(listsizer, 0, gui_info, parent->gm->arena);

	gui_info->model = model;
	gui_info->model_component = model_component;
	gui_info->pool = pool;
	gui_info->entity_id = entity_id;
	gui_info->geometries = geometries;
	gui_info->geometries_count = geometries_count;
	gui_info->geometries_size = geometries_size;

	ztGuiItem *listbox = zt_guiMakeListBox(listsizer, 0, geometries_size);
	listbox->min_size.y = 1.f;
	zt_guiSizerAddItem(listsizer, listbox, 1, padding);
	zt_guiListBoxSetCallback(listbox, ZT_FUNCTION_POINTER_TO_VAR(_zt_collisionGeoGuiListBox), gui_info);
	gui_info->listbox = listbox;

	ztGuiItem *sizer_ops = zt_guiMakeSizer(listsizer, ztGuiItemOrient_Vert);
	zt_guiSizerAddItem(listsizer, sizer_ops, 0, padding);

	ztGuiItem *btn_new = zt_guiMakeButton(sizer_ops, "+", 0, nullptr);
	zt_guiSizerAddItem(sizer_ops, btn_new, 0, padding);
	zt_guiButtonSetCallback(btn_new, ZT_FUNCTION_POINTER_TO_VAR(_zt_collisionGeoGuiButtonAddBounds), gui_info);
	ztGuiItem *btn_del = zt_guiMakeButton(sizer_ops, "-", 0, nullptr);
	zt_guiSizerAddItem(sizer_ops, btn_del, 0, padding);
	zt_guiButtonSetCallback(btn_del, ZT_FUNCTION_POINTER_TO_VAR(_zt_collisionGeoGuiButtonRemBounds), gui_info);

	ztGuiItem *detailed_bounds_sizer = zt_guiMakeSizer(main_sizer, ztGuiItemOrient_Vert);
	zt_guiSizerAddItem(main_sizer, detailed_bounds_sizer, 0, padding);
	gui_info->detailed_bounds_sizer = detailed_bounds_sizer;

	_zt_collisionGeoUpdateBoundsList(gui_info);

	return main_sizer;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_RIGID_BODY_COMPONENT_GUID       zt_guidMake(0xee435e72, 0xc31d485d, 0x902ad11f, 0x7646f882)
#define ZT_RIGID_BODY_COMPONENT_NAME       "RigidBody"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_rigidBodyComponentMake)
{
	ZT_PROFILE_GUI("_zt_rigidBodyComponentMake");

	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;
	zt_rigidBodyComponentAdd(rigid_body_component, pool, entity_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_rigidBodyComponentFree)
{
	ZT_PROFILE_GUI("_zt_rigidBodyComponentFree");

	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;
	zt_rigidBodyComponentRemove(rigid_body_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_rigidBodyComponentFind)
{
	ZT_PROFILE_GUI("_zt_rigidBodyComponentFind");

	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(rigid_body_component->rigid_bodies_count) {
		if (rigid_body_component->entity_ids[i] == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztRigidBodyComponentGuiInfo
{
	ztRigidBodyComponent *rigid_body_component;
	ztComponentID         component_id;
	ztEntityID            entity_id;
	ztGuiItem            *details_editor;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_rigidBodyGuiComboCollisionLayer)
{
	ZT_PROFILE_GUI("_zt_rigidBodyGuiComboCollisionLayer");

	ztRigidBodyComponentGuiInfo *gui_info = (ztRigidBodyComponentGuiInfo*)user_data;

	gui_info->rigid_body_component->rigid_bodies[gui_info->component_id].collision_layer = selected;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_rigidBodyComponentGui)
{
	ZT_PROFILE_GUI("_zt_rigidBodyComponentGui");

	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < rigid_body_component->rigid_bodies_count, nullptr);

	r32 padding = zt_guiPadding();

	ztRigidBody *rigid_body = &rigid_body_component->rigid_bodies[component_id];

	ztGuiItem *main_sizer = zt_guiMakeSizer(parent, ztGuiItemOrient_Vert, false);
	zt_guiSizerSizeParent(main_sizer, false, true);
	zt_guiSizerSizeToParent(main_sizer);

	ztGuiItem *collapsing = zt_guiMakeCollapsingPanel(main_sizer, "Values");
	zt_guiCollapsingPanelCollapse(collapsing);
	zt_guiSizerAddItem(main_sizer, collapsing, 1, padding);
	{
		ztGuiItem *collapsing_sizer = zt_guiMakeColumnSizer(zt_guiCollapsingPanelGetContentParent(collapsing), 2, ztGuiColumnSizerType_FillRow);

		zt_guiColumnSizerSetProp(collapsing_sizer, 0, 0);
		zt_guiColumnSizerSetProp(collapsing_sizer, 1, 1);

		zt_componentGuiMakeEditor(collapsing_sizer, "Velocity:", &rigid_body->velocity);
		zt_componentGuiMakeEditor(collapsing_sizer, "Angular Velocity:", &rigid_body->angular_velocity);
		zt_componentGuiMakeEditor(collapsing_sizer, "Acceleration:", &rigid_body->acceleration);
		zt_componentGuiMakeEditor(collapsing_sizer, "Force Accum:", &rigid_body->force_accum);
		zt_componentGuiMakeEditor(collapsing_sizer, "Torque Accum:", &rigid_body->torque_accum);
		zt_componentGuiMakeEditor(collapsing_sizer, "Prev Acceleration:", &rigid_body->prev_acceleration);
	}

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztRigidBodyComponentGuiInfo *gui_info = zt_mallocStructArena(ztRigidBodyComponentGuiInfo, sizer->gm->arena);
	gui_info->rigid_body_component = rigid_body_component;
	gui_info->component_id = component_id;
	gui_info->entity_id = rigid_body_component->entity_ids[component_id];

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	zt_guiSizerAddItem(main_sizer, sizer, 0, 0);

	{
		zt_componentGuiMakeEditor(sizer, "Damping:", &rigid_body->damping);
		zt_componentGuiMakeEditor(sizer, "Angular Damping:", &rigid_body->angular_damping);
		zt_componentGuiMakeEditor(sizer, "Inverse Mass:", &rigid_body->inverse_mass);
		zt_componentGuiMakeEditor(sizer, "Force Gravity:", &rigid_body->force_gravity);
	}

	{
		const char *flags_names[] = {
			"Static (Immovable)",
			"Never Sleep",
		};

		i32 flags[] = {
			ztRigidBodyFlags_Static,
			ztRigidBodyFlags_NeverSleep,
		};

		zt_componentGuiMakeFlagsEditor(sizer, "Flags:", flags_names, flags, zt_elementsOf(flags_names), &rigid_body->flags, 2);
	}
	{
		ztGuiItem *combo_layers = zt_guiMakeComboBox(sizer, rigid_body_component->collision_layers_count);
		zt_fiz(rigid_body_component->collision_layers_count) {
			zt_guiComboBoxAppend(combo_layers, rigid_body_component->collision_layers[i]);

			if (rigid_body->collision_layer == i) {
				zt_guiComboBoxSetSelected(combo_layers, i);
			}
		}
		zt_guiComboBoxSetCallback(combo_layers, ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyGuiComboCollisionLayer), gui_info);

		zt_componentGuiMakeItem(sizer, "Collision Layer:", combo_layers);
	}

	if (rigid_body_component->collision_layers_count > 0) {
		const char *flags_names[32];
		i32 flags[32];

		zt_fiz(rigid_body_component->collision_layers_count) {
			flags_names[i] = rigid_body_component->collision_layers[i];
			flags[i] = zt_bit(i);
		}

		zt_componentGuiMakeFlagsEditor(sizer, "Collides With:", flags_names, flags, rigid_body_component->collision_layers_count, &rigid_body->collides_with_layers, 2);
	}

	{
		ztGuiItem *editor = zt_guiMakeEditor(sizer, &rigid_body->cg_bounding, rigid_body->model, rigid_body_component->model_component, rigid_body_component->pool, rigid_body_component->entity_ids[component_id], true);
		zt_componentGuiMakeItem(sizer, "Bounds:", editor);
	}

	{
		ztGuiItem *editor = zt_guiMakeEditor(sizer, rigid_body->model, rigid_body_component->model_component, rigid_body_component->pool, rigid_body_component->entity_ids[component_id], rigid_body->cg_details, &rigid_body->cg_details_count, zt_elementsOf(rigid_body->cg_details));
		zt_componentGuiMakeItem(sizer, "Colliders:", editor);
	}


	return main_sizer;
 }

// ================================================================================================================================================================================================

#define ZT_RIGID_BODY_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("RigidBodyComponent serialization failed."); return false; }


ZT_FUNC_COMPONENT_SAVE(_zt_rigidBodyComponentSave)
{
	ZT_PROFILE_GAME("_zt_rigidBodyComponentSave");

	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_RIGID_BODY_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_RIGID_BODY_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, rigid_body_component->rigid_bodies_count));

		zt_fiz(rigid_body_component->rigid_bodies_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, rigid_body_component->entity_ids[i]));

				if (rigid_body_component->entity_ids[i] != ztInvalidID) {
					ztRigidBody *rigid_body = &rigid_body_component->rigid_bodies[i];
					_serialCheck(zt_rigidBodySave(serial, rigid_body));
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_rigidBodyComponentLoad)
{
	ZT_PROFILE_GAME("_zt_rigidBodyComponentLoad");
	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_RIGID_BODY_COMPONENT_GUID) {
			zt_logCritical("RigidBodyComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_RIGID_BODY_COMPONENT_FILE_VERSION) {
			zt_logCritical("RigidBodyComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		_serialCheck(zt_serialRead(serial, &rigid_body_component->rigid_bodies_count));

		zt_fiz(rigid_body_component->rigid_bodies_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialRead(serial, &rigid_body_component->entity_ids[i]));

				if (rigid_body_component->entity_ids[i] != ztInvalidID) {
					ztRigidBody *rigid_body = &rigid_body_component->rigid_bodies[i];
					_serialCheck(zt_rigidBodyLoad(serial, rigid_body));
					rigid_body->model = zt_modelComponentGet(rigid_body_component->model_component, pool, rigid_body_component->entity_ids[i]);
					zt_entityAddedComponent(pool, rigid_body_component->entity_ids[i], ZT_RIGID_BODY_COMPONENT_GUID, i);
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_rigidBodyComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_rigidBodyComponentUpdate");

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_rigidBodyComponentEditDrawDebug)
{
	ZT_PROFILE_GAME("_zt_rigidBodyComponentEditDrawDebug");

	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;
	zt_assertReturnOnFail(active_component_id >= 0 && active_component_id < rigid_body_component->rigid_bodies_count);

	ztRigidBody *rigid_body = &rigid_body_component->rigid_bodies[active_component_id];

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	zt_drawListPushColor(draw_list, ztColor_Orange);
	zt_collisionGeometryRenderDebug(&rigid_body->cg_bounding, draw_list, rigid_body->model ? rigid_body->model->transform.position : ztVec3::zero, rigid_body->model ? rigid_body->model->calculated_mat : ztMat4::identity);
	zt_drawListPopColor(draw_list);

	static ztColor colors[] = {ztColor_Yellow, ztColor_Purple, ztColor_Green, ztColor_Blue};

	zt_fiz(rigid_body->cg_details_count) {
		zt_drawListPushColor(draw_list, colors[i % zt_elementsOf(colors)]);
		zt_collisionGeometryRenderDebug(&rigid_body->cg_details[i], draw_list, rigid_body->model ? rigid_body->model->transform.position : ztVec3::zero, rigid_body->model ? rigid_body->model->calculated_mat : ztMat4::identity);
		zt_drawListPopColor(draw_list);
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_NOTIFY_CHANGE(_zt_rigidBodyComponentNotifyChange)
{
	ZT_PROFILE_GAME("_zt_rigidBodyComponentNotifyChange");

	// we need to make sure we update the model pointer if the model component is changed or removed
	ztRigidBodyComponent *rigid_body_component = (ztRigidBodyComponent*)component->user_data;
	rigid_body_component->rigid_bodies[component_id].model = zt_modelComponentGet(rigid_body_component->model_component, rigid_body_component->pool, entity_id);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_rigidBodyComponentMakeAndRegister(ztRigidBodyComponent *rigid_body_component, i32 pool_size, ztEntityPool *pool, ztModelComponent *model_component, const char ** collision_layers, i32 collision_layers_size)
{
	ZT_PROFILE_GAME("zt_rigidBodyComponentMakeAndRegister");

	zt_returnValOnNull(rigid_body_component, false);
	zt_returnValOnNull(pool, false);

	rigid_body_component->collision_layers_count = collision_layers_size;
	zt_fiz(collision_layers_size) {
		rigid_body_component->collision_layers[i] = zt_stringMakeFrom(collision_layers[i]);
	}

	rigid_body_component->rigid_bodies = zt_mallocStructArray(ztRigidBody, pool_size);
	rigid_body_component->rigid_bodies_size = pool_size;
	rigid_body_component->rigid_bodies_count = 0;

	rigid_body_component->entity_ids = zt_mallocStructArray(ztEntityID, pool_size);
	zt_fiz(pool_size) {
		rigid_body_component->entity_ids[i] = ztInvalidID;
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_RIGID_BODY_COMPONENT_GUID, ZT_RIGID_BODY_COMPONENT_NAME, rigid_body_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentUpdate), &component) < 0) {

		return false;
	}


	component->component_edit_draw_debug = ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentEditDrawDebug);
	component->component_notify_change = ZT_FUNCTION_POINTER_TO_VAR(_zt_rigidBodyComponentNotifyChange);

	rigid_body_component->pool = pool;
	rigid_body_component->model_component = model_component;

	return true;
}

// ================================================================================================================================================================================================

void zt_rigidBodyComponentFreeAndUnregister(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_rigidBodyComponentFreeAndUnregister");

	if (rigid_body_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_RIGID_BODY_COMPONENT_GUID);

	zt_fiz(rigid_body_component->collision_layers_count) {
		zt_stringFree(rigid_body_component->collision_layers[i]);
	}

	zt_free(rigid_body_component->entity_ids);
	zt_free(rigid_body_component->rigid_bodies);

	zt_memSet(rigid_body_component, zt_sizeof(ztRigidBodyComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_rigidBodyComponentAdd(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_rigidBodyComponentAdd");

	zt_returnValOnNull(rigid_body_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);

	zt_fiz(rigid_body_component->rigid_bodies_size) {
		if (rigid_body_component->entity_ids[i] == ztInvalidID) {
			rigid_body_component->entity_ids[i] = entity_id;
			rigid_body_component->rigid_bodies_count = zt_max(i + 1, rigid_body_component->rigid_bodies_count);

			ztRigidBody *rigid_body = &rigid_body_component->rigid_bodies[i];
			rigid_body->model = zt_modelComponentGet(rigid_body_component->model_component, pool, entity_id);
			
			rigid_body->cg_bounding.type = ztCollisionGeometryType_OrientedBox;
			rigid_body->cg_bounding.obb_extents = ztVec3::one;

			if (rigid_body->model) {
				zt_modelGetAABB(rigid_body->model, &rigid_body->cg_bounding.obb_center, &rigid_body->cg_bounding.obb_extents);
			}

			zt_entityAddedComponent(pool, entity_id, ZT_RIGID_BODY_COMPONENT_GUID, i);

			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_rigidBodyComponentRemove(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_rigidBodyComponentRemove");

	zt_returnOnNull(rigid_body_component);
	zt_returnOnNull(pool);

	zt_rigidBodyFree(&rigid_body_component->rigid_bodies[component_id]);
	rigid_body_component->entity_ids[component_id] = ztInvalidID;

	if (rigid_body_component->rigid_bodies_count - 1 == component_id) {
		rigid_body_component->rigid_bodies_count -= 1;
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_RIGID_BODY_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

ztRigidBody *zt_rigidBodyComponentGet(ztRigidBodyComponent *rigid_body_component, ztEntityPool *pool, ztEntityID entity, int which_idx, ztComponentID *component_id_out)
{
	ZT_PROFILE_GAME("zt_rigidBodyComponentGet");

	if (component_id_out) {
		*component_id_out = ztInvalidID;
	}

	zt_returnValOnNull(rigid_body_component, nullptr);
	zt_returnValOnNull(pool, nullptr);

	zt_fiz(rigid_body_component->rigid_bodies_count) {
		if (rigid_body_component->entity_ids[i] == entity) {
			if (which_idx-- <= 0) {

				if (component_id_out) {
					*component_id_out = i;
				}
				return &rigid_body_component->rigid_bodies[i];
			}
		}
	}

	return nullptr;

}

// ================================================================================================================================================================================================

ztRigidBody *zt_rigidBodyComponentGet(ztRigidBodyComponent *rigid_body_component, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_rigidBodyComponentGet");

	zt_returnValOnNull(rigid_body_component, nullptr);

	if (component_id < 0 || component_id >= rigid_body_component->rigid_bodies_count) {
		return nullptr;
	}

	return &rigid_body_component->rigid_bodies[component_id];
}

// ================================================================================================================================================================================================

void zt_rigidBodyComponentPhysicsPopulate(ztRigidBodyComponent *rigid_body_component, ztPhysics *physics)
{
	zt_fiz(rigid_body_component->rigid_bodies_count) {
		if (rigid_body_component->entity_ids[i] != ztInvalidID) {
			zt_physicsAddRigidBody(physics, &rigid_body_component->rigid_bodies[i]);
		}
	}
}

// ================================================================================================================================================================================================

void zt_rigidBodyComponentPhysicsCleanup(ztRigidBodyComponent *rigid_body_component, ztPhysics *physics)
{
	zt_fiz(rigid_body_component->rigid_bodies_count) {
		if (rigid_body_component->entity_ids[i] != ztInvalidID) {
			zt_physicsRemoveRigidBody(physics, &rigid_body_component->rigid_bodies[i]);
		}
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================

#define ZT_STATIC_BODY_COMPONENT_GUID       zt_guidMake(0x70bc2976, 0x33844412, 0x8cc4e8b1, 0x2bba2f10)
#define ZT_STATIC_BODY_COMPONENT_NAME       "StaticBody"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal void _zt_staticBodyComponentRecalcOcTree(ztStaticBodyComponent *static_body_component)
{
	zt_staticBodyFree(&static_body_component->editor_body);

	i32 total_verts = 0;

	zt_fiz(static_body_component->static_bodies_count) {
		if (static_body_component->entity_ids[i] != ztInvalidID) {
			ztModel *model = zt_modelComponentGet(static_body_component->model_component, static_body_component->pool, static_body_component->entity_ids[i]);
			if (model) {
				total_verts += zt_modelGetVertices(model, nullptr, 0, ztModelGetVerticesTransform_NoTransform);
			}
		}
	}

	if (total_verts == 0) {
		zt_logCritical("No verts found for static body");
		return;
	}

	zt_assertReturnOnFail(total_verts % 3 == 0);

	if (!zt_staticBodyMake(&static_body_component->editor_body, total_verts / 3)) {
		zt_logCritical("Unable to make static body with %d verts (%d triangles)", total_verts, total_verts / 3);
		return;
	}

	zt_fiz(static_body_component->static_bodies_count) {
		if (static_body_component->entity_ids[i] != ztInvalidID) {
			ztModel *model = zt_modelComponentGet(static_body_component->model_component, static_body_component->pool, static_body_component->entity_ids[i]);
			if (model) {
				i32 verts_count = zt_modelGetVertices(model, nullptr, 0, ztModelGetVerticesTransform_NoTransform);
				ztVec3 *verts = zt_mallocStructArrayArena(ztVec3, verts_count, zt_memGetTempArena());

				zt_modelGetVertices(model, verts, verts_count, ztModelGetVerticesTransform_WorldTransform);
				zt_staticBodyAddTriangles(&static_body_component->editor_body, verts, verts_count);

				zt_freeArena(verts, zt_memGetTempArena());
			}
		}
	}

	zt_staticBodyGenerateOcTree(&static_body_component->editor_body, static_body_component->max_objects_per_node, static_body_component->max_node_levels);

	static_body_component->changed = false;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


ZT_FUNC_COMPONENT_MAKE(_zt_staticBodyComponentMake)
{
	ZT_PROFILE_GUI("_zt_staticBodyComponentMake");

	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;
	zt_staticBodyComponentAdd(static_body_component, pool, entity_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_staticBodyComponentFree)
{
	ZT_PROFILE_GUI("_zt_staticBodyComponentFree");

	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;
	zt_staticBodyComponentRemove(static_body_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_staticBodyComponentFind)
{
	ZT_PROFILE_GUI("_zt_staticBodyComponentFind");

	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(static_body_component->static_bodies_count) {
		if (static_body_component->entity_ids[i] == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_staticBodyComponentGuiButtonRecalc)
{
	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)user_data;
	_zt_staticBodyComponentRecalcOcTree(static_body_component);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_staticBodyComponentGui)
{
	ZT_PROFILE_GUI("_zt_staticBodyComponentGui");

	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < static_body_component->static_bodies_count, nullptr);

	r32 padding = zt_guiPadding();

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztGuiItem *show_octree = zt_guiMakeCheckbox(sizer, "", ztGuiCheckboxBehaviorFlags_RightText, &static_body_component->show_octree);
	zt_componentGuiMakeItem(sizer, "Show OcTree:", show_octree);

	ztGuiItem *show_tris = zt_guiMakeCheckbox(sizer, "", ztGuiCheckboxBehaviorFlags_RightText, &static_body_component->show_triangles);
	zt_componentGuiMakeItem(sizer, "Show Triangles:", show_tris);

	ztGuiItem *edit_max_objs = zt_guiMakeEditor(sizer, "", &static_body_component->max_objects_per_node, 1, ztInt32Max, 1);
	zt_componentGuiMakeItem(sizer, "Max Tris Per Node:", edit_max_objs);

	ztGuiItem *edit_max_lvls = zt_guiMakeEditor(sizer, "", &static_body_component->max_node_levels, 1, ztInt32Max, 1);
	zt_componentGuiMakeItem(sizer, "Max Node Levels:", edit_max_lvls);

	ztGuiItem *recalc = zt_guiMakeButton(sizer, "Recalculate OcTree");
	zt_guiButtonSetCallback(recalc, ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentGuiButtonRecalc), static_body_component);
	zt_componentGuiMakeItem(sizer, "", recalc);

	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_STATIC_BODY_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("StaticModelComponent serialization failed."); return false; }


ZT_FUNC_COMPONENT_SAVE(_zt_staticBodyComponentSave)
{
	ZT_PROFILE_GAME("_zt_staticBodyComponentSave");

	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;

	if (static_body_component->changed) {
		_zt_staticBodyComponentRecalcOcTree(static_body_component);
	}

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_STATIC_BODY_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_STATIC_BODY_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, static_body_component->static_bodies_count));
		_serialCheck(zt_serialWrite(serial, static_body_component->show_octree));
		_serialCheck(zt_serialWrite(serial, static_body_component->show_triangles));
		_serialCheck(zt_serialWrite(serial, static_body_component->max_objects_per_node));
		_serialCheck(zt_serialWrite(serial, static_body_component->max_node_levels));

		zt_fiz(static_body_component->static_bodies_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, static_body_component->entity_ids[i]));
			}
			_serialCheck(zt_serialGroupPop(serial));
		}

		_serialCheck(zt_serialGroupPush(serial));
		{
			_serialCheck(zt_staticBodySave(serial, &static_body_component->editor_body));
		}
		_serialCheck(zt_serialGroupPop(serial));

	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_staticBodyComponentLoad)
{
	ZT_PROFILE_GAME("_zt_staticBodyComponentLoad");
	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_STATIC_BODY_COMPONENT_GUID) {
			zt_logCritical("StaticBodyComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_STATIC_BODY_COMPONENT_FILE_VERSION) {
			zt_logCritical("StaticBodyComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		_serialCheck(zt_serialRead(serial, &static_body_component->static_bodies_count));
		_serialCheck(zt_serialRead(serial, &static_body_component->show_octree));
		_serialCheck(zt_serialRead(serial, &static_body_component->show_triangles));
		_serialCheck(zt_serialRead(serial, &static_body_component->max_objects_per_node));
		_serialCheck(zt_serialRead(serial, &static_body_component->max_node_levels));

		zt_fiz(static_body_component->static_bodies_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialRead(serial, &static_body_component->entity_ids[i]));

				if (static_body_component->entity_ids[i] != ztInvalidID) {
					zt_entityAddedComponent(pool, static_body_component->entity_ids[i], ZT_STATIC_BODY_COMPONENT_GUID, i);
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}

		_serialCheck(zt_serialGroupPush(serial));
		{
			zt_staticBodyFree(&static_body_component->editor_body);

			_serialCheck(zt_staticBodyLoad(serial, &static_body_component->editor_body));
		}
		_serialCheck(zt_serialGroupPop(serial));

	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_staticBodyComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_staticBodyComponentUpdate");

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG_ALL(_zt_staticBodyComponentEditDrawDebugAll)
{
	ZT_PROFILE_GAME("_zt_staticBodyComponentEditDrawDebugAll");

	ztStaticBodyComponent *static_body_component = (ztStaticBodyComponent*)component->user_data;

	if (static_body_component->show_triangles) {
		zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		zt_drawListPushTexture(draw_list, ztTextureDefault);
		zt_drawListPushColor(draw_list, ztColor_Yellow);

		zt_fiz(static_body_component->editor_body.triangles_count) {
			zt_drawListAddLine(draw_list, static_body_component->editor_body.triangles[i].points[0], static_body_component->editor_body.triangles[i].points[1]);
			zt_drawListAddLine(draw_list, static_body_component->editor_body.triangles[i].points[0], static_body_component->editor_body.triangles[i].points[2]);
			zt_drawListAddLine(draw_list, static_body_component->editor_body.triangles[i].points[2], static_body_component->editor_body.triangles[i].points[1]);
		}

		zt_drawListPopColor(draw_list);
		zt_drawListPopTexture(draw_list);
		zt_drawListPopShader(draw_list);
	}

	if (static_body_component->show_octree) {
		zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		zt_drawListPushTexture(draw_list, ztTextureDefault);
		zt_drawListPushColor(draw_list, static_body_component->changed ? ztColor_Red : ztColor_Green);

		zt_fiz(static_body_component->editor_body.octree.nodes_cache_used) {
			zt_drawListAddEmptyCubeFromCenterSize(draw_list, static_body_component->editor_body.octree.nodes_cache[i].center, static_body_component->editor_body.octree.nodes_cache[i].size);
		}

		zt_drawListPopColor(draw_list);
		zt_drawListPopTexture(draw_list);
		zt_drawListPopShader(draw_list);
	}
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_NOTIFY_CHANGE(_zt_staticBodyComponentNotifyChange)
{
	ZT_PROFILE_GAME("_zt_staticBodyComponentNotifyChange");
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_staticBodyComponentMakeAndRegister(ztStaticBodyComponent *static_body_component, i32 pool_size, ztEntityPool *pool, ztModelComponent *model_component)
{
	ZT_PROFILE_GAME("zt_staticBodyComponentMakeAndRegister");

	zt_returnValOnNull(static_body_component, false);
	zt_returnValOnNull(pool, false);

	static_body_component->static_bodies_size   = pool_size;
	static_body_component->static_bodies_count  = 0;
	static_body_component->changed              = false;
	static_body_component->show_octree          = true;
	static_body_component->show_triangles       = true;
	static_body_component->max_objects_per_node = 16;
	static_body_component->max_node_levels      = 8;

	static_body_component->entity_ids = zt_mallocStructArray(ztEntityID, pool_size);
	zt_fiz(pool_size) {
		static_body_component->entity_ids[i] = ztInvalidID;
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_STATIC_BODY_COMPONENT_GUID, ZT_STATIC_BODY_COMPONENT_NAME, static_body_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentUpdate), &component) < 0) {

		return false;
	}


	component->component_edit_draw_debug_all = ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentEditDrawDebugAll);
	component->component_notify_change       = ZT_FUNCTION_POINTER_TO_VAR(_zt_staticBodyComponentNotifyChange);

	static_body_component->pool = pool;
	static_body_component->model_component = model_component;

	return true;
}

// ================================================================================================================================================================================================

void zt_staticBodyComponentFreeAndUnregister(ztStaticBodyComponent *static_body_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_staticBodyComponentFreeAndUnregister");

	if (static_body_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_STATIC_BODY_COMPONENT_GUID);

	zt_free(static_body_component->entity_ids);
	zt_staticBodyFree(&static_body_component->editor_body);

	zt_memSet(static_body_component, zt_sizeof(ztStaticBodyComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_staticBodyComponentAdd(ztStaticBodyComponent *static_body_component, ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_staticBodyComponentAdd");

	zt_returnValOnNull(static_body_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);

	zt_fiz(static_body_component->static_bodies_size) {
		if (static_body_component->entity_ids[i] == ztInvalidID) {
			static_body_component->entity_ids[i] = entity_id;
			static_body_component->static_bodies_count = zt_max(i + 1, static_body_component->static_bodies_count);

			zt_entityAddedComponent(pool, entity_id, ZT_STATIC_BODY_COMPONENT_GUID, i);
			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_staticBodyComponentRemove(ztStaticBodyComponent *static_body_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_staticBodyComponentRemove");

	zt_returnOnNull(static_body_component);
	zt_returnOnNull(pool);

	static_body_component->entity_ids[component_id] = ztInvalidID;

	if (static_body_component->static_bodies_count - 1 == component_id) {
		static_body_component->static_bodies_count -= 1;

		if (static_body_component->static_bodies_count == 0) {
			zt_staticBodyFree(&static_body_component->editor_body);
		}
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_STATIC_BODY_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

bool zt_staticBodyComponentCreateStaticBody(ztStaticBodyComponent *static_body_component, ztStaticBody *body)
{
	if (!zt_staticBodyMake(body, static_body_component->editor_body.triangles_count)) {
		return false;
	}

	body->triangles_count = static_body_component->editor_body.triangles_count;
	zt_fiz(static_body_component->editor_body.triangles_count) {
		zt_memCpy(&body->triangles[i], zt_sizeof(ztTriangle), &static_body_component->editor_body.triangles[i], zt_sizeof(ztTriangle));
	}

	body->min = static_body_component->editor_body.min;
	body->max = static_body_component->editor_body.max;

	zt_ocTreeClone(&body->octree, &static_body_component->editor_body.octree);

	return true;
}

// ================================================================================================================================================================================================

void zt_staticBodyComponentPhysicsPopulate(ztStaticBodyComponent *static_body_component, ztPhysics *physics)
{
	zt_physicsAddStaticBody(physics, &static_body_component->editor_body);
}

// ================================================================================================================================================================================================

void zt_staticBodyComponentPhysicsCleanup(ztStaticBodyComponent *static_body_component, ztPhysics *physics)
{
	zt_physicsRemoveStaticBody(physics, &static_body_component->editor_body);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


#define ZT_MOVING_BODY_COMPONENT_GUID       zt_guidMake(0x6b0604f3, 0x4c9a4a7a, 0xbfc43492, 0xb0db9c5f)
#define ZT_MOVING_BODY_COMPONENT_NAME       "MovingBody"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_movingBodyComponentMake)
{
	ZT_PROFILE_GUI("_zt_movingBodyComponentMake");

	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;
	zt_movingBodyComponentAdd(moving_body_component, pool, entity_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_movingBodyComponentFree)
{
	ZT_PROFILE_GUI("_zt_movingBodyComponentFree");

	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;

	zt_movingBodyComponentRemove(moving_body_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_movingBodyComponentFind)
{
	ZT_PROFILE_GUI("_zt_movingBodyComponentFind");

	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(moving_body_component->moving_bodies_count) {
		if (moving_body_component->entity_ids[i] == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztMovingBodyComponentGuiInfo
{
	ztMovingBodyComponent *moving_body_component;
	ztComponentID         component_id;
	ztEntityID            entity_id;
	ztGuiItem            *listbox;
	ztGuiItem            *detailed_bounds_sizer;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_movingBodyGuiComboCollisionLayer)
{
	ZT_PROFILE_GUI("_zt_movingBodyGuiComboCollisionLayer");

	ztMovingBodyComponentGuiInfo *gui_info = (ztMovingBodyComponentGuiInfo*)user_data;

	gui_info->moving_body_component->moving_bodies[gui_info->component_id].collision_layer = selected;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_movingBodyComponentGui)
{
	ZT_PROFILE_GUI("_zt_movingBodyComponentGui");

	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < moving_body_component->moving_bodies_count, nullptr);

	r32 padding = zt_guiPadding();

	ztMovingBody *moving_body = &moving_body_component->moving_bodies[component_id];

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztMovingBodyComponentGuiInfo *gui_info = zt_mallocStructArena(ztMovingBodyComponentGuiInfo, sizer->gm->arena);
	gui_info->moving_body_component = moving_body_component;
	gui_info->component_id = component_id;
	gui_info->entity_id = moving_body_component->entity_ids[component_id];

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	{
		const char *flags_names[] = {
			"Allow Penetration",
			"Track Collisions",
		};

		i32 flags[] = {
			ztMovingBodyFlags_AllowPenetration,
			ztMovingBodyFlags_TrackCollisions,
		};

		zt_componentGuiMakeFlagsEditor(sizer, "Flags:", flags_names, flags, zt_elementsOf(flags_names), &moving_body->flags, 2);
	}
	{
		ztGuiItem *combo_layers = zt_guiMakeComboBox(sizer, moving_body_component->collision_layers_count);
		zt_fiz(moving_body_component->collision_layers_count) {
			zt_guiComboBoxAppend(combo_layers, moving_body_component->collision_layers[i]);

			if (moving_body->collision_layer == i) {
				zt_guiComboBoxSetSelected(combo_layers, i);
			}
		}
		zt_guiComboBoxSetCallback(combo_layers, ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyGuiComboCollisionLayer), gui_info);

		zt_componentGuiMakeItem(sizer, "Collision Layer:", combo_layers);
	}

	if (moving_body_component->collision_layers_count > 0) {
		const char *flags_names[32];
		i32 flags[32];

		zt_fiz(moving_body_component->collision_layers_count) {
			flags_names[i] = moving_body_component->collision_layers[i];
			flags[i] = zt_bit(i);
		}

		zt_componentGuiMakeFlagsEditor(sizer, "Collides With:", flags_names, flags, moving_body_component->collision_layers_count, &moving_body->collides_with_layers, 2);
	}

	{
		ztGuiItem *editor = zt_guiMakeEditor(sizer, &moving_body->cg_bounding, moving_body->model, moving_body_component->model_component, moving_body_component->pool, moving_body_component->entity_ids[component_id], true);
		zt_componentGuiMakeItem(sizer, "Bounds:", editor);
	}

	{
		ztGuiItem *editor = zt_guiMakeEditor(sizer, moving_body->model, moving_body_component->model_component, moving_body_component->pool, moving_body_component->entity_ids[component_id], moving_body->cg_details, &moving_body->cg_details_count, zt_elementsOf(moving_body->cg_details));
		zt_componentGuiMakeItem(sizer, "Colliders:", editor);
	}


	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_MOVING_BODY_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("MovingBodyComponent serialization failed."); return false; }

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_SAVE(_zt_movingBodyComponentSave)
{
	ZT_PROFILE_GAME("_zt_movingBodyComponentSave");

	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_MOVING_BODY_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_MOVING_BODY_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, moving_body_component->moving_bodies_count));

		zt_fiz(moving_body_component->moving_bodies_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, moving_body_component->entity_ids[i]));

				if (moving_body_component->entity_ids[i] != ztInvalidID) {
					ztMovingBody *moving_body = &moving_body_component->moving_bodies[i];
					_serialCheck(zt_movingBodySave(serial, moving_body));
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_movingBodyComponentLoad)
{
	ZT_PROFILE_GAME("_zt_movingBodyComponentLoad");
	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_MOVING_BODY_COMPONENT_GUID) {
			zt_logCritical("MovingBodyComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_MOVING_BODY_COMPONENT_FILE_VERSION) {
			zt_logCritical("MovingBodyComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		_serialCheck(zt_serialRead(serial, &moving_body_component->moving_bodies_count));

		zt_fiz(moving_body_component->moving_bodies_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialRead(serial, &moving_body_component->entity_ids[i]));

				if (moving_body_component->entity_ids[i] != ztInvalidID) {
					ztMovingBody *moving_body = &moving_body_component->moving_bodies[i];
					_serialCheck(zt_movingBodyLoad(serial, moving_body));
					moving_body->model = zt_modelComponentGet(moving_body_component->model_component, pool, moving_body_component->entity_ids[i]);
					moving_body->transform = &moving_body->model->transform;
					zt_entityAddedComponent(pool, moving_body_component->entity_ids[i], ZT_MOVING_BODY_COMPONENT_GUID, i);
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_movingBodyComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_movingBodyComponentUpdate");

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_movingBodyComponentEditDrawDebug)
{
	ZT_PROFILE_GAME("_zt_movingBodyComponentEditDrawDebug");

	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;
	zt_assertReturnOnFail(active_component_id >= 0 && active_component_id < moving_body_component->moving_bodies_count);

	ztMovingBody *moving_body = &moving_body_component->moving_bodies[active_component_id];

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	zt_drawListPushColor(draw_list, ztColor_Orange);
	zt_collisionGeometryRenderDebug(&moving_body->cg_bounding, draw_list, moving_body->model ? moving_body->model->transform.position : ztVec3::zero, moving_body->model ? moving_body->model->calculated_mat : ztMat4::identity);
	zt_drawListPopColor(draw_list);

	static ztColor colors[] = { ztColor_Yellow, ztColor_Purple, ztColor_Green, ztColor_Blue };

	zt_fiz(moving_body->cg_details_count) {
		zt_drawListPushColor(draw_list, colors[i % zt_elementsOf(colors)]);
		zt_collisionGeometryRenderDebug(&moving_body->cg_details[i], draw_list, moving_body->model ? moving_body->model->transform.position : ztVec3::zero, moving_body->model ? moving_body->model->calculated_mat : ztMat4::identity);
		zt_drawListPopColor(draw_list);
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_NOTIFY_CHANGE(_zt_movingBodyComponentNotifyChange)
{
	ZT_PROFILE_GAME("_zt_movingBodyComponentNotifyChange");

	// we need to make sure we update the model pointer if the model component is changed or removed
	ztMovingBodyComponent *moving_body_component = (ztMovingBodyComponent*)component->user_data;
	moving_body_component->moving_bodies[component_id].model = zt_modelComponentGet(moving_body_component->model_component, moving_body_component->pool, entity_id);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_movingBodyComponentMakeAndRegister(ztMovingBodyComponent *moving_body_component, i32 pool_size, ztEntityPool *pool, ztModelComponent *model_component, const char ** collision_layers, i32 collision_layers_size)
{
	ZT_PROFILE_GAME("zt_movingBodyComponentMakeAndRegister");

	zt_returnValOnNull(moving_body_component, false);
	zt_returnValOnNull(pool, false);

	moving_body_component->collision_layers_count = collision_layers_size;
	zt_fiz(collision_layers_size) {
		moving_body_component->collision_layers[i] = zt_stringMakeFrom(collision_layers[i]);
	}

	moving_body_component->moving_bodies = zt_mallocStructArray(ztMovingBody, pool_size);
	moving_body_component->moving_bodies_size = pool_size;
	moving_body_component->moving_bodies_count = 0;

	moving_body_component->entity_ids = zt_mallocStructArray(ztEntityID, pool_size);
	zt_fiz(pool_size) {
		moving_body_component->entity_ids[i] = ztInvalidID;
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_MOVING_BODY_COMPONENT_GUID, ZT_MOVING_BODY_COMPONENT_NAME, moving_body_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentUpdate), &component) < 0) {

		return false;
	}


	component->component_edit_draw_debug = ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentEditDrawDebug);
	component->component_notify_change = ZT_FUNCTION_POINTER_TO_VAR(_zt_movingBodyComponentNotifyChange);

	moving_body_component->pool = pool;
	moving_body_component->model_component = model_component;

	return true;
}

// ================================================================================================================================================================================================

void zt_movingBodyComponentFreeAndUnregister(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_movingBodyComponentFreeAndUnregister");

	if (moving_body_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_MOVING_BODY_COMPONENT_GUID);

	zt_fiz(moving_body_component->collision_layers_count) {
		zt_stringFree(moving_body_component->collision_layers[i]);
	}

	zt_free(moving_body_component->entity_ids);
	zt_free(moving_body_component->moving_bodies);

	zt_memSet(moving_body_component, zt_sizeof(ztMovingBodyComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_movingBodyComponentAdd(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_movingBodyComponentAdd");

	zt_returnValOnNull(moving_body_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);

	zt_fiz(moving_body_component->moving_bodies_size) {
		if (moving_body_component->entity_ids[i] == ztInvalidID) {
			moving_body_component->entity_ids[i] = entity_id;
			moving_body_component->moving_bodies_count = zt_max(i + 1, moving_body_component->moving_bodies_count);

			ztMovingBody *moving_body = &moving_body_component->moving_bodies[i];

			moving_body->cg_bounding.type = ztCollisionGeometryType_OrientedBox;
			moving_body->cg_bounding.obb_extents = ztVec3::one;

			zt_movingBodyMake(moving_body, zt_modelComponentGet(moving_body_component->model_component, pool, entity_id), .5f, moving_body->cg_bounding, moving_body->cg_bounding);

			if (moving_body->model) {
				zt_modelGetAABB(moving_body->model, &moving_body->cg_bounding.obb_center, &moving_body->cg_bounding.obb_extents);
			}

			zt_entityAddedComponent(pool, entity_id, ZT_MOVING_BODY_COMPONENT_GUID, i);

			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_movingBodyComponentRemove(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_movingBodyComponentRemove");

	zt_returnOnNull(moving_body_component);
	zt_returnOnNull(pool);

	zt_movingBodyFree(&moving_body_component->moving_bodies[component_id]);
	moving_body_component->entity_ids[component_id] = ztInvalidID;

	if (moving_body_component->moving_bodies_count - 1 == component_id) {
		moving_body_component->moving_bodies_count -= 1;
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_MOVING_BODY_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

ztMovingBody *zt_movingBodyComponentGet(ztMovingBodyComponent *moving_body_component, ztEntityPool *pool, ztEntityID entity, int which_idx, ztComponentID *component_id_out)
{
	ZT_PROFILE_GAME("zt_movingBodyComponentGet");

	if (component_id_out) {
		*component_id_out = ztInvalidID;
	}

	zt_returnValOnNull(moving_body_component, nullptr);
	zt_returnValOnNull(pool, nullptr);

	zt_fiz(moving_body_component->moving_bodies_count) {
		if (moving_body_component->entity_ids[i] == entity) {
			if (which_idx-- <= 0) {

				if (component_id_out) {
					*component_id_out = i;
				}
				return &moving_body_component->moving_bodies[i];
			}
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

ztMovingBody *zt_movingBodyComponentGet(ztMovingBodyComponent *moving_body_component, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_movingBodyComponentGet");

	zt_returnValOnNull(moving_body_component, nullptr);

	if (component_id < 0 || component_id >= moving_body_component->moving_bodies_count) {
		return nullptr;
	}

	return &moving_body_component->moving_bodies[component_id];
}

// ================================================================================================================================================================================================

void zt_movingBodyComponentPhysicsPopulate(ztMovingBodyComponent *moving_body_component, ztPhysics *physics)
{
	zt_fiz(moving_body_component->moving_bodies_count) {
		if (moving_body_component->entity_ids[i] != ztInvalidID) {
			zt_physicsAddMovingBody(physics, &moving_body_component->moving_bodies[i]);
		}
	}
}

// ================================================================================================================================================================================================

void zt_movingBodyComponentPhysicsCleanup(ztMovingBodyComponent *moving_body_component, ztPhysics *physics)
{
	zt_fiz(moving_body_component->moving_bodies_count) {
		if (moving_body_component->entity_ids[i] != ztInvalidID) {
			zt_physicsRemoveMovingBody(physics, &moving_body_component->moving_bodies[i]);
		}
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


#define ZT_MARKER_COMPONENT_GUID       zt_guidMake(0x9d9657c6, 0xd5f244e3, 0xb4246d44, 0x66b9fd35)
#define ZT_MARKER_COMPONENT_NAME       "Marker"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_markerComponentMake)
{
	ZT_PROFILE_GUI("_zt_markerComponentMake");

	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;
	zt_markerComponentAdd(marker_component, pool, entity_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_markerComponentFree)
{
	ZT_PROFILE_GUI("_zt_markerComponentFree");

	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;

	zt_markerComponentRemove(marker_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_markerComponentFind)
{
	ZT_PROFILE_GUI("_zt_markerComponentFind");

	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(marker_component->markers_count) {
		if (marker_component->markers[i].entity_id == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztMarkerComponentGuiInfo
{
	ztMarkerComponent    *marker_component;
	ztComponentID         component_id;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_markerComponentGuiComboType)
{
	ztMarkerComponentGuiInfo *gui_info = (ztMarkerComponentGuiInfo*)user_data;

	gui_info->marker_component->markers[gui_info->component_id].type = gui_info->marker_component->types[selected].guid;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_markerComponentGui)
{
	ZT_PROFILE_GUI("_zt_markerComponentGui");

	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < marker_component->markers_count, nullptr);

	r32 padding = zt_guiPadding();

	ztMarkerComponent::Marker *marker = &marker_component->markers[component_id];

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow);
	zt_guiSizerSizeParent(sizer, false, true);
	zt_guiSizerSizeToParent(sizer);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztMarkerComponentGuiInfo *gui_info = zt_mallocStructArena(ztMarkerComponentGuiInfo, sizer->gm->arena);
	gui_info->marker_component = marker_component;
	gui_info->component_id = component_id;

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	ztGuiItem *text_edit = zt_guiMakeTextEdit(sizer, marker->name, 0, zt_elementsOf(marker->name));
	zt_guiTextEditSetLiveBuffer(text_edit, marker->name, zt_elementsOf(marker->name));
	zt_componentGuiMakeItem(sizer, "Name", text_edit);

	ztGuiItem *combo_types = zt_guiMakeComboBox(sizer, marker_component->types_count);
	zt_fiz(marker_component->types_count) {
		zt_guiComboBoxAppend(combo_types, marker_component->types[i].label);

		if (marker->type == marker_component->types[i].guid) {
			zt_guiComboBoxSetSelected(combo_types, i);
		}
	}
	zt_guiComboBoxSetCallback(combo_types, ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentGuiComboType), gui_info);

	zt_componentGuiMakeItem(sizer, "Type", combo_types);

	zt_componentGuiMakeEditor(sizer, "Transform", &marker->transform, .25f, 1.f, 1.f);

	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_MARKER_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("MarkerComponent serialization failed."); return false; }


ZT_FUNC_COMPONENT_SAVE(_zt_markerComponentSave)
{
	ZT_PROFILE_GAME("_zt_markerComponentSave");

	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_MARKER_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_MARKER_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, marker_component->markers_count));

		zt_fiz(marker_component->markers_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, marker_component->markers[i].entity_id));

				if (marker_component->markers[i].entity_id != ztInvalidID) {
					_serialCheck(zt_serialWrite(serial, marker_component->markers[i].name, zt_strLen(marker_component->markers[i].name)));
					_serialCheck(zt_serialWrite(serial, marker_component->markers[i].type));
					_serialCheck(zt_serialWrite(serial, marker_component->markers[i].transform.position));
					_serialCheck(zt_serialWrite(serial, marker_component->markers[i].transform.rotation));
					_serialCheck(zt_serialWrite(serial, marker_component->markers[i].transform.scale));
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_markerComponentLoad)
{
	ZT_PROFILE_GAME("_zt_markerComponentLoad");
	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_MARKER_COMPONENT_GUID) {
			zt_logCritical("MarkerComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_MARKER_COMPONENT_FILE_VERSION) {
			zt_logCritical("MarkerComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		_serialCheck(zt_serialRead(serial, &marker_component->markers_count));

		zt_fiz(marker_component->markers_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialRead(serial, &marker_component->markers[i].entity_id));

				if (marker_component->markers[i].entity_id != ztInvalidID) {
					i32 name_len = 0;
					_serialCheck(zt_serialRead(serial, marker_component->markers[i].name, zt_elementsOf(marker_component->markers[i].name), &name_len));
					_serialCheck(zt_serialRead(serial, &marker_component->markers[i].type));
					_serialCheck(zt_serialRead(serial, &marker_component->markers[i].transform.position));
					_serialCheck(zt_serialRead(serial, &marker_component->markers[i].transform.rotation));
					_serialCheck(zt_serialRead(serial, &marker_component->markers[i].transform.scale));
					zt_entityAddedComponent(pool, marker_component->markers[i].entity_id, ZT_MARKER_COMPONENT_GUID, i);
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_markerComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_markerComponentUpdate");

	ztMarkerComponent *marker_component = (ztMarkerComponent *)component->user_data;

	if (pool->editor) {
		bool found = false;
		ztEntityID active_entity = zt_entityEditorGetActiveEntity(pool->editor);
		zt_fiz(marker_component->markers_count) {
			if (marker_component->markers[i].entity_id == active_entity) {
				found = true;
				if (marker_component->edit_widget.transform != &marker_component->markers[i].transform) {
					zt_modelEditWidgetFree(&marker_component->edit_widget);
					zt_modelEditWidgetMake(&marker_component->edit_widget, &marker_component->markers[i].transform);
				}

				zt_modelEditWidgetUpdate(&marker_component->edit_widget, input_keys, input_mouse, camera, dt);
			}
		}

		if (!found) {
			marker_component->edit_widget.transform = nullptr;
		}
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK(_zt_markerComponentEditQueryClick)
{
	ZT_PROFILE_GAME("_zt_markerComponentEditQueryClick");

	ztMarkerComponent *marker_component = (ztMarkerComponent *)component->user_data;

	ztEntityID active_entity = zt_entityEditorGetActiveEntity(pool->editor);
	zt_fiz(marker_component->markers_count) {
		if (marker_component->markers[i].entity_id == active_entity) {
			if (zt_modelEditWidgetIsMouseWithinBounds(&marker_component->edit_widget, camera, input_mouse->screen_x, input_mouse->screen_y)) {
				*closest_id = -100;
				*closest_dist = ztReal32Min; // this always needs processed with priority
				return true;
			}
		}
	}

	r32 closest_time = ztReal32Max;
	i32 closest_idx = -1;
	ztVec3 closest_pos = ztVec3::zero;

	zt_fiz(marker_component->markers_count) {

		ztVec3 center = marker_component->markers[i].transform.position;
		ztVec3 ext = ztVec3::one;

		r32 intersect_time = ztReal32Max;
		ztVec3 intersect_pos = ztVec3::zero;
		if (zt_collisionRayInAABB(ray_pos, ray_dir, center, ext, &intersect_time, &intersect_pos)) {
			if (intersect_time < closest_time) {
				closest_time = intersect_time;
				closest_idx = i;
				closest_pos = intersect_pos;
			}
		}
	}

	if (closest_idx >= 0) {
		*closest_id = closest_idx;
		*closest_dist = ray_pos.distance(closest_pos);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK(_zt_markerComponentEditProcessClick)
{
	ZT_PROFILE_GAME("_zt_markerComponentEditProcessClick");

	ztMarkerComponent *marker_component = (ztMarkerComponent *)component->user_data;

	if (closest_id != -100) {
		zt_modelEditWidgetFree(&marker_component->edit_widget);
		zt_modelEditWidgetMake(&marker_component->edit_widget, &marker_component->markers[closest_id].transform);
		zt_entityEditorMakeEntityActive(pool->editor, marker_component->markers[closest_id].entity_id);
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_markerComponentEditDrawDebug)
{
	ZT_PROFILE_GAME("_zt_markerComponentEditDrawDebug");

	ztMarkerComponent *marker_component = (ztMarkerComponent *)component->user_data;

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefaultWhite);
	zt_modelEditWidgetRender(&marker_component->edit_widget, camera, draw_list);
	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);

}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_markerComponentEditDrawDebugAll)
{
	ZT_PROFILE_GAME("_zt_markerComponentEditDrawDebugAll");

	ztMarkerComponent *marker_component = (ztMarkerComponent*)component->user_data;

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	zt_fiz(marker_component->markers_count) {
		if (active_entity_id == marker_component->markers[i].entity_id) {
			zt_drawListPushColor(draw_list, ztColor_Green);
		}

		ztTransform transform;
		zt_memCpy(&transform, zt_sizeof(ztTransform), &marker_component->markers[i].transform, zt_sizeof(ztTransform));

		if (transform.position == ztVec3::zero && transform.rotation == ztQuat::identity) {
			ztModel *model = zt_modelComponentGet(marker_component->model_component, marker_component->pool, marker_component->markers[i].entity_id);
			if (model) {
				transform = model->transform;
			}
		}

		transform.scale = ztVec3::one;
		ztMat4 mat = zt_transformToMat4(&transform);
		zt_drawListPushTransform(draw_list, mat);
		zt_drawListAddText2D(draw_list, ztFontDefault, marker_component->markers[i].name, zt_vec2(0, .75f));
		zt_drawListAddAxis(draw_list, .5f);
		zt_drawListPopTransform(draw_list);

		transform.rotation *= ztQuat::makeFromEuler(0, 180, 0);
		mat = zt_transformToMat4(&transform);
		zt_drawListPushTransform(draw_list, mat);
		zt_drawListAddText2D(draw_list, ztFontDefault, marker_component->markers[i].name, zt_vec2(0, .75f));
		zt_drawListPopTransform(draw_list);
		zt_drawListAddEmptyBone(draw_list, marker_component->markers[i].transform.position, .5f, .125f, .15f);

		if (active_entity_id == marker_component->markers[i].entity_id) {
			zt_drawListPopColor(draw_list);
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztMarkerType zt_markerTypeMake(ztGuid guid, const char *label)
{
	ztMarkerType type;
	type.guid = guid;
	zt_strCpy(type.label, zt_elementsOf(type.label), label);
	return type;
}

// ================================================================================================================================================================================================

bool zt_markerComponentMakeAndRegister(ztMarkerComponent *marker_component, ztEntityPool *pool, ztModelComponent *model_component, ztMarkerType *types, i32 types_count)
{
	ZT_PROFILE_GAME("zt_markerComponentMakeAndRegister");

	zt_returnValOnNull(marker_component, false);
	zt_returnValOnNull(pool, false);

	marker_component->pool = pool;
	marker_component->model_component = model_component;

	marker_component->types_count = types_count;
	marker_component->types = types_count > 0 ? zt_mallocStructArray(ztMarkerType, types_count) : nullptr;
	zt_fiz(types_count) {
		zt_memCpy(&marker_component->types[i], zt_sizeof(ztMarkerType), &types[i], zt_sizeof(ztMarkerType));
	}

	zt_fiz(ZT_MARKER_COMPONENT_MAX_MARKERS) {
		marker_component->markers[i].entity_id = ztInvalidID;
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_MARKER_COMPONENT_GUID, ZT_MARKER_COMPONENT_NAME, marker_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentUpdate), &component) < 0) {

		return false;
	}

	component->component_edit_query_click = ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentEditQueryClick);
	component->component_edit_process_click = ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentEditProcessClick);
	component->component_edit_draw_debug = ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentEditDrawDebug);
	component->component_edit_draw_debug_all = ZT_FUNCTION_POINTER_TO_VAR(_zt_markerComponentEditDrawDebugAll);

	return true;
}

// ================================================================================================================================================================================================

void zt_markerComponentFreeAndUnregister(ztMarkerComponent *marker_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_markerComponentFreeAndUnregister");

	if (marker_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_MARKER_COMPONENT_GUID);

	if (marker_component->types) {
		zt_free(marker_component->types);
	}

	zt_modelEditWidgetFree(&marker_component->edit_widget);

	zt_memSet(marker_component, zt_sizeof(ztMarkerComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_markerComponentAdd(ztMarkerComponent *marker_component, ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_markerComponentAdd");

	zt_returnValOnNull(marker_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);

	zt_fize(marker_component->markers) {
		if (marker_component->markers[i].entity_id == ztInvalidID) {
			marker_component->markers[i].entity_id = entity_id;
			marker_component->markers_count = zt_max(i + 1, marker_component->markers_count);

			ztMarkerComponent::Marker *marker = &marker_component->markers[i];

			zt_strCpy(marker->name, zt_elementsOf(marker->name), "Marker");

			marker->type = marker_component->types_count > 0 ? marker_component->types[0].guid : zt_guidMake(0, 0, 0, 0);
			marker->transform.position = ztVec3::zero;
			marker->transform.rotation = ztQuat::identity;
			marker->transform.scale = ztVec3::one;

			zt_entityAddedComponent(pool, entity_id, ZT_MARKER_COMPONENT_GUID, i);

			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_markerComponentRemove(ztMarkerComponent *marker_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_markerComponentRemove");

	zt_returnOnNull(marker_component);
	zt_returnOnNull(pool);

	marker_component->markers[component_id].entity_id = ztInvalidID;

	if (marker_component->markers_count - 1 == component_id) {
		marker_component->markers_count -= 1;
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_MARKER_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

ztMarkerComponent::Marker *zt_markerComponentGet(ztMarkerComponent *marker_component, ztEntityPool *pool, ztEntityID entity, int which_idx, ztComponentID *component_id_out)
{
	ZT_PROFILE_GAME("zt_markerComponentGet");

	if (component_id_out) {
		*component_id_out = ztInvalidID;
	}

	zt_returnValOnNull(marker_component, nullptr);
	zt_returnValOnNull(pool, nullptr);

	zt_fiz(marker_component->markers_count) {
		if (marker_component->markers[i].entity_id == entity) {
			if (which_idx-- <= 0) {
				if (component_id_out) {
					*component_id_out = i;
				}
				return &marker_component->markers[i];
			}
		}
	}

	return nullptr;

}

// ================================================================================================================================================================================================

ztMarkerComponent::Marker *zt_markerComponentGet(ztMarkerComponent *marker_component, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_markerComponentGet");

	zt_returnValOnNull(marker_component, nullptr);

	if (component_id < 0 || component_id >= marker_component->markers_count) {
		return nullptr;
	}

	return &marker_component->markers[component_id];
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


#define ZT_TAG_COMPONENT_GUID       zt_guidMake(0x1a243347, 0x62fa4f7b, 0xbc39ea10, 0x2da9a984)
#define ZT_TAG_COMPONENT_NAME       "Tag"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_tagComponentMake)
{
	ZT_PROFILE_GUI("_zt_tagComponentMake");

	ztTagComponent *tag_component = (ztTagComponent*)component->user_data;
	zt_tagComponentAdd(tag_component, pool, entity_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_tagComponentFree)
{
	ZT_PROFILE_GUI("_zt_tagComponentFree");

	ztTagComponent *tag_component = (ztTagComponent*)component->user_data;

	zt_tagComponentRemove(tag_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_tagComponentFind)
{
	ZT_PROFILE_GUI("_zt_tagComponentFind");

	ztTagComponent *tag_component = (ztTagComponent*)component->user_data;

	bool return_next = after_component_id == ztInvalidID;

	zt_fiz(tag_component->tags_count) {
		if (tag_component->tags[i].entity_id == entity_id) {
			if (return_next) {
				return i;
			}
			return_next = i == after_component_id;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztTagComponentGuiInfo
{
	ztTagComponent    *tag_component;
	ztComponentID      component_id;
	ztGuiItem         *text_edit;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_DIALOG_LIST_SELECTED(_zt_tagComponentListSelect)
{
	ztTagComponentGuiInfo *gui_info = (ztTagComponentGuiInfo*)user_data;

	ztTagComponent::Tag *tag = &gui_info->tag_component->tags[gui_info->component_id];
	zt_strCpy(tag->tag, zt_elementsOf(tag->tag), list_item);
	zt_guiTextEditSetValue(gui_info->text_edit, list_item);
	zt_guiTextEditSetLiveBuffer(gui_info->text_edit, tag->tag, zt_elementsOf(tag->tag));
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_tagComponentButtonDefaults)
{
	ztTagComponentGuiInfo *gui_info = (ztTagComponentGuiInfo*)user_data;

	zt_guiDialogListSelector(gui_info->tag_component->defaults, gui_info->tag_component->defaults_count, "Choose a Default:", ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentListSelect), gui_info);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_tagComponentGui)
{
	ZT_PROFILE_GUI("_zt_tagComponentGui");

	ztTagComponent *tag_component = (ztTagComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < tag_component->tags_count, nullptr);

	r32 padding = zt_guiPadding();

	ztTagComponent::Tag *tag = &tag_component->tags[component_id];

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow);
	zt_guiSizerSizeParent(sizer, false, true);
	zt_guiSizerSizeToParent(sizer);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztTagComponentGuiInfo *gui_info = zt_mallocStructArena(ztTagComponentGuiInfo, sizer->gm->arena);
	gui_info->tag_component = tag_component;
	gui_info->component_id = component_id;

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	ztGuiItem *text_edit = zt_guiMakeTextEdit(sizer, tag->tag, 0, zt_elementsOf(tag->tag));
	zt_guiTextEditSetLiveBuffer(text_edit, tag->tag, zt_elementsOf(tag->tag));
	zt_componentGuiMakeItem(sizer, "Tag", text_edit);
	gui_info->text_edit = text_edit;

	ztGuiItem *button_defaults = zt_guiMakeButton(sizer, "Choose From Defaults");
	zt_componentGuiMakeItem(sizer, "", button_defaults);

	zt_guiButtonSetCallback(button_defaults, ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentButtonDefaults), gui_info);

	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_TAG_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("TagComponent serialization failed."); return false; }


ZT_FUNC_COMPONENT_SAVE(_zt_tagComponentSave)
{
	ZT_PROFILE_GAME("_zt_tagComponentSave");

	ztTagComponent *tag_component = (ztTagComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_TAG_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_TAG_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, tag_component->tags_count));

		zt_fiz(tag_component->tags_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, tag_component->tags[i].entity_id));

				if (tag_component->tags[i].entity_id != ztInvalidID) {
					_serialCheck(zt_serialWrite(serial, tag_component->tags[i].tag, zt_strLen(tag_component->tags[i].tag)));
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_tagComponentLoad)
{
	ZT_PROFILE_GAME("_zt_tagComponentLoad");
	ztTagComponent *tag_component = (ztTagComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_TAG_COMPONENT_GUID) {
			zt_logCritical("MarkerComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_TAG_COMPONENT_FILE_VERSION) {
			zt_logCritical("MarkerComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		_serialCheck(zt_serialRead(serial, &tag_component->tags_count));

		zt_fiz(tag_component->tags_count) {
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialRead(serial, &tag_component->tags[i].entity_id));

				if (tag_component->tags[i].entity_id != ztInvalidID) {
					i32 name_len = 0;
					_serialCheck(zt_serialRead(serial, tag_component->tags[i].tag, zt_elementsOf(tag_component->tags[i].tag), &name_len));
					zt_entityAddedComponent(pool, tag_component->tags[i].entity_id, ZT_TAG_COMPONENT_GUID, i);
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

#undef _serialCheck

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_tagComponentMakeAndRegister(ztTagComponent *tag_component, ztEntityPool *pool, const char **defaults, i32 defaults_count)
{
	ZT_PROFILE_GAME("zt_tagComponentMakeAndRegister");

	zt_returnValOnNull(tag_component, false);
	zt_returnValOnNull(pool, false);

	tag_component->defaults_count = defaults_count;
	tag_component->defaults = defaults_count > 0 ? zt_mallocStructArray(const char*, defaults_count) : nullptr;

	zt_fiz(defaults_count) {
		int strLen = zt_strLen(defaults[i]);
		tag_component->defaults[i] = zt_mallocStructArray(const char, strLen + 1);
		zt_strCpy((char*)tag_component->defaults[i], strLen + 1, defaults[i], strLen);
	}

	zt_fiz(ZT_TAG_COMPONENT_MAX_TAGS) {
		tag_component->tags[i].entity_id = ztInvalidID;
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_TAG_COMPONENT_GUID, ZT_TAG_COMPONENT_NAME, tag_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_tagComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR_NULL, &component) < 0) {

		return false;
	}

	return true;
}

// ================================================================================================================================================================================================

void zt_tagComponentFreeAndUnregister(ztTagComponent *tag_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_tagComponentFreeAndUnregister");

	if (tag_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_TAG_COMPONENT_GUID);

	if (tag_component->defaults) {
		zt_fiz(tag_component->defaults_count) {
			zt_free(tag_component->defaults[i]);
		}
		zt_free(tag_component->defaults);
	}

	zt_memSet(tag_component, zt_sizeof(ztTagComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_tagComponentAdd(ztTagComponent *tag_component, ztEntityPool *pool, ztEntityID entity_id)
{
	ZT_PROFILE_GAME("zt_tagComponentAdd");

	zt_returnValOnNull(tag_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);

	zt_fize(tag_component->tags) {
		if (tag_component->tags[i].entity_id == ztInvalidID) {
			tag_component->tags[i].entity_id = entity_id;
			tag_component->tags_count = zt_max(i + 1, tag_component->tags_count);

			ztTagComponent::Tag *tag = &tag_component->tags[i];

			zt_strCpy(tag->tag, zt_elementsOf(tag->tag), "New Tag");

			zt_entityAddedComponent(pool, entity_id, ZT_TAG_COMPONENT_GUID, i);

			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_tagComponentRemove(ztTagComponent *tag_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_tagComponentRemove");

	zt_returnOnNull(tag_component);
	zt_returnOnNull(pool);

	tag_component->tags[component_id].entity_id = ztInvalidID;

	if (tag_component->tags_count - 1 == component_id) {
		tag_component->tags_count -= 1;
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_TAG_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

const char *zt_tagComponentGet(ztTagComponent *tag_component, ztEntityPool *pool, ztEntityID entity, int which_idx, ztComponentID *component_id_out)
{
	ZT_PROFILE_GAME("zt_tagComponentGet");

	if (component_id_out) {
		*component_id_out = ztInvalidID;
	}

	zt_returnValOnNull(tag_component, nullptr);
	zt_returnValOnNull(pool, nullptr);

	zt_fiz(tag_component->tags_count) {
		if (tag_component->tags[i].entity_id == entity) {
			if (which_idx-- <= 0) {
				if (component_id_out) {
					*component_id_out = i;
				}
				return tag_component->tags[i].tag;
			}
		}
	}

	return nullptr;
}

// ================================================================================================================================================================================================

const char *zt_tagComponentGet(ztTagComponent *tag_component, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_tagComponentGet");

	zt_returnValOnNull(tag_component, nullptr);

	if (component_id < 0 || component_id >= tag_component->tags_count) {
		return nullptr;
	}

	return tag_component->tags[component_id].tag;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_PATH_COMPONENT_GUID       zt_guidMake(0x3314d6f0, 0x710c4b98, 0xa7b824aa, 0x0e38d990)
#define ZT_PATH_COMPONENT_NAME       "Path"

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================

struct ztPathComponentMakeParams
{
	ztEntityPool     *pool;
	ztEntityID        entity_id;
	ztComponent      *component;
	ztPathComponent  *path_component;
	ztGuiItem        *listbox;
};

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_pathComponentMakeAdd)
{
	ZT_PROFILE_GAME("_zt_pathComponentMakeAdd");

	ztPathComponentMakeParams *params = (ztPathComponentMakeParams*)user_data;

	int selected = zt_guiListBoxGetSelected(params->listbox);
	ztGuid *guid = (ztGuid*)zt_guiListBoxGetItemUserData(params->listbox, selected);
	zt_assertReturnOnFail(guid != nullptr);

	ztComponentID component_id = zt_pathComponentAdd(params->path_component, params->pool, params->entity_id, *guid);

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNC_GUI_BUTTON_PRESSED(_zt_pathComponentMakeCancel)
{
	ZT_PROFILE_GAME("_zt_pathComponentMakeCancel");

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_MAKE(_zt_pathComponentMake)
{
	ZT_PROFILE_GAME("_zt_pathComponentMake");

	ztPathComponent *path_component = (ztPathComponent*)component->user_data;

	i32 unused_paths = 0;
	zt_fiz(path_component->paths_count) {
		if (path_component->paths[i].entity_id == ztInvalidID) {
			unused_paths += 1;
		}
	}

	if (unused_paths == 0) {
		zt_guiDialogMessageBoxOk("No Paths Available", "All paths have already been assigned to entities.");
		return;
	}

	// this needs to open a dialog to allow the user to select one of the valid paths

	ztGuiItem *window = zt_guiMakeWindow("Select Path", ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_Modal | ztGuiWindowBehaviorFlags_ShowTitle);
	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	r32 padding = zt_guiPadding();

	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Choose a path:"), 0, padding);

	ztGuiItem *listbox = zt_guiMakeListBox(sizer, 0, path_component->paths_count);
	zt_fiz(path_component->paths_count) {
		int idx = zt_guiListBoxAppend(listbox, path_component->paths_ids[i].label, &path_component->paths_ids[i].guid);

		if (path_component->paths[i].entity_id != ztInvalidID) {
			zt_guiListBoxHideItem(listbox, idx);
		}
	}


	zt_guiSizerAddItem(sizer, listbox, 1, padding);

	ztGuiItem *button_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, button_sizer, 0, 0);

	ztGuiItem *button_ok = zt_guiMakeButton(button_sizer, "OK");
	ztGuiItem *button_no = zt_guiMakeButton(button_sizer, "Cancel");

	button_ok->size = button_no->size;

	zt_guiSizerAddStretcher(button_sizer, 1);
	zt_guiSizerAddItem(button_sizer, button_ok, 0, padding);
	zt_guiSizerAddItem(button_sizer, button_no, 0, padding);

	ztPathComponentMakeParams *params = zt_mallocStructArena(ztPathComponentMakeParams, window->gm->arena);
	ztGuiItem *params_cleanup = zt_guiMakePanel(window, 0, params, window->gm->arena);

	zt_guiButtonSetCallback(button_ok, ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentMakeAdd), params);
	zt_guiButtonSetCallback(button_no, ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentMakeCancel), nullptr);

	params->pool = pool;
	params->entity_id = entity_id;
	params->component = component;
	params->path_component = path_component;
	params->listbox = listbox;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FREE(_zt_pathComponentFree)
{
	ZT_PROFILE_GUI("_zt_pathComponentFree");

	ztPathComponent *path_component = (ztPathComponent*)component->user_data;

	zt_pathComponentRemove(path_component, pool, entity_id, component_id);
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_FIND(_zt_pathComponentFind)
{
	ZT_PROFILE_GUI("_zt_pathComponentFind");

	if (after_component_id != ztInvalidID) {
		return ztInvalidID;
	}

	ztPathComponent *path_component = (ztPathComponent*)component->user_data;

	zt_fiz(path_component->paths_count) {
		if (path_component->paths[i].entity_id == entity_id) {
			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

struct ztPathComponentGuiInfo
{
	ztPathComponent    *path_component;
	ztComponentID       component_id;
};

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_GUI(_zt_pathComponentGui)
{
	ZT_PROFILE_GUI("_zt_pathComponentGui");

	ztPathComponent *path_component = (ztPathComponent*)component->user_data;
	zt_assertReturnValOnFail(component_id >= 0 && component_id < path_component->paths_count, nullptr);

	r32 padding = zt_guiPadding();

	ztPathComponent::Path *path = &path_component->paths[component_id];

	ztGuiItem *sizer = zt_guiMakeColumnSizer(parent, 2, ztGuiColumnSizerType_FillRow);
	zt_guiSizerSizeParent(sizer, false, true);
	zt_guiSizerSizeToParent(sizer);
	zt_guiColumnSizerSetProp(sizer, 0, 0);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	ztPathComponentGuiInfo *gui_info = zt_mallocStructArena(ztPathComponentGuiInfo, sizer->gm->arena);
	gui_info->path_component = path_component;
	gui_info->component_id = component_id;

	path_component->active_path = component_id;

	zt_guiMakePanel(sizer, 0, gui_info, sizer->gm->arena);

	ztGuiItem *path_name = zt_guiMakeStaticText(sizer, path_component->paths_ids[path->path_idx].label, 0);
	zt_componentGuiMakeItem(sizer, "Name", path_name);

	ztGuiItem *button_add = zt_guiMakeToggleButton(sizer, "Add Waypoints", 0, &path_component->active_path_adding);
	zt_componentGuiMakeItem(sizer, " ", button_add);

	ztGuiItem *instructions = zt_guiMakeStaticText(sizer, "Right-click in scene to configure");
	zt_componentGuiMakeItem(sizer, "Instructions", instructions);

	ztGuiItem *chk_static_bodies_only = zt_guiMakeCheckbox(sizer, "Add on Static Bodies Only", ztGuiCheckboxBehaviorFlags_RightText, &path_component->add_to_static_bodies_only);
	zt_componentGuiMakeItem(sizer, " ", chk_static_bodies_only);
	return sizer;
}

// ================================================================================================================================================================================================

#define ZT_PATH_COMPONENT_FILE_VERSION       10001

#define _serialCheck(code) if(!(code)) { zt_logCritical("PathComponent serialization failed."); return false; }


ZT_FUNC_COMPONENT_SAVE(_zt_pathComponentSave)
{
	ZT_PROFILE_GAME("_zt_pathComponentSave");

	ztPathComponent *path_component = (ztPathComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		_serialCheck(zt_serialWrite(serial, ZT_PATH_COMPONENT_GUID));
		_serialCheck(zt_serialWrite(serial, ZT_PATH_COMPONENT_FILE_VERSION));

		_serialCheck(zt_serialWrite(serial, path_component->paths_count));

		zt_fiz(path_component->paths_count) {
			ztPathComponent::Path *path = &path_component->paths[i];
			_serialCheck(zt_serialGroupPush(serial));
			{
				_serialCheck(zt_serialWrite(serial, path_component->paths_ids[path->path_idx].guid));
				_serialCheck(zt_serialWrite(serial, path->entity_id));

				if (path->entity_id != ztInvalidID) {
					_serialCheck(zt_serialWrite(serial, path->selected_node));
					_serialCheck(zt_serialWrite(serial, path->nodes_count));

					zt_fjz(path->nodes_count) {
						ztPathComponent::Node *node = &path->nodes[j];

						_serialCheck(zt_serialWrite(serial, node->index));
						_serialCheck(zt_serialWrite(serial, node->position));

						_serialCheck(zt_serialWrite(serial, (i32)zt_elementsOf(node->neighbors)));
						zt_fkz(zt_elementsOf(node->neighbors)) {
							_serialCheck(zt_serialWrite(serial, node->neighbors[k]));
						}
					}
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_LOAD(_zt_pathComponentLoad)
{
	ZT_PROFILE_GAME("_zt_pathComponentLoad");
	ztPathComponent *path_component = (ztPathComponent*)component->user_data;

	_serialCheck(zt_serialGroupPush(serial));
	{
		ztGuid guid;
		_serialCheck(zt_serialRead(serial, &guid));
		if (guid != ZT_PATH_COMPONENT_GUID) {
			zt_logCritical("PathComponent serialization failed due to mismatch GUID");
			return false;
		}

		i32 version = 0;
		_serialCheck(zt_serialRead(serial, &version));
		if (version > ZT_PATH_COMPONENT_FILE_VERSION) {
			zt_logCritical("PathComponent serialization failed due to unrecognized version identifier");
			return false;
		}

		zt_fiz(ZT_PATH_COMPONENT_MAX_PATHS) {
			path_component->paths[i].entity_id = ztInvalidID;
			path_component->paths[i].path_idx = -1;

			zt_fjze(path_component->paths[i].nodes) {
				path_component->paths[i].nodes[j].index = -1;
			}
		}

		_serialCheck(zt_serialRead(serial, &path_component->paths_count));

		zt_fiz(path_component->paths_count) {
			ztPathComponent::Path *path = &path_component->paths[i];
			_serialCheck(zt_serialGroupPush(serial));
			{
				ztGuid path_guid;
				_serialCheck(zt_serialRead(serial, &path_guid));
				_serialCheck(zt_serialRead(serial, &path->entity_id));

				zt_fxz(path_component->paths_count) {
					if (path_component->paths_ids[x].guid == path_guid) {
						path->path_idx = x;
						break;
					}
				}

				if (path->entity_id != ztInvalidID) {

					if (path->path_idx >= 0) {
						_serialCheck(zt_serialRead(serial, &path->selected_node));
						_serialCheck(zt_serialRead(serial, &path->nodes_count));

						zt_fjz(path->nodes_count) {
							ztPathComponent::Node *node = &path->nodes[j];

							_serialCheck(zt_serialRead(serial, &node->index));
							_serialCheck(zt_serialRead(serial, &node->position));

							i32 neighbors_count = 0;
							_serialCheck(zt_serialRead(serial, &neighbors_count));

							zt_assert(neighbors_count <= zt_elementsOf(node->neighbors));

							zt_fkz(neighbors_count) {
								_serialCheck(zt_serialRead(serial, &node->neighbors[k]));
							}
						}
					}
				}
			}
			_serialCheck(zt_serialGroupPop(serial));
		}
	}
	_serialCheck(zt_serialGroupPop(serial));

	return true;
}

#undef _serialCheck

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_UPDATE(_zt_pathComponentUpdate)
{
	ZT_PROFILE_GAME("_zt_pathComponentUpdate");

	ztPathComponent *path_component = (ztPathComponent *)component->user_data;

	if (pool->editor) {
		bool found = false;
		ztEntityID active_entity = zt_entityEditorGetActiveEntity(pool->editor);

		zt_fiz(path_component->paths_count) {
			if (path_component->paths[i].entity_id == active_entity) {
				found = true;
				//if (path_component->edit_widget.transform != &path_component->markers[i].transform) {
				//	zt_modelEditWidgetFree(&path_component->edit_widget);
				//	zt_modelEditWidgetMake(&path_component->edit_widget, &path_component->markers[i].transform);
				//}
				//
				//zt_modelEditWidgetUpdate(&path_component->edit_widget, input_keys, input_mouse, camera, dt);
			}
		}

		if (!found) {
			path_component->edit_widget.transform = nullptr;
		}
		else {
			if (input_keys[ztInputKeys_Tab].justPressedOrRepeated()) {
				path_component->active_path_adding = !path_component->active_path_adding;
			}

			if (input_keys[ztInputKeys_1].justPressed()) {
				path_component->active_action = ztPathComponent::Action_Add;
			}
			else if(input_keys[ztInputKeys_2].justPressed()) {
				path_component->active_action = ztPathComponent::Action_Del;
			}
			else if(input_keys[ztInputKeys_3].justPressed()) {
				path_component->active_action = ztPathComponent::Action_Move;
			}
			else if(input_keys[ztInputKeys_4].justPressed()) {
				path_component->active_action = ztPathComponent::Action_LinkStep1;
			}
			else if(input_keys[ztInputKeys_5].justPressed()) {
				path_component->active_action = ztPathComponent::Action_UnlinkStep1;
			}
		}
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_QUERY_CLICK(_zt_pathComponentEditQueryClick)
{
	ZT_PROFILE_GAME("_zt_pathComponentEditQueryClick");

	ztPathComponent *path_component = (ztPathComponent *)component->user_data;

	ztEntityID active_entity = zt_entityEditorGetActiveEntity(pool->editor);

	ztPathComponent::Path *path = nullptr;
	i32 test_closest_idx = -1;
	r32 test_closest_dist = ztReal32Max;
	zt_fiz(path_component->paths_count) {
		if (path_component->paths[i].entity_id != active_entity) {
			continue;
		}

		path = &path_component->paths[i];
		zt_fjz(path->nodes_count) {
			ztVec3 sphere_center = path->nodes[j].position;
			r32 intersect_time = ztReal32Max;
			if (zt_collisionRaySphere(ray_pos, ray_dir, sphere_center, .5f, &intersect_time, nullptr)) {
				if (intersect_time < test_closest_dist) {
					test_closest_dist = intersect_time;
					test_closest_idx = j;
				}
			}
		}
	}

	if (test_closest_idx >= 0) {
		*closest_id = test_closest_idx;
		*closest_dist = test_closest_dist;
		return true;
	}

	if (path && path_component->active_path_adding) {
		ztModel *model = nullptr;
		ztVec3 intersect_point = ztVec3::zero;
		ztEntityID entity_id = ztInvalidID;

		if (zt_modelComponentFindModelAndIntersectPoint(path_component->model_component, ray_pos, ray_dir, &entity_id, &model, &intersect_point)) {

			bool add_new_waypoint = true;
			if (path_component->add_to_static_bodies_only) {
				add_new_waypoint = false;
				ztEntity *entity = zt_entityPoolGetEntity(path_component->pool, entity_id);
				zt_flink(component, entity->components) {
					if (component->component->guid == ZT_STATIC_BODY_COMPONENT_GUID) {
						add_new_waypoint = true;
						break;
					}
				}
			}

			if (add_new_waypoint) {
				*closest_id = -100;
				*closest_dist = ztReal32Min;
				path_component->active_path_add_point = intersect_point;
				return true;
			}
		}
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_PROCESS_CLICK(_zt_pathComponentEditProcessClick)
{
	ZT_PROFILE_GAME("_zt_pathComponentEditProcessClick");

	ztPathComponent *path_component = (ztPathComponent *)component->user_data;

	zt_assert(zt_between(path_component->active_path, 0, path_component->paths_count));

	ztPathComponent::Path *path = &path_component->paths[path_component->active_path];

	if (closest_id != -100) {
		i32 prev_selected_node = path->selected_node;
		path->selected_node = closest_id;

		switch (path_component->active_action)
		{
			case ztPathComponent::Action_Add: {
				// do nothing
			} break;

			case ztPathComponent::Action_Del: {
				zt_fiz(path->nodes_count) {
					if (i == path->selected_node) continue;

					if (path->nodes[i].index > path->selected_node) {
						path->nodes[i].index -= 1;
					}
					zt_fjze(path->nodes[i].neighbors) {
						if (path->nodes[i].neighbors[j] == path->selected_node) {
							path->nodes[i].neighbors[j] = -1;
						}
					}
					zt_fjze(path->nodes[i].neighbors) {
						if (path->nodes[i].neighbors[j] > path->selected_node) {
							path->nodes[i].neighbors[j] -= 1;
						}
					}
				}

				for (int j = path->selected_node; j < path->nodes_count - 1; ++j) {
					zt_memCpy(&path->nodes[j], zt_sizeof(ztPathComponent::Node), &path->nodes[j + 1], zt_sizeof(ztPathComponent::Node));
				}

				path->nodes_count -= 1;
				path->nodes[path->nodes_count].index = -1;
			} break;

			case ztPathComponent::Action_Move: {
			} break;

			case ztPathComponent::Action_LinkStep1: {
				path_component->active_action = ztPathComponent::Action_LinkStep2;
			} break;

			case ztPathComponent::Action_LinkStep2: {
				ztPathComponent::Node *origin = &path->nodes[prev_selected_node];
				ztPathComponent::Node *link = &path->nodes[path->selected_node];

				int origin_idx = -1;
				int link_idx = -1;

				bool already_neighbors = origin == link;
				zt_fize(origin->neighbors) {
					if (origin->neighbors[i] == -1 && origin_idx == -1) {
						origin_idx = i;
					}
					if (origin->neighbors[i] == link->index) {
						already_neighbors = true;
					}
				}
				zt_fize(link->neighbors) {
					if (link->neighbors[i] == -1 && link_idx == -1) {
						link_idx = i;
					}
					if (link->neighbors[i] == origin->index) {
						already_neighbors = true;
					}
				}

				if (origin_idx != -1 && link_idx != -1 && !already_neighbors) {
					origin->neighbors[origin_idx] = link->index;
					link->neighbors[link_idx] = origin->index;
				}

				path_component->active_action = ztPathComponent::Action_LinkStep1;

			} break;

			case ztPathComponent::Action_UnlinkStep1: {
				path_component->active_action = ztPathComponent::Action_UnlinkStep2;
			} break;

			case ztPathComponent::Action_UnlinkStep2: {
				ztPathComponent::Node *origin = &path->nodes[prev_selected_node];
				ztPathComponent::Node *link = &path->nodes[path->selected_node];

				ztPathComponent::Node *nodes[2] = { origin, link };

				zt_fxze(nodes){
					int y = (x == 0 ? 1 : 0);
					zt_fize(nodes[x]->neighbors) {
						if (nodes[x]->neighbors[i] == nodes[y]->index) {
							for (int j = i; j < zt_elementsOf(nodes[x]->neighbors) - 1; ++j) {
								nodes[x]->neighbors[j] = nodes[x]->neighbors[j + 1];
							}
							nodes[x]->neighbors[zt_elementsOf(nodes[x]->neighbors) - 1] = -1;
						}
					}
				}

				path_component->active_action = ztPathComponent::Action_UnlinkStep1;
			} break;

		}
		//zt_modelEditWidgetFree(&path_component->edit_widget);
		//zt_modelEditWidgetMake(&path_component->edit_widget, &path_component->markers[closest_id].transform);
		//zt_entityEditorMakeEntityActive(pool->editor, path_component->markers[closest_id].entity_id);
	}
	else {

		switch (path_component->active_action)
		{
			case ztPathComponent::Action_Add: {
				ztVec3 point = path_component->active_path_add_point;
				zt_logDebug("Adding new path node at %.2f, %.2f, %.2f", point.x, point.y, point.z);

				ztPathComponent::Node *node = nullptr;
				zt_fize(path->nodes) {
					if (path->nodes[i].index == -1) {
						node = &path->nodes[i];
						node->index = i;
						break;
					}
				}

				if (node == nullptr) {
					zt_logCritical("No path nodes remain");
					return false;
				}

				node->position = point;

				zt_fize(node->neighbors) {
					node->neighbors[i] = -1;
				}

				path->nodes_count = zt_max(path->nodes_count, node->index + 1);
			} break;

			case ztPathComponent::Action_Move: {
				ztPathComponent::Node *node = &path->nodes[path->selected_node];
				node->position = path_component->active_path_add_point;
			} break;

		}

	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_pathComponentEditDrawDebug)
{
	ZT_PROFILE_GAME("_zt_pathComponentEditDrawDebug");

	ztPathComponent *path_component = (ztPathComponent *)component->user_data;

//	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
//	zt_drawListPushTexture(draw_list, ztTextureDefaultWhite);
//	zt_modelEditWidgetRender(&path_component->edit_widget, camera, draw_list);
//	zt_drawListPopTexture(draw_list);
//	zt_drawListPopShader(draw_list);

}

// ================================================================================================================================================================================================

ZT_FUNC_COMPONENT_EDIT_DRAW_DEBUG(_zt_pathComponentEditDrawDebugAll)
{
	ZT_PROFILE_GAME("_zt_pathComponentEditDrawDebugAll");

	ztPathComponent *path_component = (ztPathComponent*)component->user_data;

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	ztQuat rot = ztQuat::makeFromEuler(-90, 0, 0);
	zt_fiz(path_component->paths_count) {
		ztPathComponent::Path *path = &path_component->paths[i];
		bool is_active = active_entity_id == path->entity_id;
		ztColor color = path_component->paths_ids[path->path_idx].color;

		zt_fjz(path->nodes_count) {

			ztColor this_color = path->selected_node == j && is_active ? color * zt_vec4(.5f, .5f, .5f, 1) : color;

			zt_drawListAddSolidCircle2D(draw_list, path->nodes[j].position, .25f, 8, this_color, &rot);

			zt_fkze(path->nodes[j].neighbors) {
				if (path->nodes[j].neighbors[k] != -1) {
					ztVec3 pos = path->nodes[path->nodes[j].neighbors[k]].position;

					zt_drawListAddLine(draw_list, path->nodes[j].position, pos);
				}
			}

			ztTransform transform = zt_transformMake(path->nodes[j].position, rot);
			ztMat4 mat = zt_transformToMat4(&transform);
			zt_drawListPushTransform(draw_list, mat);

			switch (path_component->active_action)
			{
				case ztPathComponent::Action_Add: {
					// do nothing
				} break;

				case ztPathComponent::Action_Del: {
					zt_drawListAddText2D(draw_list, ztFontDefault, "Delete", ztVec2::zero);
				} break;

				case ztPathComponent::Action_Move: {
					zt_drawListAddText2D(draw_list, ztFontDefault, "Move", ztVec2::zero);
				} break;

				case ztPathComponent::Action_LinkStep1: {
					zt_drawListAddText2D(draw_list, ztFontDefault, "Link Origin", ztVec2::zero);
				} break;

				case ztPathComponent::Action_LinkStep2: {
					if (j != path->selected_node) {
						zt_drawListAddText2D(draw_list, ztFontDefault, "Link Target", ztVec2::zero);
					}
				} break;

				case ztPathComponent::Action_UnlinkStep1: {
					zt_drawListAddText2D(draw_list, ztFontDefault, "Unlink Origin", ztVec2::zero);
				} break;

				case ztPathComponent::Action_UnlinkStep2: {
					if (j != path->selected_node) {
						zt_drawListAddText2D(draw_list, ztFontDefault, "Unlink Target", ztVec2::zero);
					}
				} break;
			}

			zt_drawListPopTransform(draw_list);
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztPath zt_pathMake(ztGuid guid, const char *label, ztColor color)
{
	ztPath path;
	path.guid = guid;
	zt_strCpy(path.label, zt_elementsOf(path.label), label);
	path.color = color;

	return path;
}

// ================================================================================================================================================================================================

bool zt_pathComponentMakeAndRegister(ztPathComponent *path_component, ztEntityPool *pool, ztModelComponent *model_component, ztPath *paths, i32 paths_count)
{
	ZT_PROFILE_GAME("zt_pathComponentMakeAndRegister");

	zt_returnValOnNull(path_component, false);
	zt_returnValOnNull(pool, false);

	path_component->pool = pool;
	path_component->model_component = model_component;
	path_component->add_to_static_bodies_only = true;

	path_component->paths_count = paths_count;
	zt_assertReturnValOnFail(paths_count < zt_elementsOf(path_component->paths), false);

	zt_fiz(paths_count) {
		zt_memCpy(&path_component->paths_ids[i], zt_sizeof(ztPath), &paths[i], zt_sizeof(ztPath));
	}

	zt_fiz(ZT_PATH_COMPONENT_MAX_PATHS) {
		path_component->paths[i].entity_id = ztInvalidID;

		zt_fjze(path_component->paths[i].nodes) {
			path_component->paths[i].nodes[j].index = -1;
		}
	}

	ztComponent *component = nullptr;
	if (zt_entityPoolRegisterComponent(pool, ZT_PATH_COMPONENT_GUID, ZT_PATH_COMPONENT_NAME, path_component,
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentMake),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentFree),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentFind),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentGui),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentSave),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentLoad),
		ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentUpdate), &component) < 0) {

		return false;
	}

	component->component_edit_query_click    = ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentEditQueryClick);
	component->component_edit_process_click  = ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentEditProcessClick);
	component->component_edit_draw_debug     = ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentEditDrawDebug);
	component->component_edit_draw_debug_all = ZT_FUNCTION_POINTER_TO_VAR(_zt_pathComponentEditDrawDebugAll);

	return true;
}

// ================================================================================================================================================================================================

void zt_pathComponentFreeAndUnregister(ztPathComponent *path_component, ztEntityPool *pool)
{
	ZT_PROFILE_GAME("zt_pathComponentFreeAndUnregister");

	if (path_component == nullptr || pool == nullptr) {
		return;
	}

	zt_entityPoolUnregisterComponent(pool, ZT_PATH_COMPONENT_GUID);

	zt_modelEditWidgetFree(&path_component->edit_widget);

	zt_memSet(path_component, zt_sizeof(ztPathComponent), 0);
}

// ================================================================================================================================================================================================

ztComponentID zt_pathComponentAdd(ztPathComponent *path_component, ztEntityPool *pool, ztEntityID entity_id, ztGuid path_guid)
{
	ZT_PROFILE_GAME("zt_pathComponentAdd");

	zt_returnValOnNull(path_component, ztInvalidID);
	zt_returnValOnNull(pool, ztInvalidID);

	zt_fize(path_component->paths) {
		if (path_component->paths[i].entity_id != ztInvalidID && path_component->paths_ids[path_component->paths[i].path_idx].guid == path_guid) {
			zt_logCritical("Only one entity can be assigned to each path");
			return ztInvalidID;
		}
	}

	zt_fiz(path_component->paths_count) {
		if (path_component->paths[i].entity_id == ztInvalidID) {
			path_component->paths[i].entity_id = entity_id;

			zt_entityAddedComponent(pool, entity_id, ZT_PATH_COMPONENT_GUID, i);

			return i;
		}
	}

	return ztInvalidID;
}

// ================================================================================================================================================================================================

void zt_pathComponentRemove(ztPathComponent *path_component, ztEntityPool *pool, ztEntityID entity_id, ztComponentID component_id)
{
	ZT_PROFILE_GAME("zt_pathComponentRemove");

	zt_returnOnNull(path_component);
	zt_returnOnNull(pool);

	zt_fize(path_component->paths) {
		if (path_component->paths[i].entity_id == entity_id) {
			path_component->paths[i].entity_id = ztInvalidID;
			break;
		}
	}

	zt_entityRemovedComponent(pool, entity_id, ZT_PATH_COMPONENT_GUID, component_id);
}

// ================================================================================================================================================================================================

i32 zt_pathComponentPathNodeCount(ztPathComponent *path_component, ztGuid path_guid)
{
	ZT_PROFILE_PATHFINDING("zt_pathComponentPathNodeCount");

	zt_returnValOnNull(path_component, 0);

	zt_fiz(path_component->paths_count) {
		if(path_component->paths_ids[i].guid == path_guid) {
			return path_component->paths[i].nodes_count;
		}
	}

	return 0;
}

// ================================================================================================================================================================================================

i32 zt_pathComponentGeneratePath(ztPathComponent *path_component, ztGuid path_guid, ztPathNode *nodes, i32 nodes_count)
{
	ZT_PROFILE_PATHFINDING("zt_pathComponentGeneratePath");

	zt_returnValOnNull(path_component, 0);
	zt_returnValOnNull(nodes, 0);
	zt_assertReturnValOnFail(nodes_count > 0, 0);

	zt_fvz(pidx, path_component->paths_count) {
		if(path_component->paths_ids[pidx].guid != path_guid) {
			continue;
		}

		ztPathComponent::Path *path = &path_component->paths[pidx];

		if(nodes_count < path->nodes_count) {
			return 0;
		}

		zt_fiz(path->nodes_count) {
			nodes[i].position = path->nodes[i].position;
			nodes[i].user_data = nullptr;
			nodes[i].flags = 0;

			zt_fjze(path->nodes[i].neighbors) {
				if(path->nodes[i].neighbors[j] != -1) {
					nodes[i].neighbors[nodes[i].neighbors_count++] = &nodes[path->nodes[i].neighbors[j]];
				}
			}
		}
		
		return path->nodes_count;
	}

	return 0;
}
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // __zt_game_entity_implementation__
#endif // ZT_GAME_ENTITY_IMPLEMENTATION