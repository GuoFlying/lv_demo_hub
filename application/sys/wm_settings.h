/*
 * @Author: Flying
 * @Date: 2022-05-09 22:49:35
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-18 22:45:40
 * @Description: 新建文件
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
class wm_settings
{
private:
    lv_obj_t *cont;
    lv_obj_t *parent;
    static void open_changer_anim_cb(void *var, int32_t v);
    void body_create();

public:
    wm_settings(lv_obj_t *parent);
    ~wm_settings();
    void show();
    bool exit();
};
