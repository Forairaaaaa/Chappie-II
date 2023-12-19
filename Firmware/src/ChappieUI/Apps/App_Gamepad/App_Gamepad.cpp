#if 1
#include "App_Gamepad.h"
#include "../../../ChappieBsp/Chappie.h"


static std::string app_name = "Gamepad";
static CHAPPIE* device;


LV_IMG_DECLARE(ui_img_icon_gamepad_png);



/* ------------------------------ BLE Gamepad ------------------------------*/
/**
 * @file App_Gamepad.cpp
 * @author Forairaaaaa
 * @brief BLE gamepad
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <BleGamepad.h>

static BleGamepad* _bleGamepad;
static LGFX_Sprite* _screen;


static void _gamepad_init()
{
    _bleGamepad = new BleGamepad;
    _screen = new LGFX_Sprite(&device->Lcd);
    _screen->setPsram(true);
    _screen->createSprite(device->Lcd.width(), device->Lcd.height());

    /* Init ble gamepad */
    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setAxesMin(-120);
    bleGamepadConfig.setAxesMax(120);
    _bleGamepad->begin(&bleGamepadConfig);
}


static void _gamepad_loop()
{
    static int x, y;

    if (_bleGamepad->isConnected()) {
        /* Get toupad data */
        if (device->Tp.isTouched()) {
            device->Tp.getPos(x, y); 
        }
        else {
            x = -1;
            y = -1;
        }            

        /* Update screen */
        _screen->fillScreen(0xCFDCAEU);
        if ((x == -1) && (y == -1))
            _screen->fillSmoothCircle(_screen->width() / 2, _screen->height() / 2, 75, 0x9BB090U);
        else 
            _screen->fillSmoothCircle(x, y, 75, 0x9BB090U);
        _screen->pushSprite(0, 0);

        /* Update data */
        if ((x == -1) && (y == -1))
            _bleGamepad->setAxes(0, 0);
        else {
            x = x - _screen->width() / 2;
            y = y - _screen->height() / 2;
            _bleGamepad->setAxes(x, y);
        }
    }
    else {
        _screen->fillScreen(0xCFDCAEU);
        _screen->setCursor(0, 30);
        _screen->setTextSize(2);
        _screen->setTextColor(0x9BB090U, 0xCFDCAEU);
        _screen->printf(" > Waiting\n > BLE connection \n > (=^.^=)");
        _screen->pushSprite(0, 0);
    }

    delay(10);
}


static void _gamepad_deinit()
{
    _screen->deleteSprite();
    /* Seems empty... */
    _bleGamepad->end();
    delete _screen;
    delete _bleGamepad;
}



/* ------------------------------ BLE Gamepad ------------------------------*/



namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_Gamepad_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_Gamepad_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_gamepad_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_Gamepad_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_Gamepad_appName().c_str());

        _gamepad_init();
        while (1) {
            _gamepad_loop();
            if (device->Button.B.pressed())
                break;
        }
        _gamepad_deinit();

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
    void App_Gamepad_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_Gamepad_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_Gamepad_appName().c_str());
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_Gamepad_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
