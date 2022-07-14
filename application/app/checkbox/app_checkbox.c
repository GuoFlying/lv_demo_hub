/*
 * @Author: Flying
 * @Date: 2022-04-28 21:52:22
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 21:56:21
 * @Description: 新建文件
 */
#include "../app.h"
int app_checkbox_1(lv_obj_t *parent);
int app_checkbox_2(lv_obj_t *parent);

lv_obj_t *app_checkbox()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("checkbox example", parent);
    app_common_obj_add_item(list1, "多选框", app_checkbox_1);
    app_common_obj_add_item(list1, "单选框", app_checkbox_2);
    return parent;
}
