/*
 * @Author: Flying
 * @Date: 2022-03-26 23:31:44
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-14 12:15:44
 * @Description: 新建文件
 */
#include "wm_footer.h"

#define ITEM_SIZE ((10 * MY_UI_H_ZOOM) > 2 ? (10 * MY_UI_H_ZOOM) : 2)
#define ITEM_SPACE ((6 * MY_UI_W_ZOOM) > 1 ? (6 * MY_UI_W_ZOOM) : 1)
#define OFF_COLOR (0x9f9f9f)
#define ON_COLOR (0xab03f2)
//回调上报间隔3* lvgl 长按间隔时间（目前为100ms） = 300ms
#define CB_REPORTED_TIME 3

wm_footer::wm_footer(lv_obj_t *parent, uint8_t size, footer_event_cb_t footer_cb, void *cb_arg)
{
    this->old_index = -1;
    this->footer_cb = footer_cb;
    this->cb_arg = cb_arg;
    this->item_list.clear();
    this->cont = lv_obj_create(parent);
    lv_obj_align(this->cont, LV_ALIGN_BOTTOM_MID, 0, -50 * MY_UI_H_ZOOM);
    lv_obj_set_size(this->cont, (ITEM_SPACE * 2 + ITEM_SIZE) * size, (ITEM_SPACE + ITEM_SIZE) * 2);
    lv_obj_set_style_pad_all(this->cont, 0, 0);
    lv_obj_set_style_border_width(this->cont, 0, 0);
    lv_obj_set_style_radius(this->cont, 0, 0);
    lv_obj_set_style_bg_opa(this->cont, LV_OPA_0, 0);

    for (int i = 0; i < size; i++)
    {
        lv_obj_t *obj = lv_led_create(this->cont);
        lv_obj_set_size(obj, ITEM_SIZE, ITEM_SIZE);
        // lv_led_set_color(obj, lv_color_hex(OFF_COLOR));
        // lv_obj_set_style_shadow_width(obj, 2, 0);
        lv_obj_set_style_shadow_spread(obj, 5 * MY_UI_W_ZOOM, 0);
        lv_led_off(obj);
        int x = ITEM_SPACE + i * (ITEM_SIZE + ITEM_SPACE * 2);
        int y = ITEM_SPACE;
        lv_obj_set_pos(obj, x, y);
        this->item_list.push_back(obj);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
    }
    this->select(0);

    lv_obj_add_event_cb(this->cont, wm_footer::footer_event_cb, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(this->cont, wm_footer::footer_event_cb, LV_EVENT_PRESSING, this);
}

wm_footer::~wm_footer()
{
}

/**
 * @description: 选择当前第几个
 * @param {int} index
 * @return {*}
 */
void wm_footer::select(int index)
{
    if (index >= this->item_list.size())
    {
        return;
    }

    if (this->old_index != -1)
    {
        // lv_led_set_color(this->item_list.at(this->old_index), lv_color_hex(OFF_COLOR));
        lv_led_off(this->item_list.at(this->old_index));
    }
    this->old_index = index;
    // lv_led_set_color(this->item_list.at(this->old_index), lv_color_hex(ON_COLOR));
    lv_led_on(this->item_list.at(this->old_index));
}
/**
 * @description:
 * @param {lv_color_t} color
 * @return {*}
 */
void wm_footer::set_bg_color(lv_color_t color)
{
    for (auto item : this->item_list)
    {
        lv_obj_set_style_bg_color(item, color, 0);
    }
}

/**
 * @description: 通过实际x坐标获取当前是第几个index
 * @param {int} x
 * @return {*}
 */
int wm_footer::get_index_by_x(int x)
{
    int parent_x = lv_obj_get_x(this->cont);
    int item_size = ITEM_SIZE + ITEM_SPACE * 2;
    if (x <= parent_x)
    {
        return 0;
    }
    int diff = x - parent_x;
    int index = diff / item_size;
    if (index >= this->item_list.size() - 1)
    {
        index = this->item_list.size() - 1;
    }
    return index;
}

/**
 * @description: 点击事件处理
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_footer::footer_event_cb(lv_event_t *e)
{
    wm_footer *_this = (wm_footer *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED && code != LV_EVENT_PRESSING)
    {
        return;
    }

    if (!_this || !_this->footer_cb)
    {
        return;
    }

    lv_indev_t *indev = lv_indev_get_act();
    if (indev == NULL)
        return;

    lv_indev_type_t indev_type = lv_indev_get_type(indev);
    lv_point_t p;
    if (indev_type != LV_INDEV_TYPE_POINTER)
    {
        return;
    }
    lv_indev_get_point(indev, &p);
    // LV_LOG_USER("%p x  %d  y  %d", obj, p.x, p.y);
    int index = _this->get_index_by_x(p.x);
    if (index == -1)
    {
        return;
    }

    // footer的user_data用于记录cb进入次数，控制回调间隔
    int *count = (int *)&_this->cont->user_data;
    if (code == LV_EVENT_CLICKED)
    {
        *count = 0;
    }

    if (*count == 0 || *count > CB_REPORTED_TIME)
    {
        _this->footer_cb(index, _this->cb_arg);
        *count = 0;
    }
    (*count)++;

    _this->select(index);
}