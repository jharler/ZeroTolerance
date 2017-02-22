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

// ------------------------------------------------------------------------------------------------

struct ztGuiManager;
struct ztGuiItem;

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
	_ztGIT(ztGuiItemType_MenuBar        ) \
	_ztGIT(ztGuiItemType_Scrollbar      ) \
	_ztGIT(ztGuiItemType_ScrollContainer) \
	_ztGIT(ztGuiItemType_TextEdit       ) \
	_ztGIT(ztGuiItemType_Tab            ) \
	_ztGIT(ztGuiItemType_Tree           ) \
	_ztGIT(ztGuiItemType_ComboBox       ) \
	_ztGIT(ztGuiItemType_SpriteDisplay  ) \
	_ztGIT(ztGuiItemType_ProgressBar    ) \
	_ztGIT(ztGuiItemType_Sizer          ) \
	_ztGIT(ztGuiItemType_Spinner        ) \
	_ztGIT(ztGuiItemType_Custom         )

// ------------------------------------------------------------------------------------------------

#define _ztGIT(TYPE)	TYPE,

enum ztGuiItemType_Enum
{
	_ztGuiItemTypeList
};

#undef _ztGIT

// ------------------------------------------------------------------------------------------------

enum ztGuiItemBehaviorFlags_Enum
{
	ztGuiItemBehaviorFlags_WantsFocus          = (1 << 0),
	ztGuiItemBehaviorFlags_WantsInput          = (1 << 1),
	ztGuiItemBehaviorFlags_HasOutlyingChildren = (1 << 2),
	ztGuiItemBehaviorFlags_ClipChildren        = (1 << 3),
	ztGuiItemBehaviorFlags_ClipContents        = (1 << 4),
	ztGuiItemBehaviorFlags_BringToFront        = (1 << 5),
};

// --------------------------

#define ztGuiItemBehaviorFlags_MaxBit             5


// ------------------------------------------------------------------------------------------------

enum ztGuiItemStates_Enum
{
	ztGuiItemStates_Visible   = 1,
	ztGuiItemStates_Dirty     = 2,
	ztGuiItemStates_Disabled  = 3,
	ztGuiItemStates_Locked    = 4,
	ztGuiItemStates_HasFocus  = 5,
	ztGuiItemStates_MouseOver = 6,
	ztGuiItemStates_Resized   = 7,
	ztGuiItemStates_MAX,
};


// ------------------------------------------------------------------------------------------------

enum ztGuiThemeValue_Enum
{
	ztGuiThemeValue_r32_Padding,
	
	ztGuiThemeValue_r32_WindowTitleHeight,
	ztGuiThemeValue_i32_WindowCollapseButtonAlign,
	ztGuiThemeValue_i32_WindowCollapseButtonAnchor,
	ztGuiThemeValue_r32_WindowCollapseButtonOffsetX,
	ztGuiThemeValue_r32_WindowCollapseButtonOffsetY,
	ztGuiThemeValue_i32_WindowCollapseButtonBehaviorFlags,
	ztGuiThemeValue_i32_WindowCloseButtonAlign,
	ztGuiThemeValue_i32_WindowCloseButtonAnchor,
	ztGuiThemeValue_r32_WindowCloseButtonOffsetX,
	ztGuiThemeValue_r32_WindowCloseButtonOffsetY,
	ztGuiThemeValue_i32_WindowCloseButtonBehaviorFlags,
	ztGuiThemeValue_r32_WindowPaddingX,
	ztGuiThemeValue_r32_WindowPaddingY,
	ztGuiThemeValue_r32_WindowCornerResizeW,
	ztGuiThemeValue_r32_WindowCornerResizeH,

	ztGuiThemeValue_r32_CollapsingPanelHeight,
	ztGuiThemeValue_i32_CollapsingPanelButtonAlign,
	ztGuiThemeValue_i32_CollapsingPanelButtonAnchor,
	ztGuiThemeValue_r32_CollapsingPanelButtonOffsetX,
	ztGuiThemeValue_r32_CollapsingPanelButtonOffsetY,

	ztGuiThemeValue_r32_ButtonDefaultW,
	ztGuiThemeValue_r32_ButtonDefaultH,
	ztGuiThemeValue_r32_ButtonPaddingW,
	ztGuiThemeValue_r32_ButtonPaddingH,
	
	ztGuiThemeValue_r32_CheckboxW,
	ztGuiThemeValue_r32_CheckboxH,

	ztGuiThemeValue_r32_RadiobuttonW,
	ztGuiThemeValue_r32_RadiobuttonH,
	
	ztGuiThemeValue_r32_SliderHandleSize,
	ztGuiThemeValue_r32_SliderHandleMinHeight,
	
	ztGuiThemeValue_r32_ScrollbarButtonW, // vertical orient
	ztGuiThemeValue_r32_ScrollbarButtonH, // vertical orient
	ztGuiThemeValue_r32_ScrollbarMinHandleSize,
	ztGuiThemeValue_r32_ScrollbarMinWidth,
	
	ztGuiThemeValue_r32_ScrollContainerPaddingX,
	ztGuiThemeValue_r32_ScrollContainerPaddingY,
	
	ztGuiThemeValue_r32_TextEditPaddingX,
	ztGuiThemeValue_r32_TextEditPaddingY,
	ztGuiThemeValue_r32_TextEditDefaultW,
	ztGuiThemeValue_r32_TextEditDefaultH,
	ztGuiThemeValue_i32_TextEditFontID,
	
	ztGuiThemeValue_r32_MenuSubmenuIconX,
	ztGuiThemeValue_r32_MenuSubmenuIconY,
	ztGuiThemeValue_i32_MenuFontID,
	
	ztGuiThemeValue_r32_TreeIndent,
	ztGuiThemeValue_i32_TreeCollapseButtonAlign,
	ztGuiThemeValue_i32_TreeCollapseButtonAnchor,
	ztGuiThemeValue_i32_TreeCollapseButtonBehaviorFlags,
	
	ztGuiThemeValue_r32_ComboboxButtonW,
};

// ------------------------------------------------------------------------------------------------

struct ztGuiWindowState
{
	bool resizable;
	bool collapsable;
	bool is_collapsed;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiPanelState
{
	bool display_background;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiCollapsingPanelState
{
	bool is_collapsed;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiButtonState
{
	bool      is_toggled;
	bool      is_pressed;
	ztSprite *icon_sprite;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiTheme;

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_THEME_GET_RVALUE(name)	bool name(ztGuiTheme *theme, ztGuiThemeValue_Enum value, r32 *result)
typedef ZT_FUNC_THEME_GET_RVALUE(ztGuiThemeGetRValue_Func);

#define ZT_FUNC_THEME_GET_IVALUE(name) bool name(ztGuiTheme *theme, ztGuiThemeValue_Enum value, i32 *result)
typedef ZT_FUNC_THEME_GET_IVALUE(ztGuiThemeGetIValue_Func);

#define ZT_FUNC_THEME_UPDATE_ITEM(name) bool name(ztGuiTheme *theme, ztGuiItem *item)
typedef ZT_FUNC_THEME_UPDATE_ITEM(ztGuiThemeUpdateItem_Func);

#define ZT_FUNC_THEME_UPDATE_SUBITEM(name) bool name(ztGuiTheme *theme, ztGuiItem *item, ztGuiItem *subitem, void *data)
typedef ZT_FUNC_THEME_UPDATE_SUBITEM(ztGuiThemeUpdateSubitem_Func);

#define ZT_FUNC_THEME_SIZE_ITEM(name) bool name(ztGuiTheme *theme, ztGuiItem *item)
typedef ZT_FUNC_THEME_SIZE_ITEM(ztGuiThemeSizeItem_Func);

#define ZT_FUNC_THEME_RENDER_ITEM(name) bool name(ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos)
typedef ZT_FUNC_THEME_RENDER_ITEM(ztGuiThemeRenderItem_Func);

#define ZT_FUNC_THEME_RENDER_PASS_BEGIN(name) void name(ztGuiTheme *theme, ztGuiItem *item, ztDrawList *draw_list)
typedef ZT_FUNC_THEME_RENDER_PASS_BEGIN(ztGuiThemeRenderPassBegin_Func);

#define ZT_FUNC_THEME_RENDER_PASS_END(name) void name(ztGuiTheme *theme, ztGuiItem *item, ztDrawList *draw_list)
typedef ZT_FUNC_THEME_RENDER_PASS_END(ztGuiThemeRenderPassEnd_Func);

// ------------------------------------------------------------------------------------------------

enum ztGuiThemeFlags_Enum
{
	ztGuiThemeFlags_SeparatePasses = (1<<0), // will call the pass function after each top level window is drawn
};

// ------------------------------------------------------------------------------------------------

struct ztGuiTheme
{
	void          *theme_data;
	i32            flags;

	ztFunctionID   get_rvalue;
	ztFunctionID   get_ivalue;
	ztFunctionID   update_item;
	ztFunctionID   update_subitem;
	ztFunctionID   size_item;
	ztFunctionID   render_item;

	ztFunctionID   pass_begin;
	ztFunctionID   pass_end;
};

// ------------------------------------------------------------------------------------------------

r32  zt_guiThemeGetRValue    (ztGuiTheme *theme, ztGuiThemeValue_Enum value);
i32  zt_guiThemeGetIValue    (ztGuiTheme *theme, ztGuiThemeValue_Enum value);
void zt_guiThemeUpdateItem   (ztGuiTheme *theme, ztGuiItem *item);
void zt_guiThemeUpdateSubitem(ztGuiTheme *theme, ztGuiItem *item, ztGuiItem *subitem, void *data = nullptr);
void zt_guiThemeSizeItem     (ztGuiTheme *theme, ztGuiItem *item);
void zt_guiThemeRender       (ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos);


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

#define ZT_FUNC_GUI_ITEM_UPDATE(name) void name(ztGuiItem *item, r32 dt, void *user_data)
typedef ZT_FUNC_GUI_ITEM_UPDATE(zt_guiItemUpdate_Func);

#define ZT_FUNC_GUI_ITEM_RENDER(name) void name(ztGuiItem *item, ztDrawList *draw_list, ztGuiTheme *theme, const ztVec2& offset, bool enabled, void *user_data)
typedef ZT_FUNC_GUI_ITEM_RENDER(zt_guiItemRender_Func);

#define ZT_FUNC_GUI_ITEM_CLEANUP(name) void name(ztGuiItem *item, void *user_data)
typedef ZT_FUNC_GUI_ITEM_CLEANUP(zt_guiItemCleanup_Func);

#define ZT_FUNC_GUI_ITEM_BEST_SIZE(name) void name(ztGuiItem *item, ztVec2 *min_size, ztVec2 *max_size, ztVec2 *size, ztGuiTheme *theme, void *user_data)
typedef ZT_FUNC_GUI_ITEM_BEST_SIZE(zt_guiItemBestSize_Func);

#define ZT_FUNC_GUI_ITEM_INPUT_KEY(name) bool name(ztGuiItem *item, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], void *user_data)
typedef ZT_FUNC_GUI_ITEM_INPUT_KEY(zt_guiItemInputKey_Func);

#define ZT_FUNC_GUI_ITEM_INPUT_MOUSE(name) bool name(ztGuiItem *item, ztInputMouse *input_mouse, void *user_data)
typedef ZT_FUNC_GUI_ITEM_INPUT_MOUSE(zt_guiItemInputMouse_Func);

// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_GUI_BUTTON_PRESSED(name) void name(ztGuiItem *button, void *user_data)
typedef ZT_FUNC_GUI_BUTTON_PRESSED(zt_guiButtonPressed_Func);

#define ZT_FUNC_GUI_MENU_SELECTED(name) void name(ztGuiItem *menu, i32 menu_item, void *user_data)
typedef ZT_FUNC_GUI_MENU_SELECTED(zt_guiMenuSelected_Func);

#define ZT_FUNC_GUI_TEXTEDIT_KEY(name) void name(ztGuiItem *textedit, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], bool *should_process, void *user_data)
typedef ZT_FUNC_GUI_TEXTEDIT_KEY(zt_guiTextEditKey_Func);

#define ZT_FUNC_GUI_TREE_ITEM_SELECTED(name) void name(ztGuiItem *tree, ztGuiTreeNodeID node_id, void *user_data)
typedef ZT_FUNC_GUI_TREE_ITEM_SELECTED(zt_guiTreeItemSelected_Func);

#define ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(name) void name(ztGuiItem *combobox, int selected, void *user_data)
typedef ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(zt_guiComboBoxItemSelected_Func);

#define ZT_FUNC_GUI_SPINNER_VALUE_CHANGED(name) void name(ztGuiItem *spinner, int value, void *user_data)
typedef ZT_FUNC_GUI_SPINNER_VALUE_CHANGED(zt_guiSpinnerValueChanged_Func);

// ------------------------------------------------------------------------------------------------

struct ztGuiItemFunctions
{
	ztFunctionID update;
	ztFunctionID render;
	ztFunctionID cleanup;
	ztFunctionID best_size;
	ztFunctionID input_key;
	ztFunctionID input_mouse;

	void *user_data;
};

// ------------------------------------------------------------------------------------------------

enum ztGuiWindowBehaviorFlags_Enum
{
	ztGuiWindowBehaviorFlags_ShowTitle     = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiWindowBehaviorFlags_AllowDrag     = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
	ztGuiWindowBehaviorFlags_AllowResize   = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
	ztGuiWindowBehaviorFlags_AllowClose    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 4)),
	ztGuiWindowBehaviorFlags_AllowCollapse = (1 << (ztGuiItemBehaviorFlags_MaxBit + 5)),
	ztGuiWindowBehaviorFlags_CloseHides    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 6)),

	ztGuiWindowBehaviorFlags_Default = ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowCollapse,
};

#define ztGuiWindowBehaviorFlags_MaxBit   (ztGuiItemBehaviorFlags_MaxBit + 6)


// ------------------------------------------------------------------------------------------------

enum ztGuiPanelBehaviorFlags_Enum
{
	ztGuiPanelBehaviorFlags_AllowDrag      = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiPanelBehaviorFlags_DrawBackground = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

#define ztGuiPanelBehaviorFlags_MaxBit   (ztGuiItemBehaviorFlags_MaxBit + 2)


// ------------------------------------------------------------------------------------------------

enum ztGuiStaticTextBehaviorFlags_Enum
{
	ztGuiStaticTextBehaviorFlags_Fancy      = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiStaticTextBehaviorFlags_MonoSpaced = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiButtonBehaviorFlags_Enum
{
	ztGuiButtonBehaviorFlags_NoBackground = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiButtonBehaviorFlags_OnPressDip   = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiCheckboxBehaviorFlags_Enum
{
	ztGuiCheckboxBehaviorFlags_RightText = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiRadioButtonFlags_Enum
{
	ztGuiRadioButtonBehaviorFlags_RightText = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
};

#define ztGuiButtonBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 3)


// ------------------------------------------------------------------------------------------------

enum ztGuiScrollContainerBehaviorFlags_Enum
{
	ztGuiScrollContainerBehaviorFlags_ShowScrollVert = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiScrollContainerBehaviorFlags_ShowScrollHorz = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
	ztGuiScrollContainerBehaviorFlags_StretchVert    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
	ztGuiScrollContainerBehaviorFlags_StretchHorz    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 4)),
	ztGuiScrollContainerBehaviorFlags_NoBackground   = (1 << (ztGuiItemBehaviorFlags_MaxBit + 5)),
};

#define ztGuiScrollContainerBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 5)


// ------------------------------------------------------------------------------------------------

enum ztGuiTextEditBehaviorFlags_Enum
{
	ztGuiTextEditBehaviorFlags_MultiLine = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
};

#define ztGuiTextEditBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 1)


// ------------------------------------------------------------------------------------------------

enum ztGuiItemOrient_Enum
{
	ztGuiItemOrient_Horz = (1 << 1),
	ztGuiItemOrient_Vert = (1 << 2),
};

// ------------------------------------------------------------------------------------------------

ztGuiManager  *zt_guiManagerMake(ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena);
void           zt_guiManagerFree(ztGuiManager *gui_manager);

bool           zt_guiManagerHandleInput(ztGuiManager *gui_manager, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], ztInputMouse *input_mouse);
void           zt_guiManagerRender(ztGuiManager *gui_manager, ztDrawList *draw_list, r32 dt);

void           zt_guiSetActiveManager(ztGuiManager *gui_manager);

void           zt_guiManagerSetKeyboardFocus(ztGuiManager *gui_manager, bool keyboard_focus = true);
bool           zt_guiManagerHasKeyboardFocus(ztGuiManager *gui_manager);

bool           zt_guiManagerMouseOverGui(ztGuiManager *gui_manager);

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeWindow            (const char *title, i32 behavior_flags = ztGuiWindowBehaviorFlags_Default);
ztGuiItem *zt_guiMakeScrollWindow      (const char *title, i32 scroll_dir, i32 behavior_flags = ztGuiWindowBehaviorFlags_Default); // set the size of the content item
ztGuiItem *zt_guiMakePanel             (ztGuiItem *parent, i32 behavior_flags = 0, void *user_data = nullptr, ztMemoryArena *arena = nullptr); // user data is freed by the panel item
ztGuiItem *zt_guiMakeCollapsingPanel   (ztGuiItem *parent, const char *label);
ztGuiItem *zt_guiMakeStaticText        (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, i32 max_chars = 64);
ztGuiItem *zt_guiMakeButton            (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem *zt_guiMakeToggleButton      (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem *zt_guiMakeCheckbox          (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem *zt_guiMakeRadioButton       (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem *zt_guiMakeSlider            (ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItem *zt_guiMakeScrollbar         (ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItem *zt_guiMakeScrollContainer   (ztGuiItem *parent, i32 behavior_flags = 0);
ztGuiItem *zt_guiMakeTextEdit          (ztGuiItem *parent, const char *value, i32 behavior_flags = 0, i32 buffer_size = 1024);
ztGuiItem *zt_guiMakeMenu              ();
ztGuiItem *zt_guiMakeMenuBar           (ztGuiItem *parent);
ztGuiItem *zt_guiMakeTree              (ztGuiItem *parent, i32 max_items);
ztGuiItem *zt_guiMakeComboBox          (ztGuiItem *parent, i32 max_items);
ztGuiItem *zt_guiMakeSpriteDisplay     (ztGuiItem *parent, ztGuiThemeSprite *sprite);
ztGuiItem *zt_guiMakeSpinner           (ztGuiItem *parent, int *live_value = nullptr);
ztGuiItem *zt_guiMakeSizer             (ztGuiItem *parent, ztGuiItemOrient_Enum orient, bool size_to_parent = true);
ztGuiItem *zt_guiMakeColumnSizer       (ztGuiItem *parent, int columns, bool size_to_parent = true);

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, r32 *value, r32 min, r32 max, r32 step);
ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, i32 *value, i32 min, i32 max, i32 step);
ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec2 *value, ztVec2 min, ztVec2 max, r32 step = .1f, bool label_above = true, char *label_x = "X", char *label_y = "Y");
ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec3 *value, ztVec3 min, ztVec3 max, r32 step = .1f, bool label_above = true, char *label_x = "X", char *label_y = "Y", char *label_z = "Z");
ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec4 *value, ztVec4 min, ztVec4 max, r32 step = .1f, bool label_above = true, char *label_x = "X", char *label_y = "Y", char *label_z = "Z", char *label_w = "W");

// ------------------------------------------------------------------------------------------------

void       zt_guiItemFree                   (ztGuiItem *item_id);

void       zt_guiItemSetSize                (ztGuiItem *item, const ztVec2& size);
void       zt_guiItemAutoSize               (ztGuiItem *item);
void       zt_guiItemSetPosition            (ztGuiItem *item, const ztVec2& pos);
void       zt_guiItemSetPosition            (ztGuiItem *item, i32 align_flags, i32 anchor_flags, ztVec2 offset = ztVec2::zero);

void       zt_guiItemSetName                (ztGuiItem *item, const char *name);
void       zt_guiItemSetLabel               (ztGuiItem *item, const char *label);
void       zt_guiItemSetTooltip             (ztGuiItem *item, const char *tooltip);
void       zt_guiItemSetThemeType           (ztGuiItem *item, const char *theme_type);
void       zt_guiItemSetTheme               (ztGuiItem *item, ztGuiTheme *theme);

ztString   zt_guiItemGetName                (ztGuiItem *item);
ztString   zt_guiItemGetLabel               (ztGuiItem *item);
ztString   zt_guiItemGetTooltip             (ztGuiItem *item);
ztString   zt_guiItemGetThemeType           (ztGuiItem *item);

void       zt_guiItemSetAlign               (ztGuiItem *item, i32 align_flags);
i32        zt_guiItemGetAlign               (ztGuiItem *item);

bool       zt_guiItemIsShowing              (ztGuiItem *item);

void       zt_guiItemShow                   (ztGuiItem *item, bool show = true);
void       zt_guiItemHide                   (ztGuiItem *item);
bool       zt_guiItemIsVisible              (ztGuiItem *item);

void       zt_guiItemEnable                 (ztGuiItem *item, bool enable = true);
void       zt_guiItemDisable                (ztGuiItem *item);
bool       zt_guiItemIsEnabled              (ztGuiItem *item);

void       zt_guiItemBringToFront           (ztGuiItem *item);

ztGuiItem *zt_guiItemGetTopLevelParent      (ztGuiItem *item);
bool       zt_guiItemIsChildOf              (ztGuiItem *parent, ztGuiItem *child); // determine if the child is a descendent of the parent

ztGuiItem *zt_guiItemFindByName             (const char *name, ztGuiItem *parent = nullptr);
ztGuiItem *zt_guiItemFindByType             (ztGuiItemType_Enum type, ztGuiItem *parent = nullptr, ztGuiItem *find_after = nullptr);

ztVec2     zt_guiItemPositionLocalToScreen  (ztGuiItem *item, const ztVec2& pos);
ztVec2     zt_guiItemPositionScreenToLocal  (ztGuiItem *item, const ztVec2& pos);

void        zt_guiItemSetFocus              (ztGuiItem *item, ztGuiItem **prev_focus_item = nullptr);

ztGuiTheme *zt_guiItemGetTheme              (ztGuiItem *item);

void        zt_guiItemLock                  (ztGuiItem *item);
void        zt_guiItemUnlock                (ztGuiItem *item);

void        zt_guiItemReparent              (ztGuiItem *item, ztGuiItem *new_parent);

bool        zt_guiItemTopLevelIsOverlapping (ztGuiItem *item); // determine if there is another window below this one in z-order and is entirely or partially covered by this one

// ------------------------------------------------------------------------------------------------

void        zt_guiWindowSetMenuBar(ztGuiItem *window, ztGuiItem *menubar);
ztGuiItem  *zt_guiWindowGetContentParent(ztGuiItem *window);

// ------------------------------------------------------------------------------------------------

ztGuiItem  *zt_guiCollapsingPanelGetContentParent (ztGuiItem *panel);
void        zt_guiCollapsingPanelCollapse         (ztGuiItem *panel);
void        zt_guiCollapsingPanelExpand           (ztGuiItem *panel);

// ------------------------------------------------------------------------------------------------

// used for button and toggle button
void zt_guiButtonSetIcon         (ztGuiItem *button, ztSprite *icon);
void zt_guiButtonSetTextPosition (ztGuiItem *button, i32 align_flags);
void zt_guiButtonSetCallback     (ztGuiItem *button, ztFunctionID, void *user_data = nullptr);

// ------------------------------------------------------------------------------------------------

bool zt_guiToggleButtonGetValue(ztGuiItem *button);
void zt_guiToggleButtonSetValue(ztGuiItem *button, bool value);

// ------------------------------------------------------------------------------------------------

bool zt_guiCheckboxGetValue(ztGuiItem *checkbox);
void zt_guiCheckboxSetValue(ztGuiItem *checkbox, bool value);

// ------------------------------------------------------------------------------------------------

bool zt_guiRadioButtonGetValue(ztGuiItem *radio);
void zt_guiRadioButtonSetValue(ztGuiItem *radio, bool value);

// ------------------------------------------------------------------------------------------------

r32  zt_guiSliderGetValue(ztGuiItem *slider);
void zt_guiSliderSetValue(ztGuiItem *slider, r32 value);

// ------------------------------------------------------------------------------------------------

r32  zt_guiScrollbarGetValue     (ztGuiItem *scrollbar);
void zt_guiScrollbarSetValue     (ztGuiItem *scrollbar, r32 value);
void zt_guiScrollbarSetSteps     (ztGuiItem *scrollbar, r32 step_single, r32 step_page);
bool zt_guiScrollbarStepNeg      (ztGuiItem *scrollbar);
bool zt_guiScrollbarStepPageNeg  (ztGuiItem *scrollbar);
bool zt_guiScrollbarStepPos      (ztGuiItem *scrollbar);
bool zt_guiScrollbarStepPagePos  (ztGuiItem *scrollbar);
void zt_guiScrollbarSetPercent   (ztGuiItem *scrollbar, r32 percent); // what percent of the total scrolled area is current displayed

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerSetItem     (ztGuiItem *scroll, ztGuiItem *internal_item);
void zt_guiScrollContainerResetScroll (ztGuiItem *scroll);
void zt_guiScrollContainerSetScroll   (ztGuiItem *scroll, ztGuiItemOrient_Enum orient, r32 value);

// ------------------------------------------------------------------------------------------------

int    zt_guiTextEditGetValue       (ztGuiItem *text, char *buffer, int buffer_len);
void   zt_guiTextEditSetValue       (ztGuiItem *text, const char *value);
void   zt_guiTextEditSetSelection   (ztGuiItem *text, int sel_beg, int sel_end);
void   zt_guiTextEditGetSelection   (ztGuiItem *text, int *sel_beg, int *sel_end);
void   zt_guiTextEditSelectAll      (ztGuiItem *text);
int    zt_guiTextEditGetCursorPos   (ztGuiItem *text);
void   zt_guiTextEditSetCursorPos   (ztGuiItem *text, int cursor_pos);
void   zt_guiTextEditSetCallback    (ztGuiItem *text, ztFunctionID on_key, void *user_data = nullptr);
ztVec2 zt_guiTextEditGetCharacterPos(ztGuiItem *item, int ch, bool bottom_right);

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppend          (ztGuiItem *menu, const char *label, i32 id, void *user_data = nullptr, ztSprite *icon = nullptr);
void zt_guiMenuAppendSubmenu   (ztGuiItem *menu, const char *label, ztGuiItem *submenu, ztSprite *icon = nullptr);
void zt_guiMenuPopupAtItem     (ztGuiItem *menu, ztGuiItem *item, i32 align_flags, const ztVec2& offset = ztVec2::zero);
void zt_guiMenuPopupAtPosition (ztGuiItem *menu, const ztVec2& pos);
bool zt_guiMenuGetSelected     (ztGuiItem *menu, i32 *selected_id);
void zt_guiMenuSetCallback     (ztGuiItem *menu, ztFunctionID on_selected);

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID  zt_guiTreeAppend          (ztGuiItem *tree, const char *item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID);
ztGuiTreeNodeID  zt_guiTreeAppend          (ztGuiItem *tree, ztGuiItem *item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID);

ztGuiTreeNodeID  zt_guiTreeGetSelected     (ztGuiItem *tree);
void             zt_guiTreeSetSelected     (ztGuiItem *tree, ztGuiTreeNodeID node);

ztGuiTreeNodeID  zt_guiTreeGetRoot         (ztGuiItem *tree);
ztGuiItem       *zt_guiTreeGetNodeItem     (ztGuiItem *tree, ztGuiTreeNodeID node);
void            *zt_guiTreeGetNodeUserData (ztGuiItem *tree, ztGuiTreeNodeID node);
void             zt_guiTreeSetCallback     (ztGuiItem *tree, ztFunctionID on_item_sel, void *user_data);

void             zt_guiTreeClear           (ztGuiItem *tree);

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxSetContents     (ztGuiItem *combobox, const char **contents, int contents_count, int active);
void zt_guiComboBoxClear           (ztGuiItem *combobox);
void zt_guiComboBoxAppend          (ztGuiItem *combobox, const char *content, void *user_data = nullptr);
int  zt_guiComboBoxGetSelected     (ztGuiItem *combobox);
int  zt_guiComboBoxGetItemCount    (ztGuiItem *combobox);
int  zt_guiComboBoxGetItemText     (ztGuiItem *combobox, int index, char* buffer, int buffer_len);
void *zt_guiComboBoxGetItemUserData(ztGuiItem *combobox, int index);
void zt_guiComboBoxSetCallback     (ztGuiItem *combobox, ztFunctionID on_item_sel, void *user_data);

// ------------------------------------------------------------------------------------------------

void zt_guiSpriteDisplaySetSprite(ztGuiItem *item_id, ztGuiThemeSprite *sprite, const ztVec2& scale = ztVec2::one);

// ------------------------------------------------------------------------------------------------

int zt_guiSpinnerGetValue(ztGuiItem *spinner);	// -1 or +1
void zt_guiSpinnerSetCallback(ztGuiItem *spinner, ztFunctionID on_value_changed, void *user_data);

void zt_guiSpinnerTickUp(ztGuiItem *spinner);
void zt_guiSpinnerTickDown(ztGuiItem *spinner);

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToMin(ztGuiItem *editor);
void zt_guiEditorSetToMax(ztGuiItem *editor);
void zt_guiEditorSetToValue(ztGuiItem *editor, r32 value);
void zt_guiEditorSetToValue(ztGuiItem *editor, i32 value);
void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec2 value);
void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec3 value);
void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec4 value);

void zt_guiEditorReassign(ztGuiItem *editor, r32 *value);
void zt_guiEditorReassign(ztGuiItem *editor, i32 *value);
void zt_guiEditorReassign(ztGuiItem *editor, ztVec2 *value);
void zt_guiEditorReassign(ztGuiItem *editor, ztVec3 *value);
void zt_guiEditorReassign(ztGuiItem *editor, ztVec4 *value);

// ------------------------------------------------------------------------------------------------

void   zt_guiSizerAddItem(ztGuiItem *sizer, ztGuiItem *item_id, int proportion, r32 padding, i32 align_flags = ztAlign_Center, i32 grow_direction = ztGuiItemOrient_Horz | ztGuiItemOrient_Vert);
void   zt_guiSizerAddStretcher      (ztGuiItem *sizer, int proportion, r32 padding = 0);

void   zt_guiSizerSizeToParent      (ztGuiItem *sizer, bool size_to_parent = true);
void   zt_guiSizerSizeParent        (ztGuiItem *sizer, bool size_parent_x = true, bool size_parent_y = true);

void   zt_guiSizerRecalc            (ztGuiItem *item);
void   zt_guiSizerRecalcImmediately (ztGuiItem *sizer);

ztVec2 zt_guiSizerGetMinSize        (ztGuiItem *sizer);

void   zt_guiColumnSizerSetProp     (ztGuiItem *sizer, int col, int prop);

// ------------------------------------------------------------------------------------------------

void zt_guiInitDebug(ztGuiManager *gui_manager);

void zt_guiDebugHide();
void zt_guiDebugShow();
void zt_guiDebugToggle();

ztGuiItem *zt_guiDebugAddMetric(const char *sample); // returns a static text that will appear in the dropdown when [+] is pressed next to the fps display

// ------------------------------------------------------------------------------------------------

#define ztDebugConsoleParams(PARAMS)	char PARAMS[16][256]

#define ZT_FUNC_DEBUG_CONSOLE_COMMAND(name) void name(ztDebugConsoleParams(params), int params_count, void *user_data)
typedef ZT_FUNC_DEBUG_CONSOLE_COMMAND(zt_debugConsole_Func);

#define ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(name) void name(char **params, int params_count, char *auto_fill, int auto_fill_len, void *user_data)
typedef ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(zt_debugConsoleAutoComplete_Func);

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleAddCommand   (const char *command, const char *help, ztFunctionID command_func, ztFunctionID auto_complete_func, void *user_data = nullptr);
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

void zt_debugConsoleLog        (ztDebugConsoleLevel_Enum message_level, const char *command, ...);
void zt_debugConsoleLogUser    (const char *command, ...);
void zt_debugConsoleLogCommand (const char *command, ...);
void zt_debugConsoleLogHelp    (const char *command, ...);
void zt_debugConsoleLogWarning (const char *command, ...);
void zt_debugConsoleLogError   (const char *command, ...);
void zt_debugConsoleLogSystem  (const char *command, ...);

void zt_debugConsoleToggle     (bool *is_shown = nullptr);

// ------------------------------------------------------------------------------------------------

void zt_debugLogGuiHierarchy   (ztGuiItem *item);

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ZT_FUNC_DLL_SET_GAME_GUI_GLOBALS(name) void name(void *memory, int version)
typedef ZT_FUNC_DLL_SET_GAME_GUI_GLOBALS(zt_dllSetGameGuiGlobals_Func);

#if !defined(ZT_DLL)
void zt_dllSendGameGuiGlobals(zt_dllSetGameGuiGlobals_Func *set_globals);
#else
void zt_dllGuiLoad();
void zt_dllGuiUnload();
#endif


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

#ifndef __zt_game_gui_h_internal_included__
#define __zt_game_gui_h_internal_included__

#define ZT_GAME_INTERNAL_DECLARATIONS
#include "zt_game.h"

// GUI implementation

enum ztGuiSizerType_Enum
{
	ztGuiSizerType_Normal,
	ztGuiSizerType_Column,
};

#ifndef ZT_GUI_SIZER_MAX_COLUMNS
#define ZT_GUI_SIZER_MAX_COLUMNS	16
#endif

// ------------------------------------------------------------------------------------------------

struct ztGuiItem
{
	i32                 id;
	ztGuiItemType_Enum  type;

	ztString            name;
	ztString            label;
	ztString            tooltip;
	ztString            theme_type;

	ztVec2              size;
	ztVec2              pos;
	ztVec2              prev_size;

	i32                 align_flags;
	i32                 anchor_flags;
	i32                 pos_align_flags;
	i32                 pos_anchor_flags;
	i32                 custom_flags;

	ztVec2              pos_offset;
	ztVec4              color;
	ztVec4              clip_area;

	i32                 behavior_flags;
	i32                 state_flags;   // use zt_bit() with the ztGuiItemStates_Enum values
	r32                 state_length[32];
	i32                 prev_state_flags;

	ztGuiItem          *parent;
	ztGuiItem          *sib_next;
	ztGuiItem          *sib_prev;
	ztGuiItem          *first_child;

	ztGuiItemFunctions  functions;
	ztGuiTheme         *theme;

	ztDrawList         *draw_list;

	ztGuiManager       *gm;

	zt_debugOnly(ztColor debug_highlight);

	// -------------------------------------------------

	struct ztDragState
	{
		bool dragging;
		r32  offset_x;
		r32  offset_y;
	};

	// -------------------------------------------------

	struct ztSizerItemEntry
	{
		ztGuiItem        *item;
		int               proportion;
		r32               padding;
		int               align_flags;
		int               grow_direction;

		ztSizerItemEntry *next;
	};

	// -------------------------------------------------

	struct ztTreeItem
	{
		ztGuiTreeNodeID node_id;
		bool            expanded;
		ztGuiItem      *control_button;
		ztGuiItem      *item;
		void           *user_data;

		ztTreeItem     *first_child;
		ztTreeItem     *next;
		ztTreeItem     *parent;
	};

	// -------------------------------------------------

	union {
		struct {
			ztDragState drag_state;
			ztGuiItem  *menubar;
			ztGuiItem  *content;
			ztGuiItem  *button_collapse;
			ztGuiItem  *button_close;
			r32         resize[2];
			r32         pos[2];
			r32         size[2];

			// TODO(josh): need some way to keep track of focus on a per-window basis so switching back and forth between windows works as expected
		} window;

		// -------------------------------------------------

		struct {
			void *user_data;
			ztMemoryArena *arena;
			ztGuid guid;
		} panel;

		// -------------------------------------------------

		struct {
			ztGuiItem *content_panel;
			ztGuiItem *button;
		} collapsing_panel;

		// -------------------------------------------------

		struct {
			bool        *live_value;
			ztFunctionID on_pressed;
			void        *on_pressed_user_data;
			ztSprite    *icon;
			i32          text_pos;
		} button;

		// -------------------------------------------------

		struct {
			r32                 *live_value;
			r32                  value;
			ztGuiItemOrient_Enum orient;
			r32                  drag_pos[2];
			ztDragState          drag_state;
			bool                 highlight;
			r32                  handle_pos;
			r32                  handle_size;
			// scrollbar only
			int                  press_button;
			r32                  press_time;
			r32                  step, step_page, handle_pct;
		} slider;

		// -------------------------------------------------

		struct {
			ztGuiItem  *scrollbar_vert;
			ztGuiItem  *scrollbar_horz;
			ztGuiItem  *viewport;
			ztGuiItem  *contained_item;

			r32         scroll_amt_vert;
			r32         scroll_amt_horz;
			r32         viewport_pos[2];
			r32         viewport_size[2];
		} scrolled_container;

		// -------------------------------------------------

		struct {
			i32          cursor_pos;
			r32          cursor_blink_time;
			b32          cursor_vis;
			r32          cursor_xy[2];

			i32          select_beg;
			i32          select_end;

			bool         dragging;

			ztGuiItem   *scrollbar_vert;
			ztGuiItem   *scrollbar_horz;

			r32          scroll_amt_vert;
			r32          scroll_amt_horz;

			ztString     text_buffer;

			r32          content_size[2];
			r32          text_pos[2];
			r32          select_pos[4];

			ztFunctionID on_key;
			void        *on_key_user_data;
		} textedit;

		// -------------------------------------------------

		struct {
			ztString    *display;
			i32         *ids;
			ztGuiItem  **submenus;
			ztSprite   **icons;
			void       **user_datas;

			i32          item_count;
			i32          highlighted;
			i32          selected;
			bool         just_opened;

			ztFunctionID on_selected;
		} menu;

		// -------------------------------------------------

		struct {
			ztGuiSizerType_Enum      type;

			ztSizerItemEntry        *items;
			r32                      size[2];
			bool                     size_to_parent;
			bool                     size_parent_x, size_parent_y;

			union {
				// ztGuiSizerType_Normal
				ztGuiItemOrient_Enum orient;

				// ztGuiSizerType_Column
				struct {
					int              columns;
					i8               props[ZT_GUI_SIZER_MAX_COLUMNS];
				};
			};
		} sizer;

		// -------------------------------------------------

		struct {
			ztGuiItem      *container;
			ztGuiItem      *content;

			ztTreeItem     *root_item;
			ztTreeItem     *active_item;

			ztGuiTreeNodeID last_id;
			ztMemoryArena  *arena;

			ztFunctionID    on_item_sel;
			void           *on_item_sel_user_data;
		} tree;

		// -------------------------------------------------

		struct {
			ztGuiItem   *popup;

			ztString    *contents;
			void       **contents_user_data;
			int          contents_size;
			int          contents_count;
			int          selected;

			ztFunctionID on_selected;
			void        *on_selected_user_data;
		} combobox;

		// -------------------------------------------------

		struct {
			ztGuiThemeSprite* sprite;
			r32               scale[2];
		} sprite_display;

		// -------------------------------------------------

		struct {
			int          *live_value;
			int          value;
			r32          start[2];
			r32          time;
			int          last_dir;
			ztFunctionID on_value_changed;
			void        *on_value_changed_user_data;
		} spinner;

		// -------------------------------------------------
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
	i32            id;

	ztGuiItem     *item_has_mouse;
	ztVec2         mouse_pos;
	bool           mouse_over_gui;
	bool           mouse_click;
	bool           mouse_click_ignored;
	bool           keyboard_focus;
	bool           key_state_alt;
	bool           key_state_ctrl;
	bool           key_state_shift;
	r32            last_input_time;

	i32            internal_flags;

	ztCamera      *gui_camera;
	i32            gui_camera_w;
	i32            gui_camera_h;

	ztGuiItem     *focus_item;

	ztGuiItem     *tooltip_item;
	ztVec2         tooltip_pos;

	ztGuiItem     *first_child;

	ztGuiItem      item_cache      [1024 * 64];
	i32            item_cache_flags[1024 * 64];
	i32            item_cache_used;

	ztGuiTheme     default_theme;

	ztMemoryArena *arena;
	i32            base_id;

	ztGuiManager  *next;
};

// ------------------------------------------------------------------------------------------------

struct ztConsoleCommand
{
	char              command[32];
	char              help[1024];

	ztFunctionID      on_command;
	ztFunctionID      on_auto_complete;

	void             *user_data;

	ztConsoleCommand *next;
};

// ------------------------------------------------------------------------------------------------

struct ztGuiGlobals
{
	int               gui_managers_count           = 0;
	ztGuiManager     *gui_manager_active           = nullptr;
	ztGuiManager     *gui_manager_first            = nullptr;
	ztConsoleCommand *console_commands             = nullptr;
	ztGuiItem        *console_window               = nullptr;
	ztGuiItem        *console_display_container    = nullptr;
	ztGuiItem        *console_display              = nullptr;
	ztGuiItem        *console_command              = nullptr;

	ztMemoryArena    *arena = nullptr;
};

#define ZT_GAME_GUI_GLOBALS_VERSION   1 // update this any time ztGuiGlobals is changed

// ------------------------------------------------------------------------------------------------

enum ztGuiManagerInternalFlags_Enum
{
	ztGuiManagerInternalFlags_OwnsTheme = (1 << 0),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiWindowInternalBehaviorFlags_Enum
{
	ztGuiWindowInternalBehaviorFlags_ScrollHorz = (1 << (ztGuiWindowBehaviorFlags_MaxBit + 1)),
	ztGuiWindowInternalBehaviorFlags_ScrollVert = (1 << (ztGuiWindowBehaviorFlags_MaxBit + 2)),
};

zt_staticAssert(ztGuiWindowBehaviorFlags_MaxBit <= 29);


// ------------------------------------------------------------------------------------------------

enum ztGuiWindowInternalStates_Enum
{
	ztGuiWindowInternalStates_Resizing = (ztGuiItemStates_MAX + 1),
	ztGuiWindowInternalStates_Collapsed = (ztGuiItemStates_MAX + 2),
};


// ------------------------------------------------------------------------------------------------

enum ztGuiCollapsingPanelInternalStates_Enum
{
	ztGuiCollapsingPanelInternalStates_Collapsed = (ztGuiItemStates_MAX + 1),
	ztGuiCollapsingPanelInternalStates_Recalc = (ztGuiItemStates_MAX + 2),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiButtonInternalBehaviorFlags_Enum
{
	ztGuiButtonInternalBehaviorFlags_IsToggleButton = (1 << (ztGuiButtonBehaviorFlags_MaxBit + 1)),
	ztGuiButtonInternalBehaviorFlags_IsCheckbox     = (1 << (ztGuiButtonBehaviorFlags_MaxBit + 2)),
	ztGuiButtonInternalBehaviorFlags_IsRadio        = (1 << (ztGuiButtonBehaviorFlags_MaxBit + 3)),
};

enum ztGuiButtonInternalStates_Enum
{
	ztGuiButtonInternalStates_IsToggled = (ztGuiItemStates_MAX + 1),
};

// ------------------------------------------------------------------------------------

enum ztGuiSliderInternalStates_Enum
{
	ztGuiSliderInternalStates_NegHighlight = (ztGuiItemStates_MAX + 1),
	ztGuiSliderInternalStates_PosHighlight = (ztGuiItemStates_MAX + 2),
	ztGuiSliderInternalStates_NegPressed   = (ztGuiItemStates_MAX + 3),
	ztGuiSliderInternalStates_PosPressed   = (ztGuiItemStates_MAX + 4),
};

// ------------------------------------------------------------------------------------------------

enum ztGuiComboBoxInternalStates_Enum
{
	ztGuiComboBoxInternalStates_IgnorePopup = (ztGuiItemStates_MAX + 1),
};

// ------------------------------------------------------------------------------------------------


#if defined(ZT_GAME_GUI_INTERNAL_DECLARATIONS)
extern ztGuiGlobals *zt_gui;
#endif

// ------------------------------------------------------------------------------------------------

#define ZT_PROFILE_GUI(section)	ZT_PROFILE((section), "GUI")

// ------------------------------------------------------------------------------------------------

#endif // include guard
#endif // INTERNAL DECLARATIONS

#if defined(ZT_GAME_GUI_IMPLEMENTATION)

#ifndef __zt_game_gui_implementation__
#define __zt_game_gui_implementation__

// ------------------------------------------------------------------------------------------------

ztGuiGlobals zt_gui_local = {};

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugConsoleAddLoggingCallbacks();
ztInternal void _zt_guiDebugConsoleRemoveLoggingCallbacks();

// ------------------------------------------------------------------------------------------------

#if defined(ZT_DLL)
ztGuiGlobals *zt_gui = nullptr;

ZT_DLLEXPORT ZT_FUNC_DLL_SET_GAME_GLOBALS(zt_dllSetGameGuiGlobals)
{
	if (version == ZT_GAME_GUI_GLOBALS_VERSION) {
		zt_gui = (ztGuiGlobals *)memory;
	}
}

void zt_dllGuiLoad()
{
	_zt_guiDebugConsoleAddLoggingCallbacks();
}

void zt_dllGuiUnload()
{
	_zt_guiDebugConsoleRemoveLoggingCallbacks();
}

#else
ztGuiGlobals *zt_gui = &zt_gui_local;

void zt_dllSendGameGuiGlobals(zt_dllSetGameGuiGlobals_Func *set_globals)
{
	if (set_globals) {
		set_globals(zt_gui, ZT_GAME_GUI_GLOBALS_VERSION);
	}
}
#endif

// ------------------------------------------------------------------------------------------------

void zt_guiInitGlobalMemory(ztMemoryArena *arena)
{
	zt_gui->arena = arena;
	zt_gui->gui_manager_first = zt_gui->gui_manager_active = nullptr;
	zt_gui->gui_managers_count = 0;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeGetRValue, ztInternal ZT_FUNC_THEME_GET_RVALUE(_zt_guiDefaultThemeGetRValue))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetRValue");

	r32 ppu = zt_pixelsPerUnit();

	switch (value)
	{
		case ztGuiThemeValue_r32_Padding:                     *result =  3 / ppu; break;
		
		case ztGuiThemeValue_r32_WindowTitleHeight:           *result = 26 / ppu; break;
		case ztGuiThemeValue_r32_WindowCollapseButtonOffsetX: *result =  5 / ppu; break;
		case ztGuiThemeValue_r32_WindowCollapseButtonOffsetY: *result = -3 / ppu; break;
		case ztGuiThemeValue_r32_WindowCloseButtonOffsetX:    *result = -5 / ppu; break;
		case ztGuiThemeValue_r32_WindowCloseButtonOffsetY:    *result = -3 / ppu; break;
		case ztGuiThemeValue_r32_WindowPaddingX:              *result =  3 / ppu; break;
		case ztGuiThemeValue_r32_WindowPaddingY:              *result =  3 / ppu; break;
		case ztGuiThemeValue_r32_WindowCornerResizeW:         *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_WindowCornerResizeH:         *result = 16 / ppu; break;

		case ztGuiThemeValue_r32_CollapsingPanelHeight:       *result = 26 / ppu; break;

		case ztGuiThemeValue_r32_ButtonDefaultW:              *result = 96 / ppu; break;
		case ztGuiThemeValue_r32_ButtonDefaultH:              *result = 32 / ppu; break;
		case ztGuiThemeValue_r32_ButtonPaddingW:              *result =  3 / ppu; break;
		case ztGuiThemeValue_r32_ButtonPaddingH:              *result =  3 / ppu; break;

		case ztGuiThemeValue_r32_CheckboxW:                   *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_CheckboxH:                   *result = 16 / ppu; break;

		case ztGuiThemeValue_r32_RadiobuttonW:                *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_RadiobuttonH:                *result = 16 / ppu; break;
		
		case ztGuiThemeValue_r32_SliderHandleSize:            *result =  8 / ppu; break;
		case ztGuiThemeValue_r32_SliderHandleMinHeight:       *result = 20 / ppu; break;
		
		case ztGuiThemeValue_r32_ScrollbarButtonW:            *result = 16 / ppu; break;
        case ztGuiThemeValue_r32_ScrollbarButtonH:            *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinHandleSize:      *result =  8 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinWidth:           *result = 16 / ppu; break;
		
		case ztGuiThemeValue_r32_ScrollContainerPaddingX:     *result =  3 / ppu; break;
		case ztGuiThemeValue_r32_ScrollContainerPaddingY:     *result =  3 / ppu; break;
		
		case ztGuiThemeValue_r32_TextEditPaddingX:            *result =  2 / ppu; break;
		case ztGuiThemeValue_r32_TextEditPaddingY:            *result =  1 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultW:            *result = 90 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultH:            *result = 20 / ppu; break;
		
		case ztGuiThemeValue_r32_MenuSubmenuIconX:            *result =  1 / ppu; break;
		case ztGuiThemeValue_r32_MenuSubmenuIconY:            *result =  1 / ppu; break;
		
		case ztGuiThemeValue_r32_TreeIndent:                  *result = 12 / ppu; break;
		
		case ztGuiThemeValue_r32_ComboboxButtonW:             *result = 16 / ppu; break;

		default: return true;  // return false to use the default (this is the default though)
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeGetIValue, ztInternal ZT_FUNC_THEME_GET_IVALUE(_zt_guiDefaultThemeGetIValue))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetIValue");

	switch (value)
	{
		case ztGuiThemeValue_i32_WindowCollapseButtonAlign:         *result = ztAlign_Left | ztAlign_Top; break;
		case ztGuiThemeValue_i32_WindowCollapseButtonAnchor:        *result = ztAnchor_Left | ztAnchor_Top; break;
		case ztGuiThemeValue_i32_WindowCollapseButtonBehaviorFlags: *result = ztGuiButtonBehaviorFlags_NoBackground | ztGuiButtonBehaviorFlags_OnPressDip; break;
		case ztGuiThemeValue_i32_WindowCloseButtonAlign:            *result = ztAlign_Right | ztAlign_Top; break;
		case ztGuiThemeValue_i32_WindowCloseButtonAnchor:           *result = ztAnchor_Right | ztAnchor_Top; break;
		case ztGuiThemeValue_i32_WindowCloseButtonBehaviorFlags:    *result = ztGuiButtonBehaviorFlags_NoBackground | ztGuiButtonBehaviorFlags_OnPressDip; break;

		case ztGuiThemeValue_i32_CollapsingPanelButtonAlign:        *result = ztAlign_Left | ztAlign_Top; break;
		case ztGuiThemeValue_i32_CollapsingPanelButtonAnchor:       *result = ztAnchor_Left | ztAnchor_Top; break;
		
		case ztGuiThemeValue_i32_TextEditFontID:                    *result = ztFontDefault; break;
		
		case ztGuiThemeValue_i32_MenuFontID:                        *result = ztFontDefault; break;
		
		case ztGuiThemeValue_i32_TreeCollapseButtonAlign:           *result = ztAlign_Center; break;
		case ztGuiThemeValue_i32_TreeCollapseButtonAnchor:          *result = ztAnchor_Center; break;
		case ztGuiThemeValue_i32_TreeCollapseButtonBehaviorFlags:   *result = ztGuiButtonBehaviorFlags_NoBackground | ztGuiButtonBehaviorFlags_OnPressDip; break;
		
		default: return true;  // return false to use the default (this is the default though)
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeUpdateItem, ztInternal ZT_FUNC_THEME_UPDATE_ITEM(_zt_guiDefaultThemeUpdateItem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeUpdateItem");

	r32 ppu = zt_pixelsPerUnit();

//	switch (item->type)
//	{
//
//		default: return true;  // return false to use the default (this is the default though)
//	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeUpdateSubitem, ztInternal ZT_FUNC_THEME_UPDATE_SUBITEM(_zt_guiDefaultThemeUpdateSubitem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeUpdateSubitem");

	r32 ppu = zt_pixelsPerUnit();

	switch (item->type)
	{
		case ztGuiItemType_Window: {
			switch (subitem->type)
			{
				case ztGuiItemType_Button: {
					char *name = zt_guiItemGetName(subitem);

					if (zt_strEquals(name, "Close")) {
						zt_guiItemSetLabel(subitem, "X");
					}
					else if (zt_strEquals(name, "Collapse")) {
						if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
							zt_guiItemSetLabel(subitem, ">");
						}
						else {
							zt_guiItemSetLabel(subitem, "v");
						}
					}
					zt_guiItemSetSize(subitem, ztVec2(21 / ppu, 21 / ppu));
				} break;
			}

		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_CollapsingPanel : {
			switch (subitem->type)
			{
				case ztGuiItemType_Button: {
					if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
						zt_guiItemSetLabel(subitem, ">");
					}
					else {
						zt_guiItemSetLabel(subitem, "v");
					}
					zt_guiItemSetSize(subitem, ztVec2(21 / ppu, 21 / ppu));
				} break;
			}

		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Tree: {
			switch (subitem->type)
			{
				case ztGuiItemType_Button: {
					if (data == nullptr || *((bool*)data) == true) {
						zt_guiItemSetLabel(subitem, "-");
					}
					else {
						zt_guiItemSetLabel(subitem, "+");
					}
					zt_guiItemSetSize(subitem, ztVec2(17 / ppu, 17 / ppu));
				} break;
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		default: return true; // return false to use the default (this is the default though)
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeSizeItem, ztInternal ZT_FUNC_THEME_SIZE_ITEM(_zt_guiDefaultThemeSizeItem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeSizeItem");

	r32 ppu = zt_pixelsPerUnit();

	switch (item->type)
	{
		case ztGuiItemType_CollapsingPanel: {
			ztVec2 ext = zt_fontGetExtents(ztFontDefault, item->label);
			ztVec2 m_size = ext;
			r32 padding = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, &padding);
			m_size.x += padding * 2;
			r32 panel_height = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelHeight, &panel_height);
			m_size.y = zt_max(m_size.y, panel_height);

			item->size.x = zt_max(item->size.x, m_size.x);
			item->size.y = zt_max(item->size.y, m_size.y);
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_StaticText: {
			item->size = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(0, item->label) : zt_fontGetExtents(ztFontDefault, item->label);
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_ToggleButton:
		case ztGuiItemType_Button: {
			r32 button_padding_w = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ButtonPaddingW, &button_padding_w);
			r32 button_padding_h = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ButtonPaddingH, &button_padding_h);

			ztVec2 text_size = item->label ? zt_fontGetExtents(ztFontDefault, item->label) : ztVec2::zero;
			if (item->button.icon) {
				ztVec2 content_size = ztVec2::zero;
				ztVec2 icon_size(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);
				ztVec2 icon_pos = ztVec2::zero;

				if (zt_bitIsSet(item->button.text_pos, ztAlign_Left)) {
					content_size = ztVec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
				}
				else if (zt_bitIsSet(item->button.text_pos, ztAlign_Right)) {
					content_size = ztVec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
				}
				else if (zt_bitIsSet(item->button.text_pos, ztAlign_Top)) {
					content_size = ztVec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
				}
				else if (zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
					content_size = ztVec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
				}
				else {
					content_size.x = zt_max(icon_size.x, text_size.x);
					content_size.y = zt_max(icon_size.y, text_size.y);
				}

				content_size.x += button_padding_w * 2.f;
				content_size.y += button_padding_h * 2.f;

				item->size = content_size;
			}
			else {
				r32 min_x = text_size.x + button_padding_w * 2;
				r32 min_y = text_size.y + button_padding_h * 2;
				r32 button_default_w = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ButtonDefaultW, &button_default_w);
				r32 button_default_h = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ButtonDefaultH, &button_default_h);
				item->size.x = zt_max(min_x, button_default_w);
				item->size.y = zt_max(min_y, button_default_h);
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Checkbox:
		case ztGuiItemType_RadioButton: {
			ztVec2 txt_size = zt_fontGetExtents(ztFontDefault, item->label);
			r32 padding    = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, &padding);
			r32 checkbox_w = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_CheckboxW, &checkbox_w);
			r32 checkbox_h = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_CheckboxW, &checkbox_h);
			item->size.x = txt_size.x + padding + checkbox_w;
			item->size.y = zt_max(txt_size.y, checkbox_h);
			
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_MenuBar:
		case ztGuiItemType_Menu: {
			ztVec2 icon_orig(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY));
			ztVec2 icon = icon_orig;
			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding);
			zt_fiz(item->menu.item_count) {
				if (item->menu.icons[i] != nullptr) {
					icon.x = zt_max(icon.x, item->menu.icons[i]->half_size.x * 2.f + padding * 2.f);
					icon.y = zt_max(icon.y, item->menu.icons[i]->half_size.y * 2.f);
				}
			}

			item->size = ztVec2::zero;

			ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_MenuFontID);
			if (item->type == ztGuiItemType_Menu) {
				zt_fiz(item->menu.item_count) {
					ztVec2 ext = zt_fontGetExtents(font, item->menu.display[i]);

					item->size.y += zt_max(zt_max(icon.y, ext.y), icon_orig.y) + padding;
					item->size.x = zt_max(item->size.x, ext.x + icon.x + icon_orig.x + padding * 3.f);
				}
				item->size.y += padding;
			}
			else {
				zt_fiz(item->menu.item_count) {
					ztVec2 ext = zt_fontGetExtents(font, item->menu.display[i]);
					
					if (item->menu.icons[i] != nullptr) {
						ext.x += icon.x;
						ext.y = zt_max(ext.y, icon.y);
					}

					item->size.y = zt_max(item->size.y, ext.y);
					item->size.x += ext.x;
				}
				item->size.y += padding * 2;
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_ComboBox: {
			item->size.x = 80 / ppu;
			item->size.y = 22 / ppu;
		} break;


		case ztGuiItemType_Spinner: {
			item->size.x = 20 / ppu;
			item->size.y = 20 / ppu;
		} break;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeRenderItem, ztInternal ZT_FUNC_THEME_RENDER_ITEM(_zt_guiDefaultThemeRenderItem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem");

	struct local
	{
		static ztColor outline(bool highlighted, bool pressed)
		{
			if (pressed) return ztColor(1, 1, 1, 1);
			if (highlighted) return ztColor(1, 1, 1, 1);
			return ztColor(1, 1, 1, 1);
		}

		static ztColor face(bool highlighted, bool pressed)
		{
			if (pressed) return ztColor(.15f, .15f, .15f, .85f);
			if (highlighted) return ztColor(.25f, .25f, .25f, 1);
			return ztColor(0, 0, 0, .85f);
		}
	};

	r32 ppu = zt_pixelsPerUnit();
	bool has_focus   = zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_HasFocus));
	bool highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
	bool pressed     = (highlighted && item->gm->item_has_mouse == item) || (!highlighted && zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled)));
	bool enabled     = true;

	switch (item->type)
	{
		case ztGuiItemType_Window: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Window");

			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
				ztVec2 win_size(item->size.x, 25 / ppu);
				ztVec2 win_pos(pos.x, pos.y + (item->size.y / 2) - (win_size.y / 2));
				zt_drawListAddSolidOutlinedRect2D(draw_list, win_pos, win_size, (has_focus ? local::face(false, false) : ztColor(0, 0, 0, .85f)), (has_focus ? local::outline(false, false) : ztColor(.65f, .65f, .65f, 1)));
			}
			else {
				zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, (has_focus ? local::face(false, false) : ztColor(0, 0, 0, .85f)), (has_focus ? local::outline(false, false) : ztColor(.65f, .65f, .65f, 1)));

				if (zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_AllowResize)) {
					ztVec2 pos_corner(pos.x + item->size.x / 2.f - 3 / ppu, pos.y - item->size.y / 2.f + 2 / ppu);

					zt_drawListPushColor(draw_list, local::outline(false, false));
					zt_fiz(4) {
						ztVec3 top(pos_corner.x, pos_corner.y + ((i + 1) / ppu) * 3, 0);
						ztVec3 btm(pos_corner.x - ((i + 1) / ppu) * 3, pos_corner.y, 0);

						zt_drawListAddLine(draw_list, top, btm);
					}
					zt_drawListPopColor(draw_list);
				}
			}

			if (item->label != nullptr) {
				ztVec2 title_pos(pos.x, pos.y + (item->size.y / 2) - (3 / ppu));
				ztVec2 title_size;
				zt_drawListAddText2D(draw_list, 0, item->label, title_pos, ztAlign_Top, ztAnchor_Top, &title_size);
				title_size.y += 6 / ppu;
				zt_drawListPushColor(draw_list, has_focus ? local::outline(false, false) : ztColor(.65f, .65f, .65f, 1));
				zt_drawListAddLine(draw_list, ztVec3((title_pos + ztVec2(item->size.x / -2, -title_size.y)), 0), ztVec3((title_pos + ztVec2(item->size.x / 2, -title_size.y)), 0));
				zt_drawListPopColor(draw_list);
			}

		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Panel: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Panel");

			if (zt_bitIsSet(item->behavior_flags, ztGuiPanelBehaviorFlags_DrawBackground)) {
				zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(false, false), local::outline(false, false));
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_CollapsingPanel: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:CollapsingPanel");

			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, highlighted ? local::face(true, false) : ztColor(.1f, .1f, .2f, 1), local::outline(highlighted, false));

			if (item->label != nullptr) {
				r32 panel_height = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelHeight, &panel_height);

				ztVec2 title_pos(pos.x - ((item->size.x) / 2) + 25 / ppu, pos.y + (item->size.y - (panel_height)) / 2);
				ztVec2 title_size;

//				if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed)) {
//				}
				zt_drawListAddText2D(draw_list, 0, item->label, title_pos, ztAlign_Left, ztAnchor_Left, &title_size);
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_StaticText: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:StaticText");

			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty))) {
				if (item->draw_list) {
					ztVec2 ext = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(0, item->label) : zt_fontGetExtents(ztFontDefault, item->label);
					ztVec2 off = ztVec2::zero;

					if (item->align_flags != 0) {
						if (zt_bitIsSet(item->align_flags, ztAlign_Left  )) off.x -= (item->size.x - ext.x) / 2.f;
						if (zt_bitIsSet(item->align_flags, ztAlign_Right )) off.x += (item->size.x - ext.x) / 2.f;
						if (zt_bitIsSet(item->align_flags, ztAlign_Top   )) off.y += (item->size.y - ext.y) / 2.f;
						if (zt_bitIsSet(item->align_flags, ztAlign_Bottom)) off.y -= (item->size.y - ext.y) / 2.f;
					}

					ztGuiTheme *theme = zt_guiItemGetTheme(item);
					zt_drawListReset(item->draw_list);
					if (zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy)) {
						zt_drawListAddFancyText2D(item->draw_list, ztFontDefault, item->label, off, item->align_flags, item->anchor_flags);
					}
					else {
						zt_drawListAddText2D(item->draw_list, ztFontDefault, item->label, off, item->align_flags, item->anchor_flags);
					}
				}
			}

			zt_alignToPixel(&pos, zt_pixelsPerUnit());
			zt_drawListAddDrawList(draw_list, item->draw_list, ztVec3(pos, 0));
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_ToggleButton:
		case ztGuiItemType_Button: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Button");

			if (!zt_bitIsSet(item->behavior_flags, ztGuiButtonBehaviorFlags_NoBackground) || pressed || highlighted) {
				zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(highlighted, pressed), local::outline(highlighted, pressed));
			}

			r32 button_padding_w = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ButtonPaddingW, &button_padding_w);
			r32 button_padding_h = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ButtonPaddingH, &button_padding_h);

			ztVec2 text_pos = ztVec2::zero;
			if (item->button.icon) {
				ztVec2 text_size = item->label ? zt_fontGetExtents(ztFontDefault, item->label) : ztVec2::zero;
				ztVec2 content_size = ztVec2::zero;
				ztVec2 icon_size(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);
				ztVec2 icon_pos = text_pos;

				if (item->label != nullptr) {
					if (zt_bitIsSet(item->button.text_pos, ztAlign_Left)) {
						content_size = ztVec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
						icon_pos.x = (content_size.x - icon_size.x) / 2.f;
						text_pos.x = (content_size.x - text_size.x) / -2.f;
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Right)) {
						content_size = ztVec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
						icon_pos.x = (content_size.x - icon_size.x) / -2.f;
						text_pos.x = (content_size.x - text_size.x) / 2.f;
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Top)) {
						content_size = ztVec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
						icon_pos.y = (content_size.y - icon_size.y) / -2.f;
						text_pos.y = (content_size.y - text_size.y) / 2.f;
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
						content_size = ztVec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
						icon_pos.y = (content_size.y - icon_size.y) / 2.f;
						text_pos.y = (content_size.y - text_size.y) / -2.f;
					}
				}
				else {
					content_size = icon_size;
				}

				ztVec2 item_size = ztVec2(item->size.x - button_padding_w * 2.f, item->size.y - button_padding_h * 2.f);
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
				zt_drawListAddFancyText2D(draw_list, 0, item->label, pos + text_pos, item->align_flags);
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Checkbox:
		case ztGuiItemType_RadioButton: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:CheckRadio");

			bool checkbox = zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsCheckbox);
			bool radio    = zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio);

			r32 checkbox_w = 0; _zt_guiDefaultThemeGetRValue(theme, item->type == ztGuiItemType_Checkbox ? ztGuiThemeValue_r32_CheckboxW : ztGuiThemeValue_r32_RadiobuttonW, &checkbox_w);
			r32 checkbox_h = 0; _zt_guiDefaultThemeGetRValue(theme, item->type == ztGuiItemType_Checkbox ? ztGuiThemeValue_r32_CheckboxW : ztGuiThemeValue_r32_RadiobuttonW, &checkbox_h);
			r32 padding    = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, &padding);

			ztVec2 box_size = ztVec2(checkbox_w, checkbox_h);
			ztVec2 box_pos, txt_size, txt_pos;

			if (item->label) {
				txt_size = zt_fontGetExtents(ztFontDefault, item->label);
				if (zt_bitIsSet(item->behavior_flags, ztGuiCheckboxBehaviorFlags_RightText)) {
					box_pos = ztVec2((item->size.x - box_size.x) / -2.f, 0);
					txt_pos = ztVec2(box_pos.x + box_size.x / 2.f + padding, 0);
				}
				else {
					txt_pos = ztVec2(item->size.x / -2.f, 0);
					box_pos = ztVec2((item->size.x / 2.f) - (box_size.x / 2.f), 0);
				}

				zt_drawListAddText2D(draw_list, ztFontDefault, item->label, zt_strLen(item->label), txt_pos + pos, ztAlign_Left, ztAnchor_Left);
			}

			box_pos += pos;

			if (checkbox) {
				zt_drawListAddSolidOutlinedRect2D(draw_list, ztVec3(box_pos, 0), box_size, local::face(highlighted, pressed), local::outline(highlighted, pressed));

				if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled))) {
					zt_drawListAddSolidRect2D(draw_list, ztVec3(box_pos, 0), box_size - ztVec2(8 / ppu, 8 / ppu), ztColor(.7f, .7f, .7f, 1));
				}
			}
			else if (radio) {
				zt_drawListAddSolidOutlinedCircle2D(draw_list, ztVec3(box_pos, 0), box_size.x / 2.f, 8, local::face(highlighted, pressed), local::outline(highlighted, pressed));

				if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled))) {
					zt_drawListAddSolidCircle2D(draw_list, ztVec3(box_pos, 0), (box_size.x - 8 / ppu) / 2.f, 8, ztColor(.7f, .7f, .7f, 1));
				}
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Scrollbar:
		case ztGuiItemType_Slider: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:ScrollbarSlider");

			ztVec2 handle_pos, handle_size;

			if (item->slider.drag_state.dragging) {
				highlighted = true;
			}

			r32 scrollbar_button_w = 0;
			_zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, &scrollbar_button_w);

			if (item->slider.orient == ztGuiItemOrient_Horz) {
				handle_pos = pos + ztVec2(item->slider.handle_pos, 0);

				if (item->type == ztGuiItemType_Slider) {
					zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size - ztVec2(0, 10 / ppu), local::face(highlighted && !item->slider.highlight, false), local::outline(highlighted && !item->slider.highlight, false));
					handle_size = ztVec2(zt_max(8 / ppu, item->slider.handle_size), item->size.y);
				}
				else {
					zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(false, false), local::outline(false, false));
					handle_size = ztVec2( zt_max(10 / ppu, item->slider.handle_size),item->size.y);

					ztVec2 btn_size(16 / ppu, 16 / ppu);
					bool neg_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegHighlight)), neg_pressed = neg_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)),
					     pos_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosHighlight)), pos_pressed = pos_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed));

					zt_drawListAddSolidOutlinedRect2D(draw_list, pos + ztVec2(item->size.x / -2.f + scrollbar_button_w / 2.f, 0), btn_size, local::face(neg_highlight, neg_pressed), local::outline(neg_highlight, neg_pressed));
					zt_drawListAddSolidOutlinedRect2D(draw_list, pos + ztVec2(item->size.x /  2.f - scrollbar_button_w / 2.f, 0), btn_size, local::face(pos_highlight, pos_pressed), local::outline(pos_highlight, pos_pressed));
				}
			}
			else {
				handle_pos = pos + ztVec2(0, item->slider.handle_pos);
				if (item->type == ztGuiItemType_Slider) {
					zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size - ztVec2(6 / ppu, 0), local::face(highlighted && !item->slider.highlight, false), local::outline(highlighted && !item->slider.highlight, false));
					handle_size = ztVec2(item->size.x, zt_max(10 / ppu, item->slider.handle_size));
				}
				else {
					zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(false, false), local::outline(false, false));
					handle_size = ztVec2(item->size.x, zt_max(10 / ppu, item->slider.handle_size));

					ztVec2 btn_size(16 / ppu, 16 / ppu);
					bool neg_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegHighlight)), neg_pressed = neg_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)),
					     pos_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosHighlight)), pos_pressed = pos_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed));

					zt_drawListAddSolidOutlinedRect2D(draw_list, pos + ztVec2(0, item->size.y /  2.f - scrollbar_button_w / 2.f), btn_size, local::face(neg_highlight, neg_pressed), local::outline(neg_highlight, neg_pressed));
					zt_drawListAddSolidOutlinedRect2D(draw_list, pos + ztVec2(0, item->size.y / -2.f + scrollbar_button_w / 2.f), btn_size, local::face(pos_highlight, pos_pressed), local::outline(pos_highlight, pos_pressed));
				}
			}


			if (enabled) {
				bool highlight = item->slider.highlight && zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
				bool pressed = item->slider.drag_state.dragging;
				zt_drawListAddSolidOutlinedRect2D(draw_list, handle_pos, handle_size, local::face(highlight, pressed), local::outline(highlight, pressed));
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_TextEdit: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:TextEdit");

			ztVec2 size = item->size;
			zt_alignToPixel(&size, zt_pixelsPerUnit());
			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, size, local::face(false, false), local::outline(false, false));

			ztVec2 text_pos(item->textedit.text_pos[0], item->textedit.text_pos[1]);

			if (item->textedit.select_beg != item->textedit.select_end) {
				int sel_beg = zt_min(item->textedit.select_beg, item->textedit.select_end);
				int sel_end = zt_max(item->textedit.select_beg, item->textedit.select_end);

				while (sel_beg < sel_end) {
					ztVec2 pos_beg = zt_guiTextEditGetCharacterPos(item, sel_beg, false);

					int idx_end_line = zt_strFindPos(item->textedit.text_buffer, "\n", sel_beg);
					if (idx_end_line == ztStrPosNotFound || idx_end_line > sel_end) {
						idx_end_line = sel_end;
					}

					ztVec2 pos_end = zt_guiTextEditGetCharacterPos(item, idx_end_line, true);

					ztVec2 pos_size = ztVec2(pos_end.x - pos_beg.x, pos_beg.y - pos_end.y);
					ztVec2 pos_center = ztVec2(pos_beg.x + pos_size.x / 2.f, pos_beg.y - pos_size.y / 2.f);

					zt_drawListAddSolidRect2D(draw_list, ztVec3(text_pos + pos_center, 0), pos_size, ztColor(.5f, .5f, 1, .5f));

					sel_beg = idx_end_line + 1;
				}
			}

			ztVec3 dlpos(text_pos, 0);
			zt_alignToPixel(&dlpos, zt_pixelsPerUnit());
			zt_drawListAddDrawList(draw_list, item->draw_list, dlpos);

			if (item->gm->focus_item == item) {
				if (item->textedit.cursor_vis) {
					ztFontID font = ztFontDefault;
					ztVec2 cursor_pos = text_pos + ztVec2(item->textedit.cursor_xy[0], item->textedit.cursor_xy[1]);
					ztVec2 cursor_size = zt_fontGetExtents(font, "|");
					cursor_pos.x -= cursor_size.x / 2;
					zt_drawListAddText2D(draw_list, font, "|", cursor_pos, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);
				}
			}

		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_MenuBar:
		case ztGuiItemType_Menu: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Menu");

			if (item->type == ztGuiItemType_Menu) {
				zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(false, false), local::outline(false, false));
			}
			else {
				zt_drawListPushTexture(draw_list, 0);
				zt_drawListPushColor(draw_list, local::face(false, false));
				zt_drawListAddFilledRect2D(draw_list, pos, item->size, ztVec2::zero, ztVec2::one);
				zt_drawListPopColor(draw_list);
				zt_drawListPopTexture(draw_list);
				zt_drawListPushColor(draw_list, local::outline(false, false));
				zt_drawListAddLine(draw_list, ztVec3(pos, 0) - ztVec3(item->size.x / 2, item->size.y / 2, 0), ztVec3(pos, 0) + ztVec3(item->size.x / 2, item->size.y / -2, 0));
				zt_drawListPopColor(draw_list);
			}

			r32 padding = 0;  _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, &padding);
			pos.x -= (item->size.x - padding * 2.f) / 2.f;
			pos.y += (item->size.y - padding * 2.f) / 2.f;

			ztVec2 icon; 
			_zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, &icon.x);
			_zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, &icon.y);

			zt_fiz(item->menu.item_count) {
				if (item->menu.icons[i] != nullptr) {
					icon.x = zt_max(icon.x, item->menu.icons[i]->half_size.x * 2.f + padding * 2.f);
					icon.y = zt_max(icon.y, item->menu.icons[i]->half_size.y * 2.f);
				}
			}

			zt_fiz(item->menu.item_count) {
				ztVec2 ext = zt_fontGetExtents(ztFontDefault, item->menu.display[i]);

				if (item->menu.highlighted == i && highlighted) {
					if (item->type == ztGuiItemType_Menu) {
						zt_drawListAddSolidRect2D(draw_list, ztVec2(pos.x + item->size.x / 2 - padding, pos.y - ext.y / 2.f), ztVec2(item->size.x - padding * 2.f, ext.y + 2 / ppu), ztColor(.5f, .5f, 1, .5f));
					}
					else {
						zt_drawListAddSolidRect2D(draw_list, ztVec2(pos.x + ext.x / 2, pos.y - ext.y / 2.f), ztVec2(ext.x + padding * 2, ext.y + 2 / ppu), ztColor(.5f, .5f, 1, .5f));
					}
				}
				zt_drawListAddText2D(draw_list, ztFontDefault, item->menu.display[i], ztVec2(pos.x + icon.x, pos.y - ext.y / 2.f + padding), ztAlign_Left, ztAnchor_Left);

				if (item->menu.icons[i] != nullptr) {
					r32 y = zt_max(item->menu.icons[i]->half_size.y, ext.y / 2.f);
					zt_drawListAddSprite(draw_list, item->menu.icons[i], ztVec3(pos.x + padding + item->menu.icons[i]->half_size.x, pos.y - y, 0));
				}

				if (item->type == ztGuiItemType_Menu) {
					if (item->menu.submenus[i] != nullptr) {
						r32 icon_x = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, &icon_x);
						r32 icon_y = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, &icon_y);
						r32 y = zt_max(icon_y, ext.y) / 2.f;
						zt_drawListAddText2D(draw_list, ztFontDefault, ">", ztVec2((item->size.x + pos.x) - (padding * 3 + icon_x / 2.f), pos.y - y + padding));
					}

					pos.y -= zt_max(icon.y, ext.y) + padding;
				}
				else {
					pos.x += icon.x + padding + ext.x + padding;
				}
			}
		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Tree: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Tree");

			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(false, false), local::outline(false, false));

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
					ztGuiItem *active = item->tree.active_item->item;
					if (active) {
						ztVec2 npos = zt_guiItemPositionLocalToScreen(active, ztVec2::zero);
						zt_drawListAddSolidRect2D(draw_list, ztVec2(pos.x, npos.y), ztVec2(item->size.x, active->size.y), ztColor(.5f, .5f, 1, .25f));
					}
				}
			}

		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_ComboBox: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Combobox");

			bool pressed = false, highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(highlighted, pressed), local::outline(highlighted, pressed));

			r32 padding = 0;  _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, &padding);
			pos.y += padding;

			r32 button_w = 0; _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_ComboboxButtonW, &button_w);
			zt_drawListAddText2D(draw_list, ztFontDefault, "v", ztVec2(pos.x + (item->size.x - button_w) / 2, pos.y));

			if (item->combobox.selected >= 0 && item->combobox.selected < item->combobox.contents_count) {
				pos.x = (pos.x) + (item->size.x / -2.f + padding);
				zt_drawListAddFancyText2D(draw_list, ztFontDefault, item->combobox.contents[item->combobox.selected], pos, ztAlign_Left, ztAnchor_Left);
			}

		} break;

		// ------------------------------------------------------------------------------------------------

		case ztGuiItemType_Spinner: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Spinner");

			bool pressed = item->gm->item_has_mouse == item;
			bool highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);

			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(highlighted, pressed), local::outline(highlighted, pressed));
			zt_drawListAddLine(draw_list, ztVec3(pos.x - item->size.x / 2 + (1/ppu), pos.y, 0), ztVec3(pos.x + item->size.x / 2, pos.y, 0));

			r32 padding = 0;  _zt_guiDefaultThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, &padding);
			
			ztVec2 pos_txt_p(pos.x, (pos.y + (item->size.y / 2)) + (4 / ppu));
			ztVec2 pos_txt_m(pos.x, (pos.y - (item->size.y / 2)) - (8 / ppu));

			zt_drawListAddText2D(draw_list, ztFontDefault, "+", pos_txt_p, ztAlign_Top, ztAnchor_Top);
			zt_drawListAddText2D(draw_list, ztFontDefault, "-", pos_txt_m, ztAlign_Bottom, ztAnchor_Bottom);

		} break;

		// ------------------------------------------------------------------------------------------------

		default: return true; // return false to use the default (this is the default though)
	} 

	return true;
}

// ------------------------------------------------------------------------------------------------

ztGuiManager *zt_guiManagerMake(ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena)
{
	ZT_PROFILE_GUI("zt_guiManagerMake");

	zt_returnValOnNull(gui_camera, nullptr);

	if (zt_gui == nullptr) {
		zt_guiInitGlobalMemory(arena);
	}

	{
		char size[128];
		zt_strBytesToString(size, zt_sizeof(size), zt_sizeof(ztGuiManager));
		zt_logVerbose("GuiManager allocated size: %s", size);
	}

	ztGuiManager *gm = zt_mallocStructArena(ztGuiManager, arena);
	if (!gm) {
		return nullptr;
	}

	zt_memSet(gm, zt_sizeof(ztGuiManager), 0);

	gm->id              = zt_gui->gui_managers_count;
	gm->arena           = arena;
	gm->gui_camera      = gui_camera;
	gm->gui_camera_w    = gui_camera->width;
	gm->gui_camera_h    = gui_camera->height;
	gm->item_has_mouse  = nullptr;
	gm->focus_item      = nullptr;
	gm->tooltip_item    = nullptr;
	gm->item_cache_used = 0;

	if (theme_default) {
		gm->default_theme = *theme_default;
	}
	else {
#if defined(ZT_WINDOWS)
		gm->internal_flags |= ztGuiManagerInternalFlags_OwnsTheme;

		zt_memSet(&gm->default_theme, zt_sizeof(ztGuiTheme), 0);

		// ----------------------------------------------------------------

		gm->default_theme.theme_data     = nullptr;
		gm->default_theme.flags          = 0;
		gm->default_theme.get_rvalue     = _zt_guiDefaultThemeGetRValue_FunctionID;
		gm->default_theme.get_ivalue     = _zt_guiDefaultThemeGetIValue_FunctionID;
		gm->default_theme.render_item    = _zt_guiDefaultThemeRenderItem_FunctionID;
		gm->default_theme.update_item    = _zt_guiDefaultThemeUpdateItem_FunctionID;
		gm->default_theme.update_subitem = _zt_guiDefaultThemeUpdateSubitem_FunctionID;
		gm->default_theme.size_item      = _zt_guiDefaultThemeSizeItem_FunctionID;
		gm->default_theme.pass_begin     = ztInvalidID;
		gm->default_theme.pass_end       = ztInvalidID;

		// ----------------------------------------------------------------

#endif
	}

	if (zt_gui->gui_managers_count++ == 0) {
		zt_gui->gui_manager_active = gm;
		zt_gui->gui_manager_first = gm;
	}
	else {
		zt_singleLinkAddToEnd(zt_gui->gui_manager_first, gm);
	}

	return gm;
}

// ------------------------------------------------------------------------------------------------

r32 zt_guiThemeGetRValue(ztGuiTheme *theme, ztGuiThemeValue_Enum value)
{
	ZT_PROFILE_GUI("zt_guiThemeGetRValue");

	zt_returnValOnNull(theme, 0);

	r32 result = 0;
	if (theme->get_rvalue == ztInvalidID || !((ztGuiThemeGetRValue_Func*)zt_functionPointer(theme->get_rvalue))(theme, value, &result)) {
		_zt_guiDefaultThemeGetRValue(theme, value, &result);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

i32 zt_guiThemeGetIValue(ztGuiTheme *theme, ztGuiThemeValue_Enum value)
{
	ZT_PROFILE_GUI("zt_guiThemeGetIValue");

	zt_returnValOnNull(theme, 0);

	i32 result = 0;
	if (theme->get_ivalue == ztInvalidID || !((ztGuiThemeGetIValue_Func*)zt_functionPointer(theme->get_ivalue))(theme, value, &result)) {
		_zt_guiDefaultThemeGetIValue(theme, value, &result);
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_guiThemeUpdateItem(ztGuiTheme *theme, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiThemeUpdateItem");

	zt_returnOnNull(theme);
	zt_returnOnNull(item);
	zt_returnOnNull(item);

	if (theme->update_item == ztInvalidID || !((ztGuiThemeUpdateItem_Func*)zt_functionPointer(theme->update_item))(theme, item)) {
		_zt_guiDefaultThemeUpdateItem(theme, item);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiThemeUpdateSubitem(ztGuiTheme *theme, ztGuiItem *item, ztGuiItem * subitem, void *data)
{
	ZT_PROFILE_GUI("zt_guiThemeUpdateSubitem");

	zt_returnOnNull(theme);
	zt_returnOnNull(item);
	zt_returnOnNull(subitem);

	if (theme->update_subitem == ztInvalidID || !((ztGuiThemeUpdateSubitem_Func*)zt_functionPointer(theme->update_subitem))(theme, item, subitem, data)) {
		_zt_guiDefaultThemeUpdateSubitem(theme, item, subitem, data);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiThemeSizeItem(ztGuiTheme *theme, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiThemeSizeItem");

	zt_returnOnNull(theme);
	zt_returnOnNull(item);

	if (theme->size_item == ztInvalidID || !((ztGuiThemeSizeItem_Func*)zt_functionPointer(theme->size_item))(theme, item)) {
		_zt_guiDefaultThemeSizeItem(theme, item);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiThemeRender(ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos)
{
	ZT_PROFILE_GUI("zt_guiThemeRender");

	zt_returnOnNull(theme);
	zt_returnOnNull(draw_list);
	zt_returnOnNull(item);

	if (theme->render_item == ztInvalidID || !((ztGuiThemeRenderItem_Func*)zt_functionPointer(theme->render_item))(theme, draw_list, item, pos)) {
		_zt_guiDefaultThemeRenderItem(theme, draw_list, item, pos);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiItemFree(ztGuiManager *gm, ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiItemFree");

	if (item->functions.cleanup != ztInvalidID) {
		((zt_guiItemCleanup_Func*)zt_functionPointer(item->functions.cleanup))(item, item->functions.user_data);
	}

	if (item == gm->item_has_mouse) {
		gm->item_has_mouse = nullptr;
	}
	if (item == gm->tooltip_item) {
		gm->tooltip_item = nullptr;
	}

	// remove from parent list
	ztGuiItem *child = item->parent ? item->parent->first_child : gm->first_child;
	while (child) {
		if (child == item) {
			if (child->sib_prev) {
				child->sib_prev->sib_next = child->sib_next;
			}
			if (child->sib_next) {
				child->sib_next->sib_prev = child->sib_prev;
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

	gm->item_cache_flags[item->id] = 0;
	gm->item_cache_used -= 1;

	zt_memSet(item, zt_sizeof(ztGuiItem), 0);

#	if defined(ZT_DEBUG)
	zt_fize(gm->item_cache) {
		if (gm->item_cache_flags[i] != 0 && gm->item_cache[i].functions.update == 0) {
			zt_assert(false);
		}
	}
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerFree(ztGuiManager *gm)
{
	ZT_PROFILE_GUI("zt_guiManagerFree");

	if (gm == nullptr) {
		return;
	}

	zt_assertReturnOnFail(gm != zt_gui->gui_manager_active || zt_gui->gui_managers_count == 1);

	{
		ztGuiManager *gm_link = zt_gui->gui_manager_first;
		ztGuiManager *gm_prev = nullptr;
		while (gm_link) {
			if (gm_link == gm) {
				if (gm_prev == nullptr) {
					zt_gui->gui_manager_first = gm_link->next;
				}
				else {
					zt_gui->gui_manager_first = gm_prev;
					gm_prev->next = gm->next;
				}
				break;
			}
			gm_prev = gm_link;
			gm_link = gm_link->next;
		}
	}

	zt_fiz(zt_elementsOf(gm->item_cache)) {
		if (gm->item_cache_flags[i] != 0) {
			_zt_guiItemFree(gm, &gm->item_cache[i]);
		}
	}

	if (zt_bitIsSet(gm->internal_flags, ztGuiManagerInternalFlags_OwnsTheme)) {
//		zt_fontFree(gm->default_theme.font);
//		zt_textureFree(gm->default_theme.sprite_combobox_background.normal.sns.tex);
	}

	zt_freeArena(gm, gm->arena);

	zt_gui->gui_managers_count--;
	if (zt_gui->gui_managers_count > 0) {
		return;
	}

	_zt_guiDebugConsoleRemoveLoggingCallbacks();

	auto* command = zt_gui->console_commands;
	while (command) {
		auto* next = command->next;
		zt_freeArena(command, zt_gui->arena);
		command = next;
	}
//	zt_freeArena(zt_gui, zt_gui->arena);
	zt_gui = nullptr;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiItemReposition(ztGuiManager *gm, ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiItemReposition");

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

ztInternal void _zt_guiManagerUpdatePre(ztGuiManager *gm, r32 dt)
{
	ZT_PROFILE_GUI("_zt_guiManagerUpdatePre");

	int item_count = gm->item_cache_used;
	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] != 0) {
			if (gm->item_cache[i].prev_state_flags != gm->item_cache[i].state_flags) {
				zt_fkz(32) {
					if (zt_bitIsSet(gm->item_cache[i].prev_state_flags, zt_bit(k)) != zt_bitIsSet(gm->item_cache[i].state_flags, zt_bit(k))) {
						gm->item_cache[i].state_length[k] = 0;
					}
				}
			}
			zt_fkz(32) {
				gm->item_cache[i].state_length[k] += dt;
			}

			if (gm->item_cache[i].prev_size.x != gm->item_cache[i].size.x || gm->item_cache[i].prev_size.y != gm->item_cache[i].size.y) {
				gm->item_cache[i].state_flags |= zt_bit(ztGuiItemStates_Dirty);
				gm->item_cache[i].state_flags |= zt_bit(ztGuiItemStates_Resized);
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
			else {
				zt_bitRemove(gm->item_cache[i].state_flags, zt_bit(ztGuiItemStates_Resized));
			}
			if (gm->item_cache[i].functions.update != ztInvalidID) {
				((zt_guiItemUpdate_Func*)zt_functionPointer(gm->item_cache[i].functions.update))(&gm->item_cache[i], dt, gm->item_cache[i].functions.user_data);
			}
			if (--item_count == 0) {
				break;
			}
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

ztInternal void _zt_guiManagerUpdatePost(ztGuiManager *gm, r32 dt)
{
	ZT_PROFILE_GUI("_zt_guiManagerUpdatePost");

	int item_count = gm->item_cache_used;
	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] != 0) {
			zt_bitRemove(gm->item_cache_flags[i], ztGuiManagerItemCacheFlags_MouseOver);
			if (--item_count == 0) {
				break;
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

bool zt_guiManagerHandleInput(ztGuiManager *gm, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[16], ztInputMouse *input_mouse)
{
	ZT_PROFILE_GUI("zt_guiManagerHandleInput");

	zt_returnValOnNull(gm, false);
	zt_returnValOnNull(input_keys, false);
	zt_returnValOnNull(input_mouse, false);

	gm->key_state_alt   = input_keys[ztInputKeys_Menu].pressed();
	gm->key_state_ctrl  = input_keys[ztInputKeys_Control].pressed();
	gm->key_state_shift = input_keys[ztInputKeys_Shift].pressed();


	bool mouse_captured = gm->item_has_mouse != nullptr;
	if (mouse_captured) {
		ztGuiItem *mc_item = gm->item_has_mouse;
		if (mc_item && !zt_bitIsSet(mc_item->state_flags, zt_bit(ztGuiItemStates_Visible))) {
			gm->item_has_mouse = nullptr;
		}
	}

	if (gm->focus_item != nullptr && zt_guiItemIsShowing(gm->focus_item)) {
		bool key_handled = false;
		ztGuiItem *f_item = gm->focus_item;
		if (!key_handled && f_item && input_key_strokes[0] != ztInputKeys_Invalid) {
			if (f_item->functions.input_key != ztInvalidID) {
				if (((zt_guiItemInputKey_Func*)zt_functionPointer(f_item->functions.input_key))(gm->focus_item, input_keys, input_key_strokes, f_item->functions.user_data)) {
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

	ztGuiItem *top_level_mouse_item = nullptr;
	if (gm->item_has_mouse != nullptr) {
		top_level_mouse_item = zt_guiItemGetTopLevelParent(gm->item_has_mouse);
	}

	ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);

	while (child) {
		bool process_input = true;
		if (top_level_mouse_item != nullptr && top_level_mouse_item != child) {
			process_input = false;
		}
		if (!zt_bitIsSet(child->behavior_flags, ztGuiItemBehaviorFlags_WantsInput) && !zt_bitIsSet(child->behavior_flags, ztGuiItemBehaviorFlags_WantsFocus)) {
			process_input = false;
		}
		if (process_input) {

			struct local
			{
				static bool mouseIntersecting(ztGuiItem *item, const ztVec2& mpos)
				{
					ztVec2 pos = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
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
					if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled))) {
						zt_assert(item != gm->item_has_mouse);
						return false;
					}

					if (gm->item_has_mouse != nullptr && gm->item_has_mouse != item) {
						ztGuiItem *mi = gm->item_has_mouse;
						if (mi) {
							bool result = processMouseFocusEvent(gm, mi, input_mouse, mpos);
							if (gm->item_has_mouse != nullptr && !zt_guiItemIsShowing(gm->item_has_mouse)) {
								gm->item_has_mouse = nullptr;
							}
							return result;
						}
					}

					bool mouse_intersecting = mouseIntersecting(item, mpos);
					if ((mouse_intersecting && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsInput)) || gm->item_has_mouse == item) {
						gm->mouse_over_gui = true;
					}

					// verify that the mouse is within this item's boundary
					if (gm->item_has_mouse != item) {
						if (mouse_intersecting || zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_HasOutlyingChildren)) {
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
					if (gm->focus_item != item) {
						if (zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsFocus)) {
							zt_guiItemSetFocus(item);
							recv_focus = true;
						}
					}
					if (item->parent == nullptr && mouse_intersecting) {
						recv_focus = true; // this prevents windows behind this top level window from receiving events
					}
					if (gm->tooltip_item == item && !mouse_intersecting) {
						gm->tooltip_item = nullptr;
					}

					if(mouse_intersecting && gm->item_has_mouse == nullptr && (input_mouse->leftJustPressed() || input_mouse->rightJustPressed() || input_mouse->middleJustPressed()) && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsFocus)) {
						gm->item_has_mouse = item;
						recv_focus = true;
					}

					if (mouse_intersecting || gm->item_has_mouse == item) {
						if (mouse_intersecting) {
							gm->item_cache_flags[item->id] |= ztGuiManagerItemCacheFlags_MouseOver;
						}
						if (item->functions.input_mouse != ztInvalidID && ((zt_guiItemInputMouse_Func*)zt_functionPointer(item->functions.input_mouse))(item, input_mouse, item->functions.user_data)) {
							recv_focus = true;
						}
					}

					if (gm->item_has_mouse == item && (input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased())) {
						gm->item_has_mouse = nullptr;
					}
					return recv_focus;
				}

				// movements and scroll wheel
				static bool mouseProcessNonFocusEvent(ztGuiManager *gm, ztGuiItem *item, ztInputMouse *input_mouse, const ztVec2& mpos)
				{
					if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible))) {
						zt_assert(item != gm->item_has_mouse);
						return false;
					}

					bool mouse_intersecting = mouseIntersecting(item, mpos);
					if (mouse_intersecting && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsInput)) {
						gm->mouse_over_gui = true;
					}

					// verify that the mouse is within this item's boundary
					if (gm->item_has_mouse != item) {
						if (mouse_intersecting || zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_HasOutlyingChildren)) {
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
					if (gm->tooltip_item == item && !mouse_intersecting) {
						gm->tooltip_item = nullptr;
					}
					if (mouse_intersecting || gm->item_has_mouse == item) {
						if (mouse_intersecting) {
							gm->item_cache_flags[item->id] |= ztGuiManagerItemCacheFlags_MouseOver;
						}
						if (item->functions.input_mouse != ztInvalidID && ((zt_guiItemInputMouse_Func*)zt_functionPointer(item->functions.input_mouse))(item, input_mouse, item->functions.user_data)) {
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
					if (zt_bitIsSet(child->behavior_flags, ztGuiItemBehaviorFlags_BringToFront)) {
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
			gm->focus_item = nullptr;
		}
		else result = true;
	}

	return result;
}

// ------------------------------------------------------------------------------------------------

void zt_drawListAddGuiThemeSprite(ztDrawList *draw_list, ztGuiThemeSprite *theme_sprite, const ztVec2& pos, const ztVec2& size)
{
	ZT_PROFILE_GUI("zt_drawListAddGuiThemeSprite");

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
	ZT_PROFILE_GUI("zt_drawListAddGuiThemeButtonSprite");

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
	ZT_PROFILE_GUI("zt_guiThemeSpriteGetSize");

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
	ZT_PROFILE_GUI("zt_guiThemeButtonSpriteGetSize");

	ztVec2 normal = zt_guiThemeSpriteGetSize(&sprite->normal);
	ztVec2 highlight = zt_guiThemeSpriteGetSize(&sprite->highlight);
	ztVec2 pressed   = zt_guiThemeSpriteGetSize(&sprite->pressed);

	return ztVec2(zt_max(normal.x, zt_max(highlight.x, pressed.x)), zt_max(normal.y, zt_max(highlight.y, pressed.y)));
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerRender(ztGuiManager *gm, ztDrawList *draw_list, r32 dt)
{
	ZT_PROFILE_GUI("zt_guiManagerRender");

	zt_returnOnNull(draw_list);
	zt_returnOnNull(gm);

	_zt_guiManagerUpdatePre(gm, dt);

//#define _zt_guiManagerRenderClipAreas

	struct local
	{
		static void clipTo(ztDrawList *draw_list, ztVec2 pos, ztVec2 size)
		{
			r32 ppu = zt_pixelsPerUnit();
			size.y += 1 / ppu;
			zt_alignToPixel(&pos, ppu);
			zt_alignToPixel(&size, ppu);
			zt_drawListPushClipRegion(draw_list, pos, size);
		}

		static void renderItem(ztGuiManager *gm, ztGuiItem *item, ztDrawList *draw_list, const ztVec2& offset)
		{
			if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible)) || item->size.x <= 0 || item->size.y <= 0) {
				return;
			}

			ztVec2 pos = item->pos + offset;

			ztGuiTheme *theme = item->theme == nullptr ? &gm->default_theme : item->theme;

			if(item->parent == nullptr && zt_bitIsSet(theme->flags, ztGuiThemeFlags_SeparatePasses) && theme->pass_begin != ztInvalidID) {
				((ztGuiThemeRenderPassBegin_Func*)zt_functionPointer(theme->pass_begin))(theme, item, draw_list);
			}

			bool clip = zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_ClipContents);
			if (clip) {
				if (item->clip_area != ztVec4::zero) {
#					if !defined(_zt_guiManagerRenderClipAreas)
					clipTo(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
#					endif
				}
				else {
#					if !defined(_zt_guiManagerRenderClipAreas)
					clipTo(draw_list, pos, item->size);
#					endif
				}
			}

			if (item->functions.render != ztInvalidID) {
				((zt_guiItemRender_Func*)zt_functionPointer(item->functions.render))(item, draw_list, theme, offset, !zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled)), item->functions.user_data);
			}

			zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Dirty));

#			if defined(ZT_DEBUG)
				if (item->debug_highlight != ztVec4::zero) {
					zt_drawListPushColor(draw_list, item->debug_highlight);
					zt_drawListAddEmptyRect(draw_list, pos, item->size);
					zt_drawListPopColor(draw_list);
				}
#			endif
			if (!clip && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_ClipChildren) ) {
				clip = true;
				if (item->clip_area != ztVec4::zero) {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, ztVec4(1, 1, 0, 1));
						zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
						zt_drawListPopColor(draw_list);
#					else
					clipTo(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
#					endif
				}
				else {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, ztVec4(0, 1, 1, 1));
						zt_drawListAddEmptyRect(draw_list, pos, item->size);
						zt_drawListPopColor(draw_list);
#					else
						zt_drawListPushClipRegion(draw_list, pos, item->size);
#					endif
				}
			}
			else if (clip && !zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_ClipChildren)) {
#				if defined(_zt_guiManagerRenderClipAreas)
					zt_drawListPushColor(draw_list, ztVec4(1, 0, 0, .5f));
					zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
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
					zt_drawListPushColor(draw_list, ztVec4(1, 0, 0, .5f));
					if (item->clip_area != ztVec4::zero) {
						zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
					}
					else {
						zt_drawListPushClipRegion(draw_list, pos, item->size);
					}
					zt_drawListPopColor(draw_list);
#				else
					zt_drawListPopClipRegion(draw_list);
#				endif
			}

			if(item->parent == nullptr && zt_bitIsSet(theme->flags, ztGuiThemeFlags_SeparatePasses) && theme->pass_end != ztInvalidID) {
				((ztGuiThemeRenderPassEnd_Func*)zt_functionPointer(theme->pass_end))(theme, item, draw_list);
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

	_zt_guiManagerUpdatePost(gm, dt);

#	if defined(_zt_guiManagerRenderClipAreas)
#		undef _zt_guiManagerRenderClipAreas
#	endif
}

// ------------------------------------------------------------------------------------------------

void zt_guiSetActiveManager(ztGuiManager *gm)
{
	zt_returnOnNull(gm);
	zt_gui->gui_manager_active = gm;
}

// ------------------------------------------------------------------------------------------------

void zt_guiManagerSetKeyboardFocus(ztGuiManager *gm, bool keyboard_focus)
{
	zt_returnOnNull(gm);
	gm->keyboard_focus = keyboard_focus;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiManagerHasKeyboardFocus(ztGuiManager *gm)
{
	zt_returnValOnNull(gm, false);
	return gm->keyboard_focus;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiManagerMouseOverGui(ztGuiManager *gm)
{
	zt_returnValOnNull(gm, false);
	return gm->mouse_over_gui;
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_guiProcessDrag(ztGuiItem::ztDragState *drag_state, ztGuiManager *gm, ztVec2* pos, ztInputMouse *input_mouse)
{
	ZT_PROFILE_GUI("_zt_guiProcessDrag");

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

ztInternal ztGuiItem *_zt_guiMakeItemBase(ztGuiItem *parent, ztGuiItemType_Enum type, i32 item_flags, i32 draw_list_size = 0)
{
	ZT_PROFILE_GUI("_zt_guiMakeItemBase");

	ztGuiItem *item = nullptr;
	i32 item_id = ztInvalidID;

	ztGuiManager *gm = parent == nullptr ? zt_gui->gui_manager_active : parent->gm;

	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] == 0) {
			gm->item_cache_flags[i] |= ztGuiManagerItemCacheFlags_Used;
			item_id = i;
			item = &gm->item_cache[i];
			break;
		}
	}

	zt_returnValOnNull(item, nullptr);

	zt_memSet(item, zt_sizeof(ztGuiItem), 0);

	item->id             = item_id;
	item->type           = type;
	item->behavior_flags = item_flags;
	item->state_flags    = zt_bit(ztGuiItemStates_Visible) | zt_bit(ztGuiItemStates_Dirty) | zt_bit(ztGuiItemStates_Resized);
	item->color          = ztVec4::one;
	item->gm             = gm;

	item->functions.update      = ztInvalidID;
	item->functions.render      = ztInvalidID;
	item->functions.cleanup     = ztInvalidID;
	item->functions.input_key   = ztInvalidID;
	item->functions.input_mouse = ztInvalidID;
	item->functions.best_size   = ztInvalidID;
	
	if (draw_list_size != 0) {
		item->draw_list = zt_mallocStruct(ztDrawList);
		zt_drawListMake(item->draw_list, draw_list_size, 0, gm->arena);
	}

	zt_debugOnly(item->debug_highlight = ztVec4::zero);

	if (parent != nullptr) {
		item->parent = parent;

		ztGuiItem* last_child = parent->first_child;
		if (!last_child) {
			parent->first_child = item;
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

	return item;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowUpdate, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiWindowUpdate))
{
	ZT_PROFILE_GUI("_zt_guiWindowUpdate");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized))) {
		ztGuiTheme *theme = zt_guiItemGetTheme(item);
		
		zt_guiThemeUpdateItem(theme, item);

		if (item->window.button_collapse) {
			zt_guiThemeUpdateSubitem(theme, item, item->window.button_collapse);
			ztVec2 offset_collapse(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCollapseButtonOffsetX), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCollapseButtonOffsetY));
			zt_guiItemSetPosition(item->window.button_collapse, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCollapseButtonAlign), zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCollapseButtonAnchor), offset_collapse);
		}
		if (item->window.button_close) {
			zt_guiThemeUpdateSubitem(theme, item, item->window.button_close);
			ztVec2 offset_close(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCloseButtonOffsetX), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCloseButtonOffsetY));
			zt_guiItemSetPosition(item->window.button_close, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCloseButtonAlign), zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCloseButtonAnchor), offset_close);
		}

		r32 title_height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight);

		if (item->window.menubar) {
			item->window.menubar->size.x = item->size.x;
			zt_guiItemSetPosition(item->window.menubar, ztAlign_Top, ztAnchor_Top, ztVec2(0, -title_height));
			title_height += item->window.menubar->size.y;
		}

		if (item->window.content != item) {
			ztVec2 pos = ztVec2::zero;
			ztVec2 size = item->size;

			size.x -= zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingX) * 2;
			size.y -= zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingY) * 2 + title_height;

			pos.y -= title_height / 2;

			item->window.content->pos = pos;
			item->window.content->size = size;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiWindowRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowOnButtonClose, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiWindowOnButtonClose))
{
	ZT_PROFILE_GUI("_zt_guiWindowOnButtonClose");

	ztGuiItem *window = zt_guiItemGetTopLevelParent(button);

	if (zt_bitIsSet(window->behavior_flags, ztGuiWindowBehaviorFlags_CloseHides)) {
		zt_guiItemHide(window);
	}
	else {
		zt_guiItemFree(window);
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowOnButtonToggle, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiWindowOnButtonToggle))
{
	ZT_PROFILE_GUI("_zt_guiWindowOnButtonToggle");

	ztGuiItem  *window = zt_guiItemGetTopLevelParent(button);
	ztGuiTheme *theme  = zt_guiItemGetTheme(window);

	if (zt_bitIsSet(window->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
		zt_bitRemove(window->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed));

		r32 y_diff = window->window.size[1] - window->size.y;
		window->pos.y -= y_diff / 2;

		window->size.x = window->window.size[0];
		window->size.y = window->window.size[1];

		zt_guiItemShow(window->window.content);
	}
	else {
		window->state_flags |= zt_bit(ztGuiWindowInternalStates_Collapsed);
		zt_guiItemHide(window->window.content);
		window->window.size[0] = window->size.x;
		window->window.size[1] = window->size.y;
		window->size.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight) + zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingY) * 2;

		r32 y_diff = window->window.size[1] - window->size.y;
		window->pos.y += y_diff / 2;
	}

	window->state_flags |= zt_bit(ztGuiItemStates_Resized);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiWindowInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiWindowInputMouse");

	ztGuiManager *gm = item->gm;

	if (!item->window.drag_state.dragging) {
		if (input_mouse->leftJustPressed()) {
			if (zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_AllowResize)) {
				ztGuiTheme *theme = zt_guiItemGetTheme(item);
				ztVec2 pos = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
				ztVec2 mpos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);

				r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding);
				r32 resize_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCornerResizeW);
				r32 resize_h = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCornerResizeH);
				ztVec2 resize_pos(pos.x + ((item->size.x / 2) - (resize_w / 2 + padding)), pos.y - ((item->size.y / 2) - (resize_w / 2.f + padding)));
				ztVec2 resize_size(resize_w + padding, resize_h + padding);
				if (zt_collisionPointInRect(mpos, resize_pos, resize_size)) {
					item->state_flags |= zt_bit(ztGuiWindowInternalStates_Resizing);
					item->window.resize[0] = item->window.resize[1] = 0;
					item->window.pos[0] = item->pos.x;
					item->window.pos[1] = item->pos.y;
					item->window.size[0] = item->size.x;
					item->window.size[1] = item->size.y;
				}
			}
		}
		else {
			zt_bitRemove(item->state_flags, zt_bit(ztGuiWindowInternalStates_Resizing));
		}
	}
	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Resizing))) {
		bool result = _zt_guiProcessDrag(&item->window.drag_state, gm, (ztVec2*)item->window.resize, input_mouse);
		item->pos.x = item->window.pos[0] + item->window.resize[0] / 2.f;
		item->pos.y = item->window.pos[1] + item->window.resize[1] / 2.f;
		item->size.x = item->window.size[0] + item->window.resize[0];
		item->size.y = item->window.size[1] - item->window.resize[1];

		zt_guiSizerRecalcImmediately(item);
		return result;
	}
	else if (zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_AllowDrag)) {
		if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
			ztGuiTheme *theme = zt_guiItemGetTheme(item);
			r32 height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight);
			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingY);

			ztVec2 mpos = zt_guiItemPositionScreenToLocal(item, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));
			if (mpos.y > (item->size.y / 2) - (height + padding)) {
				return _zt_guiProcessDrag(&item->window.drag_state, gm, &item->pos, input_mouse);
			}
		}
		else {
			return _zt_guiProcessDrag(&item->window.drag_state, gm, &item->pos, input_mouse);
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeWindow(const char *title, i32 behavior_flags)
{
	ZT_PROFILE_GUI("zt_guiMakeWindow");

	ztGuiItem *item = _zt_guiMakeItemBase(nullptr, ztGuiItemType_Window, behavior_flags | ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_BringToFront /* | ztGuiItemBehaviorFlags_ClipChildren*/);
	if (!item) return nullptr;

	if (zt_bitIsSet(behavior_flags, ztGuiWindowBehaviorFlags_ShowTitle)) {
		ztGuiItem *scroll_container = nullptr;
		if (zt_bitIsSet(behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollHorz) || zt_bitIsSet(behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollVert)) {
			i32 sflags = (zt_bitIsSet(behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollHorz) ? ztGuiItemOrient_Horz : 0) |
						 (zt_bitIsSet(behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollVert) ? ztGuiItemOrient_Vert : 0);

			if (!zt_bitIsSet(behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollHorz)) sflags |= ztGuiScrollContainerBehaviorFlags_StretchHorz;
			if (!zt_bitIsSet(behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollVert)) sflags |= ztGuiScrollContainerBehaviorFlags_StretchVert;

			scroll_container = zt_guiMakeScrollContainer(item, sflags);
		}

		item->window.content = _zt_guiMakeItemBase(item, ztGuiItemType_Panel, 0);
		zt_debugOnly(zt_guiItemSetName(item->window.content, "Window Content Panel"));

		ztGuiTheme *theme = zt_guiItemGetTheme(item);

		if (scroll_container != nullptr) {
			zt_guiScrollContainerSetItem(scroll_container, item->window.content);
			item->window.content = scroll_container;
		}

		if (zt_bitIsSet(behavior_flags, ztGuiWindowBehaviorFlags_AllowClose)) {
			ztGuiItem *button_close = zt_guiMakeButton(item, nullptr, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCloseButtonBehaviorFlags));
			item->window.button_close = button_close;
			zt_guiItemSetName(button_close, "Close");
			zt_guiButtonSetCallback(button_close, _zt_guiWindowOnButtonClose_FunctionID);
			zt_guiThemeUpdateSubitem(theme, item, button_close);
		}
		if (zt_bitIsSet(behavior_flags, ztGuiWindowBehaviorFlags_AllowCollapse)) {
			ztGuiItem *button_collapse = zt_guiMakeButton(item, nullptr, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCollapseButtonBehaviorFlags));
			item->window.button_collapse = button_collapse;
			zt_guiItemSetName(item->window.button_collapse, "Collapse");
			zt_guiThemeUpdateSubitem(theme, item, button_collapse);
			zt_guiButtonSetCallback(item->window.button_collapse, _zt_guiWindowOnButtonToggle_FunctionID);
		}
	}
	else {
		item->window.content = item;
	}

	item->functions.render = _zt_guiWindowRender_FunctionID;

	zt_guiItemSetSize(item, ztVec2(7, 5));
	zt_guiItemSetLabel(item, title);

	item->functions.input_mouse = _zt_guiWindowInputMouse_FunctionID;
	item->functions.update = _zt_guiWindowUpdate_FunctionID;

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeScrollWindow(const char *title, i32 scroll_dir, i32 behavior_flags)
{
	ZT_PROFILE_GUI("zt_guiMakeScrollWindow");

	i32 scroll_flags = (zt_bitIsSet(scroll_dir, ztGuiItemOrient_Horz) ? ztGuiWindowInternalBehaviorFlags_ScrollHorz : 0) |
					   (zt_bitIsSet(scroll_dir, ztGuiItemOrient_Vert) ? ztGuiWindowInternalBehaviorFlags_ScrollVert : 0);

	return zt_guiMakeWindow(title, scroll_flags | behavior_flags);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiWindowGetContentParent(ztGuiItem *window)
{
	ZT_PROFILE_GUI("zt_guiWindowGetContentParent");

	zt_assertReturnValOnFail(window->type == ztGuiItemType_Window, nullptr);

	if (zt_bitIsSet(window->behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollHorz) || zt_bitIsSet(window->behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollVert)) {
		return window->window.content->scrolled_container.contained_item;
	}

	return window->window.content;
}

// ------------------------------------------------------------------------------------------------

void zt_guiWindowSetMenuBar(ztGuiItem *window, ztGuiItem *menubar)
{
	zt_returnOnNull(window);
	zt_assertReturnOnFail(window->type == ztGuiItemType_Window);
	zt_assertReturnOnFail(menubar == nullptr || menubar->type == ztGuiItemType_MenuBar);

	window->window.menubar = menubar;
	window->state_flags |= zt_bit(ztGuiItemStates_Dirty);

	if (menubar) {
		zt_guiItemReparent(menubar, window);
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiPanelCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiPanelCleanup))
{
	if (item->panel.user_data) {
		zt_freeArena(item->panel.user_data, item->panel.arena);
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiPanelRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiPanelRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakePanel(ztGuiItem *parent, i32 behavior_flags, void *user_data, ztMemoryArena *arena)
{
	ZT_PROFILE_GUI("zt_guiMakePanel");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Panel, behavior_flags);
	zt_returnValOnNull(item, nullptr);

	item->panel.user_data = user_data;
	item->panel.arena = arena;
	if (user_data) {
		item->functions.cleanup = _zt_guiPanelCleanup_FunctionID;
	}

	item->functions.render = _zt_guiPanelRender_FunctionID;

	return item;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiCollapsingPanelUpdate))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelUpdate");

	// TODO: should use ztGuiItemState_Dirty here
	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Recalc))) {
		zt_bitRemove(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Recalc));

		ztGuiTheme *theme = zt_guiItemGetTheme(item);
		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding);
		zt_guiItemSetPosition(item->collapsing_panel.button, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(0, -padding));

		ztGuiItem *content_panel = item->collapsing_panel.content_panel;

		r32 panel_height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelHeight);
		if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
			item->size.y = panel_height;
			zt_guiItemHide(item->collapsing_panel.content_panel);
		}
		else {
			ztVec2 size = zt_guiSizerGetMinSize(item->collapsing_panel.content_panel);
			content_panel->size.x = item->size.x;
			content_panel->size.y = size.y;
			item->size.x = zt_max(item->size.x, size.x);
			item->size.y = panel_height + size.y;

			content_panel->pos.x = 0;
			content_panel->pos.y = -panel_height / 2.f;
			zt_guiItemShow(item->collapsing_panel.content_panel);
		}

		zt_guiSizerRecalcImmediately(zt_guiItemGetTopLevelParent(item));
	}
	else if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized))) {
		item->collapsing_panel.content_panel->size.x = item->size.x;
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiCollapsingPanelRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelOnToggle, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiCollapsingPanelOnToggle))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelOnToggle");

	ztGuiItem *item = button->parent;
	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
		zt_bitRemove(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed));
	}
	else {
		item->state_flags |= zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed);
	}

	item->state_flags |= zt_bit(ztGuiCollapsingPanelInternalStates_Recalc);
	zt_guiThemeUpdateSubitem(theme, item, button);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiCollapsingPanelBestSize))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeCollapsingPanel(ztGuiItem *parent, const char *label)
{
	ZT_PROFILE_GUI("zt_guiMakeCollapsingPanel");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_CollapsingPanel, 0, (zt_strLen(label) * 2) + 19);
	zt_returnValOnNull(item, nullptr);

	item->state_flags |= zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztGuiItem *button = zt_guiMakeButton(item, nullptr, ztGuiButtonBehaviorFlags_NoBackground | ztGuiButtonBehaviorFlags_OnPressDip);
	item->collapsing_panel.button = button;

	zt_guiItemSetName(button, "Collapse Button");
	zt_guiButtonSetCallback(button, _zt_guiCollapsingPanelOnToggle_FunctionID);
	zt_guiThemeUpdateSubitem(theme, item, button);

	ztGuiItem *content_panel = zt_guiMakePanel(item, ztGuiPanelBehaviorFlags_DrawBackground);
	item->collapsing_panel.content_panel = content_panel;
	zt_guiItemSetName(content_panel, "content-panel");

	zt_guiItemHide(content_panel);

	item->state_flags |= zt_bit(ztGuiCollapsingPanelInternalStates_Recalc) | zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed);

	zt_guiItemSetLabel(item, label);

	item->functions.update    = _zt_guiCollapsingPanelUpdate_FunctionID;
	item->functions.render    = _zt_guiCollapsingPanelRender_FunctionID;
	item->functions.best_size = _zt_guiCollapsingPanelBestSize_FunctionID;

	_zt_guiCollapsingPanelBestSize(item, nullptr, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiCollapsingPanelGetContentParent(ztGuiItem *panel)
{
	zt_assertReturnValOnFail(panel->type == ztGuiItemType_CollapsingPanel, nullptr);
	return panel->collapsing_panel.content_panel;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiStaticTextRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiStaticTextRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiStaticTextBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiStaticTextBestSize))
{
	ZT_PROFILE_GUI("_zt_guiStaticTextBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeStaticText(ztGuiItem *parent, const char *label, i32 behavior_flags, int max_chars)
{
	ZT_PROFILE_GUI("zt_guiMakeStaticText");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_StaticText, behavior_flags, zt_max(zt_strLen(label), max_chars) * 2);
	zt_returnValOnNull(item, nullptr);

	item->functions.render    = _zt_guiStaticTextRender_FunctionID;
	item->functions.best_size = _zt_guiStaticTextBestSize_FunctionID;

	zt_guiItemSetLabel(item, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	zt_guiThemeSizeItem(theme, item);

	return item;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiButtonBaseUpdate))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseUpdate");

	if (zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsToggleButton)) {
		if (item->button.live_value) {
			if (*item->button.live_value) {
				item->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
			}
			else {
				zt_bitRemove(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
			}
		}
	}
	else if (item->button.live_value && *item->button.live_value) {
		*item->button.live_value = false;
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiButtonBaseRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiButtonBaseCleanup))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseCleanup");

	if (item->button.icon) {
		zt_freeArena(item->button.icon, item->gm->arena);
	}
}
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiButtonBaseInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseInputMouse");

	if (input_mouse->leftJustReleased()) {
		if (item->gm->item_has_mouse == item && zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver)) {
			bool value = true;
			if (zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsToggleButton)) {
				value = !zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
				if (value) {
					item->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
				}
				else {
					zt_bitRemove(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
				}
			}
			if (zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio)) {
				value = true;
				item->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);

				ztGuiItem *sib = item->parent ? item->parent->first_child : nullptr;
				while (sib) {
					if (sib->type == ztGuiItemType_RadioButton && sib != item) {
						zt_bitRemove(sib->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
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
			if (item->button.on_pressed != ztInvalidID) {
				((zt_guiButtonPressed_Func*)zt_functionPointer(item->button.on_pressed))(item, item->button.on_pressed_user_data);
			}
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiButtonBaseBestSize))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItem *_zt_guiMakeButtonBase(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("_zt_guiMakeButtonBase");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Button, behavior_flags | ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus, zt_strLen(label) * 2);
	zt_returnValOnNull(item, nullptr);

	zt_guiItemSetLabel(item, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->button.live_value = live_value;
	item->button.on_pressed = ztInvalidID;
	item->button.icon       = nullptr;
	item->button.text_pos   = 0;

	item->functions.input_mouse = _zt_guiButtonBaseInputMouse_FunctionID;
	item->functions.render      = _zt_guiButtonBaseRender_FunctionID;
	item->functions.best_size   = _zt_guiButtonBaseBestSize_FunctionID;
	item->functions.cleanup     = _zt_guiButtonBaseCleanup_FunctionID;

	if (item->button.live_value) {
		if (!(zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsCheckbox) || zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio) || zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsToggleButton))) {
			*item->button.live_value = false;
		}
		else if (*item->button.live_value) {
			item->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
		}

		item->functions.update = _zt_guiButtonBaseUpdate_FunctionID;
	}

	if (zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsToggleButton)) {
		if (zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsCheckbox)) {
			item->type = ztGuiItemType_Checkbox;
		}
		else if (zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio)) {
			item->type = ztGuiItemType_RadioButton;
		}
		else {
			item->type = ztGuiItemType_ToggleButton;
		}
	}

	ztVec2 min_size;
	_zt_guiButtonBaseBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	zt_guiThemeUpdateItem(theme, item);

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeButton(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeButton");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags, live_value);
}

// ------------------------------------------------------------------------------------------------

void zt_guiButtonSetIcon(ztGuiItem *button, ztSprite *icon)
{
	ZT_PROFILE_GUI("zt_guiButtonSetIcon");

	zt_returnOnNull(button);
	zt_returnOnNull(icon);
	zt_assertReturnOnFail(button->type == ztGuiItemType_Button || button->type == ztGuiItemType_ToggleButton);

	if (button->button.icon == nullptr) {
		button->button.icon = zt_mallocStructArena(ztSprite, button->gm->arena);
	}
	*button->button.icon = *icon;

	_zt_guiButtonBaseBestSize(button, nullptr, nullptr, &button->size, zt_guiItemGetTheme(button), button->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiButtonSetTextPosition(ztGuiItem *button, i32 align_flags)
{
	zt_returnOnNull(button);
	zt_assertReturnOnFail(button->type == ztGuiItemType_Button || button->type == ztGuiItemType_ToggleButton);

	button->button.text_pos = align_flags;
}

// ------------------------------------------------------------------------------------------------

void zt_guiButtonSetCallback(ztGuiItem *button, ztFunctionID on_pressed, void *user_data)
{
	zt_returnOnNull(button);
	zt_assertReturnOnFail(button->type == ztGuiItemType_Button || button->type == ztGuiItemType_ToggleButton || button->type == ztGuiItemType_Checkbox || button->type == ztGuiItemType_RadioButton);

	button->button.on_pressed = on_pressed;
	button->button.on_pressed_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeToggleButton(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeToggleButton");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags | ztGuiButtonInternalBehaviorFlags_IsToggleButton, live_value);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiToggleButtonGetValue(ztGuiItem *button)
{
	zt_returnValOnNull(button, false);
	zt_assertReturnValOnFail(button->type == ztGuiItemType_ToggleButton, false);

	return zt_bitIsSet(button->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
}

// ------------------------------------------------------------------------------------------------

void zt_guiToggleButtonSetValue(ztGuiItem *button, bool value)
{
	zt_returnOnNull(button);
	zt_assertReturnOnFail(button->type == ztGuiItemType_ToggleButton);

	if (value) {
		button->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
	}
	else {
		zt_bitRemove(button->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeCheckbox(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeCheckbox");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags | ztGuiButtonInternalBehaviorFlags_IsToggleButton | ztGuiButtonInternalBehaviorFlags_IsCheckbox, live_value);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiCheckboxGetValue(ztGuiItem *checkbox)
{
	zt_returnValOnNull(checkbox, false);
	zt_assertReturnValOnFail(checkbox->type == ztGuiItemType_Checkbox, false);

	return zt_bitIsSet(checkbox->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
}

// ------------------------------------------------------------------------------------------------

void zt_guiCheckboxSetValue(ztGuiItem *checkbox, bool value)
{
	zt_returnOnNull(checkbox);
	zt_assertReturnOnFail(checkbox->type == ztGuiItemType_Checkbox);

	if (value) {
		checkbox->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
	}
	else {
		zt_bitRemove(checkbox->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeRadioButton(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeRadioButton");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags | ztGuiButtonInternalBehaviorFlags_IsToggleButton | ztGuiButtonInternalBehaviorFlags_IsRadio, live_value);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiRadioGetValue(ztGuiItem *radio)
{
	zt_returnValOnNull(radio, false);
	zt_assertReturnValOnFail(radio->type == ztGuiItemType_RadioButton, false);

	return zt_bitIsSet(radio->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
}

// ------------------------------------------------------------------------------------------------

void zt_guiRadioSetValue(ztGuiItem *radio, bool value)
{
	zt_returnOnNull(radio);
	zt_assertReturnOnFail(radio->type == ztGuiItemType_RadioButton);

	if (value) {
		radio->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
	}
	else {
		zt_bitRemove(radio->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
	}
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiSliderBaseCalcHandleSizeAndPos(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSliderBaseCalcHandleSizeAndPos");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	r32 value = item->slider.orient == ztGuiItemOrient_Horz ? item->slider.value : 1.f - item->slider.value;
	r32 size_item = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;

	if (item->type == ztGuiItemType_Slider) {
		item->slider.handle_size = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize);

		r32 handle_size = item->slider.handle_size;
		r32 size_value = size_item - handle_size;
		item->slider.handle_pos = (size_item / -2.f) + (size_value * value) + handle_size / 2.f;
	}
	else {
		r32 scrollbar_button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW);
		size_item -= scrollbar_button_w * 2;

		item->slider.handle_size = zt_max(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinHandleSize), size_item * item->slider.handle_pct);

		r32 handle_size = item->slider.handle_size;
		r32 size_value  = size_item - handle_size;
		r32 offset      = handle_size / 2.f;

		item->slider.handle_pos = (size_item / -2.f) + (size_value * value) + offset;
	}
}

// ------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSliderBaseUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiSliderBaseUpdate))
{
	ZT_PROFILE_GUI("_zt_guiSliderBaseUpdate");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized))) {
		_zt_guiSliderBaseCalcHandleSizeAndPos(item);
	}

	if (item->slider.live_value && !item->slider.drag_state.dragging) {
		item->slider.value = *item->slider.live_value;

		if (item->type == ztGuiItemType_Scrollbar) {
			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)) && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegHighlight))) {
				item->slider.press_time -= dt;
				if (item->slider.press_time <= 0) {
					zt_guiScrollbarStepNeg(item);
					item->slider.press_time = .1f;
				}
			}
			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed)) && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosHighlight))) {
				item->slider.press_time -= dt;
				if (item->slider.press_time <= 0) {
					zt_guiScrollbarStepPos(item);
					item->slider.press_time = .1f;
				}
			}

			zt_bitRemove(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegHighlight) | zt_bit(ztGuiSliderInternalStates_PosHighlight));
		}
	}
}

// ------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSliderBaseRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiSliderBaseRender))
{
	zt_guiThemeRender(theme, draw_list, item, item->pos + offset);
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_guiItemSliderMouseOverButton(ztGuiItem *item, ztGuiTheme *theme, ztVec2& mpos) // 0 = none, -1 = neg, 1 = pos
{
	ZT_PROFILE_GUI("_zt_guiItemSliderMouseOverButton");

	if (item->type != ztGuiItemType_Scrollbar || !zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver)) {
		return 0;
	}

	r32 scrollbar_button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW);
	if (item->slider.orient == ztGuiItemOrient_Horz) {
		if (mpos.x <= item->size.x / -2.f + scrollbar_button_w) return -1;
		else if (mpos.x >= item->size.x / 2.f - scrollbar_button_w) return 1;
	}
	else {
		if (mpos.y <= item->size.y / -2.f + scrollbar_button_w) return 1;
		else if (mpos.y >= item->size.y / 2.f - scrollbar_button_w) return -1;
	}

	return 0;
}

// ------------------------------------------------------------------------------------

ztInternal void _zt_guiItemSliderProcessDragReturn(ztGuiItem *item, ztGuiTheme *theme, ztInputMouse *input_mouse)
{
	ZT_PROFILE_GUI("_zt_guiItemSliderProcessDragReturn");

	r32 slider_handle_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize);

	ztVec2 mouse_pos = zt_guiItemPositionScreenToLocal(item, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));
	if (item->type == ztGuiItemType_Slider) {
		if (item->slider.orient == ztGuiItemOrient_Horz) {
			r32 pos_x = (mouse_pos.x - item->slider.drag_state.offset_x) + ((item->size.x - slider_handle_w) / 2);
			item->slider.value = zt_clamp(pos_x / (item->size.x - slider_handle_w), 0, 1);
		}
		else {
			r32 pos_y = (mouse_pos.y - item->slider.drag_state.offset_y) + ((item->size.y - slider_handle_w) / 2);
			item->slider.value = zt_clamp(1.f - (pos_y / (item->size.y - slider_handle_w)), 0, 1);
		}
	}
	else {
		r32 handle_size = item->slider.handle_size;
		r32 size_item = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;
		r32 size_value = size_item - handle_size;

		r32 button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW);

		size_value -= button_w * 2;
		if (zt_real32Eq(size_value, 0.f)) {
			size_value = 0.01f;
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

	_zt_guiSliderBaseCalcHandleSizeAndPos(item);
}

// ------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiItemSliderInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiItemSliderInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiItemSliderInputMouse");

	if (!item->slider.drag_state.dragging) {
		ztGuiTheme *theme = zt_guiItemGetTheme(item);
		ztVec2 mouse_pos = zt_guiItemPositionScreenToLocal(item, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));

		int button = _zt_guiItemSliderMouseOverButton(item, theme, mouse_pos);
		if (button == -1) { item->state_flags |= zt_bit(ztGuiSliderInternalStates_NegHighlight); }
		else if (button == 1) { item->state_flags |= zt_bit(ztGuiSliderInternalStates_PosHighlight); }

		if (!input_mouse->leftPressed()) {
			zt_bitRemove(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed) | zt_bit(ztGuiSliderInternalStates_PosPressed));
		}

		if (button != 0) {
			if (input_mouse->leftJustPressed()) {
				if (button == -1) {
					item->state_flags |= zt_bit(ztGuiSliderInternalStates_NegPressed);
					zt_guiScrollbarStepNeg(item);
					item->slider.press_time = 0.25f;
				}
				else if (button == 1) {
					item->state_flags |= zt_bit(ztGuiSliderInternalStates_PosPressed);
					zt_guiScrollbarStepPos(item);
					item->slider.press_time = 0.25f;
				}
			}
		}
		else if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed))) {
			// do nothing
		}
		else {
			if (item->slider.orient == ztGuiItemOrient_Horz) {
				ztVec2 handle_pos = ztVec2(item->slider.handle_pos, 0);
				r32 handle_size = item->slider.handle_size;
				if (mouse_pos.x >= handle_pos.x - handle_size / 2.f && mouse_pos.x <= handle_pos.x + handle_size / 2.f) {
					item->slider.drag_pos[0] = zt_guiItemPositionLocalToScreen(item, handle_pos).x;
					item->slider.drag_pos[1] = 0;
					item->slider.highlight = true;
					if (_zt_guiProcessDrag(&item->slider.drag_state, item->gm, (ztVec2*)item->slider.drag_pos, input_mouse)) {
						_zt_guiItemSliderProcessDragReturn(item, theme, input_mouse);
						return true;
					}
					return false;
				}
				else if (input_mouse->leftJustPressed()) {
					if (item->type == ztGuiItemType_Scrollbar) {
						if (mouse_pos.x < handle_pos.x) zt_guiScrollbarStepPageNeg(item);
						else zt_guiScrollbarStepPagePos(item);
					}
					else {
						_zt_guiItemSliderProcessDragReturn(item, theme, input_mouse);
						return true;
					}
				}
			}
			else {
				ztVec2 handle_pos = ztVec2(0, item->slider.handle_pos);
				r32 handle_size = item->slider.handle_size;
				if (mouse_pos.y >= handle_pos.y - handle_size / 2.f && mouse_pos.y <= handle_pos.y + handle_size / 2.f) {
					item->slider.drag_pos[0] = 0;
					item->slider.drag_pos[1] = zt_guiItemPositionLocalToScreen(item, handle_pos).y;
					item->slider.highlight = true;
					if (_zt_guiProcessDrag(&item->slider.drag_state, item->gm, (ztVec2*)item->slider.drag_pos, input_mouse)) {
						_zt_guiItemSliderProcessDragReturn(item, theme, input_mouse);
						return true;
					}
					return false;
				}
				else if (input_mouse->leftJustPressed()) {
					if (item->type == ztGuiItemType_Scrollbar) {
						if (mouse_pos.x < handle_pos.x) zt_guiScrollbarStepPageNeg(item);
						else zt_guiScrollbarStepPagePos(item);
					}
					else {
						_zt_guiItemSliderProcessDragReturn(item, theme, input_mouse);
						return true;
					}
				}
			}
		}
	}
	else if (_zt_guiProcessDrag(&item->slider.drag_state, item->gm, (ztVec2*)item->slider.drag_pos, input_mouse)) {
		item->slider.highlight = true;
		ztGuiTheme *theme = zt_guiItemGetTheme(item);
		_zt_guiItemSliderProcessDragReturn(item, theme, input_mouse);
		return true;
	}
	item->slider.highlight = false;
	return false;
}

// ------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiItemSliderBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiItemSliderBestSize))
{
	ZT_PROFILE_GUI("_zt_guiItemSliderBestSize");

	if (item->type == ztGuiItemType_Slider) {
		if (item->slider.orient == ztGuiItemOrient_Horz) {
			min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize) * 2;
			min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleMinHeight);
		}
		else {
			min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize) * 2;
			min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleMinHeight);
		}
	}
	else {
		if (item->slider.orient == ztGuiItemOrient_Horz) {
			min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW) * 2;
			min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinWidth);
		}
		else {
			min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW) * 2;
			min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinWidth);
		}
	}

	*size = *min_size;
}

// ------------------------------------------------------------------------------------

ztInternal ztGuiItem *_zt_guiMakeSliderBase(ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value, bool scrollbar)
{
	ZT_PROFILE_GUI("_zt_guiMakeSliderBase");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Slider, ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->slider.live_value = live_value;

	item->slider.value = live_value ? zt_clamp(*live_value, 0, 1) : 0;
	item->slider.orient = orient;

	item->functions.input_mouse = _zt_guiItemSliderInputMouse_FunctionID;
	item->functions.render      = _zt_guiSliderBaseRender_FunctionID;
	item->functions.best_size   = _zt_guiItemSliderBestSize_FunctionID;
	item->functions.update      = _zt_guiSliderBaseUpdate_FunctionID;

	if (scrollbar) {
		item->type = ztGuiItemType_Scrollbar;
		item->slider.step = .1f;
		item->slider.step_page = .25f;
		item->slider.handle_pct = .5f;
		item->slider.press_button = 0;
		item->slider.press_time = 0;
	}

	ztVec2 min_size;
	_zt_guiItemSliderBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeSlider(ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeSlider");

	return _zt_guiMakeSliderBase(parent, orient, live_value, false);
}

// ------------------------------------------------------------------------------------------------

r32 zt_guiSliderGetValue(ztGuiItem *slider)
{
	zt_assertReturnValOnFail(slider->type == ztGuiItemType_Slider, 0);

	return slider->slider.value;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSliderSetValue(ztGuiItem *slider, r32 value)
{
	zt_assertReturnOnFail(slider->type == ztGuiItemType_Slider);

	slider->slider.value = value;
	if (slider->slider.live_value) {
		*slider->slider.live_value = value;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeScrollbar(ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeScrollbar");

	return _zt_guiMakeSliderBase(parent, orient, live_value, true);
}

// ------------------------------------------------------------------------------------------------

r32 zt_guiScrollbarGetValue(ztGuiItem *scrollbar)
{
	zt_assertReturnValOnFail(scrollbar->type == ztGuiItemType_Scrollbar, 0);

	return scrollbar->slider.value;
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollbarSetValue(ztGuiItem *scrollbar, r32 value)
{
	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.value = value;
	if (scrollbar->slider.live_value) {
		*scrollbar->slider.live_value = value;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollbarSetSteps(ztGuiItem *scrollbar, r32 step_single, r32 step_page)
{
	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.step = zt_abs(step_single);
	scrollbar->slider.step_page = zt_abs(step_page);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepNeg(ztGuiItem *scrollbar)
{
	ZT_PROFILE_GUI("zt_guiScrollbarStepNeg");

	zt_assertReturnValOnFail(scrollbar->type == ztGuiItemType_Scrollbar, false);

	if (scrollbar->slider.value == 0) {
		return false;
	}

	scrollbar->slider.value = zt_max(0, scrollbar->slider.value - scrollbar->slider.step);
	if (scrollbar->slider.live_value) {
		*scrollbar->slider.live_value = scrollbar->slider.value;
	}
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepPageNeg(ztGuiItem *scrollbar)
{
	ZT_PROFILE_GUI("zt_guiScrollbarStepPageNeg");

	zt_assertReturnValOnFail(scrollbar->type == ztGuiItemType_Scrollbar, false);

	if (scrollbar->slider.value == 0) {
		return false;
	}

	scrollbar->slider.value = zt_max(0, scrollbar->slider.value - scrollbar->slider.step_page);
	if (scrollbar->slider.live_value) {
		*scrollbar->slider.live_value = scrollbar->slider.value;
	}
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepPos(ztGuiItem *scrollbar)
{
	ZT_PROFILE_GUI("zt_guiScrollbarStepPos");

	zt_assertReturnValOnFail(scrollbar->type == ztGuiItemType_Scrollbar, false);

	if (scrollbar->slider.value == 1) {
		return false;
	}

	scrollbar->slider.value = zt_min(1, scrollbar->slider.value + scrollbar->slider.step);
	if (scrollbar->slider.live_value) {
		*scrollbar->slider.live_value = scrollbar->slider.value;
	}
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);

	return true;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiScrollbarStepPagePos(ztGuiItem *scrollbar)
{
	ZT_PROFILE_GUI("zt_guiScrollbarStepPagePos");

	zt_assertReturnValOnFail(scrollbar->type == ztGuiItemType_Scrollbar, false);

	if (scrollbar->slider.value == 1) {
		return false;
	}

	scrollbar->slider.value = zt_min(1, scrollbar->slider.value + scrollbar->slider.step_page);
	if (scrollbar->slider.live_value) {
		*scrollbar->slider.live_value = scrollbar->slider.value;
	}
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollbarSetPercent(ztGuiItem *scrollbar, r32 percent)
{
	ZT_PROFILE_GUI("zt_guiScrollbarSetPercent");

	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.handle_pct = zt_clamp(percent, 0, 1);
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiScrollContainerCalcViewportSizePos(ztGuiItem *item, ztVec2 *pposition, ztVec2 *psize)
{
	ZT_PROFILE_GUI("_zt_guiScrollContainerCalcViewportSizePos");

	if (item->size == ztVec2::zero) {
		return;
	}

	ztVec2 size = *psize;
	ztVec2 position = *pposition;

	if (item->scrolled_container.contained_item == nullptr) {
		return;
	}

	bool horz_vis = zt_bitIsSet(item->behavior_flags, ztGuiScrollContainerBehaviorFlags_ShowScrollHorz);
	bool horz_vis_disabled = horz_vis;
	if (size.x < item->scrolled_container.contained_item->size.x) {
		horz_vis = true;
		horz_vis_disabled = false;
	}
	else {
		zt_bitRemove(item->scrolled_container.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible));
	}
	if (horz_vis) {
		item->scrolled_container.scrollbar_horz->state_flags |= zt_bit(ztGuiItemStates_Visible);
	}

	bool vert_vis = zt_bitIsSet(item->behavior_flags, ztGuiScrollContainerBehaviorFlags_ShowScrollVert);
	bool vert_vis_disabled = vert_vis;
	if (size.y < item->scrolled_container.contained_item->size.y) {
		vert_vis = true;
		vert_vis_disabled = false;
	}
	else {
		zt_bitRemove(item->scrolled_container.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible));
	}
	if (vert_vis) {
		item->scrolled_container.scrollbar_vert->state_flags |= zt_bit(ztGuiItemStates_Visible);
	}

	zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_horz, item->scrolled_container.scroll_amt_horz);
	zt_guiScrollbarSetValue(item->scrolled_container.scrollbar_vert, item->scrolled_container.scroll_amt_vert);

	if (horz_vis) {
		zt_guiScrollbarSetPercent(item->scrolled_container.scrollbar_horz, item->size.x / item->scrolled_container.contained_item->size.x);

		r32 x_off = vert_vis ? item->scrolled_container.scrollbar_vert->size.x : 0;
		item->scrolled_container.scrollbar_horz->size.x = item->size.x - x_off;
		item->scrolled_container.scrollbar_horz->pos.x = x_off / -2;
		item->scrolled_container.scrollbar_horz->pos.y = -(item->size.y - item->scrolled_container.scrollbar_horz->size.y) / 2;
		size.y -= item->scrolled_container.scrollbar_horz->size.y;
		position.y += item->scrolled_container.scrollbar_horz->size.y / 2;
	}
	if (item->scrolled_container.scroll_amt_horz != ztInvalidID) {
		zt_guiItemEnable(item->scrolled_container.scrollbar_horz, !horz_vis_disabled);
	}

	if (vert_vis) {
		zt_guiScrollbarSetPercent(item->scrolled_container.scrollbar_vert, item->size.y / item->scrolled_container.contained_item->size.y);

		r32 y_off = horz_vis ? item->scrolled_container.scrollbar_horz->size.y : 0;
		item->scrolled_container.scrollbar_vert->size.y = item->size.y - y_off;
		item->scrolled_container.scrollbar_vert->pos.y = y_off / 2;
		item->scrolled_container.scrollbar_vert->pos.x = (item->size.x - item->scrolled_container.scrollbar_vert->size.x) / 2;
		size.x -= item->scrolled_container.scrollbar_vert->size.x;
		position.x -= item->scrolled_container.scrollbar_vert->size.x / 2;
	}
	if (item->scrolled_container.scroll_amt_vert != ztInvalidID) {
		zt_guiItemEnable(item->scrolled_container.scrollbar_vert, !vert_vis_disabled);
	}

	*pposition = position;
	*psize = size;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiScrollContainerUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiScrollContainerUpdate))
{
	ZT_PROFILE_GUI("_zt_guiScrollContainerUpdate");

	if (item->scrolled_container.contained_item == nullptr || !zt_guiItemIsShowing(item)) {
		return;
	}

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztGuiItem *contained = item->scrolled_container.contained_item;

	ztVec2 size = item->size;
	ztVec2 pos = item->pos;
	ztVec2 orig_pos = pos;
	ztVec2 orig_size = contained->size;

	_zt_guiScrollContainerCalcViewportSizePos(item, &pos, &size);
	item->scrolled_container.viewport_pos[0] = pos.x - orig_pos.x;
	item->scrolled_container.viewport_pos[1] = pos.y - orig_pos.y;
	item->scrolled_container.viewport_size[0] = size.x;
	item->scrolled_container.viewport_size[1] = size.y;

	zt_guiItemSetSize(item->scrolled_container.viewport, size);
	zt_guiItemSetPosition(item->scrolled_container.viewport, ztVec2(item->scrolled_container.viewport_pos[0], item->scrolled_container.viewport_pos[1]));

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollContainerPaddingX);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollContainerPaddingY);

	if (zt_bitIsSet(item->behavior_flags, ztGuiScrollContainerBehaviorFlags_StretchVert)) {
		contained->size.y = size.y - padding_y * 2;
	}
	if (zt_bitIsSet(item->behavior_flags, ztGuiScrollContainerBehaviorFlags_StretchHorz)) {
		contained->size.x = size.x - padding_x * 2;
	}

	r32 horz_amt = (item->scrolled_container.scrollbar_horz == nullptr || !zt_guiItemIsVisible(item->scrolled_container.scrollbar_horz) || !zt_guiItemIsEnabled(item->scrolled_container.scrollbar_horz)) ? 0 : item->scrolled_container.scroll_amt_horz;
	r32 vert_amt = (item->scrolled_container.scrollbar_vert == nullptr || !zt_guiItemIsVisible(item->scrolled_container.scrollbar_vert) || !zt_guiItemIsEnabled(item->scrolled_container.scrollbar_vert)) ? 0 : item->scrolled_container.scroll_amt_vert;

	contained->pos.x = (((size.x - contained->size.x) / -2.f) + padding_x) - (horz_amt * ((contained->size.x - size.x) + padding_x * 2));
	contained->pos.y = (((size.y - contained->size.y) / 2.f) - padding_y) + (vert_amt * ((contained->size.y - size.y) + padding_y * 2));

	item->scrolled_container.viewport->behavior_flags |= ztGuiItemBehaviorFlags_ClipChildren;
	item->scrolled_container.viewport->clip_area = ztVec4(0, 0, size.x - padding_x * 2, size.y - padding_y * 2);

	if (contained->size != orig_size) {
		zt_guiSizerRecalc(contained);
	}
}

// ------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiScrollContainerInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiScrollContainerInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiScrollContainerInputMouse");

	if (input_mouse->wheel_delta > 0) {
		zt_guiScrollbarStepNeg(item->scrolled_container.scrollbar_vert);
	}
	else if (input_mouse->wheel_delta < 0) {
		zt_guiScrollbarStepPos(item->scrolled_container.scrollbar_vert);
	}

	return false;
}

// ------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiScrollContainerInputKey, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiScrollContainerInputKey))
{
	ZT_PROFILE_GUI("_zt_guiScrollContainerInputKey");

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

ZT_FUNCTION_POINTER_REGISTER(_zt_guiScrollContainerBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiScrollContainerBestSize))
{
	ZT_PROFILE_GUI("_zt_guiScrollContainerBestSize");

	if (item->scrolled_container.contained_item != nullptr) {
		*min_size = item->scrolled_container.contained_item->size;
	}

	*size = *min_size;
}

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeScrollContainer(ztGuiItem *parent, i32 behavior_flags)
{
	ZT_PROFILE_GUI("zt_guiMakeScrollContainer");

	zt_returnValOnNull(parent, nullptr);

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_ScrollContainer, ztGuiItemBehaviorFlags_ClipChildren | behavior_flags);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->scrolled_container.scrollbar_horz   = zt_guiMakeScrollbar(item, ztGuiItemOrient_Horz, &item->scrolled_container.scroll_amt_horz);
	item->scrolled_container.scrollbar_vert   = zt_guiMakeScrollbar(item, ztGuiItemOrient_Vert, &item->scrolled_container.scroll_amt_vert);
	item->scrolled_container.viewport         = zt_guiMakePanel(item, ztGuiItemBehaviorFlags_ClipChildren | (zt_bitIsSet(behavior_flags, ztGuiScrollContainerBehaviorFlags_NoBackground) ? 0 : ztGuiPanelBehaviorFlags_DrawBackground));
	item->scrolled_container.contained_item   = nullptr;
	item->scrolled_container.scroll_amt_vert  = 0;
	item->scrolled_container.scroll_amt_horz  = 0;
	item->scrolled_container.viewport_pos [0] = 0;
	item->scrolled_container.viewport_pos [1] = 0;
	item->scrolled_container.viewport_size[0] = 0;
	item->scrolled_container.viewport_size[1] = 0;

	zt_debugOnly(zt_guiItemSetName(item->scrolled_container.scrollbar_horz, "Horz Scrollbar"));
	zt_debugOnly(zt_guiItemSetName(item->scrolled_container.scrollbar_vert, "Vert Scrollbar"));
	zt_debugOnly(zt_guiItemSetName(item->scrolled_container.viewport, "Viewport"));

	item->functions.input_mouse = _zt_guiScrollContainerInputMouse_FunctionID;
	item->functions.input_key   = _zt_guiScrollContainerInputKey_FunctionID;
	item->functions.update      = _zt_guiScrollContainerUpdate_FunctionID;
	item->functions.best_size   = _zt_guiScrollContainerBestSize_FunctionID;

	ztVec2 min_size = ztVec2::zero;
	_zt_guiScrollContainerBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerSetItem(ztGuiItem *scroll, ztGuiItem *internal_item)
{
	ZT_PROFILE_GUI("zt_guiScrollContainerSetItem");

	zt_returnOnNull(scroll);
	zt_returnOnNull(internal_item);
	zt_assertReturnOnFail(scroll->type == ztGuiItemType_ScrollContainer);

	zt_guiItemReparent(internal_item, scroll->scrolled_container.viewport);

	scroll->scrolled_container.contained_item = internal_item;
	_zt_guiScrollContainerUpdate(scroll, 0, scroll->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerResetScroll(ztGuiItem *scroll)
{
	ZT_PROFILE_GUI("zt_guiScrollContainerResetScroll");

	zt_returnOnNull(scroll);
	zt_assertReturnOnFail(scroll->type == ztGuiItemType_ScrollContainer);

	scroll->scrolled_container.scroll_amt_horz = 0;
	scroll->scrolled_container.scroll_amt_vert = 0;
	_zt_guiScrollContainerUpdate(scroll, 0, scroll->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiScrollContainerSetScroll(ztGuiItem *scroll, ztGuiItemOrient_Enum orient, r32 value)
{
	zt_returnOnNull(scroll);
	zt_assertReturnOnFail(scroll->type == ztGuiItemType_ScrollContainer);

	if (orient == ztGuiItemOrient_Horz) {
		scroll->scrolled_container.scroll_amt_horz = value;
	}
	else {
		scroll->scrolled_container.scroll_amt_vert = value;
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal ztVec2 _zt_guiTextEditGetTextStartPos(ztGuiItem *item, ztGuiTheme *theme)
{
	ZT_PROFILE_GUI("_zt_guiTextEditGetTextStartPos");

	ztVec2 pos = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingX);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY);

	r32 diff_x = zt_max(0, item->textedit.content_size[0] - (item->size.x - padding_x * 2.f));
	r32 diff_y = zt_max(0, item->textedit.content_size[1] - (item->size.y - padding_y * 2.f));

	if (item->textedit.scrollbar_vert != nullptr && zt_bitIsSet(item->textedit.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		diff_x += item->textedit.scrollbar_vert->size.x;
	}
	if (item->textedit.scrollbar_horz != nullptr && zt_bitIsSet(item->textedit.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		diff_y += item->textedit.scrollbar_horz->size.y;
	}

	return ztVec2(pos.x - item->size.x / 2.f + padding_x - (diff_x * item->textedit.scroll_amt_horz),
	              pos.y + item->size.y / 2.f - padding_y + (diff_y * item->textedit.scroll_amt_vert));
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditSizeContent(ztGuiItem *item, ztGuiTheme *theme)
{
	ZT_PROFILE_GUI("_zt_guiTextEditSizeContent");

	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID);
	ztVec2 size = zt_fontGetExtents(font, item->textedit.text_buffer);

	if (zt_strEndsWith(item->textedit.text_buffer, "\n")) {
		ztVec2 extra = zt_fontGetExtents(font, " ");
		size.y += extra.y;
	}

	item->textedit.content_size[0] = size.x;
	item->textedit.content_size[1] = size.y;

	ztGuiItem *scroll_horz = item->textedit.scrollbar_horz;
	ztGuiItem *scroll_vert = item->textedit.scrollbar_vert;

	bool vert = scroll_vert ? (item->textedit.content_size[1] > item->size.y) : false;
	bool horz = scroll_horz ? (item->textedit.content_size[0] > item->size.x - (vert && scroll_vert ? scroll_vert->size.x : 0)) : false;

	item->clip_area.xy = ztVec2::zero;
	item->clip_area.zw = item->size;

	if (horz) {
		if (zt_bitIsSet(item->behavior_flags, ztGuiTextEditBehaviorFlags_MultiLine)) {
			scroll_horz->state_flags |= zt_bit(ztGuiItemStates_Visible);
			scroll_horz->pos.y = (item->size.y - scroll_horz->size.y) / -2.f;
			scroll_horz->pos.x = (vert ? -scroll_vert->size.x / 2.f : 0);
			scroll_horz->size.x = item->size.x - (vert ? scroll_vert->size.x : 0);
			item->clip_area.y += scroll_horz->size.y / 2.f;
			item->clip_area.w -= scroll_horz->size.y;
		}
	}
	else if (scroll_horz) {
		zt_bitRemove(scroll_horz->state_flags, zt_bit(ztGuiItemStates_Visible));
	}

	if (vert) {
		scroll_vert->state_flags |= zt_bit(ztGuiItemStates_Visible);
		scroll_vert->pos.x = (item->size.x - scroll_vert->size.x) / 2.f;
		scroll_vert->pos.y = (horz ? scroll_horz->size.y / 2.f : 0);
		scroll_vert->size.y = item->size.y - (horz ? scroll_horz->size.y : 0);
		item->clip_area.x -= scroll_vert->size.x / 2.f;
		item->clip_area.z -= scroll_vert->size.x;

		int lines_count = zt_strCount(item->textedit.text_buffer, "\n");
		r32 line_height = item->textedit.content_size[1] / lines_count;

		r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY);
		int lines_shown = zt_convertToi32Floor(((item->size.y - padding_y * 2.f) - (horz ? scroll_horz->size.y : 0)) / line_height);
		r32 pct_per_line = line_height / ((lines_count - lines_shown) * line_height);

		zt_guiScrollbarSetSteps(item->textedit.scrollbar_vert, pct_per_line, lines_shown * pct_per_line);
	}
	else if (scroll_vert) {
		zt_bitRemove(scroll_vert->state_flags, zt_bit(ztGuiItemStates_Visible));
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditAdjustViewForCursor(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiTextEditAdjustViewForCursor");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	if (item->textedit.content_size[0] == 0 && item->textedit.content_size[1] == 0) {
		_zt_guiTextEditSizeContent(item, theme);
	}

	ztVec2 cursor_pos_beg = zt_guiTextEditGetCharacterPos(item, item->textedit.cursor_pos, false);
	ztVec2 cursor_pos_end = zt_guiTextEditGetCharacterPos(item, item->textedit.cursor_pos, true);

	ztVec2 text_pos = zt_guiItemPositionScreenToLocal(item, _zt_guiTextEditGetTextStartPos(item, theme));
	cursor_pos_beg += text_pos;
	cursor_pos_end += text_pos;

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingX);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY);
	r32 x_diff = zt_max(0, item->textedit.content_size[0] - (item->size.x - padding_x * 2.f));
	r32 y_diff = zt_max(0, item->textedit.content_size[1] - (item->size.y - padding_y * 2.f));

	if (item->textedit.scrollbar_vert != nullptr && zt_bitIsSet(item->textedit.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		x_diff += item->textedit.scrollbar_vert->size.x;
	}
	if (item->textedit.scrollbar_horz != nullptr && zt_bitIsSet(item->textedit.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		y_diff += item->textedit.scrollbar_horz->size.y;
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
	ZT_PROFILE_GUI("_zt_guiTextEditCacheText");

	zt_drawListReset(item->draw_list);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	zt_drawListAddText2D(item->draw_list, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID), item->textedit.text_buffer, ztVec2::zero, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditGetCurrentLineInfo(ztGuiItem *item, int *beg_pos, int *end_pos, int from_pos = -1)
{
	ZT_PROFILE_GUI("_zt_guiTextEditGetCurrentLineInfo");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

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
	ZT_PROFILE_GUI("_zt_guiTextEditRecalcCursor");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID);
	int beg_line = 0;
	_zt_guiTextEditGetCurrentLineInfo(item, &beg_line, nullptr);
	if (beg_line != ztStrPosNotFound) {
		ztVec2 ext = zt_fontGetExtents(font, item->textedit.text_buffer, beg_line);

		item->textedit.cursor_xy[1] = -ext.y;
	}
	else {
		beg_line = 0;
		item->textedit.cursor_xy[1] = 0;
	}

	const char *text = zt_strMoveForward(item->textedit.text_buffer, beg_line);
	item->textedit.cursor_xy[0] = zt_fontGetExtents(font, text, item->textedit.cursor_pos - beg_line).x;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiTextEditUpdate))
{
	ZT_PROFILE_GUI("_zt_guiTextEditUpdate");

	if (!zt_guiItemIsShowing(item)) {
		return;
	}

	item->textedit.cursor_blink_time -= dt;
	if (item->textedit.cursor_blink_time < 0) {
		item->textedit.cursor_blink_time += .5f;
		item->textedit.cursor_vis = !item->textedit.cursor_vis;
	}

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	if ((item->textedit.content_size[0] == 0 && item->textedit.content_size[1] == 0) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty))) {
		_zt_guiTextEditSizeContent(item, theme);
	}

	ztVec2 text_pos = _zt_guiTextEditGetTextStartPos(item, theme);
	item->textedit.text_pos[0] = text_pos.x;
	item->textedit.text_pos[1] = text_pos.y;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiTextEditRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiTextEditCleanup))
{
	ZT_PROFILE_GUI("_zt_guiTextEditCleanup");

	zt_stringFree(item->textedit.text_buffer, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

#ifndef ZT_TEXTEDIT_WORD_SEPARATORS
#define ZT_TEXTEDIT_WORD_SEPARATORS      " \t"
#endif

#ifndef ZT_TEXTEDIT_WORD_SEPARATORS_LEN
#define ZT_TEXTEDIT_WORD_SEPARATORS_LEN     2
#endif

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_guiTextEditPosNextWord(ztGuiItem *item, int str_len)
{
	ZT_PROFILE_GUI("_zt_guiTextEditPosNextWord");

	int pos = item->textedit.cursor_pos;
	bool break_next_char = item->textedit.text_buffer[pos] == '\n';
	while (++pos < str_len) {
		if (item->textedit.text_buffer[pos] == '\n') break;

		bool is_separator = false;
		zt_fjz(ZT_TEXTEDIT_WORD_SEPARATORS_LEN) {
			if (is_separator = item->textedit.text_buffer[pos] == ZT_TEXTEDIT_WORD_SEPARATORS[j]) {
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

ztInternal int _zt_guiTextEditPosPrevWord(ztGuiItem *item, int str_len)
{
	ZT_PROFILE_GUI("_zt_guiTextEditPosPrevWord");

	int pos = item->textedit.cursor_pos;
	while (--pos > 0) {
		if (item->textedit.text_buffer[pos - 1] == '\n') break;

		bool need_break = false;
		zt_fjz(ZT_TEXTEDIT_WORD_SEPARATORS_LEN) {
			if (need_break = item->textedit.text_buffer[pos - 1] == ZT_TEXTEDIT_WORD_SEPARATORS[j]) {
				break;
			}
		}
		if (need_break) break;
	}

	return pos;
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_guiTextEditPosAboveChar(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiTextEditPosAboveChar");

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

ztInternal int _zt_guiTextEditPosBelowChar(ztGuiItem *item, int str_len)
{
	ZT_PROFILE_GUI("_zt_guiTextEditPosBelowChar");

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

ztInternal void _zt_guiTextEditSelectBeg(ztGuiItem *item, bool force = false)
{
	if (force || item->textedit.select_beg == -1) {
		item->textedit.select_beg = item->textedit.select_end = item->textedit.cursor_pos;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTextEditSelectEnd(ztGuiItem *item)
{
	item->textedit.select_end = item->textedit.cursor_pos;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditInputKey, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiTextEditInputKey))
{
	ZT_PROFILE_GUI("_zt_guiTextEditInputKey");

	if (item->textedit.on_key != ztInvalidID) {
		bool should_process = true;
		((zt_guiTextEditKey_Func*)zt_functionPointer(item->textedit.on_key))(item, input_keys, input_key_strokes, &should_process, item->textedit.on_key_user_data);
		if (!should_process) {
			return false;
		}
	}

	bool recalc_cursor = false;

	int str_len = zt_strLen(item->textedit.text_buffer);

	bool shifting = input_keys[ztInputKeys_Shift].pressed();
	if (shifting) {
		_zt_guiTextEditSelectBeg(item);
	}

	if (input_keys[ztInputKeys_Right].justPressedOrRepeated()) {
		recalc_cursor = true;
		if (item->textedit.cursor_pos < str_len) {
			if (input_keys[ztInputKeys_Control].pressed()) {
				item->textedit.cursor_pos = _zt_guiTextEditPosNextWord(item, str_len);
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
				item->textedit.cursor_pos = _zt_guiTextEditPosPrevWord(item, str_len);
			}
			else {
				item->textedit.cursor_pos -= 1;
			}
		}
	}
	if (input_keys[ztInputKeys_Up].justPressedOrRepeated() && zt_bitIsSet(item->behavior_flags, ztGuiTextEditBehaviorFlags_MultiLine)) {
		recalc_cursor = true;
		item->textedit.cursor_pos = _zt_guiTextEditPosAboveChar(item);
	}
	if (input_keys[ztInputKeys_Down].justPressedOrRepeated() && zt_bitIsSet(item->behavior_flags, ztGuiTextEditBehaviorFlags_MultiLine)) {
		recalc_cursor = true;
		item->textedit.cursor_pos = _zt_guiTextEditPosBelowChar(item, str_len);
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
				int next_word = _zt_guiTextEditPosNextWord(item, str_len);
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
				int prev_word = _zt_guiTextEditPosPrevWord(item, str_len);
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
		_zt_guiTextEditSelectEnd(item);
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

			if (input_key_strokes[i] == ztInputKeys_Return && !zt_bitIsSet(item->behavior_flags, ztGuiTextEditBehaviorFlags_MultiLine)) {
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

	return true;
}

// ------------------------------------------------------------------------------------------------

ztInternal int _zt_guiTextEditGetCursorIndexAtPosition(ztGuiItem *item, ztVec2 pos)
{
	ZT_PROFILE_GUI("_zt_guiTextEditGetCursorIndexAtPosition");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID);

	ztVec2 chpos = _zt_guiTextEditGetTextStartPos(item, theme);

	int prev_idx = 0;
	int idx = zt_strFindPos(item->textedit.text_buffer, "\n", 0);
	while (idx != ztStrPosNotFound) {
		idx += 1;

		ztVec2 ext = zt_fontGetExtents(font, zt_strMoveForward(item->textedit.text_buffer, prev_idx), idx - prev_idx);

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
		ztVec2 ext = zt_fontGetExtents(font, line, i);
		if (pos.x < chpos.x + ext.x) {
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

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiTextEditInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiTextEditInputMouse");

	if (input_mouse->leftJustPressed()) {
		ztVec2 mpos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		item->textedit.cursor_pos = _zt_guiTextEditGetCursorIndexAtPosition(item, mpos);
		_zt_guiTextEditRecalcCursor(item);

		item->textedit.dragging = true;
		_zt_guiTextEditSelectBeg(item, true);
	}
	else if (input_mouse->leftJustReleased()) {
		item->textedit.dragging = false;
		_zt_guiTextEditSelectEnd(item);
	}
	else if (item->textedit.dragging) {
		ztVec2 mpos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		item->textedit.cursor_pos = item->textedit.select_end = _zt_guiTextEditGetCursorIndexAtPosition(item, mpos);
		_zt_guiTextEditRecalcCursor(item);
		_zt_guiTextEditAdjustViewForCursor(item);
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiTextEditBestSize))
{
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeTextEdit(ztGuiItem *parent, const char *value, i32 flags, i32 buffer_size)
{
	ZT_PROFILE_GUI("zt_guiMakeTextEdit");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_TextEdit, ztGuiItemBehaviorFlags_ClipContents | ztGuiItemBehaviorFlags_WantsFocus | flags, buffer_size * 2);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingX);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY);

	zt_guiItemSetSize(item, ztVec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultW), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultH)));

	item->textedit.cursor_pos      = 0;
	item->textedit.cursor_xy[0]    = item->textedit.cursor_xy[1] = 0;
	item->textedit.cursor_vis      = false;
	item->textedit.text_buffer     = zt_stringMake(buffer_size, item->gm->arena);
	item->textedit.text_buffer[0]  = 0;
	item->textedit.select_beg      = -1;
	item->textedit.select_end      = -1;
	item->textedit.dragging        = false;
	item->textedit.scroll_amt_horz = 0;
	item->textedit.scroll_amt_vert = 0;
	item->textedit.content_size[0] = 0;
	item->textedit.content_size[1] = 0;
	item->textedit.on_key          = ztInvalidID;

	if (zt_bitIsSet(flags, ztGuiTextEditBehaviorFlags_MultiLine)) {
		item->textedit.scrollbar_horz = zt_guiMakeScrollbar(item, ztGuiItemOrient_Horz, &item->textedit.scroll_amt_horz);
		zt_bitRemove(item->textedit.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible));

		item->textedit.scrollbar_vert = zt_guiMakeScrollbar(item, ztGuiItemOrient_Vert, &item->textedit.scroll_amt_vert);
		zt_bitRemove(item->textedit.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible));
	}
	else {
		item->textedit.scrollbar_vert = nullptr;
		item->textedit.scrollbar_horz = nullptr;
	}

	if (value) {
		zt_stringOverwrite(item->textedit.text_buffer, value, item->gm->arena);
		_zt_guiTextEditCacheText(item);
	}

	item->functions.cleanup     = _zt_guiTextEditCleanup_FunctionID;
	item->functions.update      = _zt_guiTextEditUpdate_FunctionID;
	item->functions.input_mouse = _zt_guiTextEditInputMouse_FunctionID;
	item->functions.input_key   = _zt_guiTextEditInputKey_FunctionID;
	item->functions.render      = _zt_guiTextEditRender_FunctionID;
	item->functions.best_size   = _zt_guiTextEditBestSize_FunctionID;

	ztVec2 min_size;
	_zt_guiTextEditBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

int zt_guiTextEditGetValue(ztGuiItem *text, char *buffer, int buffer_len)
{
	ZT_PROFILE_GUI("zt_guiTextEditGetValue");

	zt_assertReturnValOnFail(text->type == ztGuiItemType_TextEdit, -1);
	return zt_strCpy(buffer, buffer_len, text->textedit.text_buffer);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetValue(ztGuiItem *text, const char *value)
{
	ZT_PROFILE_GUI("zt_guiTextEditSetValue");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	zt_strCpy(text->textedit.text_buffer, zt_stringSize(text->textedit.text_buffer), value);

	text->textedit.cursor_pos = 0;
	text->textedit.select_beg = text->textedit.select_end = -1;
	_zt_guiTextEditRecalcCursor(text);
	_zt_guiTextEditAdjustViewForCursor(text);
	_zt_guiTextEditCacheText(text);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetSelection(ztGuiItem *text, int sel_beg, int sel_end)
{
	ZT_PROFILE_GUI("zt_guiTextEditSetSelection");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	int str_len = zt_strLen(text->textedit.text_buffer);

	text->textedit.select_beg = zt_clamp(sel_beg, 0, str_len);
	text->textedit.select_end = zt_clamp(sel_end, 0, str_len);
	text->textedit.cursor_pos = zt_clamp(sel_end, 0, str_len);
	_zt_guiTextEditRecalcCursor(text);
	_zt_guiTextEditAdjustViewForCursor(text);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditGetSelection(ztGuiItem *text, int *sel_beg, int *sel_end)
{
	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);

	*sel_beg = text->textedit.select_beg;
	*sel_end = text->textedit.select_end;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSelectAll(ztGuiItem *text)
{
	ZT_PROFILE_GUI("zt_guiTextEditSelectAll");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	zt_guiTextEditSetSelection(text, 0, zt_strLen(text->textedit.text_buffer));
}

// ------------------------------------------------------------------------------------------------

int zt_guiTextEditGetCursorPos(ztGuiItem *text)
{
	zt_assertReturnValOnFail(text->type == ztGuiItemType_TextEdit, -1);
	return text->textedit.cursor_pos;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetCursorPos(ztGuiItem *text, int cursor_pos)
{
	ZT_PROFILE_GUI("zt_guiTextEditSetCursorPos");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	text->textedit.cursor_pos = zt_clamp(cursor_pos, 0, zt_strLen(text->textedit.text_buffer));
	_zt_guiTextEditRecalcCursor(text);
	_zt_guiTextEditAdjustViewForCursor(text);
}

// ------------------------------------------------------------------------------------------------

void zt_guiTextEditSetCallback(ztGuiItem *text, ztFunctionID on_key, void *user_data)
{
	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	text->textedit.on_key = on_key;
	text->textedit.on_key_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiTextEditGetCharacterPos(ztGuiItem *item, int ch, bool bottom_right)
{
	ZT_PROFILE_GUI("zt_guiTextEditGetCharacterPos");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	ztVec2 chpos = ztVec2::zero;
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID);
	int prev_pos = 0;
	int pos = zt_strFindPos(item->textedit.text_buffer, "\n", 0);
	while (pos != ztStrPosNotFound && pos < ch) {
		pos += 1;
		ztVec2 ext = zt_fontGetExtents(font, zt_strMoveForward(item->textedit.text_buffer, prev_pos), pos - prev_pos);
		chpos.y -= ext.y;

		prev_pos = pos;
		pos = zt_strFindPos(item->textedit.text_buffer, "\n", pos + 1);
	}
	if (item->textedit.text_buffer[prev_pos] == '\n') {
		prev_pos += 1;
	}

	ztVec2 ext = zt_fontGetExtents(font, zt_strMoveForward(item->textedit.text_buffer, prev_pos), ch - prev_pos);
	chpos.x += ext.x;

	if (bottom_right) {
		chpos.y -= ext.y;
	}

	return chpos;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ztGuiMenuMaxMenuItems	128

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiMenuClose(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiMenuClose");

	zt_guiItemHide(item);
	item->menu.selected = item->menu.highlighted = -1;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiMenuCloseAll()
{
	ZT_PROFILE_GUI("_zt_guiMenuCloseAll");

	zt_flink(gm, zt_gui->gui_manager_first) {
		zt_fjze(gm->item_cache) {
			if (gm->item_cache_flags[j] != 0) {
				if (gm->item_cache[j].type == ztGuiItemType_Menu) {
					_zt_guiMenuClose(&gm->item_cache[j]);
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuBaseUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiMenuBaseUpdate))
{
	ZT_PROFILE_GUI("_zt_guiMenuBaseUpdate");

	if (item->type == ztGuiItemType_Menu) {
		if (item->gm->mouse_click && !item->menu.just_opened && item->gm->item_has_mouse != item && !zt_guiItemIsChildOf(item, item->gm->item_has_mouse)) {
			bool close = true;
			if (item->gm->item_has_mouse != nullptr) {
				if (item->gm->item_has_mouse->type == ztGuiItemType_Menu) {
					close = false;
				}
			}
			if (close) {
				_zt_guiMenuClose(item);
			}
		}
	}
	else {
		if (item->parent == nullptr) {
			item->size.x = zt_cameraOrthoGetViewportSize(item->gm->gui_camera).x;
		}
		else {
			item->size.x = item->parent->size.x;
		}
	}

	item->menu.just_opened = false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuBaseRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiMenuBaseRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiMenuCleanup))
{
	ZT_PROFILE_GUI("_zt_guiMenuCleanup");

	zt_fiz(item->menu.item_count) {
		zt_stringFree(item->menu.display[i], item->gm->arena);
	}

	zt_freeArena(item->menu.display, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiMenuInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiMenuInputMouse");

	ztVec2 mpos = zt_guiItemPositionScreenToLocal(item, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding);

	ztVec2 pos = ztVec2::zero;
	pos.x -= (item->size.x - padding * 2.f) / 2.f;
	pos.y += (item->size.y - padding * 2.f) / 2.f;

	item->menu.selected = item->menu.highlighted = -1;

	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_MenuFontID);
	zt_fiz(item->menu.item_count) {
		ztVec2 ext = zt_fontGetExtents(font, item->menu.display[i]);

		if (item->type == ztGuiItemType_Menu) {
			if (mpos.y <= pos.y && mpos.y > pos.y - ext.y) {
				item->menu.highlighted = i;
				break;
			}

			pos.y -= ext.y + padding;
		}
		else {
			if (mpos.x >= pos.x && mpos.x < pos.x + ext.x + padding * 2) {
				item->menu.highlighted = i;
				break;
			}

			pos.x += ext.x + padding * 2;
		}
	}

	bool need_open = false;
	if (item->type == ztGuiItemType_MenuBar && item->menu.highlighted != -1) {
		zt_fiz(item->menu.item_count) {
			if (item->menu.submenus[i] && zt_bitIsSet(item->menu.submenus[i]->state_flags, zt_bit(ztGuiItemStates_Visible))) {
				if (i != item->menu.highlighted) {
					_zt_guiMenuClose(item->menu.submenus[i]);
					need_open = true;
					item->menu.selected = i;
					break;
				}
			}
		}
	}

	if (need_open || input_mouse->leftJustReleased()) {
		item->menu.selected = item->menu.highlighted;

		if (item->menu.selected != -1 && item->menu.submenus[item->menu.selected] != nullptr) {
			ztVec2 ppos = item->type == ztGuiItemType_Menu ? ztVec2(item->size.x / 2.f, pos.y) : ztVec2(pos.x, item->size.y / -2.f);
			ppos = zt_guiItemPositionLocalToScreen(item, ppos);

			ztVec2 cam_min, cam_max;
			zt_cameraOrthoGetExtents(item->gm->gui_camera, &cam_min, &cam_max);

			ztGuiItem *submenu = item->menu.submenus[item->menu.selected];

			if (ppos.x + submenu->size.x / 2.f > cam_max.x) {
				ppos.x -= item->size.x + submenu->size.x;
			}

			if (ppos.y - submenu->size.y < cam_min.y) {
				ppos.y += submenu->size.y;
			}

			zt_guiMenuPopupAtPosition(item->menu.submenus[item->menu.selected], ppos);
		}
		else if (item->menu.selected != -1) {
			if (item->menu.on_selected != ztInvalidID && !need_open) {
				((zt_guiMenuSelected_Func*)zt_functionPointer(item->menu.on_selected))(item, item->menu.ids[item->menu.selected], item->menu.user_datas[item->menu.selected]);
			}

			_zt_guiMenuCloseAll();
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiMenuBestSize))
{
	ZT_PROFILE_GUI("_zt_guiMenuBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItem *_zt_guiMakeMenuBase(ztGuiItem *parent, bool bar)
{
	ZT_PROFILE_GUI("_zt_guiMakeMenuBase");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, bar ? ztGuiItemType_MenuBar : ztGuiItemType_Menu, /*ztGuiItemBehaviorFlags_ClipContents |*/ ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_BringToFront);
	zt_returnValOnNull(item, nullptr);

	if (!bar) {
		zt_guiItemHide(item);
	}

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	int max_menu = ztGuiMenuMaxMenuItems;
	i32 size = (zt_sizeof(char *) + zt_sizeof(i32) + zt_sizeof(ztGuiItem*) + zt_sizeof(ztSprite*) + zt_sizeof(void*)) * max_menu;
	byte *mem = zt_mallocStructArrayArena(byte, size, item->gm->arena);

	item->menu.display = (ztString*)mem;
	mem += max_menu * zt_sizeof(ztString);
	item->menu.ids = (i32*)mem;
	mem += max_menu * zt_sizeof(i32);
	item->menu.submenus = (ztGuiItem**)mem;
	mem += max_menu * zt_sizeof(ztGuiItem*);
	item->menu.icons = (ztSprite**)mem;
	mem += max_menu * zt_sizeof(ztSprite*);
	item->menu.user_datas = (void**)mem;

	item->menu.item_count = 0;
	item->menu.highlighted = -1;
	item->menu.just_opened = false;
	item->menu.on_selected = ztInvalidID;

	item->functions.cleanup     = _zt_guiMenuCleanup_FunctionID;
	item->functions.update      = _zt_guiMenuBaseUpdate_FunctionID;
	item->functions.input_mouse = _zt_guiMenuInputMouse_FunctionID;
	item->functions.render      = _zt_guiMenuBaseRender_FunctionID;
	item->functions.best_size   = _zt_guiMenuBestSize_FunctionID;

	ztVec2 min_size;
	_zt_guiMenuBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeMenu()
{
	ZT_PROFILE_GUI("zt_guiMakeMenu");

	return _zt_guiMakeMenuBase(nullptr, false);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeMenuBar(ztGuiItem *parent)
{
	ZT_PROFILE_GUI("zt_guiMakeMenuBar");

	return _zt_guiMakeMenuBase(parent, true);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppend(ztGuiItem *menu, const char *label, i32 id, void *user_data, ztSprite *icon)
{
	ZT_PROFILE_GUI("zt_guiMenuAppend");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);

	zt_assert(menu->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = menu->menu.item_count++;
	menu->menu.display[idx] = zt_stringMakeFrom(label, menu->gm->arena);
	menu->menu.ids[idx] = id;
	menu->menu.submenus[idx] = nullptr;
	menu->menu.user_datas[idx] = user_data;

	if (icon) {
		menu->menu.icons[idx] = zt_mallocStructArena(ztSprite, menu->gm->arena);
		*menu->menu.icons[idx] = *icon;
	}
	else {
		menu->menu.icons[idx] = nullptr;
	}

	_zt_guiMenuBestSize(menu, nullptr, nullptr, &menu->size, zt_guiItemGetTheme(menu), menu->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuAppendSubmenu(ztGuiItem *menu, const char *label, ztGuiItem *submenu, ztSprite *icon)
{
	ZT_PROFILE_GUI("zt_guiMenuAppendSubmenu");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);
	zt_assertReturnOnFail(submenu->type == ztGuiItemType_Menu);
	zt_assertReturnOnFail(menu->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = menu->menu.item_count++;
	menu->menu.display[idx] = zt_stringMakeFrom(label, menu->gm->arena);
	menu->menu.ids[idx] = ztInvalidID;
	menu->menu.submenus[idx] = submenu;
	menu->menu.user_datas[idx] = nullptr;

	//zt_guiItemReparent(submenu, menu);

	if (icon) {
		menu->menu.icons[idx] = zt_mallocStructArena(ztSprite, menu->gm->arena);
		*menu->menu.icons[idx] = *icon;
	}
	else {
		menu->menu.icons[idx] = nullptr;
	}

	_zt_guiMenuBestSize(menu, nullptr, nullptr, &menu->size, zt_guiItemGetTheme(menu), menu->functions.user_data);
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuPopupAtItem(ztGuiItem *menu, ztGuiItem *item, i32 align_flags, const ztVec2& offset)
{
	ZT_PROFILE_GUI("zt_guiMenuPopupAtItem");

	ztVec2 off = offset;
	if (zt_bitIsSet(align_flags, ztAlign_Left  )) off.x -= item->size.x / 2.f;
	if (zt_bitIsSet(align_flags, ztAlign_Right )) off.x += item->size.x / 2.f; 
	if (zt_bitIsSet(align_flags, ztAlign_Top   )) off.y += item->size.y / 2.f; 
	if (zt_bitIsSet(align_flags, ztAlign_Bottom)) off.y -= item->size.y / 2.f; 


	zt_guiMenuPopupAtPosition(menu, zt_guiItemPositionLocalToScreen(item, off));
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuPopupAtPosition(ztGuiItem *menu, const ztVec2& pos)
{
	ZT_PROFILE_GUI("zt_guiMenuPopupAtPosition");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu);

	_zt_guiMenuClose(menu);

	menu->state_flags |= zt_bit(ztGuiItemStates_Visible);
	menu->menu.just_opened = true;

	ztVec2 position = pos;
	position.x += menu->size.x / 2;
	position.y -= menu->size.y / 2;

	menu->pos = position;
	zt_guiItemBringToFront(menu);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiMenuGetSelected(ztGuiItem *menu, i32 *selected_id)
{
	ZT_PROFILE_GUI("zt_guiMenuGetSelected");

	zt_assertReturnValOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar, false);

	if (menu->menu.selected != -1) {
		if (menu->menu.submenus[menu->menu.selected] != nullptr) {
			return zt_guiMenuGetSelected(menu->menu.submenus[menu->menu.selected], selected_id);
		}
		*selected_id = menu->menu.ids[menu->menu.selected];
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

void zt_guiMenuSetCallback(ztGuiItem *menu, ztFunctionID on_selected)
{
	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);
	menu->menu.on_selected = on_selected;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTreeCalculateSize(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiTreeCalculateSize");

	ztGuiItem *content = item->tree.content;
	content->size = ztVec2::zero;

	struct local
	{
		static void hideAll(ztGuiItem::ztTreeItem *tree_entry)
		{
			ZT_PROFILE_GUI("_zt_guiTreeCalculateSize:hideAll");

			zt_guiItemHide(tree_entry->control_button);
			zt_guiItemHide(tree_entry->item);

			ztGuiItem::ztTreeItem *child = tree_entry->first_child;
			while (child) {
				hideAll(child);
				child = child->next;
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void addToSize(ztGuiItem::ztTreeItem *tree_entry, ztGuiTheme *theme, ztVec2 *size, r32 indent_size, int *shown_items)
		{
			ZT_PROFILE_GUI("_zt_guiTreeCalculateSize:addToSize");

			ztGuiItem *tree_item = tree_entry->item;

			if (tree_item->size.x + indent_size > size->x) {
				ztGuiItem *button = tree_entry->control_button;
				r32 icon_size = button->size.x;;
				size->x = tree_item->size.x + indent_size + icon_size + zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding) * 2;
			}

			size->y += tree_item->size.y;

			shown_items += 1;

			r32 tree_indent = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TreeIndent);
			if (tree_entry->expanded) {
				ztGuiItem::ztTreeItem *child = tree_entry->first_child;
				while (child) {
					addToSize(child, theme, size, indent_size + tree_indent, shown_items);
					child = child->next;
				}
			}
		}

		// ------------------------------------------------------------------------------------------------

		static void reposition(ztGuiItem::ztTreeItem *tree_entry, ztGuiTheme *theme, r32 x, r32* y, r32 w, r32 indent_size)
		{
			ZT_PROFILE_GUI("_zt_guiTreeCalculateSize:resposition");

			ztGuiItem *tree_item = tree_entry->item;

			tree_item->state_flags |= zt_bit(ztGuiItemStates_Visible);
			tree_item->pos.x = x + indent_size + (tree_item->size.x / 2);

			r32 tree_indent = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TreeIndent);
			ztVec2 size = tree_item->size;
			if (tree_entry->control_button != nullptr && tree_entry->first_child != nullptr) {
				ztGuiItem *button = tree_entry->control_button;
				//size.y = zt_max(size.y, button->size.y);

				button->state_flags |= zt_bit(ztGuiItemStates_Visible);
				button->pos.x = x + indent_size - tree_indent;
				button->pos.y = *y - size.y / 2;

				//tree_item->pos.x += button->size.x;
			}

			tree_item->pos.y = *y - size.y / 2;

			*y -= size.y;

			if (tree_entry->expanded) {
				ztGuiItem::ztTreeItem *child = tree_entry->first_child;
				while (child) {
					reposition(child, theme, x, y, w, indent_size + tree_indent);
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

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	child = item->tree.root_item->first_child;
	while (child) {
		local::addToSize(child, theme, &size, 0, &shown_items);
		child = child->next;
	}

	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding);
	size.y += padding * 2;

	r32 x = (padding * 2) + size.x / -2;
	r32 y = size.y / 2;
	r32 tree_indent = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TreeIndent);
	child = item->tree.root_item->first_child;
	while (child) {
		local::reposition(child, theme, x, &y, size.x, tree_indent);
		child = child->next;
	}

	content->size = size;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiTreeRecalc(ztGuiItem *tree)
{
	ZT_PROFILE_GUI("_zt_guiTreeRecalc");

	_zt_guiTreeCalculateSize(tree);

	ztGuiItem *container = tree->tree.container;
	container->size = tree->size;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiTreeUpdate))
{
	ZT_PROFILE_GUI("_zt_guiTreeUpdate");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized))) {
		_zt_guiTreeRecalc(item);
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiTreeRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiTreeCleanup))
{
	ZT_PROFILE_GUI("_zt_guiTreeCleanup");

	zt_freeArena(item->tree.arena, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItem::ztTreeItem *_zt_guiTreeMouseIntersecting(ztGuiItem::ztTreeItem *root, ztVec2& mpos, ztVec2& pos, ztVec2& size)
{
	ZT_PROFILE_GUI("_zt_guiTreeMouseIntersecting");

	if (root->item != nullptr) {
		ztGuiItem *item = root->item;

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
		ztGuiItem::ztTreeItem *intersecting = _zt_guiTreeMouseIntersecting(child, mpos, pos, size);
		if (intersecting) {
			return intersecting;
		}
		child = child->next;
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiTreeInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiTreeInputMouse");

	if (input_mouse->leftJustReleased() && item->tree.root_item->first_child) {
		ztVec2 mpos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		ztVec2 pos = zt_guiItemPositionLocalToScreen(item->tree.content, ztVec2::zero);

		ztGuiItem *first_item = item->tree.root_item->first_child->item;

		ztGuiItem *content = item->tree.content;
		pos.y += content->size.y / 2.f - first_item->size.y / 2.f;
		pos.x -= (content->size.x - item->size.x) / 2.f;

		ztVec2 size(item->size.x, 0);
		ztGuiItem::ztTreeItem *intersecting = _zt_guiTreeMouseIntersecting(item->tree.root_item, mpos, pos, size);
		if (intersecting) {
			if (item->tree.active_item != intersecting) {
				item->tree.active_item = intersecting;
				if (item->tree.on_item_sel != ztInvalidID) {
					((zt_guiTreeItemSelected_Func*)zt_functionPointer(item->tree.on_item_sel))(item, intersecting->node_id, item->tree.on_item_sel_user_data);
				}
			}
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiTreeBestSize))
{
}
// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeTree(ztGuiItem *parent, i32 max_items)
{
	ZT_PROFILE_GUI("zt_guiMakeTree");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Tree, ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_ClipContents);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->tree.container = zt_guiMakeScrollContainer(item, ztGuiScrollContainerBehaviorFlags_NoBackground);
	item->tree.content = zt_guiMakePanel(parent, 0);
	zt_guiScrollContainerSetItem(item->tree.container, item->tree.content);

	item->tree.arena = zt_memMakeArena(max_items * zt_sizeof(ztGuiItem::ztTreeItem), item->gm->arena);
	item->tree.last_id = -1;
	item->tree.on_item_sel = ztInvalidID;

	item->tree.root_item = zt_mallocStructArena(ztGuiItem::ztTreeItem, item->tree.arena);
	zt_memSet(item->tree.root_item, zt_sizeof(ztGuiItem::ztTreeItem), 0);
	item->tree.root_item->expanded = true;
	item->tree.root_item->node_id = ++item->tree.last_id;
	item->tree.root_item->item = nullptr;
	item->tree.root_item->control_button = nullptr;

	item->functions.cleanup     = _zt_guiTreeCleanup_FunctionID;
	item->functions.update      = _zt_guiTreeUpdate_FunctionID;
	item->functions.input_mouse = _zt_guiTreeInputMouse_FunctionID;
	item->functions.render      = _zt_guiTreeRender_FunctionID;
	item->functions.best_size   = _zt_guiTreeBestSize_FunctionID;

	ztVec2 min_size;
	_zt_guiTreeBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItem *tree, const char *item_label, void *user_data, ztGuiTreeNodeID parent_id)
{
	ZT_PROFILE_GUI("zt_guiTreeAppend");

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);

	ztGuiItem *item = zt_guiMakeStaticText(tree->tree.content, item_label);
	return zt_guiTreeAppend(tree, item, user_data, parent_id);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem::ztTreeItem *_zt_guiTreeFindNode(ztGuiItem *tree, ztGuiItem::ztTreeItem *root, ztGuiTreeNodeID node_id)
{
	ZT_PROFILE_GUI("_zt_guiTreeFindNode");

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

ztInternal bool _zt_guiTreeToggleItem(ztGuiItem *tree, ztGuiItem::ztTreeItem *root, ztGuiItem *button)
{
	ZT_PROFILE_GUI("_zt_guiTreeToggleItem");

	if (root->control_button && root->control_button == button) {
		root->expanded = !root->expanded;
		tree->state_flags |= zt_bit(ztGuiItemStates_Dirty);

		ztGuiTheme *theme = zt_guiItemGetTheme(button);
		zt_guiThemeUpdateSubitem(theme, tree, button, (void*)&root->expanded);
		_zt_guiTreeRecalc(tree);
		return true;
	}
	else {
		ztGuiItem::ztTreeItem *child = root->first_child;
		while (child) {
			if (_zt_guiTreeToggleItem(tree, child, button)) {
				return true;
			}
			child = child->next;
		}
		return false;
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeOnToggle, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiTreeOnToggle))
{
	ZT_PROFILE_GUI("_zt_guiTreeOnToggle");

	ztGuiItem *tree = (ztGuiItem*)user_data;
	_zt_guiTreeToggleItem(tree, tree->tree.root_item, button);
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItem *tree, ztGuiItem *item, void *user_data, ztGuiTreeNodeID parent_id)
{
	ZT_PROFILE_GUI("zt_guiTreeAppend");

	struct local
	{
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
			
			tree_item->control_button = zt_guiMakeButton(tree->tree.content, nullptr, zt_guiThemeGetIValue(zt_guiItemGetTheme(tree), ztGuiThemeValue_i32_TreeCollapseButtonBehaviorFlags));
	
			ztGuiTheme *theme = zt_guiItemGetTheme(tree);
			zt_guiThemeUpdateSubitem(theme, tree, tree_item->control_button);
			zt_guiButtonSetCallback(tree_item->control_button, _zt_guiTreeOnToggle_FunctionID, tree);

			zt_singleLinkAddToEnd(root->first_child, tree_item);

			return tree_item;
		}
	};

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);

	zt_guiItemReparent(item, tree->tree.content);

	ztGuiItem::ztTreeItem *tree_item = local::appendItem(tree, tree->tree.root_item, parent_id);
	if (tree_item == nullptr) {
		return ztInvalidID;
	}

	tree_item->item = item;
	tree_item->user_data = user_data;

	if (!zt_bitIsSet(tree->state_flags, zt_bit(ztGuiItemStates_Locked))) {
		_zt_guiTreeCalculateSize(tree);
	}

	return tree_item->node_id;
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeGetSelected(ztGuiItem *tree)
{
	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);
	return tree->tree.active_item ? tree->tree.active_item->node_id : ztInvalidID;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTreeSetSelected(ztGuiItem *tree, ztGuiTreeNodeID node)
{
	ZT_PROFILE_GUI("zt_guiTreeSetSelected");

	struct local
	{
		static bool findAndSelect(ztGuiItem *tree, ztGuiItem::ztTreeItem *tree_item, ztGuiTreeNodeID node)
		{
			if (tree_item->node_id == node) {
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
	zt_assertReturnOnFail(tree->type == ztGuiItemType_Tree);
	local::findAndSelect(tree, tree->tree.root_item, node);
}

// ------------------------------------------------------------------------------------------------

ztGuiTreeNodeID zt_guiTreeGetRoot(ztGuiItem *tree)
{
	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);
	return 0;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiTreeGetNodeItem(ztGuiItem *tree, ztGuiTreeNodeID node)
{
	ZT_PROFILE_GUI("zt_guiTreeGetNodeItem");

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, nullptr);

	ztGuiItem::ztTreeItem *tree_item = _zt_guiTreeFindNode(tree, tree->tree.root_item, node);
	return tree_item ? tree_item->item : nullptr;
}

// ------------------------------------------------------------------------------------------------

void *zt_guiTreeGetNodeUserData(ztGuiItem *tree, ztGuiTreeNodeID node)
{
	ZT_PROFILE_GUI("zt_guiTreeGetNodeUserData");

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, nullptr);

	ztGuiItem::ztTreeItem *tree_item = _zt_guiTreeFindNode(tree, tree->tree.root_item, node);
	return tree_item ? tree_item->user_data : nullptr;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTreeSetCallback(ztGuiItem *tree, ztFunctionID on_item_sel, void *user_data)
{
	zt_assertReturnOnFail(tree->type == ztGuiItemType_Tree);

	tree->tree.on_item_sel           = on_item_sel;
	tree->tree.on_item_sel_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

void zt_guiTreeClear(ztGuiItem *tree)
{
	ZT_PROFILE_GUI("zt_guiTreeClear");

	zt_assertReturnOnFail(tree->type == ztGuiItemType_Tree);

	struct local
	{
		static void clear(ztMemoryArena *arena, ztGuiItem::ztTreeItem *tree_item)
		{
			if (tree_item->control_button != nullptr) {
				zt_guiItemFree(tree_item->control_button);
				tree_item->control_button = nullptr;
			}
			if (tree_item->item != nullptr) {
				zt_guiItemFree(tree_item->item);
				tree_item->item = nullptr;
			}

			ztGuiItem::ztTreeItem *child = tree_item->first_child;
			while (child) {
				ztGuiItem::ztTreeItem *next = child->next;
				clear(arena, child);
				child = next;
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
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiComboBoxRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiComboBoxCleanup))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxCleanup");

	if (item->combobox.popup != nullptr) {
		zt_guiItemFree(item->combobox.popup);
	}

	zt_fiz(item->combobox.contents_size) {
		zt_stringFree(item->combobox.contents[i], item->gm->arena);
	}
	zt_freeArena(item->combobox.contents, item->gm->arena);
	zt_freeArena(item->combobox.contents_user_data, item->gm->arena);
	item->combobox.contents_size = item->combobox.contents_count = -1;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiComboBoxInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxInputMouse");

	if (input_mouse->leftJustPressed()) {
		if (item->combobox.popup && zt_guiItemIsVisible(item->combobox.popup)) {
			item->state_flags |= zt_bit(ztGuiComboBoxInternalStates_IgnorePopup);
		}
	}
	else if (input_mouse->leftJustReleased()) {
		if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiComboBoxInternalStates_IgnorePopup))) {
			if (item->combobox.popup != nullptr) {
				ztGuiItem *menu = item->combobox.popup;
				menu->size.x = item->size.x;

				zt_guiMenuPopupAtItem(item->combobox.popup, item, ztAlign_Left | ztAlign_Bottom);
			}
		}
		else zt_bitRemove(item->state_flags, zt_bit(ztGuiComboBoxInternalStates_IgnorePopup));
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxInputKey, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiComboBoxInputKey))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxInputKey");

	if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
		if (item->combobox.selected > 0) {
			item->combobox.selected -= 1;
			if (item->combobox.on_selected != ztInvalidID) {
				((zt_guiComboBoxItemSelected_Func*)zt_functionPointer(item->combobox.on_selected))(item, item->combobox.selected, item->combobox.on_selected_user_data);
			}
		}
	}
	if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
		if (item->combobox.selected < item->combobox.contents_count - 1) {
			item->combobox.selected += 1;
			if (item->combobox.on_selected != ztInvalidID) {
				((zt_guiComboBoxItemSelected_Func*)zt_functionPointer(item->combobox.on_selected))(item, item->combobox.selected, item->combobox.on_selected_user_data);
			}
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiComboBoxBestSize))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeComboBox(ztGuiItem *parent, i32 max_items)
{
	ZT_PROFILE_GUI("zt_guiMakeComboBox");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_ComboBox, ztGuiItemBehaviorFlags_WantsFocus);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->combobox.popup                 = nullptr;
	item->combobox.contents              = zt_mallocStructArrayArena(ztString, max_items, item->gm->arena);
	item->combobox.contents_user_data    = zt_mallocStructArrayArena(void*, max_items, item->gm->arena);
	item->combobox.contents_size         = max_items;
	item->combobox.contents_count        = 0;
	item->combobox.on_selected           = ztInvalidID;
	item->combobox.on_selected_user_data = nullptr;

	zt_fiz(max_items) {
		item->combobox.contents[i] = zt_stringMake(128, item->gm->arena);
		item->combobox.contents[i][0] = 0;
		item->combobox.contents_user_data[i] = nullptr;
	}

	item->combobox.selected = 0;


	item->functions.cleanup     = _zt_guiComboBoxCleanup_FunctionID;
	item->functions.input_mouse = _zt_guiComboBoxInputMouse_FunctionID;
	item->functions.input_key   = _zt_guiComboBoxInputKey_FunctionID;
	item->functions.render      = _zt_guiComboBoxRender_FunctionID;
	item->functions.best_size   = _zt_guiComboBoxBestSize_FunctionID;

	ztVec2 min_size;
	_zt_guiComboBoxBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxMenuSelected, ztInternal ZT_FUNC_GUI_MENU_SELECTED(_zt_guiComboBoxMenuSelected))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxMenuSelected");

	ztGuiItem *combo = (ztGuiItem*)user_data;
	combo->combobox.selected = menu_item;

	if (combo->combobox.on_selected != ztInvalidID) {
		((zt_guiComboBoxItemSelected_Func*)zt_functionPointer(combo->combobox.on_selected))(combo, combo->combobox.selected, combo->combobox.on_selected_user_data);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxSetContents(ztGuiItem *combobox, const char **contents, int contents_count, int active)
{
	ZT_PROFILE_GUI("zt_guiComboBoxSetContents");

	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);

	if (combobox->combobox.popup != nullptr) {
		zt_guiItemFree(combobox->combobox.popup);
	}
	combobox->combobox.popup = zt_guiMakeMenu();
	zt_guiMenuSetCallback(combobox->combobox.popup, _zt_guiComboBoxMenuSelected_FunctionID);

	combobox->combobox.contents_count = zt_min(contents_count, combobox->combobox.contents_size);
	zt_fiz(combobox->combobox.contents_count) {
		zt_stringOverwrite(combobox->combobox.contents[i], contents[i], combobox->gm->arena);

		zt_guiMenuAppend(combobox->combobox.popup, contents[i], i, combobox);
	}

	combobox->combobox.selected = zt_clamp(active, 0, combobox->combobox.contents_count - 1);
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxClear(ztGuiItem *combobox)
{
	ZT_PROFILE_GUI("zt_guiComboBoxClear");

	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	combobox->combobox.contents_count = 0;
	combobox->combobox.selected = -1;

	if (combobox->combobox.popup != nullptr) {
		zt_guiItemFree(combobox->combobox.popup);
		combobox->combobox.popup = nullptr;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxAppend(ztGuiItem *combobox, const char *content, void *user_data)
{
	ZT_PROFILE_GUI("zt_guiComboBoxAppend");

	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	zt_assertReturnOnFail(combobox->combobox.contents_count < combobox->combobox.contents_size);

	if (combobox->combobox.contents_count == 0) {
		if (combobox->combobox.popup != nullptr) {
			zt_guiItemFree(combobox->combobox.popup);
		}
		combobox->combobox.popup = zt_guiMakeMenu();
		zt_guiMenuSetCallback(combobox->combobox.popup, _zt_guiComboBoxMenuSelected_FunctionID);
		combobox->combobox.selected = 0;
	}
	
	int idx = combobox->combobox.contents_count;
	combobox->combobox.contents_count += 1;

	zt_stringOverwrite(combobox->combobox.contents[idx], content, combobox->gm->arena);
	combobox->combobox.contents_user_data[idx] = user_data;
	zt_guiMenuAppend(combobox->combobox.popup, content, idx, combobox);
}

// ------------------------------------------------------------------------------------------------

int zt_guiComboBoxGetSelected(ztGuiItem *combobox)
{
	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, -1);
	return combobox->combobox.selected;
}

// ------------------------------------------------------------------------------------------------

int zt_guiComboBoxGetItemCount(ztGuiItem *combobox)
{
	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, 0);
	return combobox->combobox.contents_count;
}

// ------------------------------------------------------------------------------------------------

int zt_guiComboBoxGetItemText(ztGuiItem *combobox, int index, char* buffer, int buffer_len)
{
	ZT_PROFILE_GUI("zt_guiComboBoxGetItemText");

	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, 0);
	if (index >= 0 && index < combobox->combobox.contents_count) {
		return zt_strCpy(buffer, buffer_len, combobox->combobox.contents[index]);
	}
	return 0;
}

// ------------------------------------------------------------------------------------------------

void *zt_guiComboBoxGetItemUserData(ztGuiItem *combobox, int index)
{
	ZT_PROFILE_GUI("zt_guiComboBoxGetItemUserData");

	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, nullptr);
	if (index >= 0 && index < combobox->combobox.contents_count) {
		return combobox->combobox.contents_user_data[index];
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

void zt_guiComboBoxSetCallback(ztGuiItem *combobox, ztFunctionID on_item_sel, void *user_data)
{
	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	combobox->combobox.on_selected = on_item_sel;
	combobox->combobox.on_selected_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpriteDisplayRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiSpriteDisplayRender))
{
	ZT_PROFILE_GUI("_zt_guiSpriteDisplayRender");

	ztVec2 pos = offset + item->pos;

	zt_drawListAddGuiThemeSprite(draw_list, item->sprite_display.sprite, pos, item->size);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpriteDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiSpriteDisplayCleanup))
{
	ZT_PROFILE_GUI("_zt_guiSpriteDisplayCleanup");

	zt_freeArena(item->sprite_display.sprite, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpriteDisplayBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiSpriteDisplayBestSize))
{
	ZT_PROFILE_GUI("_zt_guiSpriteDisplayBestSize");

	*size = zt_guiThemeSpriteGetSize(item->sprite_display.sprite) * ztVec2(item->sprite_display.scale[0], item->sprite_display.scale[1]);
}
// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeSpriteDisplay(ztGuiItem *parent, ztGuiThemeSprite *sprite)
{
	ZT_PROFILE_GUI("zt_guiMakeSpriteDisplay");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_SpriteDisplay, ztGuiItemBehaviorFlags_WantsFocus);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->sprite_display.sprite = zt_mallocStructArena(ztGuiThemeSprite, item->gm->arena);
	if (sprite) {
		*item->sprite_display.sprite = *sprite;
	}
	else {
		item->sprite_display.sprite->type = ztGuiThemeSpriteType_Invalid;
	}
	item->sprite_display.scale[0] = item->sprite_display.scale[1] = 1;


	item->functions.render    = _zt_guiSpriteDisplayRender_FunctionID;
	item->functions.cleanup   = _zt_guiSpriteDisplayCleanup_FunctionID;
	item->functions.best_size = _zt_guiSpriteDisplayBestSize_FunctionID;

	ztVec2 min_size;
	_zt_guiSpriteDisplayBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSpriteDisplaySetSprite(ztGuiItem *item, ztGuiThemeSprite *sprite, const ztVec2& scale)
{
	zt_assertReturnOnFail(item->type == ztGuiItemType_SpriteDisplay);
	*item->sprite_display.sprite = *sprite;
	item->sprite_display.scale[0] = scale.x;
	item->sprite_display.scale[1] = scale.y;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpinnerUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiSpinnerUpdate))
{
	if (item->gm->item_has_mouse == item) {
		item->spinner.time += dt;
	}
	else if (item->spinner.value != 0) {
		item->spinner.value = 0;
		if (item->spinner.live_value) {
			*item->spinner.live_value = 0;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpinnerRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiSpinnerRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpinnerInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiSpinnerInputMouse))
{
	if (input_mouse->leftPressed()) {
		ztVec2 mpos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		if (input_mouse->leftJustPressed()) {
			ztVec2 pos = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
			item->spinner.start[0] = pos.x;
			item->spinner.start[1] = pos.y;

			item->spinner.time = ztReal32Max; // so we pop off immediately
		}

		ztVec2 viewport = zt_cameraOrthoGetViewportSize(item->gm->gui_camera);
		r32 diff_x = mpos.x - item->spinner.start[0];
		r32 diff_y = mpos.y - item->spinner.start[1];
		r32 diff = zt_max(zt_abs(diff_x), zt_abs(diff_y));
		r32 percent = zt_clamp(diff / (zt_min(viewport.x, viewport.y) / 4), 0, 1);
		r32 threshold = zt_clamp(.5f * (1 - percent), .025f, 1);

		if (item->spinner.time >= threshold) {
			int dir = 1;

			if (zt_abs(diff_x) > zt_abs(diff_y)) {
				if (diff_x < 0) {
					dir = -1;
				}
			}
			else {
				if (diff_y < 0) {
					dir = -1;
				}
			}

			item->spinner.value = dir;
			item->spinner.time = 0;
			item->spinner.last_dir = dir;

			if (item->spinner.on_value_changed != ztInvalidID) {
				((zt_guiSpinnerValueChanged_Func*)zt_functionPointer(item->spinner.on_value_changed))(item, dir, item->spinner.on_value_changed_user_data);
			}
		}
		else {
			item->spinner.value = false;
		}

		if (item->spinner.live_value) {
			*item->spinner.live_value = item->spinner.value;
		}

		return true;
	}
	else {
		item->spinner.time = 0;
	}
	return false;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeSpinner(ztGuiItem *parent, int *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeSpinner");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Spinner, ztGuiItemBehaviorFlags_WantsFocus);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->spinner.live_value = live_value;
	item->spinner.start[0] = 0;
	item->spinner.start[1] = 0;
	item->spinner.time = 0;
	item->spinner.on_value_changed = ztInvalidID;

	item->functions.update = _zt_guiSpinnerUpdate_FunctionID;
	item->functions.render = _zt_guiSpinnerRender_FunctionID;
	item->functions.input_mouse = _zt_guiSpinnerInputMouse_FunctionID;

	zt_guiThemeSizeItem(theme, item);

	return item;
}

// ------------------------------------------------------------------------------------------------

int zt_guiSpinnerGetValue(ztGuiItem *spinner)
{
	zt_assertReturnValOnFail(spinner->type == ztGuiItemType_Spinner, 0);
	return spinner->spinner.value;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSpinnerSetCallback(ztGuiItem *spinner, ztFunctionID on_value_changed, void *user_data)
{
	zt_assertReturnOnFail(spinner->type == ztGuiItemType_Spinner);
	spinner->spinner.on_value_changed = on_value_changed;
	spinner->spinner.on_value_changed_user_data = user_data;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSpinnerTickUp(ztGuiItem *spinner)
{
	zt_assertReturnOnFail(spinner->type == ztGuiItemType_Spinner);

	spinner->spinner.value = 1;
	spinner->spinner.time = 0;
	spinner->spinner.last_dir = 1;

	if (spinner->spinner.on_value_changed != ztInvalidID) {
		((zt_guiSpinnerValueChanged_Func*)zt_functionPointer(spinner->spinner.on_value_changed))(spinner, spinner->spinner.last_dir, spinner->spinner.on_value_changed_user_data);
	}

	if (spinner->spinner.live_value) {
		*spinner->spinner.live_value = spinner->spinner.value;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSpinnerTickDown(ztGuiItem *spinner)
{
	zt_assertReturnOnFail(spinner->type == ztGuiItemType_Spinner);

	spinner->spinner.value = -1;
	spinner->spinner.time = 0;
	spinner->spinner.last_dir = 1;

	if (spinner->spinner.on_value_changed != ztInvalidID) {
		((zt_guiSpinnerValueChanged_Func*)zt_functionPointer(spinner->spinner.on_value_changed))(spinner, spinner->spinner.last_dir, spinner->spinner.on_value_changed_user_data);
	}

	if (spinner->spinner.live_value) {
		*spinner->spinner.live_value = spinner->spinner.value;
	}
}

// ------------------------------------------------------------------------------------------------

enum ztGuiEditorType_Enum
{
	ztGuiEditorType_r32,
	ztGuiEditorType_i32,
};

struct ztGuiEditorValue
{
	ztGuiEditorType_Enum type;
	bool                 needs_update_from_spinner;
	bool                 needs_update_from_editor;

	union {
		struct {
			r32 *value;
			r32  min;
			r32  max;
			r32  step;
		} val_r32;

		struct {
			i32 *value;
			i32  min;
			i32  max;
			i32  step;
		} val_i32;
	};

	ztGuiItem *editor;
	ztGuiItem *text_edit;
	ztGuiItem *spinner;
};

#define ztGuiEditorFirstChildName       "editor"
#define ztGuiEditorFirstChildNameVec2   "editor-vec2"
#define ztGuiEditorFirstChildNameVec3   "editor-vec3"
#define ztGuiEditorFirstChildNameVec4   "editor-vec4"

#define ztGuiEditor_Guid                zt_guidMake(0x4787c0e7, 0x2c9d61aa, 0xc7f1dc78, 0x8776b714)


// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiEditorUpdate))
{
	// item is the panel
	ztGuiEditorValue *vptr = (ztGuiEditorValue*)item->panel.user_data;

	if (vptr->needs_update_from_editor) {
		vptr->needs_update_from_editor = false;
		vptr->needs_update_from_spinner = true;

		char buffer[128];
		zt_guiTextEditGetValue(vptr->text_edit, buffer, zt_elementsOf(buffer));

		if (vptr->type == ztGuiEditorType_i32) {
			if (vptr->val_i32.value == nullptr) return;
			*vptr->val_i32.value = zt_strToInt(buffer, 0);
		}
		else if (vptr->type == ztGuiEditorType_r32) {
			if (vptr->val_r32.value == nullptr) return;
			*vptr->val_r32.value = zt_strToReal32(buffer, 0);
		}
	}
	if (vptr->needs_update_from_spinner) {
		vptr->needs_update_from_spinner = false;

		char buffer[32] = { 0 };
		if (vptr->type == ztGuiEditorType_i32) {
			if (vptr->val_i32.value == nullptr) return;
			zt_strPrintf(buffer, zt_elementsOf(buffer), "%d", *vptr->val_i32.value);
		}
		else if (vptr->type == ztGuiEditorType_r32) {
			if (vptr->val_r32.value == nullptr) return;
			zt_strPrintf(buffer, zt_elementsOf(buffer), "%.4f", *vptr->val_r32.value);

			if (zt_strFind(buffer, ".")) {	// let's remove any trailing zeros
				int len = zt_strLen(buffer);
				zt_fizr(len - 1) {
					if (buffer[i] == '0') {
						buffer[i] = 0;
					}
					else if (buffer[i] == '.') {
						buffer[i] = 0;
						break;
					}
					else break;
				}
			}
		}

		zt_guiTextEditSetValue(vptr->text_edit, buffer);
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorTextChange, ZT_FUNC_GUI_TEXTEDIT_KEY(_zt_guiEditorTextChange))
{
	ztGuiEditorValue *vptr = (ztGuiEditorValue*)user_data;

	zt_fize(input_key_strokes) {
		if (input_key_strokes[i] == ztInputKeys_Invalid) {
			break;
		}
		if (input_key_strokes[i] == ztInputKeys_Return) {
			vptr->needs_update_from_editor = true;

			if (input_keys[ztInputKeys_Control].pressed()) {
				if (vptr->editor->parent) {
					zt_flinknext(child, vptr->editor->parent->first_child, sib_next) {
						if (child != vptr->editor && child->type == ztGuiItemType_Panel && child->panel.guid == ztGuiEditor_Guid) {
							ztGuiEditorValue *vptr2 = (ztGuiEditorValue*)child->panel.user_data;
							char copy[1024];
							zt_guiTextEditGetValue(textedit, copy, zt_elementsOf(copy));
							zt_guiTextEditSetValue(vptr2->text_edit, copy);
							vptr2->needs_update_from_editor = true;
						}
					}
				}
			}

			break;
		}
		if (input_key_strokes[i] == ztInputKeys_Back || input_key_strokes[i] == ztInputKeys_Delete){
			continue;
		}

		if (input_key_strokes[i] == ztInputKeys_Up) {
			zt_guiSpinnerTickUp(vptr->spinner);
		}
		else if (input_key_strokes[i] == ztInputKeys_Down) {
			zt_guiSpinnerTickDown(vptr->spinner);
		}

		char display = input_keys[input_key_strokes[i]].display;

		switch (display)
		{
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				break;

			case '-':
				break;

			case '.':
				if (vptr->type == ztGuiEditorType_r32) {
					*should_process = zt_strFind(textedit->textedit.text_buffer, ".") == nullptr;
				}
				else {
					*should_process = false;
				}
				break;

			case 0:
				break;

			default:
				*should_process = false;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorSpinnerChanged, ZT_FUNC_GUI_SPINNER_VALUE_CHANGED(_zt_guiEditorSpinnerChanged))
{
	ztGuiEditorValue *vptr = (ztGuiEditorValue*)user_data;

	if (vptr->type == ztGuiEditorType_r32) {
		if (vptr->val_r32.value == nullptr) return;
		*vptr->val_r32.value = zt_clamp(*vptr->val_r32.value + (vptr->val_r32.step * value), vptr->val_r32.min, vptr->val_r32.max);
	}
	else if (vptr->type == ztGuiEditorType_i32) {
		if (vptr->val_i32.value == nullptr) return;
		*vptr->val_i32.value = zt_clamp(*vptr->val_i32.value + (vptr->val_i32.step * value), vptr->val_i32.min, vptr->val_i32.max);
	}

	vptr->needs_update_from_spinner = true;

	if (spinner->gm->key_state_ctrl) {
		if (vptr->editor->parent) {
			zt_flinknext(child, vptr->editor->parent->first_child, sib_next) {
				if (child != vptr->editor && child->type == ztGuiItemType_Panel && child->panel.guid == ztGuiEditor_Guid) {
					ztGuiEditorValue *vptr2 = (ztGuiEditorValue*)child->panel.user_data;

					if (vptr2->type == ztGuiEditorType_r32) {
						*vptr2->val_r32.value = *vptr->val_r32.value;
					}
					else if (vptr2->type == ztGuiEditorType_i32) {
						*vptr2->val_i32.value = *vptr->val_i32.value;
					}

					vptr2->needs_update_from_spinner = true;
				}
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal ztGuiItem *_zt_guiEditorMakeBase(ztGuiItem *parent, const char *label, ztGuiEditorValue *value)
{
	ztGuiItem *panel = zt_guiMakePanel(parent, 0, value, parent->gm->arena);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz);
	zt_guiSizerSizeToParent(sizer);

	zt_guiItemSetName(sizer, ztGuiEditorFirstChildName);

	panel->functions.update = _zt_guiEditorUpdate_FunctionID;
	panel->panel.guid = ztGuiEditor_Guid;

	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, 0);
		zt_guiSizerAddStretcher(sizer, 0, zt_guiThemeGetRValue(zt_guiItemGetTheme(parent), ztGuiThemeValue_r32_Padding));
	}


	char val_str[32] = "0";
	ztGuiItem *text = zt_guiMakeTextEdit(sizer, val_str, 0, 32);
	zt_guiTextEditSetCallback(text, _zt_guiEditorTextChange_FunctionID, value); // todo: need user data on this callback

	zt_guiSizerAddItem(sizer, text, 1, 0);

	ztGuiItem *spinner = zt_guiMakeSpinner(sizer);
	zt_guiSpinnerSetCallback(spinner, _zt_guiEditorSpinnerChanged_FunctionID, value);

	zt_guiSizerAddItem(sizer, spinner, 0, 0);

	panel->size = zt_guiSizerGetMinSize(sizer);

	value->editor = panel;
	value->text_edit = text;
	value->spinner = spinner;
	value->needs_update_from_spinner = true;
	value->needs_update_from_editor = false;

	return panel;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, r32 *value, r32 min, r32 max, r32 step)
{
	ztGuiEditorValue *val = zt_mallocStructArena(ztGuiEditorValue, parent->gm->arena);
	val->type = ztGuiEditorType_r32;
	val->val_r32.value = value;
	val->val_r32.min = min;
	val->val_r32.max = max;
	val->val_r32.step = step;

	return _zt_guiEditorMakeBase(parent, label, val);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, i32 *value, i32 min, i32 max, i32 step)
{
	ztGuiEditorValue *val = zt_mallocStructArena(ztGuiEditorValue, parent->gm->arena);
	val->type = ztGuiEditorType_i32;
	val->val_i32.value = value;
	val->val_i32.min = min;
	val->val_i32.max = max;
	val->val_i32.step = step;
	return _zt_guiEditorMakeBase(parent, label, val);
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec2 *value, ztVec2 min, ztVec2 max, r32 step, bool label_above, char *label_x, char *label_y)
{
	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec2);

	r32 padding = 1 / zt_pixelsPerUnit();
	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, padding, ztAlign_Center, ztGuiItemOrient_Horz);

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, padding);

	char * labels[] = { label_x, label_y };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		editor->size.y = 25 / zt_pixelsPerUnit();
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	return panel;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec3 *value, ztVec3 min, ztVec3 max, r32 step, bool label_above, char *label_x, char *label_y, char *label_z)
{
	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, label_above ? ztGuiItemOrient_Vert : ztGuiItemOrient_Horz);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec3);

	r32 padding = 3 / zt_pixelsPerUnit();
	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, padding, ztAlign_Center, ztGuiItemOrient_Horz);

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, padding);

	char * labels[] = { label_x, label_y, label_z };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		editor->size.y = 25 / zt_pixelsPerUnit();
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	return panel;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec4 *value, ztVec4 min, ztVec4 max, r32 step, bool label_above, char *label_x, char *label_y, char *label_z, char *label_w)
{
	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec4);

	r32 padding = 3 / zt_pixelsPerUnit();
	zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, padding, ztAlign_Center, ztGuiItemOrient_Horz);

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, padding);

	char * labels[] = { label_x, label_y, label_z, label_w };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		editor->size.y = 25 / zt_pixelsPerUnit();

		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	return panel;
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToMin(ztGuiItem *editor)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		if (vptr->type == ztGuiEditorType_i32) {
			*vptr->val_i32.value = vptr->val_i32.min;
		}
		else if (vptr->type == ztGuiEditorType_r32) {
			*vptr->val_r32.value = vptr->val_r32.min;
		}
		vptr->needs_update_from_spinner = true;
	}
	else {
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_guiEditorSetToMin(edit);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToMax(ztGuiItem *editor)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		if (vptr->type == ztGuiEditorType_i32) {
			*vptr->val_i32.value = vptr->val_i32.min;
		}
		else if (vptr->type == ztGuiEditorType_r32) {
			*vptr->val_r32.value = vptr->val_r32.min;
		}
		vptr->needs_update_from_spinner = true;
	}
	else {
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_guiEditorSetToMax(edit);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToValue(ztGuiItem *editor, r32 value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		if (vptr->type == ztGuiEditorType_r32) {
			*vptr->val_r32.value = value;
			return;
		}
		vptr->needs_update_from_spinner = true;
	}

	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToValue(ztGuiItem *editor, i32 value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		if (vptr->type == ztGuiEditorType_i32) {
			*vptr->val_i32.value = value;
			return;
		}
	}

	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec2 value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec2)) {	
		int editor_idx = 0;
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_assert(editor_idx < zt_elementsOf(value.values));
				zt_guiEditorSetToValue(edit, value.values[editor_idx++]);
			}
		}
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec3 value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec3)) {
		int editor_idx = 0;
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_assert(editor_idx < zt_elementsOf(value.values));
				zt_guiEditorSetToValue(edit, value.values[editor_idx++]);
			}
		}
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec4 value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec4)) {
		int editor_idx = 0;
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_assert(editor_idx < zt_elementsOf(value.values));
				zt_guiEditorSetToValue(edit, value.values[editor_idx++]);
			}
		}
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorReassign(ztGuiItem *editor, r32 *value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		vptr->needs_update_from_spinner = true;
		if (vptr->type == ztGuiEditorType_r32) {
			vptr->val_r32.value = value;
			return;
		}
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorReassign(ztGuiItem *editor, i32 *value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		vptr->needs_update_from_spinner = true;
		if (vptr->type == ztGuiEditorType_i32) {
			vptr->val_i32.value = value;
			return;
		}
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorReassign(ztGuiItem *editor, ztVec2 *value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec2)) {
		int editor_idx = 0;
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_assert(editor_idx < zt_elementsOf(value->values));
				if (value == nullptr) {
					zt_guiEditorReassign(edit, (r32*)nullptr);
				}
				else {
					zt_guiEditorReassign(edit, &value->values[editor_idx++]);
				}
			}
		}
		return;
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorReassign(ztGuiItem *editor, ztVec3 *value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec3)) {
		int editor_idx = 0;
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_assert(editor_idx < zt_elementsOf(value->values));
				if(value == nullptr) {
					zt_guiEditorReassign(edit, (r32*)nullptr);
				}
				else {
					zt_guiEditorReassign(edit, &value->values[editor_idx++]);
				}
			}
		}
		return;
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

void zt_guiEditorReassign(ztGuiItem *editor, ztVec4 *value)
{
	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec4)) {
		int editor_idx = 0;
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_assert(editor_idx < zt_elementsOf(value->values));
				if (value == nullptr) {
					zt_guiEditorReassign(edit, (r32*)nullptr);
				}
				else {
					zt_guiEditorReassign(edit, &value->values[editor_idx++]);
				}
			}
		}
		return;
	}
	zt_assert(false); // wrong editor type
}

// ------------------------------------------------------------------------------------------------

ztInternal ztVec2 _zt_guiSizerMinSize(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSizerMinSize");

	ztVec2 min_size = ztVec2::zero;

	if (item->sizer.type == ztGuiSizerType_Normal) {
		bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

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
	}
	else if (item->sizer.type == ztGuiSizerType_Column) {
		zt_linkGetCount(items_count, item->sizer.items);

		int items_per_column = zt_convertToi32Ceil(items_count / (r32)item->sizer.columns);

		ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;

		zt_fxz(item->sizer.columns) {
			ztVec2 column_min = ztVec2::zero;

			int items_this_col = 0;
			while (entry && items_this_col++ < items_per_column) {
				ztVec2 size = entry->item->size;
				if (entry->item->type == ztGuiItemType_Sizer) {
					size = _zt_guiSizerMinSize(entry->item);
				}

				column_min.x  = zt_max(column_min.x, size.x + entry->padding * 2);
				column_min.y += size.y + entry->padding * 2;

				entry = entry->next;
			}

			min_size.x += column_min.x;
			min_size.y = zt_max(min_size.y, column_min.y);
		}
	}

	min_size.x = zt_max(0.01f, min_size.x);
	min_size.y = zt_max(0.01f, min_size.y);

	return min_size;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSizerUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiSizerUpdate))
{
	ZT_PROFILE_GUI("_zt_guiSizerUpdate");

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
			else if(item->sizer.size_to_parent) {
				item->size.x = item->parent->size.x;
				recalc = true;
			}
			else {
				if(item->size.x != min_size.x) {
					item->size.x = min_size.x;
					recalc = true;
				}
			}

			if (item->sizer.size_parent_y) {
				if (item->parent->size.y != min_size.y) {
					item->size.y = item->parent->size.y = min_size.y;
					recalc = true;
				}
			}
			else if(item->sizer.size_to_parent) {
				item->size.y = item->parent->size.y;
				recalc = true;
			}
			else {
				if(item->size.y != min_size.y) {
					item->size.y = min_size.y;
					recalc = true;
				}
			}

			if (recalc) {
				zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(item->parent));
			}
		}

		item->sizer.size[0] = item->size.x;
		item->sizer.size[1] = item->size.y;
	}

	if (item->sizer.type == ztGuiSizerType_Normal) {
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
	else if (item->sizer.type == ztGuiSizerType_Column) {
		zt_linkGetCount(items_count, item->sizer.items);

		int items_per_column = zt_convertToi32Ceil(items_count / (r32)item->sizer.columns);

		ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;

		ztVec2 column_sizes[ZT_GUI_SIZER_MAX_COLUMNS];
		r32 item_size = 0;

		int total_prop = 0;
		zt_fxz(item->sizer.columns) {
			column_sizes[x] = ztVec2::zero;
			total_prop += item->sizer.props[x];

			int items_this_col = 0;
			while (entry && items_this_col++ < items_per_column) {
				ztVec2 size = entry->item->size;
				if (entry->item->type == ztGuiItemType_Sizer) {
					size = entry->item->size = _zt_guiSizerMinSize(entry->item);
				}

				column_sizes[x].x = zt_max(column_sizes[x].x, size.x + entry->padding * 2);
				column_sizes[x].y += size.y + entry->padding * 2;

				entry = entry->next;
			}

			item_size += column_sizes[x].x;
		}

		// column sizes are now at the minimum, so now distribute the extra size according to proportions
		r32 extra = item->size.x - item_size;
		zt_fxz(item->sizer.columns) {
			column_sizes[x].x += extra * (item->sizer.props[x] / (r32)total_prop);
		}

		// position each item
		r32 col_x = item->size.x / -2;

		entry = item->sizer.items;
		zt_fxz(item->sizer.columns) {
			int items_this_col = 0;
			r32 item_y = item->size.y / 2;
			while (entry && items_this_col++ < items_per_column) {
				ztVec2 size = entry->item->size;
				if (entry->item->type == ztGuiItemType_Sizer) {
					size = _zt_guiSizerMinSize(entry->item);
				}

				if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Horz)) {
					entry->item->size.x = column_sizes[x].x - entry->padding * 2;
				}

				if (zt_bitIsSet(entry->align_flags, ztAlign_Left)) {
					entry->item->pos.x = col_x + entry->padding + entry->item->size.x / 2;
				}
				else if (zt_bitIsSet(entry->align_flags, ztAlign_Right)) {
					entry->item->pos.x = (col_x + column_sizes[x].x) - (entry->item->size.x + entry->padding);
				}
				else {
					entry->item->pos.x = (col_x + (column_sizes[x].x / 2));
				}
				entry->item->pos.y = (item_y - entry->padding) - (entry->item->size.y / 2);
				item_y -= entry->item->size.y + entry->padding * 2;

				entry = entry->next;
			}

			col_x += column_sizes[x].x;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSizerCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiSizerCleanup))
{
	ZT_PROFILE_GUI("_zt_guiSizerCleanup");

	ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
	while (entry) {
		ztGuiItem::ztSizerItemEntry *copy = entry;
		entry = entry->next;
		zt_freeArena(copy, item->gm->arena);
	}
	item->sizer.items = nullptr;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSizerBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiSizerBestSize))
{
	ZT_PROFILE_GUI("_zt_guiSizerBestSize");

	*size = _zt_guiSizerMinSize(item);
	if (min_size) *min_size = *size;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeSizer(ztGuiItem *parent, ztGuiItemOrient_Enum orient, bool size_to_parent)
{
	ZT_PROFILE_GUI("zt_guiMakeSizer");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Sizer, 0);
	zt_returnValOnNull(item, nullptr);

	item->sizer.orient = orient;
	item->sizer.type = ztGuiSizerType_Normal;
	item->sizer.size[0] = item->sizer.size[1] = 0;
	item->sizer.size_to_parent = size_to_parent;
	item->sizer.size_parent_x = item->sizer.size_parent_y = false;
	item->sizer.items = nullptr;

	item->functions.cleanup = _zt_guiSizerCleanup_FunctionID;
	item->functions.update = _zt_guiSizerUpdate_FunctionID;
	item->functions.best_size = _zt_guiSizerBestSize_FunctionID;
	item->functions.user_data = nullptr;

	return item;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiMakeColumnSizer(ztGuiItem *parent, int columns, bool size_to_parent)
{
	ZT_PROFILE_GUI("zt_guiMakeColumnSizer");

	ztGuiItem *sizer = zt_guiMakeSizer(parent, ztGuiItemOrient_Horz, size_to_parent);
	if (sizer) {
		sizer->sizer.type = ztGuiSizerType_Column;
		sizer->sizer.columns = columns;
		zt_fiz(columns) {
			sizer->sizer.props[i] = 1;
		}
	}

	return sizer;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerAddItem(ztGuiItem *sizer, ztGuiItem *item, int proportion, r32 padding, i32 align_flags, i32 grow_direction)
{
	ZT_PROFILE_GUI("zt_guiSizerAddItem");

	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer);
	zt_assert(sizer->gm == item->gm);

	zt_guiItemReparent(item, sizer);

	ztGuiItem::ztSizerItemEntry *entry = zt_mallocStructArena(ztGuiItem::ztSizerItemEntry, item->gm->arena);

	entry->item           = item;
	entry->proportion     = proportion;
	entry->padding        = padding;
	entry->align_flags    = align_flags;
	entry->grow_direction = grow_direction;
	entry->next           = nullptr;

	zt_singleLinkAddToEnd(sizer->sizer.items, entry);

	sizer->sizer.size[0] = sizer->sizer.size[1] = 0; // trigger recalc

	if (item->type == ztGuiItemType_Sizer) {
		item->sizer.size_to_parent = false;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerAddStretcher(ztGuiItem *sizer, int proportion, r32 padding)
{
	ZT_PROFILE_GUI("zt_guiSizerAddStretcher");

	ztGuiItem *stretcher = _zt_guiMakeItemBase(sizer, ztGuiItemType_Custom, 0);
	zt_debugOnly(zt_guiItemSetName(stretcher, "Sizer Stretcher"));

	zt_guiSizerAddItem(sizer, stretcher, proportion, padding);
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerSizeToParent(ztGuiItem *sizer, bool size_to_parent)
{
	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer);
	sizer->sizer.size_to_parent = size_to_parent;
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerSizeParent(ztGuiItem *sizer, bool size_parent_x, bool size_parent_y)
{
	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer);
	sizer->sizer.size_to_parent = false;
	sizer->sizer.size_parent_x = size_parent_x;
	sizer->sizer.size_parent_y = size_parent_y;
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiSizerRecalc(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSizerRecalc");

	if (item->type == ztGuiItemType_Sizer) {
		item->sizer.size[0] = item->sizer.size[1] = -1;
	}

	ztGuiItem *child = item->first_child;
	while (child) {
		zt_guiSizerRecalc(child);
		child = child->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerRecalc(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiSizerRecalc");

	_zt_guiSizerRecalc(item);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiSizerRecalcImmediately(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSizerRecalcImmediately");

	if (item->type == ztGuiItemType_Sizer) {
		_zt_guiSizerUpdate(item, 0, item->functions.user_data);
	}

	ztGuiItem *child = item->first_child;
	while (child) {
		_zt_guiSizerRecalcImmediately(child);
		child = child->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiSizerRecalcImmediately(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiSizerRecalcImmediately");

	_zt_guiSizerRecalc(item);
	_zt_guiSizerRecalcImmediately(item);
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiSizerGetMinSize(ztGuiItem *sizer)
{
	ZT_PROFILE_GUI("zt_guiSizerGetMinSize");

	zt_returnValOnNull(sizer, ztVec2::zero);

	if (sizer->type == ztGuiItemType_Sizer) {
		return _zt_guiSizerMinSize(sizer);
	}
	else if (sizer->first_child && sizer->first_child->type == ztGuiItemType_Sizer && sizer->first_child->sib_next == nullptr) {
		return _zt_guiSizerMinSize(sizer->first_child);
	}

	return ztVec2::zero;
}

// ------------------------------------------------------------------------------------------------

void zt_guiColumnSizerSetProp(ztGuiItem *sizer, int col, int prop)
{
	ZT_PROFILE_GUI("zt_guiColumnSizerSetProp");

	zt_returnOnNull(sizer);
	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer && sizer->sizer.type == ztGuiSizerType_Column);
	zt_assertReturnOnFail(col >= 0 && col < sizer->sizer.columns);

	sizer->sizer.props[col] = prop;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemFree(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemFree");

	if (item == nullptr) {
		return;
	}

	_zt_guiItemFree(item->gm, item);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetSize(ztGuiItem *item, const ztVec2& size)
{
	zt_returnOnNull(item);

	if (size.x != -1) item->size.x = size.x;
	if (size.y != -1) item->size.y = size.y;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemAutoSize(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemAutoSize");

	zt_returnOnNull(item);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	if (item->functions.best_size != ztInvalidID) {
		ztVec2 min, max;
		((zt_guiItemBestSize_Func*)zt_functionPointer(item->functions.best_size))(item, &min, &max, &item->size, theme, item->functions.user_data);
	}
	//else {
	//	if (item->label != nullptr) {
	//		item->size = zt_fontGetExtents(theme->font, item->label);
	//		item->size.x += theme->padding * 2;
	//		item->size.y += theme->padding * 2;
	//	}
	//}
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetPosition(ztGuiItem *item, const ztVec2& pos)
{
	zt_returnOnNull(item);
	item->pos = pos;
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetPosition(ztGuiItem *item, i32 align_flags, i32 anchor_flags, ztVec2 offset)
{
	ZT_PROFILE_GUI("zt_guiItemSetPosition");

	zt_returnOnNull(item);
	item->pos_align_flags = align_flags;
	item->pos_anchor_flags = anchor_flags;
	item->pos_offset = offset;

	_zt_guiItemReposition(item->gm, item);
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetName(ztGuiItem *item, const char *name)
{
	ZT_PROFILE_GUI("zt_guiItemSetName");

	zt_returnOnNull(item);
	item->name = zt_stringOverwrite(item->name, name, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetLabel(ztGuiItem *item, const char *label)
{
	ZT_PROFILE_GUI("zt_guiItemSetLabel");

	zt_returnOnNull(item);
	item->label = zt_stringOverwrite(item->label, label, item->gm->arena);
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetTooltip(ztGuiItem *item, const char *tooltip)
{
	ZT_PROFILE_GUI("zt_guiItemSetTooltip");

	zt_returnOnNull(item);
	item->tooltip = zt_stringOverwrite(item->tooltip, tooltip, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetThemeType(ztGuiItem *item, const char *theme_type)
{
	ZT_PROFILE_GUI("zt_guiItemSetThemeType");

	zt_returnOnNull(item);
	item->theme_type = zt_stringOverwrite(item->theme_type, theme_type, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetTheme(ztGuiItem *item, ztGuiTheme *theme)
{
	zt_returnOnNull(item);
	item->theme = theme;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetName(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->name;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetLabel(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->label;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetTooltip(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->tooltip;
}

// ------------------------------------------------------------------------------------------------

ztString zt_guiItemGetThemeType(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->theme_type;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemSetAlign(ztGuiItem *item, i32 align_flags)
{
	zt_returnOnNull(item);
	item->align_flags = align_flags;
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ------------------------------------------------------------------------------------------------

i32 zt_guiItemGetAlign(ztGuiItem *item)
{
	zt_returnValOnNull(item, 0);
	return item->align_flags;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsShowing(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemIsShowing");

	zt_returnValOnNull(item, false);

	if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		return false;
	}

	ztGuiItem *parent = item->parent;
	while (parent) {
		if (!zt_bitIsSet(parent->state_flags, zt_bit(ztGuiItemStates_Visible))) {
			return false;
		}
		parent = parent->parent;
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemShow(ztGuiItem *item, bool show)
{
	zt_returnOnNull(item);

	if (show) {
		item->state_flags |= zt_bit(ztGuiItemStates_Visible);
	}
	else {
		zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Visible));
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemHide(ztGuiItem *item)
{
	zt_guiItemShow(item, false);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsVisible(ztGuiItem *item)
{
	zt_returnValOnNull(item, false);
	return zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible));
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemEnable(ztGuiItem *item, bool enable)
{
	zt_returnOnNull(item);

	if (enable) {
		zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Disabled));
	}
	else {
		item->state_flags |= zt_bit(ztGuiItemStates_Disabled);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemDisable(ztGuiItem *item)
{
	zt_returnOnNull(item);
	zt_guiItemEnable(item, false);
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsEnabled(ztGuiItem *item)
{
	zt_returnValOnNull(item, false);
	return !zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled));
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemBringToFront(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemBringToFront");

	zt_returnOnNull(item);

	if (item->parent == nullptr && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_BringToFront)) {
		// need to make this particular child the last in the series
		if (item->sib_next) {
			if (item->sib_prev) item->sib_prev->sib_next = item->sib_next;
			if (item->sib_next) item->sib_next->sib_prev = item->sib_prev;
			zt_assert(item->sib_next->sib_prev != item->sib_next);

			if (item->gm->first_child == item) {
				item->gm->first_child = item->sib_next;
			}

			ztGuiItem *last_child = item->gm->first_child;
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

ztGuiItem *zt_guiItemGetTopLevelParent(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemGetTopLevelParent");

	zt_returnValOnNull(item, nullptr);

	ztGuiItem *last = item;
	ztGuiItem *parent = item->parent;
	while (parent) {
		last = parent;
		parent = parent->parent;
	}

	return last;
}

// ------------------------------------------------------------------------------------------------

bool zt_guiItemIsChildOf(ztGuiItem *parent, ztGuiItem *child)
{
	ZT_PROFILE_GUI("zt_guiItemIsChildOf");

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

ztGuiItem *zt_guiItemFindByName(const char *name, ztGuiItem *parent)
{
	ZT_PROFILE_GUI("zt_guiItemFindByName");

	if (parent) {
		if (zt_strEquals(name, parent->name)) {
			return parent;
		}

		for (auto *child = parent->first_child; child != nullptr; child = child->sib_next) {
			ztGuiItem *result = zt_guiItemFindByName(name, child);
			if (result) {
				return result;
			}
		}
	}
	else {
		ztGuiManager *gm = zt_gui->gui_manager_active;
		for (auto *child = gm->first_child; child != nullptr; child = child->sib_next) {
			ztGuiItem *result = zt_guiItemFindByName(name, child);
			if (result) {
				return result;
			}
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiItemFindByType(ztGuiItemType_Enum type, ztGuiItem *parent, ztGuiItem *find_after)
{
	ZT_PROFILE_GUI("zt_guiItemFindByType");

	bool return_next = find_after == nullptr;

	if (parent) {
		zt_flinknext(child, parent->first_child, sib_next) {
			if (child->type == type) {
				if (return_next) {
					return child;
				}
				if (child == find_after) {
					return_next = true;
					find_after = nullptr;
				}
			}
		}

		zt_flinknext(child, parent->first_child, sib_next) {
			ztGuiItem *result = zt_guiItemFindByType(type, child, find_after);
			if (result) {
				return result;
			}
		}
	}
	else {
		ztGuiManager *gm = zt_gui->gui_manager_active;
		zt_flinknext(child, gm->first_child, sib_next) {
			ztGuiItem *result = zt_guiItemFindByType(type, child, find_after);
			if (result) {
				return result;
			}
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

ztVec2 zt_guiItemPositionLocalToScreen(ztGuiItem *item, const ztVec2& pos)
{
	ZT_PROFILE_GUI("zt_guiItemPositionLocalToScreen");

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

ztVec2 zt_guiItemPositionScreenToLocal(ztGuiItem *item, const ztVec2& pos)
{
	ZT_PROFILE_GUI("zt_guiItemPositionScreenToLocal");

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

void zt_guiItemSetFocus(ztGuiItem *item, ztGuiItem **prev_focus_item_id)
{
	zt_returnOnNull(item);
	if (prev_focus_item_id) *prev_focus_item_id = item->gm->focus_item;
	item->gm->focus_item = item;
}

// ------------------------------------------------------------------------------------------------

ztGuiTheme *zt_guiItemGetTheme(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemGetTheme");

	zt_returnValOnNull(item, nullptr);
	if (item->theme) {
		return item->theme;
	}

	for (ztGuiItem *parent = item->parent; parent; parent = parent->parent) {
		if (parent->theme) {
			return parent->theme;
		}
	}

	return &item->gm->default_theme;
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemLock(ztGuiItem *item)
{
	zt_returnOnNull(item);
	item->state_flags |= zt_bit(ztGuiItemStates_Locked);
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemUnlock(ztGuiItem *item)
{
	zt_returnOnNull(item);
	zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Locked));
}

// ------------------------------------------------------------------------------------------------

void zt_guiItemReparent(ztGuiItem *item, ztGuiItem *new_parent)
{
	ZT_PROFILE_GUI("zt_guiItemReparent");

	zt_returnOnNull(item);

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
		if (item == item->gm->first_child) {
			item->gm->first_child = item->sib_next;
		}
	}
	if (item->sib_prev) item->sib_prev->sib_next = item->sib_next;
	if (item->sib_next) item->sib_next->sib_prev = item->sib_prev;
	zt_assert(item->sib_next == nullptr || item->sib_next->sib_prev != item->sib_next);

	item->sib_next = nullptr;
	item->sib_prev = nullptr;

	item->parent = new_parent;

	ztGuiItem *sibling = new_parent == nullptr ? item->gm->first_child : new_parent->first_child;
	if (sibling == nullptr) {
		if (new_parent == nullptr) {
			item->gm->first_child = item;
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

bool zt_guiItemTopLevelIsOverlapping(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemTopLevelIsOverlapping");

	zt_returnValOnNull(item, false);

	item = zt_guiItemGetTopLevelParent(item);

	ztVec3 item_center(item->pos, 0);
	ztVec3 item_size(item->size, 1);

	zt_flinknext(child, item->gm->first_child, sib_next) {
		if(child == item) {
			return false;
		}
		if (!zt_guiItemIsShowing(child)) {
			continue;
		}

		ztVec3 child_center(child->pos, 0);
		ztVec3 child_size(child->size, 1);

		// bool zt_collisionAABBInAABB(const ztVec3& aabb_center_1, const ztVec3& aabb_extents_1, const ztVec3& aabb_center_2, const ztVec3& aabb_extents_2);
		if(zt_collisionAABBInAABB(item_center, item_size, child_center, child_size)) {
			return true;
		}
	}

	return false;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ZT_DEBUG_MENUBAR_NAME	"Debug Menu"

// ------------------------------------------------------------------------------------------------

struct ztDebugRenderingDetails
{
	ztGuiItem *window;
	ztGuiItem *text;
	ztGuiItem *sizer;
};

#define ZT_DEBUG_RENDERING_DETAILS_WINDOW_NAME	"Rendering Details Window"

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugRenderingDetailsUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiDebugRenderingDetailsUpdate))
{
	ZT_PROFILE_GUI("_zt_guiDebugRenderingDetailsUpdate");

	if (!zt_guiItemIsShowing(item)) return;

	ztDebugRenderingDetails *details = (ztDebugRenderingDetails*)item->functions.user_data;

	zt_strMakePrintf(details_str, 256, "%d triangles\n%d shader switches\n%d tex switches\n%d draw calls", zt_game->game_details.prev_frame.triangles_drawn, zt_game->game_details.prev_frame.shader_switches, zt_game->game_details.prev_frame.texture_switches, zt_game->game_details.prev_frame.draw_calls);
	zt_guiItemSetLabel(details->text, details_str);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugRenderingDetailsCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugRenderingDetailsCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugRenderDetailsSize(ztDebugRenderingDetails *details)
{
	details->sizer->size = zt_guiSizerGetMinSize(details->sizer);
	//zt_guiSizerRecalcImmediately(details->sizer);

	r32 ppu = zt_pixelsPerUnit();

	details->window->size = details->sizer->size + ztVec2(8 / ppu, 4 / ppu);
}

// ------------------------------------------------------------------------------------------------

ztInternal bool _zt_guiDebugRenderingDetails()
{
	const char *window_name = ZT_DEBUG_RENDERING_DETAILS_WINDOW_NAME;

	r32 y_off = -.35f;

	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		y_off = -(menubar->size.y + 2 / zt_pixelsPerUnit());
	}

	ztGuiItem *window = zt_guiItemFindByName(window_name);
	if (window != nullptr) {
		zt_guiItemShow(window, !zt_guiItemIsShowing(window));
		zt_guiItemSetPosition(window, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right, ztVec2(0, y_off));
		return zt_guiItemIsShowing(window);
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugRenderingDetails *details = zt_mallocStructArena(ztDebugRenderingDetails, gm->arena);
	*details = {};

	window = zt_guiMakeWindow(nullptr, ztGuiWindowBehaviorFlags_AllowDrag);
	zt_guiItemSetName(window, window_name);

	details->window = window;
	details->sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(details->sizer, false);

	details->text = zt_guiMakeStaticText(details->sizer, "00000000 triangles\n0000 shader switches\n0000 tex switches\n0000 draw calls", ztGuiStaticTextBehaviorFlags_MonoSpaced);
	zt_guiItemSetAlign(details->text, ztAlign_Right);
	zt_debugOnly(zt_guiItemSetName(details->text, "Rendering Details Text"));
	zt_guiSizerAddItem(details->sizer, details->text, 0, 3 / zt_pixelsPerUnit());

	//zt_guiItemSetSize(window, ztVec2(3.25f, 1.2f));
	//zt_guiItemSetPosition(details->text, ztAlign_Right, ztAnchor_Right, ztVec2(-26.f / zt_pixelsPerUnit(), 0));

	_zt_guiDebugRenderDetailsSize(details);

	ztGuiItem *update = _zt_guiMakeItemBase(window, ztGuiItemType_Custom, 0);
	update->functions.update = _zt_guiDebugRenderingDetailsUpdate_FunctionID;
	update->functions.cleanup = _zt_guiDebugRenderingDetailsCleanup_FunctionID;
	update->functions.user_data = details;


	zt_guiItemSetPosition(window, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right, ztVec2(0, y_off));
	return true;
}

// ------------------------------------------------------------------------------------------------

ztGuiItem *zt_guiDebugAddMetric(const char *sample)
{
	ztGuiItem *window = zt_guiItemFindByName(ZT_DEBUG_RENDERING_DETAILS_WINDOW_NAME);
	bool needs_hidden = false;
	if (window == nullptr) {
		_zt_guiDebugRenderingDetails();
		window = zt_guiItemFindByName(ZT_DEBUG_RENDERING_DETAILS_WINDOW_NAME);
		needs_hidden = true;
	}
	if (window != nullptr) {
		ztGuiItem* custom = zt_guiItemFindByType(ztGuiItemType_Custom, window);
		if (custom) {
			ztDebugRenderingDetails *details = (ztDebugRenderingDetails*)custom->functions.user_data;
			ztGuiItem *static_txt = zt_guiMakeStaticText(details->sizer, sample, ztGuiStaticTextBehaviorFlags_MonoSpaced);
			zt_guiItemSetAlign(static_txt, ztAlign_Right);
			zt_guiSizerAddItem(details->sizer, static_txt, 0, 3 / zt_pixelsPerUnit());
			_zt_guiDebugRenderDetailsSize(details);
			if (needs_hidden) {
				zt_guiItemHide(window);
			}

			return static_txt;
		}
	}

	return nullptr;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct ztDebugFpsDisplay
{
	ztGuiItem  *panel;
	ztGuiItem  *text;
	ztGuiItem  *button;
};

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugFpsDisplayUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiDebugFpsDisplayUpdate))
{
	ZT_PROFILE_GUI("_zt_guiDebugFpsDisplayUpdate");

	ztDebugFpsDisplay *fps = (ztDebugFpsDisplay*)item->functions.user_data;

	if (!zt_guiItemIsShowing(fps->panel)) return;

	zt_strMakePrintf(fps_str, 256, "%.0f f/s %.02f us/f", 1.f / dt, dt * 1000000.f);
	zt_guiItemSetLabel(fps->text, fps_str);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugFpsDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugFpsDisplayCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugFpsDisplayButtonExpand, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugFpsDisplayButtonExpand))
{
	if (_zt_guiDebugRenderingDetails()) {
		zt_guiItemSetLabel(button, "-");
	}
	else {
		zt_guiItemSetLabel(button, "+");
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugFpsDisplay()
{
	const char *window_name = "FPS Display Window";

	{
		ztGuiItem *window = zt_guiItemFindByName(window_name);
		if (window != nullptr) {
			zt_guiItemShow(window, !zt_guiItemIsShowing(window));
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugFpsDisplay *fps = zt_mallocStructArena(ztDebugFpsDisplay, gm->arena);
	*fps = {};

	fps->panel = zt_guiMakePanel(zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME));
	zt_guiItemSetName(fps->panel, window_name);

	ztGuiItem *sizer = zt_guiMakeSizer(fps->panel, ztGuiItemOrient_Horz);
	zt_guiSizerSizeToParent(sizer);

	fps->text = zt_guiMakeStaticText(fps->panel, "00000 f/s 00.0000f us/f", ztGuiStaticTextBehaviorFlags_MonoSpaced);
	zt_guiItemSetAlign(fps->text, ztAlign_Right);
	zt_debugOnly(zt_guiItemSetName(fps->text, "FPS Display Text"));
	zt_guiSizerAddItem(sizer, fps->text, 1, 0);
	zt_guiSizerAddStretcher(sizer, 0, 3 / zt_pixelsPerUnit());

	fps->button = zt_guiMakeButton(fps->panel, "+", ztGuiButtonBehaviorFlags_NoBackground);
	zt_guiButtonSetCallback(fps->button, _zt_guiDebugFpsDisplayButtonExpand_FunctionID);
	fps->button->size.x = fps->button->size.y = 18 / zt_pixelsPerUnit();
	zt_guiSizerAddItem(sizer, fps->button, 0, 2 / zt_pixelsPerUnit());

	zt_guiItemSetSize(fps->panel, ztVec2(3.25f, 20 / zt_pixelsPerUnit()));

	ztGuiItem *update = _zt_guiMakeItemBase(fps->panel, ztGuiItemType_Custom, 0);
	update->functions.update  = _zt_guiDebugFpsDisplayUpdate_FunctionID;
	update->functions.cleanup = _zt_guiDebugFpsDisplayCleanup_FunctionID;
	update->functions.user_data = fps;

	zt_guiItemSetPosition(fps->panel, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#ifndef ZT_DEBUG_CONSOLE_BUFFER_SIZE
#define ZT_DEBUG_CONSOLE_BUFFER_SIZE	1024 * 32
#endif

#ifndef ZT_DEBUG_CONSOLE_MAX_COMMANDS
#define ZT_DEBUG_CONSOLE_MAX_COMMANDS 32
#endif

#define ZT_DEBUG_CONSOLE_NAME           "Console"
#define ZT_DEBUG_CONSOLE_COMMAND_NAME   "Console Command"

// ------------------------------------------------------------------------------------------------

struct ztConsoleCmdStr
{
	char command[128];
	ztConsoleCmdStr *next, *prev;
};

// ------------------------------------------------------------------------------------------------

struct ztDebugConsole
{
	ztGuiItem       *display;
	ztGuiItem       *command;
	int              last_tab_stop;

	char             working_buffer[ZT_DEBUG_CONSOLE_BUFFER_SIZE];

	ztConsoleCmdStr *commands;
	byte             command_buffer[zt_sizeof(ztConsoleCmdStr) * ZT_DEBUG_CONSOLE_MAX_COMMANDS];

	ztConsoleCmdStr *current_command;
	ztConsoleCmdStr *selected_command;
};

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugConsoleCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleInputKey, ztInternal ZT_FUNC_GUI_TEXTEDIT_KEY(_zt_guiDebugConsoleInputKey))
{
	ZT_PROFILE_GUI("_zt_guiDebugConsoleInputKey");

	ztGuiItem *console = zt_guiItemGetTopLevelParent(textedit);
	zt_returnOnNull(console);
	ztDebugConsole *dc = (ztDebugConsole*)console->functions.user_data;

	if (input_keys[ztInputKeys_Return].justPressed()) {

		zt_guiTextEditGetValue(dc->command, dc->current_command->command, zt_elementsOf(dc->current_command->command));
		zt_guiTextEditSetValue(dc->command, nullptr);

		if (zt_strLen(dc->current_command->command) == 0) {
			zt_debugConsoleLogWarning("  Please enter a command.");
			return;
		}

		zt_debugConsoleLogUser("> %s", dc->current_command->command);

		ztToken tokens[16];
		int tokens_count = zt_strTokenize(dc->current_command->command, " ", tokens, zt_elementsOf(tokens));
		if (tokens_count > 16) {
			zt_debugConsoleLogError("  Too many parameters");
		}
		else {
			ztDebugConsoleParams(params);

			zt_fiz(tokens_count) {
				zt_strCpy(params[i], 256, zt_strMoveForward(dc->current_command->command, tokens[i].beg), tokens[i].len);
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
				((zt_debugConsole_Func*)zt_functionPointer(command->on_command))(params, tokens_count, command->user_data);
			}
		}

		dc->current_command = dc->current_command->next;
		dc->selected_command = dc->current_command;
	}
	if (input_keys[ztInputKeys_Up].justPressed()) {
		if (dc->selected_command->prev->command[0] != 0 && dc->selected_command->prev != dc->current_command) {
			dc->selected_command = dc->selected_command->prev;
			zt_guiTextEditSetValue(dc->command, dc->selected_command->command);
			zt_guiTextEditSelectAll(dc->command);
			zt_guiTextEditSetCursorPos(dc->command, 0);
		}
	}
	if (input_keys[ztInputKeys_Down].justPressed()) {
		if (dc->selected_command->next != dc->current_command && dc->selected_command->next->command[0] != 0) {
			dc->selected_command = dc->selected_command->next;
			zt_guiTextEditSetValue(dc->command, dc->selected_command->command);
			zt_guiTextEditSelectAll(dc->command);
			zt_guiTextEditSetCursorPos(dc->command, 0);
		}
	}
	if (input_keys[ztInputKeys_Tab].justPressedOrRepeated()) {
		*should_process = false;

		char command_buffer[256];
		zt_guiTextEditGetValue(dc->command, command_buffer, zt_elementsOf(command_buffer));

		if (zt_strFindPos(command_buffer, " ", 0) != ztStrPosNotFound) {

		}
		else {
			int cursor = zt_guiTextEditGetCursorPos(dc->command);
			char start_with[256];
			zt_strCpy(start_with, zt_elementsOf(start_with), command_buffer, cursor);

			int which_stop = 0;
			auto *command = zt_gui->console_commands;
			while (command) {
				if (zt_strStartsWith(command->command, start_with)) {
					if (++which_stop > dc->last_tab_stop) {
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
				zt_guiTextEditSetValue(dc->command, command->command);
				zt_guiTextEditSetSelection(dc->command, cursor, cursor + 999999);
				zt_guiTextEditSetCursorPos(dc->command, 999999);
				dc->last_tab_stop = which_stop;
			}
		}
		return;
	}

	zt_fiz(zt_elementsOf(input_key_strokes)) {
		if (input_key_strokes[i] == ztInputKeys_Invalid) {
			break;
		}
		if (input_keys[input_key_strokes[i]].display != 0) {
			dc->last_tab_stop = 0;
		}
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleLogMessageCallback, ztInternal void _zt_guiDebugConsoleLogMessageCallback(ztLogMessageLevel_Enum level, const char * message))
{
	ZT_PROFILE_GUI("_zt_guiDebugConsoleLogMessageCallback");

	switch (level)
	{
		case ztLogMessageLevel_Fatal:
		case ztLogMessageLevel_Critical: zt_debugConsoleLogError(message); break;

		case ztLogMessageLevel_Info: zt_debugConsoleLogCommand(message); break;

		case ztLogMessageLevel_Verbose:
		case ztLogMessageLevel_Debug: zt_debugConsoleLogCommand("<color=44cccc>%s</color>", message); break;
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_List, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_List))
{
	zt_debugConsoleLogCommand("  Available commands:");

	auto *command = zt_gui->console_commands;
	while (command) {
		zt_debugConsoleLogCommand("    %s", command->command);
		command = command->next;
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_Help, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_Help))
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

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommandAutoComplete_Help, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(_zt_guiDebugConsoleCommandAutoComplete_Help))
{

}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_Exit, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_Exit))
{
	zt_game->quit_requested = true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_PlayAudio, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_PlayAudio))
{
	ztAudioClipID audio_clip_id = zt_strToInt(params[1], ztInvalidID);
	if(audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count) {
		zt_audioClipPlayOnce(audio_clip_id);
	}
	else {
		if(zt_game->audio_clips_count == 0) {
			zt_debugConsoleLogCommand("There are no loaded audio clips to play");
		}
		else {
			zt_debugConsoleLogCommand("Please select an ID between 0 and %d", zt_game->audio_clips_count - 1);
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugConsoleAddLoggingCallbacks()
{
	if (zt_gui->console_window != nullptr) {
		zt_logAddCallback(_zt_guiDebugConsoleLogMessageCallback, ztLogMessageLevel_Debug);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugConsoleRemoveLoggingCallbacks()
{
	zt_logRemoveCallback(_zt_guiDebugConsoleLogMessageCallback);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugConsole()
{
	{
		ztGuiItem *window = zt_guiItemFindByName(ZT_DEBUG_CONSOLE_NAME);
		if (window != nullptr) {
			zt_guiItemShow(window);
			zt_guiItemSetFocus(zt_guiItemFindByName(ZT_DEBUG_CONSOLE_COMMAND_NAME, window));
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugConsole *dc = zt_mallocStructArena(ztDebugConsole, gm->arena);
	zt_memSet(dc, zt_sizeof(ztDebugConsole), 0);

	byte *command_buffer_ptr = dc->command_buffer;

	ztConsoleCmdStr* first = nullptr;
	zt_fiz(ZT_DEBUG_CONSOLE_MAX_COMMANDS) {
		ztConsoleCmdStr *cmd = (ztConsoleCmdStr*)command_buffer_ptr;
		command_buffer_ptr += zt_sizeof(ztConsoleCmdStr);

		if (dc->commands) {
			dc->commands->prev = cmd;
		}
		else {
			first = cmd;
		}
		cmd->command[0] = 0;
		cmd->next = dc->commands;
		cmd->prev = nullptr;
		dc->commands = cmd;
	}

	dc->commands->prev = first;
	first->next = dc->commands;

	dc->current_command = dc->commands;
	dc->selected_command = dc->current_command;

	ztGuiItem *window = zt_guiMakeWindow("Console", ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowCollapse | ztGuiWindowBehaviorFlags_CloseHides);
	zt_gui->console_window = window;

	window->functions.user_data = dc;
	window->functions.cleanup = _zt_guiDebugConsoleCleanup_FunctionID;
	
	zt_guiItemSetSize(window, ztVec2(16, 9));
	zt_guiItemSetName(window, ZT_DEBUG_CONSOLE_NAME);

	ztGuiItem *content = zt_guiWindowGetContentParent(window);
	ztGuiItem *display_container = zt_gui->console_display_container = zt_guiMakeScrollContainer(content, ztGuiScrollContainerBehaviorFlags_ShowScrollVert);
	zt_gui->console_display = dc->display = zt_guiMakeStaticText(display_container, nullptr, ztGuiStaticTextBehaviorFlags_Fancy | ztGuiStaticTextBehaviorFlags_MonoSpaced, zt_elementsOf(dc->working_buffer));
	zt_guiScrollContainerSetItem(display_container, dc->display);

	zt_guiItemSetAlign(dc->display, ztAlign_Left | ztAlign_Top);

	zt_gui->console_command = dc->command = zt_guiMakeTextEdit(content, nullptr);
	zt_guiItemSetName(zt_gui->console_command, ZT_DEBUG_CONSOLE_COMMAND_NAME);
	zt_guiTextEditSetCallback(dc->command, _zt_guiDebugConsoleInputKey_FunctionID);
	zt_guiItemSetFocus(zt_gui->console_command);

	ztGuiItem *main_sizer = zt_guiMakeSizer(content, ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(main_sizer);

	zt_guiSizerAddItem(main_sizer, display_container, 1, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddItem(main_sizer, dc->command, 0, 3 / zt_pixelsPerUnit(), 0, ztGuiItemOrient_Horz);

	zt_debugConsoleAddCommand("list", "Lists the available commands", _zt_guiDebugConsoleCommand_List_FunctionID     , ztInvalidID);
	zt_debugConsoleAddCommand("help",                        nullptr, _zt_guiDebugConsoleCommand_Help_FunctionID     , _zt_guiDebugConsoleCommandAutoComplete_Help_FunctionID);
	zt_debugConsoleAddCommand("exit",            "Quits the program", _zt_guiDebugConsoleCommand_Exit_FunctionID     , ztInvalidID);
	zt_debugConsoleAddCommand("playaudio",     "Plays an audio clip", _zt_guiDebugConsoleCommand_PlayAudio_FunctionID, ztInvalidID);

	zt_debugConsoleLogCommand("<color=00aa00ff>Welcome to the console.  Type 'help <<cmd>' for help.  Type 'list' for commands.</color>");

	zt_guiSizerRecalcImmediately(zt_gui->console_window);

	zt_guiItemShow(window, false);

	_zt_guiDebugConsoleAddLoggingCallbacks();
}

// ------------------------------------------------------------------------------------------------

void zt_debugConsoleAddCommand(const char *command, const char *help, ztFunctionID command_func, ztFunctionID auto_complete_func, void *user_data)
{
	ztConsoleCommand *console_command = zt_mallocStructArena(ztConsoleCommand, zt_gui->arena);
	zt_strCpy(console_command->command, zt_elementsOf(console_command->command), command);
	zt_strCpy(console_command->help, zt_elementsOf(console_command->help), help);
	console_command->on_command = command_func;
	console_command->on_auto_complete = auto_complete_func;
	console_command->user_data = user_data;

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
	ZT_PROFILE_GUI("_zt_debugConsoleLogRaw");

	zt_assertReturnOnFail(zt_gui->console_display->type == ztGuiItemType_StaticText);

	ztGuiItem *item = zt_gui->console_display;

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

	char lcl_command[1024 * 16];

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

	zt_guiItemSetLabel(item, buffer);
	zt_guiItemAutoSize(zt_gui->console_display);

	zt_freeArena(buffer, zt_gui->arena);

	zt_guiScrollContainerSetScroll(zt_gui->console_display_container, ztGuiItemOrient_Vert, 1);
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
	ZT_PROFILE_GUI("zt_debugConsoleToggle");

	if (zt_gui->console_window == nullptr) {
		_zt_guiDebugConsole();
		return;
	}
	bool show = !zt_guiItemIsVisible(zt_gui->console_window);
	zt_guiItemShow(zt_gui->console_window, show);
	zt_guiTextEditSetValue(zt_gui->console_command, "");
	zt_guiItemSetFocus(zt_gui->console_command);

	if (show) {
		zt_guiItemBringToFront(zt_gui->console_window);
	}

	if (is_shown) *is_shown = show;
}

// ------------------------------------------------------------------------------------------------

#undef _zt_var_args

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

struct ztDebugGuiHierarchy
{
	ztGuiItem *window  = nullptr;
	ztGuiItem *tree    = nullptr;
	ztGuiItem *details = nullptr;
};

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugGuiHierarchyAppend(ztDebugGuiHierarchy *dgh, ztGuiItem *item, ztGuiTreeNodeID parent_node)
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyAppend");

	if (item == dgh->window) {
		return;
	}

	zt_strMakePrintf(buffer, 1024, "%s - %s", zt_guiItemTypeName(item->type), item->name ? item->name : "(unnamed)");

	ztGuiTreeNodeID root = zt_guiTreeAppend(dgh->tree, buffer, item, parent_node);
	ztGuiItem *child = item->first_child;
	while (child) {
		_zt_guiDebugGuiHierarchyAppend(dgh, child, root);
		child = child->sib_next;
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugGuiHierarchyPopulate(ztDebugGuiHierarchy *dgh)
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyPopulate");

	zt_guiTreeClear(dgh->tree);

	zt_flink(gm, zt_gui->gui_manager_first) {
		ztGuiTreeNodeID root = zt_guiTreeAppend(dgh->tree, "GUI Manager", nullptr);

		zt_flinknext(child, gm->first_child, sib_next) {
			_zt_guiDebugGuiHierarchyAppend(dgh, child, root);
		}
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugGuiHierarchyPopulateItem(ztDebugGuiHierarchy *dgh, ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyPopulateItem");

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
		(zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsFocus) ? "true" : "false"),
		(zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsInput) ? "true" : "false"),
		(zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible)) ? "true" : "false"),
		(zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_HasOutlyingChildren) ? "true" : "false"),
		(zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_BringToFront) ? "true" : "false"),
		item->label ? item->label : "(no label)"
		);

	zt_guiItemSetLabel(dgh->details, details_buffer);
	zt_guiItemAutoSize(dgh->details);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyOnTreeSel, ztInternal ZT_FUNC_GUI_TREE_ITEM_SELECTED(_zt_guiDebugGuiHierarchyOnTreeSel))
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyOnTreeSel");

	ztGuiItem *item = (ztGuiItem*)zt_guiTreeGetNodeUserData(tree, node_id);
	if (item) {
		ztGuiItem *win = zt_guiItemGetTopLevelParent(tree);
		ztDebugGuiHierarchy *dgh = (ztDebugGuiHierarchy*)win->functions.user_data;
		_zt_guiDebugGuiHierarchyPopulateItem(dgh, item);
	}
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyOnRefreshTree, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugGuiHierarchyOnRefreshTree))
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyOnRefreshTree");

	ztGuiItem *win = zt_guiItemGetTopLevelParent(button);
	ztDebugGuiHierarchy *dgh = (ztDebugGuiHierarchy*)win->functions.user_data;
	_zt_guiDebugGuiHierarchyPopulate(dgh);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyOnToggleHighlight, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugGuiHierarchyOnToggleHighlight))
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyOnToggleHighlight");

#	if defined(ZT_DEBUG)
	ztGuiItem *win = zt_guiItemGetTopLevelParent(button);
	ztDebugGuiHierarchy *dgh = (ztDebugGuiHierarchy*)win->functions.user_data;

	ztGuiItem* item = (ztGuiItem*)zt_guiTreeGetNodeUserData(dgh->tree, zt_guiTreeGetSelected(dgh->tree));
	if (item) {
		if (item->debug_highlight == ztVec4::zero) {
			item->debug_highlight = ztVec4(0, 1, 0, 1);
		}
		else {
			item->debug_highlight = ztVec4::zero;
		}
	}
#	endif
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugGuiHierarchyCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugGuiHierarchy()
{
	const char *window_name = "GUI Hierarchy";

	{
		ztGuiItem *window = zt_guiItemFindByName(window_name);
		if (window != nullptr) {
			zt_guiItemShow(window);
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugGuiHierarchy *dgh = zt_mallocStructArena(ztDebugGuiHierarchy, gm->arena);
	*dgh = {};


	dgh->window = zt_guiMakeWindow("GUI Hierarchy", ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowCollapse | ztGuiWindowBehaviorFlags_CloseHides);
	dgh->window->functions.user_data = dgh;
	dgh->window->functions.cleanup = _zt_guiDebugGuiHierarchyCleanup_FunctionID;

	ztVec2 cam_ext = zt_cameraOrthoGetViewportSize(gm->gui_camera);
	zt_guiItemSetSize(dgh->window, ztVec2(cam_ext.x - 2, cam_ext.y - 2));

	ztGuiTheme *theme   = zt_guiItemGetTheme(dgh->window);
	ztGuiItem  *content = zt_guiWindowGetContentParent(dgh->window);
	ztGuiItem  *sizer   = zt_guiMakeSizer(content, ztGuiItemOrient_Horz);

	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding);

	zt_guiSizerSizeToParent(sizer);
	{

		ztGuiItem *sizer_left = zt_guiMakeSizer(sizer, ztGuiItemOrient_Vert);
		zt_guiSizerAddItem(sizer, sizer_left, 2, padding);

		dgh->tree = zt_guiMakeTree(sizer_left, 1024 * 64);
		zt_guiSizerAddItem(sizer_left, dgh->tree, 1, padding);

		zt_guiTreeSetCallback(dgh->tree, _zt_guiDebugGuiHierarchyOnTreeSel_FunctionID, nullptr);

		ztGuiItem *sizer_btns = zt_guiMakeSizer(sizer_left, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer_left, sizer_btns, 0, 0);

		ztGuiItem *button_refresh = zt_guiMakeButton(sizer_left, "Refresh");
		zt_guiButtonSetCallback(button_refresh, _zt_guiDebugGuiHierarchyOnRefreshTree_FunctionID);
		zt_guiSizerAddItem(sizer_btns, button_refresh, 0, padding);

#		if defined(ZT_DEBUG)
		zt_guiSizerAddStretcher(sizer_btns, 1);
		ztGuiItem *button_highlight = zt_guiMakeButton(sizer_btns, "Toggle Highlight");
		zt_guiButtonSetCallback(button_highlight, _zt_guiDebugGuiHierarchyOnToggleHighlight_FunctionID);
		zt_guiSizerAddItem(sizer_btns, button_highlight, 0, padding, ztAlign_Right, 0);
#		endif
	}

	{
		ztGuiItem *sizer_right = zt_guiMakeSizer(sizer, ztGuiItemOrient_Vert);
		zt_guiSizerAddItem(sizer, sizer_right, 3, padding);

		ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer_right);
		dgh->details = zt_guiMakeStaticText(scroll, "<color=8abbf8>Select an item on the left to view details on that item.</color>", ztGuiStaticTextBehaviorFlags_Fancy|ztGuiStaticTextBehaviorFlags_MonoSpaced, 2048);
		zt_guiItemSetAlign(dgh->details, ztAlign_Left|ztAlign_Top);
		zt_guiScrollContainerSetItem(scroll, dgh->details);

		zt_guiSizerAddItem(sizer_right, scroll, 1, padding);
	}

	_zt_guiDebugGuiHierarchyPopulate(dgh);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ZT_GUI_DEBUG_TEXVIEW_NAME           "Texture Viewer"
#define ZT_GUI_DEBUG_TEXVIEW_DROPDOWN_NAME  "Texture Viewer Dropdown"
#define ZT_GUI_DEBUG_TEXVIEW_DISPLAY_NAME   "Texture Viewer Display"

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugTextureViewerRefresh()
{
	ZT_PROFILE_GUI("_zt_guiDebugTextureViewerRefresh");

	ztGuiItem *dropdown = zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_DROPDOWN_NAME, zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_NAME));
	zt_assert(dropdown);

	zt_guiComboBoxClear(dropdown);

	zt_fiz(zt_game->textures_count) {
		if(zt_game->textures[i].renderer == ztRenderer_Invalid) {
			continue;
		}
		bool render_tex = false;
		bool cubemap_tex = false;
		switch (zt_currentRenderer())
		{
			case ztRenderer_OpenGL: {
				zt_openGLSupport(render_tex = ztgl_textureIsRenderTarget(zt_game->textures[i].gl_texture));
				zt_openGLSupport(cubemap_tex = zt_bitIsSet(zt_game->textures[i].gl_texture->flags, ztTextureGLFlags_CubeMap));
			} break;

			case ztRenderer_DirectX: {
				zt_directxSupport(render_tex = ztdx_textureIsRenderTarget(zt_game->textures[i].dx_texture));
				zt_directxSupport(cubemap_tex = zt_bitIsSet(zt_game->textures[i].dx_texture->flags, ztTextureDXFlags_CubeMap));
			} break;
		}
		zt_strMakePrintf(buffer, 256, "[%d] %d x %d %s", i, zt_game->textures[i].width, zt_game->textures[i].height, (render_tex ? "(render texture)" : (cubemap_tex ? "(cube map)" : "")));
		zt_guiComboBoxAppend(dropdown, buffer, (void*)i);
	}
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugTextureViewerLoadTexture(ztTextureID tex_id)
{
	ZT_PROFILE_GUI("_zt_guiDebugTextureViewerLoadTexture");

	if (tex_id == ztInvalidID || zt_game->textures[tex_id].renderer == ztRenderer_Invalid) {
		return;
	}

	ztGuiThemeSprite sprite;
	sprite.type = ztGuiThemeSpriteType_Sprite;
	sprite.s = zt_spriteMake(tex_id, ztVec2i(0, 0), ztVec2i(zt_game->textures[tex_id].width, zt_game->textures[tex_id].height));

	ztGuiItem *display = zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_DISPLAY_NAME, zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_NAME));

	ztVec2 scale = ztVec2::one;
	i32 max = zt_max(zt_game->textures[tex_id].width, zt_game->textures[tex_id].height);
	if (max > 1024) {
		scale.x = scale.y = 1.f / (max / 1024.f);
	}

	zt_guiSpriteDisplaySetSprite(display, &sprite, scale);
	zt_guiItemAutoSize(display);
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugTextureViewerOnRefresh, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugTextureViewerOnRefresh))
{
	_zt_guiDebugTextureViewerRefresh();
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugTextureViewerOnComboBox, ztInternal ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiDebugTextureViewerOnComboBox))
{
	_zt_guiDebugTextureViewerLoadTexture((ztTextureID)zt_guiComboBoxGetItemUserData(combobox, selected));
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugTextureViewer()
{
	{
		ztGuiItem *window = zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_NAME);
		if (window != nullptr) {
			_zt_guiDebugTextureViewerRefresh();
			zt_guiItemShow(window);
			return;
		}
	}

	ztGuiItem *window = zt_guiMakeWindow("Texture Viewer", ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowCollapse | ztGuiWindowBehaviorFlags_CloseHides);
	zt_guiItemSetName(window, ZT_GUI_DEBUG_TEXVIEW_NAME);

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztVec2 cam_ext = zt_cameraOrthoGetViewportSize(gm->gui_camera);

	zt_guiItemSetSize(window, ztVec2(cam_ext.x - 2, cam_ext.y - 2));

	ztGuiTheme *theme = zt_guiItemGetTheme(window);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	{
		zt_guiSizerSizeToParent(sizer);

		ztGuiItem *sizer_top = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		{
			zt_guiSizerAddItem(sizer, sizer_top, 0, 0);

			ztGuiItem *dropdown = zt_guiMakeComboBox(sizer_top, zt_elementsOf(zt_game->textures));
			zt_guiItemSetName(dropdown, ZT_GUI_DEBUG_TEXVIEW_DROPDOWN_NAME);
			zt_guiItemSetSize(dropdown, ztVec2(6, -1));
			zt_guiSizerAddItem(sizer_top, dropdown, 0, 3 / zt_pixelsPerUnit(), ztAlign_Top, ztGuiItemOrient_Horz);
			zt_guiComboBoxSetCallback(dropdown, _zt_guiDebugTextureViewerOnComboBox_FunctionID, nullptr);

			ztGuiItem *button = zt_guiMakeButton(sizer_top, "Refresh");
			zt_guiSizerAddItem(sizer_top, button, 0, 3 / zt_pixelsPerUnit());
			zt_guiButtonSetCallback(button, _zt_guiDebugTextureViewerOnRefresh_FunctionID);
		}

		ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer);
		ztGuiItem *display = zt_guiMakeSpriteDisplay(scroll, nullptr);
		zt_guiItemSetName(display, ZT_GUI_DEBUG_TEXVIEW_DISPLAY_NAME);
		zt_guiScrollContainerSetItem(scroll, display);

		zt_guiSizerAddItem(sizer, scroll, 1, 3 / zt_pixelsPerUnit());
	}

	_zt_guiDebugTextureViewerRefresh();
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#define ZT_GUI_DEBUG_PROFILER_NAME           "Profiler"

// ------------------------------------------------------------------------------------------------

struct ztDebugProfiler
{
	ztProfilerRenderState render_state;
	ztVec2                mouse_pos;
	bool                  mouse_clicked;
};

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerDisplayRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiDebugProfilerDisplayRender))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerDisplayRender");

	ztDebugProfiler *fps = (ztDebugProfiler*)item->functions.user_data;

	zt_profilerRender(draw_list, item->pos + offset, item->size, fps->mouse_pos, fps->mouse_clicked, &fps->render_state);
	fps->mouse_clicked = false;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerDisplayInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiDebugProfilerDisplayInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerDisplayInputMouse");

	ztDebugProfiler *fps = (ztDebugProfiler*)item->functions.user_data;

	fps->mouse_pos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
	fps->mouse_clicked = input_mouse->leftJustPressed();
	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugProfilerDisplayCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugProfiler()
{
	const char *window_name = "Profiler";

	{
		ztGuiItem *window = zt_guiItemFindByName(window_name);
		if (window != nullptr) {
			zt_guiItemShow(window, true);
			zt_guiItemBringToFront(window);
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugProfiler *prof = zt_mallocStructArena(ztDebugProfiler, gm->arena);
	*prof = {};
	prof->render_state = {};

	ztGuiItem *window = zt_guiMakeWindow("Profiler", ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);
	zt_guiItemSetSize(window, ztVec2(19, 10));

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Horz);
	zt_guiSizerSizeToParent(sizer);

	ztGuiItem *profiler = zt_guiMakePanel(sizer);
	zt_guiSizerAddItem(sizer, profiler, 1, 3 / zt_pixelsPerUnit());

	profiler->functions.user_data = prof;
	profiler->functions.render = _zt_guiDebugProfilerDisplayRender_FunctionID;
	profiler->functions.input_mouse = _zt_guiDebugProfilerDisplayInputMouse_FunctionID;
	profiler->functions.cleanup = _zt_guiDebugProfilerDisplayCleanup_FunctionID;
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ztInternal void _zt_guiDebugVariables()
{
	const char *window_name = "Variables";

	// we want a new variable window each time, as variables can be added

	ztGuiItem *window = zt_guiMakeWindow("Variables", ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);

	ztVec2 avg_size(4.5, .5f);

	r32 ttl_avg_height = zt_game->debug_vars_count * avg_size.y;

	ztVec2 extents = zt_cameraOrthoGetViewportSize(window->gm->gui_camera);

	int cols_needed = zt_max(1, zt_convertToi32Ceil(ttl_avg_height / (extents.y - 2)));
	ztVec2 needed_size = ztVec2::zero;
	while (true) {
		needed_size = ztVec2(avg_size.x * cols_needed, ttl_avg_height / cols_needed);
		if (needed_size.y > needed_size.x) {
			cols_needed += 1;
		}
		else break;
	}


	zt_guiItemSetSize(window, needed_size + ztVec2(0, .5f));

	ztGuiItem *sizer = zt_guiMakeColumnSizer(zt_guiWindowGetContentParent(window), cols_needed);
	zt_fiz(cols_needed) {
		zt_guiColumnSizerSetProp(sizer, i, 1);
	}

	zt_guiSizerSizeToParent(sizer);

	zt_fiz(zt_game->debug_vars_count) {
		ztGuiItem *item_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);

		zt_guiSizerAddStretcher(item_sizer, 0, 7 / zt_pixelsPerUnit());

		ztGuiItem *label = zt_guiMakeStaticText(item_sizer, zt_game->debug_vars[i].name);
		zt_guiItemSetAlign(label, ztAlign_Left);

		label->size.y = avg_size.y - ((3 / zt_pixelsPerUnit()) * 2);

		ztGuiItem *editor = nullptr;

		switch (zt_game->debug_vars[i].variable.type)
		{
			case ztVariant_bool: editor = zt_guiMakeCheckbox(item_sizer, " ", 0, &zt_game->debug_vars[i].variable.v_bool); break;
		}

		zt_guiSizerAddItem(item_sizer, label, 0, 0);
		zt_guiSizerAddStretcher(item_sizer, 1, 7 / zt_pixelsPerUnit());

		if (editor) {
			zt_guiSizerAddItem(item_sizer, editor, 0, 0);
		}

		zt_guiSizerAddStretcher(item_sizer, 0, 7 / zt_pixelsPerUnit());


		zt_guiSizerAddItem(sizer, item_sizer, 1, 3 / zt_pixelsPerUnit());
	}

	zt_guiItemSetPosition(window, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, ztVec2(1.f, -1.f));
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

enum
{
	ztGuiDebugMenu_FpsDisplay,
	ztGuiDebugMenu_Exit,

	ztGuiDebugMenu_Console,
	ztGuiDebugMenu_GuiHierarchy,
	ztGuiDebugMenu_TextureViewer,
	ztGuiDebugMenu_Profiler,

	ztGuiDebugMenu_Variables,
};

// ------------------------------------------------------------------------------------------------

ZT_FUNCTION_POINTER_REGISTER(_zt_guiInitDebugOnMenuItem, ztInternal ZT_FUNC_GUI_MENU_SELECTED(_zt_guiInitDebugOnMenuItem))
{
	switch (menu_item)
	{
		case ztGuiDebugMenu_FpsDisplay: {
			_zt_guiDebugFpsDisplay();
		} break;

		case ztGuiDebugMenu_Exit: {
			zt_game->quit_requested = true;
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

		case ztGuiDebugMenu_Profiler: {
			_zt_guiDebugProfiler();
		} break;

		case ztGuiDebugMenu_Variables: {
			_zt_guiDebugVariables();
		} break;
	};
}

// ------------------------------------------------------------------------------------------------

void zt_guiInitDebug(ztGuiManager *gm)
{
	ztGuiItem *menubar = zt_guiMakeMenuBar(nullptr);
	zt_guiItemSetName(menubar, ZT_DEBUG_MENUBAR_NAME);
	zt_guiMenuSetCallback(menubar, _zt_guiInitDebugOnMenuItem_FunctionID);

	{
		ztGuiItem *menu_options = zt_guiMakeMenu();
		zt_guiMenuAppend(menu_options, "Toggle FPS Display", ztGuiDebugMenu_FpsDisplay);
		zt_guiMenuAppend(menu_options, "Exit", ztGuiDebugMenu_Exit);
		zt_guiMenuAppendSubmenu(menubar, "Options", menu_options);
		zt_guiMenuSetCallback(menu_options, _zt_guiInitDebugOnMenuItem_FunctionID);
	}
	{
		ztGuiItem *menu_tools = zt_guiMakeMenu();
		zt_guiMenuAppend(menu_tools, "Console", ztGuiDebugMenu_Console);
		zt_guiMenuAppend(menu_tools, "GUI Hierarchy", ztGuiDebugMenu_GuiHierarchy);
		zt_guiMenuAppend(menu_tools, "Texture Viewer", ztGuiDebugMenu_TextureViewer);
		zt_guiMenuAppend(menu_tools, "Profiler", ztGuiDebugMenu_Profiler);
		zt_guiMenuAppendSubmenu(menubar, "Tools", menu_tools);
		zt_guiMenuSetCallback(menu_tools, _zt_guiInitDebugOnMenuItem_FunctionID);
	}
	{
		zt_guiMenuAppend(menubar, "Variables", ztGuiDebugMenu_Variables);
	}

	zt_guiItemSetPosition(menubar, ztAlign_Top, ztAnchor_Top);

	_zt_guiDebugFpsDisplay();

	zt_gui->console_window = nullptr;
	_zt_guiDebugConsole();
}

// ------------------------------------------------------------------------------------------------

void zt_guiDebugHide()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemHide(menubar);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiDebugShow()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemShow(menubar);
	}
}

// ------------------------------------------------------------------------------------------------

void zt_guiDebugToggle()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemShow(menubar, !zt_guiItemIsShowing(menubar));
	}
}

// ------------------------------------------------------------------------------------------------

void zt_debugLogGuiHierarchy(ztGuiItem *item)
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
				default: type = "Unknown"; break;
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

	if (item) {
		local::log(item, 0);
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

#endif // include guard
#endif // implementation
