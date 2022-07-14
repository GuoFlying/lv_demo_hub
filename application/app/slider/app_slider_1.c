/*
 * @Author: Flying
 * @Date: 2022-05-01 22:41:24
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-08 21:51:11
 * @Description: 新建文件
 */
#include "../app.h"

static void slider_event_cb(lv_event_t *e);
static lv_obj_t *slider_label;

/**
 * A default slider with a label displaying the current value
 */
int app_slider_1(lv_obj_t *parent)
{
    /*Create a slider in the center of the display*/
    lv_obj_t *slider = lv_slider_create(parent);
    lv_obj_center(slider);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /*Create a label below the slider*/
    slider_label = lv_label_create(parent);
    lv_label_set_text(slider_label, "0%");

    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    return 0;
}

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
