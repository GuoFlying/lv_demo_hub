/*
 * @Author: Flying
 * @Date: 2022-05-01 22:49:04
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:49:52
 * @Description: 新建文件
 */
#include "../app.h"
int app_spinner_1(lv_obj_t *parent);
lv_obj_t *app_spinner()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("spinner example", parent);
    app_common_obj_add_item(list1, "简易加载动画", app_spinner_1);
    return parent;
}
