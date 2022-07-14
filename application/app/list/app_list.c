/*
 * @Author: Flying
 * @Date: 2022-05-01 20:30:20
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 20:42:18
 * @Description: 新建文件
 */

#include "../app.h"
int app_list_1(lv_obj_t *parent);
int app_list_2(lv_obj_t *parent);

lv_obj_t *app_list()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("list example", parent);
    app_common_obj_add_item(list1, "带标题列表", app_list_1);
    app_common_obj_add_item(list1, "可点击按键列表", app_list_2);
    return parent;
}
