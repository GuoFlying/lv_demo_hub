/*
 * @Author: Flying
 * @Date: 2022-04-26 22:11:46
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-26 22:47:23
 * @Description: 新建文件
 */
#include "../app.h"
int app_animimg_1(lv_obj_t *parent);

lv_obj_t *app_animimg()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("animimg example", parent);
    app_common_obj_add_item(list1, "图片动画简单实现", app_animimg_1);
    return parent;
}
