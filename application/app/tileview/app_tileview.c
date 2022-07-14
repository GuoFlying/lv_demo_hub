/*
 * @Author: Flying
 * @Date: 2022-05-01 23:08:39
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 23:10:21
 * @Description: 新建文件
 */
#include "../app.h"
int app_tileview_1(lv_obj_t *parent);
lv_obj_t *app_tileview()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("tileview example", parent);
    app_common_obj_add_item(list1, "tileview_1", app_tileview_1);
    return parent;
}
