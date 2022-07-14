/*
 * @Author: Flying
 * @Date: 2022-05-01 22:46:59
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:47:56
 * @Description: 新建文件
 */
#include "../app.h"
int app_spinbox_1(lv_obj_t *parent);
lv_obj_t *app_spinbox()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("spinbox example", parent);
    app_common_obj_add_item(list1, "简易选值框演示", app_spinbox_1);
    return parent;
}
