/**
 * @file ChappieENV.hpp
 * @author Forairaaaaa
 * @brief Thanks to https://github.com/adafruit/Adafruit_BMP280_Library
 * @version 0.1
 * @date 2023-03-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../Utility/Adafruit_BMP280/Adafruit_BMP280.h"

class ChappieENV : public Adafruit_BMP280 {
    private:
        float _offset;

    public:
        using Adafruit_BMP280::Adafruit_BMP280;

        inline void init(float pressureOffset = 0)
        {
            setPressureOffset(pressureOffset);

            begin();

            /* Default settings from datasheet. */
            // setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
            //             Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
            //             Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
            //             Adafruit_BMP280::FILTER_X16,      /* Filtering. */
            //             Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
        }

        /**
         * @brief Set pressure offset for value adjust
         * 
         * @param offset 
         */
        inline void setPressureOffset(float offset) { _offset = offset; }

        /* Rewrite functions with offset */
        /*!
        * Reads the barometric pressure from the device.
        * @return Barometric pressure in Pa.
        */
        inline float readPressure(void)
        {
            return Adafruit_BMP280::readPressure() + _offset;
        }
        
        /*!
        * @brief Calculates the approximate altitude using barometric pressure and the
        * supplied sea level hPa as a reference.
        * @param seaLevelhPa
        *        The current hPa at sea level.
        * @return The approximate altitude above sea level in meters.
        */
        inline float readAltitude(float seaLevelhPa = 1013.25)
        {
            return Adafruit_BMP280::readAltitude(seaLevelhPa + (_offset / 100));
        }

};

