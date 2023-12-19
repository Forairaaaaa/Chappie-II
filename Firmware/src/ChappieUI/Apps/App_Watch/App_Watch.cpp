#if 1
#include "App_Watch.h"
#include "../../../ChappieBsp/Chappie.h"
#include "UI/ui.h"


static std::string app_name = "Watch";
static CHAPPIE* device;


static std::array<_lv_obj_t**, 3> _WatchPad_List = {
    &ui_ScreenWatchWarma,
    &ui_ScreenWatchThink,
    &ui_ScreenWatchLaugh,
};
static int _WatchPad_Current = 0;
static lv_timer_t* _timer_watch_time_update;



static void _watch_time_update(lv_timer_t * timer)
{
    static char label_buffer[10];

    /* Update clock */
    static I2C_BM8563_TimeTypeDef rtc_time;
    static int16_t hours, minutes, seconds;
    device->Rtc.getTime(&rtc_time);

    if (_WatchPad_Current == 0) {
        snprintf(label_buffer, 10, "%d:%02d", rtc_time.hours, rtc_time.minutes);
        lv_label_set_text(ui_WatchWarmaLabel, label_buffer);
    }

    else if (_WatchPad_Current == 1) {
        snprintf(label_buffer, 10, "%02d", rtc_time.hours);
        lv_label_set_text(ui_WatchThinkLabelHour, label_buffer);
        snprintf(label_buffer, 10, "%02d", rtc_time.minutes);
        lv_label_set_text(ui_WatchThinkLabelMinute, label_buffer);
    }

    else if (_WatchPad_Current == 2) {
        /* Change 24 to 12 */
        if (rtc_time.hours > 12) {
            rtc_time.hours -= 12;
        }
        
        hours = rtc_time.hours;
        minutes = rtc_time.minutes;
        seconds = rtc_time.seconds;

        /* 900 offset is because I forget to set the pointer to the 0 at the first time */
        hours = hours * 300 - 900;
        minutes = minutes * 60 - 900;
        seconds = seconds * 60 - 900;

        if (hours < 0)
            hours = 3600 + hours;
        if (minutes < 0)
            minutes = 3600 + minutes;
        if (seconds < 0)
            seconds = 3600 + seconds;
        
        /* If time change, Update with animation */
        if (lv_img_get_angle(ui_WatchLaughHour) != hours) {
            lv_img_set_angle(ui_WatchLaughHour, hours - 300);
            WatchLaughPointerRotate_Animation_hour(ui_WatchLaughHour, 0);
        }
        if (lv_img_get_angle(ui_WatchLaughMinute) != minutes) {
            lv_img_set_angle(ui_WatchLaughMinute, minutes - 60);
            WatchLaughPointerRotate_Animation_minute(ui_WatchLaughMinute, 0);
        }
        if (lv_img_get_angle(ui_WatchLaughSecond) != seconds - 60) {
            lv_img_set_angle(ui_WatchLaughSecond, seconds);
            WatchLaughPointerRotate_Animation_minute(ui_WatchLaughSecond, 0);
        }
    }
    
}


/**
 * @brief Enven to change watch pad
 * 
 * @param e 
 */
static void ui_event_Watch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        // printf("->\n");
        if (_WatchPad_Current < (_WatchPad_List.size() - 1)) {
            _WatchPad_Current++;
            lv_scr_load_anim(*_WatchPad_List[_WatchPad_Current], LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
            _watch_time_update(_timer_watch_time_update);
        }
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        // printf("<-\n");
        _WatchPad_Current--;
        if (_WatchPad_Current < 0) {
            _WatchPad_Current = 0;
        }
        else {
            lv_scr_load_anim(*_WatchPad_List[_WatchPad_Current], LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
            _watch_time_update(_timer_watch_time_update);
        }
    }
}


namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_Watch_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_Watch_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_clock_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_Watch_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_Watch_appName().c_str());

        watch_ui_init();
        
        /* Add event callback */
        for (auto i : _WatchPad_List) {
            lv_obj_add_event_cb(*i, ui_event_Watch, LV_EVENT_ALL, NULL);
        }
        _WatchPad_Current = 0;
        lv_scr_load_anim(*_WatchPad_List[_WatchPad_Current], LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, true);

        _timer_watch_time_update = lv_timer_create(_watch_time_update, 1000, NULL);
        _watch_time_update(_timer_watch_time_update);
    }


    /**
     * @brief Called repeatedly, end this function ASAP! or the App management will be affected
     * If the thing you want to do takes time, try create a taak or lvgl timer to handle them.
     * Try use millis() instead of delay() here
     * 
     */
    void App_Watch_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_Watch_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_Watch_appName().c_str());

        lv_timer_del(_timer_watch_time_update);
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_Watch_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
