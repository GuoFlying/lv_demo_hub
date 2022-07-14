/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:34:42
 * @Description: 新建文件
 */

#include "../app.h"
static void set_angle(void *img, int32_t v)
{
    lv_img_set_angle(img, v);
}

static void set_zoom(void *img, int32_t v)
{
    lv_img_set_zoom(img, v);
}

/**
 * Show transformations (zoom and rotation) using a pivot point.
 */
int app_img_3(lv_obj_t *parent)
{
    LV_IMG_DECLARE(app_img_cogwheel_argb);

    /*Now create the actual image*/
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &app_img_cogwheel_argb);
    lv_obj_align(img, LV_ALIGN_CENTER, 50, 50);
    lv_img_set_pivot(img, 0, 0); /*Rotate around the top left corner*/

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_values(&a, 0, 3600);
    lv_anim_set_time(&a, 5000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);

    lv_anim_set_exec_cb(&a, set_zoom);
    lv_anim_set_values(&a, 128, 256);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_start(&a);
    return 0;
}
