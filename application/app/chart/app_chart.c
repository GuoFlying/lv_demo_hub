/*
 * @Author: Flying
 * @Date: 2022-04-28 21:14:29
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 21:50:26
 * @Description: 新建文件
 */

#include "../app.h"
int app_chart_1(lv_obj_t *parent);
int app_chart_2(lv_obj_t *parent);
int app_chart_3(lv_obj_t *parent);
int app_chart_4(lv_obj_t *parent);
int app_chart_5(lv_obj_t *parent);
int app_chart_6(lv_obj_t *parent);
int app_chart_7(lv_obj_t *parent);
int app_chart_8(lv_obj_t *parent);
int app_chart_9(lv_obj_t *parent);

lv_obj_t *app_chart()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("chart example", parent);
    app_common_obj_add_item(list1, "简单折线图表", app_chart_1);
    app_common_obj_add_item(list1, "动态折线图表", app_chart_2);
    app_common_obj_add_item(list1, "柱形图", app_chart_3);
    app_common_obj_add_item(list1, "可滑动折线图表", app_chart_4);
    app_common_obj_add_item(list1, "可放大缩小的波形图", app_chart_5);
    app_common_obj_add_item(list1, "折线图-点击可查看数值", app_chart_6);
    app_common_obj_add_item(list1, "点阵图表", app_chart_7);
    app_common_obj_add_item(list1, "堆积折线图", app_chart_8);
    app_common_obj_add_item(list1, "动态连接折线图", app_chart_9);
    return parent;
}
