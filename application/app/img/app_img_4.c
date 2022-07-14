/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:40:34
 * @Description: 新建文件
 */

#include "../app.h"
static void ofs_y_anim(void *img, int32_t v)
{
    lv_img_set_offset_y(img, v);
}

/**
 * Image styling and offset
 */
int app_img_4(lv_obj_t *parent)
{
    LV_IMG_DECLARE(app_img_skew_strip);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_img_recolor_opa(&style, LV_OPA_COVER);
    lv_style_set_img_recolor(&style, lv_color_black());

    lv_obj_t *img = lv_img_create(parent);
    lv_obj_add_style(img, &style, 0);
    lv_img_set_src(img, &app_img_skew_strip);
    lv_obj_set_size(img, 150, 100);
    lv_obj_center(img);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);
    lv_anim_set_exec_cb(&a, ofs_y_anim);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
    return 0;
}
