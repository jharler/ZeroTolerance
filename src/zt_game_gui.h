/**************************************************************************************************
 ** file: zt_game.h v 0.00 (active initial development)
 **
 ** This library is in the public domain.  Do with it what you will.  No waranty implied.
 **
 ** There is no guarantee that this code works as intended.  Use it at your own risk.
 **
 **************************************************************************************************
   
    Zero Tolerance Game Library
   
    Single header library collection of powerful and easy to use utilities.  The goal is to be able
    to use this header file to easily create programs with access to a wide variety of useful tools.

	The game library is geared towards containing game-specific utilities.  zt_tools.h is required,
	so this technically isn't a single header library, but all the game stuff is in the single file,
	so I say it counts.  I may embed zt_tools.h at some point once both libraries have matured a bit.
   
    Be sure that you #define ZT_GAME_GUI_IMPLEMENTATION is used in one cpp file before including this
    header file:

		#define ZT_GAME_GUI_IMPLEMENTATION
		#include "zt_game_gui.h"
    
	You must also defined the following



 **************************************************************************************************

    Options:


 **************************************************************************************************

	Implimentation Options: (only used with ZT_GAME_IMPLEMENTATION #include)


 **************************************************************************************************

	What's with the name "Zero Tolerance?"
		I chose the name because my goal is to have a zero tolerance policy for slow, bloated
		software, slow compile times, and long development time.  I want this library to be
		fast in execution, fast in compile times and fast and easy to use.

	Special Thanks
		This library is inspired by the single file libraries by Sean Barrett.  Inspiration has
		also been drawn from Casey Muratori's Handmade Hero video series as well as Shawn
		McGrath's programming streams.

 **************************************************************************************************/

#ifndef __zt_game_gui_h_included__
#define __zt_game_gui_h_included__

#include "zt_tools.h"
#include "zt_game.h"

// ------------------------------------------------------------------------------------------------
// gui

void zt_guiInitGlobalMemory(ztMemoryArena *arena);
void *zt_guiGetGlobalMemory(i32 *size);
void zt_guiSetGlobalMemory(void *);

// ------------------------------------------------------------------------------------------------

typedef i32 ztGuiManagerID;
typedef i32 ztGuiItemID;

// ------------------------------------------------------------------------------------------------

enum ztGuiThemeSpriteType_Enum
{
	ztGuiThemeSpriteType_SpriteNineSlice,
	ztGuiThemeSpriteType_Sprite,
};

// ------------------------------------------------------------------------------------------------

struct ztGuiThemeSprite
{
	ztGuiThemeSpriteType_Enum type;
	union {
		struct {
			ztSprite s;
		};
		struct {
			ztSpriteNineSlice sns;
		};
	};
};

// ------------------------------------------------------------------------------------------------

struct ztGuiThemeButtonSprite
{
	ztGuiThemeSprite normal;
	ztGuiThemeSprite highlight;
	ztGuiThemeSprite pressed;
};

// ------------------------------------------------------------------------------------------------

void zt_drawListAddGuiThemeSprite(ztDrawList *draw_list, ztGuiThemeSprite *theme_sprite, const ztVec2& pos, const ztVec2& size);
void zt_drawListAddGuiThemeButtonSprite(ztDrawList *draw_list, ztGuiThemeButtonSprite *theme_button_sprite, const ztVec2& pos, const ztVec2& size, bool highlighted, bool pressed);

// ------------------------------------------------------------------------------------------------

struct ztGuiTheme
{
	ztFontID font;
	r32      font_scale;
	ztColor  font_color;

	ztColor back_color;
	ztColor fore_color;
	ztColor highlight_color;

	ztGuiThemeSprite       sprite_window;
	ztGuiThemeSprite       sprite_panel;
	ztGuiThemeButtonSprite sprite_button;
	ztGuiThemeButtonSprite sprite_checkbox;
	ztGuiThemeSprite       sprite_checkbox_check;
	ztGuiThemeButtonSprite sprite_radio;
	ztGuiThemeSprite       sprite_radio_check;
	ztGuiThemeButtonSprite sprite_slider_horz_handle;
	ztGuiThemeButtonSprite sprite_slider_vert_handle;
	ztGuiThemeSprite       sprite_slider_background;

	ztGuiThemeButtonSprite sprite_scrollbar_horz_handle;
	ztGuiThemeButtonSprite sprite_scrollbar_vert_handle;
	ztGuiThemeButtonSprite sprite_scrollbar_horz_button_neg;
	ztGuiThemeButtonSprite sprite_scrollbar_horz_button_pos;
	ztGuiThemeButtonSprite sprite_scrollbar_vert_button_neg;
	ztGuiThemeButtonSprite sprite_scrollbar_vert_button_pos;
	ztGuiThemeSprite       sprite_scrollbar_background;

	ztGuiThemeSprite       sprite_textedit;
	ztGuiThemeSprite       sprite_textedit_select;

	ztGuiThemeSprite       sprite_menu;
	ztGuiThemeSprite       sprite_menu_highlight;
	ztGuiThemeSprite       sprite_menu_submenu;
	ztGuiThemeSprite       sprite_menu_check;

	ztGuiThemeSprite       sprite_group;
	ztGuiThemeSprite       sprite_slider;
	ztGuiThemeSprite       sprite_tree_collapse;
	ztGuiThemeSprite       sprite_tree_expand;

	r32 window_title_height;
	i32 window_title_align;
	r32 window_title_padding_x;
	r32 window_title_padding_y;

	r32 button_default_w;
	r32 button_default_h;
	r32 button_padding_w;
	r32 button_padding_h;
	
	r32 checkbox_size_w;
	r32 checkbox_size_h;

	r32 radio_size_w;
	r32 radio_size_h;

	r32 slider_handle_w;
	r32 slider_handle_h;
	r32 slider_background_h;

	bool scrollbar_has_buttons;
	r32 scrollbar_button_w;
	r32 scrollbar_button_h;
	r32 scrollbar_handle_min_size;

	r32 scroll_container_padding_x;
	r32 scroll_container_padding_y;

	r32 textedit_padding_x;
	r32 textedit_padding_y;
	r32 textedit_default_w;
	r32 textedit_default_h;

	r32 menu_padding_x;
	r32 menu_padding_y;
	r32 menu_submenu_icon_x;
	r32 menu_submenu_icon_y;

	r32 padding; // space around interior items
	r32 spacing; // space between interior items
};

// ------------------------------------------------------------------------------------------------

enum ztGuiItemType_Enum
{
	ztGuiItemType_Invalid, 

	ztGuiItemType_Window,
	ztGuiItemType_Panel,
	ztGuiItemType_Text,
	ztGuiItemType_Button,
	ztGuiItemType_ToggleButton,
	ztGuiItemType_Checkbox,
	ztGuiItemType_RadioButton,
	ztGuiItemType_Slider,
	ztGuiItemType_Menu,
	ztGuiItemType_Scrollbar,
	ztGuiItemType_ScrollContainer,
	ztGuiItemType_TextEdit,
	ztGuiItemType_Tab,
	ztGuiItemType_Tree,
	ztGuiItemType_ProgressBar,
	
	ztGuiItemType_Custom,
};

// ------------------------------------------------------------------------------------------------

enum ztGuiItemFlags_Enum
{
	ztGuiItemFlags_WantsFocus       = (1<<0),
	ztGuiItemFlags_WantsInput       = (1<<1),
	ztGuiItemFlags_Visible          = (1<<2),
	ztGuiItemFlags_OutlyingChildren = (1<<3),
	ztGuiItemFlags_ClipChildren     = (1<<4),
	ztGuiItemFlags_ClipContents     = (1<<5),
	ztGuiItemFlags_BringToFront     = (1<<6),
	ztGuiItemFlags_Dirty            = (1<<7),
};

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_GUI_ITEM_UPDATE(name) void name(ztGuiItemID item_id, r32 dt, void *user_data)
typedef ZT_FUNC_GUI_ITEM_UPDATE(zt_guiItemUpdate_Func);

#define ZT_FUNC_GUI_ITEM_RENDER(name) void name(ztGuiItemID item_id, ztDrawList *draw_list, ztGuiTheme *theme, const ztVec2& offset, void *user_data)
typedef ZT_FUNC_GUI_ITEM_RENDER(zt_guiItemRender_Func);

#define ZT_FUNC_GUI_ITEM_CLEANUP(name) void name(ztGuiItemID item_id, void *user_data)
typedef ZT_FUNC_GUI_ITEM_CLEANUP(zt_guiItemCleanup_Func);

#define ZT_FUNC_GUI_ITEM_BEST_SIZE(name) void name(ztGuiItemID item_id, ztVec2 *min_size, ztVec2 *max_size, ztVec2 *size, ztGuiTheme *theme, void *user_data)
typedef ZT_FUNC_GUI_ITEM_BEST_SIZE(zt_guiItemBestSize_Func);

#define ZT_FUNC_GUI_ITEM_INPUT_KEY(name) bool name(ztGuiItemID item_id, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], void *user_data)
typedef ZT_FUNC_GUI_ITEM_INPUT_KEY(zt_guiItemInputKey_Func);

#define ZT_FUNC_GUI_ITEM_INPUT_MOUSE(name) bool name(ztGuiItemID item_id, ztInputMouse *input_mouse, void *user_data)
typedef ZT_FUNC_GUI_ITEM_INPUT_MOUSE(zt_guiItemInputMouse_Func);

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_GUI_BUTTON_PRESSED(name) void name(ztGuiItemID item_id)
typedef ZT_FUNC_GUI_BUTTON_PRESSED(zt_guiButtonPressed_Func);

#define ZT_FUNC_GUI_MENU_SELECTED(name) void name(ztGuiItemID item_id, i32 menu_item)
typedef ZT_FUNC_GUI_MENU_SELECTED(zt_guiMenuSelected_Func);

// ------------------------------------------------------------------------------------------------

struct ztGuiItemFunctions
{
	zt_guiItemUpdate_Func *update;
	zt_guiItemRender_Func *render;
	zt_guiItemCleanup_Func *cleanup;
	zt_guiItemBestSize_Func *best_size;
	zt_guiItemInputKey_Func *input_key;
	zt_guiItemInputMouse_Func *input_mouse;

	void *user_data;
};

// ------------------------------------------------------------------------------------------------

enum ztGuiWindowFlags_Enum
{
	ztGuiWindowFlags_ShowTitle     = (1 << 0),
	ztGuiWindowFlags_AllowDrag     = (1 << 1),
	ztGuiWindowFlags_AllowResize   = (1 << 2),
	ztGuiWindowFlags_AllowClose    = (1 << 3),
	ztGuiWindowFlags_AllowCollapse = (1 << 4),

	ztGuiWindowFlags_Default = ztGuiWindowFlags_ShowTitle | ztGuiWindowFlags_AllowDrag | ztGuiWindowFlags_AllowResize | ztGuiWindowFlags_AllowClose | ztGuiWindowFlags_AllowCollapse,
};

// ------------------------------------------------------------------------------------------------

enum ztGuiPanelFlags_Enum
{
	ztGuiPanelFlags_AllowDrag = (1 << 0),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiButtonFlags_Enum
{
	ztGuiButtonFlags_NoBackground = (1 << 0),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiCheckboxFlags_Enum
{
	ztGuiCheckboxFlags_RightText = (1 << 10),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiRadioButtonFlags_Enum
{
	ztGuiRadioButtonFlags_RightText = (1 << 10),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiTextEditFlags_Enum
{
	ztGuiTextEditFlags_MultiLine = (1<<31),
	ztGuiTextEditFlags_WordWrap  = (1<<30),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiItemOrient_Enum
{
	ztGuiItemOrient_Horz,
	ztGuiItemOrient_Vert,
};

// ------------------------------------------------------------------------------------------------

ztGuiManagerID zt_guiManagerMake(ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena);
void zt_guiManagerFree(ztGuiManagerID gui_manager);
void zt_guiManagerUpdate(ztGuiManagerID gui_manager, r32 dt);
bool zt_guiManagerHandleInput(ztGuiManagerID gui_manager, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], ztInputMouse *input_mouse);
void zt_guiManagerRender(ztGuiManagerID gui_manager, ztDrawList *draw_list);

void zt_guiSetActiveManager(ztGuiManagerID gui_manager);

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeWindow(const char *title, i32 flags = ztGuiWindowFlags_Default);
ztGuiItemID zt_guiMakePanel(ztGuiItemID parent, i32 item_flags = 0);
ztGuiItemID zt_guiMakeStaticText(ztGuiItemID parent, const char *label, i32 max_chars = 64);
ztGuiItemID zt_guiMakeButton(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeToggleButton(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeCheckbox(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeRadioButton(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeSlider(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItemID zt_guiMakeScrollbar(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItemID zt_guiMakeScrollContainer(ztGuiItemID parent);
ztGuiItemID zt_guiMakeTextEdit(ztGuiItemID parent, const char *value, i32 flags = 0, i32 buffer_size = 1024);
ztGuiItemID zt_guiMakeMenu();
ztGuiItemID zt_guiMakeTab(ztGuiItemID parent);
ztGuiItemID zt_guiMakeTree(ztGuiItemID parent);
ztGuiItemID zt_guiMakeProgressBar(ztGuiItemID parent, ztGuiItemOrient_Enum orient);

// ------------------------------------------------------------------------------------------------

void zt_guiItemFree(ztGuiItemID item_id);

void zt_guiItemSetSize(ztGuiItemID item_id, const ztVec2& size);
void zt_guiItemAutoSize(ztGuiItemID item_id);
void zt_guiItemSetPosition(ztGuiItemID item_id, const ztVec2& pos);
void zt_guiItemSetPosition(ztGuiItemID item_id, i32 align_flags, i32 anchor_flags, ztVec2 offset = ztVec2::zero);

void zt_guiItemSetName(ztGuiItemID item_id, const char *name);
void zt_guiItemSetLabel(ztGuiItemID item_id, const char *label);
void zt_guiItemSetTooltip(ztGuiItemID item_id, const char *tooltip);
void zt_guiItemSetThemeType(ztGuiItemID item_id, const char *theme_type);

ztString zt_guiItemGetName(ztGuiItemID item_id);
ztString zt_guiItemGetLabel(ztGuiItemID item_id);
ztString zt_guiItemGetTooltip(ztGuiItemID item_id);
ztString zt_guiItemGetThemeType(ztGuiItemID item_id);

void zt_guiItemSetAlign(ztGuiItemID item_id, i32 align_flags);
i32 zt_guiItemGetAlign(ztGuiItemID item_id);

bool zt_guiItemIsShowing(ztGuiItemID item_id);

void zt_guiItemShow(ztGuiItemID id, bool show = true);
void zt_guiItemHide(ztGuiItemID id);

void zt_guiItemBringToFront(ztGuiItemID id);

ztGuiItemID zt_guiItemGetTopLevelParent(ztGuiItemID item_id);
bool zt_guiItemIsChildOf(ztGuiItemID parent_id, ztGuiItemID child_id); // determine if the child is a descendent of the parent

ztVec2 zt_guiItemPositionLocalToScreen(ztGuiItemID item_id, const ztVec2& pos);
ztVec2 zt_guiItemPositionScreenToLocal(ztGuiItemID item_id, const ztVec2& pos);

void zt_guiItemSetFocus(ztGuiItemID item_id, ztGuiItemID *prev_focus_item_id = nullptr);

ztGuiTheme *zt_guiItemGetTheme(ztGuiItemID item_id);

void zt_guiItemLock(ztGuiItemID item_id);
void zt_guiItemUnlock(ztGuiItemID item_id);

void zt_guiItemReparent(ztGuiItemID item_id, ztGuiItemID new_parent);

// ------------------------------------------------------------------------------------------------

// used for button and toggle button
void zt_guiButtonSetIcon(ztGuiItemID button, ztSprite *icon);
void zt_guiButtonSetTextPosition(ztGuiItemID button, i32 align_flags);
void zt_guiButtonSetCallback(ztGuiItemID button, zt_guiButtonPressed_Func);

// ------------------------------------------------------------------------------------------------

bool zt_guiToggleButtonGetValue(ztGuiItemID button);
void zt_guiToggleButtonSetValue(ztGuiItemID button, bool value);

// ------------------------------------------------------------------------------------------------

bool zt_guiCheckboxGetValue(ztGuiItemID checkbox);
void zt_guiCheckboxSetValue(ztGuiItemID checkbox, bool value);

// ------------------------------------------------------------------------------------------------

bool zt_guiRadioButtonGetValue(ztGuiItemID radio);
void zt_guiRadioButtonSetValue(ztGuiItemID radio, bool value);

// ------------------------------------------------------------------------------------------------

r32 zt_guiSliderGetValue(ztGuiItemID slider);
void zt_guiSliderSetValue(ztGuiItemID slider, r32 value);

// ------------------------------------------------------------------------------------------------

r32 zt_guiScrollbarGetValue(ztGuiItemID scrollbar);
void zt_guiScrollbarSetValue(ztGuiItemID scrollbar, r32 value);
void zt_guiScrollbarSetSteps(ztGuiItemID scrollbar, r32 step_single, r32 step_page);
bool zt_guiScrollbarStepNeg(ztGuiItemID scrollbar);
bool zt_guiScrollbarStepPageNeg(ztGuiItemID scrollbar);
bool zt_guiScrollbarStepPos(ztGuiItemID scrollbar);
bool zt_guiScrollbarStepPagePos(ztGuiItemID scrollbar);
void zt_guiScrollbarSetPercent(ztGuiItemID scrollbar, r32 percent); // what percent of the total scrolled area is current displayed

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerSetItem(ztGuiItemID scroll, ztGuiItemID internal_item);
void zt_guiScrollContainerResetScroll(ztGuiItemID scroll);

// ------------------------------------------------------------------------------------------------

int zt_guiTextEditGetValue(ztGuiItemID text, char *buffer, int buffer_len);
void zt_guiTextEditSetValue(ztGuiItemID text, const char *value);

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppend(ztGuiItemID menu, const char *label, i32 id, ztSprite *icon = nullptr);
void zt_guiMenuAppendSubmenu(ztGuiItemID menu, const char *label, ztGuiItemID submenu, ztSprite *icon = nullptr);
void zt_guiMenuPopupAtItem(ztGuiItemID menu, ztGuiItemID item, i32 align_flags, const ztVec2& offset = ztVec2::zero);
void zt_guiMenuPopupAtPosition(ztGuiItemID menu, const ztVec2& pos);
bool zt_guiMenuGetSelected(ztGuiItemID menu, i32 *selected_id);
void zt_guiMenuSetCallback(ztGuiItemID menu, zt_guiMenuSelected_Func *on_selected);

// ------------------------------------------------------------------------------------------------

void zt_guiTabAddTab(ztGuiItemID tab, ztGuiItemID item, const char *tab_title, i32 flags = 0);

// ------------------------------------------------------------------------------------------------

typedef i32 ztGuiTreeNodeID;

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItemID tree, const char *item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID);
ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItemID tree, ztGuiItemID item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID);

ztGuiTreeNodeID zt_guiTreeGetSelected(ztGuiItemID tree);
void zt_guiTreeSetSelected(ztGuiItemID tree, ztGuiTreeNodeID node);

ztGuiTreeNodeID zt_guiTreeGetRoot(ztGuiItemID tree);
ztGuiItemID zt_guiTreeGetNodeItem(ztGuiItemID tree, ztGuiTreeNodeID node);
void *zt_guiTreeGetNodeUserData(ztGuiItemID tree, ztGuiTreeNodeID node);

void zt_guiTreeClear(ztGuiItemID tree);

// ------------------------------------------------------------------------------------------------

void zt_guiInitDebug(ztGuiManagerID gui_manager);


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

#if defined(ZT_GAME_GUI_IMPLEMENTATION) || defined(ZT_GAME_GUI_INTERNAL_DECLARATIONS)

#define ZT_GAME_INTERNAL_DECLARATIONS
#include "zt_game.h"

// GUI implementation

struct ztGuiItem
{
	ztGuiItemID id;
	ztGuiItemType_Enum type;

	ztString name;
	ztString label;
	ztString tooltip;
	ztString theme_type;

	ztVec2 size;
	ztVec2 pos;

	i32 align_flags;
	i32 anchor_flags;
	i32 pos_align_flags;
	i32 pos_anchor_flags;

	ztVec2 pos_offset;
	ztVec4 color;
	ztVec4 clip_area;

	i32 flags;

	ztGuiItem *parent;
	ztGuiItem *sib_next;
	ztGuiItem *sib_prev;
	ztGuiItem *first_child;

	ztGuiItemFunctions functions;
	ztGuiTheme *theme;

	zt_debugOnly(ztColor debug_highlight);

	ztDrawList *draw_list;

	struct ztDragState
	{
		bool dragging;
		r32 offset_x;
		r32 offset_y;
	};

	union {
		struct {
			i32 flags;
			i32 state_flags;
			ztDragState drag_state;
			// TODO(josh): need some way to keep track of focus on a per-window basis so switching back and forth between windows works as expected
		} window;

		struct {
			bool *live_value;
			i32 flags;
			zt_guiButtonPressed_Func *on_pressed;
			ztSprite *icon;
			i32 text_pos;
		} button;

		struct {
			r32 *live_value;
			r32 value;
			ztGuiItemOrient_Enum orient;
			r32 drag_pos[2];
			ztDragState drag_state;
			bool highlight;
			// scrollbar only
			int press_button;
			r32 press_time;
			r32 step, step_page, handle_pct;
		} slider;

		struct {
			ztGuiItemID scrollbar_vert;
			ztGuiItemID scrollbar_horz;
			ztGuiItemID viewport;
			ztGuiItemID contained_item;

			r32 scroll_amt_vert;
			r32 scroll_amt_horz;
			r32 viewport_pos[2];
			r32 viewport_size[2];
		} scrolled_container;

		struct {
			i32 cursor_pos;
			r32 cursor_blink_time;
			b32 cursor_vis;
			r32 cursor_xy[2];

			i32 select_beg;
			i32 select_end;

			bool dragging;

			ztGuiItemID scrollbar_vert;
			ztGuiItemID scrollbar_horz;

			r32 scroll_amt_vert;
			r32 scroll_amt_horz;

			ztString text_buffer;

			r32 content_size[2];
		} textedit;

		struct {
			ztString *display;
			i32 *ids;
			ztGuiItemID *submenus;
			ztSprite **icons;

			i32 item_count;
			i32 highlighted;
			i32 selected;
			bool just_opened;

			zt_guiMenuSelected_Func *on_selected;
		} menu;
	};
};

// ------------------------------------------------------------------------------------------------

enum ztGuiManagerItemCacheFlags_Enum
{
	ztGuiManagerItemCacheFlags_Used      = (1<<0),
	ztGuiManagerItemCacheFlags_MouseOver = (1<<1),
};

// ------------------------------------------------------------------------------------------------

struct ztGuiManager
{
	ztGuiItemID item_has_mouse;
	ztVec2 mouse_pos;
	bool   mouse_over_gui;
	bool   mouse_click;
	bool   mouse_click_ignored;
	bool   keyboard_focus;
	r32    last_input_time;

	i32 internal_flags;

	ztCamera *gui_camera;
	i32 gui_camera_w;
	i32 gui_camera_h;

	ztGuiItemID focus_item;

	ztGuiItemID tooltip_item;
	ztVec2 tooltip_pos;

	ztGuiItem *first_child;

	ztGuiItem item_cache[64 * 1024];
	i32 item_cache_flags[64 * 1024];

	ztGuiTheme default_theme;

	ztMemoryArena *arena;
	i32 base_id;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiGlobals
{
	ztGuiManager* gui_managers[4];
	ztGuiManagerID active_gui_manager;
};

// ------------------------------------------------------------------------------------------------

enum ztGuiManagerInternalFlags_Enum
{
	ztGuiManagerInternalFlags_OwnsTheme = (1 << 0),
};

// ------------------------------------------------------------------------------------------------

#if defined(ZT_GAME_GUI_INTERNAL_DECLARATIONS)
extern ztGuiGlobals *zt_gui;
#endif

// ------------------------------------------------------------------------------------------------

#endif // INTERNAL DECLARATIONS

#if defined(ZT_GAME_GUI_IMPLEMENTATION)

// ------------------------------------------------------------------------------------------------

ztGuiGlobals *zt_gui = nullptr;

// ------------------------------------------------------------------------------------------------

void zt_guiInitGlobalMemory(ztMemoryArena *arena)
{
	zt_gui = zt_mallocStructArena(ztGuiGlobals, arena);
	zt_memSet(zt_gui, zt_sizeof(ztGuiGlobals), 0);

	zt_gui->active_gui_manager = ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

void *zt_guiGetGlobalMemory(i32 *size)
{
	if(size) {
		*size = zt_sizeof(ztGuiGlobals);
	}

	return zt_gui;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSetGlobalMemory(void *mem)
{
	zt_gui = (ztGuiGlobals*)mem;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ztGuiManagerItemIDOffset	1000000

#define _zt_guiManagerCheckAndGet(gm_var, gui_manager_id) \
	zt_assert(gui_manager_id >= 0 && gui_manager_id < zt_elementsOf(zt_gui->gui_managers) && zt_gui->gui_managers[gui_manager_id] != nullptr); \
	ztGuiManager *gm_var = zt_gui->gui_managers[gui_manager_id];

#define _zt_guiManagerGetFromItem(gm_var, gui_item_id) \
	ztGuiManager *gm_var; \
	if (gui_item_id != ztInvalidID) { \
		i32 _gui_manager_idx = zt_convertToi32Floor((r32)gui_item_id / ztGuiManagerItemIDOffset); \
		zt_assert(_gui_manager_idx >= 0 && _gui_manager_idx < zt_elementsOf(zt_gui->gui_managers) && zt_gui->gui_managers[_gui_manager_idx] != nullptr); \
		gm_var = zt_gui->gui_managers[_gui_manager_idx]; \
												} else { \
		zt_assert(zt_gui->active_gui_manager >= 0 && zt_gui->active_gui_manager < zt_elementsOf(zt_gui->gui_managers) && zt_gui->gui_managers[zt_gui->active_gui_manager] != nullptr); \
		gm_var = zt_gui->gui_managers[zt_gui->active_gui_manager]; \
												}
#define _zt_guiItemFromID(gi_var, gui_item_id) \
	ztGuiItem *gi_var = nullptr; \
	if (gui_item_id != ztInvalidID) { \
		i32 _gui_manager_idx = zt_convertToi32Floor((r32)gui_item_id / ztGuiManagerItemIDOffset); \
		zt_assert(_gui_manager_idx >= 0 && _gui_manager_idx < zt_elementsOf(zt_gui->gui_managers) && zt_gui->gui_managers[_gui_manager_idx] != nullptr); \
		i32 _gui_item_idx = gui_item_id - (_gui_manager_idx * ztGuiManagerItemIDOffset); \
		gi_var = &zt_gui->gui_managers[_gui_manager_idx]->item_cache[_gui_item_idx]; }

#define _zt_guiItemTypeFromIDReturnOnError(gi_var, gui_item_id, gi_type) \
	_zt_guiItemFromID(gi_var, gui_item_id); \
	if (gi_var == nullptr) return; \
	zt_assert(gi_var->type == gi_type); \
	if (gi_var->type != gi_type) return;

#define _zt_guiItemTypeFromIDReturnValOnError(gi_var, gui_item_id, gi_type, ret_val) \
	_zt_guiItemFromID(gi_var, gui_item_id); \
	if (gi_var == nullptr) return ret_val; \
	zt_assert(gi_var->type == gi_type); \
	if (gi_var->type != gi_type) return ret_val;

#define _zt_guiItemAndManagerReturnOnError(gm_var, gi_var, item_id) \
		_zt_guiManagerGetFromItem(gm_var, item_id); \
		if (gm_var == nullptr) return; \
		_zt_guiItemFromID(gi_var, item_id); \
		if (gi_var == nullptr) return;

#define _zt_guiItemAndManagerReturnValOnError(gm_var, gi_var, item_id, ret_val) \
		_zt_guiManagerGetFromItem(gm_var, item_id); \
		if (gm_var == nullptr) return ret_val; \
		_zt_guiItemFromID(gi_var, item_id); \
		if (gi_var == nullptr) return ret_val;

// ------------------------------------------------------------------------------------------------

ztInternal byte *_zt_guiLoadDefaultTexture(i32 *size) {
	byte data[] = {
		0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00, 0xc5, 0x90, 0xce, 0x67, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x49, 0x6d, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 0x64, 0x79, 0x71, 0xc9, 0x65, 0x3c, 0x00, 0x00, 0x03, 0x64, 0x69, 0x54, 0x58, 0x74, 0x58, 0x4d, 0x4c, 0x3a, 0x63, 0x6f, 0x6d, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x78, 0x6d, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3f, 0x78, 0x70, 0x61, 0x63, 0x6b, 0x65, 0x74, 0x20, 0x62, 0x65, 0x67, 0x69, 0x6e, 0x3d, 0x22, 0xef, 0xbb, 0xbf, 0x22, 0x20, 0x69, 0x64, 0x3d, 0x22, 0x57, 0x35, 0x4d, 0x30, 0x4d, 0x70, 0x43, 0x65, 0x68, 0x69, 0x48, 0x7a, 0x72, 0x65, 0x53, 0x7a, 0x4e, 0x54, 0x63, 0x7a, 0x6b, 0x63, 0x39, 0x64, 0x22, 0x3f, 0x3e, 0x20, 0x3c, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x6d, 0x65, 0x74, 0x61, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x3d, 0x22, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x3a, 0x6e, 0x73, 0x3a, 0x6d, 0x65, 0x74, 0x61, 0x2f, 0x22, 0x20, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x74, 0x6b, 0x3d, 0x22, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x58, 0x4d, 0x50, 0x20, 0x43, 0x6f, 0x72, 0x65, 0x20, 0x35, 0x2e, 0x30, 0x2d, 0x63, 0x30, 0x36, 0x30, 0x20, 0x36, 0x31, 0x2e, 0x31, 0x33, 0x34, 0x37, 0x37, 0x37, 0x2c, 0x20, 0x32, 0x30, 0x31, 0x30, 0x2f, 0x30, 0x32, 0x2f, 0x31, 0x32, 0x2d, 0x31, 0x37, 0x3a, 0x33, 0x32, 0x3a, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x3e, 0x20, 0x3c, 0x72, 0x64, 0x66, 0x3a, 0x52, 0x44, 0x46, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x72, 0x64, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x31, 0x39, 0x39, 0x39, 0x2f, 0x30, 0x32, 0x2f, 0x32, 0x32, 0x2d, 0x72, 0x64, 0x66, 0x2d, 0x73, 0x79, 0x6e, 0x74, 0x61, 0x78, 0x2d, 0x6e, 0x73, 0x23, 0x22, 0x3e, 0x20, 0x3c, 0x72, 0x64, 0x66, 0x3a, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x72, 0x64, 0x66, 0x3a, 0x61, 0x62, 0x6f, 0x75, 0x74, 0x3d, 0x22, 0x22, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x78, 0x61, 0x70, 0x2f, 0x31, 0x2e, 0x30, 0x2f, 0x6d, 0x6d, 0x2f, 0x22, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x73, 0x74, 0x52, 0x65, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x78, 0x61, 0x70, 0x2f, 0x31, 0x2e, 0x30, 0x2f, 0x73, 0x54, 0x79, 0x70, 0x65, 0x2f, 0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x52, 0x65, 0x66, 0x23, 0x22, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x6d, 0x70, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x78, 0x61, 0x70, 0x2f, 0x31, 0x2e, 0x30, 0x2f, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x4f, 0x72, 0x69, 0x67, 0x69, 0x6e, 0x61, 0x6c, 0x44, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x64, 0x69, 0x64, 0x3a, 0x33, 0x34, 0x30, 0x46, 0x46, 0x41, 0x32, 0x38, 0x34, 0x44, 0x34, 0x46, 0x45, 0x36, 0x31, 0x31, 0x42, 0x31, 0x31, 0x32, 0x41, 0x41, 0x45, 0x31, 0x46, 0x43, 0x45, 0x36, 0x34, 0x31, 0x31, 0x39, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x44, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x64, 0x69, 0x64, 0x3a, 0x35, 0x33, 0x37, 0x46, 0x32, 0x45, 0x38, 0x34, 0x36, 0x44, 0x31, 0x41, 0x31, 0x31, 0x45, 0x36, 0x38, 0x38, 0x42, 0x43, 0x38, 0x33, 0x36, 0x32, 0x41, 0x42, 0x31, 0x36, 0x37, 0x39, 0x37, 0x46, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x49, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x69, 0x69, 0x64, 0x3a, 0x35, 0x33, 0x37, 0x46, 0x32, 0x45, 0x38, 0x33, 0x36, 0x44, 0x31, 0x41, 0x31, 0x31, 0x45, 0x36, 0x38, 0x38, 0x42, 0x43, 0x38, 0x33, 0x36, 0x32, 0x41, 0x42, 0x31, 0x36, 0x37, 0x39, 0x37, 0x46, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x3a, 0x43, 0x72, 0x65, 0x61, 0x74, 0x6f, 0x72, 0x54, 0x6f, 0x6f, 0x6c, 0x3d, 0x22, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x50, 0x68, 0x6f, 0x74, 0x6f, 0x73, 0x68, 0x6f, 0x70, 0x20, 0x43, 0x53, 0x35, 0x20, 0x57, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x73, 0x22, 0x3e, 0x20, 0x3c, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x44, 0x65, 0x72, 0x69, 0x76, 0x65, 0x64, 0x46, 0x72, 0x6f, 0x6d, 0x20, 0x73, 0x74, 0x52, 0x65, 0x66, 0x3a, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x69, 0x69, 0x64, 0x3a, 0x41, 0x33, 0x39, 0x36, 0x38, 0x43, 0x46, 0x39, 0x31, 0x35, 0x36, 0x44, 0x45, 0x36, 0x31, 0x31, 0x39, 0x30, 0x33, 0x33, 0x39, 0x42, 0x42, 0x37, 0x42, 0x38, 0x35, 0x32, 0x35, 0x43, 0x43, 0x32, 0x22, 0x20, 0x73, 0x74, 0x52, 0x65, 0x66, 0x3a, 0x64, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x64, 0x69, 0x64, 0x3a, 0x33, 0x34, 0x30, 0x46, 0x46, 0x41, 0x32, 0x38, 0x34, 0x44, 0x34, 0x46, 0x45, 0x36, 0x31, 0x31, 0x42, 0x31, 0x31, 0x32, 0x41, 0x41, 0x45, 0x31, 0x46, 0x43, 0x45, 0x36, 0x34, 0x31, 0x31, 0x39, 0x22, 0x2f, 0x3e, 0x20, 0x3c, 0x2f, 0x72, 0x64, 0x66, 0x3a, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x20, 0x3c, 0x2f, 0x72, 0x64, 0x66, 0x3a, 0x52, 0x44, 0x46, 0x3e, 0x20, 0x3c, 0x2f, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x6d, 0x65, 0x74, 0x61, 0x3e, 0x20, 0x3c, 0x3f, 0x78, 0x70, 0x61, 0x63, 0x6b, 0x65, 0x74, 0x20, 0x65, 0x6e, 0x64, 0x3d, 0x22, 0x72, 0x22, 0x3f, 0x3e, 0xe4, 0xfc, 0x8d, 0x8d, 0x00, 0x00, 0x17, 0xe9, 0x49, 0x44, 0x41, 0x54, 0x78, 0xda, 0xec, 0xdd, 0x7d, 0xac, 0x5c, 0x65, 0x9d, 0x07, 0xf0, 0xe7, 0x5c, 0xbb, 0x08, 0x21, 0x18, 0x2f, 0x6a, 0x16, 0x89, 0xdb, 0x68, 0x49, 0x4c, 0xc4, 0x75, 0x01, 0x8b, 0x28, 0x2a, 0x82, 0x49, 0xd1, 0x05, 0xd6, 0x75, 0x45, 0x8a, 0x9a, 0x60, 0xc4,
		0x26, 0xdb, 0x8a, 0xfe, 0xe1, 0x5f, 0x86, 0xdb, 0x2a, 0xa0, 0x46, 0xbb, 0xed, 0x5f, 0x9b, 0x86, 0xd5, 0xa5, 0x65, 0xed, 0xa2, 0x10, 0x13, 0x69, 0x83, 0x6b, 0x36, 0x2e, 0x68, 0x2b, 0xb4, 0x90, 0xfa, 0x4a, 0x05, 0x85, 0x42, 0x62, 0xa4, 0x20, 0x6b, 0x44, 0xa3, 0xa6, 0x2a, 0x8b, 0x56, 0x79, 0x99, 0xbd, 0xcf, 0x30, 0x53, 0xe6, 0x4e, 0xe7, 0xcc, 0x3c, 0xe7, 0xcc, 0x39, 0x73, 0x67, 0xe6, 0x7e, 0x3e, 0xc9, 0xf4, 0xf6, 0xde, 0x99, 0x33, 0x2f, 0x67, 0x66, 0xce, 0xef, 0xfb, 0x3c, 0xe7, 0x39, 0xcf, 0xc9, 0x36, 0x6e, 0xdc, 0xd8, 0x08, 0x8b, 0x68, 0xfd, 0xfa, 0xf5, 0xd9, 0xb6, 0x6d, 0xdb, 0x0a, 0x3d, 0x87, 0xb5, 0x6b, 0xd7, 0x66, 0xfb, 0xf6, 0xed, 0x2b, 0xb4, 0xcc, 0x9b, 0xde, 0xf4, 0xa6, 0x52, 0xcb, 0x5c, 0x72, 0xc9, 0x25, 0x85, 0x96, 0xd9, 0xb9, 0x73, 0x67, 0x56, 0xe4, 0xf6, 0x45, 0x5f, 0x7b, 0xe7, 0x3a, 0x88, 0x3f, 0x8b, 0xbe, 0xa6, 0xce, 0xd7, 0x56, 0xc5, 0xf2, 0x4b, 0xf5, 0xf9, 0x0f, 0x7a, 0x5d, 0x75, 0xdd, 0x2f, 0x40, 0x55, 0x96, 0xc5, 0x7f, 0x36, 0x6c, 0xd8, 0xf0, 0xe8, 0x62, 0x3c, 0xf8, 0x7c, 0xf8, 0x58, 0xde, 0xfe, 0xff, 0xba, 0x75, 0xeb, 0x92, 0x96, 0xd9, 0xba, 0x75, 0xeb, 0x91, 0xff, 0xdf, 0x75, 0xd7, 0x5d, 0x49, 0xcb, 0x9c, 0x73, 0xce, 0x39, 0xcf, 0x3d, 0xe6, 0xa6, 0x8d, 0x49, 0xcb, 0x6c, 0x98, 0xdb, 0xd0, 0xf9, 0x6b, 0xea, 0xc6, 0xb7, 0xd4, 0x46, 0xff, 0x9a, 0x6b, 0xae, 0x29, 0x74, 0xfb, 0x4f, 0x7d, 0xea, 0x53, 0x0b, 0x7e, 0x4f, 0x5d, 0x0f, 0xbd, 0xd6, 0x47, 0x91, 0x75, 0x92, 0xb3, 0x6e, 0x96, 0xdc, 0xf3, 0x4f, 0x7d, 0x5d, 0x75, 0xdd, 0x2f, 0x40, 0x65, 0x01, 0x60, 0xde, 0x5f, 0x59, 0x15, 0xd0, 0xdf, 0xf3, 0x9e, 0xf7, 0xbc, 0xf0, 0xf4, 0xd3, 0x4f, 0x5b, 0x11, 0xc0, 0x54, 0x98, 0xb1, 0x0a, 0x60, 0xb0, 0x0b, 0x2e, 0xb8, 0x20, 0xec, 0xd8, 0xb1, 0xa3, 0x92, 0xfb, 0x7a, 0xd5, 0xab, 0x5e, 0x15, 0xbe, 0xfc, 0xe5, 0x2f, 0x87, 0x57, 0xbe, 0xf2, 0x95, 0x56, 0x2c, 0x20, 0x00, 0xc0, 0x38, 0x8a, 0xc5, 0xfa, 0x96, 0x5b, 0x6e, 0x09, 0xdb, 0xb7, 0x6f, 0x0f, 0xcb, 0x97, 0x2f, 0xaf, 0xec, 0x7e, 0xdf, 0xfa, 0xd6, 0xb7, 0x86, 0xdb, 0x6f, 0xbf, 0x3d, 0x7c, 0xf6, 0xb3, 0x9f, 0x0d, 0x2f, 0x78, 0xc1, 0x0b, 0xac, 0x68, 0x40, 0x00, 0x60, 0x3a, 0xbc, 0xe2, 0x15, 0xaf, 0x08, 0x27, 0x9d, 0x74, 0x52, 0xe9, 0xe5, 0x67, 0x67, 0x67, 0xc3, 0x09, 0x27, 0x9c, 0x50, 0x7a, 0xf9, 0x93, 0x5f, 0x7a, 0x72, 0x78, 0xd1, 0x8b, 0x5e, 0x54, 0x7a, 0xf9, 0x17, 0xbe, 0xf0, 0x85, 0x61, 0xd3, 0xa6, 0x4d, 0x61, 0xd7, 0xae, 0x5d, 0xe1, 0xec, 0xb3, 0xcf, 0xae, 0x65, 0x1d, 0xc5, 0x5d, 0x0a, 0x6b, 0xd6, 0xac, 0x09, 0xdf, 0xfb, 0xde, 0xf7, 0xc2, 0x07, 0x3e, 0xf0, 0x81, 0xe6, 0xef, 0x00, 0x02, 0x00, 0x13, 0xed, 0xd3, 0x9f, 0xfe, 0x74, 0xb8, 0xea, 0xaa, 0xab, 0x4a, 0x2f, 0xbf, 0x6a, 0xd5, 0xaa, 0x66, 0x2b, 0xb9, 0xac, 0xb5, 0xff, 0xbc, 0x36, 0xac, 0xf9, 0xe0, 0x9a, 0x89, 0x28, 0xca, 0xed, 0xb0, 0x11, 0x7b, 0x04, 0xde, 0xfc, 0xe6, 0x37, 0xfb, 0xf0, 0x00, 0x02, 0x00, 0x93, 0x29, 0x16, 0xef, 0x78, 0xb9, 0xf8, 0xe2, 0x8b, 0xc3, 0x59, 0x67, 0x9d, 0x55, 0x78, 0xf9, 0x53, 0x4e, 0x39, 0xa5, 0x79, 0x39, 0xf5, 0xd4, 0x53, 0xc3, 0xcb, 0x5e, 0xf6, 0xb2, 0xc2, 0xcb, 0xbf, 0xee, 0x75, 0xaf, 0x6b, 0x5e, 0xce, 0x3b, 0xf7, 0xbc, 0xf0, 0xea, 0x53, 0x5f, 0x5d, 0x68, 0xd9, 0x38, 0xc8, 0xef, 0x0f, 0x7f, 0xf8, 0x43, 0x38, 0x7c, 0xf8, 0xf0, 0xc8, 0xd7, 0xdb, 0x13, 0x4f, 0x3c, 0xd1, 0xbc, 0x00, 0x08, 0x00, 0x4c, 0x9c, 0xd8, 0x62, 0xee, 0x6c, 0xf9, 0x7f, 0xfc, 0xe3, 0x1f, 0x2f, 0xb4, 0x7c, 0x96, 0x65, 0x0b, 0x5a, 0xfe, 0xe7, 0x9d, 0x77, 0x5e, 0xb1, 0x0f, 0xf4, 0xcc, 0xcc, 0x82, 0x96, 0x7f, 0x6c, 0xc5, 0x17, 0xb5, 0x73, 0xe7, 0xce, 0xf0, 0xc6, 0x37, 0xbe, 0x31, 0x6c, 0xd9, 0xb2, 0x25, 0x3c, 0xf9, 0xe4, 0x93, 0xb5, 0xaf, 0xb3, 0x5f, 0xfe, 0xf2, 0x97, 0xe1, 0x23, 0x1f, 0xf9, 0x48, 0xb8, 0xf0, 0xc2, 0x0b, 0xc3, 0x3d, 0xf7, 0xdc, 0xe3, 0x43, 0x04, 0x08, 0x00, 0x4c, 0x9e, 0xcb, 0x2e, 0xbb, 0x6c, 0xc1, 0xe8, 0xf6, 0xd8, 0x03, 0x10, 0x7b, 0x02, 0x52, 0x9d, 0x7e, 0xfa, 0xe9, 0xe1, 0xc5, 0x2f, 0x7e, 0xf1, 0x91, 0xdf, 0x63, 0x0f, 0x40, 0xec, 0x09, 0x48, 0x75, 0xc1, 0xdf, 0x5f, 0x10, 0x96, 0xff, 0xcd, 0x73, 0x83, 0xf5, 0x62, 0x0f, 0x40, 0xec, 0x09, 0x28, 0xd3, 0x1a, 0x8f, 0xdd, 0xf2, 0xe7, 0x9e, 0x7b, 0x6e, 0xb8, 0xf5, 0xd6, 0x5b, 0x6b, 0x59, 0x57, 0xb1, 0x97, 0x21, 0x86, 0x8c, 0xd8, 0xed, 0x1f, 0x07, 0x1a, 0x02, 0x08, 0x00, 0x4c, 0xa4, 0xb8, 0x2f, 0x7b, 0x6e, 0x6e, 0xee, 0xa8, 0xbf, 0xc7, 0x1e, 0x81, 0xe3, 0x8f, 0x3f, 0x7e, 0xe0, 0xf2, 0xc7, 0x1e, 0x7b, 0x6c, 0xb3, 0xe0, 0x76, 0x8b, 0x3d, 0x02, 0xc7, 0x1c, 0x73, 0xcc, 0xc0, 0xe5, 0xe3, 0xa0, 0xc1, 0xf7, 0x5f, 0xf6, 0xfe, 0xa3, 0xfe, 0x1e, 0x7b, 0x04, 0x8e, 0x3b, 0xf6, 0xb8, 0x52, 0xaf, 0xe9, 0xe1, 0x87, 0x1f, 0x6e, 0x8e, 0x09, 0x78, 0xef, 0x7b, 0xdf, 0x1b, 0x7e, 0xf2, 0x93, 0x9f, 0x54, 0xb6, 0xae, 0x62, 0xa8, 0x88, 0x85, 0x3f, 0x86, 0x0c, 0xdd, 0xfe, 0xc0, 0x62, 0x58, 0x36, 0x2e, 0x4f, 0xa4, 0x73, 0x86, 0xbf, 0x54, 0xdd, 0x33, 0xc2, 0xa5, 0xe8, 0x9e, 0x05, 0x2e, 0x51, 0xc3, 0x47, 0x65, 0xb0, 0x58, 0xfc, 0x63, 0x08, 0xe8, 0x16, 0x8f, 0x06, 0xf8, 0xe8, 0x47, 0x3f, 0x1a, 0x67, 0x7e, 0xec, 0xbb, 0x7c, 0x2c, 0xfe, 0x31, 0x04, 0xf4, 0x2a, 0xec, 0xb1, 0x4b, 0x7e, 0xcf, 0x9e, 0x3d, 0x7d, 0x97, 0x8f, 0xc5, 0xbf, 0xd7, 0x91, 0x03, 0xf1, 0x68, 0x80, 0xf7, 0xbc, 0xe7, 0x3d, 0xe1, 0x86, 0x2f, 0xde, 0x50, 0xfa, 0xb5, 0xed, 0xdd, 0xbb, 0xb7, 0x79, 0xa9, 0xc2, 0x83, 0x0f, 0x3e, 0xd8, 0x0c, 0x15, 0x00, 0x4b, 0x3e, 0x00, 0x94, 0x99, 0xe7, 0xbc, 0x3d, 0x97, 0x7b, 0xdd, 0xcb, 0x14, 0x9d, 0xdb, 0x7f, 0xa9, 0x8a, 0xfb, 0xfe, 0x7f, 0xfc, 0xe3, 0x1f, 0x87, 0x8f, 0x7d, 0xec, 0x63, 0x3d, 0xaf, 0x1f, 0xb4, 0x2f, 0x3d, 0xee, 0xfb, 0x8f, 0xfb, 0xc2, 0x6f, 0xbb, 0xed, 0xb6, 0x9e, 0xd7, 0x0f, 0x9a, 0x81, 0x2f, 0xee, 0xfb, 0xff, 0xe9, 0x4f, 0x7f, 0x1a, 0xae, 0xfd, 0xdc, 0xb5, 0x3d, 0xaf, 0x7f, 0xea, 0xc9, 0xa7, 0xbc, 0x49, 0x00, 0xe3, 0xd8, 0x03, 0xc0, 0x64, 0x8b, 0x05, 0x3a, 0xce, 0x6e, 0x57, 0x56, 0xa3, 0xd1, 0x08, 0x3f, 0xfa, 0xd1, 0x8f, 0x4a, 0x2f, 0xff, 0xcc, 0x33, 0xcf, 0x84, 0x6f, 0xee, 0xfa, 0x66, 0xa9, 0x65, 0xeb, 0x9a, 0x6b, 0xdf, 0x1c, 0xfe, 0x80, 0x00, 0x50, 0x42, 0xde, 0xd9, 0xd4, 0xf2, 0x7a, 0x0b, 0xf6, 0xed, 0xdb, 0x77, 0x54, 0x4d, 0xc9, 0x6b, 0x6c, 0x76, 0xf5, 0x0a, 0x34, 0x7f, 0x5e, 0xf4, 0x8e, 0x8b, 0x16, 0xdc, 0x68, 0xc3, 0xdc, 0x86, 0xdc, 0xe5,
		0x3b, 0x4f, 0x3e, 0xf3, 0xf5, 0xff, 0xfe, 0xba, 0x4f, 0xd1, 0x04, 0xab, 0xeb, 0x2c, 0x7b, 0xce, 0xde, 0x07, 0x08, 0x00, 0x25, 0x8b, 0x7f, 0x9f, 0x33, 0xa9, 0x35, 0xf2, 0x36, 0xae, 0xed, 0xb3, 0xca, 0x9d, 0x73, 0xce, 0x39, 0x8d, 0xbc, 0x33, 0xcc, 0xb5, 0xae, 0xcb, 0x5a, 0xff, 0xef, 0x79, 0x9b, 0x58, 0xfc, 0xf3, 0xce, 0x30, 0x17, 0xaf, 0x9b, 0xbf, 0x64, 0x45, 0xcf, 0x40, 0x07, 0x00, 0x02, 0x40, 0xf9, 0xe2, 0xdf, 0x3e, 0xc5, 0x6a, 0x6e, 0x08, 0xe8, 0x57, 0xfc, 0xdb, 0x21, 0xa1, 0x33, 0x04, 0x14, 0x29, 0xfe, 0x51, 0xbc, 0x4e, 0x08, 0x98, 0x1e, 0xfb, 0xf6, 0xed, 0xab, 0x74, 0x80, 0x67, 0x7b, 0x9c, 0x49, 0x5d, 0xf7, 0x0b, 0x30, 0x95, 0x01, 0x60, 0x50, 0xf1, 0x1f, 0x14, 0x02, 0x06, 0x15, 0xff, 0xee, 0x10, 0x10, 0xba, 0x76, 0x07, 0x0c, 0x2a, 0xfe, 0xbd, 0x42, 0x40, 0x9f, 0x9b, 0x75, 0x17, 0x00, 0x1b, 0xf0, 0x31, 0x95, 0xf2, 0x99, 0x49, 0xd1, 0xdd, 0xa3, 0x54, 0xd7, 0xfd, 0x02, 0x54, 0x61, 0x6c, 0xe6, 0x01, 0x48, 0x2d, 0xfe, 0x9d, 0x21, 0xa0, 0x6b, 0x9c, 0x40, 0xa3, 0xc8, 0x06, 0xb7, 0x75, 0xdb, 0x46, 0xd1, 0xe2, 0xdf, 0x19, 0x02, 0x42, 0xfe, 0x38, 0x83, 0x46, 0xe2, 0xdf, 0x98, 0x20, 0xf1, 0x48, 0x05, 0x00, 0x3d, 0x00, 0xa4, 0xb6, 0xfc, 0xbb, 0xaf, 0x9b, 0xba, 0x2a, 0x32, 0xec, 0x68, 0xf7, 0x61, 0x5b, 0xb8, 0x25, 0xe7, 0x76, 0x28, 0x24, 0xce, 0x6e, 0x78, 0xe6, 0x99, 0x67, 0x0e, 0x75, 0xa4, 0x43, 0xdb, 0x4b, 0x5e, 0xf2, 0x92, 0x23, 0xa7, 0x03, 0xfe, 0xcd, 0x6f, 0x7e, 0xe3, 0x1b, 0x03, 0x08, 0x00, 0x4b, 0xb5, 0x61, 0x39, 0x5f, 0x40, 0x93, 0x7b, 0x3f, 0x5a, 0xc5, 0xf6, 0x48, 0x88, 0x38, 0x70, 0xe0, 0x40, 0x96, 0xba, 0xeb, 0xa3, 0x5d, 0x6c, 0xe3, 0x32, 0xed, 0xa3, 0x1f, 0xe2, 0x7d, 0x15, 0xe9, 0xfd, 0x68, 0x15, 0xdb, 0x23, 0x8f, 0x3f, 0xec, 0x68, 0xf7, 0x61, 0xf7, 0x6d, 0xd7, 0xbd, 0x6f, 0x3c, 0x16, 0xeb, 0xf3, 0xcf, 0x3f, 0x3f, 0x2c, 0x5f, 0xbe, 0xbc, 0x79, 0x92, 0xa0, 0xaa, 0xac, 0x58, 0xb1, 0xa2, 0x79, 0xca, 0xe4, 0x1f, 0xfe, 0xf0, 0x87, 0xe1, 0xce, 0x3b, 0xef, 0x0c, 0x7f, 0xfe, 0xf3, 0x9f, 0x7d, 0x13, 0x80, 0x91, 0x32, 0x15, 0xf0, 0x18, 0x98, 0x2f, 0xfe, 0x59, 0x4a, 0x2b, 0x3a, 0xde, 0x26, 0xde, 0xb6, 0xfb, 0xef, 0x71, 0x40, 0x63, 0x4a, 0x2b, 0x3a, 0xde, 0x26, 0x67, 0xf0, 0x63, 0x96, 0xd2, 0x8a, 0xee, 0x2e, 0xfe, 0xd3, 0x2c, 0xce, 0x48, 0xf8, 0xf6, 0xb7, 0xbf, 0xbd, 0x39, 0x63, 0x5f, 0x2c, 0xfe, 0xb5, 0x24, 0xbf, 0x2c, 0x0b, 0x2b, 0x57, 0xae, 0x0c, 0x57, 0x5c, 0x71, 0x45, 0x38, 0xe3, 0x8c, 0x33, 0xec, 0x62, 0x00, 0xf4, 0x00, 0x2c, 0x25, 0xf3, 0x2d, 0xe8, 0xe6, 0x78, 0x86, 0x56, 0x08, 0xc8, 0xed, 0x09, 0xc8, 0x2b, 0xfe, 0x71, 0xf9, 0x38, 0x9f, 0x7c, 0x2b, 0x04, 0xf4, 0x3b, 0xfc, 0xb1, 0x67, 0xf1, 0x6f, 0x0d, 0x68, 0x1c, 0xd8, 0x13, 0x90, 0x57, 0xfc, 0xf3, 0xe6, 0x6b, 0x48, 0x78, 0xdd, 0x43, 0x8d, 0x96, 0x1f, 0x76, 0xb4, 0x7d, 0x5e, 0xcf, 0x41, 0x2c, 0xc2, 0xaf, 0x7d, 0xed, 0x6b, 0xc3, 0x5b, 0xde, 0xf2, 0x96, 0xf0, 0xfc, 0xe7, 0x3f, 0x7f, 0xa4, 0x61, 0x23, 0x86, 0x81, 0x5d, 0xbb, 0x76, 0x85, 0x9f, 0xfd, 0xec, 0x67, 0xbe, 0x18, 0x80, 0x00, 0x30, 0x81, 0x62, 0x61, 0x49, 0x9a, 0x84, 0x28, 0xa7, 0x27, 0xe0, 0xa8, 0x10, 0xd0, 0x5d, 0xfc, 0x63, 0xd1, 0xef, 0x25, 0x2f, 0x04, 0x74, 0x17, 0xff, 0xee, 0xe5, 0x07, 0x85, 0x80, 0xee, 0xe2, 0x1f, 0xaf, 0xef, 0x9c, 0x00, 0xa9, 0xc8, 0xe0, 0xcd, 0xf6, 0xeb, 0xe9, 0x7a, 0xde, 0x85, 0x96, 0xef, 0xee, 0xed, 0x28, 0x7a, 0x38, 0x66, 0xbf, 0xde, 0x8e, 0x38, 0x23, 0x61, 0xec, 0x8e, 0x7f, 0xea, 0xa9, 0xa7, 0x46, 0x16, 0x00, 0xda, 0xe2, 0x74, 0xc9, 0x7f, 0xf9, 0xcb, 0x5f, 0x7c, 0x83, 0x80, 0xa5, 0x15, 0x00, 0x5a, 0x2d, 0xc2, 0x42, 0xfb, 0xc2, 0xbb, 0xf6, 0x3f, 0x17, 0xde, 0x17, 0xde, 0x55, 0x90, 0x87, 0xda, 0x17, 0x9e, 0x10, 0x02, 0x72, 0x8b, 0xff, 0x63, 0x8f, 0x3d, 0xd6, 0x6e, 0x4d, 0x37, 0x6f, 0x17, 0x43, 0x40, 0xf7, 0xb2, 0xed, 0xa2, 0xd9, 0xab, 0xf8, 0xb7, 0xcf, 0xc0, 0x17, 0x97, 0x6f, 0x8f, 0x09, 0xe8, 0xbc, 0x3e, 0xfe, 0xed, 0xc4, 0x13, 0x4f, 0xec, 0x1b, 0x1e, 0xba, 0x43, 0x40, 0xde, 0x73, 0x5f, 0x0a, 0x73, 0x1f, 0xdc, 0x7f, 0xff, 0xfd, 0xcd, 0x33, 0xff, 0xbd, 0xe1, 0x0d, 0x6f, 0x08, 0xaf, 0x7f, 0xfd, 0xeb, 0x9b, 0xe7, 0x39, 0xa8, 0xd3, 0xe3, 0x8f, 0x3f, 0x1e, 0xee, 0xb8, 0xe3, 0x8e, 0xf0, 0xc0, 0x03, 0x0f, 0xd8, 0x22, 0x01, 0x23, 0x0f, 0x00, 0x4f, 0x4e, 0x52, 0x08, 0xe8, 0x51, 0xfc, 0xfb, 0xb6, 0x80, 0x7b, 0x15, 0xff, 0x9c, 0xfd, 0xe6, 0x49, 0x21, 0x20, 0x71, 0x5f, 0x78, 0x56, 0xe2, 0xf5, 0x97, 0x5e, 0xb6, 0xdf, 0xf2, 0x1d, 0x03, 0xfe, 0x8e, 0x92, 0x33, 0x95, 0x71, 0x56, 0xf0, 0xf6, 0x53, 0x27, 0xb6, 0xc4, 0xe3, 0xe0, 0xbc, 0xfb, 0xee, 0xbb, 0xaf, 0x39, 0x62, 0x3f, 0x1e, 0x05, 0x50, 0xb5, 0xd8, 0xcb, 0xf0, 0xfd, 0xef, 0x7f, 0x3f, 0x7c, 0xf7, 0xbb, 0xdf, 0xd5, 0xf2, 0x07, 0x16, 0x27, 0x00, 0x6c, 0xdc, 0xb8, 0x71, 0xf9, 0xb8, 0x3c, 0xa1, 0x41, 0x21, 0x20, 0xaf, 0xf8, 0xa7, 0x86, 0x80, 0xba, 0xf6, 0x85, 0x33, 0x9d, 0x0e, 0x1d, 0x3a, 0x14, 0x6e, 0xb9, 0xe5, 0x96, 0xf0, 0xf2, 0x97, 0xbf, 0x3c, 0x9c, 0x75, 0xd6, 0x59, 0x95, 0xdd, 0x6f, 0xec, 0x61, 0xd8, 0xbd, 0x7b, 0x77, 0xa5, 0x47, 0x16, 0x00, 0x14, 0x0e, 0x00, 0x1b, 0x36, 0x6c, 0x58, 0x94, 0xd3, 0x96, 0xcd, 0x07, 0x8f, 0x6b, 0xfa, 0x85, 0x80, 0x3e, 0xd7, 0xe5, 0x16, 0xf7, 0x76, 0x0b, 0xb6, 0xbb, 0x1b, 0xbc, 0xb3, 0x75, 0x9b, 0x37, 0x62, 0x7e, 0x40, 0x37, 0xf8, 0x51, 0xad, 0xe3, 0xee, 0x7d, 0xe1, 0x4c, 0xaf, 0x47, 0x1e, 0x79, 0xa4, 0x79, 0xa9, 0xc2, 0xaf, 0x7f, 0xfd, 0xeb, 0x66, 0xa8, 0x00, 0x58, 0xf4, 0x00, 0x30, 0x8e, 0x8a, 0x1e, 0x5f, 0xde, 0xa3, 0x9b, 0xbb, 0xd0, 0xf2, 0x3d, 0x0a, 0x79, 0x56, 0x62, 0x19, 0x00, 0x10, 0x00, 0x60, 0x12, 0xd4, 0x35, 0xd7, 0xbe, 0x39, 0xfc, 0x01, 0x01, 0x80, 0xd2, 0x8a, 0x1e, 0x67, 0x1f, 0x7b, 0x4e, 0x8a, 0x1e, 0x1b, 0x1f, 0x8f, 0x89, 0x2f, 0xb3, 0x4c, 0xe7, 0xef, 0x71, 0xa4, 0xfc, 0x55, 0x57, 0x5d, 0x15, 0x8e, 0x3f, 0xfe, 0xf8, 0x9e, 0xb7, 0x8f, 0xfb, 0xd2, 0x37, 0x6e, 0xcc, 0x1f, 0x5c, 0x19, 0x8f, 0xbf, 0x8f, 0x83, 0xed, 0x8e, 0x39, 0xe6, 0x98, 0x9e, 0xd7, 0x1f, 0x3e, 0x7c, 0x38, 0xec, 0xd9, 0xb3, 0x27, 0x77, 0xf9, 0x99, 0x99, 0x99, 0xb0, 0xe6, 0x83, 0x6b, 0xc2, 0x71, 0xc7, 0x1e, 0xd7, 0xf3, 0xfa, 0xc7, 0xff, 0xef, 0xf1, 0x70, 0xc3, 0x17, 0x6f, 0x18, 0xf8, 0x3a, 0xaa, 0xe2, 0xec, 0x7d, 0xc0, 0x44, 0x04, 0x80, 0xbc, 0x7d, 0xf1, 0x8c, 0x87, 0xed, 0xdb, 0xb7, 0x27, 0xdd, 0x2e, 0xce, 0x5a,
		0xd7, 0x56, 0xf0, 0x70, 0xc8, 0xa6, 0x4b, 0x2e, 0xb9, 0x24, 0x69, 0x99, 0x9d, 0x3b, 0x77, 0x1e, 0xf5, 0xb7, 0xa7, 0x9f, 0x7e, 0x3a, 0xfc, 0xf6, 0xb7, 0xbf, 0x0d, 0xeb, 0xd6, 0xad, 0xeb, 0xb9, 0x4c, 0xfb, 0x50, 0xc5, 0x3c, 0xf1, 0xf8, 0xfb, 0x3f, 0xfe, 0xf1, 0x8f, 0xb9, 0x03, 0xed, 0xbe, 0xf1, 0x8d, 0x6f, 0xf4, 0x5d, 0xfe, 0x99, 0x67, 0x9e, 0x09, 0xbf, 0xff, 0xfd, 0xef, 0xc3, 0xbb, 0xfe, 0xe9, 0x5d, 0x3d, 0xaf, 0xff, 0xfc, 0xbf, 0x7f, 0xde, 0x07, 0x09, 0xa0, 0x33, 0x00, 0xac, 0x5f, 0xbf, 0x5e, 0x4b, 0x85, 0x4a, 0x5c, 0x77, 0xdd, 0x75, 0xe1, 0x7d, 0xef, 0x7b, 0x5f, 0x73, 0x8e, 0xfb, 0x4e, 0x07, 0x0e, 0x1c, 0x08, 0x37, 0xdd, 0x74, 0xd3, 0xc0, 0xe5, 0x7f, 0xf0, 0x83, 0x1f, 0x84, 0xd3, 0x4e, 0x3b, 0x2d, 0xcc, 0xce, 0xce, 0x2e, 0xf8, 0xfb, 0xaf, 0x7e, 0xf5, 0xab, 0x70, 0xef, 0xbd, 0xf7, 0x0e, 0x5c, 0xfe, 0xab, 0xff, 0xf5, 0xd5, 0xf0, 0xb6, 0xb7, 0xbd, 0x2d, 0x9c, 0xfc, 0xd2, 0x93, 0x17, 0xfc, 0xfd, 0xe0, 0xc1, 0x83, 0xe1, 0xd6, 0xdb, 0x6e, 0xed, 0xb9, 0x4c, 0xd9, 0x99, 0x04, 0x07, 0xb5, 0xfc, 0xeb, 0xba, 0x5f, 0x80, 0x4a, 0x7b, 0x00, 0xa0, 0x0a, 0x71, 0x26, 0xbb, 0xab, 0xaf, 0xbe, 0x3a, 0xdc, 0x78, 0xe3, 0x8d, 0x0b, 0xfe, 0xbe, 0x61, 0xc3, 0x86, 0x66, 0x0f, 0xc1, 0x20, 0xf1, 0x36, 0xf1, 0xd0, 0xb8, 0xd5, 0xab, 0x57, 0x2f, 0xf8, 0x7b, 0x9c, 0x1e, 0x37, 0xf6, 0x10, 0x0c, 0x12, 0x8f, 0xab, 0xdf, 0x76, 0xfd, 0xb6, 0xf0, 0xc9, 0xab, 0x3f, 0xb9, 0x30, 0x98, 0x6c, 0xbd, 0xae, 0xd9, 0x43, 0x90, 0xa7, 0xaa, 0xc9, 0x8d, 0xba, 0x67, 0x18, 0xac, 0xeb, 0x7e, 0x01, 0xc6, 0x3a, 0x00, 0x94, 0x9d, 0x23, 0xbe, 0x8f, 0x9e, 0xf3, 0xe0, 0xd7, 0xd1, 0xda, 0xea, 0xf5, 0x58, 0xed, 0xa3, 0x0c, 0x46, 0xf9, 0x58, 0x93, 0x28, 0x16, 0xf0, 0xef, 0x7c, 0xe7, 0x3b, 0xe1, 0xec, 0xb3, 0xcf, 0x6e, 0xfe, 0xfe, 0xb5, 0xaf, 0x7d, 0xad, 0x39, 0xd9, 0x4d, 0xaa, 0x87, 0x1e, 0x7a, 0x28, 0x3c, 0xfa, 0xe8, 0xa3, 0x47, 0x4e, 0xc0, 0xf3, 0xe0, 0x83, 0x0f, 0x86, 0x9f, 0xff, 0xfc, 0xe7, 0xc9, 0xcb, 0xc7, 0x5e, 0x84, 0xfb, 0xee, 0xbf, 0x2f, 0xbc, 0xe6, 0x6f, 0x5f, 0xd3, 0xfc, 0xfd, 0xce, 0xbb, 0xee, 0x0c, 0x07, 0x1e, 0x38, 0x50, 0xc9, 0x6b, 0x8b, 0xe3, 0x0c, 0xfa, 0x05, 0x09, 0x00, 0x01, 0xa0, 0xa5, 0xe8, 0x1c, 0xf1, 0xfd, 0xb4, 0xa6, 0xc7, 0xed, 0x37, 0x01, 0x50, 0x65, 0x8f, 0xd5, 0x9a, 0x43, 0x20, 0xab, 0xbb, 0xc5, 0xd8, 0x6a, 0xdd, 0xf5, 0x7d, 0xac, 0x49, 0x14, 0x07, 0x03, 0xc6, 0x7d, 0xf6, 0xb1, 0x58, 0x6e, 0xde, 0xbc, 0xb9, 0xf0, 0xf2, 0xdf, 0xfa, 0xd6, 0xb7, 0xc2, 0xe5, 0x97, 0x5f, 0xde, 0x5c, 0x3e, 0xce, 0xc6, 0x57, 0x38, 0x7c, 0x5e, 0xbf, 0x2d, 0x6c, 0xf9, 0xd7, 0x2d, 0xcd, 0xe5, 0xbb, 0x7b, 0x23, 0xca, 0x8a, 0x81, 0xe6, 0x9d, 0xff, 0xf8, 0xce, 0x30, 0xb7, 0x7e, 0x6e, 0xe8, 0xfb, 0x8a, 0x93, 0x0a, 0xad, 0xb9, 0x7c, 0x4d, 0xf8, 0x8f, 0x2f, 0xfc, 0x47, 0x78, 0xf4, 0x7f, 0x1f, 0xb5, 0x15, 0x02, 0x16, 0xc5, 0xc4, 0x9c, 0x0e, 0xb8, 0x15, 0x26, 0x1a, 0xa3, 0x78, 0xac, 0x56, 0x98, 0x18, 0xc9, 0x63, 0xb5, 0xc2, 0x44, 0x63, 0x9a, 0x3e, 0x54, 0xed, 0x7d, 0xfe, 0x71, 0x4c, 0xc0, 0xc3, 0x0f, 0x3f, 0x5c, 0x78, 0xf9, 0xf6, 0x3e, 0xff, 0xd8, 0x9a, 0x8f, 0x47, 0x0f, 0x14, 0xd5, 0xde, 0xe7, 0x1f, 0xc7, 0x04, 0xfc, 0xe2, 0xb1, 0x5f, 0x0c, 0x5d, 0xac, 0x37, 0xfd, 0xcb, 0xa6, 0xf0, 0x89, 0x0d, 0x9f, 0x08, 0x27, 0xfd, 0xf5, 0x49, 0x95, 0xad, 0xa3, 0x78, 0xe6, 0xbf, 0xcf, 0xfd, 0xdb, 0xe7, 0xc2, 0x87, 0xd6, 0x7d, 0x28, 0xf7, 0xc8, 0x09, 0x00, 0x01, 0x40, 0x08, 0x98, 0x38, 0xf1, 0x14, 0xc5, 0x5b, 0xb6, 0x6c, 0x29, 0xbd, 0xfc, 0xde, 0xbd, 0x7b, 0xc3, 0xb7, 0xbf, 0xfd, 0xed, 0xd2, 0xcb, 0xdf, 0x78, 0xd3, 0x8d, 0xe1, 0x2b, 0x5f, 0xf9, 0x4a, 0xe9, 0xe5, 0x4f, 0x38, 0xe1, 0x84, 0xf0, 0xe1, 0x2b, 0x3e, 0x1c, 0xae, 0xdd, 0x72, 0xed, 0x91, 0xdd, 0x09, 0x95, 0x7f, 0xf9, 0x66, 0x66, 0xc2, 0x3b, 0xfe, 0xe1, 0x1d, 0xe1, 0x0b, 0xd7, 0x7f, 0x21, 0x5c, 0x74, 0xe1, 0x45, 0xcd, 0xdf, 0x01, 0x26, 0x25, 0x00, 0xac, 0x10, 0x02, 0x84, 0x80, 0x5e, 0x7e, 0xf7, 0xbb, 0xdf, 0x85, 0x27, 0x9e, 0x78, 0xa2, 0xf4, 0xf2, 0xf1, 0xb8, 0xff, 0x61, 0x4e, 0x90, 0x13, 0xcf, 0xb0, 0xf7, 0xa7, 0xc3, 0x7f, 0x9a, 0x88, 0xa2, 0xdc, 0x0e, 0x1b, 0xb1, 0x47, 0xe0, 0xb4, 0xbf, 0x3b, 0xcd, 0x56, 0x09, 0x18, 0xfb, 0x00, 0x70, 0xf3, 0xfc, 0xe5, 0xa1, 0xf9, 0xcb, 0x95, 0x42, 0x80, 0x10, 0x30, 0x2d, 0xe2, 0xb8, 0x81, 0x18, 0x5c, 0x16, 0xe3, 0xec, 0x7c, 0x87, 0xff, 0x74, 0xb8, 0x54, 0x68, 0x01, 0x28, 0xa3, 0xec, 0x20, 0xc0, 0x58, 0xfc, 0xdb, 0xc7, 0x6a, 0x6d, 0x6a, 0xfd, 0xdc, 0x6c, 0x75, 0x32, 0x0d, 0x6e, 0xbf, 0xe3, 0xf6, 0xe6, 0x91, 0x0c, 0xf1, 0x70, 0xc4, 0x77, 0x5f, 0xfc, 0xee, 0xb0, 0x6c, 0x59, 0xbd, 0x47, 0xcb, 0xc6, 0x09, 0x94, 0xb6, 0xff, 0xe7, 0xf6, 0xb0, 0x67, 0xef, 0x1e, 0x2b, 0x1f, 0x18, 0xeb, 0x00, 0xd0, 0x59, 0xfc, 0xdb, 0x56, 0x0b, 0x00, 0xf5, 0xe9, 0x9c, 0xe1, 0x2f, 0x55, 0x99, 0x79, 0xe8, 0x7b, 0xcd, 0xf0, 0x97, 0x22, 0x9e, 0xa2, 0x79, 0x18, 0xc3, 0xce, 0x99, 0x5f, 0xc7, 0x71, 0xf2, 0xb1, 0x25, 0xfe, 0xa5, 0x1b, 0xbf, 0xd4, 0x3c, 0xac, 0x31, 0x4e, 0x31, 0xdc, 0x3e, 0xac, 0xb1, 0x4a, 0xb1, 0x97, 0x21, 0x0e, 0x54, 0xdc, 0xb1, 0x63, 0x87, 0x96, 0x3f, 0xb0, 0xe8, 0x01, 0x20, 0xee, 0xd3, 0x8f, 0x07, 0xd7, 0x6f, 0x9b, 0xbf, 0x1c, 0x4c, 0x2c, 0xfe, 0xf1, 0x76, 0x97, 0x5a, 0x95, 0xf5, 0x28, 0x7a, 0x56, 0xc4, 0xa8, 0xcc, 0xac, 0x71, 0x65, 0x67, 0x9a, 0x2b, 0xf3, 0xfc, 0xaa, 0x78, 0xdc, 0xaa, 0x96, 0x1f, 0x24, 0x1e, 0x45, 0xf0, 0x99, 0x8d, 0x9f, 0x09, 0x67, 0x9c, 0x7e, 0x46, 0xee, 0x34, 0xc3, 0x65, 0xc4, 0x1e, 0x86, 0xad, 0xd7, 0x6f, 0x6d, 0x9e, 0x1a, 0x18, 0x60, 0xb1, 0x03, 0x40, 0x2c, 0xfe, 0xbb, 0x5a, 0x3f, 0x63, 0x91, 0x3f, 0xbf, 0x2b, 0x04, 0xe4, 0x15, 0xff, 0xf3, 0x73, 0xc2, 0x42, 0x6d, 0x5a, 0x2d, 0xce, 0x91, 0x1c, 0x3b, 0xdf, 0x6a, 0x9d, 0x8e, 0xe4, 0xb1, 0x5a, 0x2d, 0x59, 0x53, 0xbe, 0x8e, 0xa1, 0x7b, 0xee, 0xbd, 0xa7, 0x79, 0xa9, 0xc2, 0x23, 0x8f, 0x3c, 0xd2, 0x0c, 0x15, 0x00, 0x8b, 0x69, 0xa6, 0xab, 0xc0, 0xaf, 0xe8, 0x11, 0x06, 0x14, 0x7f, 0xc5, 0x1f, 0x80, 0x29, 0xee, 0x01, 0x88, 0x85, 0x7c, 0x65, 0x8f, 0x1e, 0x81, 0xfd, 0x8a, 0xbf, 0xe2, 0x3f, 0xcd, 0xea, 0x9a, 0x6b, 0xdf, 0x1c, 0xfe, 0xc0, 0xa4, 0x04, 0x80, 0x4b, 0x7b, 0xb4, 0xf4, 0x57, 0x84, 0xa3, 0x8f, 0xf5, 0x57, 0xfc, 0x15, 0xff, 0xa9, 0x51, 0xd7, 0x18, 0x02, 0x67, 0xef, 0x03, 0x26, 0x29, 0x00, 0xe4, 0x85, 0x80, 0xd2, 0xc5, 0x7f,
		0xd8, 0xd1, 0xe1, 0x5d, 0xb2, 0x84, 0xa2, 0x3d, 0x92, 0xc7, 0xaa, 0xb8, 0x65, 0xa7, 0x50, 0x00, 0x30, 0x72, 0x59, 0xce, 0x69, 0x56, 0xc7, 0x66, 0x9f, 0x3f, 0x00, 0x30, 0xba, 0x00, 0xd0, 0x1d, 0x02, 0x14, 0x7f, 0x00, 0x58, 0x22, 0x01, 0xa0, 0x1d, 0x02, 0xe2, 0x18, 0x80, 0x4b, 0x13, 0x8a, 0x7f, 0xbc, 0xdd, 0x6c, 0x78, 0x76, 0xd0, 0x20, 0x00, 0x30, 0xc1, 0x01, 0xa0, 0x88, 0xad, 0xe1, 0xd9, 0x1e, 0x83, 0x18, 0x16, 0x76, 0x5b, 0xb5, 0x00, 0x30, 0xbe, 0xaa, 0x3e, 0xd5, 0x59, 0xec, 0x01, 0x88, 0xbd, 0x06, 0xab, 0xac, 0x5a, 0x00, 0x58, 0x3a, 0x01, 0x40, 0x08, 0x00, 0x80, 0x25, 0x1a, 0x00, 0x84, 0x00, 0x00, 0x18, 0x73, 0x47, 0xe6, 0x01, 0xc8, 0xb2, 0x2c, 0x34, 0x1a, 0x8d, 0x15, 0x09, 0xcb, 0x1c, 0x9a, 0xbf, 0xed, 0xa1, 0x84, 0xb1, 0x03, 0xed, 0x10, 0x10, 0x8f, 0x1e, 0x30, 0x30, 0x10, 0x00, 0xc6, 0x31, 0x00, 0xcc, 0x17, 0xf4, 0xd5, 0xad, 0x82, 0x3d, 0x30, 0x00, 0xcc, 0xdf, 0xf6, 0x94, 0xf8, 0x33, 0xe5, 0xb6, 0x89, 0xb7, 0x03, 0x00, 0x46, 0x68, 0xa6, 0xa3, 0x07, 0x60, 0xc7, 0xfc, 0x8f, 0x1d, 0x09, 0xcb, 0x6c, 0x8e, 0x3d, 0x00, 0x09, 0xb7, 0x33, 0x77, 0x00, 0x00, 0x8c, 0x7b, 0x00, 0x68, 0x85, 0x80, 0x4b, 0x07, 0x84, 0x80, 0xb9, 0xf9, 0xdb, 0x6c, 0x56, 0xfc, 0x01, 0x60, 0x8a, 0x02, 0xc0, 0x80, 0x10, 0xa0, 0xf8, 0x03, 0xc0, 0xb4, 0x06, 0x80, 0x9c, 0x10, 0x90, 0x52, 0xfc, 0x0f, 0x29, 0xfe, 0x00, 0x30, 0x19, 0x8e, 0xcc, 0x04, 0x18, 0x8f, 0x02, 0xe8, 0x36, 0x7f, 0x5d, 0x1c, 0x14, 0xb8, 0xbf, 0x57, 0xf1, 0xcf, 0x39, 0x0a, 0x60, 0x36, 0x18, 0xf4, 0x07, 0x00, 0x93, 0x13, 0x00, 0x00, 0x00, 0x01, 0x60, 0x1c, 0x75, 0xcf, 0x51, 0xe0, 0x10, 0x43, 0x00, 0x28, 0x69, 0x66, 0x42, 0x9e, 0xe7, 0xa6, 0xf9, 0xcb, 0x43, 0x3d, 0x2e, 0xab, 0xbd, 0x85, 0x00, 0xb0, 0xf8, 0x01, 0x60, 0x6b, 0xeb, 0x92, 0x67, 0xe5, 0xfc, 0xe5, 0xee, 0xd6, 0xcf, 0x22, 0xb6, 0x85, 0xa3, 0x07, 0x16, 0xce, 0xb6, 0x2e, 0x45, 0xad, 0x68, 0x3d, 0x07, 0xd3, 0x14, 0x03, 0x20, 0x00, 0x54, 0x54, 0xfc, 0xd7, 0xb6, 0x2e, 0x5b, 0x73, 0x8a, 0xff, 0xae, 0xae, 0x9f, 0xa9, 0x62, 0xf1, 0x5f, 0x57, 0xf2, 0x79, 0xcd, 0x76, 0x15, 0xff, 0xf6, 0x63, 0xdf, 0x5c, 0x32, 0x40, 0x00, 0xc0, 0xd4, 0x06, 0x80, 0x15, 0x05, 0x5b, 0xea, 0xed, 0xe2, 0xdf, 0xd6, 0x1d, 0x02, 0xda, 0x45, 0x7f, 0xb6, 0xa3, 0x28, 0xef, 0x0a, 0x47, 0xef, 0xd7, 0xef, 0xd7, 0x6a, 0xdf, 0x5a, 0xe2, 0xf5, 0x5d, 0x19, 0x9e, 0xdd, 0x55, 0xb0, 0xaa, 0xa3, 0xf8, 0xb7, 0x1f, 0x33, 0x1e, 0xd9, 0x60, 0x0c, 0x01, 0x00, 0x02, 0x40, 0x57, 0xc1, 0x2e, 0xd3, 0x52, 0x0f, 0x3d, 0x42, 0xc0, 0xaa, 0xae, 0xe2, 0x5f, 0x54, 0xaf, 0xc2, 0x7d, 0xb0, 0xc0, 0xb2, 0xed, 0x93, 0x12, 0x75, 0xde, 0xc7, 0x5c, 0xeb, 0x7e, 0x00, 0x40, 0x00, 0xe8, 0x61, 0x36, 0x31, 0x04, 0xc4, 0xee, 0xf9, 0x6d, 0x39, 0x21, 0xa0, 0x57, 0xf1, 0x8f, 0x2d, 0xef, 0x94, 0x09, 0x83, 0x56, 0xf4, 0x28, 0xdc, 0x73, 0xe1, 0xb9, 0x33, 0x0c, 0xa6, 0x9e, 0x65, 0x70, 0x56, 0xf1, 0x07, 0x80, 0xf4, 0x00, 0x50, 0x45, 0x08, 0x08, 0x39, 0xc5, 0xbf, 0xe8, 0x29, 0x82, 0x3b, 0x0b, 0x77, 0x0c, 0x0e, 0x67, 0x96, 0xb8, 0x8f, 0x43, 0xc1, 0xa9, 0x89, 0x01, 0x20, 0x79, 0x10, 0x60, 0x55, 0x21, 0x20, 0xb5, 0xf8, 0xaf, 0x68, 0x5d, 0xda, 0x53, 0x0b, 0x57, 0xd5, 0x6a, 0x6f, 0xef, 0x0e, 0x58, 0xe9, 0xad, 0x07, 0x60, 0x29, 0x5b, 0x56, 0xb0, 0x78, 0x6e, 0x6a, 0x15, 0xe4, 0x7e, 0xe2, 0x39, 0x04, 0xd6, 0xe6, 0x5c, 0xb7, 0x3b, 0xb1, 0xf8, 0xef, 0x6a, 0xfd, 0xbf, 0xbd, 0x9b, 0x20, 0xa5, 0xf8, 0xf7, 0x7a, 0xcc, 0x83, 0xc1, 0x79, 0x09, 0x00, 0x60, 0xa8, 0x00, 0x10, 0x0b, 0xf7, 0xa5, 0x03, 0x6e, 0xd3, 0x3e, 0xbc, 0x2e, 0x4f, 0x9c, 0xb8, 0x67, 0x6b, 0x58, 0x78, 0x48, 0xdf, 0xa6, 0xf0, 0xdc, 0x71, 0xfe, 0xdd, 0xfb, 0xfc, 0x57, 0x27, 0x16, 0xff, 0x76, 0x38, 0xe9, 0x1e, 0x6b, 0x10, 0xef, 0xf7, 0x14, 0x6f, 0x33, 0x00, 0x2c, 0x94, 0xba, 0x0b, 0x60, 0x7f, 0xab, 0x35, 0x7e, 0x68, 0x40, 0xf1, 0x4f, 0x19, 0xed, 0xdf, 0x79, 0x88, 0x60, 0x2c, 0xf4, 0x57, 0xb6, 0x96, 0x5b, 0x15, 0xca, 0x8f, 0xd4, 0x3f, 0xd4, 0x0a, 0x27, 0x0e, 0xeb, 0x03, 0x80, 0x8a, 0x02, 0xc0, 0x30, 0xc5, 0x3f, 0x2e, 0xb3, 0x63, 0x40, 0x08, 0x08, 0xa1, 0xf7, 0x68, 0xff, 0xa2, 0xfb, 0xfc, 0x0f, 0x0a, 0x00, 0x00, 0x50, 0x4d, 0x00, 0x48, 0x29, 0xfe, 0xa1, 0x55, 0xcc, 0xf3, 0x0e, 0xf5, 0x8b, 0x2d, 0xf3, 0xbc, 0x43, 0x04, 0x2f, 0xec, 0xf1, 0xf7, 0xcd, 0x25, 0x8a, 0x7f, 0x77, 0x80, 0x10, 0x04, 0x00, 0xa0, 0x44, 0x00, 0xd8, 0xdf, 0x6a, 0xb9, 0xa7, 0x14, 0xff, 0x68, 0x5d, 0xd7, 0xed, 0xba, 0x47, 0xfb, 0xf7, 0x3a, 0x3a, 0x20, 0xfe, 0xfe, 0x3f, 0x3d, 0xee, 0x6b, 0x75, 0x48, 0x9f, 0x21, 0x30, 0xaf, 0xf7, 0xc0, 0xee, 0x00, 0x00, 0xe8, 0xa3, 0xca, 0xd3, 0x01, 0xb7, 0x77, 0x03, 0x84, 0x90, 0x7f, 0xa8, 0x5f, 0x7b, 0xca, 0xe0, 0x6d, 0xad, 0x50, 0x10, 0x8b, 0xf6, 0x43, 0x39, 0x01, 0xe4, 0xcc, 0xc4, 0xc7, 0xed, 0x9c, 0xb2, 0xb8, 0x73, 0xd7, 0xc1, 0xca, 0x8e, 0xfb, 0x02, 0x00, 0x6a, 0x0a, 0x00, 0xa1, 0xa3, 0x15, 0xde, 0xef, 0xd0, 0xbb, 0xd5, 0x61, 0xe1, 0xb8, 0x80, 0xf8, 0xfb, 0x6c, 0x8f, 0x00, 0x90, 0x5a, 0xb8, 0xe3, 0xe0, 0xc1, 0x9b, 0x43, 0xb9, 0x5d, 0x07, 0x00, 0x20, 0x00, 0x4c, 0xb0, 0x15, 0xc1, 0xf1, 0xfe, 0x00, 0xb0, 0xe4, 0x02, 0x00, 0x00, 0x50, 0xc0, 0x91, 0x41, 0x80, 0x59, 0x96, 0xf5, 0xbd, 0x84, 0x67, 0xbb, 0xda, 0xef, 0x1e, 0x74, 0xbb, 0x8e, 0xdb, 0x03, 0x00, 0xe3, 0x1e, 0x00, 0x12, 0xc4, 0xfd, 0xf4, 0x2b, 0x1b, 0x8d, 0xc6, 0xac, 0xd5, 0x06, 0x00, 0x4b, 0x27, 0x00, 0x2c, 0x30, 0x1f, 0x04, 0xd6, 0xce, 0x5f, 0xee, 0x6e, 0x5d, 0x36, 0x09, 0x06, 0x00, 0x30, 0xe1, 0x01, 0x20, 0x16, 0xf3, 0xf9, 0xcb, 0xaa, 0xae, 0x3f, 0xb7, 0x47, 0xf8, 0xb7, 0x7b, 0x01, 0xe2, 0xe1, 0x7c, 0x2b, 0x5b, 0x97, 0xe6, 0x74, 0xbe, 0x42, 0x00, 0x00, 0x4c, 0x76, 0x0f, 0xc0, 0xaa, 0x56, 0x41, 0xbf, 0xb2, 0x15, 0x08, 0xe2, 0xcf, 0x4d, 0xad, 0xeb, 0x6e, 0x6e, 0x85, 0x81, 0xee, 0x63, 0xfd, 0x57, 0x86, 0xfc, 0xb3, 0x00, 0x02, 0x00, 0xe3, 0x1e, 0x00, 0xb2, 0x2c, 0x8b, 0xc7, 0xe9, 0xc7, 0xc9, 0x7a, 0x62, 0xd7, 0xfe, 0xcd, 0x1d, 0xc5, 0x3f, 0x8a, 0xad, 0xfc, 0x5d, 0x39, 0x21, 0x40, 0x0f, 0x00, 0x00, 0x4c, 0x70, 0x0f, 0x40, 0x0c, 0x01, 0x71, 0xa6, 0xbe, 0xdd, 0xe1, 0xd9, 0x89, 0x7a, 0xba, 0xe5, 0x85, 0x00, 0xd3, 0xef, 0x02, 0xc0, 0x24, 0x07, 0x80, 0x38, 0xc8, 0x2f, 0x3c, 0xbb, 0x2b, 0xa0, 0x97, 0x38, 0xe5, 0xee, 0xc1, 0xae, 0x10, 0xb0, 0x3b, 0xf4, 0x3e, 0xe9, 0x0f, 0x00, 0x30, 0x66, 0x8e,
		0x4c, 0x04, 0xd4, 0x79, 0xec, 0x7e, 0x6b, 0x30, 0xdf, 0xdd, 0xa1, 0xf7, 0x49, 0x79, 0xe6, 0x5a, 0x85, 0x3e, 0x16, 0xff, 0x95, 0xad, 0x56, 0xff, 0xf9, 0xf3, 0xcb, 0xef, 0xef, 0x0a, 0x10, 0xd6, 0x2e, 0x00, 0x8c, 0x7b, 0x00, 0x68, 0x15, 0xf4, 0xf6, 0x3e, 0xfc, 0x95, 0x7d, 0x5a, 0xfe, 0x9d, 0xc5, 0xbf, 0xed, 0x50, 0xeb, 0xba, 0xf6, 0x2e, 0x80, 0xfd, 0xc1, 0xd4, 0xbc, 0x00, 0x30, 0x11, 0x01, 0xe0, 0xca, 0x8e, 0x00, 0x10, 0x5b, 0xfe, 0xab, 0x13, 0x8b, 0x7f, 0x2f, 0x71, 0x10, 0xe1, 0xa5, 0x56, 0x2f, 0x00, 0x8c, 0x79, 0x00, 0xe8, 0xda, 0x05, 0xb0, 0x2a, 0x3c, 0x77, 0x6a, 0xdf, 0x94, 0xe2, 0xbf, 0xbf, 0x55, 0xf0, 0x0f, 0xb5, 0xee, 0xeb, 0x90, 0x5d, 0x00, 0x00, 0x30, 0x61, 0x01, 0xa0, 0x15, 0x02, 0x1e, 0x6a, 0xf5, 0x04, 0xa4, 0x14, 0xff, 0x38, 0x06, 0xe0, 0x50, 0xd7, 0xf2, 0xd6, 0x2e, 0x00, 0x8c, 0xa9, 0x65, 0x7d, 0xae, 0x9b, 0x6b, 0x05, 0x80, 0x41, 0xdd, 0xfe, 0x3b, 0xba, 0x8b, 0x3f, 0x00, 0x30, 0xa1, 0x3d, 0x00, 0x1d, 0x2d, 0xf9, 0xbb, 0xfb, 0xb4, 0xfc, 0xe3, 0x25, 0x1e, 0x2e, 0x38, 0x37, 0xbf, 0xfc, 0x66, 0x3d, 0x00, 0x00, 0x30, 0x3d, 0x01, 0x20, 0x8e, 0x07, 0x88, 0x03, 0x04, 0xdb, 0x73, 0x02, 0xc4, 0xd6, 0xfe, 0x8e, 0x56, 0xd1, 0x8f, 0xfb, 0xfa, 0xb7, 0xb6, 0x42, 0xc0, 0x89, 0x9d, 0x3d, 0x01, 0x02, 0x00, 0x00, 0x4c, 0x70, 0x00, 0xe8, 0x28, 0xe8, 0xed, 0xd9, 0xff, 0x76, 0xcf, 0xdf, 0x76, 0xae, 0xeb, 0xba, 0x15, 0xf3, 0x7f, 0x3b, 0xa8, 0x07, 0x00, 0x00, 0x26, 0x43, 0xf2, 0xe9, 0x80, 0xfb, 0xed, 0xe7, 0xef, 0x2e, 0xfe, 0x00, 0xc0, 0x94, 0x04, 0x00, 0x00, 0x60, 0xe9, 0x06, 0x80, 0x38, 0xdf, 0xbf, 0xd6, 0x3e, 0x00, 0x4c, 0xb8, 0xcc, 0xbe, 0x7a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x60, 0xa2, 0x02, 0x40, 0xbc, 0x71, 0x36, 0xe0, 0xba, 0xbc, 0xdb, 0x74, 0xfe, 0x7d, 0xd0, 0x6d, 0xfa, 0x3d, 0xce, 0xa0, 0xe5, 0x8f, 0xbc, 0xb6, 0x82, 0xcf, 0xbf, 0xd7, 0xfd, 0x64, 0x39, 0xbf, 0x4f, 0xba, 0x41, 0xeb, 0x2f, 0x2b, 0xf9, 0xfe, 0x0f, 0x5a, 0xf7, 0x21, 0x61, 0x3d, 0xe6, 0x3d, 0x87, 0x5e, 0x1f, 0xd4, 0xac, 0xc0, 0x63, 0x0c, 0xbb, 0x7c, 0x91, 0xd7, 0x30, 0xae, 0xef, 0x79, 0xea, 0x6b, 0x2b, 0xfa, 0x19, 0x48, 0x59, 0xb7, 0xfd, 0x9e, 0x43, 0xa3, 0xc0, 0xfb, 0x92, 0xb2, 0x7c, 0xca, 0x7d, 0x64, 0x09, 0xaf, 0x29, 0xab, 0x68, 0xfd, 0x35, 0x0a, 0xfe, 0x5e, 0xe4, 0xfb, 0x9a, 0x95, 0x78, 0xfe, 0x75, 0xac, 0xbf, 0xb2, 0xcb, 0xf7, 0x2b, 0x40, 0x59, 0xc9, 0xf5, 0x97, 0xba, 0x7e, 0x53, 0x6b, 0x56, 0xca, 0xf5, 0x61, 0x88, 0xed, 0x4b, 0x4a, 0x5d, 0x6a, 0x94, 0xfc, 0x6e, 0xf6, 0xb5, 0x6c, 0xcc, 0x37, 0x54, 0xa9, 0x85, 0xa9, 0xcc, 0x97, 0xaa, 0xc8, 0x97, 0x2d, 0x1b, 0xf2, 0x8b, 0x3a, 0xec, 0x73, 0x1a, 0x75, 0x28, 0x48, 0xdd, 0xc8, 0xd7, 0xf9, 0x85, 0x4c, 0xf9, 0x42, 0x15, 0x79, 0x0e, 0x83, 0x5e, 0x4f, 0x55, 0xaf, 0xa1, 0xce, 0x80, 0x36, 0x6c, 0x38, 0x2f, 0xf2, 0x5a, 0x8a, 0x3e, 0x87, 0x6c, 0xc8, 0xc7, 0xcc, 0x12, 0xbf, 0x83, 0xa1, 0x82, 0xcf, 0x46, 0xd9, 0xd7, 0xd7, 0x6f, 0x99, 0x2c, 0xf1, 0xbb, 0x52, 0xd5, 0x67, 0xa2, 0x31, 0xc4, 0xfb, 0x9f, 0xfa, 0xfd, 0xc8, 0x46, 0xb0, 0xfc, 0xa8, 0xbe, 0x53, 0x45, 0xdf, 0xdb, 0x22, 0xcf, 0x25, 0x25, 0x10, 0x0e, 0xdb, 0x70, 0x18, 0x14, 0x98, 0x52, 0x1b, 0xcf, 0x0b, 0xcc, 0x54, 0xbc, 0x12, 0x87, 0x79, 0x81, 0x9d, 0x1f, 0x88, 0x6c, 0x40, 0x62, 0xcc, 0x4a, 0xbe, 0x29, 0x59, 0xc1, 0x2f, 0x59, 0xde, 0x07, 0x65, 0xd0, 0x9b, 0x3d, 0xce, 0xfb, 0x55, 0x52, 0xbf, 0xcc, 0x8d, 0x02, 0xeb, 0x6e, 0x5a, 0x7a, 0x46, 0xc6, 0xb9, 0x77, 0x26, 0x75, 0x23, 0x36, 0x6c, 0xf0, 0x6b, 0xf4, 0xb9, 0xbf, 0x46, 0xc9, 0xc7, 0x29, 0x5a, 0xd0, 0xb3, 0x11, 0x7c, 0x87, 0xb2, 0x09, 0x7b, 0x7f, 0xa7, 0x4d, 0x36, 0x61, 0xcf, 0x75, 0xd8, 0xc0, 0x15, 0x6a, 0xfc, 0xbc, 0x37, 0xba, 0xea, 0x6f, 0xf2, 0x7d, 0xcd, 0x8c, 0xf0, 0x43, 0xdf, 0xbd, 0x81, 0x69, 0x14, 0xf8, 0x80, 0x64, 0x23, 0x58, 0x89, 0x55, 0x7d, 0x40, 0x26, 0xfd, 0x0b, 0xde, 0x58, 0xa4, 0x2f, 0x7b, 0xd5, 0xeb, 0x6d, 0x31, 0x7a, 0x62, 0x1a, 0x15, 0x5c, 0x9f, 0xd7, 0x9a, 0xe8, 0x75, 0x49, 0xfd, 0x0e, 0x14, 0x59, 0xff, 0x8b, 0xf9, 0x3d, 0x12, 0xee, 0xca, 0x6f, 0x63, 0xbc, 0x6f, 0xf5, 0x6e, 0xc3, 0xc7, 0x79, 0x1b, 0x9f, 0x95, 0xf8, 0xbe, 0x37, 0x2d, 0x1b, 0xf1, 0xca, 0xcd, 0x86, 0x5c, 0x81, 0x55, 0xa6, 0xae, 0xba, 0x5f, 0x63, 0xde, 0x86, 0xbf, 0xec, 0x78, 0x82, 0x46, 0xd9, 0x37, 0x79, 0x8c, 0xd6, 0xd1, 0xb0, 0x63, 0x29, 0xea, 0xdc, 0x07, 0x9f, 0x0d, 0xb8, 0xff, 0x94, 0x0d, 0x6c, 0xd5, 0xdd, 0xd4, 0x65, 0x5e, 0x6b, 0x56, 0xd3, 0xf7, 0xa4, 0x57, 0x2b, 0x23, 0xab, 0xf8, 0xf3, 0x39, 0xcc, 0x7b, 0xdf, 0xa8, 0xe0, 0xbb, 0xa1, 0xe5, 0x3f, 0xba, 0x16, 0x74, 0x36, 0xc6, 0xcf, 0x33, 0x5b, 0x84, 0xf7, 0x39, 0x5b, 0x8c, 0xcf, 0xc8, 0xb2, 0x31, 0xfe, 0x90, 0x64, 0x43, 0xac, 0xf4, 0xc5, 0x18, 0xb4, 0x37, 0x28, 0x3d, 0x56, 0xd1, 0x02, 0x18, 0xe7, 0x16, 0x4a, 0x91, 0x42, 0x56, 0x66, 0x7f, 0x5b, 0xca, 0x3e, 0xdc, 0x61, 0x8a, 0x40, 0xca, 0x73, 0xaa, 0x6b, 0x3f, 0x6f, 0x1d, 0xbd, 0x1f, 0x55, 0xec, 0xf7, 0x1e, 0xe6, 0xf3, 0x39, 0xca, 0x1e, 0x9d, 0x22, 0xef, 0x77, 0xde, 0x67, 0xa4, 0xc8, 0x98, 0x97, 0xc5, 0x2a, 0x2e, 0x75, 0x3e, 0xc6, 0xb0, 0x05, 0x7a, 0xd0, 0xf2, 0xa3, 0xfc, 0x2c, 0xd6, 0xdd, 0x0b, 0x33, 0xae, 0x8d, 0xd0, 0xb1, 0x0d, 0x00, 0x8d, 0x9c, 0x96, 0xf0, 0xa0, 0x0d, 0xec, 0xb0, 0x83, 0x32, 0x46, 0xf5, 0x86, 0x74, 0x0f, 0xc0, 0x18, 0xc7, 0x0f, 0xc2, 0x28, 0x9e, 0xd3, 0x30, 0x8f, 0x51, 0xc5, 0x06, 0xb7, 0xc8, 0x40, 0xc3, 0x69, 0x6b, 0x79, 0x0c, 0xfb, 0x1a, 0xb3, 0xd0, 0xbb, 0xa7, 0x6a, 0x94, 0xad, 0xe4, 0x51, 0xad, 0xeb, 0xc5, 0x7a, 0x2d, 0xc3, 0xbe, 0xcf, 0x75, 0x6e, 0x5b, 0xb2, 0x8a, 0x97, 0x9f, 0xc4, 0x1e, 0x8f, 0x61, 0xb6, 0xdf, 0x8d, 0x8a, 0xd6, 0xe1, 0x48, 0xd7, 0xdb, 0xa4, 0xed, 0x02, 0x18, 0xd7, 0x0f, 0x58, 0x56, 0xf1, 0x97, 0x69, 0x5c, 0x5e, 0x47, 0x55, 0xef, 0x47, 0xca, 0xe0, 0xca, 0x69, 0x2b, 0x34,
		0x55, 0x7e, 0xf9, 0x8b, 0x8c, 0x28, 0xae, 0xa3, 0x97, 0x69, 0x92, 0xc2, 0xd4, 0x24, 0xbf, 0xcf, 0x55, 0xde, 0xff, 0x28, 0x1a, 0x74, 0xd3, 0x64, 0xd0, 0x2e, 0xae, 0xa9, 0x34, 0x33, 0x66, 0x6f, 0x40, 0x6a, 0x71, 0x69, 0x24, 0x7c, 0xe8, 0xab, 0x68, 0x05, 0x0d, 0x5b, 0xc8, 0xaa, 0x4e, 0xd9, 0x75, 0x85, 0xa5, 0x5e, 0xad, 0xbf, 0xac, 0xc2, 0xfb, 0x9f, 0x86, 0x8d, 0xce, 0x28, 0x1e, 0xbf, 0xdf, 0x20, 0xbe, 0x5e, 0x97, 0x2a, 0x3e, 0x9f, 0xa9, 0x47, 0xb6, 0x54, 0xfd, 0xba, 0x1a, 0x8b, 0xfc, 0x79, 0x9a, 0xd4, 0xcf, 0xe6, 0x38, 0xac, 0x97, 0x6c, 0xcc, 0xd6, 0x4f, 0xea, 0x00, 0xbd, 0xb2, 0x47, 0xb1, 0x8c, 0x72, 0xfb, 0x37, 0xd2, 0xc1, 0x9c, 0xe3, 0x36, 0x13, 0xe0, 0x30, 0x13, 0x25, 0xf4, 0x5a, 0x7e, 0xd8, 0xfd, 0x61, 0xa3, 0x9e, 0x08, 0xa8, 0xae, 0x01, 0x28, 0x65, 0x27, 0x40, 0x4a, 0x79, 0x6f, 0x42, 0xa8, 0x66, 0x92, 0x9d, 0xd4, 0xd7, 0x11, 0x4a, 0x3e, 0xc7, 0xd4, 0x9e, 0x8a, 0x61, 0xee, 0xbf, 0xaa, 0x79, 0x20, 0xea, 0xea, 0x82, 0x4c, 0x7d, 0xed, 0xa9, 0xdf, 0xbf, 0x46, 0x28, 0x76, 0xe4, 0x41, 0x9d, 0x13, 0x01, 0x15, 0x99, 0x48, 0x25, 0x65, 0xf9, 0x61, 0x26, 0x02, 0x2a, 0x33, 0x27, 0x42, 0x18, 0x72, 0xfd, 0x0f, 0x3b, 0x11, 0x50, 0x99, 0xf5, 0x57, 0xd5, 0xe3, 0x57, 0xf1, 0xdd, 0x4c, 0x2d, 0xfe, 0xbd, 0x7e, 0x2f, 0xb2, 0xdd, 0x2c, 0x32, 0x47, 0x4a, 0xd9, 0x6d, 0x60, 0x1d, 0xe3, 0x9b, 0x7a, 0x3e, 0xbf, 0x2a, 0x67, 0x02, 0xac, 0xb2, 0x00, 0x2e, 0xd5, 0xae, 0x45, 0x5d, 0xaa, 0xde, 0x5b, 0x80, 0x25, 0xd9, 0x03, 0xa0, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x40, 0xc9, 0x00, 0x50, 0xc7, 0x1c, 0xfd, 0x65, 0x95, 0x3d, 0x14, 0x2a, 0x84, 0x7a, 0x67, 0x71, 0x2a, 0x73, 0xa8, 0x57, 0x91, 0xc3, 0x6c, 0x96, 0xf2, 0x40, 0xc0, 0xa5, 0x32, 0x10, 0x32, 0xef, 0xbd, 0x1e, 0x74, 0xf8, 0xa3, 0x41, 0xa2, 0x80, 0x00, 0x30, 0xe0, 0xf6, 0xe3, 0x36, 0x91, 0x4d, 0x9d, 0xc7, 0x7f, 0x0b, 0x00, 0xd3, 0xf3, 0x1a, 0x87, 0x99, 0x47, 0x60, 0xa9, 0x1f, 0x42, 0x0b, 0x0c, 0x19, 0x00, 0x52, 0x5a, 0x21, 0xa1, 0x47, 0x6b, 0xa4, 0xd7, 0x84, 0x20, 0x45, 0x27, 0x32, 0x18, 0x34, 0x89, 0x4f, 0x15, 0x93, 0xb0, 0x84, 0x01, 0x2d, 0xaf, 0x41, 0x2d, 0xad, 0xb2, 0xd7, 0xa7, 0x9e, 0xd7, 0x20, 0x75, 0xc2, 0x8f, 0xc6, 0x80, 0xf5, 0x9f, 0xd5, 0xf0, 0xfa, 0x1b, 0x7d, 0xde, 0x9b, 0x94, 0xfb, 0x18, 0x66, 0x22, 0x8f, 0x41, 0xbd, 0x2a, 0x29, 0x13, 0xad, 0xd4, 0xfd, 0x7b, 0xe8, 0xf3, 0xfd, 0xa8, 0x3b, 0x00, 0x28, 0xfe, 0x40, 0x25, 0x01, 0x20, 0x75, 0xc3, 0xd3, 0xbd, 0x01, 0x0e, 0x21, 0x7d, 0xa6, 0xa5, 0xd4, 0x0d, 0x6a, 0x91, 0xb3, 0xc7, 0x95, 0x9d, 0x05, 0x2a, 0xe5, 0xf1, 0x86, 0xdd, 0x48, 0x37, 0x86, 0xbc, 0xef, 0x5e, 0xc5, 0xb7, 0xdf, 0xfa, 0xaf, 0x73, 0x7d, 0x0f, 0x2a, 0xf0, 0x59, 0x89, 0xf5, 0x9f, 0x1a, 0x30, 0xeb, 0x0a, 0x00, 0x83, 0x8a, 0x68, 0x91, 0x13, 0x53, 0x55, 0xd1, 0x8a, 0xd7, 0x43, 0x04, 0xd4, 0x2e, 0xf5, 0x5c, 0x00, 0x59, 0x45, 0xb7, 0x49, 0xbd, 0xed, 0x62, 0x6c, 0xe4, 0x46, 0x31, 0xcd, 0x6f, 0x9d, 0xa7, 0x03, 0xce, 0x46, 0xf4, 0xfa, 0xb3, 0x9a, 0xee, 0xa3, 0xf3, 0x44, 0x1c, 0x8a, 0x1c, 0x40, 0xcd, 0x8a, 0x9c, 0x0d, 0x70, 0x12, 0x4e, 0xc6, 0x32, 0xce, 0x83, 0xa5, 0x46, 0x7d, 0x8a, 0xe2, 0x71, 0x7b, 0xed, 0xc3, 0xcc, 0x65, 0x3d, 0xca, 0xe7, 0x58, 0xd7, 0x19, 0x11, 0x01, 0x26, 0x32, 0x00, 0x14, 0x39, 0x01, 0xc2, 0x62, 0xb6, 0xd0, 0x27, 0x61, 0xe3, 0xbb, 0x54, 0xf7, 0xd5, 0x96, 0x39, 0xb9, 0x53, 0x1d, 0x21, 0x72, 0x31, 0xd7, 0xfb, 0xb0, 0x8f, 0x6f, 0x3f, 0x3f, 0x50, 0x99, 0x19, 0xab, 0x00, 0x16, 0x14, 0xe7, 0xc6, 0x90, 0xcb, 0xa7, 0x14, 0xf0, 0x49, 0x0d, 0x30, 0x80, 0x00, 0x30, 0xf4, 0xf9, 0xc3, 0x1b, 0x35, 0x5f, 0x4f, 0x35, 0xef, 0x69, 0x55, 0xeb, 0xbe, 0x51, 0xf3, 0x73, 0x4d, 0x3d, 0x1f, 0x38, 0x00, 0xed, 0x0d, 0x67, 0x81, 0x99, 0x00, 0xfb, 0x1d, 0xa6, 0x37, 0x69, 0x87, 0x01, 0x86, 0x50, 0x7c, 0x94, 0x78, 0xca, 0x73, 0xc8, 0x5b, 0xb6, 0xe8, 0x28, 0xf8, 0x94, 0x11, 0xef, 0x45, 0x46, 0xc1, 0xa7, 0xde, 0x7f, 0x15, 0x87, 0x01, 0xa6, 0x7e, 0x7e, 0x06, 0xdd, 0x2e, 0x2b, 0xf8, 0xf9, 0x18, 0xf4, 0x1c, 0x86, 0x1d, 0xe5, 0x3f, 0xe8, 0xf3, 0x13, 0xfa, 0x5c, 0x5f, 0xf4, 0x39, 0xea, 0x01, 0x00, 0xc6, 0x2a, 0x00, 0x4c, 0x5b, 0x6b, 0x37, 0x9b, 0xc0, 0xfb, 0x1e, 0x97, 0xf5, 0x61, 0xc2, 0xa2, 0xf2, 0xaf, 0x5f, 0x00, 0x00, 0x04, 0x00, 0x01, 0x40, 0x00, 0x10, 0x00, 0x04, 0x00, 0x40, 0x00, 0x18, 0xe5, 0x06, 0xbb, 0xca, 0x0d, 0x69, 0x9d, 0xf7, 0x2d, 0x00, 0x4c, 0xe7, 0xe7, 0xc7, 0xb9, 0x00, 0x00, 0x01, 0x60, 0xc4, 0x1b, 0xf1, 0x50, 0xd3, 0x86, 0x74, 0xdc, 0x8f, 0x71, 0x17, 0x00, 0xbc, 0xc7, 0x00, 0x4b, 0x36, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80,
		0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x30, 0x0a, 0xff, 0x2f, 0xc0, 0x00, 0xc8, 0xbf, 0x9b, 0xa0, 0xcd, 0xbc, 0xee, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82 };
	*size = zt_sizeof(data);
	byte *result = zt_mallocStructArray(byte, *size);
	zt_memCpy(result, *size, data, *size);
	return result;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztFontID _zt_guiLoadDefaultFont(ztTextureID tex)
{
	char *data = "info face=ZeroToleranceGui size=16 bold=0 italic=0 charset=unicode=stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=0,0 outline=0\ncommon lineHeight=16 base=13 scaleW=512 scaleH=64 pages=1 packed=0\npage id=0 file=\".\"\nchars count=93\nchar id=33 x=8 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=34 x=16 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=35 x=24 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=36 x=32 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=37 x=40 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=38 x=48 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=39 x=56 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=40 x=64 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=41 x=72 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=42 x=80 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=43 x=88 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=44 x=96 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=45 x=104 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=46 x=112 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=47 x=120 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=48 x=128 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=49 x=136 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=50 x=144 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=51 x=152 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=52 x=160 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=53 x=168 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=54 x=176 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=55 x=184 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=56 x=192 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=57 x=200 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=58 x=208 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=59 x=216 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=60 x=224 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=61 x=232 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=62 x=240 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=63 x=248 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=64 x=256 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=65 x=264 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=66 x=272 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=67 x=280 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=68 x=288 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=69 x=296 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=70 x=304 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=71 x=312 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=72 x=320 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=73 x=328 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=74 x=336 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=75 x=344 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=76 x=352 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=77 x=360 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=78 x=368 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=79 x=376 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=80 x=384 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=81 x=392 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=82 x=400 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=83 x=408 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=84 x=416 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=85 x=424 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=86 x=432 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=87 x=440 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=88 x=448 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=89 x=456 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=90 x=464 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=91 x=472 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=93 x=480 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=94 x=488 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=95 x=496 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=96 x=0 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=97 x=8 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=98 x=16 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=99 x=24 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=100 x=32 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=101 x=40 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=102 x=48 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=103 x=56 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=104 x=64 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=105 x=72 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=106 x=80 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=107 x=88 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=108 x=96 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=109 x=104 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=110 x=112 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=111 x=120 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=112 x=128 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=113 x=136 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=114 x=144 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=115 x=152 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=116 x=160 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=117 x=168 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=118 x=176 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=119 x=184 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=120 x=192 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=121 x=200 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=122 x=208 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=123 x=216 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=124 x=224 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=125 x=232 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=126 x=240 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\n";
	return zt_fontMakeFromBmpFontData(data, tex, ztVec2(0, 128));
}

// ------------------------------------------------------------------------------------------------

ztGuiManagerID zt_guiManagerMake(ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena)
{
	zt_returnValOnNull(gui_camera, ztInvalidID);

	if (zt_gui == nullptr) {
		zt_guiInitGlobalMemory(arena);
	}

	ztGuiManagerID id = ztInvalidID;
	int active = 0;
	zt_fiz(zt_elementsOf(zt_gui->gui_managers)) {
		if (zt_gui->gui_managers[i] == nullptr) {
			if (id == ztInvalidID)
				id = i;
			break;
		}
		else {
			active += 1;
		}
	}
	if (id == ztInvalidID) {
		zt_assert(false);
		return ztInvalidID;
	}

	{
		char size[128];
		zt_strBytesToString(size, zt_sizeof(size), zt_sizeof(ztGuiManager));
		zt_logVerbose("GuiManager allocated size: %s", size);
	}

	ztGuiManager *gm = zt_gui->gui_managers[id] = zt_mallocStructArena(ztGuiManager, arena);
	if (!gm) {
		return ztInvalidID;
	}

	zt_memSet(gm, zt_sizeof(ztGuiManager), 0);

	gm->arena = arena;
	gm->gui_camera = gui_camera;
	gm->gui_camera_w = gui_camera->width;
	gm->gui_camera_h = gui_camera->height;
	gm->item_has_mouse = ztInvalidID;
	gm->focus_item = ztInvalidID;
	gm->tooltip_item = ztInvalidID;

	if (theme_default) {
		gm->default_theme = *theme_default;
	}
	else {
#if defined(ZT_WINDOWS)
		gm->internal_flags |= ztGuiManagerInternalFlags_OwnsTheme;

		zt_memSet(&gm->default_theme, zt_sizeof(ztGuiTheme), 0);

		i32 tex_size = 0;
		byte *tex_data = _zt_guiLoadDefaultTexture(&tex_size);
		ztTextureID tex = zt_textureMakeFromFileData(tex_data, tex_size, ztTextureFlags_PixelPerfect);
		zt_free(tex_data);

		gm->default_theme.font = _zt_guiLoadDefaultFont(tex);
		if (gm->default_theme.font == ztInvalidID) {
			gm->default_theme.font = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\SegoeWP.ttf", 20);
			if (gm->default_theme.font == ztInvalidID) {
				gm->default_theme.font = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\calibri.ttf", 16);
				if (gm->default_theme.font == ztInvalidID) {
					gm->default_theme.font = zt_fontMakeFromTrueTypeFile("C:\\Windows\\Fonts\\arial.ttf", 16);
				}
			}
		}

		r32 ppu = zt_pixelsPerUnit();

		gm->default_theme.font_scale = 1;
		gm->default_theme.font_color = ztColor::one;
		gm->default_theme.back_color = ztColor(0, 0, 0, 1);
		gm->default_theme.highlight_color = ztColor(0, .5f, .5f, 1);

		gm->default_theme.window_title_height = 27 / ppu;
		gm->default_theme.window_title_align = ztAlign_Left | ztAlign_Center;
		gm->default_theme.window_title_padding_x = 8 / ppu;
		gm->default_theme.window_title_padding_y = 3 / ppu;

		gm->default_theme.button_default_w = 96 / ppu;
		gm->default_theme.button_default_h = 32 / ppu;
		gm->default_theme.button_padding_w = 3 / ppu;
		gm->default_theme.button_padding_h = 3 / ppu;

		gm->default_theme.padding = 6.f / ppu;
		gm->default_theme.spacing = 6.f / ppu;

		gm->default_theme.sprite_panel.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_panel.sns = zt_spriteNineSliceMake(tex, ztPoint2(72, 0), ztPoint2(12, 12), ztPoint2(74, 2), ztPoint2(81, 9));

		gm->default_theme.sprite_window.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_window.sns = zt_spriteNineSliceMake(tex, ztPoint2(0, 0), ztPoint2(32, 32), ztPoint2(2, 29), ztPoint2(29, 30));

		gm->default_theme.sprite_button.normal.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_button.normal.sns = zt_spriteNineSliceMake(tex, ztPoint2(33, 0), ztPoint2(12, 12), ztPoint2(35, 2), ztPoint2(42, 9));
		gm->default_theme.sprite_button.highlight.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_button.highlight.sns = zt_spriteNineSliceMake(tex, ztPoint2(46, 0), ztPoint2(12, 12), ztPoint2(48, 2), ztPoint2(55, 9));
		gm->default_theme.sprite_button.pressed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_button.pressed.sns = zt_spriteNineSliceMake(tex, ztPoint2(59, 0), ztPoint2(12, 12), ztPoint2(61, 2), ztPoint2(68, 9));

		gm->default_theme.sprite_checkbox.normal = gm->default_theme.sprite_button.normal;
		gm->default_theme.sprite_checkbox.highlight = gm->default_theme.sprite_button.highlight;
		gm->default_theme.sprite_checkbox.pressed = gm->default_theme.sprite_button.pressed;
		gm->default_theme.sprite_checkbox_check.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_checkbox_check.s = zt_spriteMake(tex, ztPoint2(1,36), ztPoint2(17, 17));

		gm->default_theme.checkbox_size_w = 17 / ppu;
		gm->default_theme.checkbox_size_h = 17 / ppu;

		gm->default_theme.sprite_radio.normal.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_radio.normal.s = zt_spriteMake(tex, ztPoint2(34, 14), ztPoint2(14,14));
		gm->default_theme.sprite_radio.highlight.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_radio.highlight.s = zt_spriteMake(tex, ztPoint2(50, 14), ztPoint2(14,14));
		gm->default_theme.sprite_radio.pressed.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_radio.pressed.s = zt_spriteMake(tex, ztPoint2(66, 14), ztPoint2(14,14));
		gm->default_theme.sprite_radio_check.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_radio_check.s = zt_spriteMake(tex, ztPoint2(81, 14), ztPoint2(14,14));

		gm->default_theme.radio_size_w = 14 / ppu;
		gm->default_theme.radio_size_h = 14 / ppu;

		gm->default_theme.sprite_slider_horz_handle.normal.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_slider_horz_handle.normal.sns = zt_spriteNineSliceMake(tex, ztPoint2(96, 0), ztPoint2(14, 25), ztPoint2(101, 2), ztPoint2(104, 19));
		gm->default_theme.sprite_slider_horz_handle.highlight.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_slider_horz_handle.highlight.sns = zt_spriteNineSliceMake(tex, ztPoint2(112, 0), ztPoint2(14, 25), ztPoint2(117, 2), ztPoint2(120, 19));
		gm->default_theme.sprite_slider_horz_handle.pressed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_slider_horz_handle.pressed.sns = zt_spriteNineSliceMake(tex, ztPoint2(128, 0), ztPoint2(14, 25), ztPoint2(133, 2), ztPoint2(136, 19));

		gm->default_theme.sprite_slider_vert_handle.normal.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_slider_vert_handle.normal.sns = zt_spriteNineSliceMake(tex, ztPoint2(22, 34), ztPoint2(25, 14), ztPoint2(24, 39), ztPoint2(41, 42));
		gm->default_theme.sprite_slider_vert_handle.highlight.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_slider_vert_handle.highlight.sns = zt_spriteNineSliceMake(tex, ztPoint2(49, 34), ztPoint2(25, 14), ztPoint2(51, 39), ztPoint2(68, 42));
		gm->default_theme.sprite_slider_vert_handle.pressed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_slider_vert_handle.pressed.sns = zt_spriteNineSliceMake(tex, ztPoint2(76, 34), ztPoint2(25, 14), ztPoint2(78, 39), ztPoint2(95, 42));

		gm->default_theme.sprite_slider_background = gm->default_theme.sprite_button.normal;
		gm->default_theme.slider_handle_w = 12 / ppu;
		gm->default_theme.slider_handle_h = 22 / ppu;
		gm->default_theme.slider_background_h = 10 / ppu;

		gm->default_theme.sprite_scrollbar_horz_handle.normal.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_scrollbar_horz_handle.normal.sns = zt_spriteNineSliceMake(tex, ztPoint2(104, 30), ztPoint2(12, 12), ztPoint2(106, 32), ztPoint2(113, 39));
		gm->default_theme.sprite_scrollbar_horz_handle.highlight.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_scrollbar_horz_handle.highlight.sns = zt_spriteNineSliceMake(tex, ztPoint2(117, 30), ztPoint2(12, 12), ztPoint2(119, 32), ztPoint2(126, 39));
		gm->default_theme.sprite_scrollbar_horz_handle.pressed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_scrollbar_horz_handle.pressed.sns = zt_spriteNineSliceMake(tex, ztPoint2(130, 30), ztPoint2(12, 12), ztPoint2(132, 32), ztPoint2(139, 39));
		gm->default_theme.sprite_scrollbar_vert_handle = gm->default_theme.sprite_scrollbar_horz_handle;
		
		gm->default_theme.sprite_scrollbar_background = gm->default_theme.sprite_button.normal;

		gm->default_theme.sprite_scrollbar_vert_button_neg.normal.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_vert_button_neg.normal.s = zt_spriteMake(tex, ztPoint2(144, 0), ztPoint2(14, 20));
		gm->default_theme.sprite_scrollbar_vert_button_neg.highlight.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_vert_button_neg.highlight.s = zt_spriteMake(tex, ztPoint2(160, 0), ztPoint2(14, 20));
		gm->default_theme.sprite_scrollbar_vert_button_neg.pressed.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_vert_button_neg.pressed.s = zt_spriteMake(tex, ztPoint2(176, 0), ztPoint2(14, 20));

		gm->default_theme.sprite_scrollbar_vert_button_pos.normal.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_vert_button_pos.normal.s = zt_spriteMake(tex, ztPoint2(144, 22), ztPoint2(14, 20));
		gm->default_theme.sprite_scrollbar_vert_button_pos.highlight.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_vert_button_pos.highlight.s = zt_spriteMake(tex, ztPoint2(160, 22), ztPoint2(14, 20));
		gm->default_theme.sprite_scrollbar_vert_button_pos.pressed.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_vert_button_pos.pressed.s = zt_spriteMake(tex, ztPoint2(176, 22), ztPoint2(14, 20));

		gm->default_theme.sprite_scrollbar_horz_button_neg.normal.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_horz_button_neg.normal.s = zt_spriteMake(tex, ztPoint2(192, 0), ztPoint2(20, 14));
		gm->default_theme.sprite_scrollbar_horz_button_neg.highlight.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_horz_button_neg.highlight.s = zt_spriteMake(tex, ztPoint2(192, 16), ztPoint2(20, 14));
		gm->default_theme.sprite_scrollbar_horz_button_neg.pressed.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_horz_button_neg.pressed.s = zt_spriteMake(tex, ztPoint2(192, 32), ztPoint2(20, 14));

		gm->default_theme.sprite_scrollbar_horz_button_pos.normal.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_horz_button_pos.normal.s = zt_spriteMake(tex, ztPoint2(214, 0), ztPoint2(20, 14));
		gm->default_theme.sprite_scrollbar_horz_button_pos.highlight.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_horz_button_pos.highlight.s = zt_spriteMake(tex, ztPoint2(214, 16), ztPoint2(20, 14));
		gm->default_theme.sprite_scrollbar_horz_button_pos.pressed.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_scrollbar_horz_button_pos.pressed.s = zt_spriteMake(tex, ztPoint2(214, 32), ztPoint2(20, 14));

		gm->default_theme.scrollbar_has_buttons = true;
		gm->default_theme.scrollbar_button_h = 14 / ppu;
		gm->default_theme.scrollbar_button_w = 20 / ppu;
		gm->default_theme.scrollbar_handle_min_size = 10 / ppu;

		gm->default_theme.scroll_container_padding_x = 2 / ppu;
		gm->default_theme.scroll_container_padding_y = 2 / ppu;


		gm->default_theme.sprite_textedit = gm->default_theme.sprite_button.normal;
		gm->default_theme.sprite_textedit_select.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_textedit_select.s = zt_spriteMake(tex, ztPoint2(60, 1), ztPoint2(10, 10));

		gm->default_theme.textedit_padding_x = 3 / ppu;
		gm->default_theme.textedit_padding_y = 3 / ppu;
		gm->default_theme.textedit_default_h = 24 / ppu;
		gm->default_theme.textedit_default_w = 100 / ppu;

		gm->default_theme.sprite_menu = gm->default_theme.sprite_button.normal;
		gm->default_theme.sprite_menu_highlight = gm->default_theme.sprite_button.highlight;
		gm->default_theme.sprite_menu_check = gm->default_theme.sprite_checkbox_check;
		gm->default_theme.sprite_menu_submenu.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_menu_submenu.s = zt_spriteMake(tex, ztPoint2(0, 64), ztPoint2(16, 16));

		gm->default_theme.menu_padding_x = 3 / ppu;
		gm->default_theme.menu_padding_y = 3 / ppu;
		gm->default_theme.menu_submenu_icon_x = 16 / ppu;
		gm->default_theme.menu_submenu_icon_y = 16 / ppu;

#endif
	}

	if (active == 0) {
		zt_gui->active_gui_manager = id;
	}
	gm->base_id = id * ztGuiManagerItemIDOffset;

	return id;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiItemFree(ztGuiManager *gm, ztGuiItem *item)
{
	if (item->functions.cleanup) {
		item->functions.cleanup(item->id, item->functions.user_data);
	}

	if (item->name      ) zt_stringFree(item->name, gm->arena);
	if (item->label     ) zt_stringFree(item->label, gm->arena);
	if (item->tooltip   ) zt_stringFree(item->tooltip, gm->arena);
	if (item->theme_type) zt_stringFree(item->theme_type, gm->arena);

	if (item->draw_list) {
		zt_drawListFree(item->draw_list);
		zt_freeArena(item->draw_list, gm->arena);
		item->draw_list = nullptr;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerFree(ztGuiManagerID gui_manager)
{
	zt_assert(gui_manager >= 0 && gui_manager < zt_elementsOf(zt_gui->gui_managers));

	if (zt_gui->gui_managers[gui_manager] == nullptr) {
		return;
	}

	ztGuiManager *gm = zt_gui->gui_managers[gui_manager];

	zt_fiz(zt_elementsOf(gm->item_cache)) {
		if (gm->item_cache_flags[i] != 0) {
			_zt_guiItemFree(gm, &gm->item_cache[i]);
		}
	}

	if (zt_bitIsSet(gm->internal_flags, ztGuiManagerInternalFlags_OwnsTheme)) {
		zt_fontFree(gm->default_theme.font);
		zt_textureFree(gm->default_theme.sprite_window.sns.tex);
	}

	zt_freeArena(zt_gui->gui_managers[gui_manager], zt_gui->gui_managers[gui_manager]->arena);
	zt_gui->gui_managers[gui_manager] = nullptr;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiItemReposition(ztGuiManager *gm, ztGuiItem *item)
{
	ztVec2 min, max;
	if (item->parent) {
		min = ztVec2(item->parent->size.x / -2.f, item->parent->size.y / -2.f);
		max = ztVec2(item->parent->size.x / 2.f, item->parent->size.y / 2.f);
	}
	else {
		zt_cameraOrthoGetExtents(gm->gui_camera, &min, &max);
	}

	item->pos = ztVec2::zero;

	if (zt_bitIsSet(item->pos_align_flags, ztAlign_Left  )) { item->pos.x = min.x; }
	if (zt_bitIsSet(item->pos_align_flags, ztAlign_Right )) { item->pos.x = max.x; }
	if (zt_bitIsSet(item->pos_align_flags, ztAlign_Top   )) { item->pos.y = max.y; }
	if (zt_bitIsSet(item->pos_align_flags, ztAlign_Bottom)) { item->pos.y = min.y; }

	if (zt_bitIsSet(item->pos_anchor_flags, ztAnchor_Left  )) { item->pos.x += item->size.x / 2.f; }
	if (zt_bitIsSet(item->pos_anchor_flags, ztAnchor_Right )) { item->pos.x -= item->size.x / 2.f; }
	if (zt_bitIsSet(item->pos_anchor_flags, ztAnchor_Top   )) { item->pos.y -= item->size.y / 2.f; }
	if (zt_bitIsSet(item->pos_anchor_flags, ztAnchor_Bottom)) { item->pos.y += item->size.y / 2.f; }

	item->pos.x += item->pos_offset.x;
	item->pos.y += item->pos_offset.y;
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerUpdate(ztGuiManagerID gui_manager, r32 dt)
{
	_zt_guiManagerCheckAndGet(gm, gui_manager);

	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] != 0) {
			zt_bitRemove(gm->item_cache_flags[i], ztGuiManagerItemCacheFlags_MouseOver);
		}
		if (gm->item_cache[i].functions.update) {
			gm->item_cache[i].functions.update(i, dt, gm->item_cache[i].functions.user_data);
		}
	}

	if (gm->gui_camera_w != gm->gui_camera->width || gm->gui_camera_h != gm->gui_camera->height) {
		gm->gui_camera_w = gm->gui_camera->width;
		gm->gui_camera_h = gm->gui_camera->height;

		ztVec2 cam_min, cam_max;
		zt_cameraOrthoGetExtents(gm->gui_camera, &cam_min, &cam_max);

		zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
			if ((gm->item_cache[i].pos_anchor_flags || gm->item_cache[i].pos_align_flags) && gm->item_cache[i].parent == nullptr) {
				_zt_guiItemReposition(gm, &gm->item_cache[i]);
			}
		}
	}

}

// ------------------------------------------------------------------------------------------------

bool zt_guiManagerHandleInput(ztGuiManagerID gui_manager, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], ztInputMouse *input_mouse)
{
	_zt_guiManagerCheckAndGet(gm, gui_manager);
	zt_returnValOnNull(gm, false);
	zt_returnValOnNull(input_keys, false);
	zt_returnValOnNull(input_mouse, false);

	bool mouse_captured = gm->item_has_mouse != ztInvalidID;
	if (mouse_captured) {
		_zt_guiItemFromID(mc_item, gm->item_has_mouse);
		if (mc_item && !zt_bitIsSet(mc_item->flags, ztGuiItemFlags_Visible)) {
			gm->item_has_mouse = ztInvalidID;
		}
	}

	if (gm->focus_item != ztInvalidID && zt_guiItemIsShowing(gm->focus_item)) {
		bool key_handled = false;
		_zt_guiItemFromID(f_item, gm->focus_item);
		if (!key_handled && f_item) {
			if (f_item->functions.input_key != nullptr) {
				if (f_item->functions.input_key(gm->focus_item, input_keys, input_key_strokes, f_item->functions.user_data)) {
					key_handled = true;
				}
			}
			f_item = f_item->parent;
		}		
	}

	bool mouse_pressed = input_mouse->leftPressed() || input_mouse->middlePressed() || input_mouse->rightPressed();
	gm->mouse_over_gui = false;
	gm->mouse_click = mouse_pressed;
	gm->mouse_click_ignored = mouse_pressed;

	ztGuiItem *child = gm->first_child;
	while (child && child->sib_next) {
		child = child->sib_next;
	}

	ztGuiItemID top_level_mouse_item = ztInvalidID;
	if (gm->item_has_mouse != ztInvalidID) {
		top_level_mouse_item = zt_guiItemGetTopLevelParent(gm->item_has_mouse);
	}

	ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);

	while (child) {
		bool process_input = true;
		if (top_level_mouse_item != ztInvalidID && top_level_mouse_item != child->id) {
			process_input = false;
		}
		if (process_input) {

			struct local
			{
				static bool mouseIntersecting(ztGuiItem *item, const ztVec2& mpos)
				{
					ztVec2 pos = zt_guiItemPositionLocalToScreen(item->id, ztVec2::zero);
					ztVec2 top_left = ztVec2(pos.x - item->size.x / 2.f, pos.y + item->size.y / 2.f);
					ztVec2 btm_right = ztVec2(pos.x + item->size.x / 2.f, pos.y - item->size.y / 2.f);

					if (mpos.x >= top_left.x && mpos.x < btm_right.x && mpos.y >= btm_right.y && mpos.y <= top_left.y) {
						return true;
					}
					return false;
				}

				// clicks and releases
				static bool processMouseFocusEvent(ztGuiManager *gm, ztGuiItem *item, ztInputMouse *input_mouse, const ztVec2& mpos)
				{
					if (!zt_bitIsSet(item->flags, ztGuiItemFlags_Visible)) {
						zt_assert(item->id != gm->item_has_mouse);
						return false;
					}

					if (gm->item_has_mouse != ztInvalidID && gm->item_has_mouse != item->id) {
						_zt_guiItemFromID(mi, gm->item_has_mouse);
						if (mi) {
							bool result = processMouseFocusEvent(gm, mi, input_mouse, mpos);
							if (gm->item_has_mouse != ztInvalidID && !zt_guiItemIsShowing(gm->item_has_mouse)) {
								gm->item_has_mouse = ztInvalidID;
							}
							return result;
						}
					}

					bool mouse_intersecting = mouseIntersecting(item, mpos);
					if ((mouse_intersecting && zt_bitIsSet(item->flags, ztGuiItemFlags_WantsInput)) || gm->item_has_mouse == item->id) {
						gm->mouse_over_gui = true;
					}

					// verify that the mouse is within this item's boundary
					if (gm->item_has_mouse != item->id) {
						if (mouse_intersecting || zt_bitIsSet(item->flags, ztGuiItemFlags_OutlyingChildren)) {
							// check each child first
							ztGuiItem *child = item->first_child;
							while (child) {
								if (processMouseFocusEvent(gm, child, input_mouse, mpos)) {
									return true;
								}
								child = child->sib_next;
							}
						}
						else return false; // the mouse is not captured and it's not in this item's area, so ignore
					}

					bool recv_focus = false;
					if (gm->focus_item != item->id) {
						if (zt_bitIsSet(item->flags, ztGuiItemFlags_WantsFocus)) {
							zt_guiItemSetFocus(item->id);
							recv_focus = true;
						}
					}
					if (item->parent == nullptr && mouse_intersecting) {
						recv_focus = true; // this prevents windows behind this top level window from receiving events
					}
					if (gm->tooltip_item == item->id && !mouse_intersecting) {
						gm->tooltip_item = ztInvalidID;
					}

					if(mouse_intersecting && gm->item_has_mouse == ztInvalidID && (input_mouse->leftJustPressed() || input_mouse->rightJustPressed() || input_mouse->middleJustPressed()) && zt_bitIsSet(item->flags, ztGuiItemFlags_WantsFocus)) {
						gm->item_has_mouse = item->id;
						recv_focus = true;
					}

					if (mouse_intersecting || gm->item_has_mouse == item->id) {
						if (mouse_intersecting) {
							gm->item_cache_flags[item->id] |= ztGuiManagerItemCacheFlags_MouseOver;
						}
						if (item->functions.input_mouse && item->functions.input_mouse(item->id, input_mouse, item->functions.user_data)) {
							recv_focus = true;
						}
					}

					if (gm->item_has_mouse == item->id && (input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased())) {
						gm->item_has_mouse = ztInvalidID;
					}
					return recv_focus;
				}

				// movements and scroll wheel
				static bool mouseProcessNonFocusEvent(ztGuiManager *gm, ztGuiItem *item, ztInputMouse *input_mouse, const ztVec2& mpos)
				{
					if (!zt_bitIsSet(item->flags, ztGuiItemFlags_Visible)) {
						zt_assert(item->id != gm->item_has_mouse);
						return false;
					}

					bool mouse_intersecting = mouseIntersecting(item, mpos);
					if (mouse_intersecting && zt_bitIsSet(item->flags, ztGuiItemFlags_WantsInput)) {
						gm->mouse_over_gui = true;
					}

					// verify that the mouse is within this item's boundary
					if (gm->item_has_mouse != item->id) {
						if (mouse_intersecting || zt_bitIsSet(item->flags, ztGuiItemFlags_OutlyingChildren)) {
							// check each child first
							ztGuiItem *child = item->first_child;
							while (child) {
								if (mouseProcessNonFocusEvent(gm, child, input_mouse, mpos)) {
									return true;
								}
								child = child->sib_next;
							}
						}
						else return false; // the mouse is not captured and it's not in this item's area, so ignore
					}

					bool handled_event = false;
					if (item->parent == nullptr && mouse_intersecting) {
						handled_event = true; // this prevents windows behind this top level window from receiving events
					}
					if (gm->tooltip_item == item->id && !mouse_intersecting) {
						gm->tooltip_item = ztInvalidID;
					}
					if (mouse_intersecting || gm->item_has_mouse == item->id) {
						if (mouse_intersecting) {
							gm->item_cache_flags[item->id] |= ztGuiManagerItemCacheFlags_MouseOver;
						}
						if (item->functions.input_mouse && item->functions.input_mouse(item->id, input_mouse, item->functions.user_data)) {
							return true;
						}
					}
					return handled_event;
				}
			};

			bool mouse_just_released = input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased();
			if (mouse_captured || input_mouse->leftPressed() || input_mouse->rightPressed() || input_mouse->middlePressed() ||
				input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased()) {
				if (local::processMouseFocusEvent(gm, child, input_mouse, mpos)) {
					if (zt_bitIsSet(child->flags, ztGuiItemFlags_BringToFront)) {
						// need to make this particular child the last in the series
						if (child->sib_next) {
							if (child->sib_prev) child->sib_prev->sib_next = child->sib_next;
							if (child->sib_next) child->sib_next->sib_prev = child->sib_prev;
							zt_assert(child->sib_next->sib_prev != child->sib_next);

							if (gm->first_child == child) {
								gm->first_child = child->sib_next;
							}

							ztGuiItem *last_child = gm->first_child;
							while (last_child->sib_next) {
								last_child = last_child->sib_next;
							}

							zt_assert(last_child != nullptr);
							last_child->sib_next = child;
							child->sib_prev = last_child;
							zt_assert(child->sib_prev != child);
							child->sib_next = nullptr;
						}
					}

					break; // exit the loop, the mouse has been handled
				}
			}
			else if (local::mouseProcessNonFocusEvent(gm, child, input_mouse, mpos)) {
				break; // exit the loop
			}

		}
		child = child->sib_prev;
	}

	bool result = gm->keyboard_focus;

	if (mouse_pressed) {
		if (!gm->mouse_over_gui) {
			result = gm->keyboard_focus = false; // user clicked in non-gui area of screen so give up focus
			gm->focus_item = ztInvalidID;
		}
		else result = true;
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddGuiThemeSprite(ztDrawList *draw_list, ztGuiThemeSprite *theme_sprite, const ztVec2& pos, const ztVec2& size)
{
	if (theme_sprite->type == ztGuiThemeSpriteType_Sprite) {
		if (!zt_real32Eq(size.x, theme_sprite->s.half_size.x * 2) || !zt_real32Eq(size.y, theme_sprite->s.half_size.y * 2)) {
			ztVec3 scale = ztVec3::one;
			scale.x = size.x / (theme_sprite->s.half_size.x * 2);
			scale.y = size.y / (theme_sprite->s.half_size.y * 2);

			zt_drawListAddSprite(draw_list, &theme_sprite->s, ztVec3(pos.x, pos.y, 0), ztVec3::zero, scale);
		}
		else {
			zt_drawListAddSprite(draw_list, &theme_sprite->s, ztVec3(pos.x, pos.y, 0));
		}
	}
	else {
		zt_drawListAddSpriteNineSlice(draw_list, &theme_sprite->sns, pos, size);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddGuiThemeButtonSprite(ztDrawList *draw_list, ztGuiThemeButtonSprite *theme_button_sprite, const ztVec2& pos, const ztVec2& size, bool highlighted, bool pressed)
{
	if (pressed) {
		zt_drawListAddGuiThemeSprite(draw_list, &theme_button_sprite->pressed, pos, size);
	}
	else if (highlighted) {
		zt_drawListAddGuiThemeSprite(draw_list, &theme_button_sprite->highlight, pos, size);
	}
	else {
		zt_drawListAddGuiThemeSprite(draw_list, &theme_button_sprite->normal, pos, size);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerRender(ztGuiManagerID gui_manager, ztDrawList *draw_list)
{
	zt_returnOnNull(draw_list);
	_zt_guiManagerCheckAndGet(gm, gui_manager);

	struct local
	{
		static void renderItem(ztGuiManager *gm, ztGuiItem *item, ztDrawList *draw_list, const ztVec2& offset)
		{
			if (!zt_bitIsSet(item->flags, ztGuiItemFlags_Visible)) {
				return;
			}

			ztVec2 pos = item->pos + offset;

			ztGuiTheme *theme = item->theme == nullptr ? &gm->default_theme : item->theme;

			bool clip = zt_bitIsSet(item->flags, ztGuiItemFlags_ClipContents);
			if (clip) {
				if (item->clip_area != ztVec4::zero) {
					zt_drawListPushClipRegion(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
				}
				else {
					zt_drawListPushClipRegion(draw_list, pos, item->size);
				}
			}

			if (item->functions.render) {
				item->functions.render(item->id, draw_list, theme, offset, item->functions.user_data);
			}

			zt_bitRemove(item->flags, ztGuiItemFlags_Dirty);

#if _DEBUG
			if (item->debug_highlight != ztVec4::zero) {
				zt_drawListPushColor(draw_list, item->debug_highlight);
				zt_drawListAddEmptyRect(draw_list, pos, item->size);
				zt_drawListPopColor(draw_list);
			}
#endif
			if (!clip && zt_bitIsSet(item->flags, ztGuiItemFlags_ClipChildren) ) {
				clip = true;
				if (item->clip_area != ztVec4::zero) {
					zt_drawListPushClipRegion(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
				}
				else {
					zt_drawListPushClipRegion(draw_list, pos, item->size);
				}
			}
			else if (clip && !zt_bitIsSet(item->flags, ztGuiItemFlags_ClipChildren)) {
				zt_drawListPopClipRegion(draw_list);
				clip = false;
			}

			ztGuiItem *child = item->first_child;
			while (child) {
				renderItem(gm, child, draw_list, pos);
				child = child->sib_next;
			}

			if (clip) {
				zt_drawListPopClipRegion(draw_list);
			}
		}
	};


	ztGuiItem *child = gm->first_child;
	while (child) {
		local::renderItem(gm, child, draw_list, ztVec2::zero);
		child = child->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSetActiveManager(ztGuiManagerID gui_manager)
{
	_zt_guiManagerCheckAndGet(gm, gui_manager);
	zt_gui->active_gui_manager = gui_manager;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_guiProcessDrag(ztGuiItem::ztDragState *drag_state, ztGuiManager *gm, ztVec2* pos, ztInputMouse *input_mouse)
{
	if (drag_state->dragging) {
		if (input_mouse->leftJustReleased()) {
			drag_state->dragging = false;
		}
		else {
			ztVec2 drag_pos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
			*pos = drag_pos - ztVec2(drag_state->offset_x, drag_state->offset_y);
		}
		return true;
	}
	else {
		if (input_mouse->leftJustPressed()) {
			drag_state->dragging = true;
			ztVec2 drag_start = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
			drag_state->offset_x = drag_start.x - pos->x;
			drag_state->offset_y = drag_start.y - pos->y;
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItem *_zt_guiMakeItemBase(ztGuiManager *gm, ztGuiItemID parent, ztGuiItemType_Enum type, i32 item_flags, ztGuiItemID *id, i32 draw_list_size = 0)
{
	*id = ztInvalidID;

	ztGuiItem *item = nullptr;
	ztGuiItemID item_id = ztInvalidID;

	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] == 0) {
			gm->item_cache_flags[i] |= ztGuiManagerItemCacheFlags_Used;
			item_id = gm->base_id + i;
			item = &gm->item_cache[i];
			break;
		}
	}

	zt_assert(item != nullptr);
	if (item == nullptr) {
		return nullptr;
	}

	zt_memSet(item, zt_sizeof(ztGuiItem), 0);
	item->id = item_id;
	item->type = type;
	item->flags = item_flags | ztGuiItemFlags_Visible | ztGuiItemFlags_Dirty;
	item->color = ztVec4::one;

	if (draw_list_size != 0) {
		item->draw_list = zt_mallocStruct(ztDrawList);
		zt_drawListMake(item->draw_list, draw_list_size, 0, gm->arena);
	}

	zt_debugOnly(item->debug_highlight = ztVec4::zero);

	_zt_guiItemFromID(gi_parent, parent);
	if (gi_parent != nullptr) {
		item->parent = gi_parent;

		ztGuiItem* last_child = gi_parent->first_child;
		if (!last_child) {
			gi_parent->first_child = item;
		}
		else {
			while (last_child->sib_next) {
				last_child = last_child->sib_next;
			}
			last_child->sib_next = item;
			item->sib_prev = last_child;
		}
	}
	else {
		ztGuiItem *last_child = gm->first_child;
		if (last_child == nullptr) {
			gm->first_child = item;
		}
		else {
			while (last_child->sib_next) {
				last_child = last_child->sib_next;
			}
			last_child->sib_next = item;
			item->sib_prev = last_child;
		}
	}

	*id = item_id;
	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeWindow(const char *title, i32 flags)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
			ztVec2 pos = offset + item->pos;
			if (zt_bitIsSet(item->window.flags, ztGuiWindowFlags_ShowTitle)) {
				zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_window, pos, item->size);

				if (item->label) {
					ztVec2 font_ext = zt_fontGetExtents(theme->font, item->label);
					ztVec2 font_pos = ztVec2(pos.x, pos.y + (item->size.y / 2.f) - (theme->window_title_height / 2.f));
					i32 font_align = 0, font_anchor = 0;

					if (zt_bitIsSet(theme->window_title_align, ztAlign_Left)) { font_pos.x = pos.x - (item->size.x / 2.f) + theme->window_title_padding_x;  font_align |= ztAlign_Left; font_anchor |= ztAnchor_Left; }
					else if (zt_bitIsSet(theme->window_title_align, ztAlign_Right)) { font_pos.x = pos.x + (item->size.x / 2.f) - theme->window_title_padding_x; font_align |= ztAlign_Right; font_anchor |= ztAnchor_Right; }

					if (zt_bitIsSet(theme->window_title_align, ztAlign_Top)) { font_pos.y += (theme->window_title_height / 2.f) - theme->window_title_padding_y; font_align |= ztAlign_Top; font_anchor |= ztAnchor_Top; }
					else if (zt_bitIsSet(theme->window_title_align, ztAlign_Bottom)) { font_pos.y -= (theme->window_title_height / 2.f) - theme->window_title_padding_y; font_align |= ztAlign_Bottom; font_anchor |= ztAnchor_Bottom; }

					zt_drawListAddText2D(draw_list, theme->font, item->label, font_pos, font_align, font_anchor);
				}
			}
			else {
				zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_panel, pos, item->size);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);
			return _zt_guiProcessDrag(&item->window.drag_state, gm, &item->pos, input_mouse);
		}
	};

	_zt_guiManagerGetFromItem(gm, ztInvalidID);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, ztInvalidID, ztGuiItemType_Window, ztGuiItemFlags_WantsInput | ztGuiItemFlags_WantsFocus | ztGuiItemFlags_Visible | ztGuiItemFlags_BringToFront | ztGuiItemFlags_ClipChildren, &item_id);
	if (!item) return ztInvalidID;

	item->functions.render = local::render;
	item->functions.user_data = gm;

	zt_guiItemSetSize(item_id, ztVec2(7, 5));
	zt_guiItemSetLabel(item_id, title);

	item->window.flags = flags;

	item->functions.input_mouse = local::inputMouse;

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakePanel(ztGuiItemID parent, i32 item_flags)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
			ztVec2 pos = offset + item->pos;
			zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_panel, pos, item->size);
		}
	};

	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Panel, item_flags, &item_id);
	if (!item) return ztInvalidID;

	item->functions.render = local::render;
	item->functions.user_data = gm;

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeStaticText(ztGuiItemID parent, const char *label, int max_chars)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (zt_bitIsSet(item->flags, ztGuiItemFlags_Dirty)) {
				if (item->draw_list) {
					ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
					zt_drawListReset(item->draw_list);
					zt_drawListAddText2D(item->draw_list, theme->font, item->label, ztVec2::zero, item->align_flags, item->anchor_flags);
				}
			}

			zt_drawListAddDrawList(draw_list, item->draw_list, ztVec3(offset + item->pos, 0));
		}
	};

	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Text, 0, &item_id, zt_max(zt_strLen(label), max_chars) * 2);
	if (!item) return ztInvalidID;

	item->functions.render = local::render;
	item->functions.user_data = gm;

	zt_guiItemSetLabel(item_id, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
	zt_assert(theme);

	item->size = zt_fontGetExtents(theme->font, label);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

enum ztGuiButtonInternalFlags_Enum
{
	ztGuiButtonInternalFlags_IsToggleButton = (1<<31),
	ztGuiButtonInternalFlags_IsToggled      = (1<<30),
	ztGuiButtonInternalFlags_IsCheckbox     = (1<<29),
	ztGuiButtonInternalFlags_IsRadio        = (1<<28),
};

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItemID _zt_guiMakeButtonBase(ztGuiItemID parent, const char *label, i32 flags, bool *live_value)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);
			if (input_mouse->leftJustReleased()) {
				if (gm->item_has_mouse == item_id && zt_bitIsSet(gm->item_cache_flags[item_id], ztGuiManagerItemCacheFlags_MouseOver)) {
					bool value = true;
					if (zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggleButton)) {
						value = !zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
						if (value) {
							item->button.flags |= ztGuiButtonInternalFlags_IsToggled;
						}
						else {
							zt_bitRemove(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
						}
					}
					if (zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsRadio)) {
						value = true;
						item->button.flags |= ztGuiButtonInternalFlags_IsToggled;

						ztGuiItem *sib = item->parent ? item->parent->first_child : nullptr;
						while (sib) {
							if (sib->type == ztGuiItemType_RadioButton && sib != item) {
								zt_bitRemove(sib->button.flags, ztGuiButtonInternalFlags_IsToggled);
								if (sib->button.live_value) {
									*sib->button.live_value = false;
								}
							}
							sib = sib->sib_next;
						}
					}
					if (item->button.live_value) {
						*item->button.live_value = value;
					}
					if (item->button.on_pressed) {
						item->button.on_pressed(item_id);
					}
					return true;
				}
			}
			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
			if (zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggleButton)) {
				if (item->button.live_value) {
					if (*item->button.live_value) {
						item->button.flags |= ztGuiButtonInternalFlags_IsToggled;
					}
					else {
						zt_bitRemove(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
					}
				}
			}
			else if (item->button.live_value && *item->button.live_value) {
				*item->button.live_value = false;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;

			bool checkbox = zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsCheckbox);
			bool radio    = zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsRadio);

			if (checkbox || radio) {
				ztVec2 box_size = checkbox ? ztVec2(theme->checkbox_size_w, theme->checkbox_size_h) : ztVec2(theme->radio_size_w, theme->radio_size_h);
				ztVec2 box_pos, txt_size, txt_pos;

				if (item->label) {
					txt_size = zt_fontGetExtents(theme->font, item->label);
					if (zt_bitIsSet(item->button.flags, ztGuiCheckboxFlags_RightText)) {
						box_pos = ztVec2((item->size.x - box_size.x) / -2.f + theme->padding, 0);
						txt_pos =  ztVec2(box_pos.x + box_size.x / 2.f + theme->spacing, 0);
					}
					else {
						txt_pos = ztVec2(item->size.x / -2.f + theme->padding, 0);
						box_pos = ztVec2((item->size.x / 2.f) - (box_size.x / 2.f + theme->spacing), 0);
					}

					zt_drawListAddText2D(draw_list, theme->font, item->label, zt_strLen(item->label), txt_pos + pos, ztAlign_Left, ztAnchor_Left);
				}

				box_pos += pos;

				ztGuiThemeButtonSprite *sprite = checkbox ? &theme->sprite_checkbox : &theme->sprite_radio;
				ztGuiThemeSprite *sprite_check = checkbox ? &theme->sprite_checkbox_check : &theme->sprite_radio_check;

				bool highlighted = zt_bitIsSet(gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
				bool pressed = highlighted && gm->item_has_mouse == item->id;
				zt_drawListAddGuiThemeButtonSprite(draw_list, sprite, box_pos, box_size, highlighted, pressed);

				if (zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled)) {
					zt_drawListAddGuiThemeSprite(draw_list, sprite_check, box_pos, box_size);
				}
			}
			else {
				if (!zt_bitIsSet(item->button.flags, ztGuiButtonFlags_NoBackground)) {
					bool highlighted = zt_bitIsSet(gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
					bool pressed = gm->item_has_mouse == item->id || (!highlighted && zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled));
					zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_button, pos, item->size, highlighted, pressed);
				}
				ztVec2 text_pos = ztVec2::zero;
				if (item->button.icon) {
					ztVec2 text_size = item->label ? zt_fontGetExtents(theme->font, item->label) : ztVec2::zero;
					ztVec2 content_size = ztVec2::zero;
					ztVec2 icon_size(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);
					ztVec2 icon_pos = ztVec2::zero;

					if (item->label != nullptr) {
						if (zt_bitIsSet(item->button.text_pos, ztAlign_Left)) {
							content_size = ztVec2(text_size.x + icon_size.x + theme->button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + theme->button_padding_h * 1.f);
							icon_pos.x = (content_size.x - icon_size.x) / 2.f;
							text_pos.x = (content_size.x - text_size.x) / -2.f;
						}
						else if (zt_bitIsSet(item->button.text_pos, ztAlign_Right)) {
							content_size = ztVec2(text_size.x + icon_size.x + theme->button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + theme->button_padding_h * 1.f);
							icon_pos.x = (content_size.x - icon_size.x) / -2.f;
							text_pos.x = (content_size.x - text_size.x) / 2.f;
						}
						else if (zt_bitIsSet(item->button.text_pos, ztAlign_Top)) {
							content_size = ztVec2(zt_max(text_size.x, icon_size.x) + theme->button_padding_w * 1.f, text_size.y + icon_size.y + theme->button_padding_h * 1.f);
							icon_pos.y = (content_size.y - icon_size.y) / -2.f;
							text_pos.y = (content_size.y - text_size.y) / 2.f;
						}
						else if (zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
							content_size = ztVec2(zt_max(text_size.x, icon_size.x) + theme->button_padding_w * 1.f, text_size.y + icon_size.y + theme->button_padding_h * 1.f);
							icon_pos.y = (content_size.y - icon_size.y) / 2.f;
							text_pos.y = (content_size.y - text_size.y) / -2.f;
						}
					}
					else {
						content_size = icon_size;
					}

					ztVec2 item_size = ztVec2(item->size.x - theme->button_padding_w * 2.f, item->size.y - theme->button_padding_h * 2.f);
					if (zt_bitIsSet(item->align_flags, ztAlign_Left)) {
						if (zt_bitIsSet(item->button.text_pos, ztAlign_Top) || zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
							text_pos.x += (item_size.x - content_size.x) / -2.f;
							icon_pos.x += (item_size.x - content_size.x) / -2.f;
							text_pos.x += (content_size.x - text_size.x) / -2.f;
							icon_pos.x += (content_size.x - icon_size.x) / -2.f;
						}
						else {
							pos.x += (item_size.x - content_size.x) / -2.f;
						}
					}
					else if (zt_bitIsSet(item->align_flags, ztAlign_Right)) {
						if (zt_bitIsSet(item->button.text_pos, ztAlign_Top) || zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
							text_pos.x += (item_size.x - content_size.x) / 2.f;
							icon_pos.x += (item_size.x - content_size.x) / 2.f;
							text_pos.x += (content_size.x - text_size.x) / 2.f;
							icon_pos.x += (content_size.x - icon_size.x) / 2.f;
						}
						else {
							pos.x += (item_size.x - content_size.x) / 2.f;
						}
					}
					if (zt_bitIsSet(item->align_flags, ztAlign_Top)) {
						if (zt_bitIsSet(item->button.text_pos, ztAlign_Top) || zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
							pos.y += (item_size.y - content_size.y) / 2.f;
						}
						else {
							text_pos.y += (item_size.y - content_size.y) / 2.f;
							icon_pos.y += (item_size.y - content_size.y) / 2.f;
							text_pos.y += (content_size.y - text_size.y) / 2.f;
							icon_pos.y += (content_size.y - icon_size.y) / 2.f;
						}
					}
					if (zt_bitIsSet(item->align_flags, ztAlign_Bottom)) {
						if (zt_bitIsSet(item->button.text_pos, ztAlign_Top) || zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
							pos.y += (item_size.y - content_size.y) / -2.f;
						}
						else {
							text_pos.y += (item_size.y - content_size.y) / -2.f;
							icon_pos.y += (item_size.y - content_size.y) / -2.f;
							text_pos.y += (content_size.y - text_size.y) / -2.f;
							icon_pos.y += (content_size.y - icon_size.y) / -2.f;
						}
					}

					icon_pos.x += pos.x;
					icon_pos.y += pos.y;

 					zt_drawListAddSprite(draw_list, item->button.icon, ztVec3(icon_pos, 0));
				}
				if (item->label) {
					zt_drawListAddText2D(draw_list, theme->font, item->label, pos + text_pos);
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			if (zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsCheckbox) || zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsRadio)) {
				ztVec2 txt_size = zt_fontGetExtents(theme->font, item->label);
				size->x = txt_size.x + theme->spacing + theme->checkbox_size_w + theme->padding * 2;
				size->y = zt_max(txt_size.y, theme->checkbox_size_h) + theme->padding * 2;
				*min_size = *size;
			}
			else {
				if (item->button.icon) {
					ztVec2 text_size = item->label ? zt_fontGetExtents(theme->font, item->label) : ztVec2::zero;
					ztVec2 content_size = ztVec2::zero;
					ztVec2 icon_size(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);
					ztVec2 icon_pos = ztVec2::zero;

					if (zt_bitIsSet(item->button.text_pos, ztAlign_Left)) {
						content_size = ztVec2(text_size.x + icon_size.x + theme->button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + theme->button_padding_h * 1.f);
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Right)) {
						content_size = ztVec2(text_size.x + icon_size.x + theme->button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + theme->button_padding_h * 1.f);
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Top)) {
						content_size = ztVec2(zt_max(text_size.x, icon_size.x) + theme->button_padding_w * 1.f, text_size.y + icon_size.y + theme->button_padding_h * 1.f);
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
						content_size = ztVec2(zt_max(text_size.x, icon_size.x) + theme->button_padding_w * 1.f, text_size.y + icon_size.y + theme->button_padding_h * 1.f);
					}
					else {
						content_size.x = zt_max(icon_size.x, text_size.x);
						content_size.y = zt_max(icon_size.y, text_size.y);
					}

					content_size.x += theme->button_padding_w * 2.f;
					content_size.y += theme->button_padding_h * 2.f;

					*size = content_size;
				}
				else {
					ztVec2 txt_size = zt_fontGetExtents(theme->font, item->label);
					r32 min_x = txt_size.x + theme->padding * 2;
					r32 min_y = txt_size.y + theme->padding * 2;
					if (min_size) {
						min_size->x = min_x;
						min_size->y = min_y;
					}
					size->x = zt_max(min_x, theme->button_default_w);
					size->y = zt_max(min_y, theme->button_default_h);
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			if (item->button.icon) {
				zt_freeArena(item->button.icon, gm->arena);
			}
		}
	};


	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Button, ztGuiItemFlags_WantsInput | ztGuiItemFlags_WantsFocus, &item_id, zt_strLen(label) * 2);
	if (!item) return ztInvalidID;

	zt_guiItemSetLabel(item_id, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	if (label) {
		if (theme) {
			ztVec2 text = zt_fontGetExtents(theme->font, label);
			text.x = zt_max(theme->button_default_w, text.x + theme->button_padding_w * 2);
			text.y = zt_max(theme->button_default_h, text.y + theme->button_padding_h * 2);
			item->size = text;
		}
	}

	item->button.live_value = live_value;
	item->button.flags = flags;
	item->button.on_pressed = nullptr;
	item->button.icon = nullptr;
	item->button.text_pos = 0;

	item->functions.input_mouse = local::inputMouse;
	item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	if (item->button.live_value) {
		*item->button.live_value = false;
		item->functions.update = local::update;
	}

	ztVec2 min_size;
	local::best_size(item->id, &min_size, nullptr, &item->size, theme, gm);

	if (zt_bitIsSet(flags, ztGuiButtonInternalFlags_IsToggleButton)) {
		if (zt_bitIsSet(flags, ztGuiButtonInternalFlags_IsCheckbox)) {
			item->type = ztGuiItemType_Checkbox;
		}
		else if (zt_bitIsSet(flags, ztGuiButtonInternalFlags_IsRadio)) {
			item->type = ztGuiItemType_RadioButton;
		}
		else {
			item->type = ztGuiItemType_ToggleButton;
		}
	}

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeButton(ztGuiItemID parent, const char *label, i32 flags, bool *live_value)
{
	return _zt_guiMakeButtonBase(parent, label, flags, live_value);
}

// ------------------------------------------------------------------------------------------------

void zt_guiButtonSetIcon(ztGuiItemID button, ztSprite *icon)
{
	zt_returnOnNull(icon);

	_zt_guiItemFromID(item, button);
	_zt_guiManagerGetFromItem(gm, button);
	zt_returnOnNull(gm);
	zt_returnOnNull(item);
	zt_assert(item->type == ztGuiItemType_Button || item->type == ztGuiItemType_ToggleButton);

	item->button.icon = zt_mallocStructArena(ztSprite, gm->arena);
	*item->button.icon = *icon;

	item->functions.best_size(item->id, nullptr, nullptr, &item->size, zt_guiItemGetTheme(button), item->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiButtonSetTextPosition(ztGuiItemID button, i32 align_flags)
{
	_zt_guiItemFromID(item, button);
	_zt_guiManagerGetFromItem(gm, button);
	zt_returnOnNull(gm);
	zt_returnOnNull(item);
	zt_assert(item->type == ztGuiItemType_Button || item->type == ztGuiItemType_ToggleButton);

	item->button.text_pos = align_flags;
}

// ------------------------------------------------------------------------------------------------

void zt_guiButtonSetCallback(ztGuiItemID button, zt_guiButtonPressed_Func on_pressed)
{
	_zt_guiItemFromID(item, button);
	zt_returnOnNull(item);
	zt_assert(item->type == ztGuiItemType_Button || item->type == ztGuiItemType_ToggleButton || item->type == ztGuiItemType_Checkbox || item->type == ztGuiItemType_RadioButton);

	item->button.on_pressed = on_pressed;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeToggleButton(ztGuiItemID parent, const char *label, i32 flags, bool *live_value)
{
	return _zt_guiMakeButtonBase(parent, label, flags | ztGuiButtonInternalFlags_IsToggleButton, live_value);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiToggleButtonGetValue(ztGuiItemID button)
{
	_zt_guiItemFromID(item, button);
	zt_returnValOnNull(item, false);
	zt_assert(item->type ==ztGuiItemType_ToggleButton);

	return zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
}

// ------------------------------------------------------------------------------------------------

void zt_guiToggleButtonSetValue(ztGuiItemID button, bool value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, button, ztGuiItemType_ToggleButton);

	if (value) {
		item->button.flags |= ztGuiButtonInternalFlags_IsToggled;
	}
	else {
		zt_bitRemove(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
	}
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeCheckbox(ztGuiItemID parent, const char *label, i32 flags, bool *live_value)
{
	return _zt_guiMakeButtonBase(parent, label, flags | ztGuiButtonInternalFlags_IsToggleButton | ztGuiButtonInternalFlags_IsCheckbox, live_value);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiCheckboxGetValue(ztGuiItemID checkbox)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, checkbox, ztGuiItemType_Checkbox, false);

	return zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
}

// ------------------------------------------------------------------------------------------------

void zt_guiCheckboxSetValue(ztGuiItemID checkbox, bool value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, checkbox, ztGuiItemType_Checkbox);

	if (value) {
		item->button.flags |= ztGuiButtonInternalFlags_IsToggled;
	}
	else {
		zt_bitRemove(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
	}
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeRadioButton(ztGuiItemID parent, const char *label, i32 flags, bool *live_value)
{
	return _zt_guiMakeButtonBase(parent, label, flags | ztGuiButtonInternalFlags_IsToggleButton | ztGuiButtonInternalFlags_IsRadio, live_value);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiRadioGetValue(ztGuiItemID radio)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, radio, ztGuiItemType_RadioButton, false);

	return zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
}

// ------------------------------------------------------------------------------------------------

void zt_guiRadioSetValue(ztGuiItemID radio, bool value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, radio, ztGuiItemType_RadioButton);

	if (value) {
		item->button.flags |= ztGuiButtonInternalFlags_IsToggled;
	}
	else {
		zt_bitRemove(item->button.flags, ztGuiButtonInternalFlags_IsToggled);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItemID _zt_guiMakeSliderBase(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value, bool scrollbar)
{
	enum ztGuiSliderInternalFlags_Enum
	{
		ztGuiSliderInternalFlags_NegHighlight = (1<<31),
		ztGuiSliderInternalFlags_PosHighlight = (1<<30),
		ztGuiSliderInternalFlags_NegPressed   = (1<<29),
		ztGuiSliderInternalFlags_PosPressed   = (1<<28),
	};

	struct local
	{
		static r32 getHandleSize(ztGuiItem *item, ztGuiTheme *theme)
		{
			if (item->type == ztGuiItemType_Slider) {
				return theme->slider_handle_w;
			}
			else {
				r32 size = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;
				if (theme->scrollbar_has_buttons) {
					size -= theme->scrollbar_button_w * 2;
				}

				return zt_max(theme->scrollbar_handle_min_size, size * item->slider.handle_pct);
			}
		}

		// ------------------------------------------------------------------------------------

		static r32 getHandlePos(ztGuiItem *item, ztGuiTheme *theme)
		{
			r32 value = item->slider.orient == ztGuiItemOrient_Horz ? item->slider.value : 1.f - item->slider.value;
			r32 size_item = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;

			if (item->type == ztGuiItemType_Slider) {
				r32 size_value = size_item - theme->slider_handle_w;
				r32 handle_size = item->slider.orient == ztGuiItemOrient_Horz ? theme->slider_handle_w : theme->slider_handle_w;

				return (size_item / -2.f) + (size_value * value) + handle_size / 2.f;
			}
			else {
				r32 handle_size = getHandleSize(item, theme);
				r32 size_value = size_item - handle_size;

				r32 offset = handle_size / 2.f;
				if (theme->scrollbar_has_buttons) {
					offset += theme->scrollbar_button_w;
					size_value -= theme->scrollbar_button_w * 2;
				}

				return (size_item / -2.f) + (size_value * value) + offset;
			}
		}

		// ------------------------------------------------------------------------------------

		static int mouseOverButton(ztGuiManager *gm, ztGuiItem *item, ztGuiTheme *theme, ztVec2& mpos) // 0 = none, -1 = neg, 1 = pos
		{
			if (item->type != ztGuiItemType_Scrollbar || !zt_bitIsSet(gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver)) {
				return 0;
			}

			if (item->slider.orient == ztGuiItemOrient_Horz) {
				if (mpos.x <= item->size.x / -2.f + theme->scrollbar_button_w) return -1;
				else if (mpos.x >= item->size.x / 2.f - theme->scrollbar_button_w) return 1;
			}
			else {
				if (mpos.y <= item->size.y / -2.f + theme->scrollbar_button_w) return 1;
				else if (mpos.y >= item->size.y / 2.f - theme->scrollbar_button_w) return -1;
			}

			return 0;
		}

		// ------------------------------------------------------------------------------------

		static void processDragReturn(ztGuiManager *gm, ztGuiItem *item, ztGuiTheme *theme, ztInputMouse *input_mouse)
		{
			ztVec2 mouse_pos = zt_guiItemPositionScreenToLocal(item->id, zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));
			if (item->type == ztGuiItemType_Slider) {
				if (item->slider.orient == ztGuiItemOrient_Horz) {
					r32 pos_x = (mouse_pos.x - item->slider.drag_state.offset_x) + ((item->size.x - theme->slider_handle_w) / 2);
					item->slider.value = zt_clamp(pos_x / (item->size.x - theme->slider_handle_w), 0, 1);
				}
				else {
					r32 pos_y = (mouse_pos.y - item->slider.drag_state.offset_y) + ((item->size.y - theme->slider_handle_w) / 2);
					item->slider.value = zt_clamp(1.f - (pos_y / (item->size.y - theme->slider_handle_w)), 0, 1);
				}
			}
			else {
				r32 handle_size = getHandleSize(item, theme);
				r32 size_item = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;
				r32 size_value = size_item - handle_size;

				if (theme->scrollbar_has_buttons) {
					size_value -= theme->scrollbar_button_w * 2;

					if (zt_real32Eq(size_value, 0.f)) {
						size_value = 0.01f;
					}
				}

				if (item->slider.orient == ztGuiItemOrient_Horz) {
					r32 pos_x = (mouse_pos.x - item->slider.drag_state.offset_x) + (size_value / 2);
					item->slider.value = zt_clamp(pos_x / size_value, 0, 1);
				}
				else {
					r32 pos_y = (mouse_pos.y - item->slider.drag_state.offset_y) + (size_value / 2);
					item->slider.value = zt_clamp(1.f - (pos_y / size_value), 0, 1);
				}
			}
			if (item->slider.live_value) {
				*item->slider.live_value = item->slider.value;
			}
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (!item->slider.drag_state.dragging) {
				item->slider.value = *item->slider.live_value;

				if (item->type == ztGuiItemType_Scrollbar) {
					if (zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegPressed) && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegHighlight)) {
						item->slider.press_time -= dt;
						if (item->slider.press_time <= 0) {
							zt_guiScrollbarStepNeg(item_id);
							item->slider.press_time = .1f;
						}
					}
					if (zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosPressed) && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosHighlight)) {
						item->slider.press_time -= dt;
						if (item->slider.press_time <= 0) {
							zt_guiScrollbarStepPos(item_id);
							item->slider.press_time = .1f;
						}
					}

					zt_bitRemove(item->flags, ztGuiSliderInternalFlags_NegHighlight | ztGuiSliderInternalFlags_PosHighlight);
				}
			}
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);
			if (!item->slider.drag_state.dragging) {
				ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
				ztVec2 mouse_pos = zt_guiItemPositionScreenToLocal(item->id, zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));

				int button = mouseOverButton(gm, item, theme, mouse_pos);
				if (button == -1) { item->flags |= ztGuiSliderInternalFlags_NegHighlight; }
				else if (button ==  1) { item->flags |= ztGuiSliderInternalFlags_PosHighlight; }

				if (!input_mouse->leftPressed()) {
					zt_bitRemove(item->flags, ztGuiSliderInternalFlags_NegPressed | ztGuiSliderInternalFlags_PosPressed);
				}
				
				if (button != 0) {
					if (input_mouse->leftJustPressed()) {
						if (button == -1) {
							item->flags |= ztGuiSliderInternalFlags_NegPressed;
							zt_guiScrollbarStepNeg(item_id);
							item->slider.press_time = 0.25f;
						}
						else if (button == 1) {
							item->flags |= ztGuiSliderInternalFlags_PosPressed;
							zt_guiScrollbarStepPos(item_id);
							item->slider.press_time = 0.25f;
						}
					}
				}
				else if (zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegPressed) || zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosPressed)) {
					// do nothing
				}
				else {
					if (item->slider.orient == ztGuiItemOrient_Horz) {
						ztVec2 handle_pos = ztVec2(getHandlePos(item, theme), 0);
						r32 handle_size = getHandleSize(item, theme);
						if (mouse_pos.x >= handle_pos.x - handle_size / 2.f && mouse_pos.x <= handle_pos.x + handle_size / 2.f) {
							item->slider.drag_pos[0] = zt_guiItemPositionLocalToScreen(item_id, handle_pos).x;
							item->slider.drag_pos[1] = 0;
							item->slider.highlight = true;
							if (_zt_guiProcessDrag(&item->slider.drag_state, gm, (ztVec2*)item->slider.drag_pos, input_mouse)) {
								processDragReturn(gm, item, theme, input_mouse);
								return true;
							}
							return false;
						}
						else if (input_mouse->leftJustPressed()) {
							if (item->type == ztGuiItemType_Scrollbar) {
								if (mouse_pos.x < handle_pos.x) zt_guiScrollbarStepPageNeg(item_id);
								else zt_guiScrollbarStepPagePos(item_id);
							}
							else {
								processDragReturn(gm, item, theme, input_mouse);
								return true;
							}
						}
					}
					else {
						ztVec2 handle_pos = ztVec2(0, getHandlePos(item, theme));
						r32 handle_size = getHandleSize(item, theme);
						if (mouse_pos.y >= handle_pos.y - handle_size / 2.f && mouse_pos.y <= handle_pos.y + handle_size / 2.f) {
							item->slider.drag_pos[0] = 0;
							item->slider.drag_pos[1] = zt_guiItemPositionLocalToScreen(item_id, handle_pos).y;
							item->slider.highlight = true;
							if (_zt_guiProcessDrag(&item->slider.drag_state, gm, (ztVec2*)item->slider.drag_pos, input_mouse)) {
								processDragReturn(gm, item, theme, input_mouse);
								return true;
							}
							return false;
						}
						else if (input_mouse->leftJustPressed()) {
							if (item->type == ztGuiItemType_Scrollbar) {
								if (mouse_pos.x < handle_pos.x) zt_guiScrollbarStepPageNeg(item_id);
								else zt_guiScrollbarStepPagePos(item_id);
							}
							else {
								processDragReturn(gm, item, theme, input_mouse);
								return true;
							}
						}
					}
				}
			}
			else if (_zt_guiProcessDrag(&item->slider.drag_state, gm, (ztVec2*)item->slider.drag_pos, input_mouse)) {
				item->slider.highlight = true;
				ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
				processDragReturn(gm, item, theme, input_mouse);
				return true;
			}
			item->slider.highlight = false;
			return false;
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;
			ztVec2 handle_pos, handle_size;

			ztGuiThemeSprite *sprite_background = (item->type == ztGuiItemType_Slider ? &theme->sprite_slider_background : &theme->sprite_scrollbar_background);

			if (item->slider.orient == ztGuiItemOrient_Horz) {
				handle_pos = pos + ztVec2(getHandlePos(item, theme), 0);

				if (item->type == ztGuiItemType_Slider) {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_slider_background, pos, ztVec2(item->size.x, theme->slider_background_h));
					handle_size = ztVec2(theme->slider_handle_w, theme->slider_handle_h);
				}
				else {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_scrollbar_background, pos, item->size);
					handle_size = ztVec2(getHandleSize(item, theme), theme->scrollbar_button_h);

					if (theme->scrollbar_has_buttons) {
						ztVec2 btn_size(theme->scrollbar_button_w, theme->scrollbar_button_h);

						bool neg_highlight = zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegHighlight), neg_pressed = neg_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegPressed),
							 pos_highlight = zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosHighlight), pos_pressed = pos_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosPressed);

						zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_scrollbar_horz_button_neg, pos + ztVec2(item->size.x / -2.f + theme->scrollbar_button_w / 2.f, 0), btn_size, neg_highlight, neg_pressed);
						zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_scrollbar_horz_button_pos, pos + ztVec2(item->size.x / 2.f - theme->scrollbar_button_w / 2.f, 0), btn_size, pos_highlight, pos_pressed);
					}
				}
			}
			else {
				handle_pos = pos + ztVec2(0, getHandlePos(item, theme));
				if (item->type == ztGuiItemType_Slider) {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_slider_background, pos, ztVec2(theme->slider_background_h, item->size.y));
					handle_size = ztVec2(theme->slider_handle_h, theme->slider_handle_w);
				}
				else {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_scrollbar_background, pos, item->size);
					handle_size = ztVec2(theme->scrollbar_button_h, getHandleSize(item, theme));

					if (theme->scrollbar_has_buttons) {
						ztVec2 btn_size(theme->scrollbar_button_h, theme->scrollbar_button_w);

						bool neg_highlight = zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegHighlight), neg_pressed = neg_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegPressed),
							 pos_highlight = zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosHighlight), pos_pressed = pos_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosPressed);

						zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_scrollbar_vert_button_neg, pos + ztVec2(0, item->size.y / 2.f - theme->scrollbar_button_w / 2.f), btn_size, neg_highlight, neg_pressed);
						zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_scrollbar_vert_button_pos, pos + ztVec2(0, item->size.y / -2.f + theme->scrollbar_button_w / 2.f), btn_size, pos_highlight, pos_pressed);
					}
				}
			}


			bool highlight = item->slider.highlight && zt_bitIsSet(gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
			bool pressed = item->slider.drag_state.dragging;
			ztGuiThemeButtonSprite *sprite_handle = item->slider.orient == ztGuiItemOrient_Horz ? (item->type == ztGuiItemType_Slider ? &theme->sprite_slider_horz_handle : &theme->sprite_scrollbar_horz_handle) : (item->type == ztGuiItemType_Slider ? &theme->sprite_slider_vert_handle : &theme->sprite_scrollbar_vert_handle);
			zt_drawListAddGuiThemeButtonSprite(draw_list, sprite_handle, handle_pos, handle_size, highlight, pressed);
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			if (item->type == ztGuiItemType_Slider) {
				if (item->slider.orient == ztGuiItemOrient_Horz) {
					min_size->x = theme->slider_handle_w * 2 + theme->padding * 2;
					min_size->y = zt_max(theme->slider_handle_h, theme->slider_background_h);
				}
				else {
					min_size->y = theme->slider_handle_w * 2 + theme->padding * 2;
					min_size->x = zt_max(theme->slider_handle_h, theme->slider_background_h);
				}
			}
			else {
				if (item->slider.orient == ztGuiItemOrient_Horz) {
					min_size->x = theme->scrollbar_button_w * 2;
					min_size->y = theme->scrollbar_button_h;
				}
				else {
					min_size->x = theme->scrollbar_button_h;
					min_size->y = theme->scrollbar_button_w * 2;
				}
			}

			*size = *min_size;
		}
	};


	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Slider , ztGuiItemFlags_WantsInput | ztGuiItemFlags_WantsFocus, &item_id);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->slider.live_value = live_value;
	if (item->slider.live_value) {
		item->functions.update = local::update;
	}

	item->slider.value = live_value ? zt_clamp(*live_value, 0, 1) : 0;
	item->slider.orient = orient;

	item->functions.input_mouse = local::inputMouse;
	item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	if (scrollbar) {
		item->type = ztGuiItemType_Scrollbar;
		item->slider.step = .1f;
		item->slider.step_page = .25f;
		item->slider.handle_pct = .5f;
		item->slider.press_button = 0;
		item->slider.press_time = 0;
	}

	ztVec2 min_size;
	local::best_size(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeSlider(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value)
{
	return _zt_guiMakeSliderBase(parent, orient, live_value, false);
}

// ------------------------------------------------------------------------------------------------

r32 zt_guiSliderGetValue(ztGuiItemID slider)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, slider, ztGuiItemType_Slider, 0);

	return item->slider.value;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSliderSetValue(ztGuiItemID slider, r32 value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, slider, ztGuiItemType_Slider);

	item->slider.value = value;
	if (item->slider.live_value) {
		*item->slider.live_value = value;
	}
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeScrollbar(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value)
{
	return _zt_guiMakeSliderBase(parent, orient, live_value, true);
}

// ------------------------------------------------------------------------------------------------

r32 zt_guiScrollbarGetValue(ztGuiItemID scrollbar)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, scrollbar, ztGuiItemType_Scrollbar, 0);

	return item->slider.value;
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollbarSetValue(ztGuiItemID scrollbar, r32 value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, scrollbar, ztGuiItemType_Scrollbar);

	item->slider.value = value;
	if (item->slider.live_value) {
		*item->slider.live_value = value;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollbarSetSteps(ztGuiItemID scrollbar, r32 step_single, r32 step_page)
{
	_zt_guiItemTypeFromIDReturnOnError(item, scrollbar, ztGuiItemType_Scrollbar);

	item->slider.step = zt_abs(step_single);
	item->slider.step_page = zt_abs(step_page);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepNeg(ztGuiItemID scrollbar)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, scrollbar, ztGuiItemType_Scrollbar, false);

	if (item->slider.value == 0) {
		return false;
	}

	item->slider.value = zt_max(0, item->slider.value - item->slider.step);
	if (item->slider.live_value) {
		*item->slider.live_value = item->slider.value;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepPageNeg(ztGuiItemID scrollbar)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, scrollbar, ztGuiItemType_Scrollbar, false);

	if (item->slider.value == 0) {
		return false;
	}

	item->slider.value = zt_max(0, item->slider.value - item->slider.step_page);
	if (item->slider.live_value) {
		*item->slider.live_value = item->slider.value;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepPos(ztGuiItemID scrollbar)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, scrollbar, ztGuiItemType_Scrollbar, false);

	if (item->slider.value == 1) {
		return false;
	}

	item->slider.value = zt_min(1, item->slider.value + item->slider.step);
	if (item->slider.live_value) {
		*item->slider.live_value = item->slider.value;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepPagePos(ztGuiItemID scrollbar)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, scrollbar, ztGuiItemType_Scrollbar, false);

	if (item->slider.value == 1) {
		return false;
	}

	item->slider.value = zt_min(1, item->slider.value + item->slider.step_page);
	if (item->slider.live_value) {
		*item->slider.live_value = item->slider.value;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollbarSetPercent(ztGuiItemID scrollbar, r32 percent)
{
	_zt_guiItemTypeFromIDReturnOnError(item, scrollbar, ztGuiItemType_Scrollbar);

	item->slider.handle_pct = percent;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiScrollContainerCalcViewportSizePos(ztGuiManager *gm, ztGuiItem *item, ztVec2 *pposition, ztVec2 *psize)
{
	ztVec2 size = *psize;
	ztVec2 position = *pposition;

	if (item->scrolled_container.contained_item == ztInvalidID) {
		return;
	}

	bool horz_vis = false;
	if (size.x < gm->item_cache[item->scrolled_container.contained_item].size.x) {
		gm->item_cache[item->scrolled_container.scrollbar_horz].flags |= ztGuiItemFlags_Visible;
		horz_vis = true;
	}
	else {
		zt_bitRemove(gm->item_cache[item->scrolled_container.scrollbar_horz].flags, ztGuiItemFlags_Visible);
	}

	bool vert_vis = false;
	if (size.x < gm->item_cache[item->scrolled_container.contained_item].size.x) {
		gm->item_cache[item->scrolled_container.scrollbar_vert].flags |= ztGuiItemFlags_Visible;
		vert_vis = true;
	}
	else {
		zt_bitRemove(gm->item_cache[item->scrolled_container.scrollbar_vert].flags, ztGuiItemFlags_Visible);
	}

	zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_horz, item->scrolled_container.scroll_amt_horz);
	zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_vert, item->scrolled_container.scroll_amt_vert);

	if (horz_vis) {
		zt_guiScrollbarSetPercent(item->scrolled_container.scrollbar_horz, item->size.x / gm->item_cache[item->scrolled_container.contained_item].size.x);

		r32 x_off = vert_vis ? gm->item_cache[item->scrolled_container.scrollbar_vert].size.x : 0;
		gm->item_cache[item->scrolled_container.scrollbar_horz].size.x = item->size.x - x_off;
		gm->item_cache[item->scrolled_container.scrollbar_horz].pos.x = x_off / -2;
		gm->item_cache[item->scrolled_container.scrollbar_horz].pos.y = -(item->size.y - gm->item_cache[item->scrolled_container.scrollbar_horz].size.y) / 2;
		size.y -= gm->item_cache[item->scrolled_container.scrollbar_horz].size.y;
		position.y += gm->item_cache[item->scrolled_container.scrollbar_horz].size.y / 2;
	}

	if (vert_vis) {
		zt_guiScrollbarSetPercent(item->scrolled_container.scrollbar_vert, item->size.y / gm->item_cache[item->scrolled_container.contained_item].size.y);

		r32 y_off = horz_vis ? gm->item_cache[item->scrolled_container.scrollbar_horz].size.y : 0;
		gm->item_cache[item->scrolled_container.scrollbar_vert].size.y = item->size.y - y_off;
		gm->item_cache[item->scrolled_container.scrollbar_vert].pos.y = y_off / 2;
		gm->item_cache[item->scrolled_container.scrollbar_vert].pos.x = (item->size.x - gm->item_cache[item->scrolled_container.scrollbar_vert].size.x) / 2;
		size.x -= gm->item_cache[item->scrolled_container.scrollbar_vert].size.x;
		position.x -= gm->item_cache[item->scrolled_container.scrollbar_vert].size.x / 2;
	}

	*pposition = position;
	*psize = size;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeScrollContainer(ztGuiItemID parent)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (item->scrolled_container.contained_item == ztInvalidID) {
				return;
			}

			ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

			ztVec2 size = item->size;
			ztVec2 pos = item->pos;
			ztVec2 orig_pos = pos;
			_zt_guiScrollContainerCalcViewportSizePos(gm, item, &pos, &size);
			item->scrolled_container.viewport_pos[0] = pos.x - orig_pos.x;
			item->scrolled_container.viewport_pos[1] = pos.y - orig_pos.y;
			item->scrolled_container.viewport_size[0] = size.x;
			item->scrolled_container.viewport_size[1] = size.y;

			zt_guiItemSetSize(item->scrolled_container.viewport, size);
			zt_guiItemSetPosition(item->scrolled_container.viewport, ztVec2(item->scrolled_container.viewport_pos[0], item->scrolled_container.viewport_pos[1]));

			ztGuiItem *contained = &gm->item_cache[item->scrolled_container.contained_item];

			contained->pos.x = (((size.x - contained->size.x) / -2.f) + theme->scroll_container_padding_x) - (item->scrolled_container.scroll_amt_horz * ((contained->size.x - size.x) + theme->scroll_container_padding_x * 2));
			contained->pos.y = (((size.y - contained->size.y) /  2.f) - theme->scroll_container_padding_y) + (item->scrolled_container.scroll_amt_vert * ((contained->size.y - size.y) + theme->scroll_container_padding_y * 2));

			pos = zt_guiItemPositionScreenToLocal(item->scrolled_container.contained_item, pos);
			gm->item_cache[item->scrolled_container.contained_item].flags |= ztGuiItemFlags_ClipChildren;
			gm->item_cache[item->scrolled_container.contained_item].clip_area = ztVec4(pos.x + item->pos.x, pos.y - item->pos.y, size.x - theme->scroll_container_padding_x * 2, size.y - theme->scroll_container_padding_y * 2);
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (input_mouse->wheel_delta > 0) {
				zt_guiScrollbarStepNeg(item->scrolled_container.scrollbar_vert);
			}
			else if (input_mouse->wheel_delta < 0) {
				zt_guiScrollbarStepPos(item->scrolled_container.scrollbar_vert);
			}

			return false;
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_KEY(inputKey)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (input_keys[ztInputKeys_Up].justPressed()) {
				zt_guiScrollbarStepNeg(item->scrolled_container.scrollbar_vert);
			}
			if (input_keys[ztInputKeys_Down].justPressed()) {
				zt_guiScrollbarStepPos(item->scrolled_container.scrollbar_vert);
			}
			if (input_keys[ztInputKeys_Home].justPressed()) {
				zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_vert, 0);
				zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_horz, 0);
			}
			if (input_keys[ztInputKeys_End].justPressed()) {
				zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_vert, 1);
				zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_horz, 1);
			}

			return false;
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
		}

		// ------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			if (item->scrolled_container.contained_item != ztInvalidID) {
				*min_size = gm->item_cache[item->scrolled_container.contained_item].size;
			}

			*size = *min_size;
		}
	};


	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_ScrollContainer, ztGuiItemFlags_ClipChildren, &item_id);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->scrolled_container.scrollbar_horz = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Horz, &item->scrolled_container.scroll_amt_horz);
	item->scrolled_container.scrollbar_vert = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Vert, &item->scrolled_container.scroll_amt_vert);
	item->scrolled_container.viewport = zt_guiMakePanel(item_id, ztGuiItemFlags_Visible | ztGuiItemFlags_ClipChildren);
	item->scrolled_container.contained_item = ztInvalidID;
	item->scrolled_container.scroll_amt_vert = 0;
	item->scrolled_container.scroll_amt_horz = 0;
	item->scrolled_container.viewport_pos[0] = 0;
	item->scrolled_container.viewport_pos[1] = 0;
	item->scrolled_container.viewport_size[0] = 0;
	item->scrolled_container.viewport_size[1] = 0;

	//zt_debugOnly(item->debug_highlight = ztVec4(1, 0, 0, 1));
	//zt_debugOnly(gm->item_cache[item->scrolled_container.viewport].debug_highlight = ztVec4(0, 1, 0, 1));


	item->functions.input_mouse = local::inputMouse;
	item->functions.input_key = local::inputKey;
	item->functions.update = local::update;
	//item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	ztVec2 min_size;
	local::best_size(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerSetItem(ztGuiItemID scroll, ztGuiItemID internal_item)
{
	_zt_guiItemTypeFromIDReturnOnError(item, scroll, ztGuiItemType_ScrollContainer);

	zt_guiItemReparent(internal_item, item->scrolled_container.viewport);

	item->scrolled_container.contained_item = internal_item;
	item->functions.update(scroll, 0, item->functions.user_data);

	_zt_guiManagerGetFromItem(gm, scroll);
	//zt_debugOnly(gm->item_cache[item->scrolled_container.contained_item].debug_highlight = ztVec4(0, 0, 1, 1));
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerResetScroll(ztGuiItemID scroll)
{
	_zt_guiItemTypeFromIDReturnOnError(item, scroll, ztGuiItemType_ScrollContainer);

	item->scrolled_container.scroll_amt_horz = 0;
	item->scrolled_container.scroll_amt_vert = 0;
	item->functions.update(scroll, 0, item->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztVec2 _zt_guiTextEditGetCharacterPos(ztGuiItem *item, int ch, ztGuiTheme *theme, bool bottom_right)
{
	ztVec2 chpos = ztVec2::zero;

	int prev_pos = 0;
	int pos = zt_strFindPos(item->textedit.text_buffer, "\n", 0);
	while (pos != ztStrPosNotFound && pos < ch) {
		pos += 1;
		ztVec2 ext = zt_fontGetExtents(theme->font, zt_strMoveForward(item->textedit.text_buffer, prev_pos), pos - prev_pos);
		chpos.y -= ext.y;

		prev_pos = pos;
		pos = zt_strFindPos(item->textedit.text_buffer, "\n", pos + 1);
	}
	if (item->textedit.text_buffer[prev_pos] == '\n') {
		prev_pos += 1;
	}

	ztVec2 ext = zt_fontGetExtents(theme->font, zt_strMoveForward(item->textedit.text_buffer, prev_pos), ch - prev_pos);
	chpos.x += ext.x;

	if (bottom_right) {
		chpos.y -= ext.y;
	}

	return chpos;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztVec2 _zt_guiTextEditGetTextStartPos(ztGuiItem *item, ztGuiTheme *theme, ztGuiManager *gm)
{
	ztVec2 pos = zt_guiItemPositionLocalToScreen(item->id, ztVec2::zero);

	r32 diff_x = zt_max(0, item->textedit.content_size[0] - (item->size.x - theme->textedit_padding_x * 2.f));
	r32 diff_y = zt_max(0, item->textedit.content_size[1] - (item->size.y - theme->textedit_padding_y * 2.f));

	if (zt_bitIsSet(gm->item_cache[item->textedit.scrollbar_vert].flags, ztGuiItemFlags_Visible)) {
		diff_x += gm->item_cache[item->textedit.scrollbar_vert].size.x;
	}
	if (zt_bitIsSet(gm->item_cache[item->textedit.scrollbar_horz].flags, ztGuiItemFlags_Visible)) {
		diff_y += gm->item_cache[item->textedit.scrollbar_horz].size.y;
	}

	return ztVec2(pos.x - item->size.x / 2.f + theme->textedit_padding_x - (diff_x * item->textedit.scroll_amt_horz),
		pos.y + item->size.y / 2.f - theme->textedit_padding_y + (diff_y * item->textedit.scroll_amt_vert));
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditAdjustViewForCursor(ztGuiItem *item)
{
	_zt_guiManagerGetFromItem(gm, item->id);
	ztGuiTheme *theme = zt_guiItemGetTheme(item->id);

	ztVec2 cursor_pos_beg = _zt_guiTextEditGetCharacterPos(item, item->textedit.cursor_pos, zt_guiItemGetTheme(item->id), false);
	ztVec2 cursor_pos_end = _zt_guiTextEditGetCharacterPos(item, item->textedit.cursor_pos, zt_guiItemGetTheme(item->id), true);

	ztVec2 text_pos = zt_guiItemPositionScreenToLocal(item->id, _zt_guiTextEditGetTextStartPos(item, theme, gm));
	cursor_pos_beg += text_pos;
	cursor_pos_end += text_pos;

	r32 x_diff = zt_max(0, item->textedit.content_size[0] - (item->size.x - theme->textedit_padding_x * 2.f));
	r32 y_diff = zt_max(0, item->textedit.content_size[1] - (item->size.y - theme->textedit_padding_y * 2.f));

	if (zt_bitIsSet(gm->item_cache[item->textedit.scrollbar_vert].flags, ztGuiItemFlags_Visible)) {
		x_diff += gm->item_cache[item->textedit.scrollbar_vert].size.x;
	}
	if (zt_bitIsSet(gm->item_cache[item->textedit.scrollbar_horz].flags, ztGuiItemFlags_Visible)) {
		y_diff += gm->item_cache[item->textedit.scrollbar_horz].size.y;
	}

	if (cursor_pos_beg.x < item->clip_area.x - item->clip_area.z / 2.f) {
		r32 diff = item->clip_area.x - cursor_pos_beg.x;
		item->textedit.scroll_amt_horz = zt_max(0, item->textedit.scroll_amt_horz - (diff / x_diff));
	}
	if (cursor_pos_end.x > item->clip_area.x + item->clip_area.z / 2.f) {
		r32 diff = cursor_pos_end.x - (item->clip_area.x + item->clip_area.z / 2.f);
		item->textedit.scroll_amt_horz = zt_min(1, (diff / x_diff) + item->textedit.scroll_amt_horz);
	}

	if (cursor_pos_beg.y > item->clip_area.y + item->clip_area.w / 2.f) {
		r32 diff = cursor_pos_beg.y - (item->clip_area.y + item->clip_area.w / 2.f);
		item->textedit.scroll_amt_vert = zt_max(0, item->textedit.scroll_amt_vert - (diff / y_diff));
	}
	if (cursor_pos_end.y < item->clip_area.y - item->clip_area.w / 2.f) {
		r32 diff = (item->clip_area.y - item->clip_area.w / 2.f) - cursor_pos_end.y;
		item->textedit.scroll_amt_vert = zt_min(1, (diff / y_diff) + item->textedit.scroll_amt_vert);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditCacheText(ztGuiItem *item)
{
	zt_drawListReset(item->draw_list);

	ztGuiTheme *theme = zt_guiItemGetTheme(item->id);
	zt_drawListAddText2D(item->draw_list, theme->font, item->textedit.text_buffer, ztVec2::zero, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeTextEdit(ztGuiItemID parent, const char *value, i32 flags, i32 buffer_size)
{
	static const char *word_separators = " \t";
	static const int word_separators_len = zt_strLen(word_separators);

	struct local
	{
		// ------------------------------------------------------------------------------------------------

		static void getCurrentLineInfo(ztGuiItem *item, int *beg_pos, int *end_pos, int from_pos = -1)
		{
			ztGuiTheme *theme = zt_guiItemGetTheme(item->id);

			if (from_pos == -1) from_pos = item->textedit.cursor_pos;

			if (item->textedit.text_buffer[from_pos] == '\n' && (from_pos == 0 || item->textedit.text_buffer[from_pos - 1] == '\n')) {
				*beg_pos = from_pos;
			}
			else {
				*beg_pos = zt_strFindLastPos(item->textedit.text_buffer, "\n", zt_max(0, from_pos - 1));
				if (*beg_pos == ztStrPosNotFound) {
					*beg_pos = 0;
				}
				else {
					*beg_pos += 1;
				}
			}

			if (end_pos) {
				const char *find_end = zt_strMoveForward(item->textedit.text_buffer, *beg_pos);
				*end_pos = zt_strFindPos(find_end, "\n", 0);
				if (*end_pos == ztStrPosNotFound) {
					*end_pos = zt_strLen(find_end) + *beg_pos;
				}
				else {
					*end_pos += *beg_pos;
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static int posNextWord(ztGuiItem *item, int str_len)
		{
			int pos = item->textedit.cursor_pos;
			bool break_next_char = item->textedit.text_buffer[pos] == '\n';
			while (++pos < str_len) {
				if (item->textedit.text_buffer[pos] == '\n') break;

				bool is_separator = false;
				zt_fjz(word_separators_len) {
					if (is_separator = item->textedit.text_buffer[pos] == word_separators[j]) {
						break;
					}
				}
				if (is_separator) {
					break_next_char = true;
				}
				else if (break_next_char) break;
			}

			return pos;
		}

		// ------------------------------------------------------------------------------------------------

		static int posPrevWord(ztGuiItem *item, int str_len)
		{
			int pos = item->textedit.cursor_pos;
			while (--pos > 0) {
				if (item->textedit.text_buffer[pos - 1] == '\n') break;

				bool need_break = false;
				zt_fjz(word_separators_len) {
					if (need_break = item->textedit.text_buffer[pos - 1] == word_separators[j]) {
						break;
					}
				}
				if (need_break) break;
			}

			return pos;
		}

		// ------------------------------------------------------------------------------------------------

		static int posAboveChar(ztGuiItem *item)
		{
			int beg_line = 0;
			getCurrentLineInfo(item, &beg_line, nullptr);
			if (beg_line != 0) {
				int line_prev = zt_strFindLastPos(item->textedit.text_buffer, "\n", beg_line - 2);
				if (line_prev == ztStrPosNotFound) {
					line_prev = 0;
				}
				else line_prev += 1;

				int chars_in = item->textedit.cursor_pos - beg_line;
				return zt_min(line_prev + chars_in, line_prev + (beg_line - line_prev) - 1);
			}
			return item->textedit.cursor_pos;
		}

		// ------------------------------------------------------------------------------------------------

		static int posBelowChar(ztGuiItem *item, int str_len)
		{
			int beg_line = 0, end_line = 0;
			getCurrentLineInfo(item, &beg_line, &end_line);
			if (end_line < str_len) {
				int chars_in = item->textedit.cursor_pos - beg_line;

				item->textedit.cursor_pos = zt_min(end_line + 1, str_len);

				int nbeg_line = 0, nend_line = 0;
				getCurrentLineInfo(item, &nbeg_line, &nend_line);

				return zt_min(nbeg_line + chars_in, nend_line);
			}

			return item->textedit.cursor_pos;
		}

		// ------------------------------------------------------------------------------------------------

		static void selectBeg(ztGuiItem *item, bool force = false)
		{
			if (force || item->textedit.select_beg == -1) {
				item->textedit.select_beg = item->textedit.select_end = item->textedit.cursor_pos;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void selectEnd(ztGuiItem *item)
		{
			item->textedit.select_end = item->textedit.cursor_pos;
		}

		// ------------------------------------------------------------------------------------------------

		static void recalcCursor(ztGuiItem *item)
		{
			ztGuiTheme *theme = zt_guiItemGetTheme(item->id);
			int beg_line = 0;
			getCurrentLineInfo(item, &beg_line, nullptr);
			if (beg_line != ztStrPosNotFound) {
				ztVec2 ext = zt_fontGetExtents(theme->font, item->textedit.text_buffer, beg_line);

				item->textedit.cursor_xy[1] = -ext.y;
			}
			else {
				beg_line = 0;
				item->textedit.cursor_xy[1] = 0;
			}

			const char *text = zt_strMoveForward(item->textedit.text_buffer, beg_line);
			item->textedit.cursor_xy[0] = zt_fontGetExtents(theme->font, text, item->textedit.cursor_pos - beg_line).x;
		}

		// ------------------------------------------------------------------------------------------------
		static ZT_FUNC_GUI_ITEM_INPUT_KEY(inputKey)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			bool recalc_cursor = false;

			int str_len = zt_strLen(item->textedit.text_buffer);

			bool shifting = input_keys[ztInputKeys_Shift].pressed();
			if (shifting) {
				selectBeg(item);
			}

			if (input_keys[ztInputKeys_Right].justPressedOrRepeated()) {
				recalc_cursor = true;
				if (item->textedit.cursor_pos < str_len) {
					if (input_keys[ztInputKeys_Control].pressed()) {
						item->textedit.cursor_pos = posNextWord(item, str_len);
					}
					else {
						item->textedit.cursor_pos += 1;
					}
				}
			}
			if (input_keys[ztInputKeys_Left].justPressedOrRepeated()) {
				recalc_cursor = true;
				if (item->textedit.cursor_pos > 0) {
					if (input_keys[ztInputKeys_Control].pressed()) {
						item->textedit.cursor_pos = posPrevWord(item, str_len);
					}
					else {
						item->textedit.cursor_pos -= 1;
					}
				}
			}
			if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
				recalc_cursor = true;
				item->textedit.cursor_pos = posAboveChar(item);
			}
			if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
				recalc_cursor = true;
				item->textedit.cursor_pos = posBelowChar(item, str_len);
			}
			if (input_keys[ztInputKeys_Home].justPressedOrRepeated()) {
				recalc_cursor = true;
				if (input_keys[ztInputKeys_Control].pressed()) {
					item->textedit.cursor_pos = 0;
				}
				else {
					int beg_line = 0;
					getCurrentLineInfo(item, &beg_line, nullptr);
					item->textedit.cursor_pos = beg_line;
				}
			}
			if (input_keys[ztInputKeys_End].justPressedOrRepeated()) {
				recalc_cursor = true;
				if (input_keys[ztInputKeys_Control].pressed()) {
					item->textedit.cursor_pos = str_len + 1;
				}
				else {
					int beg_line = 0, end_line = 0;
					getCurrentLineInfo(item, &beg_line, &end_line);
					item->textedit.cursor_pos = end_line;
				}
			}
			if (input_keys[ztInputKeys_Delete].justPressedOrRepeated()) {
				recalc_cursor = true;
				if (item->textedit.select_beg != item->textedit.select_end) {
					int offset = zt_max(item->textedit.select_beg, item->textedit.select_end) - zt_min(item->textedit.select_beg, item->textedit.select_end);
					for (int i = zt_min(item->textedit.select_beg, item->textedit.select_end); i <= str_len; ++i) {
						item->textedit.text_buffer[i] = item->textedit.text_buffer[i + offset];
					}
					item->textedit.cursor_pos = zt_min(item->textedit.select_beg, item->textedit.select_end);
					item->textedit.select_beg = item->textedit.select_end = -1;
				}
				else {
					int iterations = 1;
					if (input_keys[ztInputKeys_Control].pressed()) {
						int next_word = posNextWord(item, str_len);
						iterations = next_word - item->textedit.cursor_pos;
					}

					zt_fjz(iterations) {
						for (int i = item->textedit.cursor_pos; i <= str_len; ++i) {
							item->textedit.text_buffer[i] = item->textedit.text_buffer[i + 1];
						}
					}
				}
				_zt_guiTextEditCacheText(item);
			}
			if (input_keys[ztInputKeys_Back].justPressedOrRepeated()) {
				recalc_cursor = true;
				if (item->textedit.select_beg != item->textedit.select_end) {
					int offset = zt_max(item->textedit.select_beg, item->textedit.select_end) - zt_min(item->textedit.select_beg, item->textedit.select_end);
					for (int i = zt_min(item->textedit.select_beg, item->textedit.select_end); i <= str_len; ++i) {
						item->textedit.text_buffer[i] = item->textedit.text_buffer[i + offset];
					}
					item->textedit.cursor_pos = zt_min(item->textedit.select_beg, item->textedit.select_end);
					item->textedit.select_beg = item->textedit.select_end = -1;
				}
				else {
					int iterations = 1;
					if (input_keys[ztInputKeys_Control].pressed()) {
						int prev_word = posPrevWord(item, str_len);
						iterations = item->textedit.cursor_pos - prev_word;
					}

					zt_fjz(iterations) {
						if (item->textedit.cursor_pos > 0) {
							for (int i = item->textedit.cursor_pos - 1; i <= str_len; ++i) {
								item->textedit.text_buffer[i] = item->textedit.text_buffer[i + 1];
							}
							item->textedit.cursor_pos -= 1;
						}
					}
				}
				_zt_guiTextEditCacheText(item);
			}

			if (shifting) {
				selectEnd(item);
			}

			int keys = 0;
			zt_fiz(input_key_strokes) {
				if (input_key_strokes[i] == ztInputKeys_Invalid) break;

				if (input_keys[input_key_strokes[i]].display != 0) {
					if (str_len >= zt_stringSize(item->textedit.text_buffer)) {
						zt_logInfo("GUI text edit control has reached its max size");
						break;
					}

					if (input_key_strokes[i] == ztInputKeys_Return && !zt_bitIsSet(item->flags, ztGuiTextEditFlags_MultiLine)) {
						continue;
					}

					for (int j = str_len; j >= item->textedit.cursor_pos; --j) {
						item->textedit.text_buffer[j + 1] = item->textedit.text_buffer[j];
					}
					item->textedit.text_buffer[item->textedit.cursor_pos++] = input_keys[input_key_strokes[i]].display;
					recalc_cursor = true;
					keys += 1;
				}
			}

			if (recalc_cursor) {
				if (!shifting) {
					item->textedit.select_beg = -1;
					item->textedit.select_end = -1;
				}
				item->textedit.cursor_vis = true;

				recalcCursor(item);
				_zt_guiTextEditAdjustViewForCursor(item);
				item->textedit.content_size[0] = 0;
				item->textedit.content_size[1] = 0;
			}

			if (keys > 0) {
				_zt_guiTextEditCacheText(item);
			}

			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static int getCursorIndexAtPosition(ztGuiItem *item, ztVec2 pos)
		{
			ztGuiTheme *theme = zt_guiItemGetTheme(item->id);
			_zt_guiManagerGetFromItem(gm, item->id);

			ztVec2 chpos = _zt_guiTextEditGetTextStartPos(item, theme, gm);

			int prev_idx = 0;
			int idx = zt_strFindPos(item->textedit.text_buffer, "\n", 0);
			while (idx != ztStrPosNotFound) {
				idx += 1;

				ztVec2 ext = zt_fontGetExtents(theme->font, zt_strMoveForward(item->textedit.text_buffer, prev_idx), idx - prev_idx);

				if ((pos.y < chpos.y && pos.y >= chpos.y - ext.y) || pos.y > chpos.y) {
					break;
				}

				chpos.y -= ext.y;

				prev_idx = idx;
				idx = zt_strFindPos(item->textedit.text_buffer, "\n", idx + 1);
			}

			if (idx == ztStrPosNotFound) {
				idx = zt_strLen(item->textedit.text_buffer);
			}
			idx = zt_max(0, idx - 1);

			int beg_pos = 0, end_pos = 0;
			getCurrentLineInfo(item, &beg_pos, &end_pos, idx);

			int line_len = end_pos - beg_pos;
			const char *line = zt_strMoveForward(item->textedit.text_buffer, beg_pos);
			ztVec2 ext_prev = ztVec2::zero;
			zt_fiz(line_len) {
				ztVec2 ext = zt_fontGetExtents(theme->font, line, i);
				if (pos.x < chpos.x +  ext.x) {
					r32 half = (ext.x - ext_prev.x) / 2.f;
					if (i != 0 && pos.x < chpos.x + (ext.x - half)) {
						return beg_pos + (i - 1);
					}
					else {
						return beg_pos + i;
					}
				}
				ext_prev = ext;
			}

			return end_pos;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (input_mouse->leftJustPressed()) {
				ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
				item->textedit.cursor_pos = getCursorIndexAtPosition(item, mpos);
				recalcCursor(item);

				item->textedit.dragging = true;
				selectBeg(item, true);
			}
			else if (input_mouse->leftJustReleased()) {
				item->textedit.dragging = false;
				selectEnd(item);
			}
			else if (item->textedit.dragging) {
				ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
				item->textedit.cursor_pos = item->textedit.select_end = getCursorIndexAtPosition(item, mpos);
				recalcCursor(item);
				_zt_guiTextEditAdjustViewForCursor(item);
			}

			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			item->textedit.cursor_blink_time -= dt;
			if (item->textedit.cursor_blink_time < 0) {
				item->textedit.cursor_blink_time += .5f;
				item->textedit.cursor_vis = !item->textedit.cursor_vis;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;

			zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_textedit, pos, item->size);

			if (item->textedit.content_size[0] == 0 && item->textedit.content_size[1] == 0) {
				ztVec2 size = zt_fontGetExtents(theme->font, item->textedit.text_buffer);

				if (zt_strEndsWith(item->textedit.text_buffer, "\n")) {
					ztVec2 extra = zt_fontGetExtents(theme->font, " ");
					size.y += extra.y;
				}

				item->textedit.content_size[0] = size.x;
				item->textedit.content_size[1] = size.y;

				_zt_guiItemFromID(scroll_horz, item->textedit.scrollbar_horz);
				_zt_guiItemFromID(scroll_vert, item->textedit.scrollbar_vert);

				bool vert = item->textedit.content_size[1] > item->size.y;
				bool horz = item->textedit.content_size[0] > item->size.x - (vert ? scroll_vert->size.x : 0);

				item->clip_area.xy = ztVec2::zero;
				item->clip_area.zw = item->size;

				if (horz) {
					if (zt_bitIsSet(item->flags, ztGuiTextEditFlags_MultiLine)) {
						scroll_horz->flags |= ztGuiItemFlags_Visible;
						scroll_horz->pos.y = (item->size.y - scroll_horz->size.y) / -2.f;
						scroll_horz->pos.x = (vert ? -scroll_vert->size.x / 2.f : 0);
						scroll_horz->size.x = item->size.x - (vert ? scroll_vert->size.x : 0);
						item->clip_area.y += scroll_horz->size.y / 2.f;
						item->clip_area.w -= scroll_horz->size.y;
					}
				}
				else if (scroll_horz) {
					zt_bitRemove(scroll_horz->flags, ztGuiItemFlags_Visible);
				}

				if (vert) {
					scroll_vert->flags |= ztGuiItemFlags_Visible;
					scroll_vert->pos.x = (item->size.x - scroll_vert->size.x) / 2.f;
					scroll_vert->pos.y = (horz ? scroll_horz->size.y / 2.f : 0);
					scroll_vert->size.y = item->size.y - (horz ? scroll_horz->size.y : 0);
					item->clip_area.x -= scroll_vert->size.x / 2.f;
					item->clip_area.z -= scroll_vert->size.x;

					int lines_count = zt_strCount(item->textedit.text_buffer, "\n");
					r32 line_height = item->textedit.content_size[1] / lines_count;
					int lines_shown = zt_convertToi32Floor(((item->size.y - theme->textedit_padding_y * 2.f) - (horz ? scroll_horz->size.y : 0)) / line_height);
					r32 pct_per_line = line_height / ((lines_count - lines_shown) * line_height);

					zt_guiScrollbarSetSteps(item->textedit.scrollbar_vert, pct_per_line, lines_shown * pct_per_line);
				}
				else if (scroll_vert) {
					zt_bitRemove(scroll_vert->flags, ztGuiItemFlags_Visible);
				}
			}

			ztVec2 text_pos = _zt_guiTextEditGetTextStartPos(item, theme, gm);

			if (item->textedit.select_beg != item->textedit.select_end) {
				int sel_beg = zt_min(item->textedit.select_beg, item->textedit.select_end);
				int sel_end = zt_max(item->textedit.select_beg, item->textedit.select_end);

				while (sel_beg < sel_end) {
					ztVec2 pos_beg = _zt_guiTextEditGetCharacterPos(item, sel_beg, theme, false);

					int idx_end_line = zt_strFindPos(item->textedit.text_buffer, "\n", sel_beg);
					if (idx_end_line == ztStrPosNotFound || idx_end_line > sel_end) {
						idx_end_line = sel_end;
					}

					ztVec2 pos_end = _zt_guiTextEditGetCharacterPos(item, idx_end_line, theme, true);

					ztVec2 pos_size = ztVec2(pos_end.x - pos_beg.x, pos_beg.y - pos_end.y);
					ztVec2 pos_center = ztVec2(pos_beg.x + pos_size.x / 2.f, pos_beg.y - pos_size.y / 2.f);

					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_textedit_select, text_pos + pos_center, pos_size);

					sel_beg = idx_end_line + 1;
				}
			}

			zt_drawListAddDrawList(draw_list, item->draw_list, ztVec3(text_pos, 0));
			//ztVec2 text_size = zt_fontGetExtents(theme->font, item->textedit.text_buffer);
			//zt_drawListAddText2D(draw_list, theme->font, item->textedit.text_buffer, text_pos, ztAlign_Left|ztAlign_Top, ztAnchor_Left|ztAnchor_Top);

			if (gm->focus_item == item_id) {
				if (item->textedit.cursor_vis) {
					ztVec2 cursor_pos = text_pos + ztVec2(item->textedit.cursor_xy[0], item->textedit.cursor_xy[1]);
					ztVec2 cursor_size = zt_fontGetExtents(theme->font, "|");
					cursor_pos.x -= cursor_size.x / 2;
					zt_drawListAddText2D(draw_list, theme->font, "|", cursor_pos, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			zt_stringFree(item->textedit.text_buffer, gm->arena);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
		}
	};


	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_TextEdit, ztGuiItemFlags_ClipContents | ztGuiItemFlags_WantsFocus | flags, &item_id, buffer_size * 2);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	zt_guiItemSetSize(item_id, ztVec2(theme->textedit_default_w, theme->textedit_default_h));

	item->textedit.cursor_pos = 0;
	item->textedit.cursor_xy[0] = item->textedit.cursor_xy[1] = 0;
	item->textedit.cursor_vis = false;
	item->textedit.text_buffer = zt_stringMake(buffer_size, gm->arena);
	item->textedit.text_buffer[0] = 0;
	item->textedit.select_beg = -1;
	item->textedit.select_end = -1;
	item->textedit.dragging = false;
	item->textedit.scroll_amt_horz = 0;
	item->textedit.scroll_amt_vert = 0;
	item->textedit.content_size[0] = 0;
	item->textedit.content_size[1] = 0;

	if (zt_bitIsSet(flags, ztGuiTextEditFlags_MultiLine)) {
		if (zt_bitIsSet(flags, ztGuiTextEditFlags_WordWrap)) {
			item->textedit.scrollbar_horz = ztInvalidID;
		}
		else {
			item->textedit.scrollbar_horz = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Horz, &item->textedit.scroll_amt_horz);
			zt_bitRemove(gm->item_cache[item->textedit.scrollbar_horz].flags, ztGuiItemFlags_Visible);
		}

		item->textedit.scrollbar_vert = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Vert, &item->textedit.scroll_amt_vert);
		zt_bitRemove(gm->item_cache[item->textedit.scrollbar_vert].flags, ztGuiItemFlags_Visible);
	}
	else {
		item->textedit.scrollbar_vert = ztInvalidID;
		item->textedit.scrollbar_horz = ztInvalidID;
	}

	if (value) {
		zt_stringOverwrite(item->textedit.text_buffer, value, gm->arena);
		_zt_guiTextEditCacheText(item);
	}

	item->functions.cleanup = local::cleanup;
	item->functions.update = local::update;
	item->functions.input_mouse = local::inputMouse;
	item->functions.input_key = local::inputKey;
	item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	ztVec2 min_size;
	local::best_size(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

int zt_guiTextEditGetValue(ztGuiItemID text, char *buffer, int buffer_len)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, text, ztGuiItemType_TextEdit, -1);
	return zt_strCpy(buffer, buffer_len, item->textedit.text_buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetValue(ztGuiItemID text, const char *value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, text, ztGuiItemType_TextEdit);
	zt_strCpy(item->textedit.text_buffer, zt_stringSize(item->textedit.text_buffer), value);

	item->textedit.cursor_pos = 0;
	_zt_guiTextEditAdjustViewForCursor(item);
}

// ------------------------------------------------------------------------------------------------

#define ztGuiMenuMaxMenuItems	32

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiMenuClose(ztGuiItem *item)
{
	zt_guiItemHide(item->id);
	item->menu.selected = item->menu.highlighted = -1;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiMenuCloseAll()
{
	zt_fiz(zt_elementsOf(zt_gui->gui_managers)) {
		if (zt_gui->gui_managers[i] == nullptr) break;

		zt_fjz(zt_elementsOf(zt_gui->gui_managers[i]->item_cache)) {
			if (zt_gui->gui_managers[i]->item_cache_flags[j] != 0) {
				if (zt_gui->gui_managers[i]->item_cache[j].type == ztGuiItemType_Menu) {
					_zt_guiMenuClose(&zt_gui->gui_managers[i]->item_cache[j]);
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItemID _zt_guiMakeMenuBase( ztGuiItemID parent )
{
	struct local
	{
		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			ztVec2 mpos = zt_guiItemPositionScreenToLocal(item_id, zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));

			ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

			ztVec2 pos = ztVec2::zero;
			pos.x -= (item->size.x - theme->menu_padding_x * 2.f) / 2.f;
			pos.y += (item->size.y - theme->menu_padding_y * 2.f) / 2.f;

			item->menu.selected = item->menu.highlighted = -1;

			zt_fiz(item->menu.item_count) {
				ztVec2 ext = zt_fontGetExtents(theme->font, item->menu.display[i]);
				
				if (mpos.y <= pos.y && mpos.y > pos.y - ext.y) {
					item->menu.highlighted = i;
					break;
				}

				pos.y -= ext.y + theme->menu_padding_y;
			}

			if (input_mouse->leftJustReleased()) {
				item->menu.selected = item->menu.highlighted;

				if (item->menu.selected != -1 && item->menu.submenus[item->menu.selected] != ztInvalidID) {
					ztVec2 ppos(item->size.x / 2.f, pos.y);
					ppos = zt_guiItemPositionLocalToScreen(item->id, ppos);

					ztVec2 cam_min, cam_max;
					zt_cameraOrthoGetExtents(gm->gui_camera, &cam_min, &cam_max);

					ztGuiItem *submenu = &gm->item_cache[item->menu.submenus[item->menu.selected]];

					if (ppos.x + submenu->size.x / 2.f > cam_max.x) {
						ppos.x -= item->size.x + submenu->size.x;
					}

					if (ppos.y - submenu->size.y < cam_min.y) {
						ppos.y += submenu->size.y;
					}

					zt_guiMenuPopupAtPosition(item->menu.submenus[item->menu.selected], ppos);
				}
				else {
					if (item->menu.on_selected) {
						item->menu.on_selected(item->id, item->menu.ids[item->menu.selected]);
					}

					_zt_guiMenuCloseAll();
				}
			}

			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (gm->mouse_click && !item->menu.just_opened && gm->item_has_mouse != item_id && !zt_guiItemIsChildOf(item_id, gm->item_has_mouse)) {
				bool close = true;
				if (gm->item_has_mouse != ztInvalidID) {
					if (gm->item_cache[gm->item_has_mouse].type == ztGuiItemType_Menu) {
						close = false;
					}
				}
				if (close) {
					_zt_guiMenuClose(item);
				}
			}

			item->menu.just_opened = false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;

			zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_menu, pos, item->size);

			pos.x -= (item->size.x - theme->menu_padding_x * 2.f) / 2.f;
			pos.y += (item->size.y - theme->menu_padding_y * 2.f) / 2.f;

			ztVec2 icon = ztVec2(theme->menu_submenu_icon_x, theme->menu_submenu_icon_y);
			zt_fiz(item->menu.item_count) {
				if (item->menu.icons[i] != nullptr) {
					icon.x = zt_max(icon.x, item->menu.icons[i]->half_size.x * 2.f + theme->menu_padding_x * 2.f);
					icon.y = zt_max(icon.y, item->menu.icons[i]->half_size.y * 2.f);
				}
			}

			zt_fiz(item->menu.item_count) {
				ztVec2 ext = zt_fontGetExtents(theme->font, item->menu.display[i]);

				if (item->menu.highlighted == i) {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_menu_highlight, ztVec2(offset.x + item->pos.x, pos.y - ext.y / 2.f), ztVec2(item->size.x - theme->menu_padding_x * 2.f, ext.y));
				}
				zt_drawListAddText2D(draw_list, theme->font, item->menu.display[i], ztVec2(pos.x + icon.x, pos.y), ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);

				if (item->menu.icons[i] != nullptr) {
					r32 y = zt_max(item->menu.icons[i]->half_size.y, ext.y / 2.f);
					zt_drawListAddSprite(draw_list, item->menu.icons[i], ztVec3(offset.x + pos.x + theme->menu_padding_x + item->menu.icons[i]->half_size.x, pos.y - y, 0));
				}

				if (item->menu.submenus[i] != ztInvalidID) {
					r32 y = zt_max(theme->menu_submenu_icon_y, ext.y) / 2.f;
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_menu_submenu, ztVec2((item->size.x + pos.x) - (theme->menu_padding_x * 2 + theme->menu_submenu_icon_x / 2.f), pos.y - y), ztVec2(theme->menu_submenu_icon_x, theme->menu_submenu_icon_y));
				}

				pos.y -= zt_max(icon.y, ext.y) + theme->menu_padding_y;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			zt_fiz(item->menu.item_count) {
				zt_stringFree(item->menu.display[i], gm->arena);
			}

			zt_freeArena(item->menu.display, gm->arena);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			*size = ztVec2::zero;

			ztVec2 icon = ztVec2(theme->menu_submenu_icon_x, theme->menu_submenu_icon_y);
			zt_fiz(item->menu.item_count) {
				if (item->menu.icons[i] != nullptr) {
					icon.x = zt_max(icon.x, item->menu.icons[i]->half_size.x * 2.f + theme->menu_padding_x * 2.f);
					icon.y = zt_max(icon.y, item->menu.icons[i]->half_size.y * 2.f);
				}
			}

			zt_fiz(item->menu.item_count) {
				ztVec2 ext = zt_fontGetExtents(theme->font, item->menu.display[i]);

				size->y += zt_max(zt_max(icon.y, ext.y), theme->menu_submenu_icon_y) + theme->menu_padding_y;
				size->x = zt_max(size->x, ext.x + icon.x + theme->menu_submenu_icon_x + theme->menu_padding_x * 3.f);
			}
			size->y += theme->menu_padding_y;
		}
	};


	ztGuiManager *gm = zt_gui->gui_managers[zt_gui->active_gui_manager];
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Menu, /*ztGuiItemFlags_ClipContents |*/ ztGuiItemFlags_WantsFocus | ztGuiItemFlags_BringToFront, &item_id);
	if (!item) return ztInvalidID;

	zt_guiItemHide(item_id);

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	int max_menu = ztGuiMenuMaxMenuItems;
	i32 size = (zt_sizeof(char *) + zt_sizeof(i32) + zt_sizeof(ztGuiItemID) + zt_sizeof(ztSprite*)) * max_menu;
	byte *mem = zt_mallocStructArrayArena(byte, size, gm->arena);

	item->menu.display = (ztString*)mem;
	mem += max_menu * zt_sizeof(ztString);
	item->menu.ids = (i32*)mem;
	mem += max_menu * zt_sizeof(i32);
	item->menu.submenus = (ztGuiItemID*)mem;
	mem += max_menu * zt_sizeof(ztGuiItemID);
	item->menu.icons = (ztSprite**)mem;

	item->menu.item_count = 0;
	item->menu.highlighted = -1;
	item->menu.just_opened = false;
	item->menu.on_selected = nullptr;

	item->functions.cleanup = local::cleanup;
	item->functions.update = local::update;
	item->functions.input_mouse = local::inputMouse;
	item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	ztVec2 min_size;
	local::best_size(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeMenu()
{
	return _zt_guiMakeMenuBase(ztInvalidID);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppend(ztGuiItemID menu, const char *label, i32 id, ztSprite *icon)
{
	_zt_guiItemTypeFromIDReturnOnError(item, menu, ztGuiItemType_Menu);
	_zt_guiManagerGetFromItem(gm, menu);

	zt_assert(item->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = item->menu.item_count++;
	item->menu.display[idx] = zt_stringMakeFrom(label, gm->arena);
	item->menu.ids[idx] = id;
	item->menu.submenus[idx] = ztInvalidID;

	if (icon) {
		item->menu.icons[idx] = zt_mallocStructArena(ztSprite, gm->arena);
		*item->menu.icons[idx] = *icon;
	}
	else {
		item->menu.icons[idx] = nullptr;
	}

	item->functions.best_size(menu, nullptr, nullptr, &item->size, zt_guiItemGetTheme(menu), item->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppendSubmenu(ztGuiItemID menu, const char *label, ztGuiItemID submenu, ztSprite *icon)
{
	_zt_guiItemTypeFromIDReturnOnError(item, menu, ztGuiItemType_Menu);
	_zt_guiManagerGetFromItem(gm, menu);

	zt_assert(item->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = item->menu.item_count++;
	item->menu.display[idx] = zt_stringMakeFrom(label, gm->arena);
	item->menu.ids[idx] = ztInvalidID;
	item->menu.submenus[idx] = submenu;

	//zt_guiItemReparent(submenu, menu);

	if (icon) {
		item->menu.icons[idx] = zt_mallocStructArena(ztSprite, gm->arena);
		*item->menu.icons[idx] = *icon;
	}
	else {
		item->menu.icons[idx] = nullptr;
	}

	item->functions.best_size(menu, nullptr, nullptr, &item->size, zt_guiItemGetTheme(menu), item->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuPopupAtItem(ztGuiItemID menu, ztGuiItemID item_id, i32 align_flags, const ztVec2& offset)
{
	_zt_guiItemFromID(item, item_id);

	ztVec2 off = offset;
	if (zt_bitIsSet(align_flags, ztAlign_Left  )) off.x -= item->size.x / 2.f;
	if (zt_bitIsSet(align_flags, ztAlign_Right )) off.x += item->size.x / 2.f; 
	if (zt_bitIsSet(align_flags, ztAlign_Top   )) off.y += item->size.y / 2.f; 
	if (zt_bitIsSet(align_flags, ztAlign_Bottom)) off.y -= item->size.y / 2.f; 


	zt_guiMenuPopupAtPosition(menu, zt_guiItemPositionLocalToScreen(item_id, off));
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuPopupAtPosition(ztGuiItemID menu, const ztVec2& pos)
{
	_zt_guiItemTypeFromIDReturnOnError(item, menu, ztGuiItemType_Menu);
	_zt_guiManagerGetFromItem(gm, menu);

	_zt_guiMenuClose(item);

	item->flags |= ztGuiItemFlags_Visible;
	item->menu.just_opened = true;

	ztVec2 position = pos;
	position.x += item->size.x / 2;
	position.y -= item->size.y / 2;

	item->pos = position;
	zt_guiItemBringToFront(menu);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiMenuGetSelected(ztGuiItemID menu, i32 *selected_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, menu, ztGuiItemType_Menu, false);

	if (item->menu.selected != -1) {
		if (item->menu.submenus[item->menu.selected] != ztInvalidID) {
			return zt_guiMenuGetSelected(item->menu.submenus[item->menu.selected], selected_id);
		}
		*selected_id = item->menu.ids[item->menu.selected];
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuSetCallback(ztGuiItemID menu, zt_guiMenuSelected_Func *on_selected)
{
	_zt_guiItemTypeFromIDReturnOnError(item, menu, ztGuiItemType_Menu);
	item->menu.on_selected = on_selected;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemFree(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	zt_returnOnNull(item);

	_zt_guiItemFree(gm, item);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetSize(ztGuiItemID item_id, const ztVec2& size)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnOnNull(item);

	if (size.x != -1) item->size.x = size.x;
	if (size.y != -1) item->size.y = size.y;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemAutoSize(ztGuiItemID item_id)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnOnNull(item);

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	if (item->functions.best_size) {
		ztVec2 min, max;
		item->functions.best_size(item_id, &min, &max, &item->size, theme, item->functions.user_data);
	}
	else {
		if (item->label != nullptr) {
			item->size = zt_fontGetExtents(theme->font, item->label);
			item->size.x += theme->padding * 2;
			item->size.y += theme->padding * 2;
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetPosition(ztGuiItemID item_id, const ztVec2& pos)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnOnNull(item);

	item->pos = pos;
	item->flags |= ztGuiItemFlags_Dirty;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetPosition(ztGuiItemID item_id, i32 align_flags, i32 anchor_flags, ztVec2 offset)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

	item->pos_align_flags = align_flags;
	item->pos_anchor_flags = anchor_flags;
	item->pos_offset = offset;

	_zt_guiItemReposition(gm, item);
	item->flags |= ztGuiItemFlags_Dirty;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetName(ztGuiItemID item_id, const char *name)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	item->name = zt_stringOverwrite(item->label, name, gm->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetLabel(ztGuiItemID item_id, const char *label)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	item->label = zt_stringOverwrite(item->label, label, gm->arena);

	item->flags |= ztGuiItemFlags_Dirty;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetTooltip(ztGuiItemID item_id, const char *tooltip)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	item->tooltip = zt_stringOverwrite(item->label, tooltip, gm->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetThemeType(ztGuiItemID item_id, const char *theme_type)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	item->theme_type = zt_stringOverwrite(item->label, theme_type, gm->arena);
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetName(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, nullptr);
	return item->name;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetLabel(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, nullptr);
	return item->label;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetTooltip(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, nullptr);
	return item->tooltip;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetThemeType(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, nullptr);
	return item->theme_type;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetAlign(ztGuiItemID item_id, i32 align_flags)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	item->align_flags = align_flags;
	item->flags |= ztGuiItemFlags_Dirty;
}

// ------------------------------------------------------------------------------------------------

i32 zt_guiItemGetAlign(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, 0);
	return item->align_flags;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsShowing(ztGuiItemID item_id)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnValOnNull(item, false);

	if (!zt_bitIsSet(item->flags, ztGuiItemFlags_Visible)) {
		return false;
	}

	ztGuiItem *parent = item->parent;
	while (parent) {
		if (!zt_bitIsSet(parent->flags, ztGuiItemFlags_Visible)) {
			return false;
		}
		parent = parent->parent;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemShow(ztGuiItemID id, bool show)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, id);

	if (show) {
		item->flags |= ztGuiItemFlags_Visible;
	}
	else {
		zt_bitRemove(item->flags, ztGuiItemFlags_Visible);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemHide(ztGuiItemID id)
{
	zt_guiItemShow(id, false);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemBringToFront(ztGuiItemID id)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, id);

	if (item->parent == nullptr && zt_bitIsSet(item->flags, ztGuiItemFlags_BringToFront)) {
		// need to make this particular child the last in the series
		if (item->sib_next) {
			if (item->sib_prev) item->sib_prev->sib_next = item->sib_next;
			if (item->sib_next) item->sib_next->sib_prev = item->sib_prev;
			zt_assert(item->sib_next->sib_prev != item->sib_next);

			if (gm->first_child == item) {
				gm->first_child = item->sib_next;
			}

			ztGuiItem *last_child = gm->first_child;
			while (last_child->sib_next) {
				last_child = last_child->sib_next;
			}

			zt_assert(last_child != nullptr);
			last_child->sib_next = item;
			item->sib_prev = last_child;
			zt_assert(item->sib_prev != item);
			item->sib_next = nullptr;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiItemGetTopLevelParent(ztGuiItemID item_id)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnValOnNull(item, ztInvalidID);

	ztGuiItem *last = item;
	ztGuiItem *parent = item->parent;
	while (parent) {
		last = parent;
		parent = parent->parent;
	}

	return last->id;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsChildOf(ztGuiItemID parent_id, ztGuiItemID child_id)
{
	_zt_guiItemFromID(parent, parent_id);
	_zt_guiItemFromID(child, child_id);

	if (parent == nullptr || child == nullptr) {
		return false;
	}

	ztGuiItem *child_parent = child->parent;
	while (child_parent) {
		if (child_parent == parent) {
			return true;
		}

		child_parent = child_parent->parent;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiItemPositionLocalToScreen(ztGuiItemID item_id, const ztVec2& pos)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnValOnNull(item, pos);

	ztVec2 result = item->pos + pos;

	ztGuiItem *parent = item->parent;
	while (parent) {
		result += parent->pos;
		parent = parent->parent;
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiItemPositionScreenToLocal(ztGuiItemID item_id, const ztVec2& pos)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnValOnNull(item, pos);

	ztVec2 result = pos - item->pos;

	ztGuiItem *parent = item->parent;
	while (parent) {
		result -= parent->pos;
		parent = parent->parent;
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetFocus(ztGuiItemID item_id, ztGuiItemID *prev_focus_item_id)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	if (prev_focus_item_id) *prev_focus_item_id = gm->focus_item;
	gm->focus_item = item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiTheme *zt_guiItemGetTheme(ztGuiItemID item_id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, nullptr);
	if (item->theme) {
		return item->theme;
	}

	for (ztGuiItem *parent = item->parent; parent; parent = parent->parent) {
		if (parent->theme) {
			return parent->theme;
		}
	}

	return &gm->default_theme;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemLock(ztGuiItemID item_id)
{
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemUnlock(ztGuiItemID item_id)
{
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemReparent(ztGuiItemID item_id, ztGuiItemID new_parent_id)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	_zt_guiItemFromID(new_parent, new_parent_id);

	zt_assert(item->sib_prev != item);
	if (new_parent == item->parent) {
		return;
	}

	if (item->parent) {
		if (item == item->parent->first_child) {
			item->parent->first_child = item->sib_next;
		}
	}
	else {
		if (item == gm->first_child) {
			gm->first_child = item->sib_next;
		}
	}
	if (item->sib_prev) item->sib_prev->sib_next = item->sib_next;
	if (item->sib_next) item->sib_next->sib_prev = item->sib_prev;
	zt_assert(item->sib_next == nullptr || item->sib_next->sib_prev != item->sib_next);

	item->sib_next = nullptr;
	item->sib_prev = nullptr;

	item->parent = new_parent;

	ztGuiItem *sibling = new_parent == nullptr ? gm->first_child : new_parent->first_child;
	if (sibling == nullptr) {
		if (new_parent == nullptr) {
			gm->first_child = item;
			return;
		}
		else {
			new_parent->first_child = item;
			return;
		}
	}

	while (sibling) {
		if (sibling->sib_next == nullptr) {
			item->sib_prev = sibling;
			sibling->sib_next = item;
			zt_assert(item->sib_prev != item);
			break;
		}
		sibling = sibling->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugFpsDisplay()
{
	static ztGuiItemID window_id = ztInvalidID;
	static ztGuiItemID text_id = ztInvalidID;
	static r64 time = 0;

	if (window_id != ztInvalidID) {
		zt_guiItemShow(window_id);
		return;
	}

	struct local
	{
		static ZT_FUNC_GUI_BUTTON_PRESSED(on_close)
		{
			zt_guiItemHide(window_id);
		}

		static ZT_FUNC_GUI_ITEM_UPDATE(item_update)
		{
			time += dt;
			if(!zt_guiItemIsShowing(window_id)) return;

			zt_strMakePrintf(fps, 128, "%.0f f/s %2.04f us/f\n%.0f f/s %2.04f us/f", 1.f / dt, dt * 1000.f, 1.f / (time / (r32)zt->game_details.current_frame), (time / (r32)zt->game_details.current_frame) * 1000.f);
			zt_guiItemSetLabel(text_id, fps);
			//zt_guiItemAutoSize(text_id);
			//zt_guiItemSetPosition(text_id, ztAlign_Left, ztAnchor_Left, ztVec2(3.f / zt_pixelsPerUnit(), 0));
		}
	};

	window_id = zt_guiMakeWindow(nullptr, ztGuiWindowFlags_AllowDrag);
	text_id = zt_guiMakeStaticText(window_id, "00000 f/s 00.0000f us/f\n00000 f/s 00.0000f us/f");
	zt_guiItemSetAlign(text_id, ztAlign_Right);

	ztGuiItemID button_id = zt_guiMakeButton(window_id, nullptr, ztGuiButtonFlags_NoBackground);
	zt_guiButtonSetCallback(button_id, local::on_close);

	_zt_guiManagerGetFromItem(gm, window_id);

	ztSprite sprite = zt_spriteMake(gm->default_theme.sprite_panel.type == ztGuiThemeSpriteType_Sprite ? gm->default_theme.sprite_panel.s.tex : gm->default_theme.sprite_panel.sns.tex, ztPoint2(16, 64), ztPoint2(16, 16));
	zt_guiButtonSetIcon(button_id, &sprite);

	zt_guiItemSetSize(window_id, ztVec2(3.25f, .65f));

	zt_guiItemSetAlign(text_id, ztAlign_Left);
	zt_guiItemSetPosition(text_id, ztAlign_Left, ztAnchor_Left, ztVec2(3.f / zt_pixelsPerUnit(), 0));
	zt_guiItemSetPosition(button_id, ztAlign_Right | ztAlign_Top, ztAnchor_Right | ztAnchor_Top, ztVec2(-3.f / zt_pixelsPerUnit(), -3.f / zt_pixelsPerUnit()));

	ztGuiItemID update_id = ztInvalidID;
	ztGuiItem *update = _zt_guiMakeItemBase(gm, window_id, ztGuiItemType_Custom, 0, &update_id);
	update->functions.update = local::item_update;

	zt_guiItemSetPosition(window_id, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugRenderingDetails()
{
	static ztGuiItemID window_id = ztInvalidID;
	static ztGuiItemID text_id = ztInvalidID;
	static r64 time = 0;

	if(window_id != ztInvalidID) {
		zt_guiItemShow(window_id);
		return;
	}

	struct local
	{
		static ZT_FUNC_GUI_BUTTON_PRESSED(on_close)
		{
			zt_guiItemHide(window_id);
		}

		static ZT_FUNC_GUI_ITEM_UPDATE(item_update)
		{
			time += dt;
			if(!zt_guiItemIsShowing(window_id)) return;

			zt_strMakePrintf(fps, 256, "%d triangles\n%d shader switches\n%d tex switches\n%d draw calls", zt->game_details.prev_frame.triangles_drawn, zt->game_details.prev_frame.shader_switches, zt->game_details.prev_frame.texture_switches, zt->game_details.prev_frame.draw_calls);
			zt_guiItemSetLabel(text_id, fps);
		}

		static ZT_FUNC_GUI_ITEM_RENDER(item_render)
		{
		}
	};

	window_id = zt_guiMakeWindow(nullptr, ztGuiWindowFlags_AllowDrag);
	text_id = zt_guiMakeStaticText(window_id, "00000000 triangles\n0000 shader switches\n0000 tex switches\n0000 draw calls");

	ztGuiItemID button_id = zt_guiMakeButton(window_id, nullptr, ztGuiButtonFlags_NoBackground);
	zt_guiButtonSetCallback(button_id, local::on_close);

	_zt_guiManagerGetFromItem(gm, window_id);

	ztSprite sprite = zt_spriteMake(gm->default_theme.sprite_panel.type == ztGuiThemeSpriteType_Sprite ? gm->default_theme.sprite_panel.s.tex : gm->default_theme.sprite_panel.sns.tex, ztPoint2(16, 64), ztPoint2(16, 16));
	zt_guiButtonSetIcon(button_id, &sprite);

	zt_guiItemSetSize(window_id, ztVec2(3.25f, 1.35f));

	zt_guiItemSetAlign(text_id, ztAlign_Left);
	zt_guiItemSetPosition(text_id, ztAlign_Left, ztAnchor_Left, ztVec2(3.f / zt_pixelsPerUnit(), 0));
	zt_guiItemSetPosition(button_id, ztAlign_Right | ztAlign_Top, ztAnchor_Right | ztAnchor_Top, ztVec2(-3.f / zt_pixelsPerUnit(), -3.f / zt_pixelsPerUnit()));

	ztGuiItemID update_id = ztInvalidID;
	ztGuiItem *update = _zt_guiMakeItemBase(gm, window_id, ztGuiItemType_Custom, 0, &update_id);
	update->functions.update = local::item_update;
	update->functions.render = local::item_render;

	zt_guiItemSetPosition(window_id, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right, ztVec2(0, -.75f));
}
// ------------------------------------------------------------------------------------------------

void zt_guiInitDebug(ztGuiManagerID gui_manager)
{
	static ztGuiItemID menu_id;

	enum
	{
		ztGuiDebugMenu_FpsDisplay,
		ztGuiDebugMenu_RenderingDetails,
	};

	struct local
	{
		static ZT_FUNC_GUI_BUTTON_PRESSED(on_open_menu)
		{
			zt_guiMenuPopupAtItem(menu_id, item_id, ztAlign_Left | ztAlign_Bottom);
		}

		static ZT_FUNC_GUI_MENU_SELECTED(on_menu_item)
		{
			switch (menu_item)
			{
				case ztGuiDebugMenu_FpsDisplay: {
					_zt_guiDebugFpsDisplay();
				} break;

				case ztGuiDebugMenu_RenderingDetails: {
					_zt_guiDebugRenderingDetails();
				} break;
			};
		}
	};

	_zt_guiManagerCheckAndGet(gm, gui_manager);

	ztGuiItemID button = zt_guiMakeButton(ztInvalidID, nullptr);
	ztSprite sprite = zt_spriteMake(gm->default_theme.sprite_panel.type == ztGuiThemeSpriteType_Sprite ? gm->default_theme.sprite_panel.s.tex : gm->default_theme.sprite_panel.sns.tex, ztPoint2(1, 80), ztPoint2(23, 23));
	zt_guiButtonSetIcon(button, &sprite);
	zt_guiButtonSetCallback(button, local::on_open_menu);
	zt_guiItemSetPosition(button, ztAlign_Top, ztAnchor_Top);

	menu_id = zt_guiMakeMenu();
	zt_guiMenuAppend(menu_id, "FPS Display", ztGuiDebugMenu_FpsDisplay);
	zt_guiMenuAppend(menu_id, "Rendering Details", ztGuiDebugMenu_RenderingDetails);

	zt_guiMenuSetCallback(menu_id, local::on_menu_item);

	_zt_guiDebugFpsDisplay();
	_zt_guiDebugRenderingDetails();
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // implementation
