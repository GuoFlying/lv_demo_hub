/*
 * @Author: Flying
 * @Date: 2022-05-01 23:04:22
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 23:07:48
 * @Description: 新建文件
 */
#include "../app.h"
int app_textarea_1(lv_obj_t *parent);
int app_textarea_2(lv_obj_t *parent);
int app_textarea_3(lv_obj_t *parent);
lv_obj_t *app_textarea()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("textarea example", parent);
    app_common_obj_add_item(list1, "单行输入框演示", app_textarea_1);
    app_common_obj_add_item(list1, "密码输入框演示", app_textarea_2);
    app_common_obj_add_item(list1, "单行输入框自动分号", app_textarea_3);
    return parent;
}
