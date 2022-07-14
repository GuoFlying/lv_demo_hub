/*
 * @Author: Flying
 * @Date: 2022-05-01 22:45:06
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:45:36
 * @Description: 新建文件
 */
#include "../app.h"
int app_span_1(lv_obj_t *parent);
lv_obj_t *app_span()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("span example", parent);
    app_common_obj_add_item(list1, "多色彩文本展示", app_span_1);
    return parent;
}
