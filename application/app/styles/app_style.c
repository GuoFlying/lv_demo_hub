/*
 * @Author: Flying
 * @Date: 2022-05-02 16:11:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:24:04
 * @Description: 新建文件
 */
#include "../app.h"
int app_style_1(lv_obj_t *parent);
int app_style_2(lv_obj_t *parent);
int app_style_3(lv_obj_t *parent);
int app_style_4(lv_obj_t *parent);
int app_style_5(lv_obj_t *parent);
int app_style_6(lv_obj_t *parent);
int app_style_7(lv_obj_t *parent);
int app_style_8(lv_obj_t *parent);
int app_style_9(lv_obj_t *parent);
int app_style_10(lv_obj_t *parent);
int app_style_11(lv_obj_t *parent);
int app_style_12(lv_obj_t *parent);
int app_style_13(lv_obj_t *parent);
lv_obj_t *app_style()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("styles example", parent);
    app_common_obj_add_item(list1, "边框", app_style_1);
    app_common_obj_add_item(list1, "渐变色", app_style_2);
    app_common_obj_add_item(list1, "阴影", app_style_3);
    app_common_obj_add_item(list1, "内边距", app_style_4);
    app_common_obj_add_item(list1, "发散阴影", app_style_5);
    app_common_obj_add_item(list1, "图片背景", app_style_6);
    app_common_obj_add_item(list1, "arc 样式修改", app_style_7);
    app_common_obj_add_item(list1, "text 样式修改", app_style_8);
    app_common_obj_add_item(list1, "line 样式修改", app_style_9);
    app_common_obj_add_item(list1, "obj +点击 样式修改", app_style_10);
    app_common_obj_add_item(list1, "obj + text 样式修改", app_style_11);
    app_common_obj_add_item(list1, "obj 背景样式修改", app_style_12);
    app_common_obj_add_item(list1, "slider 样式修改", app_style_13);
    return parent;
}
