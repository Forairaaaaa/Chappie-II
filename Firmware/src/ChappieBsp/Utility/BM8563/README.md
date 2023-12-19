Thanks to: https://github.com/tanakamasayuki/I2C_BM8563.git

# I2C BM8563 RTC Library

This is a library of BM8563, the RTC for I2C connectivity.

## Support Devices

- [M5Stack M5Stick](https://docs.m5stack.com/#/en/core/m5stickc)
- [M5Stack M5Stick Plus](https://docs.m5stack.com/#/en/core/m5stickc_plus)
- [M5Stack Core2](https://docs.m5stack.com/#/en/core/core2)
- [M5Stack Timer Camera](https://docs.m5stack.com/#/en/unit/timercam)
- [M5Stack Timer Camera X](https://docs.m5stack.com/#/en/unit/timercam_x)
- [M5Stack CoreInk](https://docs.m5stack.com/#/en/core/coreink)

## Usage
```c
#include "I2C_BM8563.h"
#include <WiFi.h>

// RTC BM8563 I2C port
// I2C pin definition for M5Stick & M5Stick Plus & M5Stack Core2 & M5Stack Core.Ink
#define BM8563_I2C_SDA 21
#define BM8563_I2C_SCL 22

// I2C pin definition for M5Stack TimerCam
// #define BM8563_I2C_SDA 12
// #define BM8563_I2C_SCL 14

I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire1);

const char* ntpServer = "time.cloudflare.com";

void setup() {
  // Init Serial
  Serial.begin(115200);
  delay(50);

  // Connect to an access point
  WiFi.begin();                 // Connect to the access point of the last connection
  //WiFi.begin("SSID", "KEY");  // Or, Connect to the specified access point

  Serial.print("Connecting to Wi-Fi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // Set ntp time to local
  configTime(9 * 3600, 0, ntpServer);

  // Init I2C
  Wire1.begin(BM8563_I2C_SDA, BM8563_I2C_SCL);

  // Init RTC
  rtc.begin();

  // Get local time
  struct tm timeInfo;
  if (getLocalTime(&timeInfo)) {
    // Set RTC time
    I2C_BM8563_TimeTypeDef timeStruct;
    timeStruct.hours   = timeInfo.tm_hour;
    timeStruct.minutes = timeInfo.tm_min;
    timeStruct.seconds = timeInfo.tm_sec;
    rtc.setTime(&timeStruct);

    // Set RTC Date
    I2C_BM8563_DateTypeDef dateStruct;
    dateStruct.weekDay = timeInfo.tm_wday;
    dateStruct.month   = timeInfo.tm_mon + 1;
    dateStruct.date    = timeInfo.tm_mday;
    dateStruct.year    = timeInfo.tm_year + 1900;
    rtc.setDate(&dateStruct);
  }
}

void loop() {
  I2C_BM8563_DateTypeDef dateStruct;
  I2C_BM8563_TimeTypeDef timeStruct;

  // Get RTC
  rtc.getDate(&dateStruct);
  rtc.getTime(&timeStruct);

  // Print RTC
  Serial.printf("%04d/%02d/%02d %02d:%02d:%02d\n",
                dateStruct.year,
                dateStruct.month,
                dateStruct.date,
                timeStruct.hours,
                timeStruct.minutes,
                timeStruct.seconds
               );

  // Wait
  delay(1000);
}
```