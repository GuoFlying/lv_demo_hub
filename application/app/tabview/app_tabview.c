/*
 * @Author: Flying
 * @Date: 2022-05-01 22:56:54
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 23:03:15
 * @Description: 新建文件
 */
#include "../app.h"
int app_tabview_1(lv_obj_t *parent);
int app_tabview_2(lv_obj_t *parent);
lv_obj_t *app_tabview()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("tabview example", parent);
    app_common_obj_add_item(list1, "横向 tabview", app_tabview_1);
    app_common_obj_add_item(list1, "纵向 tabview", app_tabview_2);
    return parent;
}
