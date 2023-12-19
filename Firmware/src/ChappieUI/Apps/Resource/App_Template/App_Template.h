#if 0
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_Template_appName();
    void* App_Template_appIcon();
    void App_Template_onCreate();
    void App_Template_onLoop();
    void App_Template_onDestroy();
    void App_Template_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(Template);
}

#endif
