/*
 * @Author: Flying
 * @Date: 2022-03-26 12:51:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-19 22:25:27
 * @Description: 新建文件
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
#include <iostream>
using namespace std;
#include <vector>

class wm_body;
using wm_body_event_cb_t = void (*)(wm_body *_body);
class wm_body
{
public:
    enum CODE_E
    {
        CODE_CLICKED,
        CODE_SCROLL,
        CODE_GESTURE_UP
    };

private:
    int row_max; //行数
    int col_max; //列数
    lv_obj_t *cont;
    lv_style_t page_style;
    vector<lv_obj_t *> item_list;
    vector<lv_obj_t *> page_list;
    wm_body_event_cb_t event_cb;
    void *cb_arg;

    int sync_page;
    int sync_index;
    CODE_E sync_code;

    lv_obj_t *get_page(uint8_t index);
    static void scroll_event_cb(lv_event_t *e);
    static void item_event_cb(lv_event_t *e);

public:
    wm_body(lv_obj_t *parent, wm_body_event_cb_t event_cb = NULL, void *cb_arg = NULL);
    ~wm_body();
    lv_obj_t *add_item(int current_frame, char *lottie_name, char *label_text, bool is_draw_line = false);

    void select_page(int index, lv_anim_enable_t anim_en = LV_ANIM_ON);
    int get_page_count();
    int get_sync_page()
    {
        return this->sync_page;
    }
    int get_sync_index()
    {
        return this->sync_index;
    }
    void *get_cb_arg()
    {
        return this->cb_arg;
    }
    CODE_E get_sync_code()
    {
        return this->sync_code;
    }
};
