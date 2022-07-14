/*
 * @Author: Flying
 * @Date: 2022-05-01 18:21:40
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:41:40
 * @Description: 新建文件
 */

#include "../app.h"
int app_imgbtn_1(lv_obj_t *parent);

lv_obj_t *app_imgbtn()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("imgbtn example", parent);
    app_common_obj_add_item(list1, "图片按键", app_imgbtn_1);
    return parent;
}
