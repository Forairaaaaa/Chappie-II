/**
 * @file EmmaConfig.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#if 1

/* Common configs */
#define EMMA_BSP_VERISON                "v3.2"
#define EMMA_PROJECT_NAME               "Chappie-II"


/* Enable module Button */
#define EMMA_MODULE_BUTTON              1
#if EMMA_MODULE_BUTTON
    /* Set pin -1 to disable */
    #define EMMA_BTN_A_PIN              9
    #define EMMA_BTN_B_PIN              0
    #define EMMA_BTN_C_PIN              -1
    /* Add more button in "Button/EmmaButton.hpp" */
#endif


/* Enable module RGB led */
/* Require: https://github.com/FastLED/FastLED.git */
#define EMMA_MODULE_RGB_LED             1
#if EMMA_MODULE_RGB_LED
    #define EMMA_RGBLED_PIN             14
    #define EMMA_RGBLED_NUM             1
#endif


/* Enable module Buzzer */
#define EMMA_MODULE_BUZZER              0
#if EMMA_MODULE_BUZZER
    #define EMMA_BUZZER_PIN             -1
    #define EMMA_BUZZER_MELODY          1
    #define EMMA_BUZZER_MELODY_MSG      1
    #define EMMA_BUZZER_MELODY_MUSIC    1
#endif


/* Enable module PDM Mic */
/* Use speaker class from M5Unified, thanks to @lovyan03 */
/* https://github.com/m5stack/M5Unified/blob/master/src/utility/Mic_Class.hpp */
#define EMMA_MODULE_MIC_PDM             1
#if EMMA_MODULE_MIC_PDM
    #define EMMA_MICPDM_CLK_PIN         6
    #define EMMA_MICPDM_DATA_PIN        7
    #define EMMA_MICPDM_I2S_PORT        I2S_NUM_0
    /* More configs in Mic/EmmaMicPDM.hpp */
#endif


/* Enable module Display */
/* Using https://github.com/lovyan03/LovyanGFX as GFX lib */
#define EMMA_MODULE_DISPLAY             1
#if EMMA_MODULE_DISPLAY
    /* Enable auto detect if supported */
    /* If not, setup your own config in Display/EmmaDisplay.hpp */
    #define EMMA_LGFX_AUTODETECT        0
    #if EMMA_LGFX_AUTODETECT
        #define LGFX_AUTODETECT
    #endif
#endif


/* Enable module Vibrator */
/* Simple viration motor control with ledc pwm */
#define EMMA_MODULE_VIBRATOR            1
#if EMMA_MODULE_VIBRATOR
    #define EMMA_VIBRATOR_PIN           46
#endif


/* Enable module Speaker */
/* Use speaker class from M5Unified, thanks to @lovyan03 */
/* https://github.com/m5stack/M5Unified/blob/master/src/utility/Speaker_Class.hpp */
/* Only wraped I2S mode so far */
#define EMMA_MODULE_SPEAKER             1
#if EMMA_MODULE_SPEAKER
    #define EMMA_SPEAKER_DATA_PIN       17
    #define EMMA_SPEAKER_BCLK_PIN       16
    #define EMMA_SPEAKER_LRCLK_PIN      15
    #define EMMA_SPEAKER_I2S_PORT       I2S_NUM_1
    /* Pin to shut down the speaker */
    #define EMMA_SPEAKER_ENABLE_PIN     3
    /* More configs in Speaker/EmmaSpeaker.hpp */
#endif

#endif
