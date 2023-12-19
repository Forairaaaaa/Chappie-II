/**
 * @file Emma.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Emma.h"
#include "../EmmaConfig.h"


/**
 * @brief Add your own init steps
 * 
 */
void EMMA::init()
{
    // delay(2000);
    printBspInfos();
    printf("%s", Cowsay("Meow~").c_str());


    #if EMMA_MODULE_DISPLAY
    Lcd.init();
    /* Print Logo */
    Lcd.printf("%s\n", Logo.c_str());
    delay(100);
    Lcd.printf(" EmmaBSP %s ;)\n Author: Forairaaaaa\n", EMMA_BSP_VERISON);
    delay(100);
    Lcd.printf(" Project: %s\n", EMMA_PROJECT_NAME);
    delay(100);
    Lcd.printf("%s", Cowsay("Meow~").c_str());
    delay(100);
    #endif
}


void EMMA::printBspInfos()
{
    /* Print Logo */
    printf("%s\n", Logo.c_str());
    printf(" EmmaBSP %s ;)\n Author: Forairaaaaa\n", EMMA_BSP_VERISON);
    printf(" Project: %s\n", EMMA_PROJECT_NAME);

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }
    printf(" %luMB %s flash\n", flash_size / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf(" Minimum free heap size: %ld bytes\n\n", esp_get_minimum_free_heap_size());
}


std::string EMMA::Cowsay(std::string whatCowSay, int ANSIcolor)
{
    std::string ret;

    /* Corlor start */
    if (ANSIcolor != 0)
        ret = "\033[0;" + std::to_string(ANSIcolor) + "m";
    
    /* Print dialog */
    ret.append(" ");
    ret.append(whatCowSay.length() + 2, '_');
    ret.append("\n< ");
    ret.append(whatCowSay);
    ret.append(" >\n ");
    ret.append(whatCowSay.length() + 2, '-');
    ret.append(Cow);

    /* Color end */
    if (ANSIcolor != 0)
        ret.append("\033[0m\n");
    else
        ret.append("\n");
    
    return ret;
}
