/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-08 22:46:04
 * @Description: 新建文件
 */

#include "../app.h"
static lv_obj_t *create_slider(lv_obj_t *parent, lv_color_t color);
static void slider_event_cb(lv_event_t *e);

static lv_obj_t *img1;

/**
 * Demonstrate runtime image re-coloring
 */
int app_img_5(lv_obj_t *parent)
{
    lv_obj_t *zoom_slider = create_slider(parent, lv_palette_main(LV_PALETTE_AMBER));
    lv_slider_set_value(zoom_slider, 500, LV_ANIM_OFF);
    lv_obj_align(zoom_slider, LV_ALIGN_LEFT_MID, 25, 0);

    LV_IMG_DECLARE(app_img_cogwheel_argb)
    img1 = lv_img_create(parent);
    lv_img_set_src(img1, &app_img_cogwheel_argb);
    lv_obj_align(img1, LV_ALIGN_RIGHT_MID, -50, 0);

    lv_event_send(zoom_slider, LV_EVENT_VALUE_CHANGED, NULL);

    return 0;
}

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *zoom_slider = lv_event_get_target(e);
    int val = lv_slider_get_value(zoom_slider);
    int zoom_val = lv_map(val, 0, 1000, 128, 512);
    lv_img_set_zoom(img1, zoom_val);
    lv_obj_invalidate(img1);

    LV_LOG_USER("zoom =  %d", zoom_val);
    LV_LOG_USER("img (w,h) =  (%d,%d)", lv_obj_get_width(img1), lv_obj_get_height(img1));
}

static lv_obj_t *create_slider(lv_obj_t *parent, lv_color_t color)
{
    lv_obj_t *slider = lv_slider_create(parent);
    lv_slider_set_range(slider, 0, 1000);
    lv_obj_set_size(slider, 10, 200);
    lv_obj_set_style_bg_color(slider, color, LV_PART_KNOB);
    lv_obj_set_style_bg_color(slider, lv_color_darken(color, LV_OPA_40), LV_PART_INDICATOR);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    return slider;
}
