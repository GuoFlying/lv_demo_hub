/*
 * @Author: Flying
 * @Date: 2022-05-01 22:51:10
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-15 11:53:14
 * @Description: 新建文件
 */
#include "../app.h"
int app_other_calc_1(lv_obj_t *parent);
int app_other_sketchpad_1(lv_obj_t *parent);

lv_obj_t *app_other()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("other example", parent);
    app_common_obj_add_item(list1, "100ask:计算器控件", app_other_calc_1);
    app_common_obj_add_item(list1, "100ask:画板", app_other_sketchpad_1);

    return parent;
}
