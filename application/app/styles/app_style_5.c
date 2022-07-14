/*
 * @Author: Flying
 * @Date: 2022-05-02 16:11:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:12:20
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Using the Shadow style properties
 */
int app_style_5(lv_obj_t *parent)
{
    static lv_style_t style;
    lv_style_init(&style);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, 5);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_GREY, 1));

    /*Add a shadow*/
    lv_style_set_shadow_width(&style, 55);
    lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    //    lv_style_set_shadow_ofs_x(&style, 10);
    //    lv_style_set_shadow_ofs_y(&style, 20);

    /*Create an object with the new style*/
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_add_style(obj, &style, 0);
    lv_obj_center(obj);
    return 0;
}
