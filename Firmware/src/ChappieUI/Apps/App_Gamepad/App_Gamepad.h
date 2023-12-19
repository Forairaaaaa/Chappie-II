#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_Gamepad_appName();
    void* App_Gamepad_appIcon();
    void App_Gamepad_onCreate();
    void App_Gamepad_onLoop();
    void App_Gamepad_onDestroy();
    void App_Gamepad_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(Gamepad);
}

#endif
