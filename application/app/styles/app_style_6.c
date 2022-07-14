/*
 * @Author: Flying
 * @Date: 2022-05-02 16:11:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:15:06
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Using the Image style properties
 */
int app_style_6(lv_obj_t *parent)
{
    static lv_style_t style;
    lv_style_init(&style);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, 5);
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_GREY, 3));
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_img_recolor(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_img_recolor_opa(&style, LV_OPA_50);
    lv_style_set_transform_angle(&style, 300);

    /*Create an object with the new style*/
    lv_obj_t *obj = lv_img_create(parent);
    lv_obj_add_style(obj, &style, 0);

    LV_IMG_DECLARE(app_img_cogwheel_argb);
    lv_img_set_src(obj, &app_img_cogwheel_argb);

    lv_obj_center(obj);
    return 0;
}
