/*
 * @Author: Flying
 * @Date: 2022-05-02 16:41:46
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:49:15
 * @Description: 新建文件
 */
#include "../app.h"
int app_get_started_1(lv_obj_t *parent);
int app_get_started_2(lv_obj_t *parent);
int app_get_started_3(lv_obj_t *parent);
lv_obj_t *app_get_started()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("get_started example", parent);
    app_common_obj_add_item(list1, "获取按键值", app_get_started_1);
    app_common_obj_add_item(list1, "按键按下颜色修改演示", app_get_started_2);
    app_common_obj_add_item(list1, "滑动条事件监控演示", app_get_started_3);
    return parent;
}
