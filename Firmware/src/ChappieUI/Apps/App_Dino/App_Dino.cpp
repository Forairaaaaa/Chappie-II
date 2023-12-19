#if 1
#include "App_Dino.h"
#include "../../../ChappieBsp/Chappie.h"
#include "Dino/include/Game.h"

static std::string app_name = "Dino";
static CHAPPIE* device;

LV_IMG_DECLARE(ui_img_icon_dinogame_png);


Game Dino;


namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_Dino_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_Dino_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_dinogame_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_Dino_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_Dino_appName().c_str());

        device->Lcd.clear();
        Dino.begin(device);
        while (1)
        {
            Dino.loop();
            if (device->Button.B.pressed()) {
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
    void App_Dino_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_Dino_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_Dino_appName().c_str());
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_Dino_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
