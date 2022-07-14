/*
 * @Author: Flying
 * @Date: 2022-05-01 18:21:38
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-22 15:33:12
 * @Description: 新建文件
 */

#include "../app.h"
int app_img_1(lv_obj_t *parent);
int app_img_2(lv_obj_t *parent);
int app_img_3(lv_obj_t *parent);
int app_img_4(lv_obj_t *parent);
int app_img_5(lv_obj_t *parent);
int app_img_6(lv_obj_t *parent);

lv_obj_t *app_img()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("img example", parent);
    app_common_obj_add_item(list1, "图形现显示", app_img_1);
    app_common_obj_add_item(list1, "图片调色", app_img_2);
    app_common_obj_add_item(list1, "图片旋转+缩放", app_img_3);
    app_common_obj_add_item(list1, "图片位置移动", app_img_4);
    app_common_obj_add_item(list1, "图片放大缩小", app_img_5);
    app_common_obj_add_item(list1, "BMP 图片显示测试", app_img_6);
    return parent;
}
