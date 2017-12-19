/***************************************************************************************************************************************************************************************************
	file: zt_game_gui.h v 0.00 (active initial development)
	
	This software is dual-licensed to the public domain and under the following
	license: you are granted a perpetual, irrevocable license to copy, modify,
	publish, and distribute this file as you see fit.
	
	No warranty is offered or implied.  Use this at your own risk.
	
 ***************************************************************************************************************************************************************************************************
   
	Zero Tolerance Game GUI Library
   
	In exactly one c/cpp source file of your project, you must:

		#define ZT_GAME_GUI_IMPLEMENTATION
		#include "zt_game_gui.h"
    
 ***************************************************************************************************************************************************************************************************

    Options:


 ***************************************************************************************************************************************************************************************************

	Implimentation Options: (only used with ZT_GAME_GUI_IMPLEMENTATION #include)


 ***************************************************************************************************************************************************************************************************/

#ifndef __zt_game_gui_h_included__
#define __zt_game_gui_h_included__

#include "zt_tools.h"
#include "zt_game.h"

// ================================================================================================================================================================================================
// gui
// ================================================================================================================================================================================================

void zt_guiInitGlobalMemory(ztMemoryArena *arena);

// ================================================================================================================================================================================================

struct ztGuiManager;
struct ztGuiItem;

typedef i32 ztGuiTreeNodeID;

// ================================================================================================================================================================================================

enum ztGuiThemeSpriteType_Enum
{
	ztGuiThemeSpriteType_Invalid,
	ztGuiThemeSpriteType_SpriteNineSlice,
	ztGuiThemeSpriteType_Sprite,
};

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

struct ztGuiThemeButtonSprite
{
	ztGuiThemeSprite normal;
	ztGuiThemeSprite highlight;
	ztGuiThemeSprite pressed;
};

// ================================================================================================================================================================================================

void   zt_drawListAddGuiThemeSprite       (ztDrawList *draw_list, ztGuiThemeSprite *theme_sprite, const ztVec2& pos, const ztVec2& size);
void   zt_drawListAddGuiThemeButtonSprite (ztDrawList *draw_list, ztGuiThemeButtonSprite *theme_button_sprite, const ztVec2& pos, const ztVec2& size, bool highlighted, bool pressed);

ztVec2 zt_guiThemeSpriteGetSize           (ztGuiThemeSprite *sprite);
ztVec2 zt_guiThemeButtonSpriteGetSize     (ztGuiThemeButtonSprite *sprite);

// ================================================================================================================================================================================================

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
	_ztGIT(ztGuiItemType_CycleBox       ) \
	_ztGIT(ztGuiItemType_SpriteDisplay  ) \
	_ztGIT(ztGuiItemType_ProgressBar    ) \
	_ztGIT(ztGuiItemType_Sizer          ) \
	_ztGIT(ztGuiItemType_Spinner        ) \
	_ztGIT(ztGuiItemType_ListBox        ) \
	_ztGIT(ztGuiItemType_ColorPicker    ) \
	_ztGIT(ztGuiItemType_AnimCurve      ) \
	_ztGIT(ztGuiItemType_GradientPicker ) \
	_ztGIT(ztGuiItemType_Splitter       ) \
	_ztGIT(ztGuiItemType_Custom         )

// ================================================================================================================================================================================================

#define _ztGIT(TYPE)	TYPE,

enum ztGuiItemType_Enum
{
	_ztGuiItemTypeList
};

#undef _ztGIT

// ================================================================================================================================================================================================

enum ztGuiItemBehaviorFlags_Enum
{
	ztGuiItemBehaviorFlags_WantsFocus          = (1 << 0),
	ztGuiItemBehaviorFlags_WantsInput          = (1 << 1),
	ztGuiItemBehaviorFlags_HasOutlyingChildren = (1 << 2),
	ztGuiItemBehaviorFlags_ClipChildren        = (1 << 3),
	ztGuiItemBehaviorFlags_ClipContents        = (1 << 4),
	ztGuiItemBehaviorFlags_BringToFront        = (1 << 5),
	ztGuiItemBehaviorFlags_WantsKeyboardAlways = (1 << 6),
	ztGuiItemBehaviorFlags_LateUpdate          = (1 << 7),
};

// --------------------------

#define ztGuiItemBehaviorFlags_MaxBit            8


// ================================================================================================================================================================================================

enum ztGuiItemStates_Enum
{
	ztGuiItemStates_Visible    = 1,
	ztGuiItemStates_Dirty      = 2,
	ztGuiItemStates_Disabled   = 3,
	ztGuiItemStates_Locked     = 4,
	ztGuiItemStates_HasFocus   = 5,
	ztGuiItemStates_MouseOver  = 6,
	ztGuiItemStates_MouseClick = 7,
	ztGuiItemStates_Resized    = 8,
	ztGuiItemStates_PostRender = 9,

	ztGuiItemStates_MAX,

	ztGuiItemStates_USER       = 24,
};


// ================================================================================================================================================================================================

enum ztGuiThemeValue_Enum
{
	ztGuiThemeValue_r32_Padding,

	ztGuiThemeValue_i32_FontID,
	
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
	ztGuiThemeValue_r32_CollapsingPanelPaddingX,
	ztGuiThemeValue_r32_CollapsingPanelPaddingY,

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
	ztGuiThemeValue_r32_MenuSeparatorHeight,
	
	ztGuiThemeValue_r32_TreeIndent,
	ztGuiThemeValue_i32_TreeCollapseButtonAlign,
	ztGuiThemeValue_i32_TreeCollapseButtonAnchor,
	ztGuiThemeValue_i32_TreeCollapseButtonBehaviorFlags,
	
	ztGuiThemeValue_r32_ComboboxButtonW,

	ztGuiThemeValue_r32_CycleBoxButtonW,

	ztGuiThemeValue_r32_SplitterHandleW,
	ztGuiThemeValue_r32_SplitterPadding,
};

// ================================================================================================================================================================================================

struct ztGuiWindowState
{
	bool resizable;
	bool collapsable;
	bool is_collapsed;
};

// ================================================================================================================================================================================================

struct ztGuiPanelState
{
	bool display_background;
};

// ================================================================================================================================================================================================

struct ztGuiCollapsingPanelState
{
	bool is_collapsed;
};

// ================================================================================================================================================================================================

struct ztGuiButtonState
{
	bool      is_toggled;
	bool      is_pressed;
	ztSprite *icon_sprite;
};

// ================================================================================================================================================================================================

struct ztGuiTheme;

// ================================================================================================================================================================================================

#define ZT_FUNC_THEME_GET_RVALUE(name)	bool name(ztGuiTheme *theme, ztGuiItem *item, ztGuiThemeValue_Enum value, r32 *result)
typedef ZT_FUNC_THEME_GET_RVALUE(ztGuiThemeGetRValue_Func);

#define ZT_FUNC_THEME_GET_IVALUE(name) bool name(ztGuiTheme *theme, ztGuiItem *item, ztGuiThemeValue_Enum value, i32 *result)
typedef ZT_FUNC_THEME_GET_IVALUE(ztGuiThemeGetIValue_Func);

#define ZT_FUNC_THEME_UPDATE_ITEM(name) bool name(ztGuiTheme *theme, ztGuiItem *item)
typedef ZT_FUNC_THEME_UPDATE_ITEM(ztGuiThemeUpdateItem_Func);

#define ZT_FUNC_THEME_UPDATE_SUBITEM(name) bool name(ztGuiTheme *theme, ztGuiItem *item, ztGuiItem *subitem, void *data)
typedef ZT_FUNC_THEME_UPDATE_SUBITEM(ztGuiThemeUpdateSubitem_Func);

#define ZT_FUNC_THEME_SIZE_ITEM(name) bool name(ztGuiTheme *theme, ztGuiItem *item)
typedef ZT_FUNC_THEME_SIZE_ITEM(ztGuiThemeSizeItem_Func);

#define ZT_FUNC_THEME_RENDER_ITEM(name) bool name(ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos, bool *needs_postrender)
typedef ZT_FUNC_THEME_RENDER_ITEM(ztGuiThemeRenderItem_Func);

#define ZT_FUNC_THEME_POSTRENDER_ITEM(name) bool name(ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos)
typedef ZT_FUNC_THEME_POSTRENDER_ITEM(ztGuiThemePostRenderItem_Func);

#define ZT_FUNC_THEME_RENDER_PASS_BEGIN(name) void name(ztGuiTheme *theme, ztGuiItem *item, ztDrawList *draw_list)
typedef ZT_FUNC_THEME_RENDER_PASS_BEGIN(ztGuiThemeRenderPassBegin_Func);

#define ZT_FUNC_THEME_RENDER_PASS_END(name) void name(ztGuiTheme *theme, ztGuiItem *item, ztDrawList *draw_list)
typedef ZT_FUNC_THEME_RENDER_PASS_END(ztGuiThemeRenderPassEnd_Func);

// ================================================================================================================================================================================================

enum ztGuiThemeFlags_Enum
{
	ztGuiThemeFlags_SeparatePasses = (1<<0), // will call the pass function after each top level window is drawn
};

// ================================================================================================================================================================================================

struct ztGuiTheme
{
	void          *theme_data;
	i32            flags;

	ZT_FUNCTION_POINTER_VAR(get_rvalue,      ztGuiThemeGetRValue_Func);
	ZT_FUNCTION_POINTER_VAR(get_ivalue,      ztGuiThemeGetIValue_Func);
	ZT_FUNCTION_POINTER_VAR(update_item,     ztGuiThemeUpdateItem_Func);
	ZT_FUNCTION_POINTER_VAR(update_subitem,  ztGuiThemeUpdateSubitem_Func);
	ZT_FUNCTION_POINTER_VAR(size_item,       ztGuiThemeSizeItem_Func);
	ZT_FUNCTION_POINTER_VAR(render_item,     ztGuiThemeRenderItem_Func);
	ZT_FUNCTION_POINTER_VAR(postrender_item, ztGuiThemePostRenderItem_Func);

	ZT_FUNCTION_POINTER_VAR(pass_begin,      ztGuiThemeRenderPassBegin_Func);
	ZT_FUNCTION_POINTER_VAR(pass_end,        ztGuiThemeRenderPassEnd_Func);
};

// ================================================================================================================================================================================================

r32  zt_guiThemeGetRValue     (ztGuiTheme *theme, ztGuiThemeValue_Enum value, ztGuiItem *item);
i32  zt_guiThemeGetIValue     (ztGuiTheme *theme, ztGuiThemeValue_Enum value, ztGuiItem *item);
void zt_guiThemeUpdateItem    (ztGuiTheme *theme, ztGuiItem *item);
void zt_guiThemeUpdateSubitem (ztGuiTheme *theme, ztGuiItem *item, ztGuiItem *subitem, void *data = nullptr);
void zt_guiThemeSizeItem      (ztGuiTheme *theme, ztGuiItem *item);
void zt_guiThemeRender        (ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos);


// ================================================================================================================================================================================================

inline const char* zt_guiItemTypeName(ztGuiItemType_Enum type)
{
#	define _ztGIT(TYPE) case TYPE: return (#TYPE) + 14;
	switch (type)
	{
		_ztGuiItemTypeList
	}
	return "Unknown";
#	undef _ztGIT
}

// ================================================================================================================================================================================================

#define ZT_FUNC_GUI_ITEM_UPDATE(name) void name(ztGuiItem *item, r32 dt, void *user_data)
typedef ZT_FUNC_GUI_ITEM_UPDATE(zt_guiItemUpdate_Func);

#define ZT_FUNC_GUI_ITEM_RENDER(name) void name(ztGuiItem *item, ztDrawList *draw_list, ztGuiTheme *theme, const ztVec2& offset, bool enabled, void *user_data)
typedef ZT_FUNC_GUI_ITEM_RENDER(zt_guiItemRender_Func);

#define ZT_FUNC_GUI_ITEM_CLEANUP(name) void name(ztGuiItem *item, void *user_data)
typedef ZT_FUNC_GUI_ITEM_CLEANUP(zt_guiItemCleanup_Func);

#define ZT_FUNC_GUI_ITEM_BEST_SIZE(name) void name(ztGuiItem *item, ztVec2 *min_size, ztVec2 *max_size, ztVec2 *size, ztGuiTheme *theme, void *user_data)
typedef ZT_FUNC_GUI_ITEM_BEST_SIZE(zt_guiItemBestSize_Func);

#define ZT_FUNC_GUI_ITEM_INPUT_KEY(name) bool name(ztGuiItem *item, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[ZT_MAX_INPUT_KEYSTROKES], void *user_data)
typedef ZT_FUNC_GUI_ITEM_INPUT_KEY(zt_guiItemInputKey_Func);

#define ZT_FUNC_GUI_ITEM_INPUT_MOUSE(name) bool name(ztGuiItem *item, ztInputMouse *input_mouse, bool key_ctrl, bool key_alt, bool key_shift, void *user_data)
typedef ZT_FUNC_GUI_ITEM_INPUT_MOUSE(zt_guiItemInputMouse_Func);

// ================================================================================================================================================================================================

#define ZT_FUNC_GUI_BUTTON_PRESSED(name) void name(ztGuiItem *button, void *user_data)
typedef ZT_FUNC_GUI_BUTTON_PRESSED(zt_guiButtonPressed_Func);

#define ZT_FUNC_GUI_SLIDER_CHANGED(name) void name(ztGuiItem *slider, r32 value, void *user_data)
typedef ZT_FUNC_GUI_SLIDER_CHANGED(zt_guiSliderChanged_Func);

#define ZT_FUNC_GUI_SCROLLBAR_SCROLLED(name) void name(ztGuiItem *scrollbar, r32 value, void *user_data)
typedef ZT_FUNC_GUI_SCROLLBAR_SCROLLED(zt_guiScrollbarScrolled_Func);

#define ZT_FUNC_GUI_MENU_SELECTED(name) void name(ztGuiItem *menu, i32 menu_item, void *user_data)
typedef ZT_FUNC_GUI_MENU_SELECTED(zt_guiMenuSelected_Func);

#define ZT_FUNC_GUI_TEXTEDIT_KEY(name) void name(ztGuiItem *textedit, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[ZT_MAX_INPUT_KEYSTROKES], bool *should_process, void *user_data)
typedef ZT_FUNC_GUI_TEXTEDIT_KEY(zt_guiTextEditKey_Func);

#define ZT_FUNC_GUI_TREE_ITEM_SELECTED(name) void name(ztGuiItem *tree, ztGuiTreeNodeID node_id, void *user_data)
typedef ZT_FUNC_GUI_TREE_ITEM_SELECTED(zt_guiTreeItemSelected_Func);

#define ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(name) void name(ztGuiItem *combobox, int selected, void *user_data)
typedef ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(zt_guiComboBoxItemSelected_Func);

#define ZT_FUNC_GUI_SPINNER_VALUE_CHANGED(name) void name(ztGuiItem *spinner, int value, void *user_data)
typedef ZT_FUNC_GUI_SPINNER_VALUE_CHANGED(zt_guiSpinnerValueChanged_Func);

#define ZT_FUNC_GUI_LISTBOX_ITEM_SELECTED(name) void name(ztGuiItem *listbox, int selected, void *user_data)
typedef ZT_FUNC_GUI_LISTBOX_ITEM_SELECTED(zt_guiListBoxItemSelected_Func);

#define ZT_FUNC_GUI_CYCLEBOX_VALUE_CHANGED(name) void name(ztGuiItem *cyclebox, int value, void *user_data)
typedef ZT_FUNC_GUI_CYCLEBOX_VALUE_CHANGED(zt_guiCycleBoxValueChanged_Func);

#define ZT_FUNC_GUI_COLOR_PICKER_CHANGED(name) void name(ztGuiItem *color_picker, ztColor color_chosen, void *user_data)
typedef ZT_FUNC_GUI_COLOR_PICKER_CHANGED(zt_guiColorPickerChanged_Func);

#define ZT_FUNC_GUI_GRADIENT_PICKER_CHANGED(name) void name(ztGuiItem *gradient_picker, ztColorGradient2 *gradient_chosen, void *user_data)
typedef ZT_FUNC_GUI_GRADIENT_PICKER_CHANGED(zt_guiColorGradientChanged_Func);

#define ZT_FUNC_GUI_EDITOR_VALUE_CHANGED(name) void name(ztGuiItem *editor, void *user_data)
typedef ZT_FUNC_GUI_EDITOR_VALUE_CHANGED(zt_guiEditorValueChanged_Func);

// ================================================================================================================================================================================================

struct ztGuiItemFunctions
{
	ZT_FUNCTION_POINTER_VAR(update,      zt_guiItemUpdate_Func);
	ZT_FUNCTION_POINTER_VAR(render,      zt_guiItemRender_Func);
	ZT_FUNCTION_POINTER_VAR(cleanup,     zt_guiItemCleanup_Func);
	ZT_FUNCTION_POINTER_VAR(best_size,   zt_guiItemBestSize_Func);
	ZT_FUNCTION_POINTER_VAR(input_key,   zt_guiItemInputKey_Func);
	ZT_FUNCTION_POINTER_VAR(input_mouse, zt_guiItemInputMouse_Func);

	void *user_data;
};

// ================================================================================================================================================================================================

enum ztGuiWindowBehaviorFlags_Enum
{
	ztGuiWindowBehaviorFlags_ShowTitle     = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiWindowBehaviorFlags_AllowDrag     = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
	ztGuiWindowBehaviorFlags_AllowResize   = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
	ztGuiWindowBehaviorFlags_AllowClose    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 4)),
	ztGuiWindowBehaviorFlags_AllowCollapse = (1 << (ztGuiItemBehaviorFlags_MaxBit + 5)),
	ztGuiWindowBehaviorFlags_CloseHides    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 6)),
	ztGuiWindowBehaviorFlags_Modal         = (1 << (ztGuiItemBehaviorFlags_MaxBit + 7)),

	ztGuiWindowBehaviorFlags_Default = ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_AllowCollapse,
};

#define ztGuiWindowBehaviorFlags_MaxBit   (ztGuiItemBehaviorFlags_MaxBit + 7)


// ================================================================================================================================================================================================

enum ztGuiPanelBehaviorFlags_Enum
{
	ztGuiPanelBehaviorFlags_AllowDrag      = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiPanelBehaviorFlags_DrawBackground = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

#define ztGuiPanelBehaviorFlags_MaxBit   (ztGuiItemBehaviorFlags_MaxBit + 2)


// ================================================================================================================================================================================================

enum ztGuiMenuBehaviorFlags_Enum
{
	ztGuiMenuBehaviorFlags_FreeOnClose = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
};

// ================================================================================================================================================================================================

enum ztGuiStaticTextBehaviorFlags_Enum
{
	ztGuiStaticTextBehaviorFlags_Fancy      = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiStaticTextBehaviorFlags_MonoSpaced = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

// ================================================================================================================================================================================================

enum ztGuiButtonBehaviorFlags_Enum
{
	ztGuiButtonBehaviorFlags_NoBackground = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiButtonBehaviorFlags_OnPressDip   = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

// ================================================================================================================================================================================================

enum ztGuiCheckboxBehaviorFlags_Enum
{
	ztGuiCheckboxBehaviorFlags_RightText = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
};

// ================================================================================================================================================================================================

enum ztGuiRadioButtonFlags_Enum
{
	ztGuiRadioButtonBehaviorFlags_RightText = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
};

#define ztGuiButtonBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 3)


// ================================================================================================================================================================================================

enum ztGuiScrollContainerBehaviorFlags_Enum
{
	ztGuiScrollContainerBehaviorFlags_ShowScrollVert = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiScrollContainerBehaviorFlags_ShowScrollHorz = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
	ztGuiScrollContainerBehaviorFlags_StretchVert    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)),
	ztGuiScrollContainerBehaviorFlags_StretchHorz    = (1 << (ztGuiItemBehaviorFlags_MaxBit + 4)),
	ztGuiScrollContainerBehaviorFlags_NoBackground   = (1 << (ztGuiItemBehaviorFlags_MaxBit + 5)),
};

#define ztGuiScrollContainerBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 5)


// ================================================================================================================================================================================================

enum ztGuiTextEditBehaviorFlags_Enum
{
	ztGuiTextEditBehaviorFlags_MultiLine = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiTextEditBehaviorFlags_ReadOnly  = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

#define ztGuiTextEditBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 2)


// ================================================================================================================================================================================================

enum ztGuiTreeItemFlags_Enum
{
	ztGuiTreeItemFlags_StretchToMax = (1<<0),
};

// ================================================================================================================================================================================================

enum ztGuiCycleBoxBehaviorFlags_Enum
{
	ztGuiCycleBoxBehaviorFlags_HideInvalidButton = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiCycleBoxBehaviorFlags_Infinite          = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

#define ztGuiCycleBoxBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 2)

// ================================================================================================================================================================================================

enum ztGuiListBoxBehaviorFlags_Enum
{
	ztGuiListBoxBehaviorFlags_MultiSelect        = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiListBoxBehaviorFlags_AlternateRowColor  = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
	ztGuiListBoxBehaviorFlags_AlwaysCallCallback = (1 << (ztGuiItemBehaviorFlags_MaxBit + 3)), // will call callback even when set using function (not just on user input)
	ztGuiListBoxBehaviorFlags_UseFancyText       = (1 << (ztGuiItemBehaviorFlags_MaxBit + 4)),
};

#define ztGuiListBoxBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 4)


// ================================================================================================================================================================================================

enum ztGuiListGridBehaviorFlags_Enum
{
	ztGuiListGridBehaviorFlags_MultiSelect = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
};

#define ztGuiListGridBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 1)


// ================================================================================================================================================================================================

enum ztGuiColorPickerBehaviorFlags_Enum
{
	ztGuiColorPickerBehaviorFlags_LiveEdit = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiColorPickerBehaviorFlags_IncludesAlpha = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

#define ztGuiColorPickerBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 2)


// ================================================================================================================================================================================================

enum ztGuiGradientPickerBehaviorFlags_Enum
{
	ztGuiGradientPickerBehaviorFlags_LiveEdit      = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
};

#define ztGuiGradientPickerBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 1)


// ================================================================================================================================================================================================

enum ztGuiAnimCurveBehaviorFlags_Enum
{
	ztGuiAnimCurveBehaviorFlags_LiveEdit     = (1 << (ztGuiItemBehaviorFlags_MaxBit + 1)),
	ztGuiAnimCurveBehaviorFlags_AdjustValues = (1 << (ztGuiItemBehaviorFlags_MaxBit + 2)),
};

#define ztGuiAnimCurveBehaviorFlags_MaxBit (ztGuiItemBehaviorFlags_MaxBit + 2)


// ================================================================================================================================================================================================

enum ztGuiItemOrient_Enum
{
	ztGuiItemOrient_Horz = (1 << 1),
	ztGuiItemOrient_Vert = (1 << 2),
};

// ================================================================================================================================================================================================

enum ztGuiColumnSizerType_Enum
{
	ztGuiColumnSizerType_FillRow,
	ztGuiColumnSizerType_FillColumn,
};

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztGuiManagerStringPool_Enum
{
	ztGuiManagerStringPool_None,
	ztGuiManagerStringPool_Minimal,
	ztGuiManagerStringPool_Standard,
	ztGuiManagerStringPool_Heavy,

	ztGuiManagerStringPool_MAX,
};

// ================================================================================================================================================================================================


ztGuiManager   *zt_guiManagerMake                      (ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena, ztGuiManagerStringPool_Enum string_pool = ztGuiManagerStringPool_Standard);
void            zt_guiManagerFree                      (ztGuiManager *gui_manager);

bool            zt_guiManagerHandleInput               (ztGuiManager *gui_manager, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[ZT_MAX_INPUT_KEYSTROKES], ztInputMouse *input_mouse);
void            zt_guiManagerRender                    (ztGuiManager *gui_manager, ztDrawList *draw_list, r32 dt);

void            zt_guiSetActiveManager                 (ztGuiManager *gui_manager);
ztGuiManager   *zt_guiGetActiveManager                 ();

void            zt_guiManagerSetKeyboardFocus          (ztGuiManager *gui_manager, bool keyboard_focus = true);
bool            zt_guiManagerHasKeyboardFocus          (ztGuiManager *gui_manager);

bool            zt_guiManagerMouseOverGui              (ztGuiManager *gui_manager);

// ================================================================================================================================================================================================

ztGuiItem       *zt_guiMakeWindow                      (const char *title, i32 behavior_flags = ztGuiWindowBehaviorFlags_Default);
ztGuiItem       *zt_guiMakeScrollWindow                (const char *title, i32 scroll_dir, i32 behavior_flags = ztGuiWindowBehaviorFlags_Default); // set the size of the content item
ztGuiItem       *zt_guiMakePanel                       (ztGuiItem *parent, i32 behavior_flags = 0, void *user_data = nullptr, ztMemoryArena *arena = nullptr); // user data is freed by the panel item
ztGuiItem       *zt_guiMakeCollapsingPanel             (ztGuiItem *parent, const char *label);
ztGuiItem       *zt_guiMakeStaticText                  (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, i32 max_chars = 64);
ztGuiItem       *zt_guiMakeButton                      (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem       *zt_guiMakeToggleButton                (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem       *zt_guiMakeCheckbox                    (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem       *zt_guiMakeRadioButton                 (ztGuiItem *parent, const char *label, i32 behavior_flags = 0, bool *live_value = nullptr);
ztGuiItem       *zt_guiMakeSlider                      (ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItem       *zt_guiMakeScrollbar                   (ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value = nullptr);
ztGuiItem       *zt_guiMakeScrollContainer             (ztGuiItem *parent, i32 behavior_flags = 0);
ztGuiItem       *zt_guiMakeTextEdit                    (ztGuiItem *parent, const char *value, i32 behavior_flags = 0, i32 buffer_size = 1024);
ztGuiItem       *zt_guiMakeMenu                        (ztGuiItem *parent, i32 behavior_flags = 0);
ztGuiItem       *zt_guiMakeMenuBar                     (ztGuiItem *parent);
ztGuiItem       *zt_guiMakeTree                        (ztGuiItem *parent, i32 max_items);
ztGuiItem       *zt_guiMakeComboBox                    (ztGuiItem *parent, i32 max_items);
ztGuiItem       *zt_guiMakeSpriteDisplay               (ztGuiItem *parent, ztGuiThemeSprite *sprite, const ztVec2& scale = ztVec2::one, const ztVec4& bgcolor = ztVec4::zero);
ztGuiItem       *zt_guiMakeSpriteDisplay               (ztGuiItem *parent, ztSpriteAnimController *sprite_anim_controller, const ztVec2& scale = ztVec2::one, const ztVec4& bgcolor = ztVec4::zero);
ztGuiItem       *zt_guiMakeSpinner                     (ztGuiItem *parent, int *live_value = nullptr);
ztGuiItem       *zt_guiMakeListBox                     (ztGuiItem *parent, i32 behavior_flags = 0, i32 max_items = 128);
ztGuiItem       *zt_guiMakeColorPicker                 (ztGuiItem *parent, ztColor color, i32 behavior_flags = 0, ztColor *live_value = nullptr);
ztGuiItem       *zt_guiMakeGradientPicker              (ztGuiItem *parent, ztColorGradient2 *gradient, i32 behavior_flags = 0, ztColorGradient2 *live_value = nullptr);
ztGuiItem       *zt_guiMakeAnimCurve                   (ztGuiItem *parent, ztAnimCurve *curve, i32 behavior_flags = 0, ztAnimCurve *live_value = nullptr);
ztGuiItem       *zt_guiMakeSizer                       (ztGuiItem *parent, ztGuiItemOrient_Enum orient, bool size_to_parent = true);
ztGuiItem       *zt_guiMakeColumnSizer                 (ztGuiItem *parent, int columns, ztGuiColumnSizerType_Enum type, bool size_to_parent = true);
ztGuiItem       *zt_guiMakeWrapSizer                   (ztGuiItem *parent, ztGuiItemOrient_Enum orient, bool size_to_parent = true);
ztGuiItem       *zt_guiMakeSplitter                    (ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 split_percent);

// ================================================================================================================================================================================================

ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, r32 *value, r32 min, r32 max, r32 step);
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, i32 *value, i32 min, i32 max, i32 step);
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, ztVec2 *value, ztVec2 min, ztVec2 max, r32 step = .1f, bool label_above = true, const char *label_x = "X", const char *label_y = "Y");
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, ztVec3 *value, ztVec3 min, ztVec3 max, r32 step = .1f, bool label_above = true, const char *label_x = "X", const char *label_y = "Y", const char *label_z = "Z");
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, ztVec4 *value, ztVec4 min, ztVec4 max, r32 step = .1f, bool label_above = true, const char *label_x = "X", const char *label_y = "Y", const char *label_z = "Z", const char *label_w = "W");
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, ztVec2i *value, ztVec2i min, ztVec2i max, i32 step = 1, bool label_above = true, const char *label_x = "X", const char *label_y = "Y");
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, ztVec3i *value, ztVec3i min, ztVec3i max, i32 step = 1, bool label_above = true, const char *label_x = "X", const char *label_y = "Y", const char *label_z = "Z");
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, const char *label, ztVec4i *value, ztVec4i min, ztVec4i max, i32 step = 1, bool label_above = true, const char *label_x = "X", const char *label_y = "Y", const char *label_z = "Z", const char *label_w = "W");

ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, ztParticleVariableReal *variable, r32 def, r32 min, r32 max, r32 step);
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, ztParticleVariableColor *variable);
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, ztParticleVariableVec2 *variable, ztVec2 def, ztVec2 min, ztVec2 max, r32 step, bool allow_sync);
ztGuiItem       *zt_guiMakeEditor                      (ztGuiItem *parent, ztParticleVariableVec3 *variable, ztVec3 def, ztVec3 min, ztVec3 max, r32 step, bool allow_sync);


// ================================================================================================================================================================================================

void             zt_guiItemFree                        (ztGuiItem *item_id);
void             zt_guiItemQueueFree                   (ztGuiItem *item_id);

void             zt_guiItemSetSize                     (ztGuiItem *item, const ztVec2& size);
void             zt_guiItemSetMinSize                  (ztGuiItem *item, const ztVec2& size);
void             zt_guiItemAutoSize                    (ztGuiItem *item);
void             zt_guiItemSetPosition                 (ztGuiItem *item, const ztVec2& pos);
void             zt_guiItemSetPosition                 (ztGuiItem *item, i32 align_flags, i32 anchor_flags, ztVec2 offset = ztVec2::zero);

void             zt_guiItemSetName                     (ztGuiItem *item, const char *name);
void             zt_guiItemSetLabel                    (ztGuiItem *item, const char *label);
void             zt_guiItemSetTooltip                  (ztGuiItem *item, const char *tooltip);
void             zt_guiItemSetThemeType                (ztGuiItem *item, const char *theme_type);
void             zt_guiItemSetTheme                    (ztGuiItem *item, ztGuiTheme *theme);
void             zt_guiItemSetColor                    (ztGuiItem *item, const ztVec4& color);

void             zt_guiItemSetCustomFlags              (ztGuiItem *item, i32 flags);

//               this is never used internally, so it can be set for any item without worry
void             zt_guiItemSetUserData                 (ztGuiItem *item, void *user_data);

ztString         zt_guiItemGetName                     (ztGuiItem *item);
ztString         zt_guiItemGetLabel                    (ztGuiItem *item);
ztString         zt_guiItemGetTooltip                  (ztGuiItem *item);
ztString         zt_guiItemGetThemeType                (ztGuiItem *item);
void            *zt_guiItemGetUserData                 (ztGuiItem *item);
ztVec2           zt_guiItemGetSize                     (ztGuiItem *item);
ztVec2           zt_guiItemGetPosition                 (ztGuiItem *item);
i32              zt_guiItemGetCustomFlags               (ztGuiItem *item);

void             zt_guiItemSetAlign                    (ztGuiItem *item, i32 align_flags);
i32              zt_guiItemGetAlign                    (ztGuiItem *item);

bool             zt_guiItemIsShowing                   (ztGuiItem *item);

void             zt_guiItemShow                        (ztGuiItem *item, bool show = true);
void             zt_guiItemHide                        (ztGuiItem *item);
bool             zt_guiItemIsVisible                   (ztGuiItem *item);

void             zt_guiItemEnable                      (ztGuiItem *item, bool enable = true);
void             zt_guiItemDisable                     (ztGuiItem *item);
bool             zt_guiItemIsEnabled                   (ztGuiItem *item);

void             zt_guiItemBringToFront                (ztGuiItem *item);

ztGuiItem       *zt_guiItemGetTopLevelParent           (ztGuiItem *item);

//               determine if the child is a descendent of the parent
bool             zt_guiItemIsChildOf                   (ztGuiItem *parent, ztGuiItem *child);

ztGuiItem       *zt_guiItemFindByName                  (const char *name, ztGuiItem *parent = nullptr);
ztGuiItem       *zt_guiItemFindByType                  (ztGuiItemType_Enum type, ztGuiItem *parent = nullptr, ztGuiItem *find_after = nullptr);

ztVec2           zt_guiItemPositionLocalToScreen       (ztGuiItem *item, const ztVec2& pos);
ztVec2           zt_guiItemPositionScreenToLocal       (ztGuiItem *item, const ztVec2& pos);

void             zt_guiItemSetFocus                    (ztGuiItem *item, ztGuiItem **prev_focus_item = nullptr);

ztGuiTheme      *zt_guiItemGetTheme                    (ztGuiItem *item);

void             zt_guiItemLock                        (ztGuiItem *item);
void             zt_guiItemUnlock                      (ztGuiItem *item);

void             zt_guiItemReparent                    (ztGuiItem *item, ztGuiItem *new_parent);

//               determine if there is another window below this one in z-order and is entirely or partially covered by this one
bool             zt_guiItemTopLevelIsOverlapping       (ztGuiItem *item);

// ================================================================================================================================================================================================

void             zt_guiWindowSetMenuBar                (ztGuiItem *window, ztGuiItem *menubar);
ztGuiItem       *zt_guiWindowGetContentParent          (ztGuiItem *window);

// ================================================================================================================================================================================================

ztGuiItem       *zt_guiCollapsingPanelGetContentParent (ztGuiItem *panel);
void             zt_guiCollapsingPanelCollapse         (ztGuiItem *panel);
void             zt_guiCollapsingPanelExpand           (ztGuiItem *panel);

// ================================================================================================================================================================================================

//               used for button and toggle button
void             zt_guiButtonSetIcon                   (ztGuiItem *button, ztSprite *icon);
void             zt_guiButtonSetTextPosition           (ztGuiItem *button, i32 align_flags);
void             zt_guiButtonSetCallback               (ztGuiItem *button, ZT_FUNCTION_POINTER_VAR(callback, zt_guiButtonPressed_Func), void *user_data = nullptr);

// ================================================================================================================================================================================================

bool             zt_guiToggleButtonGetValue            (ztGuiItem *button);
void             zt_guiToggleButtonSetValue            (ztGuiItem *button, bool value);

// ================================================================================================================================================================================================

bool             zt_guiCheckboxGetValue                (ztGuiItem *checkbox);
void             zt_guiCheckboxSetValue                (ztGuiItem *checkbox, bool value);

// ================================================================================================================================================================================================

bool             zt_guiRadioButtonGetValue             (ztGuiItem *radio);
void             zt_guiRadioButtonSetValue             (ztGuiItem *radio, bool value);

// ================================================================================================================================================================================================

r32              zt_guiSliderGetValue                  (ztGuiItem *slider);
void             zt_guiSliderSetValue                  (ztGuiItem *slider, r32 value);
void             zt_guiSliderSetCallback               (ztGuiItem *slider, ZT_FUNCTION_POINTER_VAR(callback, zt_guiSliderChanged_Func), void *user_data);

// ================================================================================================================================================================================================

r32              zt_guiScrollbarGetValue               (ztGuiItem *scrollbar);
void             zt_guiScrollbarSetValue               (ztGuiItem *scrollbar, r32 value);
void             zt_guiScrollbarSetSteps               (ztGuiItem *scrollbar, r32 step_single, r32 step_page);
void             zt_guiScrollbarSetStepsAndPercent     (ztGuiItem *scrollbar, r32 step_single, r32 step_page, r32 percent);
bool             zt_guiScrollbarStepNeg                (ztGuiItem *scrollbar);
bool             zt_guiScrollbarStepPageNeg            (ztGuiItem *scrollbar);
bool             zt_guiScrollbarStepPos                (ztGuiItem *scrollbar);
bool             zt_guiScrollbarStepPagePos            (ztGuiItem *scrollbar);

//               what percent of the total scrolled area is current displayed
void             zt_guiScrollbarSetPercent             (ztGuiItem *scrollbar, r32 percent);
void             zt_guiScrollbarSetCallback            (ztGuiItem *scrollbar, ZT_FUNCTION_POINTER_VAR(callback, zt_guiScrollbarScrolled_Func), void *user_data);


// ================================================================================================================================================================================================

void             zt_guiScrollContainerSetItem          (ztGuiItem *scroll, ztGuiItem *internal_item);
void             zt_guiScrollContainerResetScroll      (ztGuiItem *scroll);
void             zt_guiScrollContainerSetScroll        (ztGuiItem *scroll, ztGuiItemOrient_Enum orient, r32 value);
r32              zt_guiScrollContainerGetScroll        (ztGuiItem *scroll, ztGuiItemOrient_Enum orient);

// ================================================================================================================================================================================================

int              zt_guiTextEditGetValue                (ztGuiItem *text, char *buffer, int buffer_len);
void             zt_guiTextEditSetValue                (ztGuiItem *text, const char *value);
void             zt_guiTextEditSetSelection            (ztGuiItem *text, int sel_beg, int sel_end);
void             zt_guiTextEditGetSelection            (ztGuiItem *text, int *sel_beg, int *sel_end);
void             zt_guiTextEditSelectAll               (ztGuiItem *text);
int              zt_guiTextEditGetCursorPos            (ztGuiItem *text);
void             zt_guiTextEditSetCursorPos            (ztGuiItem *text, int cursor_pos);
void             zt_guiTextEditSetCallback             (ztGuiItem *text, ZT_FUNCTION_POINTER_VAR(on_key, zt_guiTextEditKey_Func), void *user_data = nullptr);
ztVec2           zt_guiTextEditGetCharacterPos         (ztGuiItem *item, int ch, bool bottom_right);

// ================================================================================================================================================================================================

void             zt_guiMenuAppend                      (ztGuiItem *menu, const char *label, i32 id, void *user_data = nullptr, ztSprite *icon = nullptr);
void             zt_guiMenuAppendSubmenu               (ztGuiItem *menu, const char *label, ztGuiItem *submenu, ztSprite *icon = nullptr);
void             zt_guiMenuAppendSeparator             (ztGuiItem *menu);
void             zt_guiMenuPopupAtItem                 (ztGuiItem *menu, ztGuiItem *item, i32 align_flags, const ztVec2& offset = ztVec2::zero);
void             zt_guiMenuPopupAtPosition             (ztGuiItem *menu, const ztVec2& pos);
bool             zt_guiMenuGetSelected                 (ztGuiItem *menu, i32 *selected_id);
void             zt_guiMenuSetCallback                 (ztGuiItem *menu, ZT_FUNCTION_POINTER_VAR(on_selected, zt_guiMenuSelected_Func));
void             zt_guiMenuClear                       (ztGuiItem *menu);

// ================================================================================================================================================================================================

ztGuiTreeNodeID  zt_guiTreeAppend                      (ztGuiItem *tree, const char *item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID, i32 flags = 0);
ztGuiTreeNodeID  zt_guiTreeAppend                      (ztGuiItem *tree, ztGuiItem *item, void *user_data, ztGuiTreeNodeID parent_id = ztInvalidID, i32 flags = 0);
ztGuiTreeNodeID  zt_guiTreeGetSelected                 (ztGuiItem *tree);
void             zt_guiTreeSetSelected                 (ztGuiItem *tree, ztGuiTreeNodeID node);
ztGuiTreeNodeID  zt_guiTreeGetRoot                     (ztGuiItem *tree);
ztGuiItem       *zt_guiTreeGetNodeItem                 (ztGuiItem *tree, ztGuiTreeNodeID node);
void            *zt_guiTreeGetNodeUserData             (ztGuiItem *tree, ztGuiTreeNodeID node);
void             zt_guiTreeSetCallback                 (ztGuiItem *tree, ZT_FUNCTION_POINTER_VAR(on_item_sel, zt_guiTreeItemSelected_Func), void *user_data);
void             zt_guiTreeCollapseNode                (ztGuiItem *tree, ztGuiTreeNodeID node);
void             zt_guiTreeExpandNode                  (ztGuiItem *tree, ztGuiTreeNodeID node);
void             zt_guiTreeClear                       (ztGuiItem *tree);

// ================================================================================================================================================================================================

void             zt_guiComboBoxSetContents             (ztGuiItem *combobox, const char **contents, int contents_count, int active);
void             zt_guiComboBoxClear                   (ztGuiItem *combobox);
void             zt_guiComboBoxAppend                  (ztGuiItem *combobox, const char *content, void *user_data = nullptr);
void             zt_guiComboBoxAppendWithIcon          (ztGuiItem *combobox, const char *content, ztSprite *sprite, void *user_data = nullptr);
int              zt_guiComboBoxGetSelected             (ztGuiItem *combobox);
void             zt_guiComboBoxSetSelected             (ztGuiItem *combobox, int selected);
int              zt_guiComboBoxGetItemCount            (ztGuiItem *combobox);
int              zt_guiComboBoxGetItemText             (ztGuiItem *combobox, int index, char* buffer, int buffer_len);
void            *zt_guiComboBoxGetItemUserData         (ztGuiItem *combobox, int index);
void             zt_guiComboBoxSetCallback             (ztGuiItem *combobox, ZT_FUNCTION_POINTER_VAR(on_item_sel, zt_guiComboBoxItemSelected_Func), void *user_data);

// ================================================================================================================================================================================================

ztGuiItem       *zt_guiMakeCycleBox                    (ztGuiItem *parent, i32 max_items, i32 behavior_flags = 0, int *live_value = nullptr);
void             zt_guiCycleBoxSetContents             (ztGuiItem *cyclebox, const char **contents, int contents_count, int active);
void             zt_guiCycleBoxClear                   (ztGuiItem *cyclebox);
void             zt_guiCycleBoxAppend                  (ztGuiItem *cyclebox, const char *content, void *user_data = nullptr);
int              zt_guiCycleBoxGetSelected             (ztGuiItem *cyclebox);
void             zt_guiCycleBoxSetSelected             (ztGuiItem *cyclebox, int selected);
int              zt_guiCycleBoxGetItemCount            (ztGuiItem *cyclebox);
int              zt_guiCycleBoxGetItemText             (ztGuiItem *cyclebox, int index, char* buffer, int buffer_len);
void            *zt_guiCycleBoxGetItemUserData         (ztGuiItem *cyclebox, int index);
void             zt_guiCycleBoxSetCallback             (ztGuiItem *cyclebox, ZT_FUNCTION_POINTER_VAR(on_item_change, zt_guiCycleBoxValueChanged_Func), void *user_data);

// ================================================================================================================================================================================================

void             zt_guiSpriteDisplaySetSprite          (ztGuiItem *item_id, ztGuiThemeSprite *sprite, const ztVec2& scale = ztVec2::one, const ztVec4& bgcolor = ztVec4::zero);

// ================================================================================================================================================================================================

int              zt_guiSpinnerGetValue                 (ztGuiItem *spinner);	// -1 or +1
void             zt_guiSpinnerSetCallback              (ztGuiItem *spinner, ZT_FUNCTION_POINTER_VAR(on_value_changed, zt_guiSpinnerValueChanged_Func), void *user_data);
void             zt_guiSpinnerTickUp                   (ztGuiItem *spinner);
void             zt_guiSpinnerTickDown                 (ztGuiItem *spinner);

// ================================================================================================================================================================================================

int              zt_guiListBoxAppend                   (ztGuiItem *listbox, ztGuiItem *item, void *user_data, bool size_width = false);
int              zt_guiListBoxAppend                   (ztGuiItem *listbox, const char *item, void *user_data);
void             zt_guiListBoxClear                    (ztGuiItem *listbox);
int              zt_guiListBoxGetActiveItem            (ztGuiItem *listbox);
int              zt_guiListBoxGetSelectedCount         (ztGuiItem *listbox);
int              zt_guiListBoxGetSelected              (ztGuiItem *listbox, int which = 0);
bool             zt_guiListBoxIsSelected               (ztGuiItem *listbox, int item_idx);
int              zt_guiListBoxSetSelected              (ztGuiItem *listbox, int item_idx, bool append_to_selection = false, bool force_visible = true);
int              zt_guiListBoxGetCount                 (ztGuiItem *listbox);
ztGuiItem       *zt_guiListBoxGetItem                  (ztGuiItem *listbox, int item_idx);
void            *zt_guiListBoxGetItemUserData          (ztGuiItem *listbox, int item_idx);
void             zt_guiListBoxShowItem                 (ztGuiItem *listbox, int item_idx, bool show = true);
void             zt_guiListBoxHideItem                 (ztGuiItem *listbox, int item_idx);
bool             zt_guiListBoxIsItemShown              (ztGuiItem *listbox, int item_idx);
void             zt_guiListBoxScrollToItem             (ztGuiItem *listbox, int item_idx);
void             zt_guiListBoxSetHeaderItem            (ztGuiItem *listbox, ztGuiItem *header);
void             zt_guiListBoxSetCallback              (ztGuiItem *listbox, ZT_FUNCTION_POINTER_VAR(function_id, zt_guiListBoxItemSelected_Func), void *user_data = nullptr);
void             zt_guiListBoxRefresh                  (ztGuiItem *listbox);
void             zt_guiListBoxRemoveItem               (ztGuiItem *listbox, int item);

// ================================================================================================================================================================================================

void             zt_guiColorPickerSetCallback          (ztGuiItem *color_picker, ZT_FUNCTION_POINTER_VAR(callback, zt_guiColorPickerChanged_Func), void *user_data);
void             zt_guiColorPickerSetLiveValue         (ztGuiItem *color_picker, ztColor *live_value);

// ================================================================================================================================================================================================

void             zt_guiGradientPickerSetCallback       (ztGuiItem *gradient_picker, ZT_FUNCTION_POINTER_VAR(callback, zt_guiColorGradientChanged_Func), void *user_data);
void             zt_guiGradientPickerSetLiveValue      (ztGuiItem *gradient_picker, ztColorGradient2 *live_value);

// ================================================================================================================================================================================================

void             zt_guiAnimCurveSetCallback            (ztGuiItem *anim_curve, ZT_FUNCTION_POINTER_VAR(callback, zt_guiEditorValueChanged_Func), void *user_data);
void             zt_guiAnimCurveSetLiveValue           (ztGuiItem *anim_curve, ztAnimCurve *live_value);

// ================================================================================================================================================================================================

void             zt_guiEditorSetToMin                  (ztGuiItem *editor);
void             zt_guiEditorSetToMax                  (ztGuiItem *editor);
void             zt_guiEditorSetToValue                (ztGuiItem *editor, r32 value);
void             zt_guiEditorSetToValue                (ztGuiItem *editor, i32 value);
void             zt_guiEditorSetToValue                (ztGuiItem *editor, ztVec2 value);
void             zt_guiEditorSetToValue                (ztGuiItem *editor, ztVec3 value);
void             zt_guiEditorSetToValue                (ztGuiItem *editor, ztVec4 value);
void             zt_guiEditorSetToValue                (ztGuiItem *editor, ztVec2i value);
void             zt_guiEditorReassign                  (ztGuiItem *editor, r32 *value);
void             zt_guiEditorReassign                  (ztGuiItem *editor, i32 *value);
void             zt_guiEditorReassign                  (ztGuiItem *editor, ztVec2 *value);
void             zt_guiEditorReassign                  (ztGuiItem *editor, ztVec3 *value);
void             zt_guiEditorReassign                  (ztGuiItem *editor, ztVec4 *value);
void             zt_guiEditorReassign                  (ztGuiItem *editor, ztVec2i *value);
void             zt_guiEditorSetCallback               (ztGuiItem *editor, ZT_FUNCTION_POINTER_VAR(function_id, zt_guiEditorValueChanged_Func), void *user_data);

// ================================================================================================================================================================================================

void             zt_guiSizerAddItem                    (ztGuiItem *sizer, ztGuiItem *item_id, int proportion, r32 padding, i32 align_flags = ztAlign_Center, i32 grow_direction = ztGuiItemOrient_Horz | ztGuiItemOrient_Vert);
void             zt_guiSizerAddStretcher               (ztGuiItem *sizer, int proportion, r32 padding = 0);
void             zt_guiSizerSizeToParent               (ztGuiItem *sizer, bool size_to_parent = true);
void             zt_guiSizerSizeParent                 (ztGuiItem *sizer, bool size_parent_x = true, bool size_parent_y = true); // calling this before SizeToParent will allow sizing of either horz/vert of parent wh ile still sizing to the other dim of the parent
void             zt_guiSizerRecalc                     (ztGuiItem *item);
void             zt_guiSizerRecalcImmediately          (ztGuiItem *sizer);
ztVec2           zt_guiSizerGetMinSize                 (ztGuiItem *sizer);
void             zt_guiColumnSizerSetProp              (ztGuiItem *sizer, int col, int prop);

// ================================================================================================================================================================================================

void             zt_guiSplitterSetItems(ztGuiItem *splitter, ztGuiItem *first, ztGuiItem *second);
void             zt_guiSplitterSetPercent(ztGuiItem *splitter, r32 percent);
void             zt_guiSplitterSetFirstSize(ztGuiItem *splitter, r32 size); // will cause resizing to resize second only and not the first
void             zt_guiSplitterSetSecondSize(ztGuiItem *splitter, r32 size); // will cause resizing to resize first only and not the second
void             zt_guiSplitterSetFirstItem(ztGuiItem *splitter, ztGuiItem *item);
void             zt_guiSplitterSetSecondItem(ztGuiItem *splitter, ztGuiItem *item);

// ================================================================================================================================================================================================

struct ztGuiDialogMessageOption
{
	i32 id;
	char display[64];
	void *user_data;
};

#define          ZT_FUNC_GUI_DIALOG_MESSAGE_CLOSED(name) void name(ztGuiDialogMessageOption *option, void *user_data);
typedef          ZT_FUNC_GUI_DIALOG_MESSAGE_CLOSED(zt_guiDialogMessageClosed_Func);

void             zt_guiDialogMessageBox(const char *title, const char *message, ztGuiDialogMessageOption *options, int options_count, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data);

void             zt_guiDialogMessageBoxOk         (const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data);
void             zt_guiDialogMessageBoxOkCancel   (const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data);
void             zt_guiDialogMessageBoxYesNo      (const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data);
void             zt_guiDialogMessageBoxYesNoCancel(const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data);


// ================================================================================================================================================================================================

#define          ZT_FUNC_GUI_DIALOG_GET_USER_TEXT(name) void name(const char *value, bool cancelled, void *user_data)
typedef          ZT_FUNC_GUI_DIALOG_GET_USER_TEXT(zt_guiDialogGetUserText_Func);

void             zt_guiDialogGetUserText(const char *title, const char *message, const char *def_value, bool allow_cancel, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogGetUserText_Func), void *user_data);

// ================================================================================================================================================================================================

enum             ztGuiDialogFileSelectFlags_Enum
{
	             ztGuiDialogFileSelectFlags_Open = (1 << 0),
	             ztGuiDialogFileSelectFlags_Save = (1 << 1),
};

#define          ZT_FUNC_GUI_DIALOG_FILE_SELECTED(name) void name(char *path, void *user_data)
typedef          ZT_FUNC_GUI_DIALOG_FILE_SELECTED(zt_guiDialogFileSelected_Func);

void             zt_guiDialogFileSelect(const char *title, i32 flags, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogFileSelected_Func), void *user_data, char *start_dir = nullptr);

// ================================================================================================================================================================================================

#define          ZT_FUNC_GUI_DIALOG_COLOR_PICKER_SELECTED(name) void name(ztColor color_chosen, void *user_data)
typedef          ZT_FUNC_GUI_DIALOG_COLOR_PICKER_SELECTED(zt_guiDialogColorPickerSelected_Func);

void             zt_guiDialogColorPicker(ztColor *selected_color, i32 behavior_flags, ZT_FUNCTION_POINTER_VAR_DEFNULL(callback, zt_guiDialogColorPickerSelected_Func), void *user_data = nullptr, const char *window_title = "Select a Color");

// ================================================================================================================================================================================================

#define          ZT_FUNC_GUI_DIALOG_COLOR_GRADIENT_EDITOR_COMPLETE(name) void name(ztColorGradient2 *gradient, void *user_data)
typedef          ZT_FUNC_GUI_DIALOG_COLOR_GRADIENT_EDITOR_COMPLETE(zt_guiDialogColorGradientEditorComplete_Func);

void             zt_guiDialogColorGradient(ztColorGradient2 *gradient, i32 behavior_flags, ZT_FUNCTION_POINTER_VAR_DEFNULL(callback, zt_guiDialogColorGradientEditorComplete_Func), void *user_data = nullptr, const char *window_title = "Color Gradient");

// ================================================================================================================================================================================================

#define          ZT_FUNC_GUI_DIALOG_ANIM_CURVE_EDITOR_COMPLETE(name) void name(ztAnimCurve *curve, void *user_data)
typedef          ZT_FUNC_GUI_DIALOG_ANIM_CURVE_EDITOR_COMPLETE(zt_guiDialogAnimCurveEditorComplete_Func);

void             zt_guiDialogAnimCurveEditor(ztAnimCurve *curve, i32 behavior_flags, ZT_FUNCTION_POINTER_VAR_DEFNULL(callback, zt_guiDialogAnimCurveEditorComplete_Func), void *user_data = nullptr, const char *window_title = "Curve Editor");

// ================================================================================================================================================================================================

#define          ZT_FUNC_GUI_DIALOG_SPRITE_SELECTED(name) void name(ztSpriteManager *sprite_manager, ztSpriteManager::Entry *entry, i32 sprite_name_hash, const char *sprite_name, bool cancelled, void *user_data)
typedef          ZT_FUNC_GUI_DIALOG_SPRITE_SELECTED(zt_guiDialogSpriteSelected_Func);

void             zt_guiDialogSpriteSelector(ztSpriteManager *sprite_manager, ZT_FUNCTION_POINTER_VAR_DEFNULL(callback, zt_guiDialogSpriteSelected_Func), void *user_data = nullptr, const char *window_title = "Select Sprite");

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


void             zt_guiInitDebug(ztGuiManager *gui_manager);

void             zt_guiDebugHide                       ();
void             zt_guiDebugShow                       ();
void             zt_guiDebugToggle                     ();
void             zt_guiDebugBringToFront               ();

void             zt_guiDebugShowDetails                (bool show = true);

//               returns a static text that will appear in the dropdown when [+] is pressed next to the fps display
ztGuiItem       *zt_guiDebugAddMetric                  (const char *sample);

ztGuiItem       *zt_guiDebugGetMenuBar                 ();

// ================================================================================================================================================================================================

#define ztDebugConsoleParams(PARAMS)	char PARAMS[16][256]

#define ZT_FUNC_DEBUG_CONSOLE_COMMAND(name) void name(ztDebugConsoleParams(params), int params_count, void *user_data)
typedef ZT_FUNC_DEBUG_CONSOLE_COMMAND(zt_debugConsole_Func);

#define ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(name) void name(char **params, int params_count, char *auto_fill, int auto_fill_len, void *user_data)
typedef ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(zt_debugConsoleAutoComplete_Func);

// ================================================================================================================================================================================================

void zt_debugConsoleAddCommand(const char *command, const char *help, ZT_FUNCTION_POINTER_VAR(command_func, zt_debugConsole_Func), ZT_FUNCTION_POINTER_VAR(auto_complete_func, zt_debugConsoleAutoComplete_Func), void *user_data = nullptr);
void zt_debugConsoleRemoveCommand (const char *command);

enum ztDebugConsoleLevel_Enum
{
	ztDebugConsoleLevel_User,
	ztDebugConsoleLevel_Command,
	ztDebugConsoleLevel_Help,
	ztDebugConsoleLevel_Warning,
	ztDebugConsoleLevel_Error,
	ztDebugConsoleLevel_System,
};

void zt_debugConsoleLog           (ztDebugConsoleLevel_Enum message_level, const char *command, ...);
void zt_debugConsoleLogUser       (const char *command, ...);
void zt_debugConsoleLogCommand    (const char *command, ...);
void zt_debugConsoleLogHelp       (const char *command, ...);
void zt_debugConsoleLogWarning    (const char *command, ...);
void zt_debugConsoleLogError      (const char *command, ...);
void zt_debugConsoleLogSystem     (const char *command, ...);

void zt_debugConsoleToggle        (bool *is_shown = nullptr);

// ================================================================================================================================================================================================

void zt_debugLogGuiHierarchy      (ztGuiItem *item);

// ================================================================================================================================================================================================

void zt_guiDebugMemoryInspectorAddArena    (ztMemoryArena *arena, const char *alias);
void zt_guiDebugMemoryInspectorRemoveArena (ztMemoryArena *arena);

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_FUNC_DLL_SET_GAME_GUI_GLOBALS(name) void name(void *memory, int version)
typedef ZT_FUNC_DLL_SET_GAME_GUI_GLOBALS(zt_dllSetGameGuiGlobals_Func);

#if !defined(ZT_DLL)
void zt_dllSendGameGuiGlobals(zt_dllSetGameGuiGlobals_Func *set_globals);
#else
void zt_dllGuiLoad   ();
void zt_dllGuiUnload ();
#endif


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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
	ztGuiSizerType_Wrap,
};

#ifndef ZT_GUI_SIZER_MAX_COLUMNS
#define ZT_GUI_SIZER_MAX_COLUMNS	16
#endif

#ifndef ZT_GUI_SIZER_MAX_ROWS
#define ZT_GUI_SIZER_MAX_ROWS		128
#endif


// ================================================================================================================================================================================================

struct ztGuiItem
{
	i32                  id;
	ztGuiItemType_Enum   type;

	ztString             name;
	ztString             label;
	ztString             tooltip;
	ztString             theme_type;

	ztVec2               size;
	ztVec2               pos;
	ztVec2               prev_size;
	ztVec2               min_size;

	i32                  align_flags;
	i32                  anchor_flags;
	i32                  pos_align_flags;
	i32                  pos_anchor_flags;
	i32                  custom_flags;

	ztVec2               pos_offset;
	ztVec4               color;
	ztVec4               clip_area;

	i32                  behavior_flags;
	i32                  state_flags;   // use zt_bit() with the ztGuiItemStates_Enum values
	r32                  state_length[32];
	i32                  prev_state_flags;

	ztGuiItem           *parent;
	ztGuiItem           *sib_next;
	ztGuiItem           *sib_prev;
	ztGuiItem           *first_child;

	ztGuiItemFunctions   functions;
	ztGuiTheme          *theme;

	ztDrawList          *draw_list;

	ztGuiManager        *gm;

	void                *user_data;

	zt_debugOnly(ztColor debug_highlight);

	// -------------------------------------------------

	struct ztDragState
	{
		bool  dragging;
		r32   offset_x;
		r32   offset_y;
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
		i32             flags;

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
			ztVec2     content_panel_size;
			ztGuiItem *button;
		} collapsing_panel;

		// -------------------------------------------------

		struct {
			bool                   *live_value;
			ZT_FUNCTION_POINTER_VAR(on_pressed, zt_guiButtonPressed_Func);
			void                   *on_pressed_user_data;
			ztSprite               *icon;
			i32                     text_pos;
		} button;

		// -------------------------------------------------

		struct {
			r32                    *live_value;
			r32                     value;
			ztGuiItemOrient_Enum    orient;
			r32                     drag_pos[2];
			ztDragState             drag_state;
			bool                    highlight;
			r32                     handle_size;
			r32                     handle_pos;
			// scrollbar only
			int                     press_button;
			r32                     press_time;
			r32                     step, step_page, handle_pct;
			ZT_FUNCTION_POINTER_VAR(on_scrollbar_scroll, zt_guiSliderChanged_Func);
			void                   *on_scrollbar_scroll_user_data;
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
			i32                     cursor_pos;
			r32                     cursor_blink_time;
			b32                     cursor_vis;
			r32                     cursor_xy[2];

			i32                     select_beg;
			i32                     select_end;

			bool                    dragging;

			ztGuiItem              *scrollbar_vert;
			ztGuiItem              *scrollbar_horz;

			r32                     scroll_amt_vert;
			r32                     scroll_amt_horz;

			ztString                text_buffer;

			r32                     content_size[2];
			r32                     text_pos[2];
			r32                     select_pos[4];

			ZT_FUNCTION_POINTER_VAR(on_key, zt_guiTextEditKey_Func);
			void                   *on_key_user_data;
		} textedit;

		// -------------------------------------------------

		struct {
			ztString               *display;
			i32                    *ids;
			ztGuiItem             **submenus;
			ztSprite              **icons;
			void                  **user_datas;
			ztGuiItem              *scrollbar_vert;
			ztGuiItem              *scrollbar_horz;
			ztVec2                  full_size;

			i32                     item_count;
			i32                     highlighted;
			i32                     selected;
			i32                     just_opened;
			r32                     label_offset;
			ztGuiItem              *owner;

			ZT_FUNCTION_POINTER_VAR(on_selected, zt_guiMenuSelected_Func);
		} menu;

		// -------------------------------------------------

		struct {
			ztGuiSizerType_Enum      type;

			ztSizerItemEntry        *items;
			r32                      size[2];
			bool                     size_to_parent;
			bool                     size_parent_x, size_parent_y;
			int                      size_frame;

			union {
				// ztGuiSizerType_Normal/Wrap
				ztGuiItemOrient_Enum orient;

				// ztGuiSizerType_Column
				struct {
					ztGuiColumnSizerType_Enum columns_type;
					int                       columns;
					i8                        props[ZT_GUI_SIZER_MAX_COLUMNS];
				};
			};
		} sizer;

		// -------------------------------------------------

		struct {
			ztGuiItem              *container;
			ztGuiItem              *content;

			ztTreeItem             *root_item;
			ztTreeItem             *active_item;

			ztGuiTreeNodeID         last_id;
			ztMemoryArena          *arena;

			ZT_FUNCTION_POINTER_VAR(on_item_sel, zt_guiTreeItemSelected_Func);
			void                   *on_item_sel_user_data;
		} tree;

		// -------------------------------------------------

		struct {
			ztGuiItem              *popup;

			ztString               *contents;
			void                  **contents_user_data;
			int                     contents_size;
			int                     contents_count;
			int                     selected;

			ZT_FUNCTION_POINTER_VAR(on_selected, zt_guiComboBoxItemSelected_Func);
			void                   *on_selected_user_data;
		} combobox;

		// -------------------------------------------------

		struct {
			int                    *live_value;
			ztString               *contents;
			void                  **contents_user_data;
			int                     contents_size;
			int                     contents_count;
			int                     selected;
			ztGuiItem              *buttons[2]; // 0 - left, 1 - right

			ZT_FUNCTION_POINTER_VAR(on_changed, zt_guiCycleBoxValueChanged_Func);
			void                   *on_changed_user_data;
		} cyclebox;

		// -------------------------------------------------

		struct {
			ztGuiThemeSprite       *sprite;
			ztSpriteAnimController *sprite_anim_controller;
			r32                     scale[2];
			r32                     bgcolor[4];
		} sprite_display;

		// -------------------------------------------------

		struct {
			int                    *live_value;
			int                     value;
			r32                     start[2];
			r32                     time;
			int                     last_dir;
			ZT_FUNCTION_POINTER_VAR(on_value_changed, zt_guiSpinnerValueChanged_Func);
			void                   *on_value_changed_user_data;
		} spinner;

		// -------------------------------------------------

		struct {
			ztGuiItem             **items;
			void                  **user_datas;
			bool                   *selected;
			r32                    *heights;
			bool                   *hidden;
			bool                   *size_x;

			i32                     item_count;
			i32                     item_size;
			r32                     total_height;
			r32                     total_width;
			i32                     active_item;
			i32                     prev_active_item;

			ztGuiItem              *container;
			ztGuiItem              *scrollbar_vert;
			ztGuiItem              *scrollbar_horz;
			ztGuiItem              *header;

			r32                     scroll_amt_vert;
			r32                     scroll_amt_horz;

			ZT_FUNCTION_POINTER_VAR(on_selected, zt_guiListBoxItemSelected_Func);
			void                   *on_selected_user_data;
		} listbox;

		// -------------------------------------------------

		struct {
			ZT_FUNCTION_POINTER_VAR(callback, zt_guiColorPickerChanged_Func);
			void                   *user_data;
			ztColor                *live_value;
			bool                    include_alpha;
		} color_picker;

		// -------------------------------------------------

		struct {
			ZT_FUNCTION_POINTER_VAR(callback, zt_guiColorGradientChanged_Func);
			void                   *user_data;
			ztColorGradient2       *gradient;
			ztColorGradient2       *live_value;
		} gradient_picker;

		// -------------------------------------------------

		struct {
			ZT_FUNCTION_POINTER_VAR(callback, zt_guiEditorValueChanged_Func);
			void                   *user_data;
			ztAnimCurve            *curve;
			ztAnimCurve            *live_value;
		} anim_curve;

		// -------------------------------------------------

		struct {
			ztGuiItemOrient_Enum orient;
			r32                  split_percent;
			ztGuiItem           *items[2];

			int                  size_only;
			r32                  size;

			bool                 dragging;
			r32                  dragging_offset;
		} splitter;

		// -------------------------------------------------
	};
};

// ================================================================================================================================================================================================

enum ztGuiManagerItemCacheFlags_Enum
{
	ztGuiManagerItemCacheFlags_Used       = (1<<0),
	ztGuiManagerItemCacheFlags_MouseOver  = (1<<1),
	ztGuiManagerItemCacheFlags_FreeQueued = (1<<2),
};

// ================================================================================================================================================================================================

#ifndef ZT_GUI_MANAGER_MAX_ITEMS
#define ZT_GUI_MANAGER_MAX_ITEMS	1024 * 64
#endif

// ================================================================================================================================================================================================

struct ztGuiManager
{
	i32            id;

	ztGuiItem     *item_has_mouse;
	ztVec2         mouse_pos;
	bool           mouse_over_gui;
	bool           mouse_click;
	bool           mouse_click_ignored;
	bool           mouse_just_clicked;
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

	ztGuiItem      item_cache      [ZT_GUI_MANAGER_MAX_ITEMS];
	i32            item_cache_flags[ZT_GUI_MANAGER_MAX_ITEMS];
	i32            item_cache_used;

	ztGuiTheme     default_theme;

	ztMemoryArena *arena;
	i32            base_id;

	bool           in_update;

	ztStringPool   string_pool;

	ztGuiManager  *next;
};

// ================================================================================================================================================================================================

struct ztConsoleCommand
{
	char              command[32];
	char              help[1024];

	ZT_FUNCTION_POINTER_VAR(on_command,       zt_debugConsole_Func);
	ZT_FUNCTION_POINTER_VAR(on_auto_complete, zt_debugConsoleAutoComplete_Func);

	void             *user_data;

	ztConsoleCommand *next;
};

// ================================================================================================================================================================================================

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
	ztGuiItem        *menu_bar                     = nullptr;
	ztMemoryArena    *arena                        = nullptr;
	ztMemoryArena    *stack_arena                  = nullptr;
};

#define ZT_GAME_GUI_GLOBALS_VERSION   1 // update this any time ztGuiGlobals is changed

// ================================================================================================================================================================================================

enum ztGuiManagerInternalFlags_Enum
{
	ztGuiManagerInternalFlags_OwnsTheme = (1 << 0),
};

// ================================================================================================================================================================================================

enum ztGuiWindowInternalBehaviorFlags_Enum
{
	ztGuiWindowInternalBehaviorFlags_ScrollHorz = (1 << (ztGuiWindowBehaviorFlags_MaxBit + 1)),
	ztGuiWindowInternalBehaviorFlags_ScrollVert = (1 << (ztGuiWindowBehaviorFlags_MaxBit + 2)),
};

zt_staticAssert(ztGuiWindowBehaviorFlags_MaxBit <= 29);


// ================================================================================================================================================================================================

enum ztGuiWindowInternalStates_Enum
{
	ztGuiWindowInternalStates_Resizing = (ztGuiItemStates_MAX + 1),
	ztGuiWindowInternalStates_Collapsed = (ztGuiItemStates_MAX + 2),
};


// ================================================================================================================================================================================================

enum ztGuiCollapsingPanelInternalStates_Enum
{
	ztGuiCollapsingPanelInternalStates_Collapsed = (ztGuiItemStates_MAX + 1),
};

// ================================================================================================================================================================================================

enum ztGuiButtonInternalBehaviorFlags_Enum
{
	ztGuiButtonInternalBehaviorFlags_IsToggleButton = (1 << (ztGuiButtonBehaviorFlags_MaxBit + 1)),
	ztGuiButtonInternalBehaviorFlags_IsCheckbox     = (1 << (ztGuiButtonBehaviorFlags_MaxBit + 2)),
	ztGuiButtonInternalBehaviorFlags_IsRadio        = (1 << (ztGuiButtonBehaviorFlags_MaxBit + 3)),
};

// ------------------------------------------------------------------------------------

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

// ================================================================================================================================================================================================

enum ztGuiComboBoxInternalStates_Enum
{
	ztGuiComboBoxInternalStates_IgnorePopup = (ztGuiItemStates_MAX + 1),
};

// ================================================================================================================================================================================================

#if defined(ZT_GAME_GUI_INTERNAL_DECLARATIONS)
extern ztGuiGlobals *zt_gui;
#endif

// ================================================================================================================================================================================================

#define ZT_PROFILE_GUI(section)	ZT_PROFILE((section), "GUI")

// ================================================================================================================================================================================================

ztGuiItem *_zt_guiMakeItemBase(ztGuiItem *parent, ztGuiItemType_Enum type, i32 item_flags, i32 draw_list_size = 0);

// ================================================================================================================================================================================================

#endif // include guard
#endif // INTERNAL DECLARATIONS

#if defined(ZT_GAME_GUI_IMPLEMENTATION)

#ifndef __zt_game_gui_implementation__
#define __zt_game_gui_implementation__

// ================================================================================================================================================================================================

ztGuiGlobals zt_gui_local = {};

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugConsoleAddLoggingCallbacks();
ztInternal void _zt_guiDebugConsoleRemoveLoggingCallbacks();


// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiInitGlobalMemory(ztMemoryArena *arena)
{
	zt_gui->arena = arena;
	zt_gui->gui_manager_first = zt_gui->gui_manager_active = nullptr;
	zt_gui->gui_managers_count = 0;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeGetRValue, ztInternal ZT_FUNC_THEME_GET_RVALUE(_zt_guiDefaultThemeGetRValue))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetRValue");

	r32 ppu = zt_pixelsPerUnit();

	switch (value)
	{
		case ztGuiThemeValue_r32_Padding:                      *result =  3 / ppu; break;
		
		case ztGuiThemeValue_r32_WindowTitleHeight:            *result = 26 / ppu; break;
		case ztGuiThemeValue_r32_WindowCollapseButtonOffsetX:  *result =  5 / ppu; break;
		case ztGuiThemeValue_r32_WindowCollapseButtonOffsetY:  *result = -3 / ppu; break;
		case ztGuiThemeValue_r32_WindowCloseButtonOffsetX:     *result = -5 / ppu; break;
		case ztGuiThemeValue_r32_WindowCloseButtonOffsetY:     *result = -3 / ppu; break;
		case ztGuiThemeValue_r32_WindowPaddingX:               *result =  6 / ppu; break;
		case ztGuiThemeValue_r32_WindowPaddingY:               *result =  6 / ppu; break;
		case ztGuiThemeValue_r32_WindowCornerResizeW:          *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_WindowCornerResizeH:          *result = 16 / ppu; break;

		case ztGuiThemeValue_r32_CollapsingPanelHeight:        *result = 26 / ppu; break;
		case ztGuiThemeValue_r32_CollapsingPanelButtonOffsetX: *result =  2 / ppu; break;
		case ztGuiThemeValue_r32_CollapsingPanelButtonOffsetY: *result = -3 / ppu; break;
		case ztGuiThemeValue_r32_CollapsingPanelPaddingX:      *result =  4 / ppu; break;
		case ztGuiThemeValue_r32_CollapsingPanelPaddingY:      *result =  4 / ppu; break;

		case ztGuiThemeValue_r32_ButtonDefaultW:              *result = 96 / ppu; break;
		case ztGuiThemeValue_r32_ButtonDefaultH:              *result = 26 / ppu; break;
		case ztGuiThemeValue_r32_ButtonPaddingW:              *result =  3 / ppu; break;
		case ztGuiThemeValue_r32_ButtonPaddingH:              *result =  3 / ppu; break;

		case ztGuiThemeValue_r32_CheckboxW:                   *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_CheckboxH:                   *result = 16 / ppu; break;

		case ztGuiThemeValue_r32_RadiobuttonW:                *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_RadiobuttonH:                *result = 16 / ppu; break;
		
		case ztGuiThemeValue_r32_SliderHandleSize:            *result =  8 / ppu; break;
		case ztGuiThemeValue_r32_SliderHandleMinHeight:       *result = 20 / ppu; break;
		
		case ztGuiThemeValue_r32_ScrollbarButtonW:            *result =  0 / ppu; break;
        case ztGuiThemeValue_r32_ScrollbarButtonH:            *result =  0 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinHandleSize:      *result =  8 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinWidth:           *result = 10 / ppu; break;
		
		case ztGuiThemeValue_r32_ScrollContainerPaddingX:     *result =  3 / ppu; break;
		case ztGuiThemeValue_r32_ScrollContainerPaddingY:     *result =  3 / ppu; break;
		
		case ztGuiThemeValue_r32_TextEditPaddingX:            *result =  2 / ppu; break;
		case ztGuiThemeValue_r32_TextEditPaddingY:            *result =  1 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultW:            *result = 90 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultH:            *result = 26 / ppu; break;
		
		case ztGuiThemeValue_r32_MenuSubmenuIconX:            *result =  1 / ppu; break;
		case ztGuiThemeValue_r32_MenuSubmenuIconY:            *result =  1 / ppu; break;
		case ztGuiThemeValue_r32_MenuSeparatorHeight:         *result =  3 / ppu; break;
		
		case ztGuiThemeValue_r32_TreeIndent:                  *result = 12 / ppu; break;
		
		case ztGuiThemeValue_r32_ComboboxButtonW:             *result = 26 / ppu; break;

		case ztGuiThemeValue_r32_CycleBoxButtonW:             *result = 26 / ppu; break;

		case ztGuiThemeValue_r32_SplitterHandleW:             *result =  4 / ppu; break;
		case ztGuiThemeValue_r32_SplitterPadding:             *result =  1 / ppu; break;


		default: return true;  // return false to use the default (this is the default though)
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeGetIValue, ztInternal ZT_FUNC_THEME_GET_IVALUE(_zt_guiDefaultThemeGetIValue))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetIValue");

	switch (value)
	{
		case ztGuiThemeValue_i32_FontID:                            *result = ztFontDefault; break;

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeUpdateItem, ztInternal ZT_FUNC_THEME_UPDATE_ITEM(_zt_guiDefaultThemeUpdateItem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeUpdateItem");

//	r32 ppu = zt_pixelsPerUnit();
//	switch (item->type)
//	{
//
//		default: return true;  // return false to use the default (this is the default though)
//	}

	return false;
}

// ================================================================================================================================================================================================

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
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(1007, 16), zt_vec2i(16, 16));
						zt_guiButtonSetIcon(subitem, &sprite);
						//zt_guiItemSetLabel(subitem, "X");
					}
					else if (zt_strEquals(name, "Collapse")) {
						if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
							ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(992, 1), zt_vec2i(12, 12));
							zt_guiButtonSetIcon(subitem, &sprite);
							//zt_guiItemSetLabel(subitem, ">");
						}
						else {
							ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(992, 14), zt_vec2i(12, 12));
							zt_guiButtonSetIcon(subitem, &sprite);
							//zt_guiItemSetLabel(subitem, "v");
						}
					}
					zt_guiItemSetSize(subitem, zt_vec2(18 / ppu, 18 / ppu));
				} break;
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_CollapsingPanel : {
			switch (subitem->type)
			{
				case ztGuiItemType_Button: {
					if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(992, 1), zt_vec2i(12, 12));
						zt_guiButtonSetIcon(subitem, &sprite);
						//zt_guiItemSetLabel(subitem, ">");
					}
					else {
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(992, 14), zt_vec2i(12, 12));
						zt_guiButtonSetIcon(subitem, &sprite);
						//zt_guiItemSetLabel(subitem, "v");
					}
					zt_guiItemSetSize(subitem, zt_vec2(21 / ppu, 21 / ppu));
				} break;
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Tree: {
			switch (subitem->type)
			{
				case ztGuiItemType_Button: {
					if (data == nullptr || *((bool*)data) == true) {
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(979, 16), zt_vec2i(9, 9));
						zt_guiButtonSetIcon(subitem, &sprite);
						//zt_guiItemSetLabel(subitem, "-");
					}
					else {
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(979, 2), zt_vec2i(9, 9));
						zt_guiButtonSetIcon(subitem, &sprite);
						//zt_guiItemSetLabel(subitem, "+");
					}
					zt_guiItemSetSize(subitem, zt_vec2(17 / ppu, 17 / ppu));
				} break;
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_CycleBox: {
			r32 button_w = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_CycleBoxButtonW, item);

			subitem->size.x = button_w;
			subitem->size.y = item->size.y;

			switch (subitem->type)
			{
				case ztGuiItemType_Button: {
					subitem->behavior_flags |= ztGuiButtonBehaviorFlags_NoBackground;

					if (((ztDirection_Enum)(pointer)data) == ztDirection_Left) {
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(931, 1), zt_vec2i(12, 12));
						zt_guiButtonSetIcon(subitem, &sprite);
						zt_guiItemSetPosition(subitem, ztAlign_Left, ztAnchor_Left, ztVec2::zero);
					}
					else if (((ztDirection_Enum)(pointer)data) == ztDirection_Right) {
						ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(992, 1), zt_vec2i(12, 12));
						zt_guiButtonSetIcon(subitem, &sprite);
						zt_guiItemSetPosition(subitem, ztAlign_Right, ztAnchor_Right, ztVec2::zero);
					}
				} break;
			}

		} break;

		// ================================================================================================================================================================================================

		default: return true; // return false to use the default (this is the default though)
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeSizeItem, ztInternal ZT_FUNC_THEME_SIZE_ITEM(_zt_guiDefaultThemeSizeItem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeSizeItem");

	r32 ppu = zt_pixelsPerUnit();

	switch (item->type)
	{
		case ztGuiItemType_CollapsingPanel: {
			ztVec2 ext = zt_fontGetExtents(ztFontDefault, item->label);
			ztVec2 m_size = ext;
			r32 padding = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_Padding, &padding);
			m_size.x += padding * 2;
			r32 panel_height = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_CollapsingPanelHeight, &panel_height);
			m_size.y = zt_max(m_size.y, panel_height);

			item->size.x = zt_max(item->size.x, m_size.x);
			item->size.y = zt_max(item->size.y, m_size.y);
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_StaticText: {
			ztFontID font = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_MonoSpaced) ? ztFontDefaultMono : ztFontDefault;
			item->size = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(font, item->label) : zt_fontGetExtents(font, item->label);
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_ToggleButton:
		case ztGuiItemType_Button: {
			r32 button_padding_w = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ButtonPaddingW, &button_padding_w);
			r32 button_padding_h = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ButtonPaddingH, &button_padding_h);

			ztVec2 text_size = item->label ? zt_fontGetExtents(ztFontDefault, item->label) : ztVec2::zero;
			if (item->button.icon) {
				ztVec2 content_size = ztVec2::zero;
				ztVec2 icon_size = zt_vec2(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);

				if (zt_bitIsSet(item->button.text_pos, ztAlign_Left)) {
					content_size = zt_vec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
				}
				else if (zt_bitIsSet(item->button.text_pos, ztAlign_Right)) {
					content_size = zt_vec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
				}
				else if (zt_bitIsSet(item->button.text_pos, ztAlign_Top)) {
					content_size = zt_vec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
				}
				else if (zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
					content_size = zt_vec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
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
				r32 button_default_w = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ButtonDefaultW, &button_default_w);
				r32 button_default_h = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ButtonDefaultH, &button_default_h);
				item->size.x = zt_max(min_x, button_default_w);
				item->size.y = zt_max(min_y, button_default_h);
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Checkbox:
		case ztGuiItemType_RadioButton: {
			ztVec2 txt_size = zt_fontGetExtents(ztFontDefault, item->label);
			r32 padding    = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_Padding, &padding);
			r32 checkbox_w = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_CheckboxW, &checkbox_w);
			r32 checkbox_h = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_CheckboxW, &checkbox_h);
			item->size.x = txt_size.x + padding + checkbox_w;
			item->size.y = zt_max(txt_size.y, checkbox_h);
			
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_MenuBar:
		case ztGuiItemType_Menu: {
			ztVec2 icon_orig = zt_vec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, item), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item));
			ztVec2 icon = icon_orig;
			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
			zt_fiz(item->menu.item_count) {
				if (item->menu.icons[i] != nullptr) {
					icon.x = zt_max(icon.x, item->menu.icons[i]->half_size.x * 2.f + padding * 2.f);
					icon.y = zt_max(icon.y, item->menu.icons[i]->half_size.y * 2.f);
				}
			}

			item->size = ztVec2::zero;

			ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_MenuFontID, item);
			if (item->type == ztGuiItemType_Menu) {
				zt_fiz(item->menu.item_count) {
					ztVec2 ext = zt_fontGetExtents(font, item->menu.display[i]);

					if (icon.y > ext.y) ext.y = icon.y;
					if (item->menu.ids[i] == ztInvalidID && zt_strStartsWith(item->menu.display[i], "__")) {
						ext.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSeparatorHeight, item);
					}

					item->size.y += ext.y + padding;
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

		// ================================================================================================================================================================================================

		case ztGuiItemType_ComboBox: {
			r32 base_width = 22 / ppu;

			item->size.x = 80 / ppu;
			item->size.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultH, item);

			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
			ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_FontID, item);
			zt_fiz(item->combobox.contents_count) {
				ztVec2 ext = zt_fontGetExtents(font, item->combobox.contents[i]);
				item->size.x = zt_max(item->size.x, base_width + ext.x + padding * 2);
				item->size.y = zt_max(item->size.y, ext.y + padding * 2);
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_CycleBox: {
			r32 base_width = 44 / ppu;

			item->size.x = 80 / ppu;
			item->size.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultH, item);

			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
			ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_FontID, item);
			zt_fiz(item->cyclebox.contents_count) {
				ztVec2 ext = zt_fontGetExtents(font, item->cyclebox.contents[i]);
				item->size.x = zt_max(item->size.x, base_width + ext.x);
				item->size.y = zt_max(item->size.y, ext.y + padding * 2);
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Spinner: {
			item->size.x = 20 / ppu;
			item->size.y = 20 / ppu;
		} break;
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDefaultThemeRenderItem, ztInternal ZT_FUNC_THEME_RENDER_ITEM(_zt_guiDefaultThemeRenderItem))
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem");

	struct local
	{
		static ztColor outline(bool highlighted, bool pressed)
		{
			if (pressed) return zt_color(1, 1, 1, 1);
			if (highlighted) return zt_color(1, 1, 1, 1);
			return zt_color(1, 1, 1, 1);
		}

		static ztColor face(bool highlighted, bool pressed)
		{
			if (pressed) return zt_color(.15f, .15f, .15f, .85f);
			if (highlighted) return zt_color(.25f, .25f, .25f, 1);
			return zt_color(0, 0, 0, .85f);
		}

		static ztColor fancyOutline(bool highlighted, bool pressed)
		{
			ztColor color = zt_color(120 / 255.f, 201 / 255.f, 242 / 255.f, .95f);
			if (pressed) return color * .8f;
			if (highlighted) return color * .9f;
			return color;
		}

		static ztColor fancyFace(bool highlighted, bool pressed)
		{
			ztColor color = zt_color(0 / 255.f, 137 / 255.f, 207 / 255.f, .95f);
			if (pressed) return color * .8f;
			if (highlighted) return color * .9f;
			return color;
		}

		static void drawColoredOutlinedRect(ztDrawList *draw_list, ztVec2 pos, ztVec2 size, ztColor color)
		{
			static ztSpriteNineSlice sns = zt_spriteNineSliceMake(zt_game->fonts[ztFontDefault].texture, 964, 2, 12, 12, 966, 4, 974, 12);
			zt_drawListPushColor(draw_list, color);
			zt_drawListAddSpriteNineSlice(draw_list, &sns, pos, size);
			zt_drawListPopColor(draw_list);
		}

		static void drawColoredSolidRect(ztDrawList *draw_list, ztVec2 pos, ztVec2 size, ztColor color)
		{
			static ztSprite s = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 948, 2, 12, 12);
			zt_drawListPushColor(draw_list, color);
			ztVec3 scale = zt_vec3(size.x / (s.half_size.x * 2), size.y / (s.half_size.y * 2), 1);
			zt_drawListAddSprite(draw_list, &s, zt_vec3(pos, 0), ztVec3::zero, scale);
			zt_drawListPopColor(draw_list);
		}

		static void drawHorizontalLine(ztDrawList *draw_list, r32 x1, r32 x2, r32 y, ztColor color)
		{
			if (x1 > x2) {
				zt_swap(x1, x2);
			}

			static ztSprite s = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 964, 20, 12, 3);
			zt_drawListPushColor(draw_list, color);
			r32 scale = (x2 - x1) / (s.half_size.x * 2);
			r32 pos = x1 + (x2 - x1) / 2;
			zt_drawListAddSpriteFast(draw_list, &s, zt_vec3(pos, y, 0), ztVec3::zero, zt_vec3(scale, 1, 1));
			zt_drawListPopColor(draw_list);
		}

		static void drawVerticalLine(ztDrawList *draw_list, r32 x, r32 y1, r32 y2, ztColor color)
		{
			if (y1 > y2) {
				zt_swap(y1, y2);
			}

			static ztSprite s = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 953, 16, 1, 12);
			zt_drawListPushColor(draw_list, color);
			r32 scale = (y2 - y1) / (s.half_size.y * 2);
			r32 pos = y1 + (y2 - y1) / 2;
			zt_drawListAddSpriteFast(draw_list, &s, zt_vec3(x, pos, 0), ztVec3::zero, zt_vec3(1, scale, 1));
			zt_drawListPopColor(draw_list);
		}

		static void drawOutlinedRect(ztDrawList *draw_list, ztVec2 pos, ztVec2 size, bool highlighted, bool pressed)
		{
			static ztSpriteNineSlice sns = zt_spriteNineSliceMake(zt_game->fonts[ztFontDefault].texture, 964, 2, 12, 12, 966, 4, 974, 12);
			zt_drawListAddSpriteNineSlice(draw_list, &sns, pos, size);
		}

		static void drawOutlinedSolidRect(ztDrawList *draw_list, ztVec2 pos, ztVec2 size, bool highlighted, bool pressed, bool fancy = false)
		{
			static ztSprite s = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 948, 2, 12, 12);
			static ztSpriteNineSlice sns = zt_spriteNineSliceMake(zt_game->fonts[ztFontDefault].texture, 963, 1, 14, 14, 967, 5, 973, 11, 1, 1, 1, 1);

			ztColor color_face = fancy ? (pressed ? zt_colorRgb(46, 128, 150, 255) : highlighted ? zt_colorRgb(16, 173, 215, 255) : zt_colorRgb(55, 155, 181, 255)) : 
			                             (pressed ? zt_colorRgb(26, 76, 90, 255) : highlighted ? zt_color(.3f, .3f, .3f, .8f) : zt_color(0, 0, 0, .8f));

			zt_drawListPushColor(draw_list, color_face);
			ztVec3 scale = zt_vec3(size.x / (s.half_size.x * 2), size.y / (s.half_size.y * 2), 1);
			zt_drawListAddSprite(draw_list, &s, zt_vec3(pos, 0), ztVec3::zero, scale);
			zt_drawListPopColor(draw_list);

			if (fancy) {
				zt_drawListPushColor(draw_list, zt_colorRgb(26, 76, 90, 255));
				zt_drawListAddSpriteNineSlice(draw_list, &sns, pos, size);
				zt_drawListPopColor(draw_list);
			}
			else {
				zt_drawListAddSpriteNineSlice(draw_list, &sns, pos, size);
			}
		}
	};

	r32 ppu = zt_pixelsPerUnit();
	bool has_focus   = zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_HasFocus));
	bool highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
	bool pressed     = (highlighted && item->gm->item_has_mouse == item) || (!highlighted && zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled)));
	bool enabled     = true;

	//zt_alignToPixel(&pos, ppu);
	ztVec2 size = item->size;
	zt_alignToPixel(&size, ppu);

	switch (item->type)
	{
		case ztGuiItemType_Window: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Window");

			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
				ztVec2 win_size = zt_vec2(item->size.x, 25 / ppu);
				ztVec2 win_pos = zt_vec2(pos.x, pos.y + (item->size.y / 2) - (win_size.y / 2));
				local::drawOutlinedSolidRect(draw_list, win_pos, win_size, has_focus, false);
			}
			else {
				local::drawOutlinedSolidRect(draw_list, pos, item->size, has_focus, false);

				if (zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_AllowResize)) {
					static ztSprite resize_sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 929, 15, 16, 16);
					ztVec2 pos_corner = zt_vec2(pos.x + item->size.x / 2.f - 3 / ppu, pos.y - item->size.y / 2.f + 2 / ppu) + zt_vec2(-resize_sprite.half_size.x, resize_sprite.half_size.y);
					zt_drawListAddSprite(draw_list, &resize_sprite, zt_vec3(pos_corner, 0));
				}
			}

			if (item->label != nullptr && zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_ShowTitle)) {
				ztVec2 title_pos = zt_vec2(pos.x, pos.y + (item->size.y / 2) - (4 / ppu));
				ztVec2 title_size;
				zt_drawListAddText2D(draw_list, 0, item->label, title_pos, ztAlign_Top, ztAnchor_Top, &title_size);
				title_size.y += 4 / ppu;

				ztVec2 size = item->size;
				size.x -= 4 / ppu;

				local::drawHorizontalLine(draw_list, title_pos.x + (size.x / -2), title_pos.x + (size.x / 2), title_pos.y - title_size.y, has_focus ? local::outline(false, false) : zt_color(.65f, .65f, .65f, 1));
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Panel: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Panel");

			if (zt_bitIsSet(item->behavior_flags, ztGuiPanelBehaviorFlags_DrawBackground)) {
				local::drawOutlinedSolidRect(draw_list, pos, item->size, false, false);
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_CollapsingPanel: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:CollapsingPanel");

			local::drawOutlinedSolidRect(draw_list, pos, item->size, false, false);

			if (item->label != nullptr) {
				r32 panel_height = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_CollapsingPanelHeight, &panel_height);

				ztVec2 title_pos = zt_vec2(pos.x - ((item->size.x) / 2) + 25 / ppu, pos.y + (item->size.y - (panel_height)) / 2);
				ztVec2 title_size;

//				if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed)) {
//				}
				local::drawOutlinedSolidRect(draw_list, zt_vec2(pos.x, title_pos.y), zt_vec2(item->size.x, panel_height), true, false);

				zt_drawListAddText2D(draw_list, 0, item->label, title_pos, ztAlign_Left, ztAnchor_Left, &title_size);
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_StaticText: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:StaticText");
#			if 0
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
			zt_drawListAddDrawList(draw_list, item->draw_list, zt_vec3(pos, 0));
#			else
			ztFontID font = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_MonoSpaced) ? ztFontDefaultMono : ztFontDefault;
			ztVec2 ext = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(font, item->label) : zt_fontGetExtents(font, item->label);
			ztVec2 off = pos;

			if (item->align_flags != 0) {
				if (zt_bitIsSet(item->align_flags, ztAlign_Left)) off.x -= (item->size.x - ext.x) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Right)) off.x += (item->size.x - ext.x) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Top)) off.y += (item->size.y - ext.y) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Bottom)) off.y -= (item->size.y - ext.y) / 2.f;
			}

			if (zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy)) {
				zt_drawListAddFancyText2D(draw_list, font, item->label, off, item->align_flags, item->anchor_flags);
			}
			else {
				zt_drawListAddText2D(draw_list, font, item->label, off, item->align_flags, item->anchor_flags);
			}

#			endif
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_ToggleButton:
		case ztGuiItemType_Button: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Button");

			if (!zt_bitIsSet(item->behavior_flags, ztGuiButtonBehaviorFlags_NoBackground) || pressed || highlighted) {
				local::drawOutlinedSolidRect(draw_list, pos, item->size, highlighted, pressed);
			}

			r32 button_padding_w = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ButtonPaddingW, &button_padding_w);
			r32 button_padding_h = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ButtonPaddingH, &button_padding_h);

			ztVec2 text_pos = ztVec2::zero;
			if (item->button.icon) {
				ztVec2 text_size = item->label ? zt_fontGetExtents(ztFontDefault, item->label) : ztVec2::zero;
				ztVec2 content_size = ztVec2::zero;
				ztVec2 icon_size = zt_vec2(item->button.icon->half_size.x * 2.f, item->button.icon->half_size.y * 2.f);
				ztVec2 icon_pos = text_pos;

				if (item->label != nullptr) {
					if (zt_bitIsSet(item->button.text_pos, ztAlign_Left)) {
						content_size = zt_vec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
						icon_pos.x = (content_size.x - icon_size.x) / 2.f;
						text_pos.x = (content_size.x - text_size.x) / -2.f;
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Right)) {
						content_size = zt_vec2(text_size.x + icon_size.x + button_padding_w * 1.f, zt_max(text_size.y, icon_size.y) + button_padding_h * 1.f);
						icon_pos.x = (content_size.x - icon_size.x) / -2.f;
						text_pos.x = (content_size.x - text_size.x) / 2.f;
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Top)) {
						content_size = zt_vec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
						icon_pos.y = (content_size.y - icon_size.y) / -2.f;
						text_pos.y = (content_size.y - text_size.y) / 2.f;
					}
					else if (zt_bitIsSet(item->button.text_pos, ztAlign_Bottom)) {
						content_size = zt_vec2(zt_max(text_size.x, icon_size.x) + button_padding_w * 1.f, text_size.y + icon_size.y + button_padding_h * 1.f);
						icon_pos.y = (content_size.y - icon_size.y) / 2.f;
						text_pos.y = (content_size.y - text_size.y) / -2.f;
					}
				}
				else {
					content_size = icon_size;
				}

				ztVec2 item_size = zt_vec2(item->size.x - button_padding_w * 2.f, item->size.y - button_padding_h * 2.f);
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

				zt_drawListAddSprite(draw_list, item->button.icon, zt_vec3(icon_pos, 0));
			}
			if (item->label) {
				zt_drawListAddFancyText2D(draw_list, 0, item->label, pos + text_pos, item->align_flags);
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Checkbox:
		case ztGuiItemType_RadioButton: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:CheckRadio");

			bool checkbox = zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsCheckbox);
			bool radio    = zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio);

			r32 checkbox_w = 0; _zt_guiDefaultThemeGetRValue(theme, item, item->type == ztGuiItemType_Checkbox ? ztGuiThemeValue_r32_CheckboxW : ztGuiThemeValue_r32_RadiobuttonW, &checkbox_w);
			r32 checkbox_h = 0; _zt_guiDefaultThemeGetRValue(theme, item, item->type == ztGuiItemType_Checkbox ? ztGuiThemeValue_r32_CheckboxW : ztGuiThemeValue_r32_RadiobuttonW, &checkbox_h);
			r32 padding    = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_Padding, &padding);

			ztVec2 box_size = zt_vec2(checkbox_w, checkbox_h);
			ztVec2 box_pos, txt_size, txt_pos;

			txt_size = item->label == nullptr ? ztVec2::zero : zt_fontGetExtents(ztFontDefault, item->label);
			if (zt_bitIsSet(item->behavior_flags, ztGuiCheckboxBehaviorFlags_RightText)) {
				box_pos = zt_vec2((item->size.x - box_size.x) / -2.f, 0);
				txt_pos = zt_vec2(box_pos.x + box_size.x / 2.f + padding, 0);
			}
			else {
				txt_pos = zt_vec2(item->size.x / -2.f, 0);
				box_pos = zt_vec2((item->size.x / 2.f) - (box_size.x / 2.f), 0);
			}

			zt_drawListAddText2D(draw_list, ztFontDefault, item->label, zt_strLen(item->label), txt_pos + pos, ztAlign_Left, ztAnchor_Left);


			box_pos += pos;

			if (checkbox) {
				local::drawOutlinedSolidRect(draw_list, box_pos, box_size, highlighted, highlighted && pressed);

				if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled))) {
					static ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 0, 16, 16);
					zt_drawListAddSprite(draw_list, &sprite, zt_vec3(box_pos, 0));
				}
			}
			else if (radio) {
				zt_drawListAddSolidOutlinedCircle2D(draw_list, zt_vec3(box_pos, 0), box_size.x / 2.f, 8, local::face(highlighted, pressed), local::outline(highlighted, pressed));

				if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled))) {
					zt_drawListAddSolidCircle2D(draw_list, zt_vec3(box_pos, 0), (box_size.x - 8 / ppu) / 2.f, 8, zt_color(.7f, .7f, .7f, 1));
				}
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Scrollbar:
		case ztGuiItemType_Slider: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:ScrollbarSlider");

			ztVec2 handle_pos, handle_size;

			if (item->slider.drag_state.dragging) {
				highlighted = true;
			}

			r32 scrollbar_button_w = 0;
			_zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ScrollbarButtonW, &scrollbar_button_w);

			if (item->slider.orient == ztGuiItemOrient_Horz) {
				handle_pos = pos + zt_vec2(item->slider.handle_pos, 0);

				if (item->type == ztGuiItemType_Slider) {
					local::drawOutlinedSolidRect(draw_list, pos, item->size - zt_vec2(0, 10 / ppu), highlighted && !item->slider.highlight, false);
					handle_size = zt_vec2(zt_max(8 / ppu, item->slider.handle_size), item->size.y);
				}
				else {
					local::drawOutlinedSolidRect(draw_list, pos, item->size, highlighted, false);
					handle_size = zt_vec2( zt_max(10 / ppu, item->slider.handle_size - (2 / ppu)),item->size.y - (2 / ppu));

					ztVec2 btn_size = zt_vec2(scrollbar_button_w / ppu, scrollbar_button_w / ppu);
					if(btn_size.x > 0 && btn_size.y > 0) {
						bool neg_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegHighlight)), neg_pressed = neg_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)),
							 pos_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosHighlight)), pos_pressed = pos_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed));

						local::drawOutlinedSolidRect(draw_list, pos + zt_vec2(item->size.x / -2.f + scrollbar_button_w / 2.f, 0), btn_size, neg_highlight, neg_pressed);
						local::drawOutlinedSolidRect(draw_list, pos + zt_vec2(item->size.x / 2.f - scrollbar_button_w / 2.f, 0), btn_size, pos_highlight, pos_pressed);
					}
				}
			}
			else {
				handle_pos = pos + zt_vec2(0, item->slider.handle_pos);
				if (item->type == ztGuiItemType_Slider) {
					local::drawOutlinedSolidRect(draw_list, pos, item->size - zt_vec2(6 / ppu, 0), highlighted, pressed);

					handle_size = zt_vec2(item->size.x, zt_max(10 / ppu, item->slider.handle_size));
				}
				else {
					local::drawOutlinedSolidRect(draw_list, pos, item->size, highlighted, false);
					handle_size = zt_vec2(item->size.x - (2 / ppu), zt_max(10 / ppu, item->slider.handle_size - (2 / ppu)));

					ztVec2 btn_size = zt_vec2(scrollbar_button_w / ppu, scrollbar_button_w / ppu);
					if(btn_size.x > 0 && btn_size.y > 0) {
						bool neg_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegHighlight)), neg_pressed = neg_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)),
							 pos_highlight = enabled && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosHighlight)), pos_pressed = pos_highlight && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed));

						local::drawOutlinedSolidRect(draw_list, pos + zt_vec2(0, item->size.y / 2.f - scrollbar_button_w / 2.f), btn_size, neg_highlight, neg_pressed);
						local::drawOutlinedSolidRect(draw_list, pos + zt_vec2(0, item->size.y / -2.f + scrollbar_button_w / 2.f), btn_size, pos_highlight, pos_pressed);
					}
				}
			}


			if (enabled) {
				bool highlight = item->slider.highlight && zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
				bool pressed = item->slider.drag_state.dragging;
				local::drawOutlinedSolidRect(draw_list, handle_pos, handle_size, highlight, pressed, true);

			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_TextEdit: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:TextEdit");

			ztVec2 size = item->size;
			zt_alignToPixel(&size, zt_pixelsPerUnit());
			local::drawOutlinedSolidRect(draw_list, pos, item->size, false, false);

			ztVec2 text_pos = zt_vec2(item->textedit.text_pos[0], item->textedit.text_pos[1] + (-4 / zt_pixelsPerUnit()));

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

					ztVec2 pos_size = zt_vec2(pos_end.x - pos_beg.x, pos_beg.y - pos_end.y);
					ztVec2 pos_center = zt_vec2(pos_beg.x + pos_size.x / 2.f, pos_beg.y - pos_size.y / 2.f);

					local::drawColoredSolidRect(draw_list, text_pos + pos_center, pos_size, zt_color(.5f, .5f, 1, .5f));

					sel_beg = idx_end_line + 1;
				}
			}

			ztVec3 dlpos = zt_vec3(text_pos, 0);
			zt_alignToPixel(&dlpos, zt_pixelsPerUnit());
			zt_drawListAddDrawList(draw_list, item->draw_list, dlpos);

			if (item->gm->focus_item == item) {
				if (item->textedit.cursor_vis) {
					ztFontID font = ztFontDefault;
					ztVec2 cursor_pos = text_pos + zt_vec2(item->textedit.cursor_xy[0], item->textedit.cursor_xy[1]);
					ztVec2 cursor_size = zt_fontGetExtents(font, "|");
					cursor_pos.x -= cursor_size.x / 2;
					zt_drawListAddText2D(draw_list, font, "|", cursor_pos, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);
				}
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_MenuBar:
		case ztGuiItemType_Menu: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Menu");

			if (item->type == ztGuiItemType_Menu) {
				local::drawOutlinedSolidRect(draw_list, pos, item->size, false, false);
			}
			else {
				local::drawOutlinedSolidRect(draw_list, pos + zt_vec2(0, 1 / ppu), item->size + zt_vec2(2 / ppu, 2 / ppu), false, false);
			}

			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
			pos.x -= (item->size.x - padding * 2.f) / 2.f;
			pos.y += (item->size.y - padding * 2.f) / 2.f;

			ztVec2 icon; 
			icon.x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, item);
			icon.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item);

			zt_fiz(item->menu.item_count) {
				if (item->menu.icons[i] != nullptr) {
					icon.x = zt_max(icon.x, item->menu.icons[i]->half_size.x * 2.f + padding * 2.f);
					icon.y = zt_max(icon.y, item->menu.icons[i]->half_size.y * 2.f);
				}
			}

			zt_fiz(item->menu.item_count) {
				ztVec2 ext = zt_fontGetExtents(ztFontDefault, item->menu.display[i]);

				if (icon.y > ext.y) ext.y = icon.y;
				if (item->menu.ids[i] == ztInvalidID && zt_strStartsWith(item->menu.display[i], "__")) {
					ext.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSeparatorHeight, item);

					ztVec2 lpos = pos;
					local::drawHorizontalLine(draw_list, lpos.x, lpos.x + (item->size.x - padding * 2), lpos.y - ext.y / 2, ztColor_White);
				}
				else {
					if (item->menu.highlighted == i && highlighted) {
						if (item->type == ztGuiItemType_Menu) {
							local::drawColoredSolidRect(draw_list, zt_vec2(pos.x + item->size.x / 2 - padding, pos.y - ext.y / 2.f), zt_vec2(item->size.x - padding * 2.f, ext.y + 2 / ppu), zt_color(.5f, .5f, 1, .5f));
						}
						else {
							local::drawColoredSolidRect(draw_list, zt_vec2(pos.x + ext.x / 2, pos.y - ext.y / 2.f), zt_vec2(ext.x + padding * 2, ext.y + 2 / ppu), zt_color(.5f, .5f, 1, .5f));
						}
					}
					zt_drawListAddText2D(draw_list, ztFontDefault, item->menu.display[i], zt_vec2(pos.x + icon.x, pos.y - ext.y / 2.f), ztAlign_Left, ztAnchor_Left);

					if (item->menu.icons[i] != nullptr) {
						r32 y = zt_max(item->menu.icons[i]->half_size.y, ext.y / 2.f);
						zt_drawListAddSprite(draw_list, item->menu.icons[i], zt_vec3(pos.x + padding + item->menu.icons[i]->half_size.x, pos.y - y, 0));
					}
				}


				if (item->type == ztGuiItemType_Menu) {
					if (item->menu.submenus[i] != nullptr) {
						r32 icon_x = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_MenuSubmenuIconX, &icon_x);
						r32 icon_y = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_MenuSubmenuIconY, &icon_y);
						r32 y = zt_max(icon_y, ext.y) / 2.f;
						zt_drawListAddText2D(draw_list, ztFontDefault, ">", zt_vec2((item->size.x + pos.x) - (padding * 3 + icon_x / 2.f), pos.y - y + padding));
					}

					pos.y -= ext.y + padding;
				}
				else {
					pos.x += icon.x + padding + ext.x + padding;
				}
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Tree: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Tree");

			local::drawOutlinedSolidRect(draw_list, pos, item->size, false, false);

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
						zt_drawListAddSolidRect2D(draw_list, zt_vec2(pos.x, npos.y), zt_vec2(item->size.x, active->size.y), zt_color(.5f, .5f, 1, .25f));
					}
				}
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_ComboBox: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Combobox");

			bool pressed = false, highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(highlighted, pressed), local::outline(highlighted, pressed));

			r32 padding = 0;  _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_Padding, &padding);

			r32 button_w = 0; _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_ComboboxButtonW, &button_w);
			ztSprite sprite_arrow = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, zt_vec2i(992, 14), zt_vec2i(12, 12));
			zt_drawListAddSprite(draw_list, &sprite_arrow, zt_vec3(pos.x + (item->size.x - button_w) / 2, pos.y, 0));

			if (item->combobox.selected >= 0 && item->combobox.selected < item->combobox.contents_count) {
				r32 width = item->size.x;

				pos.x = (pos.x) + (width / -2.f + padding);

				if (item->combobox.popup != nullptr) {
					if (item->combobox.popup->menu.icons[item->combobox.selected]) {
						ztSprite *sprite = item->combobox.popup->menu.icons[item->combobox.selected];

						zt_drawListAddSprite(draw_list, sprite, zt_vec3(pos.x + sprite->half_size.x, pos.y, 0));

						pos.x += sprite->half_size.x * 2 + padding;
					}
				}
				zt_drawListAddFancyText2D(draw_list, ztFontDefault, item->combobox.contents[item->combobox.selected], pos, ztAlign_Left, ztAnchor_Left);
			}

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_CycleBox: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Cyclebox");

			//bool pressed = false, highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
			//if (highlighted) {
			//	zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(highlighted, pressed), local::outline(highlighted, pressed));
			//}

			if (item->cyclebox.selected >= 0 && item->cyclebox.selected < item->cyclebox.contents_count) {
				zt_drawListAddFancyText2D(draw_list, ztFontDefault, item->cyclebox.contents[item->cyclebox.selected], pos);
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Spinner: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Spinner");

			bool pressed = item->gm->item_has_mouse == item;
			bool highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);

			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(highlighted, pressed), local::outline(highlighted, pressed));
			zt_drawListAddLine(draw_list, zt_vec3(pos.x - item->size.x / 2 + (1/ppu), pos.y, 0), zt_vec3(pos.x + item->size.x / 2, pos.y, 0));

			r32 padding = 0;  _zt_guiDefaultThemeGetRValue(theme, item, ztGuiThemeValue_r32_Padding, &padding);
			
			ztVec3 pos_txt_p = zt_vec3(pos.x, (pos.y + (item->size.y / 2)) - (6 / ppu), 0);
			ztVec3 pos_txt_m = zt_vec3(pos.x, (pos.y - (item->size.y / 2)) + (7 / ppu), 0);

			ztSprite sprite_up = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 917, 1, 13, 13);
			ztSprite sprite_dn = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 991, 13, 13, 13);

			zt_drawListAddSprite(draw_list, &sprite_up, pos_txt_p);
			zt_drawListAddSprite(draw_list, &sprite_dn, pos_txt_m);

			//zt_drawListAddText2D(draw_list, ztFontDefault, "+", pos_txt_p, ztAlign_Top, ztAnchor_Top);
			//zt_drawListAddText2D(draw_list, ztFontDefault, "-", pos_txt_m, ztAlign_Bottom, ztAnchor_Bottom);

		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_ListBox: {
			ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:ListBox");

			zt_drawListAddSolidOutlinedRect2D(draw_list, pos, item->size, local::face(false, false), local::outline(false, false));

			int item_drawn = 0;
			zt_fiz(item->listbox.item_count) {
				item_drawn += 1;

				if (!zt_guiItemIsVisible(item->listbox.items[i])) {
					if (item->listbox.hidden[i]) {
						item_drawn -= 1;
					}
					continue;
				}

				if (item->listbox.selected[i]) {
					zt_drawListAddSolidRect2D(draw_list, pos + item->listbox.container->pos + zt_vec2(0, item->listbox.items[i]->pos.y), zt_vec2(item->listbox.container->size.x, item->listbox.items[i]->size.y), zt_color(.5f, .5f, 1, .5f));
				}
				else if (zt_bitIsSet(item->behavior_flags, ztGuiListBoxBehaviorFlags_AlternateRowColor) && item_drawn % 2 == 0) {
					zt_drawListAddSolidRect2D(draw_list, pos + item->listbox.container->pos + zt_vec2(0, item->listbox.items[i]->pos.y), zt_vec2(item->listbox.container->size.x, item->listbox.items[i]->size.y), zt_color(.5f, .5f, 1, .125f));
				}
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_SpriteDisplay: {
			if (*(ztVec4*)item->sprite_display.bgcolor != ztVec4::zero) {
				zt_drawListAddSolidRect2D(draw_list, zt_vec3(pos, 0), item->size, zt_vec4(item->sprite_display.bgcolor));
			}

			if (item->sprite_display.sprite_anim_controller != nullptr) {
				ztSprite *sprite = zt_spriteAnimControllerActiveSprite(item->sprite_display.sprite_anim_controller);
				if (sprite != nullptr) {
					zt_drawListAddSprite(draw_list, sprite, zt_vec3(pos, 0), ztVec3::zero, zt_vec3(item->size, 1));
				}
			}
			else if (item->sprite_display.sprite != nullptr) {
				zt_drawListAddGuiThemeSprite(draw_list, item->sprite_display.sprite, pos, item->size);
			}
		} break;

		// ================================================================================================================================================================================================

		case ztGuiItemType_Splitter: {
			if(item->splitter.orient == ztGuiItemOrient_Horz) {
				//r32 center = (pos.x - item->size.x / 2) + (item->size.x * item->splitter.split_percent);
			}
			else {
			}
		} break;

		// ================================================================================================================================================================================================

		default: return true; // return false to use the default (this is the default though)
	}

	return true;
}

// ================================================================================================================================================================================================

ztGuiManager *zt_guiManagerMake(ztCamera *gui_camera, ztGuiTheme *theme_default, ztMemoryArena *arena, ztGuiManagerStringPool_Enum string_pool)
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
	gm->in_update       = false;
	gm->string_pool     = {};

	if(string_pool != ztGuiManagerStringPool_None) {
		int sp_sizes[4];
		int sp_props[4];
		int count = 0;

		switch(string_pool)
		{
			case ztGuiManagerStringPool_Minimal: {
				sp_sizes[0] =  16; sp_props[0] = 8;
				sp_sizes[1] =  32; sp_props[1] = 4;
				sp_sizes[2] =  64; sp_props[2] = 2;
				sp_sizes[3] = 128; sp_props[3] = 1;
				count = 1024;
			} break;

			case ztGuiManagerStringPool_Standard: {
				sp_sizes[0] =  16; sp_props[0] = 8;
				sp_sizes[1] =  32; sp_props[1] = 4;
				sp_sizes[2] =  64; sp_props[2] = 2;
				sp_sizes[3] = 128; sp_props[3] = 1;
				count = 1024 * 8;
			} break;

			case ztGuiManagerStringPool_Heavy:  {
				sp_sizes[0] =  16; sp_props[0] = 8;
				sp_sizes[1] =  32; sp_props[1] = 4;
				sp_sizes[2] =  64; sp_props[2] = 2;
				sp_sizes[3] = 128; sp_props[3] = 1;
				count = 1024 * 16;
			} break;
		}

		i32 bytes_needed = zt_stringPoolBytesNeeded(count, sp_sizes, sp_props, zt_elementsOf(sp_sizes));
		ztMemoryArena *sp_arena = zt_memMakeArena(bytes_needed, arena, 0);

		gm->string_pool = zt_stringPoolMake(count, sp_sizes, sp_props, zt_elementsOf(sp_sizes), sp_arena);
	}
	else {
		gm->string_pool.arena = arena;
	}

	if (theme_default) {
		gm->default_theme = *theme_default;
	}
	else {
#		if defined(ZT_WINDOWS)
		gm->internal_flags |= ztGuiManagerInternalFlags_OwnsTheme;

		zt_memSet(&gm->default_theme, zt_sizeof(ztGuiTheme), 0);

		// ----------------------------------------------------------------

		gm->default_theme.theme_data      = nullptr;
		gm->default_theme.flags           = 0;
		gm->default_theme.get_rvalue      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetRValue);
		gm->default_theme.get_ivalue      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetIValue);
		gm->default_theme.render_item     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeRenderItem);
		gm->default_theme.postrender_item = ZT_FUNCTION_POINTER_TO_VAR_NULL;
		gm->default_theme.update_item     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeUpdateItem);
		gm->default_theme.update_subitem  = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeUpdateSubitem);
		gm->default_theme.size_item       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeSizeItem);
		gm->default_theme.pass_begin      = ZT_FUNCTION_POINTER_TO_VAR_NULL;
		gm->default_theme.pass_end        = ZT_FUNCTION_POINTER_TO_VAR_NULL;

		// ----------------------------------------------------------------

#		endif
	}

	if (zt_gui->gui_managers_count++ == 0) {
		zt_gui->gui_manager_active = gm;
		zt_gui->gui_manager_first = gm;

		if (zt_gui->stack_arena == nullptr) {
			zt_gui->stack_arena = zt_memMakeArena(zt_megabytes(1), arena);
		}
	}
	else {
		zt_singleLinkAddToEnd(zt_gui->gui_manager_first, gm);
	}

	return gm;
}

// ================================================================================================================================================================================================

r32 zt_guiThemeGetRValue(ztGuiTheme *theme, ztGuiThemeValue_Enum value, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiThemeGetRValue");

	zt_returnValOnNull(theme, 0);

	r32 result = 0;
	if (!ZT_FUNCTION_POINTER_IS_VALID(theme->get_rvalue) || !ZT_FUNCTION_POINTER_ACCESS(theme->get_rvalue, ztGuiThemeGetRValue_Func)(theme, item, value, &result)) {
		_zt_guiDefaultThemeGetRValue(theme, item, value, &result);
	}

	return result;
}

// ================================================================================================================================================================================================

i32 zt_guiThemeGetIValue(ztGuiTheme *theme, ztGuiThemeValue_Enum value, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiThemeGetIValue");

	zt_returnValOnNull(theme, 0);

	i32 result = 0;
	if (!ZT_FUNCTION_POINTER_IS_VALID(theme->get_ivalue) || !ZT_FUNCTION_POINTER_ACCESS(theme->get_ivalue, ztGuiThemeGetIValue_Func)(theme, item, value, &result)) {
		_zt_guiDefaultThemeGetIValue(theme, item, value, &result);
	}

	return result;
}

// ================================================================================================================================================================================================

void zt_guiThemeUpdateItem(ztGuiTheme *theme, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiThemeUpdateItem");

	zt_returnOnNull(theme);
	zt_returnOnNull(item);
	zt_returnOnNull(item);

	if (!ZT_FUNCTION_POINTER_IS_VALID(theme->update_item) || !ZT_FUNCTION_POINTER_ACCESS(theme->update_item, ztGuiThemeUpdateItem_Func)(theme, item)) {
		_zt_guiDefaultThemeUpdateItem(theme, item);
	}
}

// ================================================================================================================================================================================================

void zt_guiThemeUpdateSubitem(ztGuiTheme *theme, ztGuiItem *item, ztGuiItem * subitem, void *data)
{
	ZT_PROFILE_GUI("zt_guiThemeUpdateSubitem");

	zt_returnOnNull(theme);
	zt_returnOnNull(item);
	zt_returnOnNull(subitem);

	if (!ZT_FUNCTION_POINTER_IS_VALID(theme->update_subitem) || !ZT_FUNCTION_POINTER_ACCESS(theme->update_subitem, ztGuiThemeUpdateSubitem_Func)(theme, item, subitem, data)) {
		_zt_guiDefaultThemeUpdateSubitem(theme, item, subitem, data);
	}
}

// ================================================================================================================================================================================================

void zt_guiThemeSizeItem(ztGuiTheme *theme, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiThemeSizeItem");

	zt_returnOnNull(theme);
	zt_returnOnNull(item);

	if (!ZT_FUNCTION_POINTER_IS_VALID(theme->size_item) || !ZT_FUNCTION_POINTER_ACCESS(theme->size_item, ztGuiThemeSizeItem_Func)(theme, item)) {
		_zt_guiDefaultThemeSizeItem(theme, item);
	}
}

// ================================================================================================================================================================================================

void zt_guiThemeRender(ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos)
{
	ZT_PROFILE_GUI("zt_guiThemeRender");

	zt_returnOnNull(theme);
	zt_returnOnNull(draw_list);
	zt_returnOnNull(item);

	bool needs_postrender = false;
	if (!ZT_FUNCTION_POINTER_IS_VALID(theme->render_item) || !ZT_FUNCTION_POINTER_ACCESS(theme->render_item, ztGuiThemeRenderItem_Func)(theme, draw_list, item, pos, &needs_postrender)) {
		_zt_guiDefaultThemeRenderItem(theme, draw_list, item, pos, &needs_postrender);
	}

	if (needs_postrender) {
		item->state_flags |= zt_bit(ztGuiItemStates_PostRender);
	}
}

// ================================================================================================================================================================================================

void zt_guiThemePostRender(ztGuiTheme *theme, ztDrawList *draw_list, ztGuiItem *item, ztVec2 pos)
{
	ZT_PROFILE_GUI("zt_guiThemePostRender");

	zt_returnOnNull(theme);
	zt_returnOnNull(draw_list);
	zt_returnOnNull(item);

	if (ZT_FUNCTION_POINTER_IS_VALID(theme->postrender_item)) {
		ZT_FUNCTION_POINTER_ACCESS(theme->postrender_item, ztGuiThemePostRenderItem_Func)(theme, draw_list, item, pos);
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiItemFree(ztGuiManager *gm, ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiItemFree");

	if (ZT_FUNCTION_POINTER_IS_VALID(item->functions.cleanup)) {
		ZT_FUNCTION_POINTER_ACCESS(item->functions.cleanup, zt_guiItemCleanup_Func)(item, item->functions.user_data);
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
			else if (gm->first_child == child) {
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

	if (item->name      ) zt_stringFree(&gm->string_pool, item->name);
	if (item->label     ) zt_stringFree(&gm->string_pool, item->label);
	if (item->tooltip   ) zt_stringFree(&gm->string_pool, item->tooltip);
	if (item->theme_type) zt_stringFree(&gm->string_pool, item->theme_type);

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

// ================================================================================================================================================================================================

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

	zt_memFreeArena(gm->string_pool.arena);
	//zt_stringPoolFree(&gm->string_pool); can skip this since it was contained in the arena
	gm->string_pool = {};

	zt_freeArena(gm, gm->arena);

	zt_gui->gui_managers_count--;
	if (zt_gui->gui_managers_count > 0) {
		return;
	}

	if (zt_gui->stack_arena) {
		zt_memFreeArena(zt_gui->stack_arena);
		zt_gui->stack_arena = nullptr;
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

// ================================================================================================================================================================================================

ztInternal void _zt_guiItemReposition(ztGuiManager *gm, ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiItemReposition");

	ztVec2 min, max;
	if (item->parent) {
		min = zt_vec2(item->parent->size.x / -2.f, item->parent->size.y / -2.f);
		max = zt_vec2(item->parent->size.x / 2.f, item->parent->size.y / 2.f);
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

// ================================================================================================================================================================================================

ztInternal void _zt_guiManagerUpdatePre(ztGuiManager *gm, r32 dt)
{
	ZT_PROFILE_GUI("_zt_guiManagerUpdatePre");

	int item_count = gm->item_cache_used;
	int items_freed = 0;

	bool has_late_update = false;

	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] != 0) {
			zt_fkz(32) {
				gm->item_cache[i].state_length[k] += dt;
			}

			if (gm->item_cache[i].prev_state_flags != gm->item_cache[i].state_flags) {
				zt_fkz(32) {
					if (zt_bitIsSet(gm->item_cache[i].prev_state_flags, zt_bit(k)) != zt_bitIsSet(gm->item_cache[i].state_flags, zt_bit(k))) {
						gm->item_cache[i].state_length[k] = 0;
					}
				}
			}

			gm->item_cache[i].prev_state_flags = gm->item_cache[i].state_flags;

			if (gm->item_cache[i].prev_size.x != gm->item_cache[i].size.x || gm->item_cache[i].prev_size.y != gm->item_cache[i].size.y) {
				ZT_PROFILE_GUI("_zt_guiManagerUpdatePre:windowSize");

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

			if (zt_bitIsSet(gm->item_cache_flags[i], ztGuiManagerItemCacheFlags_FreeQueued)) {
				ZT_PROFILE_GUI("_zt_guiManagerUpdatePre:freeQueued");
				if (items_freed++ < 10) {
					zt_guiItemFree(&gm->item_cache[i]);
				}
			}
			else {
				if (ZT_FUNCTION_POINTER_IS_VALID(gm->item_cache[i].functions.update)) {
					ZT_PROFILE_GUI("_zt_guiManagerUpdatePre:updateCallback");
					if (zt_bitIsSet(gm->item_cache[i].behavior_flags, ztGuiItemBehaviorFlags_LateUpdate)) {
						has_late_update = true;
					}
					else {
						ZT_FUNCTION_POINTER_ACCESS(gm->item_cache[i].functions.update, zt_guiItemUpdate_Func)(&gm->item_cache[i], dt, gm->item_cache[i].functions.user_data);
					}
				}
			}
			if (--item_count == 0) {
				break;
			}
		}
	}

	if (has_late_update) {
		ZT_PROFILE_GUI("_zt_guiManagerUpdatePre:lateUpdate");

		zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
			if (gm->item_cache_flags[i] != 0 && ZT_FUNCTION_POINTER_IS_VALID(gm->item_cache[i].functions.update)) {
				if (zt_bitIsSet(gm->item_cache[i].behavior_flags, ztGuiItemBehaviorFlags_LateUpdate)) {
					ZT_FUNCTION_POINTER_ACCESS(gm->item_cache[i].functions.update, zt_guiItemUpdate_Func)(&gm->item_cache[i], dt, gm->item_cache[i].functions.user_data);
				}
			}
		}
	}

	if (gm->gui_camera_w != gm->gui_camera->width || gm->gui_camera_h != gm->gui_camera->height) {
		ZT_PROFILE_GUI("_zt_guiManagerUpdatePre:cameraAdjust");
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

	// modal windows
	{
		ZT_PROFILE_GUI("_zt_guiManagerUpdatePre:windowsAdjust");
#if 0
		{
			bool check_modals = true;
			zt_flinknext(child, gm->first_child, sib_next) {
				if (child->sib_next == nullptr && child->type == ztGuiItemType_Window && zt_bitIsSet(child->behavior_flags, ztGuiWindowBehaviorFlags_Modal)) {
					check_modals = false;
				}
			}

			if (check_modals) {
				zt_flinknext(child, gm->first_child, sib_next) {
					if (child->type == ztGuiItemType_Window && zt_bitIsSet(child->behavior_flags, ztGuiWindowBehaviorFlags_Modal)) {
						zt_guiItemBringToFront(child);
						break;
					}
				}
			}
		}
#endif

		// then menus windows
		zt_flinknext(child, gm->first_child, sib_next) {
			if (child->type == ztGuiItemType_Menu && zt_bitIsSet(child->state_flags, zt_bit(ztGuiItemStates_Visible))) {
				zt_guiItemBringToFront(child);
			}
		}
	}

	//zt_memArenaValidate(gm->arena);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiManagerUpdatePost(ztGuiManager *gm, r32 dt)
{
	ZT_PROFILE_GUI("_zt_guiManagerUpdatePost");

	int item_count = gm->item_cache_used;
	zt_fiz(zt_elementsOf(gm->item_cache_flags)) {
		if (gm->item_cache_flags[i] != 0) {
			zt_bitRemove(gm->item_cache_flags[i], ztGuiManagerItemCacheFlags_MouseOver);
			zt_bitRemove(gm->item_cache[i].state_flags, zt_bit(ztGuiItemStates_MouseOver));
			if (--item_count == 0) {
				break;
			}
		}
	}
}

// ================================================================================================================================================================================================

bool zt_guiManagerHandleInput(ztGuiManager *gm, ztInputKeys input_keys[ztInputKeys_MAX], ztInputKeys_Enum input_key_strokes[ZT_MAX_INPUT_KEYSTROKES], ztInputMouse *input_mouse)
{
	ZT_PROFILE_GUI("zt_guiManagerHandleInput");

	if (zt_inputMouseIsLook()) {
		return false;
	}

	zt_returnValOnNull(gm, false);
	zt_returnValOnNull(input_keys, false);
	zt_returnValOnNull(input_mouse, false);

	gm->in_update = true;

	gm->key_state_alt   = input_keys[ztInputKeys_Menu].pressed();
	gm->key_state_ctrl  = input_keys[ztInputKeys_Control].pressed();
	gm->key_state_shift = input_keys[ztInputKeys_Shift].pressed();


	bool mouse_captured = gm->item_has_mouse != nullptr;
	if (mouse_captured) {
		ztGuiItem *mc_item = gm->item_has_mouse;
		if (mc_item && !zt_bitIsSet(mc_item->state_flags, zt_bit(ztGuiItemStates_Visible))) {
			zt_bitRemove(gm->item_has_mouse->state_flags, zt_bit(ztGuiItemStates_MouseClick));
			gm->item_has_mouse = nullptr;
		}
	}

	if (gm->focus_item != nullptr && zt_guiItemIsShowing(gm->focus_item)) {
		bool key_handled = false;
		ztGuiItem *f_item = gm->focus_item;
		if (!key_handled && f_item && (input_key_strokes[0] != ztInputKeys_Invalid || zt_bitIsSet(f_item->behavior_flags, ztGuiItemBehaviorFlags_WantsKeyboardAlways))) {
			if (ZT_FUNCTION_POINTER_IS_VALID(f_item->functions.input_key)) {
				if (ZT_FUNCTION_POINTER_ACCESS(f_item->functions.input_key, zt_guiItemInputKey_Func)(gm->focus_item, input_keys, input_key_strokes, f_item->functions.user_data)) {
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
	gm->mouse_just_clicked = input_mouse->leftJustPressed() || input_mouse->middleJustPressed() || input_mouse->rightJustPressed();

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
					ztVec2 top_left = zt_vec2(pos.x - item->size.x / 2.f, pos.y + item->size.y / 2.f);
					ztVec2 btm_right = zt_vec2(pos.x + item->size.x / 2.f, pos.y - item->size.y / 2.f);

					if (mpos.x >= top_left.x && mpos.x < btm_right.x && mpos.y >= btm_right.y && mpos.y <= top_left.y) {
						return true;
					}
					return false;
				}

				// clicks and releases
				static bool processMouseFocusEvent(ztGuiManager *gm, ztGuiItem *item, ztInputMouse *input_mouse, ztInputKeys *input_keys, const ztVec2& mpos)
				{
					if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled))) {
						zt_assert(item != gm->item_has_mouse);
						return false;
					}

					if (gm->item_has_mouse != nullptr && gm->item_has_mouse != item) {
						ztGuiItem *mi = gm->item_has_mouse;
						if (mi) {
							bool result = processMouseFocusEvent(gm, mi, input_mouse, input_keys, mpos);
							if (gm->item_has_mouse != nullptr && !zt_guiItemIsShowing(gm->item_has_mouse)) {
								zt_bitRemove(gm->item_has_mouse->state_flags, zt_bit(ztGuiItemStates_MouseClick));
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
							if (child) {
								while (child->sib_next) {
									child = child->sib_next;
								}

								while (child) {
									if (processMouseFocusEvent(gm, child, input_mouse, input_keys, mpos)) {
										return true;
									}
									child = child->sib_prev;
								}
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

					if (mouse_intersecting && gm->item_has_mouse == nullptr && (input_mouse->leftJustPressed() || input_mouse->rightJustPressed() || input_mouse->middleJustPressed()) && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_WantsFocus)) {
						gm->item_has_mouse = item;
						gm->item_has_mouse->state_flags |= zt_bit(ztGuiItemStates_MouseClick);
						recv_focus = true;
					}

					if (mouse_intersecting || gm->item_has_mouse == item) {
						if (mouse_intersecting) {
							gm->item_cache_flags[item->id] |= ztGuiManagerItemCacheFlags_MouseOver;
							item->state_flags |= zt_bit(ztGuiItemStates_MouseOver);
						}
						if (ZT_FUNCTION_POINTER_IS_VALID(item->functions.input_mouse) && ZT_FUNCTION_POINTER_ACCESS(item->functions.input_mouse, zt_guiItemInputMouse_Func)(item, input_mouse, input_keys[ztInputKeys_Control].pressed(), input_keys[ztInputKeys_Menu].pressed(), input_keys[ztInputKeys_Shift].pressed(), item->functions.user_data)) {
							recv_focus = true;
						}
					}

					if (gm->item_has_mouse == item && (input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased())) {
						zt_bitRemove(gm->item_has_mouse->state_flags, zt_bit(ztGuiItemStates_MouseClick));
						gm->item_has_mouse = nullptr;
					}
					return recv_focus;
				}

				// movements and scroll wheel
				static bool mouseProcessNonFocusEvent(ztGuiManager *gm, ztGuiItem *item, ztInputMouse *input_mouse, ztInputKeys *input_keys, const ztVec2& mpos)
				{
					if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled))) {
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
								if (mouseProcessNonFocusEvent(gm, child, input_mouse, input_keys, mpos)) {
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
							item->state_flags |= zt_bit(ztGuiItemStates_MouseOver);
						}
						if (ZT_FUNCTION_POINTER_IS_VALID(item->functions.input_mouse) && ZT_FUNCTION_POINTER_ACCESS(item->functions.input_mouse, zt_guiItemInputMouse_Func)(item, input_mouse, input_keys[ztInputKeys_Control].pressed(), input_keys[ztInputKeys_Menu].pressed(), input_keys[ztInputKeys_Shift].pressed(), item->functions.user_data)) {
							return true;
						}
					}
					return handled_event;
				}
			};

			//bool mouse_just_released = input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased();
			if (mouse_captured || input_mouse->leftPressed() || input_mouse->rightPressed() || input_mouse->middlePressed() ||
				input_mouse->leftJustReleased() || input_mouse->rightJustReleased() || input_mouse->middleJustReleased()) {
				if (local::processMouseFocusEvent(gm, child, input_mouse, input_keys, mpos)) {
					gm->keyboard_focus = true;
					if (zt_bitIsSet(child->behavior_flags, ztGuiItemBehaviorFlags_BringToFront)) {
						// need to make this particular child the last in the series
						if (child->sib_next && !(child->sib_next->type == ztGuiItemType_Window && zt_bitIsSet(child->sib_next->behavior_flags, ztGuiWindowBehaviorFlags_Modal))) {// && (!zt_bitIsSet(child->sib_next->behavior_flags, ztGuiItemBehaviorFlags_BringToFront) || !zt_bitIsSet(child->sib_next->state_flags, zt_bit(ztGuiItemStates_Visible)))) {
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
			else if (local::mouseProcessNonFocusEvent(gm, child, input_mouse, input_keys, mpos)) {
				break; // exit the loop
			}

		}
		if (child->type == ztGuiItemType_Window && zt_bitIsSet(child->behavior_flags, ztGuiWindowBehaviorFlags_Modal)) {
			break;
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

	gm->in_update = false;

	return result;
}

// ================================================================================================================================================================================================

void zt_drawListAddGuiThemeSprite(ztDrawList *draw_list, ztGuiThemeSprite *theme_sprite, const ztVec2& pos, const ztVec2& size)
{
	ZT_PROFILE_GUI("zt_drawListAddGuiThemeSprite");

	if (theme_sprite->type == ztGuiThemeSpriteType_Sprite) {
		if (!zt_real32Eq(size.x, theme_sprite->s.half_size.x * 2) || !zt_real32Eq(size.y, theme_sprite->s.half_size.y * 2)) {
			ztVec3 scale = ztVec3::one;
			scale.x = size.x / (theme_sprite->s.half_size.x * 2);
			scale.y = size.y / (theme_sprite->s.half_size.y * 2);

			zt_drawListAddSprite(draw_list, &theme_sprite->s, zt_vec3(pos.x, pos.y, 0), ztVec3::zero, scale);
		}
		else {
			zt_drawListAddSprite(draw_list, &theme_sprite->s, zt_vec3(pos.x, pos.y, 0));
		}
	}
	else {
		zt_drawListAddSpriteNineSlice(draw_list, &theme_sprite->sns, pos, size);
	}
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztVec2 zt_guiThemeSpriteGetSize(ztGuiThemeSprite *sprite)
{
	ZT_PROFILE_GUI("zt_guiThemeSpriteGetSize");

	if (sprite->type == ztGuiThemeSpriteType_Sprite) {
		return zt_vec2(sprite->s.half_size.x * 2.f, sprite->s.half_size.y * 2.f);
	}
	else {
		return zt_vec2(sprite->sns.sp_w.x + sprite->sns.sp_e.x, sprite->sns.sp_n.y + sprite->sns.sp_s.y);
	}
}

// ================================================================================================================================================================================================

ztVec2 zt_guiThemeButtonSpriteGetSize(ztGuiThemeButtonSprite *sprite)
{
	ZT_PROFILE_GUI("zt_guiThemeButtonSpriteGetSize");

	ztVec2 normal = zt_guiThemeSpriteGetSize(&sprite->normal);
	ztVec2 highlight = zt_guiThemeSpriteGetSize(&sprite->highlight);
	ztVec2 pressed   = zt_guiThemeSpriteGetSize(&sprite->pressed);

	return zt_vec2(zt_max(normal.x, zt_max(highlight.x, pressed.x)), zt_max(normal.y, zt_max(highlight.y, pressed.y)));
}

// ================================================================================================================================================================================================

void zt_guiManagerRender(ztGuiManager *gm, ztDrawList *draw_list, r32 dt)
{
	ZT_PROFILE_GUI("zt_guiManagerRender");

	zt_returnOnNull(draw_list);
	zt_returnOnNull(gm);

	gm->in_update = true;
	_zt_guiManagerUpdatePre(gm, dt);
	gm->in_update = false;

//#define _zt_guiManagerRenderClipAreas

	struct local
	{
		static void clipTo(ztDrawList *draw_list, ztVec2 pos, ztVec2 size)
		{
			r32 ppu = zt_pixelsPerUnit();
			size.y += 2 / ppu;
			size.x += 2 / ppu;
			zt_alignToPixel(&pos, ppu);
			zt_alignToPixel(&size, ppu);
			zt_drawListPushClipRegion(draw_list, pos, size);
		}

		static void renderItem(ztGuiManager *gm, ztGuiItem *item, ztDrawList *draw_list, const ztVec2& offset)
		{
			if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible)) || item->size.x <= 0 || item->size.y <= 0) {
				zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Dirty));
				return;
			}

			ztVec2 pos = item->pos + offset;

			ztGuiTheme *theme = item->theme == nullptr ? &gm->default_theme : item->theme;

			if (item->parent == nullptr && zt_bitIsSet(theme->flags, ztGuiThemeFlags_SeparatePasses) && ZT_FUNCTION_POINTER_IS_VALID(theme->pass_begin)) {
				ZT_FUNCTION_POINTER_ACCESS(theme->pass_begin, ztGuiThemeRenderPassBegin_Func)(theme, item, draw_list);
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

			if (ZT_FUNCTION_POINTER_IS_VALID(item->functions.render)) {
				ZT_FUNCTION_POINTER_ACCESS(item->functions.render, zt_guiItemRender_Func)(item, draw_list, theme, offset, !zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled)), item->functions.user_data);
			}

			zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Dirty));

#			if defined(ZT_DEBUG)
				if (item->debug_highlight != ztVec4::zero) {
					zt_drawListPushTexture(draw_list, ztTextureDefault);
					zt_drawListPushColor(draw_list, item->debug_highlight);
					zt_drawListAddEmptyRect(draw_list, pos, item->size);
					zt_drawListPopColor(draw_list);
					zt_drawListPopTexture(draw_list);
				}
#			endif
			if (!clip && zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_ClipChildren) ) {
				clip = true;
				if (item->clip_area != ztVec4::zero) {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, zt_vec4(1, 1, 0, 1));
						zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
						zt_drawListPopColor(draw_list);
#					else
					clipTo(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
#					endif
				}
				else {
#					if defined(_zt_guiManagerRenderClipAreas)
						zt_drawListPushColor(draw_list, zt_vec4(0, 1, 1, 1));
						zt_drawListAddEmptyRect(draw_list, pos, item->size);
						zt_drawListPopColor(draw_list);
#					else
					clipTo(draw_list, pos, item->size);
						//zt_drawListPushClipRegion(draw_list, pos, item->size);
#					endif
				}
			}
			else if (clip && !zt_bitIsSet(item->behavior_flags, ztGuiItemBehaviorFlags_ClipChildren)) {
#				if defined(_zt_guiManagerRenderClipAreas)
					zt_drawListPushColor(draw_list, zt_vec4(0, 1, 0, .5f));
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
					zt_drawListPushColor(draw_list, zt_vec4(1, 0, 0, .5f));
					if (item->clip_area != ztVec4::zero) {
						zt_drawListAddEmptyRect(draw_list, pos + item->clip_area.xy, item->clip_area.zw);
					}
					else {
						zt_drawListAddEmptyRect(draw_list, pos, item->size);
					}
					zt_drawListPopColor(draw_list);
#				else
					zt_drawListPopClipRegion(draw_list);
#				endif
			}

			if(zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_PostRender))) {
				zt_guiThemePostRender(theme, draw_list, item, pos);
				zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_PostRender));
			}

			if (item->parent == nullptr && zt_bitIsSet(theme->flags, ztGuiThemeFlags_SeparatePasses) && ZT_FUNCTION_POINTER_IS_VALID(theme->pass_end)) {
				ZT_FUNCTION_POINTER_ACCESS(theme->pass_end, ztGuiThemeRenderPassEnd_Func)(theme, item, draw_list);
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

	gm->in_update = true;
	_zt_guiManagerUpdatePost(gm, dt);
	gm->in_update = false;

#	if defined(_zt_guiManagerRenderClipAreas)
#		undef _zt_guiManagerRenderClipAreas
#	endif
}

// ================================================================================================================================================================================================

void zt_guiSetActiveManager(ztGuiManager *gm)
{
	zt_returnOnNull(gm);
	zt_gui->gui_manager_active = gm;
}

// ================================================================================================================================================================================================

ztGuiManager *zt_guiGetActiveManager()
{
	return zt_gui->gui_manager_active;
}

// ================================================================================================================================================================================================

void zt_guiManagerSetKeyboardFocus(ztGuiManager *gm, bool keyboard_focus)
{
	zt_returnOnNull(gm);
	gm->keyboard_focus = keyboard_focus;
}

// ================================================================================================================================================================================================

bool zt_guiManagerHasKeyboardFocus(ztGuiManager *gm)
{
	zt_returnValOnNull(gm, false);
	return gm->keyboard_focus;
}

// ================================================================================================================================================================================================

bool zt_guiManagerMouseOverGui(ztGuiManager *gm)
{
	zt_returnValOnNull(gm, false);
	return gm->mouse_over_gui;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_guiProcessDrag(ztGuiItem::ztDragState *drag_state, ztGuiManager *gm, ztVec2* pos, ztInputMouse *input_mouse)
{
	ZT_PROFILE_GUI("_zt_guiProcessDrag");

	if (drag_state->dragging) {
		if (input_mouse->leftJustReleased()) {
			drag_state->dragging = false;
		}
		else {
			ztVec2 drag_pos = zt_cameraOrthoScreenToWorld(gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
			*pos = drag_pos - zt_vec2(drag_state->offset_x, drag_state->offset_y);
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

// ================================================================================================================================================================================================

ztGuiItem *_zt_guiMakeItemBase(ztGuiItem *parent, ztGuiItemType_Enum type, i32 item_flags, i32 draw_list_size)
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
	item->user_data      = nullptr;

	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	
	if (draw_list_size != 0) {
		item->draw_list = zt_mallocStructArena(ztDrawList, gm->arena);
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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiWindowUpdate))
{
	ZT_PROFILE_GUI("_zt_guiWindowUpdate");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized))) {
		ztGuiTheme *theme = zt_guiItemGetTheme(item);
		
		zt_guiThemeUpdateItem(theme, item);

		if (item->window.button_collapse) {
			zt_guiThemeUpdateSubitem(theme, item, item->window.button_collapse);
			ztVec2 offset_collapse = zt_vec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCollapseButtonOffsetX, item), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCollapseButtonOffsetY, item));
			zt_guiItemSetPosition(item->window.button_collapse, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCollapseButtonAlign, item), zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCollapseButtonAnchor, item), offset_collapse);
		}
		if (item->window.button_close) {
			zt_guiThemeUpdateSubitem(theme, item, item->window.button_close);
			ztVec2 offset_close = zt_vec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCloseButtonOffsetX, item), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCloseButtonOffsetY, item));
			zt_guiItemSetPosition(item->window.button_close, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCloseButtonAlign, item), zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCloseButtonAnchor, item), offset_close);
		}

		r32 title_height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight, item);

		if (item->window.menubar) {
			item->window.menubar->size.x = item->size.x;
			zt_guiItemSetPosition(item->window.menubar, ztAlign_Top, ztAnchor_Top, zt_vec2(0, -title_height));
			title_height += item->window.menubar->size.y;
		}

		if (item->window.content != item) {
			ztVec2 pos = ztVec2::zero;
			ztVec2 size = item->size;

			size.x -= zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingX, item) * 2;
			size.y -= zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingY, item) * 2 + title_height;

			pos.y -= title_height / 2;

			item->window.content->pos = pos;
			item->window.content->size = size;
			item->window.content->min_size = size;
		}
	}

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiWindowRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiWindowOnButtonClose, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiWindowOnButtonClose))
{
	ZT_PROFILE_GUI("_zt_guiWindowOnButtonClose");

	ztGuiItem *window = zt_guiItemGetTopLevelParent(button);

	if (zt_bitIsSet(window->behavior_flags, ztGuiWindowBehaviorFlags_CloseHides)) {
		zt_guiItemHide(window);
	}
	else {
		zt_guiItemQueueFree(window);
	}
}

// ================================================================================================================================================================================================

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
		window->size.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight, window) + zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingY, window) * 2;

		r32 y_diff = window->window.size[1] - window->size.y;
		window->pos.y += y_diff / 2;
	}

	window->state_flags |= zt_bit(ztGuiItemStates_Resized);
}

// ================================================================================================================================================================================================

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

				r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
				r32 resize_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCornerResizeW, item);
				r32 resize_h = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowCornerResizeH, item);
				ztVec2 resize_pos = zt_vec2(pos.x + ((item->size.x / 2) - (resize_w / 2 + padding)), pos.y - ((item->size.y / 2) - (resize_w / 2.f + padding)));
				ztVec2 resize_size = zt_vec2(resize_w + padding, resize_h + padding);
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
			r32 height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight, item);
			r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowPaddingY, item);

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

// ================================================================================================================================================================================================

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
			ztGuiItem *button_close = zt_guiMakeButton(item, nullptr, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCloseButtonBehaviorFlags, item));
			item->window.button_close = button_close;
			zt_guiItemSetName(button_close, "Close");
			zt_guiButtonSetCallback(button_close, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiWindowOnButtonClose));
			zt_guiThemeUpdateSubitem(theme, item, button_close);
		}
		if (zt_bitIsSet(behavior_flags, ztGuiWindowBehaviorFlags_AllowCollapse)) {
			ztGuiItem *button_collapse = zt_guiMakeButton(item, nullptr, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_WindowCollapseButtonBehaviorFlags, item));
			item->window.button_collapse = button_collapse;
			zt_guiItemSetName(item->window.button_collapse, "Collapse");
			zt_guiThemeUpdateSubitem(theme, item, button_collapse);
			zt_guiButtonSetCallback(item->window.button_collapse, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiWindowOnButtonToggle));
		}
	}
	else {
		item->window.content = item;
	}

	item->functions.render = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiWindowRender);

	zt_guiItemSetSize(item, zt_vec2(7, 5));
	zt_guiItemSetLabel(item, title);

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiWindowInputMouse);
	item->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiWindowUpdate);

	if (zt_bitIsSet(behavior_flags, ztGuiWindowBehaviorFlags_Modal)) {
		zt_guiItemBringToFront(item);
	}

	return item;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeScrollWindow(const char *title, i32 scroll_dir, i32 behavior_flags)
{
	ZT_PROFILE_GUI("zt_guiMakeScrollWindow");

	i32 scroll_flags = (zt_bitIsSet(scroll_dir, ztGuiItemOrient_Horz) ? ztGuiWindowInternalBehaviorFlags_ScrollHorz : 0) |
					   (zt_bitIsSet(scroll_dir, ztGuiItemOrient_Vert) ? ztGuiWindowInternalBehaviorFlags_ScrollVert : 0);

	return zt_guiMakeWindow(title, scroll_flags | behavior_flags);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiWindowGetContentParent(ztGuiItem *window)
{
	ZT_PROFILE_GUI("zt_guiWindowGetContentParent");

	zt_assertReturnValOnFail(window->type == ztGuiItemType_Window, nullptr);

	if (zt_bitIsSet(window->behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollHorz) || zt_bitIsSet(window->behavior_flags, ztGuiWindowInternalBehaviorFlags_ScrollVert)) {
		return window->window.content->scrolled_container.contained_item;
	}

	return window->window.content;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiPanelCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiPanelCleanup))
{
	ZT_PROFILE_GUI("_zt_guiPanelCleanup");

	if (item->panel.user_data) {
		zt_freeArena(item->panel.user_data, item->panel.arena);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiPanelRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiPanelRender))
{
	ZT_PROFILE_GUI("_zt_guiPanelRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakePanel(ztGuiItem *parent, i32 behavior_flags, void *user_data, ztMemoryArena *arena)
{
	ZT_PROFILE_GUI("zt_guiMakePanel");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Panel, behavior_flags);
	zt_returnValOnNull(item, nullptr);

	item->panel.user_data = user_data;
	item->panel.arena = arena;
	if (user_data) {
		item->functions.cleanup = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiPanelCleanup);
	}

	item->functions.render = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiPanelRender);

	return item;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiCollapsingPanelUpdate))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelUpdate");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized)) || item->collapsing_panel.content_panel_size != item->collapsing_panel.content_panel->size) {
		ztGuiTheme *theme = zt_guiItemGetTheme(item);

		r32 button_offset_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelButtonOffsetX, item);
		r32 button_offset_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelButtonOffsetY, item);

		zt_guiItemSetPosition(item->collapsing_panel.button, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, zt_vec2(button_offset_x, button_offset_y));

		ztGuiItem *content_panel = item->collapsing_panel.content_panel;

		r32 panel_height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelHeight, item);
		if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
			item->size.y = panel_height;
			zt_guiItemHide(item->collapsing_panel.content_panel);
		}
		else {
			ztVec2 size = zt_guiSizerGetMinSize(item->collapsing_panel.content_panel);

			size.y += zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelPaddingY, item) * 2;

			content_panel->size.x = item->size.x - zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelPaddingX, item) * 2;
			content_panel->size.y = size.y;
			item->size.x = zt_max(item->size.x, size.x);
			item->size.y = panel_height + size.y;

			content_panel->pos.x = 0;
			content_panel->pos.y = -panel_height / 2.f;
			zt_guiItemShow(item->collapsing_panel.content_panel);
		}

		zt_guiSizerRecalcImmediately(zt_guiItemGetTopLevelParent(item));

		item->collapsing_panel.content_panel_size = content_panel->size;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiCollapsingPanelRender))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ztInternal bool _zt_guiCollapsingPanelIsCollapsed(ztGuiItem *item)
{
	return zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed));
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiCollapsingPanelToggle(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelToggle");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
		zt_bitRemove(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed));
	}
	else {
		item->state_flags |= zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed);
		zt_guiItemHide(item->collapsing_panel.content_panel);
	}

	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	zt_guiThemeUpdateSubitem(theme, item, item->collapsing_panel.button);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelOnToggle, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiCollapsingPanelOnToggle))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelOnToggle");

	ztGuiItem *item = button->parent;
	_zt_guiCollapsingPanelToggle(item);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCollapsingPanelBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiCollapsingPanelBestSize))
{
	ZT_PROFILE_GUI("_zt_guiCollapsingPanelBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeCollapsingPanel(ztGuiItem *parent, const char *label)
{
	ZT_PROFILE_GUI("zt_guiMakeCollapsingPanel");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_CollapsingPanel, /*ztGuiItemBehaviorFlags_ClipChildren*/ 0, (zt_strLen(label) * 2) + 19);
	zt_returnValOnNull(item, nullptr);

	item->state_flags |= zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztGuiItem *button = zt_guiMakeButton(item, nullptr, ztGuiButtonBehaviorFlags_NoBackground | ztGuiButtonBehaviorFlags_OnPressDip);
	item->collapsing_panel.button = button;

	zt_guiItemSetName(button, "Collapse Button");
	zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCollapsingPanelOnToggle));
	zt_guiThemeUpdateSubitem(theme, item, button);

	ztGuiItem *content_panel = zt_guiMakePanel(item);
	item->collapsing_panel.content_panel = content_panel;
	zt_guiItemSetName(content_panel, "content-panel");

	zt_guiItemHide(content_panel);

	item->state_flags |= zt_bit(ztGuiItemStates_Dirty) | zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed);

	zt_guiItemSetLabel(item, label);

	item->functions.update    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCollapsingPanelUpdate);
	item->functions.render    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCollapsingPanelRender);
	item->functions.best_size = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCollapsingPanelBestSize);

	_zt_guiCollapsingPanelBestSize(item, nullptr, nullptr, &item->size, theme, nullptr);
	zt_guiCollapsingPanelExpand(item);

	return item;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiCollapsingPanelGetContentParent(ztGuiItem *panel)
{
	zt_assertReturnValOnFail(panel->type == ztGuiItemType_CollapsingPanel, nullptr);
	return panel->collapsing_panel.content_panel;
}

// ================================================================================================================================================================================================

void zt_guiCollapsingPanelCollapse(ztGuiItem *panel)
{
	zt_assertReturnOnFail(panel->type == ztGuiItemType_CollapsingPanel);
	if (!_zt_guiCollapsingPanelIsCollapsed(panel)) {
		_zt_guiCollapsingPanelToggle(panel);
	}
}

// ================================================================================================================================================================================================

void zt_guiCollapsingPanelExpand(ztGuiItem *panel)
{
	zt_assertReturnOnFail(panel->type == ztGuiItemType_CollapsingPanel);
	if (_zt_guiCollapsingPanelIsCollapsed(panel)) {
		_zt_guiCollapsingPanelToggle(panel);
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiStaticTextRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiStaticTextRender))
{
	ZT_PROFILE_GUI("_zt_guiStaticTextRender");
	//	zt_assert(zt_strLen(item->label) < item->draw_list->commands_size / 2); // this means you need to set the max chars in the constructor to be higher

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiStaticTextBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiStaticTextBestSize))
{
	ZT_PROFILE_GUI("_zt_guiStaticTextBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeStaticText(ztGuiItem *parent, const char *label, i32 behavior_flags, int max_chars)
{
	ZT_PROFILE_GUI("zt_guiMakeStaticText");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_StaticText, behavior_flags);// , zt_max(zt_strLen(label), max_chars) * 2);
	zt_returnValOnNull(item, nullptr);

	item->functions.render    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiStaticTextRender);
	item->functions.best_size = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiStaticTextBestSize);

	zt_guiItemSetLabel(item, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	zt_guiThemeSizeItem(theme, item);

	return item;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiButtonBaseRender))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiButtonBaseCleanup))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseCleanup");

	if (item->button.icon) {
		zt_freeArena(item->button.icon, item->gm->arena);
	}
}
// ================================================================================================================================================================================================

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
			if (ZT_FUNCTION_POINTER_IS_VALID(item->button.on_pressed)) {
				ZT_FUNCTION_POINTER_ACCESS(item->button.on_pressed, zt_guiButtonPressed_Func)(item, item->button.on_pressed_user_data);
			}
			return true;
		}
	}
	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiButtonBaseBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiButtonBaseBestSize))
{
	ZT_PROFILE_GUI("_zt_guiButtonBaseBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ================================================================================================================================================================================================

ztInternal ztGuiItem *_zt_guiMakeButtonBase(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("_zt_guiMakeButtonBase");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Button, behavior_flags | ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus, zt_strLen(label) * 2);
	zt_returnValOnNull(item, nullptr);

	zt_guiItemSetLabel(item, label);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->button.live_value = live_value;
	item->button.on_pressed = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->button.icon       = nullptr;
	item->button.text_pos   = 0;

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiButtonBaseInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiButtonBaseRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiButtonBaseBestSize);
	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiButtonBaseCleanup);

	if (item->button.live_value) {
		if (!(zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsCheckbox) || zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio) || zt_bitIsSet(behavior_flags, ztGuiButtonInternalBehaviorFlags_IsToggleButton))) {
			*item->button.live_value = false;
		}
		else if (*item->button.live_value) {
			item->state_flags |= zt_bit(ztGuiButtonInternalStates_IsToggled);
		}

		item->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiButtonBaseUpdate);
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

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeButton(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeButton");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags, live_value);
}

// ================================================================================================================================================================================================

void zt_guiButtonSetIcon(ztGuiItem *button, ztSprite *icon)
{
	ZT_PROFILE_GUI("zt_guiButtonSetIcon");

	zt_returnOnNull(button);
	zt_assertReturnOnFail(button->type == ztGuiItemType_Button || button->type == ztGuiItemType_ToggleButton);

	if (icon == nullptr) {
		// remove icon
		if (button->button.icon != nullptr) {
			zt_freeArena(button->button.icon, button->gm->arena);
			button->button.icon = nullptr;
		}
	}
	else {
		if (button->button.icon == nullptr) {
			button->button.icon = zt_mallocStructArena(ztSprite, button->gm->arena);
		}
		*button->button.icon = *icon;
		button->button.icon->anchor = ztVec2::zero;
	}

	_zt_guiButtonBaseBestSize(button, nullptr, nullptr, &button->size, zt_guiItemGetTheme(button), button->functions.user_data);
}

// ================================================================================================================================================================================================

void zt_guiButtonSetTextPosition(ztGuiItem *button, i32 align_flags)
{
	zt_returnOnNull(button);
	zt_assertReturnOnFail(button->type == ztGuiItemType_Button || button->type == ztGuiItemType_ToggleButton);

	button->button.text_pos = align_flags;
}

// ================================================================================================================================================================================================

void zt_guiButtonSetCallback(ztGuiItem *button, ZT_FUNCTION_POINTER_VAR(on_pressed, zt_guiButtonPressed_Func), void *user_data)
{
	zt_returnOnNull(button);
	zt_assertReturnOnFail(button->type == ztGuiItemType_Button || button->type == ztGuiItemType_ToggleButton || button->type == ztGuiItemType_Checkbox || button->type == ztGuiItemType_RadioButton);

	button->button.on_pressed = on_pressed;
	button->button.on_pressed_user_data = user_data;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeToggleButton(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeToggleButton");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags | ztGuiButtonInternalBehaviorFlags_IsToggleButton, live_value);
}

// ================================================================================================================================================================================================

bool zt_guiToggleButtonGetValue(ztGuiItem *button)
{
	zt_returnValOnNull(button, false);
	zt_assertReturnValOnFail(button->type == ztGuiItemType_ToggleButton, false);

	return zt_bitIsSet(button->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeCheckbox(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeCheckbox");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags | ztGuiButtonInternalBehaviorFlags_IsToggleButton | ztGuiButtonInternalBehaviorFlags_IsCheckbox, live_value);
}

// ================================================================================================================================================================================================

bool zt_guiCheckboxGetValue(ztGuiItem *checkbox)
{
	zt_returnValOnNull(checkbox, false);
	zt_assertReturnValOnFail(checkbox->type == ztGuiItemType_Checkbox, false);

	return zt_bitIsSet(checkbox->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeRadioButton(ztGuiItem *parent, const char *label, i32 behavior_flags, bool *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeRadioButton");

	return _zt_guiMakeButtonBase(parent, label, behavior_flags | ztGuiButtonInternalBehaviorFlags_IsToggleButton | ztGuiButtonInternalBehaviorFlags_IsRadio, live_value);
}

// ================================================================================================================================================================================================

bool zt_guiRadioButtonGetValue(ztGuiItem *radio)
{
	zt_returnValOnNull(radio, false);
	zt_assertReturnValOnFail(radio->type == ztGuiItemType_RadioButton, false);

	return zt_bitIsSet(radio->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
}

// ================================================================================================================================================================================================

void zt_guiRadioButtonSetValue(ztGuiItem *radio, bool value)
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
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal void _zt_guiSliderBaseCalcHandleSizeAndPos(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSliderBaseCalcHandleSizeAndPos");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	r32 value = item->slider.orient == ztGuiItemOrient_Horz ? item->slider.value : 1.f - item->slider.value;
	r32 size_item = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;

	if (item->type == ztGuiItemType_Slider) {
		item->slider.handle_size = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item);

		r32 handle_size = item->slider.handle_size;
		r32 size_value = size_item - handle_size;
		item->slider.handle_pos = (size_item / -2.f) + (size_value * value) + handle_size / 2.f;
	}
	else {
		r32 scrollbar_button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, item);
		size_item -= scrollbar_button_w * 2;

		item->slider.handle_size = zt_max(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinHandleSize, item), size_item * item->slider.handle_pct);

		r32 handle_size = item->slider.handle_size;
		r32 size_value  = size_item - handle_size;
		r32 offset      = handle_size / 2.f;

		item->slider.handle_pos = (size_item / -2.f) + (size_value * value) + offset;
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiSliderDoCallback(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSliderDoCallback");

	if (ZT_FUNCTION_POINTER_IS_VALID(item->slider.on_scrollbar_scroll)) {
		ZT_FUNCTION_POINTER_ACCESS(item->slider.on_scrollbar_scroll, zt_guiScrollbarScrolled_Func)(item, item->slider.value, item->slider.on_scrollbar_scroll_user_data);
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
					_zt_guiSliderDoCallback(item);
					item->slider.press_time = .1f;
				}
			}
			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed)) && zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosHighlight))) {
				item->slider.press_time -= dt;
				if (item->slider.press_time <= 0) {
					zt_guiScrollbarStepPos(item);
					_zt_guiSliderDoCallback(item);
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
	ZT_PROFILE_GUI("_zt_guiSliderBaseRender");

	zt_guiThemeRender(theme, draw_list, item, item->pos + offset);
}

// ================================================================================================================================================================================================

ztInternal int _zt_guiItemSliderMouseOverButton(ztGuiItem *item, ztGuiTheme *theme, ztVec2& mpos) // 0 = none, -1 = neg, 1 = pos
{
	ZT_PROFILE_GUI("_zt_guiItemSliderMouseOverButton");

	if (item->type != ztGuiItemType_Scrollbar || !zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver)) {
		return 0;
	}

	r32 scrollbar_button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, item);
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

	r32 slider_handle_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item);

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
		_zt_guiSliderDoCallback(item);
	}
	else {
		r32 handle_size = item->slider.handle_size;
		r32 size_item = item->slider.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y;
		r32 size_value = size_item - handle_size;

		r32 button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, item);

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
	_zt_guiSliderDoCallback(item);
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
					_zt_guiSliderDoCallback(item);
					item->slider.press_time = 0.25f;
				}
				else if (button == 1) {
					item->state_flags |= zt_bit(ztGuiSliderInternalStates_PosPressed);
					zt_guiScrollbarStepPos(item);
					_zt_guiSliderDoCallback(item);
					item->slider.press_time = 0.25f;
				}
			}
		}
		else if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_NegPressed)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiSliderInternalStates_PosPressed))) {
			// do nothing
		}
		else {
			if (item->slider.orient == ztGuiItemOrient_Horz) {
				ztVec2 handle_pos = zt_vec2(item->slider.handle_pos, 0);
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
				ztVec2 handle_pos = zt_vec2(0, item->slider.handle_pos);
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

	zt_guiThemeSizeItem(theme, item);

	if (item->size == ztVec2::zero) {
		if (item->type == ztGuiItemType_Slider) {
			if (item->slider.orient == ztGuiItemOrient_Horz) {
				min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item) * 2;
				min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleMinHeight, item);
			}
			else {
				min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item) * 2;
				min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleMinHeight, item);
			}
		}
		else {
			if (item->slider.orient == ztGuiItemOrient_Horz) {
				min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, item) * 2;
				min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinWidth, item);
			}
			else {
				min_size->y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, item) * 2;
				min_size->x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinWidth, item);
			}
		}

		*size = *min_size;
	}
	else {
		*size = item->size;
	}
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

	item->slider.on_scrollbar_scroll = ZT_FUNCTION_POINTER_TO_VAR_NULL;

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiItemSliderInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSliderBaseRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiItemSliderBestSize);
	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSliderBaseUpdate);

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

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeSlider(ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeSlider");

	return _zt_guiMakeSliderBase(parent, orient, live_value, false);
}

// ================================================================================================================================================================================================

r32 zt_guiSliderGetValue(ztGuiItem *slider)
{
	zt_assertReturnValOnFail(slider->type == ztGuiItemType_Slider, 0);

	return slider->slider.value;
}

// ================================================================================================================================================================================================

void zt_guiSliderSetValue(ztGuiItem *slider, r32 value)
{
	zt_assertReturnOnFail(slider->type == ztGuiItemType_Slider);

	slider->slider.value = value;
	if (slider->slider.live_value) {
		*slider->slider.live_value = value;
	}
}

// ================================================================================================================================================================================================

void zt_guiSliderSetCallback(ztGuiItem *slider, ZT_FUNCTION_POINTER_VAR(callback, zt_guiSliderChanged_Func), void *user_data)
{
	ZT_PROFILE_GUI("zt_guiSliderSetCallback");
	zt_assertReturnOnFail(slider->type == ztGuiItemType_Slider);

	slider->slider.on_scrollbar_scroll = callback;
	slider->slider.on_scrollbar_scroll_user_data = user_data;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeScrollbar(ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeScrollbar");

	return _zt_guiMakeSliderBase(parent, orient, live_value, true);
}

// ================================================================================================================================================================================================

r32 zt_guiScrollbarGetValue(ztGuiItem *scrollbar)
{
	zt_assertReturnValOnFail(scrollbar->type == ztGuiItemType_Scrollbar, 0);

	return scrollbar->slider.value;
}

// ================================================================================================================================================================================================

void zt_guiScrollbarSetValue(ztGuiItem *scrollbar, r32 value)
{
	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.value = value;
	if (scrollbar->slider.live_value) {
		*scrollbar->slider.live_value = value;
	}
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);
}

// ================================================================================================================================================================================================

void zt_guiScrollbarSetSteps(ztGuiItem *scrollbar, r32 step_single, r32 step_page)
{
	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.step = zt_abs(step_single);
	scrollbar->slider.step_page = zt_abs(step_page);

	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);
}

// ================================================================================================================================================================================================

void zt_guiScrollbarSetStepsAndPercent(ztGuiItem *scrollbar, r32 step_single, r32 step_page, r32 percent)
{
	zt_guiScrollbarSetSteps(scrollbar, step_single, step_page);
	zt_guiScrollbarSetPercent(scrollbar, percent);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiScrollbarSetPercent(ztGuiItem *scrollbar, r32 percent)
{
	ZT_PROFILE_GUI("zt_guiScrollbarSetPercent");

	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.handle_pct = zt_clamp(percent, 0, 1);
	_zt_guiSliderBaseCalcHandleSizeAndPos(scrollbar);
}

// ================================================================================================================================================================================================

void zt_guiScrollbarSetCallback(ztGuiItem *scrollbar, ZT_FUNCTION_POINTER_VAR(callback, zt_guiScrollbarScrolled_Func), void *user_data)
{
	ZT_PROFILE_GUI("zt_guiScrollbarSetCallback");
	zt_assertReturnOnFail(scrollbar->type == ztGuiItemType_Scrollbar);

	scrollbar->slider.on_scrollbar_scroll = callback;
	scrollbar->slider.on_scrollbar_scroll_user_data = user_data;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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
	zt_guiItemSetPosition(item->scrolled_container.viewport, zt_vec2(item->scrolled_container.viewport_pos[0], item->scrolled_container.viewport_pos[1]));

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollContainerPaddingX, item);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollContainerPaddingY, item);

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
	item->scrolled_container.viewport->clip_area = zt_vec4(0, 0, size.x - padding_x * 2, size.y - padding_y * 2);

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

ztGuiItem *zt_guiMakeScrollContainer(ztGuiItem *parent, i32 behavior_flags)
{
	ZT_PROFILE_GUI("zt_guiMakeScrollContainer");

	zt_returnValOnNull(parent, nullptr);

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_ScrollContainer, ztGuiItemBehaviorFlags_LateUpdate | ztGuiItemBehaviorFlags_ClipChildren | behavior_flags);
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

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiScrollContainerInputMouse);
	item->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiScrollContainerInputKey);
	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiScrollContainerUpdate);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiScrollContainerBestSize);

	ztVec2 min_size = ztVec2::zero;
	_zt_guiScrollContainerBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiScrollContainerResetScroll(ztGuiItem *scroll)
{
	ZT_PROFILE_GUI("zt_guiScrollContainerResetScroll");

	zt_returnOnNull(scroll);
	zt_assertReturnOnFail(scroll->type == ztGuiItemType_ScrollContainer);

	scroll->scrolled_container.scroll_amt_horz = 0;
	scroll->scrolled_container.scroll_amt_vert = 0;
	_zt_guiScrollContainerUpdate(scroll, 0, scroll->functions.user_data);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

r32 zt_guiScrollContainerGetScroll(ztGuiItem *scroll, ztGuiItemOrient_Enum orient)
{
	zt_returnValOnNull(scroll, 0);
	zt_assertReturnValOnFail(scroll->type == ztGuiItemType_ScrollContainer, 0);

	if (orient == ztGuiItemOrient_Horz) {
		return scroll->scrolled_container.scroll_amt_horz;
	}
	else {
		return scroll->scrolled_container.scroll_amt_vert;
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal ztVec2 _zt_guiTextEditGetTextStartPos(ztGuiItem *item, ztGuiTheme *theme)
{
	ZT_PROFILE_GUI("_zt_guiTextEditGetTextStartPos");

	ztVec2 pos = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingX, item);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY, item);

	r32 diff_x = zt_max(0, item->textedit.content_size[0] - (item->size.x - padding_x * 2.f));
	r32 diff_y = zt_max(0, item->textedit.content_size[1] - (item->size.y - padding_y * 2.f));

	if (item->textedit.scrollbar_vert != nullptr && zt_bitIsSet(item->textedit.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		diff_x += item->textedit.scrollbar_vert->size.x;
	}
	if (item->textedit.scrollbar_horz != nullptr && zt_bitIsSet(item->textedit.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		diff_y += item->textedit.scrollbar_horz->size.y;
	}

	return zt_vec2(pos.x - item->size.x / 2.f + padding_x - (diff_x * item->textedit.scroll_amt_horz),
	              pos.y + item->size.y / 2.f - padding_y + (diff_y * item->textedit.scroll_amt_vert));
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiTextEditSizeContent(ztGuiItem *item, ztGuiTheme *theme)
{
	ZT_PROFILE_GUI("_zt_guiTextEditSizeContent");

	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID, item);
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

		r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY, item);
		int lines_shown = zt_convertToi32Floor(((item->size.y - padding_y * 2.f) - (horz ? scroll_horz->size.y : 0)) / line_height);
		r32 pct_per_line = line_height / ((lines_count - lines_shown) * line_height);

		zt_guiScrollbarSetSteps(item->textedit.scrollbar_vert, pct_per_line, lines_shown * pct_per_line);
	}
	else if (scroll_vert) {
		zt_bitRemove(scroll_vert->state_flags, zt_bit(ztGuiItemStates_Visible));
	}
}

// ================================================================================================================================================================================================

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

	r32 padding_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingX, item);
	r32 padding_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditPaddingY, item);
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

// ================================================================================================================================================================================================

ztInternal void _zt_guiTextEditCacheText(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiTextEditCacheText");

	zt_drawListReset(item->draw_list);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	zt_drawListAddText2D(item->draw_list, zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID, item), item->textedit.text_buffer, ztVec2::zero, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiTextEditGetCurrentLineInfo(ztGuiItem *item, int *beg_pos, int *end_pos, int from_pos = -1)
{
	ZT_PROFILE_GUI("_zt_guiTextEditGetCurrentLineInfo");

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

// ================================================================================================================================================================================================

ztInternal void _zt_guiTextEditRecalcCursor(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiTextEditRecalcCursor");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID, item);
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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiTextEditRender))
{
	ZT_PROFILE_GUI("_zt_guiTextEditRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiTextEditCleanup))
{
	ZT_PROFILE_GUI("_zt_guiTextEditCleanup");

	zt_stringFree(&item->gm->string_pool, item->textedit.text_buffer);
}

// ================================================================================================================================================================================================

#ifndef ZT_TEXTEDIT_WORD_SEPARATORS
#define ZT_TEXTEDIT_WORD_SEPARATORS      " \t"
#endif

#ifndef ZT_TEXTEDIT_WORD_SEPARATORS_LEN
#define ZT_TEXTEDIT_WORD_SEPARATORS_LEN     2
#endif

// ================================================================================================================================================================================================

ztInternal int _zt_guiTextEditPosNextWord(ztGuiItem *item, int str_len)
{
	ZT_PROFILE_GUI("_zt_guiTextEditPosNextWord");

	int pos = item->textedit.cursor_pos;
	bool break_next_char = item->textedit.text_buffer[pos] == '\n';
	while (++pos < str_len) {
		if (item->textedit.text_buffer[pos] == '\n') break;

		bool is_separator = false;
		zt_fjz(ZT_TEXTEDIT_WORD_SEPARATORS_LEN) {
			if ((is_separator = (item->textedit.text_buffer[pos] == ZT_TEXTEDIT_WORD_SEPARATORS[j]))) {
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

// ================================================================================================================================================================================================

ztInternal int _zt_guiTextEditPosPrevWord(ztGuiItem *item, int str_len)
{
	ZT_PROFILE_GUI("_zt_guiTextEditPosPrevWord");

	int pos = item->textedit.cursor_pos;
	while (--pos > 0) {
		if (item->textedit.text_buffer[pos - 1] == '\n') break;

		bool need_break = false;
		zt_fjz(ZT_TEXTEDIT_WORD_SEPARATORS_LEN) {
			if ((need_break = (item->textedit.text_buffer[pos - 1] == ZT_TEXTEDIT_WORD_SEPARATORS[j]))) {
				break;
			}
		}
		if (need_break) break;
	}

	return pos;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztInternal void _zt_guiTextEditSelectBeg(ztGuiItem *item, bool force = false)
{
	if (force || item->textedit.select_beg == -1) {
		item->textedit.select_beg = item->textedit.select_end = item->textedit.cursor_pos;
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiTextEditSelectEnd(ztGuiItem *item)
{
	item->textedit.select_end = item->textedit.cursor_pos;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditInputKey, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiTextEditInputKey))
{
	ZT_PROFILE_GUI("_zt_guiTextEditInputKey");

	if (ZT_FUNCTION_POINTER_IS_VALID(item->textedit.on_key)) {
		bool should_process = true;
		ZT_FUNCTION_POINTER_ACCESS(item->textedit.on_key, zt_guiTextEditKey_Func)(item, input_keys, input_key_strokes, &should_process, item->textedit.on_key_user_data);
		if (!should_process) {
			return false;
		}
	}

	bool can_edit = !zt_bitIsSet(item->behavior_flags, ztGuiTextEditBehaviorFlags_ReadOnly);
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
	if (can_edit && input_keys[ztInputKeys_Delete].justPressedOrRepeated()) {
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
	if (can_edit && input_keys[ztInputKeys_Back].justPressedOrRepeated()) {
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

	struct local
	{
		static bool processKeyStroke(ztGuiItem *item, char display_ch, int &str_len, bool &recalc_cursor, int &keys)
		{
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
				return false;
			}

			if (display_ch == '\n' && !zt_bitIsSet(item->behavior_flags, ztGuiTextEditBehaviorFlags_MultiLine)) {
				return true;
			}

			for (int j = str_len; j >= item->textedit.cursor_pos; --j) {
				item->textedit.text_buffer[j + 1] = item->textedit.text_buffer[j];
			}
			item->textedit.text_buffer[item->textedit.cursor_pos++] = display_ch;;

			if(item->textedit.cursor_pos >= str_len) {
				item->textedit.text_buffer[item->textedit.cursor_pos] = 0;
				str_len += 1;
			}

			recalc_cursor = true;
			keys += 1;
			return true;
		}
	};

	bool control = input_keys[ztInputKeys_Control].pressed();
	bool alt = input_keys[ztInputKeys_Menu].pressed();
	int keys = 0;
	if (can_edit && !control && !alt) {
		zt_fiz(ZT_MAX_INPUT_KEYSTROKES) {
			if (input_key_strokes[i] == ztInputKeys_Invalid) break;

			if (input_keys[input_key_strokes[i]].display != 0) {
				if (!local::processKeyStroke(item, shifting ? input_keys[input_key_strokes[i]].shift_display : input_keys[input_key_strokes[i]].display, str_len, recalc_cursor, keys)) {
					break;
				}
			}
		}
	}
	else {
		if (can_edit && control && input_keys[ztInputKeys_V].justPressed()) {
			if (zt_clipboardContains(ztClipboardDataType_PlainText)) {
				char buffer[1024 * 4] = {0};
				int buffer_len = 0;
				if (zt_clipboardReadPlainText(buffer, zt_elementsOf(buffer), &buffer_len)) {
					zt_fiz(buffer_len) {
						if(!local::processKeyStroke(item, buffer[i], str_len, recalc_cursor, keys)) {
							break;
						}
					}
				}
			}
		}
		else if (control && input_keys[ztInputKeys_C].justPressed()) {
			if (item->textedit.select_beg != item->textedit.select_end) {
				int min = zt_min(item->textedit.select_beg, item->textedit.select_end);
				int max = zt_max(item->textedit.select_beg, item->textedit.select_end);

				char buffer[1024 * 4] = {0};
				zt_strCpy(buffer, zt_elementsOf(buffer), item->textedit.text_buffer + min, max - min);

				zt_clipboardSendPlainText(buffer);
			}
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

// ================================================================================================================================================================================================

ztInternal int _zt_guiTextEditGetCursorIndexAtPosition(ztGuiItem *item, ztVec2 pos)
{
	ZT_PROFILE_GUI("_zt_guiTextEditGetCursorIndexAtPosition");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID, item);

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTextEditBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiTextEditBestSize))
{
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeTextEdit(ztGuiItem *parent, const char *value, i32 flags, i32 buffer_size)
{
	ZT_PROFILE_GUI("zt_guiMakeTextEdit");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_TextEdit, ztGuiItemBehaviorFlags_ClipContents | ztGuiItemBehaviorFlags_WantsFocus | flags, buffer_size * 2);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	zt_guiItemSetSize(item, zt_vec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultW, item), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultH, item)));

	item->textedit.cursor_pos      = 0;
	item->textedit.cursor_xy[0]    = item->textedit.cursor_xy[1] = 0;
	item->textedit.cursor_vis      = false;
	item->textedit.text_buffer     = zt_stringMake(&item->gm->string_pool, buffer_size);
	item->textedit.text_buffer[0]  = 0;
	item->textedit.select_beg      = -1;
	item->textedit.select_end      = -1;
	item->textedit.dragging        = false;
	item->textedit.scroll_amt_horz = 0;
	item->textedit.scroll_amt_vert = 0;
	item->textedit.content_size[0] = 0;
	item->textedit.content_size[1] = 0;
	item->textedit.on_key          = ZT_FUNCTION_POINTER_TO_VAR_NULL;

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
		zt_stringOverwrite(&item->gm->string_pool, item->textedit.text_buffer, value);
		_zt_guiTextEditCacheText(item);
	}

	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTextEditCleanup);
	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTextEditUpdate);
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTextEditInputMouse);
	item->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTextEditInputKey);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTextEditRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTextEditBestSize);

	ztVec2 min_size;
	_zt_guiTextEditBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ================================================================================================================================================================================================

int zt_guiTextEditGetValue(ztGuiItem *text, char *buffer, int buffer_len)
{
	ZT_PROFILE_GUI("zt_guiTextEditGetValue");

	zt_assertReturnValOnFail(text->type == ztGuiItemType_TextEdit, -1);
	return zt_strCpy(buffer, buffer_len, text->textedit.text_buffer);
}

// ================================================================================================================================================================================================

void zt_guiTextEditSetValue(ztGuiItem *text, const char *value)
{
	ZT_PROFILE_GUI("zt_guiTextEditSetValue");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	zt_strCpy(text->textedit.text_buffer, zt_stringSize(text->textedit.text_buffer), value);

	text->textedit.cursor_pos = 0;
	text->textedit.select_beg = text->textedit.select_end = -1;
	text->textedit.text_pos[0] = 0;
	text->textedit.text_pos[1] = 0;
	_zt_guiTextEditRecalcCursor(text);
	_zt_guiTextEditAdjustViewForCursor(text);
	_zt_guiTextEditCacheText(text);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiTextEditGetSelection(ztGuiItem *text, int *sel_beg, int *sel_end)
{
	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);

	*sel_beg = text->textedit.select_beg;
	*sel_end = text->textedit.select_end;
}

// ================================================================================================================================================================================================

void zt_guiTextEditSelectAll(ztGuiItem *text)
{
	ZT_PROFILE_GUI("zt_guiTextEditSelectAll");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	zt_guiTextEditSetSelection(text, 0, zt_strLen(text->textedit.text_buffer));
}

// ================================================================================================================================================================================================

int zt_guiTextEditGetCursorPos(ztGuiItem *text)
{
	zt_assertReturnValOnFail(text->type == ztGuiItemType_TextEdit, -1);
	return text->textedit.cursor_pos;
}

// ================================================================================================================================================================================================

void zt_guiTextEditSetCursorPos(ztGuiItem *text, int cursor_pos)
{
	ZT_PROFILE_GUI("zt_guiTextEditSetCursorPos");

	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	text->textedit.cursor_pos = zt_clamp(cursor_pos, 0, zt_strLen(text->textedit.text_buffer));
	_zt_guiTextEditRecalcCursor(text);
	_zt_guiTextEditAdjustViewForCursor(text);
}

// ================================================================================================================================================================================================

void zt_guiTextEditSetCallback(ztGuiItem *text, ZT_FUNCTION_POINTER_VAR(on_key, zt_guiTextEditKey_Func), void *user_data)
{
	zt_assertReturnOnFail(text->type == ztGuiItemType_TextEdit);
	text->textedit.on_key = on_key;
	text->textedit.on_key_user_data = user_data;
}

// ================================================================================================================================================================================================

ztVec2 zt_guiTextEditGetCharacterPos(ztGuiItem *item, int ch, bool bottom_right)
{
	ZT_PROFILE_GUI("zt_guiTextEditGetCharacterPos");

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	ztVec2 chpos = ztVec2::zero;
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID, item);
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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ztGuiMenuMaxMenuItems	512

// ================================================================================================================================================================================================

ztInternal void _zt_guiMenuClose(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiMenuClose");

	if (zt_bitIsSet(item->behavior_flags, ztGuiMenuBehaviorFlags_FreeOnClose)) {
		zt_guiItemQueueFree(item);
	}
	else {
		zt_guiItemHide(item);
	}
	item->menu.selected = item->menu.highlighted = -1;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuBaseUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiMenuBaseUpdate))
{
	ZT_PROFILE_GUI("_zt_guiMenuBaseUpdate");

	if (item->type == ztGuiItemType_Menu) {
		if (item->gm->mouse_just_clicked && !item->menu.just_opened && item->gm->item_has_mouse != item && !zt_guiItemIsChildOf(item, item->gm->item_has_mouse)) {
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

		if (item->size.x < item->menu.full_size.x) {
			zt_guiScrollbarSetStepsAndPercent(item->menu.scrollbar_horz, .125f, .5f, 0);
			zt_guiItemShow(item->menu.scrollbar_horz);
			zt_guiItemSetPosition(item->menu.scrollbar_horz, ztAlign_Bottom, ztAnchor_Bottom);
			zt_guiItemSetSize(item->menu.scrollbar_horz, zt_vec2(item->size.x, -1));
		}
		else if (zt_bitIsSet(item->menu.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible))) {
			zt_guiItemHide(item->menu.scrollbar_horz);
		}

		if (item->size.y < item->menu.full_size.y) {
			zt_guiScrollbarSetStepsAndPercent(item->menu.scrollbar_vert, 1.f / item->menu.item_count, 4.f / item->menu.item_count, 0);
			zt_guiItemShow(item->menu.scrollbar_vert);
			zt_guiItemSetPosition(item->menu.scrollbar_vert, ztAlign_Right, ztAnchor_Right);
			zt_guiItemSetSize(item->menu.scrollbar_vert, zt_vec2(-1, item->size.y));
		}
		else if (zt_bitIsSet(item->menu.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible))) {
			zt_guiItemHide(item->menu.scrollbar_vert);
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

	item->menu.just_opened = zt_max(0, item->menu.just_opened - 1);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuBaseRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiMenuBaseRender))
{
	ZT_PROFILE_GUI("_zt_guiMenuBaseRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiMenuCleanup))
{
	ZT_PROFILE_GUI("_zt_guiMenuCleanup");

	zt_fiz(item->menu.item_count) {
		zt_stringFree(&item->gm->string_pool, item->menu.display[i]);

		if (item->menu.icons[i] != nullptr) {
			zt_freeArena(item->menu.icons[i], item->gm->arena);
		}

	}

	zt_freeArena(item->menu.display, item->gm->arena);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiMenuInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiMenuInputMouse");

	ztVec2 mpos = zt_guiItemPositionScreenToLocal(item, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));

	ztGuiTheme *theme = zt_guiItemGetTheme(item);
	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);

	ztVec2 pos = ztVec2::zero;
	pos.x -= (item->size.x - padding * 2.f) / 2.f;
	pos.y += (item->size.y - padding * 2.f) / 2.f;

	if (zt_bitIsSet(item->menu.scrollbar_vert->state_flags, zt_bit(ztGuiItemStates_Visible))) {
		if (input_mouse->wheel_delta < 0) {
			zt_guiScrollbarStepPos(item->menu.scrollbar_vert);
		}
		else if (input_mouse->wheel_delta > 0) {
			zt_guiScrollbarStepNeg(item->menu.scrollbar_vert);
		}
		pos.y += (item->menu.full_size.y - item->size.y) * zt_guiScrollbarGetValue(item->menu.scrollbar_vert);
	}
//	if (zt_bitIsSet(item->menu.scrollbar_horz->state_flags, zt_bit(ztGuiItemStates_Visible)) {
//		pos.x -= (item->menu.full_size.x - item->size.x) * zt_guiScrollbarGetValue(item->menu.scrollbar_horz);
//	}

	r32 icon = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item);
	zt_fiz(item->menu.item_count) {
		if (item->menu.icons[i] != nullptr) {
			icon = zt_max(icon, item->menu.icons[i]->half_size.y * 2.f);
		}
	}

	pos.y -= item->menu.label_offset;

	item->menu.selected = item->menu.highlighted = -1;

	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_MenuFontID, item);
	zt_fiz(item->menu.item_count) {
		ztVec2 ext = zt_fontGetExtents(font, item->menu.display[i]);

		if (icon > ext.y) ext.y = icon;
		if (item->menu.ids[i] == ztInvalidID && zt_strStartsWith(item->menu.display[i], "__")) {
			ext.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSeparatorHeight, item);
		}

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
			ztVec2 ppos = item->type == ztGuiItemType_Menu ? zt_vec2(item->size.x / 2.f, pos.y) : zt_vec2(pos.x, item->size.y / -2.f);
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
			if (ZT_FUNCTION_POINTER_IS_VALID(item->menu.on_selected) && !need_open) {
				ZT_FUNCTION_POINTER_ACCESS(item->menu.on_selected, zt_guiMenuSelected_Func)(item, item->menu.ids[item->menu.selected], item->menu.user_datas[item->menu.selected]);
			}

			if (zt_bitIsSet(item->behavior_flags, ztGuiMenuBehaviorFlags_FreeOnClose)) {
				zt_guiItemQueueFree(item);
			}

			_zt_guiMenuCloseAll();
		}
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiMenuBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiMenuBestSize))
{
	ZT_PROFILE_GUI("_zt_guiMenuBestSize");

	zt_guiThemeSizeItem(theme, item);

	item->menu.full_size = item->size;
}

// ================================================================================================================================================================================================

ztInternal ztGuiItem *_zt_guiMakeMenuBase(ztGuiItem *parent, ztGuiItem *owner, bool bar, i32 behavior_flags)
{
	ZT_PROFILE_GUI("_zt_guiMakeMenuBase");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, bar ? ztGuiItemType_MenuBar : ztGuiItemType_Menu, behavior_flags | (bar ? 0 : ztGuiItemBehaviorFlags_ClipContents) /* <- this was commented out... why? */ | ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_BringToFront);
	zt_returnValOnNull(item, nullptr);

	if (!bar) {
		zt_guiItemHide(item);
	}

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->menu.owner = owner;
	item->menu.scrollbar_vert = zt_guiMakeScrollbar(item, ztGuiItemOrient_Vert);
	item->menu.scrollbar_horz = zt_guiMakeScrollbar(item, ztGuiItemOrient_Horz);

	zt_guiItemHide(item->menu.scrollbar_vert);
	zt_guiItemHide(item->menu.scrollbar_horz);

	int max_menu = ztGuiMenuMaxMenuItems; // fixme: if dynamically allocating, this should be dynamic as well and passed in as a parameter
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
	item->menu.just_opened = 0;
	item->menu.on_selected = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->menu.label_offset = 0;
	item->menu.owner = nullptr;

	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiMenuCleanup);
	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiMenuBaseUpdate);
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiMenuInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiMenuBaseRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiMenuBestSize);

	ztVec2 min_size;
	_zt_guiMenuBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeMenu(ztGuiItem *parent, i32 behavior_flags)
{
	ZT_PROFILE_GUI("zt_guiMakeMenu");

	return _zt_guiMakeMenuBase(nullptr, parent, false, behavior_flags);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeMenuBar(ztGuiItem *parent)
{
	ZT_PROFILE_GUI("zt_guiMakeMenuBar");

	return _zt_guiMakeMenuBase(parent, nullptr, true, 0);
}

// ================================================================================================================================================================================================

void zt_guiMenuAppend(ztGuiItem *menu, const char *label, i32 id, void *user_data, ztSprite *icon)
{
	ZT_PROFILE_GUI("zt_guiMenuAppend");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);

	zt_assert(menu->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = menu->menu.item_count++;
	menu->menu.display[idx] = zt_stringMakeFrom(&menu->gm->string_pool, label);
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

// ================================================================================================================================================================================================

void zt_guiMenuAppendSubmenu(ztGuiItem *menu, const char *label, ztGuiItem *submenu, ztSprite *icon)
{
	ZT_PROFILE_GUI("zt_guiMenuAppendSubmenu");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);
	zt_assertReturnOnFail(submenu->type == ztGuiItemType_Menu);
	zt_assertReturnOnFail(menu->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = menu->menu.item_count++;
	menu->menu.display[idx] = zt_stringMakeFrom(&menu->gm->string_pool, label);
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

// ================================================================================================================================================================================================

void zt_guiMenuAppendSeparator(ztGuiItem *menu)
{
	ZT_PROFILE_GUI("zt_guiMenuAppendSeparator");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu);

	zt_assert(menu->menu.item_count < ztGuiMenuMaxMenuItems);

	int idx = menu->menu.item_count++;
	menu->menu.display[idx] = zt_stringMakeFrom(&menu->gm->string_pool, "__________");
	menu->menu.ids[idx] = ztInvalidID;
	menu->menu.submenus[idx] = nullptr;
	menu->menu.user_datas[idx] = nullptr;
	menu->menu.icons[idx] = nullptr;

	_zt_guiMenuBestSize(menu, nullptr, nullptr, &menu->size, zt_guiItemGetTheme(menu), menu->functions.user_data);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiMenuPopupAtPosition(ztGuiItem *menu, const ztVec2& pos)
{
	ZT_PROFILE_GUI("zt_guiMenuPopupAtPosition");

	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu);

	//_zt_guiMenuClose(menu);

	menu->state_flags |= zt_bit(ztGuiItemStates_Visible);
	menu->menu.just_opened = menu->gm->in_update ? 1 : 2;

	ztVec2 position = pos;

	ztVec2 ext_min = zt_cameraOrthoGetMinExtent(menu->gm->gui_camera);
	ztVec2 ext_max = zt_cameraOrthoGetMaxExtent(menu->gm->gui_camera);

	if (position.x + menu->size.x > ext_max.x) {
		position.x -= (position.x + menu->size.x) - ext_max.x;
	}
	if (position.y - menu->size.y < ext_min.y) {
		position.y += ext_min.y - (position.y - menu->size.y);
	}


	position.x += menu->size.x / 2;
	position.y -= menu->size.y / 2;

	menu->pos = position;
	zt_guiItemBringToFront(menu);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiMenuSetCallback(ztGuiItem *menu, ZT_FUNCTION_POINTER_VAR(on_selected, zt_guiMenuSelected_Func))
{
	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);
	menu->menu.on_selected = on_selected;
}

// ================================================================================================================================================================================================

void zt_guiMenuClear(ztGuiItem *menu)
{
	zt_assertReturnOnFail(menu->type == ztGuiItemType_Menu || menu->type == ztGuiItemType_MenuBar);
	menu->menu.item_count = 0;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztTreeEntryFlags_Enum
{
	ztTreeEntryFlags_NeedsSized = (1<<0),
};

// ================================================================================================================================================================================================

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

		// ================================================================================================================================================================================================

		static void addToSize(ztGuiItem::ztTreeItem *tree_entry, ztGuiTheme *theme, ztVec2 *size, r32 indent_size, int *shown_items, r32 padding, r32 tree_indent)
		{
			ZT_PROFILE_GUI("_zt_guiTreeCalculateSize:addToSize");

			ztGuiItem *tree_item = tree_entry->item;

			if (tree_item->size.x + indent_size > size->x) {
				ztGuiItem *button = tree_entry->control_button;
				r32 icon_size = button->size.x;;
				size->x = tree_item->size.x + indent_size + icon_size + padding * 2;
			}

			size->y += tree_item->size.y;

			shown_items += 1;

			if (tree_entry->expanded) {
				ztGuiItem::ztTreeItem *child = tree_entry->first_child;
				while (child) {
					addToSize(child, theme, size, indent_size + tree_indent, shown_items, padding, tree_indent);
					child = child->next;
				}
			}
		}

		// ================================================================================================================================================================================================

		static void reposition(ztGuiItem::ztTreeItem *tree_entry, ztGuiTheme *theme, r32 x, r32* y, r32 w, r32 indent_size, r32 tree_indent)
		{
			ZT_PROFILE_GUI("_zt_guiTreeCalculateSize:resposition");

			ztGuiItem *tree_item = tree_entry->item;

			tree_item->state_flags |= zt_bit(ztGuiItemStates_Visible);

			if (zt_bitIsSet(tree_entry->flags, ztTreeEntryFlags_NeedsSized)) {
				tree_item->size.x = w - indent_size;
				zt_bitRemove(tree_entry->flags, ztTreeEntryFlags_NeedsSized);
			}

			tree_item->pos.x = x + indent_size + (tree_item->size.x / 2);

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
					reposition(child, theme, x, y, w, indent_size + tree_indent, tree_indent);
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
	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
	r32 tree_indent = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TreeIndent, item);
	child = item->tree.root_item->first_child;
	while (child) {
		local::addToSize(child, theme, &size, 0, &shown_items, padding, tree_indent);
		child = child->next;
	}

	size.y += padding * 2;

	r32 x = (padding * 2) + size.x / -2;
	r32 y = size.y / 2;
	child = item->tree.root_item->first_child;
	while (child) {
		local::reposition(child, theme, x, &y, size.x, tree_indent, tree_indent);
		child = child->next;
	}

	content->size = size;
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiTreeRecalc(ztGuiItem *tree)
{
	ZT_PROFILE_GUI("_zt_guiTreeRecalc");

	_zt_guiTreeCalculateSize(tree);

	ztGuiItem *container = tree->tree.container;
	container->size = tree->size;

	zt_bitRemove(tree->state_flags, zt_bit(ztGuiItemStates_Dirty));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiTreeUpdate))
{
	ZT_PROFILE_GUI("_zt_guiTreeUpdate");

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty)) || zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Resized))) {
		_zt_guiTreeRecalc(item);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiTreeRender))
{
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiTreeCleanup))
{
	ZT_PROFILE_GUI("_zt_guiTreeCleanup");

	zt_freeArena(item->tree.arena, item->gm->arena);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

		ztVec2 size = zt_vec2(item->size.x, 0);
		ztGuiItem::ztTreeItem *intersecting = _zt_guiTreeMouseIntersecting(item->tree.root_item, mpos, pos, size);
		if (intersecting) {
			if (item->tree.active_item != intersecting) {
				item->tree.active_item = intersecting;
				if (ZT_FUNCTION_POINTER_IS_VALID(item->tree.on_item_sel)) {
					ZT_FUNCTION_POINTER_ACCESS(item->tree.on_item_sel, zt_guiTreeItemSelected_Func)(item, intersecting->node_id, item->tree.on_item_sel_user_data);
				}
			}
		}
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiTreeBestSize))
{
}
// ================================================================================================================================================================================================

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
	item->tree.on_item_sel = ZT_FUNCTION_POINTER_TO_VAR_NULL;

	item->tree.root_item = zt_mallocStructArena(ztGuiItem::ztTreeItem, item->tree.arena);
	zt_memSet(item->tree.root_item, zt_sizeof(ztGuiItem::ztTreeItem), 0);
	item->tree.root_item->expanded = true;
	item->tree.root_item->node_id = ++item->tree.last_id;
	item->tree.root_item->item = nullptr;
	item->tree.root_item->control_button = nullptr;

	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTreeCleanup);
	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTreeUpdate);
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTreeInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTreeRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTreeBestSize);

	ztVec2 min_size;
	_zt_guiTreeBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ================================================================================================================================================================================================

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItem *tree, const char *item_label, void *user_data, ztGuiTreeNodeID parent_id, i32 flags)
{
	ZT_PROFILE_GUI("zt_guiTreeAppend");

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);

	ztGuiItem *item = zt_guiMakeStaticText(tree->tree.content, item_label);
	return zt_guiTreeAppend(tree, item, user_data, parent_id, flags);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiTreeOnToggle, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiTreeOnToggle))
{
	ZT_PROFILE_GUI("_zt_guiTreeOnToggle");

	ztGuiItem *tree = (ztGuiItem*)user_data;
	_zt_guiTreeToggleItem(tree, tree->tree.root_item, button);
}

// ================================================================================================================================================================================================

ztGuiTreeNodeID zt_guiTreeAppend(ztGuiItem *tree, ztGuiItem *item, void *user_data, ztGuiTreeNodeID parent_id, i32 flags)
{
	ZT_PROFILE_GUI("zt_guiTreeAppend");

	struct local
	{
		// ================================================================================================================================================================================================

		static ztGuiItem::ztTreeItem *appendItem(ztGuiItem *tree, ztGuiItem::ztTreeItem *root, ztGuiTreeNodeID parent_node, i32 flags)
		{
			if (parent_node != ztInvalidID && parent_node != root->node_id) {
				ztGuiItem::ztTreeItem *node = root->first_child;
				while (node) {
					auto *tree_item = appendItem(tree, node, parent_node, flags);
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
			tree_item->flags = zt_bitIsSet(flags, ztGuiTreeItemFlags_StretchToMax) ? ztTreeEntryFlags_NeedsSized : 0;
			
			tree_item->control_button = zt_guiMakeButton(tree->tree.content, nullptr, zt_guiThemeGetIValue(zt_guiItemGetTheme(tree), ztGuiThemeValue_i32_TreeCollapseButtonBehaviorFlags, tree));
	
			ztGuiTheme *theme = zt_guiItemGetTheme(tree);
			zt_guiThemeUpdateSubitem(theme, tree, tree_item->control_button);
			zt_guiButtonSetCallback(tree_item->control_button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiTreeOnToggle), tree);

			zt_singleLinkAddToEnd(root->first_child, tree_item);

			return tree_item;
		}
	};

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);

	zt_guiItemReparent(item, tree->tree.content);

	ztGuiItem::ztTreeItem *tree_item = local::appendItem(tree, tree->tree.root_item, parent_id, flags);
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

// ================================================================================================================================================================================================

ztGuiTreeNodeID zt_guiTreeGetSelected(ztGuiItem *tree)
{
	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);
	return tree->tree.active_item ? tree->tree.active_item->node_id : ztInvalidID;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztGuiTreeNodeID zt_guiTreeGetRoot(ztGuiItem *tree)
{
	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, ztInvalidID);
	return 0;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiTreeGetNodeItem(ztGuiItem *tree, ztGuiTreeNodeID node)
{
	ZT_PROFILE_GUI("zt_guiTreeGetNodeItem");

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, nullptr);

	ztGuiItem::ztTreeItem *tree_item = _zt_guiTreeFindNode(tree, tree->tree.root_item, node);
	return tree_item ? tree_item->item : nullptr;
}

// ================================================================================================================================================================================================

void *zt_guiTreeGetNodeUserData(ztGuiItem *tree, ztGuiTreeNodeID node)
{
	ZT_PROFILE_GUI("zt_guiTreeGetNodeUserData");

	zt_assertReturnValOnFail(tree->type == ztGuiItemType_Tree, nullptr);

	ztGuiItem::ztTreeItem *tree_item = _zt_guiTreeFindNode(tree, tree->tree.root_item, node);
	return tree_item ? tree_item->user_data : nullptr;
}

// ================================================================================================================================================================================================

void zt_guiTreeSetCallback(ztGuiItem *tree, ZT_FUNCTION_POINTER_VAR(on_item_sel, zt_guiTreeItemSelected_Func), void *user_data)
{
	zt_assertReturnOnFail(tree->type == ztGuiItemType_Tree);

	tree->tree.on_item_sel           = on_item_sel;
	tree->tree.on_item_sel_user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiTreeCollapseNode(ztGuiItem *tree, ztGuiTreeNodeID node_id)
{
	ZT_PROFILE_GUI("zt_guiTreeCollapseNode");
	zt_returnOnNull(tree);

	ztGuiItem::ztTreeItem *node = _zt_guiTreeFindNode(tree, tree->tree.root_item, node_id);
	if (node && node->expanded) {
		node->expanded = false;
		tree->state_flags |= zt_bit(ztGuiItemStates_Dirty);

		ztGuiTheme *theme = zt_guiItemGetTheme(node->control_button);
		zt_guiThemeUpdateSubitem(theme, tree, node->control_button, (void*)&node->expanded);
		_zt_guiTreeRecalc(tree);
	}
}

// ================================================================================================================================================================================================

void zt_guiTreeExpandNode(ztGuiItem *tree, ztGuiTreeNodeID node_id)
{
	ZT_PROFILE_GUI("zt_guiTreeExpandNode");

	zt_returnOnNull(tree);

	ztGuiItem::ztTreeItem *node = _zt_guiTreeFindNode(tree, tree->tree.root_item, node_id);
	if (node && !node->expanded) {
		node->expanded = true;
		tree->state_flags |= zt_bit(ztGuiItemStates_Dirty);

		ztGuiTheme *theme = zt_guiItemGetTheme(node->control_button);
		zt_guiThemeUpdateSubitem(theme, tree, node->control_button, (void*)&node->expanded);
		_zt_guiTreeRecalc(tree);
	}
}

// ================================================================================================================================================================================================

void zt_guiTreeClear(ztGuiItem *tree)
{
	ZT_PROFILE_GUI("zt_guiTreeClear");

	zt_assertReturnOnFail(tree->type == ztGuiItemType_Tree);

	struct local
	{
		static void clear(ztMemoryArena *arena, ztGuiItem::ztTreeItem *tree_item)
		{
			if (tree_item->control_button != nullptr) {
				zt_guiItemQueueFree(tree_item->control_button);
				tree_item->control_button = nullptr;
			}
			if (tree_item->item != nullptr) {
				zt_guiItemQueueFree(tree_item->item);
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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiComboBoxRender))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiComboBoxCleanup))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxCleanup");

	if (item->combobox.popup != nullptr) {
		zt_guiItemQueueFree(item->combobox.popup);
	}

	zt_fiz(item->combobox.contents_size) {
		zt_stringFree(&item->gm->string_pool, item->combobox.contents[i]);
	}
	zt_freeArena(item->combobox.contents, item->gm->arena);
	zt_freeArena(item->combobox.contents_user_data, item->gm->arena);
	item->combobox.contents_size = item->combobox.contents_count = -1;
}

// ================================================================================================================================================================================================

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
				//zt_guiItemAutoSize(item->combobox.popup);

				menu->size.x = item->size.x;
				zt_guiMenuPopupAtItem(item->combobox.popup, item, ztAlign_Left | ztAlign_Bottom);
			}
		}
		else zt_bitRemove(item->state_flags, zt_bit(ztGuiComboBoxInternalStates_IgnorePopup));
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxInputKey, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiComboBoxInputKey))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxInputKey");

	if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
		if (item->combobox.selected > 0) {
			item->combobox.selected -= 1;
			if (ZT_FUNCTION_POINTER_IS_VALID(item->combobox.on_selected)) {
				ZT_FUNCTION_POINTER_ACCESS(item->combobox.on_selected, zt_guiComboBoxItemSelected_Func)(item, item->combobox.selected, item->combobox.on_selected_user_data);
			}
		}
	}
	if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
		if (item->combobox.selected < item->combobox.contents_count - 1) {
			item->combobox.selected += 1;
			if (ZT_FUNCTION_POINTER_IS_VALID(item->combobox.on_selected)) {
				ZT_FUNCTION_POINTER_ACCESS(item->combobox.on_selected, zt_guiComboBoxItemSelected_Func)(item, item->combobox.selected, item->combobox.on_selected_user_data);
			}
		}
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiComboBoxBestSize))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeComboBox(ztGuiItem *parent, i32 max_items)
{
	ZT_PROFILE_GUI("zt_guiMakeComboBox");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_ComboBox, ztGuiItemBehaviorFlags_WantsFocus);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->combobox.popup = nullptr;
	item->combobox.contents = zt_mallocStructArrayArena(ztString, max_items, item->gm->arena);
	item->combobox.contents_user_data = zt_mallocStructArrayArena(void*, max_items, item->gm->arena);
	item->combobox.contents_size = max_items;
	item->combobox.contents_count = 0;
	item->combobox.on_selected = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->combobox.on_selected_user_data = nullptr;

	zt_fiz(max_items) {
		item->combobox.contents[i] = zt_stringMake(&item->gm->string_pool, 128);
		item->combobox.contents[i][0] = 0;
		item->combobox.contents_user_data[i] = nullptr;
	}

	item->combobox.selected = 0;


	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxCleanup);
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxInputMouse);
	item->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxInputKey);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxBestSize);

	ztVec2 min_size;
	_zt_guiComboBoxBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiComboBoxMenuSelected, ztInternal ZT_FUNC_GUI_MENU_SELECTED(_zt_guiComboBoxMenuSelected))
{
	ZT_PROFILE_GUI("_zt_guiComboBoxMenuSelected");

	ztGuiItem *combo = (ztGuiItem*)user_data;
	combo->combobox.selected = menu_item;

	if (ZT_FUNCTION_POINTER_IS_VALID(combo->combobox.on_selected)) {
		ZT_FUNCTION_POINTER_ACCESS(combo->combobox.on_selected, zt_guiComboBoxItemSelected_Func)(combo, combo->combobox.selected, combo->combobox.on_selected_user_data);
	}
}

// ================================================================================================================================================================================================

void zt_guiComboBoxSetContents(ztGuiItem *combobox, const char **contents, int contents_count, int active)
{
	ZT_PROFILE_GUI("zt_guiComboBoxSetContents");

	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);

	if (combobox->combobox.popup != nullptr) {
		zt_guiItemQueueFree(combobox->combobox.popup);
	}
	combobox->combobox.popup = zt_guiMakeMenu(combobox);
	zt_guiMenuSetCallback(combobox->combobox.popup, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxMenuSelected));
	combobox->combobox.popup->menu.owner = combobox;
	zt_guiItemReparent(combobox->combobox.popup, combobox);

	combobox->combobox.contents_count = zt_min(contents_count, combobox->combobox.contents_size);
	zt_fiz(combobox->combobox.contents_count) {
		zt_stringOverwrite(&combobox->gm->string_pool, combobox->combobox.contents[i], contents[i]);

		zt_guiMenuAppend(combobox->combobox.popup, contents[i], i, combobox);
	}

	zt_guiItemAutoSize(combobox->combobox.popup);

	combobox->combobox.selected = zt_clamp(active, 0, combobox->combobox.contents_count - 1);
}

// ================================================================================================================================================================================================

void zt_guiComboBoxClear(ztGuiItem *combobox)
{
	ZT_PROFILE_GUI("zt_guiComboBoxClear");

	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	combobox->combobox.contents_count = 0;
	combobox->combobox.selected = -1;

	if (combobox->combobox.popup != nullptr) {
		zt_guiItemQueueFree(combobox->combobox.popup);
		combobox->combobox.popup = nullptr;
	}
}

// ================================================================================================================================================================================================

void zt_guiComboBoxAppend(ztGuiItem *combobox, const char *content, void *user_data)
{
	ZT_PROFILE_GUI("zt_guiComboBoxAppend");

	zt_guiComboBoxAppendWithIcon(combobox, content, nullptr, user_data);
}

// ================================================================================================================================================================================================

void zt_guiComboBoxAppendWithIcon(ztGuiItem *combobox, const char *content, ztSprite *sprite, void *user_data)
{
	ZT_PROFILE_GUI("zt_guiComboBoxAppendWithIcon");

	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	zt_assertReturnOnFail(combobox->combobox.contents_count < combobox->combobox.contents_size);

	if (combobox->combobox.contents_count == 0) {
		if (combobox->combobox.popup != nullptr) {
			zt_guiItemFree(combobox->combobox.popup);
		}
		combobox->combobox.popup = zt_guiMakeMenu(combobox);
		combobox->combobox.popup->menu.owner = combobox;
		zt_guiMenuSetCallback(combobox->combobox.popup, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiComboBoxMenuSelected));
		combobox->combobox.selected = 0;
	}

	int idx = combobox->combobox.contents_count;
	combobox->combobox.contents_count += 1;

	zt_stringOverwrite(&combobox->gm->string_pool, combobox->combobox.contents[idx], content);
	combobox->combobox.contents_user_data[idx] = user_data;
	zt_guiMenuAppend(combobox->combobox.popup, content, idx, combobox, sprite);
	zt_guiItemAutoSize(combobox->combobox.popup);

	_zt_guiComboBoxBestSize(combobox, nullptr, nullptr, &combobox->size, zt_guiItemGetTheme(combobox), nullptr);
}


// ================================================================================================================================================================================================

int zt_guiComboBoxGetSelected(ztGuiItem *combobox)
{
	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, -1);
	return combobox->combobox.selected;
}

// ================================================================================================================================================================================================

void zt_guiComboBoxSetSelected(ztGuiItem *combobox, int selected)
{
	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	combobox->combobox.selected = selected;
}

// ================================================================================================================================================================================================

int zt_guiComboBoxGetItemCount(ztGuiItem *combobox)
{
	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, 0);
	return combobox->combobox.contents_count;
}

// ================================================================================================================================================================================================

int zt_guiComboBoxGetItemText(ztGuiItem *combobox, int index, char* buffer, int buffer_len)
{
	ZT_PROFILE_GUI("zt_guiComboBoxGetItemText");

	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, 0);
	if (index >= 0 && index < combobox->combobox.contents_count) {
		return zt_strCpy(buffer, buffer_len, combobox->combobox.contents[index]);
	}
	return 0;
}

// ================================================================================================================================================================================================

void *zt_guiComboBoxGetItemUserData(ztGuiItem *combobox, int index)
{
	ZT_PROFILE_GUI("zt_guiComboBoxGetItemUserData");

	zt_assertReturnValOnFail(combobox->type == ztGuiItemType_ComboBox, nullptr);
	if (index >= 0 && index < combobox->combobox.contents_count) {
		return combobox->combobox.contents_user_data[index];
	}

	return nullptr;
}

// ================================================================================================================================================================================================

void zt_guiComboBoxSetCallback(ztGuiItem *combobox, ZT_FUNCTION_POINTER_VAR(on_item_sel, zt_guiComboBoxItemSelected_Func), void *user_data)
{
	zt_assertReturnOnFail(combobox->type == ztGuiItemType_ComboBox);
	combobox->combobox.on_selected = on_item_sel;
	combobox->combobox.on_selected_user_data = user_data;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal void _zt_guiCycleBoxChanged(ztGuiItem *cyclebox)
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxChanged");

	if (zt_bitIsSet(cyclebox->behavior_flags, ztGuiCycleBoxBehaviorFlags_HideInvalidButton)) {
		if (cyclebox->cyclebox.selected == 0 && zt_guiItemIsVisible(cyclebox->cyclebox.buttons[0])) {
			zt_guiItemHide(cyclebox->cyclebox.buttons[0]);
		}
		else if(!zt_guiItemIsVisible(cyclebox->cyclebox.buttons[0])) {
			zt_guiItemShow(cyclebox->cyclebox.buttons[0]);
		}

		if (cyclebox->cyclebox.selected >= cyclebox->cyclebox.contents_count - 1 && zt_guiItemIsVisible(cyclebox->cyclebox.buttons[1])) {
			zt_guiItemHide(cyclebox->cyclebox.buttons[1]);
		}
		else if(!zt_guiItemIsVisible(cyclebox->cyclebox.buttons[1])) {
			zt_guiItemShow(cyclebox->cyclebox.buttons[1]);
		}
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiCycleBoxCycleLeft(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxCycleLeft");

	bool changed = false;

	if (item->cyclebox.selected > 0) {
		item->cyclebox.selected -= 1;
		changed = true;
	}
	else if (zt_bitIsSet(item->behavior_flags, ztGuiCycleBoxBehaviorFlags_Infinite)) {
		item->cyclebox.selected = item->cyclebox.contents_count - 1;
		changed = true;
	}

	if (changed) {
		if (ZT_FUNCTION_POINTER_IS_VALID(item->cyclebox.on_changed)) {
			ZT_FUNCTION_POINTER_ACCESS(item->cyclebox.on_changed, zt_guiCycleBoxValueChanged_Func)(item, item->cyclebox.selected, item->cyclebox.on_changed_user_data);
		}
		if (item->cyclebox.live_value) {
			*item->cyclebox.live_value = item->cyclebox.selected;
		}
		_zt_guiCycleBoxChanged(item);
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiCycleBoxCycleRight(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxCycleRight");

	bool changed = false;

	if (item->cyclebox.selected < item->cyclebox.contents_count - 1) {
		item->cyclebox.selected += 1;
		changed = true;
	}
	else if (zt_bitIsSet(item->behavior_flags, ztGuiCycleBoxBehaviorFlags_Infinite)) {
		item->cyclebox.selected = 0;
		changed = true;
	}

	if (changed) {
		if (ZT_FUNCTION_POINTER_IS_VALID(item->cyclebox.on_changed)) {
			ZT_FUNCTION_POINTER_ACCESS(item->cyclebox.on_changed, zt_guiCycleBoxValueChanged_Func)(item, item->cyclebox.selected, item->cyclebox.on_changed_user_data);
		}
		if (item->cyclebox.live_value) {
			*item->cyclebox.live_value = item->cyclebox.selected;
		}
		_zt_guiCycleBoxChanged(item);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCycleBoxRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiCycleBoxRender))
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCycleBoxCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiCycleBoxCleanup))
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxCleanup");

	zt_fiz(item->cyclebox.contents_size) {
		zt_stringFree(&item->gm->string_pool, item->cyclebox.contents[i]);
	}
	zt_freeArena(item->cyclebox.contents, item->gm->arena);
	zt_freeArena(item->cyclebox.contents_user_data, item->gm->arena);
	item->cyclebox.contents_size = item->cyclebox.contents_count = -1;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCycleBoxInputKey, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiCycleBoxInputKey))
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxInputKey");

	if (input_keys[ztInputKeys_Left].justPressedOrRepeated()) {
		_zt_guiCycleBoxCycleLeft(item);
	}
	if (input_keys[ztInputKeys_Right].justPressedOrRepeated()) {
		_zt_guiCycleBoxCycleRight(item);
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCycleBoxBestSize, static ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiCycleBoxBestSize))
{
	ZT_PROFILE_GUI("_zt_guiCycleBoxBestSize");

	zt_guiThemeSizeItem(theme, item);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCycleBoxButtonLeft, static ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiCycleBoxButtonLeft))
{
	ztGuiItem *item = (ztGuiItem*)user_data;
	_zt_guiCycleBoxCycleLeft(item);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiCycleBoxButtonRight, static ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiCycleBoxButtonRight))
{
	ztGuiItem *item = (ztGuiItem*)user_data;
	_zt_guiCycleBoxCycleRight(item);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeCycleBox(ztGuiItem *parent, i32 max_items, i32 behavior_flags, int *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeCycleBox");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_CycleBox, ztGuiItemBehaviorFlags_WantsFocus|behavior_flags);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->cyclebox.live_value            = live_value;
	item->cyclebox.contents              = zt_mallocStructArrayArena(ztString, max_items, item->gm->arena);
	item->cyclebox.contents_user_data    = zt_mallocStructArrayArena(void*, max_items, item->gm->arena);
	item->cyclebox.contents_size         = max_items;
	item->cyclebox.contents_count        = 0;
	item->cyclebox.on_changed            = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->cyclebox.on_changed_user_data  = nullptr;

	zt_fiz(max_items) {
		item->cyclebox.contents[i]           = zt_stringMake(&item->gm->string_pool, 128);
		item->cyclebox.contents[i][0]        = 0;
		item->cyclebox.contents_user_data[i] = nullptr;
	}

	ztGuiItem *button_left = zt_guiMakeButton(item, nullptr, 0);
	zt_guiButtonSetCallback(button_left, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCycleBoxButtonLeft), item);
	zt_guiThemeUpdateSubitem(theme, item, button_left, (void*)ztDirection_Left);

	ztGuiItem *button_right = zt_guiMakeButton(item, nullptr, 0);
	zt_guiButtonSetCallback(button_right, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCycleBoxButtonRight), item);
	zt_guiThemeUpdateSubitem(theme, item, button_right, (void*)ztDirection_Right);

	item->cyclebox.selected = live_value ? *live_value : 0;

	item->cyclebox.buttons[0] = button_left;
	item->cyclebox.buttons[1] = button_right;

	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCycleBoxCleanup);
	item->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCycleBoxInputKey);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCycleBoxRender);
	item->functions.best_size   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiCycleBoxBestSize);

	ztVec2 min_size;
	_zt_guiCycleBoxBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	_zt_guiCycleBoxChanged(item);

	return item;
}

// ================================================================================================================================================================================================

void zt_guiCycleBoxSetContents(ztGuiItem *cyclebox, const char **contents, int contents_count, int active)
{
	ZT_PROFILE_GUI("zt_guiCycleBoxSetContents");

	zt_assertReturnOnFail(cyclebox->type == ztGuiItemType_CycleBox);

	cyclebox->cyclebox.contents_count = zt_min(contents_count, cyclebox->cyclebox.contents_size);
	zt_fiz(cyclebox->cyclebox.contents_count) {
		zt_stringOverwrite(&cyclebox->gm->string_pool, cyclebox->cyclebox.contents[i], contents[i]);
	}

	cyclebox->cyclebox.selected = zt_clamp(active, 0, cyclebox->cyclebox.contents_count - 1);

	_zt_guiCycleBoxChanged(cyclebox);
}

// ================================================================================================================================================================================================

void zt_guiCycleBoxClear(ztGuiItem *cyclebox)
{
	ZT_PROFILE_GUI("zt_guiCycleBoxClear");

	zt_assertReturnOnFail(cyclebox->type == ztGuiItemType_CycleBox);
	cyclebox->cyclebox.contents_count = 0;
	cyclebox->cyclebox.selected = -1;
	_zt_guiCycleBoxChanged(cyclebox);
}

// ================================================================================================================================================================================================

void zt_guiCycleBoxAppend(ztGuiItem *cyclebox, const char *content, void *user_data)
{
	ZT_PROFILE_GUI("zt_guiCycleBoxAppend");

	zt_assertReturnOnFail(cyclebox->type == ztGuiItemType_CycleBox);
	zt_assertReturnOnFail(cyclebox->cyclebox.contents_count < cyclebox->cyclebox.contents_size);

	if (cyclebox->cyclebox.contents_count == 0) {
		cyclebox->cyclebox.selected = 0;
	}

	int idx = cyclebox->cyclebox.contents_count;
	cyclebox->cyclebox.contents_count += 1;

	zt_stringOverwrite(&cyclebox->gm->string_pool, cyclebox->cyclebox.contents[idx], content);
	cyclebox->cyclebox.contents_user_data[idx] = user_data;

	_zt_guiCycleBoxChanged(cyclebox);
}

// ================================================================================================================================================================================================

int zt_guiCycleBoxGetSelected(ztGuiItem *cyclebox)
{
	zt_assertReturnValOnFail(cyclebox->type == ztGuiItemType_CycleBox, -1);
	return cyclebox->cyclebox.selected;
}

// ================================================================================================================================================================================================

void zt_guiCycleBoxSetSelected(ztGuiItem *cyclebox, int selected)
{
	zt_assertReturnOnFail(cyclebox->type == ztGuiItemType_CycleBox);
	cyclebox->cyclebox.selected = selected;

	if (cyclebox->cyclebox.live_value) {
		*cyclebox->cyclebox.live_value = selected;
	}
	_zt_guiCycleBoxChanged(cyclebox);
}

// ================================================================================================================================================================================================

int zt_guiCycleBoxGetItemCount(ztGuiItem *cyclebox)
{
	zt_assertReturnValOnFail(cyclebox->type == ztGuiItemType_CycleBox, 0);
	return cyclebox->cyclebox.contents_count;
}

// ================================================================================================================================================================================================

int zt_guiCycleBoxGetItemText(ztGuiItem *cyclebox, int index, char* buffer, int buffer_len)
{
	ZT_PROFILE_GUI("zt_guiCycleBoxGetItemText");

	zt_assertReturnValOnFail(cyclebox->type == ztGuiItemType_CycleBox, 0);
	if (index >= 0 && index < cyclebox->cyclebox.contents_count) {
		return zt_strCpy(buffer, buffer_len, cyclebox->cyclebox.contents[index]);
	}
	return 0;
}

// ================================================================================================================================================================================================

void *zt_guiCycleBoxGetItemUserData(ztGuiItem *cyclebox, int index)
{
	ZT_PROFILE_GUI("zt_guiCycleBoxGetItemUserData");

	zt_assertReturnValOnFail(cyclebox->type == ztGuiItemType_CycleBox, nullptr);
	if (index >= 0 && index < cyclebox->cyclebox.contents_count) {
		return cyclebox->cyclebox.contents_user_data[index];
	}

	return nullptr;
}

// ================================================================================================================================================================================================

void zt_guiCycleBoxSetCallback(ztGuiItem *cyclebox, ZT_FUNCTION_POINTER_VAR(on_item_change, zt_guiCycleBoxValueChanged_Func), void *user_data)
{
	zt_assertReturnOnFail(cyclebox->type == ztGuiItemType_CycleBox);
	cyclebox->cyclebox.on_changed = on_item_change;
	cyclebox->cyclebox.on_changed_user_data = user_data;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpriteDisplayRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiSpriteDisplayRender))
{
	ZT_PROFILE_GUI("_zt_guiSpriteDisplayRender");
	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpriteDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiSpriteDisplayCleanup))
{
	ZT_PROFILE_GUI("_zt_guiSpriteDisplayCleanup");

	if (item->sprite_display.sprite != nullptr) {
		zt_freeArena(item->sprite_display.sprite, item->gm->arena);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpriteDisplayBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiSpriteDisplayBestSize))
{
	ZT_PROFILE_GUI("_zt_guiSpriteDisplayBestSize");

	if (item->sprite_display.sprite) {
		*size = zt_guiThemeSpriteGetSize(item->sprite_display.sprite) * zt_vec2(item->sprite_display.scale[0], item->sprite_display.scale[1]);
	}
	else if (item->sprite_display.sprite_anim_controller) {
		ztSprite *sprite = zt_spriteAnimControllerActiveSprite(item->sprite_display.sprite_anim_controller);;
		if (sprite != nullptr) {
			*size = sprite->half_size * 2;
		}
	}
}

// ================================================================================================================================================================================================

ztInternal ztGuiItem *_zt_guiMakeSpriteDisplay(ztGuiItem *parent, ztGuiThemeSprite *sprite, ztSpriteAnimController *anim_controller, const ztVec2& scale, const ztVec4& bgcolor)
{
	ZT_PROFILE_GUI("zt_guiMakeSpriteDisplay");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_SpriteDisplay, ztGuiItemBehaviorFlags_WantsFocus);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	if (anim_controller) {
		item->sprite_display.sprite_anim_controller = anim_controller;
		item->sprite_display.sprite = nullptr;
	}
	else {
		item->sprite_display.sprite = zt_mallocStructArena(ztGuiThemeSprite, item->gm->arena);
		if (sprite) {
			*item->sprite_display.sprite = *sprite;
		}
		else {
			item->sprite_display.sprite->type = ztGuiThemeSpriteType_Invalid;
		}
		item->sprite_display.sprite_anim_controller = nullptr;
	}

	item->sprite_display.scale[0] = scale.x;
	item->sprite_display.scale[1] = scale.y;
	zt_fize(item->sprite_display.bgcolor) {
		item->sprite_display.bgcolor[i] = bgcolor.values[i];
	}

	item->functions.render    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSpriteDisplayRender);
	item->functions.cleanup   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSpriteDisplayCleanup);
	item->functions.best_size = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSpriteDisplayBestSize);

	ztVec2 min_size;
	_zt_guiSpriteDisplayBestSize(item, &min_size, nullptr, &item->size, theme, nullptr);

	return item;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeSpriteDisplay(ztGuiItem *parent, ztGuiThemeSprite *sprite, const ztVec2& scale, const ztVec4& bgcolor)
{
	return _zt_guiMakeSpriteDisplay(parent, sprite, nullptr, scale, bgcolor);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeSpriteDisplay(ztGuiItem *parent, ztSpriteAnimController *anim_controller, const ztVec2& scale, const ztVec4& bgcolor)
{
	return _zt_guiMakeSpriteDisplay(parent, nullptr, anim_controller, scale, bgcolor);
}

// ================================================================================================================================================================================================

void zt_guiSpriteDisplaySetSprite(ztGuiItem *item, ztGuiThemeSprite *sprite, const ztVec2& scale, const ztVec4& bgcolor)
{
	zt_assertReturnOnFail(item->type == ztGuiItemType_SpriteDisplay);
	*item->sprite_display.sprite = *sprite;
	item->sprite_display.scale[0] = scale.x;
	item->sprite_display.scale[1] = scale.y;
	zt_fize(item->sprite_display.bgcolor) {
		item->sprite_display.bgcolor[i] = bgcolor.values[i];
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpinnerUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiSpinnerUpdate))
{
	ZT_PROFILE_GUI("_zt_guiSpinnerUpdate");

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpinnerRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiSpinnerRender))
{
	ZT_PROFILE_GUI("_zt_guiSpinnerRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSpinnerInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiSpinnerInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiSpinnerInputMouse");

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

			if (ZT_FUNCTION_POINTER_IS_VALID(item->spinner.on_value_changed)) {
				ZT_FUNCTION_POINTER_ACCESS(item->spinner.on_value_changed, zt_guiSpinnerValueChanged_Func)(item, dir, item->spinner.on_value_changed_user_data);
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

// ================================================================================================================================================================================================

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
	item->spinner.on_value_changed = ZT_FUNCTION_POINTER_TO_VAR_NULL;

	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSpinnerUpdate);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSpinnerRender);
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSpinnerInputMouse);

	zt_guiThemeSizeItem(theme, item);

	return item;
}

// ================================================================================================================================================================================================

int zt_guiSpinnerGetValue(ztGuiItem *spinner)
{
	zt_assertReturnValOnFail(spinner->type == ztGuiItemType_Spinner, 0);
	return spinner->spinner.value;
}

// ================================================================================================================================================================================================

void zt_guiSpinnerSetCallback(ztGuiItem *spinner, ZT_FUNCTION_POINTER_VAR(on_value_changed, zt_guiSpinnerValueChanged_Func), void *user_data)
{
	zt_assertReturnOnFail(spinner->type == ztGuiItemType_Spinner);
	spinner->spinner.on_value_changed = on_value_changed;
	spinner->spinner.on_value_changed_user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiSpinnerTickUp(ztGuiItem *spinner)
{
	ZT_PROFILE_GUI("zt_guiSpinnerTickUp");

	zt_assertReturnOnFail(spinner->type == ztGuiItemType_Spinner);

	spinner->spinner.value = 1;
	spinner->spinner.time = 0;
	spinner->spinner.last_dir = 1;

	if (ZT_FUNCTION_POINTER_IS_VALID(spinner->spinner.on_value_changed)) {
		ZT_FUNCTION_POINTER_ACCESS(spinner->spinner.on_value_changed, zt_guiSpinnerValueChanged_Func)(spinner, spinner->spinner.last_dir, spinner->spinner.on_value_changed_user_data);
	}

	if (spinner->spinner.live_value) {
		*spinner->spinner.live_value = spinner->spinner.value;
	}
}

// ================================================================================================================================================================================================

void zt_guiSpinnerTickDown(ztGuiItem *spinner)
{
	ZT_PROFILE_GUI("zt_guiSpinnerTickDown");

	zt_assertReturnOnFail(spinner->type == ztGuiItemType_Spinner);

	spinner->spinner.value = -1;
	spinner->spinner.time = 0;
	spinner->spinner.last_dir = 1;

	if (ZT_FUNCTION_POINTER_IS_VALID(spinner->spinner.on_value_changed)) {
		ZT_FUNCTION_POINTER_ACCESS(spinner->spinner.on_value_changed, zt_guiSpinnerValueChanged_Func)(spinner, spinner->spinner.last_dir, spinner->spinner.on_value_changed_user_data);
	}

	if (spinner->spinner.live_value) {
		*spinner->spinner.live_value = spinner->spinner.value;
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztGuiListBoxInternalBehaviorFlags_Enum
{
	ztGuiListBoxInternalBehaviorFlags_ControlPressed = (1 << (ztGuiListBoxBehaviorFlags_MaxBit + 1)),
	ztGuiListBoxInternalBehaviorFlags_ShiftPressed   = (1 << (ztGuiListBoxBehaviorFlags_MaxBit + 2)),
	ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted  = (1 << (ztGuiListBoxBehaviorFlags_MaxBit + 3)),
};

zt_staticAssert(ztGuiListBoxBehaviorFlags_MaxBit <= 29);

#define ztGuiListBoxHorzFitWidth	(16.f / zt_pixelsPerUnit())

// ================================================================================================================================================================================================

ztInternal void _zt_guiListBoxGetFitCount(ztGuiItem *listbox, int *fit_h, int *fit_w, int *steps_w)
{
	ZT_PROFILE_GUI("_zt_guiListBoxGetFitCount");

	int shown_item_count = 0;
	zt_fiz(listbox->listbox.item_count) {
		if(!listbox->listbox.hidden[i]) {
			shown_item_count += 1;
		}
	}

	r32 header_height = listbox->listbox.header ? listbox->listbox.header->size.y : 0;

	r32 average_height = listbox->listbox.total_height / shown_item_count;
	int items_fit_count_h = zt_convertToi32Ceil((listbox->listbox.container->size.y - header_height) / average_height);
	r32 average_width = ztGuiListBoxHorzFitWidth;
	int steps_count_w = zt_convertToi32Ceil(listbox->listbox.total_width / average_width);
	int steps_fit_count_w = zt_convertToi32Floor(listbox->listbox.container->size.x / average_width);

	*fit_h = items_fit_count_h;
	*fit_w = steps_fit_count_w;
	*steps_w = steps_count_w;
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiListBoxAdjustItemsPositions(ztGuiItem *listbox)
{
	ZT_PROFILE_GUI("_zt_guiListBoxAdjustItemsPositions");

	r32 pct_vert = zt_guiScrollbarGetValue(listbox->listbox.scrollbar_vert);
	r32 pct_horz = zt_guiScrollbarGetValue(listbox->listbox.scrollbar_horz);

	int shown_item_count = 0;
	zt_fiz(listbox->listbox.item_count) {
		if(!listbox->listbox.hidden[i]) {
			shown_item_count += 1;
		}
	}

	r32 average_height = listbox->listbox.total_height / shown_item_count;
	int items_fit_count_h = zt_convertToi32Floor(listbox->listbox.container->size.y / average_height);

	int start_idx = zt_max(zt_convertToi32Floor((shown_item_count - items_fit_count_h) *  pct_vert), 0);

	r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(listbox), ztGuiThemeValue_r32_Padding, listbox);

	r32 height = listbox->listbox.container->size.y - (listbox->listbox.header ? listbox->listbox.header->size.y : 0);
	r32 start_y = (listbox->listbox.container->size.y / 2.f) - padding;
	r32 start_x = (listbox->listbox.container->size.x / -2.f) - (pct_horz * (listbox->listbox.total_width - listbox->listbox.container->size.x)) + padding;

	r32 header_height = listbox->listbox.header ? listbox->listbox.header->size.y : 0;
	start_y -= header_height;

	zt_fiz(start_idx) {
		zt_guiItemHide(listbox->listbox.items[i]);

		if (listbox->listbox.hidden[i]) {
			start_idx = zt_min(start_idx + 1, listbox->listbox.item_count - 1);
		}
	}

	int last_shown_idx = -1;
	int first_shown_idx = -1;
	for (int i = start_idx; i < listbox->listbox.item_count; ++i) {
		if (height <= 0 || listbox->listbox.hidden[i]) {
			zt_guiItemHide(listbox->listbox.items[i]);
		}
		else {
			zt_guiItemShow(listbox->listbox.items[i], !listbox->listbox.hidden[i]);
			listbox->listbox.items[i]->pos.x = start_x + listbox->listbox.items[i]->size.x / 2.f;
			listbox->listbox.items[i]->pos.y = start_y - listbox->listbox.items[i]->size.y / 2.f;

			//listbox->clip_area = ztVec4::zero;

			height -= listbox->listbox.items[i]->size.y;
			start_y -= listbox->listbox.items[i]->size.y;

			last_shown_idx = i;

			if (first_shown_idx == -1) {
				first_shown_idx = i;
			}
		}
	}

	if (listbox->listbox.header) {
		listbox->listbox.header->pos.x = start_x + listbox->listbox.header->size.x / 2.f;
		listbox->listbox.header->pos.y = (listbox->listbox.container->size.y - listbox->listbox.header->size.y) / 2.f;
	}

	if (pct_vert == 1 && last_shown_idx >= 0) {
		r32 diff = (listbox->listbox.container->pos.y - (listbox->listbox.container->size.y / 2.f)) - (listbox->listbox.items[last_shown_idx]->pos.y - (listbox->listbox.items[last_shown_idx]->size.y / 2.f));
		if (diff > 0) {
			zt_fiz(listbox->listbox.item_count) {
				if (zt_guiItemIsVisible(listbox->listbox.items[i])) {
					listbox->listbox.items[i]->pos.y += diff;
				}
			}

			// todo: this won't work until draw lists support nested clip areas
			//listbox->clip_area.xy = zt_guiItemPositionScreenToLocal(listbox->listbox.items[first_shown_idx], zt_guiItemPositionLocalToScreen(listbox->listbox.container, ztVec2::zero));
			//listbox->clip_area.zw = listbox->listbox.container->size;

			if (listbox->listbox.items[first_shown_idx]->pos.y + (listbox->listbox.items[first_shown_idx]->size.y / 2.f) > (listbox->listbox.container->size.y / 2.f) - (listbox->listbox.header ? listbox->listbox.header->size.y : 0)) {
				zt_guiItemHide(listbox->listbox.items[first_shown_idx]);
			}
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiListBoxScrolled, ztInternal ZT_FUNC_GUI_SCROLLBAR_SCROLLED(_zt_guiListBoxScrolled))
{
	ztGuiItem *listbox = (ztGuiItem*)user_data;
	_zt_guiListBoxAdjustItemsPositions(listbox);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiListBoxUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiListBoxUpdate))
{
	ZT_PROFILE_GUI("_zt_guiListBoxUpdate");

	if (!zt_guiItemIsShowing(item)) {
		return;
	}

	if (zt_bitIsSet(item->behavior_flags, ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted)) {
		_zt_guiListBoxAdjustItemsPositions(item);
		zt_bitRemove(item->behavior_flags, ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted);
	}

	if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty))) {
		item->listbox.total_height = 0;
		item->listbox.total_width  = 0;

		int shown_item_count = 0;
		zt_fiz(item->listbox.item_count) {
			if(item->listbox.hidden[i]) {
				continue;
			}
			shown_item_count += 1;
			item->listbox.heights[i] = item->listbox.items[i]->size.y;
			item->listbox.total_height += item->listbox.heights[i];
			item->listbox.total_width = zt_max(item->listbox.total_width, item->listbox.items[i]->size.x);
		}

		r32 scrollbar_w = item->listbox.scrollbar_vert->size.x;
		r32 scrollbar_h = item->listbox.scrollbar_horz->size.y;

		item->listbox.container->size.x = item->size.x - scrollbar_w;
		item->listbox.container->size.y = item->size.y - scrollbar_h;
		item->listbox.scrollbar_vert->size.y = item->size.y - scrollbar_h;
		item->listbox.scrollbar_horz->size.x = item->size.x - scrollbar_w;

		zt_fiz(item->listbox.item_count) {
			if (!item->listbox.hidden[i] && item->listbox.size_x[i]) {
				item->listbox.items[i]->size.x = item->listbox.container->size.x;
			}
		}

		int items_fit_count_h, items_fit_count_w, steps_count_w;
		_zt_guiListBoxGetFitCount(item, &items_fit_count_h, &items_fit_count_w, &steps_count_w);

		zt_guiScrollbarSetStepsAndPercent(item->listbox.scrollbar_vert, zt_max(0, 1.f / (shown_item_count - items_fit_count_h)), zt_max(0, shown_item_count / (r32)items_fit_count_h), zt_min(1, items_fit_count_h / (r32)shown_item_count));
		zt_guiScrollbarSetStepsAndPercent(item->listbox.scrollbar_horz, zt_max(0, 1.f / (steps_count_w - items_fit_count_w)), zt_max(0, item->listbox.container->size.x / (items_fit_count_w / 2.f)), items_fit_count_w / (r32)steps_count_w);

		if (shown_item_count == 0 || shown_item_count <= items_fit_count_h) {
			zt_guiItemShow(item->listbox.scrollbar_vert, false);
			scrollbar_w = 0;
		}
		else {
			zt_guiItemShow(item->listbox.scrollbar_vert);
		}

		if (steps_count_w <= items_fit_count_w) {
			zt_guiItemShow(item->listbox.scrollbar_horz, false);
			scrollbar_h = 0;
		}
		else {
			zt_guiItemShow(item->listbox.scrollbar_horz);
		}

		zt_guiItemSetPosition(item->listbox.container, ztAlign_Left|ztAlign_Top, ztAnchor_Left|ztAnchor_Top);
		zt_guiItemSetPosition(item->listbox.scrollbar_vert, ztAlign_Right|ztAlign_Top, ztAnchor_Right|ztAnchor_Top);
		zt_guiItemSetPosition(item->listbox.scrollbar_horz, ztAlign_Left|ztAlign_Bottom, ztAnchor_Left|ztAnchor_Bottom);

		_zt_guiListBoxAdjustItemsPositions(item);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiListBoxRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiListBoxRender))
{
	ZT_PROFILE_GUI("_zt_guiListBoxRender");

	zt_guiThemeRender(theme, draw_list, item, offset + item->pos);
}

// ================================================================================================================================================================================================

ztInternal int _zt_guiListBoxSetSelected(ztGuiItem *listbox, int item_idx, bool append_to_selection, bool force_visible, bool from_user_input)
{
	ZT_PROFILE_GUI("zt_guiListBoxSetSelected");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, -1);

	if (item_idx < 0) {
		zt_fiz(listbox->listbox.item_count) {
			if (listbox->listbox.selected[i]) {
				listbox->listbox.selected[i] = false;
			}
		}

		listbox->listbox.prev_active_item = listbox->listbox.active_item;
		listbox->listbox.active_item = -1;
		return 0;
	}

	zt_assertReturnValOnFail(listbox->listbox.item_count > item_idx && item_idx >= 0, -1);

	if (append_to_selection && !zt_bitIsSet(listbox->behavior_flags, ztGuiListBoxBehaviorFlags_MultiSelect)) {
		append_to_selection = false;
	}

	bool already_selected = false;
	if (!append_to_selection) {
		zt_fiz(listbox->listbox.item_count) {
			if (listbox->listbox.selected[i]) {
				if (i == item_idx) {
					already_selected = true;
				}
				else {
					listbox->listbox.selected[i] = false;
				}
			}
		}
	}

	int selected_count = 0;
	if (append_to_selection) {
		zt_fiz(listbox->listbox.item_count) {
			if (listbox->listbox.selected[i]) {
				selected_count += 1;
			}
		}
	}

	if (!already_selected) {
		listbox->listbox.selected[item_idx] = true;
	}

	if (force_visible) {
		zt_guiListBoxScrollToItem(listbox, item_idx);
	}

	listbox->listbox.prev_active_item = listbox->listbox.active_item;
	listbox->listbox.active_item = item_idx;

	if (!already_selected) {
		if (ZT_FUNCTION_POINTER_IS_VALID(listbox->listbox.on_selected) && (from_user_input || zt_bitIsSet(listbox->behavior_flags, ztGuiListBoxBehaviorFlags_AlwaysCallCallback))) {
			ZT_FUNCTION_POINTER_ACCESS(listbox->listbox.on_selected, zt_guiListBoxItemSelected_Func)(listbox, item_idx, listbox->listbox.on_selected_user_data);// listbox->listbox.user_datas[item_idx]);
		}
	}

	return selected_count;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiListBoxInputKeyboard, ztInternal ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiListBoxInputKeyboard))
{
	ZT_PROFILE_GUI("_zt_guiListBoxInputKeyboard");

	if (input_keys[ztInputKeys_Control].pressed()) {
		if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
			zt_guiScrollbarStepNeg(item->listbox.scrollbar_vert);
			_zt_guiListBoxAdjustItemsPositions(item);
			return true;
		}
		if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
			zt_guiScrollbarStepPos(item->listbox.scrollbar_vert);
			_zt_guiListBoxAdjustItemsPositions(item);
			return true;
		}
		if (input_keys[ztInputKeys_Prior].justPressedOrRepeated()) {
			zt_guiScrollbarStepPageNeg(item->listbox.scrollbar_vert);
			_zt_guiListBoxAdjustItemsPositions(item);
			return true;
		}
		if (input_keys[ztInputKeys_Prior].justPressedOrRepeated()) {
			zt_guiScrollbarStepPagePos(item->listbox.scrollbar_vert);
			_zt_guiListBoxAdjustItemsPositions(item);
			return true;
		}
		if(input_keys[ztInputKeys_Home].justPressedOrRepeated()) {
			zt_guiScrollbarSetValue(item->listbox.scrollbar_vert, 0);
			_zt_guiListBoxAdjustItemsPositions(item);
			return true;
		}
		if(input_keys[ztInputKeys_End].justPressedOrRepeated()) {
			zt_guiScrollbarSetValue(item->listbox.scrollbar_vert, 1);
			_zt_guiListBoxAdjustItemsPositions(item);
			return true;
		}
	}
	else {
		bool should_append = input_keys[ztInputKeys_Shift].pressed();

		if (input_keys[ztInputKeys_Up].justPressedOrRepeated()) {
			int sel_idx = zt_guiListBoxGetActiveItem(item);
			int sel_idx_old = sel_idx;
			while (sel_idx >= 1) {
				sel_idx -= 1;
				if (item->listbox.hidden[sel_idx]) {
					continue;
				}

				if (should_append && zt_guiListBoxIsSelected(item, sel_idx)) {
					item->listbox.selected[sel_idx_old] = false;
				}
				_zt_guiListBoxSetSelected(item, sel_idx, should_append, true, true);
				return true;
			}
			return true;
		}
		if (input_keys[ztInputKeys_Down].justPressedOrRepeated()) {
			int sel_idx = zt_guiListBoxGetActiveItem(item);
			int sel_idx_old = sel_idx;
			while (sel_idx >= 0 && sel_idx < item->listbox.item_count - 1) {
				sel_idx += 1;
				if (item->listbox.hidden[sel_idx]) {
					continue;
				}

				if (should_append && zt_guiListBoxIsSelected(item, sel_idx)) {
					item->listbox.selected[sel_idx_old] = false;
				}
				_zt_guiListBoxSetSelected(item, sel_idx, should_append, true, true);
				return true;
			}
			return true;
		}
		if (input_keys[ztInputKeys_Prior].justPressedOrRepeated()) {
			int fit_h, fit_w, steps_w;
			_zt_guiListBoxGetFitCount(item, &fit_h, &fit_w, &steps_w);

			int sel_idx = zt_guiListBoxGetActiveItem(item);

			if (should_append) {
				while (fit_h > 0 && sel_idx > 0) {
					sel_idx -= 1;
					if (item->listbox.hidden[sel_idx]) {
						continue;
					}
					_zt_guiListBoxSetSelected(item, sel_idx, true, true, true);
					fit_h -= 1;
				}
			}
			else {
				while (fit_h > 0 && sel_idx > 0) {
					sel_idx -= 1;
					if (item->listbox.hidden[sel_idx]) {
						continue;
					}
					fit_h -= 1;
					if (fit_h == 0 || sel_idx == 0) {
						_zt_guiListBoxSetSelected(item, sel_idx, false, true, true);
					}
				}
			}

			return true;
		}
		if (input_keys[ztInputKeys_Next].justPressedOrRepeated()) {
			int fit_h, fit_w, steps_w;
			_zt_guiListBoxGetFitCount(item, &fit_h, &fit_w, &steps_w);

			int sel_idx = zt_guiListBoxGetActiveItem(item);

			if (should_append) {
				while (fit_h > 0 && sel_idx < item->listbox.item_count - 1) {
					sel_idx += 1;
					if (item->listbox.hidden[sel_idx]) {
						continue;
					}
					_zt_guiListBoxSetSelected(item, sel_idx, true, true, true);
					fit_h -= 1;
				}
			}
			else {
				while (fit_h > 0 && item->listbox.item_count - 1) {
					sel_idx += 1;
					if (item->listbox.hidden[sel_idx]) {
						continue;
					}
					fit_h -= 1;
					if (fit_h == 0 || sel_idx == item->listbox.item_count - 1) {
						_zt_guiListBoxSetSelected(item, sel_idx, false, true, true);
					}
				}
			}

			return true;
		}
		if(input_keys[ztInputKeys_Home].justPressedOrRepeated()) {
			if(should_append) {
				int sel_idx = zt_guiListBoxGetActiveItem(item);
				for (int i = sel_idx; i >= 0; --i) {
					if (!item->listbox.hidden[i]) {
						_zt_guiListBoxSetSelected(item, i, i != sel_idx, true, true);
					}
				}
				item->listbox.prev_active_item = sel_idx;
			}
			else {
				int sel_idx = 0;
				while (item->listbox.hidden[sel_idx] && sel_idx < item->listbox.item_count) {
					sel_idx += 1;
				}

				_zt_guiListBoxSetSelected(item, sel_idx, false, true, true);
			}
			return true;
		}
		if(input_keys[ztInputKeys_End].justPressedOrRepeated()) {
			if(should_append) {
				int sel_idx = zt_guiListBoxGetActiveItem(item);
				for (int i = sel_idx; i < item->listbox.item_count; ++i) {
					if (!item->listbox.hidden[i]) {
						_zt_guiListBoxSetSelected(item, i, i != sel_idx, true, true);
					}
				}
				item->listbox.prev_active_item = sel_idx;
			}
			else {
				int sel_idx = item->listbox.item_count - 1;
				while (sel_idx >= 0 && item->listbox.hidden[sel_idx]) {
					sel_idx -= 1;
				}

				_zt_guiListBoxSetSelected(item, sel_idx, false, true, true);
			}
			return true;
		}
	}

	if(input_keys[ztInputKeys_Control].pressed()) {
		item->behavior_flags |= ztGuiListBoxInternalBehaviorFlags_ControlPressed;
	}
	else {
		zt_bitRemove(item->behavior_flags, ztGuiListBoxInternalBehaviorFlags_ControlPressed);
	}

	if(input_keys[ztInputKeys_Shift].pressed()) {
		item->behavior_flags |= ztGuiListBoxInternalBehaviorFlags_ShiftPressed;
	}
	else {
		zt_bitRemove(item->behavior_flags, ztGuiListBoxInternalBehaviorFlags_ShiftPressed);
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiListBoxInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiListBoxInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiListBoxInputMouse");

	if (input_mouse->leftJustPressed()) {
		if (zt_bitIsSet(item->gm->item_cache_flags[item->listbox.container->id], ztGuiManagerItemCacheFlags_MouseOver)) {
			ztVec2 local_mpos = zt_guiItemPositionScreenToLocal(item->listbox.container, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));
			zt_fiz(item->listbox.item_count) {
				if (zt_guiItemIsVisible(item->listbox.items[i])) {
					if (zt_collisionPointInRect(local_mpos, zt_vec2(0, item->listbox.items[i]->pos.y), zt_vec2(item->listbox.container->size.x, item->listbox.items[i]->size.y))) {
						if(zt_bitIsSet(item->behavior_flags, ztGuiListBoxInternalBehaviorFlags_ControlPressed)) {
							if(item->listbox.selected[i]) {
								_zt_guiListBoxSetSelected(item, i, true, false, true);
								item->listbox.selected[i] = false;
							}
							else {
								_zt_guiListBoxSetSelected(item, i, true, false, true);
							}
						}
						else if(zt_bitIsSet(item->behavior_flags, ztGuiListBoxInternalBehaviorFlags_ShiftPressed)) {
							int start = zt_guiListBoxGetSelectedCount(item) > 1 ? item->listbox.prev_active_item : item->listbox.active_item;
							for (int j = start; j != i; (start < i ? ++j : --j)) {
								_zt_guiListBoxSetSelected(item, j, j != start, false, true);
							}
							item->listbox.prev_active_item = start;
						}
						else {
							_zt_guiListBoxSetSelected(item, i, false, true, true);
						}

						break;
					}
				}
			}
		}
	}

	if (input_mouse->wheel_delta < 0) {
		zt_guiScrollbarStepPos(item->listbox.scrollbar_vert);
		_zt_guiListBoxAdjustItemsPositions(item);
	}
	else if (input_mouse->wheel_delta > 0) {
		zt_guiScrollbarStepNeg(item->listbox.scrollbar_vert);
		_zt_guiListBoxAdjustItemsPositions(item);
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiListBoxCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiListBoxCleanup))
{
	ZT_PROFILE_GUI("_zt_guiListBoxCleanup");

	zt_freeArena(item->listbox.items, item->gm->arena);
	zt_freeArena(item->listbox.user_datas, item->gm->arena);
	zt_freeArena(item->listbox.selected,   item->gm->arena);
	zt_freeArena(item->listbox.heights,    item->gm->arena);
	zt_freeArena(item->listbox.hidden,     item->gm->arena);
	zt_freeArena(item->listbox.size_x,     item->gm->arena);
	item->listbox.item_size = 0;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeListBox(ztGuiItem *parent, i32 behavior_flags, i32 max_items)
{
	ZT_PROFILE_GUI("zt_guiMakeListBox");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_ListBox, behavior_flags | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsKeyboardAlways | ztGuiItemBehaviorFlags_ClipChildren | ztGuiItemBehaviorFlags_ClipContents);
	zt_returnValOnNull(item, nullptr);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	item->listbox.items            = zt_mallocStructArrayArena(ztGuiItem*, max_items, item->gm->arena);
	item->listbox.user_datas       = zt_mallocStructArrayArena(void*, max_items, item->gm->arena);
	item->listbox.selected         = zt_mallocStructArrayArena(bool, max_items, item->gm->arena);
	item->listbox.heights          = zt_mallocStructArrayArena(r32, max_items, item->gm->arena);
	item->listbox.hidden           = zt_mallocStructArrayArena(bool, max_items, item->gm->arena);
	item->listbox.size_x           = zt_mallocStructArrayArena(bool, max_items, item->gm->arena);
	item->listbox.item_count       = 0;
	item->listbox.item_size        = max_items;
	item->listbox.total_height     = 0;
	item->listbox.total_width      = 0;
	item->listbox.active_item      = -1;
	item->listbox.prev_active_item = -1;
	item->listbox.header           = nullptr;

	item->listbox.container = zt_guiMakePanel(item, ztGuiItemBehaviorFlags_ClipChildren | ztGuiItemBehaviorFlags_ClipContents);

	item->listbox.scrollbar_vert = zt_guiMakeScrollbar(item, ztGuiItemOrient_Vert, &item->listbox.scroll_amt_vert);
	item->listbox.scrollbar_horz = zt_guiMakeScrollbar(item, ztGuiItemOrient_Horz, &item->listbox.scroll_amt_horz);

	zt_guiScrollbarSetCallback(item->listbox.scrollbar_vert, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxScrolled), item);
	zt_guiScrollbarSetCallback(item->listbox.scrollbar_horz, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxScrolled), item);

	zt_guiItemSetPosition(item->listbox.scrollbar_vert, ztAlign_Right|ztAlign_Top, ztAnchor_Right|ztAnchor_Top);

	item->functions.update       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxUpdate);
	item->functions.render       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxRender);
	item->functions.input_mouse  = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxInputMouse);
	item->functions.input_key    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxInputKeyboard);
	item->functions.cleanup      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiListBoxCleanup);

	item->listbox.on_selected    = ZT_FUNCTION_POINTER_TO_VAR_NULL;

	zt_guiThemeSizeItem(theme, item);

	return item;
}

// ================================================================================================================================================================================================

int zt_guiListBoxAppend(ztGuiItem *listbox, ztGuiItem *item, void *user_data, bool size_width)
{
	ZT_PROFILE_GUI("zt_guiListBoxAppend");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, -1);
	zt_assertReturnValOnFail(listbox->listbox.item_count < listbox->listbox.item_size, -1);

	int idx = listbox->listbox.item_count++;
	listbox->listbox.items     [idx] = item;
	listbox->listbox.user_datas[idx] = user_data;
	listbox->listbox.selected  [idx] = false;
	listbox->listbox.heights   [idx] = 0;
	listbox->listbox.hidden    [idx] = false;
	listbox->listbox.size_x    [idx] = size_width;
	zt_guiItemReparent(item, listbox->listbox.container);
	//item->behavior_flags |= ztGuiItemBehaviorFlags_ClipContents | ztGuiItemBehaviorFlags_ClipChildren;

	listbox->state_flags |= zt_bit(ztGuiItemStates_Dirty);
	listbox->behavior_flags |= ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted;

	if (idx == 0) {
		listbox->listbox.prev_active_item = -1;
		listbox->listbox.active_item = idx;
	}

	return idx;
}

// ================================================================================================================================================================================================

int zt_guiListBoxAppend(ztGuiItem *listbox, const char *item, void *user_data)
{
	ZT_PROFILE_GUI("zt_guiListBoxAppend");
	return zt_guiListBoxAppend(listbox, zt_guiMakeStaticText(listbox, item, zt_bitIsSet(listbox->behavior_flags, ztGuiListBoxBehaviorFlags_UseFancyText) ? ztGuiStaticTextBehaviorFlags_Fancy : 0), user_data);
}

// ================================================================================================================================================================================================

void zt_guiListBoxClear(ztGuiItem *listbox)
{
	ZT_PROFILE_GUI("zt_guiListBoxClear");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);

	zt_fiz(listbox->listbox.item_count) {
		zt_guiItemQueueFree(listbox->listbox.items[i]);
	}

	listbox->listbox.item_count = 0;
	listbox->listbox.active_item = -1;
	listbox->listbox.prev_active_item = -1;

	listbox->behavior_flags |= ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted;
}

// ================================================================================================================================================================================================

int zt_guiListBoxGetActiveItem(ztGuiItem *listbox)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetSelectedCount");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, -1);

	return listbox->listbox.active_item;
}

// ================================================================================================================================================================================================

int zt_guiListBoxGetSelectedCount(ztGuiItem *listbox)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetSelectedCount");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, -1);

	int selected = 0;
	zt_fiz(listbox->listbox.item_count) {
		if (listbox->listbox.selected[i]) {
			selected += 1;
		}
	}

	return selected;
}

// ================================================================================================================================================================================================

int zt_guiListBoxGetSelected(ztGuiItem *listbox, int which)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetSelected");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, -1);

	int selected = which;
	zt_fiz(listbox->listbox.item_count) {
		if (listbox->listbox.selected[i]) {
			if (selected-- == which) {
				return i;
			}
		}
	}

	return -1;
}

// ================================================================================================================================================================================================

bool zt_guiListBoxIsSelected(ztGuiItem *listbox, int item_idx)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetSelectedCount");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, false);

	if(item_idx < 0 || item_idx >= listbox->listbox.item_count) {
		return false;
	}

	return listbox->listbox.selected[item_idx];
}

// ================================================================================================================================================================================================

int zt_guiListBoxGetCount(ztGuiItem *listbox)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetCount");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, -1);

	return listbox->listbox.item_count;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiListBoxGetItem(ztGuiItem *listbox, int item_idx)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetItem");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, nullptr);
	zt_assertReturnValOnFail(listbox->listbox.item_count > item_idx && item_idx >= 0, nullptr);

	return listbox->listbox.items[item_idx];
}

// ================================================================================================================================================================================================

void *zt_guiListBoxGetItemUserData(ztGuiItem *listbox, int item_idx)
{
	ZT_PROFILE_GUI("zt_guiListBoxGetItemUserData");

	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, nullptr);
	zt_assertReturnValOnFail(listbox->listbox.item_count > item_idx && item_idx >= 0, nullptr);

	return listbox->listbox.user_datas[item_idx];
}

// ================================================================================================================================================================================================

int zt_guiListBoxSetSelected(ztGuiItem *listbox, int item_idx, bool append_to_selection, bool force_visible)
{
	return _zt_guiListBoxSetSelected(listbox, item_idx, append_to_selection, force_visible, false);
}

// ================================================================================================================================================================================================

void zt_guiListBoxShowItem(ztGuiItem *listbox, int item_idx, bool show)
{
	ZT_PROFILE_GUI("zt_guiListBoxShowItem");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);
	zt_assertReturnOnFail(listbox->listbox.item_count > item_idx && item_idx >= 0);

	listbox->listbox.hidden[item_idx] = !show;

	listbox->state_flags |= zt_bit(ztGuiItemStates_Dirty);

	_zt_guiListBoxAdjustItemsPositions(listbox);
}

// ================================================================================================================================================================================================

void zt_guiListBoxHideItem(ztGuiItem *listbox, int item_idx)
{
	zt_guiListBoxShowItem(listbox, item_idx, false);
}

// ================================================================================================================================================================================================

bool zt_guiListBoxIsItemShown(ztGuiItem *listbox, int item_idx)
{
	ZT_PROFILE_GUI("zt_guiListBoxIsItemShown");
	zt_assertReturnValOnFail(listbox->type == ztGuiItemType_ListBox, false);
	zt_assertReturnValOnFail(listbox->listbox.item_count > item_idx && item_idx >= 0, false);

	return !listbox->listbox.hidden[item_idx];
}

// ================================================================================================================================================================================================

void zt_guiListBoxScrollToItem(ztGuiItem *listbox, int item_idx)
{
	ZT_PROFILE_GUI("zt_guiListBoxScrollToItem");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);
	zt_assertReturnOnFail(listbox->listbox.item_count > item_idx && item_idx >= 0);

	if (zt_bitIsSet(listbox->behavior_flags, ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted) ||
		zt_bitIsSet(listbox->state_flags, zt_bit(ztGuiItemStates_Dirty))) {
		_zt_guiListBoxUpdate(listbox, 0, listbox->functions.user_data);
	}

	bool needs_scroll = true;

	if (zt_guiItemIsVisible(listbox->listbox.items[item_idx])) {
		needs_scroll = false;
	}
	else if (!zt_guiItemIsVisible(listbox->listbox.scrollbar_vert)) {
		needs_scroll = false;
	}

	if (needs_scroll) {
		int first_visible = -1;
		zt_fiz(listbox->listbox.item_count) {
			if (zt_guiItemIsVisible(listbox->listbox.items[i])) {
				first_visible = i;
				break;
			}
		}

		if (item_idx < first_visible) {
			while (zt_guiScrollbarGetValue(listbox->listbox.scrollbar_vert) > 0) {
				zt_guiScrollbarStepNeg(listbox->listbox.scrollbar_vert);
				_zt_guiListBoxAdjustItemsPositions(listbox);

				if (zt_guiItemIsVisible(listbox->listbox.items[item_idx])) {
					break;
				}
			}
		}
		else {
			while (zt_guiScrollbarGetValue(listbox->listbox.scrollbar_vert) < 1) {
				zt_guiScrollbarStepPos(listbox->listbox.scrollbar_vert);
				_zt_guiListBoxAdjustItemsPositions(listbox);

				if (zt_guiItemIsVisible(listbox->listbox.items[item_idx])) {
					break;
				}
			}
		}
	}

	// check for partial visibility at the bottom
	while (listbox->listbox.items[item_idx]->pos.y - (listbox->listbox.items[item_idx]->size.y / 2.f) < (listbox->listbox.container->pos.y - (listbox->listbox.container->size.y / 2.f)) && listbox->listbox.scrollbar_vert->slider.value < 1) {
		zt_guiScrollbarStepPos(listbox->listbox.scrollbar_vert);
		_zt_guiListBoxAdjustItemsPositions(listbox);
	}
}

// ================================================================================================================================================================================================

void zt_guiListBoxSetHeaderItem(ztGuiItem *listbox, ztGuiItem *header)
{
	ZT_PROFILE_GUI("zt_guiListBoxSetHeaderItem");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);

	listbox->listbox.header = header;
	listbox->state_flags |= zt_bit(ztGuiItemStates_Dirty);

	zt_guiItemReparent(header, listbox->listbox.container);
}

// ================================================================================================================================================================================================

void zt_guiListBoxSetCallback(ztGuiItem *listbox, ZT_FUNCTION_POINTER_VAR(function_id, zt_guiListBoxItemSelected_Func), void *user_data)
{
	ZT_PROFILE_GUI("zt_guiListBoxSetCallback");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);

	listbox->listbox.on_selected = function_id;
	listbox->listbox.on_selected_user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiListBoxRefresh(ztGuiItem *listbox)
{
	ZT_PROFILE_GUI("zt_guiListBoxRefresh");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);

	zt_guiSizerRecalcImmediately(listbox->listbox.container);

	_zt_guiListBoxAdjustItemsPositions(listbox);
	listbox->behavior_flags |= ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted;
	listbox->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

void zt_guiListBoxRemoveItem(ztGuiItem *listbox, int item)
{
	ZT_PROFILE_GUI("zt_guiListBoxRemoveItem");
	zt_assertReturnOnFail(listbox->type == ztGuiItemType_ListBox);
	zt_assertReturnOnFail(item >= 0 && item < listbox->listbox.item_count);

	zt_guiItemQueueFree(listbox->listbox.items[item]);

	for (int i = item; i < listbox->listbox.item_count; ++i) {
		listbox->listbox.items     [i] = listbox->listbox.items     [i + 1];
		listbox->listbox.user_datas[i] = listbox->listbox.user_datas[i + 1];
		listbox->listbox.selected  [i] = listbox->listbox.selected  [i + 1];
		listbox->listbox.heights   [i] = listbox->listbox.heights   [i + 1];
		listbox->listbox.hidden    [i] = listbox->listbox.hidden    [i + 1];
		listbox->listbox.size_x    [i] = listbox->listbox.size_x    [i + 1];
	}

	if (listbox->listbox.active_item == item) {
		listbox->listbox.prev_active_item = item;
		listbox->listbox.active_item = -1;
	}

	listbox->listbox.item_count -= 1;

	listbox->behavior_flags |= ztGuiListBoxInternalBehaviorFlags_NeedsAdjusted;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiColorPickerInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiColorPickerInputMouse");

	if (input_mouse->leftJustReleased()) {
		zt_guiDialogColorPicker(&item->color, item->behavior_flags);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiColorPickerRender))
{
	ZT_PROFILE_GUI("_zt_guiColorPickerRender");

	zt_drawListPushTexture(draw_list, ztTextureDefault);
	zt_drawListAddSolidOutlinedRect2D(draw_list, item->pos + offset, item->size, item->color, ztColor_White);
	zt_drawListPopTexture(draw_list);

	if (item->color_picker.live_value && *item->color_picker.live_value != item->color) {
		*item->color_picker.live_value = item->color;
	}
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeColorPicker(ztGuiItem *parent, ztColor color, i32 behavior_flags, ztColor *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeColorPicker");
	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_ColorPicker, behavior_flags | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput);
	item->color = color;
	item->size = zt_vec2(1, zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_TextEditDefaultH, item));

	item->color_picker.callback = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->color_picker.user_data = nullptr;
	item->color_picker.live_value = live_value;

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerRender);

	return item;
}

// ================================================================================================================================================================================================

void zt_guiColorPickerSetCallback(ztGuiItem *color_picker, ZT_FUNCTION_POINTER_VAR(callback, zt_guiColorPickerChanged_Func), void *user_data)
{
	zt_returnOnNull(color_picker);
	zt_assertReturnOnFail(color_picker->type == ztGuiItemType_ColorPicker);

	color_picker->color_picker.callback = callback;
	color_picker->color_picker.user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiColorPickerSetLiveValue(ztGuiItem *color_picker, ztColor *live_value)
{
	zt_returnOnNull(color_picker);
	zt_assertReturnOnFail(color_picker->type == ztGuiItemType_ColorPicker);

	color_picker->color_picker.live_value = live_value;

	if (live_value) {
		color_picker->color = *live_value;
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiGradientPickerInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiGradientPickerInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiGradientPickerInputMouse");

	if (input_mouse->leftJustReleased()) {
		zt_guiDialogColorGradient(item->gradient_picker.gradient, item->behavior_flags);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiGradientPickerRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiGradientPickerRender))
{
	ZT_PROFILE_GUI("_zt_guiGradientPickerRender");

	ztVec2 center = item->pos + offset;
	ztVec2 size = item->size;
	ztVec3 start = zt_vec3(center.x - (size.x / 2), center.y, 0);

	//zt_drawListAddSpriteTiled(draw_list, &zt_spriteMake(grad_editor->tex_background, 0, 0, 32, 32), zt_vec3(center, 0), size);

	{
		ztColor colors[ZT_COLOR_GRADIENT_MAX_VALUES * 2];
		r32 locations[ZT_COLOR_GRADIENT_MAX_VALUES * 2];
		int colors_count = zt_colorGradientGetColors(item->gradient_picker.gradient, colors, locations, ZT_COLOR_GRADIENT_MAX_VALUES * 2);

		zt_drawListPushTexture(draw_list, ztTextureDefault);
		zt_fiz(colors_count - 1) {
			r32 width_this = size.x * (locations[i + 1] - locations[i]);

			ztColor colors_this[] = {
				colors[i], zt_vec4(colors[i].xyz, colors[i].a), zt_vec4(colors[i + 1].xyz, colors[i + 1].a), colors[i + 1]
			};

			zt_drawListAddFilledRect2D(draw_list, start + zt_vec3(width_this / 2, 0, 0), zt_vec2(width_this, size.y), ztVec2::zero, ztVec2::one, colors_this);
			start.x += width_this;
		}
		zt_drawListPopTexture(draw_list);
	}

	if (item->gradient_picker.live_value && !zt_colorGradientIsEqual(item->gradient_picker.live_value, item->gradient_picker.gradient)) {
		zt_memCpy(item->gradient_picker.live_value, zt_sizeof(ztColorGradient2), item->gradient_picker.gradient, zt_sizeof(ztColorGradient2));
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiGradientPickerCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiGradientPickerCleanup))
{
	ZT_PROFILE_GUI("_zt_guiGradientPickerCleanup");

	zt_freeArena(item->gradient_picker.gradient, item->gm->arena);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeGradientPicker(ztGuiItem *parent, ztColorGradient2 *gradient, i32 behavior_flags, ztColorGradient2 *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeGradientPicker");
	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_GradientPicker, behavior_flags | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput);

	item->size = zt_vec2(1, zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_TextEditDefaultH, item));

	item->gradient_picker.gradient = zt_mallocStructArena(ztColorGradient2, item->gm->arena);

	if (gradient) {
		zt_memCpy(item->gradient_picker.gradient, zt_sizeof(ztColorGradient2), gradient, zt_sizeof(ztColorGradient2));
	}
	else {
		item->gradient_picker.gradient->color_vals[item->gradient_picker.gradient->color_entries  ] = ztColor_Black;
		item->gradient_picker.gradient->color_locs[item->gradient_picker.gradient->color_entries++] = 0;
		item->gradient_picker.gradient->color_vals[item->gradient_picker.gradient->color_entries  ] = ztColor_White;
		item->gradient_picker.gradient->color_locs[item->gradient_picker.gradient->color_entries++] = 1;

		item->gradient_picker.gradient->alpha_vals[item->gradient_picker.gradient->alpha_entries  ] = 1;
		item->gradient_picker.gradient->alpha_locs[item->gradient_picker.gradient->alpha_entries++] = 0;
		item->gradient_picker.gradient->alpha_vals[item->gradient_picker.gradient->alpha_entries  ] = 1;
		item->gradient_picker.gradient->alpha_locs[item->gradient_picker.gradient->alpha_entries++] = 1;
	}

	item->gradient_picker.callback = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->gradient_picker.user_data = nullptr;
	item->gradient_picker.live_value = live_value;

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiGradientPickerInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiGradientPickerRender);
	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiGradientPickerCleanup);

	return item;
}

// ================================================================================================================================================================================================

void zt_guiGradientPickerSetCallback(ztGuiItem *gradient_picker, ZT_FUNCTION_POINTER_VAR(callback, zt_guiColorGradientChanged_Func), void *user_data)
{
	zt_returnOnNull(gradient_picker);
	zt_assertReturnOnFail(gradient_picker->type == ztGuiItemType_GradientPicker);

	gradient_picker->gradient_picker.callback = callback;
	gradient_picker->gradient_picker.user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiGradientPickerSetLiveValue(ztGuiItem *gradient_picker, ztColorGradient2 *live_value)
{
	ZT_PROFILE_GUI("zt_guiGradientPickerSetLiveValue");

	zt_returnOnNull(gradient_picker);
	zt_assertReturnOnFail(gradient_picker->type == ztGuiItemType_GradientPicker);

	gradient_picker->gradient_picker.live_value = live_value;

	if (live_value) {
		zt_memCpy(gradient_picker->gradient_picker.gradient, zt_sizeof(ztColorGradient2), live_value, zt_sizeof(ztColorGradient2));
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiAnimCurveInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiAnimCurveInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiAnimCurveInputMouse");

	if (input_mouse->leftJustReleased()) {
		zt_guiDialogAnimCurveEditor(item->anim_curve.curve, item->behavior_flags);
		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiAnimCurveRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiAnimCurveRender))
{
	ZT_PROFILE_GUI("_zt_guiAnimCurveRender");

	zt_drawListPushTexture(draw_list, ztTextureDefault);
	zt_drawListAddSolidOutlinedRect2D(draw_list, item->pos + offset, item->size, ztColor_DarkGray, ztColor_Gray);
	zt_drawListPushColor(draw_list, ztColor_Green);


	ztVec2 center = item->pos + offset;
	r32 start = center.x - item->size.x / 2;

	i32 pixels_wide = zt_convertToi32Floor(item->size.x * zt_pixelsPerUnit());
	r32 size_per_pixel = 1 / zt_pixelsPerUnit();

	zt_fiz(pixels_wide) {
		r32 val = zt_animCurveGetValue(item->anim_curve.curve, i / (r32)pixels_wide) / item->anim_curve.curve->val_max;
		zt_drawListAddPoint(draw_list, zt_vec3(start, center.y + val * (item->size.y / 2), 0));
		start += size_per_pixel;
	}

	zt_drawListPopColor(draw_list);
	zt_drawListPopTexture(draw_list);

	if (item->anim_curve.live_value && 0 != zt_memCmp(item->anim_curve.live_value, item->anim_curve.curve, zt_sizeof(ztAnimCurve))) {
		zt_memCpy(item->anim_curve.live_value, zt_sizeof(ztAnimCurve), item->anim_curve.curve, zt_sizeof(ztAnimCurve));
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiAnimCurveCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiAnimCurveCleanup))
{
	ZT_PROFILE_GUI("_zt_guiAnimCurveCleanup");

	zt_freeArena(item->anim_curve.curve, item->gm->arena);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeAnimCurve(ztGuiItem *parent, ztAnimCurve *curve, i32 behavior_flags, ztAnimCurve *live_value)
{
	ZT_PROFILE_GUI("zt_guiMakeAnimCurve");
	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_AnimCurve, behavior_flags | ztGuiItemBehaviorFlags_ClipContents | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput);
	item->size = zt_vec2(1.5f, zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_TextEditDefaultH, item));

	item->anim_curve.curve = zt_mallocStructArena(ztAnimCurve, item->gm->arena);

	if (curve != nullptr) {
		zt_memCpy(item->anim_curve.curve, zt_sizeof(ztAnimCurve), curve, zt_sizeof(ztAnimCurve));
	}
	else {
		ztAnimCurve lcl_curve;
		lcl_curve.type = ztAnimCurveType_Linear;
		lcl_curve.val_max = 1;
		lcl_curve.val_beg = 0;
		lcl_curve.val_end = 1;

		zt_memCpy(item->anim_curve.curve, zt_sizeof(ztAnimCurve), &lcl_curve, zt_sizeof(ztAnimCurve));
	}

	item->anim_curve.callback = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	item->anim_curve.user_data = nullptr;
	item->anim_curve.live_value = live_value;

	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiAnimCurveInputMouse);
	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiAnimCurveRender);
	item->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiAnimCurveCleanup);

	return item;
}

// ================================================================================================================================================================================================

void zt_guiAnimCurveSetCallback(ztGuiItem *anim_curve, ZT_FUNCTION_POINTER_VAR(callback, zt_guiEditorValueChanged_Func), void *user_data)
{
	zt_returnOnNull(anim_curve);
	zt_assertReturnOnFail(anim_curve->type == ztGuiItemType_AnimCurve);

	anim_curve->anim_curve.callback = callback;
	anim_curve->anim_curve.user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiAnimCurveSetLiveValue(ztGuiItem *anim_curve, ztAnimCurve *live_value)
{
	ZT_PROFILE_GUI("zt_guiAnimCurveSetLiveValue");

	zt_returnOnNull(anim_curve);
	zt_assertReturnOnFail(anim_curve->type == ztGuiItemType_AnimCurve);

	anim_curve->anim_curve.live_value = live_value;

	if (live_value) {
		zt_memCpy(anim_curve->anim_curve.curve, zt_sizeof(ztAnimCurve), live_value, zt_sizeof(ztAnimCurve));
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

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
			r32  value_last;
			r32 *value;
			r32  min;
			r32  max;
			r32  step;
		} val_r32;

		struct {
			i32  value_last;
			i32 *value;
			i32  min;
			i32  max;
			i32  step;
		} val_i32;
	};

	ztGuiItem    *editor;
	ztGuiItem    *text_edit;
	ztGuiItem    *spinner;

	ZT_FUNCTION_POINTER_VAR(func_val_changed, zt_guiEditorValueChanged_Func);
	void                   *func_val_changed_user_data;

};

#define ztGuiEditorFirstChildName       "editor"
#define ztGuiEditorFirstChildNameVec2   "editor-vec2"
#define ztGuiEditorFirstChildNameVec3   "editor-vec3"
#define ztGuiEditorFirstChildNameVec4   "editor-vec4"
#define ztGuiEditorFirstChildNameVec2i  "editor-vec2i"

#define ztGuiEditor_Guid                zt_guidMake(0x4787c0e7, 0x2c9d61aa, 0xc7f1dc78, 0x8776b714)


// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiEditorUpdate))
{
	ZT_PROFILE_GUI("_zt_guiEditorUpdate");

	if (!zt_guiItemIsShowing(item)) {
		return;
	}

	// item is the panel
	ztGuiEditorValue *vptr = (ztGuiEditorValue*)item->panel.user_data;

	if (vptr->type == ztGuiEditorType_i32) {
		if (*vptr->val_i32.value != vptr->val_i32.value_last) {
			vptr->val_i32.value_last = *vptr->val_i32.value;
			vptr->needs_update_from_spinner = true;
		}
	}
	else if (vptr->type == ztGuiEditorType_r32) {
		if (*vptr->val_r32.value != vptr->val_r32.value_last) {
			vptr->val_r32.value_last = *vptr->val_r32.value;
			vptr->needs_update_from_spinner = true;
		}
	}

	if (vptr->needs_update_from_editor) {
		vptr->needs_update_from_editor = false;
		vptr->needs_update_from_spinner = true;

		char buffer[128];
		zt_guiTextEditGetValue(vptr->text_edit, buffer, zt_elementsOf(buffer));

		if (vptr->type == ztGuiEditorType_i32) {
			if (vptr->val_i32.value == nullptr) return;
			*vptr->val_i32.value = zt_strToInt(buffer, 0);
			vptr->val_i32.value_last = *vptr->val_i32.value;
		}
		else if (vptr->type == ztGuiEditorType_r32) {
			if (vptr->val_r32.value == nullptr) return;
			*vptr->val_r32.value = zt_strToReal32(buffer, 0);
			vptr->val_r32.value_last = *vptr->val_r32.value;
		}

		if (ZT_FUNCTION_POINTER_IS_VALID(vptr->func_val_changed)) {
			ZT_FUNCTION_POINTER_ACCESS(vptr->func_val_changed, zt_guiEditorValueChanged_Func)(item, vptr->func_val_changed_user_data);
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

		if (ZT_FUNCTION_POINTER_IS_VALID(vptr->func_val_changed)) {
			ZT_FUNCTION_POINTER_ACCESS(vptr->func_val_changed, zt_guiEditorValueChanged_Func)(item, vptr->func_val_changed_user_data);
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorTextChange, ZT_FUNC_GUI_TEXTEDIT_KEY(_zt_guiEditorTextChange))
{
	ZT_PROFILE_GUI("_zt_guiEditorTextChange");

	ztGuiEditorValue *vptr = (ztGuiEditorValue*)user_data;

	zt_fiz(ZT_MAX_INPUT_KEYSTROKES) {
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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorSpinnerChanged, ZT_FUNC_GUI_SPINNER_VALUE_CHANGED(_zt_guiEditorSpinnerChanged))
{
	ZT_PROFILE_GUI("_zt_guiEditorSpinnerChanged");

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

// ================================================================================================================================================================================================

ztInternal ztGuiItem *_zt_guiEditorMakeBase(ztGuiItem *parent, const char *label, ztGuiEditorValue *value)
{
	ZT_PROFILE_GUI("_zt_guiEditorMakeBase");

	ztGuiItem *panel = zt_guiMakePanel(parent, 0, value, parent->gm->arena);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz);
	zt_guiSizerSizeToParent(sizer);

	zt_guiItemSetName(sizer, ztGuiEditorFirstChildName);

	panel->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorUpdate);
	panel->panel.guid = ztGuiEditor_Guid;

	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, 0);
		zt_guiSizerAddStretcher(sizer, 0, zt_guiThemeGetRValue(zt_guiItemGetTheme(parent), ztGuiThemeValue_r32_Padding, parent));
	}

	char val_min[64], val_max[64];
	switch (value->type)
	{
		case ztGuiEditorType_i32: {
			zt_strPrintf(val_min, 64, "%d", value->val_i32.min);
			zt_strPrintf(val_max, 64, "%d", value->val_i32.max);
		}; break;

		case ztGuiEditorType_r32: {
			zt_strPrintf(val_min, 64, "%.2f", value->val_r32.min);
			zt_strPrintf(val_max, 64, "%.2f", value->val_r32.max);
		}; break;
	}

	ztGuiTheme *theme = zt_guiItemGetTheme(panel);
	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_FontID, panel);
	ztVec2 ext_min = zt_fontGetExtents(font, val_min);
	ztVec2 ext_max = zt_fontGetExtents(font, val_max);

	r32 width = zt_max(ext_min.x, ext_max.x);

	char val_str[32] = "0";
	ztGuiItem *text = zt_guiMakeTextEdit(sizer, val_str, 0, 32);
	text->size.x = zt_min(text->size.x, width + 6 / zt_pixelsPerUnit());
	text->size.x = zt_fontGetExtents(font, "0").x;
	zt_guiTextEditSetCallback(text, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorTextChange), value); // todo: need user data on this callback

	zt_guiSizerAddItem(sizer, text, 1, 0);

	ztGuiItem *spinner = zt_guiMakeSpinner(sizer);
	zt_guiSpinnerSetCallback(spinner, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorSpinnerChanged), value);

	zt_guiSizerAddItem(sizer, spinner, 0, 0);

	panel->size = zt_guiSizerGetMinSize(sizer);
	panel->min_size = panel->size;

	value->editor = panel;
	value->text_edit = text;
	value->spinner = spinner;
	value->needs_update_from_spinner = true;
	value->needs_update_from_editor = false;

	value->func_val_changed = ZT_FUNCTION_POINTER_TO_VAR_NULL;
	value->func_val_changed_user_data = nullptr;

	return panel;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, r32 *value, r32 min, r32 max, r32 step)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiEditorValue *val = zt_mallocStructArena(ztGuiEditorValue, parent->gm->arena);
	val->type = ztGuiEditorType_r32;
	val->val_r32.value_last = *value;
	val->val_r32.value = value;
	val->val_r32.min = min;
	val->val_r32.max = max;
	val->val_r32.step = step;

	return _zt_guiEditorMakeBase(parent, label, val);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, i32 *value, i32 min, i32 max, i32 step)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiEditorValue *val = zt_mallocStructArena(ztGuiEditorValue, parent->gm->arena);
	val->type = ztGuiEditorType_i32;
	val->val_i32.value_last = *value;
	val->val_i32.value = value;
	val->val_i32.min = min;
	val->val_i32.max = max;
	val->val_i32.step = step;
	return _zt_guiEditorMakeBase(parent, label, val);
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec2 *value, ztVec2 min, ztVec2 max, r32 step, bool label_above, const char *label_x, const char *label_y)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, label_above ? ztGuiItemOrient_Vert : ztGuiItemOrient_Horz);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec2);

	r32 padding = 1 / zt_pixelsPerUnit();
	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, 0);

	const char * labels[] = { label_x, label_y };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	panel->size = zt_guiSizerGetMinSize(sizer) + zt_vec2(6 / zt_pixelsPerUnit(), 6 / zt_pixelsPerUnit());
	//panel->min_size = panel->size;

	return panel;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec3 *value, ztVec3 min, ztVec3 max, r32 step, bool label_above, const char *label_x, const char *label_y, const char *label_z)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, label_above ? ztGuiItemOrient_Vert : ztGuiItemOrient_Horz);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec3);

	r32 padding = 3 / zt_pixelsPerUnit();
	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 0, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, 0);

	const char * labels[] = { label_x, label_y, label_z };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	panel->size = zt_guiSizerGetMinSize(sizer) + zt_vec2(6 / zt_pixelsPerUnit(), 6 / zt_pixelsPerUnit());
	//panel->min_size = panel->size;

	return panel;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec4 *value, ztVec4 min, ztVec4 max, r32 step, bool label_above, const char *label_x, const char *label_y, const char *label_z, const char *label_w)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec4);

	r32 padding = 3 / zt_pixelsPerUnit();
	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, 0);

	const char * labels[] = { label_x, label_y, label_z, label_w };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);

		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	panel->size = zt_guiSizerGetMinSize(sizer) + zt_vec2(6 / zt_pixelsPerUnit(), 6 / zt_pixelsPerUnit());
	//panel->min_size = panel->size;

	return panel;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec2i *value, ztVec2i min, ztVec2i max, i32 step, bool label_above, const char *label_x, const char *label_y)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec2i);

	r32 padding = 1 / zt_pixelsPerUnit();
	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, 0);

	const char * labels[] = { label_x, label_y };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	panel->size = zt_guiSizerGetMinSize(sizer);// +zt_vec2(6 / zt_pixelsPerUnit(), 6 / zt_pixelsPerUnit());
	//panel->min_size = panel->size;

	return panel;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec3i *value, ztVec3i min, ztVec3i max, i32 step, bool label_above, const char *label_x, const char *label_y, const char *label_z)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec2i);

	r32 padding = 1 / zt_pixelsPerUnit();
	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, 0);

	const char * labels[] = { label_x, label_y, label_z };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	panel->size = zt_guiSizerGetMinSize(sizer);// +zt_vec2(6 / zt_pixelsPerUnit(), 6 / zt_pixelsPerUnit());
	//panel->min_size = panel->size;

	return panel;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, const char *label, ztVec4i *value, ztVec4i min, ztVec4i max, i32 step, bool label_above, const char *label_x, const char *label_y, const char *label_z, const char *label_w)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiItemSetName(sizer, ztGuiEditorFirstChildNameVec2i);

	r32 padding = 1 / zt_pixelsPerUnit();
	if (label != nullptr) {
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, label), 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	ztGuiItem *sizer_edit = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_edit, 1, 0);

	const char * labels[] = { label_x, label_y, label_z, label_w };

	zt_fize(labels) {
		if (i != 0) {
			zt_guiSizerAddStretcher(sizer_edit, 0, padding);
		}

		ztGuiItem *editor = zt_guiMakeEditor(sizer_edit, labels[i], (value ? &value->values[i] : nullptr), min.values[i], max.values[i], step);
		zt_guiSizerAddItem(sizer_edit, editor, 1, padding, ztAlign_Center, ztGuiItemOrient_Horz);
	}

	panel->size = zt_guiSizerGetMinSize(sizer);// +zt_vec2(6 / zt_pixelsPerUnit(), 6 / zt_pixelsPerUnit());
	//panel->min_size = panel->size;

	return panel;
}

// ================================================================================================================================================================================================

void zt_guiEditorSetToMin(ztGuiItem *editor)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToMin");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToMax(ztGuiItem *editor)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToMax");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToValue(ztGuiItem *editor, r32 value)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToValue");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToValue(ztGuiItem *editor, i32 value)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToValue");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec2 value)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToValue");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec3 value)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToValue");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec4 value)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToValue");

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

// ================================================================================================================================================================================================

void zt_guiEditorSetToValue(ztGuiItem *editor, ztVec2i value)
{
	ZT_PROFILE_GUI("zt_guiEditorSetToValue");

	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec2i)) {
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

// ================================================================================================================================================================================================

void zt_guiEditorReassign(ztGuiItem *editor, r32 *value)
{
	ZT_PROFILE_GUI("zt_guiEditorReassign");

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

// ================================================================================================================================================================================================

void zt_guiEditorReassign(ztGuiItem *editor, i32 *value)
{
	ZT_PROFILE_GUI("zt_guiEditorReassign");

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

// ================================================================================================================================================================================================

void zt_guiEditorReassign(ztGuiItem *editor, ztVec2 *value)
{
	ZT_PROFILE_GUI("zt_guiEditorReassign");

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

// ================================================================================================================================================================================================

void zt_guiEditorReassign(ztGuiItem *editor, ztVec3 *value)
{
	ZT_PROFILE_GUI("zt_guiEditorReassign");

	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec3)) {
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

// ================================================================================================================================================================================================

void zt_guiEditorReassign(ztGuiItem *editor, ztVec4 *value)
{
	ZT_PROFILE_GUI("zt_guiEditorReassign");

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

// ================================================================================================================================================================================================

void zt_guiEditorReassign(ztGuiItem *editor, ztVec2i *value)
{
	ZT_PROFILE_GUI("zt_guiEditorReassign");

	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildNameVec2i)) {
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

// ================================================================================================================================================================================================

void zt_guiEditorSetCallback(ztGuiItem *editor, ZT_FUNCTION_POINTER_VAR(function_id, zt_guiEditorValueChanged_Func), void *user_data)
{
	ZT_PROFILE_GUI("zt_guiEditorSetCallback");

	zt_assertReturnOnFail(editor->type == ztGuiItemType_Panel && editor->first_child);

	if (zt_strEquals(editor->first_child->name, ztGuiEditorFirstChildName)) {
		ztGuiEditorValue *vptr = (ztGuiEditorValue*)editor->panel.user_data;
		zt_assertReturnOnFail(vptr != nullptr);

		vptr->func_val_changed = function_id;
		vptr->func_val_changed_user_data = user_data;
	}
	else {
		ztGuiItem *sizer = zt_guiItemFindByType(ztGuiItemType_Sizer, editor->first_child);
		zt_assertReturnOnFail(sizer != nullptr);
		zt_flinknext(edit, sizer->first_child, sib_next) {
			if (edit->type == ztGuiItemType_Panel && edit->first_child && zt_strEquals(edit->first_child->name, ztGuiEditorFirstChildName)) {
				zt_guiEditorSetCallback(edit, function_id, user_data);
			}
		}
	}
	return;

}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztParticleVariableRealEditor
{
	ztParticleVariableReal *variable;
	ztParticleVariableReal  variable_compare;

	ztGuiItem *ed_constant;

	ztGuiItem *ed_random_value_panel;
	ztGuiItem *ed_random_value_min;
	ztGuiItem *ed_random_value_max;

	ztGuiItem *ed_curve;

	ztGuiItem *ed_random_curve_panel;
	ztGuiItem *ed_random_curve_min;
	ztGuiItem *ed_random_curve_max;

	r32 min, max, def;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiEditorPartVarRealUpdateGui(ztParticleVariableRealEditor *editor)
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarRealUpdateGui");

	zt_guiItemHide(editor->ed_constant);
	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_curve);
	zt_guiItemHide(editor->ed_random_curve_panel);

	switch (editor->variable->type)
	{
		case ztParticleVariableRealType_Constant: {
			zt_guiItemShow(editor->ed_constant);
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoConstants: {
			zt_guiItemShow(editor->ed_random_value_panel);
		} break;

		case ztParticleVariableRealType_Curve: {
			zt_guiAnimCurveSetLiveValue(editor->ed_curve, &editor->variable->curve);
			zt_guiItemShow(editor->ed_curve);
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoCurves: {
			zt_guiAnimCurveSetLiveValue(editor->ed_random_curve_min, &editor->variable->random_curve_min);
			zt_guiAnimCurveSetLiveValue(editor->ed_random_curve_max, &editor->variable->random_curve_max);
			zt_guiItemShow(editor->ed_random_curve_panel);
		} break;
	}

	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor->ed_constant));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarRealButtonCfgMenu, ZT_FUNC_GUI_MENU_SELECTED(_zt_guiEditorPartVarRealButtonCfgMenu))
{
	ztParticleVariableRealEditor *editor = (ztParticleVariableRealEditor*)user_data;

	editor->variable->type = (ztParticleVariableRealType_Enum)menu_item;
	switch (menu_item)
	{
		case ztParticleVariableRealType_Constant: {
			editor->variable->constant = editor->def;
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoConstants: {
			editor->variable->random_value_min = editor->def;
			editor->variable->random_value_max = editor->def;
		} break;

		case ztParticleVariableRealType_Curve: {
			zt_memSet(&editor->variable->curve, zt_sizeof(ztAnimCurve), 0);
			editor->variable->curve.val_max = 1;
			editor->variable->curve.val_end = 1;
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoCurves: {
			zt_memSet(&editor->variable->random_curve_min, zt_sizeof(ztAnimCurve), 0);
			editor->variable->random_curve_min.val_max = 1;
			editor->variable->random_curve_min.val_end = 1;

			zt_memSet(&editor->variable->random_curve_max, zt_sizeof(ztAnimCurve), 0);
			editor->variable->random_curve_max.val_max = 1;
			editor->variable->random_curve_max.val_end = 1;
		} break;
	}

	_zt_guiEditorPartVarRealUpdateGui(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarRealButtonCfg, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiEditorPartVarRealButtonCfg))
{
	ztParticleVariableRealEditor *editor = (ztParticleVariableRealEditor*)user_data;

	ztGuiItem *menu = zt_guiMakeMenu(nullptr, ztGuiMenuBehaviorFlags_FreeOnClose);

	ztSprite check_sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 995, 1, 7, 12);

	zt_guiMenuAppend(menu, "Constant Value", ztParticleVariableRealType_Constant, editor, editor->variable->type == ztParticleVariableRealType_Constant ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Constants", ztParticleVariableRealType_RandomBetweenTwoConstants, editor, editor->variable->type == ztParticleVariableRealType_RandomBetweenTwoConstants ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Curve", ztParticleVariableRealType_Curve, editor, editor->variable->type == ztParticleVariableRealType_Curve ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Curves", ztParticleVariableRealType_RandomBetweenTwoCurves, editor, editor->variable->type == ztParticleVariableRealType_RandomBetweenTwoCurves ? &check_sprite : nullptr);

	zt_guiMenuSetCallback(menu, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarRealButtonCfgMenu));

	zt_guiMenuPopupAtItem(menu, button, ztAlign_Bottom | ztAlign_Right);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarRealUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiEditorPartVarRealUpdate))
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarRealUpdate");

	ztParticleVariableRealEditor *editor = (ztParticleVariableRealEditor*)user_data;

	if (zt_memCmp(editor->variable, &editor->variable_compare, zt_sizeof(ztParticleVariableReal))) {
		zt_memCpy(&editor->variable_compare, zt_sizeof(ztParticleVariableReal), editor->variable, zt_sizeof(ztParticleVariableReal));
		_zt_guiEditorPartVarRealUpdateGui(editor);
	}
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, ztParticleVariableReal *variable, r32 def, r32 min, r32 max, r32 step)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztParticleVariableRealEditor *editor = zt_mallocStructArena(ztParticleVariableRealEditor, panel->gm->arena);

	panel->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarRealUpdate);
	panel->functions.user_data = editor;

	editor->variable = variable;
	editor->min = min;
	editor->max = max;
	editor->def = def;

	ztGuiItem *sizer_width = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz, false);
	zt_guiSizerSizeParent(sizer_width, false, true);
	zt_guiSizerSizeToParent(sizer_width);

	ztGuiItem *sizer_main = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiSizerAddItem(sizer_width, sizer_main, 1, 0);

	editor->ed_constant = zt_guiMakeEditor(panel, nullptr, &variable->constant, min, max, step);
	zt_guiSizerAddItem(sizer_main, editor->ed_constant, 0, 0);

	r32 padding = 3 / zt_pixelsPerUnit();

	editor->ed_random_value_panel = zt_guiMakePanel(panel, 0, editor, panel->gm->arena);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_value_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_value_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_min = zt_guiMakeEditor(sizer, nullptr, &variable->random_value_min, min, max, step);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_max = zt_guiMakeEditor(sizer, nullptr, &variable->random_value_max, min, max, step);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_max, 1, 0);
	}

	editor->ed_curve = zt_guiMakeAnimCurve(panel, &variable->curve, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->curve);
	zt_guiSizerAddItem(sizer_main, editor->ed_curve, 0, 0);

	editor->ed_random_curve_panel = zt_guiMakePanel(panel, 0);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_curve_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_curve_min = zt_guiMakeAnimCurve(sizer, &variable->random_curve_min, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->random_curve_min);
		zt_guiSizerAddItem(sizer, editor->ed_random_curve_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_curve_max = zt_guiMakeAnimCurve(sizer, &variable->random_curve_max, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->random_curve_max);
		zt_guiSizerAddItem(sizer, editor->ed_random_curve_max, 1, 0);
	}

	ztGuiItem *button = zt_guiMakeButton(panel, nullptr, ztGuiButtonBehaviorFlags_NoBackground);
	ztSprite sprite_cfg = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 979, 2, 9, 9);
	zt_guiButtonSetIcon(button, &sprite_cfg);
	zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarRealButtonCfg), editor);
	zt_guiSizerAddItem(sizer_width, button, 0, 0, ztAlign_Top, ztAnchor_Top);

	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_curve);
	zt_guiItemHide(editor->ed_random_curve_panel);

	return panel;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztParticleVariableColorEditor
{
	ztParticleVariableColor *variable;
	ztParticleVariableColor  variable_compare;

	ztGuiItem *ed_constant;

	ztGuiItem *ed_random_value_panel;
	ztGuiItem *ed_random_value_min;
	ztGuiItem *ed_random_value_max;

	ztGuiItem *ed_gradient;

	ztGuiItem *ed_random_gradient_panel;
	ztGuiItem *ed_random_gradient_min;
	ztGuiItem *ed_random_gradient_max;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiEditorPartVarColorInitGradient(ztColorGradient2 *gradient)
{
	zt_memSet(gradient, zt_sizeof(ztColorGradient2), 0);
	gradient->alpha_locs[0] = 0;
	gradient->alpha_vals[0] = 0;
	gradient->alpha_locs[1] = .1f;
	gradient->alpha_vals[1] = 1;
	gradient->alpha_locs[2] = .9f;
	gradient->alpha_vals[2] = 1;
	gradient->alpha_locs[3] = 1;
	gradient->alpha_vals[3] = 0;
	gradient->alpha_entries = 4;

	gradient->color_locs[0] = 0;
	gradient->color_vals[0] = ztColor_White;
	gradient->color_locs[1] = 1;
	gradient->color_vals[1] = ztColor_White;
	gradient->color_entries = 2;
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiEditorPartVarColorUpdateGui(ztParticleVariableColorEditor *editor)
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarColorUpdateGui");

	zt_guiItemHide(editor->ed_constant);
	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_gradient);
	zt_guiItemHide(editor->ed_random_gradient_panel);

	switch (editor->variable->type)
	{
		case ztParticleVariableColorType_Constant: {
			zt_guiItemShow(editor->ed_constant);
			zt_guiColorPickerSetLiveValue(editor->ed_constant, &editor->variable->constant);
		} break;

		case ztParticleVariableColorType_RandomBetweenTwoConstants: {
			zt_guiItemShow(editor->ed_random_value_panel);
			zt_guiColorPickerSetLiveValue(editor->ed_random_value_min, &editor->variable->random_value_min);
			zt_guiColorPickerSetLiveValue(editor->ed_random_value_max, &editor->variable->random_value_max);
		} break;

		case ztParticleVariableColorType_Gradient: {
			zt_guiGradientPickerSetLiveValue(editor->ed_gradient, &editor->variable->gradient);
			zt_guiItemShow(editor->ed_gradient);
		} break;

		case ztParticleVariableColorType_RandomBetweenTwoGradients: {
			zt_guiGradientPickerSetLiveValue(editor->ed_random_gradient_min, &editor->variable->random_gradient_min);
			zt_guiGradientPickerSetLiveValue(editor->ed_random_gradient_max, &editor->variable->random_gradient_max);
			zt_guiItemShow(editor->ed_random_gradient_panel);
		} break;
	}

	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor->ed_constant));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarColorButtonCfgMenu, ZT_FUNC_GUI_MENU_SELECTED(_zt_guiEditorPartVarColorButtonCfgMenu))
{
	ztParticleVariableColorEditor *editor = (ztParticleVariableColorEditor*)user_data;

	editor->variable->type = (ztParticleVariableColorType_Enum)menu_item;
	switch (menu_item)
	{
		case ztParticleVariableColorType_Constant: {
			editor->variable->constant = ztColor_White;
		} break;

		case ztParticleVariableColorType_RandomBetweenTwoConstants: {
			editor->variable->random_value_min = ztColor_White;
			editor->variable->random_value_max = ztColor_White;
		} break;

		case ztParticleVariableColorType_Gradient: {
			_zt_guiEditorPartVarColorInitGradient(&editor->variable->gradient);
		} break;

		case ztParticleVariableColorType_RandomBetweenTwoGradients: {
			_zt_guiEditorPartVarColorInitGradient(&editor->variable->random_gradient_min);
			_zt_guiEditorPartVarColorInitGradient(&editor->variable->random_gradient_max);
		} break;
	}

	_zt_guiEditorPartVarColorUpdateGui(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarColorButtonCfg, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiEditorPartVarColorButtonCfg))
{
	ztParticleVariableColorEditor *editor = (ztParticleVariableColorEditor*)user_data;

	ztGuiItem *menu = zt_guiMakeMenu(nullptr, ztGuiMenuBehaviorFlags_FreeOnClose);

	ztSprite check_sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 995, 1, 7, 12);

	zt_guiMenuAppend(menu, "Constant Color", ztParticleVariableColorType_Constant, editor, editor->variable->type == ztParticleVariableColorType_Constant ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Colors", ztParticleVariableColorType_RandomBetweenTwoConstants, editor, editor->variable->type == ztParticleVariableColorType_RandomBetweenTwoConstants ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Gradient", ztParticleVariableColorType_Gradient, editor, editor->variable->type == ztParticleVariableColorType_Gradient ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Gradients", ztParticleVariableColorType_RandomBetweenTwoGradients, editor, editor->variable->type == ztParticleVariableColorType_RandomBetweenTwoGradients ? &check_sprite : nullptr);

	zt_guiMenuSetCallback(menu, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarColorButtonCfgMenu));

	zt_guiMenuPopupAtItem(menu, button, ztAlign_Bottom | ztAlign_Right);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarColorUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiEditorPartVarColorUpdate))
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarColorUpdate");

	ztParticleVariableColorEditor *editor = (ztParticleVariableColorEditor*)user_data;

	if (zt_memCmp(editor->variable, &editor->variable_compare, zt_sizeof(ztParticleVariableColor))) {
		zt_memCpy(&editor->variable_compare, zt_sizeof(ztParticleVariableColor), editor->variable, zt_sizeof(ztParticleVariableColor));
		_zt_guiEditorPartVarColorUpdateGui(editor);
	}
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, ztParticleVariableColor *variable)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztParticleVariableColorEditor *editor = zt_mallocStructArena(ztParticleVariableColorEditor, panel->gm->arena);

	panel->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarColorUpdate);
	panel->functions.user_data = editor;

	editor->variable = variable;

	ztGuiItem *sizer_width = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz, false);
	zt_guiSizerSizeParent(sizer_width, false, true);
	zt_guiSizerSizeToParent(sizer_width);

	ztGuiItem *sizer_main = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiSizerAddItem(sizer_width, sizer_main, 1, 0);

	editor->ed_constant = zt_guiMakeColorPicker(sizer_main, ztColor_White, ztGuiColorPickerBehaviorFlags_LiveEdit | ztGuiColorPickerBehaviorFlags_IncludesAlpha, &variable->constant);
	zt_guiSizerAddItem(sizer_main, editor->ed_constant, 0, 0);

	r32 padding = 3 / zt_pixelsPerUnit();

	editor->ed_random_value_panel = zt_guiMakePanel(panel, 0, editor, panel->gm->arena);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_value_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_value_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_min = zt_guiMakeColorPicker(sizer, ztColor_White, ztGuiColorPickerBehaviorFlags_LiveEdit | ztGuiColorPickerBehaviorFlags_IncludesAlpha, &variable->random_value_min);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_max = zt_guiMakeColorPicker(sizer, ztColor_White, ztGuiColorPickerBehaviorFlags_LiveEdit | ztGuiColorPickerBehaviorFlags_IncludesAlpha, &variable->random_value_max);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_max, 1, 0);
	}

	editor->ed_gradient = zt_guiMakeGradientPicker(sizer_main, &variable->gradient, ztGuiGradientPickerBehaviorFlags_LiveEdit, &variable->gradient);
	zt_guiSizerAddItem(sizer_main, editor->ed_gradient, 0, 0);

	editor->ed_random_gradient_panel = zt_guiMakePanel(sizer_main, 0);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_gradient_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_gradient_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_gradient_min = zt_guiMakeGradientPicker(sizer_main, &variable->random_gradient_min, ztGuiGradientPickerBehaviorFlags_LiveEdit, &variable->random_gradient_min);
		zt_guiSizerAddItem(sizer, editor->ed_random_gradient_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_gradient_max = zt_guiMakeGradientPicker(sizer_main, &variable->random_gradient_max, ztGuiGradientPickerBehaviorFlags_LiveEdit, &variable->random_gradient_max);
		zt_guiSizerAddItem(sizer, editor->ed_random_gradient_max, 1, 0);
	}

	ztGuiItem *button = zt_guiMakeButton(panel, nullptr, ztGuiButtonBehaviorFlags_NoBackground);
	ztSprite sprite_cfg = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 979, 2, 9, 9);
	zt_guiButtonSetIcon(button, &sprite_cfg);
	zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarColorButtonCfg), editor);
	zt_guiSizerAddItem(sizer_width, button, 0, 0, ztAlign_Top, ztAnchor_Top);

	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_gradient);
	zt_guiItemHide(editor->ed_random_gradient_panel);

	return panel;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztParticleVariableVec2Editor
{
	ztParticleVariableVec2 *variable;
	ztParticleVariableVec2  variable_compare;
	ztParticleVariableReal  unified;

	ztGuiItem *ed_constant;

	ztGuiItem *ed_random_value_panel;
	ztGuiItem *ed_random_value_min;
	ztGuiItem *ed_random_value_max;

	ztGuiItem *ed_curve_panel;
	ztGuiItem *ed_curve[2];

	ztGuiItem *ed_random_curve_panel;
	ztGuiItem *ed_random_curve_min[2];
	ztGuiItem *ed_random_curve_max[2];

	ztGuiItem *ed_unified_constant;

	ztGuiItem *ed_unified_random_value_panel;
	ztGuiItem *ed_unified_random_value_min;
	ztGuiItem *ed_unified_random_value_max;

	ztGuiItem *ed_unified_curve;

	ztGuiItem *ed_unified_random_curve_panel;
	ztGuiItem *ed_unified_random_curve_min;
	ztGuiItem *ed_unified_random_curve_max;

	ztVec2 min, max, def;

	bool is_unified;
	bool allow_sync;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiEditorPartVarVec2UpdateGui(ztParticleVariableVec2Editor *editor)
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarVec2UpdateGui");

	zt_guiItemHide(editor->ed_constant);
	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_curve_panel);
	zt_guiItemHide(editor->ed_random_curve_panel);
	zt_guiItemHide(editor->ed_unified_constant);
	zt_guiItemHide(editor->ed_unified_random_value_panel);
	zt_guiItemHide(editor->ed_unified_curve);
	zt_guiItemHide(editor->ed_unified_random_curve_panel);

	if (editor->is_unified) {
		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->unified.constant = editor->variable->constant.x;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->unified.random_value_min = editor->variable->random_value_min.x;
				editor->unified.random_value_max = editor->variable->random_value_max.x;
			} break;

			case ztParticleVariableRealType_Curve: {
				zt_memCpy(&editor->unified.curve, zt_sizeof(ztAnimCurve), &editor->variable->curve[0], zt_sizeof(ztAnimCurve));
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				zt_memCpy(&editor->unified.random_curve_min, zt_sizeof(ztAnimCurve), &editor->variable->random_curve_min[0], zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->unified.random_curve_max, zt_sizeof(ztAnimCurve), &editor->variable->random_curve_max[0], zt_sizeof(ztAnimCurve));
			} break;
		}
	}

	switch (editor->variable->type)
	{
		case ztParticleVariableRealType_Constant: {
			if (editor->is_unified) {
				zt_guiItemShow(editor->ed_unified_constant);
			}
			else {
				zt_guiItemShow(editor->ed_constant);
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoConstants: {
			if (editor->is_unified) {
				zt_guiItemShow(editor->ed_unified_random_value_panel);
			}
			else {
				zt_guiItemShow(editor->ed_random_value_panel);
			}
		} break;

		case ztParticleVariableRealType_Curve: {
			if (editor->is_unified) {
				zt_guiAnimCurveSetLiveValue(editor->ed_unified_curve, &editor->unified.curve);
				zt_guiItemShow(editor->ed_unified_curve);
			}
			else {
				zt_guiItemShow(editor->ed_curve_panel);

				zt_fiz(2) {
					zt_guiAnimCurveSetLiveValue(editor->ed_curve[i], &editor->variable->curve[i]);
				}
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoCurves: {
			if (editor->is_unified) {
				zt_guiItemShow(editor->ed_unified_random_curve_panel);
				zt_guiAnimCurveSetLiveValue(editor->ed_unified_random_curve_min, &editor->unified.random_curve_min);
				zt_guiAnimCurveSetLiveValue(editor->ed_unified_random_curve_max, &editor->unified.random_curve_max);
			}
			else {
				zt_guiItemShow(editor->ed_random_curve_panel);

				zt_fiz(2) {
					zt_guiAnimCurveSetLiveValue(editor->ed_random_curve_min[i], &editor->variable->random_curve_min[i]);
					zt_guiAnimCurveSetLiveValue(editor->ed_random_curve_max[i], &editor->variable->random_curve_max[i]);
				}
			}
		} break;
	}

	zt_guiSizerRecalcImmediately(zt_guiItemGetTopLevelParent(editor->ed_constant));
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiEditorPartVarVec2UpdateUnified(ztParticleVariableVec2Editor *editor)
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarVec2UpdateUnified");

	if (editor->is_unified) {
		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->unified.constant = editor->variable->constant.x;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->unified.random_value_min = editor->variable->random_value_min.x;
				editor->unified.random_value_max = editor->variable->random_value_max.x;
			} break;

			case ztParticleVariableRealType_Curve: {
				zt_memCpy(&editor->unified.curve, zt_sizeof(ztAnimCurve), &editor->variable->curve[0], zt_sizeof(ztAnimCurve));
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				zt_memCpy(&editor->unified.random_curve_min, zt_sizeof(ztAnimCurve), &editor->variable->random_curve_min[0], zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->unified.random_curve_max, zt_sizeof(ztAnimCurve), &editor->variable->random_curve_max[0], zt_sizeof(ztAnimCurve));
			} break;
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarVec2ButtonCfgMenu, ZT_FUNC_GUI_MENU_SELECTED(_zt_guiEditorPartVarVec2ButtonCfgMenu))
{
	ztParticleVariableVec2Editor *editor = (ztParticleVariableVec2Editor*)user_data;

	if (menu_item == ztParticleVariableRealType_MAX) {
		editor->is_unified = !editor->is_unified;
		menu_item = editor->variable->type;
		_zt_guiEditorPartVarVec2UpdateUnified(editor);
	}

	bool matched = editor->variable->type == (ztParticleVariableRealType_Enum)menu_item;
	editor->variable->type = (ztParticleVariableRealType_Enum)menu_item;
	switch (menu_item)
	{
		case ztParticleVariableRealType_Constant: {
			if (editor->is_unified) {
				if (!matched) editor->unified.constant = editor->def.x;
			}
			else {
				if (!matched) {
					editor->variable->constant = editor->def;
				}
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoConstants: {
			if (editor->is_unified) {
				if (!matched) {
					editor->unified.random_value_min = editor->def.x;
					editor->unified.random_value_max = editor->def.x;
				}
			}
			else {
				if (!matched) {
					editor->variable->random_value_min = editor->def;
					editor->variable->random_value_max = editor->def;
				}
			}
		} break;

		case ztParticleVariableRealType_Curve: {
			if (editor->is_unified) {
				if (!matched) {
					zt_memSet(&editor->unified.curve, zt_sizeof(ztAnimCurve), 0);
					editor->unified.curve.val_max = 1;
					editor->unified.curve.val_end = 1;
				}
			}
			else {
				if (!matched) {
					zt_fiz(2) {
						zt_memSet(&editor->variable->curve[i], zt_sizeof(ztAnimCurve), 0);
						editor->variable->curve[i].val_max = 1;
						editor->variable->curve[i].val_end = 1;
					}
				}
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoCurves: {
			if (editor->is_unified) {
				if (!matched) {
					zt_memSet(&editor->unified.random_curve_min, zt_sizeof(ztAnimCurve), 0);
					editor->unified.random_curve_min.val_max = 1;
					editor->unified.random_curve_min.val_end = 1;

					zt_memSet(&editor->unified.random_curve_max, zt_sizeof(ztAnimCurve), 0);
					editor->unified.random_curve_max.val_max = 1;
					editor->unified.random_curve_max.val_end = 1;
				}
			}
			else {
				if (!matched) {
					zt_fiz(2) {
						zt_memSet(&editor->variable->random_curve_min[i], zt_sizeof(ztAnimCurve), 0);
						editor->variable->random_curve_min[i].val_max = 1;
						editor->variable->random_curve_min[i].val_end = 1;

						zt_memSet(&editor->variable->random_curve_max[i], zt_sizeof(ztAnimCurve), 0);
						editor->variable->random_curve_max[i].val_max = 1;
						editor->variable->random_curve_max[i].val_end = 1;
					}
				}
			}
		} break;
	}

	_zt_guiEditorPartVarVec2UpdateGui(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarVec2ButtonCfg, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiEditorPartVarVec2ButtonCfg))
{
	ztParticleVariableVec2Editor *editor = (ztParticleVariableVec2Editor*)user_data;

	ztGuiItem *menu = zt_guiMakeMenu(nullptr, ztGuiMenuBehaviorFlags_FreeOnClose);

	ztSprite check_sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 995, 1, 7, 12);

	zt_guiMenuAppend(menu, "Constant Value", ztParticleVariableRealType_Constant, editor, editor->variable->type == ztParticleVariableRealType_Constant ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Constants", ztParticleVariableRealType_RandomBetweenTwoConstants, editor, editor->variable->type == ztParticleVariableRealType_RandomBetweenTwoConstants ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Curve", ztParticleVariableRealType_Curve, editor, editor->variable->type == ztParticleVariableRealType_Curve ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Curves", ztParticleVariableRealType_RandomBetweenTwoCurves, editor, editor->variable->type == ztParticleVariableRealType_RandomBetweenTwoCurves ? &check_sprite : nullptr);

	if (editor->allow_sync) {
		zt_guiMenuAppendSeparator(menu);
		zt_guiMenuAppend(menu, "Synchronize Values", ztParticleVariableRealType_MAX, editor, editor->is_unified ? &check_sprite : nullptr);
	}

	zt_guiMenuSetCallback(menu, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarVec2ButtonCfgMenu));

	zt_guiMenuPopupAtItem(menu, button, ztAlign_Bottom | ztAlign_Right);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarVec2Update, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiEditorPartVarVec2Update))
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarVec2Update");

	ztParticleVariableVec2Editor *editor = (ztParticleVariableVec2Editor*)user_data;

	if (zt_memCmp(editor->variable, &editor->variable_compare, zt_sizeof(ztParticleVariableVec2))) {
		zt_memCpy(&editor->variable_compare, zt_sizeof(ztParticleVariableVec2), editor->variable, zt_sizeof(ztParticleVariableVec2));

		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->is_unified = zt_real32Eq(editor->variable->constant.x, editor->variable->constant.y);
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->is_unified = zt_real32Eq(editor->variable->random_value_min.x, editor->variable->random_value_min.y) &&
					zt_real32Eq(editor->variable->random_value_max.x, editor->variable->random_value_max.y);
			} break;

			case ztParticleVariableRealType_Curve: {
				editor->is_unified = zt_memCmp(&editor->variable->curve[0], &editor->variable->curve[1], zt_sizeof(ztAnimCurve)) == 0;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				editor->is_unified = zt_memCmp(&editor->variable->random_curve_min[0], &editor->variable->random_curve_min[1], zt_sizeof(ztAnimCurve)) == 0 &&
					zt_memCmp(&editor->variable->random_curve_max[0], &editor->variable->random_curve_max[1], zt_sizeof(ztAnimCurve)) == 0;
			} break;
		}

		_zt_guiEditorPartVarVec2UpdateUnified(editor);
		_zt_guiEditorPartVarVec2UpdateGui(editor);
	}

	if (editor->is_unified) {
		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->variable->constant.x = editor->unified.constant;
				editor->variable->constant.y = editor->unified.constant;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->variable->random_value_min.x = editor->unified.random_value_min;
				editor->variable->random_value_min.y = editor->unified.random_value_min;
				editor->variable->random_value_max.x = editor->unified.random_value_max;
				editor->variable->random_value_max.y = editor->unified.random_value_max;
			} break;

			case ztParticleVariableRealType_Curve: {
				zt_memCpy(&editor->variable->curve[0], zt_sizeof(ztAnimCurve), &editor->unified.curve, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->curve[1], zt_sizeof(ztAnimCurve), &editor->unified.curve, zt_sizeof(ztAnimCurve));
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				zt_memCpy(&editor->variable->random_curve_min[0], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_min, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_min[1], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_min, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_max[0], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_max, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_max[1], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_max, zt_sizeof(ztAnimCurve));
			} break;
		}
	}
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, ztParticleVariableVec2 *variable, ztVec2 def, ztVec2 min, ztVec2 max, r32 step, bool allow_sync)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztParticleVariableVec2Editor *editor = zt_mallocStructArena(ztParticleVariableVec2Editor, panel->gm->arena);

	editor->variable = variable;
	editor->min = min;
	editor->max = max;
	editor->def = def;
	editor->allow_sync = allow_sync;

	panel->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarVec2Update);
	panel->functions.user_data = editor;

	ztGuiItem *sizer_width = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz, false);
	zt_guiSizerSizeParent(sizer_width, false, true);
	zt_guiSizerSizeToParent(sizer_width);

	ztGuiItem *sizer_main = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiSizerAddItem(sizer_width, sizer_main, 1, 0);

	editor->ed_constant = zt_guiMakeEditor(panel, nullptr, &variable->constant, min, max, step);
	zt_guiSizerAddItem(sizer_main, editor->ed_constant, 0, 0);

	r32 padding = 3 / zt_pixelsPerUnit();

	editor->ed_random_value_panel = zt_guiMakePanel(panel, 0, editor, panel->gm->arena);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_value_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_value_panel, ztGuiItemOrient_Vert);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		//zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_min = zt_guiMakeEditor(sizer, "Min:", &variable->random_value_min, min, max, step, false);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_min, 1, 0);

		//zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_max = zt_guiMakeEditor(sizer, "Max:", &variable->random_value_max, min, max, step, false);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_max, 1, 0);
	}

	editor->ed_curve_panel = zt_guiMakePanel(panel);
	zt_guiSizerAddItem(sizer_main, editor->ed_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_curve_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		const char *labels[] = { "X:", "Y:", "Z:" };
		zt_fiz(3) {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, labels[i]), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->ed_curve[i] = zt_guiMakeAnimCurve(sizer, &variable->curve[i], ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->curve[i]);
			editor->ed_curve[i]->size.x = .75f;
			zt_guiSizerAddItem(sizer, editor->ed_curve[i], 1, padding);
		}
	}

	editor->ed_random_curve_panel = zt_guiMakePanel(panel, 0);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_curve_panel, ztGuiItemOrient_Vert);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		ztGuiItem *sizer_min = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, sizer_min, 0, 0);

		const char *labels[] = { "X:", "Y:", "Z:" };
		zt_fiz(3) {
			zt_guiSizerAddItem(sizer_min, zt_guiMakeStaticText(sizer_min, labels[i]), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->ed_random_curve_min[i] = zt_guiMakeAnimCurve(sizer_min, &variable->random_curve_min[i], ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->random_curve_min[i]);
			editor->ed_random_curve_min[i]->size.x = .75f;
			zt_guiSizerAddItem(sizer_min, editor->ed_random_curve_min[i], 1, 0);
		}

		zt_guiSizerAddStretcher(sizer, 0, padding * 3);

		ztGuiItem *sizer_max = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, sizer_max, 0, 0);

		zt_fiz(3) {
			zt_guiSizerAddItem(sizer_max, zt_guiMakeStaticText(sizer_max, labels[i]), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->ed_random_curve_max[i] = zt_guiMakeAnimCurve(sizer_max, &variable->random_curve_max[i], ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->random_curve_max[i]);
			editor->ed_random_curve_min[i]->size.x = .75f;
			zt_guiSizerAddItem(sizer_max, editor->ed_random_curve_max[i], 1, 0);
		}
	}

	editor->ed_unified_constant = zt_guiMakeEditor(panel, nullptr, &editor->unified.constant, min.x, max.x, step);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_constant, 0, 0);


	editor->ed_unified_random_value_panel = zt_guiMakePanel(panel);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_random_value_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_unified_random_value_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_value_min = zt_guiMakeEditor(sizer, nullptr, &editor->unified.random_value_min, min.x, max.x, step);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_value_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_value_max = zt_guiMakeEditor(sizer, nullptr, &editor->unified.random_value_max, min.x, max.x, step);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_value_max, 1, 0);
	}

	editor->ed_unified_curve = zt_guiMakeAnimCurve(panel, &editor->unified.curve, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &editor->unified.curve);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_curve, 0, 0);

	editor->ed_unified_random_curve_panel = zt_guiMakePanel(panel, 0);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_random_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_unified_random_curve_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_curve_min = zt_guiMakeAnimCurve(sizer, &editor->unified.random_curve_min, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &editor->unified.random_curve_min);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_curve_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_curve_max = zt_guiMakeAnimCurve(sizer, &editor->unified.random_curve_max, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &editor->unified.random_curve_max);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_curve_max, 1, 0);
	}


	ztGuiItem *button = zt_guiMakeButton(panel, nullptr, ztGuiButtonBehaviorFlags_NoBackground);
	ztSprite sprite_cfg = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 979, 2, 9, 9);
	zt_guiButtonSetIcon(button, &sprite_cfg);
	zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarVec2ButtonCfg), editor);
	zt_guiSizerAddItem(sizer_width, button, 0, 0, ztAlign_Top, ztAnchor_Top);

	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_curve_panel);
	zt_guiItemHide(editor->ed_random_curve_panel);
	zt_guiItemHide(editor->ed_unified_constant);
	zt_guiItemHide(editor->ed_unified_random_value_panel);
	zt_guiItemHide(editor->ed_unified_curve);
	zt_guiItemHide(editor->ed_unified_random_curve_panel);

	return panel;
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztParticleVariableVec3Editor
{
	ztParticleVariableVec3 *variable;
	ztParticleVariableVec3  variable_compare;
	ztParticleVariableReal  unified;

	ztGuiItem *ed_constant;

	ztGuiItem *ed_random_value_panel;
	ztGuiItem *ed_random_value_min;
	ztGuiItem *ed_random_value_max;

	ztGuiItem *ed_curve_panel;
	ztGuiItem *ed_curve[3];

	ztGuiItem *ed_random_curve_panel;
	ztGuiItem *ed_random_curve_min[3];
	ztGuiItem *ed_random_curve_max[3];

	ztGuiItem *ed_unified_constant;

	ztGuiItem *ed_unified_random_value_panel;
	ztGuiItem *ed_unified_random_value_min;
	ztGuiItem *ed_unified_random_value_max;

	ztGuiItem *ed_unified_curve;

	ztGuiItem *ed_unified_random_curve_panel;
	ztGuiItem *ed_unified_random_curve_min;
	ztGuiItem *ed_unified_random_curve_max;

	ztVec3 min, max, def;

	bool is_unified;
	bool allow_sync;
};

// ================================================================================================================================================================================================

void _zt_guiEditorPartVarVec3UpdateGui(ztParticleVariableVec3Editor *editor)
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarVec3UpdateGui");

	zt_guiItemHide(editor->ed_constant);
	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_curve_panel);
	zt_guiItemHide(editor->ed_random_curve_panel);
	zt_guiItemHide(editor->ed_unified_constant);
	zt_guiItemHide(editor->ed_unified_random_value_panel);
	zt_guiItemHide(editor->ed_unified_curve);
	zt_guiItemHide(editor->ed_unified_random_curve_panel);

	switch (editor->variable->type)
	{
		case ztParticleVariableRealType_Constant: {
			if (editor->is_unified) {
				zt_guiItemShow(editor->ed_unified_constant);
			}
			else {
				zt_guiItemShow(editor->ed_constant);
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoConstants: {
			if (editor->is_unified) {
				zt_guiItemShow(editor->ed_unified_random_value_panel);
			}
			else {
				zt_guiItemShow(editor->ed_random_value_panel);
			}
		} break;

		case ztParticleVariableRealType_Curve: {
			if (editor->is_unified) {
				zt_guiAnimCurveSetLiveValue(editor->ed_unified_curve, &editor->unified.curve);

				zt_guiItemShow(editor->ed_unified_curve);
			}
			else {
				zt_guiItemShow(editor->ed_curve_panel);

				zt_fiz(3) {
					zt_guiAnimCurveSetLiveValue(editor->ed_curve[i], &editor->variable->curve[i]);
				}
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoCurves: {
			if (editor->is_unified) {
				zt_guiItemShow(editor->ed_unified_random_curve_panel);
				zt_guiAnimCurveSetLiveValue(editor->ed_unified_random_curve_min, &editor->unified.random_curve_min);
				zt_guiAnimCurveSetLiveValue(editor->ed_unified_random_curve_max, &editor->unified.random_curve_max);
			}
			else {
				zt_guiItemShow(editor->ed_random_curve_panel);

				zt_fiz(3) {
					zt_guiAnimCurveSetLiveValue(editor->ed_random_curve_min[i], &editor->variable->random_curve_min[i]);
					zt_guiAnimCurveSetLiveValue(editor->ed_random_curve_max[i], &editor->variable->random_curve_max[i]);
				}
			}
		} break;
	}

	zt_guiSizerRecalcImmediately(zt_guiItemGetTopLevelParent(editor->ed_constant));
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiEditorPartVarVec3UpdateUnified(ztParticleVariableVec3Editor *editor)
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarVec3UpdateUnified");

	if (editor->is_unified) {
		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->unified.constant = editor->variable->constant.x;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->unified.random_value_min = editor->variable->random_value_min.x;
				editor->unified.random_value_max = editor->variable->random_value_max.x;
			} break;

			case ztParticleVariableRealType_Curve: {
				zt_memCpy(&editor->unified.curve, zt_sizeof(ztAnimCurve), &editor->variable->curve[0], zt_sizeof(ztAnimCurve));
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				zt_memCpy(&editor->unified.random_curve_min, zt_sizeof(ztAnimCurve), &editor->variable->random_curve_min[0], zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->unified.random_curve_max, zt_sizeof(ztAnimCurve), &editor->variable->random_curve_max[0], zt_sizeof(ztAnimCurve));
			} break;
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarVec3ButtonCfgMenu, ZT_FUNC_GUI_MENU_SELECTED(_zt_guiEditorPartVarVec3ButtonCfgMenu))
{
	ztParticleVariableVec3Editor *editor = (ztParticleVariableVec3Editor*)user_data;

	if (menu_item == ztParticleVariableRealType_MAX) {
		editor->is_unified = !editor->is_unified;
		menu_item = editor->variable->type;
		_zt_guiEditorPartVarVec3UpdateUnified(editor);
	}

	bool matched = editor->variable->type == (ztParticleVariableRealType_Enum)menu_item;
	editor->variable->type = (ztParticleVariableRealType_Enum)menu_item;
	switch (menu_item)
	{
		case ztParticleVariableRealType_Constant: {
			if (editor->is_unified) {
				if (!matched) editor->unified.constant = editor->def.x;
			}
			else {
				if (!matched) {
					editor->variable->constant = editor->def;
				}
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoConstants: {
			if (editor->is_unified) {
				if (!matched) {
					editor->unified.random_value_min = editor->def.x;
					editor->unified.random_value_max = editor->def.x;
				}
			}
			else {
				if (!matched) {
					editor->variable->random_value_min = editor->def;
					editor->variable->random_value_max = editor->def;
				}
			}
		} break;

		case ztParticleVariableRealType_Curve: {
			if (editor->is_unified) {
				if (!matched) {
					zt_memSet(&editor->unified.curve, zt_sizeof(ztAnimCurve), 0);
					editor->unified.curve.val_max = 1;
					editor->unified.curve.val_end = 1;
				}
			}
			else {
				if (!matched) {
					zt_fiz(3) {
						zt_memSet(&editor->variable->curve[i], zt_sizeof(ztAnimCurve), 0);
						editor->variable->curve[i].val_max = 1;
						editor->variable->curve[i].val_end = 1;
					}
				}
			}
		} break;

		case ztParticleVariableRealType_RandomBetweenTwoCurves: {
			if (editor->is_unified) {
				if (!matched) {
					zt_memSet(&editor->unified.random_curve_min, zt_sizeof(ztAnimCurve), 0);
					editor->unified.random_curve_min.val_max = 1;
					editor->unified.random_curve_min.val_end = 1;

					zt_memSet(&editor->unified.random_curve_max, zt_sizeof(ztAnimCurve), 0);
					editor->unified.random_curve_max.val_max = 1;
					editor->unified.random_curve_max.val_end = 1;
				}
			}
			else {
				if (!matched) {
					zt_fiz(3) {
						zt_memSet(&editor->variable->random_curve_min[i], zt_sizeof(ztAnimCurve), 0);
						editor->variable->random_curve_min[i].val_max = 1;
						editor->variable->random_curve_min[i].val_end = 1;

						zt_memSet(&editor->variable->random_curve_max[i], zt_sizeof(ztAnimCurve), 0);
						editor->variable->random_curve_max[i].val_max = 1;
						editor->variable->random_curve_max[i].val_end = 1;
					}
				}
			}
		} break;
	}

	_zt_guiEditorPartVarVec3UpdateGui(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarVec3ButtonCfg, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiEditorPartVarVec3ButtonCfg))
{
	ztParticleVariableVec3Editor *editor = (ztParticleVariableVec3Editor*)user_data;

	ztGuiItem *menu = zt_guiMakeMenu(nullptr, ztGuiMenuBehaviorFlags_FreeOnClose);

	ztSprite check_sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 995, 1, 7, 12);

	zt_guiMenuAppend(menu, "Constant Value", ztParticleVariableRealType_Constant, editor, editor->variable->type == ztParticleVariableRealType_Constant ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Constants", ztParticleVariableRealType_RandomBetweenTwoConstants, editor, editor->variable->type == ztParticleVariableRealType_RandomBetweenTwoConstants ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Curve", ztParticleVariableRealType_Curve, editor, editor->variable->type == ztParticleVariableRealType_Curve ? &check_sprite : nullptr);
	zt_guiMenuAppend(menu, "Random Between Two Curves", ztParticleVariableRealType_RandomBetweenTwoCurves, editor, editor->variable->type == ztParticleVariableRealType_RandomBetweenTwoCurves ? &check_sprite : nullptr);

	if (editor->allow_sync) {
		zt_guiMenuAppendSeparator(menu);
		zt_guiMenuAppend(menu, "Synchronize Values", ztParticleVariableRealType_MAX, editor, editor->is_unified ? &check_sprite : nullptr);
	}


	zt_guiMenuSetCallback(menu, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarVec3ButtonCfgMenu));

	zt_guiMenuPopupAtItem(menu, button, ztAlign_Bottom | ztAlign_Right);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiEditorPartVarVec3Update, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiEditorPartVarVec3Update))
{
	ZT_PROFILE_GUI("_zt_guiEditorPartVarVec3Update");

	ztParticleVariableVec3Editor *editor = (ztParticleVariableVec3Editor*)user_data;

	if (zt_memCmp(editor->variable, &editor->variable_compare, zt_sizeof(ztParticleVariableVec3))) {
		zt_memCpy(&editor->variable_compare, zt_sizeof(ztParticleVariableVec3), editor->variable, zt_sizeof(ztParticleVariableVec3));

		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->is_unified = zt_real32Eq(editor->variable->constant.x, editor->variable->constant.y) && zt_real32Eq(editor->variable->constant.x, editor->variable->constant.z);
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->is_unified = zt_real32Eq(editor->variable->random_value_min.x, editor->variable->random_value_min.y) &&
					zt_real32Eq(editor->variable->random_value_min.y, editor->variable->random_value_min.z) &&
					zt_real32Eq(editor->variable->random_value_max.x, editor->variable->random_value_max.y) &&
					zt_real32Eq(editor->variable->random_value_max.y, editor->variable->random_value_max.z);
			} break;

			case ztParticleVariableRealType_Curve: {
				editor->is_unified = zt_memCmp(&editor->variable->curve[0], &editor->variable->curve[1], zt_sizeof(ztAnimCurve)) == 0 && zt_memCmp(&editor->variable->curve[1], &editor->variable->curve[2], zt_sizeof(ztAnimCurve)) == 0;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				editor->is_unified = zt_memCmp(&editor->variable->random_curve_min[0], &editor->variable->random_curve_min[1], zt_sizeof(ztAnimCurve)) == 0 && zt_memCmp(&editor->variable->random_curve_min[1], &editor->variable->random_curve_min[2], zt_sizeof(ztAnimCurve)) == 0 &&
					zt_memCmp(&editor->variable->random_curve_max[0], &editor->variable->random_curve_max[1], zt_sizeof(ztAnimCurve)) == 0 && zt_memCmp(&editor->variable->random_curve_max[1], &editor->variable->random_curve_max[2], zt_sizeof(ztAnimCurve)) == 0;
			} break;
		}

		_zt_guiEditorPartVarVec3UpdateUnified(editor);
		_zt_guiEditorPartVarVec3UpdateGui(editor);
	}	if (editor->is_unified) {
		switch (editor->variable->type)
		{
			case ztParticleVariableRealType_Constant: {
				editor->variable->constant.x = editor->unified.constant;
				editor->variable->constant.y = editor->unified.constant;
				editor->variable->constant.z = editor->unified.constant;
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoConstants: {
				editor->variable->random_value_min.x = editor->unified.random_value_min;
				editor->variable->random_value_min.y = editor->unified.random_value_min;
				editor->variable->random_value_min.z = editor->unified.random_value_min;
				editor->variable->random_value_max.x = editor->unified.random_value_max;
				editor->variable->random_value_max.y = editor->unified.random_value_max;
				editor->variable->random_value_max.z = editor->unified.random_value_max;
			} break;

			case ztParticleVariableRealType_Curve: {
				zt_memCpy(&editor->variable->curve[0], zt_sizeof(ztAnimCurve), &editor->unified.curve, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->curve[1], zt_sizeof(ztAnimCurve), &editor->unified.curve, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->curve[2], zt_sizeof(ztAnimCurve), &editor->unified.curve, zt_sizeof(ztAnimCurve));
			} break;

			case ztParticleVariableRealType_RandomBetweenTwoCurves: {
				zt_memCpy(&editor->variable->random_curve_min[0], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_min, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_min[1], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_min, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_min[2], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_min, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_max[0], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_max, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_max[1], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_max, zt_sizeof(ztAnimCurve));
				zt_memCpy(&editor->variable->random_curve_max[2], zt_sizeof(ztAnimCurve), &editor->unified.random_curve_max, zt_sizeof(ztAnimCurve));
			} break;
		}
	}
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeEditor(ztGuiItem *parent, ztParticleVariableVec3 *variable, ztVec3 def, ztVec3 min, ztVec3 max, r32 step, bool allow_sync)
{
	ZT_PROFILE_GUI("zt_guiMakeEditor");

	ztGuiItem *panel = zt_guiMakePanel(parent);
	ztParticleVariableVec3Editor *editor = zt_mallocStructArena(ztParticleVariableVec3Editor, panel->gm->arena);

	editor->variable = variable;
	editor->min = min;
	editor->max = max;
	editor->def = def;
	editor->allow_sync = allow_sync;

	panel->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarVec3Update);
	panel->functions.user_data = editor;

	ztGuiItem *sizer_width = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz, false);
	zt_guiSizerSizeParent(sizer_width, false, true);
	zt_guiSizerSizeToParent(sizer_width);

	ztGuiItem *sizer_main = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert);
	zt_guiSizerAddItem(sizer_width, sizer_main, 1, 0);

	editor->ed_constant = zt_guiMakeEditor(panel, nullptr, &variable->constant, min, max, step);
	zt_guiSizerAddItem(sizer_main, editor->ed_constant, 0, 0);

	r32 padding = 3 / zt_pixelsPerUnit();

	editor->ed_random_value_panel = zt_guiMakePanel(panel, 0, editor, panel->gm->arena);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_value_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_value_panel, ztGuiItemOrient_Vert);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		//zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_min = zt_guiMakeEditor(sizer, "Min:", &variable->random_value_min, min, max, step, false);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_min, 1, 0);

		//zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_random_value_max = zt_guiMakeEditor(sizer, "Max:", &variable->random_value_max, min, max, step, false);
		zt_guiSizerAddItem(sizer, editor->ed_random_value_max, 1, 0);
	}

	editor->ed_curve_panel = zt_guiMakePanel(panel);
	zt_guiSizerAddItem(sizer_main, editor->ed_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_curve_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		const char *labels[] = { "X:", "Y:", "Z:" };
		zt_fiz(3) {
			zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, labels[i]), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->ed_curve[i] = zt_guiMakeAnimCurve(sizer, &variable->curve[i], ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->curve[i]);
			editor->ed_curve[i]->size.x = .75f;
			zt_guiSizerAddItem(sizer, editor->ed_curve[i], 1, padding);
		}
	}

	editor->ed_random_curve_panel = zt_guiMakePanel(panel, 0);
	zt_guiSizerAddItem(sizer_main, editor->ed_random_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_random_curve_panel, ztGuiItemOrient_Vert);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		ztGuiItem *sizer_min = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, sizer_min, 0, 0);

		const char *labels[] = { "X:", "Y:", "Z:" };
		zt_fiz(3) {
			zt_guiSizerAddItem(sizer_min, zt_guiMakeStaticText(sizer_min, labels[i]), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->ed_random_curve_min[i] = zt_guiMakeAnimCurve(sizer_min, &variable->random_curve_min[i], ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->random_curve_min[i]);
			editor->ed_random_curve_min[i]->size.x = .75f;
			zt_guiSizerAddItem(sizer_min, editor->ed_random_curve_min[i], 1, 0);
		}

		zt_guiSizerAddStretcher(sizer, 0, padding * 3);

		ztGuiItem *sizer_max = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, sizer_max, 0, 0);

		zt_fiz(3) {
			zt_guiSizerAddItem(sizer_max, zt_guiMakeStaticText(sizer_max, labels[i]), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->ed_random_curve_max[i] = zt_guiMakeAnimCurve(sizer_max, &variable->random_curve_max[i], ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &variable->random_curve_max[i]);
			editor->ed_random_curve_min[i]->size.x = .75f;
			zt_guiSizerAddItem(sizer_max, editor->ed_random_curve_max[i], 1, 0);
		}
	}

	editor->ed_unified_constant = zt_guiMakeEditor(panel, nullptr, &editor->unified.constant, min.x, max.x, step);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_constant, 0, 0);


	editor->ed_unified_random_value_panel = zt_guiMakePanel(panel);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_random_value_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_unified_random_value_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_value_min = zt_guiMakeEditor(sizer, nullptr, &editor->unified.random_value_min, min.x, max.x, step);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_value_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_value_max = zt_guiMakeEditor(sizer, nullptr, &editor->unified.random_value_max, min.x, max.x, step);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_value_max, 1, 0);
	}

	editor->ed_unified_curve = zt_guiMakeAnimCurve(panel, &editor->unified.curve, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &editor->unified.curve);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_curve, 0, 0);

	editor->ed_unified_random_curve_panel = zt_guiMakePanel(panel, 0);
	zt_guiSizerAddItem(sizer_main, editor->ed_unified_random_curve_panel, 0, 0);
	{
		ztGuiItem *sizer = zt_guiMakeSizer(editor->ed_unified_random_curve_panel, ztGuiItemOrient_Horz);
		zt_guiSizerSizeParent(sizer, false, true);
		zt_guiSizerSizeToParent(sizer);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Min:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_curve_min = zt_guiMakeAnimCurve(sizer, &editor->unified.random_curve_min, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &editor->unified.random_curve_min);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_curve_min, 1, 0);
		zt_guiSizerAddStretcher(sizer, 0, padding * 3);
		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Max:"), 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
		editor->ed_unified_random_curve_max = zt_guiMakeAnimCurve(sizer, &editor->unified.random_curve_max, ztGuiAnimCurveBehaviorFlags_LiveEdit | ztGuiAnimCurveBehaviorFlags_AdjustValues, &editor->unified.random_curve_max);
		zt_guiSizerAddItem(sizer, editor->ed_unified_random_curve_max, 1, 0);
	}


	ztGuiItem *button = zt_guiMakeButton(panel, nullptr, ztGuiButtonBehaviorFlags_NoBackground);
	ztSprite sprite_cfg = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 979, 2, 9, 9);
	zt_guiButtonSetIcon(button, &sprite_cfg);
	zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiEditorPartVarVec3ButtonCfg), editor);
	zt_guiSizerAddItem(sizer_width, button, 0, 0, ztAlign_Top, ztAnchor_Top);

	zt_guiItemHide(editor->ed_random_value_panel);
	zt_guiItemHide(editor->ed_curve_panel);
	zt_guiItemHide(editor->ed_random_curve_panel);
	zt_guiItemHide(editor->ed_unified_constant);
	zt_guiItemHide(editor->ed_unified_random_value_panel);
	zt_guiItemHide(editor->ed_unified_curve);
	zt_guiItemHide(editor->ed_unified_random_curve_panel);

	return panel;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ztInternal ztVec2 _zt_guiSizerMinSize(ztGuiItem *item);

// ================================================================================================================================================================================================

ztInternal void _zt_guiSizerTypeColumnGetMinSizes(ztGuiItem *item, ztVec2 *column_sizes, ztVec2 *row_sizes)
{
	zt_fiz(ZT_GUI_SIZER_MAX_ROWS) row_sizes[i] = ztVec2::zero;
	zt_fiz(ZT_GUI_SIZER_MAX_COLUMNS) column_sizes[i] = ztVec2::zero;

	ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;

	if (item->sizer.columns_type == ztGuiColumnSizerType_FillColumn) {
		zt_linkGetCount(items_count, item->sizer.items);
		int items_per_column = zt_convertToi32Ceil(items_count / (r32)item->sizer.columns);

		zt_fxz(item->sizer.columns) {
			zt_assert(x < ZT_GUI_SIZER_MAX_COLUMNS);
			column_sizes[x] = ztVec2::zero;

			int items_this_col = 0;
			while (entry && items_this_col++ < items_per_column) {
				ztVec2 size = entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size;
				if (entry->item->type == ztGuiItemType_Sizer) {
					size = entry->item->size = _zt_guiSizerMinSize(entry->item);
				}

				column_sizes[x].x = zt_max(column_sizes[x].x, size.x + entry->padding * 2);
				column_sizes[x].y += size.y + entry->padding * 2;

				entry = entry->next;
			}
		}
	}
	else {
		zt_fxz(item->sizer.columns) {
			zt_assert(x < ZT_GUI_SIZER_MAX_COLUMNS);
			column_sizes[x] = ztVec2::zero;

			int row_count = 0;
			int column_count = 0;
			entry = item->sizer.items;
			while (entry) {
				if (column_count == x) {
					ztVec2 size = entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size;
					if (entry->item->type == ztGuiItemType_Sizer) {
						size = entry->item->size = _zt_guiSizerMinSize(entry->item);
					}

					column_sizes[x].x = zt_max(column_sizes[x].x, size.x + entry->padding * 2);
					column_sizes[x].y += size.y + entry->padding * 2;

					row_sizes[row_count].y = zt_max(row_sizes[row_count].y, size.y + entry->padding * 2);
				}

				column_count += 1;
				if (column_count >= item->sizer.columns) {
					column_count = 0;
					row_count += 1;
					zt_assert(row_count < ZT_GUI_SIZER_MAX_ROWS);
				}

				entry = entry->next;
			}
		}
	}
}

// ================================================================================================================================================================================================

ztInternal ztVec2 _zt_guiSizerMinSize(ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiSizerMinSize");

	ztVec2 min_size = ztVec2::zero;

	if (item->sizer.type == ztGuiSizerType_Normal) {
		bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

		ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
		while (entry) {
			if (zt_guiItemIsVisible(entry->item)) {
				ztVec2 size = entry->item->size;

				if (entry->item->type == ztGuiItemType_Sizer) {
					size = _zt_guiSizerMinSize(entry->item);
				}

				if (entry->item->min_size != ztVec2::zero) {
					size.x = zt_max(size.x, entry->item->min_size.x);
					size.y = zt_max(size.y, entry->item->min_size.y);
				}

				if (horz) {
					min_size.x += size.x + entry->padding * 2;
					min_size.y = zt_max(min_size.y, size.y + entry->padding * 2);
				}
				else {
					min_size.x = zt_max(min_size.x, size.x + entry->padding * 2);
					min_size.y += size.y + entry->padding * 2;
				}
			}

			entry = entry->next;
		}
	}
	else if (item->sizer.type == ztGuiSizerType_Column) {
		ztVec2 column_sizes[ZT_GUI_SIZER_MAX_COLUMNS];
		ztVec2 row_sizes[ZT_GUI_SIZER_MAX_ROWS];

		_zt_guiSizerTypeColumnGetMinSizes(item, column_sizes, row_sizes);

		zt_fxz(item->sizer.columns) {
			min_size.x += column_sizes[x].x;
			min_size.y = zt_max(column_sizes[x].y, min_size.y);
		}
	}
	else if (item->sizer.type == ztGuiSizerType_Wrap) {
		bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

		ztVec2 start_pos = ztVec2::zero;// zt_vec2(item->size.x / 2, item->size.y / 2);
		ztVec2 current_pos = start_pos;
		ztVec2 max_item_size = ztVec2::zero;
		ztVec2 max_pos = ztVec2::zero;

		ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
		while (entry) {
			if (zt_guiItemIsVisible(entry->item)) {
				ztVec2 item_size = (entry->item->type == ztGuiItemType_Sizer ? _zt_guiSizerMinSize(entry->item) : (entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size));

				if (horz) {
					if (current_pos.x + item_size.x + entry->padding * 2 > item->size.x) {
						current_pos.x = start_pos.x;
						current_pos.y += max_item_size.y;
						max_item_size = ztVec2::zero;
					}

					item_size += zt_vec2(entry->padding * 2, entry->padding * 2);

					max_item_size.x = zt_max(max_item_size.x, item_size.x);
					max_item_size.y = zt_max(max_item_size.y, item_size.y);

					current_pos.x += item_size.x;
					max_pos.x = zt_max(max_pos.x, current_pos.x);
					max_pos.y = zt_max(max_pos.y, current_pos.y + item_size.y);
				}
				else {
					if (current_pos.y + item_size.y + entry->padding * 2 > item->size.y) {
						current_pos.y = start_pos.y;
						current_pos.x += max_item_size.x;
						max_item_size = ztVec2::zero;
					}

					item_size += zt_vec2(entry->padding * 2, entry->padding * 2);

					max_item_size.x = zt_max(max_item_size.x, item_size.x);
					max_item_size.y = zt_max(max_item_size.y, item_size.y);

					current_pos.y += item_size.y;
					max_pos.x = zt_max(max_pos.x, current_pos.x + item_size.x);
					max_pos.y = zt_max(max_pos.y, current_pos.y);
				}
			}
			entry = entry->next;
		}

		min_size = max_pos;

		if (horz) {
			min_size.x = item->size.x;
		}
		else {
			min_size.y = item->size.y;
		}
	}

	if (item->sizer.size_to_parent && item->parent) {
		if (item->parent->min_size != ztVec2::zero) {
			min_size.x = zt_max(min_size.x, item->parent->min_size.x);
			min_size.y = zt_max(min_size.y, item->parent->min_size.y);
		}
	}

	min_size.x = zt_max(0.01f, min_size.x);
	min_size.y = zt_max(0.01f, min_size.y);

	if(item->min_size.x > min_size.x) min_size.x = item->min_size.x;
	if(item->min_size.y > min_size.y) min_size.y = item->min_size.y;

	return min_size;
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiSizerRecalc(ztGuiItem *item, bool force = false)
{
	ZT_PROFILE_GUI("_zt_guiSizerRecalc");

	if (!force && item->sizer.size_frame == zt_game->game_details.current_frame && (item->sizer.size_parent_x || item->sizer.size_parent_y)) {
		return;
	}

	if (item->type == ztGuiItemType_Sizer) {
		item->sizer.size[0] = item->sizer.size[1] = -1;
	}

	ztGuiItem *child = item->first_child;
	while (child) {
		_zt_guiSizerRecalc(child, force);
		child = child->sib_next;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSizerUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiSizerUpdate))
{
	ZT_PROFILE_GUI("_zt_guiSizerUpdate");

	if (item->parent == nullptr || ((item->sizer.size_to_parent && item->parent->size == item->size)) || (!item->sizer.size_to_parent && item->size.x == item->sizer.size[0] && item->size.y == item->sizer.size[1])) {
		if (item->sizer.size[0] != -1 && item->sizer.size[1] != -1) {
			return;
		}
	}

	if (item->sizer.size_to_parent && !item->sizer.size_parent_x && !item->sizer.size_parent_y) {
		//ztVec2 parent_size = item->parent->min_size == ztVec2::zero ? item->parent->size : item->parent->min_size;
		ztVec2 parent_size = zt_vec2(zt_max(item->parent->min_size.x, item->parent->size.x), zt_max(item->parent->min_size.y, item->parent->size.y));
		item->sizer.size[0] = item->size.x = parent_size.x;
		item->sizer.size[1] = item->size.y = parent_size.y;
	}
	else {
		if (item->size == ztVec2::zero && !item->sizer.size_parent_x && !item->sizer.size_parent_y) {
			return;
		}

		item->sizer.size_frame = zt_game->game_details.current_frame;

		if (item->sizer.size_parent_x || item->sizer.size_parent_y) {
			ztVec2 min_size = _zt_guiSizerMinSize(item);

			bool recalc = false;
			if (item->sizer.size_parent_x) {
				if (item->parent->size.x != min_size.x) {
					item->size.x = item->parent->size.x = min_size.x;
					recalc = true;
				}
				else if (item->sizer.size_to_parent && item->size.x != item->parent->size.x) {
					item->size.x = item->parent->size.x;
				}
			}
			else if (item->sizer.size_to_parent) {
				item->size.x = item->parent->min_size.x == 0 ? item->parent->size.x : item->parent->min_size.x;
				recalc = true;
			}
			else {
				if (item->size.x != min_size.x) {
					item->size.x = min_size.x;
					recalc = true;
				}
			}

			if (item->sizer.size_parent_y) {
				if (item->parent->size.y != min_size.y) {
					if (item->min_size.y != 0) {
						min_size.y = zt_max(item->min_size.y, min_size.y);
					}
					item->size.y = item->parent->size.y = min_size.y;
					recalc = true;
				}
				else if (item->sizer.size_to_parent && item->size.y != item->parent->size.y) {
					item->size.y = item->parent->size.y;
				}
			}
			else if (item->sizer.size_to_parent) {
				item->size.y = item->parent->min_size.y == 0 ? item->parent->size.y : item->parent->min_size.y;
				recalc = true;
			}
			else {
				if (item->size.y != min_size.y) {
					item->size.y = min_size.y;
					recalc = true;
				}
			}

			if (recalc) {
				if (item->min_size != ztVec2::zero) {
					if (item->size.x < item->min_size.x) item->size.x = item->min_size.x;
					if (item->size.y < item->min_size.y) item->size.y = item->min_size.y;
				}
				if (item->parent && item->parent->min_size != ztVec2::zero) {
					if (item->parent->size.x < item->parent->min_size.x) item->parent->size.x = item->parent->min_size.x;
					if (item->parent->size.y < item->parent->min_size.y) item->parent->size.y = item->parent->min_size.y;
				}

				_zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(item->parent));
			}
		}

		item->sizer.size[0] = zt_max(item->min_size.x, item->size.x);
		item->sizer.size[1] = zt_max(item->min_size.y, item->size.y);
	}

	if (item->sizer.type == ztGuiSizerType_Normal) {
		bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

		r32 room_orient = horz ? item->sizer.size[0] : item->sizer.size[1];
		r32 total_prop = 0;

		int entry_count = 0;
		ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
		while (entry) {
			if (zt_guiItemIsVisible(entry->item)) {
				entry_count += 1;
				if (entry->proportion == 0) {
					// takes up only as much space as the item inside it
					int padding_mult = 2;

					if (entry->item->type == ztGuiItemType_Sizer) {
						ztVec2 min_size = _zt_guiSizerMinSize(entry->item);
						room_orient -= (horz ? min_size.x : min_size.y) + entry->padding * padding_mult;
					}
					else {
						ztVec2 item_size = entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size;
						room_orient -= (horz ? item_size.x : item_size.y) + entry->padding * padding_mult;
					}
				}

				total_prop += entry->proportion;
			}
			entry = entry->next;
		}

		r32 entry_pos_orient = horz ? item->sizer.size[0] / -2.f : item->sizer.size[1] / 2.f;
		r32 entry_opp_orient = horz ? item->sizer.size[1] / 2.f : item->sizer.size[0] / -2.f;

		entry = item->sizer.items;
		while (entry) {
			if (zt_guiItemIsVisible(entry->item)) {
				r32 entry_size_orient = 0;

				ztVec2 item_size = (entry->item->type == ztGuiItemType_Sizer ? _zt_guiSizerMinSize(entry->item) : (entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size));

				if (entry->proportion != 0) {
					entry_size_orient = (entry->proportion / total_prop) * room_orient;
				}
				else {
					entry_size_orient = (horz ? (item_size.x + entry->padding * 2) : (item_size.y + entry->padding * 2));
				}
				ztVec2 entry_size = zt_vec2(horz ? entry_size_orient : item->sizer.size[0], horz ? item->sizer.size[1] : entry_size_orient);

				if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Horz)) {
					item_size.x = entry_size.x - entry->padding * 2;
				}
				if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Vert)) {
					item_size.y = entry_size.y - entry->padding * 2;
				}

				item_size.x = zt_min(item_size.x, entry_size.x - entry->padding * 2);
				item_size.y = zt_min(item_size.y, entry_size.y - entry->padding * 2);

				entry->item->size = item_size;

				ztVec2 entry_pos = zt_vec2(horz ? entry_pos_orient + (entry->padding + item_size.x / 2) : entry_opp_orient + (entry->padding + item_size.x / 2),
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
			}
			entry = entry->next;
		}
	}
	else if (item->sizer.type == ztGuiSizerType_Column) {

		ztVec2 column_sizes[ZT_GUI_SIZER_MAX_COLUMNS];
		ztVec2 row_sizes   [ZT_GUI_SIZER_MAX_ROWS];
		r32 item_size_w = 0;

		_zt_guiSizerTypeColumnGetMinSizes(item, column_sizes, row_sizes);

		if (item->sizer.columns_type == ztGuiColumnSizerType_FillColumn) {
			zt_linkGetCount(items_count, item->sizer.items);
			int items_per_column = zt_convertToi32Ceil(items_count / (r32)item->sizer.columns);

			int total_prop = 0;
			zt_fxz(item->sizer.columns) {
				total_prop += item->sizer.props[x];
				item_size_w += column_sizes[x].x;
			}

			ztVec2 item_size = item->min_size == ztVec2::zero ? item->size : item->min_size;

			// column sizes are now at the minimum, so now distribute the extra size according to proportions
			r32 extra = item_size.x - item_size_w;
			zt_fxz(item->sizer.columns) {
				column_sizes[x].x += extra * (item->sizer.props[x] / (r32)total_prop);
			}

			// position each item
			r32 col_x = item_size.x / -2;

			ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
			zt_fxz(item->sizer.columns) {
				int items_this_col = 0;
				r32 item_y = item->size.y / 2;
				while (entry && items_this_col++ < items_per_column) {
					ztVec2 size = entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size;
					if (entry->item->type == ztGuiItemType_Sizer) {
						size = _zt_guiSizerMinSize(entry->item);
					}

					if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Horz)) {
						entry->item->size.x = column_sizes[x].x - entry->padding * 2;
					}
					if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Vert)) {
						entry->item->size.y = column_sizes[x].y - entry->padding * 2;
					}

					if (zt_bitIsSet(entry->align_flags, ztAlign_Left)) {
						entry->item->pos.x = col_x + entry->padding + entry->item->size.x / 2;
					}
					else if (zt_bitIsSet(entry->align_flags, ztAlign_Right)) {
						entry->item->pos.x = (col_x + column_sizes[x].x) - (entry->item->size.x / 2.f + entry->padding);
					}
					else {
						entry->item->pos.x = (col_x + (column_sizes[x].x / 2));
					}
					entry->item->pos.y = (item_y - entry->padding) - (entry->item->size.y / 2);

					//if (zt_bitIsSet(entry->align_flags, ztAlign_VertCenter)) {
					//	entry->item->pos.y -= (column_sizes[x].y - (entry->item->size.y + entry->padding * 2)) / 2;
					//}
					//else if (zt_bitIsSet(entry->align_flags, ztAlign_Bottom)) {
					//	entry->item->pos.y -= column_sizes[x].y - (entry->item->size.y + entry->padding * 2);
					//}
					//else { // top is default
					//}
					item_y -= entry->item->size.y + entry->padding * 2;

					entry = entry->next;
				}

				col_x += column_sizes[x].x;
			}
		}
		else if (item->sizer.columns_type == ztGuiColumnSizerType_FillRow) {
			int total_prop = 0;

			zt_fxz(item->sizer.columns) {
				total_prop += item->sizer.props[x];
				item_size_w += column_sizes[x].x;
			}

			ztVec2 item_size = item->min_size == ztVec2::zero ? item->size : item->min_size;

			// column sizes are now at the minimum, so now distribute the extra size according to proportions
			r32 extra = item_size.x - item_size_w;
			zt_fxz(item->sizer.columns) {
				column_sizes[x].x += extra * (item->sizer.props[x] / (r32)total_prop);
			}

			// position each item
			r32 col_x = item_size.x / -2;

			zt_fxz(item->sizer.columns) {
				r32 item_y = item->size.y / 2;

				int column_count = 0;
				int row_count = 0;
				ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;
				while (entry) {
					if (column_count == x) {
						ztVec2 size = entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size;
						if (entry->item->type == ztGuiItemType_Sizer) {
							size = _zt_guiSizerMinSize(entry->item);
						}

						if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Horz)) {
							entry->item->size.x = column_sizes[x].x - entry->padding * 2;
						}
						if (zt_bitIsSet(entry->grow_direction, ztGuiItemOrient_Vert)) {
							entry->item->size.y = row_sizes[row_count].y - entry->padding * 2;
						}

						if (zt_bitIsSet(entry->align_flags, ztAlign_Left)) {
							entry->item->pos.x = col_x + entry->padding + entry->item->size.x / 2;
						}
						else if (zt_bitIsSet(entry->align_flags, ztAlign_Right)) {
							entry->item->pos.x = (col_x + column_sizes[x].x) - (entry->item->size.x / 2.f + entry->padding);
						}
						else {
							entry->item->pos.x = (col_x + (column_sizes[x].x / 2));
						}

						entry->item->pos.y = (item_y - entry->padding) - (entry->item->size.y / 2);
						if (zt_bitIsSet(entry->align_flags, ztAlign_VertCenter)) {
							entry->item->pos.y -= (row_sizes[row_count].y - (entry->item->size.y + entry->padding * 2)) / 2;
						}
						else if (zt_bitIsSet(entry->align_flags, ztAlign_Bottom)) {
							entry->item->pos.y -= row_sizes[row_count].y - (entry->item->size.y + entry->padding * 2);
						}
						else { // top is default
						}
						item_y -= row_sizes[row_count].y;// entry->item->size.y + entry->padding * 2;
					}

					column_count += 1;
					if (column_count >= item->sizer.columns) {
						column_count = 0;
						row_count += 1;
					}

					entry = entry->next;
				}

				col_x += column_sizes[x].x;
			}
		}
		else zt_assert(false);
	}
	else if (item->sizer.type == ztGuiSizerType_Wrap) {
		bool horz = item->sizer.orient == ztGuiItemOrient_Horz;

		ztGuiItem::ztSizerItemEntry *entry = item->sizer.items;

		ztVec2 start_pos = zt_vec2(item->size.x / -2, item->size.y / 2);
		ztVec2 current_pos = start_pos;
		ztVec2 max_item_size = ztVec2::zero;

		r32 section_size = 0;

		ztGuiItem::ztSizerItemEntry *section_first_entry = nullptr;

		struct local
		{
			static void alignEntries(bool horz, r32 section_size, ztGuiItem::ztSizerItemEntry *first, ztGuiItem::ztSizerItemEntry *last)
			{
				if (horz) {
					for (ztGuiItem::ztSizerItemEntry *align_entry = first; align_entry != last; align_entry = align_entry->next) {
						if (zt_bitIsSet(align_entry->grow_direction, ztGuiItemOrient_Vert)) {
							r32 diff = section_size - align_entry->item->size.y;
							align_entry->item->size.y = section_size;
							align_entry->item->pos.y += diff / -2;
						}

						r32 diff = section_size - align_entry->item->size.y;

						if (zt_bitIsSet(align_entry->align_flags, ztAlign_VertCenter)) {
							align_entry->item->pos.y -= diff / 2;
						}
						else if (zt_bitIsSet(align_entry->align_flags, ztAlign_Bottom)) {
							align_entry->item->pos.y -= diff;
						}
					}
				}
				else {
					for (ztGuiItem::ztSizerItemEntry *align_entry = first; align_entry != last; align_entry = align_entry->next) {
						if (zt_bitIsSet(align_entry->grow_direction, ztGuiItemOrient_Horz)) {
							r32 diff = section_size - align_entry->item->size.x;
							align_entry->item->size.x = section_size;
							align_entry->item->pos.x += diff / -2;
						}

						r32 diff = section_size - align_entry->item->size.x;

						if (zt_bitIsSet(align_entry->align_flags, ztAlign_Center)) {
							align_entry->item->pos.x += diff / 2;
						}
						else if (zt_bitIsSet(align_entry->align_flags, ztAlign_Right)) {
							align_entry->item->pos.x += diff;
						}
					}
				}
			}
		};

		while (entry) {
			if (zt_guiItemIsVisible(entry->item)) {
				if (section_first_entry == nullptr) {
					section_first_entry = entry;
				}

				ztVec2 item_size = (entry->item->type == ztGuiItemType_Sizer ? _zt_guiSizerMinSize(entry->item) : (entry->item->min_size == ztVec2::zero ? entry->item->size : entry->item->min_size));

				if (horz) {
					if (current_pos.x + item_size.x + entry->padding * 2 + item->size.x / 2 > item->size.x) {
						local::alignEntries(horz, section_size, section_first_entry, entry);
						section_first_entry = entry;
						section_size = 0;

						current_pos.x = start_pos.x;
						current_pos.y -= max_item_size.y;

						max_item_size = ztVec2::zero;
					}

					section_size = zt_max(section_size, item_size.y);

					item_size += zt_vec2(entry->padding, entry->padding);
					entry->item->pos = zt_vec2(current_pos.x + item_size.x / 2, current_pos.y - item_size.y / 2);
					item_size += zt_vec2(entry->padding, entry->padding);

					max_item_size.x = zt_max(max_item_size.x, item_size.x);
					max_item_size.y = zt_max(max_item_size.y, item_size.y);

					current_pos.x += item_size.x;
				}
				else {
					if (current_pos.y - (item_size.y + entry->padding * 2 + item->size.y / 2)  < -item->size.y) {
						local::alignEntries(horz, section_size, section_first_entry, entry);
						section_first_entry = entry;
						section_size = 0;

						current_pos.y = start_pos.y;
						current_pos.x += max_item_size.x;

						max_item_size = ztVec2::zero;
					}

					section_size = zt_max(section_size, item_size.x);

					item_size += zt_vec2(entry->padding, entry->padding);
					entry->item->pos = zt_vec2(current_pos.x + item_size.x / 2, current_pos.y - item_size.y / 2);
					item_size += zt_vec2(entry->padding, entry->padding);

					max_item_size.x = zt_max(max_item_size.x, item_size.x);
					max_item_size.y = zt_max(max_item_size.y, item_size.y);

					current_pos.y -= item_size.y;
				}
			}
			entry = entry->next;
		}

		local::alignEntries(horz, section_size, section_first_entry, entry);
	}
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSizerBestSize, ztInternal ZT_FUNC_GUI_ITEM_BEST_SIZE(_zt_guiSizerBestSize))
{
	ZT_PROFILE_GUI("_zt_guiSizerBestSize");

	*size = _zt_guiSizerMinSize(item);
	if (min_size) *min_size = *size;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeSizer(ztGuiItem *parent, ztGuiItemOrient_Enum orient, bool size_to_parent)
{
	ZT_PROFILE_GUI("zt_guiMakeSizer");

	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Sizer, ztGuiItemBehaviorFlags_LateUpdate);
	zt_returnValOnNull(item, nullptr);

	item->sizer.orient = orient;
	item->sizer.type = ztGuiSizerType_Normal;
	item->sizer.size[0] = item->sizer.size[1] = -1;
	item->sizer.size_to_parent = size_to_parent;
	item->sizer.size_parent_x = item->sizer.size_parent_y = false;
	item->sizer.size_frame = 0;
	item->sizer.items = nullptr;

	item->functions.cleanup   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSizerCleanup);
	item->functions.update    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSizerUpdate);
	item->functions.best_size = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSizerBestSize);
	item->functions.user_data = nullptr;

	return item;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeColumnSizer(ztGuiItem *parent, int columns, ztGuiColumnSizerType_Enum type, bool size_to_parent)
{
	ZT_PROFILE_GUI("zt_guiMakeColumnSizer");

	ztGuiItem *sizer = zt_guiMakeSizer(parent, ztGuiItemOrient_Horz, size_to_parent);
	if (sizer) {
		sizer->sizer.type         = ztGuiSizerType_Column;
		sizer->sizer.columns      = columns;
		sizer->sizer.columns_type = type;

		zt_fiz(columns) {
			sizer->sizer.props[i] = 1;
		}
	}

	return sizer;
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeWrapSizer(ztGuiItem *parent, ztGuiItemOrient_Enum orient, bool size_to_parent)
{
	ZT_PROFILE_GUI("zt_guiMakeWrapSizer");

	ztGuiItem *sizer = zt_guiMakeSizer(parent, orient, size_to_parent);
	if (sizer) {
		sizer->sizer.type = ztGuiSizerType_Wrap;

		zt_guiSizerSizeParent(sizer, orient == ztGuiItemOrient_Vert, orient == ztGuiItemOrient_Horz);
		//zt_guiSizerSizeToParent(sizer, true);
	}

	return sizer;
}

// ================================================================================================================================================================================================

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

	sizer->sizer.size[0] = sizer->sizer.size[1] = -1; // trigger recalc

	if (item->type == ztGuiItemType_Sizer) {
		item->sizer.size_to_parent = false;
	}
}

// ================================================================================================================================================================================================

void zt_guiSizerAddStretcher(ztGuiItem *sizer, int proportion, r32 padding)
{
	ZT_PROFILE_GUI("zt_guiSizerAddStretcher");

	ztGuiItem *stretcher = _zt_guiMakeItemBase(sizer, ztGuiItemType_Custom, 0);
	zt_debugOnly(zt_guiItemSetName(stretcher, "Sizer Stretcher"));

	zt_guiSizerAddItem(sizer, stretcher, proportion, padding);
}

// ================================================================================================================================================================================================

void zt_guiSizerSizeToParent(ztGuiItem *sizer, bool size_to_parent)
{
	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer);
	sizer->sizer.size_to_parent = size_to_parent;
}

// ================================================================================================================================================================================================

void zt_guiSizerSizeParent(ztGuiItem *sizer, bool size_parent_x, bool size_parent_y)
{
	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer);
	sizer->sizer.size_to_parent = false;
	sizer->sizer.size_parent_x = size_parent_x;
	sizer->sizer.size_parent_y = size_parent_y;

	zt_bitRemove(sizer->behavior_flags, ztGuiItemBehaviorFlags_LateUpdate);
}

// ================================================================================================================================================================================================

void zt_guiSizerRecalc(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiSizerRecalc");

	_zt_guiSizerRecalc(item, true);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiSizerRecalcImmediately(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiSizerRecalcImmediately");

	_zt_guiSizerRecalc(item, true);
	_zt_guiSizerRecalcImmediately(item);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiColumnSizerSetProp(ztGuiItem *sizer, int col, int prop)
{
	ZT_PROFILE_GUI("zt_guiColumnSizerSetProp");

	zt_returnOnNull(sizer);
	zt_assertReturnOnFail(sizer->type == ztGuiItemType_Sizer && sizer->sizer.type == ztGuiSizerType_Column);
	zt_assertReturnOnFail(col >= 0 && col < sizer->sizer.columns);

	sizer->sizer.props[col] = prop;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSplitterRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiSplitterRender))
{
	ZT_PROFILE_GUI("_zt_guiSplitterRender");

	zt_guiThemeRender(theme, draw_list, item, item->pos + offset);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSplitterInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiSplitterInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiSplitterInputMouse");

	ztVec2 mpos = zt_guiItemPositionScreenToLocal(item, zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y));

	r32 size_handle = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterHandleW, item);

	if (!item->splitter.dragging) {
		bool over_splitter = false;
		r32 splitter_center = 0;

		if (item->splitter.orient == ztGuiItemOrient_Horz) {
			r32 start = item->size.x / -2;
			r32 size_first = 0;

			if (item->splitter.size_only <= 0) {
				size_first = item->splitter.split_percent * item->size.x;
			}
			else {
				r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterPadding, item);
				size_first = (item->splitter.size_only == 1 ? item->splitter.size : item->size.x - (item->splitter.size + padding + size_handle)) + padding + size_handle / 2;
			}

			if (mpos.x >= (start + size_first) - size_handle && mpos.x <= (start + size_first) + size_handle) {
				zt_inputMouseSetCursor(ztInputMouseCursor_ResizeEW);
				over_splitter = true;
				splitter_center = start + size_first;
			}
			else {
				zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
			}
		}
		else {
			r32 start = item->size.y / 2;
			r32 size_first = 0;

			if (item->splitter.size_only <= 0) {
				size_first = item->splitter.split_percent * item->size.y;
			}
			else {
				r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterPadding, item);
				size_first = (item->splitter.size_only == 1 ? item->splitter.size : item->size.y - (item->splitter.size + padding + size_handle)) + padding + size_handle / 2;
			}

			if (mpos.y <= (start - size_first) + (size_handle / 2) && mpos.y >= (start - size_first) - (size_handle / 2)) {
				zt_inputMouseSetCursor(ztInputMouseCursor_ResizeNS);
				over_splitter = true;
				splitter_center = start - size_first;
			}
			else {
				zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
			}
		}

		if (over_splitter && input_mouse->leftJustPressed()) {
			item->splitter.dragging_offset = item->splitter.orient == ztGuiItemOrient_Horz ? mpos.x - splitter_center : splitter_center - mpos.y;
			item->splitter.dragging = true;
		}
	}
	else {
		if (input_mouse->leftPressed()) {
			if (item->splitter.orient == ztGuiItemOrient_Horz) {
				r32 start = item->size.x / -2;
				r32 min = (3 / zt_pixelsPerUnit()) / item->size.x;
				item->splitter.split_percent = zt_clamp(((mpos.x - start) - item->splitter.dragging_offset) / item->size.x, min, 1 - min);

				if (item->splitter.size_only == 1) {
					r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterPadding, item);
					r32 size = item->size.x - ((padding * 2) + size_handle);
					item->splitter.size = size * item->splitter.split_percent;
				}
				else if (item->splitter.size_only == 2) {
					r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterPadding, item);
					r32 size = item->size.x - ((padding * 2) + size_handle);
					item->splitter.size = size * (1 - item->splitter.split_percent);
				}
			}
			else {
				r32 start = item->size.y / 2;
				r32 min = (3 / zt_pixelsPerUnit()) / item->size.y;
				item->splitter.split_percent = zt_clamp(((start - mpos.y) - item->splitter.dragging_offset) / item->size.y, min, 1 - min);

				if (item->splitter.size_only == 1) {
					r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterPadding, item);
					r32 size = item->size.y - ((padding * 2) + size_handle);
					item->splitter.size = size * item->splitter.split_percent;
				}
				else if(item->splitter.size_only == 2) {
					r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_SplitterPadding, item);
					r32 size = item->size.y - ((padding * 2) + size_handle);
					item->splitter.size = size * (1 - item->splitter.split_percent);
				}
			}

			item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
		}
		else {
			item->splitter.dragging = false;
			zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
		}

		return true;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiSplitterUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiSplitterUpdate))
{
	ZT_PROFILE_GUI("_zt_guiSplitterUpdate");
	if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Dirty))) {
		return;
	}

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SplitterPadding, item);
	r32 size_handle = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SplitterHandleW, item);
	r32 size = (item->splitter.orient == ztGuiItemOrient_Horz ? item->size.x : item->size.y) - (size_handle + padding * 2);

	r32 size_first = 0;
	r32 size_second = 0;

	if (item->splitter.size_only <= 0) {
		size_first = item->splitter.split_percent * size;
		size_second = (1 - item->splitter.split_percent) * size;
	}
	else {
		size_first = item->splitter.size_only == 1 ? item->splitter.size : size - item->splitter.size;
		size_second = item->splitter.size_only == 2 ? item->splitter.size : size - item->splitter.size;
	}

	if (item->splitter.orient == ztGuiItemOrient_Horz) {
		if (item->splitter.items[0] != nullptr) {
			item->splitter.items[0]->size = zt_vec2(size_first, item->size.y - padding * 2);
			item->splitter.items[0]->pos = zt_vec2((item->size.x / -2) + (size_first / 2) + padding, 0);
		}
		if (item->splitter.items[1] != nullptr) {
			item->splitter.items[1]->size = zt_vec2(size_second, item->size.y - padding * 2);
			item->splitter.items[1]->pos = zt_vec2((item->size.x / 2) + ((size_second / -2) - padding), 0);
		}
	}
	else {
		if (item->splitter.items[0] != nullptr) {
			item->splitter.items[0]->size = zt_vec2(item->size.x - padding * 2, size_first);
			item->splitter.items[0]->pos = zt_vec2(0, (item->size.y / 2) + (size_first / -2) - padding);
		}
		if (item->splitter.items[1] != nullptr) {
			item->splitter.items[1]->size = zt_vec2(item->size.x - padding * 2, size_second);
			item->splitter.items[1]->pos = zt_vec2(0, (item->size.y / -2) + (size_second / 2) + padding);
		}
	}
}

// ================================================================================================================================================================================================

ztGuiItem *zt_guiMakeSplitter(ztGuiItem *parent, ztGuiItemOrient_Enum orient, r32 split_percent)
{
	ZT_PROFILE_GUI("zt_guiMakeSplitter");
	ztGuiItem *item = _zt_guiMakeItemBase(parent, ztGuiItemType_Splitter, ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus);

	item->splitter.orient = orient;
	item->splitter.split_percent = split_percent;
	item->splitter.items[0] = nullptr;
	item->splitter.items[1] = nullptr;
	item->splitter.dragging = false;
	item->splitter.size_only = 0;
	item->splitter.size = 0;

	item->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSplitterRender);
	item->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSplitterInputMouse);
	item->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiSplitterUpdate);
	item->functions.user_data   = nullptr;

	return item;
}

// ================================================================================================================================================================================================

void zt_guiSplitterSetItems(ztGuiItem *splitter, ztGuiItem *first, ztGuiItem *second)
{
	ZT_PROFILE_GUI("zt_guiSplitterSetItems");
	zt_returnOnNull(splitter);
	zt_assertReturnOnFail(splitter->type == ztGuiItemType_Splitter);

	zt_guiSplitterSetFirstItem(splitter, first);
	zt_guiSplitterSetSecondItem(splitter, second);
}

// ================================================================================================================================================================================================

void zt_guiSplitterSetPercent(ztGuiItem *splitter, r32 percent)
{
	ZT_PROFILE_GUI("zt_guiSplitterSetPercent");
	zt_returnOnNull(splitter);
	zt_assertReturnOnFail(splitter->type == ztGuiItemType_Splitter);

	splitter->splitter.split_percent = percent;
	splitter->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

void zt_guiSplitterSetFirstSize(ztGuiItem *splitter, r32 size)
{
	ZT_PROFILE_GUI("zt_guiSplitterSetFirstWidth");
	zt_returnOnNull(splitter);
	zt_assertReturnOnFail(splitter->type == ztGuiItemType_Splitter);

	splitter->splitter.size_only = 1;
	splitter->splitter.size = size;
}

// ================================================================================================================================================================================================

void zt_guiSplitterSetSecondSize(ztGuiItem *splitter, r32 size)
{
	ZT_PROFILE_GUI("zt_guiSplitterSetSecondWidth");
	zt_returnOnNull(splitter);
	zt_assertReturnOnFail(splitter->type == ztGuiItemType_Splitter);

	splitter->splitter.size_only = 2;
	splitter->splitter.size = size;
}

// ================================================================================================================================================================================================

void zt_guiSplitterSetFirstItem(ztGuiItem *splitter, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiSplitterSetFirstItem");
	zt_returnOnNull(splitter);
	zt_assertReturnOnFail(splitter->type == ztGuiItemType_Splitter);

	if (item != nullptr) {
		zt_guiItemReparent(item, splitter);
	}
	splitter->splitter.items[0] = item;
	splitter->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

void zt_guiSplitterSetSecondItem(ztGuiItem *splitter, ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiSplitterSetSecondItem");
	zt_returnOnNull(splitter);
	zt_assertReturnOnFail(splitter->type == ztGuiItemType_Splitter);

	if (item != nullptr) {
		zt_guiItemReparent(item, splitter);
	}
	splitter->splitter.items[1] = item;
	splitter->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztGuiDialogMessage
{
	ztGuiDialogMessageOption options[8];
	ztGuiItem               *options_buttons[8];
	int                      options_count;

	ZT_FUNCTION_POINTER_VAR (callback, zt_guiDialogMessageClosed_Func);
	void                    *user_data;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogMessageBoxButton, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDialogMessageBoxButton))
{
	ztGuiDialogMessage *dialog_data = (ztGuiDialogMessage*)user_data;

	if (ZT_FUNCTION_POINTER_IS_VALID(dialog_data->callback)) {
		zt_fiz(dialog_data->options_count) {
			if (dialog_data->options_buttons[i] == button) {
				ZT_FUNCTION_POINTER_ACCESS(dialog_data->callback, zt_guiDialogMessageClosed_Func)(&dialog_data->options[i], dialog_data->user_data);
				break;
			}
		}
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

void zt_guiDialogMessageBox(const char *title, const char *message, ztGuiDialogMessageOption *options, int options_count, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data)
{
	ztGuiItem *window = zt_guiMakeWindow(title, ztGuiWindowBehaviorFlags_Modal | ztGuiWindowBehaviorFlags_ShowTitle);

	ztGuiDialogMessage *dialog_data = zt_mallocStructArena(ztGuiDialogMessage, window->gm->arena);
	zt_guiMakePanel(window, 0, dialog_data, window->gm->arena);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	zt_guiSizerAddStretcher(sizer, 1);
	ztGuiTheme *theme = zt_guiItemGetTheme(sizer);

	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, sizer);

	ztGuiItem *label = zt_guiMakeStaticText(sizer, message);
	zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Center | ztAlign_VertCenter, 0);

	zt_guiSizerAddStretcher(sizer, 1, 0);

	ztGuiItem *button_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, button_sizer, 0, padding, ztAlign_Center|ztAlign_VertCenter, 0);

	options_count = zt_min(options_count, zt_elementsOf(dialog_data->options));
	zt_memCpy(dialog_data->options, zt_sizeof(ztGuiDialogMessageOption) * options_count, options, zt_sizeof(ztGuiDialogMessageOption) * options_count);
	dialog_data->options_count = options_count;
	dialog_data->callback = callback;
	dialog_data->user_data = user_data;

	zt_fiz(options_count) {
		ztGuiItem *button = zt_guiMakeButton(button_sizer, options[i].display);
		zt_guiSizerAddItem(button_sizer, button, 1, padding);

		dialog_data->options_buttons[i] = button;

		zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogMessageBoxButton), dialog_data);
	}

	zt_guiSizerAddStretcher(sizer, 1);

	ztVec2 min_size = zt_guiSizerGetMinSize(sizer);

	min_size.y += zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight, window);

	min_size.x += padding * 6;
	min_size.y += padding * 6;

	min_size.x = zt_max(min_size.x, 6);
	min_size.y = zt_max(min_size.y, 2.25f);

	zt_guiItemSetSize(window, min_size);
}

// ================================================================================================================================================================================================

void zt_guiDialogMessageBoxOk(const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data)
{
	ztGuiDialogMessageOption options[1];

	options[0].id = 0;
	zt_strCpy(options[0].display, zt_elementsOf(options[0].display), "OK");

	zt_guiDialogMessageBox(title, message, options, zt_elementsOf(options), ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
}

// ================================================================================================================================================================================================

void zt_guiDialogMessageBoxOkCancel(const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data)
{
	ztGuiDialogMessageOption options[2];

	options[0].id = 0;
	zt_strCpy(options[0].display, zt_elementsOf(options[0].display), "OK");
	options[1].id = 1;
	zt_strCpy(options[1].display, zt_elementsOf(options[1].display), "Cancel");

	zt_guiDialogMessageBox(title, message, options, zt_elementsOf(options), ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
}

// ================================================================================================================================================================================================

void zt_guiDialogMessageBoxYesNo(const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data)
{
	ztGuiDialogMessageOption options[2];

	options[0].id = 0;
	zt_strCpy(options[0].display, zt_elementsOf(options[0].display), "Yes");
	options[1].id = 1;
	zt_strCpy(options[1].display, zt_elementsOf(options[1].display), "No");

	zt_guiDialogMessageBox(title, message, options, zt_elementsOf(options), ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
}

// ================================================================================================================================================================================================

void zt_guiDialogMessageBoxYesNoCancel(const char *title, const char *message, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogMessageClosed_Func), void *user_data)
{
	ztGuiDialogMessageOption options[3];

	options[0].id = 0;
	zt_strCpy(options[0].display, zt_elementsOf(options[0].display), "Yes");
	options[1].id = 1;
	zt_strCpy(options[1].display, zt_elementsOf(options[1].display), "No");
	options[2].id = 2;
	zt_strCpy(options[2].display, zt_elementsOf(options[2].display), "Cancel");

	zt_guiDialogMessageBox(title, message, options, zt_elementsOf(options), ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


struct ztGuiDialogGetUserText
{
	ztGuiItem   *text_edit;
	ztGuiItem   *button_ok;
	ztGuiItem   *button_cancel;

	ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogGetUserText_Func);
	void                   *user_data;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogGetUserTextButtonOK, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDialogGetUserTextButtonOK))
{
	ztGuiDialogGetUserText *dialog_data = (ztGuiDialogGetUserText*)user_data;

	if (ZT_FUNCTION_POINTER_IS_VALID(dialog_data->callback)) {
		char buffer[512];
		zt_guiTextEditGetValue(dialog_data->text_edit, buffer, zt_elementsOf(buffer));
		ZT_FUNCTION_POINTER_ACCESS(dialog_data->callback, zt_guiDialogGetUserText_Func)(buffer, false, dialog_data->user_data);
	}

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogGetUserTextButtonCancel, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDialogGetUserTextButtonCancel))
{
	ztGuiDialogGetUserText *dialog_data = (ztGuiDialogGetUserText*)user_data;

	if (ZT_FUNCTION_POINTER_IS_VALID(dialog_data->callback)) {
		char buffer[512];
		zt_guiTextEditGetValue(dialog_data->text_edit, buffer, zt_elementsOf(buffer));
		ZT_FUNCTION_POINTER_ACCESS(dialog_data->callback, zt_guiDialogGetUserText_Func)(buffer, true, dialog_data->user_data);
	}

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogGetUserTextEditKey, ZT_FUNC_GUI_TEXTEDIT_KEY(_zt_guiDialogGetUserTextEditKey))
{
	ztGuiDialogGetUserText *dialog_data = (ztGuiDialogGetUserText*)user_data;

	if(input_keys[ztInputKeys_Return].justPressed()) {
		_zt_guiDialogGetUserTextButtonOK(dialog_data->button_ok, dialog_data);
	}
	if(input_keys[ztInputKeys_Escape].justPressed() && dialog_data->button_cancel != nullptr) {
		_zt_guiDialogGetUserTextButtonCancel(dialog_data->button_cancel, dialog_data);
	}
}

// ================================================================================================================================================================================================

void zt_guiDialogGetUserText(const char *title, const char *message, const char *def_value, bool allow_cancel, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogGetUserText_Func), void *user_data)
{
	ztGuiItem *window = zt_guiMakeWindow(title, ztGuiWindowBehaviorFlags_Modal | ztGuiWindowBehaviorFlags_ShowTitle);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	zt_guiSizerAddStretcher(sizer, 1);
	ztGuiTheme *theme = zt_guiItemGetTheme(sizer);

	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, sizer);

	ztGuiItem *label = zt_guiMakeStaticText(sizer, message);
	zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);

	ztGuiItem *value = zt_guiMakeTextEdit(sizer, def_value, 0, 512);
	zt_guiSizerAddItem(sizer, value, 0, padding);
	zt_guiTextEditSetSelection(value, 0, zt_strLen(def_value));
	zt_guiItemSetFocus(value);

	ztGuiItem *button_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, button_sizer, 0, padding, ztAlign_Center|ztAlign_VertCenter, 0);

	ztGuiItem *button_ok = zt_guiMakeButton(button_sizer, "OK");
	zt_guiSizerAddItem(button_sizer, button_ok, 1, padding);

	ztGuiItem *button_cancel = nullptr;
	if(allow_cancel) {
		button_cancel = zt_guiMakeButton(button_sizer, "Cancel");
		zt_guiSizerAddItem(button_sizer, button_cancel, 1, padding);
	}

	zt_guiSizerAddStretcher(sizer, 1);

	ztGuiDialogGetUserText *dialog_data = zt_mallocStructArena(ztGuiDialogGetUserText, window->gm->arena);
	zt_guiMakePanel(window, 0, dialog_data, window->gm->arena);

	dialog_data->text_edit = value;
	dialog_data->button_ok = button_ok;
	dialog_data->button_cancel = button_cancel;
	dialog_data->callback = callback;
	dialog_data->user_data = user_data;

	zt_guiButtonSetCallback(button_ok, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogGetUserTextButtonOK), dialog_data);
	if (button_cancel) {
		zt_guiButtonSetCallback(button_cancel, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogGetUserTextButtonCancel), dialog_data);
	}

	zt_guiTextEditSetCallback(value, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogGetUserTextEditKey), dialog_data);

	ztVec2 min_size = zt_guiSizerGetMinSize(sizer);

	min_size.y += zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_WindowTitleHeight, window);

	min_size.x += padding * 6;
	min_size.y += padding * 6;

	min_size.x = zt_max(min_size.x, 6);
	min_size.y = zt_max(min_size.y, 2.25f);

	zt_guiItemSetSize(window, min_size);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_GUI_DIALOG_MAX_FILES_IN_LIST
#define ZT_GUI_DIALOG_MAX_FILES_IN_LIST	2048
#endif

// ================================================================================================================================================================================================

struct ztDialogFileSelect
{
	ztGuiItem    *text_path;
	ztGuiItem    *text_file;
	ztGuiItem    *list_drives;
	ztGuiItem    *list_files;

	ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogFileSelected_Func);
	void         *user_data;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiDialogFileSelectLoadPath(ztDialogFileSelect *file_sel, const char *path)
{
	if (!zt_directoryExists(path)) {
		if (zt_directoryExists(zt_game->game_details.app_path)) {
			_zt_guiDialogFileSelectLoadPath(file_sel, zt_game->game_details.app_path);
		}
		return;
	}

	int strlen_path = zt_strLen(path);
	if (!zt_strEndsWith(path, ztFilePathSeparatorStr)) {
		strlen_path += 1;
	}

	zt_guiListBoxClear(file_sel->list_files);

	if (zt_strFindPos(path, ztFilePathSeparatorStr, 0) != ztStrPosNotFound) {
		zt_guiListBoxAppend(file_sel->list_files, "..", nullptr);
	}

	const int files_len = 1024 * 1024;
	char *files = zt_mallocStructArray(char, files_len);

	// directories first
	zt_getDirectorySubs(path, files, files_len, false);

	ztToken tokens[ZT_GUI_DIALOG_MAX_FILES_IN_LIST];
	int tokens_count = zt_strTokenize(files, "\n", tokens, zt_elementsOf(tokens));

	int directories = tokens_count;
	zt_fiz(zt_min(ZT_GUI_DIALOG_MAX_FILES_IN_LIST, tokens_count)) {
		char file[ztFileMaxPath];
		zt_strCpy(file, ztFileMaxPath, files + tokens[i].beg + strlen_path, tokens[i].len - strlen_path);

		char dir[ztFileMaxPath] = { 0 };
		zt_strCat(dir, ztFileMaxPath, "[D] ");
		zt_strCat(dir, ztFileMaxPath, file);
		zt_guiListBoxAppend(file_sel->list_files, dir, nullptr);
	}

	files[0] = 0;
	zt_getDirectoryFiles(path, files, files_len, false);

	tokens_count = zt_strTokenize(files, "\n", tokens, zt_elementsOf(tokens));

	zt_fiz(zt_min(ZT_GUI_DIALOG_MAX_FILES_IN_LIST - directories, tokens_count)) {
		char file[ztFileMaxPath];
		zt_strCpy(file, ztFileMaxPath, files + tokens[i].beg + strlen_path, tokens[i].len - strlen_path);
		if (!zt_strEquals(file, ".") && !zt_strEquals(file, "..")) {
			zt_guiListBoxAppend(file_sel->list_files, file, nullptr);
		}
	}

	zt_guiTextEditSetValue(file_sel->text_path, path);

	zt_guiListBoxScrollToItem(file_sel->list_files, 0);

	zt_free(files);

	char mount[ztFileMaxPath];

	int pos_path = zt_strFindPos(path, ztFilePathSeparatorStr, 1);
	if (pos_path != ztStrPosNotFound) {
		zt_strCpy(mount, ztFileMaxPath, path, pos_path + 1);
		zt_strCat(mount, ztFileMaxPath, " ");

		int drive_count = zt_guiListBoxGetCount(file_sel->list_drives);
		zt_fiz(drive_count) {
			ztGuiItem *item = zt_guiListBoxGetItem(file_sel->list_drives, i);
			zt_assertReturnOnFail(item->type == ztGuiItemType_StaticText);
			if (zt_strStartsWith(item->label, mount)) {
				zt_guiListBoxSetSelected(file_sel->list_drives, i);
				break;
			}
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogFileSelectDriveListChanged, ZT_FUNC_GUI_LISTBOX_ITEM_SELECTED(_zt_guiDialogFileSelectDriveListChanged))
{
	ztDialogFileSelect *file_sel = (ztDialogFileSelect*)user_data;

	ztGuiItem *item = zt_guiListBoxGetItem(listbox, selected);
	zt_assertReturnOnFail(item->type == ztGuiItemType_StaticText);

	char mount[ztFileMaxPath];
	zt_strGetBetween(mount, ztFileMaxPath, item->label, "", " ");

	if (zt_directoryExists(mount)) {
		_zt_guiDialogFileSelectLoadPath(file_sel, mount);
	}
	else {
		_zt_guiDialogFileSelectLoadPath(file_sel, file_sel->text_path->textedit.text_buffer);
	}

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogFileSelectFileListChanged, ZT_FUNC_GUI_LISTBOX_ITEM_SELECTED(_zt_guiDialogFileSelectFileListChanged))
{
	ztDialogFileSelect *file_sel = (ztDialogFileSelect*)user_data;

	ztGuiItem *item = zt_guiListBoxGetItem(listbox, selected);
	zt_assertReturnOnFail(item->type == ztGuiItemType_StaticText);

	if (zt_strEquals(item->label, "..")) {
		char path[ztFileMaxPath];
		zt_guiTextEditGetValue(file_sel->text_path, path, ztFileMaxPath);

		int last_pos = -1;
		if (zt_strEndsWith(path, ztFilePathSeparatorStr)) {
			last_pos = zt_strFindLastPos(path, ztFilePathSeparatorStr);
		}
		last_pos = zt_strFindLastPos(path, ztFilePathSeparatorStr, last_pos);
		path[last_pos] = 0;

		_zt_guiDialogFileSelectLoadPath(file_sel, path);
	}
	else if (zt_strStartsWith(item->label, "[D] ")) {
		char path[ztFileMaxPath];
		zt_guiTextEditGetValue(file_sel->text_path, path, ztFileMaxPath);

		zt_strCat(path, ztFileMaxPath, ztFilePathSeparatorStr);
		zt_strCat(path, ztFileMaxPath, item->label + 4);

		_zt_guiDialogFileSelectLoadPath(file_sel, path);
	}
	else {
		zt_guiTextEditSetValue(file_sel->text_file, item->label);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogFileSelectButtonSelect, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDialogFileSelectButtonSelect))
{
	ztDialogFileSelect *file_sel = (ztDialogFileSelect*)user_data;

	if (zt_strLen(file_sel->text_file->textedit.text_buffer) == 0) {
		return;
	}

	if (ZT_FUNCTION_POINTER_IS_VALID(file_sel->callback)) {
		char path[ztFileMaxPath] = { 0 };
		zt_fileConcatFileToPath(path, ztFileMaxPath, file_sel->text_path->textedit.text_buffer, file_sel->text_file->textedit.text_buffer);

		ZT_FUNCTION_POINTER_ACCESS(file_sel->callback, zt_guiDialogFileSelected_Func)(path, file_sel->user_data);
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogFileSelectButtonCancel, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDialogFileSelectButtonCancel))
{
	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

void zt_guiDialogFileSelect(const char *title, i32 flags, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogFileSelected_Func), void *user_data, char *start_dir)
{
	ztGuiItem *window = zt_guiMakeWindow(title, ztGuiWindowBehaviorFlags_Default | ztGuiWindowBehaviorFlags_Modal);
	zt_guiItemSetSize(window, zt_vec2(12, 7));

	ztDialogFileSelect *file_sel = zt_mallocStructArena(ztDialogFileSelect, window->gm->arena);
	zt_guiItemSetUserData(window, file_sel);

	file_sel->callback = callback;
	file_sel->user_data = user_data;

	zt_guiMakePanel(window, 0, file_sel, window->gm->arena); // so the structure is deleted on close

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	ztGuiTheme *theme = zt_guiItemGetTheme(window);
	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, window);

	// up button, path text
	{
		ztGuiItem *top_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, top_sizer, 0, padding);

		ztGuiItem *text_path = zt_guiMakeTextEdit(sizer, nullptr, ztGuiTextEditBehaviorFlags_ReadOnly, ztFileMaxPath);
		zt_guiSizerAddItem(top_sizer, text_path, 1, padding);

		file_sel->text_path = text_path;
	}

	// drive list, current directory listing
	{
		ztGuiItem *mid_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, mid_sizer, 1, padding);

		ztDrive drives[26];

		ztGuiItem *list_drives = zt_guiMakeListBox(mid_sizer, 0, zt_elementsOf(drives));
		file_sel->list_drives = list_drives;
		zt_guiListBoxSetCallback(list_drives, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogFileSelectDriveListChanged), file_sel);

		int drives_count = zt_driveGetDetails(drives, zt_elementsOf(drives));
		ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_FontID, list_drives);

		r32 max_width = 0;
		zt_fiz(zt_min(drives_count, zt_elementsOf(drives))) {
			char drive_name[128] = { 0 };
			zt_strCat(drive_name, zt_elementsOf(drive_name), drives[i].mount);
			zt_strCat(drive_name, zt_elementsOf(drive_name), " ");

			if (drives[i].name[0] != 0 && !zt_strEquals(drives[i].name, drives[i].mount)) {
				zt_strCat(drive_name, zt_elementsOf(drive_name), drives[i].name);
			}

			zt_guiListBoxAppend(list_drives, drive_name, nullptr);

			max_width = zt_max(max_width, zt_fontGetExtents(font, drive_name).x);
		}

		list_drives->size.x = max_width + padding * 2 + zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarMinWidth, list_drives);
		zt_guiSizerAddItem(mid_sizer, list_drives, 0, padding);

		{
			ztGuiItem *mid_right_sizer = zt_guiMakeSizer(mid_sizer, ztGuiItemOrient_Vert);
			zt_guiSizerAddItem(mid_sizer, mid_right_sizer, 1, padding);

			ztGuiItem *list_directory = zt_guiMakeListBox(mid_right_sizer, 0, ZT_GUI_DIALOG_MAX_FILES_IN_LIST + 1);
			zt_guiListBoxSetCallback(list_directory, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogFileSelectFileListChanged), file_sel);
			zt_guiSizerAddItem(mid_right_sizer, list_directory, 1, 0);
			zt_guiSizerAddStretcher(mid_right_sizer, 0, padding);
			file_sel->list_files = list_directory;

			ztGuiItem *file_sizer = zt_guiMakeSizer(mid_right_sizer, ztGuiItemOrient_Horz);
			ztGuiItem *lbl_file = zt_guiMakeStaticText(file_sizer, "File: ");
			ztGuiItem *text_file = zt_guiMakeTextEdit(file_sizer, "", 0, ztFileMaxPath);

			file_sel->text_file = text_file;

			zt_guiSizerAddItem(mid_right_sizer, file_sizer, 0, 0);
			zt_guiSizerAddItem(file_sizer, lbl_file, 0, padding);
			zt_guiSizerAddItem(file_sizer, text_file, 1, 0);

			ztGuiItem *button_sizer = zt_guiMakeSizer(mid_right_sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(mid_right_sizer, button_sizer, 0, padding, ztAlign_Right, 0);

			ztGuiItem *button_select = zt_guiMakeButton(button_sizer, zt_bitIsSet(flags, ztGuiDialogFileSelectFlags_Open) ? "Open" : "Save");
			zt_guiButtonSetCallback(button_select, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogFileSelectButtonSelect), file_sel);
			ztGuiItem *button_cancel = zt_guiMakeButton(button_sizer, "Cancel");
			zt_guiButtonSetCallback(button_cancel, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogFileSelectButtonCancel), file_sel);
			zt_guiSizerAddItem(button_sizer, button_select, 1, padding);
			zt_guiSizerAddItem(button_sizer, button_cancel, 1, padding);
		}

	}

	_zt_guiDialogFileSelectLoadPath(file_sel, start_dir == nullptr ? zt_game->game_details.app_path : start_dir);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztGuiColorPickerData
{
	ztVec4i       color_rgba;
	ztVec4i       color_rgba_save;
	ztVec4        color_rgba_work;
	ztVec4        color_full;
	ztVec4        color_orig;
	i32           cp_behavior_flags;

	ztTextureID   tex_details;
	bool          recalc_tex;

	bool          black_at_bottom_right;

	ztVec2        mpos_click;
	int           dragging;

	ztGuiItem    *curr_clr;

	ztVec4       *color_val;

	ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogColorPickerSelected_Func);
	void                   *user_data;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerPanelPreviewRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiColorPickerPanelPreviewRender))
{
	ztColor colors[4] = { item->color, item->color, item->color, item->color };
	zt_drawListPushTexture(draw_list, ztTextureDefault);
	zt_drawListAddFilledRect2D(draw_list, item->pos + offset, item->size, ztVec2::zero, ztVec2::one, colors);
	zt_drawListPopTexture(draw_list);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerPanelInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiColorPickerPanelInputMouse))
{
	ztGuiColorPickerData *picker_data = (ztGuiColorPickerData*)user_data;

	if (input_mouse->leftPressed()) {
		picker_data->mpos_click = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		return true;
	}
	else if (input_mouse->leftJustReleased()){
		picker_data->mpos_click = ztVec2::min;
		picker_data->dragging = -1;
		return false;
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerPanelCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiColorPickerPanelCleanup))
{
	ztGuiColorPickerData *picker_data = (ztGuiColorPickerData*)user_data;
	zt_textureFree(picker_data->tex_details);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerPanelRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiColorPickerPanelRender))
{
	ztGuiColorPickerData *picker_data = (ztGuiColorPickerData*)user_data;

	bool updated_color = false;

	if (picker_data->color_rgba_save != picker_data->color_rgba) {
		picker_data->color_rgba_save = picker_data->color_rgba;
		picker_data->color_rgba_work = zt_vec4(picker_data->color_rgba.x / 255.f, picker_data->color_rgba.y / 255.f, picker_data->color_rgba.z / 255.f, picker_data->color_rgba.w / 255.f);
		picker_data->color_full = ztVec4::min;
		picker_data->recalc_tex = true;
		updated_color = true;
	}

	if (picker_data->recalc_tex) {
		ZT_PROFILE_GUI("zt_guiColorPickerPanelRender::createTex");
		picker_data->recalc_tex = false;

		if (picker_data->color_full == ztVec4::min) {
			picker_data->color_full = zt_colorRgbToHsv(picker_data->color_rgba_work);
			picker_data->color_full.g = 1;
			picker_data->color_full.b = 1;
			picker_data->color_full = zt_colorHsvToRgb(picker_data->color_full);
		}

		ztColor color_hsv = zt_colorRgbToHsv(picker_data->color_full);

		byte pixels[256 * 256 * 4];
		zt_fyz(256) {
			color_hsv.b = y / 255.f;

			zt_fxz(256) {
				color_hsv.g = x / 255.f;

				ztColor color_rgb = zt_colorHsvToRgb(color_hsv);

				int idx = (((255 - y) * 256) + x) * 4;
				pixels[idx + 0] = zt_convertToi32Ceil(color_rgb.r * 255);
				pixels[idx + 1] = zt_convertToi32Ceil(color_rgb.g * 255);
				pixels[idx + 2] = zt_convertToi32Ceil(color_rgb.b * 255);
				pixels[idx + 3] = 255;
			}
		}

		if (picker_data->tex_details != ztInvalidID) {
			zt_textureFree(picker_data->tex_details);
		}

		picker_data->tex_details = zt_textureMakeFromPixelData(pixels, 256, 256);
	}

	// draw detail for color
	ztVec2 size = zt_vec2(4, 4);

	ztVec4 color_sel = picker_data->color_rgba_work;
	ztVec4 color_sel_hsv = zt_colorRgbToHsv(color_sel);
	ztVec4 color_full = picker_data->color_full;

	if (color_full == ztVec4::min) {
		color_full = color_sel_hsv;
		color_full.g = 1;
		color_full.b = 1;
		color_full = zt_colorHsvToRgb(color_full);
		picker_data->color_full = color_full;
	}

	picker_data->curr_clr->color = color_sel;

	r32 color_sel_x = size.x * color_sel_hsv.g;
	r32 color_sel_y = size.y * color_sel_hsv.b;

	if (picker_data->black_at_bottom_right) {
		color_sel_x = size.x;
	}

	r32 hsv_sel_y = size.y * (zt_colorRgbToHsv(color_full).r / 360);
	r32 alp_sel_y = size.y * color_sel.a;

	r32 ppu = zt_pixelsPerUnit();
	{
		ztVec3 center = zt_vec3(offset + item->pos, 0);

		center.x -= .5f;

		ztSprite sprite = zt_spriteMake(picker_data->tex_details, 0, 0, 256, 256);
		zt_drawListAddSprite(draw_list, &sprite, center);

		zt_drawListPushColor(draw_list, ztColor_White);
		zt_drawListAddEmptyCircle(draw_list, center + zt_vec3(size.x / -2 + color_sel_x, size.y / -2 + color_sel_y, 0), 5 / ppu, 10);
		zt_drawListAddEmptyRect(draw_list, center, zt_vec2(size.y, size.y));
		zt_drawListPopColor(draw_list);

		if (picker_data->dragging == 0 || (picker_data->mpos_click != ztVec2::min && zt_collisionPointInRect(picker_data->mpos_click, center.xy, size + zt_vec2(6 / ppu, 6 / ppu)) && picker_data->dragging == -1)) {
			picker_data->dragging = 0;
			r32 pct_y = zt_clamp((picker_data->mpos_click.y - (center.y - size.y / 2)) / size.y, 0, 1);
			r32 pct_x = zt_clamp((picker_data->mpos_click.x - (center.x - size.x / 2)) / size.x, 0, 1);

			ztColor clr_new = zt_colorRgbToHsv(color_full);
			clr_new.g = pct_x;
			clr_new.b = pct_y;
			clr_new = zt_colorHsvToRgb(clr_new);

			picker_data->black_at_bottom_right = clr_new == ztColor_Black && picker_data->mpos_click.x > center.x;

			picker_data->color_rgba_work = clr_new;
			picker_data->color_rgba_save = picker_data->color_rgba = zt_vec4i(zt_convertToi32Ceil(clr_new.r * 255), zt_convertToi32Ceil(clr_new.g * 255), zt_convertToi32Ceil(clr_new.b * 255), zt_convertToi32Ceil(clr_new.a * 255));

			updated_color = true;
		}
	}

	// draw hue and alpha gradients
	zt_fxz(2) {
		ztVec3 center = zt_vec3(offset + item->pos, 0);
		center.x += 1.8f + (x * .5f);
		r32 width = .35f;

		ztColor colors[] = {
			ztColor_Red,
			ztColor_Magenta,
			ztColor_Blue,
			ztColor_Cyan,
			ztColor_Green,
			ztColor_Yellow,
			ztColor_Red,
		};

		int colors_count = zt_elementsOf(colors);

		if (x == 1) {
			if (!zt_bitIsSet(item->behavior_flags, ztGuiColorPickerBehaviorFlags_IncludesAlpha)) {
				break;
			}
			colors[0] = ztColor_White;
			colors[1] = ztColor_Black;
			colors_count = 2;
		}

		r32 height_per = size.y / (colors_count - 1);

		ztVec3 start = zt_vec3(center.x, center.y + ((size.y / 2) - (height_per / 2)), 0);

		zt_drawListPushTexture(draw_list, ztTextureDefault);
		zt_drawListPushBlendMode(draw_list, ztRendererBlendMode_One, ztRendererBlendMode_OneMinusDestColor);

		zt_fiz(colors_count - 1) {
			ztColor colors_this[] = {
				colors[i], colors[i + 1], colors[i + 1], colors[i]
			};

			zt_drawListAddFilledRect2D(draw_list, start, zt_vec2(width, height_per), ztVec2::zero, ztVec2::one, colors_this);

			start.y -= height_per;
		}
		zt_drawListPopBlendMode(draw_list);
		zt_drawListPopTexture(draw_list);

		r32 sel_y = x == 0 ? hsv_sel_y : alp_sel_y;

		zt_drawListPushColor(draw_list, ztColor_White);
		zt_drawListAddEmptyRect(draw_list, center + zt_vec3(0, size.y / -2 + sel_y, 0), zt_vec2(width + 4 / ppu, 5 / ppu));
		zt_drawListAddEmptyRect(draw_list, center, zt_vec2(width, size.y));
		zt_drawListPopColor(draw_list);

		if (picker_data->dragging == 1 + x || (picker_data->mpos_click != ztVec2::min && zt_collisionPointInRect(picker_data->mpos_click, center.xy, zt_vec2(width, size.y)) && picker_data->dragging == -1)) {
			picker_data->dragging = 1 + x;
			r32 pct_y = zt_clamp((picker_data->mpos_click.y - (center.y - size.y / 2)) / size.y, 0, .9999f);

			ztColor clr_new;
			if (x == 0) {
				clr_new = color_sel_hsv;
				clr_new.r = 360 * pct_y;
				clr_new = zt_colorHsvToRgb(clr_new);

				color_full = zt_colorRgbToHsv(color_full);
				color_full.r = 360 * pct_y;
				picker_data->color_full = zt_colorHsvToRgb(color_full);
				picker_data->recalc_tex = true;
			}
			else {
				clr_new = picker_data->color_rgba_work;
				clr_new.a = pct_y;
			}

			picker_data->color_rgba_work = clr_new;
			picker_data->color_rgba_save = picker_data->color_rgba = zt_vec4i(zt_convertToi32Ceil(clr_new.r * 255), zt_convertToi32Ceil(clr_new.g * 255), zt_convertToi32Ceil(clr_new.b * 255), zt_convertToi32Ceil(clr_new.a * 255));

			updated_color = true;
		}
	}
	if (updated_color && zt_bitIsSet(picker_data->cp_behavior_flags, ztGuiColorPickerBehaviorFlags_LiveEdit) && picker_data->color_val != nullptr) {
		*picker_data->color_val = picker_data->color_rgba_work;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerButtonOk, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiColorPickerButtonOk))
{
	ztGuiColorPickerData *picker_data = (ztGuiColorPickerData*)user_data;
	if (picker_data->color_val) {
		*picker_data->color_val = picker_data->color_rgba_work;
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));

	if (ZT_FUNCTION_POINTER_IS_VALID(picker_data->callback)) {
		ZT_FUNCTION_POINTER_ACCESS(picker_data->callback, zt_guiDialogColorPickerSelected_Func)(picker_data->color_rgba_work, picker_data->user_data);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiColorPickerButtonCancel, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiColorPickerButtonCancel))
{
	ztGuiColorPickerData *picker_data = (ztGuiColorPickerData*)user_data;
	if (picker_data->color_val && zt_bitIsSet(picker_data->cp_behavior_flags, ztGuiColorPickerBehaviorFlags_LiveEdit)) {
		*picker_data->color_val = picker_data->color_orig;
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

void zt_guiDialogColorPicker(ztColor *selected_color, i32 behavior_flags, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogColorPickerSelected_Func), void *user_data, const char *window_title)
{
	ztGuiItem *window = zt_guiMakeWindow(window_title, ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_Modal);

	zt_guiItemSetSize(window, zt_vec2(5.5f, 6.f));

	ztGuiColorPickerData *picker_data = zt_mallocStructArena(ztGuiColorPickerData, window->gm->arena);
	zt_guiMakePanel(window, 0, picker_data, window->gm->arena);

	r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(window), ztGuiThemeValue_r32_Padding, window);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	ztGuiItem *panel_picker = zt_guiMakePanel(sizer, ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_WantsFocus);
	zt_guiSizerAddItem(sizer, panel_picker, 1, padding, ztAlign_Center, 0);

	zt_guiItemSetSize(panel_picker, zt_vec2(5, 4));
	zt_guiItemSetMinSize(panel_picker, zt_vec2(5, 4));

	panel_picker->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerPanelInputMouse);
	panel_picker->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerPanelRender);
	panel_picker->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerPanelCleanup);
	panel_picker->functions.user_data   = picker_data;

	ztGuiItem *sizer_btm = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_btm, 0, 0, ztAlign_Center, ztGuiItemOrient_Horz);

	ztGuiItem *ed_rgba;
	picker_data->color_rgba_work = *selected_color;
	picker_data->color_rgba = zt_vec4i(zt_convertToi32Ceil(selected_color->r * 255), zt_convertToi32Ceil(selected_color->g * 255), zt_convertToi32Ceil(selected_color->b * 255), zt_convertToi32Ceil(selected_color->a * 255));
	picker_data->color_rgba_save = picker_data->color_rgba;
	picker_data->color_full = ztVec4::min;
	picker_data->color_orig = *selected_color;
	picker_data->cp_behavior_flags = behavior_flags;
	picker_data->black_at_bottom_right = false;
	picker_data->mpos_click = ztVec2::min;
	picker_data->dragging = -1;
	picker_data->color_val = selected_color;
	picker_data->tex_details = ztInvalidID;
	picker_data->recalc_tex = true;
	picker_data->callback = callback;
	picker_data->user_data = user_data;

	if (zt_bitIsSet(picker_data->cp_behavior_flags, ztGuiColorPickerBehaviorFlags_IncludesAlpha)) {
		ed_rgba = zt_guiMakeEditor(sizer, nullptr, &picker_data->color_rgba, zt_vec4i(0, 0, 0, 0), zt_vec4i(255, 255, 255, 255), 1, false, "R", "G", "B", "A");
	}
	else {
		ed_rgba = zt_guiMakeEditor(sizer, nullptr, &picker_data->color_rgba.xyz, zt_vec3i(0, 0, 0), zt_vec3i(255, 255, 255), 1, false, "R", "G", "B");
	}

	zt_guiSizerAddItem(sizer_btm, ed_rgba, 1, padding, ztAlign_Left | ztAlign_VertCenter, ztGuiItemOrient_Horz);

	zt_guiSizerAddStretcher(sizer_btm, 0, padding);

	ztGuiItem *curr_clr = zt_guiMakePanel(sizer_btm);
	curr_clr->color = *selected_color;
	curr_clr->functions.render = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerPanelPreviewRender);
	zt_guiSizerAddItem(sizer_btm, curr_clr, 0, 0, 0, 0);
	curr_clr->size.x = .5f;
	curr_clr->size.y = zt_guiThemeGetRValue(zt_guiItemGetTheme(curr_clr), ztGuiThemeValue_r32_TextEditDefaultH, curr_clr);


	picker_data->curr_clr = curr_clr;

	ztGuiItem *prev_clr = zt_guiMakePanel(sizer_btm);
	prev_clr->color = *selected_color;
	prev_clr->functions.render = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerPanelPreviewRender);
	zt_guiSizerAddItem(sizer_btm, prev_clr, 0, 0, 0, 0);
	prev_clr->size.x = .5f;
	prev_clr->size.y = curr_clr->size.y;


	ztGuiItem *sizer_btns = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_btns, 0, 0);
	zt_guiSizerAddStretcher(sizer_btns, 1);

	ztGuiItem *button_ok = zt_guiMakeButton(sizer_btns, nullptr);
	ztSprite sprite_ok = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 0, 16, 16);
	zt_guiButtonSetIcon(button_ok, &sprite_ok);
	zt_guiButtonSetCallback(button_ok, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerButtonOk), picker_data);
	button_ok->size.x *= 2;
	zt_guiSizerAddItem(sizer_btns, button_ok, 0, padding);

	ztGuiItem *button_cancel = zt_guiMakeButton(sizer_btns, nullptr);
	ztSprite sprite_cancel = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 16, 16, 16);
	zt_guiButtonSetIcon(button_cancel, &sprite_cancel);
	zt_guiButtonSetCallback(button_cancel, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiColorPickerButtonCancel), picker_data);
	button_cancel->size.x *= 2;
	zt_guiSizerAddItem(sizer_btns, button_cancel, 0, padding);

	zt_guiSizerAddStretcher(sizer_btns, 1);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztGuiColorGradientEditor
{
	ztColorGradient2        gradient;
	ztColorGradient2       *gradient_val;
	ztColorGradient2        gradient_orig;

	ztGuiItem              *panel_alpha;
	ztGuiItem              *panel_color;

	ztGuiItem              *ed_alpha_val;
	ztGuiItem              *ed_alpha_loc;

	ztGuiItem              *ed_color_val;
	ztGuiItem              *ed_color_loc;

	ztVec2                  mpos_click;
	ztVec2                  mpos_click_offset;
	int                     dragging;

	int                     active_control;

	ztTextureID             tex_background;

	i32                     gp_behavior_flags;
	ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogColorGradientEditorComplete_Func);
	void                   *user_data;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientButtonDeleteColor, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_colorGradientButtonDeleteColor))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	if (grad_editor->active_control >= 0) {
		if (grad_editor->active_control == 0) {
			grad_editor->gradient.color_vals[0] = grad_editor->gradient.color_vals[1];
		}
		else if (grad_editor->active_control == grad_editor->gradient.color_entries - 1) {
			grad_editor->gradient.color_vals[grad_editor->gradient.color_entries - 1] = grad_editor->gradient.color_vals[grad_editor->gradient.color_entries - 2];
		}
		else {
			zt_guiColorPickerSetLiveValue(grad_editor->ed_color_val, nullptr);

			for (int i = grad_editor->active_control; i < grad_editor->gradient.color_entries; ++i) {
				grad_editor->gradient.color_vals[i] = grad_editor->gradient.color_vals[i + 1];
				grad_editor->gradient.color_locs[i] = grad_editor->gradient.color_locs[i + 1];
			}
			grad_editor->gradient.color_entries -= 1;
		}

		grad_editor->active_control = -1;
		zt_guiItemHide(grad_editor->panel_alpha);
		zt_guiItemHide(grad_editor->panel_color);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientButtonDeleteAlpha, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_colorGradientButtonDeleteAlpha))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	int active_control = grad_editor->active_control - 1000;
	if (active_control >= 0) {
		if (active_control == 0) {
			grad_editor->gradient.alpha_vals[0] = grad_editor->gradient.alpha_vals[1];
		}
		else if (active_control == grad_editor->gradient.alpha_entries - 1) {
			grad_editor->gradient.alpha_vals[grad_editor->gradient.alpha_entries - 1] = grad_editor->gradient.alpha_vals[grad_editor->gradient.alpha_entries - 2];
		}
		else {
			zt_guiColorPickerSetLiveValue(grad_editor->ed_color_val, nullptr);

			for (int i = active_control; i < grad_editor->gradient.alpha_entries; ++i) {
				grad_editor->gradient.alpha_vals[i] = grad_editor->gradient.alpha_vals[i + 1];
				grad_editor->gradient.alpha_locs[i] = grad_editor->gradient.alpha_locs[i + 1];
			}
			grad_editor->gradient.alpha_entries -= 1;
		}

		grad_editor->active_control = -1;
		zt_guiItemHide(grad_editor->panel_alpha);
		zt_guiItemHide(grad_editor->panel_color);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientPanelInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_colorGradientPanelInputMouse))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	if (input_mouse->leftPressed()) {
		grad_editor->mpos_click = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		return true;
	}
	else if (input_mouse->leftJustReleased()){
		grad_editor->mpos_click = ztVec2::min;
		grad_editor->dragging = -1;
		return false;
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientPanelRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_colorGradientPanelRender))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	ztVec2 center = item->pos + offset;
	ztVec2 size = item->size;
	size.x *= .9f;
	size.y = .5f;

	r32 height = size.y;

	r32 size_controls = .15f;

	ztVec3 start = zt_vec3(center.x - (size.x / 2), center.y, 0);
	r32 controls_start_x = center.x - (size.x / 2);

	zt_drawListPushTexture(draw_list, ztTextureDefault);
	ztSprite sprite_back = zt_spriteMake(grad_editor->tex_background, 0, 0, 32, 32);
	zt_drawListAddSpriteTiled(draw_list, &sprite_back, zt_vec3(center, 0), size);

	int active_control = grad_editor->active_control;

	{
		zt_fiz(grad_editor->gradient.alpha_entries) {
			r32 pos_x = controls_start_x + (size.x * grad_editor->gradient.alpha_locs[i]);
			ztVec2 pos_box = zt_vec2(pos_x, start.y + .35f);
			ztVec2 size_box = zt_vec2(size_controls, size_controls);
			zt_drawListAddSolidOutlinedRect2D(draw_list, pos_box, size_box, zt_color(1, 1, 1, 1) * grad_editor->gradient.alpha_vals[i], ztColor_White);

			if (grad_editor->dragging == i + 1000) {
				r32 pos_move_to = grad_editor->mpos_click.x - grad_editor->mpos_click_offset.x;
				r32 pct_move_to = zt_clamp((pos_move_to - controls_start_x) / size.x, 0, 1);
				grad_editor->gradient.alpha_locs[i] = pct_move_to;
			}
			else if (grad_editor->dragging == -1 && grad_editor->mpos_click != ztVec2::min && zt_collisionPointInRect(grad_editor->mpos_click, pos_box, size_box)) {
				grad_editor->dragging = i != 0 && i < grad_editor->gradient.alpha_entries - 1 ? i + 1000 : -2;
				grad_editor->mpos_click_offset = grad_editor->mpos_click - pos_box;
				grad_editor->active_control = i + 1000;
			}
		}

		ztVec2 pos_box = zt_vec2(center.x, start.y + .35f);
		ztVec2 size_box = zt_vec2(size.x, .25f);
		if (grad_editor->dragging == -1 && grad_editor->mpos_click != ztVec2::min && zt_collisionPointInRect(grad_editor->mpos_click, pos_box, size_box) && grad_editor->gradient.alpha_entries < zt_elementsOf(grad_editor->gradient.alpha_locs)) {
			r32 loc = (grad_editor->mpos_click.x - (pos_box.x - size_box.x / 2.f)) / size_box.x;

			int idx = grad_editor->gradient.alpha_entries++;
			grad_editor->gradient.alpha_vals[idx] = 1;
			grad_editor->gradient.alpha_locs[idx] = loc;
			grad_editor->dragging = idx + 1000;
			grad_editor->mpos_click_offset = ztVec2::zero;
			grad_editor->active_control = idx + 1000;
			active_control = -1;
		}
	}

	{
		zt_fiz(grad_editor->gradient.color_entries) {
			r32 pos_x = controls_start_x + (size.x * grad_editor->gradient.color_locs[i]);
			ztVec2 pos_box = zt_vec2(pos_x, start.y - .35f);
			ztVec2 size_box = zt_vec2(size_controls, size_controls);
			zt_drawListAddSolidOutlinedRect2D(draw_list, pos_box, size_box, grad_editor->gradient.color_vals[i], ztColor_White);

			if (grad_editor->dragging == i) {
				r32 pos_move_to = grad_editor->mpos_click.x - grad_editor->mpos_click_offset.x;
				r32 pct_move_to = zt_clamp((pos_move_to - controls_start_x) / size.x, 0, 1);
				grad_editor->gradient.color_locs[i] = pct_move_to;
			}
			else if (grad_editor->dragging == -1 && grad_editor->mpos_click != ztVec2::min && zt_collisionPointInRect(grad_editor->mpos_click, pos_box, size_box)) {
				grad_editor->dragging = i != 0 && i < grad_editor->gradient.color_entries - 1 ? i : -2;
				grad_editor->mpos_click_offset = grad_editor->mpos_click - pos_box;
				grad_editor->active_control = i;
			}
		}

		ztVec2 pos_box = zt_vec2(center.x, start.y - .35f);
		ztVec2 size_box = zt_vec2(size.x, .25f);
		if (grad_editor->dragging == -1 && grad_editor->mpos_click != ztVec2::min && zt_collisionPointInRect(grad_editor->mpos_click, pos_box, size_box) && grad_editor->gradient.color_entries < zt_elementsOf(grad_editor->gradient.color_locs)) {
			r32 loc = (grad_editor->mpos_click.x - (pos_box.x - size_box.x / 2.f)) / size_box.x;

			int idx = grad_editor->gradient.color_entries++;
			grad_editor->gradient.color_vals[idx] = ztColor_White;
			grad_editor->gradient.color_locs[idx] = loc;
			grad_editor->dragging = idx;
			grad_editor->mpos_click_offset = ztVec2::zero;
			grad_editor->active_control = idx;
			active_control = -1;
		}
	}

	{
		ztColor colors[ZT_COLOR_GRADIENT_MAX_VALUES * 2];
		r32 locations[ZT_COLOR_GRADIENT_MAX_VALUES * 2];
		int colors_count = zt_colorGradientGetColors(&grad_editor->gradient, colors, locations, ZT_COLOR_GRADIENT_MAX_VALUES * 2);

		zt_fiz(colors_count - 1) {
			r32 width_this = size.x * (locations[i + 1] - locations[i]);

			ztColor colors_this[] = {
				colors[i], zt_vec4(colors[i].xyz, colors[i].a), zt_vec4(colors[i + 1].xyz, colors[i + 1].a), colors[i + 1]
			};

			zt_drawListAddFilledRect2D(draw_list, start + zt_vec3(width_this / 2, 0, 0), zt_vec2(width_this, height), ztVec2::zero, ztVec2::one, colors_this);
			start.x += width_this;
		}
	}

	zt_drawListPopTexture(draw_list);

	if (grad_editor->active_control != -1) {
		if (grad_editor->dragging > -1) {
			bool adjusted = true;
			while (adjusted) {
				adjusted = false;
				for (int i = 1; i < grad_editor->gradient.color_entries - 1; ++i) {
					if (grad_editor->gradient.color_locs[i] > grad_editor->gradient.color_locs[i + 1]) {
						zt_swap(grad_editor->gradient.color_locs[i], grad_editor->gradient.color_locs[i + 1]);
						zt_swap(grad_editor->gradient.color_vals[i], grad_editor->gradient.color_vals[i + 1]);

						if (i == grad_editor->dragging) {
							grad_editor->dragging += 1;
						}
						else if (i == grad_editor->dragging - 1) {
							grad_editor->dragging -= 1;
						}

						adjusted = true;
					}
				}
			}
			adjusted = true;
			while (adjusted) {
				adjusted = false;
				for (int i = 1; i < grad_editor->gradient.alpha_entries - 1; ++i) {
					if (grad_editor->gradient.alpha_locs[i] > grad_editor->gradient.alpha_locs[i + 1]) {
						zt_swap(grad_editor->gradient.alpha_locs[i], grad_editor->gradient.alpha_locs[i + 1]);
						zt_swap(grad_editor->gradient.alpha_vals[i], grad_editor->gradient.alpha_vals[i + 1]);

						if (i + 1000 == grad_editor->dragging) {
							grad_editor->dragging += 1;
						}
						else if (i + 1000 == grad_editor->dragging - 1) {
							grad_editor->dragging -= 1;
						}

						adjusted = true;
					}
				}
			}

			grad_editor->active_control = grad_editor->dragging;
			active_control = -1;
		}

		if (grad_editor->active_control != active_control) {
			zt_guiItemHide(grad_editor->panel_alpha);
			zt_guiItemHide(grad_editor->panel_color);

			if (grad_editor->active_control < 1000) {
				zt_guiEditorReassign(grad_editor->ed_color_loc, &grad_editor->gradient.color_locs[grad_editor->active_control]);
				zt_guiColorPickerSetLiveValue(grad_editor->ed_color_val, &grad_editor->gradient.color_vals[grad_editor->active_control]);
				zt_guiItemShow(grad_editor->panel_color);
			}
			else {
				zt_guiEditorReassign(grad_editor->ed_alpha_loc, &grad_editor->gradient.alpha_locs[grad_editor->active_control - 1000]);
				zt_guiEditorReassign(grad_editor->ed_alpha_val, &grad_editor->gradient.alpha_vals[grad_editor->active_control - 1000]);
				zt_guiItemShow(grad_editor->panel_alpha);
			}

			zt_guiSizerRecalc(item->parent ? item->parent : item);
		}
	}

	if (grad_editor->gradient_val && zt_bitIsSet(grad_editor->gp_behavior_flags, ztGuiGradientPickerBehaviorFlags_LiveEdit) && !zt_colorGradientIsEqual(grad_editor->gradient_val, &grad_editor->gradient)) {
		zt_memCpy(grad_editor->gradient_val, zt_sizeof(ztColorGradient2), &grad_editor->gradient, zt_sizeof(ztColorGradient2));
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientPanelCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_colorGradientPanelCleanup))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	if (grad_editor->tex_background != ztInvalidID) {
		zt_textureFree(grad_editor->tex_background);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientButtonOk, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_colorGradientButtonOk))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	if (grad_editor->gradient_val) {
		zt_memCpy(grad_editor->gradient_val, zt_sizeof(ztColorGradient2), &grad_editor->gradient, zt_sizeof(ztColorGradient2));
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));

	if (ZT_FUNCTION_POINTER_IS_VALID(grad_editor->callback)) {
		ZT_FUNCTION_POINTER_ACCESS(grad_editor->callback, zt_guiDialogColorGradientEditorComplete_Func)(&grad_editor->gradient, grad_editor->user_data);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_colorGradientButtonCancel, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_colorGradientButtonCancel))
{
	ztGuiColorGradientEditor *grad_editor = (ztGuiColorGradientEditor*)user_data;

	if (grad_editor->gradient_val && zt_bitIsSet(grad_editor->gp_behavior_flags, ztGuiGradientPickerBehaviorFlags_LiveEdit)) {
		zt_memCpy(grad_editor->gradient_val, zt_sizeof(ztColorGradient2), &grad_editor->gradient_orig, zt_sizeof(ztColorGradient2));
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

void zt_guiDialogColorGradient(ztColorGradient2 *gradient, i32 behavior_flags, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogColorGradientEditorComplete_Func), void *user_data, const char *window_title)
{
	ztGuiItem *window = zt_guiMakeWindow(window_title, ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_Modal);
	zt_guiItemSetSize(window, zt_vec2(8, 4));

	r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(window), ztGuiThemeValue_r32_Padding, window);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	ztGuiColorGradientEditor *grad_editor = zt_mallocStructArena(ztGuiColorGradientEditor, window->gm->arena);

	grad_editor->mpos_click = ztVec2::min;
	grad_editor->dragging = -1;
	grad_editor->active_control = -1;
	grad_editor->callback = callback;
	grad_editor->gp_behavior_flags = behavior_flags;
	grad_editor->user_data = user_data;
	grad_editor->gradient_val = gradient;
	grad_editor->tex_background = ztInvalidID;

	if (gradient == nullptr) {
		grad_editor->gradient.alpha_vals[grad_editor->gradient.alpha_entries  ] = 1;
		grad_editor->gradient.alpha_locs[grad_editor->gradient.alpha_entries++] = 0;
		grad_editor->gradient.alpha_vals[grad_editor->gradient.alpha_entries  ] = 1;
		grad_editor->gradient.alpha_locs[grad_editor->gradient.alpha_entries++] = 1;

		grad_editor->gradient.color_vals[grad_editor->gradient.color_entries  ] = ztColor_Black;
		grad_editor->gradient.color_locs[grad_editor->gradient.color_entries++] = 0;
		grad_editor->gradient.color_vals[grad_editor->gradient.color_entries  ] = ztColor_White;
		grad_editor->gradient.color_locs[grad_editor->gradient.color_entries++] = 1;
	}
	else {
		zt_memCpy(&grad_editor->gradient, zt_sizeof(ztColorGradient2), gradient, zt_sizeof(ztColorGradient2));
	}

	zt_memCpy(&grad_editor->gradient_orig, zt_sizeof(ztColorGradient2), &grad_editor->gradient, zt_sizeof(ztColorGradient2));

	{
		int w = 32;
		int h = 32;
		byte *grid_tex = zt_mallocStructArray(byte, w * h * 4);

		zt_fyz(h) {
			zt_fxz(w) {
				int idx = ((y * w) + x) * 4;

				i32 color = ((zt_convertToi32Floor(y / 4.f) % 2) + zt_convertToi32Floor(x / 4.f)) % 2 == 0 ? 128 : 190;
				grid_tex[idx + 0] = color;
				grid_tex[idx + 1] = color;
				grid_tex[idx + 2] = color;
				grid_tex[idx + 3] = 255;
			}
		}

		ztTextureID tex = zt_textureMakeFromPixelData(grid_tex, w, h, ztTextureFlags_PixelPerfect);
		grad_editor->tex_background = tex;

		zt_free(grid_tex);
	}

	ztGuiItem *grad_panel = zt_guiMakePanel(sizer, 0, grad_editor, window->gm->arena);
	zt_guiSizerAddItem(sizer, grad_panel, 1, padding);

	grad_panel->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientPanelInputMouse);
	grad_panel->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientPanelRender);
	grad_panel->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientPanelCleanup);
	grad_panel->functions.user_data   = grad_editor;


	ztGuiItem *alpha_panel = zt_guiMakePanel(sizer);
	zt_guiSizerAddItem(sizer, alpha_panel, 0, padding, ztAlign_Center, 0);
	grad_editor->panel_alpha = alpha_panel;
	{
		ztGuiItem *panel_sizer = zt_guiMakeSizer(alpha_panel, ztGuiItemOrient_Horz, true);
		alpha_panel->min_size = zt_vec2(6, 1);

		ztGuiItem *ed_alpha = zt_guiMakeEditor(panel_sizer, "Opacity: ", &grad_editor->gradient.alpha_vals[0], 0, 1, .1f);
		grad_editor->ed_alpha_val = ed_alpha;

		ztGuiItem *ed_location = zt_guiMakeEditor(panel_sizer, "Location: ", &grad_editor->gradient.alpha_locs[0], 0, 1, .1f);
		grad_editor->ed_alpha_loc = ed_location;

		ztGuiItem *btn_delete = zt_guiMakeButton(panel_sizer, "Delete");
		zt_guiButtonSetCallback(btn_delete, ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientButtonDeleteAlpha), grad_editor);

		zt_guiSizerAddItem(panel_sizer, ed_alpha, 1, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(panel_sizer, ed_location, 1, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(panel_sizer, btn_delete, 0, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
	}
	zt_guiItemHide(grad_editor->panel_alpha);

	ztGuiItem *color_panel = zt_guiMakePanel(sizer);
	zt_guiSizerAddItem(sizer, color_panel, 0, padding, ztAlign_Center, 0);
	grad_editor->panel_color = color_panel;
	{
		ztGuiItem *panel_sizer = zt_guiMakeSizer(color_panel, ztGuiItemOrient_Horz, true);
		color_panel->min_size = zt_vec2(6, 1);

		ztGuiItem *lbl_color = zt_guiMakeStaticText(panel_sizer, "Color: ");

		ztGuiItem *ed_color = zt_guiMakeColorPicker(panel_sizer, ztColor_White, ztGuiColorPickerBehaviorFlags_LiveEdit);
		grad_editor->ed_color_val = ed_color;
		zt_guiColorPickerSetLiveValue(grad_editor->ed_color_val, &grad_editor->gradient.color_vals[0]);

		ztGuiItem *ed_location = zt_guiMakeEditor(panel_sizer, "Location: ", &grad_editor->gradient.color_locs[0], 0, 1, .1f);
		grad_editor->ed_color_loc = ed_location;

		ztGuiItem *btn_delete = zt_guiMakeButton(panel_sizer, "Delete");
		zt_guiButtonSetCallback(btn_delete, ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientButtonDeleteColor), grad_editor);

		zt_guiSizerAddItem(panel_sizer, lbl_color, 0, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(panel_sizer, ed_color, 0, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(panel_sizer, ed_location, 1, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(panel_sizer, btn_delete, 0, padding, ztAlign_VertCenter, ztGuiItemOrient_Horz);
	}
	grad_editor->active_control = 0;

	{
		ztGuiItem *sizer_btns = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, sizer_btns, 0, 0);
		zt_guiSizerAddStretcher(sizer_btns, 1);

		ztGuiItem *button_ok = zt_guiMakeButton(sizer_btns, nullptr);
		ztSprite sprite_ok = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 0, 16, 16);
		zt_guiButtonSetIcon(button_ok, &sprite_ok);
		zt_guiButtonSetCallback(button_ok, ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientButtonOk), grad_editor);
		button_ok->size.x *= 2;
		zt_guiSizerAddItem(sizer_btns, button_ok, 0, padding);

		ztGuiItem *button_cancel = zt_guiMakeButton(sizer_btns, nullptr);
		ztSprite sprite_cancel = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 16, 16, 16);
		zt_guiButtonSetIcon(button_cancel, &sprite_cancel);
		zt_guiButtonSetCallback(button_cancel, ZT_FUNCTION_POINTER_TO_VAR(_zt_colorGradientButtonCancel), grad_editor);
		button_cancel->size.x *= 2;
		zt_guiSizerAddItem(sizer_btns, button_cancel, 0, padding);

		zt_guiSizerAddStretcher(sizer_btns, 1);
	}
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztGuiAnimCurveEditor
{
	ztAnimCurve             curve;
	ztAnimCurve            *curve_val;
	ztAnimCurve             curve_orig;

	ztGuiItem              *type_combo;
	ztGuiItem              *ease_in_label;
	ztGuiItem              *ease_in_combo;
	ztGuiItem              *ease_out_label;
	ztGuiItem              *ease_out_combo;

	int                     active_point;
	int                     active_control_point;

	ztVec2                  mpos_dragging;
	bool                    just_clicked;
	ztVec2                  add_point_at;
	ztVec2                  add_point_at_clicked;
	bool                    dragging_point;
	ztVec2                  dragging_point_offset;

	i32                     ac_behavior_flags;

	ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogAnimCurveEditorComplete_Func);
	void                   *user_data;
};


// ================================================================================================================================================================================================

ztInternal void _zt_animCurveUpdateGui(ztGuiAnimCurveEditor *curve_editor)
{
	zt_guiComboBoxSetSelected(curve_editor->type_combo, curve_editor->curve.type);

	zt_guiItemShow(curve_editor->ease_in_combo, curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseIn);
	zt_guiItemShow(curve_editor->ease_in_label, curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseIn);
	zt_guiItemShow(curve_editor->ease_out_combo, curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseOut);
	zt_guiItemShow(curve_editor->ease_out_label, curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseOut);

	if (curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseIn) {
		zt_guiComboBoxSetSelected(curve_editor->ease_in_combo, curve_editor->curve.ease_in);
	}
	if (curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseOut) {
		zt_guiComboBoxSetSelected(curve_editor->ease_out_combo, curve_editor->curve.ease_out);
	}

	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(curve_editor->ease_in_combo));

	curve_editor->active_point = -1;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveDisplayAddKeyMenu, ZT_FUNC_GUI_MENU_SELECTED(_zt_animCurveDisplayAddKeyMenu))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	curve_editor->add_point_at = curve_editor->add_point_at_clicked;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveDisplay_InputKeyboard, ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_animCurveDisplay_InputKeyboard))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	if (curve_editor->curve.type == ztAnimCurveType_Spline && curve_editor->active_point != -1 && input_keys[ztInputKeys_Delete].justPressed()) {
		if (curve_editor->active_point != 0 && curve_editor->active_point != curve_editor->curve.segments_count) {
			// merge segment active_point - 1 with active_point
			curve_editor->curve.segments[curve_editor->active_point - 1].pos_end = curve_editor->curve.segments[curve_editor->active_point].pos_end;
			curve_editor->curve.segments[curve_editor->active_point - 1].control_point_end = curve_editor->curve.segments[curve_editor->active_point].control_point_end;

			for (int i = curve_editor->active_point; i < curve_editor->curve.segments_count - 1; ++i) {
				zt_memCpy(&curve_editor->curve.segments[i], zt_sizeof(ztAnimCurveSplineSegment), &curve_editor->curve.segments[i + 1], zt_sizeof(ztAnimCurveSplineSegment));
			}
			curve_editor->curve.segments_count -= 1;
		}
	}
	if (input_keys[ztInputKeys_Control].pressed()) {
		char buffer[4096] = { 0 };
		if (input_keys[ztInputKeys_C].justPressed()) {
			zt_strCat(buffer, zt_elementsOf(buffer), "ztAnimCurve curve;\n");

			zt_strCatf(buffer, zt_elementsOf(buffer), "curve.val_max = %.4ff;\n", curve_editor->curve.val_max);
			zt_strCatf(buffer, zt_elementsOf(buffer), "curve.val_beg = %.4ff;\n", curve_editor->curve.val_beg);
			zt_strCatf(buffer, zt_elementsOf(buffer), "curve.val_end = %.4ff;\n", curve_editor->curve.val_end);

			const char *ease_funcs[ztAnimCurveEaseType_MAX] = {
				"ztAnimCurveEaseType_Linear",
				"ztAnimCurveEaseType_Back",
				"ztAnimCurveEaseType_Bounce",
				"ztAnimCurveEaseType_Circ",
				"ztAnimCurveEaseType_Cubic",
				"ztAnimCurveEaseType_Elastic",
				"ztAnimCurveEaseType_Expo",
				"ztAnimCurveEaseType_Quad",
				"ztAnimCurveEaseType_Quart",
				"ztAnimCurveEaseType_Quint",
				"ztAnimCurveEaseType_Sine",
			};

			switch (curve_editor->curve.type)
			{
				case ztAnimCurveType_Linear: {
					zt_strCat(buffer, zt_elementsOf(buffer), "curve.type = ztAnimCurveType_Linear;\n");
				} break;

				case ztAnimCurveType_EaseIn: {
					zt_strCat(buffer, zt_elementsOf(buffer), "curve.type = ztAnimCurveType_EaseIn;\n");
					zt_strCatf(buffer, zt_elementsOf(buffer), "curve.ease_in = %s;\n", ease_funcs[curve_editor->curve.ease_in]);
				} break;

				case ztAnimCurveType_EaseOut: {
					zt_strCat(buffer, zt_elementsOf(buffer), "curve.type = ztAnimCurveType_EaseOut;\n");
					zt_strCatf(buffer, zt_elementsOf(buffer), "curve.ease_out = %s;\n", ease_funcs[curve_editor->curve.ease_out]);
				} break;

				case ztAnimCurveType_EaseInOut: {
					zt_strCat(buffer, zt_elementsOf(buffer), "curve.type = ztAnimCurveType_EaseInOut;\n");
					zt_strCatf(buffer, zt_elementsOf(buffer), "curve.ease_in = %s;\n", ease_funcs[curve_editor->curve.ease_in]);
					zt_strCatf(buffer, zt_elementsOf(buffer), "curve.ease_out = %s;\n", ease_funcs[curve_editor->curve.ease_out]);
				} break;

				case ztAnimCurveType_Spline: {
					zt_strCat(buffer, zt_elementsOf(buffer), "curve.type = ztAnimCurveType_Spline;\n");

					zt_strCatf(buffer, zt_elementsOf(buffer), "curve.segments_count = %d;\n", curve_editor->curve.segments_count);
					zt_fiz(curve_editor->curve.segments_count) {
						zt_strCatf(buffer, zt_elementsOf(buffer), "curve.segments[%d].pos_beg = zt_vec2(%.4ff, %.4ff);\n", i, curve_editor->curve.segments[i].pos_beg.x, curve_editor->curve.segments[i].pos_beg.y);
						zt_strCatf(buffer, zt_elementsOf(buffer), "curve.segments[%d].pos_end = zt_vec2(%.4ff, %.4ff);\n", i, curve_editor->curve.segments[i].pos_end.x, curve_editor->curve.segments[i].pos_end.y);
						zt_strCatf(buffer, zt_elementsOf(buffer), "curve.segments[%d].control_point_beg = zt_vec2(%.4ff, %.4ff);\n", i, curve_editor->curve.segments[i].control_point_beg.x, curve_editor->curve.segments[i].control_point_beg.y);
						zt_strCatf(buffer, zt_elementsOf(buffer), "curve.segments[%d].control_point_end = zt_vec2(%.4ff, %.4ff);\n", i, curve_editor->curve.segments[i].control_point_end.x, curve_editor->curve.segments[i].control_point_end.y);
					}

				} break;
			}

			char base64[zt_sizeof(ztAnimCurve) * 2];
			zt_base64Encode((byte*)&curve_editor->curve, zt_sizeof(ztAnimCurve), base64, zt_elementsOf(base64));
			zt_strCat(buffer, zt_elementsOf(buffer), "// ztAnimCurveData:");
			zt_strCat(buffer, zt_elementsOf(buffer), base64);
			zt_strCat(buffer, zt_elementsOf(buffer), "\n");

			zt_clipboardSendPlainText(buffer);
		}
		else if(input_keys[ztInputKeys_V].justPressed()) {
			int chars_read = 0;
			if (zt_clipboardReadPlainText(buffer, zt_elementsOf(buffer), &chars_read)) {
				if (zt_strStartsWith(buffer, "ztAnimCurveData:")) {
					byte curve_data[zt_sizeof(ztAnimCurve)];
					int size = zt_base64Decode(buffer + 16, chars_read, curve_data, zt_elementsOf(curve_data));
					if (size == zt_sizeof(ztAnimCurve)) {
						zt_memCpy(&curve_editor->curve, zt_sizeof(ztAnimCurve), curve_data, zt_sizeof(ztAnimCurve));
						_zt_animCurveUpdateGui(curve_editor);
					}
				}
			}
		}
	}


	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveDisplay_InputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_animCurveDisplay_InputMouse))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	if (input_mouse->leftPressed()) {
		curve_editor->just_clicked = input_mouse->leftJustPressed();
		curve_editor->mpos_dragging = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		return true;
	}
	else {
		curve_editor->mpos_dragging = ztVec2::min;
		curve_editor->active_control_point = -1;
		curve_editor->dragging_point = false;
	}

	if (curve_editor->curve.type == ztAnimCurveType_Spline && input_mouse->rightJustReleased()) {
		curve_editor->add_point_at_clicked = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
		ztGuiItem *popup = zt_guiMakeMenu(nullptr);
		zt_guiMenuAppend(popup, "Add Key Here", 0, curve_editor);
		zt_guiMenuSetCallback(popup, ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveDisplayAddKeyMenu));
		zt_guiMenuPopupAtPosition(popup, curve_editor->add_point_at_clicked);
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveDisplay_Render, ZT_FUNC_GUI_ITEM_RENDER(_zt_animCurveDisplay_Render))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	r32 padding = 3 / zt_pixelsPerUnit();

	ztVec2 center = item->pos + offset;
	zt_drawListAddSolidRect2D(draw_list, center, item->size, ztColor_DarkGray);

	center.x += .125f;
	ztVec2 size = item->size - zt_vec2(1, 1);

	zt_drawListPushColor(draw_list, ztColor_DarkGray * zt_vec4(.75f, .75f, .75f, 1));
	zt_drawListAddEmptyRect(draw_list, center, size);

	r32 each_y = size.y / 4;
	r32 vals[5] = { curve_editor->curve.val_max, curve_editor->curve.val_max / 2, 0, curve_editor->curve.val_max / -2, curve_editor->curve.val_max / -1 };
	r32 start_y = center.y + size.y / 2;
	zt_fyz(5) {
		if (y != 0 && y != 4) {
			zt_drawListAddLine(draw_list, zt_vec2(center.x - size.x / 2, start_y), zt_vec2(center.x + size.x / 2, start_y));
		}
		start_y -= each_y;
	}
	r32 each_x = size.x / 20;
	r32 start_x = center.x - size.x / 2;
	zt_fxz(21) {
		if (x != 0 && x != 20) {
			zt_drawListAddLine(draw_list, zt_vec2(start_x, center.y + size.y / 2), zt_vec2(start_x, center.y - size.y / 2));
		}
		start_x += each_x;
	}

	start_y = center.y + size.y / 2;
	zt_fyz(5) {
		const char *format_spec = curve_editor->curve.val_max <= 1 ? "%.1f" : "%.0f";
		zt_strMakePrintf(valstr, 8, format_spec, vals[y]);
		zt_drawListAddText2D(draw_list, ztFontDefault, valstr, zt_vec2(center.x - ((size.x / 2) + padding * 2), start_y), ztAlign_Right, ztAnchor_Right);

		start_y -= each_y;
	}

	start_x = center.x - size.x / 2;
	zt_fxz(21) {
		if (x % 2 == 0) {
			zt_strMakePrintf(valstr, 8, "%.1f", x / 20.f);
			zt_drawListAddText2D(draw_list, ztFontDefault, valstr, zt_vec2(start_x, center.y - ((size.y / 2) + padding * 2)), ztAlign_Top, ztAnchor_Top);
		}
		start_x += each_x;
	}

	zt_drawListPopColor(draw_list);

	zt_drawListPushTexture(draw_list, ztTextureDefault);
	zt_drawListPushColor(draw_list, ztColor_Green);

	r32 val_beg = curve_editor->curve.val_beg / curve_editor->curve.val_max;
	r32 val_end = curve_editor->curve.val_end / curve_editor->curve.val_max;

	r32 radius = .05f;
	ztVec2 beg_pnt = zt_vec2(center.x - size.x / 2, center.y + ((size.y / 2) * val_beg));
	ztVec2 end_pnt = zt_vec2(center.x + size.x / 2, center.y + ((size.y / 2) * val_end));
	zt_drawListAddSolidCircle2D(draw_list, beg_pnt, radius, 8, ztColor_Green);
	zt_drawListAddSolidCircle2D(draw_list, end_pnt, radius, 8, ztColor_Green);

	if (zt_bitIsSet(curve_editor->ac_behavior_flags, ztGuiAnimCurveBehaviorFlags_AdjustValues)) {
		if (curve_editor->mpos_dragging != ztVec2::min && curve_editor->active_control_point == -1) {
			if (curve_editor->just_clicked) {
				if (zt_collisionPointInCircle(curve_editor->mpos_dragging, beg_pnt, .35f)) {
					curve_editor->active_point = 0;
					curve_editor->dragging_point_offset = curve_editor->mpos_dragging - beg_pnt;
				}
				if (zt_collisionPointInCircle(curve_editor->mpos_dragging, end_pnt, .35f)) {
					curve_editor->active_point = 1;
					curve_editor->dragging_point_offset = curve_editor->mpos_dragging - end_pnt;
				}
			}
			else if (curve_editor->active_point == 0) {
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(beg_pnt, 0), radius * 2, 8);

				ztVec2 diff = curve_editor->mpos_dragging - (beg_pnt + curve_editor->dragging_point_offset);
				r32 pct = diff.y / (size.y * .5f);
				curve_editor->curve.val_beg = zt_clamp(curve_editor->curve.val_beg + curve_editor->curve.val_max * pct, curve_editor->curve.val_max * -1, curve_editor->curve.val_max);
			}
			else if ((curve_editor->curve.type != ztAnimCurveType_Spline && curve_editor->active_point == 1) || (curve_editor->curve.type == ztAnimCurveType_Spline && curve_editor->active_point == curve_editor->curve.segments_count)) {
				zt_drawListAddEmptyCircle(draw_list, zt_vec3(end_pnt, 0), radius * 2, 8);

				ztVec2 diff = curve_editor->mpos_dragging - (end_pnt + curve_editor->dragging_point_offset);
				r32 pct = diff.y / (size.y * .5f);
				curve_editor->curve.val_end = zt_clamp(curve_editor->curve.val_end + curve_editor->curve.val_max * pct, curve_editor->curve.val_max * -1, curve_editor->curve.val_max);
			}

			if (curve_editor->curve.type == ztAnimCurveType_Spline) {
				curve_editor->curve.segments[0].pos_beg.y = curve_editor->curve.val_beg;
				curve_editor->curve.segments[curve_editor->curve.segments_count - 1].pos_end.y = curve_editor->curve.val_end;
			}
		}
		else if (curve_editor->curve.type != ztAnimCurveType_Spline) {
			curve_editor->active_point = -1;
		}
	}

	switch (curve_editor->curve.type)
	{
		case ztAnimCurveType_Linear: {
			zt_drawListAddLine(draw_list, beg_pnt, end_pnt);
		} break;

		case ztAnimCurveType_EaseIn: {
			ztTweenEase_Func *ease_in = zt_animCurveFindEaseFunction(curve_editor->curve.ease_in);

			r32 seg_w = size.x / 100;
			r32 prev_y = beg_pnt.y;
			r32 start_x = center.x - size.x / 2;

			zt_fiz(100) {
				r32 y = zt_lerp(beg_pnt.y, end_pnt.y, ease_in((i + 1) / 100.f, nullptr));

				zt_drawListAddLine(draw_list, zt_vec2(start_x + i * seg_w, prev_y), zt_vec2(start_x + (i + 1) * seg_w, y));
				prev_y = y;
			}
		} break;

		case ztAnimCurveType_EaseOut: {
			ztTweenEase_Func *ease_out = zt_animCurveFindEaseFunction(curve_editor->curve.ease_out);

			r32 seg_w = size.x / 100;
			r32 prev_y = beg_pnt.y;
			r32 start_x = center.x - size.x / 2;

			zt_fiz(100) {
				r32 y = zt_lerp(end_pnt.y, beg_pnt.y, ease_out(1 - ((i + 1) / 100.f), nullptr));

				zt_drawListAddLine(draw_list, zt_vec2(start_x + i * seg_w, prev_y), zt_vec2(start_x + (i + 1) * seg_w, y));
				prev_y = y;
			}
		} break;

		case ztAnimCurveType_EaseInOut: {
			ztTweenEase_Func *ease_in = zt_animCurveFindEaseFunction(curve_editor->curve.ease_in);
			ztTweenEase_Func *ease_out = zt_animCurveFindEaseFunction(curve_editor->curve.ease_out);

			r32 seg_w = size.x / 100;
			r32 prev_y = beg_pnt.y;
			r32 start_x = center.x - size.x / 2;

			zt_fiz(100) {
				r32 y = zt_tweenValue(beg_pnt.y, end_pnt.y, (i + 1) / 100.f, ease_in, ease_out);

				zt_drawListAddLine(draw_list, zt_vec2(start_x + i * seg_w, prev_y), zt_vec2(start_x + (i + 1) * seg_w, y));
				prev_y = y;
			}
		} break;

		case ztAnimCurveType_Spline: {
			curve_editor->curve.segments[0].pos_beg.y = val_beg;
			curve_editor->curve.segments[curve_editor->curve.segments_count - 1].pos_end.y = val_end;

			if (curve_editor->add_point_at != ztVec2::min) {
				if (curve_editor->curve.segments_count < zt_elementsOf(curve_editor->curve.segments)) {
					r32 x = (curve_editor->add_point_at.x - (center.x - size.x / 2)) / size.x;
					r32 y = (curve_editor->add_point_at.x - (center.x - size.x / 2)) / size.x;

					zt_fiz(curve_editor->curve.segments_count) {
						ztAnimCurveSplineSegment *segment = &curve_editor->curve.segments[i];
						if (x < segment->pos_end.x) {
							for (int j = curve_editor->curve.segments_count - 1; j >= i; --j) {
								curve_editor->curve.segments[j + 1].pos_beg = curve_editor->curve.segments[j].pos_beg;
								curve_editor->curve.segments[j + 1].pos_end = curve_editor->curve.segments[j].pos_end;
								curve_editor->curve.segments[j + 1].control_point_beg = curve_editor->curve.segments[j].control_point_beg;
								curve_editor->curve.segments[j + 1].control_point_end = curve_editor->curve.segments[j].control_point_end;
							}

							curve_editor->curve.segments[i].pos_end = zt_vec2(x, y);
							curve_editor->curve.segments[i + 1].pos_beg = zt_vec2(x, y);

							curve_editor->curve.segments[i].control_point_end = zt_vec2(-.5f, -2.f);
							curve_editor->curve.segments[i + 1].control_point_beg = zt_vec2(.5f, 2.f);

							curve_editor->curve.segments_count += 1;
							break;
						}
					}
				}
				curve_editor->add_point_at = ztVec2::min;
			}


			if (curve_editor->mpos_dragging != ztVec2::min) {
				curve_editor->mpos_dragging.x = zt_clamp(curve_editor->mpos_dragging.x, (offset.x + item->pos.x) - ((item->size.x / 2) - padding * 2), (offset.x + item->pos.x) + ((item->size.x / 2) - padding * 2));
				curve_editor->mpos_dragging.y = zt_clamp(curve_editor->mpos_dragging.y, (offset.y + item->pos.y) - ((item->size.y / 2) - padding * 2), (offset.y + item->pos.y) + ((item->size.y / 2) - padding * 2));
			}

			ztAnimCurveSplineSegment segment_absolutes[zt_elementsOf(curve_editor->curve.segments)];

			const r32 control_point_resize = .15f;

			zt_fiz(curve_editor->curve.segments_count) {
				ztAnimCurveSplineSegment *segment = &curve_editor->curve.segments[i];
				segment_absolutes[i].pos_beg = zt_vec2(center.x - size.x / 2 + (segment->pos_beg.x * size.x), center.y + (segment->pos_beg.y * (size.y * .5f)));
				segment_absolutes[i].pos_end = zt_vec2(center.x - size.x / 2 + (segment->pos_end.x * size.x), center.y + (segment->pos_end.y * (size.y * .5f)));

				segment_absolutes[i].control_point_beg = segment_absolutes[i].pos_beg + (segment->control_point_beg * control_point_resize) * zt_vec2(size.x, size.y * .5f);
				segment_absolutes[i].control_point_end = segment_absolutes[i].pos_end + (segment->control_point_end * control_point_resize) * zt_vec2(size.x, size.y * .5f);
			}

			int current_point = 0;
			bool clicked_in_point = false;
			zt_fiz(curve_editor->curve.segments_count) {
				ztAnimCurveSplineSegment *segment = &curve_editor->curve.segments[i];
				ztVec2 beg = segment_absolutes[i].pos_beg;
				ztVec2 end = segment_absolutes[i].pos_end;

				r32 radius = .035f;
				zt_drawListAddSolidCircle2D(draw_list, beg, radius, 8, ztColor_Green);
				if (curve_editor->active_point == current_point) {
					zt_drawListAddEmptyCircle(draw_list, zt_vec3(beg, 0), radius * 3, 8);
				}
				zt_drawListAddSolidCircle2D(draw_list, end, radius, 8, ztColor_Green);
				if (curve_editor->active_point == current_point + 1) {
					zt_drawListAddEmptyCircle(draw_list, zt_vec3(end, 0), radius * 3, 8);
				}

				radius *= 3.f;
				if (curve_editor->just_clicked) {
					if (zt_collisionPointInCircle(curve_editor->mpos_dragging, beg, radius)) {
						curve_editor->active_point = current_point;
						curve_editor->active_control_point = -1;
						curve_editor->dragging_point = true;
						curve_editor->dragging_point_offset = curve_editor->mpos_dragging - beg;
						clicked_in_point = true;
					}
				}
				else if (curve_editor->mpos_dragging != ztVec2::min && curve_editor->dragging_point && curve_editor->active_point == current_point && i != 0 && zt_collisionPointInRect(curve_editor->mpos_dragging, center, size)) {
					ztVec2 diff = (curve_editor->mpos_dragging - curve_editor->dragging_point_offset) - beg;

					if (segment_absolutes[i - 1].control_point_end.x + diff.x < segment_absolutes[i - 1].control_point_beg.x) {
						diff.x = 0;
					}
					if (segment_absolutes[i].control_point_beg.x + diff.x > segment_absolutes[i].control_point_end.x) {
						diff.x = 0;
					}

					diff.x /= size.x;
					diff.y /= size.y * .5f;
					curve_editor->curve.segments[i].pos_beg += diff;
					curve_editor->curve.segments[i - 1].pos_end += diff;
				}
				current_point += 1;

				if (curve_editor->just_clicked) {
					if (zt_collisionPointInCircle(curve_editor->mpos_dragging, end, radius)) {
						curve_editor->active_point = current_point;
						curve_editor->active_control_point = -1;
						curve_editor->dragging_point = true;
						clicked_in_point = true;
					}
				}

				radius = .065f;

				if (curve_editor->active_point == current_point - 1 && curve_editor->active_control_point == 0) {
					ztVec2 mpos = curve_editor->mpos_dragging;
					r32 bounds_x = segment_absolutes[i].control_point_end.x;

					if (i > 0) {
						r32 diff = beg.x - segment_absolutes[i - 1].control_point_beg.x;
						if (diff < bounds_x - segment_absolutes[i].pos_beg.x) {
							bounds_x = segment_absolutes[i].pos_beg.x + diff;
						}
					}

					if (mpos.x > bounds_x) {
						mpos.x = bounds_x;
					}

					ztVec2 diff = (mpos - beg);
					diff.x /= size.x;
					diff.y /= size.y * .5f;

					if (diff.x < 0) {
						diff.x = 0;
					}
					diff *= 1 / control_point_resize;
					segment->control_point_beg = diff;// *dist;


					if (i > 0) {
						curve_editor->curve.segments[i - 1].control_point_end = diff * -1;
					}
				}
				if (curve_editor->active_point == current_point - 1) {
					ztVec2 beg_cp_vis = segment_absolutes[i].control_point_beg;
					zt_drawListPushColor(draw_list, ztColor_White);
					zt_drawListAddLine(draw_list, beg, beg_cp_vis);
					zt_drawListPopColor(draw_list);
					zt_drawListAddSolidCircle2D(draw_list, beg_cp_vis, radius, 8, ztColor_Cyan);

					if (curve_editor->just_clicked && zt_collisionPointInCircle(curve_editor->mpos_dragging, beg_cp_vis, radius * 3)) {
						curve_editor->active_control_point = 0;
						clicked_in_point = true;
					}
				}

				if (curve_editor->active_point == current_point - 0 && curve_editor->active_control_point == 1) {
					ztVec2 mpos = curve_editor->mpos_dragging;
					r32 bounds_x = segment_absolutes[i].control_point_beg.x;
					if (i < curve_editor->curve.segments_count - 1) {
						r32 diff = segment_absolutes[i + 1].control_point_end.x - end.x;
						if (diff < segment_absolutes[i].pos_end.x - bounds_x) {
							bounds_x = segment_absolutes[i].pos_end.x - diff;
						}
					}
					if (mpos.x < bounds_x) {
						mpos.x = bounds_x;
					}

					ztVec2 diff = (mpos - end);
					diff.x /= size.x;
					diff.y /= size.y * .5f;

					if (diff.x > 0) {
						diff.x = 0;
					}
					diff *= 1 / control_point_resize;
					segment->control_point_end = diff;// *dist;

					if (i < curve_editor->curve.segments_count - 1) {
						curve_editor->curve.segments[i + 1].control_point_beg = diff * -1;
					}

				}
				if (curve_editor->active_point == current_point - 0) {
					ztVec2 end_cp_vis = segment_absolutes[i].control_point_end;
					zt_drawListPushColor(draw_list, ztColor_White);
					zt_drawListAddLine(draw_list, end, end_cp_vis);
					zt_drawListPopColor(draw_list);
					zt_drawListAddSolidCircle2D(draw_list, end_cp_vis, radius, 8, ztColor_Cyan);

					if (curve_editor->just_clicked && zt_collisionPointInCircle(curve_editor->mpos_dragging, end_cp_vis, radius * 3)) {
						curve_editor->active_control_point = 1;
						clicked_in_point = true;
					}
				}

				ztVec2 beg_cp = beg + (segment->control_point_beg * .25f) * zt_vec2(size.x, size.y * .5f);
				ztVec2 end_cp = end + (segment->control_point_end * .25f) * zt_vec2(size.x, size.y * .5f);

				zt_drawListAddBezierCurve(draw_list, beg, end, beg_cp, end_cp, 100);
			}

			if (curve_editor->just_clicked && !clicked_in_point) {
				curve_editor->active_point = -1;
			}
		} break;
	}

	zt_drawListPopColor(draw_list);
	zt_drawListPopTexture(draw_list);

	curve_editor->just_clicked = false;

	if (curve_editor->curve_val && zt_bitIsSet(curve_editor->ac_behavior_flags, ztGuiGradientPickerBehaviorFlags_LiveEdit) && 0 != zt_memCmp(curve_editor->curve_val, &curve_editor->curve, zt_sizeof(ztAnimCurve))) {
		zt_memCpy(curve_editor->curve_val, zt_sizeof(ztAnimCurve), &curve_editor->curve, zt_sizeof(ztAnimCurve));
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveComboType, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_animCurveComboType))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	switch (selected)
	{
		case ztAnimCurveType_Linear: {
			curve_editor->curve.type = ztAnimCurveType_Linear;
		} break;

		case ztAnimCurveType_EaseIn: {
			curve_editor->curve.type = ztAnimCurveType_EaseIn;
			curve_editor->curve.ease_in = ztAnimCurveEaseType_Linear;
		} break;

		case ztAnimCurveType_EaseOut: {
			curve_editor->curve.type = ztAnimCurveType_EaseOut;
			curve_editor->curve.ease_out = ztAnimCurveEaseType_Linear;
		} break;

		case ztAnimCurveType_EaseInOut: {
			curve_editor->curve.type = ztAnimCurveType_EaseInOut;
			curve_editor->curve.ease_in = ztAnimCurveEaseType_Linear;
			curve_editor->curve.ease_out = ztAnimCurveEaseType_Linear;
		} break;

		case ztAnimCurveType_Spline: {
			curve_editor->curve.type = ztAnimCurveType_Spline;

			curve_editor->curve.segments_count = 0;
			ztAnimCurveSplineSegment *segment = &curve_editor->curve.segments[curve_editor->curve.segments_count++];

			segment->pos_beg = zt_vec2(0, curve_editor->curve.val_beg);
			segment->pos_end = zt_vec2(1, curve_editor->curve.val_end);

			segment->control_point_beg = zt_vec2(.5f, .5f).getNormal();
			segment->control_point_end = zt_vec2(-.5f, .0f).getNormal();
		} break;
	}

	_zt_animCurveUpdateGui(curve_editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveEaseComboType, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_animCurveEaseComboType))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	if (combobox == curve_editor->ease_in_combo) {
		curve_editor->curve.ease_in = (ztAnimCurveEaseType_Enum)selected;
	}
	else if (combobox == curve_editor->ease_out_combo) {
		curve_editor->curve.ease_out = (ztAnimCurveEaseType_Enum)selected;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveButtonOk, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_animCurveButtonOk))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	if (curve_editor->curve_val) {
		zt_memCpy(curve_editor->curve_val, zt_sizeof(ztAnimCurve), &curve_editor->curve, zt_sizeof(ztAnimCurve));
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));

	if (ZT_FUNCTION_POINTER_IS_VALID(curve_editor->callback)) {
		ZT_FUNCTION_POINTER_ACCESS(curve_editor->callback, zt_guiDialogAnimCurveEditorComplete_Func)(&curve_editor->curve, curve_editor->user_data);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_animCurveButtonCancel, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_animCurveButtonCancel))
{
	ztGuiAnimCurveEditor *curve_editor = (ztGuiAnimCurveEditor*)user_data;

	if (curve_editor->curve_val && zt_bitIsSet(curve_editor->ac_behavior_flags, ztGuiGradientPickerBehaviorFlags_LiveEdit)) {
		zt_memCpy(curve_editor->curve_val, zt_sizeof(ztAnimCurve), &curve_editor->curve_orig, zt_sizeof(ztAnimCurve));
	}

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

void zt_guiDialogAnimCurveEditor(ztAnimCurve *curve, i32 behavior_flags, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogAnimCurveEditorComplete_Func), void *user_data, const char *window_title)
{
	ztGuiItem *window = zt_guiMakeWindow(window_title, ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_Modal);

	zt_guiItemSetSize(window, zt_vec2(9, 5));

	r32 padding = zt_guiThemeGetRValue(zt_guiItemGetTheme(window), ztGuiThemeValue_r32_Padding, window);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	ztGuiAnimCurveEditor *curve_editor = zt_mallocStructArena(ztGuiAnimCurveEditor, window->gm->arena);

	curve_editor->mpos_dragging = ztVec2::min;
	curve_editor->just_clicked = false;
	curve_editor->add_point_at = ztVec2::min;
	curve_editor->dragging_point = false;
	curve_editor->curve_val = curve;
	curve_editor->ac_behavior_flags = behavior_flags;
	curve_editor->callback = callback;
	curve_editor->user_data = user_data;

	if (curve == nullptr) {
		curve_editor->curve.type = ztAnimCurveType_Linear;
		curve_editor->curve.val_max = 1;
	}
	else {
		zt_memCpy(&curve_editor->curve, zt_sizeof(ztAnimCurve), curve, zt_sizeof(ztAnimCurve));
	}

	zt_memCpy(&curve_editor->curve_orig, zt_sizeof(ztAnimCurve), &curve_editor->curve, zt_sizeof(ztAnimCurve));

	{
		ztGuiItem *type_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, type_sizer, 0, 0);

		if (zt_bitIsSet(behavior_flags, ztGuiAnimCurveBehaviorFlags_AdjustValues)) {
			ztGuiItem *edit_val = zt_guiMakeEditor(sizer, nullptr, &curve_editor->curve.val_max, 0, 99, .1f);
			edit_val->min_size.x = .75f;

			zt_guiSizerAddItem(type_sizer, zt_guiMakeStaticText(type_sizer, "Value:"), 0, padding);
			zt_guiSizerAddItem(type_sizer, edit_val, 0, padding);
		}

		ztGuiItem *combo_type = zt_guiMakeComboBox(sizer, ztAnimCurveType_MAX);
		zt_guiComboBoxAppend(combo_type, "Linear");
		zt_guiComboBoxAppend(combo_type, "Ease In");
		zt_guiComboBoxAppend(combo_type, "Ease Out");
		zt_guiComboBoxAppend(combo_type, "Ease In/Out");
		zt_guiComboBoxAppend(combo_type, "Spline");
		zt_guiComboBoxSetCallback(combo_type, ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveComboType), curve_editor);
		zt_guiComboBoxSetSelected(combo_type, curve_editor->curve.type);
		curve_editor->type_combo = combo_type;

		zt_guiSizerAddItem(type_sizer, zt_guiMakeStaticText(type_sizer, "Curve Type:"), 0, padding);
		zt_guiSizerAddItem(type_sizer, combo_type, 0, padding);

		ztGuiItem *lbl_ease_in = zt_guiMakeStaticText(type_sizer, "In:");
		ztGuiItem *combo_ease_in = zt_guiMakeComboBox(type_sizer, ztAnimCurveEaseType_MAX);
		zt_guiComboBoxSetCallback(combo_ease_in, ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveEaseComboType), curve_editor);

		ztGuiItem *lbl_ease_out = zt_guiMakeStaticText(type_sizer, "Out:");
		ztGuiItem *combo_ease_out = zt_guiMakeComboBox(type_sizer, ztAnimCurveEaseType_MAX);
		zt_guiComboBoxSetCallback(combo_ease_out, ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveEaseComboType), curve_editor);

		const char *ease_names[] = {
			"Linear",
			"Back",
			"Bounce",
			"Circ",
			"Cubic",
			"Elastic",
			"Expo",
			"Quad",
			"Quart",
			"Quint",
			"Sine",
		};

		zt_fize(ease_names) {
			zt_guiComboBoxAppend(combo_ease_in, ease_names[i]);
			zt_guiComboBoxAppend(combo_ease_out, ease_names[i]);
		}

		if (curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseIn) {
			zt_guiComboBoxSetSelected(combo_ease_in, curve_editor->curve.ease_in);
		}
		if (curve_editor->curve.type == ztAnimCurveType_EaseInOut || curve_editor->curve.type == ztAnimCurveType_EaseOut) {
			zt_guiComboBoxSetSelected(combo_ease_out, curve_editor->curve.ease_out);
		}

		curve_editor->ease_in_label = lbl_ease_in;
		curve_editor->ease_in_combo = combo_ease_in;
		curve_editor->ease_out_label = lbl_ease_out;
		curve_editor->ease_out_combo = combo_ease_out;

		zt_guiSizerAddStretcher(type_sizer, 1);
		zt_guiSizerAddItem(type_sizer, lbl_ease_in, 0, padding);
		zt_guiSizerAddItem(type_sizer, combo_ease_in, 0, padding);
		zt_guiSizerAddItem(type_sizer, lbl_ease_out, 0, padding);
		zt_guiSizerAddItem(type_sizer, combo_ease_out, 0, padding);
	}

	{
		ztGuiItem *main_panel = zt_guiMakePanel(sizer, ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput | ztGuiItemBehaviorFlags_ClipContents, curve_editor, window->gm->arena);
		zt_guiSizerAddItem(sizer, main_panel, 1, padding);

		main_panel->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveDisplay_InputMouse);
		main_panel->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveDisplay_InputKeyboard);
		main_panel->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveDisplay_Render);
		main_panel->functions.user_data   = curve_editor;
	}


	{
		ztGuiItem *sizer_btns = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, sizer_btns, 0, 0);
		zt_guiSizerAddStretcher(sizer_btns, 1);

		ztGuiItem *button_ok = zt_guiMakeButton(sizer_btns, nullptr);
		ztSprite sprite_ok = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 0, 16, 16);
		zt_guiButtonSetIcon(button_ok, &sprite_ok);
		zt_guiButtonSetCallback(button_ok, ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveButtonOk), curve_editor);
		button_ok->size.x *= 2;
		zt_guiSizerAddItem(sizer_btns, button_ok, 0, padding);

		ztGuiItem *button_cancel = zt_guiMakeButton(sizer_btns, nullptr);
		ztSprite sprite_cancel = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 1007, 16, 16, 16);
		zt_guiButtonSetIcon(button_cancel, &sprite_cancel);
		zt_guiButtonSetCallback(button_cancel, ZT_FUNCTION_POINTER_TO_VAR(_zt_animCurveButtonCancel), curve_editor);
		button_cancel->size.x *= 2;
		zt_guiSizerAddItem(sizer_btns, button_cancel, 0, padding);

		zt_guiSizerAddStretcher(sizer_btns, 1);
	}

	_zt_animCurveUpdateGui(curve_editor);
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


struct ztSpriteSelectorData
{
	ztSpriteManager        *sprite_manager;

	ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogSpriteSelected_Func);
	void                   *user_data;

	bool                    cancelled;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogSpriteSelectorButton, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDialogSpriteSelectorButton))
{
	ztSpriteSelectorData *data = (ztSpriteSelectorData*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(button));
	ztSpriteManager::Entry *sprite_entry = (ztSpriteManager::Entry*)user_data;

	if (ZT_FUNCTION_POINTER_IS_VALID(data->callback)) {
		ZT_FUNCTION_POINTER_ACCESS(data->callback, zt_guiDialogSpriteSelected_Func)(data->sprite_manager, sprite_entry, sprite_entry->hash, sprite_entry->name, false, data->user_data);
	}
	data->cancelled = false;

	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDialogSpriteSelectorCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDialogSpriteSelectorCleanup))
{
	ztSpriteSelectorData *data = (ztSpriteSelectorData*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(item));
	
	if (data->cancelled && ZT_FUNCTION_POINTER_IS_VALID(data->callback)) {
		ZT_FUNCTION_POINTER_ACCESS(data->callback, zt_guiDialogSpriteSelected_Func)(data->sprite_manager, nullptr, 0, nullptr, true, user_data);
	}

	zt_freeArena(data, item->gm->arena);
}

// ================================================================================================================================================================================================

void zt_guiDialogSpriteSelector(ztSpriteManager *sprite_manager, ZT_FUNCTION_POINTER_VAR(callback, zt_guiDialogSpriteSelected_Func), void *user_data, const char *window_title)
{
	ztGuiItem *window = zt_guiMakeWindow(window_title, ztGuiWindowBehaviorFlags_Modal | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowClose | ztGuiItemBehaviorFlags_BringToFront);
	zt_guiItemSetSize(window, zt_vec2(16, 10));
	zt_guiItemSetName(window, "Select Sprite Window");
	zt_guiItemBringToFront(window);

	ztSpriteSelectorData *data = zt_mallocStructArena(ztSpriteSelectorData, window->gm->arena);
	ztGuiItem *win_cleanup = zt_guiMakePanel(window, 0);
	win_cleanup->functions.cleanup = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogSpriteSelectorCleanup);
	win_cleanup->functions.user_data = data;

	zt_guiItemSetUserData(window, data);

	data->sprite_manager = sprite_manager;
	data->callback = callback;
	data->user_data = user_data;
	data->cancelled = true;

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window_sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	ztGuiItem *scroll = zt_guiMakeScrollContainer(window_sizer, ztGuiScrollContainerBehaviorFlags_StretchHorz);
	zt_guiSizerAddItem(window_sizer, scroll, 1, padding);

	ztGuiItem *sizer = zt_guiMakeWrapSizer(window_sizer, ztGuiItemOrient_Horz);

	zt_guiScrollContainerSetItem(scroll, sizer);

	int sprites_count = 0;
	zt_fiz(data->sprite_manager->sprites_count) {
		if (data->sprite_manager->sprites[i].hash != 0 && data->sprite_manager->sprites[i].type == ztSpriteType_Sprite) {
			sprites_count += 1;
		}
	}

	ztSpriteManager::Entry **entries = zt_mallocStructArray(ztSpriteManager::Entry*, sprites_count);
	sprites_count = 0;
	zt_fiz(data->sprite_manager->sprites_count) {
		if (data->sprite_manager->sprites[i].hash != 0 && data->sprite_manager->sprites[i].type == ztSpriteType_Sprite) {
			entries[sprites_count++] = &data->sprite_manager->sprites[i];
		}
	}

	struct local
	{
		static int compare(const void *vone, const void *vtwo)
		{
			ztSpriteManager::Entry* one = *(ztSpriteManager::Entry**)vone;
			ztSpriteManager::Entry* two = *(ztSpriteManager::Entry**)vtwo;

			return zt_striCmp(one->name, two->name);
		}
	};

	qsort(entries, sprites_count, zt_sizeof(ztSpriteManager::Entry*), local::compare);

	zt_fiz(sprites_count) {
		ztGuiItem *button = zt_guiMakeButton(sizer, entries[i]->name, ztGuiButtonBehaviorFlags_NoBackground);
		zt_guiButtonSetTextPosition(button, ztAlign_VertCenter | ztAlign_Bottom);
		zt_guiButtonSetIcon(button, &entries[i]->s);
		zt_guiSizerAddItem(sizer, button, 0, padding, ztAlign_Bottom, 0);
		zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDialogSpriteSelectorButton), entries[i]);
	}

	zt_free(entries);

}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void zt_guiItemFree(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemFree");

	if (item == nullptr) {
		return;
	}

	_zt_guiItemFree(item->gm, item);
}

// ================================================================================================================================================================================================

void zt_guiItemQueueFree(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemFree");

	if (item == nullptr) {
		return;
	}

	item->gm->item_cache_flags[item->id] |= ztGuiManagerItemCacheFlags_FreeQueued;
	zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Visible));
}

// ================================================================================================================================================================================================

void zt_guiItemSetSize(ztGuiItem *item, const ztVec2& size)
{
	zt_returnOnNull(item);

	if (size.x != -1) item->size.x = size.x;
	if (size.y != -1) item->size.y = size.y;
}

// ================================================================================================================================================================================================

void zt_guiItemSetMinSize(ztGuiItem *item, const ztVec2& size)
{
	zt_returnOnNull(item);

	if (size.x != -1) item->min_size.x = size.x;
	if (size.y != -1) item->min_size.y = size.y;
}

// ================================================================================================================================================================================================

void zt_guiItemAutoSize(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemAutoSize");

	zt_returnOnNull(item);

	ztGuiTheme *theme = zt_guiItemGetTheme(item);

	if (ZT_FUNCTION_POINTER_IS_VALID(item->functions.best_size)) {
		ztVec2 min, max;
		ZT_FUNCTION_POINTER_ACCESS(item->functions.best_size, zt_guiItemBestSize_Func)(item, &min, &max, &item->size, theme, item->functions.user_data);
	}
	//else {
	//	if (item->label != nullptr) {
	//		item->size = zt_fontGetExtents(theme->font, item->label);
	//		item->size.x += theme->padding * 2;
	//		item->size.y += theme->padding * 2;
	//	}
	//}
}

// ================================================================================================================================================================================================

void zt_guiItemSetPosition(ztGuiItem *item, const ztVec2& pos)
{
	zt_returnOnNull(item);
	item->pos = pos;
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiItemSetName(ztGuiItem *item, const char *name)
{
	ZT_PROFILE_GUI("zt_guiItemSetName");

	zt_returnOnNull(item);
	item->name = zt_stringOverwrite(&item->gm->string_pool, item->name, name);
}

// ================================================================================================================================================================================================

void zt_guiItemSetLabel(ztGuiItem *item, const char *label)
{
	ZT_PROFILE_GUI("zt_guiItemSetLabel");

	zt_returnOnNull(item);
	item->label = zt_stringOverwrite(&item->gm->string_pool, item->label, label);
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

void zt_guiItemSetTooltip(ztGuiItem *item, const char *tooltip)
{
	ZT_PROFILE_GUI("zt_guiItemSetTooltip");

	zt_returnOnNull(item);
	item->tooltip = zt_stringOverwrite(&item->gm->string_pool, item->tooltip, tooltip);
}

// ================================================================================================================================================================================================

void zt_guiItemSetThemeType(ztGuiItem *item, const char *theme_type)
{
	ZT_PROFILE_GUI("zt_guiItemSetThemeType");

	zt_returnOnNull(item);
	item->theme_type = zt_stringOverwrite(&item->gm->string_pool, item->theme_type, theme_type);
}

// ================================================================================================================================================================================================

void zt_guiItemSetTheme(ztGuiItem *item, ztGuiTheme *theme)
{
	zt_returnOnNull(item);
	item->theme = theme;
}

// ================================================================================================================================================================================================

void zt_guiItemSetColor(ztGuiItem *item, const ztVec4& color)
{
	zt_returnOnNull(item);
	item->color = color;
}

// ================================================================================================================================================================================================

void zt_guiItemSetUserData(ztGuiItem *item, void *user_data)
{
	zt_returnOnNull(item);
	item->user_data = user_data;
}

// ================================================================================================================================================================================================

void zt_guiItemSetCustomFlags(ztGuiItem *item, i32 flags)
{
	zt_returnOnNull(item);
	item->custom_flags = flags;
}

// ================================================================================================================================================================================================

i32 zt_guiItemGetCustomFlags(ztGuiItem *item)
{
	zt_returnValOnNull(item, 0);
	return item->custom_flags;
}

// ================================================================================================================================================================================================

ztString zt_guiItemGetName(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->name;
}

// ================================================================================================================================================================================================

ztString zt_guiItemGetLabel(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->label;
}

// ================================================================================================================================================================================================

ztString zt_guiItemGetTooltip(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->tooltip;
}

// ================================================================================================================================================================================================

ztString zt_guiItemGetThemeType(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->theme_type;
}

// ================================================================================================================================================================================================

void zt_guiItemSetAlign(ztGuiItem *item, i32 align_flags)
{
	zt_returnOnNull(item);
	item->align_flags = align_flags;
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

void *zt_guiItemGetUserData(ztGuiItem *item)
{
	zt_returnValOnNull(item, nullptr);
	return item->user_data;
}

// ================================================================================================================================================================================================

ztVec2 zt_guiItemGetSize(ztGuiItem *item)
{
	zt_returnValOnNull(item, ztVec2::zero);
	return item->size;
}

// ================================================================================================================================================================================================

ztVec2 zt_guiItemGetPosition(ztGuiItem *item)
{
	zt_returnValOnNull(item, ztVec2::min);
	return item->pos;
}

// ================================================================================================================================================================================================

i32 zt_guiItemGetAlign(ztGuiItem *item)
{
	zt_returnValOnNull(item, 0);
	return item->align_flags;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiItemHide(ztGuiItem *item)
{
	zt_guiItemShow(item, false);
}

// ================================================================================================================================================================================================

bool zt_guiItemIsVisible(ztGuiItem *item)
{
	zt_returnValOnNull(item, false);
	return zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Visible));
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiItemDisable(ztGuiItem *item)
{
	zt_returnOnNull(item);
	zt_guiItemEnable(item, false);
}

// ================================================================================================================================================================================================

bool zt_guiItemIsEnabled(ztGuiItem *item)
{
	zt_returnValOnNull(item, false);
	return !zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled));
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiItemSetFocus(ztGuiItem *item, ztGuiItem **prev_focus_item_id)
{
	zt_returnOnNull(item);
	if (prev_focus_item_id) *prev_focus_item_id = item->gm->focus_item;
	item->gm->focus_item = item;
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

void zt_guiItemLock(ztGuiItem *item)
{
	zt_returnOnNull(item);
	item->state_flags |= zt_bit(ztGuiItemStates_Locked);
}

// ================================================================================================================================================================================================

void zt_guiItemUnlock(ztGuiItem *item)
{
	zt_returnOnNull(item);
	zt_bitRemove(item->state_flags, zt_bit(ztGuiItemStates_Locked));
	item->state_flags |= zt_bit(ztGuiItemStates_Dirty);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

bool zt_guiItemTopLevelIsOverlapping(ztGuiItem *item)
{
	ZT_PROFILE_GUI("zt_guiItemTopLevelIsOverlapping");

	zt_returnValOnNull(item, false);

	item = zt_guiItemGetTopLevelParent(item);

	ztVec3 item_center = zt_vec3(item->pos, 0);
	ztVec3 item_size = zt_vec3(item->size, 1);

	zt_flinknext(child, item->gm->first_child, sib_next) {
		if (child == item) {
			return false;
		}
		if (!zt_guiItemIsShowing(child)) {
			continue;
		}

		ztVec3 child_center = zt_vec3(child->pos, 0);
		ztVec3 child_size = zt_vec3(child->size, 1);

		// bool zt_collisionAABBInAABB(const ztVec3& aabb_center_1, const ztVec3& aabb_extents_1, const ztVec3& aabb_center_2, const ztVec3& aabb_extents_2);
		if (zt_collisionAABBInAABB(item_center, item_size, child_center, child_size)) {
			return true;
		}
	}

	return false;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_DEBUG_MENUBAR_NAME	"Debug Menu"

// ================================================================================================================================================================================================

struct ztDebugRenderingDetails
{
	ztGuiItem *window;
	ztGuiItem *text;
	ztGuiItem *sizer;
};

#define ZT_DEBUG_RENDERING_DETAILS_WINDOW_NAME	"Rendering Details Window"

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugRenderingDetailsUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiDebugRenderingDetailsUpdate))
{
	ZT_PROFILE_GUI("_zt_guiDebugRenderingDetailsUpdate");

	if (!zt_guiItemIsShowing(item)) return;

	ztDebugRenderingDetails *details = (ztDebugRenderingDetails*)item->functions.user_data;

	zt_strMakePrintf(details_str, 256, "%d triangles\n%d shader switches\n%d tex switches\n%d draw calls", zt_game->game_details.prev_frame.triangles_drawn, zt_game->game_details.prev_frame.shader_switches, zt_game->game_details.prev_frame.texture_switches, zt_game->game_details.prev_frame.draw_calls);
	zt_guiItemSetLabel(details->text, details_str);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugRenderingDetailsCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugRenderingDetailsCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugRenderDetailsSize(ztDebugRenderingDetails *details)
{
	details->sizer->size = zt_guiSizerGetMinSize(details->sizer);
	//zt_guiSizerRecalcImmediately(details->sizer);

	r32 ppu = zt_pixelsPerUnit();

	details->window->size = details->sizer->size + zt_vec2(8 / ppu, 4 / ppu);
}

// ================================================================================================================================================================================================

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
		zt_guiItemSetPosition(window, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right, zt_vec2(0, y_off));
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

	details->text = zt_guiMakeStaticText(details->sizer, "00000000 triangles\n0000 shader switches\n0000 tex switches\n0000 draw calls", ztGuiStaticTextBehaviorFlags_MonoSpaced, 256);
	zt_guiItemSetAlign(details->text, ztAlign_Right);
	zt_debugOnly(zt_guiItemSetName(details->text, "Rendering Details Text"));
	zt_guiSizerAddItem(details->sizer, details->text, 0, 3 / zt_pixelsPerUnit());

	//zt_guiItemSetSize(window, zt_vec2(3.25f, 1.2f));
	//zt_guiItemSetPosition(details->text, ztAlign_Right, ztAnchor_Right, zt_vec2(-26.f / zt_pixelsPerUnit(), 0));

	_zt_guiDebugRenderDetailsSize(details);

	ztGuiItem *update = _zt_guiMakeItemBase(window, ztGuiItemType_Custom, 0);
	update->functions.update    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugRenderingDetailsUpdate);
	update->functions.cleanup   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugRenderingDetailsCleanup);
	update->functions.user_data = details;


	zt_guiItemSetPosition(window, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right, zt_vec2(0, y_off));
	return true;
}

// ================================================================================================================================================================================================

void zt_guiDebugShowDetails(bool show)
{
	ztGuiItem *window = zt_guiItemFindByName(ZT_DEBUG_RENDERING_DETAILS_WINDOW_NAME);

	if (window == nullptr) {
		_zt_guiDebugRenderingDetails();
		return;
	}

	zt_guiItemShow(window, show);
}

// ================================================================================================================================================================================================

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
			ztGuiItem *static_txt = zt_guiMakeStaticText(details->sizer, sample, ztGuiStaticTextBehaviorFlags_MonoSpaced, zt_strLen(sample) + 64);
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

// ================================================================================================================================================================================================

ztGuiItem *zt_guiDebugGetMenuBar()
{
	return zt_gui->menu_bar;
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztDebugFpsDisplay
{
	ztGuiItem  *panel;
	ztGuiItem  *text;
	ztGuiItem  *button;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugFpsDisplayUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiDebugFpsDisplayUpdate))
{
	ZT_PROFILE_GUI("_zt_guiDebugFpsDisplayUpdate");

	ztDebugFpsDisplay *fps = (ztDebugFpsDisplay*)item->functions.user_data;

	if (!zt_guiItemIsShowing(fps->panel)) return;

	zt_strMakePrintf(fps_str, 256, "(%d) %.0f f/s %.02f us/f", zt_game->game_details.current_frame, 1.f / dt, dt * 1000000.f);
	zt_guiItemSetLabel(fps->text, fps_str);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugFpsDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugFpsDisplayCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugFpsDisplayButtonExpand, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugFpsDisplayButtonExpand))
{
	if (_zt_guiDebugRenderingDetails()) {
		zt_guiItemSetLabel(button, "-");
	}
	else {
		zt_guiItemSetLabel(button, "+");
	}
}

// ================================================================================================================================================================================================

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

	fps->text = zt_guiMakeStaticText(fps->panel, "(000000000000) 00000 f/s 00.0000f us/f", ztGuiStaticTextBehaviorFlags_MonoSpaced);
	zt_guiItemSetAlign(fps->text, ztAlign_Right);
	zt_debugOnly(zt_guiItemSetName(fps->text, "FPS Display Text"));
	zt_guiSizerAddItem(sizer, fps->text, 1, 0);
	zt_guiSizerAddStretcher(sizer, 0, 3 / zt_pixelsPerUnit());

	fps->button = zt_guiMakeButton(fps->panel, "+", ztGuiButtonBehaviorFlags_NoBackground);
	zt_guiButtonSetCallback(fps->button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugFpsDisplayButtonExpand));
	fps->button->size.x = fps->button->size.y = 18 / zt_pixelsPerUnit();
	zt_guiSizerAddItem(sizer, fps->button, 0, 2 / zt_pixelsPerUnit());

	zt_guiItemSetSize(fps->panel, zt_vec2(3.25f, 20 / zt_pixelsPerUnit()));

	ztGuiItem *update = _zt_guiMakeItemBase(fps->panel, ztGuiItemType_Custom, 0);
	update->functions.update    = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugFpsDisplayUpdate);
	update->functions.cleanup   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugFpsDisplayCleanup);
	update->functions.user_data = fps;

	zt_guiItemSetPosition(fps->panel, ztAlign_Top | ztAlign_Right, ztAnchor_Top | ztAnchor_Right);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_DEBUG_CONSOLE_MAX_LINES
#define ZT_DEBUG_CONSOLE_MAX_LINES      512
#endif

#ifndef ZT_DEBUG_CONSOLE_MAX_COMMANDS
#define ZT_DEBUG_CONSOLE_MAX_COMMANDS 32
#endif

#define ZT_DEBUG_CONSOLE_NAME           "Console"
#define ZT_DEBUG_CONSOLE_COMMAND_NAME   "Console Command"

// ================================================================================================================================================================================================

struct ztConsoleCmdStr
{
	char command[128];
	ztConsoleCmdStr *next, *prev;
};

// ================================================================================================================================================================================================

struct ztDebugConsole
{
	ztGuiItem       *display;
	ztGuiItem       *command;
	int              last_tab_stop;

	ztConsoleCmdStr *commands;
	byte             command_buffer[zt_sizeof(ztConsoleCmdStr) * ZT_DEBUG_CONSOLE_MAX_COMMANDS];

	ztConsoleCmdStr *current_command;
	ztConsoleCmdStr *selected_command;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugConsoleCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ================================================================================================================================================================================================

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
				ZT_FUNCTION_POINTER_ACCESS_SAFE(command->on_command, zt_debugConsole_Func)(params, tokens_count, command->user_data);
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

	zt_fiz(ZT_MAX_INPUT_KEYSTROKES) {
		if (input_key_strokes[i] == ztInputKeys_Invalid) {
			break;
		}
		if (input_keys[input_key_strokes[i]].display != 0) {
			dc->last_tab_stop = 0;
		}
	}
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_List, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_List))
{
	zt_debugConsoleLogCommand("  Available commands:");

	auto *command = zt_gui->console_commands;
	while (command) {
		zt_debugConsoleLogCommand("    %s", command->command);
		command = command->next;
	}
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommandAutoComplete_Help, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND_AUTOCOMPLETE(_zt_guiDebugConsoleCommandAutoComplete_Help))
{

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_Exit, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_Exit))
{
	zt_game->quit_requested = true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugConsoleCommand_PlayAudio, ztInternal ZT_FUNC_DEBUG_CONSOLE_COMMAND(_zt_guiDebugConsoleCommand_PlayAudio))
{
	ztAudioClipID audio_clip_id = zt_strToInt(params[1], ztInvalidID);
	if (audio_clip_id >= 0 && audio_clip_id < zt_game->audio_clips_count) {
		zt_audioClipPlayOnce(audio_clip_id);
	}
	else {
		if (zt_game->audio_clips_count == 0) {
			zt_debugConsoleLogCommand("There are no loaded audio clips to play");
		}
		else {
			zt_debugConsoleLogCommand("Please select an ID between 0 and %d", zt_game->audio_clips_count - 1);
		}
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugConsoleAddLoggingCallbacks()
{
	if (zt_gui->console_window != nullptr) {
#		ifndef ZT_DEBUG_CONSOLE_LOG_LEVEL
		zt_logAddCallback(_zt_guiDebugConsoleLogMessageCallback, ztLogMessageLevel_Debug);
#		else
		zt_logAddCallback(_zt_guiDebugConsoleLogMessageCallback, ZT_DEBUG_CONSOLE_LOG_LEVEL);
#		endif
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugConsoleRemoveLoggingCallbacks()
{
	zt_logRemoveCallback(_zt_guiDebugConsoleLogMessageCallback);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugConsole()
{
	{
		ztGuiItem *window = zt_guiItemFindByName(ZT_DEBUG_CONSOLE_NAME);
		if (window != nullptr) {
			zt_guiItemShow(window);
			zt_guiItemBringToFront(window);
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
	window->functions.cleanup = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleCleanup);
	
	zt_guiItemSetSize(window, zt_vec2(16, 9));
	zt_guiItemSetName(window, ZT_DEBUG_CONSOLE_NAME);

	ztGuiItem *content = zt_guiWindowGetContentParent(window);

	zt_gui->console_display = dc->display = zt_guiMakeListBox(content, ztGuiListBoxBehaviorFlags_UseFancyText, ZT_DEBUG_CONSOLE_MAX_LINES);

	zt_gui->console_command = dc->command = zt_guiMakeTextEdit(content, nullptr);
	zt_guiItemSetName(zt_gui->console_command, ZT_DEBUG_CONSOLE_COMMAND_NAME);
	zt_guiTextEditSetCallback(dc->command, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleInputKey));
	zt_guiItemSetFocus(zt_gui->console_command);

	ztGuiItem *main_sizer = zt_guiMakeSizer(content, ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(main_sizer);

	zt_guiSizerAddItem(main_sizer, dc->display, 1, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddItem(main_sizer, dc->command, 0, 3 / zt_pixelsPerUnit(), 0, ztGuiItemOrient_Horz);

	zt_debugConsoleAddCommand("list", "Lists the available commands", ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleCommand_List     ), ZT_FUNCTION_POINTER_TO_VAR_NULL);
	zt_debugConsoleAddCommand("help",                        nullptr, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleCommand_Help     ), ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleCommandAutoComplete_Help));
	zt_debugConsoleAddCommand("exit",            "Quits the program", ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleCommand_Exit     ), ZT_FUNCTION_POINTER_TO_VAR_NULL);
	zt_debugConsoleAddCommand("playaudio",     "Plays an audio clip", ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugConsoleCommand_PlayAudio), ZT_FUNCTION_POINTER_TO_VAR_NULL);

	zt_debugConsoleLogCommand("<color=00aa00ff>Welcome to the console.  Type 'help <<cmd>' for help.  Type 'list' for commands.</color>");

	zt_guiSizerRecalcImmediately(zt_gui->console_window);

	zt_guiItemShow(window, false);

	_zt_guiDebugConsoleAddLoggingCallbacks();
}

// ================================================================================================================================================================================================

void zt_debugConsoleAddCommand(const char *command, const char *help, ZT_FUNCTION_POINTER_VAR(command_func, zt_debugConsole_Func), ZT_FUNCTION_POINTER_VAR(auto_complete_func, zt_debugConsoleAutoComplete_Func), void *user_data)
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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

#if defined(ZT_COMPILER_MSVC)
#define _zt_var_args \
			va_list arg_ptr; \
			va_start(arg_ptr, command); \
			char *buffer = zt_mallocStructArrayArena(char, 1024 * 64, zt_gui->stack_arena); \
			vsnprintf_s(buffer, 1024 * 64, 1024 * 64, command, arg_ptr);

#elif defined(ZT_COMPILER_LLVM) || defined(ZT_ANDROID)
#define _zt_var_args \
			va_list arg_ptr; \
			va_start(arg_ptr, command); \
			char *buffer = zt_mallocStructArrayArena(char, 1024 * 64, zt_gui->stack_arena); \
			vsnprintf(buffer, 1024 * 64, command, arg_ptr);


#else
#	error "Unsupported compiler for zt_debugConsoleLog"
#endif

// ================================================================================================================================================================================================

ztInternal void _zt_debugConsoleLogRaw(ztDebugConsoleLevel_Enum message_level, const char *command)
{
	ZT_PROFILE_GUI("_zt_debugConsoleLogRaw");

	if (zt_gui->console_display == nullptr) {
		return;
	}

	zt_assertReturnOnFail(zt_gui->console_display->type == ztGuiItemType_ListBox);

	if (zt_guiListBoxGetCount(zt_gui->console_display) >= ZT_DEBUG_CONSOLE_MAX_LINES) {
		zt_guiListBoxRemoveItem(zt_gui->console_display, 0);
	}

	zt_guiListBoxAppend(zt_gui->console_display, command, nullptr);


#if 0
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
#endif
}

// ================================================================================================================================================================================================

void zt_debugConsoleLog(ztDebugConsoleLevel_Enum message_level, const char *command, ...)
{
	_zt_var_args;
	_zt_debugConsoleLogRaw(message_level, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

void zt_debugConsoleLogUser(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_User, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

void zt_debugConsoleLogCommand(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Command, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

void zt_debugConsoleLogHelp(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Help, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

void zt_debugConsoleLogWarning(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Warning, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

void zt_debugConsoleLogError(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_Error, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

void zt_debugConsoleLogSystem(const char *command, ...)
{
	_zt_var_args;
	zt_debugConsoleLog(ztDebugConsoleLevel_System, (const char *)buffer);
	zt_freeArena(buffer, zt_gui->stack_arena);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

#undef _zt_var_args

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztDebugGuiHierarchy
{
	ztGuiItem *window  = nullptr;
	ztGuiItem *tree    = nullptr;
	ztGuiItem *details = nullptr;
};

// ================================================================================================================================================================================================

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

	zt_guiTreeCollapseNode(dgh->tree, root);
}

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugGuiHierarchyPopulateItem(ztDebugGuiHierarchy *dgh, ztGuiItem *item)
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyPopulateItem");

	zt_strMakePrintf(details_buffer, 64 * 1024,
		"<color=8abbf8>ID:</color>                      %d\n"
		"<color=8abbf8>Type:</color>                    %s\n"
		"<color=8abbf8>Name:</color>                    %s\n"
		"<color=8abbf8>Tooltip:</color>                 %s\n"
		"<color=8abbf8>Size:</color>                    %.2f, %.2f\n"
		"<color=8abbf8>Min Size:</color>                %.2f, %.2f\n"
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
		item->id,
		zt_guiItemTypeName(item->type),
		item->name ? item->name : "(unnamed)",
		item->tooltip ? item->tooltip : "(no tooltip)",
		item->size.x, item->size.y,
		item->min_size.x, item->min_size.y,
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

// ================================================================================================================================================================================================

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

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyOnRefreshTree, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugGuiHierarchyOnRefreshTree))
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyOnRefreshTree");

	ztGuiItem *win = zt_guiItemGetTopLevelParent(button);
	ztDebugGuiHierarchy *dgh = (ztDebugGuiHierarchy*)win->functions.user_data;
	_zt_guiDebugGuiHierarchyPopulate(dgh);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyOnToggleHighlight, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugGuiHierarchyOnToggleHighlight))
{
	ZT_PROFILE_GUI("_zt_guiDebugGuiHierarchyOnToggleHighlight");

#	if defined(ZT_DEBUG)
	ztGuiItem *win = zt_guiItemGetTopLevelParent(button);
	ztDebugGuiHierarchy *dgh = (ztDebugGuiHierarchy*)win->functions.user_data;

	ztGuiItem* item = (ztGuiItem*)zt_guiTreeGetNodeUserData(dgh->tree, zt_guiTreeGetSelected(dgh->tree));
	if (item) {
		if (item->debug_highlight == ztVec4::zero) {
			item->debug_highlight = zt_vec4(0, 1, 0, 1);
		}
		else {
			item->debug_highlight = ztVec4::zero;
		}
	}
#	endif
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugGuiHierarchyCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugGuiHierarchyCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ================================================================================================================================================================================================

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
	zt_guiItemSetName(dgh->window, window_name);
	dgh->window->functions.user_data = dgh;
	dgh->window->functions.cleanup = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugGuiHierarchyCleanup);

	ztVec2 cam_ext = zt_cameraOrthoGetViewportSize(gm->gui_camera);
	zt_guiItemSetSize(dgh->window, zt_vec2(cam_ext.x - 2, cam_ext.y - 2));

	ztGuiTheme *theme   = zt_guiItemGetTheme(dgh->window);
	ztGuiItem  *content = zt_guiWindowGetContentParent(dgh->window);
	ztGuiItem  *sizer   = zt_guiMakeSizer(content, ztGuiItemOrient_Horz);

	r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, dgh->window);

	ztGuiItem *splitter = zt_guiMakeSplitter(sizer, ztGuiItemOrient_Horz, .5f);
	zt_guiSplitterSetFirstSize(splitter, 5);
	zt_guiSizerAddItem(sizer, splitter, 1, padding);

	{

		ztGuiItem *sizer_left = zt_guiMakeSizer(splitter, ztGuiItemOrient_Vert, false);
		zt_guiSplitterSetFirstItem(splitter, sizer_left);

		dgh->tree = zt_guiMakeTree(sizer_left, 1024 * 64);
		zt_guiSizerAddItem(sizer_left, dgh->tree, 1, padding);

		zt_guiTreeSetCallback(dgh->tree, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugGuiHierarchyOnTreeSel), nullptr);

		ztGuiItem *sizer_btns = zt_guiMakeSizer(sizer_left, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer_left, sizer_btns, 0, 0);

		ztGuiItem *button_refresh = zt_guiMakeButton(sizer_left, "Refresh");
		zt_guiButtonSetCallback(button_refresh, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugGuiHierarchyOnRefreshTree));
		zt_guiSizerAddItem(sizer_btns, button_refresh, 0, padding);

#		if defined(ZT_DEBUG)
		zt_guiSizerAddStretcher(sizer_btns, 1);
		ztGuiItem *button_highlight = zt_guiMakeButton(sizer_btns, "Toggle Highlight");
		zt_guiButtonSetCallback(button_highlight, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugGuiHierarchyOnToggleHighlight));
		zt_guiSizerAddItem(sizer_btns, button_highlight, 0, padding, ztAlign_Right, 0);
#		endif
	}

	{
		ztGuiItem *sizer_right = zt_guiMakeSizer(splitter, ztGuiItemOrient_Vert, false);
		zt_guiSplitterSetSecondItem(splitter, sizer_right);

		ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer_right);
		dgh->details = zt_guiMakeStaticText(scroll, "<color=8abbf8>Select an item on the left to view details on that item.</color>", ztGuiStaticTextBehaviorFlags_Fancy|ztGuiStaticTextBehaviorFlags_MonoSpaced, 2048);
		zt_guiItemSetAlign(dgh->details, ztAlign_Left|ztAlign_Top);
		zt_guiScrollContainerSetItem(scroll, dgh->details);

		zt_guiSizerAddItem(sizer_right, scroll, 1, padding);
	}

	_zt_guiDebugGuiHierarchyPopulate(dgh);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_GUI_DEBUG_TEXVIEW_NAME           "Texture Viewer"
#define ZT_GUI_DEBUG_TEXVIEW_DROPDOWN_NAME  "Texture Viewer Dropdown"
#define ZT_GUI_DEBUG_TEXVIEW_DISPLAY_NAME   "Texture Viewer Display"

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugTextureViewerRefresh()
{
	ZT_PROFILE_GUI("_zt_guiDebugTextureViewerRefresh");

	ztGuiItem *dropdown = zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_DROPDOWN_NAME, zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_NAME));
	zt_assert(dropdown);

	zt_guiComboBoxClear(dropdown);

	zt_fiz(zt_game->textures_count) {
		if (zt_game->textures[i].renderer == ztRenderer_Invalid) {
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
		zt_strMakePrintf(buffer, 256, "[%d] %d x %d %s %s", i, zt_game->textures[i].width, zt_game->textures[i].height, (render_tex ? "(render texture)" : (cubemap_tex ? "(cube map)" : "")), (zt_game->textures[i].name[0] == 0 ? "" : zt_game->textures[i].name));
		zt_guiComboBoxAppend(dropdown, buffer, (void*)i);
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugTextureViewerLoadTexture(ztTextureID tex_id)
{
	ZT_PROFILE_GUI("_zt_guiDebugTextureViewerLoadTexture");

	if (tex_id == ztInvalidID || zt_game->textures[tex_id].renderer == ztRenderer_Invalid) {
		return;
	}

	ztGuiThemeSprite sprite;
	sprite.type = ztGuiThemeSpriteType_Sprite;
	sprite.s = zt_spriteMake(tex_id, zt_vec2i(0, 0), zt_vec2i(zt_game->textures[tex_id].width, zt_game->textures[tex_id].height));

	ztGuiItem *display = zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_DISPLAY_NAME, zt_guiItemFindByName(ZT_GUI_DEBUG_TEXVIEW_NAME));

	ztVec2 scale = ztVec2::one;
	i32 max = zt_game->textures[tex_id].height;//zt_max(zt_game->textures[tex_id].width, zt_game->textures[tex_id].height);
	if (max > 1024) {
		scale.x = scale.y = 1.f / (max / 1024.f);
	}

	zt_guiSpriteDisplaySetSprite(display, &sprite, scale, zt_color(0, .1f, 0, 1));
	zt_guiItemAutoSize(display);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugTextureViewerOnRefresh, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugTextureViewerOnRefresh))
{
	_zt_guiDebugTextureViewerRefresh();
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugTextureViewerOnComboBox, ztInternal ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiDebugTextureViewerOnComboBox))
{
	_zt_guiDebugTextureViewerLoadTexture((ztTextureID)(pointer)zt_guiComboBoxGetItemUserData(combobox, selected));
}

// ================================================================================================================================================================================================

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

	zt_guiItemSetSize(window, zt_vec2(cam_ext.x - 2, cam_ext.y - 2));

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	{
		zt_guiSizerSizeToParent(sizer);

		ztGuiItem *sizer_top = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		{
			zt_guiSizerAddItem(sizer, sizer_top, 0, 0);

			ztGuiItem *dropdown = zt_guiMakeComboBox(sizer_top, zt_elementsOf(zt_game->textures));
			zt_guiItemSetName(dropdown, ZT_GUI_DEBUG_TEXVIEW_DROPDOWN_NAME);
			zt_guiItemSetSize(dropdown, zt_vec2(6, -1));
			zt_guiSizerAddItem(sizer_top, dropdown, 0, 3 / zt_pixelsPerUnit(), ztAlign_Top, ztGuiItemOrient_Horz);
			zt_guiComboBoxSetCallback(dropdown, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugTextureViewerOnComboBox), nullptr);

			ztGuiItem *button = zt_guiMakeButton(sizer_top, "Refresh");
			zt_guiSizerAddItem(sizer_top, button, 0, 3 / zt_pixelsPerUnit());
			zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugTextureViewerOnRefresh));
		}

		ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer);
		ztGuiItem *display = zt_guiMakeSpriteDisplay(scroll, (ztGuiThemeSprite*)nullptr);
		zt_guiItemSetName(display, ZT_GUI_DEBUG_TEXVIEW_DISPLAY_NAME);
		zt_guiScrollContainerSetItem(scroll, display);

		zt_guiSizerAddItem(sizer, scroll, 1, 3 / zt_pixelsPerUnit());
	}

	_zt_guiDebugTextureViewerRefresh();
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_GUI_DEBUG_PROFILER_NAME           "Profiler"

// ================================================================================================================================================================================================

struct ztDebugProfiler
{
	ztProfilerRenderState render_state;
	ztVec2                mouse_pos;
	bool                  mouse_clicked;

	ztGuiItem            *combo_thread;

};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerDisplayRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiDebugProfilerDisplayRender))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerDisplayRender");

	ztDebugProfiler *fps = (ztDebugProfiler*)item->functions.user_data;

	zt_profilerRender(draw_list, item->pos + offset, item->size, fps->mouse_pos, fps->mouse_clicked, &fps->render_state);
	fps->mouse_clicked = false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerDisplayInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiDebugProfilerDisplayInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerDisplayInputMouse");

	ztDebugProfiler *fps = (ztDebugProfiler*)item->functions.user_data;

	fps->mouse_pos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
	fps->mouse_clicked = input_mouse->leftJustPressed();
	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugProfilerDisplayCleanup))
{
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ================================================================================================================================================================================================

struct ztDebugProfilerOverview
{
	ztDebugProfiler *profiler;
	int              display_frame = -1;
	bool             mouse_clicked = false;
	ztVec2           mouse_pos;

	char             systems[16][32];
	i32              systems_hash[16];
	int              systems_count = 0;

	r32              systems_frame_time[ZT_PROFILER_FRAMES_KEPT][16];
	r32              frame_time        [ZT_PROFILER_FRAMES_KEPT];

	int              active_system = -1;

	ztGuiItem       *section_panel;
	ztGuiItem       *list_sections;
	ztGuiItem       *listbox_call_hier;
	ztGuiItem       *listbox_call_list;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugProfilerSectionListProcessHidden(ztDebugProfilerOverview *dpo)
{
	zt_fiz(dpo->listbox_call_hier->listbox.item_count) {
		zt_guiListBoxShowItem(dpo->listbox_call_hier, i);
		int index = (int)(pointer)zt_guiListBoxGetItemUserData(dpo->listbox_call_hier, i);
		while (index >= 0) {
			ztGuiItem *button = zt_guiItemFindByType(ztGuiItemType_Button, zt_guiListBoxGetItem(dpo->listbox_call_hier, index));
			if (button && zt_strEquals(button->label, "+")) {
				zt_guiListBoxHideItem(dpo->listbox_call_hier, i);

				ztGuiItem *my_button = zt_guiItemFindByType(ztGuiItemType_Button, zt_guiListBoxGetItem(dpo->listbox_call_hier, i));
				if(my_button && zt_strEquals(my_button->label, "-")) {
					zt_guiItemSetLabel(my_button, "+");
				}
			}
			index = (int)(pointer)zt_guiListBoxGetItemUserData(dpo->listbox_call_hier, index);
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerSectionListButton, ztInternal ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugProfilerSectionListButton))
{
	if(zt_strEquals(button->label, "+")) {
		zt_guiItemSetLabel(button, "-");
	}
	else {
		zt_guiItemSetLabel(button, "+");
	}

	ztDebugProfilerOverview *dpo = (ztDebugProfilerOverview*)user_data;
	_zt_guiDebugProfilerSectionListProcessHidden(dpo);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugProfilerOverviewRefreshGrouping(ztDebugProfilerOverview *dpo)
{
	zt_guiListBoxClear(dpo->listbox_call_hier);

	if (!zt_profilerIsPaused()) {
		zt_guiListBoxAppend(dpo->listbox_call_hier, "<Pause profiling and select a frame to see section details>", nullptr);
	}
	else {
		int display_thread = zt_guiComboBoxGetSelected(dpo->profiler->combo_thread);

		int display_frame = zt_game->profiler->current_frame - 1;
		if (display_frame < 0) {
			display_frame = ZT_PROFILER_FRAMES_KEPT - 1;
		}
		if (dpo->display_frame >= 0) {
			display_frame = dpo->display_frame;
		}

		ztProfiledThread *pt = &zt_game->profiler->threads[display_thread];
		ztProfiledSection *ps = pt->roots[display_frame];

		struct local
		{
			static void populateHier(ztDebugProfilerOverview *dpo, ztGuiItem *listbox, ztProfiledSection *section, int level, ztVec2& char_ext, int parent_idx)
			{
				r32 column_sizes[] = {
					char_ext.x * 64,	// section name
					char_ext.x * 9,		// times called
					char_ext.x * 12,	// time acc
					char_ext.x * 12,	// time acc per call
					char_ext.x * 12,	// time acc percent of parent
					char_ext.x * 12,	// time iso
					char_ext.x * 12,	// time iso per call
				};

				i32 column_align[] = {
					ztAlign_Left,
					ztAlign_Right,
					ztAlign_Right,
					ztAlign_Right,
					ztAlign_Right,
					ztAlign_Right,
					ztAlign_Right,
				};

				zt_staticAssert(zt_elementsOf(column_align) == zt_elementsOf(column_sizes));

				r32 padding = 3 / zt_pixelsPerUnit();

				if (listbox->listbox.header == nullptr) {
					// make the header

					const char *column_names[] = {
						"Section Name",
						"Called",
						"Time Acc",
						"(per call)",
						"(%)",
						"Time Iso",
						"(per call)",
					};

					zt_staticAssert(zt_elementsOf(column_names) == zt_elementsOf(column_sizes));

					ztGuiItem *panel = zt_guiMakePanel(listbox);
					ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz);
					zt_guiSizerSizeParent(sizer);

					zt_guiSizerAddStretcher(sizer, 0, char_ext.y / 2.f + padding);

					zt_fize(column_names) {
						ztGuiItem *label = zt_guiMakeStaticText(panel, column_names[i], ztGuiStaticTextBehaviorFlags_MonoSpaced);
						zt_guiItemSetSize(label, zt_vec2(column_sizes[i], char_ext.y));
						zt_guiItemSetAlign(label, column_align[i]);
						zt_guiSizerAddItem(sizer, label, 0, padding, column_align[i]);
					}

					zt_guiSizerRecalcImmediately(sizer);

					zt_guiListBoxSetHeaderItem(listbox, panel);
				}

				ztGuiItem *panel = zt_guiMakePanel(listbox);
				{
					char space_buffer[64] = { 0 };
					for (int i = 0; i < zt_min(zt_elementsOf(space_buffer) - 1, level * 3); ++i) {
						space_buffer[i] = ' ';
					}

					zt_strMakePrintf(section_name_str, 256, "%s%s", space_buffer, section->section);
					zt_strMakePrintf(called_str, 32, "%d", section->called);

					r32 percent_of_parent = section->parent ? (r32)(section->time_accum / section->parent->time_accum) : 1.f;

					r32 time_iso_val = (r32)section->time_accum;
					zt_flink(child, section->children) {
						time_iso_val -= (r32)child->time_accum;
					}

					time_iso_val *= 100000.f;

					r32 time_acc_val = (r32)section->time_accum * 1000000.f;

					zt_strMakePrintf(time_iso_str, 128, "%.2f", time_iso_val);
					zt_strMakePrintf(time_iso_per_str, 128, "%.4f", time_iso_val / section->called);
					zt_strMakePrintf(time_acc_str, 128, "%.2f", time_acc_val);
					zt_strMakePrintf(time_acc_per_str, 128, "%.4f", time_acc_val / section->called);
					zt_strMakePrintf(time_acc_pct_str, 128, "%.2f%%", percent_of_parent * 100.f);


					const char *column_vals[] = {
						section_name_str,
						called_str,
						time_acc_str,
						time_acc_per_str,
						time_acc_pct_str,
						time_iso_str,
						time_iso_per_str,
					};

					zt_staticAssert(zt_elementsOf(column_vals) == zt_elementsOf(column_sizes));

					ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz);
					zt_guiSizerSizeParent(sizer);

					if (section->children) {
						ztGuiItem *button = zt_guiMakeButton(panel, "-", ztGuiButtonBehaviorFlags_NoBackground);
						button->size.x = button->size.y = char_ext.y;
						zt_guiSizerAddItem(sizer, button, 0, padding);
						zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerSectionListButton), dpo);
					}
					else {
						zt_guiSizerAddStretcher(sizer, 0, char_ext.y / 2.f + padding);
					}

					zt_fize(column_vals) {
						ztGuiItem *label = zt_guiMakeStaticText(panel, column_vals[i], ztGuiStaticTextBehaviorFlags_MonoSpaced);
						zt_guiItemSetSize(label, zt_vec2(column_sizes[i], char_ext.y));
						zt_guiItemSetAlign(label, column_align[i]);
						zt_guiSizerAddItem(sizer, label, 0, padding, column_align[i]);
					}

					zt_guiSizerRecalcImmediately(sizer);
				}

				int my_idx = zt_guiListBoxAppend(listbox, panel, (void*)parent_idx);

				//zt_guiItemSetSize(panel, zt_vec2(char_ext.x * 200 - (level * char_ext.x * 4), char_ext.y));


				ztProfiledSection *children[512];
				int children_count = 0;

				zt_flink(child, section->children) {
					children[children_count++] = child;
					zt_assert(children_count < zt_elementsOf(children));

					//populate(dpo, listbox, child, level + 1, char_ext, my_idx);
				}

				struct sort
				{
					static int compare(const void *pone, const void *ptwo)
					{
						ztProfiledSection *sone = *(ztProfiledSection**)pone;
						ztProfiledSection *stwo = *(ztProfiledSection**)ptwo;

						if (sone->time_accum > stwo->time_accum) {
							return -1;
						}
						else {
							return 1;
						}
					}
				};

				qsort(children, children_count, zt_sizeof(ztProfiledSection*), sort::compare);

				zt_fiz(children_count) {
					populateHier(dpo, listbox, children[i], level + 1, char_ext, my_idx);
				}
			}

			static void populateList(ztDebugProfilerOverview *dpo, ztGuiItem *listbox, ztProfiledSection *sections, int sections_count, ztVec2& char_ext, int parent_idx)
			{
				struct ztChildInfo
				{
					char name[64];
					i32 name_hash;
					int called;
					r32 time_iso;
				};

				zt_guiListBoxClear(listbox);

				ztChildInfo children[512];
				int children_count = 0;

				zt_fiz(sections_count) {
					r64 time_iso = sections[i].time_accum;
					zt_flink(child, sections[i].children) {
						time_iso -= child->time_accum;
					}

					bool found = false;
					zt_fjz(children_count) {
						if (children[j].name_hash == sections[i].section_hash) {
							children[j].called += sections[i].called;
							children[j].time_iso += (r32)time_iso;
							found = true;
							break;
						}
					}

					if (!found) {
						int idx = children_count++;
						zt_strCpy(children[idx].name, zt_elementsOf(children[idx].name), sections[i].section);
						children[idx].name_hash = sections[i].section_hash;
						children[idx].called = sections[i].called;
						children[idx].time_iso = (r32)time_iso;
					}
				}

				struct sort
				{
					static int compare(const void *pone, const void *ptwo)
					{
						ztChildInfo *sone = (ztChildInfo*)pone;
						ztChildInfo *stwo = (ztChildInfo*)ptwo;

						if (sone->time_iso > stwo->time_iso) {
							return -1;
						}
						else {
							return 1;
						}
					}
				};

				qsort(children, children_count, zt_sizeof(ztChildInfo), sort::compare);

				r32 column_sizes[] = {
					char_ext.x * 48,	// section name
					char_ext.x * 9,		// times called
					char_ext.x * 12,	// time iso
					char_ext.x * 12,	// time iso per call
				};

				i32 column_align[] = {
					ztAlign_Left,
					ztAlign_Right,
					ztAlign_Right,
					ztAlign_Right,
				};

				zt_staticAssert(zt_elementsOf(column_align) == zt_elementsOf(column_sizes));

				r32 padding = 3 / zt_pixelsPerUnit();

				if (listbox->listbox.header == nullptr) {
					// make the header

					const char *column_names[] = {
						"Section Name",
						"Called",
						"Time Iso",
						"(per call)",
					};

					zt_staticAssert(zt_elementsOf(column_names) == zt_elementsOf(column_sizes));

					ztGuiItem *panel = zt_guiMakePanel(listbox);
					ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz);
					zt_guiSizerSizeParent(sizer);

					zt_fize(column_names) {
						ztGuiItem *label = zt_guiMakeStaticText(panel, column_names[i], ztGuiStaticTextBehaviorFlags_MonoSpaced);
						zt_guiItemSetSize(label, zt_vec2(column_sizes[i], char_ext.y));
						zt_guiItemSetAlign(label, column_align[i]);
						zt_guiSizerAddItem(sizer, label, 0, padding, column_align[i]);
					}

					zt_guiSizerRecalcImmediately(sizer);

					zt_guiListBoxSetHeaderItem(listbox, panel);
				}

				zt_fiz(children_count) {
					ztGuiItem *panel = zt_guiMakePanel(listbox);
					{
						zt_strMakePrintf(section_name_str, 256, "%s", children[i].name);
						zt_strMakePrintf(called_str, 32, "%d", children[i].called);

						r32 time_iso_val = (r32)children[i].time_iso * 1000000.f;

						zt_strMakePrintf(time_iso_str, 128, "%.2f", time_iso_val);
						zt_strMakePrintf(time_iso_per_str, 128, "%.4f", time_iso_val / children[i].called);

						char *column_vals[] = {
							section_name_str,
							called_str,
							time_iso_str,
							time_iso_per_str,
						};

						zt_staticAssert(zt_elementsOf(column_vals) == zt_elementsOf(column_sizes));

						ztGuiItem *sizer = zt_guiMakeSizer(panel, ztGuiItemOrient_Horz);
						zt_guiSizerSizeParent(sizer);

						zt_fize(column_vals) {
							ztGuiItem *label = zt_guiMakeStaticText(panel, column_vals[i], ztGuiStaticTextBehaviorFlags_MonoSpaced);
							zt_guiItemSetSize(label, zt_vec2(column_sizes[i], char_ext.y));
							zt_guiItemSetAlign(label, column_align[i]);
							zt_guiSizerAddItem(sizer, label, 0, padding, column_align[i]);
						}

						zt_guiSizerRecalcImmediately(sizer);
					}

					//int my_idx =
					zt_guiListBoxAppend(listbox, panel, (void*)parent_idx);

					//zt_guiItemSetSize(panel, zt_vec2(char_ext.x * 200 - (level * char_ext.x * 4), char_ext.y));
					//zt_guiTreeCollapseNode(tree, node);
				}
			}
		};

		ztFontID font = zt_guiThemeGetIValue(zt_guiItemGetTheme(dpo->listbox_call_hier), ztGuiThemeValue_i32_FontID, dpo->listbox_call_hier);
		ztVec2 char_ext = zt_fontGetExtents(font, "W");

		zt_guiItemLock(dpo->listbox_call_hier);
		zt_guiItemLock(dpo->listbox_call_list);

		local::populateHier(dpo, dpo->listbox_call_hier, ps, 0, char_ext, -1);
		local::populateList(dpo, dpo->listbox_call_list, pt->allocations[display_frame], pt->sections[display_frame], char_ext, -1);

		zt_guiItemUnlock(dpo->listbox_call_hier);
		zt_guiItemUnlock(dpo->listbox_call_list);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerOverviewInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiDebugProfilerOverviewInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerOverviewInputMouse");
	ztDebugProfilerOverview *dpo = (ztDebugProfilerOverview*)item->panel.user_data;

	dpo->mouse_pos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
	dpo->mouse_clicked = input_mouse->leftJustPressed();
	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerOverviewButtonPause, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugProfilerOverviewButtonPause))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerOverviewButtonCheck");
	ztDebugProfilerOverview *dpo = (ztDebugProfilerOverview*)user_data;

	if (zt_profilerIsPaused()) {
		zt_profilerResume();
		zt_guiItemSetLabel(button, "Pause");
	}
	else {
		zt_profilerPause();
		zt_guiItemSetLabel(button, "Resume");
	}

	_zt_guiDebugProfilerOverviewRefreshGrouping(dpo);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerOverviewButtonCheck, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiDebugProfilerOverviewButtonCheck))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerOverviewButtonCheck");
	ztDebugProfilerOverview *dpo = (ztDebugProfilerOverview*)user_data;

	zt_guiItemShow(dpo->section_panel, zt_guiCheckboxGetValue(button));
	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(button));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugProfilerOverviewRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiDebugProfilerOverviewRender))
{
	ZT_PROFILE_GUI("_zt_guiDebugProfilerOverviewRender");
	ztDebugProfilerOverview *dpo = (ztDebugProfilerOverview*)item->panel.user_data;

	r32 ppu = zt_pixelsPerUnit();
	r32 alpha = zt_guiManagerHasKeyboardFocus(item->gm) ? 1 : .10f;
	ztVec4 alpha_vec = zt_vec4(1,1,1,alpha);

	zt_drawListAddSolidOutlinedRect2D(draw_list, offset + item->pos, item->size, zt_color(0,0,0,.25f), zt_color(1,1,1,.25f));

	ztVec2 size = item->size;
	ztVec2 pos = item->pos + offset;

	ztVec2 timeline_size = zt_vec2(size.x - 10 / ppu, 30 / ppu);
	ztVec2 timeline_pos = zt_vec2(pos.x, pos.y + ((size.y - timeline_size.y) / 2) - (5 / ppu));

	r32 pixel_size = 2 / ppu;
	r32 width_per_frame = (timeline_size.x - ((ZT_PROFILER_FRAMES_KEPT + 1) * pixel_size)) / ZT_PROFILER_FRAMES_KEPT;

	int display_frame = zt_game->profiler->current_frame - 1;
	if (display_frame < 0) {
		display_frame = ZT_PROFILER_FRAMES_KEPT - 1;
	}

	int display_thread = zt_guiComboBoxGetSelected(dpo->profiler->combo_thread);

	if (dpo->display_frame >= 0) {
		display_frame = dpo->display_frame;
	}

	// draw the active frame and display frame indicators
	zt_drawListPushTexture(draw_list, ztTextureDefault);
	{
		zt_drawListPushColor(draw_list, ztColor_Black * alpha_vec);
		zt_drawListAddFilledRect2D(draw_list, timeline_pos, timeline_size, ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);

		zt_drawListPushColor(draw_list, ztColor_Gray * alpha_vec);

		ztVec2 frame_size = zt_vec2(width_per_frame, timeline_size.y - (pixel_size * 2));
		r32 x = (timeline_pos.x - (timeline_size.x / 2)) + (width_per_frame / 2) + pixel_size;
		zt_fiz(ZT_PROFILER_FRAMES_KEPT) {
			ztVec2 fpos = zt_vec2(x, timeline_pos.y);
			if (dpo->mouse_clicked && i != zt_game->profiler->current_frame && zt_collisionPointInRect(dpo->mouse_pos, fpos, frame_size)) {
				if (dpo->display_frame == i) {
					dpo->display_frame = -1;
				}
				else {
					dpo->display_frame = i;
				}
				_zt_guiDebugProfilerOverviewRefreshGrouping(dpo);
			}

			if (i == zt_game->profiler->current_frame) {
				zt_drawListPushColor(draw_list, ztColor_Green * alpha_vec);
			}
			else if (i == display_frame) {
				zt_drawListPushColor(draw_list, ztColor_Orange * alpha_vec);
			}

			zt_drawListAddFilledRect2D(draw_list, fpos, frame_size, ztVec2::zero, ztVec2::one);
			x += width_per_frame + pixel_size;

			if (i == zt_game->profiler->current_frame || i == display_frame) {
				zt_drawListPopColor(draw_list);
			}

			dpo->frame_time[i] = 0;
			zt_fkz(dpo->systems_count) {
				dpo->systems_frame_time[i][k] = 0;
			}

			ztProfiledThread *pt = &zt_game->profiler->threads[display_thread];
			zt_fjz(pt->sections[i]) {
				ztProfiledSection *ps = &pt->allocations[i][j];
				int sec_idx = -1;
				zt_fkz(dpo->systems_count) {
					if (dpo->systems_hash[k] == ps->system_hash) {
						sec_idx = k;
						break;
					}
				}
				if (sec_idx == -1) {
					sec_idx = dpo->systems_count;
					zt_strCpy(dpo->systems[dpo->systems_count], zt_elementsOf(dpo->systems[dpo->systems_count]), ps->system);
					dpo->systems_hash[dpo->systems_count] = ps->system_hash;
					dpo->systems_count += 1;
				}

				r32 this_calls_time = (r32)ps->time_accum;

				zt_flink(child, ps->children) {
					this_calls_time -= (r32)child->time_accum;
				}

				dpo->frame_time[i] += this_calls_time;
				dpo->systems_frame_time[i][sec_idx] += this_calls_time;
			}
		}

		zt_drawListPopColor(draw_list);
	}

	static ztColor system_colors[] = {
		ztColor_Red, ztColor_Yellow, ztColor_Green, ztColor_Orange, ztColor_LightBlue, ztColor_LightGreen, ztColor_LightRed, ztColor_Blue, ztColor_Purple, ztColor_DarkRed, ztColor_DarkGreen, ztColor_DarkBlue, ztColor_DarkPurple, ztColor_DarkYellow, ztColor_DarkOrange
	};

	ztFontID font = zt_guiThemeGetIValue(theme, ztGuiThemeValue_i32_TextEditFontID, item);
	ztVec2 legend_text_ext = zt_fontGetExtents(font, "A");
	ztVec2 legend_entry_size = zt_vec2(128 / ppu, legend_text_ext.y);

	int legend_columns = zt_convertToi32Ceil(size.x / legend_entry_size.x);
	int legend_rows    = zt_convertToi32Ceil(dpo->systems_count / (r32)legend_columns);

	// draw the time graph (showing details of each frame)
	ztVec2 timegraph_size = zt_vec2(size.x - 10 / ppu, ((size.y - timeline_size.y) - (15 / ppu)) - ((legend_entry_size.y + 3 / ppu) * legend_rows));
	ztVec2 timegraph_pos = zt_vec2(pos.x, timeline_pos.y - (timeline_size.y / 2 + timegraph_size.y / 2 + 5 / ppu));

	if (dpo->mouse_clicked) {
		dpo->active_system = -1;
	}

	// adjust for current frame/active system
	r32 diff = legend_text_ext.y + (8 / ppu);
	timegraph_size.y -= diff;
	timegraph_pos.y += diff / 2;

	bool use_bars = true;

	int mouse_over_frame = -1;
	int mouse_over_system = -1;

	char tooltip[4096] = {0};

	if (use_bars) {
		//zt_drawListPushColor(draw_list, ztColor_Black * alpha_vec);
		//zt_drawListAddFilledRect2D(draw_list, timegraph_pos, timegraph_size, ztVec2::zero, ztVec2::one);
		//zt_drawListPopColor(draw_list);

		r64 max = 0;
		zt_fiz(ZT_PROFILER_FRAMES_KEPT) {
			if (i == zt_game->profiler->current_frame || zt_game->profiler->threads[display_thread].roots[i] == nullptr) {
				continue;
			}

			max = zt_max(max, zt_game->profiler->threads[display_thread].roots[i]->time_accum);
		}

		max *= 1.1f;
		//max = 1000 / 60.f;

		if (max) {
			r32 x = (timegraph_pos.x - (timegraph_size.x / 2)) + (width_per_frame / 2) + pixel_size;
			//zt_drawListPushColor(draw_list, ztColor_Green);
			ztVec2 frame_size = zt_vec2(width_per_frame, timegraph_size.y - (pixel_size * 2));
			zt_fiz(ZT_PROFILER_FRAMES_KEPT) {
				if (i == zt_game->profiler->current_frame || zt_game->profiler->threads[display_thread].roots[i] == nullptr) {
					x += width_per_frame + pixel_size;
					continue;
				}

				r32 pct = (r32)(zt_game->profiler->threads[display_thread].roots[i]->time_accum / max);

				r32 this_height = frame_size.y * pct;
				r32 start_y = timegraph_pos.y - (timegraph_size.y / 2);

				r32 unclaimed_time = dpo->frame_time[i];

				zt_fjz(dpo->systems_count) {
					r32 sys_pct = dpo->systems_frame_time[i][j] / dpo->frame_time[i];

					ztVec2 fs_pos = zt_vec2(x, start_y + (this_height * sys_pct / 2));
					ztVec2 fs_size = zt_vec2(frame_size.x, this_height * sys_pct);

					if (zt_collisionPointInRect(dpo->mouse_pos, fs_pos - zt_vec2(1 / ppu, 0), fs_size + zt_vec2(2 / ppu, 0))) {
						mouse_over_frame = i;
						mouse_over_system = j;
					}

					zt_drawListPushColor(draw_list, system_colors[j % zt_elementsOf(system_colors)] * alpha_vec);
					zt_drawListAddFilledRect2D(draw_list, fs_pos, fs_size, ztVec2::zero, ztVec2::one);
					zt_drawListPopColor(draw_list);

					start_y += this_height *  sys_pct;
					unclaimed_time -= dpo->systems_frame_time[i][j];
				}

				if (unclaimed_time > 0) {
					r32 sys_pct = unclaimed_time / dpo->frame_time[i];

					zt_drawListPushColor(draw_list, ztColor_DarkGray * alpha_vec);
					zt_drawListAddFilledRect2D(draw_list, zt_vec2(x, start_y + (this_height * sys_pct / 2)), zt_vec2(frame_size.x, this_height * sys_pct), ztVec2::zero, ztVec2::one);
					zt_drawListPopColor(draw_list);
				}

				//				zt_drawListAddFilledRect2D(draw_list, zt_vec2(x, timegraph_pos.y - ((frame_size.y * (1 - pct)) / 2)), zt_vec2(frame_size.x, zt_max(pixel_size, frame_size.y * pct)), ztVec2::zero, ztVec2::one);
				x += width_per_frame + pixel_size;
			}
			//zt_drawListPopColor(draw_list);
		}

		if (mouse_over_frame != -1) {
			//int frame = mouse_over_frame;
			zt_strCatf(tooltip, zt_elementsOf(tooltip), "Frame Time: %.2f us (%.2f fps)\n\n", dpo->frame_time[mouse_over_frame] * 1000000.f, 1 / dpo->frame_time[mouse_over_frame]);
			zt_strCatf(tooltip, zt_elementsOf(tooltip), "System: %s\n   Time: %.2f us (%.2f %%)", dpo->systems[mouse_over_system], dpo->systems_frame_time[mouse_over_frame][mouse_over_system] * 1000000.f, (dpo->systems_frame_time[mouse_over_frame][mouse_over_system] / dpo->frame_time[mouse_over_frame]) * 100.f);

			if (dpo->mouse_clicked) {
				dpo->active_system = mouse_over_system;
				_zt_guiDebugProfilerOverviewRefreshGrouping(dpo);
			}
		}
	}
	else { // todo: line graph
	}

	// draw legend
	{
		ztVec2 legend_pos = zt_vec2(timegraph_pos.x - (timegraph_size.x / 2) + (3 / ppu), timegraph_pos.y - (timegraph_size.y / 2) - (5 / ppu));
		zt_fiz(dpo->systems_count) {
			zt_drawListPushColor(draw_list, system_colors[i] * alpha_vec);
			zt_drawListAddFilledRect2D(draw_list, legend_pos + zt_vec2(8 / ppu, -8 / ppu), zt_vec2(16 / ppu, 16 / ppu), ztVec2::zero, ztVec2::one);
			zt_drawListPopColor(draw_list);
			legend_pos.x += 22 / ppu;

			ztVec2 text_ext;
			zt_drawListAddFancyText2D(draw_list, font, dpo->systems[i], legend_pos, ztAlign_Left|ztAlign_Top, ztAnchor_Left|ztAnchor_Top, &text_ext, ztColor_White * alpha_vec);

			legend_pos.x += text_ext.x + 25 / ppu;
		}
	}

	{
		// draw horizontal frame bar
		ztVec2 as_pos = zt_vec2(timegraph_pos.x - (timegraph_size.x / 2) + (3 / ppu), timegraph_pos.y - (timegraph_size.y / 2) - legend_entry_size.y - (14 / ppu));

		zt_drawListPushColor(draw_list, system_colors[dpo->active_system] * alpha_vec);
		zt_drawListAddFilledRect2D(draw_list, as_pos + zt_vec2(8 / ppu, -8 / ppu), zt_vec2(16 / ppu, 16 / ppu), ztVec2::zero, ztVec2::one);
		zt_drawListPopColor(draw_list);
		as_pos.x += 22 / ppu;

		const char *frame = mouse_over_system == -1 ? "selected frame" : "hovered frame";

		zt_strMakePrintf(system_name, 128, "%s (%s):", (dpo->active_system == -1 ? "Active Frame" : dpo->systems[dpo->active_system]), frame);
		ztVec2 text_ext;
		zt_drawListAddFancyText2D(draw_list, font, system_name, as_pos, ztAlign_Left|ztAlign_Top, ztAnchor_Left|ztAnchor_Top, &text_ext, ztColor_White * alpha_vec);

		ztVec2 bar_size = zt_vec2(timegraph_size.x - (text_ext.x + 28 / ppu), 16 / ppu);
		ztVec2 bar_pos = zt_vec2(timegraph_pos.x + (timegraph_size.x - bar_size.x) / 2.f, as_pos.y - (8 / ppu));

		int active_frame = mouse_over_system == -1 ? display_frame : mouse_over_frame;

		r32 system_time = dpo->active_system == -1 ? dpo->frame_time[active_frame] : dpo->systems_frame_time[active_frame][dpo->active_system];

		r32 start_x = bar_pos.x - (bar_size.x / 2);

		struct SectionEntry
		{
			char *section;
			i32   section_hash;
			r32   time_iso;
			r32   time_acc;
			int   called;


			static int compare(const void *a, const void *b)
			{
				SectionEntry *pa = (SectionEntry*)a;
				SectionEntry *pb = (SectionEntry*)b;

				if (pa->time_iso > pb->time_iso) {
					return -1;
				}
				else if (pa->time_iso < pb->time_iso) {
					return 1;
				}
				return 0;
			}
		};

		SectionEntry section_entries[ZT_PROFILER_MAX_SECTIONS_PER_FRAME];
		int section_entries_count = 0;

		ztProfiledThread *pt = &zt_game->profiler->threads[display_thread];
		int sec_count = 0;
		zt_fjz(pt->sections[active_frame]) {
			ztProfiledSection *ps = &pt->allocations[active_frame][j];
			if (dpo->active_system != -1 && ps->system_hash != dpo->systems_hash[dpo->active_system]) {
				continue;
			}

			int entry_idx = -1;
			zt_fiz(section_entries_count) {
				if (section_entries[i].section_hash == ps->section_hash) {
					entry_idx = i;
					break;
				}
			}
			if (entry_idx == -1) {
				section_entries[section_entries_count].section = (char*)ps->section;
				section_entries[section_entries_count].section_hash = ps->section_hash;
				section_entries[section_entries_count].time_iso = 0;
				section_entries[section_entries_count].time_acc = 0;
				section_entries[section_entries_count].called = 0;
				entry_idx = section_entries_count++;
			}

			r32 this_calls_time = (r32)ps->time_accum;
			zt_flink(child, ps->children) {
				this_calls_time -= (r32)child->time_accum;
			}

			section_entries[entry_idx].time_iso += this_calls_time;
			section_entries[entry_idx].time_acc += (r32)ps->time_accum;
			section_entries[entry_idx].called += ps->called;
		}

		qsort(section_entries, section_entries_count, zt_sizeof(SectionEntry), SectionEntry::compare);

		zt_fjz(section_entries_count) {

			r32 sec_pct = section_entries[j].time_iso / system_time;

			ztVec2 ss_pos = zt_vec2(start_x + (bar_size.x * sec_pct / 2), bar_pos.y);
			ztVec2 ss_size = zt_vec2(bar_size.x * sec_pct, bar_size.y);

			if (zt_collisionPointInRect(dpo->mouse_pos, ss_pos, ss_size)) {
				// mouse over this section
				if (tooltip[0] == 0) {
					if (dpo->active_system != -1) {
						zt_strCatf(tooltip, zt_elementsOf(tooltip), "System: %s (%.2f us)\n\n", dpo->systems[dpo->active_system], system_time * 1000000.f);
					}
					else {
						zt_strCatf(tooltip, zt_elementsOf(tooltip), "Frame time: %.2f us (%.2f fps)\n\n", system_time * 1000000.f, 1.f / system_time);
					}
				}
				zt_strCatf(tooltip, zt_elementsOf(tooltip), "Section: %s\n    Called: %d\n    Time Isolated: %.2f us (%.4f us/call) (%.2f%%)\n    Time Accum: %.2f us (%.4f us/call)\n\n", section_entries[j].section, section_entries[j].called, section_entries[j].time_iso * 1000000.f, section_entries[j].time_iso * 1000000.f / section_entries[j].called, section_entries[j].time_iso / system_time * 100, section_entries[j].time_acc * 1000000.f, section_entries[j].time_acc * 1000000.f / section_entries[j].called);
			}

			zt_drawListPushColor(draw_list, system_colors[sec_count++ % zt_elementsOf(system_colors)] * alpha_vec);
			zt_drawListAddFilledRect2D(draw_list, ss_pos, ss_size, ztVec2::zero, ztVec2::one);
			zt_drawListPopColor(draw_list);

			start_x += bar_size.x * sec_pct;
		}

		//		zt_drawListAddSolidRect2D(draw_list, bar_pos, bar_size, ztColor_White * alpha_vec);
	}

	if (tooltip[0] != 0 && zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver)) {
		ztVec2 tt_pad = zt_vec2(10 / ppu, 10 / ppu);
		ztVec2 tt_ext = zt_fontGetExtents(font, tooltip) + tt_pad;
		ztVec2 tt_pos = dpo->mouse_pos;

		tt_pos.x += (dpo->mouse_pos.x > timegraph_pos.x ? -tt_ext.x : tt_ext.x) / 2;
		tt_pos.y += (dpo->mouse_pos.y > timegraph_pos.y ? -tt_ext.y : tt_ext.y) / 2;

		zt_drawListAddSolidOutlinedRect2D(draw_list, tt_pos, tt_ext, ztColor_Black * alpha_vec, ztColor_White * alpha_vec);
		zt_drawListAddFancyText2D(draw_list, font, tooltip, tt_pos + zt_vec2(tt_ext.x / -2, 0) + zt_vec2(tt_pad.x / 2, tt_pad.y / -2), ztAlign_Left, ztAnchor_Left, nullptr, ztColor_White * alpha_vec);

		if (dpo->mouse_clicked) {
			dpo->active_system = mouse_over_system;
		}
	}

	zt_drawListPopTexture(draw_list);
}


// ================================================================================================================================================================================================

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

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window = zt_guiMakeWindow("Profiler", ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);
	zt_guiItemSetSize(window, zt_cameraOrthoGetViewportSize(gm->gui_camera) - zt_vec2(1, 1.5f));

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(sizer);

	ztGuiItem *sizer_control_bar = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
	zt_guiSizerAddItem(sizer, sizer_control_bar, 0, padding);

	ztGuiItem *combo_thread = zt_guiMakeComboBox(sizer_control_bar, ZT_MAX_THREADS);
	combo_thread->size.x = 200 / zt_pixelsPerUnit();

	zt_fize(zt_game->profiler->threads) {
		if (i == 0) {
			zt_guiComboBoxAppend(combo_thread, "Main Thread");
		}
		else {
			zt_strMakePrintf(thread_name, 128, "Thread %d", i);
			zt_guiComboBoxAppend(combo_thread, thread_name);
		}
	}

	prof->combo_thread = combo_thread;

	zt_guiSizerAddItem(sizer_control_bar, zt_guiMakeStaticText(sizer_control_bar, "Thread:"), 0, padding);
	zt_guiSizerAddItem(sizer_control_bar, combo_thread, 0, padding);

//	ztGuiItem *combo_display = zt_guiMakeComboBox(sizer_control_bar, 2);
//	zt_guiComboBoxAppend(combo_display, "Bars");
//	zt_guiComboBoxAppend(combo_display, "Lines");
//
//	zt_guiSizerAddStretcher(sizer_control_bar, 0, padding * 2);
//	zt_guiSizerAddItem(sizer_control_bar, zt_guiMakeStaticText(sizer_control_bar, "Display:"), 0, padding);
//	zt_guiSizerAddItem(sizer_control_bar, combo_display, 0, padding);

	zt_guiSizerAddStretcher(sizer_control_bar, 0, padding * 2);
	ztGuiItem *check_sections = zt_guiMakeCheckbox(sizer_control_bar, "Show Sections Details");
	zt_guiCheckboxSetValue(check_sections, false);
	zt_guiSizerAddItem(sizer_control_bar, check_sections, 0, padding);

	ztGuiItem *button = zt_guiMakeButton(sizer_control_bar, "Pause");
	zt_guiSizerAddStretcher(sizer_control_bar, 1);
	zt_guiSizerAddItem(sizer_control_bar, button, 0, padding);

	ztDebugProfilerOverview* overview_data = zt_mallocStructArena(ztDebugProfilerOverview, gm->arena);
	*overview_data = {};
	overview_data->profiler = prof;
	ztGuiItem *overview = zt_guiMakePanel(sizer, 0, overview_data, gm->arena);
	overview->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerOverviewInputMouse);
	overview->functions.render = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerOverviewRender);
	overview->size.y = overview->min_size.y = 192 / zt_pixelsPerUnit();

	zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerOverviewButtonPause), overview_data);
	zt_guiButtonSetCallback(check_sections, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerOverviewButtonCheck), overview_data);

	zt_guiSizerAddItem(sizer, overview, 1, padding);

	ztGuiItem *section_panel = zt_guiMakePanel(sizer);
	{
		zt_guiSizerAddItem(sizer, section_panel, 3, padding);
		overview_data->section_panel = section_panel;

		ztGuiItem *section_panel_sizer = zt_guiMakeSizer(section_panel, ztGuiItemOrient_Horz);

		{
			ztGuiItem *listbox_call_hier = zt_guiMakeListBox(section_panel_sizer, ztGuiListBoxBehaviorFlags_AlternateRowColor, ZT_PROFILER_MAX_SECTIONS_PER_FRAME * 16);
			zt_guiSizerAddItem(section_panel_sizer, listbox_call_hier, 1, padding);
			overview_data->listbox_call_hier = listbox_call_hier;
		}

		{
			ztGuiItem *listbox_call_list = zt_guiMakeListBox(section_panel_sizer, ztGuiListBoxBehaviorFlags_AlternateRowColor, ZT_PROFILER_MAX_SECTIONS_PER_FRAME * 16);
			zt_guiSizerAddItem(section_panel_sizer, listbox_call_list, 1, padding);
			overview_data->listbox_call_list = listbox_call_list;
		}

		_zt_guiDebugProfilerOverviewRefreshGrouping(overview_data);

		zt_guiItemHide(section_panel);
	}

//	ztGuiItem *list_sections = zt_guiMakeListBox(sizer, ztGuiListBoxBehaviorFlags_MultiSelect, 128);
//	{
//		zt_guiSizerAddItem(sizer, list_sections, 1, padding);
//
//		zt_fiz(50) {
//			zt_strMakePrintf(item, 32, "Item %d", i+1);
//			zt_guiListBoxAppend(list_sections,  item, nullptr);
//		}
//	}

	zt_guiSizerRecalcImmediately(sizer);

//	ztGuiItem *profiler = zt_guiMakePanel(sizer);
//	zt_guiSizerAddItem(sizer, profiler, 1, padding);
//
//	profiler->functions.user_data = prof;
//	profiler->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerDisplayRender);
//	profiler->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerDisplayInputMouse);
//	profiler->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugProfilerDisplayCleanup);
}

// ================================================================================================================================================================================================

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#define ZT_DEBUG_MEMORY_INSPECTOR_WINDOW_NAME	    "Memory Inspector"
#define ZT_DEBUG_MEMORY_INSPECTOR_PANEL_NAME	    "_zt_debugMemoryInspectorPanelName"
#define ZT_DEBUG_MEMORY_INSPECTOR_LINE_HEIGHT	    (17 / zt_pixelsPerUnit())
#define ZT_DEBUG_MEMORY_INSPECTOR_BYTE_WIDTH_MIN    (0.000001f)
#define ZT_DEBUG_MEMORY_INSPECTOR_BYTE_WIDTH_MAX    (0.005f)

// ================================================================================================================================================================================================

struct ztDebugMemory
{
	ztMemoryArena *arenas[32];
	char           aliases[32][64];
	int            arenas_count = 0;
	int            active_arena = 0;

	ztVec2         mouse_pos = ztVec2::zero;
	bool           mouse_clicked = false;

	ztGuiItem     *combobox;
	ztGuiItem     *hover_info;
	ztGuiItem     *source_info;
	
	r32            byte_width_multiplier = .005f;
	bool           color_by_file = true;

	const char     *source_info_last_file = nullptr;
	char            source_info_buffer[512];

	char            source_path[ztFileMaxPath];
	char           *source_dir_listing;
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugMemoryDisplayRefresh(ztDebugMemory *mem)
{

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugMemoryDisplayComboSelected, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiDebugMemoryDisplayComboSelected))
{
	ztDebugMemory *mem = (ztDebugMemory*)user_data;
	mem->active_arena = selected;
	_zt_guiDebugMemoryDisplayRefresh(mem);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugMemoryDisplayUpdate, ztInternal ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiDebugMemoryDisplayUpdate))
{
	ZT_PROFILE_GUI("_zt_guiDebugMemoryDisplayUpdate");

	ztDebugMemory *mem = (ztDebugMemory*)item->functions.user_data;

	ztMemoryArena *arena = mem->arenas[mem->active_arena];
	if (arena == nullptr) {
		return;
	}

	ztVec2 size = item->size;

	r32 line_height = ZT_DEBUG_MEMORY_INSPECTOR_LINE_HEIGHT;
	r32 total_width = zt_lerp(ZT_DEBUG_MEMORY_INSPECTOR_BYTE_WIDTH_MIN, ZT_DEBUG_MEMORY_INSPECTOR_BYTE_WIDTH_MAX, mem->byte_width_multiplier) * arena->total_size;

	item->size.y = (zt_convertToi32Floor(total_width / size.x) + 1) * line_height;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugMemoryDisplayRender, ztInternal ZT_FUNC_GUI_ITEM_RENDER(_zt_guiDebugMemoryDisplayRender))
{
	ZT_PROFILE_GUI("_zt_guiDebugMemoryDisplayRender");

	ztDebugMemory *mem = (ztDebugMemory*)item->functions.user_data;

	ztMemoryArena *arena = mem->arenas[mem->active_arena];
	if (arena == nullptr) {
		return;
	}

	ztVec2 ppos = offset;
	ztVec2 psize = item->parent ? item->parent->size : ztVec2::zero;


	ztVec2 pos = offset + item->pos;

	ztVec2 size = item->size;

	r32 line_height = ZT_DEBUG_MEMORY_INSPECTOR_LINE_HEIGHT;
	r32 pixels_per_byte = zt_lerp(ZT_DEBUG_MEMORY_INSPECTOR_BYTE_WIDTH_MIN, ZT_DEBUG_MEMORY_INSPECTOR_BYTE_WIDTH_MAX, mem->byte_width_multiplier);

	ztColor colors[] = {
		zt_colorRgb(66, 199, 179),
		zt_colorRgb(232, 98, 98),
		zt_colorRgb(111, 98, 232),
		zt_colorRgb(104, 213, 93),
		zt_colorRgb(213, 93, 155),
		zt_colorRgb(224, 226, 71),
		zt_colorRgb(160, 66, 199),
		zt_colorRgb(226, 177, 71),
	};

	ztColor colors_by_file[zt_elementsOf(arena->file_names)];
	zt_fize(colors_by_file) {
		colors_by_file[i] = colors[i % zt_elementsOf(colors)];
	}

	int color_idx = 0;

	char hover_info[512] = {0};

	int hover_count = 0;

	zt_fzz(2) {
		r32 x_pos_start = size.x / -2;
		r32 x_pos = 0;
		r32 y_pos_start = (size.y / 2) - line_height / 2;
		r32 y_pos = 0;

		bool has_drawn = false;
		bool early_out = false;

		if (z == 1) {
			zt_drawListPushTexture(draw_list, ztTextureDefault);
			zt_drawListPushColor(draw_list, zt_colorRgb(240, 240, 240));
		}

		zt_flink(alloc, arena->latest) {
			r32 pixels_for_alloc = pixels_per_byte * alloc->length;

			ztColor color = colors[color_idx];
			color_idx = (color_idx + 1) % zt_elementsOf(colors);

			if (mem->color_by_file) {
				i32 hash = zt_strHash(alloc->file);
				zt_fjze(arena->file_names_hashes) {
					if (arena->file_names_hashes[j] == hash) {
						color = colors_by_file[j];
					}
				}
			}

			if (alloc->freed == 1) {
				color = ztColor_Black;
			}

			while(pixels_for_alloc > 0) {
				r32 x_pixels_left_this_line = size.x - x_pos;
				if (x_pixels_left_this_line <= 0) {
					y_pos += line_height;
					x_pos = 0;
					x_pixels_left_this_line = size.x;
				}

				r32 x_pixels_this_alloc = zt_min(pixels_for_alloc, x_pixels_left_this_line);
				pixels_for_alloc = pixels_for_alloc - x_pixels_this_alloc;


				ztVec2 bpos = pos + zt_vec2(x_pos_start + x_pos + (x_pixels_this_alloc / 2), y_pos_start - y_pos);
				ztVec2 bsize = zt_vec2(x_pixels_this_alloc, line_height);

				if (zt_collisionAABBInAABB(zt_vec3(ppos,0), zt_vec3(psize, 0), zt_vec3(bpos, 0), zt_vec3(bsize, 0))) {
					has_drawn = true;

					bool mouse_colliding = zt_collisionPointInRect(mem->mouse_pos, bpos, bsize);
					if (z == 0) {

						r32 color_pct = .85f;
						if (mouse_colliding) {
							color_pct = 1;
							hover_count += 1;
							if (hover_count == 1) {
								char size[128];
								zt_strBytesToString(size, zt_elementsOf(size), alloc->length);
								zt_strCat(hover_info, zt_elementsOf(hover_info), size);
								zt_strCat(hover_info, zt_elementsOf(hover_info), "  //  ");
								if (alloc->freed == 1) {
									zt_strCat(hover_info, zt_elementsOf(hover_info), "free space");
								}
								else {
									zt_strCat(hover_info, zt_elementsOf(hover_info), alloc->file == nullptr ? "(null)" : alloc->file + 1);
									zt_strCat(hover_info, zt_elementsOf(hover_info), " (");
									zt_strMakePrintf(file_line, 32, "%d", alloc->file_line);
									zt_strCat(hover_info, zt_elementsOf(hover_info), file_line);
									zt_strCat(hover_info, zt_elementsOf(hover_info), ")  //  ");

									zt_strMakePrintf(address, 64, "0x%llx", (long long unsigned int)alloc->start);
									zt_strCat(hover_info, zt_elementsOf(hover_info), address);
								}
								zt_strCat(hover_info, zt_elementsOf(hover_info), "  //  ");

								if (!zt_strEquals(alloc->file, mem->source_info_last_file)) {
									mem->source_info_last_file = alloc->file;

									mem->source_info_buffer[0] = 0;
									if (alloc->file != nullptr) {
										char file_name[ztFileMaxPath] = {0};

										ztToken tokens[256];
										int tokens_count = zt_strTokenize(mem->source_dir_listing, "\n", tokens, zt_elementsOf(tokens));
										zt_fiz(zt_min(zt_elementsOf(tokens), tokens_count)) {
											char file_name_only[ztFileMaxPath];
											zt_strCpy(file_name_only, zt_elementsOf(file_name_only), mem->source_dir_listing + tokens[i].beg, tokens[i].len);

											if (zt_strEquals(file_name_only, alloc->file + 1)) {
												zt_fileConcatFileToPath(file_name, zt_elementsOf(file_name), mem->source_path, file_name_only);
												break;
											}
										}

										if (file_name[0] == 0 || !zt_fileExists(file_name)) {
											if (zt_strStartsWith(alloc->file + 1, "zt_")) {
												char zt_path[ztFileMaxPath];
												zt_fileConcatFileToPath(zt_path, zt_elementsOf(zt_path), mem->source_path, "../../ZeroTolerance");
												if (zt_directoryExists(zt_path)) {
													zt_fileConcatFileToPath(file_name, zt_elementsOf(file_name), zt_path, alloc->file + 1);
												}
											}
										}

										if (zt_fileExists(file_name)) {
											i32 data_size = 0;
											char *data_beg = (char*)zt_readEntireFile(file_name, &data_size, false, item->gm->arena);
											const char *data = data_beg;

											int lines = alloc->file_line;
											while (lines-- > 0 && data) {
												data = zt_strFind(data, data_size - (int)(data - data_beg), "\n");
												if (data) ++data;

												if (lines == 1) {
													const char *find[] = {"\r", "\n"};
													while (*data == ' ' || *data == '\t') ++data;

													int end = zt_strFindFirstOfPos(data, find, zt_elementsOf(find));
													if (end != ztStrPosNotFound) {
														zt_strCpy(mem->source_info_buffer, zt_elementsOf(mem->source_info_buffer), data, end);
													}
												}
											}

											zt_freeArena(data_beg, item->gm->arena);
										}
									}
									zt_guiItemSetLabel(mem->source_info, mem->source_info_buffer);
								}
							}
						}

						zt_drawListAddSolidRect2D(draw_list, bpos, bsize, color * color_pct);
					}
					else {
						zt_drawListAddEmptyRect(draw_list, bpos, bsize);
					}
				}
				else {
					if (has_drawn) {
						early_out = true;
						break;
					}
				}

				x_pos += x_pixels_this_alloc;
				if (early_out) break;
			}
			if (early_out) break;
		}

		if (z == 1) {
			zt_drawListPopColor(draw_list);
			zt_drawListPopTexture(draw_list);
		}
	}

	if (hover_count == 0 && mem->source_info_buffer[0] != 0) {
		zt_guiItemSetLabel(mem->source_info, nullptr);
		mem->source_info_buffer[0] = 0;
		mem->source_info_last_file = nullptr;
	}

	char total_size_str[128];
	zt_strBytesToString(total_size_str, zt_elementsOf(total_size_str), arena->current_used);
	zt_strCat(hover_info, zt_elementsOf(hover_info), total_size_str);
	zt_strCat(hover_info, zt_elementsOf(hover_info), " used from ");
	zt_strBytesToString(total_size_str, zt_elementsOf(total_size_str), arena->total_size);
	zt_strCat(hover_info, zt_elementsOf(hover_info), total_size_str);
	zt_strBytesToString(total_size_str, zt_elementsOf(total_size_str), arena->peak_used);
	zt_strCat(hover_info, zt_elementsOf(hover_info), " (peak: ");
	zt_strCat(hover_info, zt_elementsOf(hover_info), total_size_str);
	zt_strCat(hover_info, zt_elementsOf(hover_info), ")");

	zt_guiItemSetLabel(mem->hover_info, hover_info);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugMemoryDisplayInputMouse, ztInternal ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiDebugMemoryDisplayInputMouse))
{
	ZT_PROFILE_GUI("_zt_guiDebugMemoryDisplayInputMouse");

	ztDebugMemory *mem = (ztDebugMemory*)item->functions.user_data;

	mem->mouse_pos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);
	mem->mouse_clicked = input_mouse->leftJustPressed();
	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiDebugMemoryDisplayCleanup, ztInternal ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiDebugMemoryDisplayCleanup))
{
	ztDebugMemory *mem = (ztDebugMemory*)item->functions.user_data;
	zt_freeArena(mem->source_dir_listing, item->gm->arena);
	zt_freeArena(item->functions.user_data, item->gm->arena);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugMemoryInspector(bool should_hide_if_not_created = false)
{
	{
		ztGuiItem *window = zt_guiItemFindByName(ZT_DEBUG_MEMORY_INSPECTOR_WINDOW_NAME);
		if (window != nullptr) {
			if (should_hide_if_not_created) {
				return;
			}
			zt_guiItemShow(window, true);
			zt_guiItemBringToFront(window);
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugMemory *mem = zt_mallocStructArena(ztDebugMemory, gm->arena);
	*mem = {};

	ztGuiItem *window = zt_guiMakeWindow(ZT_DEBUG_MEMORY_INSPECTOR_WINDOW_NAME, ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, ZT_DEBUG_MEMORY_INSPECTOR_WINDOW_NAME);
	zt_guiItemSetSize(window, zt_vec2(19, 10));

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(sizer);

	ztGuiItem *top_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz, false);
	ztGuiItem *combobox = zt_guiMakeComboBox(top_sizer, zt_elementsOf(mem->aliases));
	mem->combobox = combobox;
	combobox->size.x = 3;
	zt_guiComboBoxSetCallback(combobox, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugMemoryDisplayComboSelected), mem);

	ztGuiItem *slider = zt_guiMakeSlider(top_sizer, ztGuiItemOrient_Horz, &mem->byte_width_multiplier);
	slider->size.x = 9;

	ztGuiItem *chk_color = zt_guiMakeCheckbox(top_sizer, "Color By File", 0, &mem->color_by_file);

	ztGuiItem *hover_info = zt_guiMakeStaticText(sizer, "ABC", ztGuiStaticTextBehaviorFlags_MonoSpaced, 512);
	zt_guiItemSetAlign(hover_info, ztAlign_Right);
	mem->hover_info = hover_info;

	ztGuiItem *source_info = zt_guiMakeStaticText(sizer, "ABC", ztGuiStaticTextBehaviorFlags_MonoSpaced, 1024);
	zt_guiItemSetAlign(source_info, ztAlign_Right);
	source_info->color = zt_color(.75f, .75f, 1, 1);
	mem->source_info = source_info;

	ztGuiItem *refresh = zt_guiMakeButton(top_sizer, "Refresh");

	zt_guiSizerAddItem(top_sizer, combobox, 0, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddItem(top_sizer, refresh, 0, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddStretcher(top_sizer, 1, 0);
	zt_guiSizerAddItem(top_sizer, slider, 0, 3 / zt_pixelsPerUnit(), ztAlign_Center, 0); // todo: check aligning within sizer cell
	zt_guiSizerAddItem(top_sizer, chk_color, 0, 3 / zt_pixelsPerUnit(), 0);
	zt_guiSizerAddItem(sizer, top_sizer, 0, 0);

	ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer, ztGuiScrollContainerBehaviorFlags_StretchHorz);

	ztGuiItem *inspector = zt_guiMakePanel(sizer);
	zt_guiItemSetName(inspector, ZT_DEBUG_MEMORY_INSPECTOR_PANEL_NAME);

	zt_guiScrollContainerSetItem(scroll, inspector);
	zt_guiSizerAddItem(sizer, scroll, 1, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddItem(sizer, hover_info, 0, 3 / zt_pixelsPerUnit());
	zt_guiSizerAddItem(sizer, source_info, 0, 3 / zt_pixelsPerUnit());

	inspector->functions.user_data   = mem;
	inspector->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugMemoryDisplayUpdate);
	inspector->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugMemoryDisplayRender);
	inspector->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugMemoryDisplayInputMouse);
	inspector->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDebugMemoryDisplayCleanup);

	{
		int source_dir_listing_len = zt_kilobytes(64);
		mem->source_dir_listing = zt_mallocStructArrayArena(char, source_dir_listing_len, window->gm->arena);

		char current_path[ztFileMaxPath];
		zt_fileGetCurrentPath(current_path, zt_elementsOf(current_path));

		char source_path[ztFileMaxPath];
		zt_fileConcatFileToPath(source_path, zt_elementsOf(source_path), current_path, ztFilePathSeparatorStr "src");

		if (zt_directoryExists(source_path)) {
			zt_strCpy(mem->source_path, zt_elementsOf(mem->source_path), source_path);

			int temp_buffer_size = zt_kilobytes(64);
			char *temp_buffer = zt_mallocStructArrayArena(char, temp_buffer_size, window->gm->arena);

			zt_getDirectoryFiles(source_path, temp_buffer, temp_buffer_size, true);
			ztToken tokens[256];
			int tokens_count = zt_strTokenize(temp_buffer, "\n", tokens, zt_elementsOf(tokens));
			if (tokens_count < zt_elementsOf(tokens)) {
				zt_fiz(tokens_count) {
					char file[ztFileMaxPath];
					zt_strCpy(file, zt_elementsOf(file), temp_buffer + tokens[i].beg, tokens[i].len);

					const char *file_name_only = zt_strFindLast(file, ztFilePathSeparatorStr);
					if (file_name_only && (zt_striEndsWith(file_name_only, ".c") || zt_striEndsWith(file_name_only, ".cpp") || zt_striEndsWith(file_name_only, ".h") || zt_striEndsWith(file_name_only, ".cc") || zt_striEndsWith(file_name_only, ".hpp"))) {
						zt_strCat(mem->source_dir_listing, source_dir_listing_len, file_name_only + 1);
						zt_strCat(mem->source_dir_listing, source_dir_listing_len, "\n");
					}
				}
			}

			zt_freeArena(temp_buffer, window->gm->arena);
		}
		else {
			mem->source_path[0] = 0;
		}
	}

	zt_guiDebugMemoryInspectorAddArena(zt_memGetGlobalArena(), "Global Arena");
	_zt_guiDebugMemoryDisplayRefresh(mem);

	if (should_hide_if_not_created) {
		zt_guiItemHide(window);
	}

}

// ================================================================================================================================================================================================

ztInternal void _zt_guiDebugMemoryInspectorRefreshCombo(ztDebugMemory *mem)
{
	int selected = zt_guiComboBoxGetSelected(mem->combobox);

	char selected_text[zt_elementsOf(mem->aliases[0])];
	zt_guiComboBoxGetItemText(mem->combobox, selected, selected_text, zt_elementsOf(selected_text));

	zt_guiComboBoxClear(mem->combobox);

	int to_select = 0;
	zt_fiz(mem->arenas_count) {
		zt_guiComboBoxAppend(mem->combobox, mem->aliases[i], mem->arenas[i]);

		if (zt_strEquals(selected_text, mem->aliases[i])) {
			to_select = i;
		}
	}

	// todo: add function to set combo selection
}

// ================================================================================================================================================================================================

void zt_guiDebugMemoryInspectorAddArena(ztMemoryArena *arena, const char *alias)
{
	_zt_guiDebugMemoryInspector(true);

	ztGuiItem *window = zt_guiItemFindByName(ZT_DEBUG_MEMORY_INSPECTOR_WINDOW_NAME);
	if (window != nullptr) {
		ztGuiItem *inspector = zt_guiItemFindByName(ZT_DEBUG_MEMORY_INSPECTOR_PANEL_NAME, window);
		if (inspector) {
			ztDebugMemory *mem = (ztDebugMemory*)inspector->functions.user_data;

			zt_assertReturnOnFail(mem->arenas_count < zt_elementsOf(mem->arenas));
			int idx = mem->arenas_count++;
			mem->arenas[idx] = arena;
			zt_strCpy(mem->aliases[idx], zt_elementsOf(mem->aliases[idx]), (alias == nullptr ? "(unknown)" : alias));

			_zt_guiDebugMemoryInspectorRefreshCombo(mem);
		}
	}
}

// ================================================================================================================================================================================================

void zt_guiDebugMemoryInspectorRemoveArena(ztMemoryArena *arena)
{
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum ztDebugSpriteDragType_Enum
{
	ztDebugSpriteDragType_None,
	ztDebugSpriteDragType_Move,
	ztDebugSpriteDragType_MoveRight,
	ztDebugSpriteDragType_Sprite,
	ztDebugSpriteDragType_SpriteResize,

	ztDebugSpriteDragType_MAX,
};

// private functions ==============================================================================================================================================================================

struct ztDebugSpriteEditor
{
	ztGuiItem                  *combo_textures;
	ztGuiItem                  *display;
	ztVec2                      display_drag_pos;
	ztVec2                      display_drag_mpos;
	ztDebugSpriteDragType_Enum  display_drag_type;
	ztVec2                      display_scroll_amt;
	ztGuiItem                  *display_scroll;
	int                         display_zoom_level;
	r32                         display_zoom_mult;

	ztGuiItem                  *sprite_info_panel;

	ztGuiItem                  *text_name;
	ztGuiItem                  *combo_type; // sprite, nine slice

	ztGuiItem                  *edit_xy;
	ztGuiItem                  *edit_wh;
	ztGuiItem                  *edit_anchor;
	ztGuiItem                  *edit_nw;
	ztGuiItem                  *edit_se;
	ztGuiItem                  *edit_offset_nw;
	ztGuiItem                  *edit_offset_se;

	ztGuiItem                  *gui_edit_sprite[32];
	ztGuiItem                  *gui_edit_nineslice[32];

	ztVec2i                     val_xy;
	ztVec2i                     val_wh;
	ztVec2i                     val_anchor;
	ztVec2i                     val_nw;
	ztVec2i                     val_se;
	ztVec2i                     val_offset_nw;
	ztVec2i                     val_offset_se;

	bool                        ignore_value_change;

	ztTextureID                 active_tex;
	ztVec2i                     active_tex_size;

	ztTextureID                 grid_texture;
	ztVec2i                     grid_texture_size;

	ztVec2i                     sprite_grid_values;

	char                        sprite_name[1024][64];
	int                         sprite_type[1024];
	ztVec2                      sprite_pos[1024];
	ztVec2                      sprite_size[1024];
	ztVec2                      sprite_anchor[1024];
	ztVec2                      sprite_nw[1024];
	ztVec2                      sprite_se[1024];
	ztVec2                      sprite_offset_nw[1024];
	ztVec2                      sprite_offset_se[1024];
	int                         sprite_active;
	i32                         sprite_active_drag;
};

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteEdDisplayCalcSize(ztGuiItem *display)
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)display->functions.user_data;

	ztVec2 size = zt_vec2(editor->active_tex_size.x / zt_pixelsPerUnit(), editor->active_tex_size.y / zt_pixelsPerUnit());

	switch (editor->display_zoom_level) {
		case -3: editor->display_zoom_mult = .25f; break;
		case -2: editor->display_zoom_mult = .50f; break;
		case -1: editor->display_zoom_mult = .75f; break;
		case  0: editor->display_zoom_mult = 1.00f; break;
		case  1: editor->display_zoom_mult = 2.00f; break;
		case  2: editor->display_zoom_mult = 4.00f; break;
		case  3: editor->display_zoom_mult = 8.00f; break;
		case  4: editor->display_zoom_mult = 16.00f; break;
	}

	zt_guiItemSetSize(editor->display, size * editor->display_zoom_mult + zt_vec2(editor->sprite_info_panel->size.x, 0));
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteEdDisplayAdjustGui(ztDebugSpriteEditor *editor)
{
	int selected = zt_guiComboBoxGetSelected(editor->combo_type);
	if (selected == 0) { // sprite
		zt_fize(editor->gui_edit_nineslice) {
			if (editor->gui_edit_nineslice[i]) {
				zt_guiItemHide(editor->gui_edit_nineslice[i]);
			}
		}
		zt_fize(editor->gui_edit_sprite) {
			if (editor->gui_edit_sprite[i]) {
				zt_guiItemShow(editor->gui_edit_sprite[i]);
			}
		}
	}
	else if (selected == 1) { // nine slice
		zt_fize(editor->gui_edit_nineslice) {
			if (editor->gui_edit_nineslice[i]) {
				zt_guiItemShow(editor->gui_edit_nineslice[i]);
			}
		}
		zt_fize(editor->gui_edit_sprite) {
			if (editor->gui_edit_sprite[i]) {
				zt_guiItemHide(editor->gui_edit_sprite[i]);
			}
		}
	}
	else zt_assert(false);

	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor->combo_type));

}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteEdDisplayReadVals(ztDebugSpriteEditor *editor)
{
	r32 ppu = zt_pixelsPerUnit();
	int i = editor->sprite_active;
	editor->val_xy = zt_vec2i(zt_convertToi32Floor(editor->sprite_pos[i].x * ppu), zt_convertToi32Floor(editor->sprite_pos[i].y * ppu));
	editor->val_wh = zt_vec2i(zt_convertToi32Floor(editor->sprite_size[i].x * ppu), zt_convertToi32Floor(editor->sprite_size[i].y * ppu));
	editor->val_anchor = zt_vec2i(zt_convertToi32Floor(editor->sprite_anchor[i].x * ppu), zt_convertToi32Floor(editor->sprite_anchor[i].y * ppu));
	editor->val_nw = zt_vec2i(zt_convertToi32Floor(editor->sprite_nw[i].x * ppu), zt_convertToi32Floor(editor->sprite_nw[i].y * ppu));
	editor->val_se = zt_vec2i(zt_convertToi32Floor(editor->sprite_se[i].x * ppu), zt_convertToi32Floor(editor->sprite_se[i].y * ppu));
	editor->val_offset_nw = zt_vec2i(zt_convertToi32Floor(editor->sprite_offset_nw[i].x * ppu), zt_convertToi32Floor(editor->sprite_offset_nw[i].y * ppu));
	editor->val_offset_se = zt_vec2i(zt_convertToi32Floor(editor->sprite_offset_se[i].x * ppu), zt_convertToi32Floor(editor->sprite_offset_se[i].y * ppu));

	zt_guiTextEditSetValue(editor->text_name, editor->sprite_name[i]);

	zt_guiComboBoxSetSelected(editor->combo_type, editor->sprite_type[i]);

	zt_guiEditorReassign(editor->edit_xy, &editor->val_xy);
	zt_guiEditorReassign(editor->edit_wh, &editor->val_wh);
	zt_guiEditorReassign(editor->edit_anchor, &editor->val_anchor);
	zt_guiEditorReassign(editor->edit_nw, &editor->val_nw);
	zt_guiEditorReassign(editor->edit_se, &editor->val_se);
	zt_guiEditorReassign(editor->edit_offset_nw, &editor->val_offset_nw);
	zt_guiEditorReassign(editor->edit_offset_se, &editor->val_offset_se);

	_zt_debugSpriteEdDisplayAdjustGui(editor);
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteEdDisplayApplyVals(ztDebugSpriteEditor *editor)
{
	r32 ppu = zt_pixelsPerUnit();
	int i = editor->sprite_active;
	editor->sprite_pos[i] = zt_vec2(editor->val_xy.x / ppu, editor->val_xy.y / ppu);
	editor->sprite_size[i] = zt_vec2(editor->val_wh.x / ppu, editor->val_wh.y / ppu);
	editor->sprite_anchor[i] = zt_vec2(editor->val_anchor.x / ppu, editor->val_anchor.y / ppu);
	editor->sprite_nw[i] = zt_vec2(editor->val_nw.x / ppu, editor->val_nw.y / ppu);
	editor->sprite_se[i] = zt_vec2(editor->val_se.x / ppu, editor->val_se.y / ppu);
	editor->sprite_offset_nw[i] = zt_vec2(editor->val_offset_nw.x / ppu, editor->val_offset_nw.y / ppu);
	editor->sprite_offset_se[i] = zt_vec2(editor->val_offset_se.x / ppu, editor->val_offset_se.y / ppu);

	zt_guiTextEditGetValue(editor->text_name, editor->sprite_name[i], zt_elementsOf(editor->sprite_name[i]));

	editor->sprite_type[i] = zt_guiComboBoxGetSelected(editor->combo_type);

	_zt_debugSpriteEdDisplayAdjustGui(editor);

	if (editor->sprite_type[i] == 1) { // nine slice
		if (editor->sprite_nw[i] == ztVec2::zero) {
			r32 ppu = zt_pixelsPerUnit();
			editor->sprite_size[i].x = zt_max(16 / ppu, editor->sprite_size[i].x);
			editor->sprite_size[i].y = zt_max(16 / ppu, editor->sprite_size[i].y);

			editor->sprite_nw[i] = editor->sprite_pos[i] + zt_vec2(4 / ppu, 4 / ppu);
			editor->sprite_se[i] = (editor->sprite_pos[i] + editor->sprite_size[i]) - zt_vec2(4 / ppu, 4 / ppu);

			_zt_debugSpriteEdDisplayReadVals(editor);
		}
	}
}

// ================================================================================================================================================================================================

ztInternal bool _zt_debugSpriteEdDisplayGetFileName(ztDebugSpriteEditor *editor, char *name, int name_size)
{
	if (zt_game->textures[editor->active_tex].load_type == ztTextureLoadType_Asset) {
		zt_fileConcatFileToPath(name, name_size, zt_game->game_details.data_path, zt_game->textures[editor->active_tex].asset_mgr->asset_name[zt_game->textures[editor->active_tex].asset_id]);

		int pos = zt_strFindLastPos(name, ".");
		if (pos != ztStrPosNotFound) {
			name[pos] = 0;
		}

		zt_strCat(name, ztFileMaxPath, ".spr");
		return true;
	}
	else if(zt_game->textures[editor->active_tex].load_type == ztTextureLoadType_Data) {
		if (zt_game->textures[editor->active_tex].file_name[0] != 0) {
			zt_fileConcatFileToPath(name, name_size, zt_game->game_details.data_path, zt_game->textures[editor->active_tex].file_name);

			int pos = zt_strFindLastPos(name, ".");
			if (pos != ztStrPosNotFound) {
				name[pos] = 0;
			}

			zt_strCat(name, ztFileMaxPath, ".spr");
			return true;
		}
	}

	return false;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayEditorChanged, ZT_FUNC_GUI_EDITOR_VALUE_CHANGED(_zt_debugSpriteEdDisplayEditorChanged))
{
	ztDebugSpriteEditor *editor_ = (ztDebugSpriteEditor*)user_data;

	if (editor_->ignore_value_change) {
		return;
	}

	_zt_debugSpriteEdDisplayApplyVals(editor_);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_debugSpriteEdDisplayRender))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	ztVec2 pos = offset + item->pos;
	ztVec3 scale = zt_vec3(editor->display_zoom_mult, editor->display_zoom_mult, 1);

	int w = zt_convertToi32Ceil(editor->active_tex_size.x / (r32)editor->grid_texture_size.x) + 1;
	int h = zt_convertToi32Ceil(editor->active_tex_size.y / (r32)editor->grid_texture_size.y) + 1;

	int sw = zt_min(editor->grid_texture_size.x, editor->active_tex_size.x);
	int sh = zt_min(editor->grid_texture_size.y, editor->active_tex_size.y);
	ztVec2 checker_size = zt_vec2(sw / zt_pixelsPerUnit(), sh / zt_pixelsPerUnit());

	ztVec2 start = zt_vec2(pos.x + (item->size.x / -2 + (checker_size.x * scale.x) / 2), pos.y + (item->size.y / 2 - (checker_size.y * scale.y) / 2)) - zt_vec2(editor->sprite_info_panel->size.x / 2, 0);

	ztSprite grid_sprite = zt_spriteMake(editor->grid_texture, zt_vec2i(0, 0), zt_vec2i(sw, sh));
	zt_fyz(h) {
		zt_fxz(w) {
			zt_drawListAddSprite(draw_list, &grid_sprite, zt_vec3(start.x + (x * checker_size.x * scale.x), start.y - (y * checker_size.y * scale.y), 0), ztVec3::zero, scale);
		}
	}


	ztSprite sprite = zt_spriteMake(editor->active_tex, zt_vec2i(0, 0), editor->active_tex_size);
	zt_drawListAddSprite(draw_list, &sprite, zt_vec3(offset + item->pos - zt_vec2(editor->sprite_info_panel->size.x / 2, 0), 0), ztVec3::zero, scale);

	zt_drawListPushTexture(draw_list, ztTextureDefault);
	ztVec2 image_pos = offset + item->pos - zt_vec2(editor->sprite_info_panel->size.x / 2.f, 0);
	ztVec2 image_size = zt_vec2(editor->active_tex_size.x / zt_pixelsPerUnit(), editor->active_tex_size.y / zt_pixelsPerUnit()) * editor->display_zoom_mult;
	zt_drawListAddEmptyRect(draw_list, zt_vec3(image_pos, 0), image_size);

	ztVec2 zero = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
	ztVec2 local_tl = zt_vec2(zero.x - item->size.x / 2, zero.y + item->size.y / 2);

	r32 ppu = zt_pixelsPerUnit();

	zt_drawListPushColor(draw_list, ztColor_White);
	zt_drawListPushBlendMode(draw_list, ztRendererBlendMode_OneMinusDestColor, ztRendererBlendMode_Zero);
	zt_fize(editor->sprite_pos) {
		if (editor->sprite_size[i] != ztVec2::zero) {
			ztVec2 size = editor->sprite_size[i] * editor->display_zoom_mult;
			ztVec2 sptl = editor->sprite_pos[i] * editor->display_zoom_mult;
			sptl.x += local_tl.x;
			sptl.y = local_tl.y - sptl.y;
			sptl.x += size.x / 2;
			sptl.y -= size.y / 2;

			r32 anchor_offset_x = zt_convertToi32Floor(editor->sprite_size[i].x * ppu) % 2 != 0 ? 0 : (.5f / ppu);
			r32 anchor_offset_y = zt_convertToi32Floor(editor->sprite_size[i].y * ppu) % 2 != 0 ? 0 : (.5f / ppu);

			ztVec3 anchor = zt_vec3(sptl + (editor->display_zoom_mult * zt_vec2(editor->sprite_anchor[i].x + anchor_offset_x, editor->sprite_anchor[i].y - anchor_offset_y)), 0);

			if (i == editor->sprite_active) {
				zt_drawListPushColor(draw_list, ztColor_Cyan);
			}

			zt_drawListAddEmptyRect(draw_list, sptl, size);

			if (editor->sprite_type[i] == 0) {
				zt_drawListAddEmptyCircle(draw_list, anchor, 5 / ppu, 5);

				if (i == editor->sprite_active) {
					zt_drawListAddLine(draw_list, zt_vec2(anchor.x, sptl.y - size.y / 2.f), zt_vec2(anchor.x, sptl.y + size.y / 2.f));
					zt_drawListAddLine(draw_list, zt_vec2(sptl.x - size.x / 2.f, anchor.y), zt_vec2(sptl.x + size.x / 2.f, anchor.y));
				}
			}
			else {
				ztVec2 nw = editor->sprite_nw[i] * editor->display_zoom_mult;
				nw.x += local_tl.x;
				nw.y = local_tl.y - nw.y;
				ztVec2 se = editor->sprite_se[i] * editor->display_zoom_mult;
				se.x += local_tl.x;
				se.y = local_tl.y - se.y;

				zt_drawListAddLine(draw_list, zt_vec2(nw.x, sptl.y + size.y / 2.f), zt_vec2(nw.x, sptl.y - size.y / 2.f));
				zt_drawListAddLine(draw_list, zt_vec2(se.x, sptl.y + size.y / 2.f), zt_vec2(se.x, sptl.y - size.y / 2.f));
				zt_drawListAddLine(draw_list, zt_vec2(sptl.x - size.x / 2.f, nw.y), zt_vec2(sptl.x + size.x / 2.f, nw.y));
				zt_drawListAddLine(draw_list, zt_vec2(sptl.x - size.x / 2.f, se.y), zt_vec2(sptl.x + size.x / 2.f, se.y));

				if (editor->sprite_offset_nw[i] != ztVec2::zero || editor->sprite_offset_se[i] != ztVec2::zero) {
					ztVec2 offset_size = size - (editor->sprite_offset_nw[i] + editor->sprite_offset_se[i]) * editor->display_zoom_mult;
					ztVec2 offset_diff = (editor->sprite_offset_se[i] - editor->sprite_offset_nw[i]) * editor->display_zoom_mult;

					ztVec2 offset_center = zt_vec2(sptl.x - offset_diff.x / 2, sptl.y + offset_diff.y / 2);

					zt_drawListPushColor(draw_list, i == editor->sprite_active ? ztColor_Red : ztColor_White);
					zt_drawListAddEmptyRect(draw_list, offset_center, offset_size);
					zt_drawListPopColor(draw_list);
				}
			}

			if (i == editor->sprite_active) {
				zt_drawListPopColor(draw_list);
			}
		}
	}
	zt_drawListPopBlendMode(draw_list);
	zt_drawListPopColor(draw_list);

	if (image_size.x < item->parent->size.x) {
		ztVec2 start = zt_vec2(pos.x + item->size.x / -2.f, pos.y);
		ztVec2 right_size = zt_vec2(item->parent->size.x - image_size.x, image_size.y);
		ztVec2 right_pos = zt_vec2(start.x + image_size.x + right_size.x / 2, start.y);
		zt_drawListAddSolidRect2D(draw_list, right_pos, right_size, ztColor_Black);
	}
	else {
		ztVec2 start = zt_vec2(pos.x + item->size.x / -2.f, pos.y);
		ztVec2 right_size = zt_vec2(editor->sprite_info_panel->size.x, image_size.y);
		ztVec2 right_pos = zt_vec2(start.x + image_size.x + right_size.x / 2, start.y);
		zt_drawListAddSolidRect2D(draw_list, right_pos, right_size, ztColor_Black);
	}
	if (image_size.y < item->parent->size.y) {
		ztVec2 start = zt_vec2(offset.x, pos.y + item->size.y / -2.f);
		ztVec2 bottom_size = zt_vec2(item->parent->size.x, item->parent->size.y - image_size.y);
		ztVec2 bottom_pos = zt_vec2(start.x, start.y + bottom_size.y / -2);
		zt_drawListAddSolidRect2D(draw_list, bottom_pos, bottom_size, ztColor_Black);
	}

	if (editor->display_drag_type == ztDebugSpriteDragType_Sprite) {
		zt_drawListPushColor(draw_list, ztColor_Cyan);

		ztVec2 size = editor->display_drag_mpos - editor->display_drag_pos;
		ztVec2 center = editor->display_drag_pos + (size * .5f);

		zt_drawListAddEmptyRect(draw_list, center, size);
		zt_drawListPopColor(draw_list);
	}

	zt_drawListPopTexture(draw_list);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_debugSpriteEdDisplayUpdate))
{
	//ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_debugSpriteEdDisplayInputMouse))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	ztVec2 mpos = zt_cameraOrthoScreenToWorld(item->gm->gui_camera, input_mouse->screen_x, input_mouse->screen_y);

	switch (editor->display_drag_type)
	{
		case ztDebugSpriteDragType_None: {
			bool dragging = false;
			ztInputMouseCursor_Enum cursor = ztInputMouseCursor_Arrow;

			if (key_shift) {
				cursor = ztInputMouseCursor_Hand;

				if (input_mouse->leftJustPressed()) {
					dragging = true;
					editor->display_drag_type = ztDebugSpriteDragType_Move;
				}
			}
			else if (input_mouse->rightJustPressed()) {
				dragging = true;
				editor->display_drag_type = ztDebugSpriteDragType_MoveRight;
			}

			ztVec2 conv_mpos = zt_guiItemPositionScreenToLocal(item, mpos) * (1.f / editor->display_zoom_mult);
			{
				ztVec2 zero = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
				ztVec2 local_tl = zt_vec2(zero.x - item->size.x / 2, zero.y + item->size.y / 2);
				conv_mpos = zt_vec2(mpos.x - local_tl.x, local_tl.y - mpos.y) * (1.f / editor->display_zoom_mult);
			}

			i32 hover_direction = 0;
			if (editor->sprite_active >= 0) {
				int i = editor->sprite_active;
				ztVec2 sprite_pos = zt_vec2(editor->sprite_pos[i].x + editor->sprite_size[i].x / 2, editor->sprite_pos[i].y + editor->sprite_size[i].y / 2);
				ztVec2 sprite_size = editor->sprite_size[editor->sprite_active];
				if (zt_collisionPointInRect(conv_mpos, sprite_pos, sprite_size)) {
					r32 side_check = 3 / zt_pixelsPerUnit();

					// top side
					if (zt_collisionPointInRect(conv_mpos, sprite_pos + zt_vec2(0, sprite_size.y / -2), zt_vec2(sprite_size.x, side_check))) {
						hover_direction |= zt_bit(ztDirection_North);
					}
					else if (zt_collisionPointInRect(conv_mpos, sprite_pos + zt_vec2(0, sprite_size.y / 2), zt_vec2(sprite_size.x, side_check))) {
						hover_direction |= zt_bit(ztDirection_South);
					}
					if (zt_collisionPointInRect(conv_mpos, sprite_pos + zt_vec2(sprite_size.x / 2, 0), zt_vec2(side_check, sprite_size.y))) {
						hover_direction |= zt_bit(ztDirection_East);
					}
					else if (zt_collisionPointInRect(conv_mpos, sprite_pos + zt_vec2(sprite_size.x / -2, 0), zt_vec2(side_check, sprite_size.y))) {
						hover_direction |= zt_bit(ztDirection_West);
					}

					if (hover_direction == 0) {
						zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
					}
					else {
						if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_North))) {
							if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_East))) {
								cursor = ztInputMouseCursor_ResizeSWNE;
							}
							else if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_West))) {
								cursor = ztInputMouseCursor_ResizeNWSE;
							}
							else {
								cursor = ztInputMouseCursor_ResizeNS;
							}
						}
						else if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_South))) {
							if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_East))) {
								cursor = ztInputMouseCursor_ResizeNWSE;
							}
							else if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_West))) {
								cursor = ztInputMouseCursor_ResizeSWNE;
							}
							else {
								cursor = ztInputMouseCursor_ResizeNS;
							}
						}
						else if (zt_bitIsSet(hover_direction, zt_bit(ztDirection_East)) || zt_bitIsSet(hover_direction, zt_bit(ztDirection_West))) {
							cursor = ztInputMouseCursor_ResizeEW;
						}
					}
				}
			}

			if (dragging) {
				editor->display_drag_pos = mpos;
				editor->display_scroll_amt.x = zt_guiScrollContainerGetScroll(editor->display_scroll, ztGuiItemOrient_Horz);
				editor->display_scroll_amt.y = zt_guiScrollContainerGetScroll(editor->display_scroll, ztGuiItemOrient_Vert);
			}
			else if (input_mouse->leftJustPressed()) {

				bool allow_new_sprite = true;

				if (editor->sprite_active != -1) {
					int i = editor->sprite_active;
					ztVec2 sprite_pos = zt_vec2(editor->sprite_pos[i].x + editor->sprite_size[i].x / 2, editor->sprite_pos[i].y + editor->sprite_size[i].y / 2);
					if (zt_collisionPointInRect(conv_mpos, sprite_pos, editor->sprite_size[editor->sprite_active])) {
						editor->sprite_active_drag = hover_direction;
						editor->display_drag_type = ztDebugSpriteDragType_SpriteResize;
						editor->ignore_value_change = true;
					}
					else {
						_zt_debugSpriteEdDisplayApplyVals(editor);
						editor->sprite_active = -1;
					}

					allow_new_sprite = false;
				}

				if (editor->sprite_active == -1) {
					zt_fize(editor->sprite_pos) {
						if (editor->sprite_size[i] != ztVec2::zero) {
							ztVec2 sprite_pos = zt_vec2(editor->sprite_pos[i].x + editor->sprite_size[i].x / 2, editor->sprite_pos[i].y + editor->sprite_size[i].y / 2);
							if (zt_collisionPointInRect(conv_mpos, sprite_pos, editor->sprite_size[i])) {
								editor->sprite_active = i;
								editor->sprite_active_drag = 0;

								_zt_debugSpriteEdDisplayReadVals(editor);
								break;
							}
						}
					}
				}

				editor->display_drag_pos = mpos;

				if (allow_new_sprite && editor->sprite_active == -1) {
					editor->display_drag_mpos = mpos;
					editor->display_drag_type = ztDebugSpriteDragType_Sprite;
				}
			}

			zt_inputMouseSetCursor(cursor);
		} break;

		case ztDebugSpriteDragType_Move: {
			if (input_mouse->leftPressed()) {
				ztVec2 mdiff = mpos - editor->display_drag_pos;
				ztVec2 pct = zt_vec2(mdiff.x / (item->size.x - item->parent->size.x), mdiff.y / (item->size.y - item->parent->size.y));

				r32 scroll_h = zt_clamp(editor->display_scroll_amt.x - pct.x, 0, 1);
				r32 scroll_v = zt_clamp(editor->display_scroll_amt.y + pct.y, 0, 1);

				zt_guiScrollContainerSetScroll(editor->display_scroll, ztGuiItemOrient_Horz, scroll_h);
				zt_guiScrollContainerSetScroll(editor->display_scroll, ztGuiItemOrient_Vert, scroll_v);
			}
			else {
				editor->display_drag_pos = ztVec2::min;
				editor->display_drag_type = ztDebugSpriteDragType_None;
			}
		} break;

		case ztDebugSpriteDragType_MoveRight: {
			if (input_mouse->rightPressed()) {
				ztVec2 mdiff = mpos - editor->display_drag_pos;
				ztVec2 pct = zt_vec2(mdiff.x / (item->size.x - item->parent->size.x), mdiff.y / (item->size.y - item->parent->size.y));

				r32 scroll_h = zt_clamp(editor->display_scroll_amt.x - pct.x, 0, 1);
				r32 scroll_v = zt_clamp(editor->display_scroll_amt.y + pct.y, 0, 1);

				zt_guiScrollContainerSetScroll(editor->display_scroll, ztGuiItemOrient_Horz, scroll_h);
				zt_guiScrollContainerSetScroll(editor->display_scroll, ztGuiItemOrient_Vert, scroll_v);
			}
			else {
				editor->display_drag_pos = ztVec2::min;
				editor->display_drag_type = ztDebugSpriteDragType_None;
			}
		} break;

		case ztDebugSpriteDragType_Sprite: {
			if (input_mouse->leftPressed()) {
				editor->display_drag_mpos = mpos;
			}
			else {
				editor->display_drag_type = ztDebugSpriteDragType_None;

				zt_fize(editor->sprite_pos) {
					if (editor->sprite_size[i] == ztVec2::zero) {

						ztVec2 pos1 = editor->display_drag_pos;
						ztVec2 pos2 = editor->display_drag_mpos;

						if (pos1.x > pos2.x) zt_swap(pos1.x, pos2.x);
						if (pos1.y < pos2.y) zt_swap(pos1.y, pos2.y);

						// 0,0 is top left of image
						ztVec2 local = pos1;

						ztVec2 zero = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
						ztVec2 local_tl = zt_vec2(zero.x - item->size.x / 2, zero.y + item->size.y / 2);

						ztVec2 top_left = zt_vec2(local.x - local_tl.x, local_tl.y - local.y);// -item->pos;
						ztVec2 size = zt_vec2(pos2.x - pos1.x, pos1.y - pos2.y);

						ztVec2i pix_top_left = zt_vec2i(zt_convertToi32Floor(top_left.x * zt_pixelsPerUnit()), zt_convertToi32Floor(top_left.y * zt_pixelsPerUnit()));
						ztVec2i pix_size = zt_vec2i(zt_convertToi32Floor(size.x * zt_pixelsPerUnit()), zt_convertToi32Floor(size.y * zt_pixelsPerUnit()));

						if (pix_size.x > 0 && pix_size.y > 0) {
							editor->sprite_pos[i] = zt_vec2(pix_top_left.x / zt_pixelsPerUnit(), pix_top_left.y / zt_pixelsPerUnit()) * (1.f / editor->display_zoom_mult);
							editor->sprite_size[i] = zt_vec2(pix_size.x / zt_pixelsPerUnit(), pix_size.y / zt_pixelsPerUnit()) * (1.f / editor->display_zoom_mult);

							editor->sprite_active = i;

							int total_sprites = 0;
							zt_fjze(editor->sprite_size) {
								if (editor->sprite_size[j] != ztVec2::zero) {
									total_sprites += 1;
								}
							}

							while (true) {
								zt_strMakePrintf(sprite_name, 64, "sprite_%d", total_sprites);
								zt_strCpy(editor->sprite_name[i], zt_elementsOf(editor->sprite_name[i]), sprite_name);

								bool found_copy = false;
								zt_fjze(editor->sprite_pos) {
									if (j != i && editor->sprite_pos[j] != ztVec2::zero && zt_strEquals(editor->sprite_name[j], editor->sprite_name[i])) {
										found_copy = true;
										break;
									}
								}
								if (!found_copy) {
									break;
								}
								total_sprites += 1;
							}

							zt_guiComboBoxSetSelected(editor->combo_type, 0);
						}
						break;
					}
				}

				_zt_debugSpriteEdDisplayReadVals(editor);
			}
		} break;

		case ztDebugSpriteDragType_SpriteResize: {
			if (input_mouse->leftPressed()) {
				editor->display_drag_mpos = mpos;

				ztVec2 conv_mpos = zt_guiItemPositionScreenToLocal(item, mpos) * (1.f / editor->display_zoom_mult);
				ztVec2 conv_dpos = zt_guiItemPositionScreenToLocal(item, editor->display_drag_pos) * (1.f / editor->display_zoom_mult);
				{
					ztVec2 zero = zt_guiItemPositionLocalToScreen(item, ztVec2::zero);
					ztVec2 local_tl = zt_vec2(zero.x - item->size.x / 2, zero.y + item->size.y / 2);
					conv_mpos = zt_vec2(mpos.x - local_tl.x, local_tl.y - mpos.y) * (1.f / editor->display_zoom_mult);
					conv_dpos = zt_vec2(editor->display_drag_pos.x - local_tl.x, local_tl.y - editor->display_drag_pos.y) * (1.f / editor->display_zoom_mult);
				}

				r32 min_size = 1 / zt_pixelsPerUnit();

				if (zt_bitIsSet(editor->sprite_active_drag, zt_bit(ztDirection_North))) {
					r32 diff_y = conv_mpos.y - conv_dpos.y;
					if (editor->sprite_size[editor->sprite_active].y > min_size || diff_y < 0) {
						editor->sprite_pos[editor->sprite_active].y += diff_y;
						editor->sprite_size[editor->sprite_active].y -= diff_y;
					}
				}
				if (zt_bitIsSet(editor->sprite_active_drag, zt_bit(ztDirection_South))) {
					r32 diff_y = conv_dpos.y - conv_mpos.y;
					if (editor->sprite_size[editor->sprite_active].y > min_size || diff_y < 0) {
						editor->sprite_size[editor->sprite_active].y -= diff_y;
					}
				}
				if (zt_bitIsSet(editor->sprite_active_drag, zt_bit(ztDirection_East))) {
					r32 diff_x = conv_mpos.x - conv_dpos.x;
					if (editor->sprite_size[editor->sprite_active].x > min_size || diff_x > 0) {
						editor->sprite_size[editor->sprite_active].x += diff_x;
					}
				}
				if (zt_bitIsSet(editor->sprite_active_drag, zt_bit(ztDirection_West))) {
					r32 diff_x = conv_dpos.x - conv_mpos.x;
					if (editor->sprite_size[editor->sprite_active].x > min_size || diff_x > 0) {
						editor->sprite_pos[editor->sprite_active].x -= diff_x;
						editor->sprite_size[editor->sprite_active].x += diff_x;
					}
				}

				editor->display_drag_pos = mpos;

				_zt_debugSpriteEdDisplayReadVals(editor);
			}
			else {
				editor->display_drag_type = ztDebugSpriteDragType_None;
				editor->ignore_value_change = false;
				_zt_debugSpriteEdDisplayApplyVals(editor);
				zt_inputMouseSetCursor(ztInputMouseCursor_Arrow);
			}
		} break;
	}

	if (input_mouse->wheel_delta) {
		editor->display_zoom_level = zt_clamp(editor->display_zoom_level + input_mouse->wheel_delta, -3, 4);
		_zt_debugSpriteEdDisplayCalcSize(editor->display);
	}

	zt_guiItemShow(editor->sprite_info_panel, editor->sprite_active >= 0);

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEditorComboTexture, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_debugSpriteEditorComboTexture))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	ztTextureID tex = (ztTextureID)(pointer)zt_guiComboBoxGetItemUserData(combobox, zt_guiComboBoxGetSelected(combobox));
	editor->active_tex = tex;
	editor->active_tex_size = zt_textureGetSize(tex);
	editor->display_zoom_level = 0;
	editor->sprite_active = -1;

	zt_fize(editor->sprite_size) {
		editor->sprite_name[i][0] = 0;
		editor->sprite_size[i] = ztVec2::zero;
		editor->sprite_pos[i] = ztVec2::zero;
		editor->sprite_anchor[i] = ztVec2::zero;
		editor->sprite_nw[i] = ztVec2::zero;;
		editor->sprite_se[i] = ztVec2::zero;
		editor->sprite_offset_nw[i] = ztVec2::zero;
		editor->sprite_offset_se[i] = ztVec2::zero;
	}

	char sm_name[ztFileMaxPath];
	if (_zt_debugSpriteEdDisplayGetFileName(editor, sm_name, zt_elementsOf(sm_name))) {
		ztSpriteManager sm;
		zt_spriteManagerMake(&sm, zt_elementsOf(editor->sprite_pos));

		ztSerial serial;
		if (zt_serialMakeReader(&serial, sm_name, ZT_SPRITE_FILE_GUID)) {
			if (zt_spriteManagerLoad(&sm, &serial, editor->active_tex)) {
				zt_logInfo("sprite manager loaded: %s", sm_name);
			}

			zt_serialClose(&serial);
		}

		ztVec2 tex_size = zt_vec2((r32)editor->active_tex_size.x, (r32)editor->active_tex_size.y);

		r32 ppu = zt_pixelsPerUnit();

		zt_fiz(sm.sprites_count) {
			if (sm.sprites[i].hash != 0) {
				zt_strCpy(editor->sprite_name[i], zt_elementsOf(editor->sprite_name[i]), sm.sprites[i].name);
				if (sm.sprites[i].type == ztSpriteType_Sprite) {
					editor->sprite_type[i] = 0;
					editor->sprite_pos[i] = (sm.sprites[i].s.tex_uv.xy * tex_size) * (1 / ppu);
					editor->sprite_size[i] = ((sm.sprites[i].s.tex_uv.zw - sm.sprites[i].s.tex_uv.xy) * tex_size) * (1 / ppu);
					editor->sprite_anchor[i] = sm.sprites[i].s.anchor;

				}
				else if (sm.sprites[i].type == ztSpriteType_SpriteNineSlice) {
					editor->sprite_type[i] = 1;
					editor->sprite_pos[i] = (sm.sprites[i].sns.sp_nw.xy * tex_size) * (1 / ppu);
					editor->sprite_size[i] = ((sm.sprites[i].sns.sp_se.zw - sm.sprites[i].sns.sp_nw.xy) * tex_size) * (1 / ppu);
					editor->sprite_nw[i] = (sm.sprites[i].sns.sp_nw.zw * tex_size) * (1 / ppu);
					editor->sprite_se[i] = (sm.sprites[i].sns.sp_se.xy * tex_size) * (1 / ppu);
					editor->sprite_offset_nw[i] = (sm.sprites[i].sns.offset.xy);
					editor->sprite_offset_se[i] = (sm.sprites[i].sns.offset.zw);
				}
			}
		}

	}

	zt_guiScrollContainerSetScroll(editor->display_scroll, ztGuiItemOrient_Horz, 0);
	zt_guiScrollContainerSetScroll(editor->display_scroll, ztGuiItemOrient_Vert, 0);

	_zt_debugSpriteEdDisplayCalcSize(editor->display);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEditorComboType, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_debugSpriteEditorComboType))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;
	_zt_debugSpriteEdDisplayApplyVals(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_debugSpriteEdDisplayCleanup))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	zt_textureFree(editor->grid_texture);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayTextChange, ZT_FUNC_GUI_TEXTEDIT_KEY(_zt_debugSpriteEdDisplayTextChange))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;
	_zt_debugSpriteEdDisplayApplyVals(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayButtonBestFit, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteEdDisplayButtonBestFit))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	i32 bytes_size = editor->active_tex_size.x * editor->active_tex_size.y * 4;
	byte *pixels = zt_mallocStructArray(byte, bytes_size);

	zt_textureGetPixels(editor->active_tex, pixels);

	//zt_writeEntireFile("pixels.raw", pixels, bytes_size);

	r32 ppu = zt_pixelsPerUnit();

	ztVec2 nwv = editor->sprite_pos[editor->sprite_active];
	ztVec2i nw = zt_vec2i(zt_convertToi32Floor(nwv.x * ppu), zt_convertToi32Floor(nwv.y * ppu));
	ztVec2 sev = editor->sprite_pos[editor->sprite_active] + editor->sprite_size[editor->sprite_active];
	ztVec2i se = zt_vec2i(zt_convertToi32Floor(sev.x * ppu), zt_convertToi32Floor(sev.y * ppu));

#define _idx(X,Y)  int idx = ((((editor->active_tex_size.y - 1) - Y) * editor->active_tex_size.x) + X) * 4;

	int sides_filled = 4;
	int direction = 1;
	int attempts = 0;
	i32 adjusted = 0;
	while (sides_filled != 0) {
		sides_filled = 0;

		// check top
		for (int x = nw.x; x <= se.x; ++x) {
			_idx(x, nw.y);
			if (pixels[idx + 3] != 0) {
				if (direction > 0 && nw.y > 0) {
					adjusted |= zt_bit(ztDirection_Up);
					nw.y = nw.y - 1;
					sides_filled += 1;
				}
				else {
					zt_bitRemove(adjusted, ztDirection_Up);
				}
				break;
			}
		}
		// check bottom
		for (int x = nw.x; x <= se.x; ++x) {
			_idx(x, se.y);
			if (pixels[idx + 3] != 0) {
				if (direction > 0 && se.y < editor->active_tex_size.y - 1) {
					adjusted |= zt_bit(ztDirection_Down);
					se.y = se.y + 1;
					sides_filled += 1;
				}
				else {
					zt_bitRemove(adjusted, ztDirection_Down);
				}
				break;
			}
		}
		// check left
		for (int y = nw.y; y <= se.y; ++y) {
			_idx(nw.x, y);
			if (pixels[idx + 3] != 0) {
				if (direction > 0 && nw.x > 0) {
					adjusted |= zt_bit(ztDirection_Left);
					nw.x = nw.x - 1;
					sides_filled += 1;
				}
				else {
					zt_bitRemove(adjusted, ztDirection_Down);
				}
				break;
			}
		}
		// check right
		for (int y = nw.y; y <= se.y; ++y) {
			_idx(se.x, y);
			if (pixels[idx + 3] != 0) {
				if (direction > 0 && se.x < editor->active_tex_size.x - 1) {
					adjusted |= zt_bit(ztDirection_Right);
					se.x = se.x + 1;
					sides_filled += 1;
				}
				else {
					zt_bitRemove(adjusted, ztDirection_Right);
				}
				break;
			}
		}

		if (sides_filled == 0) {
			break;
		}
		attempts += 1;
	}

	if (attempts == 0) {
		// got all transparent pixels on first attempt, meaning we need to shrink to fit

		int sides_empty = 4;
		while (sides_empty != 0) {
			sides_empty = 0;

			// check top
			bool has_pixel = false;
			for (int x = nw.x; x <= se.x; ++x) {
				_idx(x, nw.y);
				if (pixels[idx + 3] != 0) {
					has_pixel = true;
					break;
				}
			}
			if (!has_pixel) {
				nw.y += 1;
				sides_empty += 1;
			}

			// check bottom
			has_pixel = false;
			for (int x = nw.x; x <= se.x; ++x) {
				_idx(x, se.y);
				if (pixels[idx + 3] != 0) {
					has_pixel = true;
					break;
				}
			}
			if (!has_pixel && se.y > nw.y + 1) {
				se.y -= 1;
				sides_empty += 1;
			}

			// check left
			has_pixel = false;
			for (int y = nw.y; y <= se.y; ++y) {
				_idx(nw.x, y);
				if (pixels[idx + 3] != 0) {
					has_pixel = true;
					break;
				}
			}
			if (!has_pixel) {
				nw.x += 1;
				sides_empty += 1;
			}

			// check right
			has_pixel = false;
			for (int y = nw.y; y <= se.y; ++y) {
				_idx(se.x, y);
				if (pixels[idx + 3] != 0) {
					has_pixel = true;
					break;
				}
			}
			if (!has_pixel && se.x > nw.x + 1) {
				se.x -= 1;
				sides_empty += 1;
			}

			if (sides_empty == 0) {
				se.y += 1;
				se.x += 1;
				break;
			}
			attempts += 1;
		}
	}
	else {
		if (zt_bitIsSet(adjusted, zt_bit(ztDirection_Up))) {
			nw.y += 1;
		}
		//		if (zt_bitIsSet(adjusted, zt_bit(ztDirection_Down))) {
		//			se.y -= 1;
		//		}
		if (zt_bitIsSet(adjusted, zt_bit(ztDirection_Left))) {
			nw.x += 1;
		}
		//		if (zt_bitIsSet(adjusted, zt_bit(ztDirection_Right))) {
		//			se.x -= 1;
		//		}
	}

	zt_free(pixels);

	editor->sprite_pos[editor->sprite_active] = zt_vec2(nw.x / ppu, nw.y / ppu);
	editor->sprite_size[editor->sprite_active] = zt_vec2((se.x - nw.x) / ppu, (se.y - nw.y) / ppu);

	_zt_debugSpriteEdDisplayReadVals(editor);

#undef _idx
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayButtonGridSplitDialogOk, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteEdDisplayButtonGridSplitDialogOk))
{
	zt_guiItemQueueFree(zt_guiItemGetTopLevelParent(button));

	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	if (editor->sprite_grid_values.x <= 0 || editor->sprite_grid_values.y <= 0) {
		return;
	}
	if (editor->sprite_type[editor->sprite_active] != 0) {
		return;
	}


	ztVec2 grid_size = editor->sprite_size[editor->sprite_active];
	ztVec2 grid_start = editor->sprite_pos[editor->sprite_active];// -(grid_size * .5f);

	grid_size.x /= editor->sprite_grid_values.x;
	grid_size.y /= editor->sprite_grid_values.y;

	ztVec2i grid_size_pix = zt_vec2i(zt_convertToi32Floor(grid_size.x * zt_pixelsPerUnit()), zt_convertToi32Floor(grid_size.y * zt_pixelsPerUnit()));

	//grid_start += grid_size;
	ztVec2 grid_curr = grid_start;

	if(grid_size_pix.x <= 0 || grid_size_pix.y <= 0) {
		return;
	}

	char sprite_prefix[64];
	zt_strCpy(sprite_prefix, zt_elementsOf(sprite_prefix), editor->sprite_name[editor->sprite_active]);

	zt_fyz(editor->sprite_grid_values.y) {
		zt_fxz(editor->sprite_grid_values.x) {

			int idx = (y * editor->sprite_grid_values.x) + x;
			zt_strMakePrintf(sprite_name, 64, "%s_%d", sprite_prefix, idx);

			zt_fize(editor->sprite_pos) {

				if ((idx == 0 && i == editor->sprite_active) || (idx != 0 && editor->sprite_size[i] == ztVec2::zero)) {
					ztVec2i top_left_pix = zt_vec2i(zt_convertToi32Floor(grid_curr.x * zt_pixelsPerUnit()), zt_convertToi32Floor(grid_curr.y * zt_pixelsPerUnit()));

					editor->sprite_pos[i] = zt_vec2(top_left_pix.x / zt_pixelsPerUnit(), top_left_pix.y / zt_pixelsPerUnit());
					editor->sprite_size[i] = grid_size;
					editor->sprite_type[i] = 0;

					zt_strCpy(editor->sprite_name[i], zt_elementsOf(editor->sprite_name[i]), sprite_name);

					if(idx == 0) {
						_zt_debugSpriteEdDisplayReadVals(editor);
					}
					break;
				}
			}

			grid_curr.x += grid_size.x;
		}
		grid_curr.x = grid_start.x;
		grid_curr.y += grid_size.y;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayButtonGridSplit, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteEdDisplayButtonGridSplit))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	ztGuiItem *window = zt_guiMakeWindow("Enter Grid Dimensions", ztGuiWindowBehaviorFlags_AllowClose | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_Modal);
	zt_guiItemSetSize(window, zt_vec2(5, 2.1f));

	editor->sprite_grid_values = zt_vec2i(1, 1);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	ztGuiItem *val_ed = zt_guiMakeEditor(sizer, nullptr, &editor->sprite_grid_values, zt_vec2i(1, 1), zt_vec2i(999, 999), 1, true, "Columns", "   Rows");

	zt_guiItemSetSize(val_ed, zt_vec2(4, .75f));

	r32 padding = 3 / zt_pixelsPerUnit();
	zt_guiSizerAddStretcher(sizer, 1, 0);

	zt_guiSizerAddItem(sizer, val_ed, 2, padding, ztAlign_Center, 0);

	zt_guiSizerAddStretcher(sizer, 1, 0);
	ztGuiItem *split_button = zt_guiMakeButton(sizer, "Split Sprite Into Grid");
	zt_guiSizerAddItem(sizer, split_button, 0, padding, ztAlign_Center, 0);

	zt_guiButtonSetCallback(split_button, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayButtonGridSplitDialogOk), editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayButtonDelete, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteEdDisplayButtonDelete))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;
	editor->sprite_size[editor->sprite_active] = ztVec2::zero;
	editor->sprite_active = -1;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayButtonSave, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteEdDisplayButtonSave))
{
	ztDebugSpriteEditor *editor = (ztDebugSpriteEditor*)user_data;

	int total_sprites = 0;
	zt_fize(editor->sprite_pos) {
		if (editor->sprite_size[i] != ztVec2::zero) {
			total_sprites += 1;
		}
	}

	ztSpriteManager sm;
	zt_spriteManagerMake(&sm, total_sprites);

	r32 ppu = zt_pixelsPerUnit();

	zt_fize(editor->sprite_pos) {
		if (editor->sprite_size[i] != ztVec2::zero) {
			if (editor->sprite_type[i] == 0) {
				ztVec2i sprite_pos = zt_vec2i(zt_convertToi32Floor(editor->sprite_pos[i].x * ppu), zt_convertToi32Floor(editor->sprite_pos[i].y * ppu));
				ztVec2i sprite_size = zt_vec2i(zt_convertToi32Floor(editor->sprite_size[i].x * ppu), zt_convertToi32Floor(editor->sprite_size[i].y * ppu));
				ztVec2i sprite_anchor = zt_vec2i(zt_convertToi32Floor(editor->sprite_anchor[i].x * ppu), zt_convertToi32Floor(editor->sprite_anchor[i].y * ppu));

				ztSprite sprite = zt_spriteMake(editor->active_tex, sprite_pos, sprite_size, sprite_anchor);
				zt_spriteManagerAddSprite(&sm, &sprite, editor->sprite_name[i]);
			}
			else {
				ztVec2i sprite_pos = zt_vec2i(zt_convertToi32Floor(editor->sprite_pos[i].x * ppu), zt_convertToi32Floor(editor->sprite_pos[i].y * ppu));
				ztVec2i sprite_size = zt_vec2i(zt_convertToi32Floor(editor->sprite_size[i].x * ppu), zt_convertToi32Floor(editor->sprite_size[i].y * ppu));
				ztVec2i sprite_nw = zt_vec2i(zt_convertToi32Floor(editor->sprite_nw[i].x * ppu), zt_convertToi32Floor(editor->sprite_nw[i].y * ppu));
				ztVec2i sprite_se = zt_vec2i(zt_convertToi32Floor(editor->sprite_se[i].x * ppu), zt_convertToi32Floor(editor->sprite_se[i].y * ppu));
				ztVec2i sprite_offset_nw = zt_vec2i(zt_convertToi32Floor(editor->sprite_offset_nw[i].x * ppu), zt_convertToi32Floor(editor->sprite_offset_nw[i].y * ppu));
				ztVec2i sprite_offset_se = zt_vec2i(zt_convertToi32Floor(editor->sprite_offset_se[i].x * ppu), zt_convertToi32Floor(editor->sprite_offset_se[i].y * ppu));

				ztSpriteNineSlice sns = zt_spriteNineSliceMake(editor->active_tex, sprite_pos, sprite_size, sprite_nw, sprite_se, sprite_offset_nw.x, sprite_offset_nw.y, sprite_offset_se.x, sprite_offset_se.y);
				zt_spriteManagerAddSpriteNineSlice(&sm, &sns, editor->sprite_name[i]);
			}
		}
	}

	char tex_name[ztFileMaxPath];
	if (_zt_debugSpriteEdDisplayGetFileName(editor, tex_name, zt_elementsOf(tex_name))) {
		ztSerial serial;
		if (zt_serialMakeWriter(&serial, tex_name, ZT_SPRITE_FILE_GUID, ZT_SPRITE_FILE_VERSION)) {
			if (zt_spriteManagerSave(&sm, &serial)) {
				zt_logInfo("Sprite manager saved: %s", tex_name);
			}
			zt_serialClose(&serial);
		}
	}
	else {
		zt_assert(false); // should only be working with asset textures here
	}

	zt_spriteManagerFree(&sm);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteEdDisplayButtonReset, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteEdDisplayButtonReset))
{
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteEditor()
{
	const char *window_name = "Sprite Editor";

	{
		ztGuiItem *window = zt_guiItemFindByName(window_name);
		if (window != nullptr) {
			zt_guiItemShow(window, true);
			zt_guiItemBringToFront(window);
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztDebugSpriteEditor *editor = zt_mallocStructArena(ztDebugSpriteEditor, gm->arena);
	*editor = {};

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window = zt_guiMakeWindow(window_name, ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);
	zt_guiItemSetSize(window, zt_cameraOrthoGetViewportSize(gm->gui_camera) - zt_vec2(1, 1.5f));
	zt_guiItemSetUserData(window, editor);

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	zt_guiSizerSizeToParent(sizer);
	zt_guiItemSetName(sizer, "main_panel");

	ztGuiItem *tools_panel = zt_guiMakePanel(sizer, ztGuiPanelBehaviorFlags_DrawBackground, editor, gm->arena);
	zt_guiItemSetName(tools_panel, "tools_panel");
	zt_guiItemSetMinSize(tools_panel, zt_vec2(350 / zt_pixelsPerUnit(), 30 / zt_pixelsPerUnit()));
	{
		ztGuiItem *sizer_tools = zt_guiMakeSizer(tools_panel, ztGuiItemOrient_Horz);

		zt_guiSizerAddItem(sizer_tools, zt_guiMakeStaticText(sizer_tools, "Texture:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->combo_textures = zt_guiMakeComboBox(sizer_tools, 128);
		zt_guiSizerAddItem(sizer_tools, editor->combo_textures, 0, padding);
		zt_guiComboBoxSetCallback(editor->combo_textures, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEditorComboTexture), editor);

		zt_fiz(zt_game->textures_count) {
			if (i > 0 && !zt_textureIsRenderTarget(i) && zt_textureGetSize(i) != zt_vec2i(0, 0)) {
				zt_strMakePrintf(texture_info, 256, "[%d] %s (%d x %d)", i, zt_game->textures[i].name, zt_game->textures[i].width, zt_game->textures[i].height);
				zt_guiComboBoxAppend(editor->combo_textures, texture_info, (void*)i);
			}
		}
		zt_guiItemAutoSize(editor->combo_textures);
		zt_guiComboBoxSetSelected(editor->combo_textures, 0);

		ztGuiItem *button_save = zt_guiMakeButton(sizer, "Save");
		zt_guiButtonSetCallback(button_save, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayButtonSave), editor);
		zt_guiSizerAddItem(sizer_tools, button_save, 0, padding);

		ztGuiItem *button_reset = zt_guiMakeButton(sizer, "Reset");
		zt_guiSizerAddItem(sizer_tools, button_reset, 0, padding);


		zt_guiSizerAddStretcher(sizer_tools, 1);
	}

	{
		int w = 512;
		int h = 512;
		byte *grid_tex = zt_mallocStructArray(byte, w * h * 4);

		zt_fyz(h) {
			zt_fxz(w) {
				int idx = ((y * w) + x) * 4;

				i32 color = ((zt_convertToi32Floor(y / 16.f) % 2) + zt_convertToi32Floor(x / 16.f)) % 2 == 0 ? 128 : 190;
				grid_tex[idx + 0] = color;
				grid_tex[idx + 1] = color;
				grid_tex[idx + 2] = color;
				grid_tex[idx + 3] = 255;
			}
		}

		ztTextureID tex = zt_textureMakeFromPixelData(grid_tex, w, h, ztTextureFlags_PixelPerfect);
		editor->grid_texture = tex;

		editor->grid_texture_size = zt_vec2i(w, h);

		zt_free(grid_tex);
	}


	zt_guiSizerAddItem(sizer, tools_panel, 0, padding);

	ztGuiItem *scroll = zt_guiMakeScrollContainer(sizer);

	ztGuiItem *display_panel = zt_guiMakePanel(scroll, ztGuiPanelBehaviorFlags_DrawBackground | ztGuiItemBehaviorFlags_WantsFocus);
	zt_guiScrollContainerSetItem(scroll, display_panel);
	zt_guiSizerAddItem(sizer, scroll, 1, padding);


	editor->sprite_info_panel = zt_guiMakePanel(zt_guiWindowGetContentParent(window), ztGuiPanelBehaviorFlags_DrawBackground | ztGuiItemBehaviorFlags_WantsFocus | ztGuiItemBehaviorFlags_WantsInput);
	{
		int idx_spr = 0;
		int idx_sns = 0;

		zt_guiItemSetPosition(editor->sprite_info_panel, ztAlign_Right | ztAlign_Bottom, ztAnchor_Right | ztAnchor_Bottom, zt_vec2(-10 / zt_pixelsPerUnit(), 10 / zt_pixelsPerUnit()));

		ztGuiItem *sizer = zt_guiMakeColumnSizer(editor->sprite_info_panel, 2, ztGuiColumnSizerType_FillRow, true);
		zt_guiColumnSizerSetProp(sizer, 1, 1);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Sprite Name:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);

		editor->text_name = zt_guiMakeTextEdit(sizer, "sprite_01", 0, 128);
		zt_guiTextEditSetCallback(editor->text_name, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayTextChange), editor);
		zt_guiSizerAddItem(sizer, editor->text_name, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Type:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->combo_type = zt_guiMakeComboBox(sizer, 2);
		zt_guiComboBoxAppend(editor->combo_type, "Sprite");
		zt_guiComboBoxAppend(editor->combo_type, "Nine Slice");
		zt_guiComboBoxSetCallback(editor->combo_type, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEditorComboType), editor);
		zt_guiSizerAddItem(sizer, editor->combo_type, 1, padding);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Position:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_xy = zt_guiMakeEditor(sizer, nullptr, &editor->val_xy, zt_vec2i(0, 0), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "X", "Y");
		zt_guiSizerAddItem(sizer, editor->edit_xy, 1, padding);
		zt_guiEditorSetCallback(editor->edit_xy, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);

		zt_guiSizerAddItem(sizer, zt_guiMakeStaticText(sizer, "Size:"), 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_wh = zt_guiMakeEditor(sizer, nullptr, &editor->val_wh, zt_vec2i(1, 1), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "W", "H");
		zt_guiSizerAddItem(sizer, editor->edit_wh, 1, padding);
		zt_guiEditorSetCallback(editor->edit_wh, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);

		ztGuiItem *label = zt_guiMakeStaticText(sizer, "Anchor:");
		zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_anchor = zt_guiMakeEditor(sizer, nullptr, &editor->val_anchor, zt_vec2i(ztInt32Min, ztInt32Min), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "X", "Y");
		zt_guiSizerAddItem(sizer, editor->edit_anchor, 1, padding);
		zt_guiEditorSetCallback(editor->edit_anchor, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);
		editor->gui_edit_sprite[idx_spr++] = label;
		editor->gui_edit_sprite[idx_spr++] = editor->edit_anchor;


		label = zt_guiMakeStaticText(sizer, "Nine Slice NW:");
		zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_nw = zt_guiMakeEditor(sizer, nullptr, &editor->val_nw, zt_vec2i(0, 0), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "X", "Y");
		zt_guiSizerAddItem(sizer, editor->edit_nw, 1, padding);
		zt_guiEditorSetCallback(editor->edit_nw, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);
		editor->gui_edit_nineslice[idx_sns++] = label;
		editor->gui_edit_nineslice[idx_sns++] = editor->edit_nw;

		label = zt_guiMakeStaticText(sizer, "Offset:");
		zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_offset_nw = zt_guiMakeEditor(sizer, nullptr, &editor->val_offset_nw, zt_vec2i(ztInt32Min, ztInt32Min), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "X", "Y");
		zt_guiSizerAddItem(sizer, editor->edit_offset_nw, 1, padding);
		zt_guiEditorSetCallback(editor->edit_offset_nw, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);
		editor->gui_edit_nineslice[idx_sns++] = label;
		editor->gui_edit_nineslice[idx_sns++] = editor->edit_offset_nw;

		label = zt_guiMakeStaticText(sizer, "Nine Slice SE:");
		zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_se = zt_guiMakeEditor(sizer, nullptr, &editor->val_se, zt_vec2i(0, 0), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "X", "Y");
		zt_guiSizerAddItem(sizer, editor->edit_se, 1, padding);
		zt_guiEditorSetCallback(editor->edit_se, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);
		editor->gui_edit_nineslice[idx_sns++] = label;
		editor->gui_edit_nineslice[idx_sns++] = editor->edit_se;

		label = zt_guiMakeStaticText(sizer, "Offset:");
		zt_guiSizerAddItem(sizer, label, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		editor->edit_offset_se = zt_guiMakeEditor(sizer, nullptr, &editor->val_offset_se, zt_vec2i(ztInt32Min, ztInt32Min), zt_vec2i(ztInt32Max, ztInt32Max), 1, false, "X", "Y");
		zt_guiSizerAddItem(sizer, editor->edit_offset_se, 1, padding);
		zt_guiEditorSetCallback(editor->edit_offset_se, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayEditorChanged), editor);
		editor->gui_edit_nineslice[idx_sns++] = label;
		editor->gui_edit_nineslice[idx_sns++] = editor->edit_offset_se;

		zt_guiSizerAddStretcher(sizer, 0);

		ztGuiItem *button_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(sizer, button_sizer, 0, padding, ztAlign_Right, ztGuiItemOrient_Vert);

		ztGuiItem *button_delete = zt_guiMakeButton(sizer, "Delete Sprite");
		zt_guiSizerAddItem(button_sizer, button_delete, 0, padding, ztAlign_Right, ztGuiItemOrient_Vert);
		zt_guiButtonSetCallback(button_delete, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayButtonDelete), editor);

		ztGuiItem *button_best_fit = zt_guiMakeButton(sizer, "Best Fit");
		zt_guiSizerAddItem(button_sizer, button_best_fit, 0, padding, ztAlign_Right, ztGuiItemOrient_Vert);
		zt_guiButtonSetCallback(button_best_fit, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayButtonBestFit), editor);

		ztGuiItem *button_grid = zt_guiMakeButton(sizer, "Grid Split");
		zt_guiSizerAddItem(button_sizer, button_grid, 0, padding, ztAlign_Right, ztGuiItemOrient_Vert);
		zt_guiButtonSetCallback(button_grid, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayButtonGridSplit), editor);

		editor->gui_edit_sprite[idx_spr++] = button_grid;

		zt_guiItemSetSize(editor->sprite_info_panel, zt_guiSizerGetMinSize(sizer) + zt_vec2(padding * 2, padding * 2));
		zt_guiItemHide(editor->sprite_info_panel);
	}

	editor->display = display_panel;
	editor->display_scroll = scroll;
	editor->display_drag_pos = ztVec2::min;
	editor->display_drag_type = ztDebugSpriteDragType_None;
	editor->display_zoom_level = 0;
	editor->ignore_value_change = false;

	editor->sprite_active = -1;

	display_panel->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayRender);
	display_panel->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayUpdate);
	display_panel->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayInputMouse);
	display_panel->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteEdDisplayCleanup);
	display_panel->functions.user_data = editor;

	_zt_debugSpriteEditorComboTexture(editor->combo_textures, 0, editor);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#ifndef ZT_SPRITE_ANIM_EDITOR_MAX_SPRITES
#define ZT_SPRITE_ANIM_EDITOR_MAX_SPRITES (1024 * 4)
#endif

#ifndef ZT_SPRITE_ANIM_EDITOR_MAX_ANIMS
#define ZT_SPRITE_ANIM_EDITOR_MAX_ANIMS 512
#endif

#ifndef ZT_SPRITE_ANIM_EDITOR_MAX_SEQUENCES
#define ZT_SPRITE_ANIM_EDITOR_MAX_SEQUENCES 128
#endif

#ifndef ZT_SPRITE_ANIM_EDITOR_MAX_ENTRIES
#define ZT_SPRITE_ANIM_EDITOR_MAX_ENTRIES 128
#endif

// ================================================================================================================================================================================================

struct ztSpriteAnimEditorEntry
{
	i32  hash;
	int  prop;

	ztGuiItem *button;
	ztGuiItem *editor;
};

// ================================================================================================================================================================================================

struct ztSpriteAnimEditorSequence
{
	char name[64];
	i32  hash;

	i32  sprite_hash[ZT_SPRITE_ANIM_EDITOR_MAX_ENTRIES];
	i32  sprite_prop[ZT_SPRITE_ANIM_EDITOR_MAX_ENTRIES];

	int  sprites;

	bool loops;
	r32  length;
};

// ================================================================================================================================================================================================

struct ztSpriteAnimEditor
{
	ztGuiItem                 *lbl_file;

	ztGuiItem                 *combo_sequences;
	ztGuiItem                 *text_sequence_name;

	ztGuiItem                 *ed_length;
	r32                        ed_length_val;

	ztGuiItem                 *chk_loops;
	bool                       chk_loops_val;

	ztGuiItem                 *list_sprites;

	ztSpriteAnimEditorSequence sequences[ZT_SPRITE_ANIM_EDITOR_MAX_SEQUENCES];
	int                        sequences_count;

	ztSpriteAnimEditorEntry    entries[ZT_SPRITE_ANIM_EDITOR_MAX_ENTRIES];
	int                        entries_count;

	ztSpriteManager            sprite_manager;
	ztTextureID                sprite_manager_textures[ZT_MAX_TEXTURES];

	ztGuiItem                 *sprite_display;
	ztGuiItem                 *sprite_display_info;

	int                        active_sequence;
	int                        active_entry;
	r32                        active_time;
	bool                       active_playing;

	ztGuiItem                 *button_play;

	char                       work_file[ztFileMaxPath];
};

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEdRefreshSequenceCombo(ztSpriteAnimEditor *editor)
{
	zt_guiComboBoxClear(editor->combo_sequences);
	zt_guiComboBoxAppend(editor->combo_sequences, "[New Sequence]");

	zt_fiz(editor->sequences_count) {
		zt_guiComboBoxAppend(editor->combo_sequences, editor->sequences[i].name);
	}

	zt_guiComboBoxSetSelected(editor->combo_sequences, editor->active_sequence + 1);
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEdAddSequence(ztSpriteAnimEditor *editor, const char *seq_name)
{
	zt_assertReturnOnFail(editor->sequences_count < zt_elementsOf(editor->sequences));
	ztSpriteAnimEditorSequence *seq = &editor->sequences[editor->sequences_count++];

	zt_strCpy(seq->name, zt_elementsOf(seq->name), seq_name);
	seq->hash = zt_strHash(seq_name);
	seq->sprites = 0;
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEdLoadSequences(ztSpriteAnimEditor *editor)
{
	editor->sequences_count = 0;
	editor->active_sequence = 0;

	if (editor->sequences_count == 0) {
		_zt_debugSpriteAnimEdAddSequence(editor, "new_sequence");
	}

	_zt_debugSpriteAnimEdRefreshSequenceCombo(editor);
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEdSyncEntries(ztSpriteAnimEditor *editor)
{
	if (editor->active_sequence >= 0) {
		ztSpriteAnimEditorSequence *seq = &editor->sequences[editor->active_sequence];
		seq->sprites = 0;
		zt_fiz(editor->entries_count) {
			if (editor->entries[i].hash == 0) {
				zt_guiButtonSetIcon(editor->entries[i].button, nullptr);
				zt_guiItemSetLabel(editor->entries[i].button, "Select Sprite");
				zt_guiItemAutoSize(editor->entries[i].button);
				editor->entries[i].button->min_size = editor->entries[i].button->size;
			}
			else {
				int sidx = seq->sprites++;
				seq->sprite_hash[sidx] = editor->entries[i].hash;
				seq->sprite_prop[sidx] = editor->entries[i].prop;

				zt_fjz(editor->sprite_manager.sprites_count) {
					if (editor->sprite_manager.sprites[j].hash == editor->entries[i].hash) {
						editor->entries[i].button->min_size = ztVec2::zero;
						zt_guiButtonSetIcon(editor->entries[i].button, &editor->sprite_manager.sprites[j].s);
						zt_guiItemSetLabel(editor->entries[i].button, editor->sprite_manager.sprites[j].name);
						zt_guiItemAutoSize(editor->entries[i].button);
						editor->entries[i].button->min_size = editor->entries[i].button->size;
						break;
					}
				}
			}
		}
		seq->length = editor->ed_length_val;
		seq->loops = editor->chk_loops_val;

		zt_guiListBoxRefresh(editor->list_sprites);
	}
}

// ================================================================================================================================================================================================

ztInternal int _zt_debugSpriteAnimEdAddSpriteEntry(ztSpriteAnimEditor *editor, int before);

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdSelectSpriteWindowButton, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdSelectSpriteWindowButton))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(button));
	ztSpriteManager::Entry *sprite_entry = (ztSpriteManager::Entry*)user_data;

	int idx = editor->active_entry;

	editor->entries[idx].hash = sprite_entry->hash;

	zt_guiItemFree(zt_guiItemGetTopLevelParent(button));

	zt_guiListBoxScrollToItem(editor->list_sprites, idx);

	int items = zt_guiListBoxGetCount(editor->list_sprites);

	if (items == 1) {
		char num[16];
		int pos_us = zt_strFindLastPos(sprite_entry->name, "_");
		if (pos_us != ztStrPosNotFound) {
			zt_strCpy(num, zt_elementsOf(num), sprite_entry->name + pos_us + 1);
			bool is_number = false;
			int start_val = zt_strToInt(num, 0, &is_number);

			if (is_number) {
				char prefix[64];
				zt_strCpy(prefix, zt_elementsOf(prefix), sprite_entry->name, pos_us);

				while (true) {
					zt_strMakePrintf(next, 64, "%s_%d", prefix, ++start_val);
					i32 hash = zt_strHash(next);

					bool found = false;
					zt_fiz(editor->sprite_manager.sprites_count) {
						if (editor->sprite_manager.sprites[i].hash == hash) {
							int x = _zt_debugSpriteAnimEdAddSpriteEntry(editor, -1);
							editor->entries[x].hash = hash;
							editor->entries[x].prop = 1;
							found = true;
							break;
						}
					}

					if (!found) break;
				}
			}			
		}
	}

	_zt_debugSpriteAnimEdSyncEntries(editor);

	if (editor->entries[items - 1].hash != 0) {
		_zt_debugSpriteAnimEdAddSpriteEntry(editor, -1);
	}

}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEdSelectSprite(ztSpriteAnimEditor *editor, int entry)
{
	ztGuiItem *window = zt_guiMakeWindow("Select Sprite", ztGuiWindowBehaviorFlags_Modal | ztGuiWindowBehaviorFlags_ShowTitle | ztGuiWindowBehaviorFlags_AllowResize | ztGuiWindowBehaviorFlags_AllowDrag | ztGuiWindowBehaviorFlags_AllowClose | ztGuiItemBehaviorFlags_BringToFront);
	zt_guiItemSetSize(window, zt_vec2(16, 10));
	zt_guiItemSetName(window, "Select Sprite Window");
	zt_guiItemBringToFront(window);

	editor->active_entry = entry;
	zt_guiItemSetUserData(window, editor);

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window_sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);
	ztGuiItem *scroll = zt_guiMakeScrollContainer(window_sizer, ztGuiScrollContainerBehaviorFlags_StretchHorz);
	zt_guiSizerAddItem(window_sizer, scroll, 1, padding);

	ztGuiItem *sizer = zt_guiMakeWrapSizer(window_sizer, ztGuiItemOrient_Horz);

	zt_guiScrollContainerSetItem(scroll, sizer);

	int sprites_count = 0;
	zt_fiz(editor->sprite_manager.sprites_count) {
		if (editor->sprite_manager.sprites[i].hash != 0 && editor->sprite_manager.sprites[i].type == ztSpriteType_Sprite) {
			sprites_count += 1;
		}
	}

	ztSpriteManager::Entry **entries = zt_mallocStructArray(ztSpriteManager::Entry*, sprites_count);
	sprites_count = 0;
	zt_fiz(editor->sprite_manager.sprites_count) {
		if (editor->sprite_manager.sprites[i].hash != 0 && editor->sprite_manager.sprites[i].type == ztSpriteType_Sprite) {
			entries[sprites_count++] = &editor->sprite_manager.sprites[i];
		}
	}

	struct local
	{
		static int compare(const void *vone, const void *vtwo)
		{
			ztSpriteManager::Entry* one = *(ztSpriteManager::Entry**)vone;
			ztSpriteManager::Entry* two = *(ztSpriteManager::Entry**)vtwo;

			return zt_striCmp(one->name, two->name);
		}
	};

	qsort(entries, sprites_count, zt_sizeof(ztSpriteManager::Entry*), local::compare);

	zt_fiz(sprites_count) {
		ztGuiItem *button = zt_guiMakeButton(sizer, entries[i]->name, ztGuiButtonBehaviorFlags_NoBackground);
		zt_guiButtonSetTextPosition(button, ztAlign_VertCenter | ztAlign_Bottom);
		zt_guiButtonSetIcon(button, &entries[i]->s);
		zt_guiSizerAddItem(sizer, button, 0, padding, ztAlign_Bottom, 0);
		zt_guiButtonSetCallback(button, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdSelectSpriteWindowButton), entries[i]);
	}

	zt_free(entries);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdSelectSpriteButton, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdSelectSpriteButton))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(button));
	int entry = (int)(pointer)user_data;
	_zt_debugSpriteAnimEdSelectSprite(editor, entry);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonEntryMoveUp, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonEntryMoveUp))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(button));
	int entry = (int)(pointer)user_data;

	if (entry == 0) {
		return;
	}

	int temp_hash = editor->entries[entry - 1].hash;
	int temp_prop = editor->entries[entry - 1].prop;

	editor->entries[entry - 1].hash = editor->entries[entry].hash;
	editor->entries[entry - 1].prop = editor->entries[entry].prop;

	editor->entries[entry].hash = temp_hash;
	editor->entries[entry].prop = temp_prop;

	_zt_debugSpriteAnimEdSyncEntries(editor);

	zt_guiListBoxSetSelected(editor->list_sprites, entry - 1);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonEntryMoveDn, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonEntryMoveDn))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(button));
	int entry = (int)(pointer)user_data;

	if (entry >= editor->entries_count - 2) {
		return;
	}

	int temp_hash = editor->entries[entry + 1].hash;
	int temp_prop = editor->entries[entry + 1].prop;

	editor->entries[entry + 1].hash = editor->entries[entry].hash;
	editor->entries[entry + 1].prop = editor->entries[entry].prop;

	editor->entries[entry].hash = temp_hash;
	editor->entries[entry].prop = temp_prop;

	_zt_debugSpriteAnimEdSyncEntries(editor);

	zt_guiListBoxSetSelected(editor->list_sprites, entry + 1);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonEntryDelete, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonEntryDelete))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)zt_guiItemGetUserData(zt_guiItemGetTopLevelParent(button));
	int entry = (int)(pointer)user_data;

	if (editor->entries_count <= 1) {
		return;
	}

	for (int i = entry; i < editor->entries_count - 1; ++i) {
		editor->entries[i].hash = editor->entries[i + 1].hash;
		editor->entries[i].prop = editor->entries[i + 1].prop;
	}

	editor->entries[editor->entries_count - 1].hash = 0;

	zt_guiListBoxRemoveItem(editor->list_sprites, editor->entries_count - 1);

	editor->entries_count -= 1;

	_zt_debugSpriteAnimEdSyncEntries(editor);
}

// ================================================================================================================================================================================================

ztInternal int _zt_debugSpriteAnimEdAddSpriteEntry(ztSpriteAnimEditor *editor, int before)
{
	ztGuiItem *entry = zt_guiMakePanel(editor->list_sprites);
	zt_guiItemSetName(entry, "Sprite Panel");

	ztGuiItem *button_sel = zt_guiMakeButton(entry, "Select Sprite");
	zt_guiButtonSetTextPosition(button_sel, ztAlign_VertCenter | ztAlign_Bottom);
	button_sel->min_size = button_sel->size;

	int idx = editor->entries_count++;
	ztSpriteAnimEditorEntry *ed_entry = &editor->entries[idx];

	zt_guiButtonSetCallback(button_sel, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdSelectSpriteButton), (void*)idx);

	ed_entry->hash = 0;
	ed_entry->prop = 1;
	ed_entry->button = button_sel;

	ztGuiItem *edit = zt_guiMakeEditor(entry, nullptr, &ed_entry->prop, 0, 999, 1);
	ed_entry->editor = edit;

	ztGuiItem *button_up = zt_guiMakeButton(entry, nullptr);
	ztSprite sprite_up = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 917, 1, 13, 13);
	zt_guiButtonSetIcon(button_up, &sprite_up);
	zt_guiButtonSetCallback(button_up, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonEntryMoveUp), (void*)idx);
	zt_guiItemAutoSize(button_up);

	ztGuiItem *button_dn = zt_guiMakeButton(entry, nullptr);
	ztSprite sprite_dn = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 991, 13, 13, 13);
	zt_guiButtonSetIcon(button_dn, &sprite_dn);
	zt_guiButtonSetCallback(button_dn, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonEntryMoveDn), (void*)idx);
	zt_guiItemAutoSize(button_dn);

	ztGuiItem *button_rm = zt_guiMakeButton(entry, nullptr);
	ztSprite sprite_rm = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 633, 43, 19, 19);
	zt_guiButtonSetIcon(button_rm, &sprite_rm);
	zt_guiButtonSetCallback(button_rm, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonEntryDelete), (void*)idx);
	zt_guiItemAutoSize(button_rm);

	button_up->size.x = button_dn->size.x = button_rm->size.x = zt_max(button_up->size.x, zt_max(button_dn->size.x, button_rm->size.x));
	button_up->size.y = button_dn->size.y = button_rm->size.y = zt_max(button_up->size.y, zt_max(button_dn->size.y, button_rm->size.y));

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *sizer = zt_guiMakeSizer(entry, ztGuiItemOrient_Horz, true);
	zt_guiItemSetName(sizer, "Sprite Panel Sizer");
	zt_guiSizerSizeParent(sizer, false, true);
	zt_guiSizerSizeToParent(sizer, true);
	zt_guiSizerAddItem(sizer, button_sel, 1, padding, ztAlign_Left | ztAlign_VertCenter, 0);
	zt_guiSizerAddItem(sizer, edit, 0, padding, ztAlign_Center | ztAlign_Top, 0);
	zt_guiSizerAddItem(sizer, button_up, 0, padding, ztAlign_Center | ztAlign_Top, 0);
	zt_guiSizerAddItem(sizer, button_dn, 0, padding, ztAlign_Center | ztAlign_Top, 0);
	zt_guiSizerAddItem(sizer, button_rm, 0, padding, ztAlign_Center | ztAlign_Top, 0);

	zt_guiSizerRecalcImmediately(sizer);

	zt_guiListBoxAppend(editor->list_sprites, entry, nullptr, true);

	if (before >= 0) {
		for (int i = editor->entries_count - 2; i >= before; --i) {
			editor->entries[i + 1].hash = editor->entries[i].hash;
			editor->entries[i + 1].prop = editor->entries[i].prop;
		}

		editor->entries[before].hash = 0;
		editor->entries[before].prop = 1;

		idx = before;
	}

	return idx;
}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEdLoadSeq(ztSpriteAnimEditor *editor, int seq_idx)
{
	zt_assertReturnOnFail(seq_idx >= 0 && seq_idx < editor->sequences_count);

	zt_guiComboBoxSetSelected(editor->combo_sequences, seq_idx + 1);

	ztSpriteAnimEditorSequence *seq = &editor->sequences[seq_idx];

	editor->entries_count = 0;
	editor->active_sequence = seq_idx;
	editor->active_playing = false;
	editor->active_time = 0;

	zt_guiListBoxClear(editor->list_sprites);
	zt_fiz(seq->sprites) {
		_zt_debugSpriteAnimEdAddSpriteEntry(editor, 0);
	}
	_zt_debugSpriteAnimEdAddSpriteEntry(editor, 0);

	zt_fiz(seq->sprites) {
		editor->entries[i].hash = seq->sprite_hash[i];
		editor->entries[i].prop = seq->sprite_prop[i];
	}

	editor->ed_length_val = seq->length;
	editor->chk_loops_val = seq->loops;

	_zt_debugSpriteAnimEdSyncEntries(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonSeqRenameResult, ZT_FUNC_GUI_DIALOG_GET_USER_TEXT(_zt_debugSpriteAnimEdButtonSeqRenameResult))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	ztSpriteAnimEditorSequence *seq = &editor->sequences[editor->active_sequence];
	if (!zt_strEquals(seq->name, value)) {
		zt_strCpy(seq->name, zt_elementsOf(seq->name), value);
		seq->hash = zt_strHash(seq->name);
		_zt_debugSpriteAnimEdRefreshSequenceCombo(editor);
	}
	_zt_debugSpriteAnimEdSyncEntries(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonFileNewDialogCallback, ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_debugSpriteAnimEdButtonFileNewDialogCallback))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	if (zt_fileExists(path)) {
		zt_guiDialogMessageBoxOk("File Already Exists", "This file already exists.\n\nPlease choose a new file.", ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	zt_strCpy(editor->work_file, zt_elementsOf(editor->work_file), path);

	int pos_path_sep = zt_strFindLastPos(editor->work_file, ztFilePathSeparatorStr);

	zt_guiItemSetLabel(editor->lbl_file, editor->work_file + pos_path_sep + 1);
	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor->lbl_file));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonFileNew, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonFileNew))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	char path[ztFileMaxPath];
	char *path_to_send = path;

	zt_fileConcatFileToPath(path, ztFileMaxPath, zt_game->game_details.data_path, "textures");
	if (!zt_directoryExists(path)) {
		path_to_send = nullptr;
	}

	zt_guiDialogFileSelect("Choose Sprite Animation File", ztGuiDialogFileSelectFlags_Open, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonFileNewDialogCallback), editor, path_to_send);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonFileOpenDialogCallback, ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_debugSpriteAnimEdButtonFileOpenDialogCallback))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	zt_logDebug("choose sprite anim file: %s", path);

	if (!zt_fileExists(path)) {
		char message[ztFileMaxPath + 128];
		zt_strPrintf(message, zt_elementsOf(message), "File does not exist:\n\n%s", path);
		zt_guiDialogMessageBoxOk("Sprite Animation File Required", message, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	zt_strCpy(editor->work_file, zt_elementsOf(editor->work_file), path);

	editor->sequences_count = 0;
	editor->entries_count = 0;
	editor->active_sequence = -1;
	editor->active_entry = -1;
	editor->active_time = 0;
	editor->active_playing = false;

	ztSpriteAnimManager anim_manager;
	zt_spriteAnimManagerMake(&anim_manager, ZT_SPRITE_ANIM_EDITOR_MAX_SEQUENCES);

	const char *error = nullptr;

	ztSerial serial;
	if (zt_serialMakeReader(&serial, editor->work_file, ZT_SPRITE_ANIM_FILE_GUID)) {
		if (!zt_spriteAnimManagerLoad(&anim_manager, &serial)) {
			error = "Unable to load animation manager";
		}
		zt_serialClose(&serial);
	}
	else {
		error = "Unable to read from file.";
	}

	if (error != nullptr) {
		zt_spriteAnimManagerFree(&anim_manager);
		zt_guiDialogMessageBoxOk("Unable to Load Sprite Animation File", error, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	zt_fiz(anim_manager.sequences_count) {
		if (anim_manager.sequences[i].hash == 0) {
			break;
		}

		editor->sequences[i].hash = anim_manager.sequences[i].hash;
		zt_strCpy(editor->sequences[i].name, zt_elementsOf(editor->sequences[i].name), anim_manager.sequences[i].name);
		editor->sequences[i].length = anim_manager.sequences[i].length;
		editor->sequences[i].loops = anim_manager.sequences[i].loops;

		editor->sequences[i].sprites = anim_manager.sequences[i].sprite_count;
		zt_fjz(editor->sequences[i].sprites) {
			editor->sequences[i].sprite_hash[j] = anim_manager.sequences[i].sprite_hash[j];
			editor->sequences[i].sprite_prop[j] = anim_manager.sequences[i].sprite_prop[j];
		}

		editor->sequences_count += 1;
	}

	zt_spriteAnimManagerFree(&anim_manager);

	_zt_debugSpriteAnimEdRefreshSequenceCombo(editor);
	if (editor->sequences_count > 0) {
		editor->active_sequence = 0;
		_zt_debugSpriteAnimEdLoadSeq(editor, editor->active_sequence);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonFileOpen, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonFileOpen))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	char path[ztFileMaxPath];
	char *path_to_send = path;

	zt_fileConcatFileToPath(path, ztFileMaxPath, zt_game->game_details.data_path, "textures");
	if (!zt_directoryExists(path)) {
		path_to_send = nullptr;
	}

	zt_guiDialogFileSelect("Choose Sprite Animation File", ztGuiDialogFileSelectFlags_Open, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonFileOpenDialogCallback), editor, path_to_send);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonFileSave, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonFileSave))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	char path[ztFileMaxPath] = { 0 };
	zt_fileGetFullPath(editor->work_file, path, zt_elementsOf(path));
	if (!zt_directoryExists(path)) {
		zt_guiDialogMessageBoxOk("Invalid File Name", "Select a valid file name", ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	_zt_debugSpriteAnimEdSyncEntries(editor);

	ztSpriteAnimManager anim_manager;
	zt_spriteAnimManagerMake(&anim_manager, editor->sequences_count);

	zt_fiz(editor->sequences_count) {
		zt_spriteAnimManagerAddSequence(&anim_manager, editor->sequences[i].name, editor->sequences[i].sprite_hash, editor->sequences[i].sprite_prop, editor->sequences[i].sprites, editor->sequences[i].length, editor->sequences[i].loops);
	}

	const char *error = nullptr;

	ztSerial serial;
	if (zt_serialMakeWriter(&serial, editor->work_file, ZT_SPRITE_ANIM_FILE_GUID, ZT_SPRITE_ANIM_FILE_VERSION)) {
		if (!zt_spriteAnimManagerSave(&anim_manager, &serial)) {
			error = "Unable to save animation manager";
		}
		zt_serialClose(&serial);
	}
	else {
		error = "Unable to write to file.";
	}

	zt_spriteAnimManagerFree(&anim_manager);

	if (error != nullptr) {
		char message[ztFileMaxPath];
		zt_strPrintf(message, zt_elementsOf(message), "%s\n\n%s", error, editor->work_file);
		zt_guiDialogMessageBoxOk("Error Saving File", message, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
	}
	else {
		char message[ztFileMaxPath];
		zt_strPrintf(message, zt_elementsOf(message), "File saved.\n\n%s", editor->work_file);
		zt_guiDialogMessageBoxOk("File Successfully Saved", message, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonSeqRename, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonSeqRename))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;
	if (editor->active_sequence >= 0) {
		zt_guiDialogGetUserText("Rename Sequence", "Sequence name:", editor->sequences[editor->active_sequence].name, false, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonSeqRenameResult), editor);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonSeqDelete, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonSeqDelete))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;
	if (editor->active_sequence < 0) {
		return;
	}

	for (int i = editor->active_sequence; i < editor->sequences_count - 1; ++i) {
		zt_memCpy(&editor->sequences[i], zt_sizeof(ztSpriteAnimEditorSequence), &editor->sequences[i + 1], zt_sizeof(ztSpriteAnimEditorSequence));
	}

	editor->sequences_count -= 1;
	editor->active_sequence -= 1;

	if (editor->active_sequence < 0 && editor->sequences_count > 0) {
		editor->active_sequence = 0;
	}

	_zt_debugSpriteAnimEdRefreshSequenceCombo(editor);
	if (editor->sequences_count > 0) {
		_zt_debugSpriteAnimEdLoadSeq(editor, editor->active_sequence);
	}
	else {
		editor->sequences_count = 0;
		editor->active_sequence = 1;
		editor->entries_count = 0;
		editor->active_playing = false;
		editor->active_time = 0;

		zt_guiListBoxClear(editor->list_sprites);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdButtonPlay, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_debugSpriteAnimEdButtonPlay))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	editor->active_playing = !editor->active_playing;

	ztVec2 size = button->size;
	if (editor->active_playing) {
		editor->active_time = 0;
		ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 968, 43, 19, 19);
		zt_guiButtonSetIcon(button, &sprite);
	}
	else {
		ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 988, 43, 18, 18);
		zt_guiButtonSetIcon(button, &sprite);
	}

	button->size = size;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdDialogNewSeq, ZT_FUNC_GUI_DIALOG_GET_USER_TEXT(_zt_debugSpriteAnimEdDialogNewSeq))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	if (cancelled) {
		if (editor->active_sequence > 0) {
			zt_guiComboBoxSetSelected(editor->combo_sequences, editor->active_sequence + 1);
		}
		return;
	}
	zt_assertReturnOnFail(editor->active_sequence < zt_elementsOf(editor->sequences));

	_zt_debugSpriteAnimEdSyncEntries(editor);

	editor->active_sequence = editor->sequences_count++;

	ztSpriteAnimEditorSequence *seq = &editor->sequences[editor->active_sequence];

	zt_strCpy(seq->name, zt_elementsOf(seq->name), value);
	seq->hash = zt_strHash(seq->name);
	seq->sprites = 0;

	editor->active_entry = -1;
	editor->active_playing = false;
	editor->active_time = 0;
	editor->chk_loops_val = true;
	editor->ed_length_val = 1;
	editor->entries_count = 0;

	zt_guiListBoxClear(editor->list_sprites);

	_zt_debugSpriteAnimEdAddSpriteEntry(editor, 0);
	_zt_debugSpriteAnimEdRefreshSequenceCombo(editor);
	_zt_debugSpriteAnimEdSyncEntries(editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdComboSeq, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_debugSpriteAnimEdComboSeq))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	_zt_debugSpriteAnimEdSyncEntries(editor);

	if (selected == 0) {
		zt_guiDialogGetUserText("Sequence Name", "Name of this sequence:", "sequence_name", true, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdDialogNewSeq), editor);
		return;
	}

	_zt_debugSpriteAnimEdLoadSeq(editor, selected - 1);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_debugSpriteAnimEdUpdate))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	int total_prop = 0;
	int total_entries = 0;
	zt_fiz(editor->entries_count) {
		if (editor->entries[i].hash != 0) {
			total_prop += editor->entries[i].prop;
			total_entries += 1;
		}
	}

	if (editor->active_playing) {
		editor->active_time += dt;

		if (editor->active_time > editor->ed_length_val) {
			if (editor->chk_loops_val) {
				editor->active_time -= editor->ed_length_val;
				zt_guiItemShow(editor->sprite_display);
				zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor->sprite_display));
			}
			else {
				_zt_debugSpriteAnimEdButtonPlay(editor->button_play, editor);
				zt_guiListBoxSetSelected(editor->list_sprites, -1);
				zt_guiListBoxScrollToItem(editor->list_sprites, 0);
			}
		}

		char sprite_info[256] = { 0 };

		int curr_prop = zt_convertToi32Floor(total_prop * (editor->active_time / editor->ed_length_val));
		int curr_entry = 0;
		zt_fiz(editor->entries_count) {
			if (editor->entries[i].hash != 0) {
				curr_entry += 1;
				if (curr_prop <= 0) {
					if (editor->active_playing) {
						zt_guiListBoxSetSelected(editor->list_sprites, i);
					}

					ztSprite *sprite = zt_spriteManagerGetSprite(&editor->sprite_manager, editor->entries[i].hash);
					if (sprite) {
						ztGuiThemeSprite sp;
						sp.type = ztGuiThemeSpriteType_Sprite;
						sp.s = *sprite;
						zt_guiSpriteDisplaySetSprite(editor->sprite_display, &sp);
						zt_guiItemAutoSize(editor->sprite_display);
						editor->sprite_display->min_size = editor->sprite_display->size;

						zt_fjz(editor->sprite_manager.sprites_count) {
							if (editor->sprite_manager.sprites[j].hash == editor->entries[i].hash) {
								zt_strPrintf(sprite_info, zt_elementsOf(sprite_info), "%s (%d/%d) %.2f", editor->sprite_manager.sprites[j].name, curr_entry, total_entries, editor->active_time);
								break;
							}
						}

					}
					break;
				}
				curr_prop -= editor->entries[i].prop;
			}
		}

		zt_guiItemSetLabel(editor->sprite_display_info, sprite_info);
	}
	else {
		char sprite_info[256] = { 0 };

		int i = zt_guiListBoxGetSelected(editor->list_sprites);
		if (i >= 0) {
			if (editor->entries[i].hash != 0) {
				ztSprite *sprite = zt_spriteManagerGetSprite(&editor->sprite_manager, editor->entries[i].hash);
				if (sprite) {
					ztGuiThemeSprite sp;
					sp.type = ztGuiThemeSpriteType_Sprite;
					sp.s = *sprite;
					zt_guiSpriteDisplaySetSprite(editor->sprite_display, &sp);
					zt_guiItemAutoSize(editor->sprite_display);
					editor->sprite_display->min_size = editor->sprite_display->size;

					zt_fjz(editor->sprite_manager.sprites_count) {
						if (editor->sprite_manager.sprites[j].hash == editor->entries[i].hash) {
							zt_strPrintf(sprite_info, zt_elementsOf(sprite_info), "%s (%d/%d)", editor->sprite_manager.sprites[j].name, i, total_entries);
							break;
						}
					}

				}

			}
		}
		else {
			ztGuiThemeSprite sp;
			sp.type = ztGuiThemeSpriteType_Sprite;
			sp.s = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 0, 0, 1, 1);
			zt_guiSpriteDisplaySetSprite(editor->sprite_display, &sp);
		}

		zt_guiItemSetLabel(editor->sprite_display_info, sprite_info);
	}

}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_debugSpriteAnimEdCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_debugSpriteAnimEdCleanup))
{
	ztSpriteAnimEditor *editor = (ztSpriteAnimEditor*)user_data;

	zt_fize(editor->sprite_manager_textures) {
		if (editor->sprite_manager_textures[i] != ztInvalidID) {
			zt_textureFree(editor->sprite_manager_textures[i]);
		}
	}

	zt_spriteManagerFree(&editor->sprite_manager);

	zt_freeArena(editor, item->gm->arena);

}

// ================================================================================================================================================================================================

ztInternal void _zt_debugSpriteAnimEditor()
{
	const char *window_name = "Sprite Animation Editor";

	{
		ztGuiItem *window = zt_guiItemFindByName(window_name);
		if (window != nullptr) {
			zt_guiItemShow(window, true);
			zt_guiItemBringToFront(window);
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztSpriteAnimEditor *editor = zt_mallocStructArena(ztSpriteAnimEditor, gm->arena);
	*editor = {};

	zt_spriteManagerMake(&editor->sprite_manager, ZT_SPRITE_ANIM_EDITOR_MAX_SPRITES);
	{
		zt_fize(editor->sprite_manager_textures) {
			editor->sprite_manager_textures[i] = ztInvalidID;
		}

		char path[ztFileMaxPath];
		zt_fileConcatFileToPath(path, zt_elementsOf(path), zt_game->game_details.data_path, "textures");
		char files[ztFileMaxPath];
		zt_getDirectoryFiles(path, files, zt_elementsOf(files), false);

		ztToken tokens[ZT_SPRITE_ANIM_EDITOR_MAX_ANIMS];
		int tokens_count = zt_min(ZT_SPRITE_ANIM_EDITOR_MAX_ANIMS, zt_strTokenize(files, "\n", tokens, zt_elementsOf(tokens), ztStrTokenizeFlags_TrimWhitespace));

		zt_fiz(tokens_count) {
			char file[ztFileMaxPath];
			zt_strCpy(file, zt_elementsOf(file), files + tokens[i].beg, tokens[i].len);

			if (zt_striEndsWith(file, ".spr")) {
				ztTextureID tex = ztInvalidID;
				zt_fjz(tokens_count) {
					char tex_file[ztFileMaxPath];
					zt_strCpy(tex_file, zt_elementsOf(tex_file), files + tokens[j].beg, tokens[j].len);

					if (j != i && zt_striStartsWith(tex_file, zt_strLen(tex_file), file, zt_strLen(file) - 3)) {
						tex = zt_textureMakeFromFile(tex_file, ztTextureFlags_PixelPerfect);
						zt_fkze(editor->sprite_manager_textures) {
							if (editor->sprite_manager_textures[k] == ztInvalidID) {
								editor->sprite_manager_textures[k] = tex;
								break;
							}
						}
						break;
					}
				}

				ztSerial serial;
				if (zt_serialMakeReader(&serial, file, ZT_SPRITE_FILE_GUID)) {
					zt_spriteManagerLoad(&editor->sprite_manager, &serial, tex);
					zt_serialClose(&serial);
				}
			}
		}
	}

	editor->entries_count = 0;
	editor->active_time = 0;
	editor->active_playing = false;
	editor->work_file[0] = 0;
	editor->active_sequence = -1;

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window = zt_guiMakeWindow(window_name, ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);
	zt_guiItemSetSize(window, zt_cameraOrthoGetViewportSize(gm->gui_camera) - zt_vec2(1, 1.5f));
	zt_guiItemSetUserData(window, editor);

	ztGuiItem *panel = zt_guiMakePanel(window);
	panel->functions.cleanup   = ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdCleanup);
	panel->functions.update    = ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdUpdate);
	panel->functions.user_data = editor;

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Horz);
	zt_guiSizerSizeToParent(sizer);
	zt_guiItemSetName(sizer, "main_panel");


	ztGuiItem *tools_panel = zt_guiMakePanel(sizer, ztGuiPanelBehaviorFlags_DrawBackground | ztGuiItemBehaviorFlags_WantsInput);
	tools_panel->size.x = 5;
	zt_guiSizerAddItem(sizer, tools_panel, 0, padding);

	{
		ztGuiItem *tools_sizer = zt_guiMakeSizer(tools_panel, ztGuiItemOrient_Vert);

		ztGuiItem *tools_sizer_top = zt_guiMakeColumnSizer(tools_sizer, 2, ztGuiColumnSizerType_FillRow);
		zt_guiSizerAddItem(tools_sizer, tools_sizer_top, 0, padding);
		zt_guiColumnSizerSetProp(tools_sizer_top, 0, 0);
		zt_guiColumnSizerSetProp(tools_sizer_top, 1, 1);

		// file name
		ztGuiItem *lbl_file = zt_guiMakeStaticText(tools_sizer_top, "File:");
		zt_guiSizerAddItem(tools_sizer_top, lbl_file, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);

		ztGuiItem *file_sizer = zt_guiMakeSizer(tools_sizer_top, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(tools_sizer_top, file_sizer, 0, 0);
		{
			ztGuiItem *lbl_file_name = zt_guiMakeStaticText(tools_sizer_top, "<file name>");
			zt_guiItemSetAlign(lbl_file_name, ztAlign_Left);
			zt_guiSizerAddItem(file_sizer, lbl_file_name, 1, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			editor->lbl_file = lbl_file_name;

			ztGuiItem *button_new = zt_guiMakeButton(file_sizer, nullptr);
			ztSprite sprite_new = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 750, 42, 21, 21);
			zt_guiButtonSetIcon(button_new, &sprite_new);
			zt_guiButtonSetCallback(button_new, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonFileNew), editor);
			zt_guiItemAutoSize(button_new);
			zt_guiSizerAddItem(file_sizer, button_new, 0, padding);

			ztGuiItem *button_edit = zt_guiMakeButton(file_sizer, nullptr);
			ztSprite sprite_edit = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 709, 43, 21, 21);
			zt_guiButtonSetIcon(button_edit, &sprite_edit);
			zt_guiButtonSetCallback(button_edit, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonFileOpen), editor);
			zt_guiItemAutoSize(button_edit);
			zt_guiSizerAddItem(file_sizer, button_edit, 0, padding);

			ztGuiItem *button_save = zt_guiMakeButton(file_sizer, nullptr);
			ztSprite sprite_save = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 730, 44, 21, 21);
			zt_guiButtonSetIcon(button_save, &sprite_save);
			zt_guiButtonSetCallback(button_save, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonFileSave), editor);
			zt_guiItemAutoSize(button_save);
			zt_guiSizerAddItem(file_sizer, button_save, 0, padding);
		}

		// sequence combo
		ztGuiItem *lbl_combo_seq = zt_guiMakeStaticText(tools_sizer_top, "Sequences:");
		zt_guiSizerAddItem(tools_sizer_top, lbl_combo_seq, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);

		editor->combo_sequences = zt_guiMakeComboBox(tools_sizer_top, ZT_SPRITE_ANIM_EDITOR_MAX_SEQUENCES);
		zt_guiComboBoxAppend(editor->combo_sequences, "[New Sequence]");
		zt_guiComboBoxSetCallback(editor->combo_sequences, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdComboSeq), editor);

		zt_guiSizerAddItem(tools_sizer_top, editor->combo_sequences, 1, padding);

		zt_guiSizerAddStretcher(tools_sizer_top, 0);
		ztGuiItem *seq_sizer = zt_guiMakeSizer(tools_sizer_top, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(tools_sizer_top, seq_sizer, 0, 0, ztAlign_Right, 0);
		{
			ztGuiItem *button_open = zt_guiMakeButton(tools_sizer_top, nullptr);
			ztSprite sprite_open = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 651, 43, 19, 19);
			zt_guiButtonSetIcon(button_open, &sprite_open);
			zt_guiButtonSetCallback(button_open, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonSeqRename), editor);
			zt_guiItemAutoSize(button_open);
			zt_guiSizerAddItem(seq_sizer, button_open, 0, padding);

			ztGuiItem *button_dele = zt_guiMakeButton(tools_sizer_top, nullptr);
			ztSprite sprite_dele = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 633, 43, 19, 19);
			zt_guiButtonSetIcon(button_dele, &sprite_dele);
			zt_guiButtonSetCallback(button_dele, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonSeqDelete), editor);
			zt_guiItemAutoSize(button_dele);
			zt_guiSizerAddItem(seq_sizer, button_dele, 0, padding);
		}

		zt_guiSizerAddStretcher(tools_sizer_top, 0, padding * 2);
		zt_guiSizerAddStretcher(tools_sizer_top, 0, padding * 2);

		// length
		editor->ed_length_val = 1;
		ztGuiItem *lbl_ed_len = zt_guiMakeStaticText(tools_sizer_top, "Length:");
		zt_guiSizerAddItem(tools_sizer_top, lbl_ed_len, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);

		ztGuiItem *len_sizer = zt_guiMakeSizer(tools_sizer_top, ztGuiItemOrient_Horz);
		zt_guiSizerAddItem(tools_sizer_top, len_sizer, 1, padding, ztAlign_Left | ztAlign_VertCenter);
		editor->ed_length = zt_guiMakeEditor(tools_sizer_top, nullptr, &editor->ed_length_val, 0, ztReal32Max, .25f);
		zt_guiSizerAddItem(len_sizer, editor->ed_length, 1, padding, ztAlign_Left | ztAlign_VertCenter);
		zt_guiSizerAddItem(len_sizer, zt_guiMakeStaticText(len_sizer, "seconds"), 0, padding, ztAlign_Left | ztAlign_VertCenter);


		// loops
		editor->chk_loops_val = true;
		ztGuiItem *lbl_loops = zt_guiMakeStaticText(tools_sizer_top, "Loops:");
		editor->chk_loops = zt_guiMakeCheckbox(tools_sizer_top, "", ztGuiCheckboxBehaviorFlags_RightText, &editor->chk_loops_val);

		zt_guiSizerAddItem(tools_sizer_top, lbl_loops, 0, padding, ztAlign_Right | ztAlign_VertCenter, 0);
		zt_guiSizerAddItem(tools_sizer_top, editor->chk_loops, 1, padding);

		// sprite list box
		ztGuiItem *lbl_sprites = zt_guiMakeStaticText(tools_sizer, "Sprites:");

		editor->list_sprites = zt_guiMakeListBox(tools_sizer, 0, ZT_SPRITE_ANIM_EDITOR_MAX_ENTRIES);
		zt_guiSizerAddStretcher(tools_sizer, 0, padding * 2);

		zt_guiSizerAddItem(tools_sizer, lbl_sprites, 0, padding * 2, ztAlign_Left | ztAlign_VertCenter, 0);
		zt_guiSizerAddItem(tools_sizer, editor->list_sprites, 1, padding * 2);

		// play controls
		ztGuiItem *play_panel = zt_guiMakePanel(tools_sizer);
		zt_guiSizerAddItem(tools_sizer, play_panel, 0, padding * 2);
		{
			ztGuiItem *play_sizer = zt_guiMakeSizer(play_panel, ztGuiItemOrient_Horz, false);
			zt_guiSizerSizeParent(play_sizer, false, true);

			ztGuiItem *button_play = zt_guiMakeButton(play_sizer, nullptr);
			ztSprite sprite_play = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 988, 43, 18, 18);
			zt_guiButtonSetIcon(button_play, &sprite_play);
			zt_guiItemAutoSize(button_play);
			zt_guiButtonSetCallback(button_play, ZT_FUNCTION_POINTER_TO_VAR(_zt_debugSpriteAnimEdButtonPlay), editor);
			button_play->size.x *= 2;
			editor->button_play = button_play;

			zt_guiSizerAddItem(play_sizer, button_play, 0, padding);
		}

	}

	ztGuiItem *display_panel = zt_guiMakePanel(sizer, ztGuiPanelBehaviorFlags_DrawBackground);
	zt_guiSizerAddItem(sizer, display_panel, 1, padding);
	{
		ztGuiItem *display_sizer = zt_guiMakeSizer(display_panel, ztGuiItemOrient_Vert);

		ztGuiItem *sprite_display = zt_guiMakeSpriteDisplay(display_sizer, (ztGuiThemeSprite*)nullptr);
		editor->sprite_display = sprite_display;
		editor->sprite_display_info = zt_guiMakeStaticText(display_sizer, "                                                                        ", 0, 256);

		zt_guiSizerAddItem(display_sizer, sprite_display, 1, padding, ztAlign_Center | ztAlign_VertCenter, 0);
		zt_guiSizerAddItem(display_sizer, editor->sprite_display_info, 0, padding, ztAlign_Center | ztAlign_VertCenter, 0);
	}
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

struct ztParticleEditor
{
	ztGuiItem                *window;

	ztParticleSystem          particle_system;
	ztParticleEmitter        *particle_emitter;
	ztParticleSystem          display_particle_system;
	r32                       display_reset_time;
	ztParticleSystem          display_reset_particle_system;

	ztTextureID               render_tex;
	ztCamera                  camera;
	ztCameraControllerArcball camera_controller;
	ztDrawList                draw_list;

	r32                       time;
	r32                       overall_time;

	ztInputMouse              input_mouse;
	ztInputKeys               input_keys[ztInputKeys_MAX];

	ztSpriteManager           sprite_manager;

	ztGuiItem                *billboard_sprite_button;
	ztGuiItem                *trail_sprite_button;

	i32                       billboard_sprite_hash;
	i32                       trail_sprite_hash;

	ztGuiItem                *shape_options_sphere;
	ztGuiItem                *shape_options_circle;
	ztGuiItem                *shape_options_box;
	ztGuiItem                *shape_options_square;

	ztGuiItem                *combo_shape_type;
	ztGuiItem                *combo_rendering_type;
	ztGuiItem                *combo_rendering_blend_src;
	ztGuiItem                *combo_rendering_blend_dst;

	bool                      draw_floor_grid;
	bool                      draw_axis;
	bool                      draw_guides;
	ztColor                   background_color;
	bool                      draw_2d;
	bool                      move_emitter;
	bool                      paused;

	char                      work_file[ztFileMaxPath];
	bool                      should_save;
	bool                      has_changed;
	bool                      ignore_diff;
};

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiParticleEditorUpdate))
{
	//ztParticleEditor *editor = (ztParticleEditor*)user_data;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorDisplayRender, ZT_FUNC_GUI_ITEM_RENDER(_zt_guiParticleEditorDisplayRender))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	zt_drawListPushBlendMode(draw_list, ztRendererBlendMode_One, ztRendererBlendMode_Zero);
	ztSprite sprite = zt_spriteMake(editor->render_tex, 0, 0, 2048, 2048);
	zt_drawListAddSprite(draw_list, &sprite, zt_vec3(item->pos + offset, 0));
	zt_drawListPopBlendMode(draw_list);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorDisplayUpdate, ZT_FUNC_GUI_ITEM_UPDATE(_zt_guiParticleEditorDisplayUpdate))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;

	const char *work_file = "untitled";
	if (editor->work_file[0] != 0) {
		int pos_path_sep = zt_strFindLastPos(editor->work_file, ztFilePathSeparatorStr);
		work_file = editor->work_file + pos_path_sep + 1;
	}

	zt_strMakePrintf(window_title, 512, "Particle System Editor - %s%s", work_file, editor->has_changed ? "*" : "");
	zt_guiItemSetLabel(zt_guiItemGetTopLevelParent(editor->billboard_sprite_button), window_title);

	zt_cameraControlUpdateArcball(&editor->camera_controller, &editor->input_mouse, editor->input_keys, dt);

	zt_drawListPushShader(&editor->draw_list, zt_shaderGetDefault(ztShaderDefault_Unlit));
	zt_drawListPushTexture(&editor->draw_list, ztTextureDefault);

	if (editor->draw_floor_grid) {
		zt_drawListPushColor(&editor->draw_list, zt_vec4(1, 1, 1, .5f));
		zt_drawListAddFloorGrid(&editor->draw_list, zt_vec3(0, -.001f, 0), 10, 10);
		zt_drawListPopColor(&editor->draw_list);
	}

	if (editor->draw_axis) {
		zt_drawListAddAxis(&editor->draw_list);
	}

	if (zt_memCmp(&editor->particle_system, &editor->display_reset_particle_system, zt_sizeof(ztParticleSystem))) {
		zt_memCpy(&editor->display_reset_particle_system, zt_sizeof(ztParticleSystem), &editor->particle_system, zt_sizeof(ztParticleSystem));
		editor->display_reset_time = editor->particle_emitter != nullptr && editor->particle_emitter->system == nullptr ? dt * .5f : .5f;
	}

	if (editor->display_reset_time > 0) {
		editor->display_reset_time -= dt;
		if (editor->display_reset_time < 0) {
			zt_particleEmitterFree(editor->particle_emitter);
			zt_memCpy(&editor->display_particle_system, zt_sizeof(ztParticleSystem), &editor->particle_system, zt_sizeof(ztParticleSystem));
			editor->particle_emitter = zt_particleEmitterInit(&editor->display_particle_system, zt_game->game_details.current_frame * 10000);

			r32 dt_each = 1 / 30.f;
			r32 time = editor->time;
			while (time > 0) {
				zt_particleEmitterUpdate(editor->particle_emitter, dt_each);
				time -= dt_each;
			}

			if (!editor->ignore_diff) {
				editor->has_changed = true;
			}
			else {
				editor->ignore_diff = false;
			}
		}
	}

	if (!editor->paused) {
		editor->time += dt;
		editor->overall_time += dt;

		if(editor->particle_emitter != nullptr) {
			zt_particleEmitterUpdate(editor->particle_emitter, dt);

			if (editor->display_particle_system.system_duration > 0) {
				if (editor->particle_emitter->enabled == false) {
					editor->time = 0;
					zt_particleEmitterFree(editor->particle_emitter);
					editor->particle_emitter = zt_particleEmitterInit(&editor->display_particle_system, zt_game->game_details.current_frame * 10000);
				}
				if (editor->display_particle_system.system_loops) {
					if (editor->time > editor->display_particle_system.system_duration) {
						editor->time -= editor->display_particle_system.system_duration;
					}
				}
			}
			else if (editor->time > 10) {
				editor->time = 0;
			}
		}
	}

	if(editor->particle_emitter != nullptr) {
		if (editor->draw_guides) {
			r32 emitter_life_pct = editor->display_particle_system.system_duration <= 0 ? 0 : 1 - (zt_max(0, editor->particle_emitter->life_left) / editor->display_particle_system.system_duration);

			ztVec3 system_rotation_euler = zt_particleVariableVec3GetValue(&editor->particle_emitter->system_rotation, emitter_life_pct);
			if (system_rotation_euler != ztVec3::zero) {
				zt_drawListPushTransform(&editor->draw_list, ztQuat::makeFromEuler(system_rotation_euler).convertToMat4());
			}

			switch (editor->display_particle_system.system_shape.type)
			{
				case ztParticleShapeType_Sphere: {
					r32 radius = zt_particleVariableRealGetValue(&editor->particle_emitter->system_shape_sphere.radius, emitter_life_pct);
					zt_drawListAddEmptySimpleSphere(&editor->draw_list, ztVec3::zero, radius, zt_max(16, zt_convertToi32Floor(16 * radius)));
				} break;

				case ztParticleShapeType_Circle: {
					r32 radius = zt_particleVariableRealGetValue(&editor->particle_emitter->system_shape_circle.radius, emitter_life_pct);
					zt_drawListAddEmptyCircle(&editor->draw_list, ztVec3::zero, radius, zt_max(16, zt_convertToi32Floor(16 * radius)));
				} break;

				case ztParticleShapeType_Box: {
					ztVec3 extents = zt_particleVariableVec3GetValue(&editor->particle_emitter->system_shape_box.extents, emitter_life_pct);
					zt_drawListAddEmptyCubeFromCenterSize(&editor->draw_list, ztVec3::zero, extents);
				} break;

				case ztParticleShapeType_Square: {
					ztVec2 extents = zt_particleVariableVec2GetValue(&editor->particle_emitter->system_shape_square.extents, emitter_life_pct);
					zt_drawListAddEmptyRect(&editor->draw_list, ztVec3::zero, extents);
				} break;
			}

			if (system_rotation_euler != ztVec3::zero) {
				zt_drawListPopTransform(&editor->draw_list);
			}
		}

		if (!editor->move_emitter) {
			editor->particle_emitter->position = ztVec3::zero;
		}
		else {
			editor->particle_emitter->position = zt_vec3(zt_sin(editor->overall_time) * 4, zt_cos(editor->overall_time) * 4, 0);
		}

		if(editor->draw_2d && editor->camera.type != ztCameraType_Orthographic) {
			ztVec2i tex_size = zt_textureGetSize(editor->render_tex);
			zt_cameraMakeOrtho(&editor->camera, tex_size.x, tex_size.y, tex_size.x, tex_size.y, 0.001f, 100.f);
		}
		else if(editor->draw_2d == false && editor->camera.type != ztCameraType_Perspective) {
			ztVec2i tex_size = zt_textureGetSize(editor->render_tex);
			zt_cameraMakePersp(&editor->camera, tex_size.x, tex_size.y, 90.f, 0.001f, 1000.f, zt_vec3(0, 3, 3));
			editor->camera_controller = zt_cameraControllerMakeArcball(&editor->camera, ztVec3::zero);
		}

		zt_particleEmitterRender(editor->particle_emitter, &editor->draw_list, &editor->camera);
	}

	zt_drawListPopTexture(&editor->draw_list);
	zt_drawListPopShader(&editor->draw_list);

	zt_renderDrawList(&editor->camera, &editor->draw_list, editor->background_color, editor->draw_2d ? ztRenderDrawListFlags_NoDepthTest : 0, editor->render_tex);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorDisplayInputMouse, ZT_FUNC_GUI_ITEM_INPUT_MOUSE(_zt_guiParticleEditorDisplayInputMouse))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	zt_memCpy(&editor->input_mouse, zt_sizeof(ztInputMouse), input_mouse, zt_sizeof(ztInputMouse));


	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorDisplayInputKeyboard, ZT_FUNC_GUI_ITEM_INPUT_KEY(_zt_guiParticleEditorDisplayInputKeyboard))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	zt_memCpy(editor->input_keys, zt_sizeof(ztInputKeys) * zt_elementsOf(editor->input_keys), input_keys, zt_sizeof(ztInputKeys) * zt_elementsOf(editor->input_keys));
	return true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorDisplayCleanup, ZT_FUNC_GUI_ITEM_CLEANUP(_zt_guiParticleEditorDisplayCleanup))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	zt_particleEmitterFree(editor->particle_emitter);
	zt_textureFree(editor->render_tex);
	zt_drawListFree(&editor->draw_list);
	zt_spriteManagerFree(&editor->sprite_manager, true);
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiParticleEditorShapeTypeHideEditors(ztParticleEditor *editor, ztParticleShapeType_Enum except_for)
{
	zt_guiItemShow(editor->shape_options_sphere, except_for == ztParticleShapeType_Sphere);
	zt_guiItemShow(editor->shape_options_circle, except_for == ztParticleShapeType_Circle);
	zt_guiItemShow(editor->shape_options_box, except_for == ztParticleShapeType_Box);
	zt_guiItemShow(editor->shape_options_square, except_for == ztParticleShapeType_Square);

	zt_guiSizerRecalc(zt_guiItemGetTopLevelParent(editor->shape_options_sphere));
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorShapeTypeCombo, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiParticleEditorShapeTypeCombo))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	_zt_guiParticleEditorShapeTypeHideEditors(editor, (ztParticleShapeType_Enum)selected);

	editor->particle_system.system_shape.type = (ztParticleShapeType_Enum)selected;

	switch (selected)
	{
		case ztParticleShapeType_Point: {
			// ...
		} break;

		case ztParticleShapeType_Sphere: {
			editor->particle_system.system_shape.sphere.radius.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.sphere.radius.constant = 1;
			editor->particle_system.system_shape.sphere.volume_angle_min.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.sphere.volume_angle_min.constant = 0;
			editor->particle_system.system_shape.sphere.volume_angle_max.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.sphere.volume_angle_max.constant = 360;
		} break;

		case ztParticleShapeType_Circle: {
			editor->particle_system.system_shape.circle.radius.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.circle.radius.constant = 1;
			editor->particle_system.system_shape.circle.volume_angle_min.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.circle.volume_angle_min.constant = 0;
			editor->particle_system.system_shape.circle.volume_angle_max.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.circle.volume_angle_max.constant = 360;
		} break;

		case ztParticleShapeType_Box: {
			editor->particle_system.system_shape.box.extents.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.box.extents.constant = zt_vec3(1, 1, 1);
		} break;

		case ztParticleShapeType_Square: {
			editor->particle_system.system_shape.square.extents.type = ztParticleVariableRealType_Constant;
			editor->particle_system.system_shape.square.extents.constant = zt_vec2(1, 1);
		} break;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorTrailSpriteSelected, ZT_FUNC_GUI_DIALOG_SPRITE_SELECTED(_zt_guiParticleEditorTrailSpriteSelected))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	if (!cancelled) {
		ztSprite *sprite = zt_spriteManagerGetSprite(&editor->sprite_manager, sprite_name_hash);
		if (sprite) {
			zt_guiButtonSetIcon(editor->trail_sprite_button, sprite);
			zt_guiItemSetLabel(editor->trail_sprite_button, nullptr);

			editor->particle_system.trails_sprite = *sprite;
			zt_guiSizerRecalc(editor->window);
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorTrailSpriteSelectButton, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiParticleEditorTrailSpriteSelectButton))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	zt_guiDialogSpriteSelector(&editor->sprite_manager, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorTrailSpriteSelected), editor, "Select Sprite");
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorBillboardSpriteSelected, ZT_FUNC_GUI_DIALOG_SPRITE_SELECTED(_zt_guiParticleEditorBillboardSpriteSelected))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	if (!cancelled) {
		ztSprite *sprite = zt_spriteManagerGetSprite(&editor->sprite_manager, sprite_name_hash);
		if (sprite) {
			zt_guiButtonSetIcon(editor->billboard_sprite_button, sprite);
			zt_guiItemSetLabel(editor->billboard_sprite_button, nullptr);

			editor->particle_system.system_rendering.billboard.sprite = *sprite;
			editor->particle_system.system_rendering.facing.sprite = *sprite;
			zt_guiSizerRecalc(editor->window);
		}
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorBillboardSpriteSelectButton, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiParticleEditorBillboardSpriteSelectButton))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;
	zt_guiDialogSpriteSelector(&editor->sprite_manager, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorBillboardSpriteSelected), editor, "Select Sprite");
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorRenderingTypeCombo, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiParticleEditorRenderingTypeCombo))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;

	editor->particle_system.system_rendering.type = (ztParticleRenderingType_Enum)selected;

	switch (selected)
	{
		case ztParticleRenderingType_BillBoard: {
		} break;

		case ztParticleRenderingType_Facing: {
		} break;
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorRenderingBlendCombo, ZT_FUNC_GUI_COMBOBOX_ITEM_SELECTED(_zt_guiParticleEditorRenderingBlendCombo))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;

	if (combobox == editor->combo_rendering_blend_src) {
		editor->particle_system.system_rendering.blend_mode_src = (ztRendererBlendMode_Enum)selected;
	}
	else if (combobox == editor->combo_rendering_blend_dst) {
		editor->particle_system.system_rendering.blend_mode_dst = (ztRendererBlendMode_Enum)selected;
	}
}

// ================================================================================================================================================================================================

ztInternal void _zt_guiParticleEditorSave(ztParticleEditor *editor)
{
	const char *error = nullptr;

	ztSerial serial;
	if (zt_serialMakeWriter(&serial, editor->work_file, ZT_PARTICLE_SYSTEM_FILE_GUID, ZT_SPRITE_ANIM_FILE_VERSION)) {
		if (!zt_serialWrite(&serial, &editor->particle_system, &editor->sprite_manager)) {
			error = "Unable to serialize particle system";
		}
		zt_serialClose(&serial);
	}
	else {
		error = "Unable to write to file.";
	}

	if (error != nullptr) {
		char message[ztFileMaxPath];
		zt_strPrintf(message, zt_elementsOf(message), "%s\n\n%s", error, editor->work_file);
		zt_guiDialogMessageBoxOk("Error Saving File", message, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
	}
	else {
		char message[ztFileMaxPath];
		zt_strPrintf(message, zt_elementsOf(message), "File saved.\n\n%s", editor->work_file);
		zt_guiDialogMessageBoxOk("File Successfully Saved", message, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
	}
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorButtonFileSave, ZT_FUNC_GUI_BUTTON_PRESSED(_zt_guiParticleEditorButtonFileSave))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;

	char path[ztFileMaxPath] = { 0 };
	zt_fileGetFullPath(editor->work_file, path, zt_elementsOf(path));
	if (!zt_directoryExists(path)) {
		zt_guiDialogMessageBoxOk("Invalid File Name", "Select a valid file name", ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	_zt_guiParticleEditorSave(editor);
}

// ================================================================================================================================================================================================

enum ztParticleEditorMenu_Enum
{
	ztParticleEditorMenu_New,
	ztParticleEditorMenu_Open,
	ztParticleEditorMenu_Save,
};

// ================================================================================================================================================================================================

ztInternal void _zt_guiParticleEditorUpdateGui(ztParticleEditor *editor, ztParticleSystem *particle_system)
{
	zt_guiComboBoxSetSelected(editor->combo_shape_type, particle_system->system_shape.type);
	_zt_guiParticleEditorShapeTypeCombo(editor->combo_shape_type, particle_system->system_shape.type, editor);

	zt_guiComboBoxSetSelected(editor->combo_rendering_type, particle_system->system_rendering.type);
	_zt_guiParticleEditorRenderingTypeCombo(editor->combo_rendering_type, particle_system->system_rendering.type, editor);

	zt_guiComboBoxSetSelected(editor->combo_rendering_blend_src, particle_system->system_rendering.blend_mode_src);
	_zt_guiParticleEditorRenderingBlendCombo(editor->combo_rendering_blend_src, particle_system->system_rendering.blend_mode_src, editor);
	zt_guiComboBoxSetSelected(editor->combo_rendering_blend_dst, particle_system->system_rendering.blend_mode_dst);
	_zt_guiParticleEditorRenderingBlendCombo(editor->combo_rendering_blend_dst, particle_system->system_rendering.blend_mode_dst, editor);
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorButtonFileDialogCallback, ZT_FUNC_GUI_DIALOG_FILE_SELECTED(_zt_guiParticleEditorButtonFileDialogCallback))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;

	if (editor->should_save && zt_fileExists(path)) {
		zt_guiDialogMessageBoxOk("File Already Exists", "This file already exists.\n\nPlease choose a new file.", ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
		return;
	}

	zt_strCpy(editor->work_file, zt_elementsOf(editor->work_file), path);

	if (editor->should_save) {
		_zt_guiParticleEditorSave(editor);
		editor->should_save = false;
	}
	else {
		ztSerial serial;

		const char *error = nullptr;

		ztParticleSystem particle_system;
		if (zt_serialMakeReader(&serial, editor->work_file, ZT_PARTICLE_SYSTEM_FILE_GUID)) {
			if (!zt_serialRead(&serial, &particle_system, &editor->sprite_manager)) {
				error = "Unable to serialize particle system";
			}
			zt_serialClose(&serial);
		}
		else {
			error = "Unable to read from file.";
		}

		if (error != nullptr) {
			zt_guiDialogMessageBoxOk("Unable to Load Particle System File", error, ZT_FUNCTION_POINTER_TO_VAR_NULL, nullptr);
			return;
		}
		else {
			_zt_guiParticleEditorUpdateGui(editor, &particle_system);
			zt_memCpy(&editor->particle_system, zt_sizeof(ztParticleSystem), &particle_system, zt_sizeof(ztParticleSystem));
		}
	}

	editor->has_changed = false;
	editor->ignore_diff = true;
}

// ================================================================================================================================================================================================

ZT_FUNCTION_POINTER_REGISTER(_zt_guiParticleEditorMenu, ZT_FUNC_GUI_MENU_SELECTED(_zt_guiParticleEditorMenu))
{
	ztParticleEditor *editor = (ztParticleEditor*)user_data;

	char path[ztFileMaxPath];
	char *path_to_send = path;

	zt_fileConcatFileToPath(path, ztFileMaxPath, zt_game->game_details.data_path, "textures");
	if (!zt_directoryExists(path)) {
		path_to_send = nullptr;
	}

	switch (menu_item)
	{
		case ztParticleEditorMenu_New: {
			editor->work_file[0] = 0;

			zt_memSet(&editor->particle_system, zt_sizeof(ztParticleSystem), 0);

			editor->particle_system.system_duration = 0;
			editor->particle_system.system_loops = true;
			editor->particle_system.system_prewarm = 0;
			editor->particle_system.system_local_space = true;
			editor->particle_system.start_speed.constant = 1.f;
			editor->particle_system.system_rate_over_time.constant = 20;
			editor->particle_system.lifetime.constant = 3;
			editor->particle_system.start_scale.constant = ztVec3::one;

			ztSprite sprite = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 815, 1, 33, 33);
			editor->particle_system.system_rendering.type = ztParticleRenderingType_BillBoard;
			editor->particle_system.system_rendering.billboard.sprite = sprite;
			editor->particle_system.system_rendering.facing.sprite = sprite;
			editor->particle_system.system_rendering.blend_mode_src = ztRendererBlendMode_SourceAlpha;
			editor->particle_system.system_rendering.blend_mode_dst = ztRendererBlendMode_OneMinusSourceAlpha;

			ztSprite sprite_trail = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 948, 2, 12, 12);
			editor->particle_system.trails_sprite = sprite_trail;

			_zt_guiParticleEditorUpdateGui(editor, &editor->particle_system);
			zt_guiButtonSetIcon(editor->billboard_sprite_button, nullptr);
			zt_guiItemSetLabel(editor->billboard_sprite_button, "Select Sprite");
			zt_guiButtonSetIcon(editor->trail_sprite_button, nullptr);
			zt_guiItemSetLabel(editor->trail_sprite_button, "Select Sprite");
		} break;

		case ztParticleEditorMenu_Open: {
			editor->should_save = false;
			zt_guiDialogFileSelect("Choose Particle System File", ztGuiDialogFileSelectFlags_Open, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorButtonFileDialogCallback), editor, path_to_send);
		} break;

		case ztParticleEditorMenu_Save: {
			if (editor->work_file[0] == 0) {
				editor->should_save = true;
				zt_guiDialogFileSelect("Save As", ztGuiDialogFileSelectFlags_Save, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorButtonFileDialogCallback), editor, path_to_send);
			}
			else {
				_zt_guiParticleEditorSave(editor);
			}

			editor->has_changed = false;
		} break;
	}
}

// ================================================================================================================================================================================================

void _zt_guiParticleEditor()
{
	const char *window_name = "Particle System Editor";

	{
		ztGuiItem *window = zt_guiItemFindByName(window_name);
		if (window != nullptr) {
			zt_guiItemShow(window, true);
			zt_guiItemBringToFront(window);
			return;
		}
	}

	ztGuiManager *gm = zt_gui->gui_manager_active;
	ztParticleEditor *editor = zt_mallocStructArena(ztParticleEditor, gm->arena);

	r32 padding = 3 / zt_pixelsPerUnit();

	ztGuiItem *window = zt_guiMakeWindow(window_name, ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);
	zt_guiItemSetSize(window, zt_cameraOrthoGetViewportSize(gm->gui_camera) - zt_vec2(1, 1.5f));
	zt_guiItemSetUserData(window, editor);

	ztGuiItem *menu_bar = zt_guiMakeMenuBar(window);

	ztGuiItem *menu_file = zt_guiMakeMenu(menu_bar);
	ztSprite sprite_new = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 750, 42, 21, 21);
	ztSprite sprite_open = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 709, 43, 21, 21);
	ztSprite sprite_save = zt_spriteMake(zt_game->fonts[ztFontDefault].texture, 730, 44, 21, 21);
	zt_guiMenuAppend(menu_file, "New Particle System", ztParticleEditorMenu_New, editor, &sprite_new);
	zt_guiMenuAppend(menu_file, "Open Particle System", ztParticleEditorMenu_Open, editor, &sprite_open);
	zt_guiMenuAppend(menu_file, "Save Particle System", ztParticleEditorMenu_Save, editor, &sprite_save);
	zt_guiMenuSetCallback(menu_file, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorMenu));
	zt_guiMenuAppendSubmenu(menu_bar, "File", menu_file);

	zt_guiWindowSetMenuBar(window, menu_bar);

	ztGuiItem *panel = zt_guiMakePanel(window, 0, editor, gm->arena);
	panel->functions.update = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorUpdate);
	panel->functions.user_data = editor;

	ztGuiItem *sizer = zt_guiMakeSizer(zt_guiWindowGetContentParent(window), ztGuiItemOrient_Vert);

	ztGuiItem *splitter = zt_guiMakeSplitter(sizer, ztGuiItemOrient_Horz, .35f);
	zt_guiSizerAddItem(sizer, splitter, 1, 0);

	ztGuiItem *panel_tools = zt_guiMakeScrollContainer(splitter, ztGuiScrollContainerBehaviorFlags_StretchHorz);
	ztGuiItem *panel_preview = zt_guiMakePanel(splitter, ztGuiPanelBehaviorFlags_DrawBackground | ztGuiItemBehaviorFlags_ClipContents | ztGuiItemBehaviorFlags_LateUpdate);

	panel_preview->functions.render      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorDisplayRender);
	panel_preview->functions.update      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorDisplayUpdate);
	panel_preview->functions.input_mouse = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorDisplayInputMouse);
	panel_preview->functions.input_key   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorDisplayInputKeyboard);
	panel_preview->functions.cleanup     = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorDisplayCleanup);
	panel_preview->functions.user_data   = editor;

	editor->background_color = ztColor_DarkGray;
	editor->draw_floor_grid = true;
	editor->draw_axis = true;
	editor->draw_guides = true;
	editor->paused = false;
	editor->move_emitter = false;
	editor->overall_time = 0;

	{
		ztGuiItem *preview_sizer = zt_guiMakeSizer(panel_preview, ztGuiItemOrient_Vert);

		ztGuiItem *controls_panel = zt_guiMakePanel(preview_sizer, ztGuiPanelBehaviorFlags_DrawBackground);
		zt_guiSizerAddStretcher(preview_sizer, 1);
		zt_guiSizerAddItem(preview_sizer, controls_panel, 0, padding);

		ztGuiItem *controls_sizer = zt_guiMakeSizer(controls_panel, ztGuiItemOrient_Horz, false);
		zt_guiSizerSizeParent(controls_sizer);

		zt_guiSizerAddStretcher(controls_sizer, 1, 0);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeToggleButton(controls_sizer, "Pause", 0, &editor->paused), 0, padding);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeStaticText(controls_sizer, "Background:"), 0, padding);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeColorPicker(controls_sizer, editor->background_color, ztGuiColorPickerBehaviorFlags_LiveEdit, &editor->background_color), 0, padding);

		zt_guiSizerAddItem(controls_sizer, zt_guiMakeCheckbox(controls_sizer, "Draw Floor Grid:", 0, &editor->draw_floor_grid), 0, padding);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeCheckbox(controls_sizer, "Draw Axis:", 0, &editor->draw_axis), 0, padding);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeCheckbox(controls_sizer, "Draw Guides:", 0, &editor->draw_guides), 0, padding);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeCheckbox(controls_sizer, "Draw 2D:", 0, &editor->draw_2d), 0, padding);
		zt_guiSizerAddItem(controls_sizer, zt_guiMakeCheckbox(controls_sizer, "Move Emitter:", 0, &editor->move_emitter), 0, padding);

		//zt_guiSizerAddStretcher(controls_sizer, 1, 0);
	}

	editor->window = window;
	editor->display_reset_time = 0;

	zt_drawListMake(&editor->draw_list, 1024 * 512);
	editor->render_tex = zt_textureMakeRenderTarget(2048, 2048);

	zt_spriteManagerMake(&editor->sprite_manager, 512);
	zt_spriteManagerLoadAll(&editor->sprite_manager);


	zt_cameraMakePersp(&editor->camera, 2048, 2048, 90, .01f, 1000.f, zt_vec3(0, 5, 5));
	editor->camera_controller = zt_cameraControllerMakeArcball(&editor->camera);

	zt_guiSplitterSetItems(splitter, panel_tools, panel_preview);
	zt_guiSplitterSetFirstSize(splitter, 8);

#	define ztEdLabelWidth	2.5f

	struct local
	{
		static ztGuiItem *makePanelSizer(ztGuiItem *sizer_parent, const char *label, r32 padding, bool collapsed = false)
		{
			ztGuiItem *collapsing_panel = zt_guiMakeCollapsingPanel(sizer_parent, label);
			zt_guiItemSetName(collapsing_panel, label);
			zt_guiSizerAddItem(sizer_parent, collapsing_panel, 0, padding);

			ztGuiItem *panel = zt_guiCollapsingPanelGetContentParent(collapsing_panel);

			ztGuiItem *sizer_panel = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert, true);
			zt_guiSizerSizeParent(sizer_panel, false, true);
			zt_guiSizerSizeToParent(sizer_panel);

			ztGuiItem *sizer = zt_guiMakeColumnSizer(sizer_panel, 2, ztGuiColumnSizerType_FillRow, false);
			zt_guiSizerAddItem(sizer_panel, sizer, 0, padding);

			zt_guiItemSetName(sizer, label);
			zt_guiColumnSizerSetProp(sizer, 1, 1);

			if (collapsed) {
				zt_guiCollapsingPanelCollapse(collapsing_panel);
			}

			return sizer;
		}

		static ztGuiItem  *makeLabel(ztGuiItem *sizer, const char *label, r32 padding)
		{
			ztGuiItem *lbl = zt_guiMakeStaticText(sizer, label);
			lbl->size.x = ztEdLabelWidth;
			lbl->align_flags = ztAlign_Left;
			zt_guiSizerAddItem(sizer, lbl, 0, padding, ztAlign_Left | ztAlign_VertCenter, 0);
			return lbl;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, r32 *value, r32 step = .1f, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *editor = zt_guiMakeEditor(sizer, nullptr, value, 0, 999, step);
			zt_guiSizerAddItem(sizer, editor, 1, padding);
			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, i32 *value, i32 step = 1, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *editor = zt_guiMakeEditor(sizer, nullptr, value, 0, 999, step);
			zt_guiSizerAddItem(sizer, editor, 1, padding);
			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, bool *value, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *check = zt_guiMakeCheckbox(sizer, " ", ztGuiCheckboxBehaviorFlags_RightText, value);
			zt_guiSizerAddItem(sizer, check, 1, padding);
			check->size.y = zt_guiThemeGetRValue(zt_guiItemGetTheme(check), ztGuiThemeValue_r32_TextEditDefaultH, check);
			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = check;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, ztParticleVariableReal *var_real, r32 step = .1f, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *editor = zt_guiMakeEditor(sizer, var_real, 0, 0, 999, step);
			zt_guiSizerAddItem(sizer, editor, 1, padding);
			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, ztParticleVariableVec2 *var_vec2, bool allow_sync, r32 step = .1f, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *editor = zt_guiMakeEditor(sizer, var_vec2, ztVec2::zero, zt_vec2(-999, -999), zt_vec2(999, 999), step, allow_sync);
			zt_guiSizerAddItem(sizer, editor, 1, padding);

			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, ztParticleVariableVec3 *var_vec3, bool allow_sync, r32 step = .1f, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *editor = zt_guiMakeEditor(sizer, var_vec3, ztVec3::zero, zt_vec3(-999, -999, -999), zt_vec3(999, 999, 999), step, allow_sync);
			zt_guiSizerAddItem(sizer, editor, 1, padding);

			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, bool *using_var, ztParticleVariableVec3 *var_vec3, bool allow_sync, r32 step = .1f, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);

			ztGuiItem *editor_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(sizer, editor_sizer, 1, 0);

			ztGuiItem *check = zt_guiMakeCheckbox(editor_sizer, nullptr, ztGuiCheckboxBehaviorFlags_RightText, using_var);
			zt_guiSizerAddItem(editor_sizer, check, 0, padding, ztAlign_VertCenter, 0);

			ztGuiItem *editor = zt_guiMakeEditor(editor_sizer, var_vec3, ztVec3::zero, zt_vec3(-999, -999, -999), zt_vec3(999, 999, 999), step, allow_sync);
			zt_guiSizerAddItem(editor_sizer, editor, 1, 0);

			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, bool *using_var, ztParticleVariableReal *var_real, bool allow_sync, r32 step = .1f, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);

			ztGuiItem *editor_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(sizer, editor_sizer, 1, 0);

			ztGuiItem *check = zt_guiMakeCheckbox(editor_sizer, nullptr, ztGuiCheckboxBehaviorFlags_RightText, using_var);
			zt_guiSizerAddItem(editor_sizer, check, 0, padding, ztAlign_VertCenter, 0);

			ztGuiItem *editor = zt_guiMakeEditor(editor_sizer, var_real, 0, -999, 999, step);
			zt_guiSizerAddItem(editor_sizer, editor, 1, 0);

			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, ztParticleVariableColor *var_color, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);
			ztGuiItem *editor = zt_guiMakeEditor(sizer, var_color);
			zt_guiSizerAddItem(sizer, editor, 1, padding);

			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, bool *using_var, ztParticleVariableColor *var_color, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);

			ztGuiItem *editor_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(sizer, editor_sizer, 1, 0);

			ztGuiItem *check = zt_guiMakeCheckbox(editor_sizer, nullptr, ztGuiCheckboxBehaviorFlags_RightText, using_var);
			zt_guiSizerAddItem(editor_sizer, check, 0, padding, ztAlign_VertCenter, 0);

			ztGuiItem *editor = zt_guiMakeEditor(editor_sizer, var_color);
			zt_guiSizerAddItem(editor_sizer, editor, 1, padding);

			if (label_item) *label_item = lbl;
			if (editor_item) *editor_item = editor;
		}

		static void makeEditor(ztGuiItem *sizer, const char *label, r32 padding, r32* val_one, r32 *val_two, r32 step, ztGuiItem **label_item = nullptr, ztGuiItem **editor_item_1 = nullptr, ztGuiItem **editor_item_2 = nullptr)
		{
			ztGuiItem *lbl = makeLabel(sizer, label, padding);

			ztGuiItem *editor_sizer = zt_guiMakeSizer(sizer, ztGuiItemOrient_Horz);
			zt_guiSizerAddItem(sizer, editor_sizer, 1, 0);

			ztGuiItem *editor_one = zt_guiMakeEditor(editor_sizer, nullptr, val_one, 0, 999, step);
			ztGuiItem *editor_two = zt_guiMakeEditor(editor_sizer, nullptr, val_two, 0, 999, step);

			zt_guiSizerAddItem(editor_sizer, editor_one, 1, 0);
			zt_guiSizerAddStretcher(editor_sizer, 0, padding * 2);
			zt_guiSizerAddItem(editor_sizer, editor_two, 1, 0);

			if (label_item) *label_item = lbl;
			if (editor_item_1) *editor_item_1 = editor_one;
			if (editor_item_2) *editor_item_2 = editor_two;
		}
	};

#	undef ztEdLabelWidth

	{
		ztGuiItem *panel = zt_guiMakePanel(panel_tools);
		zt_guiItemSetName(panel, "panel_tools");
		zt_guiScrollContainerSetItem(panel_tools, panel);

		ztGuiItem *sizer_tools = zt_guiMakeSizer(panel, ztGuiItemOrient_Vert, false);
		zt_guiSizerSizeParent(sizer_tools, false, true);
		zt_guiSizerSizeToParent(sizer_tools);
		zt_guiItemSetName(sizer_tools, "sizer_tools");

		ztGuiItem *system_panel = local::makePanelSizer(sizer_tools, "System", padding);
		{
			local::makeEditor(system_panel, "Duration:", padding, &editor->particle_system.system_duration);
			local::makeEditor(system_panel, "Delay:", padding, &editor->particle_system.system_delay);
			local::makeEditor(system_panel, "Loops:", padding, &editor->particle_system.system_loops);
			local::makeEditor(system_panel, "Pre-Warm:", padding, &editor->particle_system.system_prewarm);
			local::makeEditor(system_panel, "Gravity Multiplier:", padding, &editor->particle_system.system_gravity_multiplier);
		}

		ztGuiItem *emission_panel = local::makePanelSizer(sizer_tools, "Emission", padding);
		{
			local::makeEditor(emission_panel, "Local Space:", padding, &editor->particle_system.system_local_space);
			local::makeEditor(emission_panel, "Rate Over Time:", padding, &editor->particle_system.system_rate_over_time);

			local::makeLabel(emission_panel, "Shape", padding);
			ztGuiItem *shape_combo = zt_guiMakeComboBox(emission_panel, ztParticleShapeType_MAX);
			editor->combo_shape_type = shape_combo;
			zt_guiSizerAddItem(emission_panel, shape_combo, 1, padding);

			zt_guiComboBoxAppend(shape_combo, "Point");
			zt_guiComboBoxAppend(shape_combo, "Sphere");
			zt_guiComboBoxAppend(shape_combo, "Circle");
			zt_guiComboBoxAppend(shape_combo, "Box");
			zt_guiComboBoxAppend(shape_combo, "Square");

			zt_guiComboBoxSetCallback(shape_combo, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorShapeTypeCombo), editor);

			local::makeEditor(emission_panel, "Spawn Volume", padding, &editor->particle_system.system_shape.spawn_volume);
			local::makeEditor(emission_panel, "Spawn Volume Local", padding, &editor->particle_system.system_shape.spawn_volume_local);

			ztGuiItem *parent_sizer = emission_panel->parent;
			ztGuiItem *shape_options_sphere = local::makePanelSizer(parent_sizer, "Sphere Options", padding);
			{
				local::makeEditor(shape_options_sphere, "Radius", padding, &editor->particle_system.system_shape.sphere.radius, .1f);
				local::makeEditor(shape_options_sphere, "Angle Min", padding, &editor->particle_system.system_shape.sphere.volume_angle_min, .1f);
				local::makeEditor(shape_options_sphere, "Angle Max", padding, &editor->particle_system.system_shape.sphere.volume_angle_max, .1f);

				while (shape_options_sphere->type != ztGuiItemType_CollapsingPanel) {
					shape_options_sphere = shape_options_sphere->parent;
				}
				editor->shape_options_sphere = shape_options_sphere;
			}

			ztGuiItem *shape_options_circle = local::makePanelSizer(parent_sizer, "Circle Options", padding);
			{
				local::makeEditor(shape_options_circle, "Radius", padding, &editor->particle_system.system_shape.circle.radius, .1f);
				local::makeEditor(shape_options_circle, "Angle Min", padding, &editor->particle_system.system_shape.circle.volume_angle_min, .1f);
				local::makeEditor(shape_options_circle, "Angle Max", padding, &editor->particle_system.system_shape.circle.volume_angle_max, .1f);

				while (shape_options_circle->type != ztGuiItemType_CollapsingPanel) {
					shape_options_circle = shape_options_circle->parent;
				}
				editor->shape_options_circle = shape_options_circle;
			}

			ztGuiItem *shape_options_box = local::makePanelSizer(parent_sizer, "Box Options", padding);
			{
				local::makeEditor(shape_options_box, "Extents", padding, &editor->particle_system.system_shape.box.extents, true, .1f);

				while (shape_options_box->type != ztGuiItemType_CollapsingPanel) {
					shape_options_box = shape_options_box->parent;
				}
				editor->shape_options_box = shape_options_box;
			}

			ztGuiItem *shape_options_square = local::makePanelSizer(parent_sizer, "Square Options", padding);
			{
				local::makeEditor(shape_options_square, "Extents", padding, &editor->particle_system.system_shape.square.extents, true, .1f);

				while (shape_options_square->type != ztGuiItemType_CollapsingPanel) {
					shape_options_square = shape_options_square->parent;
				}
				editor->shape_options_square = shape_options_square;
			}

			_zt_guiParticleEditorShapeTypeHideEditors(editor, ztParticleShapeType_Point);

			local::makeEditor(emission_panel, "Rotation:", padding, &editor->particle_system.system_rotation, true);
			local::makeEditor(emission_panel, "Burst", padding, &editor->particle_system.system_burst);

			//ztGuiItem *burst_options = local::makePanelSizer(parent_sizer, "Burst Options", padding);
			//{
			//	local::makeEditor(burst_options, "Time Start", padding, &editor->particle_system.system_bursts[0].time_start, .1f);
			//	local::makeEditor(burst_options, "Min Particles", padding, &editor->particle_system.system_bursts[0].min_particles, 1);
			//	local::makeEditor(burst_options, "Max Particles", padding, &editor->particle_system.system_bursts[0].max_particles, 1);
			//	local::makeEditor(burst_options, "Cycles", padding, &editor->particle_system.system_bursts[0].cycles, 1);
			//	local::makeEditor(burst_options, "Interval", padding, &editor->particle_system.system_bursts[0].interval, .1f);
			//}
		}

		ztGuiItem *part_birth_panel = local::makePanelSizer(sizer_tools, "Particle Birth", padding);
		{
			local::makeEditor(part_birth_panel, "Lifetime:", padding, &editor->particle_system.lifetime);
			local::makeEditor(part_birth_panel, "Start Speed:", padding, &editor->particle_system.start_speed);
			local::makeEditor(part_birth_panel, "Start Scale", padding, &editor->particle_system.start_scale, true);
			local::makeEditor(part_birth_panel, "Start Rotation", padding, &editor->particle_system.start_rotation, true);
			local::makeEditor(part_birth_panel, "Start Color", padding, &editor->particle_system.start_color);
		}

		ztGuiItem *part_movement_panel = local::makePanelSizer(sizer_tools, "Particle Movement", padding);
		{
			local::makeEditor(part_movement_panel, "Inherit Velocity", padding, &editor->particle_system.velocity_inherit);
			local::makeEditor(part_movement_panel, "Velocity Over Lifetime", padding, &editor->particle_system.velocity_over_lifetime_used, &editor->particle_system.velocity_over_lifetime, true);
			local::makeEditor(part_movement_panel, "Damping Over Lifetime", padding, &editor->particle_system.velocity_damping_over_lifetime_used, &editor->particle_system.velocity_damping_over_lifetime, true);
			local::makeEditor(part_movement_panel, "Speed Over Lifetime", padding, &editor->particle_system.speed_over_lifetime_used, &editor->particle_system.speed_over_lifetime, true, 1);
			local::makeEditor(part_movement_panel, "Rotate Towards Movement", padding, &editor->particle_system.rotate_towards_movement);
			local::makeEditor(part_movement_panel, "Rotation Over Lifetime", padding, &editor->particle_system.rotation_over_lifetime_used, &editor->particle_system.rotation_over_lifetime, true, 1);
			local::makeEditor(part_movement_panel, "Rotation Over Speed", padding, &editor->particle_system.rotation_over_speed_used, &editor->particle_system.rotation_over_speed, true, 1);
			local::makeEditor(part_movement_panel, "+  Speed Range", padding, &editor->particle_system.rotation_over_speed_range[0], &editor->particle_system.rotation_over_speed_range[1], .1f);
		}

		ztGuiItem *part_appear_panel = local::makePanelSizer(sizer_tools, "Particle Appearance", padding);
		{
			local::makeEditor(part_appear_panel, "Color Over Lifetime", padding, &editor->particle_system.color_over_lifetime);
			local::makeEditor(part_appear_panel, "Color Over Speed", padding, &editor->particle_system.color_over_speed_used, &editor->particle_system.color_over_speed);
			local::makeEditor(part_appear_panel, "+  Speed Range", padding, &editor->particle_system.color_over_speed_range[0], &editor->particle_system.color_over_speed_range[1], .1f);
			local::makeEditor(part_appear_panel, "Size Over Lifetime", padding, &editor->particle_system.size_over_lifetime_used, &editor->particle_system.size_over_lifetime, true, .1f);
			local::makeEditor(part_appear_panel, "Size Over Speed", padding, &editor->particle_system.size_over_speed_used, &editor->particle_system.size_over_speed, true, .1f);
			local::makeEditor(part_appear_panel, "+  Speed Range", padding, &editor->particle_system.size_over_speed_range[0], &editor->particle_system.size_over_speed_range[1], .1f);
		}

		ztGuiItem *part_noise_panel = local::makePanelSizer(sizer_tools, "Noise", padding, true);
		{
			local::makeEditor(part_noise_panel, "Use Noise", padding, &editor->particle_system.noise_use);
			local::makeEditor(part_noise_panel, "Multiplier", padding, &editor->particle_system.noise_multiplier);
			local::makeEditor(part_noise_panel, "Position Amount", padding, &editor->particle_system.noise_position_amount, true);
			local::makeEditor(part_noise_panel, "Rotation Amount", padding, &editor->particle_system.noise_rotation_amount, true);
			local::makeEditor(part_noise_panel, "Scale Amount", padding, &editor->particle_system.noise_scale_amount, true);
		}

		ztGuiItem *part_trails_panel = local::makePanelSizer(sizer_tools, "Trails", padding, true);
		{
			local::makeEditor(part_trails_panel, "Use Trails", padding, &editor->particle_system.trails_use);
			local::makeEditor(part_trails_panel, "Percent of Particles", padding, &editor->particle_system.trails_percentage);
			local::makeEditor(part_trails_panel, "Lifetime", padding, &editor->particle_system.trails_lifetime);
			local::makeEditor(part_trails_panel, "Width is Size", padding, &editor->particle_system.trails_width_is_size);
			local::makeEditor(part_trails_panel, "Width", padding, &editor->particle_system.trails_width);
			local::makeEditor(part_trails_panel, "Inherit Color", padding, &editor->particle_system.trails_inherit_color);
			local::makeEditor(part_trails_panel, "Color Over Lifetime", padding, &editor->particle_system.trails_color_over_lifetime_use, &editor->particle_system.trails_color_over_lifetime);
			local::makeEditor(part_trails_panel, "Color Over Trail", padding, &editor->particle_system.trails_color_over_trail);

			local::makeLabel(part_trails_panel, "Sprite:", padding);
			ztGuiItem *button_sprite = zt_guiMakeButton(part_trails_panel, "Select Sprite");
			zt_guiSizerAddItem(part_trails_panel, button_sprite, 1, padding);

			zt_guiButtonSetCallback(button_sprite, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorTrailSpriteSelectButton), editor);
			editor->trail_sprite_button = button_sprite;
		}

		ztGuiItem *rendering_panel = local::makePanelSizer(sizer_tools, "Rendering", padding);
		{
			local::makeLabel(rendering_panel, "Type:", padding);
			ztGuiItem *combo_type = zt_guiMakeComboBox(rendering_panel, 2);
			editor->combo_rendering_type = combo_type;
			zt_guiSizerAddItem(rendering_panel, combo_type, 1, padding);
			zt_guiComboBoxSetCallback(combo_type, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorRenderingTypeCombo), editor);

			zt_guiComboBoxAppend(combo_type, "Billboard", editor);
			zt_guiComboBoxAppend(combo_type, "Facing", editor);

			local::makeLabel(rendering_panel, "Sprite:", padding);
			ztGuiItem *button_sprite = zt_guiMakeButton(rendering_panel, "Select Sprite");
			zt_guiSizerAddItem(rendering_panel, button_sprite, 1, padding);

			zt_guiButtonSetCallback(button_sprite, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorBillboardSpriteSelectButton), editor);
			editor->billboard_sprite_button = button_sprite;

			local::makeLabel(rendering_panel, "Blend Src:", padding);
			ztGuiItem *combo_blend_src = zt_guiMakeComboBox(rendering_panel, ztRendererBlendMode_MAX);
			zt_guiSizerAddItem(rendering_panel, combo_blend_src, 1, padding);
			zt_guiComboBoxSetCallback(combo_blend_src, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorRenderingBlendCombo), editor);
			editor->combo_rendering_blend_src = combo_blend_src;

			local::makeLabel(rendering_panel, "Blend Dst:", padding);
			ztGuiItem *combo_blend_dst = zt_guiMakeComboBox(rendering_panel, ztRendererBlendMode_MAX);
			zt_guiSizerAddItem(rendering_panel, combo_blend_dst, 1, padding);
			zt_guiComboBoxSetCallback(combo_blend_dst, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiParticleEditorRenderingBlendCombo), editor);
			editor->combo_rendering_blend_dst = combo_blend_dst;

			const char *blend_modes[ztRendererBlendMode_MAX] = {
				"Zero",
				"One",
				"Source Color",
				"One Minus Source Color",
				"Dest Color",
				"One Minus Dest Color",
				"Source Alpha",
				"One Minus Source Alpha",
				"Dest Alpha",
				"One Minus Dest Alpha",
			};
			zt_fiz(ztRendererBlendMode_MAX) {
				zt_guiComboBoxAppend(combo_blend_src, blend_modes[i], editor);
				zt_guiComboBoxAppend(combo_blend_dst, blend_modes[i], editor);
			}
		}
	}

	_zt_guiParticleEditorMenu(menu_file, ztParticleEditorMenu_New, editor);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


ztInternal void _zt_guiDebugVariables()
{
	const char *window_name = "Variables";

	// we want a new variable window each time, as variables can be added

	ztGuiItem *window = zt_guiMakeWindow("Variables", ztGuiWindowBehaviorFlags_Default);
	zt_guiItemSetName(window, window_name);

	ztVec2 avg_size = zt_vec2(4.5, .5f);

	r32 ttl_avg_height = zt_game->debug_vars_count * avg_size.y;

	ztVec2 extents = zt_cameraOrthoGetViewportSize(window->gm->gui_camera);

	int cols_needed = zt_max(1, zt_convertToi32Ceil(ttl_avg_height / (extents.y - 2)));
	ztVec2 needed_size = ztVec2::zero;
	while (true) {
		needed_size = zt_vec2(avg_size.x * cols_needed, ttl_avg_height / cols_needed);
		if (needed_size.y > needed_size.x) {
			cols_needed += 1;
		}
		else break;
	}


	zt_guiItemSetSize(window, needed_size + zt_vec2(0, .5f));

	ztGuiItem *sizer = zt_guiMakeColumnSizer(zt_guiWindowGetContentParent(window), cols_needed, ztGuiColumnSizerType_FillColumn);
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

	zt_guiItemSetPosition(window, ztAlign_Left | ztAlign_Top, ztAnchor_Left | ztAnchor_Top, zt_vec2(1.f, -1.f));
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


ztInternal void _zt_guiDebugCurveEditor()
{
	zt_guiDialogAnimCurveEditor(nullptr, ztGuiAnimCurveBehaviorFlags_AdjustValues);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

enum
{
	ztGuiDebugMenu_FpsDisplay,
	ztGuiDebugMenu_Exit,

	ztGuiDebugMenu_Console,
	ztGuiDebugMenu_GuiHierarchy,
	ztGuiDebugMenu_TextureViewer,
	ztGuiDebugMenu_Profiler,
	ztGuiDebugMenu_MemoryInspector,
	ztGuiDebugMenu_SpriteEditor,
	ztGuiDebugMenu_SpriteAnimEditor,
	ztGuiDebugMenu_ParticleEditor,
	ztGuiDebugMenu_CurveEditor,

	ztGuiDebugMenu_Variables,
};

// ================================================================================================================================================================================================

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

		case ztGuiDebugMenu_MemoryInspector: {
			_zt_guiDebugMemoryInspector();
		} break;

		case ztGuiDebugMenu_Variables: {
			_zt_guiDebugVariables();
		} break;

		case ztGuiDebugMenu_SpriteEditor: {
			_zt_debugSpriteEditor();
		} break;

		case ztGuiDebugMenu_SpriteAnimEditor: {
			_zt_debugSpriteAnimEditor();
		} break;

		case ztGuiDebugMenu_ParticleEditor: {
			_zt_guiParticleEditor();
		} break;

		case ztGuiDebugMenu_CurveEditor: {
			_zt_guiDebugCurveEditor();
		}
	};
}

// ================================================================================================================================================================================================

void zt_guiInitDebug(ztGuiManager *gm)
{
	ztGuiItem *menubar = zt_guiMakeMenuBar(nullptr);
	zt_guiItemSetName(menubar, ZT_DEBUG_MENUBAR_NAME);
	zt_guiMenuSetCallback(menubar, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiInitDebugOnMenuItem));

	{
		ztGuiItem *menu_options = zt_guiMakeMenu(nullptr);
		zt_guiMenuAppend(menu_options, "Toggle FPS Display", ztGuiDebugMenu_FpsDisplay);
		zt_guiMenuAppendSeparator(menu_options);
		zt_guiMenuAppend(menu_options, "Exit", ztGuiDebugMenu_Exit);
		zt_guiMenuAppendSubmenu(menubar, "Options", menu_options);
		zt_guiMenuSetCallback(menu_options, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiInitDebugOnMenuItem));
	}
	{
		ztGuiItem *menu_tools = zt_guiMakeMenu(nullptr);
		zt_guiMenuAppend(menu_tools, "Console", ztGuiDebugMenu_Console);
		zt_guiMenuAppend(menu_tools, "GUI Hierarchy", ztGuiDebugMenu_GuiHierarchy);
		zt_guiMenuAppend(menu_tools, "Texture Viewer", ztGuiDebugMenu_TextureViewer);
		zt_guiMenuAppend(menu_tools, "Profiler", ztGuiDebugMenu_Profiler);
		zt_guiMenuAppend(menu_tools, "Memory Inspector", ztGuiDebugMenu_MemoryInspector);
		zt_guiMenuAppend(menu_tools, "Sprite Editor", ztGuiDebugMenu_SpriteEditor);
		zt_guiMenuAppend(menu_tools, "Sprite Animation Editor", ztGuiDebugMenu_SpriteAnimEditor);
		zt_guiMenuAppend(menu_tools, "Particle Editor", ztGuiDebugMenu_ParticleEditor);
		zt_guiMenuAppend(menu_tools, "Curve Editor", ztGuiDebugMenu_CurveEditor);
		zt_guiMenuAppendSubmenu(menubar, "Tools", menu_tools);
		zt_guiMenuSetCallback(menu_tools, ZT_FUNCTION_POINTER_TO_VAR(_zt_guiInitDebugOnMenuItem));
	}
	{
		zt_guiMenuAppend(menubar, "Variables", ztGuiDebugMenu_Variables);
	}

	zt_guiItemSetPosition(menubar, ztAlign_Top, ztAnchor_Top);

	_zt_guiDebugFpsDisplay();

	zt_gui->menu_bar = menubar;
	zt_gui->console_window = nullptr;
	_zt_guiDebugConsole();
}

// ================================================================================================================================================================================================

void zt_guiDebugHide()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemHide(menubar);
	}
}

// ================================================================================================================================================================================================

void zt_guiDebugShow()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemShow(menubar);
	}
}

// ================================================================================================================================================================================================

void zt_guiDebugToggle()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemShow(menubar, !zt_guiItemIsShowing(menubar));
	}
}

// ================================================================================================================================================================================================

void zt_guiDebugBringToFront()
{
	ztGuiItem *menubar = zt_guiItemFindByName(ZT_DEBUG_MENUBAR_NAME);
	if (menubar) {
		zt_guiItemBringToFront(menubar);
	}
}

// ================================================================================================================================================================================================

void zt_debugLogGuiHierarchy(ztGuiItem *item)
{
	struct local
	{
		static void log(ztGuiItem *item, int tabs)
		{
			const char *type;
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

			const char *name = item->name ? item->name : "unnamed";

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

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // include guard
#endif // implementation
