/*
 * @Author: Flying
 * @Date: 2022-05-01 22:31:45
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:32:11
 * @Description: 新建文件
 */
#include "../app.h"
int app_msgbox_1(lv_obj_t *parent);
lv_obj_t *app_msgbox()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("msgbox example", parent);
    app_common_obj_add_item(list1, "简单弹框演示", app_msgbox_1);
    return parent;
}
