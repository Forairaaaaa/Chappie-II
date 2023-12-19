/**
 * @file ChappieCTP.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "Arduino.h"
#include "Wire.h"

/* Configs */
#define CTP_DEV_ADDR            0x15
#define CTP_INT_PIN             21

#define CTP_HORIZON
// #define CTP_PORTRAIT

#ifdef CTP_HORIZON
    #define CTP_REVERS_XPOS     0
    #define CTP_REVERS_YPOS     1
    #define CTP_REVERS_XY       1
#else
#ifdef CTP_PORTRAIT
    #define CTP_REVERS_XPOS     0
    #define CTP_REVERS_YPOS     1
    #define CTP_REVERS_XY       0
#endif
#endif

/* Use map for calibration, can solve some dead area problem, but lost precision */
#define USING_MAP_TO_CALIBRATE  0


class ChappieCTP {
    private:
        int _x_pos;
        int _y_pos;
        bool _enable;

        /* I2C related */
        TwoWire* _wire;
        uint8_t _dev_addr;

        inline void _I2C_init(TwoWire * wire, uint8_t dev_addr)
        {
            _wire = wire;
            _dev_addr = dev_addr;
        }

        inline bool _I2C_checkDevAvl()
        {
            _wire->beginTransmission(_dev_addr);
            return ( _wire->endTransmission() ? true : false);
        }

        inline void _I2C_write1Byte(uint8_t addr, uint8_t data)
        {
            _wire->beginTransmission(_dev_addr);
            _wire->write(addr);
            _wire->write(data);
            _wire->endTransmission();
        }

        inline void _I2C_readBuff(uint8_t addr, int size, uint8_t buff[])
        {
            _wire->beginTransmission(_dev_addr);
            _wire->write(addr);
            _wire->endTransmission();
            _wire->requestFrom(_dev_addr, (size_t)size);
            for (int i = 0; i < size; i++) {
                buff[i] = _wire->read();
            }
        }

        inline uint8_t _I2C_read8Bit(uint8_t addr)
        {
            _wire->beginTransmission(_dev_addr);
            _wire->write(addr);
            _wire->endTransmission();
            _wire->requestFrom(_dev_addr, (size_t)1);
            return _wire->read();
        }

        inline uint16_t _I2C_read12Bit(uint8_t addr)
        {
            uint8_t buff[2];
            _I2C_readBuff(addr, 2, buff);
            return (buff[0] << 4) + buff[1];
        }

        /* CTP init */
        inline void _init()
        {
            /* Reset coordinate */
            _reset_coor();
            _enable = true;

            /* Shut down auto sleep */
            // _I2C_write1Byte(0xFE, 0xFF);
            _I2C_write1Byte(0xFE, 0x07);
            printf("[CTP] auto sleep shut down\n");

            /* Setup INT PIN */
            // pinMode(CTP_INT_PIN, INPUT);
            // printf("[CTP] set int-pin input\n");
            // _I2C_write1Byte(0xFA, 0B01000001);
            // _I2C_write1Byte(0xED, 0xC8);
        }

        inline void _reset_coor()
        {
            _x_pos = -1;
            _y_pos = -1;
        }

        inline void _update_coor()
        {
            // coor_x = _I2C_read12Bit(0x03);
            // coor_y = _I2C_read12Bit(0x05);

            uint8_t buff[4];
            _I2C_readBuff(0x03, 4, buff);
            // _x_pos = ((buff[0]&0x0F)<<8)|buff[1];
            // _y_pos = ((buff[2]&0x0F)<<8)|buff[3];

            #if CTP_REVERS_XY
                _y_pos = ((buff[0]&0x0F)<<8)|buff[1];
                _x_pos = ((buff[2]&0x0F)<<8)|buff[3];
                #if CTP_REVERS_XPOS
                    _x_pos = -(_x_pos ) + 280;
                #endif
                #if CTP_REVERS_YPOS
                    _y_pos = -(_y_pos ) + 240;
                #endif
            #else
                _x_pos = ((buff[0]&0x0F)<<8)|buff[1];
                _y_pos = ((buff[2]&0x0F)<<8)|buff[3];
            #endif
        }


    public:
        /**
         * @brief Init toupac with wire pointer
         * 
         * @param wire 
         */
        inline void init(TwoWire* wire)
        {
            _I2C_init(wire, CTP_DEV_ADDR);
            /* Hold until init done */
            while (_I2C_checkDevAvl()) {
                printf("[CTP] please touch screen to activate it\n");
                delay(500);
            }
            printf("[CTP] init successful\n");
            _init();
        }

        inline bool isTouched()
        {
            // return !digitalRead(CTP_INT_PIN);

            if (!_enable)
                return false;

            return _I2C_read8Bit(0x02) ? true : false;
        }

        inline void getPos(int& x_pos, int& y_pos)
        {
            _update_coor();

            x_pos = _x_pos;
            y_pos = _y_pos;

            #if USING_MAP_TO_CALIBRATE

                /* Remap the possition value */
                x_pos = map(_x_pos, 6, 258, 0, 280);
                y_pos = map(_y_pos, 15, 230, 0, 240);

                #ifdef CTP_HORIZON
                    if (x_pos > 280)
                        x_pos = 280;
                    if (x_pos < 0)
                        x_pos = 0;
                    if (y_pos > 240)
                        y_pos = 240;
                    if (y_pos < 0)
                        y_pos = 0;
                #else
                #ifdef CTP_PORTRAIT
                    if (x_pos > 240)
                        x_pos = 240;
                    if (x_pos < 0)
                        x_pos = 0;
                    if (y_pos > 280)
                        y_pos = 280;
                    if (y_pos < 0)
                        y_pos = 0;
                #endif
                #endif           

            #endif
        }

        inline void printCoordinate()
        {
            if (isTouched())
                _update_coor();
            else
                _reset_coor();

            // _update_coor();
            printf("X:%03d Y:%03d\n", _x_pos, _y_pos);
        }

        inline void enable() { _enable = true; }
        inline void disable() { _enable = false; }
};

