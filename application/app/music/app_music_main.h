/*
 * @Author: Flying
 * @Date: 2022-05-02 11:24:32
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 14:08:37
 * @Description: 新建文件
 */
/**
 * @file app_music_main.h
 *
 */

#ifndef APP_MUSIC_MAIN_H
#define APP_MUSIC_MAIN_H

#ifdef __cplusplus
extern "C"
{
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
    lv_obj_t *_app_music_main_create(lv_obj_t *parent);
    void _app_music_play(uint32_t id);
    void _app_music_resume(void);
    void _app_music_pause(void);
    void _app_music_album_next(bool next);

    /**********************
     *      MACROS
     **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_MUSIC_MAIN_H*/
