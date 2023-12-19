#if 1
#include "App_WifiTV.h"
#include "../../../ChappieBsp/Chappie.h"
#include <WiFi.h>
#include "ScreenShotReceiver/TCPReceiver.h"


static std::string app_name = "WifiTV";
static CHAPPIE* device;


LV_IMG_DECLARE(ui_img_icon_wifitv_png);


static TCPReceiver* _recv;


static void _wifi_tv_init()
{
    device->Lcd.fillScreen(TFT_BLACK);
    device->Lcd.setCursor(0, 30);
    device->Lcd.setTextSize(1.5);
    device->Lcd.setTextColor(TFT_WHITE, TFT_BLACK);

    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();

    device->Lcd.printf("Waiting for SmartConfig...\n");
    while (!WiFi.smartConfigDone()) { delay(500); }

    device->Lcd.printf("SmartConfig received, connecting WiFi...\n");
    while (WiFi.status() != WL_CONNECTED) { delay(500); }

    device->Lcd.printf("Connected. IP: %s\n", WiFi.localIP().toString().c_str());

    _recv = new TCPReceiver;
    _recv->setup(&device->Lcd);
}


static void _wifi_tv_update()
{
    _recv->loop();
}


static void _wifi_tv_deinit()
{
    delete _recv;
    WiFi.disconnect(true);
}


namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_WifiTV_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_WifiTV_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_wifitv_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_WifiTV_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_WifiTV_appName().c_str());

        _wifi_tv_init();
        while (1) {
            _wifi_tv_update();
            if (device->Button.B.pressed()) 
                    break;
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
    void App_WifiTV_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_WifiTV_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_WifiTV_appName().c_str());
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_WifiTV_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
