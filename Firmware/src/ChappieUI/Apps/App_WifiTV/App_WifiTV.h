#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_WifiTV_appName();
    void* App_WifiTV_appIcon();
    void App_WifiTV_onCreate();
    void App_WifiTV_onLoop();
    void App_WifiTV_onDestroy();
    void App_WifiTV_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(WifiTV);
}

#endif
