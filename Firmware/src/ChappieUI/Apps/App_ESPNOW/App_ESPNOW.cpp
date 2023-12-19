#if 1
#include "App_ESPNOW.h"
#include "../../../ChappieBsp/Chappie.h"


static std::string app_name = "ESPNOW";
static CHAPPIE* device;


LV_IMG_DECLARE(ui_img_icon_espnow_png);



/* ------------------------------------ ESPNOW ------------------------------------ */
/**
 * @file App_ESPNOW.cpp
 * @author Forairaaaaa
 * @brief Two-Way Communication
 * @version 0.1
 * @date 2023-04-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <esp_now.h>
#include <WiFi.h>

static LGFX_Sprite* _screen;
static esp_now_peer_info_t _peerInfo;
static bool is_joystick_mode = true;

// REPLACE WITH THE MAC Address of your receiver 
static uint8_t _broadcastAddress[] = {0x34, 0x85, 0x18, 0x92, 0xE8, 0x84};
// static uint8_t _broadcastAddress[] = {0x34, 0x85, 0x18, 0x92, 0xE8, 0x94};


static void _espnow_joystick_sender()
{
    static char data_send[20];
    static int x, y;
    

    /* Get toupad data */
    if (device->Tp.isTouched()) {
        device->Tp.getPos(x, y); 
    }
    else {
        x = 0;
        y = 0;
    }

    /* Espnow send data */
    if ((x == 0) && (y == 0))
        snprintf(data_send, sizeof(data_send), "S:%d,%d", x, y);
    else 
        snprintf(data_send, sizeof(data_send), "S:%d,%d", x - _screen->width() / 2, -(y - _screen->height() / 2));
    esp_now_send(_broadcastAddress, (uint8_t*)data_send, sizeof(data_send));

    /* Update screen */
    _screen->fillScreen(0xCFDCAEU);
    if ((x == 0) && (y == 0)) {
        x = _screen->width() / 2;
        y = _screen->height() / 2;
    }
    _screen->fillSmoothCircle(x, y, 75, 0x9BB090U);
    _screen->pushSprite(0, 0);

    delay(10);
}


static void _espnow_imu_sender()
{
    static char data_send[20];
    static bool imu_inited = false;
    static float y, p, r;

    if (!imu_inited) {
        device->Lcd.printf("Init IMU...\n");
        imu_inited = true;
        device->Imu.init();
    }

    device->Imu.getYawPitchRoll(y, p, r);

    snprintf(data_send, sizeof(data_send), "S:%0.1f,%0.1f,%0.1f", y, p, r);
    esp_now_send(_broadcastAddress, (uint8_t*)data_send, sizeof(data_send));

    _screen->fillScreen(TFT_BLACK);
    _screen->setTextSize(2);
    _screen->setTextColor(TFT_ORANGE);
    _screen->setCursor(0, 30);
    _screen->printf(" > Yaw:   %.1f\n > Pitch: %.1f\n > Row:   %.1f\n", y, p, r);
    _screen->printf(" > (=^.^=)\n");
    _screen->pushSprite(0, 0);

    delay(10);
}


static void _espnow_choose_sender_mode()
{
    device->Lcd.fillScreen(TFT_BLACK);
    device->Lcd.setCursor(0, 0);
    device->Lcd.setTextSize(1.5);
    device->Lcd.setTextColor(TFT_ORANGE, TFT_BLACK);

    device->Lcd.printf("> Choose sender mode <\n");
    device->Lcd.printf("> BtnA: Joystick\n");
    device->Lcd.printf("> BtnB: IMU\n");

    while (1) {
        if (device->Button.A.pressed()) {
            is_joystick_mode = true;
            break;
        }
        if (device->Button.B.pressed()) {
            is_joystick_mode = false;
            break;
        }
        delay(10);
    }
}



static void _espnow_send_callback(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    _screen->printf("< Sent to: %s %s\n", macStr, (status == ESP_NOW_SEND_SUCCESS ? "success" : "failed"));
    _screen->pushSprite(0, 0);
}



static void _espnow_receive_callback(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    /* Print out as string */
    printf("%s\n", data);
}



static void _espnow_init()
{
    _screen = new LGFX_Sprite(&device->Lcd);
    _screen->setPsram(true);
    _screen->createSprite(device->Lcd.width(), device->Lcd.height());
    _screen->setTextScroll(true);
    _screen->setTextSize(1.2);

    device->Lcd.fillScreen(TFT_BLACK);
    device->Lcd.setCursor(0, 0);
    device->Lcd.setTextSize(1.5);
    device->Lcd.setTextColor(TFT_WHITE, TFT_BLACK);

    /* Init espnow */
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        device->Lcd.printf("Error initializing ESP-NOW\n");
        return;
    }
    device->Lcd.printf("  MAC: %s\n", WiFi.macAddress().c_str());

    /* Add peer */
    memcpy(_peerInfo.peer_addr, _broadcastAddress, 6);
    _peerInfo.channel = 0;  
    _peerInfo.encrypt = false;
    if (esp_now_add_peer(&_peerInfo) != ESP_OK){
        device->Lcd.printf("Failed to add peer\n");
        return;
    }

    /* Send callback */
    // esp_now_register_send_cb(_espnow_send_callback);
    /* Receive callback */
    esp_now_register_recv_cb(_espnow_receive_callback);

    /* To see your MAC */
    // while (1);
}



static void _espnow_loop()
{
    if (is_joystick_mode)
        _espnow_joystick_sender();
    else
        _espnow_imu_sender();
}



static void _espnow_deinit()
{
    WiFi.disconnect(true);
    _screen->deleteSprite();
    delete _screen;
}


/* ------------------------------------ ESPNOW ------------------------------------ */



namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_ESPNOW_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_ESPNOW_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_espnow_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_ESPNOW_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_ESPNOW_appName().c_str());

        _espnow_choose_sender_mode();
        _espnow_init();
        while (1) {
            _espnow_loop();
            if (device->Button.B.pressed())
                break;
        }
        _espnow_deinit();


        lv_obj_t * label = lv_label_create(lv_scr_act());
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(label, "Press B again to quit");
    }


    /**
     * @brief Called repeatedly, end this function ASAP! or the App management will be affected
     * If the thing you want to do takes time, try create a taak or lvgl timer to handle them.
     * Try use millis() instead of delay() here
     * 
     */
    void App_ESPNOW_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_ESPNOW_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_ESPNOW_appName().c_str());
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_ESPNOW_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
