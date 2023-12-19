// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: ChappieUI_Launcher

#ifndef _CHAPPIEUI_LAUNCHER_UI_H
#define _CHAPPIEUI_LAUNCHER_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void StateBarDropDown_Animation(lv_obj_t * TargetObject, int delay);
void StateBarPullUp_Animation(lv_obj_t * TargetObject, int delay);
extern lv_obj_t * ui_ScreenLauncher;
extern lv_obj_t * ui_PanelDesktop;
extern lv_obj_t * ui_PanelControlPad;
extern lv_obj_t * ui_ArcBrightness;
extern lv_obj_t * ui_LabelBrightness;
extern lv_obj_t * ui_ButtonAutoScreenOff;
extern lv_obj_t * ui_LabelBtnAutoScreenOff;
extern lv_obj_t * ui_ButtonInfos;
extern lv_obj_t * ui_ButtonWifi;
extern lv_obj_t * ui_ButtonBle;
extern lv_obj_t * ui_PanelHome;
extern lv_obj_t * ui_LabelHomeTime;
extern lv_obj_t * ui_LabelStateBarTime1;
extern lv_obj_t * ui_ImgStateBar;
extern lv_obj_t * ui_LabelStateBarTime;
extern lv_obj_t * ui_ImgBattery;
extern lv_obj_t * ui_BatteryBar;


LV_IMG_DECLARE(ui_img_img_infos_png);    // assets\IMG_Infos.png
LV_IMG_DECLARE(ui_img_img_wifi_png);    // assets\IMG_Wifi.png
LV_IMG_DECLARE(ui_img_img_ble_png);    // assets\IMG_Ble.png
LV_IMG_DECLARE(ui_img_img_statebar_png);    // assets\IMG_StateBar.png
LV_IMG_DECLARE(ui_img_img_battery_png);    // assets\IMG_Battery.png
LV_IMG_DECLARE(ui_img_img_icon_defalut_png);    // assets\IMG_Icon_Defalut.png


LV_FONT_DECLARE(ui_font_FontUbuntuBold16);
LV_FONT_DECLARE(ui_font_FontUbuntuBold18);
LV_FONT_DECLARE(ui_font_FontUbuntuBold96);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
