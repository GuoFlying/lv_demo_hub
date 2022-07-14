/*
 * @Author: Flying
 * @Date: 2022-05-02 16:11:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:12:25
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Using the Arc style properties
 */
int app_style_7(lv_obj_t *parent)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_arc_color(&style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_arc_width(&style, 4);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_arc_create(parent);
    lv_obj_add_style(obj, &style, 0);
    lv_obj_center(obj);
    return 0;
}

