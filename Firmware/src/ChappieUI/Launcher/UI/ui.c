// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: ChappieUI_Launcher

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void StateBarDropDown_Animation(lv_obj_t * TargetObject, int delay);
void StateBarPullUp_Animation(lv_obj_t * TargetObject, int delay);
lv_obj_t * ui_ScreenLauncher;
lv_obj_t * ui_PanelDesktop;
lv_obj_t * ui_PanelControlPad;
lv_obj_t * ui_ArcBrightness;
lv_obj_t * ui_LabelBrightness;
lv_obj_t * ui_ButtonAutoScreenOff;
lv_obj_t * ui_LabelBtnAutoScreenOff;
lv_obj_t * ui_ButtonInfos;
lv_obj_t * ui_ButtonWifi;
lv_obj_t * ui_ButtonBle;
lv_obj_t * ui_PanelHome;
lv_obj_t * ui_LabelHomeTime;
lv_obj_t * ui_LabelStateBarTime1;
lv_obj_t * ui_ImgStateBar;
lv_obj_t * ui_LabelStateBarTime;
lv_obj_t * ui_ImgBattery;
lv_obj_t * ui_BatteryBar;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void StateBarDropDown_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -135, -105);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void StateBarPullUp_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -105, -135);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_ScreenLauncher_screen_init(void)
{
    ui_ScreenLauncher = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenLauncher, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PanelDesktop = lv_obj_create(ui_ScreenLauncher);
    lv_obj_set_width(ui_PanelDesktop, 280);
    lv_obj_set_height(ui_PanelDesktop, 240);
    lv_obj_set_align(ui_PanelDesktop, LV_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(ui_PanelDesktop, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_PanelDesktop, LV_DIR_HOR);
    lv_obj_set_style_radius(ui_PanelDesktop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelDesktop, lv_color_hex(0x4D5B74), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelDesktop, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelDesktop, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelDesktop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelControlPad = lv_obj_create(ui_PanelDesktop);
    lv_obj_set_width(ui_PanelControlPad, 280);
    lv_obj_set_height(ui_PanelControlPad, 240);
    lv_obj_set_align(ui_PanelControlPad, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelControlPad, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scrollbar_mode(ui_PanelControlPad, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_PanelControlPad, LV_DIR_HOR);
    lv_obj_set_style_radius(ui_PanelControlPad, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelControlPad, lv_color_hex(0x4D5B74), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelControlPad, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelControlPad, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelControlPad, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ArcBrightness = lv_arc_create(ui_PanelControlPad);
    lv_obj_set_width(ui_ArcBrightness, 273);
    lv_obj_set_height(ui_ArcBrightness, 275);
    lv_obj_set_x(ui_ArcBrightness, 0);
    lv_obj_set_y(ui_ArcBrightness, 134);
    lv_obj_set_align(ui_ArcBrightness, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_ArcBrightness, 0, 255);
    lv_arc_set_value(ui_ArcBrightness, 100);
    lv_arc_set_bg_angles(ui_ArcBrightness, 200, 340);

    lv_obj_set_style_arc_color(ui_ArcBrightness, lv_color_hex(0xA6B4CD), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcBrightness, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcBrightness, lv_color_hex(0xA6B4CD), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcBrightness, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_LabelBrightness = lv_label_create(ui_ArcBrightness);
    lv_obj_set_width(ui_LabelBrightness, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelBrightness, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelBrightness, 0);
    lv_obj_set_y(ui_LabelBrightness, -88);
    lv_obj_set_align(ui_LabelBrightness, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelBrightness, "BRIGHTNESS");
    lv_obj_set_style_text_color(ui_LabelBrightness, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelBrightness, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelBrightness, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelBrightness, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelBrightness, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelBrightness, &ui_font_FontUbuntuBold16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonAutoScreenOff = lv_btn_create(ui_ArcBrightness);
    lv_obj_set_width(ui_ButtonAutoScreenOff, 155);
    lv_obj_set_height(ui_ButtonAutoScreenOff, 38);
    lv_obj_set_x(ui_ButtonAutoScreenOff, 0);
    lv_obj_set_y(ui_ButtonAutoScreenOff, -44);
    lv_obj_set_align(ui_ButtonAutoScreenOff, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonAutoScreenOff, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAutoScreenOff, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ButtonAutoScreenOff, 19, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonAutoScreenOff, lv_color_hex(0xA6B4CD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAutoScreenOff, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonAutoScreenOff, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonAutoScreenOff, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonAutoScreenOff, lv_color_hex(0x7FD19A), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_ButtonAutoScreenOff, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_LabelBtnAutoScreenOff = lv_label_create(ui_ButtonAutoScreenOff);
    lv_obj_set_width(ui_LabelBtnAutoScreenOff, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelBtnAutoScreenOff, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelBtnAutoScreenOff, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelBtnAutoScreenOff, "AutoScreenOff");
    lv_obj_set_style_text_color(ui_LabelBtnAutoScreenOff, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelBtnAutoScreenOff, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelBtnAutoScreenOff, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelBtnAutoScreenOff, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelBtnAutoScreenOff, &ui_font_FontUbuntuBold16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonInfos = lv_btn_create(ui_PanelControlPad);
    lv_obj_set_width(ui_ButtonInfos, 60);
    lv_obj_set_height(ui_ButtonInfos, 60);
    lv_obj_set_x(ui_ButtonInfos, -90);
    lv_obj_set_y(ui_ButtonInfos, -53);
    lv_obj_set_align(ui_ButtonInfos, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonInfos, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonInfos, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ButtonInfos, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonInfos, lv_color_hex(0xA6B4CD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonInfos, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ButtonInfos, &ui_img_img_infos_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonInfos, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonInfos, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonInfos, lv_color_hex(0x7FD19A), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_ButtonInfos, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ButtonWifi = lv_btn_create(ui_PanelControlPad);
    lv_obj_set_width(ui_ButtonWifi, 60);
    lv_obj_set_height(ui_ButtonWifi, 60);
    lv_obj_set_x(ui_ButtonWifi, 0);
    lv_obj_set_y(ui_ButtonWifi, -53);
    lv_obj_set_align(ui_ButtonWifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonWifi, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonWifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ButtonWifi, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonWifi, lv_color_hex(0xA6B4CD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ButtonWifi, &ui_img_img_wifi_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonWifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonWifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonWifi, lv_color_hex(0x7FD19A), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_ButtonWifi, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_ButtonBle = lv_btn_create(ui_PanelControlPad);
    lv_obj_set_width(ui_ButtonBle, 60);
    lv_obj_set_height(ui_ButtonBle, 60);
    lv_obj_set_x(ui_ButtonBle, 90);
    lv_obj_set_y(ui_ButtonBle, -53);
    lv_obj_set_align(ui_ButtonBle, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonBle, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonBle, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_ButtonBle, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonBle, lv_color_hex(0xA6B4CD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonBle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ButtonBle, &ui_img_img_ble_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonBle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonBle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonBle, lv_color_hex(0x7FD19A), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_ButtonBle, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_PanelHome = lv_obj_create(ui_PanelDesktop);
    lv_obj_set_width(ui_PanelHome, 280);
    lv_obj_set_height(ui_PanelHome, 240);
    lv_obj_set_x(ui_PanelHome, 280);
    lv_obj_set_y(ui_PanelHome, 0);
    lv_obj_set_align(ui_PanelHome, LV_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(ui_PanelHome, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_PanelHome, LV_DIR_HOR);
    lv_obj_set_style_radius(ui_PanelHome, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelHome, lv_color_hex(0x4D5B74), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelHome, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelHome, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelHomeTime = lv_label_create(ui_PanelHome);
    lv_obj_set_width(ui_LabelHomeTime, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelHomeTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelHomeTime, 1);
    lv_obj_set_y(ui_LabelHomeTime, -38);
    lv_obj_set_align(ui_LabelHomeTime, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelHomeTime, "18:01");
    lv_obj_set_style_text_color(ui_LabelHomeTime, lv_color_hex(0xFFCC4D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelHomeTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelHomeTime, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelHomeTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHomeTime, &ui_font_FontUbuntuBold96, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelStateBarTime1 = lv_label_create(ui_PanelHome);
    lv_obj_set_width(ui_LabelStateBarTime1, LV_SIZE_CONTENT);   /// 280
    lv_obj_set_height(ui_LabelStateBarTime1, LV_SIZE_CONTENT);    /// 28
    lv_obj_set_x(ui_LabelStateBarTime1, 57);
    lv_obj_set_y(ui_LabelStateBarTime1, 85);
    lv_obj_set_align(ui_LabelStateBarTime1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelStateBarTime1, "Sat, Mar 18");
    lv_obj_set_style_text_color(ui_LabelStateBarTime1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelStateBarTime1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelStateBarTime1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelStateBarTime1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelStateBarTime1, &ui_font_FontUbuntuBold18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgStateBar = lv_img_create(ui_ScreenLauncher);
    lv_img_set_src(ui_ImgStateBar, &ui_img_img_statebar_png);
    lv_obj_set_width(ui_ImgStateBar, LV_SIZE_CONTENT);   /// 280
    lv_obj_set_height(ui_ImgStateBar, LV_SIZE_CONTENT);    /// 30
    lv_obj_set_x(ui_ImgStateBar, 0);
    lv_obj_set_y(ui_ImgStateBar, -135);
    lv_obj_set_align(ui_ImgStateBar, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgStateBar, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImgStateBar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_ImgStateBar, 255);

    ui_LabelStateBarTime = lv_label_create(ui_ImgStateBar);
    lv_obj_set_width(ui_LabelStateBarTime, LV_SIZE_CONTENT);   /// 280
    lv_obj_set_height(ui_LabelStateBarTime, LV_SIZE_CONTENT);    /// 28
    lv_obj_set_align(ui_LabelStateBarTime, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelStateBarTime, "21:15");
    lv_obj_set_style_text_color(ui_LabelStateBarTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelStateBarTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelStateBarTime, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelStateBarTime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelStateBarTime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelStateBarTime, &ui_font_FontUbuntuBold16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgBattery = lv_img_create(ui_ImgStateBar);
    lv_img_set_src(ui_ImgBattery, &ui_img_img_battery_png);
    lv_obj_set_width(ui_ImgBattery, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_ImgBattery, LV_SIZE_CONTENT);    /// 27
    lv_obj_set_x(ui_ImgBattery, 100);
    lv_obj_set_y(ui_ImgBattery, -1);
    lv_obj_set_align(ui_ImgBattery, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgBattery, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImgBattery, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_BatteryBar = lv_bar_create(ui_ImgBattery);
    lv_bar_set_value(ui_BatteryBar, 80, LV_ANIM_OFF);
    lv_obj_set_width(ui_BatteryBar, 17);
    lv_obj_set_height(ui_BatteryBar, 9);
    lv_obj_set_x(ui_BatteryBar, -2);
    lv_obj_set_y(ui_BatteryBar, 0);
    lv_obj_set_align(ui_BatteryBar, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_BatteryBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BatteryBar, lv_color_hex(0x4D5B74), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BatteryBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_BatteryBar, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BatteryBar, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BatteryBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_ScreenLauncher_screen_init();
    // lv_disp_load_scr(ui_ScreenLauncher);
}
