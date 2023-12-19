#if 1
#pragma once
#include "../AppTypedef.h"
#include "../../ChappieUIConfigs.h"

/**
 * @brief Create an App in name space 
 * 
 */
namespace App {

    std::string App_FFT_appName();
    void* App_FFT_appIcon();
    void App_FFT_onCreate();
    void App_FFT_onLoop();
    void App_FFT_onDestroy();
    void App_FFT_getBsp(void* bsp);

    /**
     * @brief Declace your App like this 
     * 
     */
    App_Declare(FFT);
}

#endif
