/*
 * @Author: Flying
 * @Date: 2022-04-28 20:44:09
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-28 20:48:36
 * @Description: 新建文件
 */

#include "../app.h"
int app_btnmatrix_1(lv_obj_t *parent);
int app_btnmatrix_2(lv_obj_t *parent);
int app_btnmatrix_3(lv_obj_t *parent);

lv_obj_t *app_btnmatrix()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("btnmatrix example", parent);
    app_common_obj_add_item(list1, "简单自定义矩阵键盘", app_btnmatrix_1);
    app_common_obj_add_item(list1, "带颜色图像的矩阵键盘", app_btnmatrix_2);
    app_common_obj_add_item(list1, "横行矩阵按键", app_btnmatrix_3);
    return parent;
}
