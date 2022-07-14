/*
 * @Author: Flying
 * @Date: 2022-05-09 22:49:27
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-11 23:54:50
 * @Description: 新建文件
 */
#include "wm_explain.h"
#include "../../common/c_common.h"
#include <string.h>
wm_explain::wm_explain(lv_obj_t *parent)
{
    this->parent = parent;
    this->cont = NULL;

    for (int i = 1; i <= 2; i++)
    {
        std::string tmp = MY_PNG_PATH;
        tmp += "explain/" + std::to_string(i) + ".png";
        img_scr_list.push_back(tmp);
    }
}

wm_explain::~wm_explain()
{
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void wm_explain::show()
{
    if (this->cont)
    {
        return;
    }

    this->cont = lv_tileview_create(this->parent);
    lv_obj_set_style_radius(this->cont, 0, 0);

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
void wm_explain::body_create()
{
    int index = 0;
    for (auto item : this->img_scr_list)
    {
        lv_obj_t *tile = lv_tileview_add_tile(this->cont, 0, index++, LV_DIR_VER);

        lv_obj_t *label = lv_label_create(tile);
        lv_obj_set_style_text_font(label, c_font::get_font(40 * MY_UI_H_ZOOM), 0);
        lv_label_set_text_fmt(label, "说明页：%d", index);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10 * MY_UI_H_ZOOM);

        lv_obj_t *img = lv_img_create(tile);
        // lv_img_set_src(img, "S./resource/img/explain/2.png");
        lv_img_set_src(img, item.data());
        lv_obj_set_size(img, 600, 360);
        lv_obj_center(img);
    }
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
bool wm_explain::exit()
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
void wm_explain::open_changer_anim_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    lv_coord_t w, h;
    wm_explain *_this = (wm_explain *)obj->user_data;

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
    o = lv_map(v, 0, 256, 0, LV_OPA_100);
    lv_obj_set_style_bg_opa(obj, o, 0);
}