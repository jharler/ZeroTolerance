/**************************************************************************************************
 ** file: zt_game_gui.h v 0.00 (active initial development)
 **
 ** This software is dual-licensed to the public domain and under the following
 ** license: you are granted a perpetual, irrevocable license to copy, modify,
 ** publish, and distribute this file as you see fit.
 **
 ** No warranty is offered or implied.  Use this at your own risk.
 **
 **************************************************************************************************
   
	Zero Tolerance Game GUI Library
   
	In exactly one c/cpp source file of your project, you must:

		#define ZT_GAME_GUI_IMPLEMENTATION
		#include "zt_game_gui.h"
    
 **************************************************************************************************

    Options:


 **************************************************************************************************

	Implimentation Options: (only used with ZT_GAME_GUI_IMPLEMENTATION #include)


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
typedef i32 ztGuiTreeNodeID;

// ------------------------------------------------------------------------------------------------

enum ztGuiThemeSpriteType_Enum
{
	ztGuiThemeSpriteType_Invalid,
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

ztVec2 zt_guiThemeSpriteGetSize(ztGuiThemeSprite *sprite);
ztVec2 zt_guiThemeButtonSpriteGetSize(ztGuiThemeButtonSprite *sprite);

// ------------------------------------------------------------------------------------------------

struct ztGuiTheme
{
	ztFontID font;
	r32      font_scale;
	ztColor  font_color;

	ztColor back_color;
	ztColor fore_color;
	ztColor highlight_color;

	r32 padding; // space around interior items
	r32 spacing; // space between interior items

	ztSprite         sprite_icon_close;
	ztSprite         sprite_icon_resize;
	ztSprite         sprite_icon_collapse;
	ztSprite         sprite_icon_expand;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_window;
	ztGuiThemeSprite sprite_window_collapsed;

	r32 window_title_height;
	i32 window_title_align;
	r32 window_title_padding_x;
	r32 window_title_padding_y;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_panel;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_collapsing_panel_header;
	r32 collapsing_panel_header_h;

	// ----------------------------------------------------------------

	ztGuiThemeButtonSprite sprite_button;

	r32 button_default_w;
	r32 button_default_h;
	r32 button_padding_w;
	r32 button_padding_h;
	r32 button_dip_x;
	r32 button_dip_y;

	// ----------------------------------------------------------------

	ztGuiThemeButtonSprite sprite_checkbox;
	ztGuiThemeSprite       sprite_checkbox_check;

	r32 checkbox_size_w;
	r32 checkbox_size_h;

	// ----------------------------------------------------------------

	ztGuiThemeButtonSprite sprite_radio;
	ztGuiThemeSprite       sprite_radio_check;

	r32 radio_size_w;
	r32 radio_size_h;

	// ----------------------------------------------------------------

	ztGuiThemeButtonSprite sprite_slider_horz_handle;
	ztGuiThemeButtonSprite sprite_slider_vert_handle;
	ztGuiThemeSprite       sprite_slider_background;
	ztGuiThemeSprite       sprite_slider;

	r32 slider_handle_w;
	r32 slider_handle_h;
	r32 slider_background_h;

	// ----------------------------------------------------------------

	ztGuiThemeButtonSprite sprite_scrollbar_horz_handle;
	ztGuiThemeButtonSprite sprite_scrollbar_vert_handle;
	ztGuiThemeButtonSprite sprite_scrollbar_horz_button_neg;
	ztGuiThemeButtonSprite sprite_scrollbar_horz_button_pos;
	ztGuiThemeButtonSprite sprite_scrollbar_vert_button_neg;
	ztGuiThemeButtonSprite sprite_scrollbar_vert_button_pos;
	ztGuiThemeSprite       sprite_scrollbar_background;

	bool scrollbar_has_buttons;
	r32  scrollbar_button_w;
	r32  scrollbar_button_h;
	r32  scrollbar_handle_min_size;

	// ----------------------------------------------------------------

	r32 scroll_container_padding_x;
	r32 scroll_container_padding_y;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_textedit;
	ztGuiThemeSprite sprite_textedit_select;

	r32 textedit_padding_x;
	r32 textedit_padding_y;
	r32 textedit_default_w;
	r32 textedit_default_h;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_menu;
	ztGuiThemeSprite sprite_menu_highlight;
	ztGuiThemeSprite sprite_menu_submenu;
	ztGuiThemeSprite sprite_menu_check;

	r32 menu_padding_x;
	r32 menu_padding_y;
	r32 menu_submenu_icon_x;
	r32 menu_submenu_icon_y;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_tree_background;
	ztGuiThemeSprite sprite_tree_highlight;
	ztSprite         sprite_tree_collapse;
	ztSprite         sprite_tree_expand;

	r32 tree_indent;

	// ----------------------------------------------------------------

	ztGuiThemeButtonSprite sprite_combobox_background;
	ztGuiThemeButtonSprite sprite_combobox_button;
	ztGuiThemeSprite       sprite_combobox_dropdown;

	r32 combobox_size_y;
	r32 combobox_button_size_x;

	// ----------------------------------------------------------------

	ztGuiThemeSprite sprite_group;

};

// ------------------------------------------------------------------------------------------------

#define _ztGuiItemTypeList \
	_ztGIT(ztGuiItemType_Invalid        ) \
	_ztGIT(ztGuiItemType_Window         ) \
	_ztGIT(ztGuiItemType_Panel          ) \
	_ztGIT(ztGuiItemType_CollapsingPanel) \
	_ztGIT(ztGuiItemType_StaticText     ) \
	_ztGIT(ztGuiItemType_Button         ) \
	_ztGIT(ztGuiItemType_ToggleButton   ) \
	_ztGIT(ztGuiItemType_Checkbox       ) \
	_ztGIT(ztGuiItemType_RadioButton    ) \
	_ztGIT(ztGuiItemType_Slider         ) \
	_ztGIT(ztGuiItemType_Menu           ) \
	_ztGIT(ztGuiItemType_Scrollbar      ) \
	_ztGIT(ztGuiItemType_ScrollContainer) \
	_ztGIT(ztGuiItemType_TextEdit       ) \
	_ztGIT(ztGuiItemType_Tab            ) \
	_ztGIT(ztGuiItemType_Tree           ) \
	_ztGIT(ztGuiItemType_ComboBox       ) \
	_ztGIT(ztGuiItemType_SpriteDisplay  ) \
	_ztGIT(ztGuiItemType_ProgressBar    ) \
	_ztGIT(ztGuiItemType_Sizer          ) \
	_ztGIT(ztGuiItemType_Custom         )

// ------------------------------------------------------------------------------------------------

#define _ztGIT(TYPE)	TYPE,

enum ztGuiItemType_Enum
{
	_ztGuiItemTypeList
};

#undef _ztGIT

// ------------------------------------------------------------------------------------------------

inline const char* zt_guiItemTypeName(ztGuiItemType_Enum type)
{
#define _ztGIT(TYPE) case TYPE: return (#TYPE) + 14;
	switch (type)
	{
		_ztGuiItemTypeList
	}
	return "Unknown";
#undef _ztGIT
}

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
	ztGuiItemFlags_Disabled         = (1<<8),
	ztGuiItemFlags_Locked           = (1<<9),
};

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_GUI_ITEM_UPDATE(name) void name(ztGuiItemID item_id, r32 dt, void *user_data)
typedef ZT_FUNC_GUI_ITEM_UPDATE(zt_guiItemUpdate_Func);

#define ZT_FUNC_GUI_ITEM_RENDER(name) void name(ztGuiItemID item_id, ztDrawList *draw_list, ztGuiTheme *theme, const ztVec2& offset, bool enabled, void *user_data)
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

#define ZT_FUNC_GUI_BUTTON_PRESSED(name) void name(ztGuiItemID button_id, void *user_data)
typedef ZT_FUNC_GUI_BUTTON_PRESSED(zt_guiButtonPressed_Func);

#define ZT_FUNC_GUI_MENU_SELECTED(name) void name(ztGuiItemID menu_id, i32 menu_item, void *user_data)
typedef ZT_FUNC_GUI_MENU_SELECTED(zt_guiMenuSelected_Func);

#define ZT_FUNC_GUI_TEXTEDIT_KEY(name) void name(ztGuiItemID textedit_id, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], bool *should_process)
typedef ZT_FUNC_GUI_TEXTEDIT_KEY(zt_guiTextEditKey_Func);

#define ZT_FUNC_GUI_TREE_ITEM_SELECTED(name) void name(ztGuiItemID tree_id, ztGuiTreeNodeID node_id, void *user_data)
typedef ZT_FUNC_GUI_TREE_ITEM_SELECTED(zt_guiTreeItemSelected_Func);

#define ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(name) void name(ztGuiItemID combobox_id, int selected, void *user_data)
typedef ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(zt_guiComboBoxItemSelected_Func);

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
	ztGuiWindowFlags_CloseHides    = (1 << 5),

	ztGuiWindowFlags_Default = ztGuiWindowFlags_ShowTitle | ztGuiWindowFlags_AllowDrag | ztGuiWindowFlags_AllowResize | ztGuiWindowFlags_AllowClose | ztGuiWindowFlags_AllowCollapse,
};

// ------------------------------------------------------------------------------------------------

enum ztGuiPanelFlags_Enum
{
	ztGuiPanelFlags_AllowDrag      = (1 << 31),
	ztGuiPanelFlags_DrawBackground = (1 << 30),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiStaticTextFlags_Enum
{
	ztGuiStaticTextFlags_Fancy = (1 << 31),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiButtonFlags_Enum
{
	ztGuiButtonFlags_NoBackground = (1 << 0),
	ztGuiButtonFlags_OnPressDip   = (1 << 1),
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

enum ztGuiScrollContainerFlags_Enum
{
	ztGuiScrollContainerFlags_ShowScrollVert = (1 << 31),
	ztGuiScrollContainerFlags_ShowScrollHorz = (1 << 30),
	ztGuiScrollContainerFlags_StretchVert    = (1 << 29),
	ztGuiScrollContainerFlags_StretchHorz    = (1 << 28),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiTextEditFlags_Enum
{
	ztGuiTextEditFlags_MultiLine = (1 << 31),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiItemOrient_Enum
{
	ztGuiItemOrient_Horz = (1 << 0),
	ztGuiItemOrient_Vert = (1 << 1),
};

// ------------------------------------------------------------------------------------------------

ztGuiManagerID zt_guiManagerMake(ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena);
void zt_guiManagerFree(ztGuiManagerID gui_manager);
void zt_guiManagerUpdate(ztGuiManagerID gui_manager, r32 dt);
bool zt_guiManagerHandleInput(ztGuiManagerID gui_manager, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], ztInputMouse *input_mouse);
void zt_guiManagerRender(ztGuiManagerID gui_manager, ztDrawList *draw_list);

void zt_guiSetActiveManager(ztGuiManagerID gui_manager);

void zt_guiManagerSetKeyboardFocus(ztGuiManagerID gui_manager, bool keyboard_focus = true);
bool zt_guiManagerHasKeyboardFocus(ztGuiManagerID gui_manager);

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeWindow(const char *title, i32 flags = ztGuiWindowFlags_Default);
ztGuiItemID zt_guiMakeScrollWindow(const char *title, i32 scroll_dir, i32 flags = ztGuiWindowFlags_Default); // set the size of the content item
ztGuiItemID zt_guiMakePanel(ztGuiItemID parent, i32 item_flags = 0);
ztGuiItemID zt_guiMakeCollapsingPanel(ztGuiItemID parent, const char *label);
ztGuiItemID zt_guiMakeStaticText(ztGuiItemID parent, const char *label, i32 flags = 0, i32 max_chars = 64);
ztGuiItemID zt_guiMakeButton(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeToggleButton(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeCheckbox(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeRadioButton(ztGuiItemID parent, const char *label, i32 flags = 0, bool *live_value = nullptr);
ztGuiItemID zt_guiMakeSlider(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItemID zt_guiMakeScrollbar(ztGuiItemID parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItemID zt_guiMakeScrollContainer(ztGuiItemID parent, i32 flags = 0);
ztGuiItemID zt_guiMakeTextEdit(ztGuiItemID parent, const char *value, i32 flags = 0, i32 buffer_size = 1024);
ztGuiItemID zt_guiMakeMenu();
ztGuiItemID zt_guiMakeTree(ztGuiItemID parent, i32 max_items);
ztGuiItemID zt_guiMakeComboBox(ztGuiItemID parent, i32 max_items);
ztGuiItemID zt_guiMakeSpriteDisplay(ztGuiItemID parent, ztGuiThemeSprite *sprite);

ztGuiItemID zt_guiMakeSizer(ztGuiItemID parent, ztGuiItemOrient_Enum orient);

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
bool zt_guiItemIsVisible(ztGuiItemID id);

void zt_guiItemEnable(ztGuiItemID id, bool enable = true);
void zt_guiItemDisable(ztGuiItemID id);
bool zt_guiItemIsEnabled(ztGuiItemID id);

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

ztGuiItemID zt_guiWindowGetContentParent(ztGuiItemID window);

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiCollapsingPanelGetContentParent(ztGuiItemID panel);
void zt_guiCollapsingPanelCollapse(ztGuiItemID panel);
void zt_guiCollapsingPanelExpand(ztGuiItemID panel);

// ------------------------------------------------------------------------------------------------

// used for button and toggle button
void zt_guiButtonSetIcon(ztGuiItemID button, ztSprite *icon);
void zt_guiButtonSetTextPosition(ztGuiItemID button, i32 align_flags);
void zt_guiButtonSetCallback(ztGuiItemID button, zt_guiButtonPressed_Func, void *user_data = nullptr);

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
void zt_guiScrollContainerSetScroll(ztGuiItemID scroll, ztGuiItemOrient_Enum orient, r32 value);

// ------------------------------------------------------------------------------------------------

int zt_guiTextEditGetValue(ztGuiItemID text, char *buffer, int buffer_len);
void zt_guiTextEditSetValue(ztGuiItemID text, const char *value);
void zt_guiTextEditSetSelection(ztGuiItemID text, int sel_beg, int sel_end);
void zt_guiTextEditGetSelection(ztGuiItemID text, int *sel_beg, int *sel_end);
void zt_guiTextEditSelectAll(ztGuiItemID text);
int  zt_guiTextEditGetCursorPos(ztGuiItemID text);
void zt_guiTextEditSetCursorPos(ztGuiItemID text, int cursor_pos);
void zt_guiTextEditSetCallback(ztGuiItemID text, zt_guiTextEditKey_Func *on_key);


// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppend(ztGuiItemID menu, const char *label, i32 id, void *user_data = nullptr, ztSprite *icon = nullptr);
void zt_guiMenuAppendSubmenu(ztGuiItemID menu, const char *label, ztGuiItemID submenu, ztSprite *icon = nullptr);
void zt_guiMenuPopupAtItem(ztGuiItemID menu, ztGuiItemID item, i32 align_flags, const ztVec2& offset = ztVec2::zero);
void zt_guiMenuPopupAtPosition(ztGuiItemID menu, const ztVec2& pos);
bool zt_guiMenuGetSelected(ztGuiItemID menu, i32 *selected_id);
void zt_guiMenuSetCallback(ztGuiItemID menu, zt_guiMenuSelected_Func *on_selected);

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItemID tree, const char *item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID);
ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItemID tree, ztGuiItemID item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID);

ztGuiTreeNodeID zt_guiTreeGetSelected(ztGuiItemID tree);
void zt_guiTreeSetSelected(ztGuiItemID tree, ztGuiTreeNodeID node);

ztGuiTreeNodeID zt_guiTreeGetRoot(ztGuiItemID tree);
ztGuiItemID zt_guiTreeGetNodeItem(ztGuiItemID tree, ztGuiTreeNodeID node);
void *zt_guiTreeGetNodeUserData(ztGuiItemID tree, ztGuiTreeNodeID node);
void zt_guiTreeSetCallback(ztGuiItemID tree, zt_guiTreeItemSelected_Func on_item_sel, void *user_data);

void zt_guiTreeClear(ztGuiItemID tree);

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxSetContents(ztGuiItemID combobox_id, const char **contents, int contents_count, int active);
void zt_guiComboBoxClear(ztGuiItemID combobox_id);
void zt_guiComboBoxAppend(ztGuiItemID combobox_id, const char *content);
int zt_guiComboBoxGetSelected(ztGuiItemID combobox_id);
int zt_guiComboBoxGetItemCount(ztGuiItemID combobox_id);
int zt_guiComboBoxGetItemText(ztGuiItemID combobox_id, int index, char* buffer, int buffer_len);
void zt_guiComboBoxSetCallback(ztGuiItemID combobox_id, zt_guiComboBoxItemSelected_Func *on_item_sel, void *user_data);

// ------------------------------------------------------------------------------------------------

void zt_guiSpriteDisplaySetSprite(ztGuiItemID item_id, ztGuiThemeSprite *sprite);

// ------------------------------------------------------------------------------------------------

void zt_guiSizerAddItem(ztGuiItemID sizer, ztGuiItemID item_id, int proportion, r32 padding, i32 align_flags = ztAlign_Center, i32 grow_direction = ztGuiItemOrient_Horz | ztGuiItemOrient_Vert);
void zt_guiSizerAddStretcher(ztGuiItemID sizer, int proportion, r32 padding = 0);

void zt_guiSizerSizeToParent(ztGuiItemID sizer, bool size_to_parent = true);
void zt_guiSizerSizeParent(ztGuiItemID sizer, bool size_parent_x = true, bool size_parent_y = true);

void zt_guiSizerRecalc(ztGuiItemID item);
void zt_guiSizerRecalcImmediately(ztGuiItemID sizer);

ztVec2 zt_guiSizerGetMinSize(ztGuiItemID sizer);

// ------------------------------------------------------------------------------------------------

void zt_guiInitDebug(ztGuiManagerID gui_manager);

// ------------------------------------------------------------------------------------------------

#define ztDebugConsoleParams(PARAMS)	char PARAMS[16][256]

#define ZT_FUNC_DEBUG_CONSOLE_COMMAND(name) void name(ztDebugConsoleParams(params), int params_count)
typedef ZT_FUNC_DEBUG_CONSOLE_COMMAND(zt_debugConsole_Func);

#define ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(name) void name(char **params, int params_count, char *auto_fill, int auto_fill_len)
typedef ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(zt_debugConsoleAutoComplete_Func);

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleAddCommand(const char *command, const char *help, zt_debugConsole_Func *command_func, zt_debugConsoleAutoComplete_Func auto_complete_func);
void zt_debugConsoleRemoveCommand(const char *command);

enum ztDebugConsoleLevel_Enum
{
	ztDebugConsoleLevel_User,
	ztDebugConsoleLevel_Command,
	ztDebugConsoleLevel_Help,
	ztDebugConsoleLevel_Warning,
	ztDebugConsoleLevel_Error,
	ztDebugConsoleLevel_System,
};

void zt_debugConsoleLog(ztDebugConsoleLevel_Enum message_level, const char *command, ...);
void zt_debugConsoleLogUser(const char *command, ...);
void zt_debugConsoleLogCommand(const char *command, ...);
void zt_debugConsoleLogHelp(const char *command, ...);
void zt_debugConsoleLogWarning(const char *command, ...);
void zt_debugConsoleLogError(const char *command, ...);
void zt_debugConsoleLogSystem(const char *command, ...);

void zt_debugConsoleToggle(bool *is_shown = nullptr);

// ------------------------------------------------------------------------------------------------

void zt_debugLogGuiHierarchy(ztGuiItemID item);

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
	ztVec2 prev_size;

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

	// -------------------------------------------------

	struct ztDragState
	{
		bool dragging;
		r32 offset_x;
		r32 offset_y;
	};

	// -------------------------------------------------

	struct ztSizerItemEntry
	{
		ztGuiItem *item;
		int proportion;
		r32 padding;
		int align_flags;
		int grow_direction;

		ztSizerItemEntry *next;
	};

	// -------------------------------------------------

	struct ztTreeItem
	{
		ztGuiTreeNodeID node_id;
		bool expanded;
		ztGuiItemID control_button_id;
		ztGuiItemID item_id;
		void *user_data;

		ztTreeItem *first_child;
		ztTreeItem *next;
		ztTreeItem *parent;
	};

	// -------------------------------------------------

	union {
		struct {
			i32 flags;
			i32 state_flags;
			ztDragState drag_state;
			ztGuiItemID content_id;
			ztGuiItemID button_expand_id;
			r32 resize[2];
			r32 pos[2];
			r32 size[2];

			// TODO(josh): need some way to keep track of focus on a per-window basis so switching back and forth between windows works as expected
		} window;

		// -------------------------------------------------

		struct {
			ztGuiItemID content_panel_id;
			ztGuiItemID button_id;
		} collapsing_panel;

		// -------------------------------------------------

		struct {
			bool *live_value;
			i32 flags;
			zt_guiButtonPressed_Func *on_pressed;
			void *on_pressed_user_data;
			ztSprite *icon;
			i32 text_pos;
		} button;

		// -------------------------------------------------

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

		// -------------------------------------------------

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

		// -------------------------------------------------

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

			zt_guiTextEditKey_Func *on_key;
		} textedit;

		// -------------------------------------------------

		struct {
			ztString *display;
			i32 *ids;
			ztGuiItemID *submenus;
			ztSprite **icons;
			void **user_datas;

			i32 item_count;
			i32 highlighted;
			i32 selected;
			bool just_opened;

			zt_guiMenuSelected_Func *on_selected;
		} menu;

		// -------------------------------------------------

		struct {
			ztGuiItemOrient_Enum orient;

			ztSizerItemEntry *items;
			r32 size[2];
			bool size_to_parent;
			bool size_parent_x, size_parent_y;
		} sizer;

		// -------------------------------------------------

		struct {
			ztGuiItemID container_id;
			ztGuiItemID content_id;

			ztTreeItem *root_item;
			ztTreeItem *active_item;

			ztGuiTreeNodeID last_id;
			ztMemoryArena* arena;

			zt_guiTreeItemSelected_Func *on_item_sel;
			void *on_item_sel_user_data;
		} tree;

		// -------------------------------------------------

		struct {
			ztGuiItemID popup_id;

			ztString* contents;
			int contents_size;
			int contents_count;
			int selected;

			zt_guiComboBoxItemSelected_Func *on_selected;
			void *on_selected_user_data;
		} combobox;

		struct {
			ztGuiThemeSprite* sprite;
		} sprite_display;
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
	i32 item_cache_used;

	ztGuiTheme default_theme;

	ztMemoryArena *arena;
	i32 base_id;
};

// ------------------------------------------------------------------------------------------------

struct ztConsoleCommand
{
	char command[32];
	char help[1024];

	zt_debugConsole_Func *on_command;
	zt_debugConsoleAutoComplete_Func *on_auto_complete;

	ztConsoleCommand *next;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiGlobals
{
	ztGuiManager* gui_managers[4];
	ztGuiManagerID active_gui_manager;

	ztConsoleCommand *console_commands;
	ztGuiItemID console_window_id;
	ztGuiItemID console_display_container_id;
	ztGuiItemID console_display_id;
	ztGuiItemID console_command_id;

	ztMemoryArena *arena;
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
	zt_gui->arena = arena;
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
		0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00, 0xc5, 0x90, 0xce, 0x67, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x49, 0x6d, 0x61, 0x67, 0x65, 0x52, 0x65, 0x61, 0x64, 0x79, 0x71, 0xc9, 0x65, 0x3c, 0x00, 0x00, 0x03, 0x64, 0x69, 0x54, 0x58, 0x74, 0x58, 0x4d, 0x4c, 0x3a, 0x63, 0x6f, 0x6d, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x78, 0x6d, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3f, 0x78, 0x70, 0x61, 0x63, 0x6b, 0x65, 0x74, 0x20, 0x62, 0x65, 0x67, 0x69, 0x6e, 0x3d, 0x22, 0xef, 0xbb, 0xbf, 0x22, 0x20, 0x69, 0x64, 0x3d, 0x22, 0x57, 0x35, 0x4d, 0x30, 0x4d, 0x70, 0x43, 0x65, 0x68, 0x69, 0x48, 0x7a, 0x72, 0x65, 0x53, 0x7a, 0x4e, 0x54, 0x63, 0x7a, 0x6b, 0x63, 0x39, 0x64, 0x22, 0x3f, 0x3e, 0x20, 0x3c, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x6d, 0x65, 0x74, 0x61, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x3d, 0x22, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x3a, 0x6e, 0x73, 0x3a, 0x6d, 0x65, 0x74, 0x61, 0x2f, 0x22, 0x20, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x74, 0x6b, 0x3d, 0x22, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x58, 0x4d, 0x50, 0x20, 0x43, 0x6f, 0x72, 0x65, 0x20, 0x35, 0x2e, 0x30, 0x2d, 0x63, 0x30, 0x36, 0x30, 0x20, 0x36, 0x31, 0x2e, 0x31, 0x33, 0x34, 0x37, 0x37, 0x37, 0x2c, 0x20, 0x32, 0x30, 0x31, 0x30, 0x2f, 0x30, 0x32, 0x2f, 0x31, 0x32, 0x2d, 0x31, 0x37, 0x3a, 0x33, 0x32, 0x3a, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x3e, 0x20, 0x3c, 0x72, 0x64, 0x66, 0x3a, 0x52, 0x44, 0x46, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x72, 0x64, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x31, 0x39, 0x39, 0x39, 0x2f, 0x30, 0x32, 0x2f, 0x32, 0x32, 0x2d, 0x72, 0x64, 0x66, 0x2d, 0x73, 0x79, 0x6e, 0x74, 0x61, 0x78, 0x2d, 0x6e, 0x73, 0x23, 0x22, 0x3e, 0x20, 0x3c, 0x72, 0x64, 0x66, 0x3a, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x72, 0x64, 0x66, 0x3a, 0x61, 0x62, 0x6f, 0x75, 0x74, 0x3d, 0x22, 0x22, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x78, 0x61, 0x70, 0x2f, 0x31, 0x2e, 0x30, 0x2f, 0x6d, 0x6d, 0x2f, 0x22, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x73, 0x74, 0x52, 0x65, 0x66, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x78, 0x61, 0x70, 0x2f, 0x31, 0x2e, 0x30, 0x2f, 0x73, 0x54, 0x79, 0x70, 0x65, 0x2f, 0x52, 0x65, 0x73, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x52, 0x65, 0x66, 0x23, 0x22, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x6d, 0x70, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6e, 0x73, 0x2e, 0x61, 0x64, 0x6f, 0x62, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x78, 0x61, 0x70, 0x2f, 0x31, 0x2e, 0x30, 0x2f, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x4f, 0x72, 0x69, 0x67, 0x69, 0x6e, 0x61, 0x6c, 0x44, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x64, 0x69, 0x64, 0x3a, 0x33, 0x34, 0x30, 0x46, 0x46, 0x41, 0x32, 0x38, 0x34, 0x44, 0x34, 0x46, 0x45, 0x36, 0x31, 0x31, 0x42, 0x31, 0x31, 0x32, 0x41, 0x41, 0x45, 0x31, 0x46, 0x43, 0x45, 0x36, 0x34, 0x31, 0x31, 0x39, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x44, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x64, 0x69, 0x64, 0x3a, 0x32, 0x41, 0x34, 0x42, 0x42, 0x45, 0x38, 0x34, 0x37, 0x35, 0x42, 0x42, 0x31, 0x31, 0x45, 0x36, 0x39, 0x46, 0x42, 0x38, 0x38, 0x46, 0x35, 0x30, 0x38, 0x31, 0x36, 0x42, 0x45, 0x38, 0x42, 0x30, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x49, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x69, 0x69, 0x64, 0x3a, 0x32, 0x41, 0x34, 0x42, 0x42, 0x45, 0x38, 0x33, 0x37, 0x35, 0x42, 0x42, 0x31, 0x31, 0x45, 0x36, 0x39, 0x46, 0x42, 0x38, 0x38, 0x46, 0x35, 0x30, 0x38, 0x31, 0x36, 0x42, 0x45, 0x38, 0x42, 0x30, 0x22, 0x20, 0x78, 0x6d, 0x70, 0x3a, 0x43, 0x72, 0x65, 0x61, 0x74, 0x6f, 0x72, 0x54, 0x6f, 0x6f, 0x6c, 0x3d, 0x22, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x50, 0x68, 0x6f, 0x74, 0x6f, 0x73, 0x68, 0x6f, 0x70, 0x20, 0x43, 0x53, 0x35, 0x20, 0x57, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x73, 0x22, 0x3e, 0x20, 0x3c, 0x78, 0x6d, 0x70, 0x4d, 0x4d, 0x3a, 0x44, 0x65, 0x72, 0x69, 0x76, 0x65, 0x64, 0x46, 0x72, 0x6f, 0x6d, 0x20, 0x73, 0x74, 0x52, 0x65, 0x66, 0x3a, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x69, 0x69, 0x64, 0x3a, 0x41, 0x34, 0x44, 0x34, 0x36, 0x38, 0x37, 0x33, 0x45, 0x44, 0x37, 0x34, 0x45, 0x36, 0x31, 0x31, 0x39, 0x33, 0x45, 0x37, 0x43, 0x30, 0x39, 0x41, 0x44, 0x41, 0x42, 0x38, 0x45, 0x34, 0x31, 0x41, 0x22, 0x20, 0x73, 0x74, 0x52, 0x65, 0x66, 0x3a, 0x64, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x49, 0x44, 0x3d, 0x22, 0x78, 0x6d, 0x70, 0x2e, 0x64, 0x69, 0x64, 0x3a, 0x33, 0x34, 0x30, 0x46, 0x46, 0x41, 0x32, 0x38, 0x34, 0x44, 0x34, 0x46, 0x45, 0x36, 0x31, 0x31, 0x42, 0x31, 0x31, 0x32, 0x41, 0x41, 0x45, 0x31, 0x46, 0x43, 0x45, 0x36, 0x34, 0x31, 0x31, 0x39, 0x22, 0x2f, 0x3e, 0x20, 0x3c, 0x2f, 0x72, 0x64, 0x66, 0x3a, 0x44, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x20, 0x3c, 0x2f, 0x72, 0x64, 0x66, 0x3a, 0x52, 0x44, 0x46, 0x3e, 0x20, 0x3c, 0x2f, 0x78, 0x3a, 0x78, 0x6d, 0x70, 0x6d, 0x65, 0x74, 0x61, 0x3e, 0x20, 0x3c, 0x3f, 0x78, 0x70, 0x61, 0x63, 0x6b, 0x65, 0x74, 0x20, 0x65, 0x6e, 0x64, 0x3d, 0x22, 0x72, 0x22, 0x3f, 0x3e, 0x32, 0xe5, 0x30, 0xc4, 0x00, 0x00, 0x1a, 0xce, 0x49, 0x44, 0x41, 0x54, 0x78, 0xda, 0xec, 0xdd, 0x7f, 0x8c, 0x14, 0x65, 0x9e, 0xc7, 0xf1, 0xa7, 0xc6, 0x39, 0x84, 0x10, 0x8c, 0xe3, 0x8f, 0x9c, 0x6b, 0x3c, 0xa2, 0x63, 0x62, 0xa2, 0xde, 0x9e, 0x3f, 0x40, 0x14, 0x15, 0x7f, 0x05, 0xf4, 0xd4, 0xf3, 0xf6, 0xd6, 0x05, 0xd4, 0xc4,
		0x8d, 0x2e, 0xb7, 0xc7, 0xac, 0xeb, 0x1f, 0xfe, 0x65, 0x1c, 0xc6, 0x05, 0xc5, 0xac, 0x73, 0xc3, 0x5f, 0x17, 0xe2, 0xe9, 0x02, 0xae, 0x2c, 0x2e, 0xc4, 0x44, 0x20, 0xb8, 0xe4, 0xb2, 0x87, 0xec, 0x80, 0x02, 0x06, 0x51, 0x10, 0x45, 0x71, 0x24, 0x31, 0xf2, 0x43, 0x8e, 0xac, 0x12, 0x35, 0x23, 0xb0, 0xe0, 0x20, 0x3f, 0xea, 0xfa, 0xdb, 0x54, 0x8d, 0x3d, 0x35, 0x55, 0x5d, 0x4f, 0x3d, 0xf5, 0x54, 0x75, 0x57, 0xcf, 0xfb, 0x95, 0xb4, 0xd8, 0xd3, 0x55, 0xdd, 0xd5, 0xd5, 0xd5, 0xfd, 0xfd, 0xd4, 0x53, 0x4f, 0x3d, 0xe5, 0x74, 0x76, 0x76, 0xba, 0xaa, 0x86, 0x66, 0xcc, 0x98, 0xe1, 0x2c, 0x58, 0xb0, 0x20, 0xd1, 0x32, 0x4c, 0x9f, 0x3e, 0xdd, 0xd9, 0xb8, 0x71, 0x63, 0xa2, 0x79, 0x6e, 0xb8, 0xe1, 0x06, 0xa3, 0x79, 0x26, 0x4f, 0x9e, 0x9c, 0x68, 0x9e, 0xe5, 0xcb, 0x97, 0x3b, 0x49, 0xa6, 0x4f, 0xfa, 0xde, 0x2b, 0xd7, 0x81, 0xfc, 0x9b, 0xf4, 0x3d, 0x55, 0xbe, 0x37, 0x1b, 0xf3, 0x0f, 0xd5, 0xe5, 0x8f, 0x7b, 0x5f, 0x59, 0x3d, 0x2f, 0x00, 0xd8, 0xd2, 0x2c, 0xff, 0xe9, 0xe8, 0xe8, 0xd8, 0x5b, 0x8b, 0x17, 0x2f, 0x85, 0x8f, 0xd1, 0xfe, 0xff, 0xb7, 0xb5, 0xb5, 0x69, 0xcd, 0x33, 0x7f, 0xfe, 0xfc, 0xfe, 0xff, 0x7f, 0xeb, 0xad, 0xb7, 0xb4, 0xe6, 0x99, 0x30, 0x61, 0xc2, 0x0f, 0xaf, 0xd9, 0xd5, 0xa9, 0x35, 0x4f, 0x47, 0x7b, 0x47, 0xe5, 0x5d, 0xdd, 0x1f, 0x5f, 0xa3, 0x1f, 0xfd, 0xa7, 0x9e, 0x7a, 0x2a, 0xd1, 0xf4, 0xb3, 0x67, 0xcf, 0x1e, 0x70, 0x5f, 0x77, 0x3d, 0x84, 0xad, 0x8f, 0x24, 0xeb, 0x24, 0x62, 0xdd, 0x0c, 0xb9, 0xe5, 0xd7, 0x7d, 0x5f, 0x59, 0x3d, 0x2f, 0x00, 0x58, 0x0b, 0x00, 0x25, 0x7f, 0xc7, 0xaa, 0x00, 0xaa, 0x3b, 0xed, 0xb4, 0xd3, 0xd4, 0x89, 0x13, 0x27, 0x58, 0x11, 0x00, 0x1a, 0x42, 0x13, 0xab, 0x00, 0x88, 0x77, 0xe7, 0x9d, 0x77, 0xaa, 0x65, 0xcb, 0x96, 0x59, 0x79, 0xae, 0x4b, 0x2f, 0xbd, 0x54, 0xbd, 0xf2, 0xca, 0x2b, 0xea, 0x92, 0x4b, 0x2e, 0x61, 0xc5, 0x02, 0x20, 0x00, 0x00, 0xf5, 0x48, 0x8a, 0xf5, 0x8a, 0x15, 0x2b, 0xd4, 0xc2, 0x85, 0x0b, 0xd5, 0xe8, 0xd1, 0xa3, 0xad, 0x3d, 0xef, 0xad, 0xb7, 0xde, 0xaa, 0xde, 0x78, 0xe3, 0x0d, 0xf5, 0xec, 0xb3, 0xcf, 0xaa, 0x33, 0xce, 0x38, 0x83, 0x15, 0x0d, 0x80, 0x00, 0x80, 0xc6, 0x70, 0xd1, 0x45, 0x17, 0xa9, 0xf3, 0xce, 0x3b, 0xcf, 0x78, 0xfe, 0x96, 0x96, 0x16, 0x35, 0x6a, 0xd4, 0x28, 0xe3, 0xf9, 0xcf, 0xff, 0xd1, 0xf9, 0xea, 0xec, 0xb3, 0xcf, 0x36, 0x9e, 0xff, 0xcc, 0x33, 0xcf, 0x54, 0x5d, 0x5d, 0x5d, 0xaa, 0xbb, 0xbb, 0x5b, 0x8d, 0x1f, 0x3f, 0x3e, 0x93, 0x75, 0x24, 0x87, 0x14, 0xa6, 0x4d, 0x9b, 0xa6, 0xde, 0x7d, 0xf7, 0x5d, 0xf5, 0xd0, 0x43, 0x0f, 0x95, 0xef, 0x03, 0x00, 0x01, 0x00, 0x85, 0xf6, 0xcc, 0x33, 0xcf, 0xa8, 0x99, 0x33, 0x67, 0x1a, 0xcf, 0x3f, 0x71, 0xe2, 0xc4, 0xf2, 0x5e, 0xb2, 0xa9, 0xe9, 0xff, 0x31, 0x5d, 0x4d, 0xfb, 0xc5, 0xb4, 0x42, 0x14, 0x65, 0x3f, 0x6c, 0x48, 0x8b, 0xc0, 0x8d, 0x37, 0xde, 0xc8, 0xc6, 0x03, 0x80, 0x00, 0x80, 0x62, 0x92, 0xe2, 0x2d, 0xb7, 0x7b, 0xef, 0xbd, 0x57, 0x8d, 0x1b, 0x37, 0x2e, 0xf1, 0xfc, 0x17, 0x5f, 0x7c, 0x71, 0xf9, 0x76, 0xd9, 0x65, 0x97, 0xa9, 0x0b, 0x2e, 0xb8, 0x20, 0xf1, 0xfc, 0xd7, 0x5c, 0x73, 0x4d, 0xf9, 0x76, 0xcb, 0xcd, 0xb7, 0xa8, 0xcb, 0x2f, 0xbb, 0x3c, 0xd1, 0xbc, 0xd2, 0xc9, 0xef, 0xe0, 0xc1, 0x83, 0xaa, 0xaf, 0xaf, 0x2f, 0xf7, 0xf5, 0x76, 0xf8, 0xf0, 0xe1, 0xf2, 0x0d, 0x00, 0x08, 0x00, 0x28, 0x1c, 0xd9, 0x63, 0xae, 0xdc, 0xf3, 0x7f, 0xf2, 0xc9, 0x27, 0x13, 0xcd, 0xef, 0x38, 0xce, 0x80, 0x3d, 0xff, 0x5b, 0x6e, 0xb9, 0x25, 0xd9, 0x06, 0xdd, 0xd4, 0x34, 0x60, 0xcf, 0x5f, 0xf6, 0xe2, 0x93, 0x5a, 0xbe, 0x7c, 0xb9, 0xba, 0xfe, 0xfa, 0xeb, 0xd5, 0xdc, 0xb9, 0x73, 0xd5, 0xb1, 0x63, 0xc7, 0x32, 0x5f, 0x67, 0x5f, 0x7e, 0xf9, 0xa5, 0x7a, 0xf4, 0xd1, 0x47, 0xd5, 0x5d, 0x77, 0xdd, 0xa5, 0x3e, 0xf8, 0xe0, 0x03, 0x36, 0x22, 0x00, 0x04, 0x00, 0x14, 0xcf, 0x83, 0x0f, 0x3e, 0x38, 0xa0, 0x77, 0xbb, 0xb4, 0x00, 0x48, 0x4b, 0x80, 0xae, 0x2b, 0xaf, 0xbc, 0x52, 0x9d, 0x73, 0xce, 0x39, 0xfd, 0xf7, 0xa5, 0x05, 0x40, 0x5a, 0x02, 0x74, 0xdd, 0xf9, 0xcf, 0x77, 0xaa, 0xd1, 0xff, 0xf0, 0x43, 0x67, 0x3d, 0x69, 0x01, 0x90, 0x96, 0x00, 0x93, 0xbd, 0x71, 0x69, 0x96, 0xbf, 0xf9, 0xe6, 0x9b, 0xd5, 0xaa, 0x55, 0xab, 0x32, 0x59, 0x57, 0xd2, 0xca, 0x20, 0x21, 0x43, 0x9a, 0xfd, 0xa5, 0xa3, 0x21, 0x00, 0x10, 0x00, 0x50, 0x48, 0x72, 0x2c, 0xbb, 0xbd, 0xbd, 0x7d, 0xd0, 0xdf, 0xa5, 0x45, 0x60, 0xe4, 0xc8, 0x91, 0xb1, 0xf3, 0x0f, 0x1f, 0x3e, 0xbc, 0x5c, 0x70, 0x83, 0xa4, 0x45, 0x60, 0xd8, 0xb0, 0x61, 0xb1, 0xf3, 0x4b, 0xa7, 0xc1, 0x9f, 0x3f, 0xf8, 0xf3, 0x41, 0x7f, 0x97, 0x16, 0x81, 0x11, 0xc3, 0x47, 0x18, 0xbd, 0xa7, 0xdd, 0xbb, 0x77, 0x97, 0xfb, 0x04, 0xdc, 0x7f, 0xff, 0xfd, 0xea, 0xd3, 0x4f, 0x3f, 0xb5, 0xb6, 0xae, 0x24, 0x54, 0x48, 0xe1, 0x97, 0x90, 0x41, 0xb3, 0x3f, 0x80, 0x5a, 0x68, 0xae, 0x97, 0x05, 0xa9, 0x1c, 0xe1, 0x4f, 0x57, 0x70, 0x44, 0x38, 0x1d, 0xc1, 0x51, 0xe0, 0x34, 0xb9, 0x6c, 0x2a, 0xf1, 0xa4, 0xf8, 0x4b, 0x08, 0x08, 0x92, 0xb3, 0x01, 0x1e, 0x7b, 0xec, 0x31, 0x19, 0xf9, 0xb1, 0xea, 0xfc, 0x52, 0xfc, 0x25, 0x04, 0x84, 0x15, 0x76, 0x69, 0x92, 0x5f, 0xb7, 0x6e, 0x5d, 0xd5, 0xf9, 0xa5, 0xf8, 0x87, 0x9d, 0x39, 0x20, 0x67, 0x03, 0xdc, 0x77, 0xdf, 0x7d, 0x6a, 0xd1, 0xcb, 0x8b, 0x8c, 0xdf, 0xdb, 0xfa, 0xf5, 0xeb, 0xcb, 0x37, 0x1b, 0x76, 0xec, 0xd8, 0x51, 0x0e, 0x15, 0x00, 0x30, 0xe4, 0x03, 0x80, 0xc9, 0x38, 0xe7, 0xfe, 0x58, 0xee, 0x59, 0xcf, 0x93, 0x74, 0x6c, 0xff, 0xa1, 0x4a, 0x8e, 0xfd, 0x7f, 0xf4, 0xd1, 0x47, 0xea, 0xf1, 0xc7, 0x1f, 0x0f, 0x7d, 0x3c, 0xee, 0x58, 0xba, 0x1c, 0xfb, 0x97, 0x63, 0xe1, 0xaf, 0xbf, 0xfe, 0x7a, 0xe8, 0xe3, 0x71, 0x23, 0xf0, 0xc9, 0xb1, 0xff, 0xcf, 0x3e, 0xfb, 0x4c, 0x3d, 0xf7, 0xfc, 0x73, 0xa1, 0x8f, 0x1f, 0x3f, 0x76, 0x9c, 0x0f, 0x09, 0x00, 0xea, 0xb1, 0x05, 0x00, 0xc5, 0x26, 0x05, 0x5a, 0x46, 0xb7, 0x33, 0xe5, 0xba, 0xae, 0xfa, 0xf0, 0xc3, 0x0f, 0x8d, 0xe7, 0x3f, 0x79, 0xf2, 0xa4, 0xfa, 0x4b, 0xf7, 0x5f, 0x8c, 0xe6, 0xcd, 0x6a, 0xac, 0x7d, 0xc6, 0xf0, 0x07, 0x40, 0x00, 0x30, 0x10, 0x75, 0x35, 0xb5, 0xa8, 0xd6, 0x82, 0x8d, 0x1b, 0x37, 0x0e, 0xaa, 0x29, 0x51, 0x3b, 0x9b, 0x81, 0x56, 0x81, 0xf2, 0xbf, 0x77, 0xdf, 0x73, 0xf7, 0x80, 0x89, 0x3a, 0xda, 0x3b, 0x22, 0xe7, 0xaf, 0xbc, 0xf8, 0xcc, 0x9f, 0xff, 0xe7, 0xcf, 0x6c, 0x45, 0x05, 0x96, 0xd5, 0x55, 0xf6, 0xb8, 0x7a, 0x1f, 0x00, 0x02, 0x80, 0x61, 0xf1, 0xaf, 0x72, 0x25,
		0x35, 0x37, 0xea, 0xc7, 0xd5, 0xbf, 0xaa, 0xdc, 0x84, 0x09, 0x13, 0xdc, 0xa8, 0x2b, 0xcc, 0x79, 0x8f, 0x39, 0xde, 0xff, 0x87, 0x4e, 0x23, 0xc5, 0x3f, 0xea, 0x0a, 0x73, 0xf2, 0x58, 0xe9, 0xe6, 0x24, 0xbd, 0x02, 0x1d, 0x00, 0x00, 0x04, 0x00, 0xf3, 0xe2, 0xef, 0x5f, 0x62, 0x35, 0x32, 0x04, 0x54, 0x2b, 0xfe, 0x7e, 0x48, 0xa8, 0x0c, 0x01, 0x49, 0x8a, 0xbf, 0x90, 0xc7, 0x08, 0x01, 0x8d, 0x63, 0xe3, 0xc6, 0x8d, 0x56, 0x3b, 0x78, 0xfa, 0xfd, 0x4c, 0xb2, 0x7a, 0x5e, 0x00, 0x68, 0xc8, 0x00, 0x10, 0x57, 0xfc, 0xe3, 0x42, 0x40, 0x5c, 0xf1, 0x0f, 0x86, 0x00, 0x15, 0x38, 0x1c, 0x10, 0x57, 0xfc, 0xc3, 0x42, 0x40, 0x95, 0xc9, 0x82, 0x05, 0x80, 0x1f, 0xf0, 0x3a, 0xa5, 0xb3, 0xcd, 0xe8, 0x08, 0xb6, 0x28, 0x65, 0xf5, 0xbc, 0x00, 0x60, 0x43, 0xdd, 0x8c, 0x03, 0xa0, 0x5b, 0xfc, 0x2b, 0x43, 0x40, 0xa0, 0x9f, 0x80, 0x9b, 0xe4, 0x07, 0xd7, 0x9b, 0xd6, 0x4d, 0x5a, 0xfc, 0x2b, 0x43, 0x80, 0x8a, 0xee, 0x67, 0xe0, 0x6a, 0xfe, 0x0d, 0x05, 0x22, 0x67, 0x2a, 0x00, 0x00, 0x2d, 0x00, 0xd0, 0xdd, 0xf3, 0x0f, 0x3e, 0xd6, 0x70, 0x55, 0x24, 0x6d, 0x6f, 0xf7, 0xb4, 0x7b, 0xb8, 0x86, 0x63, 0x3b, 0x24, 0x22, 0xa3, 0x1b, 0x8e, 0x1d, 0x3b, 0x36, 0xd5, 0x99, 0x0e, 0xbe, 0x73, 0xcf, 0x3d, 0xb7, 0xff, 0x72, 0xc0, 0x5f, 0x7f, 0xfd, 0x35, 0xdf, 0x18, 0x00, 0x04, 0x80, 0xa1, 0xba, 0x63, 0x59, 0x2a, 0xa0, 0xda, 0xad, 0x1f, 0x5e, 0xb1, 0xed, 0x0f, 0x11, 0x3d, 0x3d, 0x3d, 0x8e, 0xee, 0xa1, 0x0f, 0xbf, 0xd8, 0xca, 0x3c, 0xfe, 0xd9, 0x0f, 0xf2, 0x5c, 0x49, 0x5a, 0x3f, 0xbc, 0x62, 0xdb, 0xff, 0xfa, 0x69, 0x7b, 0xbb, 0xa7, 0x3d, 0xb6, 0x9d, 0xf5, 0xb1, 0x71, 0x29, 0xd6, 0x93, 0x26, 0x4d, 0x52, 0xa3, 0x47, 0x8f, 0x2e, 0x5f, 0x24, 0xc8, 0x96, 0xd6, 0xd6, 0xd6, 0xf2, 0x25, 0x93, 0xdf, 0x7f, 0xff, 0x7d, 0xb5, 0x61, 0xc3, 0x06, 0x75, 0xf4, 0xe8, 0x51, 0xbe, 0x09, 0x00, 0x72, 0xc5, 0x50, 0xc0, 0x75, 0xa0, 0x54, 0xfc, 0x1d, 0x9d, 0xbd, 0x68, 0x99, 0x46, 0xa6, 0x0d, 0xfe, 0x5d, 0x3a, 0x34, 0xea, 0xec, 0x45, 0xcb, 0x34, 0x11, 0x9d, 0x1f, 0x1d, 0x9d, 0xbd, 0xe8, 0x60, 0xf1, 0x6f, 0x64, 0x32, 0x22, 0xe1, 0x1d, 0x77, 0xdc, 0x51, 0x1e, 0xb1, 0x4f, 0x8a, 0x7f, 0x26, 0xc9, 0xcf, 0x71, 0xd4, 0x98, 0x31, 0x63, 0xd4, 0x23, 0x8f, 0x3c, 0xa2, 0xae, 0xba, 0xea, 0x2a, 0x0e, 0x31, 0x00, 0xa0, 0x05, 0x60, 0x28, 0x29, 0xed, 0x41, 0x97, 0xfb, 0x33, 0x78, 0x21, 0x20, 0xb2, 0x25, 0x20, 0xaa, 0xf8, 0xcb, 0xfc, 0x32, 0x9e, 0xbc, 0x17, 0x02, 0xaa, 0x9d, 0xfe, 0x18, 0x5a, 0xfc, 0xbd, 0x0e, 0x8d, 0xb1, 0x2d, 0x01, 0x51, 0xc5, 0x3f, 0x6a, 0xbc, 0x06, 0x8d, 0xf7, 0x9d, 0xaa, 0xb7, 0x7c, 0xda, 0xde, 0xf6, 0x51, 0x2d, 0x07, 0x52, 0x84, 0xaf, 0xbe, 0xfa, 0x6a, 0x75, 0xd3, 0x4d, 0x37, 0xa9, 0xd3, 0x4f, 0x3f, 0x3d, 0xd7, 0xb0, 0x21, 0x61, 0xa0, 0xbb, 0xbb, 0x5b, 0x7d, 0xfe, 0xf9, 0xe7, 0x7c, 0x31, 0x00, 0x10, 0x00, 0x0a, 0x48, 0x0a, 0x8b, 0xd6, 0x20, 0x44, 0x11, 0x2d, 0x01, 0x83, 0x42, 0x40, 0xb0, 0xf8, 0x4b, 0xd1, 0x0f, 0x13, 0x15, 0x02, 0x82, 0xc5, 0x3f, 0x38, 0x7f, 0x5c, 0x08, 0x08, 0x16, 0x7f, 0x79, 0xbc, 0x72, 0x00, 0xa4, 0x24, 0x9d, 0x37, 0xfd, 0xf7, 0x13, 0x58, 0xee, 0x44, 0xf3, 0x07, 0x5b, 0x3b, 0x92, 0x9e, 0x8e, 0x59, 0xad, 0xb5, 0x43, 0x46, 0x24, 0x94, 0xe6, 0xf8, 0xe3, 0xc7, 0x8f, 0xe7, 0x16, 0x00, 0x7c, 0x32, 0x5c, 0xf2, 0xf7, 0xdf, 0x7f, 0xcf, 0x37, 0x08, 0xc0, 0xd0, 0x0a, 0x00, 0xde, 0x1e, 0x61, 0xa2, 0x63, 0xe1, 0x81, 0xe3, 0xcf, 0x89, 0x8f, 0x85, 0x07, 0x0a, 0x72, 0xaa, 0x63, 0xe1, 0x1a, 0x21, 0x20, 0xb2, 0xf8, 0x7f, 0xf1, 0xc5, 0x17, 0xfe, 0xde, 0x74, 0x79, 0x3a, 0x09, 0x01, 0xc1, 0x79, 0xfd, 0xa2, 0x19, 0x56, 0xfc, 0xfd, 0x2b, 0xf0, 0xc9, 0xfc, 0x7e, 0x9f, 0x80, 0xca, 0xc7, 0xe5, 0x6f, 0x67, 0x9d, 0x75, 0x56, 0xd5, 0xf0, 0x10, 0x0c, 0x01, 0x51, 0xcb, 0x3e, 0x14, 0xc6, 0x3e, 0xf8, 0xf8, 0xe3, 0x8f, 0xcb, 0x57, 0xfe, 0xbb, 0xee, 0xba, 0xeb, 0xd4, 0xb5, 0xd7, 0x5e, 0x5b, 0xbe, 0xce, 0x41, 0x96, 0x0e, 0x1d, 0x3a, 0xa4, 0xde, 0x7c, 0xf3, 0x4d, 0xf5, 0xc9, 0x27, 0x9f, 0xf0, 0x8b, 0x04, 0x20, 0xf7, 0x00, 0x70, 0xac, 0x48, 0x21, 0x20, 0xa4, 0xf8, 0x57, 0xdd, 0x03, 0x0e, 0x2b, 0xfe, 0x11, 0xc7, 0xcd, 0xb5, 0x42, 0x80, 0xe6, 0xb1, 0x70, 0xc7, 0xe0, 0xfd, 0x1b, 0xcf, 0x5b, 0x6d, 0xfe, 0x8a, 0x0e, 0x7f, 0x83, 0x44, 0x0c, 0x65, 0xec, 0x24, 0x9c, 0xbe, 0xe1, 0xc8, 0x9e, 0xb8, 0x74, 0xce, 0xdb, 0xbe, 0x7d, 0x7b, 0xb9, 0xc7, 0xbe, 0x9c, 0x05, 0x60, 0x9b, 0xb4, 0x32, 0x6c, 0xde, 0xbc, 0x59, 0xbd, 0xf3, 0xce, 0x3b, 0xec, 0xf9, 0x03, 0xa8, 0x4d, 0x00, 0xe8, 0xec, 0xec, 0x1c, 0x5d, 0x2f, 0x0b, 0x14, 0x17, 0x02, 0xa2, 0x8a, 0xbf, 0x6e, 0x08, 0xc8, 0xea, 0x58, 0x38, 0x1a, 0x53, 0x6f, 0x6f, 0xaf, 0x5a, 0xb1, 0x62, 0x85, 0xba, 0xf0, 0xc2, 0x0b, 0xd5, 0xb8, 0x71, 0xe3, 0xac, 0x3d, 0xaf, 0xb4, 0x30, 0xac, 0x59, 0xb3, 0xc6, 0xea, 0x99, 0x05, 0x00, 0x90, 0x38, 0x00, 0x74, 0x74, 0x74, 0x7c, 0x5a, 0x8b, 0x17, 0x2f, 0x05, 0x8f, 0x4b, 0xaa, 0x85, 0x80, 0x2a, 0x8f, 0x45, 0x16, 0x77, 0x7f, 0x0f, 0x36, 0xd8, 0x0c, 0x5e, 0xb9, 0x77, 0x1b, 0xd5, 0x63, 0x3e, 0xa6, 0x19, 0x7c, 0xd0, 0xde, 0x71, 0xf0, 0x58, 0x38, 0x1a, 0xd7, 0x9e, 0x3d, 0x7b, 0xca, 0x37, 0x1b, 0xbe, 0xfa, 0xea, 0xab, 0x72, 0xa8, 0x00, 0x80, 0x9a, 0x07, 0x80, 0x7a, 0x94, 0xf4, 0xfc, 0xf2, 0x90, 0x66, 0xee, 0x44, 0xf3, 0x87, 0x14, 0x72, 0xc7, 0x60, 0x1e, 0x00, 0x00, 0x08, 0x00, 0x40, 0x11, 0x64, 0x35, 0xd6, 0x3e, 0x63, 0xf8, 0x03, 0x20, 0x00, 0xc0, 0x58, 0xd2, 0xf3, 0xec, 0xa5, 0xe5, 0x24, 0xe9, 0xb9, 0xf1, 0x72, 0x4e, 0xbc, 0xc9, 0x3c, 0x95, 0xf7, 0xa5, 0xa7, 0xfc, 0xcc, 0x99, 0x33, 0xd5, 0xc8, 0x91, 0x23, 0x43, 0xa7, 0x97, 0x63, 0xe9, 0x9d, 0x9d, 0xd1, 0x9d, 0x2b, 0xe5, 0xfc, 0x7b, 0xe9, 0x6c, 0x37, 0x6c, 0xd8, 0xb0, 0xd0, 0xc7, 0xfb, 0xfa, 0xfa, 0xd4, 0xba, 0x75, 0xeb, 0x22, 0xe7, 0x6f, 0x6a, 0x6a, 0x52, 0xd3, 0x7e, 0x31, 0x4d, 0x8d, 0x18, 0x3e, 0x22, 0xf4, 0xf1, 0x43, 0x7f, 0x3b, 0xa4, 0x16, 0xbd, 0xbc, 0x28, 0xf6, 0x7d, 0xd8, 0xc2, 0xd5, 0xfb, 0x00, 0x14, 0x22, 0x00, 0x44, 0x1d, 0x8b, 0x47, 0x7d, 0x58, 0xb8, 0x70, 0xa1, 0xd6, 0x74, 0x32, 0x6a, 0x9d, 0x2f, 0xe1, 0xe9, 0x90, 0x65, 0x93, 0x27, 0x4f, 0xd6, 0x9a, 0x67, 0xf9, 0xf2, 0xe5, 0x83, 0xfe, 0x76, 0xe2, 0xc4, 0x09, 0xf5, 0xcd, 0x37, 0xdf, 0xa8, 0xb6, 0xb6, 0xb6, 0xd0, 0x79, 0xfc, 0x53, 0x15, 0xa3, 0xc8, 0xf9, 0xf7, 0x47, 0x8e, 0x1c, 0x89, 0xec, 0x68, 0xb7, 0x7a, 0xf5, 0xea, 0xaa,
		0xf3, 0x9f, 0x3c, 0x79, 0x52, 0x1d, 0x38, 0x70, 0x40, 0xfd, 0xf4, 0xdf, 0x7e, 0x1a, 0xfa, 0xf8, 0x0b, 0xbf, 0x7b, 0x81, 0x0d, 0x09, 0x00, 0x2a, 0x03, 0xc0, 0x8c, 0x19, 0x33, 0xd8, 0x53, 0x81, 0x15, 0xf3, 0xe6, 0xcd, 0x53, 0x0f, 0x3c, 0xf0, 0x40, 0x79, 0x8c, 0xfb, 0x4a, 0x3d, 0x3d, 0x3d, 0x6a, 0xc9, 0x92, 0x25, 0xb1, 0xf3, 0x6f, 0xd9, 0xb2, 0x45, 0x5d, 0x71, 0xc5, 0x15, 0xaa, 0xa5, 0xa5, 0x65, 0xc0, 0xdf, 0xf7, 0xef, 0xdf, 0xaf, 0xb6, 0x6d, 0xdb, 0x16, 0x3b, 0xff, 0x6b, 0x7f, 0x7a, 0x4d, 0xdd, 0x7e, 0xfb, 0xed, 0xea, 0xfc, 0x1f, 0x9d, 0x3f, 0xe0, 0xef, 0xbb, 0x76, 0xed, 0x52, 0xab, 0x5e, 0x5f, 0x15, 0x3a, 0x8f, 0xe9, 0x48, 0x82, 0x71, 0x7b, 0xfe, 0x59, 0x3d, 0x2f, 0x00, 0x58, 0x6d, 0x01, 0x00, 0x6c, 0x90, 0x91, 0xec, 0x66, 0xcd, 0x9a, 0xa5, 0x16, 0x2f, 0x5e, 0x3c, 0xe0, 0xef, 0x1d, 0x1d, 0x1d, 0xe5, 0x16, 0x82, 0x38, 0x32, 0x8d, 0x9c, 0x1a, 0x37, 0x65, 0xca, 0x94, 0x01, 0x7f, 0x97, 0xe1, 0x71, 0xa5, 0x85, 0x20, 0x8e, 0x9c, 0x57, 0xbf, 0xe0, 0xc5, 0x05, 0xea, 0xe9, 0x59, 0x4f, 0x0f, 0x0c, 0x26, 0xf3, 0xe7, 0x95, 0x5b, 0x08, 0xa2, 0xd8, 0x1a, 0xdc, 0x28, 0x38, 0xc2, 0x60, 0x56, 0xcf, 0x0b, 0x00, 0x75, 0x1d, 0x00, 0x4c, 0xc7, 0x88, 0xaf, 0x22, 0x74, 0x1c, 0xfc, 0x2c, 0xf6, 0xb6, 0xc2, 0x5e, 0xcb, 0x3f, 0xcb, 0x20, 0xcf, 0xd7, 0x2a, 0x22, 0x29, 0xe0, 0x9b, 0x36, 0x6d, 0x52, 0xe3, 0xc7, 0x8f, 0x2f, 0xdf, 0x5f, 0xb9, 0x72, 0x65, 0x79, 0xb0, 0x1b, 0x5d, 0x3b, 0x77, 0xee, 0x54, 0x7b, 0xf7, 0xee, 0xed, 0xbf, 0x00, 0xcf, 0x8e, 0x1d, 0x3b, 0xd4, 0xbe, 0x7d, 0xfb, 0xb4, 0xe7, 0x97, 0x56, 0x84, 0xed, 0x1f, 0x6f, 0x57, 0x3f, 0xfe, 0xc7, 0x1f, 0x97, 0xef, 0x6f, 0x78, 0x6b, 0x83, 0xea, 0xf9, 0xa4, 0xc7, 0xca, 0x7b, 0x93, 0x7e, 0x06, 0xd5, 0x82, 0x04, 0x00, 0x10, 0x00, 0x3c, 0x49, 0xc7, 0x88, 0xaf, 0xc6, 0x1b, 0x1e, 0xb7, 0xda, 0x00, 0x40, 0xd6, 0x5e, 0xcb, 0x1b, 0x43, 0xc0, 0xc9, 0x7a, 0x8f, 0xd1, 0xdb, 0xbb, 0xab, 0xfa, 0x5a, 0x45, 0x24, 0x9d, 0x01, 0xe5, 0x98, 0xbd, 0x14, 0xcb, 0x39, 0x73, 0xe6, 0x24, 0x9e, 0x7f, 0xed, 0xda, 0xb5, 0xea, 0xe1, 0x87, 0x1f, 0x2e, 0xcf, 0x2f, 0xa3, 0xf1, 0x25, 0x0e, 0x9f, 0x2f, 0x2e, 0x50, 0x73, 0xff, 0x6b, 0x6e, 0x79, 0xfe, 0x60, 0x6b, 0x84, 0x29, 0x09, 0x34, 0x3f, 0xf9, 0xd7, 0x9f, 0xa8, 0xf6, 0x19, 0xed, 0xa9, 0x9f, 0x4b, 0x06, 0x15, 0x9a, 0xf6, 0xf0, 0x34, 0xf5, 0xfb, 0x97, 0x7e, 0xaf, 0xf6, 0xfe, 0xdf, 0x5e, 0x7e, 0x85, 0x00, 0xd4, 0x44, 0x61, 0x2e, 0x07, 0xec, 0x85, 0x09, 0x37, 0x8f, 0xd7, 0xf2, 0xc2, 0x44, 0x2e, 0xaf, 0xe5, 0x85, 0x09, 0xb7, 0x91, 0x36, 0x2a, 0xff, 0x98, 0xbf, 0xf4, 0x09, 0xd8, 0xbd, 0x7b, 0x77, 0xe2, 0xf9, 0xfd, 0x63, 0xfe, 0xb2, 0x37, 0x2f, 0x67, 0x0f, 0x24, 0xe5, 0x1f, 0xf3, 0x97, 0x3e, 0x01, 0x7f, 0xfd, 0xe2, 0xaf, 0xa9, 0x8b, 0x75, 0xd7, 0x7f, 0x76, 0xa9, 0xdf, 0x74, 0xfc, 0x46, 0x9d, 0xf7, 0xf7, 0xe7, 0x59, 0x5b, 0x47, 0x72, 0xe5, 0xbf, 0xe7, 0xff, 0xfb, 0x79, 0xf5, 0xab, 0xb6, 0x5f, 0x45, 0x9e, 0x39, 0x01, 0x00, 0x04, 0x00, 0x42, 0x40, 0xe1, 0xc8, 0x25, 0x8a, 0xe7, 0xce, 0x9d, 0x6b, 0x3c, 0xff, 0xfa, 0xf5, 0xeb, 0xd5, 0xdb, 0x6f, 0xbf, 0x6d, 0x3c, 0xff, 0xe2, 0x25, 0x8b, 0xd5, 0xab, 0xaf, 0xbe, 0x6a, 0x3c, 0xff, 0xa8, 0x51, 0xa3, 0xd4, 0xaf, 0x1f, 0xf9, 0xb5, 0x7a, 0x6e, 0xee, 0x73, 0xfd, 0x87, 0x13, 0xac, 0x7f, 0xf9, 0x9a, 0x9a, 0xd4, 0x3d, 0xff, 0x72, 0x8f, 0x7a, 0xe9, 0xc5, 0x97, 0xd4, 0xdd, 0x77, 0xdd, 0x5d, 0xbe, 0x0f, 0x00, 0x45, 0x09, 0x00, 0xad, 0x84, 0x00, 0x42, 0x40, 0x98, 0x6f, 0xbf, 0xfd, 0x56, 0x1d, 0x3e, 0x7c, 0xd8, 0x78, 0x7e, 0x39, 0xef, 0x3f, 0xcd, 0x05, 0x72, 0xe4, 0x0a, 0x7b, 0xdf, 0xf5, 0x7d, 0x57, 0x88, 0xa2, 0xec, 0x87, 0x0d, 0x69, 0x11, 0xb8, 0xe2, 0x9f, 0xae, 0xe0, 0x57, 0x09, 0x40, 0xdd, 0x07, 0x80, 0xa5, 0xa5, 0xdb, 0xce, 0xd2, 0xed, 0x09, 0x42, 0x00, 0x21, 0xa0, 0x51, 0x48, 0xbf, 0x01, 0x09, 0x2e, 0xb5, 0xb8, 0x3a, 0x5f, 0xdf, 0x77, 0x7d, 0x46, 0xa1, 0x05, 0x00, 0x4c, 0x98, 0x76, 0x02, 0x94, 0xe2, 0xef, 0x9f, 0xab, 0xd5, 0xe5, 0xfd, 0x3b, 0x87, 0xd5, 0x89, 0x46, 0xf0, 0xc6, 0x9b, 0x6f, 0x94, 0xcf, 0x64, 0x90, 0xd3, 0x11, 0x7f, 0x76, 0xef, 0xcf, 0x54, 0x73, 0x73, 0xb6, 0x67, 0xcb, 0xca, 0x00, 0x4a, 0x0b, 0xff, 0xb0, 0x50, 0xad, 0x5b, 0xbf, 0x8e, 0x95, 0x0f, 0xa0, 0xae, 0x03, 0x40, 0x65, 0xf1, 0xf7, 0x4d, 0x21, 0x00, 0x64, 0xa7, 0x72, 0x84, 0x3f, 0x5d, 0x26, 0xe3, 0xd0, 0x87, 0x8d, 0xf0, 0xa7, 0x43, 0x2e, 0xd1, 0x9c, 0x46, 0xda, 0x31, 0xf3, 0xb3, 0x38, 0x4f, 0x5e, 0xf6, 0xc4, 0xff, 0xb8, 0xf8, 0x8f, 0xe5, 0xd3, 0x1a, 0x65, 0x88, 0x61, 0xff, 0xb4, 0x46, 0x9b, 0xa4, 0x95, 0x41, 0x3a, 0x2a, 0x2e, 0x5b, 0xb6, 0x8c, 0x3d, 0x7f, 0x00, 0x35, 0x0f, 0x00, 0x72, 0x4c, 0x5f, 0x4e, 0xae, 0x5f, 0x50, 0xba, 0xed, 0xd2, 0x2c, 0xfe, 0x32, 0xdd, 0x54, 0x56, 0x65, 0x36, 0x92, 0x5e, 0x15, 0x51, 0x98, 0x8c, 0x1a, 0x67, 0x3a, 0xd2, 0x9c, 0xc9, 0xf2, 0xd9, 0x78, 0x5d, 0x5b, 0xf3, 0xc7, 0x91, 0xb3, 0x08, 0x7e, 0xdb, 0xf9, 0x5b, 0x75, 0xd5, 0x95, 0x57, 0x45, 0x0e, 0x33, 0x6c, 0x42, 0x5a, 0x18, 0xe6, 0xbf, 0x38, 0xbf, 0x7c, 0x69, 0x60, 0x00, 0xa8, 0x75, 0x00, 0x90, 0xe2, 0xdf, 0xed, 0xfd, 0x2b, 0x45, 0x7e, 0x52, 0x20, 0x04, 0x44, 0x15, 0xff, 0x49, 0x11, 0x61, 0x21, 0x33, 0xde, 0x1e, 0x67, 0x2e, 0xe7, 0xce, 0x7b, 0x7b, 0xa7, 0xb9, 0xbc, 0x96, 0xb7, 0x27, 0xcb, 0x90, 0xaf, 0x75, 0xe8, 0x83, 0x6d, 0x1f, 0x94, 0x6f, 0x36, 0xec, 0xd9, 0xb3, 0xa7, 0x1c, 0x2a, 0x00, 0xa0, 0x96, 0x9a, 0x02, 0x05, 0xbe, 0x35, 0x24, 0x0c, 0x50, 0xfc, 0x29, 0xfe, 0x00, 0x80, 0x06, 0x6e, 0x01, 0x90, 0x42, 0x3e, 0x26, 0xa4, 0x45, 0x60, 0x2b, 0xc5, 0x9f, 0xe2, 0xdf, 0xc8, 0xb2, 0x1a, 0x6b, 0x9f, 0x31, 0xfc, 0x01, 0x14, 0x25, 0x00, 0x4c, 0x0d, 0xd9, 0xd3, 0x6f, 0x55, 0x83, 0xcf, 0xf5, 0xa7, 0xf8, 0x53, 0xfc, 0x1b, 0x46, 0x56, 0x7d, 0x08, 0xb8, 0x7a, 0x1f, 0x80, 0x22, 0x05, 0x80, 0xa8, 0x10, 0x60, 0x5c, 0xfc, 0xd3, 0xf6, 0x0e, 0x0f, 0x70, 0x34, 0x8a, 0x76, 0x2e, 0xaf, 0x65, 0x79, 0xcf, 0x8e, 0x42, 0x01, 0x00, 0xc8, 0x9d, 0x13, 0x71, 0x99, 0xd5, 0xba, 0x39, 0xe6, 0x8f, 0xea, 0x32, 0xb8, 0xea, 0x62, 0x22, 0xfe, 0x59, 0x00, 0x69, 0x97, 0xe3, 0xf2, 0xcb, 0x2f, 0xb7, 0xb2, 0xc7, 0x5d, 0x2f, 0xcb, 0x01, 0x00, 0x45, 0x6b, 0x01, 0x88, 0x6a, 0x09, 0xa0, 0xf8, 0xd7, 0xb1, 0x34, 0x57, 0x5d, 0x94, 0x56, 0x1a, 0xd3, 0xf9, 0x83, 0x2d, 0x3c, 0x69, 0x96, 0x43, 0xc6, 0x20, 0x30, 0xbd, 0xa2,
		0x63, 0xb0, 0xf5, 0x27, 0xed, 0x72, 0x98, 0x5e, 0xed, 0x91, 0x63, 0xfe, 0x00, 0x8a, 0xa4, 0xda, 0x50, 0xc0, 0x12, 0x02, 0x96, 0xa9, 0x53, 0x9d, 0x00, 0x75, 0x8a, 0xbf, 0xf4, 0x15, 0x18, 0xc3, 0x2a, 0x05, 0x00, 0xa0, 0xd8, 0x01, 0xc0, 0x0f, 0x01, 0x63, 0x35, 0xf7, 0xfc, 0xe5, 0x9a, 0x00, 0x72, 0xd6, 0xc0, 0xc4, 0x14, 0xcb, 0xe3, 0x6a, 0xdc, 0xb2, 0x9c, 0x1f, 0x00, 0x00, 0x02, 0x80, 0x81, 0x16, 0x75, 0xea, 0xd0, 0x41, 0x9a, 0x10, 0xe0, 0x54, 0xb9, 0xe5, 0x31, 0x3f, 0x00, 0x00, 0x04, 0x80, 0x1a, 0x85, 0x80, 0xca, 0x3d, 0x7a, 0x00, 0x00, 0x50, 0x80, 0x00, 0x60, 0x3b, 0x04, 0x00, 0x00, 0x00, 0xcb, 0xfa, 0xcf, 0x02, 0x70, 0x1c, 0x47, 0xb9, 0xae, 0xdb, 0xaa, 0x31, 0x4f, 0x6f, 0x69, 0xda, 0xde, 0x88, 0xd3, 0x07, 0xc3, 0x42, 0x80, 0x74, 0x20, 0xdc, 0x9a, 0x62, 0xcf, 0xdf, 0xff, 0x7f, 0xc7, 0x70, 0x7e, 0x65, 0x30, 0xff, 0x90, 0xf5, 0xf4, 0xd3, 0x4f, 0xab, 0x91, 0x23, 0x47, 0x86, 0x7f, 0xf0, 0xbd, 0xbd, 0xaa, 0xb3, 0xb3, 0x33, 0x97, 0xe5, 0xb8, 0xed, 0xb6, 0xdb, 0xd4, 0xb0, 0x61, 0xc3, 0x42, 0x1f, 0xeb, 0xeb, 0xeb, 0x53, 0xeb, 0xd6, 0xad, 0xcb, 0x65, 0x39, 0x7e, 0xf9, 0xef, 0xbf, 0x54, 0x23, 0x86, 0x8f, 0x08, 0x7d, 0xec, 0xd0, 0xdf, 0x0e, 0xa9, 0x45, 0x2f, 0x2f, 0x62, 0xa3, 0x01, 0x50, 0xec, 0x00, 0x50, 0x2a, 0xe8, 0x53, 0xbc, 0x82, 0x1d, 0x1b, 0x00, 0x4a, 0xd3, 0x5e, 0x2c, 0xff, 0xea, 0x4c, 0xab, 0x39, 0x5d, 0x54, 0xb1, 0x76, 0x0d, 0x0b, 0x37, 0xc5, 0xde, 0x90, 0x5c, 0x9b, 0xbe, 0xad, 0xad, 0x2d, 0xf4, 0xb1, 0xf6, 0xf6, 0xf6, 0xdc, 0x96, 0xe3, 0xc8, 0x91, 0x23, 0x6a, 0xdc, 0xb8, 0x71, 0xa1, 0x8f, 0xad, 0x5e, 0xbd, 0x3a, 0xb7, 0xe5, 0x38, 0x70, 0xe0, 0x40, 0xe4, 0x55, 0x00, 0x5f, 0xf8, 0xdd, 0x0b, 0x6c, 0x30, 0x00, 0x0a, 0xab, 0xa9, 0xa2, 0x05, 0x40, 0x4e, 0xf9, 0x5b, 0xa6, 0x31, 0xcf, 0x1c, 0x69, 0x01, 0xd0, 0x98, 0x8e, 0xb1, 0x03, 0x0a, 0x68, 0xde, 0xbc, 0x79, 0x6a, 0xf7, 0xee, 0xdd, 0x83, 0xfe, 0xde, 0xd3, 0xd3, 0xa3, 0x96, 0x2c, 0x59, 0x92, 0xdb, 0x72, 0x6c, 0xd9, 0xb2, 0xa5, 0xdc, 0xe2, 0x10, 0xb4, 0x7f, 0xff, 0x7e, 0xb5, 0x6d, 0xdb, 0xb6, 0xdc, 0x96, 0xe3, 0xb5, 0x3f, 0xbd, 0x56, 0xbe, 0x24, 0xf0, 0xa0, 0x8d, 0x7b, 0xd7, 0x2e, 0xb5, 0xea, 0xf5, 0x55, 0x6c, 0x30, 0x00, 0x8a, 0x1f, 0x00, 0xbc, 0x10, 0x30, 0x35, 0x26, 0x04, 0xb4, 0x97, 0xa6, 0x99, 0x93, 0x63, 0xf1, 0x67, 0x4f, 0x3e, 0x67, 0xc7, 0x8e, 0x1d, 0x53, 0xb3, 0x66, 0xcd, 0x1a, 0xf4, 0xf7, 0x8e, 0x8e, 0x0e, 0x75, 0xe2, 0xc4, 0x89, 0xdc, 0x96, 0x43, 0x5e, 0x6b, 0xcd, 0x9a, 0x35, 0x83, 0xfe, 0xde, 0xdd, 0xdd, 0xad, 0x34, 0x0e, 0x3f, 0x59, 0x73, 0xfc, 0xf8, 0x71, 0xb5, 0xe0, 0xc5, 0x05, 0x83, 0x83, 0xd2, 0xfc, 0x79, 0xea, 0xe4, 0xc9, 0x93, 0x6c, 0x30, 0x00, 0x1a, 0x23, 0x00, 0xc4, 0x84, 0x80, 0xbc, 0x8a, 0x7f, 0xda, 0x73, 0xf8, 0x19, 0x03, 0x20, 0x25, 0x29, 0xbc, 0x9b, 0x36, 0x6d, 0xea, 0xbf, 0xbf, 0x72, 0xe5, 0x4a, 0xb5, 0x79, 0xf3, 0xe6, 0xdc, 0x97, 0x63, 0xe7, 0xce, 0x9d, 0x6a, 0xef, 0xde, 0xbd, 0xfd, 0xf7, 0x77, 0xec, 0xd8, 0xa1, 0xf6, 0xed, 0xdb, 0x97, 0xfb, 0x72, 0x48, 0x6b, 0xc4, 0xf6, 0x8f, 0xb7, 0xf7, 0xdf, 0xdf, 0xf0, 0xd6, 0x06, 0xd5, 0xf3, 0x49, 0x0f, 0x1b, 0x0a, 0x80, 0xc6, 0x0a, 0x00, 0x11, 0x21, 0x40, 0xa7, 0xf8, 0xf7, 0x5a, 0x28, 0xfe, 0x8e, 0xc6, 0x2d, 0xcb, 0xf9, 0xe1, 0x99, 0x39, 0x73, 0x66, 0x79, 0x2f, 0x5c, 0x5a, 0x04, 0xe6, 0xcc, 0x99, 0x53, 0xb3, 0xe5, 0x58, 0xbb, 0x76, 0x6d, 0x79, 0x8f, 0x5f, 0x96, 0x65, 0xc3, 0x86, 0x0d, 0x35, 0x5b, 0x0e, 0x69, 0x05, 0x90, 0x3d, 0x7e, 0x69, 0x11, 0x58, 0xbc, 0x78, 0x31, 0x1b, 0x08, 0x80, 0xc2, 0x6b, 0x8e, 0xac, 0xa4, 0xa5, 0x10, 0x50, 0xfa, 0xe1, 0x95, 0x4e, 0x81, 0x5b, 0x35, 0xf7, 0xfc, 0xa5, 0x87, 0xd8, 0x1c, 0x65, 0xd6, 0xe9, 0x0f, 0x75, 0xc6, 0x3f, 0xe6, 0x7f, 0xf0, 0xe0, 0xc1, 0xd0, 0x3e, 0x01, 0x79, 0xf1, 0x8f, 0xf9, 0x1f, 0x3d, 0x7a, 0x34, 0xb4, 0x4f, 0x40, 0x5e, 0xfc, 0x63, 0xfe, 0xd2, 0x39, 0x31, 0xac, 0x4f, 0x00, 0x00, 0x14, 0x36, 0x00, 0x44, 0x1c, 0x57, 0x9d, 0x5a, 0xe5, 0xb1, 0xa8, 0x56, 0x00, 0x34, 0x88, 0x3c, 0x7b, 0xfd, 0x57, 0x93, 0x67, 0xaf, 0xff, 0x6a, 0xe8, 0xf5, 0x0f, 0x60, 0x48, 0xb4, 0x00, 0xd4, 0xa1, 0xd6, 0x90, 0xb0, 0x41, 0xe0, 0x00, 0x00, 0xc0, 0x40, 0x53, 0x41, 0x96, 0xb3, 0xab, 0x74, 0xdb, 0x19, 0x72, 0x9b, 0x52, 0xe3, 0xe5, 0xa2, 0x63, 0x21, 0x00, 0x80, 0x00, 0x50, 0x32, 0xdf, 0xbb, 0x45, 0x91, 0xcb, 0x05, 0xbf, 0xa7, 0x92, 0x5f, 0x36, 0x58, 0xce, 0xc3, 0x0a, 0x76, 0x2c, 0x6c, 0xf1, 0x6e, 0x49, 0xb5, 0x7a, 0xcb, 0x90, 0x76, 0x98, 0x62, 0xd3, 0x41, 0x8a, 0x00, 0x00, 0x68, 0xa8, 0x00, 0x20, 0x85, 0x7f, 0xba, 0x77, 0x9b, 0x1f, 0x51, 0xfc, 0xbb, 0x03, 0xff, 0xea, 0x92, 0xe2, 0xdf, 0x66, 0xb8, 0x5c, 0x2d, 0x81, 0xe2, 0xef, 0xbf, 0xf6, 0x52, 0xc3, 0x00, 0x41, 0xf1, 0x07, 0x00, 0x14, 0x5e, 0x73, 0x95, 0xbd, 0xe4, 0xa5, 0x5e, 0xd1, 0xd5, 0x19, 0xc7, 0xdf, 0x2f, 0xfe, 0x3e, 0xff, 0xff, 0xdb, 0x02, 0xc5, 0xbf, 0xa5, 0xa2, 0x28, 0xcb, 0xfd, 0xb1, 0x4a, 0xef, 0x94, 0xc1, 0xd6, 0x98, 0x96, 0x85, 0x28, 0x4f, 0x78, 0xb7, 0xa9, 0xde, 0xeb, 0x74, 0xab, 0x1f, 0xfa, 0x12, 0x98, 0x9e, 0xb1, 0x50, 0x59, 0xfc, 0xeb, 0x22, 0x08, 0xcc, 0x9e, 0x3d, 0xbb, 0xa6, 0xf3, 0xdb, 0x7a, 0x9e, 0x09, 0x13, 0x26, 0xd4, 0xc5, 0x72, 0x74, 0xb4, 0x77, 0xf0, 0xcb, 0x00, 0xa0, 0xe1, 0x39, 0x11, 0x3d, 0xfc, 0xfd, 0xeb, 0x02, 0x48, 0x81, 0xd4, 0xb9, 0x98, 0x4f, 0x30, 0x00, 0xf8, 0xa4, 0xe9, 0x7e, 0x59, 0xc4, 0xde, 0x76, 0xaf, 0x66, 0x00, 0x68, 0x0d, 0x29, 0xdc, 0x53, 0xbc, 0xfb, 0x6d, 0xde, 0x6b, 0xc4, 0x2d, 0x97, 0xdf, 0x61, 0xd0, 0x7f, 0x0e, 0xff, 0x94, 0xc5, 0xc2, 0x17, 0x7f, 0x00, 0x00, 0x4c, 0xc4, 0x1d, 0x02, 0xf0, 0xf7, 0xd4, 0xe3, 0x9a, 0xeb, 0xa3, 0x0a, 0xf1, 0xf4, 0xc0, 0x9e, 0x7f, 0x65, 0xf1, 0xd7, 0x19, 0x30, 0x28, 0x58, 0xfc, 0xdb, 0xbd, 0x9b, 0x1f, 0x4a, 0x74, 0xaf, 0x32, 0xd8, 0x42, 0xf1, 0x07, 0x00, 0x40, 0x3f, 0x00, 0xd8, 0x08, 0x01, 0x2a, 0xa2, 0xf8, 0x27, 0xbd, 0x44, 0x70, 0x65, 0xe1, 0xde, 0xe5, 0xb5, 0x1e, 0x24, 0x7d, 0x8e, 0x5e, 0x83, 0x79, 0xaa, 0x15, 0x7f, 0xce, 0x02, 0x00, 0x00, 0x34, 0x6c, 0x00, 0xb0, 0x19, 0x02, 0x74, 0x8b, 0x7f, 0xab, 0x77, 0xf3, 0x87, 0x16, 0x36, 0xdd, 0x6b, 0x0f, 0x7b, 0x1f, 0x4b, 0x55, 0xb2, 0x0e, 0x88, 0xd5, 0x8a, 0x3f, 0xad, 0x00, 0x00, 0x80, 0x42, 0x4a, 0x32, 0x10, 0x90, 0x14, 0xcf, 0x2e, 0xaf, 0x20, 0x57, 0x23, 0xc7, 0xfc, 0xa7, 0x47, 0x3c, 0xb6,
		0x46, 0xb3, 0xf8, 0x77, 0x7b, 0xff, 0xef, 0x1f, 0x26, 0xd0, 0x29, 0xfe, 0x61, 0xaf, 0xb9, 0x4b, 0xa5, 0xbb, 0x22, 0x21, 0xc5, 0x1f, 0x00, 0x30, 0xe4, 0x03, 0x80, 0x14, 0xee, 0xa9, 0x31, 0xd3, 0xf8, 0xa7, 0xd7, 0x45, 0x91, 0xce, 0x7b, 0xf3, 0xd5, 0xc0, 0x53, 0xfa, 0xba, 0xd4, 0x0f, 0xe7, 0xf9, 0x07, 0x8f, 0xf9, 0x4f, 0xd1, 0x2c, 0xfe, 0x7e, 0x38, 0x09, 0xf6, 0x35, 0x90, 0xe7, 0xbd, 0x38, 0xc3, 0xe2, 0x4f, 0x10, 0x00, 0x00, 0x14, 0x92, 0xee, 0x21, 0x80, 0xad, 0xde, 0xde, 0x78, 0x6f, 0x4c, 0xf1, 0x0f, 0xeb, 0xf0, 0x17, 0xb6, 0xa7, 0x3e, 0xbf, 0x62, 0x6f, 0xff, 0x09, 0x6f, 0xbe, 0x89, 0x6a, 0x70, 0x87, 0x3f, 0xdd, 0x66, 0xff, 0x5e, 0x2f, 0x9c, 0xd8, 0x1a, 0x1a, 0x98, 0xe2, 0x0f, 0x00, 0x18, 0xf2, 0x01, 0x20, 0x4d, 0xf1, 0x97, 0x79, 0x96, 0xc5, 0x84, 0x00, 0xa5, 0xc2, 0x7b, 0xfb, 0x27, 0x3d, 0xe6, 0xbf, 0xcb, 0x52, 0x00, 0xa0, 0xf8, 0x03, 0x00, 0x86, 0x7c, 0x00, 0xd0, 0x29, 0xfe, 0xca, 0x2b, 0xe6, 0x51, 0xa7, 0xfa, 0xc9, 0x9e, 0x79, 0xd4, 0x29, 0x82, 0x77, 0x85, 0xfc, 0x7d, 0x8e, 0x41, 0xf1, 0x0f, 0x06, 0x08, 0xd3, 0x20, 0x90, 0xb4, 0xf8, 0x73, 0x16, 0x00, 0x00, 0xa0, 0xa1, 0x02, 0xc0, 0x56, 0x6f, 0xcf, 0x5d, 0xa7, 0xf8, 0x8b, 0xb6, 0xc0, 0x74, 0xc1, 0xde, 0xfe, 0x61, 0x67, 0x07, 0xc8, 0xfd, 0xff, 0x0d, 0x79, 0xae, 0x29, 0x6a, 0xf0, 0x95, 0xff, 0x92, 0x14, 0xff, 0x76, 0x65, 0x76, 0x38, 0xc0, 0xa4, 0xf8, 0xd3, 0x0a, 0x00, 0x00, 0x28, 0xa4, 0xa8, 0x91, 0x00, 0x4d, 0xf8, 0x87, 0x01, 0x94, 0x8a, 0x3e, 0xd5, 0xcf, 0x1f, 0x99, 0x6f, 0x81, 0x17, 0x0a, 0xa4, 0x68, 0xef, 0x8c, 0x08, 0x20, 0x63, 0x35, 0x5f, 0xb7, 0xf2, 0xe2, 0x42, 0x95, 0x87, 0x0e, 0xc6, 0x54, 0x3c, 0x17, 0xc5, 0x1f, 0x00, 0x80, 0x8c, 0x02, 0x80, 0xaa, 0xd8, 0x0b, 0xaf, 0x76, 0xea, 0xdd, 0x14, 0x35, 0xb0, 0x5f, 0x80, 0xdc, 0x6f, 0x09, 0x09, 0x00, 0xba, 0x03, 0xf6, 0x48, 0xe7, 0xc1, 0xa5, 0xca, 0xec, 0xd0, 0x41, 0xda, 0xe2, 0x4f, 0x10, 0x00, 0x00, 0x10, 0x00, 0x6a, 0xa8, 0x55, 0xa5, 0x3b, 0xdf, 0x1f, 0x00, 0x80, 0x21, 0xa5, 0xa9, 0x41, 0xde, 0x07, 0xc5, 0x1f, 0x00, 0x00, 0x93, 0x00, 0xe0, 0x38, 0x4e, 0xd5, 0x9b, 0x3a, 0xd5, 0xd4, 0xfe, 0x5e, 0xdc, 0x74, 0x15, 0xd3, 0x03, 0x00, 0x80, 0x06, 0x68, 0x01, 0x90, 0xe3, 0xf4, 0x63, 0x5c, 0xd7, 0x6d, 0x61, 0xb5, 0x01, 0x00, 0x30, 0x74, 0x02, 0xc0, 0x00, 0xa5, 0x20, 0x30, 0xbd, 0x74, 0x7b, 0xcf, 0xbb, 0x75, 0x11, 0x0c, 0x00, 0x00, 0x28, 0x78, 0x00, 0x90, 0x62, 0x5e, 0xba, 0x4d, 0x0c, 0xfc, 0xd9, 0xef, 0xe1, 0xef, 0xb7, 0x02, 0xc8, 0xe9, 0x7c, 0x63, 0xbc, 0x5b, 0x79, 0x38, 0x5f, 0x42, 0x00, 0x00, 0x00, 0xc5, 0x6e, 0x01, 0x98, 0xe8, 0x15, 0xf4, 0x27, 0xbc, 0x40, 0x20, 0xff, 0x76, 0x79, 0x8f, 0x2d, 0xf5, 0xc2, 0x40, 0xf0, 0x5c, 0xff, 0x31, 0x2a, 0xfa, 0x2a, 0x80, 0x00, 0x00, 0xa0, 0xde, 0x03, 0x80, 0xe3, 0x38, 0x72, 0x9e, 0xbe, 0x0c, 0xd6, 0x23, 0x4d, 0xfb, 0x4b, 0x2b, 0x8a, 0xbf, 0x90, 0xbd, 0xfc, 0xee, 0x88, 0x10, 0x40, 0x0b, 0x00, 0x00, 0x00, 0x05, 0x6e, 0x01, 0x90, 0x10, 0x20, 0x23, 0xf5, 0xad, 0x51, 0xa7, 0x06, 0xea, 0x09, 0x8a, 0x0a, 0x01, 0xbd, 0xac, 0x52, 0x00, 0x00, 0x0a, 0x1c, 0x00, 0xa4, 0x93, 0x9f, 0x3a, 0x75, 0x28, 0x20, 0x8c, 0x0c, 0xb9, 0xbb, 0x2b, 0x10, 0x02, 0xd6, 0xa8, 0xf0, 0x8b, 0xfe, 0x00, 0x00, 0x80, 0x22, 0x04, 0x00, 0xaf, 0x33, 0xdf, 0x13, 0x55, 0x8a, 0xff, 0x82, 0x60, 0x4b, 0x80, 0xe3, 0x38, 0x93, 0x4a, 0x37, 0x5a, 0x00, 0x00, 0x00, 0x28, 0x80, 0xe6, 0x8a, 0xa2, 0xdf, 0xad, 0x7e, 0x38, 0x86, 0x3f, 0x26, 0xa6, 0xf8, 0x77, 0x57, 0x4c, 0x53, 0x0e, 0x01, 0xa5, 0xf9, 0xe5, 0x31, 0x3f, 0x00, 0x6c, 0x55, 0x8c, 0xce, 0x07, 0x00, 0x40, 0xfd, 0x07, 0x00, 0x75, 0xaa, 0x09, 0xdf, 0x0f, 0x00, 0x52, 0xbc, 0xa7, 0x68, 0x14, 0x7f, 0x55, 0x11, 0x02, 0xe6, 0x57, 0xdc, 0x97, 0x4e, 0x84, 0x53, 0x59, 0xbd, 0x00, 0x00, 0xd4, 0xa7, 0xfe, 0x8b, 0x01, 0x55, 0x0e, 0xdf, 0xeb, 0x8d, 0x01, 0xd0, 0xad, 0x59, 0xfc, 0xfd, 0x3d, 0xfe, 0xa9, 0x7e, 0x0b, 0x80, 0x1c, 0x0a, 0x68, 0x90, 0x8b, 0x0c, 0x01, 0x00, 0xd0, 0xf0, 0x2d, 0x00, 0x3f, 0xa4, 0x02, 0xc7, 0x59, 0x53, 0x2a, 0xe0, 0xd2, 0x0a, 0xd0, 0xaa, 0x59, 0xfc, 0x39, 0xfe, 0x0f, 0x00, 0x40, 0xd1, 0x03, 0x40, 0xc5, 0x5e, 0x7f, 0x6b, 0x4c, 0xf1, 0x17, 0xcb, 0x28, 0xfe, 0x00, 0x00, 0x34, 0x48, 0x00, 0xf0, 0x06, 0x03, 0x92, 0xc3, 0x01, 0xef, 0x55, 0xd9, 0xf3, 0x97, 0x9b, 0x0c, 0x16, 0x24, 0xd3, 0xcf, 0x61, 0x75, 0x02, 0x00, 0x50, 0x0c, 0x3a, 0x17, 0x03, 0x92, 0x96, 0x80, 0x35, 0x15, 0xf7, 0x7b, 0xbd, 0x56, 0x81, 0x49, 0xde, 0x60, 0x41, 0xfe, 0x88, 0x81, 0x8c, 0x02, 0x08, 0x00, 0x40, 0x41, 0x84, 0x76, 0x02, 0x0c, 0xe3, 0x15, 0x78, 0x39, 0x14, 0xb0, 0xa6, 0x34, 0x6d, 0x7b, 0xe0, 0x31, 0x19, 0x07, 0x60, 0x57, 0xe0, 0x6f, 0xac, 0x5d, 0x00, 0x00, 0x0a, 0xdc, 0x02, 0xe0, 0x07, 0x84, 0xde, 0x2a, 0x8f, 0x71, 0xce, 0x3f, 0x00, 0x00, 0x8d, 0x18, 0x00, 0x00, 0x00, 0xc0, 0xd0, 0x0d, 0x00, 0xd2, 0x17, 0x80, 0xbd, 0x7d, 0x00, 0x00, 0x0a, 0xce, 0xe1, 0x58, 0x3d, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x50, 0x53, 0xcd, 0x09, 0xa7, 0x77, 0x4b, 0x37, 0x27, 0xe6, 0xb1, 0xa8, 0x69, 0x2a, 0xff, 0x1e, 0x37, 0x4d, 0xb5, 0xd7, 0x89, 0x9b, 0xdf, 0xe7, 0x24, 0x5c, 0xfe, 0xb0, 0xe7, 0x71, 0x22, 0xee, 0x17, 0x5d, 0xdc, 0xfa, 0x73, 0x0c, 0x3f, 0xff, 0xb8, 0x75, 0xaf, 0x34, 0xd6, 0x63, 0xd4, 0x32, 0xb8, 0x21, 0xd3, 0x3a, 0x09, 0x5e, 0x23, 0xed, 0xfc, 0x49, 0xde, 0x43, 0xbd, 0x7e, 0xe6, 0xba, 0xef, 0x2d, 0xe9, 0x36, 0xa0, 0xb3, 0x6e, 0xab, 0x2d, 0x83, 0x9b, 0xe0, 0x73, 0xd1, 0x99, 0x5f, 0xe7, 0x39, 0x1c, 0x8d, 0xf7, 0xe4, 0x58, 0x5a, 0x7f, 0x6e, 0xc2, 0xfb, 0x49, 0xbe, 0xaf, 0x8e, 0xc1, 0xf2, 0x67, 0xb1, 0xfe, 0x4c, 0xe7, 0x77, 0xab, 0xbc, 0x6f, 0xc7, 0x70,
		0xfd, 0xe9, 0xae, 0x5f, 0xdd, 0x9a, 0xa5, 0xf3, 0xb8, 0x4a, 0xf1, 0xfb, 0xa2, 0x53, 0x97, 0x5c, 0xc3, 0xef, 0xa6, 0xd5, 0x00, 0x90, 0xf7, 0x0f, 0x95, 0x6e, 0x61, 0x32, 0xf9, 0x52, 0x25, 0xf9, 0xb2, 0x39, 0x29, 0xbf, 0xa8, 0x69, 0x97, 0x29, 0xef, 0x50, 0xa0, 0xfb, 0x23, 0x9f, 0xe5, 0x17, 0x52, 0xe7, 0x0b, 0x95, 0x64, 0x19, 0xe2, 0xde, 0x8f, 0xad, 0xf7, 0x90, 0x65, 0x40, 0x4b, 0x1b, 0xce, 0x93, 0xbc, 0x97, 0xa4, 0xcb, 0xe0, 0xa4, 0x7c, 0x4d, 0x47, 0xf3, 0x3b, 0xa8, 0x2c, 0x6c, 0x1b, 0xa6, 0xef, 0xaf, 0xda, 0x3c, 0x8e, 0xe6, 0x77, 0xc5, 0xd6, 0x36, 0xe1, 0xa6, 0xf8, 0xfc, 0x75, 0xbf, 0x1f, 0x4e, 0x0e, 0xf3, 0xe7, 0xf5, 0x9d, 0x4a, 0xfa, 0xd9, 0x26, 0x59, 0x16, 0x9d, 0x40, 0x98, 0x76, 0xc7, 0x21, 0x2e, 0x30, 0xe9, 0xee, 0x3c, 0x0f, 0xd0, 0x64, 0x79, 0x25, 0xa6, 0x79, 0x83, 0x95, 0x1b, 0x84, 0x13, 0x93, 0x18, 0x1d, 0xc3, 0x0f, 0xc5, 0x49, 0xf8, 0x25, 0x8b, 0xda, 0x50, 0xe2, 0x3e, 0x6c, 0x57, 0xd5, 0x2f, 0xdd, 0x2f, 0xb3, 0x9b, 0x60, 0xdd, 0x35, 0x4a, 0xcb, 0x48, 0x3d, 0xb7, 0xce, 0xe8, 0xfe, 0x88, 0xa5, 0x0d, 0x7e, 0x6e, 0x95, 0xe7, 0x73, 0x0d, 0x5f, 0x27, 0x69, 0x41, 0x77, 0x72, 0xf8, 0x0e, 0x39, 0x05, 0xfb, 0x7c, 0x1b, 0x8d, 0x53, 0xb0, 0x65, 0x4d, 0x1b, 0xb8, 0x54, 0x86, 0xdb, 0xbb, 0x1b, 0xa8, 0xbf, 0xda, 0xcf, 0xd5, 0x94, 0xe3, 0x46, 0x1f, 0xfc, 0x81, 0x71, 0x13, 0x6c, 0x20, 0x4e, 0x0e, 0x2b, 0xd1, 0xd6, 0x06, 0x52, 0xf4, 0x2f, 0xb8, 0x5b, 0xa3, 0x2f, 0xbb, 0xed, 0xf5, 0x56, 0x8b, 0x96, 0x18, 0xd7, 0xc2, 0xe3, 0x51, 0x7b, 0x13, 0x61, 0x37, 0xdd, 0xef, 0x40, 0x92, 0xf5, 0x5f, 0xcb, 0xef, 0x11, 0xe1, 0xce, 0xfc, 0x37, 0x86, 0xcf, 0x2d, 0xdb, 0xdf, 0xf0, 0x7a, 0xfe, 0x8d, 0x77, 0x0c, 0xbe, 0xef, 0x65, 0xcd, 0x39, 0xaf, 0x5c, 0x27, 0xe5, 0x0a, 0xb4, 0x99, 0xba, 0xb2, 0x7e, 0x8f, 0x51, 0x3f, 0xfc, 0xa6, 0xfd, 0x09, 0x5c, 0xd3, 0x0f, 0xb9, 0x8e, 0xd6, 0x51, 0xda, 0xbe, 0x14, 0x59, 0x1e, 0x83, 0x77, 0x62, 0x9e, 0x5f, 0xe7, 0x07, 0xd6, 0x76, 0x33, 0xb5, 0xc9, 0x7b, 0x75, 0x32, 0xfa, 0x9e, 0x84, 0xed, 0x65, 0x38, 0x96, 0xb7, 0xcf, 0x34, 0x9f, 0xbd, 0x6b, 0xe1, 0xbb, 0xc1, 0x9e, 0x7f, 0x7e, 0x7b, 0xd0, 0x4e, 0x1d, 0x2f, 0xa7, 0x53, 0x83, 0xcf, 0xd9, 0xa9, 0xc5, 0x36, 0xd2, 0x5c, 0xc7, 0x1b, 0x89, 0x93, 0x62, 0xa5, 0xd7, 0xa2, 0xd3, 0x5e, 0x5c, 0x7a, 0xb4, 0xb1, 0x07, 0x50, 0xcf, 0x7b, 0x28, 0x49, 0x0a, 0x99, 0xc9, 0xf1, 0x36, 0x9d, 0x63, 0xb8, 0x69, 0x8a, 0x80, 0xce, 0x32, 0x65, 0x75, 0x9c, 0x37, 0x8b, 0xd6, 0x0f, 0x1b, 0xc7, 0xbd, 0xd3, 0x6c, 0x9f, 0x79, 0xb6, 0xe8, 0x24, 0xf9, 0xbc, 0xa3, 0xb6, 0x91, 0x24, 0x7d, 0x5e, 0x6a, 0x55, 0x5c, 0xb2, 0x7c, 0x8d, 0xb4, 0x05, 0x3a, 0x6e, 0xfe, 0x3c, 0xb7, 0xc5, 0xac, 0x5b, 0x61, 0xea, 0x75, 0x27, 0xb4, 0x6e, 0x03, 0x80, 0x1b, 0xb1, 0x27, 0x1c, 0xf7, 0x03, 0x9b, 0xb6, 0x53, 0x46, 0x5e, 0x1f, 0x48, 0xb0, 0x03, 0x46, 0x3d, 0x6e, 0x08, 0x79, 0x2c, 0x53, 0x9a, 0xd7, 0xb0, 0xf1, 0x83, 0x9b, 0xa4, 0xa3, 0x61, 0xa3, 0xed, 0x79, 0xa4, 0x7d, 0x8f, 0x8e, 0x0a, 0x6f, 0xa9, 0xca, 0x73, 0x2f, 0x39, 0xaf, 0x75, 0x5d, 0xab, 0xf7, 0x92, 0xf6, 0x73, 0xce, 0xf2, 0xb7, 0xc5, 0xb1, 0x3c, 0x7f, 0x11, 0x5b, 0x3c, 0xd2, 0xfc, 0x7e, 0xbb, 0x96, 0xd6, 0x61, 0xae, 0xeb, 0xad, 0x68, 0x87, 0x00, 0xea, 0x75, 0x03, 0x73, 0x2c, 0x7f, 0x99, 0xea, 0xe5, 0x7d, 0xd8, 0xfa, 0x3c, 0x74, 0x3a, 0x57, 0x36, 0x5a, 0xa1, 0xb1, 0xf9, 0xe5, 0x4f, 0xd2, 0xa3, 0x38, 0x8b, 0x56, 0xa6, 0x22, 0x85, 0xa9, 0x22, 0x7f, 0xce, 0x36, 0x9f, 0x3f, 0x8f, 0x1d, 0xba, 0x46, 0x12, 0x77, 0x88, 0xab, 0x21, 0x35, 0xd5, 0xd9, 0x07, 0xa0, 0x5b, 0x5c, 0x5c, 0x8d, 0x8d, 0xde, 0xc6, 0x5e, 0x50, 0xda, 0x42, 0x66, 0x3b, 0x65, 0x67, 0x15, 0x96, 0xc2, 0xf6, 0xfe, 0x1c, 0x8b, 0xcf, 0xdf, 0x08, 0x3f, 0x3a, 0x79, 0xbc, 0x7e, 0xb5, 0x4e, 0x7c, 0x61, 0x37, 0x1b, 0xdb, 0xa7, 0xee, 0x99, 0x2d, 0xb6, 0xdf, 0x97, 0x5b, 0xe3, 0xed, 0xa9, 0xa8, 0xdb, 0x66, 0x3d, 0xac, 0x17, 0xa7, 0xce, 0xd6, 0x8f, 0x6e, 0x07, 0x3d, 0xd3, 0xb3, 0x58, 0xf2, 0xfc, 0xfd, 0xcb, 0xb5, 0x33, 0x67, 0x73, 0x8e, 0x1b, 0x5f, 0x5c, 0xaf, 0xfe, 0x24, 0x7d, 0x00, 0x74, 0xe7, 0x4f, 0x1b, 0x02, 0xf2, 0x1e, 0x08, 0xa8, 0x56, 0x1d, 0x50, 0xa2, 0xde, 0x77, 0xd8, 0x97, 0x58, 0x77, 0x2f, 0xd5, 0x31, 0xfc, 0x6c, 0x75, 0xbf, 0x18, 0x4e, 0x8a, 0xed, 0x27, 0xab, 0xe7, 0xb7, 0x31, 0x0e, 0x44, 0x96, 0x4d, 0x90, 0x6e, 0x82, 0x10, 0x90, 0xc5, 0x31, 0x60, 0xdd, 0x81, 0x9a, 0xd2, 0x0c, 0x54, 0xa4, 0x32, 0x7e, 0x7f, 0x6e, 0x06, 0xdb, 0x9e, 0x52, 0x76, 0x3b, 0xc9, 0x45, 0xfd, 0x16, 0xda, 0x5e, 0x7f, 0x49, 0x4e, 0xc9, 0xb6, 0xf9, 0xfa, 0x4e, 0xc2, 0xef, 0x8d, 0x13, 0xb3, 0x87, 0x5f, 0xed, 0x33, 0x75, 0x0c, 0x3f, 0xbf, 0x7a, 0x09, 0x6b, 0xd5, 0x02, 0x98, 0xd3, 0x9c, 0xc1, 0x8f, 0x4c, 0x16, 0x09, 0xc8, 0x74, 0x40, 0x06, 0x5b, 0x4d, 0xa1, 0x45, 0xd9, 0x1b, 0x49, 0xdb, 0x8b, 0xdc, 0xc9, 0xe0, 0x31, 0xd3, 0x2f, 0x7c, 0x56, 0x2d, 0x2c, 0x59, 0xb6, 0xe0, 0xd8, 0x3a, 0xf5, 0xd0, 0xb1, 0xf8, 0xd9, 0x67, 0xf9, 0xf9, 0x3a, 0x96, 0xb6, 0xaf, 0x2c, 0xd7, 0x7b, 0x9a, 0x1d, 0x0a, 0x5b, 0xcb, 0xe0, 0x64, 0xf4, 0xdc, 0x8e, 0xa5, 0xe5, 0x4f, 0x3b, 0xae, 0x8a, 0x8d, 0xf5, 0x97, 0xf5, 0x6f, 0x8c, 0x93, 0x70, 0x87, 0x54, 0xf7, 0x7d, 0x65, 0x51, 0x1f, 0x72, 0x7b, 0xbe, 0xe6, 0x1a, 0x2f, 0x58, 0xda, 0x1f, 0x94, 0x46, 0xc2, 0xf1, 0xd4, 0xc6, 0xc6, 0x67, 0x0b, 0xc0, 0xd6, 0x69, 0xe0, 0x56, 0x34, 0xf3, 0x79, 0x50, 0x20, 0x00, 0x00, 0x75, 0xfd, 0x1b, 0x9f, 0x49, 0x7d, 0xe0, 0x6a, 0x80, 0x00, 0x00, 0x0c, 0x41, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x60, 0x28, 0x06, 0x00, 0xd3, 0x8e, 0x06, 0x59, 0x5d, 0xfe, 0xd2, 0x64, 0x1e, 0x37, 0xc3, 0xd7, 0x72, 0x0d, 0xa7, 0x71, 0x33, 0x5c, 0xf6, 0x46, 0xe2, 0x0e, 0xa1, 0xf7, 0x99, 0x64, 0x3b, 0x61, 0xdb, 0x00, 0x40, 0x0b, 0x40, 0xcc, 0x8f, 0x6a, 0xd6, 0x57, 0x33, 0xb3, 0x7d, 0xba, 0x9b, 0x8d, 0xf9, 0x50, 0xdc, 0xed, 0x34, 0xc9, 0xb6, 0xa1, 0x33, 0x48, 0xd5, 0x50, 0x0a, 0x51, 0x00, 0x2c, 0x07, 0x00, 0x47, 0x63, 0x2f, 0xc4, 0xd5, 0x9c, 0x26, 0xc9, 0x63, 0x36, 0x1e, 0x8f, 0x2b, 0xa6, 0x3a, 0xf3, 0xeb, 0xbc, 0xbe, 0x8d, 0xbd, 0x78, 0x93, 0xeb, 0xa9, 0x57, 0xfb, 0x91, 0x77, 0x13, 0x2c, 0xbf, 0x1b, 0xf3, 0xfc, 0x3a, 0xef, 0xdf, 0xe4, 0x39, 0x92, 0x7c, 0x7e, 0x3a, 0xeb, 0xab, 0xda, 0xb8, 0xf5, 0xb5, 0xb8, 0xef, 0xa6, 0x7c, 0x8f, 0x36, 0x42, 0x05, 0xa7, 0x92, 0x02, 0xd0, 0xd6,
		0x9c, 0xa0, 0x78, 0xc6, 0x5d, 0xec, 0xa1, 0xda, 0xfd, 0x24, 0xd3, 0x46, 0xfd, 0xc0, 0x9a, 0x5e, 0x18, 0x48, 0x77, 0x7e, 0xdd, 0x91, 0xa1, 0xe2, 0x82, 0x87, 0xe9, 0x35, 0xdf, 0x93, 0xfe, 0xc8, 0xdb, 0x5c, 0xdf, 0x49, 0xe6, 0x37, 0x19, 0xc2, 0x55, 0xf7, 0xf5, 0x2b, 0xff, 0xcd, 0xb3, 0x90, 0xa5, 0xbd, 0x90, 0x93, 0x63, 0xe1, 0xf3, 0x4d, 0xbb, 0xfc, 0x4a, 0x51, 0xfc, 0x01, 0xa4, 0x68, 0x01, 0x48, 0xb2, 0x47, 0x6d, 0x32, 0x8d, 0xee, 0xb4, 0xb5, 0xf8, 0x21, 0xcb, 0x63, 0x98, 0xdf, 0x2c, 0x2f, 0x07, 0xec, 0xe4, 0xf4, 0xfe, 0x9d, 0x8c, 0x9e, 0xa3, 0xb2, 0x88, 0x51, 0xc8, 0x00, 0xa0, 0x06, 0x2d, 0x00, 0xd5, 0x0a, 0x58, 0x2d, 0x25, 0x69, 0x5a, 0xaf, 0xc7, 0x02, 0x92, 0xf7, 0x25, 0x8a, 0xeb, 0xed, 0xbd, 0xa7, 0x1d, 0x2b, 0x3d, 0xcf, 0x56, 0x80, 0x34, 0xdb, 0x28, 0xe1, 0x05, 0x40, 0x43, 0x05, 0x80, 0x6a, 0x4d, 0xb6, 0xf5, 0xb4, 0x87, 0x5e, 0x84, 0x1f, 0xdf, 0xa1, 0x7a, 0xac, 0xb6, 0xd6, 0xcd, 0xe4, 0xf5, 0x50, 0xa0, 0xd3, 0xbe, 0x3e, 0xc7, 0xf9, 0x01, 0x58, 0xc3, 0x38, 0x00, 0xc0, 0xc0, 0xe2, 0xec, 0xa6, 0x9c, 0x5f, 0xa7, 0x80, 0x17, 0x35, 0xc0, 0x00, 0x20, 0x00, 0xa4, 0xbe, 0x7e, 0xb8, 0x9b, 0xf1, 0xe3, 0xb0, 0xf3, 0x99, 0xda, 0x5a, 0xf7, 0x6e, 0xc6, 0xcb, 0xaa, 0x7b, 0x3d, 0x70, 0x00, 0x80, 0x47, 0xf7, 0x10, 0x80, 0xee, 0xf5, 0xa5, 0xa3, 0x8e, 0xf3, 0x9a, 0x5c, 0x6b, 0xdd, 0x4d, 0x30, 0x7f, 0xd2, 0xe5, 0x4f, 0x53, 0x74, 0xb2, 0x2a, 0x30, 0x59, 0x3e, 0x7f, 0x92, 0xeb, 0x69, 0xc7, 0x7d, 0x3e, 0x26, 0xeb, 0x52, 0xf7, 0xf3, 0x8b, 0x5a, 0x86, 0x24, 0xdb, 0x5f, 0xdc, 0xf5, 0xc0, 0xe3, 0xce, 0x80, 0x08, 0x9b, 0xc6, 0xe4, 0x1c, 0x7c, 0x42, 0x08, 0x80, 0x86, 0x08, 0x00, 0x51, 0x45, 0x21, 0xf8, 0xff, 0x36, 0xaf, 0xb5, 0x6e, 0xf3, 0x7a, 0xdc, 0xc1, 0xc7, 0x5d, 0x83, 0xd7, 0xb2, 0x79, 0x25, 0xa7, 0xa4, 0xcf, 0x1f, 0xb7, 0xae, 0x6d, 0x2d, 0xbf, 0xcd, 0xcf, 0xcf, 0x74, 0xfd, 0x39, 0x19, 0xaf, 0x43, 0xc7, 0xc2, 0x73, 0xbb, 0x16, 0xb7, 0x0d, 0x00, 0xa8, 0x09, 0xfa, 0x00, 0x00, 0x00, 0x40, 0x00, 0x68, 0x58, 0x6e, 0x41, 0x9f, 0x1b, 0x8d, 0xb7, 0xfd, 0xf8, 0x87, 0x13, 0x92, 0xf6, 0x99, 0xa1, 0x6f, 0x03, 0x00, 0xab, 0x9a, 0x87, 0xc8, 0xfb, 0xcc, 0xf2, 0x3c, 0xf4, 0x22, 0x9c, 0xe3, 0x8e, 0xfa, 0xfa, 0x8c, 0x1d, 0x4b, 0x7f, 0x07, 0x00, 0x02, 0x40, 0x8a, 0x1f, 0xdd, 0x7a, 0x7f, 0xee, 0x7a, 0x5c, 0x37, 0x43, 0xb1, 0x20, 0x51, 0x84, 0x01, 0x34, 0x14, 0xfa, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x53, 0xff, 0x2f, 0xc0, 0x00, 0xe4, 0xb2, 0xe4, 0xfa, 0xa6, 0x0a, 0x6f, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82 };
	*size = zt_sizeof(data);
	byte *result = zt_mallocStructArray(byte, *size);
	zt_memCpy(result, *size, data, *size);
	return result;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztFontID _zt_guiLoadDefaultFont(ztTextureID tex)
{
	char *data = "info face=ZeroToleranceGui size=16 bold=0 italic=0 charset=unicode=stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=0,0 outline=0\ncommon lineHeight=16 base=13 scaleW=512 scaleH=64 pages=1 packed=0\npage id=0 file=\".\"\nchars count=94\nchar id=33 x=8 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=34 x=16 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=35 x=24 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=36 x=32 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=37 x=40 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=38 x=48 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=39 x=56 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=40 x=64 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=41 x=72 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=42 x=80 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=43 x=88 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=44 x=96 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=45 x=104 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=46 x=112 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=47 x=120 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=48 x=128 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=49 x=136 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=50 x=144 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=51 x=152 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=52 x=160 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=53 x=168 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=54 x=176 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=55 x=184 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=56 x=192 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=57 x=200 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=58 x=208 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=59 x=216 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=60 x=224 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=61 x=232 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=62 x=240 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=63 x=248 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=64 x=256 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=65 x=264 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=66 x=272 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=67 x=280 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=68 x=288 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=69 x=296 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=70 x=304 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=71 x=312 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=72 x=320 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=73 x=328 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=74 x=336 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=75 x=344 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=76 x=352 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=77 x=360 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=78 x=368 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=79 x=376 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=80 x=384 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=81 x=392 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=82 x=400 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=83 x=408 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=84 x=416 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=85 x=424 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=86 x=432 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=87 x=440 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=88 x=448 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=89 x=456 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=90 x=464 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=91 x=472 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=92 x=480 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=93 x=488 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=94 x=496 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=95 x=504 y=0 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=96 x=0 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=97 x=8 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=98 x=16 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=99 x=24 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=100 x=32 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=101 x=40 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=102 x=48 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=103 x=56 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=104 x=64 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=105 x=72 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=106 x=80 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=107 x=88 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=108 x=96 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=109 x=104 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=110 x=112 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=111 x=120 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=112 x=128 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=113 x=136 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=114 x=144 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=115 x=152 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=116 x=160 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=117 x=168 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=118 x=176 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=119 x=184 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=120 x=192 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=121 x=200 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=122 x=208 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=123 x=216 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=124 x=224 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=125 x=232 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\nchar id=126 x=240 y=16 width=8 height=16 xoffset=0 yoffset=0 xadvance=8 page=0 chnl=15\n";
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
	gm->item_cache_used = 0;

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

		// ----------------------------------------------------------------

		r32 ppu = zt_pixelsPerUnit();

		gm->default_theme.font_scale = 1;
		gm->default_theme.font_color = ztColor::one;
		gm->default_theme.back_color = ztColor(0, 0, 0, 1);
		gm->default_theme.highlight_color = ztColor(0, .5f, .5f, 1);

		gm->default_theme.padding = 3.f / ppu;
		gm->default_theme.spacing = 6.f / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_icon_close = zt_spriteMake(tex, ztPoint2(16, 64), ztPoint2(16, 16));
		gm->default_theme.sprite_icon_resize = zt_spriteMake(tex, ztPoint2(64, 64), ztPoint2(16, 16));
		gm->default_theme.sprite_icon_collapse = zt_spriteMake(tex, ztPoint2(1, 52), ztPoint2(13, 13));
		gm->default_theme.sprite_icon_expand = zt_spriteMake(tex, ztPoint2(14, 49), ztPoint2(13, 13));

		// ----------------------------------------------------------------

		gm->default_theme.window_title_height = 26 / ppu;
		gm->default_theme.window_title_align = ztAlign_Left | ztAlign_Center;
		gm->default_theme.window_title_padding_x = 8 / ppu;
		gm->default_theme.window_title_padding_y = 3 / ppu;

		gm->default_theme.sprite_window.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_window.sns = zt_spriteNineSliceMake(tex, ztPoint2(0, 0), ztPoint2(32, 32), ztPoint2(2, 29), ztPoint2(29, 30));

		gm->default_theme.sprite_window_collapsed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_window_collapsed.sns = zt_spriteNineSliceMake(tex, ztPoint2(0, 0), ztPoint2(32, 27), ztPoint2(3, 3), ztPoint2(29, 24));

		// ----------------------------------------------------------------

		gm->default_theme.sprite_panel.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_panel.sns = zt_spriteNineSliceMake(tex, ztPoint2(72, 0), ztPoint2(12, 12), ztPoint2(74, 2), ztPoint2(81, 9));

		gm->default_theme.sprite_collapsing_panel_header = gm->default_theme.sprite_window_collapsed;

		gm->default_theme.collapsing_panel_header_h = 27 / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_button.normal.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_button.normal.sns = zt_spriteNineSliceMake(tex, ztPoint2(33, 0), ztPoint2(12, 12), ztPoint2(35, 2), ztPoint2(42, 9));
		gm->default_theme.sprite_button.highlight.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_button.highlight.sns = zt_spriteNineSliceMake(tex, ztPoint2(46, 0), ztPoint2(12, 12), ztPoint2(48, 2), ztPoint2(55, 9));
		gm->default_theme.sprite_button.pressed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_button.pressed.sns = zt_spriteNineSliceMake(tex, ztPoint2(59, 0), ztPoint2(12, 12), ztPoint2(61, 2), ztPoint2(68, 9));

		gm->default_theme.button_default_w = 96 / ppu;
		gm->default_theme.button_default_h = 32 / ppu;
		gm->default_theme.button_padding_w = 3 / ppu;
		gm->default_theme.button_padding_h = 3 / ppu;

		gm->default_theme.button_dip_x = 1 / ppu;
		gm->default_theme.button_dip_y = -1 / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_checkbox.normal = gm->default_theme.sprite_button.normal;
		gm->default_theme.sprite_checkbox.highlight = gm->default_theme.sprite_button.highlight;
		gm->default_theme.sprite_checkbox.pressed = gm->default_theme.sprite_button.pressed;
		gm->default_theme.sprite_checkbox_check.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_checkbox_check.s = zt_spriteMake(tex, ztPoint2(1,36), ztPoint2(17, 17));

		gm->default_theme.checkbox_size_w = 17 / ppu;
		gm->default_theme.checkbox_size_h = 17 / ppu;

		// ----------------------------------------------------------------

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

		// ----------------------------------------------------------------

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

		// ----------------------------------------------------------------

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

		// ----------------------------------------------------------------

		gm->default_theme.scroll_container_padding_x = 2 / ppu;
		gm->default_theme.scroll_container_padding_y = 2 / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_textedit = gm->default_theme.sprite_button.normal;
		gm->default_theme.sprite_textedit_select.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_textedit_select.s = zt_spriteMake(tex, ztPoint2(60, 1), ztPoint2(10, 10));

		gm->default_theme.textedit_padding_x = 3 / ppu;
		gm->default_theme.textedit_padding_y = 3 / ppu;
		gm->default_theme.textedit_default_h = 24 / ppu;
		gm->default_theme.textedit_default_w = 100 / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_menu = gm->default_theme.sprite_button.normal;
		gm->default_theme.sprite_menu_highlight = gm->default_theme.sprite_button.highlight;
		gm->default_theme.sprite_menu_check = gm->default_theme.sprite_checkbox_check;
		gm->default_theme.sprite_menu_submenu.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_menu_submenu.s = zt_spriteMake(tex, ztPoint2(0, 64), ztPoint2(16, 16));

		gm->default_theme.menu_padding_x = 3 / ppu;
		gm->default_theme.menu_padding_y = 3 / ppu;
		gm->default_theme.menu_submenu_icon_x = 16 / ppu;
		gm->default_theme.menu_submenu_icon_y = 16 / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_tree_background = gm->default_theme.sprite_panel;
		gm->default_theme.sprite_tree_highlight = gm->default_theme.sprite_menu_highlight;
		gm->default_theme.sprite_tree_collapse = zt_spriteMake(tex, ztPoint2(48, 48), ztPoint2(16, 16));
		gm->default_theme.sprite_tree_expand = zt_spriteMake(tex, ztPoint2(32, 48), ztPoint2(16, 16));

		gm->default_theme.tree_indent = 10 / ppu;

		// ----------------------------------------------------------------

		gm->default_theme.sprite_combobox_background.normal.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_combobox_background.normal.sns = zt_spriteNineSliceMake(tex, ztPoint2(112, 48), ztPoint2(17, 20), ztPoint2(114, 50), ztPoint2(126, 65));
		gm->default_theme.sprite_combobox_background.highlight.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_combobox_background.highlight.sns = zt_spriteNineSliceMake(tex, ztPoint2(146, 48), ztPoint2(17, 20), ztPoint2(148, 50), ztPoint2(160, 65));
		gm->default_theme.sprite_combobox_background.pressed.type = ztGuiThemeSpriteType_SpriteNineSlice;
		gm->default_theme.sprite_combobox_background.pressed.sns = zt_spriteNineSliceMake(tex, ztPoint2(180, 48), ztPoint2(17, 20), ztPoint2(182, 90), ztPoint2(194, 65));

		gm->default_theme.sprite_combobox_button.normal.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_combobox_button.normal.s = zt_spriteMake(tex, ztPoint2(128, 48), ztPoint2(16, 20));
		gm->default_theme.sprite_combobox_button.highlight.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_combobox_button.highlight.s = zt_spriteMake(tex, ztPoint2(162, 48), ztPoint2(16, 20));
		gm->default_theme.sprite_combobox_button.pressed.type = ztGuiThemeSpriteType_Sprite;
		gm->default_theme.sprite_combobox_button.pressed.s = zt_spriteMake(tex, ztPoint2(196, 48), ztPoint2(16, 20));

		gm->default_theme.combobox_size_y = 20 / ppu;
		gm->default_theme.combobox_button_size_x = 16 / ppu;

		// ----------------------------------------------------------------
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

	if (item->id == gm->item_has_mouse) {
		gm->item_has_mouse = ztInvalidID;
	}
	if (item->id == gm->tooltip_item) {
		gm->tooltip_item = ztInvalidID;
	}

	// remove from parent list
	ztGuiItem *child = item->parent ? item->parent->first_child : gm->first_child;
	while (child) {
		if (child == item) {
			if (child->sib_prev) {
				child->sib_prev->sib_next = child->sib_next;
			}
			if (child->sib_next) {
				child->sib_next = child->sib_prev;
			}

			if (item->parent && item->parent->first_child == child) {
				item->parent->first_child = child->sib_next;
			}
			else if(gm->first_child == child) {
				gm->first_child = child->sib_next;
			}
			break;
		}
		child = child->sib_next;
	}

	// remove our children
	child = item->first_child;
	while (child) {
		ztGuiItem *next_child = child->sib_next;
		_zt_guiItemFree(gm, child);
		child = next_child;
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

	gm->item_cache_flags[item->id - gm->base_id] = 0;
	gm->item_cache_used -= 1;

	zt_memSet(item, zt_sizeof(ztGuiItem), 0);
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

	zt_fiz(zt_elementsOf(zt_gui->gui_managers)) {
		if (zt_gui->gui_managers[i] != nullptr) {
			return;
		}
	}

	auto* command = zt_gui->console_commands;
	while (command) {
		auto* next = command->next;
		zt_freeArena(command, zt_gui->arena);
		command = next;
	}
	zt_freeArena(zt_gui, zt_gui->arena);
	zt_gui = nullptr;
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

	int item_count = gm->item_cache_used;
	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] != 0) {
			zt_bitRemove(gm->item_cache_flags[i], ztGuiManagerItemCacheFlags_MouseOver);

			if (gm->item_cache[i].prev_size.x != gm->item_cache[i].size.y || gm->item_cache[i].prev_size.y != gm->item_cache[i].size.y) {
				gm->item_cache[i].flags |= ztGuiItemFlags_Dirty;
				gm->item_cache[i].prev_size = gm->item_cache[i].size;

				auto *child = gm->item_cache[i].first_child;
				while (child) {
					if (child->pos_align_flags != 0) {
						_zt_guiItemReposition(gm, child);
					}
					child = child->sib_next;
				}

				if (gm->item_cache[i].parent == nullptr) {
					if (gm->item_cache[i].pos_align_flags != 0) {
						_zt_guiItemReposition(gm, &gm->item_cache[i]);
					}
				}
			}
			if (--item_count == 0) {
				break;
			}
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

		int item_count = gm->item_cache_used;
		zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
			if (gm->item_cache_flags[i] != 0) {
				if ((gm->item_cache[i].pos_anchor_flags || gm->item_cache[i].pos_align_flags) && gm->item_cache[i].parent == nullptr) {
					_zt_guiItemReposition(gm, &gm->item_cache[i]);
				}
				if (--item_count == 0) {
					break;
				}
			}
		}
	}

	//zt_memArenaValidate(gm->arena);
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
					if (!zt_bitIsSet(item->flags, ztGuiItemFlags_Visible) || zt_bitIsSet(item->flags, ztGuiItemFlags_Disabled)) {
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
					gm->keyboard_focus = true;
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

ztVec2 zt_guiThemeSpriteGetSize(ztGuiThemeSprite *sprite)
{
	if (sprite->type == ztGuiThemeSpriteType_Sprite) {
		return ztVec2(sprite->s.half_size.x * 2.f, sprite->s.half_size.y * 2.f);
	}
	else {
		return ztVec2(sprite->sns.sp_w.x + sprite->sns.sp_e.x, sprite->sns.sp_n.y + sprite->sns.sp_s.y);
	}
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiThemeButtonSpriteGetSize(ztGuiThemeButtonSprite *sprite)
{
	ztVec2 normal    = zt_guiThemeSpriteGetSize(&sprite->normal);
	ztVec2 highlight = zt_guiThemeSpriteGetSize(&sprite->highlight);
	ztVec2 pressed   = zt_guiThemeSpriteGetSize(&sprite->pressed);

	return ztVec2(zt_max(normal.x, zt_max(highlight.x, pressed.x)), zt_max(normal.y, zt_max(highlight.y, pressed.y)));
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerRender(ztGuiManagerID gui_manager, ztDrawList *draw_list)
{
	zt_returnOnNull(draw_list);
	_zt_guiManagerCheckAndGet(gm, gui_manager);

//#define _zt_guiManagerRenderClipAreas

	struct local
	{
		static void renderItem(ztGuiManager *gm, ztGuiItem *item, ztDrawList *draw_list, const ztVec2& offset)
		{
			if (!zt_bitIsSet(item->flags, ztGuiItemFlags_Visible) || item->size == ztVec2::zero) {
				return;
			}

			ztVec2 pos = item->pos + offset;

			ztGuiTheme *theme = item->theme == nullptr ? &gm->default_theme : item->theme;

			bool clip = zt_bitIsSet(item->flags, ztGuiItemFlags_ClipContents);
			if (clip) {
				if (item->clip_area != ztVec4::zero) {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, ztVec4(1, 0, 0, .5f));
						zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
						zt_drawListPopColor(&g_game->draw_list);
#					else
						zt_drawListPushClipRegion(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
#					endif
				}
				else {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, ztVec4(0, 1, 0, .5f));
						zt_drawListAddEmptyRect(draw_list, pos, item->size);
						zt_drawListPopColor(&g_game->draw_list);
#					else
						zt_drawListPushClipRegion(draw_list, pos, item->size);
#					endif
				}
			}

			if (item->functions.render) {
				item->functions.render(item->id, draw_list, theme, offset, !zt_bitIsSet(item->flags, ztGuiItemFlags_Disabled), item->functions.user_data);
			}

			zt_bitRemove(item->flags, ztGuiItemFlags_Dirty);

#			if defined(ZT_DEBUG)
				if (item->debug_highlight != ztVec4::zero) {
					zt_drawListPushColor(draw_list, item->debug_highlight);
					zt_drawListAddEmptyRect(draw_list, pos, item->size);
					zt_drawListPopColor(draw_list);
				}
#			endif
			if (!clip && zt_bitIsSet(item->flags, ztGuiItemFlags_ClipChildren) ) {
				clip = true;
				if (item->clip_area != ztVec4::zero) {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, ztVec4(1, 1, 0, 1));
						zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
						zt_drawListPopColor(&g_game->draw_list);
#					else
						zt_drawListPushClipRegion(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
#					endif
				}
				else {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, ztVec4(0, 1, 1, 1));
						zt_drawListAddEmptyRect(draw_list, pos, item->size);
						zt_drawListPopColor(&g_game->draw_list);
#					else
						zt_drawListPushClipRegion(draw_list, pos, item->size);
#					endif
				}
			}
			else if (clip && !zt_bitIsSet(item->flags, ztGuiItemFlags_ClipChildren)) {
#				if defined(_zt_guiManagerRenderClipAreas)
					zt_drawListPopColor(draw_list);
#				else
					zt_drawListPopClipRegion(draw_list);
#				endif
				clip = false;
			}

			ztGuiItem *child = item->first_child;
			while (child) {
				renderItem(gm, child, draw_list, pos);
				child = child->sib_next;
			}

			if (clip) {
#				if defined(_zt_guiManagerRenderClipAreas)
					zt_drawListPopColor(draw_list);
#				else
					zt_drawListPopClipRegion(draw_list);
#				endif
			}
		}
	};

	zt_drawListPushColor(draw_list, ztVec4::one);

	ztGuiItem *child = gm->first_child;
	while (child) {
		local::renderItem(gm, child, draw_list, ztVec2::zero);
		child = child->sib_next;
	}

	zt_drawListPopColor(draw_list);

#	if defined(_zt_guiManagerRenderClipAreas)
#		undef _zt_guiManagerRenderClipAreas
#	endif

}

// ------------------------------------------------------------------------------------------------

void zt_guiSetActiveManager(ztGuiManagerID gui_manager)
{
	_zt_guiManagerCheckAndGet(gm, gui_manager);
	zt_gui->active_gui_manager = gui_manager;
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerSetKeyboardFocus(ztGuiManagerID gui_manager, bool keyboard_focus)
{
	_zt_guiManagerCheckAndGet(gm, gui_manager);
	gm->keyboard_focus = keyboard_focus;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiManagerHasKeyboardFocus(ztGuiManagerID gui_manager)
{
	_zt_guiManagerCheckAndGet(gm, gui_manager);
	return gm->keyboard_focus;
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

	gm->item_cache_used += 1;

	*id = item_id;
	return item;
}

// ------------------------------------------------------------------------------------------------

enum ztGuiWindowInternalFlags_Enum
{
	ztGuiWindowInternalFlags_Resizing = (1 << 31),
	ztGuiWindowInternalFlags_Collapsed = (1 << 30),
	ztGuiWindowInternalFlags_ScrollHorz = (1 << 29),
	ztGuiWindowInternalFlags_ScrollVert = (1 << 28),
};

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
				r32 title_offset = zt_bitIsSet(item->window.flags, ztGuiWindowFlags_AllowCollapse) ? theme->sprite_icon_collapse.half_size.x * 2.f + theme->window_title_padding_x : 0;

				if (zt_bitIsSet(item->window.flags, ztGuiWindowInternalFlags_Collapsed)) {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_window_collapsed, ztVec2(pos.x, pos.y + (item->size.y - theme->window_title_height) / 2.f), ztVec2(item->size.x, theme->window_title_height));
				}
				else {
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_window, pos, item->size);
				}

				if (item->label) {
					ztVec2 font_ext = zt_fontGetExtents(theme->font, item->label);
					ztVec2 font_pos = ztVec2(pos.x, pos.y + (item->size.y / 2.f) - (theme->window_title_height / 2.f));
					i32 font_align = 0, font_anchor = 0;

					if (zt_bitIsSet(theme->window_title_align, ztAlign_Left)) { font_pos.x = pos.x - (item->size.x / 2.f) + theme->window_title_padding_x + title_offset;  font_align |= ztAlign_Left; font_anchor |= ztAnchor_Left; }
					else if (zt_bitIsSet(theme->window_title_align, ztAlign_Right)) { font_pos.x = pos.x + (item->size.x / 2.f) - theme->window_title_padding_x; font_align |= ztAlign_Right; font_anchor |= ztAnchor_Right; }

					if (zt_bitIsSet(theme->window_title_align, ztAlign_Top)) { font_pos.y += (theme->window_title_height / 2.f) - theme->window_title_padding_y; font_align |= ztAlign_Top; font_anchor |= ztAnchor_Top; }
					else if (zt_bitIsSet(theme->window_title_align, ztAlign_Bottom)) { font_pos.y -= (theme->window_title_height / 2.f) - theme->window_title_padding_y; font_align |= ztAlign_Bottom; font_anchor |= ztAnchor_Bottom; }

					zt_drawListAddText2D(draw_list, theme->font, item->label, font_pos, font_align, font_anchor);
				}
			}
			else {
				zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_panel, pos, item->size);
			}

			if (zt_bitIsSet(item->window.flags, ztGuiWindowFlags_AllowResize) && !zt_bitIsSet(item->window.flags, ztGuiWindowInternalFlags_Collapsed)) {
				ztVec3 resize_pos(pos.x + ((item->size.x / 2) - (theme->sprite_icon_resize.half_size.x + theme->padding)), pos.y - ((item->size.y / 2) - (theme->sprite_icon_resize.half_size.y + theme->padding)), 0);

				zt_drawListAddSprite(draw_list, &theme->sprite_icon_resize, resize_pos);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (!item->window.drag_state.dragging) {
				if (input_mouse->leftJustPressed()) {
					if (zt_bitIsSet(item->window.flags, ztGuiWindowFlags_AllowResize)) {
						ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
						ztVec2 pos = zt_guiItemPositionLocalToScreen(item_id, ztVec2::zero);
						ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);

						ztVec2 resize_pos(pos.x + ((item->size.x / 2) - (theme->sprite_icon_resize.half_size.x + theme->padding)), pos.y - ((item->size.y / 2) - (theme->sprite_icon_resize.half_size.y + theme->padding)));
						ztVec2 resize_size(theme->sprite_icon_resize.half_size.x * 2 + theme->padding, theme->sprite_icon_resize.half_size.y * 2 + theme->padding);
						if (zt_collisionPointInRect(mpos, resize_pos, resize_size)) {
							item->window.flags |= ztGuiWindowInternalFlags_Resizing;
							item->window.resize[0] = item->window.resize[1] = 0;
							item->window.pos[0] = item->pos.x;
							item->window.pos[1] = item->pos.y;
							item->window.size[0] = item->size.x;
							item->window.size[1] = item->size.y;
						}
					}
				}
				else {
					zt_bitRemove(item->window.flags, ztGuiWindowInternalFlags_Resizing);
				}
			}
			if (zt_bitIsSet(item->window.flags, ztGuiWindowInternalFlags_Resizing)) {
				bool result = _zt_guiProcessDrag(&item->window.drag_state, gm, (ztVec2*)item->window.resize, input_mouse);
				item->pos.x = item->window.pos[0] + item->window.resize[0] / 2.f;
				item->pos.y = item->window.pos[1] + item->window.resize[1] / 2.f;
				item->size.x = item->window.size[0] + item->window.resize[0];
				item->size.y = item->window.size[1] - item->window.resize[1];

				zt_guiSizerRecalcImmediately(item->id);
				return result;
			}
			else {
				return _zt_guiProcessDrag(&item->window.drag_state, gm, &item->pos, input_mouse);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_BUTTON_PRESSED(onButtonClose)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, button_id);
			_zt_guiItemFromID(window, zt_guiItemGetTopLevelParent(button_id));

			if (zt_bitIsSet(window->window.flags, ztGuiWindowFlags_CloseHides)) {
				zt_guiItemHide(window->id);
			}
			else {
				zt_guiItemFree(window->id);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_BUTTON_PRESSED(onButtonToggle)
		{
			_zt_guiItemAndManagerReturnOnError(gm, button, button_id);
			_zt_guiItemFromID(window, zt_guiItemGetTopLevelParent(button_id));

			ztGuiTheme *theme = zt_guiItemGetTheme(window->id);
			if (zt_bitIsSet(window->window.flags, ztGuiWindowInternalFlags_Collapsed)) {
				zt_guiButtonSetIcon(window->window.button_expand_id, &theme->sprite_icon_collapse);
				zt_bitRemove(window->window.flags, ztGuiWindowInternalFlags_Collapsed);
				zt_guiItemShow(window->window.content_id);
			}
			else {
				zt_guiButtonSetIcon(window->window.button_expand_id, &theme->sprite_icon_expand);
				window->window.flags |= ztGuiWindowInternalFlags_Collapsed;
				zt_guiItemHide(window->window.content_id);
			}
		}
	};

	_zt_guiManagerGetFromItem(gm, ztInvalidID);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, ztInvalidID, ztGuiItemType_Window, ztGuiItemFlags_WantsInput | ztGuiItemFlags_WantsFocus | ztGuiItemFlags_Visible | ztGuiItemFlags_BringToFront /* | ztGuiItemFlags_ClipChildren*/, &item_id);
	if (!item) return ztInvalidID;


	if (zt_bitIsSet(flags, ztGuiWindowFlags_ShowTitle)) {
		ztGuiItemID sizer_main = zt_guiMakeSizer(item_id, ztGuiItemOrient_Vert);
		zt_guiSizerSizeToParent(sizer_main, true);
		zt_debugOnly(zt_guiItemSetName(sizer_main, "Window Main Sizer"));
		_zt_guiItemFromID(sizer_main_item, sizer_main);

		ztGuiItemID scroll_container = ztInvalidID;
		if (zt_bitIsSet(flags, ztGuiWindowInternalFlags_ScrollHorz) || zt_bitIsSet(flags, ztGuiWindowInternalFlags_ScrollVert)) {
			i32 sflags = (zt_bitIsSet(flags, ztGuiWindowInternalFlags_ScrollHorz) ? ztGuiItemOrient_Horz : 0) |
						 (zt_bitIsSet(flags, ztGuiWindowInternalFlags_ScrollVert) ? ztGuiItemOrient_Vert : 0);

			if (!zt_bitIsSet(flags, ztGuiWindowInternalFlags_ScrollHorz)) sflags |= ztGuiScrollContainerFlags_StretchHorz;
			if (!zt_bitIsSet(flags, ztGuiWindowInternalFlags_ScrollVert)) sflags |= ztGuiScrollContainerFlags_StretchVert;

			scroll_container = zt_guiMakeScrollContainer(sizer_main, sflags);
		}

		ztGuiItem *content = _zt_guiMakeItemBase(gm, sizer_main, ztGuiItemType_Panel, 0, &item->window.content_id);
		zt_debugOnly(zt_guiItemSetName(item->window.content_id, "Window Content Panel"));

		ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

		zt_guiSizerAddStretcher(sizer_main, 0, theme->window_title_height / 2.f);

		if (scroll_container != ztInvalidID) {
			zt_guiScrollContainerSetItem(scroll_container, item->window.content_id);
			zt_guiSizerAddItem(sizer_main, scroll_container, 1, 3 / zt_pixelsPerUnit());
		}
		else {
			zt_guiSizerAddItem(sizer_main, item->window.content_id, 1, 3 / zt_pixelsPerUnit());
		}

		r32 diff = theme->window_title_height - ((theme->sprite_icon_close.half_size.y + theme->button_padding_h) * 2.f);
		if (zt_bitIsSet(flags, ztGuiWindowFlags_AllowClose)) {
			ztGuiItemID button = zt_guiMakeButton(item_id, nullptr, ztGuiButtonFlags_NoBackground | ztGuiButtonFlags_OnPressDip);
			zt_debugOnly(zt_guiItemSetName(button, "Close Button"));
			zt_guiButtonSetCallback(button, local::onButtonClose);
			zt_guiButtonSetIcon(button, &theme->sprite_icon_close);

			zt_guiItemSetPosition(button, ztAlign_Right | ztAlign_Top, ztAnchor_Right | ztAnchor_Top, ztVec2(-theme->padding, diff / -2.f));
		}
		if (zt_bitIsSet(flags, ztGuiWindowFlags_AllowCollapse)) {
			item->window.button_expand_id = zt_guiMakeButton(item_id, nullptr, ztGuiButtonFlags_NoBackground | ztGuiButtonFlags_OnPressDip);
			zt_debugOnly(zt_guiItemSetName(item->window.button_expand_id, "Expand/Collapse Button"));
			zt_guiButtonSetCallback(item->window.button_expand_id, local::onButtonToggle);
			zt_guiButtonSetIcon(item->window.button_expand_id, &theme->sprite_icon_collapse);

			zt_guiItemSetPosition(item->window.button_expand_id, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(theme->padding, diff / -2.f));
		}
	}
	else {
		item->window.content_id = item_id;
	}

	item->functions.render = local::render;
	item->functions.user_data = gm;

	zt_guiItemSetSize(item_id, ztVec2(7, 5));
	zt_guiItemSetLabel(item_id, title);

	item->window.flags = flags;

	item->functions.input_mouse = local::inputMouse;

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeScrollWindow(const char *title, i32 scroll_dir, i32 flags)
{
	i32 scroll_flags = (zt_bitIsSet(scroll_dir, ztGuiItemOrient_Horz) ? ztGuiWindowInternalFlags_ScrollHorz : 0) |
					   (zt_bitIsSet(scroll_dir, ztGuiItemOrient_Vert) ? ztGuiWindowInternalFlags_ScrollVert : 0);

	return zt_guiMakeWindow(title, scroll_flags | flags);
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiWindowGetContentParent(ztGuiItemID window)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, window, ztGuiItemType_Window, ztInvalidID);
	return item->window.content_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakePanel(ztGuiItemID parent, i32 item_flags)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (zt_bitIsSet(item->flags, ztGuiPanelFlags_DrawBackground)) {
				ztVec2 pos = offset + item->pos;
				zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_panel, pos, item->size);
			}
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

ztGuiItemID zt_guiMakeCollapsingPanel(ztGuiItemID parent, const char *label)
{
	enum ztGuiCollapsingPanelInternalFlags_Enum
	{
		ztGuiCollapsingPanelInternalFlags_Collapsed = (1<<31),
		ztGuiCollapsingPanelInternalFlags_Recalc    = (1<<30),
	};

	struct local
	{
		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (zt_bitIsSet(item->flags, ztGuiCollapsingPanelInternalFlags_Recalc)) {
				zt_bitRemove(item->flags, ztGuiCollapsingPanelInternalFlags_Recalc);

				ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

				_zt_guiItemFromID(content_panel, item->collapsing_panel.content_panel_id);

				if (zt_bitIsSet(item->flags, ztGuiCollapsingPanelInternalFlags_Collapsed)) {
					item->size.y = theme->collapsing_panel_header_h;
					zt_guiItemHide(item->collapsing_panel.content_panel_id);
				}
				else {
					ztVec2 size = zt_guiSizerGetMinSize(item->collapsing_panel.content_panel_id);
					content_panel->size.x = item->size.x;
					content_panel->size.y = size.y;
					item->size.x = zt_max(item->size.x, size.x);
					item->size.y = theme->collapsing_panel_header_h + size.y;

					content_panel->pos.x = 0;
					content_panel->pos.y = -theme->collapsing_panel_header_h / 2.f;
					zt_guiItemShow(item->collapsing_panel.content_panel_id);

					//zt_guiSizerRecalcImmediately(content_panel->id);
				}

				zt_guiSizerRecalcImmediately(zt_guiItemGetTopLevelParent(item_id));
			}
			else if (zt_bitIsSet(item->flags, ztGuiItemFlags_Dirty)) {
				_zt_guiItemFromID(content_panel, item->collapsing_panel.content_panel_id);
				content_panel->size.x = item->size.x;
			}
		}

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			_zt_guiItemFromID(button, item->collapsing_panel.button_id);
			if (zt_bitIsSet(item->flags, ztGuiItemFlags_Dirty)) {
				zt_drawListReset(item->draw_list);

				ztVec2 pos(0, (item->size.y - theme->collapsing_panel_header_h) / 2.f);

				zt_drawListAddGuiThemeSprite(item->draw_list, &theme->sprite_collapsing_panel_header, pos, ztVec2(item->size.x, theme->collapsing_panel_header_h));
				pos.x = (item->size.x / -2.f) + button->size.x + theme->padding;
				//pos.y -= theme->collapsing_panel_header_h / 2.f;
//				ztVec2 pos((item->size.x / -2.f) + button->size.x + theme->padding, item->size.y / 2.f);
				zt_drawListAddText2D(item->draw_list, theme->font, item->label, pos, ztAlign_Left, ztAnchor_Left);

			}

			ztVec2 pos = offset + item->pos;
			zt_alignToPixel(&pos, zt_pixelsPerUnit());
			zt_drawListAddDrawList(draw_list, item->draw_list, ztVec3(pos, 0));

			pos.x += (item->size.x / -2.f) + button->size.x + theme->padding;
			pos.y += (item->size.y - theme->collapsing_panel_header_h) / 2.f;
			zt_drawListAddText2D(draw_list, theme->font, item->label, pos, ztAlign_Left, ztAnchor_Left);

		}

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(bestSize)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			ztVec2 ext = zt_fontGetExtents(theme->font, item->label);
			ztVec2 m_size = ext;
			m_size.x += theme->padding * 2;
			m_size.y = zt_max(m_size.y, theme->collapsing_panel_header_h);

			if (min_size) *min_size = m_size;
			if (size) {
				size->x = zt_max(size->x, m_size.x);
				size->y = zt_max(size->y, m_size.y);
			}
		}

		static  ZT_FUNC_GUI_BUTTON_PRESSED(onToggle)
		{
			_zt_guiItemAndManagerReturnOnError(gm, button, button_id);
			_zt_guiItemFromID(item, button->parent->id);

			ztGuiTheme *theme = zt_guiItemGetTheme(item->id);

			if (zt_bitIsSet(item->flags, ztGuiCollapsingPanelInternalFlags_Collapsed)) {
				zt_guiButtonSetIcon(item->collapsing_panel.button_id, &theme->sprite_icon_collapse);
				zt_bitRemove(item->flags, ztGuiCollapsingPanelInternalFlags_Collapsed);
			}
			else {
				zt_guiButtonSetIcon(item->collapsing_panel.button_id, &theme->sprite_icon_expand);
				item->flags |= ztGuiCollapsingPanelInternalFlags_Collapsed;
			}

			item->flags |= ztGuiCollapsingPanelInternalFlags_Recalc;
		}
	};

	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_CollapsingPanel, ztGuiCollapsingPanelInternalFlags_Collapsed, &item_id, (zt_strLen(label) * 2) + 19);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->collapsing_panel.button_id = zt_guiMakeButton(item_id, nullptr, ztGuiButtonFlags_NoBackground | ztGuiButtonFlags_OnPressDip);
	zt_guiItemSetName(item->collapsing_panel.button_id, "Collapse Button");
	zt_guiButtonSetIcon(item->collapsing_panel.button_id, &theme->sprite_icon_expand);
	zt_guiButtonSetCallback(item->collapsing_panel.button_id, local::onToggle);
	zt_guiItemSetPosition(item->collapsing_panel.button_id, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(0, -theme->padding));

	item->collapsing_panel.content_panel_id = zt_guiMakePanel(item_id, ztGuiPanelFlags_DrawBackground);
	zt_guiItemSetName(item->collapsing_panel.content_panel_id, "content-panel");

	zt_guiItemHide(item->collapsing_panel.content_panel_id);

	item->flags |= ztGuiCollapsingPanelInternalFlags_Recalc | ztGuiCollapsingPanelInternalFlags_Collapsed;

	zt_guiItemSetLabel(item_id, label);

	item->functions.update = local::update;
	item->functions.render = local::render;
	item->functions.best_size = local::bestSize;
	item->functions.user_data = gm;

	local::bestSize(item_id, nullptr, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiCollapsingPanelGetContentParent(ztGuiItemID panel_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, panel_id, ztGuiItemType_CollapsingPanel, ztInvalidID);
	return item->collapsing_panel.content_panel_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeStaticText(ztGuiItemID parent, const char *label, i32 flags, int max_chars)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (zt_bitIsSet(item->flags, ztGuiItemFlags_Dirty)) {
				if (item->draw_list) {
					ztVec2 ext = zt_bitIsSet(item->flags, ztGuiStaticTextFlags_Fancy) ? zt_fontGetExtentsFancy(theme->font, item->label) : zt_fontGetExtents(theme->font, item->label);
					ztVec2 off = ztVec2::zero;

					if (item->align_flags != 0) {
						if (zt_bitIsSet(item->align_flags, ztAlign_Left)) off.x -= (item->size.x - ext.x) / 2.f;
						if (zt_bitIsSet(item->align_flags, ztAlign_Right)) off.x += (item->size.x - ext.x) / 2.f;
						if (zt_bitIsSet(item->align_flags, ztAlign_Top)) off.y += (item->size.y - ext.y) / 2.f;
						if (zt_bitIsSet(item->align_flags, ztAlign_Bottom)) off.y -= (item->size.y - ext.y) / 2.f;
					}

					ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
					zt_drawListReset(item->draw_list);
					if (zt_bitIsSet(item->flags, ztGuiStaticTextFlags_Fancy)) {
						zt_drawListAddFancyText2D(item->draw_list, theme->font, item->label, off, item->align_flags, item->anchor_flags);
					}
					else {
						zt_drawListAddText2D(item->draw_list, theme->font, item->label, off, item->align_flags, item->anchor_flags);
					}
				}
			}

			ztVec3 pos(offset + item->pos, 0);
			zt_alignToPixel(&pos, zt_pixelsPerUnit());
			zt_drawListAddDrawList(draw_list, item->draw_list, pos);
		}

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
			*size = zt_bitIsSet(item->flags, ztGuiStaticTextFlags_Fancy) ? zt_fontGetExtentsFancy(theme->font, item->label) : zt_fontGetExtents(theme->font, item->label);
		}
	};

	_zt_guiManagerGetFromItem(gm, parent);
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_StaticText, flags, &item_id, zt_max(zt_strLen(label), max_chars) * 2);
	if (!item) return ztInvalidID;

	item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	zt_guiItemSetLabel(item_id, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
	zt_assert(theme);

	item->size = zt_bitIsSet(item->flags, ztGuiStaticTextFlags_Fancy) ? zt_fontGetExtentsFancy(theme->font, label) : zt_fontGetExtents(theme->font, label);

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
						item->button.on_pressed(item_id, item->button.on_pressed_user_data);
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
				bool highlighted = zt_bitIsSet(gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
				bool pressed = (highlighted && gm->item_has_mouse == item->id) || (!highlighted && zt_bitIsSet(item->button.flags, ztGuiButtonInternalFlags_IsToggled));
				if (!zt_bitIsSet(item->button.flags, ztGuiButtonFlags_NoBackground)) {
					zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_button, pos, item->size, highlighted, pressed);
				}
				ztVec2 text_pos = ztVec2::zero;
				if (pressed && zt_bitIsSet(item->button.flags, ztGuiButtonFlags_OnPressDip)) {
					text_pos.x += theme->button_dip_x;
					text_pos.y += theme->button_dip_y;
				}
				if (item->button.icon) {
					ztVec2 text_size = item->label ? zt_fontGetExtents(theme->font, item->label) : ztVec2::zero;
					ztVec2 content_size = ztVec2::zero;
					ztVec2 icon_size(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);
					ztVec2 icon_pos = text_pos;

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
	item->functions.cleanup = local::cleanup;
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

	if (item->button.icon == nullptr) {
		item->button.icon = zt_mallocStructArena(ztSprite, gm->arena);
	}
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

void zt_guiButtonSetCallback(ztGuiItemID button, zt_guiButtonPressed_Func on_pressed, void *user_data)
{
	_zt_guiItemFromID(item, button);
	zt_returnOnNull(item);
	zt_assert(item->type == ztGuiItemType_Button || item->type == ztGuiItemType_ToggleButton || item->type == ztGuiItemType_Checkbox || item->type == ztGuiItemType_RadioButton);

	item->button.on_pressed = on_pressed;
	item->button.on_pressed_user_data = user_data;
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

						bool neg_highlight = enabled && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegHighlight), neg_pressed = neg_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegPressed),
							 pos_highlight = enabled && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosHighlight), pos_pressed = pos_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosPressed);

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

						bool neg_highlight = enabled && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegHighlight), neg_pressed = neg_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_NegPressed),
							 pos_highlight = enabled && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosHighlight), pos_pressed = pos_highlight && zt_bitIsSet(item->flags, ztGuiSliderInternalFlags_PosPressed);

						zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_scrollbar_vert_button_neg, pos + ztVec2(0, item->size.y / 2.f - theme->scrollbar_button_w / 2.f), btn_size, neg_highlight, neg_pressed);
						zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_scrollbar_vert_button_pos, pos + ztVec2(0, item->size.y / -2.f + theme->scrollbar_button_w / 2.f), btn_size, pos_highlight, pos_pressed);
					}
				}
			}


			if (enabled) {
				bool highlight = item->slider.highlight && zt_bitIsSet(gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
				bool pressed = item->slider.drag_state.dragging;
				ztGuiThemeButtonSprite *sprite_handle = item->slider.orient == ztGuiItemOrient_Horz ? (item->type == ztGuiItemType_Slider ? &theme->sprite_slider_horz_handle : &theme->sprite_scrollbar_horz_handle) : (item->type == ztGuiItemType_Slider ? &theme->sprite_slider_vert_handle : &theme->sprite_scrollbar_vert_handle);
				zt_drawListAddGuiThemeButtonSprite(draw_list, sprite_handle, handle_pos, handle_size, highlight, pressed);
			}
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

	item->slider.handle_pct = zt_clamp(percent, 0, 1);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiScrollContainerCalcViewportSizePos(ztGuiManager *gm, ztGuiItem *item, ztVec2 *pposition, ztVec2 *psize)
{
	if (item->size == ztVec2::zero) {
		return;
	}

	ztVec2 size = *psize;
	ztVec2 position = *pposition;

	if (item->scrolled_container.contained_item == ztInvalidID) {
		return;
	}

	bool horz_vis = zt_bitIsSet(item->flags, ztGuiScrollContainerFlags_ShowScrollHorz);
	bool horz_vis_disabled = horz_vis;
	if (size.x < gm->item_cache[item->scrolled_container.contained_item].size.x) {
		horz_vis = true;
		horz_vis_disabled = false;
	}
	else {
		zt_bitRemove(gm->item_cache[item->scrolled_container.scrollbar_horz].flags, ztGuiItemFlags_Visible);
	}
	if (horz_vis) {
		gm->item_cache[item->scrolled_container.scrollbar_horz].flags |= ztGuiItemFlags_Visible;
	}

	bool vert_vis = zt_bitIsSet(item->flags, ztGuiScrollContainerFlags_ShowScrollVert);
	bool vert_vis_disabled = vert_vis;
	if (size.y < gm->item_cache[item->scrolled_container.contained_item].size.y) {
		vert_vis = true;
		vert_vis_disabled = false;
	}
	else {
		zt_bitRemove(gm->item_cache[item->scrolled_container.scrollbar_vert].flags, ztGuiItemFlags_Visible);
	}
	if (vert_vis) {
		gm->item_cache[item->scrolled_container.scrollbar_vert].flags |= ztGuiItemFlags_Visible;
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
	if (item->scrolled_container.scroll_amt_horz != ztInvalidID) {
		zt_guiItemEnable(item->scrolled_container.scrollbar_horz, !horz_vis_disabled);
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
	if (item->scrolled_container.scroll_amt_vert != ztInvalidID) {
		zt_guiItemEnable(item->scrolled_container.scrollbar_vert, !vert_vis_disabled);
	}

	*pposition = position;
	*psize = size;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeScrollContainer(ztGuiItemID parent, i32 flags)
{
	struct local
	{
		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (item->scrolled_container.contained_item == ztInvalidID || !zt_guiItemIsShowing(item_id)) {
				return;
			}

			ztGuiTheme *theme = zt_guiItemGetTheme(item_id);
			ztGuiItem *contained = &gm->item_cache[item->scrolled_container.contained_item];

			ztVec2 size = item->size;
			ztVec2 pos = item->pos;
			ztVec2 orig_pos = pos;
			ztVec2 orig_size = contained->size;

			_zt_guiScrollContainerCalcViewportSizePos(gm, item, &pos, &size);
			item->scrolled_container.viewport_pos[0] = pos.x - orig_pos.x;
			item->scrolled_container.viewport_pos[1] = pos.y - orig_pos.y;
			item->scrolled_container.viewport_size[0] = size.x;
			item->scrolled_container.viewport_size[1] = size.y;

			zt_guiItemSetSize(item->scrolled_container.viewport, size);
			zt_guiItemSetPosition(item->scrolled_container.viewport, ztVec2(item->scrolled_container.viewport_pos[0], item->scrolled_container.viewport_pos[1]));


			if (zt_bitIsSet(item->flags, ztGuiScrollContainerFlags_StretchVert)) {
				contained->size.y = size.y - theme->scroll_container_padding_y * 2;
			}
			if (zt_bitIsSet(item->flags, ztGuiScrollContainerFlags_StretchHorz)) {
				contained->size.x = size.x - theme->scroll_container_padding_x * 2;
			}

			r32 horz_amt = (item->scrolled_container.scrollbar_horz == ztInvalidID || !zt_guiItemIsVisible(item->scrolled_container.scrollbar_horz) || !zt_guiItemIsEnabled(item->scrolled_container.scrollbar_horz)) ? 0 : item->scrolled_container.scroll_amt_horz;
			r32 vert_amt = (item->scrolled_container.scrollbar_vert == ztInvalidID || !zt_guiItemIsVisible(item->scrolled_container.scrollbar_vert) || !zt_guiItemIsEnabled(item->scrolled_container.scrollbar_vert)) ? 0 : item->scrolled_container.scroll_amt_vert;

			contained->pos.x = (((size.x - contained->size.x) / -2.f) + theme->scroll_container_padding_x) - (horz_amt * ((contained->size.x - size.x) + theme->scroll_container_padding_x * 2));
			contained->pos.y = (((size.y - contained->size.y) /  2.f) - theme->scroll_container_padding_y) + (vert_amt * ((contained->size.y - size.y) + theme->scroll_container_padding_y * 2));

			gm->item_cache[item->scrolled_container.viewport].flags |= ztGuiItemFlags_ClipChildren;
			gm->item_cache[item->scrolled_container.viewport].clip_area = ztVec4(0, 0, size.x - theme->scroll_container_padding_x * 2, size.y - theme->scroll_container_padding_y * 2);

			if (contained->size != orig_size) {
				zt_guiSizerRecalc(contained->id);
			}
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
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_ScrollContainer, ztGuiItemFlags_ClipChildren | flags, &item_id);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->scrolled_container.scrollbar_horz = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Horz, &item->scrolled_container.scroll_amt_horz);
	item->scrolled_container.scrollbar_vert = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Vert, &item->scrolled_container.scroll_amt_vert);
	item->scrolled_container.viewport = zt_guiMakePanel(item_id, ztGuiItemFlags_Visible | ztGuiItemFlags_ClipChildren | ztGuiPanelFlags_DrawBackground);
	item->scrolled_container.contained_item = ztInvalidID;
	item->scrolled_container.scroll_amt_vert = 0;
	item->scrolled_container.scroll_amt_horz = 0;
	item->scrolled_container.viewport_pos[0] = 0;
	item->scrolled_container.viewport_pos[1] = 0;
	item->scrolled_container.viewport_size[0] = 0;
	item->scrolled_container.viewport_size[1] = 0;

	zt_debugOnly(zt_guiItemSetName(item->scrolled_container.scrollbar_horz, "Horz Scrollbar"));
	zt_debugOnly(zt_guiItemSetName(item->scrolled_container.scrollbar_vert, "Vert Scrollbar"));
	zt_debugOnly(zt_guiItemSetName(item->scrolled_container.viewport, "Viewport"));

	//zt_debugOnly(item->debug_highlight = ztVec4(1, 0, 0, 1));
	//zt_debugOnly(gm->item_cache[item->scrolled_container.viewport].debug_highlight = ztVec4(0, 1, 0, 1));


	item->functions.input_mouse = local::inputMouse;
	item->functions.input_key = local::inputKey;
	item->functions.update = local::update;
	//item->functions.render = local::render;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	ztVec2 min_size = ztVec2::zero;
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

void zt_guiScrollContainerSetScroll(ztGuiItemID scroll, ztGuiItemOrient_Enum orient, r32 value)
{
	_zt_guiItemTypeFromIDReturnOnError(item, scroll, ztGuiItemType_ScrollContainer);

	if (orient == ztGuiItemOrient_Horz) {
		item->scrolled_container.scroll_amt_horz = value;
	}
	else {
		item->scrolled_container.scroll_amt_vert = value;
	}
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

ztInternal void _zt_guiTextEditSizeContent(ztGuiItem *item, ztGuiTheme *theme)
{
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

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditAdjustViewForCursor(ztGuiItem *item)
{
	_zt_guiManagerGetFromItem(gm, item->id);
	ztGuiTheme *theme = zt_guiItemGetTheme(item->id);

	if (item->textedit.content_size[0] == 0 && item->textedit.content_size[1] == 0) {
		_zt_guiTextEditSizeContent(item, theme);
	}

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
		item->textedit.scroll_amt_horz = x_diff == 0 ? 0 : zt_clamp(item->textedit.scroll_amt_horz - (diff / x_diff), 0, 1);
	}
	if (cursor_pos_end.x > item->clip_area.x + item->clip_area.z / 2.f) {
		r32 diff = cursor_pos_end.x - (item->clip_area.x + item->clip_area.z / 2.f);
		item->textedit.scroll_amt_horz = x_diff == 0 ? 0 : zt_clamp((diff / x_diff) + item->textedit.scroll_amt_horz, 0, 1);
	}

	if (cursor_pos_beg.y > item->clip_area.y + item->clip_area.w / 2.f) {
		r32 diff = cursor_pos_beg.y - (item->clip_area.y + item->clip_area.w / 2.f);
		item->textedit.scroll_amt_vert = y_diff == 0 ? 0 : zt_clamp(item->textedit.scroll_amt_vert - (diff / y_diff), 0, 1);
	}
	if (cursor_pos_end.y < item->clip_area.y - item->clip_area.w / 2.f) {
		r32 diff = (item->clip_area.y - item->clip_area.w / 2.f) - cursor_pos_end.y;
		item->textedit.scroll_amt_vert = y_diff == 0 ? 0 : zt_clamp((diff / y_diff) + item->textedit.scroll_amt_vert, 0, 1);
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

ztInternal void _zt_guiTextEditGetCurrentLineInfo(ztGuiItem *item, int *beg_pos, int *end_pos, int from_pos = -1)
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

ztInternal void _zt_guiTextEditRecalcCursor(ztGuiItem *item)
{
	ztGuiTheme *theme = zt_guiItemGetTheme(item->id);
	int beg_line = 0;
	_zt_guiTextEditGetCurrentLineInfo(item, &beg_line, nullptr);
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

ztGuiItemID zt_guiMakeTextEdit(ztGuiItemID parent, const char *value, i32 flags, i32 buffer_size)
{
	static const char *word_separators = " \t";
	static const int word_separators_len = zt_strLen(word_separators);

	struct local
	{
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
			_zt_guiTextEditGetCurrentLineInfo(item, &beg_line, nullptr);
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
			_zt_guiTextEditGetCurrentLineInfo(item, &beg_line, &end_line);
			if (end_line < str_len) {
				int chars_in = item->textedit.cursor_pos - beg_line;

				item->textedit.cursor_pos = zt_min(end_line + 1, str_len);

				int nbeg_line = 0, nend_line = 0;
				_zt_guiTextEditGetCurrentLineInfo(item, &nbeg_line, &nend_line);

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

		static ZT_FUNC_GUI_ITEM_INPUT_KEY(inputKey)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (item->textedit.on_key) {
				bool should_process = true;
				item->textedit.on_key(item_id, input_keys, input_key_strokes, &should_process);
				if (!should_process) {
					return false;
				}
			}

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
			if (input_keys[ztInputKeys_Up].justPressedOrRepeated() && zt_bitIsSet(item->flags, ztGuiTextEditFlags_MultiLine)) {
				recalc_cursor = true;
				item->textedit.cursor_pos = posAboveChar(item);
			}
			if (input_keys[ztInputKeys_Down].justPressedOrRepeated() && zt_bitIsSet(item->flags, ztGuiTextEditFlags_MultiLine)) {
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
					_zt_guiTextEditGetCurrentLineInfo(item, &beg_line, nullptr);
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
					_zt_guiTextEditGetCurrentLineInfo(item, &beg_line, &end_line);
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
				str_len = zt_strLen(item->textedit.text_buffer);
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
				str_len = zt_strLen(item->textedit.text_buffer);
				_zt_guiTextEditCacheText(item);
			}

			if (shifting) {
				selectEnd(item);
			}

			int keys = 0;
			zt_fiz(input_key_strokes) {
				if (input_key_strokes[i] == ztInputKeys_Invalid) break;

				if (input_keys[input_key_strokes[i]].display != 0) {
					if (item->textedit.select_beg != item->textedit.select_end) {
						int offset = zt_max(item->textedit.select_beg, item->textedit.select_end) - zt_min(item->textedit.select_beg, item->textedit.select_end);
						for (int i = zt_min(item->textedit.select_beg, item->textedit.select_end); i <= str_len; ++i) {
							item->textedit.text_buffer[i] = item->textedit.text_buffer[i + offset];
						}
						item->textedit.cursor_pos = zt_min(item->textedit.select_beg, item->textedit.select_end);
						item->textedit.select_beg = item->textedit.select_end = -1;
						str_len = zt_strLen(item->textedit.text_buffer);
					}

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
					item->textedit.text_buffer[item->textedit.cursor_pos++] = shifting ? input_keys[input_key_strokes[i]].shift_display : input_keys[input_key_strokes[i]].display;
					recalc_cursor = true;
					keys += 1;
				}
			}

			if (recalc_cursor) {
				if (!shifting || keys > 0) {
					item->textedit.select_beg = -1;
					item->textedit.select_end = -1;
				}
				item->textedit.cursor_vis = true;

				_zt_guiTextEditRecalcCursor(item);
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
			_zt_guiTextEditGetCurrentLineInfo(item, &beg_pos, &end_pos, idx);

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
				_zt_guiTextEditRecalcCursor(item);

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
				_zt_guiTextEditRecalcCursor(item);
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
				_zt_guiTextEditSizeContent(item, theme);
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
			ztVec3 dlpos(text_pos, 0);
			zt_alignToPixel(&dlpos, zt_pixelsPerUnit());
			zt_drawListAddDrawList(draw_list, item->draw_list, dlpos);
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
		item->textedit.scrollbar_horz = zt_guiMakeScrollbar(item_id, ztGuiItemOrient_Horz, &item->textedit.scroll_amt_horz);
		zt_bitRemove(gm->item_cache[item->textedit.scrollbar_horz].flags, ztGuiItemFlags_Visible);

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
	item->textedit.select_beg = item->textedit.select_end = -1;
	_zt_guiTextEditRecalcCursor(item);
	_zt_guiTextEditAdjustViewForCursor(item);
	_zt_guiTextEditCacheText(item);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetSelection(ztGuiItemID text, int sel_beg, int sel_end)
{
	_zt_guiItemTypeFromIDReturnOnError(item, text, ztGuiItemType_TextEdit);
	int str_len = zt_strLen(item->textedit.text_buffer);

	item->textedit.select_beg = zt_clamp(sel_beg, 0, str_len);
	item->textedit.select_end = zt_clamp(sel_end, 0, str_len);
	item->textedit.cursor_pos = zt_clamp(sel_end, 0, str_len);
	_zt_guiTextEditRecalcCursor(item);
	_zt_guiTextEditAdjustViewForCursor(item);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditGetSelection(ztGuiItemID text, int *sel_beg, int *sel_end)
{
	_zt_guiItemTypeFromIDReturnOnError(item, text, ztGuiItemType_TextEdit);

	*sel_beg = item->textedit.select_beg;
	*sel_end = item->textedit.select_end;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSelectAll(ztGuiItemID text)
{
	_zt_guiItemTypeFromIDReturnOnError(item, text, ztGuiItemType_TextEdit);
	zt_guiTextEditSetSelection(item->id, 0, zt_strLen(item->textedit.text_buffer));
}

// ------------------------------------------------------------------------------------------------

int zt_guiTextEditGetCursorPos(ztGuiItemID text)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, text, ztGuiItemType_TextEdit, -1);
	return item->textedit.cursor_pos;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetCursorPos(ztGuiItemID text, int cursor_pos)
{
	_zt_guiItemTypeFromIDReturnOnError(item, text, ztGuiItemType_TextEdit);
	item->textedit.cursor_pos = zt_clamp(cursor_pos, 0, zt_strLen(item->textedit.text_buffer));
	_zt_guiTextEditRecalcCursor(item);
	_zt_guiTextEditAdjustViewForCursor(item);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetCallback(ztGuiItemID text, zt_guiTextEditKey_Func* on_key)
{
	_zt_guiItemTypeFromIDReturnOnError(item, text, ztGuiItemType_TextEdit);
	item->textedit.on_key = on_key;
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

ztInternal ztGuiItemID _zt_guiMakeMenuBase( ztGuiItemID parent_id )
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
				else if (item->menu.selected != -1) {
					if (item->menu.on_selected) {
						item->menu.on_selected(item->id, item->menu.ids[item->menu.selected], item->menu.user_datas[item->menu.selected]);
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

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(bestSize)
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
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent_id, ztGuiItemType_Menu, /*ztGuiItemFlags_ClipContents |*/ ztGuiItemFlags_WantsFocus | ztGuiItemFlags_BringToFront, &item_id);
	if (!item) return ztInvalidID;

	zt_guiItemHide(item_id);

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	int max_menu = ztGuiMenuMaxMenuItems;
	i32 size = (zt_sizeof(char *) + zt_sizeof(i32) + zt_sizeof(ztGuiItemID) + zt_sizeof(ztSprite*) + zt_sizeof(void*)) * max_menu;
	byte *mem = zt_mallocStructArrayArena(byte, size, gm->arena);

	item->menu.display = (ztString*)mem;
	mem += max_menu * zt_sizeof(ztString);
	item->menu.ids = (i32*)mem;
	mem += max_menu * zt_sizeof(i32);
	item->menu.submenus = (ztGuiItemID*)mem;
	mem += max_menu * zt_sizeof(ztGuiItemID);
	item->menu.icons = (ztSprite**)mem;
	mem += max_menu * zt_sizeof(ztSprite*);
	item->menu.user_datas = (void**)mem;

	item->menu.item_count = 0;
	item->menu.highlighted = -1;
	item->menu.just_opened = false;
	item->menu.on_selected = nullptr;

	item->functions.cleanup = local::cleanup;
	item->functions.update = local::update;
	item->functions.input_mouse = local::inputMouse;
	item->functions.render = local::render;
	item->functions.best_size = local::bestSize;
	item->functions.user_data = gm;

	ztVec2 min_size;
	local::bestSize(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeMenu()
{
	return _zt_guiMakeMenuBase(ztInvalidID);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppend(ztGuiItemID menu, const char *label, i32 id, void *user_data, ztSprite *icon)
{
	_zt_guiItemTypeFromIDReturnOnError(item, menu, ztGuiItemType_Menu);
	_zt_guiManagerGetFromItem(gm, menu);

	zt_assert(item->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = item->menu.item_count++;
	item->menu.display[idx] = zt_stringMakeFrom(label, gm->arena);
	item->menu.ids[idx] = id;
	item->menu.submenus[idx] = ztInvalidID;
	item->menu.user_datas[idx] = user_data;

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
	item->menu.user_datas[idx] = nullptr;

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

ztInternal void _zt_guiTreeCalculateSize(ztGuiItem *item)
{
	_zt_guiItemFromID(content, item->tree.content_id);
	content->size = ztVec2::zero;

	struct local
	{
		static void hideAll(ztGuiItem::ztTreeItem *tree_entry)
		{
			zt_guiItemHide(tree_entry->control_button_id);
			zt_guiItemHide(tree_entry->item_id);

			ztGuiItem::ztTreeItem *child = tree_entry->first_child;
			while (child) {
				hideAll(child);
				child = child->next;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void addToSize(ztGuiItem::ztTreeItem *tree_entry, ztGuiTheme *theme, ztVec2 *size, r32 indent_size, int *shown_items)
		{
			_zt_guiItemFromID(tree_item, tree_entry->item_id);

			if (tree_item->size.x + indent_size > size->x) {
				_zt_guiItemFromID(button, tree_entry->control_button_id);
				r32 icon_size = button->size.x;;
				size->x = tree_item->size.x + indent_size + icon_size + theme->padding * 2;
			}

			size->y += tree_item->size.y;

			shown_items += 1;

			if (tree_entry->expanded) {
				ztGuiItem::ztTreeItem *child = tree_entry->first_child;
				while (child) {
					addToSize(child, theme, size, indent_size + theme->tree_indent, shown_items);
					child = child->next;
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void reposition(ztGuiItem::ztTreeItem *tree_entry, ztGuiTheme *theme, r32 x, r32* y, r32 w, r32 indent_size)
		{
			_zt_guiItemFromID(tree_item, tree_entry->item_id);

			tree_item->flags |= ztGuiItemFlags_Visible;
			tree_item->pos.x = x + indent_size + (tree_item->size.x / 2);

			ztVec2 size = tree_item->size;
			if (tree_entry->control_button_id != ztInvalidID && tree_entry->first_child != nullptr) {
				_zt_guiItemFromID(button, tree_entry->control_button_id);
				//size.y = zt_max(size.y, button->size.y);

				button->flags |= ztGuiItemFlags_Visible;
				button->pos.x = x + indent_size - theme->tree_indent;
				button->pos.y = *y - size.y / 2;

				//tree_item->pos.x += button->size.x;
			}

			tree_item->pos.y = *y - size.y / 2;

			*y -= size.y;

			if (tree_entry->expanded) {
				ztGuiItem::ztTreeItem *child = tree_entry->first_child;
				while (child) {
					reposition(child, theme, x, y, w, indent_size + theme->tree_indent);
					child = child->next;
				}
			}
		}
	};

	ztGuiItem::ztTreeItem *child = item->tree.root_item->first_child;
	while (child) {
		local::hideAll(child);
		child = child->next;
	}

	int shown_items = 0;
	ztVec2 size = ztVec2::zero;

	ztGuiTheme *theme = zt_guiItemGetTheme(item->id);
	child = item->tree.root_item->first_child;
	while (child) {
		local::addToSize(child, theme, &size, 0, &shown_items);
		child = child->next;
	}

	size.y += theme->scroll_container_padding_y * 2;

	r32 x = (theme->padding * 2) + size.x / -2;
	r32 y = size.y / 2;

	child = item->tree.root_item->first_child;
	while (child) {
		local::reposition(child, theme, x, &y, size.x, theme->tree_indent);
		child = child->next;
	}

	content->size = size;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeTree(ztGuiItemID parent, i32 max_items)
{
	struct local
	{
		// ------------------------------------------------------------------------------------------------

		static ztGuiItem::ztTreeItem *mouseIntersecting(ztGuiItem::ztTreeItem *root, ztVec2& mpos, ztVec2& pos, ztVec2& size)
		{
			if (root->item_id != ztInvalidID) {
				_zt_guiItemFromID(item, root->item_id);

				size.y = item->size.y;

				if (zt_collisionPointInRect(mpos, pos, size)) {
					return root;
				}

				pos.y -= size.y;

				if (root->expanded == false) {
					return nullptr;
				}
			}

			ztGuiItem::ztTreeItem *child = root->first_child;
			while (child) {
				ztGuiItem::ztTreeItem *intersecting = mouseIntersecting(child, mpos, pos, size);
				if (intersecting) {
					return intersecting;
				}
				child = child->next;
			}

			return nullptr;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (input_mouse->leftJustReleased() && item->tree.root_item->first_child) {
				ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
				ztVec2 pos = zt_guiItemPositionLocalToScreen(item->tree.content_id, ztVec2::zero);

				_zt_guiItemFromID(first_item, item->tree.root_item->first_child->item_id);

				_zt_guiItemFromID(content, item->tree.content_id);
				pos.y += content->size.y / 2.f - first_item->size.y / 2.f;
				pos.x -= (content->size.x - item->size.x) / 2.f;

				ztVec2 size(item->size.x, 0);
				ztGuiItem::ztTreeItem *intersecting = mouseIntersecting(item->tree.root_item, mpos, pos, size);
				if (intersecting) {
					if (item->tree.active_item != intersecting) {
						item->tree.active_item = intersecting;
						if (item->tree.on_item_sel) {
							item->tree.on_item_sel(item_id, intersecting->node_id, item->tree.on_item_sel_user_data);
						}
					}
				}				
			}

			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (zt_bitIsSet(item->flags, ztGuiItemFlags_Dirty)) {
				_zt_guiTreeCalculateSize(item);

				_zt_guiItemFromID(container, item->tree.container_id);
				container->size = item->size;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;

			zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_tree_background, pos, item->size);

			if (item->tree.active_item != nullptr) {
				bool visible = true;
				ztGuiItem::ztTreeItem *parent = item->tree.active_item->parent;
				while (parent) {
					if (!parent->expanded) {
						visible = false;
						break;
					}
					parent = parent->parent;
				}
				if (visible) {
					_zt_guiItemFromID(active, item->tree.active_item->item_id);
					ztVec2 npos = zt_guiItemPositionLocalToScreen(active->id, ztVec2::zero);
					zt_drawListAddGuiThemeSprite(draw_list, &theme->sprite_tree_highlight, npos, active->size);
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			zt_freeArena(item->tree.arena, gm->arena);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
		}
	};


	ztGuiManager *gm = zt_gui->gui_managers[zt_gui->active_gui_manager];
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Tree, ztGuiItemFlags_WantsFocus | ztGuiItemFlags_ClipContents, &item_id);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->tree.container_id = zt_guiMakeScrollContainer(item_id);
	item->tree.content_id = zt_guiMakePanel(parent, 0);
	zt_guiScrollContainerSetItem(item->tree.container_id, item->tree.content_id);

	item->tree.arena = zt_memMakeArena(max_items * zt_sizeof(ztGuiItem::ztTreeItem), gm->arena);
	item->tree.last_id = -1;

	item->tree.root_item = zt_mallocStructArena(ztGuiItem::ztTreeItem, item->tree.arena);
	zt_memSet(item->tree.root_item, zt_sizeof(ztGuiItem::ztTreeItem), 0);
	item->tree.root_item->expanded = true;
	item->tree.root_item->node_id = ++item->tree.last_id;
	item->tree.root_item->item_id = ztInvalidID;
	item->tree.root_item->control_button_id = ztInvalidID;

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

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItemID tree_id, const char *item, void *user_data, ztGuiTreeNodeID parent_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(tree, tree_id, ztGuiItemType_Tree, false);

	ztGuiItemID item_id = zt_guiMakeStaticText(tree->tree.content_id, item);
	return zt_guiTreeAppend(tree_id, item_id, user_data, parent_id);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem::ztTreeItem *_zt_guiTreeFindNode(ztGuiItem *tree, ztGuiItem::ztTreeItem *root, ztGuiTreeNodeID node_id)
{
	if (root->node_id == node_id) {
		return root;
	}

	ztGuiItem::ztTreeItem *child = root->first_child;
	while (child) {
		ztGuiItem::ztTreeItem *result = _zt_guiTreeFindNode(tree, child, node_id);
		if (result) return result;
		child = child->next;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItemID tree_id, ztGuiItemID item, void *user_data, ztGuiTreeNodeID parent_id)
{
	struct local
	{
		static bool toggleItem(ztGuiItem *tree, ztGuiItem::ztTreeItem *root, ztGuiItemID button_id)
		{
			if (root->control_button_id == button_id) {
				root->expanded = !root->expanded;
				tree->flags |= ztGuiItemFlags_Dirty;

				ztGuiTheme *theme = zt_guiItemGetTheme(button_id);
				zt_guiButtonSetIcon(button_id, root->expanded ? &theme->sprite_tree_collapse : &theme->sprite_tree_expand);
				return true;
			}
			else {
				ztGuiItem::ztTreeItem *child = root->first_child;
				while (child) {
					if (toggleItem(tree, child, button_id)) {
						return true;
					}
					child = child->next;
				}
				return false;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_BUTTON_PRESSED(onToggle)
		{
			ztGuiItem *tree = (ztGuiItem*)user_data;
			toggleItem(tree, tree->tree.root_item, button_id);
		}

		// ------------------------------------------------------------------------------------------------

		static ztGuiItem::ztTreeItem *appendItem(ztGuiItem *tree, ztGuiItem::ztTreeItem *root, ztGuiTreeNodeID parent_node)
		{
			if (parent_node != ztInvalidID && parent_node != root->node_id) {
				ztGuiItem::ztTreeItem *node = root->first_child;
				while (node) {
					auto *tree_item = appendItem(tree, node, parent_node);
					if (tree_item) {
						return tree_item;
					}
					node = node->next;
				}
				return nullptr;
			}

			ztGuiItem::ztTreeItem *tree_item = zt_mallocStructArena(ztGuiItem::ztTreeItem, tree->tree.arena);
			zt_memSet(tree_item, zt_sizeof(ztGuiItem::ztTreeItem), 0);

			tree_item->node_id = ++tree->tree.last_id;
			tree_item->expanded = true;
			tree_item->parent = root;
			
			tree_item->control_button_id = zt_guiMakeButton(tree->tree.content_id, nullptr, ztGuiButtonFlags_NoBackground | ztGuiButtonFlags_OnPressDip);
	
			ztGuiTheme *theme = zt_guiItemGetTheme(tree->id);
			zt_guiButtonSetIcon(tree_item->control_button_id, &theme->sprite_tree_collapse);
			zt_guiButtonSetCallback(tree_item->control_button_id, local::onToggle, tree);
			zt_guiItemSetSize(tree_item->control_button_id, theme->sprite_tree_collapse.half_size * ztVec2(2, 2));

			zt_singleLinkAddToEnd(root->first_child, tree_item);

			return tree_item;
		}
	};

	_zt_guiItemTypeFromIDReturnValOnError(tree, tree_id, ztGuiItemType_Tree, false);

	zt_guiItemReparent(item, tree->tree.content_id);

	ztGuiItem::ztTreeItem *tree_item = local::appendItem(tree, tree->tree.root_item, parent_id);
	if (tree_item == nullptr) {
		return ztInvalidID;
	}

	tree_item->item_id = item;
	tree_item->user_data = user_data;

	if (!zt_bitIsSet(tree->flags, ztGuiItemFlags_Locked)) {
		_zt_guiTreeCalculateSize(tree);
	}

	return tree_item->node_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeGetSelected(ztGuiItemID tree_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(tree, tree_id, ztGuiItemType_Tree, ztInvalidID);
	return tree->tree.active_item ? tree->tree.active_item->node_id : ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTreeSetSelected(ztGuiItemID tree_id, ztGuiTreeNodeID node)
{
	struct local
	{
		static bool findAndSelect(ztGuiItem *tree, ztGuiItem::ztTreeItem *tree_item, ztGuiTreeNodeID node)
		{
			if (tree_item->item_id == node) {
				tree->tree.active_item = tree_item;
				return true;
			}

			ztGuiItem::ztTreeItem *child = tree_item->first_child;
			while (child) {
				if (findAndSelect(tree, child, node)) {
					return true;
				}
				child = child->next;
			}

			return false;
		}
	};
	_zt_guiItemTypeFromIDReturnOnError(tree, tree_id, ztGuiItemType_Tree);
	local::findAndSelect(tree, tree->tree.root_item, node);
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeGetRoot(ztGuiItemID tree_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(tree, tree_id, ztGuiItemType_Tree, ztInvalidID);
	return 0;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiTreeGetNodeItem(ztGuiItemID tree_id, ztGuiTreeNodeID node)
{
	_zt_guiItemTypeFromIDReturnValOnError(tree, tree_id, ztGuiItemType_Tree, ztInvalidID);

	ztGuiItem::ztTreeItem *tree_item = _zt_guiTreeFindNode(tree, tree->tree.root_item, node);
	return tree_item ? tree_item->item_id : ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

void *zt_guiTreeGetNodeUserData(ztGuiItemID tree_id, ztGuiTreeNodeID node)
{
	_zt_guiItemTypeFromIDReturnValOnError(tree, tree_id, ztGuiItemType_Tree, nullptr);

	ztGuiItem::ztTreeItem *tree_item = _zt_guiTreeFindNode(tree, tree->tree.root_item, node);
	return tree_item ? tree_item->user_data : nullptr;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTreeSetCallback(ztGuiItemID tree_id, zt_guiTreeItemSelected_Func on_item_sel, void *user_data)
{
	_zt_guiItemTypeFromIDReturnOnError(tree, tree_id, ztGuiItemType_Tree);

	tree->tree.on_item_sel = on_item_sel;
	tree->tree.on_item_sel_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTreeClear(ztGuiItemID tree_id)
{
	_zt_guiItemTypeFromIDReturnOnError(tree, tree_id, ztGuiItemType_Tree);

	struct local
	{
		static void clear(ztMemoryArena *arena, ztGuiItem::ztTreeItem *tree_item)
		{
			if (tree_item->control_button_id != ztInvalidID) {
				zt_guiItemFree(tree_item->control_button_id);
				tree_item->control_button_id = ztInvalidID;
			}
			if (tree_item->item_id != ztInvalidID) {
				zt_guiItemFree(tree_item->item_id);
				tree_item->item_id = ztInvalidID;
			}

			ztGuiItem::ztTreeItem *child = tree_item->first_child;
			while (child) {
				clear(arena, child);
				child = child->next;
			}

			tree_item->first_child = nullptr;
			tree_item->next = nullptr;
			
			if (tree_item->parent) { // don't clear the root item, we need it for later
				zt_freeArena(tree_item, arena);
			}
		}
	};

	local::clear(tree->tree.arena, tree->tree.root_item);
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeComboBox(ztGuiItemID parent, i32 max_items)
{
	enum ztGuiComboBoxInternalFlags_Enum
	{
		ztGuiComboBoxInternalFlags_IgnorePopup = (1<<31),
	};

	struct local
	{
		static ZT_FUNC_GUI_ITEM_INPUT_MOUSE(inputMouse)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (input_mouse->leftJustPressed()) {
				if (zt_guiItemIsVisible(item->combobox.popup_id)) {
					item->flags |= ztGuiComboBoxInternalFlags_IgnorePopup;
				}
			}
			else if (input_mouse->leftJustReleased()) {
				if (!zt_bitIsSet(item->flags, ztGuiComboBoxInternalFlags_IgnorePopup)) {
					if (item->combobox.popup_id != ztInvalidID) {
						_zt_guiItemFromID(menu, item->combobox.popup_id);
						menu->size.x = item->size.x;

						zt_guiMenuPopupAtItem(item->combobox.popup_id, item_id, ztAlign_Left | ztAlign_Bottom);
					}
				}
				else zt_bitRemove(item->flags, ztGuiComboBoxInternalFlags_IgnorePopup);
			}

			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_INPUT_KEY(inputKey)
		{
			_zt_guiItemAndManagerReturnValOnError(gm, item, item_id, false);

			if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
				if (item->combobox.selected > 0) {
					item->combobox.selected -= 1;
					if (item->combobox.on_selected) {
						item->combobox.on_selected(item_id, item->combobox.selected, item->combobox.on_selected_user_data);
					}
				}
			}
			if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
				if (item->combobox.selected < item->combobox.contents_count - 1) {
					item->combobox.selected += 1;
					if (item->combobox.on_selected) {
						item->combobox.on_selected(item_id, item->combobox.selected, item->combobox.on_selected_user_data);
					}
				}
			}

			return false;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;

			bool pressed = false, highlighted = zt_bitIsSet(gm->item_cache_flags[item_id], ztGuiManagerItemCacheFlags_MouseOver);
			zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_combobox_background, pos, item->size, highlighted, pressed);

			pos.x += (item->size.x - zt_guiThemeButtonSpriteGetSize(&theme->sprite_combobox_button).x) / 2.f;
			zt_drawListAddGuiThemeButtonSprite(draw_list, &theme->sprite_combobox_button, pos, ztVec2(theme->combobox_button_size_x, theme->combobox_size_y), highlighted, pressed);

			if (item->combobox.selected >= 0 && item->combobox.selected < item->combobox.contents_count) {
				pos.x = (offset.x + item->pos.x) + (item->size.x / -2.f + theme->padding);
				zt_drawListAddFancyText2D(draw_list, theme->font, item->combobox.contents[item->combobox.selected], pos, ztAlign_Left, ztAnchor_Left);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			zt_fiz(item->combobox.contents_size) {
				zt_stringFree(item->combobox.contents[i], gm->arena);
			}
			zt_freeArena(item->combobox.contents, gm->arena);
			item->combobox.contents_size = item->combobox.contents_count = -1;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(bestSize)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			size->x = 0;
			size->y = theme->combobox_size_y;
		}

	};


	ztGuiManager *gm = zt_gui->gui_managers[zt_gui->active_gui_manager];
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_ComboBox, ztGuiItemFlags_WantsFocus, &item_id);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->combobox.popup_id = ztInvalidID;
	item->combobox.contents = zt_mallocStructArrayArena(ztString, max_items, gm->arena);
	item->combobox.contents_size = max_items;
	item->combobox.contents_count = 0;
	item->combobox.on_selected = nullptr;
	item->combobox.on_selected_user_data = nullptr;

	zt_fiz(max_items) {
		item->combobox.contents[i] = zt_stringMake(128, gm->arena);
		item->combobox.contents[i][0] = 0;
	}

	item->combobox.selected = 0;


	item->functions.cleanup = local::cleanup;
	item->functions.update = local::update;
	item->functions.input_mouse = local::inputMouse;
	item->functions.input_key = local::inputKey;
	item->functions.render = local::render;
	item->functions.best_size = local::bestSize;
	item->functions.user_data = gm;

	ztVec2 min_size;
	local::bestSize(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

ztInternal ZT_FUNC_GUI_MENU_SELECTED(_zt_guiComboBoxMenuSelected)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, menu_id);
	ztGuiItem *combo = (ztGuiItem*)user_data;
	combo->combobox.selected = menu_item;

	if (combo->combobox.on_selected) {
		combo->combobox.on_selected(combo->id, combo->combobox.selected, combo->combobox.on_selected_user_data);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxSetContents(ztGuiItemID combobox_id, const char **contents, int contents_count, int active)
{
	_zt_guiItemTypeFromIDReturnOnError(item, combobox_id, ztGuiItemType_ComboBox);
	_zt_guiManagerGetFromItem(gm, item->id);

	if (item->combobox.popup_id != ztInvalidID) {
		zt_guiItemFree(item->combobox.popup_id);
	}
	item->combobox.popup_id = zt_guiMakeMenu();
	zt_guiMenuSetCallback(item->combobox.popup_id, _zt_guiComboBoxMenuSelected);

	item->combobox.contents_count = zt_min(contents_count, item->combobox.contents_size);
	zt_fiz(item->combobox.contents_count) {
		zt_stringOverwrite(item->combobox.contents[i], contents[i], gm->arena);

		zt_guiMenuAppend(item->combobox.popup_id, contents[i], i, item);
	}

	item->combobox.selected = zt_clamp(active, 0, item->combobox.contents_count - 1);
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxClear(ztGuiItemID combobox_id)
{
	_zt_guiItemTypeFromIDReturnOnError(item, combobox_id, ztGuiItemType_ComboBox);
	item->combobox.contents_count = 0;
	item->combobox.selected = -1;

	if (item->combobox.popup_id != ztInvalidID) {
		zt_guiItemFree(item->combobox.popup_id);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxAppend(ztGuiItemID combobox_id, const char *content)
{
	_zt_guiItemTypeFromIDReturnOnError(item, combobox_id, ztGuiItemType_ComboBox);
	zt_assert(item->combobox.contents_count < item->combobox.contents_size);

	if (item->combobox.contents_count == 0) {
		if (item->combobox.popup_id != ztInvalidID) {
			zt_guiItemFree(item->combobox.popup_id);
		}
		item->combobox.popup_id = zt_guiMakeMenu();
		zt_guiMenuSetCallback(item->combobox.popup_id, _zt_guiComboBoxMenuSelected);
		item->combobox.selected = 0;
	}
	
	int idx = item->combobox.contents_count;
	item->combobox.contents_count += 1;

	_zt_guiManagerGetFromItem(gm, combobox_id);
	zt_stringOverwrite(item->combobox.contents[idx], content, gm->arena);
	zt_guiMenuAppend(item->combobox.popup_id, content, idx, item);
}

// ------------------------------------------------------------------------------------------------

int zt_guiComboBoxGetSelected(ztGuiItemID combobox_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, combobox_id, ztGuiItemType_ComboBox, -1);
	return item->combobox.selected;
}

// ------------------------------------------------------------------------------------------------

int zt_guiComboBoxGetItemCount(ztGuiItemID combobox_id)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, combobox_id, ztGuiItemType_ComboBox, 0);
	return item->combobox.contents_count;
}

// ------------------------------------------------------------------------------------------------

int zt_guiComboBoxGetItemText(ztGuiItemID combobox_id, int index, char* buffer, int buffer_len)
{
	_zt_guiItemTypeFromIDReturnValOnError(item, combobox_id, ztGuiItemType_ComboBox, 0);
	if (index >= 0 && index < item->combobox.contents_count) {
		return zt_strCpy(buffer, buffer_len, item->combobox.contents[index]);
	}
	return 0;
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxSetCallback(ztGuiItemID combobox_id, zt_guiComboBoxItemSelected_Func *on_item_sel, void *user_data)
{
	_zt_guiItemTypeFromIDReturnOnError(item, combobox_id, ztGuiItemType_ComboBox);
	item->combobox.on_selected = on_item_sel;
	item->combobox.on_selected_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeSpriteDisplay(ztGuiItemID parent, ztGuiThemeSprite *sprite)
{
	struct local
	{
		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_RENDER(render)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];
			ztVec2 pos = offset + item->pos;

			zt_drawListAddGuiThemeSprite(draw_list, item->sprite_display.sprite, pos, item->size);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			zt_freeArena(item->sprite_display.sprite, gm->arena);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(bestSize)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			*size = zt_guiThemeSpriteGetSize(item->sprite_display.sprite);
		}
	};


	ztGuiManager *gm = zt_gui->gui_managers[zt_gui->active_gui_manager];
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_SpriteDisplay, ztGuiItemFlags_WantsFocus, &item_id);
	if (!item) return ztInvalidID;

	ztGuiTheme *theme = zt_guiItemGetTheme(item_id);

	item->sprite_display.sprite = zt_mallocStructArena(ztGuiThemeSprite, gm->arena);
	if (sprite) {
		*item->sprite_display.sprite = *sprite;
	}
	else {
		item->sprite_display.sprite->type = ztGuiThemeSpriteType_Invalid;
	}


	item->functions.render = local::render;
	item->functions.cleanup = local::cleanup;
	item->functions.best_size = local::bestSize;
	item->functions.user_data = gm;

	ztVec2 min_size;
	local::bestSize(item->id, &min_size, nullptr, &item->size, theme, gm);

	return item_id;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSpriteDisplaySetSprite(ztGuiItemID item_id, ztGuiThemeSprite *sprite)
{
	_zt_guiItemTypeFromIDReturnOnError(item, item_id, ztGuiItemType_SpriteDisplay);
	*item->sprite_display.sprite = *sprite;
}

// ------------------------------------------------------------------------------------------------

ztInternal ztVec2 _zt_guiSizerMinSize(ztGuiItem *item)
{
	bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

	ztVec2 min_size = ztVec2::zero;
	ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
	while (entry) {
		ztVec2 size = entry->item->size;
		if (entry->item->type == ztGuiItemType_Sizer) {
			size = _zt_guiSizerMinSize(entry->item);
		}

		if (horz) {
			min_size.x += size.x + entry->padding * 2;
			min_size.y = zt_max(min_size.y, size.y + entry->padding * 2);
		}
		else {
			min_size.x = zt_max(min_size.x, size.x + entry->padding * 2);
			min_size.y += size.y + entry->padding * 2;
		}

		entry = entry->next;
	}

	return min_size;
}

// ------------------------------------------------------------------------------------------------

ztGuiItemID zt_guiMakeSizer(ztGuiItemID parent, ztGuiItemOrient_Enum orient)
{
	struct local
	{
		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_UPDATE(update)
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, item_id);

			if (item->parent == nullptr || ((item->sizer.size_to_parent && item->parent->size == item->size)) || (!item->sizer.size_to_parent && item->size.x == item->sizer.size[0] && item->size.y == item->sizer.size[1])) {
				if (item->sizer.size[0] != -1 && item->sizer.size[1] != -1) {
					return;
				}
			}

			if (item->sizer.size_to_parent) {
				item->sizer.size[0] = item->size.x = item->parent->size.x;
				item->sizer.size[1] = item->size.y = item->parent->size.y;
			}
			else {
				if (item->size == ztVec2::zero && !item->sizer.size_parent_x && !item->sizer.size_parent_y) {
					return;
				}

				if (item->sizer.size_parent_x || item->sizer.size_parent_y) {
					ztVec2 min_size = _zt_guiSizerMinSize(item);

					bool recalc = false;
					if (item->sizer.size_parent_x) {
						if (item->parent->size.x != min_size.x) {
							item->size.x = item->parent->size.x = min_size.x;
							recalc = true;
						}
					}
					else {
						item->size.x = item->parent->size.x;
						recalc = true;
					}

					if (item->sizer.size_parent_y) {
						if (item->parent->size.y != min_size.y) {
							item->size.y = item->parent->size.y = min_size.y;
							recalc = true;
						}
					}
					else {
						item->size.y = item->parent->size.y;
						recalc = true;
					}

					if (recalc) {
						zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(item->parent->id));
					}
				}

				item->sizer.size[0] = item->size.x;
				item->sizer.size[1] = item->size.y;
			}

			bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

			r32 room_orient = horz ? item->sizer.size[0] : item->sizer.size[1];
			r32 total_prop = 0;

			int entry_count = 0;
			ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
			while (entry) {
				entry_count += 1;
				if (entry->proportion == 0) {
					// takes up only as much space as the item inside it
					int padding_mult = 2;

					if (entry->item->type == ztGuiItemType_Sizer) {
						ztVec2 min_size = _zt_guiSizerMinSize(entry->item);
						r32 space_needed = (horz ? min_size.x : min_size.y) + entry->padding * padding_mult;
						room_orient -= (horz ? min_size.x : min_size.y) + entry->padding * padding_mult;
					}
					else {
						r32 space_needed = (horz ? entry->item->size.x : entry->item->size.y) + entry->padding * padding_mult;
						room_orient -= (horz ? entry->item->size.x : entry->item->size.y) + entry->padding * padding_mult;
					}
				}

				total_prop += entry->proportion;
				entry = entry->next;
			}

			r32 entry_pos_orient = horz ? item->sizer.size[0] / -2.f : item->sizer.size[1] / 2.f;
			r32 entry_opp_orient = horz ? item->sizer.size[1] / 2.f : item->sizer.size[0] / -2.f;

			entry = item->sizer.items;
			while (entry) {
				r32 entry_size_orient = 0;

				ztVec2 item_size = (entry->item->type == ztGuiItemType_Sizer ? _zt_guiSizerMinSize(entry->item) : entry->item->size);

				if (entry->proportion != 0) {
					entry_size_orient = (entry->proportion / total_prop) * room_orient;
				}
				else {
					entry_size_orient = (horz ? (item_size.x + entry->padding * 2) : (item_size.y + entry->padding * 2));
				}
				ztVec2 entry_size = ztVec2(horz ? entry_size_orient : item->sizer.size[0], horz ? item->sizer.size[1] : entry_size_orient);

				if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Horz)) {
					item_size.x = entry_size.x - entry->padding * 2;
				}
				if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Vert)) {
					item_size.y = entry_size.y - entry->padding * 2;
				}

				item_size.x = zt_min(item_size.x, entry_size.x - entry->padding * 2);
				item_size.y = zt_min(item_size.y, entry_size.y - entry->padding * 2);

				entry->item->size = item_size;

				ztVec2 entry_pos = ztVec2(horz ? entry_pos_orient + (entry->padding + item_size.x / 2) : entry_opp_orient + (entry->padding + item_size.x / 2),
										  horz ? entry_opp_orient - (entry->padding + item_size.y / 2) : entry_pos_orient - (entry->padding + item_size.y / 2));

				if (zt_bitIsSet(entry->align_flags, ztAlign_Left)) {
					// default
				}
				else if (zt_bitIsSet(entry->align_flags, ztAlign_Right)) {
					entry_pos.x += entry_size.x - (item_size.x + entry->padding * 2);
				}
				else {
					entry_pos.x += (entry_size.x - (item_size.x + entry->padding * 2)) / 2;
				}

				if (zt_bitIsSet(entry->align_flags, ztAlign_Top)) {
					// default
				}
				else if (zt_bitIsSet(entry->align_flags, ztAlign_Bottom)) {
					entry_pos.y -= entry_size.y - (item_size.y + entry->padding * 2);
				}
				else {
					entry_pos.y -= (entry_size.y - (item_size.y + entry->padding * 2)) / 2;
				}

				entry->item->pos = entry_pos;

				entry_pos_orient += horz ? (entry_size.x - entry->padding * 0) : -(entry_size.y - entry->padding * 0);
				entry = entry->next;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_CLEANUP(cleanup)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
			while (entry) {
				auto *copy = entry;
				entry = entry->next;
				zt_freeArena(copy, gm->arena);
			}
			item->sizer.items = nullptr;
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_ITEM_BEST_SIZE(best_size)
		{
			ztGuiManager *gm = (ztGuiManager *)user_data;
			ztGuiItem *item = &gm->item_cache[item_id];

			*size = _zt_guiSizerMinSize(item);

			if (min_size) *min_size = *size;
		}
	};


	ztGuiManager *gm = zt_gui->gui_managers[zt_gui->active_gui_manager];
	zt_returnValOnNull(gm, ztInvalidID);

	ztGuiItemID item_id = ztInvalidID;
	ztGuiItem *item = _zt_guiMakeItemBase(gm, parent, ztGuiItemType_Sizer, 0, &item_id);
	if (!item) return ztInvalidID;

	item->sizer.orient = orient;
	item->sizer.size[0] = item->sizer.size[1] = 0;
	item->sizer.size_to_parent = false;
	item->sizer.size_parent_x = item->sizer.size_parent_y = false;
	item->sizer.items = nullptr;

	item->functions.cleanup = local::cleanup;
	item->functions.update = local::update;
	item->functions.best_size = local::best_size;
	item->functions.user_data = gm;

	return item_id;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerAddItem(ztGuiItemID sizer_id, ztGuiItemID item_id, int proportion, r32 padding, i32 align_flags, i32 grow_direction)
{
	_zt_guiItemTypeFromIDReturnOnError(sizer, sizer_id, ztGuiItemType_Sizer);
	_zt_guiManagerGetFromItem(gm, sizer_id);
	_zt_guiManagerGetFromItem(gm_test, item_id);
	zt_assert(gm == gm_test);

	zt_guiItemReparent(item_id, sizer_id);

	ztGuiItem::ztSizerItemEntry *entry = zt_mallocStructArena(ztGuiItem::ztSizerItemEntry, gm->arena);

	_zt_guiItemFromID(item, item_id);

	entry->item = item;
	entry->proportion = proportion;
	entry->padding = padding;
	entry->align_flags = align_flags;
	entry->grow_direction = grow_direction;
	entry->next = nullptr;

	zt_singleLinkAddToEnd(sizer->sizer.items, entry);

	sizer->sizer.size[0] = sizer->sizer.size[1] = 0; // trigger recalc
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerAddStretcher(ztGuiItemID sizer_id, int proportion, r32 padding)
{
	_zt_guiManagerGetFromItem(gm, sizer_id);
	ztGuiItemID stretcher_id = ztInvalidID;
	ztGuiItem *stretcher = _zt_guiMakeItemBase(gm, sizer_id, ztGuiItemType_Custom, 0, &stretcher_id);
	zt_debugOnly(zt_guiItemSetName(stretcher_id, "Sizer Stretcher"));

	zt_guiSizerAddItem(sizer_id, stretcher_id, proportion, padding);
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerSizeToParent(ztGuiItemID sizer_id, bool size_to_parent)
{
	_zt_guiItemTypeFromIDReturnOnError(sizer, sizer_id, ztGuiItemType_Sizer);
	sizer->sizer.size_to_parent = size_to_parent;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerSizeParent(ztGuiItemID sizer_id, bool size_parent_x, bool size_parent_y)
{
	_zt_guiItemTypeFromIDReturnOnError(sizer, sizer_id, ztGuiItemType_Sizer);
	sizer->sizer.size_parent_x = size_parent_x;
	sizer->sizer.size_parent_y = size_parent_y;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiSizerRecalc(ztGuiItem *item)
{
	if (item->type == ztGuiItemType_Sizer) {
		item->sizer.size[0] = item->sizer.size[1] = -1;
	}

	ztGuiItem *child = item->first_child;
	while (child) {
		zt_guiSizerRecalc(child->id);
		child = child->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerRecalc(ztGuiItemID item_id)
{
	_zt_guiItemFromID(item, item_id);
	_zt_guiSizerRecalc(item);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiSizerRecalcImmediately(ztGuiItem *item)
{
	if (item->type == ztGuiItemType_Sizer) {
		item->functions.update(item->id, 0, item->functions.user_data);
	}

	ztGuiItem *child = item->first_child;
	while (child) {
		_zt_guiSizerRecalcImmediately(child);
		child = child->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerRecalcImmediately(ztGuiItemID item_id)
{
	_zt_guiItemFromID(item, item_id);
	_zt_guiSizerRecalc(item);
	_zt_guiSizerRecalcImmediately(item);
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiSizerGetMinSize(ztGuiItemID sizer_id)
{
	_zt_guiItemFromID(item, sizer_id);
	zt_returnValOnNull(item, ztVec2::zero);

	if (item->type == ztGuiItemType_Sizer) {
		return _zt_guiSizerMinSize(item);
	}
	else if (item->first_child && item->first_child->type == ztGuiItemType_Sizer && item->first_child->sib_next == nullptr) {
		return _zt_guiSizerMinSize(item->first_child);
	}

	return ztVec2::zero;
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
	item->name = zt_stringOverwrite(item->name, name, gm->arena);
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
	item->tooltip = zt_stringOverwrite(item->tooltip, tooltip, gm->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetThemeType(ztGuiItemID item_id, const char *theme_type)
{
	_zt_guiItemAndManagerReturnOnError(gm, item, item_id);
	item->theme_type = zt_stringOverwrite(item->theme_type, theme_type, gm->arena);
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

bool zt_guiItemIsVisible(ztGuiItemID id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, id, false);
	return zt_bitIsSet(item->flags, ztGuiItemFlags_Visible);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemEnable(ztGuiItemID id, bool enable)
{
	_zt_guiItemFromID(item, id);
	zt_returnOnNull(item);

	if (enable) {
		zt_bitRemove(item->flags, ztGuiItemFlags_Disabled);
	}
	else {
		item->flags |= ztGuiItemFlags_Disabled;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemDisable(ztGuiItemID id)
{
	zt_guiItemEnable(id, false);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsEnabled(ztGuiItemID id)
{
	_zt_guiItemAndManagerReturnValOnError(gm, item, id, false);
	return !zt_bitIsSet(item->flags, ztGuiItemFlags_Disabled);
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
	_zt_guiItemFromID(item, item_id);
	zt_returnOnNull(item);
	item->flags |= ztGuiItemFlags_Locked;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemUnlock(ztGuiItemID item_id)
{
	_zt_guiItemFromID(item, item_id);
	zt_returnOnNull(item);
	zt_bitRemove(item->flags, ztGuiItemFlags_Locked);
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

	static const int frames = 100;
	static r32 frame_times[frames];
	static i32 frame_times_idx = -1;
	static i32 frame_times_idx_oldest = 0;

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
			frame_times_idx = (frame_times_idx + 1) % frames;
			frame_times_idx_oldest = (frame_times_idx_oldest + 1) % frames;

			frame_times[frame_times_idx] = dt;
			time += dt;
			time -= frame_times[frame_times_idx_oldest];

			if(!zt_guiItemIsShowing(window_id)) return;

			r32 l_avg = (r32)time / frames;
			r32 l_time = time;
			r32 l_frame_times[frames];
			zt_memCpy(l_frame_times, zt_sizeof(r32) * frames, frame_times, zt_sizeof(r32) * frames);
			i32 l_frame_times_idx = frame_times_idx;
			i32 l_frame_times_idx_oldest = frame_times_idx_oldest;

			zt_strMakePrintf(fps, 256, "%.0f f/s %.02f us/f\n%.0f f/s %.02f us/f", 1.f / dt, dt * 1000000.f, 1.f / (time / (r32)frames), (time / (r32)frames) * 1000000.f);
			zt_guiItemSetLabel(text_id, fps);
			//zt_guiItemAutoSize(text_id);
			//zt_guiItemSetPosition(text_id, ztAlign_Left, ztAnchor_Left, ztVec2(3.f / zt_pixelsPerUnit(), 0));
		}
	};

	zt_fiz(frames) {
		frame_times[i] = 1 / 60.f;
		time += 1 / 60.f;
	}

	window_id = zt_guiMakeWindow(nullptr, ztGuiWindowFlags_AllowDrag);
	zt_debugOnly(zt_guiItemSetName(window_id, "FPS Display Window"));

	text_id = zt_guiMakeStaticText(window_id, "00000 f/s 00.0000f us/f\n00000 f/s 00.0000f us/f");
	zt_guiItemSetAlign(text_id, ztAlign_Right);
	zt_debugOnly(zt_guiItemSetName(text_id, "FPS Display Text"));

	ztGuiItemID button_id = zt_guiMakeButton(window_id, nullptr, ztGuiButtonFlags_NoBackground | ztGuiButtonFlags_OnPressDip);
	zt_guiButtonSetCallback(button_id, local::on_close);
	zt_debugOnly(zt_guiItemSetName(button_id, "Close Button"));

	_zt_guiManagerGetFromItem(gm, window_id);

	ztSprite sprite = zt_spriteMake(gm->default_theme.sprite_panel.type == ztGuiThemeSpriteType_Sprite ? gm->default_theme.sprite_panel.s.tex : gm->default_theme.sprite_panel.sns.tex, ztPoint2(16, 64), ztPoint2(16, 16));
	zt_guiButtonSetIcon(button_id, &sprite);

	zt_guiItemSetSize(window_id, ztVec2(3.25f, .65f));

	zt_guiItemSetPosition(text_id, ztAlign_Right, ztAlign_Right, ztVec2(-26.f / zt_pixelsPerUnit(), 0));
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
	zt_debugOnly(zt_guiItemSetName(window_id, "Rendering Details Window"));

	text_id = zt_guiMakeStaticText(window_id, "00000000 triangles\n0000 shader switches\n0000 tex switches\n0000 draw calls");
	zt_guiItemSetAlign(text_id, ztAlign_Right);
	zt_debugOnly(zt_guiItemSetName(text_id, "Rendering Details Text"));

	ztGuiItemID button_id = zt_guiMakeButton(window_id, nullptr, ztGuiButtonFlags_NoBackground | ztGuiButtonFlags_OnPressDip);
	zt_guiButtonSetCallback(button_id, local::on_close);
	zt_debugOnly(zt_guiItemSetName(button_id, "Close Button"));

	_zt_guiManagerGetFromItem(gm, window_id);

	ztSprite sprite = zt_spriteMake(gm->default_theme.sprite_panel.type == ztGuiThemeSpriteType_Sprite ? gm->default_theme.sprite_panel.s.tex : gm->default_theme.sprite_panel.sns.tex, ztPoint2(16, 64), ztPoint2(16, 16));
	zt_guiButtonSetIcon(button_id, &sprite);

	zt_guiItemSetSize(window_id, ztVec2(3.25f, 1.2f));

	zt_guiItemSetPosition(text_id, ztAlign_Right, ztAnchor_Right, ztVec2(-26.f / zt_pixelsPerUnit(), 0));
	zt_guiItemSetPosition(button_id, ztAlign_Right | ztAlign_Top, ztAnchor_Right | ztAnchor_Top, ztVec2(-3.f / zt_pixelsPerUnit(), -3.f / zt_pixelsPerUnit()));

	ztGuiItemID update_id = ztInvalidID;
	ztGuiItem *update = _zt_guiMakeItemBase(gm, window_id, ztGuiItemType_Custom, 0, &update_id);
	update->functions.update = local::item_update;
	update->functions.render = local::item_render;

	zt_guiItemSetPosition(window_id, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right, ztVec2(0, -.75f));
}

// ------------------------------------------------------------------------------------------------

#ifndef ZT_DEBUG_CONSOLE_BUFFER_SIZE
#define ZT_DEBUG_CONSOLE_BUFFER_SIZE	1024 * 32
#endif

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugConsole()
{
	static ztGuiItemID window_id = ztInvalidID;
	static ztGuiItemID display_id = ztInvalidID;
	static ztGuiItemID command_id = ztInvalidID;
	static int last_tab_stop = 0;

	if (window_id != ztInvalidID) {
		zt_guiItemShow(window_id);
		zt_guiItemSetFocus(command_id);
		return;
	}

	static char working_buffer[ZT_DEBUG_CONSOLE_BUFFER_SIZE];

	struct ztConsoleCommandString
	{
		char command[128];
		ztConsoleCommandString *next, *prev;
	};

	static ztConsoleCommandString *commands = nullptr;

	const int commands_count = 32;
	static byte command_buffer[zt_sizeof(ztConsoleCommandString) * commands_count];

	byte *command_buffer_ptr = command_buffer;

	ztConsoleCommandString* first = nullptr;
	zt_fiz(commands_count) {
		ztConsoleCommandString *cmd = (ztConsoleCommandString*)command_buffer_ptr;
		command_buffer_ptr += zt_sizeof(ztConsoleCommandString);

		if (commands) {
			commands->prev = cmd;
		}
		else {
			first = cmd;
		}
		cmd->command[0] = 0;
		cmd->next = commands;
		cmd->prev = nullptr;
		commands = cmd;
	}

	commands->prev = first;
	first->next = commands;

	static ztConsoleCommandString *current_command = commands;
	static ztConsoleCommandString *selected_command = current_command;

	struct local
	{
		static ZT_FUNC_GUI_TEXTEDIT_KEY(input_key)
		{
			if (input_keys[ztInputKeys_Return].justPressed()) {

				zt_guiTextEditGetValue(command_id, current_command->command, zt_elementsOf(current_command->command));
				zt_guiTextEditSetValue(command_id, nullptr);

				zt_debugConsoleLogUser("> %s", current_command->command);

				ztToken tokens[16];
				int tokens_count = zt_strTokenize(current_command->command, " ", tokens, zt_elementsOf(tokens));
				if (tokens_count > 16) {
					zt_debugConsoleLogError("  Too many parameters");
				}
				else {
					ztDebugConsoleParams(params);

					zt_fiz(tokens_count) {
						zt_strCpy(params[i], 256, zt_strMoveForward(current_command->command, tokens[i].beg), tokens[i].len);
					}

					auto *command = zt_gui->console_commands;
					while (command) {
						if (zt_strEquals(command->command, params[0])) {
							break;
						}
						command = command->next;
					}

					if (command == nullptr) {
						zt_debugConsoleLogWarning("  Command not found: %s", params[0]);
					}
					else {
						command->on_command(params, tokens_count);
					}
				}

				current_command = current_command->next;
				selected_command = current_command;
			}
			if (input_keys[ztInputKeys_Up].justPressed()) {
				if (selected_command->prev->command[0] != 0 && selected_command->prev != current_command) {
					selected_command = selected_command->prev;
					zt_guiTextEditSetValue(command_id, selected_command->command);
					zt_guiTextEditSelectAll(command_id);
					zt_guiTextEditSetCursorPos(command_id, 0);
				}
			}
			if (input_keys[ztInputKeys_Down].justPressed()) {
				if (selected_command->next != current_command && selected_command->next->command[0] != 0) {
					selected_command = selected_command->next;
					zt_guiTextEditSetValue(command_id, selected_command->command);
					zt_guiTextEditSelectAll(command_id);
					zt_guiTextEditSetCursorPos(command_id, 0);
				}
			}
			if (input_keys[ztInputKeys_Tab].justPressedOrRepeated()) {
				*should_process = false;

				char command_buffer[256];
				zt_guiTextEditGetValue(command_id, command_buffer, zt_elementsOf(command_buffer));

				if (zt_strFindPos(command_buffer, " ", 0) != ztStrPosNotFound) {

				}
				else {
					int cursor = zt_guiTextEditGetCursorPos(command_id);
					char start_with[256];
					zt_strCpy(start_with, zt_elementsOf(start_with), command_buffer, cursor);

					int which_stop = 0;
					auto *command = zt_gui->console_commands;
					while (command) {
						if (zt_strStartsWith(command->command, start_with)) {
							if (++which_stop > last_tab_stop) {
								break;
							}
						}
						command = command->next;
					}

					if (command == nullptr && which_stop > 0) {
						command = zt_gui->console_commands;
						while (command) {
							if (zt_strStartsWith(command->command, start_with)) {
								which_stop = 1;
								break;
							}
							command = command->next;
						}
					}

					if (command != nullptr) {
						zt_guiTextEditSetValue(command_id, command->command);
						zt_guiTextEditSetSelection(command_id, cursor, cursor + 999999);
						zt_guiTextEditSetCursorPos(command_id, 999999);
						last_tab_stop = which_stop;
					}
				}
				return;
			}

			zt_fiz(zt_elementsOf(input_key_strokes)) {
				if (input_key_strokes[i] == ztInputKeys_Invalid) {
					break;
				}
				if (input_keys[input_key_strokes[i]].display != 0) {
					last_tab_stop = 0;
				}
			}
		}

		static void log_callback(ztLogMessageLevel_Enum level, const char * message)
		{
			switch (level)
			{
			case ztLogMessageLevel_Fatal: 
			case ztLogMessageLevel_Critical: zt_debugConsoleLogError(message); break;

			case ztLogMessageLevel_Info: zt_debugConsoleLogCommand(message); break;
			}
		}

		static ZT_FUNC_DEBUG_CONSOLE_COMMAND(command_list)
		{
			zt_debugConsoleLogCommand("  Available commands:");

			auto *command = zt_gui->console_commands;
			while (command) {
				zt_debugConsoleLogCommand("    %s", command->command);
				command = command->next;
			}
		}

		static ZT_FUNC_DEBUG_CONSOLE_COMMAND(command_help)
		{
			if (params_count == 1 || zt_strEquals(params[1], "help")) {
				zt_debugConsoleLogHelp("  Syntax: help <<cmd>");
				zt_debugConsoleLogHelp("  Type 'list' for a list of commands");
			}
			else {
				char *help_cmd = params[1];
				
				auto *command = zt_gui->console_commands;
				while (command) {
					if (zt_strEquals(command->command, help_cmd)) {
						zt_debugConsoleLogHelp("  %s", command->help);
						break;
					}
					command = command->next;
				}
				if (command == nullptr) {
					zt_debugConsoleLogWarning("  Command not found: %s", help_cmd);
				}
			}
		}

		static ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(command_help_auto)
		{

		}

		static ZT_FUNC_DEBUG_CONSOLE_COMMAND(command_exit)
		{
			zt->quit_requested = true;
		}
	};

	zt_gui->console_window_id = window_id = zt_guiMakeWindow("Console", ztGuiWindowFlags_AllowDrag | ztGuiWindowFlags_AllowResize | ztGuiWindowFlags_ShowTitle | ztGuiWindowFlags_AllowClose | ztGuiWindowFlags_AllowCollapse | ztGuiWindowFlags_CloseHides);
	zt_guiItemSetSize(window_id, ztVec2(16, 9));
	zt_debugOnly(zt_guiItemSetName(zt_gui->console_window_id, "Debug Console"));

	ztGuiItemID content_id = zt_guiWindowGetContentParent(window_id);
	ztGuiItemID display_container = zt_gui->console_display_container_id = zt_guiMakeScrollContainer(content_id, ztGuiScrollContainerFlags_ShowScrollVert);
	zt_gui->console_display_id = display_id = zt_guiMakeStaticText(display_container, nullptr, ztGuiStaticTextFlags_Fancy, zt_elementsOf(working_buffer));
	zt_guiScrollContainerSetItem(display_container, display_id);

	zt_guiItemSetAlign(display_id, ztAlign_Left | ztAlign_Top);

	zt_gui->console_command_id = command_id = zt_guiMakeTextEdit(content_id, nullptr);
	zt_guiTextEditSetCallback(command_id, local::input_key);
	zt_guiItemSetFocus(zt_gui->console_command_id);

	ztGuiItemID main_sizer = zt_guiMakeSizer(content_id, ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(main_sizer);

	zt_guiSizerAddItem(main_sizer, display_container, 1, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddItem(main_sizer, command_id, 0, 3 / zt_pixelsPerUnit(), 0, ztGuiItemOrient_Horz);

	zt_debugConsoleAddCommand("list", "Lists the available commands", local::command_list, nullptr);
	zt_debugConsoleAddCommand("help", nullptr, local::command_help, local::command_help_auto);
	zt_debugConsoleAddCommand("exit", "Quits the program", local::command_exit, nullptr);

	zt_debugConsoleLogCommand("<color=00aa00ff>Welcome to the console.  Type 'help <<cmd>' for help.  Type 'list' for commands.</color>");

	zt_logAddCallback(local::log_callback, ztLogMessageLevel_Info);

	zt_guiItemShow(window_id, false);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleAddCommand(const char *command, const char *help, zt_debugConsole_Func *command_func, zt_debugConsoleAutoComplete_Func auto_complete_func)
{
	ztConsoleCommand *console_command = zt_mallocStructArena(ztConsoleCommand, zt_gui->arena);
	zt_strCpy(console_command->command, zt_elementsOf(console_command->command), command);
	zt_strCpy(console_command->help, zt_elementsOf(console_command->help), help);
	console_command->on_command = command_func;
	console_command->on_auto_complete = auto_complete_func;

	ztConsoleCommand *prev = nullptr;
	ztConsoleCommand *link = zt_gui->console_commands;
	while (link) {
		if (zt_striCmp(link->command, command) > 0) {
			console_command->next = link;
			if (prev) {
				prev->next = console_command;
			}
			if (link == zt_gui->console_commands) {
				zt_gui->console_commands = console_command;
			}
			break;
		}
		prev = link;
		link = link->next;
	}
	if (link == nullptr) {
		zt_singleLinkAddToEnd(zt_gui->console_commands, console_command);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleRemoveCommand(const char *command)
{
	ztConsoleCommand *prev = nullptr;
	ztConsoleCommand *link = zt_gui->console_commands;
	while (link) {
		if (zt_strEquals(link->command, command)) {
			if (prev) {
				prev->next = link->next;
			}
			else {
				zt_gui->console_commands = link->next;
			}

			zt_freeArena(link, zt_gui->arena);
			break;
		}
		prev = link;
		link = link->next;
	}
}

// ------------------------------------------------------------------------------------------------

#if defined(ZT_COMPILER_MSVC)
#define _zt_var_args \
			va_list arg_ptr; \
			va_start(arg_ptr, command); \
			char buffer[1024 * 64]; \
			vsnprintf_s(buffer, zt_elementsOf(buffer), command, arg_ptr);

#else
#	error "Unsupported compiler for zt_debugConsoleLog"
#endif

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_debugConsoleLogRaw(ztDebugConsoleLevel_Enum message_level, const char *command)
{
	_zt_guiItemTypeFromIDReturnOnError(item, zt_gui->console_display_id, ztGuiItemType_StaticText);

	char *color = nullptr;
	switch (message_level)
	{
		case ztDebugConsoleLevel_User   : color = "b3b3b3ff"; break;
		case ztDebugConsoleLevel_Command: color = nullptr; break;
		case ztDebugConsoleLevel_Help   : color = "7f7ffeff"; break;
		case ztDebugConsoleLevel_Warning: color = "cb8517ff"; break;
		case ztDebugConsoleLevel_Error  : color = "cb4617ff"; break;
		case ztDebugConsoleLevel_System : color = "b3ffb3ff"; break;
	}

	char lcl_command[1024 * 4];

	if (color != nullptr) {
		zt_strPrintf(lcl_command, zt_elementsOf(lcl_command), "<color=%s>%s</color>", color, command);
	}
	else {
		zt_strPrintf(lcl_command, zt_elementsOf(lcl_command), "%s", command);
	}

	int str_len_label = zt_strLen(item->label);
	int str_len = str_len_label + 2 + zt_strLen(lcl_command);
	int start = 0;

	if (str_len > ZT_DEBUG_CONSOLE_BUFFER_SIZE) {
		start = str_len - ZT_DEBUG_CONSOLE_BUFFER_SIZE;
		start = zt_strFindPos(item->label, "\n", start);
		str_len -= start;
		str_len_label -= start;
	}

	char *buffer = zt_mallocStructArrayArena(char, str_len + 1, zt_gui->arena);


	zt_strCpy(buffer, str_len, zt_strMoveForward(item->label, start));
	if (str_len_label != 0) {
		zt_strCpy((char*)zt_strMoveForward(buffer, str_len_label), 2, "\n");
	}
	zt_strCpy((char*)zt_strMoveForward(buffer, str_len_label + 1), str_len - (str_len_label + 1), lcl_command);

	zt_guiItemSetLabel(item->id, buffer);
	zt_guiItemAutoSize(zt_gui->console_display_id);

	zt_freeArena(buffer, zt_gui->arena);

	zt_guiScrollContainerSetScroll(zt_gui->console_display_container_id, ztGuiItemOrient_Vert, 1);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLog(ztDebugConsoleLevel_Enum message_level, const char *command, ...)
{
	_zt_var_args;
	_zt_debugConsoleLogRaw(message_level, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLogUser(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_User, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLogCommand(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Command, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLogHelp(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Help, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLogWarning(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Warning, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLogError(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Error, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleLogSystem(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_System, (const char *)buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleToggle(bool *is_shown)
{
	if (zt_gui->console_window_id == ztInvalidID) {
		_zt_guiDebugConsole();
		return;
	}
	bool show = !zt_guiItemIsVisible(zt_gui->console_window_id);
	zt_guiItemShow(zt_gui->console_window_id, show);
	zt_guiTextEditSetValue(zt_gui->console_command_id, "");
	zt_guiItemSetFocus(zt_gui->console_command_id);

	if (show) {
		zt_guiItemBringToFront(zt_gui->console_window_id);
	}

	if (is_shown) *is_shown = show;
}

// ------------------------------------------------------------------------------------------------

#undef _zt_var_args

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugGuiHierarchy()
{
	static ztGuiItemID window_id = ztInvalidID;
	static ztGuiItemID tree_id = ztInvalidID;
	static ztGuiItemID details_id = ztInvalidID;

	struct local
	{
		static void append(ztGuiItem *item, ztGuiTreeNodeID parent_node)
		{
			if (item->id == window_id) {
				return;
			}

			zt_strMakePrintf(buffer, 1024, "%s - %s", zt_guiItemTypeName(item->type), item->name ? item->name : "(unnamed)");

			ztGuiTreeNodeID root = zt_guiTreeAppend(tree_id, buffer, item, parent_node);
			ztGuiItem *child = item->first_child;
			while (child) {
				append(child, root);
				child = child->sib_next;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void populate()
		{
			_zt_guiItemFromID(tree, tree_id);
			zt_guiTreeClear(tree_id);

			zt_fiz(zt_elementsOf(zt_gui->gui_managers)) {
				if (!zt_gui->gui_managers[i]) {
					break;
				}
				ztGuiTreeNodeID root = zt_guiTreeAppend(tree_id, "GUI Manager", nullptr);

				ztGuiItem *child = zt_gui->gui_managers[i]->first_child;
				while (child) {
					append(child, root);
					child = child->sib_next;
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void populateItem(ztGuiItem *item)
		{
			zt_strMakePrintf(details_buffer, 64 * 1024,
				"<color=8abbf8>Type:</color>                    %s\n"
				"<color=8abbf8>Name:</color>                    %s\n"
				"<color=8abbf8>Tooltip:</color>                 %s\n"
				"<color=8abbf8>Size:</color>                    %.2f, %.2f\n"
				"<color=8abbf8>Position:</color>                %.2f, %.2f\n"
				"<color=8abbf8>Align Flags:</color>             %d\n"
				"<color=8abbf8>Anchor Flags:</color>            %d\n"
				"<color=8abbf8>Position Align Flags:</color>    %d\n"
				"<color=8abbf8>Position Anchor Flags:</color>   %d\n"
				"<color=8abbf8>Position Offset:</color>         %.2f, %.2f\n"
				"<color=8abbf8>Color:</color>                   %.2f, %.2f, %.2f, %.2f\n"
				"<color=8abbf8>Wants Focus:</color>             %s\n"
				"<color=8abbf8>Wants Input:</color>             %s\n"
				"<color=8abbf8>Visible:</color>                 %s\n"
				"<color=8abbf8>Outlying Children:</color>       %s\n"
				"<color=8abbf8>Bring to Front:</color>          %s\n"
				"<color=8abbf8>Label:</color>                   %s\n",
				zt_guiItemTypeName(item->type),
				item->name ? item->name : "(unnamed)",
				item->tooltip ? item->tooltip : "(no tooltip)",
				item->size.x, item->size.y,
				item->pos.x, item->pos.y,
				item->align_flags,
				item->anchor_flags,
				item->pos_align_flags,
				item->pos_anchor_flags,
				item->pos_offset.x, item->pos_offset.y,
				item->color.r, item->color.g, item->color.b, item->color.a,
				(zt_bitIsSet(item->flags, ztGuiItemFlags_WantsFocus) ? "true" : "false"),
				(zt_bitIsSet(item->flags, ztGuiItemFlags_WantsInput) ? "true" : "false"),
				(zt_bitIsSet(item->flags, ztGuiItemFlags_Visible) ? "true" : "false"),
				(zt_bitIsSet(item->flags, ztGuiItemFlags_OutlyingChildren) ? "true" : "false"),
				(zt_bitIsSet(item->flags, ztGuiItemFlags_BringToFront) ? "true" : "false"),
				item->label ? item->label : "(no label)"
				);

			zt_guiItemSetLabel(details_id, details_buffer);
			zt_guiItemAutoSize(details_id);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_TREE_ITEM_SELECTED(onTreeSel)
		{
			ztGuiItem *item = (ztGuiItem*)zt_guiTreeGetNodeUserData(tree_id, node_id);
			if (item) {
				populateItem(item);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_BUTTON_PRESSED(onRefreshTree)
		{
			populate();
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_BUTTON_PRESSED(onToggleHighlight)
		{
#			if defined(ZT_DEBUG)
			ztGuiItem* item = (ztGuiItem*)zt_guiTreeGetNodeUserData(tree_id, zt_guiTreeGetSelected(tree_id));
			if (item) {
				if (item->debug_highlight == ztVec4::zero) {
					item->debug_highlight = ztVec4(0, 1, 0, 1);
				}
				else {
					item->debug_highlight = ztVec4::zero;
				}
			}
#			endif
		}
	};

	if (window_id != ztInvalidID) {
		zt_guiItemShow(window_id);
		return;
	}

	window_id = zt_guiMakeWindow("GUI Hierarchy", ztGuiWindowFlags_AllowDrag | ztGuiWindowFlags_AllowResize | ztGuiWindowFlags_ShowTitle | ztGuiWindowFlags_AllowClose | ztGuiWindowFlags_AllowCollapse | ztGuiWindowFlags_CloseHides);
	zt_guiItemSetSize(window_id, ztVec2(16, 9));

	ztGuiTheme *theme = zt_guiItemGetTheme(window_id);

	ztGuiItemID content_id = zt_guiWindowGetContentParent(window_id);

	ztGuiItemID sizer_id = zt_guiMakeSizer(content_id, ztGuiItemOrient_Horz);
	zt_guiSizerSizeToParent(sizer_id);

	{
		ztGuiItemID sizer_left_id = zt_guiMakeSizer(sizer_id, ztGuiItemOrient_Vert);
		zt_guiSizerAddItem(sizer_id, sizer_left_id, 2, theme->padding);

		tree_id = zt_guiMakeTree(sizer_left_id, 1024 * 64);
		zt_guiSizerAddItem(sizer_left_id, tree_id, 1, theme->padding);

		zt_guiTreeSetCallback(tree_id, local::onTreeSel, nullptr);

		ztGuiItemID sizer_btns = zt_guiMakeSizer(sizer_left_id, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer_left_id, sizer_btns, 0, 0);

		ztGuiItemID button_refresh_id = zt_guiMakeButton(sizer_left_id, "Refresh");
		zt_guiButtonSetCallback(button_refresh_id, local::onRefreshTree);
		zt_guiSizerAddItem(sizer_btns, button_refresh_id, 0, theme->padding);

#		if defined(ZT_DEBUG)
		zt_guiSizerAddStretcher(sizer_btns, 1);
		ztGuiItemID button_highlight_id = zt_guiMakeButton(sizer_btns, "Toggle Highlight");
		zt_guiButtonSetCallback(button_highlight_id, local::onToggleHighlight);
		zt_guiSizerAddItem(sizer_btns, button_highlight_id, 0, theme->padding, ztAlign_Right, 0);
#		endif
	}

	{
		ztGuiItemID sizer_right_id = zt_guiMakeSizer(sizer_id, ztGuiItemOrient_Vert);
		zt_guiSizerAddItem(sizer_id, sizer_right_id, 3, theme->padding);

		ztGuiItemID scroll_id = zt_guiMakeScrollContainer(sizer_right_id);
		details_id = zt_guiMakeStaticText(scroll_id, "<color=8abbf8>Select an item on the left to view details on that item.</color>", ztGuiStaticTextFlags_Fancy, 2048);
		zt_guiScrollContainerSetItem(scroll_id, details_id);

		zt_guiSizerAddItem(sizer_right_id, scroll_id, 1, theme->padding);

	}

	local::populate();
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugTextureViewer()
{
	static ztGuiItemID window_id = ztInvalidID;
	static ztGuiItemID dropdown_id = ztInvalidID;
	static ztGuiItemID display_id = ztInvalidID;

	if (window_id != ztInvalidID) {
		zt_guiItemShow(window_id);
		return;
	}

	struct local
	{
		static void refresh()
		{
			_zt_guiItemAndManagerReturnOnError(gm, item, dropdown_id);

			zt_guiComboBoxClear(dropdown_id);

			zt_fiz(zt->textures_count) {
				bool render_tex = false;
				switch (zt_currentRenderer())
				{
				case ztRenderer_OpenGL: zt_openGLSupport(render_tex = zt->textures[i].gl_fbo != 0); break;
				case ztRenderer_DirectX: zt_directxSupport(render_tex = zt->textures[i].dx_render_target_view != nullptr); break;
				}
				zt_strMakePrintf(buffer, 256, "[%d] %d x %d %s", i, zt->textures[i].width, zt->textures[i].height, (render_tex ? "(render texture)" : ""));
				zt_guiComboBoxAppend(dropdown_id, buffer);
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void loadTexture(ztTextureID tex_id)
		{
			ztGuiThemeSprite sprite;
			sprite.type = ztGuiThemeSpriteType_Sprite;
			sprite.s = zt_spriteMake(tex_id, ztPoint2(0, 0), ztPoint2(zt->textures[tex_id].width, zt->textures[tex_id].height));

			zt_guiSpriteDisplaySetSprite(display_id, &sprite);
			zt_guiItemAutoSize(display_id);
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_BUTTON_PRESSED(onRefresh)
		{
			refresh();
		}

		// ------------------------------------------------------------------------------------------------

		static ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(onComboBox)
		{
			loadTexture(selected);
		}
	};

	window_id = zt_guiMakeWindow("Texture Viewer", ztGuiWindowFlags_AllowDrag | ztGuiWindowFlags_AllowResize | ztGuiWindowFlags_ShowTitle | ztGuiWindowFlags_AllowClose | ztGuiWindowFlags_AllowCollapse | ztGuiWindowFlags_CloseHides);
	zt_guiItemSetSize(window_id, ztVec2(16, 16));

	ztGuiTheme *theme = zt_guiItemGetTheme(window_id);

	ztGuiItemID sizer_id = zt_guiMakeSizer(zt_guiWindowGetContentParent(window_id), ztGuiItemOrient_Vert);
	{
		zt_guiSizerSizeToParent(sizer_id);

		ztGuiItemID sizer_top_id = zt_guiMakeSizer(sizer_id, ztGuiItemOrient_Horz);
		{
			zt_guiSizerAddItem(sizer_id, sizer_top_id, 0, 0);

			dropdown_id = zt_guiMakeComboBox(sizer_top_id, zt_elementsOf(zt->textures));
			zt_guiItemSetSize(dropdown_id, ztVec2(6, -1));
			zt_guiSizerAddItem(sizer_top_id, dropdown_id, 0, 3 / zt_pixelsPerUnit(), ztAlign_Top, ztGuiItemOrient_Horz);
			zt_guiComboBoxSetCallback(dropdown_id, local::onComboBox, nullptr);

			ztGuiItemID button_id = zt_guiMakeButton(sizer_top_id, "Refresh");
			zt_guiSizerAddItem(sizer_top_id, button_id, 0, 3 / zt_pixelsPerUnit());
		}

		ztGuiItemID scroll_id = zt_guiMakeScrollContainer(sizer_id);
		display_id = zt_guiMakeSpriteDisplay(scroll_id, nullptr);
		zt_guiScrollContainerSetItem(scroll_id, display_id);

		zt_guiSizerAddItem(sizer_id, scroll_id, 1, 3 / zt_pixelsPerUnit());
	}

	local::refresh();
}

// ------------------------------------------------------------------------------------------------

void zt_guiInitDebug(ztGuiManagerID gui_manager)
{
	static ztGuiItemID button_id;
	static ztGuiItemID menu_id;

	enum
	{
		ztGuiDebugMenu_FpsDisplay,
		ztGuiDebugMenu_RenderingDetails,
		ztGuiDebugMenu_Console,
		ztGuiDebugMenu_GuiHierarchy,
		ztGuiDebugMenu_TextureViewer,
	};

	struct local
	{
		static ZT_FUNC_GUI_BUTTON_PRESSED(on_open_menu)
		{
			zt_guiMenuPopupAtItem(menu_id, button_id, ztAlign_Left | ztAlign_Bottom);
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

				case ztGuiDebugMenu_Console: {
					_zt_guiDebugConsole();
				} break;

				case ztGuiDebugMenu_GuiHierarchy: {
					_zt_guiDebugGuiHierarchy();
				} break;

				case ztGuiDebugMenu_TextureViewer: {
					_zt_guiDebugTextureViewer();
				} break;
			};
		}
	};

	_zt_guiManagerCheckAndGet(gm, gui_manager);

	button_id = zt_guiMakeButton(ztInvalidID, nullptr);
	zt_debugOnly(zt_guiItemSetName(button_id, "Debug Menu Button"));

	ztSprite sprite = zt_spriteMake(gm->default_theme.sprite_panel.type == ztGuiThemeSpriteType_Sprite ? gm->default_theme.sprite_panel.s.tex : gm->default_theme.sprite_panel.sns.tex, ztPoint2(1, 80), ztPoint2(23, 23));
	zt_guiButtonSetIcon(button_id, &sprite);
	zt_guiButtonSetCallback(button_id, local::on_open_menu);
	zt_guiItemSetPosition(button_id, ztAlign_Top, ztAnchor_Top);

	menu_id = zt_guiMakeMenu();
	zt_debugOnly(zt_guiItemSetName(menu_id, "Debug Menu"));

	zt_guiMenuAppend(menu_id, "FPS Display", ztGuiDebugMenu_FpsDisplay);
	zt_guiMenuAppend(menu_id, "Rendering Details", ztGuiDebugMenu_RenderingDetails);
	zt_guiMenuAppend(menu_id, "Console", ztGuiDebugMenu_Console);
	zt_guiMenuAppend(menu_id, "GUI Hierarchy", ztGuiDebugMenu_GuiHierarchy);
	zt_guiMenuAppend(menu_id, "Texture Viewer", ztGuiDebugMenu_TextureViewer);

	zt_guiMenuSetCallback(menu_id, local::on_menu_item);

	_zt_guiDebugFpsDisplay();
	_zt_guiDebugRenderingDetails();

	zt_gui->console_window_id = ztInvalidID;
	_zt_guiDebugConsole();
}

// ------------------------------------------------------------------------------------------------

void zt_debugLogGuiHierarchy(ztGuiItemID item_id)
{
	struct local
	{
		static void log(ztGuiItem *item, int tabs)
		{
			char *type;
			switch (item->type)
			{
				case ztGuiItemType_Window         : type = "Window"; break;
				case ztGuiItemType_Panel          : type = "Panel"; break;
				case ztGuiItemType_CollapsingPanel: type = "CollapsingPanel"; break;
				case ztGuiItemType_StaticText     : type = "StaticText"; break;
				case ztGuiItemType_Button         : type = "Button"; break;
				case ztGuiItemType_ToggleButton   : type = "ToggleButton"; break;
				case ztGuiItemType_Checkbox       : type = "Checkbox"; break;
				case ztGuiItemType_RadioButton    : type = "RadioButton"; break;
				case ztGuiItemType_Slider         : type = "Slider"; break;
				case ztGuiItemType_Menu           : type = "Menu"; break;
				case ztGuiItemType_Scrollbar      : type = "Scrollbar"; break;
				case ztGuiItemType_ScrollContainer: type = "ScrollContainer"; break;
				case ztGuiItemType_TextEdit       : type = "TextEdit"; break;
				case ztGuiItemType_Tab            : type = "Tab"; break;
				case ztGuiItemType_Tree           : type = "Tree"; break;
				case ztGuiItemType_ProgressBar    : type = "ProgressBar"; break;
				case ztGuiItemType_Sizer          : type = "Sizer"; break;
				case ztGuiItemType_Custom         : type = "Custom"; break;
			}

			char *name = item->name ? item->name : "unnamed";

			char prefix_buffer[128] = { 0 };
			char *prefix = prefix_buffer;
			*prefix++ = ' ';

			zt_fiz(tabs) {
				if (i != 0) *prefix++ = ' ';
				*prefix++ = '+';
				*prefix++ = '-';
				*prefix++ = '-';
			}

			zt_logDebug("%s %s (%s) (%d - 0x%llu)", prefix_buffer, type, name, item->id, (u64)item);

			ztGuiItem *child = item->first_child;
			if (child) {
				log(child, tabs + 1);
			}

			if (item->sib_next) {
				log(item->sib_next, tabs);
			}
		}
	};

	_zt_guiItemFromID(item, item_id);

	if (item) {
		local::log(item, 0);
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // implementation
