/*
 * @Author: Flying
 * @Date: 2022-03-25 22:16:00
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-17 09:38:31
 * @Description: 新建文件
 */
#include "wm_home_btn.h"
#include "../../common/c_common.h"
#include <string>
#define BOX_SIZE (40 * MY_UI_W_ZOOM)
#define BOX_MAX_SIZE (160 * MY_UI_W_ZOOM)

//转换UTF-16： https://www.qqxiuzi.cn/bianma/Unicode-UTF.php
#define UNICODE_HOME "\xEE\x98\x8A"    // 0XE60A
#define UNICODE_ABOUT "\xEE\x99\xAA"   // 0XE66A
#define UNICODE_THEME "\xEE\x9B\x86"   // 0XE6C6
#define UNICODE_EXPLAIN "\xEE\xA3\x88" // 0XE8C8
#define UNICODE_PUS "\xEE\x98\xA8"     // 0XE628
#define UNICODE_SETTING_U16 0XE78E

#define UNICONDE_SIZE (18 * MY_UI_W_ZOOM)
/**
 * @description:
 * @param {*}
 * @return {*}
 */
wm_home_btn::wm_home_btn(home_btn_event_cb_t cb, void *cb_arg)
{
    this->cb = cb;
    this->cb_arg = cb_arg;
    this->cont = lv_obj_create(lv_layer_sys());
    lv_obj_set_style_radius(this->cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(this->cont, lv_color_hex(0x00bcec), 0);
    lv_obj_set_style_size(this->cont, 0, 0);
    lv_obj_set_style_pad_all(this->cont, 0, 0);
    lv_obj_set_style_border_width(this->cont, 0, 0);
    lv_obj_set_style_shadow_width(this->cont, 0, 0);
    lv_obj_set_style_bg_opa(this->cont, LV_OPA_0, 0);
    this->cont->user_data = this;

    for (int i = 0; i < 4; i++)
    {
        this->btn_items[i] = lv_label_create(this->cont);
        lv_obj_set_style_radius(this->btn_items[i], LV_RADIUS_CIRCLE, 0);
        // lv_obj_set_pos(this->btn_items[i], LV_PCT(80), LV_PCT(80));
        lv_obj_set_size(this->btn_items[i], BOX_SIZE, BOX_SIZE);
        lv_obj_set_style_border_width(this->btn_items[i], 0, 0);
        lv_obj_set_style_bg_color(this->btn_items[i], lv_color_hex(0x7f7f7f), 0);
        lv_obj_set_style_bg_opa(this->btn_items[i], LV_OPA_0, 0);
        lv_obj_set_style_bg_opa(this->btn_items[i], LV_OPA_100, LV_STATE_PRESSED);
        lv_obj_set_style_opa(this->btn_items[i], LV_OPA_0, LV_PART_SCROLLBAR);
        this->btn_items[i]->user_data = (void *)i;
        lv_obj_set_style_pad_top(this->btn_items[i], (BOX_SIZE - UNICONDE_SIZE) / 2.0 + 0.5, 0);
        lv_obj_set_style_pad_top(this->btn_items[i], (BOX_SIZE - UNICONDE_SIZE) / 2.0 + 0.5, LV_STATE_PRESSED);
        lv_obj_set_style_text_align(this->btn_items[i], LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_add_flag(this->btn_items[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(this->btn_items[i], wm_home_btn::items_clicket_event_cb, LV_EVENT_CLICKED, this);
    }
    lv_obj_set_style_text_font(this->btn_items[0], c_font::get_icon_font(UNICONDE_SIZE), 0);
    lv_label_set_text(this->btn_items[0], UNICODE_HOME);
    // lv_obj_set_style_bg_img_src(this->btn_items[0], UNICODE_HOME, 0);
    lv_obj_align(this->btn_items[0], LV_ALIGN_TOP_MID, 0, 0 * MY_UI_H_ZOOM);

    lv_obj_set_style_text_font(this->btn_items[1], c_font::get_icon_font(UNICONDE_SIZE), 0);
    lv_label_set_text(this->btn_items[1], c_font::get_utf8(UNICODE_SETTING_U16).data());
    // lv_obj_set_style_bg_img_src(this->btn_items[1], UNICODE_ABOUT, 0);
    lv_obj_align(this->btn_items[1], LV_ALIGN_BOTTOM_MID, 0, 0 * MY_UI_H_ZOOM);

    lv_obj_set_style_text_font(this->btn_items[2], c_font::get_icon_font(UNICONDE_SIZE), 0);
    lv_label_set_text(this->btn_items[2], UNICODE_THEME);
    // lv_obj_set_style_bg_img_src(this->btn_items[2], UNICODE_THEME, 0);
    lv_obj_align(this->btn_items[2], LV_ALIGN_LEFT_MID, 0 * MY_UI_W_ZOOM, 0 * MY_UI_H_ZOOM);

    lv_obj_set_style_text_font(this->btn_items[3], c_font::get_icon_font(UNICONDE_SIZE), 0);
    lv_label_set_text(this->btn_items[3], UNICODE_EXPLAIN);
    // lv_obj_set_style_bg_img_src(this->btn_items[3], UNICODE_EXPLAIN, 0);
    lv_obj_align(this->btn_items[3], LV_ALIGN_RIGHT_MID, -0 * MY_UI_W_ZOOM, 0 * MY_UI_H_ZOOM);

    this->btn = lv_label_create(lv_layer_sys());
    lv_obj_set_style_radius(this->btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_pos(this->btn, LV_PCT(80), LV_PCT(80));
    lv_obj_set_size(this->btn, BOX_SIZE, BOX_SIZE);
    lv_obj_set_style_border_width(this->btn, 0, 0);
    lv_obj_set_style_bg_color(this->btn, lv_color_hex(0x7f7f7f), 0);
    lv_obj_set_style_bg_opa(this->btn, LV_OPA_60, 0);
    lv_obj_set_style_bg_opa(this->btn, LV_OPA_100, LV_STATE_PRESSED);
    lv_obj_set_style_text_font(this->btn, c_font::get_icon_font(UNICONDE_SIZE), 0);
    lv_label_set_text(this->btn, UNICODE_PUS);
    lv_obj_set_style_pad_top(this->btn, (BOX_SIZE - UNICONDE_SIZE) / 2.0 + 0.5, 0);
    lv_obj_set_style_pad_top(this->btn, (BOX_SIZE - UNICONDE_SIZE) / 2.0 + 0.5, LV_STATE_PRESSED);
    // lv_obj_set_style_bg_img_src(this->btn, UNICODE_PUS, 0);
    lv_obj_set_style_opa(this->btn, LV_OPA_0, LV_PART_SCROLLBAR); //滑动条隐藏
    // lv_obj_set_style_border_color(this->btn, lv_color_hex(0x000000), 0);
    lv_obj_add_flag(this->btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_text_align(this->btn, LV_TEXT_ALIGN_CENTER, 0);

    lv_obj_add_event_cb(this->btn, wm_home_btn::move_event_cb, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(this->btn, wm_home_btn::move_event_cb, LV_EVENT_PRESSING, this);
    lv_obj_add_event_cb(this->btn, wm_home_btn::checkout_move_event_cb, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(this->btn, wm_home_btn::clicket_event_cb, LV_EVENT_CLICKED, this);
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
wm_home_btn::~wm_home_btn()
{
}

/**
 * @description:
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_home_btn::items_clicket_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    wm_home_btn *_this = (wm_home_btn *)lv_event_get_user_data(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (!obj)
    {
        return;
    }

    if (LV_EVENT_CLICKED != code)
    {
        return;
    }
    if (_this->cb)
    {
        _this->cb((int)(int64_t)obj->user_data, _this->cb_arg);
    }
}

/**
 * @description:
 * @param {void} *var
 * @param {int32_t} v
 * @return {*}
 */
void wm_home_btn::open_changer_anim_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    lv_coord_t w;
    wm_home_btn *_this = (wm_home_btn *)obj->user_data;

    w = lv_map(v, 0, 256, 0, BOX_MAX_SIZE);
    lv_obj_set_size(obj, w, w);
    lv_obj_align_to(obj, _this->btn, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);

    // lv_coord_t o, o1;
    // o = lv_map(v, 0, 256, 0, LV_OPA_60);
    // o1 = lv_map(v, 0, 256, 0, LV_OPA_COVER);
    w = lv_map(v, 0, 256, 0, BOX_SIZE);
    // int font_size = lv_map(v, 0, 256, 2, UNICONDE_SIZE);
    lv_coord_t p = lv_map(v, 0, 256, LV_OPA_0, LV_OPA_60);

    for (int i = 0; i < 4; i++)
    {
        // lv_obj_set_style_text_font(_this->btn_items[i], c_font::get_icon_font(font_size), 0);
        lv_obj_set_size(_this->btn_items[i], w, w);
        lv_obj_set_style_bg_opa(_this->btn_items[i], p, 0);

        if (v > 250)
        {
            lv_obj_set_style_text_opa(_this->btn_items[i], LV_OPA_100, 0);
        }
        else
        {
            lv_obj_set_style_text_opa(_this->btn_items[i], LV_OPA_0, 0);
        }
        // lv_obj_set_style_bg_img_opa(_this->btn_items[i], o1, 0);
        // lv_obj_set_style_bg_img_recolor_opa(_this->btn_items[i], o1, 0);
    }
}
/**
 * @description:
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_home_btn::clicket_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    wm_home_btn *_this = (wm_home_btn *)lv_event_get_user_data(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (!obj)
    {
        return;
    }

    if (LV_EVENT_CLICKED != code)
    {
        return;
    }
    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_USER_4))
    {
        //触发过移动，不触发clicked事件
        return;
    }
    if (lv_obj_get_width(_this->cont) < BOX_MAX_SIZE / 2)
    {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, _this->cont);
        lv_anim_set_exec_cb(&a, open_changer_anim_cb);
        lv_anim_set_values(&a, 0, 256);
        lv_anim_set_time(&a, 200);
        lv_anim_start(&a);
        lv_obj_set_style_bg_opa(_this->btn, LV_OPA_100, 0);
    }
    else
    {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, _this->cont);
        lv_anim_set_exec_cb(&a, open_changer_anim_cb);
        lv_anim_set_values(&a, 256, 0);
        lv_anim_set_time(&a, 200);
        lv_anim_start(&a);
        lv_obj_set_style_bg_opa(_this->btn, LV_OPA_60, 0);
    }
}

/**
 * @description: 移动home键
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_home_btn::move_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    wm_home_btn *_this = (wm_home_btn *)lv_event_get_user_data(e);
    if (!obj || _this->btn != obj)
    {
        return;
    }

    if (LV_EVENT_PRESSING != code && LV_EVENT_PRESSED != code)
    {
        return;
    }

    if (LV_EVENT_PRESSED == code)
    { // LV_OBJ_FLAG_USER_4 标志用于记录是否有移动，移动了就不触发click事件
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_USER_4);
    }

    lv_indev_t *indev = lv_indev_get_act();
    if (indev == NULL)
    {
        return;
    }

    lv_indev_type_t indev_type = lv_indev_get_type(indev);
    lv_point_t p;
    if (indev_type != LV_INDEV_TYPE_POINTER)
    {
        return;
    }
    lv_point_t vect;
    lv_indev_get_vect(indev, &vect);
    lv_coord_t x = lv_obj_get_x(obj) + vect.x;
    lv_coord_t y = lv_obj_get_y(obj) + vect.y;
    if (vect.x == 0 && vect.y == 0)
    {
        return;
    }
    //移动后就不触发click
    lv_obj_add_flag(obj, LV_OBJ_FLAG_USER_4);

    // LV_LOG_USER("%d %d , %d %d , %d %d\r\n", lv_obj_get_x(obj), lv_obj_get_y(obj), vect.x, vect.y, x, y);
    lv_obj_set_pos(obj, x, y);
    lv_obj_align_to(_this->cont, obj, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);
}

/**
 * @description: 校验移动位置，判断不能超过边缘
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_home_btn::checkout_move_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    wm_home_btn *_this = (wm_home_btn *)lv_event_get_user_data(e);
    if (!obj || _this->btn != obj)
    {
        return;
    }
    lv_coord_t x = lv_obj_get_x(obj);
    lv_coord_t y = lv_obj_get_y(obj);
    if (x > MY_UI_W_MAX - BOX_SIZE * 1.5)
    {
        x = MY_UI_W_MAX - BOX_SIZE * 1.5;
    }
    else if (x < BOX_SIZE / 2)
    {
        x = BOX_SIZE / 2;
    }

    if (y > MY_UI_H_MAX - BOX_SIZE * 1.5)
    {
        y = MY_UI_H_MAX - BOX_SIZE * 1.5;
    }
    else if (y < BOX_SIZE / 2)
    {
        y = BOX_SIZE / 2;
    }
    lv_obj_set_pos(obj, x, y);
    lv_obj_align_to(_this->cont, obj, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);
}
