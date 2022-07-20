/*
 * @Author: Flying
 * @Date: 2022-05-09 22:49:27
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-18 22:45:43
 * @Description: 新建文件
 */
#include "wm_settings.h"
#include "../../common/c_common.h"
wm_settings::wm_settings(lv_obj_t *parent)
{
    this->parent = parent;
    this->cont = NULL;
}

wm_settings::~wm_settings()
{
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void wm_settings::show()
{
    if (this->cont)
    {
        return;
    }

    this->cont = lv_obj_create(this->parent);
    lv_obj_align(this->cont, LV_ALIGN_BOTTOM_MID, 0, 0);
    // lv_obj_set_size(this->cont, MY_UI_W_MAX, MY_UI_H_MAX);
    lv_obj_set_size(this->cont, 10, 10);
    lv_obj_set_style_bg_opa(this->cont, LV_OPA_0, 0);
    lv_obj_set_style_radius(this->cont, 20 * MY_UI_H_ZOOM, 0);
    this->cont->user_data = (void *)this;
    this->body_create();

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, this->cont);
    lv_anim_set_exec_cb(&a, open_changer_anim_cb);
    lv_anim_set_values(&a, 0, 256);
    lv_anim_set_time(&a, 200);
    lv_anim_start(&a);
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void wm_settings::body_create()
{
    lv_obj_set_flex_flow(this->cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(this->cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    {
        lv_obj_t *label = lv_label_create(this->cont);
        lv_obj_set_style_text_font(label, c_font::get_font(40 * MY_UI_H_ZOOM), 0);
        lv_label_set_text(label, "关于");
    }

    {
        lv_obj_t *label = lv_label_create(this->cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text_fmt(label, "版本：%s", MY_VERSION);
    }

    {
        lv_obj_t *label = lv_label_create(this->cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text(label, "作者：Flying");
    }

    {
        lv_obj_t *label = lv_label_create(this->cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text_fmt(label, "编译时间：%s", __DATE__);
    }

    {
        lv_obj_t *obj = lv_rlottie_create_from_file(this->cont, 240 * MY_UI_W_ZOOM, 240 * MY_UI_H_ZOOM, MY_LOTTIE_PATH "about.json");
    }
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
bool wm_settings::exit()
{
    if (this->cont)
    {
        lv_obj_del(this->cont);
        this->cont = NULL;
        return true;
    }
    return false;
}

/**
 * @description: 动画轨迹
 * @param {void} *var
 * @param {int32_t} v
 * @return {*}
 */
void wm_settings::open_changer_anim_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    lv_coord_t w, h;
    wm_settings *_this = (wm_settings *)obj->user_data;

    w = lv_map(v, 0, 256, 10, MY_UI_W_MAX * 0.95);
    h = lv_map(v, 0, 256, 10, MY_UI_H_MAX * 0.95);
    lv_obj_set_size(obj, w, h);
    if (v > 250)
    {
        lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    }
    else
    {
        lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, 0);
    }
    lv_opa_t o;
    o = lv_map(v, 0, 256, 0, LV_OPA_90);
    lv_obj_set_style_bg_opa(obj, o, 0);
}