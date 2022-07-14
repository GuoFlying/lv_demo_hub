/*
 * @Author: Flying
 * @Date: 2022-05-01 22:49:04
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:49:38
 * @Description: 新建文件
 */
#include "../app.h"

int app_spinner_1(lv_obj_t *parent)
{
    /*Create a spinner*/
    lv_obj_t *spinner = lv_spinner_create(parent, 1000, 60);
    lv_obj_set_size(spinner, 100, 100);
    lv_obj_center(spinner);
    return 0;
}
