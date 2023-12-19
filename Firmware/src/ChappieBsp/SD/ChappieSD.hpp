/**
 * @file ChappieSD.hpp
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
#include <FS.h>
#include <SD.h>

#define CHAPPIE_SD_PIN_MISO     42
#define CHAPPIE_SD_PIN_MOSI     41
#define CHAPPIE_SD_PIN_CLK      40
#define CHAPPIE_SD_PIN_CS       48

class ChappieSD {
    private:
        bool _inited;

    public:
        inline ChappieSD() : _inited(false) {}
        inline ~ChappieSD() {}

        /**
         * @brief 
         * 
         * @return true Success
         * @return false Failed
         */
        inline bool init()
        {
            /* Init spi */
            SPIClass* sd_spi = new SPIClass(HSPI);
            sd_spi->begin(CHAPPIE_SD_PIN_CLK, CHAPPIE_SD_PIN_MISO, CHAPPIE_SD_PIN_MOSI, CHAPPIE_SD_PIN_CS);
            bool ret = SD.begin(CHAPPIE_SD_PIN_CS, *sd_spi, 40000000);
            
            if (!ret) {
                printf("[SD] init failed\n");
                return ret;
            }
            printf("[SD] init success, ");

            /* Get SD card info */
            uint8_t cardType = SD.cardType();
            if (cardType == CARD_MMC)
                printf("MMC");
            else if(cardType == CARD_SD)
                printf("SDSC");
            else if(cardType == CARD_SDHC)
                printf("SDHC");
            printf(" %dGB\n", (SD.cardSize() / 1073741824));

            _inited = true;
            return ret;
        }

        inline bool isInited() { return _inited; }

};

