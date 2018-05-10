/***************************************************************************************************************************************************************************************************
	file: zt_game_platformer.h v 0.00 (active initial development)
	
	This software is dual-licensed to the public domain and under the following
	license: you are granted a perpetual, irrevocable license to copy, modify,
	publish, and distribute this file as you see fit.
	
	No warranty is offered or implied.  Use this at your own risk.
	
  ***************************************************************************************************************************************************************************************************
   
	Zero Tolerance Game 2D Platformer Library
   
	In exactly one c/cpp source file of your project, you must:

		#define ZT_GAME_PLATFORMER_IMPLEMENTATION
		#include "zt_game_platformer.h"
    
 ***************************************************************************************************************************************************************************************************

    Options:


 ***************************************************************************************************************************************************************************************************

	Implementation Options: (only used with ZT_GAME_PLATFORMER_IMPLEMENTATION #include)


 ***************************************************************************************************************************************************************************************************/

#ifndef __zt_game_platformer_h__
#define __zt_game_platformer_h__

// headers ========================================================================================================================================================================================

#include "zt_game.h"

// types/enums/defines ============================================================================================================================================================================

struct ztPlatformerLayer
{
	ztGuid guid;
	char   name[64];
	r32    parallax_amount; // 1 - identical to camera position, < 1 further back away from camera, > 1 further forward towards camera
};

void zt_platformerLayerMake(ztPlatformerLayer *layer, ztGuid guid, const char *name, r32 parallax_amount);

// ================================================================================================================================================================================================

enum ztPlatformerColliderType_Enum
{
	ztPlatformerColliderType_Surface,
	ztPlatformerColliderType_Spring,
	ztPlatformerColliderType_Blower,
	ztPlatformerColliderType_Blades,
	ztPlatformerColliderType_Magnet,

	ztPlatformerColliderType_TriggerLine,
	ztPlatformerColliderType_TriggerCircle,
	ztPlatformerColliderType_TriggerRect,

	ztPlatformerColliderType_Sprite,

	ztPlatformerColliderType_Marker,

	ztPlatformerColliderType_MAX,
};

// ================================================================================================================================================================================================

struct ztPlatformerCollider;
struct ztPlatformerMovementPath;
struct ztPlatformerLevelEditor;

#define ZT_FUNC_PLATFORMER_COLLIDER_MOVEMENT_PATH_UPDATE(name) r32 name(ztPlatformerCollider *collider, ztPlatformerMovementPath *movement_path, i32 movement_idx, r32 percent_there, void *user_data)
typedef ZT_FUNC_PLATFORMER_COLLIDER_MOVEMENT_PATH_UPDATE(ztPlatformerCollideMovementPathUpdate_Func);

#define ZT_FUNC_PLATFORMER_COLLIDER_MOVING_SURFACE_UPDATE(name) r32 name(ztPlatformerCollider *collider, void *user_data, r32 percent)
typedef ZT_FUNC_PLATFORMER_COLLIDER_MOVING_SURFACE_UPDATE(ztPlatformerColliderMovingSurfaceUpdate_Func);

// ================================================================================================================================================================================================

#ifndef ZT_PLATFORMER_MOVEMENT_PATH_MAX_POINTS
#define ZT_PLATFORMER_MOVEMENT_PATH_MAX_POINTS	32
#endif

// ================================================================================================================================================================================================

enum ztPlatformerMovementPathType_Enum
{
	ztPlatformerMovementPathType_Loops,
	ztPlatformerMovementPathType_PingPong,

	ztPlatformerMovementPathType_MAX,
};

// ================================================================================================================================================================================================

struct ztPlatformerMovementPath
{
	ztGuid                            guid;
	ztPlatformerMovementPathType_Enum type;
	i32                               points;
	ztVec2                            movements[ZT_PLATFORMER_MOVEMENT_PATH_MAX_POINTS]; // these are relative movements
	r32                               times    [ZT_PLATFORMER_MOVEMENT_PATH_MAX_POINTS];

	r32                               current_time;

	char                              name[64];
};

// ================================================================================================================================================================================================

enum ztPlatformerColliderFlags_Enum
{
	ztPlatformerColliderFlags_Disabled = (1<<0),
};

// ================================================================================================================================================================================================

struct ztPlatformerCollider
{
	ztPlatformerColliderType_Enum type;
	char                          name[64];
	i32                           movement_path;
	r32                           movement_offset;
	r32                           movement_speed;
	ztVec2                        offset_last, offset_this;
	ztVec2                        points[2];
	i32                           flags;

	union {
		struct {
			r32                   strength;
		} spring;

		struct {
			r32                   strength;
		} blower;

		struct {
			r32                   radius;
			r32                   speed;
		} blades;

		struct {
			r32                   strength;
		} magnet;

		struct {
			r32                   radius;
		} trigger_circle;

		struct {
			r32                   height;
		} trigger_rect;

		struct {
			u32                     hash;
			r32                     rotation;
			i32                     layer;
			ztSprite                sprite;
			ztVec2                  scale;
			ztSpriteAnimController *anim_controller; // will use active sprite if this is set
		} sprite;

		struct {
			i32                   type;
			char                  info[32];
		} marker;
	};
};

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztPlatformerLevelCollision
{
	ztPlatformerCollider       *collider;
	r32                         time;
	ztVec2                      point;
	ztVec2                      normal;
	bool                        force_movement;

	ztPlatformerLevelCollision *next;
};

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztPlatformerPhysicsObjectType_Enum
{
	ztPlatformerPhysicsObjectType_Invalid,
	ztPlatformerPhysicsObjectType_AABB,

	ztPlatformerPhysicsObjectType_MAX,
};

// ================================================================================================================================================================================================

enum ztPlatformerPhysicsObjectFlags_Enum
{
	ztPlatformerPhysicsObjectFlags_Kinematic        = (1<<0),
	ztPlatformerPhysicsObjectFlags_KinematicIfMoved = (1<<1),
};

// ================================================================================================================================================================================================

struct ztPlatformerPhysicsObject
{
	ztVec2                             position;
	ztVec2                             velocity;
	ztVec2                             aabb_center;
	ztVec2                             aabb_size;
	i32                                flags;
	r32                                mass;
	i32                                collision_flags; // flags used to determine if other objects would collide with this
	i32                                collides_with;   // flags used to determine what objects to this object can collide with

	r32                                angular_velocity;
	r32                                velocity_transfer; // how much velocity changes when bouncing

	ztPlatformerPhysicsObjectType_Enum type;

	ztPlatformerLevelCollision        *collisions;
	ztPlatformerCollider              *collider_resting_on;
	r32                                movement_since_last_collision;

	union {
		struct {
			ztVec2 center;
			ztVec2 size;
		} aabb;
	};
};

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztPlatformerLevel
{
	ztGuid                      guid;
	char                        name[64];
	r32                         gravity;
	r32                         terminal_velocity;
	r32                         air_friction_multiplier;
	ztColorGradient2            background_color;
	r32                         background_rotation;

	ztPlatformerCollider       *colliders;
	i32                         colliders_size;
	i32                         colliders_used;

	ztPlatformerMovementPath   *movement_paths;
	i32                         movement_paths_size;
	i32                         movement_paths_used;


	// the following are not serialized:

	ztPlatformerLayer          *layers;
	i32                         layers_size;

	ztQuadTree                  quadtree;
	ztQuadTree                  quadtree_visual;

	ztPlatformerLevelCollision *collisions;
	i32                         collisions_used;
	i32                         collisions_size;

	ZT_FUNCTION_POINTER_VAR    (movement_path_update_function, ztPlatformerCollideMovementPathUpdate_Func);
	void                       *movement_path_update_function_user_data;
};

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void                  zt_platformerLevelMake                     (ztPlatformerLevel *level, ztPlatformerLayer *layers, i32 layers_size, i32 max_colliders, i32 max_movement_paths, i32 max_collisions = 128);
void                  zt_platformerLevelFree                     (ztPlatformerLevel *level);

bool                  zt_platformerLevelSave                     (ztPlatformerLevel *level, const char *filename);
bool                  zt_platformerLevelLoad                     (ztPlatformerLevel *level, ztSpriteManager *sprite_manager, const char *filename); // already created using zt_platformerLevelMake
bool                  zt_platformerLevelLoad                     (ztPlatformerLevel *level, ztSpriteManager *sprite_manager, ztAssetManager *asset_manager, ztAssetID asset_id);
bool                  zt_platformerLevelLoad                     (ztPlatformerLevel *level, ztSpriteManager *sprite_manager, void *data, i32 data_size);

i32                   zt_platformerAddMovementPath               (ztPlatformerLevel *level, ztPlatformerMovementPath **movement_path, ztGuid guid);

i32                   zt_platformerAppendCollider                (ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2); // collider will have a normal where p1 is left and p2 is right
i32                   zt_platformerAppendColliderRect            (ztPlatformerLevel *level, ztVec2 center, ztVec2 size);
i32                   zt_platformerAppendColliderSpring          (ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2, r32 strength);
i32                   zt_platformerAppendColliderBlower          (ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2, r32 strength);
i32                   zt_platformerAppendColliderBlades          (ztPlatformerLevel *level, ztVec2 p, r32 radius, r32 speed);
i32                   zt_platformerAppendColliderMagnet          (ztPlatformerLevel *level, ztVec2 p, r32 strength);
i32                   zt_platformerAppendColliderTriggerLine     (ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2);
i32                   zt_platformerAppendColliderTriggerCircle   (ztPlatformerLevel *level, ztVec2 p, r32 radius);
i32                   zt_platformerAppendColliderTriggerRect     (ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2, r32 height);
i32                   zt_platformerAppendMarker                  (ztPlatformerLevel *level, ztVec2 p, i32 type, char *info);
i32                   zt_platformerAppendSprite                  (ztPlatformerLevel *level, ztVec2 p, u32 hash, r32 rotation, i32 layer, ztSprite *sprite);


i32                   zt_platformerGetColliderIndex              (ztPlatformerLevel *level, ztPlatformerCollider *collider);
ztVec2                zt_platformerGetColliderVelocity           (ztPlatformerCollider *collider);
void                  zt_platformerGetColliderPositions          (ztPlatformerLevel *level, ztPlatformerCollider *collider, ztVec2 *p0, ztVec2 *p1, ztVec2 *n, bool apply_offset = true);

i32                   zt_platformerGetCollidersThatIntersectAABB (ztPlatformerLevel *level, ztVec2 aabb_center, ztVec2 aabb_size, ztPlatformerCollider **colliders, i32 colliders_size);
i32                   zt_platformerGetCollidersThatIntersectAABB (ztPlatformerLevel *level, ztVec2 aabb_center, ztVec2 aabb_size, i32 *colliders, i32 colliders_size);
i32                   zt_platformerGetCollidersThatIntersectLine (ztPlatformerLevel *level, ztVec2 line_beg, ztVec2 line_end, ztPlatformerCollider **colliders, i32 colliders_size);
i32                   zt_platformerGetCollidersThatIntersectLine (ztPlatformerLevel *level, ztVec2 line_beg, ztVec2 line_end, i32 *colliders, i32 colliders_size);
ztPlatformerCollider *zt_platformerGetNearestCollider            (ztPlatformerLevel *level, ztVec2 point, ztPlatformerColliderType_Enum valid_types, r32 within_distance, i32 *collider_idx);
ztPlatformerCollider *zt_platformerGetNearestCollider            (ztPlatformerLevel *level, ztVec2 point, ztPlatformerColliderType_Enum *valid_types, i32 valid_types_size, r32 within_distance, i32 *collider_idx);

void                  zt_platformerSetMovementPath               (ztPlatformerLevel *level, i32 collider_idx, i32 movement_path_idx, r32 time_offset = 0);
void                  zt_platformerSetColliderName               (ztPlatformerLevel *level, i32 collider_idx, const char *name);

void                  zt_platformerRecalcQuadTree                (ztPlatformerLevel *level);
void                  zt_platformerResetMovementPaths            (ztPlatformerLevel *level);

void                  zt_platformerUpdateColliders               (ztPlatformerLevel *level, r32 dt);
void                  zt_platformerUpdatePhysicsObjects          (ztPlatformerLevel *level, ztPlatformerPhysicsObject *objects, i32 objects_size, r32 dt);

void                  zt_platformerDrawBackground                (ztPlatformerLevel *level, ztDrawList *draw_list, ztCamera *camera);
void                  zt_platformerDraw                          (ztPlatformerLevel *level, ztDrawList *draw_list, ztCamera *camera, i32 layer, ztPlatformerPhysicsObject *objects, i32 objects_size, bool apply_parallax);

//                    these will only work if there is only one texture being used:
i32                   zt_platformerGetBackgroundTriangles        (ztPlatformerLevel *level, ztCamera *camera, ztVec3 *pos, ztVec2 *uvs, i32 triangles_size);
i32                   zt_platformerGetTriangles                  (ztPlatformerLevel *level, ztCamera *camera, i32 layer, ztPlatformerPhysicsObject *objects, i32 objects_size, bool apply_parallax, ztVec3 *pos, ztVec2 *uvs, i32 triangles_size);

ztVec2                zt_platformerGetPositionOnLayer            (ztPlatformerLevel *level, i32 layer, ztVec2 position, ztCamera *camera);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztPlatformerDrawDebugFlags_Enum
{
	ztPlatformerDrawDebugFlags_DrawQuadTree      = (1<<0),
	ztPlatformerDrawDebugFlags_DrawColliders     = (1<<1),
	ztPlatformerDrawDebugFlags_DrawGrid          = (1<<2),
	ztPlatformerDrawDebugFlags_DrawMarkerSprites = (1<<3),
};

// ================================================================================================================================================================================================

void zt_platformerDrawDebugView           (ztPlatformerLevel *level, ztDrawList *draw_list, ztPlatformerLevelEditor * level_editor, i32 layer, ztVec2 mpos, i32 flags = ztPlatformerDrawDebugFlags_DrawColliders);
void zt_platformerDrawDebugPhysicsObjects (ztPlatformerLevel *level, ztDrawList *draw_list, ztPlatformerPhysicsObject *objects, i32 objects_size, i32 flags = 0);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
//
//	Enemy Attributes & Abilities Guideline
//
//	Combine these attributes and abilities to make interesting enemies
//
//	List drawn from: http://www.gamasutra.com/blogs/GarretBright/20140422/215978/Build_a_Bad_Guy_Workshop__Designing_enemies_for_retro_games.php
//
//	Movement Attributes:
//		Stationary      -- The enemy does not move at all
//		Walker          -- The enemy walks or runs along the ground
//		Riser           -- The enemy can increase its height
//		Ducker          -- The enemy can reduce its height
//		Faller          -- The enemy falls from the ceiling onto the ground
//		Jumper          -- The enemy can bounce or jump
//		Floater         -- The enemy can float  fly  or levitate
//		Sticky          -- The enemy sticks to walls and ceilings
//		Waver           -- The enemy floats in a sine wave pattern
//		Rotator         -- The enemy rotates around a fixed point
//		Swinger         -- The enemy swings from a fixed point
//		Pacer           -- The enemy changes direction
//		Follower        -- The enemy follows the player
//		Roamer          -- The enemy changes direction completely randomly
//		Liner           -- The enemy moves in a straight line directly to a spot on the screen
//		Teleporter      -- The enemy can teleport from one location to another
//		Dasher          -- The enemy dashes in a direction  faster than its normal movement speed
//		Ponger          -- The enemy ignores gravity and physics  and bounces off walls in straight lines
//		GeoBound        -- The enemy is physically stuck to the geometry of the level
//		Tethered        -- The enemy is tethered to the level's geometry by a chain or a rope
//		Swooper         -- A floating enemy that swoops down
//		Mirror          -- The enemy mirrors the movement patterns of the player
//
//	Quality Attributes:
//		GeoIgnore       -- The enemy ignores the properties of the level's geometry and can pass through solid objects
//		Shielder        -- Player attacks are nullified when hit from a specific direction or angle, or hit a specific spot on the enemy
//		Deflector       -- Player's ranged attacks are reflected when the enemy is hit by them
//		Secret Spot     -- The enemy has a specific spot where damage can only be taken when that spot is hit
//		Invulnerable    -- The enemy cannot be harmed or killed
//		Revivor         -- The enemy is revived after dying
//		Regenerator     -- The enemy's health is regenerated over time
//		Secret Weakness -- The enemy is vulnerable to specific types of attacks
//		Hard to Hit     -- These enemies are specifically hard to hit
//		Segmented       -- These enemies are made up of smaller individual objects or enemies
//		Bumper          -- These enemies act like pinball bumpers, pushing the player (or other objects) away quickly
//		GeoMimic        -- These enemies have properties of level geometry
//		Alarm           -- An enemy or object that causes another enemy or object to react
//
//	Abilities
//		Grower          -- The enemy can grow in size
//		Shrinker        -- The enemy can shrink in size
//		Forcer          -- The enemy can apply direct movement force to the player
//		Carrier         -- The enemy can carry another enemy, an object, or the player
//		Thrower         -- The enemy can throw whatever it is holding
//		Emitter         -- The enemy 'emits' another enemy or projectile
//		Splitter        -- The enemy can split into multiple other enemies while destroying itself
//		Cloner          -- The enemy can duplicate itself
//		Morpher         -- The enemy morphs into another enemy type
//		Sapper          -- The enemy can cause the player's stats to be modified
//		Latcher         -- Like a Sapper, the enemy can drain the player's stats and abilities, but does so by latching on to the player
//		Hider           -- The enemy can hide from the player
//		Switcher        -- The enemy can toggle between various attributes
//		Exploder        -- The enemy can destroy itself and cause splash damage
//		Interactor      -- The enemy can interact with scripted objects, such as levers or buttons
//		Charger         -- The enemy will pause its behavior between switching to another behavior
//
//================================================================================================================================================================================================


// ================================================================================================================================================================================================

struct ztPlatformerActorInstance;

struct ztPlatformerActorCollision
{
	ztPlatformerActorInstance *actors[2];
	i32                        aabbs[2];
	ztVec2                     normal;
	r32                        depth;
	i32                        face;
};

// ================================================================================================================================================================================================

struct ztPlatformerLevel;
struct ztPlatformerActorTemplate;

#define ZT_FUNC_PLATFORMER_ACTOR_COLLISION(name) void name(ztPlatformerLevel * level, ztPlatformerActorCollision *collision, void *user_data)
typedef ZT_FUNC_PLATFORMER_ACTOR_COLLISION(ztPlatformerActorCollision_Func);

// ================================================================================================================================================================================================

struct ztPlatformerActorTemplate
{
	ztVec2                     aabb_centers[8];
	ztVec2                     aabb_sizes[8];
	int                        aabb_count;

	ztVec2                     aabb_overall_center; // including all aabbs
	ztVec2                     aabb_overall_size;   // including all aabbs

	i32                        custom_id;
	i32                        custom_flags;

	i32                        collision_flags;     // identifies what kind of object this is
	i32                        collides_with;       // identifies what kind of object this object collides with

	void                      *user_data;

	ztPlatformerActorInstance *actor_instances;
	i32                        actor_instances_count;

	ZT_FUNCTION_POINTER_VAR   (collision_func, ztPlatformerActorCollision_Func);
	void                      *collision_user_data;
};

// ================================================================================================================================================================================================

void zt_platformerActorTemplateInit(ztPlatformerActorTemplate *actor_template, i32 collision_flags, i32 collides_with, ztPlatformerActorInstance *actor_instances, i32 actor_instances_count, ZT_FUNCTION_POINTER_VAR(collision_func, ztPlatformerActorCollision_Func) = ZT_FUNCTION_POINTER_TO_VAR_NULL, void *collision_user_data = nullptr);

// ================================================================================================================================================================================================

enum ztPlatformerActorInstanceFlags_Enum
{
	ztPlatformerActorInstanceFlags_Enabled = (1 << 0),
	ztPlatformerActorInstanceFlags_Alive   = (1 << 1),

	ztPlatformerActorInstanceFlags_MAX     = 2,
};

// ================================================================================================================================================================================================

struct ztPlatformerActorInstance
{
	ztPlatformerActorTemplate *actor_template;

	i32                        index; // index into template actor instances array
	ztVec2                     position;
	i32                        flags;

	i32                        user_id;
	i32                        user_flags;

	ztPlatformerPhysicsObject *physics_object;
};


// ================================================================================================================================================================================================

void                       zt_platformerActorsUpdate(ztPlatformerLevel *level, ztPlatformerActorInstance *instances, i32 instances_count, r32 dt);

void                       zt_platformerCharacterActorMakeTemplate(ztPlatformerActorTemplate *character_template, ztPlatformerActorInstance *instances, i32 instances_count, i32 collision_flags, i32 collides_with, ZT_FUNCTION_POINTER_VAR(collision_func, ztPlatformerActorCollision_Func), void *collision_user_data);
ztPlatformerActorInstance *zt_platformerCharacterActorMakeInstance(ztPlatformerActorTemplate *character_template, ztPlatformerPhysicsObject *physics_object);


// ================================================================================================================================================================================================
// sample enemy that walks - copy and modify to make custom enemies

struct ztPlatformerEnemySimpleWalkerTemplate
{
	r32                         speed; // speed of walk

	struct Instance
	{
		i32                     direction;
		i32                     surface_idx;
		ztSpriteAnimController *animation;
	};

	Instance                   *instances;
	i32                         instances_count;

	ztPlatformerActorTemplate   actor_template;
};

void zt_platformerEnemySimpleWalkerMake  (ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztPlatformerActorInstance *instances, i32 instances_count, i32 collision_flags, i32 collides_with, r32 speed = 1);
void zt_platformerEnemySimpleWalkerFree  (ztPlatformerEnemySimpleWalkerTemplate *enemy_template);
void zt_platformerEnemySimpleWalkerUpdate(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztPlatformerLevel *level, r32 dt);
void zt_platformerEnemySimpleWalkerRender(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztDrawList *draw_list, bool draw_bounding_box);

ztPlatformerActorInstance *zt_platformerEnemySimpleWalkerNewInstance(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztPlatformerLevel *level, ztVec2 pos, ztPlatformerCollider *surface_walking_on, i32 direction, ztSpriteAnimController *anim_controller);


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztPlatformerCharacterControllerFlags_Enum
{
	ztPlatformerCharacterControllerFlags_FixedJumpHeight          = (1<<0),
	ztPlatformerCharacterControllerFlags_FixedJumpHalfHeight      = (1<<1),
	ztPlatformerCharacterControllerFlags_AllowMultiJump           = (1<<2),
	ztPlatformerCharacterControllerFlags_AllowMultiJumpInFall     = (1<<3),

	ztPlatformerCharacterControllerFlags_WallJump                 = (1<<4),
	ztPlatformerCharacterControllerFlags_EdgeGrab                 = (1<<5),

	ztPlatformerCharacterControllerFlags_ChangeDirectionInstantly = (1<<6),
};

// ================================================================================================================================================================================================

enum ztPlatformerCharacterControllerInternalFlags_Enum
{
	ztPlatformerCharacterControllerInternalFlags_InJump       = (1<<0),
	ztPlatformerCharacterControllerInternalFlags_InHalfJump   = (1<<1),
	ztPlatformerCharacterControllerInternalFlags_InMove       = (1<<2),
	ztPlatformerCharacterControllerInternalFlags_AtRest       = (1<<3),
	ztPlatformerCharacterControllerInternalFlags_JumpForgive  = (1<<4),
	ztPlatformerCharacterControllerInternalFlags_WasOnSpring  = (1<<5),
	ztPlatformerCharacterControllerInternalFlags_AgainstWall  = (1<<6),
	ztPlatformerCharacterControllerInternalFlags_JumpReleased = (1<<7),
};

// ================================================================================================================================================================================================

#ifndef ZT_PLATFORMER_CHARACTER_CONTROLLER_MAX_JUMPS
#define ZT_PLATFORMER_CHARACTER_CONTROLLER_MAX_JUMPS   2
#endif

// ================================================================================================================================================================================================

struct ztPlatformerCharacterControllerSettings
{
	i32         flags;

	r32         jump_velocities[ZT_PLATFORMER_CHARACTER_CONTROLLER_MAX_JUMPS];      // the peak velocities per jump
	r32         jump_times     [ZT_PLATFORMER_CHARACTER_CONTROLLER_MAX_JUMPS];      // amount of time to increase velocity in non-fixed scenerios
	r32         jump_time_full_threshold;                                           // after this amount of time, the jump will be considered full if ztPlatformerCharacterControllerFlags_FixedJumpHalfHeight is set
	r32         jump_half_slowdown_velocity;
	r32         jump_forgiveness;                                                   // how much time can pass after falling off a collider does the player have to execute a jump?
	r32         spring_time_forgiveness;                                            // how much time can pass after landing on a spring can the jump be pressed to boost height?
	r32         spring_jump_multiplier;                                             // how much boost does a spring jump give to the jump velocity?
	ztVec2      wall_jump_velocity;                                                 // how much of a boost does jumping off a wall give?
	r32         wall_slide_max_velocity;                                            // how fast can the character slide down a wall (set lower than gravity to slow down descent)
	r32         wall_jump_movement_pause;                                           // how much time before the player's opposing button press will affect movement
	
	ztAnimCurve jump_accels[ZT_PLATFORMER_CHARACTER_CONTROLLER_MAX_JUMPS];  // the amount of acceleration for jumps (with variable height jumps)

	r32         side_walk_accel;
	r32         side_walk_max_vel;

	r32         side_run_accel;
	r32         side_run_max_vel;

	r32         side_decel;

	r32         wall_cling_max_dist;


	struct {
		r32     x_axis;
		bool    jump;
		bool    jump_held;
		bool    run;
	} input;


	struct {
		i32     jumps;
		r32     jump_time;
		r32     run_time;
		i32     state_flags;
		r32     fall_time;
		r32     time_since_spring;
		i32     last_side_direction;
		i32     wall_collider;
		r32     wall_collider_dist;
		r32     wall_cling_time;
		r32     wall_jump_movement_time;

		ztVec2  outside_force;
		r32     outside_force_time_max;
		r32     outside_force_time;
	} _internal;
};


void zt_platformerCharacterControllerUpdate(ztPlatformerLevel *level, ztPlatformerCharacterControllerSettings *settings, ztPlatformerPhysicsObject *character, r32 dt);


void zt_platformerCharacterControllerSetupPreset1(ztPlatformerLevel *level, ztPlatformerCharacterControllerSettings *settings, ztPlatformerPhysicsObject *character);


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztPlatformerLevelEditorActionType_Enum
{
	ztPlatformerLevelEditorActionType_NewCollider,
	ztPlatformerLevelEditorActionType_EditCollider,
	ztPlatformerLevelEditorActionType_DeleteCollider,
};

// ================================================================================================================================================================================================

struct ztPlatformerLevelEditorAction
{
	ztPlatformerLevelEditorActionType_Enum type;
	r64                                    time;
	i32                                    group;

	union {
		struct {
			i32                            collider_idx;
			ztPlatformerCollider           collider;
		} new_collider;

		struct {
			i32                            collider_idx;
			ztPlatformerCollider           collider_before;
			ztPlatformerCollider           collider_after;
		} edit_collider;

		struct {
			i32                            collider_idx;
			ztPlatformerCollider           collider;
		} delete_collider;
	};
};

// ================================================================================================================================================================================================

struct ztPlatformerLevelEditorBlueprint
{
	char                              name[64];
	ztPlatformerLevelEditorAction    *actions;
	i32                               actions_size;
	ztVec2                            size;
	ztPlatformerLevelEditorBlueprint *next;
};

// ================================================================================================================================================================================================

enum ztPlatformerLevelEditorMouseState_Enum
{
	ztPlatformerLevelEditorMouseState_Waiting,
	ztPlatformerLevelEditorMouseState_DraggingEmpty,
	ztPlatformerLevelEditorMouseState_DraggingCollider,
	ztPlatformerLevelEditorMouseState_DraggingColliderPoint,
	ztPlatformerLevelEditorMouseState_DraggingMakeSelection,
	ztPlatformerLevelEditorMouseState_DraggingSelection,
	ztPlatformerLevelEditorMouseState_Blueprint,
	ztPlatformerLevelEditorMouseState_Tile,

	ztPlatformerLevelEditorMouseState_MAX
};

// ================================================================================================================================================================================================

struct ztPlatformerLevelEditorTile
{
	char     name[64];
	ztSprite sprite;
	r32      rotation;
	u32      hash;
};

// ================================================================================================================================================================================================

void zt_platformerLevelEditorTile(ztPlatformerLevelEditorTile *tile, const char *name, ztSprite *sprite, r32 rotation, u32 hash);

// ================================================================================================================================================================================================

struct ztPlatformerLevelEditorMarker
{
	char      name[64];
	i32       value;
	char      info[32];
	ztVec2    area_center;
	ztVec2    area_size;
	ztSprite *sprite;
	ztVec2    sprite_offset;
	ztVec2    sprite_scale;
};

// ================================================================================================================================================================================================

void zt_platformerLevelEditorMarker(ztPlatformerLevelEditorMarker *marker, const char *name, i32 value, char *info, ztVec2 area_center, ztVec2 area_size, ztSprite *sprite, ztVec2 sprite_offset, ztVec2 sprite_scale = ztVec2::one);

// ================================================================================================================================================================================================

struct ztPlatformerLevelEditor
{
	ztPlatformerLevel                     *level;

	char                                   file_name[ztFileMaxPath];
	char                                   file_name_working[ztFileMaxPath];
	char                                   levels_path[ztFileMaxPath];

	bool                                   enabled;
	i32                                    active_collider;
	i32                                    active_collider_point;
	ztPlatformerCollider                   active_collider_copy;

	i32                                   *selection;
	i32                                    selection_count;

	bool                                  *layer_show;
	bool                                  *layer_lock;

	ztVec2                                 mouse_pos;
	ztVec2                                 mouse_movement;
	ztPlatformerLevelEditorMouseState_Enum mouse_state;
	r32                                    mouse_time_since_change;
	ztVec2                                 mouse_drag_pos_start;
	bool                                   mouse_drag_confirmed;
	ztPlatformerLevelEditorBlueprint      *mouse_blueprint;
	ztPlatformerLevelEditorTile           *mouse_tile;
	bool                                   mouse_dragging_camera;
	ztVec2                                 mouse_dragging_camera_pos;
	bool                                   gui_had_input;
	ztVec2                                 last_cam_pos;

	bool                                   hide_widgets;

	ztPlatformerLevelEditorAction         *actions;
	i32                                    actions_size;
	i32                                    actions_first;
	i32                                    actions_last;
	i32                                    actions_current;
	i32                                    actions_group;

	ztPlatformerLevelEditorTile           *tiles;
	i32                                    tiles_size;
	r32                                    tiles_unit_size;

	ztPlatformerLevelEditorMarker         *markers;
	i32                                    markers_size;

	ztPlatformerLevelEditorBlueprint      *blueprints;

	ztSpriteManager                       *sprite_manager;


	bool       opts_draw_grid;
	bool       opts_snap_points;
	r32        opts_snap_increment;

	ztGuiItem *gui_right_click_menu;
	ztGuiItem *gui_right_click_menu_colliders;
	ztGuiItem *gui_active_item;
	ztGuiItem *gui_active_item_name_edit;

	ztGuiItem *gui_tools;

	ztGuiItem *gui_blueprints;
	ztGuiItem *gui_blueprints_sizer;
	ztGuiItem *gui_blueprints_button;
	ztGuiItem *gui_tiles;
	ztGuiItem *gui_layers_list;
	ztGuiItem *gui_items_count;

	ztGuiItem *gui_background_color_gradient;

	bool       skip_quadtree_recalc;

	i32        selection_layer;
	r32        selection_movement_offset;
	r32        selection_movement_speed;
};

// ================================================================================================================================================================================================

bool zt_platformerLevelEditorMake        (ztPlatformerLevelEditor *editor, ztPlatformerLevel *level, ztSpriteManager *sprite_manager, ztPlatformerLevelEditorTile *tiles, i32 tiles_size, ztPlatformerLevelEditorMarker *markers, i32 markers_size, i32 action_buffer_size = 512);
void zt_platformerLevelEditorFree        (ztPlatformerLevelEditor *editor);

void zt_platformerLevelEditorEnable      (ztPlatformerLevelEditor *editor, bool enabled = true);
bool zt_platformerLevelEditorUpdate      (ztPlatformerLevelEditor *editor, ztInputKeys *input_keys, ztInputMouse *input_mouse, bool gui_input, ztCamera *game_camera, ztCamera *gui_camera, r32 dt);
void zt_platformerLevelEditorDraw        (ztPlatformerLevelEditor *editor, ztDrawList *draw_list, ztCamera *game_camera);
void zt_platformerLevelEditorDrawWidgets (ztPlatformerLevelEditor *editor, ztDrawList *draw_list, ztCamera *game_camera);


// ================================================================================================================================================================================================

#endif // include guard


#if defined(ZT_GAME_PLATFORMER_IMPLEMENTATION) || defined(ZT_GAME_PLATFORMER_INTERNAL_DECLARATIONS)

#define ZT_GAME_PLATFORMER_INTERNAL_DECLARATIONS


#endif // defined(ZT_GAME_PLATFORMER_IMPLEMENTATION) || defined(ZT_GAME_PLATFORMER_INTERNAL_DECLARATIONS)

#if defined(ZT_GAME_PLATFORMER_IMPLEMENTATION)

#ifndef __zt_game_platformer_implementation__
#define __zt_game_platformer_implementation__


// variables ======================================================================================================================================================================================

#define ZT_PLATFORMER_MARKER_RADIUS	.2f

// private functions ==============================================================================================================================================================================

ztVec2 _zt_platformerSnapPosition(ztPlatformerLevelEditor *editor, ztVec2 pos, bool snap_disable, r32 snap = ztReal32Min)
{
	if (snap_disable) {
		return pos;
	}

	if (snap == ztReal32Min) {
		snap = editor->opts_snap_increment;
	}

	if (pos.x > 0) pos.x += snap;
	if (pos.y > 0) pos.y += snap;

	r32 modx = zt_fmod(pos.x, snap);
	pos.x -= modx;

	r32 mody = zt_fmod(pos.y, snap);
	pos.y -= mody;

	return pos;
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerBlowerGetPoints(ztPlatformerLevel *level, ztPlatformerCollider *collider, ztVec2 *p0, ztVec2 *p1, ztVec2 *p2, ztVec2 *p3, bool apply_offset = true)
{
	ztVec2 n;
	zt_platformerGetColliderPositions(level, collider, p1, p2, &n, apply_offset);

	*p0 = *p1 + n * collider->blower.strength;
	*p3 = *p2 + n * collider->blower.strength;
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerRectGetPoints(ztPlatformerLevel *level, ztPlatformerCollider *collider, ztVec2 *p0, ztVec2 *p1, ztVec2 *p2, ztVec2 *p3, bool apply_offset = true)
{
	ztVec2 n;
	zt_platformerGetColliderPositions(level, collider, p1, p2, &n, apply_offset);

	*p0 = *p1 + n * collider->trigger_rect.height;
	*p3 = *p2 + n * collider->trigger_rect.height;
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerGetExtents(ztPlatformerLevel *level, ztPlatformerCollider *collider, ztVec2 *pmin, ztVec2 *pmax, bool apply_min_size)
{
	ztVec2 min = ztVec2::max;
	ztVec2 max = ztVec2::min;

	if (collider->type == ztPlatformerColliderType_Blower) {
		ztVec2 p0, p1, p2, p3;
		_zt_platformerBlowerGetPoints(level, collider, &p0, &p1, &p2, &p3, false);

		min.x = zt_min(min.x, zt_min(p0.x, zt_min(p1.x, zt_min(p2.x, p3.x))));
		min.y = zt_min(min.y, zt_min(p0.y, zt_min(p1.y, zt_min(p2.y, p3.y))));
		max.x = zt_max(max.x, zt_max(p0.x, zt_max(p1.x, zt_max(p2.x, p3.x))));
		max.y = zt_max(max.y, zt_max(p0.y, zt_max(p1.y, zt_max(p2.y, p3.y))));
	}
	else if (collider->type == ztPlatformerColliderType_Blades) {
		ztVec2 bmin = zt_vec2(collider->points[0].x - collider->blades.radius, collider->points[0].y - collider->blades.radius);
		ztVec2 bmax = zt_vec2(collider->points[0].x + collider->blades.radius, collider->points[0].y + collider->blades.radius);

		min.x = zt_min(min.x, bmin.x);
		min.y = zt_min(min.y, bmin.y);
		max.x = zt_max(max.x, bmax.x);
		max.y = zt_max(max.y, bmax.y);
	}
	else if (collider->type == ztPlatformerColliderType_Magnet) {
		ztVec2 mmin = zt_vec2(collider->points[0].x - collider->magnet.strength, collider->points[0].y - collider->magnet.strength);
		ztVec2 mmax = zt_vec2(collider->points[0].x + collider->magnet.strength, collider->points[0].y + collider->magnet.strength);

		min.x = zt_min(min.x, mmin.x);
		min.y = zt_min(min.y, mmin.y);
		max.x = zt_max(max.x, mmax.x);
		max.y = zt_max(max.y, mmax.y);
	}
	else if (collider->type == ztPlatformerColliderType_Blower) {
		ztVec2 p0, p1, p2, p3;
		_zt_platformerRectGetPoints(level, collider, &p0, &p1, &p2, &p3, false);

		min.x = zt_min(min.x, zt_min(p0.x, zt_min(p1.x, zt_min(p2.x, p3.x))));
		min.y = zt_min(min.y, zt_min(p0.y, zt_min(p1.y, zt_min(p2.y, p3.y))));
		max.x = zt_max(max.x, zt_max(p0.x, zt_max(p1.x, zt_max(p2.x, p3.x))));
		max.y = zt_max(max.y, zt_max(p0.y, zt_max(p1.y, zt_max(p2.y, p3.y))));
	}
	else if (collider->type == ztPlatformerColliderType_TriggerCircle) {
		ztVec2 mmin = zt_vec2(collider->points[0].x - collider->trigger_circle.radius, collider->points[0].y - collider->trigger_circle.radius);
		ztVec2 mmax = zt_vec2(collider->points[0].x + collider->trigger_circle.radius, collider->points[0].y + collider->trigger_circle.radius);

		min.x = zt_min(min.x, mmin.x);
		min.y = zt_min(min.y, mmin.y);
		max.x = zt_max(max.x, mmax.x);
		max.y = zt_max(max.y, mmax.y);
	}
	else if (collider->type == ztPlatformerColliderType_TriggerRect) {
		ztVec2 p0, p1, p2, p3;
		_zt_platformerRectGetPoints(level, collider, &p0, &p1, &p2, &p3, false);

		min.x = zt_min(min.x, zt_min(p0.x, zt_min(p1.x, zt_min(p2.x, p3.x))));
		min.y = zt_min(min.y, zt_min(p0.y, zt_min(p1.y, zt_min(p2.y, p3.y))));
		max.x = zt_max(max.x, zt_max(p0.x, zt_max(p1.x, zt_max(p2.x, p3.x))));
		max.y = zt_max(max.y, zt_max(p0.y, zt_max(p1.y, zt_max(p2.y, p3.y))));
	}
	else if (collider->type == ztPlatformerColliderType_Sprite) {
		ztVec2 ne = zt_vec2(collider->sprite.sprite.half_size.x, collider->sprite.sprite.half_size.y);
		ztVec2 nw = zt_vec2(-collider->sprite.sprite.half_size.x, collider->sprite.sprite.half_size.y);
		ztVec2 se = zt_vec2(collider->sprite.sprite.half_size.x, -collider->sprite.sprite.half_size.y);
		ztVec2 sw = zt_vec2(-collider->sprite.sprite.half_size.x, -collider->sprite.sprite.half_size.y);

		if (!zt_real32Eq(collider->sprite.rotation, 0)) {
			ztMat4 rotation_mat = ztMat4::identity.getRotateEuler(0, 0, collider->sprite.rotation);
			ne = (rotation_mat * zt_vec3(ne, 0)).xy;
			nw = (rotation_mat * zt_vec3(nw, 0)).xy;
			se = (rotation_mat * zt_vec3(se, 0)).xy;
			sw = (rotation_mat * zt_vec3(sw, 0)).xy;
		}

		ne += collider->points[0];
		nw += collider->points[0];
		se += collider->points[0];
		sw += collider->points[0];

		min.x = zt_min(min.x, zt_min(zt_min(zt_min(ne.x, sw.x), nw.x), se.x));
		min.y = zt_min(min.y, zt_min(zt_min(zt_min(ne.y, sw.y), nw.y), se.y));
		max.x = zt_max(max.x, zt_max(zt_max(zt_max(ne.x, sw.x), nw.x), se.x));
		max.y = zt_max(max.y, zt_max(zt_max(zt_max(ne.y, sw.y), nw.y), se.y));
	}
	else if (collider->type == ztPlatformerColliderType_Marker) {
		ztVec2 mmin = zt_vec2(collider->points[0].x - ZT_PLATFORMER_MARKER_RADIUS, collider->points[0].y - ZT_PLATFORMER_MARKER_RADIUS);
		ztVec2 mmax = zt_vec2(collider->points[0].x + ZT_PLATFORMER_MARKER_RADIUS, collider->points[0].y + ZT_PLATFORMER_MARKER_RADIUS);

		min.x = zt_min(min.x, mmin.x);
		min.y = zt_min(min.y, mmin.y);
		max.x = zt_max(max.x, mmax.x);
		max.y = zt_max(max.y, mmax.y);
	}
	else {
		ztVec2 p0, p1;
		zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr, false);

		min.x = zt_min(min.x, zt_min(p0.x, p1.x));
		min.y = zt_min(min.y, zt_min(p0.y, p1.y));
		max.x = zt_max(max.x, zt_max(p0.x, p1.x));
		max.y = zt_max(max.y, zt_max(p0.y, p1.y));
	}

	if (collider->movement_path >= 0) {
		ztPlatformerMovementPath *path = &level->movement_paths[collider->movement_path];

		ztVec2 offset = ztVec2::zero;
		ztVec2 offset_min = ztVec2::max;
		ztVec2 offset_max = ztVec2::min;

		zt_fiz(path->points) {
			offset += path->movements[i];

			offset_min.x = zt_min(offset_min.x, offset.x);
			offset_min.y = zt_min(offset_min.y, offset.y);
			offset_max.x = zt_max(offset_max.x, offset.x);
			offset_max.y = zt_max(offset_max.y, offset.y);
		}

		min.x = zt_min(min.x, min.x + offset_min.x);
		min.y = zt_min(min.y, min.y + offset_min.y);
		max.x = zt_max(max.x, max.x + offset_max.x);
		max.y = zt_max(max.y, max.y + offset_max.y);
	}

	if (apply_min_size) {
		static r32 diff = 8 / zt_pixelsPerUnit();

		if (zt_real32Eq(min.x, max.x)) {
			min.x -= diff;
			max.x += diff;
		}
		if (zt_real32Eq(min.y, max.y)) {
			min.y -= diff;
			max.y += diff;
		}
	}

	*pmin = min;
	*pmax = max;
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelClearColliders(ztPlatformerLevel *level)
{
	zt_memSet(level->colliders, zt_sizeof(ztPlatformerCollider) * level->colliders_size, 0);

	zt_fiz(level->colliders_size) {
		level->colliders[i].movement_path = -1;
		level->colliders[i].movement_speed = 1;
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// functions ======================================================================================================================================================================================

void zt_platformerLayerMake(ztPlatformerLayer *layer, ztGuid guid, const char *name, r32 parallax_amount)
{
	zt_returnOnNull(layer);

	layer->guid = guid;
	zt_strCpy(layer->name, zt_elementsOf(layer->name), name);
	layer->parallax_amount = parallax_amount;
}

// ================================================================================================================================================================================================

void zt_platformerLevelMake(ztPlatformerLevel *level, ztPlatformerLayer *layers, i32 layers_size, i32 max_colliders, i32 max_movement_paths, i32 max_collisions)
{
	zt_returnOnNull(level);

	level->colliders = zt_mallocStructArray(ztPlatformerCollider, max_colliders);
	level->colliders_size = max_colliders;
	level->colliders_used = 0;

	_zt_platformerLevelClearColliders(level);

	level->movement_paths      = zt_mallocStructArray(ztPlatformerMovementPath, max_movement_paths);
	level->movement_paths_size = max_movement_paths;
	level->movement_paths_used = 0;

	level->collisions      = zt_mallocStructArray(ztPlatformerLevelCollision, max_collisions);
	level->collisions_size = max_collisions;
	level->collisions_used = 0;

	level->layers = zt_mallocStructArray(ztPlatformerLayer, layers_size);
	level->layers_size = layers_size;

	zt_memCpy(level->layers, zt_sizeof(ztPlatformerLayer) * layers_size, layers, zt_sizeof(ztPlatformerLayer) * layers_size);

	level->gravity = -25.f;
	level->terminal_velocity = 12.5f;
	level->air_friction_multiplier = .75f;

	level->background_color.alpha_vals[level->background_color.alpha_entries] = 1;
	level->background_color.alpha_locs[level->background_color.alpha_entries++] = 0;
	level->background_color.alpha_vals[level->background_color.alpha_entries] = 1;
	level->background_color.alpha_locs[level->background_color.alpha_entries++] = 1;

	level->background_color.color_vals[level->background_color.color_entries] = ztColor_Black;
	level->background_color.color_locs[level->background_color.color_entries++] = 0;
	level->background_color.color_vals[level->background_color.color_entries] = ztColor_Black;
	level->background_color.color_locs[level->background_color.color_entries++] = 1;

	level->background_rotation = 0;

}

// ================================================================================================================================================================================================

void zt_platformerLevelFree(ztPlatformerLevel *level)
{
	if (level == nullptr) {
		return;
	}

	if (level->layers) {
		zt_free(level->layers);
	}

	if (level->colliders) {
		zt_free(level->colliders);
	}

	if (level->movement_paths) {
		zt_free(level->movement_paths);
	}

	if (level->collisions) {
		zt_free(level->collisions);
	}

	zt_quadTreeFree(&level->quadtree);
	zt_quadTreeFree(&level->quadtree_visual);

	zt_memSet(level, zt_sizeof(ztPlatformerLevel), 0);
}

// ================================================================================================================================================================================================

#define ZT_PLATFORMER_LEVEL_IDENTIFIER	"8fbe343991714f0fb1ab09caff68187a"
#define ZT_PLATFORMER_LEVEL_VERSION_V4     100003
#define ZT_PLATFORMER_LEVEL_VERSION_V3     100002
#define ZT_PLATFORMER_LEVEL_VERSION_V2     100001
#define ZT_PLATFORMER_LEVEL_VERSION_V1     100000
#define ZT_PLATFORMER_LEVEL_VERSION        ZT_PLATFORMER_LEVEL_VERSION_V4

// ================================================================================================================================================================================================

bool zt_platformerLevelSave(ztPlatformerLevel *level, const char *filename)
{
	zt_returnValOnNull(level, false);
	zt_returnValOnNull(filename, false);

	ztSerial serial;
	if (!zt_serialMakeWriter(&serial, filename, ZT_PLATFORMER_LEVEL_IDENTIFIER, ZT_PLATFORMER_LEVEL_VERSION)) {
		return false;
	}

	if (!zt_serialWrite(&serial, level->guid)) return false;
	if (!zt_serialWrite(&serial, level->name, zt_strLen(level->name))) return false;
	if (!zt_serialWrite(&serial, level->gravity)) return false;
	if (!zt_serialWrite(&serial, level->air_friction_multiplier)) return false;
	if (!zt_serialWrite(&serial, &level->background_color)) return false;
	if (!zt_serialWrite(&serial, level->background_rotation)) return false;
	if (!zt_serialWrite(&serial, level->terminal_velocity)) return false;

	if (!zt_serialGroupPush(&serial)) return false;
	{
		if (!zt_serialWrite(&serial, level->colliders_used)) return false;

		// colliders
		zt_fiz(level->colliders_used) {
			if (!zt_serialGroupPush(&serial)) return false;
			{
				ztPlatformerCollider *collider = &level->colliders[i];

				if (!zt_serialWrite(&serial, (i32)collider->type)) return false;
				if (!zt_serialWrite(&serial, collider->name, zt_strLen(collider->name))) return false;

				ztGuid guid = collider->movement_path < 0 ? zt_guidMake(0,0,0,0) : level->movement_paths[collider->movement_path].guid;
				if (!zt_serialWrite(&serial, guid)) return false; // V2 - changed from movement path idx to guid

				if (!zt_serialWrite(&serial, collider->movement_offset)) return false;
				if (!zt_serialWrite(&serial, collider->movement_speed)) return false;
				if (!zt_serialWrite(&serial, collider->points[0])) return false;
				if (!zt_serialWrite(&serial, collider->points[1])) return false;
				if (!zt_serialWrite(&serial, collider->flags)) return false;

				if (!zt_serialGroupPush(&serial)) return false;
				{
					switch (collider->type)
					{
						case ztPlatformerColliderType_Spring: {
							if (!zt_serialWrite(&serial, collider->spring.strength)) return false;
						} break;

						case ztPlatformerColliderType_Blower: {
							if (!zt_serialWrite(&serial, collider->blower.strength)) return false;
						} break;

						case ztPlatformerColliderType_Blades: {
							if (!zt_serialWrite(&serial, collider->blades.radius)) return false;
							if (!zt_serialWrite(&serial, collider->blades.speed)) return false;
						} break;

						case ztPlatformerColliderType_Magnet: {
							if (!zt_serialWrite(&serial, collider->magnet.strength)) return false;
						} break;

						case ztPlatformerColliderType_TriggerCircle: {
							if (!zt_serialWrite(&serial, collider->trigger_circle.radius)) return false;
						} break;

						case ztPlatformerColliderType_TriggerRect: {
							if (!zt_serialWrite(&serial, collider->trigger_rect.height)) return false;
						} break;

						case ztPlatformerColliderType_Sprite: {
							if (!zt_serialWrite(&serial, collider->sprite.hash)) return false;
							if (!zt_serialWrite(&serial, level->layers[collider->sprite.layer].guid)) return false;
							if (!zt_serialWrite(&serial, collider->sprite.rotation)) return false;
							if (!zt_serialWrite(&serial, collider->sprite.scale)) return false;
						} break;

						case ztPlatformerColliderType_Marker: {
							if (!zt_serialWrite(&serial, collider->marker.type)) return false;
							if (!zt_serialWrite(&serial, collider->marker.info, zt_strLen(collider->marker.info))) return false;
						} break;

					}
				}
				if (!zt_serialGroupPop(&serial)) return false;
			}
			if (!zt_serialGroupPop(&serial)) return false;
		}

		// Update for ZT_PLATFORMER_LEVEL_VERSION_V2.  Movement paths need to be a per game thing, not per level

#		if 0
		// movement paths
		if (!zt_serialWrite(&serial, level->movement_paths_used)) return false;

		zt_fiz(level->movement_paths_used) {
			if (!zt_serialGroupPush(&serial)) return false;
			{
				ztPlatformerMovementPath *movement_path = &level->movement_paths[i];
		
				if (!zt_serialWrite(&serial, movement_path->guid)) return false;
				if (!zt_serialWrite(&serial, (i32)movement_path->type)) return false;
				if (!zt_serialWrite(&serial, movement_path->points)) return false;
		
				zt_fjz(movement_path->points) {
					if (!zt_serialGroupPush(&serial)) return false;
					{
						if (!zt_serialWrite(&serial, movement_path->movements[j])) return false;
						if (!zt_serialWrite(&serial, movement_path->times[j])) return false;
					}
					if (!zt_serialGroupPop(&serial)) return false;
				}
			}
			if (!zt_serialGroupPop(&serial)) return false;
		}
#		endif
	}
	if (!zt_serialGroupPop(&serial)) return false;

	zt_serialClose(&serial);

	return true;
}

// ================================================================================================================================================================================================

bool zt_platformerLevelLoad(ztPlatformerLevel *level, ztSpriteManager *sprite_manager, const char *filename)
{
	zt_returnValOnNull(level, false);

	if (!zt_fileExists(filename)) {
		return false;
	}

	i32 data_size = 0;
	void *data = zt_readEntireFile(filename, &data_size);

	if (data_size <= 0) {
		return false;
	}

	bool result = zt_platformerLevelLoad(level, sprite_manager, data, data_size);
	zt_free(data);
	return result;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_assetLoadData(ztAssetManager *asset_mgr, ztAssetID asset_id, ztAssetManagerType_Enum *type_verify, int type_verify_count, void **data, i32 *data_size);

// ================================================================================================================================================================================================

bool zt_platformerLevelLoad(ztPlatformerLevel *level, ztSpriteManager *sprite_manager, ztAssetManager *asset_manager, ztAssetID asset_id)
{
	zt_returnValOnNull(level, false);
	zt_returnValOnNull(asset_manager, false);

	void *data = nullptr;
	i32 data_size = 0;

	if (!_zt_assetLoadData(asset_manager, asset_id, nullptr, 0, &data, &data_size)) {
		return false;
	}

	bool result = zt_platformerLevelLoad(level, sprite_manager, data, data_size);
	zt_free(data);
	return result;
}

// ================================================================================================================================================================================================

bool zt_platformerLevelLoad(ztPlatformerLevel *level, ztSpriteManager *sprite_manager, void *data, i32 data_size)
{
	zt_returnValOnNull(level, false);

	ztSerial serial;
	if (!zt_serialMakeReader(&serial, data, data_size, ZT_PLATFORMER_LEVEL_IDENTIFIER)) {
		return false;
	}

	_zt_platformerLevelClearColliders(level);

	if (!zt_serialRead(&serial, &level->guid)) return false;
	i32 str_len = 0;
	if (!zt_serialRead(&serial, level->name, zt_strLen(level->name), &str_len)) return false;
	if (!zt_serialRead(&serial, &level->gravity)) return false;
	if (!zt_serialRead(&serial, &level->air_friction_multiplier)) return false;

	level->background_color.alpha_entries = 0;
	level->background_color.alpha_vals[level->background_color.alpha_entries] = 1;
	level->background_color.alpha_locs[level->background_color.alpha_entries++] = 0;
	level->background_color.alpha_vals[level->background_color.alpha_entries] = 1;
	level->background_color.alpha_locs[level->background_color.alpha_entries++] = 1;

	level->background_color.color_entries = 0;
	level->background_color.color_vals[level->background_color.color_entries] = ztColor_Black;
	level->background_color.color_locs[level->background_color.color_entries++] = 0;
	level->background_color.color_vals[level->background_color.color_entries] = ztColor_Black;
	level->background_color.color_locs[level->background_color.color_entries++] = 1;

	if (!zt_serialRead(&serial, &level->background_color)) return false;
	if (!zt_serialRead(&serial, &level->background_rotation)) return false;
	if (!zt_serialRead(&serial, &level->terminal_velocity)) return false;

	if (!zt_serialGroupPush(&serial)) return false;
	{
		if (!zt_serialRead(&serial, &level->colliders_used)) return false;

		zt_assertReturnValOnFail(level->colliders_used <= level->colliders_size, false);

		// colliders
		zt_fiz(level->colliders_used) {
			if (!zt_serialGroupPush(&serial)) return false;
			{
				ztPlatformerCollider *collider = &level->colliders[i];

				i32 collider_type = 0;
				if (!zt_serialRead(&serial, &collider_type)) return false;
				zt_assertReturnValOnFail(collider_type >= 0 && collider_type < ztPlatformerColliderType_MAX, false);

				collider->type = (ztPlatformerColliderType_Enum)collider_type;
				if (!zt_serialRead(&serial, collider->name, zt_elementsOf(collider->name), &str_len)) return false;

				collider->movement_path = -1;
				
				if (serial.version == ZT_PLATFORMER_LEVEL_VERSION_V1) {
					if (!zt_serialRead(&serial, &collider->movement_path)) return false;
				}
				else {
					ztGuid guid;
					if (!zt_serialRead(&serial, &guid)) return false;

					zt_fjz(level->movement_paths_used) {
						if (level->movement_paths[j].guid == guid) {
							collider->movement_path = j;
							break;
						}
					}
				}

				if (!zt_serialRead(&serial, &collider->movement_offset)) return false;

				collider->movement_speed = 1;
				if (serial.version >= ZT_PLATFORMER_LEVEL_VERSION_V3) {
					if (!zt_serialRead(&serial, &collider->movement_speed)) return false;
				}

				if (!zt_serialRead(&serial, &collider->points[0])) return false;
				if (!zt_serialRead(&serial, &collider->points[1])) return false;
				if (!zt_serialRead(&serial, &collider->flags)) return false;

				if (!zt_serialGroupPush(&serial)) return false;
				{
					switch (collider->type)
					{
						case ztPlatformerColliderType_Spring: {
							if (!zt_serialRead(&serial, &collider->spring.strength)) return false;
						} break;

						case ztPlatformerColliderType_Blower: {
							if (!zt_serialRead(&serial, &collider->blower.strength)) return false;
						} break;

						case ztPlatformerColliderType_Blades: {
							if (!zt_serialRead(&serial, &collider->blades.radius)) return false;
							if (!zt_serialRead(&serial, &collider->blades.speed)) return false;
						} break;

						case ztPlatformerColliderType_Magnet: {
							if (!zt_serialRead(&serial, &collider->magnet.strength)) return false;
						} break;

						case ztPlatformerColliderType_TriggerCircle: {
							if (!zt_serialRead(&serial, &collider->trigger_circle.radius)) return false;
						} break;

						case ztPlatformerColliderType_TriggerRect: {
							if (!zt_serialRead(&serial, &collider->trigger_rect.height)) return false;
						} break;

						case ztPlatformerColliderType_Sprite: {
							if (!zt_serialRead(&serial, &collider->sprite.hash)) return false;

							if (serial.version >= ZT_PLATFORMER_LEVEL_VERSION_V4) {
								collider->sprite.layer = 0;

								ztGuid guid;
								if (!zt_serialRead(&serial, &guid)) return false;

								zt_fxz(level->layers_size) {
									if (level->layers[x].guid == guid) {
										collider->sprite.layer = x;
										break;
									}
								}
							}
							else {
								if (!zt_serialRead(&serial, &collider->sprite.layer)) return false;
							}

							if (!zt_serialRead(&serial, &collider->sprite.rotation)) return false;

							collider->sprite.scale = ztVec2::one;
							if (!zt_serialRead(&serial, &collider->sprite.scale)) return false;

							ztSprite *sprite = zt_spriteManagerGetSprite(sprite_manager, collider->sprite.hash);
							if (sprite) {
								collider->sprite.sprite = *sprite;
							}

							collider->sprite.anim_controller = nullptr;
						} break;

						case ztPlatformerColliderType_Marker: {
							if (!zt_serialRead(&serial, &collider->marker.type)) return false;
							if (!zt_serialRead(&serial, collider->marker.info, zt_elementsOf(collider->marker.info), &str_len)) return false;
						} break;
					}
				}
				if (!zt_serialGroupPop(&serial)) return false;
			}
			if (!zt_serialGroupPop(&serial)) return false;
		}

		// movement paths
		if (serial.version == ZT_PLATFORMER_LEVEL_VERSION_V1) {
			i32 movement_paths_used = 0;
			if (!zt_serialRead(&serial, &movement_paths_used)) return false;
			zt_assertReturnValOnFail(movement_paths_used >= 0 && movement_paths_used < level->movement_paths_size, false);

			zt_fiz(movement_paths_used) {
				if (!zt_serialGroupPush(&serial)) return false;
				{
					// Update for ZT_PLATFORMER_LEVEL_VERSION_V2.  Movement paths need to be a per game thing, not per level
#					if 0
					ztPlatformerMovementPath *movement_path = &level->movement_paths[i];

					if (!zt_serialRead(&serial, &movement_path->guid)) return false;
					i32 movement_path_type = 0;
					if (!zt_serialRead(&serial, &movement_path_type)) return false;
					zt_assertReturnValOnFail(movement_path_type >= 0 && movement_path_type < ztPlatformerMovementPathType_MAX, false);
					movement_path->type = (ztPlatformerMovementPathType_Enum)movement_path_type;
					if (!zt_serialRead(&serial, &movement_path->points)) return false;

					zt_fjz(movement_path->points) {
						if (!zt_serialGroupPush(&serial)) return false;
						{
							if (!zt_serialRead(&serial, &movement_path->movements[j])) return false;
							if (!zt_serialRead(&serial, &movement_path->times[j])) return false;
						}
						if (!zt_serialGroupPop(&serial)) return false;
					}
#					endif
				}
				if (!zt_serialGroupPop(&serial)) return false;
			}
		}
	}
	if (!zt_serialGroupPop(&serial)) return false;

	zt_serialClose(&serial);

	zt_platformerRecalcQuadTree(level);

	return true;
}

// ================================================================================================================================================================================================

i32 zt_platformerAddMovementPath(ztPlatformerLevel *level, ztPlatformerMovementPath **movement_path, ztGuid guid)
{
	zt_returnValOnNull(level, -1);
	zt_returnValOnNull(movement_path, -1);

	if (level->movement_paths_used >= level->movement_paths_size) {
		if (movement_path) *movement_path = nullptr;
		return -1;
	}

	i32 idx = level->movement_paths_used++;
	if(movement_path) *movement_path = &level->movement_paths[idx];

	zt_memSet(&level->movement_paths[idx], zt_sizeof(ztPlatformerMovementPath), 0);

	level->movement_paths[idx].guid = guid;
	//level->movement_paths[idx].update_function = ZT_FUNCTION_POINTER_TO_VAR_NULL;

	return (idx);
}

// ================================================================================================================================================================================================

ztInternal i32 zt_platformerAllocCollider(ztPlatformerLevel *level)
{
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = level->colliders_used++;
	zt_memSet(&level->colliders[idx], zt_sizeof(ztPlatformerCollider), 0);
	level->colliders[idx].movement_path = -1;
	level->colliders[idx].movement_speed = 1;
	return idx;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendCollider(ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Surface;
	level->colliders[idx].points[0] = p1;
	level->colliders[idx].points[1] = p2;

	return idx;
}

// ================================================================================================================================================================================================

i32 zt_platformerAppendColliderRect(ztPlatformerLevel *level, ztVec2 center, ztVec2 size)
{
	i32 result =
	zt_platformerAppendCollider(level, zt_vec2(center.x + size.x / -2, center.y + size.y / 2), zt_vec2(center.x + size.x / 2, center.y + size.y / 2));
	zt_platformerAppendCollider(level, zt_vec2(center.x + size.x /  2, center.y + size.y / 2), zt_vec2(center.x + size.x / 2, center.y - size.y / 2));
	zt_platformerAppendCollider(level, zt_vec2(center.x + size.x / 2, center.y - size.y / 2), zt_vec2(center.x + size.x / -2, center.y - size.y / 2));
	zt_platformerAppendCollider(level, zt_vec2(center.x - size.x / 2, center.y - size.y / 2), zt_vec2(center.x - size.x / 2, center.y + size.y / 2));
	return result;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendColliderSpring(ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2, r32 strength)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Spring;
	level->colliders[idx].points[0] = p1;
	level->colliders[idx].points[1] = p2;
	level->colliders[idx].spring.strength = strength;

	return idx;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendColliderBlower(ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2, r32 strength)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Blower;
	level->colliders[idx].points[0] = p1;
	level->colliders[idx].points[1] = p2;
	level->colliders[idx].blower.strength = strength;

	return idx;
}

// ================================================================================================================================================================================================

i32 zt_platformerAppendColliderBlades(ztPlatformerLevel *level, ztVec2 p, r32 radius, r32 speed)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Blades;
	level->colliders[idx].points[0] = level->colliders[idx].points[1] = p;
	level->colliders[idx].blades.radius = radius;
	level->colliders[idx].blades.speed = speed;

	return idx;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendColliderMagnet(ztPlatformerLevel *level, ztVec2 p, r32 strength)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Magnet;
	level->colliders[idx].points[0] = level->colliders[idx].points[1] = p;
	level->colliders[idx].magnet.strength = strength;

	return idx;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendColliderTriggerLine(ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_TriggerLine;
	level->colliders[idx].points[0] = p1;
	level->colliders[idx].points[1] = p2;

	return idx;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendColliderTriggerCircle(ztPlatformerLevel *level, ztVec2 p, r32 radius)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_TriggerCircle;
	level->colliders[idx].points[0] = level->colliders[idx].points[1] = p;
	level->colliders[idx].trigger_circle.radius = radius;

	return idx;
}

// ================================================================================================================================================================================================

i32  zt_platformerAppendColliderTriggerRect(ztPlatformerLevel *level, ztVec2 p1, ztVec2 p2, r32 height)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_TriggerRect;
	level->colliders[idx].points[0] = p1;
	level->colliders[idx].points[1] = p2;
	level->colliders[idx].trigger_rect.height = height;

	return idx;
}

// ================================================================================================================================================================================================

i32 zt_platformerAppendMarker(ztPlatformerLevel *level, ztVec2 p, i32 type, char *info)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Marker;
	level->colliders[idx].points[0] = level->colliders[idx].points[1] = p;
	level->colliders[idx].marker.type = type;
	zt_strCpy(level->colliders[idx].marker.info, zt_elementsOf(level->colliders[idx].marker.info), info);

	return idx;
}

// ================================================================================================================================================================================================

i32 zt_platformerAppendSprite(ztPlatformerLevel *level, ztVec2 p, u32 hash, r32 rotation, i32 layer, ztSprite *sprite)
{
	zt_returnValOnNull(level, -1);
	zt_assertReturnValOnFail(level->colliders_used < level->colliders_size, -1);

	i32 idx = zt_platformerAllocCollider(level);
	level->colliders[idx].type = ztPlatformerColliderType_Sprite;
	level->colliders[idx].points[0] = level->colliders[idx].points[1] = p;
	level->colliders[idx].sprite.hash = hash;
	level->colliders[idx].sprite.rotation = rotation;
	level->colliders[idx].sprite.layer = layer;
	level->colliders[idx].sprite.scale = ztVec2::one;

	if (sprite) {
		level->colliders[idx].sprite.sprite = *sprite;
	}

	level->colliders[idx].sprite.anim_controller = nullptr;

	return idx;
}

// ================================================================================================================================================================================================

void zt_platformerSetColliderName(ztPlatformerLevel *level, i32 collider_idx, const char *name)
{
	zt_returnOnNull(level);
	zt_assertReturnOnFail(collider_idx >= 0 && collider_idx < level->colliders_used);

	zt_strCpy(level->colliders[collider_idx].name, zt_elementsOf(level->colliders[collider_idx].name), name);
}

// ================================================================================================================================================================================================

void zt_platformerSetMovementPath(ztPlatformerLevel *level, i32 collider_idx, i32 movement_path_idx, r32 time_offset)
{
	zt_returnOnNull(level);
	zt_assertReturnOnFail(collider_idx >= 0 && collider_idx < level->colliders_used);

	level->colliders[collider_idx].movement_path = movement_path_idx;
	level->colliders[collider_idx].movement_offset = time_offset;
	level->colliders[collider_idx].movement_speed = 1;
}

// ================================================================================================================================================================================================

i32 zt_platformerGetColliderIndex(ztPlatformerLevel *level, ztPlatformerCollider *collider)
{
	zt_returnValOnNull(level, -1);
	zt_returnValOnNull(collider, -1);

	zt_fiz(level->colliders_used) {
		if (collider == &level->colliders[i]) {
			return i;
		}
	}

	return -1;
}

// ================================================================================================================================================================================================

ztVec2 zt_platformerGetColliderVelocity(ztPlatformerCollider *collider)
{
	zt_returnValOnNull(collider, ztVec2::zero);

	if (collider->offset_this != ztVec2::zero) {
		return collider->offset_this - collider->offset_last;
	}

	return ztVec2::zero;
}

// ================================================================================================================================================================================================

void zt_platformerGetColliderPositions(ztPlatformerLevel *level, ztPlatformerCollider *collider, ztVec2 *p0, ztVec2 *p1, ztVec2 *n, bool apply_offset)
{
	switch (collider->type)
	{
		case ztPlatformerColliderType_Surface:
		case ztPlatformerColliderType_Spring:
		case ztPlatformerColliderType_Blower:
		case ztPlatformerColliderType_TriggerLine:
		case ztPlatformerColliderType_TriggerRect:
			*p0 = collider->points[0];
			*p1 = collider->points[1];
			break;

		case ztPlatformerColliderType_Blades:
		case ztPlatformerColliderType_Magnet:
		case ztPlatformerColliderType_TriggerCircle:
		case ztPlatformerColliderType_Sprite:
		case ztPlatformerColliderType_Marker:
			*p0 = *p1 = collider->points[0];
			break;

		default:
			zt_assert(false);
	}

	if (collider->movement_path >= 0 && apply_offset) {
		*p0 += collider->offset_this;
		*p1 += collider->offset_this;
	}

	if (n) {
		ztVec2 d = zt_vec2(p1->x - p0->x, p1->y - p0->y);
		*n = zt_vec2(-d.y, d.x).getNormal();
	}
}

// ================================================================================================================================================================================================

i32 zt_platformerGetCollidersThatIntersectAABB(ztPlatformerLevel *level, ztVec2 aabb_ctr, ztVec2 aabb_size, i32 *colliders, i32 colliders_size)
{
	zt_returnValOnNull(level, -1);

	ztQuadTree::Node *nodes[64];
	i32 nodes_count = zt_quadTreeFindNodesThatIntersect(&level->quadtree, nodes, zt_elementsOf(nodes), aabb_ctr, aabb_size);

	i32 colliders_count = 0;

	zt_fiz(nodes_count) {
		zt_fjz(nodes[i]->objects_count) {
			ztPlatformerCollider *collider = &level->colliders[nodes[i]->objects[j]];

			if (collider->type == ztPlatformerColliderType_Sprite || collider->type == ztPlatformerColliderType_Marker || zt_bitIsSet(collider->flags, ztPlatformerColliderFlags_Disabled)) {
				continue;
			}

			bool colliding = false;

			ztVec2 p0, p1;
			zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr);

			if ((collider->type == ztPlatformerColliderType_Surface || collider->type == ztPlatformerColliderType_Spring)) {
				if (zt_collisionLineSegmentInAABB(p0, p1, aabb_ctr, aabb_size, nullptr, nullptr)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_Blower) {
				ztVec2 p2, p3;
				_zt_platformerBlowerGetPoints(level, collider, &p0, &p1, &p2, &p3);

				if (zt_collisionTriangleInAABB(p0, p1, p2, aabb_ctr, aabb_size) || zt_collisionTriangleInAABB(p0, p2, p3, aabb_ctr, aabb_size)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_Magnet) {
				if (zt_collisionCircleInAABB(p0, collider->magnet.strength, aabb_ctr, aabb_size)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_Blades) {
				if (zt_collisionCircleInAABB(p0, collider->blades.radius, aabb_ctr, aabb_size)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_TriggerLine) {
				if (zt_collisionLineSegmentInAABB(p0, p1, aabb_ctr, aabb_size)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_TriggerCircle) {
				if (zt_collisionCircleInAABB(p0, collider->trigger_circle.radius, aabb_ctr, aabb_size)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_TriggerRect) {
				ztVec2 p2, p3;
				_zt_platformerRectGetPoints(level, collider, &p0, &p1, &p2, &p3);

				if (zt_collisionTriangleInAABB(p0, p1, p2, aabb_ctr, aabb_size) || zt_collisionTriangleInAABB(p0, p2, p3, aabb_ctr, aabb_size)) {
					colliding = true;
				}
			}

			if (colliding) {
				if (colliders_count < colliders_size) {
					colliders[colliders_count] = nodes[i]->objects[j];
				}
				colliders_count += 1;
			}
		}
	}

	return colliders_count;
}

// ================================================================================================================================================================================================

i32 zt_platformerGetCollidersThatIntersectAABB(ztPlatformerLevel *level, ztVec2 aabb_ctr, ztVec2 aabb_size, ztPlatformerCollider **colliders, i32 colliders_size)
{
	zt_returnValOnNull(level, -1);

	i32 *colliders_i32 = zt_mallocStructArrayArena(i32, colliders_size, zt_memGetTempArena());
	i32 result = zt_platformerGetCollidersThatIntersectAABB(level, aabb_ctr, aabb_size, colliders_i32, colliders_size);

	zt_fiz(result) {
		colliders[i] = &level->colliders[colliders_i32[i]];
	}

	zt_freeArena(colliders_i32, zt_memGetTempArena());

	return result;
}

// ================================================================================================================================================================================================

i32 zt_platformerGetCollidersThatIntersectLine(ztPlatformerLevel *level, ztVec2 line_beg, ztVec2 line_end, i32 *colliders, i32 colliders_size)
{
	zt_returnValOnNull(level, -1);

	ztQuadTree::Node *nodes[64];

	i32 nodes_count = zt_quadTreeFindNodesThatIntersectLine(&level->quadtree, nodes, zt_elementsOf(nodes), line_beg, line_end);

	i32 colliders_count = 0;

	zt_fiz(nodes_count) {
		zt_fjz(nodes[i]->objects_count) {
			ztPlatformerCollider *collider = &level->colliders[nodes[i]->objects[j]];

			if (collider->type == ztPlatformerColliderType_Sprite || collider->type == ztPlatformerColliderType_Marker || zt_bitIsSet(collider->flags, ztPlatformerColliderFlags_Disabled)) {
				continue;
			}

			bool colliding = false;

			ztVec2 p0, p1;
			zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr);

			if ((collider->type == ztPlatformerColliderType_Surface || collider->type == ztPlatformerColliderType_Spring)) {
				if (zt_collisionLineWithLine(line_beg, line_end, p0, p1)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_Blower) {
				ztVec2 p2, p3;
				_zt_platformerBlowerGetPoints(level, collider, &p0, &p1, &p2, &p3);

				if (zt_collisionLineInTriangle(line_beg, line_end, p0, p1, p2) || zt_collisionLineInTriangle(line_beg, line_end, p0, p2, p3)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_Magnet) {
				if (zt_collisionLineInCircle(line_beg, line_end, p0, collider->magnet.strength)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_Blades) {
				if (zt_collisionLineInCircle(line_beg, line_end, p0, collider->blades.radius)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_TriggerLine) {
				if (zt_collisionLineWithLine(line_beg, line_end, p0, p1)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_TriggerCircle) {
				if (zt_collisionLineInCircle(line_beg, line_end, p0, collider->trigger_circle.radius)) {
					colliding = true;
				}
			}
			else if (collider->type == ztPlatformerColliderType_TriggerRect) {
				ztVec2 p2, p3;
				_zt_platformerRectGetPoints(level, collider, &p0, &p1, &p2, &p3);

				if (zt_collisionLineInTriangle(line_beg, line_end, p0, p1, p2) || zt_collisionLineInTriangle(line_beg, line_end, p0, p2, p3)) {
					colliding = true;
				}
			}

			if (colliding) {
				if (colliders_count < colliders_size) {
					colliders[colliders_count] = nodes[i]->objects[j];
				}
				colliders_count += 1;
			}
		}
	}

	return colliders_count;
}

// ================================================================================================================================================================================================

i32 zt_platformerGetCollidersThatIntersectLine(ztPlatformerLevel *level, ztVec2 line_beg, ztVec2 line_end, ztPlatformerCollider **colliders, i32 colliders_size)
{
	zt_returnValOnNull(level, -1);

	i32 *colliders_i32 = zt_mallocStructArrayArena(i32, colliders_size, zt_memGetTempArena());
	i32 result = zt_platformerGetCollidersThatIntersectLine(level, line_beg, line_end, colliders_i32, colliders_size);

	zt_fiz(result) {
		colliders[i] = &level->colliders[colliders_i32[i]];
	}

	zt_freeArena(colliders_i32, zt_memGetTempArena());

	return result;
}

// ================================================================================================================================================================================================

ztPlatformerCollider *zt_platformerGetNearestCollider(ztPlatformerLevel *level, ztVec2 point, ztPlatformerColliderType_Enum valid_types, r32 within_distance, i32 *collider_idx)
{
	return zt_platformerGetNearestCollider(level, point, &valid_types, 1, within_distance, collider_idx);
}

// ================================================================================================================================================================================================

ztPlatformerCollider *zt_platformerGetNearestCollider(ztPlatformerLevel *level, ztVec2 point, ztPlatformerColliderType_Enum *valid_types, i32 valid_types_size, r32 within_distance, i32 *collider_idx)
{
	zt_returnValOnNull(level, nullptr);

	ztVec2 aabb_ctr = point;
	ztVec2 aabb_size = zt_vec2(within_distance, within_distance);

	ztQuadTree::Node *nodes[64];
	i32 nodes_count = zt_quadTreeFindNodesThatIntersect(&level->quadtree, nodes, zt_elementsOf(nodes), aabb_ctr, aabb_size);

	i32 colliders_count = 0;

	r32 nearest_dist = ztReal32Max;
	i32 nearest_idx = -1;

	zt_fiz(nodes_count) {
		zt_fjz(nodes[i]->objects_count) {
			ztPlatformerCollider *collider = &level->colliders[nodes[i]->objects[j]];

			bool should_continue = valid_types_size > 0;
			zt_fxz(valid_types_size) {
				if (collider->type == valid_types[x]) {
					should_continue = true;
					break;
				}
			}

			if (zt_bitIsSet(collider->flags, ztPlatformerColliderFlags_Disabled)) {
				should_continue = false;
			}

			if (should_continue) {
				ztVec2 p0, p1;
				zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr);

				ztVec2 nearest = zt_closestPointLineSegmentPoint(p0, p1, point);

				r32 dist = point.distanceForCompare(nearest);
				if (dist < nearest_dist && dist <= within_distance) {
					nearest_dist = dist;
					nearest_idx = nodes[i]->objects[j];
				}
			}
		}
	}

	if (nearest_idx != -1) {
		if (collider_idx) *collider_idx = nearest_idx;
		return &level->colliders[nearest_idx];
	}

	return nullptr;
}

// ================================================================================================================================================================================================

void zt_platformerRecalcQuadTree(ztPlatformerLevel *level)
{
	zt_returnOnNull(level);

	struct local
	{
		static ZT_FUNC_QUADTREE_ITEM_CONTAINED(testContainmentColliders)
		{
			ztPlatformerLevel *level = (ztPlatformerLevel*)user_data;

			if (object_idx < 0 || object_idx >= level->colliders_used) {
				return ztQuadTreeItemContainedResult_InvalidIndex;
			}

			if (level->colliders[object_idx].type == ztPlatformerColliderType_Sprite) {
				return ztQuadTreeItemContainedResult_Outside;
			}

			ztVec2 min, max;
			_zt_platformerGetExtents(level, &level->colliders[object_idx], &min, &max, false);

			ztVec2 col_pos = (min + max) * .5f;
			ztVec2 col_ext = max - min;

			if (zt_collisionAABBInAABB(zt_vec3(center, 0), zt_vec3(size, 0), zt_vec3(col_pos, 0), zt_vec3(col_ext, 0))) {
				return ztQuadTreeItemContainedResult_Inside;
			}

			return ztQuadTreeItemContainedResult_Outside;
		}

		static ZT_FUNC_QUADTREE_ITEM_CONTAINED(testContainmentVisual)
		{
			ztPlatformerLevel *level = (ztPlatformerLevel*)user_data;

			if (object_idx < 0 || object_idx >= level->colliders_used) {
				return ztQuadTreeItemContainedResult_InvalidIndex;
			}

			if (level->colliders[object_idx].type != ztPlatformerColliderType_Sprite) {
				return ztQuadTreeItemContainedResult_Outside;
			}

			ztVec2 min, max;
			_zt_platformerGetExtents(level, &level->colliders[object_idx], &min, &max, false);

			ztVec2 col_pos = (min + max) * .5f;
			ztVec2 col_ext = max - min;

			if (zt_collisionAABBInAABB(zt_vec3(center, 0), zt_vec3(size, 0), zt_vec3(col_pos, 0), zt_vec3(col_ext, 0))) {
				return ztQuadTreeItemContainedResult_Inside;
			}

			return ztQuadTreeItemContainedResult_Outside;
		}
	};

	zt_quadTreeFree(&level->quadtree);
	zt_quadTreeFree(&level->quadtree_visual);

	ztVec2 min = ztVec2::max;
	ztVec2 max = ztVec2::min;
	ztVec2 vis_min = ztVec2::max;
	ztVec2 vis_max = ztVec2::min;

	zt_fiz(level->colliders_used) {
		ztVec2 col_min, col_max;
		_zt_platformerGetExtents(level, &level->colliders[i], &col_min, &col_max, false);

		ztVec2 *pmin = level->colliders[i].type == ztPlatformerColliderType_Sprite ? &vis_min : &min;
		ztVec2 *pmax = level->colliders[i].type == ztPlatformerColliderType_Sprite ? &vis_max : &max;

		pmin->x = zt_min(pmin->x, zt_min(col_min.x, col_max.x));
		pmin->y = zt_min(pmin->y, zt_min(col_min.y, col_max.y));
		pmax->x = zt_max(pmax->x, zt_max(col_min.x, col_max.x));
		pmax->y = zt_max(pmax->y, zt_max(col_min.y, col_max.y));
	}

	ztVec2 center = (min + max) * .5f;
	ztVec2 size = max - min;
	zt_quadTreeMake(&level->quadtree, 8, 12, center, size, local::testContainmentColliders, level);

	center = (vis_min + vis_max) * .5f;
	size = vis_max - vis_min;
	zt_quadTreeMake(&level->quadtree_visual, 32, 12, center, size, local::testContainmentVisual, level);
}

// ================================================================================================================================================================================================

void zt_platformerResetMovementPaths(ztPlatformerLevel *level)
{
	zt_returnOnNull(level);

	zt_fiz(level->movement_paths_used) {
		level->movement_paths[i].current_time = 0;
	}
}

// ================================================================================================================================================================================================

ztInternal i32 _zt_platformerDrawBackground(ztPlatformerLevel *level, ztCamera *camera, ztDrawList *draw_list, ztVec3 *pos, ztVec2 *uvs, i32 triangles_size)
{
	zt_returnValOnNull(level, 0);
	zt_returnValOnNull(camera, 0);

	ztColor colors[32];
	r32  locations[32];

	i32 colors_count = zt_colorGradientGetColors(&level->background_color, colors, locations, zt_elementsOf(colors));

	ztVec2 cam_pos = camera->position.xy;
	ztVec2 cam_min, cam_max;
	zt_cameraOrthoGetExtents(camera, &cam_min, &cam_max);
	ztVec2 cam_size = cam_max - cam_min;

	cam_min += cam_pos;
	cam_max += cam_pos;

	ztQuat rot = ztQuat::identity;
	
	if (!zt_real32Eq(level->background_rotation, 0)) {
		rot = ztQuat::makeFromEuler(0, 0, level->background_rotation);

		ztVec2 size_add = cam_size * .97f;

		cam_min -= size_add * .5f;
		cam_max += size_add * .5f;
		cam_size += size_add;
	}

	if (draw_list) {
		zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
		zt_drawListPushTexture(draw_list, ztTextureDefaultWhite);
		zt_rendererSetFaceCulling(ztRendererFaceCulling_CullNone);
	}

	r32 prev_loc = locations[0];

	i32 triangle_idx = 0;

	for (int i = 1; i < colors_count; ++i) {
		ztVec3 p1 = zt_vec3(cam_min.x, cam_max.y - cam_size.y * prev_loc, 0);
		ztVec3 p2 = zt_vec3(cam_min.x, cam_max.y - cam_size.y * locations[i], 0);
		ztVec3 p3 = zt_vec3(cam_max.x, cam_max.y - cam_size.y * locations[i], 0);
		ztVec3 p4 = zt_vec3(cam_max.x, cam_max.y - cam_size.y * prev_loc, 0);

		prev_loc = locations[i];

		if (!zt_real32Eq(level->background_rotation, 0)) {
			rot.rotatePosition(&p1);
			rot.rotatePosition(&p2);
			rot.rotatePosition(&p3);
			rot.rotatePosition(&p4);
		}

		if (draw_list) {
			zt_drawListAddFilledQuad(draw_list, p1, p2, p3, p4, zt_vec2(0, 0), zt_vec2(0, 1), zt_vec2(1, 1), zt_vec2(1, 0), ztVec3::zero, ztVec3::zero, ztVec3::zero, ztVec3::zero, colors[i - 1], colors[i], colors[i], colors[i - 1]);
		}
		else {
			zt_assert(triangle_idx < triangles_size - 6);
			pos[triangle_idx  ] = p1;
			uvs[triangle_idx++] = zt_vec2(0, 0);
			pos[triangle_idx  ] = p2;
			uvs[triangle_idx++] = zt_vec2(0, 1);
			pos[triangle_idx  ] = p3;
			uvs[triangle_idx++] = zt_vec2(1, 1);

			pos[triangle_idx  ] = p1;
			uvs[triangle_idx++] = zt_vec2(0, 0);
			pos[triangle_idx  ] = p3;
			uvs[triangle_idx++] = zt_vec2(1, 1);
			pos[triangle_idx  ] = p4;
			uvs[triangle_idx++] = zt_vec2(1, 0);
		}
	}

	if (draw_list) {
		zt_drawListPopTexture(draw_list);
		zt_drawListPopShader(draw_list);
	}

	return triangle_idx;
}

// ================================================================================================================================================================================================

void zt_platformerDrawBackground(ztPlatformerLevel *level, ztDrawList *draw_list, ztCamera *camera)
{
	_zt_platformerDrawBackground(level, camera, draw_list, nullptr, nullptr, 0);
}

// ================================================================================================================================================================================================

i32 zt_platformerGetBackgroundTriangles(ztPlatformerLevel *level, ztCamera *camera, ztVec3 *pos, ztVec2 *uvs, i32 triangles_size)
{
	return _zt_platformerDrawBackground(level, camera, nullptr, pos, uvs, triangles_size);
}

// ================================================================================================================================================================================================

ztInternal i32 _zt_platformerDraw(ztPlatformerLevel *level, ztCamera *camera, i32 layer, ztPlatformerPhysicsObject *objects, i32 objects_size, bool apply_parallax, ztDrawList *draw_list, ztVec3 *pos, ztVec2 *uvs, i32 triangle_size)
{
	zt_returnValOnNull(level, 0);
	zt_returnValOnNull(camera, 0);

	if (draw_list) {
		zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	}

	ztVec2 diff_from_cam = ztVec2::zero;
	if (layer >= 0 && layer < level->layers_size) {
		diff_from_cam = ztVec2::zero - camera->position.xy;;
		diff_from_cam *= (1 - level->layers[layer].parallax_amount);
	}

	i32 triangle_idx = 0;
	ztVec3 sprite_pos[6];
	ztVec2 sprite_uvs[6];

	ztVec2 cam_aabb_center = camera->position.xy;
	ztVec2 cam_aabb_extent = zt_cameraOrthoGetViewportSize(camera);

	zt_fiz(level->colliders_used) {
		if (level->colliders[i].type == ztPlatformerColliderType_Sprite && (level->colliders[i].sprite.layer == layer || layer < 0) && !zt_bitIsSet(level->colliders[i].flags, ztPlatformerColliderFlags_Disabled)) {
			ztVec2 p0, p1;
			zt_platformerGetColliderPositions(level, &level->colliders[i], &p0, &p1, nullptr);

			if (!zt_collisionAABBInAABB(cam_aabb_center, cam_aabb_extent, p0, level->colliders[i].sprite.sprite.half_size * 2)) {
				continue;
			}

			ztVec3 scale = zt_vec3(level->colliders[i].sprite.scale, 1);
			ztVec3 rot = zt_vec3(0, 0, level->colliders[i].sprite.rotation);

			if (layer >= 0 && apply_parallax) {
				p0 -= diff_from_cam;
				p1 -= diff_from_cam;
			}

			ztSprite *sprite = level->colliders[i].sprite.anim_controller ? zt_spriteAnimControllerActiveSprite(level->colliders[i].sprite.anim_controller) : &level->colliders[i].sprite.sprite;

			if (draw_list) {
				if (!zt_real32Eq(level->colliders[i].sprite.rotation, 0)) {
					zt_drawListAddSpriteFast(draw_list, sprite, zt_vec3(p0, 0), rot, scale);
				}
				else {
					zt_drawListAddSpriteFast(draw_list, sprite, zt_vec3(p0, 0), rot, scale);
				}
			}
			else {
				zt_assertReturnValOnFail(triangle_idx < triangle_size + 6, triangle_idx);

				zt_spriteGetTrianglesFast(sprite, zt_vec3(p0, 0), rot, scale, sprite_pos, sprite_uvs);

				pos[triangle_idx  ] = sprite_pos[0];
				uvs[triangle_idx++] = sprite_uvs[0];
				pos[triangle_idx  ] = sprite_pos[1];
				uvs[triangle_idx++] = sprite_uvs[1];
				pos[triangle_idx  ] = sprite_pos[2];
				uvs[triangle_idx++] = sprite_uvs[2];

				pos[triangle_idx  ] = sprite_pos[3];
				uvs[triangle_idx++] = sprite_uvs[3];
				pos[triangle_idx  ] = sprite_pos[4];
				uvs[triangle_idx++] = sprite_uvs[4];
				pos[triangle_idx  ] = sprite_pos[5];
				uvs[triangle_idx++] = sprite_uvs[5];
			}
		}
	}

	if (draw_list) {
		zt_drawListPopShader(draw_list);
	}

	return triangle_idx;
}

// ================================================================================================================================================================================================

void zt_platformerDraw(ztPlatformerLevel *level, ztDrawList *draw_list, ztCamera *camera, i32 layer, ztPlatformerPhysicsObject *objects, i32 objects_size, bool apply_parallax)
{
	_zt_platformerDraw(level, camera, layer, objects, objects_size, apply_parallax, draw_list, nullptr, nullptr, 0);
}

// ================================================================================================================================================================================================

i32 zt_platformerGetTriangles(ztPlatformerLevel *level, ztCamera *camera, i32 layer, ztPlatformerPhysicsObject *objects, i32 objects_size, bool apply_parallax, ztVec3 *pos, ztVec2 *uvs, i32 triangles_size)
{
	return _zt_platformerDraw(level, camera, layer, objects, objects_size, apply_parallax, nullptr, pos, uvs, triangles_size);
}

// ================================================================================================================================================================================================

ztVec2 zt_platformerGetPositionOnLayer(ztPlatformerLevel *level, i32 layer, ztVec2 position, ztCamera *camera)
{
	if (layer >= 0 && layer < level->layers_size) {
		ztVec2 diff_from_cam = ztVec2::zero;
		diff_from_cam = ztVec2::zero - camera->position.xy;;
		diff_from_cam *= (1 - level->layers[layer].parallax_amount);

		position -= diff_from_cam;
	}

	return position;
}

// ================================================================================================================================================================================================

void zt_platformerDrawDebugView(ztPlatformerLevel *level, ztDrawList *draw_list, ztPlatformerLevelEditor *level_editor, i32 layer, ztVec2 mpos, i32 flags)
{
	zt_returnOnNull(level);
	zt_returnOnNull(draw_list);

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	if (zt_bitIsSet(flags, ztPlatformerDrawDebugFlags_DrawGrid)) {
		ztVec2i min = zt_vec2i(level->quadtree.root_node->center - (level->quadtree.root_node->size * .5f));
		ztVec2i max = zt_vec2i(level->quadtree.root_node->center + (level->quadtree.root_node->size * .5f));

		int cols = max.x - min.x;
		int rows = max.y - min.y;

		zt_drawListPushColor(draw_list, ztColor_LightGray * zt_vec4(1, 1, 1, .5f));
		zt_fyz(rows + 1) {
			zt_drawListAddLine(draw_list, zt_vec2(zt_vec2i(min.x, min.y + y)), zt_vec2(zt_vec2i(max.x, min.y + y)));
		}
		zt_fxz(cols + 1) {
			zt_drawListAddLine(draw_list, zt_vec2(zt_vec2i(min.x + x, min.y)), zt_vec2(zt_vec2i(min.x + x, max.y)));
		}
		zt_drawListPopColor(draw_list);
	}

	ztQuadTree::Node *mnode = nullptr;

	if (zt_bitIsSet(flags, ztPlatformerDrawDebugFlags_DrawQuadTree)) {
		struct quadtree
		{
			static void renderNode(ztDrawList *draw_list, ztQuadTree::Node *node)
			{
				zt_drawListAddEmptyRect(draw_list, zt_vec3(node->center, 0), node->size);

				zt_fize(node->nodes) {
					if (node->nodes[i]) {
						renderNode(draw_list, node->nodes[i]);
					}
				}
			}
		};

		zt_drawListPushColor(draw_list, ztColor_LightGray * zt_vec4(1,1,1,.5f));
		quadtree::renderNode(draw_list, level->quadtree.root_node);
		zt_drawListPopColor(draw_list);

		ztQuadTree::Node *mouse_nodes[1];
		if (zt_quadTreeFindNodesThatIntersect(&level->quadtree, mouse_nodes, zt_elementsOf(mouse_nodes), mpos, zt_vec2(1 / zt_pixelsPerUnit(), 1 / zt_pixelsPerUnit())) > 0) {
			zt_drawListPushColor(draw_list, ztColor_Magenta);
			quadtree::renderNode(draw_list, mouse_nodes[0]);
			zt_drawListPopColor(draw_list);
			mnode = mouse_nodes[0];
		}
	}


	if (zt_bitIsSet(flags, ztPlatformerDrawDebugFlags_DrawColliders)) {
		bool non_sprite_layer = layer < 0 || layer == level->layers_size - 1;
		zt_fiz(level->colliders_used) {
			ztVec2 p0, p1, n;
			zt_platformerGetColliderPositions(level, &level->colliders[i], &p0, &p1, &n);

			if ((level->colliders[i].type == ztPlatformerColliderType_Surface || level->colliders[i].type == ztPlatformerColliderType_Spring || level->colliders[i].type == ztPlatformerColliderType_Blower) && non_sprite_layer) {
				ztColor colors[] = { ztColor_Red, ztColor_Blue, ztColor_Cyan, ztColor_Purple };
				ztColor color = colors[(i32)level->colliders[i].type];

				if (zt_bitIsSet(level->colliders[i].flags, ztPlatformerColliderFlags_Disabled)) {
					color *= zt_vec4(1, 1, 1, .5f);
				}

				if (mnode) {
					bool found = false;
					zt_fxz(mnode->objects_count) {
						if (mnode->objects[x] == i) {
							found = true;
							break;
						}
					}

					if (!found) {
						color *= zt_vec4(1, 1, 1, .5f);
					}
				}


				zt_drawListPushColor(draw_list, color);

				zt_drawListAddLine(draw_list, zt_vec3(p0, 0), zt_vec3(p1, 0));

				ztVec2 c = (p0 + p1) * .5f;
				zt_drawListAddLine(draw_list, c, c + n * .2f);

				if (level->colliders[i].type == ztPlatformerColliderType_Blower) {
					ztVec2 p0, p1, p2, p3;
					_zt_platformerBlowerGetPoints(level, &level->colliders[i], &p0, &p1, &p2, &p3);

					zt_drawListAddLine(draw_list, p0, p1);
					zt_drawListAddLine(draw_list, p0, p3);
					zt_drawListAddLine(draw_list, p2, p3);
				}

				zt_drawListPopColor(draw_list);
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_Blades && non_sprite_layer) {
				zt_drawListPushColor(draw_list, ztColor_Orange);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), level->colliders[i].blades.radius, 32);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), 8 / zt_pixelsPerUnit(), 12);
				zt_drawListPopColor(draw_list);
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_Magnet && non_sprite_layer) {
				zt_drawListPushColor(draw_list, ztColor_LightBlue);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), 8 / zt_pixelsPerUnit(), 12);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), level->colliders[i].magnet.strength * .25f, 32);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), level->colliders[i].magnet.strength * .50f, 32);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), level->colliders[i].magnet.strength * .75f, 32);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), level->colliders[i].magnet.strength * 1.0f, 32);
				zt_drawListPopColor(draw_list);
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_TriggerLine && non_sprite_layer) {
				zt_drawListPushColor(draw_list, ztColor_Yellow);
				zt_drawListAddLine(draw_list, zt_vec3(p0, 0), zt_vec3(p1, 0));

				ztVec2 c = (p0 + p1) * .5f;
				zt_drawListAddLine(draw_list, c, c + n * .2f);

				zt_drawListPopColor(draw_list);
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_TriggerCircle && non_sprite_layer) {
				zt_drawListPushColor(draw_list, ztColor_Yellow);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), level->colliders[i].trigger_circle.radius, 32);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), 8 / zt_pixelsPerUnit(), 12);
				zt_drawListPopColor(draw_list);
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_TriggerRect && non_sprite_layer) {
				zt_drawListPushColor(draw_list, ztColor_Yellow);
				ztVec2 p0, p1, p2, p3;
				_zt_platformerRectGetPoints(level, &level->colliders[i], &p0, &p1, &p2, &p3);

				ztVec2 c = (p1 + p2) * .5f;
				zt_drawListAddLine(draw_list, c, c + n * .2f);
				zt_drawListAddLine(draw_list, p0, p1);
				zt_drawListAddLine(draw_list, p1, p2);
				zt_drawListAddLine(draw_list, p0, p3);
				zt_drawListAddLine(draw_list, p2, p3);
				zt_drawListPopColor(draw_list);
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_Sprite) {
				if (layer < 0 || layer == level->colliders[i].sprite.layer) {
					zt_drawListPushColor(draw_list, ztColor_Magenta * zt_vec4(1, 1, 1, .5f));

					ztVec2 ne = zt_vec2(level->colliders[i].sprite.sprite.half_size.x, level->colliders[i].sprite.sprite.half_size.y);
					ztVec2 nw = zt_vec2(-level->colliders[i].sprite.sprite.half_size.x, level->colliders[i].sprite.sprite.half_size.y);
					ztVec2 se = zt_vec2(level->colliders[i].sprite.sprite.half_size.x, -level->colliders[i].sprite.sprite.half_size.y);
					ztVec2 sw = zt_vec2(-level->colliders[i].sprite.sprite.half_size.x, -level->colliders[i].sprite.sprite.half_size.y);

					if (!zt_real32Eq(level->colliders[i].sprite.rotation, 0)) {
						ztMat4 rotation_mat = ztMat4::identity.getRotateEuler(0, 0, level->colliders[i].sprite.rotation);
						ne = (rotation_mat * zt_vec3(ne, 0)).xy;
						nw = (rotation_mat * zt_vec3(nw, 0)).xy;
						se = (rotation_mat * zt_vec3(se, 0)).xy;
						sw = (rotation_mat * zt_vec3(sw, 0)).xy;
					}
					//zt_drawListAddLine(draw_list, p0 + nw, p0 + ne);
					//zt_drawListAddLine(draw_list, p0 + nw, p0 + sw);
					//zt_drawListAddLine(draw_list, p0 + sw, p0 + se);
					//zt_drawListAddLine(draw_list, p0 + se, p0 + ne);

					zt_drawListPopColor(draw_list);
					zt_drawListPushColor(draw_list, ztColor_Yellow * zt_vec4(1, 1, 1, .125f));
					zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), 8 / zt_pixelsPerUnit(), 12);
					zt_drawListPopColor(draw_list);
				}
			}
			else if (level->colliders[i].type == ztPlatformerColliderType_Marker && non_sprite_layer) {

				ztPlatformerLevelEditorMarker *marker = nullptr;
				const char *marker_name = nullptr;
				if (level_editor) {
					zt_fjz(level_editor->markers_size) {
						if (level_editor->markers[j].value == level->colliders[i].marker.type) {
							marker = &level_editor->markers[j];
							marker_name = level_editor->markers[j].name;
							break;
						}
					}
				}

				if (marker) {
					if (marker->sprite && zt_bitIsSet(flags, ztPlatformerDrawDebugFlags_DrawMarkerSprites)) {
						zt_drawListAddSpriteFast(draw_list, marker->sprite, zt_vec3(p0 + marker->sprite_offset, 0), ztVec3::zero, zt_vec3(marker->sprite_scale, 1));
					}
				}

				zt_drawListPushColor(draw_list, ztColor_Green);
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), ZT_PLATFORMER_MARKER_RADIUS, 32);
				zt_drawListAddLine(draw_list, p0 + zt_vec2(ZT_PLATFORMER_MARKER_RADIUS, 0), p0 - zt_vec2(ZT_PLATFORMER_MARKER_RADIUS, 0));
				zt_drawListAddLine(draw_list, p0 + zt_vec2(0, ZT_PLATFORMER_MARKER_RADIUS), p0 - zt_vec2(0, ZT_PLATFORMER_MARKER_RADIUS));

				r32 y = ZT_PLATFORMER_MARKER_RADIUS + .15f;
				if (marker_name) {
					ztVec2 ext = ztVec2::zero;
					zt_drawListAddText2D(draw_list, ztFontDefault, marker_name, p0 + zt_vec2(0, y), 0, 0, &ext);
				}
				if (level->colliders[i].marker.info[0] != 0 && !zt_strEquals(level->colliders[i].marker.info, marker_name)) {
					zt_drawListAddText2D(draw_list, ztFontDefault, level->colliders[i].marker.info, p0 - zt_vec2(0, y));
				}

				zt_drawListPopColor(draw_list);
			}

			if (level->colliders[i].movement_path >= 0) {
				ztVec2 min, max;
				_zt_platformerGetExtents(level, &level->colliders[i], &min, &max, true);

				ztVec2 center = (min + max) * .5f;
				ztVec2 size = max - min;

				zt_drawListPushColor(draw_list, ztColor_Purple);
				zt_drawListAddEmptyRect(draw_list, center, size);
				zt_drawListPopColor(draw_list);
			}
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================

void zt_platformerDrawDebugPhysicsObjects(ztPlatformerLevel *level, ztDrawList *draw_list, ztPlatformerPhysicsObject *objects, i32 objects_size, i32 flags)
{
	zt_returnOnNull(level);
	zt_returnOnNull(draw_list);

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Solid));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	zt_fiz(objects_size) {
		zt_drawListPushColor(draw_list, ztColor_Cyan);
		zt_drawListAddEmptyRect(draw_list, objects[i].position + objects[i].aabb_center, zt_vec2(.1f, .1f));
		zt_drawListAddEmptyRect(draw_list, objects[i].position + objects[i].aabb_center, objects[i].aabb_size);
		zt_drawListPopColor(draw_list);

		zt_drawListPushColor(draw_list, objects[i].collisions == nullptr ? ztColor_Green : ztColor_Yellow);
		switch (objects[i].type)
		{
			case ztPlatformerPhysicsObjectType_AABB: {
				zt_drawListAddEmptyRect(draw_list, objects[i].position + objects[i].aabb_center, objects[i].aabb.size);
				zt_drawListPushColor(draw_list, ztColor_Purple);
				zt_drawListAddEmptyRect(draw_list, zt_vec3(objects[i].position + objects[i].aabb_center, 0) + zt_vec3(0, objects[i].aabb.size.y * .375f, 0), objects[i].aabb.size * zt_vec2(1, .25f));
				zt_drawListAddLine(draw_list, zt_vec3(objects[i].position + objects[i].aabb_center, 0) + zt_vec3(objects[i].aabb.size.x / -2, objects[i].aabb.size.y / 2, 0), zt_vec3(objects[i].position + objects[i].aabb_center, 0) + zt_vec3(objects[i].aabb.size.x / 2, objects[i].aabb.size.y / 2, 0));
				zt_drawListPopColor(draw_list);
			} break;
		}
		zt_drawListPopColor(draw_list);

		if (zt_bitIsSet(flags, ztPlatformerDrawDebugFlags_DrawQuadTree)) {
			ztQuadTree::Node *nodes[16];
			i32 nodes_in = zt_quadTreeFindNodesThatIntersect(&level->quadtree, nodes, zt_elementsOf(nodes), objects[i].position + objects[i].aabb_center, objects[i].aabb_size);

			zt_drawListPushColor(draw_list, ztColor_Yellow);
			zt_fiz(nodes_in) {
				zt_drawListAddEmptyRect(draw_list, nodes[i]->center, nodes[i]->size);
			}
			zt_drawListPopColor(draw_list);
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================

void zt_platformerUpdateColliders(ztPlatformerLevel *level, r32 dt)
{
	zt_returnOnNull(level);

	zt_fiz(level->movement_paths_used) {
		level->movement_paths[i].current_time += dt;

		r32 max_time = 0;
		zt_fjz(level->movement_paths[i].points) {
			max_time += level->movement_paths[i].times[j];
		}

		//if (level->movement_paths[i].current_time > max_time) {
		//	level->movement_paths[i].current_time -= max_time;
		//}
	}

	zt_fiz(level->colliders_used) {
		ztPlatformerCollider *collider = &level->colliders[i];

		if (collider->movement_path >= 0) {
			ztPlatformerMovementPath *path = &level->movement_paths[collider->movement_path];

			r32 movement_time = (path->current_time + collider->movement_offset) * collider->movement_speed;
			{
				r32 max_movement_time = 0;
				zt_fiz(path->points) {
					max_movement_time += path->times[i];
				}

				if (movement_time > max_movement_time) {
					movement_time = zt_fmod(movement_time, max_movement_time);
				}
			}

			ztVec2 offset = ztVec2::zero;
			zt_fiz(path->points) {
				if (movement_time < path->times[i]) {
					r32 pct = movement_time / path->times[i];
					//if (ZT_FUNCTION_POINTER_IS_VALID(path->update_function)) {
					//	pct = ZT_FUNCTION_POINTER_ACCESS(path->update_function, ztPlatformerCollideMovementPathUpdate_Func)(collider, path, i, pct, path->update_function_user_data);
					//}

					offset += path->movements[i] * pct;
					break;
				}
				else {
					movement_time -= path->times[i];
					offset += path->movements[i];
				}
			}

			collider->offset_last = collider->offset_this;
			collider->offset_this = offset;
		}
	}

}

// ================================================================================================================================================================================================

void zt_platformerUpdatePhysicsObjects(ztPlatformerLevel *level, ztPlatformerPhysicsObject *objects, i32 objects_size, r32 dt)
{
	zt_returnOnNull(level);

	ztQuadTree::Node *nodes[64];

	enum Stage_Enum
	{
		Stage_EnvironmentalPushes = 0,
		Stage_Movers,
		Stage_Triggers,
		Stage_Surfaces, // must be last in this list

		Stage_MAX,
	};

	level->collisions_used = 0;

	for (int stage = 0; stage < Stage_MAX; ++stage) {

		ztPlatformerCollider *collisions[128];
		i32 collisions_count = 0;

		zt_fxz(objects_size) {

			if (stage == 0) {
				objects[x].collisions = nullptr;
			}

			r32 gravity_pull = level->gravity * dt * objects[x].mass;

			bool was_yvel_zero_or_greater = objects[x].velocity.y >= 0;
			ztVec2 new_pos;
			if (zt_bitIsSet(objects[x].flags, ztPlatformerPhysicsObjectFlags_Kinematic)) {
				if (stage == Stage_Surfaces) {
					if (objects[x].collider_resting_on) {
						if (objects[x].collider_resting_on->type == ztPlatformerColliderType_Surface) {
							// we're resting on a surface.  if this is a slanted surface, applying gravity can cause undesired consequences, so check to see if we're still above the surface

							ztVec3 aabb_ctr = zt_vec3(objects[x].position + objects[x].aabb.center - zt_vec2(0, 1 / zt_pixelsPerUnit()), 0);
							ztVec3 aabb_size = zt_vec3(objects[x].aabb.size, 1);

							ztVec2 p0, p1, collider_normal;
							zt_platformerGetColliderPositions(level, objects[x].collider_resting_on, &p0, &p1, &collider_normal);

							if (zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr, aabb_size)) {
								gravity_pull = 0;

								if (objects[x].velocity_transfer != 0) {
									objects[x].velocity.y = zt_approach(objects[x].velocity.y, 0, 1 * dt);

									if (zt_real32Close(objects[x].velocity.y, 0)) {
										objects[x].velocity.y = 0;
									}
									if (zt_abs(objects[x].velocity.y) < 16 / zt_pixelsPerUnit()) {
										objects[x].velocity.x = zt_approach(objects[x].velocity.x, 0, 1 * dt);
										if (zt_real32Close(objects[x].velocity.x, 0)) {
											objects[x].velocity.x = 0;
										}
									}
								}
							}
							else {
								objects[x].collider_resting_on = nullptr;
							}
						}
					}

					objects[x].velocity += zt_vec2(0, gravity_pull);
					objects[x].velocity *= zt_pow(level->air_friction_multiplier, dt);

					if (level->terminal_velocity < 0) {
						objects[x].velocity.y = zt_max(level->terminal_velocity, objects[x].velocity.y);
					}
					else {
						objects[x].velocity.y = zt_min(level->terminal_velocity, objects[x].velocity.y);
					}

					new_pos = objects[x].position + objects[x].velocity * dt;
				}
				else {
					new_pos = objects[x].position;
				}
			}
			else {
				new_pos = objects[x].position;
			}

			if (objects[x].collider_resting_on) {
				if (objects[x].collider_resting_on->offset_this != ztVec2::zero && stage == Stage_EnvironmentalPushes) {
					ztVec2 velocity = zt_platformerGetColliderVelocity(objects[x].collider_resting_on);
					new_pos += velocity;
				}
				objects[x].movement_since_last_collision = 0;
			}

			ztVec2 obj_aabb_old_min = zt_vec2((objects[x].position.x + objects[x].aabb_center.x) - objects[x].aabb_size.x * .5f, (objects[x].position.y + objects[x].aabb_center.y) - objects[x].aabb_size.y * .5f);
			ztVec2 obj_aabb_old_max = zt_vec2((objects[x].position.x + objects[x].aabb_center.x) + objects[x].aabb_size.x * .5f, (objects[x].position.y + objects[x].aabb_center.y) + objects[x].aabb_size.y * .5f);
			ztVec2 obj_aabb_new_min = zt_vec2((new_pos.x + objects[x].aabb_center.x) - objects[x].aabb_size.x * .5f, (new_pos.y + objects[x].aabb_center.y) - objects[x].aabb_size.y * .5f);
			ztVec2 obj_aabb_new_max = zt_vec2((new_pos.x + objects[x].aabb_center.x) + objects[x].aabb_size.x * .5f, (new_pos.y + objects[x].aabb_center.y) + objects[x].aabb_size.y * .5f);

			ztVec2 obj_aabb_min = zt_vec2(zt_min(obj_aabb_old_min.x, obj_aabb_new_min.x), zt_min(obj_aabb_old_min.y, obj_aabb_new_min.y));
			ztVec2 obj_aabb_max = zt_vec2(zt_max(obj_aabb_old_max.x, obj_aabb_new_max.x), zt_max(obj_aabb_old_max.y, obj_aabb_new_max.y));

			ztVec2 obj_aabb_center = (obj_aabb_min + obj_aabb_max) * .5f;
			ztVec2 obj_aabb_size = obj_aabb_max - obj_aabb_min;

			i32 nodes_count = zt_quadTreeFindNodesThatIntersect(&level->quadtree, nodes, zt_elementsOf(nodes), obj_aabb_center, obj_aabb_size * 1.25f);

			bool has_collision = true;
			collisions_count = 0;
			while (has_collision) {

				switch (objects[x].type) {
					case ztPlatformerPhysicsObjectType_AABB: {
						ztVec2                first_intersection_point = ztVec2::max;
						r32                   first_intersection_time = ztReal32Max;
						ztVec2                first_intersection_normal = ztVec2::zero;
						bool                  first_intersection_edge = false;
						ztPlatformerCollider *first_intersection_collider = nullptr;
						bool                  first_intersection_force_movement = false;
						r32                   first_intersection_closest_point_dot = ztReal32Min;

						ztVec3 aabb_ctr = zt_vec3(new_pos + objects[x].aabb.center, 0);
						ztVec3 aabb_size = zt_vec3(objects[x].aabb.size, 1);

						zt_fiz(nodes_count) {
							zt_fjz(nodes[i]->objects_count) {
								ztPlatformerCollider *collider = &level->colliders[nodes[i]->objects[j]];

								if (collider->type == ztPlatformerColliderType_Sprite || collider->type == ztPlatformerColliderType_Marker || zt_bitIsSet(collider->flags, ztPlatformerColliderFlags_Disabled)) {
									continue;
								}

								if ((collider->type == ztPlatformerColliderType_Surface || collider->type == ztPlatformerColliderType_Spring) && stage != Stage_Movers && stage != Stage_Triggers) {
									r32 intersect_time = ztReal32Max;

									ztVec2 p0, p1, collider_normal;
									zt_platformerGetColliderPositions(level, collider, &p0, &p1, &collider_normal);

									r32 dot = collider_normal.dot(objects[x].velocity.getNormal());
									if (dot > 0.f) {
										continue; // if the object is not heading towards the normal of this collider, the collision is ignored
									}

									ztVec3 intersect_points[2];

									if (zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr, aabb_size, &intersect_time, intersect_points)) {
										ztVec2 closest_point = zt_closestPointLineSegmentPoint(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr).xy;
										ztVec2 closest_point_diff = aabb_ctr.xy - closest_point;
										r32 diff_dot = closest_point_diff.getNormal().dot(collider_normal);
										if (diff_dot < 0) {
											// this handles cases where the object just hit its peak and is partially colliding with the segment as it's heading back.
											// in these cases, the collision is ignored because the object hasn't completely cleared the segment before colliding
											continue;
										}

										r32 edge_percent = (3 / zt_pixelsPerUnit()) / zt_abs(p1.distance(p0));

										r32 edge_check = intersect_time;
										bool is_edge = edge_check < edge_percent || edge_check > 1 - edge_percent;
										if (is_edge && first_intersection_time != ztReal32Max && !first_intersection_force_movement && !first_intersection_edge) {
											// if an intersection has already been found, we ignore this edge intersection
											continue;
										}

										// see if we were already colliding with this, and if so, make sure velocity is heading in the direction of the normal
										ztVec2 platform_velocity = zt_platformerGetColliderVelocity(collider);
										ztVec2 pp0 = (p0 - (platform_velocity * dt)), pp1 = (p1 - (platform_velocity * dt));

										if (stage == Stage_EnvironmentalPushes && zt_collisionLineSegmentInAABB(zt_vec3(pp0, 0), zt_vec3(pp1, 0), zt_vec3(objects[x].position + objects[x].aabb.center, 0), aabb_size)) {
											r32 vel_dot = platform_velocity.dot(objects[x].velocity);
											if (vel_dot < 0 && objects[x].velocity.length() < platform_velocity.length() || objects[x].velocity == ztVec2::zero) {
												objects[x].velocity = platform_velocity * .0001f; // give close to zero, but not zero velocity so the code that makes sure the object comes to rest on the platform is executed
												if (objects[x].velocity == ztVec2::zero) {
													objects[x].velocity = collider_normal * .0001f;
												}
												first_intersection_time = 0;
												first_intersection_point = objects[x].position;
												first_intersection_normal = collider_normal;
												first_intersection_edge = is_edge;
												first_intersection_collider = collider;
												first_intersection_force_movement = false;
											}

											continue;
										}

										i32 steps = 10;
										r32 dt_div = dt / steps;
										zt_fiz(steps) {  // step x times to find closest time to collision
											ztVec2 new_pos2 = objects[x].position + objects[x].velocity * (dt_div * i);
											ztVec3 aabb_ctr2 = zt_vec3(new_pos2 + objects[x].aabb.center, 0);

											if (zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr2, aabb_size)) {
												intersect_time = dt_div * i;
												break;
											}
										}

										if (zt_real32Eq(intersect_time, first_intersection_time)) {
											// go with the one that has the smaller collision normal dot velocity
											if (first_intersection_closest_point_dot < diff_dot) {
												first_intersection_time += dt_div;
											}
										}

										if (intersect_time < first_intersection_time || (first_intersection_edge && !is_edge)) { // check for first_intersection_edge so that any non-edge intersection takes precedent over an edge intersection
											first_intersection_time = intersect_time;
											first_intersection_point = ztVec2::lerp(objects[x].position, new_pos, intersect_time);
											first_intersection_normal = collider_normal;
											first_intersection_edge = is_edge;
											first_intersection_collider = collider;
											first_intersection_force_movement = false;
											first_intersection_closest_point_dot = diff_dot;
										}
									}
								}
								else if (collider->type == ztPlatformerColliderType_Blower && stage == Stage_Movers && first_intersection_time == ztReal32Max) {
									bool already_encountered = false;
									zt_fzz(collisions_count) {
										if (collisions[z] == collider) {
											already_encountered = true;
											break;
										}
									}

									if (!already_encountered) {
										ztVec2 p0, p1, p2, p3;
										_zt_platformerBlowerGetPoints(level, collider, &p0, &p1, &p2, &p3);

										if (zt_collisionPointInTriangle(zt_vec3(new_pos, 0), zt_vec3(p0, 0), zt_vec3(p1, 0), zt_vec3(p2, 0)) || zt_collisionPointInTriangle(zt_vec3(new_pos, 0), zt_vec3(p0, 0), zt_vec3(p2, 0), zt_vec3(p3, 0))) {
											ztVec2 collider_normal;
											zt_platformerGetColliderPositions(level, collider, &p0, &p1, &collider_normal);

											first_intersection_time = 0;
											first_intersection_point = new_pos;
											first_intersection_normal = collider_normal;
											first_intersection_edge = false;
											first_intersection_collider = collider;
											first_intersection_force_movement = true;
										}
									}
								}
								else if (collider->type == ztPlatformerColliderType_Magnet && stage == Stage_Movers && first_intersection_time == ztReal32Max) {
									bool already_encountered = false;
									zt_fzz(collisions_count) {
										if (collisions[z] == collider) {
											already_encountered = true;
											break;
										}
									}

									if (!already_encountered) {
										ztVec2 p0, p1;
										zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr);

										if (zt_collisionSphereInAABB(zt_vec3(p0, 0), collider->magnet.strength, aabb_ctr, aabb_size)) {
											first_intersection_time = 1;
											first_intersection_point = new_pos;
											first_intersection_normal = (collider->points[0] - new_pos).getNormal();
											first_intersection_edge = false;
											first_intersection_collider = collider;
											first_intersection_force_movement = true;
										}
									}
								}
								else if (collider->type == ztPlatformerColliderType_Blades && stage == Stage_Movers) {
									r32 intersect_time = 1;
									ztVec2 p0, p1;
									zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr);
									if (zt_collisionSphereInAABB(zt_vec3(p0, 0), collider->blades.radius, aabb_ctr, aabb_size)) {
										i32 steps = 10;
										r32 dt_div = dt / steps;
										zt_fiz(steps) {  // step x times to find closest time to collision
											ztVec2 new_pos2 = objects[x].position + objects[x].velocity * (dt_div * i);
											ztVec3 aabb_ctr2 = zt_vec3(new_pos2 + objects[x].aabb.center, 0);

											if (zt_collisionSphereInAABB(zt_vec3(collider->points[0], 0), collider->blades.radius, aabb_ctr2, aabb_size)) {
												intersect_time = dt_div * i;
												break;
											}
										}

										if (intersect_time < first_intersection_time || first_intersection_edge) { // check for first_intersection_edge so that any non-edge intersection takes precedent over an edge intersection
											first_intersection_time = intersect_time;
											first_intersection_point = ztVec2::lerp(objects[x].position, new_pos, intersect_time);
											first_intersection_normal = (new_pos - collider->points[0]).getNormal();
											first_intersection_edge = false;
											first_intersection_collider = collider;
											first_intersection_force_movement = true;
										}
									}
								}
								else if (collider->type == ztPlatformerColliderType_TriggerLine && stage == Stage_Triggers) {
									ztVec2 p0, p1, collider_normal;
									zt_platformerGetColliderPositions(level, collider, &p0, &p1, &collider_normal);

									r32 dot = collider_normal.dot(objects[x].velocity.getNormal());
									if (dot > 0.f) {
										continue; // if the object is not heading towards the normal of this collider, the collision is ignored
									}

									r32 intersect_time = 0;
									ztVec3 intersect_points[2];

									if (zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr, aabb_size, &intersect_time, intersect_points)) {
										i32 steps = 10;
										r32 dt_div = dt / steps;
										zt_fiz(steps) {  // step x times to find closest time to collision
											ztVec2 new_pos2 = objects[x].position + objects[x].velocity * (dt_div * i);
											ztVec3 aabb_ctr2 = zt_vec3(new_pos2 + objects[x].aabb.center, 0);

											if (zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr2, aabb_size)) {
												intersect_time = dt_div * i;
												break;
											}
										}

										ztPlatformerLevelCollision *collision = level->collisions_used < level->collisions_size ? &level->collisions[level->collisions_used++] : nullptr;

										if (collision) {
											collision->collider = collider;
											collision->time = intersect_time;
											collision->point = ztVec2::lerp(objects[x].position, new_pos, intersect_time);
											collision->normal = collider_normal;
											collision->force_movement = false;

											zt_flink(collision_check, objects[x].collisions) {
												zt_assert(collision_check != collision);
											}

											zt_singleLinkAddToBegin(objects[x].collisions, collision);
										}
									}
								}
								else if (collider->type == ztPlatformerColliderType_TriggerCircle && stage == Stage_Triggers) {
									r32 intersect_time = 1;
									ztVec2 p0, p1;
									zt_platformerGetColliderPositions(level, collider, &p0, &p1, nullptr);
									if (zt_collisionSphereInAABB(zt_vec3(p0, 0), collider->trigger_circle.radius, aabb_ctr, aabb_size)) {
										i32 steps = 10;
										r32 dt_div = dt / steps;
										zt_fiz(steps) {  // step x times to find closest time to collision
											ztVec2 new_pos2 = objects[x].position + objects[x].velocity * (dt_div * i);
											ztVec3 aabb_ctr2 = zt_vec3(new_pos2 + objects[x].aabb.center, 0);

											if (zt_collisionSphereInAABB(zt_vec3(collider->points[0], 0), collider->blades.radius, aabb_ctr2, aabb_size)) {
												intersect_time = dt_div * i;
												break;
											}
										}

										ztPlatformerLevelCollision *collision = level->collisions_used < level->collisions_size ? &level->collisions[level->collisions_used++] : nullptr;

										if (collision) {
											collision->collider = collider;
											collision->time = intersect_time;
											collision->point = ztVec2::lerp(objects[x].position, new_pos, intersect_time);
											collision->normal = (new_pos - collider->points[0]).getNormal();
											collision->force_movement = false;

											zt_flink(collision_check, objects[x].collisions) {
												zt_assert(collision_check != collision);
											}

											zt_singleLinkAddToBegin(objects[x].collisions, collision);
										}
									}
								}
								else if (collider->type == ztPlatformerColliderType_TriggerRect && stage == Stage_Triggers) {
									ztVec2 p0, p1, p2, p3;
									_zt_platformerRectGetPoints(level, collider, &p0, &p1, &p2, &p3);

									if (zt_collisionTriangleInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), zt_vec3(p2, 0), aabb_ctr, aabb_size) || zt_collisionTriangleInAABB(zt_vec3(p0, 0), zt_vec3(p2, 0), zt_vec3(p3, 0), aabb_ctr, aabb_size)) {
										ztVec2 collider_normal;
										zt_platformerGetColliderPositions(level, collider, &p0, &p1, &collider_normal);

										ztPlatformerLevelCollision *collision = level->collisions_used < level->collisions_size ? &level->collisions[level->collisions_used++] : nullptr;

										if (collision) {
											collision->collider = collider;
											collision->time = 0;
											collision->point = new_pos;
											collision->normal = collider_normal;
											collision->force_movement = false;

											zt_flink(collision_check, objects[x].collisions) {
												zt_assert(collision_check != collision);
											}

											zt_singleLinkAddToBegin(objects[x].collisions, collision);
										}
									}
								}
							}
						}

						r32 movement_since_last_collision = objects[x].movement_since_last_collision;

						if (first_intersection_time != ztReal32Max) {
							has_collision = true;

							if (collisions_count < zt_elementsOf(collisions)) {
								collisions[collisions_count++] = first_intersection_collider;
							}

							bool stop_velocity = false;

							if (stage == Stage_Surfaces) {

								if (first_intersection_normal == zt_vec2(-1, 0)) {
									int debug_stop = 1;
								}

								if (objects[x].velocity_transfer == 0) {
									ztVec2 u = objects[x].velocity.dot(first_intersection_normal) * first_intersection_normal;
									ztVec2 w = objects[x].velocity - u;

									if (first_intersection_normal.x != 0) {
										objects[x].velocity.x *= .75f * zt_abs(first_intersection_normal.x);
									}
									if (first_intersection_normal.y != 0) {
										objects[x].velocity.y = first_intersection_normal.y * .0001f;// *= .75f * zt_abs(first_intersection_normal.y);
									}
								}
								else {
									ztVec2 u = objects[x].velocity.dot((first_intersection_normal * objects[x].velocity_transfer)) * (first_intersection_normal * objects[x].velocity_transfer);
									ztVec2 w = objects[x].velocity - u;

									objects[x].velocity = w - u;
									objects[x].velocity *= .75f;

									objects[x].movement_since_last_collision = 0;
								}

								//objects[x].angular_velocity += zt_pow(objects[x].velocity.distance(ztVec2::zero), objects[x].velocity.distance(ztVec2::zero)) * (objects[x].velocity.x < 0 ? -1 : 1) * .00001f;
								//objects[x].angular_velocity = zt_clamp(objects[x].angular_velocity, -.99f, .99f);

								//if (first_intersection_collider->type == ztPlatformerColliderType_MovingSurface) {
								if (first_intersection_collider->offset_this != ztVec2::zero) {
									// add the moving platform velocity to the object's velocity
									ztVec2 platform_velocity = zt_platformerGetColliderVelocity(first_intersection_collider);// _zt_platformerMovingPlatformGetVelocity(first_intersection_collider);

									if (objects[x].velocity.length() < 8 / zt_pixelsPerUnit()) {
										stop_velocity = true;
									}

									r32 vel_dot = platform_velocity.dot(objects[x].velocity);
									if (vel_dot < 0) {
										objects[x].velocity += platform_velocity * objects[x].velocity_transfer;
									}
								}
								else if (first_intersection_collider->type == ztPlatformerColliderType_Spring) {
									ztVec2 p0, p1, n;
									zt_platformerGetColliderPositions(level, first_intersection_collider, &p0, &p1, &n);

									if (objects[x].velocity_transfer == 0) {
										objects[x].velocity += first_intersection_normal * first_intersection_collider->spring.strength * 2;
									}
									else {
										objects[x].velocity += objects[x].velocity.getNormal() * first_intersection_collider->spring.strength;
									}
								}
							}
							else if (stage == Stage_Movers) {
								if (first_intersection_collider->type == ztPlatformerColliderType_Blower) {
									objects[x].velocity += first_intersection_normal * first_intersection_collider->blower.strength * dt * 25.f;

									if (first_intersection_normal.dot(zt_vec2(0, 1)) > .9f && zt_abs(objects[x].velocity.length()) < (32 / zt_pixelsPerUnit())) {
										r32 dot = objects[x].velocity.getNormal().dot(first_intersection_normal);
										if (dot > .8f || dot < -.8f) {
											objects[x].velocity.x *= 1.5f;
											if (zt_real32Eq(objects[x].velocity.x, 0)) {
												objects[x].velocity.x = .1f;
											}
										}
									}
								}
								else if (first_intersection_collider->type == ztPlatformerColliderType_Magnet) {
									r32 strength = 1 - (zt_abs(first_intersection_point.distance(first_intersection_collider->points[0])) / first_intersection_collider->magnet.strength);
									objects[x].velocity *= .99f;
									objects[x].velocity += first_intersection_normal * strength * dt * 10.f;
								}
								else if (first_intersection_collider->type == ztPlatformerColliderType_Blades) {
									objects[x].velocity = first_intersection_normal * first_intersection_collider->blades.speed * 20.f;
								}
							}

							ztPlatformerLevelCollision *collision = level->collisions_used < level->collisions_size ? &level->collisions[level->collisions_used++] : nullptr;

							if (collision) {
								collision->collider = first_intersection_collider;
								collision->time = first_intersection_time;
								collision->point = first_intersection_point;
								collision->normal = first_intersection_normal;
								collision->force_movement = first_intersection_force_movement;

								zt_flink(collision_check, objects[x].collisions) {
									zt_assert(collision_check != collision);
								}

								zt_singleLinkAddToBegin(objects[x].collisions, collision);
							}

							if (objects[x].velocity != ztVec2::zero || first_intersection_force_movement) {
								r32 dist = objects[x].position.distance(new_pos);
								r32 pos_pct = dist == 0.f ? 0 : (objects[x].position.distance(first_intersection_point) / dist);
								r32 rem_pct = 1 - pos_pct;
								new_pos = first_intersection_point + (objects[x].velocity * (dt * rem_pct));
								aabb_ctr = zt_vec3(new_pos + objects[x].aabb.center, 0);

								{
									i32 bailout_start = 400;
									i32 bailout = bailout_start;

									// make sure the object isn't resting within a collision
									if (first_intersection_collider->type == ztPlatformerColliderType_Surface) {
										ztVec2 p0, p1;
										zt_platformerGetColliderPositions(level, first_intersection_collider, &p0, &p1, nullptr);
										while (bailout-- > 0 && zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr, aabb_size)) {
											//new_pos = new_pos + (objects[x].velocity * (dt / 10.f));
											new_pos = new_pos + (first_intersection_normal * (dt / 10.f));
											aabb_ctr = zt_vec3(new_pos + objects[x].aabb.center, 0);
											if (zt_bitIsSet(objects[x].flags, ztPlatformerPhysicsObjectFlags_KinematicIfMoved)) {
												objects[x].flags |= ztPlatformerPhysicsObjectFlags_Kinematic;
											}
										}
										if (bailout <= 0) {
											zt_logCritical("had to bail out of surface adjust");

											if (first_intersection_collider->offset_this != ztVec2::zero) {
												if (bailout <= 0) {
													// we moved a lot but are still colliding.  need to move the object in the direction of the moving platform's velocity until it's not colliding
													bailout = bailout_start;
													while (bailout-- > 0 && zt_collisionLineSegmentInAABB(zt_vec3(p0, 0), zt_vec3(p1, 0), aabb_ctr, aabb_size)) {
														new_pos = new_pos + (first_intersection_normal * (dt / 10.f));
														aabb_ctr = zt_vec3(new_pos + objects[x].aabb.center, 0);
														if (zt_bitIsSet(objects[x].flags, ztPlatformerPhysicsObjectFlags_KinematicIfMoved)) {
															objects[x].flags |= ztPlatformerPhysicsObjectFlags_Kinematic;
														}
													}
												}
												if (bailout <= 0) {
													zt_logCritical("had to bail out of moving surface adjust");
													has_collision = false;
												}
											}
											else {
												has_collision = false;
											}
										}
										else {
											if (objects[x].velocity.equalsClose(ztVec2::zero)) {
												new_pos = new_pos + (first_intersection_normal * (dt / 2.f));
											}
										}
									}
								}
							}

							// determine if we should stop this object
							r32 moved_threshold = (16 / zt_pixelsPerUnit()) * dt;
							r32 moved = zt_abs(new_pos.x - objects[x].position.x) + zt_abs(new_pos.y - objects[x].position.y);
							if (stop_velocity || moved < moved_threshold) {
								if (first_intersection_collider->type != ztPlatformerColliderType_Blower && first_intersection_collider->type != ztPlatformerColliderType_Magnet) {
									r32 velocity_threshold = moved_threshold / dt;
									if (objects[x].velocity.length() < velocity_threshold) {
										objects[x].velocity = ztVec2::zero;
										has_collision = false;
									}
								}
							}
							objects[x].movement_since_last_collision = 0;
						}
						else {
							objects[x].movement_since_last_collision += zt_abs(new_pos.distance(objects[x].position));
							has_collision = false;
						}

						if (stage == Stage_MAX - 1) {
							r32 velocity_threshold = (8 / zt_pixelsPerUnit());

							if (zt_real32Close(zt_abs(objects[x].position.y - new_pos.y), 0) || objects[x].velocity == ztVec2::zero) {
								zt_flink(collision, objects[x].collisions) {
									if (collision->collider->type == ztPlatformerColliderType_Surface) {
										if (collision->normal.dot(zt_vec2(0, 1)) > .25f) {
											objects[x].collider_resting_on = collision->collider;
											// don't break.  these are appended to the beginning, so if there are any further colliders that match, they have a better collision

											r32 movement_threshold = 8 / zt_pixelsPerUnit();
											r32 velocity_len = objects[x].velocity.length();
											if (movement_since_last_collision < movement_threshold && velocity_len < velocity_threshold) {
												objects[x].velocity = ztVec2::zero;
											}
										}
									}
								}
							}
							else if (objects[x].velocity.length() > velocity_threshold && zt_bitIsSet(objects[x].flags, ztPlatformerPhysicsObjectFlags_Kinematic)) {
								objects[x].collider_resting_on = nullptr;
							}
						}

						objects[x].position = new_pos;
					} break;

				} // switch object type
			} // while has collision

			int debug_stop = 0;
		} // object x
	} // stage
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_platformerActorTemplateInit(ztPlatformerActorTemplate *actor_template, i32 collision_flags, i32 collides_with, ztPlatformerActorInstance *actor_instances, i32 actor_instances_count, ZT_FUNCTION_POINTER_VAR(collision_func, ztPlatformerActorCollision_Func), void *collision_user_data)
{
	zt_returnOnNull(actor_template);
	zt_returnOnNull(actor_instances);

	zt_memSet(actor_template, zt_sizeof(ztPlatformerActorTemplate), 0);

	actor_template->actor_instances = actor_instances;
	actor_template->actor_instances_count = actor_instances_count;
	actor_template->collision_flags = collision_flags;
	actor_template->collides_with = collides_with;

	actor_template->collision_func = collision_func;
	actor_template->collision_user_data = collision_user_data;

	zt_fiz(actor_instances_count) {
		actor_template->actor_instances[i].index = i;
		actor_template->actor_instances[i].actor_template = actor_template;
	}
}

// ================================================================================================================================================================================================

void zt_platformerActorsUpdate(ztPlatformerLevel *level, ztPlatformerActorInstance *instances, i32 instances_count, r32 dt)
{
	zt_fiz(instances_count) {
		if (!zt_bitIsSet(instances[i].flags, ztPlatformerActorInstanceFlags_Enabled) || !zt_bitIsSet(instances[i].flags, ztPlatformerActorInstanceFlags_Alive)) {
			continue;
		}

		if (instances[i].physics_object) {
			instances[i].position = instances[i].physics_object->position;
		}
	}

	zt_fiz(instances_count) {
		if (!zt_bitIsSet(instances[i].flags, ztPlatformerActorInstanceFlags_Enabled) || !zt_bitIsSet(instances[i].flags, ztPlatformerActorInstanceFlags_Alive)) {
			continue;
		}

		if (instances[i].actor_template->collides_with == 0) {
			continue;
		}

		ztVec2 aabb_center = instances[i].position + instances[i].actor_template->aabb_overall_center;
		ztVec2 aabb_size = instances[i].actor_template->aabb_overall_size;

		zt_fjz(instances_count) {
			if (!zt_bitIsSet(instances[j].flags, ztPlatformerActorInstanceFlags_Enabled) || !zt_bitIsSet(instances[j].flags, ztPlatformerActorInstanceFlags_Alive) || i == j) {
				continue;
			}

			if (!zt_bitIsSet(instances[i].actor_template->collides_with, instances[j].actor_template->collision_flags)) {
				continue;
			}

			if (zt_collisionAABBInAABB(instances[j].position + instances[j].actor_template->aabb_overall_center, instances[j].actor_template->aabb_overall_size, aabb_center, aabb_size)) {
				zt_fxz(instances[i].actor_template->aabb_count) {
					zt_fyz(instances[j].actor_template->aabb_count) {
						ztVec2 i_aabb_center = instances[i].actor_template->aabb_centers[x] + instances[i].position;
						ztVec2 i_aabb_size = instances[i].actor_template->aabb_sizes[x];

						ztVec2 j_aabb_center = instances[j].actor_template->aabb_centers[y] + instances[j].position;
						ztVec2 j_aabb_size = instances[j].actor_template->aabb_sizes[y];

						ztVec2 collision_normal;
						r32    collision_depth;
						i32    collision_face;

						if (zt_collisionAABBInAABB(j_aabb_center, j_aabb_size, i_aabb_center, i_aabb_size, &collision_normal, &collision_depth, &collision_face)) {
							ztPlatformerActorCollision collision;
							collision.actors[0] = &instances[i];
							collision.actors[1] = &instances[j];
							collision.aabbs[0]  = x;
							collision.aabbs[1]  = y;
							collision.normal    = (j_aabb_center - i_aabb_center).getNormal();// collision_normal;
							collision.face      = collision_face;

							ZT_FUNCTION_POINTER_ACCESS_SAFE(instances[i].actor_template->collision_func, ztPlatformerActorCollision_Func)(level, &collision, instances[i].actor_template->collision_user_data);
						}
					}
				}
			}
		}
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_platformerCharacterActorMakeTemplate(ztPlatformerActorTemplate *character_template, ztPlatformerActorInstance *instances, i32 instances_count, i32 collision_flags, i32 collides_with, ZT_FUNCTION_POINTER_VAR(collision_func, ztPlatformerActorCollision_Func), void *collision_user_data)
{
	zt_returnOnNull(character_template);
	zt_returnOnNull(instances);
	zt_assertReturnOnFail(instances_count > 0);

	zt_platformerActorTemplateInit(character_template, collision_flags, collides_with, instances, instances_count, collision_func, collision_user_data);

	character_template->aabb_centers[0] = zt_vec2(0, 0);
	character_template->aabb_sizes[0] = zt_vec2(1, 1);
	character_template->aabb_count = 1;

	character_template->aabb_overall_center = ztVec2::zero;
	character_template->aabb_overall_size = character_template->aabb_sizes[0];
}

// ================================================================================================================================================================================================

ztPlatformerActorInstance * zt_platformerCharacterActorMakeInstance(ztPlatformerActorTemplate *character_template, ztPlatformerPhysicsObject *physics_object)
{
	if (physics_object) {
		character_template->aabb_centers[0] = physics_object->aabb_center;
		character_template->aabb_sizes[0] = physics_object->aabb_size;
	}

	zt_fiz(character_template->actor_instances_count) {
		ztPlatformerActorInstance *actor_instance = &character_template->actor_instances[i];

		if (zt_bitIsSet(actor_instance->flags, ztPlatformerActorInstanceFlags_Enabled)) {
			continue;
		}

		actor_instance->flags |= ztPlatformerActorInstanceFlags_Enabled | ztPlatformerActorInstanceFlags_Alive;
		actor_instance->physics_object = physics_object;

		if (physics_object) {
			actor_instance->position = physics_object->position;
		}

		return actor_instance;
	}

	return nullptr;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_platformerEnemySimpleWalkerMake(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztPlatformerActorInstance *instances, i32 instances_count, i32 collision_flags, i32 collides_with, r32 speed)
{
	zt_memSet(enemy_template, zt_sizeof(ztPlatformerEnemySimpleWalkerTemplate), 0);

	enemy_template->speed = speed;

	zt_platformerActorTemplateInit(&enemy_template->actor_template, collision_flags, collides_with, instances, instances_count);

	enemy_template->actor_template.aabb_centers[0] = zt_vec2(0, 0);
	enemy_template->actor_template.aabb_sizes[0] = zt_vec2(1, 1);
	enemy_template->actor_template.aabb_count = 1;

	enemy_template->actor_template.aabb_overall_center = ztVec2::zero;
	enemy_template->actor_template.aabb_overall_size = enemy_template->actor_template.aabb_sizes[0];

	enemy_template->instances = zt_mallocStructArray(ztPlatformerEnemySimpleWalkerTemplate::Instance, instances_count);
	enemy_template->instances_count = instances_count;
}

// ================================================================================================================================================================================================

void zt_platformerEnemySimpleWalkerFree(ztPlatformerEnemySimpleWalkerTemplate *enemy_template)
{
	if (enemy_template == nullptr) {
		return;
	}

	if (enemy_template->instances) {
		zt_free(enemy_template->instances);
	}

	zt_memSet(enemy_template, zt_sizeof(ztPlatformerEnemySimpleWalkerTemplate), 0);
}

// ================================================================================================================================================================================================

void zt_platformerEnemySimpleWalkerUpdate(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztPlatformerLevel *level, r32 dt)
{
	zt_fiz(enemy_template->instances_count) {
		ztPlatformerActorInstance *actor_instance = &enemy_template->actor_template.actor_instances[i];

		if (!zt_bitIsSet(actor_instance->flags, ztPlatformerActorInstanceFlags_Alive)) {
			continue;
		}

		ztPlatformerEnemySimpleWalkerTemplate::Instance *enemy_instance = &enemy_template->instances[i];

		// make sure we aren't running into a wall
		{
			ztVec2 line_beg = actor_instance->position;
			ztVec2 line_end = actor_instance->position + zt_vec2(((enemy_template->actor_template.aabb_overall_size.x / 2.f) + (1 / zt_pixelsPerUnit())) * enemy_instance->direction, -((enemy_template->actor_template.aabb_overall_size.y / 2.f) - (1 / zt_pixelsPerUnit())));

			i32 colliders[64];
			i32 colliders_count = zt_platformerGetCollidersThatIntersectLine(level, line_beg, line_end, colliders, zt_elementsOf(colliders));

			if (colliders_count > 0) {
				enemy_instance->direction *= -1;
			}
		}

		// make sure we aren't walking off this surface
		{
			r32 x_offset = ((enemy_template->actor_template.aabb_overall_size.x / 2.f) + (1 / zt_pixelsPerUnit())) * enemy_instance->direction;
			ztVec2 line_beg = actor_instance->position + zt_vec2(x_offset, 0);
			ztVec2 line_end = actor_instance->position + zt_vec2(x_offset, -((enemy_template->actor_template.aabb_overall_size.y / 2.f) + (16 / zt_pixelsPerUnit())));

			i32 colliders[64];
			i32 colliders_count = zt_platformerGetCollidersThatIntersectLine(level, line_beg, line_end, colliders, zt_elementsOf(colliders));

			bool on_same_collider = false;
			zt_fiz(colliders_count) {
				if (colliders[i] == enemy_instance->surface_idx) {
					on_same_collider = true;
					break;
				}
			}

			if (!on_same_collider) {
				enemy_instance->direction *= -1;
			}
		}

		// move
		{
			ztVec2 p0, p1, n;
			zt_platformerGetColliderPositions(level, &level->colliders[enemy_instance->surface_idx], &p0, &p1, &n, true);

			ztVec2 diff = (p1 - p0);
			ztVec2 dir = diff.getNormal();

			ztVec2 movement = dir * enemy_template->speed * dt * (r32)enemy_instance->direction;
			actor_instance->position += movement;
		}
	}
}

// ================================================================================================================================================================================================

void zt_platformerEnemySimpleWalkerRender(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztDrawList *draw_list, bool draw_bounding_box)
{
	ztSprite sprite = zt_spriteMake(2, zt_vec2i(770, 45), zt_vec2i(20, 15));

	zt_fiz(enemy_template->instances_count) {
		ztPlatformerActorInstance *actor_instance = &enemy_template->actor_template.actor_instances[i];

		if (!zt_bitIsSet(actor_instance->flags, ztPlatformerActorInstanceFlags_Alive)) {
			continue;
		}

		ztPlatformerEnemySimpleWalkerTemplate::Instance *enemy_instance = &enemy_template->instances[i];

		if (enemy_instance->animation) {
			ztSprite *sprite = zt_spriteAnimControllerActiveSprite(enemy_instance->animation);
			if (sprite) {
				zt_drawListAddSpriteFast(draw_list, sprite, zt_vec3(actor_instance->position, 0), zt_vec3(0, 0, 0), zt_vec3(2 * (enemy_instance->direction > 0 ? 1.f : -1.f), 2, 1));
			}
		}

		if (draw_bounding_box) {
			zt_drawListPushTexture(draw_list, ztTextureDefault);
			zt_drawListPushColor(draw_list, ztColor_Red);
			zt_drawListAddEmptyRect(draw_list, zt_vec3(actor_instance->position + enemy_template->actor_template.aabb_overall_center, 0), enemy_template->actor_template.aabb_overall_size);
			zt_drawListPopColor(draw_list);
			zt_drawListPopTexture(draw_list);
		}
	}
}

// ================================================================================================================================================================================================

ztPlatformerActorInstance *zt_platformerEnemySimpleWalkerNewInstance(ztPlatformerEnemySimpleWalkerTemplate *enemy_template, ztPlatformerLevel *level, ztVec2 pos, ztPlatformerCollider *surface_walking_on, i32 direction, ztSpriteAnimController *anim_controller)
{
	zt_returnValOnNull(enemy_template, nullptr);
	zt_returnValOnNull(surface_walking_on, nullptr);

	zt_fiz(enemy_template->instances_count) {
		ztPlatformerActorInstance *actor_instance = &enemy_template->actor_template.actor_instances[i];

		if (zt_bitIsSet(actor_instance->flags, ztPlatformerActorInstanceFlags_Enabled)) {
			continue;
		}

		ztPlatformerEnemySimpleWalkerTemplate::Instance *instance = &enemy_template->instances[i];

		actor_instance->flags |= ztPlatformerActorInstanceFlags_Enabled | ztPlatformerActorInstanceFlags_Alive;
		actor_instance->position = pos;
		actor_instance->user_flags = 0;
		actor_instance->user_id = i;

		instance->direction = direction < 0 ? -1 : 1;
		instance->animation = anim_controller;

		zt_fjz(level->colliders_used) {
			if (&level->colliders[j] == surface_walking_on) {
				instance->surface_idx = j;
				break;
			}
		}

		return actor_instance;
	}

	return nullptr;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_platformerCharacterControllerUpdate(ztPlatformerLevel *level, ztPlatformerCharacterControllerSettings *settings, ztPlatformerPhysicsObject *character, r32 dt)
{
	bool reset_jump = character->collider_resting_on != nullptr;

	zt_flink(collision, character->collisions) {
		if (collision->normal.dot(zt_vec2(0, 1)) > .25f) {
			reset_jump = true;

			if (collision->collider->type == ztPlatformerColliderType_Spring) {
				settings->_internal.time_since_spring = 0;
				settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_WasOnSpring;
			}
		}
		else {
			if (settings->_internal.outside_force != ztVec2::zero && collision->normal.dot(settings->_internal.outside_force) < 0) {
				settings->_internal.outside_force = ztVec2::zero;
				settings->_internal.outside_force_time_max = 0;
			}

			if (collision->collider->type == ztPlatformerColliderType_Surface && !zt_between(collision->normal.dot(zt_vec2(1, 0)), -.5f, .5f)) {
				settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_AgainstWall;
				i32 wall_collider = zt_platformerGetColliderIndex(level, collision->collider);
				if (wall_collider != settings->_internal.wall_collider) {
					settings->_internal.wall_collider = wall_collider;
					settings->_internal.wall_cling_time = 0;
				
					ztVec2 p0, p1, n;
					zt_platformerGetColliderPositions(level, &level->colliders[settings->_internal.wall_collider], &p0, &p1, &n);
					ztVec2 closest = zt_closestPointLineSegmentPoint(p0, p1, character->position);
				
					settings->_internal.wall_collider_dist = closest.distance(character->position);
				}
			}
		}
	}

	if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AgainstWall) && settings->_internal.wall_collider >= 0) {
		if (settings->_internal.wall_cling_time != 0) {
			ztVec2 p0, p1, n;
			zt_platformerGetColliderPositions(level, &level->colliders[settings->_internal.wall_collider], &p0, &p1, &n);

			ztVec2 closest = zt_closestPointLineSegmentPoint(p0, p1, character->position);
			r32 dist = closest.distance(character->position);

			if (zt_abs(dist - settings->_internal.wall_collider_dist) > settings->wall_cling_max_dist) {
				zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AgainstWall);
				settings->_internal.wall_collider = -1;
			}

			if (character->velocity.y < 0) {
				character->velocity.y = zt_max(character->velocity.y, settings->wall_slide_max_velocity);
			}
		}
		if (reset_jump) {
			zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AgainstWall);
			settings->_internal.wall_collider = -1;
		}
		else if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_WallJump)) {
			//reset_jump = true;
		}
		settings->_internal.wall_cling_time += dt;
	}

	if (settings->_internal.outside_force != ztVec2::zero) {
		if (settings->_internal.outside_force_time_max != 0) {
			character->velocity -= ztVec2::lerp(ztVec2::zero, settings->_internal.outside_force, settings->_internal.outside_force_time / settings->_internal.outside_force_time_max);
		}
		else {
			character->velocity -= settings->_internal.outside_force;
		}
	}

	if (reset_jump) {
		settings->_internal.jumps = 0;
		zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InJump);
		zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InHalfJump);
		settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_AtRest;
	}

	if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InJump)) {
		settings->_internal.jump_time += dt;
		settings->_internal.wall_jump_movement_time -= dt;

		if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_FixedJumpHalfHeight)) {
			if (settings->_internal.jumps == 1 && !settings->input.jump_held && !zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InHalfJump)) {
				if (settings->_internal.jump_time - dt < settings->jump_time_full_threshold && settings->_internal.jump_time >= settings->jump_time_full_threshold) {
					settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_InHalfJump;
				}
			}

			if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InHalfJump) && character->velocity.y > 0) {
				character->velocity.y = zt_approach(character->velocity.y, 0, settings->jump_half_slowdown_velocity * dt);
			}
		}
	}
	else {
		settings->_internal.jump_time = 0;
		settings->_internal.wall_jump_movement_time = 0;
	}

	if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_WasOnSpring)) {
		settings->_internal.time_since_spring += dt;
		if (settings->_internal.time_since_spring > settings->spring_time_forgiveness) {
			zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_WasOnSpring);
		}
	}

	if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AtRest)) {
		if (character->collider_resting_on == nullptr) {
			settings->_internal.fall_time += dt;
			if (settings->_internal.fall_time > settings->jump_forgiveness) {
				zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AtRest);
			}
		}
		else {
			settings->_internal.fall_time = 0;
		}
	}
	else if (character->collider_resting_on) {
		settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_AtRest;
	}

	if (settings->input.jump) {
		settings->input.jump = false;

		if (settings->_internal.jumps < ZT_PLATFORMER_CHARACTER_CONTROLLER_MAX_JUMPS) {

			bool can_jump = true;
			bool jumping_in_fall = false;
			if (settings->_internal.jumps != 0) {
				can_jump = false;
				if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InJump)) {
					if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_AllowMultiJump)) {
						can_jump = true;
					}
				}
				if (!can_jump && zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AgainstWall) && zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_WallJump)) {
					can_jump = true;
					settings->_internal.jumps -= 1;
				}
			}
			else if (!zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AtRest)) {
				if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_AllowMultiJumpInFall)) {
					jumping_in_fall = true;
				}
				else if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_WallJump) && zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AgainstWall)) {
					jumping_in_fall = true;
				}
				else {
					can_jump = false;
					if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_WasOnSpring) && settings->_internal.time_since_spring <= settings->spring_time_forgiveness) {
						can_jump = true;
					}
				}
			}

			if (can_jump) {
				if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_WallJump) && zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AgainstWall)) {
					r32 jump_multiplier = 1;
					int jump_idx = settings->_internal.jumps++;

					ztVec2 wall_jump_velocity = settings->wall_jump_velocity;
					if (wall_jump_velocity == ztVec2::zero) {
						wall_jump_velocity = zt_vec2(settings->jump_velocities[0] * .35f, settings->jump_velocities[0] * 1.f);
					}

					settings->_internal.wall_jump_movement_time = settings->wall_jump_movement_pause;

					ztVec2 p0, p1, n;
					zt_platformerGetColliderPositions(level, &level->colliders[settings->_internal.wall_collider], &p0, &p1, &n);
					if (p0.x > character->position.x) {
						wall_jump_velocity.x *= -1;
					}

					//character->velocity = zt_vec2(0, wall_jump_velocity.y);
					//settings->_internal.outside_force = zt_vec2(wall_jump_velocity.x, 0);
					//settings->_internal.outside_force_time = settings->_internal.outside_force_time_max = .25f;
					character->velocity = wall_jump_velocity;
				}
				else {
					r32 jump_multiplier = 1;
					if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_WasOnSpring)) {
						if (settings->_internal.time_since_spring <= settings->spring_time_forgiveness) {
							zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_WasOnSpring);
							jump_multiplier *= settings->spring_jump_multiplier;
							zt_logDebug("multiplying");
						}
					}

					int jump_idx = settings->_internal.jumps++;

					if (jumping_in_fall) {
						jump_idx = settings->_internal.jumps++;
					}
					if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_FixedJumpHeight)) {
						if (jump_idx > 0) {
							character->velocity.y = settings->jump_velocities[jump_idx] * jump_multiplier;
							zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InHalfJump);
						}
						else {
							if (character->velocity.y < 0) {
								character->velocity.y = 0;
							}
							character->velocity.y += settings->jump_velocities[jump_idx] * jump_multiplier;
							if (jump_idx == 0) {
								settings->_internal.jump_time = 0;
							}
						}
					}
					else {
						settings->_internal.jump_time = dt;
						character->velocity.y = -level->gravity;
						zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_JumpReleased);
					}
				}

				settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_InJump;
				zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_AtRest);
			}
		}
	}
	
	if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InJump) && !zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_FixedJumpHeight)) {
		if (settings->input.jump_held && !zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_JumpReleased)) {
			if (settings->_internal.jump_time >= settings->jump_times[settings->_internal.jumps - 1]) {
				settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_JumpReleased;
			}
			else {
				//character->velocity.y = zt_approach(character->velocity.y, settings->jump_velocities[settings->_internal.jumps - 1], level->gravity * dt * 4);
				character->velocity.y += settings->jump_velocities[settings->_internal.jumps - 1] / settings->jump_times[settings->_internal.jumps - 1] * dt * .2f;
			}
		}
		else {
			settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_JumpReleased;

			if (character->velocity.y > 0) {
				character->velocity.y = zt_approach(character->velocity.y, 0, level->gravity * dt * 4);
			}
		}
	}

	if (settings->input.x_axis != 0) {
		bool apply_movement = true;

		if (settings->_internal.wall_jump_movement_time > 0) {
			apply_movement = false;
		}

		if (apply_movement) {
			settings->_internal.last_side_direction = settings->input.x_axis < 0 ? -1 : 1;

			r32 side_accel = settings->input.run ? settings->side_run_accel : settings->side_walk_accel;
			r32 side_max_vel = settings->input.run ? settings->side_run_max_vel : settings->side_walk_max_vel;

			if (zt_bitIsSet(settings->flags, ztPlatformerCharacterControllerFlags_ChangeDirectionInstantly) && settings->_internal.outside_force == ztVec2::zero) {
				if (settings->input.x_axis < 0 && character->velocity.x > 0 && settings->_internal.wall_jump_movement_time <= 0) { character->velocity.x = 0; settings->_internal.run_time = 0; }
				if (settings->input.x_axis > 0 && character->velocity.x < 0 && settings->_internal.wall_jump_movement_time <= 0) { character->velocity.x = 0; settings->_internal.run_time = 0; }
			}

			ztVec2 dir = zt_vec2(settings->input.x_axis < 0 ? -1.f : 1.f, 0);

			if (character->collider_resting_on != nullptr) {
				ztVec2 p0, p1, n;
				zt_platformerGetColliderPositions(level, character->collider_resting_on, &p0, &p1, &n);

				r32 cross = n.cross(dir);
				r32 cross_angle = zt_radiansToDegrees(cross);

				if (!zt_real32Eq(cross, 0)) {
					if (settings->input.x_axis < 0) {
						n = ztQuat::makeFromEuler(0, 0, 90).rotatePosition(zt_vec3(n, 0)).xy;
					}
					else {
						n = ztQuat::makeFromEuler(0, 0, -90).rotatePosition(zt_vec3(n, 0)).xy;
					}

					dir = n;
					character->position += ((dir * zt_lerp(0, side_max_vel, zt_linearRemapAndClamp(settings->_internal.run_time, 0, .125f, .25f, 1))) + settings->_internal.outside_force) * dt;
					dir = ztVec2::zero;
				}
			}

			character->velocity += dir * zt_abs(settings->input.x_axis) * side_accel;
			character->velocity.x = zt_clamp(character->velocity.x, -side_max_vel, side_max_vel);
			settings->_internal.state_flags |= ztPlatformerCharacterControllerInternalFlags_InMove;
			//settings->input.x_axis = 0;
		}

		settings->_internal.run_time += dt;
	}
	else {
		if (zt_bitIsSet(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InMove) || character->collider_resting_on != nullptr) {
			character->velocity.x = zt_approach(character->velocity.x, 0, settings->side_decel * dt);
		}
		else {
			character->velocity.x = zt_approach(character->velocity.x, 0, settings->side_decel * dt * .1f);
		}
		if (zt_real32Eq(character->velocity.x, 0)) {
			zt_bitRemove(settings->_internal.state_flags, ztPlatformerCharacterControllerInternalFlags_InMove);
		}

		settings->_internal.run_time = 0;
	}

	if (settings->_internal.outside_force != ztVec2::zero) {
		if (settings->_internal.outside_force_time_max != 0) {
			settings->_internal.outside_force_time -= dt;
			if (settings->_internal.outside_force_time < 0) {
				settings->_internal.outside_force_time = settings->_internal.outside_force_time_max = 0;
				settings->_internal.outside_force = ztVec2::zero;
			}
			else {
				character->velocity += ztVec2::lerp(ztVec2::zero, settings->_internal.outside_force, settings->_internal.outside_force_time / settings->_internal.outside_force_time_max);
			}
		}
		else {
			character->velocity += settings->_internal.outside_force;
			//character->position += settings->_internal.outside_force * dt;
			settings->_internal.outside_force = zt_vec2(zt_approach(settings->_internal.outside_force.x, 0, character->collider_resting_on != nullptr ? settings->side_decel * dt : level->gravity * dt), zt_approach(settings->_internal.outside_force.y, 0, level->gravity * dt));
		}
	}

	character->flags |= ztPlatformerPhysicsObjectFlags_Kinematic;
}

// ================================================================================================================================================================================================

void zt_platformerCharacterControllerSetupPreset1(ztPlatformerLevel *level, ztPlatformerCharacterControllerSettings *settings, ztPlatformerPhysicsObject *character)
{
	zt_memSet(settings, zt_sizeof(ztPlatformerCharacterControllerSettings), 0);

	character->velocity          = zt_vec2(0, 0);
	character->velocity_transfer = 0;
	character->flags             = ztPlatformerPhysicsObjectFlags_Kinematic;
	character->mass              = 2;

	settings->flags                         = ztPlatformerCharacterControllerFlags_FixedJumpHeight | ztPlatformerCharacterControllerFlags_FixedJumpHalfHeight | ztPlatformerCharacterControllerFlags_ChangeDirectionInstantly;
	settings->jump_velocities[0]            = 17;
	settings->jump_times     [0]            = .2f;
	settings->jump_half_slowdown_velocity   = 150;
	settings->jump_forgiveness              = .05f;
	settings->spring_time_forgiveness       = .15f;
	settings->spring_jump_multiplier        = .5f;
	settings->jump_time_full_threshold      = .1f;
	settings->side_walk_accel               = .125f;
	settings->side_walk_max_vel             = 6;
	settings->side_run_accel                = .085f;
	settings->side_run_max_vel              = 15;
	settings->side_decel                    = 100;
	settings->_internal.last_side_direction = 1;

	//level->gravity = -12.5f;
	//level->terminal_velocity = -6.75f;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_platformerLevelEditorTile(ztPlatformerLevelEditorTile *tile, const char *name, ztSprite *sprite, r32 rotation, u32 hash)
{
	zt_strCpy(tile->name, zt_elementsOf(tile->name), name);
	
	if (sprite) {
		tile->sprite = *sprite;
	}

	tile->rotation = rotation;
	tile->hash = hash;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_platformerLevelEditorMarker(ztPlatformerLevelEditorMarker *marker, const char *name, i32 value, char *info, ztVec2 area_center, ztVec2 area_size, ztSprite *sprite, ztVec2 sprite_offset, ztVec2 sprite_scale)
{
	zt_strCpy(marker->name, zt_elementsOf(marker->name), name);
	zt_strCpy(marker->info, zt_elementsOf(marker->info), info);

	marker->value = value;

	marker->area_center = area_center;
	marker->area_size = area_size;
	marker->sprite = sprite;
	marker->sprite_offset = sprite_offset;
	marker->sprite_scale = sprite_scale;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal ztPlatformerLevelEditorAction* _zt_platformerLevelEditorGetAvailableAction(ztPlatformerLevelEditor *editor, i32 *idx = nullptr)
{
	bool first_action = editor->actions_current == -1;
	editor->actions_current = (editor->actions_current + 1) % editor->actions_size;

	if (!first_action && editor->actions_current == editor->actions_first) {
		editor->actions_first = (editor->actions_first + 1) % editor->actions_size;
	}

	editor->actions_last = editor->actions_current;

	if (idx) *idx = editor->actions_current;

	editor->actions[editor->actions_current].time = zt_getTime();
	editor->actions[editor->actions_current].group = editor->actions_group++;

	//zt_logDebug("new action (%d) first: %d; last: %d", editor->actions_current, editor->actions_first, editor->actions_last);

	return &editor->actions[editor->actions_current];
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorDoAction(ztPlatformerLevelEditor *editor, ztPlatformerLevelEditorAction *action, bool quadtree_recalc)
{
	switch (action->type)
	{
		case ztPlatformerLevelEditorActionType_NewCollider: {
			zt_assertReturnOnFail(editor->level->colliders_used < editor->level->colliders_size);
			action->new_collider.collider_idx = editor->level->colliders_used;
			zt_memCpy(&editor->level->colliders[editor->level->colliders_used++], zt_sizeof(ztPlatformerCollider), &action->new_collider.collider, zt_sizeof(ztPlatformerCollider));
		} break;

		case ztPlatformerLevelEditorActionType_EditCollider: {
			i32 idx = action->edit_collider.collider_idx;
			zt_assertReturnOnFail(idx >= 0 && idx < editor->level->colliders_used);
			zt_memCpy(&editor->level->colliders[idx], zt_sizeof(ztPlatformerCollider), &action->edit_collider.collider_after, zt_sizeof(ztPlatformerCollider));
		} break;

		case ztPlatformerLevelEditorActionType_DeleteCollider: {
			i32 idx = action->edit_collider.collider_idx;
			if (idx == editor->level->colliders_used - 1) {
				editor->level->colliders_used -= 1;
			}
			else {
				for (int i = idx; i < editor->level->colliders_used - 1; ++i) {
					zt_memCpy(&editor->level->colliders[i], zt_sizeof(ztPlatformerCollider), &editor->level->colliders[i + 1], zt_sizeof(ztPlatformerCollider));
				}
				editor->level->colliders_used -= 1;
			}
		} break;
	}

	if (quadtree_recalc) {
		zt_platformerRecalcQuadTree(editor->level);
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorUndoAction(ztPlatformerLevelEditor *editor, ztPlatformerLevelEditorAction *action, bool quadtree_recalc)
{
	switch (action->type)
	{
		case ztPlatformerLevelEditorActionType_NewCollider: {
			i32 idx = action->new_collider.collider_idx;
			zt_assertReturnOnFail(idx >= 0 && idx < editor->level->colliders_used);

			if (idx == editor->level->colliders_used - 1) {
				editor->level->colliders_used -= 1;
			}
			else {
				for (int i = idx; i < editor->level->colliders_used - 1; ++i) {
					zt_memCpy(&editor->level->colliders[i], zt_sizeof(ztPlatformerCollider), &editor->level->colliders[i + 1], zt_sizeof(ztPlatformerCollider));
				}
				editor->level->colliders_used -= 1;
			}
		} break;

		case ztPlatformerLevelEditorActionType_EditCollider: {
			i32 idx = action->edit_collider.collider_idx;
			zt_assertReturnOnFail(idx >= 0 && idx < editor->level->colliders_used);
			zt_memCpy(&editor->level->colliders[idx], zt_sizeof(ztPlatformerCollider), &action->edit_collider.collider_before, zt_sizeof(ztPlatformerCollider));
		} break;

		case ztPlatformerLevelEditorActionType_DeleteCollider: {
			zt_assertReturnOnFail(editor->level->colliders_used < editor->level->colliders_size);
			i32 idx = action->delete_collider.collider_idx;
			for (int i = editor->level->colliders_used; i > idx; --i) {
				zt_memCpy(&editor->level->colliders[i], zt_sizeof(ztPlatformerCollider), &editor->level->colliders[i - 1], zt_sizeof(ztPlatformerCollider));
			}
			zt_memCpy(&editor->level->colliders[idx], zt_sizeof(ztPlatformerCollider), &action->delete_collider.collider, zt_sizeof(ztPlatformerCollider));
			editor->level->colliders_used += 1;
		} break;
	}

	if (quadtree_recalc) {
		zt_platformerRecalcQuadTree(editor->level);
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorAddCollider(ztPlatformerLevelEditor *editor, ztPlatformerCollider *collider, bool execute = true, ztPlatformerLevelEditorAction *action = nullptr)
{
	if (action == nullptr) {
		action = _zt_platformerLevelEditorGetAvailableAction(editor);
	}

	action->type = ztPlatformerLevelEditorActionType_NewCollider;
	action->new_collider.collider_idx = -1;
	zt_memCpy(&action->new_collider.collider, zt_sizeof(ztPlatformerCollider), collider, zt_sizeof(ztPlatformerCollider));

	if (execute) {
		_zt_platformerLevelEditorDoAction(editor, action, true);
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorEditCollider(ztPlatformerLevelEditor *editor, i32 collider_idx, ztPlatformerCollider *collider_before, ztPlatformerCollider *collider_after, bool recalc_quadtree)
{
	ztPlatformerLevelEditorAction *action = _zt_platformerLevelEditorGetAvailableAction(editor);

	action->type = ztPlatformerLevelEditorActionType_EditCollider;
	action->edit_collider.collider_idx = collider_idx;
	zt_memCpy(&action->edit_collider.collider_before, zt_sizeof(ztPlatformerCollider), collider_before, zt_sizeof(ztPlatformerCollider));
	zt_memCpy(&action->edit_collider.collider_after, zt_sizeof(ztPlatformerCollider), collider_after, zt_sizeof(ztPlatformerCollider));
	_zt_platformerLevelEditorDoAction(editor, action, recalc_quadtree);
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorDeleteCollider(ztPlatformerLevelEditor *editor, i32 collider_idx, ztPlatformerCollider *collider)
{
	ztPlatformerLevelEditorAction *action = _zt_platformerLevelEditorGetAvailableAction(editor);

	action->type = ztPlatformerLevelEditorActionType_DeleteCollider;
	action->delete_collider.collider_idx = collider_idx;
	zt_memCpy(&action->delete_collider.collider, zt_sizeof(ztPlatformerCollider), collider, zt_sizeof(ztPlatformerCollider));
	_zt_platformerLevelEditorDoAction(editor, action, false);
}

// ================================================================================================================================================================================================

ztInternal bool _zt_platformerLevelEditorCommandBufferForward(ztPlatformerLevelEditor *editor)
{
	if (editor->actions_current >= editor->actions_last) {
		zt_assertReturnValOnFail(editor->actions_current == editor->actions_last, false); // if we're bigger, there's a problem
		return false;
	}

	while (true) {
		ztPlatformerLevelEditorAction *action = &editor->actions[++editor->actions_current];
		_zt_platformerLevelEditorDoAction(editor, action, false);

		if (editor->actions_current >= editor->actions_last) {
			break;
		}

		if (editor->actions[editor->actions_current + 1].group != action->group) {
			break;
		}
	}

	if (editor->active_collider >= 0) {
		zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
		zt_guiTextEditSetValue(editor->gui_active_item_name_edit, editor->active_collider_copy.name);
	}

	zt_platformerRecalcQuadTree(editor->level);

	return true;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_platformerLevelEditorCommandBufferBackward(ztPlatformerLevelEditor *editor)
{
	if (editor->actions_current < editor->actions_first) {
		return false;
	}

	i32 group = -1;

	while (true) {
		ztPlatformerLevelEditorAction *action = &editor->actions[editor->actions_current--];
		_zt_platformerLevelEditorUndoAction(editor, action, false);

		if (editor->actions_current < editor->actions_first) {
			break;
		}

		if (editor->actions[editor->actions_current].group != action->group) {
			break;
		}
	}

	if (editor->active_collider >= 0) {
		zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
		zt_guiTextEditSetValue(editor->gui_active_item_name_edit, editor->active_collider_copy.name);
	}

	zt_platformerRecalcQuadTree(editor->level);

	return true;
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorCreateGuiForCollider(ztPlatformerLevelEditor *editor, ztPlatformerCollider *collider);

ztInternal void _zt_platformerLevelEditorSelectCollider(ztPlatformerLevelEditor *editor, i32 collider_idx)
{
	editor->active_collider = collider_idx;
	editor->active_collider_point = -1;

	zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[collider_idx], zt_sizeof(ztPlatformerCollider));
	_zt_platformerLevelEditorCreateGuiForCollider(editor, &editor->level->colliders[collider_idx]);
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorClearSelection(ztPlatformerLevelEditor *editor)
{
	if (editor->gui_active_item != nullptr) {
		zt_guiItemFree(editor->gui_active_item);
		editor->gui_active_item = nullptr;
	}

	editor->active_collider = -1;
	editor->active_collider_point = -1;

	editor->selection_count = 0;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_platformerLevelEditorIsSelected(ztPlatformerLevelEditor *editor, i32 collider_idx)
{
	if (collider_idx < 0 || collider_idx > editor->level->colliders_used) {
		return false;
	}

	if (editor->active_collider == collider_idx) {
		return true;
	}

	zt_fiz(editor->selection_count) {
		if (editor->selection[i] == collider_idx) {
			return true;
		}
	}

	return false;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorTileSelect, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorTileSelect))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;
	ztPlatformerLevelEditorTile *tile = (ztPlatformerLevelEditorTile*)zt_guiItemGetUserData(button);

	if (zt_guiListBoxGetSelected(editor->gui_layers_list) >= editor->level->layers_size) {
		zt_guiDialogMessageBoxOk("Invalid Layer", "Sprites cannot be added to the collider layer", ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	editor->mouse_state = ztPlatformerLevelEditorMouseState_Tile;
	editor->mouse_tile = tile;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonLoadFileSelected, ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_platformerLevelEditorButtonLoadFileSelected))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	if (!zt_fileExists(path)) {
		zt_guiDialogMessageBoxOk("File Does Not Exist", "This file does not exist.", ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	zt_strCpy(editor->file_name, zt_elementsOf(editor->file_name), path);

	_zt_platformerLevelEditorClearSelection(editor);
	zt_platformerLevelLoad(editor->level, editor->sprite_manager, editor->file_name);

	zt_guiGradientPickerSetLiveValue(editor->gui_background_color_gradient, &editor->level->background_color);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonLoad, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorButtonLoad))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;
	zt_guiDialogFileSelect("Select Level File To Load", ztGuiDialogFileSelectFlags_Open, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonLoadFileSelected), editor, editor->levels_path);

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonNew, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorButtonNew))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	_zt_platformerLevelEditorClearSelection(editor);

	editor->level->name[0] = 0;
	editor->level->colliders_used = 0;
	editor->level->collisions_used = 0;
	editor->file_name[0] = editor->file_name_working[0] = 0;
	
	zt_platformerAppendCollider(editor->level, zt_vec2(-10, -5), zt_vec2(10, -5)); // bottom
	zt_platformerAppendCollider(editor->level, zt_vec2(10, 5), zt_vec2(-10, 5)); // top
	zt_platformerAppendCollider(editor->level, zt_vec2(-10, 5), zt_vec2(-10, -5)); // left
	zt_platformerAppendCollider(editor->level, zt_vec2(10, -5), zt_vec2(10, 5)); // right


	zt_platformerRecalcQuadTree(editor->level);
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorSave(ztPlatformerLevelEditor *editor)
{
	zt_platformerLevelSave(editor->level, editor->file_name);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonSaveAsFileSelectedConfirmOverwrite, ZT_FUNC_GUI_DIALOG_MESSAGE_CLOSED(_zt_platformerLevelEditorButtonSaveAsFileSelectedConfirmOverwrite))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	switch (option->id)
	{
		case 0: { // yes
			zt_strCpy(editor->file_name, zt_elementsOf(editor->file_name), editor->file_name_working);
			_zt_platformerLevelEditorSave(editor);
		} break;

		case 1: { // no
		} break;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonSaveAsFileSelected, ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_platformerLevelEditorButtonSaveAsFileSelected))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	if (zt_fileExists(path)) {
		zt_strCpy(editor->file_name_working, zt_elementsOf(editor->file_name_working), path);
		zt_guiDialogMessageBoxYesNo("File Already Exists", "Overwrite existing file?", ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonSaveAsFileSelectedConfirmOverwrite), editor);
		return;
	}

	zt_strCpy(editor->file_name, zt_elementsOf(editor->file_name), path);
	_zt_platformerLevelEditorSave(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonSaveAs, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorButtonSaveAs))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;
	zt_guiDialogFileSelect("Select Level File To Save", ztGuiDialogFileSelectFlags_Save, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonSaveAsFileSelected), editor, editor->levels_path);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonSave, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorButtonSave))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	if (editor->file_name[0] == 0) {
		_zt_platformerLevelEditorButtonSaveAs(button, user_data);
		return;
	}

	_zt_platformerLevelEditorSave(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonNewItem, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorButtonNewItem))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	if (zt_guiListBoxGetSelected(editor->gui_layers_list) >= editor->level->layers_size) {
		zt_guiMenuPopupAtItem(editor->gui_right_click_menu_colliders, button, ztAlign_Left | ztAlign_Bottom);
	}
	else {
		zt_guiMenuPopupAtItem(editor->gui_right_click_menu, button, ztAlign_Left | ztAlign_Bottom);
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorBlueprintSelect, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorBlueprintSelect))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;
	ztPlatformerLevelEditorBlueprint *blueprint = (ztPlatformerLevelEditorBlueprint*)zt_guiItemGetUserData(button);

	editor->mouse_blueprint = blueprint;
	editor->mouse_state = ztPlatformerLevelEditorMouseState_Blueprint;
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorBlueprintUpdate(ztPlatformerLevelEditor *editor)
{
	if (editor->gui_blueprints == nullptr) {
		return;
	}

	while (editor->gui_blueprints_sizer->first_child) {
		zt_guiItemFree(editor->gui_blueprints_sizer->first_child);
	}

	r32 padding = 3 / zt_pixelsPerUnit();

	zt_flink(blueprint, editor->blueprints) {
		ztGuiItem *button = zt_guiMakeButton(editor->gui_blueprints_sizer, blueprint->name);
		zt_guiSizerAddItem(editor->gui_blueprints_sizer, button, 0, padding);

		zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorBlueprintSelect), editor);
		zt_guiItemSetUserData(button, blueprint);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorBlueprintName, ZT_FUNC_GUI_DIALOG_GET_USER_TEXT(_zt_platformerLevelEditorBlueprintName))
{
	if (cancelled || zt_strLen(value) <= 0) {
		return;
	}

	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	ztPlatformerLevelEditorBlueprint *blueprint = zt_mallocStruct(ztPlatformerLevelEditorBlueprint);

	zt_strCpy(blueprint->name, zt_elementsOf(blueprint->name), value);

	blueprint->actions = zt_mallocStructArray(ztPlatformerLevelEditorAction, editor->selection_count);

	ztVec2 max = ztVec2::min, min = ztVec2::max;

	zt_fiz(editor->selection_count) {
		ztVec2 smin, smax;
		_zt_platformerGetExtents(editor->level, &editor->level->colliders[editor->selection[i]], &smin, &smax, true);

		min.x = zt_min(min.x, smin.x);
		min.y = zt_min(min.y, smin.y);
		max.x = zt_max(max.x, smax.x);
		max.y = zt_max(max.y, smax.y);
	}

	ztVec2 ctr = (min + max) * .5f;
	ztVec2 ext = max - min;

	zt_fiz(editor->selection_count) {
		ztPlatformerCollider collider;
		zt_memCpy(&collider, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->selection[i]], zt_sizeof(ztPlatformerCollider));

		collider.points[0] -= ctr;
		collider.points[1] -= ctr;

		_zt_platformerLevelEditorAddCollider(editor, &collider, false, &blueprint->actions[i]);
		blueprint->actions[blueprint->actions_size++].group = -1;
	}

	blueprint->size = ext;

	zt_singleLinkAddToEnd(editor->blueprints, blueprint);

	_zt_platformerLevelEditorBlueprintUpdate(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorButtonNewBlueprint, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_platformerLevelEditorButtonNewBlueprint))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;
	zt_guiDialogGetUserText("Blueprint Name", "Name this blueprint:", "", true, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorBlueprintName), editor);
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLeveleditorMakeToolsWindow(ztPlatformerLevelEditor *editor)
{
	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window = zt_guiMakeWindow("Tools", ztGuiWindowBehaviorFlags_AllowCollapse | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_ShowTitle);
	editor->gui_tools = window;

	ztGuiItem *window_sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	// make options
	{
		ztGuiItem *btn_sizer = zt_guiMakeSizer(window_sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(window_sizer, btn_sizer, 0, 0);

		ztGuiItem *btn_load = zt_guiMakeButton(btn_sizer, "Load");
		zt_guiSizerAddItem(btn_sizer, btn_load, 1, padding);
		zt_guiButtonSetCallback(btn_load, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonLoad), editor);

		ztGuiItem *btn_new = zt_guiMakeButton(btn_sizer, "New");
		zt_guiSizerAddItem(btn_sizer, btn_new, 1, padding);
		zt_guiButtonSetCallback(btn_new, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonNew), editor);

		ztGuiItem *btn_save = zt_guiMakeButton(btn_sizer, "Save");
		zt_guiSizerAddItem(btn_sizer, btn_save, 1, padding);
		zt_guiButtonSetCallback(btn_save, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonSave), editor);

		ztGuiItem *btn_saveas = zt_guiMakeButton(btn_sizer, "Save As");
		zt_guiSizerAddItem(btn_sizer, btn_saveas, 1, padding);
		zt_guiButtonSetCallback(btn_saveas, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonSaveAs), editor);

		ztGuiItem *collapsing_panel = zt_guiMakeCollapsingPanel(window_sizer, "Options");
		zt_guiSizerAddItem(window_sizer, collapsing_panel, 0, 0);

		ztGuiItem *sizer = zt_guiMakeColumnSizer(zt_guiCollapsingPanelGetContentParent(collapsing_panel), 2, ztGuiColumnSizerType_FillRow);
		zt_guiSizerSizeToParent(sizer, false);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer, true);

		zt_guiColumnSizerSetProp(sizer, 1, 1);
		//zt_guiSizerAddItem(window_sizer, sizer, 0, padding);
		
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Level Name:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *level_name = zt_guiMakeTextEdit(sizer, "", 0, zt_elementsOf(editor->level->name) + 1);
		zt_guiSizerAddItem(sizer, level_name, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Gravity:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *gravity = zt_guiMakeEditor(sizer, nullptr, &editor->level->gravity, ztReal32Min, ztReal32Max, .25f);
		zt_guiSizerAddItem(sizer, gravity, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Terminal Velocity:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *terminal_vel = zt_guiMakeEditor(sizer, nullptr, &editor->level->terminal_velocity, ztReal32Min, ztReal32Max, .25f);
		zt_guiSizerAddItem(sizer, terminal_vel, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Air Friction Multiplier:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *air_friction = zt_guiMakeEditor(sizer, nullptr, &editor->level->air_friction_multiplier, ztReal32Min, ztReal32Max, .25f);
		zt_guiSizerAddItem(sizer, air_friction, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Background Color:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *background_color = zt_guiMakeGradientPicker(sizer, &editor->level->background_color, ztGuiGradientPickerBehaviorFlags_LiveEdit, &editor->level->background_color);
		zt_guiSizerAddItem(sizer, background_color, 1, padding);
		editor->gui_background_color_gradient = background_color;

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Background Rotation:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *background_rotation = zt_guiMakeEditor(sizer, nullptr, &editor->level->background_rotation, 0.f, 360.f, 5.f);
		zt_guiSizerAddItem(sizer, background_rotation, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Draw Grid:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *check_grid = zt_guiMakeCheckbox(sizer, nullptr, ztGuiCheckboxBehaviorFlags_RightText, &editor->opts_draw_grid);
		zt_guiSizerAddItem(sizer, check_grid, 1, padding, ztAlign_Left | ztAlign_VertCenter, 0);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Snap Points:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *check_snap = zt_guiMakeCheckbox(sizer, nullptr, ztGuiCheckboxBehaviorFlags_RightText, &editor->opts_snap_points);
		zt_guiSizerAddItem(sizer, check_snap, 1, padding, ztAlign_Left | ztAlign_VertCenter, 0);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Snap Increment:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *edit_snap = zt_guiMakeEditor(sizer, nullptr, &editor->opts_snap_increment, 0.f, ztReal32Max, .125f);
		zt_guiSizerAddItem(sizer, edit_snap, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Item Count:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		ztGuiItem *items_count = zt_guiMakeStaticText(sizer, "000000/000000", ztGuiStaticTextBehaviorFlags_Fancy);
		zt_guiItemSetAlign(items_count, ztAlign_Right);
		zt_guiSizerAddItem(sizer, items_count, 0, padding);
		editor->gui_items_count = items_count;
	}

	ztGuiItem *splitter_1 = zt_guiMakeSplitter(window_sizer, ztGuiItemOrient_Vert, .25f);
	zt_guiSizerAddItem(window_sizer, splitter_1, 1, padding);

	// make layers
	{
		ztGuiItem *sizer = zt_guiMakeSizer(splitter_1, ztGuiItemOrient_Vert, false);
		zt_guiSplitterSetFirstItem(splitter_1, sizer);

		ztGuiItem *label_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, label_sizer, 0, 0);

		ztGuiItem *label = zt_guiMakeStaticText(sizer, "Layers: ");
		zt_guiItemSetAlign(label, ztAlign_Left);
		zt_guiSizerAddItem(label_sizer, label, 1, padding);

		ztGuiItem *button = zt_guiMakeButton(sizer, "New Item");
		button->size.y = label->size.y + padding * 4;
		zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonNewItem), editor);
		zt_guiSizerAddItem(label_sizer, button, 0, padding);

		ztGuiItem *listbox = zt_guiMakeListBox(splitter_1, ztGuiListBoxBehaviorFlags_AlternateRowColor, editor->level->layers_size + 1);
		zt_guiSizerAddItem(sizer, listbox, 1, padding);
		editor->gui_layers_list = listbox;

		zt_fiz(editor->level->layers_size + 1) {
			ztGuiItem *lbitem = zt_guiMakePanel(listbox);
			ztGuiItem *lbsizer = zt_guiMakeSizer(lbitem, ztGuiItemOrient_Horz, false);
			zt_guiSizerSizeParent(lbsizer);
			zt_guiSizerSizeToParent(lbsizer);

			ztGuiItem *button_show = zt_guiMakeToggleButton(lbsizer, "Show", 0, &editor->layer_show[i]);
			zt_guiSizerAddItem(lbsizer, button_show, 0, padding);
			zt_guiToggleButtonSetValue(button_show, true);

			//ztGuiItem *button_lock = zt_guiMakeToggleButton(lbsizer, "Lock", 0, &editor->layer_lock[i]);
			//zt_guiSizerAddItem(lbsizer, button_lock, 0, padding);
			//zt_guiToggleButtonSetValue(button_lock, true);
			//
			//button_show->size.x = button_lock->size.x = .65f;
			//button_show->size.y = button_lock->size.y = .4f;
			button_show->size.x = .65f;
			button_show->size.y = .4f;

			zt_guiSizerAddStretcher(lbsizer, 0, padding * 2);

			ztGuiItem *label = zt_guiMakeStaticText(lbsizer, i == editor->level->layers_size ? "<color=ffaaaa>Colliders</color>" : editor->level->layers[i].name, ztGuiStaticTextBehaviorFlags_Fancy);
			label->size.x = 2.55f;
			zt_guiItemSetAlign(label, ztAlign_Left);
			zt_guiSizerAddItem(lbsizer, label, 1, padding);

			zt_guiListBoxAppend(listbox, lbitem, editor, true);
		}
		zt_guiListBoxSetSelected(listbox, 0, false, false);
	}

	ztGuiItem *splitter_2 = zt_guiMakeSplitter(splitter_1, ztGuiItemOrient_Vert, .75f);
	zt_guiSplitterSetSecondItem(splitter_1, splitter_2);

	// make tiles
	{
		ztGuiItem *sizer = zt_guiMakeSizer(splitter_1, ztGuiItemOrient_Vert, false);
		zt_guiSplitterSetFirstItem(splitter_2, sizer);

		ztGuiItem *label = zt_guiMakeStaticText(sizer, "Tiles: ");
		zt_guiItemSetAlign(label, ztAlign_Left);
		zt_guiSizerAddItem(sizer, label, 0, padding);

		ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer, ztGuiScrollContainerBehaviorFlags_StretchHorz);
		zt_guiSizerAddItem(sizer, scroll, 1, padding);

		ztGuiItem *tile_sizer = zt_guiMakeWrapSizer(scroll, ztGuiItemOrient_Horz);
		zt_guiScrollContainerSetItem(scroll, tile_sizer);

		zt_fiz(editor->tiles_size) {
			ztGuiItem *button = zt_guiMakeButton(tile_sizer, editor->tiles[i].name);

			zt_guiButtonSetIcon(button, &editor->tiles[i].sprite);
			button->button.icon->half_size.x = .5f;
			button->button.icon->half_size.y = .5f;
			zt_guiItemAutoSize(button);

			zt_guiSizerAddItem(tile_sizer, button, 0, padding);

			zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorTileSelect), editor);
			zt_guiItemSetUserData(button, &editor->tiles[i]);
		}

		editor->gui_tiles = window;
	}

	// make blueprints
	{
		ztGuiItem *sizer = zt_guiMakeSizer(splitter_1, ztGuiItemOrient_Vert, false);
		zt_guiSplitterSetSecondItem(splitter_2, sizer);


		ztGuiItem *label_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, label_sizer, 0, 0);

		ztGuiItem *label = zt_guiMakeStaticText(sizer, "Blueprints: ");
		zt_guiItemSetAlign(label, ztAlign_Left);
		zt_guiSizerAddItem(label_sizer, label, 1, padding);

		ztGuiItem *button = zt_guiMakeButton(sizer, "New Blueprint From Selected");
		button->size.y = label->size.y + padding * 4;
		zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorButtonNewBlueprint), editor);
		zt_guiSizerAddItem(label_sizer, button, 0, padding);

		editor->gui_blueprints_button = button;

		ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer, ztGuiScrollContainerBehaviorFlags_StretchHorz);
		zt_guiSizerAddItem(sizer, scroll, 1, padding);

		ztGuiItem *blueprint_sizer = zt_guiMakeWrapSizer(scroll, ztGuiItemOrient_Horz);
		zt_guiScrollContainerSetItem(scroll, blueprint_sizer);

		editor->gui_blueprints = window;
		editor->gui_blueprints_sizer = blueprint_sizer;
	}

	ztVec2 ext = zt_cameraOrthoGetViewportSize(editor->gui_blueprints->gm->gui_camera);

	zt_guiItemSetSize(editor->gui_blueprints, zt_vec2(5, ext.y - .5f));
	zt_guiItemSetPosition(window, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, zt_vec2(0, -.5f), true);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztPlatformerLevelEditorMenuItem_Enum
{
	ztPlatformerLevelEditorMenuItem_NewColliderSurface,
	ztPlatformerLevelEditorMenuItem_NewColliderSpring,
	ztPlatformerLevelEditorMenuItem_NewColliderBlower,
	ztPlatformerLevelEditorMenuItem_NewColliderBlades,
	ztPlatformerLevelEditorMenuItem_NewColliderMagnet,
	ztPlatformerLevelEditorMenuItem_NewColliderTriggerLine,
	ztPlatformerLevelEditorMenuItem_NewColliderTriggerCircle,
	ztPlatformerLevelEditorMenuItem_NewColliderTriggerRect,
	ztPlatformerLevelEditorMenuItem_NewSprite,
	ztPlatformerLevelEditorMenuItem_NewMarker,

	ztPlatformerLevelEditorMenuItem_MAX,
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorMenuRightClickAddSprite, ZT_FUNC_GUI_DIALOG_SPRITE_SELECTED(_zt_platformerLevelEditorMenuRightClickAddSprite))
{
	if (cancelled) {
		return;
	}

	ztSprite *sprite = zt_spriteManagerGetSprite(sprite_manager, entry->hash);
	if (sprite == nullptr) {
		return;
	}

	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	ztPlatformerCollider collider;
	zt_memSet(&collider, zt_sizeof(ztPlatformerCollider), 0);
	collider.movement_path = -1;
	collider.movement_speed = 1;

	collider.type = ztPlatformerColliderType_Sprite;
	collider.points[0] = editor->last_cam_pos;
	collider.sprite.sprite = *sprite;
	collider.sprite.rotation = 0;
	collider.sprite.hash = entry->hash;
	collider.sprite.layer = zt_guiListBoxGetSelected(editor->gui_layers_list);
	collider.sprite.scale = ztVec2::one;
	collider.sprite.anim_controller = nullptr;

	_zt_platformerLevelEditorAddCollider(editor, &collider);

	_zt_platformerLevelEditorSelectCollider(editor, editor->level->colliders_used - 1);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorMenuRightClickAddMarker, ZT_FUNC_GUI_DIALOG_SPRITE_SELECTED(_zt_platformerLevelEditorMenuRightClickAddMarker))
{
	if (cancelled) {
		return;
	}

	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	ztPlatformerCollider collider;
	zt_memSet(&collider, zt_sizeof(ztPlatformerCollider), 0);
	collider.movement_path = -1;
	collider.movement_speed = 1;

	collider.type = ztPlatformerColliderType_Marker;
	collider.points[0] = editor->mouse_pos;
	collider.marker.type = 0;
	collider.marker.info[0] = 0;

	_zt_platformerLevelEditorAddCollider(editor, &collider);
	_zt_platformerLevelEditorSelectCollider(editor, editor->level->colliders_used - 1);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorMenuRightClick, ZT_FUNC_GUI_MENU_SELECTED(_zt_platformerLevelEditorMenuRightClick))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	ztPlatformerCollider collider;
	zt_memSet(&collider, zt_sizeof(ztPlatformerCollider), 0);
	collider.movement_path = -1;
	collider.movement_speed = 1;

	bool add_collider = true;

	//editor->mouse_pos = _zt_platformerSnapPosition(editor, editor->mouse_pos, false);
	ztVec2 col_pos = editor->last_cam_pos;

	switch (menu_item)
	{
		case ztPlatformerLevelEditorMenuItem_NewColliderSurface: {
			collider.type = ztPlatformerColliderType_Surface;
			collider.points[0] = col_pos + zt_vec2(-1, 0);
			collider.points[1] = col_pos + zt_vec2( 1, 0);
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderSpring: {
			collider.type = ztPlatformerColliderType_Spring;
			collider.points[0] = col_pos + zt_vec2(-1, 0);
			collider.points[1] = col_pos + zt_vec2(1, 0);
			collider.spring.strength = 1;
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderBlower: {
			collider.type = ztPlatformerColliderType_Blower;
			collider.points[0] = col_pos + zt_vec2(-1, 0);
			collider.points[1] = col_pos + zt_vec2(1, 0);
			collider.blower.strength = 1;
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderBlades: {
			collider.type = ztPlatformerColliderType_Blades;
			collider.points[0] = collider.points[1] = col_pos;
			collider.blades.radius = 1;
			collider.blades.speed = 1;
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderMagnet: {
			collider.type = ztPlatformerColliderType_Magnet;
			collider.points[0] = collider.points[1] = col_pos;
			collider.magnet.strength = 1;
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderTriggerLine: {
			collider.type = ztPlatformerColliderType_TriggerLine;
			collider.points[0] = col_pos + zt_vec2(-1, 0);
			collider.points[1] = col_pos + zt_vec2(1, 0);
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderTriggerCircle: {
			collider.type = ztPlatformerColliderType_TriggerCircle;
			collider.points[0] = collider.points[1] = col_pos;
			collider.trigger_circle.radius = 1;
		} break;

		case ztPlatformerLevelEditorMenuItem_NewColliderTriggerRect: {
			collider.type = ztPlatformerColliderType_TriggerRect;
			collider.points[0] = col_pos + zt_vec2(-1, 0);
			collider.points[1] = col_pos + zt_vec2(1, 0);
			collider.trigger_rect.height = 2;
		} break;

		case ztPlatformerLevelEditorMenuItem_NewSprite: {
			add_collider = false;
			zt_guiDialogSpriteSelector(editor->sprite_manager, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorMenuRightClickAddSprite), editor);
		} break;

		case ztPlatformerLevelEditorMenuItem_NewMarker: {
			collider.type = ztPlatformerColliderType_Marker;
			collider.points[0] = collider.points[1] = col_pos;
			collider.marker.type = 0;
			collider.marker.info[0] = 0;
		} break;

		default: {
			zt_assertReturnOnFail(false);
		}
	}

	if (add_collider) {
		_zt_platformerLevelEditorAddCollider(editor, &collider);
		_zt_platformerLevelEditorSelectCollider(editor, editor->level->colliders_used - 1);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorSelectionLayerChange, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_platformerLevelEditorSelectionLayerChange))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	i32 layer = selected;

	zt_fiz(editor->selection_count) {
		ztPlatformerCollider *collider = &editor->level->colliders[editor->selection[i]];

		if (collider->type == ztPlatformerColliderType_Sprite) {
			ztPlatformerCollider copy;
			zt_memCpy(&copy, zt_sizeof(ztPlatformerCollider), collider, zt_sizeof(ztPlatformerCollider));

			copy.sprite.layer = layer;

			if (i != 0) {
				editor->actions_group -= 1; // make the same action group so undo/redo works appropriately
			}

			_zt_platformerLevelEditorEditCollider(editor, editor->selection[i], collider, &copy, false);
		}
	}

	zt_platformerRecalcQuadTree(editor->level);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorSelectionMovementPathChanged, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_platformerLevelEditorSelectionMovementPathChanged))
{
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)user_data;

	zt_fiz(editor->selection_count) {
		ztPlatformerCollider *collider = &editor->level->colliders[editor->selection[i]];

		ztPlatformerCollider copy;
		zt_memCpy(&copy, zt_sizeof(ztPlatformerCollider), collider, zt_sizeof(ztPlatformerCollider));

		copy.movement_path = selected - 1;

		if (i != 0) {
			editor->actions_group -= 1; // make the same action group so undo/redo works appropriately
		}

		_zt_platformerLevelEditorEditCollider(editor, editor->selection[i], collider, &copy, false);
	}
	zt_platformerRecalcQuadTree(editor->level);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorSelectionMovementOffsetChanged, ZT_FUNC_GUI_EDITOR_VALUE_CHANGED(_zt_platformerLevelEditorSelectionMovementOffsetChanged))
{
	ztPlatformerLevelEditor *level_editor = (ztPlatformerLevelEditor*)user_data;

	zt_fiz(level_editor->selection_count) {
		ztPlatformerCollider *collider = &level_editor->level->colliders[level_editor->selection[i]];

		ztPlatformerCollider copy;
		zt_memCpy(&copy, zt_sizeof(ztPlatformerCollider), collider, zt_sizeof(ztPlatformerCollider));

		copy.movement_offset = level_editor->selection_movement_offset;

		if (i != 0) {
			level_editor->actions_group -= 1; // make the same action group so undo/redo works appropriately
		}

		_zt_platformerLevelEditorEditCollider(level_editor, level_editor->selection[i], collider, &copy, false);
	}
	zt_platformerRecalcQuadTree(level_editor->level);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorSelectionMovementSpeedChanged, ZT_FUNC_GUI_EDITOR_VALUE_CHANGED(_zt_platformerLevelEditorSelectionMovementSpeedChanged))
{
	ztPlatformerLevelEditor *level_editor = (ztPlatformerLevelEditor*)user_data;

	zt_fiz(level_editor->selection_count) {
		ztPlatformerCollider *collider = &level_editor->level->colliders[level_editor->selection[i]];

		ztPlatformerCollider copy;
		zt_memCpy(&copy, zt_sizeof(ztPlatformerCollider), collider, zt_sizeof(ztPlatformerCollider));

		copy.movement_speed = level_editor->selection_movement_speed;

		if (i != 0) {
			level_editor->actions_group -= 1; // make the same action group so undo/redo works appropriately
		}

		_zt_platformerLevelEditorEditCollider(level_editor, level_editor->selection[i], collider, &copy, false);
	}
	zt_platformerRecalcQuadTree(level_editor->level);
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorCreateGuiForSelection(ztPlatformerLevelEditor *editor)
{
	if (editor->gui_active_item != nullptr) {
		zt_guiItemFree(editor->gui_active_item);
	}

	if (editor->selection_count <= 0) {
		return;
	}

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *panel = zt_guiMakePanel(nullptr, ztGuiPanelBehaviorFlags_DrawBackground | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput);
	zt_guiItemSetPosition(panel, ztAlign_Right | ztAlign_Bottom, ztAnchor_Right | ztAnchor_Bottom, zt_vec2(-8 / zt_pixelsPerUnit(), 8 / zt_pixelsPerUnit()));

	ztGuiItem *sizer_main = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);

	zt_guiSizerAddStretcher(sizer_main, 0, padding * 2);
	zt_guiSizerAddItem(sizer_main, zt_guiMakeStaticText(sizer_main, "(Multiple Items)"), 0, padding, ztAlign_Center, 0);

	ztGuiItem *sizer = zt_guiMakeColumnSizer(sizer_main, 2, ztGuiColumnSizerType_FillRow, true);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	zt_guiSizerAddItem(sizer_main, sizer, 1, padding * 4);
	{
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Layer:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *combo_layers = zt_guiMakeComboBox(sizer, editor->level->layers_size);

		zt_guiComboBoxSetCallback(combo_layers, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorSelectionLayerChange), editor);

		zt_fiz(editor->level->layers_size) {
			zt_guiComboBoxAppend(combo_layers, editor->level->layers[i].name);
		}

		i32 layer = -1;

		zt_fiz(editor->selection_count) {
			ztPlatformerCollider *collider = &editor->level->colliders[editor->selection[i]];

			if (collider->type == ztPlatformerColliderType_Sprite) {
				if (layer == -1) {
					layer = collider->sprite.layer;
				}
				else {
					if (collider->sprite.layer != layer) {
						layer = -100;
						break;
					}
				}
			}
		}

		if (layer >= 0) {
			zt_guiComboBoxSetSelected(combo_layers, layer);
		}

		zt_guiItemSetSize(combo_layers, zt_vec2(3.5f, -1));
		zt_guiSizerAddItem(sizer, combo_layers, 1, padding);
	}

	{
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Movement Path:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *combo_movement_path = zt_guiMakeComboBox(sizer, editor->level->movement_paths_used + 1);

		zt_guiComboBoxSetCallback(combo_movement_path, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorSelectionMovementPathChanged), editor);

		zt_guiComboBoxAppend(combo_movement_path, "No Path");
		zt_fiz(editor->level->movement_paths_used) {
			zt_guiComboBoxAppend(combo_movement_path, editor->level->movement_paths[i].name);
		}

		i32 movement_path = -1;

		zt_fiz(editor->selection_count) {
			ztPlatformerCollider *collider = &editor->level->colliders[editor->selection[i]];

			if (movement_path == -1) {
				movement_path = collider->movement_path;
			}
			else {
				if (movement_path != collider->movement_path) {
					movement_path = -100;
					break;
				}
			}
		}

		if (movement_path >= 0) {
			zt_guiComboBoxSetSelected(combo_movement_path, movement_path - 1);
		}

		zt_guiItemSetSize(combo_movement_path, zt_vec2(3.5f, -1));
		zt_guiSizerAddItem(sizer, combo_movement_path, 1, padding);
	}

	{
		r32 movement_offset = -1;

		zt_fiz(editor->selection_count) {
			ztPlatformerCollider *collider = &editor->level->colliders[editor->selection[i]];

			if (movement_offset == -1) {
				movement_offset = collider->movement_offset;
			}
			else {
				if (!zt_real32Eq(movement_offset, collider->movement_offset)) {
					movement_offset = -100;
					break;
				}
			}
		}

		if (movement_offset >= 0) {
			editor->selection_movement_offset = movement_offset;
		}
		else {
			editor->selection_movement_offset = 1;
		}

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Movement Offset:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *edit_movement_offset = zt_guiMakeEditor(sizer, nullptr, &editor->selection_movement_offset, 0, ztReal32Max, .25f);

		zt_guiEditorSetCallback(edit_movement_offset, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorSelectionMovementOffsetChanged), editor);

		zt_guiItemSetSize(edit_movement_offset, zt_vec2(3.5f, -1));
		zt_guiSizerAddItem(sizer, edit_movement_offset, 1, padding);
	}

	{
		r32 movement_speed = -1;

		zt_fiz(editor->selection_count) {
			ztPlatformerCollider *collider = &editor->level->colliders[editor->selection[i]];

			if (movement_speed == -1) {
				movement_speed = collider->movement_speed;
			}
			else {
				if (!zt_real32Eq(movement_speed, collider->movement_speed)) {
					movement_speed = -100;
					break;
				}
			}
		}

		if (movement_speed >= 0) {
			editor->selection_movement_speed = movement_speed;
		}
		else {
			editor->selection_movement_speed = 1;
		}

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Movement Speed:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *edit_movement_speed = zt_guiMakeEditor(sizer, nullptr, &editor->selection_movement_speed, 0, ztReal32Max, .25f);

		zt_guiEditorSetCallback(edit_movement_speed, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorSelectionMovementSpeedChanged), editor);

		zt_guiItemSetSize(edit_movement_speed, zt_vec2(3.5f, -1));
		zt_guiSizerAddItem(sizer, edit_movement_speed, 1, padding);
	}


	ztVec2 size = zt_guiSizerGetMinSize(sizer_main) + zt_vec2(padding * 2, padding * 2);
	size.x = zt_max(size.x, 5);
	zt_guiItemSetSize(panel, size);

	editor->gui_active_item = panel;
	editor->gui_active_item_name_edit = nullptr;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorColliderNameTextChange, ZT_FUNC_GUI_TEXTEDIT_KEY(_zt_platformerLevelEditorColliderNameTextChange))
{
	if (!input_keys[ztInputKeys_Return].justPressed()) {
		return;
	}

	ztPlatformerCollider *collider = (ztPlatformerCollider*)user_data;
	
	char name[zt_elementsOf(collider->name)] = { 0 };

	zt_guiTextEditGetValue(textedit, name, zt_elementsOf(name));

	zt_strCpy(collider->name, zt_elementsOf(collider->name), name);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorColliderMarkerTypeSelected, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_platformerLevelEditorColliderMarkerTypeSelected))
{
	ztPlatformerCollider *collider = (ztPlatformerCollider*)user_data;
	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)zt_guiItemGetUserData(combobox);

	if (selected > 0) {
		collider->marker.type = editor->markers[selected - 1].value;
		zt_strCpy(collider->marker.info, zt_elementsOf(collider->marker.info), editor->markers[selected - 1].info);
	}
	else {
		collider->marker.type = 0;
		zt_strCpy(collider->marker.info, zt_elementsOf(collider->marker.info), "");
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_platformerLevelEditorColliderMovementPathSelected, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_platformerLevelEditorColliderMovementPathSelected))
{
	ztPlatformerCollider *collider = (ztPlatformerCollider*)user_data;

	ztPlatformerLevelEditor *editor = (ztPlatformerLevelEditor*)zt_guiItemGetUserData(combobox);

	if (selected > 0) {
		collider->movement_path = selected - 1;
	}
	else {
		collider->movement_path = -1;
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_platformerLevelEditorCreateGuiForCollider(ztPlatformerLevelEditor *editor, ztPlatformerCollider *collider)
{
	if (editor->gui_active_item != nullptr) {
		zt_guiItemFree(editor->gui_active_item);
	}

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *panel = zt_guiMakePanel(nullptr, ztGuiPanelBehaviorFlags_DrawBackground | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput);
	zt_guiItemSetPosition(panel, ztAlign_Right | ztAlign_Bottom, ztAnchor_Right | ztAnchor_Bottom, zt_vec2(-8 / zt_pixelsPerUnit(), 8 / zt_pixelsPerUnit()));

	ztGuiItem *sizer_main = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);

	char *type = "Unknown Type";
	bool has_two_positions = true;
	switch (collider->type)
	{
		case ztPlatformerColliderType_Surface:       type = "Surface"; break;
		case ztPlatformerColliderType_Spring:        type = "Spring";  break;
		case ztPlatformerColliderType_Blower:        type = "Blower";  break;
		case ztPlatformerColliderType_Blades:        type = "Blades";  has_two_positions = false; break;
		case ztPlatformerColliderType_Magnet:        type = "Magnet";  has_two_positions = false; break;
		case ztPlatformerColliderType_TriggerLine:   type = "Trigger Line"; break;
		case ztPlatformerColliderType_TriggerCircle: type = "Trigger Circle"; has_two_positions = false;  break;
		case ztPlatformerColliderType_TriggerRect:   type = "Trigger Rect"; break;
		case ztPlatformerColliderType_Sprite:        type = "Sprite"; has_two_positions = false; break;
		case ztPlatformerColliderType_Marker:        type = "Marker"; has_two_positions = false; break;
	}

	zt_guiSizerAddStretcher(sizer_main, 0, padding * 2);

	i32 idx = -1;
	zt_fiz(editor->level->colliders_used) {
		if(collider == &editor->level->colliders[i]) {
			idx = i;
			break;
		}
	}

	zt_strMakePrintf(type_full, 128, "%s (%d)", type, idx);

	zt_guiSizerAddItem(sizer_main, zt_guiMakeStaticText(sizer_main, type_full), 0, padding, ztAlign_Center, 0);

	ztGuiItem *sizer = zt_guiMakeColumnSizer(sizer_main, 2, ztGuiColumnSizerType_FillRow, true);
	zt_guiColumnSizerSetProp(sizer, 1, 1);

	zt_guiSizerAddItem(sizer_main, sizer, 1, padding * 4);

	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Name:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
	ztGuiItem *text_name = zt_guiMakeTextEdit(sizer, collider->name, 0, 128);
	zt_guiTextEditSetCallback(text_name, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorColliderNameTextChange), collider);
	zt_guiSizerAddItem(sizer, text_name, 1, padding);

	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, has_two_positions ? "Position 1:" : "Position:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
	ztGuiItem *edit_pos0 = zt_guiMakeEditor(sizer, nullptr, &collider->points[0], ztVec2::min, ztVec2::max, .125f, false, "X", "Y");
	zt_guiItemSetSize(edit_pos0, zt_vec2(3.5f, -1));
	zt_guiSizerAddItem(sizer, edit_pos0, 1, padding);

	if (has_two_positions) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Position 2:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *edit_pos1 = zt_guiMakeEditor(sizer, nullptr, &collider->points[1], ztVec2::min, ztVec2::max, .125f, false, "X", "Y");
		zt_guiItemSetSize(edit_pos1, zt_vec2(3.5f, -1));
		zt_guiSizerAddItem(sizer, edit_pos1, 1, padding);
	}

	switch (collider->type)
	{
		case ztPlatformerColliderType_Spring: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Spring Strength:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_strength = zt_guiMakeEditor(sizer, nullptr, &collider->spring.strength, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_strength, 1, padding);
		} break;

		case ztPlatformerColliderType_Blower: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Blower Strength:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_strength = zt_guiMakeEditor(sizer, nullptr, &collider->blower.strength, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_strength, 1, padding);
		} break;

		case ztPlatformerColliderType_Blades: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Blades Radius:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_radius = zt_guiMakeEditor(sizer, nullptr, &collider->blades.radius, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_radius, 1, padding);

			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Blades Speed:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_speed = zt_guiMakeEditor(sizer, nullptr, &collider->blades.speed, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_speed, 1, padding);
		} break;

		case ztPlatformerColliderType_Magnet: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Magnet Strength:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_strength = zt_guiMakeEditor(sizer, nullptr, &collider->blower.strength, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_strength, 1, padding);
		} break;

		case ztPlatformerColliderType_TriggerCircle: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Radius:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_strength = zt_guiMakeEditor(sizer, nullptr, &collider->blower.strength, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_strength, 1, padding);
		} break;

		case ztPlatformerColliderType_TriggerRect: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Height:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_height = zt_guiMakeEditor(sizer, nullptr, &collider->trigger_rect.height, 0.f, 10.f, .125f);
			zt_guiSizerAddItem(sizer, edit_height, 1, padding);
		} break;

		case ztPlatformerColliderType_Sprite: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Rotation:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *edit_rotation = zt_guiMakeEditor(sizer, nullptr, &collider->sprite.rotation, -360.f, 360.f, 1.f);
			zt_guiSizerAddItem(sizer, edit_rotation, 1, padding);
		} break;

		case ztPlatformerColliderType_Marker: {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Type:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *combo_type = zt_guiMakeComboBox(sizer, editor->markers_size + 1);

			zt_guiComboBoxAppend(combo_type, "<None>", nullptr);
			zt_fiz(editor->markers_size) {
				zt_guiComboBoxAppend(combo_type, editor->markers[i].name, nullptr);

				if (collider->marker.type == editor->markers[i].value) {
					zt_guiComboBoxSetSelected(combo_type, i + 1);
				}
			}
			zt_guiSizerAddItem(sizer, combo_type, 1, padding);
			zt_guiItemSetUserData(combo_type, editor);
			zt_guiComboBoxSetCallback(combo_type, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorColliderMarkerTypeSelected), collider);

			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Info:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
			ztGuiItem *textedit = zt_guiMakeTextEdit(sizer, collider->marker.info, zt_elementsOf(collider->marker.info));
			zt_guiTextEditSetLiveBuffer(textedit, collider->marker.info, zt_elementsOf(collider->marker.info));
			zt_guiSizerAddItem(sizer, textedit, 1, padding);
		} break;

	}

	if (editor->level->movement_paths_used > 0) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Movement Path:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		//ztGuiItem *edit_movement_path = zt_guiMakeEditor(sizer, nullptr, &collider->movement_path, -1, editor->level->movement_paths_used, 1);
		ztGuiItem *combo_movement_path = zt_guiMakeComboBox(sizer, editor->level->movement_paths_used + 1);

		zt_guiComboBoxAppend(combo_movement_path, "No Path");
		zt_fiz(editor->level->movement_paths_used) {
			zt_guiComboBoxAppend(combo_movement_path, editor->level->movement_paths[i].name);

			if (collider->movement_path == i) {
				zt_guiComboBoxSetSelected(combo_movement_path, zt_guiComboBoxGetItemCount(combo_movement_path) - 1);
			}
		}
		zt_guiSizerAddItem(sizer, combo_movement_path, 1, padding);
		zt_guiItemSetUserData(combo_movement_path, editor);
		zt_guiComboBoxSetCallback(combo_movement_path, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorColliderMovementPathSelected), collider);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Movement Offset:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *edit_movement_offset = zt_guiMakeEditor(sizer, nullptr, &collider->movement_offset, 0.f, 60.f, .125f);
		zt_guiSizerAddItem(sizer, edit_movement_offset, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Movement Speed:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		ztGuiItem *edit_movement_speed = zt_guiMakeEditor(sizer, nullptr, &collider->movement_speed, 0.f, 60.f, .125f);
		zt_guiSizerAddItem(sizer, edit_movement_speed, 1, padding);
	}

	ztVec2 size = zt_guiSizerGetMinSize(sizer_main) + zt_vec2(padding * 2, padding * 2);
	size.x = zt_max(size.x, 5);
	zt_guiItemSetSize(panel, size);

	editor->gui_active_item = panel;
	editor->gui_active_item_name_edit = text_name;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

bool zt_platformerLevelEditorMake(ztPlatformerLevelEditor *editor, ztPlatformerLevel *level, ztSpriteManager *sprite_manager, ztPlatformerLevelEditorTile *tiles, i32 tiles_size, ztPlatformerLevelEditorMarker *markers, i32 markers_size, i32 action_buffer_size)
{
	editor->level = level;
	editor->file_name[0] = 0;
	editor->levels_path[0] = 0;
	editor->enabled = true;

	editor->actions = zt_mallocStructArray(ztPlatformerLevelEditorAction, action_buffer_size);
	editor->actions_size = action_buffer_size;
	editor->actions_first = 0;
	editor->actions_current = -1;
	editor->active_collider = -1;
	editor->actions_group = 0;

	editor->opts_draw_grid = true;
	editor->opts_snap_points = true;
	editor->opts_snap_increment = .25f;

	editor->layer_show = zt_mallocStructArray(bool, level->layers_size + 1);
	editor->layer_lock = zt_mallocStructArray(bool, level->layers_size + 1);

	zt_fiz(level->layers_size + 1) {
		editor->layer_show[i] = true;
	}

	editor->sprite_manager = sprite_manager;

	editor->tiles_size = tiles_size;
	editor->tiles = zt_mallocStructArray(ztPlatformerLevelEditorTile, tiles_size);

	zt_fiz(tiles_size) {
		zt_memCpy(&editor->tiles[i], zt_sizeof(ztPlatformerLevelEditorTile), &tiles[i], zt_sizeof(ztPlatformerLevelEditorTile));
	}

	editor->tiles_unit_size = 1;

	editor->markers_size = markers_size;
	editor->markers = zt_mallocStructArray(ztPlatformerLevelEditorMarker, markers_size);

	zt_fiz(markers_size) {
		zt_memCpy(&editor->markers[i], zt_sizeof(ztPlatformerLevelEditorMarker), &markers[i], zt_sizeof(ztPlatformerLevelEditorMarker));
	}

	_zt_platformerLeveleditorMakeToolsWindow(editor);

	editor->blueprints = nullptr;

	editor->selection = zt_mallocStructArray(i32, level->colliders_size);
	editor->selection_count = 0;

	editor->gui_right_click_menu = zt_guiMakeMenu(nullptr);
	zt_guiMenuSetCallback(editor->gui_right_click_menu, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorMenuRightClick));
	zt_guiMenuAppend(editor->gui_right_click_menu, "New Sprite", ztPlatformerLevelEditorMenuItem_NewSprite, editor);

	editor->gui_right_click_menu_colliders = zt_guiMakeMenu(nullptr);
	zt_guiMenuSetCallback(editor->gui_right_click_menu_colliders, ZT_FUNCTION_POINTER_TO_VAR(_zt_platformerLevelEditorMenuRightClick));
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Surface", ztPlatformerLevelEditorMenuItem_NewColliderSurface, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Spring", ztPlatformerLevelEditorMenuItem_NewColliderSpring, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Blower", ztPlatformerLevelEditorMenuItem_NewColliderBlower, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Blades", ztPlatformerLevelEditorMenuItem_NewColliderBlades, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Magnet", ztPlatformerLevelEditorMenuItem_NewColliderMagnet, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Trigger Line", ztPlatformerLevelEditorMenuItem_NewColliderTriggerLine, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Trigger Circle", ztPlatformerLevelEditorMenuItem_NewColliderTriggerCircle, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Trigger Rect", ztPlatformerLevelEditorMenuItem_NewColliderTriggerRect, editor);
	zt_guiMenuAppend(editor->gui_right_click_menu_colliders, "New Marker", ztPlatformerLevelEditorMenuItem_NewMarker, editor);

	return true;
}

// ================================================================================================================================================================================================

void zt_platformerLevelEditorFree(ztPlatformerLevelEditor *editor)
{
	if (editor == nullptr) {
		return;
	}

	if (editor->actions) {
		zt_free(editor->actions);
		editor->actions = nullptr;
		editor->actions_size = editor->actions_first = editor->actions_current = 0;
	}

	if (editor->selection) {
		zt_free(editor->selection);
		editor->selection = nullptr;
		editor->selection_count = 0;
	}

	if (editor->tiles) {
		zt_free(editor->tiles);
		editor->tiles = nullptr;
		editor->tiles_size = 0;
	}

	if (editor->markers) {
		zt_free(editor->markers);
		editor->markers = nullptr;
		editor->markers_size = 0;
	}

	if (editor->layer_lock) zt_free(editor->layer_lock);
	if (editor->layer_show) zt_free(editor->layer_show);

	editor->enabled = false;
	editor->level = nullptr;
}

// ================================================================================================================================================================================================

void zt_platformerLevelEditorEnable(ztPlatformerLevelEditor *editor, bool enabled)
{
	editor->enabled = enabled;
	zt_guiItemShow(editor->gui_tools, enabled);

	zt_platformerResetMovementPaths(editor->level);

	_zt_platformerLevelEditorClearSelection(editor);
}

// ================================================================================================================================================================================================

bool zt_platformerLevelEditorUpdate(ztPlatformerLevelEditor *editor, ztInputKeys *input_keys, ztInputMouse *input_mouse, bool gui_input, ztCamera *game_camera, ztCamera *gui_camera, r32 dt)
{
	{
		zt_strMakePrintf(items_count, 64, "%d/%d", editor->level->colliders_used, editor->level->colliders_size);

		if (!zt_strEquals(editor->gui_items_count->label, items_count)) {
			zt_guiItemSetLabel(editor->gui_items_count, items_count);
		}

		zt_guiItemShow(editor->gui_blueprints_button, editor->selection_count != 0 || editor->active_collider >= 0);

		editor->last_cam_pos = _zt_platformerSnapPosition(editor, game_camera->position.xy, false);
	}

	if (input_mouse->leftJustPressed()) {
		int debug_stop = 1;
	}
	if (input_mouse->leftJustReleased()) {
		int debug_stop = 1;
	}

	if (editor->enabled == false) {
		return false;
	}

	bool snap_disable = input_keys[ztInputKeys_Control].pressed() || editor->opts_snap_points == false;
	bool colliders_layer_selected = zt_guiListBoxGetSelected(editor->gui_layers_list) == editor->level->layers_size;
	ztQuadTree *quadtree = colliders_layer_selected ? &editor->level->quadtree : &editor->level->quadtree_visual;
	i32 active_layer = zt_guiListBoxGetSelected(editor->gui_layers_list);

	// if a collider is selected and we're not manipulating it with the mouse, check to see if it's changed and if so add an action for the change
	if (editor->active_collider >= 0 && editor->mouse_state == ztPlatformerLevelEditorMouseState_Waiting) {
		if (zt_memCmp(&editor->active_collider_copy, &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider))) {
			ztPlatformerCollider collider_before, collider_after;
			zt_memCpy(&collider_before, zt_sizeof(ztPlatformerCollider), &editor->active_collider_copy, zt_sizeof(ztPlatformerCollider));
			zt_memCpy(&collider_after, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));

			_zt_platformerLevelEditorEditCollider(editor, editor->active_collider, &collider_before, &collider_after, true);
			zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));

			zt_guiTextEditSetValue(editor->gui_active_item_name_edit, editor->active_collider_copy.name);
		}
	}

	if (gui_input) {
		if (editor->mouse_state == ztPlatformerLevelEditorMouseState_Blueprint) {
			ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
			editor->mouse_pos = _zt_platformerSnapPosition(editor, mouse_pos, snap_disable);
		}
		if (editor->mouse_state == ztPlatformerLevelEditorMouseState_Tile) {
			ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
			editor->mouse_pos = _zt_platformerSnapPosition(editor, mouse_pos, snap_disable, editor->tiles_unit_size) - (ztVec2::one * (editor->tiles_unit_size * .5f));
		}
		editor->gui_had_input = true;
		return false;
	}


	bool mouse_over_gui = zt_guiManagerMouseOverGui(zt_guiGetActiveManager());// || editor->gui_had_input;
	editor->gui_had_input = false;

	if (input_mouse->rightJustPressed() && !mouse_over_gui) {
		editor->mouse_dragging_camera = true;
		editor->mouse_dragging_camera_pos = zt_cameraOrthoScreenToWorld(gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		return true;
	}

	editor->mouse_time_since_change += dt;

	r32 dist_points = 8 / zt_pixelsPerUnit();

	bool right_click_for_dismissal = false;

	if (editor->mouse_dragging_camera) {
		ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(gui_camera, input_mouse->screen_x, input_mouse->screen_y);

		ztVec2 movement = mouse_pos - editor->mouse_dragging_camera_pos;
		editor->mouse_dragging_camera_pos = mouse_pos;

		game_camera->position.xy += (movement * zt_vec2(-1, -1));
		zt_cameraRecalcMatrices(game_camera);

		if (input_mouse->rightJustReleased()) {
			editor->mouse_dragging_camera = false;
		}
	}

	if (input_mouse->leftJustPressed() && !mouse_over_gui && editor->mouse_state == ztPlatformerLevelEditorMouseState_Waiting) {

		editor->mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
		// snap is context sensitive, so don't snap here
		editor->mouse_movement = ztVec2::zero;
		editor->mouse_time_since_change = 0;
		editor->mouse_drag_confirmed = false;

		if (input_keys[ztInputKeys_Control].pressed()) {
			editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingMakeSelection;
			editor->mouse_drag_pos_start = editor->mouse_pos;
			editor->mouse_drag_confirmed = true;
		}
		else {
			if (editor->active_collider >= 0) {
				ztVec2 p0, p1;
				zt_platformerGetColliderPositions(editor->level, &editor->level->colliders[editor->active_collider], &p0, &p1, nullptr);

				if (editor->mouse_pos.distance((p0 + p1) * .5f) < dist_points) {
					editor->mouse_pos = _zt_platformerSnapPosition(editor, editor->mouse_pos, snap_disable);
					editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingCollider;
					editor->mouse_drag_pos_start = p0;
				}
				else if (editor->mouse_pos.distance(p0) < dist_points) {
					editor->mouse_pos = _zt_platformerSnapPosition(editor, editor->mouse_pos, snap_disable);
					editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingColliderPoint;
					editor->active_collider_point = 0;
					editor->mouse_drag_pos_start = p0;
				}
				else if (editor->mouse_pos.distance(p1) < dist_points) {
					editor->mouse_pos = _zt_platformerSnapPosition(editor, editor->mouse_pos, snap_disable);
					editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingColliderPoint;
					editor->active_collider_point = 1;
					editor->mouse_drag_pos_start = p1;
				}
				else {
					//_zt_platformerLevelEditorClearSelection(editor);
					editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingEmpty;
				}
			}
			else if (editor->selection_count > 0) {
				zt_fiz(editor->selection_count) {
					ztVec2 min, max;
					_zt_platformerGetExtents(editor->level, &editor->level->colliders[editor->selection[i]], &min, &max, true);

					ztVec2 node_center = (min + max) * .5f;
					ztVec2 node_size = max - min;

					if (zt_collisionPointInAABB(zt_vec3(editor->mouse_pos, 0), zt_vec3(node_center, 0), zt_vec3(node_size, 0))) {
						editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingSelection;
						editor->mouse_pos = _zt_platformerSnapPosition(editor, editor->mouse_pos, snap_disable);
						break;
					}
				}

				if (editor->mouse_state != ztPlatformerLevelEditorMouseState_DraggingSelection) {
					if (!input_keys[ztInputKeys_Shift].pressed()) {
						_zt_platformerLevelEditorClearSelection(editor);
					}
					else {
						editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingEmpty;
					}
				}
			}
			else {
				editor->mouse_state = ztPlatformerLevelEditorMouseState_DraggingEmpty;
			}
		}
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingEmpty || editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingCollider || editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingColliderPoint) {

		if (editor->mouse_drag_confirmed || (zt_abs(input_mouse->delta_x) + zt_abs(input_mouse->delta_y)) > 6) {
			editor->mouse_drag_confirmed = true;

			ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
			mouse_pos = _zt_platformerSnapPosition(editor, mouse_pos, snap_disable);

			ztVec2 movement = mouse_pos - editor->mouse_pos;
			editor->mouse_pos = mouse_pos;
			editor->mouse_movement += movement;

			if (editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingCollider) {
				ztVec2 diff = editor->level->colliders[editor->active_collider].points[1] - editor->level->colliders[editor->active_collider].points[0];
				if (input_mouse->leftJustReleased()) {
					editor->level->colliders[editor->active_collider].points[0] = editor->mouse_drag_pos_start;
					editor->level->colliders[editor->active_collider].points[1] = editor->mouse_drag_pos_start + diff;

					ztPlatformerCollider collider_before, collider_after;
					zt_memCpy(&collider_before, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
					zt_memCpy(&collider_after, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));

					collider_after.points[0] = _zt_platformerSnapPosition(editor, editor->mouse_drag_pos_start + editor->mouse_movement, snap_disable);
					collider_after.points[1] = _zt_platformerSnapPosition(editor, editor->mouse_drag_pos_start + editor->mouse_movement, snap_disable) + diff;

					_zt_platformerLevelEditorEditCollider(editor, editor->active_collider, &collider_before, &collider_after, true);
					zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
				}
				else {
					editor->level->colliders[editor->active_collider].points[0] = _zt_platformerSnapPosition(editor, editor->mouse_drag_pos_start + editor->mouse_movement, snap_disable);
					editor->level->colliders[editor->active_collider].points[1] = _zt_platformerSnapPosition(editor, editor->mouse_drag_pos_start + editor->mouse_movement, snap_disable) + diff;
				}
			}
			else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingColliderPoint) {
				if (input_mouse->leftJustReleased()) {
					editor->level->colliders[editor->active_collider].points[editor->active_collider_point] = editor->mouse_drag_pos_start;

					ztPlatformerCollider collider_before, collider_after;
					zt_memCpy(&collider_before, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
					zt_memCpy(&collider_after, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));

					collider_after.points[editor->active_collider_point] = editor->mouse_drag_pos_start + editor->mouse_movement;

					_zt_platformerLevelEditorEditCollider(editor, editor->active_collider, &collider_before, &collider_after, true);
					zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
				}
				else {
					editor->level->colliders[editor->active_collider].points[editor->active_collider_point] = editor->mouse_drag_pos_start + editor->mouse_movement;
				}
			}
			else if (editor->active_collider >= 0 || editor->selection_count > 0) {
				_zt_platformerLevelEditorClearSelection(editor);
			}

			if (input_mouse->leftJustReleased()) {
				editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;
			}
		}
		else if (input_mouse->leftJustReleased()) {
			editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;

			if (editor->mouse_time_since_change < .25f) {
				ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);

				ztVec2 aabb_size = zt_vec2(16 / zt_pixelsPerUnit(), 16 / zt_pixelsPerUnit());
				ztQuadTree::Node *nodes[32];
				i32 nodes_count = zt_quadTreeFindNodesThatIntersect(quadtree, nodes, zt_elementsOf(nodes), mouse_pos, aabb_size);

				i32 closest_idx = -1;
				r32 closest_dist = ztReal32Max;
				r32 minimum_dist = 16 / zt_pixelsPerUnit();

				i32 selected_by_click[128];
				i32 selected_by_click_count = 0;

				zt_fiz(nodes_count) {
					zt_fjz(nodes[i]->objects_count) {
						ztPlatformerCollider *collider = &editor->level->colliders[nodes[i]->objects[j]];

						if (collider->type == ztPlatformerColliderType_Sprite && collider->sprite.layer != active_layer) {
							continue;
						}

						ztVec2 min, max;
						_zt_platformerGetExtents(editor->level, collider, &min, &max, true);

						ztVec2 center = (min + max) * .5f;
						ztVec2 size = (max - min);

						if (zt_collisionAABBInAABB(zt_vec3(center, 0), zt_vec3(size, 1), zt_vec3(mouse_pos, 0), zt_vec3(aabb_size, 1))) {
							if (selected_by_click_count < zt_elementsOf(selected_by_click)) {
								bool already_selected = false;
								zt_fkz(selected_by_click_count) {
									if (selected_by_click[k] == nodes[i]->objects[j]) {
										already_selected = true;
										break;
									}
								}
								if (!already_selected) {
									selected_by_click[selected_by_click_count++] = nodes[i]->objects[j];
								}

								zt_logDebug("node [%d] object [%d] (%d) collided", i, j, nodes[i]->objects[j]);
							}
						}

						//ztVec2 p0, p1;
						//zt_platformerGetColliderPositions(editor->level, collider, &p0, &p1, nullptr);
						//
						//r32 dist = ztReal32Max;
						//
						//if (p0 == p1) {
						//	dist = zt_abs(editor->mouse_pos.distance(p0));
						//}
						//else {
						//	dist = zt_abs(editor->mouse_pos.distance(zt_closestPointLineSegmentPoint(zt_vec3(p0, 0), zt_vec3(p1, 0), zt_vec3(editor->mouse_pos, 0)).xy));
						//}						
						//
						//if (dist < minimum_dist && dist < closest_dist && nodes[i]->objects[j] != editor->active_collider) {
						//	if (collider->type != ztPlatformerColliderType_Sprite || collider->sprite.layer == active_layer) {
						//		closest_dist = dist;
						//		closest_idx = nodes[i]->objects[j];
						//	}
						//}
					}
				}

				if (selected_by_click_count == 1) {
					closest_idx = selected_by_click[0];
				}
				else if (selected_by_click_count > 1) {
					if (input_keys[ztInputKeys_Shift].pressed()) {
						zt_fiz(selected_by_click_count) {
							bool already_selected = false;
							zt_fjz(editor->selection_count) {
								if (editor->selection[j] == selected_by_click[i]) {
									already_selected = true;
									break;
								}
							}

							if (!already_selected) {
								editor->selection[editor->selection_count++] = selected_by_click[i];
							}
						}
					}
					else {
						bool active_collider_is_in_selection = false;
						zt_fiz(selected_by_click_count) {
							if (selected_by_click[i] == editor->active_collider) {
								active_collider_is_in_selection = true;
							}
							else if (active_collider_is_in_selection) {
								closest_idx = selected_by_click[i];
							}
						}

						if (!active_collider_is_in_selection) {
							closest_idx = selected_by_click[0];
						}
					}
				}

				if (closest_idx != -1) {
					if (input_keys[ztInputKeys_Shift].pressed() && (editor->active_collider >= 0 || editor->selection_count > 0)) {
						if (editor->active_collider >= 0) {
							i32 active_collider = editor->active_collider;
							_zt_platformerLevelEditorClearSelection(editor);
							editor->selection[editor->selection_count++] = active_collider;
						}

						editor->selection[editor->selection_count++] = closest_idx;
						_zt_platformerLevelEditorCreateGuiForSelection(editor);
					}
					else {
						if (editor->active_collider >= 0) {
							_zt_platformerLevelEditorClearSelection(editor);
						}

						editor->active_collider = closest_idx;
						editor->active_collider_point = -1;

			 			zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[closest_idx], zt_sizeof(ztPlatformerCollider));
						_zt_platformerLevelEditorCreateGuiForCollider(editor, &editor->level->colliders[closest_idx]);
					}
				}
				else {
					_zt_platformerLevelEditorClearSelection(editor);
				}
			}

			editor->mouse_time_since_change = 0;
		}
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingMakeSelection) {
		ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
		ztVec2 movement = mouse_pos - editor->mouse_pos;// zt_vec2(input_mouse->delta_x / zt_pixelsPerUnit(), input_mouse->delta_y / zt_pixelsPerUnit());
		editor->mouse_pos = mouse_pos;
		editor->mouse_movement += movement;

		if (input_mouse->leftJustReleased()) {
			editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;

			if (!input_keys[ztInputKeys_Shift].pressed()) {
				_zt_platformerLevelEditorClearSelection(editor);
			}

			ztVec2 center = (editor->mouse_drag_pos_start + editor->mouse_pos) * .5f;
			ztVec2 size = editor->mouse_pos - editor->mouse_drag_pos_start;
			size.x = zt_abs(size.x);
			size.y = zt_abs(size.y);

			i32 nodes_count = zt_quadTreeFindNodesThatIntersect(quadtree, nullptr, 0, center, size);
			ztQuadTree::Node **nodes = zt_mallocStructArray(ztQuadTree::Node*, nodes_count);
			
			if (nodes_count == zt_quadTreeFindNodesThatIntersect(quadtree, nodes, nodes_count, center, size)) {

				zt_fiz(nodes_count) {
					zt_fjz(nodes[i]->objects_count) {
						i32 collider_idx = nodes[i]->objects[j];

						if (editor->level->colliders[collider_idx].type == ztPlatformerColliderType_Sprite && editor->level->colliders[collider_idx].sprite.layer != active_layer) {
							continue;
						}

						ztVec2 min, max;
						_zt_platformerGetExtents(editor->level, &editor->level->colliders[collider_idx], &min, &max, true);

						ztVec2 node_center = (min + max) * .5f;
						ztVec2 node_size = max - min;
						node_size.x = zt_max(node_size.x, 8 / zt_pixelsPerUnit());
						node_size.y = zt_max(node_size.y, 8 / zt_pixelsPerUnit());

						if (zt_collisionAABBInAABB(zt_vec3(center, 0), zt_vec3(size, 0), zt_vec3(node_center, 0), zt_vec3(node_size, 0), nullptr, nullptr, nullptr)) {

							bool already_selected = false;
							zt_fxz(editor->selection_count) {
								if (editor->selection[x] == collider_idx) {
									already_selected = true;
									break;
								}
							}

							if (!already_selected) {
								editor->selection[editor->selection_count++] = nodes[i]->objects[j];
							}
						}
					}
				}
			}

			if (editor->selection_count == 1) {
				editor->active_collider = editor->selection[0];
				editor->active_collider_point = -1;
				editor->selection_count = 0;

				zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
				_zt_platformerLevelEditorCreateGuiForCollider(editor, &editor->level->colliders[editor->active_collider]);
			}
			else if (editor->selection_count > 1) {
				_zt_platformerLevelEditorCreateGuiForSelection(editor);
			}

			zt_free(nodes);
		}
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingSelection) {
		if (editor->mouse_drag_confirmed || (zt_abs(input_mouse->delta_x) + zt_abs(input_mouse->delta_y)) > 3) {
			editor->mouse_drag_confirmed = true;

			ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
			mouse_pos = _zt_platformerSnapPosition(editor, mouse_pos, snap_disable);
			ztVec2 movement = mouse_pos - editor->mouse_pos;
			editor->mouse_pos = mouse_pos;
			editor->mouse_movement += movement;

			bool requires_recalc = false;
			zt_fiz(editor->selection_count) {
				i32 collider_idx = editor->selection[i];
				editor->level->colliders[collider_idx].points[0] += movement;
				editor->level->colliders[collider_idx].points[1] += movement;

				if (input_mouse->leftJustReleased()) {
					editor->level->colliders[collider_idx].points[0] -= editor->mouse_movement;
					editor->level->colliders[collider_idx].points[1] -= editor->mouse_movement;

					ztPlatformerCollider collider_before, collider_after;
					zt_memCpy(&collider_before, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[collider_idx], zt_sizeof(ztPlatformerCollider));
					zt_memCpy(&collider_after, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[collider_idx], zt_sizeof(ztPlatformerCollider));

					collider_after.points[0] += editor->mouse_movement;
					collider_after.points[1] += editor->mouse_movement;

					if (i != 0) {
						editor->actions_group -= 1; // make the same action group so undo/redo works appropriately
					}
					_zt_platformerLevelEditorEditCollider(editor, collider_idx, &collider_before, &collider_after, false);
					requires_recalc = true;
				}
			}

			if (requires_recalc) {
				zt_platformerRecalcQuadTree(editor->level);
			}

			if (input_mouse->leftJustReleased()) {
				editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;
			}
		}
		else if (input_mouse->leftJustReleased()) {
			editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;
		}
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_Blueprint) {
		ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
		mouse_pos = _zt_platformerSnapPosition(editor, mouse_pos, snap_disable);
		editor->mouse_pos = mouse_pos;

		if (input_mouse->leftJustPressed()) {
			editor->mouse_drag_confirmed = true;
		}
		if (editor->mouse_drag_confirmed) {
			if (input_keys[ztInputKeys_Escape].justPressed() || right_click_for_dismissal) {
				editor->mouse_drag_confirmed = false;
			}

			if (input_mouse->leftJustReleased()) {
				editor->mouse_drag_confirmed = false;

				editor->selection_count = 0;

				zt_fiz(editor->mouse_blueprint->actions_size) {
					ztPlatformerLevelEditorAction *action = _zt_platformerLevelEditorGetAvailableAction(editor);
					zt_memCpy(action, zt_sizeof(ztPlatformerLevelEditorAction), &editor->mouse_blueprint->actions[i], zt_sizeof(ztPlatformerLevelEditorAction));
					action->new_collider.collider.points[0] += editor->mouse_pos;
					action->new_collider.collider.points[1] += editor->mouse_pos;
					action->group = editor->actions_group - 1;
					action->time = zt_getTime();
					_zt_platformerLevelEditorDoAction(editor, action, false);
					if (i != editor->mouse_blueprint->actions_size - 1) {
						editor->actions_group -= 1; // keep in the same group
					}
					editor->selection[editor->selection_count++] = editor->level->colliders_used - 1;
				}

				zt_platformerRecalcQuadTree(editor->level);
			}

		}
		else {
			if (input_keys[ztInputKeys_Escape].justPressed() || right_click_for_dismissal) {
				editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;
			}
		}
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_Tile) {
		ztVec2 mouse_pos = zt_cameraOrthoScreenToWorld(game_camera, input_mouse->screen_x, input_mouse->screen_y);
		editor->mouse_pos = _zt_platformerSnapPosition(editor, mouse_pos, snap_disable, editor->tiles_unit_size) - (ztVec2::one * (editor->tiles_unit_size * .5f));

		if (input_mouse->leftJustPressed()) {
			editor->mouse_drag_confirmed = true;
		}
		if (editor->mouse_drag_confirmed) {
			if (input_keys[ztInputKeys_Escape].justPressed() || right_click_for_dismissal) {
				editor->mouse_drag_confirmed = false;
			}

			if (input_mouse->leftJustReleased()) {
				editor->mouse_drag_confirmed = false;

				ztPlatformerLevelEditorAction *action = _zt_platformerLevelEditorGetAvailableAction(editor);

				action->type = ztPlatformerLevelEditorActionType_NewCollider;
				action->new_collider.collider_idx = -1;
				action->new_collider.collider.points[0] = editor->mouse_pos;
				action->new_collider.collider.points[1] = editor->mouse_pos;
				action->new_collider.collider.sprite.sprite = editor->mouse_tile->sprite;
				action->new_collider.collider.sprite.rotation = editor->mouse_tile->rotation;
				action->new_collider.collider.sprite.layer = zt_guiListBoxGetSelected(editor->gui_layers_list);
				action->new_collider.collider.sprite.hash = editor->mouse_tile->hash;
				action->new_collider.collider.sprite.scale = ztVec2::one;
				action->new_collider.collider.sprite.anim_controller = nullptr;
				action->new_collider.collider.movement_path = -1;
				action->new_collider.collider.movement_speed = 1;
				action->new_collider.collider.type = ztPlatformerColliderType_Sprite;

				_zt_platformerLevelEditorDoAction(editor, action, true);

				editor->selection[editor->selection_count++] = editor->level->colliders_used - 1;
			}
		}
		else {
			if (input_keys[ztInputKeys_Escape].justPressed() || right_click_for_dismissal) {
				editor->mouse_state = ztPlatformerLevelEditorMouseState_Waiting;
			}
		}
	}

	if (input_keys[ztInputKeys_Control].pressed()) {
		if (input_keys[ztInputKeys_Z].justPressed()) {
			if (input_keys[ztInputKeys_Shift].pressed()) {
				_zt_platformerLevelEditorCommandBufferForward(editor);
			}
			else {
				_zt_platformerLevelEditorCommandBufferBackward(editor);
			}
		}
		else if (input_keys[ztInputKeys_Y].justPressed()) {
			_zt_platformerLevelEditorCommandBufferForward(editor);
		}
	}

	if (input_keys[ztInputKeys_Tab].justPressedOrRepeated()) {
		editor->hide_widgets = !editor->hide_widgets;
	}

	if ((editor->selection_count > 0 || editor->active_collider >= 0) && input_keys[ztInputKeys_Delete].justPressed()) {
		i32 selections_count = editor->selection_count > 0 ? editor->selection_count : 1;
		i32 *selections = zt_mallocStructArray(i32, selections_count);

		zt_fiz(editor->selection_count) {
			selections[i] = editor->selection[i];
		}
		if (editor->active_collider >= 0) {
			selections[0] = editor->active_collider;
		}

		struct local
		{
			static int compare(const void *vone, const void *vtwo)
			{
				i32 *ione = (i32*)vone;
				i32 *itwo = (i32*)vtwo;

				if (*ione < *itwo) return 1;
				if (*ione > *itwo) return -1;
				return 0;
			}
		};

		qsort(selections, selections_count, zt_sizeof(i32), local::compare);

		_zt_platformerLevelEditorClearSelection(editor);

		zt_fiz(selections_count) {
			_zt_platformerLevelEditorDeleteCollider(editor, selections[i], &editor->level->colliders[selections[i]]);
			if (i != 0) editor->actions_group -= 1;
		}
		zt_platformerRecalcQuadTree(editor->level);

		zt_free(selections);

		editor->selection_count = 0;
	}

	if (editor->active_collider >= 0) {
		r32 one_pixel = 1 / zt_pixelsPerUnit();
		ztVec2 movement = ztVec2::zero;
		if (input_keys[ztInputKeys_Right].justPressedOrRepeated()) {
			movement.x += one_pixel;
		}
		if (input_keys[ztInputKeys_Left].justPressedOrRepeated()) {
			movement.x -= one_pixel;
		}
		if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
			movement.y += one_pixel;
		}
		if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
			movement.y -= one_pixel;
		}

		if (movement != ztVec2::zero) {
			ztPlatformerCollider collider_before, collider_after;
			zt_memCpy(&collider_before, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
			zt_memCpy(&collider_after, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));

			collider_after.points[0] += movement;
			collider_after.points[1] += movement;

			_zt_platformerLevelEditorEditCollider(editor, editor->active_collider, &collider_before, &collider_after, true);
			zt_memCpy(&editor->active_collider_copy, zt_sizeof(ztPlatformerCollider), &editor->level->colliders[editor->active_collider], zt_sizeof(ztPlatformerCollider));
		}
	}

	return false;
}

// ================================================================================================================================================================================================

void zt_platformerLevelEditorDraw(ztPlatformerLevelEditor *editor, ztDrawList *draw_list, ztCamera *game_camera)
{
	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	{
		zt_platformerDrawBackground(editor->level, draw_list, game_camera);
		zt_fiz(editor->level->layers_size) {
			if (editor->layer_show[i]) {
				zt_platformerDraw(editor->level, draw_list, game_camera, i, nullptr, 0, false);
			}
		}
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================

void zt_platformerLevelEditorDrawWidgets(ztPlatformerLevelEditor *editor, ztDrawList *draw_list, ztCamera *game_camera)
{
	if (editor->hide_widgets) {
		return;
	}

	zt_drawListPushShader(draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(draw_list, ztTextureDefault);

	zt_fiz(editor->level->colliders_used) {
		if (!_zt_platformerLevelEditorIsSelected(editor, i)) {
			continue;
		}

		ztVec2 min, max;
		_zt_platformerGetExtents(editor->level, &editor->level->colliders[i], &min, &max, true);

		zt_drawListPushColor(draw_list, ztVec4::lerp(ztColor_Yellow, ztColor_White, zt_linearRemap(zt_sin(editor->mouse_time_since_change * 8), -1, 1, 0, 1)));

		ztVec2 size = (max - min);
		//size.x = zt_max(size.x, 16 / zt_pixelsPerUnit());
		//size.y = zt_max(size.y, 16 / zt_pixelsPerUnit());
		ztVec2 center = (min + max) * .5f;

		zt_drawListAddEmptyRect(draw_list, center, size + zt_vec2(16 / zt_pixelsPerUnit(), 16 / zt_pixelsPerUnit()) * zt_linearRemap(zt_sin(editor->mouse_time_since_change * 2), -1, 1, 1, 1));
		zt_drawListPopColor(draw_list);

		zt_drawListPushColor(draw_list, ztColor_LightOrange);

		if (editor->active_collider == i) {
			ztVec2 p0, p1;
			zt_platformerGetColliderPositions(editor->level, &editor->level->colliders[i], &p0, &p1, nullptr);

			zt_drawListAddEmptyCircle(draw_list, zt_vec3(p0, 0), .125f, 8);
			if (p0 != p1) {
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(p1, 0), .125f, 8);
			}

			zt_drawListPopColor(draw_list);
			zt_drawListPushColor(draw_list, ztColor_LightPurple);
			zt_drawListAddEmptyCircle(draw_list, zt_vec3((p0 + p1) * .5f, 0), .125f, 8);
			zt_drawListPopColor(draw_list);
		}
	}

	{
		i32 flags = (editor->layer_show[editor->level->layers_size] ? ztPlatformerDrawDebugFlags_DrawColliders : 0) | (editor->opts_draw_grid ? ztPlatformerDrawDebugFlags_DrawGrid : 0) | ztPlatformerDrawDebugFlags_DrawMarkerSprites;
		zt_fiz(editor->level->layers_size) {
			if (editor->layer_show[i]) {
				zt_platformerDrawDebugView(editor->level, draw_list, editor, i, ztVec2::min, flags);
			}
		}
	}

	if (editor->mouse_state == ztPlatformerLevelEditorMouseState_DraggingMakeSelection) {
		zt_drawListPushColor(draw_list, ztColor_White);
		ztVec2 center = (editor->mouse_drag_pos_start + editor->mouse_pos) * .5f;
		ztVec2 size = editor->mouse_pos - editor->mouse_drag_pos_start;
		size.x = zt_abs(size.x);
		size.y = zt_abs(size.y);
		zt_drawListAddEmptyRect(draw_list, center, size);
		zt_drawListPopColor(draw_list);
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_Blueprint) {
		zt_drawListPushColor(draw_list, ztColor_Magenta);
		zt_drawListAddEmptyRect(draw_list, editor->mouse_pos, editor->mouse_blueprint->size);
		zt_drawListPopColor(draw_list);
	}
	else if (editor->mouse_state == ztPlatformerLevelEditorMouseState_Tile) {
		zt_drawListAddSpriteFast(draw_list, &editor->mouse_tile->sprite, zt_vec3(editor->mouse_pos, 0));
	}

	zt_drawListPopTexture(draw_list);
	zt_drawListPopShader(draw_list);
}

// ================================================================================================================================================================================================

#endif // __zt_game_platformer_implementation__
#endif // ZT_GAME_PLATFORMER_IMPLEMENTATION

