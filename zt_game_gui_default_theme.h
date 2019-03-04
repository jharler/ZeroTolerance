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
	ztGuiSpriteNineSlice_SliderHorzBar,
	ztGuiSpriteNineSlice_SliderHorzBarSet,
	ztGuiSpriteNineSlice_SliderHorzBarPressed,
	ztGuiSpriteNineSlice_SliderHorzBarDisabled,
	ztGuiSpriteNineSlice_SliderVertBar,
	ztGuiSpriteNineSlice_SliderVertBarSet,
	ztGuiSpriteNineSlice_SliderVertBarPressed,
	ztGuiSpriteNineSlice_SliderVertBarDisabled,
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
	ztGuiSpriteNineSlice_Spinner,
	ztGuiSpriteNineSlice_SpinnerUpHighlight,
	ztGuiSpriteNineSlice_SpinnerUpPressed,
	ztGuiSpriteNineSlice_SpinnerDownHighlight,
	ztGuiSpriteNineSlice_SpinnerDownPressed,
	ztGuiSpriteNineSlice_SpinnerText,
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
	ztGuiSprite_SliderHorzHandle,
	ztGuiSprite_SliderHorzHandleHighlight,
	ztGuiSprite_SliderHorzHandlePressed,
	ztGuiSprite_SliderHorzHandleDisabled,
	ztGuiSprite_SliderVertHandle,
	ztGuiSprite_SliderVertHandleHighlight,
	ztGuiSprite_SliderVertHandlePressed,
	ztGuiSprite_SliderVertHandleDisabled,
	ztGuiSprite_SpinnerArrowUp,
	ztGuiSprite_SpinnerArrowUpPressed,
	ztGuiSprite_SpinnerArrowDown,
	ztGuiSprite_SpinnerArrowDownPressed,
	ztGuiSprite_ResizerHorz,
	ztGuiSprite_ResizerVert,
	ztGuiSprite_HorzLine,
	ztGuiSprite_IconPlus,
	ztGuiSprite_IconMinus,
	ztGuiSprite_IconArrowLeft,
	ztGuiSprite_IconArrowRight,
	ztGuiSprite_IconArrowUp,
	ztGuiSprite_IconArrowDown,
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

	ztGuiSprite_IconBrush,
	ztGuiSprite_IconPenNib,
	ztGuiSprite_IconPen,
	ztGuiSprite_IconPaintBrush,
	ztGuiSprite_IconPaintBucket,
	ztGuiSprite_IconVisible,
	ztGuiSprite_IconNotAllowed,
	ztGuiSprite_IconSearch,
	ztGuiSprite_IconZoomOut,
	ztGuiSprite_IconZoomIn,
	ztGuiSprite_IconWand,
	ztGuiSprite_IconReticle,
	ztGuiSprite_IconFlag,
	ztGuiSprite_IconPaperclip,
	ztGuiSprite_IconNodes,
	ztGuiSprite_IconLink,
	ztGuiSprite_IconTag,
	ztGuiSprite_IconLock,
	ztGuiSprite_IconUnlock,
	ztGuiSprite_IconPushpin,
	ztGuiSprite_IconPushpin2,
	ztGuiSprite_IconShield,
	ztGuiSprite_IconKey,
	ztGuiSprite_IconFlame,
	ztGuiSprite_IconTarget,
	ztGuiSprite_IconBolt,
	ztGuiSprite_IconClock,
	ztGuiSprite_IconTicks,
	ztGuiSprite_IconHourglass,
	ztGuiSprite_IconAlarm,
	ztGuiSprite_IconLargePage,
	ztGuiSprite_IconBanner,
	ztGuiSprite_IconClassicPhone,
	ztGuiSprite_IconCellPhone,
	ztGuiSprite_IconMail,
	ztGuiSprite_IconMailOpen,
	ztGuiSprite_IconMailFile,
	ztGuiSprite_IconInbox,
	ztGuiSprite_IconInboxOut,
	ztGuiSprite_IconInboxIn,
	ztGuiSprite_IconCamera,
	ztGuiSprite_IconFilmRoll,
	ztGuiSprite_IconComment,
	ztGuiSprite_IconComment2,
	ztGuiSprite_IconComment3,
	ztGuiSprite_IconDiscussion,
	ztGuiSprite_IconRSS,
	ztGuiSprite_IconRSS2,
	ztGuiSprite_IconConnected,
	ztGuiSprite_IconBell,
	ztGuiSprite_IconMegaphone,
	ztGuiSprite_IconContacts,
	ztGuiSprite_IconContacts2,
	ztGuiSprite_IconPerson,
	ztGuiSprite_IconPerson2,
	ztGuiSprite_IconPersonMinus,
	ztGuiSprite_IconPersonPlus,
	ztGuiSprite_IconPersonMinus2,
	ztGuiSprite_IconPersonTimes,
	ztGuiSprite_IconContacts3,
	ztGuiSprite_IconPeople,
	ztGuiSprite_IconBuildings,
	ztGuiSprite_IconCalendar,
	ztGuiSprite_IconCalendar2,
	ztGuiSprite_IconFile,
	ztGuiSprite_IconFileText,
	ztGuiSprite_IconFileCopy,
	ztGuiSprite_IconFolder,
	ztGuiSprite_IconFolderLock,
	ztGuiSprite_IconFolderPlus,
	ztGuiSprite_IconFolderMinus,
	ztGuiSprite_IconFilePlus,
	ztGuiSprite_IconFileMinus,
	ztGuiSprite_IconFileWrite,
	ztGuiSprite_IconFileDownload,
	ztGuiSprite_IconHouse,
	ztGuiSprite_IconHouse2,
	ztGuiSprite_IconSignpost,
	ztGuiSprite_IconGlobe,
	ztGuiSprite_IconMap,
	ztGuiSprite_IconMapPoint,
	ztGuiSprite_IconConstruction,
	ztGuiSprite_IconLifesaver,
	ztGuiSprite_IconConstruction2,
	ztGuiSprite_IconBlocks,
	ztGuiSprite_IconBlock,
	ztGuiSprite_IconHierarchy,
	ztGuiSprite_IconLayers,
	ztGuiSprite_IconArrowStyleLeft,
	ztGuiSprite_IconArrowStyleLeft2,
	ztGuiSprite_IconArrowStyleLeft3,
	ztGuiSprite_IconArrowStyleLeft4,
	ztGuiSprite_IconArrowStyleLeft5,
	ztGuiSprite_IconArrowStyleLeft6,
	ztGuiSprite_IconArrowStyleLeft7,
	ztGuiSprite_IconArrowStyleLeft8,
	ztGuiSprite_IconArrowStyleLeft9,
	ztGuiSprite_IconArrowStyleLeft10,
	ztGuiSprite_IconArrowStyleLeft11,
	ztGuiSprite_IconArrowStyleLeft12,
	ztGuiSprite_IconArrowStyleLeft13,
	ztGuiSprite_IconArrowStyleRight,
	ztGuiSprite_IconArrowStyleRight2,
	ztGuiSprite_IconArrowStyleRight3,
	ztGuiSprite_IconArrowStyleRight4,
	ztGuiSprite_IconArrowStyleRight5,
	ztGuiSprite_IconArrowStyleRight6,
	ztGuiSprite_IconArrowStyleRight7,
	ztGuiSprite_IconArrowStyleRight8,
	ztGuiSprite_IconArrowStyleRight9,
	ztGuiSprite_IconArrowStyleRight10,
	ztGuiSprite_IconArrowStyleRight11,
	ztGuiSprite_IconArrowStyleRight12,
	ztGuiSprite_IconArrowStyleRight13,
	ztGuiSprite_IconCart,
	ztGuiSprite_IconCart2,
	ztGuiSprite_IconShoppingBag,
	ztGuiSprite_IconCart3,
	ztGuiSprite_IconTruck,
	ztGuiSprite_IconGift,
	ztGuiSprite_IconGift2,
	ztGuiSprite_IconCreditCard,
	ztGuiSprite_IconCreditCard2,
	ztGuiSprite_IconStack,
	ztGuiSprite_IconCalculator,
	ztGuiSprite_IconMonument,
	ztGuiSprite_IconSpeedomter,
	ztGuiSprite_IconGears,
	ztGuiSprite_IconRepair,
	ztGuiSprite_IconRepair2,
	ztGuiSprite_IconRepair3,
	ztGuiSprite_IconTools,
	ztGuiSprite_IconLightSwitch,
	ztGuiSprite_IconControls,
	ztGuiSprite_IconGrid,
	ztGuiSprite_IconGrid2,
	ztGuiSprite_IconMenu2,
	ztGuiSprite_IconBook,
	ztGuiSprite_IconBook2,
	ztGuiSprite_IconCalendar3,
	ztGuiSprite_IconBook3,
	ztGuiSprite_IconCamera2,
	ztGuiSprite_IconCamera3,
	ztGuiSprite_IconGraph,
	ztGuiSprite_IconGraph2,
	ztGuiSprite_IconImage,
	ztGuiSprite_IconImages,
	ztGuiSprite_IconPresentation,
	ztGuiSprite_IconFilm,
	ztGuiSprite_IconContainerMinus,
	ztGuiSprite_IconContainerDown,
	ztGuiSprite_IconContainerUp,
	ztGuiSprite_IconMusic,
	ztGuiSprite_IconOpenBook,
	ztGuiSprite_IconOpenBook2,
	ztGuiSprite_IconFilmClapper,
	ztGuiSprite_IconDbase,
	ztGuiSprite_IconScreen,
	ztGuiSprite_IconScreen2,
	ztGuiSprite_IconScreen3,
	ztGuiSprite_IconScreen4,
	ztGuiSprite_IconBatteryEmpty,
	ztGuiSprite_IconBatteryHalf,
	ztGuiSprite_IconBatteryFull,
	ztGuiSprite_IconBatteryCharging,
	ztGuiSprite_IconGraphPie,
	ztGuiSprite_IconGraphBar,
	ztGuiSprite_IconWindow,
	ztGuiSprite_IconWindow2,
	ztGuiSprite_IconWindow3,
	ztGuiSprite_IconWindow4,
	ztGuiSprite_IconWindow5,
	ztGuiSprite_IconCommandPrompt,
	ztGuiSprite_IconHeart,
	ztGuiSprite_IconHeart2,
	ztGuiSprite_IconThumbUp,
	ztGuiSprite_IconThumbDown,
	ztGuiSprite_IconMedal,
	ztGuiSprite_IconCheck2,
	ztGuiSprite_IconCheck3,
	ztGuiSprite_IconCheck4,
	ztGuiSprite_IconCheck5,
	ztGuiSprite_IconCheck6,
	ztGuiSprite_IconCheck7,
	ztGuiSprite_IconStar,
	ztGuiSprite_IconStar2,
	ztGuiSprite_IconBeaker,
	ztGuiSprite_IconBomb,
	ztGuiSprite_IconJoystick,
	ztGuiSprite_IconMug,
	ztGuiSprite_IconBulb,
	ztGuiSprite_IconSuitcase,
	ztGuiSprite_IconFilter,
	ztGuiSprite_IconTicket,
	ztGuiSprite_IconGameChar,
	ztGuiSprite_IconText,
	ztGuiSprite_IconUnderline,
	ztGuiSprite_IconItalic,
	ztGuiSprite_IconBold,
	ztGuiSprite_IconStrikeThrough,
	ztGuiSprite_IconAlignFill,
	ztGuiSprite_IconAlignLeft,
	ztGuiSprite_IconAlignCenter,
	ztGuiSprite_IconAlignRight,
	ztGuiSprite_IconListBullet,
	ztGuiSprite_IconListNumber,
	ztGuiSprite_IconIndentBack,
	ztGuiSprite_IconIndent,
	ztGuiSprite_IconArrowBottomRight,
	ztGuiSprite_IconArrowBottomRight2,
	ztGuiSprite_IconArrowBottomRight3,
	ztGuiSprite_IconArrowBottomRight4,
	ztGuiSprite_IconArrowBottomRight5,
	ztGuiSprite_IconPaste,
	ztGuiSprite_IconRedo,
	ztGuiSprite_IconFind,
	ztGuiSprite_IconPrint,
	ztGuiSprite_IconAnchor,
	ztGuiSprite_IconErase,
	ztGuiSprite_IconLessThan,
	ztGuiSprite_IconGreaterThan,
	ztGuiSprite_IconQuote,
	ztGuiSprite_IconParagraph,
	ztGuiSprite_IconTextBackground,
	ztGuiSprite_IconTextForeground,
	ztGuiSprite_IconLine,
	ztGuiSprite_IconArrowStyleDown,
	ztGuiSprite_IconArrowStyleDown2,
	ztGuiSprite_IconVolumeOff,
	ztGuiSprite_IconVolumeHalf,
	ztGuiSprite_IconVolumeFull,
	ztGuiSprite_IconPlay2,
	ztGuiSprite_IconPause2,
	ztGuiSprite_IconRewind2,
	ztGuiSprite_IconFastForward2,
	ztGuiSprite_IconBegin2,
	ztGuiSprite_IconEnd2,
	ztGuiSprite_IconHeadphones,
	ztGuiSprite_IconMicrophone,
	ztGuiSprite_IconLoop,
	ztGuiSprite_IconLoop2,
	ztGuiSprite_IconLoop3,
	ztGuiSprite_IconLoop4,
	ztGuiSprite_IconLoop5,
	ztGuiSprite_IconQuestion,
	ztGuiSprite_IconExclaim,
	ztGuiSprite_IconInfo,
	ztGuiSprite_IconQuestion2,
	ztGuiSprite_IconExclaim2,
	ztGuiSprite_IconInfo2,
	ztGuiSprite_IconMinus3,
	ztGuiSprite_IconPlus3,
	ztGuiSprite_IconMinus2,
	ztGuiSprite_IconPlus2,
	ztGuiSprite_IconMinus4,
	ztGuiSprite_IconPlus4,
	ztGuiSprite_IconBigPlus,
	ztGuiSprite_IconBigMinus,
	ztGuiSprite_IconPower,
	ztGuiSprite_IconDrag,
	ztGuiSprite_IconResizeHorz,
	ztGuiSprite_IconResizeCardinal,
	ztGuiSprite_IconExpand,
	ztGuiSprite_IconResizeSwNe,
	ztGuiSprite_IconArrowOut,
	ztGuiSprite_IconArrowLoop,
	ztGuiSprite_IconBottom,
	ztGuiSprite_IconBottom2,
	ztGuiSprite_IconBottom3,
	ztGuiSprite_IconLabelRight,
	ztGuiSprite_IconLabelUp,
	ztGuiSprite_IconLabelDown,
	ztGuiSprite_IconLabelLeft,
	ztGuiSprite_IconResizeNwSe,

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
bool zt_guiDefaultThemeMake(ztGuiTheme *theme, ztCamera *gui_camera, const char *gui_texture_file, const char *gui_sprite_file);
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
#define ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR	zt_colorRgb(121, 213, 130, 80)
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
		case ztGuiThemeValue_r32_ScrollbarMinHandleSize:      *result = 18 / ppu; break;
		case ztGuiThemeValue_r32_ScrollbarMinWidth:           *result = 18 / ppu; break;

		case ztGuiThemeValue_r32_TextEditPaddingX:            *result = 2 / ppu; break;
		case ztGuiThemeValue_r32_TextEditPaddingY:            *result = 1 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultW:            *result = 90 / ppu; break;
		case ztGuiThemeValue_r32_TextEditDefaultH:            *result = 20 / ppu; break;

		case ztGuiThemeValue_r32_ComboboxButtonW:             *result = 18 / ppu; break;

		case ztGuiThemeValue_r32_CycleBoxButtonW:             *result = 27 / ppu; break;

		case ztGuiThemeValue_r32_MenuSubmenuIconX:            *result = 7 / ppu; break;
		case ztGuiThemeValue_r32_MenuSubmenuIconY:            *result = 7 / ppu; break;

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


		case ztGuiThemeValue_i32_FontID:
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

ZT_FUNC_THEME_GET_COLOR(_zt_guiDefaultThemeGetColor)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetColor");

	if (!_zt_guiDefaultThemeIsItemCustom(item)) {
		return false;
	}

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	switch (value)
	{
		case ztGuiThemeColor_Highlight: *result = ZT_GUI_DEFAULT_THEME_HIGHLIGHT_COLOR; break;

		default: return false;  // return false to use the default
	}

	return true;
}

// ------------------------------------------------------------------------------------------------

ZT_FUNC_THEME_GET_SPRITE(_zt_guiDefaultThemeGetSprite)
{
	ZT_PROFILE_GUI("_zt_guiDefaultThemeGetSprite");

	ztGuiThemeData *theme_data = (ztGuiThemeData*)theme->theme_data;

	i32 hash = zt_strHash(value);

	bool failed = true;
	zt_fiz(theme_data->sprite_manager.sprites_count) {
		if (theme_data->sprite_manager.sprites[i].hash == hash){
			if (theme_data->sprite_manager.sprites[i].type == ztSpriteType_Sprite) {
				result->s = theme_data->sprite_manager.sprites[i].s;
				result->type = ztGuiThemeSpriteType_Sprite;
				failed = false;
			}
			else if (theme_data->sprite_manager.sprites[i].type == ztSpriteType_SpriteNineSlice) {
				result->sns = theme_data->sprite_manager.sprites[i].sns;
				result->type = ztGuiThemeSpriteType_SpriteNineSlice;
				failed = false;
			}
			else {
				break;
			}
		}
	}

	return !failed;
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
		item->size.y += (padding * 3) * 2 - padding;
		item->size.x += (padding * 3) * 2;
	}

	// ================================================================================================================================================================================================

	else if (item->guid == ZT_GUI_MENUBAR_GUID) {
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

			item->size.y = zt_max(item->size.y, zt_max(zt_max(icon.y, ext.y), icon_orig.y));
		}
		item->size.y += (padding * 2) * 2;
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
			zt_drawListPushColor(draw_list, item->color);
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_PanelFrame, -1, -1, ztGuiSpriteNineSlice_PanelFrameDisabled, item)], pos, item->size);
			zt_drawListPopColor(draw_list);
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

		if (item->sib_next && item->sib_next->guid == ZT_GUI_SPINNER_GUID) {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_SpinnerText, -1, -1, ztGuiSpriteNineSlice_TextEditDisabled, item)], pos, item->size);
		}
		else {
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_TextEdit, -1, -1, ztGuiSpriteNineSlice_TextEditDisabled, item)], pos, item->size);
		}

		ztGuiTextEditState *textedit_state = (ztGuiTextEditState*)item->state;
		ztVec2 text_pos = zt_vec2(textedit_state->text_pos[0] + (2 / zt_pixelsPerUnit()), textedit_state->text_pos[1] + (-3 / zt_pixelsPerUnit()));

		if (textedit_state->select_beg != textedit_state->select_end && item->gm->focus_item == item) {
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

			ztSpriteNineSlice *sprite_set = highlighted ? theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_SliderHorzBarPressed] : theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_SliderHorzBarSet];
			ztSpriteNineSlice *sprite_rem = theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_SliderHorzBar];

			zt_drawListAddSpriteNineSlice(draw_list, sprite_rem, pos, zt_vec2(item->size.x, 4 / zt_pixelsPerUnit()));

			r32 x_offset = (item->size.x - (item->size.x * slider_state->value)) * .5f;
			zt_drawListAddSpriteNineSlice(draw_list, sprite_set, zt_vec2(pos.x - x_offset, pos.y), zt_vec2(item->size.x * slider_state->value, 6 / zt_pixelsPerUnit()));

			ztSprite *sprite_handle = highlighted ? theme_data->sprite[ztGuiSprite_SliderHorzHandlePressed] : theme_data->sprite[local::imageIndex(ztGuiSprite_SliderHorzHandle, ztGuiSprite_SliderHorzHandleHighlight, ztGuiSprite_SliderHorzHandlePressed, ztGuiSprite_SliderHorzHandleDisabled, item)];
			zt_drawListAddSpriteFast(draw_list, sprite_handle, zt_vec3(handle_pos, 0), ztVec3::zero, zt_vec3(scale, scale, 1));
		}
		else {
			handle_pos = pos + zt_vec2(0, slider_state->handle_pos);
			handle_size = zt_vec2(item->size.x, zt_max(10 / ppu, slider_state->handle_size));

			ztSpriteNineSlice *sprite_set = highlighted ? theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_SliderVertBarPressed] : theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_SliderVertBarSet];
			ztSpriteNineSlice *sprite_rem = theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_SliderVertBar];

			zt_drawListAddSpriteNineSlice(draw_list, sprite_rem, pos, zt_vec2(4 / zt_pixelsPerUnit(), item->size.y));

			r32 y_offset = (item->size.y - (item->size.y * slider_state->value)) * .5f;
			zt_drawListAddSpriteNineSlice(draw_list, sprite_set, zt_vec2(pos.x, pos.y - y_offset), zt_vec2(6 / zt_pixelsPerUnit(), item->size.y * slider_state->value));

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

			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarHorzBackground, -1, -1, ztGuiSpriteNineSlice_ScrollbarHorzBackgroundDisabled, item)], pos, zt_vec2(item->size.x, 16 / ppu));
			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarHorzHandle, ztGuiSpriteNineSlice_ScrollbarHorzHandleHighlight, ztGuiSpriteNineSlice_ScrollbarHorzHandlePressed, ztGuiSpriteNineSlice_ScrollbarHorzHandleDisabled, item)], handle_pos, handle_size);
		}
		else {
			handle_pos = pos + zt_vec2(0, slider_state->handle_pos);
			handle_size = zt_vec2(item->size.x - (2 / ppu), zt_max(10 / ppu, slider_state->handle_size - (2 / ppu)));

			zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[local::imageIndex(ztGuiSpriteNineSlice_ScrollbarVertBackground, -1, -1, ztGuiSpriteNineSlice_ScrollbarVertBackgroundDisabled, item)], pos, zt_vec2(16 / ppu, item->size.y));
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
		pos.y += (item->size.y - padding * 2 * 2.f) / 2.f;

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
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], zt_vec2(pos.x + ext.x / 2 + (padding * 3), pos.y - ext.y / 2.f), zt_vec2(ext.x + padding * 4, ext.y + 6 / ppu));
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
		pos.x -= (item->size.x - padding * 3 * 2.f) / 2.f;
		pos.y += (item->size.y - padding * 3 * 2.f) / 2.f;

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
					zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[ztGuiSpriteNineSlice_Solid], zt_vec2(pos.x + size.x / 2 - (padding * 3), pos.y - ext.y / 2.f + 1 / ppu), zt_vec2(size.x - padding * 4.f, ext.y + 4 / ppu));
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
				zt_drawListAddSprite(draw_list, theme_data->sprite[ztGuiSprite_IconArrowRight], zt_vec3((item->size.x + pos.x) - (padding * 5 + icon_x), pos.y - y, 0));
				//zt_drawListAddText2D(draw_list, font, ">", zt_vec2((item->size.x + pos.x) - (padding * 3 + icon_x / 2.f), pos.y - y + padding));
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

		ztGuiSpriteNineSlice_Enum nine_slices[] = {
			ztGuiSpriteNineSlice_Spinner,
			ztGuiSpriteNineSlice_SpinnerUpHighlight,
			ztGuiSpriteNineSlice_SpinnerDownHighlight,
			ztGuiSpriteNineSlice_SpinnerUpPressed,
			ztGuiSpriteNineSlice_SpinnerDownPressed,
		};

		ztGuiSpinnerState *spinner_state = (ztGuiSpinnerState*)item->state;

		zt_drawListAddSpriteNineSlice(draw_list, theme_data->sprite_nine_slice[nine_slices[spinner_state->state]], pos, item->size);

		ztSprite *sprite_up = theme_data->sprite[spinner_state->state == ztGuiSpinnerState::State_Idle ? ztGuiSprite_SpinnerArrowUp : ztGuiSprite_SpinnerArrowUpPressed];
		ztSprite *sprite_down = theme_data->sprite[spinner_state->state == ztGuiSpinnerState::State_Idle ? ztGuiSprite_SpinnerArrowDown : ztGuiSprite_SpinnerArrowDownPressed];

		ztVec3 pos_txt_p = zt_vec3(pos.x, (pos.y + (item->size.y / 2)) - (5 / ppu), 0);
		ztVec3 pos_txt_m = zt_vec3(pos.x, (pos.y - (item->size.y / 2)) + (6 / ppu), 0);

		zt_drawListAddSprite(draw_list, sprite_up, pos_txt_p);
		zt_drawListAddSprite(draw_list, sprite_down, pos_txt_m);
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
	i32 encoded_size = 164585;
	char *encoded_data_strings[] = {
		"iVBORw0KGgoAAAANSUhEUgAABAAAAAQACAYAAAB/HSuDAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAB4c9JREFUeNrsvU1vJNlxNho9noGEGcCdwoVswIDd2Rd6FzMLdxKvdobE5NY2zCLUwLtkcvveBat+QVX9giIX1uq9qOJ+ABZ/gFFJ/QFWrwb+gJmNC9syRlJXC5qBpbHA29kToYw6PJ+ZWV9kPECBxaqsyPMR52Q8ceLEeXJ3dwcbRox/iw2XI3n36rx7Ld69zhrKirBec3ic6L57HWo+L9ujFyAnZe8XDdpz2+QImo3REpMNzRm8DITpA9GFUr/zFuWV82CGfwvsM45R4HxA7Q+B7V2W4QW+f6Uph29d+jXKu6pn5tjwXTkvneDfVSNi9xkY+tiGWcC1tmdHyq5ZGNorxvIVGh1MGrTBhaHOLrkXNfVQ8IDw5MkTaQSBQLAZlA6AgNfo3Wv27pUE/s70yu6+xZsav43evW5QRlvlIIwayEqwPnctlW1dr8671+XdfZSfpYGybPDRnQFrQ45bLKdvObZNjumljqm44e99XjHWq3x1DfdMcJzVrVeKZZu1MBY6Stu/aXEeqjO265QlZXPoZYvzQ4Yy73BOHNfot7jlOSvGdrnBvqP36jyRGdp5YGn/NOAZMdP0101g+9B9Ry30D2GG4y6qOV/cNdDDNl4DpT9nrM8i1MEmz4k7TXvp+uVWmY9Dn+2zu2YYWPpojG3EQZ8Ndsg2kNeKXgKBQLALDoBxy4ZG5ni4+5D/uxaM1szT2AglCGRY2K7v4muTD6HIQPzvNIaLr7FK6KKxnrLP0oB+tZUFdkiOTk8Spb1SRYe6HgRrpCF+qUeduoZ63DDC/qahMyxTDPO7msTUZqiP7zZP/n3nxJGlzZs4WcYtkcFuS/OpWt9LrN+tRrZubklZOw/Y5x32ua8DYNDCmM3Yfcds/PjqDNf9DMvewf/f4PdJw+dVaH9nmnmNHBxRQN14fw7Y+3GAU9/1jEwNz+NIGY+2+o8tToBVOgAGGvkDxVkiL3EACAQCwVY6ACJmsLS12pA1NIB1Rm921w759zEO6SHecRCEsWcdxht8CN0ojo+MkfZMWWGZOQjaTDF4bhyfqfpzqUQexIoh6Ov0GQfI6XqStiZyQFNPPn4GTPalx5gYMGI9YDo0U0hXKCkyIa05rt6wKIIbVrZQB5UpAmN2tznyf4t9FrMx8sYjeuFWcdzUaROTE7Wj6OwsoI1vW5hPfVZWBzVXgOvo442mTjcBUWepps9vPds1YVEPscP56vssjRpGoPg4NG0RFjHOMwlrn8gwb/pGRrnKnhnaO9PUn6KaLhnJTgwLGOIAkJc4AAQCwaPFE8ckVO7xK/fpxe9ez+HbfW0Z+36Bn4fsNyx/T/sXyz17BwG/L8tz+e41BP0eu3Lv46RGOThcZRorbVDuS8yxnSL2+QTLo0MK9/c/0vVvmJwpyi8s9ShlHWJbRKxfynpcgH2v7AC+3ddqKi/1P2/nIf7uni+phv4dQLXnuLzHjaPteHnKOn5Pc82q5dyxss895Nj0uIcyxijjQBlbtj4rf3vGykRtmaLsUmf2PHXPhQLHeci4WrA2UtvcpEM6WSNlXNUd73WRaMa2qhNlGbs0p2pkzLDd1bmFj7/nEJ7T4AbLlyu6w+e2PcccoBvjbbSvOk/qZN5Z9C03/F6dN6z+bdfzr0a/g6f+3rIxAJpn5wTlFDheU49nqa5N1XHm289l+52z+x0yHTbJjLGsiYdeURuW+n1l0aNS3itLe5bfX8P9vDw0dqisx6z8Kqaod7wPnihjsy5MujDDcu8r8of42bXnHPgg8PLly1J3TqFZvgWBQCAQ1ENpa1x8/vnnuY8DgJP/HlQJm/bZQzTUAdCE/CeMKJW/OdI4AXwN1rrkPwV7AiYf8s8NuTl2Ck9sdqEQNBP5SrD+KeuLKfZbygzXHMtSaPr3Fv9OsT1tBuPcQXQzj3bhOENjaKGQKBfZjLHcgGWeKt+vWs6dQkJccnyJ0gLvdaC0+UJD3nuKQXxncKaYjNOxhVyFGro28t/B+aKAKoEXtdX3NAb9Pv72Go3FWEMKaaycK+WJsM9iTbnIiWb7fh5IAhdsjI/ZNU8sRFQ3P90Fklrdb3V6Z5KbIFnqYBseO4zyOk4AU7up8ysv/4K1KznFrpTPbwLb6sZSN9f8YPstzVuHWMYzwzigZyM5A4jwx0heIyTSdM25ZYzpHHe+5F91NvE+TbBMC6XfbO2TgjnhnuoEof6dW2Rdsvmiz54PV/jdnub5RWU9wLmC2yQ5/k3ZeJ+jnDFzYIgDYD3kP/vqq69G//Iv/xK9fftWzHCBQCBYMz766CP4sz/7M3j27Nnk888//9Z2dYQKvlH2QN6xMMCQLQCREnocEvbf0YSn8lDFm8CQ1U7NvbhjZS9n3b2liXK/SPN7NUy7Y9mXqttbrYZ66vqqo/SpK8dC7BGCy8vrep8aQoZHAaG9A0vo8UizNWGmbD8IkWMLR75xhIO6dCpTQoFNbTTWJFIzheIODEmxbKHELsQBYf9jQ6jsSFO3kSMkeeAxX1yy66mPb5XPbN9HgXv+TbCNizTwO99cGyFyx571eOOZU8K2XeIN2+6g60Of8vNrQtrKVc9uzdwBPklNZ+w5MEY9iwxz7IyNgRtLmW4NSUj5nGbb+vPG8HxSw9FTy3NnVa8xy3tCW5lGHs/1WHmmjA3zoDoHxbIFYD2vn/zkJ50f/vCHd+jsk5e85CUveW3w9Wd/9md3f/M3f/PeDggl/927KvO+b6byriIjhPynnvsVQwwV3T5IX/LPH/iZoTy++0Ijy57MsWI4DBz7UonQc3LrSpI0YHX3TbB46zB6TMa6jxE/CyDRMw/iPvAg7uuQ49KpQYBDzSc5oOpoSgLzX9gwCyT/N8xAHyhEPXXsBfcl/lwGJ1qJxXE40Dgf0hbI/xsPIhu6t73u71PLHm0XOa6bmFAl/8mdnwOj07IDwFW/kcc4q9vfoNSJz6GXypzbYU6j1OJAGniWJfF4jsYOB4DJwZrVdFalntfztiCnv8/vLjXPMfX0kktLf4kDYIWvv/qrv7oVo1te8pKXvLbn9emnn9795Cc/ST/wCPuPWJjsMVTn2xceYaADTejfkWfYf6SElJ9owh0jLI8r7HqA9RphmOEJk+MK++f7BidY7zsM/9Ttmc8s9ZmxMG8A897bzFKeS+X/CxaGnOJrzLYEmNqTh5Gawv7V8N8CVgcqxwvPEGMwtJEqZ2h4FQ45hSLnAJb3WfeYPtrkgCMEv486SbJM+90pNPcY35t0Z8Z0HVjIq4qJEkY9xbDY72FZzpSxlhvCeNWwfwrHpXO7x+z3Y6xrrtx7YRgv+xC2Z7RgslJDuD/JJbwNCPt36e/BFkV85SwUWhfWb5ozQ7dm6drNNzR9roxn1/MgdGypY/UAw9p7lt+nYN7yYSo/OK6nuaTD6puyMZB69OUBe5002ApQaH6r7s0mOfvKfEH3zz37ImXzkauOU6VMhed9+JYg/szuKmH3pEOyB31NePnyZedXv/pVLC0hEAgE24P/+I//gPdcInDlP+S8a76alLKQ0pBzhnUrj90amddvNStA0Z3fsWSm0P9Ly0pqZmmTriMbM2UuTg2rDG8MKxC6qICRZcVqoFzrc7TiG0e7N4kAyBxhtbr+jx0r26uQo5bfJce1OsnHVMcyxlLW37bV3ZRFxXB9s0UJvLlrloVet/LPj3PLlO+iO78j8vj4T1n4bmzQzTdYb2oD3ekBN2ybzYDpfNJgRdA2L24qAqDOkYa3a1r5V8fCraPet8o4iwJX/kMixFKL/vH/bRExagRAR1lZVyMAIkcEQNMjeVPLFhV+DKwaqXC5ppXi6G752NzUEtLvs9XlUnOagSvyTCIA2g//H5QrTbLiJi95yUte2/V6Nz/PdKF03YbkHwwh9mnAtgGVtF9qynkbSFJ8Qpl99xpygnOpucfAQThvDcZEZjBuBpb6zDRkLDM4PlLLXk8X+U89iHUTB0DkQSLUo58ix/72pnJuNXI4+faR40v+uRPm0jKuRndhuS5cZRoE",
		"OtP4mHjTAvnn44P2MXcMZE49sjLyDJO+ufPP2+FzVNpdAAHT4bKhA2BkIPB1jsd747Gn3XdL1U3gHJ96zH13zDF2Z3Eijw19E3pcrep4vWNOJ67ftufIjI1T9VjP9O7+0ankBLv1HHch5J87+mw6MmBlfmN4jiV3/scgRp76GDGnXMResWMuVPUku9Mfr6jWPxEHgDgA5CUvecnrkTsAlghRpjEG65D/pOHqlCqDE4o3Afs4+YP4RmP4hj7QugaCc+u5RzJ27C3NPFc3wNPhMPaQf+tZDm7k33quxoQ6AHQJGvlK7Sxgr3K6ZXJ8yD9v68iRT0O3jzfRkLxLTwP81iDXx3GQsXaqS/5tZOcywPhOWf/Qi0dAxMyBQ6/krt556aH73O+USJHbBg6AkN/bIqtuWCSUa3Xd5UwY1SQKM0Nb8vno0uGg0Dl/unhtqEND3S8/YuOCxlnX4QDoMocgzfs3LBKA8rW8uVvO1+JDCsc1Ii34XD/zfM7p2nqAfREHPMNnDp3qKmWasXkr0qzkm3IA6KJXYo9FgxAHwIzNKyOH43TGnBDc6X+DL3EAyEte8pKXvDbuAJhpQv8HNci/LZw3hFyYyHZokqpEWRXnD+O4xkMtVcpDxskliwTIaoTeZhby8MaywvvGYJzcKtEG6Z3fiQgDAwm78QynbeoA0NXLBZMubJOccQ3iaCPr6j3U9hwHruZ2aoT8DpT7pi2Tf3Xc3bYQyVN3Zbsu+QeLM7RJBEDI702O1YFGR0NDvsds20XddjZtH3ij6JBttbWuM8SVBHDgiAy6vLOfsnHJ6jjT6G6itKNrjMQN5o9McWRGDvJ/6SFvZChjzMatK4z/hj3/xhoH/8jhXEqVMqun4bj0J8QBMLDMfza5A0Vv7h6LA+Czzz67e/LkibzkJS95yWuLXqUD4EOWHIfO0abkf/3A5EJqUh6OM/BPIJfi/SmJ2KWSlEk9P96WNGqsvC+TCl1A+LnWPBlTlyW6OsKyUmKhI4+kVwdKkjHXOdvnlqRJOSa8OoQqASD//sohe4rfU9KsMhnUs3ev1/j/MyWh1hmEn3MfCrVePDHUFX7PE+AlUJ0jvY1yRkob1hlT/LdHeL8bHAcTZez08e9JwD2m+Orgy6ePC3bPHMtGen2CCcQyqJ9UTh13pZzYkdCsTSzYWE0aJF0z1WcB4YkG+Twyr5HQbIxtpjuX/SRQ3gj7Y69hP8zx3jTPk16fsHsA6vlA8/tY0YspzvF5gzJR8sq+Mh8C6jXd78KhOzdYL0pgS0no5qz/KWmhT3LcfgPdm7AxmeE4Lz+jJJiHrP8LuJ9oUH22jtjck2GbDNj8swf3k33qkGCfdZV5svz/1bvXNT6XbGNpwurUYfdM2BibG/SnDhLWF7nH3Dpg9sGswbjfObwzNOGDDz6QrFsCgUCwbfNz6anFkABuvPTwAXcUaGiQAaAaHicBMsoH/7FC/imj/TDA2ORlmSCRnrfQZhEaOAUsZ1h3EXlVRheqUwVMuEVDarFiPehiW0UWg7bnUb+7gHuGZJPWtZ9KzJ5sqZw62dF97qc6FrhB3KtxjxgJyxz8stkTWYtxbKaM/M8VWW3or5qdv0DZxYrHhtq3oX3YdEy0NabK+fAp+DlPXeCEry3YTl84A3vm/giJ3wLac1BmsHwKjoqhR/1TqE5tKefOK/bdIRu/Jx7lpvHZdP5QM+Tr5g+XM4IvFiywHfaxbFTOI4/5nZ7RZ5YyTVE3hobnT8T0JjL0Fzk3dc9onxMKuB4CK6vtmU9lUue/DO2GYcvjZ+vw8uXLwT/+4z/2373E0hYIBIItwt/93d+9dwCUD6k37PMCDYyjQHkdqI7tKmW8xgdvqLFCR/vRkXlHNY38BI2UJiv+LuNuVoP8h5KyYk36EGMfHiqfUxSBD2lYlwOA9OQS+6GJMbUOORQVcATtOKH4PYk49XC8FQ11OgogUVSvWOMk6gboTWh9AapV1HWAH48aSsC2xQGQNhxvar/PV9TO3LFV4Nyaw2ZA+sYJ4hzMxyuaZJBTO1aesxdIKn1k0bOsjXYvy6Ee/VdAFdFUx1nygjlpohU8L3LQOyYH+Mw6YHYItfOCzYlEvJ80cAAAkztkDgEdLvGauaEv3z4GB8A//dM/9d+9xNoWCASCLcLf/u3f/sEBkOBDbb5F5WvTYF0VumhcTEWd/tBnvlgngXsM7b7J9oweQV/S6mKx5jHxGMdUjK9chvZSmxQPrE4hur0q+4RvE2hznLnmxIfYn/ccAP/8z//cf/eS0SsQCARbhL/+67+GD8FvH9smsAvG35mo0c71mbR7+3gMjpxFzXrmMqaCUTx0clSzTWTeah+rWvRYPML+vAfJASAQCATbiQ/Z+wF8G8JfPph6LRj1tPfxaAvrneHfyQPrz7JePBRT0F67lmGmtpUi01aJWcN7035+2tLiA9e2FxrroQSEzwtlOG2M76+xjG1FwtCebrXNy3ucBxrPlGgtgnq5EeqC+qvn2W+2PpvV1JuRR53Ldj5lpGVYs41UOec1Cd42yWmrLG3L2gaUuvWqwTOUJ8/V6b7r+7blCFbkAHjywRNpCIFAINhSB8AYlhOKlQ/2pqvbdBpAumWGTpcZ5CFk2WWEl0bdCWxuNTSD5VMPTmrKmRkI6K4ihmq/a8qI5Bzc2cL5vn4XUryPus8/bVh+IsCXcD8Lvq0suYEol+S/36AtD9j7VKljnWSdOuJMdZ3gXFTiKc4pXdTJs4Dx3mFt+HxFYy9SykR1iAL0x9RnaU29ScHutOpqnBMp1Dv55VLzWWiej22S01ZZ2pa1LSjH6duGvy/wb1zj+7blCFbkAJAIAIFAINheB0CmfL7fwAHAVzoADUwdKT6H9e+dJ0cHrWTylUEXcU+RkLw2fN9nBGndTgBO/nl/1nECpAYCuovQERwyChNsJ9uxkjz7e2mo00r3QmkvOi4xxt8818gLdaTMNOQ7lKzryCQfm6TPLzzIItXVlgAuguqYMd/jOtV+ucF5gU6/4E6bHjowRtjmLuddWZ5jpU060G6kAiWtW8ByBEgdshHDekODjw116gTq6qlFfr6jck4tn4eS9jZlNcUAn+91oz3IKcoJ9SDg9yM2/16jjGO4H5Gk+56v4LclRyAOAIFAIHi0DgAXCQwl2ZHyADbd43trIsvcaOGrLnNG8nyIu23FuA9VRvZ1OgFU8t+GEyAEl1CtsNpQttvRGttlAH4r3V3W/2r7JYy8n1nqRboxY6RQbfc5bMdqX2TR5wwqR5br9z2osqS/QB2IlHbtgP/JB5Rpf4q/0R1NOcH7FqjzV5Y2NR0rR+eyNyEAMbbVKZNPxHmXiMVijbr2UOREa2qftrYOqXNdX/MMprJk+Ne2nafL7IMI5U3A33HFI7GOoUquGRscNvz76xXIEawY4gAQCASC3XEANDFyIosBoho3icaAt50H7TJmdaGrCSPIe4qhUl77HO93C+2c0b5uJ0CB9zKF7q86Q3vH87pU09/pikhxCmFh7ik6DAbss1NG8H2iYcrrhnjfbA2OlzYwg2o7BOUwmGIduo7fzhUHyInGgRDjPXzOOc+YHHLe0FFbC6jOZY9R34/xGpP+jC1zyBjM4faJxvHAx1QK5j39+54OAEooGFvmxhMs36ymHB8nhsk5ewj+q7qRRU5IubZJjk1GnWdjHVkp1N9+ZXp+Rpb/+fGLAObtCaTjFAlEkVSDmjrY5Pu25QhahkQACAQCwXY7AArlIdkGeam74lkaL0ewnLzHx6A+QcO+x+5LZDwH8/78BToGxgFkRYche983ODdi0K/W26AzAlU5PUP795Xy2crjMjZnFjl1DOIRVPuN23YCHNf8zUBjtJ8HyJiwNl+VcyN0LJWwhbzy7RAF6n+pC68cutrBsVMwIj3B14C1AyXhKxz6dcjKeIp6Vo7DS1aHUldusKzn+J3OwdXxmDv6hnmO9NJE2PZbIBrkaLzV/CZlsgpGBHVOhyPUsZuAuZKXNQokrKZrt0lOG/Vqq22a1oueobStjm+bq5Or5YWhDHODHuYW50TEXur4Ueulzj8T/CwEI8N824acncOPfvyj0a9//evkN7/5DXz91dfw1Vdf",
		"wddffw2///3vfUVc3N3dTcQBIBAIBI/bAZBD5f2fwmbDWClc/4QRaZeR1GNkgJAh8RiC3+pEeb9rlNODaiX0HPxWYQYKueiztuVligMcLCM0/NTrM2yXI+bAsTklRqDf/8rlnBoIzAjln2OdQvfjqoZ1Ka/r6PuU1aunOGQ6UK0Ek76qzp1OzbLp9reHRE8UWza+U8WYLzSkoUDyTbpJTrAJ/m+KpDhV+qk0xGm1foDtOGYkoZS7Z2mjFHWMCNMZEtuYfb+H9eDJO3WOtkOPtukYxmEKVSSHSUfbgq9uHTf8vQ45vnTOjl6gnAnczyPD5591ypm3IMcmIzQ3zhx/020gi8LdCzYXDmvMPYVGfxbKXEF45ugrHgGgKyuHGnL/GmVQokoaw3PD874w6PprZeyT8+EC5wjd+4dyZGkCzbZqrmUbxPtTAJ7IKQACgUCwrQ6AK2bsdGD9yahsToB9gyFGhsi5hvwDko/Qvb4TNBD4qmMf6kVEXEN1DFfOSFPI8U/nUEU1LBTy5SMnV+So2dm5HMqHoCPGJ1BtJ9DJ8YUr+oHIPw9tpsztBX53yQzrGKq95wctkLRIMY4jCFvJ76zQGXAG7rB8TjoSTT/qCMAUqsz9Y6zvmBH5fQ9DkxwF5KwimQumU6Q7B56EWBfaHkGV0dvH8eHqa53DZx3zHum4rh4HrA/p/1kNOT7ooZNF7YNQknuumaPbkgMbknPegjOCy+o2dEiopK1v6VPfckyZvk+V+etCQziJYMewHAFwjCT7hD1HEwuhpznjVvP5rEE7ESm+trxfGb7//e+/Pxrxyy+/nIBAIBAIBFuMDzSGAMD9I4vqYIQPc90rhDCazhqeoJFyaSF8IwhbDU6hChHk4Ze3Nep/qhg/Gdw/KszXIdHVyKnj2MgscnQ5FNTPdHLaAl/leo6vCWtLgGoltGzDPaiy7acKWay7yrNQjGO6t69Doc9IZNtEsqeQZ8rifYKf89cF+OVAKMfXGyT61NcT9l1kIRRzDXkmx13GHFA9ZXyZxiMRe74ieaa5HxnysaWv4xoOH058+h5krC64buQGHeJ5FPKacnyJ5VwzV7QlZ9GCnLOacvKGctqQwfsqV9rGN0cMP8lkBFWk2dDwKgLKwUn+leU6uncKVSI99W+HPadoPk4tY7GA+yeqFKweZ8rnIXPkxPJ+Jfj0009Hz58/z168eBGDQCAQCAQ74gAgg4KTsXFD2RdoAFxp/oagz4gON8RM+2J1hOTSQeIi5rCILUTh1FOOjlycQhVdQI6QxCBDdZYca+SMFTkqCSw0ck4dcmJG+BeectpCxIy9hWKUJgqxu2Lkb64hfXUI0UIhH0NWrhuwryonSn/2VjRec1bWctvGC6iS4dHrEnUwCmj3PlTh9rQtIEKD3pTLo8ecMOpxf2PmBDiD+2G6prodsvslzHCnV8QIVKbps1Do+nSA9TpQSMgE73VhIbeuFcYhthc5XA/wXmqZUlZXncP0zENOXQdI9EDkmBLe3eErbSCjyfxW6s65oj+Z5Xf7jJDPocpB0de8FhanQoa6xOt9ifoea5w/ppV7GgfqX3UsF2BOtEnYU35bQJWMlT8PbMSdntsZmwtTy/tV4eK73/3uURRFExAIBAKBYMvxofJgP2YPSTJKThjB6jBDxIVjx19fUnaEhgrt9V+gEUR7lUfgXvHrYL10Cf4SlB97lKeJnERDOnTnbWcaQ4WHopvkDDzkgKccIluFh5wQTMF83vycyc1Qdl8h/OREGqFedGD5nHjCOYTnAVCT/RVQJZaMGRGbQ5Whfay5zwT0SSRHinFORHsEYVmqyTEzhvqh31zWORJvcvodQLUd4BT14cJiPJPRPlX0n2fa56HmsUF36BjFDpZhoCG/CyS+EVTbV1TELcyLc1a3LhuDC9b/PfyOOwVdyUMPwZ5E0OSkUJ2dKTQ7Ji7GcmeasUjj/Rzcq/htyslA72BtQw4/EcWnbVxl4fkuQmQR+ae+O2Dttw/6rWZHFmeSbizqiP/I4lwh50GO96LxeYPlPdHoY6R52a4JRQL+x9j6hP2vbAsAD/sv33/xxRevYLeOAhUIBALBI3cAkLHBE29l+PA8V4yIAg0Q24PuAqrEO7q/PkY4T+5HewoLRrrGEHZiwAKWowEWEJ5F2CTnqoYcWrU5YwS835KcUUM5iwZybCSbyExH06a0z32sIc8jxei7VYxhboznEL5nfqD5fMKIfszu3dEQBArJP3M4gLiDLKthIFMivaSF/iBH1gTbM0W5U6i2AOj2yXMCEUMVuk1Z+iPWb0dQreqnjAirDoAcy0EnBuxbHE8j0O8xn0HYKl8fy3JiqGNh6b8Fc3yMwS8awafPDjQOreMackzOBJ+V0JiNuQncDy03yVkoullXTlvl4eN7ptEVau88sCxEmonQz2u0cwT38y+YkKEO0Gk3CzZ+1O9AM89EnrqRIElOmewLZazmsLy/n/4mlmtCMWJycse1Paic1VOP9/vQEsqw/88++yz76KOPzvl7MSsFAoFAsGsOAFpx5+cI67YDxMxQNz2gm0QATJFQq6H7qqFBIf49NOQ7FgNwqBA5bvj4OhHmUCXUayLHRm7rYtvkmFBgO6VIogvFmHsFYVEipiPuKAy/66FrtlWmUr+fY5/eMOLI72M78nKoIZ1quSYWR5QpSV2og0NXvkOoojKAOY8GzHiPDL/N2LxA5L/A9hgzWTFUpwSk7POewSEB4I7eiFCHFpoxGIrEQZCmrB4jTbmp7m2dDtBX9MqWBDCU/NeRk2H9Kd9GYpGTQ7XiapLDHVhNytNUjqoDPjJ8jtqzycqgiuC5CZiDeE4INfmr7TsI1EtfR8EqIwB4VJfPVqpjcGf+n6zoWXbx8ccfX33yySfFv/3bv0X0XszKCt/5znfgza/eSEMIBALBluDp06daBwAZtM9h+Tg2mzGQW4hZnQiAM3CfQa4aLZTxv4D7YZCmYwJVJwKtKtmcCG3IecxQV+l1ujOB1YdQUvb7C/DfxjA3ODJchGBgIHhUDt12Eh+UunhlceLwfAQTCyHJNAb1PiMVI9CHOqsRGV2s60QhJR24nwcgttTrBL9/qpl/CmzvPUOZDmrqg60PhwqhMelTW8eLpQoZy1uWWwcUCZI75rUOuFe944D5USXcs5pyuG7MFNlz8E9qOreQex5JYJt3yjnnVNM3ukgbGnuR5jMdadeN1RBndOzxjM+h3QgAvt2mxCFzJPlsNdx42L/6HmQLwB/wwQcfwO9+9ztpCIFAINgyfGgxVA7QMOobDAPXMU8+EQALg8HdhfDjlmK4v2IwQQPAtbpDyfsovDLTyHnVgpyHiD3wW+VpmrCtDjrMuHRtWQnBlPXxJmXkFjIyY0a46nhJHeMoNhAI3oeuVXOKTtjHeaJwEAuV6F/B/QiHqaO9dPJmDlLpQ/r2oNrqEOJkiuBxoeyfc2gnYoEIbRuYKU4A6tfcQ5frOEtsDg2+v53nRKHjTkFT1lAMma7uBdSP8iTkGoLOx22bEQDqMzv0yF2fLQCtwRT2L1sABAKBQPAQHACc+E6QSB3C8tFbJvJCBCNRCIT6d24wqGlvbVOUpOM1hJ1mMIbq2KCFImfUUM5DxXxLy9VBA5D25bfVDz0IP5dc1e8erHaVaAHm0PEeLG/xCa07Hxdddj9en2tYTp7n63xQ5xF+PSUsrKOfXfa+DiEoavyuLGs/sM/mjPjlOzgXUGLLkH5eNw4azlsHDebBESwfR3cCVfLYI43+b2J+Xjh0PVbGdeRxjQqKMgoB5SdYhZwQaMP+ZQuAQCAQCHYJT+7u7lYh18f4W7WBG0H9ZFl81bQtOU0NYpK1bXK2FQksHynYBmJovqLUhoyQMQCaNqij0zoSTPvn1e+4fB41wPfb++hPDMtOx7qkLd2QzpIOJg3HU1pzfPIIEN6WTca7SY4aHZLUlNNWeULa2FdGqM6Co512Ca5cGTRH6Fb9+fzgI8dnDmpLjhdcYf/qe/rd//xfSVnO/i+LX0VfffnV/Mt//eUfIh7+z//7f5Jf/vKX/Z///OfRb3/72/lP//6nS9EQn376afnbEdObky+++OK9/v3oxz+a/frXv05/",
		"85vfwNdffQ1fffUVfP311/D73//et0rDd7bfYJUK8/Lly8G7tuj/7Gc/E0tbIBAItgTvnlXw4x//2BkBUBf5FtRx0VI52pKTb1nb5g9cx1dhZBdbIiNEd1ep0/NA+fMabVXssK7PW7p/3sLvihb1t/DQu3xNfduGnKLFcVmseYzv2ny6bXKc8An7t2wBKKOAaCta+v3/+/+6/vJff/k+58uHH3649N3//n/+9/VP//6nPB/M6B2pT9++fQt/8id/An/0R39UbouaiPkqEAgEgqYgBwD3NNuMOtee5bbk+MorQ/kG0o0bx6ylPm9Djk+ehgOPsrhCY+aecnaxH0P3yW8jyrmDMoRzchaS+LFNlHqXwbdbqdQ5bFKDNFLy02gF/UXHXA7X3Fa2MXcQWJYYqvw1Q9icEyjGfldD1YnM7er8keL4ipX5uS5JNUUNmZBBswiSELvBGfZv2QIQaealqcd371Gu6pcOgDJr8zv5MQgEAoFA0KIDIAK/MNPYQXrakuMrL0XDeSJduXFjsI0+b0OOj4xZC+Q9aSiHEkZeQZUMbNP6nBoM0yake451NBGwSyTlUweRoz31tmsJZbt2LcShbN+TNbbrAKrM72XZX+P7p9heZb3OkKj66tKMtXP5/nkLZJKcCim20SX+9SlXypwb11DvZAswODNCkgqSvmRK2fKWHAHkHHE5IyMsR9fSXqTXg4B7X9ZwhrTt0BizuSpHfaZTO8ZYrxPPMmbYnuqWETqphU7VUXEMzbaxOds8NOxfTgEQCAQCwa45ADh02fdfoPERQnrakqOT94wZeJTkTx66m8eEkRtgJKcb2OdtyGmrLDpCQpEpdZ0ACeotZQQvyd9bNJzzGro8QPJ1hMay70r+zEKg1frYztMm4tgxEJ0u1utEY8x38FWwexQaIndhuVaV1/UgHa8tJKBJFnu1zcesDoXG8UCRAV1sKx9dylB3howMjVpwalAZyJlQtvEN6uZAQwSJ9KdQ5YJYsPafMmdA4VmGupn/dcRf1cOmjoCuUr5zg5xIcdCAw0nwLLDvmp5akKHOhEbQJWxsnBjmgxTbaGa5hupgO2qYxkUH6h+VWhuhYf9yCoBAIBAIdt0BMDA81DuKEeAyVOvK4WH/kUFeqhh6q3YC8Hu7jj804VJjuNXZwrBtclSSqDOIXzHC66M7bcjxlbHnqNNcIyfH+4bUiRvfI6XtuzXbWzWib9AJkHoShdRi6JuunXiQnTOozmpP2e9vsJ3mFgLXxz658SB7dC2Xp8u8n8P9pGGnFl1PG4wBdc7KlHLzcbdQnCaUEd51BBxFDAyYY2EM5tXS0PLPcPyYTjG4Yf3NCfVc4xzoo74XqJttby1xEf+2HAFj5R5zS10uISzJZgbV6SCmMs/w+yctkP9xzd/S7w4sdc+hOoFkhP/rdHLm2UY0xx2t2QkQFPYvpwAIBAKBYNcdAD7wJU915PhuI9AZJxMHwb2qSd5VQ7iMZAhZsUnBvDoasvqzbXJ8MWF91CR0vg05XMb5GutEIf+cRPSgWkGtM3YuYXkfLJG3VWGERvjCQHYWUJ0wQcf29aAKdyZjfs/RZyErnJHDeUHh0jES10iZZ3KPfuar2q7/VWKqI6xX+H7fMAYzMDszM5RxrpSRHCK+Y7eLbTAw6Fbi0D3e3wulPxfKX6p3tAKdDCH/OidP4XCa6KJbbPk/Msd4XqDjIVL0o4t9WmjaemEh0k3I/0XAbylySiX/I2yb50ody+tuDTo5MOhXObe8gipSUH2+555zPUXhHIfqRt2wf9kCIBAIBIKH6AAooAo35WH8LoKihnOeBMqZGB7gvDzPNNe4CG6vBUPKZUDlAbI6YM+ofrSDclyEOYF6YbhtyJkwg7qJ0eZbllghygVUq6FnsLxnPUUDeeAwxkdrnisWGtKjkp2yPd6i4U17eDv4d47OiRjLP1hTuXOF6IUef3gC1TYGn/8JtE+ck96hpt4qKVvgb036SG2rW8Xt4NxmI0kxVHu4AR1QJ9g/U/w/UdpvYiBZ9PsxI8bcQTDH316t0DFFz5QQR0AOfqv/uuiWiaONTx3zBf12YPhtT3mG3mBZDxq2k6pnJ4Fz3inqR66Q8szwrCAHYF9pr8jQRhMsU2L4PvKcN06Y3RBE/puE/csWAIFAIBA8VAfAwEGudQbAdUM5FxYHAJcT8qDvWoyWUKJsu29IqGbdqIdNyUmgXijvBOqHn7Ytp4D7Yb11nQCFQoBUUjZmRDBH/VooZOqaXVcazfua63RRBDaMwZ6MS83T0Wd1UvMnTDX1OzSQ2wEjT0c45vqMEB+v0AEwVwgbhcarzkafo+rmbI7x+Z8jRQI0QeePifRNoIoWeA5VZEekIZkxLG+pAIO+TSxzH0Vi8LwTN6z/9qBKWjgEc8QUbY05Y/PFKZaRdK4I7DtOcinkfW4ZW3ws+zgCfIk/gD7Chkiqbd5MDPf1OamhwxwAfItFwebcmNU5VZwuOVSRFvMWyT9t5xkayP+BZW7sYzmnTG8jC/mfgTlS5NAxb3DyX+f5UDvsX7YACAQCgeAhOgDqEqzBltY7lCgfiKrca79dh0r+6+SRGGhI30QhPpz8n4E5+kRdJU+hWj0jA38MYSvYMcpTV54zJOE28hMrDgqTc4PImdoWfAVQ1ZsYX6swls8V4z8zEMJpQPvFnv+rbdhj5O3I4USiI+tyhdDp2tuGQ4MOz6DK3H7EZE+hytx+yBwAIXM3RXskNcZQCdPxfyPNPJxr5qIOlj1CXVcdAUT8C/ycTje4MOi1joj6kOZE8wwcBrRHzOTcYJseYHnH2DcUSXGE70vZr7FeB3hdKeeJgfyTE8GnfyewHDVTMEcSH1OXOjLN6s2Pt0sM5J8cn6b+iBxzH/WPzllB6Nsq+8UXX+z60acCgUAgEGzcAaDbAsAx3IH2KQ2J2wa/fyIqZuz3YoNlGBtIoW6Puw2mhHOFQlqIuF855BVQZVJXk4LFEB6+TuAr7ioh8CEyLofPlcWpERmcDatyAEzhfpLFuvOP6ih0/e8iybZ+97nuGPXr2vA9bYfSRQ+kUEU3zRVCSPu1kw2OySYnVmRKPXPmCKC2UCMDaE+77mSKyxrkX4fzmr8roNo6kbLxRZ+/hWrLBm1De4Hfn6Me0Dgea8a2bz+XER3fc+hrHX3nc+UJu/7I0vepw1ExYXIGAfO1QCAQCATiAGgRC4uhuivYFEkdbpmcNrHPiNo2kX/dHvc2UBrq5crdXcBvrjRG7BSN5RcQdmpArjgSVpE74BjrGWkIz3TNhrcu8kBHGAqPcWPbEgGGawrFyUHziC1XRYddFxsIVAxVJMHU4rDIwLwNgLZl8NB+dYvKpjCHejlBdKH/KVTh8XPNeCcHQW4pS8z+PwQ/x+BC45w4hPBjBxdQ5Zag/jpijhLCkVIngOUtG+RIjBqMJYDl0x34XDRm5dC1TayUTUUKywkvTcQ9dpQzQ1tjAlWOi7WDJwQU01IgEAgEj9UBUIA9zDDdkTZS9xSHEK+6mLZE1LicbdnGkDIy0oZzowj4zchB/udrbAN1RdMnWoQMy67y2WsNIeXtxOtFR3RFLY3xGKokh6T3hVKeuOXx4cIZOiVih+6YMFDa8sJSXtM1OZK/GKrw5omBKJ0yWa/xmrnGSbAAu+OMvt8H+/nrREzVYwjV6/pIrFbhrFMdYjNFR3PPa0gPdY4AdbXbRfw5seaOwg72o8tBONcQbnJGTMCdoDHXyKPyDlCvF4HjUx3vc/BPgjtnekVZ9SfKXDQG84lAmSJHN1/zrVeFg7zb5mcu52LdToAyCeDz58+zP/7jP5YkgAKBQCB41A6AtrcAzCyG6iqxWPPvKGyVjMasATlumhRQJZdQg3Sb+m8EVZj7vIEciijwkUNJJaOG5D+zkMtjbPMzaD+awFSn3OIA0BnRBwbiZ1rxLiyEJdMY4gfKPLBO8k99OjSQgDNYT2QPkZCOors9Vv8YljPyZwq50um5K5s+ORxcxwGmju/o2LUR6vTJCvRZN2ZngdesIgcAsPp2mR7fwP0tFCqmhjk7w3Keg9kxfqHR4wH+lsbmILCN54oTIGH9GYJzps9TRU8PDXpIp1kslPYZ",
		"W8g7WMi7awuVr5yVjPfvfve7V1EUFSAQCAQCwSN2ALS9BSDdUBtd17z3q5r34wZSwgzeg0AZI8UwI6M5RM6FgVDu1yDuahsmNR04pr5wybnBunNjuO7K/xzMzq1sRWSpTcwNdfZZ8eYYgv4ITk4CYsPvVo0JEpBE4xgIxahGf07gfvQDJZej0OzY4rzQ6X2IQ089qSMkFLyPZLmH97tEAsh1gjL+u0LjO8x5oWtXn7Z3fZ8p7ZRjeevmAODOh1dsPo7ZXDy3jImOoa0pquJY8/sCzFEbU6gSRJYOgFDnouoEyJiTI3Q8jbGsc/b5RFPPS9aGqn6fwf1tTKXccnsT5TdIDL9zwSVnJSgTCJZbAN79rXukrEAgEAgED8IBUEDzLQCFwRh+xoyYVZOJRYP61wHPdpzUdH7oiEJdB0pdwm0ifbY90yFyQts7YcY7ZdY+MpClUINaLd9jMQBpfPY1pKwH1ZFzKpHIlf8zx31yRpCygPL1YHm1eFhzPM/BnAPANq6ONDpyhP/TUW1juH/iQmEg/yHoKDq9B8vRBro6nij3vDE4Kc6gihIY42+vcF6m89r3YTm3waoiL2w5AArQR6nk4L8vf4I6M2b9dgPmxIDkOLGtPsdKu7qOnqVIgAFUx2me1dBh1QmwAP/tAMB+P0MHi84RkcHytrOFYQ5PNeS86xjLvmO3u+6JsNwC8Nlnn2UfffSRbAEQCAQCwU46AFwhpr6GaBtyxh6/Hay4jeruCy9acAbUdSoQMTM5SkLKE0K4bSulFDHgs8ocsuJqikTgMnoaJ8Bz9v9RgB7zqAHVCTBx6COVKbLcpyzTLiXPHCh6RgZ4oiGbE7i/6niC/VP+/lQhRipRs11rchyQ02BegzSBh672A0hXjq+FUsaM1W+imQPTGmU+RRJOCdoKLEtX45hRj4mkqKeY6XyhjDkisuV1h3i/iOnwFK+bwuq3XBQGR0Cs6GUI8eegOvCxTo6PucFpAOAXgh4ShUROlLo5GXTbAUJAZR1hO/ehcs7FUB3Xl4M9QmzByuFThrqnMKwTFx9//PHVJ598UoBAIBAIBDvoAEhbkp1uUEab4dd1H+hq4qMjaB6O6CunQIM+ZQbwQPn+wKN9i0AHS+Lh8PFJ3hfSTpGHjAiWM1VTWHCdZHgRLIcB02qfjtyqZJTrZ27RmxCdG8HmtxuU9b7CssSasVuAPTKCVjRpZZn0M/e81gYKye5tqG3K/nwOVaj6G6iOekwYwRwaCFNW874UBaSePnAG1TYjyhUw1zh1ckZyTVtaClgOAU81ur5OmBwBdYm/2o9lFMWl5/w0gcrh2bFcE7KyvWiBCJMToCzXRc1nK7Vx2b77bMxPcB7IPeXsoa6ZEnbaxsVWgbYAwLdbRrbdWSEQCAQCcQAsGehtGGDDLZBBRmvckLg3Kc9CY8z4rNzEjvv5ynGVPW/RUB96lgUcDoVhTX1xySgMRPHI0OcA/rkSyNB3GaltnsJga6drR/v4yC1qlIn0kjKvx8zREWLA5wFlyD3146imrvu0h881RJpOGCmPoFolXbQ8Jlz9X3joY46OC6jRdz448JiDfa5xOQKiFgkktVsHlvfB28pIWz74iQR1jzxsC3OwRz35tsWghbIM8EVjgpfRNi56sPmjK/8A2QIgEAgEgl11ALTxMG9DTltlmbTYToM19knR4v2KNZV9sEVyQmTkLZGZda9QDbZY7hy2b8UuX2F7DGqUJd+Cvt6FPmlKkosVlLvOKvwC2nW4PkTMV3z9qiFbAAQCgUCwUw4AWp1oapy0JecxYQTmcNIDzzansGv1fGeSXUBYmOmuw5Z7IgZ7VMiBh/5SJu9SzrZk+6fEayWmLRvHZT3HYM6WnoE7EzwPR58Y5MRQZcd/DLroA4oQmLUgo3Qk8Gz81J9NP4cVXOODJuXUyREIakO2AAgEAoFg1xwAdLZvaSieNZDVlpwIqv2pIXBlUuayyTAu31/DelfZ+L06SDj5XswEyTu/zkSaaD9qGXZYJuF6C1VIZcY+j6HdEPRtRrpi2Txre4oEYrrhOiewnIxu3pLMEepdiu9Lfd1j8hNsjz5UCd90ci6hclKdWchytKb2pHDjYsXkr6kuRi3IIRn7ipyMkeQmn8MKrvFBk3Lq5AgEtSFbAAQCgUCwaw6AV2jY9xl5qGMYtyUnAXPSJB+DO/eUTZmu0zUbgH1NmWONwc6vyw3tmKLToyRMT+HbZEplXQ6hykg/ZwRsFWSnrVXOtlHWXz26bWG4l8+JFWV/dDWfX2L7rzMagBxZV2BebcrALzmhCQVUWd4Bqn3PheJoyKE6K/5IQ9657h1Y2ugC2/gSVpf1m/orhSoT+Tqg08WQOaKOnL483gSCtUG2AAgEAoFgpxwAJUksV+VGUJ3fy0lAgYb+W6gS8+hIdlty/oCjo28X9C8vL2t9rzH+aUVziETlGZK6cU2S1AZiqJeskAjtMdbpihHUBIl1gt/rQqtLQnda877njOilNQgOJymrSuR0Ae5w/jsPEpjC/bPaQdOWKfivXkf4G55Bu+yfa6jOHbeBom3K1wtYXuk8huVj+TLU91DDlOpM2c9vUJ/ewHIUQA+q1fsRLB9zl7L6FUq9MljeOlDOHYdQRRWsIpeASv7XtY+YnBsuZ9cMr+k30GlfB0DR0uebwiLwc2jpeoHgHmQLgEAgEAh2zQFARtA53D9yishpavh9rhCoNuS8Jwzz+RymUzOXKorC+r2F0Bwo5OU1EpfrNT+4C4dR7eMYOMB63Sgkgv+ljM8LTXvUJd+JQvQuIHzFUUd0ZpZrV0HWfIlxiHMocpCKrsXx0UFdVM9lt5GxrkZv+PibNCBvCyYvRjkXcD8KYA+q8+rpiMSFxpGS4PUZXl8wQrtg+tyB5aMW20DC5h/VuZBoHBS6fjtUPptjX/mQyGuojp406fi1p6wZLOcH0L3Xye+wtp7W/LwtcPl19HJiKOckQH4bx+oJBLIFQCAQCAQ76QAgY3YRSAp1BJXLmTJCZPsbqzKTJIFut/ue6GtvHMfvrzk+PtYRUxUDNAaPNMZxufL4AsJXHUsSc+xxnWmF+cJB8gYWUj1TjNgClldaOVFcoJy+Qqapn6eMfIaQXLWt00Dd0+lZClU0QR+q8PI6joqRhkzpnCqmNr5rOLZ0CQXHcN85pmv/PpJNU8h8D+vh6rO5p/OCdJlHdpRj5Q0s582IQH88V8HIe8bIuzp4bxS9zTWE7Ig5CNp0AkTKPMHfz8B+VOAIy1Tq5lv2+THq557H/QfKOOF6TuUbeJL/FKqoJT4+bGPFNLeFft4W2pK/qfILBEvPc9kCIBAIBIJddAAAGsAhRNBkYJEcX1na1aV+vw/Pnz9/Hw1Qkv2lG+T5e+dAlmUmI/9SMYxLcnEK9rD3GdjPoOZh8+kG+8127wtGMnWEN9JcH+oA8AFfXcsCSHzCyhw3JAbAiBt3MKifZ2voswG7zxTb/RL/LqBKCJmydhhZCHystDXlIOAnSySMVM6VcUa6kUMVnXON/3eh2t9P5aSVbpuBe8LacwbLyS1V2FbKJsxhMgZ77oA6DoAIHTw5VAkB1YiAU1hO9ljA/RM7FvjZDVTbbC7Ab7U8qanfF1DlOimUuQssOlPqQRunALjGPHheo8oPhZwCINgayBYAgUAgEOyyA+A6kAi+MnzO5biiAFKTnCiKYDQawcHBAZyenkKn863IMvT//PwcZrPZ+2ssZYjYexeuHYYsrYSWxOXZA9KByxZllYYPrWr2mCH0CqqEdHzVEzQEJlFI6oQZ6CFbBC4YGfV5r6Jpgri5Uo++gQiN2f9DuJ/RnO/7JrKpIzFTVu437Dt+3yfs/ZgRSSKi5Yo27cPPWRtQX/oQPO4ESJS60rg/B/dqN3cCzBo6ARLWzhwpu9dCGROxxuESW+QTyknqex5lTRqMMUoAufBwDBDaOgXAFFrvE37Pr5FTAAQPBrIFQCAQCAS77ADIA3+fe3zeCZTzYsk6yzJI0xSGwyH0et8ec1+G/9/c3Lz/a8EZLEcBhEB3nOAYSdYADctM1OceiKz2FRKSa77XkTHuIMjxM77n3HRNZHEo+L7X6eQdI9Wh/y80JHwI1akM",
		"HUaK6buE6V+p3OWK0ilrP5Muh6y8cgdFqpCkmF3bU8aSDZTUMEa518r4OKoxt7TlBKAQf1PbTZW6AjSLPAEwb0VS62ZyhvlCt+p/BatNbOcTWi/h94JH9+yTLQACgUAg2FUHQGgegLnl84IZ0qYogFQj5969S6I/Ho99yqOGfHYYmUsD3i+U8tAZ6HMHmVgXhpbvCo/vVwVOqE+ZPvU9CDcRp9hBwny3CBB5zDzfrxKkV08NZV4gyZ5p9LijjCsaSwnTwxFUiR7VEzgODP1erlR1mdySOB6z8tH4zD36zDUmRliOuAYxbOIEMJWtB/WPKW2NMIDZGRYig/ootB5F4Oc+ofs+4fdthdzLKQCCrUG5BUBaQSAQCAS76gAgIuyzal84jKecEatOAzlNMEcSwEOrXe8XGlLL91RvAwYWMj21GN89xfguyVXd4/tcoBwQvg6loSI3ZuTxBKqM665rODkicl9nC0CbiLEdMkNbnDNSD3A/s3/CnClH7JoR+/7WQG4WGtL9RinHEVTHdFLUzIw5EGxOAFuUTZkc7xTrfQPVKRx5YPupTgBAh8WgBvk/Afce3WHD/l6XU2EC+u0AprHf5BQAajNbaH0G7vB7ukZOARBsHWgf/5dffjlp8l5aUiAQCAS75gA4R8OJEpUtDOTeBUpGNwV9wi8dMWkbdRwLajKwZEv7zmRgR47v1D7Ka9w7ZNXSN1pigHLJKaEL8fe5hjtuQt6vGidY1jea78p992peCb4NINK06bFn28+QiBcOB0UBy9EJuQeZTaFa1Z9rxkuB9Y6ZTlI0QOjYnEAVjUM4M8hpQv6J5JpI9EjzXoVPEsAR1Hd88uMrTe9185qcAiAQGMD38Td5Ly0pEAgEgl10ACyYgVu0QL5D5aQN7qka/Ncacuh6X9Qgr6vAix3TpdBVU5NOtLUNgIheBpvfAkBOk2PNGCEyPPMkoSW6oE+wx+tOZJz25/N9/N/Dz2+Zk2CukPeeJ4GaszpEioMj1oxp1+kGvsScSL7qTGhK/m1zUAzLyUJTz3kIsEw9zTi5ZuOBrnFh4PFe95tVnwIQggHIKQCC7cIf9vH/27/9W1T3vTSjQCAQCLYVT58+fW9zqg6AsYMMdaDKps0zj8OK5IQiMTghxkrZbO9fe5DUVWMM7R/Lp0OTVchFQzn7Hn0Ya0iU7pqJpq+2aQsAgD6ahK9STmE59L9rkVVeS8dRHqCMGyb/hBF7U5hzqhDVRNPW3wsg/6QTPM8HP1LzmLVzxsoZgiES5pHBCRC1QP5d45LqdBz422ss48DjmlWM17ZOAWgLcgqAYKsg+/hbx+KTTz6RVhAIBIItAs7L9xwAmUIACg2JIeP61ELc25LTFBMIX8U/UxwAtO88R4PSttL9FImbz7X7BsPzxZrIf97AAOfEtcl+6WuNbkzgfng/J6267y80cppuAbizXOfzv89e9xR1oAh0QpRtv8d0FDTEcMGusTlaJmzMUp6FMfg5vxYagkzj7VzRtVyZG8gBk9fQuwVUDrsEx9xAmVfaJv8A9u014EHcfVak9z36TCAQCLYd048//nj07NkzeP36tbSGQCAQbBgfffQRlHPyO1ypDoDS6I9p8n73eqsx+DsK8dChLTlN4Vpx88EAnRSpp7zM89oUmq2ANcURVEe3haCAZYfNoOVyucL7fU8B2Ca4nCQx6PNkgGWMqJ9d4d9rzzKdMWKeot5SErg6DrkRyiiwLrqjA08UZ0PdFbcJczgAk1PActLJNsl/6LzTJnFv4mQrAj9vkl2/rWuggRw5BUAg2AJ8/vnnxcuXLycvXrzI3r59C4uFDDWBQCDYJH74wx+WToD3kcGqA+AAjXMiBjp0GYEwwUdOhob6mYaY1jWYVxXCtwfLe8abXHvQUr2GFsN+6GH0b2MGbF7ua025Xd+7yJIr8eS8YT+ZZA3W0HZnjjGpa4uclXXYcPz0wG//+gnU2/+vcwLMNQ6AcvzF0OyIvwPYfHQM1+s29Cc0239odv22rvHV3brlhC2fAwWCh4TeO2Mz+fGPf5y8evUK/v3f/x2++eYbaRWBQCBYI77//e/DX/7lX0IURe9zj33++eeLJ3d3d9IyAoFAIBAIBC3if/6vpNwOlv6y+BV89eVX5UfDL//1l4PyzeRiMvvP//zP9Oc//zn89re/ff/dT//+pwP67aeffjr7xS9+kf7yl7+EP//zP4ePP/54+MUXX7z//kc//tHs17/+dfqb3/wGvv7qa/jqq6/g66+/ht///ve+RRu+s/0G62iDly9flgs95Za994tHpQNAogEEAoFg9Sj3+797dtC/+btX7x35f79I9eEWl5uyhR94vjf9PhTlvuSJqM2DRJn1Pga//flNPWP8HjHeu+7vYUvlPES02e8lKG9AOR+9AH1OEsqFkcN6Eo8maJC78qOUWzmmDX7vO6/6yJN5WfAHPHnyZATbkRPj4h2RFr20oFxpKo3Oly9flhFRSbkHtVyNEggEAsHaUJTbsvgHpQOAEpj1AgnzgYFs2+QcaK43yYlg+Ugv13v1HnUTdtFv5KG+Xsxq/k49rs4mJ3ZcsyqSm8G34cZHhjqrdaAjA/MW5JyuUI7veCLym6DsXCHcfGvGNei3DpW/7TASHYO/M6eOTp2i/CkS4bHn/xwDlBN5zjmA8k5gtXvTL1lZF7Ccf4Jnzy//Ptc4JS4hPP9GanFwjD3IXArN8kYIHhD+4i/+IoHN5tABNl+t0tHx0BwBuWivQCAQbB4fsodoXcKs/tZHjuka3edp4Ps2MN5iY3PW4Lec2G2DHC6rie7BinSBnFk9T12Ygd4Bdooky2T8zJXvYtTBoUKY6sqJVyTHRfZ9V+iGSERL+c+gSu7Xw/uNUHZJjl8xh4FO9+6g2v9fXnOFdYnR8bEPlePQ5DzgpyGkSMh9/1f7PfQUko7SN22NL1D6k4+ffcXRol5bGH4/geVjU03oW2Txe5rk9Q1jXfBI8fHHH/e2RB+KVd/gITkBBAKBQLA9DoBtxQQN9iGSAtt7upYjb3j/to2LGRKFpgZD2lKdtkGOrp1DSYWJwC6YgVZX3shAiG1QyX+GdZwE6n4fls8o3wY5p2BO9HfnMJJjR3+p7VvuF71kRP57YF8Vv4Mq+ifGV4pyDixE+k7jCJgp+vkm4H+OI2wz32R3cyT/8xWOL9dYu/YYXwTfYxz7nmU1yeuDQMDwxRdfSCSIQCAQCAQrcgDwLNbPIOys8qYYonE6QGPe9j5XyhYhefA1etdhZKZYJh2JKT8rVyqn4B/660uUXXXbhBybrIvAvqAz1vlKZ8+DmJS6k+B1ixX2/yn+te25n1l+O2hZznEDORlUq/U2sl/2wytsW3LGhO6tP8O+Lftp1SHxKmh1sc+IfBLwP+ESxzTfapFo2quAKiqhD1U+gFWML18CL6RbINgClBEAEgUgEAgEgnU6AAYKgV2nA6Bg93e9TzWEOmVGc9/D6PUxeC+hWlHT7aEm8mQKGbeFRHeQ8OyBX5SA7+qbq24+ciKFENnklHXoYvuodYnZ/32Hs8QXCSsjeNSj7MNyxfcG/58a+pGIYGgiSfU3TRJV0ZaYvEU5aUM5iUNfTmD393nOmX5OUEdOPf9X2ytT5s254sxoujrexAHwEPCQtkStQo5AIBAIBAJBkAOgbaRoKF+v6X4JhCershF/lTzdwP2VyfKaMRJdlVhOHE6UCJb3ES8s5NRlFLdpBN4gAQkl5GVdB+z/mwAHB7WXbtXzGbbNWwvRGUCVTI7el7pwpWlzE+qcIjGSaeVBkUqVwLv+B2X8RobxIWjvmVIX0SOQI1gDPv3009EvfvGL5N2r1VMBZOVfIBAIBJtwAMxaNipIXmeFdUqgSuJl2tcdGk7ccdxrge8j9jllKc7xsxMPB4DO8OMyQoziKPD6GKp94eQ4mWJ56TufVUVK6LeA5X3mXaiiCE48y0WrnpfYB0dYpjEj+aYylaHuh+gIOcRXAdW2liOookRCCOG2IeQUBB/ksB3ZtR8C2sgB8JhQZ24mlON4V7dErUOOYLWg533rixu76AR4+fJlhM/8fVENgUAg2BpcfP755xMfB8AuEoHIQQ7rrsARoe2y",
		"/4+gWuWb43d9iyHna9hxGTHoM8KrBLXJin+f9TVlV4+QqPexrEUAIT1Xro+gCpHOYDm3hI4EuPqXnCjnFmMsx/alkP8OOgV4iG35+S0sH0Wp1qXpFoBVIyRBoQvkpBrDerf7bBvqjiXV+aLmAFho5tQC/HIAPBYSBdhmBVQJK70eahC+JWqEOj9X5PSV8dVrQY5N11xyeL3KZ8wz/B2RzhcecgSCdWL2zTffJK9fv4bFYgFff/21tIhAIBBsCE+fPoUoiuDZs2fpy5cv9z///POTDx9wfdtetVUN0QMktRkz7g/QGPNZ8TMZiD3l8zG7vjAQ/xTLN1OM1ZnFeCWkUEUZjLEeBRqPdO9hYFsVUG2FKOW+Utov9iABHEcoa4zkwCWnYCSC6lIo7XeAnx9YDOVRICGcwe5uASDyD4xcPNZw9VGLc0YG7eQAeCzYY/PAHjpRVqWHicHBkCrvyRnaRI7PcyWxODxoe1iHOQIA59cjRacSkG0ADwa7FgHwzrjsluT/Zz/72XvyLxAIBILN4ssvv/zD3x/+8IfZu3n64qE4AAqD8VUSmtctGtnc6AI07ClsdwTVmfG+Ib9Uxoz9DQ3djwL+16FcTTrDco+hOh994WhfWxs9Y22Vef5uaCBFIybLV15fKf8xcxiMa/R7m6vsbULnmDjA+mYBcjj5B6icWbOG5CvD/nPp4DHqKpFjlSQTAUoCiNUq29zXQSA5AMIwwTFKJ7hMsb03vQUnY+NkE0hYm0ygcs6Vc+ZA1EawZTiklX+BQCAQbA/KufkHP/hBGQ2QPmQHABlO8Qrud80M+XNGclIID7tMNkwMeIjpiYYYhjgkVLIegoHBAfAWzBEIhcORoCK1EGfQfLbtWwD6UB21B8zJkQXKoaSV3MnxpoXyjTz1J3P0xThgHB9AtQK6rzgLyJHzVtNuvgj5jeQACHw2KfNgtKG2MM0hMYQ5Q30ip3zkkVO2YO3iOo1DINgYfve730kjCAQCwRbim2++ef/3IW8BMCUBbAOHUO3r5SRnCmEJDslAvGJ/C42BGFt+X3j8bYIQN/7bFo1ealvb/fcdjgQdYeZE0Of+dUhvKHQOCZ9VT9r2QdsYMqgX4VAXWQDJN+nTgaGuiUK8fNpthP+/Zn18AtWRlNRmKY7hOvNDyGp0mzkAmiTI2xXsY38dY59fgL8zq077TDRzkU3OfktyTDJtco4t85lPeQQ7iDL8X04CEAgEAkHbeMgOgMEKHQAUgnnCCB+RjcuGBqtqZBKBmRt+v6/8zvS3TcO5qZz9gHZuA5FCzPugDzPfFJpsMSAnwDmsfz+5i/z3lGvONHqcgz4JI185z7F+C027Ldg4KUnjC/zbd7R3+bsykucK9JEfbSQBbDMHQLKi/lts8PcqUmyPPZSbrbh9dHlVHqocgUAgEAgEgq13AMy2vO0oM/9zNFZjJP9pywZrYTDm2iIE2yYHIDzpIFgMXuoXTuxKUnED367Mzj0IbIgu1tkC0FTXoxbIf1vjjRPCCVT7um2EJDd8lhpIsw4TQ7skHmNJR2zbaoumOQB0Y8G28vvac1yoZTnCescNxjzdv4kuZhC2hWXY4F7FI5AjeACQKACBQCAQPBYHQLrlbUeryqNAQ+wI7FEC3Iifa2Q8JEPV1EaDlvqoXEEuHTXnisySXHaxH4YG8liXCI4e0fzhs8LfhJDkLRDwfIPtc4BkODQHQG4YCy4nDeU8cUUwnMH9XB3HGmfFwiBH93t+f1NfzAPK4/v7tuaKhypHIORfyiwQCASCew6AITPS65K5YgVytonkHkH4yt3cQHwos3VkMHLPxFBtDZQ8y0RipkhYItDvTW+C+QOXU2ICfiv8u4Q222cO1f7/VPnL55kC/KIcrpW/NrJsQzn/vNKQ9VeKjKlBlun3YCjfAvVkEVge398LBIItcwB88MEH0hACgUCwhfMzOQAGLZC5YkVytoWcTmH5/PmmOBMVXAsGHvpmIq55S2V4qHLUdnwoyFcsN1+hPodgsuHfr1qeQPAgDLVdXU0XB4BAIBBsLz6UJhAIgkFJIMtkhjF8m4AulASn8G3kwfQRtRkljaPElpuUs8vtSLoDUJ0YUGxJ2eYyPQgEjxtyeoFAIBBs7/xscwCUe1ZP0dAsYDmUddVomoyM9r+KHLucx4IMyVKTqIsYx8Qh6HNTlPcYeMihveD7+D5CmdcNyjhiToi2yTAdS7dAvakrn04qINKq7nNft5xV6NgLbKMmMugYPFNfjMCcG2UC9Y79JN1uIyrJlVND8PDm1kPUIXL+lPp3JTogBqZEAAgEAsH2whYBkDIDcRWrbDMDMU0byo2U8oscvZw2HQl03Nkz/P8VMwBTfL1gnxcOQhLj+9ygk0UA0Tlmvzur0VYlAXYlKDvFtnCt5u9rZGX4mtcoX8rkvYJ2Q8QThWxfsP4I1Z2YyZlr5KjOLdv/Ojl1x0HikBFj31LER6EhOGUfjFkb6Zxr3KH6hJHuCc6tXMa5RkbGvreRsVKmKeeFCR0cI00dACnW6/CBkr/UMCc9RiSojwkbh+WYeMp0uZw3j0AiQloh07tYZokAEAgEgt1zAKgP7XN8sJ+iMV60cO/UQEwJEzRq1b+hEDnm9i9/87rGvfusv2hVNtGQ3WuFuBARMpGUkUKQC6giTy5hOUlYWfYTT2MVkJj4kpwI28f3WDQik1MPsl4SviGrf4z3SfD7s8B+4E6IM2jHWRdhv1EfL5QxH6I7x6wNF7AcSZTCcnK3a3ad+v+I9aUqJxQx6lOCOqQjrANs3wL79Qrb4xkjOEOoTn0YanS6y/rkGudRqncf2+YEqlNBdDI6HuQflLG4B2EOMsre32ReP2bljeBhbM2gZ556ikOOffUYnQHkGFzgPJ4b2o2OTw11SAkeCCQCQCAQCLYPui0AERqsh8yAjKHKwDyDajX3aA3GT2L4K3Lak3MB4Wd295TfjBj5PYdq1TzDFye8RHxKwvNcQ7i6GqI2MziISLYr7LpO5EQC9qMadbBFAQzwe2q/U0YcF4wEjtBx4kNuM6VO1O69FsbeWNEnndPvwmMOyBQHiiqHwsUL1k5qu5Ecrht1ci6oBCZi+jvR1D/D8uocMkO8hoj5VFN2kkErpLytJvibDiuLTgaA/7GSC8V543OaQcz6uek2gI7yfrLB51uk6Esdx1hmcbzQc3AImzkFZdTSOK/TrjMceweWNs3x+xm+noOc4NDIUNvFcksEgEAgEGwvPlQe7An7f44G4jn+Tdl3l3B/lckU0l8X5W+v8L36V4e+yKklJ4VqhdfHiRBpDH81IVtZthu8tsfIQI4ElwzoXCHQPvdTjXSbIZyucSzZogDOoFpNjpR2pjwAE6zPhef9dP3ZxfFaNKjHSCFzZzXJXKIhr4WB4IfIGUL9xIkqqVtoiHIHrzux1Huh6GXPcM2Jw0lyyuT0PBwoNvJ/AFVodgp+K/odpSx1HQADpT1OYXOJCdVnWZ3cGDbyX7A+oTG9TmfH2GPeWxW62L5HSpuSng4UnTzC58AI/KK1BA/ECSA5AAQCgWC7nykfMqMiUYjTNVQrOX2NkTWC++G8vsTNBz4rjD4Et205vuGt6yhPn5EH20phD9wr/RdMZkjfRVifhWIkH0AV4s1xrdGVpKa+RBpHgk/bAVS5BvIWx1VuIWjAHAC6sqjh7y6CQiSkbN/XrK79BsZ2Bssrp1MH0YjRwCeiNWX9csnqOoX7YdSARI2SC94wcmGTsw/6bPMuwkvEiUO3R7mP95lYdIu2DywYkT7TjDlq00lNGfsefTbHsRYrcwCXpxtfMSw73YjA5Ra9Lq+59XTa6K4LWTGnVfxnAfqsI/+TGnPKyDCGh9im3EEwQn1ZOMaJb1QGeOrwnfpMX4PdcAr3c7jQtq2hwVkygcqhJnhEBqY4AAQCgWB78SEaSx2NAZdDtT830/x21/d6ZoxA+SJFw73pvkYKm6cwSRtxd5WHE2GbUesyeilpU84cP689iLRJ/tzQRk9rlK8OUk2bzDSf6cK8iwb3zA2EiP6ea74vyf+hMvZ8CQo5lPpMr88NbR/j91PN9+pK+9zDaI9Z342hOjFkzBwUBcrpGNorYi8fOW80",
		"+kJh/QXqcKG016Wm33Wr8zFUeQFSlKmSyDGT1UOSruaXuMVyUDi+mt1flVEYdC7WEOhjxflzAve3NejGFM+hYEJfM9ZPlHFxoDhlfHEWQP5Tpe99nKYq+Z/D/VVpcmbYZHU0daOxMMfvTpX72rY8dCHcqeoi/20ixvK52picSBes3mM2rlXdofwAV9gGKUgCxdpketeiAN6X+QPZAiAQCATb7ADQGeb7aDgtwJ4B3UVWtgkpMwA5qQ1xAORInnhyo5lCJn0cA2XG9reM/JkQ4lwZWr5zEdoCqigCTlZjj/vOISyJWEdTpqZbRUxkxqQD4NEeIViA/RQA2uNNRwmeMFIwgWr7xdyjz7seZGIE+tXGG+bs2YPlUxw4gVS3dNjGw5yRgxnWp8PkHFnkDBn5zZlDwCZHd9QdEdIE60jRCJTLIdaQ2omFcM+hygExZvNEF5YdhxNFp1XHyClzytB9TTJ8MEUiPcI55EzTd6YxcoC/ywLGgC5Couyn5wanimls9ALqOVDG7pnnM0ZNRJpYHB65gxCrOjpg/TwGfTSFTs5YaaM7hSDTs8PFlFZB/inC4lQh9rbrgTlBZuC3ZUxI/yPFB08kAkAgEAi2DXwLwDMLUWrj3Pm2cwPUNXbIkN9DQy5mxvkE/KMZzvE3tGJ+XYOwv2DG077D4PdFEzkR3E9655tU8AKqvceuENcuVGH3hdJupjBxl3G50Bje/QCyTyHfKqk8YG3T17THHKpVs7lHOYkoZ1jGIZb9ENuOSPfc0U+nHnVKwb3iRk6sQkMgQ47vOmBkQE2+5hrrA+WePnIGGjk9pr+ky+RAiDTX+pDRK6aPtIqfsb4/YUQ5MsxxF0wG9XuqkVF+fgvmrOpqn50YHDcuIn6CjgNXYsGpwwFEOQdcxLQI1CUeoVOAO4eCOi+PoV3wxIyZRf6+Zp5rY9WfdKPTcr3o+RU3kFFA/QS2gkBDbRfLLREAAoFAsL340GLkjdCoOoflZFWhSDUkZt3gxlgflkM2+8zR4Qp5plBbbrwPapRnFREAqYM4QoPvbTiD6oxz2zF2PMS8ZzDgQw3docG4zQKdQ5GBtPP36opXDGFJ04iA8dM01Pq7iJJu9X9k0JO+hjwdMMJI5HEK9zP+5zXrFSl64SLaM0aWedIwm5yZxrFAhHWs6IGKiWefReyeY0We7ijDuWZM6MqVWmSAxgl1BfdPeuCONtsqbG4ZrwWYT7mYgP9+7RPHWLuAMGdvE0Kq9hdFPTTZopZC5SCeoCxdBMC1Uocmz0sd0T4IcPT4tPFxjbZesDaZov7yY1sLuO/UVXVe8EicAJIDQCAQCLb7mVI6AF5byEaGJGsPqqPdOHbhfF8ipj3F8B0yw/4GquO6XMihXmZpjlVEAGwStHpLZHRicJwQaZgb2vUM7FtOVCKTt1D2uYceL2B5pZvIWBpYhtShEy7DvW8o/2uNbE5e+LU9RpIiZUz7EmRdGQ6gSgg4B78s5alCagoPOamBCE1geZW+DrHNsa87jPS9UHRSzTFwqNGfGyS/5LxQ+06VkYP+qMUp3F+t52MpsZDGvCbRDlnVdV37LFCP9qDaVx5jPc/AP+M9dwJQO4U6AeYah8sxVNtKclje+646bgr2vOxCO5i36ASgMdZB3YoDylCgvtNzqeyXV9gepb4PNL87hmqLlOARGZjiABAIBILtxQcOkkkJx2b4gOchqhPYDa/+Ao3IM6wrZfguoMpS7LtaNAf7nmZflEYTrRpdW167smrCidpYMXxTZrhOwL4q7Lv67EswfRAH6JGa/DFtqJcq2bDBdhrEIOA3JiLsk/TP1ScnoD9azwTdfn6XHN1vCCeG+WwSUDci3fx4volBPzMkmhcaRwJv+wGTMVRkxGyO0pG1oYF4J45xZMO+g9T7joljx/edGmPiCKqtKQBVAjlf8L5OapBm3Xag8v63bJy9Uso80dSjp9QD8P8DNo8cBIwV9Rl1oLxCUdbzOVSncPjgAnU+Vdp7zyCDtjydi6klEAgEAsH24ENmZLqOTKMQ+QN8qOc7Use5YlyfgP4M73WS7YlCDh4CJlCFyJYE6gUs7zf2Xcnje8FthnBbGAYSlB7Uz4uxrzgTClbXxDH+MsN3I4vu0u8mmr7iK9uLltp0Au4j0cBD921yXOPlBKps/nUcGz0krnz1mPbOnymkcAT6SJRSp6415dLJuESCNLC00TPw39bSA7dTlydXpIgcnrAuBb88Caly3zOo8oFQLoe0xrMiR3LaZf+H6uEc6q+W85wSHK5TEnT14NEAueb70GcZRQK09fw9g7AEjYdw/yQcXRQVP5njDAS1sat5AAQCgUCw3Q4AerA/BXvIIjcUJh5Eqqj5+aqxUIjFLu9NHLK2q3sKwDDwnjZZU0ZqM8VIngT0D4UCZxrDvtdyn4WShBzrGNcshxpJcADujNqx5bukZv16jAwetNimIXJ0+/ldcmy/4e17C1W4c53+Ke9zg+NjykhMDNV2KNJHnYwpI0EURXDG+oQSQE49nRquE1l8s+2nTI95NNMByh9huVxyyMnCj8gjMrgH1f7wwwZktQlxbBJyTrkbRo754QTc27SoXy5aGl/Uvm0/E31BDtrydY59tFDmm4w5So5A9v8LBAKBQLCVDgAiBGXSKUroRkZqjg96lxG37/jf9blqSI1aMhweg5z9wL5pUhbXvUoDlY4JiyEsC7hqXPMIgp4nISA9fQHm/eI5K2sdknGO7TAJ/F0C97cRqPkFTPkRTqBe4q6Jo40vavZPG3qcoqOHCOSM9bXp/9TDacMjLOqUkXR4hOVTs78X4OfUKqDaUjCBajtMie9B2DaWHlQnkOwrdb0G/y1Z+5axRNEMPtn0I1g+Ik9X3it0AOwiJlBt5eCnSZBzx7YVpW2HhE6vNoUCKgctRUTkypjmThQh/w1xd3cnjSAQCASClTkAiGjkNWVdNyzLQkOW2oDI0WPY4LfXDiO0rZDyM4Ws+0DV4ZgR57yltj+r6Tg4APNq94GD2E5WNAfka9Idnc4MlbF/7fG/S/faIlwUHt+DKpydCNA8UMYJKxNFW9QhRgU03zLU82i3Pc/2nQeOxV1DofSfoNLrI6i2GL1g44MiZiTp3+NF8fTpU4D/TxpCIBAItor0f/ghfPLJJ++f4x+2KHfQkpxhw98XIsdLzmBH9HXeQn2LHahLXVK4CQxWJCf0/3WRnXwLZQkEGyd68HBy2Ajaw/nTp0+z//GD/wG3xS3893//t7SIQCAQbBjf+c534LNPPyudAO+jgz9c471j+DZcsPxr28NrMihoP2mJaw/DY1UkpUS5IngK1cpyaQhdOIz7NstThtfXSXBl2o+phlr7freNmDX8vRp+/tDkCAQCgWAHUIb/79oWgM8//3z+8uXLkz/90z8dvXtF//Vf/wW//e1vpTMFAoFgQ2Ar/yVfPXo3T2sjAMZg3mtMoX+hKMnqDSOtoeSVEkoRUvg2aWFvA+2YYRuVZOoKP9uH8DOrVacGweeIuyvw26fLMQHzCnPKHBucJCbsu2gNbUt6V3jqVFm+XFOXsq6va9y/z+r5UOUI1ody73jpKDyQpmgVNG9egWSYFwi20Qkwefny5ftEqN/97nehfAkEAoFg43PzHzjThwaC6yJpReA9+R7asxq/7xo+G1pIbcgqua9jI0XirUuiRY6BV+C/X3tkuIcrMVsp/xj8z8deYPlcUQojqPb2xjWcDAD2LO2uDO4Z2I+j1EF3RpKrnjai/BjkCMzIcGyVc1TTvd+HEHaG/WNoW5pj6maHz9i8Wbbtiwb9FOFzRPasC7YWu5oEsFxhAtnyJBAIBFsJnQPgCAl7X0M6r2qQ95lCxBNGopsaXYnlAdMJlJV6PKxGsHwkmNo++9huk4D7lte+Vsiaj+OibL8bz3scodxjRx0pUmMO9ZMMXsNyZneuB4WH0V/A8lF/I1YWrjPH4JcVf8bI88TyWShxuFT6QgjEwwA/+o0cLqOA8XDC5sgTWHaocjmJZZwTQS48ytp1jCU6DSHk2lW3bYpjsM7xk7HGIQAGJ0AC1WkkuuisLs6LFKUhY1ggTgCBQCAQPEoHwBRfba0+pob/Q0KSC43h5+td",
		"ntZwBtgcDrYkfHRMV6wxpBM0gHuwvPKfaOpGR6zRtedw/5jEOZal71H/sp0OA0hMkxMG9qFy8iyUfp979PtcqetC+S5XnCW++nft+CwEHSZjEUAcEtBHfZSoE84cw/IxZQVUx3bOHQ6RuqiTkyDUQTJbsRyb7Dnr24KRzCigT0wk2ldOAn6RVplHWUhOyLU20NabooazIGdzceJwAmSgjxYoLO2gOgH4drYujrFcmRtPsU4zDyfAJerGHmxPYlHBdqDH5mCBQCAQCHbOAQCgX1kN3UOsrpKq6KOx5bMC1ENjLlI+88G5pwNghsahi2QsHI4KEwmgSIhIcYokFgJO15av72nuXRJG20r4ghkmHY0TYRVIHfVq66i7OWwmBwT189BCSGxjIrW0W/n9IEDWTOn7GMlQZtCXJk4PVf+va/zGF9crlmOTfYRjZc76ds+DQJNO5spnfIsKl+Mi0LnH/fbAHQWT17jWhhuUs4DwVfMT/G3i4QTos/HCI73KOWJf0x86J0Di0V8HbG52OQE6lvmdj8vMoAuCB4ovvvhiZdEjsvovEAgEgnU5AHR7v08DCeSMGWCUMO8pGlExhIWB0h7NW2akr4LMpg4jcOEwolNW36YOFB15zg0E/9Ji4KbMmB46yHdm+RsC3W985ISQ6ZCV97bRDyRNJrJVEtRnrF32A/UhVmS9wPHVs4yp/YZ1n9aQo7tWdbTNAuTYTqtoWq8F3HdEFVDvFI9EmQ/qyiF0FWJZBIyZInB8zUC/Tz9m85lurix12bTPf8EIt8sJEDscCeDpBPBx2oQ4AVyg+lM5JmJmCIT8CwQCgWDbHQA8vFklt5mnQTNAw26BRlDCjPchVKHLCRq1PkZxoRiSbWMIVTjoCPSZu2lrxNRQhj4a5+s8z522bHQ07RVDlbdg6ChX4vjrSxpKXGiM8wtmHJ/A7u63TZTxUTcBWYG6ErG2qqs3MToAzpEc24jeJiIAbHLqlGuVkQ1lX7SRBJD2n0fQfH95KWOMY3xdJwqUOn6LJD5nn0+YvuoIM9/nb3Ja+joBYAedAPSMoD4DzTNzhOWUrQQCgUDwgPHy5UvdaV8CwapwUZ7CUscBwI0WHUYW8stxjH9zRvS5YTlhhuSxwQHAs/jrsvS7vg9FjgYf7fOMNPXsoVE8Q+NNJb8xbObIr57GAdCDsCiJpg6AGSPGI4PukLzxBpwAz5iON8GxQhzqGvCZQl4WnqRlpqlHjOOsD/cjI9RtEpuIAKByzC31CcG+Ru6godypQmDfT6RQPwkgrYDPQJ/Q0jcJIE9kZ6rXASPaPNlfAfokgPzzEncWx0N5vyFrX5V4q4TZZ3ytywkQgracAIUiR+cEoL7PoFlEiOARQKIABIKtJ9nn70jXVFOucv7P/uVf/gUWiwV8/fXX0lmCleDp06cQRRE8e/Ysfad3++/00cknVAeAKwM9rY67BJOx2rGQnwW7NtYQKfW3qcf3eQtOAG6k5QbD9UZzvxSN9k2sbBcGI3udSJlTx5bXgK5Z17n0dKJBxnSNfxcKrncXDfusYGUi0rHn+B1f6b5Cx0aHtWfE+uI1NFtpB4teXdf8HayoPE3lLphOpMq4CtHXmPXrDPthESiHJwHsg99pFzryy+dW0+c+OMV6FB5OgJD2tjkBfLGNToC5hxNAIBAIBM3J/+ybb75JX79+vXaSrZCus3ekq8fKVT6Dsn/4h394Xy6BYJX48ssv//D3hz/8YfZO/8pIgNzXAUDh+KWmnmuupf3FGdQ/EUB1JqhGc4lLg5E8MrznnxXQLBIg8yCHPNR1sWHSvW2gMH8inyr6oN8esEqcMEM8ZZ+XZQzNI6Ge2JA3bKsB0/kOyk8chGOg6PwFVNtsRqyOr0G/uripCADdqj3Vp+7+fXW7w6yFerWZBPCczXULqJcE8Ajn5ZGm7XRz1Z5BR/csuqsj3DN2nS4XgMkJEOp0MTkBQsc4tDSviBNAsFXYtQiAJ0+ehERMCQTeNtO7sTBRyH8556c/+9nPNkKyFdLVRdJFz4rDf//3fxfyL1grSkfYD37wg9Ixlbo4CncAjJmBOTEQdiJAI3CvVIaAF7KD99clrLsyvOcE01lpA06hWt312eYwV0hu+sj1bghVdvxDuH8UHa2GFuzadWCOuspXyedQL4kk7+MCmkV7HDNSXEd3MiSGlBhOTVBpKts25ABoKyqhzeiGBfurzn8FhIdq635TR06JM5zTLsGdXd7kWLA5HHLLmB4EEO+oZrvrnAChWIcToKmcsZgngodM/tn4TaX3BC1D93w/pJX/TZOuzz77DD7++OMOs70iIf+CTeCbb77xuo4cAF2oQt4nFkNtiEZMgoahyTjUJaWzGUm6B0i85jbrMEPZZy/2Jsq4zRgof/k+/5lC/AdrLJduNbEk3qf4PuRs+WNFx5sg1ujPJNCpsIDKMaeOKVP5NhEB4GrjgaWvQuQNPPreVa8M2kkCGEEVUXXWEindW+O42fPUxTaIt84J4DP/Xq5wDlbJ+01LcsYgkWICgUDQBqKvvvpqKwpSluPjjz+WHhHsDD5Eo6TPjKqZw6glqPtCOc4DHABDg3HX2gTheV2BDpCep4EmEQBuQsdXi0260lb/meBaFQ4xxq+gijyZ1ChLAeajGEOjEiaorx0k4xRmfu0gnJuIAFi01FerksdltpUEkGT2oVq1r5ME0FZvntjPpG+6JICua8FB/jOlnULR9PeARHpV5N9E3tuSs678J4IHAEkCKBAIBIJVOAC4IRYFEFlyHOhWyXIkIV0PEjNdcR19wy5PIGzrQGgEQN7ASTAPLFsO9UPsc7h/Pn0TJ4D63hdlWx0rxGsMy3vnQ8vRlmOjLoqWy1PgOAtZYd5EBIBp/z8hdM/3PrR7qgCvV1tJABc4hqIacngSQBeRdpWF5IRc60JT8t7099AyiaYcHG3C5XARCMQJIBAIBIKNOQDKFc3XDYipCaWB/spg7NF2grMV1GlR01AMWQkeQhU1wZ0ZNuP5AI3wAsyrwDqCdwL+TpIcZec12668D0+i+FpTz1VBd+zi64C2Uo3vNsJsH6KcTecAWLRUprZPFSB5bSUBLEn8W5QRaeQU4JcE0AY1sZ9NTsi1PvNME8Lc9Pc0B4fsqZ9bnlerSFjmI7MQE0QgEAgEAsEmHABTWN0q/ARfKVSramQkmwz4owYGWcGMvBA5BYTtvR4Y6lp4tIfp967fuHDQgPgPDfc6W6OxutCQhLxBXeqS4+KByxm01F+DFvt+m2S1mQSQtnXMG8hx3aNYwbUulE7Jc0/SbZrj00DyrpsXy8+jABkLy9wZNyyPro1cMnMQCCwoV/5l9V8gEAgEq3AArAMhZK4th8QqHRttk5a22rjtuiy2sJ7r6peHKkewHixg9dubNlm3puS1DfI7b6k+BbTv4FyFTIFAIBAIBILWHACufbOlwXcC9vDjWcOyqHt6M/Bf/e6AfRXfVraTGobazGGU9nak/2eOPmh6HccF1EucR+fbN5EhePhoOv+YjnmLcC6iRItE7q7B77hQHWKo9tvvOkmMcP49hOXV+DmOVx+STgn92h7fPNFiLkNEsIuQCACBQCAQrMoBkHoarQcWg5fLKI04n7wCfcWQ5BiBfd8mL1dpQB5ZCEEKVXI7wgs0XMcexNZWV913ETQ7QmxduGZ9MAH7vmqf61JD3/dZm4Ua+JdQJVUbQ7MEh4BkrizPcIedCWVbnoLfPuomW0NoHJZE6hy2e0U7XYHMAZhzYGTYNr45OmKU1VHmOooUGNbUa0o2l+McuM4j5mj+jAz90cW6nTjmjIy93284d1I7Z5rvpqjHj90ZECt6SDpYgEBtp1j0RSAQCAQP1QFgI+5P0ZCjIwIPPIzMC8+Hpi3BXITkb89xv0uLAapzYKgOgtTihHBBbS9yKmRYZlckQIxEjucqCFk5M8koPPuAZ2dPAq6LAvue+nlcwwkQQ+WY6YB/pnITaRs3KMu2EN3Zmu41ZkQq8SS6HdRHIhZHOzo3jsGd+I/mqBOHHpHeUX6BK/bdIX6foZ6HJkaNFb3wmZ9Ncsbg7+jxaR9gY9ZUrhzHdsLaCsD/OFZTO58p7ZygXs7wux48PtDJ",
		"PbrTCUaomz1YrxOp7bmRnoUx063zgGdGhG2hOupKWU0S7AoEAoFAsLUOABNp7DIjqomRGYIFmFf3udGSMNLrMnBvWLlTz3K4wtrV9rrBMpVt9ooRg65i3A8MDpCUXesyUgdgX6FUZWSwHFWRKgZyDMunNtDWjzTAAeBDHHwiOwhnSLLIOVLXAOPkHzboBIjRuNxHgjJhn2dgP+KOdF4FXT9T/geov0/al+Cp6MOyMynbQSfLKLDuRDqnFr0zrYQTsRixvg1xAgyhijpqMj/TEbDXHg6ALLB9qFx7hu8PlDbP8Dch9aB2NpHYHNuVH8+3KSfAAMvS1skgPg7jCPsgcbRhAut5vrcNmq9yRvj3oXLI9zzmIdJT04JCiuNtsK5K7WISwI8++kgsa4FAINgxB0CIMbdqI4GM4o6GPAP7nK41OQDKh75uO8K1QlpMcDkKdPvjyTHByS4d4TZRjFD6rDwy7ClUK2ZdsG8lCJVB5Tlw1EcNKz9vqS95W4c4EHotGOw68h/iBKCV3hSWV3vLNr5F3TvyMMIzjYNlonHkpBB2ZJnqGGniKNGR/4WH3lDZ1PIdb9gBMGdldxEgYOMmVM5IQ5wTRkpPNPdZsNcJkxPSf1SuWUMnQCnnCereLY61qWEsjDTk+gL0R77ythgYyBOvf6Y8Z048xpWtnRPl9zSHlH185dHOCc6JbRF2QGJ62NIzlJzNLmLKHXNzrPuppr8SnOsOAsoQs3nUJ1+QDm/Ys+KsxnzVwTmY6+yU2RFjnKdzh4PE9WzqQ3W6h0CDjz/5WBpBIBAIHogDgAgc3w6QwGrD4c6QPFASuJwZctzgKBwGg08ovM9Z99yR0Dc4Eqg8B8ygiRRD5QUjGHONEUgGS4avaw2BSh0yeozEZfhdpsi4NDgVfD4jI4jkHivXu4w/umYdCRNt5N/HCUAGcazpz4jp4wzsq0yRQpCmqJupok8Th3G5gGYRGHXJv08kwanms1RDwtYJTogPPJwApzXlxEhCpso4KQw6PmNtu2DjNsUyhMytbTkBeF1iy3iKDPPjFOcl03x67CCpJzjfjTVtPnf0mamdOzjujpR27mA5Xe1MYfOnNckpzXeJoktRYB+RjAuotprFiq4dGhwmqlMrhyoKQbclIHTMFliuMbtf3SiUEerJCfjn48k05F91LkVYvucGOd2AeXUkDgAzPvn4E2kEgUAgeCAOgIHyoFwXygf3DSOse+x9xK5ZR7gidyRwA3dfuW7fQWq7iqNgYTBYYkYOJwaSUlgMLS6jazCMdSTH57OUOYBo5S2zXG+SWcrhq3BEonyNbNf1PuSfk5OJ4/fqHm0iXpfMwDQlMeN7SudQbWsZKCTKlQBtssIx2IT8R8pvc6iiZ04t9Woa3+qT5DDECZA0kLPPiAFlxzftqR5ie3MSWL7OmaNogTISz7bI2bh2hd3bZDxBOXcaYnXocE4NUEfHoM/D4iKWE0ayIkaUbc61DNtzwRwghGdQ5UfgpJLaPwa//eFETkmXQxw0CegjyUIcNSTjGqrtWrprbuB+NEBH8wx6C9UWMSLvifKbEKfdhM0hdRxQe1BF/FE9fLbBHUO1Im/atnSAcm4t+sed2JQsUm3bEdPjFNaUD2DXtgFIBIBAIBA8HAfApjBHI6AL1ar/ghkq08CHsCt52ilUK9u+v782GMI+DgXbdedoZMSMDHACTtf4yAgBJ/MT8Nvrm7TU33RawFkL12fMOXEO9vBOXcJGbkxSMrvcQJj20AmQgHkfbay01x0a6vtKmTMHqR0yx8e2kH+A+yuMQ6Z7NiJMjpU6EQIzi1PARlJtToC0gZxEMybm7H+ufwUbX5ws5ez6HElHXLNPkxUQFZ+yFFiflJFsTqR95qA5VM7fiI1lU3/lCqk2kW0axzmrTxFYf9pKVbTQnqvYUneq1DEyzJ3HzJlBc1jn/2fvzaPjOK574QvMYLARQJMESAqkiKFISSS1cGBRtmgtHDj285ZngglM2focY2DG8VGY7xH4zufvnOQcPQBR4vyRkwPA78l0nqNwaOslkYwYYGw9O3FiDOV4kSWKQ8kiqY1sUiTFBSQGINbB9vVtdM3UNKq32TAA7k/qA2KmUV1dXVV9f7+6dS8nZlm1Q8Dgne1L4r5k7dnwdWgGe4F0j3JzY0AwP4e4a/gN5hqvTvxo0T3fVkG/y4oAsNhQVlZGjUAgEAhLUABo516mRrDjBm4HkvZy92ov3HrO+GbRfSUH1/KDOCbAMc5wMjNajglIgshQsuMeuAfM95X26ozEkMCIDlu0XWsSbY7CxMkUBABR+4LAkJJ1RhdvUAbAet+42fk8+W/iyJxIBDAiuvx977Uw9hjhOQfxFchMbZFhYoSPI0gLTf4BElfQ9GOEeQd0mswX6UTIRhuGwVq4CqWpLs0W98j2sIviSPRC8h4fEW6ePqGNmVqtn/Zq8xlLZbhHe2abtO+x3nnatWe1vws7FCNCWtnJZK04KCCWZrDrpdLH3Usy7YnvnLY091evw/eYGazSLoruibWN12Gdrd4vTrxQmMjDv+Odbg+TNfuEr1eT7l6duPnv5eYy/0IZaYstCGBpaWkLZHabGmF5QqYmIBAWVgDYbYPkpmNFOADmQaXYS5kZCkGb5R4xMFxY0KvDmgFcK5hwdpuIAiKjyo5xZCQ2eFNsv44UnkNnCtc9YmIYtnDf6c/r0IkEQRv3Jzq/HsQBwcICEcCM6DZB3P2/x0IE8ELitpQgZH51KF176r2Q6E2QDPkP6PqryGA+mGK/cmQzG4xJNqbNMhyEuLrPGrS7UTBAo5XFoME8xvZyRyAurHoFY8YuEdJ7rfCr1CGIBx7Ef5+EeFA0GeKiH/+9nzsnImgfq351OAnixAfcFLW52XxqZ8yxbQDJpHzNRIo8/XMym1ePcc/rKMSDy/ogvnWs1+b7qBPi2yb8MN9TI2yj3iGD58ePCbtBZM9xz4QJR3YN/hrdfbHghkGuDFavdpP74ftEPcRX+Q8bzBNE/gX4+Us/DwOBQCAQlpwA4OdeqJkCI3Esn7N+D6UE8UjZAXCezs2ItMsQD+DnFRggIg+ANpvXbHdouNabGBuyVr9Gg7/F784bXFPOQr86ZmJk8aSdx0mI723tBWvXXEZQJM04Zuf7wHj1iO2977NBdJnxyIg920McNBByJI6wdS6S8d+mkVDmegtJkH+A+av/ZkKDnqDUpXgPdurKkyyr9IZhE9JqlQngpGCc+SGe6UHfbw4K+qE/yXEqIv+i6Pf6Nu8VzDHYH5ohvve+zsH8IYF5IEArryV9uwbBPC5GWDePyrp5bzfEhWJexPObkGP9fLkpQ/OmE7EtaFKG1ap/LyQKpmxvPYtrIPIwOWpj3NUZPD9ebAk6bBOn8yfLPsHEGSamtcL8FLgRE+LeK5gXOrh3i77NieQSCAQCYVkIAH2ClyMjWmYkSuQObuU6eFhHRno4I5UFxpIhHsDohFYfu8bGbpPPWhz8nZOtDm0O2trHtVHQwOhp1QyWLkH7y5C9XMXtgue628TI0vcLWdc+bF//EQuisEP72au7VzQe94DYu0LinpkdwzsE8SB/Xpif793LkX+nnigLjQD3vLwQj5Lu1LD16giz3r2a39N7UCAAhDJ8n/yztiL/oI2nZNIARnTPXtb+xigNopHg0qj9rRPCaUX+ncIPcYE1JJh7AiZ9ysxrK2QyX4pysNsJAsdIHfMw0c99bRBPhcq3yUHuGVkJAKmCrd7zz1hKw3NiJFu2cQ9B7rn5ufHvNXhOTselXrxxSv5rOQLvBL3affDzPesHEd371CxmTjskBmplf+czmCOyEXhYxWL0AhChoaEhoL2bJcHc2tXd3W17rD35wn7Tsg7te1YGAoFAIKRFAPALDDYAc08A3s2bFwpaLa7D3PfC2kuZucnu5a5drxnqnZxx4xcYLiKSfszCoDSC3gPAl6Hn0sqRStEqPu/m2AHJr6LqBZrWJM5rE3xu5QFglJqR3RcfBbpLZ2Q2c+0DMN/FlA/OxoJ+yToD1cke4LB2Pvtbr64+kk3S1ZZFUcYO+T+sG8vJrmq16toqLJgD6rlx44Xs7uWLcKTUzniVIR54VD/fDVgQ",
		"MRGp6OHmKR4tAgLarLVRk4P760gz+Wd9o91gXmHk0K8TgfrA2t2/3WTO79G9S5wQyHbt+qIxFoL5sVYCSbRzKtDfxw6tzulYRbY7llo4QusD4+wokSTaJVXyn4rQwuwCNt+3a6IA8yJjQkfQYv6VIZ4+1+pZ5so8vliIP+tvvsuXL0MkEoHR0VEoKChQD6/X6y8pKWlWzuvs7u5usSD+sbIGLkdg4FIEbl0fhgKPG4oqimD9PdX+whJPs3Je56F9z7ZQ6xMIBELqAkC7zuBnpNDqxe23IRQYvdi93AuZz+O8VyOIrdqL3oy0i4x+swjHvRYkzowE6YlysobNEYi7tssGbVOnGf/HUnj+fkjcI2kkgNg9z0hwsdPuvPHZwxEinoj1CPpkyKR90CBkAc144zScRF+sFQhMTByQIYsrQmmA3n03FZfWJgvCgOMpbwHv1QvO42m0QDzVpV2C12tw70FuTARN5pkAxPOLBx3eX7rIv1/7+6DFPMjSs0oO2rgTjLcr9QnmACd51hnJb4X4CjD/nUjgcNrO6UTTAswXrH/wgfZE7ehk771+flzI+axWu7ceQd3abZL2IMTjKvgNylks27tyhfyr41sh/dLx48dV8q/H6dOnYcuWLbB9+3YUAaTu7u4mA/KvljU6OCadOHoS3gq9C9GRaMI5JSuLYWdDLdy9+04UAaRD+561FLM++9nPphIvKdNoefHFF2m7CYFAyLgAYOXSrg/iFnIgHMgWBoTMvcyZocZc8joFxKtFq+8JAxLTbkLUk/EAsOPub7dNrNBrwwC2ExjLDHUCI0e0ncDueUZtrscxi77QC3G3e7O0fVbGWISru497NnIKbRYyeA6LCecguQCTIq+JAUguFkjtImg3lpe82aKPWW37YKtQSE4atbHDj22c4w5q/bQXnK++4vknITHgWbLkv08bU1Z1kME4q4YR+bezGpeKiMHvad+jjXcmDkva/aXSzukm4wt1XZZBBPvdbm5ODsHiTmvH+qRXN785vadwmsohaPMekv+XXnoJpqenweVyJWxpwN8RZ8+ehcHBQXjssccCDQ0NJ7u7u0Xv9sNI/n/5vZfh3Mtz6ywujyv2ZXF5kfr7yRd/CyODo/Dg738o8OQL+08e2veslWjjO3XqlP/cuXM51XCPPvoolJeXUzYFAoGQFQHASgWVbBJ6EWnebWH0ydzvTRDPf90Jxm7wLNUdM8R5w6rNQACwIvJG9fQtsWdv1+BzYhi2pbFumzQRiO3zk7Q+cswG2ekzeK6HM0Q+Fgp1OhGizoYo4U3yWpLNz5ItKxfRohH2gG5eiHD90IrMsfnsmDb/9BiQl2Tcpln56Rh3YYi7T9s9fxPEY5FIBuO4Heyl0PTZbE8rMeSoNscfFoz3VNp5KSEMSzeInQzp2WKUrnKWLRQir2ZSwJV/Rv4RKACUlJRAWXkZTE9Nw/j4OExMTEB/fz8oRBw9AVpBJ+4rRN6PZb3183fgwmsXwVUQJ/4V1eWw4f5q8JQUxD6bmpyGi6cuw4bt1fPKEmFoaCjn2m9ycpI6EYFAyLgA0G7zfNnE2Gx3cF1+Bb5XYIwEbRppbQ6N33YH9ZOTuC8yGNIH5sqbjMvlEQOiaxW8abE9v5DF7yLUJknAwxkuK1VkapuBnCaCzeY0ltGExY4I5QgZS0ZIYMIrv2VC4gim7KAfh9J0H8x7isXr8HF1IVdaAiF72IMu/3jgXv/8/Hz1w5UrV0LpilKYmppSBQAe58+fRwFAamho8Hd3d/NzQuPo4BhcOP4+uLlV/3Xb1qqHHigQ3Dh/AwUACcWDQ/ueDdHjIBAIhPkCQDoM3LZFcL9tS/S+CPPJFiHz5JsIVXJtthTbLZ0kPp3t3EtdjkBYEHgx6F9eXp56oAdAYWEhlFeUqx4BPNi2AAwOiEdJSYlfN594b14agNHIGBQUza30r6gshY21G+aVMzszV9bwzRFA0aCkotgPtIWDQCAQEpBPTUAgEHIQuHKLmzIxzkAbNQeBQCAsPiD5x9V/PJD866FPczgyMmJssLrywV3oVo/b7lkX+zc7XG4XTE9Oq8fs9CxMRafoASxthL1e74JXAre0VFVV4T9leiSExQI3NQFhkZBB5jIdXsByePdt0MrpTWLSZ0HJ+LgSLO96xGF9+Ije6ayPDNYZNjIJ3CvP3uws20c4iftiwc68XBsdS7KdCGJ4tXbeo+uLduMk8PBr5ej74lFwvprv5Z57OMW+7Nd+htLQVt4U5zI+pWUYFlcGEsIyFgGQKOlX/50Ag/y5PXNma6V39bzvZ1wz6v5/9Zr5edTwSx9dSp8K7Ny5Uzp58uSCxE3APr1r1y7eZiIQSAAgEFI0lFshnglCT3LbbRK4dJTj18rwC77r0EhBi02Dvg3mopGL9s5jnbrAesW7HuJBMo3qYzedl1l9OmzWR0RO/BzJCSX5/PXlOgG20WGDv2PtxwKMSoK26oDEyPWM4PL1OgqpB65baBjdV6+D/tPKkWMk/RXa86/XvrOTPs2rPS+/dl0sC0N912ifBbS+ZJXGE58lZm5oFPQhWatL0GbbBLSxoQ8AG9bGRTDFuQy0du6yOUaatfp4U6xPLqBPN5+yVIIyEJamAOBK3eEUV/nZFgD2kwfGFCiIkgCwXNDd3S03NDQ01dTUHFYOCbePmHmQpBulpaWqAMDeTUp9SIwlkACQZTQvAUOcICYVIgM/oB1WEb3TUU4AzLMHMIGgD8xTwknaOT4L8tKqEbI6g/5slZqO1ecEmGc1SFd9eJLTAXGPhLD2915O2OjM0hgVPXdGsHwcCWvW6ot1zBPMKZJW7w4D8YcJQ1apAEVtxYilD+IRx+0SQXZtnuRGOEHCDnxav/YZlM0EEDPiflgbH0GYn4WF7xN47ADj1Hs+iGfuMBqLfu16fSb9GsthniNBrT0iXF0atTIOWvRns7bhv8fy9lr06YB2/5KJAFMP5qkS9fVh42mH9rc+m/eVq9BnAiIsNfKfnw+ufFfKZXkU0l9YWjgnABTON19drnyYic6o/87PIwFgmYgAauBXDByJZFwj5NmuQ4ieBGGpCQDeNLyUfZCeoFdG5Xg1I3y3ZowRli75FxEQMCAM6Sin3gb558nyYTAO8tYD9lNJMiJTJyClzQ7qg2TJaFUtHfXRkxxZG4O9unqwlUs7QkKqqNc993aB8BDQzvGCeVpEJhABJ2oc1f7NyBd77jvAXq77Zq2t9O3LtnOELEglu169wb03mjwnPeGWBPdVw92XGXFvg0TxjD3nPRypa9fuhQkFJwWCgqT1LZajPswRfr/Wp4Jau9Rq9cZjk66NvJyIUKcTfPzadYPav/F6J7TyIgbjRu8txNeLFyX6TPp0QDB/GJXFBKcmG/UJQtwr5xzXh30W9SEQFkYEyM+LZQFIyWBVSH9RTAAQeAC4psE1MRW7JmFZCQFEwgkEB8i3IGLnQLzyZRcdmqHlT7GeRuUEONJRn4brEBYWfgeknSfv3jSV4xP0O6foMSAC+r4ZttEWAR3BcXpPkoGAEUhirOjroxdJejVC1SsgPG3ad8CRtEyAv1/mUtwmIEMyzF+RtRJDmrjy2rQ5ZxP3HJtttGkb16dYmssWjSiHdaRSMulf9RwR3KsdQe2zo1pdTlj0dYkj3fx9NWn3FeL6il5sYH2xk7suEwwYca/X7sOrldmr/Y0kEES8OvLPj+FGXV/aazA2DwvIPzuvg+u7Ie0co7HRo6sjXm+l9jd1MF9Q8xnME16Dz8NcWaJxWW9RH9Y2bKuNV9CPO2BxIKIddryRCIvZ0MzLT8sWgILiAihcUage+gCA6uGJH0ACAIFAIDgSALya8diaQrmsjOYU62dWDnN7DEA8BdVBk3L6BIYRM1oHkqhbQBNIfDoydM6GIdOh1Yc37kSf2cGAAQl2+vdSmsqc5Qx/Hn02jLyDNo1GPXludVBOr8nvB3XPl7+HFoHhLvrMKzDiRWPpqI5oWbVHQPeM9G7QRm7RfsGzaBUQYlnQziGLv2MkKgjG7t38NZq0urSZ9B2/jf5ldA6/x7rdRGQJw/yYDVZjbrfBPfGuyx0Wc1krd/1NEHexZwJJCze3NVsIN00cse7l",
		"iDsj2j6DdvZxY7BJMB4kbfz7dSR0lutHAa6N+bZo0eqwkhNZvNxYkQRjo1HrP/pnFTLpR0HdeGCigygOx1GYn6IwrNW9Xjcf+Q36lpcbR2GY7+kRMBhjUhLzZ6tFfRhp7gFj76RACu+DbJJ/NneSCLCEoaYBVMh4OrYAqAJAWaF6iAQAjAtQoJB/PPJoCwCBQCBYCgAdHEE7keRL2E4ZvjSWE9YMQWYwdYHYLZY34JoFBL7ZoaHG3CwZQWZGbg/E959alcdWC3kDVPSZHbC97Cc0g9+p0Snp2kL/WTJl+gV/y4xZyaQe+udXpyMZQY0oHRUYvGblMKMfy9tr8Lu+nD2CvxcRiZCArOzW9T2vCZmpA+P9r/wK3x4BQarVSFxE8LueGJvVJ8IR0oiufcDkbwMcubMDNmYbMzSf7dH1FTPywfpSLdiLHxIwIFwRHXH3WhC7CBi7aPMr6iIRq1Fwnr4/8WKeUcC4lQbkX38/PPhgmbtBnCGikyP+kqBuYYOxcdThcz6ie580csKA/pntMSiDPfN6QfuCTvw4x835YNBu9Ra/O3m/GI159p7jvRHM+qvV+5U/UiXeXnAWLJQFcwxz40EGigOwNA1NEw8ARtRVocCCtBcWe6CorEg9RAIAXgPT/+ExMzVDDU8gEAgWAkCzDYJmBasyAmDu2uqknBMQD9DlhcT4AH4b5PQEGEcINyPKoq0IrZqBWL/Az5IFbDthYvzZvT89cUm2TNY2dv7WZ0Ec68A8sr3foBxGaGo5ot6k+11UjpTCs/DpDGMrhDQC3g7iQGpm7RPU/lb/e6fu2ZrVx8cRuE0W5NmrI9x2yLOevHlN7odPsegUR7U2bHLw90aR5dsFx3mD9us1aB8vR7DqdaTSiCy1c+3gN+ibR0zGgF/XlgET8ckInQKhq013XycN/vawNuYlmB8PQxa0j1VdZINnxv+9F4w9Brwg9oKJGAgSZvXoMhmL+nIki7lBsjF/+AxEIDvz6W6TMeLXHQCpx+lphXhcDTuI6J5nLVDsgiULqxgAapBAl8syTgB6ABSVFaoHW+nnDxQAoqOT6jEzSQIAgUAgWAkA2UAIEvMXp1IO6Ei/BPZXDpJZ7WCu/c0mhDFX4IV4tOxk2tqX5jKN9traRdCErNshd3oyDJC76bI6Ibk8shHB711JGvURjRDbCaiJff+YRkjQbdzIBZ7/PmxCgEIQX/UM6p5jGBKjoBv1lbY0Pd82g0N2UIas1dXP3S8j9r0OCC8fJR8gcU+7vv3yuPapMxAa2Cqw2RYtJqJEwFlwVUYAW9JE6M6ncF7QRCwBre/aQS/Et1cYzWdWIpv+PJ/DOZgvOxUPmpCg77Wk+Iz8XH9Mdq6Xub5C2wGWmqGpEXyhOJCXp37HDlMBoNANnhKPeogwOaKQ/1tR9ZidmqWGJxAIhBwQABhhD6WxHD7lmM/EgE4VTr0FcgH+DIgTmSgzk9dkxMnvwMBOB5IhPUjGzLwlZBNC0Sb4/VwK9+kD+/E78F7Zfudmg2vy35s9y6Pa/fsg7rXB7xPu0Ma9mbChX223QgDiq/TJjnHJBpHm0elQnJFh/l71kMl44aP7i+43wAkBPpNrsjgDsuC7HQZ/x+ZmUcpHr64s2YQws3JkE4LMf1eRxHPbbfO8k1zb2RlXqb6D5AzPTy06kSQdq//pfEcchngwTN5jYqG97AhJgLn2G63uI+l3u91QUFBgKQC4i9xQqJD/QgMBYOjyLZgcnVKPmUkSAAgEAsFKAEAjj7m5JrtiY1UGixKeznJaNSORrbJFbBhPyRhXolXkXAbe49401zmVMnttli+ClyNoXpO/DxuUo4/ZgDgBxkEOwybkyS74lcWQDYHjBIhzhfOB+EIGZO4cZ4DrfwfBvYTAPMUc2way24DshwyekRkZ9tpsN0aM+7R7YSTQy5EBq9VKllbO7taTVoi7iEeSrHuzQVuzNtMHy2s3KateICTp9+W3G4wX9vzYmIsIxoLeS8Ms6Cje+x4BoTsKiQEXQVe3FoOyfLqxIWvHHoO+Vgdib45GXV+UkySH+tSyRnPQDq0Ndpu0lf6+zN6jHWC+ih9OgxBwzGKubQfjeA9OIMq+czjFMlndmCeAXgwgLDIBAMl9YWHhfAM0Px88hR7weDzq91YxAEpXl4JUXaEeeowPTkDk/BBMjU6rh8uVT41PIBAIFgIAGlltEI9GnQz5SUcZTsrxagYCM2AO2iSa+mBndiDaR84LFqEceZ6MbNRC8q7kTWksU4b5gfbMzg0LDPQajiif04xn/dufJ7UyGK98skCJot/15XSl8Bx6BX1ajxqNfJkZtnw5eldmJmpIBr/zz6/XhiDDPBCaufHVZvF3vZCcYGj2d4z04b3MascJ7ruwjT7M6n8YxGkZ+Xv2GrQvI2rnLAiND+IB+4JgHNwvxM0XVgIMI4FhXR8KaZ9heQPa82FB41h/9glEB+DmSEkwjwYM7qtV+67RoB+IslucA3HMkMMGffEIiNNS1mv32GNQ314d2fUKymjj6tgnmA8kSAxAeMyE5PZZCEp2xhjf7wI25sGjBv1bL+jZqY+oT6Yi+DPshnggVHbIkJoXAB8YkLYDLGKUlpbC7OysoTBQVFykEv/CokL131NTU1BVVcXGQQKKSgshOhoVljU5MgUXfn4JZsdnY8e08l95VZmwLAKBQCABQGyA1EJqq8fpKMOqHBniebjZ6mm7zXLtBDszM0z26ginWST3bCEIxnnPk22TZMtkBMQqzZ0e7QICFhAYz80Wf9duQrBaTX7Xr9QGdYSbEVKzz0SrsyJDOwDmq5Z6EhfStaXewDYyuI0iukcEba3fx9xqUh+A+bnb7cLs75jYtpL7rMkm+RfBaA94G0e2IwZzjMQ9qx6Y7w3QDPGtAxGL+aeFEwIkmJ/W0Q+JXi4tBu1WB/EtFSxAJxMpvBBfORe1FbZjnu5e9f1KsnFfsvaZiMhKup+M/PtBLLy2aXXt0ZE8H8x3+5Y4QUDvxi4LBLBeSAziqBda9PceNJjDO7V2M0p1GRK0d5fJO2SlNjdGLObAXkG5Qd2919msj2icpcNDjE+Fyh+hFMsNg7PYE4Tcw9Hq6mqV1M/MzCQQf/QIWLFiBRQXF0NRUZH6E4WCyspKI2Hr6MpqCW5dvwUjkVGYHJ9Uj4nhKNx4awDe+ZdzMHEjCjMK8cdjcmISVt+xyqgsAoFAWPZwW7zYj0BqrtDpKMOqHGZMt5gQ8BDMD0jFVru7wLn7aK9WZoC7ZkgjywGHQkDE5mdmbZNKbIUWgcGYSpksvVhE8Llk0Rd6IZ7j24lwEcpQOS2QmDfdjtHaZiBWtYAz11jR3uu94Gw1LAjG6eKawHx13E59+OsEYP7qpN3v9eMZxyPvFo5Ed4fNuSTMkUfQ7hGfK1vdrdDK93JjzShYXQvEV5brtUOG+SucrAzZol5hjhDXaz9DMD+9opFXUYSrFwa9a4TE/fC92nwm2xjzbN70ayIC2z7ls3lf2M9rtHvYw82/dVoZQe2eOrR7NeqL7H7ZNp92iAfDxPKPciJMB0d6IwZjo4/7PizoL14DEYEvR58J5Rg3rxwWPJMmg+fdDvO9JEIQD66ob++QoI2aIDE+BbbDIPd9jc36LDbw3jCExYlehei3bt26VRq6NaR6A/BAws+8A0ZGRuBG/w14+OGH1XHQ3d2tn3OCrgJX6+qa1dKZo+9A0XSx+qEo0v+MewYmK6KwfvtmtaxD+56V6VEQCASCfQEA0kDc01WGWTksh7kVaQ7ZMMydQLSCYndVpU4zvGXu2qLP7BLXVNCZ5jKDDj8XkQGwSd6DYLyHNR3lMAJ02IZIZFYX9n0ErANKsqjrIZP69IC1i207mOfl7uXuzZtkffi2PgLGe5+tvucxIPgM68c8P6xWF49oz6GNI19+g/aSwdobgUXSZ+7zerIeshBHwITIg65eTCjqtTluUxmnWOeTEPcm0Gdo6QVzUZWVcV5rm3OQKCQyoYoR0qDF3L5J69cdWp3CGvFu1D7zauW3GDwvtmLM4j90QeIKug8SU+jVmZTDxhgbp+z6jQb9w6iN2jTBifdYauYIrp787zWpTx/3nFot+utSIDyS",
		"YD51fF9PvrDfx/VxO8BrdCmkMQyElIAkvqGhoX379u0dr776Krz37nvg3eRNEAKi0ShcvnQZ+vv74d577wVJkoQClvI8IsqzbN+wvboDtwEMvD0IhSNF4JrlTFj3LEwWRWG6bAo2+WqgpKJ4qYhhBAKBkHUBYLFgseUODglITAjIVY0nFkc5w1tkFLfbIErpKIcRYL9GdPycMSlrz+yIzWfHe440CgjAUTDeR6438uu1MvT1sbsKzK7JvFb0wd7s1oc/P5XvgSNmYEEW7XzfptX9oNbOfq6Nwty92UGbdvh15YSSJFss0Kkf4m77IUifWGoXTETwQ9xrggmisoO26dT60G5I9EhgJNxO/2H92seNjd3cuDlqs4/VQjwnvYgoB8E6BgxfTgDingx8XXvBXiyZFq3urVzfadYRznabAolR+seI9vfp2NOfK5DTJGS0jg6O1V955yqMj0yYnlgqlUCVtxKJY71CNutIBEiLCNDZ0NCwY+fOnYHLly/D6dOnIRKJqFH/cVsAHjU1NeD3+6GkpESdAwSr/0wE6FSeS80dO73NA9URuHTqMgwPDs9tztE24VXWrIb126sxS4Balt3V/+3bt8NDDz2UU21XXl5OHYhAIJAAQFh26NUORkz8HOGSkyjHyx1yEuWkS6CJQOqrt/x95Up90oVQGsuSIfUo55noA6xuwRxq81CO9KFkPbL4dm2C+dt3WLmRFMphbvuhJNuXzT9sLos4uNeIrj5eSNx+RhBDunlpAPrP35gjiiYYvjEMV9+9BgrBlBQi2UciQNpEgKaGhgaMB9ChHNhvYXR0VI0DgIcGnAvbjcg/JwK0KM/l2MpqqUM51LImRqPgLnCBq8CVUJYD1/8WhWznappn6n8EAoEEAMKyRDhNRq5Twk8gEBYvIpAewSZd5fBzUCgN9SE4QEFRAXiKCizPwxXps8fV1wSJAOkVAVTBuqGhQRX0S0pKEt7xyve2PVeU56GWpW3vkApLPAll4XYBJ3V78cUX6fkSCAQSAAiEHIM+fZfRHuDFBH7/r51VyT6b5abSNn1pal/mwt2SxLNFGO2n74D5wQ9ZXbE9MZZBu8O6Y5m4Dz5Iwyxt8IG9WA+E5FAP8SCLsoN+3uxAYLCK+bHoUFjsgWKp2Na5xeXFcO618yQCZEYISFs70jMhEAiEzAgA+iBFTtwn9fBC4h7sZMrSlxGix7cs4Bf0y2wDyeUxE6Lo04zsvTb7NRrjbH+yVbA+URuYjdlU2zmVMhgR99kk1n6b5J+1kz4DAh/p368ddZwoIOnKQ/LUyz3TADcf2TUmAzA/GNxSEKXSBRZzoWmRt0mfwbizM14zBZ7IHwT7qTF9Dsewf6m9X91FblixstT2+SgCyCcuoFu5tLJawvllEw1tAoFAICxlAcAL8dRNegRBnOfczMBvFRhSToIWMXIlKgODTHU6FBN4YUMGcgsnWJP/AMSDgbUJ+ieL0M2nIBP1u2YQ79v3aePNiljgmDkv+Lw1R9qKX6XvcEisrfZDs+9FZKZF9wz2atfXR7Hv0Yjpbo78Bx0S1aDu71MVTRYzWL/dwbUBi9lxQmt/s7gAAbDnEm/3vIVGm82xyN5/duNTsJR4+j53AqwzLGTquXeAPWEyJzwKPMUeKF1lXwDAM4euDcHA5QiwveYEMRoaGti7bTe1htrfj2hbHubhyRf2t1E7xdClbecgEAg5IAAwMiNrL+1enRHWqhl8dlYeAhDPc82n7mJ5vpkBUWdC4Pky+Pp4te9wFWSPRRlmRhSAeWopO4YQM3ztejV0gP0VGRb4KZLBcgjW5J8n2jUQTy3Ek3/+d31/ZMTUZ2AIs9ReVn3ZKNtALggAAQFBOWxzbIJOQAlbPIuIjnTrU6X1WTxTnszncpoou1s/jmSZBNolgB2asSuae3zcs6g1mX/rufPycny+sGvYM8Ik2eh//Nxh1J93QHqDXdqpj+TgfP9CCwDuQjeUlBfbPv/sqzJMT05DzY7b8ddOIJjOU5OTk77z58+rEf4xwN9yREVFBVRVVUF1dXV9Q0NDU3d3d1BH/k8ofcqHASlHIqOWWSmWKjDbBh6VNav9Spt0YmBHGkIEwsIKAF7txW6U3iiofdenHZtMDHs/xPfktgnIqL6sWgMj87CBkS5DPM1Xj0kZ/L2dMDBa/BBfNbRrpDABwytoI6vUUM0On1GXQb3SVY7eqE+VZKSrnFxFgGtPu4Zwn02xxmejL9sVLrJNbCVtvLdyY+G89rnZeGji6mwkAvDkn40xPTlmeeDtkuZQkm3E10UGcXpJUdtELOYn2WBuYu1oBBRBj2XxOddzz8ru+ScF7wGZaz8joUji5pKwg+diBr2wvdBzyUkTgumzOcfYFROyTf5zCzblIyT/o4OjsG333bgFIEgExRgK0W1G8v/SSy+p5H854/r16/Duu+/Cli1bYMeOHYeVtgmxrAYK0cWx7jt97C2lb40t63Ya7h9Wf6IIUrPj9malbbocZGwgEAhpQj7371bNAGMvuxOcQRXQfgfOUOuwMMZ6wdylma1K+wwMtw6Bkd6nI1OyRRmgIxdmhk2PTcOmTTvXa2DQLaSBFNRIWDLg91GLjsM2yU66yskFGLnXsvEgCUionsi0cf2114DI8K7yVn1ZhHZI3JoTgMSVbiPyYSVK2CF6rJxO3Xg/ov0um5SzV2vfIDfOJV3/4LfssPNYznjZgCzagT+JdtYLEZvAWsw6bKOdT5icw9rR6GjR5smONM07bSblMK8OWetve7XnwfLYhwUiS63BeyACiZ40Ii+WVq4vWJFbK+GVPTMr8o/tOAvG3g2t2vf1aZpjOkzKanXwTANprJNZXX2wCIGr+bjianWcfUUh/5EE8t8EBDPsYSv/hDmgCKB5QfDjsRFX/pc7+eeBKTcxhWMS72ECgZAG8B4A9ZwR1QPxFXh+v2uHZoh1acaJ6OXIchTvtXH9sGaUNeoMaS/EtwfojXaA+e6/ojL4+vht1EXS7rPTgjS06gzcOkjc++nj2inbYC7iybiEewXGckBwjuywHKNz9OXYXbntMDD02TYOq3J8FkY1v12FJx4BG31ZtIrJAsbJYLwNgxHac1rdDoIzL4k2A0IgIk78Vpg6G6TCr43lcAbK6dX1N9HnrG2adfcZ0bUlln9UO4Brc71Q4rSv8jim3QsvWDSZ9CcmGByxMfeYbX+wIrWMLKZj3tmt9VnRM2fvCLO+yQTaFht9OKTNt83acZQbez6Iezl12mgXttfcaPzLYM9NvoV7FxihCdLrRcBEFdEYcwIfZM67oW2xGuoFHjdcU8jGzYsDpudNRadAWldB5N8hotEoNYIOIyMjUFJSkjB+VZf/PID8/HxqIAUz0zMwobSJLo0jgUDIsgDg14yNEGco+3WGUJgzoEIQd4GXBSSZD+hltGrAXMGPwfyVCx93HRE5ZCSQkb6jmmghQj1nAB4xMXr92k8zAaDRZrsGwN6KVC7jSJYNPr/N83wmJMpJOU5gJQIYkX8vRzKPWPQHtjWmmRMpUk0PqBcBmKjnMxFT9J9h/fUB3dJVjhGZFbVNm8W99togP20p9oMgiIPRRUzIv1H7pCICYB/fo7W/SNCyS1xYSrnduvFlFGCuV3Affl17HIX52TDM+jJ717A+VQuJHmYy2PdqCkHiNhQedjN0WI33TATdYx5ouRpp3g+5E2jUKY6t3bLGL1VLKtkwA+5LVoi/Os6J/BMyAZfbBe65PrbsER2fpEYgEHJAAADO2GKEpkv30ucJTJgz6mWBMRPWGZQiUnaMu6YkIE4RE3Lo05E+O4adbEIA2jjBww5JRQPwPHfvvAHMewKELMiE2d5euwYXX47MGdVOywHBvbUnWYbR/bUu4rHSZSEAiPqgV0dOLI1ViK96+mz8jR2xIwCJniE+CzHFZ9Ife7V+ka5yFgOQiPIpDe08Ry8kipp23aZx/mk0EQD0wosd0Ud0DexjB23Md8wDrEkwz/o5YYNvk05BH/WZiD5sK8AJiGegOcn1badCahsnjgBXhlPPCpEI0A6Zi1/izeExsCjd/hEKkW978oX9vYUlHsnmSqOc4f3IkWS+o1XjpYF8Vz4UFBVQQwB6",
		"3ExTIxAIOSAAyNyLPgzxiP96Q5itUvp1QoCeDOmFA1GQqhB3TVlQhqQzvHgCqSfgXpOXZ4S7Tp+F8WX14vdy9xTS3UvIIck9YkEmUimnLQXSzbZw9EJq6Wp8sHj2+tu5l74USBeAPXdepy6/7Tb6ThPXP/ZC4nYVXqQx+4wF2JPTXE4uoh7ingT8Kr6TlIZ4f3xWAr4tzJ5XEIzd1O0GhGP30AVil3K7ASn5svg5Rp9NJaK103ndPCRpRBz/3iqoZRjiK/cBbs6249Uhwl6Ix+gIQfJR3HkRIAipe5CYIZcDzWH7NS5WIUAh9OEFvPwxzl6K8P15ZmbG8Ds2LiorK/0YXb6goAAgd4JXJiAvL089CNZwufPB7XFTQ6AYkk99hkDIFQFA1ow1fFnu4AwzNExYgDz2eaN2fsTAmOONpqBFHRoFBDZsYHi1GpDeRhMy3QvxAFl+Gy9rK0PVx4khrH0CYH97gF5QSRV8OXb3wVuRXbDZXnbKSSeZBRMyJVuUwz/DiMX3yRAvkQjAl7WHM+B6dcY1Ay+4hGy0WZtFm4ncldu0snt040g0tlq1+rUYXDsd5fA4bCCkBLR+buYeLxqD+pVf/bhg+8Z59GjX52OfBMH5CjKfmtCO2Be0EJDYHBzW+jqukmNKSi8kbjWJmLSTU/If1uoU5sQAfUBHfptYqwGJlm32ZbZyz7YMJEuKZe1vO8BeLBrWNn6Yn7mmSXsvBG2enwyCkFup5kTzYx3EvTQINnH8+XDbA4/7etnYvX72Rqxtv9L0lbZv/NU32Hfyt575VsI4OX36dMu2bduOauQ/ovwe1s1tqQT9lNN1j0j+yUNhfpsISa8rX01JScDGWPICQNjr9fqVcUvPmpA14PtCkiSwwy/5mQiN1IMQTwM4qBklzKBs1D5nUcqbTF4sQYi7+kYsSJNPYOhFDMpoF7y86kEcMJCvDws0ZWXsWokVRyG+75aHV0eWIzYIXLpWU3w6YxwgPfvgO7Lcb63ILBiIP3bLSbZtReSfrQYHLEQA1g/82ndd3N+KhIaAQCCwS170hNdsrzLWaZMNA9IqZVqq5XRwY59fbecJl5cTBvg98j6dyBLUkXYQ1Es/RusshAiwQcztiABWsBJH6rn6hkz6gKQj7DyatbZkbuyyoP+xKP9e7Xnpg1bK2mFn7mKu/U76chN3H+0pkpSg1lbpEFmDGZz3wpD5gLFHHLwTIgbPjA+yuDjTAC6cCGAoHv7Zn/6ZqbCokAfheP/5Sz8P58r9kQDggPNiDAASALSOs+TvsKukpCSwa9cu6dVXX4XJSYp5QMgslP4GSn9DESBix25x64jTHs7IbhMQHkaIrMhyu2a0srIiBuT/sGb8il5yaBCf05XRJjDoD3PGnll9zLIBMNdkO4Y6v3eWrZLXCOq+2KAXSXwGpNdpOZBkObmAHrBO9ScSAXj363au3/Vp/Swk6Md8EMsuh/X06wivnVznERvkyA55Y+Xog3122CCBzVydAxzZCupIZxPEV577wPnqbrIIpYGc2enrVvOF12Qe5a/TbnIOiiO1JqQ6zLX3ERALaazvd4A4HkZI+/tjYC3+mgkmEtjzgLFCMgJCK2QvVolsUyBKl4Bx2EZ99lr0kSYwDrhLWI48jgQAYZuI4HLlg4diAMy1xRLvM93d3XJDQ0NddXV13+c+9zkJU0NidggCIRPgVv7V97jS/xx5AADEXVZPaEbDUc2IY/s5A5phZmV4M8OmRyPxrCxmzDZqpMVs5StiUgZLleYHeyt0rKyA9nf86uFRiHs6gM1y2CqIaG94J2R2xcgMqWwraNEMd5/B87Rr0KernFyAfsVLT/5FgcL0K7AhiKdUZAQW2+AkR8z8uv6TKvlZiL2iXdq8wQtInTZIWEBHVJpMCAzbyiMiMrwHgQzGrsoRbg6xirrvh/g2pIVEp8WYP2lDRGixSYitAuYxUecoxMXXZAXPNgdkm71T5DSUsxcWXoRkK+rZmguD2r2LRE3R3GY2tzTZEBNEY45AAsCyRj7FAIj3m2UQA0AhYTivrmxoaPDj6iweBEKG+5xt/uAWvKhrIb6ftkdHZJykQArrymrmrhECc3dWfRnNujKYIWJnpVNvBKVqzGOdNml1YXtWZYhnTggt4LNPdVtBskG3MlXOQoPfxy0bGMi8CGA0PpgrNeu/9TA/9SXCaj9xuuJGZAIyJK4Ohh0SQxnMhbwgR/TNyH/QhKDwbv99nAjAr4zrY0h4F7hdrZ65D+x5jMgO+rzdMR5Occ5xEmTUC3HBNx3lhAXCh5Rkv+fHuddBO2d7LLP3rj6TRBCceboEtbK8Dq67IDhw4ADeZ6uDZ4vPs+uZZ55ZLF5qJADkaJuI4KItAMtKAEiGlBEI2YI7g0SZGdydkFqAI+b635ZD7ZZKnerA/n5M2cR4Slc5BHsigGxisKPxbBWbAAkGrpo2auRf0j0bO3uecz0Kd6821pGMO3XP92rEpMnk3o3iUhyD+Ep9E/dM9EY/T/R5YYd/rrk0z7TbOOfYAo5tGVLbp++EMJsRyXSUE86B9kjHe8nufNajjan2JN/PC32vdtE6PDxcf+nSJRifGDc9cUXpCli7di2sWLGi/sCBA3UkAtgnu3kU0d1eW7nyKA0g128IBELuCQCEzCGUJoM9XeXkOtoFhudCiADJkhPRM2tKsQ3MjPJU2znV9mVCh5zkfXkN/tYP81e62XlBEItcEZP2sSPsLDTalvjYTheJXCxk1CnSJZCIhII6WB6Q+m/0w9VrVy1PHBwchEuXL8Fdd94lrVu3ro9EAPtEjjwA7JFb1QOAtgDMtRGJRgQCCQAEwjImQbnSBum8RigD1+xM0zVBJwIQCLkKGZamsJHTePudt1XhgEQAEgDSDUoDSAIAgUACAIFAIBAIhJyGw330xxTC3Cb64skX9jsq59C+Z9tIBCABYLG2ifiLuUwABIBZB+c+/fTTXm3u8FLLOYKaHeipp56iQKwEEgAIBAKBQCDYhq199BUVFeCt8foVwtxrQJhbRwfH6q+8cxXGRyYMyymvKoMN26v9T76wP3Ro37OhhRQB3G63VFlZifESNqWjTOWeAjAXPFhKsgg12LDSLrKdkxsaGtJyPUxpRgIAYSGgkH8121YkEpFOnDgBV65cgbGxsQWrz6ZNm6C2tlZNuXbX3Xepkf2np6dhZmZGPXIBOCaVuQsuXbzkv3HjBrZfnUHb+iF7aW8J2QGKPSj6WIrWJAAQCAQCgUAwgq199LiHvnJ1pRpED8Tba6Sblwag//wN03KG+4dh1fqVUFJRjMZpaCFvXDGeobKy0psG4o9GuJp9YeByBEYiozD0wRBMjEbVVeF8dIfGVWP8txZUD1dI8XM05ktXl4KrwAVV3kp/YYmnWSmv89C+Z1tMiH/sepcvXwaFPAHmIcfDDlDMwbzSXq8X05c1K+V1dnd3t5AAYJ+AEdKGDoX0S3//938P4+PjC14ZWZahr68PmpqaoLCwEO69716YnZ1VyT/+zAXgeEQBAAWK37z8Gz96UCiEUBaQ/77Tp0+roko2sHv3bnjnnXfgF7/4Rdbb5Atf+AK8//77Wb82XveXv/wlXLhwISvXKy4uhvr6enzmtfpnTgIAgUAgEAiEtGNqasqaHCmkNt/EDXp6ahqmolNprVcyhvmKFStg8+bN+M9Ushgx8t83OjgmhX/4Onxw5iqMDYypOeGR1OcXaD8xR7zy06Udcznj534OD4yoZV0+/QGs3bIGPSRQBJAO7Xu2yYD8qyumv/rVr1TS5HK5VFKAP9Wo/ZrIoP6nkVVGYPDn0NCQuqqJ5GDLli2wfft2FAGk7u7uJiK8hCzDj4Q7F8g/jx//+MeqNwCKhDhuJicn1TGTC8BxjkQQvROKiopgZGTEC/PjyTSeO3cO/vEf/zFr9dq5cyfcunVLFVGyDXw2C3FtvO7Vq1ezet1169ZJdXV1AbCIs0UCAIFAIBAIhKwAo6B7TFKhjQ9PpPV6k9FJNIAd/U1FeQXsuH8HrqIFn3nmmZYUq3AYyf8vv/cyXHjtokrqVYLvylfTwuFPPAoK3OBi3xVwYoDyWUFxvL36wzdVD4Ltu+8OPPnC/pOH",
		"9j2rFygOI/l/6aWXVOMTVwLxQAGArdarIkxefkwMYAIAO9i5CDSaUUh47LHHAg0NDSe7u7s7qRengFlqAqdYSJd/I7BVc/R8wrESjUZtCaBZmWOV8Y5jnwl6BvAuBBEn5NC7mJqAQCAQCARCVowOhdR6SjyG30fHomm9HhrmSGLtYuXKlfDhD3+Ykf+mVK6t7fn3nTh6Es69fB4KCueIOCP9mBauYm25usrPewAw7wCX8jNPOYrKCuP3c30axi9OwNV3r6E3wEHgPBQUgo7bL3zHjx9XyYjINd/j8cyRe/X/uZ+zM7OA/+XN5s1bzS+vKIfIQAROnTqFngCtkKJHxHJGdDQKQzduUUMomJmcXhL3gSQbDyTcueIBgGOYxSUgEEgAIBAIBAKBsKBAYltYWmj4PXN3TyeGbw3bOs/r9cKjjz6K+99TJv8aduOe//d+eW7O5V5zvZfWV8DtO9bDijUrHBc47R4H16gLMJji2i1rvE++sN/PBUvcw/b880Qe3YCllZJK/vn9yuzn1OQUTE5NwlTeFMxOzl+irvHWwKk3VQFAamho8Hd3d4eoJzvHxPAEYH8goGfO1JK4D0aycykIID++CQQSAAgEAoFAICys0YFbAEw8ANKcJu3YPffc49+4caO6r90MlZWValAvBeki/6qmMHT9FoxGxubyvyvk/+66O2GDQv6Txa3hUXDNumFyYkoNIlhY4sE9/4yQe5H880CPhsqqyqQJAdtHzIIIKr/z1yM4AIpbo0Nj1BAwF+tjKYDFF2GeAGb44IMP1LgaiNtuuw22bduW8D3uyRcBYw3g34riIGA5OD71dcqloISERSAAtP3rf/cC5dpcTpCVo6vtk38+L2JzQ0MD9YXlBzV9SHd3tzB9yIEDB9qUH7tt9KkWxYA2XOY4+FzAdjldXwoalvPA475mmEtxZVnO8efDhuUoL2Hb5Sgvb1vLNxgwSxs/PupWhCyN3a7FsDKLHgBFK4w9AHCFPF1Q5qE2TEtYVlYmKYetd6LyN3I673c8Mme044p89bZ1cOcjm5MnkBdHY6772IYTIxMoABim+ENBY0XZiqSvV15envA7xlIoKSlJuN6aNWvUrAGEOEpLS+d9VuWtVFNcErh2kkqWhADADiOBDYn7P/zvf5gXCA5TCT7xfz2BQdvU35/9u2eFf//nT/85vPijF4WB5L6y/yuq5xIPRv5JACDYEgAU8q9Gjp2KTknjg6MQHY/C7DS5jyxVFJYWQVFZMbiLCuqVZ1/HiwAa+T8xOjoq4YSDQU4wwilh6QJXv6qqqvCoV57/XoVI9ArIf+vrr78OmA98YmJ+oK7169fD/fffj0Yn9p86E/LfeuInp+DyGXE+8PWKkVz7qe1o2BqWo5B/tRwrqqC9/nBuqzUg/2o5N2/eVFe3RC9wXAHDVTSXy2VYjoD8901NTfkwUBCWmyt7AwlLD0hskagpB47dJmXsBnNdACgsMRYAMIJ1OqEQ+nAu3DcKADs/X6u8d4uS+vuJyARE3hqaE0im0ci3Nu5LV5Qmbxy63bBq9Sqr01qKiook/QokQQXP1lpQqCk08Xyhdlq8AgBz/zci3Dz59/l86op9OBxWt+r8/bN/Dy3/T0vCKj4KAvzvfLn4ORMMVFu+sHDedckDgOBIAFDQMTU+KfVfuKb0sFnIK5wLDkNYmkCBZ/jGEEjrV0tFZcU9ykeb+L7AoggT8V8euH79uuqatmvXLqiuru5QPurVc/dXXnkF8DAC7j1FcQBzkB44cMBnYHgf/PUPwvCbnpOG5Vw6cxXOHr8AT/zl5/wHnwv4ur4UFJZT4HGrZMIMaCRHx6K+Bx73+Y4/HxaW09/fD3gYAQk8BhHbtGmTb9u2bT6lnawIRcf4+LjvtROvLRk3R0LugvXdO++8Ew3DjoaGht7u7u6c3WiMY9ZTakyEMDL+UgLu90es2rgSVq6XkipjtH8MLv36CsxOz6pCwmz+LIzfGmcrygnzEe7zZ0KKKz85MQXJP3oOsDgCLLo5isT89Yy8xQiJOLTvWWqnJQp+9V+0gICLAIz8f/JTn4SHHnpI/TfG1Xj+n55XvQNee+212OfsPH5Vnyfza9euhcZAo87OmZn3O3kAEJwIAP6h64MAyvskr4SY/1JHPgo8hQDD14fQE8CLHiCcF0D9u+++S+R/GeLkyZMoAHgFgZ4kJPhW+Z5xnxo738gexpV/q3JuvB+xLAdX0jBFlhW0qOKG5SDBtwLn8WDHgq8/f/48jI6MUociZA1nzpxR8//CnMdLKJ1lo0FpJ8XVihWqu7lsWtb0jOk+/9HBMeYavBSipR2VqiV/WdUK8HCp/NA1yUwcnFGIPrbT6M0xGLk6AkOXhhOC882UT0FlzWr2K08ujyrztx/ncf0cy7sqiw7mLqWmDSxwJ/z9xYsX8b0guh6BkB2y4nZb2g3ZBLOP9UE19WB7/hHoIcnOueuuu9StM+hhe+b0GTXzSGyAnQjH4gHgNoEdO3bEvsPz+/r6Yr/v3r1bOF9TEECCEwFgzuW/kBpl2UB51pP9k0JiY4cUEZYezJ47upoVFxen3u3SVA4GEvPYcKmMfDBo+j2ulKFxkUZIAwMDwm0SBEKmkMH+JleurgQrUXjd2nVsHBmJDzLugz5z7C11P3RJxfw54OyrsrqqrXn2hJbAY+ktLPF0fOSJnfBW3zuxD5H8Y2BAI2C6uPGhCZgcnoTocGKbz7hnYLJoAu7cfgf+Gjy071lecOktKSnpwOBib7/9NszMzsRICj47frVS/beW/i+WwmwW5pEszMF+o/8GfPSjH1WfSXd3t0yjjZBtoM1QUFCQM/XBbYNsbJm53POf6d31kdwjodefhwIeQ01NjSocxOyZSAReOvZS7PfHHntMeE07WwDQ9slmm7K5JdtiDhNCsn2/TDTH+83mde1uo3OLHlAuqWyETINclAn2X8CpBJSKlVNSkpZyMJVYcVnqe08zMTmjsU0CAGGJoB3jC3zkwx+Rjr10DCaj80UANGQ1IzVoEkSvXSHD9Xd+dIv0zi/fBeVnggiA5H80Mgrbdt/NiO2iX2lGcv7kC/vbt+y6o3Vqchre+Lc31ZV7l8etEPxxY8MRI/wPR2F6bFo9ZqOKETuhGPP5s5AnzcJG3waMkaIGbeX/Dsl5Q0ND+/bt21tRzEWvLZzbtOwGjoHpE1HMvPfee/EZ4/WaaDgQFgIYi6ewKHdWKPUCgJ0VdxyT/N5+lrFD/7f33X9fLLAmzq08mcfP8Xs9uU0gvLP2PABwu5DN4KhpJabZFnNQxFyI+2WZZ/B+s3ldtg3MsQCQn5dPAsCyov8kABDsTyrpCPaUrnIwoFJReerl5Ofnpz3wGO2/IywVIKE/cOBAnWJ49j36yKPST3/6U4hGo7HvV61aBY8++igadKbp8zQyXKeQ/j4mAtx+3wbVi+eDt6+oOdKR/LsKXEj+lwzRVO6lTbnvmq2P3RnoP38DrrxzFUYGRmFmagbyDbZC4F7/6clpze1/blHGXeyCqjsrYf32akb+63Sr/0wEaGtoaKjZuXNnAAUAdEG+dPFSTOgUBQzj50Jm/6GIiW7/dXV1SL7U69HqP2HBkAc5yU30QQD14wuzZDBgEGVlXKr/vnDhQmz1/8677kwUAO67DzB1qYjkowDwyCOPmAoA6NljxwMAbbF0LMY4FQCyLeawIMzZvl/MmsLuN5vXTVoAwPQyKAIQCAQCDwxWMzI8kjPlIHEoSoMHAL4cKN4FgWAqAoRRBFi5cmXfxz/+celHP/qRKgKsXr0alN/R4DAl/xwZDvMiwJmfv60QUxfku/OXJPnn7rtJue+jlTWrO5TDi59NjEbVNH52gDERuICnQeVoF5F/TgRoamhowHgAHRjTBT/D1UdmkFoBVx25FTr1ekbkX+kX9cqPgzRKVKheGUaZJ5Rn0gbWKXCXC7r02YbMgDExcjGbjlUMgC1btqgiwLVr1+Dff/rvqkcN4rdv/Fb9id456GHDk3WRkMB+t7O44CQIYDZFldi1FlDMWW7360wAULcAkABAIBASgW5Uw8PDqZejGKLpKAfTYZkFE7ML3KdlJ8AZgUAiwIG6VatW9X3mM5+R",
		"cDXr4Ycftk3+RSLA1kfvknBFvGbH7UuW/HP3jWSnV7l3DNKopoRLIi1cWCnHVnBEjVz1KqRTvR6uQuHh9HpmGSU08t+DAcvwYC6vyxGYSnfr1q34E7PgbFLGRERH/k8ohMyHwhkS2eUaoE3NTqEcyrzhV9qkU+lfLbYEgNmZnGwzqywAiE9/5tPQ84MedXwcf/V47HMk/1/44hfUFVv+b63c963awW4MAPW8LKZ7j4kYMwt03WV2v44FAFz9RzcwAoHiQSw/mL1YsC9Y7Wu3s9c0vyAvLfvj0UU2XcjFlQUCIVdFAIXk9HzsYx/zKh91Kp+1OC2HEwF67tip5rvqVD5rWQ5tmO3YBhlO1XcQif+Pf/zjZT82cLvFW2+9BV/60pck5T0YwD7NkX/83YfC93J/1zCxHduhuLi4WWmbLjtbS5BE5WLbMeJvtuqO4tBX/+iraiBV9ARAoCs/egegzcTsrn2P74udr7fF/HV+1W7izzerk50YAHjO9Mz0grRZNq/LCwDL6X4dCwC4+k9bAAgqUcuneBAkAMQQevDBB/1o5JiRd1wRhDk3SCOjM/ThvTv8F09fUV1gjfDxr1qW03vxzUv1aj818QK4dvY6+6dhOcrLth7dY81elrfddptVOQTCshEBlB+b0kSEN1GLLm709/dTI2jAdyO2x/r16/XpYhvZyj8h3lZIZhU7E8WRNltEezp3PQDsEO7NmzerhxFZ27BhgyGJq6qqsk3wWBBAWx4AM9lfmTbzlsi0ALCc7jcJAYBiABDiAgB5gywvmLjCtyhEuW///v0SGjgiEUAxemLn6t0f+XKqalb1fe1vvyhdP39TKAJs2LYudm7Xl4JG5bSPDY373vnVe17cG5ufP1+ompyI3UvT8efDhuUUFRX57rrrLi/GJhBN0pzbbNPp06cj1EsIBAKB4ASUk13cJnZtzGyTKCdki/cCyIk6zeT2FoBsizkLvQVgoe7XuQBAQQAJJAAQdPj2t7/dIUmSvHbtWh+q9nh4Cj3qXj5c2UBB4OzZs5jWRr527VrjoUOHwsqkN2+1/H82fq9DqqyQ192xRivHo5bFl/PeSxfh5lWlnAv9jf/jy98VlhPufqNjRcWKSHllmbp/jtXH7XLHysFjZGhUvnXjVqPSj4XlvP32276ysrIu5fBh0Kui4iLwFHhUrwIMDIgpzzD2gXLIGLFXKWedUs4V6hEEAoFAIGRPLMgVDwqsC5/JiHnK4s/FlP1noVzis33dhd4CsFD361gAAAoCSOAEgHSnRyMsWrQjob5+/bpKkjGvKa6MY2opjSCrx/hYLLe1bFjOSBSuvXsj5XKmo9MwNqCcV5wHrmI3eGaUl7A7D6bHZmBybAomxqIwNTZlVU4IvR7Gxsd6MVKru8ANLrdLrQ8aGzhpo6DApT0jDwACgUAgELKDyKZNm6SLFy+q9kIubEtFG4Wl88M6sYWyXMkmhIsZbKFmanLKVMhYDivizDNjud2vYwHARTEACJwAQB4ABIRChkNLtByZni6BQCAQCDmJrrq6ulbcoverX/1qwWNT4cJAbW0tKHWC4pJiNZ+9unVaqRcuIEAOOADgAgZ6KKB35PXR65GnnnpKaC/ZCSiYKYK6HGIALPT9OhYAKAgggRcAyAOAQCAQCAQCwRoUODm9UMhr29NPP13x6U9/ulk54MqVK+oK/EIBAwIjuWb28cTYhCoK4L57hT3BbJ5zBSAdWZF44Ko/buceGhxCj0Wj7CpH77nnHv8bb7wRy0ywVIn4cruuFjBSTkIAoBgABK4vkAcAgeAY6IJHIOQaHnjchznhW5VDotYgmCB8/PmwrbSMtFBAyIII0PL00093Kf/0rlu3LifqhIRu+NZwWsoq9BSmvX5aQGdZaTsjIhgsLCzc09jY6Mf4RkNDQxlvsxUrVkB1dTU88sgjWRXKUKBBb4i77roLVq5cmbXrXrp0Sb3u1q1bYc2aNVm55saNG+H2228PKs896FgAQPJPMQAI9GInEJI3npWXnA9TJhII2QKXJsosTgWS/3pqLYIF/A887jt2/Plwrx07gQTPxPYgZEQEQCIrU0ukrT3xPVH39NNP+ysqKvDI+DVRNEEBAI+FgkKOs36tbdu2ZeuS+ExDyrO1la5amAWAXJgI7EVmlmOdQCAI0V5TU9MzMjICp0+fptYgZIX879q1C/8Z6u7uNnz5D5wf8KGrKoFgA+gtYksAwD3HBM2GJvuZsLiEgBC+N6gllh9o1iaYCwCkZhMIjqAQsN6Ghoam7du3H1YOTI2YM9GBCUsPpaWlaiYNzYjba3burWvDR2DOC4BAMAOuJAXt2gkkAJAAQCAQSAAgLCEBgLYAEJzij7//hwHlR4dyhBVzaO+3Pv+dSI6UIyvl1CVbzl//9V9z5UDd17/+9YiJCBBsaGjA1TOfJNF2a0LmCZvZyj/D9bM32qruWI39kjolwQyy0ldk2wJAAZmSJABkDk8//TRuWzpILeEYXU899VQvNQOBBACCYwGAPAAIDAcOHGhTfuw2PalyVs6/zxXQfvPDnBtpiD/l4HMBy3Jm8/PlfE+BaTkPPO5rVn7sMStnVfVK+e6H76rXCI9PVM62bdssy7n99tvlT3ziE6blCESACJBrHSHHoBC7MLUCIV3ARYICN8UAIAEgY+Tf73a7ezbdswlcZfkwARO50e/zXeDKc839VI5zr8kwPDCspirETAUDAwMLVjfMVIDBEmtra/1K+3ViEEWjtgXyCFtqQLuz3U4cABIACKYvMhIACBz5b3399dfVyKaitDWb7twEH/rj+5WOE+szoW/+/iER+W898ZNTcPnMVRgfmV/OHTtrwFf/IeB6XlhfjkL+1XLMTK38Ahfc9ZE7+awm88pRyL9azs2bN2F0dFSYqmX16tWwe3eCXhH++te/bkrsn3xhv6S9WH3UewhZeul3Hdr3bIiagpBNkAcACQAZxsGNd2+E4juKYGxyTN1ONwsLH8ekIL8A8lx5qgA2eHFQJf/f+ta3VPK/0JBlOfZz7969zQrRP6InhEj+J6ITfT/9+b+B8jMr9Rq+MQKf/73Pw8kzYbh8NXtBkieGJ6D+s3th10d3qduVsA9hlgSWpi/dwGtgYFTMEvHDH/4QwqdPgLswO3MkZpT4+COfQOGn1iQDhFgAwIGVqUYhEAiL9yX8yiuvAB7CSae0EOo+96hCumNkW1bmEdF+5IO//kEYftNz0rAc/1f9ilHp4supE5VT4HGDq8B4i8o9j90DBYUey3L6+/sBDyP80R/9kZrKhZWjHHU2yH/fZHTKd/n0BzAWGYOp6BT1IEJGULamDKR1FVCxtrxe6XtNh/Y9G6RWIWST8NJWQUIGIU0XTsHQ+CCMREdgNDoKM7MzC97nC1wF4HF5lJ8eiLwfUQP+5gL553HixAk1OOy6devQe1G/Itz40svH4OyF97JWn8gHQ2pKvv6Bfrh05WLWrjs6MKZet7i4WH12+G/kuZniuiwzSmFRIdy6dQvev/w+eIqz5yV18lSV9JHahwLKP9scCQBT05OQN00KJoFASHwJT3qisO8vfh8mRiag79mX4Nb1W7Ev/fsfg7Wb12qTCMDkB9Mt3/yTZ0R75KXhm2P2ylEm5+nJaEvX578tLKessgzu2HEHTE9NwxX5CowNj8W+3Lh1I5StLJurjkK+r52/1vKP/+/3heUUFhbC1772NRgfH4ef/vSnwKfv27dvXyxlTTQahXPnzrX83d/9nVUMgY6xW+O+4z84QcSfkHH0yzfUn3c/dhfcdvfajidf2N97aN+zEWoZQjaAXlNaznECISMYnxyHqYlJGJ4YhtHoyIILAAgk/oXuQvWYjE7mHPlnGBsbM/rKOzQ8tKz6EbYFzlXo7Yn2nsjjMx0oKipSA/Pmesad+QLAzBTMTpEHAIFASMTWh++G2+9br/575bqVcPQvfqSS+B2fvg/u/5174y/r307C9LVZQwKy4xP3wYb7NlqWEx27pcxFk4blrLl9DVSsmstdW7KiBM6/dV5VdletWQVV1bGc6HDmtbfgytkrhuU8+OCDsHnzZvXfq1atgu985zvqy+GjH/0o7Ny5M3beyy+/DO+8844d",
		"YlV//vgFGB0YpU5DyBpO/8cZFABYjIqQ6Jzv/N13fG63G7emUBBAgiFmZ2fDX2n6SottAWCSBAC+PQhp748q6Z+enVaPBfcAUP6b0eqhHkCcaTEAt66iCIApmo22fKbcN/Ly1C0GWLanwLPIBIBppeKKEU1YDm8qDOBDe/wJ9gyX87+5ALc9sA4KigtgzaY10NC2F37701PwaOPDsXPCP3wdthTcaVrOuZfPw7o711uWs/WxatNycAJHDy50tyouLYE77tkMgzcjUHXbmtg5kZsDSP5Nyzl58iR86EMfUlVbDJ7z1a9+FUKhEPzu7/5u7Bz8/ezZs3abUrr5/gCMD09QpyJk07yxPKO/v79VMVDqqa0IFvB/46++cezP/vTPLCOI43tjcorSnPJklZChdtXcthe8jWNO0nN1IiyePoTzFR64WJQpAYBdYxYWjwdApLC0SBoZuqUGtgDihUt/MAzMQmFZcYxzcV/JlZWV3vfeew9uq76NAgEuE9zovwE1NTWxPqD/fnxwAvq+eQw+3vwxlbxX1lSC/w8fi31/9tfn4My/vQVbPmsuAERvTdoqx0oAcBXkQ2TgJlRWrlEnXdzfVby+OE6HJsZhbMJ6FX5oaAi++93vwpe//OWYCPDFL34x9v1bb70FL730EmzYsMF2W06OT8LkKBnFhNzC1atXKSglwS6wr9gSAMgDgASATLdpwn822njo2hC8/et3YGx4HKS1FVBz30YoX1MenwvPXVM9DxEb77099vmF376v/lyzqQqKSovM66TVi0SARdSPOBEgkwLAnGCV2+3BCwBdK6rKW2emZ2Dk8jBAAR/Mm7DkBoIy7xWWFUG56jEKnW2f/HPetblr+/btHejG8u6776oB0EgEWNpAl/eqqirYsWMH/hrs7u6WRedcu3ANfvHcr+B3vpYYB++63A8//+4vYi9Uq2tdfac/5XI8JR7IK8xT9wSWF1ckfDc1PQWjkyNQVFZkWQ4qwe+//z784Ac/gCeeeCLhuw8++AD++Z//WXXpcjbAIOf3fxGWH6LR6BGgtE8Ea6A9ELRzIsUAIAEgSw2bSLpN8J//8Ev4xT/+ct7nnzn4Kbjv43PbDP/jOz+DC2/Mkf3f+cM62LnnAfXf//Cn/6T+/OI3HoeN991uKkig+z8978U1NmOr8xn0JGHXWTQeAAoBbGv71/9eUb5OalYOmBrHrQC0l2mpwl1UAPlz7v9B5dkn7PVTyF9nQ0ODpJDBViSEkUjEOQEiLCpIkqRGLYW5FR/h3k/cOzU8PAyv/eSEGhDvs//tM3OEfmQcev7qKAxeG7R1rbHR0bSUk5efp25hiU6Nw63xPKgoXjlnkCov5VvjShl5s7a2uKDxiscbb7wB3//+9+Hzn/987H6/973vqVFcCYSlgG898622Pz7wxzjGKQYAwQyy0ldkOyeigEoCAAkAGW1TbuWf7bs3wmv/ciJG/m+/d4NK4t/4jzdVj4D/0/UTNdPQloc2JwoGyvn3/s494Cn1JAgORtfBGADsOc/S/v9FNz55ISDdSPAAyHUeyP+CRLDtX/97l/JPLxJEwtJ/ySvPXPiS7+7ubmtoaAhiX0BySFgWiCjPPWw2sWEQFcTxH78GlRsr4aG9H4Ej/9/34Nr719TPMaK+FfILrMuxZXhOxmOVTEyOwajLA6WFKyAycgOmZ5wZpNNa3BNMc4j9/ROf+AQcOXLEND0ggbBIRYAwtQIhXVBjANACAQkA2SBumghglqfslX85HiP/X/zGPvXfH/qvtfC/vvqs6lmI4sCdD21OeE7s84/9oT9BdMgzESSYEEHPe/GR/9kMxpJIKHsRbQFgIgASQpm6CkFzA6e+QECEHnzwQT+myGPk/V//9t8g/NOTcPXs1dhJDz+sBvJD91EjkhH68N4d/ounr8DEaNSwnI9/1bKc3otvXlKDmWmeLDAIQ+B2FaiBTBmunb3O/mlYTmVlZT0fERZTAb755psJ6QAxLoBFOQQCgbAsjWqKfG8tAOBWSrfbTQ3EweVyJdG2xsTt6tlr6ko/4p6PbY+dV1RaqP7+2g9PwLVz1xP+vmJNOQwqf/Pqv7ymCgV6ImeEPE6UYMCtsk7vKZMgzxzj+SrTHgCLYU5MmI2efGG/F+b2B3qpmywLILnvOrTv2XmkpqGhgfrC8gMS7nYDL4AWhSj37d+/X8JVcSYCqLhv7sf69etj5z7zzDNG6fJaqmpW9X3tb78oXT9/MyYC8NiwbV3s3K4vBY3KaR8bGve986v3vK4Cl/Lina/VT07EXn5Nx58PG5ZTVFTku+uuu7z6vLAbN86lKsR8rqyc06dPU351AoFAIDhBi0IOJYqlZGiHWpO22ZmEbQAi4DZChvI1ZQnnoQjAwH+OwsCbPzuligC4FQC3CKBHAFvlNyR5XH0Y0AMSgxHnCjDAsakA43GBuyh7ohSz0woK3dm9rjs/gfxneguAPlbFQt2vbQFAIf8Y8bVPMcglDMQ1NjgGk1FSj5YqyqvKYNX6lVBSUVyvPPs6XgTQyP+J0dFRSZZlGBwcJBe/JQ6F3KtBAJWjXnn+e7u7uxOiP3/729/ukCRJXrt2rQ9fcnh4Cj2q2o37+FEQwDR5kUhEvnbtWuOhQ4fCyuQ6T0j4n43f65AqK+R1d6zRyvGoZfHlvPfSRbh5VSnnQn/j//jyd4XlhLvf6FhRsSJSXlmmrqyw+rhd7lg5eIwMjcq3btxqVAwvYTlvv/22r6ysrEs5fBgDoai4SM3dil4F2Ocno5NqLADlkHEcKOWsU8q5Qj2GsBixbds2P1AQQII1UOgkwTNNMNtaR7AGI1J8NgBL8qsQev48XhzgP8d/7/rCR+An3/wpnPrZadUjgAUhNrzOLJeWkBMB0BZZUbYiZ9oNPRvNUFxRBGWz2avv4OU5QaIIrzuevetGtYxM/P7/TAYB1GcBwPstkbInDCXEsrAjACjoGB0ck04feythby1haWK4fxgun/4A7ty1WVpZLfUoH23i+4JC5CRMfUbEf3ng+vXroBh7sGvXLqiuru6A+emf2pFQ43lIklHlxpVxdGnUCLJ6jI/FXrKywaXaJ0aicO3dGymXMx2dhrEB5bziPHAVu8Ezk6fMaHkwPTYDk2NTMDEWhamxKatyQugmNzY+1os+fe4CN7jcLrU+GBdgemZaFRTw4AxjAmGxokMxCn03btygliAIgULomjVrUOw8pvzaSS1CyAXMrcab791ef091bAX/tz87Bdvqtqqf4+/vvXxW/Tem9+NXZ/HfeB6ef/G3l1RPAHY9Q4KYlyhKJHyVl7do2lQlpq6SrF0PvTVj153K3nWHrg3HtZssBAHU91H1fldn734xvbZTAcB/6dRlIv/LDPjMV1ZLXvQA4bwA6jH9H5H/5YeTJ0+iAOBtaGjwd3d3h9jnChkOpaP8HCxHpqdOWEbwosBGe7YJRkChF0VRj8dD0X8JOQU7HgC1v7sDfv38b1Qy//2nfgAb7lkP7/3mbIzYf+TxB+f9Pf7+0OMfhu7f9sz7XFwR4LYizM4pAlr9WEDhXGkv0+9nZrOarjiWOWGhrqtLA5jpGAAxkWiB7teJAKC6/GNqrcWkYBFSw+jgGPtnwsveynWIsET7Az13AmEpo3f16tWBXNqnSsgtoAeAlhI2RK3hHHYy4RCSJ/+gud4b4SGF4KP7/6m+M6oIgAfDR/Y9CJs/vCnh75kr/4Z7quEO5buzvznHvjC8zgzM6rYlQALBXCwCAHpRTo5lb6GPkeBsX3dmaiaxH3HbADJyPd0WgIW8X9sCgPpBgUsVAQjLA9ExWgkiEAiE5YDTp083bdu27QgX2JJAECGi9BU7+9bl+++/H86dO0cpUxVs3bpVjacDJJ6km8nG9tpPq6755nbrx/+kDny/ez+8q7n9YwBAJPd8YMDHmh5WtwaUVcU/+8SffAz65bl+vNq72jAIIK74xwITzuauB4AVpiamYGo8e7HemACQ7esyQsyn6Mv0FgC+7IW6X8cCAO5/tRtBkLAUBABy8yc4x4EDBwLKjz0Q9xzBvfFHn3nmmaDdMg4+F9CXgTiqHEGT6P/z8MDjPlE5R44/Hw46uSeFGAnLUQzh",
		"oNP2sbsHi0BYABGAyAkhXWgpLCz07du3z3fr1i3LqONLGUj8tdX/TuU9SGMsncQREj0A7Kzcrq5ZpR6JOsJswvf6zz0lBVC9/Tbh+Tr+DwDztyOopHJ68XgATEWns8oBeA+AbF6XbW3P5hYAPs7EQt2vYwEAyT8L1EAgEAg64o/kuE85fGfOnAE0+hBlZWW4+lGvfH9Q+XWvYgDJJsQfy8DNdv73jl8ATAeIKK9cAZt3bvQXlngOKufs7fpSMGxB/GN1yZtvMPiV79W6HH8+LFsQ/1g5fMYLdIOtqKjwK99jOU02V8QQYcWI8F1+8wPqMISsoeqOSvZPClRJyAq0dK+1yrzvx3cAHsscEaVNKOJ/ukkVe6s7yAKQ0frMJq4m53GEezHFV5mKTsHkeBZd0zUBAFM0Z/W6Wd4CoA8CiPebX5C/IPfrSABA8u/2uGnGIRAIQvLf39/v+9nPfjbP5fOVV16BT3/6077Kysoe5dw6zTgUoWdiNOr/UcfP4NKZqwlf/Px/vwK/92ef9FbVrOo7+FygtutLQdmM/Ofl5/kKCgti+WX5CTg6PumbnZntU86tPf58OGJG/sfHx30ffPCBGgCLB97j+vXrfUVFRT3KubU202K1ex/Y2DM6MAqn/v0MdRxCVsj/rj/4CP4zxKd0JRCyJASEqBUImcKck31e7GceLOw2ZRYnLT8vMWYaksrFFARwbm969rcAZPu6+i0AzAsg00EAE2MALJItACQAEPhJjrCMXrTmL4zmaDTq+8lPfqKu/Hvvr4Ga+2rUL86/cV45LsDRo0fhD/7gD3wej6dZ+bhNX4Dm9u//wTf+FfovDAjL6Pmrf4Mv/sV/lcoqSzFfeZNRXRTS7yurLIM8V56ae3fVmtXqF5hC8Nrlq1BcXozBgLwzM7PCurBylInad+nSJXXlf9OmTeD1etUvZFlW97a+//77sHnzZm9+fr5ZOTEoBKz3yRf2N23/+NbDygGDHwxBdCxKnYuQEZSsLIHSleqefiRhe6lFCATCUoIn3wPT7kIoLiiG6ZmpjK3cOrGNC1weKFTqVOQugumyWaitrYVQKKSmEHa5Ft6LGu0ZrAvaNGCQBnkqyyvxsRgA0YXxAOA5Tab4TR4vCmk/8H6zqVklLQDgFgA3bQEgkAhAAsB8NJ4+fVpNEbXz0w/AZ/7bp2FidBzyXfng/4Pd8H+++WN4M3QK9xjDjh07DhqQ5ca3fyXDyPVx0zJOvHgaHmvcGTj4XKDFIB5AY4lUopKfsvIyuPu+bWo5OMkWFheBVCXB++cuwPTUNNzqHz5oQtwbcd8q3ve9994Ljz/+eMKXvb29amrEmzdv4h7Pg3YEAE0ECD75wv5e5Z++itvKqWMRMo0IrfynD5/97Gc7cOxSSySg5cUXX5zXx5R5Dr2oUBzdvdzHoHIcQQGYukpacWz00pi/dFUpTLonYXpm2iQ4X/bsYo/LM3e4C8Fd44bJq9PwhS98AXp6egBTrS6k7YyrzxUVFfDEE08w8i/sk1PLJAvAlLYnHgURj8ejxupAOzYT3hr43LF8PFz5rtj9ZjMN4FSyMQDULQCF5AFA0ClZBAKANxKJqKvtjz7xCAxeH4B3X3sbVq6tgA13b4Tf2f8xOH/8AuA5CiTcMiDYBuC/9tZArIxbN4fg7VdOzyuj/93Yn6ERHhLVpXxNORSXFUF1zXoYHRqBMy+/CSukUrh960ZYW71OqcdNVcy81T8sPfC4z2sQC8CLbv+43/9Tn/rUvC/xs1OnTrG4ANK2bdu8p0+flm2KABGgaNCEJYaGhoZcI8dHuru7g2ku06eMe/9yDmrHY/v27VBeXi4ZfN03PTnt6z9/A0YiozA+MrHs2qdUKoHyqjJYWS3Vo/cXCsDUa9KGzluRW3uiv4n6ZgoUjpLvgfwc8ACA/HyYzgeYdE3DjAszDRThlkL1QBtoYGBgweq3cuVKkCR1uKJg1/TUU0+JFlGOPnD/A3757LmsCwAoPCApzpogogVmRAGgsKhQtedUISkDARsxi15RUdGcAKB5guD9urIoAFStrmLCj0MBwO2iIIAEEgAIQqB6ipMbut5/8N77qvt9vvIiVGZ2KCwtUb/jVFWv9gJKxHRerIwrZy/GyphVJmRWhp0YP4UlSl3Ki6DAUwBjkRHVi0BNYaqtDpStLgdXoYuvi3BCxGvjRI2KuR5YF/yO84zw2plYFZKEb99WoFVEQnaABl6XQoRDWbiW7/z5837lWPCbxhR0iqF7LBNlI/lHzx8CxAKj6qGQ3WYk/6ePvQWjg2PLtn2G+4fh6rvXYO2WNVCz4/bDSrtgLA6Zek7q0Mhr7dNPP+2HmLa0sHYpWgMKfVSPKMwfG0i+NQK+0G1n9j4I3n3n3Xv2N/6hf3x8PDtEfGYGMAXttru3wbq167LWDhVlFep1b/TfUL1HMIZEYUEhzBZkhpTn5+WrcybGkLr77ruhsqoya1wKbda1a9YGlWcfdCwAqFsAKAYAgQQAgsEEPjI8Av3n+6Fy/RrwFLmhqKQQCpRJZ/D6kPrdSmmleq5BNGS5eLXHO/LGXBmrlTIKFJKOZXiKi2NlrNpQwRMbw5dwUVkRzOTNwIpV5XD73euVstyqiKC6CCqTO9tndvz5cMisn+NkjYSmpqYmkVVFIup3paWl6u92Uqhp5L9venrad+XKFRgdG11UuYEJiwtlK8pwdRYjsNcrfa8pA6vh8zAyMgLXr1/PWWJKyBr24Mr/cib/PFAEWHfnWhSn65VfO6lFskZmCckJK3WqsJJl3HfPfQtyz/rA1ZnCRFypggXIjhJRnq2t7YDCLQDkAUDgyRGBoKF38+bN9Zj+74cdP4Iv/sUXFAI/lzN3fHgcfvCXP4Dh4WEMmIcfGb2sQ3c/6g28+qPXTcvY+dF7VLHAJBVgb/+FG/VrNlXCaHQYVpVWxspBDI4NgMuVD1feu2ZWF7UchdzXo7vej3/8YwgEAnMeCFif8XH4p3/6J3WvmCYA2DVAOiYmJnyvv/66+rcEQiYxcHPO1RTH3Zo1azoaGhp6u7u7KRUgISuY1AJcka2gYGYWJkYmUACQqDEIi0QICFErLE9QFgACkX+CXXStW7euHl2akNx2Nn4T1m2ec+O68t4V1fDZunUrKOfgR+0GZbSvWF1S/+iXd0r//p1fCMvY9ugWuPujm8zKUOsy3D9cz9wu+4evQYGrQP0C93ZhpGBcmULXTKtyiouL63EFFTMB/M3f/A3cdtuckIBpAVEEwK0BmgDQbrOd6i9evAjZcqsjEBDvvvcuCgBIPIziZhAIGQFuk3K585d9O6jRvgkEAmExCgC4BcDlIQ8AAm0BICQCcz0fOHCg6ZFHHjm8fv16+M///E84//rcPmB0cXr4Yw+rAoCCFqO80F1fCsoY2X/7Y1sOl1etgJee+02sjPLKFbDjv2yFh35P3TYfVM4NGtUFXfofeNzXdP7k+4cjVwahylsZ81yanpyGm5cG4OZFdWW03cz9H136t23b1rR27drDuEfs2rVrauo/BAYGRDFAiw3Qacf9X4OE+4cnp8g9mZA9UH8jLJitkJ9HnqNgP/o2gUAg5JwA4Ha7oIA8AAicCEAgcCJA8MCBA5FNmzZ1KIdX97WskX/TNEhI7A8+F5A3bFt3+Im//Jy+DHRdblfOsdw/qRD74AOP+yKDV4c6lENYF+Ucy5RMCrEPbtu2LVJWVtahHMJylHMcpXbCPf+YgpBAIBBIAFgeyM8ne4mweKDt/2+lllhSUG1oO3EAxB4ANJETgDwACLrJwu3uKy4uBu2Q16xdI5WUlEgYRX90dDRy7do1eWx07OBzzz13EN3fo9Foy+zsbMIk5HK5YmUUFRfJ6+6okkrLSyR0IVXOh0tnrobHxsb2fPf/XrkHc+liGTMzM2GzumA5ZatXSJ5ij1qX6Fg0MnxzRFb+/mBFRYVhXbRyAloZWFZ7SXGJr8BToJYzGZ2EsfGxkFKOpCCg1ecnSjlXrNoKswbMLnCqIgKBQMgGMN4KbR2lBRPC4iL/k9OTfa9dehWiU9GsXPNi+DLs+dQeuDAqw/Wh7AWRvSHfhP/y0Cdh10d3qakAMXgsxmfKlI2G10AP",
		"0uFbw/DDH/4Qzo+cg2KpOCv36nF7oHb9A37l+dY+9dRTsiMBgEAgAYBggIQ98OjmjpMokvfR0VHR+bJVGYMfDMPk4Iw6YSLBtlnGvHKmRqfBg8ldFEN0emzGSTmhBOIOsyGsy//P3rsHx3Hdd74/vEHwgSZFkCJEEQNKskTGFoeWFFm2Eg7iDXVTmyzBW7Al7+aaA/vG115uCkC5XBXnxgFgK4+qLReArVJcyY2E4a7/sFzcBejEvle0HQwVO44fMoeSLCiWSA4lipTE1/CB9+v2b3Cac9Donunu6enp6fl+qpoDzvTznNPd5/s9v3MOX5PJCOMYXA3g3YB3A5DLQxUiANLvD9wSoHQ49MrFU3TxxgXPDvj2O2+loyNvztygK5OXPTvuxfffTR+XG3v4vcV/F7KRhhuQ2ACoq6+jmzdv0vs33qN1tes8u97Gukblga27o+qffTAAACp5IG9UsR/Pdx/qgzful3MR+0kiZwFw9n7AOQAmPQggDACUR1BKhCZmJ8rqgrmRiRutuMGKI0N5WutCwDNJ8ZhSS4v+jgKFAQDwQgMAAGDrvYB3A7hdHhABgPoSAD5nZmYmbQJMTEykTYBCGAD8DODoUd53bU0tDACASh4AAACIHRDAslBZgcGjCYMAAuBnOOSfhTkv3A2gUAaAdowlQgQAAAAAACD+QRCFbxUGj16+MZAEAPjZAJBNgEIaAOnxBXw+DvQqA4D7LCwuLKKkAAAAAMC3JgCMCP8YAJgFIF0gkQYA+NgAuN06X8BBALXjlFwEwNT1KZQSAAAAAJgKb4hvIBsAlTWVSAd0AQDA9yaAbAQU4t14OwLA56wyACZSkzQ3O49SUg4sLiFsD6x4MAIAgNWKDgDpsqAK3+oaRADgngDA/+JfXgp5jFLqApDa0LReuXTmEtWtrUNJKQNmJmdpY7Oi/Tch/ZTcvHlz6MqVK+mpLPBSK5PyMDNDLS0tt8uA2XqHDx/mQtOtLgfUJSyVn2PqMvjMM8+krByv65tR3schaR98zFF1GRr6w1jSyj4eejJsdC687RE+l5eeT1g6l127dmXdz/j4eAolBICM0MF7AWjwvNdVtWhMqEAEAAC+NwG8GAOgUFMMFsoAGNq+u7l3YW6B3nvzfXElKCzBvQsoLf5b9tzN/xv8xieflQXO0O7duwd4Kos333wz/XJHZS/Y8IioTU1NtGfPHv5v7OjRo0kT8c/ieGRmZib0b//2b3TmzJn09zt37gzff//94bq6ui51nbZnnnkmkUX4s9gem5mcDb/24pt04fX3aHpihppaNoXCT+zu3tC0Lqqu0zn0h7HRHOI/fS7qEtI9q0Jq+e7lQ6nrtL30fCKRQ/yn96OmQej69et069at9Pfr1q0LNTY29lZVVXWp67SNj48nrKZnTU0NChUIvAmAcwDpfKjiCAAYABgDAJRUvW92geam5ryTHYvLTeLzHh93QYxrd7tvfoG7ANyOAqDiXq9lA0AVgH1f+PZnG1VB2M2icPL6lHrS6AoQVNYqDVr4f0zN+x75N1X8DXZ0dCiqGOxlQZhKpdLzWoLgoiiKJlpZdPeYiP+0cL98+bJy7NixdMSAxoULF+jnP/85HThwQNm8efOYum5rlkiAsUvnroa/OzhGNy7fuv3lO6+/R+P/fJp+6z89ouz+7XuHu74ZTQ79YSxhIv7T51JZVanUNRjPtTozOassLiyOqeu2mkUCiJb/kenp6dBbb7214oXA88Sq10o7duxQ6uvrx9R1946PjyctJGdiy5Yt4ffffx8FC3jGxo0btT8LHq2CCAAgkx4EEF0A0GgGSoqp1BRNXJvw7HiLc4uZ41727rizE7O3DQDZBChUt1f9LAB8veRhF9tZZdaeASBMgJ4vfPuzQ+qfoYbGNbg7gk9SzXNDQXP06NG+jo6OGJcFFoegLEip+Z6tlbt3dnZW+c53vkPq5yoBwN/xb5/4xCeU9evXD6hfdep3wGH/3PL/vaE43bwysXofU3P0w7//F9oSukPZvGMj76PN5Fy6KysrlMatG0wrXfXr6+nG+zeVhfkFw3PR9qM+rENvv/12+oGtPx/+jn8LhUJKTU1Nb5b9yPQ3NzePTE1N0enTp1GqgCfif+/evfxnPMc97KoJAADELwAlagDcmKZbHgpxjjBnpj0+7tzk3Io6nVcRABp8vdq1e3K9zdYabFdZtkIQJnFrABEGjrIANKKnTp2i6urq9GLG66+/To888ki7iVg+9Napi7QwtURr16413cfL/++/0e/8Xx+JcHeBoT+MGbVodq27Yx2tsWBUXruQas8i3A9x2D93c+HFdB/XrtGWLVvarRgA6n0z2tHR0XnPPfcMqwvdvHkTETSgYKxZsya9sPhXl4NeHPOuu+6iTZs2WVp3fn6eXn31Vcv3wPr16+mBBx6wtO6GDRtQAAAAwAFLC6oQnveur/qiEMUL6jG9PK7W9UA/DWChxwDQugDw9VYV4XptGQB9L/x5SP3gVq4Qbo2ygMX9UN8TX13VYqQKGJSF8oOFdn+WFkRlanqK+8Zn3QkLXl738OHDoWeeeSap+zl86dfXcu7j8pvXb68vhM2qc1m3eR01bMhuAFRXV7EBoPB4ASZjAYQ4ciGbocEI8aLweAFWxgJQ0zCm3kPcnSLMggaAQt+7XrX8q/SsWbNGEaZDLjh8bPiRRx5RuIsQmwG5zIzf/M3f5PuR7/l+G+8xAAAAILs41nUDKIjRoesC4FeqJfHPFe2x+dl5Zfr6JM1Oz9LSwiJKS0CpW1tP9evXUHV9Tbua922yCSDE/8nJyUklmUwSt5CiBTPYbN68OT0IoLq0q/l/kFuxjdarqa6hmtqanA9YqfK/ioW5pZz7sEL92jpak8MAkKa5NO3Hwo5tttZ/A0FjCTUNUybmBQAli12jQX2eJNevXz+WywRgEy4cDvMn7/+guH8AAAAA18S/F10ASm0WgIH56Tnl6tuX08KwQVlrp1IMSozZyRm6eu4SbWjeqKj5zSOpt8plIZVKKS+++OLt8NJcLaSgtLl48SLxqP6PPvooNTc3c595QwOAnwkTt7L33drStCX9aTITQKLpvsbwuVfOZ93Hpu2N2p9Jk1VSS4tLSt267FOWTt+cTn++9HzCTIin1GtScrVMat0VxsfHIegBsGkYdHR0tOUyAVj8q+ukIP4BAAAUwgDwqguAPAtAKRgAkRuXrtO6pg1p8Q+CTe3aOqptqKMb76XY8AlxBIgUBdDO0/9x/8oNjehjWQ7Ur6lPGz3cx7+5uTmkVtgjaiVcL3Zj9913X/SVV17Juq+WlhYyMxBU4nd9cGv4J0dP8ij9pvv42L9LD2jGswCYGQCjF16/GG1q3Zzd2HjzvWznkv6tsbExevXq1az7EWH8oygpALhvAnzwgx/kMQVY9LeZTUEKAAAA5GsCFLoLQCFnGHCTFU38HPKPqVzKywSYm74d2r8itJmnQKutrUUilZkJwPmehSEe+Ovxxx9Pj/hvtPBvd955J69r1n+3f/0da1OPfmKP6T7ueXQHte7dzuv2ZDmXfjYQzvzCXCvwb7eWpxnM1pe4v6amJrV169bbzrB+4d9Ef+chlBIAnJsALPC5lf+RRx65HVXGhmFzc3P6fvdwHAPgZoV3fjFdlyj3hRaXUBgAKAHx78VSMmMAAABANjik//Dhw50PPPDAMLeIv/zyy3T27Nn0b62trfTggw+mRwdX6TQJ/yce0b/rm9G23b9971hTyyYl8cI4nXnprXQ0wOYdG+nR/z1M9zy0Iy3M1XVNW9xfej6RfOjJcOflc1eGOcy/8c5GqhfdAaZvzdD1d6/TravprgqdJoP/pRkfH0/u2rWrp7GxcbimpoY4EuDWrbRpkB6okA2PhoaG9H4Q/g9A/iaAHAlw4cIFuv/++zXxH0MKlSYzU7N0c9lsLWvmPZzqCwBgD3nq2kJNY8v7vb1vn0+NCgMAAGDHBIgdPnw4oQr9AXWJ6H5mgdyvrpNVKKvCPtH1zejeppZNA7/7uY+1E31M/jmRS/xLJkDsoSfDCVXoD6iL4blk6fsvmwCxXbt2JVShP6AuhvuB+AfAfRNAFf8ceRZTvxtEypQu",
		"s5OzdOPyzbJPh4XZeRQGAPwqeKur05HNdXV16S5oCwvuG3Ys/nn/vFRVVsEAAAAE4uG5pA0Kycu69evSswfwwIBXrlzh6f8iU5NTkW9+85s0PT3N4fxtS0tLK4RzVVXV7X1wl4MNG9dTU8sm/p5S79+ka++mwlNTUyP//Y83kvqZ3sfi4mI827nwfhrWNdAapT59LtPXZ2jy1mRE3T7S2Nhoei5iP33aPtTPE+ryU/UFcSfvZ252LjU1PZXi/SiKEhHnE1P3k0RpACB/E0D9s0v9uxMpUrIkNzStpwuvX6SF+YWyHjh6YU69/qpK4vSgZSMbAD9zLLw7HHnn3fNlZQDU1delZzVbWFygxQLMdFdRWUH19fXLBkBVcQyAzZvSY2PlrKfCAAAAWKVN/g87qDdu3Eg/5ExG0U/k2sfc9Dyl3r6VfjBPT81Y3ceq/SwtLBFNVVCFWgFL/219PzGjlwRfk8nUl++iGADgjgmgfkD8lzZDquCN7nwoROdOvU2Lqggu117wDY1raOcj6cmUEt/45LMYMBb4ndg9Lfce+NSB/xSZnpn25IALswvpLpX3he6jLZu2eHdv1q9NH/fK5Su0uLRIak2R6mrqaKmmME+ryorKdP3x8uXL6S5uW7ZtSRsDXlBfV09Nm5piX/nKV2IwAAAArqCK/HjeL4CFhbhfzkXsJ4mcBQAA+6hCN/GFb3+2c3PLHQPqovBYLjMTM2WXDnVr66iuIT1ocnqgS5QM4HdUgZiedeVrX/taxOtjP3DPrqJcMwtyL5ihzDOQx8sSs0h5RUrNW0sRSDAAAACW6OjoiKofB0g3Y4TPSY8pgHnFAQCgICZA7Avf/iy3eIdZBAshXI6k2BBBiQAlZgTEkQrlCQwAAEAu4c+Cf2x+fj587do1mpnxtoVn+/btdOrUKbp+/brtbZubmyP33ntvlPsbez3FmEi3Xq4YoxQBLwSIugyp5TzuoJx2q8s+pA1waAJw+iJtAQAABgAAICD0svh/5ZVXaGJiwvODswHA4v/SpUu2t+VtUqmU8vDDD4+o/23N5zweejLMQimUbVpBnagam5ubC7/xxhvp8zcZUwCAvOHBOJuamnhpV8tep9Up9eRyeu7cOb5XaHJyMlBpwwOBNjc3206b3bt3454VbNiwAYkAgEWMpph76qmnfl/9/i9v3LjxgPpcqUEqgXzZtGnT+crKyqHLly///fHjx1dEuS4t5R7fAAYAACAX0TNnztDVq1dL8uRZ2Nx7770htfIf1kcBHD58OKI+RA987Wtf67GwKzYRwg89GW596flEri4FA6qQCv/gBz+AiAAFh42u8fFxevjhh6mlpWVALeujFru9dLP4f/HFF9PiP6hp8+abb9KuXbtY1FtNmx5V9CooWStAeDsANtm/f39o48aNY2r9KVRTU0O1tXW0Zk1DesaMYo0SD0oXFvY86Pbi4iI3yG2fnZ39rw0NDf1PPfXUk9/61rf+0c6+YAAAAHKhsPj3OvTfTYQIV3TiX1FfwCMPPfSQcvz48RPqi9p05GZV9PepHxHJCMg10FM7t/xD/AMv4a4yLS0tXM6520ncwib7tJb/oMMGye7duxVxH2cdpf273/0uxC4AIC8+/elP/9aVK1f+6caNG9UbNjQSGwAA5ANHl2jliKcaXFhYoMnJiQa1jv4Pn/nMZ3qfe+65r1rdVyWSEwBgRUCzAVCMpYCM7Ny5U+FxDRYXF4ePHz8eMhH/LBh6pa8iwhDIapo4GbMAgHzvU5uEZmdnyyZ9RDcijMkBACgo+/fvV27evHl8aWmpWlE2Um1tbVq8YcHi5sLTVrO5VF9fT+fPn+//3Oc+95TVMooIAABATjjsiEOOiolRvzqnHD58uG/Hjh0R7jvNqC9qpbGxkVv29+rEP7cYjhjsolf9Lf7S84k4SgcoYZJsAiAZAADAPe6+++7Rd955p37Llq3pcH8ACsmmTXfQlSuX2eQeVv/7LRgAAIBAwH3l8ukvpzcPFEVJ7N27t1+/HkcB7N+/Pyl9xaOjm4UDd1GOMGt+8btpXIBgw+F8+ZQZ3t7p/RH0SmqxDUwAQHnA/f7ffvvtfXfcsTndMguAFzQ1baHz59+u//znP//X6n//BAYAAKDkyVeg6AXVX/zFX3Af4NFc2730fKIvn/PmsD8M9AOswrNs5FNmnM7SwWGEfNwgMz09jQIGACg4ra2tX+GxVe644w4kBvAMfoevW7eO33WfggEAAAgEH/zgB/MaUK9Y01jxA7m6Bo9ZYM8AcFpm8jEA6urrAp225TTWAQCgeMzPz39k7dp1gTdVgf9Yt249Xb58ebul9z6SCwDgdxKJ/AblfvDBBzns3/PzrqmtSY/UCkA+ZWbbndvoM5/5DPcrzaxXU0PPP/88Hf/+8byPyQZA0ENVb928hcIFACg4s7OzzWvXroUBADxn/fr19O67Fy2Fy64yABaWFmhxcQGpCNL9SXm+SQCKDYdE37x50/H2xer/y8IKU/+AfMvM5SuX6cUXX6SPfOQj6Rf8mjVr6MqVKzQWH3OlfHH3mqCXUwzEBQDwss6Cdz/wGjtlbrUBoIr/uQXMXQ3SYUxUOYtKEyg+LHimZ5z34XU6qNpDT4Z5yjDT0IFcswDMzc5hEEBgC7My8y8/+RfauHEjPfzww+nW+sGhQdemyWSzt8BTbhYdDAIIAPCCtWvX3rh+/bqCCADgNTzWjdWo0+rVL8kFWlhEhRUQWv+Bb+DWOzdnATh8+DBPlRLV/s+u6cc+9jFqbGzcu3//frm/QYiMpwFkeBDBrAYA9zuG8AB2MCsz01PTNDY2Rlu2bKHnnnuOrl656uqznvcPAwAAAPJDFWC/vH79+g4YAMBrbt68wXWEy44MgPlFVfThPQlEpZDnfwfAFwZApXsGgEq/+pJuf+CBBxQ2FjZt2sSufb9O/HML/+hDT4YHaXk6QJmkunTmOi4PXOh0ajZQnmQrM2+99RY9++yzdPXqVVePyc96RAAAAED+rF+//uvqM7X9/fffp+3btyNBgCdMTU3RpUuXaO/evd93ZABwBMD8AkQfWK4UQrwAP8ACvqLSvcikZ555Jnn48OHOc+fOjXzoQx/iLgZxVfz3Ga370vOJnoeeDEfUP8PS1wfV71O5joORx4FdcpWZCxcuuH5Mfs4H/VkPMxsA4AVPP/30j7q7u8+//vr4dh64FWMBAC/42c9+yjNeLf7O7/zOf3ZkACwPAginvBxYWlyiqirzPv7cEoX+yyCoPPPMM6OHDx/m1v1oZWXlwRyr8+8naXk8gB5V/FualgCiA5SCUEU5BQAA92htbf3358+fP/njH/+oMhJpw4wAoMDi/2fpgYHb2tq+8cQTT6SsvNNlAyBVt7Zembt5Q/1WFX0Y+y34Fc3UEtWtb9D+Kwua5ObNm0McSoKKYXnR0tJyuwwYlYdSRQyKkjIwAXoOHz58RP3M2pqvCv7kQ0+GOeT/kPr3oJVjwvUHwF/w1FxGzwEAAHCTrq6ul7/+9a/3x+Px/hMn4vTww4/Q1q1bkTDAVW7dukW/+MUv6J13ztNHP/rRH335y1/+L1a3lQ2AoXVNG3oXFxZp4uIttfZKVAETILjif0YVRevracPW9ADng31PfFWuFA3t3r17gCMA3nzzTSRWmdDU1ER79uzhP2NHjx6VDYAjannovX79ekHCjwtN87ZmHjU9rl6TYau9Kv4ttebzeAC0PPCfFRLNzc3hUkwvUNr3sMCqyE3xNuPj44FPG0VRqKEhbXjHUVLc4Qvf/uwArewaFRR6vvHJZxPIYZAPX/ziF786MDDw61deeeV//OAH36/euvVOuu+++2jdunXp6Vz5EwA7cBdBbunnz3PnztHbb7+VnhXod3/3d4986UtfitrZV4Xcwtv3wp/zwzw92NX89ByxGQCCSXV9DVUuh//HVPG/ajCzjo6OPvWjN11DTKXS3QFAsCvHosWaBW6nKpZTuvKQHjW/GGWBBcp7773naJCyxsZGXrgi16a/pkKiple7+jHy2muvlYW4Av4Q/4899hjfx2x2tVkspxH1Y4wrEqdOnQrsc57T5sEHH+TnnOW0AZYMgLFzp96OTKQmA3NN",
		"ofAOamhc0/aNTz4b1747fvz4x9WPR9WlVBXbv+7fv/87+i937doVFvU8JQBZN6S+a0f9cCL6rrMvvPCC8vLLLw+ePn36P77zzjs1QR9wFXgDjy+hLj9S3/t//MQTT6wwLK1Eb1foV+p74c9DtDz1FQg+SVX8J7NUDlEWyouUWSu5KA9cWWgvtTKuXlOsGAdW0yuqfgynExYmGiggHNoutW4ftGN2iXLK5r8yOTlJExMTSBtg2QB4/cVfR25cuhmYa9q1735av3ndbQNAFf9d6sfHA3BpZ9XlT/fv3z8hxH/apOZ7XltKEe7exy2gbParDI6Pj/f4zQDQmQFcj1Lw9AAukOD+/kY/ODIAAAAAuGYC8Is+jJQAHpDVwCvzcuo4bUB2A+DXP34zcvPyrcBc0wc+du9tA0AV/59Sv/pUgLLs1f379/+pMADO3rx5M/TOO+8E4sI2btyo9bFvHR8fT/rVAADAC+wOAkjbdm8N0XI4UAjJVxbwQ3Lo4mvvraoYNTU1oSyUoYBQl/5Lly4lTERCVP04QB671xNrbn5grmam2fHLmCqf+/5z//TZYiSoaG2Mo2gBP4NyCpxSWV1J1bVVgbke3XSz/yFg2fXB48ePt3Z1dfFovyGepz4oXLt2jTZt2sRdoLie0ue383vqqad+v6Ki4i9v3LjxwNzcHEYIBnmjlvfzlZWVQ5cvX/579b62HdlWLYl/dv/H5qfnlYU5zP1eFi/uqkqqWVPTruZ9m2wCCPF/cmFhQeG+SvPz85gNIOBw/3+xtKv5f/DSpUujkvBX0s+G+fkwv2S97r+2bnc99f/Z19J/czlkd13/qaH/P9P79Fc+80Tnx9e/MPzDT3qdrrt27eLKiOemCShL+Bk+5KT1qwzKqeO0AdmpqqlKL4ExAMT7Q61Qf0j9WBvALPuIulzkP4LWLY2vx2+z7+zfvz+0cePGMfXPkPo3fehDH6IdO3akBwHUwzMt3by5ujsNj2GC9bG+fv2f/vSn23/4wx/+18nJyf6nnnrqyW9961v/6MgAUBmYm5xT5mbmaWF2AQMAloH4r6qt4nxW6tbXjahftcplQRV7Co/6DuFfHmgVgQ0bNvB8tdwfWB5Mp5fF/yuvvFKU/sEf3P0AzcxNa7UzVvnpz7TYFxW2JU38y+sI/vRP/oz+8q+f/oTHwj9tmqhLmO8j9P8HVuB+rFxW7PbHrays5ApBhFu/1LLXpgrdhI2ymh7gM6jlVJc2nX4ZKCwoVFdXUXVtdXAMgEqEbwN3+PSnP/1bV65c+ad9+/ZVqwvELdZ3df1HH300vbz66qsNTz/99D985jOf6X3uuee+6sQAiLD4n1eXxXmI/6CzsLhAS4uqSKqv5s8QR4BIUQDtU1NTEP9lCM8pumnTppD6kImoD6C4+Dp65swZunr1atHOa2beRtQB19+0oiuZATyIoYf9gLsXFhbCb731FmHEX2AVHqyOxf/ly5dtb8vhvHfddZeiVg7YeNpoUfzzrD/Rs2fPBrqcctps27ZNaWxsHFavOT4+Po6BAN0SzNwFoA4GAAAy+/fvV1QBd7y9vb36kUceSZurd955Z3rqP33d+uLFi4ZiD+tjfSvrc9eXz33uc/S3f/u3/ernr//u7/7uW3YNADwAywytELERoOb5itDPxUWYQOWISb4rLP6LKRBmFmYshfunhb/548vL8OZDxeguAcobrjisX79eUUVuRBW5cQubHCj2ve0VPJVoY2MjPwMitDLCyZSHngwHdZ57pxx56flEbEUlsiZgEQAYwA24wN133z26bdu2+vvvv59u3LhBoVAoLd70daxkMmnYuIL1sb6d9Tkq4A/+4A/oe9/7Hkf0OTMA0g+/Sty8AIAM7F4X1QDgCAAR+s+fS9LzSjOytIqbTyJXQqU6rRIoXZwYt+Vi9vJ18j3Z0NAQtmoACPEfQcm6zQn9F1XVwRoDgMpM/3MXmXJ99hUK7vf//vvv7/v93//9dLfJ++67L929a2Fh5fhqb7zxRjrUWw/Wx/pO1t++fTvPhlH/+c9//q/V//6JfQOAW//R+AsAkGBRXcwX7LQYA0Dfx1+W+qvMAHRhAQDkQaCEbQHTqKYOEQAwAIpfR/ELra2tX6murk4PoN3S0kJ33HHHqvrTr371q3TElp7f+I3fwPpY3/H6jz32GP34xz/+lCMDgGvY6AIAAPATHAEgP5WWhA8gOwBLKypwSyJgQLcSKpMgwCIkn0pw0Muqk7SpqcdsXTkFZHoawOAYAJWVMABKET9FAKjC/yPcX/sDH/gAbd26ddW5JRIJOn/+/KrtwuEw1sf6ea1fV1dHx44d226lnFYbPfzQcAYA8BOz8iCAVjR9hc4VKGLlCiYAsCPCucxUVTlreeYWJ6flNChCwAx9+KQVamEA5IQjANIDCgflHiwzA8Dps8ZvOH32FaS+Mjvb/PDDD/OgrKuMx5deeonOnTu3apuHHnoI62P9vNcX5c/Sy9wgAqCCUF8FWmUUlBd+nPmhdraeRo/kN3NX9XRt0QyAoAsr4O4zlxevDYB8jlkqOGkhrF1Ti0KZS0BWVxXdaHX5Jiyr/AvK+8lv9VWeUln/zPnlL39pKt7uvvturI/1XV3ftgGA8P8yE3w5nHuYADAAik3D9Dr6xfFf5rWPBx980Ns5AKTKVdCFFSh8meEBgHgUYP68LbzUdX7961/TO++8g3JqAR7I1C7V9dUokLkMgJqqQNUby60OjDqe+6xdu/bGpUuXlAceeOD2d9xyy9MCm4k3o5ZerI/17a7PUwhzNwBnBgAiAMqKhSwGgNYaBUDRK5mqODGaF9UqxeofiAgAYLcyrnUDkOGyPzU1RU1NTVRbW0s1NTV069at9CBAbpQvo2NC6KALgKVnXHVloPrNl1udB1M+u48qwH45Pj6+4/HHH88q3j784Q/bEntYH+vnWv+1116jLVu2XHZkAKQHAYToAzAAgI9Ys2YNTc9Ml1yljitXuIeAVfhFbjbjxunTp9P3QXNzc1qsv/jii65V3os9y4dXaWsXDAJoIY1qqn0ZOeb4XVEJA6Bc7u9CsX79+q+roq39U5/6FL3++usIU8f6nq3/z//8z7R58+bvOzIAKln0oRsAgAEAfES+IcrFNAAAsFtmjAas4+845L+hoSH9OT09XfBjlr24hQFg4eGKRiMYADAAZJ5++ukfdXd3n/+bv/mb7ffcc8+q37lLIo/uPjMzs+L7l19+2XB0d6yP9a2sf/z4cbpw4cLiH/3RH/1nRwYAi38YAKDYwgmAVQZAZWkaAEuYVgXYqMTyYibGr1+/Tj/5yU94lF/Xjxt0AwARAAAE1wDwG62trf/+xRdfPFlTU1N59907bn/P4wLwvO7cpUuGIwUuXFg9rzvWx/pW1v/pT39K3/nOd+jxxx//xhNPPJGy8r6DAQAg/kFJlMVSfC6hcgXsitRcrfH6F79b5TToRhUMAABWExTjz2/Pr66urpe//vWv98fj8X4egHTnznvYFEjPDnDr1sSKdc+ePUuXLl0yMhGwPtbPuf4vfvFz+u53v0uPPPLIj7785S//F6tl1HgMABgAgNAFAICgVUoAyg3KqnWqazCDB8CzBjjji1/84lcHBgZ+/corr/yPsbF/ql5cjKSjGevr62+vc+HCBUqlUqvq2tu2bUt395qYWCn2sD7W13jjjTfo5z//GV27do0ikciRL33pS1Fb7zdD0QcDAEjlAZQ9yc2bN4eMHMlSQUyLkkJWAlC+YEYOAICX9PT0fOuFF174/15++eXB11771X88fvyFGre7cIHyhAcBVJcfdXR0/PETTzyRsLu9cRcAiD5AiAAAtzmye/fuXu5/zO5kqdG8rZkd9/jRo0cTHh42sW7duvDk5CRKD/AMnh7Qi21KNW1Ey1scJcVFlgizAAAg3xKr74fU/v37o+pn9Pjx42H1U0EqATfqmWq5SpmUOfsGwPITEKkKYACAZVTh3NfR0dHy2GOPRTk0ifuzec2WLVuosbHR9na8jbqw8D/o8SkPbdq0aZhHaWXjBIBCw63bd911V7pSMD4+blXkDqn3R4SNqiCXUyltkjbSBlhg8sYULcwFZwDJhsY1VLXc",
		"9eO9gGbZ+yi1xUMVbAmkAvAD1UgCAAMAWDABOjs6OoYURWkvxvF5yhOHJNVzj3l9vqrIiO3atWvftm3bohs3bsRggMAS3FWFW6q5r59t4bK8TVJdOm2U01G1nA6q5bR78+bNRTH3vErXqqoqThtbRuDMFEJ1czFxbYJmJoOTTjVratIGgCrU3j9+/Pir6lcfDFJ2qcu/qksT/4cN8qAYf9JzM4m7EgAYAMAFEwAAYQKwcw332rq46lTF1VB9fX07UgNYRRWqTsPyueI7qpa7lM1y2qOW0yPqMdsD3B3AUdpce/saCmQuRZmapKnrU4G5no3NK6Kz/x91+Ut1WRuQy/v7/fv3T6j3wYR6z8e2bNkSZdOv1Luq8XNLivCJ4a4EAAYAyFP8wwAAGh0dHVH14wCVVv81Niz6jx49WpQBANXKCEwT4HtQTo25/NYVJEIOtu7cQvNz84G5nrq1dbf/VsXy2ePHj/+p+uf/rS5bSviyuOV/SL2ef5W+66mqqlJ27NiRNqhL1QRg8S+MS35+deKOBAAGAADAHeHPgn9sfn4+zNONcL92L9m+fTudOnXKUahic3Nz5N57742q19Dm8SCA9IVvf5bTrVddwihFwAPY5Br6xiefjTsop93qsg9ps5LJ61M9hAG7ZJK6//es2VAfxPRJyCaA+vF/Hj9+vFX9XFeKF6Newyv670Q0zMFdu3alB6Vz0u3IT2BsDwDsUaGNHLht99alyWtTVL++jiqrMVVOuSDledvF195LP0CbmpqWWGyxq8rhqKB8uHnzJnFfYJW2S5cuxYUBMKCK/+5XXnll1ZylXvD444/Tiy++SE6nIWxpaaGHH36YxwJo9Vj8j83NzocvjF+kqdQUzc/Oo4CBrJz+lyQ1/8adtKax3tZ267esJ+XORmrcuoH/26kK3Zjdcvr+6Uvq+2CSZiZmApWmazeupU13b7SdNgAAAEBQWRUBsLS4REsLS0gZAIBG9MyZM3T16tWSPPlz587RvffeG+ro6Ah7GAUwMHVzOvzS/zoJ4Q8sc/G1d6lmTTU1bFxja7vLyeVQ9ft/+wO07f6tA6qwH1WFrpVuL93zM/PhxD++TBNXJwKZppw2506+RS0f3kGtD7XYSRsAAACgPAyAhdkFWqzEiNUAlBtZ5hFVWPx7HfrvJmJ0cy9DVdvPvfRWukUVAFtldWqOZmudRV6N//B1NgC4nHNYb9zCJvvO/+pCWQx298Y/v8kGAKdNRF1GUdIAAADAACBKVVRWKAvzi9mEAAgQ6UH+Kiu0Lh9yy2iypqYmND09nZ5WBQMBlgcs8Hm6LK0M6AV0KRsARUC5qoqq6VtIM2CP2ek5qqhy+sy1Xd5CM2oZLZdyeuXcVbqjZVMYBgAAAAAYAMsM1a+r601XBDT9DyMgyOpfXYhq16RHTx28+Np7ckjkkCr8B9gIunXrFlVWVsIECDgLCwvpMR/WrUuPcRS7dOnSCgOAy0Kx57IvtTI4pwq5uck5FC5gi/npear0rqwnF+YWQuVSTrmLIwAAAAADQKAKwL5tu7c2rtlQ3724gC4AZeEBVKYjAGJq3vfI36vib7CpqUlZu3Ztr7rQ/Pw8okKC/iCortYENreM9fjt/HgwynwGpCyKebAEwQGciVRPy00ZlVO8xwAAAADdGAAsBLft3jpUWV0ZQtKUBUk1z5NGP1y6dKmvqakppv4ZYnEIyoKUmu++nAucBTxHopSUAQAAAAAAAICfDQBhArAgTCJpgAgDR1kARWWy/hbt/t8+kN+DbrqGaBZpCQAAAAAAYAAAAIBvma2dpv4/+5rhbxzSq7Xuy3/r1+n7iz+HAQBKmo9++GPUceATpCiZySx40M4vP/0n9Nb5c0ggD1CfLwO0PMNCkDmiPjNjyG0AAIABAAAARWN6bnpZ3Is+vPxvRaZWrin923/zv4vCEEDwPwgCifEEbWtqpg/v/XB6PAw2Av7x+/8A8e8tLP4jAb/GE8hmAACAAQAAAEVldn5mWdzbHcTLyTYA+JDJqQn6ycl/ocYNjbRnzx46f/Ft+l//+D+RMMC3dHR0RNSPQ+oSQmoAAIDn8LheQ0ePHk3CAAAAlBwzCyvnKb8d7r8iFACAYHPh/Xfo5Ku/pC1bt9B/e3YQCQL8LP6HL126FD137hxNTk4iQQAAwGMaGxsj9913X7f6PO48evRoDAYAAKC0DID5mRVTeMn9/rX/m40BAECQODn+Szpz/gxNTkFUAf+K/1OnTkXffPNNJAYAABSJS5cuEZuwe/bsGVafyySbADAAVhNRly51UfLcR1IsHH5xRHwCAJwYAHPTGaEvhH/F8he3hf/t78T3HPqPAAEQRK7fTCERgF/Ff+TChQsQ/wAA4APm5ubo1KlTtHnz5gH1+Tx69OjRFAyA1QyrS9SlfYXEwmZAt7rE1aVffAIA7BgA6TEAxDh/msBnea/r3r9EmWiA214Akg8AALziEMQ/AAD4ywQ4d+6csnv37nb1vzEYACtpd1H8GxERC3fc7EFygxIiuXnz5hCHEhXVANDUvNGYfvrv5f9nHABPm01r1tSg5ADgIxo2NuT1HEAXI0uEUylEqAAAgA8JaX/AAMjQ69FxOBqAuxd0IslBiXBk9+7dvdevX6cLFy4U5QRmF2ZX9fE36/O/okuA+vm9b36PaubqLhw9etTLbjiJ5t3bwhd+dRGlB3hG087N2p9WFVhK2ibQNG5rpLXLBkDc6T4qKytRyCwYANzaBAAAwL/AAJBeWh4eKyoqaIgEAL5HFc59HR0dLY899liUW3a8rtzVztanRbzj7efqLzdMrfsNj5OtP/TQjpHJa5P02g9eRyECnoj/x/6PR9MC9xuffNaq2TWkbtf+8Cc+TKf+4RWam54LbNqE/+BBu2mzCkQAIJ0AACAIz2UYAMWDIwFOkeiLAYDPTYDOjo6OIUVR2j0/+DRRw/Q6p1sn9VOfeIEqMka/8O3Pdu7+dw8Mqwtdv3iDZqdmUZBAVuam56m6tooqKu0JKA5tl1q3D9oop3Eup6GHdgyoizJxbZLYtAoSTtPGCEQAIJ0AAAAGAMiXAVqeHQAzBIBSMAFQVu2ZADFVXI2qf4Ybt21AgoBCk3LSui2X07UZsYy0gbBFOgEAAAwAUAB4LIAxdWmDsAIgkCYAd/WJIyUAyimELdIJAAAADACgmQAnaXk8gEEkBwDB4Avf/izf2zy4aBipATyARfwQh/U7KKfcJW0f0sZeBQrAAAAAABgAIB+4O0CXuvSryyh5PGUZAMB18T+2MLcQvvjGezR1fYrmZueRMCArb8RP0469d1FdY72t7TY0rdeWdu7Tz2H9dsvp5XNXaCI1SdMTM4FK07VKA21sVmynDYStexVNAAAAMACAOSF1GRZLnJa7BVwvwnmkhAmRRJYA4IiBmcnZ8Ks/eI1UcYXUAJa4+Nq7tH7LWlo3Z2/Qy1uXb9GF8Yu08+EQbW65Y4D79Iuw/lx0s/gfP/FvNHl9KpBpymnz3pvvU/OubbR9d7OdtIEB4JCqqiokAgAAwAAADoiIpVhw6DJ3S4ghKwCwTfu7b7xHiwuLVFkF0QDsqMwKx2Xm3Km32QDgVn3udhK3sMk+bvmfvDEV+HLKBsn23c2KeK+OwgAoYEWzEhEAAAAAAwCUIlxR4kiEJGFwKABs3z8cTl1dV01VMACADWrUMlO7psbRttO3bIfvh7hrSk2NWk5rg91qOzs1Rzcu3eSuAGEYAIWlqhIRAAAAAAMAlDK9MAAAcEZtXQ1V1aAyDGyUmfpaql1T65UBkGQTgMuo02OWCnMz+Y/BgZZtpBMAAMAAAOVAhJajATAoIQA24QiAmvoaJASwDLfE1zZ4K8Yrqys9P6bXcDeHvNMJEQDWyjAiAAAAAAYAKHms9icFAMgP2FoYAMAeNXU1npcZjgAIejl1Q7xjdHuL6YQIAAAAgAEAAABlaQDk0Z8blKsB4H2ZqaquCnw5rayCKC1WRRMAAIDP6qdIAgAAKAy19TVU11CHhADWX8p11YZlRrlyB330vsdJUZTb39XV1dGxs/+Trk5fyU8cV1cGvpyiVRoAAACAAQAAAAWlirsAIAIA2Hkpm5SZqS236Ge/",
		"/Bl9aNeH0vOssxHw6+lxullxI+8ylu4CsAZdAAAAAAAYAAAAAByzHM5di4QA1l/KZmVmDdFs6ySdPn2a9uzZQ1N1kzR+7VeulK9ymAWgEtNxAgAAADAAfEyCVo66HxILAKCESLes1uExC2y8lDkCwKzM3El081aKLqcu05s1466VLRbHQS+nS+gBAAAAAMAA8BGj6nKClkfaT2RZL0LLI/IfEp8AAADKiKV752n81svqH0tIDO/poeVpcYNMMt8d3L39bpQUAADwEY2NjTAAfAK38MfUZcjGCzculkFajgjoVZcokhIAAMqIdRD/xeDdi+8mkAq5mZqaoomJCSQEAAD4hJqamhUmAAyA4sAt/j2Un9PO23aqS7+6DNNydAAAAAAAQFENgBs3biAhAADAJ2zatGnF/2EA5Ae3xHfbWD8lhH/MxXNgI6BNnMcAsgQAf1BTW02T16fSfboBsMrMxEy63HjJ/My858csRrrWra3T3sOggCwsLNDc3BwSAgAAfMLi4iIMABc5pi6naLkF3or4Z6FeqBDCQWEG8LkoyBoAikpiY7MSfvvVd2j65jQRBiADFrl2MUUVNfYLzJQq4NdtXie/b6yQ2tC0nt74yWlaWlqiispgFtSZWzNpQ66uIT3TQRylrLDMz8/DAAAAABgAgSZGmf74+Yp/HtivXV326ER8UhgN8Rz7GBXrjsEEAKCo9G9uuWNkemKGLoxfTAurigq4ACA3N969sepFnfPFvrCYFv/3f/TetMD9xieftWo0D21oWt/esuduOnfqbVpS90MBK6da2ux8pNVu2gCHcAQAmwAAAAD881yGAeA+ferSQuYD8uUS/1FhIIQsHIv3M0Tm3Qj4d+5mMIxsAaA4qCJj9Avf/mzn9t3Nw+qSDq+en0WFGGSn+QPbqEFZQ5U19uas59B2qXX7oI1yGudyurnljgF1UWYmZ9Oh8kHCadoAGAAAABAUNmzYAAOgQHRKYl6mJ4v4DwuhbmdKP22bQ+KYSYN12BzgKIJuZAsARTMBYqq44qiccEPjGiQIyP2Cblqfz+YpJ63bcjlloSzEctBIoeUfAABAucKzAMAAKBw9QqBrgj5Oy33zjWCjgAftcxqqH1GXk2QeXcDnwt0JQsgWAIpmAqQIfY4ByikAAAAAfEIlksBV9H39e0zWY2HuxmB9vD339zeLIOhElgAAAAAAAAAAgAFQOBOA+xn2k3HLfIjc7Z+vmQBGZkKc0KoDAAAAAAAAAAAGQMFI0vLAgEYUYpo+3t+AyW9HkB0AAAAAAAAAAGAAeEtELIUgSsb9/WNkfU5oAAAAAAAAAABBNQB4bmrMT+0ZvUXafxxJDwAAAAAAAADliab7EQHgHRymHynwMdpNvj+F5AcAAAAAAACA8gYGgHeEPTiGYnKcOJIfAAAAAAAAAGAAAG9gER7z4DhGBgDGAAAAAAAAAAAAGADAQzqp8K3xIYPvEkh6AAAAAAAAAIABALzlIAQ5AAAAAAAAAAAYAMGHw/Hb1CXp4TEVJDsAAAAAAAAAwAAAxTEBDlJh+ubHDb4LI8kBAAAAAAAAAAYAKA7cDaCtACaAUfeCEJIbAAAAAAAAAMqbaiRBXhxSl0ie+0iSey30LP6NDIU9yCoAAAAAAAAAgAEAnBP12fkMmXzfjqwCAAAAAAAAgPIGXQCCQ1JdYgbfc3RBCMkDAAAAAAAAADAAQDDoMfn+EJIGAAAAAAAAAAAMgGAwqC6jBt/z9H9RJA8AAAAAAAAAABgApU+MzFv/e4UJAAAAAAAAAAAABgAocczEf0RdupE8AAAAAAAAAABgAJQ+ZtP+cav/MJIHAAAAAAAAAAAMgGBgNsL/GGHkfwAAAAAAAAAAMAACxYgk9kPi/2EkCwAAAAAAAAAAmWokQcnDYv8skgEAAAAAAAAAQDYQAQAAAAAAAAAAAMAAAAAAAAAAAAAAAAwAAAAAAAAAAAAAwAAAAAAAAABlQ7KhoQGpAAAAMABK46WFJDAljiQAAAAAQK66lKIoSAUAAPARa9euhQFgwhEkgSExJAEAAAAALHCspaWFampqkBIAAOADmpqaSERmjcIAWE2fuiSQDCvg9OhBMgAAAADAAjFV/KcefvhhpAQAABQZNmPF8zh+9OjRBAwAY9rUZRDJsPwSF+mRQlIAAAAAIBdqBZPrDG3Nzc2pj3/84+mWJwAAAN7D0Vi/93u/x63/LPwPyr9VaH8sLS0hpVYSKeNrjyP7AQAAAOCEjo6OsPoxoNWlJicnaWJiAgkDAAAFhsdhkbphxdSlR5izVFFRAQMAAAAAAAAUzAgIqR8hpAQAAHhOQhP+GjAAAAAAAAAAAACAMgAGAAAAAAAAAAAAAAMAAAAAAAAAAAAAgTQATp8+M4ZkAQAAAAAAAAAASp4jO3e2xvQGQLW0QoSWp30DAAAAAAAAAABAaXKITAZhlQ0A2rmzNY60AgCAnCjqEjb4nudaTSF5AAAAAABAsThz5mzE7LfqLNuFRSXXT6ByDQAoFu3qcoCWo6VCWdZLqktcXY6pyyiSDQAAAAAA+IVsBsCAqOj6zQBogwkAQOCI0nKokpNnQo8H59ZL1ueyDoltosIM6FeXmEfpyKZtd4H2HRPXEyQU8Z5jw3tfljJ2ipZNnVK5fi6DbFgNepSGUY+OVcpwnnTRysihY+K+Qp0GAACALwwAP8IvzjGYAL7NGy8jRlKiYu5X2kWatIiK3wlxznGfn3cuNLG0R1yXW+OGhMh/hiNf5zCtDvVPiIq7PiJJ6xZwQNomJPbBFf/OAue9Ip6P4QLtv1ACuNvCsyPlssCMinxqt1jm5bw/4nPRxunZK9L0UIHLHZe1EXUZwiswKwNkbMxFRF61lfh7AQAAAAwAmABlRlSIHK9pE6LEL2itr10GgiaiE1L9Pjv3XGI/XEBh6dcyPSDlY0qInJiBCNbMC/6NQ/77KBMF0CUZA/zc6qHCRAMUWvwXimGRTlbYI8RsPrSLfA3l8f4JC9E2JPLaL4REekakMsvnelI8b/oKcI8MS8+0UidSoOswE//6e7fYJoD2/uJImCPkXdQSAAAAj5GnAVzaubO1QvptjFa3yCXJ+xDIkEllDd0B/EOfqBB7TSEqtU7RWsJCWe4X/f0UE4LQD2XYqdivKPB9notCRILIwoaEqO8UFWSj55/2rDQypBSxL7mluTPPynWx7je3DTc74l++Z5yYAEb5oJUfzt8TohwlDMql1j2g3aCMcnk4SMVvvZVb/VMijUZ1ZSVB7kUD6POugkob7XryvTeNnmtnLa4bp+LMxGRmXCfJ2+5LAAAAXOTMmbNpjaTq+9tayWgaQCscKYLgMmvZKnQkgFNB4oVAAf5CK4uKJFKGTPI9Spn+5FGxrddGllOxX0iS5I/+1XrxrwkCrSXVTiVdE48HdfsdlsqJk7LWG4B7xon4J2mbTptpZmTOWRE3WrlkMd1DmZDtiJTHJwsgHO0gm/WaWaU9T/rEd8NSGT5IzgenNDNSSpkBqVwNU8YUcoMuB89lr+oL2SLWtLI9LMo7jAAAAAgQpdAFICUq3F6ZAIWo4GgVin4K3iBapUREVGrcrMgokviXW97MiInfByQDYIDyD23OJn4iPhH7EfKmn3/M4X0WNhH/mhBMifNvtyAQFCG2+HOvtB/ZBEg4qOybhVwrVDrh/07FvxMTQG/OEeUXORQXS0RcR0iXL7Ei3VfMIBkPiJkQZfAsZUwpJwI3WzeTiK5MRouYHnY5Is5X0d2bbryrww7ystAGQC7hDyMAAABgAPjGBDhm8jJ10wQoVD9abZTkKPkr7LtcCAmR3S4qqW5WYIalStRBshYinZLEi1YujlDh+p9GfJIPEfKm9TrusPI+YiL+tTwbEuc/oBNQCfHMkI+pDWyXlCr0ehOAj9dq4/z6xHFiBuI3Ip5dQRf/dkwAvfhPknvh+nEhqmWzuJgmgFbmNIMjpUsH2awoxLsxLBkjA+L/e4v4vI+KfLZidGjdCbWyojUCFCsc3y/CH0YAAAAElMqAXIdRK4/TClShW9G4YnKSymtAtWLSJ9K7ECGrIWm/Tgb165FEox/Duvl6BoXI2lsG5UQTSIMmlds+ISji",
		"Bvm4UWcA9JoI1BhlRrMPkfWWaDn0v79E09iO+O8Xacqd1VpN7q0omQ8+qujeCVoreCLH/RwRedJHmZk8zEgJQyGmu8ZIEdO4WzzvIrrnXz7vGyvG+CEh/LX1klScrm/t4nr5XhmxsZ1+OtEIuWNU2TX6C5FmiigHZykzTkS+771hsb8oAQAAKDmqA3QtbkQCHPLoXEPiXPcSugQUigjl3+qViy6pkudkirKUEDqaaAgVsTzEKTPfuZPQdKvH8AK7aajo8rJfCKkBka9yi+pBGwLW7Jr7KRNy3CWOkeuZJbcul+Izw67479PlZ5uJkOV9GkXPyJE5ySzvBa1V9FCWZ0WuLlxyNA9RJrKjWFFe2vsl6dLzz0pUnL57UTHEf67R9vXnqz9PvrfkqSG1SJ988vEY2TOf3XxG5tvib9UIQEQAAADAAChpEyDk4bkqoqKImQzcr5QMkDeDVEXEZz6VxJgk7trJ3bnOzUiIimYhxb5Z5TbuwzLTLlWQNbGvCb1uIezsTtHVZ/BdVAgMFoxadwJFHD+WY19hnbEQVPFPWe6BIbI23Wi77v4/aHJ/RmnlVI/ZntVRsegNIY0eSQQrlP+4HoooH0fyuD9DLuWdk+iBUx6/9+2cp1ZPIIP7ukcqO1buzVyMUmbQVyvl3q26gDwrhBfvXM0I6KRgTAkJAACBpjKA1+RWdwCvznUAxdA1WCgVKtzfLP+YEy4IY/KwzPZQZj56zFCRifxJSZX9UcpMe8f5EsmznJylTH/xsK6yfyDLtlHKhP6nxD7GDBa/Pkec9Pk3E0FJi9vLadFvUsaHaWWUAIn1NIGvLXEDYWX0fknpBH80DwHeLsqLFs7f5zC93BCRUYfbeiUCo2R/3B59X3/91Hey4M+3a5bWTSRXHiXIXXOPr2GIvGtcSJKzbnAAAABgAJSlCRAl62GLwJgIude/0Wnlxw32BCxflny4REzKjyb6UzoRwyZAK+UXmTEgxKAmEuO0cqqxdpNn2Ela2eKtGRFGix/HFHE64F8oy3PdyvM0JN2XfRbOS8tn7pLVQ5kxAPqk/I9ZeL8k8hSPWlTYiG7fvZS9H/9eG8LL6gwIbpvTEXHcEXJnjATFxMSxQo/uOrsN0kgui/neW9ogg3ETg6Bf5KGbYj0l0ruVjCNW3Hz3dRrcIwAAAGAAwASwIBAQCWCfFlGhHCNvu28YVUb9ZCQAe8JE40SB8kWLuNBXkk+YnEc7FWY2klIQ/0TGYf5hi4L6kImQkw2CqG6dthwCWhM5cktu2OQ8+3XHsvps0Fr927O8z8yiAZLiGrLNLqMNgtiXRx7YIU6ZcViWRHnupcxsAW68252WL74HZUNPH6KfpJVRI26MDWRmAgyR8ykpi2kEQPgDAAAMAJgALqAfvRnkJkrehftnE4b5CjWt8nkdWVqUZ4RbQj9b5d+of2/SoAzw/T9SIs+sQoh/LQ1Oin1EyDzsXo/cVSNlIEy0vvmyWLcjvrRuIbJojxjkaUy3Tq5zNmr11wSjfhq7bNEAg2QcDaC1MFvt7tPnwjPtpIlIH7J4/JO0MnJH298wuTOLjn5Axy7d70d05bHUccsIgPAHAAAYADABCnSuJ0WlN4Qi6mu0ivaBPPM8pNtfUKjw4RI3EGByfnbrhMeIB+VHNgBKPRIoX/Ev3xfaeAdWBurTi22j+d+7pf3EyVnLq76vtlF+HZP+3pfjfI1a/fslIX+QVvchtxoNECd7rf7a/dDlUv6ZmSi5xH+vwfZhyn9qPjn/UzozIprl3gzSlL1OjQAIfwAAgAEAE8CD8x0QlcNi9ZU+S4UNTQwCx3SVUyfIA7zFkaRFJ6mrFLs1mnk7rexbHrYpnMpJ/Dtlj4kI18jVPUATifLAiiETkZqU8iucRTxGTES2Wau/kWAfFcLLbjSA3Zkr9CK5EPdWMsc6+wpYNvVd7WK6PMk2jWGpmwDtlBkzIWTDCDAS/iGxnxGy180FAACAT6guo2vNd4rAciMkKpgHRKUUrGaUMnNtD5P9gZyilGn9GwpwOg34oALdZiNPRwtw/C4DMRikGRiKLf7JgoALSb/FDUS5ftyFCJlPATlKmcHjIrrfU+L/YRMD4ayBaMrVHUEbTV4Tcop0XSfJXoh/rnJaKIpV3vukshkVz9oEZUzXiEk+yr9Z6X5iNiDhCcptpue7vZnoP0ArpznV0iBGmW4QvO9BUZ67xLpJ8XtMdz900cqIlXbxfOf74QjBxAYAABgAMAECk2Z9hGgAMzopMwihnbKlVZy0ivFgwMtQpATOM0SFGwegR1dxHqTghBYXU/ynpDzTT+emz1tZ2OmJmuSHNm6A3kA6JhkAe0zOSy7/Cd0+ZVHcaUMcj4rzH9aVJzdaYdupsK25p4pURgaFENby95CU3gmLIj9k4R4wG+8hQqvHhrC7fYLsGZNcNrPNihPNYgToB2qMiH1FspgXUfF7J0wAAADwP5VleM2l1h3AD3QhCUyJUyacWGuNy1W2uHKmhf9qU8PBkCpe/snPhkKRoJVdAFIWRCnEf27x30bWBuOUfztn8Hu2cTwiJvmZTRwmLIpzxUfvon0O0j9pc/1ilZNjJmXB6sCruQwApcDb2302sZC30s+f792ztLJrQFwq91p3mEiWfSQp000A4h8AAEqAUooAiDl8uRiFHyMSwB5a/8gEksKQPvGpTSeVa6qrAzoBE/R07SH/Gm5JnQAalcr8AGVayToLLLiSJZivfhD/iTzzPJ/jZ8OOsBwTgs3KoGz6LgBuEnaQ/mbjJCQM9lfM51xjGb6XtH7++vB+MyNAe9YdI+MuS0b3kb6bAAAAABgArlfUnVTc2sh4Tu0wuTMncTmZAH4sE35pQesja/OUywxReZgqfr5G7bkSEuKqR/wtR3LkE7ocEeXCqB9ve57PNoj/1XkZsiD6+bk/asMUSJrkazbstqZ3i/JgFkKt9REv5LSnIZvv1YQo10Zp0SPeu34grCurcjRAi8NnmL7Pfi7z5JAoE2GL35ttT2R/TAAnRgCEPwAAwAAoabTK4jVkd+A4Iio1A1T8Acj0Fc5slFr3k4jL+1Oo8OH2diJ7tAHdQuJaU+Ic40LIJPIsCxGxcCX+oNhfuyS4ZDEa81lZNqKP/NnyLxsAiq4MyCLeqM9+P5n3ge/PIZZP5DjnuA0BbhQNUMhW/1wGgFF5lO+JlMk2cek+KvZzL0wrp/8bNXlWJ7I8p/XXOUD2zJiQSfqafZ9tvQjZHxPArhEA4Q8AADAAAmECgODmbacwA/ww2rxWOSx1uJLZS4UZvE/rglMo2sheZM8QZQZ06xXbV5hUwhWbhsCgKKNa95B2sX2X7viyuNLSP2QiboncjVySxUWKVo5PkDIQe/pB1fwg/vUiXx/dJQvSdhODQAtpj1gQPIeyCEeS9uHk3aNFA/SI4+Tb6t8n8ivXYINGYftHpDTT0mQwRznsl/YX0eXJaBGeZVr+DYs0TUrl3urUf0kTs4Sv/4SH13JIOu9RB/e5di12jACj+8DJsxAAAAAMAABchStieyn36McgN36Y0s1LkpRp6YyIMjRoUHk+Kf7emGVfith+VKocx8T/tXE0uiVhFNOJC83Q6qNMl5KDYnt5zvc2F69/TBIH2qB62lR1SYNjaUJ8zEMTwEqf/1M6Aa4Xp6NSue6VzBZZAFpJ14hO4I9mEY5OBRLnx0ieaRYW97J2Picp+3SDKRNTYEgyAI4Y/C639A9Sft1ZzLoUuGECxHXn1qu7jqQuj+V0SWY53z4Pn1X7yF5XjZDIu0NSOYhR9ikAswn/sFgvKq1zxOA5BgAAAAYAAJ4xKCojxewWkKsFOteoysUk6kG6paiwY284aXWVQ8B7xfnJ4m2AMt0C9GJfDscNi+25wr1XOhftmsOS8EiRcXi5kZCLU+FMrZROMNgR5F6YAFYH/JPz5oCBMDsilW3Ot2MOyqHW91tjyGAdOTrgWJHu4z6pnA0KoTogvrMSDSBfb1ysP2yyjmasJHSmStjheScNyuE+aZ9O74OkrpxHdWWDdOXHqFwZ5fU+D/PVappGhVAPZ3nGmxkB+yRRLxsiRhFhIfG99szsJ4yrBAAAMAAAKALF7hZQymMAeDHl",
		"o9WWVi9JisrrgCTytFlCwpRpAe3U5bNW8R2VxIImYLp1IlQ/cFg/mbeajUoCrpdWtla6XcE+Jl3fiMFvxTQB7Iz2n5DSXht7Ia5LN03kaNdqZyYBhVZGSyRpdaQI0cqQ/WKEvGuRIklaOahgXJSjbrHOXt21G7W+a/uJic9ek/IT1t3TkTyec7Esv4VEvuVb3kZ0ZSyWJQ9P5DifkA+f46PSuVkZ+V82AsiC8Dd6fh6B+AcAgNKgEkkAAkxcVHJ7yNtxIAYoM3+y0VJoQyJCmfnm7VZOw2VcXgYlIRCWxJ7Wwt9J1sJctVbQfTqhIOd9zEQ8ymK230QQ97h83TET0ZXIcY52BXohxb+G3JJrZGb1S/vTBH23xXtK7oLB53bQ4LkSpZX9w5NFKMdhqRzGdempv37KYVboW8LbTMTmXl1aHDIRifmSFMcazGMfw7rnXKfu3CO65+YolR7agH+tlHt6SS6zZ0W6hKQ00N5XkRz50SmOE0OVAwAASgNEAIByEnYDFOyxAfrI/sjORhU6q6aBVVOlWIMzJhyI5R7KTBEaFqKvU4g9q4zqRIV+FHer59UnRJc28NcxUY4LYWbx+Z4QpoUi/rZ6rEJEAjg1Fgale6CdVkcB6M9VEeWTt9Gm5YxLQjos0j9iYMIYjRo/YGJG6MuYm+OUDJqk0witnFEg12wCCYP7P0r2pyuNkHE3IjdNoh5RRp3MjiCX0ZiBwNdH2ySpdHEyBWDCwn2cJMwIAAAAMAAAKIGKUKdHxyrGGABuDdx3hIzDfM2ErtUKd6SEykkbZeZcV4SQihuIPi0ywChMPkaZVrRIFnMgF3HyLqw2lkeF3k0TIJ+ogpQQrL3SfaFvndb2PyLlTYiszd7BwuegybnJBmMiS1oOinIwnOd9kaSVIf5GaDMKaFNP5qKfVvf1l7vDWKHX5FzdjhLRBtq02yVAK6eakaA3LyK69AjK+8+qERCG8AcAgGCDLgAAlD5Rcm/gvkGy3t+6J6DpqYV39+uEwUmxdItKsrZeTFd51vpYjxmIiYMU3GlJ3egO4MY+5JHozYS9dhyr3Tq08Pm9Juemvwdz3RtJcXyn3ZMGxbnELawbIutTCcbIeDq8s5SZIlEr04r0/4go92dNTI1CCekk2e8SoOW93tTQD/AYp+D1abfTNUCfzgj1BwCAgIAIAFDqlRk/Mubx8Q4UQMRpg4WZiQQ7wqWtRMsXV5RHaeXc8FpYuJxeWsisWYtanIxDxoNsAjiJBHBrPAEt2mdMEudExhFAMbFoAz3u0eXjCVo5ywOZiP9hndi1KhztRgNoQiye4/rz6V5glH/ajBfdDvYX90A02u0SYPTsGqCV3R/6fX6fuWEE5IoISBJa/AEAAAYAACaV2BbydjTkJColKyrnblcue0TFLyIJgSSVfp9Yu2gzFnA6HKJMtwA57SMmacjCrhxHxnZiArg9mGCcVk5dl80E0PLZybH14j9O9ueFT4prZyGWbWwAuT9/Nlop04Ulm0ESz5EXI5R/1x0+xkGPyp2+S0DKZj5GdWmd7b4douJ1a9KeLW7ty8gIgPAHAIAAU6H9cfr0maWdO1srpN+M+in3O6jc+IUlg+/0fbWXUCRMydWvHWTul1wRADEhDJMuiWm7/f83UnDD0L3KZ63FXx7p/wRlIgJwr2RG2c9lAhRyJgH9vZEQgjTpwrUNGOy7Lc97K0SrowGSlLvV3wijQf/sjkERJfP55HOZGsUUkBEbz9corTRxrOajNraJ15E9iQI+vxVxXXh+AQBAiXPmzNm0Zlf1/W3tXlGxLPURAQCAe1itNJ1zuYJ1xIYBEIP4dyWfUUHOjZVIgEKKfxJil++3Xkm0nRXidNDhvRAV+wvpyoQb4zskaWU0QIzs9dUmndiPS4ZCJ9lvOY5RposE72MPZeaWl6dE1PLvhE/uj3geZdaqQZKg4HXrSeHZBgAAwQcGAADuk6vPe7IAlV053DlbhbUH2QN8YgIUWvxr9IljyK3hvZLAPmZBGGvTAbbT6q5OgwW4rwYpv7nu5TR2IwQ/iGJXI0aZrgMHqTzG6gAAAAADAADgsiAvViW2l1b3/WXD4QiVbvcdEDwTwCvxr6G1huvD9qPS/7XQ6hPi/9qAgGYDPGqGWhxZXPJwXrYiGQAAAMAAAMA7tBDTfVJlO0SZ1nIro3GjEptp7dNESyH7ixayHGihxkZi8hRlBvwCpWcChDwW//I5cKQMm2GHaHW3Gc2ciFi4z3gQuBiyFQAAAAAwAACwB1fCe8l8BoGQrlKeEpVvp/13y8kMsCK2Oe1PkDvhxk5RKDPYWMjC+u3ivFNChHF5SHpwniFRDvlzX5b1TlB5zphg1QRQipwuccpMzchl6YC4F0I5tuF89bvxpM1KAaPUf0RopSGrPffY7CzH2UIAAADAAABlBld+nEwzpQjxx2LRyaBWYJk+ygyMpomgziIIsz4yn4PaSlnQ5ia3OkWaE9HP6XOIrI+ELpfphKjcj3qQtnx+Aw6FeSd5Y6ilyD/GnWYgxUzyjqi0ImjkWRc6CREKfsqXs+JTm2I1Riu7o/DnXkJUEwAAABgAIKCwqDpJ+c1frxkIqOjaF4nDBmI2IvJEGx29WOfhlG5RiXbLFDKa5s3pdWrCPCYq/4USlE7SU2uVRzTNMvESFpnyGAvagKB4NhafqPSu054ro7Q64qRLPH/ZmD1HiHIDAABQICqRBKAIjOQp/vWiJ+JRJY7Pm1tyronKdreL1+EFfULkh3OI3jGyFoqfT1pamR/eiQgaEfmSr5lw1gXxb3TdZ104P7Nzdir+0epY2igm99NwAcowyJ0X2jN0QPxfMVjH6F4NUcZ01GapAAAAAFwHEQCgGCLUbeHHlaa9HleuI2LhVhu/Tx1lt7U9QoWLBohS7ukKSRyXB/tL6vJinzi/cI7ywP1qOx1W3gspmhTp/NyKBgg5EAuFEv9j0t9tLpRbrUsDprC093ySTQAmhqTyBPn5ob0jhkzWPUErzetjuvs4jOQEAAAAAwAEgUMFErjcT7sQ4wHkaqkOiXVayZ/hmn3krCVJE6pujg3QbkH8j0pCLymJ2yHxtyIqynxOXVnEelQYCIM2rrcQUQmU5fzC5E74vdbSWGzxT+RuNI7iwv7GyJsIIY0KH4l/qybASXF/jeZZFrV7VRvQbljcgzGH+43afF8cy3G/a+cXsri/JNkfnC9q8G4KiTTQfktQZiBKZp/4blD83S7dpwAAAAAMAFDSRCxWvuKi4pUk4+m6jDhQAAPAali1JpY78zxen6gouiG23epjHyF3ogFCFsR/Qlz7sFj/IGWmM+ySTIAWsa42pduwSbkakCrbuXBzPAK7eXQwT1Ol3Sfi348kCeQyAbRyqPVNH7JZPjRhrT2nj0jfRykz/oVVMe3UjIuI94WRqRYla5FHRoK+J89n3z5xTkOUmZpVfubLdEpp0I9iCwAAoBBgDADgtQGQi5ioLMVEZZErRFbC+wsh3uy0PkXzPJYmct3o99lH2fv6Ozm3fMcGGKbsrdSDomLcTRmjaEDkwZAkSni9c9J5xCn76Nm5jkvimO1FuifayfmYAFq++En8t4mFRdOSWMZsPiPk7eT9OeGch3kZ9+g4iij/dvMz15gA2rR0J8WSa4yTkNinlfEyoiI/z+bYb76ROGGxveKC+New0y0okeO3OGVv2effDhLG5gAAAAADAJQJSTJuRdeEn9cGgJMWKKdEpQp4JI/zPUmFGzwqIgkDuyI3YuHcWVD0644XocyAWloFuY9WtuxmE0KhHOerUPEH2+olZ4NJ2gln9qrlPy6WhA/3x910KrIsZnRm2Wajx0JNE8iawee2CSDfj3zPXaPVA63aEf5G96PZfomcDWZpdO69UnoNuJDuAxbvNaNW+xMmz/sRkZdj5N1gtgAAAAC6AABP2WOhsm/GMSrM6Ol+oUsn7OIO9qHNMV0oYZdP5TkbbO4MUabPf6PIa65M75PyXy8UYpRpTdOE0Ekynl7LbEotP8zkoIjz6LMpcrptlAuvWhQj0vnJ1xexcV1G+0vlef5a9xInJHOk7THypvuIvnV8TMrXNrLecj4strGanlGxtInnwFkL52ln",
		"v/2i7Cu652A+dItnStSl+1szCnN18+IuFAfFumHxjBrUle8REzMhKtL3IKH/PwAAABgAICDkqoArLlQq3SRl87hOBUpUVyFk0eNkUMMk+a/Pc4Syt5wN6kyLpPh/j8l+klLenBRpfkz8Nioq6GMGZSdKxlEkh3ySTodsGgDDNsqwl+HEYyaifizP/cUpv1kFSl1QGYXGKw5NgFiBy0OYnI3H0m7wvE2R+Sj6+vsnZLC/QyYi/VSO/bXQ6uiGdrI2zsuoyfUbdU8wel5qeQoTAAAAAAwAUPLkqnRFROUo5UCoxQtwvqNkr++n0wqbUQj6gIVK9JKP8rbNJA8O5RAiVge60gS/JnZiwgzQpgbsFumojSUQNjgPvQEQIudjGrhNSGdwZMNqmHS5DfiXjWQB9x2nwnUj4TKhzXahZDEGrJoAMcp/sNJCsc+g/FqdXWWQVkf/GJkCWrSB1ffVgC6tw3ncT1bGI9GMggEf5xMAAIASB2MAAC/JJWi1yqxiIHhyDdJ2rADn21+gdWXaTURoiILR5aE9S1noJOumSUKkca9OeGmjlstlxaxSHTJIYz8RsriOFbEJ8Z8RvG1U2BHVNeHd42I56BaCNtegefJzM9eYAH4W/2Qi1lM5hDKnDxuh1wy2NzJBeikzyKSVrklJl54ZdmcZifrw+QQAAAAGAAC2SVkwAbRKHVeY+kQl2MogTqMFON+kxQpzLI/jZ+vz6nRwOL8QNjn/lEMhMkjGfd+7LFbSIwG4hwYslokUZWZuMFtGSrx8Wb2H41TYCIAUuTdQYVQ8/wZsCsZcJoDfxb8RudJzJE+R3E25TdakBVPBynMw6mC7CAEAAAAFAF0AgNdwa22u1nzFZoUpVsAKvrZvo7nm+fuePMR/JEclz8ngcH7CrHI+Ss67S/SIir8muIwq8YrN8ykV2sn6dIWhHNeriUT0M/YPYcpvujqz7gAJCl44ecSl+/kA5Z5hxo371s3nJwAAAAADAJQUccqM9u4WRzw451Za2aKd76jkTJfFdTQTwui8/ELKRNAYcSqP47B5sJcy0RERG9vqZ6FI+uzeSOYQdwMu5pVXUwJaMSPMtlPIm9H1/UCInA+UmM0E2ItXji+fjQAAAAAMAFBWcN/OYZf2FfdQCLspmLjCb6VlKNv0U20lmv8JF7Zn0+eAEDgnbYgjveC2O9NDIUVCNgOgl9wxzbwcG0Arn31kb5A8bbuIS6K4FMjWHSMhnnFhsmZ4aSbAXvKfyVWOsGk5gGQAAAAAAwCUMzEXBU1/iaaBHUEUFddpVpnX97U3ik6IGIjfpE40hA2Eh9x6FTLIs7iDa3dDcGtTbbW7sJ+oT0RCNo5R7oEuOW+GfSL+gXX6yDzSoVM8L+V73Urf99GAi/84uRNJdsyDc0269KwCAAAAYACAksaNKIA4+SsM3iohB6IzlKVCP6AT+HFaHR0wZpD+fTphoV9HP7Ufn7PeuKhwcP1d5N6gjV0ulMOoT+6HXGU9F8US/1600svl84hOFJcyITI3A/sNrpPz7yBlj3qJUTD6/OcyCjkd8hkIkNNp0EL+6NPfCT0wAAAAAPgFzAIAikWM8m+h8mvrfztl77scLZM8Nuv7GqHMLA8s6q6JNLMbGdBN9sYAMKq8J6nwg4DlYtCFeyGUpVwVuuU/QrkHtHRDDGrHCAXoHunN8Yw0K8eJgIt/5oCF+5nHZqkQS8zg3jZ6Z2jr50qnbjIe+NUJSQqOaQUAAKDEQQQAKCbaiO5O4BbkuM+uJ0qZrg1moouFTFeZ5G8iR1rJjIjyYFWMs8Fit1/t9SzlMELFGXAuQe4YWb1FEv/AOSHKbgZmE5spk/U7S/x5EdE9I05ZfCZEDdIyTqsNI75PWtTlXI79tRjsL9+BX/0SbQQAAAAGAABFY1SqpDkxD/wCn79+mkD9aNwa3RT8udetGABG2EkXJ91H4ll+06ZMC3ucPm5MxWcmJAsd9p/rvl1yuO9c2/VSxvDQd2UpJXIZge1k3FXGbHaE/hJ/Xpyg1VN6DpDzAfSOiXug28AscPq+yodkHu87AAAAwDXQBQAUGyeV1hj5Y4ArroiPCDEUMvldLyoPlVHe2m0xO2TRBIg6EOqpHAaA1y3lbol/IuPWf7T8+59ojvJhVl4HDO6TFJV+iLmbAxcmxf76yb1p+NwwWOxMWRvHLQIAAAAGAAgicZsVV67M+aH1nwUoD8SVa2An2QSIUrD6L7td4Q2RtQHlnFToRy3ul0VzoccEGHRR/IfIOFQZ4t/fZBvzQjaHtOdGRGwzYmIcjAYkXXpc3o9b74secsecgKgHAAAAAwAAstdKM0TutejkI/7HbIh5zQToLcO8jTlI26gLYt6pEaEJhkKYTHEh7HpcLMO9PhD/fDxtYLVCEZeOEQQRFbYo/vm5MSw+R8jccDwWkOcF39v5GnAx3TOC/5/P2Aj95J4pmCQYcwAAAGAAgBIhWeB9D1lcr8/Da45IlW9euikzD7fdfvwKlV/rvyZI7ZoA+yykpSyYrIhHu6LxgItpEBOirs1l8crlKVpk8Q+csc+i+Fcs3mOjAUobzYCza5KlhFjvNLkH95L17mNJkaZtBXjnxF1eDwAAALAFBgFcCb/wMVevcWUoWeBjcAvLoRwi2cvQ/yitHmgugqLgiH6yN83fuRyiV5s54iBZm0XCbt/dcB55rd0rLOZOiEp8oSJWeiH+S5aQi+K/LYDpMyjEejtZM041wZ7tXkuQP2ZJMBrsEAAAAIABUCSGYAAUTXhrrTdmo7vHybtWLidTzIHslfN+G2l6SAgAo8r8SSGM4mRtIMBBst+Slmt09oR4VuQSHIUWkFGfi/98uwREyNqYEKVGWCdqnYp/NweS9CNBGNjQLN+sPDMBAAAAXxgALRTsVlAWCp3kbIqxoDLoofCOCfFnVMa8arlRbFTAgb1yxGHPVgy2kMiDvQbCSZHyKdeYCgmy3/ovC2uj8nmE/BGa2+tz8Q/Mxf+YC+J/kNwd4d4OSSrP7kxuph8MAAAAACVjAETJ+Ry6pUJMvHxzhaOXQyWlGGKHow1OGlR2vagQQfwXlk5xT1lpued1hmml8TOi+z0bLIwOOhBIRoPqDZF/pp4kypgUxRT/CV0aacSle6lPepbEbF4b0yLtL2Fy7KRH6e3WfuTnixPxnxT3hJvP5UGR5lafe9kMAD4vzTA+JtaDWWCcThEkAwAAgFIwAMrp5RxHMhSFhKiQdkviot+jYw+Q/fnli0lEElsyioXKpT6aJ2wiwvXbmJ1DwoLY1gTrmMV0jkriwY6Q0I5jVxwqkvhMSMLfb/RS8Vv+zboFtUnlYkx6ntoxAGQTpsLGsfNB8cAAiOYh/jUjqq9Aedkjzu+QQ2EaF8/puM5Y4KVd7Bfd6wSzs7NUW1uLhAAAAAADAABBv1RZdnPKtGz0UelFt5j1jw5T7r7TUQvXO2DjHKyOcK8J1wGL6W1XjOTTL7qb/BXmbyZG2wlh/27jhfGXciD+vRxvIiYWLmNdZC0qwEj46xkVS0gyGULlXNgWFhZOGD3bFhcXaWZmJv0OXLNmDe5KAAAAnhsA5VC5TKEI+DZf+kVFMeax8aC/B/xSRhIBy18OY+YQ4WFyp8uFGy2kfSWQdl0lIv6T0v20hzJGEZ+3UQu+9rtC3kX8yBzK8dugC88CfpbtE2XfSPwnKTODxCkhqpNFyrtcUQFaPsZt7rdPLGUdFaCK+77Z2dl9tbW1kampqfR3HBVw7VqKTYDYzp2tcQIAAAAKxO3wytOnzyypL50KJAnwEWFCK2c2lnx0Lk7nuGfx0y2ErVMjICZEY7IM8jxUgtfJgk8L64+T8bR1S0bvpQKjdUWxU+60qeTyfS7pxb/fR/QPSSLezeeyvN+y48yZs1H144AoB5wGRyD+AQAAuPSO4foXqe+VvtsVrIrlKha6AAA/A/EffFJCIGp9hbkyHLEgyjik+IQQ/+UUyZNEkXGNiEPh7kbEynAJiX99uUugPLuDWimLUTCnOgQAAOBjYAAAULr0++hc8q3Ia3N+a5XhEBn3E04RjKFSI26hnBSjLLfZLE9amUy4dOywQfoAAAAAABQUdAEAAAAAAAAAAAACguUu",
		"AOqKY0guAAAAAAAAAACgZAnR8sxWq5ANgDakEwAAAAAAAAAAUPIkkQQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQMmCUf8BAAAAAAAAOfnyl78cEn8mDX4Oi+9Tuu+yTZ+qSNslTdYJi/X0U7dGpHNJ2rgMK8c0IkL5TUdsdFzt2oy+i2fZV7Z1QpSZtjblUdGIUGlPa6uQs6l+jcq8b/irv/orw+8r8SgDAAAAAAAAWBQ8IyYC6qTuu251Gciyr3Z1OasuvWLbXpP1eB9jYpHPQ/vukINrcLLdWI7rcbKPAYNzsXKcAV16yBwSv4U9LBMDASjXTq5hwMN0dg0YAAAAAAAAAAArjFKmhVkmKn5LCTNgJIugl8VTm1hahWEQMlk3SZkWdCZCxq33IfFb2ETkmYk1RWwXspAG2rqKzbRLiXOOSN9FxPcR6fx5vwndeUey7NfKeYdtXJ8+LSM51jtApdf6b1ZGsuWtkzTUb6s4PK9IlrIrl2tLZRMGAAAAAAAAAMAqMXXp0n3Hrc5HJDOABWxnDnFJktBNCQMhksUAkMXzPgPRyQYCRxRw6/dJWtmiOyy+03/PtEvbnaXsLcEh3bqa8DpLKyMgeB9LBmIxTplwc+1a5OvW9ndCfGrXoj+ehvxb1OScR3TrtVs4517pOrVzMBOVvL9juu+uSev36o5zUpyr/J0c9aCI7fURJEvSubfTykiUsIX9yfk3IMrEmHSe2m+9uvTUoluGpd/aDdJAPp+oWF9L1xFp25CJiL8m1hmRtg1L5zuiO98l8Z0WDdJNmUias9mMChgAAAAAAAAAAKsM6cSm1h99VPx/UF36KXu/6BCtbsHn/7dk2SYuhD8JwXxC9ztv20fLY5wlhCDS1o2K86swOO6wWH+jOPduMm9t5fPmiIW94poHJBEflkRXu9in/linpDTbJ9JoSDrPPZIx0i2+O0jLERIKrY6qOCLOOynORTE435TYx0bxXZeFc+4TnxXCyEmaCErNzNCbMaOSSI6I9bR1FWEiKdI+ZUOkXWyv30dSyv8DOtMhYWF/mhgfEvm3V6RNVJe32jKgO/Ze8f1BWm2AaSZOyOD8uqVt+03SsVf8ppWtsGTEaOfbqjtfLf95mx6xrnYcTt9DMAAAAAAAAAAA+ZIUS7skKEc9OO4pyoRC68PkSRLS+v7v+3S/D0m/RSTR3CX9fSCLCZEQS1wSmUOS2NTE25DJ9iSEfkTaX4pWhvonpHPYI8Rcila3PA+K7zVBHTbIqyMiDcZM0svonBPi/9ckMWs0QF47GYf/n5DSPSS2jYhlVEqLiJQOmjmwTxwvKW2/j1ZGSkQMylyu/Wnn2yjEcq9IuwO6vCUpj7Xj9Ihtew3Ev970UHTpwp9a5EncJL3aRV6SOKe90j02qMuzA7pjavksD/qYdVBCGAAAAAAAAAAAOwxRpoWx3UTsZiNFq1ur+f/Xs2wTF+t00erR+LUw7W6dkHNibvTR6ugCK9slhNiM6MSZTEISsGHpOPK2cZNjxMS52SEihH+EMl00rJxzmxCemggdJuOuEbK4NhLD2vVohsAB6ZqPif/vE99pAl4Wz/J+hijTsp8yELlW9kcmBkk22kXZOqQzccjg+Ick00A7P44Y0Fr+sw126RkwAAAAAAAAAAB20Fpje8k41P3/Z+9O4H+Z6sfxz+Xat2tXdiIUUUTK1qKSilIqir4t0ibtiqJNWmlBiyRFpCyRLJV9TZbKUsmaJdvFde0+/zn/z2t+99xj5r187krP5+NxHp/Pe2be857lzJlzzpxzpp/mCfOEorB6Rp/vTOwo0DWtApruB/l6L88Kq/nfqqgo2CcKcfdW/V9J2Dxtz79/WGzbTkUBsK0io3yN3xlZIfyMYtvOjG27N9uX/Jjlfy9rKaAnu3dUSLRt80pR2G+eRC+a7Xtb4bjtnE2M6btlhfF1q6mf3B+XTWsqCXaL/ydm27dZNaXLyBkR5w7riJP91ndZdjz3KY7nulm8yc9vWsc7s4L8vT2uiZXiWDaVIivF9v40vr9t1T7OxWXF9EOrKV0y8umvr8ZeuaUCAAAAGJNm0L6PVP2foObyp5+psN48Ef1T9eSn+l2F5wnVk5/QN5UDzUBoeUHuuJi/dzVlsLR8P/aPQlYzUF6/J7SXZr+xTzb9p1lB8vgB9mFiUcifUFRYHBDLNIP4fbuovMjnbV5N6Q6QOzMrUDbHeEKfbb4+ltk729dme8rKkOt7VJYcnxViL4vlj+uoDLk+qwQp+/avWxynvBJh86KA3G99+1RTBs5rBgLMt785/5dmx7OpdPh8NWUgwKpHJUBeKXJ9bMOx2Tqa7dm5mjIeQL5dh2brKKfvXA3f2uZJ5pR+AQAA/WyyySb5x1RQfSgqAB7q+Mq9RaF+86xQmv7eUIdl4v/dO9YxLn4rref2KFQdlRV203evjmlpO06pwx4xPy1/W8xr/t815p0Z6zol/m++u3uPQu1+sS3XR+Hs99m8h6opYwq8tcdhvDfbpsuygmJTgG32I23jD6opLRIOyAp/42Jbf5Cdg/2yedfHPjVPvJvBBpt1N+eua5uPimWaSordqyc/6V+jDhfGse+qJJoY66ri+B8f+54fiwvjN5rpZXy6N/b1+ljmhuy4r1Qcv37ra+LJGjFt1+wcXBPzVopjdVgWvx6OY3R5xK2mEmpcNXXf+3Gx7v2KY5laUcwb5+uXRQXKxGK70v69s8f021oqeMprLW3HDeecc871XRcUAABAT3vssYeD0G6lKNClp7U/rXq/AtE2P30dG5UcP50dNmbfffdtna4LAAAAwNjtFIW/M6qpuwXY5v8NK9VhpJryikMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgNnBuPzDyMjIjPiNlepwWR0mzML9XLMOV2Wf16jD1U4/8JRMuMeNm5FpNtPfinHPeTj+v3eA72xWhxPq8GgdlnAI4emVfgPMKnMMWIBPucx7xrD+VevwzTosUIf96jDfDNyXtJ2TWqa/ug77Z5/TNhwelQIAMMPz/HV4vBqtCL93wO+cWYfn1WHe6bQNW9fhhjHch7vurdN6v544hu+9sw431uEvs2j7B1nXjDhezJ4WqcMBdVioxzJr1+EzdZjT4QJm1wqArhvX3R036xXqcEr8f2odli/mp6cXl9RhwzpsXIevFfM/ExULt9Rh+z7bulsd7oqb/8sG3L8FI3HeKZv2YB0+XIefzIY37y/U4f0tN4/L6/BAHf5QhyWL+YvX4ZN1+Gsx/flx7NO+pBYY67X83ovr8Lc6TI5ln9tj2/bucVxOiXVMinByx3Lb1OHSOlxcTD81++6kWNfDxTLpnF8Vx+GcOjyrmJ8yylfU4f46/KoO88/iaytdG2fE9l5Zh406ltu8Dr+Pa+y+OD4f7JNZOKsOB/aIvyPZcUzH5AUdBZJ0/d0Ux+zcOqzbY133xTKb9FgmD+sNsMwKxbrmjv26K9Kbo+uwaJ9rsyxI9Lt+y/nl53ERf35TTd1CapD1pn3cq2XeUS3bmJZ9yQAFol3q8K84R+k63qrH8b8/1nFcHZ4xjeuaFGnzcS3p+nPq8MeIE3fU4eBqtJK30Xz/gZbzPsy5PLIarUAu71m31uF12bR963BQ9vmFdXioKDinp+9bZp9fE9dc/mT9s3G9jC9+88+RxuZ+VofDWva5CY9Egb+fFN93HzJtWTqO7VJDfu/EOvyyZV+eKuaP8/y2uL9NL0tE/CgrRlaJ9JjhTIh7y/+CIyMNvL9H2pbyLWtFOgUw+xkZGVmpDpNSs9IspGmX1+H8YnoKb6vDZ+swvg5/LeYtU4eH6zAuPr+iDtdn85eowyN1WLYOL6vDTTH9q3WYr1jXArGuterwvDpc0rItbdv+kTp8p2XZFM6qw0uLadvXYc1Yz0KxXW2/M7FjndMarqrD4sW0c2M/5qzDD+vw3WzeM+pwex2ObNn3K2P/0vHfpw4XFfPT+m6pw+timT3qcHbHdj27Dne0/EYT0rlft8++pfN/Qx02GeA4vLcOP88+p/j13zg/c9Thy3X4Y/GdFEffV4e563BsHb40g87RoOEXddg/tvdDdfhLyzLvr8M/6rB1HeaK8/D8OpwS36864t89cTzm6nMdpPXt3nHtfrIO58X1l7bx3XW4tQ7z91jXlrHMun2uu0GuzbawXx1OrsMikQYcWofD+qynvB77/VY5v/y8bx3+XByHQdf7eFx3+fSUjtzfso0jcU2O65GuvDPWt0Z8fnEc/xf1SLPnizTvxGJd74p1rZmt6z9pXT32Ma3r23U4tUg3bqzD2yPeLFiHn9Thx0OmlYOcy9cV94wUNqvDXXGdN9PS9XNp9jndkx7L0u8JdXi0DgsX6zoh2+7lY3va0qdX1eG27L60Sh0m12Hljn1L6dVldThggPjz4ohvw1w7n4x0/xMzKS0b9Poddp3D3kdXrMMDs3j7p2d691QJc8wG8WV2DBMinZlvgP1/fpbHVdgAnhIVAG1hlVju0cgIPRj/35Yts2BMe2F8njfLyFZR0E0VAMtFQTVlKl9Zh2+0/N6Ssa75oxLg3AET6HOj4Nk27+N1+H72OW3f4XW4OTLyN0QBbmZVAGxUh98W0+aLbVkgPm9Yh79n8+eJ41yet0Xr8KPs8+qRaS4LJnkGMp2buzu27YwoSHbFjbuiQqfX/v0pMuqDHIu/xfEoK5PyColbi8qkRyPjnT6/JNbRzF+4qNxYuEdlx0uLyoWJLaGZ98eWSqQmPCfOQ3Nsy+P/vCiALdPy3bmiANF2vD4bhZYUt18/QObr2VFYKJdLlT8vKKZdFIWdXhmZ3epwxAzKEN9Zh7Wzz0tFZdDMqgDYOTJpzxzDPjTzU2XLetn0naJCp9zGVJC5uA479khXrqnDFsW0D9Th133S7LZzfm3LunapwzF99nGNIl1fJq61vPJphTocOAMqAOaO62b9bNp3oyI0/95icS+ZP0uvUiXgV+LzllFBWG7DynEeUrp6VKT/Xef37Ij7VaStB/ZYNqWr/87S7V7xJ1UAXRfnbNDjdFXs05XT6d6TrrkL4l7+9zge5TakeT+rw311OCeuzaqojD4lKrv+0XHfXSvS5YlxrCcWad6BUbl5c1yLVRHHHoiKs3Q8PlrMf25se1rnQR3X29cjPt0SeY1+56Yrjk7K7rNXx3XUL425M9LteyKN2SYquZvPryiWv6PH9jb5q8NiP9O1/oWsMrFZR7pufxnnJJ2zpYt1rJMdsx+0HLP0vd8X99rmHnlVHNM/FxXCLy/O0wp9jkv+m0cU5/XoOnw4+/yTbP5SkQ4tll1zebqQKrSviMqLeSM/98Zs/slF/uecIs7dFts6KfIej3VUSA0Tb+5XAQA81SsAmnBaZAhTJnbPlvlfisqBg6IQ2lYIvy2e8uwQhcQFO37r5HjS/Y+WDEpbmDMS7iV6FPTanrycEJnl3afjk4tBQsrYvqWYtlzxxGPlyEgMWzhJN7Zf95g/PjLLR7TMe2dUTHT9xjxxs78sjsvvWwpQc8W5ODwyNOfGvnW1FLi4JZOcnqBvFzf0vSMzUBWZgbmyCqq7hjz+W0fh7eYoZA/ynd0iPp7fp3IjXQfHFdOOzDIzK8c67siuo/d2nI+ropC+e1F463pq/7k6/KajQm2OMRTcn1c8lZ1eFQDNORw35HqmVwXA5lEBtu4Y96GZ/6GiEvPUqARo28ZNouJzvpb9WDQq/8a3ZNpv6JFmzxstKU4pCsht61o7MsZd+7hwFHbLeHZmxOcXTMNT3kHOZRWZ+q9m8fk/ca7arovNotCd0sgN6nBhzNurR4H9c3EMJnZUxjVh0/jtZ8Wyz+xYbuXYr5cNEX++HAW4QY7TJtF6ramUeMl0uPdcGYXYcVEouqRlG0aiRcb4aJ10ULHMSbEfc0RF050trWjOjLR7jkj78nP9hbjHLxCVp6lgvNoQx/DcWHfah491tLjZNeb/X7GPY6kAmDvyK98eMI15IrtHfDi2Z4esIu7SIba3invp4XGMl4r9363lN18W2/rrKOTn6zg/O2cf6DhmW3dUHu+atRy8dMDz1K8C4A1Z5fv4iAPLZvN3iIq9KlogPZTlmVJ69OYiz3BRpL2fKtLDFN4T8bGKFmcPtbS+bPKR58VxKuetWod7B4w3y+d5uSz9bior7oh0dt4sTXibUgkwu1YANM3+v1WHrXoU6E6KAuA2Pda1d9wAuuZ/PrspDrJtzZOqrvlrRDPqfNq2UYBdJjLmz2h5EnxfbMfE6VgRMD4qHeYf8oY5SMZo+cjgrtkx/7Nx",
		"87s7arSr4sn6DTG9VwXA7nHM5o8naWVhd9k4Zh+KG+rXOgq3TUZyp46nVA/Ek77r46ZdFgA+FJmd73VUlHSFy6KwsH1LIalfGBdx/0+xnnL+W6OSa6WiSeXErAnx2RH3JmRPKtePp0v5utaPTNFc8WTlwfhOW2Z9YjxxmJxlNPs9uRg0A3x3x+814ZAe29SEL/bZpmsjc3Vbn/XcNx0qAB6JtOD+eEo5LRUAS0X8nCOuievjPHdt46+j0qe8tns9XbqnSLPzY5IyksfHdT/Iunqdy8ejK0EZx+aP9PrG2L9PxHU9IyoAUmH/n1lz+Zs6Kq5+HBn9rWL/x0VBZZFIU3bo2I7F4+neDwe4Hn4fT+u/3meZHw4Zf9aK+D7IcXpZ1k1h045uasOGZ2fp3qqRxvTaho2zc9J00XusqLzfKSoay2UW6jjXNxbdL46JLlKDHMMFI64uNGCl4Mot8X7YCoAfRbyaYwzdjFbJnwYPsD3l/HkjzVqyiBeXD3HOFowKgkXGUJF6Q1wDi8W96JnTqQJgvoh7i8R1f35Lnu6/WWuB/bIuYre1POx5YWzr7S0PoJaMfM+EyHee2SN/dElLd7ume91ZA8ab8bGNmxQVAAvFQ4clotB/VExLlSqrKZUAM8ocY/zet6rRkYzT6/TSoE0fqkYHQ/lstsw8EU6rRgdc+lgdvtSxvpTQpcHu0sBVaYCn9IRru2x+GjwuDeCURjFOg2ylwXlSM9g39djGuarR1yd1eTS2L5cGSXp7HW6rRl/BdGs2b0KEdWLfm89d0iBZzYBQi/c5nmnf0gBrk4vpjxXnaI4++1RaKPYpnZerOpb5cjU6WOL36/CjYl4agOvAOB9d0mB9345jlrb/q9XUg20laUC7NPjid6vRgbEOiONbWr0O61ejA1Xl0mBsP6/De6rRgZqOiN/MvaMaHUDxump0AK47hzhOF9VhuWp04LrlinmTWkJuhdiX1eMc5ppB7VJcvj6bvngc8+vje+m8HluNDvD4n1gmFfIWK9aX4mbzWrA0GGYa+PHNLfvzQMTNhbI4mw+mNjni/liu/7S++zp+rwnv6rFNTdirZf681ZTBD9MbRNpGQC/Xs850SAdTWvGJSNd+2ZIuDOO/1eiAYilOvKUaHVCwV5vPNCBbGgRumWL6fRHXywHpFu5z/FMcen01Orhj4/6OdS3UZ10Hx3VUDk6Y4s/eEfdTGpwGE/zODLpHnRXb/ry4jtL5eaJluXTtpYE2X16NDiqajvmf6rBFNToo4Hkd6/9UNTow4lurJw9KWfpipA/7dcxP60gDJH58yH28Mu4pLxpg2TQQ7NnZsfnDdDjGK8fxS9twaVW8HrjFbUXatFjcB/K0MQ2QeEfLMvd3rHPZOpwUcS2FV1WDvzo4DRT6UI91P+lZxzTkfZI04OXbIl6OpT33E9XUA0T2255y/hKRN8iP7/VxDAc9Z80xu3cM25/u78vHdXN6n98dxoORX3xV5BmPadmH/8Y19sLIu2wa99BbW+75F8X99MI6/KOYl47dBfFbr6zD8S3bs16kzzu25LveHveLLw+4b+l8fS6u2ecX8f43se17xj7eGPnbfyqiALNbBcBHIzN2UNyk/xl/88Tw69Xo6Nd5xmXJjvV9PRK//aIA+K5IXBspg/mFyCCkwuxxkcG+sMc23heFh/E9Csf3tFQKNDfV66bx2L40Cnkp3NVn2R2igFu6MwojzStmlo4bxCDmjMzyMR3rXiB+t7k5HR7HvrFMFC4/ExmyK+I7EyPDmN8kd8w+P94Sr+6MQtaELEPTlolPb3o4pHryGwCeEZVNR8T6fxoZhFx6s8CacUP9a9zcu4yrph61/L2RoZg3vptnBhZsCY104748jnUaaf8DLYXlVBF0TjF9fOzHSGRmrswyA7dkx39i8Z23REXHSIQNIiPSS6oM+Ul2rpvMzx3Vk98McU5L5U0pFbDOnwFpUYojt8d5mJ4WKdKSueOYlIXewyKNuS/So2lxRBQQdoj/e7k24nNZOXpPZLDLty6kz38ecnvujgJCua6Nq96jnKfKvNdVU7/iapPIyObXXYr3bxxymybF9TZ3n8qNJ+I+ku43b+hxPM+L+JzS3ebNNKfF9fFoR3qerr1UeZ3eQHN0VEz28p9Im+7sKISmSsn3tezDIH5RXKMzy/xxj/hCFBAHqVBbOuJUHr/mKeLJi4rPzTILdqzzrrinN5VPabmvDBG/e617ens0jlN6C8MHZ8E5uyvuB3l+aqXs3tHmGcU5uyeO2SJjiC/zxr0o7f8ZHYXnroqPfpVLKS6+NvJ8v+6oAEv5z8viOrs60p+2irDN4z76gqhALKX1bx0VAMcV8+aNfFNK69oenvws0o7PDrjv4+MaSxUW/+8VluPGjbu6Dh+uQ/p/pA671WHROnwpTQOYWRUA1w9xE00FsmvihvBg9eSa8OMiYU03ivR6sX1aCkLJRlFYu66a8q7kx4obxTWRwUyZxRPjN1ON7809tu/eKFCs0jF/1ar7qfjMlAqiG3bcwFIN/blRQE3naudq8Cc+zVP5L/YoGKanwi+OY50y2H/L5qfvzhcZhOZJa/N0MM9MPxgZ57WikJ+eZv6p+K30xDC9GnCP2I9dW/ZjQmSAD2rZ1juiwLB1fE7b+o+Ogv2mcaP9bo9js2JLRUrK3H8k4suVAx7jv0U8+nhHxcx/OwpGd0eGYNE4pqtF3P6/yDTPFZmcPGO1ZVxjc8d+prBcXD8r99jGeaJQcnkx/Ttx3pbK4taqHddok1ak4//JKBjOCPtHeEbs38uqJ7eKGdakKARuHetM+3lRx7KPRxzcsaWCaRipNce2cW0P8hqxL1ZPfgVjFQWgA+PaStJrA1NF6TfGsE3lutJ1v3fV+8n9TVH4zl/Rel1U1L0h4sQ8UdnxtzFU+FwaGejxcaw+01GYSIX+D0dc6Dqe10R6NX9UnDQVAFtXT26Z00jH40dxbXw6CgxbjfGcfy1+76Qxfv/ISNfGz+T7T9NS79q4Pt7UUUhL5ye1LJkzClynFhVop8X5myPi1vEtlWxnVVNeefiGYv4voxJskTiHX448xiDydY8bQ2XUsB6J4/WOuHZndlPtB6Og/M2I80tE/uqnxXJp3hZxz/hYcc4mxXXx8Thmrx0iv3J+pEWPVe0PNx6Ke1j5Kt7b47c2jHi+c8t3T4p844PV1K3mGqnFQXqt8++z5XeJ6bn0+9+P6/oLca2Pa0mnUzxMLUf+XczbNypUeqWPv+uoWOiqgEn39rMVO4DZTvRTuqrHAG15+F70O1s3BjRrW+aN0b/5sRjxdqk+69w9+m7fFn2n8z5vh0b/sDtiULVzYgCnXus7PF5/1TZv/xgsaHq+1uj+AZYrR6DfoeNtA/lo8pdF//fTOwY1LPucLR99eR/IRrKdVIyC2/QbvDLmXVC8pWGYPqzvjL52af4fiv7HTXhm9LObFAP9LNUyIORv+rxG8JpsW9fs6JuY+uu9us8xXyf68s6MVwWdG68AqlpeW/iaGLPgrOjb+NroVzopxlFYsBghed+W9RwXg5yV/bibc35vrHP5llc77RMjPN8f27BuR9/9SdHX/qzoS1r1+L1JLa9TG3RskXEx1kezTef1eU3doH1XXxX9Xx+IdGOVPsu/Kc7HMi37Wepaz1HZeRlkGz/Y0V/+vdE/fFKMubJ10Yd0mHFb0rr+Fcfhwbge5+yzXSvE+Bb5tA1j2n0Rv47t8eaEiX3SlJNiHXfEwHLzdyx7dRHP28LxLYPTXdkxoOs7om/wIsU5uDYbiGuYNPCJOKbldTDMNfCHlrF0ZsYr1Zr77h0xns8T2ejq+Yjyv8hGlF+yJX3/fcy/suWNE824O81bAH7U0v/7h3GPvzve0DPXEMdizWxE+1/0ud4G7e/e7y0AzdhE5xVjAfQbA6Dt94fZ3uae9vOY/t9sML/yzQ1Hx7rObTlnz4ljdl8sN+gYANvG4LeT4vuv6LgvTYoxJco06K44x4d1pA+/icEFu/JPj2Z51JVjPIQFOl5z2wzk97cYTLFc3wUdrwx+IsYIyK/lNb0FAHi6GFdUAMyI31ipGm2uNWEW7N8mUfu7RTE91YinpmMb",
		"V4M3qe8nNT9NTcpWGfJ7qRb589VoU1pmjndXo0/NPzsLt+ET8XQyxc0nnBKGSrijeeg0pNnPrEZbaaXuWzs4ojNcug+mVhK9WtilFkCpi83bhvxeI7WqKMfMSE/rD/sfOL6pZULTr/55cV9ddjqcs9QlbKGnaXybXfJps1JqOZJa2/15DN+dENdcOsYP9Tn2qd9/ahWzfJ5+A8wqc8yE37h+Ft5UUnOr1Nx625bC1+HTsfCfpIEKDxnD97ZS+J/pDq1Gmz/PSqmLQtP/9tkxLWU0N3Z6mAlS89bU5/orDsVMMRKF1NT0uqvf9U+Kwv/mUZB4aMDfWKJ68nglh/2PHN+Unr4sjnEaDPZP0yFvlJr23yPqPi2le2/q9pCa5l8yxnWkMXrSeCNNN4ouTReMIxx24H+pAmBWe1dRAZAS/jRY3Ben8++kfrlfFaWeEtKTokdn8TakTH16+p/6LqenVakfaxp7YFOnh5kk9bP9u8MwU6Q3qcwXhfJBR14/I5ZfwuHrKw3YlsY0SQPDPSsKXNMijceQ3riyv0P7tJTGMflxNfpmoWlp+prGuFq0mvpp//XF5zSWRRpn5DMOOwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADzdTPXu0pGRkZnxm8+rw1F1WKcOj8xmx+ODdfhrHc6Mz++sw+3V6GvaAGavBHzcuJmZdsPMskEd/hT/vyvyDIPYp5ryCsClq9HXq4L0m9Kmkb+/pscyL67DxGqMr8ttzi/MjuYoPm9Ujb4TdcGWaS+Pv/N2rOvQavSdqMlNVfe7i1eqw7PrMKFj/ofqcE+s49VD7Mvb6nBrXKwf6Vimbf8ab4qMxqXZtNPrcHAd1uvxu73WObPP5c11WLuYno7zMZERursafVfynC3fX6QafTfuNcW+zF2Hb9XhjjpMrsOxkbEqLRO/M6kafc/14T3OceMnHXHq3TE9D2d0rGPJOhxUh//U4ZCW+SMd4bFiueXrcHwcp3tiXW3nNL3z98jYz1vqsPtsfo1vVo1Waj1ch3PrsGqPZdP5+nod/h3H5+44JusN8DvPjeO6TZ/rpAnpfd2/7ohLyeZ1OL8afVd9ukl/tw4L9FjnE5FmfKMOCw/w+13xoGu521rWuV12bK+tw3uHSB82aon7g6YlvdLpfNpisV1HjiHNapY5sStvU4freuzDGwfY38a6dTglu/aOjOux3zl8POLqx6uiMns6rPvROvyjDh/tWPeESHdSvEgV2VfV4f1DpD9NGEs8+UVcG23+VU397vpP1+HKYplUsX1/HcZn014X+zFfkUEeabkP7x3X79JFmp2+v1xL+pPW8ZIBj0ljzrjeN67DSdn0r9Xh6B7x9jt12Dm+23beUnzed4wVEumYbTHGdHhG5xM26pM/6+f1kfe5p0f+aXrs30px35xjgOnDpFOzOv/FU8vHIv85vk9cmj/ynls7ZDzdKwC6pMz1Q5FZ7npqn57sXxaZzrTeO4v5m0SG6rj4fG1kDspC5LfrsGsdflyHH2TztonCaJuFo8C2b2Q0UiXCCkMch4Xq8L3IGN2XTb8pMjs/bPnOEi0FjcXrMNcsOpdbxDH/azH925HhTRmYreI47lYs86koQH+2DqsX874c331FHV5UhxU7CtrHR6Z4wzgHq0UGuctL67BTx7wUD1Kri2dk4Q0dhfEL6rBGHXaswydalnlGSzisDr8tljshMp3r1+FVcTP4fsv6fhbHYMPI9O7TUtiZXaTM/G/qcHYd1orCyg86ll094s7qsV+pomDLuGZTxcG2fX7rrZFOvKXPcqvGOXhxXENt11aad3Js+5pxfFOFwBE91rlc/HZKh/7YIyO8ahEXlh1wubJi7bURF74dx2yPqCh722xy7sdHQem+qNgcq1fG9diW3qzU43tfHTAtfG7Ez0ujomnTqFA5J67vXudm+Sig7xGVAP3WvdkQ6165DntG+HRHQXLFyBiuEtuQlv1MR/rzmqygk8ersfhVpD/leVk7tj8vIKf08dlxj8vT3gUjrcsLuJdHhVvjrGq0UvebWUZ52UhnvxQVc43DOipE073lD3HMu9LklH7fGxWCpVTBMyn7fHhce4t0HJu7qtGK8DZLR5q24xB5n8bFkcYdHIWCp5MlI86cGGnvL2bgb10feYMnBpzO7FdZ9FS3UKRfu1T9n+yfFuWKr4k2PK2NjIxsNDJqwdQkKUKa9t/4e0s2PQ/j63B3HeaowxZ1OLmYv0DM/3L8v1IdLq3DhcVyG2a//6L4f+46rF6HEzt+O4UXxLILxeej6rBJy3Jt+5fCR+pwese656rDnXV4eTF9lzpMqsNpsc70mw/Gdnf97rw99mFaw0/r8PFi2tyxTa/Mpn20DpcUy+0e+/eiluNzWx3Wyz6/rg6PxLlupj07vvfcbNrr6/BQHca1bOt8dfhXHQ7pOC7fq8PBA+zzN+rwl9jPQY9TiiP31eFlLdu/cjZt2zpMLr67VCy3YTZtnzqcOQPP67SEdJ0dU4dl43Pa50eLc9ecj2vq8M2O9Wxfh3vrsHSP37o2vv9AXOODXHuvijhSLnt2y7a8ML6/Zp91prhwZR0+OeC1X41xuZR+7V1M2yfi4yDra0sTht7GHmn3AXW4ow4rjnEfm2X+UYdPtMw/vA5X99iHe+qw2wBp4EmRdrXFgX0H3O70Oze0rCOt+9CW6efW4SsDrvvDdbipmLZGLLtcMf0dccyrMdwDhokn80Yatkux7F51uLFIc9O1+FgdNs+m3Rzp76ezab+vw3c60pB0D/lQfD4svtuW5r63DvfXYdH4vE5s+0v6xOcD4nvLDhhHL6/Du8ZwDad7369j+18xk9PiQa/taV3/WPIYTb5r/tls/4ZJpxacTe/BPUOWfo81zDGT48rTITw/9n/CgHFp06wsMqbzC0/lFgC3F3+nqjeoRptLpicqj8fTt1dVUzfne3bMT7VoD0Rtb2pq/Pxq6mZ6t2dPbtJTgbtj3ekpW69maTdF64SNIqSnGX9pWe6C+L1JxfTtW54IN9LvnxTL5NKT1OdkrQAejv08fxY96X19yxPSlaOW9/Js2l/jaXDZSuD04pw1PlBN3YQ07edDRU39P6NWNa9NfTDiV1t3g32ixcGPe7QAuH2A/d4hnk4NM5bEO+O3/5BNa+LgQ9m0ycW8qprSdPjqbNrZxZO05rjfVlxfbdNyC8aTxg8OsS9nxpPFcT2etmwX+9v8xmMt53nXWEfzpPPTsa0Xx5PT1P/2imgZ0CY9jXxmNdpa5q6Ii4N4In433/4JHU+hLo4n7P2eWqS48KN4WjejpJY+qWn5ccX0n/VIR2amFMdTc/Q31+GGaVzXT2N9uZTmvSHmdUkth/aqencDWiBaGLS1KEpPercZcBtTWr9CkdY06/5Jy/I/HyKOptYDyxXrfjT+PqtYNrVYeXWP63F6SenUCS3HZ5t4Yp9f3+l++7e4JyarR/xNrbM2z5ZbP+6PbWnIN+PaTt0A316NNp99pCOu3F1N6QrxyZan/6XnxvKfy9Kpfg6Pp/jD2inOfUpbdp6O52P5eIJ+b9w3TmmJG40PR9o6KdKpuTvuBalL5X2Rnu7Xct9YLOLbg3GO3twjj7dP/ObkeMq/Qku+qIkrbXmA9FvHZr/12R5PkN8c98cUPy6rntx9rF9Xl15N+T8Qx2SdAZ9wp3vpdZFnuaQOL6hGW6/cGNt3Ucu6Nor7UrpvXtVjP6rY/5SHuT/yK3t2bEu6XveIZXqd98Wz45y28YtVdxer78b5KlucpTzoWbHPN1VP7pY0kuVRH+xz/NtaCqS0+ldF3um24n77nWKZXWNbGs+PfMiEIt6k7VkxPm8Q5+Gl2TKbx/bk3YwOq6buItSva1GVHfvHBry+Hym+B/8zFQDp5rB2/G1LBFMTvl3ign9G3GA/XE3dvLEpoOcZjpTQrVlcnOnmsn9kGFJTu0/FjT799r96bON/q9GmxIdEYvB/1eCD/8wTmZ+L+xyDF7dMXyFu9KnZ5xbV1N0HZqaU8ftzNdoEs8yoV0WFx6RI0AftqvDruJk0doyMR1mQm5Sdy6XimPyiJZFdL25Ku3RkNpLUVPN1cRO8NW4oZeK7bFQU",
		"rBUVELdHnJmnx76km1XqHnJgMf3quCnuE8dmsSgEH1Js4z3Zec/3ff5i+1KmY9WikqRtWhUVJ3tE3H9/Ec8ndYS84uWoqNTZeYAb1Psjc1oe93fF9fNonN9U4Ns2MhJNBuOEqNhrk5renxoZod9U/bsBNAX9j0e6kW/PStWU/uVlxuVj1dRjdHS5IirnZpSmIqgsXKduTZ+fxWn6RlG4S4WvP02H9R0RadyGxfm+vZoyWGqbH0W6vGePZVaJgvXVLfP+0aMQ1XY+0rX5+IDrvrp6clenLs9uWXczrkIqTH0tqwCcFOnwzHj0c3RkjhfKjsHzq/b+8RdkFQDpPnVeNdrFKt3Txkfl5OIdFQDJvlGISffWVMF/fI+M8r5x/08V+NtHmtrLd6OC4jtDxsmXVO1jOXRZL9Lt30UeZZuqfayQYY2LNPWJuEbWj+Pwy47lU8Vh6g6Zuo68puP6SNdv6sqUusOkbntpfKKy2156ALFarOu1ce7bfDH29fVZ/q2suCy7p1R9fmvLHsdjhwhrxf37R9Mpvqff/VbEqSuGSAu3imN+Z9zPNotKurUjfTqk45y+L+6FvfZj//iNTaIAvFt8ry2PmdKj1IXyjXFvbTvvP470ZrPY7g177Nu8sQ9lXuxXUbGxelTUfLfIu5bdkcaS7rwyy2u8sBrtjpOPFXNaHJPGVlFob7rRvSQqZCYW603n5yvx+Vtxnf8xW+asyA9uk5VfXh2Vnvn+NWHzyNMc2HI+qmrwB0fNcnMqMvK0NQ3NqVLTw8/E/3+K9ZTLvD+a+x4RTdLH9VjfknVYpA6L1eGMAZrezFOHn8W2/3DIbW+afz+zxzJpex9u2eYf1eH/4v9j67BTMX9ShMnxG5OyMD2bNJ0UzU8HaR7Xq/lXv/O/TTQ9XbFj/nqxb09E8+CyKfic0UT6c322JTX//lodnlOH10Y3hK91NOM6rw4bR/P2m6NbQNdx2jqami7cMm+paD6bmsg/HvFurpbl/hrnOjWbX74Of47tmHMM5+2zdbirDhfV4a3RlSaf/6yOkC+T9uUDdbiiDv9pafqed1l5qOimUcU1NhLdaNLnq6Jpfvp/z2x9r41uPG1NEP+Txb+XxLWyaEfcauL/49G1aOlpaNLZr9n0PD1+vwnb99nOJmzQ0VVp0G0s1zd5BnUBuDOO7femY9Pa39ThoGze+dH9oV83htdEnFupY9lex7HXOVywuEaubOkyND3W3XR7+3ZHvP9ANCdvukrsNA3NbofpAtDc81K3nDfH59RE//qOde9ch+uy7nF7xP+3xPrTOm7vE+f2i+14U5/l5o50NG3LH/osu33cKzYcQxw9rejC0O+7L4k0Nu82svp0uPfOEb+3UEuT4fEt27RY0b3k2mJ9i8Q9aNNs2lvqcGCR5j9WdEvcuKOryANFt8RVYrk1BoybzW9tmU17cY/rPk/Pt4jzO+cQ8bwtr7JppJm7DpnHWSSb9tKWfF6v7eu3H/PHfS7vXvmJyB+0bd9CxXLXFl0AJkS6nR/nF/U4zhM64uMDsa/N5x1a7vmDdj9rW2583GOa/f5SHY5r6Wb5aMSxJp06NstLHBXfq1ryO5Oj69fEji6H38m6624Yv7NYR9fdP0dXvXmK7T+4pRtsr7g5f3Rp277lO5tEnunGoltS6gJ7olIl/wsVAEdEn+kmU7Foj8L2N6JAlwosq/VZ7w8j8X9fFO7+0dF37zexvldFArh5hMcH6CO1Qezzwj2WaW548/XofzV3R4KWwnbx/bU6CnFVR8XBIBUFS0UCu2CPfVuo5aYyfshM11rxO2/tUxHzrLiJpUz5T4r56Qbw9+xYDdoXbZcoLLZl8FfIpr27T0b21CIjlYdfxY3lBXHD7+r7vE7cvB+Nwvt34+9YMo+pcHRBXBfTmhHdLI7tgx2Z1Ns69mftOI5LRp/myVncOCAKD82N7omWSrAtYkyICdlv3RLnoi1urRNxZIMoSB5ZLLduLLfoNFQAvDy2qdfvN2HBAZebp4gDyRJZJiu/ZucZYH3bzaAKgJOjkPZEy7glY60AeF1kgOaNTN0TMV7GIBnJVAj8ZceyTdxbquX3t4iCR6/KlMlxnn/esi/91v1In3U/FJ9/NkAF9HpR4fJIVIbPjAqAZhyGI+L/P9bh6x3rXiO7xm/PKrN+EYXo9L3je+zfYpHG3R/j9ozrczzenxXcupZZIMZWOHiMcTRVtvxtNukXvnLEkxuignzQyr3N4lqao6Vie9E+8S1ZvE88Waej8nGkyEf1imOD/tagBcixVAD8Jyqw5hyyAmDQbRnLfqzbclza8pxt69u8Oe9Z+j0txzkPe8Y5/nUUSBccMC0a5mFRevD1/Ww8jh1bfuOcyLdtGf+/IR6qNGOQbN6x/Z+P3/xAx/yNI++Vro8v1OGUjuW+EulVWcn3uzj2Gw+Zbmzfct2Mj7j5tdifdP1/KuLp0WlMIKVKZmdzTOP394pmj2+O5t6TounNTdWTR0NOrolmvytHE89eo82+OLYvNXNOI/R/Kpr6lH06V4smVamp8u+j6evPohnVNVX/UWWb/py9msTPVSybN/+uejQn+leEZlTif2fTelk3C/28JZpfTWqZd2/8zUeAToWG1NfqsSHO82LR7PPA6smvFMs9HPt2ajWl+0b+mpW943zdHdvbNO+6s8/vp7EFlqymbt5/f/ydXDTtXaqjqVZqypf6sLaN7J+a5qc+f7tE07TUdPrTHXH4itiHlSOu/zWasI7FqtFk+NJomrplNXX/4X5dAFLTu9Sl4cpoCnhsR7O+1PR16Y5z18Ttx6LJ9b+zuLFkNJNslhtpSTPeGvNui2bCk+O3uvrgN9fAxdE89Q3FOm+I32nbj32qJ4/G33X9XN3n95swacDl8m4w18e1v1p8PiF+c+eq+/Vj5fpuHjCOpOtniY60ui1te3s0A019I1M/4gnVtPtd7H9KZ98ZTTGvG/C7H48mzG3NWdM6Hq+ePCZJFU1hu9LJjeN4Pyf2b8eW89hv3Tf2WfdLYp0XtaTtqen5mtnndP2m/sapj/LHxniMH+24J89Ztb+usmk2u1Vcb5tU3a/HS/fB1I3hHXGtXhLT/xj3ydR8/IIe2/aFOP8vjWXf0Wdf/lL8bfPZaEa8xxiP168jDV6vmrXSPpwZ99V0XF4wwPH5f+W+Mc4bdJnm3vvSIk+R0q1zh30+NAuPcboGF67a38bB1NLo9qn7yNkRD6+qhnsj1iBSOpO6ZKwYaekJLcucXk3pbvG7yBOm7jFpzIU0Hth5Hetu7ldd3XNSV83U1bXpQnNMyzKbRP5z1yhn5FI6fXKkP4OaM47rl4rtflbMS68ePqOa8marhyJt+pboyFOpAqBrkLwu348b3uS4sbw7bizp/4OLDFfKkC8enx+MQv0GHYW1ueJi+1Q1ZXCndMNPA2wtV03d17kpwNyXbVMqpKW+uD8cYB9ujb9L9FhmiSikPjaTzsu/BqwoaDL8P++Yd12cmzyTtE7V/9UnZeJ3VBRyP9OxzGqxrfmrtR6vpryfPf/ttbKMSJNRemG2TCr43VFN/YqrlSMDmxfCUsKe+pBtVBSob6+m7q/b+HBk1Nr2vXmtUz4I4IM9CnNPRAEu/X1P1f76qlKqmHhfUSHyn7ghrRYFxBMizrdVBLVVCqUb4UfjWkvXyZ5V++CJadqLqiePEVFVU/rhLRbXVX7s1syuq/XjGn68uPbeGIWefPveHDf/ZQbIVJaD9NwTN9ntWwr1n6v699tLA2K+N+LsjHJfxKUds8qoYQr1w1gtroe84mO5SKMntyzfxOHd4lx9bzpsQ0r3fhFxPaU3Px3iu6lwnAZt26tl3qTIKL63Zd4OHRnLvDLluo5j0Kz71NjmtnWf3Gfdf4749vHimk22iUxtee+6IeLfWAYBbCqVykrfdWJe273nlPibMqA3Vd3j2IxEIWrnqNx8IqsASOnn6lX34LXPjXRrj1h/Smv2rabtvevPinTr49WUcVWGlc7v8REfZ6W1okJol0gT/ln1HsB27iJN+3dxj7w2zvVzigLNbkX+4LEirrTlo5p1rVjkKW7rcd205UUeq6YeY2Bm94XeOQpzn68Geygy",
		"M/wz7kX5cXlBFLjbKmbzNOGFLee9qbBcr+M7g1ghrs2UXuwf9+DrWu6lIz3uG/O15K1Lf4zlUvp4WtU+9tVpRQXApLiv712NViC33cfTuX1/pA17Vu0PAUaiAuJ9kTYeW8xfOO43h3Xki/8dBfNXtaTrva7xZ8UxzccWuzryOP/NrreUXq4S5/heRUyeMrKmecM0f1sz+tpU0WynrQ/2vNF8fI+smfBBHX2Km+ZVb4n/l40mO6+P5pXlqwjHRdPnY6Mp9XrR1Huko8lzW7g168LQFj4XfQ5nxCt6hmmuuEBLl4rb+vQ//3H0u187mv/fXLyeq9+2HBD9XFetwzJFyPv2/yua4qZuHc+Lpu1HjfG4XBznc81o6v+vaGpffv8L0VR/gwjXtowVUEVzsQei2XXbdqTt/2c021o92/5jOpZfOpoRnxZN4OYd4Fw1+9rr+lq2o2laV3jrEGMPLNBj3yfH+A4rRjPmTaNP8c0R9zeI6+6jxXdfE/0gJ7RckzdFH9dy/1eJuPPcGL/hmI5+dQ9En88V4phcFl19qo51Lhvn5OxYdv4ey5bxeNwYrscNo7vFp6OP+5qRpt3T0fd3rK8BnCPi+Ilxva8f6d0hRR/SribGqUnqGwfs5tDrNWxrZ82JFxxyH5btaBbdNFNO6/xW7N9z47WANxXNYcfStPs50ST7G9m6D437zvIDrLsZs+TtLU3ib4q4u37s32bR3/Sn0/DqrZ9Gf9LNojvOttHfdtce3zks1rtfn2OxdyxXruu66GrRlT78IdLj5hpZPOL4V6dhjIkTY53L9LinDHKuXx337jlnYReAxSKt2jvi1EvjnlB2vWu26Vdxj9k00tTPd3TtuDCujfUjTnysWOaXEd+eH/H8jI74dVAco60inWrS9fmHiJu/jDR1vR6/NSO7ADTTfh597OeZDboANF1UL4/ztGnkxd7fsV8Hx71ny7imP9/yGsBjYv9eEGnVaUN2AVgo0ravxL184zj327Wki+XrjOeNfvffiHj8krhGu+LFDyJf/o4erwa/L5rI52NejLTkI5r73AWx3irGFfhtx7rXj/X8oePauaHlPl+NMQ5OU3oCT6UKgFWij+Aw7xZ9SxQym8Lmjh3LvS0KFzfHu5KTLw74Gx+NxOnW6I9azl81+r5OjgTw0Oh/9GgUJvqt/ycdBcwmnNGRaE2P0LybffwA73S/tTg3aSCV/ft8b+Eo2D4QGbcDehQa2xK6XvLvrh4VLw9GZc/hPQaq6XdjXT4yic35PKhl/IXmJvOt2K+JcZOdp2W5T8SNqNcxXi36k02OdR3WY/sviJvM/h3LtJ2rrePGPyvee9vvuv5tnK8qKlAmxzWxRlSMTIp9Lb//8+hT17bOb0cf//Jcj2QFyV9l/ejL8KoofD0cx3L/HoX6kSjo3hAZmIV7xLU2E8Z4s98s9vHhiPMnRmZwrH27u5ZdM/p4Pxhx/YfNMn0qAKo4HncUAyp1HYtz+mzLn4sC7jD78MUemcnnx/gbD8S196uOgUbHkhF7Xrzjvun//FjE2zkGXPcGkckv1/vMqIT5b6zzpuhLP980VADMG9ffLXFPSAW/9/TZv9cUg3hWPa6nkZZxdw6Jwl3bd94Q3ykrJXePOP+sMVYADHJPGeRcj4907ZWzeAyAreJcpXhwTYx1U56TjeL63T22eVJcx20DzS4Y95/7YuyFL7fE1wlRIfpgDEDWdX3NFZVDt0acuqSl/3W/uLloVMg/FL/1nSEG0ZyeFQCLRBr/9dmkAmD+yGveH2ns3j2uhS/HMg9EPnmulgqAxeI4PxiDaO4/hjEANor8ySNxzvdqGbNjXAzW/UDLIMnN+EbXxDZ3xYuXdVT+5+GErGyQD0C5Tsuyu0Z8XyobP+vhHg/mbuyoGB0kr9o17lfXsd14wLGqVADwlDKubAEwg60QTTJT8543tDTfmVU2jOamK1ZTNwOvohnSX6NZzx0z4Le/Fk0wtxnDd9+dNTtk9vaNaPL3ydlw29LYCGn8jM2r3u/sZnZLwMeNm1lp99NFiuupe0jqI7ttNWv7NtMtdU1I3RLS+DW9uiSmLkipC86pY/hurmu5BZ2K/3/snYeLY57GYlpkOv5G6qJ2XhzvB/5X4nGf9Lv57nwt+dL/ZalL7k2RN799DN9PYxulbjCpC/JfBjhXadybNF7RcmO9P8PsaPxM/r008NJJUQFw8mx0HC6MgnTqy/zlYt6Xo5B+xwz67dRHa6z9dH8sCj9lpDEtHpxNty31w94/KgHSe3hT39rUry+9yzv10f2z08fTxOmR8VtX4f8pIWXU31V1j+lRjr+SBgr9xBh+Z12HulMaS+mW+LtkFIZ+OR3Xv2w12ie7a1wTaKS0O40dctoYC/9V5OUPiTzPm/qsJ/X/T+PX7OfQ83Qzs1sAzM7SIGhpgKT0VL0ZTGnHCGnE0cdEF57m0hsl0qCEaXCdNABQGhQ0DUp4kUMzmybgWgDw9JSeOi+fVQIM+iQ/DTTcDEabBuVyYUy7NABaGjgttZ5JT6LTIGzpYcn0elKf3laS3sKTHgwd8DQ7dloATF/pIUp661FqvXXjNKwnDWSZ3tqS3ohybp880RNV9xtWBro/gwqA2V/KOKQ3I9wVn1eIzMcjogowu1YAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADAbmVlvAZhYhwmzaB/nrkZfKXR/fE6vCbrLqQdgBntW/L07wiBWiPtWem3YbQ4hzNI88rvqcH0dTu9YZrc6XFiNvjZ3sJV6ewswi80xwDIjWRhWeq3e56rR95im94uPn4H7krbvuGLa4pEovymb9uNq9J22ADAj/TPCR4f4zqnxnYOnw++nd4mnCu+vT4f76fS+P/ezZTX6ru8HpuPvXFWHP3acp68PsZ7pfXyYPe1Thx/UYd4ey6xZh7PqsKHDBTyVKwDabmzp6fnklmV3jEzK++rwjZb5v6/DntVoC4Dv1mHfbN7OkTG5sw7v6LGN89fhV3V4sA7/qcNbeixbbuPPqtEa3J9n0/aKyoi3d6xjudimWeWZdXiiDs/Jpi1ch6Nj/9ITod1bvrdJHX5Sh8OzaQvW4bA4f/fG//Nn89OTppPi2KZ9PqAOc3Vs1+t6ZHreX01dUTQScSK3RB2+V4eb6nB8S5xrC41V63BabOddEZfmzuanCqZDqtEnZmn9O81m19kX4vhOjvO4UMsyz4l5d9ThoTpcWYdPV6OtV9qk/b87jsnCPTKpTZgUx3D1Ypm3RKb4kTpcW4cPdKwjxclb6vCdlu1vO3d7DzE/2a4Of4vtSHH8+3VYoE+6dFwRT4bNtOefx0V6NVIcg0HWmcJniumfbYnHI3F+F+uxD8m2dfh7HR6Ov9v0ON6PReHlgy3blq8nHdvX91hPKmSdUk15Yp1bOtLSO+P8XFKHVw94Dfc7P+W0i2Javh1bx7RfZNOOjzi5YHw+OJZZLj7vG583yL6zX0zbI7v//S2OYZ7efiuWe3M27fCYtsWQ+5xcXIcjs89XxLXUVQH/4Y7pa8e6PzxE2nNB3BvSPXiRp1j+JKUBi0aaM718sQ7f7pj+K1nCgezdJx/2dLJrXEMn9sgj7hX5pneLGsBTUuoCMDLquPi/+XxlHa7LpjXhG3V4Xx0OrsOOxbyV47tvq8NcdfhHHW7P5t9ThwPju/fEtA/VYd1iPbvGen5Qh0vqMLFlO5rt/E72ebOY9vqWZQ+vw82xXc20cXXYuQ6r1eHOOixchy07fue4jm2YHiHt7z+Lad+J303H64z4f9Ns/j9Hpsi37dA6PFqHA+pwSszfK5t/Tjb/pJj/sZZtmjv7jbZ937cOT9Rhzyw8P5s/Ic7/Q3U4IuJE/v09i3BfHf6SzT+/Do/FcTg1tuPT2fz9Y9qP63BeHR4vfn9WhtfEtv0x9j3Zu1jm1XV4sA7X1OHbdfhiHX5Zh8mxv3O0rHeb7Jzv3OOauDKO6UFxDC/M5r8qlknT9onjPFKcn2Yde8V1k9Zxbh3Gd/xOEzYdYv4rI/5cle178qM+191xMX3Qa7MtbWs+fyI+HzXk9d64rJh+eTavXPaHPfZhi4i/V8SxuCI+dx3Pz8f5S3ZoWc/lsZ6/",
		"xudNOtZzcMy/sGUfz4p0IsWhr9bhjvj83JZr+MpYb36uex3LctonY9oHs2nfj2nbFL+XvKg43tvF599FejN39p1FYtvvivR9h5bzkcIz4no8Kz4vXYeH63B2n3TrsljfMX32+VMx/eVDxNXmPvBA7OuMTrem931uLOtLacJvZ9F2D5uWPJXDHLM4bszOoW1fl4s8YrncsYOuF+CpUgGQCiEXdWR8S1WWaUo+Ep83iMJQM//RyNRuFv+/IQp+KxW/895Yzzp1+EVHBrXZns9lnw+JTNw8LctuG8u/Opu2ZOzjvbE9qVLi5Flw80sF9a8V026sw8XZzWckCr3N/J/UYauWbbulDj+N/xeK+Udn8/fICg0LdBSAmsLRvT32/ed1uDUK+ku3zN8vCo7pfC9fhzl77P/G8TvvzqalzPfpxX78Mpt/e1ZhsFLM/2Y2f82IW3nBe5MoYO/Ssg3jIo5ckE17VkvIK1JeG98r1/XyOFfL1mHelnOwTMS1L0RGbHwco3FRiXZ9cSyacHQUZlLF3GkDZl7SMXwk+/yHOtwd576JA+mYnNljHR+JaW+ZjpnlVDkyKa7BPM4cMZMqADaI43JNxK9hCwJ3xN/VY9qz4/N/OyoAUsFmw459+H0ci8Xi82Lx+cQe27RITDuyx3qWiMJjr/X8IdK+ch8fjorH5vN2EZfe3LJsuT/VkBUAq8S0k7Jp/67D/XH9NNO2jOXS9btgpC8jUSldRQVv273iQ7HcF6NS8/64Bsvlvpfdd/aK/1/RIx48P+LQTXVYtM8+rxBx4NAh4uo8UXHx/tjXF06nyuabo6Lk+Ei/899PFQ1/i3jz3SJ9S2nFzyKO3REVN1Vx/z8j1n1ky/6kdO5bsU/pHBxWh/l75C+a6YtH3Hs4Knlua7mmz4s05eFIm5ca4HruShvmjN97vMgvtC1/cva7l0Z8OT/iRfr7zGL532XLX1zMnycq/CdmD0vmLr5/TlSaPhCV+OOK+0pz/H9dhxtatvfiyFuUFdJbREXeI7HM8wY4L/0qWKuoOL4/zv24SB/zitOT4/pJ/781vr9a7MtI3CPz+0NTifasuCaOKbbnS0U+72fxeY0++dg8HzASx69fBcDjw+QLAZ4KFQBdYc+48X81CldfKJ72VPHEqLkxbljMOzJLcE+Pm8F7W35nvsikPB43y2UGTGT/ES0G2uY1hcQvtcz7dVQcvK+Y3hT6RqLAVRYC28IaWRhkmxeJm+7GxfTHIoOW35R+NWRBqylY79HydH+1LGO8ezF/qSj8f7LH+s+IY/Zodr7ny+ZfE4X0/8T8lBl5Tsd2Hh2ZngWyaafF918SGeDkw9n8R6LiJD8+xxRx6CORmW+mpUz6x+uwanEs/i8yVSNROB4ko3BX9jT1nUVGLQ9vLyrFmkzKCfH/OpEhG4kntulJ5PYR7/P1LBQF9R9FZdHjsWxbfGji6qZxDM/L5t/XUnmwZBQWu+LU4h1P5/NrYuUe29F23dyb7ePCHcu1reO06VABcFoUBCcX8WOYdZ4QBZHPZmnjrTG93L6LIhP8lyhclAXmlNn/U/Ebf2qJi82xWD2rlPl6n/Wc0WM9L459uKJlH38by/4kKmx7PTGc1gqAKo7NA1EIaipTjiiWWTQK0d+PAstIPKE/Jyo9RqLQWm7DXJEePdHSIioPy0fB7NBIt87vsc/zRZrxeByfQeLPmRHv5x3wWL01zuk8UXD80TQW/tfLWiYdHv/vW/z+Q1FIPzs+5xU+341pB0XFUbJ5Nv+wmHZo3LvK/dk7m3ZgnI9vtbTwuLLIV/w4pv8iKqvbrumHotL1mPj8lWmoAPhKRzxpW/7hKIg32/VoxM+mRdPXWpbfP+7lI1GobeZ/PdvPIzrOz+So8GpaAG1btHIciQcAR3ds7yPRqmTzYt/Sg4N/xb7fXbQ46Tovg1QANC1fNorWQ2Whvln34tl53iVrqfbKbNnFIp9wdtYybc1iezYoHgak6/jqjlY8v8zyLs28nTvOfVsFwCVRGf/MYvrika9rPqcHAYsqbQBP1QqAJuOZEuC1IzHsKgy/ORLHJ6JwlTc72zwyb7+NJ1ZLRoKZf//dWYHrwsjAXRs3+V7b+GBklNrmzdORqXxbPHF9Rdz4lhuixUOv5sEjA2bK3haZ8DmGvLH2m75k3ND/3fKEc91sG89veTr/4zje8/RY/56R2doxu5F+uHiCODkK3HtFXDilI9P9aNGVo5l+Z7adZxRPOy6LAsNLs/hy9BgyxU0FxVmxL/MWTz3LkMent0Rh6vGosGqrgGlaMsxVbPsWsT9/jXPwntiO9ePc3VWs6x1ZhmiDjoqbtjj7QGT8h7nWy2WaCpbf9PidiQO0Fur6jXd3LDcywDU4lgqARnqSueI0NAU+KMsoXxFPkLtaKOwe/+/WsswTLb93fEzvdSwuKipuxrKeGyPOtVVM/iQKDCORlrxuBlYAfCambxnHqCzc5JW858Tyt0QF8uRIv0eiwq1tOz6dtcToVaH8w+zYbNVjuaaLwpeHiD/vbSlU9/retlEJUEVl+semsQLgGVGwWjWrZPlNS8VW02KhrPS7LWthsWSk+3l3u/zp7hwt+3N93GOfHXmHyyP97Xfs0u/+vc81fXxWoTtIl4yu9dwcceTEltZdvX53rqIVy1wd23F8j/n/KSrj/pY9HS+/v2rWTbKZf0d2/Md1bG9X94pbY94S0bLl1QPG6X75lDWz7nsfyO5xecuDkbiP/zvS5KOi4uDxoiCdVxh0taYZF+cwxa21WipZ8tYol8Z9q8zzXVM8zOiqAHhhpI95a4rdYrsfi/vBCyP+flBpA5jV5hjj99KgU9dUo4MKpQGNFo9puTWq0YFiTq7D+tXoAGdfyuanAZzOqMPK1eggRWlwrP/G33y5z1ejg0Sl0VhfWIdD67BSy++V0uBpj3bMezRbJpcGwdq+Gh0sbZc63JrNe1M15W0CFxefu7xpwOUaabCvZnCr3OPVlFc2jiv2oZ8JsV/pHKWB/O4v5l8X25cG6EsjRr8nm7deHd5Zh4PqsHxMSwOzLVasI52vNIhbGmyxGQhno2z++DimaaDINNjS2XHOS82bIg4qpu8f5yoNyJMGANysDm/L5jeD8PyhDl+NaTePIV6nmvk0qN4/6vDvanQwvsbfWkIjDbJ2U/zmIy3HJ0kDd91TjQ7Mlp+7NNjZn+uwTh2eW4f/q6aMUn1LfKccvGuH+LtVxNfHsmmlJq6+N373e9m8NDDg/C3Xzdw9jtHi8ffujt9J4R09tqPtergv28fTY/7FA6zj4umUDp4S8fp707COY+IcpoH21o7PXb4T6WYaHPIZxbx7qye/MnWRmN52LN5QhxdE2nhncUzb1jOxYz23x29c0rK990a8TNuaBiBNA3oeW1zj01T33HIsk1dHmBT3kbb4sHZsx3l1OLcaHRD0Hdn8UhrN+31ZmvqRHtvVDFqbztXvOpZ5TTU6COpFca8a1K8irdhhwOXT8W4GEkyvHPvmNB7zdEzTmwn+VYerO/IDzX3opvibp2tLVlNeUXhH3OuPL9KJG4r15JaP9PbquJena2eZAbY7/e61A8anR7L7z1gsG3Fk7mqwtyCNFPfm8u/4Psvn85eOe3Pj3y1pxUh2D8/T5uZc3dBxfeX5ijbbxblIaUIaAX/ydLrOr4pznQbS3LwaHdQ5T28uinvZtpEv/GYsu17cb8s08IgsT3Rkx/k4IdKIJr9wfMtyH6/DunX4WJFvSIMir171HqQ6zwPdW6w/DQSbBk/dO9LPC+McH6PoAcxWhnh6sF0MGnZhNGs7s3gimsJOUYPaPLU4MJ7O5MusGM2Qd4on+u+PwZ8eKp4efyFqc0/Insh8qs82Tsz6jZdh4VjHIbPB4Ej5U+T7W2rbmzEALinGAPj2ANu2YDT5fqClW0EVTyJfmTVjLfvWf7XjaePeRZPaw7Mn0EtmTT/zpz2XFc3lyqfa88cToT+1bOdDWYuBBVr6OzfdOrbOnp6/coBjPr5obbFkxLWmSf/VAz7FvjLrMvDFoi973t/2PS3TH4nt2C6eFqR4/rL4f85oLnlj0SXjsY7teXaf+HBKMQbAmfEkY97s2D5Y",
		"DHZWruNjxXU9PcYAOD3i6NJD9u/vt8yp8eQ67ydfjitwdtZnfqQlHRt03+aMp263Zq14em3fxlkz9HyZ38WxWKIYA+CUIdOgU2I95VgCv+tYT9PU+Q0tTcVvK7oOHdjRnahfC4C7iubEzUCxP25Z9op4Cvhgy7WeP2EbiWU+GtfO3fF5YseYHHvEdz4b1+2DHS0/BjnWS0W3mvuKrkSDfv/YuB4XmwVjzXwgGzdnu46ntydkzZbbWgBckN1n0lPdFxVPoP/SowXArdGl4U3x+28a8Nq7PZ6GD/rUeayt50ZiGw+J/7cf8mn3tH6+pbhW/lq0LMtbADTjZhxctMD4S58WAG3HYbFohbV63MdOjnM9SNx8PBtjZFzHct+IdOi/0WqqXMfFMf/f0Trnifh8YMuyB2RdGU7siOfNWCH3R9wpW1euFmlA23hPc3e0JmxrAfBYdr1U2Vgw82fX0OuaexzArFbWSM8XTwpPjdraXk+70qvALoha3HNaajWPiyeY6fVJX6lGn9r/uljmufHU+LB4+rZW1ADnT0jPjaenc8cTg8blA9Q2r9Qxb5X4+/fpXYcSNcDb9FhmnjjGfyx+/+XxpOQPLd/5TR12q8OB1ZTXuP1mgO1Jtd8vinW+NEJTW528tRptqZHW+5yW45rOy5+Lp1bpqdrR2bRH43imJ9Er1uF5LTXtP42nY7+Ipw7Pj9/M7RTn98CW/bgyngSkJwLPzs5v7sV1eFU1+uqukyMO9zvmjxbnKz3J+lw1+rqwd1dTv26xVyuOBeNp2o/iyVppXMTrv7bMS681fGb8TU/gfhhPw+aI7UhPlI/Klk/Hec54ctg8AdkynmLvENufS/Flz3hqu0Vxfr8RceT0iCOviCekh7asY6849ulJ3/nVk1+Z1fxO46wIg/hqnK/zYl8XiLj68DRej+m87xznZM2YdkrL8U8+GE+ZDohtuS9bZq1qSsuSKo7X6S1P046LeHNQx1PPXNrXQ6onvzoqnfNXVqOto9JT39dWo600hn2P+1djG8+IOP66SN+71pPi3afiHOZpy//H3nmASVFsb78XFlhyUjIoAoJZFDMqimLAgKiYE14x5xxBTNccMAfEjF4vAgZArhkDioiKikRFUURyWBbY3fnq/Oetj6Ko6jAzG5D39zzn2Z3u6uruiqdOnar+Hml0I2YgC9FuCN8kfCaZpTsfZe571DtpM4d6+pibjXbHxZf4W4B+IoWyeajx26RJkP4EoMxsyqfgfkbcdwaZfdbsGcQ5zkiTwGpjw3gJaXAsZlorgiZGP2l7APRAG9EFv8da+SN5+Qhmaw9B+6t5G23602h7bOSTtfLpzDMxM7of9Imo2dGRqDMvBOGeSrlgPPrdg1FeRlntQlkyFP3PC4audLcnf/Y00lzzDtJfymi9BPddjX72T/TzHYP1PQUkDXZDX3NXsNZTbjra7TuCdT+raeff5WjjRzrOf4ryJm3wXLQT2+O4iXzCWLw0R6MeX4x0+MwK9yGetx76Frtdfhrtx69G/3WrkRZBzHJW1ZFOPxv/z4EQQkjlA2u0lqXW/cSaT27BxnEPYeMzV5hW2MxmNdZH1guJ7xzM3iy0NgPcHBsVrYZV/BF4BSxyzHiachOst81DZj+2zuGMSr5nZtqWrWDRHuhYaz80xGPhdXhQzMNa+qRrnF0z1+2wgVMRZuceDNnALszy3xoW+JWYLbjakTb3I2+XYVa2lrVW7yfMuFTzbKb4MfJ9MWai7M2z3sImPLc5zrnSPE5+5cfM+2oR5xthxmCw49woeAdUxbrLpZgNexb5MgwzbPYnERtaMxXLsFeDb+19EWb8t3JsTDgVey/MwKxq4Nm5/g9sWlU3xhr/AQlnM8V7YwLyeAnWz+6epQfAFkb5/hteS3kh4Qfi2MMZvlsPYw1rnOdrlFr7BQHzvY7ELOcqzFL3znB2WMezGrNzMyN2RH8Lxw5zrBd/DmW4GOXl/Az2AChAOzAX5e17y5PElK2NvRlqhsS3Gu1ONWv/gNsd4R+39ifJgzdSyiprcdM6230pClDWP87SA6CTQ6KuqYO2ZxXamDlog837v43y5/oKQB1sULcCZfhax74zHyD+4Wg77K8A3G6UhS8c+0+40qARPHv0c6dS635+LZceAMOtPVceLEcPgAKs6V8CeSK17heN9Eax+isA9zm8Uz5COr2eIB0C7KExBfkyGWvzzfOXoJ9aZvUFB2GfgpXYfHCh4x5V0Y4sS7m/0HSs5YmkN0O0N5bVnhm7YFZ9RWrdL5W4Npw+PGYdDqyNct+P8ADQXyZ6jl8BIIRsKORZBoCyuo+sO21Qzu/WEhbpgcHatZzmzJFYhQ/I4f32hJVarO7PJ7y2CizuF3tmw0ju0fl1SpD2QqkoTsLsksyA/cBsIWWEzBbKzP4HQdqrgJSTXT1Ie9eIh8F8x3mZCT89SM+i6zXb8r+s+Y7yJjPvEdq3/4MQr0XxNJN9ADoE6f1anke/mykye1uM+nH0BlSu4paPTML/k3gYdUw8UYoSXvsM+uiuwVpvyFZKJgVrPVtkrb94DYiX1ZuxFO+8vIAQQiq6My0PGlTAu81Bwyyu5yONwZW4+oo78C45vp9swDMkw8GkuKU1ZXEsV2S5gbj/vVTBzyFu/LJB0TdQHqSciuu6bFzUM4i3+RQhUYhL7b4B3VArgu5BerPBGxzn+kJMRiWM/9iNKC37ok8X1/hDcWxkFvHJsqcz8f80FtV/HI8HaePQ8AwG/1pflMmijsG6yyFNmuIebzK5CSEbCuXlAVCRXIlBld7FWdaVylrGccx+UkmQLxiI94fsNiyzWmuCtevJVzN5CNlgOQZ/fwrie/iIt4asWRZjzedMwnVoF6T3S9BfDpIvxNyTRXzXBOkv04g+0AdxbgjQAyAe8lUfMezIXjqzKo3iTQ8AQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCKg15TAJCCNnwSaVSTARSGRiOvyuVnJDguteUVFeyWkkfJiP5xyreeVS9CSGVyABQTgpkeyWTlNSpJGnQQMm5Su6wjl+nZJCSZSwmhJDKrkjSAEAqCbogrkjYzxcpqaFklZICJiP5p7fbG1mbna/kViV7Kdk7IuxXSt5WMlBJaSb9ISEknCqezrvIc8x1TsdThMH9K0pu8NyvuZK+QdrKf46Sho4wFytZouQPJYeZddsTp8TxupJCXHN+iFJiP3t9JR8rORONk0aer5+SD5TU8sS3rZLiSpafjyiZ7Tgu7zc9SM+sTFFykud6yb/bENbkFCU/4HpJ4/uV1LTC9ECjLWHmKXlUSe2QZz08pDzpsmbKF5545L7vKlmk5HJHnvtEI+9xr5I5StYo+U3Jv6GImhyr5Ec8mxiwDq7E9VqMWi8qWRqkDViv4JiLOkaey/v/reQNJbtE3ON8pOP3EQMBLSVKfsW9qlvhWuB5F6EeS53cNyI+yYevlZzlaBt8eT4gYRihFZ5tIe45QcnRMdoWsxxHhQuLy/5dH+koxwfFfA5X2ox3nJvoqB/6974R76bz8WW030vwf/OIvJH8/kTJIY7nSRpfCdo/UTKrefqpS4y2bD7ibJOg3YiTn/bxCTh2lRXuSBxfaPU/r+H4qcaxn3CshZE28nuBFeetOP6tUS8K0G6n0O9qGmOQLsd3MI53wbGlVh8dN10CDOLNwf93CLNTSNkMG/T/hPahRsK2cAe8+8+oO0kNGUVl1EZnGnd79HeFqBO5vKe0p3856pjOvy+zbMvIxo30/VejnwnTpfPQZvZXchOTjZByQKyRqTRF+N889if+zrXOiWyhZJWSqkomKjnWEWYrJQtT6/KXkq2NMI2VFCvprORfSmbheG0l3yvp4oj3JcQl53/H/3s6wgkLrGPP4347OMLvpqRUyUPW8aZKNlWyLa6VY83x7kEFSp6SOUoetI4fgXdfomS0kuX4fYARpquSj4x8MfP/dBxboeRdIw8fNsJ0UrIa6TFWyW8IM9jzrNWU/Owpa42M8jbckDsd8VyOsJJPXys5",
		"yjo/3JJ3EX6GVQaEeUrGoIwIjxlhDsU9dBrIM69RsmsF57lPXsA7/KhkGv4f4gi3mZLpyCepAwVKmijpi7J0Qsg9PjbKy1aeMEIJ0v4dJYtw7H4jTH3khzBeyYe4Zg3KpS++MSjTrnJmhjPl+IRhpCzORthvUbZX4fcRVlxFjvcvwrmocEFIGPv3i8bz1LDa77jx6zrTxDjewmqb7fAT0Mb43q0uypLwFcKnUM9rh6S7zm95niONcHWMsjsBcUbF96bRPrnai3/j3Hwlb6N/EX5VUs/TbpQgjHksKj/t4zfg2Fgr3KM4/rx1/Gocvwu/6yF9hF441gO/37WurW+0Ybo9vAC/JT3zrfAP4tyjxrFncOyeiPZ0uFEfvohIlytx/L6E5V/3xZo+GbSH0s69qqRfwuvi1KdMJdO4P8e1U5S8leN7DlDypJKajnO3K+mfZVu2scv/bzMtnXtjkb/w/vWs46YuraWJ0TbHvgchpGwMAJ86Onothyj5Cf8v9wyon8X1YiBooORc/H7HCLON0RBsi0GA/H8blMsajniXQkkTBXRfxHmtpzP60TJIiFL1WkiDMgYD21bGseuVrISyKfd9DkrQXjEGAGUpe+Be+1rH37UG/Efi9wir4y8xBnVm/k/Bsb3xu7MxQNdhTlUyScmF+N3aULRdz3qpx9igy4BvwGpKZzyzKLu7x0yjfoj7euPYChxrg99bOp59nDXoOwW/X6ukHa3UiUIMlJobxjbbCCODyCs8cXRAHrdynGuBtNeDowExFcBOjmcZ6BiwneUZMNnxNUJ7krKMP7lSTm9HuCettk63h+VtADjOMMZtZSs8CeLXg8nTjeP/ss7ZBoAU6rnv3W50DCSfxLFrItKgjzHQ18euc6T9Ezh2dUh8u+DYH453X4j32wy/axjtW98opT1BGbKP6zZtJYxs+vh0R9kV6W71jd2NPLgNxy7D79tDDKMT8Y7aIHu8Z3C8Bsa0OjAgrECf1iKiLOl8W4V3DEuXlmgv/owwlruufRQGyfEw3JRXO1oZDQCFuLZmBb/Pxm4AqEIDQM7KjMsAEBhtJg0AhJQBVRKEnYW/vzjcvN5R0gn/i9v3JIdLYHvDzWyxkiFwy2tshJmLvzsq2TVIu2VvEaRduy+BW6FNMd5D3Pt2x7HZnnf4y/j/JLgaDQt559fhSnqycUzcxcUFuDXuW09Jb7xXRXJUkHbfHmcd3xl58SF+v2cc17wKl9J9HPH+N0jvj/AJfk/DX9PF9nnk2SDLldO1f0JjuHV97HmPFo68cnER0l9cyr6ImUay14O4CT9rHJtvuJ2ZLLDSsATlXNCbXO1lhNGu2VMtV9b2uMc4zzOJ6++JQXr5RFw+D9KbZOV7zkvZbBak3XvX4FhVK8zpyJ97jDr3tJKn4JIn+fyckn854j8Gaf8MylbcDbskTlnPZy5H6IW/jxvH/oNyujIivoXI/8DznNlyuFHnNaOQZuPKuX5LvXgM/18apF2iM0Xc32U5i7nEqqeSyTgXONr4Urhw1gxpf4SHjGMP4G/viOfR9amDI777jWMPxohvAp51U09/l2e0MdKfyNKeA4P0cq+yQpYcTEe7oNe+tlXSDmV8jBX+a8M1NkBfqJ93V+ucq9+RpWCylKkz2vZW6JNfdYSVNmso+jHZsE+WHciytxeCtOu8j4ZGXt+KdwxjDtJY2qUDEqSdeLkcjzbhJSUHIY5sqY22bgHyYDTaTZs8pKe0lbK0baCjr7gY+pHUHVl6cYgjjtvQD8iyivs8zyTLM2YGabf5T4N1l2XoeqjrX6FDx+qPfnM52vJfArcL/q14HymTu1jx+1z2w87tgL5mdRC+tjuFZ5K0WAI9bX+0/Svwez/HNVKWB+Aa+X9fR182FfVjSrDu0hkzjmeRNn878lHahtuNPBqEMm0vx5L0HWn0q4FRn98O1i7NkDrVxLq2hvG/L13tpVUf4rdecrgHfk8ywozEsR3x+x28p9bRFkGqWGUlhT5cuAy//2O91/M4fo2hv5XgOeta7xG1LCjwHAuDi/oJqWAPgDAZDlfKaZgpXelwlTQ9AMQN+OCQ+C7BbMSfmHEdbnkJ2PKI4RqqPRSqJXClaxcSZgeE+Z91fEdY4sWl/ksl1TOYPcq1SPo/7The4vHoWJGh1V7P3g91nDsSnhHzEEcvT36VYjmH616n4vhUlIMlcJGtb4Wbabjqz8es9yCHi6uWPRH+Tet4b+TlPOTnfPw+3Jp1KXW4HhdaM+qyLOJea3agAVzUr7Pu2xAzmb+FuF2nItyyf4VrbYOQ/HoKYe2y8ZmSEw1vikIj3mUo03ujTttxao+IXQxX7+0iypKkz9k4NsbywCix3MuTzCDUc3ik5Gp2Sj9blQzjyqUHwNv4f5hvxiNh/HejzlRDXi+Di7zvmXX7faPn3ZahjphpVRXHlkakwf44/oMjvqoJ49vRcJEOPO7uxUjHo0Lai1x6AARI7xT+yu9zjKUFrrinG+6yw+DpNAL9Zx76nZThzWBLX6vtOCTkHbdDGFlGNRllvmNEujxrLEWpFjNd9HKyFxOU/2NxTLy8muHZrshBf/kY4v0J3muufl4jSwtHGcvnznak83x4262BR4SpV5xv9LmjsYzSfs8TjHZsNM79Ca8MU9eyl6Toc2cbM6aj4THhakt03fgW/38Ss33ytUsNjSVc58a4RutqkwzvkVkoe7o8BZ5rvjWWGNnlYynee5ljqYhmNsIUOp73UiuP/gh5/t8dOqmuj1+iHUuhzDjzLqTNttubSy0PuescXndXGh5d1Y1yKv13W4enrV5i9RfK647Qf9bA888Mdziu/9AqpyNDlgfNdeST9kSclcADQC87bkQPAEIqpwEgQIN5PhqgTzxh2hlrgFIYgO8REe+B6CC2DAmzi+G2+qVjfZFP9FrRMGNBfaPBN4+/BRf1+mg4+3kaw7D1oz5jStywpmyP+xwaUxlN0tGbshfOFcKd2z5/hZG/MoBvb53fGp3MCyH30srSb+i0luL3Sx7FfKG1t8ENEevieznc2SdbyvIPlvurHvDeDBfec419FTJRPh82nlcU+setZQzDPaLP74y9KeYhjuXWngy2K/107K+hjxcgH7R7/1gosFsjD3WebOJYxtEK9e1PDET64x63hKw3N5lhLStI0t6EDbgKExhQkoQpslzafWvBUzENN5kYAEw+yJEBYD/83x3trLBPiAGgBcrZMgzE7HClIUaQ0pA9AMYacZ2WZXzmHgBnevYeeQjKZsqoG3uXgwFAGyAn4fcwxzubMtTYz0YPQPXeAJ2QF3+HPHct49nnxjCwvW2kyX8jwnY3DCk7J0iXuqinyy1jati1R1jG03OtpSiZykmYbGiEZRLFWO5nP8saDHIDTFzYyyC/wbEu1lKYS4wweuB6kLW+2XzPL1Cu2+L3NQhzXMzyONFaptbA05asQdmojfsVZmkAeNuxVCfsmjUYfNYy9KMmyINVDoOr6xo73cwljgd59qRYg/IXQAfQ+qIO852VRw09z19s9aXmJMEiGClrID0ei7EEIMoA0NZ61rH4vaNj+eeDxjJYbSTojf+vczzzBYbxKuV4Xr1MagnqRl0seU2F1MFtkY+FlhHxJ+TdvxIYAM5HGf3BMvBOQfzP4plqIr9P4yiOkPIzAGglbhkG9FMwcPMNXptjHecKo1HumfJvFPcjZqUuQiMkVu3DLAPBCig4U2H93gsN26qIZy9xdPiudV6u2fI6RiewtUO5SsUcYEQNmOIqMwOQPtXL0ANAGt7FOH9iyLNUNTqWMda5UWi4W0Xcq5mhIO5hzBTUcHTGraxZxKmO+DYxZlTsGb+RxmxAdShuthLcwxo0FBuzEpmuhRNeNpSSTKS20SG7yovuKG1DzOYIXxWKTokxw3Ar6lmAtFrj8QB5Br93CkkLe7A327MHQy48AOamojf4CxKGKbRmtX8JGdi74irJoQFgiVH/TsiBAaAa4rwfiuMi5HeY10J/w5vE5wHgmrFfFtLGrcB+Cr2t5wyLb0lEW3tvRBrIHiU3GbN8K1AnytIAUAVltBTGlMWoW77ZLT2r19/4q5X7m/B3dMg7XmylSdTmefsYYXeJ",
		"MCzoGd9/Z2BEfgXnT6ngdeOboe1fksAAWAPHFlvlw2wj81CP7A0zix0D2yLH2n6b62KWxyK0N/kx9xNJ6qEUZpgs9dSfpPfX7VtBgmtWWmmbj3RYGRJHgcOAvypGHoWlzy3G5IG0qd1i7gEQ9X7aOFEMQ0mhYxa9Oo5/jOdYhhn7ccZz7ePRsWcYbWAzz7u9aOxV8ifSyuV1mG94clyQcm8kvn0CA8CuxiSHORmzAobwUugU2pukG0dxhGRnAMhkIJN0oNsQM+h6oyKfq/kcdNTFaAzOtho/rZCfB2vjYrhKfuZxAQ2sBr8kIkx1R4ef0aYvZSzfYjDpOrcADWU1YxbG5dUQ1sl1NLw3rnFc0xizUrUtRWmRw5IdVV6qWkpMvhGmhaUsFBuKVjXDFdB+vqtDFNYVVsevlQP7ixFdMegdbMysP5sDD4D5+L1rAg+ALrhmgeEB8Ehq/a9ClKTcm2Z1NAwAembyaJx73HDDrO0o+5+H5OGOEWWpCcriQuPY9wjX2vK8eRHLF6LK5sEOd8tcLQHQM3fbZujaHxWuLWautggxOGoF+2DD+PK7dg3OwgAg/7+OpUPTjSU9Yc9cC21ySWr9zQK14md+EUJvfjchgwHe14601/F944nvYGNpTG2H99IN1oxqfUPBvCSDNlwP/vJi9hl6U0S9bO39kPffz3CZ1TOTtXA/vfzpVs+1dY33et4wjObnoE7cYxj8CjKI51CPcbi8DQDaq+sw5F9RAgOAPXBcE0PXiBpcrk5Ff5UkygBQbBnMysMAsBJ/X6skBoCqMQwALkNOtgYA/bWKuzFx5TJEZmoA0Bvl6rr3gOPeH6Jcjodh63KUqQ/wbgUR7cSakGU/RxpeFa7lBOZElK7beQ5vXu35G9cA8IPhBaWPvW8swTkU/dcKrdsRQsrPAKBd+9dgAPZVyr3TcDPMfnxozST4BmxN0DifmPJ/GcDcwV3PKPY0OqY7I577V4SrHxKmqbFOsLIaANrhHsd6zttfATjcs4bL18m1MWZufZ9wuhDnL7WWJMyyjD62cmPOnOpw/8HxM1LrfgKq0PJwGKWtvlYH861j5k0rzB0cz67d3/Qa9t2N9YKBx9jxIQZAu8XMo16pdfcU0C6aVxlpm0rgnp4ylklcbbioujwf6nrqox5072OVD3FNfg//7238r8uCds0eZ4hO3zsiylJTx4zw7cYMpz52Jo59FBHfJobrZu8yMAAMMDw1qhiGplU5MgBcYHlTdHa0N+Y11XBOuCsHBgBznfipMZ/5dE+Z1J+6eyK1/q79N2YwwLvB4Vqs4xvoiS/PUL7t9r+PbTxBeuo9OC7OoA3XnyY067Zek/xhyv21HK1sp1Jrv5riEvPTf6XGjNtEI+17ea69Gec/xaBf7ydwTpZ1Ymf0xaURyybC4smHMbkYHoEVZQDQA+4aaD/XeAwAppfGATj2tRFGzz7uZNSpydbSDm1IPNDSK4ocSwn2NvqtfRKUx4mGQSNsCUAuDQDF8IDU7f8hFWAAGG8sZTI/jznekY/1Uut+GvlzRz72MPr5uAaAzeGNc7thhFhgLa8IDGNJFaPN1hNRNWG0dJXDnQ0dKOXxLrjFaBfOM4ylKUyIhXkt6PbhdU+4gtTapZiplPuLKTvh2Rek3F8PqWJMVsQ1AJTG8OTlHgCE5MgAUB2zE3clqHQHwwqnPz/WOeX/Rn0p3IiqpdZ+Su0bz4ztx0ZDXAy3xBMx66/DDTEa97GptRsBCoMinluvwQz7lrt2uXyhjAwAcZUdUZoeggW4isNVdGXImsojDWv3KKMhPyjmM0010niEZ0a6NRr2NTA4/G2sQUuqcPYwBpljjAH6g1a4vVEu7M1/zvDMOH3keYb7cV7vJbDEM7t2EuIodAxqovIoSiE+LuX+vGYQMvA4McaM3umYAWztqI9LcN9NkG+SV1siHSdAWRqD97Y/LzYs5d7EbXqIm/0IDL5SqXU3kGycWrth1ThY+ItxXfeQ+MYYZfm5mO79xyese/VSa79FL/XgLcPr6K8ceQBoBXCsMRtzacg1eo2rDGA6OQwApRh8mnK6J77mCC/33zTmM1exBqHmsiidVlI+9aZYM1Lr7ssSt83zxTfbcpu34zvHSJ9tLHdXPWD/A3mp+4tljjoSpw0/3Ei/T1B+S1B+u3s8ykxFunVEGkx1GIQeibi+idEW9rAMPX/A8J5pfzTJ6EvCPJSi4tGbMV5WgQaAyYYH4q9Gmuan/Ju+LXEYi3Ta6k1ki1D2tk6tv6/NcvTBrk0ATzYGeaNR9osdRmtfeTzbun5OORgAiiwdY2Zq3c8TlocB4DhjImmUUfaPT7k3ARxlTByd6TDG6jz6I4EBIN+oq58Y7Yzt3aqNjR8YbfZXhh48LcSDdrbhMej6jOZBxrXtrPvd5ZkEWA5pZSwF8OnDLzsMYoHDk29mKnzZHT8DSEglNQA0QscxNRVvJ309+/tOau0un76BaJ/UuuuodWNwUIjybX4ZYHFq7ZcBTMvk3XjmYjTagzE4KDVmNV1yBp7hqhgzgEeXgQKSF2IRdW1G+Bsa6ZoOl+wREdefhWtXo5M5PYESGHeZx96wuq9GPtySCv/ec1iHcBQ6xNXI8397yuNhmAFehcGna4brTdzHt+a0Gmauf0cZ+g0zjFUdbngLoFwdmiCPqnmWFJSHvIjy5ZqtGw6jQxUYkVagE++H9xCF6jbrmvGeGYD81NrN17qErBMVJflph9eNDIT/CwW7EAOp7hFLjopQRs5Jxd+DY0AGA42mmKGfh/IxG0sT2uTAAKANqLqsz8HMd17ENXrfirEOA0DS9/7ami2L88zdPG1ACxh3lqD8iFtwyywGeGZ8awy3+Toh8dUylsZ85OhT7oRnUjGWKL3lMVrHNeL2xAxbIeQTY6Y3bHO/CTHe/2XHUqOTHQYoUwY5ZjfzjVna67MwAKRi9gdR8ewSYvwvLwNAF7R3RWgnJ1sz+fpZvofL9VKUqzsdBt6LkL6rMdt/iKOvvwWDt2VYvjXD8Z5nwCi1BmX0nITl8Sa0U8uxlCuVCt/kL1cGAL0RdCq17jK78jAAaI+xaYZ+c6bj2UVHeBTp/zfSys6jW408GpRwCUA76MGFuH5kau2GjuZzSlu2yGiz90LZKYS302+e/H0Yx4eELPspNibjAvS1KUtntr+CcbvVrviWJR2N8+8mbBtcX9XJj2EAqGUYPGgAIKQMyLOXAJQx8l3ifkH6m923KHk5SH+LtiKQbx3Lt3vlO8DyTeVS67x8Y30q0mjLYP3vvmZLO7z7R0q6ZRiHfNv9eiX/U/IZi3OlpKuST4L0d7VPrUTPJWXuA9TB85UsZlZtgA14Xl55tt8ViXzTWr7jfZKSYUqOZu5X3rkE9KevKTnBE+ZqJQVK7g7S304PEP7YIP0994KY9xruOd5rI0z3g5SMwf/7K3lPyTToL9lQR8kySL0NtDwmKVPZXhe73d6A2uwrUFfPVvJkhnG8qeQw1M0RxnHRvydB59Ycr+QVJa+jTUjcHxJCKpcBQGiPyl6nErz/cUqGKrkKjZvJDTBSHK7krTK4980YvHeHEYD8M5GO8yIluyn5s5I920AlNypZqeRrJTIz0UTJHA6waACopP3VtUqeV/I7c79SD7iEFQn7+SIlNRIOulJxdJuNgD5KXlXyrZK/leyNtLxUyQNZxHsa9KOtg+wmK2gA2HANAO8H6YmM1UpaQ0/IBLl2VJA2IrUJMQBI4vyFNr5nEr2JBgBCKrcBoLJxLTq4TZUU41h1dKIyOHqojO4rjeB2Sj5lMfzHUx2dZ2XkEBgodkGZ/EnJvRhkERoACCGVn9pBesJCPGQaBWnvwkeUPJxlvKIb3a7kOyWnKPmBBoCNzgAgEwTiIXiBkv9mGZcM8jvGKEdiFPgxWN8zlwYAQmgAyCktlPxhHWseVL4ZW0IIocJDCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGE",
		"EEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQsgGQiqVaq+kSEkAMX/L/8uNc1rOVbIv/n9GSXXr/LVK5iopVTJNSSfr/GNK/lZygXHsZSVtHfc6U8lMJb8oOd1x3n5+Lacp+Z+SPONYPTzPrgniqQj5XEk361hdpJGkxXQld1jvpuWoiPe4AWkp8XyiZCtHmBOU/IwwXynZMSS+hzz3a4/8n2LIWVaYOkqGI08+U9LSOHeLde1sPJN5vaTRt7j+E0c5k3z+Dun1hpJalSR/bWmtZKSSGUpmIU1aOMJ1UDIG7ztVyTGe+LZPpbnQc97Mm+nI490c4SS9hqAc/OYoc3Y87ynZO0Y5ENkpRpgGVlzSzjyCe0lajVDSJKQO2+3XZFyn7/WG452/RZiikHjbKJmnpHvCNqQ98uUp49ib1jPqMOeFtMEFSgYbbcFNEWn+C/KxvhWumpLHEY+UqStj1GMpn+/iuB1W0uNrPJOUl1fQ5urzgxHHDCvOaxPk4WfoE8z7dlGyREkN49hCJVs7nrFQyRbG7/2U/G61DVKOrzB+Szm70YrndSW3We2qWXYlztURaWm2dy2QZvVDyk83I/1c5WwHvN9pWbZHByiZgHYpyXVl0Yf6dJA4cg/S9Ccl48vgPdqgvUgaLm7874Tk9cYm32/o72Do3HHlfiVzUOd3CCk/xyDMH9DNEz0PIYQGgCQGgEFKNsX/L1rnRIEphoFArr1UyRPW+RIoM9MNJew2x31ksLFUSSsMLObG7KwbIWw7R/jD0RlXMY79W0k/JauUnGgZJspbZAA/2nFcjCZPIk1E0f1AyRnWoOBEKJ4+heFIKER60HSlQzFqB+VZp90lSr7xxLc7Op6iDJWoe5U8aBiNbgwJK4Omy6zB4AIl++C3DJg+ta6R8nUy/n/aMVBKKtUzUK5PcxjIbPnGGHDkwfjxrhWmMYwgxxjGgL+sgbRpPBEj0kcxFdzzPIrsg6jfUlcaQgn7V0g8++GZdk1YDuIqxHcp+Q8GrlWg4L+bYPCY6fOYv/MxCL0ug/doj0HhdMTTAPXRNgAUGmXZ9Q53KxmqpKqS2jDgnBjyHNVgqH3eimeAkv8injooh4fHeKdrkAa2UWKxYbiU36OgxCZJp6g8vAxGE7u8v2QdkzQ5yFGHVuN9zeOvIi3k/15KfkSa6fOd0NZsgt+7oH+pG5LXwx19WlT5kH7o1iwGqPehLv8vR0bJ4zdgA0AzGFuaZnjPshx0J4m//T/QAJCXMLy0cSs2MgNAU5TfhgnKRFdMrNEAQAgpMwPAUKMht5XKVjAAdMK1Ta2Z2bYYaG8JhbEqFMU6no5iOZSxfpjljdMYykDyuYgBV29rxvR1NLgyy7lZBXXEkhY/KOnsOLfQSsdjLUVPBrgPQwH3PWdnSykWq/IihwHAVPy2g/LrGgx/ifgyNQD8gXIQlS47Ysa7mjVjVmoYcrbFrKw+3xLn9eB7LzxvnEGeLZsYnhODE+bpYFx3gzGACKznfMdSirZBfpvhZDDxLAZyMvg4H8axIY44xShzMJSmpjHyZjsr7bQswDmz/GwRkWaXoy6VhQFgnjUTUtOqq+VhALgH3hp5GRoA5PxryJ8z0H7aBoDFMABs4XmHeZZXzskRhhBd1/+yjs3GYFb/PgMD16h32sbRJrRBfatlKbHNcmwAaAMDSW3j2HcYuNt91FmGh0AB0mCa456tkKZb4PwBjjCPGsbK9yJm2o6Ft1KNhOWjIQxCzTKoL/kw4uXD8NemDPqnrWBYnAo50PNcV8HbZorDw6wVDNxT4XlymeM+ByEdvoHR1lWHxyGvfnB44jzo8DJ5xwrTE/eYqORslCn7PSSPJ6Gf6mX101NizM5f5gln598rHkNZVJnpCGPVZzAeTYAeYJ6XCYGLUDak3zjaiqO54X02E+1RHSuO+UquRlr/jPpvxnEw7jMRhvyVxrnjod+dbOR5H+v6i3F/8dT4An252T/aeXlBgvbiPIfe+KCVTm+hztrpu8jqP5vgPbcxDIq/Q3/UYc5Hetpel08bOvdQy6OqJMs2MiMdlRBCA0ASA8ABUBB/x9930SHcbw3af4R7ra2oaWvuGsw0/YjON2xW9W0lY3GvFjEbPemIDg2J8xrLcLEpZjd7QbnLqyADwJmGccVlDc63BsVzsnzO25C+vvM14HXwiONcfwz2wjqjNSgH0+FGu6nlpVEC5UQUiw9DXE5HWt4OupxNMmbEr7G8UZrDlbqmMcg1B0CbGx4ort9a4X0CiuKtDsW8u8NtfQoUGns26lbE84Rn2YUpNyE9bBfIN2Dc6o56+QiUqsAazC+FsUTqzTkRZSQP5cA2JDRxlLk4ZW0XDCxzbQDYFPlZLeHAPZcGgMPwbg0yfA99/kQYhkbCEGkbAFZCcb3J8Q46X6pZhpk5Ec+xJ5Rvc7CZsgapXaCQhr1TAbyRXrfCVcGg73Ms1WqVYX7HycMvjYGMGJSX4bnstm2gUW56QkZ77nstBnqve843wUDobAxU8kMG8X8YnklJy97VMDYkrS89DQOFGMuvL4P+6R1j8HUG+m/XEoczDQ8TOz3Hos3XdXquY9nQNMNAf4cj/z+FZ6Eus/Mc+R+V1jONvuMJRx0sxWBOfvdFH5VpXxumY12PdqBKhnWlFJ59azAQ/9PRB19gvMdPVhzvwoNGGzZE/3jAiqME1+q+6Q2Hp53OrzuttOwCY+HLDoOYHkQXG31rL8dSpGzai8Y438p4x7mYLTc9Ea81ymR11PeFjvv1Rhsn+fUC9A7zfAMsR2psLT3r6vEAGGykv73cb2XCMtEOk2s0ABBCMjIABDEU8QcMd/U+nhmVl6B4zXcoQwOhaJ4H66vPJexwhPsAv7fGtUHEoLXEGmzasj8GaqZypzuEIyyX7Ts861bPyLFyVQClxLW2VntNmJ2b9qDIVCk5Fh1cx5DZi8WYXbCNOFvDql415H5NMajsAGX5Bcx0mO9UCpfyPHgvDPN0hPM8bvSd8YwLMDBraZ2fijJWBUaqxQnzZA1ms3K1d0AtKPhrQlwjB6IcdLDKRinqwpbwBElBKVvoqFtaQbsCCnfYuu7fYNA70lHmVmcwEOloeZW41vd/mEGZ3dx4nuqIZyq8K3z3mpFDA0Ax0qrQs7Y8iQGgDgY5XzkUVh2mMRRH+3xbh5JntwX2czRGObghYTx2mv4Cr5IHPO7vjaHMTsY1H1geI7kyAFxlGHAvsdqVwBjsDDEU9n9j8P6I577bok6FGaOvR5gjQsI8A6Nppoaumkjn9gnr3WuGN0eDmGvTM/FQyzfq+TLPHhd1DWPgb9Y+NiXWDHMtq/9vjDgKjDiWW0sIS60+6StjT6K4Hl2mcXgfzz4cNY0lIEvLwABwBPbMqJ2FsazEGCy2t/Ik6j3qIi0bGcf2tgzhdp7ujP4ibn51wPkOnneohzb1ahjty8JgOAKTFfJ/D4ehvx88Auoj/S5EOnzmuecLWIo2zmO4ednYw2U7fT+HAeA4GLOqOuK4At4QSdKjFpYAHGIdfx59pXiMngQ9qS9HP4RsfFTJ8vrtlHxn/P+9I8zvSvorWaFk",
		"oJJ7rPM3KWmrZAsltyHs+0pOMsLkKxG3qaOlzVSyk5KD8X8YmyDM3yFh/lTSxPg9T8k4/D9SyWrj3LVKOik5CMc7QZ6NkVZTDIniQiXvKpnuOLdcSTW81884VlvJsgzzUBr/R5QcYsRncx/SaKKSwVb5kWvPVVISco+/lJyuZJqSYiUPKulunF+F93nW+NvVEc+pSv5j5Yl+jpfwLo2VPKHkUSvMKUrOVjJeyRwlSxKm0zNKLlJyg5LmWdabFkpuRD4/4wlzl5K9lHRBumka429zlA/9LHMc6XKsklH4X8pTN+N6E12WWyvZEuX7XuP8UpS5GgnfU+610HMvLd0c11W36suX1nn9PAVGfIeivvvudVCO283zlDyJ+pBNO7ocbejokDALlMxUsqt1fBnSqrpxrC7Sx5ee0raOVXK7Vf+qWe9R4ChPZprug9+ve9qeBSjj26J9l2d6LqlNOsYxuX9P9BFH4rfNDJTtrmgX9kIdnBFS955BX1TTE+ZVpNtIz/n90UddmUXZWIl8ujXBNQ2UdFTyFX4vVjJVye451h364B7SNr2jJM9TVnTZkPa2ntU2lKD8awqt/K2HOIqMOEwa4u/XRvluaRyPQ13cY6XRV9msMs4X50BvspG69xjerzCLeNYg/XRfnJfgPRrj2EJLF2ockqfLkH5x8yuFe0zzPL+0EQeirE5Fu79bjtP6BSXH4/8THW2SlKH2SnqgDTgAfeJPIbrRMdCDSj16wyn4/wRPG7i5kjuh89p61FtKLsOzJqEQdVTaw38bx1/G+4ge0wtpvAeHQoRs5CScAXgYbtS/YEZoMZYA3GC5fB1nWGK3cqwz17NNg2F9Xo2Nw36xNiEqMazK43HP7SOesSVm66LWMi6rRBsDNYBVvUVImL+ttXcneNxZo57zDMzK+NzQd7H2R9gOXhz69xZwcZsL+RsW/rnWTEJLay+DXa3ZoCooHw2N2fw/Hc8zEe6tLi8Tew+A+SHv3SdiuYNPGmPDt1mYUdw+4RKA7Y2d9K+zXANtD5Alnl3AWyKNVxqznil4soxzzGIuRd1cbLlvRq3rttPvN9Rn/Xsnawd2VzzXWRuy5XIPgFlwZffN9mSzBOAIY0PFbUJm1GtiNuXyLDwAtKdStYh36IOlVvY7zLU2fzwNnlRJ0rMqwrSzNgmdEPFO12NtdhVHuIMcy1EWJkynZiizVT3LG8x24UjkU01P+/ADZtgaYJ+AZx2eLjrvv8M9ZRnRzRmU05qWK3Q25Tw/tf6XMip6Y7h66Kf3Ntqa5R4PgALPciA941zPyqcGjqU+BcbSleWOOGpn0aY0sZa/dM2gHcnWA2ANyvrHKf/XWuLOfuvnS9oeao8Ms9/ex1pWZnsR2HkalV9JymoN6JLTEqSB7fbe2ZFXNaCDbo32YjOHt+JMeO90Rp96Z8r9VZQ8eLDdgues6wmjvTmnwXvN1Ln1RrJ9IjwB30lYJvLRR57EJQCEEN9MVqZcoORNzDZ0wkxjR2u2oil+61kUOf+bIy7xDLgJszh5xqyVZj6synth1mEJZvtmRDzjfMS3SUgYmUH9M8fpKt4Kkz2zIrbl9xfr2NVKXlTyR8h1Mtt9BfKvJmaShyR8xs6wXh8YYt0Wi/6gYK2HhMyyml4CMitZX0kzyB6YZWhmzSR0xixRE6RJP/zWiOV8hJIz8fs4JR86ZjG3x2yPzd+YSdKzkvsG63tPSLk5XElVJefAEu7LhzaY3djMMat5OyzoY4N1Z+/fs2a2tTxozQaMRT24HfEFnhmn5oHbS+FvzPRIemyK/JNZnW2UDDPCyez/B8jDBpB7MVsRRh6utb15ZLb7WtTROkoesOqojZSFi4N1PQlyySNoN2rhd4ccxi3l6Hr8382YTXXN0IrXyc2YNcqUVcjTMGSmeRfH8SFoM6Rc10ZbMDjh/UtQfo+zys/7Edfdg7JwlnW8lZJXlOxglKneQdr7Jglz0Tbrei1eSp87wsks14Ag7eWy0nF+Dsp/VcyIf4mZPbv/EA+X+5VcijS5Rsn5QdqDIQk3o/4My0FZlBnTG61ZvIqmBtqBH5Gmp6MtqOaY8e2F/w9T8plxbhnapzMNXWEC2lazrZN2+WCjTAZWHB+hP9Gz2C8Gfq8NF/NQxvQ9TqqA9CxBWe8LPahDBTyDpOX/lFyC3/loS2yPmlIjT3taddrOr2MSPsOOSt5AOZI28btg/Vn1pShrbYw8N++fb/TbR3jaWnmnO4K0R+Ov1nnxABHvp62VTFLyhZKjPDrSxdAxpX6+hrYjcNSBIegHf3foewMQ92u+eTnoKvskTMtWkJc5zCGERJKK/y3bwPrsX2usj3dZLwdhlkqvW7bXJPWwPvn2IjZOsjdUOQXW5mnwFngYM+UnxPis2iERGy29nOMZkunY/CrpbEBzzHA1jPEpnBeRntMsrwv9Kav5mHHTey/Mt2ZKnsYaXnvGuqkjfWZBPg9Z8xxlnR9o5N+rjtntplgnPB17CrRwfIqqJOTeh+P5Z2It5Q6p9b9n/TPWgt8X8dzHhaz5Kw+JqocfQ97E5/bGoD6YeyP8aH0OznzPBiFr5Wdi34A2jlniB5B+v2JjtTxPPDPgpdM9Ff7tcy3nZDBLJPe+PbX2u/XjIz5LaM94Tbb28njD2pRyLMrrJMtDxvV892G39TzHbFmxIb9HxBM1azfYM6P1NNJhurGBVdL03AkzY0+hfs5zrMN1xXUIPH8aOtbd/4g0no51ss0zmDk9GPV2Ktqfth4PslTILJquDw/h/1MRvpZjh+4Rjk04hyd8bp3XdjnfI8PZ0Dysbe9eiT4N9zD69c/xVZWJlgdSR8yw9of3xY+Otd9tUM+mQc71tOu/ox5eau3Qr/ev+BDX/+TwcIqTRsfhXb7CMyxL0I7c4tkXaJsMNgEM8I6fWV41d8S4R7YeAPprOm/jPiKPWxsq6s+SDkCeTrG+RqTzaw7Kw1UJPQCqoI7OQH2fiLLl+grHMug09h4bt8B79G14qLk2z9snYo+Pz+EhpL9CkXLsw7ElvOKaGu3wD9gc1tWfl5j3M3TuEuhWZjuxA78CQAgpa/IsA0BZ3ac9rKl1KuAd+2MG53TP+YmYSRyeo/u1glVc7rmaRWyDRGa3ZQ3io5X0+WRm46kgva5d6pXsn7FT4F7/TEhcpBzdEqQ9aMSD4zcmSZkhfeJkzDZWhnhIGtnLSLxhmpRR/FsFaY+iOhtomRXPlpoJwk/aQN81l8j7z0T7+n97XuTl5SXRudsp+cFTx331P1Fe6echhGw85JfTfaZXYCfwMBpPaURtl09xSxQXxpE5vF+3IO32zcH/hsvOGAhVVqS8yrIWce8TF2Fxrb2B2UayRJRUcXuXTbpa0gDwj0VcqL8LOS9LQb7diNJjAPQAceUW9/WJOY5f4tabu4nx9usNOK04UkyOLCd7PVh3w8sk6KUNsrRybsxrNg/CN78mhNAA8I9H1lnLGtnHg/TOrtrkKmujZQ287NBamsP7vchitcFzR+Bfn19ZGBwkX+tNSBQy6Je1rWJkkvXROwThX/gg2Q3E9Vdh5KsocxJc2w19WrUM7qu/5EDSyFdnhgbp3eHla0W53gdAvGnEY6sAg7JTmeQbBVVRp2UC7Igs4pF9D2QvLfGmkD1Mwgx0xyCs7HlyObOAEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEkLJmvW+6plIpV7iuSj5R0lDJtvi/bpD5d03NOLONJ5t7y/ssts51VDI+SH8y8Esck08F3qZke0f4OHFWJPIpmh+VDFTyEos8iYl8IvRaJf2UbKLkcyXnKvmZSVNJGu+8vLA2m5CKQveFq/D7MSWX4v86SmYp6aPkg5A43lWyD3SU6uXUr76gZMsg/YnFlTnWK3KdttnoTUcruVlJ+yD9ScjCIP2N+bJ81z2VvK+kcZD+1GJUuKZKliS412bom3R5qQi9kvyzuEzJACU1lIwL0p9q9ZXHd5QcoGSZknOU/CdpP05IeVPF07CLRtkgw8Hme8bvMUH627cmhwfpb5i+j99/KXlNSW1HfLcE6W+gyrdz",
		"T8Qxea7ZStp6nmFHJV9B+RBFo3fCd3g6SH+z90tLMZBB9J2O8I2UnKWkJn7LYOn8SpTHYryQ73i/Yh0XRexFI31vi4jnLJSLOo5z8u5PKlmEzl3yfQtHuH2VfAaFQzrnsUHaoBTGm4776jJaZMk1njiuVzIX7zoCSohJkUNSDsVkHN5PGv03PGWweZD+hrq83zyU4cqCpP8XUG4XIv839YSVb2MfBmVYOrrvUGcbhsQ/AunWLkRp1Pm2EuVFFP3Orn5RyQ2o6xJevoF8YEh8kiejlewWcV9bascI94MVn3x7/QHUm+Xo7BvGaEe7OspyEdoq+742J1hhG0Tc61yU960zaN91mKHGsY9C6uEzEe+ouVLJL8j775X0ipFXUk5fQrvq4lK084Uooz1jxLkMdbSVI+z+SiYinJTP5x3vUhQj3+Lmv7QpTzieY1eE7Wgck7TwfaNe8voo4/d2GNztYfXPk1B2TfZD2A7W8V5I1zYRbWWxklLHMzVD/3+pcUzqy11B2iAdRg9c2z1G/7AcA8Zc9JUjg3+2obwe2v0XMUiW3y3K4b6fIT9XxAy3JGH8v8YsL2R9/vK01xszosfdreR0GACiytWhMDzdr+TRwDG5SsiGYADIhq2CdWcICyylaBMoyy+jgxe2h7JytRVXKwwAjgzS1mqttIjiMARKn28AL4PRWkoGI2zc9xTjxA5Kbneck9nQM4O01Tyw3lGe/xH8HooOtaAS5K/M4t6I9LMVtLsxgBXLeRcoP2d4DByXe9JEc4eSnTHYaA6l0TY4tFYySsmrUIpbQ6EdGRKvGH32CjmvFUwt/3aEOVvJyRgYNkfDfIUjD00RhXWYcb4BBpfvIT3aQOkc4bjfaxggNofCfyaMJ7mkgfUOV8Qw2HXAOwyB4rcdlGaXsnswlH+RGajDl+OdLwh5ph5Io+MjnqUZjEabQ3Eb7hks9oMRQgbpz0HZ38oTXyuUr/c9BgVXefEppHa4bazzA4K0tb8z3qEl2p1MMJXWTYx72rySQMHdXcl9KPc/ZlHOdkfb2QDlxYUYF/vEKH8XB+kZlaPRNt+AfmDviLzaGv8/7wjTD/3GsVBg+6P+7RIRZ3uUvxccg6Ph6KOkjuyINOjvaS/i5FsUQ1HPqlrHj8Zg3exPp1mDcU1DPO8049j36DMfMeI+D896o3X9B2iH77WMXDJQvxNGOF9bKQbEOQgbl0fQHvXIsh1sjfZAFO6+OWpbxRDeO/jn0gn5Ju3VGhwrpSr8jyCTQae0J02YdOvRFn3fBwmv+wRtbF0mIdnYDAA7KfkG/8sM8C/WeTlWA8p8MY79BSVumsMAoBWZH6BoyEC1p2egZyoFI6GY/hakZzbi+sj2gwK5yHHuG8i/rON/KLkqSM9qiRvQT0F6xtk1ixc2O1YWnIHB+GvW8aoYXN+Nd/0VCoFtAKiP9Bel4dyQ+1SFQv9nkJ6JejxIz2BVsxTHm5Q8iDyR+z6LAZRLcd4USuU1WabB5VDgf8Vg7wgYc3zUh8HkeqszqAvD0iq844sYGJqK++bIYxkgyizjVCjVfT3loEHM46aB7VG8y+7G8T1w7FHklQsxRHyFvCmG0n43BrL5VtjzMDg7A+96EQYiMjg61BO/DFi+RTk6LmbeLMEAqKX1DKLIXBKkvSe+Q10Wy/qgkI51OcrWMJTFsmwzz4ZB7Hcl8zGw/T2oHFZ/Meq8joHMyCzj+gmGs4OCdT2i7PT41GM8DCwjlTzT1yjjI1CHroy4bi7KaQ9HOb0G+TABg5g3YCi5KiLOvzA43seKsxPK17MYHP2KPuGjMswvMTY0xrPY9ck2ovoMAG2QpjMchqpGaLtFyR+IurzM004eYBg1xIuteoyB/T1o95PUuUIYFm7OMu3OhGHoKfTLZVX/RG8ZjXSTfl5mqXcICS9eJFMQdkzg9rISo6Z4fvyNcB8H6ckQm21QZ1ZC/9g+pN+S+rQYbfZItKsmRRigBGivfB5H2+GehajbR6B81XPct4vxfKKn2Qb7o4J1vWV8us/Pgd/DyUaMggszMNR0gzHrXugCZ6M/LAzW90jphneSfnYi/v/ZUU+1rjIM5WMh+sCaVpj90EYdgnos8b3rKRvb4p6FSNvTkCb1jTA3YXAq6f8jdKpPrHiOgf5WhDIx3FEmtN4931MW4noyHY9r61vXS/0caxkW10A/dOnHK6x6XAvpbk54dEB/38041h9pZfNWsHZyLgjW915a4xkf6LFR0vV1JWU0tiKk0hoApJH8Ap36RfhfOkxxOX7fauRXQGE2G0jprOzZmNmofGJU2BGKoB4QFoY8y7cYgIiR4FY0THEqcVV03KNDwowO3LMWF0Ip6IXGe89KkLfVoZQNcLx/W3Tm3xvHvkM62wM06TDOQvr7kPcfZSktfwdrZxh0R3OP8bsj8vJZj7FkEAa02cxgNkVnUQPvugwKd72Qay6Bwj/FODYZg6GLoLg1QKc8wmjwBb2O8hfLcLRDFu+Qh0H3aJSxIsR3jDVY2AHndN07xOpIb3MM3jdDfSxx1IOlMDiIce46KGbjA/9M8AlQMMQItmXgnql3KU7nYcBabD2XeFCMs8JfGTIQ1YyyFINcszkGbBOMY5LmF2egLOQaGcyKh83naPuy5T2Uo0MD/0xIHgy654QMwDaDQdeO4/0g3MNHUxMKrllOW6Adc8W5d4w4C9A+mbOfc/D7ArQZwodQIsuKv/AOZn3eEYPOVx3K+mZGXdBLU1pjQLfSMdC+AIa0J1Cfhnme41cYWu5DvbwJSnfYWvgD0NeeYNXfODyGd+mZYbpJO3V6kPZomob371FGefQM2r8WaPu/cxhnTE6CTtQKbYVr6eATKL9bIc4vMCCsZYXT7ydeHofjnV0Mhj7XBv3QPEf58XmtFDgGbVNgPDrDGByXevr+w/Cek4P1PaHeCOJ5LnWMGU6e+00807CE+VgMQ9hM9Gt3oj+5Fn27HbYA9awn3m8SjE02z6GNaon83NVhUFiD9rEvzreAHuIysA2Brizpf2SwdvLFbP+moJ24H7pIdav8t0AZvRNlqiXqsn2/XHgxBej7i6CLmEau3tDxzHQQQ2V7Rxxb4b1SVht2MtqjDkjDwdANPzTCPQXj2PaW/ifG6yetOqClPsrsgxwKEhL834ZSXVNpGsjmUgnlAyU18P+dSvZ0hDlIyWwlxbjPi7inK75rlSxU8oeSl5W8H3H/2krGKClRch3eoZqSfWM8e3s8T6eQMH2UrHQcr6qkAP/XDblep22dDNI2qZynZJKSPMe53fAcjY1n6om/1bN89rZK5iu5ynNeysQaxPW8kiqOMEcq+VpJvue++th/lCxQsgjlqKEVz85GuE2UtFYyWckznmcrwLPv4zjXTslvSkoR5yRHHWmLc7tbZSZl1AuRmihn9ru7jv+sZIaSiyPKVmCUv0twzc8h4bZRMk/JbdbxLfC8Hys5HHVHeMX43y4jzVCf2+H320oGhpShIiWr8P8EJfWscLvi3CYR7+pqq/bDsWqe+5oyOEZ8YXUnzrOZ91vlqUNJ2oX//4yONnsw/h6WMM18YbZV8hHK+r4h9bCRkplKDvS8iy8/u4XkVQOjTk1U8rR17S6eOHX+Vw2Js6mSz5Q853j3S5BXS9FuHJphe+5KZ1/4vujjdL2/Bc9nx3ki2i/d1/6tZCu09WF941uon5tFlC1pf35V8lOMvlbamV+UHJ9hGRO5APU/yKC8Hoa+Xv8+RcmwMupLJV1qOcptgedZ9zaOnYF21gxXH/mxp6W79ME5faw54utiHDvTUYYaQedpaxxrgnCbJWxrWuD8zsaxy0PqvvlsPRx9XdI2LqzeNEG/9GCWdXILIw9bGP/XzOD9GkMn2Ms4dpaS32OUjVMdZaO5I/3/5Xgn3R739aTDjjjfI2Z618kgP+xrnlTyP+P3yUoWW+kqMlxJf/w/VMkQ/H+vkhc8z3Gjkk+gB03y6Kn/tcrGZUq+DHn3x9CO5jvO9UCdqpGwfdsJ51pax59GWkj7+hDyR9rQ8zjqJBu6B4Cg3b31zr8ycz/REW4MZtH6Gc8gMyCXOsLeASuobCq2G6zJn8ES28tjiRVXpqmYsV6MGabBMZ5f",
		"bww3PyTM37Ac2hsWlhiz2C73Su1u9J5xD99mX7mgALO2A2LMShbC2pyL2UuZfRiLWbh7PGE+g7W6C8TekKoBLLJ9Q2aV5mPW+HlYeWXN79awnLvKZH9cI0tCxDOkjyfe3si/jx3nXkT+1cUswnzHs8u+FF/hfvVRbi8xZhQ0K2HptmdUXMdlluhrzOoui5EHyxD2a9QzF7Jfg7gLyvr/Gx0zLHpG5gdjRuo7o70osa45Dh4W2gV5WBC+DKAZZljbYmZ3kG2HNGaXM23TwjYl0+JbNzw3WNdN8DXPs9UO1t0IrXbEPct6gyrx3BiJ2ZH6OYhPZlXroD0tCQlXihnNKGUmz/M7FZIHX6A8Xxyz70oZ3hCuOKV/+gUeHK7nfQAzt5ejrr8dZO+qHsUw9D/aG+JozwzzdLSxUne2Rf3dF8emeeKuh5nC1TG8LaT9Ea+xTnj/MO5BOz80i/d+Cm1prwyu7Resu/nk6/D8aF4G+dMFestSlMkxIWUsCNbdt+EXeFRUN451gAeDmWcr0M6Ym9+1NuLQzHTcrx3qw09GezQbbVKbhO/ayvAICYy238cMS5cw+91c8zhmia/IMp5FRn+81Pi/agbvtwXasWlWPW3pSQezbMx2lI3WjvSf4YhHt8f/87yjeMLKMr7R+P/eIJ5nVDaI/r1fsNYT8hS0D7YX0RR4AEibJ/vodEXfKe2Oz+PzdqSneDSchPbM5lGc0+l5mjX7b+ssPaEL2nqmeCZdi3Z5VcI0+A7vIMvQTC/nL9DWdcM44r9BevlwFw5DyYZuAJCOfDkaGN0BdccA/GWPwjjV6MjFFfymEIX/Wihiss5P1iY+HKRdCAOr4RTF6VbEeS86RtkgalSuHSUyGJBnummUvWYpDrK2TVxLh4cMoIWGMNLojYGWehrWOEhHKC6m4j5/gmcAVsNIPxmgXo+8Mjvee9GRfBtyrynI1zfReE/HoLunpZQtcBh1fsOgpoYj3mMC97ppUTp2x0BgBRpwUYCPd9ShEzBwmAMF9TUMPEoyTNfN8L7yrp/ivV2KSlWcEwPLCFyzuSecLIN4CEa3Uk/ZFsVkYbB2zeD36LD/cLyLvPM2qO+LMYjaMvBvxmcqx7ehMzbr/h/42zyD9kragT+zSG+XoaCP49maoCzI+QOQruW5B4CrDToCSk+ANjJXSt3LMcKJkbVHsP4a0wD5Idi7jTdHXSoOyYOmaPPtzRp13bZ3f2+KvmiVJ86tUOZfCPw7ks9Hn3YwjKiXZ9BXljiMHlUcxsAAdWYM2p+tYHxzfUZqGtqWg9A+fgIDQMsQA8CtOCd9531B9GaNs6y/LqS8y1roC7MsW6ug2A9IWHckHccH627CuhLlpFmO61k96B4T0LZImTww4prSmPU1GwOnK+7NrHarWrD+uvAo8hLqO+W97GlJEL3HRy71t0zeL8ywWerIy6h7VA05tzTkuU+CDvwYdIH30O9ni6/cfgoD1fGoh6LvPuvR38QAcAgMGONgONgyxABQG/3F6sC9fCCAQVL6BVk2oZdRuQyU7ZEOvdH/mOxlGO0ymZ2Xtv1kpP27xvGn8ezSrt6CfJG2vG9ASCUyAIxDBU/yHVtZI346KkwBKrLetfpEI9xFUChtvodi4rKYtkXcN6ERkwZmhqEgmsqdbhCl05O1UW9BIR4S4x3mG4NzH5tC0Sgsxzyyd13W1MTA3c7DmjCo9I9Q8sQKbq7n7hy4N1GJgxgSZOZfrJpnegZflzoG9SWO5++LcjIf8pYxWNTIOq/9reuqQaE07z0T77mTcWxzxLvK0al1C9yz/zUcHXW+Z9A3C0p5HcTXLFh/Lbsv72rgmubW4EnKvszkiDX7apR/+ysAM6AYPY6wNxkDL5OW6CTv9OTlAiM9UsHatfw/YZD/icPwsxsGBTtCtoMyEGczwDyko5kWc5B33aywTwThGzgKYevVc4HMis8O4q1dzwXdMQDR1IWS4Rq8zka7fSra3VzsZv5QiCHRRBSpN6D82PwGsT0g9vPUtzjMwrvu7VDgJoZcNxN9w9PB+jO4kmb22l0xqNWKUMLD+hNzk68WeGaXIfcVGHAOQ/l17bmyCPVT8vUj1MU90ca4DAAyu9QPA+OXUYfvzLI8SPl7BEa/FTkoX8+g7z8mwTWlMBzabbgYW7/Jcf3TG0PeFaydnd8p4prNrfZR2mFzP5zp6Kc6WYaGaywDxhxjYK/p6DEMlQTr7uGT7zHGRaHLXWvj2A5B5aAvdMEbg2jjcnkxE/3klsaxDmifij36bGDk61yrbLjyvFMWxqtZ0AmOhm52gdXuRRkf9DtUt3QIH8+jLstkxFQY6lwGAPE06Ym+7V0YA9qEGAAGQY+S/kWMs009Rg8xdpwBvV/a1OUOHes16FETPEaMVtCn3sywfXwHz3FgQMiGRBbr5O7Cukz5/ygllzrCdMO6mtOMtZqy5ul1JeM98b6BNVXy/w9Y+3Qx1j+a4WQ90hI8R3WsjVyGNfs7edaa2+v4Vyg5OiTMwBhrFrNZb6XXD92WZC2wdfyKkLQ05T6sM22Atdt/etZz1oEciPs1NY7pMLKW9h3PfgPm+viVyLt8rBv/1LFus5UlR+G+W1pr4gqxn0QVrOmTdWGPO+57O/YTaIL1flKG7nGEa4P7dHScy8farcexnq0+1p++6Qj7I/a/qIq9ABY59sLw5d0BMfahCLDe8FXj96vWGsRspArqkdAZa+R0PZ1s7W8QYK+NyY54LlQyK+K9m2Kt8QjH9bK2cS7alCpY4yt5vr0nPqnz56IOb5vhmuS44S7Gmvd2uO+VIWtk46ydDGsX2mG9cF+slZe9UEbLOaPNdt3rLrSRTT33knTc3JBNM3h2O9xeWD/vepcL8Dy7op2QNdzL8TuTPAiw3vMX7O2h170uw9rasDhrYT+P66xwRyhZraQ36nxj1PGxGbTn8o7TldyPfGuM9ctDQvavkbI7Fe2b750/x7rhrkZ785eSrR39meydcLe174fsQ7FHFnVA2sCLclSPzPZ8sqePzmZPolxIS6zxPhXPd7CS9zx9RVdjX6O6WJv/NdYa2/G+grZvE+wlcD/2RrL3FfgOdb4G6umXnjIn8X2FdroW+rifHX1ynLX409Cn10C5mpBl+5arPQAaGGvFf3CkVZJ9OcxwXbN8v7eg/9QxdIybPPd+BXveNEJePul4zklWnn8V8/lMOR7twraGHjfIsS/QVojnVJSdHfBXn98E/c8pxn4TH4Sk8eZoYz5Fv+h6tgYIMxP61KYo+yutvVu09MYeKY3w+3mP7qXjXoq+potn3f/DMer9fgn3d9Gyh7FfRaw2hpDKZADYE0pc/YQd5SijQb7F2uzEtZHRalSUQihYWzjCHoDORysGvdCoLXIoeTr892hcZsEIMRAbCb4d4x1GeBpkLeMxoCwrZeNCbJDXKkMDQB0ohwfH3NhoCBpLueZ6T7gwdJgSPLe9yVptK6790ekVIg9fcGzcF6dDF6XmGuRxETbcucejEFRDx7cIA9snPRu76I3KGoZsmvc+lPQl2CBsU0e43VFmC7ER34kJOpD+EZvW5ELi1O9X8XzjEP5/+P8kR1ipbzeHKM67h2yMtwCKZsOQjSxnIOy3SrqHbLRXCINW15gb8mk5KoPBRh7alXkoD+Mc+RxXgTQ3BzSfK7A2U5qN4x/CWBVlABDDxDdKRnqey2ZoDgwAWnn1KU5XwJC2EgObnlkO+OrAEKfbe2mHngoZ9JhxHofn2NIK20/JFMS5EAp7kywMup+hbC5GvWoU8j5D0S+GtYnPI77qhkJb6mj7LkG7aD/bvaiz1TIcvPvqUVEWg/Z8GEtOTFU+A4DeBG8h2v2hMOZ8gbq/uWPQcBQG0SuhdzT0lN2n0QauQBvbybOZ27eIawIGdq70qIv+fDGeU+7bIcOB+J7YCLIQz6U3sq2dYfsWp41LYgAogOHr/oT3KSsDwKaYqFqO/LzfsbGcvvYU9GkroTO7NpPdHm33SugDp2dgAMiDEWIW4lkKI4WrjA3Cs69E27eXQy+dizr6Poy3Yff+AEaDZiFlbK6lk09AObfDNcVg/nBrkD8HbbUr7iFIP1/7tSqk7YqTvpmeowGA",
		"VCryXB4A5URXuDDWdbjpVBTiPjwUrkj2Eogd4TLUMXBvypILhgZr13KTjQ9xhRsRrPvd2opA3P5lOYi4Qz8At7necN37nNlUSRrvvLzybrMrK9vA1VTWm17IklHh6L69YZBsKWFZx0UyQz4/KHtSyNK1sm5sZN8NcaGWZTdFrBOVVleuzMgSqtez1KNkKZksOZBNyBclyEtZkibL2mRZ05Ik/Tgh5U2VCry33mugMjVo0vHIFwaud5yTLxI8U4aDf93oDGKx3GjroqxrHFoJnkXWCstGY7JuUDYC/AId2pfMJlIJka9VyJp+WR+6SwX3a6TyUCNYfxNdW85hMq2H7BMhkx2y6avsZSN7O71bhoN/WVMu69LlyyViwPv8Hzb4J+WDlJ/LgvSeCc9lGddf+LtHwuuk/1kR5GZ/FELKlHwmwXr8CwMd2SjkKxwTxVJmmU4ow/u2wWDrY2bBRonsKi8bri2oJM/zCTozQjYE5LOnTdF+rkB7WshkqVD0hnKyIdalCa+VAad8aSCb6THZJLCA2ZAY+cKN7FI+Azqi1Klzy/B+N0K3EoONbLp5CrOAZMC8IL2JonjQZjuxKBt1DsQ4QDaYlgnLsM/4yuThAeh7xIhVzOwghBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgghhBBCCCGEEEIIIYQQQgjZWPh/AgwAfn8YvlGtFegAAAAASUVORK5CYII=",
	};
	*data_size = 123437;
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
	i32 encoded_size = 93809;
	char *encoded_data_strings[] = {
		"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",
	};
	*data_size = 70355;
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

	struct {
		ztGuiSpriteNineSlice_Enum val;
		const char *name;
	} nine_slice[] = {
		{ztGuiSpriteNineSlice_WindowFrame                      , "gui_window_frame"                      },
		{ztGuiSpriteNineSlice_WindowFrameDisabled              , "gui_window_frame"                      },
		{ztGuiSpriteNineSlice_PanelFrame                       , "gui_panel_frame"                       },
		{ztGuiSpriteNineSlice_PanelFrameDisabled               , "gui_panel_frame"                       },
		{ztGuiSpriteNineSlice_CollapsingPanelFrame             , "gui_collapsing_panel_frame"            },
		{ztGuiSpriteNineSlice_CollapsingPanelFrameDisabled     , "gui_collapsing_panel_frame"            },
		{ztGuiSpriteNineSlice_CollapsingPanelCollapsed         , "gui_collapsing_panel_collapsed"        },
		{ztGuiSpriteNineSlice_CollapsingPanelCollapsedDisabled , "gui_collapsing_panel_collapsed"        },
		{ztGuiSpriteNineSlice_ButtonNormal                     , "gui_button_normal"                     },
		{ztGuiSpriteNineSlice_ButtonHighlight                  , "gui_button_highlight"                  },
		{ztGuiSpriteNineSlice_ButtonPressed                    , "gui_button_pressed"                    },
		{ztGuiSpriteNineSlice_ButtonDisabled                   , "gui_button_disabled"                   },
		{ztGuiSpriteNineSlice_ButtonToggleNormal               , "gui_button_normal"                     },
		{ztGuiSpriteNineSlice_ButtonToggleHighlight            , "gui_button_highlight"                  },
		{ztGuiSpriteNineSlice_ButtonTogglePressed              , "gui_button_pressed"                    },
		{ztGuiSpriteNineSlice_ButtonToggleDisabled             , "gui_button_disabled"                   },
		{ztGuiSpriteNineSlice_ButtonToggleOn                   , "gui_button_highlight"                  },
		{ztGuiSpriteNineSlice_ButtonToggleOnDisabled           , "gui_button_pressed"                    },
		{ztGuiSpriteNineSlice_Menu                             , "gui_menu"                              },
		{ztGuiSpriteNineSlice_MenuBar                          , "gui_menubar"                           },
		{ztGuiSpriteNineSlice_MenuBarDisabled                  , "gui_menubar"                           },
		{ztGuiSpriteNineSlice_TextEdit                         , "gui_textedit"                          },
		{ztGuiSpriteNineSlice_TextEditDisabled                 , "gui_textedit_disabled"                 },
		{ztGuiSpriteNineSlice_SliderHorzBar                    , "gui_slider_horz_bar"                   },
		{ztGuiSpriteNineSlice_SliderHorzBarSet                 , "gui_slider_horz_bar_pressed"           },
		{ztGuiSpriteNineSlice_SliderHorzBarPressed             , "gui_slider_horz_bar_pressed"           },
		{ztGuiSpriteNineSlice_SliderHorzBarDisabled            , "gui_slider_horz_bar_disabled"          },
		{ztGuiSpriteNineSlice_SliderVertBar                    , "gui_slider_vert_bar"                   },
		{ztGuiSpriteNineSlice_SliderVertBarSet                 , "gui_slider_vert_bar_pressed"           },
		{ztGuiSpriteNineSlice_SliderVertBarPressed             , "gui_slider_vert_bar_pressed"           },
		{ztGuiSpriteNineSlice_SliderVertBarDisabled            , "gui_slider_vert_bar_disabled"          },
		{ztGuiSpriteNineSlice_ScrollbarVertBackground          , "gui_scrollbar_vert_background"         },
		{ztGuiSpriteNineSlice_ScrollbarVertBackgroundDisabled  , "gui_scrollbar_vert_background"         },
		{ztGuiSpriteNineSlice_ScrollbarVertHandle              , "gui_scrollbar_vert_handle"             },
		{ztGuiSpriteNineSlice_ScrollbarVertHandleHighlight     , "gui_scrollbar_vert_handle_highlight"   },
		{ztGuiSpriteNineSlice_ScrollbarVertHandlePressed       , "gui_scrollbar_vert_handle_highlight"   },
		{ztGuiSpriteNineSlice_ScrollbarVertHandleDisabled      , "gui_empty_nine_slice"                  },
		{ztGuiSpriteNineSlice_ScrollbarHorzBackground          , "gui_scrollbar_horz_background"         },
		{ztGuiSpriteNineSlice_ScrollbarHorzBackgroundDisabled  , "gui_scrollbar_horz_background"         },
		{ztGuiSpriteNineSlice_ScrollbarHorzHandle              , "gui_scrollbar_horz_handle"             },
		{ztGuiSpriteNineSlice_ScrollbarHorzHandleHighlight     , "gui_scrollbar_horz_handle_highlight"   },
		{ztGuiSpriteNineSlice_ScrollbarHorzHandlePressed       , "gui_scrollbar_horz_handle_highlight"   },
		{ztGuiSpriteNineSlice_ScrollbarHorzHandleDisabled      , "gui_empty_nine_slice"                  },
		{ztGuiSpriteNineSlice_ComboBox                         , "gui_combobox"                          },
		{ztGuiSpriteNineSlice_ComboBoxHighlight                , "gui_combobox_highlight"                },
		{ztGuiSpriteNineSlice_ComboBoxPressed                  , "gui_combobox_pressed"                  },
		{ztGuiSpriteNineSlice_ComboBoxDisabled                 , "gui_combobox_disabled"                 },
		{ztGuiSpriteNineSlice_CycleBox                         , "gui_cyclebox"                          },
		{ztGuiSpriteNineSlice_CycleBoxHighlight                , "gui_cyclebox_highlight"                },
		{ztGuiSpriteNineSlice_CycleBoxPressed                  , "gui_cyclebox_pressed"                  },
		{ztGuiSpriteNineSlice_CycleBoxDisabled                 , "gui_cyclebox_disabled"                 },
		{ztGuiSpriteNineSlice_TabsActive                       , "gui_tab_active"                        },
		{ztGuiSpriteNineSlice_TabsInactive                     , "gui_tab_inactive"                      },
		{ztGuiSpriteNineSlice_TabsDisabled                     , "gui_tab_disabled"                      },
		{ztGuiSpriteNineSlice_Spinner                          , "gui_spinner"                           },
		{ztGuiSpriteNineSlice_SpinnerUpHighlight               , "gui_spinner_up_highlight"              },
		{ztGuiSpriteNineSlice_SpinnerUpPressed                 , "gui_spinner_up_highlight"              },
		{ztGuiSpriteNineSlice_SpinnerDownHighlight             , "gui_spinner_down_highlight"            },
		{ztGuiSpriteNineSlice_SpinnerDownPressed               , "gui_spinner_down_highlight"            },
		{ztGuiSpriteNineSlice_SpinnerText                      , "gui_spinner_text"                      },
		{ztGuiSpriteNineSlice_Solid                            , "gui_solid"                             },
	};

	zt_fize(nine_slice) {
		theme_data->sprite_nine_slice[nine_slice[i].val] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, nine_slice[i].name);
		if (theme_data->sprite_nine_slice[nine_slice[i].val] == nullptr) {
			zt_logCritical("Missing GUI theme nine slice sprite (%s)", nine_slice[i].name);
			theme_data->sprite_nine_slice[nine_slice[i].val] = zt_spriteManagerGetSpriteNineSlice(&theme_data->sprite_manager, "gui_solid");
			//return false;
		}
	}
	zt_fize(theme_data->sprite_nine_slice) {
		if (theme_data->sprite_nine_slice[i] == nullptr) {
			zt_assert(false); // an entry is missing from the above array
		}
	}

	struct {
		ztGuiSprite_Enum val;
		const char *name;
	} sprite[] = {
		{ ztGuiSprite_CheckBox                  , "gui_checkbox"                         },
		{ ztGuiSprite_CheckBoxHighlight         , "gui_checkbox_highlight"               },
		{ ztGuiSprite_CheckBoxPressed           , "gui_checkbox_pressed"                 },
		{ ztGuiSprite_CheckBoxDisabled          , "gui_checkbox_disabled"                },
		{ ztGuiSprite_CheckBoxOn                , "gui_checkbox_on"                      },
		{ ztGuiSprite_CheckBoxOnHighlight       , "gui_checkbox_on_highlight"            },
		{ ztGuiSprite_CheckBoxOnPressed         , "gui_checkbox_on_pressed"              },
		{ ztGuiSprite_CheckBoxOnDisabled        , "gui_checkbox_on_disabled"             },
		{ ztGuiSprite_Radio                     , "gui_radio"                            },
		{ ztGuiSprite_RadioHighlight            , "gui_radio_highlight"                  },
		{ ztGuiSprite_RadioPressed              , "gui_radio_pressed"                    },
		{ ztGuiSprite_RadioDisabled             , "gui_radio_disabled"                   },
		{ ztGuiSprite_RadioOn                   , "gui_radio_on"                         },
		{ ztGuiSprite_RadioOnHighlight          , "gui_radio_on_highlight"               },
		{ ztGuiSprite_RadioOnPressed            , "gui_radio_on_pressed"                 },
		{ ztGuiSprite_RadioOnDisabled           , "gui_radio_on_disabled"                },
		{ ztGuiSprite_SliderHorzHandle          , "gui_slider_horz_handle"               },
		{ ztGuiSprite_SliderHorzHandleHighlight , "gui_slider_horz_handle_pressed"       },
		{ ztGuiSprite_SliderHorzHandlePressed   , "gui_slider_horz_handle_pressed"       },
		{ ztGuiSprite_SliderHorzHandleDisabled  , "gui_empty"                            },
		{ ztGuiSprite_SliderVertHandle          , "gui_slider_vert_handle"               },
		{ ztGuiSprite_SliderVertHandleHighlight , "gui_slider_vert_handle_pressed"       },
		{ ztGuiSprite_SliderVertHandlePressed   , "gui_slider_vert_handle_pressed"       },
		{ ztGuiSprite_SliderVertHandleDisabled  , "gui_empty"                            },
		{ ztGuiSprite_SpinnerArrowUp            , "gui_spinner_button_label_up"          },
		{ ztGuiSprite_SpinnerArrowUpPressed     , "gui_spinner_button_label_up_pressed"  },
		{ ztGuiSprite_SpinnerArrowDown          , "gui_spinner_button_label_down"        },
		{ ztGuiSprite_SpinnerArrowDownPressed   , "gui_spinner_button_label_down_pressed"},
		{ ztGuiSprite_ResizerHorz               , "gui_resizer_horz"                     },
		{ ztGuiSprite_ResizerVert               , "gui_resizer_vert"                     },
		{ ztGuiSprite_HorzLine                  , "gui_horz_line"                        },
		{ ztGuiSprite_IconPlus                  , "gui_icon_plus"                        },
		{ ztGuiSprite_IconMinus                 , "gui_icon_minus"                       },
		{ ztGuiSprite_IconArrowLeft             , "gui_icon_arrow_left"                  },
		{ ztGuiSprite_IconArrowRight            , "gui_icon_arrow_right"                 },
		{ ztGuiSprite_IconArrowUp               , "gui_icon_arrow_up"                    },
		{ ztGuiSprite_IconArrowDown             , "gui_icon_arrow_down"                  },
		{ ztGuiSprite_IconPencil                , "gui_icon_pencil"                      },
		{ ztGuiSprite_IconTrash                 , "gui_icon_trash"                       },
		{ ztGuiSprite_IconUndo                  , "gui_icon_undo"                        },
		{ ztGuiSprite_IconCopy                  , "gui_icon_copy"                        },
		{ ztGuiSprite_IconCut                   , "gui_icon_cut"                         },
		{ ztGuiSprite_IconNew                   , "gui_icon_new"                         },
		{ ztGuiSprite_IconSave                  , "gui_icon_save"                        },
		{ ztGuiSprite_IconOpen                  , "gui_icon_open"                        },
		{ ztGuiSprite_IconWarning               , "gui_icon_warning"                     },
		{ ztGuiSprite_IconMenu                  , "gui_icon_menu"                        },
		{ ztGuiSprite_IconCheck                 , "gui_icon_check"                       },
		{ ztGuiSprite_IconX                     , "gui_icon_x"                           },
		{ ztGuiSprite_IconGear                  , "gui_icon_gear"                        },
		{ ztGuiSprite_IconCancel                , "gui_icon_cancel"                      },
		{ ztGuiSprite_IconPlay                  , "gui_icon_play"                        },
		{ ztGuiSprite_IconPause                 , "gui_icon_pause"                       },
		{ ztGuiSprite_IconRewind                , "gui_icon_rewind"                      },
		{ ztGuiSprite_IconFastForward           , "gui_icon_fastforward"                 },
		{ ztGuiSprite_IconBegin                 , "gui_icon_begin"                       },
		{ ztGuiSprite_IconEnd                   , "gui_icon_end"                         },
		{ ztGuiSprite_IconBrush                 , "gui_icon_brush"                       },
		{ ztGuiSprite_IconPenNib                , "gui_icon_pen_nib"                     },
		{ ztGuiSprite_IconPen                   , "gui_icon_pen"                         },
		{ ztGuiSprite_IconPaintBrush            , "gui_icon_brush"                       },
		{ ztGuiSprite_IconPaintBucket           , "gui_icon_paint_bucket"                },
		{ ztGuiSprite_IconVisible               , "gui_icon_visible"                     },
		{ ztGuiSprite_IconNotAllowed            , "gui_icon_not_allowed"                 },
		{ ztGuiSprite_IconSearch                , "gui_icon_search"                      },
		{ ztGuiSprite_IconZoomOut               , "gui_icon_zoom_out"                    },
		{ ztGuiSprite_IconZoomIn                , "gui_icon_zoom_in"                     },
		{ ztGuiSprite_IconWand                  , "gui_icon_wand"                        },
		{ ztGuiSprite_IconReticle               , "gui_icon_reticle"                     },
		{ ztGuiSprite_IconFlag                  , "gui_icon_flag"                        },
		{ ztGuiSprite_IconPaperclip             , "gui_icon_paperclip"                   },
		{ ztGuiSprite_IconNodes                 , "gui_icon_nodes"                       },
		{ ztGuiSprite_IconLink                  , "gui_icon_link"                        },
		{ ztGuiSprite_IconTag                   , "gui_icon_tag"                         },
		{ ztGuiSprite_IconLock                  , "gui_icon_lock"                        },
		{ ztGuiSprite_IconUnlock                , "gui_icon_unlock"                      },
		{ ztGuiSprite_IconPushpin               , "gui_icon_pushpin"                     },
		{ ztGuiSprite_IconPushpin2              , "gui_icon_pushpin_2"                   },
		{ ztGuiSprite_IconShield                , "gui_icon_shield"                      },
		{ ztGuiSprite_IconKey                   , "gui_icon_key"                         },
		{ ztGuiSprite_IconFlame                 , "gui_icon_flame"                       },
		{ ztGuiSprite_IconTarget                , "gui_icon_target"                      },
		{ ztGuiSprite_IconBolt                  , "gui_icon_bolt"                        },
		{ ztGuiSprite_IconClock                 , "gui_icon_clock"                       },
		{ ztGuiSprite_IconTicks                 , "gui_icon_ticks"                       },
		{ ztGuiSprite_IconHourglass             , "gui_icon_hourglass"                   },
		{ ztGuiSprite_IconAlarm                 , "gui_icon_alarm"                       },
		{ ztGuiSprite_IconLargePage             , "gui_icon_large_page"                  },
		{ ztGuiSprite_IconBanner                , "gui_icon_banner"                      },
		{ ztGuiSprite_IconClassicPhone          , "gui_icon_classic_phone"               },
		{ ztGuiSprite_IconCellPhone             , "gui_icon_cell_phone"                  },
		{ ztGuiSprite_IconMail                  , "gui_icon_mail"                        },
		{ ztGuiSprite_IconMailOpen              , "gui_icon_mail_open"                   },
		{ ztGuiSprite_IconMailFile              , "gui_icon_mail_file"                   },
		{ ztGuiSprite_IconInbox                 , "gui_icon_inbox"                       },
		{ ztGuiSprite_IconInboxOut              , "gui_icon_inbox_out"                   },
		{ ztGuiSprite_IconInboxIn               , "gui_icon_inbox_in"                    },
		{ ztGuiSprite_IconCamera                , "gui_icon_camera"                      },
		{ ztGuiSprite_IconFilmRoll              , "gui_icon_film_roll"                   },
		{ ztGuiSprite_IconComment               , "gui_icon_comment"                     },
		{ ztGuiSprite_IconComment2              , "gui_icon_comment_2"                   },
		{ ztGuiSprite_IconComment3              , "gui_icon_comment_3"                   },
		{ ztGuiSprite_IconDiscussion            , "gui_icon_discussion"                  },
		{ ztGuiSprite_IconRSS                   , "gui_icon_rss"                         },
		{ ztGuiSprite_IconRSS2                  , "gui_icon_rss_2"                       },
		{ ztGuiSprite_IconConnected             , "gui_icon_connected"                   },
		{ ztGuiSprite_IconBell                  , "gui_icon_bell"                        },
		{ ztGuiSprite_IconMegaphone             , "gui_icon_megaphone"                   },
		{ ztGuiSprite_IconContacts              , "gui_icon_contacts"                    },
		{ ztGuiSprite_IconContacts2             , "gui_icon_contacts_2"                  },
		{ ztGuiSprite_IconPerson                , "gui_icon_person"                      },
		{ ztGuiSprite_IconPerson2               , "gui_icon_person_2"                    },
		{ ztGuiSprite_IconPersonMinus           , "gui_icon_person_minus"                },
		{ ztGuiSprite_IconPersonPlus            , "gui_icon_person_plus"                 },
		{ ztGuiSprite_IconPersonMinus2          , "gui_icon_person_minus_2"              },
		{ ztGuiSprite_IconPersonTimes           , "gui_icon_person_times"                },
		{ ztGuiSprite_IconContacts3             , "gui_icon_contacts_3"                  },
		{ ztGuiSprite_IconPeople                , "gui_icon_people"                      },
		{ ztGuiSprite_IconBuildings             , "gui_icon_buildings"                   },
		{ ztGuiSprite_IconCalendar              , "gui_icon_calendar"                    },
		{ ztGuiSprite_IconCalendar2             , "gui_icon_calendar_2"                  },
		{ ztGuiSprite_IconFile                  , "gui_icon_file"                        },
		{ ztGuiSprite_IconFileText              , "gui_icon_file_text"                   },
		{ ztGuiSprite_IconFileCopy              , "gui_icon_copy"                        },
		{ ztGuiSprite_IconFolder                , "gui_icon_folder"                      },
		{ ztGuiSprite_IconFolderLock            , "gui_icon_folder_lock"                 },
		{ ztGuiSprite_IconFolderPlus            , "gui_icon_folder_plus"                 },
		{ ztGuiSprite_IconFolderMinus           , "gui_icon_folder_minus"                },
		{ ztGuiSprite_IconFilePlus              , "gui_icon_file_plus"                   },
		{ ztGuiSprite_IconFileMinus             , "gui_icon_file_minus"                  },
		{ ztGuiSprite_IconFileWrite             , "gui_icon_file_write"                  },
		{ ztGuiSprite_IconFileDownload          , "gui_icon_file_download"               },
		{ ztGuiSprite_IconHouse                 , "gui_icon_house"                       },
		{ ztGuiSprite_IconHouse2                , "gui_icon_house_2"                     },
		{ ztGuiSprite_IconSignpost              , "gui_icon_signpost"                    },
		{ ztGuiSprite_IconGlobe                 , "gui_icon_globe"                       },
		{ ztGuiSprite_IconMap                   , "gui_icon_map"                         },
		{ ztGuiSprite_IconMapPoint              , "gui_icon_map_point"                   },
		{ ztGuiSprite_IconConstruction          , "gui_icon_construction"                },
		{ ztGuiSprite_IconLifesaver             , "gui_icon_lifesaver"                   },
		{ ztGuiSprite_IconConstruction2         , "gui_icon_construction_2"              },
		{ ztGuiSprite_IconBlocks                , "gui_icon_blocks"                      },
		{ ztGuiSprite_IconBlock                 , "gui_icon_block"                       },
		{ ztGuiSprite_IconHierarchy             , "gui_icon_hierarchy"                   },
		{ ztGuiSprite_IconLayers                , "gui_icon_layers"                      },
		{ ztGuiSprite_IconArrowStyleLeft        , "gui_icon_arrow_style_left"            },
		{ ztGuiSprite_IconArrowStyleLeft2       , "gui_icon_arrow_style_left_2"          },
		{ ztGuiSprite_IconArrowStyleLeft3       , "gui_icon_arrow_style_left_3"          },
		{ ztGuiSprite_IconArrowStyleLeft4       , "gui_icon_arrow_style_left_4"          },
		{ ztGuiSprite_IconArrowStyleLeft5       , "gui_icon_arrow_style_left_5"          },
		{ ztGuiSprite_IconArrowStyleLeft6       , "gui_icon_arrow_style_left_6"          },
		{ ztGuiSprite_IconArrowStyleLeft7       , "gui_icon_arrow_style_left_7"          },
		{ ztGuiSprite_IconArrowStyleLeft8       , "gui_icon_arrow_style_left_8"          },
		{ ztGuiSprite_IconArrowStyleLeft9       , "gui_icon_arrow_style_left_9"          },
		{ ztGuiSprite_IconArrowStyleLeft10      , "gui_icon_arrow_style_left_10"         },
		{ ztGuiSprite_IconArrowStyleLeft11      , "gui_icon_arrow_style_left_11"         },
		{ ztGuiSprite_IconArrowStyleLeft12      , "gui_icon_arrow_style_left_12"         },
		{ ztGuiSprite_IconArrowStyleLeft13      , "gui_icon_arrow_style_left_13"         },
		{ ztGuiSprite_IconArrowStyleRight       , "gui_icon_arrow_style_right"           },
		{ ztGuiSprite_IconArrowStyleRight2      , "gui_icon_arrow_style_right_2"         },
		{ ztGuiSprite_IconArrowStyleRight3      , "gui_icon_arrow_style_right_3"         },
		{ ztGuiSprite_IconArrowStyleRight4      , "gui_icon_arrow_style_right_4"         },
		{ ztGuiSprite_IconArrowStyleRight5      , "gui_icon_arrow_style_right_5"         },
		{ ztGuiSprite_IconArrowStyleRight6      , "gui_icon_arrow_style_right_6"         },
		{ ztGuiSprite_IconArrowStyleRight7      , "gui_icon_arrow_style_right_7"         },
		{ ztGuiSprite_IconArrowStyleRight8      , "gui_icon_arrow_style_right_8"         },
		{ ztGuiSprite_IconArrowStyleRight9      , "gui_icon_arrow_style_right_9"         },
		{ ztGuiSprite_IconArrowStyleRight10     , "gui_icon_arrow_style_right_10"        },
		{ ztGuiSprite_IconArrowStyleRight11     , "gui_icon_arrow_style_right_11"        },
		{ ztGuiSprite_IconArrowStyleRight12     , "gui_icon_arrow_style_right_12"        },
		{ ztGuiSprite_IconArrowStyleRight13     , "gui_icon_arrow_style_right_13"        },
		{ ztGuiSprite_IconCart                  , "gui_icon_cart"                        },
		{ ztGuiSprite_IconCart2                 , "gui_icon_cart_2"                      },
		{ ztGuiSprite_IconShoppingBag           , "gui_icon_shopping_bag"                },
		{ ztGuiSprite_IconCart3                 , "gui_icon_cart_3"                      },
		{ ztGuiSprite_IconTruck                 , "gui_icon_truck"                       },
		{ ztGuiSprite_IconGift                  , "gui_icon_gift"                        },
		{ ztGuiSprite_IconGift2                 , "gui_icon_gift_2"                      },
		{ ztGuiSprite_IconCreditCard            , "gui_icon_credit_card"                 },
		{ ztGuiSprite_IconCreditCard2           , "gui_icon_credit_card_2"               },
		{ ztGuiSprite_IconStack                 , "gui_icon_stack"                       },
		{ ztGuiSprite_IconCalculator            , "gui_icon_calculator"                  },
		{ ztGuiSprite_IconMonument              , "gui_icon_monument"                    },
		{ ztGuiSprite_IconSpeedomter            , "gui_icon_speedometer"                 },
		{ ztGuiSprite_IconGears                 , "gui_icon_gears"                       },
		{ ztGuiSprite_IconRepair                , "gui_icon_repair"                      },
		{ ztGuiSprite_IconRepair2               , "gui_icon_repair_2"                    },
		{ ztGuiSprite_IconRepair3               , "gui_icon_repair_3"                    },
		{ ztGuiSprite_IconTools                 , "gui_icon_tools"                       },
		{ ztGuiSprite_IconLightSwitch           , "gui_icon_light_switch"                },
		{ ztGuiSprite_IconControls              , "gui_icon_controls"                    },
		{ ztGuiSprite_IconGrid                  , "gui_icon_grid"                        },
		{ ztGuiSprite_IconGrid2                 , "gui_icon_grid_2"                      },
		{ ztGuiSprite_IconMenu2                 , "gui_icon_menu_2"                      },
		{ ztGuiSprite_IconBook                  , "gui_icon_book"                        },
		{ ztGuiSprite_IconBook2                 , "gui_icon_book_2"                      },
		{ ztGuiSprite_IconCalendar3             , "gui_icon_calendar_3"                  },
		{ ztGuiSprite_IconBook3                 , "gui_icon_book_3"                      },
		{ ztGuiSprite_IconCamera2               , "gui_icon_camera_2"                    },
		{ ztGuiSprite_IconCamera3               , "gui_icon_camera_3"                    },
		{ ztGuiSprite_IconGraph                 , "gui_icon_graph"                       },
		{ ztGuiSprite_IconGraph2                , "gui_icon_graph_2"                     },
		{ ztGuiSprite_IconImage                 , "gui_icon_image"                       },
		{ ztGuiSprite_IconImages                , "gui_icon_images"                      },
		{ ztGuiSprite_IconPresentation          , "gui_icon_presentation"                },
		{ ztGuiSprite_IconFilm                  , "gui_icon_film"                        },
		{ ztGuiSprite_IconContainerMinus        , "gui_icon_container_minus"             },
		{ ztGuiSprite_IconContainerDown         , "gui_icon_container_down"              },
		{ ztGuiSprite_IconContainerUp           , "gui_icon_container_up"                },
		{ ztGuiSprite_IconMusic                 , "gui_icon_music"                       },
		{ ztGuiSprite_IconOpenBook              , "gui_icon_book"                        },
		{ ztGuiSprite_IconOpenBook2             , "gui_icon_book_2"                      },
		{ ztGuiSprite_IconFilmClapper           , "gui_icon_film_clapper"                },
		{ ztGuiSprite_IconDbase                 , "gui_icon_dbase"                       },
		{ ztGuiSprite_IconScreen                , "gui_icon_screen"                      },
		{ ztGuiSprite_IconScreen2               , "gui_icon_screen_2"                    },
		{ ztGuiSprite_IconScreen3               , "gui_icon_screen_3"                    },
		{ ztGuiSprite_IconScreen4               , "gui_icon_screen_4"                    },
		{ ztGuiSprite_IconBatteryEmpty          , "gui_icon_battery_empty"               },
		{ ztGuiSprite_IconBatteryHalf           , "gui_icon_battery_half"                },
		{ ztGuiSprite_IconBatteryFull           , "gui_icon_battery_full"                },
		{ ztGuiSprite_IconBatteryCharging       , "gui_icon_battery_charging"            },
		{ ztGuiSprite_IconGraphPie              , "gui_icon_graph_pie"                   },
		{ ztGuiSprite_IconGraphBar              , "gui_icon_graph_bar"                   },
		{ ztGuiSprite_IconWindow                , "gui_icon_window"                      },
		{ ztGuiSprite_IconWindow2               , "gui_icon_window_2"                    },
		{ ztGuiSprite_IconWindow3               , "gui_icon_window_3"                    },
		{ ztGuiSprite_IconWindow4               , "gui_icon_window_4"                    },
		{ ztGuiSprite_IconWindow5               , "gui_icon_window_5"                    },
		{ ztGuiSprite_IconCommandPrompt         , "gui_icon_command_prompt"              },
		{ ztGuiSprite_IconHeart                 , "gui_icon_heart"                       },
		{ ztGuiSprite_IconHeart2                , "gui_icon_heart_2"                     },
		{ ztGuiSprite_IconThumbUp               , "gui_icon_thumb_up"                    },
		{ ztGuiSprite_IconThumbDown             , "gui_icon_thumb_down"                  },
		{ ztGuiSprite_IconMedal                 , "gui_icon_medal"                       },
		{ ztGuiSprite_IconCheck2                , "gui_icon_check_2"                     },
		{ ztGuiSprite_IconCheck3                , "gui_icon_check_3"                     },
		{ ztGuiSprite_IconCheck4                , "gui_icon_check_4"                     },
		{ ztGuiSprite_IconCheck5                , "gui_icon_check_5"                     },
		{ ztGuiSprite_IconCheck6                , "gui_icon_check_6"                     },
		{ ztGuiSprite_IconCheck7                , "gui_icon_check_7"                     },
		{ ztGuiSprite_IconStar                  , "gui_icon_star"                        },
		{ ztGuiSprite_IconStar2                 , "gui_icon_star_2"                      },
		{ ztGuiSprite_IconBeaker                , "gui_icon_beaker"                      },
		{ ztGuiSprite_IconBomb                  , "gui_icon_bomb"                        },
		{ ztGuiSprite_IconJoystick              , "gui_icon_joystick"                    },
		{ ztGuiSprite_IconMug                   , "gui_icon_mug"                         },
		{ ztGuiSprite_IconBulb                  , "gui_icon_bulb"                        },
		{ ztGuiSprite_IconSuitcase              , "gui_icon_suitcase"                    },
		{ ztGuiSprite_IconFilter                , "gui_icon_filter"                      },
		{ ztGuiSprite_IconTicket                , "gui_icon_ticket"                      },
		{ ztGuiSprite_IconGameChar              , "gui_icon_game_char"                   },
		{ ztGuiSprite_IconText                  , "gui_icon_text"                        },
		{ ztGuiSprite_IconUnderline             , "gui_icon_underline"                   },
		{ ztGuiSprite_IconItalic                , "gui_icon_italic"                      },
		{ ztGuiSprite_IconBold                  , "gui_icon_bold"                        },
		{ ztGuiSprite_IconStrikeThrough         , "gui_icon_strike_through"              },
		{ ztGuiSprite_IconAlignFill             , "gui_icon_align_fill"                  },
		{ ztGuiSprite_IconAlignLeft             , "gui_icon_align_left"                  },
		{ ztGuiSprite_IconAlignCenter           , "gui_icon_align_center"                },
		{ ztGuiSprite_IconAlignRight            , "gui_icon_align_right"                 },
		{ ztGuiSprite_IconListBullet            , "gui_icon_list_bullet"                 },
		{ ztGuiSprite_IconListNumber            , "gui_icon_list_number"                 },
		{ ztGuiSprite_IconIndentBack            , "gui_icon_indent_back"                 },
		{ ztGuiSprite_IconIndent                , "gui_icon_indent"                      },
		{ ztGuiSprite_IconArrowBottomRight      , "gui_icon_arrow_bottom_right"          },
		{ ztGuiSprite_IconArrowBottomRight2     , "gui_icon_arrow_bottom_right_2"        },
		{ ztGuiSprite_IconArrowBottomRight3     , "gui_icon_arrow_bottom_right_3"        },
		{ ztGuiSprite_IconArrowBottomRight4     , "gui_icon_arrow_bottom_right_4"        },
		{ ztGuiSprite_IconArrowBottomRight5     , "gui_icon_arrow_bottom_right_5"        },
		{ ztGuiSprite_IconPaste                 , "gui_icon_paste"                       },
		{ ztGuiSprite_IconRedo                  , "gui_icon_redo"                        },
		{ ztGuiSprite_IconFind                  , "gui_icon_find"                        },
		{ ztGuiSprite_IconPrint                 , "gui_icon_print"                       },
		{ ztGuiSprite_IconAnchor                , "gui_icon_anchor"                      },
		{ ztGuiSprite_IconErase                 , "gui_icon_erase"                       },
		{ ztGuiSprite_IconLessThan              , "gui_icon_less_than"                   },
		{ ztGuiSprite_IconGreaterThan           , "gui_icon_greater_than"                },
		{ ztGuiSprite_IconQuote                 , "gui_icon_quote"                       },
		{ ztGuiSprite_IconParagraph             , "gui_icon_paragraph"                   },
		{ ztGuiSprite_IconTextBackground        , "gui_icon_text_background"             },
		{ ztGuiSprite_IconTextForeground        , "gui_icon_text_foreground"             },
		{ ztGuiSprite_IconLine                  , "gui_icon_line"                        },
		{ ztGuiSprite_IconArrowStyleDown        , "gui_icon_arrow_style_down"            },
		{ ztGuiSprite_IconArrowStyleDown2       , "gui_icon_arrow_style_down_2"          },
		{ ztGuiSprite_IconVolumeOff             , "gui_icon_volume_off"                  },
		{ ztGuiSprite_IconVolumeHalf            , "gui_icon_volume_half"                 },
		{ ztGuiSprite_IconVolumeFull            , "gui_icon_volume_full"                 },
		{ ztGuiSprite_IconPlay2                 , "gui_icon_play_2"                      },
		{ ztGuiSprite_IconPause2                , "gui_icon_pause_2"                     },
		{ ztGuiSprite_IconRewind2               , "gui_icon_rewind_2"                    },
		{ ztGuiSprite_IconFastForward2          , "gui_icon_fastforward_2"               },
		{ ztGuiSprite_IconBegin2                , "gui_icon_begin_2"                     },
		{ ztGuiSprite_IconEnd2                  , "gui_icon_end_2"                       },
		{ ztGuiSprite_IconHeadphones            , "gui_icon_headphones"                  },
		{ ztGuiSprite_IconMicrophone            , "gui_icon_microphone"                  },
		{ ztGuiSprite_IconLoop                  , "gui_icon_loop"                        },
		{ ztGuiSprite_IconLoop2                 , "gui_icon_loop_2"                      },
		{ ztGuiSprite_IconLoop3                 , "gui_icon_loop_3"                      },
		{ ztGuiSprite_IconLoop4                 , "gui_icon_loop_4"                      },
		{ ztGuiSprite_IconLoop5                 , "gui_icon_loop_5"                      },
		{ ztGuiSprite_IconQuestion              , "gui_icon_question"                    },
		{ ztGuiSprite_IconExclaim               , "gui_icon_exclaim"                     },
		{ ztGuiSprite_IconInfo                  , "gui_icon_info"                        },
		{ ztGuiSprite_IconQuestion2             , "gui_icon_question_2"                  },
		{ ztGuiSprite_IconExclaim2              , "gui_icon_exclaim_2"                   },
		{ ztGuiSprite_IconInfo2                 , "gui_icon_info_2"                      },
		{ ztGuiSprite_IconMinus3                , "gui_icon_minus_3"                     },
		{ ztGuiSprite_IconPlus3                 , "gui_icon_plus_3"                      },
		{ ztGuiSprite_IconMinus2                , "gui_icon_minus_2"                     },
		{ ztGuiSprite_IconPlus2                 , "gui_icon_plus_2"                      },
		{ ztGuiSprite_IconMinus4                , "gui_icon_minus_4"                     },
		{ ztGuiSprite_IconPlus4                 , "gui_icon_plus_4"                      },
		{ ztGuiSprite_IconBigPlus               , "gui_icon_big_plus"                    },
		{ ztGuiSprite_IconBigMinus              , "gui_icon_big_minus"                   },
		{ ztGuiSprite_IconPower                 , "gui_icon_power"                       },
		{ ztGuiSprite_IconDrag                  , "gui_icon_drag"                        },
		{ ztGuiSprite_IconResizeHorz            , "gui_icon_resize_horz"                 },
		{ ztGuiSprite_IconResizeCardinal        , "gui_icon_resize_cardinal"             },
		{ ztGuiSprite_IconExpand                , "gui_icon_expand"                      },
		{ ztGuiSprite_IconResizeSwNe            , "gui_icon_resize_sw_ne"                },
		{ ztGuiSprite_IconArrowOut              , "gui_icon_arrow_out"                   },
		{ ztGuiSprite_IconArrowLoop             , "gui_icon_arrow_loop"                  },
		{ ztGuiSprite_IconBottom                , "gui_icon_bottom"                      },
		{ ztGuiSprite_IconBottom2               , "gui_icon_bottom_2"                    },
		{ ztGuiSprite_IconBottom3               , "gui_icon_bottom_3"                    },
		{ ztGuiSprite_IconLabelRight            , "gui_icon_label_right"                 },
		{ ztGuiSprite_IconLabelUp               , "gui_icon_label_up"                    },
		{ ztGuiSprite_IconLabelDown             , "gui_icon_label_down"                  },
		{ ztGuiSprite_IconLabelLeft             , "gui_icon_label_left"                  },
		{ ztGuiSprite_IconResizeNwSe            , "gui_icon_resize_nw_se"                },
	};

	zt_fize(sprite) {
		theme_data->sprite[sprite[i].val] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, sprite[i].name);
		if (theme_data->sprite[sprite[i].val] == nullptr) {
			zt_logCritical("Missing GUI theme sprite (%s)", sprite[i].name);
			theme_data->sprite[sprite[i].val] = zt_spriteManagerGetSprite(&theme_data->sprite_manager, "gui_empty");
			//return false;
		}
	}
	zt_fize(theme_data->sprite) {
		if (theme_data->sprite[i] == nullptr) {
			zt_assert(false); // an entry is missing from the above array
		}
	}


	{
		// default font
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"><description size=\"12\" family=\"Roboto\" style=\"Regular\"/><metrics ascender=\"12\" height=\"14\" descender=\"-3\"/><texture width=\"1024\" height=\"32\" file=\"roboto_regular_12.png\"/><chars><char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"12\" rect_h=\"0\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"4\" id=\"&quot;\" rect_x=\"8\" rect_y=\"2\" rect_h=\"3\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"#\" rect_x=\"13\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"7\" id=\"$\" rect_x=\"22\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"9\" rect_w=\"10\" id=\"%\" rect_x=\"30\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"&amp;\" rect_x=\"41\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"'\" rect_x=\"50\" rect_y=\"2\" rect_h=\"3\"/><char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"(\" rect_x=\"54\" rect_y=\"1\" rect_h=\"14\"/><char offset_x=\"-1\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\")\" rect_x=\"60\" rect_y=\"1\" rect_h=\"14\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"5\" rect_w=\"7\" id=\"*\" rect_x=\"66\" rect_y=\"3\" rect_h=\"6\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"+\" rect_x=\"74\" rect_y=\"4\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"1\" advance=\"3\" rect_w=\"3\" id=\",\" rect_x=\"82\" rect_y=\"11\" rect_h=\"4\"/><char offset_x=\"0\" offset_y=\"4\" advance=\"3\" rect_w=\"5\" id=\"-\" rect_x=\"86\" rect_y=\"8\" rect_h=\"1\"/><char offset_x=\"0\" offset_y=\"1\" advance=\"3\" rect_w=\"3\" id=\".\" rect_x=\"92\" rect_y=\"11\" rect_h=\"1\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"/\" rect_x=\"96\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"0\" rect_x=\"103\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"5\" id=\"1\" rect_x=\"111\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"2\" rect_x=\"117\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"3\" rect_x=\"126\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"4\" rect_x=\"134\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"5\" rect_x=\"144\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"6\" rect_x=\"153\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"7\" rect_x=\"161\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"8\" rect_x=\"169\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"9\" rect_x=\"177\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"3\" rect_w=\"3\" id=\":\" rect_x=\"185\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"2\" rect_w=\"3\" id=\";\" rect_x=\"189\" rect_y=\"5\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"&lt;\" rect_x=\"193\" rect_y=\"5\" rect_h=\"6\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"=\" rect_x=\"200\" rect_y=\"5\" rect_h=\"4\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\">\" rect_x=\"207\" rect_y=\"5\" rect_h=\"6\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"?\" rect_x=\"214\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"12\" rect_w=\"12\" id=\"@\" rect_x=\"221\" rect_y=\"3\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"A\" rect_x=\"234\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"B\" rect_x=\"244\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"C\" rect_x=\"253\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"D\" rect_x=\"263\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"E\" rect_x=\"272\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"8\" id=\"F\" rect_x=\"281\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"G\" rect_x=\"290\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"H\" rect_x=\"299\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"3\" id=\"I\" rect_x=\"308\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"J\" rect_x=\"312\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"K\" rect_x=\"320\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"7\" id=\"L\" rect_x=\"330\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"10\" rect_w=\"10\" id=\"M\" rect_x=\"338\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"N\" rect_x=\"349\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"9\" rect_w=\"9\" id=\"O\" rect_x=\"358\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"P\" rect_x=\"368\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"9\" rect_w=\"9\" id=\"Q\" rect_x=\"377\" rect_y=\"3\" rect_h=\"11\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"R\" rect_x=\"387\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"S\" rect_x=\"396\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"T\" rect_x=\"405\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"U\" rect_x=\"414\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"V\" rect_x=\"423\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"11\" rect_w=\"12\" id=\"W\" rect_x=\"433\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"X\" rect_x=\"446\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"Y\" rect_x=\"456\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"Z\" rect_x=\"466\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"5\" id=\"[\" rect_x=\"474\" rect_y=\"1\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"\\\" rect_x=\"480\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"-1\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"]\" rect_x=\"487\" rect_y=\"1\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"^\" rect_x=\"492\" rect_y=\"3\" rect_h=\"5\"/><char offset_x=\"0\" offset_y=\"0\" advance=\"5\" rect_w=\"7\" id=\"_\" rect_x=\"499\" rect_y=\"12\" rect_h=\"1\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"4\" id=\"`\" rect_x=\"507\" rect_y=\"2\" rect_h=\"2\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"a\" rect_x=\"512\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"6\" rect_w=\"7\" id=\"b\" rect_x=\"521\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"c\" rect_x=\"529\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"d\" rect_x=\"538\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"e\" rect_x=\"546\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"-1\" offset_y=\"10\" advance=\"4\" rect_w=\"6\" id=\"f\" rect_x=\"554\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"g\" rect_x=\"561\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"h\" rect_x=\"569\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"4\" id=\"i\" rect_x=\"577\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"3\" rect_w=\"5\" id=\"j\" rect_x=\"582\" rect_y=\"3\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"6\" rect_w=\"8\" id=\"k\" rect_x=\"588\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"l\" rect_x=\"597\" rect_y=\"2\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"11\" rect_w=\"11\" id=\"m\" rect_x=\"601\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"n\" rect_x=\"613\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"o\" rect_x=\"621\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"p\" rect_x=\"630\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"q\" rect_x=\"638\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"8\" advance=\"4\" rect_w=\"5\" id=\"r\" rect_x=\"646\" rect_y=\"4\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"s\" rect_x=\"652\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"4\" rect_w=\"6\" id=\"t\" rect_x=\"660\" rect_y=\"3\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"u\" rect_x=\"667\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"v\" rect_x=\"675\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"9\" rect_w=\"10\" id=\"w\" rect_x=\"683\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"x\" rect_x=\"694\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"y\" rect_x=\"702\" rect_y=\"5\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"z\" rect_x=\"710\" rect_y=\"5\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"6\" id=\"{\" rect_x=\"718\" rect_y=\"2\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"3\" id=\"|\" rect_x=\"725\" rect_y=\"3\" rect_h=\"11\"/><char offset_x=\"-1\" offset_y=\"10\" advance=\"4\" rect_w=\"6\" id=\"}\" rect_x=\"729\" rect_y=\"2\" rect_h=\"13\"/><char offset_x=\"0\" offset_y=\"6\" advance=\"8\" rect_w=\"9\" id=\"~\" rect_x=\"736\" rect_y=\"6\" rect_h=\"3\"/></chars></font>";
		theme_data->font = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 850));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"14\" family=\"Roboto\" style=\"Regular\"/> <metrics ascender=\"13\" height=\"16\" descender=\"-4\"/> <texture width=\"1024\" height=\"32\" file=\"roboto_regular_14.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"13\" rect_h=\"0\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"5\" rect_w=\"6\" id=\"&quot;\" rect_x=\"8\" rect_y=\"2\" rect_h=\"4\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"9\" id=\"#\" rect_x=\"15\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"8\" rect_w=\"9\" id=\"$\" rect_x=\"25\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"11\" rect_w=\"12\" id=\"%\" rect_x=\"35\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"&amp;\" rect_x=\"48\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"'\" rect_x=\"59\" rect_y=\"2\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"(\" rect_x=\"64\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\")\" rect_x=\"71\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"*\" rect_x=\"78\" rect_y=\"2\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"+\" rect_x=\"87\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\",\" rect_x=\"96\" rect_y=\"11\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"5\" advance=\"5\" rect_w=\"4\" id=\"-\" rect_x=\"101\" rect_y=\"8\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\".\" rect_x=\"106\" rect_y=\"11\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"/\" rect_x=\"111\" rect_y=\"2\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"0\" rect_x=\"119\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"1\" rect_x=\"129\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"2\" rect_x=\"136\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"3\" rect_x=\"145\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"4\" rect_x=\"155\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"5\" rect_x=\"164\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"6\" rect_x=\"174\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"7\" rect_x=\"184\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"8\" rect_x=\"193\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"9\" rect_x=\"203\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"3\" rect_w=\"4\" id=\":\" rect_x=\"213\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"3\" rect_w=\"4\" id=\";\" rect_x=\"218\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"&lt;\" rect_x=\"223\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"=\" rect_x=\"231\" rect_y=\"6\" rect_h=\"5\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\">\" rect_x=\"239\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"?\" rect_x=\"247\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"13\" rect_w=\"14\" id=\"@\" rect_x=\"256\" rect_y=\"2\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"A\" rect_x=\"271\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"B\" rect_x=\"282\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"C\" rect_x=\"292\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"D\" rect_x=\"303\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"E\" rect_x=\"314\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"F\" rect_x=\"324\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"G\" rect_x=\"333\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"H\" rect_x=\"344\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"I\" rect_x=\"355\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"J\" rect_x=\"360\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"10\" id=\"K\" rect_x=\"370\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"L\" rect_x=\"381\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"12\" rect_w=\"13\" id=\"M\" rect_x=\"390\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"N\" rect_x=\"404\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"10\" rect_w=\"11\" id=\"O\" rect_x=\"415\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"P\" rect_x=\"427\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"10\" rect_w=\"11\" id=\"Q\" rect_x=\"438\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"R\" rect_x=\"450\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"S\" rect_x=\"461\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"T\" rect_x=\"472\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"U\" rect_x=\"482\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"V\" rect_x=\"493\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"12\" rect_w=\"14\" id=\"W\" rect_x=\"504\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"X\" rect_x=\"519\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"Y\" rect_x=\"530\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"Z\" rect_x=\"541\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"4\" rect_w=\"5\" id=\"[\" rect_x=\"550\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"\\\" rect_x=\"556\" rect_y=\"2\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"4\" rect_w=\"5\" id=\"]\" rect_x=\"564\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"^\" rect_x=\"570\" rect_y=\"2\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"0\" advance=\"8\" rect_w=\"7\" id=\"_\" rect_x=\"578\" rect_y=\"13\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"`\" rect_x=\"586\" rect_y=\"2\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"a\" rect_x=\"592\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"b\" rect_x=\"602\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"c\" rect_x=\"612\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"d\" rect_x=\"621\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"e\" rect_x=\"631\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"6\" rect_w=\"6\" id=\"f\" rect_x=\"641\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"g\" rect_x=\"648\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"h\" rect_x=\"658\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"i\" rect_x=\"668\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"3\" rect_w=\"5\" id=\"j\" rect_x=\"673\" rect_y=\"2\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"8\" id=\"k\" rect_x=\"679\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"l\" rect_x=\"688\" rect_y=\"2\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"13\" rect_w=\"14\" id=\"m\" rect_x=\"693\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"n\" rect_x=\"708\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"o\" rect_x=\"718\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"p\" rect_x=\"728\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"q\" rect_x=\"738\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"r\" rect_x=\"748\" rect_y=\"4\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"s\" rect_x=\"755\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"6\" rect_w=\"5\" id=\"t\" rect_x=\"764\" rect_y=\"3\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"u\" rect_x=\"770\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"v\" rect_x=\"780\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"11\" rect_w=\"12\" id=\"w\" rect_x=\"789\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"x\" rect_x=\"802\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"y\" rect_x=\"811\" rect_y=\"5\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"z\" rect_x=\"820\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"{\" rect_x=\"828\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"|\" rect_x=\"835\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"}\" rect_x=\"840\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"6\" advance=\"10\" rect_w=\"10\" id=\"~\" rect_x=\"847\" rect_y=\"7\" rect_h=\"4\"/> </chars></font>";
		theme_data->font_large = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 870));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"12\" family=\"Roboto\" style=\"Bold\"/> <metrics ascender=\"12\" height=\"14\" descender=\"-3\"/> <texture width=\"1024\" height=\"32\" file=\"roboto_bold_12.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"12\" rect_h=\"0\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"5\" rect_w=\"4\" id=\"&quot;\" rect_x=\"8\" rect_y=\"2\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"#\" rect_x=\"13\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"7\" rect_w=\"7\" id=\"$\" rect_x=\"22\" rect_y=\"1\" rect_h=\"12\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"10\" rect_w=\"9\" id=\"%\" rect_x=\"30\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"9\" id=\"&amp;\" rect_x=\"40\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"'\" rect_x=\"50\" rect_y=\"2\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"(\" rect_x=\"54\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\")\" rect_x=\"60\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"-1\" offset_y=\"9\" advance=\"5\" rect_w=\"7\" id=\"*\" rect_x=\"66\" rect_y=\"3\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"+\" rect_x=\"74\" rect_y=\"4\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\",\" rect_x=\"82\" rect_y=\"10\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"5\" rect_w=\"4\" id=\"-\" rect_x=\"87\" rect_y=\"6\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"3\" rect_w=\"4\" id=\".\" rect_x=\"92\" rect_y=\"10\" rect_h=\"2\"/>  <char offset_x=\"-1\" offset_y=\"9\" advance=\"4\" rect_w=\"7\" id=\"/\" rect_x=\"97\" rect_y=\"3\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"0\" rect_x=\"105\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"5\" id=\"1\" rect_x=\"113\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"2\" rect_x=\"119\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"3\" rect_x=\"127\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"4\" rect_x=\"135\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"5\" rect_x=\"144\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"6\" rect_x=\"153\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"7\" rect_x=\"161\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"8\" rect_x=\"169\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"9\" rect_x=\"177\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"3\" rect_w=\"4\" id=\":\" rect_x=\"185\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"3\" rect_w=\"4\" id=\";\" rect_x=\"190\" rect_y=\"5\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"6\" id=\"&lt;\" rect_x=\"195\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"=\" rect_x=\"202\" rect_y=\"5\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\">\" rect_x=\"209\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"6\" rect_w=\"7\" id=\"?\" rect_x=\"216\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"12\" rect_w=\"11\" id=\"@\" rect_x=\"224\" rect_y=\"3\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"10\" id=\"A\" rect_x=\"236\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"B\" rect_x=\"247\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"C\" rect_x=\"255\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"D\" rect_x=\"264\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"E\" rect_x=\"273\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"F\" rect_x=\"281\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"G\" rect_x=\"289\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"H\" rect_x=\"298\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"4\" rect_w=\"3\" id=\"I\" rect_x=\"307\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"J\" rect_x=\"311\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"K\" rect_x=\"319\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"L\" rect_x=\"328\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"11\" rect_w=\"10\" id=\"M\" rect_x=\"336\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"N\" rect_x=\"347\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"O\" rect_x=\"356\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"P\" rect_x=\"365\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"Q\" rect_x=\"374\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"R\" rect_x=\"383\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"S\" rect_x=\"392\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"T\" rect_x=\"402\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"U\" rect_x=\"411\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"V\" rect_x=\"420\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"11\" rect_w=\"12\" id=\"W\" rect_x=\"430\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"X\" rect_x=\"443\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"8\" rect_w=\"9\" id=\"Y\" rect_x=\"453\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"Z\" rect_x=\"463\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"4\" id=\"[\" rect_x=\"472\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"7\" id=\"\\\" rect_x=\"477\" rect_y=\"3\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"4\" id=\"]\" rect_x=\"485\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"5\" rect_w=\"6\" id=\"^\" rect_x=\"490\" rect_y=\"3\" rect_h=\"5\"/>  <char offset_x=\"0\" offset_y=\"1\" advance=\"6\" rect_w=\"6\" id=\"_\" rect_x=\"497\" rect_y=\"11\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"4\" rect_w=\"5\" id=\"`\" rect_x=\"504\" rect_y=\"2\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"a\" rect_x=\"510\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"b\" rect_x=\"518\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"c\" rect_x=\"526\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"d\" rect_x=\"534\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"e\" rect_x=\"542\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"5\" rect_w=\"5\" id=\"f\" rect_x=\"550\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"g\" rect_x=\"556\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"h\" rect_x=\"564\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"i\" rect_x=\"572\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"-1\" offset_y=\"10\" advance=\"3\" rect_w=\"5\" id=\"j\" rect_x=\"576\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"7\" rect_w=\"7\" id=\"k\" rect_x=\"582\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"3\" rect_w=\"3\" id=\"l\" rect_x=\"590\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"11\" rect_w=\"11\" id=\"m\" rect_x=\"594\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"n\" rect_x=\"606\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"o\" rect_x=\"614\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"p\" rect_x=\"622\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"q\" rect_x=\"630\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"5\" rect_w=\"5\" id=\"r\" rect_x=\"638\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"s\" rect_x=\"644\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"6\" rect_w=\"6\" id=\"t\" rect_x=\"652\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"u\" rect_x=\"659\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"7\" id=\"v\" rect_x=\"667\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"9\" rect_w=\"10\" id=\"w\" rect_x=\"675\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"8\" id=\"x\" rect_x=\"686\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"0\" offset_y=\"7\" advance=\"6\" rect_w=\"8\" id=\"y\" rect_x=\"695\" rect_y=\"5\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"6\" id=\"z\" rect_x=\"704\" rect_y=\"5\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"{\" rect_x=\"711\" rect_y=\"1\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"9\" advance=\"3\" rect_w=\"3\" id=\"|\" rect_x=\"717\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"}\" rect_x=\"721\" rect_y=\"1\" rect_h=\"13\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"8\" rect_w=\"8\" id=\"~\" rect_x=\"727\" rect_y=\"6\" rect_h=\"4\"/> </chars></font>";
		theme_data->font_bold = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 891));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"14\" family=\"Roboto\" style=\"Bold\"/> <metrics ascender=\"13\" height=\"16\" descender=\"-4\"/> <texture width=\"1024\" height=\"32\" file=\"roboto_bold_14.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"3\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"14\" rect_h=\"0\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"!\" rect_x=\"3\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"&quot;\" rect_x=\"9\" rect_y=\"3\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"#\" rect_x=\"15\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"12\" advance=\"9\" rect_w=\"9\" id=\"$\" rect_x=\"25\" rect_y=\"2\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"11\" rect_w=\"11\" id=\"%\" rect_x=\"35\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"10\" id=\"&amp;\" rect_x=\"47\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"3\" rect_w=\"3\" id=\"'\" rect_x=\"58\" rect_y=\"3\" rect_h=\"4\"/>  <char offset_x=\"1\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\"(\" rect_x=\"62\" rect_y=\"2\" rect_h=\"16\"/>  <char offset_x=\"-1\" offset_y=\"12\" advance=\"5\" rect_w=\"6\" id=\")\" rect_x=\"69\" rect_y=\"2\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"8\" id=\"*\" rect_x=\"76\" rect_y=\"3\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"9\" rect_w=\"8\" id=\"+\" rect_x=\"85\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"4\" rect_w=\"4\" id=\",\" rect_x=\"94\" rect_y=\"12\" rect_h=\"5\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"6\" rect_w=\"5\" id=\"-\" rect_x=\"99\" rect_y=\"8\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"2\" advance=\"4\" rect_w=\"5\" id=\".\" rect_x=\"105\" rect_y=\"12\" rect_h=\"2\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"5\" rect_w=\"8\" id=\"/\" rect_x=\"111\" rect_y=\"3\" rect_h=\"12\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"0\" rect_x=\"120\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"6\" id=\"1\" rect_x=\"129\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"2\" rect_x=\"136\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"3\" rect_x=\"145\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"9\" id=\"4\" rect_x=\"154\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"5\" rect_x=\"164\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"6\" rect_x=\"174\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"7\" rect_x=\"183\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"8\" rect_x=\"192\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"9\" rect_x=\"201\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"4\" rect_w=\"5\" id=\":\" rect_x=\"210\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"4\" rect_w=\"4\" id=\";\" rect_x=\"216\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"&lt;\" rect_x=\"221\" rect_y=\"5\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"7\" advance=\"8\" rect_w=\"7\" id=\"=\" rect_x=\"229\" rect_y=\"7\" rect_h=\"5\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\">\" rect_x=\"237\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"7\" rect_w=\"7\" id=\"?\" rect_x=\"245\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"13\" rect_w=\"13\" id=\"@\" rect_x=\"253\" rect_y=\"3\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"11\" id=\"A\" rect_x=\"267\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"B\" rect_x=\"279\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"C\" rect_x=\"288\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"D\" rect_x=\"299\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"E\" rect_x=\"309\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"F\" rect_x=\"318\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"G\" rect_x=\"327\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"H\" rect_x=\"337\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"3\" id=\"I\" rect_x=\"347\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"J\" rect_x=\"351\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"K\" rect_x=\"360\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"L\" rect_x=\"371\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"12\" rect_w=\"11\" id=\"M\" rect_x=\"380\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"N\" rect_x=\"392\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"O\" rect_x=\"402\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"9\" id=\"P\" rect_x=\"412\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"Q\" rect_x=\"422\" rect_y=\"3\" rect_h=\"13\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"R\" rect_x=\"432\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"S\" rect_x=\"442\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"T\" rect_x=\"453\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"U\" rect_x=\"463\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"11\" id=\"V\" rect_x=\"473\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"12\" rect_w=\"14\" id=\"W\" rect_x=\"485\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"9\" rect_w=\"10\" id=\"X\" rect_x=\"500\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"8\" rect_w=\"11\" id=\"Y\" rect_x=\"511\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"10\" rect_w=\"9\" id=\"Z\" rect_x=\"523\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"13\" advance=\"4\" rect_w=\"4\" id=\"[\" rect_x=\"533\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"8\" id=\"\\\" rect_x=\"538\" rect_y=\"3\" rect_h=\"12\"/>  <char offset_x=\"0\" offset_y=\"13\" advance=\"4\" rect_w=\"4\" id=\"]\" rect_x=\"547\" rect_y=\"1\" rect_h=\"15\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"6\" rect_w=\"7\" id=\"^\" rect_x=\"552\" rect_y=\"3\" rect_h=\"6\"/>  <char offset_x=\"0\" offset_y=\"0\" advance=\"7\" rect_w=\"7\" id=\"_\" rect_x=\"560\" rect_y=\"14\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"5\" rect_w=\"5\" id=\"`\" rect_x=\"568\" rect_y=\"3\" rect_h=\"2\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"a\" rect_x=\"574\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"b\" rect_x=\"583\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"c\" rect_x=\"592\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"9\" rect_w=\"8\" id=\"d\" rect_x=\"601\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"e\" rect_x=\"610\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"7\" rect_w=\"6\" id=\"f\" rect_x=\"619\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"9\" rect_w=\"8\" id=\"g\" rect_x=\"626\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"h\" rect_x=\"635\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"4\" id=\"i\" rect_x=\"643\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"-1\" offset_y=\"11\" advance=\"4\" rect_w=\"5\" id=\"j\" rect_x=\"648\" rect_y=\"3\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"k\" rect_x=\"654\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"4\" rect_w=\"3\" id=\"l\" rect_x=\"663\" rect_y=\"3\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"12\" rect_w=\"12\" id=\"m\" rect_x=\"667\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"n\" rect_x=\"680\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"9\" rect_w=\"8\" id=\"o\" rect_x=\"688\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"p\" rect_x=\"697\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"9\" rect_w=\"8\" id=\"q\" rect_x=\"706\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"6\" rect_w=\"5\" id=\"r\" rect_x=\"715\" rect_y=\"5\" rect_h=\"9\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"s\" rect_x=\"721\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"6\" rect_w=\"5\" id=\"t\" rect_x=\"730\" rect_y=\"4\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"u\" rect_x=\"736\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"8\" id=\"v\" rect_x=\"744\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"10\" rect_w=\"12\" id=\"w\" rect_x=\"753\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"9\" id=\"x\" rect_x=\"766\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"7\" rect_w=\"9\" id=\"y\" rect_x=\"776\" rect_y=\"6\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"z\" rect_x=\"786\" rect_y=\"6\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"13\" advance=\"5\" rect_w=\"6\" id=\"{\" rect_x=\"794\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"3\" rect_w=\"3\" id=\"|\" rect_x=\"801\" rect_y=\"3\" rect_h=\"13\"/>  <char offset_x=\"-1\" offset_y=\"13\" advance=\"5\" rect_w=\"6\" id=\"}\" rect_x=\"805\" rect_y=\"1\" rect_h=\"16\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"9\" rect_w=\"9\" id=\"~\" rect_x=\"812\" rect_y=\"8\" rect_h=\"3\"/> </chars></font>";
		theme_data->font_large_bold = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 913));
	}

	{
		// monospaced default
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"><description size=\"12\" family=\"Liberation Mono\" style=\"Regular\"/><metrics ascender=\"10\" height=\"14\" descender=\"-4\"/><texture width=\"1024\" height=\"16\" file=\"liberation_mono_regular_12.png\"/><chars><char offset_x=\"0\" offset_y=\"0\" advance=\"7\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"10\" rect_h=\"0\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"3\" id=\"!\" rect_x=\"3\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"&quot;\" rect_x=\"7\" rect_y=\"1\" rect_h=\"4\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"#\" rect_x=\"14\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"$\" rect_x=\"23\" rect_y=\"1\" rect_h=\"10\"/><char offset_x=\"-1\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"%\" rect_x=\"31\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"&amp;\" rect_x=\"41\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"3\" id=\"'\" rect_x=\"51\" rect_y=\"1\" rect_h=\"4\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"(\" rect_x=\"55\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"5\" id=\")\" rect_x=\"62\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"*\" rect_x=\"68\" rect_y=\"1\" rect_h=\"5\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"+\" rect_x=\"75\" rect_y=\"3\" rect_h=\"6\"/><char offset_x=\"1\" offset_y=\"2\" advance=\"7\" rect_w=\"5\" id=\",\" rect_x=\"84\" rect_y=\"8\" rect_h=\"4\"/><char offset_x=\"2\" offset_y=\"4\" advance=\"7\" rect_w=\"4\" id=\"-\" rect_x=\"90\" rect_y=\"6\" rect_h=\"1\"/><char offset_x=\"2\" offset_y=\"2\" advance=\"7\" rect_w=\"3\" id=\".\" rect_x=\"95\" rect_y=\"8\" rect_h=\"2\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"/\" rect_x=\"99\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"0\" rect_x=\"108\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"1\" rect_x=\"117\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"2\" rect_x=\"126\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"3\" rect_x=\"135\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"4\" rect_x=\"143\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"5\" rect_x=\"153\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"6\" rect_x=\"161\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"7\" rect_x=\"169\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"8\" rect_x=\"177\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"9\" rect_x=\"185\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"2\" offset_y=\"7\" advance=\"7\" rect_w=\"3\" id=\":\" rect_x=\"193\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"2\" offset_y=\"7\" advance=\"7\" rect_w=\"4\" id=\";\" rect_x=\"197\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"7\" id=\"&lt;\" rect_x=\"202\" rect_y=\"2\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"6\" advance=\"7\" rect_w=\"8\" id=\"=\" rect_x=\"210\" rect_y=\"4\" rect_h=\"4\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"7\" id=\">\" rect_x=\"219\" rect_y=\"2\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"?\" rect_x=\"227\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"@\" rect_x=\"236\" rect_y=\"1\" rect_h=\"11\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"A\" rect_x=\"246\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"B\" rect_x=\"256\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"C\" rect_x=\"265\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"D\" rect_x=\"274\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"E\" rect_x=\"283\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"F\" rect_x=\"292\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"G\" rect_x=\"301\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"H\" rect_x=\"310\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"I\" rect_x=\"318\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"J\" rect_x=\"325\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"K\" rect_x=\"332\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"L\" rect_x=\"342\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"M\" rect_x=\"350\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"N\" rect_x=\"359\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"O\" rect_x=\"367\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"P\" rect_x=\"376\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"Q\" rect_x=\"385\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"R\" rect_x=\"395\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"S\" rect_x=\"405\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"T\" rect_x=\"414\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"U\" rect_x=\"423\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"V\" rect_x=\"431\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"9\" id=\"W\" rect_x=\"441\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"X\" rect_x=\"451\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"Y\" rect_x=\"460\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"Z\" rect_x=\"469\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"[\" rect_x=\"478\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"\\\" rect_x=\"485\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"5\" id=\"]\" rect_x=\"494\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"^\" rect_x=\"500\" rect_y=\"1\" rect_h=\"6\"/><char offset_x=\"-1\" offset_y=\"-1\" advance=\"7\" rect_w=\"10\" id=\"_\" rect_x=\"509\" rect_y=\"11\" rect_h=\"1\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"4\" id=\"`\" rect_x=\"520\" rect_y=\"1\" rect_h=\"2\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"a\" rect_x=\"525\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"b\" rect_x=\"534\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"c\" rect_x=\"542\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"d\" rect_x=\"551\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"e\" rect_x=\"559\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"f\" rect_x=\"568\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"g\" rect_x=\"576\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"h\" rect_x=\"584\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"i\" rect_x=\"592\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"6\" id=\"j\" rect_x=\"601\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"k\" rect_x=\"608\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"8\" id=\"l\" rect_x=\"617\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"m\" rect_x=\"626\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"n\" rect_x=\"634\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"o\" rect_x=\"642\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"p\" rect_x=\"651\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"q\" rect_x=\"659\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"8\" advance=\"7\" rect_w=\"7\" id=\"r\" rect_x=\"667\" rect_y=\"2\" rect_h=\"8\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"s\" rect_x=\"675\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"t\" rect_x=\"683\" rect_y=\"1\" rect_h=\"9\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"u\" rect_x=\"691\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"v\" rect_x=\"699\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"9\" id=\"w\" rect_x=\"708\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"x\" rect_x=\"718\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"0\" offset_y=\"7\" advance=\"7\" rect_w=\"8\" id=\"y\" rect_x=\"727\" rect_y=\"3\" rect_h=\"10\"/><char offset_x=\"1\" offset_y=\"7\" advance=\"7\" rect_w=\"7\" id=\"z\" rect_x=\"736\" rect_y=\"3\" rect_h=\"7\"/><char offset_x=\"1\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"{\" rect_x=\"744\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"2\" offset_y=\"9\" advance=\"7\" rect_w=\"3\" id=\"|\" rect_x=\"752\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"0\" offset_y=\"9\" advance=\"7\" rect_w=\"7\" id=\"}\" rect_x=\"756\" rect_y=\"1\" rect_h=\"12\"/><char offset_x=\"1\" offset_y=\"5\" advance=\"7\" rect_w=\"7\" id=\"~\" rect_x=\"764\" rect_y=\"5\" rect_h=\"2\"/></chars></font>";
		theme_data->font_monospace = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 985));
	}

	{
		char *data = "<?xml version=\"1.0\" encoding=\"utf-8\"?><font type=\"NGL\"> <description size=\"14\" family=\"Liberation Mono\" style=\"Regular\"/> <metrics ascender=\"12\" height=\"16\" descender=\"-5\"/> <texture width=\"1024\" height=\"32\" file=\"liberation_mono_regular_14.png\"/> <chars>  <char offset_x=\"0\" offset_y=\"0\" advance=\"8\" rect_w=\"1\" id=\" \" rect_x=\"1\" rect_y=\"12\" rect_h=\"0\"/>  <char offset_x=\"3\" offset_y=\"10\" advance=\"8\" rect_w=\"4\" id=\"!\" rect_x=\"3\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"&quot;\" rect_x=\"8\" rect_y=\"1\" rect_h=\"5\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"#\" rect_x=\"16\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"10\" id=\"$\" rect_x=\"26\" rect_y=\"1\" rect_h=\"12\"/>  <char offset_x=\"-1\" offset_y=\"10\" advance=\"8\" rect_w=\"11\" id=\"%\" rect_x=\"37\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"&amp;\" rect_x=\"49\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"3\" offset_y=\"11\" advance=\"8\" rect_w=\"4\" id=\"'\" rect_x=\"60\" rect_y=\"1\" rect_h=\"5\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"(\" rect_x=\"65\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\")\" rect_x=\"72\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"*\" rect_x=\"79\" rect_y=\"1\" rect_h=\"6\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"8\" id=\"+\" rect_x=\"88\" rect_y=\"4\" rect_h=\"7\"/>  <char offset_x=\"1\" offset_y=\"2\" advance=\"8\" rect_w=\"5\" id=\",\" rect_x=\"97\" rect_y=\"10\" rect_h=\"5\"/>  <char offset_x=\"2\" offset_y=\"4\" advance=\"8\" rect_w=\"5\" id=\"-\" rect_x=\"103\" rect_y=\"8\" rect_h=\"1\"/>  <char offset_x=\"3\" offset_y=\"3\" advance=\"8\" rect_w=\"4\" id=\".\" rect_x=\"109\" rect_y=\"9\" rect_h=\"3\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"/\" rect_x=\"114\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"0\" rect_x=\"124\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"1\" rect_x=\"134\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"2\" rect_x=\"144\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"3\" rect_x=\"153\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"4\" rect_x=\"163\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"5\" rect_x=\"172\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"6\" rect_x=\"182\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"7\" id=\"7\" rect_x=\"192\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"8\" rect_x=\"200\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"9\" rect_x=\"210\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"3\" offset_y=\"8\" advance=\"8\" rect_w=\"4\" id=\":\" rect_x=\"220\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"2\" offset_y=\"8\" advance=\"8\" rect_w=\"5\" id=\";\" rect_x=\"225\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\"&lt;\" rect_x=\"231\" rect_y=\"3\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"8\" id=\">\" rect_x=\"240\" rect_y=\"3\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"?\" rect_x=\"249\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"11\" id=\"@\" rect_x=\"259\" rect_y=\"1\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"A\" rect_x=\"271\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"B\" rect_x=\"282\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"C\" rect_x=\"292\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"D\" rect_x=\"302\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"E\" rect_x=\"312\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"F\" rect_x=\"322\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"G\" rect_x=\"331\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"H\" rect_x=\"341\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"7\" id=\"I\" rect_x=\"351\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"J\" rect_x=\"359\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"K\" rect_x=\"368\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"L\" rect_x=\"379\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"M\" rect_x=\"388\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"N\" rect_x=\"398\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"O\" rect_x=\"408\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"P\" rect_x=\"419\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"Q\" rect_x=\"429\" rect_y=\"2\" rect_h=\"13\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"R\" rect_x=\"440\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"S\" rect_x=\"450\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"T\" rect_x=\"460\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"U\" rect_x=\"469\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"V\" rect_x=\"479\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"W\" rect_x=\"490\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"X\" rect_x=\"501\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"10\" id=\"Y\" rect_x=\"512\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"8\" id=\"Z\" rect_x=\"523\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"[\" rect_x=\"532\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"\\\" rect_x=\"539\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"2\" offset_y=\"11\" advance=\"8\" rect_w=\"6\" id=\"]\" rect_x=\"549\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"0\" offset_y=\"10\" advance=\"8\" rect_w=\"9\" id=\"^\" rect_x=\"556\" rect_y=\"2\" rect_h=\"7\"/>  <char offset_x=\"-1\" offset_y=\"-1\" advance=\"8\" rect_w=\"11\" id=\"_\" rect_x=\"566\" rect_y=\"13\" rect_h=\"1\"/>  <char offset_x=\"3\" offset_y=\"11\" advance=\"8\" rect_w=\"4\" id=\"`\" rect_x=\"578\" rect_y=\"1\" rect_h=\"2\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"10\" id=\"a\" rect_x=\"583\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"b\" rect_x=\"594\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"c\" rect_x=\"604\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"d\" rect_x=\"614\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"e\" rect_x=\"624\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"f\" rect_x=\"634\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"g\" rect_x=\"643\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"11\" advance=\"8\" rect_w=\"9\" id=\"h\" rect_x=\"653\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"i\" rect_x=\"663\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"j\" rect_x=\"672\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"k\" rect_x=\"680\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"l\" rect_x=\"689\" rect_y=\"1\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"10\" id=\"m\" rect_x=\"698\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"n\" rect_x=\"709\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"o\" rect_x=\"719\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"p\" rect_x=\"729\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"q\" rect_x=\"739\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"9\" advance=\"8\" rect_w=\"7\" id=\"r\" rect_x=\"749\" rect_y=\"3\" rect_h=\"9\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"s\" rect_x=\"757\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"10\" advance=\"8\" rect_w=\"7\" id=\"t\" rect_x=\"767\" rect_y=\"2\" rect_h=\"10\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"u\" rect_x=\"775\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"v\" rect_x=\"785\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"-1\" offset_y=\"8\" advance=\"8\" rect_w=\"11\" id=\"w\" rect_x=\"795\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"x\" rect_x=\"807\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"0\" offset_y=\"8\" advance=\"8\" rect_w=\"9\" id=\"y\" rect_x=\"817\" rect_y=\"4\" rect_h=\"11\"/>  <char offset_x=\"1\" offset_y=\"8\" advance=\"8\" rect_w=\"7\" id=\"z\" rect_x=\"827\" rect_y=\"4\" rect_h=\"8\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"8\" id=\"{\" rect_x=\"835\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"3\" offset_y=\"11\" advance=\"8\" rect_w=\"4\" id=\"|\" rect_x=\"844\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"11\" advance=\"8\" rect_w=\"7\" id=\"}\" rect_x=\"849\" rect_y=\"1\" rect_h=\"14\"/>  <char offset_x=\"1\" offset_y=\"6\" advance=\"8\" rect_w=\"8\" id=\"~\" rect_x=\"857\" rect_y=\"6\" rect_h=\"2\"/> </chars></font>";
		theme_data->font_monospace_large = zt_fontMakeFromBmpFontData(data, theme_data->texture, zt_vec2i(0, 1003));
	}

	theme->theme_data = theme_data;

	theme->get_rvalue       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetRValue);
	theme->get_ivalue       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetIValue);
	theme->get_color        = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetColor);
	theme->get_sprite       = ZT_FUNCTION_POINTER_TO_VAR(_zt_guiDefaultThemeGetSprite);
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

bool zt_guiDefaultThemeMake(ztGuiTheme *theme, ztCamera *gui_camera, const char *gui_texture_file, const char *gui_sprite_file)
{
	zt_returnValOnNull(theme, false);
	zt_returnValOnNull(gui_camera, false);
	zt_returnValOnNull(gui_texture_file, false);
	zt_returnValOnNull(gui_sprite_file, false);

	ztGuiThemeData *theme_data = zt_mallocStruct(ztGuiThemeData);

	theme_data->texture = zt_textureMakeFromFile(gui_texture_file, ztTextureFlags_PixelPerfect);
	if (theme_data->texture == ztInvalidID) {
		return false;
	}

	zt_spriteManagerMake(&theme_data->sprite_manager, ZT_GUI_DEFAULT_THEME_SPRITE_MANAGER_MAX_SPRITES);

	i32 sprite_manager_data_size = 0;
	void *sprite_manager_data = zt_readEntireFile(gui_sprite_file, &sprite_manager_data_size, false, zt_memGetTempArena());
	if (sprite_manager_data == nullptr) {
		return false;
	}

	if (!zt_spriteManagerLoad(&theme_data->sprite_manager, sprite_manager_data, sprite_manager_data_size, theme_data->texture)) {
		zt_freeArena(sprite_manager_data, zt_memGetTempArena());
		return false;
	}

	zt_freeArena(sprite_manager_data, zt_memGetTempArena());
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
