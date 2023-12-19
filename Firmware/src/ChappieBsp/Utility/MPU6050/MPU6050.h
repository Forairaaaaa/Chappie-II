// I2Cdev library collection - MPU6050 I2C device class
// Based on InvenSense MPU-6050 register map document rev. 2.0, 5/19/2011 (RM-MPU-6000A-00)
// 10/3/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     ... - ongoing debug release

// NOTE: THIS IS ONLY A PARIAL RELEASE. THIS DEVICE CLASS IS CURRENTLY UNDERGOING ACTIVE
// DEVELOPMENT AND IS STILL MISSING SOME IMPORTANT FEATURES. PLEASE KEEP THIS IN MIND IF
// YOU DECIDE TO USE THIS PARTICULAR CODE FOR ANYTHING.

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef _MPU6050_H_
#define _MPU6050_H_

// #include "I2Cdev.h"
#include "../I2Cdev/I2Cdev.h"

// supporting link:  http://forum.arduino.cc/index.php?&topic=143444.msg1079517#msg1079517
// also: http://forum.arduino.cc/index.php?&topic=141571.msg1062899#msg1062899s

#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)
#include <avr/dtostrf.h>
    #ifndef BUFFER_LENGTH
        #define BUFFER_LENGTH 32
    #endif
#else
//#define PROGMEM /* empty */
//#define pgm_read_byte(x) (*(x))
//#define pgm_read_word(x) (*(x))
//#define pgm_read_float(x) (*(x))
//#define PSTR(STR) STR
#endif




/****************************************************************************************************************************************/

namespace MPU6050_IMU{
  /*integer type cast for variable*/
  // #define  uint_cast(x)    static_cast<uint8_t>(x)

  /****************************MPU6050 Address definitions*******************************/

  constexpr uint8_t MPU6050_ADDRESS_AD0_LOW  = 0x68; // address pin low (GND), default for InvenSense evaluation board
  constexpr uint8_t MPU6050_ADDRESS_AD0_HIGH = 0x69; // address pin high (VCC)
  constexpr uint8_t MPU6050_DEFAULT_ADDRESS  = MPU6050_ADDRESS_AD0_LOW;

  /******************************MPU6050 Registers******************************/

  enum   MPU6050_REG{
    MPU6050_RA_XG_OFFS_TC = 0x00,
    MPU6050_RA_YG_OFFS_TC,
    MPU6050_RA_ZG_OFFS_TC,
    MPU6050_RA_X_FINE_GAIN,
    MPU6050_RA_Y_FINE_GAIN,
    MPU6050_RA_Z_FINE_GAIN,
    MPU6050_RA_XA_OFFS_H,
    MPU6050_RA_XA_OFFS_L_TC,
    MPU6050_RA_YA_OFFS_H,
    MPU6050_RA_YA_OFFS_L_TC,
    MPU6050_RA_ZA_OFFS_H = 0x0A,
    MPU6050_RA_ZA_OFFS_L_TC,
    MPU6050_RA_SELF_TEST_X = 0x0D,
    MPU6050_RA_SELF_TEST_Y,
    MPU6050_RA_SELF_TEST_Z,
    MPU6050_RA_SELF_TEST_A = 0x10,
    MPU6050_RA_XG_OFFS_USRH = 0x13,
    MPU6050_RA_XG_OFFS_USRL,
    MPU6050_RA_YG_OFFS_USRH,
    MPU6050_RA_YG_OFFS_USRL,
    MPU6050_RA_ZG_OFFS_USRH,
    MPU6050_RA_ZG_OFFS_USRL,
    MPU6050_RA_SMPLRT_DIV,
    MPU6050_RA_CONFIG = 0x1A,
    MPU6050_RA_GYRO_CONFIG,
    MPU6050_RA_ACCEL_CONFIG,
    MPU6050_RA_FF_THR,
    MPU6050_RA_FF_DUR,
    MPU6050_RA_MOT_THR,
    MPU6050_RA_MOT_DUR = 0x20,
    MPU6050_RA_ZRMOT_THR,
    MPU6050_RA_ZRMOT_DUR,
    MPU6050_RA_FIFO_EN,
    MPU6050_RA_I2C_MST_CTRL,
    MPU6050_RA_I2C_SLV0_ADDR,
    MPU6050_RA_I2C_SLV0_REG,
    MPU6050_RA_I2C_SLV0_CTRL,
    MPU6050_RA_I2C_SLV1_ADDR,
    MPU6050_RA_I2C_SLV1_REG,
    MPU6050_RA_I2C_SLV1_CTRL = 0x2A,
    MPU6050_RA_I2C_SLV2_ADDR,
    MPU6050_RA_I2C_SLV2_REG,
    MPU6050_RA_I2C_SLV2_CTRL,
    MPU6050_RA_I2C_SLV3_ADDR,
    MPU6050_RA_I2C_SLV3_REG,
    MPU6050_RA_I2C_SLV3_CTRL =   0x30,
    MPU6050_RA_I2C_SLV4_ADDR,
    MPU6050_RA_I2C_SLV4_REG,
    MPU6050_RA_I2C_SLV4_DO,
    MPU6050_RA_I2C_SLV4_CTRL,
    MPU6050_RA_I2C_SLV4_DI,
    MPU6050_RA_I2C_MST_STATUS,
    MPU6050_RA_INT_PIN_CFG,
    MPU6050_RA_INT_ENABLE,
    MPU6050_RA_DMP_INT_STATUS,
    MPU6050_RA_INT_STATUS   =  0x3A,
    MPU6050_RA_ACCEL_XOUT_H,
    MPU6050_RA_ACCEL_XOUT_L,
    MPU6050_RA_ACCEL_YOUT_H,
    MPU6050_RA_ACCEL_YOUT_L,
    MPU6050_RA_ACCEL_ZOUT_H,
    MPU6050_RA_ACCEL_ZOUT_L  =    0x40,
    MPU6050_RA_TEMP_OUT_H,
    MPU6050_RA_TEMP_OUT_L,
    MPU6050_RA_GYRO_XOUT_H,
    MPU6050_RA_GYRO_XOUT_L,
    MPU6050_RA_GYRO_YOUT_H,
    MPU6050_RA_GYRO_YOUT_L,
    MPU6050_RA_GYRO_ZOUT_H,
    MPU6050_RA_GYRO_ZOUT_L,
    MPU6050_RA_EXT_SENS_DATA_00,
    MPU6050_RA_EXT_SENS_DATA_01  = 0x4A,
    MPU6050_RA_EXT_SENS_DATA_02,
    MPU6050_RA_EXT_SENS_DATA_03,
    MPU6050_RA_EXT_SENS_DATA_04,
    MPU6050_RA_EXT_SENS_DATA_05,
    MPU6050_RA_EXT_SENS_DATA_06,
    MPU6050_RA_EXT_SENS_DATA_07  = 0x50,
    MPU6050_RA_EXT_SENS_DATA_08,
    MPU6050_RA_EXT_SENS_DATA_09,
    MPU6050_RA_EXT_SENS_DATA_10,
    MPU6050_RA_EXT_SENS_DATA_11,
    MPU6050_RA_EXT_SENS_DATA_12,
    MPU6050_RA_EXT_SENS_DATA_13,
    MPU6050_RA_EXT_SENS_DATA_14,
    MPU6050_RA_EXT_SENS_DATA_15,
    MPU6050_RA_EXT_SENS_DATA_16,
    MPU6050_RA_EXT_SENS_DATA_17  = 0x5A,
    MPU6050_RA_EXT_SENS_DATA_18,
    MPU6050_RA_EXT_SENS_DATA_19,
    MPU6050_RA_EXT_SENS_DATA_20,
    MPU6050_RA_EXT_SENS_DATA_21,
    MPU6050_RA_EXT_SENS_DATA_22,
    MPU6050_RA_EXT_SENS_DATA_23  = 0x60,
    MPU6050_RA_MOT_DETECT_STATUS,
    MPU6050_RA_I2C_SLV0_DO       = 0x63,
    MPU6050_RA_I2C_SLV1_DO,
    MPU6050_RA_I2C_SLV2_DO,
    MPU6050_RA_I2C_SLV3_DO,
    MPU6050_RA_I2C_MST_DELAY_CTRL,
    MPU6050_RA_SIGNAL_PATH_RESET,
    MPU6050_RA_MOT_DETECT_CTRL,
    MPU6050_RA_USER_CTRL    =    0x6A,
    MPU6050_RA_PWR_MGMT_1,
    MPU6050_RA_PWR_MGMT_2,
    MPU6050_RA_BANK_SEL,
    MPU6050_RA_MEM_START_ADDR,
    MPU6050_RA_MEM_R_W,
    MPU6050_RA_DMP_CFG_1    =    0x70,
    MPU6050_RA_DMP_CFG_2,
    MPU6050_RA_FIFO_COUNTH,
    MPU6050_RA_FIFO_COUNTL,
    MPU6050_RA_FIFO_R_W,
    MPU6050_RA_WHO_AM_I

  };

  /**********************SELF TEST definitions************************/

  constexpr uint8_t MPU6050_SELF_TEST_XA_1_LENGTH = 0x03;
  constexpr uint8_t MPU6050_SELF_TEST_XA_2_LENGTH = 0x02;

  constexpr uint8_t MPU6050_SELF_TEST_YA_1_LENGTH = 0x03;
  constexpr uint8_t MPU6050_SELF_TEST_YA_2_LENGTH = 0x02;

  constexpr uint8_t MPU6050_SELF_TEST_ZA_1_LENGTH = 0x03;
  constexpr uint8_t MPU6050_SELF_TEST_ZA_2_LENGTH = 0x02;

  constexpr uint8_t MPU6050_SELF_TEST_XG_1_LENGTH = 0x05;
  constexpr uint8_t MPU6050_SELF_TEST_YG_1_LENGTH = 0x05;
  constexpr uint8_t MPU6050_SELF_TEST_ZG_1_LENGTH = 0x05;

  enum   SELF_TEST_REG_BIT{
    MPU6050_SELF_TEST_XA_1_BIT = 0x07,
    MPU6050_SELF_TEST_XA_2_BIT = 0x05,
    MPU6050_SELF_TEST_YA_1_BIT = 0x07,
    MPU6050_SELF_TEST_YA_2_BIT = 0x03,
    MPU6050_SELF_TEST_ZA_1_BIT = 0x07,
    MPU6050_SELF_TEST_ZA_2_BIT = 0x01,
    MPU6050_SELF_TEST_XG_1_BIT = 0x04,
    MPU6050_SELF_TEST_YG_1_BIT = 0x04,
    MPU6050_SELF_TEST_ZG_1_BIT = 0x04
  };

  /*************************OFFSET definitions************************/

  constexpr uint8_t MPU6050_TC_OFFSET_LENGTH =  6;
  constexpr uint8_t MPU6050_VDDIO_LEVEL_VLOGIC = 0;
  constexpr uint8_t MPU6050_VDDIO_LEVEL_VDD = 1;

  enum   OFFS_TC_REG_BIT{
    MPU6050_TC_OTP_BNK_VLD_BIT = 0,
    MPU6050_TC_OFFSET_BIT = 6,
    MPU6050_TC_PWR_MODE_BIT,
  };

  /****************************CONFIG definitions**************************/

  constexpr uint8_t MPU6050_CFG_EXT_SYNC_SET_LENGTH  = 3;
  constexpr uint8_t MPU6050_CFG_DLPF_CFG_LENGTH  = 3;

  enum   CONFIG_REG_BIT{
    MPU6050_CFG_DLPF_CFG_BIT  =  2,
    MPU6050_CFG_EXT_SYNC_SET_BIT  = 5,
  };

  enum   EXT_SYNC_SET{
    MPU6050_EXT_SYNC_DISABLED  = 0x00,
    MPU6050_EXT_SYNC_TEMP_OUT_L,
    MPU6050_EXT_SYNC_GYRO_XOUT_L,
    MPU6050_EXT_SYNC_GYRO_YOUT_L,
    MPU6050_EXT_SYNC_GYRO_ZOUT_L,
    MPU6050_EXT_SYNC_ACCEL_XOUT_L,
    MPU6050_EXT_SYNC_ACCEL_YOUT_L,
    MPU6050_EXT_SYNC_ACCEL_ZOUT_L,
  };

  enum   DLPF_CFG{
    MPU6050_DLPF_BW_256  = 0x00,
    MPU6050_DLPF_BW_188,
    MPU6050_DLPF_BW_98,
    MPU6050_DLPF_BW_42,
    MPU6050_DLPF_BW_20,
    MPU6050_DLPF_BW_10,
    MPU6050_DLPF_BW_5,
  };

  /*****************************GYRO_CONFIG definitions****************************/

  constexpr uint8_t MPU6050_GCONFIG_FS_SEL_LENGTH =  2;

  enum   GYRO_CONFIG_REG_BIT{
    MPU6050_GCONFIG_FS_SEL_BIT = 4,
    MPU6050_ACONFIG_ZG_ST_BIT,
    MPU6050_ACONFIG_YG_ST_BIT,
    MPU6050_ACONFIG_XG_ST_BIT,
  };

  enum   GYRO_FS{
     MPU6050_GYRO_FS_250    =     0x00,
     MPU6050_GYRO_FS_500,
     MPU6050_GYRO_FS_1000,
     MPU6050_GYRO_FS_2000,
  };

  /*******************************ACCEL_CONFIG definitions**************************/

  constexpr uint8_t MPU6050_ACONFIG_AFS_SEL_LENGTH =  2;
  constexpr uint8_t MPU6050_ACONFIG_ACCEL_HPF_LENGTH =  3;

  enum   ACCEL_CONFIG_REG_BIT{
    MPU6050_ACONFIG_ACCEL_HPF_BIT = 2,
    MPU6050_ACONFIG_AFS_SEL_BIT   = 4,
    MPU6050_ACONFIG_ZA_ST_BIT,
    MPU6050_ACONFIG_YA_ST_BIT,
    MPU6050_ACONFIG_XA_ST_BIT
  };

  enum   ACCEL_FS{
    MPU6050_ACCEL_FS_2 = 0x00,
    MPU6050_ACCEL_FS_4,
    MPU6050_ACCEL_FS_8,
    MPU6050_ACCEL_FS_16,
  };

  enum   ACCEL_HPF{
    MPU6050_DHPF_RESET = 0x00,
    MPU6050_DHPF_5,
    MPU6050_DHPF_2P5,
    MPU6050_DHPF_1P25,
    MPU6050_DHPF_0P63,
    MPU6050_DHPF_HOLD = 0x07,
  };

  /***********************************FIFO_EN definitions*************************/

  enum   FIFO_EN_REG_BIT{
    MPU6050_SLV0_FIFO_EN_BIT  = 0,
    MPU6050_SLV1_FIFO_EN_BIT,
    MPU6050_SLV2_FIFO_EN_BIT,
    MPU6050_ACCEL_FIFO_EN_BIT,
    MPU6050_ZG_FIFO_EN_BIT,
    MPU6050_YG_FIFO_EN_BIT,
    MPU6050_XG_FIFO_EN_BIT,
    MPU6050_TEMP_FIFO_EN_BIT,
  };

  /**********************************I2C_MST_CTRL definitions***************************/

  constexpr uint8_t MPU6050_I2C_MST_CLK_LENGTH = 4;

  enum   I2C_MST_CTRL_REG_BIT{
    MPU6050_I2C_MST_CLK_BIT = 3,
    MPU6050_I2C_MST_P_NSR_BIT,
    MPU6050_SLV_3_FIFO_EN_BIT,
    MPU6050_WAIT_FOR_ES_BIT,
    MPU6050_MULT_MST_EN_BIT,
  };

  enum   I2C_Prescaler{
    MPU6050_CLOCK_DIV_348   =    0x0,
    MPU6050_CLOCK_DIV_333,
    MPU6050_CLOCK_DIV_320,
    MPU6050_CLOCK_DIV_308,
    MPU6050_CLOCK_DIV_296,
    MPU6050_CLOCK_DIV_286,
    MPU6050_CLOCK_DIV_276,
    MPU6050_CLOCK_DIV_267,
    MPU6050_CLOCK_DIV_258,
    MPU6050_CLOCK_DIV_500,
    MPU6050_CLOCK_DIV_471   =    0xA,
    MPU6050_CLOCK_DIV_444,
    MPU6050_CLOCK_DIV_421,
    MPU6050_CLOCK_DIV_400,
    MPU6050_CLOCK_DIV_381,
    MPU6050_CLOCK_DIV_364,
  };

  /*********************************I2C_SLVx_ADDR definitions*****************************/

  constexpr uint8_t MPU6050_I2C_SLV_ADDR_LENGTH = 7;
  constexpr uint8_t MPU6050_I2C_SLV_LEN_LENGTH  =  4;

  enum   I2C_SLVx_ADDR_REG_BIT{
    MPU6050_I2C_SLV_ADDR_BIT = 6,
    MPU6050_I2C_SLV_RW_BIT,
  };


  /****************************I2C_SLVx_CTRL definitions (x=0,1,2,3)***********************/

  enum   I2C_SLVx_CTRL_REG_BIT{
    MPU6050_I2C_SLV_LEN_BIT = 3,
    MPU6050_I2C_SLV_GRP_BIT,
    MPU6050_I2C_SLV_REG_DIS_BIT,
    MPU6050_I2C_SLV_BYTE_SW_BIT,
    MPU6050_I2C_SLV_EN_BIT
  };

  /******************************I2C_SLV4_ADDR definitions*************************/

  constexpr uint8_t MPU6050_I2C_SLV4_ADDR_LENGTH =  7;

  enum   I2C_SLV4_ADDR_REG_BIT{
    MPU6050_I2C_SLV4_ADDR_BIT = 6,
    MPU6050_I2C_SLV4_RW_BIT,
  };

  /*********************************I2C_SLV4_CTRL definitions************************/

  constexpr uint8_t MPU6050_I2C_SLV4_MST_DLY_LENGTH = 5;

  enum   I2C_SLV4_CTRL_REG_BIT{
    MPU6050_I2C_SLV4_MST_DLY_BIT = 4,
    MPU6050_I2C_SLV4_REG_DIS_BIT,
    MPU6050_I2C_SLV4_INT_EN_BIT,
    MPU6050_I2C_SLV4_EN_BIT,
  };

  /*******************************I2C_MST_STATUS definitions************************/

  enum   I2C_MST_STATUS_REG_BIT{
    MPU6050_MST_I2C_SLV0_NACK_BIT = 0,
    MPU6050_MST_I2C_SLV1_NACK_BIT,
    MPU6050_MST_I2C_SLV2_NACK_BIT,
    MPU6050_MST_I2C_SLV3_NACK_BIT,
    MPU6050_MST_I2C_SLV4_NACK_BIT,
    MPU6050_MST_I2C_LOST_ARB_BIT,
    MPU6050_MST_I2C_SLV4_DONE_BIT,
    MPU6050_MST_PASS_THROUGH_BIT,
  };

  /***********************************INT_PIN_CFG definitions***************************/

  constexpr uint8_t MPU6050_INTMODE_ACTIVEHIGH = 0x00;
  constexpr uint8_t MPU6050_INTMODE_ACTIVELOW  = 0x01;

  constexpr uint8_t MPU6050_INTDRV_PUSHPULL  =   0x00;
  constexpr uint8_t MPU6050_INTDRV_OPENDRAIN =   0x01;

  constexpr uint8_t MPU6050_INTLATCH_50USPULSE = 0x00;
  constexpr uint8_t MPU6050_INTLATCH_WAITCLEAR = 0x01;

  constexpr uint8_t MPU6050_INTCLEAR_STATUSREAD = 0x00;
  constexpr uint8_t MPU6050_INTCLEAR_ANYREAD    = 0x01;

  enum   INT_PIN_CFG_REG_BIT{
    MPU6050_INTCFG_CLKOUT_EN_BIT = 0,
    MPU6050_INTCFG_I2C_BYPASS_EN_BIT,
    MPU6050_INTCFG_FSYNC_INT_EN_BIT,
    MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT,
    MPU6050_INTCFG_INT_RD_CLEAR_BIT,
    MPU6050_INTCFG_LATCH_INT_EN_BIT,
    MPU6050_INTCFG_INT_OPEN_BIT,
    MPU6050_INTCFG_INT_LEVEL_BIT,
  };

  /*********************************INT_STATUS definitions**************************/

  enum   INT_STATUS_REG_BIT{
    MPU6050_INTERRUPT_DATA_RDY_BIT = 0,
    MPU6050_INTERRUPT_DMP_INT_BIT,
    MPU6050_INTERRUPT_PLL_RDY_INT_BIT,
    MPU6050_INTERRUPT_I2C_MST_INT_BIT,
    MPU6050_INTERRUPT_FIFO_OFLOW_BIT,
    MPU6050_INTERRUPT_ZMOT_BIT,
    MPU6050_INTERRUPT_MOT_BIT,
    MPU6050_INTERRUPT_FF_BIT,
  };

  // TODO: figure out what these actually do
  // UMPL source code is not very obivous

  /***************************DMP_INT_STATUS definitions***************************/

  enum   DMP_INT_STATUS_REG_BIT{
    MPU6050_DMPINT_0_BIT = 0,
    MPU6050_DMPINT_1_BIT,
    MPU6050_DMPINT_2_BIT,
    MPU6050_DMPINT_3_BIT,
    MPU6050_DMPINT_4_BIT,
    MPU6050_DMPINT_5_BIT,
  };

  /***************************MOT_DETECT_STATUS definitions*************************/

  enum   MOT_DETECT_STATUS_REG_BIT{
    MPU6050_MOTION_MOT_ZRMOT_BIT = 0,
    MPU6050_MOTION_MOT_ZPOS_BIT = 2,
    MPU6050_MOTION_MOT_ZNEG_BIT,
    MPU6050_MOTION_MOT_YPOS_BIT,
    MPU6050_MOTION_MOT_YNEG_BIT,
    MPU6050_MOTION_MOT_XPOS_BIT,
    MPU6050_MOTION_MOT_XNEG_BIT,
  };

  /*****************************I2C_MST_DELAY_CTRL definitions************************/

  enum   I2C_MST_DELAY_CTRL_REG_BIT{
    MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT = 0,
    MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT,
    MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT,
    MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT,
    MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT,
    MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT = 7,
  };

  /*****************************SIGNAL_PATH_RESET definitions**************************/

  enum   SIGNAL_PATH_RESET_REG_BIT{
    MPU6050_PATHRESET_TEMP_RESET_BIT = 0,
    MPU6050_PATHRESET_ACCEL_RESET_BIT,
    MPU6050_PATHRESET_GYRO_RESET_BIT
  };

  /***************************MOT_DETECT_CTRL definitions*****************************/

  constexpr uint8_t MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH  =  2;
  constexpr uint8_t MPU6050_DETECT_FF_COUNT_LENGTH   =   2;
  constexpr uint8_t MPU6050_DETECT_MOT_COUNT_LENGTH  =   2;

  enum   MOT_DETECT_CTRL_REG_BIT{
    MPU6050_DETECT_MOT_COUNT_BIT = 1,
    MPU6050_DETECT_FF_COUNT_BIT = 3,
    MPU6050_DETECT_ACCEL_ON_DELAY_BIT = 5,
  };

  /********************************USER_CTRL definitions******************************/

  enum   USER_CTRL_REG_BIT{
    MPU6050_USERCTRL_SIG_COND_RESET_BIT = 0,
    MPU6050_USERCTRL_I2C_MST_RESET_BIT,
    MPU6050_USERCTRL_FIFO_RESET_BIT,
    MPU6050_USERCTRL_DMP_RESET_BIT,
    MPU6050_USERCTRL_I2C_IF_DIS_BIT,
    MPU6050_USERCTRL_I2C_MST_EN_BIT,
    MPU6050_USERCTRL_FIFO_EN_BIT,
    MPU6050_USERCTRL_DMP_EN_BIT
  };


  /*********************************PWR_MGMT_1 definitions*******************************/

  constexpr uint8_t MPU6050_PWR1_CLKSEL_LENGTH  =    3;

  enum   PWR_MGMT_1_REG_BIT{
    MPU6050_PWR1_CLKSEL_BIT    =    2,
    MPU6050_PWR1_TEMP_DIS_BIT,
    MPU6050_PWR1_CYCLE_BIT     =    5,
    MPU6050_PWR1_SLEEP_BIT,
    MPU6050_PWR1_DEVICE_RESET_BIT,
  };


  enum   CLK_SRC{
    MPU6050_CLOCK_INTERNAL    =      0x00,
    MPU6050_CLOCK_PLL_XGYRO,
    MPU6050_CLOCK_PLL_YGYRO,
    MPU6050_CLOCK_PLL_ZGYRO,
    MPU6050_CLOCK_PLL_EXT32K,
    MPU6050_CLOCK_PLL_EXT19M,
    MPU6050_CLOCK_KEEP_RESET  =      0x07,
  };

  /*****************************PWR_MGMT_2 definitions****************************/

  constexpr uint8_t MPU6050_PWR2_LP_WAKE_CTRL_LENGTH  =  2;

  enum   PWR_MGMT_2_REG_BIT{
    MPU6050_PWR2_STBY_ZG_BIT = 0,
    MPU6050_PWR2_STBY_YG_BIT,
    MPU6050_PWR2_STBY_XG_BIT,
    MPU6050_PWR2_STBY_ZA_BIT,
    MPU6050_PWR2_STBY_YA_BIT,
    MPU6050_PWR2_STBY_XA_BIT,
    MPU6050_PWR2_LP_WAKE_CTRL_BIT  = 7,
  };

  enum   WAKE_FREQ{
    MPU6050_WAKE_FREQ_1P25  =    0x0,
    MPU6050_WAKE_FREQ_2P5,
    MPU6050_WAKE_FREQ_5,
    MPU6050_WAKE_FREQ_10,
  };

  /*WHO_AM_I definitions*/
  constexpr uint8_t  MPU6050_WHO_AM_I_BIT  =  6;
  constexpr uint8_t  MPU6050_WHO_AM_I_LENGTH  =  6;

  /*memory block definitions*/
  constexpr uint8_t MPU6050_DMP_MEMORY_BANKS  =  8;
  constexpr uint16_t MPU6050_DMP_MEMORY_BANK_SIZE  =  256;
  constexpr uint8_t MPU6050_DMP_MEMORY_CHUNK_SIZE =  16;
};


// note: DMP code memory blocks defined at end of header file

class MPU6050 {
    public:
        MPU6050(uint8_t address=(MPU6050_IMU::MPU6050_DEFAULT_ADDRESS));

        void initialize();
        bool testConnection();

        // AUX_VDDIO register
        uint8_t getAuxVDDIOLevel();
        void setAuxVDDIOLevel(uint8_t level);

        // SMPLRT_DIV register
        uint8_t getRate();
        void setRate(uint8_t rate);

        // CONFIG register
        uint8_t getExternalFrameSync();
        void setExternalFrameSync(uint8_t sync);
        uint8_t getDLPFMode();
        void setDLPFMode(uint8_t bandwidth);

        // GYRO_CONFIG register
        uint8_t getFullScaleGyroRange();
        void setFullScaleGyroRange(uint8_t range);

        // SELF_TEST registers
        uint8_t getAccelXSelfTestFactoryTrim();
        uint8_t getAccelYSelfTestFactoryTrim();
        uint8_t getAccelZSelfTestFactoryTrim();

        uint8_t getGyroXSelfTestFactoryTrim();
        uint8_t getGyroYSelfTestFactoryTrim();
        uint8_t getGyroZSelfTestFactoryTrim();

        // ACCEL_CONFIG register
        bool getAccelXSelfTest();
        void setAccelXSelfTest(bool enabled);
        bool getAccelYSelfTest();
        void setAccelYSelfTest(bool enabled);
        bool getAccelZSelfTest();
        void setAccelZSelfTest(bool enabled);
        uint8_t getFullScaleAccelRange();
        void setFullScaleAccelRange(uint8_t range);
        uint8_t getDHPFMode();
        void setDHPFMode(uint8_t mode);

        // FF_THR register
        uint8_t getFreefallDetectionThreshold();
        void setFreefallDetectionThreshold(uint8_t threshold);

        // FF_DUR register
        uint8_t getFreefallDetectionDuration();
        void setFreefallDetectionDuration(uint8_t duration);

        // MOT_THR register
        uint8_t getMotionDetectionThreshold();
        void setMotionDetectionThreshold(uint8_t threshold);

        // MOT_DUR register
        uint8_t getMotionDetectionDuration();
        void setMotionDetectionDuration(uint8_t duration);

        // ZRMOT_THR register
        uint8_t getZeroMotionDetectionThreshold();
        void setZeroMotionDetectionThreshold(uint8_t threshold);

        // ZRMOT_DUR register
        uint8_t getZeroMotionDetectionDuration();
        void setZeroMotionDetectionDuration(uint8_t duration);

        // FIFO_EN register
        bool getTempFIFOEnabled();
        void setTempFIFOEnabled(bool enabled);
        bool getXGyroFIFOEnabled();
        void setXGyroFIFOEnabled(bool enabled);
        bool getYGyroFIFOEnabled();
        void setYGyroFIFOEnabled(bool enabled);
        bool getZGyroFIFOEnabled();
        void setZGyroFIFOEnabled(bool enabled);
        bool getAccelFIFOEnabled();
        void setAccelFIFOEnabled(bool enabled);
        bool getSlave2FIFOEnabled();
        void setSlave2FIFOEnabled(bool enabled);
        bool getSlave1FIFOEnabled();
        void setSlave1FIFOEnabled(bool enabled);
        bool getSlave0FIFOEnabled();
        void setSlave0FIFOEnabled(bool enabled);

        // I2C_MST_CTRL register
        bool getMultiMasterEnabled();
        void setMultiMasterEnabled(bool enabled);
        bool getWaitForExternalSensorEnabled();
        void setWaitForExternalSensorEnabled(bool enabled);
        bool getSlave3FIFOEnabled();
        void setSlave3FIFOEnabled(bool enabled);
        bool getSlaveReadWriteTransitionEnabled();
        void setSlaveReadWriteTransitionEnabled(bool enabled);
        uint8_t getMasterClockSpeed();
        void setMasterClockSpeed(uint8_t speed);

        // I2C_SLV* registers (Slave 0-3)
        uint8_t getSlaveAddress(uint8_t num);
        void setSlaveAddress(uint8_t num, uint8_t address);
        uint8_t getSlaveRegister(uint8_t num);
        void setSlaveRegister(uint8_t num, uint8_t reg);
        bool getSlaveEnabled(uint8_t num);
        void setSlaveEnabled(uint8_t num, bool enabled);
        bool getSlaveWordByteSwap(uint8_t num);
        void setSlaveWordByteSwap(uint8_t num, bool enabled);
        bool getSlaveWriteMode(uint8_t num);
        void setSlaveWriteMode(uint8_t num, bool mode);
        bool getSlaveWordGroupOffset(uint8_t num);
        void setSlaveWordGroupOffset(uint8_t num, bool enabled);
        uint8_t getSlaveDataLength(uint8_t num);
        void setSlaveDataLength(uint8_t num, uint8_t length);

        // I2C_SLV* registers (Slave 4)
        uint8_t getSlave4Address();
        void setSlave4Address(uint8_t address);
        uint8_t getSlave4Register();
        void setSlave4Register(uint8_t reg);
        void setSlave4OutputByte(uint8_t data);
        bool getSlave4Enabled();
        void setSlave4Enabled(bool enabled);
        bool getSlave4InterruptEnabled();
        void setSlave4InterruptEnabled(bool enabled);
        bool getSlave4WriteMode();
        void setSlave4WriteMode(bool mode);
        uint8_t getSlave4MasterDelay();
        void setSlave4MasterDelay(uint8_t delay);
        uint8_t getSlate4InputByte();

        // I2C_MST_STATUS register
        bool getPassthroughStatus();
        bool getSlave4IsDone();
        bool getLostArbitration();
        bool getSlave4Nack();
        bool getSlave3Nack();
        bool getSlave2Nack();
        bool getSlave1Nack();
        bool getSlave0Nack();

        // INT_PIN_CFG register
        bool getInterruptMode();
        void setInterruptMode(bool mode);
        bool getInterruptDrive();
        void setInterruptDrive(bool drive);
        bool getInterruptLatch();
        void setInterruptLatch(bool latch);
        bool getInterruptLatchClear();
        void setInterruptLatchClear(bool clear);
        bool getFSyncInterruptLevel();
        void setFSyncInterruptLevel(bool level);
        bool getFSyncInterruptEnabled();
        void setFSyncInterruptEnabled(bool enabled);
        bool getI2CBypassEnabled();
        void setI2CBypassEnabled(bool enabled);
        bool getClockOutputEnabled();
        void setClockOutputEnabled(bool enabled);

        // INT_ENABLE register
        uint8_t getIntEnabled();
        void setIntEnabled(uint8_t enabled);
        bool getIntFreefallEnabled();
        void setIntFreefallEnabled(bool enabled);
        bool getIntMotionEnabled();
        void setIntMotionEnabled(bool enabled);
        bool getIntZeroMotionEnabled();
        void setIntZeroMotionEnabled(bool enabled);
        bool getIntFIFOBufferOverflowEnabled();
        void setIntFIFOBufferOverflowEnabled(bool enabled);
        bool getIntI2CMasterEnabled();
        void setIntI2CMasterEnabled(bool enabled);
        bool getIntDataReadyEnabled();
        void setIntDataReadyEnabled(bool enabled);

        // INT_STATUS register
        uint8_t getIntStatus();
        bool getIntFreefallStatus();
        bool getIntMotionStatus();
        bool getIntZeroMotionStatus();
        bool getIntFIFOBufferOverflowStatus();
        bool getIntI2CMasterStatus();
        bool getIntDataReadyStatus();

        // ACCEL_*OUT_* registers
        void getMotion9(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz, int16_t* mx, int16_t* my, int16_t* mz);
        void getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
        void getAcceleration(int16_t* x, int16_t* y, int16_t* z);
        int16_t getAccelerationX();
        int16_t getAccelerationY();
        int16_t getAccelerationZ();

        // TEMP_OUT_* registers
        int16_t getTemperature();

        // GYRO_*OUT_* registers
        void getRotation(int16_t* x, int16_t* y, int16_t* z);
        int16_t getRotationX();
        int16_t getRotationY();
        int16_t getRotationZ();

        // EXT_SENS_DATA_* registers
        uint8_t getExternalSensorByte(int position);
        uint16_t getExternalSensorWord(int position);
        uint32_t getExternalSensorDWord(int position);

        // MOT_DETECT_STATUS register
        uint8_t getMotionStatus();
        bool getXNegMotionDetected();
        bool getXPosMotionDetected();
        bool getYNegMotionDetected();
        bool getYPosMotionDetected();
        bool getZNegMotionDetected();
        bool getZPosMotionDetected();
        bool getZeroMotionDetected();

        // I2C_SLV*_DO register
        void setSlaveOutputByte(uint8_t num, uint8_t data);

        // I2C_MST_DELAY_CTRL register
        bool getExternalShadowDelayEnabled();
        void setExternalShadowDelayEnabled(bool enabled);
        bool getSlaveDelayEnabled(uint8_t num);
        void setSlaveDelayEnabled(uint8_t num, bool enabled);

        // SIGNAL_PATH_RESET register
        void resetGyroscopePath();
        void resetAccelerometerPath();
        void resetTemperaturePath();

        // MOT_DETECT_CTRL register
        uint8_t getAccelerometerPowerOnDelay();
        void setAccelerometerPowerOnDelay(uint8_t delay);
        uint8_t getFreefallDetectionCounterDecrement();
        void setFreefallDetectionCounterDecrement(uint8_t decrement);
        uint8_t getMotionDetectionCounterDecrement();
        void setMotionDetectionCounterDecrement(uint8_t decrement);

        // USER_CTRL register
        bool getFIFOEnabled();
        void setFIFOEnabled(bool enabled);
        bool getI2CMasterModeEnabled();
        void setI2CMasterModeEnabled(bool enabled);
        void switchSPIEnabled(bool enabled);
        void resetFIFO();
        void resetI2CMaster();
        void resetSensors();

        // PWR_MGMT_1 register
        void reset();
        bool getSleepEnabled();
        void setSleepEnabled(bool enabled);
        bool getWakeCycleEnabled();
        void setWakeCycleEnabled(bool enabled);
        bool getTempSensorEnabled();
        void setTempSensorEnabled(bool enabled);
        uint8_t getClockSource();
        void setClockSource(uint8_t source);

        // PWR_MGMT_2 register
        uint8_t getWakeFrequency();
        void setWakeFrequency(uint8_t frequency);
        bool getStandbyXAccelEnabled();
        void setStandbyXAccelEnabled(bool enabled);
        bool getStandbyYAccelEnabled();
        void setStandbyYAccelEnabled(bool enabled);
        bool getStandbyZAccelEnabled();
        void setStandbyZAccelEnabled(bool enabled);
        bool getStandbyXGyroEnabled();
        void setStandbyXGyroEnabled(bool enabled);
        bool getStandbyYGyroEnabled();
        void setStandbyYGyroEnabled(bool enabled);
        bool getStandbyZGyroEnabled();
        void setStandbyZGyroEnabled(bool enabled);

        // FIFO_COUNT_* registers
        uint16_t getFIFOCount();

        // FIFO_R_W register
        uint8_t getFIFOByte();
		int8_t GetCurrentFIFOPacket(uint8_t *data, uint8_t length);
        void setFIFOByte(uint8_t data);
        void getFIFOBytes(uint8_t *data, uint8_t length);

        // WHO_AM_I register
        uint8_t getDeviceID();
        void setDeviceID(uint8_t id);

        // ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========

        // XG_OFFS_TC register
        uint8_t getOTPBankValid();
        void setOTPBankValid(bool enabled);
        int8_t getXGyroOffsetTC();
        void setXGyroOffsetTC(int8_t offset);

        // YG_OFFS_TC register
        int8_t getYGyroOffsetTC();
        void setYGyroOffsetTC(int8_t offset);

        // ZG_OFFS_TC register
        int8_t getZGyroOffsetTC();
        void setZGyroOffsetTC(int8_t offset);

        // X_FINE_GAIN register
        int8_t getXFineGain();
        void setXFineGain(int8_t gain);

        // Y_FINE_GAIN register
        int8_t getYFineGain();
        void setYFineGain(int8_t gain);

        // Z_FINE_GAIN register
        int8_t getZFineGain();
        void setZFineGain(int8_t gain);

        // XA_OFFS_* registers
        int16_t getXAccelOffset();
        void setXAccelOffset(int16_t offset);

        // YA_OFFS_* register
        int16_t getYAccelOffset();
        void setYAccelOffset(int16_t offset);

        // ZA_OFFS_* register
        int16_t getZAccelOffset();
        void setZAccelOffset(int16_t offset);

        // XG_OFFS_USR* registers
        int16_t getXGyroOffset();
        void setXGyroOffset(int16_t offset);

        // YG_OFFS_USR* register
        int16_t getYGyroOffset();
        void setYGyroOffset(int16_t offset);

        // ZG_OFFS_USR* register
        int16_t getZGyroOffset();
        void setZGyroOffset(int16_t offset);

        // INT_ENABLE register (DMP functions)
        bool getIntPLLReadyEnabled();
        void setIntPLLReadyEnabled(bool enabled);
        bool getIntDMPEnabled();
        void setIntDMPEnabled(bool enabled);

        // DMP_INT_STATUS
        bool getDMPInt5Status();
        bool getDMPInt4Status();
        bool getDMPInt3Status();
        bool getDMPInt2Status();
        bool getDMPInt1Status();
        bool getDMPInt0Status();

        // INT_STATUS register (DMP functions)
        bool getIntPLLReadyStatus();
        bool getIntDMPStatus();

        // USER_CTRL register (DMP functions)
        bool getDMPEnabled();
        void setDMPEnabled(bool enabled);
        void resetDMP();

        // BANK_SEL register
        void setMemoryBank(uint8_t bank, bool prefetchEnabled=false, bool userBank=false);

        // MEM_START_ADDR register
        void setMemoryStartAddress(uint8_t address);

        // MEM_R_W register
        uint8_t readMemoryByte();
        void writeMemoryByte(uint8_t data);
        void readMemoryBlock(uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0);
        bool writeMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0, bool verify=true, bool useProgMem=false);
        bool writeProgMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0, bool verify=true);

        bool writeDMPConfigurationSet(const uint8_t *data, uint16_t dataSize, bool useProgMem=false);
        bool writeProgDMPConfigurationSet(const uint8_t *data, uint16_t dataSize);

        // DMP_CFG_1 register
        uint8_t getDMPConfig1();
        void setDMPConfig1(uint8_t config);

        // DMP_CFG_2 register
        uint8_t getDMPConfig2();
        void setDMPConfig2(uint8_t config);

		// Calibration Routines
		void CalibrateGyro(uint8_t Loops = 15); // Fine tune after setting offsets with less Loops.
		void CalibrateAccel(uint8_t Loops = 15);// Fine tune after setting offsets with less Loops.
		void PID(uint8_t ReadAddress, float kP,float kI, uint8_t Loops);  // Does the math
		void PrintActiveOffsets(); // See the results of the Calibration



        // special methods for MotionApps 2.0 implementation
        #ifdef MPU6050_INCLUDE_DMP_MOTIONAPPS20

            uint8_t dmpInitialize();
            bool dmpPacketAvailable();

            uint8_t dmpSetFIFORate(uint8_t fifoRate);
            uint8_t dmpGetFIFORate();
            uint8_t dmpGetSampleStepSizeMS();
            uint8_t dmpGetSampleFrequency();
            int32_t dmpDecodeTemperature(int8_t tempReg);

            // Register callbacks after a packet of FIFO data is processed
            //uint8_t dmpRegisterFIFORateProcess(inv_obj_func func, int16_t priority);
            //uint8_t dmpUnregisterFIFORateProcess(inv_obj_func func);
            uint8_t dmpRunFIFORateProcesses();

            // Setup FIFO for various output
            uint8_t dmpSendQuaternion(uint_fast16_t accuracy);
            uint8_t dmpSendGyro(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendAccel(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendLinearAccel(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendLinearAccelInWorld(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendControlData(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendExternalSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendGravity(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendPacketNumber(uint_fast16_t accuracy);
            uint8_t dmpSendQuantizedAccel(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendEIS(uint_fast16_t elements, uint_fast16_t accuracy);

            // Get Fixed Point data from FIFO
            uint8_t dmpGetAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetQuaternion(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuaternion(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuaternion(Quaternion *q, const uint8_t* packet=0);
            uint8_t dmpGet6AxisQuaternion(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGet6AxisQuaternion(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGet6AxisQuaternion(Quaternion *q, const uint8_t* packet=0);
            uint8_t dmpGetRelativeQuaternion(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetRelativeQuaternion(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetRelativeQuaternion(Quaternion *data, const uint8_t* packet=0);
            uint8_t dmpGetGyro(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyro(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyro(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpSetLinearAccelFilterCoefficient(float coef);
            uint8_t dmpGetLinearAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccel(VectorInt16 *v, VectorInt16 *vRaw, VectorFloat *gravity);
            uint8_t dmpGetLinearAccelInWorld(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccelInWorld(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, VectorInt16 *vReal, Quaternion *q);
            uint8_t dmpGetGyroAndAccelSensor(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroAndAccelSensor(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroAndAccelSensor(VectorInt16 *g, VectorInt16 *a, const uint8_t* packet=0);
            uint8_t dmpGetGyroSensor(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroSensor(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroSensor(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetControlData(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetTemperature(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGravity(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGravity(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGravity(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetGravity(VectorFloat *v, Quaternion *q);
            uint8_t dmpGetUnquantizedAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetUnquantizedAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetUnquantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetQuantizedAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuantizedAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetExternalSensorData(int32_t *data, uint16_t size, const uint8_t* packet=0);
            uint8_t dmpGetEIS(int32_t *data, const uint8_t* packet=0);

            uint8_t dmpGetEuler(float *data, Quaternion *q);
            uint8_t dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);

            // Get Floating Point data from FIFO
            uint8_t dmpGetAccelFloat(float *data, const uint8_t* packet=0);
            uint8_t dmpGetQuaternionFloat(float *data, const uint8_t* packet=0);

            uint8_t dmpProcessFIFOPacket(const unsigned char *dmpData);
            uint8_t dmpReadAndProcessFIFOPacket(uint8_t numPackets, uint8_t *processed=NULL);

            uint8_t dmpSetFIFOProcessedCallback(void (*func) (void));

            uint8_t dmpInitFIFOParam();
            uint8_t dmpCloseFIFO();
            uint8_t dmpSetGyroDataSource(uint8_t source);
            uint8_t dmpDecodeQuantizedAccel();
            uint32_t dmpGetGyroSumOfSquare();
            uint32_t dmpGetAccelSumOfSquare();
            void dmpOverrideQuaternion(long *q);
            uint16_t dmpGetFIFOPacketSize();
            uint8_t dmpGetCurrentFIFOPacket(uint8_t *data); // overflow proof
        #endif

        // special methods for MotionApps 4.1 implementation
        #ifdef MPU6050_INCLUDE_DMP_MOTIONAPPS41

            uint8_t dmpInitialize();
            bool dmpPacketAvailable();

            uint8_t dmpSetFIFORate(uint8_t fifoRate);
            uint8_t dmpGetFIFORate();
            uint8_t dmpGetSampleStepSizeMS();
            uint8_t dmpGetSampleFrequency();
            int32_t dmpDecodeTemperature(int8_t tempReg);

            // Register callbacks after a packet of FIFO data is processed
            //uint8_t dmpRegisterFIFORateProcess(inv_obj_func func, int16_t priority);
            //uint8_t dmpUnregisterFIFORateProcess(inv_obj_func func);
            uint8_t dmpRunFIFORateProcesses();

            // Setup FIFO for various output
            uint8_t dmpSendQuaternion(uint_fast16_t accuracy);
            uint8_t dmpSendGyro(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendAccel(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendLinearAccel(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendLinearAccelInWorld(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendControlData(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendExternalSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendGravity(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendPacketNumber(uint_fast16_t accuracy);
            uint8_t dmpSendQuantizedAccel(uint_fast16_t elements, uint_fast16_t accuracy);
            uint8_t dmpSendEIS(uint_fast16_t elements, uint_fast16_t accuracy);

            // Get Fixed Point data from FIFO
            uint8_t dmpGetAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetQuaternion(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuaternion(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuaternion(Quaternion *q, const uint8_t* packet=0);
            uint8_t dmpGet6AxisQuaternion(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGet6AxisQuaternion(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGet6AxisQuaternion(Quaternion *q, const uint8_t* packet=0);
            uint8_t dmpGetRelativeQuaternion(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetRelativeQuaternion(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetRelativeQuaternion(Quaternion *data, const uint8_t* packet=0);
            uint8_t dmpGetGyro(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyro(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyro(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetMag(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpSetLinearAccelFilterCoefficient(float coef);
            uint8_t dmpGetLinearAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccel(VectorInt16 *v, VectorInt16 *vRaw, VectorFloat *gravity);
            uint8_t dmpGetLinearAccelInWorld(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccelInWorld(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, VectorInt16 *vReal, Quaternion *q);
            uint8_t dmpGetGyroAndAccelSensor(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroAndAccelSensor(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroAndAccelSensor(VectorInt16 *g, VectorInt16 *a, const uint8_t* packet=0);
            uint8_t dmpGetGyroSensor(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroSensor(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGyroSensor(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetControlData(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetTemperature(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGravity(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGravity(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetGravity(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetGravity(VectorFloat *v, Quaternion *q);
            uint8_t dmpGetUnquantizedAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetUnquantizedAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetUnquantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetQuantizedAccel(int32_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuantizedAccel(int16_t *data, const uint8_t* packet=0);
            uint8_t dmpGetQuantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
            uint8_t dmpGetExternalSensorData(int32_t *data, uint16_t size, const uint8_t* packet=0);
            uint8_t dmpGetEIS(int32_t *data, const uint8_t* packet=0);

            uint8_t dmpGetEuler(float *data, Quaternion *q);
            uint8_t dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);

            // Get Floating Point data from FIFO
            uint8_t dmpGetAccelFloat(float *data, const uint8_t* packet=0);
            uint8_t dmpGetQuaternionFloat(float *data, const uint8_t* packet=0);

            uint8_t dmpProcessFIFOPacket(const unsigned char *dmpData);
            uint8_t dmpReadAndProcessFIFOPacket(uint8_t numPackets, uint8_t *processed=NULL);

            uint8_t dmpSetFIFOProcessedCallback(void (*func) (void));

            uint8_t dmpInitFIFOParam();
            uint8_t dmpCloseFIFO();
            uint8_t dmpSetGyroDataSource(uint8_t source);
            uint8_t dmpDecodeQuantizedAccel();
            uint32_t dmpGetGyroSumOfSquare();
            uint32_t dmpGetAccelSumOfSquare();
            void dmpOverrideQuaternion(long *q);
            uint16_t dmpGetFIFOPacketSize();
        #endif

    private:
        uint8_t devAddr;
        uint8_t buffer[14];
    #if defined(MPU6050_INCLUDE_DMP_MOTIONAPPS20) or defined(MPU6050_INCLUDE_DMP_MOTIONAPPS41)
        uint8_t *dmpPacketBuffer;
        uint16_t dmpPacketSize;
    #endif
};

#endif /* _MPU6050_H_ */
