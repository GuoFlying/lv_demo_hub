/*
 * @Author: Flying
 * @Date: 2022-04-28 21:06:42
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 21:10:55
 * @Description: 新建文件
 */
#include "../app.h"
int app_canvas_1(lv_obj_t *parent);
int app_canvas_2(lv_obj_t *parent);

lv_obj_t *app_canvas()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("canvas example", parent);
    app_common_obj_add_item(list1, "画布绘画多彩矩阵+文字显示", app_canvas_1);
    app_common_obj_add_item(list1, "画布简单叠加效果", app_canvas_2);
    return parent;
}
