/*
 * @Author: Flying
 * @Date: 2022-05-01 22:51:10
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:51:48
 * @Description: 新建文件
 */
#include "../app.h"
int app_switch_1(lv_obj_t *parent);
lv_obj_t *app_switch()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("switch example", parent);
    app_common_obj_add_item(list1, "switch 简单演示", app_switch_1);
    return parent;
}
