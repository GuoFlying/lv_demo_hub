/*
 * @Author: Flying
 * @Date: 2022-05-01 22:18:19
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:30:45
 * @Description: 新建文件
 */
#include "../app.h"

static lv_obj_t *meter;

static void set_value(void *indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}
static void parent_del_cb(lv_event_t *e)
{
    lv_anim_del_all();
}

/**
 * A clock from a meter
 */
int app_meter_3(lv_obj_t *parent)
{
    lv_obj_add_event_cb(parent, parent_del_cb, LV_EVENT_DELETE, NULL);
    meter = lv_meter_create(parent);
    lv_obj_set_size(meter, 220, 220);
    lv_obj_center(meter);

    /*Create a scale for the minutes*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t *scale_min = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);

    /*Create another scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t *scale_hour = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY)); /*12 ticks*/
    lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 2, 20, lv_color_black(), 10);       /*Every tick is major*/
    lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);                            /*[1..12] values in an almost full circle*/

    LV_IMG_DECLARE(app_img_hand)

    /*Add a the hands from images*/
    lv_meter_indicator_t *indic_min = lv_meter_add_needle_img(meter, scale_min, &app_img_hand, 5, 5);
    lv_meter_indicator_t *indic_hour = lv_meter_add_needle_img(meter, scale_min, &app_img_hand, 5, 5);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 60);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_time(&a, 2000); /*2 sec for 1 turn of the minute hand (1 hour)*/
    lv_anim_set_var(&a, indic_min);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_hour);
    lv_anim_set_time(&a, 24000); /*24 sec for 1 turn of the hour hand*/
    lv_anim_set_values(&a, 0, 60);
    lv_anim_start(&a);
    return 0;
}
