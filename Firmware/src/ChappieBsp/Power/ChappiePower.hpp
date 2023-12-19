/**
 * @file ChappiePower.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <Arduino.h>

#define CHAPPIE_PWR_CTRL    GPIO_NUM_9
#define CHAPPIE_BATM_ADC    GPIO_NUM_8
#define CHAPPIE_BATM_EN     GPIO_NUM_18

class ChappiePower {
    private:
        inline void _enableBatMeasure() { digitalWrite(CHAPPIE_BATM_EN, 0); }
        inline void _disableBatMeasure() { digitalWrite(CHAPPIE_BATM_EN, 1); }

        

    public:
        ChappiePower() {}
        ~ChappiePower() {}

        inline void init()
        {
            gpio_reset_pin(CHAPPIE_BATM_ADC);
            gpio_reset_pin(CHAPPIE_BATM_EN);

            gpio_set_direction(CHAPPIE_BATM_EN, GPIO_MODE_OUTPUT_OD);

            analogReadResolution(12);
        }

        inline void powerOff()
        {
            gpio_reset_pin(CHAPPIE_PWR_CTRL);
            gpio_set_direction(CHAPPIE_PWR_CTRL, GPIO_MODE_OUTPUT_OD);
            /* Double click */
            gpio_set_level(CHAPPIE_PWR_CTRL, 0);
            delay(100);
            gpio_set_level(CHAPPIE_PWR_CTRL, 1);
            delay(100);
            gpio_set_level(CHAPPIE_PWR_CTRL, 0);
            delay(100);
            gpio_set_level(CHAPPIE_PWR_CTRL, 1);
            delay(1000);
        }

        inline float readBatVoltage()
        {
            /* Calculate the real bat voltage */
            return ((float)readBatMilliVoltRaw() * 3 / 2000);
        }

        inline uint32_t readBatMilliVoltRaw()
        {  
            gpio_set_direction(CHAPPIE_BATM_EN, GPIO_MODE_OUTPUT_OD);
            gpio_set_level(CHAPPIE_BATM_EN, 0);
            delay(10);
            uint32_t ret = analogReadMilliVolts(CHAPPIE_BATM_ADC);
            gpio_set_level(CHAPPIE_BATM_EN, 1);
            gpio_reset_pin(CHAPPIE_BATM_EN);
            gpio_reset_pin(CHAPPIE_BATM_ADC);
            return ret;
        }

        inline uint8_t readBatPercentage()
        {
            /* Asume 0~100% to be 3.2~4.2V */
            uint8_t ret = map((readBatMilliVoltRaw() * 3 / 2), 3200, 4100, 0, 100);
            return ret;
        }

};

