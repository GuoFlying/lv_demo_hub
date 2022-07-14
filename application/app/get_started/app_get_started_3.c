/*
 * @Author: Flying
 * @Date: 2022-05-02 16:41:46
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:42:38
 * @Description: 新建文件
 */
#include "../app.h"

static lv_obj_t *label;

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);

    /*Refresh the text*/
    lv_label_set_text_fmt(label, "%" LV_PRId32, lv_slider_get_value(slider));
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15); /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
int app_get_started_3(lv_obj_t *parent)
{
    /*Create a slider in the center of the display*/
    lv_obj_t *slider = lv_slider_create(parent);
    lv_obj_set_width(slider, 200);                                              /*Set the width*/
    lv_obj_center(slider);                                                      /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL); /*Assign an event function*/

    /*Create a label below the slider*/
    label = lv_label_create(parent);
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15); /*Align top of the slider*/
    return 0;
}
