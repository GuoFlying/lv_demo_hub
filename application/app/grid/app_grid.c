/*
 * @Author: Flying
 * @Date: 2022-05-02 17:15:00
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 17:24:08
 * @Description: 新建文件
 */
#include "../app.h"
int app_grid_1(lv_obj_t *parent);
int app_grid_2(lv_obj_t *parent);
int app_grid_3(lv_obj_t *parent);
int app_grid_4(lv_obj_t *parent);
int app_grid_5(lv_obj_t *parent);
int app_grid_6(lv_obj_t *parent);
lv_obj_t *app_grid()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("grid example", parent);
    app_common_obj_add_item(list1, "基础grid演示1", app_grid_1);
    app_common_obj_add_item(list1, "基础grid演示2", app_grid_2);
    app_common_obj_add_item(list1, "基础grid演示3", app_grid_3);
    app_common_obj_add_item(list1, "基础grid演示4", app_grid_4);
    app_common_obj_add_item(list1, "基础grid演示5", app_grid_5);
    app_common_obj_add_item(list1, "基础grid演示6", app_grid_6);
    return parent;
}
