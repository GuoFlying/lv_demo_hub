/*
 * @Author: Flying
 * @Date: 2022-04-28 20:30:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 20:37:48
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Bar with LTR and RTL base direction
 */
int app_bar_5(lv_obj_t *parent)
{
    lv_obj_t *label;

    lv_obj_t *bar_ltr = lv_bar_create(parent);
    lv_obj_set_size(bar_ltr, 200, 20);
    lv_bar_set_value(bar_ltr, 70, LV_ANIM_OFF);
    lv_obj_align(bar_ltr, LV_ALIGN_CENTER, 0, -30);

    label = lv_label_create(parent);
    lv_label_set_text(label, "Left to Right base direction");
    lv_obj_align_to(label, bar_ltr, LV_ALIGN_OUT_TOP_MID, 0, -5);

    lv_obj_t *bar_rtl = lv_bar_create(parent);
    lv_obj_set_style_base_dir(bar_rtl, LV_BASE_DIR_RTL, 0);
    lv_obj_set_size(bar_rtl, 200, 20);
    lv_bar_set_value(bar_rtl, 70, LV_ANIM_OFF);
    lv_obj_align(bar_rtl, LV_ALIGN_CENTER, 0, 30);

    label = lv_label_create(parent);
    lv_label_set_text(label, "Right to Left base direction");
    lv_obj_align_to(label, bar_rtl, LV_ALIGN_OUT_TOP_MID, 0, -5);
    return 0;
}
