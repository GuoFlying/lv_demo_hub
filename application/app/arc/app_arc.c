/*
 * @Author: Flying
 * @Date: 2022-04-28 20:22:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 20:29:08
 * @Description: 新建文件
 */
#include "../app.h"
int app_arc_1(lv_obj_t *parent);
int app_arc_2(lv_obj_t *parent);

lv_obj_t *app_arc()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("arc example", parent);
    app_common_obj_add_item(list1, "支持滑动的简单的弧形", app_arc_1);
    app_common_obj_add_item(list1, "圆弧动画", app_arc_2);
    return parent;
}
