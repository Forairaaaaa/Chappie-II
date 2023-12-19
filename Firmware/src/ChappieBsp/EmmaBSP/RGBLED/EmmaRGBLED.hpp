/**
 * @file EmmaRGBLED.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../EmmaConfig.h"
#if EMMA_MODULE_RGB_LED
#include <FastLED.h>
#include "esp32-hal-log.h"


#define TAG_RGBLED "RGBLED"


class EmmaRGBLED
{
    private:
    public:
        CRGB* leds;

        EmmaRGBLED()
        {
            ESP_LOGI(TAG_RGBLED, "init...");

            leds = (CRGB*)malloc(sizeof(CRGB) * EMMA_RGBLED_NUM);
            if (leds == NULL) {
                ESP_LOGE(TAG_RGBLED, "malloc failed!");
                while (1);
            }

            // FastLED.addLeds<SK6812, EMMA_RGBLED_PIN, GRB>(leds, EMMA_RGBLED_NUM);
            FastLED.addLeds<WS2812B, EMMA_RGBLED_PIN, GRB>(leds, EMMA_RGBLED_NUM);
            ESP_LOGI(TAG_RGBLED, "success!");
        }

        ~EmmaRGBLED() { free(leds); }
};

#endif
