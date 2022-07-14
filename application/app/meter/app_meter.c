/*
 * @Author: Flying
 * @Date: 2022-05-01 22:18:19
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:27:51
 * @Description: 新建文件
 */
#include "../app.h"
int app_meter_1(lv_obj_t *parent);
int app_meter_2(lv_obj_t *parent);
int app_meter_3(lv_obj_t *parent);
int app_meter_4(lv_obj_t *parent);
lv_obj_t *app_meter()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("meter example", parent);
    app_common_obj_add_item(list1, "速度表盘演示", app_meter_1);
    app_common_obj_add_item(list1, "表盘演示 2：多颜色弧形", app_meter_2);
    app_common_obj_add_item(list1, "时钟", app_meter_3);
    app_common_obj_add_item(list1, "饼状图", app_meter_4);
    return parent;
}
