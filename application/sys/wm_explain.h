/*
 * @Author: Flying
 * @Date: 2022-05-09 22:49:35
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-11 23:51:05
 * @Description: 新建文件
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
#include <list>
#include <string>

class wm_explain
{
private:
    std::list<std::string> img_scr_list;

    lv_obj_t *cont;
    lv_obj_t *parent;
    static void open_changer_anim_cb(void *var, int32_t v);
    void body_create();

public:
    wm_explain(lv_obj_t *parent);
    ~wm_explain();
    void show();
    bool exit();
};
