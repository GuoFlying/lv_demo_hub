/*
 * @Author: Flying
 * @Date: 2022-02-25 22:43:33
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-22 09:28:28
 * @Description: 通用配置
 */

#pragma once

#include "my_def.h"

extern int _g_my_ui_w_max;
extern int _g_my_ui_h_max;
extern float _g_my_ui_w_zoom;
extern float _g_my_ui_h_zoom;

//当前屏幕宽高
#define MY_UI_W_MAX _g_my_ui_w_max
#define MY_UI_H_MAX _g_my_ui_h_max
//当前屏幕宽高所需放大比例
#define MY_UI_W_ZOOM _g_my_ui_w_zoom
#define MY_UI_H_ZOOM _g_my_ui_h_zoom
