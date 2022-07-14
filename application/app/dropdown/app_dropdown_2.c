/*
 * @Author: Flying
 * @Date: 2022-04-28 21:58:12
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 22:02:16
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Create a drop down, up, left and right menus
 */
int app_dropdown_2(lv_obj_t *parent)
{
    static const char *opts = "Apple\n"
                              "Banana\n"
                              "Orange\n"
                              "Melon";

    lv_obj_t *dd;
    dd = lv_dropdown_create(parent);
    lv_dropdown_set_options_static(dd, opts);
    lv_obj_align(dd, LV_ALIGN_TOP_MID, 0, 10);

    dd = lv_dropdown_create(parent);
    lv_dropdown_set_options_static(dd, opts);
    lv_dropdown_set_dir(dd, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(dd, LV_SYMBOL_UP);
    lv_obj_align(dd, LV_ALIGN_BOTTOM_MID, 0, -10);

    dd = lv_dropdown_create(parent);
    lv_dropdown_set_options_static(dd, opts);
    lv_dropdown_set_dir(dd, LV_DIR_RIGHT);
    lv_dropdown_set_symbol(dd, LV_SYMBOL_RIGHT);
    lv_obj_align(dd, LV_ALIGN_LEFT_MID, 10, 0);

    dd = lv_dropdown_create(parent);
    lv_dropdown_set_options_static(dd, opts);
    lv_dropdown_set_dir(dd, LV_DIR_LEFT);
    lv_dropdown_set_symbol(dd, LV_SYMBOL_LEFT);
    lv_obj_align(dd, LV_ALIGN_RIGHT_MID, -10, 0);
    return 0;
}
