/*
 * @Author: Flying
 * @Date: 2022-05-01 21:43:48
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:12:24
 * @Description: 新建文件
 */
#include "../app.h"
int app_menu_1(lv_obj_t *parent);
int app_menu_2(lv_obj_t *parent);
int app_menu_3(lv_obj_t *parent);
int app_menu_4(lv_obj_t *parent);
int app_menu_5(lv_obj_t *parent);
lv_obj_t *app_menu()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("menu example", parent);
    app_common_obj_add_item(list1, "简易菜单演示", app_menu_1);
    app_common_obj_add_item(list1, "简单菜单，带返回", app_menu_2);
    app_common_obj_add_item(list1, "简单菜单，带多返回", app_menu_3);
    app_common_obj_add_item(list1, "隐藏界面显示", app_menu_4);
    app_common_obj_add_item(list1, "完整菜单演示：setting", app_menu_5);
    return parent;
}
