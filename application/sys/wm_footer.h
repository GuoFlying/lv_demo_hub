/*
 * @Author: Flying
 * @Date: 2022-03-26 23:31:52
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-09 21:26:46
 * @Description: 新建文件
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
#include <iostream>
using namespace std;
#include <vector>

typedef void (*footer_event_cb_t)(int index, void *cb_arg);

class wm_footer
{
private:
    lv_obj_t *cont;
    vector<lv_obj_t *> item_list;
    int old_index;
    footer_event_cb_t footer_cb;
    void *cb_arg;

    static void footer_event_cb(lv_event_t *e);
    int get_index_by_x(int x);

public:
    wm_footer(lv_obj_t *parent, uint8_t size = 1, footer_event_cb_t footer_cb = NULL, void *cb_arg = NULL);
    ~wm_footer();
    void select(int index);
    void set_bg_color(lv_color_t color);
};
