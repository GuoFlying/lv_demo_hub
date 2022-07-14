/*
 * @Author: Flying
 * @Date: 2022-05-01 20:30:15
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 20:41:17
 * @Description: 新建文件
 */

#include "../app.h"
int app_led_1(lv_obj_t *parent);

lv_obj_t *app_led()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("led example", parent);
    app_common_obj_add_item(list1, "简易led灯显示", app_led_1);
    return parent;
}
