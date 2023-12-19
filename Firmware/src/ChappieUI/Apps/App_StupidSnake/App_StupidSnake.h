/**
 * @file App_StupidSnake.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_StupidSnake_appName();
    void* App_StupidSnake_appIcon();
    void App_StupidSnake_onCreate();
    void App_StupidSnake_onLoop();
    void App_StupidSnake_onDestroy();
    void App_StupidSnake_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(StupidSnake);
}

#endif
