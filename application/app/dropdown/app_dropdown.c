/*
 * @Author: Flying
 * @Date: 2022-04-28 21:58:35
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 22:06:29
 * @Description: 新建文件
 */

#include "../app.h"
int app_dropdown_1(lv_obj_t *parent);
int app_dropdown_2(lv_obj_t *parent);
int app_dropdown_3(lv_obj_t *parent);

lv_obj_t *app_dropdown()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("dropdown example", parent);
    app_common_obj_add_item(list1, "简单折叠选择框", app_dropdown_1);
    app_common_obj_add_item(list1, "上下左右 折叠选择框", app_dropdown_2);
    app_common_obj_add_item(list1, "菜单折叠选择框样式：图表旋转", app_dropdown_3);
    return parent;
}
