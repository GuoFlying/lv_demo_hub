/*
 * @Author: Flying
 * @Date: 2022-04-28 21:58:33
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 22:01:32
 * @Description: 新建文件
 */
#include "../app.h"
int app_colorwheel_1(lv_obj_t *parent);

lv_obj_t *app_colorwheel()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("colorwheel example", parent);
    app_common_obj_add_item(list1, "颜色选择控件简单演示", app_colorwheel_1);
    return parent;
}
