/*
 * @Author: Flying
 * @Date: 2022-05-01 22:38:00
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:41:04
 * @Description: 新建文件
 */
#include "../app.h"
int app_roller_1(lv_obj_t *parent);
int app_roller_2(lv_obj_t *parent);
int app_roller_3(lv_obj_t *parent);
lv_obj_t *app_roller()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("roller example", parent);
    app_common_obj_add_item(list1, "无线滚动roller演示", app_roller_1);
    app_common_obj_add_item(list1, "左中右 roller演示", app_roller_2);
    app_common_obj_add_item(list1, "渐变色roller演示", app_roller_3);
    return parent;
}
