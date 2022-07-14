/*
 * @Author: Flying
 * @Date: 2022-05-02 17:15:11
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 17:23:46
 * @Description: 新建文件
 */
#include "../app.h"
int app_flex_1(lv_obj_t *parent);
int app_flex_2(lv_obj_t *parent);
int app_flex_3(lv_obj_t *parent);
int app_flex_4(lv_obj_t *parent);
int app_flex_5(lv_obj_t *parent);
int app_flex_6(lv_obj_t *parent);
lv_obj_t *app_flex()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("flex example", parent);
    app_common_obj_add_item(list1, "基础flex演示1", app_flex_1);
    app_common_obj_add_item(list1, "基础flex演示2", app_flex_2);
    app_common_obj_add_item(list1, "基础flex演示3", app_flex_3);
    app_common_obj_add_item(list1, "基础flex演示4", app_flex_4);
    app_common_obj_add_item(list1, "基础flex演示5", app_flex_5);
    app_common_obj_add_item(list1, "基础flex演示6", app_flex_6);
    return parent;
}
