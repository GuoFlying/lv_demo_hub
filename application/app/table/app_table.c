/*
 * @Author: Flying
 * @Date: 2022-05-01 22:54:36
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:56:37
 * @Description: 新建文件
 */
#include "../app.h"
int app_table_1(lv_obj_t *parent);
int app_table_2(lv_obj_t *parent);
lv_obj_t *app_table()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("table example", parent);
    app_common_obj_add_item(list1, "简易表达演示", app_table_1);
    app_common_obj_add_item(list1, "带switch表格", app_table_2);
    return parent;
}
