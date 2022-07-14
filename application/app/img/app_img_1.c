/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:34:28
 * @Description: 新建文件
 */

#include "../app.h"
int app_img_1(lv_obj_t *parent)
{
    LV_IMG_DECLARE(app_img_cogwheel_argb);
    lv_obj_t *img1 = lv_img_create(parent);
    lv_img_set_src(img1, &app_img_cogwheel_argb);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, -20);
    lv_obj_set_size(img1, 200, 200);

    lv_obj_t *img2 = lv_img_create(parent);
    lv_img_set_src(img2, LV_SYMBOL_OK "Accept");
    lv_obj_align_to(img2, img1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    return 0;
}
