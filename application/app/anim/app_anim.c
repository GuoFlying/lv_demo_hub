/*
 * @Author: Flying
 * @Date: 2022-05-02 16:53:30
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 17:05:41
 * @Description: 新建文件
 */
#include "../app.h"
int app_anim_1(lv_obj_t *parent);
int app_anim_2(lv_obj_t *parent);
int app_anim_3(lv_obj_t *parent);
int app_anim_timeline_1(lv_obj_t *parent);
lv_obj_t *app_anim()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("anim example", parent);
    app_common_obj_add_item(list1, "滑入滑出效果演示", app_anim_1);
    app_common_obj_add_item(list1, "球体放大缩小动画", app_anim_2);
    app_common_obj_add_item(list1, "可调节运动轨迹", app_anim_3);
    app_common_obj_add_item(list1, "组合动画演示", app_anim_timeline_1);
    return parent;
}
