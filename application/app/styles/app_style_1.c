/*
 * @Author: Flying
 * @Date: 2022-05-02 16:11:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:12:03
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Using the Size, Position and Padding style properties
 */
int app_style_1(lv_obj_t *parent)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_width(&style, 150);
    lv_style_set_height(&style, LV_SIZE_CONTENT);

    lv_style_set_pad_ver(&style, 20);
    lv_style_set_pad_left(&style, 5);

    lv_style_set_x(&style, lv_pct(50));
    lv_style_set_y(&style, 80);

    /*Create an object with the new style*/
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_add_style(obj, &style, 0);

    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label, "Hello");
    return 0;
}
