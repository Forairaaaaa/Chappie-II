// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: Watch

#ifndef _WATCH_UI_H
#define _WATCH_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void WatchLaughPointerRotate_Animation_hour(lv_obj_t * TargetObject, int delay);
void WatchLaughPointerRotate_Animation_minute(lv_obj_t * TargetObject, int delay);
extern lv_obj_t * ui_ScreenWatchWarma;
extern lv_obj_t * ui_WatchWarmaBG;
extern lv_obj_t * ui_WatchWarmaLabel;
extern lv_obj_t * ui_ScreenWatchThink;
extern lv_obj_t * ui_WatchThinkBG;
extern lv_obj_t * ui_WatchThinkLabelHour;
extern lv_obj_t * ui_WatchThinkLabelMinute;
extern lv_obj_t * ui_ScreenWatchLaugh;
extern lv_obj_t * ui_WatchLaughBG;
extern lv_obj_t * ui_WatchLaughHour;
extern lv_obj_t * ui_WatchLaughMinute;
extern lv_obj_t * ui_WatchLaughSecond;


LV_IMG_DECLARE(ui_img_warma_png);    // assets\Warma.png
LV_IMG_DECLARE(ui_img_think_png);    // assets\Think.png
LV_IMG_DECLARE(ui_img_bg_laugh_png);    // assets\BG_Laugh.png
LV_IMG_DECLARE(ui_img_laugh_hour_png);    // assets\Laugh_Hour.png
LV_IMG_DECLARE(ui_img_laugh_minute_png);    // assets\Laugh_Minute.png
LV_IMG_DECLARE(ui_img_laugh_second_png);    // assets\Laugh_Second.png
LV_IMG_DECLARE(ui_img_icon_clock_png);    // assets\Icon_Clock.png
LV_IMG_DECLARE(ui_img_icon_setting_png);    // assets\Icon_Setting.png


LV_FONT_DECLARE(ui_font_MontserratBold48);


void watch_ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
