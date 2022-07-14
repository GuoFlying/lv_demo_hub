/*
 * @Author: Flying
 * @Date: 2022-06-22 13:19:30
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-22 15:11:25
 * @Description: 新建文件
 */
/**
 * @file my_bmp.h
 *
 */

#ifndef MY_BMP_H
#define MY_BMP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf.h"
#include "../lvgl/lvgl.h"

#if !LV_USE_BMP

    /*********************
     *      DEFINES
     *********************/

    /**********************
     *      TYPEDEFS
     **********************/

    /**********************
     * GLOBAL PROTOTYPES
     **********************/
    void my_bmp_init(void);

    /**********************
     *      MACROS
     **********************/

#endif /*LV_USE_BMP*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*MY_BMP_H*/
