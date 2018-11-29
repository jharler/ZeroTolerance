/***************************************************************************************************************************************************************************************************
file: zt_game_gui_default_theme.h v 0.00 (active initial development)

This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.

No warranty is offered or implied.  Use this at your own risk.

***************************************************************************************************************************************************************************************************

Zero Tolerance Game GUI Default Theme

In exactly one c/cpp source file of your project, you must:

#define ZT_GAME_GUI_DEFAULT_THEME_IMPLEMENTATION
#include "zt_game_gui_default_theme.h"

***************************************************************************************************************************************************************************************************

Options:


***************************************************************************************************************************************************************************************************

Implimentation Options: (only used with ZT_GAME_GUI_DEFAULT_THEME_IMPLEMENTATION #include)


***************************************************************************************************************************************************************************************************/

#ifndef __zt_game_gui_default_theme_h_included__
#define __zt_game_gui_default_theme_h_included__

// ================================================================================================================================================================================================

#include "zt_game_gui.h"

// ================================================================================================================================================================================================

enum ztGuiSpriteNineSlice_Enum
{
	ztGuiSpriteNineSlice_WindowFrame,
	ztGuiSpriteNineSlice_WindowFrameDisabled,
	ztGuiSpriteNineSlice_PanelFrame,
	ztGuiSpriteNineSlice_PanelFrameDisabled,
	ztGuiSpriteNineSlice_CollapsingPanelFrame,
	ztGuiSpriteNineSlice_CollapsingPanelFrameDisabled,
	ztGuiSpriteNineSlice_CollapsingPanelCollapsed,
	ztGuiSpriteNineSlice_CollapsingPanelCollapsedDisabled,
	ztGuiSpriteNineSlice_ButtonNormal,
	ztGuiSpriteNineSlice_ButtonHighlight,
	ztGuiSpriteNineSlice_ButtonPressed,
	ztGuiSpriteNineSlice_ButtonDisabled,
	ztGuiSpriteNineSlice_ButtonToggleNormal,
	ztGuiSpriteNineSlice_ButtonToggleHighlight,
	ztGuiSpriteNineSlice_ButtonTogglePressed,
	ztGuiSpriteNineSlice_ButtonToggleDisabled,
	ztGuiSpriteNineSlice_ButtonToggleOn,
	ztGuiSpriteNineSlice_ButtonToggleOnDisabled,
	ztGuiSpriteNineSlice_Menu,
	ztGuiSpriteNineSlice_MenuBar,
	ztGuiSpriteNineSlice_MenuBarDisabled,
	ztGuiSpriteNineSlice_TextEdit,
	ztGuiSpriteNineSlice_TextEditDisabled,
	ztGuiSpriteNineSlice_ScrollbarVertBackground,
	ztGuiSpriteNineSlice_ScrollbarVertBackgroundDisabled,
	ztGuiSpriteNineSlice_ScrollbarVertHandle,
	ztGuiSpriteNineSlice_ScrollbarVertHandleHighlight,
	ztGuiSpriteNineSlice_ScrollbarVertHandlePressed,
	ztGuiSpriteNineSlice_ScrollbarVertHandleDisabled,
	ztGuiSpriteNineSlice_ScrollbarHorzBackground,
	ztGuiSpriteNineSlice_ScrollbarHorzBackgroundDisabled,
	ztGuiSpriteNineSlice_ScrollbarHorzHandle,
	ztGuiSpriteNineSlice_ScrollbarHorzHandleHighlight,
	ztGuiSpriteNineSlice_ScrollbarHorzHandlePressed,
	ztGuiSpriteNineSlice_ScrollbarHorzHandleDisabled,
	ztGuiSpriteNineSlice_ComboBox,
	ztGuiSpriteNineSlice_ComboBoxHighlight,
	ztGuiSpriteNineSlice_ComboBoxPressed,
	ztGuiSpriteNineSlice_ComboBoxDisabled,
	ztGuiSpriteNineSlice_CycleBox,
	ztGuiSpriteNineSlice_CycleBoxHighlight,
	ztGuiSpriteNineSlice_CycleBoxPressed,
	ztGuiSpriteNineSlice_CycleBoxDisabled,
	ztGuiSpriteNineSlice_TabsActive,
	ztGuiSpriteNineSlice_TabsInactive,
	ztGuiSpriteNineSlice_TabsDisabled,
	ztGuiSpriteNineSlice_Solid,

	ztGuiSpriteNineSlice_MAX,
};

// ================================================================================================================================================================================================

enum ztGuiSprite_Enum
{
	ztGuiSprite_CheckBox,
	ztGuiSprite_CheckBoxHighlight,
	ztGuiSprite_CheckBoxPressed,
	ztGuiSprite_CheckBoxDisabled,
	ztGuiSprite_CheckBoxOn,
	ztGuiSprite_CheckBoxOnHighlight,
	ztGuiSprite_CheckBoxOnPressed,
	ztGuiSprite_CheckBoxOnDisabled,
	ztGuiSprite_Radio,
	ztGuiSprite_RadioHighlight,
	ztGuiSprite_RadioPressed,
	ztGuiSprite_RadioDisabled,
	ztGuiSprite_RadioOn,
	ztGuiSprite_RadioOnHighlight,
	ztGuiSprite_RadioOnPressed,
	ztGuiSprite_RadioOnDisabled,
	ztGuiSprite_SliderHorzBar,
	ztGuiSprite_SliderHorzBarSet,
	ztGuiSprite_SliderHorzBarPressed,
	ztGuiSprite_SliderHorzBarDisabled,
	ztGuiSprite_SliderHorzHandle,
	ztGuiSprite_SliderHorzHandleHighlight,
	ztGuiSprite_SliderHorzHandlePressed,
	ztGuiSprite_SliderHorzHandleDisabled,
	ztGuiSprite_SliderVertBar,
	ztGuiSprite_SliderVertBarSet,
	ztGuiSprite_SliderVertBarPressed,
	ztGuiSprite_SliderVertBarDisabled,
	ztGuiSprite_SliderVertHandle,
	ztGuiSprite_SliderVertHandleHighlight,
	ztGuiSprite_SliderVertHandlePressed,
	ztGuiSprite_SliderVertHandleDisabled,
	ztGuiSprite_Resizer,
	ztGuiSprite_HorzLine,
	ztGuiSprite_IconPlus,
	ztGuiSprite_IconMinus,
	ztGuiSprite_IconArrowLeft,
	ztGuiSprite_IconArrowRight,
	ztGuiSprite_IconArrowUp,
	ztGuiSprite_IconArrowDown,
	ztGuiSprite_IconHandGrab,
	ztGuiSprite_IconHandPoint,
	ztGuiSprite_IconPencil,
	ztGuiSprite_IconTrash,
	ztGuiSprite_IconUndo,
	ztGuiSprite_IconCopy,
	ztGuiSprite_IconCut,
	ztGuiSprite_IconNew,
	ztGuiSprite_IconSave,
	ztGuiSprite_IconOpen,
	ztGuiSprite_IconWarning,
	ztGuiSprite_IconMenu,
	ztGuiSprite_IconCopyright,
	ztGuiSprite_IconCheck,
	ztGuiSprite_IconX,
	ztGuiSprite_IconGear,
	ztGuiSprite_IconCancel,
	ztGuiSprite_IconPlay,
	ztGuiSprite_IconPause,
	ztGuiSprite_IconRewind,
	ztGuiSprite_IconFastForward,
	ztGuiSprite_IconBegin,
	ztGuiSprite_IconEnd,

	ztGuiSprite_MAX,
};

// ================================================================================================================================================================================================

struct ztGuiThemeData
{
	ztTextureID        texture;

	ztSpriteManager    sprite_manager;

	ztSpriteNineSlice *sprite_nine_slice[ztGuiSpriteNineSlice_MAX];
	ztSprite          *sprite           [ztGuiSprite_MAX];

	ztCamera          *gui_camera;

	ztFontID           font;
	ztFontID           font_large;
	ztFontID           font_bold;
	ztFontID           font_large_bold;
	ztFontID           font_monospace;
	ztFontID           font_monospace_large;
};

// ================================================================================================================================================================================================

bool zt_guiDefaultThemeMake(ztGuiTheme *theme, ztCamera *gui_camera);
bool zt_guiDefaultThemeMake(ztGuiTheme *theme, ztCamera *gui_camera, ztAssetManager *asset_manager, const char *gui_texture, const char *gui_sprite_file);
void zt_guiDefaultThemeFree(ztGuiTheme *theme);

// ================================================================================================================================================================================================

void zt_guiDefaultThemeWriteToDisk(const char *gui_texture, const char *gui_sprite_file); // use this to write the image and sprite file to disk for editing


// ================================================================================================================================================================================================

#endif // include guard

#if defined(ZT_GAME_GUI_DEFAULT_THEME_IMPLEMENTATION) || defined(ZT_GAME_GUI_DEFAULT_THEME_INTERNAL_DECLARATIONS)

#ifndef __zt_game_gui_default_theme_h_internal_included__
#define __zt_game_gui_default_theme_h_internal_included__

#define ZT_GAME_GUI_INTERNAL_DECLARATIONS
#include "zt_game_gui.h"

#endif // include guard
#endif // INTERNAL DECLARATIONS

#if defined(ZT_GAME_GUI_DEFAULT_THEME_IMPLEMENTATION)

#ifndef __zt_game_gui_default_theme_implementation__
#define __zt_game_gui_default_theme_implementation__

// ================================================================================================================================================================================================

/**************************************************************************************************
** file: src\gui_theme.cpp
**
** This file was automatically generated.
**************************************************************************************************/

/**************************************************************************************************************************************************************************************************
** file: src/gui_theme.cpp
**
** Responsible for drawing the gui elements
***************************************************************************************************************************************************************************************************/

#define ZT_GAME_GUI_INTERNAL_DECLARATIONS
#include "zt_game_gui.h"

// ================================================================================================================================================================================================

#ifndef ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR
#define ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR	zt_colorRgb(200, 3, 229, 80)
#endif

// ================================================================================================================================================================================================

ztInternal bool _zt_guiDefaultThemeIsItemCustom(ztGuiItem *item)
{
	if (zt_guiItemGetTopLevelParent(item)->custom_flags == 0) {
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_THEME_GET_RVALUE(_zt_guiDefaultThemeGetRValue)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetRValue");

	if (!_zt_guiDefaultThemeIsItemCustom(item)) {
		return false;
	}

	r32 ppu = zt_pixelsPerUnit();

	switch (value)
	{
		case ztGuiThemeValue_r32_Padding:                     *result = 3 / ppu; break;

		case ztGuiThemeValue_r32_WindowTitleHeight:           *result = 24 / ppu; break;
		case ztGuiThemeValue_r32_WindowCollapseButtonOffsetX: *result = 5 / ppu; break;
		case ztGuiThemeValue_r32_WindowCollapseButtonOffsetY: *result = -1 / ppu; break;
		case ztGuiThemeValue_r32_WindowCloseButtonOffsetX:    *result = -5 / ppu; break;
		case ztGuiThemeValue_r32_WindowCloseButtonOffsetY:    *result = -1 / ppu; break;
		case ztGuiThemeValue_r32_WindowPaddingX:              *result = 3 / ppu; break;
		case ztGuiThemeValue_r32_WindowPaddingY:              *result = 3 / ppu; break;
		case ztGuiThemeValue_r32_WindowCornerResizeW:         *result = 16 / ppu; break;
		case ztGuiThemeValue_r32_WindowCornerResizeH:         *result = 16 / ppu; break;

		case ztGuiThemeValue_r32_ButtonDefaultW:              *result = 80 / ppu; break;
		case ztGuiThemeValue_r32_ButtonDefaultH:              *result = 18 / ppu; break;
		case ztGuiThemeValue_r32_ButtonPaddingW:              *result = 1 / ppu; break;
		case ztGuiThemeValue_r32_ButtonPaddingH:              *result = 1 / ppu; break;

		case ztGuiThemeValue_r32_CheckboxW:                   *result = 18 / ppu; break;
		case ztGuiThemeValue_r32_CheckboxH:                   *result = 18 / ppu; break;

		case ztGuiThemeValue_r32_SliderHandleSize:            *result = 12 / ppu; break;
		case ztGuiThemeValue_r32_SliderHandleMinHeight:       *result = 12 / ppu; break;

		case ztGuiThemeValue_r32_ScrollbarButtonW:            *result = 0 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarButtonH:            *result = 0 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinHandleSize:      *result = 10 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinWidth:           *result = 10 / ppu; break;

		case ztGuiThemeValue_r32_TextEditPaddingX:            *result = 2 / ppu; break;
		case ztGuiThemeValue_r32_TextEditPaddingY:            *result = 1 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultW:            *result = 90 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultH:            *result = 20 / ppu; break;

		case ztGuiThemeValue_r32_ComboboxButtonW:             *result = 18 / ppu; break;

		case ztGuiThemeValue_r32_CycleBoxButtonW:             *result = 27 / ppu; break;

		default: return false;  // return false to use the default
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_THEME_GET_IVALUE(_zt_guiDefaultThemeGetIValue)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetIValue");

	if (!_zt_guiDefaultThemeIsItemCustom(item)) {
		return false;
	}

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	switch (value)
	{
		case ztGuiThemeValue_i32_WindowCloseButtonAlign:            *result = ztAlign_Right | ztAlign_Top; break;
		case ztGuiThemeValue_i32_WindowCloseButtonAnchor:           *result = ztAnchor_Right | ztAnchor_Top; break;
		case ztGuiThemeValue_i32_WindowCloseButtonBehaviorFlags:    *result = ztGuiButtonBehaviorFlags_NoBackground | ztGuiButtonBehaviorFlags_OnPressDip; break;


		case ztGuiThemeValue_i32_TextEditFontID:
		case ztGuiThemeValue_i32_MenuFontID: {
			*result = theme_data->font;
			return true;
		} break;

		default: return false;  // return false to use the default
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_THEME_UPDATE_ITEM(_zt_guiDefaultThemeUpdateItem)
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

ZT_FUNC_THEME_UPDATE_SUBITEM(_zt_guiDefaultThemeSubitem)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeSubitem");

	if (!_zt_guiDefaultThemeIsItemCustom(item)) {
		return false;
	}
	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;
	r32 ppu = zt_pixelsPerUnit();


	if (item->guid == ZT_GUI_WINDOW_GUID) {
		if (subitem->guid == ZT_GUI_BUTTON_GUID) {
			char *name = zt_guiItemGetName(subitem);

			if (zt_strEquals(name, "Close")) {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconX]);
			}
			else if (zt_strEquals(name, "Collapse")) {
				if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiWindowInternalStates_Collapsed))) {
					zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconArrowRight]);
				}
				else {
					zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconArrowDown]);
				}
			}
			zt_guiItemSetSize(subitem, zt_vec2(26 / ppu, 26 / ppu));
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_COLLAPSING_PANEL_GUID) {
		if (subitem->guid == ZT_GUI_BUTTON_GUID) {
			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconArrowRight]);
			}
			else {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconArrowDown]);
			}
			zt_guiItemSetSize(subitem, zt_vec2(21 / ppu, 21 / ppu));
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_TREE_GUID) {
		if (subitem->guid == ZT_GUI_BUTTON_GUID) {
			if (data == nullptr || *((bool*)data) == true) {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconMinus]);
			}
			else {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconPlus]);
			}
			zt_guiItemSetSize(subitem, zt_vec2(17 / ppu, 17 / ppu));
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_CYCLEBOX_GUID) {
		if (subitem->guid == ZT_GUI_BUTTON_GUID) {
			r32 button_w = zt_guiThemeGetRValue(zt_guiItemGetTheme(item), ztGuiThemeValue_r32_CycleBoxButtonW, item);

			subitem->size.x = button_w;
			subitem->size.y = item->size.y;

			subitem->behavior_flags |= ztGuiButtonBehaviorFlags_NoBackground;

			if (((ztDirection_Enum)(i32)data) == ztDirection_Left) {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconArrowLeft]);
				zt_guiItemSetPosition(subitem, ztAlign_Left, ztAnchor_Left, ztVec2::zero);
			}
			else if (((ztDirection_Enum)(i32)data) == ztDirection_Right) {
				zt_guiButtonSetIcon(subitem, theme_data->sprite[ztGuiSprite_IconArrowRight]);
				zt_guiItemSetPosition(subitem, ztAlign_Right, ztAnchor_Right, ztVec2::zero);
			}
		}
	}

	// ================================================================================================================================================================================================

	else {
		return false; // return false to use the default
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_THEME_SIZE_ITEM(_zt_guiDefaultThemeSizeItem)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeSizeItem");

	if (!_zt_guiDefaultThemeIsItemCustom(item)) {
		return false;
	}

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	r32 ppu = zt_pixelsPerUnit();

	if (item->guid == ZT_GUI_BUTTON_GUID) {
		ztGuiButtonState *button_state = (ztGuiButtonState*)item->state;

		ztVec2 icon_size = button_state->icon ? button_state->icon->half_size * 2.f : ztVec2::zero;
		ztFontID font = theme_data->font;
		item->size = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(font, item->label) : zt_fontGetExtents(font, item->label);
		item->size.x = zt_max(icon_size.x, item->size.x);
		item->size.y += icon_size.y;

		if (item->label != nullptr) {
			item->size.x += 12 / ppu;
			item->size.y = zt_max(item->size.y, 22 / ppu);
		}
		else {
			item->size += ztVec2::one * (6 / ppu);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_STATIC_TEXT_GUID) {
		ztFontID font = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_MonoSpaced) ? theme_data->font_monospace : theme_data->font;
		item->size = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(font, item->label) : zt_fontGetExtents(font, item->label);
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_SLIDER_GUID) {
		ztGuiSliderState *slider_state = (ztGuiSliderState*)item->state;

		if (slider_state->orient == ztGuiItemOrient_Horz) {
			item->size = zt_vec2(5, zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item));
		}
		else {
			item->size = zt_vec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item), 5);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_CHECKBOX_GUID || item->guid == ZT_GUI_RADIO_BUTTON_GUID) {
		ztVec2 txt_size = zt_fontGetExtents(theme_data->font, item->label);
		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
		r32 checkbox_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CheckboxW, item);
		r32 checkbox_h = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CheckboxW, item);
		item->size.x = txt_size.x + padding + checkbox_w;
		item->size.y = zt_max(txt_size.y, checkbox_h);
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_COMBOBOX_GUID) {
		r32 base_width = 38 / ppu;

		item->size.x = 160 / ppu;
		item->size.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ComboboxButtonW, item);

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
		ztFontID font = theme_data->font;

		ztGuiComboboxState *combo_state = (ztGuiComboboxState*)item->state;

		zt_fiz(combo_state->contents_count) {
			ztVec2 ext = zt_fontGetExtents(font, combo_state->contents[i]);
			item->size.x = zt_max(item->size.x, base_width + ext.x);
			item->size.y = zt_max(item->size.y, ext.y + padding * 2);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_MENU_GUID) {
		ztVec2 icon_orig = zt_vec2(zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, item), zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item));
		ztVec2 icon = icon_orig;
		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
		ztGuiMenuState *menu_state = (ztGuiMenuState*)item->state;
		zt_fiz(menu_state->item_count) {
			if (menu_state->icons[i] != nullptr) {
				icon.x = zt_max(icon.x, menu_state->icons[i]->half_size.x * 2.f + padding * 2.f);
				icon.y = zt_max(icon.y, menu_state->icons[i]->half_size.y * 2.f);
			}
		}

		item->size = ztVec2::zero;

		ztFontID font = theme_data->font;

		zt_fiz(menu_state->item_count) {
			ztVec2 ext = zt_fontGetExtents(font, menu_state->display[i]);

			if (menu_state->ids[i] == ztInvalidID && zt_strStartsWith(menu_state->display[i], "__")) {
				ext.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSeparatorHeight, item);
			}

			item->size.y += zt_max(zt_max(icon.y, ext.y), icon_orig.y) + padding;
			item->size.x = zt_max(item->size.x, ext.x + icon.x + icon_orig.x + padding * 3.f);
		}
		item->size.y += padding;
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_CYCLEBOX_GUID) {
		r32 base_width = 144 / ppu;

		item->size.x = 180 / ppu;
		item->size.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_TextEditDefaultH, item);

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
		ztFontID font = theme_data->font;
		ztGuiCycleboxState *cyclebox_state = (ztGuiCycleboxState*)item->state;
		zt_fiz(cyclebox_state->contents_count) {
			ztVec2 ext = zt_fontGetExtents(font, cyclebox_state->contents[i]);
			item->size.x = zt_max(item->size.x, base_width + ext.x);
			item->size.y = zt_max(item->size.y, ext.y + padding * 2);
		}
	}

	// ================================================================================================================================================================================================

	else {
		return false; // return false to use the default
	}

	return true;
}

// ================================================================================================================================================================================================

ZT_FUNC_THEME_RENDER_ITEM(_zt_guiDefaultThemeRenderItem)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem");

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	r32 ppu = zt_pixelsPerUnit();

	bool has_focus = zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_HasFocus));
	bool highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
	bool pressed = (highlighted && item->gm->item_has_mouse == item) || (!highlighted && zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled)));
	bool enabled = !zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled));

	struct local
	{
		static i32 imageIndex(i32 img_normal, i32 img_highlight, i32 img_pressed, i32 img_disabled, ztGuiItem *item)
		{
			if (img_highlight < 0) img_highlight = img_normal;
			if (img_pressed < 0) img_pressed = img_normal;
			if (img_disabled < 0) img_pressed = img_normal;

			bool disabled = zt_bitIsSet(item->state_flags, zt_bit(ztGuiItemStates_Disabled));
			ztGuiItem *parent = item->parent;
			while (!disabled && parent) {
				if (zt_bitIsSet(parent->state_flags, zt_bit(ztGuiItemStates_Disabled))) {
					disabled = true;
					break;
				}
				parent = parent->parent;
			}

			if (disabled) return img_disabled;

			bool highlighted = zt_bitIsSet(item->gm->item_cache_flags[item->id], ztGuiManagerItemCacheFlags_MouseOver);
			bool pressed = (highlighted && item->gm->item_has_mouse == item);

			if (pressed) return img_pressed;
			if (highlighted) return img_highlight;

			return img_normal;
		}
	};

	if (item->guid == ZT_GUI_WINDOW_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Window");

		if (zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_Modal)) {
			zt_drawListPushColor(draw_list, zt_color(0, 0, 0, .75f));
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], ztVec2::zero, zt_cameraOrthoGetViewportSize(item->gm->gui_camera));
			zt_drawListPopColor(draw_list);
		}

		if (zt_bitIsSet(item->behavior_flags, ztGuiWindowBehaviorFlags_ShowTitle)) {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_WindowFrame, -1, -1, ztGuiSpriteNineSlice_WindowFrameDisabled, item)], item->pos, item->size);
			zt_drawListAddText2D(draw_list, zt_guiWindowIsOnTop(item) ? theme_data->font_bold : theme_data->font, item->label, zt_vec2(pos.x, pos.y + item->size.y / 2 - 6 / ppu), ztAlign_Center | ztAlign_Top | ztAlign_ToPixel, ztAnchor_Center | ztAnchor_Top);
		}
		else {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_PANEL_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Panel");

		if (zt_bitIsSet(item->behavior_flags, ztGuiPanelBehaviorFlags_DrawBackground)) {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_COLLAPSING_PANEL_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:CollapsingPanel");

		if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed))) {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);
		}
		else {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_CollapsingPanelFrame, -1, -1, ztGuiSpriteNineSlice_CollapsingPanelFrameDisabled, item)], pos, item->size);
		}

		if (item->label != nullptr) {
			r32 panel_height = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_CollapsingPanelHeight, item);

			ztVec2 title_pos = zt_vec2(pos.x - ((item->size.x) / 2) + 25 / ppu, pos.y + (item->size.y - (panel_height)) / 2);
			ztVec2 title_size;

			//				if (!zt_bitIsSet(item->state_flags, zt_bit(ztGuiCollapsingPanelInternalStates_Collapsed)) {
			//				}

			zt_drawListAddText2D(draw_list, theme_data->font_bold, item->label, title_pos, ztAlign_Left | ztAlign_ToPixel, ztAnchor_Left, &title_size);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_TOGGLE_BUTTON_GUID || item->guid == ZT_GUI_BUTTON_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Button");
		ztFontID font = theme_data->font;
		r32 scale = 1;

		if (font != ztInvalidID) {
			ztVec2 ext = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(font, item->label) : zt_fontGetExtents(font, item->label);
			ztVec2 off = pos;

			ztGuiButtonState *button_state = (ztGuiButtonState*)item->state;

			if (button_state->icon) {
				off.y -= button_state->icon->half_size.y * 1;
			}

			ext *= scale;

			if (item->align_flags != 0) {
				if (zt_bitIsSet(item->align_flags, ztAlign_Left)) off.x -= (item->size.x - ext.x) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Right)) off.x += (item->size.x - ext.x) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Top)) off.y += (item->size.y - ext.y) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Bottom)) off.y -= (item->size.y - ext.y) / 2.f;
			}

			ztVec2 text_ext = ztVec2::zero;

			if (!zt_bitIsSet(item->behavior_flags, ztGuiButtonBehaviorFlags_NoBackground) || highlighted) {
				if (item->guid == ZT_GUI_TOGGLE_BUTTON_GUID) {
					bool toggled = zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled));
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(toggled ? ztGuiSpriteNineSlice_ButtonToggleOn : ztGuiSpriteNineSlice_ButtonToggleNormal, ztGuiSpriteNineSlice_ButtonToggleHighlight, ztGuiSpriteNineSlice_ButtonTogglePressed, toggled ? ztGuiSpriteNineSlice_ButtonToggleOnDisabled : ztGuiSpriteNineSlice_ButtonToggleDisabled, item)], pos, item->size);
				}
				else {
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ButtonNormal, ztGuiSpriteNineSlice_ButtonHighlight, ztGuiSpriteNineSlice_ButtonPressed, ztGuiSpriteNineSlice_ButtonDisabled, item)], pos, item->size);
				}
			}

			if (zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy)) {
				zt_drawListAddFancyText2D(draw_list, font, item->label, off, zt_vec2(scale, scale), item->align_flags | ztAlign_ToPixel, item->anchor_flags, &text_ext);
			}
			else {
				zt_drawListAddText2D(draw_list, font, item->label, off, zt_vec2(scale, scale), item->align_flags | ztAlign_ToPixel, item->anchor_flags, &text_ext);
			}

			if (button_state->icon) {
				if (text_ext.y > 0) {
					off.y += 3 / ppu;
				}

				ztVec3 icon_pos = zt_vec3(off + zt_vec2(0, text_ext.y / 2.f + button_state->icon->half_size.y), 0);
				zt_drawListAddSpriteFast(draw_list, button_state->icon, icon_pos, ztVec3::zero, zt_vec3(scale, scale, scale));
			}
		}
		else return false;
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_STATIC_TEXT_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:StaticText");
		ztFontID font = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_MonoSpaced) ? theme_data->font_monospace : theme_data->font;
		r32 scale = 1;

		if (font != ztInvalidID) {
			ztVec2 ext = zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy) ? zt_fontGetExtentsFancy(font, item->label) : zt_fontGetExtents(font, item->label);
			ztVec2 off = pos;


			ext *= scale;

			if (item->align_flags != 0) {
				if (zt_bitIsSet(item->align_flags, ztAlign_Left)) off.x -= (item->size.x - ext.x) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Right)) off.x += (item->size.x - ext.x) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Top)) off.y += (item->size.y - ext.y) / 2.f;
				if (zt_bitIsSet(item->align_flags, ztAlign_Bottom)) off.y -= (item->size.y - ext.y) / 2.f;
			}

			ztVec2 text_ext = ztVec2::zero;

			if (zt_bitIsSet(item->behavior_flags, ztGuiStaticTextBehaviorFlags_Fancy)) {
				zt_drawListAddFancyText2D(draw_list, font, item->label, off, zt_vec2(scale, scale), item->align_flags | ztAlign_ToPixel, item->anchor_flags, &text_ext);
			}
			else {
				zt_drawListAddText2D(draw_list, font, item->label, off, zt_vec2(scale, scale), item->align_flags | ztAlign_ToPixel, item->anchor_flags, &text_ext);
			}
		}
		else return false;
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_CHECKBOX_GUID || item->guid == ZT_GUI_RADIO_BUTTON_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:CheckRadio");

		bool checkbox = zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsCheckbox);
		bool radio = zt_bitIsSet(item->behavior_flags, ztGuiButtonInternalBehaviorFlags_IsRadio);

		r32 checkbox_w = zt_guiThemeGetRValue(theme, item->guid == ZT_GUI_CHECKBOX_GUID ? ztGuiThemeValue_r32_CheckboxW : ztGuiThemeValue_r32_RadiobuttonW, item);
		r32 checkbox_h = zt_guiThemeGetRValue(theme, item->guid == ZT_GUI_CHECKBOX_GUID ? ztGuiThemeValue_r32_CheckboxW : ztGuiThemeValue_r32_RadiobuttonW, item);
		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);

		ztVec2 box_size = zt_vec2(checkbox_w, checkbox_h);
		ztVec2 box_pos, txt_size, txt_pos;

		txt_size = item->label == nullptr ? ztVec2::zero : zt_fontGetExtents(theme_data->font, item->label);
		if (zt_bitIsSet(item->behavior_flags, ztGuiCheckboxBehaviorFlags_RightText)) {
			box_pos = zt_vec2((item->size.x - box_size.x) / -2.f, 0);
			txt_pos = zt_vec2(box_pos.x + box_size.x / 2.f + padding, 0);
		}
		else {
			txt_pos = zt_vec2(item->size.x / -2.f, 0);
			box_pos = zt_vec2((item->size.x / 2.f) - (box_size.x / 2.f), 0);
		}

		zt_drawListAddText2D(draw_list, theme_data->font, item->label, zt_strLen(item->label), txt_pos + pos, ztAlign_Left | ztAlign_ToPixel, ztAnchor_Left);


		box_pos += pos;

		if (checkbox) {
			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled))) {
				//zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_IconCheck], zt_vec3(box_pos, 0));
				zt_drawListAddSprite(draw_list, theme_data->sprite[local::imageIndex(ztGuiSprite_CheckBoxOn, ztGuiSprite_CheckBoxOnHighlight, ztGuiSprite_CheckBoxOnPressed, ztGuiSprite_CheckBoxOnDisabled, item)], zt_vec3(box_pos, 0));
			}
			else {
				zt_drawListAddSprite(draw_list, theme_data->sprite[local::imageIndex(ztGuiSprite_CheckBox, ztGuiSprite_CheckBoxHighlight, ztGuiSprite_CheckBoxPressed, ztGuiSprite_CheckBoxDisabled, item)], zt_vec3(box_pos, 0));
			}
		}
		else if (radio) {
			zt_drawListAddSprite(draw_list, theme_data->sprite[local::imageIndex(ztGuiSprite_Radio, ztGuiSprite_RadioHighlight, ztGuiSprite_RadioPressed, ztGuiSprite_RadioDisabled, item)], zt_vec3(box_pos, 0));

			if (zt_bitIsSet(item->state_flags, zt_bit(ztGuiButtonInternalStates_IsToggled))) {
				//zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_RadioSelect], zt_vec3(box_pos, 0));
			}
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_TEXTEDIT_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:TextEdit");

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_TextEdit, -1, -1, ztGuiSpriteNineSlice_TextEditDisabled, item)], pos, item->size);

		ztGuiTextEditState *textedit_state = (ztGuiTextEditState*)item->state;
		ztVec2 text_pos = zt_vec2(textedit_state->text_pos[0], textedit_state->text_pos[1] + (-2 / zt_pixelsPerUnit()));

		if (textedit_state->select_beg != textedit_state->select_end) {
			int sel_beg = zt_min(textedit_state->select_beg, textedit_state->select_end);
			int sel_end = zt_max(textedit_state->select_beg, textedit_state->select_end);

			while (sel_beg < sel_end) {
				ztVec2 pos_beg = zt_guiTextEditGetCharacterPos(item, sel_beg, false);

				int idx_end_line = zt_strFindPos(textedit_state->text_buffer, "\n", sel_beg);
				if (idx_end_line == ztStrPosNotFound || idx_end_line > sel_end) {
					idx_end_line = sel_end;
				}

				ztVec2 pos_end = zt_guiTextEditGetCharacterPos(item, idx_end_line, true);

				ztVec2 pos_size = zt_vec2(pos_end.x - pos_beg.x, pos_beg.y - pos_end.y);
				ztVec2 pos_center = zt_vec2(pos_beg.x + pos_size.x / 2.f, pos_beg.y - pos_size.y / 2.f);

				zt_drawListPushColor(draw_list, ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR);
				zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], text_pos + pos_center, pos_size);
				zt_drawListPopColor(draw_list);

				sel_beg = idx_end_line + 1;
			}
		}

		ztVec3 dlpos = zt_vec3(text_pos, 0);
		zt_alignToPixel(&dlpos, zt_pixelsPerUnit());
		zt_drawListAddDrawList(draw_list, item->draw_list, dlpos);

		if (item->gm->focus_item == item) {
			if (textedit_state->cursor_vis) {
				ztFontID font = theme_data->font;
				ztVec2 cursor_pos = text_pos + zt_vec2(textedit_state->cursor_xy[0], textedit_state->cursor_xy[1]);
				ztVec2 cursor_size = zt_fontGetExtents(font, "|");
				cursor_pos.x -= cursor_size.x / 2;
				zt_drawListAddText2D(draw_list, font, "|", cursor_pos, ztAlign_Left | ztAlign_Top | ztAlign_ToPixel, ztAnchor_Left | ztAnchor_Top);
			}
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_SLIDER_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Slider");
		ztVec2 handle_pos, handle_size;

		ztGuiSliderState *slider_state = (ztGuiSliderState*)item->state;

		if (slider_state->drag_state.dragging) {
			highlighted = true;
		}

		r32 handle_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_SliderHandleSize, item);
		r32 scale = 1.f;

		if (slider_state->orient == ztGuiItemOrient_Horz) {
			handle_pos = pos + zt_vec2(slider_state->handle_pos, 0);
			handle_size = zt_vec2(zt_max(8 / ppu, slider_state->handle_size), item->size.y);

			ztSprite *sprite_set = highlighted ? theme_data->sprite[ztGuiSprite_SliderHorzBarPressed] : theme_data->sprite[ztGuiSprite_SliderHorzBarSet];
			ztSprite *sprite_rem = theme_data->sprite[ztGuiSprite_SliderHorzBar];

			r32 x_scale = item->size.x / (sprite_rem->half_size.x * 2);
			zt_drawListAddSprite(draw_list, sprite_rem, zt_vec3(pos, 0), ztVec3::zero, zt_vec3(x_scale, 1, 1));

			x_scale = (item->size.x * slider_state->value) / (sprite_set->half_size.x * 2);
			r32 x_offset = (item->size.x - (item->size.x * slider_state->value)) * .5f;
			zt_drawListAddSprite(draw_list, sprite_set, zt_vec3(pos.x - x_offset, pos.y, 0), ztVec3::zero, zt_vec3(x_scale, 1, 1));

			ztSprite *sprite_handle = highlighted ? theme_data->sprite[ztGuiSprite_SliderHorzHandlePressed] : theme_data->sprite[local::imageIndex(ztGuiSprite_SliderHorzHandle, ztGuiSprite_SliderHorzHandleHighlight, ztGuiSprite_SliderHorzHandlePressed, ztGuiSprite_SliderHorzHandleDisabled, item)];

			zt_drawListAddSpriteFast(draw_list, sprite_handle, zt_vec3(handle_pos, 0), ztVec3::zero, zt_vec3(scale, scale, 1));
		}
		else {
			handle_pos = pos + zt_vec2(0, slider_state->handle_pos);
			handle_size = zt_vec2(item->size.x, zt_max(10 / ppu, slider_state->handle_size));

			ztSprite *sprite_set = highlighted ? theme_data->sprite[ztGuiSprite_SliderVertBarPressed] : theme_data->sprite[ztGuiSprite_SliderVertBarSet];
			ztSprite *sprite_rem = theme_data->sprite[ztGuiSprite_SliderVertBar];

			r32 y_scale = item->size.y / (sprite_rem->half_size.y * 2);
			zt_drawListAddSprite(draw_list, sprite_rem, zt_vec3(pos, 0), ztVec3::zero, zt_vec3(1, y_scale, 1));

			y_scale = (item->size.y * slider_state->value) / (sprite_set->half_size.y * 2);
			r32 y_offset = (item->size.y - (item->size.y * slider_state->value)) * .5f;
			zt_drawListAddSprite(draw_list, sprite_set, zt_vec3(pos.x, pos.y - y_offset, 0), ztVec3::zero, zt_vec3(1, y_scale, 1));

			ztSprite *sprite_handle = highlighted ? theme_data->sprite[ztGuiSprite_SliderVertHandlePressed] : theme_data->sprite[local::imageIndex(ztGuiSprite_SliderVertHandle, ztGuiSprite_SliderVertHandleHighlight, ztGuiSprite_SliderVertHandlePressed, ztGuiSprite_SliderVertHandleDisabled, item)];

			zt_drawListAddSpriteFast(draw_list, sprite_handle, zt_vec3(handle_pos, 0), ztVec3::zero, zt_vec3(scale, scale, 1));
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_SCROLLBAR_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:ScrollbarSlider");

		ztVec2 handle_pos, handle_size;

		ztGuiSliderState *slider_state = (ztGuiSliderState*)item->state;

		if (slider_state->drag_state.dragging) {
			highlighted = true;
		}

		r32 scrollbar_button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ScrollbarButtonW, item);

		if (slider_state->orient == ztGuiItemOrient_Horz) {
			handle_pos = pos + zt_vec2(slider_state->handle_pos, 0);
			handle_size = zt_vec2(zt_max(10 / ppu, slider_state->handle_size - (2 / ppu)), item->size.y - (2 / ppu));

			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarHorzBackground, -1, -1, ztGuiSpriteNineSlice_ScrollbarHorzBackgroundDisabled, item)], pos, zt_vec2(item->size.x, 10 / ppu));
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarHorzHandle, ztGuiSpriteNineSlice_ScrollbarHorzHandleHighlight, ztGuiSpriteNineSlice_ScrollbarHorzHandlePressed, ztGuiSpriteNineSlice_ScrollbarHorzHandleDisabled, item)], handle_pos, handle_size);
		}
		else {
			handle_pos = pos + zt_vec2(0, slider_state->handle_pos);
			handle_size = zt_vec2(item->size.x - (2 / ppu), zt_max(10 / ppu, slider_state->handle_size - (2 / ppu)));

			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarVertBackground, -1, -1, ztGuiSpriteNineSlice_ScrollbarVertBackgroundDisabled, item)], pos, zt_vec2(10 / ppu, item->size.y));
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarVertHandle, ztGuiSpriteNineSlice_ScrollbarVertHandleHighlight, ztGuiSpriteNineSlice_ScrollbarVertHandlePressed, ztGuiSpriteNineSlice_ScrollbarVertHandleDisabled, item)], handle_pos, handle_size);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_COMBOBOX_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:ComboBox");

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ComboBox, ztGuiSpriteNineSlice_ComboBoxHighlight, ztGuiSpriteNineSlice_ComboBoxPressed, ztGuiSpriteNineSlice_ComboBoxDisabled, item)], pos, item->size);

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);

		r32 button_w = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_ComboboxButtonW, item);

		ztGuiComboboxState *combo_state = (ztGuiComboboxState*)item->state;

		if (combo_state->selected >= 0 && combo_state->selected < combo_state->contents_count) {
			r32 width = item->size.x;

			pos.x = (pos.x) + (width / -2.f + padding * 2.f);

			if (combo_state->popup != nullptr) {
				ztGuiMenuState *menu_state = (ztGuiMenuState*)combo_state->popup->state;
				if (menu_state->icons[combo_state->selected]) {
					ztSprite *sprite = menu_state->icons[combo_state->selected];

					zt_drawListAddSprite(draw_list, sprite, zt_vec3(pos.x + sprite->half_size.x, pos.y, 0));

					pos.x += sprite->half_size.x * 2 + padding;
				}
			}
			zt_drawListAddFancyText2D(draw_list, theme_data->font, combo_state->contents[combo_state->selected], pos, ztAlign_Left | ztAlign_ToPixel, ztAnchor_Left);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_MENUBAR_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:MenuBar");

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_MenuBar, -1, -1, ztGuiSpriteNineSlice_MenuBarDisabled, item)], pos, item->size);

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
		pos.x -= (item->size.x - padding * 2.f) / 2.f;
		pos.y += (item->size.y - padding * 2.f) / 2.f;

		ztVec2 icon;
		icon.x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, item);
		icon.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item);

		ztGuiMenuState *menu_state = (ztGuiMenuState*)item->state;
		zt_fiz(menu_state->item_count) {
			if (menu_state->icons[i] != nullptr) {
				icon.x = zt_max(icon.x, menu_state->icons[i]->half_size.x * 2.f + padding * 2.f);
				icon.y = zt_max(icon.y, menu_state->icons[i]->half_size.y * 2.f);
			}
		}

		zt_fiz(menu_state->item_count) {
			ztVec2 ext = zt_fontGetExtents(theme_data->font, menu_state->display[i]);

			if (icon.y > ext.y) ext.y = icon.y;
			if (!(menu_state->ids[i] == ztInvalidID && zt_strStartsWith(menu_state->display[i], "__"))) {
				if (menu_state->highlighted == i && highlighted) {
					zt_drawListPushColor(draw_list, ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR);
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], zt_vec2(pos.x + ext.x / 2, pos.y - ext.y / 2.f), zt_vec2(ext.x + padding * 2, ext.y + 6 / ppu));
					zt_drawListPopColor(draw_list);
				}
				zt_drawListAddText2D(draw_list, theme_data->font, menu_state->display[i], zt_vec2(pos.x + icon.x, pos.y - ext.y / 2.f), ztAlign_Left | ztAlign_ToPixel, ztAnchor_Left);

				if (menu_state->icons[i] != nullptr) {
					r32 y = zt_max(menu_state->icons[i]->half_size.y, ext.y / 2.f);
					zt_drawListAddSprite(draw_list, menu_state->icons[i], zt_vec3(pos.x + padding + menu_state->icons[i]->half_size.x, pos.y - y, 0));
				}
			}

			pos.x += icon.x + padding + ext.x + padding;
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_MENU_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Menu");

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_Menu, -1, -1, -1, item)], pos, item->size);

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);
		pos.x -= (item->size.x - padding * 2.f) / 2.f;
		pos.y += (item->size.y - padding * 2.f) / 2.f;

		ztVec2 icon;
		icon.x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, item);
		icon.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item);

		ztGuiMenuState *menu_state = (ztGuiMenuState*)item->state;
		zt_fiz(menu_state->item_count) {
			if (menu_state->icons[i] != nullptr) {
				icon.x = zt_max(icon.x, menu_state->icons[i]->half_size.x * 2.f + padding * 2.f);
				icon.y = zt_max(icon.y, menu_state->icons[i]->half_size.y * 2.f);
			}
		}

		ztVec2 size = item->size;

		if (zt_guiItemIsVisible(menu_state->scrollbar_vert)) {
			pos.y += (menu_state->full_size.y - item->size.y) * zt_guiScrollbarGetValue(menu_state->scrollbar_vert);
			size.x -= menu_state->scrollbar_vert->size.x;
		}
		if (zt_guiItemIsVisible(menu_state->scrollbar_horz)) {
			pos.x -= (menu_state->full_size.x - item->size.x) * zt_guiScrollbarGetValue(menu_state->scrollbar_horz);
		}

		ztFontID font = theme_data->font;

		zt_fiz(menu_state->item_count) {
			ztVec2 ext = zt_fontGetExtents(font, menu_state->display[i]);

			if (menu_state->ids[i] == ztInvalidID && zt_strStartsWith(menu_state->display[i], "__")) {
				ext.y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSeparatorHeight, item);

				ztVec2 lpos = pos;
				lpos.y -= ext.y / 2.f;
				zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_HorzLine], zt_vec3(pos.x + item->size.x / 2 - padding, pos.y, 0), ztVec3::zero, zt_vec3(item->size.x, 1, 1));
			}
			else {
				if (menu_state->highlighted == i && highlighted) {
					zt_drawListPushColor(draw_list, ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR);
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], zt_vec2(pos.x + size.x / 2 - padding, pos.y - ext.y / 2.f + 1 / ppu), zt_vec2(size.x - padding * 2.f, ext.y + 4 / ppu));
					zt_drawListPopColor(draw_list);
				}
				zt_drawListAddText2D(draw_list, font, menu_state->display[i], zt_vec2(pos.x + icon.x + padding, pos.y - ext.y / 2.f), ztAlign_Left | ztAlign_ToPixel, ztAnchor_Left);

				if (menu_state->icons[i] != nullptr) {
					r32 y = zt_max(menu_state->icons[i]->half_size.y, ext.y / 2.f);
					zt_drawListAddSprite(draw_list, menu_state->icons[i], zt_vec3(pos.x + padding + menu_state->icons[i]->half_size.x, pos.y - y, 0));
				}
			}


			if (menu_state->submenus[i] != nullptr) {
				r32 icon_x = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconX, item);
				r32 icon_y = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_MenuSubmenuIconY, item);
				r32 y = zt_max(icon_y, ext.y) / 2.f;
				zt_drawListAddText2D(draw_list, font, ">", zt_vec2((item->size.x + pos.x) - (padding * 3 + icon_x / 2.f), pos.y - y + padding));
			}

			pos.y -= zt_max(icon.y, ext.y) + padding;
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_TREE_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Tree");

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);

		ztGuiTreeState *tree_state = (ztGuiTreeState*)item->state;

		if (tree_state->active_item != nullptr) {
			bool visible = true;
			ztGuiTreeItem *parent = tree_state->active_item->parent;
			while (parent) {
				if (!parent->expanded) {
					visible = false;
					break;
				}
				parent = parent->parent;
			}
			if (visible) {
				ztGuiItem *active = tree_state->active_item->item;
				if (active) {
					ztVec2 npos = zt_guiItemPositionLocalToScreen(active, ztVec2::zero);

					zt_drawListPushColor(draw_list, ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR);
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], zt_vec2(pos.x, npos.y), zt_vec2(item->size.x, active->size.y));
					zt_drawListPopColor(draw_list);
				}
			}
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_SPRITE_DISPLAY_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:sprite");

		ztGuiSpriteDisplayState *spritedisplay_state = (ztGuiSpriteDisplayState*)item->state;
		if (*(ztVec4*)spritedisplay_state->bgcolor != ztVec4::zero) {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);
		}

		if (spritedisplay_state->sprite_anim_controller) {
			ztSprite *sprite = zt_spriteAnimControllerActiveSprite(spritedisplay_state->sprite_anim_controller);
			if (sprite != nullptr) {
				zt_drawListAddSprite(draw_list, sprite, zt_vec3(pos, 0), ztVec3::zero, zt_vec3(spritedisplay_state->scale[0], spritedisplay_state->scale[1], 1));
			}
		}
		else {
			zt_drawListAddGuiThemeSprite(draw_list, spritedisplay_state->sprite, pos, item->size);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_SPINNER_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:Spinner");


		zt_drawListPushColor(draw_list, ztColor_DarkGray);
		//		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], pos, item->size);
		zt_drawListPopColor(draw_list);

		//zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_HorzLine], zt_vec3(pos.x, pos.y, 0), ztVec3::zero, zt_vec3(item->size.x - 0 / ppu, 1, 1));

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);

		ztVec3 pos_txt_p = zt_vec3(pos.x, (pos.y + (item->size.y / 2)) - (6 / ppu), 0);
		ztVec3 pos_txt_m = zt_vec3(pos.x, (pos.y - (item->size.y / 2)) + (6 / ppu), 0);

		zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_IconArrowUp], pos_txt_p);
		zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_IconArrowDown], pos_txt_m);
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_LISTBOX_GUID) {
		ZT_PROFILE_GUI("_zt_guiDefaultThemeRenderItem:ListBox");

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);

		r32 padding = zt_guiThemeGetRValue(theme, ztGuiThemeValue_r32_Padding, item);

		ztGuiListboxState *listbox_state = (ztGuiListboxState*)item->state;

		int item_drawn = 0;
		zt_fiz(listbox_state->item_count) {
			item_drawn += 1;

			if (!zt_guiItemIsVisible(listbox_state->items[i])) {
				if (listbox_state->hidden[i]) {
					item_drawn -= 1;
				}
				continue;
			}

			if (listbox_state->selected[i]) {
				zt_drawListPushColor(draw_list, ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR);
				zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], pos + listbox_state->container->pos + zt_vec2(0, listbox_state->items[i]->pos.y), zt_vec2(listbox_state->container->size.x - 2 / ppu, listbox_state->items[i]->size.y + 2 / ppu));
				zt_drawListPopColor(draw_list);
			}
			else if (zt_bitIsSet(item->behavior_flags, ztGuiListBoxBehaviorFlags_AlternateRowColor) && item_drawn % 2 == 0) {
				zt_drawListAddSolidRect2D(draw_list, pos + listbox_state->container->pos + zt_vec2(0, listbox_state->items[i]->pos.y), zt_vec2(listbox_state->container->size.x, listbox_state->items[i]->size.y), zt_color(.5f, .5f, 1, .125f));
			}
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_CYCLEBOX_GUID) {
		ztGuiCycleboxState *cyclebox_state = (ztGuiCycleboxState*)item->state;
		if (cyclebox_state->selected >= 0 && cyclebox_state->selected < cyclebox_state->contents_count) {
			zt_drawListAddFancyText2D(draw_list, theme_data->font, cyclebox_state->contents[cyclebox_state->selected], pos);
		}
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_TABS_GUID) {
		ztGuiTabsState *tabs_state = (ztGuiTabsState*)item->state;

		//zt_drawListPushColor(draw_list, ztColor_Red);
		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_PanelFrame], pos, item->size);
		//zt_drawListPopColor(draw_list);

		r32 padding = zt_guiPadding() * 2.f;
		ztVec2 text_pos = pos + zt_vec2(item->size.x / -2.f, (item->size.y / 2.f) - (ZT_GUI_TABS_DEFAULT_TABS_HEIGHT / 2.f));

		zt_fiz(tabs_state->tabs_count) {
			bool active = i == tabs_state->active_tab;
			ztFontID font = active ? theme_data->font_bold : theme_data->font;
			ztColor color = ztColor_White;// active ? ztColor_LightPurple : ztColor_White;

			ztVec2 ext = zt_fontGetExtentsFancy(font, tabs_state->tabs[i]);
			ztVec2 tab_size = zt_vec2(ext.x, ZT_GUI_TABS_DEFAULT_TABS_HEIGHT) + zt_vec2(padding * 2, padding * 0);

			tabs_state->tabs_pos[i] = text_pos + tab_size * zt_vec2(.5f, 0);
			tabs_state->tabs_area[i] = tab_size;

			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[active ? ztGuiSpriteNineSlice_TabsActive : ztGuiSpriteNineSlice_TabsInactive], tabs_state->tabs_pos[i], tab_size);

			text_pos.x += padding;
			zt_alignToPixel(&text_pos, zt_pixelsPerUnit());
			zt_drawListAddFancyText2D(draw_list, font, tabs_state->tabs[i], text_pos, ztAlign_Left | ztAlign_Center, ztAnchor_Left | ztAnchor_Center, &ext, color);

			text_pos.x += ext.x + padding;
		}
	}

	// ================================================================================================================================================================================================

	else {
		return false; // return false to use the default
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_THEME_POSTRENDER_ITEM(_zt_guiDefaultThemePostRenderItem)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemePostRenderItem");

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	return false;
}

// ================================================================================================================================================================================================

ztInternal ztGuiThemeSprite _zt_guiDefaultThemeMakeThemeSprite(ztSprite s)
{
	ztGuiThemeSprite gts;
	gts.type = ztGuiThemeSpriteType_Sprite;
	gts.s = s;
	return gts;
}

// ================================================================================================================================================================================================

ztInternal ztGuiThemeSprite _zt_guiDefaultThemeMakeThemeSprite(ztSpriteNineSlice sns)
{
	ztGuiThemeSprite gts;
	gts.type = ztGuiThemeSpriteType_SpriteNineSlice;
	gts.sns = sns;
	return gts;
}

// ================================================================================================================================================================================================

ZT_FUNC_THEME_RENDER_PASS_BEGIN(_zt_guiDefaultThemeRenderPassBegin)
{
}

// ================================================================================================================================================================================================

ZT_FUNC_THEME_RENDER_PASS_END(_zt_guiDefaultThemeRenderPassEnd)
{
}

// ================================================================================================================================================================================================

ztInternal void *_zt_guiDefaultThemeLoadImageFile(i32 *data_size, ztMemoryArena *arena) // this function was automatically generated
{
	i32 encoded_size = 121569;
	char *encoded_data_strings[] = {
		"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cAVVAAAAAAAAAIABAAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAACAAQAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAMAAAAAAAAAAAIABAAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAACAAQAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAAAgAEAAAAAAAAAAAMAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAACAAQAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAAAgAEAAAAAAAAAADAAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAACAAQAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAAAAwAAAAAAAAAABgAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAAAgAEAAAAAAAAAADAAAAAAAAAAAGAAAAAAAAAAAAAMAAAAAAAAAACAAQAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAMAAAAAAAAAAAAAYAAAAAAAAAAAAAwAAAAAAAAAAYAAAAAAAAAAAwAAAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAABgAAAAAAAAAAAADAAAAAAAAAAAgAEAAAAAAAAAADAAAAAAAAAAAAAGAAAAAAAAAAAMAAAAAAAAAACAAQAAAAAAAAAA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",
	};
	*data_size = 91174;
	char *encoded_data = zt_mallocStructArrayArena(char, encoded_size, zt_memGetTempArena());
	i32 encoded_data_pos = 0;
	zt_fize(encoded_data_strings) {
		i32 string_len = zt_strLen(encoded_data_strings[i]);
		zt_memCpy(encoded_data + encoded_data_pos, string_len, encoded_data_strings[i], string_len);
		encoded_data_pos += string_len;
	}
	byte *data = zt_mallocStructArrayArena(byte, *data_size, arena);
	zt_base64Decode(encoded_data, encoded_size, data, *data_size);
	zt_freeArena(encoded_data, zt_memGetTempArena());
	return data;
}

// ================================================================================================================================================================================================

ztInternal void *_zt_guiDefaultThemeLoadImageSpriteFile(i32 *data_size, ztMemoryArena *arena) // this function was automatically generated
{
	i32 encoded_size = 36901;
	char *encoded_data_strings[] = {
		"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",
		"AAAAAA8JAAAAAA8ODg0DAAAAAA8ODhC6s///",
	};
	*data_size = 27675;
	char *encoded_data = zt_mallocStructArrayArena(char, encoded_size, zt_memGetTempArena());
	i32 encoded_data_pos = 0;
	zt_fize(encoded_data_strings) {
		i32 string_len = zt_strLen(encoded_data_strings[i]);
		zt_memCpy(encoded_data + encoded_data_pos, string_len, encoded_data_strings[i], string_len);
		encoded_data_pos += string_len;
	}
	byte *data = zt_mallocStructArrayArena(byte, *data_size, arena);
	zt_base64Decode(encoded_data, encoded_size, data, *data_size);
	zt_freeArena(encoded_data, zt_memGetTempArena());
	return data;
}

// ================================================================================================================================================================================================

ztInternal bool _zt_guiDefaultThemeMakeBase(ztGuiTheme *theme, ztGuiThemeData *theme_data, ztCamera *gui_camera)
{
	zt_returnValOnNull(theme, false);

	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_WindowFrame                      ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_window_frame");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_WindowFrameDisabled              ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_window_frame_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_PanelFrame                       ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_panel_frame");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_PanelFrameDisabled               ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_panel_frame_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CollapsingPanelFrame             ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_collapsing_panel_frame");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CollapsingPanelFrameDisabled     ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_collapsing_panel_frame_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CollapsingPanelCollapsed         ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_collapsing_panel_collapsed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CollapsingPanelCollapsedDisabled ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_collapsing_panel_collapsed_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonNormal                     ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_button_normal");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonHighlight                  ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_button_highlight");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonPressed                    ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_button_pressed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonDisabled                   ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_button_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonToggleNormal               ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_toggle_button_normal");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonToggleHighlight            ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_toggle_button_highlight");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonTogglePressed              ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_toggle_button_pressed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonToggleDisabled             ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_toggle_button_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonToggleOn                   ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_toggle_button_on");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ButtonToggleOnDisabled           ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_toggle_button_on_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Menu                             ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_menu");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_MenuBar                          ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_menubar");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_MenuBarDisabled                  ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_menubar_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_TextEdit                         ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_textedit");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_TextEditDisabled                 ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_textedit_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarVertBackground          ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_vert_background");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarVertBackgroundDisabled  ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_vert_background_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarVertHandle              ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_vert_handle");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarVertHandleHighlight     ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_vert_handle_highlight");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarVertHandlePressed       ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_vert_handle_pressed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarVertHandleDisabled      ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_vert_handle_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarHorzBackground          ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_horz_background");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarHorzBackgroundDisabled  ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_horz_background_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarHorzHandle              ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_horz_handle");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarHorzHandleHighlight     ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_horz_handle_highlight");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarHorzHandlePressed       ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_horz_handle_pressed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ScrollbarHorzHandleDisabled      ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_scrollbar_horz_handle_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ComboBox                         ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_combobox");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ComboBoxHighlight                ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_combobox_highlight");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ComboBoxPressed                  ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_combobox_pressed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_ComboBoxDisabled                 ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_combobox_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CycleBox                         ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_cyclebox");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CycleBoxHighlight                ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_cyclebox_highlight");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CycleBoxPressed                  ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_cyclebox_pressed");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_CycleBoxDisabled                 ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_cyclebox_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_TabsActive                       ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_tab_active");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_TabsInactive                     ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_tab_inactive");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_TabsDisabled                     ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_tab_disabled");
	theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid                            ] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_solid");

	zt_fize(theme_data->sprite_nine_slice) {
		if (theme_data->sprite_nine_slice[i] == nullptr) {
			zt_logCritical("Missing GUI theme sprite (1.%d)", i);
			return false;
		}
	}

	theme_data->sprite[ztGuiSprite_CheckBox                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox");
	theme_data->sprite[ztGuiSprite_CheckBoxHighlight         ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_highlight");
	theme_data->sprite[ztGuiSprite_CheckBoxPressed           ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_pressed");
	theme_data->sprite[ztGuiSprite_CheckBoxDisabled          ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_disabled");
	theme_data->sprite[ztGuiSprite_CheckBoxOn                ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_on");
	theme_data->sprite[ztGuiSprite_CheckBoxOnHighlight       ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_on_highlight");
	theme_data->sprite[ztGuiSprite_CheckBoxOnPressed         ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_on_pressed");
	theme_data->sprite[ztGuiSprite_CheckBoxOnDisabled        ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_checkbox_on_disabled");
	theme_data->sprite[ztGuiSprite_Radio                     ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio");
	theme_data->sprite[ztGuiSprite_RadioHighlight            ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_highlight");
	theme_data->sprite[ztGuiSprite_RadioPressed              ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_pressed");
	theme_data->sprite[ztGuiSprite_RadioDisabled             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_disabled");
	theme_data->sprite[ztGuiSprite_RadioOn                   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_on");
	theme_data->sprite[ztGuiSprite_RadioOnHighlight          ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_on_highlight");
	theme_data->sprite[ztGuiSprite_RadioOnPressed            ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_on_pressed");
	theme_data->sprite[ztGuiSprite_RadioOnDisabled           ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_radio_on_disabled");
	theme_data->sprite[ztGuiSprite_SliderHorzBar             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_horz_bar");
	theme_data->sprite[ztGuiSprite_SliderHorzBarSet          ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_horz_bar_set");
	theme_data->sprite[ztGuiSprite_SliderHorzBarPressed      ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_horz_bar_pressed");
	theme_data->sprite[ztGuiSprite_SliderHorzBarDisabled     ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_horz_bar_disabled");
	theme_data->sprite[ztGuiSprite_SliderHorzHandle          ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_handle");
	theme_data->sprite[ztGuiSprite_SliderHorzHandleHighlight ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_handle_pressed");
	theme_data->sprite[ztGuiSprite_SliderHorzHandlePressed   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_handle_pressed");
	theme_data->sprite[ztGuiSprite_SliderHorzHandleDisabled  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_empty");
	theme_data->sprite[ztGuiSprite_SliderVertBar             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_vert_bar");
	theme_data->sprite[ztGuiSprite_SliderVertBarSet          ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_vert_bar_set");
	theme_data->sprite[ztGuiSprite_SliderVertBarPressed      ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_vert_bar_pressed");
	theme_data->sprite[ztGuiSprite_SliderVertBarDisabled     ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_vert_bar_disabled");
	theme_data->sprite[ztGuiSprite_SliderVertHandle          ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_handle");
	theme_data->sprite[ztGuiSprite_SliderVertHandleHighlight ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_handle_pressed");
	theme_data->sprite[ztGuiSprite_SliderVertHandlePressed   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_slider_handle_pressed");
	theme_data->sprite[ztGuiSprite_SliderVertHandleDisabled  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_empty");
	theme_data->sprite[ztGuiSprite_Resizer                   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_resizer");
	theme_data->sprite[ztGuiSprite_HorzLine                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_horz_line");
	theme_data->sprite[ztGuiSprite_IconPlus                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_plus");
	theme_data->sprite[ztGuiSprite_IconMinus                 ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_minus");
	theme_data->sprite[ztGuiSprite_IconArrowLeft             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_arrow_left");
	theme_data->sprite[ztGuiSprite_IconArrowRight            ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_arrow_right");
	theme_data->sprite[ztGuiSprite_IconArrowUp               ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_arrow_up");
	theme_data->sprite[ztGuiSprite_IconArrowDown             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_arrow_down");
	theme_data->sprite[ztGuiSprite_IconHandGrab              ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_hand_grab");
	theme_data->sprite[ztGuiSprite_IconHandPoint             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_hand_point");
	theme_data->sprite[ztGuiSprite_IconPencil                ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_pencil");
	theme_data->sprite[ztGuiSprite_IconTrash                 ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_trash");
	theme_data->sprite[ztGuiSprite_IconUndo                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_undo");
	theme_data->sprite[ztGuiSprite_IconCopy                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_copy");
	theme_data->sprite[ztGuiSprite_IconCut                   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_cut");
	theme_data->sprite[ztGuiSprite_IconNew                   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_new");
	theme_data->sprite[ztGuiSprite_IconSave                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_save");
	theme_data->sprite[ztGuiSprite_IconOpen                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_open");
	theme_data->sprite[ztGuiSprite_IconWarning               ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_warning");
	theme_data->sprite[ztGuiSprite_IconMenu                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_menu");
	theme_data->sprite[ztGuiSprite_IconCopyright             ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_copyright");
	theme_data->sprite[ztGuiSprite_IconCheck                 ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_check");
	theme_data->sprite[ztGuiSprite_IconX                     ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_x");
	theme_data->sprite[ztGuiSprite_IconGear                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_gear");
	theme_data->sprite[ztGuiSprite_IconCancel                ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_cancel");
	theme_data->sprite[ztGuiSprite_IconPlay                  ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_play");
	theme_data->sprite[ztGuiSprite_IconPause                 ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_pause");
	theme_data->sprite[ztGuiSprite_IconRewind                ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_rewind");
	theme_data->sprite[ztGuiSprite_IconFastForward           ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_fastforward");
	theme_data->sprite[ztGuiSprite_IconBegin                 ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_begin");
	theme_data->sprite[ztGuiSprite_IconEnd                   ] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_icon_end");

	zt_fize(theme_data->sprite_nine_slice) {
		if (theme_data->sprite_nine_slice[i] == nullptr) {
			zt_logCritical("Missing GUI theme sprite (2.%d)", i);
			return false;
		}
	}


	{
		// default font
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"><description size=\"12\" family=\"Roboto\" style=\"Regular\"/><metrics ascender=\"12\" height=\"14\" descender=\"-3\"/><texture width=\"1024\" height=\"32\" file=\"roboto_regular_12.png\"/><chars><char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"12\" rect_h=\"0\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"4\" id=\"&quot;\" rect_x=\"8\" rect_y=\"2\" rect_h=\"3\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"#\" rect_x=\"13\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"7\" id=\"$\" rect_x=\"22\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"9\" rect_w=\"10\" id=\"%\" rect_x=\"30\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"&amp;\" rect_x=\"41\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"'\" rect_x=\"50\" rect_y=\"2\" rect_h=\"3\"/><char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"(\" rect_x=\"54\" rect_y=\"1\" rect_h=\"14\"/><char offset_x=\"-1\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\")\" rect_x=\"60\" rect_y=\"1\" rect_h=\"14\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"5\" rect_w=\"7\" id=\"*\" rect_x=\"66\" rect_y=\"3\" rect_h=\"6\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"+\" rect_x=\"74\" rect_y=\"4\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"1\" advance=\"3\" rect_w=\"3\" id=\",\" rect_x=\"82\" rect_y=\"11\" rect_h=\"4\"/><char offset_x=\"0\" offset_y=\"4\" advance=\"3\" rect_w=\"5\" id=\"-\" rect_x=\"86\" rect_y=\"8\" rect_h=\"1\"/><char offset_x=\"0\" offset_y=\"1\" advance=\"3\" rect_w=\"3\" id=\".\" rect_x=\"92\" rect_y=\"11\" rect_h=\"1\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"/\" rect_x=\"96\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"0\" rect_x=\"103\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"5\" id=\"1\" rect_x=\"111\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"2\" rect_x=\"117\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"3\" rect_x=\"126\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"4\" rect_x=\"134\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"5\" rect_x=\"144\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"6\" rect_x=\"153\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"7\" rect_x=\"161\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"8\" rect_x=\"169\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"9\" rect_x=\"177\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"3\" rect_w=\"3\" id=\":\" rect_x=\"185\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"2\" rect_w=\"3\" id=\";\" rect_x=\"189\" rect_y=\"5\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"&lt;\" rect_x=\"193\" rect_y=\"5\" rect_h=\"6\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"=\" rect_x=\"200\" rect_y=\"5\" rect_h=\"4\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\">\" rect_x=\"207\" rect_y=\"5\" rect_h=\"6\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"?\" rect_x=\"214\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"12\" rect_w=\"12\" id=\"@\" rect_x=\"221\" rect_y=\"3\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"A\" rect_x=\"234\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"B\" rect_x=\"244\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"C\" rect_x=\"253\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"D\" rect_x=\"263\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"E\" rect_x=\"272\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"8\" id=\"F\" rect_x=\"281\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"G\" rect_x=\"290\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"H\" rect_x=\"299\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"3\" id=\"I\" rect_x=\"308\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"J\" rect_x=\"312\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"K\" rect_x=\"320\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"7\" id=\"L\" rect_x=\"330\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"10\" rect_w=\"10\" id=\"M\" rect_x=\"338\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"N\" rect_x=\"349\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"9\" rect_w=\"9\" id=\"O\" rect_x=\"358\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"P\" rect_x=\"368\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"9\" rect_w=\"9\" id=\"Q\" rect_x=\"377\" rect_y=\"3\" rect_h=\"11\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"R\" rect_x=\"387\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"S\" rect_x=\"396\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"T\" rect_x=\"405\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"U\" rect_x=\"414\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"V\" rect_x=\"423\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"11\" rect_w=\"12\" id=\"W\" rect_x=\"433\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"X\" rect_x=\"446\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"Y\" rect_x=\"456\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"Z\" rect_x=\"466\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"5\" id=\"[\" rect_x=\"474\" rect_y=\"1\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"\\\" rect_x=\"480\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"-1\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"]\" rect_x=\"487\" rect_y=\"1\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"^\" rect_x=\"492\" rect_y=\"3\" rect_h=\"5\"/><char offset_x=\"0\" offset_y=\"0\" advance=\"5\" rect_w=\"7\" id=\"_\" rect_x=\"499\" rect_y=\"12\" rect_h=\"1\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"4\" id=\"`\" rect_x=\"507\" rect_y=\"2\" rect_h=\"2\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"a\" rect_x=\"512\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"6\" rect_w=\"7\" id=\"b\" rect_x=\"521\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"c\" rect_x=\"529\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"d\" rect_x=\"538\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"e\" rect_x=\"546\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"-1\" offset_y=\"10\" advance=\"4\" rect_w=\"6\" id=\"f\" rect_x=\"554\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"g\" rect_x=\"561\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"h\" rect_x=\"569\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"4\" id=\"i\" rect_x=\"577\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"3\" rect_w=\"5\" id=\"j\" rect_x=\"582\" rect_y=\"3\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"6\" rect_w=\"8\" id=\"k\" rect_x=\"588\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"l\" rect_x=\"597\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"11\" rect_w=\"11\" id=\"m\" rect_x=\"601\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"n\" rect_x=\"613\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"o\" rect_x=\"621\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"p\" rect_x=\"630\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"q\" rect_x=\"638\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"8\" advance=\"4\" rect_w=\"5\" id=\"r\" rect_x=\"646\" rect_y=\"4\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"s\" rect_x=\"652\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"4\" rect_w=\"6\" id=\"t\" rect_x=\"660\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"u\" rect_x=\"667\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"v\" rect_x=\"675\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"9\" rect_w=\"10\" id=\"w\" rect_x=\"683\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"x\" rect_x=\"694\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"y\" rect_x=\"702\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"z\" rect_x=\"710\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"6\" id=\"{\" rect_x=\"718\" rect_y=\"2\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"3\" id=\"|\" rect_x=\"725\" rect_y=\"3\" rect_h=\"11\"/><char offset_x=\"-1\" offset_y=\"10\" advance=\"4\" rect_w=\"6\" id=\"}\" rect_x=\"729\" rect_y=\"2\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"6\" advance=\"8\" rect_w=\"9\" id=\"~\" rect_x=\"736\" rect_y=\"6\" rect_h=\"3\"/></chars></font>";
		theme_data->font = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 320));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"14\" family=\"Roboto\" style=\"Regular\"/> <metrics ascender=\"13\" height=\"16\" descender=\"-4\"/> <texture width=\"1024\" height=\"32\" file=\"roboto_regular_14.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"13\" rect_h=\"0\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"5\" rect_w=\"6\" id=\"&quot;\" rect_x=\"8\" rect_y=\"2\" rect_h=\"4\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"9\" id=\"#\" rect_x=\"15\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"8\" rect_w=\"9\" id=\"$\" rect_x=\"25\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"11\" rect_w=\"12\" id=\"%\" rect_x=\"35\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"&amp;\" rect_x=\"48\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"'\" rect_x=\"59\" rect_y=\"2\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"(\" rect_x=\"64\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\")\" rect_x=\"71\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"*\" rect_x=\"78\" rect_y=\"2\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"+\" rect_x=\"87\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\",\" rect_x=\"96\" rect_y=\"11\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"5\" advance=\"5\" rect_w=\"4\" id=\"-\" rect_x=\"101\" rect_y=\"8\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\".\" rect_x=\"106\" rect_y=\"11\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"/\" rect_x=\"111\" rect_y=\"2\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"0\" rect_x=\"119\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"1\" rect_x=\"129\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"2\" rect_x=\"136\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"3\" rect_x=\"145\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"4\" rect_x=\"155\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"5\" rect_x=\"164\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"6\" rect_x=\"174\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"7\" rect_x=\"184\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"8\" rect_x=\"193\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"9\" rect_x=\"203\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"3\" rect_w=\"4\" id=\":\" rect_x=\"213\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"3\" rect_w=\"4\" id=\";\" rect_x=\"218\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"&lt;\" rect_x=\"223\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"=\" rect_x=\"231\" rect_y=\"6\" rect_h=\"5\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\">\" rect_x=\"239\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"?\" rect_x=\"247\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"13\" rect_w=\"14\" id=\"@\" rect_x=\"256\" rect_y=\"2\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"A\" rect_x=\"271\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"B\" rect_x=\"282\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"C\" rect_x=\"292\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"D\" rect_x=\"303\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"E\" rect_x=\"314\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"F\" rect_x=\"324\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"G\" rect_x=\"333\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"H\" rect_x=\"344\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"I\" rect_x=\"355\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"J\" rect_x=\"360\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"10\" id=\"K\" rect_x=\"370\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"L\" rect_x=\"381\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"12\" rect_w=\"13\" id=\"M\" rect_x=\"390\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"N\" rect_x=\"404\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"10\" rect_w=\"11\" id=\"O\" rect_x=\"415\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"P\" rect_x=\"427\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"10\" rect_w=\"11\" id=\"Q\" rect_x=\"438\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"R\" rect_x=\"450\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"S\" rect_x=\"461\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"T\" rect_x=\"472\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"U\" rect_x=\"482\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"V\" rect_x=\"493\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"12\" rect_w=\"14\" id=\"W\" rect_x=\"504\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"X\" rect_x=\"519\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"Y\" rect_x=\"530\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"Z\" rect_x=\"541\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"4\" rect_w=\"5\" id=\"[\" rect_x=\"550\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"\\\" rect_x=\"556\" rect_y=\"2\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"4\" rect_w=\"5\" id=\"]\" rect_x=\"564\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"^\" rect_x=\"570\" rect_y=\"2\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"0\" advance=\"8\" rect_w=\"7\" id=\"_\" rect_x=\"578\" rect_y=\"13\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"`\" rect_x=\"586\" rect_y=\"2\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"a\" rect_x=\"592\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"b\" rect_x=\"602\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"c\" rect_x=\"612\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"d\" rect_x=\"621\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"e\" rect_x=\"631\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"6\" rect_w=\"6\" id=\"f\" rect_x=\"641\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"g\" rect_x=\"648\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"h\" rect_x=\"658\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"i\" rect_x=\"668\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"3\" rect_w=\"5\" id=\"j\" rect_x=\"673\" rect_y=\"2\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"k\" rect_x=\"679\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"l\" rect_x=\"688\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"13\" rect_w=\"14\" id=\"m\" rect_x=\"693\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"n\" rect_x=\"708\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"o\" rect_x=\"718\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"p\" rect_x=\"728\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"q\" rect_x=\"738\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"r\" rect_x=\"748\" rect_y=\"4\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"s\" rect_x=\"755\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"6\" rect_w=\"5\" id=\"t\" rect_x=\"764\" rect_y=\"3\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"u\" rect_x=\"770\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"v\" rect_x=\"780\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"11\" rect_w=\"12\" id=\"w\" rect_x=\"789\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"x\" rect_x=\"802\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"y\" rect_x=\"811\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"z\" rect_x=\"820\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"{\" rect_x=\"828\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"|\" rect_x=\"835\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"}\" rect_x=\"840\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"6\" advance=\"10\" rect_w=\"10\" id=\"~\" rect_x=\"847\" rect_y=\"7\" rect_h=\"4\"/> </chars></font>";
		theme_data->font_large = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 340));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"12\" family=\"Roboto\" style=\"Bold\"/> <metrics ascender=\"12\" height=\"14\" descender=\"-3\"/> <texture width=\"1024\" height=\"32\" file=\"roboto_bold_12.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"12\" rect_h=\"0\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"5\" rect_w=\"4\" id=\"&quot;\" rect_x=\"8\" rect_y=\"2\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"#\" rect_x=\"13\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"7\" id=\"$\" rect_x=\"22\" rect_y=\"1\" rect_h=\"12\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"10\" rect_w=\"9\" id=\"%\" rect_x=\"30\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"9\" id=\"&amp;\" rect_x=\"40\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"'\" rect_x=\"50\" rect_y=\"2\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"(\" rect_x=\"54\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\")\" rect_x=\"60\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"-1\" offset_y=\"9\" advance=\"5\" rect_w=\"7\" id=\"*\" rect_x=\"66\" rect_y=\"3\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"+\" rect_x=\"74\" rect_y=\"4\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\",\" rect_x=\"82\" rect_y=\"10\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"5\" rect_w=\"4\" id=\"-\" rect_x=\"87\" rect_y=\"6\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\".\" rect_x=\"92\" rect_y=\"10\" rect_h=\"2\"/>  <char offset_x=\"-1\" offset_y=\"9\" advance=\"4\" rect_w=\"7\" id=\"/\" rect_x=\"97\" rect_y=\"3\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"0\" rect_x=\"105\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"5\" id=\"1\" rect_x=\"113\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"2\" rect_x=\"119\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"3\" rect_x=\"127\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"4\" rect_x=\"135\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"5\" rect_x=\"144\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"6\" rect_x=\"153\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"7\" rect_x=\"161\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"8\" rect_x=\"169\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"9\" rect_x=\"177\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"3\" rect_w=\"4\" id=\":\" rect_x=\"185\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"3\" rect_w=\"4\" id=\";\" rect_x=\"190\" rect_y=\"5\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"6\" id=\"&lt;\" rect_x=\"195\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"=\" rect_x=\"202\" rect_y=\"5\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\">\" rect_x=\"209\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"7\" id=\"?\" rect_x=\"216\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"12\" rect_w=\"11\" id=\"@\" rect_x=\"224\" rect_y=\"3\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"10\" id=\"A\" rect_x=\"236\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"B\" rect_x=\"247\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"C\" rect_x=\"255\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"D\" rect_x=\"264\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"E\" rect_x=\"273\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"F\" rect_x=\"281\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"G\" rect_x=\"289\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"H\" rect_x=\"298\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"4\" rect_w=\"3\" id=\"I\" rect_x=\"307\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"J\" rect_x=\"311\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"K\" rect_x=\"319\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"L\" rect_x=\"328\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"11\" rect_w=\"10\" id=\"M\" rect_x=\"336\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"N\" rect_x=\"347\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"O\" rect_x=\"356\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"P\" rect_x=\"365\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"Q\" rect_x=\"374\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"R\" rect_x=\"383\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"S\" rect_x=\"392\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"T\" rect_x=\"402\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"U\" rect_x=\"411\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"V\" rect_x=\"420\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"11\" rect_w=\"12\" id=\"W\" rect_x=\"430\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"X\" rect_x=\"443\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"Y\" rect_x=\"453\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"Z\" rect_x=\"463\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"4\" id=\"[\" rect_x=\"472\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"7\" id=\"\\\" rect_x=\"477\" rect_y=\"3\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"]\" rect_x=\"485\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"^\" rect_x=\"490\" rect_y=\"3\" rect_h=\"5\"/>  <char offset_x=\"0\" offset_y=\"1\" advance=\"6\" rect_w=\"6\" id=\"_\" rect_x=\"497\" rect_y=\"11\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"5\" id=\"`\" rect_x=\"504\" rect_y=\"2\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"a\" rect_x=\"510\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"b\" rect_x=\"518\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"c\" rect_x=\"526\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"d\" rect_x=\"534\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"e\" rect_x=\"542\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"5\" rect_w=\"5\" id=\"f\" rect_x=\"550\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"g\" rect_x=\"556\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"h\" rect_x=\"564\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"i\" rect_x=\"572\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"-1\" offset_y=\"10\" advance=\"3\" rect_w=\"5\" id=\"j\" rect_x=\"576\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"k\" rect_x=\"582\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"l\" rect_x=\"590\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"11\" rect_w=\"11\" id=\"m\" rect_x=\"594\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"n\" rect_x=\"606\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"o\" rect_x=\"614\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"p\" rect_x=\"622\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"q\" rect_x=\"630\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"5\" rect_w=\"5\" id=\"r\" rect_x=\"638\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"s\" rect_x=\"644\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"6\" rect_w=\"6\" id=\"t\" rect_x=\"652\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"u\" rect_x=\"659\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"v\" rect_x=\"667\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"9\" rect_w=\"10\" id=\"w\" rect_x=\"675\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"8\" id=\"x\" rect_x=\"686\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"8\" id=\"y\" rect_x=\"695\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"z\" rect_x=\"704\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"{\" rect_x=\"711\" rect_y=\"1\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"3\" id=\"|\" rect_x=\"717\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"}\" rect_x=\"721\" rect_y=\"1\" rect_h=\"13\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"8\" rect_w=\"8\" id=\"~\" rect_x=\"727\" rect_y=\"6\" rect_h=\"4\"/> </chars></font>";
		theme_data->font_bold = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 361));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"14\" family=\"Roboto\" style=\"Bold\"/> <metrics ascender=\"13\" height=\"16\" descender=\"-4\"/> <texture width=\"1024\" height=\"32\" file=\"roboto_bold_14.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"14\" rect_h=\"0\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"!\" rect_x=\"3\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"&quot;\" rect_x=\"9\" rect_y=\"3\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"#\" rect_x=\"15\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"9\" rect_w=\"9\" id=\"$\" rect_x=\"25\" rect_y=\"2\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"11\" rect_w=\"11\" id=\"%\" rect_x=\"35\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"10\" id=\"&amp;\" rect_x=\"47\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"3\" rect_w=\"3\" id=\"'\" rect_x=\"58\" rect_y=\"3\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"(\" rect_x=\"62\" rect_y=\"2\" rect_h=\"16\"/>  <char offset_x=\"-1\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\")\" rect_x=\"69\" rect_y=\"2\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"8\" id=\"*\" rect_x=\"76\" rect_y=\"3\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"+\" rect_x=\"85\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"4\" rect_w=\"4\" id=\",\" rect_x=\"94\" rect_y=\"12\" rect_h=\"5\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"6\" rect_w=\"5\" id=\"-\" rect_x=\"99\" rect_y=\"8\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"4\" rect_w=\"5\" id=\".\" rect_x=\"105\" rect_y=\"12\" rect_h=\"2\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"5\" rect_w=\"8\" id=\"/\" rect_x=\"111\" rect_y=\"3\" rect_h=\"12\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"0\" rect_x=\"120\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"6\" id=\"1\" rect_x=\"129\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"2\" rect_x=\"136\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"3\" rect_x=\"145\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"9\" id=\"4\" rect_x=\"154\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"5\" rect_x=\"164\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"6\" rect_x=\"174\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"7\" rect_x=\"183\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"8\" rect_x=\"192\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"9\" rect_x=\"201\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"4\" rect_w=\"5\" id=\":\" rect_x=\"210\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"4\" rect_w=\"4\" id=\";\" rect_x=\"216\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"&lt;\" rect_x=\"221\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"=\" rect_x=\"229\" rect_y=\"7\" rect_h=\"5\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\">\" rect_x=\"237\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"7\" rect_w=\"7\" id=\"?\" rect_x=\"245\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"13\" rect_w=\"13\" id=\"@\" rect_x=\"253\" rect_y=\"3\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"11\" id=\"A\" rect_x=\"267\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"B\" rect_x=\"279\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"C\" rect_x=\"288\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"D\" rect_x=\"299\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"E\" rect_x=\"309\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"F\" rect_x=\"318\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"G\" rect_x=\"327\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"H\" rect_x=\"337\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"3\" id=\"I\" rect_x=\"347\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"J\" rect_x=\"351\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"K\" rect_x=\"360\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"L\" rect_x=\"371\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"12\" rect_w=\"11\" id=\"M\" rect_x=\"380\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"N\" rect_x=\"392\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"O\" rect_x=\"402\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"9\" id=\"P\" rect_x=\"412\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"Q\" rect_x=\"422\" rect_y=\"3\" rect_h=\"13\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"R\" rect_x=\"432\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"S\" rect_x=\"442\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"T\" rect_x=\"453\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"U\" rect_x=\"463\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"11\" id=\"V\" rect_x=\"473\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"12\" rect_w=\"14\" id=\"W\" rect_x=\"485\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"X\" rect_x=\"500\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"8\" rect_w=\"11\" id=\"Y\" rect_x=\"511\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"Z\" rect_x=\"523\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"13\" advance=\"4\" rect_w=\"4\" id=\"[\" rect_x=\"533\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"8\" id=\"\\\" rect_x=\"538\" rect_y=\"3\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"13\" advance=\"4\" rect_w=\"4\" id=\"]\" rect_x=\"547\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"^\" rect_x=\"552\" rect_y=\"3\" rect_h=\"6\"/>  <char offset_x=\"0\" offset_y=\"0\" advance=\"7\" rect_w=\"7\" id=\"_\" rect_x=\"560\" rect_y=\"14\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"`\" rect_x=\"568\" rect_y=\"3\" rect_h=\"2\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"a\" rect_x=\"574\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"b\" rect_x=\"583\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"c\" rect_x=\"592\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"d\" rect_x=\"601\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"e\" rect_x=\"610\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"7\" rect_w=\"6\" id=\"f\" rect_x=\"619\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"9\" rect_w=\"8\" id=\"g\" rect_x=\"626\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"h\" rect_x=\"635\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"4\" id=\"i\" rect_x=\"643\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"j\" rect_x=\"648\" rect_y=\"3\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"k\" rect_x=\"654\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"3\" id=\"l\" rect_x=\"663\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"12\" rect_w=\"12\" id=\"m\" rect_x=\"667\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"n\" rect_x=\"680\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"9\" rect_w=\"8\" id=\"o\" rect_x=\"688\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"p\" rect_x=\"697\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"9\" rect_w=\"8\" id=\"q\" rect_x=\"706\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"6\" rect_w=\"5\" id=\"r\" rect_x=\"715\" rect_y=\"5\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"s\" rect_x=\"721\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"6\" rect_w=\"5\" id=\"t\" rect_x=\"730\" rect_y=\"4\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"u\" rect_x=\"736\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"v\" rect_x=\"744\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"10\" rect_w=\"12\" id=\"w\" rect_x=\"753\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"9\" id=\"x\" rect_x=\"766\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"9\" id=\"y\" rect_x=\"776\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"z\" rect_x=\"786\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"13\" advance=\"5\" rect_w=\"6\" id=\"{\" rect_x=\"794\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"3\" id=\"|\" rect_x=\"801\" rect_y=\"3\" rect_h=\"13\"/>  <char offset_x=\"-1\" offset_y=\"13\" advance=\"5\" rect_w=\"6\" id=\"}\" rect_x=\"805\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"9\" rect_w=\"9\" id=\"~\" rect_x=\"812\" rect_y=\"8\" rect_h=\"3\"/> </chars></font>";
		theme_data->font_large_bold = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 383));
	}

	{
		// monospaced default
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"><description size=\"12\" family=\"Liberation Mono\" style=\"Regular\"/><metrics ascender=\"10\" height=\"14\" descender=\"-4\"/><texture width=\"1024\" height=\"16\" file=\"liberation_mono_regular_12.png\"/><chars><char offset_x=\"0\" offset_y=\"0\" advance=\"7\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"10\" rect_h=\"0\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"3\" id=\"!\" rect_x=\"3\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"&quot;\" rect_x=\"7\" rect_y=\"1\" rect_h=\"4\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"#\" rect_x=\"14\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"$\" rect_x=\"23\" rect_y=\"1\" rect_h=\"10\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"%\" rect_x=\"31\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"&amp;\" rect_x=\"41\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"3\" id=\"'\" rect_x=\"51\" rect_y=\"1\" rect_h=\"4\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"(\" rect_x=\"55\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"5\" id=\")\" rect_x=\"62\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"*\" rect_x=\"68\" rect_y=\"1\" rect_h=\"5\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"+\" rect_x=\"75\" rect_y=\"3\" rect_h=\"6\"/><char offset_x=\"1\" offset_y=\"2\" advance=\"7\" rect_w=\"5\" id=\",\" rect_x=\"84\" rect_y=\"8\" rect_h=\"4\"/><char offset_x=\"2\" offset_y=\"4\" advance=\"7\" rect_w=\"4\" id=\"-\" rect_x=\"90\" rect_y=\"6\" rect_h=\"1\"/><char offset_x=\"2\" offset_y=\"2\" advance=\"7\" rect_w=\"3\" id=\".\" rect_x=\"95\" rect_y=\"8\" rect_h=\"2\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"/\" rect_x=\"99\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"0\" rect_x=\"108\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"1\" rect_x=\"117\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"2\" rect_x=\"126\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"3\" rect_x=\"135\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"4\" rect_x=\"143\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"5\" rect_x=\"153\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"6\" rect_x=\"161\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"7\" rect_x=\"169\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"8\" rect_x=\"177\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"9\" rect_x=\"185\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"2\" offset_y=\"7\" advance=\"7\" rect_w=\"3\" id=\":\" rect_x=\"193\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"2\" offset_y=\"7\" advance=\"7\" rect_w=\"4\" id=\";\" rect_x=\"197\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"7\" id=\"&lt;\" rect_x=\"202\" rect_y=\"2\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"6\" advance=\"7\" rect_w=\"8\" id=\"=\" rect_x=\"210\" rect_y=\"4\" rect_h=\"4\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"7\" id=\">\" rect_x=\"219\" rect_y=\"2\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"?\" rect_x=\"227\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"@\" rect_x=\"236\" rect_y=\"1\" rect_h=\"11\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"A\" rect_x=\"246\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"B\" rect_x=\"256\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"C\" rect_x=\"265\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"D\" rect_x=\"274\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"E\" rect_x=\"283\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"F\" rect_x=\"292\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"G\" rect_x=\"301\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"H\" rect_x=\"310\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"I\" rect_x=\"318\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"J\" rect_x=\"325\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"K\" rect_x=\"332\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"L\" rect_x=\"342\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"M\" rect_x=\"350\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"N\" rect_x=\"359\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"O\" rect_x=\"367\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"P\" rect_x=\"376\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"Q\" rect_x=\"385\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"R\" rect_x=\"395\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"S\" rect_x=\"405\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"T\" rect_x=\"414\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"U\" rect_x=\"423\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"V\" rect_x=\"431\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"W\" rect_x=\"441\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"X\" rect_x=\"451\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"Y\" rect_x=\"460\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"Z\" rect_x=\"469\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"[\" rect_x=\"478\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"\\\" rect_x=\"485\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"5\" id=\"]\" rect_x=\"494\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"^\" rect_x=\"500\" rect_y=\"1\" rect_h=\"6\"/><char offset_x=\"-1\" offset_y=\"-1\" advance=\"7\" rect_w=\"10\" id=\"_\" rect_x=\"509\" rect_y=\"11\" rect_h=\"1\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"4\" id=\"`\" rect_x=\"520\" rect_y=\"1\" rect_h=\"2\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"a\" rect_x=\"525\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"b\" rect_x=\"534\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"c\" rect_x=\"542\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"d\" rect_x=\"551\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"e\" rect_x=\"559\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"f\" rect_x=\"568\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"g\" rect_x=\"576\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"h\" rect_x=\"584\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"i\" rect_x=\"592\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"j\" rect_x=\"601\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"k\" rect_x=\"608\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"l\" rect_x=\"617\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"m\" rect_x=\"626\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"n\" rect_x=\"634\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"o\" rect_x=\"642\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"p\" rect_x=\"651\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"q\" rect_x=\"659\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"7\" id=\"r\" rect_x=\"667\" rect_y=\"2\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"s\" rect_x=\"675\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"t\" rect_x=\"683\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"u\" rect_x=\"691\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"v\" rect_x=\"699\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"9\" id=\"w\" rect_x=\"708\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"x\" rect_x=\"718\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"y\" rect_x=\"727\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"z\" rect_x=\"736\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"{\" rect_x=\"744\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"3\" id=\"|\" rect_x=\"752\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"}\" rect_x=\"756\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"5\" advance=\"7\" rect_w=\"7\" id=\"~\" rect_x=\"764\" rect_y=\"5\" rect_h=\"2\"/></chars></font>";
		theme_data->font_monospace = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 455));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"14\" family=\"Liberation Mono\" style=\"Regular\"/> <metrics ascender=\"12\" height=\"16\" descender=\"-5\"/> <texture width=\"1024\" height=\"32\" file=\"liberation_mono_regular_14.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"8\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"12\" rect_h=\"0\"/>  <char offset_x=\"3\" offset_y=\"10\" advance=\"8\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"&quot;\" rect_x=\"8\" rect_y=\"1\" rect_h=\"5\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"#\" rect_x=\"16\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"10\" id=\"$\" rect_x=\"26\" rect_y=\"1\" rect_h=\"12\"/>  <char offset_x=\"-1\" offset_y=\"10\" advance=\"8\" rect_w=\"11\" id=\"%\" rect_x=\"37\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"&amp;\" rect_x=\"49\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"3\" offset_y=\"11\" advance=\"8\" rect_w=\"4\" id=\"'\" rect_x=\"60\" rect_y=\"1\" rect_h=\"5\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"(\" rect_x=\"65\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\")\" rect_x=\"72\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"*\" rect_x=\"79\" rect_y=\"1\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"+\" rect_x=\"88\" rect_y=\"4\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"2\" advance=\"8\" rect_w=\"5\" id=\",\" rect_x=\"97\" rect_y=\"10\" rect_h=\"5\"/>  <char offset_x=\"2\" offset_y=\"4\" advance=\"8\" rect_w=\"5\" id=\"-\" rect_x=\"103\" rect_y=\"8\" rect_h=\"1\"/>  <char offset_x=\"3\" offset_y=\"3\" advance=\"8\" rect_w=\"4\" id=\".\" rect_x=\"109\" rect_y=\"9\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"/\" rect_x=\"114\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"0\" rect_x=\"124\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"1\" rect_x=\"134\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"2\" rect_x=\"144\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"3\" rect_x=\"153\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"4\" rect_x=\"163\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"5\" rect_x=\"172\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"6\" rect_x=\"182\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"7\" id=\"7\" rect_x=\"192\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"8\" rect_x=\"200\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"9\" rect_x=\"210\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"3\" offset_y=\"8\" advance=\"8\" rect_w=\"4\" id=\":\" rect_x=\"220\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"2\" offset_y=\"8\" advance=\"8\" rect_w=\"5\" id=\";\" rect_x=\"225\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"&lt;\" rect_x=\"231\" rect_y=\"3\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\">\" rect_x=\"240\" rect_y=\"3\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"?\" rect_x=\"249\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"11\" id=\"@\" rect_x=\"259\" rect_y=\"1\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"A\" rect_x=\"271\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"B\" rect_x=\"282\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"C\" rect_x=\"292\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"D\" rect_x=\"302\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"E\" rect_x=\"312\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"F\" rect_x=\"322\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"G\" rect_x=\"331\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"H\" rect_x=\"341\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"7\" id=\"I\" rect_x=\"351\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"J\" rect_x=\"359\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"K\" rect_x=\"368\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"L\" rect_x=\"379\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"M\" rect_x=\"388\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"N\" rect_x=\"398\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"O\" rect_x=\"408\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"P\" rect_x=\"419\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"Q\" rect_x=\"429\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"R\" rect_x=\"440\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"S\" rect_x=\"450\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"T\" rect_x=\"460\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"U\" rect_x=\"469\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"V\" rect_x=\"479\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"W\" rect_x=\"490\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"X\" rect_x=\"501\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"Y\" rect_x=\"512\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"Z\" rect_x=\"523\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"[\" rect_x=\"532\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"\\\" rect_x=\"539\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"]\" rect_x=\"549\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"^\" rect_x=\"556\" rect_y=\"2\" rect_h=\"7\"/>  <char offset_x=\"-1\" offset_y=\"-1\" advance=\"8\" rect_w=\"11\" id=\"_\" rect_x=\"566\" rect_y=\"13\" rect_h=\"1\"/>  <char offset_x=\"3\" offset_y=\"11\" advance=\"8\" rect_w=\"4\" id=\"`\" rect_x=\"578\" rect_y=\"1\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"10\" id=\"a\" rect_x=\"583\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"b\" rect_x=\"594\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"c\" rect_x=\"604\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"d\" rect_x=\"614\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"e\" rect_x=\"624\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"f\" rect_x=\"634\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"g\" rect_x=\"643\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"h\" rect_x=\"653\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"i\" rect_x=\"663\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"j\" rect_x=\"672\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"k\" rect_x=\"680\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"l\" rect_x=\"689\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"10\" id=\"m\" rect_x=\"698\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"n\" rect_x=\"709\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"o\" rect_x=\"719\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"p\" rect_x=\"729\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"q\" rect_x=\"739\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"r\" rect_x=\"749\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"s\" rect_x=\"757\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"7\" id=\"t\" rect_x=\"767\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"u\" rect_x=\"775\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"v\" rect_x=\"785\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"-1\" offset_y=\"8\" advance=\"8\" rect_w=\"11\" id=\"w\" rect_x=\"795\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"x\" rect_x=\"807\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"y\" rect_x=\"817\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"z\" rect_x=\"827\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"{\" rect_x=\"835\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"3\" offset_y=\"11\" advance=\"8\" rect_w=\"4\" id=\"|\" rect_x=\"844\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"}\" rect_x=\"849\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"8\" rect_w=\"8\" id=\"~\" rect_x=\"857\" rect_y=\"6\" rect_h=\"2\"/> </chars></font>";
		theme_data->font_monospace_large = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 473));
	}

	theme->theme_data = theme_data;

	theme->get_rvalue       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetRValue);
	theme->get_ivalue       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetIValue);
	theme->update_item      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeUpdateItem);
	theme->update_subitem   = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeSubitem);
	theme->size_item        = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeSizeItem);
	theme->render_item      = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeRenderItem);
	theme->postrender_item  = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemePostRenderItem);
	theme->pass_begin       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeRenderPassBegin);
	theme->pass_end         = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeRenderPassEnd);

	theme->flags |= ztGuiThemeFlags_SeparatePasses;

	return true;
}

// ================================================================================================================================================================================================

#ifndef ZT_GUI_DEFAULT_THEME_SPRITE_MANAGER_MAX_SPRITES
#define ZT_GUI_DEFAULT_THEME_SPRITE_MANAGER_MAX_SPRITES ztGuiSpriteNineSlice_MAX + ztGuiSprite_MAX + 128
#endif

// ================================================================================================================================================================================================

bool zt_guiDefaultThemeMake(ztGuiTheme *theme, ztCamera *gui_camera)
{
	zt_returnValOnNull(theme, false);
	zt_returnValOnNull(gui_camera, false);

	ztGuiThemeData *theme_data = zt_mallocStruct(ztGuiThemeData);

	i32 texture_file_data_size = 0;
	void *texture_file_data = _zt_guiDefaultThemeLoadImageFile(&texture_file_data_size, zt_memGetTempArena());

	theme_data->texture = zt_textureMakeFromFileData(texture_file_data, texture_file_data_size, ztTextureFlags_PixelPerfect);

	zt_freeArena(texture_file_data, zt_memGetTempArena());

	if (theme_data->texture == ztInvalidID) {
		return false;
	}

	i32 sprite_file_data_size = 0;
	void *sprite_file_data = _zt_guiDefaultThemeLoadImageSpriteFile(&sprite_file_data_size, zt_memGetTempArena());

	zt_spriteManagerMake(&theme_data->sprite_manager, ZT_GUI_DEFAULT_THEME_SPRITE_MANAGER_MAX_SPRITES);

	bool result = zt_spriteManagerLoad(&theme_data->sprite_manager, sprite_file_data, sprite_file_data_size, theme_data->texture);
	zt_freeArena(sprite_file_data, zt_memGetTempArena());
	if (!result) {
		return false;
	}

	return _zt_guiDefaultThemeMakeBase(theme, theme_data, gui_camera);
}

// ================================================================================================================================================================================================

bool zt_guiDefaultThemeMake(ztGuiTheme *theme, ztCamera *gui_camera, ztAssetManager *asset_manager, const char *gui_texture, const char *gui_sprite_file)
{
	zt_returnValOnNull(theme, false);
	zt_returnValOnNull(gui_camera, false);
	zt_returnValOnNull(asset_manager, false);

	ztGuiThemeData *theme_data = zt_mallocStruct(ztGuiThemeData);

	theme_data->texture = zt_textureMake(asset_manager, zt_assetLoad(asset_manager, gui_texture), ztTextureFlags_PixelPerfect);
	if (theme_data->texture == ztInvalidID) {
		return false;
	}

	zt_spriteManagerMake(&theme_data->sprite_manager, ZT_GUI_DEFAULT_THEME_SPRITE_MANAGER_MAX_SPRITES);

	if (!zt_spriteManagerLoad(&theme_data->sprite_manager, asset_manager, zt_assetLoad(asset_manager, gui_sprite_file), theme_data->texture)) {
		return false;
	}

	return _zt_guiDefaultThemeMakeBase(theme, theme_data, gui_camera);
}

// ================================================================================================================================================================================================

void zt_guiDefaultThemeFree(ztGuiTheme *theme)
{
	if (theme == nullptr) {
		return;
	}

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	zt_fontFree(theme_data->font);
	zt_fontFree(theme_data->font_bold);
	zt_fontFree(theme_data->font_large);
	zt_fontFree(theme_data->font_large_bold);
	zt_fontFree(theme_data->font_monospace);
	zt_fontFree(theme_data->font_monospace_large);

	zt_fize(theme_data->sprite) {
		theme_data->sprite[i] = nullptr;
	}
	zt_fize(theme_data->sprite_nine_slice) {
		theme_data->sprite_nine_slice[i] = nullptr;
	}

	zt_spriteManagerFree(&theme_data->sprite_manager);
	zt_textureFree(theme_data->texture);

	zt_free(theme_data);
}

// ================================================================================================================================================================================================

void zt_guiDefaultThemeWriteToDisk(const char *gui_texture, const char *gui_sprite_file)
{
	i32 data_size = 0;
	void *data = _zt_guiDefaultThemeLoadImageFile(&data_size, zt_memGetTempArena());
	zt_writeEntireFile(gui_texture, data, data_size, zt_memGetTempArena());
	zt_freeArena(data, zt_memGetTempArena());

	data = _zt_guiDefaultThemeLoadImageSpriteFile(&data_size, zt_memGetTempArena());
	zt_writeEntireFile(gui_sprite_file, data, data_size, zt_memGetTempArena());
	zt_freeArena(data, zt_memGetTempArena());
}


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

#endif // include guard
#endif // implementation
