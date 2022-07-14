/*
 * @Author: Flying
 * @Date: 2022-05-01 20:30:18
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 20:42:51
 * @Description: 新建文件
 */


#include "../app.h"
int app_line_1(lv_obj_t *parent);

lv_obj_t *app_line()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("line example", parent);
    app_common_obj_add_item(list1, "简易画线demo", app_line_1);
    return parent;
}
