/*
 * @Author: Flying
 * @Date: 2022-04-28 20:30:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:46:18
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Bar with stripe pattern and ranged value
 */
int app_bar_4(lv_obj_t *parent)
{
    LV_IMG_DECLARE(app_img_skew_strip);
    static lv_style_t style_indic;

    lv_style_init(&style_indic);
    lv_style_set_bg_img_src(&style_indic, &app_img_skew_strip);
    lv_style_set_bg_img_tiled(&style_indic, true);
    lv_style_set_bg_img_opa(&style_indic, LV_OPA_30);

    lv_obj_t *bar = lv_bar_create(parent);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);

    lv_obj_set_size(bar, 260, 20);
    lv_obj_center(bar);
    lv_bar_set_mode(bar, LV_BAR_MODE_RANGE);
    lv_bar_set_value(bar, 90, LV_ANIM_OFF);
    lv_bar_set_start_value(bar, 20, LV_ANIM_OFF);
    return 0;
}
