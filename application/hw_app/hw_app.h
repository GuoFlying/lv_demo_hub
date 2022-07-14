/*
 * @Author: Flying
 * @Date: 2022-03-27 14:53:51
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 23:02:02
 * @Description: 标题说明
 * H: 配合硬件设备可实现功能的app
 */
#pragma once
#include "../../lvgl/lvgl.h"
#include "../../lv_lib_100ask/lv_lib_100ask.h"
#include "../../my_conf.h"

typedef lv_obj_t *(*app_fun_t)();

lv_obj_t *hw_app_folder();
lv_obj_t *hw_app_peripheral();
lv_obj_t *hw_app_video();
lv_obj_t *hw_app_wifi();
lv_obj_t *hw_app_voice();
//{40, "video.json", "H:视频硬解", hw_app_video},
//{100, "voice.json", "H:语音识别", hw_app_voice},
//{40, "peripheral.json", "H:外设相关", hw_app_peripheral},

#define _HW_APPS_FUN_LIST                           \
    {40, "folder.json", "H:文件夹", hw_app_folder}, \
        {40, "wifi.json", "H:MI_WLAN", hw_app_wifi},
