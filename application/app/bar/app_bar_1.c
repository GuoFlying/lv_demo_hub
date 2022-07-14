/*
 * @Author: Flying
 * @Date: 2022-04-28 20:30:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 20:38:18
 * @Description: 新建文件
 */
#include "../app.h"
int app_bar_1(lv_obj_t *parent)
{
    lv_obj_t *bar1 = lv_bar_create(parent);
    lv_obj_set_size(bar1, 200, 20);
    lv_obj_center(bar1);
    lv_bar_set_value(bar1, 70, LV_ANIM_OFF);
    return 0;
}
