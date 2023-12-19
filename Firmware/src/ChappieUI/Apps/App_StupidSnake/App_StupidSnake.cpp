/**
 * @file App_StupidSnake.cpp
 * @author Forairaaaaa
 * @brief https://github.com/Forairaaaaa/Stupinake/blob/main/Arduino/AtomS3/PIO/main.cpp
 * @version 0.1
 * @date 2023-03-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#if 1
#include "App_StupidSnake.h"
#include "../../../ChappieBsp/Chappie.h"
#include "StupidSnake.h"


static std::string app_name = "StupidSnake";
static CHAPPIE* device;

LV_IMG_DECLARE(ui_img_icon_snakegame_png);


namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_StupidSnake_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_StupidSnake_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_snakegame_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_StupidSnake_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_StupidSnake_appName().c_str());

        Game_Setup(device);
        while (1) {
            Game_Loop();
            if (device->Button.B.pressed()) {
                Game_End();
                break;
            }
        }
        lv_obj_t * label = lv_label_create(lv_scr_act());
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(label, "Press B again to quit");
    }


    /**
     * @brief Called repeatedly, end this function ASAP! or the App management will be affected
     * If the thing you want to do takes time, try create a taak or lvgl timer to handle them.
     * Try use millis() instead of delay() here
     * 
     */
    void App_StupidSnake_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_StupidSnake_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_StupidSnake_appName().c_str());
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_StupidSnake_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
