/*
 * @Author: Flying
 * @Date: 2022-02-25 22:50:47
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-06 12:14:35
 * @Description: 基础公用(并不是标准.H)
 */

#include "my_conf.h"
int _g_my_ui_w_max = MY_REALITE_W_MAX;
int _g_my_ui_h_max = MY_REALITE_H_MAX;
float _g_my_ui_w_zoom = MY_REALITE_W_MAX * 1.0f / MY_BASE_W_MAX;
float _g_my_ui_h_zoom = MY_REALITE_H_MAX * 1.0f / MY_BASE_H_MAX;

static void my_app_init(int argc, char *argv[]);
static void my_app_main(int argc, char *argv[]);
static void my_touch_feedback(struct _lv_indev_drv_t *drv, unsigned char ev);