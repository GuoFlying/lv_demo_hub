/*
 * @Author: Flying
 * @Date: 2022-05-01 22:41:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:44:42
 * @Description: 新建文件
 */
#include "../app.h"
int app_slider_1(lv_obj_t *parent);
int app_slider_2(lv_obj_t *parent);
int app_slider_3(lv_obj_t *parent);
lv_obj_t *app_slider()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("slider example", parent);
    app_common_obj_add_item(list1, "基础滑动条", app_slider_1);
    app_common_obj_add_item(list1, "滑动条风格修改", app_slider_2);
    app_common_obj_add_item(list1, "双向调节滑动条", app_slider_3);
    return parent;
}
