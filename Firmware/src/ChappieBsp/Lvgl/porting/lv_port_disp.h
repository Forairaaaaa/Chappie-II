/**
 * @file lv_port_disp_templ.h
 *
 */

/*Copy this file as "lv_port_disp.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_DISP_TEMPL_H
#define LV_PORT_DISP_TEMPL_H

#ifdef __cplusplus
// extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
// #include "lvgl/lvgl.h"
#include <lvgl.h>
#include <Arduino.h>
#include "../../EmmaBSP/Display/EmmaDisplay.hpp"
#endif

/*********************
 *      DEFINES
 *********************/

#define LVGL_LCD_HORIZON
// #define LVGL_LCD_PORTRAIT

#ifdef LVGL_LCD_HORIZON
    #define MY_DISP_HOR_RES     280
    #define MY_DISP_VER_RES     240
    #define LV_VER_RES_MAX      280
#else
#ifdef LVGL_LCD_PORTRAIT
    #define MY_DISP_HOR_RES     240
    #define MY_DISP_VER_RES     280
    #define LV_VER_RES_MAX      240
#endif
#endif


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
// void lv_port_disp_init(void);
void lv_port_disp_init(LGFX_EmmaDisplay* lcd);

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void);

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
// } /*extern "C"*/
#endif

#endif /*LV_PORT_DISP_TEMPL_H*/

#endif /*Disable/Enable content*/
