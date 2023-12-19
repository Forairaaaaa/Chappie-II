/**
 * @file App_Launcher.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "App_Launcher.h"
#include "../ChappieUIConfigs.h"
#include "UI/ui.h"


/* Structure to hold App num and status */
struct AppManager_t {
    uint16_t totalNum = 0;
    int16_t selected = -1;
    bool isRunning = false;
    bool onCreate = false;
    bool onDestroy = false;
};
static AppManager_t _app;

/* Structure to hold device status */
struct DeviceStatus_t {
    bool updated = false;
    bool autoScreenOff = false;
    uint8_t brightness = 127;
    uint32_t autoScreenOffTime = 20000;
};
static DeviceStatus_t _device_status;


namespace App {

    void App_Launcher::onCreate()
    {
        _device->lvgl.disable();

        /* Reinit lvgl to free resources */
        lv_deinit();
        _device->lvgl.init(&_device->Lcd, &_device->Tp);

        /* Init launcher UI */
        ui_init();
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x4D5B74), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_scr_load_anim(ui_ScreenLauncher, LV_SCR_LOAD_ANIM_FADE_IN, 250, 0, true);

        /* Desktop init */
        lv_obj_set_scroll_snap_x(ui_PanelDesktop, LV_SCROLL_SNAP_CENTER);
        lv_obj_update_snap(ui_PanelDesktop, LV_ANIM_ON);

        /* Read App register */
        _app.totalNum = sizeof(App::Register) / sizeof(App::AppRegister_t);

        /* Place App on the desktop panel */
        for (int i = 0; i < _app.totalNum; i++) {
            /* Apps' Icon (button) */
            lv_obj_t* app_btn = lv_btn_create(ui_PanelDesktop);
            lv_obj_set_size(app_btn, 150, 150);
            lv_obj_align(app_btn, LV_ALIGN_CENTER, i * 180 + 560, 0);
            lv_obj_add_flag(app_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
            lv_obj_set_style_radius(app_btn, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(app_btn, lv_color_hex(0xA6B4CD), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(app_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_spread(app_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            /* Setup event call back */
            lv_obj_add_event_cb(app_btn, button_event_cb, LV_EVENT_CLICKED, NULL);

            /* Get App Icon image */
            const lv_img_dsc_t* app_icon = (const lv_img_dsc_t*)App::Register[i].appIcon();
            if (app_icon == NULL) {
                app_icon = &ui_img_img_icon_defalut_png;
            }
            lv_obj_set_style_bg_img_src(app_btn, app_icon, LV_PART_MAIN | LV_STATE_DEFAULT);

            /* Apps' name */
            lv_obj_t* app_name = lv_label_create(ui_PanelDesktop);
            lv_obj_align(app_name, LV_ALIGN_CENTER, i * 180 + 560, 95);
            lv_label_set_text(app_name, App::Register[i].appName().c_str());
            lv_obj_set_style_text_color(app_name, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(app_name, &ui_font_FontUbuntuBold18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        /* Add ui event call back */
        lv_obj_add_event_cb(ui_PanelDesktop, scroll_event_cb, LV_EVENT_SCROLL_END, NULL);
        lv_obj_add_event_cb(ui_ArcBrightness, panel_control_pad_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_add_event_cb(ui_ButtonAutoScreenOff, panel_control_pad_event_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(ui_ButtonInfos, panel_control_pad_event_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(ui_ButtonWifi, panel_control_pad_event_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_add_event_cb(ui_ButtonBle, panel_control_pad_event_cb, LV_EVENT_CLICKED, NULL);
        
        
        /* Go to the previous place */
        if (_app.selected != -1) {
            /* Pull down state bar manully */
            lv_obj_set_y(ui_ImgStateBar, -105);
            lv_obj_scroll_to_view(lv_obj_get_child(ui_PanelDesktop, (_app.selected * 2 + 2)), LV_ANIM_OFF);
        }
        else {
            lv_obj_scroll_to_view(lv_obj_get_child(ui_PanelDesktop, 1), LV_ANIM_OFF);
        }

        /* Create a timer to update time */
        _time_update_timer = lv_timer_create(time_update, 1000, (void*)_device);
        time_update(_time_update_timer);

        /* Reset auto screen off time counting */
        lv_disp_trig_activity(NULL);

        /* Update control panel */
        if (_device_status.autoScreenOff) {
            lv_obj_add_state(ui_ButtonAutoScreenOff, (LV_STATE_CHECKED | LV_STATE_FOCUSED));
        }
        
        _device->lvgl.enable();
    }


    void App_Launcher::onLoop()
    {
        _device->lvgl.disable();

        updateDeviceStatus();
        
        updateAppManage();

        _device->lvgl.enable();
    }


    void App_Launcher::onDestroy()
    {
        /* Delete timer */
        lv_timer_del(_time_update_timer);
        
        /* Delete Launcher screen and reaplace with an empty one */
        lv_disp_load_scr(lv_obj_create(NULL));
        lv_obj_del(ui_ScreenLauncher);
    }


    void App_Launcher::updateDeviceStatus()
    {
        /* If button home is pressed */
        if (_device->Button.B.pressed()) {
            if (_app.isRunning) {
                _app.onDestroy = true;
            }

            /* If not at home, go home */
            else {
                lv_obj_scroll_to_view(lv_obj_get_child(ui_PanelDesktop, 1), LV_ANIM_ON);
            }

            /* Reset auto screen off time counting */
            lv_disp_trig_activity(NULL);
        }

        /* If button power is pressed */
        if (_device->Button.A.pressed()) {
            esp_restart();
        }

        /* Device status manage */
        if (_device_status.updated) {
            _device_status.updated = false;
            /* Update brightness */
            _device->Lcd.setBrightness(_device_status.brightness);
        }

        /* If hit auto screen off time  */
        if (_device_status.autoScreenOff && (lv_disp_get_inactive_time(NULL) > _device_status.autoScreenOffTime)) {
            _device->Lcd.setBrightness(0);
            sleep_mode();
            _device->Button.B.begin();
            _device->Lcd.setBrightness(_device_status.brightness);

            /* Reset auto screen off time counting */
            lv_disp_trig_activity(NULL);
        }
    }


    void App_Launcher::updateAppManage()
    {
        /* App state manage, kind of like a FSM */
        if (_app.onCreate) {
            _app.onCreate = false;
            _app.isRunning = true;

            /* Destroy launcher */
            onDestroy();
            /* Open App */
            App::Register[_app.selected].getBsp(_device);
            App::Register[_app.selected].onCreate();
        }
        if (_app.isRunning) {
            App::Register[_app.selected].onLoop();
        }
        if (_app.onDestroy) {
            _app.onDestroy = false;
            _app.isRunning = false;

            /* Quit App */
            App::Register[_app.selected].onDestroy();
            /* Create launcher */
            onCreate();
        }
    }

    
    /* ------------------------------------------------ UI events ------------------------------------------------ */


    void App_Launcher::time_update(lv_timer_t * timer)
    {
        CHAPPIE* device = (CHAPPIE*)timer->user_data;
        static char label_buffer[10];
        static char date_buffer[30];
        static char week1[6];
        static char month[6];
        /* Update clock */
        static I2C_BM8563_TimeTypeDef rtc_time;
        static I2C_BM8563_DateTypeDef rtc_date;
        device->Rtc.getTime(&rtc_time);
        device->Rtc.getDate(&rtc_date);
        snprintf(label_buffer, 10, "%d:%02d", rtc_time.hours, rtc_time.minutes);

        uint8_t week_data = rtc_date.weekDay;
        uint8_t month_data = rtc_date.month;
        
        if(week_data == 1){snprintf(week1,4, "Mon");}
        else if(week_data == 2){snprintf(week1,4, "Tue");}
        else if(week_data == 3){snprintf(week1,4, "Wed");}
        else if(week_data == 4){snprintf(week1,4, "Thu");}
        else if(week_data == 5){snprintf(week1,4, "Fri");}
        else if(week_data == 6){snprintf(week1,4, "Sat");}
        else if(week_data == 0){snprintf(week1,4, "Sun");}
        
        if(month_data == 1){snprintf(month,4, "Jan");}
        else if(month_data == 2){snprintf(month,4, "Feb");}
        else if(month_data == 3){snprintf(month,4, "Mar");}
        else if(month_data == 4){snprintf(month,4, "Apr");}
        else if(month_data == 5){snprintf(month,4, "May");}
        else if(month_data == 6){snprintf(month,4, "Jun");}
        else if(month_data == 7){snprintf(month,4, "Jul");}
        else if(month_data == 8){snprintf(month,4, "Aug");}
        else if(month_data == 9){snprintf(month,4, "Sep");}
        else if(month_data == 10){snprintf(month,4, "Oct");}
        else if(month_data == 11){snprintf(month,4, "Nov");}
        else if(month_data == 12){snprintf(month,4, "Dec");}
        snprintf(date_buffer,20,"%s,%s %d",week1,month,rtc_date.date);

        lv_label_set_text(ui_LabelHomeTime, label_buffer);
        lv_label_set_text(ui_LabelStateBarTime, label_buffer);

        lv_label_set_text(ui_LabelStateBarTime1, date_buffer);

    }


    void App_Launcher::scroll_event_cb(lv_event_t * e)
    {
        static int16_t last_x = 280;
        lv_obj_t * obj = lv_event_get_target(e);

        /* If enter pannel home */
        if ((lv_obj_get_scroll_x(obj) == 280) && (last_x != 280)) {
            StateBarPullUp_Animation(ui_ImgStateBar, 0);
        }
        /* If leave pannel home */
        else if ((lv_obj_get_scroll_x(obj) != 280) && (last_x == 280)) {
            StateBarDropDown_Animation(ui_ImgStateBar, 0);
        }

        last_x = lv_obj_get_scroll_x(obj);
    }


    void App_Launcher::button_event_cb(lv_event_t * e)
    {
        lv_obj_t * obj = lv_event_get_target(e);
        lv_event_code_t code = lv_event_get_code(e);

        /* Into that App */
        if (code == LV_EVENT_CLICKED) {
            _app.selected = (lv_obj_get_index(obj) - 2) / 2;
            _app.onCreate = true;
        }
    }


    void App_Launcher::panel_control_pad_event_cb(lv_event_t * e)
    {
        lv_obj_t * obj = lv_event_get_target(e);
        lv_event_code_t code = lv_event_get_code(e);

        /* If setting brightness */
        if (obj == ui_ArcBrightness) {
            _device_status.updated = true;
            _device_status.brightness = lv_arc_get_value(obj);
        }

        /* If clicked infos button */
        else if (obj == ui_ButtonInfos) {
            /* Go look for App setting */
            for (int i = 0; i < _app.totalNum; i++) {
                if (App::Register[i].appName() == "Settings") {
                    _app.selected = i;
                    _app.onCreate = true;
                    break;
                }
            }
        }

        /* If enable auto screen off */
        else if (obj == ui_ButtonAutoScreenOff) {
            // UI_LOG("%d\n", lv_obj_get_state(obj));
            if (lv_obj_get_state(obj) == (LV_STATE_CHECKED | LV_STATE_FOCUSED)) {
                _device_status.autoScreenOff = true;
            }
            else {
                _device_status.autoScreenOff = false;
            }
        }

    }


    void App_Launcher::sleep_mode()
    {
        /* Reset button B and touchpad intterupt pin */
        gpio_reset_pin(GPIO_NUM_0);
        gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT);
        gpio_wakeup_enable(GPIO_NUM_0, GPIO_INTR_LOW_LEVEL);
        gpio_reset_pin(GPIO_NUM_21);
        gpio_set_direction(GPIO_NUM_21, GPIO_MODE_INPUT);
        gpio_wakeup_enable(GPIO_NUM_21, GPIO_INTR_LOW_LEVEL);
        esp_sleep_enable_gpio_wakeup();
        
        /* Hold untill button released */
        while (gpio_get_level(GPIO_NUM_0) == 0) { delay(20); }

        /* Go to sleep */
        esp_light_sleep_start();
    }

}


