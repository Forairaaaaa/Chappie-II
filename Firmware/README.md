工程为PIO工程，vscode安装PIO扩展后打开文件夹即可

#### 文件树

```
Chappie-II/
├── default_16MB.csv
├── lib
│   ├── arduinoFFT
│   ├── ESP32-BLE-Gamepad
│   ├── FastLED
│   ├── LovyanGFX
│   ├── lv_conf.h
│   ├── lvgl
│   ├── NimBLE-Arduino
│   └── README
├── platformio.ini
├── src
    ├── ChappieBsp
    ├── ChappieUI
    └── main.cpp

```

#### 下载依赖

```shell
git submodule init
git submodule update
```

```shell
cd lib
git clone https://github.com/lovyan03/LovyanGFX.git
git clone -b v8.3.5 https://github.com/lvgl/lvgl.git
git clone https://github.com/FastLED/FastLED.git
git clone https://github.com/lemmingDev/ESP32-BLE-Gamepad.git
git clone https://github.com/h2zero/NimBLE-Arduino.git
git clone https://github.com/kosme/arduinoFFT.git
```

