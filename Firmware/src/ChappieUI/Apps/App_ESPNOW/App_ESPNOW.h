#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_ESPNOW_appName();
    void* App_ESPNOW_appIcon();
    void App_ESPNOW_onCreate();
    void App_ESPNOW_onLoop();
    void App_ESPNOW_onDestroy();
    void App_ESPNOW_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(ESPNOW);
}

#endif
