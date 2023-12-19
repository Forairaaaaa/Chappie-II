/**
 * @file EmmaMicPDM.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../EmmaConfig.h"
#if EMMA_MODULE_MIC_PDM
#include "Mic/Mic_Class.hpp"


class EmmaMicPDM : public m5::Mic_Class {
    private:
    public:
        EmmaMicPDM()
        {
            auto cfg = config();
            cfg.pin_data_in = EMMA_MICPDM_DATA_PIN;
            cfg.pin_ws = EMMA_MICPDM_CLK_PIN;
            cfg.i2s_port = EMMA_MICPDM_I2S_PORT;
            cfg.magnification = 1;
            cfg.task_priority = 15;
            cfg.sample_rate = 48000;
            config(cfg);
            begin();
        }
        ~EmmaMicPDM() { end(); }
};

#endif
