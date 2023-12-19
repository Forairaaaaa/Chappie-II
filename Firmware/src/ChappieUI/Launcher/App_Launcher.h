/**
 * @file App_Launcher.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../Apps/AppRegister.h"
#include "../../ChappieBsp/Chappie.h"


namespace App {

    class App_Launcher {
        private:
            /* BSP pointer to access hardware functions */
            CHAPPIE* _device;

            void updateDeviceStatus();
            void updateAppManage();

            /* UI events */
            lv_timer_t* _time_update_timer;
            static void time_update(lv_timer_t * timer);
            static void scroll_event_cb(lv_event_t * e);
            static void button_event_cb(lv_event_t * e);
            static void panel_control_pad_event_cb(lv_event_t * e);
            static void sleep_mode();

        public:
            inline App_Launcher(CHAPPIE* device) {  _device = device; }

            void onCreate();
            void onLoop();
            void onDestroy();

    };

}
