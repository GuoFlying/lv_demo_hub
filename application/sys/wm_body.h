/*
 * @Author: Flying
 * @Date: 2022-03-26 12:51:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-01 23:05:01
 * @Description: 新建文件
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
#include <iostream>
using namespace std;
#include <vector>
typedef void (*scroll_event_cb_t)(int index, void *cb_arg);
typedef void (*item_clicked_event_cb_t)(int index, void *cb_arg);

class wm_body
{
private:
    int row_max; //行数
    int col_max; //列数
    lv_obj_t *cont;
    lv_style_t page_style;
    vector<lv_obj_t *> item_list;
    vector<lv_obj_t *> page_list;
    scroll_event_cb_t scroll_cb;
    item_clicked_event_cb_t clicked_cb;
    void *cb_arg;

    lv_obj_t *get_page(uint8_t index);
    static void scroll_event_cb(lv_event_t *e);
    static void item_event_cb(lv_event_t *e);

public:
    wm_body(lv_obj_t *parent, scroll_event_cb_t scroll_cb = NULL, item_clicked_event_cb_t clicked_cb = NULL, void *cb_arg = NULL);
    ~wm_body();
    lv_obj_t *add_item(int current_frame, char *lottie_name, char *label_text);

    void select_page(int index, lv_anim_enable_t anim_en = LV_ANIM_ON);
    int get_page_count();
};
