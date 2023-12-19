/**
 * @file ChappieLvgl.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <Arduino.h>
#include "porting/lv_port_disp.h"
#include "porting/lv_port_indev.h"
#include "porting/lv_port_fs.h"
#include "demos/lv_demos.h"

class ChappieLvgl {
    private:
        bool _enable;
        TaskHandle_t _task_handler;
        SemaphoreHandle_t _semaphore_mutex;
        bool _task_inited;

        /**
         * @brief Task to handle lvgl timer
         * 
         * @param param 
         */
        static void task_lv_timer_handler(void* param)
        {
            ChappieLvgl* lvgl = (ChappieLvgl*)param;
            while (1)
            {
                if (lvgl->isEnable())
                    lv_timer_handler();
                delay(5);
            }
            vTaskDelete(NULL);
        }

    public:
        inline ChappieLvgl() : _task_inited(false) {}

        /**
         * @brief Init lvgl and create a task to handle lv timer
         * 
         * @param lcd 
         * @param tp 
         */
        inline void init(LGFX_EmmaDisplay* lcd, ChappieCTP* tp)
        {
            lv_init();
            lv_port_disp_init(lcd);
            lv_port_indev_init(tp);
            lv_fs_fatfs_init();

            /* Create a task to handle lvgl timer */
            if (!_task_inited) {
                _task_inited = true;
                _semaphore_mutex = xSemaphoreCreateMutex();
                _enable = false;
                xTaskCreate(task_lv_timer_handler, "lvgl", 5000, this, 5, &_task_handler);
            }
        }

        /**
         * @brief Enable lvgl refreshing
         * 
         * @param xTicksToWait 
         */
        inline void enable(TickType_t xTicksToWait = portMAX_DELAY)
        {
            if (_enable)
                return;
            xSemaphoreTake(_semaphore_mutex, xTicksToWait);
            _enable = true;
            xSemaphoreGive(_semaphore_mutex);
        }

        /**
         * @brief Disable lvgl refreshing, your should calll this before calling lvgl API like lv_lable...
         * 
         * @param xTicksToWait 
         */
        inline void disable(TickType_t xTicksToWait = portMAX_DELAY)
        {
            if (!_enable)
                return;
            xSemaphoreTake(_semaphore_mutex, xTicksToWait);
            _enable = false;
            xSemaphoreGive(_semaphore_mutex);
        }

        /**
         * @brief Is lvgl refreshing
         * 
         * @param xTicksToWait 
         * @return true 
         * @return false 
         */
        inline bool isEnable(TickType_t xTicksToWait = portMAX_DELAY)
        {
            xSemaphoreTake(_semaphore_mutex, xTicksToWait);
            bool ret = _enable;
            xSemaphoreGive(_semaphore_mutex);
            return ret;
        }

};


