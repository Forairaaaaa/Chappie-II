# ChappieUI

基于[Lvgl](https://github.com/lvgl/lvgl)及[ChappieBsp](https://github.com/Forairaaaaa/ChappieBsp)的简单UI框架，UI框架实现简单App管理，启动器实现基础界面及App图形入口

使用`App_Generator.py`即可一键生成App：

```shell
python ./App_Generator.py
```

#### 文件树

```
ChappieUI/
├── Apps
│   ├── App_Dino
│   ├── App_ESPNOW
│   ├── App_FFT
│   ├── App_Gamepad
│   ├── App_Generator.py
│   ├── AppRegister.h
│   ├── App_Settings
│   ├── App_StupidSnake
│   ├── AppTypedef.h
│   ├── App_Watch
│   ├── App_WifiTV
│   └── Resource
├── ChappieUIConfigs.h
├── ChappieUI.cpp
├── ChappieUI.h
├── Launcher
    ├── App_Launcher.cpp
    ├── App_Launcher.h
    └── UI
```

#### App结构

```c++
/* App名字 */
std::string App_Template_appName();

/* App图标 */
void* App_Template_appIcon();

/* App创建回调 */
void App_Template_onCreate();

/* App循环回调 */
void App_Template_onLoop();

/* App结束回调 */
void App_Template_onDestroy();
```

