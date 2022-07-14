/*
 * @Author: Flying
 * @Date: 2021-11-02 10:29:21
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-26 18:52:17
 * @Description: 驱动配置文件
 */

#ifndef LV_DRV_CONF_H
#define LV_DRV_CONF_H

#include "lv_conf.h"
#include "my_conf.h"

/*********************
 *  DISPLAY DRIVERS
 *********************/
#ifdef F_LINUXARM

    #define USE_WIN32DRV 0

    #define USE_FBDEV 1

    #if USE_FBDEV == 0
    #  define USE_SS_FBDEV        1
    #  define SS_FBDEV_V2         1
    #  define SS_FBDEV_V3         0
    #endif

    #if USE_FBDEV || USE_SS_FBDEV
    #define FBDEV_PATH "/dev/fb0"
    #endif

    #define USE_EVDEV 1

    #if USE_EVDEV
    #define EVDEV_NAME "/dev/input/event0" /*You can use the "evtest" Linux tool to get the list of devices and test them*/
    #define EVDEV_SWAP_AXES 0              /*Swap the x and y axes of the touchscreen*/

    #define EVDEV_CALIBRATE 0 /*Scale and offset the touchscreen coordinates by using maximum and minimum values for each axis*/

    #if EVDEV_CALIBRATE
    #define EVDEV_HOR_MIN 0    /*to invert axis swap EVDEV_XXX_MIN by EVDEV_XXX_MAX*/
    #define EVDEV_HOR_MAX 4096 /*"evtest" Linux tool can help to get the correct calibraion values>*/
    #define EVDEV_VER_MIN 0
    #define EVDEV_VER_MAX 4096
    #endif /*EVDEV_CALIBRATE*/
    #endif /*USE_EVDEV*/

#endif

#ifdef F_UBUNTU

/*-------------------
 *  SDL
 *-------------------*/

/* SDL based drivers for display, mouse, mousewheel and keyboard*/
#ifndef USE_SDL
# define USE_SDL 1
#endif

/* Hardware accelerated SDL driver */
#ifndef USE_SDL_GPU
# define USE_SDL_GPU 0
#endif

#if USE_SDL || USE_SDL_GPU
#  define SDL_HOR_RES     MY_REALITE_W_MAX
#  define SDL_VER_RES     MY_REALITE_H_MAX

/* Scale window by this factor (useful when simulating small screens) */
#  define SDL_ZOOM        1

/* Used to test true double buffering with only address changing.
 * Use 2 draw buffers, bith with SDL_HOR_RES x SDL_VER_RES size*/
#  define SDL_DOUBLE_BUFFERED 0

/*Eclipse: <SDL2/SDL.h>    Visual Studio: <SDL.h>*/
#  define SDL_INCLUDE_PATH    <SDL2/SDL.h>

/*Open two windows to test multi display support*/
#  define SDL_DUAL_DISPLAY            0
#endif

/*-------------------
 *  Monitor of PC
 *-------------------*/
#ifndef USE_MONITOR
#  define USE_MONITOR         0
#endif

#if USE_MONITOR
#  define MONITOR_HOR_RES     1024
#  define MONITOR_VER_RES     600

/* Scale window by this factor (useful when simulating small screens) */
#  define MONITOR_ZOOM        1

/* Used to test true double buffering with only address changing.
 * Use 2 draw buffers, bith with MONITOR_HOR_RES x MONITOR_VER_RES size*/
#  define MONITOR_DOUBLE_BUFFERED 0

/*Eclipse: <SDL2/SDL.h>    Visual Studio: <SDL.h>*/
#  define MONITOR_SDL_INCLUDE_PATH    <SDL2/SDL.h>

/*Open two windows to test multi display support*/
#  define MONITOR_DUAL            0
#endif

/*---------------------------------------
 * Mouse or touchpad on PC (using SDL)
 *-------------------------------------*/
#ifndef USE_MOUSE
#  define USE_MOUSE           1
#endif

#if USE_MOUSE
/*No settings*/
#endif

/*-------------------------------------------
 * Mousewheel as encoder on PC (using SDL)
 *------------------------------------------*/
#ifndef USE_MOUSEWHEEL
#  define USE_MOUSEWHEEL      1
#endif

#if USE_MOUSEWHEEL
/*No settings*/
#endif

/*-------------------------------
 *   Keyboard of a PC (using SDL)
 *------------------------------*/
#ifndef USE_KEYBOARD
#  define USE_KEYBOARD        1
#endif

#if USE_KEYBOARD
/*No settings*/
#endif

#endif

#ifdef F_WINDOWS

    #define USE_WIN32DRV 1
    /* Scale window by this factor (useful when simulating small screens) */
    #if USE_WIN32DRV
    #define WIN32DRV_MONITOR_ZOOM 1
    #endif

    #define USE_FBDEV 0
    #define USE_EVDEV 0

#endif


#endif /*LV_DRV_CONF_H*/
