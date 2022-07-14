/*
 * @Author: Flying
 * @Date: 2022-04-28 20:57:08
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 21:00:24
 * @Description: 新建文件
 */

#include "../app.h"
int app_calendar_1(lv_obj_t *parent);

lv_obj_t *app_calendar()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("calendar example", parent);
    app_common_obj_add_item(list1, "简单日历展示", app_calendar_1);
    return parent;
}
