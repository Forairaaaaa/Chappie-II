#ifndef __I2C_BM8563_H__
#define __I2C_BM8563_H__

#include <Wire.h>

#define I2C_BM8563_DEFAULT_ADDRESS 0x51

typedef struct
{
  int8_t hours;
  int8_t minutes;
  int8_t seconds;
} I2C_BM8563_TimeTypeDef;

typedef struct
{
  int8_t weekDay;
  int8_t month;
  int8_t date;
  int16_t year;
} I2C_BM8563_DateTypeDef;

class I2C_BM8563 {
  public:
    I2C_BM8563(uint8_t deviceAddress = I2C_BM8563_DEFAULT_ADDRESS, TwoWire &i2cPort = Wire);

    void begin(void);
    bool getVoltLow();

    void getTime(I2C_BM8563_TimeTypeDef* I2C_BM8563_TimeStruct);
    void getDate(I2C_BM8563_DateTypeDef* I2C_BM8563_DateStruct);

    void setTime(I2C_BM8563_TimeTypeDef* I2C_BM8563_TimeStruct);
    void setDate(I2C_BM8563_DateTypeDef* I2C_BM8563_DateStruct);

    int SetAlarmIRQ(int afterSeconds);
    int SetAlarmIRQ(const I2C_BM8563_TimeTypeDef &I2C_BM8563_TimeStruct);
    int SetAlarmIRQ(const I2C_BM8563_DateTypeDef &I2C_BM8563_DateStruct, const I2C_BM8563_TimeTypeDef &I2C_BM8563_TimeStruct);

    void clearIRQ();
    void disableIRQ();

    void WriteReg(uint8_t reg, uint8_t data);
    uint8_t ReadReg(uint8_t reg);

  private:
    uint8_t bcd2ToByte(uint8_t value);
    uint8_t byteToBcd2(uint8_t value);

    uint8_t trdata[7];
    TwoWire *_i2cPort;
    int _deviceAddress;
};

#endif