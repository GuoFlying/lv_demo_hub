/*
 * @Author: Flying
 * @Date: 2022-04-28 21:58:03
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 22:00:31
 * @Description: 新建文件
 */
#include "../app.h"

int app_colorwheel_1(lv_obj_t *parent)
{
    lv_obj_t *cw;

    cw = lv_colorwheel_create(parent, true);
    lv_obj_set_size(cw, 200, 200);
    lv_obj_center(cw);
    return 0;
}
