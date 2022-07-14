/*
 * @Author: Flying
 * @Date: 2022-05-02 11:24:32
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 14:33:12
 * @Description: 新建文件
 */
/**
 * @file app_music.h
 *
 */

#ifndef APP_MUSIC_H
#define APP_MUSIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "app_music_conf.h"

    /*********************
     *      DEFINES
     *********************/

#if APP_MUSIC_LARGE
#define APP_MUSIC_HANDLE_SIZE 40
#else
#define APP_MUSIC_HANDLE_SIZE 20
#endif

    /**********************
     *      TYPEDEFS
     **********************/

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    const char *_app_music_get_title(uint32_t track_id);
    const char *_app_music_get_artist(uint32_t track_id);
    const char *_app_music_get_genre(uint32_t track_id);
    uint32_t _app_music_get_track_length(uint32_t track_id);

    /**********************
     *      MACROS
     **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_MUSIC_H*/
