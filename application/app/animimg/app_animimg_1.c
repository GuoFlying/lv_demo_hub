/*
 * @Author: Flying
 * @Date: 2022-04-26 22:11:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:50:41
 * @Description: 新建文件
 */
#include "../app.h"

LV_IMG_DECLARE(app_animimg001)
LV_IMG_DECLARE(app_animimg002)
LV_IMG_DECLARE(app_animimg003)

static const lv_img_dsc_t *anim_imgs[3] = {
    &app_animimg001,
    &app_animimg002,
    &app_animimg003,
};

int app_animimg_1(lv_obj_t *parent)
{
    lv_obj_t *animimg0 = lv_animimg_create(parent);
    lv_obj_center(animimg0);
    lv_animimg_set_src(animimg0, (lv_img_dsc_t **)anim_imgs, 3);
    lv_animimg_set_duration(animimg0, 1000);
    lv_animimg_set_repeat_count(animimg0, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animimg0);
    return 0;
}
