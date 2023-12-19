/**
 * @file AppTypedef.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <string>

namespace App {

    /* Structure to contain app function pointers  */
    struct AppRegister_t {
        
        /* Return app name */
        std::string (*appName)();

        /* Reaturn app Icon in lv_img_t */
        void* (*appIcon)();

        /* App oncreate */
        void (*onCreate)();

        /* App onLoop */
        void (*onLoop)();

        /* App onDestroy */
        void (*onDestroy)();

        /* Pass a BSP pointer */
        void (*getBsp)(void* bsp);
    };

}


/* Use this define to declare your App */
#define App_Declare(app_name) \
    static AppRegister_t App_ ## app_name = { \
        appName:App_ ## app_name ## _appName, \
        appIcon:App_ ## app_name ## _appIcon, \
        onCreate:App_ ## app_name ## _onCreate, \
        onLoop:App_ ## app_name ## _onLoop, \
        onDestroy:App_ ## app_name ## _onDestroy, \
        getBsp:App_ ## app_name ## _getBsp, \
    };


/* Use this to log your App into register */
#define App_Login(app_name) \
    App_ ## app_name


