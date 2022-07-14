/*
 * @Author: Flying
 * @Date: 2022-05-01 22:35:37
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:36:23
 * @Description: 新建文件
 */
#include "../app.h"
int app_obj_1(lv_obj_t *parent);
int app_obj_2(lv_obj_t *parent);
lv_obj_t *app_obj()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("obj example", parent);
    app_common_obj_add_item(list1, "最基础控件 obj展示1", app_obj_1);
    app_common_obj_add_item(list1, "最基础控件 obj展示2", app_obj_2);
    return parent;
}
