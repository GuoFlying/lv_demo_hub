/*
 * @Author: Flying
 * @Date: 2022-03-27 14:52:57
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-26 21:15:46
 * @Description: 新建文件
 */
#include "../app.h"
int app_label_1(lv_obj_t *parent);
int app_label_2(lv_obj_t *parent);
int app_label_3(lv_obj_t *parent);
int app_label_4(lv_obj_t *parent);
int app_label_5(lv_obj_t *parent);

lv_obj_t *app_label()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("label example", parent);
    app_common_obj_add_item(list1, "彩色文本+滚动", app_label_1);
    app_common_obj_add_item(list1, "阴影文本", app_label_2);
    app_common_obj_add_item(list1, "多国语言显示", app_label_3);
    app_common_obj_add_item(list1, "多彩文本显示", app_label_4);
    app_common_obj_add_item(list1, "超长文本显示方式", app_label_5);
    return parent;
}
