#include "I2C_BM8563.h"

I2C_BM8563::I2C_BM8563(uint8_t deviceAddress, TwoWire &i2cPort) {
  _deviceAddress = deviceAddress;
  _i2cPort = &i2cPort;
}

void I2C_BM8563::begin(void) {
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(0x00);
  _i2cPort->write(0x00);
  _i2cPort->write(0x00);
  _i2cPort->endTransmission();
}

bool I2C_BM8563::getVoltLow() {
  uint8_t data = ReadReg(0x02);
  return data & 0x80; // RTCC_VLSEC_MASK
}

uint8_t I2C_BM8563::bcd2ToByte(uint8_t value) {
  uint8_t tmp = 0;
  tmp = ((uint8_t)(value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (value & (uint8_t)0x0F));
}

uint8_t I2C_BM8563::byteToBcd2(uint8_t value) {
  uint8_t bcdhigh = 0;

  while (value >= 10) {
    bcdhigh++;
    value -= 10;
  }

  return ((uint8_t)(bcdhigh << 4) | value);
}

void I2C_BM8563::getTime(I2C_BM8563_TimeTypeDef* I2C_BM8563_TimeStruct) {
  uint8_t buf[3] = {0};

  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(0x02);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 3);

  while (_i2cPort->available()) {
    buf[0] = _i2cPort->read();
    buf[1] = _i2cPort->read();
    buf[2] = _i2cPort->read();
  }

  I2C_BM8563_TimeStruct->seconds = bcd2ToByte(buf[0] & 0x7f);
  I2C_BM8563_TimeStruct->minutes = bcd2ToByte(buf[1] & 0x7f);
  I2C_BM8563_TimeStruct->hours   = bcd2ToByte(buf[2] & 0x3f);
}

void I2C_BM8563::setTime(I2C_BM8563_TimeTypeDef* I2C_BM8563_TimeStruct) {
  if (I2C_BM8563_TimeStruct == NULL) {
    return;
  }

  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(0x02);
  _i2cPort->write(byteToBcd2(I2C_BM8563_TimeStruct->seconds));
  _i2cPort->write(byteToBcd2(I2C_BM8563_TimeStruct->minutes));
  _i2cPort->write(byteToBcd2(I2C_BM8563_TimeStruct->hours));
  _i2cPort->endTransmission();
}

void I2C_BM8563::getDate(I2C_BM8563_DateTypeDef* I2C_BM8563_DateStruct) {
  uint8_t buf[4] = {0};

  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(0x05);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 4);

  while (_i2cPort->available()) {
    buf[0] = _i2cPort->read();
    buf[1] = _i2cPort->read();
    buf[2] = _i2cPort->read();
    buf[3] = _i2cPort->read();
  }

  I2C_BM8563_DateStruct->date    = bcd2ToByte(buf[0] & 0x3f);
  I2C_BM8563_DateStruct->weekDay = bcd2ToByte(buf[1] & 0x07);
  I2C_BM8563_DateStruct->month   = bcd2ToByte(buf[2] & 0x1f);

  if (buf[2] & 0x80) {
    I2C_BM8563_DateStruct->year = 1900 + bcd2ToByte(buf[3] & 0xff);
  } else {
    I2C_BM8563_DateStruct->year = 2000 + bcd2ToByte(buf[3] & 0xff);
  }
}

void I2C_BM8563::setDate(I2C_BM8563_DateTypeDef* I2C_BM8563_DateStruct) {
  if (I2C_BM8563_DateStruct == NULL) {
    return;
  }

  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(0x05);
  _i2cPort->write(byteToBcd2(I2C_BM8563_DateStruct->date));
  _i2cPort->write(byteToBcd2(I2C_BM8563_DateStruct->weekDay));

  if (I2C_BM8563_DateStruct->year < 2000) {
    _i2cPort->write(byteToBcd2(I2C_BM8563_DateStruct->month) | 0x80);
    _i2cPort->write(byteToBcd2((uint8_t)(I2C_BM8563_DateStruct->year % 100)));
  } else {
    _i2cPort->write(byteToBcd2(I2C_BM8563_DateStruct->month) | 0x00);
    _i2cPort->write(byteToBcd2((uint8_t)(I2C_BM8563_DateStruct->year % 100)));
  }

  _i2cPort->endTransmission();
}

void I2C_BM8563::WriteReg(uint8_t reg, uint8_t data) {
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(reg);
  _i2cPort->write(data);
  _i2cPort->endTransmission();
}

uint8_t I2C_BM8563::ReadReg(uint8_t reg) {
  _i2cPort->beginTransmission(_deviceAddress);
  _i2cPort->write(reg);
  _i2cPort->endTransmission(false);
  _i2cPort->requestFrom(_deviceAddress, 1);
  return _i2cPort->read();
}

int I2C_BM8563::SetAlarmIRQ(int afterSeconds) {
  uint8_t reg_value = 0;
  reg_value = ReadReg(0x01);

  if (afterSeconds < 0) {
    reg_value &= ~(1 << 0);
    WriteReg(0x01, reg_value);
    reg_value = 0x03;
    WriteReg(0x0E, reg_value);
    return -1;
  }

  uint8_t type_value = 2;
  uint8_t div = 1;
  if (afterSeconds > 255) {
    div = 60;
    type_value = 0x83;
  } else {
    type_value = 0x82;
  }

  afterSeconds = (afterSeconds / div) & 0xFF;
  WriteReg(0x0F, afterSeconds);
  WriteReg(0x0E, type_value);

  reg_value |= (1 << 0);
  reg_value &= ~(1 << 7);
  WriteReg(0x01, reg_value);
  return afterSeconds * div;
}

int I2C_BM8563::SetAlarmIRQ(const I2C_BM8563_TimeTypeDef &I2C_BM8563_TimeStruct) {
  uint8_t irq_enable = false;
  uint8_t out_buf[4] = {0x80, 0x80, 0x80, 0x80};

  if (I2C_BM8563_TimeStruct.minutes >= 0) {
    irq_enable = true;
    out_buf[0] = byteToBcd2(I2C_BM8563_TimeStruct.minutes) & 0x7f;
  }

  if (I2C_BM8563_TimeStruct.hours >= 0) {
    irq_enable = true;
    out_buf[1] = byteToBcd2(I2C_BM8563_TimeStruct.hours) & 0x3f;
  }

  out_buf[2] = 0x80;
  out_buf[3] = 0x80;

  uint8_t reg_value = ReadReg(0x01);

  if (irq_enable) {
    reg_value |= (1 << 1);
  } else {
    reg_value &= ~(1 << 1);
  }

  for (int i = 0; i < 4; i++) {
    WriteReg(0x09 + i, out_buf[i]);
  }
  WriteReg(0x01, reg_value);

  return irq_enable ? 1 : 0;
}

int I2C_BM8563::SetAlarmIRQ(const I2C_BM8563_DateTypeDef &I2C_BM8563_DateStruct, const I2C_BM8563_TimeTypeDef &I2C_BM8563_TimeStruct) {
  uint8_t irq_enable = false;
  uint8_t out_buf[4] = {0x80, 0x80, 0x80, 0x80};

  if (I2C_BM8563_TimeStruct.minutes >= 0) {
    irq_enable = true;
    out_buf[0] = byteToBcd2(I2C_BM8563_TimeStruct.minutes) & 0x7f;
  }

  if (I2C_BM8563_TimeStruct.hours >= 0) {
    irq_enable = true;
    out_buf[1] = byteToBcd2(I2C_BM8563_TimeStruct.hours) & 0x3f;
  }

  if (I2C_BM8563_DateStruct.date >= 0) {
    irq_enable = true;
    out_buf[2] = byteToBcd2(I2C_BM8563_DateStruct.date) & 0x3f;
  }

  if (I2C_BM8563_DateStruct.weekDay >= 0) {
    irq_enable = true;
    out_buf[3] = byteToBcd2(I2C_BM8563_DateStruct.weekDay) & 0x07;
  }

  uint8_t reg_value = ReadReg(0x01);

  if (irq_enable) {
    reg_value |= (1 << 1);
  } else {
    reg_value &= ~(1 << 1);
  }

  for (int i = 0; i < 4; i++) {
    WriteReg(0x09 + i, out_buf[i]);
  }
  WriteReg(0x01, reg_value);

  return irq_enable ? 1 : 0;
}

void I2C_BM8563::clearIRQ() {
  uint8_t data = ReadReg(0x01);
  WriteReg(0x01, data & 0xf3);
}

void I2C_BM8563::disableIRQ() {
  clearIRQ();
  uint8_t data = ReadReg(0x01);
  WriteReg(0x01, data & 0xfC);
}