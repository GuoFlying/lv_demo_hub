/*
 * @Author: Flying
 * @Date: 2022-05-02 11:24:32
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 14:08:48
 * @Description: 新建文件
 */
/**
 * @file app_music_list.h
 *
 */

#ifndef APP_MUSIC_LIST_H
#define APP_MUSIC_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "app_music.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t * _app_music_list_create(lv_obj_t * parent);
void _app_music_list_btn_check(uint32_t track_id, bool state);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_MUSIC_LIST_H*/
