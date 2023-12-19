/**
 * @file ChappieIMU.hpp
 * @author Forairaaaaa
 * @brief Reference: https://github.com/ElectronicCats/mpu6050/blob/master/examples/MPU6050_DMP6/MPU6050_DMP6.ino
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "../Utility/MPU6050/MPU6050_6Axis_MotionApps20.h"
#include "../Utility/MPU6050/MPU6050.h"


class ChappieIMU : public MPU6050 {
    private:
        uint8_t _fifoBuffer[64];
        Quaternion _q;
        VectorFloat _gravity;
        float _ypr[3]; 

    public:
        ChappieIMU() {}
        ~ChappieIMU() {}

        inline void init()
        {
            // initialize device
            initialize();
            printf(testConnection() ? "[IMU] connection successful\n" : "[IMU] connection failed\n");

            // load and configure the DMP
            uint8_t devStatus = dmpInitialize();

            // supply your own gyro offsets here, scaled for min sensitivity
            // setXGyroOffset(220);
            // setYGyroOffset(76);
            // setZGyroOffset(-85);
            // setZAccelOffset(1788);

            // make sure it worked (returns 0 if so)
            if (devStatus == 0) {
                // Calibration Time: generate offsets and calibrate our MPU6050
                CalibrateAccel(6);
                CalibrateGyro(6);
                PrintActiveOffsets();
                // turn on the DMP, now that it's ready
                setDMPEnabled(true);
            } else {
                printf("[IMU] DMP init failed\n");
            }
        }

        /**
         * @brief Get the Euler angles in degrees
         * 
         * @param yaw 
         * @param pitch 
         * @param roll 
         * @return uint8_t 0) when no valid data is available
         */
        inline uint8_t getYawPitchRoll(float& yaw, float& pitch, float& roll)
        {
            // read a packet from FIFO
            if (dmpGetCurrentFIFOPacket(_fifoBuffer)) {
                dmpGetQuaternion(&_q, _fifoBuffer);
                dmpGetGravity(&_gravity, &_q);
                dmpGetYawPitchRoll(_ypr, &_q, &_gravity);
                yaw = _ypr[0] * 180 / M_PI;
                pitch = _ypr[1] * 180 / M_PI;
                roll = _ypr[2] * 180 / M_PI;
            }
            return 0;
        }



};

