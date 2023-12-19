#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_Settings_appName();
    void* App_Settings_appIcon();
    void App_Settings_onCreate();
    void App_Settings_onLoop();
    void App_Settings_onDestroy();
    void App_Settings_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(Settings);
}

#endif
