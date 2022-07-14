/*
 * @Author: Flying
 * @Date: 2022-04-05 14:19:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-14 12:36:50
 * @Description: 新建文件
 */
#pragma once
#include "../app.h"

// C 调用 MY_UI_W_ZOOM （c++） 无法编译，C可使用以下接口
#define APP_UI_W_MAX LV_HOR_RES
#define APP_UI_H_MAX LV_VER_RES
#define APP_UI_W_ZOOM (APP_UI_W_MAX * 1.0f / MY_BASE_W_MAX)
#define APP_UI_H_ZOOM (APP_UI_H_MAX * 1.0f / MY_BASE_H_MAX)

typedef int (*app_item_fun_t)(lv_obj_t *parent);

lv_obj_t *app_common_obj_create(const char *title, lv_obj_t *parent);
void *app_common_obj_add_item(lv_obj_t *common_obj, const char *text, app_item_fun_t func);
