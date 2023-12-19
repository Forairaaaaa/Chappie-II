#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_Dino_appName();
    void* App_Dino_appIcon();
    void App_Dino_onCreate();
    void App_Dino_onLoop();
    void App_Dino_onDestroy();
    void App_Dino_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(Dino);
}

#endif
