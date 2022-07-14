/*
 * @Author: Flying
 * @Date: 2022-05-01 20:11:46
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 20:37:11
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Create LED's with different brightness and color
 */
int app_led_1(lv_obj_t *parent)
{
    /*Create a LED and switch it OFF*/
    lv_obj_t *led1 = lv_led_create(parent);
    lv_obj_align(led1, LV_ALIGN_CENTER, -80, 0);
    lv_led_off(led1);

    /*Copy the previous LED and set a brightness*/
    lv_obj_t *led2 = lv_led_create(parent);
    lv_obj_align(led2, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_brightness(led2, 150);
    lv_led_set_color(led2, lv_palette_main(LV_PALETTE_RED));

    /*Copy the previous LED and switch it ON*/
    lv_obj_t *led3 = lv_led_create(parent);
    lv_obj_align(led3, LV_ALIGN_CENTER, 80, 0);
    lv_led_on(led3);

    return 0;
}
