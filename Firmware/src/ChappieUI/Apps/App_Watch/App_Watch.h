#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_Watch_appName();
    void* App_Watch_appIcon();
    void App_Watch_onCreate();
    void App_Watch_onLoop();
    void App_Watch_onDestroy();
    void App_Watch_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(Watch);
}

#endif
