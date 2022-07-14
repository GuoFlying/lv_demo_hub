/*
 * @Author: Flying
 * @Date: 2022-03-25 22:10:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-06 22:31:23
 * @Description: 新建文件
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
class wm_head
{
private:
    lv_obj_t *cont;
    lv_obj_t *vis_handle;
    lv_obj_t *label_date;
    lv_timer_t *date_timer;
    lv_obj_t *placeholder1;
    lv_obj_t *placeholder2;

    lv_obj_t *create_about();
    static void show_date(lv_timer_t *t);

    void set_date_str(char *buff);

public:
    wm_head(lv_obj_t *parent);
    ~wm_head();
    void reset(lv_anim_enable_t anim_en = LV_ANIM_ON);
};
