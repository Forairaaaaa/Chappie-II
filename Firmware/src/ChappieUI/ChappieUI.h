/**
 * @file ChappieUI.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "ChappieUIConfigs.h"
#include "Launcher/App_Launcher.h"
#include "../ChappieBsp/Chappie.h"


class CHAPPIEUI {
    private:
        bool _inited;
        CHAPPIE* _device;
        App::App_Launcher* _launcher;

    public:
        CHAPPIEUI() : _inited(false) {}
        ~CHAPPIEUI() {}

        /**
         * @brief UI begin
         * 
         */
        int begin();
        
        /**
         * @brief Put it into loop
         * 
         */
        void update();
        
        /* Get device bsp pointor */
        inline CHAPPIE* device() { return _device; }
};


