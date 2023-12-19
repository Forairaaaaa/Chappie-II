/**
 * @file Chappie.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Chappie.h"



void CHAPPIE::init()
{
    /* Init power contrl */
    Pow.init();

    /* Init RGB led */
    // FastLED.showColor(CRGB::Orange, 5);
    
    /* Init lcd */
    Lcd.init();
    Lcd.setFont(&fonts::efontCN_12);

    /* Print Logo in a cool way */
    Lcd.setCursor(0, 0);
    for (char c : Logo) {
        Lcd.printf("%c", c);
        delay(1);
    }
    // Lcd.printf("%s", Logo);
    // delay(50);
    Lcd.printf("\n ChappieBSP %s :)\n Author: Forairaaaaa\n", EMMA_BSP_VERISON);
    // delay(50);
    Lcd.printf(" Project: %s\n", EMMA_PROJECT_NAME);
    // delay(50);

    /* Init I2C */
    Wire.begin(5, 4);
    Wire.setClock(400000);

    /* Init touchpad */
    Lcd.printf("%s", Cowsay("Pls touch screen to wakeup Tp").c_str());
    Tp.init(&Wire);
    Lcd.printf("Tp init success!\n");

    /* Init RTC */
    Rtc.begin();

    /* Init IMU */
    // Imu.init();
    
    /* Init SD card */
    Sd.init();

    /* Init BMP280 */
    Env.init();

    /* Fire up */
    Speaker.setVolume(100);
    // Speaker.tone(9000, 300);
    // Vibrator.Buzzzzz(300);
    
    // FastLED.showColor(CRGB::Black);
}
