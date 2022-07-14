/*
 * @Author: Flying
 * @Date: 2022-04-28 20:22:02
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 20:28:52
 * @Description: 新建文件
 */
#include "../app.h"

int app_arc_1(lv_obj_t *parent)
{
    /*Create an Arc*/
    lv_obj_t *arc = lv_arc_create(parent);
    lv_obj_set_size(arc, 150, 150);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 40);
    lv_obj_center(arc);
    return 0;
}
