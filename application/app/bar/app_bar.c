
/*
 * @Author: Flying
 * @Date: 2022-04-28 20:22:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 20:42:06
 * @Description: 新建文件
 */
#include "../app.h"
int app_bar_1(lv_obj_t *parent);
int app_bar_2(lv_obj_t *parent);
int app_bar_3(lv_obj_t *parent);
int app_bar_4(lv_obj_t *parent);
int app_bar_5(lv_obj_t *parent);
int app_bar_6(lv_obj_t *parent);

lv_obj_t *app_bar()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("bar example", parent);
    app_common_obj_add_item(list1, "简单进度条显示", app_bar_1);
    app_common_obj_add_item(list1, "带边框进度条展示", app_bar_2);
    app_common_obj_add_item(list1, "竖：进度条显示，渐变色进度条", app_bar_3);
    app_common_obj_add_item(list1, "斑马线进度条", app_bar_4);
    app_common_obj_add_item(list1, "改变进度条值方向", app_bar_5);
    app_common_obj_add_item(list1, "带数字显示进度条", app_bar_6);
    return parent;
}
