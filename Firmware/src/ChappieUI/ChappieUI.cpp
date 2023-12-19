/**
 * @file ChappieUI.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ChappieUI.h"


int CHAPPIEUI::begin()
{
    if (_inited) {
        UI_LOG("[ChappieUI] already inited\n");
        return -1;
    }
    
    /* Create bsp */
    _device = new CHAPPIE;
    if (_device == NULL) {
        UI_LOG("[ChappieUI] bsp create failed\n");
        return -1;
    }
    
    /* Create launcher */
    _launcher = new App::App_Launcher(_device);
    if (_device == NULL) {
        UI_LOG("[ChappieUI] Launcher create failed\n");
        return -1;
    }

    _inited = true;
    
    /* Init device */
    _device->init();

    /* Init lvgl */
    _device->lvgl.init(&_device->Lcd, &_device->Tp);

    /* Start launcher */
    _launcher->onCreate();

    return 0;
}


void CHAPPIEUI::update()
{
    _launcher->onLoop();
}

