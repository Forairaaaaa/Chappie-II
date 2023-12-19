// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: Watch

#include "ui.h"
// #include "ui_helpers.h"
#include "../../../Launcher/UI/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void WatchLaughPointerRotate_Animation(lv_obj_t * TargetObject, int delay);
lv_obj_t * ui_ScreenWatchWarma;
lv_obj_t * ui_WatchWarmaBG;
lv_obj_t * ui_WatchWarmaLabel;
lv_obj_t * ui_ScreenWatchThink;
lv_obj_t * ui_WatchThinkBG;
lv_obj_t * ui_WatchThinkLabelHour;
lv_obj_t * ui_WatchThinkLabelMinute;
lv_obj_t * ui_ScreenWatchLaugh;
lv_obj_t * ui_WatchLaughBG;
lv_obj_t * ui_WatchLaughHour;
lv_obj_t * ui_WatchLaughMinute;
lv_obj_t * ui_WatchLaughSecond;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void WatchLaughPointerRotate_Animation_hour(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 300);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 300);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);

}

void WatchLaughPointerRotate_Animation_minute(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 600);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 60);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_angle);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_ScreenWatchWarma_screen_init(void)
{
    ui_ScreenWatchWarma = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenWatchWarma, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenWatchWarma, lv_color_hex(0x515C70), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenWatchWarma, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WatchWarmaBG = lv_img_create(ui_ScreenWatchWarma);
    lv_img_set_src(ui_WatchWarmaBG, &ui_img_warma_png);
    lv_obj_set_width(ui_WatchWarmaBG, LV_SIZE_CONTENT);   /// 280
    lv_obj_set_height(ui_WatchWarmaBG, LV_SIZE_CONTENT);    /// 240
    lv_obj_set_align(ui_WatchWarmaBG, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WatchWarmaBG, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WatchWarmaBG, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WatchWarmaLabel = lv_label_create(ui_ScreenWatchWarma);
    lv_obj_set_width(ui_WatchWarmaLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WatchWarmaLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WatchWarmaLabel, 47);
    lv_obj_set_y(ui_WatchWarmaLabel, -89);
    lv_obj_set_align(ui_WatchWarmaLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WatchWarmaLabel, "18:01");
    lv_obj_set_style_text_color(ui_WatchWarmaLabel, lv_color_hex(0xFFCB4C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WatchWarmaLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WatchWarmaLabel, &ui_font_MontserratBold48, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_ScreenWatchThink_screen_init(void)
{
    ui_ScreenWatchThink = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenWatchThink, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenWatchThink, lv_color_hex(0x6C8A6F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenWatchThink, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WatchThinkBG = lv_img_create(ui_ScreenWatchThink);
    lv_img_set_src(ui_WatchThinkBG, &ui_img_think_png);
    lv_obj_set_width(ui_WatchThinkBG, LV_SIZE_CONTENT);   /// 280
    lv_obj_set_height(ui_WatchThinkBG, LV_SIZE_CONTENT);    /// 240
    lv_obj_set_align(ui_WatchThinkBG, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WatchThinkBG, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WatchThinkBG, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WatchThinkLabelHour = lv_label_create(ui_ScreenWatchThink);
    lv_obj_set_width(ui_WatchThinkLabelHour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WatchThinkLabelHour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WatchThinkLabelHour, -87);
    lv_obj_set_y(ui_WatchThinkLabelHour, -65);
    lv_obj_set_align(ui_WatchThinkLabelHour, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WatchThinkLabelHour, "18");
    lv_obj_set_style_text_color(ui_WatchThinkLabelHour, lv_color_hex(0xFFCB4C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WatchThinkLabelHour, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WatchThinkLabelHour, &ui_font_MontserratBold48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WatchThinkLabelMinute = lv_label_create(ui_ScreenWatchThink);
    lv_obj_set_width(ui_WatchThinkLabelMinute, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WatchThinkLabelMinute, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WatchThinkLabelMinute, -87);
    lv_obj_set_y(ui_WatchThinkLabelMinute, -19);
    lv_obj_set_align(ui_WatchThinkLabelMinute, LV_ALIGN_CENTER);
    lv_label_set_text(ui_WatchThinkLabelMinute, "01");
    lv_obj_set_style_text_color(ui_WatchThinkLabelMinute, lv_color_hex(0xFFCB4C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WatchThinkLabelMinute, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WatchThinkLabelMinute, &ui_font_MontserratBold48, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_ScreenWatchLaugh_screen_init(void)
{
    ui_ScreenWatchLaugh = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenWatchLaugh, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenWatchLaugh, lv_color_hex(0x998CAC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenWatchLaugh, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WatchLaughBG = lv_img_create(ui_ScreenWatchLaugh);
    lv_img_set_src(ui_WatchLaughBG, &ui_img_bg_laugh_png);
    lv_obj_set_width(ui_WatchLaughBG, LV_SIZE_CONTENT);   /// 280
    lv_obj_set_height(ui_WatchLaughBG, LV_SIZE_CONTENT);    /// 240
    lv_obj_set_align(ui_WatchLaughBG, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WatchLaughBG, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WatchLaughBG, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WatchLaughHour = lv_img_create(ui_WatchLaughBG);
    lv_img_set_src(ui_WatchLaughHour, &ui_img_laugh_hour_png);
    lv_obj_set_width(ui_WatchLaughHour, LV_SIZE_CONTENT);   /// 48
    lv_obj_set_height(ui_WatchLaughHour, LV_SIZE_CONTENT);    /// 36
    lv_obj_set_x(ui_WatchLaughHour, 96);
    lv_obj_set_y(ui_WatchLaughHour, 0);
    lv_obj_set_align(ui_WatchLaughHour, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WatchLaughHour, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WatchLaughHour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_WatchLaughHour, -72, 18);

    ui_WatchLaughMinute = lv_img_create(ui_WatchLaughBG);
    lv_img_set_src(ui_WatchLaughMinute, &ui_img_laugh_minute_png);
    lv_obj_set_width(ui_WatchLaughMinute, LV_SIZE_CONTENT);   /// 35
    lv_obj_set_height(ui_WatchLaughMinute, LV_SIZE_CONTENT);    /// 26
    lv_obj_set_x(ui_WatchLaughMinute, 96);
    lv_obj_set_y(ui_WatchLaughMinute, 0);
    lv_obj_set_align(ui_WatchLaughMinute, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WatchLaughMinute, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WatchLaughMinute, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_WatchLaughMinute, -79, 13);

    ui_WatchLaughSecond = lv_img_create(ui_WatchLaughBG);
    lv_img_set_src(ui_WatchLaughSecond, &ui_img_laugh_second_png);
    lv_obj_set_width(ui_WatchLaughSecond, LV_SIZE_CONTENT);   /// 24
    lv_obj_set_height(ui_WatchLaughSecond, LV_SIZE_CONTENT);    /// 18
    lv_obj_set_x(ui_WatchLaughSecond, 96);
    lv_obj_set_y(ui_WatchLaughSecond, 0);
    lv_obj_set_align(ui_WatchLaughSecond, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WatchLaughSecond, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WatchLaughSecond, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_WatchLaughSecond, -84, 9);
    lv_img_set_angle(ui_WatchLaughSecond, 1);

}

void watch_ui_init(void)
{
    // lv_disp_t * dispp = lv_disp_get_default();
    // lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
    //                                            false, LV_FONT_DEFAULT);
    // lv_disp_set_theme(dispp, theme);
    ui_ScreenWatchWarma_screen_init();
    ui_ScreenWatchThink_screen_init();
    ui_ScreenWatchLaugh_screen_init();
    // lv_disp_load_scr(ui_ScreenWatchWarma);
}
