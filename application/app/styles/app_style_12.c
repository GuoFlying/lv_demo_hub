/*
 * @Author: Flying
 * @Date: 2022-05-02 16:11:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:12:44
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Local styles
 */
int app_style_12(lv_obj_t *parent)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_border_color(&style, lv_palette_lighten(LV_PALETTE_GREEN, 3));
    lv_style_set_border_width(&style, 3);

    lv_obj_t * obj = lv_obj_create(parent);
    lv_obj_add_style(obj, &style, 0);

    /*Overwrite the background color locally*/
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);

    lv_obj_center(obj);
    return 0;
}

