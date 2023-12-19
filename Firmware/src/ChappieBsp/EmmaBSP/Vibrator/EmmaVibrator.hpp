/**
 * @file EmmaVibrator.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../EmmaConfig.h"
#if EMMA_MODULE_VIBRATOR
#include <Arduino.h>
// #include <freertos/task.h>
// #include <freertos/semphr.h>

class EmmaVibrator {
    private:
        uint8_t _ctrl_pin;
        uint8_t _ledc_channel;
        // TaskHandle_t _task_handler;
        // SemaphoreHandle_t _semaphore_mutex;

    public:
        inline EmmaVibrator(uint8_t ctrlPin, uint8_t ledcChannel = 0)
        {
            _ctrl_pin = ctrlPin;
            _ledc_channel = ledcChannel;
            // _task_handler = NULL;
            // _semaphore_mutex = NULL;

            ledcSetup(_ledc_channel, 10000, 8);
            ledcAttachPin(_ctrl_pin, _ledc_channel);
            ledcWrite(_ledc_channel, 0);
        }
        inline ~EmmaVibrator() { ledcDetachPin(_ctrl_pin); }

        inline void start(uint8_t intensity = 255) { ledcWrite(_ledc_channel, intensity); }
        inline void stop() { start(0); }

        /**
         * @brief Buzz for a while (Blocking)
         * 
         * @param ms 
         * @param intensity 
         */
        inline void Buzzzzz(uint32_t ms, uint8_t intensity = 255) { start(intensity); delay(ms); stop(); }

};


#endif
